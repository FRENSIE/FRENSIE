//---------------------------------------------------------------------------//
//!
//! \file   tstElectroionizationSubshellAdjointElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  adjoint electroionization subshell scattering distribution Native factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

typedef MonteCarlo::ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory
    IonizationNativeFactory;

Teuchos::RCP<Data::AdjointElectronPhotonRelaxationDataContainer> data_container;

std::shared_ptr<const MonteCarlo::ElectroionizationSubshellAdjointElectronScatteringDistribution>
  native_distribution;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the subshell binding energy
TEUCHOS_UNIT_TEST( ElectroionizationSubshellAdjointElectronScatteringDistribution,
                   getBindingEnergy )
{

  // Get binding energy
  double binding_energy = native_distribution->getBindingEnergy();

  // Test original electron
  TEST_EQUALITY_CONST( binding_energy, 8.8290E-02 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated for a given incoming and knock-on energy
TEUCHOS_UNIT_TEST( ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory,
                   evaluate )
{
  double pdf = native_distribution->evaluate( 8.829e-2 + 1e-8, 1e-8 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 0.0, 1e-12 );

  pdf = native_distribution->evaluate( 8.829e-2 + 2e-8, 1e-8 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 11111033.955596962944, 1e-12 );

  pdf = native_distribution->evaluate( 9.12175e-2, 4.275e-4 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 689.2154402763227381, 1e-12 );

  pdf = native_distribution->evaluate( 1e-1, 1e-2 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 662.81827321455386937, 1e-12 );

  pdf = native_distribution->evaluate( 1.0, 1.33136131511529e-1 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 1.5969818328396216955, 1e-12 );

  pdf = native_distribution->evaluate( 1.0, 9.71630E-02 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 2.38239950812861E+00, 1e-12 );

  pdf = native_distribution->evaluate( 1.0e5, 1.752970E+02 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 4.986498947129447938e-07, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated for a given incoming and knock-on energy
TEUCHOS_UNIT_TEST( ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory,
                   evaluatePDF )
{
  double pdf = native_distribution->evaluatePDF( 8.829e-2 + 1e-8, 1e-8 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 0.0, 1e-12 );

  pdf = native_distribution->evaluatePDF( 8.829e-2 + 2e-8, 1e-8 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 11111033.955596962944, 1e-12 );

  pdf = native_distribution->evaluatePDF( 9.12175e-2, 4.275e-4 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 689.2154402763227381, 1e-12 );

  pdf = native_distribution->evaluatePDF( 1e-1, 1e-2 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 662.81827321455386937, 1e-12 );

  pdf = native_distribution->evaluatePDF( 1.0, 1.33136131511529e-1 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 1.5969818328396216955, 1e-12 );

  pdf = native_distribution->evaluatePDF( 1.0, 9.71630E-02 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 2.38239950812861E+00, 1e-12 );

  pdf = native_distribution->evaluatePDF( 1.0e5, 1.752970E+02 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 4.986498947129447938e-07, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated for a given incoming and knock-on energy
TEUCHOS_UNIT_TEST( ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory,
                   evaluateCDF )
{
  double pdf = native_distribution->evaluateCDF( 8.829e-2 + 1e-8, 1e-8 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 0.0, 1e-12 );

  pdf = native_distribution->evaluateCDF( 8.829e-2 + 2e-8, 1e-8 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 11111033.955596962944, 1e-12 );

  pdf = native_distribution->evaluateCDF( 9.12175e-2, 4.275e-4 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 689.2154402763227381, 1e-12 );

  pdf = native_distribution->evaluateCDF( 1e-1, 1e-2 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 662.81827321455386937, 1e-12 );

  pdf = native_distribution->evaluateCDF( 1.0, 1.33136131511529e-1 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 1.5969818328396216955, 1e-12 );

  pdf = native_distribution->evaluateCDF( 1.0, 9.71630E-02 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 2.38239950812861E+00, 1e-12 );

  pdf = native_distribution->evaluateCDF( 1.0e5, 1.752970E+02 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 4.986498947129447938e-07, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
TEUCHOS_UNIT_TEST( ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory,
                   sample )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0;

  // sample the electron
  native_distribution->sample( incoming_energy,
                               outgoing_energy,
                               scattering_angle_cosine );

  // Test knock-on electron
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.2778434545019750, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 4.056721346111550E-02, 1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
TEUCHOS_UNIT_TEST( ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory,
                   sampleAndRecordTrials )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;

  unsigned trials = 0.0;

  double incoming_energy = 1.0;

  double outgoing_energy, scattering_angle_cosine;

  // sample the electron
  native_distribution->sampleAndRecordTrials( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine,
                                              trials );

  // Test trials
  TEST_EQUALITY_CONST( trials, 1.0 );

  // Test knock-on electron
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.2778434545019750, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 4.056721346111550E-02, 1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
TEUCHOS_UNIT_TEST( ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory,
                   scatterAdjointElectron )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::AdjointElectronState electron( 0 );
  electron.setEnergy( 1.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter electron
  native_distribution->scatterAdjointElectron( electron,
                                               bank,
                                               shell_of_interaction );

  // Test original electron
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 0.9645918284466900, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getEnergy(), 0.8711427865388850, 1e-12 );
}

}
//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_native_file_name;

  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_native_file",
                 &test_native_file_name,
                 "Test native file name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out =
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return =
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL )
  {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Create the native data file container
  data_container.reset( new Data::AdjointElectronPhotonRelaxationDataContainer(
                             test_native_file_name ) );

  // Set binding energy
  double binding_energy = 8.829E-02;

  std::set<unsigned> subshells = data_container->getSubshells();

  // Create the electroionization subshell distribution
  IonizationNativeFactory::createElectroionizationSubshellDistribution(
    *data_container,
    *subshells.begin(),
    binding_energy,
    native_distribution );

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
// end tstElectroionizationSubshellAdjointElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
