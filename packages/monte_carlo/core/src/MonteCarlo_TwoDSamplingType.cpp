//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_TwoDSamplingType.cpp
//! \author Luke Kersting
//! \brief  TwoDSampling type helper definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_ExceptionTestMacros.hpp"
#include "MonteCarlo_TwoDSamplingType.hpp"

namespace MonteCarlo{

// Convert the TwoDSamplingType to a string
std::string convertTwoDSamplingTypeToString( const TwoDSamplingType type )
{
  switch( type )
  {
  case CORRELATED_SAMPLING:
    return "Correlated";
  case EXACT_SAMPLING:
    return "Exact";
  case STOCHASTIC_SAMPLING:
    return "Stochastic";
  default:
    THROW_EXCEPTION( std::logic_error,
                     "Error: TwoDSamplingType " << (unsigned)type <<
                     " cannot be converted to a string!" );
  }
}

// Convert string to TwoDSamplingType
TwoDSamplingType
convertStringToTwoDSamplingType( const std::string raw_policy )
{
  if( raw_policy == "Correlated" || raw_policy == "correlated" || raw_policy == "CORRELATED" )
    return CORRELATED_SAMPLING;
  else if( raw_policy == "Exact" || raw_policy == "exact" || raw_policy == "EXACT" )
    return EXACT_SAMPLING;
  else if( raw_policy == "Stochastic" || raw_policy == "stochastic" || raw_policy == "STOCHASTIC" )
    return STOCHASTIC_SAMPLING;
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Error: 2D sampling type "
                     << raw_policy <<
                     " is not currently supported!" );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_TwoDSamplingType.cpp
//---------------------------------------------------------------------------//
