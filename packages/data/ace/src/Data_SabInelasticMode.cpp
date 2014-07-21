//---------------------------------------------------------------------------//
//!
//! \file   Data_SabInelasticMode.cpp
//! \author Alex Robinson
//! \brief  S(a,b) inelastic mode enumeration helper functions
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <stdexcept>
#include <sstream>

// FRENSIE Includes
#include "Data_SabInelasticMode.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Data{

// Convert an unsigned in to a SabInelasticMode
SabInelasticMode convertUnsignedToSabInelasticMode( const unsigned mode )
{
  switch( mode )
  {
  case 3u: return EQUIPROBABLE_COSINE_INELASTIC_MODE;
  default:
    THROW_EXCEPTION( std::runtime_error,
		     "Error: S(a,b) inelastic scattering mode " << mode <<
		     " is not supported.\n" );
  }
}

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_SabInelasticMode.cpp
//---------------------------------------------------------------------------//
