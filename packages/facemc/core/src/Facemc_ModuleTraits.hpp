//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ModuleTraits.hpp
//! \author Alex Robinson
//! \brief  Module traits class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_MODULE_TRAITS_HPP
#define FACEMC_MODULE_TRAITS_HPP

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

namespace Facemc{

/*! \brief  The module traits struct
 *
 * This struct specifies the types used by each module interface for 
 * representing Ids and other important information inside of FACEMC. 
 */
struct ModuleTraits
{
  //! The internal source handle type
  typedef unsigned long long InternalSourceHandle;
  //! The internal estimator handle type
  typedef unsigned long long InternalEstimatorHandle;
  //! The internal material handle type
  typedef unsigned long long InternalMaterialHandle;

  //! The invalid source handle value
  static const InternalSourceHandle invalid_internal_source_handle;
  
  //! The invalid estimator handle value
  static const InternalEstimatorHandle invalid_internal_estimator_handle;
  
  //! The invalid material handle value
  static const InternalMaterialHandle invalid_internal_material_handle;
};

} // end Facemc namespace

#endif // end FACEMC_MODULE_TRAITS_HPP

//---------------------------------------------------------------------------//
// end Facemc_ModuleTraits.hpp
//---------------------------------------------------------------------------//
