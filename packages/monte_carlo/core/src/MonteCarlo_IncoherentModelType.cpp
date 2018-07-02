//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IncoherentModelType.cpp
//! \author Alex Robinson
//! \brief  Photon Doppler broadening model helper function definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_IncoherentModelType.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{

// Convert a MonteCarlo::IncoherentModelType to a string
std::string ToStringTraits<MonteCarlo::IncoherentModelType>::toString( const MonteCarlo::IncoherentModelType type )
{
  switch( type )
  {
  case MonteCarlo::KN_INCOHERENT_MODEL:
    return "Klein-Nishina Model";
  case MonteCarlo::WH_INCOHERENT_MODEL:
    return "Waller-Hartree Model";
  case MonteCarlo::IMPULSE_INCOHERENT_MODEL:
    return "Impulse Model";
  case MonteCarlo::DECOUPLED_HALF_PROFILE_DB_HYBRID_INCOHERENT_MODEL:
    return "DHP Doppler Broadened Hybrid Model";
  case MonteCarlo::DECOUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL:
    return "DFP Doppler Broadened Hybrid Model";
  case MonteCarlo::COUPLED_HALF_PROFILE_DB_HYBRID_INCOHERENT_MODEL:
    return "CHP Doppler Broadened Hybrid Model";
  case MonteCarlo::COUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL:
    return "CFP Doppler Broadened Hybrid Model";
  case MonteCarlo::FULL_PROFILE_DB_IMPULSE_INCOHERENT_MODEL:
    return "FP Doppler Broadened Impulse Model";
  default:
    THROW_EXCEPTION( std::logic_error,
		     "Unknown incoherent model encountered!" );
  }
}

// Place the MonteCarlo::IncoherentModelType in a stream
void ToStringTraits<MonteCarlo::IncoherentModelType>::toStream( std::ostream& os, const MonteCarlo::IncoherentModelType type )
{
  os << ToStringTraits<MonteCarlo::IncoherentModelType>::toString( type );
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentModelType.cpp
//---------------------------------------------------------------------------//
