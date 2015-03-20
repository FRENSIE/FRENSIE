//---------------------------------------------------------------------------//
//!
//! \file   DataGen_XsdirEntryFactory_def.hpp
//! \author Alex Robinson
//! \brief  The xsdir entry factory class template definitions
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_XSDIR_ENTRY_FACTORY_DEF_HPP
#define DATA_GEN_XSDIR_ENTRY_FACTORY_DEF_HPP

// FRENSIE Includes
#include "DataGen_ContinuousEnergyNeutronXsdirEntry.hpp"
#include "DataGen_ElectronPhotonRelaxationXsdirEntry.hpp"
#include "DataGen_PhotonuclearXsdirEntry.hpp"
#include "DataGen_SAlphaBetaXsdirEntry.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace DataGen{

// Create the xsdir entry
template<typename STLCompliantContainer>
void XsdirEntryFactory::createEntry( const STLCompliantContainer& entry_tokens,
				     Teuchos::RCP<XsdirEntry>& entry )
{
  // Make sure the entry tokens are valid
  testPrecondition( XsdirEntry::isLineTableEntry( entry_tokens ) );
  testPrecondition( XsdirEntry::isTableTypeSupported( entry_tokens ) );

  XsdirEntry::TableType table_type = 
    XsdirEntry::extractTableTypeFromEntryTokens( entry_tokens );

  switch( table_type )
  {
  case XsdirEntry::CONTINUOUS_ENERGY_NEUTRON_TABLE:
  {
    entry.reset( new ContinuousEnergyNeutronXsdirEntry( entry_tokens ) );

    break;
  }
  case XsdirEntry::S_ALPHA_BETA_TABLE:
  {
    entry.reset( new SAlphaBetaXsdirEntry( entry_tokens ) );

    break;
  }
  case XsdirEntry::ELECTRON_PHOTON_RELAXATION_TABLE:
  {
    entry.reset( new ElectronPhotonRelaxationXsdirEntry( entry_tokens ) );

    break;
  }
  case XsdirEntry::PHOTONUCLEAR_TABLE:
  {
    entry.reset( new PhotonuclearXsdirEntry( entry_tokens ) );

    break;
  }
  default:
  {
    THROW_EXCEPTION( std::logic_error,
		     "Error: table type " << table_type << " is not "
		     "supported!" );
  }
  }
}

} // end DataGen namespace

#endif // end DATA_GEN_XSDIR_ENTRY_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end DataGen_XsdirEntryFactory_def.hpp
//---------------------------------------------------------------------------//
