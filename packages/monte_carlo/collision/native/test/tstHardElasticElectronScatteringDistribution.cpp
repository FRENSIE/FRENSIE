//---------------------------------------------------------------------------//
//!
//! \file   tstHardElasticElectronScatteringDistribution.cpp
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
#include "MonteCarlo_HardElasticElectronScatteringDistribution.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::HardElasticElectronScatteringDistribution> 
  ace_basic_elastic_distribution;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the pdf can be evaluated
TEUCHOS_UNIT_TEST( HardElasticElectronScatteringDistribution, 
                   evaluatePDF )
{
  // Set energy in MeV and angle cosine 
  double energy = 1.0e-3;
  double scattering_angle_cosine = 0.0;

  // Calculate the pdf
  double pdf_value = 
    ace_basic_elastic_distribution->evaluatePDF( energy, 
                                                 scattering_angle_cosine );

  // Test 1 energy 1
  TEST_FLOATING_EQUALITY( pdf_value, 4.821797947867E-02, 1e-12 );


  scattering_angle_cosine = 9.800000000000E-01;
  pdf_value = 
    ace_basic_elastic_distribution->evaluatePDF( energy, 
                                                 scattering_angle_cosine );

  // Test 2
  TEST_FLOATING_EQUALITY( pdf_value, 8.772194880275E+00, 1e-12 );

  // Test with a different energy
  energy = 1.00E+05;
  scattering_angle_cosine = -1.000000000000E+00;
  pdf_value = 
    ace_basic_elastic_distribution->evaluatePDF( energy, 
                                                 scattering_angle_cosine );

  // Test 1
  TEST_FLOATING_EQUALITY( pdf_value, 4.704745346116E-09, 1e-12 );


  scattering_angle_cosine = 9.999990000000E-01;
  pdf_value = 
    ace_basic_elastic_distribution->evaluatePDF( energy, 
                                                 scattering_angle_cosine );

  // Test 2
  TEST_FLOATING_EQUALITY( pdf_value, 4.48786781766095E+05, 1e-15 );

  // Set energy in MeV and angle cosine 
  unsigned energy_bin = 1;
  scattering_angle_cosine = 0.0;

  // Calculate the pdf
  pdf_value = 
    ace_basic_elastic_distribution->evaluatePDF( energy_bin, 
                                                 scattering_angle_cosine );

  // Test 1 energy_bin 1
  TEST_FLOATING_EQUALITY( pdf_value, 4.821797947867E-02, 1e-12 );


  scattering_angle_cosine = 9.800000000000E-01;
  pdf_value = 
    ace_basic_elastic_distribution->evaluatePDF( energy_bin, 
                                                 scattering_angle_cosine );

  // Test 2
  TEST_FLOATING_EQUALITY( pdf_value, 8.772194880275E+00, 1e-12 );

  // Test with a different energy_bin
  energy_bin = 13;
  scattering_angle_cosine = -1.000000000000E+00;
  pdf_value = 
    ace_basic_elastic_distribution->evaluatePDF( energy_bin, 
                                                 scattering_angle_cosine );

  // Test 1
  TEST_FLOATING_EQUALITY( pdf_value, 4.704745346116E-09, 1e-12 );


  scattering_angle_cosine = 9.999990000000E-01;
  pdf_value = 
    ace_basic_elastic_distribution->evaluatePDF( energy_bin, 
                                                 scattering_angle_cosine );

  // Test 2
  TEST_FLOATING_EQUALITY( pdf_value, 4.48786781766095E+05, 1e-15 );

}


//---------------------------------------------------------------------------//
// Check that the pdf can be evaluated
TEUCHOS_UNIT_TEST( HardElasticElectronScatteringDistribution, 
                   evaluateScreenedRutherfordPDF )
{
  // Set energy in MeV and angle cosine 
  double energy = 1.0e-3;

  long double scattering_angle_cosine = 9.999992000000E-01L;
  double pdf_value = 
    ace_basic_elastic_distribution->evaluateScreenedRutherfordPDF( energy, 
                                                 scattering_angle_cosine );

  // Test 1
  TEST_FLOATING_EQUALITY( pdf_value, 9.07761855353150E+01, 1e-12 );

  scattering_angle_cosine = 9.999994000000E-01L;
  pdf_value = 
    ace_basic_elastic_distribution->evaluateScreenedRutherfordPDF( energy, 
                                                 scattering_angle_cosine );

  // Test 2
  TEST_FLOATING_EQUALITY( pdf_value, 9.07761990732033E+01, 1e-12 );

  scattering_angle_cosine = 9.999996000000E-01L;
  pdf_value = 
    ace_basic_elastic_distribution->evaluateScreenedRutherfordPDF( energy, 
                                                 scattering_angle_cosine );

  // Test 3
  TEST_FLOATING_EQUALITY( pdf_value, 9.07762126110947E+01, 1e-12 );

  scattering_angle_cosine = 9.999998000000E-01L;
  pdf_value = 
    ace_basic_elastic_distribution->evaluateScreenedRutherfordPDF( energy, 
                                                 scattering_angle_cosine );

  // Test 4
  TEST_FLOATING_EQUALITY( pdf_value, 9.07762261489891E+01, 1e-12 );

  scattering_angle_cosine = 1.000000000000E+00L;
  pdf_value = 
    ace_basic_elastic_distribution->evaluateScreenedRutherfordPDF( energy, 
                                                 scattering_angle_cosine );

  // Test 5
  TEST_FLOATING_EQUALITY( pdf_value, 9.07762396868865E+01, 1e-12 );


  // Test with a different energy
  energy = 1.00E+05;

  scattering_angle_cosine = 9.99999200000000000000E-01L;
  pdf_value = 
    ace_basic_elastic_distribution->evaluateScreenedRutherfordPDF( energy, 
                                                 scattering_angle_cosine );

  // Test 1
  TEST_FLOATING_EQUALITY( pdf_value, 7.01229331962953E+05, 1e-12 );

  scattering_angle_cosine = 9.999994000000E-01L;
  pdf_value = 
    ace_basic_elastic_distribution->evaluateScreenedRutherfordPDF( energy, 
                                                 scattering_angle_cosine );

  // Test 2
  TEST_FLOATING_EQUALITY( pdf_value, 1.24662988038874E+06, 1e-12 );

  scattering_angle_cosine = 9.999996000000E-01L;
  pdf_value = 
    ace_basic_elastic_distribution->evaluateScreenedRutherfordPDF( energy, 
                                                 scattering_angle_cosine );

  // Test 3
  TEST_FLOATING_EQUALITY( pdf_value, 2.80491703692042E+06, 1e-12 );

  scattering_angle_cosine = 9.999998000000E-01L;
  pdf_value = 
    ace_basic_elastic_distribution->evaluateScreenedRutherfordPDF( energy, 
                                                 scattering_angle_cosine );

  // Test 4
  TEST_FLOATING_EQUALITY( pdf_value, 1.12196658202311E+07, 1e-12 );

  scattering_angle_cosine = 1.000000000000E+00L;
  pdf_value = 
    ace_basic_elastic_distribution->evaluateScreenedRutherfordPDF( energy, 
                                                 scattering_angle_cosine );

  // Test 5
  TEST_FLOATING_EQUALITY( pdf_value, 2.60722777551300E+20, 1e-10 );

}

//---------------------------------------------------------------------------//
// Check that the energy can be returned
TEUCHOS_UNIT_TEST( HardElasticElectronScatteringDistribution, 
                   getEnergy )
{
  // Set energy bin
  unsigned energy_bin = 1;

  double energy = 
    ace_basic_elastic_distribution->getEnergy( energy_bin );

  TEST_FLOATING_EQUALITY( energy, 1.0e-3, 1e-12 );


  energy_bin = 13;
  energy = 
    ace_basic_elastic_distribution->getEnergy( energy_bin );

  TEST_FLOATING_EQUALITY( energy, 1.0e+5, 1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the screened Rutherford cross section ratio can be evaluated
TEUCHOS_UNIT_TEST( HardElasticElectronScatteringDistribution, 
                   evaluateScreenedRutherfordCrossSectionRatio )
{
  // Set energy in MeV
  double energy = 1.0e-5;

  // Calculate screening constant
  double ratio = 
    ace_basic_elastic_distribution->
                evaluateScreenedRutherfordCrossSectionRatio( energy );

  // Test 1
  TEST_FLOATING_EQUALITY( ratio, 5.000000001434400E-07, 1e-12 );

 
  energy = 1.0;
  ratio = 
    ace_basic_elastic_distribution->
                evaluateScreenedRutherfordCrossSectionRatio( energy );

  // Test 2
  TEST_FLOATING_EQUALITY( ratio, 2.579243469610230E-02, 1e-12 );


  energy = 1.0e5;
  ratio = 
    ace_basic_elastic_distribution->
                evaluateScreenedRutherfordCrossSectionRatio( energy );

  // Test 3
  TEST_FLOATING_EQUALITY( ratio, 1.081706689774850E+07, 1e-12 );

}

//---------------------------------------------------------------------------//
// Check that Moliere's screening constant can be evaluated
TEUCHOS_UNIT_TEST( HardElasticElectronScatteringDistribution, 
                   evaluateMoliereScreeningConstant )
{
  // Set energy in MeV
  double energy = 1.0e-5;

  // Calculate screening constant
  double screening_factor = 
    ace_basic_elastic_distribution->evaluateMoliereScreeningConstant( energy );

  // Test 1
  TEST_FLOATING_EQUALITY( screening_factor, 2.5131795894201700E+03, 1e-12 );

 
  energy = 1.0;
  screening_factor = 
    ace_basic_elastic_distribution->evaluateMoliereScreeningConstant( energy );

  // Test 2
  TEST_FLOATING_EQUALITY( screening_factor, 1.9610611503219500E-04, 1e-12 );


  energy = 1.0e5;
  screening_factor = 
    ace_basic_elastic_distribution->evaluateMoliereScreeningConstant( energy );

  // Test 3
  TEST_FLOATING_EQUALITY( screening_factor, 4.1488769980623900E-14, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screened analytical function angle can be evaluated
TEUCHOS_UNIT_TEST( HardElasticElectronScatteringDistribution, 
                   evaluateScreenedScatteringAngle )
{
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
TEUCHOS_UNIT_TEST( HardElasticElectronScatteringDistribution, 
                   sampleAndRecordTrialsImpl_distribution )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 9.9990E-01; // sample angle from distribution
  fake_stream[1] = 0.5; // sample mu = 0.9874366113907

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine;
  unsigned trials = 10;

  // sampleAndRecordTrialsImpl from distribution
  ace_basic_elastic_distribution->sampleAndRecordTrialsImpl( 
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.874339332031E-01, 1e-12 );
  TEST_EQUALITY_CONST( trials, 11 );
}
//---------------------------------------------------------------------------//
// Check that sampleAndRecordTrialsImpl can be evaluated from the screened analytical function
TEUCHOS_UNIT_TEST( HardElasticElectronScatteringDistribution, 
                   sampleAndRecordTrialsImpl_analytical )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 9.9991E-01;
  fake_stream[1] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.1e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine;
  unsigned trials = 10;

  // sampleAndRecordTrialsImpl from analytical function
  ace_basic_elastic_distribution->sampleAndRecordTrialsImpl( 
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );;

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999500000, 1e-12 );
  TEST_EQUALITY_CONST( trials, 11 );

}

//---------------------------------------------------------------------------//
// Check sample can be evaluated from the distribution
TEUCHOS_UNIT_TEST( HardElasticElectronScatteringDistribution, 
                   sample_distribution )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 9.9990E-01; // sample angle from distribution
  fake_stream[1] = 0.5; // sample mu = 0.9874366113907

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine, outgoing_energy;

  // sampleAndRecordTrialsImpl from distribution
  ace_basic_elastic_distribution->sample( electron.getEnergy(),
                                          outgoing_energy,
                                          scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.874339332031E-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
}
//---------------------------------------------------------------------------//
// Check that sample can be evaluated from the screened analytical function
TEUCHOS_UNIT_TEST( HardElasticElectronScatteringDistribution, 
                   sample_analytical )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 9.9991E-01;
  fake_stream[1] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.1e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine, outgoing_energy;

  // sampleAndRecordTrialsImpl from analytical function
  ace_basic_elastic_distribution->sample( electron.getEnergy(),
                                          outgoing_energy,
                                          scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999500000, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.1e-3, 1e-12 );

}
//---------------------------------------------------------------------------//
// Check sampleAndRecordTrials can be evaluated from the distribution
TEUCHOS_UNIT_TEST( HardElasticElectronScatteringDistribution, 
                   sampleAndRecordTrials_distribution )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 9.9990E-01; // sample angle from distribution
  fake_stream[1] = 0.5; // sample mu = 0.9874366113907

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine, outgoing_energy;
  unsigned trials = 10;

  // sampleAndRecordTrialsImpl from distribution
  ace_basic_elastic_distribution->sampleAndRecordTrials( 
                                          electron.getEnergy(),
                                          outgoing_energy,
                                          scattering_angle_cosine,
                                          trials );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.874339332031E-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
}
//---------------------------------------------------------------------------//
// Check that sampleAndRecordTrials can be evaluated from the screened analytical function
TEUCHOS_UNIT_TEST( HardElasticElectronScatteringDistribution, 
                   sampleAndRecordTrials_analytical )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 9.9991E-01;
  fake_stream[1] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.1e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine, outgoing_energy;
  unsigned trials = 10;

  // sampleAndRecordTrialsImpl from analytical function
  ace_basic_elastic_distribution->sampleAndRecordTrials( 
                                          electron.getEnergy(),
                                          outgoing_energy,
                                          scattering_angle_cosine,
                                          trials );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.999999500000, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.1e-3, 1e-12 );

}
//---------------------------------------------------------------------------//
// Check that the angle can be evaluated from the distribution
TEUCHOS_UNIT_TEST( HardElasticElectronScatteringDistribution, 
                   ScatterElectron_distribution )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 9.9990E-01; // sample angle from distribution
  fake_stream[1] = 0.5; // sample mu = 0.9874366113907

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  MonteCarlo::SubshellType shell_of_interaction;
  
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter electron
  ace_basic_elastic_distribution->scatterElectron( electron, 
                                                   bank, 
                                                   shell_of_interaction );

  // Test
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 9.874339332031E-01, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getEnergy(), 1.0e-3, 1e-12 );

}
//---------------------------------------------------------------------------//
// Check that the angle can be evaluated from the screened analytical function
TEUCHOS_UNIT_TEST( HardElasticElectronScatteringDistribution, 
                   ScatterElectron_analytical )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 9.9991E-01;
  fake_stream[1] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  MonteCarlo::SubshellType shell_of_interaction;
  
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.1e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter electron
  ace_basic_elastic_distribution->scatterElectron( electron, 
                                                   bank, 
                                                   shell_of_interaction );

  // Test
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 0.999999500000, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getEnergy(), 1.1e-3, 1e-12 );

}
//---------------------------------------------------------------------------//
// Check that the angle can be evaluated from the distribution
TEUCHOS_UNIT_TEST( HardElasticElectronScatteringDistribution, 
                   ScatterAdjointElectron_distribution )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 9.9990E-01; // sample angle from distribution
  fake_stream[1] = 0.5; // sample mu = 0.9874366113907

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  MonteCarlo::SubshellType shell_of_interaction;
  
  MonteCarlo::AdjointElectronState adjoint_electron( 0 );
  adjoint_electron.setEnergy( 1.0e-3 );
  adjoint_electron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter electron
  ace_basic_elastic_distribution->scatterAdjointElectron( 
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
// Check that the angle can be evaluated from the screened analytical function
TEUCHOS_UNIT_TEST( HardElasticElectronScatteringDistribution, 
                   ScatterAdjointElectron_analytical )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 9.9991E-01;
  fake_stream[1] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  MonteCarlo::SubshellType shell_of_interaction;
  
  MonteCarlo::AdjointElectronState adjoint_electron( 0 );
  adjoint_electron.setEnergy( 1.1e-3 );
  adjoint_electron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter adjoint electron
  ace_basic_elastic_distribution->scatterAdjointElectron( 
                                                   adjoint_electron, 
                                                   bank, 
                                                   shell_of_interaction );

  // Test
  TEST_FLOATING_EQUALITY( adjoint_electron.getZDirection(), 
                          0.999999500000, 
                          1e-12 );
  TEST_FLOATING_EQUALITY( adjoint_electron.getEnergy(), 1.1e-3, 1e-12 );

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
		 elas_block( offset[n] + 1 + table_length[n], table_length[n] ) ) );
*/
  }  

  // Get the atomic number 
  const int atomic_number = xss_data_extractor->extractAtomicNumber();

  // Create the distributions
  ace_basic_elastic_distribution.reset(
		new MonteCarlo::HardElasticElectronScatteringDistribution(
						    atomic_number,
						    elastic_scattering_distribution ) );

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
// end tstHardElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
