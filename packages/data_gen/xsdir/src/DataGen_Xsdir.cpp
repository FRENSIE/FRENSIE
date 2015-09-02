//---------------------------------------------------------------------------//
//!
//! \file   DataGen_Xsdir.cpp
//! \author Alex Robinson
//! \brief  The xsdir class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <fstream>
#include <algorithm>

// Trilinos Includes
#include <Teuchos_XMLParameterListCoreHelpers.hpp>

// FRENSIE Includes
#include "DataGen_Xsdir.hpp"
#include "DataGen_XsdirEntryFactory.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace DataGen{

// Compare the versions of two entries
bool Xsdir::compareVersions( const Teuchos::RCP<XsdirEntry>& entry_a,
			     const Teuchos::RCP<XsdirEntry>& entry_b )
{
  return entry_a->getTableVersion() > entry_b->getTableVersion();
}

// Compare the ids and version of two entries (id 1st, version 2nd)
bool Xsdir::compareIdsAndVersions( const Teuchos::RCP<XsdirEntry>& entry_a,
				   const Teuchos::RCP<XsdirEntry>& entry_b )
{
  unsigned zaid_a = XsdirEntry::extractZaidFromTableName(
						     entry_a->getTableName() );
  unsigned zaid_b = XsdirEntry::extractZaidFromTableName(
						     entry_b->getTableName() );
  
  if( zaid_a < zaid_b )
    return true;
  else if( zaid_a == zaid_b )
  {
    if( entry_a->getTableVersion() > entry_b->getTableVersion() )
      return true;
    else
      return false;
  }
  else
    return false;
}

// Constructor
Xsdir::Xsdir( const std::string& xsdir_file_name )
{
  // Open the xsdir file
  std::ifstream xsdir_file( xsdir_file_name.c_str() );

  TEST_FOR_EXCEPTION( !xsdir_file.good(),
		      std::runtime_error,
		      "Error: the xsdir file " << xsdir_file_name <<
		      " cannot be opened!" );

  // Loop through the xsdir file and parse the entries
  std::string xsdir_line;
  Teuchos::Array<std::string> entry_tokens;
  Teuchos::RCP<XsdirEntry> entry;

  while( !xsdir_file.eof() )
  {
    std::getline( xsdir_file, xsdir_line );

    XsdirEntry::extractTableTokensFromXsdirLine( xsdir_line, entry_tokens );

    // Create the entry
    if( XsdirEntry::isLineTableEntry( entry_tokens ) )
    {
      if( XsdirEntry::isTableTypeSupported( entry_tokens ) )
      {
	XsdirEntryFactory::createEntry( entry_tokens, entry );

	XsdirEntry::TableType table_type = entry->getTableType();

	unsigned zaid = 
	  XsdirEntry::extractZaidFromTableName( entry->getTableName() );
	
	switch( table_type )
	{
	  case XsdirEntry::CONTINUOUS_ENERGY_NEUTRON_TABLE:
	  {
	    d_ce_neutron_xsdir_entries.push_back( entry );
	    
	    break;
	  }
	  case XsdirEntry::S_ALPHA_BETA_TABLE:
	  {
	    d_sab_xsdir_entries.push_back( entry );

	    break;
	  }
	  case XsdirEntry::ELECTRON_PHOTON_RELAXATION_TABLE:
	  {
	    unsigned atomic_number = 
	      XsdirEntry::extractAtomicNumberFromZaid( zaid );
	    
	    d_epr_xsdir_entries_map[atomic_number] = entry;

	    d_epr_xsdir_entries.push_back( entry );

	    break;
	  }
	  case XsdirEntry::PHOTONUCLEAR_TABLE:
	  {
	    d_photonuclear_xsdir_entries_map[zaid].push_back( entry );

	    d_photonuclear_xsdir_entries.push_back( entry );

	    break;
	  }
	}
      }
    }

    xsdir_line.clear();
    entry_tokens.clear();
  }

  // Sort the neutron entries
  std::sort( d_ce_neutron_xsdir_entries.begin(),
	     d_ce_neutron_xsdir_entries.end(),
	     Xsdir::compareIdsAndVersions );

  // Sort the photonuclear entries
  std::sort( d_photonuclear_xsdir_entries.begin(),
	     d_photonuclear_xsdir_entries.end(),
	     Xsdir::compareIdsAndVersions );

  IdEntriesMap::iterator zaid_entries_pair = 
    d_photonuclear_xsdir_entries_map.begin();

  while( zaid_entries_pair != d_photonuclear_xsdir_entries_map.end() )
  {
    std::sort( zaid_entries_pair->second.begin(),
	       zaid_entries_pair->second.end(),
	       Xsdir::compareVersions );
    
    ++zaid_entries_pair;
  }

  // Sort the epr entries
  std::sort( d_epr_xsdir_entries.begin(),
	     d_epr_xsdir_entries.end(),
	     Xsdir::compareIdsAndVersions );
}

// Export the xsdir file to a parameter list
void Xsdir::exportInfo( Teuchos::ParameterList& parameter_list ) const
{
  exportCENeutronEntries( parameter_list );
  exportSAlphaBetaEntries( parameter_list );
  exportEPREntries( parameter_list );

  Teuchos::ParameterList& misc_list = 
    parameter_list.sublist( "Miscellaneous" );
  
  exportPhotonuclearEntries( misc_list );
}

// Export the continuous energy neutron entries
void Xsdir::exportCENeutronEntries( 
				 Teuchos::ParameterList& parameter_list ) const
{
  for( unsigned i = 0; i < d_ce_neutron_xsdir_entries.size(); ++i )
  {
    Teuchos::ParameterList& sublist = parameter_list.sublist( 
			      d_ce_neutron_xsdir_entries[i]->getTableAlias() );
    
    d_ce_neutron_xsdir_entries[i]->addInfoToParameterList( sublist );
    
    // Add the photonuclear data if there is any (use most recent - sorted)
    unsigned zaid = XsdirEntry::extractZaidFromTableName( 
			       d_ce_neutron_xsdir_entries[i]->getTableName() );
    
    IdEntriesMap::const_iterator zaid_entries_pair = 
      d_photonuclear_xsdir_entries_map.find( zaid );

    if( zaid_entries_pair != d_photonuclear_xsdir_entries_map.end() )
      zaid_entries_pair->second.front()->addInfoToParameterList( sublist );

    // Add the photoatomic and electroatomic data
    unsigned atomic_number = XsdirEntry::extractAtomicNumberFromZaid( zaid );

    IdEntryMap::const_iterator z_entries_pair = 
      d_epr_xsdir_entries_map.find( atomic_number );

    if( z_entries_pair != d_epr_xsdir_entries_map.end() )
      z_entries_pair->second->addInfoToParameterList( sublist );
  }
}

// Export the S(alpha,beta) entries
void Xsdir::exportSAlphaBetaEntries( 
				 Teuchos::ParameterList& parameter_list ) const
{
  for( unsigned i = 0; i < d_sab_xsdir_entries.size(); ++i )
  {
    Teuchos::ParameterList& sab_list = 
      parameter_list.sublist( d_sab_xsdir_entries[i]->getTableAlias() );

    d_sab_xsdir_entries[i]->addInfoToParameterList( sab_list );
  }
}

// Export the photonuclear entries
void Xsdir::exportPhotonuclearEntries( 
				  Teuchos::ParameterList& parameter_list) const
{
  for( unsigned i = 0; i < d_photonuclear_xsdir_entries.size(); ++i )
  {
    Teuchos::ParameterList& sublist = parameter_list.sublist( 
			    d_photonuclear_xsdir_entries[i]->getTableAlias() );
    
    d_photonuclear_xsdir_entries[i]->addInfoToParameterList( sublist );
  }
}

// Export the epr entries
void Xsdir::exportEPREntries( Teuchos::ParameterList& parameter_list ) const
{
  for( unsigned i = 0; i < d_epr_xsdir_entries.size(); ++i )
  {
    Teuchos::ParameterList& sublist = parameter_list.sublist(
				     d_epr_xsdir_entries[i]->getTableAlias() );

    d_epr_xsdir_entries[i]->addInfoToParameterList( sublist );
  }
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_Xsdir.cpp
//---------------------------------------------------------------------------//
