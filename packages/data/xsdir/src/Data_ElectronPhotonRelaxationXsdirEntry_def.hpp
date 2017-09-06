//---------------------------------------------------------------------------//
//!
//! \file   Data_ElectronPhotonRelaxationXsdirEntry_def.hpp
//! \author Alex Robinson
//! \brief  The electron-photon-relaxation xsdir entry class template defs.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ELECTRON_PHOTON_RELAXATION_XSDIR_ENTRY_DEF_HPP
#define DATA_ELECTRON_PHOTON_RELAXATION_XSDIR_ENTRY_DEF_HPP

// Std Lib Includes
#include <sstream>

// FRENSIE Includes
#include "Data_AtomType.hpp"
#include "Utility_ContractException.hpp"

namespace Data{

// Constructor
template<typename STLCompliantContainer>
ElectronPhotonRelaxationXsdirEntry::ElectronPhotonRelaxationXsdirEntry(
				    const STLCompliantContainer& entry_tokens )
  : XsdirEntry( entry_tokens ),
    d_atomic_number(),
    d_alias()
{
  // Make sure the table type is valid
  testPrecondition( extractTableTypeFromEntryTokens( entry_tokens ) ==
		    ELECTRON_PHOTON_RELAXATION_TABLE );

  unsigned zaid = extractZaidFromTableName( this->getTableName() );
  d_atomic_number = extractAtomicNumberFromZaid( zaid );

  AtomType atom = convertAtomicNumberToAtomTypeEnum( d_atomic_number );

  unsigned table_version = this->getTableVersion();

  // Check the table version
  if ( table_version == 14 )
  {
    std::ostringstream oss;
    oss.precision( 1 );
    oss << convertAtomTypeEnumToString( atom )
        << "_v" << this->getTableVersion();

    d_alias = oss.str();
  }
  else
    d_alias = convertAtomTypeEnumToString( atom );

  // Make sure the atomic number is valid
  testPostcondition( d_atomic_number > 0 );
  testPostcondition( d_atomic_number <= 100 );
}

} // end Data namespace

#endif // end DATA_ELECTRON_PHOTON_RELAXATION_XSDIR_ENTRY_DEF_HPP

//---------------------------------------------------------------------------//
// end Data_ElectronPhotonRelaxationXsdirEntry_def.hpp
//---------------------------------------------------------------------------//
