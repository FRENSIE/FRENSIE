//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IncoherentAdjointModelType.hpp
//! \author Alex Robinson
//! \brief  Incoherent adjoint model types and helper functions decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_INCOHERENT_ADJOINT_MODEL_TYPE_HPP
#define MONTE_CARLO_INCOHERENT_ADJOINT_MODEL_TYPE_HPP

// Std Lib Includes
#include <string>

namespace MonteCarlo{

//! The incoherent adjoint model enumeration
enum IncoherentAdjointModelType
{
  KN_INCOHERENT_ADJOINT_MODEL = 0,
  WH_INCOHERENT_ADJOINT_MODEL,
  IMPULSE_INCOHERENT_ADJOINT_MODEL,
  DB_IMPULSE_INCOHERENT_ADJOINT_MODEL
};

//! Convert incoherent adjoint model name to an IncoherentAdjointModelType enum
IncoherentAdjointModelType convertStringToIncoherentAdjointModelTypeEnum(
                            const std::string& incoherent_adjoint_model_name );

//! Convert unsigned to IncoherentAdjointModelType enum
IncoherentAdjointModelType convertUnsignedToIncoherentAdjointModelTypeEnum(
                                const unsigned incoherent_adjoint_model_type );

//! Convert a IncoherentAdjointModelType to a string
std::string convertIncoherentAdjointModelTypeToString(
                   const IncoherentAdjointModelType incoherent_adjoint_model );

//! Stream operator for printing IncoherentAdjointModelType enums
inline std::ostream& operator<<( std::ostream& os,
		    const IncoherentAdjointModelType incoherent_adjoint_model )
{
  os << convertIncoherentAdjointModelTypeToString( incoherent_adjoint_model );
  return os;
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_INCOHERENT_ADJOINT_MODEL_TYPE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentAdjointModelType.hpp
//---------------------------------------------------------------------------//
