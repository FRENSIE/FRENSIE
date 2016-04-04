//---------------------------------------------------------------------------//
//!
//! \file   Geometry_ModuleTraits.hpp
//! \author Alex Robinson
//! \brief  Geometry module traits class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_MODULE_TRAITS_HPP
#define GEOMETRY_MODULE_TRAITS_HPP

// Std Lib Includes
#include <limits>

/*! \defgroup geometry_module_traits Geometry Module Traits
 * \ingroup traits
 *
 * The geometry module has two types associated with it. The first type is 
 * the same across all module interface specializations and is used to 
 * represent cell handles internally (seen by objects in FRENSIE framework). The
 * second type can be different for every module interface specialization and
 * is used by an external package to represent cell handles.  
 */ 

namespace Geometry{

/*! \brief  The geometry module traits struct
 *
 * This struct specifies the internal type used by the geometry module 
 * interface for representing cell handles.
 */
struct ModuleTraits
{
  //! The internal cell handle type
  typedef unsigned long long InternalCellHandle;
  //! The internal surface handle type
  typedef unsigned long long InternalSurfaceHandle;

  //! The invalid cell handle value
  static const InternalCellHandle invalid_internal_cell_handle; 
  
  //! The invalid surface handle value
  static const InternalSurfaceHandle invalid_internal_surface_handle; 
};

} // end FRENSIE namespace

#endif // end GEOMETRY_MODULE_TRAITS_HPP

//---------------------------------------------------------------------------//
// end Geometry_ModuleTraits.hpp
//---------------------------------------------------------------------------//
