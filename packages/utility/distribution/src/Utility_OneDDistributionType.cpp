//---------------------------------------------------------------------------//
//!
//! \file   Utility_OneDDistributionType.cpp
//! \author Alex Robinson
//! \brief  One dimensional distribution type enumeration helper function defs.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <sstream>

// FRENSIE Includes
#include "Utility_OneDDistributionType.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Utility{

// Convert a Utility::OneDDistributionType to a string
std::string ToStringTraits<OneDDistributionType>::toString(
                                               const OneDDistributionType obj )
{
  std::ostringstream oss;

  ToStringTraits<OneDDistributionType>::toStream( oss, obj );

  return oss.str();
}

// Place the Utility::OneDDistributionType in a stream
void ToStringTraits<OneDDistributionType>::toStream(
                                               std::ostream& os,
                                               const OneDDistributionType obj )
{
  switch( obj )
  {
  case DELTA_DISTRIBUTION: os << "Delta Distribution"; return;
  case DISCRETE_DISTRIBUTION: os << "Discrete Distribution"; return;
  case EQUIPROBABLE_BIN_DISTRIBUTION: os << "Equiprobable Bin Distribution"; return;
  case EVAPORATION_DISTRIBUTION: os << "Evaporation Distribution"; return;
  case EXPONENTIAL_DISTRIBUTION: os << "Exponential Distribution"; return;
  case HISTOGRAM_DISTRIBUTION: os << "Histogram Distribution"; return;
  case MAXWELL_FISSION_DISTRIBUTION: os << "Maxwell Fission Distribution"; return;
  case NORMAL_DISTRIBUTION: os << "Normal Distribution"; return;
  case POLYNOMIAL_DISTRIBUTION: os << "Polynomial Distribution"; return;
  case POWER_DISTRIBUTION: os << "Power Distribution"; return;
  case TABULAR_DISTRIBUTION: os << "Tabular Distribution"; return;
  case UNIFORM_DISTRIBUTION: os << "Uniform Distribution"; return;
  case WATT_DISTRIBUTION: os << "Watt Distribution"; return;
    
  default:
  {
    THROW_EXCEPTION( std::logic_error,
                     "An unknown OneDDistribution type was encountered! "
                     "Please report this to the developers!" );
  }
  }
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_OneDDistributionType.cpp
//---------------------------------------------------------------------------//
