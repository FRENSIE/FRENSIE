//---------------------------------------------------------------------------//
//!
//! \file   GeometryHandlerTraits_DagMC.hpp
//! \author Alex Robinson
//! \brief  DagMC specialization of the GeometryHandlerTraits class (decl.)
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_HANDLER_TRAITS_DAGMC_HPP
#define GEOMETRY_HANDLER_TRAITS_DAGMC_HPP

// Std Lib Includes
#include <set>
#include <limits>

// MOAB Includes
#include <DagMC.hpp>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FACEMC Includes
#include "GeometryHandlerTraitsDecl.hpp"

namespace FACEMC{

namespace Traits{

/*! The specialization of the GeometryHandlerTraits struct for the DagMC 
 * geometry handler.
 * \ingroup geometry_handler_traits
 */
template<>
struct GeometryHandlerTraits<moab::DagMC>
{
 
  //! The DagMC class pointer
  typedef moab::DagMC* GeometryHandlerPtr;
  //! The surface handle type (used to reference a surface)
  typedef moab::EntityHandle SurfaceHandle;
  //! The cell handle type (used to reference a surface)
  typedef moab::EntityHandle CellHandle;
  //! The surface id type
  typedef int SurfaceId;
  //! The cell id type
  typedef int CellId;
  
private:

  //! Typedef for Teuchos::ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! The value of an invalid cell handle
  static CellHandle invalidCellHandle();

  //! The value of an invalid surface handle
  static SurfaceHandle invalidSurfaceHandle();

  //! Get an instance of DagMC (singleton pattern)
  static GeometryHandlerPtr getHandler();
  
  //! Fire a ray through the geometry
  static void fireRay( const ParticleState<CellHandle>& particle,
		       SurfaceHandle& surface_hit,
		       double& distance_to_surface_hit );

  //! Indicate that a new ray will be started (after a collision)
  static void newRay();

  //! Update the cell that contains a given particle (start of history)
  static void updateCellContainingParticle( 
					 ParticleState<CellHandle>& particle );
						  
  //! Update the cell that contains a given particle (surface crossing)
  static void updateCellContainingParticle(
					 const SurfaceHandle& surface,
					 ParticleState<CellHandle>& particle );
  
  //! Check if the cell is a termination cell
  static bool isTerminationCell( const CellHandle& cell );
  
  //! Get the point location w.r.t. a given cell
  static PointLocation getParticleLocation(
				   const CellHandle& cell,
				   const ParticleState<CellHandle>& particle );
  
  //! Get the surface normal at a point on the surface
  static void getSurfaceNormal( const SurfaceHandle& surface,
				const ParticleState<CellHandle>& particle,
				double normal[3] );

  //! Get the volume of a cell
  static double getCellVolume( const CellHandle& cell );

  //! Get the surface area of a surface bounding a cell
  static double getCellSurfaceArea( const SurfaceHandle& surface,
				    const CellHandle& );

  //! Get the cell id corresponding to the cell handle
  static CellId getCellId( const CellHandle& cell );

  //! Get the cell handle corresponding to the cell id
  static CellHandle getCellHandle( const CellId& cell_id );

  //! Get the surface id corresponding to the surface handle
  static SurfaceId getSurfaceId( const SurfaceHandle& surface );

  //! Get the surface handle corresponding to the surface id
  static SurfaceHandle getSurfaceHandle( const SurfaceId& surface_id );

private:

  //! Get all the cells contained in the geometry
  static void getAllCells();

  //! Test the cells found to contain test points for point containment
  static void testCellsContainingTestPoints( 
				   CellHandle& cell,
				   const ParticleState<CellHandle>& particle );

  //! Test all remaining cells for point containment
  static void testAllRemainingCells(
				   CellHandle& cell,
				   const ParticleState<CellHandle>& particle );

  // An instance of DagMC
  static moab::DagMC* const dagmc_instance;

  // The termination cell property name
  static const std::string termination_cell_property_name;
  
  // Store a list of cells that have been previously found to contain points.
  // This list is appended every time the getCellContainingPoint function is
  // called.
  static std::set<CellHandle> cells_containing_test_points;

  // Store the collection of all cells in the geometry
  static moab::Range all_cells;

  // Store a DagMC::RayHistory for ray tracing
  static moab::DagMC::RayHistory ray_history;
};

//---------------------------------------------------------------------------//
// GeometryHandlerTraits<moab::DagMC> static member initialization.
//---------------------------------------------------------------------------//

// An instance of DagMC
moab::DagMC* const GeometryHandlerTraits<moab::DagMC>::dagmc_instance = 
  moab::DagMC::instance();

// The termination cell property name
const std::string 
GeometryHandlerTraits<moab::DagMC>::termination_cell_property_name = 
  "graveyard";
  
// Store a list of cells that have been previously found to contain points.
// This list is appended every time the getCellContainingPoint function is
// called.
std::set<GeometryHandlerTraits<moab::DagMC>::CellHandle> 
GeometryHandlerTraits<moab::DagMC>::cells_containing_test_points;

// Store the collection of all cells in the geometry
moab::Range GeometryHandlerTraits<moab::DagMC>::all_cells;

// Store a DagMC::RayHistory for ray tracing
moab::DagMC::RayHistory GeometryHandlerTraits<moab::DagMC>::ray_history;

} // end Traits namespace

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "GeometryHandlerTraits_DagMC_def.hpp"

//---------------------------------------------------------------------------//

#endif // end GEOMETRY_HANDLER_TRAITS_DAGMC_HPP

//---------------------------------------------------------------------------//
// end GeometryHandlerTraits_DagMC.hpp
//---------------------------------------------------------------------------//
