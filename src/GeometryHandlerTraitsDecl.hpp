//---------------------------------------------------------------------------//
//!
//! \file   GeometryHandlerTraitsDecl.hpp
//! \author Alex Robinson
//! \brief  Geometry handler traits class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_HANDLER_TRAITS_DECL_HPP
#define GEOMETRY_HANDLER_TRAITS_DECL_HPP

// Trilinos Includes
#include <Teuchos_ArrayRCP.hpp>
#include <Teuchos_OrdinalTraits.hpp>

// FACEMC Includes
#include "PointLocation.hpp"
#include "ParticleState.hpp"
#include "UndefinedTraits.hpp"
#include "ContractException.hpp"

/*! \defgroup geometry_handler_traits Geometry Handler Traits
 * \ingroup traits
 *
 * This class is needed to provide a consistent interface for Monte Carlo
 * particle tracking independent of the geometry handler (i.e. DagMC or native
 * handler). To use a particular geometry handler, the 
 * FACEMC::Traits::GeometryHandlerTraits class must be specialized for that 
 * handler. Attempting to use the class without a specialization will result 
 * in a compile time error. The compile time error message is defined by the
 * FACEMC::Traits::UndefinedTraits struct.
 */

namespace FACEMC{

namespace Traits{

/*! \brief Default geometry traits struct.
 *
 * This struct should allow use of any geometry handler used for representing
 * a geometry and conducting ray tracings. The functions in the templated base
 * unspecialized struct are designed not to compile (giving a nice compile-time
 * error message) and therefore specializations must be written for each
 * geometry handler type. The design pattern that is implemented with the
 * templated class is the bridge pattern. Every geometry handler type has a 
 * slightly different interface and this struct homogenizes the interfaces so
 * that they can all be used inside of the core Monte Carlo simulation classes.
 * It should be noted that even though the class name implies that this is a 
 * traits class, some behavioral functions are also defined indicating that it
 * is not a true traits class (it is also a policies class). The traits name
 * was used to conform with the standard library convention (see
 * std::char_traits which is also a hybrid traits and policies class). It must
 * be noted that one need not interact with the behavioral functions directly
 * through the traits class. Several policy functions have been written that
 * hide the traits class.
 * \ingroup geometry_handler_traits
 */
template<typename GeometryHandler>
struct GeometryHandlerTraits
{
  //! The GeometryHandler class pointer
  typedef GeometryHandler* GeometryHandlerPtr;
  //! The surface handle class (used to reference a surface)
  typedef int SurfaceHandle;
  //! The cell handle class (used to reference a cell)
  typedef int CellHandle;
  //! The surface id type
  typedef int SurfaceId;
  //! The cell id type
  typedef int CellId;

  //! Get an instance of the GeometryHandler (singleton pattern)
  static inline GeometryHandlerPtr getHandler()
  { (void)UndefinedTraits<GeometryHandler>::notDefined(); return NULL; }

  //! Fire a ray through the geometry
  /*! \details A std::runtime_error (or class derived from it) must be thrown 
   * if a ray tracing error occurs. These exceptions will be caught in the
   * main particle simulation algorithms and are used to indicate lost 
   * particles.
   */
  static inline void fireRay( const ParticleState<CellHandle>& particle,
			      SurfaceHandle& surface_hit,
			      double& distance_to_surface_hit )
  { (void)UndefinedTraits<GeometryHandler>::notDefined(); }
  
  //! Indicate that a new ray will be started (after a collision)
  static inline void newRay()
  { (void)UndefinedTraits<GeometryHandler>::notDefined(); }

  //! Update the cell that contains a given particle (start of history)
  /*! \details A std::runtime_error (or class derived from it) must be thrown 
   * if an error occurs. These exceptions will be caught in the main particle 
   * simulation algorithms and are used to indicate lost particles.
   */
  static inline void updateCellContainingParticle( 
					  ParticleState<CellHandle>& particle )
  { (void)UndefinedTraits<GeometryHandler>::notDefined(); }

  //! Update the cell that contains a given particle (surface crossing)
  /*! \details A std::runtime_error (or class derived from it) must be thrown 
   * if an error occurs. These exceptions will be caught in the main particle 
   * simulation algorithms and are used to indicate lost particles.
   */
  static inline void updateCellContainingParticle(
					   ParticleState<CellHandle>& particle,
					   const SurfaceHandle& surface )
  { (void)UndefinedTraits<GeometryHandler>::notDefined(); }

  //! Check if the cell is a termination cell
  static inline bool isTerminationCell( const CellHandle& cell )
  { (void)UndefinedTraits<GeometryHandler>::notDefined(); return 0; }

  //! Get the particle location w.r.t. a given cell
  /*! \details A std::runtime_error (or class derived from it) must be thrown 
   * if an error occurs. These exceptions will be caught in the main particle 
   * simulation algorithms and are used to indicate lost particles.
   */
  static inline PointLocation getParticleLocation( 
				    const CellHandle& cell,
				    const double position[3] )
  { (void)UndefinedTraits<GeometryHandler>::notDefined(); return 0; }

  //! Calculate the surface normal at a point on the surface
  static inline void getSurfaceNormal( 
				     const SurfaceHandle& surface,
				     const ParticleState<CellHandle>& particle,
				     double normal[3] )
  { (void)UndefinedTraits<GeometryHandler>::notDefined(); return 0; }

  //! Get the volume of a cell
  static inline double getCellVolume( const CellHandle& cell )
  { (void)UndefinedTraits<GeometryHandler>::notDefined(); return 0; }

  //! Get the surface area of a surface bounding a cell
  static inline double getCellSurfaceArea( const SurfaceHandle& surface,
					   const CellHandle& cell )
  { (void)UndefinedTraits<GeometryHandler>::notDefined(); return 0; }

  //! Get the cell id corresponding to the cell handle
  static inline CellId getCellId( const CellHandle& cell )
  { (void)UndefinedTraits<GeometryHandler>::notDefined(); return 0; }

  //! Get the cell handle corresponding to the cell id
  static inline CellHandle getCellHandle( const CellId& cell_id )
  { (void)UndefinedTraits<GeometryHandler>::notDefined(); return 0; }
  
  //! Get the surface id corresponding to the surface handle
  static inline SurfaceId getSurfaceId( const SurfaceHandle& surface )
  { (void)UndefinedTraits<GeometryHandler>::notDefined(); return 0; }

  //! Get the surface handle corresponding to the surface id
  static inline SurfaceHandle getSurfaceHandle( const SurfaceHandle& surface )
  { (void)UndefinedTraits<GeometryHandler>::notDefined(); return 0; }
};

} // end Traits namespace

} // end FACEMC namespace

#endif // end GEOMETRY_HANDLER_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end GeometryHandlerTraitsDecl.hpp
//---------------------------------------------------------------------------//

