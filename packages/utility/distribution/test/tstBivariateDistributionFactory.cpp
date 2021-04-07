//---------------------------------------------------------------------------//
//!
//! \file   tstBivariateDistributionFactory.cpp
//! \author Alex Robinson
//! \brief  BivariateDistributionFactory unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>

// FRENSIE Includes
#include "Utility_BivariateDistributionFactory.hpp"
#include "Utility_UnivariateDistributionEntryConverterDB.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
Teuchos::RCP<Teuchos::ParameterList> test_dists_list;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the two-d distributions can be created
TEUCHOS_UNIT_TEST( BivariateDistributionFactory, createDistribution )
{
  Utility::BivariateDistributionFactory
    factory( test_dists_list->sublist( "One-D Distributions" ) );

  std::shared_ptr<Utility::BivariateDistribution> distribution =
    factory.createDistribution( test_dists_list->sublist( "Histogram Partially-Tabular Two-D Distribution" ) );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_dists_xml_file;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_dists_xml_file",
                   &test_dists_xml_file,
                   "Test distributions xml file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Set up the entry converter database
  UTILITY_ONE_D_DISTRIBUTION_ENTRY_CONVERTER_DB_SETUP();

  // Load the test distribution representations
  test_dists_list = Teuchos::getParametersFromXmlFile( test_dists_xml_file );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstBivariateDistributionFactory.cpp
//---------------------------------------------------------------------------//
