//---------------------------------------------------------------------------//
//!
//! \file   ModuleTraits.hpp
//! \author Alex Robinson
//! \brief  Module traits class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MODULE_TRAITS_HPP
#define MODULE_TRAITS_HPP

// Std Lib Includes
#include <limits>

/*! \defgroup module_traits Module Traits
 * \ingroup traits
 *
 * Every module used in particle simulations uses a specific type in its
 * interface for representing Ids and other important information. All of
 * those classes have been pulled into a common location to provide a single
 * point of control.
 */ 

namespace FACEMC{

namespace Traits{

/*! \brief  The module traits struct
 *
 * This struct specifies the types used by each module interface for 
 * representing Ids and other important information inside of FACEMC. 
 */
struct ModuleTraits
{
  //! The internal cell handle type
  typedef unsigned long long InternalCellHandle;
  //! The internal surface handle type
  typedef unsigned long long InternalSurfaceHandle;
  //! The internal estimator handle type
  typedef unsigned long long InternalEstimatorHandle;
  //! The internal material handle type
  typedef unsigned long long InternalMaterialHandle;
  
  //! The invalid cell handle value
  static const InternalCellHandle invalid_internal_cell_handle; 
  
  //! The invalid surface handle value
  static const InternalSurfaceHandle invalid_internal_surface_handle; 
  
  //! The invalid estimator handle value
  static const InternalEstimatorHandle invalid_internal_estimator_handle;
  
  //! The invalid material handle value
  static const InternalMaterialHandle invalid_internal_material_handle;
};

} // end Traits namespace

} // end FACEMC namespace

#endif // end MODULE_TRAITS_HPP

//---------------------------------------------------------------------------//
// end ModuleTraits.hpp
//---------------------------------------------------------------------------//
