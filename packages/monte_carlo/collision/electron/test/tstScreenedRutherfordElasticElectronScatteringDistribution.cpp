//---------------------------------------------------------------------------//
//!
//! \file   tstScreenedRutherfordElasticElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  ScreenedRutherford elastic electron scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_ScreenedRutherfordElasticElectronScatteringDistribution.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestScreenedRutherfordElasticElectronScatteringDistribution : public MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution
{
public:
  TestScreenedRutherfordElasticElectronScatteringDistribution(
        const int atomic_number )
    : MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution(
        atomic_number )
  { /* ... */ }

  ~TestScreenedRutherfordElasticElectronScatteringDistribution()
  { /* ... */ }

  // Allow public access to the screened Rutherford scattering distribution protected member functions
  using MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution::sampleAndRecordTrialsImpl;
};

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution>
  native_pb_elastic_distribution, native_al_elastic_distribution;

std::shared_ptr<TestScreenedRutherfordElasticElectronScatteringDistribution>
  test_native_pb_elastic_distribution, test_native_al_elastic_distribution;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( ScreenedRutherfordElasticElectronScatteringDistribution,
                   evaluate )
{
  // Set energy in MeV
  double energy = 1.0e+5;
  double scattering_angle_cosine = 0.999999;

  // Evaluate the pdf
  double pdf_value =
    native_pb_elastic_distribution->evaluate( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 9.999999999424890E-01, 1e-12 );

  scattering_angle_cosine = 9.999995E-01; // delta_mu = 5e-7;
  pdf_value =
    native_pb_elastic_distribution->evaluate( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 3.999999668748010, 1e-12 );

  scattering_angle_cosine = 1.0;
  pdf_value =
    native_pb_elastic_distribution->evaluate( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 5.809502154347930E+14, 1e-12 );

  // Test with a different energy
  energy = 1.00E-04;

  scattering_angle_cosine = 0.999999;
  pdf_value =
    native_pb_elastic_distribution->evaluate( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 1.0, 1e-12 );

  scattering_angle_cosine = 9.999995E-01; // delta_mu = 5e-7;
  pdf_value =
    native_pb_elastic_distribution->evaluate( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 1.000000012384330E+00, 1e-12 );

  scattering_angle_cosine = 1.0; // delta_mu = 0.0;
  pdf_value =
    native_pb_elastic_distribution->evaluate( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 1.000000024768670E+00, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the pdf can be evaluated
FRENSIE_UNIT_TEST( ScreenedRutherfordElasticElectronScatteringDistribution,
                   evaluatePDF )
{
  // Set energy in MeV
  double energy = 1.0e+5;
  double scattering_angle_cosine = 0.999999;

  // Evaluate the pdf
  double pdf_value =
    native_pb_elastic_distribution->evaluatePDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 9.999999999424890E-01, 1e-12 );

  scattering_angle_cosine = 9.999995E-01; // delta_mu = 5e-7;
  pdf_value =
    native_pb_elastic_distribution->evaluatePDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 3.999999668748010, 1e-12 );

  scattering_angle_cosine = 1.0;
  pdf_value =
    native_pb_elastic_distribution->evaluatePDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 5.809502154347930E+14, 1e-12 );

  // Test with a different energy
  energy = 1.00E-04;

  scattering_angle_cosine = 0.999999;
  pdf_value =
    native_pb_elastic_distribution->evaluatePDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 1.0, 1e-12 );

  scattering_angle_cosine = 9.999995E-01; // delta_mu = 5e-7;
  pdf_value =
    native_pb_elastic_distribution->evaluatePDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 1.000000012384330E+00, 1e-12 );

  scattering_angle_cosine = 1.0; // delta_mu = 0.0;
  pdf_value =
    native_pb_elastic_distribution->evaluatePDF( energy, scattering_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 1.000000024768670E+00, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the cdf can be evaluated
FRENSIE_UNIT_TEST( ScreenedRutherfordElasticElectronScatteringDistribution,
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
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 1.0, 1e-12 );

  scattering_angle_cosine = 9.999995000000E-01;
  cdf_value =
    native_pb_elastic_distribution->evaluateCDF( energy,
                                           scattering_angle_cosine );
  // Test 2 energy 1
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 9.99999958511234000E-01, 1e-12 );

  scattering_angle_cosine = 1.0;
  cdf_value =
    native_pb_elastic_distribution->evaluateCDF( energy,
                                           scattering_angle_cosine );
  // Test 3 energy 1
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 0.0, 1e-12 );


  // Test with a different energy
  energy = 1.00E-04;

  scattering_angle_cosine = 0.999999;
  cdf_value =
    native_pb_elastic_distribution->evaluateCDF( energy,
                                           scattering_angle_cosine );
  // Test 1  energy 2
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 1.00000000002876E+00, 1e-12 );

  scattering_angle_cosine = 9.999995000000E-01;
  cdf_value =
    native_pb_elastic_distribution->evaluateCDF( energy,
                                           scattering_angle_cosine );
  // Test 2 energy 2
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 5.00000003054950E-01, 1e-12 );

  scattering_angle_cosine = 1.0;
  cdf_value =
    native_pb_elastic_distribution->evaluateCDF( energy,
                                           scattering_angle_cosine );
  // Test 3  energy 2
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that sampleAndRecordTrialsImpl can be evaluated
FRENSIE_UNIT_TEST( ScreenedRutherfordElasticElectronScatteringDistribution,
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
  MonteCarlo::ElectronScatteringDistribution::Counter trials = 10;

  // sampleAndRecordTrialsImpl from distribution
  test_native_pb_elastic_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.99999500000093E-01, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 11 );
}

//---------------------------------------------------------------------------//
// Check sample can be evaluated
FRENSIE_UNIT_TEST( ScreenedRutherfordElasticElectronScatteringDistribution,
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
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.99999500000093E-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check sampleAndRecordTrials can be evaluated
FRENSIE_UNIT_TEST( ScreenedRutherfordElasticElectronScatteringDistribution,
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
  MonteCarlo::ElectronScatteringDistribution::Counter trials = 10;

  // sampleAndRecordTrialsImpl from distribution
  native_pb_elastic_distribution->sampleAndRecordTrials(
                                          electron.getEnergy(),
                                          outgoing_energy,
                                          scattering_angle_cosine,
                                          trials );

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.99999500000093E-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
FRENSIE_UNIT_TEST( ScreenedRutherfordElasticElectronScatteringDistribution,
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
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getZDirection(), 9.99999500000093E-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getEnergy(), 1.0e-3, 1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
FRENSIE_UNIT_TEST( ScreenedRutherfordElasticElectronScatteringDistribution,
                   ScatterPositron )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 9.99999500000093E-01,

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::PositronState positron( 0 );
  positron.setEnergy( 1.0e-3 );
  positron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter positron
  native_pb_elastic_distribution->scatterPositron( positron,
                                                   bank,
                                                   shell_of_interaction );

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getZDirection(), 9.99999500000093E-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getEnergy(), 1.0e-3, 1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
FRENSIE_UNIT_TEST( ScreenedRutherfordElasticElectronScatteringDistribution,
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
  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_electron.getZDirection(),
                          9.99999500000093E-01,
                          1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_electron.getEnergy(), 1.0e-3, 1e-12 );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_native_pb_file_name, test_native_al_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_native_pb_file",
                                        test_native_pb_file_name, "",
                                        "Test Native Pb file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_native_al_file",
                                        test_native_al_file_name, "",
                                        "Test NATIVE Al file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // create Native Pb distributions
  {
  // Get native data container
  Data::ElectronPhotonRelaxationDataContainer data_container =
    Data::ElectronPhotonRelaxationDataContainer( test_native_pb_file_name );

  native_pb_elastic_distribution.reset(
        new TestScreenedRutherfordElasticElectronScatteringDistribution(
                data_container.getAtomicNumber() ) );

  test_native_pb_elastic_distribution.reset(
        new TestScreenedRutherfordElasticElectronScatteringDistribution(
                data_container.getAtomicNumber() ) );
  }

  // create NATIVE Al distributions
  {
  // Get native data container
  Data::ElectronPhotonRelaxationDataContainer data_container =
    Data::ElectronPhotonRelaxationDataContainer( test_native_al_file_name );

  native_al_elastic_distribution.reset(
        new MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution(
                data_container.getAtomicNumber() ) );

  test_native_al_elastic_distribution.reset(
        new TestScreenedRutherfordElasticElectronScatteringDistribution(
                data_container.getAtomicNumber() ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstScreenedRutherfordElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
