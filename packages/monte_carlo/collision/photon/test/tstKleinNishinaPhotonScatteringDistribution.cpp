//---------------------------------------------------------------------------//
//!
//! \file   tstKleinNishinaPhotonScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  Klein-Nishina photon scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>

// FRENSIE Includes
#include "MonteCarlo_KleinNishinaPhotonScatteringDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::PhotonScatteringDistribution>
  distribution( new MonteCarlo::KleinNishinaPhotonScatteringDistribution() );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that distribution can be evaluated
FRENSIE_UNIT_TEST( KleinNishinaPhotonScatteringDistribution, evaluate )
{
  double dist_value = distribution->evaluate(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 4.9893440508834e-1, 1e-12 );

  dist_value = distribution->evaluate(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 -1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 9.2395260201544e-2, 1e-12 );

  dist_value = distribution->evaluate( 1.0, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 4.989344050883251e-1, 1e-15 );

  dist_value = distribution->evaluate( 1.0, 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 6.54837903834309e-2, 1e-15 );

  dist_value = distribution->evaluate( 1.0, -1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 5.287012135320711e-2, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the distribution PDF can be evaluated
FRENSIE_UNIT_TEST( KleinNishinaPhotonScatteringDistribution, evaluatePDF )
{
  double pdf_value = distribution->evaluatePDF(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 1.7412387289976, 1e-12 );

  pdf_value = distribution->evaluatePDF(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 -1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.32245161648103, 1e-12 );

  pdf_value = distribution->evaluatePDF( 1.0, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 2.3622907264473127, 1e-15 );

  pdf_value = distribution->evaluatePDF( 1.0, 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.3100442646924977, 1e-15 );

  pdf_value = distribution->evaluatePDF( 1.0, -1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.2503226799056189, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the integrated cross section can be evaluated
FRENSIE_UNIT_TEST( KleinNishinaPhotonScatteringDistribution,
		   evaluateIntegratedCrossSection )
{
  double cross_section = distribution->evaluateIntegratedCrossSection(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 1e-6 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.8653991941448027e-1, 1e-15 );

  cross_section = distribution->evaluateIntegratedCrossSection( 1.0, 1e-6 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.1120787526380407e-1, 1e-15 );

  cross_section = distribution->evaluateIntegratedCrossSection( 20.0, 1e-6 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.02498575770817e-2, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the outgoing energy and direction can be sampled
FRENSIE_UNIT_TEST( KleinNishinaPhotonScatteringDistribution, sample )
{
  double outgoing_energy, scattering_angle_cosine;

  // Left branch of Kahn's method
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.27;
  fake_stream[1] = 0.25;
  fake_stream[2] = 0.90; // reject
  fake_stream[3] = 0.10;
  fake_stream[4] = 0.50;
  fake_stream[5] = 0.999;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution->sample( Utility::PhysicalConstants::electron_rest_mass_energy,
			outgoing_energy,
			scattering_angle_cosine );

  FRENSIE_CHECK_FLOATING_EQUALITY(
		       outgoing_energy,
		       Utility::PhysicalConstants::electron_rest_mass_energy/2,
		       1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.0, 1e-15 );

  // Right branch of Kahn's method
  fake_stream[0] = 0.273;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.459; // reject
  fake_stream[3] = 0.80;
  fake_stream[4] = 0.25;
  fake_stream[5] = 0.25;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution->sample( Utility::PhysicalConstants::electron_rest_mass_energy,
			outgoing_energy,
			scattering_angle_cosine );

  FRENSIE_CHECK_FLOATING_EQUALITY(
		       outgoing_energy,
		       Utility::PhysicalConstants::electron_rest_mass_energy/2,
		       1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.0, 1e-15 );

  // Koblinger's Method
  fake_stream.resize( 8 );
  fake_stream[0] = 0.120;
  fake_stream[1] = 0.2;
  fake_stream[2] = 0.698;
  fake_stream[3] = 0.4;
  fake_stream[4] = 0.818;
  fake_stream[5] = 0.6;
  fake_stream[6] = 0.90;
  fake_stream[7] = 0.8;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Sample 1st term
  distribution->sample( 3.1,
			outgoing_energy,
			scattering_angle_cosine );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 0.9046816718380433, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.6, 1e-15 );

  // Sample the 2nd term
  distribution->sample( 3.1,
			outgoing_energy,
			scattering_angle_cosine );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 1.1066615373683126, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine,
			  0.7030902148167004,
			  1e-15 );

  // Sample the 3rd term
  distribution->sample( 3.1,
			outgoing_energy,
			scattering_angle_cosine );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 1.9544179334621479, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine,
			  0.9033799968311882,
			  1e-15 );

  // Sample the 4th term
  distribution->sample( 3.1,
			outgoing_energy,
			scattering_angle_cosine );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 1.4023457957281122, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine,
			  0.8004496947064347,
			  1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the outgoing energy and direction can be sampled and the trials
// can be recorded
FRENSIE_UNIT_TEST( KleinNishinaPhotonScatteringDistribution,
		   sampleAndRecordTrials )
{
  double outgoing_energy, scattering_angle_cosine;
  MonteCarlo::KleinNishinaPhotonScatteringDistribution::Counter trials = 0;

  // Left branch of Kahn's method
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.27;
  fake_stream[1] = 0.25;
  fake_stream[2] = 0.90; // reject
  fake_stream[3] = 0.10;
  fake_stream[4] = 0.50;
  fake_stream[5] = 0.999;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution->sampleAndRecordTrials(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 outgoing_energy,
			 scattering_angle_cosine,
			 trials );

  FRENSIE_CHECK_FLOATING_EQUALITY(
		       outgoing_energy,
		       Utility::PhysicalConstants::electron_rest_mass_energy/2,
		       1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.0, 1e-15 );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 0.5 );

  // Right branch of Kahn's method
  fake_stream[0] = 0.273;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.459; // reject
  fake_stream[3] = 0.80;
  fake_stream[4] = 0.25;
  fake_stream[5] = 0.25;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution->sampleAndRecordTrials(
			Utility::PhysicalConstants::electron_rest_mass_energy,
			outgoing_energy,
			scattering_angle_cosine,
			trials );

  FRENSIE_CHECK_FLOATING_EQUALITY(
		       outgoing_energy,
		       Utility::PhysicalConstants::electron_rest_mass_energy/2,
		       1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.0, 1e-15 );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 0.5 );

  // Koblinger's Method
  fake_stream.resize( 8 );
  fake_stream[0] = 0.120;
  fake_stream[1] = 0.2;
  fake_stream[2] = 0.698;
  fake_stream[3] = 0.4;
  fake_stream[4] = 0.818;
  fake_stream[5] = 0.6;
  fake_stream[6] = 0.90;
  fake_stream[7] = 0.8;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0;

  // Sample 1st term
  distribution->sampleAndRecordTrials( 3.1,
				       outgoing_energy,
				       scattering_angle_cosine,
				       trials );


  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 0.9046816718380433, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.6, 1e-15 );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  // Sample the 2nd term
  distribution->sampleAndRecordTrials( 3.1,
				       outgoing_energy,
				       scattering_angle_cosine,
				       trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 1.1066615373683126, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine,
			  0.7030902148167004,
			  1e-15 );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );

  // Sample the 3rd term
  distribution->sampleAndRecordTrials( 3.1,
				       outgoing_energy,
				       scattering_angle_cosine,
				       trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 1.9544179334621479, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine,
			  0.9033799968311882,
			  1e-15 );
  FRENSIE_CHECK_EQUAL( 3.0/trials, 1.0 );

  // Sample the 4th term
  distribution->sampleAndRecordTrials( 3.1,
				       outgoing_energy,
				       scattering_angle_cosine,
				       trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 1.4023457957281122, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine,
			  0.8004496947064347,
			  1e-15 );
  FRENSIE_CHECK_EQUAL( 4.0/trials, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a photon can be randomly scattered
FRENSIE_UNIT_TEST( KleinNishinaPhotonScatteringDistribution, scatterPhoton )
{
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( Utility::PhysicalConstants::electron_rest_mass_energy );
  photon.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  // Left branch of Kahn's method
  std::vector<double> fake_stream( 7 );
  fake_stream[0] = 0.27;
  fake_stream[1] = 0.25;
  fake_stream[2] = 0.90; // reject
  fake_stream[3] = 0.10;
  fake_stream[4] = 0.50;
  fake_stream[5] = 0.999;
  fake_stream[6] = 0.0;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution->scatterPhoton( photon, bank, shell_of_interaction );

  FRENSIE_CHECK_FLOATING_EQUALITY(
		       photon.getEnergy(),
		       Utility::PhysicalConstants::electron_rest_mass_energy/2,
		       1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZDirection(), 0.0, 1e-15 );
  FRENSIE_CHECK_EQUAL( bank.size(), 1 );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::UNKNOWN_SUBSHELL );

  bank.pop();

  // Right branch of Kahn's method
  fake_stream[0] = 0.273;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.459; // reject
  fake_stream[3] = 0.80;
  fake_stream[4] = 0.25;
  fake_stream[5] = 0.25;
  fake_stream[6] = 0.0; // azimuthal angle

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  photon.setEnergy( Utility::PhysicalConstants::electron_rest_mass_energy );
  photon.setDirection( 0.0, 0.0, 1.0 );

  distribution->scatterPhoton( photon, bank, shell_of_interaction );

  FRENSIE_CHECK_FLOATING_EQUALITY(
		       photon.getEnergy(),
		       Utility::PhysicalConstants::electron_rest_mass_energy/2,
		       1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZDirection(), 0.0, 1e-15 );
  FRENSIE_CHECK_EQUAL( bank.size(), 1 );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::UNKNOWN_SUBSHELL );

  bank.pop();

  // Koblinger's Method
  fake_stream.resize( 12 );
  fake_stream[0] = 0.120;
  fake_stream[1] = 0.2;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.698;
  fake_stream[4] = 0.4;
  fake_stream[5] = 0.0;
  fake_stream[6] = 0.818;
  fake_stream[7] = 0.6;
  fake_stream[8] = 0.0;
  fake_stream[9] = 0.90;
  fake_stream[10] = 0.8;
  fake_stream[11] = 0.0;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  photon.setEnergy( 3.1 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  // Sample 1st term
  distribution->scatterPhoton( photon, bank, shell_of_interaction );

  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getEnergy(), 0.9046816718380433, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZDirection(), 0.6, 1e-15 );
  FRENSIE_CHECK_EQUAL( bank.size(), 1 );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::UNKNOWN_SUBSHELL );

  bank.pop();
  
  photon.setEnergy( 3.1 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  // Sample the 2nd term
  distribution->scatterPhoton( photon, bank, shell_of_interaction );

  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getEnergy(), 1.1066615373683126, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZDirection(),
			  0.7030902148167004,
			  1e-15 );
  FRENSIE_CHECK_EQUAL( bank.size(), 1 );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::UNKNOWN_SUBSHELL );

  bank.pop();
  
  photon.setEnergy( 3.1 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  // Sample the 3rd term
  distribution->scatterPhoton( photon, bank, shell_of_interaction );

  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getEnergy(), 1.9544179334621479, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZDirection(),
			  0.9033799968311882,
			  1e-15 );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::UNKNOWN_SUBSHELL );

  bank.pop();

  photon.setEnergy( 3.1 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  // Sample the 4th term
  distribution->scatterPhoton( photon, bank, shell_of_interaction );

  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getEnergy(), 1.4023457957281122, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZDirection(),
			  0.8004496947064347,
			  1e-15 );
  FRENSIE_CHECK_EQUAL( bank.size(), 1 );
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
// end tstKleinNishinaPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
