//---------------------------------------------------------------------------//
//!
//! \file   tstContinuousEnergyNeutronXsdirEntry.cpp
//! \author Alex Robinson
//! \brief  Continuous energy neutron xsdir entry unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>

// FRENSIE Includes
#include "DataGen_ContinuousEnergyNeutronXsdirEntry.hpp"
#include "MonteCarlo_CrossSectionsXMLProperties.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::string line_a( " 1001.80c 0.999167 endf70a 0 1 1 8177 0 0 2.5301E-08" );
std::string line_b( " 1002.72c 0.999167 endf70a 0 1 1 8177 0 0 2.5301E-08" );
std::string line_c( " 2004.61c 0.999167 endf70a 0 1 1 8177 0 0 2.5301E-08" );

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the xsdir entry can be added to a parameter list
TEUCHOS_UNIT_TEST( ContinuousEnergyNeutronXsdirEntry, addInfoToParameterList )
{
  Teuchos::ParameterList parameter_list("Cross Sections");
  
  Teuchos::Array<std::string> entry_tokens;

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_a, entry_tokens );
  
  Teuchos::RCP<DataGen::ContinuousEnergyNeutronXsdirEntry> entry(
	      new DataGen::ContinuousEnergyNeutronXsdirEntry( entry_tokens ) );

  TEST_EQUALITY_CONST( entry->getTableAlias(), "H-1_293.6K_v8" );
  
  Teuchos::ParameterList& sublist_a = 
    parameter_list.sublist( entry->getTableAlias() );

  entry->addInfoToParameterList( sublist_a );

  TEST_EQUALITY_CONST( sublist_a.numParams(), 9 );
  TEST_EQUALITY_CONST( sublist_a.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::nuclear_file_path_prop ),
		       "endf70a" );
  TEST_EQUALITY_CONST( sublist_a.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::nuclear_file_type_prop ),
		       MonteCarlo::CrossSectionsXMLProperties::ace_file );
  TEST_EQUALITY_CONST( sublist_a.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::nuclear_table_name_prop ),
		       "1001.80c" );
  TEST_EQUALITY_CONST( sublist_a.get<int>( MonteCarlo::CrossSectionsXMLProperties::nuclear_file_start_line_prop ),
		       1 );
  TEST_EQUALITY_CONST( sublist_a.get<int>( MonteCarlo::CrossSectionsXMLProperties::atomic_number_prop ),
		       1 );
  TEST_EQUALITY_CONST( sublist_a.get<int>( MonteCarlo::CrossSectionsXMLProperties::atomic_mass_number_prop ),
		       1 );
  TEST_EQUALITY_CONST( sublist_a.get<int>( MonteCarlo::CrossSectionsXMLProperties::isomer_number_prop ),
		       0 );
  TEST_EQUALITY_CONST( sublist_a.get<double>( MonteCarlo::CrossSectionsXMLProperties::atomic_weight_ratio_prop ),
		       0.999167 );
  TEST_EQUALITY_CONST( sublist_a.get<double>( MonteCarlo::CrossSectionsXMLProperties::temperature_prop ),
		       2.5301E-08 );
  
  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_b, entry_tokens );
  
  entry.reset(new DataGen::ContinuousEnergyNeutronXsdirEntry( entry_tokens ) );

  TEST_EQUALITY_CONST( entry->getTableAlias(), "H-2_293.6K_v7" );
  
  Teuchos::ParameterList& sublist_b = 
    parameter_list.sublist( entry->getTableAlias() );

  entry->addInfoToParameterList( sublist_b );

  TEST_EQUALITY_CONST( sublist_b.numParams(), 9 );
  TEST_EQUALITY_CONST( sublist_b.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::nuclear_file_path_prop ),
		       "endf70a" );
  TEST_EQUALITY_CONST( sublist_b.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::nuclear_file_type_prop ),
		       MonteCarlo::CrossSectionsXMLProperties::ace_file );
  TEST_EQUALITY_CONST( sublist_b.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::nuclear_table_name_prop ),
		       "1002.72c" );
  TEST_EQUALITY_CONST( sublist_b.get<int>( MonteCarlo::CrossSectionsXMLProperties::nuclear_file_start_line_prop ),
		       1 );
  TEST_EQUALITY_CONST( sublist_b.get<int>( MonteCarlo::CrossSectionsXMLProperties::atomic_number_prop ),
		       1 );
  TEST_EQUALITY_CONST( sublist_b.get<int>( MonteCarlo::CrossSectionsXMLProperties::atomic_mass_number_prop ),
		       2 );
  TEST_EQUALITY_CONST( sublist_b.get<int>( MonteCarlo::CrossSectionsXMLProperties::isomer_number_prop ),
		       0 );
  TEST_EQUALITY_CONST( sublist_b.get<double>( MonteCarlo::CrossSectionsXMLProperties::atomic_weight_ratio_prop ),
		       0.999167 );
  TEST_EQUALITY_CONST( sublist_b.get<double>( MonteCarlo::CrossSectionsXMLProperties::temperature_prop ),
		       2.5301E-08 );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_c, entry_tokens );
  
  entry.reset(new DataGen::ContinuousEnergyNeutronXsdirEntry( entry_tokens ) );

  TEST_EQUALITY_CONST( entry->getTableAlias(), "He-4_293.6K_v6" );
  
  Teuchos::ParameterList& sublist_c = 
    parameter_list.sublist( entry->getTableAlias() );

  entry->addInfoToParameterList( sublist_c );

  TEST_EQUALITY_CONST( sublist_c.numParams(), 9 );
  TEST_EQUALITY_CONST( sublist_c.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::nuclear_file_path_prop ),
		       "endf70a" );
  TEST_EQUALITY_CONST( sublist_c.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::nuclear_file_type_prop ),
		       MonteCarlo::CrossSectionsXMLProperties::ace_file );
  TEST_EQUALITY_CONST( sublist_c.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::nuclear_table_name_prop ),
		       "2004.61c" );
  TEST_EQUALITY_CONST( sublist_c.get<int>( MonteCarlo::CrossSectionsXMLProperties::nuclear_file_start_line_prop ),
		       1 );
  TEST_EQUALITY_CONST( sublist_c.get<int>( MonteCarlo::CrossSectionsXMLProperties::atomic_number_prop ),
		       2);
  TEST_EQUALITY_CONST( sublist_c.get<int>( MonteCarlo::CrossSectionsXMLProperties::atomic_mass_number_prop ),
		       4 );
  TEST_EQUALITY_CONST( sublist_c.get<int>( MonteCarlo::CrossSectionsXMLProperties::isomer_number_prop ),
		       0 );
  TEST_EQUALITY_CONST( sublist_c.get<double>( MonteCarlo::CrossSectionsXMLProperties::atomic_weight_ratio_prop ),
		       0.999167 );
  TEST_EQUALITY_CONST( sublist_c.get<double>( MonteCarlo::CrossSectionsXMLProperties::temperature_prop ),
		       2.5301E-08 );
}

//---------------------------------------------------------------------------//
// end tstContinuousEnergyNeutronXsdirEntry.cpp
//---------------------------------------------------------------------------//
