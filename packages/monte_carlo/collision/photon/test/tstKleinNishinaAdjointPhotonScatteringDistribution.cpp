//---------------------------------------------------------------------------//
//!
//! \file   tstKleinNishinaAdjointPhotonScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  Klein-Nishina adjoint photon scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_KleinNishinaAdjointPhotonScatteringDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::AdjointPhotonScatteringDistribution> distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( KleinNishinaAdjointPhotonScatteringDistribution,
		   evaluate )
{
  // Incoming energy = 0.1 MeV
  double dist_value = distribution->evaluate( 0.1, -1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 0.5617250013852311, 1e-15 );

  dist_value = distribution->evaluate( 0.1, 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 0.2613454621535213, 1e-15 );

  dist_value = distribution->evaluate( 0.1, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 0.4989344050883251, 1e-15 );

  // Incoming energy = 1.0 MeV
  dist_value = distribution->evaluate( 1.0, 0.5145510353765 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 4.818399835538855, 1e-15 );

  dist_value = distribution->evaluate( 1.0, 0.9 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 0.4634138962142929, 1e-15 );

  dist_value = distribution->evaluate( 1.0, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 0.4989344050883251, 1e-15 );

  // Incoming energy = 10.0 MeV
  dist_value = distribution->evaluate( 10.0, 0.9744500544935 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 0.6110831116179009, 1e-15 );

  dist_value = distribution->evaluate( 10.0, 0.99 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 0.5058482673670551, 1e-15 );

  dist_value = distribution->evaluate( 10.0, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 0.4989344050883251, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the distribution pdf can be evaluated
FRENSIE_UNIT_TEST( KleinNishinaAdjointPhotonScatteringDistribution,
		   evaluatePDF )
{
  // Incoming energy = 0.1 MeV
  double pdf = distribution->evaluatePDF( 0.1, -1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 0.8005229502046525, 1e-14 );

  pdf = distribution->evaluatePDF( 0.1, 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 0.37244744291211795, 1e-14 );

  pdf = distribution->evaluatePDF( 0.1, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 0.7110391044282447, 1e-14 );

  // Incoming energy = 1.0 MeV
  pdf = distribution->evaluatePDF( 1.0, 0.5145510353765 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 12.161802488005854, 1e-15 );

  pdf = distribution->evaluatePDF( 1.0, 0.9 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.1696721875147562, 1e-15 );

  pdf = distribution->evaluatePDF( 1.0, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.2593271410147135, 1e-15 );

  // Incoming energy = 10.0 MeV
  pdf = distribution->evaluatePDF( 10.0, 0.9744500544935 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 45.41678914783313, 1e-15 );

  pdf = distribution->evaluatePDF( 10.0, 0.99 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 37.595547419041566, 1e-15 );

  pdf = distribution->evaluatePDF( 10.0, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 37.08169681616877, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the integrated cross section can be evaluated
FRENSIE_UNIT_TEST( KleinNishinaAdjointPhotonScatteringDistribution,
		   evaluateIntegratedCrossSection )
{
  double cross_section =
    distribution->evaluateIntegratedCrossSection( 0.1, 1e-6 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.7016975606278707, 1e-14 );

  cross_section = distribution->evaluateIntegratedCrossSection( 1.0, 1e-6 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.39619125867985694, 1e-15 );

  cross_section = distribution->evaluateIntegratedCrossSection( 10.0, 1e-6 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.013455004703850935, 1e-15 );

  cross_section = distribution->evaluateIntegratedCrossSection( 20.0, 1e-6 );

  FRENSIE_CHECK_SMALL( cross_section, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from
FRENSIE_UNIT_TEST( KleinNishinaAdjointPhotonScatteringDistribution,
                   sample_two_branch )
{
  double outgoing_energy, scattering_angle_cosine;
  MonteCarlo::AdjointPhotonScatteringDistribution::Counter trials = 0;

  // Set the fake stream
  std::vector<double> fake_stream( 12 );
  fake_stream[0] = 0.1; // branch 1
  fake_stream[1] = 0.5; // select x = 0.9
  fake_stream[2] = 0.45; // reject
  fake_stream[3] = 0.11; // branch 1
  fake_stream[4] = 0.75; // select x = 0.95
  fake_stream[5] = 0.21; // accept
  fake_stream[6] = 0.12; // branch 2
  fake_stream[7] = 0.25; // select x = 0.85
  fake_stream[8] = 0.55; // reject
  fake_stream[9] = 0.12; // branch 2
  fake_stream[10] = 0.5; // select x = 0.9
  fake_stream[11] = 0.44; // accept

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution->sample(
		    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
		    outgoing_energy,
		    scattering_angle_cosine );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 0.053789358961052636, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.5, 1e-15 );

  distribution->sample(
		    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
		    outgoing_energy,
		    scattering_angle_cosine );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 0.05677765668111111, 1e-15 );
  FRENSIE_CHECK_SMALL( scattering_angle_cosine, 1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from
FRENSIE_UNIT_TEST( KleinNishinaAdjointPhotonScatteringDistribution,
                   sample_three_branch_inv )
{
  std::unique_ptr<MonteCarlo::AdjointPhotonScatteringDistribution>
    local_distribution = std::make_unique<MonteCarlo::KleinNishinaAdjointPhotonScatteringDistribution>( 20.0, MonteCarlo::THREE_BRANCH_INVERSE_MIXED_ADJOINT_KN_SAMPLING );
  
  double outgoing_energy, scattering_angle_cosine;

  // Set the fake stream
  std::vector<double> fake_stream( 12 );
  fake_stream[0] = 0.15; // branch 1
  fake_stream[1] = 0.4721647344828152; // select x = 0.9
  fake_stream[2] = 0.55; // reject
  fake_stream[3] = 0.15; // branch 1
  fake_stream[4] = 0.22986680137273696; // select x = 0.95
  fake_stream[5] = 0.245; // accept
  fake_stream[6] = 0.77; // branch 2
  fake_stream[7] = 0.5; // select x = 0.8124038404635961
  fake_stream[8] = 0.78; // branch 3
  fake_stream[9] = 0.1; // select x = 0.8071682233277445
  fake_stream[10] = 0.99; // branch 3
  fake_stream[11] = 0.5; // select x = 0.9000009536743164

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  local_distribution->sample(
		    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
		    outgoing_energy,
		    scattering_angle_cosine );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 0.053789358961052636, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.5, 1e-15 );

  local_distribution->sample(
		    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
		    outgoing_energy,
		    scattering_angle_cosine );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 0.05643038946823926, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.0553851381374173, 1e-15);

  local_distribution->sample(
		    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
		    outgoing_energy,
		    scattering_angle_cosine );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 0.06330760990853734, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, -0.9283177667225548, 1e-15);

  local_distribution->sample(
		    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
		    outgoing_energy,
		    scattering_angle_cosine );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 0.056777596517404945, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine,
			  9.536743164284545e-06,
			  1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from and trials can be recorded
FRENSIE_UNIT_TEST( KleinNishinaAdjointPhotonScatteringDistribution,
		   sampleAndRecordTrials )
{
  double outgoing_energy, scattering_angle_cosine;
  MonteCarlo::AdjointPhotonScatteringDistribution::Counter trials = 0;

  // Set the fake stream
  std::vector<double> fake_stream( 12 );
  fake_stream[0] = 0.1; // branch 1
  fake_stream[1] = 0.5; // select x = 0.9
  fake_stream[2] = 0.45; // reject
  fake_stream[3] = 0.11; // branch 1
  fake_stream[4] = 0.75; // select x = 0.95
  fake_stream[5] = 0.21; // accept
  fake_stream[6] = 0.12; // branch 2
  fake_stream[7] = 0.25; // select x = 0.85
  fake_stream[8] = 0.55; // reject
  fake_stream[9] = 0.12; // branch 2
  fake_stream[10] = 0.5; // select x = 0.9
  fake_stream[11] = 0.44; // accept

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution->sampleAndRecordTrials(
		    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
		    outgoing_energy,
		    scattering_angle_cosine,
                    trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 0.053789358961052636, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.5, 1e-15 );
  FRENSIE_CHECK_EQUAL( trials, 2 );

  distribution->sampleAndRecordTrials(
		    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
		    outgoing_energy,
		    scattering_angle_cosine,
                    trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 0.05677765668111111, 1e-15 );
  FRENSIE_CHECK_SMALL( scattering_angle_cosine, 1e-15 );
  FRENSIE_CHECK_EQUAL( trials, 4 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that an adjoint photon can be scattered
FRENSIE_UNIT_TEST( KleinNishinaAdjointPhotonScatteringDistribution,
		   scatterAdjointPhoton )
{
  MonteCarlo::AdjointPhotonState adjoint_photon( 0 );
  adjoint_photon.setEnergy(
		  Utility::PhysicalConstants::electron_rest_mass_energy/10.0 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  // Set the fake stream
  std::vector<double> fake_stream( 7 );
  fake_stream[0] = 0.1; // branch 1
  fake_stream[1] = 0.5; // select x = 0.9
  fake_stream[2] = 0.45; // reject
  fake_stream[3] = 0.11; // branch 1
  fake_stream[4] = 0.75; // select x = 0.95
  fake_stream[5] = 0.21; // accept
  fake_stream[6] = 0.0; // azimuthal angle = 0.0

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution->scatterAdjointPhoton( adjoint_photon,
				      bank,
				      shell_of_interaction );

  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_photon.getEnergy(),
			  0.053789358961052636,
			  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_photon.getZDirection(), 0.5, 1e-15 );
  FRENSIE_CHECK_EQUAL( bank.size(), 0 );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::UNKNOWN_SUBSHELL );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // Generate a probe with energy 0.08
  adjoint_photon.setEnergy( 0.07 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );

  distribution->scatterAdjointPhoton( adjoint_photon,
				      bank,
				      shell_of_interaction );

  FRENSIE_CHECK_EQUAL( bank.size(), 1 );
  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(), 0.08 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getWeight(),
			  29.993834199062107,
			  1e-14 );

  bank.pop();

  // Generate a probe with energy mec^2
  adjoint_photon.setEnergy( 0.19 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );

  distribution->scatterAdjointPhoton( adjoint_photon,
				      bank,
				      shell_of_interaction );

  FRENSIE_CHECK_EQUAL( bank.size(), 1 );
  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(),
		       Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getWeight(),
			  1.3851251716307225,
			  1e-15 );

  bank.pop();

  // Generate two probes
  adjoint_photon.setEnergy( 0.3 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );

  distribution->scatterAdjointPhoton( adjoint_photon,
				      bank,
				      shell_of_interaction );

  FRENSIE_CHECK_EQUAL( bank.size(), 2 );
  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(),
		       Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getWeight(),
			  0.3987875470381571,
			  1e-15 );

  bank.pop();

  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(), 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getWeight(),
			  0.20172576376840526,
			  1e-15 );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create the scattering distribution
  std::shared_ptr<std::vector<double> >
    critical_line_energies( new std::vector<double>(3) );

  (*critical_line_energies)[0] = 0.08;
  (*critical_line_energies)[1] =
    Utility::PhysicalConstants::electron_rest_mass_energy;
  (*critical_line_energies)[2] = 1.0;

  std::shared_ptr<MonteCarlo::IncoherentAdjointPhotonScatteringDistribution>
    incoherent_base_dist(
	      new MonteCarlo::KleinNishinaAdjointPhotonScatteringDistribution(
								     20.0 ) );

  incoherent_base_dist->setCriticalLineEnergies( critical_line_energies );

  distribution = incoherent_base_dist;

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstKleinNishinaAdjointPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
