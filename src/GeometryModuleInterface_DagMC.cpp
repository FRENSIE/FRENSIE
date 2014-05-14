//---------------------------------------------------------------------------//
//!
//! \file   GeometryModuleInterface_DagMC.cpp
//! \author Alex Robinson
//! \brief  DagMC specialization def. of the GeometryModuleInterface class
//!
//---------------------------------------------------------------------------//

// FACEMC Includes
#include "GeometryModuleInterface_DagMC.hpp"

namespace FACEMC{

// Initialize the DagMC geometry module interface static member data
const GeometryModuleInterface<moab::DagMC>::ExternalSurfaceHandle
GeometryModuleInterface<moab::DagMC>::invalid_external_surface_handle = 
  std::numeric_limits<ExternalSurfaceHandle>::max();

const GeometryModuleInterface<moab::DagMC>::ExternalCellHandle
GeometryModuleInterface<moab::DagMC>::invalid_external_cell_handle =
  std::numeric_limits<ExternalCellHandle>::max();

moab::DagMC* const GeometryModuleInterface<moab::DagMC>::dagmc_instance = 
  moab::DagMC::instance();

const std::string 
GeometryModuleInterface<moab::DagMC>::termination_cell_property_name = 
  "graveyard";

boost::unordered_set<GeometryModuleInterface<moab::DagMC>::ExternalCellHandle>
GeometryModuleInterface<moab::DagMC>::cells_containing_test_points;

moab::Range GeometryModuleInterface<moab::DagMC>::all_cells;

moab::DagMC::RayHistory GeometryModuleInterface<moab::DagMC>::ray_history;

// Find the cell that contains a given point (start of history)
/*! \details This function should be called after a ray is generated. It
 * is used to find the starting cell of a ray, which must be done before
 * ray tracing may begin. If no cell can be found, a FACEMC::MOABException will
 * be thrown. This exception should be caught to end the tracing of this ray.
 */
GeometryModuleInterface<moab::DagMC>::InternalCellHandle 
GeometryModuleInterface<moab::DagMC>::findCellContainingPoint( 
						      const Ray& ray )
{
  // Reset the RayHistory
  GeometryModuleInterface<moab::DagMC>::newRay();

  if( GeometryModuleInterface<moab::DagMC>::all_cells.empty() )
    GeometryModuleInterface<moab::DagMC>::getAllCells();

  InternalCellHandle cell_containing_point = 
    Traits::ModuleTraits::invalid_internal_cell_handle;

  // Try using the cells found to contain previously tested particles first
  GeometryModuleInterface<moab::DagMC>::testCellsContainingTestPoints(
						         cell_containing_point,
							 ray );

  // Try all remaining cells if necessary
  if( cell_containing_point ==
      Traits::ModuleTraits::invalid_internal_cell_handle )
  {
    GeometryModuleInterface<moab::DagMC>::testAllRemainingCells(
							 cell_containing_point,
							 ray );
  }

  // Test if the ray is lost
  TEST_FOR_EXCEPTION( 
	    cell_containing_point ==
	    Traits::ModuleTraits::invalid_internal_cell_handle,
	    FACEMC::MOABException,
	    moab::ErrorCodeStr[4] );

  return cell_containing_point;
}

// Find the cell that contains a given point (surface crossing)
/*! \details This function should be called after a ray has intersected a
 * surface. It is used to find the cell on the other side of the surface (at
 * the point of intersection). If no cell can be found, a FACEMC::MOABException
 * will be thrown. This exception should be caught and a lost particle should 
 *be indicated.
 */
GeometryModuleInterface<moab::DagMC>::InternalCellHandle 
GeometryModuleInterface<moab::DagMC>::findCellContainingPoint( 
					 const Ray& ray,
					 const InternalCellHandle current_cell,
					 const InternalSurfaceHandle surface )
{
  ExternalSurfaceHandle surface_external = 
    GeometryModuleInterface<moab::DagMC>::getExternalSurfaceHandle( surface );

  ExternalCellHandle current_cell_external = 
    GeometryModuleInterface<moab::DagMC>::getExternalCellHandle( current_cell);

  ExternalCellHandle next_cell_external;

  moab::ErrorCode return_value = 
    GeometryModuleInterface<moab::DagMC>::dagmc_instance->next_vol(
							 surface_external,
							 current_cell_external,
							 next_cell_external );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
		      FACEMC::MOABException,
		      moab::ErrorCodeStr[return_value] );

  return GeometryModuleInterface<moab::DagMC>::getInternalCellHandle( 
							  next_cell_external );
}

// Fire a ray through the geometry
/*! \details If for any reason the ray fire fails, a FACEMC::MOABException 
 * will be thrown. This exception should be caught to end the ray tracing.
 */
void GeometryModuleInterface<moab::DagMC>::fireRay( 
					const Ray& ray,
					const InternalCellHandle& current_cell,
					InternalSurfaceHandle& surface_hit,
					double& distance_to_surface_hit )
{
  ExternalCellHandle current_cell_external = 
    GeometryModuleInterface<moab::DagMC>::getExternalCellHandle( current_cell);

  ExternalSurfaceHandle surface_hit_external;
  
  moab::ErrorCode return_value = 
    GeometryModuleInterface<moab::DagMC>::dagmc_instance->ray_fire(
			  current_cell_external,
			  ray.getPosition(),
			  ray.getDirection(),
			  surface_hit_external,
			  distance_to_surface_hit,
			  &GeometryModuleInterface<moab::DagMC>::ray_history );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS, 
		      FACEMC::MOABException,
		      moab::ErrorCodeStr[return_value] );

  surface_hit = 
    GeometryModuleInterface<moab::DagMC>::getInternalSurfaceHandle( 
							surface_hit_external );
}

// Get the point location w.r.t. a given cell
/*! \details This function is used to determine if a point is in, on, or
 * outside a given cell. If a position relative to a cell cannot
 * be determined, a FACEMC::MOABException will be thrown. This exception 
 * should be caught so that ray tracing can be terminated.
 */
PointLocation GeometryModuleInterface<moab::DagMC>::getPointLocation(
						const Ray& ray,
						const InternalCellHandle cell )
{
  ExternalCellHandle cell_external = 
    GeometryModuleInterface<moab::DagMC>::getExternalCellHandle( cell );
    
  return GeometryModuleInterface<moab::DagMC>::getPointLocation(
							  cell_external,
							  ray.getPosition(),
							  ray.getDirection() );
}

// Get the point location w.r.t. a given cell (using an external handle)
PointLocation GeometryModuleInterface<moab::DagMC>::getPointLocation(
					const ExternalCellHandle cell_external,
					const double position[3],
					const double direction[3] )
{
  int test_result;
  
  moab::ErrorCode return_value = 
    GeometryModuleInterface<moab::DagMC>::dagmc_instance->point_in_volume(
			  cell_external,
			  position,
			  test_result,
			  direction,
			  &GeometryModuleInterface<moab::DagMC>::ray_history );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
		      FACEMC::MOABException,
		      moab::ErrorCodeStr[return_value] );

  switch( test_result )
  {
  case -1: 
    return POINT_ON_CELL;
  case 0:
    return POINT_OUTSIDE_CELL;
  case 1:
    return POINT_INSIDE_CELL;
  }
}

// Get all the cells contained in the geometry
void GeometryModuleInterface<moab::DagMC>::getAllCells()
{
  moab::Interface* moab_instance = 
    GeometryModuleInterface<moab::DagMC>::dagmc_instance->moab_instance();
  
  const int three = 3;
  const void* const three_val[] = {&three};
  
  moab::Tag geom_tag = 
    GeometryModuleInterface<moab::DagMC>::dagmc_instance->geom_tag();
  
  moab::ErrorCode return_value = 
    moab_instance->get_entities_by_type_and_tag( 
			     0, 
			     moab::MBENTITYSET,
			     &geom_tag,
			     three_val,
			     1,
			     GeometryModuleInterface<moab::DagMC>::all_cells );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
		      FACEMC::MOABException,
		      moab::ErrorCodeStr[return_value] );
}

// Test the cells found to contain test points for point containment
void GeometryModuleInterface<moab::DagMC>::testCellsContainingTestPoints( 
						      InternalCellHandle& cell,
						      const Ray& ray )
{
  boost::unordered_set<ExternalCellHandle>::const_iterator cell_handle = 
    GeometryModuleInterface<moab::DagMC>::cells_containing_test_points.begin();
    
  boost::unordered_set<ExternalCellHandle>::const_iterator end_cell_handle = 
    GeometryModuleInterface<moab::DagMC>::cells_containing_test_points.end();
    
  while( cell_handle != end_cell_handle )
  {
    PointLocation test_point_location = 
      GeometryModuleInterface<moab::DagMC>::getPointLocation( 
						          *cell_handle,
						          ray.getPosition(),
						          ray.getDirection() );
    
    if( test_point_location == POINT_INSIDE_CELL )
    {
      cell = GeometryModuleInterface<moab::DagMC>::getInternalCellHandle( 
								*cell_handle );
      
      break;
    }
    else
      ++cell_handle;
  }
}

// Test all remaining cells for point containment
void GeometryModuleInterface<moab::DagMC>::testAllRemainingCells( 
					              InternalCellHandle& cell,
						      const Ray& ray )
{
  moab::Range::const_iterator cell_handle = 
    GeometryModuleInterface<moab::DagMC>::all_cells.begin();
  
  moab::Range::const_iterator end_cell_handle = 
    GeometryModuleInterface<moab::DagMC>::all_cells.end();
  
  while( cell_handle != end_cell_handle )
  {
    PointLocation test_point_location = 
      GeometryModuleInterface<moab::DagMC>::getPointLocation( 
						          *cell_handle,
							  ray.getPosition(),
						          ray.getDirection() );
    
    if( test_point_location == POINT_INSIDE_CELL )
    {
      cell = GeometryModuleInterface<moab::DagMC>::getInternalCellHandle( 
								*cell_handle );
      
      // Add the cell to the set of cells found to contain test points
      GeometryModuleInterface<moab::DagMC>::cells_containing_test_points.insert( *cell_handle );
      
      // Remove the entity handle from the remaining cells container so 
      // that it is not checked twice in the future.
      GeometryModuleInterface<moab::DagMC>::all_cells.erase( *cell_handle );
	
      break;
    }
    else
      ++cell_handle;
  }
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end GeometryModuleInterface_DagMC.cpp
//---------------------------------------------------------------------------//
