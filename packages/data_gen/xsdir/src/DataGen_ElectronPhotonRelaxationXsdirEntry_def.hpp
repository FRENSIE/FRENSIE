//---------------------------------------------------------------------------//
//!
//! \file   DataGen_ElectronPhotonRelaxationXsdirEntry_def.hpp
//! \author Alex Robinson
//! \brief  The electron-photon-relaxation xsdir entry class template defs.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_ELECTRON_PHOTON_RELAXATION_XSDIR_ENTRY_DEF_HPP
#define DATA_GEN_ELECTRON_PHOTON_RELAXATION_XSDIR_ENTRY_DEF_HPP

// Std Lib Includes
#include <sstream>

// FRENSIE Includes
#include "MonteCarlo_AtomType.hpp"
#include "Utility_ContractException.hpp"

namespace DataGen{

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

  MonteCarlo::AtomType atom =
    MonteCarlo::convertAtomicNumberToAtomTypeEnum( d_atomic_number );

  d_alias = MonteCarlo::convertAtomTypeEnumToString( atom );

  // Make sure the atomic number is valid
  testPostcondition( d_atomic_number > 0 );
  testPostcondition( d_atomic_number <= 100 );
}

} // end DataGen namespace

#endif // end DATA_GEN_ELECTRON_PHOTON_RELAXATION_XSDIR_ENTRY_DEF_HPP

//---------------------------------------------------------------------------//
// end DataGen_ElectronPhotonRelaxationXsdirEntry_def.hpp
//---------------------------------------------------------------------------//
