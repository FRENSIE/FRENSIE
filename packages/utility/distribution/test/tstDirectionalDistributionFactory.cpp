//---------------------------------------------------------------------------//
//!
//! \file   tstDirectionalDistributionFactory.cpp
//! \author Alex Robinson
//! \brief  Directional distribution factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_DirectionalDistributionFactory.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::string test_xml_file_name;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution of interest can be constructed from parameter
// entries
TEUCHOS_UNIT_TEST( DirectionalDistributionFactory, createDefaultDistribution )
{
  Teuchos::RCP<Teuchos::ParameterList> parameter_list = 
    Teuchos::getParametersFromXmlFile( test_xml_file_name );

  Teuchos::ParameterList directional_distribution_rep = 
    parameter_list->get<Teuchos::ParameterList>("Directional Distribution A" );

  Teuchos::RCP<Utility::DirectionalDistribution> distribution = 
    Utility::DirectionalDistributionFactory::createDistribution(
						directional_distribution_rep );

  TEST_ASSERT( !distribution.is_null() );

  std::cout << std::endl;
  for( unsigned i = 0; i < 5; ++i )
  {
    Teuchos::Array<double> sampled_dir( 3 );

    distribution->sample( sampled_dir.getRawPtr() );

    std::cout << sampled_dir << std::endl;
  }
}

//---------------------------------------------------------------------------//
// Check that the distribution of interest can be constructed from parameter
// entries
TEUCHOS_UNIT_TEST( DirectionalDistributionFactory, createSpecificDistribution )
{
  Teuchos::RCP<Teuchos::ParameterList> parameter_list = 
    Teuchos::getParametersFromXmlFile( test_xml_file_name );

  Teuchos::ParameterList directional_distribution_rep = 
    parameter_list->get<Teuchos::ParameterList>("Directional Distribution B" );

  Teuchos::RCP<Utility::DirectionalDistribution> distribution = 
    Utility::DirectionalDistributionFactory::createDistribution(
						directional_distribution_rep );

  TEST_ASSERT( !distribution.is_null() );

  std::cout << std::endl;
  for( unsigned i = 0; i < 5; ++i )
  {
    Teuchos::Array<double> sampled_dir( 3 );

    distribution->sample( sampled_dir.getRawPtr() );

    std::cout << sampled_dir << std::endl;
  }
}

//---------------------------------------------------------------------------//
// Check that the distribution of interest can be constructed from parameter
// entries
TEUCHOS_UNIT_TEST( DirectionalDistributionFactory, createMonoDistribution )
{
  Teuchos::RCP<Teuchos::ParameterList> parameter_list = 
    Teuchos::getParametersFromXmlFile( test_xml_file_name );

  Teuchos::ParameterList directional_distribution_rep = 
    parameter_list->get<Teuchos::ParameterList>("Directional Distribution C" );

  Teuchos::RCP<Utility::DirectionalDistribution> distribution = 
    Utility::DirectionalDistributionFactory::createDistribution(
						directional_distribution_rep );
  
  TEST_ASSERT( !distribution.is_null() );

  Teuchos::Array<double> sampled_dir( 3 );
  
  distribution->sample( sampled_dir.getRawPtr() );

  TEST_FLOATING_EQUALITY( sampled_dir[0], 0.5773502691896258, 1e-15 );
  TEST_FLOATING_EQUALITY( sampled_dir[1], -0.5773502691896258, 1e-15 );
  TEST_FLOATING_EQUALITY( sampled_dir[2], 0.5773502691896258, 1e-15 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Utility::OneDDistributionEntryConverterDB::standardInitialization();
  
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();

  clp.setOption( "test_xml_file",
		 &test_xml_file_name,
		 "Test spatial distribution xml file name" );

  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );
}

//---------------------------------------------------------------------------//
// end tstDirectionalDistributionFactory.cpp
//---------------------------------------------------------------------------//
