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
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Convert incoherent adjoint model name to an IncoherentAdjointModelType enum
IncoherentAdjointModelType convertStringToIncoherentAdjointModelTypeEnum(
                             const std::string& incoherent_adjoint_model_name )
{
  if( incoherent_adjoint_model_name == "Klein-Nishina Adjoint Model" )
    return KN_INCOHERENT_ADJOINT_MODEL;
  else if( incoherent_adjoint_model_name == "Waller-Hartree Adjoint Model" )
    return WH_INCOHERENT_ADJOINT_MODEL;
  else if( incoherent_adjoint_model_name == "Impulse Adjoint Model" )
    return IMPULSE_INCOHERENT_ADJOINT_MODEL;
  else if( incoherent_adjoint_model_name ==
           "Doppler Broadened Impulse Adjoint Model" )
    return DB_IMPULSE_INCOHERENT_ADJOINT_MODEL;
  else
  {
    THROW_EXCEPTION( std::logic_error,
                     "Error: incoherent adjoint model type name "
                     << incoherent_adjoint_model_name << " is unknown!" );
  }
}

// Convert unsigned to IncoherentAdjointModelType enum
IncoherentAdjointModelType convertUnsignedToIncoherentAdjointModelTypeEnum(
                                 const unsigned incoherent_adjoint_model_type )
{
  switch( incoherent_adjoint_model_type )
  {
  case 0:
    return KN_INCOHERENT_ADJOINT_MODEL;
  case 1:
    return WH_INCOHERENT_ADJOINT_MODEL;
  case 2:
    return IMPULSE_INCOHERENT_ADJOINT_MODEL;
  case 3:
    return DB_IMPULSE_INCOHERENT_ADJOINT_MODEL;
  default:
    THROW_EXCEPTION( std::logic_error,
                     "Error: unsigned integer "
                     << incoherent_adjoint_model_type <<
                     " does not correspond to an incoherent adjoint model "
                     "type!" );
  }
}

// Convert a IncoherentAdjointModelType to a string
std::string convertIncoherentAdjointModelTypeToString(
                    const IncoherentAdjointModelType incoherent_adjoint_model )
{
  switch( incoherent_adjoint_model )
  {
  case KN_INCOHERENT_ADJOINT_MODEL:
    return "Klein-Nishina Adjoint Model";
  case WH_INCOHERENT_ADJOINT_MODEL:
    return "Waller-Hartree Adjoint Model" ;
  case IMPULSE_INCOHERENT_ADJOINT_MODEL:
    return "Impulse Adjoint Model";
  case DB_IMPULSE_INCOHERENT_ADJOINT_MODEL:
    return "Doppler Broadened Impulse Adjoint Model";
  default:
    THROW_EXCEPTION( std::logic_error,
                     "Error: unkown incoherent adjoint model "
                     "encountered!" );
  }
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentAdjointModelType.cpp
//---------------------------------------------------------------------------//
