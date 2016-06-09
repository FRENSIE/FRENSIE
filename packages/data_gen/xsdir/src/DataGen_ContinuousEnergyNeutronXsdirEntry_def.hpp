//---------------------------------------------------------------------------//
//!
//! \file   DataGen_ContinuousEnergyNeutronXsdirEntry_def.hpp
//! \author Alex Robinson
//! \brief  The continuous energy neutron xsdir entry class template defs.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_CONTINUOUS_ENERGY_NEUTRON_XSDIR_ENTRY_DEF_HPP
#define DATA_GEN_CONTINUOUS_ENERGY_NEUTRON_XSDIR_ENTRY_DEF_HPP

// Std Lib Includes
#include <sstream>

// FRENSIE Includes
#include "MonteCarlo_AtomType.hpp"
#include "Utility_ContractException.hpp"

namespace DataGen{

// Constructor
template<typename STLCompliantContainer>
ContinuousEnergyNeutronXsdirEntry::ContinuousEnergyNeutronXsdirEntry(
				    const STLCompliantContainer& entry_tokens )
  : XsdirEntry( entry_tokens ),
    d_atomic_number(),
    d_atomic_mass_number(),
    d_isomer_number( 0 ),
    d_alias()
{
  // Make sure the table type is valid
  testPrecondition( extractTableTypeFromEntryTokens( entry_tokens ) ==
		    CONTINUOUS_ENERGY_NEUTRON_TABLE );

  unsigned zaid = extractZaidFromTableName( this->getTableName() );

  d_atomic_number = extractAtomicNumberFromZaid( zaid );
  d_atomic_mass_number = extractAtomicMassNumberFromZaid( zaid );

  // Check if a metastable state is present
  if( d_atomic_mass_number > 400 )
  {
    d_atomic_mass_number %= 400;

    d_isomer_number = 1;
  }

  MonteCarlo::AtomType atom =
    MonteCarlo::convertAtomicNumberToAtomTypeEnum( d_atomic_number );

  std::ostringstream oss;
  oss.precision( 1 );
  oss << MonteCarlo::convertAtomTypeEnumToString( atom );

  if( d_atomic_mass_number > 0 )
    oss << "-" << d_atomic_mass_number;

  if( d_isomer_number > 0 )
    oss << "m";

  oss << "_"
      << std::fixed << this->getTableTemperatureKelvin() << "K_v"
      << this->getTableVersion()/10;

  d_alias = oss.str();

  // Make sure the atomic number is valid
  testPostcondition( d_atomic_number > 0 );
  testPostcondition( d_atomic_number <= 100 );
  // Make sure the atomic mass number is valid
  testPostcondition( d_atomic_mass_number >= 0 );
  testPostcondition( d_atomic_mass_number < 400 );
}

} // end DataGen namespace

#endif // end DATA_GEN_CONTINUOUS_ENERGY_NEUTRON_XSDIR_ENTRY_DEF_HPP

//---------------------------------------------------------------------------//
// end DataGen_ContinuousEnergyNeutronXsdirEntry_def.hpp
//---------------------------------------------------------------------------//
