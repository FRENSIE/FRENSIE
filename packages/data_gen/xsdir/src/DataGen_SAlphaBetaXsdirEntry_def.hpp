//---------------------------------------------------------------------------//
//!
//! \file   DataGen_SAlphaBetaXsdirEntry_def.hpp
//! \author Alex Robinson
//! \brief  The S(alpha,beta) xsdir entry class template definitions
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_S_ALPHA_BETA_XSDIR_ENTRY_DEF_HPP
#define DATA_GEN_S_ALPHA_BETA_XSDIR_ENTRY_DEF_HPP

// Std Lib Includes
#include <sstream>

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace DataGen{

// Constructor
template<typename STLCompliantContainer>
SAlphaBetaXsdirEntry::SAlphaBetaXsdirEntry( 
				    const STLCompliantContainer& entry_tokens )
  : XsdirEntry( entry_tokens ),
    d_alias()
{
  // Make sure the table type is valid
  testPrecondition( extractTableTypeFromEntryTokens( entry_tokens ) ==
		    S_ALPHA_BETA_TABLE );

  unsigned pos = this->getTableName().find( "." );

  std::ostringstream oss;
  oss.precision( 1 );
  oss << this->getTableName().substr( 0, pos ) << "_"
      << std::fixed << this->getTableTemperatureKelvin() << "K_v"
      << this->getTableVersion()/10;

  d_alias = oss.str();
}

} // end DataGen namespace

#endif // end DATA_GEN_S_ALPHA_BETA_XSDIR_ENTRY_DEF_HPP

//---------------------------------------------------------------------------//
// end DataGen_SAlphaBetaXsdirEntry_def.hpp
//---------------------------------------------------------------------------//
