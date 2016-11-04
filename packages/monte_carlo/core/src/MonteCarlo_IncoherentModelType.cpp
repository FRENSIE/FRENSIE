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
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Convert photon Doppler broadening model name to a IncoherentModelType enum
IncoherentModelType convertStringToIncoherentModelTypeEnum(
				      const std::string& incoherent_model_name )
{
  if( incoherent_model_name == "Klein-Nishina Model" )
    return KN_INCOHERENT_MODEL;
  else if( incoherent_model_name == "Waller-Hartree Model" )
    return WH_INCOHERENT_MODEL;
  else if( incoherent_model_name == "Impulse Model" )
    return IMPULSE_INCOHERENT_MODEL;
  else if( incoherent_model_name == "DHP Doppler Broadened Hybrid Model" )
    return DECOUPLED_HALF_PROFILE_DB_HYBRID_INCOHERENT_MODEL;
  else if( incoherent_model_name == "DFP Doppler Broadened Hybrid Model" )
    return DECOUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL;
  else if( incoherent_model_name == "CHP Doppler Broadened Hybrid Model" )
    return COUPLED_HALF_PROFILE_DB_HYBRID_INCOHERENT_MODEL;
  else if( incoherent_model_name == "CFP Doppler Broadened Hybrid Model" )
    return COUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL;
  else if( incoherent_model_name == "FP Doppler Broadened Impulse Model" )
    return FULL_PROFILE_DB_IMPULSE_INCOHERENT_MODEL;
  else
  {
    THROW_EXCEPTION( std::logic_error,
		     "Error: incoherent model type name "
		     << incoherent_model_name << " is unknown!" );
  }
}

// Convert unsigned to IncoherentModelType enum
IncoherentModelType convertUnsignedToIncoherentModelTypeEnum(
					  const unsigned incoherent_model_type )
{
  switch( incoherent_model_type )
  {
  case 0:
    return KN_INCOHERENT_MODEL;
  case 1:
    return WH_INCOHERENT_MODEL;
  case 2:
    return IMPULSE_INCOHERENT_MODEL;
  case 3:
    return DECOUPLED_HALF_PROFILE_DB_HYBRID_INCOHERENT_MODEL;
  case 4:
    return DECOUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL;
  case 5:
    return COUPLED_HALF_PROFILE_DB_HYBRID_INCOHERENT_MODEL;
  case 6:
    return COUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL;
  case 7:
    return FULL_PROFILE_DB_IMPULSE_INCOHERENT_MODEL;
  default:
    THROW_EXCEPTION( std::logic_error,
		     "Error: unsigned integer " << incoherent_model_type <<
		     " does not correspond to an incoherent model type!" );
  }
}

// Convert a IncoherentModelType to a string
std::string convertIncoherentModelTypeToString(
				    const IncoherentModelType incoherent_model )
{
  switch( incoherent_model )
  {
  case KN_INCOHERENT_MODEL:
    return "Klein-Nishina Model";
  case WH_INCOHERENT_MODEL:
    return "Waller-Hartree Model";
  case IMPULSE_INCOHERENT_MODEL:
    return "Impulse Model";
  case DECOUPLED_HALF_PROFILE_DB_HYBRID_INCOHERENT_MODEL:
    return "DHP Doppler Broadened Hybrid Model";
  case DECOUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL:
    return "DFP Doppler Broadened Hybrid Model";
  case COUPLED_HALF_PROFILE_DB_HYBRID_INCOHERENT_MODEL:
    return "CHP Doppler Broadened Hybrid Model";
  case COUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL:
    return "CFP Doppler Broadened Hybrid Model";
  case FULL_PROFILE_DB_IMPULSE_INCOHERENT_MODEL:
    return "FP Doppler Broadened Impulse Model";
  default:
    THROW_EXCEPTION( std::logic_error,
		     "Error: unknown incoherent model encountered!" );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentModelType.cpp
//---------------------------------------------------------------------------//
