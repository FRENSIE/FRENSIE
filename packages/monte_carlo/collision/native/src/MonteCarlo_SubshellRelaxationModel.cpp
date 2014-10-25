//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SubshellRelaxationModel.hpp
//! \author Alex Robinson
//! \brief  Subshell relaxation model base class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_SubshellRelaxationModel.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
SubshellRelaxationModel::SubshellRelaxationModel( 
					  const SubshellType vacancy_subshell )
  : d_vacancy_subshell( vacancy_subshell )
{
  // Make sure the vacancy subshell is valid
  testPrecondition( vacancy_subshell != INVALID_SUBSHELL );
  testPrecondition( vacancy_subshell != UNKNOWN_SUBSHELL );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_SubshellRelaxationModel.cpp
//---------------------------------------------------------------------------//
