//---------------------------------------------------------------------------//
//!
//! \file   tstDirectionalDistributionFactory.cpp
//! \author Alex Robinson
//! \brief  Directional distribution factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_DirectionalDistributionFactory.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<Teuchos::ParameterList> parameter_list;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution of interest can be constructed from parameter
// entries
TEUCHOS_UNIT_TEST( DirectionalDistributionFactory,
		   createDistribution_default_axis )
{
  Teuchos::ParameterList directional_distribution_rep =
    parameter_list->get<Teuchos::ParameterList>("Directional Distribution A" );

  std::shared_ptr<Utility::DirectionalDistribution> distribution =
    Utility::DirectionalDistributionFactory::createDistribution(
						directional_distribution_rep );

  TEST_ASSERT( distribution.get() );

  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.0;
  fake_stream[3] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Teuchos::Array<double> sampled_dir( 3 );

  distribution->sample( sampled_dir.getRawPtr() );

  UTILITY_TEST_FLOATING_EQUALITY( sampled_dir[0], -1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sampled_dir[1], 0.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sampled_dir[2], 0.0, 1e-15 );

  distribution->sample( sampled_dir.getRawPtr() );

  UTILITY_TEST_FLOATING_EQUALITY( sampled_dir[0], 0.0, 1e-7 );
  UTILITY_TEST_FLOATING_EQUALITY( sampled_dir[1], 0.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sampled_dir[2], 1.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution of interest can be constructed from parameter
// entries
TEUCHOS_UNIT_TEST( DirectionalDistributionFactory,
		   createDistribution_specific )
{
  Teuchos::ParameterList directional_distribution_rep =
    parameter_list->get<Teuchos::ParameterList>("Directional Distribution B" );

  std::shared_ptr<Utility::DirectionalDistribution> distribution =
    Utility::DirectionalDistributionFactory::createDistribution(
						directional_distribution_rep );

  TEST_ASSERT( distribution.get() );

  Teuchos::Array<double> sampled_dir( 3 );

  distribution->sample( sampled_dir.getRawPtr() );

  UTILITY_TEST_FLOATING_EQUALITY( sampled_dir[0], 0.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sampled_dir[1], 1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sampled_dir[2], 0.0, 1e-15 );

  distribution->sample( sampled_dir.getRawPtr() );

  UTILITY_TEST_FLOATING_EQUALITY( sampled_dir[0], 0.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sampled_dir[1], 1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sampled_dir[2], 0.0, 1e-15 );

  distribution->sample( sampled_dir.getRawPtr() );

  UTILITY_TEST_FLOATING_EQUALITY( sampled_dir[0], 0.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sampled_dir[1], 1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sampled_dir[2], 0.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the distribution of interest can be constructed from parameter
// entries
TEUCHOS_UNIT_TEST( DirectionalDistributionFactory,
		   createDistribution_default_theta_axis )
{
  Teuchos::ParameterList directional_distribution_rep =
    parameter_list->get<Teuchos::ParameterList>("Directional Distribution C" );

  std::shared_ptr<Utility::DirectionalDistribution> distribution =
    Utility::DirectionalDistributionFactory::createDistribution(
						directional_distribution_rep );

  TEST_ASSERT( distribution.get() );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Teuchos::Array<double> sampled_dir( 3 );

  distribution->sample( sampled_dir.getRawPtr() );

  UTILITY_TEST_FLOATING_EQUALITY( sampled_dir[0], 0.6189908924466622, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sampled_dir[1], 0.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sampled_dir[2], -0.7853981633974483, 1e-15 );

  distribution->sample( sampled_dir.getRawPtr() );

  UTILITY_TEST_FLOATING_EQUALITY( sampled_dir[0], -0.6189908924466622, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sampled_dir[1], 0.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sampled_dir[2], -0.7853981633974483, 1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution of interest can be constructed from parameter
// entries
TEUCHOS_UNIT_TEST( DirectionalDistributionFactory,
		   createDistribution_monodirectional )
{
  Teuchos::ParameterList directional_distribution_rep =
    parameter_list->get<Teuchos::ParameterList>("Directional Distribution D" );

  std::shared_ptr<Utility::DirectionalDistribution> distribution =
    Utility::DirectionalDistributionFactory::createDistribution(
						directional_distribution_rep );

  TEST_ASSERT( distribution.get() );

  Teuchos::Array<double> sampled_dir( 3 );

  distribution->sample( sampled_dir.getRawPtr() );

  TEST_FLOATING_EQUALITY( sampled_dir[0], 0.5773502691896258, 1e-15 );
  TEST_FLOATING_EQUALITY( sampled_dir[1], -0.5773502691896258, 1e-15 );
  TEST_FLOATING_EQUALITY( sampled_dir[2], 0.5773502691896258, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that an isotropic distribution can be constructed
TEUCHOS_UNIT_TEST( DirectionalDistributionFactory,
		   createIsotropicDistribution )
{
  std::shared_ptr<Utility::DirectionalDistribution> distribution =
    Utility::DirectionalDistributionFactory::createIsotropicDistribution();

  TEST_ASSERT( distribution.get() );

  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.0;
  fake_stream[3] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Teuchos::Array<double> sampled_dir( 3 );

  distribution->sample( sampled_dir.getRawPtr() );

  UTILITY_TEST_FLOATING_EQUALITY( sampled_dir[0], -1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sampled_dir[1], 0.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sampled_dir[2], 0.0, 1e-15 );

  distribution->sample( sampled_dir.getRawPtr() );

  UTILITY_TEST_FLOATING_EQUALITY( sampled_dir[0], 0.0, 1e-7 );
  UTILITY_TEST_FLOATING_EQUALITY( sampled_dir[1], 0.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sampled_dir[2], 1.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_xml_file_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_xml_file",
                   &test_xml_file_name,
                   "Test spatial distribution xml file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  parameter_list = Teuchos::getParametersFromXmlFile( test_xml_file_name );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstDirectionalDistributionFactory.cpp
//---------------------------------------------------------------------------//
