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
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestScreenedRutherfordElasticElectronScatteringDistribution : public MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution
{
public:
  TestScreenedRutherfordElasticElectronScatteringDistribution( 
        const ElasticDistribution& elastic_cutoff_distribution,
        const int atomic_number )
    : MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution( 
        elastic_cutoff_distribution,
        atomic_number )
  { /* ... */ }

  TestScreenedRutherfordElasticElectronScatteringDistribution( 
        const ParameterArray& screened_rutherford_parameters )
    : MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution( 
        screened_rutherford_parameters )
  { /* ... */ }

  ~TestScreenedRutherfordElasticElectronScatteringDistribution()
  { /* ... */ }

  // Allow public access to the CutoffElasticElectronScatteringDistribution protected member functions
  using MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution::sampleAndRecordTrialsImpl;
  using MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution::evaluateMoliereScreeningConstant;
};

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution> 
  ace_elastic_distribution, native_elastic_distribution;

Teuchos::RCP<TestScreenedRutherfordElasticElectronScatteringDistribution> 
  test_ace_elastic_distribution, test_native_elastic_distribution;

Teuchos::RCP<const Utility::TabularDistribution<Utility::LinLin> >
  elastic_cutoff_pdf;

double delta_mu_cutoff = 1.0e-6;
double mu_cutoff = 0.999999;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//

// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( ScreenedRutherfordElasticElectronScatteringDistribution, 
                   evaluate )
{
  // Set energy in MeV
  double energy = 1.0e+5;
  double scattering_angle_cosine = mu_cutoff; // delta_mu = delta_mu_cutoff;

  // Evaluate the distribution
  double value = 
    ace_elastic_distribution->evaluate( energy, 
                                        scattering_angle_cosine );
  // Test 1 energy 1
  TEST_FLOATING_EQUALITY( value, 4.487867817660950E+05, 1e-10 );


  scattering_angle_cosine = 9.999995000000E-01; // delta_mu = 5e-7;
  value = 
    ace_elastic_distribution->evaluate( energy, 
                                        scattering_angle_cosine );
  // Test 2 energy 1
  TEST_FLOATING_EQUALITY( value, 1.795146978107500E+06, 1e-9 );


  scattering_angle_cosine = 1.0; // delta_mu = 0.0;
  value = 
    ace_elastic_distribution->evaluate( energy, 
                                        scattering_angle_cosine );
  // Test 3 energy 1
  TEST_FLOATING_EQUALITY( value, 2.607227775513000E+20, 1e-10 );



  // Test with a different energy
  energy = 1.00E-04;

  scattering_angle_cosine = mu_cutoff; // delta_mu = delta_mu_cutoff;
  value = 
    ace_elastic_distribution->evaluate( energy, 
                                        scattering_angle_cosine );
  // Test 1  energy 2
  TEST_FLOATING_EQUALITY( value, 8.706924726988590E+00, 1e-15 );


  scattering_angle_cosine = 9.999995000000E-01; // delta_mu = 5e-7;
  value = 
    ace_elastic_distribution->evaluate( energy, 
                                        scattering_angle_cosine );
  // Test 2 energy 2
  TEST_FLOATING_EQUALITY( value, 8.706924834818060E+00, 1e-12 );


  scattering_angle_cosine = 1.0; // delta_mu = 0.0;
  value = 
    ace_elastic_distribution->evaluate( energy, 
                                        scattering_angle_cosine );
  // Test 3  energy 2
  TEST_FLOATING_EQUALITY( value, 8.706924942647520E+00, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the pdf can be evaluated
TEUCHOS_UNIT_TEST( ScreenedRutherfordElasticElectronScatteringDistribution, 
                   evaluatePDF )
{
  // Set energy in MeV
  double energy = 1.0e+5;
  double scattering_angle_cosine = mu_cutoff; // delta_mu = delta_mu_cutoff;

  // Calculate the pdf
  double pdf_value = 
    ace_elastic_distribution->evaluatePDF( energy, 
                                           scattering_angle_cosine );
  // Test 1 energy 1
  TEST_FLOATING_EQUALITY( pdf_value, 4.487867817660950E+05, 1e-10 );


  scattering_angle_cosine = 9.999995000000E-01; // delta_mu = 5e-7;
  pdf_value = 
    ace_elastic_distribution->evaluatePDF( energy, 
                                           scattering_angle_cosine );
  // Test 2 energy 1
  TEST_FLOATING_EQUALITY( pdf_value, 1.795146978107500E+06, 1e-9 );


  scattering_angle_cosine = 1.0; // delta_mu = 0.0;
  pdf_value = 
    ace_elastic_distribution->evaluatePDF( energy, 
                                           scattering_angle_cosine );
  // Test 3 energy 1
  TEST_FLOATING_EQUALITY( pdf_value, 2.607227775513000E+20, 1e-12 );


  // Test with a different energy
  energy = 1.00E-04;

  scattering_angle_cosine = mu_cutoff; // delta_mu = delta_mu_cutoff;
  pdf_value = 
    ace_elastic_distribution->evaluatePDF( energy, 
                                           scattering_angle_cosine );
  // Test 1  energy 2
  TEST_FLOATING_EQUALITY( pdf_value, 8.706924726988590E+00, 1e-15 );


  scattering_angle_cosine = 9.999995000000E-01; // delta_mu = 5e-7;
  pdf_value = 
    ace_elastic_distribution->evaluatePDF( energy, 
                                           scattering_angle_cosine );
  // Test 2 energy 2
  TEST_FLOATING_EQUALITY( pdf_value, 8.706924834818060E+00, 1e-12 );


  scattering_angle_cosine = 1.0; // delta_mu = 0.0;
  pdf_value = 
    ace_elastic_distribution->evaluatePDF( energy, 
                                           scattering_angle_cosine );
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
  double scattering_angle_cosine = mu_cutoff; // delta_mu = delta_mu_cutoff;

  // Calculate the cdf
  double cdf_value = 
    ace_elastic_distribution->evaluateCDF( energy, 
                                           scattering_angle_cosine );
  // Test 1 energy 1
  TEST_FLOATING_EQUALITY( cdf_value, 1.0, 1e-12 );


  scattering_angle_cosine = 9.999995000000E-01; // delta_mu = 5e-7;
  cdf_value = 
    ace_elastic_distribution->evaluateCDF( energy, 
                                           scattering_angle_cosine );
  // Test 2 energy 1
  TEST_FLOATING_EQUALITY( cdf_value, 9.99999958511234000E-01, 1e-12 );


  scattering_angle_cosine = 1.0; // delta_mu = 0.0;
  cdf_value = 
    ace_elastic_distribution->evaluateCDF( energy, 
                                           scattering_angle_cosine );
  // Test 3 energy 1
  TEST_FLOATING_EQUALITY( cdf_value, 0.0, 1e-12 );



  // Test with a different energy
  energy = 1.00E-04;

  scattering_angle_cosine = mu_cutoff; // delta_mu = delta_mu_cutoff;
  cdf_value = 
    ace_elastic_distribution->evaluateCDF( energy, 
                                           scattering_angle_cosine );
  // Test 1  energy 2
  TEST_FLOATING_EQUALITY( cdf_value, 1.0, 1e-10 );


  scattering_angle_cosine = 9.999995000000E-01; // delta_mu = 5e-7;
  cdf_value = 
    ace_elastic_distribution->evaluateCDF( energy, 
                                           scattering_angle_cosine );
  // Test 2 energy 2
  TEST_FLOATING_EQUALITY( cdf_value, 5.00000003096084000E-01, 1e-10 );


  scattering_angle_cosine = 1.0; // delta_mu = 0.0;
  cdf_value = 
    ace_elastic_distribution->evaluateCDF( energy, 
                                           scattering_angle_cosine );
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
  test_ace_elastic_distribution->sampleAndRecordTrialsImpl( 
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.99999500000093E-01, 1e-12 );
  TEST_EQUALITY_CONST( trials, 11 );
}

//---------------------------------------------------------------------------//
// Check that sampleAndRecordTrialsImpl can be evaluated
TEUCHOS_UNIT_TEST( ScreenedRutherfordElasticElectronScatteringDistribution, 
                   evaluateMoliereScreeningConstant )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 9.99999500000093E-01,

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-5 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double screening_constant;

  // ACE Test 1
  screening_constant = 
    test_ace_elastic_distribution->evaluateMoliereScreeningConstant( 
                                                electron.getEnergy() );
  TEST_FLOATING_EQUALITY( screening_constant, 2.5131795894201700E+03, 1e-12 );

  // ACE Test 2
  electron.setEnergy( 1.0e-3 );
  screening_constant = 
    test_ace_elastic_distribution->evaluateMoliereScreeningConstant( 
                                                electron.getEnergy() );
  TEST_FLOATING_EQUALITY( screening_constant, 2.6821367199800900, 1e-12 );

  // ACE Test 3
  electron.setEnergy( 1.0e+5 );
  screening_constant = 
    test_ace_elastic_distribution->evaluateMoliereScreeningConstant( 
                                                electron.getEnergy() );
  TEST_FLOATING_EQUALITY( screening_constant, 4.1488769980623900E-14, 1e-12 );


  // NATIVE Test 1
  electron.setEnergy( 1.0e-5 );
  screening_constant = 
    test_native_elastic_distribution->evaluateMoliereScreeningConstant( 
                                                electron.getEnergy() );
  TEST_FLOATING_EQUALITY( screening_constant, 2.3792675295299300E+01, 1e-12 );

  // NATIVE Test 2
  electron.setEnergy( 1.0e-3 );
  screening_constant = 
    test_native_elastic_distribution->evaluateMoliereScreeningConstant( 
                                                electron.getEnergy() );
  TEST_FLOATING_EQUALITY( screening_constant, 7.2595008773036300E-02, 1e-12 );

  // NATIVE Test 3
  electron.setEnergy( 6.625e+1 );
  screening_constant = 
    test_native_elastic_distribution->evaluateMoliereScreeningConstant( 
                                                electron.getEnergy() );
  TEST_FLOATING_EQUALITY( screening_constant, 1.2814675966081900E-08, 1e-12 );

  // NATIVE Test 4
  electron.setEnergy( 1.0e+5 );
  screening_constant = 
    test_native_elastic_distribution->evaluateMoliereScreeningConstant( 
                                                electron.getEnergy() );
  TEST_FLOATING_EQUALITY( screening_constant, 5.7117744434411500E-15, 1e-12 );
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
  Data::SubshellType shell_of_interaction;
  
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
  Data::SubshellType shell_of_interaction;
  
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
  std::string test_native_file_name;
  
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_ace_file",
		 &test_ace_file_name,
		 "Test ACE file name" );
  clp.setOption( "test_ace_table",
		 &test_ace_table_name,
		 "Test ACE table name" );
  clp.setOption( "test_native_file",
		 &test_native_file_name,
		 "Test NATIVE file name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // create ACE distributions
  {
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
/*
    cutoff_pdf[n] = 
        elastic_scattering_distribution[n].second->evaluatePDF( 
            mu_cutoff );  */  
  }  
/*
  elastic_cutoff_pdf.reset(
        new Utility::TabularDistribution<Utility::LinLin>(
                energy_grid,
                cutoff_pdf ) );
*/

  // Get the atomic number 
  const int atomic_number = xss_data_extractor->extractAtomicNumber();
/*! \todo Double check if the entire cutoff distribution is needed or only the cutoff pdf values
  // Create the distributions
  ace_elastic_distribution.reset(
        new MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution(
                elastic_cutoff_pdf,
                atomic_number ) );
*/

 Teuchos::RCP<MonteCarlo::CutoffElasticElectronScatteringDistribution> 
    cutoff_distribution;

  // Create the cutoff distribution
  cutoff_distribution.reset(
        new MonteCarlo::CutoffElasticElectronScatteringDistribution(
                elastic_scattering_distribution,
                0.999999 ) );

  // Create the screened Rutherford distribution
  ace_elastic_distribution.reset(
        new MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution(
                cutoff_distribution,
                atomic_number ) );

  test_ace_elastic_distribution.reset(
        new TestScreenedRutherfordElasticElectronScatteringDistribution(
                cutoff_distribution,
                atomic_number ) );

  // Clear setup data
  ace_file_handler.reset();
  xss_data_extractor.reset();
  }

  // create NATIVE distributions
  {
  // Get native data container 
  Data::ElectronPhotonRelaxationDataContainer data_container =
    Data::ElectronPhotonRelaxationDataContainer( test_native_file_name );

  // Get the energy grid
  std::vector<double> angular_energy_grid = 
    data_container.getElasticAngularEnergyGrid();

  // Get size of paramters
  int size = angular_energy_grid.size();

  // Create the scattering function
  MonteCarlo::CutoffElasticElectronScatteringDistribution::ElasticDistribution
    scattering_function(size);

  for( unsigned n = 0; n < angular_energy_grid.size(); ++n )
  {
    scattering_function[n].first = angular_energy_grid[n];

    // Get the cutoff elastic scattering angles at the energy
    Teuchos::Array<double> angles( 
        data_container.getCutoffElasticAngles( angular_energy_grid[n] ) );

    // Get the cutoff elastic scatering pdf at the energy
    Teuchos::Array<double> pdf( 
        data_container.getCutoffElasticPDF( angular_energy_grid[n] ) );

    scattering_function[n].second.reset( 
	  new const Utility::TabularDistribution<Utility::LinLin>( angles, pdf ) );
  }

  Teuchos::RCP<const MonteCarlo::CutoffElasticElectronScatteringDistribution>
        cutoff_elastic_distribution;

  // Create cutoff distribution
  cutoff_elastic_distribution.reset( 
        new MonteCarlo::CutoffElasticElectronScatteringDistribution( 
                scattering_function,
                0.999999 ) );

  double atomic_number = data_container.getAtomicNumber();

  test_native_elastic_distribution.reset(
        new TestScreenedRutherfordElasticElectronScatteringDistribution(
                cutoff_elastic_distribution,
                atomic_number ) );
  }

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
