//---------------------------------------------------------------------------//
//!
//! \file   Utility_OneDDistributionType.cpp
//! \author Alex Robinson
//! \brief  One dimensional distribution type helper function definitions
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <stdexcept>

// FRENSIE Includes
#include "Utility_OneDDistributionType.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_EquiprobableBinDistribution.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Utility{

// Convert the OneDDistribution type to a string
std::string convertOneDDistributionTypeToString(
					      const OneDDistributionType type )
{
  switch( type )
  {
  case DELTA_DISTRIBUTION: return DeltaDistribution::getDistributionTypeName();
  case DISCRETE_DISTRIBUTION: return DiscreteDistribution::getDistributionTypeName();
  case EXPONENTIAL_DISTRIBUTION: return "Exponential Distribution";
  case EVAPORATION_DISTRIBUTION: return "Evaporation Distribution";
  case HISTOGRAM_DISTRIBUTION: return "Histogram Distribution";
  case MAXWELLFISSION_DISTRIBUTION: return "Maxwell Fission Distribution";
  case WATT_DISTRIBUTION: return "Watt Distribution";
  case EQUIPROBABLE_BIN_DISTRIBUTION: return EquiprobableBinDistribution::getDistributionTypeName();
  case NORMAL_DISTRIBUTION: return "Normal Distribution";
  case POWER_1_DISTRIBUTION: return "Power 1 Distribution";
  case POWER_2_DISTRIBUTION: return "Power 2 Distribution";
  case POWER_N_DISTRIBUTION: return "Power N Distribution";
  case TABULAR_DISTRIBUTION: return "Tabular Distribution";
  case UNIFORM_DISTRIBUTION: return UniformDistribution::getDistributionTypeName();
  case POLYNOMIAL_DISTRIBUTION: return "Polynomial Distribution";
  case HYDROGEN_FORM_FACTOR_DISTRIBUTION: return "Hydrogen Form Factor Distribution";
  default:
    THROW_EXCEPTION( std::logic_error,
		     "The distribution type is missing a name. Please add it!");
  }
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_OneDDistributionType.cpp
//---------------------------------------------------------------------------//
