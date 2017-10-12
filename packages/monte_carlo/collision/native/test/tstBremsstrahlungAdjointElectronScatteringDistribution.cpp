//---------------------------------------------------------------------------//
//!
//! \file   tstBremsstrahlungAdjointElectronScatteringScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  Bremsstrahlung electron scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "MonteCarlo_UnitTestHarnessExtensions.hpp"
#include "MonteCarlo_BremsstrahlungAdjointElectronScatteringDistribution.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_RandomNumberGenerator.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::BremsstrahlungAdjointElectronScatteringDistribution>
  adjoint_brem_dist;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the min incoming electron energy
TEUCHOS_UNIT_TEST( BremsstrahlungAdjointElectronScatteringDistribution,
                   getMinEnergy )
{
  TEST_EQUALITY_CONST( adjoint_brem_dist->getMinEnergy(), 1E-5 );
}

//---------------------------------------------------------------------------//
// Check that the max incoming electron energy
TEUCHOS_UNIT_TEST( BremsstrahlungAdjointElectronScatteringDistribution,
                   getMaxEnergy )
{
  TEST_EQUALITY_CONST( adjoint_brem_dist->getMaxEnergy(), 20.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated for a given incoming and knock-on energy
TEUCHOS_UNIT_TEST( BremsstrahlungAdjointElectronScatteringDistribution,
                   evaluate )
{
  // LinLinLog interpoation used.
  double pdf;

  // Check below lowest bin
  pdf = adjoint_brem_dist->evaluate( 1.0e-6, 2.0e-5 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 0.0, 1e-12 );

  // Check on lowest bin
  pdf = adjoint_brem_dist->evaluate( 1.0e-5, 20.2 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 6.0304868712453223e-08, 1e-12 );

  // Check inbetween bins
  pdf = adjoint_brem_dist->evaluate( 1.1e-5, 1.0 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 2.2204058721960361e-06, 1e-12 );

  // Check on highest bin
  pdf = adjoint_brem_dist->evaluate( 20.0, 20.000000201 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 3.6906111654728930e+05, 1e-12 );

  // Check above highest bin
  pdf = adjoint_brem_dist->evaluate( 21.0, 22.0 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated for a given incoming and knock-on energy
TEUCHOS_UNIT_TEST( BremsstrahlungAdjointElectronScatteringDistribution,
                   evaluatePDF )
{
  // LinLinLog interpoation used.
  double pdf;

  // Check below lowest bin
  pdf = adjoint_brem_dist->evaluatePDF( 1.0e-6, 2.0e-5 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 0.0, 1e-12 );

  // Check on lowest bin
  pdf = adjoint_brem_dist->evaluatePDF( 1.0e-5, 20.2 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 5.2460964280768464e-08, 1e-12 );

  // Check inbetween bins
  pdf = adjoint_brem_dist->evaluatePDF( 1.1e-5, 1.0 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 1.9343909245238045e-06, 1e-6 );

  // Check on highest bin
  pdf = adjoint_brem_dist->evaluatePDF( 20.0, 20.000000201 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 3.2815148160976853e+05, 1e-12 );

  // Check above highest bin
  pdf = adjoint_brem_dist->evaluatePDF( 21.0, 22.0 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated for a given incoming and knock-on energy
TEUCHOS_UNIT_TEST( BremsstrahlungAdjointElectronScatteringDistribution,
                   evaluateCDF )
{
  // LinLinLog interpoation used.
  double cdf;

  // Check below lowest bin
  cdf = adjoint_brem_dist->evaluateCDF( 1.0e-6, 2.0e-5 );
  UTILITY_TEST_FLOATING_EQUALITY( cdf, 0.0, 1e-12 );

  // Check on lowest bin
  cdf = adjoint_brem_dist->evaluateCDF( 1.0e-5, 10.1000050505 );
  UTILITY_TEST_FLOATING_EQUALITY( cdf, 9.9999924241929028e-01, 1e-12 );

  // Check inbetween bins
  cdf = adjoint_brem_dist->evaluateCDF( 1.1e-5, 1.0 );
  UTILITY_TEST_FLOATING_EQUALITY( cdf, 9.9999626380824158e-01, 1e-6 );

  // Check on highest bin
  cdf = adjoint_brem_dist->evaluateCDF( 20.0, 20.1000000505 );
  UTILITY_TEST_FLOATING_EQUALITY( cdf, 9.5489335170137102e-01, 1e-12 );

  // Check above highest bin
  cdf = adjoint_brem_dist->evaluateCDF( 21.0, 22.0 );
  UTILITY_TEST_FLOATING_EQUALITY( cdf, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a bremsstrahlung photon can be sampled using detailed 2BS
TEUCHOS_UNIT_TEST( BremsstrahlungAdjointElectronScatteringDistribution,
                   sample )
{
  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // Correlated sample the 1e-5 MeV and 1.1192e-5 MeV distributions
  fake_stream[1] = 0.5; // Sample an E_out of 3.7392446346993542e-05

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double outgoing_energy, scattering_angle, incoming_energy = 1.1e-5;

  adjoint_brem_dist->sample( incoming_energy, outgoing_energy, scattering_angle );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( outgoing_energy, 1.7653510258260282e-05, 1e-12 );
  TEST_FLOATING_EQUALITY( scattering_angle, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
/* Check that a bremsstrahlung photon can be sampled and the trial number
 * recorded using detailed 2BS
 */
TEUCHOS_UNIT_TEST( BremsstrahlungAdjointElectronScatteringDistribution,
                   sampleAndRecordTrials )
{
  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // Correlated sample the 1e-5 MeV and 1.1192e-5 MeV distributions
  fake_stream[1] = 0.5; // Sample an E_out of 3.7392446346993542e-05

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned trials = 0.0;

  double outgoing_energy, scattering_angle, incoming_energy = 1.1e-5;

  adjoint_brem_dist->sampleAndRecordTrials( incoming_energy,
                                          outgoing_energy,
                                          scattering_angle,
                                          trials );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( outgoing_energy, 1.7653510258260282e-05, 1e-12 );
  TEST_FLOATING_EQUALITY( scattering_angle, 1.0, 1e-12 );
  TEST_EQUALITY_CONST( trials, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that an electron can undergo adjoint bremsstrahlung scattering
TEUCHOS_UNIT_TEST( BremsstrahlungAdjointElectronScatteringDistribution,
                   scatterAdjointElectron )
{
  MonteCarlo::ParticleBank bank;

  MonteCarlo::AdjointElectronState electron( 1 );
  electron.setEnergy( 1.1e-5 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  Data::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // Correlated sample the 1e-5 MeV and 1.1192e-5 MeV distributions
  fake_stream[1] = 0.5; // Sample an E_out of 3.7392446346993542e-05

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  adjoint_brem_dist->scatterAdjointElectron( electron,
                                             bank,
                                             shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( electron.getEnergy(), 1.7653510258260282e-05, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getXDirection(), 0.0, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getYDirection(), 0.0, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 1.0, 1e-12 );
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
  std::shared_ptr<Data::AdjointElectronPhotonRelaxationDataContainer>
    data_container( new Data::AdjointElectronPhotonRelaxationDataContainer(
        test_native_file_name ) );

  // Get the energy grid
  std::vector<double> energy_grid;

  if ( data_container->seperateAdjointBremsstrahlungEnergyGrid() )
    energy_grid = data_container->getAdjointElectronBremsstrahlungEnergyGrid();
  else
    energy_grid = data_container->getAdjointElectronEnergyGrid();

  // Get the function data
  Utility::FullyTabularTwoDDistribution::DistributionType
    function_data( energy_grid.size() );

  for( unsigned n = 0; n < energy_grid.size(); ++n )
  {
    function_data[n].first = energy_grid[n];

    // Get the outgoing energy of the adjoint bremsstrahlung electron at the incoming energy
    std::vector<double> outgoing_energy(
      data_container->getAdjointElectronBremsstrahlungEnergy( energy_grid[n] ) );

    // Get the adjoint bremsstrahlung pdf at the incoming energy
    std::vector<double> pdf(
      data_container->getAdjointElectronBremsstrahlungPDF( energy_grid[n] ) );

    function_data[n].second.reset(
      new const Utility::TabularDistribution<Utility::LinLin>( outgoing_energy,
                                                               pdf ) );
  }

  double evaluation_tol = 1e-7;

  // Create the energy gain function
  std::shared_ptr<Utility::FullyTabularTwoDDistribution> energy_gain_function(
    new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LinLinLog,Utility::Correlated>(
            function_data,
            1e-6,
            evaluation_tol ) );

  bool correlated_sampling_mode_on = true;
  bool unit_based_interpolation_mode_on = true;

  // Create the scattering distribution
  adjoint_brem_dist.reset(
    new MonteCarlo::BremsstrahlungAdjointElectronScatteringDistribution(
        energy_gain_function,
        correlated_sampling_mode_on,
        unit_based_interpolation_mode_on ) );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstBremsstrahlungAdjointElectronScatteringScatteringDistribution.cpp
//---------------------------------------------------------------------------//
