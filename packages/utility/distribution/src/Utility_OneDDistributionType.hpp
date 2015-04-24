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

namespace Utility{

enum OneDDistributionType{
  DELTA_DISTRIBUTION,
  DISCRETE_DISTRIBUTION,
  EXPONENTIAL_DISTRIBUTION,
  HISTOGRAM_DISTRIBUTION,
  EQUIPROBABLE_BIN_DISTRIBUTION,
  NORMAL_DISTRIBUTION,
  POWER_1_DISTRIBUTION,
  POWER_2_DISTRIBUTION,
  POWER_N_DISTRIBUTION,
  TABULAR_DISTRIBUTION,
  UNIFORM_DISTRIBUTION,
  POLYNOMIAL_DISTRIBUTION,
  KLEIN_NISHINA_DISTRIBUTION,
  INCOHERENT_DISTRIBUTION,
  ADJOINT_KLEIN_NISHINA_DISTRIBUTION,
  HYDROGEN_FORM_FACTOR_DISTRIBUTION
};

//! Convert the OneDDistribution type to a string
std::string convertOneDDistributionTypeToString( 
					     const OneDDistributionType type );

} // end Utility namespace

#endif // end UTILITY_ONE_D_DISTRIBUTION_TYPE_HPP

//---------------------------------------------------------------------------//
// end Utility_OneDDistributionType.hpp
//---------------------------------------------------------------------------//
