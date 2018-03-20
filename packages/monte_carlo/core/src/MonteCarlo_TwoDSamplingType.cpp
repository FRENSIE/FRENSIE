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

// // Convert string to TwoDSamplingType
// TwoDSamplingType
// convertStringToTwoDSamplingType( const std::string raw_policy )
// {
//   if( raw_policy == "Correlated" || raw_policy == "correlated" || raw_policy == "CORRELATED" )
//     return CORRELATED_SAMPLING;
//   if( raw_policy == "Unit-base Correlated" || raw_policy == "unit-base correlated" || raw_policy == "UNIT-BASE CORRELATED" )
//     return UNIT_BASE_CORRELATED_SAMPLING;
//   else if( raw_policy == "Direct" || raw_policy == "direct" || raw_policy == "DIRECT" )
//     return DIRECT_SAMPLING;
//   else if( raw_policy == "Unit-base" || raw_policy == "unit-base" || raw_policy == "UNIT-BASE" )
//     return UNIT_BASE_SAMPLING;
//   else if( raw_policy == "Cumulative Points" || raw_policy == "cumulative points" || raw_policy == "CUMULATIVE POINTS" )
//     return CUMULATIVE_POINTS_SAMPLING;
//   else
//   {
//     THROW_EXCEPTION( std::runtime_error,
//                      "Error: 2D sampling type "
//                      << raw_policy <<
//                      " is not currently supported!" );
//   }
// }

} // end MonteCarlo namespace

namespace Utility{

// Convert a MonteCarlo::TwoDSamplingType to a string
std::string ToStringTraits<MonteCarlo::TwoDSamplingType>::toString( const MonteCarlo::TwoDSamplingType type )
{
  switch( type )
  {
  case MonteCarlo::CORRELATED_SAMPLING:
    return "Correlated";
  case MonteCarlo::UNIT_BASE_CORRELATED_SAMPLING:
    return "Unit-base Correlated";
  case MonteCarlo::DIRECT_SAMPLING:
    return "Direct";
  case MonteCarlo::UNIT_BASE_SAMPLING:
    return "Unit-base";
  case MonteCarlo::CUMULATIVE_POINTS_SAMPLING:
    return "Cumulative Points";
  default:
    THROW_EXCEPTION( Utility::StringConversionException,
                     "TwoDSamplingType " << (unsigned)type <<
                     " cannot be converted to a string!" );
  }
}

// Place the MonteCarlo::TwoDSamplingType in a stream
void ToStringTraits<MonteCarlo::TwoDSamplingType>::toStream( std::ostream& os, const MonteCarlo::TwoDSamplingType type )
{
  os << ToStringTraits<MonteCarlo::TwoDSamplingType>::toString( type );
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_TwoDSamplingType.cpp
//---------------------------------------------------------------------------//
