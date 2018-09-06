//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SubshellRelaxationModel.hpp
//! \author Alex Robinson
//! \brief  Subshell relaxation model base class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_SubshellRelaxationModel.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
SubshellRelaxationModel::SubshellRelaxationModel(
					  const Data::SubshellType vacancy_subshell )
  : d_vacancy_subshell( vacancy_subshell )
{
  // Make sure the vacancy subshell is valid
  testPrecondition( vacancy_subshell != Data::INVALID_SUBSHELL );
  testPrecondition( vacancy_subshell !=Data::UNKNOWN_SUBSHELL );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_SubshellRelaxationModel.cpp
//---------------------------------------------------------------------------//
