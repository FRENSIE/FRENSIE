//---------------------------------------------------------------------------//
//!
//! \file   tstBremsstrahlungElectronScatteringDistributionNativeFactory.cpp
//! \author Luke Kersting
//! \brief  bremsstrahlung scattering distribution native factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_BremsstrahlungElectronScatteringDistributionNativeFactory.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<Data::ElectronPhotonRelaxationDataContainer> data_container;

std::shared_ptr<const MonteCarlo::BremsstrahlungElectronScatteringDistribution>
  dipole_distribution;

std::shared_ptr<const MonteCarlo::BremsstrahlungElectronScatteringDistribution>
  twobs_distribution;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the sample() function for a dipole distribution
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistributionNativeFactory,
                   sample_DipoleBremsstrahlung_LinLinLog )
{
  MonteCarlo::BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution<Utility::LinLinLog,Utility::Correlated>(
                                                 *data_container,
                                                 dipole_distribution,
                                                 true,
                                                 true );

  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // Correlated sample the 7.94968E-04 MeV and 1.18921E-02 MeV distributions
  fake_stream[1] = 0.5; // Sample angle 0.0592724905908 (0.0557151835328) from analytical function

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 0.0009;
  double photon_energy, photon_angle_cosine;

  // sample dipole_distribution
  dipole_distribution->sample( incoming_energy,
                               photon_energy,
                               photon_angle_cosine );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // Test
  TEST_FLOATING_EQUALITY( photon_energy, 1.62240683985362E-05, 1e-12 );
  TEST_FLOATING_EQUALITY( photon_angle_cosine, 0.0592724905908, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the sample() function for a dipole distribution
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistributionNativeFactory,
                   sample_LinLinLin )
{
  MonteCarlo::BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution<Utility::LinLinLin,Utility::Correlated>(
                                                 *data_container,
                                                 dipole_distribution,
                                                 true,
                                                 true );

  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // Correlated sample the 7.94968E-04 MeV and 1.18921E-02 MeV distributions
  fake_stream[1] = 0.5; // Sample angle 0.0592724905908 (0.0557151835328) from analytical function

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 0.0009;
  double photon_energy, photon_angle_cosine;

  // sample dipole_distribution
  dipole_distribution->sample( incoming_energy,
                               photon_energy,
                               photon_angle_cosine );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // Test
  TEST_FLOATING_EQUALITY( photon_energy, 1.67197635933458E-05, 1e-12 );
  TEST_FLOATING_EQUALITY( photon_angle_cosine, 0.0592724905908, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the sample() function for a dipole distribution
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistributionNativeFactory,
                   sample_LogLogLog_exact )
{
  MonteCarlo::BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution<Utility::LogLogLog,Utility::Exact>(
                                                 *data_container,
                                                 dipole_distribution,
                                                 true,
                                                 false );

  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // Correlated sample the 7.94968E-04 MeV and 1.18921E-02 MeV distributions
  fake_stream[1] = 0.5; // Sample angle 0.0592724905908 (0.0557151835328) from analytical function

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 0.0009;
  double photon_energy, photon_angle_cosine;

  // sample dipole_distribution
  dipole_distribution->sample( incoming_energy,
                               photon_energy,
                               photon_angle_cosine );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // Test
  TEST_FLOATING_EQUALITY( photon_energy, 1.561053962145298170e-05, 1e-12 );
  TEST_FLOATING_EQUALITY( photon_angle_cosine, 0.0592724905908, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the sample() function for a dipole distribution
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistributionNativeFactory,
                   sample_LinLinLin_exact )
{
  MonteCarlo::BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution<Utility::LinLinLin,Utility::Exact>(
                                                 *data_container,
                                                 dipole_distribution,
                                                 true,
                                                 false );

  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // Correlated sample the 7.94968E-04 MeV and 1.18921E-02 MeV distributions
  fake_stream[1] = 0.5; // Sample angle 0.0592724905908 (0.0557151835328) from analytical function

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 0.0009;
  double photon_energy, photon_angle_cosine;

  // sample dipole_distribution
  dipole_distribution->sample( incoming_energy,
                               photon_energy,
                               photon_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( photon_energy, 1.51455974406695E-05, 1e-12 );
  TEST_FLOATING_EQUALITY( photon_angle_cosine, 0.0592724905908, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the sampleAndRecordTrials() function for a dipole distribution
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistributionNativeFactory,
                   sampleAndRecordTrials_DipoleBremsstrahlung_LinLinLog )
{
  MonteCarlo::BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution<Utility::LinLinLog,Utility::Correlated>(
                                                 *data_container,
                                                 dipole_distribution,
                                                 true,
                                                 true );

  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // Correlated sample the 7.94968E-04 MeV and 1.18921E-02 MeV distributions
  fake_stream[1] = 0.5; // Sample angle 0.0592724905908 (0.0557151835328) from analytical function

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned trials = 10;
  double incoming_energy = 0.0009;
  double photon_energy, photon_angle_cosine;

  dipole_distribution->sampleAndRecordTrials( incoming_energy,
                                              photon_energy,
                                              photon_angle_cosine,
                                              trials );

  TEST_FLOATING_EQUALITY( photon_energy, 1.62240683985362E-05, 1e-12 );
  TEST_FLOATING_EQUALITY( photon_angle_cosine, 0.0592724905908 , 1e-12 );
  TEST_EQUALITY_CONST( trials, 11 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the sample() function using detailed 2BS
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistributionNativeFactory,
                   sample_TwoBSBremsstrahlung_LinLinLog )
{
  MonteCarlo::BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution<Utility::LinLinLog,Utility::Correlated>(
                    *data_container,
                    data_container->getAtomicNumber(),
                    twobs_distribution,
                    true,
                    true );

  // Set up the random number stream
  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 0.5; // Correlated sample the 3.1622800E-01 MeV and 2.0 MeV distributions
  fake_stream[1] = 0.5; // Sample a photon angle of 0.612270260118 (0.9118675275)
  fake_stream[2] = 0.49; // Reject the angle
  fake_stream[3] = 0.5; // Sample a photon angle of 0.612270260118 (0.9118675275)
  fake_stream[4] = 0.48; // Accept the angle


  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0;
  double photon_energy, photon_angle_cosine;

  twobs_distribution->sample( incoming_energy,
                              photon_energy,
                              photon_angle_cosine );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( photon_energy, 2.07132641637312E-04, 1e-12 );
  TEST_FLOATING_EQUALITY( photon_angle_cosine, 0.612270260118, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the sampleAndRecordTrials() function using detailed 2BS
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistributionNativeFactory,
                   sampleAndRecordTrials_TwoBSBremsstrahlung_LinLinLog )
{
  MonteCarlo::BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution<Utility::LinLinLog,Utility::Correlated>(
                    *data_container,
                    data_container->getAtomicNumber(),
                    twobs_distribution,
                    true,
                    true );

  // Set up the random number stream
  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 0.5; // Correlated sample the 3.1622800E-01 MeV and 2.0 MeV distributions
  fake_stream[1] = 0.5; // Sample a photon angle of 0.9118675275
  fake_stream[2] = 0.49; // Reject the angle
  fake_stream[3] = 0.5; // Sample a photon angle of 0.9118675275
  fake_stream[4] = 0.48; // Accept the angle


  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned trials = 0.0;
  double incoming_energy = 1.0;
  double photon_energy, photon_angle_cosine;

  twobs_distribution->sampleAndRecordTrials( incoming_energy,
                                             photon_energy,
                                             photon_angle_cosine,
                                             trials );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( photon_energy, 2.07132641637312E-04, 1e-12 );
  TEST_FLOATING_EQUALITY( photon_angle_cosine, 0.612270260118, 1e-12 );
  TEST_EQUALITY_CONST( trials, 1.0 );
}


//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_native_file_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_native_file",
                   &test_native_file_name,
                   "Test Native file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Create the native data file container
  data_container.reset( new Data::ElectronPhotonRelaxationDataContainer(
                             test_native_file_name ) );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstBremsstrahlungElectronScatteringDistributionNativeFactory.cpp
//---------------------------------------------------------------------------//
