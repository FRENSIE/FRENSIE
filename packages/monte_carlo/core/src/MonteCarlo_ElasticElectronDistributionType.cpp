//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElasticElectronDistributionType.cpp
//! \author Luke Kersting
//! \brief  Elastic electron distribution type helper function definitions.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <stdexcept>

// FRENSIE Includes
#include "MonteCarlo_ElasticElectronDistributionType.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Convert a ElasticElectronDistributionType enum to a string
std::string convertElasticElectronDistributionTypeToString(
                      const ElasticElectronDistributionType reaction )
{
  switch( reaction )
  {
  case COUPLED_DISTRIBUTION:
    return "Coupled Distribution";
  case DECOUPLED_DISTRIBUTION:
    return "Decoupled Distribution";
  case HYBRID_DISTRIBUTION:
    return "Hybrid Distribution";
  case CUTOFF_DISTRIBUTION:
    return "Cutoff Distribution";
  case SCREENED_RUTHERFORD_DISTRIBUTION:
    return "Screened Rutherford Distribution";
  default:
    THROW_EXCEPTION( std::logic_error,
                     "Error: cannot convert the Elastic electron "
                     "distribution type to a string!" );
  }
}

// Convert a CoupledElasticSamplingMethod enum to a string
std::string convertCoupledElasticSamplingMethodToString(
                      const CoupledElasticSamplingMethod method )
{
  switch( method )
  {
  case ONE_D_UNION:
    return "One D Union";
  case TWO_D_UNION:
    return "Two D Union";
  case SIMPLIFIED_UNION:
    return "Simplified Union";
  default:
    THROW_EXCEPTION( std::logic_error,
                     "Error: cannot convert the Coupled Elastic "
                     "electron sampling method to a string!" );
  }
}

// Convert a string to a CoupledElasticSamplingMethod
CoupledElasticSamplingMethod convertStringToCoupledElasticSamplingMethod(
                      const std::string raw_method )
{
  if( raw_method == "One D Union" )
    return ONE_D_UNION;
  else if( raw_method == "Two D Union" )
    return TWO_D_UNION;
  else if( raw_method == "Simplified Union" )
    return SIMPLIFIED_UNION;
  else
  {
    THROW_EXCEPTION( std::logic_error,
                     "Error: cannot convert the string to a "
                     "Coupled Elastic electron sampling method!" );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElasticElectronDistributionType.cpp
//---------------------------------------------------------------------------//

