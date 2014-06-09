//---------------------------------------------------------------------------//
//! 
//! \file   Geometry_ModuleInterfaceDecl.hpp
//! \author Alex Robinson
//! \brief  Geometry module interface class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_MODULE_INTERFACE_DECL_HPP
#define GEOMETRY_MODULE_INTERFACE_DECL_HPP

// Trilinos Inludes
#include <Teuchos_OrdinalTraits.hpp>

// FRENSIE Includes
#include "Geometry_PointLocation.hpp"
#include "Geometry_Ray.hpp"
#include "Geometry_ModuleTraits.hpp"
#include "Utility_ContractException.hpp"

/*! \defgroup geometry_module Geometry Module
 * \ingroup physics_simulation_modules
 *
 * The handling of a geometry used in particle tracking simulations has
 * been abstracted. This allows any of the geometry handling packages 
 * currently available (i.e. DagMC, ROOT, etc) to be used in this software
 * without having to change other code modules. The other code modules only
 * interact with the generic geometry module interface that has been created.
 */

namespace Geometry{

//! The struct that provides the default geometry handler compile time error
template<typename GeometryHandler>
struct UndefinedGeometryHandler
{
  //! This function should not compile if there is any attempt to instantiate!
  static inline void notDefined() { return GeometryHandler::this_geometry_handler_is_missing_an_interface_specialization(); }
};

/*! \brief Default geometry module interface class
 * \ingroup geometry_module 
 * 
 * This struct specifies the interface to the geometry module. This class
 * must be specialized for a particular geometry handling package. Attempting 
 * to use this class without a specialization will result in a compile time 
 * error. The compile time error message is defined by the 
 * Geometry::UndefinedGeometryHandler struct.
 */
template<typename GeometryHandler>
class ModuleInterface
{

public:

  //! The external surface id class (used within the geometry handler)
  typedef int ExternalSurfaceId;
  //! The external cell id class (used within the geometry handler)
  typedef int ExternalCellId;

  //! The external surface handle class (used within the geometry handler)
  typedef ExternalSurfaceId ExternalSurfaceHandle;
  //! The external cell handle class (used within the geometry handler)
  typedef ExternalCellId ExternalCellHandle;
  
  //! The internal surface handle class (used within FRENSIE)
  typedef ModuleTraits::InternalSurfaceHandle InternalSurfaceHandle;
  //! The internal cell handle class (used within FRENSIE)
  typedef ModuleTraits::InternalCellHandle InternalCellHandle;

  //! The value of an invalid surface handle
  static const ExternalSurfaceHandle invalid_external_surface_handle = 0;
 
  //! The value of an invalid cell handle
  static const ExternalCellHandle invalid_external_cell_handle = 0;

  //! Set the geometry handler instance
  static inline void setHandlerInstance( GeometryHandler* handler_instance )
  { (void)UndefinedGeometryHandler<GeometryHandler>::notDefined(); }

  /*! Find the cell that contains a given point (start of history)
   *
   * A std::runtime_error (or class derived from it) must be thrown 
   * if an error occurs. These exceptions will be caught in the main particle 
   * simulation algorithms and are used to indicate lost particles.
   */
  static inline InternalCellHandle findCellContainingPoint( const Ray& ray )
  { (void)UndefinedGeometryHandler<GeometryHandler>::notDefined(); }

  /*! Find the cell that contains a given point (surface crossing)
   *
   * A std::runtime_error (or class derived from it) must be thrown 
   * if an error occurs. These exceptions will be caught in the main particle 
   * simulation algorithms and are used to indicate lost particles.
   */
  static inline InternalCellHandle findCellContainingPoint( 
					 const Ray& ray,
					 const InternalCellHandle current_cell,
					 const InternalSurfaceHandle surface )
  { (void)UndefinedGeometryHandler<GeometryHandler>::notDefined(); }

  /*! Fire a ray through the geometry
   *
   * A std::runtime_error (or class derived from it) must be thrown 
   * if a ray tracing error occurs. These exceptions will be caught in the
   * main particle simulation algorithms and are used to indicate lost 
   * particles.
   */
  static inline void fireRay( const Ray& ray,
			      const InternalCellHandle& current_cell,
			      InternalSurfaceHandle& surface_hit,
			      double& distance_to_surface_hit )
  { (void)UndefinedGeometryHandler<GeometryHandler>::notDefined(); }

  //! Initialize a new ray (after a collision)
  static inline void newRay()
  { (void)UndefinedGeometryHandler<GeometryHandler>::notDefined(); }

  //! Check if the cell is a termination cell
  static inline bool isTerminationCell( const InternalCellHandle cell )
  { (void)UndefinedGeometryHandler<GeometryHandler>::notDefined(); return 0; }

  /*! Get the particle location w.r.t. a given cell
   *
   * A std::runtime_error (or class derived from it) must be thrown 
   * if an error occurs. These exceptions will be caught in the main particle 
   * simulation algorithms and are used to indicate lost particles.
   */
  static inline PointLocation getPointLocation( const Ray& ray,
						const InternalCellHandle cell )
  { (void)UndefinedGeometryHandler<GeometryHandler>::notDefined(); return 0; }
  
  //! Calculate the surface normal at a point on the surface
  static inline void getSurfaceNormal( const InternalSurfaceHandle surface,
				       const double position[3],
				       double normal[3] )
  { (void)UndefinedGeometryHandler<GeometryHandler>::notDefined(); }

  //! Get the volume of a cell
  static inline double getCellVolume( const InternalCellHandle cell )
  { (void)UndefinedGeometryHandler<GeometryHandler>::notDefined(); return 0; }
  
  //! Get the surface area of a surface bounding a cell
  static inline double getCellSurfaceArea( const InternalSurfaceHandle surface,
					   const InternalCellHandle cell )
  { (void)UndefinedGeometryHandler<GeometryHandler>::notDefined(); return 0; }

  //! Check that an external surface handle exists
  static inline bool doesSurfaceExist(const ExternalSurfaceId surface )
  { (void)UndefinedGeometryHandler<GeometryHandler>::notDefined(); return 0; }

  //! Check that an external cell handle exists
  static inline bool doesCellExist( const ExternalCellId cell )
  { (void)UndefinedGeometryHandler<GeometryHandler>::notDefined(); return 0; }

  //! Get the internal surf. handle corresponding to the external surf. handle
  static inline InternalSurfaceHandle getInternalSurfaceHandle(
				 const ExternalSurfaceHandle surface_external )
  { (void)UndefinedGeometryHandler<GeometryHandler>::notDefined(); return 0; }

  //! Get the internal cell handle corresponding to the external cell handle
  static inline InternalCellHandle getInternalCellHandle( 
				       const ExternalCellHandle cell_external )
  { (void)UndefinedGeometryHandler<GeometryHandler>::notDefined(); return 0; }

  //! Get the external surf. handle corresponding to the internal surf. handle
  static inline ExternalSurfaceHandle getExternalSurfaceHandle(
					  const InternalSurfaceHandle surface )
  { (void)UndefinedGeometryHandler<GeometryHandler>::notDefined(); return 0; }

  //! Get the external cell handle corresponding to the internal cell handle
  static inline ExternalCellHandle getExternalCellHandle(
					        const InternalCellHandle cell )
  { (void)UndefinedGeometryHandler<GeometryHandler>::notDefined(); return 0; } 
};

} // end Geometry namespace

#endif // end GEOMETRY_MODULE_INTERFACE_DECL_HPP

//---------------------------------------------------------------------------//
// end Geometry_ModuleInterfaceDecl.hpp
//---------------------------------------------------------------------------//
