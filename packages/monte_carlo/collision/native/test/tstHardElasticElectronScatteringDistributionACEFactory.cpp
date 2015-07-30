//---------------------------------------------------------------------------//
//!
//! \file   tstHardElasticElectronScatteringDistributionACEFactory.cpp
//! \author Luke Kersting
//! \brief  Hard elastic electron scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_HardElasticElectronScatteringDistributionACEFactory.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor;
Teuchos::RCP< const MonteCarlo::HardElasticElectronScatteringDistribution> 
  ace_basic_elastic_distribution;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the common angular grid can be created
TEUCHOS_UNIT_TEST( HardElasticElectronScatteringDistributionACEFactory, 
                   createCommonAngularGrid )
{

  Teuchos::Array<double> common_angular_grid;
  double cutoff_angle = -1.0;

  MonteCarlo::HardElasticElectronScatteringDistributionACEFactory::createCommonAngularGrid(
                                                *xss_data_extractor,
                                                common_angular_grid,
                                                cutoff_angle );

  // Test
  TEST_EQUALITY_CONST( common_angular_grid.size(), 407 );
  TEST_EQUALITY_CONST( common_angular_grid.front(), -1.0 );
  TEST_EQUALITY_CONST( common_angular_grid.back(), 1.0 );
  common_angular_grid.pop_back();
  TEST_EQUALITY_CONST( common_angular_grid.back(), 0.999999 );


  cutoff_angle = 0.9;
  common_angular_grid.clear();

  MonteCarlo::HardElasticElectronScatteringDistributionACEFactory::createCommonAngularGrid(
                                                *xss_data_extractor,
                                                common_angular_grid,
                                                cutoff_angle );

  // Test
  TEST_EQUALITY_CONST( common_angular_grid.front(), cutoff_angle );
  TEST_EQUALITY_CONST( common_angular_grid.back(), 1.0 );
  common_angular_grid.pop_back();
  TEST_EQUALITY_CONST( common_angular_grid.back(), 0.999999 );
}

//---------------------------------------------------------------------------//
// Check that the angular grid can be returned
TEUCHOS_UNIT_TEST( HardElasticElectronScatteringDistributionACEFactory, 
                   getAngularGrid )
{

  double cutoff_angle = -1.0;
  Teuchos::Array<double> angular_grid =
    MonteCarlo::HardElasticElectronScatteringDistributionACEFactory::getAngularGrid(
                                                *xss_data_extractor,
                                                0,
                                                cutoff_angle );
  // Test
  TEST_EQUALITY_CONST( angular_grid.size(), 3 );
  TEST_EQUALITY_CONST( angular_grid.front(), -1.0 );
  TEST_EQUALITY_CONST( angular_grid[1], 0.999999 );
  TEST_EQUALITY_CONST( angular_grid.back(), 1.0 );

  angular_grid.clear();

  cutoff_angle = 0.9;
  angular_grid =
    MonteCarlo::HardElasticElectronScatteringDistributionACEFactory::getAngularGrid(
                                                *xss_data_extractor,
                                                0,
                                                cutoff_angle );
  // Test
  TEST_EQUALITY_CONST( angular_grid.size(), 3 );
  TEST_EQUALITY_CONST( angular_grid.front(), 0.9 );
  TEST_EQUALITY_CONST( angular_grid[1], 0.999999 );
  TEST_EQUALITY_CONST( angular_grid.back(), 1.0 );

  angular_grid.clear();

  cutoff_angle = -1.0;
  angular_grid =
    MonteCarlo::HardElasticElectronScatteringDistributionACEFactory::getAngularGrid(
                                                *xss_data_extractor,
                                                13,
                                                cutoff_angle );
  // Test
  TEST_EQUALITY_CONST( angular_grid.size(), 85 );
  TEST_EQUALITY_CONST( angular_grid.front(), -1.0 );
  TEST_EQUALITY_CONST( angular_grid.back(), 1.0 );
  angular_grid.pop_back();
  TEST_EQUALITY_CONST( angular_grid.back(), 0.999999 );

}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
TEUCHOS_UNIT_TEST( HardElasticElectronScatteringDistributionACEFactory, 
                   evaluateMoliereScreeningConstant )
{
  MonteCarlo::HardElasticElectronScatteringDistributionACEFactory::createHardElasticDistribution(
                                                *xss_data_extractor,
                                                ace_basic_elastic_distribution );
  // Set energy in MeV
  double energy = 1.0;

  // Calculate scrrening angle
  double screening_factor = 
    ace_basic_elastic_distribution->evaluateMoliereScreeningConstant( energy );

  // Test
  TEST_FLOATING_EQUALITY( screening_factor, 1.9610611503219500E-04, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screened analytical function angle can be evaluated
TEUCHOS_UNIT_TEST( HardElasticElectronScatteringDistributionACEFactory, 
                   evaluateScreenedScatteringAngle )
{
  MonteCarlo::HardElasticElectronScatteringDistributionACEFactory::createHardElasticDistribution(
                                                *xss_data_extractor,
                                                ace_basic_elastic_distribution );

  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Set energy in MeV
  double energy = 1.0;

  // Calculate screening angle
  double scattering_angle_cosine = 
    ace_basic_elastic_distribution->evaluateScreenedScatteringAngle( energy );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999501272, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that sampleAndRecordTrialsImpl can be evaluated from the distribution
TEUCHOS_UNIT_TEST( HardElasticElectronScatteringDistributionACEFactory, 
                   sampleAndRecordTrialsImpl_distribution )
{
  MonteCarlo::HardElasticElectronScatteringDistributionACEFactory::createHardElasticDistribution(
                                                *xss_data_extractor,
                                                ace_basic_elastic_distribution );

  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 9.9990E-01; // sample angle from distribution
  fake_stream[1] = 0.5; // sample mu = 0.9874366113907

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine;
  unsigned trials = 10;

  // sampleAndRecordTrialsImpl from distribution
  ace_basic_elastic_distribution->sampleAndRecordTrialsImpl( 
                                                incoming_energy,
                                                scattering_angle_cosine,
                                                trials );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.874339332031E-01, 1e-12 );
  TEST_EQUALITY_CONST( trials, 11 );
}
//---------------------------------------------------------------------------//
// Check that sampleAndRecordTrialsImpl can be evaluated from the screened analytical function
TEUCHOS_UNIT_TEST( HardElasticElectronScatteringDistributionACEFactory, 
                   sampleAndRecordTrialsImpl_analytical )
{
  MonteCarlo::HardElasticElectronScatteringDistributionACEFactory::createHardElasticDistribution(
                                                *xss_data_extractor,
                                                ace_basic_elastic_distribution );

  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 9.9991E-01;
  fake_stream[1] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine;
  unsigned trials = 10;

  // sampleAndRecordTrialsImpl from analytical function
  ace_basic_elastic_distribution->sampleAndRecordTrialsImpl( 
                                                incoming_energy,
                                                scattering_angle_cosine,
                                                trials );;

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999500000, 1e-12 );
  TEST_EQUALITY_CONST( trials, 11 );

}

//---------------------------------------------------------------------------//
// Check sample can be evaluated from the distribution
TEUCHOS_UNIT_TEST( HardElasticElectronScatteringDistributionACEFactory, 
                   sample_distribution )
{
  MonteCarlo::HardElasticElectronScatteringDistributionACEFactory::createHardElasticDistribution(
                                                *xss_data_extractor,
                                                ace_basic_elastic_distribution );
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 9.9990E-01; // sample angle from distribution
  fake_stream[1] = 0.5; // sample mu = 0.9874366113907

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;

  // sampleAndRecordTrialsImpl from distribution
  ace_basic_elastic_distribution->sample( incoming_energy,
                                          outgoing_energy,
                                          scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.874339332031E-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
}
//---------------------------------------------------------------------------//
// Check that sample can be evaluated from the screened analytical function
TEUCHOS_UNIT_TEST( HardElasticElectronScatteringDistributionACEFactory, 
                   sample_analytical )
{
  MonteCarlo::HardElasticElectronScatteringDistributionACEFactory::createHardElasticDistribution(
                                                *xss_data_extractor,
                                                ace_basic_elastic_distribution );

  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 9.9991E-01;
  fake_stream[1] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  double incoming_energy = 1.1e-3 ;
  double scattering_angle_cosine, outgoing_energy;

  // sampleAndRecordTrialsImpl from analytical function
  ace_basic_elastic_distribution->sample( incoming_energy,
                                          outgoing_energy,
                                          scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999500000, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.1e-3, 1e-12 );

}
//---------------------------------------------------------------------------//
// Check sampleAndRecordTrials can be evaluated from the distribution
TEUCHOS_UNIT_TEST( HardElasticElectronScatteringDistributionACEFactory, 
                   sampleAndRecordTrials_distribution )
{
  MonteCarlo::HardElasticElectronScatteringDistributionACEFactory::createHardElasticDistribution(
                                                *xss_data_extractor,
                                                ace_basic_elastic_distribution );
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 9.9990E-01; // sample angle from distribution
  fake_stream[1] = 0.5; // sample mu = 0.9874366113907

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;
  unsigned trials = 10;

  // sampleAndRecordTrialsImpl from distribution
  ace_basic_elastic_distribution->sampleAndRecordTrials( 
                                          incoming_energy,
                                          outgoing_energy,
                                          scattering_angle_cosine,
                                          trials );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.874339332031E-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
}
//---------------------------------------------------------------------------//
// Check that sampleAndRecordTrials can be evaluated from the screened analytical function
TEUCHOS_UNIT_TEST( HardElasticElectronScatteringDistributionACEFactory, 
                   sampleAndRecordTrials_analytical )
{
  MonteCarlo::HardElasticElectronScatteringDistributionACEFactory::createHardElasticDistribution(
                                                *xss_data_extractor,
                                                ace_basic_elastic_distribution );
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 9.9991E-01;
  fake_stream[1] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  double incoming_energy = 1.1e-3;
  double scattering_angle_cosine, outgoing_energy;
  unsigned trials = 10;

  // sampleAndRecordTrialsImpl from analytical function
  ace_basic_elastic_distribution->sampleAndRecordTrials( 
                                          incoming_energy,
                                          outgoing_energy,
                                          scattering_angle_cosine,
                                          trials );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999500000, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.1e-3, 1e-12 );

}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_ace_file_name, test_ace_table_name;
  
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_ace_file",
		 &test_ace_file_name,
		 "Test ACE file name" );
  clp.setOption( "test_ace_table",
		 &test_ace_table_name,
		 "Test ACE table name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }
  
  // Create a file handler and data extractor
  Teuchos::RCP<Data::ACEFileHandler> ace_file_handler( 
				 new Data::ACEFileHandler( test_ace_file_name,
							   test_ace_table_name,
							   1u ) );
  xss_data_extractor.reset( new Data::XSSEPRDataExtractor( 
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );

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
// end tstHardElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
