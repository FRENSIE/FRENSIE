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

  ~TestScreenedRutherfordElasticElectronScatteringDistribution()
  { /* ... */ }

  // Allow public access to the screened Rutherford scattering distribution protected member functions
  using MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution::sampleAndRecordTrialsImpl;
  using MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution::evaluateMoliereScreeningConstant;
};

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution>
  native_pb_elastic_distribution, native_al_elastic_distribution;

std::shared_ptr<TestScreenedRutherfordElasticElectronScatteringDistribution>
  test_native_pb_elastic_distribution, test_native_al_elastic_distribution;

double mu_cutoff = 1.0;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( ScreenedRutherfordElasticElectronScatteringDistribution,
                   evaluate )
{
  // Set energy in MeV
  double energy = 1.0e+5;
  double scattering_angle_cosine = 0.999999;

  // Evaluate the distribution
  double value =
    native_pb_elastic_distribution->evaluate( energy,
                                        scattering_angle_cosine );
  // Test 1 energy 1
  TEST_FLOATING_EQUALITY( value, 9.86373999943272E+05, 1e-12 );


  scattering_angle_cosine = 9.999995000000E-01; // delta_mu = 5e-7;
  value =
    native_pb_elastic_distribution->evaluate( energy,
                                        scattering_angle_cosine );
  // Test 2 energy 1
  TEST_FLOATING_EQUALITY( value, 3.94549567326165E+06, 1e-12 );


  scattering_angle_cosine = 1.0;
  value =
    native_pb_elastic_distribution->evaluate( energy,
                                        scattering_angle_cosine );
  // Test 3 energy 1
  TEST_FLOATING_EQUALITY( value, 5.73034187799278E+20, 1e-12 );



  // Test with a different energy
  energy = 1.00E-04;

  scattering_angle_cosine = 0.999999;
  value =
    native_pb_elastic_distribution->evaluate( energy,
                                        scattering_angle_cosine );
  // Test 1  energy 2
  TEST_FLOATING_EQUALITY( value, 8.70767272727273E+00, 1e-12 );


  scattering_angle_cosine = 9.999995000000E-01; // delta_mu = 5e-7;
  value =
    native_pb_elastic_distribution->evaluate( energy,
                                        scattering_angle_cosine );
  // Test 2 energy 2
  TEST_FLOATING_EQUALITY( value, 8.70767283511146E+00, 1e-12 );


  scattering_angle_cosine = 1.0; // delta_mu = 0.0;
  value =
    native_pb_elastic_distribution->evaluate( energy,
                                        scattering_angle_cosine );
  // Test 3  energy 2
  TEST_FLOATING_EQUALITY( value, 8.70767294295018E+00, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the pdf can be evaluated
TEUCHOS_UNIT_TEST( ScreenedRutherfordElasticElectronScatteringDistribution,
                   evaluatePDF )
{
  // Set energy in MeV
  double energy = 1.0e+5;
  double scattering_angle_cosine = 0.999999;
  double norm_const = 9.99999722847540E-01;

  // Evaluate the pdf
  double pdf_value =
    native_pb_elastic_distribution->evaluatePDF( energy,
                                        scattering_angle_cosine );
  // Test 1 energy 1
  TEST_FLOATING_EQUALITY( pdf_value, 9.86373999943272E+05/norm_const, 1e-12 );

  scattering_angle_cosine = 9.999995000000E-01; // delta_mu = 5e-7;
  pdf_value =
    native_pb_elastic_distribution->evaluatePDF( energy,
                                        scattering_angle_cosine );
  // Test 2 energy 1
  TEST_FLOATING_EQUALITY( pdf_value, 3.94549567326165E+06/norm_const, 1e-12 );

  scattering_angle_cosine = 1.0;
  pdf_value =
    native_pb_elastic_distribution->evaluatePDF( energy,
                                        scattering_angle_cosine );
  // Test 3 energy 1
  TEST_FLOATING_EQUALITY( pdf_value, 5.73034187799278E+20/norm_const, 1e-12 );

  // Test with a different energy
  energy = 1.00E-04;
  norm_const = 9.99999837900441E-01;

  scattering_angle_cosine = 0.999999;
  pdf_value =
    native_pb_elastic_distribution->evaluatePDF( energy,
                                        scattering_angle_cosine );
  // Test 1  energy 2
  TEST_FLOATING_EQUALITY( pdf_value, 8.70767272727273E+00/norm_const, 1e-12 );

  scattering_angle_cosine = 9.999995000000E-01; // delta_mu = 5e-7;
  pdf_value =
    native_pb_elastic_distribution->evaluatePDF( energy,
                                        scattering_angle_cosine );
  // Test 2 energy 2
  TEST_FLOATING_EQUALITY( pdf_value, 8.70767283511146E+00/norm_const, 1e-12 );

  scattering_angle_cosine = 1.0; // delta_mu = 0.0;
  pdf_value =
    native_pb_elastic_distribution->evaluatePDF( energy,
                                        scattering_angle_cosine );
  // Test 3  energy 2
  TEST_FLOATING_EQUALITY( pdf_value, 8.70767294295018E+00/norm_const, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the integrated pdf can be evaluated
TEUCHOS_UNIT_TEST( ScreenedRutherfordElasticElectronScatteringDistribution,
                   evaluateIntegratedPDF )
{
  double tol = 1.0e-13;
  // Set energy in MeV
  double energy = 1.0e+5;

  // Calculate the pdf
  double pdf_value = native_pb_elastic_distribution->evaluateIntegratedPDF( energy );

  // Test energy 1
  TEST_FLOATING_EQUALITY( pdf_value, 2.37744892114220E+07, tol );

  // Test with a different energy
  energy = 1.00E-03;

  pdf_value = native_pb_elastic_distribution->evaluateIntegratedPDF( energy );

  // Test energy 2
  TEST_FLOATING_EQUALITY( pdf_value, 9.07844468744049E-05, tol );

  // Test with a different energy
  energy = 1.00E-04;

  pdf_value = native_pb_elastic_distribution->evaluateIntegratedPDF( energy );

  // Test energy 3
  TEST_FLOATING_EQUALITY( pdf_value, 8.70767424662160E-06, tol );

  // Test with a different energy
  energy = 1.00E-05;

  pdf_value = native_pb_elastic_distribution->evaluateIntegratedPDF( energy );

  // Test energy 4
  TEST_FLOATING_EQUALITY( pdf_value, 5.00000250199076E-07, tol );
}

//---------------------------------------------------------------------------//
// Check that the cdf can be evaluated
TEUCHOS_UNIT_TEST( ScreenedRutherfordElasticElectronScatteringDistribution,
                   evaluateCDF )
{
  // Set energy in MeV
  double energy = 1.0e+5;
  double scattering_angle_cosine = 0.999999;

  // Calculate the cdf
  double cdf_value =
    native_pb_elastic_distribution->evaluateCDF( energy,
                                           scattering_angle_cosine );
  // Test 1 energy 1
  TEST_FLOATING_EQUALITY( cdf_value, 1.0, 1e-12 );

  scattering_angle_cosine = 9.999995000000E-01;
  cdf_value =
    native_pb_elastic_distribution->evaluateCDF( energy,
                                           scattering_angle_cosine );
  // Test 2 energy 1
  TEST_FLOATING_EQUALITY( cdf_value, 9.99999958511234000E-01, 1e-12 );

  scattering_angle_cosine = 1.0;
  cdf_value =
    native_pb_elastic_distribution->evaluateCDF( energy,
                                           scattering_angle_cosine );
  // Test 3 energy 1
  TEST_FLOATING_EQUALITY( cdf_value, 0.0, 1e-12 );


  // Test with a different energy
  energy = 1.00E-04;

  scattering_angle_cosine = 0.999999;
  cdf_value =
    native_pb_elastic_distribution->evaluateCDF( energy,
                                           scattering_angle_cosine );
  // Test 1  energy 2
  TEST_FLOATING_EQUALITY( cdf_value, 1.00000000002876E+00, 1e-12 );

  scattering_angle_cosine = 9.999995000000E-01;
  cdf_value =
    native_pb_elastic_distribution->evaluateCDF( energy,
                                           scattering_angle_cosine );
  // Test 2 energy 2
  TEST_FLOATING_EQUALITY( cdf_value, 5.00000003054950E-01, 1e-12 );

  scattering_angle_cosine = 1.0; 
  cdf_value =
    native_pb_elastic_distribution->evaluateCDF( energy,
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
  test_native_pb_elastic_distribution->sampleAndRecordTrialsImpl(
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
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-5 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double screening_constant;

 // Test 1
  screening_constant =
    test_native_pb_elastic_distribution->evaluateMoliereScreeningConstant(
                                                electron.getEnergy() );
  TEST_FLOATING_EQUALITY( screening_constant, 2.5131795894201700E+03, 1e-12 );

 // Test 2
  electron.setEnergy( 1.0e-3 );
  screening_constant =
    test_native_pb_elastic_distribution->evaluateMoliereScreeningConstant(
                                                electron.getEnergy() );
  TEST_FLOATING_EQUALITY( screening_constant, 2.6821367199800900, 1e-12 );

 // Test 3
  electron.setEnergy( 1.0e+5 );
  screening_constant =
    test_native_pb_elastic_distribution->evaluateMoliereScreeningConstant(
                                                electron.getEnergy() );
  TEST_FLOATING_EQUALITY( screening_constant, 4.1488769980623900E-14, 1e-12 );


 // Al Test 1
  electron.setEnergy( 1.0e-5 );
  screening_constant =
    test_native_al_elastic_distribution->evaluateMoliereScreeningConstant(
                                                electron.getEnergy() );
  TEST_FLOATING_EQUALITY( screening_constant, 2.3792675295299300E+01, 1e-12 );

 // Al Test 2
  electron.setEnergy( 1.0e-3 );
  screening_constant =
    test_native_al_elastic_distribution->evaluateMoliereScreeningConstant(
                                                electron.getEnergy() );
  TEST_FLOATING_EQUALITY( screening_constant, 7.2595008773036300E-02, 1e-12 );

 // Al Test 3
  electron.setEnergy( 6.625e+1 );
  screening_constant =
    test_native_al_elastic_distribution->evaluateMoliereScreeningConstant(
                                                electron.getEnergy() );
  TEST_FLOATING_EQUALITY( screening_constant, 1.2814675966081900E-08, 1e-12 );

 // Al Test 4
  electron.setEnergy( 1.0e+5 );
  screening_constant =
    test_native_al_elastic_distribution->evaluateMoliereScreeningConstant(
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
  native_pb_elastic_distribution->sample( electron.getEnergy(),
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
  native_pb_elastic_distribution->sampleAndRecordTrials(
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
  native_pb_elastic_distribution->scatterElectron( electron,
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
  native_pb_elastic_distribution->scatterAdjointElectron(
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
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_native_pb_file_name, test_native_al_file_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_native_pb_file",
                   &test_native_pb_file_name,
                   "Test Native Pb file name" );
  clp().setOption( "test_native_al_file",
                   &test_native_al_file_name,
                   "Test NATIVE Al file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // create Native Pb distributions
  {
  // Get native data container
  Data::ElectronPhotonRelaxationDataContainer data_container =
    Data::ElectronPhotonRelaxationDataContainer( test_native_pb_file_name );

  // Get the energy grid
  std::vector<double> angular_energy_grid =
    data_container.getElasticAngularEnergyGrid();

  // Get size of paramters
  int size = angular_energy_grid.size();

  // Create the scattering function
  Utility::FullyTabularTwoDDistribution::DistributionType function_data( size );

  for( unsigned n = 0; n < angular_energy_grid.size(); ++n )
  {
    function_data[n].first = angular_energy_grid[n];

    // Get the cutoff elastic scattering angles at the energy
    Teuchos::Array<double> angles(
        data_container.getCutoffElasticAngles( angular_energy_grid[n] ) );

    // Get the cutoff elastic scatering pdf at the energy
    Teuchos::Array<double> pdf(
        data_container.getCutoffElasticPDF( angular_energy_grid[n] ) );

    function_data[n].second.reset(
      new const Utility::TabularDistribution<Utility::LinLin>( angles, pdf ) );
  }

  // Create the scattering function
  std::shared_ptr<Utility::FullyTabularTwoDDistribution> scattering_function(
    new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LinLinLin>(
            function_data ) );

  // Create cutoff distributions
  bool correlated_sampling_mode_on = true;
  std::shared_ptr<const MonteCarlo::CutoffElasticElectronScatteringDistribution>
    cutoff_elastic_distribution(
        new MonteCarlo::CutoffElasticElectronScatteringDistribution(
                scattering_function,
                mu_cutoff,
                correlated_sampling_mode_on ) );

  double atomic_number = data_container.getAtomicNumber();

  native_pb_elastic_distribution.reset(
        new TestScreenedRutherfordElasticElectronScatteringDistribution(
                cutoff_elastic_distribution,
                atomic_number ) );

  test_native_pb_elastic_distribution.reset(
        new TestScreenedRutherfordElasticElectronScatteringDistribution(
                cutoff_elastic_distribution,
                atomic_number ) );
  }

  // create NATIVE Al distributions
  {
  // Get native data container
  Data::ElectronPhotonRelaxationDataContainer data_container =
    Data::ElectronPhotonRelaxationDataContainer( test_native_al_file_name );

  // Get the energy grid
  std::vector<double> angular_energy_grid =
    data_container.getElasticAngularEnergyGrid();

  // Get size of paramters
  int size = angular_energy_grid.size();

  // Create the scattering function
  Utility::FullyTabularTwoDDistribution::DistributionType function_data( size );

  for( unsigned n = 0; n < angular_energy_grid.size(); ++n )
  {
    function_data[n].first = angular_energy_grid[n];

    // Get the cutoff elastic scattering angles at the energy
    Teuchos::Array<double> angles(
        data_container.getCutoffElasticAngles( angular_energy_grid[n] ) );

    // Get the cutoff elastic scatering pdf at the energy
    Teuchos::Array<double> pdf(
        data_container.getCutoffElasticPDF( angular_energy_grid[n] ) );

    function_data[n].second.reset(
      new const Utility::TabularDistribution<Utility::LinLin>( angles, pdf ) );
  }

  // Create the scattering function
  std::shared_ptr<Utility::FullyTabularTwoDDistribution> scattering_function(
    new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LinLinLin>(
            function_data ) );

  bool correlated_sampling_mode_on = true;
  std::shared_ptr<const MonteCarlo::CutoffElasticElectronScatteringDistribution>
    cutoff_elastic_distribution(
        new MonteCarlo::CutoffElasticElectronScatteringDistribution(
                scattering_function,
                mu_cutoff,
                correlated_sampling_mode_on ) );

  double atomic_number = data_container.getAtomicNumber();

  native_al_elastic_distribution.reset(
        new MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution(
                cutoff_elastic_distribution,
                atomic_number ) );

  test_native_al_elastic_distribution.reset(
        new TestScreenedRutherfordElasticElectronScatteringDistribution(
                cutoff_elastic_distribution,
                atomic_number ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstScreenedRutherfordElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
