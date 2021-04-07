//---------------------------------------------------------------------------//
//!
//! \file   tstCutoffElasticElectronScatteringDistributionNative.cpp
//! \author Luke Kersting
//! \brief  Cutoff elastic electron scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_CutoffElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_ElasticBasicBivariateDistribution.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestCutoffElasticElectronScatteringDistribution : public MonteCarlo::CutoffElasticElectronScatteringDistribution
{
public:
  TestCutoffElasticElectronScatteringDistribution(
        const std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution>&
        full_cutoff_elastic_distribution,
        const std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution>&
        partial_cutoff_elastic_distribution,
        const double cutoff_angle_cosine )
    : MonteCarlo::CutoffElasticElectronScatteringDistribution(
        full_cutoff_elastic_distribution,
        partial_cutoff_elastic_distribution,
        cutoff_angle_cosine )
  { /* ... */ }

  TestCutoffElasticElectronScatteringDistribution(
        const std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution>&
        full_cutoff_elastic_distribution )
    : MonteCarlo::CutoffElasticElectronScatteringDistribution(
        full_cutoff_elastic_distribution )
  { /* ... */ }

  ~TestCutoffElasticElectronScatteringDistribution()
  { /* ... */ }

  // Allow public access to the CutoffElasticElectronScatteringDistribution protected member functions
  using MonteCarlo::CutoffElasticElectronScatteringDistribution::sampleAndRecordTrialsImpl;
};

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::CutoffElasticElectronScatteringDistribution>
  native_elastic_distribution;
std::shared_ptr<TestCutoffElasticElectronScatteringDistribution>
  test_native_elastic_distribution;

std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution>
  native_scattering_distribution, partial_native_scattering_distribution;

double angle_cosine_cutoff = 1.0;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( CutoffElasticElectronScatteringDistribution,
                   evaluate_native )
{
  double pdf_value;

  // Set energy in MeV and angle cosine
  double energy = 1.0e-3;
  double scattering_angle_cosine = 0.0;

  // Calculate the pdf
  pdf_value =
    native_elastic_distribution->evaluate( energy,
                                           scattering_angle_cosine );
  // test 1 energy 1
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.029161, 1e-12 );

  scattering_angle_cosine = 0.9;
  pdf_value =
    native_elastic_distribution->evaluate( energy,
                                           scattering_angle_cosine );
  // test 2
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.72266, 1e-12 );

  scattering_angle_cosine = 0.9001;
  pdf_value =
    native_elastic_distribution->evaluate( energy,
                                           scattering_angle_cosine );
  // test 3
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // test with a different energy
  energy = 1e5;

  scattering_angle_cosine = 0.0;
  pdf_value =
    native_elastic_distribution->evaluate( energy,
                                           scattering_angle_cosine );
  // test 1
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 1.9783647368421053e-06, 1e-15 );

  scattering_angle_cosine = 0.9;
  pdf_value =
    native_elastic_distribution->evaluate( energy,
                                           scattering_angle_cosine );
  // test 2
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 1.2910653846153849e-04, 1e-15 );

  scattering_angle_cosine = 0.90001;
  pdf_value =
    native_elastic_distribution->evaluate( energy, scattering_angle_cosine );
  // test 3
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the pdf can be evaluated
FRENSIE_UNIT_TEST( CutoffElasticElectronScatteringDistribution,
                   evaluatePDF_native )
{
  // Set energy in MeV and angle cosine
  double energy = 1.0e-3;
  double scattering_angle_cosine = 0.0;
  double norm_factor = 9.99999856510462E-01;

  // Calculate the pdf
  double pdf_value =
    native_elastic_distribution->evaluatePDF( energy,
                                        scattering_angle_cosine );
  // test 1 energy 1
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.11951733660954690086/norm_factor, 1e-12 );

  scattering_angle_cosine = 0.9;
  pdf_value =
    native_elastic_distribution->evaluatePDF( energy,
                                        scattering_angle_cosine );
  // test 2
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 2.9618462492457449109/norm_factor, 1e-12 );

  scattering_angle_cosine = 0.9001;
  pdf_value =
    native_elastic_distribution->evaluatePDF( energy,
                                        scattering_angle_cosine );
  // test 3
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-12 );

  // test with a different energy
  energy = 1.00E+05;
  scattering_angle_cosine = 0.0;

  pdf_value =
    native_elastic_distribution->evaluatePDF( energy,
                                              scattering_angle_cosine );
  // test 2
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.1358055919901790809, 1e-15 );

  scattering_angle_cosine = 0.9;
  pdf_value =
    native_elastic_distribution->evaluatePDF( energy,
                                              scattering_angle_cosine );
  // test 2
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 8.8625669266422093528, 1e-15 );

  scattering_angle_cosine = 1.0;
  pdf_value =
    native_elastic_distribution->evaluatePDF( energy,
                                              scattering_angle_cosine );
  // test 3
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the cdf can be evaluated
FRENSIE_UNIT_TEST( CutoffElasticElectronScatteringDistribution,
                   evaluateCDF_native )
{
  // Set energy in MeV and angle cosine
  double energy = 1.0e-3;
  double scattering_angle_cosine = 0.0;

  // Calculate the cdf
  double cdf_value =
    native_elastic_distribution->evaluateCDF( energy,
                                              scattering_angle_cosine );
  // test 1 energy 1
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 0.39610617480640930577, 1e-12 );

  scattering_angle_cosine = 0.9;
  cdf_value =
    native_elastic_distribution->evaluateCDF( energy,
                                              scattering_angle_cosine );
  // test 2
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 1.0, 1e-12 );

  scattering_angle_cosine = 0.9001;
  cdf_value =
    native_elastic_distribution->evaluateCDF( energy,
                                              scattering_angle_cosine );
  // test 2
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 1.0, 1e-12 );

  // test with a different energy
  energy = 1.00E+05;

  scattering_angle_cosine = 0.0;
  cdf_value =
    native_elastic_distribution->evaluateCDF( energy,
                                              scattering_angle_cosine );
  // test 1 energy 2
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 0.049029167418501704012, 1e-15 );

  scattering_angle_cosine = 0.9;
  cdf_value =
    native_elastic_distribution->evaluateCDF( energy,
                                              scattering_angle_cosine );
  // test 2
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 1.0, 1e-15 );

  scattering_angle_cosine = 0.9001;
  cdf_value =
    native_elastic_distribution->evaluateCDF( energy,
                                              scattering_angle_cosine );
  // test 3
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that sampleAndRecordTrialsImpl can be evaluated
FRENSIE_UNIT_TEST( CutoffElasticElectronScatteringDistribution,
                   sampleAndRecordTrialsImpl_native )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 0.9875083879111824503

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine;
  MonteCarlo::CutoffElasticElectronScatteringDistribution::Counter trials = 10;

  // sampleAndRecordTrialsImpl from distribution
  test_native_elastic_distribution->sampleAndRecordTrialsImpl(
                                                electron.getEnergy(),
                                                scattering_angle_cosine,
                                                trials );
  // test
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.27199711405636251005, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 11 );
}

//---------------------------------------------------------------------------//
// Check sample can be evaluated
FRENSIE_UNIT_TEST( CutoffElasticElectronScatteringDistribution,
                   sample_native )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 0.9875083879111824503

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine, outgoing_energy;

  // sampleAndRecordTrialsImpl from distribution
  native_elastic_distribution->sample( electron.getEnergy(),
                                          outgoing_energy,
                                          scattering_angle_cosine );
  // test
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.27199711405636251005, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check sampleAndRecordTrials can be evaluated
FRENSIE_UNIT_TEST( CutoffElasticElectronScatteringDistribution,
                   sampleAndRecordTrials_native )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 0.9875083879111824503

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double scattering_angle_cosine, outgoing_energy;
  MonteCarlo::CutoffElasticElectronScatteringDistribution::Counter trials = 10;

  // sampleAndRecordTrialsImpl from distribution
  native_elastic_distribution->sampleAndRecordTrials(
                                          electron.getEnergy(),
                                          outgoing_energy,
                                          scattering_angle_cosine,
                                          trials );
  // test
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.27199711405636251005, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
FRENSIE_UNIT_TEST( CutoffElasticElectronScatteringDistribution,
                   ScatterElectron_native )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 0.9875083879111824503

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter electron
  native_elastic_distribution->scatterElectron( electron,
                                                bank,
                                                shell_of_interaction );
  // test
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getZDirection(), 0.27199711405636251005, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getEnergy(), 1.0e-3, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the angle can be evaluated
FRENSIE_UNIT_TEST( CutoffElasticElectronScatteringDistribution,
                   ScatterPositron_native )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 0.9875083879111824503

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::PositronState positron( 0 );
  positron.setEnergy( 1.0e-3 );
  positron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter positron
  native_elastic_distribution->scatterPositron( positron,
                                                bank,
                                                shell_of_interaction );
  // test
  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getZDirection(), 0.27199711405636251005, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getEnergy(), 1.0e-3, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the angle cosine can be evaluated
FRENSIE_UNIT_TEST( CutoffElasticElectronScatteringDistribution,
                   ScatterAdjointElectron_native )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 0.9875083879111824503

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::AdjointElectronState adjoint_electron( 0 );
  adjoint_electron.setEnergy( 1.0e-3 );
  adjoint_electron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter electron
  native_elastic_distribution->scatterAdjointElectron( adjoint_electron,
                                                       bank,
                                                       shell_of_interaction );
  // test
  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_electron.getZDirection(),
                          0.27199711405636251005,
                          1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_electron.getEnergy(), 1.0e-3, 1e-12 );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_native_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_native_file",
                                        test_native_file_name, "",
                                        "Test NATIVE file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
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
  std::vector<double> native_primary_grid( size );
  std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
    native_secondary_dists( size );

  std::vector<double> partial_native_primary_grid( size );
  std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
    partial_native_secondary_dists( size );

  for( unsigned n = 0; n < size; ++n )
  {
    native_primary_grid[n] = angular_energy_grid[n];
    partial_native_primary_grid[n] = angular_energy_grid[n];

    // Get the cutoff elastic scattering angles at the energy
    std::vector<double> angles(
        data_container.getCutoffElasticAngles( angular_energy_grid[n] ) );

    // Get the cutoff elastic scattering pdf at the energy
    std::vector<double> pdfs(
        data_container.getCutoffElasticPDF( angular_energy_grid[n] ) );

    native_secondary_dists[n].reset(
      new const Utility::TabularDistribution<Utility::LinLin>( angles, pdfs ) );

    unsigned index = 0;
    for( unsigned i = 0; i < angles.size(); ++i )
    {
      if( angles[i] <= 0.9 )
      {
        index = i;
      }
    }

    std::vector<double> partial_angles(index+1), partial_pdfs(index+1);
    for( unsigned i = 0; i <= index; ++i )
    {
      partial_angles[i] = angles[i];
      partial_pdfs[i] = pdfs[i];
    }

    if( angles[index] != 0.9 )
    {
      partial_angles.push_back(0.9);
      partial_pdfs.push_back(native_secondary_dists[n]->evaluate( 0.9 ) );

    }

    partial_native_secondary_dists[n].reset(
      new const Utility::TabularDistribution<Utility::LinLin>( partial_angles, partial_pdfs ) );
  }

  // Create the scattering distribution
  native_scattering_distribution.reset(
    new MonteCarlo::ElasticBasicBivariateDistribution<Utility::Correlated<Utility::LinLinLin> >(
                                                    native_primary_grid,
                                                    native_secondary_dists ) );

  // Create the scattering distribution
  partial_native_scattering_distribution.reset(
    new MonteCarlo::ElasticBasicBivariateDistribution<Utility::Correlated<Utility::LinLinLin> >(
                                            partial_native_primary_grid,
                                            partial_native_secondary_dists ) );

  // Create cutoff distributions
  native_elastic_distribution.reset(
        new MonteCarlo::CutoffElasticElectronScatteringDistribution(
                native_scattering_distribution,
                partial_native_scattering_distribution,
                0.9 ) );

  test_native_elastic_distribution.reset(
        new TestCutoffElasticElectronScatteringDistribution(
                native_scattering_distribution,
                partial_native_scattering_distribution,
                0.9 ) );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstCutoffElasticElectronScatteringDistributionNative.cpp
//---------------------------------------------------------------------------//
