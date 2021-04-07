//---------------------------------------------------------------------------//
//!
//! \file   Geometry_RootNavigator.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  The Root navigator class declaration
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Geometry_RootNavigator.hpp"
#include "Geometry_RootModel.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_OpenMPProperties.hpp"
#include "Utility_DesignByContract.hpp"

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
RootNavigator::RootNavigator(
          const std::shared_ptr<const RootModel>& root_model,
          const Navigator::AdvanceCompleteCallback& advance_complete_callback )
  : Navigator( advance_complete_callback ),
    d_root_model( root_model ),
    d_internal_ray_set( false ),
    d_navigator( RootNavigator::createInternalRay( d_root_model->getManager() ) )
{ /* ... */ }

// Copy constructor
RootNavigator::RootNavigator( const RootNavigator& other )
  : Navigator( other ),
    d_root_model( other.d_root_model ),
    d_internal_ray_set( other.d_internal_ray_set ),
    d_navigator( RootNavigator::createInternalRay( d_root_model->getManager() ) )
{
  if( other.d_internal_ray_set )
  {
    this->setState( other.getPosition(),
                    other.getDirection(),
                    other.getCurrentCell() );
  }
}

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
                                       const Length position[3],
                                       const double*,
                                       const EntityId cell_id ) const
{
  TGeoVolume* cell = d_root_model->getVolumePtr( cell_id );

  PointLocation location;

  if( cell->Contains( Utility::reinterpretAsRaw(position) ) )
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

        if( daughter_volume->Contains( Utility::reinterpretAsRaw(position) ) )
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
void RootNavigator::getSurfaceNormal( const EntityId,
                                      const Length position[3],
                                      const double direction[3],
                                      double normal[3] ) const
{
  TGeoNode* node = this->findNodeContainingRay( position, direction );

  // Note: This is basically a re-implementation of the
  // TGeoNavigator::GetNormalFast method but because we want to preserve our
  // internal ray state this re-implementation is necessary
  double local_position[3];
  node->MasterToLocal( Utility::reinterpretAsRaw(position), local_position );

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
auto RootNavigator::findCellContainingRay(
                      const Length position[3],
                      const double direction[3],
                      CellIdSet& found_cell_cache ) const -> EntityId
{
  EntityId found_cell =
    this->findCellContainingRay( position, direction );

  // Add the new cell to the cache
  found_cell_cache.insert( found_cell );

  return found_cell;
}

// Find the cell that contains the ray
auto RootNavigator::findCellContainingRay(
                        const Length position[3],
                        const double direction[3] ) const -> EntityId
{
  return this->findNodeContainingRay( position, direction )->GetVolume()->GetUniqueID();
}

// Find the node containing the ray
// Note: The internal ray will have to be modified during the execution
//       of this method. However, it's initial state will be restored, which
//       will make it appear as if it hasn't been changed. That is why this
//       this method is const.
TGeoNode* RootNavigator::findNodeContainingRay(
                                              const Length position[3],
                                              const double direction[3] ) const
{
  // Cache the navigator's state
  double cached_position[3];
  double cached_direction[3];

  if( this->isStateSet() )
  {
    RootNavigator::deepCopy( cached_position, d_navigator->GetCurrentPoint() );
    RootNavigator::deepCopy( cached_direction,
                             d_navigator->GetCurrentDirection() );
  }

  // Set the temporary state
  TGeoNode* current_node =
    d_navigator->InitTrack( Utility::reinterpretAsRaw(position), direction );

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
                      RootGeometryError,
                      "Could not find the node that contains the ray! "
                      "Here are the details...\n"
                      "  Position: "
                      << this->arrayToString( position ) << "\n"
                      "  Direction: "
                      << this->arrayToString( direction ) );

  // Reset the navigator state
  if( this->isStateSet() )
  {
    d_navigator->InitTrack( cached_position, cached_direction );
    d_navigator->FindNextBoundary();
  }

  return node_containing_point;
}

// Check if the internal ray is set
bool RootNavigator::isStateSet() const
{
  return d_internal_ray_set;
}

// Set the internal ray set flag
void RootNavigator::stateSet()
{
  d_internal_ray_set = true;
}

// Initialize (or reset) an internal Root ray
void RootNavigator::setState( const Length x_position,
                              const Length y_position,
                              const Length z_position,
                              const double x_direction,
                              const double y_direction,
                              const double z_direction )
{
  // Make sure that the direction is valid
  testPrecondition( Utility::isUnitVector( x_direction, y_direction, z_direction ) );

  // The internal ray is set now
  this->stateSet();

  d_navigator->InitTrack( x_position.value(),
                          y_position.value(),
                          z_position.value(),
                          x_direction,
                          y_direction,
                          z_direction );
}


// Initialize (or reset) an internal Root ray
/*! \details Root will not use the cell to speed up its lookup.
 */
void RootNavigator::setState( const Length x_position,
                              const Length y_position,
                              const Length z_position,
                              const double x_direction,
                              const double y_direction,
                              const double z_direction,
                              const EntityId )
{
  this->setState( x_position, y_position, z_position,
                  x_direction, y_direction, z_direction );
}

// Get the internal Root ray position
auto RootNavigator::getPosition() const -> const Length*
{
  // Make sure that the internal ray is set
  testPrecondition( this->isStateSet() );

  return Utility::reinterpretAsQuantity<Length>(d_navigator->GetCurrentPoint());
}

// Get the internal Root ray direction
const double* RootNavigator::getDirection() const
{
  // Make sure that the internal ray is set
  testPrecondition( this->isStateSet() );

  return d_navigator->GetCurrentDirection();
}

// Get the cell containing the internal Root ray position
auto RootNavigator::getCurrentCell() const -> EntityId
{
  // Make sure that the internal ray is set
  testPrecondition( this->isStateSet() );

  return d_navigator->GetCurrentVolume()->GetUniqueID();
}

// Get the distance from the internal Root ray pos. to the nearest boundary in all directions
auto RootNavigator::getDistanceToClosestBoundary() -> Length
{
  // Make sure that the internal ray is set
  testPrecondition( this->isStateSet() );

  return Length::from_value( d_navigator->Safety() );
}

// Get the distance from the internal Root ray pos. to the nearest boundary
/*! \details The distance to the nearest boundary will be returned. Surfaces
 * aren't managed separately in Root (they are simply part of the cell
 * definition). Therefore the surface hit will always be invalid.
 */
auto RootNavigator::fireRay( EntityId* surface_hit ) -> Length
{
  // Make sure that the internal ray is set
  testPrecondition( this->isStateSet() );

  TGeoNode* boundary_node = d_navigator->FindNextBoundary();

  if( surface_hit != NULL )
    *surface_hit = Navigator::invalidSurfaceId();

  return Length::from_value( d_navigator->GetStep() );
}

// Advance the internal Root ray to the next boundary
/*! \details Reflecting surfaces cannot be set in Root geometries so this
 * method will always return false.
 */
bool RootNavigator::advanceToCellBoundaryImpl( double* surface_normal,
                                               Length& distance_traveled )
{
  // Make sure that the internal ray is set
  testPrecondition( this->isStateSet() );

  Utility::setQuantity( distance_traveled, d_navigator->GetStep() );

  TGeoNode* next_node = d_navigator->Step();

  // Compute the surface normal at the boundary
  if( surface_normal != NULL )
    this->deepCopy( surface_normal, d_navigator->FindNormal() );

  return false;
}

// Advance the internal Root ray a substep
void RootNavigator::advanceBySubstepImpl( const Length substep_distance )
{
  // Make sure that the internal ray is set
  testPrecondition( this->isStateSet() );
  // Make sure that the substep distance is valid
  testPrecondition( substep_distance.value() > 0.0 );
  testPrecondition( substep_distance.value() < d_navigator->GetStep() );

  // Set the step size
  d_navigator->SetStep( substep_distance.value() );

  // Advance the root ray
  d_navigator->Step();

  // Update the ray data
  Navigator::fireRay();
}

// Change the internal ray direction (without changing its location)
void RootNavigator::changeDirection( const double x_direction,
                                     const double y_direction,
                                     const double z_direction )
{
  // Make sure that the internal ray is set
  testPrecondition( this->isStateSet() );
  // Make sure that the direction is valid
  testPrecondition( Utility::isUnitVector( x_direction, y_direction, z_direction ) );

  d_navigator->SetCurrentDirection( x_direction, y_direction, z_direction );
}

// Clone the navigator
RootNavigator* RootNavigator::clone( const AdvanceCompleteCallback& advance_complete_callback ) const
{
  // Copy the geometry data
  RootNavigator* clone = new RootNavigator( d_root_model,
                                            advance_complete_callback );

  // Copy the position, direction and cell
  clone->setState( this->getPosition(),
                   this->getDirection(),
                   this->getCurrentCell() );
  return clone;
}

// Clone the navigator
RootNavigator* RootNavigator::clone() const
{
  return new RootNavigator( *this );
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

// // Save the model to an archive
// template<typename Archive>
// void RootNavigator::save( Archive& ar, const unsigned version ) const
// {
//   // Save the base class first
//   ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( Navigator );

//   // Save the local data
//   ar & BOOST_SERIALIZATION_NVP( d_root_model );
//   ar & BOOST_SERIALIZATION_NVP( d_internal_ray_set );

//   if( d_internal_ray_set )
//   {
//     EntityId current_cell = this->getCurrentCell();

//     ar & BOOST_SERIALIZATION_NVP( current_cell );
//     ar & boost::serialization::make_nvp( "current_position", boost::serialization::make_array<double>( const_cast<double*>(d_navigator->GetCurrentPoint()), 3 ) );
//     ar & boost::serialization::make_nvp( "current_direction", boost::serialization::make_array<double>( const_cast<double*>(this->getDirection()), 3 ) );
//   }
// }

// // Load the model from an archive
// template<typename Archive>
// void RootNavigator::load( Archive& ar, const unsigned version )
// {
//   // Load the base class first
//   ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( Navigator );

//   // Load the local data
//   ar & BOOST_SERIALIZATION_NVP( d_root_model );
//   ar & BOOST_SERIALIZATION_NVP( d_internal_ray_set );

//   // Create a new internal ray
//   if( d_navigator )
//     this->freeInternalRay();

//   d_navigator = this->createInternalRay( d_root_model->getManager() );

//   // Set the internal ray state (if one was archived)
//   if( d_internal_ray_set )
//   {
//     EntityId current_cell;
//     Length current_position[3];
//     double current_direction[3];

//     ar & BOOST_SERIALIZATION_NVP( current_cell );
//     ar & boost::serialization::make_nvp( "current_position", boost::serialization::make_array<double>( Utility::reinterpretAsRaw(current_position), 3 ) );
//     ar & boost::serialization::make_nvp( "current_direction", boost::serialization::make_array<double>( current_direction, 3 ) );

//     dynamic_cast<Navigator*>(this)->setState( current_position, current_direction, current_cell );
//   }
// }

} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_RootNavigator.cpp
//---------------------------------------------------------------------------//
