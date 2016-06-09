//---------------------------------------------------------------------------//
//!
//! \file   tstElasticElectronScatteringDistributionACEFactory.cpp
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
#include "MonteCarlo_ElasticElectronScatteringDistributionACEFactory.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ElasticElectronDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"


//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor;
Teuchos::RCP< const MonteCarlo::CutoffElasticElectronScatteringDistribution>
  ace_cutoff_elastic_distribution;

Teuchos::RCP< const MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution>
  ace_sr_elastic_distribution;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the angular grid can be returned
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionACEFactory,
                   getAngularGrid )
{

  double cutoff_angle_cosine = -1.0;
  Teuchos::Array<double> angular_cosine_grid =
    MonteCarlo::ElasticElectronScatteringDistributionACEFactory::getAngularGrid(
                                                *xss_data_extractor,
                                                0,
                                                cutoff_angle_cosine );
  // Test
  TEST_EQUALITY_CONST( angular_cosine_grid.size(), 3 );
  TEST_EQUALITY_CONST( angular_cosine_grid.front(), -1.0 );
  TEST_EQUALITY_CONST( angular_cosine_grid[1], 0.999999 );
  TEST_EQUALITY_CONST( angular_cosine_grid.back(), 1.0 );

  angular_cosine_grid.clear();

  cutoff_angle_cosine = 0.9;
  angular_cosine_grid =
    MonteCarlo::ElasticElectronScatteringDistributionACEFactory::getAngularGrid(
                                                *xss_data_extractor,
                                                0,
                                                cutoff_angle_cosine );
  // Test
  TEST_EQUALITY_CONST( angular_cosine_grid.size(), 3 );
  TEST_EQUALITY_CONST( angular_cosine_grid.front(), 0.9 );
  TEST_EQUALITY_CONST( angular_cosine_grid[1], 0.999999 );
  TEST_EQUALITY_CONST( angular_cosine_grid.back(), 1.0 );

  angular_cosine_grid.clear();

  cutoff_angle_cosine = -1.0;
  angular_cosine_grid =
    MonteCarlo::ElasticElectronScatteringDistributionACEFactory::getAngularGrid(
                                                *xss_data_extractor,
                                                13,
                                                cutoff_angle_cosine );
  // Test
  TEST_EQUALITY_CONST( angular_cosine_grid.size(), 85 );
  TEST_EQUALITY_CONST( angular_cosine_grid.front(), -1.0 );
  TEST_EQUALITY_CONST( angular_cosine_grid.back(), 1.0 );
  angular_cosine_grid.pop_back();
  TEST_EQUALITY_CONST( angular_cosine_grid.back(), 0.999999 );

}
/*
//---------------------------------------------------------------------------//
// Check that sampleAndRecordTrialsImpl can be evaluated
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionACEFactory,
                   sampleAndRecordTrialsImpl )
{
  MonteCarlo::ElasticElectronScatteringDistributionACEFactory::createCutoffElasticDistributions(
        ace_cutoff_elastic_distribution,
        ace_sr_elastic_distribution,
        *xss_data_extractor );

  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // sample mu = 0.9874366113907
  fake_stream[1] = 0.5; // sample mu = 9.99999500000093

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine;
  unsigned trials = 10;

  // sampleAndRecordTrialsImpl from cutoff distribution
  ace_cutoff_elastic_distribution->sampleAndRecordTrialsImpl(
                                                incoming_energy,
                                                scattering_angle_cosine,
                                                trials );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.874339332031E-01, 1e-12 );
  TEST_EQUALITY_CONST( trials, 11 );

  // sampleAndRecordTrialsImpl from screened Rutherford distribution
  ace_sr_elastic_distribution->sampleAndRecordTrialsImpl(
                                                incoming_energy,
                                                scattering_angle_cosine,
                                                trials );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.99999500000093E-01, 1e-12 );
  TEST_EQUALITY_CONST( trials, 12 );
}
*/
//---------------------------------------------------------------------------//
// Check sample can be evaluated
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionACEFactory,
                   sample )
{
  MonteCarlo::ElasticElectronScatteringDistributionACEFactory::createCutoffElasticDistributions(
                                                ace_cutoff_elastic_distribution,
                                                ace_sr_elastic_distribution,
                                                *xss_data_extractor );
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // sample mu = 0.9874366113907
  fake_stream[1] = 0.5; // sample mu = 9.99999500000093E-01

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;

  // sampleAndRecordTrialsImpl cutoff
  ace_cutoff_elastic_distribution->sample( incoming_energy,
                                           outgoing_energy,
                                           scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.874339332031E-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  scattering_angle_cosine = 0;
  outgoing_energy = 0;

  // sampleAndRecordTrialsImpl screened rutherford
  ace_sr_elastic_distribution->sample( incoming_energy,
                                       outgoing_energy,
                                       scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.99999500000093E-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check sampleAndRecordTrials can be evaluated
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionACEFactory,
                   sampleAndRecordTrials )
{
  MonteCarlo::ElasticElectronScatteringDistributionACEFactory::createCutoffElasticDistribution(
                                                ace_cutoff_elastic_distribution,
                                                *xss_data_extractor );

  MonteCarlo::ElasticElectronScatteringDistributionACEFactory::createScreenedRutherfordElasticDistribution(
                                                ace_sr_elastic_distribution,
                                                ace_cutoff_elastic_distribution,
                                                *xss_data_extractor );
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // sample mu = 0.9874366113907
  fake_stream[1] = 0.5; // sample mu = 9.99999500000093E-01

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;
  unsigned trials = 10;

  // sampleAndRecordTrialsImpl from distribution
  ace_cutoff_elastic_distribution->sampleAndRecordTrials(
                                          incoming_energy,
                                          outgoing_energy,
                                          scattering_angle_cosine,
                                          trials );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.874339332031E-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
  TEST_EQUALITY_CONST( trials, 11 );


  scattering_angle_cosine = 0;
  outgoing_energy = 0;

  // sampleAndRecordTrialsImpl screened rutherford
  ace_sr_elastic_distribution->sampleAndRecordTrials(
                                          incoming_energy,
                                          outgoing_energy,
                                          scattering_angle_cosine,
                                          trials );
  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.99999500000093E-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
  TEST_EQUALITY_CONST( trials, 12 );
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
// end tstElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
