//---------------------------------------------------------------------------//
//!
//! \file   tstScreenedRutherfordElasticElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  ScreenedRutherford elastic electron scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ScreenedRutherfordElasticElectronScatteringDistribution.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution> 
  ace_elastic_distribution, endl_elastic_distribution;

Teuchos::RCP<const Utility::TabularDistribution<Utility::LinLin> >
  elastic_cutoff_pdf;

double angle_cutoff = 1.0e-6;
double angle_cosine_cutoff = 0.999999;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the pdf can be evaluated
TEUCHOS_UNIT_TEST( ScreenedRutherfordElasticElectronScatteringDistribution, 
                   evaluatePDF )
{
  // Set energy in MeV
  double energy = 1.0e+5;
  double scattering_angle = angle_cutoff; // angle cosine = 9.999990000000E-01;

  // Calculate the pdf
  double pdf_value = 
    ace_elastic_distribution->evaluatePDF( energy, 
                                           scattering_angle );
  // Test 1 energy 1
  TEST_FLOATING_EQUALITY( pdf_value, 4.487867817660950E+05, 1e-12 );


  scattering_angle = 5e-7; // angle cosine = 9.999995000000E-01;
  pdf_value = 
    ace_elastic_distribution->evaluatePDF( energy, 
                                           scattering_angle );
  // Test 2 energy 1
  TEST_FLOATING_EQUALITY( pdf_value, 1.795146978107500E+06, 1e-12 );


  scattering_angle = 0.0; // angle cosine = 1.0
  pdf_value = 
    ace_elastic_distribution->evaluatePDF( energy, 
                                           scattering_angle );
  // Test 3 energy 1
  TEST_FLOATING_EQUALITY( pdf_value, 2.607227775513000E+20, 1e-12 );



  // Test with a different energy
  energy = 1.00E-04;

  scattering_angle = angle_cutoff; // angle cosine = 9.999990000000E-01;
  pdf_value = 
    ace_elastic_distribution->evaluatePDF( energy, 
                                           scattering_angle );
  // Test 1  energy 2
  TEST_FLOATING_EQUALITY( pdf_value, 8.706924726988590E+00, 1e-15 );


  scattering_angle = 5e-7; // angle cosine = 9.999995000000E-01;
  pdf_value = 
    ace_elastic_distribution->evaluatePDF( energy, 
                                           scattering_angle );
  // Test 2 energy 2
  TEST_FLOATING_EQUALITY( pdf_value, 8.706924834818060E+00, 1e-12 );


  scattering_angle = 0.0; // angle cosine = 1.0
  pdf_value = 
    ace_elastic_distribution->evaluatePDF( energy, 
                                           scattering_angle );
  // Test 3  energy 2
  TEST_FLOATING_EQUALITY( pdf_value, 8.706924942647520E+00, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the cdf can be evaluated
TEUCHOS_UNIT_TEST( ScreenedRutherfordElasticElectronScatteringDistribution, 
                   evaluateCDF )
{
  // Set energy in MeV
  double energy = 1.0e+5;
  double scattering_angle = angle_cutoff; // angle cosine = 9.999990000000E-01;

  // Calculate the cdf
  double cdf_value = 
    ace_elastic_distribution->evaluateCDF( energy, 
                                           scattering_angle );
  // Test 1 energy 1
  TEST_FLOATING_EQUALITY( cdf_value, 1.0, 1e-12 );


  scattering_angle = 5e-7; // angle cosine = 9.999995000000E-01;
  cdf_value = 
    ace_elastic_distribution->evaluateCDF( energy, 
                                           scattering_angle );
  // Test 2 energy 1
  TEST_FLOATING_EQUALITY( cdf_value, 9.99999958511234000E-01, 1e-12 );


  scattering_angle = 0.0; // angle cosine = 1.0
  cdf_value = 
    ace_elastic_distribution->evaluateCDF( energy, 
                                           scattering_angle );
  // Test 3 energy 1
  TEST_FLOATING_EQUALITY( cdf_value, 0.0, 1e-12 );



  // Test with a different energy
  energy = 1.00E-04;

  scattering_angle = angle_cutoff; // angle cosine = 9.999990000000E-01;
  cdf_value = 
    ace_elastic_distribution->evaluateCDF( energy, 
                                           scattering_angle );
  // Test 1  energy 2
  TEST_FLOATING_EQUALITY( cdf_value, 1.0, 1e-15 );


  scattering_angle = 5e-7; // angle cosine = 9.999995000000E-01;
  cdf_value = 
    ace_elastic_distribution->evaluateCDF( energy, 
                                           scattering_angle );
  // Test 2 energy 2
  TEST_FLOATING_EQUALITY( cdf_value, 5.00000003096084000E-01, 1e-12 );


  scattering_angle = 0.0; // angle cosine = 1.0
  cdf_value = 
    ace_elastic_distribution->evaluateCDF( energy, 
                                           scattering_angle );
  // Test 3  energy 2
  TEST_FLOATING_EQUALITY( cdf_value, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that sampleAndRecordTrialsImpl can be evaluated
TEUCHOS_UNIT_TEST( ScreenedRutherfordElasticElectronScatteringDistribution, 
                   sampleAndRecordTrialsImpl )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 9.99999500000093E-01,

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
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.99999500000093E-01, 1e-12 );
  TEST_EQUALITY_CONST( trials, 11 );
}


//---------------------------------------------------------------------------//
// Check sample can be evaluated
TEUCHOS_UNIT_TEST( ScreenedRutherfordElasticElectronScatteringDistribution, 
                   sample )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 9.99999500000093E-01

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
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.99999500000093E-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check sampleAndRecordTrials can be evaluated
TEUCHOS_UNIT_TEST( ScreenedRutherfordElasticElectronScatteringDistribution, 
                   sampleAndRecordTrials )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 9.99999500000093E-01,

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
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.99999500000093E-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
TEUCHOS_UNIT_TEST( ScreenedRutherfordElasticElectronScatteringDistribution, 
                   ScatterElectron )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 9.99999500000093E-01,

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
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 9.99999500000093E-01, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getEnergy(), 1.0e-3, 1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
TEUCHOS_UNIT_TEST( ScreenedRutherfordElasticElectronScatteringDistribution, 
                   ScatterAdjointElectron )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 9.99999500000093E-01,

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
                          9.99999500000093E-01, 
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
  Teuchos::Array<Utility::Pair<double,Teuchos::RCP<const Utility::TabularOneDDistribution> > >
    elastic_scattering_distribution( size );

  // Extract the cutoff pdf values for each energy grid point
  Teuchos::Array<double> cutoff_pdf( size );
  
  for( unsigned n = 0; n < size; ++n )
  {
    elastic_scattering_distribution[n].first = energy_grid[n];

    elastic_scattering_distribution[n].second.reset( 
	  new Utility::HistogramDistribution(
		 elas_block( offset[n], table_length[n] ),
		 elas_block( offset[n] + 1 + table_length[n], table_length[n]-1 ),
         true ) );
/*	  new Utility::TabularDistribution<Utility::LinLin>(
		 elas_block( offset[n], table_length[n] ),
		 elas_block( offset[n] + 1 + table_length[n], table_length[n] ),
         true ) );
*/
    cutoff_pdf[n] = 
        elastic_scattering_distribution[n].second->evaluatePDF( 
            angle_cosine_cutoff );    
  }  

  elastic_cutoff_pdf.reset(
    new Utility::TabularDistribution<Utility::LinLin>(
		 energy_grid,
		 cutoff_pdf,
         false ) );

  // Get the atomic number 
  const int atomic_number = xss_data_extractor->extractAtomicNumber();

  // Create the distributions
  ace_elastic_distribution.reset(
		new MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution(
						    elastic_cutoff_pdf,
                            atomic_number,
                            angle_cutoff ) );

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
// end tstScreenedRutherfordElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
