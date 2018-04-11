//---------------------------------------------------------------------------//
//!
//! \file   tstThompsonScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  Thompson scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>

// FRENSIE Includes
#include "MonteCarlo_ThompsonScatteringDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::PhotonScatteringDistribution>
  distribution( new MonteCarlo::ThompsonScatteringDistribution() );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( ThompsonScatteringDistribution, evaluate )
{
  double dist_value = distribution->evaluate( 0.1, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 4.989344050883251e-1, 1e-15 );

  dist_value = distribution->evaluate( 0.1, 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 2.4946720254416256e-1, 1e-15 );

  dist_value = distribution->evaluate( 0.1, -1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 4.989344050883251e-1, 1e-15 );

  dist_value = distribution->evaluate( 1.0, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 4.989344050883251e-1, 1e-15 );

  dist_value = distribution->evaluate( 1.0, 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 2.4946720254416256e-1, 1e-15 );

  dist_value = distribution->evaluate( 1.0, -1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 4.989344050883251e-1, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the distribution PDF can be evaluated
FRENSIE_UNIT_TEST( ThompsonScatteringDistribution, evaluatePDF )
{
  double pdf_value = distribution->evaluatePDF( 0.1, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.75, 1e-15 );

  pdf_value = distribution->evaluatePDF( 0.1, 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.375, 1e-15 );

  pdf_value = distribution->evaluatePDF( 0.1, -1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.75, 1e-15 );

  pdf_value = distribution->evaluatePDF( 1.0, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.75, 1e-15 );

  pdf_value = distribution->evaluatePDF( 1.0, 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.375, 1e-15 );

  pdf_value = distribution->evaluatePDF( 1.0, -1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.75, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the integrated cross section can be evaluated
FRENSIE_UNIT_TEST( ThompsonScatteringDistribution,
		   evaluateIntegratedCrossSection )
{
  double cross_section =
    distribution->evaluateIntegratedCrossSection( 0.1, 1e-16 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.652458734511002e-1, 1e-15 );

  cross_section = distribution->evaluateIntegratedCrossSection( 1.0, 1e-16 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.652458734511002e-1, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the outgoing direction can be sampled
FRENSIE_UNIT_TEST( ThompsonScatteringDistribution, sample )
{
  double outgoing_energy, scattering_angle_cosine;

  // Set up the random number stream
  std::vector<double> fake_stream( 8 );
  fake_stream[0] = 0.75;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.755;
  fake_stream[3] = 0.2;
  fake_stream[4] = 0.80;
  fake_stream[5] = 0.5;
  fake_stream[6] = 0.9;
  fake_stream[7] = 0.8;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Sample 1st term
  distribution->sample( 0.1,
			outgoing_energy,
			scattering_angle_cosine );

  FRENSIE_CHECK_EQUAL( outgoing_energy, 0.1 );
  FRENSIE_CHECK_SMALL( scattering_angle_cosine, 1e-15 );

  // Sample the 2nd term
  distribution->sample( 0.1,
			outgoing_energy,
			scattering_angle_cosine );

  FRENSIE_CHECK_EQUAL( outgoing_energy, 0.1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, -0.8434326653017492, 1e-15);

  // Sample the 2nd term
  distribution->sample( 0.1,
			outgoing_energy,
			scattering_angle_cosine );

  FRENSIE_CHECK_EQUAL( outgoing_energy, 0.1 );
  FRENSIE_CHECK_SMALL( scattering_angle_cosine, 1e-15);

  // Sample the 2nd term
  distribution->sample( 0.1,
			outgoing_energy,
			scattering_angle_cosine );

  FRENSIE_CHECK_EQUAL( outgoing_energy, 0.1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.8434326653017493, 1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that outgoing direction can be sampled and the trials can be recoreded
FRENSIE_UNIT_TEST( ThompsonScatteringDistribution,
		   sampleAndRecordTrials )
{
  double outgoing_energy, scattering_angle_cosine;
  MonteCarlo::PhotonScatteringDistribution::Counter trials = 0;

  // Set up the random number stream
  std::vector<double> fake_stream( 8 );
  fake_stream[0] = 0.75;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.755;
  fake_stream[3] = 0.2;
  fake_stream[4] = 0.80;
  fake_stream[5] = 0.5;
  fake_stream[6] = 0.9;
  fake_stream[7] = 0.8;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Sample 1st term
  distribution->sampleAndRecordTrials( 0.1,
				       outgoing_energy,
				       scattering_angle_cosine,
				       trials );

  FRENSIE_CHECK_EQUAL( outgoing_energy, 0.1 );
  FRENSIE_CHECK_SMALL( scattering_angle_cosine, 1e-15 );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  // Sample the 2nd term
  distribution->sampleAndRecordTrials( 0.1,
				       outgoing_energy,
				       scattering_angle_cosine,
				       trials );

  FRENSIE_CHECK_EQUAL( outgoing_energy, 0.1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, -0.8434326653017492, 1e-15);
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );

  // Sample the 2nd term
  distribution->sampleAndRecordTrials( 0.1,
				       outgoing_energy,
				       scattering_angle_cosine,
				       trials );

  FRENSIE_CHECK_EQUAL( outgoing_energy, 0.1 );
  FRENSIE_CHECK_SMALL( scattering_angle_cosine, 1e-15);
  FRENSIE_CHECK_EQUAL( 3.0/trials, 1.0 );

  // Sample the 2nd term
  distribution->sampleAndRecordTrials( 0.1,
				       outgoing_energy,
				       scattering_angle_cosine,
				       trials );

  FRENSIE_CHECK_EQUAL( outgoing_energy, 0.1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.8434326653017493, 1e-15 );
  FRENSIE_CHECK_EQUAL( 4.0/trials, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a photon can be randomly scattered
FRENSIE_UNIT_TEST( ThompsonScatteringDistribution, scatterPhoton )
{
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 0.1 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 12 );
  fake_stream[0] = 0.75;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.0; // rnd for azimuthal angle
  fake_stream[3] = 0.755;
  fake_stream[4] = 0.2;
  fake_stream[5] = 0.0; // rnd for azimuthal angle
  fake_stream[6] = 0.80;
  fake_stream[7] = 0.5;
  fake_stream[8] = 0.0; // rnd for azimuthal angle
  fake_stream[9] = 0.9;
  fake_stream[10] = 0.8;
  fake_stream[11] = 0.0; // rnd for azimuthal angle

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Sample 1st term
  distribution->scatterPhoton( photon, bank, shell_of_interaction );

  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 0.1 );
  FRENSIE_CHECK_SMALL( photon.getZDirection(), 1e-15 );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::UNKNOWN_SUBSHELL );

  photon.setDirection( 0.0, 0.0, 1.0 );

  // Sample the 2nd term
  distribution->scatterPhoton( photon, bank, shell_of_interaction );

  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 0.1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZDirection(), -0.8434326653017492, 1e-15 );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::UNKNOWN_SUBSHELL );

  photon.setDirection( 0.0, 0.0, 1.0 );

  // Sample the 2nd term
  distribution->scatterPhoton( photon, bank, shell_of_interaction );

  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 0.1 );
  FRENSIE_CHECK_SMALL( photon.getZDirection(), 1e-15);
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::UNKNOWN_SUBSHELL );

  photon.setDirection( 0.0, 0.0, 1.0 );

  // Sample the 2nd term
  distribution->scatterPhoton( photon, bank, shell_of_interaction );

  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 0.1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZDirection(), 0.8434326653017493, 1e-15 );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::UNKNOWN_SUBSHELL );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstThompsonScatteringDistribution.cpp
//---------------------------------------------------------------------------//

