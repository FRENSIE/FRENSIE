//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_TwoDSamplingType.hpp
//! \author Luke Kersting
//! \brief  TwoDSampling type enumeration and helper declarations
//!
//---------------------------------------------------------------------------//

#ifndef MONTECARLO_TWO_D_SAMPLING_TYPE_HPP
#define MONTECARLO_TWO_D_SAMPLING_TYPE_HPP

// Std Lib Includes
#include <string>
#include <iostream>

namespace MonteCarlo{

//! The two d Sampling types
enum TwoDSamplingType{
  CORRELATED_SAMPLING = 1,
  EXACT_SAMPLING = 2,
  STOCHASTIC_SAMPLING = 3,
};

//! Convert the TwoDSamplingType to a string
std::string convertTwoDSamplingTypeToString( const TwoDSamplingType type );

//! Convert string to TwoDSamplingType
TwoDSamplingType convertStringToTwoDSamplingType( const std::string raw_policy );

//! Stream operator for printing TwoDSamplingType enums
inline std::ostream& operator<<( std::ostream& os,
                                 const TwoDSamplingType type )
{
  os << convertTwoDSamplingTypeToString( type );

  return os;
}
} // end MonteCarlo namespace

#endif // end MONTECARLO_TWO_D_SAMPLING_TYPE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_TwoDSamplingType.hpp
//---------------------------------------------------------------------------//
