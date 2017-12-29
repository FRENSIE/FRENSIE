//---------------------------------------------------------------------------//
//!
//! \file   Geometry_RootNavigator.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  The Root navigator class declaration
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>

// FRENSIE Includes
#include "Geometry_RootNavigator.hpp"
#include "Geometry_RootModel.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_GlobalOpenMPSession.hpp"
#include "Utility_ContractException.hpp"

namespace Geometry{

// Initialize static member data
const double RootNavigator::s_tol = 1e-5;

// Default constructor
RootNavigator::RootNavigator()
  : d_root_model(),
    d_internal_ray_set( false ),
    d_navigator( NULL )
{ /* ... */ }
  
// Constructor
RootNavigator::RootNavigator( const std::shared_ptr<const RootModel>& root_model )
  : d_root_model( root_model ),
    d_internal_ray_set( false ),
    d_navigator( RootNavigator::createInternalRay( d_root_model->getManager() ) )
{ /* ... */ }

// Destructor
RootNavigator::~RootNavigator()
{
  this->freeInternalRay();
}

// Get the point location w.r.t. a given cell
/*! \details Root only allows one to test if a point is inside or outside
 * a cell (not on a cell). If the point is on a cell Root will return
 * inside (unless one of the boundary cells is a daughter node of the
 * cell or interest).
 */
PointLocation RootNavigator::getPointLocation(
                         const double position[3],
                         const double*,
                         const ModuleTraits::InternalCellHandle cell_id ) const
{
  TGeoVolume* cell = d_root_model->getVolumePtr( cell_id );

  PointLocation location;

  if( cell->Contains( position ) )
  {
    location = POINT_INSIDE_CELL;

    // Check if the point is an any daughters
    TObjArray* daughters = cell->GetNodes();

    if( daughters != NULL )
    {
      TIterator* daughter_it = daughters->MakeIterator();
      unsigned long long number_of_daughters = daughters->GetEntries();

      for( unsigned long long i = 0; i < number_of_daughters; ++i )
      {
        // Obtain the next object in the array and cast it to its derived class
        TObject* daughter_object = daughter_it->Next();
        TGeoNode* daughter_node = dynamic_cast<TGeoNode*>( daughter_object );

        TGeoVolume* daughter_volume = daughter_node->GetVolume();

        if( daughter_volume->Contains( position ) )
        {
          location = POINT_OUTSIDE_CELL;

          break;
        }
      }
    }
  }
  else
    location = POINT_OUTSIDE_CELL;

  return location;
}

// Get the surface normal at a point on the surface
/*! \details The surface id will not be used. The dot product of the normal
 * and the direction will be positive defined.
 */
void RootNavigator::getSurfaceNormal(
                          const ModuleTraits::InternalSurfaceHandle,
                          const double position[3],
                          const double direction[3],
                          double normal[3] ) const
{
  TGeoNode* node = this->findNodeContainingRay( position, direction );
  
  // Note: This is basically a reimplementation of the
  // TGeoNavigator::GetNormalFast method. Because we want to preserve our
  // internal ray state this reimplementation is necessary
  double local_position[3];
  node->MasterToLocal( position, local_position );
  
  double local_direction[3];
  node->MasterToLocal( direction, local_direction );

  double local_normal[3];

  node->GetVolume()->GetShape()->ComputeNormal( local_position,
                                                local_direction,
                                                local_normal );

  node->LocalToMaster( local_normal, normal );

  // Make sure that the normal is a unit vector
  if( !Utility::isUnitVector( normal ) )
    Utility::normalizeVector( normal );
}

// Find the cell that contains a given ray
/*! \details The cache will not be used to speed up the search. The Root
 * geometry must be traversed in order to find the correct cell when the
 * ray lies on a cell boundary.
 */
ModuleTraits::InternalCellHandle RootNavigator::findCellContainingRay(
                                            const double position[3],
                                            const double direction[3],
                                            CellIdSet& found_cell_cache ) const
{
  ModuleTraits::InternalCellHandle found_cell =
    this->findCellContainingRay( position, direction );

  // Add the new cell to the cache
  found_cell_cache.insert( found_cell );

  return found_cell;
}

// Find the cell that contains the ray
ModuleTraits::InternalCellHandle RootNavigator::findCellContainingRay(
                                              const double position[3],
                                              const double direction[3] ) const
{
  return this->findNodeContainingRay( position, direction )->GetVolume()->GetUniqueID();
}

// Find the node containing the ray
// Note: The internal ray will have to be modified during the execution
//       of this method. However, it's initial state will be restored, which
//       will make it appear as if it hasn't been changed. That is why this
//       this method is const.
TGeoNode* RootNavigator::findNodeContainingRay(
                                              const double position[3],
                                              const double direction[3] ) const
{
  // Cache the navigator's state
  double cached_position[3];
  double cached_direction[3];

  if( this->isInternalRaySet() )
  {
    RootNavigator::deepCopy( cached_position, d_navigator->GetCurrentPoint() );
    RootNavigator::deepCopy( cached_direction,
                             d_navigator->GetCurrentDirection() );
  }

  // Set the temporary state
  TGeoNode* current_node = d_navigator->InitTrack( position, direction );

  TGeoNode* boundary_node = d_navigator->FindNextBoundary();

  double step_size = d_navigator->GetStep();

  TGeoNode* node_containing_point;

  // If the point is within the boundary tolerance return the next node
  if( step_size < s_tol )
  {
    node_containing_point = d_navigator->Step();

    // Update the step size
    d_navigator->FindNextBoundary();
    step_size = d_navigator->GetStep();
  }
  else
    node_containing_point = current_node;

  // Make sure the node is valid
  TEST_FOR_EXCEPTION( node_containing_point == NULL,
                      std::runtime_error,
                      "Could not find the node that contains the ray! "
                      "Here are the details...\n"
                      "  Position: "
                      << this->arrayToString( position ) << "\n"
                      "  Direction: "
                      << this->arrayToString( direction ) );

  // Reset the navigator state
  if( this->isInternalRaySet() )
  {
    d_navigator->InitTrack( cached_position, cached_direction );
    d_navigator->FindNextBoundary();
  }

  return node_containing_point;
}

// Check if the internal ray is set
bool RootNavigator::isInternalRaySet() const
{
  return d_internal_ray_set;
}

// Set the internal ray set flag
void RootNavigator::internalRaySet()
{
  d_internal_ray_set = true;
}

// Initialize (or reset) an internal Root ray
void RootNavigator::setInternalRay( const double x_position,
                                    const double y_position,
                                    const double z_position,
                                    const double x_direction,
                                    const double y_direction,
                                    const double z_direction )
{
  // Make sure that the direction is valid
  testPrecondition( Utility::isUnitVector( x_direction, y_direction, z_direction ) );

  // The internal ray is set now
  this->internalRaySet();

  d_navigator->InitTrack( x_position, y_position, z_position,
                          x_direction, y_direction, z_direction );
}
                      
                       
// Initialize (or reset) an internal Root ray
/*! \details Root will not use the cell to speed up its lookup.
 */
void RootNavigator::setInternalRay(
                          const double x_position,
                          const double y_position,
                          const double z_position,
                          const double x_direction,
                          const double y_direction,
                          const double z_direction,
                          const ModuleTraits::InternalCellHandle )
{
  this->setInternalRay( x_position, y_position, z_position,
                        x_direction, y_direction, z_direction );
}

// Get the internal Root ray position
const double* RootNavigator::getInternalRayPosition() const
{
  // Make sure that the internal ray is set
  testPrecondition( this->isInternalRaySet() );

  return d_navigator->GetCurrentPoint();
}

// Get the internal Root ray direction
const double* RootNavigator::getInternalRayDirection() const
{
  // Make sure that the internal ray is set
  testPrecondition( this->isInternalRaySet() );

  return d_navigator->GetCurrentDirection();
}

// Get the cell containing the internal Root ray position
ModuleTraits::InternalCellHandle RootNavigator::getCellContainingInternalRay() const
{
  // Make sure that the internal ray is set
  testPrecondition( this->isInternalRaySet() );

  return d_navigator->GetCurrentVolume()->GetUniqueID();
}

// Get the distance from the internal Root ray pos. to the nearest boundary
/*! \details The distance to the nearest boundary will be returned. Surfaces
 * aren't managed separately in Root (they are simply part of the cell
 * definition). Therefore the surface hit will always be invalid.
 */
double RootNavigator::fireInternalRay(
                             ModuleTraits::InternalSurfaceHandle* surface_hit )
{
  // Make sure that the internal ray is set
  testPrecondition( this->isInternalRaySet() );

  TGeoNode* boundary_node = d_navigator->FindNextBoundary();

  if( surface_hit != NULL )
    *surface_hit = ModuleTraits::invalid_internal_surface_handle;

  return d_navigator->GetStep();
}

// Advance the internal Root ray to the next boundary
/*! \details Reflecting surfaces cannot be set in Root geometries so this
 * method will always return false.
 */
bool RootNavigator::advanceInternalRayToCellBoundary( double* surface_normal )
{
  // Make sure that the internal ray is set
  testPrecondition( this->isInternalRaySet() );
  
  TGeoNode* next_node = d_navigator->Step();

  // Compute the surface normal at the boundary
  if( surface_normal != NULL )
    this->deepCopy( surface_normal, d_navigator->FindNormal() );

  return false;
}

// Advance the internal Root ray a substep
void RootNavigator::advanceInternalRayBySubstep( const double substep_distance )
{
  // Make sure that the internal ray is set
  testPrecondition( this->isInternalRaySet() );
  // Make sure that the substep distance is valid
  testPrecondition( substep_distance > 0.0 );
  testPrecondition( substep_distance < d_navigator->GetStep() );

  // Set the step size
  d_navigator->SetStep( substep_distance );

  // Advance the root ray
  d_navigator->Step();

  // Update the ray data
  Navigator::fireInternalRay();
}

// Change the internal ray direction (without changing its location)
void RootNavigator::changeInternalRayDirection( const double x_direction,
                                                const double y_direction,
                                                const double z_direction )
{
  // Make sure that the internal ray is set
  testPrecondition( this->isInternalRaySet() );
  // Make sure that the direction is valid
  testPrecondition( Utility::isUnitVector( x_direction, y_direction, z_direction ) );

  d_navigator->SetCurrentDirection( x_direction, y_direction, z_direction );
}

// Clone the navigator
RootNavigator* RootNavigator::clone() const
{
  // Copy the geometry data
  RootNavigator* clone = new RootNavigator( d_root_model );

  // Copy the position, direction and cell
  dynamic_cast<Navigator*>( clone )->setInternalRay(
                                        this->getInternalRayPosition(),
                                        this->getInternalRayDirection(),
                                        this->getCellContainingInternalRay() );
  return clone;
}

// Create internal ray
TGeoNavigator* RootNavigator::createInternalRay( TGeoManager* manager )
{
  return manager->AddNavigator();
}

// Free internal ray
void RootNavigator::freeInternalRay()
{
  if( d_navigator )
  {
    d_root_model->getManager()->RemoveNavigator( d_navigator );
  
    d_navigator = NULL;
  }
}

// Save the model to an archive
template<typename Archive>
void RootNavigator::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( Navigator );

  // Save the local data
  ar & BOOST_SERIALIZATION_NVP( d_root_model );
  ar & BOOST_SERIALIZATION_NVP( d_internal_ray_set );

  if( d_internal_ray_set )
  {
    ModuleTraits::InternalCellHandle current_cell =
      this->getCellContainingInternalRay();

    ar & BOOST_SERIALIZATION_NVP( current_cell );
    ar & boost::serialization::make_nvp( "current_position", boost::serialization::make_array<double>( const_cast<double*>(this->getInternalRayPosition()), 3 ) );
    ar & boost::serialization::make_nvp( "current_direction", boost::serialization::make_array<double>( const_cast<double*>(this->getInternalRayDirection()), 3 ) );
  }
}

// Load the model from an archive
template<typename Archive>
void RootNavigator::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( Navigator );

  // Load the local data
  ar & BOOST_SERIALIZATION_NVP( d_root_model );
  ar & BOOST_SERIALIZATION_NVP( d_internal_ray_set );

  // Create a new internal ray
  if( d_navigator )
    this->freeInternalRay();

  d_navigator = this->createInternalRay( d_root_model->getManager() );

  // Set the internal ray state (if one was archived)
  if( d_internal_ray_set )
  {
    ModuleTraits::InternalCellHandle current_cell;
    double current_position[3];
    double current_direction[3];
    
    ar & BOOST_SERIALIZATION_NVP( current_cell );
    ar & boost::serialization::make_nvp( "current_position", boost::serialization::make_array<double>( current_position, 3 ) );
    ar & boost::serialization::make_nvp( "current_direction", boost::serialization::make_array<double>( current_direction, 3 ) );
    
    dynamic_cast<Navigator*>(this)->setInternalRay( current_position, current_direction, current_cell );
  }
}

EXPLICIT_GEOMETRY_CLASS_SAVE_LOAD_INST( RootNavigator );
  
} // end Geometry namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( RootNavigator, Geometry );

//---------------------------------------------------------------------------//
// end Geometry_RootNavigator.cpp
//---------------------------------------------------------------------------//
