//---------------------------------------------------------------------------//
//!
//! \file   Utility_OneDDistributionType.hpp
//! \author Alex Robinson
//! \brief  One dimensional distribution type enumeration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ONE_D_DISTRIBUTION_TYPE_HPP
#define UTILITY_ONE_D_DISTRIBUTION_TYPE_HPP

namespace Utility{

enum OneDDistributionType{
  DELTA_DISTRIBUTION,
  DISCRETE_DISTRIBUTION,
  EXPONENTIAL_DISTRIBUTION,
  HISTOGRAM_DISTRIBUTION,
  THIRTY_TWO_EQUIPROBABLE_BIN_DISTRIBUTION,
  NORMAL_DISTRIBUTION,
  POWER_1_DISTRIBUTION,
  POWER_2_DISTRIBUTION,
  POWER_N_DISTRIBUTION,
  TABULAR_DISTRIBUTION,
  UNIFORM_DISTRIBUTION,
  POLYNOMIAL_DISTRIBUTION,
  KLEIN_NISHINA_DISTRIBUTION
};

} // end Utility namespace

#endif // end UTILITY_ONE_D_DISTRIBUTION_TYPE_HPP

//---------------------------------------------------------------------------//
// end Utility_OneDDistributionType.hpp
//---------------------------------------------------------------------------//
