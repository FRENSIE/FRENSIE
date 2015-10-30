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
  
// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_UnitTestHarnessExtensions.hpp"
#include "MonteCarlo_ThompsonScatteringDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::PhotonScatteringDistribution>
  distribution( new MonteCarlo::ThompsonScatteringDistribution() );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( ThompsonScatteringDistribution, evaluate )
{
  double dist_value = distribution->evaluate( 0.1, 1.0 );

  TEST_FLOATING_EQUALITY( dist_value, 4.989344050883251e-1, 1e-15 );

  dist_value = distribution->evaluate( 0.1, 0.0 );

  TEST_FLOATING_EQUALITY( dist_value, 2.4946720254416256e-1, 1e-15 );

  dist_value = distribution->evaluate( 0.1, -1.0 );

  TEST_FLOATING_EQUALITY( dist_value, 4.989344050883251e-1, 1e-15 );

  dist_value = distribution->evaluate( 1.0, 1.0 );

  TEST_FLOATING_EQUALITY( dist_value, 4.989344050883251e-1, 1e-15 );

  dist_value = distribution->evaluate( 1.0, 0.0 );

  TEST_FLOATING_EQUALITY( dist_value, 2.4946720254416256e-1, 1e-15 );

  dist_value = distribution->evaluate( 1.0, -1.0 );

  TEST_FLOATING_EQUALITY( dist_value, 4.989344050883251e-1, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the distribution PDF can be evaluated
TEUCHOS_UNIT_TEST( ThompsonScatteringDistribution, evaluatePDF )
{
  double pdf_value = distribution->evaluatePDF( 0.1, 1.0 );

  TEST_FLOATING_EQUALITY( pdf_value, 0.75, 1e-15 );

  pdf_value = distribution->evaluatePDF( 0.1, 0.0 );

  TEST_FLOATING_EQUALITY( pdf_value, 0.375, 1e-15 );

  pdf_value = distribution->evaluatePDF( 0.1, -1.0 );

  TEST_FLOATING_EQUALITY( pdf_value, 0.75, 1e-15 );

  pdf_value = distribution->evaluatePDF( 1.0, 1.0 );

  TEST_FLOATING_EQUALITY( pdf_value, 0.75, 1e-15 );

  pdf_value = distribution->evaluatePDF( 1.0, 0.0 );

  TEST_FLOATING_EQUALITY( pdf_value, 0.375, 1e-15 );

  pdf_value = distribution->evaluatePDF( 1.0, -1.0 );

  TEST_FLOATING_EQUALITY( pdf_value, 0.75, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the integrated cross section can be evaluated
TEUCHOS_UNIT_TEST( ThompsonScatteringDistribution, 
		   evaluateIntegratedCrossSection )
{
  double cross_section = 
    distribution->evaluateIntegratedCrossSection( 0.1, 1e-16 );

  TEST_FLOATING_EQUALITY( cross_section, 6.652458734511002e-1, 1e-15 );

  cross_section = distribution->evaluateIntegratedCrossSection( 1.0, 1e-16 );

  TEST_FLOATING_EQUALITY( cross_section, 6.652458734511002e-1, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the outgoing direction can be sampled
TEUCHOS_UNIT_TEST( ThompsonScatteringDistribution, sample )
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

  TEST_EQUALITY_CONST( outgoing_energy, 0.1 );
  UTILITY_TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.0, 1e-15 );
  
  // Sample the 2nd term
  distribution->sample( 0.1,
			outgoing_energy,
			scattering_angle_cosine );

  TEST_EQUALITY_CONST( outgoing_energy, 0.1 );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -0.8434326653017492, 1e-15);
  
  // Sample the 2nd term
  distribution->sample( 0.1,
			outgoing_energy,
			scattering_angle_cosine );

  TEST_EQUALITY_CONST( outgoing_energy, 0.1 );
  UTILITY_TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.0, 1e-15);
  
  // Sample the 2nd term
  distribution->sample( 0.1,
			outgoing_energy,
			scattering_angle_cosine );

  TEST_EQUALITY_CONST( outgoing_energy, 0.1 );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.8434326653017493, 1e-15 );
  
  Utility::RandomNumberGenerator::unsetFakeStream();
}
	
//---------------------------------------------------------------------------//
// Check that outgoing direction can be sampled and the trials can be recoreded
TEUCHOS_UNIT_TEST( ThompsonScatteringDistribution, 
		   sampleAndRecordTrials )   
{
  double outgoing_energy, scattering_angle_cosine;
  unsigned trials = 0;

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

  TEST_EQUALITY_CONST( outgoing_energy, 0.1 );
  UTILITY_TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.0, 1e-15 );
  TEST_EQUALITY_CONST( 1.0/trials, 1.0 );

  // Sample the 2nd term
  distribution->sampleAndRecordTrials( 0.1,
				       outgoing_energy,
				       scattering_angle_cosine,
				       trials );

  TEST_EQUALITY_CONST( outgoing_energy, 0.1 );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -0.8434326653017492, 1e-15);
  TEST_EQUALITY_CONST( 2.0/trials, 1.0 );

  // Sample the 2nd term
  distribution->sampleAndRecordTrials( 0.1,
				       outgoing_energy,
				       scattering_angle_cosine,
				       trials );

  TEST_EQUALITY_CONST( outgoing_energy, 0.1 );
  UTILITY_TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.0, 1e-15);
  TEST_EQUALITY_CONST( 3.0/trials, 1.0 );

  // Sample the 2nd term
  distribution->sampleAndRecordTrials( 0.1,
				       outgoing_energy,
				       scattering_angle_cosine,
				       trials );

  TEST_EQUALITY_CONST( outgoing_energy, 0.1 );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.8434326653017493, 1e-15 );
  TEST_EQUALITY_CONST( 4.0/trials, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a photon can be randomly scattered
TEUCHOS_UNIT_TEST( ThompsonScatteringDistribution, scatterPhoton )
{
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 0.1 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  MonteCarlo::SubshellType shell_of_interaction;

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

  TEST_EQUALITY_CONST( photon.getEnergy(), 0.1 );
  UTILITY_TEST_FLOATING_EQUALITY( photon.getZDirection(), 0.0, 1e-15 );
  TEST_EQUALITY_CONST( shell_of_interaction, MonteCarlo::UNKNOWN_SUBSHELL );

  photon.setDirection( 0.0, 0.0, 1.0 );

  // Sample the 2nd term
  distribution->scatterPhoton( photon, bank, shell_of_interaction );

  TEST_EQUALITY_CONST( photon.getEnergy(), 0.1 );
  TEST_FLOATING_EQUALITY( photon.getZDirection(), -0.8434326653017492, 1e-15 );
  TEST_EQUALITY_CONST( shell_of_interaction, MonteCarlo::UNKNOWN_SUBSHELL );
  
  photon.setDirection( 0.0, 0.0, 1.0 );

  // Sample the 2nd term
  distribution->scatterPhoton( photon, bank, shell_of_interaction );

  TEST_EQUALITY_CONST( photon.getEnergy(), 0.1 );
  UTILITY_TEST_FLOATING_EQUALITY( photon.getZDirection(), 0.0, 1e-15);
  TEST_EQUALITY_CONST( shell_of_interaction, MonteCarlo::UNKNOWN_SUBSHELL );

  photon.setDirection( 0.0, 0.0, 1.0 );

  // Sample the 2nd term
  distribution->scatterPhoton( photon, bank, shell_of_interaction );

  TEST_EQUALITY_CONST( photon.getEnergy(), 0.1 );
  TEST_FLOATING_EQUALITY( photon.getZDirection(), 0.8434326653017493, 1e-15 );
  TEST_EQUALITY_CONST( shell_of_interaction, MonteCarlo::UNKNOWN_SUBSHELL );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();

  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );
}

//---------------------------------------------------------------------------//
// end tstThompsonScatteringDistribution.cpp
//---------------------------------------------------------------------------//

