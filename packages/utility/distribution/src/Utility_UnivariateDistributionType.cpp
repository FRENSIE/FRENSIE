//---------------------------------------------------------------------------//
//!
//! \file   Utility_UnivariateDistributionType.cpp
//! \author Alex Robinson
//! \brief  One dimensional distribution type enumeration helper function defs.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <sstream>

// FRENSIE Includes
#include "Utility_UnivariateDistributionType.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Utility{

// Convert a Utility::UnivariateDistributionType to a string
std::string ToStringTraits<UnivariateDistributionType>::toString(
                                               const UnivariateDistributionType obj )
{
  std::ostringstream oss;

  ToStringTraits<UnivariateDistributionType>::toStream( oss, obj );

  return oss.str();
}

// Place the Utility::UnivariateDistributionType in a stream
void ToStringTraits<UnivariateDistributionType>::toStream(
                                               std::ostream& os,
                                               const UnivariateDistributionType obj )
{
  switch( obj )
  {
  case COUPLED_ELASTIC_DISTRIBUTION: os << "Coupled Elastic Distribution"; return;
  case DELTA_DISTRIBUTION: os << "Delta Distribution"; return;
  case DISCRETE_DISTRIBUTION: os << "Discrete Distribution"; return;
  case EQUIPROBABLE_BIN_DISTRIBUTION: os << "Equiprobable Bin Distribution"; return;
  case EVAPORATION_DISTRIBUTION: os << "Evaporation Distribution"; return;
  case EXPONENTIAL_DISTRIBUTION: os << "Exponential Distribution"; return;
  case HISTOGRAM_DISTRIBUTION: os << "Histogram Distribution"; return;
  case HYBRID_ELASTIC_DISTRIBUTION: os << "Hybrid Elastic Distribution"; return;
  case MAXWELL_FISSION_DISTRIBUTION: os << "Maxwell Fission Distribution"; return;
  case NORMAL_DISTRIBUTION: os << "Normal Distribution"; return;
  case POLYNOMIAL_DISTRIBUTION: os << "Polynomial Distribution"; return;
  case POWER_DISTRIBUTION: os << "Power Distribution"; return;
  case TABULAR_DISTRIBUTION: os << "Tabular Distribution"; return;
  case TABULAR_CDF_DISTRIBUTION: os << "Tabular CDF Distribution"; return;
  case UNIFORM_DISTRIBUTION: os << "Uniform Distribution"; return;
  case WATT_DISTRIBUTION: os << "Watt Distribution"; return;
    
  default:
  {
    THROW_EXCEPTION( std::logic_error,
                     "An unknown UnivariateDistribution type was encountered! "
                     "Please report this to the developers!" );
  }
  }
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_UnivariateDistributionType.cpp
//---------------------------------------------------------------------------//
