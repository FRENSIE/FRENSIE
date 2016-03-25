//---------------------------------------------------------------------------//
//!
//! \file   Geometry_ModuleInterface_DagMC.hpp
//! \author Alex Robinson
//! \brief  DagMC specialization decl. of the geometry ModuleInterface class
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_MODULE_INTERFACE_DAGMC_HPP
#define GEOMETRY_MODULE_INTERFACE_DAGMC_HPP

// FRENSIE Includes
#include "Geometry_ModuleInterfaceDecl.hpp"
#include "Geometry_DagMC.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Geometry{

/*! The specialization of the GeometryModuleInterface class for the DagMC
 * geometry handler.
 * \ingroup geometry_module
 */
template<>
class ModuleInterface<DagMC>
{

public: 
  
  //! Set the geometry handler instance
  static void setHandlerInstance( 
                              const std::shared_ptr<DagMC>& handler_instance );

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

  //! Find the cell that contain the internal ray
  static ModuleTraits::InternalCellHandle findCellContainingInternalRay();

  //! Fire the internal ray through the geometry
  static double fireInternalRay( 
                            ModuleTraits::InternalSurfaceHandle& surface_hit );

  //! Advance the internal ray to the cell boundary
  static bool advanceInternalRayToCellBoundary( double surface_normal[3] );

  //! Advance the internal ray by a substep (< than the distance to boundary)
  static void advanceInternalRayBySubstep( const double step_size );

  //! Change the internal ray direction
  static void changeInternalRayDirection( const double direction[3] );

  //! Get the internal ray direction
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
/*! \details The DagMC wrapper class has only static methods. Only one instance
 * will ever be active so this function call can be ignored.
 */
inline void ModuleInterface<DagMC>::setHandlerInstance( 
                               const std::shared_ptr<DagMC>& handler_instance )
{ /* ... */ }

// Do just in time initialization of interface members
/*! \details There is currently nothing in the interface that needs to be
 * initialized. The DagMC wrapper must be initialized before this point though.
 */
inline void ModuleInterface<DagMC>::initialize()
{
  // Make sure the DagMC wrapper is initialized
  testPrecondition( DagMC::isInitialized() );
}

// Enable support for multiple threads
inline void ModuleInterface<DagMC>::enableThreadSupport( 
                                                   const unsigned num_threads )
{
  // Make sure the DagMC wrapper is initialized
  testPrecondition( DagMC::isInitialized() );
  
  DagMC::enableThreadSupport( num_threads );
}

// Set the internal ray
inline void ModuleInterface<DagMC>::setInternalRay( 
                            const Ray& ray,
                            const ModuleTraits::InternalCellHandle start_cell )
{
  // Make sure the DagMC wrapper is initialized
  testPrecondition( DagMC::isInitialized() );

  DagMC::setInternalRay( ray, start_cell, false );
}

// Find the cell that contains a given start ray
/*! \details This function will first check a found cell cache for the
 * cell that contains the ray. If none of the cells in the cache contain
 * the ray all of the cells will be searched. Any new cells found will be
 * added to the found cell cache. 
 */
inline ModuleTraits::InternalCellHandle 
ModuleInterface<DagMC>::findCellContainingStartRay( const Ray& ray )
{
  // Make sure the DagMC wrapper is initialized
  testPrecondition( DagMC::isInitialized() );

  return DagMC::findAndCacheCellContainingExternalRay( ray );
}

// Find the cell that contain the internal ray
inline ModuleTraits::InternalCellHandle 
ModuleInterface<DagMC>::findCellContainingInternalRay()
{
  // Make sure the DagMC wrapper is initialized
  testPrecondition( DagMC::isInitialized() );

  return DagMC::findCellContainingInternalRay();
}

// Fire the internal ray through the geometry
inline double ModuleInterface<DagMC>::fireInternalRay( 
                             ModuleTraits::InternalSurfaceHandle& surface_hit )
{
  // Make sure the DagMC wrapper is initialized
  testPrecondition( DagMC::isInitialized() );

  return DagMC::fireInternalRay( surface_hit );
}

// Advance the internal ray to the cell boundary
inline bool ModuleInterface<DagMC>::advanceInternalRayToCellBoundary(
                                                     double surface_normal[3] )
{
  // Make sure the DagMC wrapper is initialized
  testPrecondition( DagMC::isInitialized() );

  return DagMC::advanceInternalRayToCellBoundary( surface_normal );
}

// Advance the internal ray by a substep (< than the distance to boundary)
inline void ModuleInterface<DagMC>::advanceInternalRayBySubstep( 
                                                       const double step_size )
{
  // Make sure the DagMC wrapper is initialized
  testPrecondition( DagMC::isInitialized() );

  DagMC::advanceInternalRayBySubstep( step_size );
}

// Change the internal ray direction
inline void ModuleInterface<DagMC>::changeInternalRayDirection( 
                                                    const double direction[3] )
{
  // Make sure the DagMC wrapper is initialized
  testPrecondition( DagMC::isInitialized() );

  DagMC::changeInternalRayDirection( direction );
}

// Get the internal ray position
inline const double* ModuleInterface<DagMC>::getInternalRayPosition()
{
  // Make sure the DagMC wrapper is initialized
  testPrecondition( DagMC::isInitialized() );

  return DagMC::getInternalRayPosition();
}

// Get the internal ray direction
inline const double* ModuleInterface<DagMC>::getInternalRayDirection()
{
  // Make sure the DagMC wrapper is initialized
  testPrecondition( DagMC::isInitialized() );

  return DagMC::getInternalRayDirection();
}

// Check if the cell is a termination cell
inline bool ModuleInterface<DagMC>::isTerminationCell( 
                                  const ModuleTraits::InternalCellHandle cell )
{
  // Make sure the DagMC wrapper is initialized
  testPrecondition( DagMC::isInitialized() );

  return DagMC::isTerminationCell( cell );
}

// Get the point location w.r.t. a given cell
inline PointLocation ModuleInterface<DagMC>::getPointLocation( 
                                  const Ray& ray,
                                  const ModuleTraits::InternalCellHandle cell )
{
  // Make sure the DagMC wrapper is initialized
  testPrecondition( DagMC::isInitialized() );

  return DagMC::getPointLocation( ray, cell );
}

// Check if a cell exists
inline bool ModuleInterface<DagMC>::doesCellExist(
                               const ModuleTraits::InternalCellHandle cell_id )
{
  // Make sure the DagMC wrapper is initialized
  testPrecondition( DagMC::isInitialized() );

  return DagMC::doesCellExist( cell_id );
}

// Check if the surface exists
inline bool ModuleInterface<DagMC>::doesSurfaceExist( 
                         const ModuleTraits::InternalSurfaceHandle surface_id )
{
  // Make sure the DagMC wrapper is initialized
  testPrecondition( DagMC::isInitialized() );

  return DagMC::doesSurfaceExist( surface_id );
}

} // end Geometry namespace

#endif // end GEOMETRY_MODULE_INTERFACE_DAGMC_HPP

//---------------------------------------------------------------------------//
// end Geometry_ModuleInterface_DagMC.hpp
//---------------------------------------------------------------------------//
