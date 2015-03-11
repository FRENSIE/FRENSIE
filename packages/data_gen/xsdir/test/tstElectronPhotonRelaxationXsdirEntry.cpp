//---------------------------------------------------------------------------//
//!
//! \file   tstElectronPhotonRelaxationXsdirEntry.cpp
//! \author Alex Robinson
//! \brief  Electron-photon-relaxation xsdir entry unit tests
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
#include "DataGen_ElectronPhotonRelaxationXsdirEntry.hpp"
#include "MonteCarlo_CrossSectionsXMLProperties.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::string line_a( "  1000.12p      0.999242  mcplib12 0 1        1     1898 0 0 0.00000E+00" );
std::string line_b( "100000.12p    254.792000 xmc/eprdata12 0 1  2114874   156679 0 0 0.00000E+00   " );

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the table alias can be returned
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationXsdirEntry, getTableAlias )
{
  Teuchos::Array<std::string> entry_tokens;

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_a, entry_tokens );
  
  Teuchos::RCP<DataGen::XsdirEntry> entry(
	     new DataGen::ElectronPhotonRelaxationXsdirEntry( entry_tokens ) );

  TEST_EQUALITY_CONST( entry->getTableAlias(), "H" );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_b, entry_tokens );
  
  entry.reset(new DataGen::ElectronPhotonRelaxationXsdirEntry( entry_tokens ));

  TEST_EQUALITY_CONST( entry->getTableAlias(), "Fm" );
}

//---------------------------------------------------------------------------//
// Check that the xsdir entry can be added to a parameter list
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationXsdirEntry, addInfoToParameterList )
{
  Teuchos::ParameterList parameter_list( "Cross Sections Directory" );
  
  Teuchos::Array<std::string> entry_tokens;

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_a, entry_tokens );
  
  Teuchos::RCP<DataGen::XsdirEntry> entry(
	     new DataGen::ElectronPhotonRelaxationXsdirEntry( entry_tokens ) );

  Teuchos::ParameterList& sublist_a = 
    parameter_list.sublist( entry->getTableAlias() );

  entry->addInfoToParameterList( sublist_a );

  TEST_EQUALITY_CONST( sublist_a.numParams(), 10 );
  TEST_EQUALITY_CONST( sublist_a.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::photoatomic_file_path_prop ),
		       "mcplib12" );
  TEST_EQUALITY_CONST( sublist_a.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::photoatomic_file_type_prop ),
		       MonteCarlo::CrossSectionsXMLProperties::ace_file );
  TEST_EQUALITY_CONST( sublist_a.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::photoatomic_table_name_prop ),
		       "1000.12p" );
  TEST_EQUALITY_CONST( sublist_a.get<int>( MonteCarlo::CrossSectionsXMLProperties::photoatomic_file_start_line_prop ),
		       1 );
  TEST_EQUALITY_CONST( sublist_a.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::electroatomic_file_path_prop ),
		       "mcplib12" );
  TEST_EQUALITY_CONST( sublist_a.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::electroatomic_file_type_prop ),
		       MonteCarlo::CrossSectionsXMLProperties::ace_file );
  TEST_EQUALITY_CONST( sublist_a.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::electroatomic_table_name_prop ),
		       "1000.12p" );
  TEST_EQUALITY_CONST( sublist_a.get<int>( MonteCarlo::CrossSectionsXMLProperties::electroatomic_file_start_line_prop ),
		       1 );
  TEST_EQUALITY_CONST( sublist_a.get<int>( MonteCarlo::CrossSectionsXMLProperties::atomic_number_prop ),
		       1 );
  TEST_EQUALITY_CONST( sublist_a.get<double>( MonteCarlo::CrossSectionsXMLProperties::atomic_weight_ratio_prop ),
		       0.999242 );
  
  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_b, entry_tokens );
  
  entry.reset(new DataGen::ElectronPhotonRelaxationXsdirEntry( entry_tokens ) );

  Teuchos::ParameterList& sublist_b = 
    parameter_list.sublist( entry->getTableAlias() );

  entry->addInfoToParameterList( sublist_b );

  TEST_EQUALITY_CONST( sublist_b.numParams(), 10 );
  TEST_EQUALITY_CONST( sublist_b.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::photoatomic_file_path_prop ),
		       "xmc/eprdata12" );
  TEST_EQUALITY_CONST( sublist_b.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::photoatomic_file_type_prop ),
		       MonteCarlo::CrossSectionsXMLProperties::ace_file );
  TEST_EQUALITY_CONST( sublist_b.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::photoatomic_table_name_prop ),
		       "100000.12p" );
  TEST_EQUALITY_CONST( sublist_b.get<int>( MonteCarlo::CrossSectionsXMLProperties::photoatomic_file_start_line_prop ),
		       2114874 );
  TEST_EQUALITY_CONST( sublist_b.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::electroatomic_file_path_prop ),
		       "xmc/eprdata12" );
  TEST_EQUALITY_CONST( sublist_b.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::electroatomic_file_type_prop ),
		       MonteCarlo::CrossSectionsXMLProperties::ace_file );
  TEST_EQUALITY_CONST( sublist_b.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::electroatomic_table_name_prop ),
		       "100000.12p" );
  TEST_EQUALITY_CONST( sublist_b.get<int>( MonteCarlo::CrossSectionsXMLProperties::electroatomic_file_start_line_prop ),
		       2114874 );
  TEST_EQUALITY_CONST( sublist_b.get<int>( MonteCarlo::CrossSectionsXMLProperties::atomic_number_prop ),
		       100 );
  TEST_EQUALITY_CONST( sublist_b.get<double>( MonteCarlo::CrossSectionsXMLProperties::atomic_weight_ratio_prop ),
		       254.792000 );

  // Make sure important info will not be overridden 
  Teuchos::ParameterList& sublist_c = 
    parameter_list.sublist( "Fm-254_293.6K_v7" );

  sublist_c.set<int>( 
		    MonteCarlo::CrossSectionsXMLProperties::atomic_number_prop,
		    100 );
  sublist_c.set( 
	      MonteCarlo::CrossSectionsXMLProperties::atomic_weight_ratio_prop,
	      255.0 );
  sublist_c.set( MonteCarlo::CrossSectionsXMLProperties::temperature_prop,
		 2.5301E-08 );

  entry->addInfoToParameterList( sublist_c );

  TEST_EQUALITY_CONST( sublist_c.numParams(), 11 );
  TEST_EQUALITY_CONST( sublist_c.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::photoatomic_file_path_prop ),
		       "xmc/eprdata12" );
  TEST_EQUALITY_CONST( sublist_c.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::photoatomic_file_type_prop ),
		       MonteCarlo::CrossSectionsXMLProperties::ace_file );
  TEST_EQUALITY_CONST( sublist_c.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::photoatomic_table_name_prop ),
		       "100000.12p" );
  TEST_EQUALITY_CONST( sublist_c.get<int>( MonteCarlo::CrossSectionsXMLProperties::photoatomic_file_start_line_prop ),
		       2114874 );
  TEST_EQUALITY_CONST( sublist_c.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::electroatomic_file_path_prop ),
		       "xmc/eprdata12" );
  TEST_EQUALITY_CONST( sublist_c.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::electroatomic_file_type_prop ),
		       MonteCarlo::CrossSectionsXMLProperties::ace_file );
  TEST_EQUALITY_CONST( sublist_c.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::electroatomic_table_name_prop ),
		       "100000.12p" );
  TEST_EQUALITY_CONST( sublist_c.get<int>( MonteCarlo::CrossSectionsXMLProperties::electroatomic_file_start_line_prop ),
		       2114874 );
  TEST_EQUALITY_CONST( sublist_c.get<int>( MonteCarlo::CrossSectionsXMLProperties::atomic_number_prop ),
		       100 );
  TEST_EQUALITY_CONST( sublist_c.get<double>( MonteCarlo::CrossSectionsXMLProperties::atomic_weight_ratio_prop ),
		       255.0 );
  TEST_EQUALITY_CONST( sublist_c.get<double>( MonteCarlo::CrossSectionsXMLProperties::temperature_prop ),
		       2.5301E-08  );
}

//---------------------------------------------------------------------------//
// end tstElectronPhotonRelaxationXsdirEntry.cpp
//---------------------------------------------------------------------------//
