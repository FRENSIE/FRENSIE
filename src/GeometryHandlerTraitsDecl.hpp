//---------------------------------------------------------------------------//
//!
//! \file   ArrayTraitsDecl.hpp
//! \author Alex Robinson
//! \brief  Geometry handler traits class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_HANDLER_TRAITS_DECL_HPP
#define GEOMETRY_HANDLER_TRAITS_DECL_HPP

// Trilinos Includes
#include <Teuchos_ArrayView.hpp>
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

  //! Get an instance of the GeometryHandler (singleton pattern)
  static inline GeometryHandlerPtr getInstance()
  { (void)UndefinedTraits<GeometryHandler>::notDefined(); return NULL; }
  
  //! Fire a ray through the geometry
  static inline void fireRay( GeometryHandler& geometry_handler,
			      const CellHandle& cell,
			      const double ray_start_position[3],
			      const double ray_direction[3],
			      SurfaceHandle& surface_hit,
			      double& distance_to_surface_hit );

  //! Fire a ray through the geometry
  static inline void fireRay( GeometryHandler& geometry_handler,
			      const ParticleState<CellHandle>& particle,
			      SurfaceHandle& surface_hit,
			      double& distance_to_surface_hit )
  { (void)UndefinedTraits<GeometryHandler>::notDefined(); }
  
  //! Indicate that a new ray will be started (after a collision)
  static inline void newRay()
  { (void)UndefinedTraits<GeometryHandler>::notDefined(); }

  //! Get the cell that contains a given point
  static inline CellHandle getCellContainingPoint( 
				          GeometryHandler& geometry_handler,
				          const double point[3],
					  const double* direction = NULL )
  { (void)UndefinedTraits<GeometryHandler>::notDefined(); return 0; }

  //! Get the point location w.r.t. a given cell
  static inline PointLocation getPointLocation( 
			            GeometryHandler& geometry_handler,
				    const CellHandle& cell,
				    const double point[3],
				    const double* direction = NULL )
  { (void)UndefinedTraits<GeometryHandler>::notDefined(); return 0; }

  //! Get the cell on the other side of a surface
  static inline CellHandle getNextCell( GeometryHandler& geometry_handler,
					const SurfaceHandle& surface,
					const CellHandle& current_cell,
					const double* point = NULL );
  { (void)UndefinedTraits<GeometryHandler>::notDefined(); return 0; }

  //! Update the cell that contains a given particle (start of history)
  static inline void updateCellContainingParticle( 
					  GeometryHandler& geometry_handler,
				          ParticleState<CellHandle>& particle )
  { (void)UndefinedTraits<GeometryHandler>::notDefined(); }

  //! Update the cell that contains a given particle (surface crossing)
  static inline void updateCellContainingParticle(
				          GeometryHandler& geometry_handler,
					  const SurfaceHandle& surface,
				          ParticleState<CellHandle>& particle )
  { (void)UndefinedTraits<GeometryHandler>::notDefined(); }

  //! Check if the cell is a termination cell
  static inline bool isTerminationCell( GeometryHandler& geometry_handler,
					const CellHandle& cell )
  { (void)UndefinedTraits<GeometryHandler>::notDefined(); return 0; }

  //! Get the volume of a cell
  static inline double getCellVolume( GeometryHandler& geometry_handler,
				      const CellHandle& cell )
  { (void)UndefinedTraits<GeometryHandler>::notDefined(); return 0; }

  //! Get the surface area of a surface bounding a cell
  static inline double getCellSurfaceArea( GeometryHandler& geometry_handler,
					   const CellHandle& cell,
					   const SurfaceHandle& surface )
  { (void)UndefinedTraits<GeometryHandler>::notDefined(); return 0; }

  //! Get the surface normal at a point on the surface
  static inline void getSurfaceNormal( GeometryHandler& geometry_handler,
				       const SurfaceHandle& surface,
				       const double point[3], 
				       double angle[3] )
  { (void)UndefinedTraits<GeometryHandler>::notDefined(); return 0; }
				       
};

} // end Traits namespace

/*! This function allows access to the fireRay GeometryHandlerTraits 
 * function.
 *
 * This function is simply a more concise way to access the fireRay static
 * member function associated with the GeometryHandlerTraits class. It simply
 * forwards calls to fire a ray to the associated 
 * FACEMC::Traits::GeometryHandlerTraits class. It is important to note that
 * GeometryHandler type will be deduced by the function.
 * \ingroup geometry_handler_traits
 */
template<typename GeometryHandler>
inline void fireRay( 
  GeometryHandler& geometry_handler,
  const typename Traits::GeometryHandlerTraits<GeometryHandler>::CellHandle& cell,
  const ParticleState<typename Traits::GeometryHandlerTraits<GeometryHandler>::CellHandle>& particle,
  typename Traits::GeometryHandlerTraits<GeometryHandler>::SurfaceHandle&
  surface_hit,
  double& distance_to_surface_hit )
{ 
  Traits::GeometryHandlerTraits<GeometryHandler>::fireRay( 
						     geometry_handler,
						     cell,
						     particle,
						     surface_hit,
						     distance_to_surface_hit );
}

/*! This function allows access to the getPointLocation GeometryHandlerTraits 
 * function
 *
 * This function is simply a more concise way to access the getPointLocation
 * static member function associated with the GeometryHandlerTraits class. It 
 * simply forwards calls to get a point location to the associated 
 * FACEMC::Traits::GeometryHandlerTraits class. It is important to note that
 * GeometryHandler type will be deduced by the function.
 * \ingroup geometry_handler_traits
 */
template<typename GeometryHandler>
inline PointLocation getPointLocation( 
     GeometryHandler& geometry_handler,
     const typename Traits::GeometryHandlerTraits<GeometryHandler>::CellHandle&
     cell,
     const ParticleState<typename Traits::GeometryHandlerTraits<GeometryHandler>::CellHandle>& particle )
{ 
  return Traits::GeometryHandlerTraits<GeometryHandler>::getPointLocation( 
							      geometry_handler,
							      cell,
							      particle );
}

/*! This function allows access to the getCellVolume GeometryHandlerTraits 
 * function
 * 
 * This function is simply a more concise way to access the getCellVolume
 * static member function associated with the GeometryHandlerTraits class. It 
 * simply forwards calls to get a cell volume to the associated 
 * FACEMC::Traits::GeometryHandlerTraits class. It is important to note that 
 * GeometryHandler type will be deduced by the function.
 * \ingroup geometry_handler_traits
 */
template<typename GeometryHandler>
inline double getCellVolume( 
     GeometryHandler& geometry_handler,
     const typename Traits::GeometryHandlerTraits<GeometryHandler>::CellHandle&
     cell )
{ 
  return Traits::GeometryHandlerTraits<GeometryHandler>::getCellVolume(
							      geometry_handler,
							      cell );
}

/*! This function allows access to the getCellSurfaceArea GeometryHandlerTraits
 * function
 *
 * This function is simply a more concise way to access the getCellSurfaceArea
 * static member function associated with the GeometryHandlerTraits class. It 
 * simply forwards calls to get a cell surface area to the associated 
 * FACEMC::Traits::GeometryHandlerTraits class. It is important to note that
 * GeometryHandler type will be deduced by the function.
 * \ingroup geometry_handler_traits
 */
template<typename GeometryHandler>
inline double getCellSurfaceArea( 
  const GeometryHandler& geometry_handler,
  const typename Traits::GeometryHandlerTraits<GeometryHandler>::CellHandle&
  cell,
  const typename Traits::GeometryHandlerTraits<GeometryHandler>::SurfaceHandle&
  surface )
{
  return Traits::GeometryHandlerTraits<GeometryHandler>::getCellVolume( 
							      geometry_handler,
							      cell,
							      surface );
}

/*! This function allows access to the getNextCell GeometryHandlerTraits 
 * function.
 *
 * This function is simply a more concise way to access the getNextCell
 * static member function associated with the GeometryHandlerTraits class. It 
 * simply forwards calls to get the cell on the other side of a surface to the 
 * associated FACEMC::Traits::GeometryHandlerTraits class. It is important to 
 * note that GeometryHandler type will be deduced by the function.
 * \ingroup geometry_handler_traits
 */
template<typename GeometryHandler>
inline void getNextCell( 
            const GeometryHandler& geometry_handler,
            const Traits::GeometryHandlerTraits<GeometryHandler> SurfaceHandle&
	    surface,
	    const Traits::GeometryHandlerTraits<GeometryHandler> CellHandle& 
	    current_cell,
	    const ParticleState<typename Traits::GeometryHandlerTraits<GeometryHandler>::CellHandle>& particle )
{
  return Traits::GeometryHandlerTraits<GeometryHandler>::getNextCell( 
							      geometry_handler,
							      surface,
							      current_cell,
							      particle );
}

} // end FACEMC namespace

#endif // end GEOMETRY_HANDLER_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end GeometryHandlerTraitsDecl.hpp
//---------------------------------------------------------------------------//

