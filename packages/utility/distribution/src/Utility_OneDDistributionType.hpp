//---------------------------------------------------------------------------//
//!
//! \file   Utility_OneDDistributionType.hpp
//! \author Alex Robinson
//! \brief  One dimensional distribution type enumeration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ONE_D_DISTRIBUTION_TYPE_HPP
#define UTILITY_ONE_D_DISTRIBUTION_TYPE_HPP

// Std Lib Includes
#include <string>

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"

namespace Utility{

/*! The one-dimensional distribution types
 * \ingroup one_d_distributions
 */
enum OneDDistributionType{
  DELTA_DISTRIBUTION,
  DISCRETE_DISTRIBUTION,
  ELASTIC_ELECTRON_DISTRIBUTION,
  EQUIPROBABLE_BIN_DISTRIBUTION,
  EVAPORATION_DISTRIBUTION,
  EXPONENTIAL_DISTRIBUTION,
  HISTOGRAM_DISTRIBUTION,
  MAXWELLFISSION_DISTRIBUTION,
  NORMAL_DISTRIBUTION,
  POLYNOMIAL_DISTRIBUTION,
  POWER_1_DISTRIBUTION,
  POWER_2_DISTRIBUTION,
  POWER_N_DISTRIBUTION,
  TABULAR_DISTRIBUTION,
  UNIFORM_DISTRIBUTION,
  WATT_DISTRIBUTION
};

} // end Utility namespace

#endif // end UTILITY_ONE_D_DISTRIBUTION_TYPE_HPP

//---------------------------------------------------------------------------//
// end Utility_OneDDistributionType.hpp
//---------------------------------------------------------------------------//
