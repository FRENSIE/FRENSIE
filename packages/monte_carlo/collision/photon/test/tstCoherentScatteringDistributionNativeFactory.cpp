//---------------------------------------------------------------------------//
//!
//! \file   tstCoherentScatteringDistributionNativeFactory.cpp
//! \author Alex Robinson
//! \brief  Coherent scattering distribution native factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_CoherentScatteringDistributionNativeFactory.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<Data::ElectronPhotonRelaxationDataContainer> data_container;
std::shared_ptr<const MonteCarlo::CoherentScatteringDistribution> distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a Thompson distribution can be created
FRENSIE_UNIT_TEST( CoherentScatteringDistributionNativeFactory,
		   createThompsonDistribution )
{
  MonteCarlo::CoherentScatteringDistributionNativeFactory::createThompsonDistribution(
								distribution );

  // Test distribution properties
  double dist_value = distribution->evaluate( 0.1, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 4.989344050883251e-1, 1e-15 );

  dist_value = distribution->evaluate( 0.1, 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 2.4946720254416256e-1, 1e-15 );

  dist_value = distribution->evaluate( 0.1, -1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 4.989344050883251e-1, 1e-15 );

  double outgoing_energy, scattering_angle_cosine;
  Data::SubshellType shell_of_interaction;

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.75;
  fake_stream[1] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Sample 1st term
  distribution->sample( 0.1,
			outgoing_energy,
			scattering_angle_cosine );

  FRENSIE_CHECK_EQUAL( outgoing_energy, 0.1 );
  FRENSIE_CHECK_SMALL( scattering_angle_cosine, 1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a basic coherent distribution can be created
FRENSIE_UNIT_TEST( CoherentScatteringDistributionNativeFactory,
		   createBasicCoherentDistribution )
{
  MonteCarlo::CoherentScatteringDistributionNativeFactory::createBasicCoherentDistribution(
							       *data_container,
							       distribution );

  // Test distribution properties
  double dist_value = distribution->evaluate( 0.1, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 3.354834939813898e3, 1e-15 );

  dist_value = distribution->evaluate( 0.1, 0.0 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 4.13794808678274517, 1e-15 );

  dist_value = distribution->evaluate( 0.1, -1.0 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 3.58206485705525468, 1e-15 );

  double outgoing_energy, scattering_angle_cosine;

  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.75;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.003; // reject
  fake_stream[3] = 0.7;
  fake_stream[4] = 0.8;
  fake_stream[5] = 0.006;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution->sample( 0.1,
			outgoing_energy,
			scattering_angle_cosine );

  FRENSIE_CHECK_EQUAL( outgoing_energy, 0.1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.6, 1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that an efficient coherent distribution can be created
FRENSIE_UNIT_TEST( CoherentScatteringDistributionNativeFactory,
		   createEfficientCoherentDistribution )
{
  MonteCarlo::CoherentScatteringDistributionNativeFactory::createEfficientCoherentDistribution(
							       *data_container,
							       distribution );

  // Test distribution properties
  double outgoing_energy, scattering_angle_cosine;

  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.942; // reject
  fake_stream[2] = 0.5;
  fake_stream[3] = 0.941;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution->sample( 0.1,
			outgoing_energy,
			scattering_angle_cosine );
  
  FRENSIE_CHECK_EQUAL( outgoing_energy, 0.1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.94014376762379892, 1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_native_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_native_file",
                                        test_native_file_name, "",
                                        "Test Native file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create the native data file container
  data_container.reset( new Data::ElectronPhotonRelaxationDataContainer(
						     test_native_file_name ) );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstCoherentScatteringDistributionNativeFactory.cpp
//---------------------------------------------------------------------------//
