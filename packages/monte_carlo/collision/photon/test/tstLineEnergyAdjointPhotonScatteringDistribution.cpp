//---------------------------------------------------------------------------//
//!
//! \file   tstLineEnergyAdjointPhotonScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  The line energy adjoint photon scattering distribution tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_LineEnergyAdjointPhotonScatteringDistribution.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::AdjointPhotonScatteringDistribution> distribution;

std::shared_ptr<MonteCarlo::LineEnergyAdjointPhotonScatteringDistribution>
  full_distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the line energy can be returned
FRENSIE_UNIT_TEST( LineEnergyAdjointPhotonScatteringDistribution,
                   getLineEnergy )
{
  FRENSIE_CHECK_EQUAL( full_distribution->getLineEnergy(),
                       Utility::PhysicalConstants::electron_rest_mass_energy );
}

//---------------------------------------------------------------------------//
// Check that the min outgoing energy can be returned
FRENSIE_UNIT_TEST( LineEnergyAdjointPhotonScatteringDistribution,
                   getMinOutgoingEnergy )
{
  FRENSIE_CHECK_EQUAL( full_distribution->getMinOutgoingEnergy(),
                       2*Utility::PhysicalConstants::electron_rest_mass_energy );
}

//---------------------------------------------------------------------------//
// Check that the max outgoing energy can be returned
FRENSIE_UNIT_TEST( LineEnergyAdjointPhotonScatteringDistribution,
                   getMaxOutgoingEnergy )
{
  FRENSIE_CHECK_EQUAL( full_distribution->getMaxOutgoingEnergy(), 20.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( LineEnergyAdjointPhotonScatteringDistribution, evaluate )
{
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.5, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.5, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.5, 1.0 ), 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluate( Utility::PhysicalConstants::electron_rest_mass_energy, -1.0 ),
                          3.68484053190814587e+00,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluate( Utility::PhysicalConstants::electron_rest_mass_energy, 0.0 ),
                          3.68484053190814587e+00,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluate( Utility::PhysicalConstants::electron_rest_mass_energy, 1.0 ),
                          3.68484053190814587e+00,
                          1e-15 );

  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.52, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.52, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.52, 1.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( LineEnergyAdjointPhotonScatteringDistribution,
                   evaluate_full )
{
  FRENSIE_CHECK_EQUAL( full_distribution->evaluate( 0.5, 1.03, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( full_distribution->evaluate( 0.5, 1.03, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( full_distribution->evaluate( 0.5, 1.03, 1.0 ), 0.0 );

  FRENSIE_CHECK_EQUAL( full_distribution->evaluate( 0.5, 20.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( full_distribution->evaluate( 0.5, 20.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( full_distribution->evaluate( 0.5, 20.0, 1.0 ), 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( full_distribution->evaluate( Utility::PhysicalConstants::electron_rest_mass_energy, 1.03, -1.0 ),
                          5.49940859885078113e-08,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_distribution->evaluate( Utility::PhysicalConstants::electron_rest_mass_energy, 1.03, 0.0 ),
                          5.49940859885078113e-08,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_distribution->evaluate( Utility::PhysicalConstants::electron_rest_mass_energy, 1.03, 1.0 ),
                          5.49940859885078113e-08,
                          1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( full_distribution->evaluate( Utility::PhysicalConstants::electron_rest_mass_energy, 20.0, -1.0 ),
                          3.15900000000000014e-01,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_distribution->evaluate( Utility::PhysicalConstants::electron_rest_mass_energy, 20.0, 0.0 ),
                          3.15900000000000014e-01,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_distribution->evaluate( Utility::PhysicalConstants::electron_rest_mass_energy, 20.0, 1.0 ),
                          3.15900000000000014e-01,
                          1e-15 );

  FRENSIE_CHECK_EQUAL( full_distribution->evaluate( 0.52, 1.03, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( full_distribution->evaluate( 0.52, 1.03, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( full_distribution->evaluate( 0.52, 1.03, 1.0 ), 0.0 );

  FRENSIE_CHECK_EQUAL( full_distribution->evaluate( 0.52, 20.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( full_distribution->evaluate( 0.52, 20.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( full_distribution->evaluate( 0.52, 20.0, 1.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the marginal pdf can be evaluated
FRENSIE_UNIT_TEST( LineEnergyAdjointPhotonScatteringDistribution,
                   evaluatePDF )
{
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 0.5, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 0.5, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 0.5, 1.0 ), 0.0 );

  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( Utility::PhysicalConstants::electron_rest_mass_energy, -1.0 ),
                       0.5 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( Utility::PhysicalConstants::electron_rest_mass_energy, 0.0 ),
                       0.5 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( Utility::PhysicalConstants::electron_rest_mass_energy, 1.0 ),
                       0.5 );

  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 0.52, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 0.52, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 0.52, 1.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the marginal pdf can be evaluated
FRENSIE_UNIT_TEST( LineEnergyAdjointPhotonScatteringDistribution,
                   evaluateEnergyPDF )
{
  FRENSIE_CHECK_EQUAL( full_distribution->evaluateEnergyPDF( 0.5, 1.03 ), 0.0 );
  FRENSIE_CHECK_EQUAL( full_distribution->evaluateEnergyPDF( 0.5, 20.0 ), 0.0 );

  FRENSIE_CHECK_SMALL( full_distribution->evaluateEnergyPDF( Utility::PhysicalConstants::electron_rest_mass_energy, 2*Utility::PhysicalConstants::electron_rest_mass_energy ),
                               1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_distribution->evaluateEnergyPDF( Utility::PhysicalConstants::electron_rest_mass_energy, 5.0 ),
                                   0.02929028890134433363,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_distribution->evaluateEnergyPDF( Utility::PhysicalConstants::electron_rest_mass_energy, 20.0 ),
                                   0.08572937984762869779,
                                   1e-15 );

  FRENSIE_CHECK_EQUAL( full_distribution->evaluateEnergyPDF( 0.52, 1.03 ), 0.0 );
  FRENSIE_CHECK_EQUAL( full_distribution->evaluateEnergyPDF( 0.52, 20.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the joint pdf can be evaluated
FRENSIE_UNIT_TEST( LineEnergyAdjointPhotonScatteringDistribution,
                   evaluateJointPDF )
{
  FRENSIE_CHECK_EQUAL( full_distribution->evaluateJointPDF( 0.5, 1.03, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( full_distribution->evaluateJointPDF( 0.5, 1.03, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( full_distribution->evaluateJointPDF( 0.5, 1.03, 1.0 ), 0.0 );

  FRENSIE_CHECK_EQUAL( full_distribution->evaluateJointPDF( 0.5, 20.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( full_distribution->evaluateJointPDF( 0.5, 20.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( full_distribution->evaluateJointPDF( 0.5, 20.0, 1.0 ), 0.0 );

  FRENSIE_CHECK_SMALL( full_distribution->evaluateJointPDF( Utility::PhysicalConstants::electron_rest_mass_energy, 2*Utility::PhysicalConstants::electron_rest_mass_energy, -1.0 ),
                               1e-15 );
  FRENSIE_CHECK_SMALL( full_distribution->evaluateJointPDF( Utility::PhysicalConstants::electron_rest_mass_energy, 2*Utility::PhysicalConstants::electron_rest_mass_energy, 0.0 ),
                               1e-15 );
  FRENSIE_CHECK_SMALL( full_distribution->evaluateJointPDF( Utility::PhysicalConstants::electron_rest_mass_energy, 2*Utility::PhysicalConstants::electron_rest_mass_energy, 1.0 ),
                               1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( full_distribution->evaluateJointPDF( Utility::PhysicalConstants::electron_rest_mass_energy, 5.0, -1.0 ),
                                   0.01464514445067216682,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_distribution->evaluateJointPDF( Utility::PhysicalConstants::electron_rest_mass_energy, 5.0, 0.0 ),
                                   0.01464514445067216682,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_distribution->evaluateJointPDF( Utility::PhysicalConstants::electron_rest_mass_energy, 5.0, 1.0 ),
                                   0.01464514445067216682,
                                   1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( full_distribution->evaluateJointPDF( Utility::PhysicalConstants::electron_rest_mass_energy, 20.0, -1.0 ),
                                   0.04286468992381434889,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_distribution->evaluateJointPDF( Utility::PhysicalConstants::electron_rest_mass_energy, 20.0, -1.0 ),
                                   0.04286468992381434889,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_distribution->evaluateJointPDF( Utility::PhysicalConstants::electron_rest_mass_energy, 20.0, -1.0 ),
                                   0.04286468992381434889,
                                   1e-15 );

  FRENSIE_CHECK_EQUAL( full_distribution->evaluateJointPDF( 0.52, 1.03, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( full_distribution->evaluateJointPDF( 0.52, 1.03, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( full_distribution->evaluateJointPDF( 0.52, 1.03, 1.0 ), 0.0 );

  FRENSIE_CHECK_EQUAL( full_distribution->evaluateJointPDF( 0.52, 20.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( full_distribution->evaluateJointPDF( 0.52, 20.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( full_distribution->evaluateJointPDF( 0.52, 20.0, 1.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the integrated cross section can be evaluated
FRENSIE_UNIT_TEST( LineEnergyAdjointPhotonScatteringDistribution,
                   evaluateIntegratedCrossSection )
{
  FRENSIE_CHECK_EQUAL( distribution->evaluateIntegratedCrossSection( 0.5, 1e-3 ), 0.0 );
  std::cout.precision( 18 );
  std::cout << distribution->evaluateIntegratedCrossSection( Utility::PhysicalConstants::electron_rest_mass_energy, 1e-3 ) << std::endl;
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluateIntegratedCrossSection( Utility::PhysicalConstants::electron_rest_mass_energy, 1e-3 ),
                                  7.36968106381629173,
                                  1e-15 );

  FRENSIE_CHECK_EQUAL( distribution->evaluateIntegratedCrossSection( 0.52, 1e-3 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from
FRENSIE_UNIT_TEST( LineEnergyAdjointPhotonScatteringDistribution, sample )
{
  // Set the fake stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  fake_stream[3] = 0.75;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double outgoing_energy, scattering_angle_cosine;

  distribution->sample( Utility::PhysicalConstants::electron_rest_mass_energy,
                        outgoing_energy,
                        scattering_angle_cosine );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy,
                          2*Utility::PhysicalConstants::electron_rest_mass_energy,
                          1e-15 );
  FRENSIE_CHECK_SMALL( scattering_angle_cosine, 1e-15 );

  distribution->sample( Utility::PhysicalConstants::electron_rest_mass_energy,
                        outgoing_energy,
                        scattering_angle_cosine );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 20.0, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.5, 1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from
FRENSIE_UNIT_TEST( LineEnergyAdjointPhotonScatteringDistribution,
                   sample_basic )
{
  // Set the fake stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  fake_stream[3] = 0.75;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double outgoing_energy, scattering_angle_cosine;

  full_distribution->sample( outgoing_energy, scattering_angle_cosine );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy,
                          2*Utility::PhysicalConstants::electron_rest_mass_energy,
                          1e-15 );
  FRENSIE_CHECK_SMALL( scattering_angle_cosine, 1e-15 );

  full_distribution->sample( outgoing_energy, scattering_angle_cosine );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 20.0, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.5, 1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from
FRENSIE_UNIT_TEST( LineEnergyAdjointPhotonScatteringDistribution,
                   sampleAndRecordTrials )
{
  // Set the fake stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  fake_stream[3] = 0.75;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double outgoing_energy, scattering_angle_cosine;
  MonteCarlo::AdjointPhotonScatteringDistribution::Counter trials = 0u;

  distribution->sampleAndRecordTrials( Utility::PhysicalConstants::electron_rest_mass_energy,
                                       outgoing_energy,
                                       scattering_angle_cosine,
                                       trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy,
                          2*Utility::PhysicalConstants::electron_rest_mass_energy,
                          1e-15 );
  FRENSIE_CHECK_SMALL( scattering_angle_cosine, 1e-15 );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  distribution->sampleAndRecordTrials( Utility::PhysicalConstants::electron_rest_mass_energy,
                                       outgoing_energy,
                                       scattering_angle_cosine,
                                       trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 20.0, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.5, 1e-15 );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from
FRENSIE_UNIT_TEST( LineEnergyAdjointPhotonScatteringDistribution,
                   sampleAndRecordTrials_basic )
{
  // Set the fake stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  fake_stream[3] = 0.75;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double outgoing_energy, scattering_angle_cosine;
  MonteCarlo::AdjointPhotonScatteringDistribution::Counter trials = 0u;

  full_distribution->sampleAndRecordTrials( outgoing_energy,
                                            scattering_angle_cosine,
                                            trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy,
                          2*Utility::PhysicalConstants::electron_rest_mass_energy,
                          1e-15 );
  FRENSIE_CHECK_SMALL( scattering_angle_cosine, 1e-15 );
  FRENSIE_CHECK_EQUAL( trials, 1u );

  full_distribution->sampleAndRecordTrials( outgoing_energy,
                                            scattering_angle_cosine,
                                            trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 20.0, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.5, 1e-15 );
  FRENSIE_CHECK_EQUAL( trials, 2u );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that an adjoint photon can be scattered
FRENSIE_UNIT_TEST( LineEnergyAdjointPhotonScatteringDistribution,
                   scatterAdjointPhoton )
{
  MonteCarlo::AdjointPhotonState adjoint_photon( 0 );
  adjoint_photon.setEnergy( 0.5 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  // Check that a particle with energy != me will not be changed
  distribution->scatterAdjointPhoton( adjoint_photon, bank, shell_of_interaction );

  FRENSIE_CHECK_EQUAL( adjoint_photon.getEnergy(), 0.5 );
  FRENSIE_CHECK_EQUAL( adjoint_photon.getXDirection(), 0.0 );
  FRENSIE_CHECK_EQUAL( adjoint_photon.getYDirection(), 0.0 );
  FRENSIE_CHECK_EQUAL( adjoint_photon.getZDirection(), 1.0 );
  FRENSIE_CHECK_EQUAL( bank.size(), 0 );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::UNKNOWN_SUBSHELL );

  // Check that a particle with energy == me will be changed
  adjoint_photon.setEnergy( Utility::PhysicalConstants::electron_rest_mass_energy );

  // Set the fake stream
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.0;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution->scatterAdjointPhoton( adjoint_photon, bank, shell_of_interaction );

  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_photon.getEnergy(),
                          2*Utility::PhysicalConstants::electron_rest_mass_energy,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( adjoint_photon.getXDirection(), 1.0 );
  FRENSIE_CHECK_EQUAL( adjoint_photon.getYDirection(), 0.0 );
  FRENSIE_CHECK_EQUAL( adjoint_photon.getZDirection(), 0.0 );
  FRENSIE_CHECK_EQUAL( bank.size(), 0 );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::UNKNOWN_SUBSHELL );

  Utility::RandomNumberGenerator::unsetFakeStream();
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
                                        "Test Native file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create the native data file container
  Data::AdjointElectronPhotonRelaxationDataContainer
    data_container( test_native_file_name );

  // Create the adjoint pair production energy distribution
  std::shared_ptr<Utility::TabularUnivariateDistribution> energy_dist(
      new Utility::TabularDistribution<Utility::LinLin>(
               data_container.getAdjointPairProductionEnergyDistributionGrid(),
               data_container.getAdjointPairProductionEnergyDistribution() ) );

  // Get the energy dist normalization constant
  double norm_constant =
    data_container.getAdjointPairProductionEnergyDistributionNormConstant().back();

  // Create the distribution
  full_distribution.reset(
              new MonteCarlo::LineEnergyAdjointPhotonScatteringDistribution(
                         Utility::PhysicalConstants::electron_rest_mass_energy,
                         norm_constant,
                         energy_dist ) );

  distribution = full_distribution;

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstLineEnergyAdjointPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
