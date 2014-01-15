//---------------------------------------------------------------------------//
//!
//! \file   GeometryHandlerTraits.hpp
//! \author Alex Robinson
//! \brief  Geometry handler traits class specializations
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_HANDLER_TRAITS_HPP
#define GEOMETRY_HANDLER_TRAITS_HPP

// Std Lib Includes
#include <set>

// MOAB Includes
#include <DagMC.hpp>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>
#include <Teuchos_OrdinalTraits.hpp>

// FACEMC Includes
#include "GeometryHandlerTraitsDecl.hpp"
#include "MOABException.hpp"
#include "ExceptionTestMacros.hpp"
#include "ContractException.hpp"

namespace FACEMC{

namespace Traits{

/*! The specialization of the GeometryHandlerTraits struct for the DagMC geometry 
 * handler.
 * \ingroup geometry_traits
 */
template<>
struct GeometryHandlerTraits<moab::DagMC>
{
 
  //! The DagMC class pointer
  typedef moab::DagMC* GeometryHandlerPtr;
  //! The surface handle class (used to reference a surface)
  typedef moab::EntityHandle SurfaceHandle;
  //! The cell handle class (used to reference a surface)
  typedef moab::EntityHandle CellHandle;
  
private:

  // Typedef for CellHandle ordinal traits
  typedef Teuchos::OrdinalTraits<CellHandle> CellHandleOT;
  
  // Store a list of cells that have been previously found to contain points.
  // This list is appended every time the getCellContainingPoint function is
  // called.
  static std::set<CellHandle> cells_containing_test_points;

  // Store the collection of all cells in the geometry
  static moab::Range all_cells;

  // Store a DagMC::RayHistory for ray tracing
  static moab::DagMC::RayHistory ray_history;

public:

  //! Get an instance of DagMC (singleton pattern)
  static inline GeometryHandlerPtr getInstance()
  { return moab::DagMC::instance(); }

  //! Fire a ray through the geometry
  static inline void fireRay( moab::DagMC& geometry_handler,
			      const CellHandle& cell,
			      const double ray_start_position[3],
			      const double ray_direction[3],
			      SurfaceHandle& surface_hit,
			      double& distance_to_surface_hit )
  {
    moab::ErrorCode return_value = 
      geometry_handler.ray_fire( 
			    cell,
			    ray_start_position,
			    ray_direction,
			    surface_hit,
			    distance_to_surface_hit,
			    &GeometryHandlerTraits<moab::DagMC>::ray_history );

    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS, 
			FACEMC::MOABException,
			moab::ErrorCodeStr[return_value] );
  }

  //! Fire a ray through the geometry
  static inline void fireRay( moab::DagMC& geometry_handler,
			      const ParticleState<CellHandle>& particle,
			      SurfaceHandle& surface_hit,
			      double& distance_to_surface_hit )
  {
    GeometryHandlerTraits<moab::DagMC>::fireRay( geometry_handler,
						 particle.getCell(),
						 particle.getPosition(),
						 particle.getDirection(),
						 surface_hit,
						 distance_to_surface_hit );
  }

  //! Indicate that a new ray will be started (after a collision)
  static inline void newRay()
  {
    GeometrYHandlerTraits<moab::DagMC>::ray_history.reset();
  }

  //! Get the cell that contains a given point
  static inline CellHandle getCellContainingPoint(
					     moab::DagMC& geometry_handler,
					     const double point[3],
					     const double* direction = NULL )
  {
    if( GeometryHandlerTraits<moab::DagMC>::all_cells.empty() )
    {
      moab::Interface* moab_instance = geometry_handler.moab_instance();

      const int three = 3;
      const void* const three_val[] = {&three};
      
      moab::Tag geom_tag = geometry_handler.geom_tag();

      moab::ErrorCode return_value = 
	moab_instance->get_entities_by_type_and_tag( 
			       0, 
			       moab::MBENTITYSET,
			       &geom_tag,
			       three_val,
			       1,
			       GeometryHandlerTraits<moab::DagMC>::all_cells );

      TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
			  FACEMC::MOABException,
			  moab::ErrorCodeStr[return_value] );
    }

    CellHandle cell_containing_point = CellHandleOT::invalid();
    
    // Try using the cells that have been found to contain previously tested
    // points first.
    {
      std::set<CellHandle>::const_iterator cell_handle = 
	GeometryHandlerTraits<moab::DagMC>::cells_containing_test_points.begin();
      
      std::set<CellHandle>::const_iterator end_cell_handle = 
	GeometryHandlerTraits<moab::DagMC>::cells_containing_test_points.end();
      
      while( cell_handle != end_cell_handle )
      {
	PointLocation test_point_location = 
	  GeometryHandlerTraits<moab::DagMC>::getPointLocation( 
			    geometry_handler,
			    *cell_handle,
			    point,
			    direction,
			    &GeometryHandlerTraits<moab::DagMC>::ray_history );
	
	if( PointLocation == POINT_INSIDE_CELL )
	{
	  cell_containing_point = *cell_handle;
	  
	  break;
	}
	else
	  ++cell_handle;
      }
    }

    // Try all remaining cells
    if( cell_handle == CellHandleOT::invalid() )
    {
      moab::Range::const_iterator cell_handle = 
	GeometryHandlerTraits<moab::DagMC>::all_cells.begin();

      moab::Range::const_iterator end_cell_handle = 
	GeometryHandlerTraits<moab::DagMC>::all_cells.end();

      while( cell_handle != end_cell_handle )
      {
	PointLocation test_point_location = 
	  GeometryHandlerTraits<moab::DagMC>::getPointLocation( 
			    geometry_handler,
			    *cell_handle,
			    point,
			    direction,
			    &GeometryHandlerTraits<moab::DagMC>::ray_history );
	
	if( PointLocation == POINT_INSIDE_CELL )
	{
	  cell_containing_point = *cell_handle;

	  // Add the cell to the set of cells found to contain test points
	  cells_containing_test_points.insert( *cell_handle );
	  
	  // Remove the entity handle from the remaining cells container so 
	  // that it is not checked twice in the future.
	  GeometryHandlerTraits<moab::DagMC>::all_cells.erase( 
						       cell_containing_point );
	  
	  break;
	}
	else
	  ++cell_handle;
      }
    }

    // Test if the particle is lost
    TEST_FOR_EXCEPTION( cell_handle == CellHandleOT::invalid(),
			FACEMC::MOABException,
			moab::ErrorCodeStr[4] );

    return cell_handle;
  }

  //! Get the point location w.r.t. a given cell
  static inline PointLocation getPointLocation(
				             moab::DagMC& geometry_handler,
					     const CellHandle& cell,
					     const double point[3],
					     const double* direction = NULL )
  {
    int test_result;
    moab::ErrorCode return_value = 
      geometry_handler.point_in_volume( 
			    cell,
			    point,
			    test_result,
			    direction,
			    &GeometryHandlerTraits<moab::DagMC>::ray_history );
    
    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
			FACEMC::MOABException,
			moab::ErrorCodeStr[return_value] );

    PointLocation point_location;

    switch( test_result )
    {
    case -1: 
      point_location = POINT_ON_CELL;
      break;
    case 0:
      point_location = POINT_OUTSIDE_CELL;
      break;
    case 1:
      point_location = POINT_INSIDE_CELL;
      break;
    }

    return point_location;
  }

  //! Get the cell on the other side of a surface
  static inline CellHandle getNextCell( moab::DagMC& geometry_handler,
					const SurfaceHandle& surface,
					const CellHandle& current_cell,
					const double* point = NULL )
  {
    CellHandle next_cell;
    
    moab::ErrorCode return_value = 
      geometry_handler.next_vol( surface, 
				 current_cell,
				 next_cell );

    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
			FACEMC::MOABException,
			moab::ErrorCodeStr[return_value] );

    return next_cell;
  }

  //! Update the cell that contains a given particle (start of history)
  static inline void updateCellContainingParticle( 
					  moab::DagMC& geometry_handler,
					  ParticleState<CellHandle>& particle )
  {
    CellHandle new_cell = 
      GeometryHandlerTraits<moab::DagMC>::getCellContainingPoint(
						     geometry_handler,
						     particle.getPosition(),
						     particle.getDirection() );

    particle.setCell( new_cell );
  }
						  
  //! Update the cell that contains a given particle (surface crossing)
  static inline void updateCellContainingParticle(
				          moab::DagMC& geometry_handler,
					  const SurfaceHandle& surface,
				          ParticleState<CellHandle>& particle )
  {
    CellHandle new_cell = 
      GeometryHandlerTraits<moab::DagMC>::getNextCell( geometry_handler,
						       surface,
						       particle.cell() );

    particle.setCell( new_cell );
  }

  //! Check if the cell is a termination cell
  static inline bool isTerminationCell( moab::DagMC& geometry_handler,
					const CellHandle& cell )
  {
    return geometry_handler.has_prop( cell, "termination_cell" );
  }

  //! Get the volume of a cell
  static inline double getCellVolume( moab::DagMC& geometry_handler,
				      const CellHandle& cell )
  {
    double volume = 0.0;
    
    moab::ErrorCode return_value = 
      geometry_handler.measure_volume( cell, volume );

    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
			FACEMC::MOABException,
			moab::ErrorCodeStr[return_value] );

    // Make sure that the calculated volume is valid
    testPostcondition( !Teuchos::ScalarTraits<double>::isNanInf( volume ) );
    testPostcondition( volume > 0.0 );
  
    return volume;
  }

  //! Get the surface area of a surface bounding a cell
  static inline double getCellSurfaceArea( moab::DagMC& geometry_handler,
					   const CellHandle& cell,
					   const SurfaceHandle& surface )
  {
    double area = 0.0;

    moab::ErrorCode return_value = 
      geometry_handler.measure_area( surface, area );

    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
			FACEMC::MOABException,
			moab::ErrorCodeStr[return_value] );

    // Make sure that the calculated area is valid
    testPostcondition( !Teuchos::ScalarTraits<double>::isNanInf( area ) );
    testPostcondition( area > 0.0 );

    return area;
  }  

  //! Get the surface normal at a point on the surface
  static inline void getSurfaceNormal( moab::DagMC& geometry_handler,
				       const SurfaceHandle& surface,
				       const double point[3],
				       double angle[3] )
  {
    moab::ErrorCode return_value =
      geometry_handler.get_angle( surface, 
				  point, 
				  angle, 
				  &GeometryTraits<moab::DagMC>::ray_history );

    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
			FACEMC::MOABException,
			moab::ErrorCodeStr[return_value] );
  }
};

// Initialize the static member data for the GeometryHandlerTraits<moab::DagMC>
// specialization.
std::set<CellHandle> GeometryHandlerTraits<moab::DagMC>::cells_containing_test_points();

moab::Range GeometryHandlerTraits<moab::DagMC>::all_cells();

moab::DagMC::RayHistory GeometryHandlerTraits<moab::DagMC>::ray_history();

} // end Traits namespace

} // end FACEMC namespace

#endif // end GEOMETRY_TRAITS_HPP

//---------------------------------------------------------------------------//
// end GeometryHandlerTraits.hpp
//---------------------------------------------------------------------------//
