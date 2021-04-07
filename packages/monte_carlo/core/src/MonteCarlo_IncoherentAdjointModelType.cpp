//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IncoherentAdjointModelType.hpp
//! \author Alex Robinson
//! \brief  The incoherent adjoint model type helper function definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_IncoherentAdjointModelType.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{
  
// Convert a MonteCarlo::IncoherentAdjointModelType to a string
std::string ToStringTraits<MonteCarlo::IncoherentAdjointModelType>::toString( const MonteCarlo::IncoherentAdjointModelType type )
{
  switch( type )
  {
  case MonteCarlo::KN_INCOHERENT_ADJOINT_MODEL:
    return "Klein-Nishina Adjoint Model";
  case MonteCarlo::WH_INCOHERENT_ADJOINT_MODEL:
    return "Waller-Hartree Adjoint Model" ;
  case MonteCarlo::IMPULSE_INCOHERENT_ADJOINT_MODEL:
    return "Impulse Adjoint Model";
  case MonteCarlo::DB_IMPULSE_INCOHERENT_ADJOINT_MODEL:
    return "Doppler Broadened Impulse Adjoint Model";
  default:
  {
    THROW_EXCEPTION( std::logic_error,
                     "Unkown incoherent adjoint model encountered!" );
  }
  }
}

// Place the MonteCarlo:: in a stream
void ToStringTraits<MonteCarlo::IncoherentAdjointModelType>::toStream( std::ostream& os, const MonteCarlo::IncoherentAdjointModelType type )
{
  os << ToStringTraits<MonteCarlo::IncoherentAdjointModelType>::toString( type );
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentAdjointModelType.cpp
//---------------------------------------------------------------------------//
