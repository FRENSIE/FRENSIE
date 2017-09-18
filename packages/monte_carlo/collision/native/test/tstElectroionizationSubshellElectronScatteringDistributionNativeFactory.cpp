//---------------------------------------------------------------------------//
//!
//! \file   tstElectroionizationSubshellElectronScatteringDistributionNativeFactory.cpp
//! \author Luke Kersting
//! \brief  electroionization subshell scattering distribution Native factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionNativeFactory.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<Data::ElectronPhotonRelaxationDataContainer> data_container;

std::shared_ptr<const MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution>
  native_distribution, exact_native_distribution;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the subshell binding energy
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   getBindingEnergy )
{

  // Get binding energy
  double binding_energy =
    native_distribution->getBindingEnergy();

  // Test original electron
  TEST_EQUALITY_CONST( binding_energy, 8.8290E-02 );
}

//---------------------------------------------------------------------------//
// Check that the min secondary (knock-on) electron energy can be returned
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistributionNativeFactory,
                   getMinSecondaryEnergyAtIncomingEnergy )
{
  // Get min energy
  double min_energy =
    native_distribution->getMinSecondaryEnergyAtIncomingEnergy( 8.829E-02 );
  TEST_EQUALITY_CONST( min_energy, 0.0 );

  // Get min energy
  min_energy =
    native_distribution->getMinSecondaryEnergyAtIncomingEnergy( 8.829E-02 + 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( min_energy, 4.9960036108132044e-16, 1e-12 );

  // Get min energy
  min_energy =
    native_distribution->getMinSecondaryEnergyAtIncomingEnergy( 1e5 );
  UTILITY_TEST_FLOATING_EQUALITY( min_energy, 1e-7, 1e-12 );

  // Get min energy
  min_energy =
    native_distribution->getMinSecondaryEnergyAtIncomingEnergy( 2.0 );
  UTILITY_TEST_FLOATING_EQUALITY( min_energy, 1e-7, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the max secondary (knock-on) electron energy can be returned
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistributionNativeFactory,
                   getMaxSecondaryEnergyAtIncomingEnergy )
{
  // Get max energy
  double max_energy =
    native_distribution->getMaxSecondaryEnergyAtIncomingEnergy( 8.829E-02 );

  // Test original electron
  TEST_EQUALITY_CONST( max_energy, 0.0 );

  // Get max energy
  max_energy =
    native_distribution->getMaxSecondaryEnergyAtIncomingEnergy( 1e5 );

  // Test original electron
  UTILITY_TEST_FLOATING_EQUALITY( max_energy, 4.9999955855E+04, 1e-12 );

  // Get max energy
  max_energy =
    native_distribution->getMaxSecondaryEnergyAtIncomingEnergy( 2.0 );

  // Test original electron
  UTILITY_TEST_FLOATING_EQUALITY( max_energy, 9.55855E-01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated for a given incoming and knock-on energy
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistributionNativeFactory,
                   evaluatePDF )
{
  double pdf;

  pdf = native_distribution->evaluatePDF( 8.829e-2 + 1e-8, 1e-8 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 0.0, 1e-12 );

  pdf = native_distribution->evaluatePDF( 8.829e-2 + 3e-8, 1.0001e-08 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 11110995.37814653106, 1e-6 );

  pdf = native_distribution->evaluatePDF( 9.12175e-2, 4.275e-4 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 689.2154402763227381, 1e-12 );

  pdf = native_distribution->evaluatePDF( 1e-1, 1e-2 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 662.92869138138178187, 1e-6 );

  pdf = native_distribution->evaluatePDF( 1.0, 1.33136131511529e-1 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 1.5969818328396216955, 1e-12 );

  pdf = native_distribution->evaluatePDF( 1.0, 9.71630E-02 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 2.38239950812861E+00, 1e-12 );

  pdf = native_distribution->evaluatePDF( 1.0e5, 1.752970E+02 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 4.98650620153625E-07, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistributionNativeFactory,
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
  TEST_FLOATING_EQUALITY( knock_on_angle_cosine, 0.2778434545019750, 1e-12 );
  TEST_FLOATING_EQUALITY( knock_on_energy, 4.056721346111550E-02, 1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistributionNativeFactory,
                   samplePrimaryAndSecondary )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.0;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0;

  double outgoing_energy, knock_on_energy,
         scattering_angle_cosine, knock_on_angle_cosine;

  // sample the electron
  native_distribution->samplePrimaryAndSecondary( incoming_energy,
                                                  outgoing_energy,
                                                  knock_on_energy,
                                                  scattering_angle_cosine,
                                                  knock_on_angle_cosine );

  // Test original electron
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.9645918284466900, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 0.8711427865388850, 1e-12 );

  // Test knock-on electron
  TEST_FLOATING_EQUALITY( knock_on_angle_cosine, 0.2778434545019750, 1e-12 );
  TEST_FLOATING_EQUALITY( knock_on_energy, 4.056721346111550E-02, 1e-12 );

  incoming_energy = 8.829E-02 + 1e-5;
    // sample the electron
  native_distribution->samplePrimaryAndSecondary( incoming_energy,
                                                  outgoing_energy,
                                                  knock_on_energy,
                                                  scattering_angle_cosine,
                                                  knock_on_angle_cosine );

  // Test original electron
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 1.1086341090801404e-02, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 9.9896875190139731e-06, 1e-12 );

  // Test knock-on electron
  TEST_FLOATING_EQUALITY( knock_on_angle_cosine, 3.5620169782643124e-04, 1e-12 );
  TEST_FLOATING_EQUALITY( knock_on_energy, 1.0312480982149415e-08, 1e-12 );

  // sample the electron
  native_distribution->samplePrimaryAndSecondary( incoming_energy,
                                                  outgoing_energy,
                                                  knock_on_energy,
                                                  scattering_angle_cosine,
                                                  knock_on_angle_cosine );

  // Test original electron
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 7.8432913332312070e-03, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 5e-6, 1e-12 );

  // Test knock-on electron
  TEST_FLOATING_EQUALITY( knock_on_angle_cosine, 7.8432913332312070e-03, 1e-12 );
  TEST_FLOATING_EQUALITY( knock_on_energy, 5e-6, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistributionNativeFactory,
                   sample_exact )
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
  exact_native_distribution->samplePrimaryAndSecondary( incoming_energy,
                                                        outgoing_energy,
                                                        knock_on_energy,
                                                        scattering_angle_cosine,
                                                        knock_on_angle_cosine );

  // Test original electron
  TEST_EQUALITY_CONST( scattering_angle_cosine, 0.0 );
  TEST_EQUALITY_CONST( outgoing_energy, 0.0 );

  // Test knock-on electron
  TEST_FLOATING_EQUALITY( knock_on_angle_cosine, 1.1088260343863984e-07, 1e-12 );
  TEST_FLOATING_EQUALITY( knock_on_energy, 9.9920072216264089e-16, 1e-12 );

  // sample the electron
  exact_native_distribution->samplePrimaryAndSecondary( incoming_energy,
                                                        outgoing_energy,
                                                        knock_on_energy,
                                                        scattering_angle_cosine,
                                                        knock_on_angle_cosine );

  // Test original electron
  TEST_EQUALITY_CONST( scattering_angle_cosine, 0.0 );
  TEST_EQUALITY_CONST( outgoing_energy, 0.0 );

  // Test knock-on electron
  TEST_FLOATING_EQUALITY( knock_on_angle_cosine, 1.1088260343863984e-07, 1e-12 );
  TEST_FLOATING_EQUALITY( knock_on_energy, 9.9920072216264089e-16, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistributionNativeFactory,
                   sampleAndRecordTrials )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned trials = 0.0;

  double incoming_energy = 1.0;

  double knock_on_energy, scattering_angle_cosine, knock_on_angle_cosine;

  // sample the electron
  native_distribution->sampleAndRecordTrials( incoming_energy,
                                              knock_on_energy,
                                              knock_on_angle_cosine,
                                              trials );

  // Test trials
  TEST_EQUALITY_CONST( trials, 1.0 );

  // Test knock-on electron
  TEST_FLOATING_EQUALITY( knock_on_angle_cosine, 0.2778434545019750, 1e-12 );
  TEST_FLOATING_EQUALITY( knock_on_energy, 4.056721346111550E-02, 1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistributionNativeFactory,
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
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 0.9645918284466900, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getEnergy(), 0.8711427865388850, 1e-12 );

  // Test knock-on electron
  TEST_FLOATING_EQUALITY( bank.top().getZDirection(), 0.2778434545019750, 1e-12 );
  TEST_FLOATING_EQUALITY( bank.top().getEnergy(), 4.056721346111550E-02, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistributionNativeFactory,
                   scatterElectron_exact )
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
    exact_native_distribution->scatterElectron( electron,
                                                bank,
                                                shell_of_interaction );

    // Test original electron
    TEST_ASSERT( electron.isGone() );

    // Test knock-on electron
    TEST_FLOATING_EQUALITY( bank.top().getZDirection(), 1.1088260343863984e-07, 1e-12 );
    TEST_FLOATING_EQUALITY( bank.top().getEnergy(), 9.9920072216264089e-16, 1e-12 );
  }
  {
    MonteCarlo::ElectronState electron( 0 );
    electron.setEnergy( 8.829E-02 + 1e-15 );
    electron.setDirection( 0.0, 0.0, 1.0 );

    // Analytically scatter electron
    exact_native_distribution->scatterElectron( electron,
                                                bank,
                                                shell_of_interaction );

    // Test original electron
    TEST_ASSERT( electron.isGone() );

    // Test knock-on electron
    TEST_FLOATING_EQUALITY( bank.top().getZDirection(), 1.1088260343863984e-07, 1e-12 );
    TEST_FLOATING_EQUALITY( bank.top().getEnergy(), 9.9920072216264089e-16, 1e-12 );
  }
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_native_file_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_native_file",
                   &test_native_file_name,
                   "Test Native file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Create the native data file container
  data_container.reset( new Data::ElectronPhotonRelaxationDataContainer(
                             test_native_file_name ) );

  // Set binding energy
  double binding_energy = 8.829E-02;

  std::set<unsigned> subshells = data_container->getSubshells();

  // Create the electroionization subshell distribution
  MonteCarlo::ElectroionizationSubshellElectronScatteringDistributionNativeFactory::createElectroionizationSubshellDistribution<Utility::LinLinLog>(
    *data_container,
    *subshells.begin(),
    binding_energy,
    native_distribution,
    true,
    true );

  // Create the electroionization subshell distribution
  MonteCarlo::ElectroionizationSubshellElectronScatteringDistributionNativeFactory::createElectroionizationSubshellDistribution<Utility::LogLogLog>(
    *data_container,
    *subshells.begin(),
    binding_energy,
    exact_native_distribution,
    true,
    false );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstElectroionizationSubshellElectronScatteringDistributionNativeFactory.cpp
//---------------------------------------------------------------------------//
