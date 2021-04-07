//---------------------------------------------------------------------------//
//!
//! \file   tstElectroionizationSubshellAdjointElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  adjoint electroionization subshell scattering distribution Native factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationSubshellAdjointElectronScatteringDistribution.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "MonteCarlo_AdjointElectronProbeState.hpp"

//---------------------------------------------------------------------------//
// Testing Structs
//---------------------------------------------------------------------------//
class TestElectroionizationSubshellAdjointElectronScatteringDistribution : public MonteCarlo::ElectroionizationSubshellAdjointElectronScatteringDistribution
{
public:

  // Constructor
  TestElectroionizationSubshellAdjointElectronScatteringDistribution(
    const std::shared_ptr<const BasicBivariateDist>&
      electroionization_subshell_scattering_distribution,
    const double& binding_energy )
    : MonteCarlo::ElectroionizationSubshellAdjointElectronScatteringDistribution(
        electroionization_subshell_scattering_distribution,
        binding_energy )
  { /* ... */ }

  // Destructor
  ~TestElectroionizationSubshellAdjointElectronScatteringDistribution()
  { /* ... */ }

  using MonteCarlo::ElectroionizationSubshellAdjointElectronScatteringDistribution::LineEnergyIterator;
  using MonteCarlo::ElectroionizationSubshellAdjointElectronScatteringDistribution::isEnergyAboveScatteringWindow;
  using MonteCarlo::ElectroionizationSubshellAdjointElectronScatteringDistribution::isEnergyInScatteringWindow;
  using MonteCarlo::ElectroionizationSubshellAdjointElectronScatteringDistribution::getCriticalLineEnergiesInScatteringWindow;
};

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<Data::AdjointElectronPhotonRelaxationDataContainer> data_container;

std::shared_ptr<TestElectroionizationSubshellAdjointElectronScatteringDistribution>
  distribution;

double max_energy = 2.00000147100000021e+01;
double binding_energy;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the subshell binding energy
FRENSIE_UNIT_TEST( ElectroionizationSubshellAdjointElectronScatteringDistribution,
                   getBindingEnergy )
{
  FRENSIE_CHECK_EQUAL( binding_energy, 1.361E-05 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated for a given incoming and knock-on energy
FRENSIE_UNIT_TEST( ElectroionizationSubshellAdjointElectronScatteringDistribution,
                   evaluate )
{
  double pdf;

  // Check below the first bin
  pdf = distribution->evaluate( 9.99e-6, 2.3711E-5 );
  FRENSIE_CHECK_SMALL( pdf, 1e-12 );

  // Check the first bin
  pdf = distribution->evaluate( 1e-5, 2.3711E-5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 2.242860168116929742e+02, 1e-12 );

  // Check between two bins
  pdf = distribution->evaluate( 1.1e-5, 0.2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.858726091810971592e-01, 1e-12 );

  // Check the last bin
  pdf = distribution->evaluate( 20.0, max_energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 9.741633350079954835e+05, 1e-12 );

  // Check above the last bin
  pdf = distribution->evaluate( 20.01, 22.1 );
  FRENSIE_CHECK_SMALL( pdf, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated for a given incoming and knock-on energy
FRENSIE_UNIT_TEST( ElectroionizationSubshellAdjointElectronScatteringDistribution,
                   evaluatePDF )
{
  double pdf;

  // Check below the first bin
  pdf = distribution->evaluatePDF( 9.99e-6, 2.3711E-5 );
  FRENSIE_CHECK_SMALL( pdf, 1e-12 );

  // Check the first bin
  pdf = distribution->evaluatePDF( 1e-5, 2.3711E-5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 6.894608999906166957e+01, 1e-12 );

  // Check between two bins
  pdf = distribution->evaluatePDF( 1.1e-5, 0.2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 5.487424940913061128e-02, 1e-6 );

  // Check the last bin
  pdf = distribution->evaluatePDF( 20.0, max_energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 9.741633364475551061e+05, 1e-12 );

  // Check above the last bin
  pdf = distribution->evaluatePDF( 20.01, 22.1 );
  FRENSIE_CHECK_SMALL( pdf, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated for a given incoming and knock-on energy
FRENSIE_UNIT_TEST( ElectroionizationSubshellAdjointElectronScatteringDistribution,
                   evaluateCDF )
{
  double cdf;

  // Check below the first bin
  cdf = distribution->evaluateCDF( 9.99e-6, 1.361e-5 );
  FRENSIE_CHECK_SMALL( cdf, 1e-12 );

  // Check the first bin
  cdf = distribution->evaluateCDF( 1e-5, 0.2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 7.630817406395892233e-01, 1e-12 );

  // Check between two bins
  cdf = distribution->evaluateCDF( 1.1e-5, 0.2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 7.690137233752327717e-01, 1e-12 );

  // Check the last bin
  cdf = distribution->evaluateCDF( 20.0, max_energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 9.999999965390767853e-01, 1e-12 );

  // Check above the last bin
  cdf = distribution->evaluateCDF( 20.01, 22.1 );
  FRENSIE_CHECK_SMALL( cdf, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
FRENSIE_UNIT_TEST( ElectroionizationSubshellAdjointElectronScatteringDistribution,
                   sample )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.1;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double scattering_angle_cosine, outgoing_energy, incoming_energy = 1e-5;

  // sample the electron
  distribution->sample( incoming_energy,
                        outgoing_energy,
                        scattering_angle_cosine );

  // Test scattered electron
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 8.101292518836437917e-02, 1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 1.525931642077658522e-03, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
FRENSIE_UNIT_TEST( ElectroionizationSubshellAdjointElectronScatteringDistribution,
                   sampleAndRecordTrials )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.1;

  MonteCarlo::AdjointElectronScatteringDistribution::Counter trials = 0;
  double incoming_energy = 1e-5;
  double outgoing_energy, scattering_angle_cosine;

  // sample the electron
  distribution->sampleAndRecordTrials( incoming_energy,
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
FRENSIE_UNIT_TEST( ElectroionizationSubshellAdjointElectronScatteringDistribution,
                   scatterAdjointElectron )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.1;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::AdjointElectronState adjoint_electron( 0 );
  adjoint_electron.setEnergy( 1e-5 );
  adjoint_electron.setDirection( 0.0, 0.0, 1.0 );

  // Scatter the adjoint electron
  distribution->scatterAdjointElectron( adjoint_electron,
                                        bank,
                                        shell_of_interaction );

  // Test the adjoint electron
  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_electron.getZDirection(), 8.101292518836437917e-02, 1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_electron.getEnergy(), 1.525931642077658522e-03, 1e-12 );

  FRENSIE_CHECK_EQUAL( bank.size(), 4 );

  double pdf = distribution->evaluate( 1e-5, 0.08 );
  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(), 0.08 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getWeight(), pdf, 1e-15 );

  bank.pop();

  pdf = distribution->evaluate(
                1e-5, Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(),
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getWeight(), pdf, 1e-15 );

  bank.pop();

  pdf = distribution->evaluate( 1e-5, 1.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(), 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getWeight(), pdf, 1e-15 );

  bank.pop();

  pdf = distribution->evaluate( 1e-5, 5.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(), 5.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getWeight(), pdf, 1e-15 );

  bank.pop();

  Utility::RandomNumberGenerator::unsetFakeStream();

  // Generate a probe with energy 5.0
  adjoint_electron.setWeight( 1.0 );
  adjoint_electron.setEnergy( 4.9 );
  adjoint_electron.setDirection( 0.0, 0.0, 1.0 );

  distribution->scatterAdjointElectron( adjoint_electron,
                                        bank,
                                        shell_of_interaction );

  FRENSIE_CHECK_EQUAL( bank.size(), 1 );

  pdf = distribution->evaluate( 4.9, 5.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(), 5.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getWeight(), pdf, 1e-15 );

  bank.pop();

  // Make sure that probes do not generate more probe particles
  MonteCarlo::AdjointElectronProbeState adjoint_electron_probe( 0 );
  adjoint_electron_probe.setEnergy( 0.3 );
  adjoint_electron_probe.setDirection( 0.0, 0.0, 1.0 );

  distribution->scatterAdjointElectron( adjoint_electron_probe,
                                        bank,
                                        shell_of_interaction );

  FRENSIE_CHECK_EQUAL( bank.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check if an energy is above the scattering window
FRENSIE_UNIT_TEST( ElectroionizationSubshellAdjointElectronScatteringDistribution,
                   isEnergyAboveScatteringWindow )
{
  FRENSIE_CHECK( !distribution->isEnergyAboveScatteringWindow( 0.1, 9.9999e-6 ) );

  FRENSIE_CHECK( !distribution->isEnergyAboveScatteringWindow( 0.1, 1e-5 ) );

  FRENSIE_CHECK( !distribution->isEnergyAboveScatteringWindow( 0.1, 0.1 - binding_energy - 2e-7 ) );

  FRENSIE_CHECK( distribution->isEnergyAboveScatteringWindow( 0.1, 0.1 - binding_energy ) );
}

//---------------------------------------------------------------------------//
// Check if an energy is in the scattering window
FRENSIE_UNIT_TEST( ElectroionizationSubshellAdjointElectronScatteringDistribution,
                   isEnergyInScatteringWindow )
{
  FRENSIE_CHECK( !distribution->isEnergyInScatteringWindow( 0.1, 9.9999e-6 ) );

  FRENSIE_CHECK( distribution->isEnergyInScatteringWindow( 0.1, 1e-5 ));

  FRENSIE_CHECK( distribution->isEnergyInScatteringWindow( 0.1, 0.1 - binding_energy - 2e-7 ) );

  FRENSIE_CHECK( !distribution->isEnergyInScatteringWindow( 0.1, 0.1 - binding_energy ) );

  FRENSIE_CHECK( !distribution->isEnergyInScatteringWindow( 21.0, 1.0 ) );

  FRENSIE_CHECK( !distribution->isEnergyInScatteringWindow( 21.0, 21.0 - binding_energy ) );

  FRENSIE_CHECK( !distribution->isEnergyInScatteringWindow( 21.0, 21.0 ) );
}

//---------------------------------------------------------------------------//
// Check that the critical line energies in scattering window can be returned
FRENSIE_UNIT_TEST( ElectroionizationSubshellAdjointElectronScatteringDistribution,
                   getCriticalLineEnergiesInScatteringWindow )
{
  TestElectroionizationSubshellAdjointElectronScatteringDistribution::LineEnergyIterator
    start_energy, end_energy;

  distribution->getCriticalLineEnergiesInScatteringWindow( 9.9999e-6,
                                                           start_energy,
                                                           end_energy );

  FRENSIE_CHECK_EQUAL( start_energy, end_energy );

  distribution->getCriticalLineEnergiesInScatteringWindow( 1e-5,
                                                           start_energy,
                                                           end_energy );

  FRENSIE_CHECK_EQUAL( *start_energy, 0.08 );
  FRENSIE_CHECK_EQUAL( *end_energy, 21.0 );
  FRENSIE_CHECK_EQUAL( std::distance( start_energy, end_energy ), 4 );

  distribution->getCriticalLineEnergiesInScatteringWindow( 0.18,
                                                           start_energy,
                                                           end_energy );

  FRENSIE_CHECK_EQUAL( *start_energy,
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( *end_energy, 21.0 );
  FRENSIE_CHECK_EQUAL( std::distance( start_energy, end_energy), 3 );

  distribution->getCriticalLineEnergiesInScatteringWindow( 0.21,
                                                           start_energy,
                                                           end_energy );

  FRENSIE_CHECK_EQUAL( *start_energy,
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( *end_energy, 21.0 );
  FRENSIE_CHECK_EQUAL( std::distance( start_energy, end_energy ), 3 );

  distribution->getCriticalLineEnergiesInScatteringWindow( 0.25,
                                                           start_energy,
                                                           end_energy );

  FRENSIE_CHECK_EQUAL( *start_energy,
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( *end_energy, 21.0 );
  FRENSIE_CHECK_EQUAL( std::distance( start_energy, end_energy ), 3 );

  distribution->getCriticalLineEnergiesInScatteringWindow( 0.52,
                                                           start_energy,
                                                           end_energy );

  FRENSIE_CHECK_EQUAL( *start_energy, 1.0 );
  FRENSIE_CHECK_EQUAL( *end_energy, 21.0 );
  FRENSIE_CHECK_EQUAL( std::distance( start_energy, end_energy ), 2 );

  distribution->getCriticalLineEnergiesInScatteringWindow( 1.1,
                                                           start_energy,
                                                           end_energy );

  FRENSIE_CHECK_EQUAL( *start_energy, 5.0 );
  FRENSIE_CHECK_EQUAL( *end_energy, 21.0 );
  FRENSIE_CHECK_EQUAL( std::distance( start_energy, end_energy ), 1 );

  distribution->getCriticalLineEnergiesInScatteringWindow( 5.1,
                                                           start_energy,
                                                           end_energy );

  FRENSIE_CHECK_EQUAL( std::distance( start_energy, end_energy ), 0 );
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
  binding_energy = 1.361E-05;

  std::vector<double> energy_grid =
    data_container->getAdjointElectronEnergyGrid();

  // Create the scattering function
  std::vector<double> primary_grid( energy_grid.size() );
  std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
    secondary_dists( energy_grid.size() );

  std::set<unsigned> subshells = data_container->getSubshells();

  for( unsigned n = 0; n < energy_grid.size(); ++n )
  {
    primary_grid[n] = energy_grid[n];

    // Get the recoil energy distribution at the incoming energy
    std::vector<double> recoil_energy(
      data_container->getAdjointElectroionizationRecoilEnergy(
        *subshells.begin(),
        energy_grid[n] ) );

    // Get the recoil energy pdf at the incoming energy
    std::vector<double> pdf(
      data_container->getAdjointElectroionizationRecoilPDF(
        *subshells.begin(),
        energy_grid[n] ) );

    secondary_dists[n].reset(
      new const Utility::TabularDistribution<Utility::LinLin>( recoil_energy,
                                                               pdf ) );
  }

  double evaluation_tol = 1e-10;

  std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution> subshell_distribution(
     new Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::UnitBaseCorrelated<Utility::LogLogLog> >(
                                                            primary_grid,
                                                            secondary_dists,
                                                            1e-6,
                                                            evaluation_tol ) );

  distribution.reset(
     new TestElectroionizationSubshellAdjointElectronScatteringDistribution(
            subshell_distribution,
            binding_energy ) );

  // Create the scattering distribution
  std::shared_ptr<std::vector<double> >
    critical_line_energies( new std::vector<double>( 5 ) );

  (*critical_line_energies)[0] = 0.08;
  (*critical_line_energies)[1] =
    Utility::PhysicalConstants::electron_rest_mass_energy;
  (*critical_line_energies)[2] = 1.0;
  (*critical_line_energies)[3] = 5.0;
  (*critical_line_energies)[4] = 21.0;

  distribution->setCriticalLineEnergies( critical_line_energies );


  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstElectroionizationSubshellAdjointElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
