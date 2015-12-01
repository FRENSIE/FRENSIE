//---------------------------------------------------------------------------//
//!
//! \file   tstAnalogElasticElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  Analog elastic electron scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_AnalogElasticElectronScatteringDistribution.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::AnalogElasticElectronScatteringDistribution> 
  ace_elastic_distribution, test_elastic_distribution;
Teuchos::Array<Utility::Pair<double,Teuchos::RCP<const Utility::TabularOneDDistribution> > >
  elastic_scattering_distribution;

double angle_cutoff = 1.0e-6;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution, 
                   evaluate )
{
  // Set energy in MeV and angle cosine 
  double energy = 1.0e-3;
  double scattering_angle = 1.0; // angle cosine = 0.0

  // Calculate the pdf
  double pdf_value = 
    ace_elastic_distribution->evaluate( energy, 
                                        scattering_angle );

  // Test 1 energy 1
  TEST_FLOATING_EQUALITY( pdf_value, 4.821797947867E-02, 1e-12 );


  scattering_angle = .02; // angle cosine = 9.800000000000E-01;
  pdf_value = 
    ace_elastic_distribution->evaluate( energy, 
                                        scattering_angle );

  // Test 2
  TEST_FLOATING_EQUALITY( pdf_value, 8.772194880275E+00, 1e-12 );

  // Test with a different energy
  energy = 1.00E+05;

  scattering_angle = angle_cutoff; // angle cosine = 9.999990000000E-01;
  pdf_value = 
    ace_elastic_distribution->evaluate( energy, 
                                        scattering_angle );

  // Test 2
  TEST_FLOATING_EQUALITY( pdf_value, 4.48786781766095E+05, 1e-15 );

  // Set energy in MeV and angle cosine 
  unsigned energy_bin = 1;
  scattering_angle = 1.0; // angle cosine = 0.0;

  // Calculate the pdf
  pdf_value = 
    ace_elastic_distribution->evaluate( energy_bin, 
                                        scattering_angle );

  // Test 1 energy_bin 1
  TEST_FLOATING_EQUALITY( pdf_value, 4.821797947867E-02, 1e-12 );


  scattering_angle = 0.02; // angle cosine = 9.800000000000E-01;
  pdf_value = 
    ace_elastic_distribution->evaluate( energy_bin, 
                                        scattering_angle );

  // Test 2
  TEST_FLOATING_EQUALITY( pdf_value, 8.772194880275E+00, 1e-12 );


  energy_bin = 13;
  scattering_angle = angle_cutoff; // angle cosine = 9.999990000000E-01;
  pdf_value = 
    ace_elastic_distribution->evaluate( energy_bin, 
                                        scattering_angle );

  // Test 2
  TEST_FLOATING_EQUALITY( pdf_value, 4.48786781766095E+05, 1e-15 );

}

// Check that the pdf can be evaluated
TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution, 
                   evaluatePDF )
{
  // Set energy in MeV and angle cosine 
  double energy = 1.0e-3;
  double scattering_angle = 1.0; // angle cosine = 0.0

  // Calculate the pdf
  double pdf_value = 
    ace_elastic_distribution->evaluatePDF( energy, 
                                           scattering_angle );

  // Test 1 energy 1
  TEST_FLOATING_EQUALITY( pdf_value, 4.821797947867E-02, 1e-12 );


  scattering_angle = .02; // angle cosine = 9.800000000000E-01;
  pdf_value = 
    ace_elastic_distribution->evaluatePDF( energy, 
                                           scattering_angle );

  // Test 2
  TEST_FLOATING_EQUALITY( pdf_value, 8.772194880275E+00, 1e-12 );

  // Test with a different energy
  energy = 1.00E+05;

  scattering_angle = angle_cutoff; // angle cosine = 9.999990000000E-01;
  pdf_value = 
    ace_elastic_distribution->evaluatePDF( energy, 
                                           scattering_angle );

  // Test 2
  TEST_FLOATING_EQUALITY( pdf_value, 4.48786781766095E+05, 1e-15 );

  // Set energy in MeV and angle cosine 
  unsigned energy_bin = 1;
  scattering_angle = 1.0; // angle cosine = 0.0;

  // Calculate the pdf
  pdf_value = 
    ace_elastic_distribution->evaluatePDF( energy_bin, 
                                           scattering_angle );

  // Test 1 energy_bin 1
  TEST_FLOATING_EQUALITY( pdf_value, 4.821797947867E-02, 1e-12 );


  scattering_angle = 0.02; // angle cosine = 9.800000000000E-01;
  pdf_value = 
    ace_elastic_distribution->evaluatePDF( energy_bin, 
                                           scattering_angle );

  // Test 2
  TEST_FLOATING_EQUALITY( pdf_value, 8.772194880275E+00, 1e-12 );


  energy_bin = 13;
  scattering_angle = angle_cutoff; // angle cosine = 9.999990000000E-01;
  pdf_value = 
    ace_elastic_distribution->evaluatePDF( energy_bin, 
                                           scattering_angle );

  // Test 2
  TEST_FLOATING_EQUALITY( pdf_value, 4.48786781766095E+05, 1e-15 );

}

//---------------------------------------------------------------------------//
// Check that the cdf can be evaluated
TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution, 
                   evaluateCDF )
{
  // Set energy in MeV and angle cosine 
  double energy = 1.0e-3;
  double scattering_angle = 1.0; // angle cosine = 0.0

  // Calculate the cdf
  double cdf_value = 
    ace_elastic_distribution->evaluateCDF( energy, 
                                           scattering_angle );

  // Test 1 energy 1
  TEST_FLOATING_EQUALITY( cdf_value, 9.663705658970E-02, 1e-12 );


  scattering_angle = .02; // angle cosine = 9.800000000000E-01;
  cdf_value = 
    ace_elastic_distribution->evaluateCDF( energy, 
                                           scattering_angle );

  // Test 2
  TEST_FLOATING_EQUALITY( cdf_value, 4.211953219580E-01, 1e-12 );

  // Test with a different energy
  energy = 1.00E+05;

  scattering_angle = angle_cutoff; // angle cosine = 9.999990000000E-01;
  cdf_value = 
    ace_elastic_distribution->evaluateCDF( energy, 
                                           scattering_angle );

  // Test 2
  TEST_FLOATING_EQUALITY( cdf_value, 5.512132182210E-01, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the cross section ratio can be evaluated
TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution, 
                   evaluateCutoffCrossSectionRatio )
{
  // Set energy in MeV and angle cosine 
  double energy = 1.0e-3;
  double scattering_angle = 1.0; // angle cosine = 0.0
  double max_cdf = 9.9990922382800E-01;

  // Create the distribution
  test_elastic_distribution.reset(
		new MonteCarlo::AnalogElasticElectronScatteringDistribution(
						    elastic_scattering_distribution,
                            scattering_angle,
                            false ) );

  // Calculate the cdf
  double cdf_value = 
    test_elastic_distribution->evaluateCutoffCrossSectionRatio( energy );

  // Test 1 energy 1
  TEST_FLOATING_EQUALITY( cdf_value, 9.663705658970E-02/max_cdf, 1e-12 );


  scattering_angle = .02; // angle cosine = 9.800000000000E-01;
  // Create the distribution
  test_elastic_distribution.reset(
		new MonteCarlo::AnalogElasticElectronScatteringDistribution(
						    elastic_scattering_distribution,
                            scattering_angle,
                            false ) );

  cdf_value = 
    test_elastic_distribution->evaluateCutoffCrossSectionRatio( energy );

  // Test 2
  TEST_FLOATING_EQUALITY( cdf_value, 4.211953219580E-01/max_cdf, 1e-12 );

  // Test with a different energy
  energy = 1.00E+05;

  scattering_angle = angle_cutoff; // angle cosine = 9.999990000000E-01;
  // Create the distribution
  test_elastic_distribution.reset(
		new MonteCarlo::AnalogElasticElectronScatteringDistribution(
						    elastic_scattering_distribution,
                            scattering_angle,
                            false ) );
  cdf_value = 
    test_elastic_distribution->evaluateCutoffCrossSectionRatio( energy );

  // Test 2
  TEST_FLOATING_EQUALITY( cdf_value, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the energy can be returned
TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution, 
                   getEnergy )
{
  // Set energy bin
  unsigned energy_bin = 1;

  double energy = 
    ace_elastic_distribution->getEnergy( energy_bin );

  TEST_FLOATING_EQUALITY( energy, 1.0e-3, 1e-12 );


  energy_bin = 13;
  energy = 
    ace_elastic_distribution->getEnergy( energy_bin );

  TEST_FLOATING_EQUALITY( energy, 1.0e+5, 1e-12 );

}

//---------------------------------------------------------------------------//
// Check that sampleAndRecordTrialsImpl can be evaluated
TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution, 
                   sampleAndRecordTrialsImpl )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 0.9874366113907

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine;
  unsigned trials = 10;

  // sampleAndRecordTrialsImpl from distribution
  ace_elastic_distribution->sampleAndRecordTrialsImpl( 
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.874339332031E-01, 1e-12 );
  TEST_EQUALITY_CONST( trials, 11 );
}


//---------------------------------------------------------------------------//
// Check sample can be evaluated
TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution, 
                   sample )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 0.9874366113907

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine, outgoing_energy;

  // sampleAndRecordTrialsImpl from distribution
  ace_elastic_distribution->sample( electron.getEnergy(),
                                          outgoing_energy,
                                          scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.874339332031E-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check sampleAndRecordTrials can be evaluated
TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution, 
                   sampleAndRecordTrials )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 0.9874366113907

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine, outgoing_energy;
  unsigned trials = 10;

  // sampleAndRecordTrialsImpl from distribution
  ace_elastic_distribution->sampleAndRecordTrials( 
                                          electron.getEnergy(),
                                          outgoing_energy,
                                          scattering_angle_cosine,
                                          trials );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.874339332031E-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution, 
                   ScatterElectron )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 0.9874366113907

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  MonteCarlo::SubshellType shell_of_interaction;
  
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter electron
  ace_elastic_distribution->scatterElectron( electron, 
                                                   bank, 
                                                   shell_of_interaction );

  // Test
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 9.874339332031E-01, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getEnergy(), 1.0e-3, 1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
TEUCHOS_UNIT_TEST( AnalogElasticElectronScatteringDistribution, 
                   ScatterAdjointElectron )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 0.9874366113907

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  MonteCarlo::SubshellType shell_of_interaction;
  
  MonteCarlo::AdjointElectronState adjoint_electron( 0 );
  adjoint_electron.setEnergy( 1.0e-3 );
  adjoint_electron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter electron
  ace_elastic_distribution->scatterAdjointElectron( 
                                                   adjoint_electron, 
                                                   bank, 
                                                   shell_of_interaction );

  // Test
  TEST_FLOATING_EQUALITY( adjoint_electron.getZDirection(), 
                          9.874339332031E-01, 
                          1e-12 );
  TEST_FLOATING_EQUALITY( adjoint_electron.getEnergy(), 1.0e-3, 1e-12 );

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
  Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor(
                            new Data::XSSEPRDataExtractor( 
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );

  // Extract the elastic scattering information data block (ELASI)
  Teuchos::ArrayView<const double> elasi_block(
				      xss_data_extractor->extractELASIBlock() );
  
  // Extract the number of tabulated distributions
  int size = elasi_block.size()/3;

  // Extract the energy grid for elastic scattering angular distributions
  Teuchos::Array<double> energy_grid(elasi_block(0,size));

  // Extract the table lengths for elastic scattering angular distributions
  Teuchos::Array<double> table_length(elasi_block(size,size));

  // Extract the offsets for elastic scattering angular distributions
  Teuchos::Array<double> offset(elasi_block(2*size,size));

  // Extract the elastic scattering angular distributions block (elas)
  Teuchos::ArrayView<const double> elas_block = 
    xss_data_extractor->extractELASBlock();

  // Create the elastic scattering distributions
  elastic_scattering_distribution.resize( size );
  
  for( unsigned n = 0; n < size; ++n )
  {
    elastic_scattering_distribution[n].first = energy_grid[n];

    elastic_scattering_distribution[n].second.reset( 
	  new Utility::HistogramDistribution(
		 elas_block( offset[n], table_length[n] ),
		 elas_block( offset[n] + 1 + table_length[n], table_length[n]-1 ),
         true ) );
  }  

  // Get the atomic number 
  const int atomic_number = xss_data_extractor->extractAtomicNumber();

  // Create the distributions
  ace_elastic_distribution.reset(
        new MonteCarlo::AnalogElasticElectronScatteringDistribution(
                elastic_scattering_distribution,
                angle_cutoff,
                false ) );

  // Clear setup data
  ace_file_handler.reset();
  xss_data_extractor.reset();

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
// end tstAnalogElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
