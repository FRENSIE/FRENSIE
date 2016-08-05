//---------------------------------------------------------------------------//
//!
//! \file   tstSalphaBetaXsdirEntry.cpp
//! \author Alex Robinson
//! \brief  S(alpha,beta) xsdir entry unit tests
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
#include "DataGen_SAlphaBetaXsdirEntry.hpp"
#include "MonteCarlo_CrossSectionsXMLProperties.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::string line_a( " smeth.60t  0.999170 sab2002 0 1 823113 53047 0 0 1.89580E-09" );
std::string line_b( " zr/h.06t   0.000000   tmccs 0 1 132047 17442 0 0 1.03408E-07" );
std::string line_c( " u/o2.12t 236.005800 endf70sab 0 1 4693164 195252 0 0 4.3087E-08" );

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the table alias can be returned
TEUCHOS_UNIT_TEST( SAlphaBetaXsdirEntry, getTableAlias )
{
  Teuchos::Array<std::string> entry_tokens;

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_a, entry_tokens );

  Teuchos::RCP<DataGen::XsdirEntry> entry(
			   new DataGen::SAlphaBetaXsdirEntry( entry_tokens ) );

  TEST_EQUALITY_CONST( entry->getTableAlias(), "smeth_22.0K_v6" );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_b, entry_tokens );

  entry.reset( new DataGen::SAlphaBetaXsdirEntry( entry_tokens ) );

  TEST_EQUALITY_CONST( entry->getTableAlias(), "zr/h_1200.0K_v0" );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_c, entry_tokens );

  entry.reset( new DataGen::SAlphaBetaXsdirEntry( entry_tokens ) );

  TEST_EQUALITY_CONST( entry->getTableAlias(), "u/o2_500.0K_v1" );
}

//---------------------------------------------------------------------------//
// Check that the xsdir entry can be added to a parameter list
TEUCHOS_UNIT_TEST( SAlphaBetaXsdirEntry, addInfoToParameterList )
{
  Teuchos::ParameterList parameter_list( "Cross Sections Directory" );

  Teuchos::Array<std::string> entry_tokens;

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_a, entry_tokens );

  Teuchos::RCP<DataGen::XsdirEntry> entry(
			   new DataGen::SAlphaBetaXsdirEntry( entry_tokens ) );

  Teuchos::ParameterList& sublist_a =
    parameter_list.sublist( entry->getTableAlias() );

  entry->addInfoToParameterList( sublist_a );

  TEST_EQUALITY_CONST( sublist_a.numParams(), 5 );
  TEST_EQUALITY_CONST( sublist_a.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::s_alpha_beta_file_path_prop ),
		       "sab2002" );
  TEST_EQUALITY_CONST( sublist_a.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::s_alpha_beta_file_type_prop ),
		       MonteCarlo::CrossSectionsXMLProperties::ace_file );
  TEST_EQUALITY_CONST( sublist_a.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::s_alpha_beta_table_name_prop ),
		       "smeth.60t" );
  TEST_EQUALITY_CONST( sublist_a.get<int>( MonteCarlo::CrossSectionsXMLProperties::s_alpha_beta_file_start_line_prop ),
		       823113 );
  TEST_EQUALITY_CONST( sublist_a.get<double>( MonteCarlo::CrossSectionsXMLProperties::temperature_prop ),
		       1.89580E-09 );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_b, entry_tokens );

  entry.reset( new DataGen::SAlphaBetaXsdirEntry( entry_tokens ) );

  Teuchos::ParameterList& sublist_b =
    parameter_list.sublist( entry->getTableAlias() );

  entry->addInfoToParameterList( sublist_b );

  TEST_EQUALITY_CONST( sublist_b.numParams(), 5 );
  TEST_EQUALITY_CONST( sublist_b.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::s_alpha_beta_file_path_prop ),
		       "tmccs" );
  TEST_EQUALITY_CONST( sublist_b.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::s_alpha_beta_file_type_prop ),
		       MonteCarlo::CrossSectionsXMLProperties::ace_file );
  TEST_EQUALITY_CONST( sublist_b.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::s_alpha_beta_table_name_prop ),
		       "zr/h.06t" );
  TEST_EQUALITY_CONST( sublist_b.get<int>( MonteCarlo::CrossSectionsXMLProperties::s_alpha_beta_file_start_line_prop ),
		       132047 );
  TEST_EQUALITY_CONST( sublist_b.get<double>( MonteCarlo::CrossSectionsXMLProperties::temperature_prop ),
		       1.03408E-07 );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_c, entry_tokens );

  entry.reset( new DataGen::SAlphaBetaXsdirEntry( entry_tokens ) );

  Teuchos::ParameterList& sublist_c =
    parameter_list.sublist( entry->getTableAlias() );

  entry->addInfoToParameterList( sublist_c );

  TEST_EQUALITY_CONST( sublist_c.numParams(), 5 );
  TEST_EQUALITY_CONST( sublist_c.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::s_alpha_beta_file_path_prop ),
		       "endf70sab" );
  TEST_EQUALITY_CONST( sublist_c.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::s_alpha_beta_file_type_prop ),
		       MonteCarlo::CrossSectionsXMLProperties::ace_file );
  TEST_EQUALITY_CONST( sublist_c.get<std::string>( MonteCarlo::CrossSectionsXMLProperties::s_alpha_beta_table_name_prop ),
		       "u/o2.12t" );
  TEST_EQUALITY_CONST( sublist_c.get<int>( MonteCarlo::CrossSectionsXMLProperties::s_alpha_beta_file_start_line_prop ),
		       4693164 );
  TEST_EQUALITY_CONST( sublist_c.get<double>( MonteCarlo::CrossSectionsXMLProperties::temperature_prop ),
		       4.3087E-08 );
}

//---------------------------------------------------------------------------//
// end tstSalphaBetaXsdirEntry.cpp
//---------------------------------------------------------------------------//
