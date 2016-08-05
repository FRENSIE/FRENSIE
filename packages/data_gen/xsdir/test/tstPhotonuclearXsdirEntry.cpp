//---------------------------------------------------------------------------//
//!
//! \file   tstPhotonuclearXsdirEntry.cpp
//! \author Alex Robinson
//! \brief  Photonuclear xsdir entry unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>

// FRENSIE Includes
#include "DataGen_PhotonuclearXsdirEntry.hpp"
#include "MonteCarlo_CrossSectionsXMLProperties.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::string line_a( "  1002.24u     1.996300 la150u 0 1 216233   3686  0 0 0.000E+00" );
std::string line_b( " 82208.24u   206.190000 xdata/la150u 0 1 196946  77099  0 0 0.000E+00  " );
std::string line_c( " 93237.70u 235.011800 xmc/endf7u 0 1 4868895 48076  " );


//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the table alias can be returned
TEUCHOS_UNIT_TEST( PhotonuclearXsdirEntry, getTableAlias )
{
  Teuchos::Array<std::string> entry_tokens;

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_a, entry_tokens );

  Teuchos::RCP<DataGen::XsdirEntry> entry(
	                 new DataGen::PhotonuclearXsdirEntry( entry_tokens ) );

  TEST_EQUALITY_CONST( entry->getTableAlias(), "H-2_v2" );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_b, entry_tokens );

  entry.reset( new DataGen::PhotonuclearXsdirEntry( entry_tokens ) );

  TEST_EQUALITY_CONST( entry->getTableAlias(), "Pb-208_v2" );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_c, entry_tokens );

  entry.reset( new DataGen::PhotonuclearXsdirEntry( entry_tokens ) );

  TEST_EQUALITY_CONST( entry->getTableAlias(), "Np-237_v7" );
}

//---------------------------------------------------------------------------//
// Check that the xsdir entry can be added to a parameter list
TEUCHOS_UNIT_TEST( PhotonuclearXsdirEntry, addInfoToParameterList )
{
  Teuchos::ParameterList parameter_list( "Cross Sections Directory" );

  Teuchos::Array<std::string> entry_tokens;

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_a, entry_tokens );

  Teuchos::RCP<DataGen::XsdirEntry> entry(
	                 new DataGen::PhotonuclearXsdirEntry( entry_tokens ) );

  Teuchos::ParameterList& sublist_a =
    parameter_list.sublist( entry->getTableAlias() );

  entry->addInfoToParameterList( sublist_a );

  TEST_EQUALITY_CONST( sublist_a.numParams(), 8 );
  TEST_EQUALITY_CONST( sublist_a.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::photonuclear_file_path_prop ),
		       "la150u" );
  TEST_EQUALITY_CONST( sublist_a.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::photonuclear_file_type_prop ),
		       MonteCarlo::CrossSectionsXMLProperties::ace_file );
  TEST_EQUALITY_CONST( sublist_a.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::photonuclear_table_name_prop ),
		       "1002.24u" );
  TEST_EQUALITY_CONST( sublist_a.get<int>( MonteCarlo::CrossSectionsXMLProperties::photonuclear_file_start_line_prop ),
		       216233 );
  TEST_EQUALITY_CONST( sublist_a.get<int>( MonteCarlo::CrossSectionsXMLProperties::atomic_number_prop ),
		       1 );
  TEST_EQUALITY_CONST( sublist_a.get<int>( MonteCarlo::CrossSectionsXMLProperties::atomic_mass_number_prop ),
		       2 );
  TEST_EQUALITY_CONST( sublist_a.get<int>( MonteCarlo::CrossSectionsXMLProperties::isomer_number_prop ),
		       0 );
  TEST_EQUALITY_CONST( sublist_a.get<double>( MonteCarlo::CrossSectionsXMLProperties::atomic_weight_ratio_prop ),
		       1.996300 );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_b, entry_tokens );

  entry.reset( new DataGen::PhotonuclearXsdirEntry( entry_tokens ) );

  Teuchos::ParameterList& sublist_b =
    parameter_list.sublist( entry->getTableAlias() );

  entry->addInfoToParameterList( sublist_b );

  TEST_EQUALITY_CONST( sublist_b.numParams(), 8 );
  TEST_EQUALITY_CONST( sublist_b.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::photonuclear_file_path_prop ),
		       "xdata/la150u" );
  TEST_EQUALITY_CONST( sublist_b.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::photonuclear_file_type_prop ),
		       MonteCarlo::CrossSectionsXMLProperties::ace_file );
  TEST_EQUALITY_CONST( sublist_b.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::photonuclear_table_name_prop ),
		       "82208.24u" );
  TEST_EQUALITY_CONST( sublist_b.get<int>( MonteCarlo::CrossSectionsXMLProperties::photonuclear_file_start_line_prop ),
		       196946 );
  TEST_EQUALITY_CONST( sublist_b.get<int>( MonteCarlo::CrossSectionsXMLProperties::atomic_number_prop ),
		       82 );
  TEST_EQUALITY_CONST( sublist_b.get<int>( MonteCarlo::CrossSectionsXMLProperties::atomic_mass_number_prop ),
		       208 );
  TEST_EQUALITY_CONST( sublist_b.get<int>( MonteCarlo::CrossSectionsXMLProperties::isomer_number_prop ),
		       0 );
  TEST_EQUALITY_CONST( sublist_b.get<double>( MonteCarlo::CrossSectionsXMLProperties::atomic_weight_ratio_prop ),
		       206.190000 );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_c, entry_tokens );

  entry.reset( new DataGen::PhotonuclearXsdirEntry( entry_tokens ) );

  Teuchos::ParameterList& sublist_c =
    parameter_list.sublist( entry->getTableAlias() );

  entry->addInfoToParameterList( sublist_c );

  TEST_EQUALITY_CONST( sublist_c.numParams(), 8 );
  TEST_EQUALITY_CONST( sublist_c.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::photonuclear_file_path_prop ),
		       "xmc/endf7u" );
  TEST_EQUALITY_CONST( sublist_c.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::photonuclear_file_type_prop ),
		       MonteCarlo::CrossSectionsXMLProperties::ace_file );
  TEST_EQUALITY_CONST( sublist_c.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::photonuclear_table_name_prop ),
		       "93237.70u" );
  TEST_EQUALITY_CONST( sublist_c.get<int>( MonteCarlo::CrossSectionsXMLProperties::photonuclear_file_start_line_prop ),
		       4868895 );
  TEST_EQUALITY_CONST( sublist_c.get<int>( MonteCarlo::CrossSectionsXMLProperties::atomic_number_prop ),
		       93 );
  TEST_EQUALITY_CONST( sublist_c.get<int>( MonteCarlo::CrossSectionsXMLProperties::atomic_mass_number_prop ),
		       237 );
  TEST_EQUALITY_CONST( sublist_c.get<int>( MonteCarlo::CrossSectionsXMLProperties::isomer_number_prop ),
		       0 );
  TEST_EQUALITY_CONST( sublist_c.get<double>( MonteCarlo::CrossSectionsXMLProperties::atomic_weight_ratio_prop ),
		       235.011800 );
}

//---------------------------------------------------------------------------//
// end tstPhotonuclearXsdirEntry.cpp
//---------------------------------------------------------------------------//
