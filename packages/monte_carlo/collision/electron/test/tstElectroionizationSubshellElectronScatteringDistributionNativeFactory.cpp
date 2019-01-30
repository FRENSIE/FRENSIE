//---------------------------------------------------------------------------//
//!
//! \file   tstElectroionizationSubshellElectronScatteringDistributionNativeFactory.cpp
//! \author Luke Kersting
//! \brief  electroionization subshell scattering distribution Native factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionNativeFactory.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::unique_ptr<Data::ElectronPhotonRelaxationDataContainer> data_container;

std::shared_ptr<const MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution>
  native_distribution, correlated_distribution,
  outgoing_distribution, outgoing_ratio_distribution;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the subshell binding energy
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistributionNativeFactory,
                   getBindingEnergy )
{

  // Get binding energy
  double binding_energy = native_distribution->getBindingEnergy();

  // Test original electron
  FRENSIE_CHECK_EQUAL( binding_energy, 8.8290E-02 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated for a given incoming and knock-on energy
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistributionNativeFactory,
                   evaluatePDF )
{
  double pdf;

  pdf = native_distribution->evaluatePDF( 8.829e-2 + 1e-8, 1e-9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.111111111111111194e+07, 1e-15 );

  pdf = native_distribution->evaluatePDF( 8.829e-2 + 1e-8, 9e-9 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.111111111111111194e+07, 1e-15 );

  pdf = native_distribution->evaluatePDF( 8.829e-2 + 2e-7, 1e-8 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.111111111111111194e+07, 1e-15 );

  pdf = native_distribution->evaluatePDF( 8.829e-2 + 3e-7, 1e-7 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 9.798137958507926669e+05, 1e-2 );

  pdf = native_distribution->evaluatePDF( 9.12175e-2, 4.275e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 6.892154402763195549e+02, 1e-12 );

  pdf = native_distribution->evaluatePDF( 1e-1, 1e-2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 2.569441093957196927e+02, 1e-12 );

  pdf = native_distribution->evaluatePDF( 1.0, 1.33136131511529e-1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.596981832839622584, 1e-12 );

  pdf = native_distribution->evaluatePDF( 1.0, 9.71630E-02 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 2.38239950812861, 1e-12 );

  pdf = native_distribution->evaluatePDF( 1.0e5, 1.752970E+02 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 4.986506201539181759e-07, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistributionNativeFactory,
                   sample_knock_on )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0;

  double knock_on_energy, knock_on_angle_cosine;

  // sample the electron
  native_distribution->sample( incoming_energy,
                               knock_on_energy,
                               knock_on_angle_cosine );

  // Test knock-on electron
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_angle_cosine, 0.2778434545019750, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_energy, 4.056721346111550E-02, 1e-12 );

  incoming_energy = 8.829e-2 + 1e-8;

  // sample the electron
  native_distribution->sample( incoming_energy,
                               knock_on_energy,
                               knock_on_angle_cosine );

  // Test knock-on electron
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_angle_cosine, 1.839515146900281607e-04, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_energy, 2.749999998531980456e-09, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistributionNativeFactory,
                   sample_PrimaryAndSecondary )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.0; // Select bin to sample
  fake_stream[1] = 0.5; // Sample knock on energy
  fake_stream[2] = 0.0; // Select bin to sample
  fake_stream[3] = 0.0; // Sample knock on energy
  fake_stream[4] = 0.0; // Select bin to sample
  fake_stream[5] = 1.0-1e-15; // Sample knock on energy
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0;

  double outgoing_energy, knock_on_energy,
         scattering_angle_cosine, knock_on_angle_cosine;

  // sample the electron
  native_distribution->sample( incoming_energy,
                               outgoing_energy,
                               knock_on_energy,
                               scattering_angle_cosine,
                               knock_on_angle_cosine );

  // Test original electron
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.645918284466902248e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 8.711427865388844394e-01, 1e-12 );

  // Test knock-on electron
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_angle_cosine, 2.778434545019752844e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_energy, 4.056721346111553245e-02, 1e-12 );

  incoming_energy = 8.829E-02 + 1e-5;
  // sample the electron
  native_distribution->sample( incoming_energy,
                               outgoing_energy,
                               knock_on_energy,
                               scattering_angle_cosine,
                               knock_on_angle_cosine );

  // Test original electron
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 1.108647083342213097e-02, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 9.989921339799667145e-06, 1e-12 );

  // Test knock-on electron
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_angle_cosine, 3.521403621061872384e-04, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_energy, 1.007866019645548442e-08, 1e-12 );

  // sample the electron
  native_distribution->sample( incoming_energy,
                               outgoing_energy,
                               knock_on_energy,
                               scattering_angle_cosine,
                               knock_on_angle_cosine );

  // Test original electron
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 7.843291333231201812e-03, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 4.999999999998060704e-06, 1e-12 );

  // Test knock-on electron
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_angle_cosine, 7.843291333231203546e-03, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_energy, 4.999999999998062398e-06, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistributionNativeFactory,
                   sample_direct )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 8.829E-02 + 1e-15;

  double outgoing_energy, knock_on_energy,
         scattering_angle_cosine, knock_on_angle_cosine;

  // sample the electron
  correlated_distribution->sample( incoming_energy,
                                                        outgoing_energy,
                                                        knock_on_energy,
                                                        scattering_angle_cosine,
                                                        knock_on_angle_cosine );

  // Test original electron
  FRENSIE_CHECK_EQUAL( scattering_angle_cosine, 0.0 );
  FRENSIE_CHECK_EQUAL( outgoing_energy, 0.0 );

  // Test knock-on electron
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_angle_cosine, 1.1088260343863984e-07, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_energy, 9.9920072216264089e-16, 1e-12 );

  // sample the electron
  correlated_distribution->sample( incoming_energy,
                                                        outgoing_energy,
                                                        knock_on_energy,
                                                        scattering_angle_cosine,
                                                        knock_on_angle_cosine );

  // Test original electron
  FRENSIE_CHECK_EQUAL( scattering_angle_cosine, 0.0 );
  FRENSIE_CHECK_EQUAL( outgoing_energy, 0.0 );

  // Test knock-on electron
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_angle_cosine, 1.1088260343863984e-07, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_energy, 9.9920072216264089e-16, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistributionNativeFactory,
                   sampleAndRecordTrials )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronScatteringDistribution::Counter trials = 0.0;

  double incoming_energy = 1.0;

  double knock_on_energy, scattering_angle_cosine, knock_on_angle_cosine;

  // sample the electron
  native_distribution->sampleAndRecordTrials( incoming_energy,
                                              knock_on_energy,
                                              knock_on_angle_cosine,
                                              trials );

  // Test trials
  FRENSIE_CHECK_EQUAL( trials, 1.0 );

  // Test knock-on electron
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_angle_cosine, 0.2778434545019750, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_energy, 4.056721346111550E-02, 1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistributionNativeFactory,
                   scatterElectron )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter electron
  native_distribution->scatterElectron( electron,
                                        bank,
                                        shell_of_interaction );

  // Test original electron
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getZDirection(), 0.9645918284466900, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getEnergy(), 0.8711427865388850, 1e-12 );

  // Test knock-on electron
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getZDirection(), 0.2778434545019750, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getEnergy(), 4.056721346111550E-02, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistributionNativeFactory,
                   scatterElectron_direct )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  {
    MonteCarlo::ElectronState electron( 0 );
    electron.setEnergy( 8.829E-02 + 1e-15 );
    electron.setDirection( 0.0, 0.0, 1.0 );

    // Analytically scatter electron
    correlated_distribution->scatterElectron( electron,
                                                bank,
                                                shell_of_interaction );

    // Test original electron
    FRENSIE_CHECK( electron.isGone() );

    // Test knock-on electron
    FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getZDirection(), 1.1088260343863984e-07, 1e-12 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getEnergy(), 9.9920072216264089e-16, 1e-12 );
  }
  {
    MonteCarlo::ElectronState electron( 0 );
    electron.setEnergy( 8.829E-02 + 1e-15 );
    electron.setDirection( 0.0, 0.0, 1.0 );

    // Analytically scatter electron
    correlated_distribution->scatterElectron( electron,
                                                bank,
                                                shell_of_interaction );

    // Test original electron
    FRENSIE_CHECK( electron.isGone() );

    // Test knock-on electron
    FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getZDirection(), 1.1088260343863984e-07, 1e-12 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getEnergy(), 9.9920072216264089e-16, 1e-12 );
  }
}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistributionNativeFactory,
                   scatterPositron )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.25;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::PositronState positron( 0 );
  positron.setEnergy( 1.0 );
  positron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter positron
  native_distribution->scatterPositron( positron,
                                        bank,
                                        shell_of_interaction );

  // Test knock-on electron
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getZDirection(), 0.9645918284466900, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getEnergy(), 0.8711427865388850, 1e-12 );

  // Test original positron
  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getZDirection(), 2.778434545019752844e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getEnergy(), 4.056721346111552551e-02, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
FRENSIE_UNIT_TEST( ElectroionizationSubshellPositronScatteringDistributionNativeFactory,
                   scatterPositron_correlated )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 1e-10;
  fake_stream[1] = 1.0-1e-10;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  {
    MonteCarlo::PositronState positron( 0 );
    positron.setEnergy( 8.829E-02 + 1e-15 );
    positron.setDirection( 0.0, 0.0, 1.0 );

    // Analytically scatter positron
    correlated_distribution->scatterPositron( positron,
                                              bank,
                                              shell_of_interaction );

    // Test original positron
    FRENSIE_CHECK_FLOATING_EQUALITY( positron.getZDirection(), 1.1088260343863984e-07, 1e-12 );
    FRENSIE_CHECK_FLOATING_EQUALITY( positron.getEnergy(), 9.9920072216264089e-16, 1e-12 );

    // Test knock-on electron
    FRENSIE_CHECK_SMALL( bank.top().getZDirection(), 1e-12 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getEnergy(), 1e-15, 1e-12 );
  }
  {
    MonteCarlo::PositronState positron( 0 );
    positron.setEnergy( 8.829E-02 + 1e-15 );
    positron.setDirection( 0.0, 0.0, 1.0 );

    // Analytically scatter positron
    correlated_distribution->scatterPositron( positron,
                                                 bank,
                                                 shell_of_interaction );

    // Test original positron
    FRENSIE_CHECK_FLOATING_EQUALITY( positron.getZDirection(), 1.1088260343863984e-07, 1e-12 );
    FRENSIE_CHECK_FLOATING_EQUALITY( positron.getEnergy(), 9.9920072216264089e-16, 1e-12 );

    // Test knock-on positron
    FRENSIE_CHECK_SMALL( bank.top().getZDirection(), 1e-12 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getEnergy(), 1e-15, 1e-12 );
  }
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
  data_container.reset( new Data::ElectronPhotonRelaxationDataContainer(
                             test_native_file_name ) );

  // Set binding energy
  double binding_energy = 8.829E-02;

  std::set<unsigned> subshells = data_container->getSubshells();

  MonteCarlo::ElectroionizationSamplingType sampling_type =
    MonteCarlo::KNOCK_ON_SAMPLING;

  // Create the electroionization subshell distribution
  MonteCarlo::ElectroionizationSubshellElectronScatteringDistributionNativeFactory::createElectroionizationSubshellDistribution<Utility::LogLogLog,Utility::UnitBase>(
    *data_container,
    *subshells.begin(),
    binding_energy,
    native_distribution,
    sampling_type,
    1e-7,
    500,
    true );

  // Create the electroionization subshell distribution
  MonteCarlo::ElectroionizationSubshellElectronScatteringDistributionNativeFactory::createElectroionizationSubshellDistribution<Utility::LogLogLog,Utility::Correlated>(
    *data_container,
    *subshells.begin(),
    binding_energy,
    correlated_distribution,
    sampling_type );

  // Create the electroionization subshell distribution
  MonteCarlo::ElectroionizationSubshellElectronScatteringDistributionNativeFactory::createElectroionizationSubshellDistribution<Utility::LogLogLog,Utility::Correlated>(
    *data_container,
    *subshells.begin(),
    binding_energy,
    outgoing_distribution,
    MonteCarlo::OUTGOING_ENERGY_SAMPLING,
    1e-7,
    500,
    true );

  // Create the electroionization subshell distribution
  MonteCarlo::ElectroionizationSubshellElectronScatteringDistributionNativeFactory::createElectroionizationSubshellDistribution<Utility::LogLogLog,Utility::Correlated>(
    *data_container,
    *subshells.begin(),
    binding_energy,
    outgoing_ratio_distribution,
    MonteCarlo::OUTGOING_ENERGY_RATIO_SAMPLING,
    1e-7,
    500,
    true );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstElectroionizationSubshellElectronScatteringDistributionNativeFactory.cpp
//---------------------------------------------------------------------------//
