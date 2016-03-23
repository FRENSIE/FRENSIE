//---------------------------------------------------------------------------//
//! 
//! \file   Geometry_ModuleInterface_Root.hpp
//! \author Alex Robinson, Eli Moll
//! \brief  Root specialization decl. of the geometry ModuleInterface class
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_MODULE_INTERFACE_ROOT_HPP
#define GEOMETRY_MODULE_INTERFACE_ROOT_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Geometry_ModuleInterfaceDecl.hpp"
#include "Geometry_Root.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Geometry{

/*! The specialization of the GeometryModuleInterface class for the Root 
 * geometry handler.
 * \ingroup geometry_module
 */ 
template<>
class ModuleInterface<Root>
{

public:

  //! Set the geometry handler instance
  static void setHandlerInstance( const std::shared_ptr<Root>& root_instance );

  //! Do just in time initialization of interface members
  static void initialize();

  //! Enable support for multiple threads
  static void enableThreadSupport( const unsigned num_threads );

  //! Check if a cell exists
  static bool doesCellExist( const ModuleTraits::InternalCellHandle cell_id );

  //! Check if the surface exists
  static bool doesSurfaceExist( 
                        const ModuleTraits::InternalSurfaceHandle surface_id );

  //! Set the internal ray
  static void setInternalRay( 
                           const Ray& ray, 
                           const ModuleTraits::InternalCellHandle start_cell );

  //! Find the cell that contains a given start ray
  static ModuleTraits::InternalCellHandle findCellContainingStartRay( 
                                                              const Ray& ray );

  //! Find the cell that containsa the internal ray
  static ModuleTraits::InternalCellHandle findCellContainingInternalRay();

  //! Fire the internal ray through the geometry
  static double fireInternalRay( 
                            ModuleTraits::InternalSurfaceHandle& surface_hit );

  //! Advance the internal ray to the cell boundary
  static bool advanceInternalRayToCellBoundary( double surface_normal[3] );

  //! Advance the internal ray by a substep (less than distance to boundary)
  static void advanceInternalRayBySubstep( const double step_size );

  //! Change the internal ray direction
  static void changeInternalRayDirection( const double direction[3] );

  //! Get the internal ray position
  static const double* getInternalRayPosition();

  //! Get the internal ray direction
  static const double* getInternalRayDirection();

  //! Check if the cell is a termination cell
  static bool isTerminationCell( const ModuleTraits::InternalCellHandle cell );

  //! Get the point location w.r.t. a given cell
  static PointLocation getPointLocation( 
                                 const Ray& ray,
				 const ModuleTraits::InternalCellHandle cell );
};

// Set the geometry handler instance
/*! \details The Root wrapper class has only static methods. Only one instance
 * will ever be active so this funciton call can be ignored.
 */
inline void ModuleInterface<Root>::setHandlerInstance( 
                                   const std::shared_ptr<Root>& root_instance )
{ /* ... */ }

// Do just in time initialization of interface members
/*! \details There is currently nothing in the interface that needs to be
 * initialized. The Root wrapper must be initialized before this point though.
 */
inline void ModuleInterface<Root>::initialize()
{
  // Make sure root is initialized
  testPrecondition( Root::isInitialized() );
}

// Enable support for multiple threads
inline void ModuleInterface<Root>::enableThreadSupport( 
                                                   const unsigned num_threads )
{ 
  // Make sure root is initialized
  testPrecondition( Root::isInitialized() );
  
  Root::enableThreadSupport( num_threads );
}

// Set the internal ray
inline void ModuleInterface<Root>::setInternalRay( 
                            const Ray& ray, 
                            const ModuleTraits::InternalCellHandle start_cell )
{
  // Make sure root is initialized
  testPrecondition( Root::isInitialized() );

  Root::setInternalRay( ray );
}

// Find the cell that contains a given start ray
inline ModuleTraits::InternalCellHandle 
ModuleInterface<Root>::findCellContainingStartRay( const Ray& ray )
{
  // Make sure root is initialized
  testPrecondition( Root::isInitialized() );
  
  return Root::findCellContainingExternalRay( ray );
}

// Find the cell that contains the internal ray
inline ModuleTraits::InternalCellHandle 
ModuleInterface<Root>::findCellContainingInternalRay()
{
  // Make sure root is initialized
  testPrecondition( Root::isInitialized() );
  
  return Root::findCellContainingInternalRay();
}

// Fire the internal ray through the geometry
/*! \details Root does not keep track of surfaces so this method will
 * always set the surface hit to 0.
 */
inline double ModuleInterface<Root>::fireInternalRay( 
                             ModuleTraits::InternalSurfaceHandle& surface_hit )
{
  // Make sure root is initialized
  testPrecondition( Root::isInitialized() );

  // Dummy return surface
  surface_hit = 0;
  
  // Fire the internal root ray
  return Root::fireInternalRay();
}

// Advance the internal ray to the cell boundary
/*! \details Root does not keep track of surfaces so this method will
 * always return a surface normal of {0,0,1}.
 */
inline bool ModuleInterface<Root>::advanceInternalRayToCellBoundary(
                                                     double surface_normal[3] )
{
  // Make sure the DagMC wrapper is initialized
  testPrecondition( Root::isInitialized() );

  // The dummy surface normal
  surface_normal[0] = 0.0;
  surface_normal[1] = 0.0;
  surface_normal[2] = 1.0;

  Root::advanceInternalRayToCellBoundary();

  return false;
}

// Advance the internal ray by a substep (< than the distance to boundary)
inline void ModuleInterface<Root>::advanceInternalRayBySubstep( 
                                                       const double step_size )
{
  // Make sure the DagMC wrapper is initialized
  testPrecondition( Root::isInitialized() );

  Root::advanceInternalRayBySubstep( step_size );
}

// Change the internal ray direction
inline void ModuleInterface<Root>::changeInternalRayDirection( 
                                                    const double direction[3] )
{
  // Make sure the DagMC wrapper is initialized
  testPrecondition( Root::isInitialized() );

  Root::changeInternalRayDirection( direction );
}

// Get the internal ray position
inline const double* ModuleInterface<Root>::getInternalRayPosition()
{
  // Make sure the DagMC wrapper is initialized
  testPrecondition( Root::isInitialized() );

  return Root::getInternalRayPosition();
}

// Get the internal ray direction
inline const double* ModuleInterface<Root>::getInternalRayDirection()
{
  // Make sure the DagMC wrapper is initialized
  testPrecondition( Root::isInitialized() );

  return Root::getInternalRayDirection();
}

// Check if the cell is a termination cell
inline bool ModuleInterface<Root>::isTerminationCell( 
                                  const ModuleTraits::InternalCellHandle cell )
{
  // Make sure the DagMC wrapper is initialized
  testPrecondition( Root::isInitialized() );

  return Root::isTerminationCell( cell );
}

// Get the point location w.r.t. a given cell
inline PointLocation ModuleInterface<Root>::getPointLocation( 
                                  const Ray& ray,
			          const ModuleTraits::InternalCellHandle cell )
{
  // Make sure the DagMC wrapper is initialized
  testPrecondition( Root::isInitialized() );
  
  return Root::getPointLocation( ray, cell );
}

// Check if a cell exists
inline bool ModuleInterface<Root>::doesCellExist( 
                               const ModuleTraits::InternalCellHandle cell_id )
{
  // Make sure the DagMC wrapper is initialized
  testPrecondition( Root::isInitialized() );
  
  return Root::doesCellExist( cell_id );
}

// Check if the surface exists
/*! \details Root does not keep track of surfaces so this method will
 * always return false.
 */
inline bool ModuleInterface<Root>::doesSurfaceExist( 
                         const ModuleTraits::InternalSurfaceHandle surface_id )
{
  // Make sure the DagMC wrapper is initialized
  testPrecondition( Root::isInitialized() );
  
  return false;
}

} // end Geometry namespace


#endif // end GEOMETRY_MODULE_INTERFACE_ROOT_HPP

//---------------------------------------------------------------------------//
// end Geometry_ModuleInterface_Root.hpp
//---------------------------------------------------------------------------//

