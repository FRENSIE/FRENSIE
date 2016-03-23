//---------------------------------------------------------------------------//
//! 
//! \file   Geometry_ModuleInterfaceDecl.hpp
//! \author Alex Robinson
//! \brief  Geometry module interface class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_MODULE_INTERFACE_DECL_HPP
#define GEOMETRY_MODULE_INTERFACE_DECL_HPP

// Std Lib Includes
#include <memory>

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

  //! Set the geometry handler instance
  static inline void setHandlerInstance( 
                     const std::shared_ptr<GeometryHandler>& handler_instance )
  { (void)UndefinedGeometryHandler<GeometryHandler>::notDefined(); }

  //! Do just in time initialization interface members
  static inline void initialize()
  { (void)UndefinedGeometryHandler<GeometryHandler>::notDefined(); }

  //! Enable support for multiple threads
  static void enableThreadSupport( const unsigned num_threads )
  { (void)UndefinedGeometryHandler<GeometryHandler>::notDefined(); }
  
  //! Check if a cell exists
  static inline bool doesCellExist(
                                  const ModuleTraits::InternalCellHandle cell )
  { (void)UndefinedGeometryHandler<GeometryHandler>::notDefined(); return 0; }

  //! Check if a surface exists
  static inline bool doesSurfaceExist(
                            const ModuleTraits::InternalSurfaceHandle surface )
  { (void)UndefinedGeometryHandler<GeometryHandler>::notDefined(); return 0; }

  /*! Set the internal ray
   *
   * A std::runtime_error (or class derived from it) must be thrown
   * if an error occurs. These exceptions will be caught in the main
   * particle simulation algorithms and are used to indicate lost particles
   */
  static inline void setInternalRay( 
                            const Ray& ray, 
                            const ModuleTraits::InternalCellHandle start_cell )
  { (void)UndefinedGeometryHandler<GeometryHandler>::notDefined(); }

  /*! Find the cell that contains a given start ray
   *
   * A std::runtime_error (or class derived from it) must be thrown 
   * if an error occurs. These exceptions will be caught in the main particle 
   * simulation algorithms and are used to indicate lost particles.
   */
  static inline ModuleTraits::InternalCellHandle findCellContainingStartRay( 
                                                               const Ray& ray )
  { (void)UndefinedGeometryHandler<GeometryHandler>::notDefined(); }

  /*! Find the cell that contains the internal ray
   *
   * A std::runtime_error (or class derived from it) must be thrown 
   * if an error occurs. These exceptions will be caught in the main particle 
   * simulation algorithms and are used to indicate lost particles.
   */
   static inline ModuleTraits::InternalCellHandle findCellContainingInternalRay()
   { (void)UndefinedGeometryHandler<GeometryHandler>::notDefined(); }

  /*! Fire the internal ray through the geometry
   *
   * A std::runtime_error (or class derived from it) must be thrown 
   * if a ray tracing error occurs. These exceptions will be caught in the
   * main particle simulation algorithms and are used to indicate lost 
   * particles.
   */
  static inline double fireInternalRay(                           
                             ModuleTraits::InternalSurfaceHandle& surface_hit )
  { (void)UndefinedGeometryHandler<GeometryHandler>::notDefined(); return 0; }

  /*! Advance the internal ray to the cell boundary
   *
   * If a reflecting surface is hit "true" will be returned.
   */
  static inline bool advanceInternalRayToCellBoundary( 
                                                     double surface_normal[3] )
  { (void)UndefinedGeometryHandler<GeometryHandler>::notDefined(); return 0; }

  //! Advance the internal ray by a substep (less than distance to boundary)
  static inline void advanceInternalRayBySubstep( const double step_size ) 
  { (void)UndefinedGeometryHandler<GeometryHandler>::notDefined(); return 0; }

  //! Change the internal ray direction
  static inline void changeInternalRayDirection( const double direction[3] )
  { (void)UndefinedGeometryHandler<GeometryHandler>::notDefined(); }         

  //! Get the internal ray position
  static inline const double* getInternalRayPosition()
  { (void)UndefinedGeometryHandler<GeometryHandler>::notDefined(); return 0; }

  //! Get the internal ray direction
  static inline const double* getInternalRayDirection()
  { (void)UndefinedGeometryHandler<GeometryHandler>::notDefined(); return 0; }

  //! Check if the cell is a termination cell
  static inline bool isTerminationCell( 
                                  const ModuleTraits::InternalCellHandle cell )
  { (void)UndefinedGeometryHandler<GeometryHandler>::notDefined(); return 0; }

  /*! Get the point location w.r.t. a given cell
   *
   * A std::runtime_error (or class derived from it) must be thrown 
   * if an error occurs. These exceptions will be caught in the main particle 
   * simulation algorithms and are used to indicate lost particles.
   */
  static inline PointLocation getPointLocation( 
                                  const Ray& ray,
				  const ModuleTraits::InternalCellHandle cell )
  { (void)UndefinedGeometryHandler<GeometryHandler>::notDefined(); return 0; }
};

//! Set the geometry handler instance
template<typename GeometryHandler>
void setGeometryHandlerInstance(
                     const std::shared_ptr<GeometryHandler>& handler_instance )
{
  Geometry::ModuleInterface<GeometryHandler>::setHandlerInstance( 
							    handler_instance );
}

} // end Geometry namespace

#endif // end GEOMETRY_MODULE_INTERFACE_DECL_HPP

//---------------------------------------------------------------------------//
// end Geometry_ModuleInterfaceDecl.hpp
//---------------------------------------------------------------------------//
