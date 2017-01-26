//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ModuleTraits.hpp
//! \author Alex Robinson
//! \brief  Module traits class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_MODULE_TRAITS_HPP
#define MONTE_CARLO_MODULE_TRAITS_HPP

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

namespace MonteCarlo{

/*! \brief  The module traits struct
 *
 * This struct specifies the types used by each module interface for
 * representing Ids and other important information inside of MONTE_CARLO.
 */
struct ModuleTraits
{
  //! The internal region of interest (ROI) handle type
  typedef unsigned int InternalROIHandle;
  //! The internal event observer handle type
  typedef unsigned long long InternalEventObserverHandle;
  //! The internal material handle type
  typedef unsigned long long InternalMaterialHandle;

  //! The internal counter type
  typedef unsigned long long InternalCounter;

  //! The invalid ROI handle value
  static const InternalROIHandle invalid_internal_roi_handle;

  //! The invalid estimator handle value
  static const InternalEventObserverHandle invalid_internal_event_observer_handle;

  //! The invalid material handle value
  static const InternalMaterialHandle invalid_internal_material_handle;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_MODULE_TRAITS_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ModuleTraits.hpp
//---------------------------------------------------------------------------//
