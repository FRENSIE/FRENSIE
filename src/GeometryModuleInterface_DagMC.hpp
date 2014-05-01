//---------------------------------------------------------------------------//
//!
//! \file   GeometryModuleInterface_DagMC.hpp
//! \author Alex Robinson
//! \brief  DagMC specialization decl. of the GeometryModuleInterface class
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

// FACEMC Includes
#include "GeometryModuleInterfaceDecl.hpp"
#include "ExceptionTestMacros.hpp"
#include "MOABException.hpp"
#include "ContractException.hpp"

namespace FACEMC{

/*! The specialization of the GeometryModuleInterface class for the DagMC
 * geometry handler.
 * \ingroup geometry_module
 */
template<>
class GeometryModuleInterface<moab::DagMC>
{

public:
  
  //! The external surface handle class (used within the geometry handler)
  typedef moab::EntityHandle ExternalSurfaceHandle;
  //! The external cell handle class (used within the geometry handler)
  typedef moab::EntityHandle ExternalCellHandle;
  
  //! The internal surface handle class (used within FACEMC)
  typedef Traits::ModuleTraits::InternalSurfaceHandle InternalSurfaceHandle;
  //! The internal cell handle class (used within FACEMC)
  typedef Traits::ModuleTraits::InternalCellHandle InternalCellHandle;

private:
  
  //! Typedef for Teuchos::ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! The value of an invalid surface handle
  static const ExternalSurfaceHandle invalid_external_surface_handle;

  //! The value of an invalid cell handle
  static const ExternalCellHandle invalid_external_cell_handle; 
  
  //! Set the geometry handler instance
  static void setHandlerInstance( moab::DagMC* handler_instance );

  //! Update the cell that contains a given particle (start of history)
  static void updateCellContainingParticle( ParticleState& particle );

  //! Update the cell that contains a given particle (surface crossing)
  static void updateCellContainingParticle( 
					 ParticleState& particle,
					 const InternalSurfaceHandle surface );

  //! Fire a ray through the geometry
  static void fireRay( const ParticleState& particle,
		       InternalSurfaceHandle& surface_hit,
		       double& distance_to_surface_hit );

  //! Initialize a new ray (after a collision)
  static void newRay();

  //! Check if the cell is a termination cell
  static bool isTerminationCell( const InternalCellHandle cell );

  //! Get the particle location w.r.t. a given cell
  static PointLocation getParticleLocation( const InternalCellHandle cell,
					    const double position[3],
					    const double direction[3] );
  
  //! Calculate the surface normal at a point on the surface
  static void getSurfaceNormal( const InternalSurfaceHandle surface,
				const ParticleState& particle,
				double normal[3] );

  //! Get the volume of a cell
  static double getCellVolume( const InternalCellHandle cell );
  
  //! Get the surface area of a surface bounding a cell
  static double getCellSurfaceArea( const InternalSurfaceHandle surface,
				    const InternalCellHandle cell );

  //! Get the internal surf. handle corresponding to the external surf. handle
  static InternalSurfaceHandle getInternalSurfaceHandle(
					 const ExternalSurfaceHandle surface );

  //! Get the internal cell handle corresponding to the external cell handle
  static InternalCellHandle getInternalCellHandle( 
					       const ExternalCellHandle cell );

  //! Get the external surf. handle corresponding to the internal surf. handle
  static ExternalSurfaceHandle getExternalSurfaceHandle(
					 const InternalSurfaceHandle surface );
  

  //! Get the external cell handle corresponding to the internal cell handle
  static ExternalCellHandle getExternalCellHandle(
					       const ExternalCellHandle cell );

private:

  //! Get the particle location w.r.t. a given cell
  static PointLocation getParticleLocation( const ExternalCellHandle cell,
					    const double position[3],
					    const double direction[3] );

  //! Get all the cells contained in the geometry
  static void getAllCells();

  //! Test the cells found to contain test points for point containment
  static void testCellsContainingTestPoints( InternalCellHandle& cell,
					     const ParticleState& particle );

  //! Test all remaining cells for point containment
  static void testAllRemainingCells( InternalCellHandle& cell,
				     const ParticleState& particle );

  // An instance of DagMC
  static moab::DagMC* const dagmc_instance;

  // The termination cell property name
  static const std::string termination_cell_property_name;

  // The set of cells that have previously been found to contain points.
  static boost::unordered_set<ExternalCellHandle> cells_containing_test_points;

  // The collection of all cells in the geometry
  static moab::Range all_cells;

  // The DagMC::RayHistory for ray tracing
  static moab::DagMC::RayHistory ray_history;
};

// Set the geometry handler instance
/*! \details The DagMC class is a singleton pattern. Only one instance will
 * ever be active so this function call can be ignored.
 */
inline void GeometryModuleInterface<moab::DagMC>::setHandlerInstance( 
						moab::DagMC* handler_instance )
{ /* ... */ }

// Initialize a new ray (after a collision)
/*! \details DagMC has an internal RayHistory class that it uses to help with
 * ray tracing. This class simply stores the entity handles of surface facets
 * that have been crossed so that those facets will not be intersected again by
 * the current ray. This class is very specific to DagMC and thus should be 
 * hidden from the rest of FACEMC so that genericity in the particle tracking 
 * algorithms is maintained. This specialized class has a RayHistory instance 
 * stored as a private static member. Everytime a particle changes direction 
 * and ray tracing recommences, this function must be called to reset the 
 * RayHistory instance. In other specializations this function may be 
 * optimized out.
 */
inline void GeometryModuleInterface<moab::DagMC>::newRay()
{
  GeometryModuleInterface<moab::DagMC>::ray_history.reset();
}

// Check if the cell is a termination cell
inline bool GeometryModuleInterface<moab::DagMC>::isTerminationCell( 
						const InternalCellHandle cell )
{
  ExternalCellHandle cell_external = 
    GeometryModuleInterface<moab::DagMC>::getExternalCellHandle( cell );
                                                                               
  return GeometryModuleInterface<moab::DagMC>::dagmc_instance->has_prop( 
	cell_external,
	GeometryModuleInterface<moab::DagMC>::termination_cell_property_name );
}

// Calculate the surface normal at a point on the surface
/* \details This function will throw a FACEMC::MOABException if the desired
 * surface does not exist or if the particle is not actually on the surface.
 */
inline void GeometryModuleInterface<moab::DagMC>::getSurfaceNormal( 
					   const InternalSurfaceHandle surface,
					   const ParticleState& particle,
					   double normal[3] )
{
  ExternalSurfaceHandle surface_external = 
    GeometryModuleInterface<moab::DagMC>::getExternalSurfaceHandle( surface );
    
  moab::ErrorCode return_value = 
    GeometryModuleInterface<moab::DagMC>::dagmc_instance->get_angle(
			  surface_external,
			  particle.getPosition(),
			  normal,
			  &GeometryModuleInterface<moab::DagMC>::ray_history );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
		      FACEMC::MOABException,
		      moab::ErrorCodeStr[return_value] );
}

// Get the volume of a cell
/*! \details This function will throw a FACEMC::MOABException if the desired
 * cell does not exist.
 */
inline double GeometryModuleInterface<moab::DagMC>::getCellVolume( 
						const InternalCellHandle cell )
{
  ExternalCellHandle cell_external = 
    GeometryModuleInterface<moab::DagMC>::getExternalCellHandle( cell );
    
  double volume = 0.0;
  
  moab::ErrorCode return_value = 
    GeometryModuleInterface<moab::DagMC>::dagmc_instance->measure_volume( 
								 cell_external,
								 volume );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
		      FACEMC::MOABException,
		      moab::ErrorCodeStr[return_value] );

  // Make sure that the calculated volume is valid
  testPostcondition( !ST::isnaninf( volume ) );
  testPostcondition( volume > 0.0 );
  
  return volume;
}

// Get the surface area of a surface bounding a cell
/*! \details This function will throw a FACEMC::MOABException if the 
 * desired surface does not exist. Currently, the cell handle is not required
 * to determine the surface area. The parameter is still needed to conform to
 * the FACEMC::Traits::GeometryHandlerTraits class concept.
 */ 
inline double GeometryModuleInterface<moab::DagMC>::getCellSurfaceArea( 
					   const InternalSurfaceHandle surface,
					   const InternalCellHandle )
{
  ExternalSurfaceHandle surface_external = 
    GeometryModuleInterface<moab::DagMC>::getExternalSurfaceHandle( surface );
    
  double area = 0.0;

  moab::ErrorCode return_value = 
    GeometryModuleInterface<moab::DagMC>::dagmc_instance->measure_area(
							      surface_external,
							      area );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
		      FACEMC::MOABException,
		      moab::ErrorCodeStr[return_value] );
  
  // Make sure that the calculated area is valid
  testPostcondition( !ST::isnaninf( area ) );
  testPostcondition( area > 0.0 );
  
  return area;
}

// Get the internal surf. handle corresponding to the external surf. handle
inline GeometryModuleInterface<moab::DagMC>::InternalSurfaceHandle 
GeometryModuleInterface<moab::DagMC>::getInternalSurfaceHandle(
					  const ExternalSurfaceHandle surface )
{
  return static_cast<InternalSurfaceHandle>( 
	   GeometryModuleInterface<moab::DagMC>::dagmc_instance->get_entity_id(
								   surface ) );
}

// Get the internal cell handle corresponding to the external cell handle
inline GeometryModuleInterface<moab::DagMC>::InternalCellHandle 
GeometryModuleInterface<moab::DagMC>::getInternalCellHandle( 
					        const ExternalCellHandle cell )
{
  return static_cast<InternalCellHandle>(
	   GeometryModuleInterface<moab::DagMC>::dagmc_instance->get_entity_id(
								      cell ) );
}

// Get the external surf. handle corresponding to the internal surf. handle
inline GeometryModuleInterface<moab::DagMC>::ExternalSurfaceHandle 
GeometryModuleInterface<moab::DagMC>::getExternalSurfaceHandle(
					  const InternalSurfaceHandle surface )
{
  return GeometryModuleInterface<moab::DagMC>::dagmc_instance->entity_by_id(
						 2,
					         static_cast<int>( surface ) );
}
  

// Get the external cell handle corresponding to the internal cell handle
inline GeometryModuleInterface<moab::DagMC>::ExternalCellHandle 
GeometryModuleInterface<moab::DagMC>::getExternalCellHandle(
					        const ExternalCellHandle cell )
{
  return GeometryModuleInterface<moab::DagMC>::dagmc_instance->entity_by_id(
						    3,
						    static_cast<int>( cell ) );
}

} // end FACEMC namespace

#endif // end GEOMETRY_MODULE_INTERFACE_DAGMC_HPP

//---------------------------------------------------------------------------//
// end GeometryModuleInterface_DagMC.hpp
//---------------------------------------------------------------------------//
