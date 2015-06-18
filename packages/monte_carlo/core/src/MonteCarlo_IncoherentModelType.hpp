//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IncoherentModelType.hpp
//! \author Alex Robinson
//! \brief  Photon Doppler broadening model type and helper function decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_INCOHERENT_MODEL_TYPE_HPP
#define MONTE_CARLO_INCOHERENT_MODEL_TYPE_HPP

// Std Lib Includes
#include <string>

namespace MonteCarlo{

//! The incoherent model enumeration
enum IncoherentModelType
{
  KN_INCOHERENT_MODEL = 0,
  WH_INCOHERENT_MODEL,
  IMPULSE_INCOHERENT_MODEL,
  DECOUPLED_HALF_PROFILE_DB_HYBRID_INCOHERENT_MODEL,
  DECOUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL,
  COUPLED_HALF_PROFILE_DB_HYBRID_INCOHERENT_MODEL,
  COUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL,
  FULL_PROFILE_DB_IMPULSE_INCOHERENT_MODEL
};

//! Convert incoherent model name to an IncoherentModelType enum
IncoherentModelType convertStringToIncoherentModelTypeEnum(
				    const std::string& incoherent_model_name );

//! Convert unsigned to IncoherentModelType enum
IncoherentModelType convertUnsignedToIncoherentModelTypeEnum(
					const unsigned incoherent_model_type );

//! Convert a IncoherentModelType to a string
std::string convertIncoherentModelTypeToString(
				  const IncoherentModelType incoherent_model );

//! Stream operator for printing IncoherentModelType enums
inline std::ostream& operator<<( std::ostream& os,
				const IncoherentModelType incoherent_model )
{
  os << convertIncoherentModelTypeToString( incoherent_model );
  return os;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_INCOHERENT_MODEL_TYPE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonDopplerBroadeningModellType.hpp
//---------------------------------------------------------------------------//
