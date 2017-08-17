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
#include "Utility_ExceptionTestMacros.hpp"

namespace Utility{

// Convert the OneDDistribution type to a string
std::string convertOneDDistributionTypeToString(
					      const OneDDistributionType type )
{
  switch( type )
  {
  case DELTA_DISTRIBUTION: return "Delta Distribution";
  case DISCRETE_DISTRIBUTION: return "Discrete Distribution";
  case ELASTIC_ELECTRON_DISTRIBUTION: return "Elastic Electron Distribution";
  case EXPONENTIAL_DISTRIBUTION: return "Exponential Distribution";
  case EVAPORATION_DISTRIBUTION: return "Evaporation Distribution";
  case HISTOGRAM_DISTRIBUTION: return "Histogram Distribution";
  case MAXWELLFISSION_DISTRIBUTION: return "Maxwell Fission Distribution";
  case WATT_DISTRIBUTION: return "Watt Distribution";
  case EQUIPROBABLE_BIN_DISTRIBUTION: return "32 Equiprobable Bin Distribution";
  case NORMAL_DISTRIBUTION: return "Normal Distribution";
  case POWER_1_DISTRIBUTION: return "Power 1 Distribution";
  case POWER_2_DISTRIBUTION: return "Power 2 Distribution";
  case POWER_N_DISTRIBUTION: return "Power N Distribution";
  case TABULAR_DISTRIBUTION: return "Tabular Distribution";
  case UNIFORM_DISTRIBUTION: return "Uniform Distribution";
  case POLYNOMIAL_DISTRIBUTION: return "Polynomial Distribution";
  case HYDROGEN_FORM_FACTOR_DISTRIBUTION: return "Hydrogen Form Factor Distribution";
  case CUTOFF_ELASTIC_DISTRIBUTION: return "Cutoff Elastic Distribution";
  case ANALOG_ELASTIC_DISTRIBUTION: return "Analog Elastic Distribution";
  default:
    THROW_EXCEPTION( std::logic_error,
		     "The distribution type is missin a name. Please add it!");
  }
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_OneDDistributionType.cpp
//---------------------------------------------------------------------------//
