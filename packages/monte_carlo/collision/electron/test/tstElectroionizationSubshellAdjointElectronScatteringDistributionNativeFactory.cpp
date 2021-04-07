//---------------------------------------------------------------------------//
//!
//! \file   tstElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory.cpp
//! \author Luke Kersting
//! \brief  adjoint electroionization subshell scattering distribution Native factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

typedef MonteCarlo::ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory
    IonizationNativeFactory;

std::unique_ptr<Data::AdjointElectronPhotonRelaxationDataContainer> data_container;

std::shared_ptr<MonteCarlo::ElectroionizationSubshellAdjointElectronScatteringDistribution>
  native_distribution;

double max_energy = 2.00000147100000021e+01;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the subshell binding energy
FRENSIE_UNIT_TEST( ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory,
                   getBindingEnergy )
{

  // Get binding energy
  double binding_energy = native_distribution->getBindingEnergy();

  // Test original electron
  FRENSIE_CHECK_EQUAL( binding_energy, 1.361E-05 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated for a given incoming and knock-on energy
FRENSIE_UNIT_TEST( ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory,
                   evaluate )
{
  double pdf;

  // Check below the first bin
  pdf = native_distribution->evaluate( 9.99e-6, 2.3711E-5 );
  FRENSIE_CHECK_SMALL( pdf, 1e-12 );

  // Check the first bin
  pdf = native_distribution->evaluate( 1e-5, 2.3711E-5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 2.242860168116929742e+02, 1e-12 );

  // Check between two bins
  pdf = native_distribution->evaluate( 1.1e-5, 0.2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.858726173232574108e-01, 1e-12 );

  // Check the last bin
  pdf = native_distribution->evaluate( 20.0, max_energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 9.741633350079954835e+05, 1e-12 );

  // Check above the last bin
  pdf = native_distribution->evaluate( 20.01, 22.1 );
  FRENSIE_CHECK_SMALL( pdf, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated for a given incoming and knock-on energy
FRENSIE_UNIT_TEST( ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory,
                   evaluatePDF )
{
  double pdf;

  // Check below the first bin
  pdf = native_distribution->evaluatePDF( 9.99e-6, 2.3711E-5 );
  FRENSIE_CHECK_SMALL( pdf, 1e-12 );

  // Check the first bin
  pdf = native_distribution->evaluatePDF( 1e-5, 2.3711E-5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 6.894608999906166957e+01, 1e-12 );

  // Check between two bins
  pdf = native_distribution->evaluatePDF( 1.1e-5, 0.2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 5.487425171273361407e-02, 1e-6 );

  // Check the last bin
  pdf = native_distribution->evaluatePDF( 20.0, max_energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 9.741633364475551061e+05, 1e-12 );

  // Check above the last bin
  pdf = native_distribution->evaluatePDF( 20.01, 22.1 );
  FRENSIE_CHECK_SMALL( pdf, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated for a given incoming and knock-on energy
FRENSIE_UNIT_TEST( ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory,
                   evaluateCDF )
{
  double cdf;

  // Check below the first bin
  cdf = native_distribution->evaluateCDF( 9.99e-6, 1.361e-5 );
  FRENSIE_CHECK_SMALL( cdf, 1e-12 );

  // Check the first bin
  cdf = native_distribution->evaluateCDF( 1e-5, 0.2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 7.630817406395892233e-01, 1e-12 );

  // Check between two bins
  cdf = native_distribution->evaluateCDF( 1.1e-5, 0.2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 7.690137233752327717e-01, 1e-6 );

  // Check the last bin
  cdf = native_distribution->evaluateCDF( 20.0, max_energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 9.999999965390767853e-01, 1e-12 );

  // Check above the last bin
  cdf = native_distribution->evaluateCDF( 20.01, 22.1 );
  FRENSIE_CHECK_SMALL( cdf, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
FRENSIE_UNIT_TEST( ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory,
                   sample )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.1;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double scattering_angle_cosine, outgoing_energy, incoming_energy = 1e-5;

  // sample the electron
  native_distribution->sample( incoming_energy,
                               outgoing_energy,
                               scattering_angle_cosine );

  // Test scattered electron
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 8.101292518836437917e-02, 1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 1.525931642077658522e-03, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
FRENSIE_UNIT_TEST( ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory,
                   sampleAndRecordTrials )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.1;

  MonteCarlo::AdjointElectronScatteringDistribution::Counter trials = 0.0;

  double incoming_energy = 1e-5;

  double outgoing_energy, scattering_angle_cosine;

  // sample the electron
  native_distribution->sampleAndRecordTrials( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine,
                                              trials );

  // Test trials
  FRENSIE_CHECK_EQUAL( trials, 1.0 );

  // Test scattered electron
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 8.101292518836437917e-02, 1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 1.525931642077658522e-03, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
FRENSIE_UNIT_TEST( ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory,
                   scatterAdjointElectron )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.1;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::AdjointElectronState electron( 0 );
  electron.setEnergy( 1e-5 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter electron
  native_distribution->scatterAdjointElectron( electron,
                                               bank,
                                               shell_of_interaction );

  // Test original electron
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getZDirection(), 8.101292518836437917e-02, 1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getEnergy(), 1.525931642077658522e-03, 1e-12 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_native_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_native_file",
                                        test_native_file_name, "",
                                        "Test Native file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create the native data file container
  data_container.reset( new Data::AdjointElectronPhotonRelaxationDataContainer(
                             test_native_file_name ) );

  // Set binding energy
  double binding_energy = 1.361E-05;

  std::set<unsigned> subshells = data_container->getSubshells();

  double evaluation_tol = 1e-7;

  // Create the electroionization subshell distribution
  IonizationNativeFactory::createElectroionizationSubshellDistribution<Utility::LogLogLog,Utility::UnitBaseCorrelated>(
    *data_container,
    1,
    binding_energy,
    native_distribution,
    evaluation_tol );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstElectroionizationSubshellAdjointElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
