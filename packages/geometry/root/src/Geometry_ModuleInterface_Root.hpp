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

// Root Includes
#include <TObjArray.h>
#include <TObject.h>
#include <TGeoNavigator.h>
#include <TGeoNode.h>
#include <TGeoVolume.h>
#include <TGeoManager.h>
#include <TGeoMaterial.h>
#include <TGeoMedium.h>
#include <RtypesCore.h>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Geometry_ModuleInterfaceDecl.hpp"
#include "Geometry_Root.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_GlobalOpenMPSession.hpp"

namespace Geometry{

/*! The specialization of the GeometryModuleInterface class for the Root 
 * geometry handler.
 * \ingroup geometry_module
 */ 
template<>
class ModuleInterface<Root>
{
public:

  //! The external surface id class (used within the geometry handler)
  typedef ModuleTraits::InternalSurfaceHandle ExternalSurfaceId;
  //! The external cell id class (used within the geometry handler )
  typedef ModuleTraits::InternalCellHandle ExternalCellId;
  
  //! The external surface handle class (used within the geometry handler)
  typedef ModuleTraits::InternalSurfaceHandle ExternalSurfaceHandle;
  //! The external cell handle class (used within the geometry handler)
  typedef ModuleTraits::InternalCellHandle ExternalCellHandle;
  
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
  static void setHandlerInstance( const Root& root_instance );

  //! Do just in time initialization of interface members
  static void initialize();

  //! Enable support for multiple threads
  static void enableThreadSupport( const unsigned num_threads );

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

  //! Get the internal cell handle corresponding to the external cell handle
  static InternalCellHandle getInternalCellHandle( 
				      const ExternalCellHandle cell_external );

  //! Get the external surf. handle corresponding to the internal surf. handle
  static ExternalSurfaceHandle getExternalSurfaceHandle(
					 const InternalSurfaceHandle surface );
  

  //! Get the external cell handle corresponding to the internal cell handle
  static ExternalCellHandle getExternalCellHandle(
					       const InternalCellHandle cell );

private:
};

// Set the geometry handler instance
/*! \details The Root wrapper handles all root queries and is a singleton.
 */
inline void ModuleInterface<Root>::setHandlerInstance( 
                                                    const Root& root_instance )
{ /* ... */ }

// Initialize a new ray (after a collision)
/*! \details ROOT has a class, FindNextBoundary() which takes a position and
 *  direction to determine where the next boundary crossed is, but strict ray
 *  creation is not required.
 */
inline void ModuleInterface<Root>::newRay()
{ /* ... */ }

// Enable support for multiple threads
inline void ModuleInterface<Root>::enableThreadSupport( 
                                                   const unsigned num_threads )
{ 
  Root::enableThreadSupport( num_threads );
  
  // if( num_threads > 1 )
  // {
  //   THROW_EXCEPTION( std::logic_error,
  //                    "Error: The Root module interface does not support "
  //                    "multiple threads yet!");
  // }
}

// Find the cell that contains a given point (start of history)
inline ModuleInterface<Root>::InternalCellHandle 
ModuleInterface<Root>::findCellContainingPoint( const Ray& ray )
{
  Root::setInternalRay( ray );

  return Root::findCellContainingInternalRay();
}

// Find the cell that contains a given point (surface crossing)
inline ModuleInterface<Root>::InternalCellHandle 
ModuleInterface<Root>::findCellContainingPoint( 
		  const Ray& ray,
		  const ModuleInterface<Root>::InternalCellHandle current_cell,
                  const ModuleInterface<Root>::InternalSurfaceHandle surface )
{
  return Root::findCellContainingInternalRay();
}

// Fire a ray through the geometry
/*! \details Root does not keep track of surfaces so this method will
 * always set the surface hit to 0.
 */
inline void ModuleInterface<Root>::fireRay( 
                 const Ray& ray,
	         const ModuleInterface<Root>::InternalCellHandle& current_cell,
	         ModuleInterface<Root>::InternalSurfaceHandle& surface_hit,
                 double& distance_to_surface_hit )
{
  // Fire the internal root ray
  distance_to_surface_hit = Root::fireInternalRay();

  // Advance the internal root ray to the next boundary
  Root::advanceInternalRayToCellBoundary();

  // Dummy return surface
  surface_hit = 0;
}

// Get the point location w.r.t. a given cell
inline PointLocation ModuleInterface<Root>::getPointLocation( 
                         const Ray& ray,
			 const ModuleInterface<Root>::InternalCellHandle cell )
{
  return Root::getPointLocation( ray, cell );
}

// Calculate the surface normal at a point on the surface
/* \details Surfaces are not considered when dealing with Root. This function
 * will always return a normal of (0,0,1).
 */
inline void ModuleInterface<Root>::getSurfaceNormal( 
					   const InternalSurfaceHandle surface,
					   const double position[3],
					   double normal[3] )
{
  normal[0] = 0.0;
  normal[1] = 0.0;
  normal[2] = 1.0;
}

// Check if the cell is a termination cell
inline bool ModuleInterface<Root>::isTerminationCell( 
						const InternalCellHandle cell )
{ 
  return Root::isTerminationCell( cell );
}

// Get the volume of a cell
inline double ModuleInterface<Root>::getCellVolume( 
						const InternalCellHandle cell )
{
  return Root::getCellVolume( cell );  
}

// Get the surface area of a surface bounding a cell
/*! \details Currently Root cannot calculate the surface area of most bounded
 *  volumes.
 */ 
inline double ModuleInterface<Root>::getCellSurfaceArea( 
					   const InternalSurfaceHandle surface,
					   const InternalCellHandle )
{
  return 1.0;
}

// Check that an external surface handle exists
inline bool ModuleInterface<Root>::doesSurfaceExist(
                const ExternalSurfaceId surface )
{
  return false;
}

// Check that an external cell handle exists
inline bool ModuleInterface<Root>::doesCellExist( const ExternalCellId cell )
{
  return Root::doesCellExist( cell );
}

// Get the internal surf. handle corresponding to the external surf. handle
/*! \details Root uses integer handles so use implicit casting.
 */ 
inline ModuleInterface<Root>::InternalSurfaceHandle 
ModuleInterface<Root>::getInternalSurfaceHandle(
				 const ExternalSurfaceHandle surface_external )
{  
  return surface_external;
} 

// Get the internal cell handle corresponding to the external cell handle
/*! \details Root uses integer handles so use implicit casting.
 */ 
inline ModuleInterface<Root>::InternalCellHandle 
ModuleInterface<Root>::getInternalCellHandle( 
				       const ExternalCellHandle cell_external )
{ 
  return cell_external;
} 

// Get the external surf. handle corresponding to the internal surf. handle
/*! \details Root uses integer handles so use implicit casting.
 */ 
inline ModuleInterface<Root>::ExternalSurfaceHandle 
ModuleInterface<Root>::getExternalSurfaceHandle(
					  const InternalSurfaceHandle surface )
{ 
  return surface;
} 

// Get the external cell handle corresponding to the internal cell handle
/*! \details Root uses integer handles so use implicit casting.
 */ 
inline ModuleInterface<Root>::ExternalCellHandle 
ModuleInterface<Root>::getExternalCellHandle( const InternalCellHandle cell )
{ 
  return cell;
} 

} // end Geometry namespace


#endif // end GEOMETRY_MODULE_INTERFACE_ROOT_HPP

//---------------------------------------------------------------------------//
// end Geometry_ModuleInterface_Root.hpp
//---------------------------------------------------------------------------//

