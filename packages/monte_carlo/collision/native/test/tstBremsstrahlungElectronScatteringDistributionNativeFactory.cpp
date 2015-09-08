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
#include "Data_EvaluatedElectronDataContainer.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<Data::EvaluatedElectronDataContainer> data_container;

Teuchos::RCP<const MonteCarlo::BremsstrahlungElectronScatteringDistribution>
  dipole_distribution;

Teuchos::RCP<const MonteCarlo::BremsstrahlungElectronScatteringDistribution>
  tabular_distribution;

Teuchos::RCP<const MonteCarlo::BremsstrahlungElectronScatteringDistribution>
  twobs_distribution;

double upper_cutoff_energy, lower_cutoff_energy;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the sample() function for a dipole distribution
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistributionNativeFactory, 
                   sample_DipoleBremsstrahlung )
{
  MonteCarlo::BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution(
                                                 *data_container,
                                                 dipole_distribution );

  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // Correlated sample the 7.94968E-04 MeV and 1.18921E-02 MeV distributions
  fake_stream[1] = 0.5; // Sample angle 0.0557151835328 from analytical function 
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 0.0009;
  double photon_energy, photon_angle_cosine;

  // sample dipole_distribution
  dipole_distribution->sample( incoming_energy,
                               photon_energy, 
                               photon_angle_cosine );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // Test
  TEST_FLOATING_EQUALITY( photon_energy, 1.51455974406695E-05, 1e-12 );
  TEST_FLOATING_EQUALITY( photon_angle_cosine, 0.0592724905908 , 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the sampleAndRecordTrials() function for a dipole distribution
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistributionNativeFactory, 
                   sampleAndRecordTrials_DipoleBremsstrahlung )
{
  MonteCarlo::BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution(
                                                 *data_container,
                                                 dipole_distribution );

  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // Correlated sample the 7.94968E-04 MeV and 1.18921E-02 MeV distributions
  fake_stream[1] = 0.5; // Sample angle 0.0557151835328 from analytical function 
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned trials = 10;
  double incoming_energy = 0.0009;
  double photon_energy, photon_angle_cosine;

  dipole_distribution->sampleAndRecordTrials( incoming_energy, 
                                              photon_energy, 
                                              photon_angle_cosine,
                                              trials );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( photon_energy, 1.51455974406695E-05, 1e-12 );
  TEST_FLOATING_EQUALITY( photon_angle_cosine, 0.0592724905908 , 1e-12 );
  TEST_EQUALITY_CONST( trials, 11 ); 
}

//---------------------------------------------------------------------------//
// Check that the sample() function using detailed 2BS
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistributionNativeFactory, 
                   sample_TwoBSBremsstrahlung )
{
  MonteCarlo::BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution(
                    *data_container,
                    twobs_distribution,
                    data_container->getAtomicNumber() );

  // Set up the random number stream
  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 0.5; // Correlated sample the 3.1622800E-01 MeV and 2.0 MeV distributions
  fake_stream[1] = 0.5; // Sample a photon angle of 0.9118675275
  fake_stream[2] = 0.49; // Reject the angle
  fake_stream[3] = 0.5; // Sample a photon angle of 0.9118675275
  fake_stream[4] = 0.48; // Accept the angle

 
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0;
  double photon_energy, photon_angle_cosine;

  twobs_distribution->sample( incoming_energy, 
                              photon_energy, 
                              photon_angle_cosine );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( photon_energy, 1.63944375104991E-04, 1e-12 );
  TEST_FLOATING_EQUALITY( photon_angle_cosine, 0.612270260118, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the sampleAndRecordTrials() function using detailed 2BS
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistributionNativeFactory, 
                   sampleAndRecordTrials_TwoBSBremsstrahlung )
{
  MonteCarlo::BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution(
                    *data_container,
                    twobs_distribution,
                    data_container->getAtomicNumber() );

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

  TEST_FLOATING_EQUALITY( photon_energy, 1.63944375104991E-04, 1e-12 );
  TEST_FLOATING_EQUALITY( photon_angle_cosine, 0.612270260118, 1e-12 );
  TEST_EQUALITY_CONST( trials, 1.0 );
}


//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_native_file_name;
  
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_native_file",
		 &test_native_file_name,
		 "Test Native file name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) 
  {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }
  
  // Create the native data file container
  data_container.reset( new Data::EvaluatedElectronDataContainer( 
						     test_native_file_name ) );

  upper_cutoff_energy = 1000;
  lower_cutoff_energy = 0.001;

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
  
  // Run the unit tests
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  const bool success = Teuchos::UnitTestRepository::runUnitTests( *out );

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);  					    
}

//---------------------------------------------------------------------------//
// end tstBremsstrahlungElectronScatteringDistributionNativeFactory.cpp
//---------------------------------------------------------------------------//
