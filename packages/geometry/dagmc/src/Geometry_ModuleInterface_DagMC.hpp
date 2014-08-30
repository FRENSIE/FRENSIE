//---------------------------------------------------------------------------//
//!
//! \file   Geometry_ModuleInterface_DagMC.hpp
//! \author Alex Robinson
//! \brief  DagMC specialization decl. of the geometry ModuleInterface class
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_MODULE_INTERFACE_DAGMC_HPP
#define GEOMETRY_MODULE_INTERFACE_DAGMC_HPP

// Boost Includes
#include <boost/unordered_set.hpp>

// Moab Includes
#include <DagMC.hpp>

// Trilins Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Geometry_ModuleInterfaceDecl.hpp"
#include "Geometry_DagMCProperties.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_MOABException.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_GlobalOpenMPSession.hpp"

namespace Geometry{

/*! The specialization of the GeometryModuleInterface class for the DagMC
 * geometry handler.
 * \ingroup geometry_module
 */
template<>
class ModuleInterface<moab::DagMC>
{

public:

  //! The external surface id class (used within the geometry handler)
  typedef int ExternalSurfaceId;
  //! The external cell id class (used within the geometry handler )
  typedef int ExternalCellId;
  
  //! The external surface handle class (used within the geometry handler)
  typedef moab::EntityHandle ExternalSurfaceHandle;
  //! The external cell handle class (used within the geometry handler)
  typedef moab::EntityHandle ExternalCellHandle;
  
  //! The internal surface handle class (used within FRENSIE)
  typedef ModuleTraits::InternalSurfaceHandle InternalSurfaceHandle;
  //! The internal cell handle class (used within FRENSIE)
  typedef ModuleTraits::InternalCellHandle InternalCellHandle;

private:
  
  //! Typedef for Teuchos::ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! The value of an invalid surface handle
  static const ExternalSurfaceHandle invalid_external_surface_handle;

  //! The value of an invalid cell handle
  static const ExternalCellHandle invalid_external_cell_handle; 
  
  //! Set the geometry handler instance
  static void setHandlerInstance( 
			   const Teuchos::RCP<moab::DagMC>& handler_instance );

  //! Do just in time initialization required for interface to work properly
  static void initialize();  

  //! Find the cell that contains a given point (start of history)
  static InternalCellHandle findCellContainingPoint( const Ray& ray );

  //! Find the cell that contains a given point (surface crossing)
  static InternalCellHandle findCellContainingPoint( 
					 const Ray& ray,
					 const InternalCellHandle current_cell,
					 const InternalSurfaceHandle surface );

  //! Fire a ray through the geometry
  static void fireRay( const Ray& ray,
		       const InternalCellHandle& current_cell,
		       InternalSurfaceHandle& surface_hit,
		       double& distance_to_surface_hit );

  //! Initialize a new ray (after a collision)
  static void newRay();

  //! Check if the cell is a termination cell
  static bool isTerminationCell( const InternalCellHandle cell );

  //! Get the point location w.r.t. a given cell
  static PointLocation getPointLocation( const Ray& ray,
					 const InternalCellHandle cell );
  
  //! Calculate the surface normal at a point on the surface
  static void getSurfaceNormal( const InternalSurfaceHandle surface,
				const double position[3],
				double normal[3] );

  //! Get the volume of a cell
  static double getCellVolume( const InternalCellHandle cell );
  
  //! Get the surface area of a surface bounding a cell
  static double getCellSurfaceArea( const InternalSurfaceHandle surface,
				    const InternalCellHandle cell );

  //! Check that an external surface handle exists
  static bool doesSurfaceExist( const ExternalSurfaceId surface );

  //! Check that an external cell handle exists
  static bool doesCellExist( const ExternalCellId cell );

  //! Get the internal surf. handle corresponding to the external surf. handle
  static InternalSurfaceHandle getInternalSurfaceHandle(
				const ExternalSurfaceHandle surface_external );

  //! Get the internal surf. handle corresponding to the external surf. id
  static InternalSurfaceHandle getInternalSurfaceHandle(
					  const ExternalSurfaceId surface_id );

  //! Get the internal cell handle corresponding to the external cell handle
  static InternalCellHandle getInternalCellHandle( 
				      const ExternalCellHandle cell_external );

  //! Get the internal cell handle corresponding to the external cell id
  static InternalCellHandle getInternalCellHandle(
						const ExternalCellId cell_id );

  //! Get the external surf. handle corresponding to the internal surf. handle
  static ExternalSurfaceHandle getExternalSurfaceHandle(
					 const InternalSurfaceHandle surface );
  

  //! Get the external cell handle corresponding to the internal cell handle
  static ExternalCellHandle getExternalCellHandle(
					       const InternalCellHandle cell );

private:

  //! Get the point location w.r.t. a given cell
  static PointLocation getPointLocation(const ExternalCellHandle cell_external,
					const double position[3],
					const double direction[3] );

  //! Get all the cells contained in the geometry
  static void getAllCells();

  //! Test the cells found to contain test points for point containment
  static void testCellsContainingTestPoints( InternalCellHandle& cell,
					     const Ray& ray );

  //! Test all remaining cells for point containment
  static void testAllRemainingCells( InternalCellHandle& cell,
				     const Ray& ray );

  // An instance of DagMC
  static moab::DagMC* const dagmc_instance;

  // The set of cells that have previously been found to contain points.
  static boost::unordered_set<ExternalCellHandle> cells_containing_test_points;

  // The collection of all cells in the geometry
  static moab::Range all_cells;

  // The DagMC::RayHistory for ray tracing (one for each thread)
  static std::vector<moab::DagMC::RayHistory> ray_history;
};

// Set the geometry handler instance
/*! \details The DagMC class is a singleton pattern. Only one instance will
 * ever be active so this function call can be ignored.
 */
inline void ModuleInterface<moab::DagMC>::setHandlerInstance( 
			    const Teuchos::RCP<moab::DagMC>& handler_instance )
{ /* ... */ }

// Initialize a new ray (after a collision)
/*! \details DagMC has an internal RayHistory class that it uses to help with
 * ray tracing. This class simply stores the entity handles of surface facets
 * that have been crossed so that those facets will not be intersected again by
 * the current ray. This class is very specific to DagMC and thus should be 
 * hidden from the rest of FRENSIE so that generality in the particle tracking 
 * algorithms is maintained. This specialized class has a RayHistory instance 
 * stored as a private static member. Everytime a particle changes direction 
 * and ray tracing recommences, this function must be called to reset the 
 * RayHistory instance. In other specializations this function may be 
 * optimized out.
 */
inline void ModuleInterface<moab::DagMC>::newRay()
{
  // Make sure the interface has been set up correctly
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() <
		    ModuleInterface<moab::DagMC>::ray_history.size() );
  
  ModuleInterface<moab::DagMC>::ray_history[Utility::GlobalOpenMPSession::getThreadId()].reset();
}

// Check if the cell is a termination cell
inline bool ModuleInterface<moab::DagMC>::isTerminationCell( 
						const InternalCellHandle cell )
{
  ExternalCellHandle cell_external = 
    ModuleInterface<moab::DagMC>::getExternalCellHandle( cell );
                                                                               
  return ModuleInterface<moab::DagMC>::dagmc_instance->has_prop( 
	cell_external,
	DagMCProperties::getTerminationCellPropertyName() );
}

// Calculate the surface normal at a point on the surface
/* \details This function will throw a Utility::MOABException if the desired
 * surface does not exist or if the point is not actually on the surface.
 */
inline void ModuleInterface<moab::DagMC>::getSurfaceNormal( 
					   const InternalSurfaceHandle surface,
					   const double position[3],
					   double normal[3] )
{
  // Make sure the interface has been set up correctly
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() <
		    ModuleInterface<moab::DagMC>::ray_history.size() );
  
  ExternalSurfaceHandle surface_external = 
    ModuleInterface<moab::DagMC>::getExternalSurfaceHandle( surface );
    
  moab::ErrorCode return_value = 
    ModuleInterface<moab::DagMC>::dagmc_instance->get_angle(
			  surface_external,
			  position,
			  normal,
			  &ModuleInterface<moab::DagMC>::ray_history[Utility::GlobalOpenMPSession::getThreadId()] );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
		      Utility::MOABException,
		      moab::ErrorCodeStr[return_value] );
}

// Get the volume of a cell
/*! \details This function will throw a Utility::MOABException if the desired
 * cell does not exist.
 */
inline double ModuleInterface<moab::DagMC>::getCellVolume( 
						const InternalCellHandle cell )
{
  ExternalCellHandle cell_external = 
    ModuleInterface<moab::DagMC>::getExternalCellHandle( cell );
    
  double volume = 0.0;
  
  moab::ErrorCode return_value = 
    ModuleInterface<moab::DagMC>::dagmc_instance->measure_volume( 
								 cell_external,
								 volume );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
		      Utility::MOABException,
		      moab::ErrorCodeStr[return_value] );

  // Make sure that the calculated volume is valid
  testPostcondition( !ST::isnaninf( volume ) );
  testPostcondition( volume > 0.0 );
  
  return volume;
}

// Get the surface area of a surface bounding a cell
/*! \details This function will throw a Utility::MOABException if the 
 * desired surface does not exist. Currently, the cell handle is not required
 * to determine the surface area. The parameter is still needed to conform to
 * the Utility::Traits::GeometryHandlerTraits class concept.
 */ 
inline double ModuleInterface<moab::DagMC>::getCellSurfaceArea( 
					   const InternalSurfaceHandle surface,
					   const InternalCellHandle )
{
  ExternalSurfaceHandle surface_external = 
    ModuleInterface<moab::DagMC>::getExternalSurfaceHandle( surface );
    
  double area = 0.0;

  moab::ErrorCode return_value = 
    ModuleInterface<moab::DagMC>::dagmc_instance->measure_area(
							      surface_external,
							      area );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
		      Utility::MOABException,
		      moab::ErrorCodeStr[return_value] );
  
  // Make sure that the calculated area is valid
  testPostcondition( !ST::isnaninf( area ) );
  testPostcondition( area > 0.0 );
  
  return area;
}

// Check that an external surface handle exists
inline bool ModuleInterface<moab::DagMC>::doesSurfaceExist(
					      const ExternalSurfaceId surface )
{
  if( ModuleInterface<moab::DagMC>::dagmc_instance->entity_by_id( 2, surface ) 
      != 0 )
    return true;
  else
    return false;
}

// Check that an external cell handle exists
inline bool ModuleInterface<moab::DagMC>::doesCellExist(
						    const ExternalCellId cell )
{
  if( ModuleInterface<moab::DagMC>::dagmc_instance->entity_by_id( 3, cell ) 
      != 0 )
    return true;
  else
    return false;
}

// Get the internal surf. handle corresponding to the external surf. handle
inline ModuleInterface<moab::DagMC>::InternalSurfaceHandle 
ModuleInterface<moab::DagMC>::getInternalSurfaceHandle(
				 const ExternalSurfaceHandle surface_external )
{
  return static_cast<InternalSurfaceHandle>( 
	   ModuleInterface<moab::DagMC>::dagmc_instance->get_entity_id(
							  surface_external ) );
}

// Get the internal surf. handle corresponding to the external surf. handle
inline ModuleInterface<moab::DagMC>::InternalSurfaceHandle 
ModuleInterface<moab::DagMC>::getInternalSurfaceHandle(
				           const ExternalSurfaceId surface_id )
{
  testPrecondition( doesSurfaceExist( surface_id ) );
  
  return static_cast<InternalSurfaceHandle>( surface_id );
}

// Get the internal cell handle corresponding to the external cell handle
inline ModuleInterface<moab::DagMC>::InternalCellHandle 
ModuleInterface<moab::DagMC>::getInternalCellHandle( 
				       const ExternalCellHandle cell_external )
{
  return static_cast<InternalCellHandle>(
	   ModuleInterface<moab::DagMC>::dagmc_instance->get_entity_id(
							     cell_external ) );
}

// Get the internal cell handle corresponding to the external cell handle
inline ModuleInterface<moab::DagMC>::InternalCellHandle 
ModuleInterface<moab::DagMC>::getInternalCellHandle( 
				                 const ExternalCellId cell_id )
{
  testPrecondition( doesCellExist( cell_id ) );
  
  return static_cast<InternalCellHandle>( cell_id );
}

// Get the external surf. handle corresponding to the internal surf. handle
inline ModuleInterface<moab::DagMC>::ExternalSurfaceHandle 
ModuleInterface<moab::DagMC>::getExternalSurfaceHandle(
					  const InternalSurfaceHandle surface )
{
  testPrecondition( doesSurfaceExist( 
		                 static_cast<ExternalSurfaceId>( surface ) ) );
  
  return ModuleInterface<moab::DagMC>::dagmc_instance->entity_by_id(
				2, static_cast<ExternalSurfaceId>( surface ) );
}
  
// Get the external cell handle corresponding to the internal cell handle
inline ModuleInterface<moab::DagMC>::ExternalCellHandle 
ModuleInterface<moab::DagMC>::getExternalCellHandle(
					        const InternalCellHandle cell )
{
  testPrecondition( doesCellExist( static_cast<ExternalCellId>( cell ) ) );
  
  return ModuleInterface<moab::DagMC>::dagmc_instance->entity_by_id(
				      3, static_cast<ExternalCellId>( cell ) );
}

} // end Geometry namespace

#endif // end GEOMETRY_MODULE_INTERFACE_DAGMC_HPP

//---------------------------------------------------------------------------//
// end Geometry_ModuleInterface_DagMC.hpp
//---------------------------------------------------------------------------//
