//---------------------------------------------------------------------------//
//!
//! \file   tstContinuousEnergyNeutronXsdirEntry.cpp
//! \author Alex Robinson
//! \brief  Continuous energy neutron xsdir entry unit tests
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
#include "Data_ContinuousEnergyNeutronXsdirEntry.hpp"
#include "Data_CrossSectionsXMLProperties.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
const std::string line_a( " 1001.80c 0.999167 endf70a 0 1 1 8177 0 0 2.5301E-08" );
const std::string line_b( " 1002.72c 0.999167 endf70a 0 1 1 8177 0 0 2.5301E-08" );
const std::string line_c( " 2004.61c 0.999167 endf70a 0 1 1 8177 0 0 2.5301E-08" );
const std::string line_d( " 27458.71c 57.438100 endf70b 0 1 3694447 18154 0 0 5.1704E-08" );
const std::string line_e( " 48515.70c 113.918000 endf70d 0 1 10018897 220366 0 0 2.5301E-08 ptable" );
const std::string line_f( " 6000.70c 11.898000 endf70a 0 1 1107528 79358 0 0 2.5301E-08" );

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the table alias can be returned
TEUCHOS_UNIT_TEST( ContinuousEnergyNeutronXsdirEntry, getTableAlias )
{
  Teuchos::Array<std::string> entry_tokens;

  Data::XsdirEntry::extractTableTokensFromXsdirLine( line_a, entry_tokens );

  Teuchos::RCP<Data::XsdirEntry> entry(
	      new Data::ContinuousEnergyNeutronXsdirEntry( entry_tokens ) );

  TEST_EQUALITY_CONST( entry->getTableAlias(), "H-1_293.6K_v8" );

  Data::XsdirEntry::extractTableTokensFromXsdirLine( line_b, entry_tokens );

  entry.reset(new Data::ContinuousEnergyNeutronXsdirEntry( entry_tokens ) );

  TEST_EQUALITY_CONST( entry->getTableAlias(), "H-2_293.6K_v7" );

  Data::XsdirEntry::extractTableTokensFromXsdirLine( line_c, entry_tokens );

  entry.reset(new Data::ContinuousEnergyNeutronXsdirEntry( entry_tokens ) );

  TEST_EQUALITY_CONST( entry->getTableAlias(), "He-4_293.6K_v6" );

  Data::XsdirEntry::extractTableTokensFromXsdirLine( line_d, entry_tokens );

  entry.reset(new Data::ContinuousEnergyNeutronXsdirEntry( entry_tokens ) );

  TEST_EQUALITY_CONST( entry->getTableAlias(), "Co-58m_600.0K_v7" );

  Data::XsdirEntry::extractTableTokensFromXsdirLine( line_e, entry_tokens );

  entry.reset(new Data::ContinuousEnergyNeutronXsdirEntry( entry_tokens ) );

  TEST_EQUALITY_CONST( entry->getTableAlias(), "Cd-115m_293.6K_v7" );

  Data::XsdirEntry::extractTableTokensFromXsdirLine( line_f, entry_tokens );

  entry.reset(new Data::ContinuousEnergyNeutronXsdirEntry( entry_tokens ) );

  TEST_EQUALITY_CONST( entry->getTableAlias(), "C_293.6K_v7" );
}

//---------------------------------------------------------------------------//
// Check that the xsdir entry can be added to a parameter list
TEUCHOS_UNIT_TEST( ContinuousEnergyNeutronXsdirEntry, addInfoToParameterList )
{
  Teuchos::ParameterList parameter_list( "Cross Sections Directory" );

  Teuchos::Array<std::string> entry_tokens;

  Data::XsdirEntry::extractTableTokensFromXsdirLine( line_a, entry_tokens );

  Teuchos::RCP<Data::XsdirEntry> entry(
	      new Data::ContinuousEnergyNeutronXsdirEntry( entry_tokens ) );

  Teuchos::ParameterList& sublist_a =
    parameter_list.sublist( entry->getTableAlias() );

  entry->addInfoToParameterList( sublist_a );

  TEST_EQUALITY_CONST( sublist_a.numParams(), 9 );
  TEST_EQUALITY_CONST( sublist_a.get<std::string>( Data::CrossSectionsXMLProperties::nuclear_file_path_prop ),
		       "endf70a" );
  TEST_EQUALITY_CONST( sublist_a.get<std::string>( Data::CrossSectionsXMLProperties::nuclear_file_type_prop ),
		       Data::CrossSectionsXMLProperties::ace_file );
  TEST_EQUALITY_CONST( sublist_a.get<std::string>( Data::CrossSectionsXMLProperties::nuclear_table_name_prop ),
		       "1001.80c" );
  TEST_EQUALITY_CONST( sublist_a.get<int>( Data::CrossSectionsXMLProperties::nuclear_file_start_line_prop ),
		       1 );
  TEST_EQUALITY_CONST( sublist_a.get<int>( Data::CrossSectionsXMLProperties::atomic_number_prop ),
		       1 );
  TEST_EQUALITY_CONST( sublist_a.get<int>( Data::CrossSectionsXMLProperties::atomic_mass_number_prop ),
		       1 );
  TEST_EQUALITY_CONST( sublist_a.get<int>( Data::CrossSectionsXMLProperties::isomer_number_prop ),
		       0 );
  TEST_EQUALITY_CONST( sublist_a.get<double>( Data::CrossSectionsXMLProperties::atomic_weight_ratio_prop ),
		       0.999167 );
  TEST_EQUALITY_CONST( sublist_a.get<double>( Data::CrossSectionsXMLProperties::temperature_prop ),
		       2.5301E-08 );

  Data::XsdirEntry::extractTableTokensFromXsdirLine( line_b, entry_tokens );

  entry.reset(new Data::ContinuousEnergyNeutronXsdirEntry( entry_tokens ) );

  Teuchos::ParameterList& sublist_b =
    parameter_list.sublist( entry->getTableAlias() );

  entry->addInfoToParameterList( sublist_b );

  TEST_EQUALITY_CONST( sublist_b.numParams(), 9 );
  TEST_EQUALITY_CONST( sublist_b.get<std::string>( Data::CrossSectionsXMLProperties::nuclear_file_path_prop ),
		       "endf70a" );
  TEST_EQUALITY_CONST( sublist_b.get<std::string>( Data::CrossSectionsXMLProperties::nuclear_file_type_prop ),
		       Data::CrossSectionsXMLProperties::ace_file );
  TEST_EQUALITY_CONST( sublist_b.get<std::string>( Data::CrossSectionsXMLProperties::nuclear_table_name_prop ),
		       "1002.72c" );
  TEST_EQUALITY_CONST( sublist_b.get<int>( Data::CrossSectionsXMLProperties::nuclear_file_start_line_prop ),
		       1 );
  TEST_EQUALITY_CONST( sublist_b.get<int>( Data::CrossSectionsXMLProperties::atomic_number_prop ),
		       1 );
  TEST_EQUALITY_CONST( sublist_b.get<int>( Data::CrossSectionsXMLProperties::atomic_mass_number_prop ),
		       2 );
  TEST_EQUALITY_CONST( sublist_b.get<int>( Data::CrossSectionsXMLProperties::isomer_number_prop ),
		       0 );
  TEST_EQUALITY_CONST( sublist_b.get<double>( Data::CrossSectionsXMLProperties::atomic_weight_ratio_prop ),
		       0.999167 );
  TEST_EQUALITY_CONST( sublist_b.get<double>( Data::CrossSectionsXMLProperties::temperature_prop ),
		       2.5301E-08 );

  Data::XsdirEntry::extractTableTokensFromXsdirLine( line_c, entry_tokens );

  entry.reset(new Data::ContinuousEnergyNeutronXsdirEntry( entry_tokens ) );

  Teuchos::ParameterList& sublist_c =
    parameter_list.sublist( entry->getTableAlias() );

  entry->addInfoToParameterList( sublist_c );

  TEST_EQUALITY_CONST( sublist_c.numParams(), 9 );
  TEST_EQUALITY_CONST( sublist_c.get<std::string>( Data::CrossSectionsXMLProperties::nuclear_file_path_prop ),
		       "endf70a" );
  TEST_EQUALITY_CONST( sublist_c.get<std::string>( Data::CrossSectionsXMLProperties::nuclear_file_type_prop ),
		       Data::CrossSectionsXMLProperties::ace_file );
  TEST_EQUALITY_CONST( sublist_c.get<std::string>( Data::CrossSectionsXMLProperties::nuclear_table_name_prop ),
		       "2004.61c" );
  TEST_EQUALITY_CONST( sublist_c.get<int>( Data::CrossSectionsXMLProperties::nuclear_file_start_line_prop ),
		       1 );
  TEST_EQUALITY_CONST( sublist_c.get<int>( Data::CrossSectionsXMLProperties::atomic_number_prop ),
		       2);
  TEST_EQUALITY_CONST( sublist_c.get<int>( Data::CrossSectionsXMLProperties::atomic_mass_number_prop ),
		       4 );
  TEST_EQUALITY_CONST( sublist_c.get<int>( Data::CrossSectionsXMLProperties::isomer_number_prop ),
		       0 );
  TEST_EQUALITY_CONST( sublist_c.get<double>( Data::CrossSectionsXMLProperties::atomic_weight_ratio_prop ),
		       0.999167 );
  TEST_EQUALITY_CONST( sublist_c.get<double>( Data::CrossSectionsXMLProperties::temperature_prop ),
		       2.5301E-08 );

  Data::XsdirEntry::extractTableTokensFromXsdirLine( line_d, entry_tokens );

  entry.reset(new Data::ContinuousEnergyNeutronXsdirEntry( entry_tokens ) );

  Teuchos::ParameterList& sublist_d =
    parameter_list.sublist( entry->getTableAlias() );

  entry->addInfoToParameterList( sublist_d );

  TEST_EQUALITY_CONST( sublist_d.numParams(), 9 );
  TEST_EQUALITY_CONST( sublist_d.get<std::string>( Data::CrossSectionsXMLProperties::nuclear_file_path_prop ),
		       "endf70b" );
  TEST_EQUALITY_CONST( sublist_d.get<std::string>( Data::CrossSectionsXMLProperties::nuclear_file_type_prop ),
		       Data::CrossSectionsXMLProperties::ace_file );
  TEST_EQUALITY_CONST( sublist_d.get<std::string>( Data::CrossSectionsXMLProperties::nuclear_table_name_prop ),
		       "27458.71c" );
  TEST_EQUALITY_CONST( sublist_d.get<int>( Data::CrossSectionsXMLProperties::nuclear_file_start_line_prop ),
		       3694447 );
  TEST_EQUALITY_CONST( sublist_d.get<int>( Data::CrossSectionsXMLProperties::atomic_number_prop ),
		       27);
  TEST_EQUALITY_CONST( sublist_d.get<int>( Data::CrossSectionsXMLProperties::atomic_mass_number_prop ),
		       58 );
  TEST_EQUALITY_CONST( sublist_d.get<int>( Data::CrossSectionsXMLProperties::isomer_number_prop ),
		       1 );
  TEST_EQUALITY_CONST( sublist_d.get<double>( Data::CrossSectionsXMLProperties::atomic_weight_ratio_prop ),
		       57.438100 );
  TEST_EQUALITY_CONST( sublist_d.get<double>( Data::CrossSectionsXMLProperties::temperature_prop ),
		       5.1704E-08 );

  Data::XsdirEntry::extractTableTokensFromXsdirLine( line_e, entry_tokens );

  entry.reset(new Data::ContinuousEnergyNeutronXsdirEntry( entry_tokens ) );

  Teuchos::ParameterList& sublist_e =
    parameter_list.sublist( entry->getTableAlias() );

  entry->addInfoToParameterList( sublist_e );

  TEST_EQUALITY_CONST( sublist_e.numParams(), 9 );
  TEST_EQUALITY_CONST( sublist_e.get<std::string>( Data::CrossSectionsXMLProperties::nuclear_file_path_prop ),
		       "endf70d" );
  TEST_EQUALITY_CONST( sublist_e.get<std::string>( Data::CrossSectionsXMLProperties::nuclear_file_type_prop ),
		       Data::CrossSectionsXMLProperties::ace_file );
  TEST_EQUALITY_CONST( sublist_e.get<std::string>( Data::CrossSectionsXMLProperties::nuclear_table_name_prop ),
		       "48515.70c" );
  TEST_EQUALITY_CONST( sublist_e.get<int>( Data::CrossSectionsXMLProperties::nuclear_file_start_line_prop ),
		       10018897 );
  TEST_EQUALITY_CONST( sublist_e.get<int>( Data::CrossSectionsXMLProperties::atomic_number_prop ),
		       48 );
  TEST_EQUALITY_CONST( sublist_e.get<int>( Data::CrossSectionsXMLProperties::atomic_mass_number_prop ),
		       115 );
  TEST_EQUALITY_CONST( sublist_e.get<int>( Data::CrossSectionsXMLProperties::isomer_number_prop ),
		       1 );
  TEST_EQUALITY_CONST( sublist_e.get<double>( Data::CrossSectionsXMLProperties::atomic_weight_ratio_prop ),
		       113.918000 );
  TEST_EQUALITY_CONST( sublist_e.get<double>( Data::CrossSectionsXMLProperties::temperature_prop ),
		       2.5301E-08 );

  Data::XsdirEntry::extractTableTokensFromXsdirLine( line_f, entry_tokens );

  entry.reset(new Data::ContinuousEnergyNeutronXsdirEntry( entry_tokens ) );

  Teuchos::ParameterList& sublist_f =
    parameter_list.sublist( entry->getTableAlias() );

  entry->addInfoToParameterList( sublist_f );

  TEST_EQUALITY_CONST( sublist_f.numParams(), 9 );
  TEST_EQUALITY_CONST( sublist_f.get<std::string>( Data::CrossSectionsXMLProperties::nuclear_file_path_prop ),
		       "endf70a" );
  TEST_EQUALITY_CONST( sublist_f.get<std::string>( Data::CrossSectionsXMLProperties::nuclear_file_type_prop ),
		       Data::CrossSectionsXMLProperties::ace_file );
  TEST_EQUALITY_CONST( sublist_f.get<std::string>( Data::CrossSectionsXMLProperties::nuclear_table_name_prop ),
		       "6000.70c" );
  TEST_EQUALITY_CONST( sublist_f.get<int>( Data::CrossSectionsXMLProperties::nuclear_file_start_line_prop ),
		       1107528 );
  TEST_EQUALITY_CONST( sublist_f.get<int>( Data::CrossSectionsXMLProperties::atomic_number_prop ),
		       6 );
  TEST_EQUALITY_CONST( sublist_f.get<int>( Data::CrossSectionsXMLProperties::atomic_mass_number_prop ),
		       0 );
  TEST_EQUALITY_CONST( sublist_f.get<int>( Data::CrossSectionsXMLProperties::isomer_number_prop ),
		       0 );
  TEST_EQUALITY_CONST( sublist_f.get<double>( Data::CrossSectionsXMLProperties::atomic_weight_ratio_prop ),
		       11.898000 );
  TEST_EQUALITY_CONST( sublist_f.get<double>( Data::CrossSectionsXMLProperties::temperature_prop ),
		       2.5301E-08 );
}

//---------------------------------------------------------------------------//
// end tstContinuousEnergyNeutronXsdirEntry.cpp
//---------------------------------------------------------------------------//
