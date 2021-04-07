//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationSamplingType.hpp
//! \author Luke Kersting
//! \brief  Electroionization sampling helper function definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationSamplingType.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{

// Convert a MonteCarlo:: to a string
std::string ToStringTraits<MonteCarlo::ElectroionizationSamplingType>::toString( const MonteCarlo::ElectroionizationSamplingType type )
{
  switch( type )
  {
    case MonteCarlo::KNOCK_ON_SAMPLING:
      return "Knock-on Electroionization Sampling";
    case MonteCarlo::OUTGOING_ENERGY_SAMPLING:
      return "Outgoing Energy Electroionization Sampling";
    case MonteCarlo::OUTGOING_ENERGY_RATIO_SAMPLING:
      return "Outgoing Energy Ratio Electroionization Sampling";
    default:
    {
      THROW_EXCEPTION( std::logic_error,
                       "Unknown Electroionization sampling type "
                       "encountered!" );
    }
  }
}

// Place the MonteCarlo:: in a stream
void ToStringTraits<MonteCarlo::ElectroionizationSamplingType>::toStream( std::ostream& os, const MonteCarlo::ElectroionizationSamplingType type )
{
os << ToStringTraits<MonteCarlo::ElectroionizationSamplingType>::toString( type );
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationSamplingType.hpp
//---------------------------------------------------------------------------//
