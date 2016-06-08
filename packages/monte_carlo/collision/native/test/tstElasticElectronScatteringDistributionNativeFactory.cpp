//---------------------------------------------------------------------------//
//!
//! \file   tstElasticElectronScatteringDistributionNativeFactory.cpp
//! \author Luke Kersting
//! \brief  Elastic electron scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<Data::ElectronPhotonRelaxationDataContainer> data_container;
Teuchos::RCP< const MonteCarlo::CutoffElasticElectronScatteringDistribution> 
  native_cutoff_elastic_distribution;

Teuchos::RCP< const MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution> 
  native_sr_elastic_distribution;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the angular grid can be returned
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory, 
                   getAngularGrid )
{

  double cutoff_angle_cosine = -1.0;
  double energy = 1.0e-5;
  std::vector<double> angular_grid =
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGrid(
                                                *data_container,
                                                energy,
                                                cutoff_angle_cosine );
  // Test
  TEST_EQUALITY_CONST( angular_grid.size(), 2 );
  TEST_EQUALITY_CONST( angular_grid.front(), -1.0 );
  TEST_EQUALITY_CONST( angular_grid.back(), 0.999999 );

  angular_grid.clear();

  cutoff_angle_cosine = 0.9;
  angular_grid =
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGrid(
                                                *data_container,
                                                energy,
                                                cutoff_angle_cosine );
  // Test
  TEST_EQUALITY_CONST( angular_grid.size(), 2 );
  TEST_EQUALITY_CONST( angular_grid.front(), 0.9 );
  TEST_EQUALITY_CONST( angular_grid.back(), 0.999999 );

  angular_grid.clear();

  cutoff_angle_cosine = -1.0;
  energy = 1.0e+5;
  angular_grid =
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGrid(
                                                *data_container,
                                                energy,
                                                cutoff_angle_cosine );
  // Test
  TEST_EQUALITY_CONST( angular_grid.size(), 90 );
  TEST_EQUALITY_CONST( angular_grid.front(), -1.0 );
  TEST_EQUALITY_CONST( angular_grid.back(), 0.999999 );

}
/*
//---------------------------------------------------------------------------//
// Check that sampleAndRecordTrialsImpl can be evaluated
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory, 
                   sampleAndRecordTrialsImpl )
{
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createHardElasticDistributions(
                                                native_cutoff_elastic_distribution,
                                                native_sr_elastic_distribution,
                                                *data_container );

  // Set fake random number stream
  std::vector<double> fake_stream( 4 );
  // Tabular
  fake_stream[0] = 0.5; // sample angle = 1.249161208881750E-02
  // Screened Rutherford
  fake_stream[1] = 0.0; // sample angle cosine = 1.0
  fake_stream[2] = 0.5; // sample angle = 0.9999995
  fake_stream[3] = 1.0 - 1.0e-15; // sample angle = 0.999999

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine;
  unsigned trials = 10;

  // sampleAndRecordTrialsImpl from cutoff distribution
  native_cutoff_elastic_distribution->sampleAndRecordTrialsImpl( 
                                                incoming_energy,
                                                scattering_angle_cosine,
                                                trials );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 
                          1.0 - 1.249161208881750E-02, 
                          1e-12 );

  TEST_EQUALITY_CONST( trials, 11 );

  // sampleAndRecordTrialsImpl from screened Rutherford distribution
  native_sr_elastic_distribution->sampleAndRecordTrialsImpl( 
                                                incoming_energy,
                                                scattering_angle_cosine,
                                                trials );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
  TEST_EQUALITY_CONST( trials, 12 );

  // sampleAndRecordTrialsImpl from screened Rutherford distribution
  native_sr_elastic_distribution->sampleAndRecordTrialsImpl( 
                                                incoming_energy,
                                                scattering_angle_cosine,
                                                trials );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.9999995000000930, 1e-12 );
  TEST_EQUALITY_CONST( trials, 13 );

  // sampleAndRecordTrialsImpl from screened Rutherford distribution
  native_sr_elastic_distribution->sampleAndRecordTrialsImpl( 
                                                incoming_energy,
                                                scattering_angle_cosine,
                                                trials );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0-1.0e-6, 1e-12 );
  TEST_EQUALITY_CONST( trials, 14 );
}
*/
//---------------------------------------------------------------------------//
// Check sample can be evaluated
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory, 
                   sample )
{
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createHardElasticDistributions(
        native_cutoff_elastic_distribution,
        native_sr_elastic_distribution,
        *data_container );

  // Set fake random number stream
  std::vector<double> fake_stream( 4 );
  // Tabular
  fake_stream[0] = 0.5; // sample angle = 1.249161208881750E-02
  // Screened Rutherford
  fake_stream[1] = 0.0; // sample angle cosine = 1.0
  fake_stream[2] = 0.5; // sample angle = 0.9999995
  fake_stream[3] = 1.0 - 1.0e-15; // sample angle = 0.999999

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;

  // sampleAndRecordTrialsImpl cutoff
  native_cutoff_elastic_distribution->sample( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 
                          1.0 - 1.249161208881750E-02, 
                          1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );


  outgoing_energy = 0.0;
  scattering_angle_cosine = 0.0;

  // sampleAndRecordTrialsImpl screened rutherford
  native_sr_elastic_distribution->sample( incoming_energy,
                                          outgoing_energy,
                                          scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // sampleAndRecordTrialsImpl screened rutherford
  native_sr_elastic_distribution->sample( incoming_energy,
                                          outgoing_energy,
                                          scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.9999995000000930, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // sampleAndRecordTrialsImpl screened rutherford
  native_sr_elastic_distribution->sample( incoming_energy,
                                          outgoing_energy,
                                          scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0-1.0e-6, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check sampleAndRecordTrials can be evaluated
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionNativeFactory, 
                   sampleAndRecordTrials )
{
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution(
                native_cutoff_elastic_distribution,
                *data_container );

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createScreenedRutherfordElasticDistribution(
                native_sr_elastic_distribution,
                native_cutoff_elastic_distribution,
                *data_container );

  // Set fake random number stream
  std::vector<double> fake_stream( 4 );
  // Tabular
  fake_stream[0] = 0.5; // sample angle = 1.249161208881750E-02
  // Screened Rutherford
  fake_stream[1] = 0.0; // sample angle cosine = 1.0
  fake_stream[2] = 0.5; // sample angle = 0.9999995
  fake_stream[3] = 1.0 - 1.0e-15; // sample angle = 0.999999


  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;
  unsigned trials = 10;

  // sampleAndRecordTrialsImpl from distribution
  native_cutoff_elastic_distribution->sampleAndRecordTrials( 
                                          incoming_energy,
                                          outgoing_energy,
                                          scattering_angle_cosine,
                                          trials );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 
                          1.0 - 1.249161208881750E-02, 
                          1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
  TEST_EQUALITY_CONST( trials, 11 );


  scattering_angle_cosine = 0;
  outgoing_energy = 0;

  // sampleAndRecordTrialsImpl screened rutherford
  native_sr_elastic_distribution->sampleAndRecordTrials( 
                                          incoming_energy,
                                          outgoing_energy,
                                          scattering_angle_cosine,
                                          trials );
  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
  TEST_EQUALITY_CONST( trials, 12 );

  // sampleAndRecordTrialsImpl screened rutherford
  native_sr_elastic_distribution->sampleAndRecordTrials( 
                                          incoming_energy,
                                          outgoing_energy,
                                          scattering_angle_cosine,
                                          trials );
  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.9999995000000930, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
  TEST_EQUALITY_CONST( trials, 13 );

  // sampleAndRecordTrialsImpl screened rutherford
  native_sr_elastic_distribution->sampleAndRecordTrials( 
                                          incoming_energy,
                                          outgoing_energy,
                                          scattering_angle_cosine,
                                          trials );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.0-1.0e-6, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
  TEST_EQUALITY_CONST( trials, 14 );
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

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }
  
  // Create the native data file container
  data_container.reset( new Data::ElectronPhotonRelaxationDataContainer( 
						     test_native_file_name ) );

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
// end tstElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
