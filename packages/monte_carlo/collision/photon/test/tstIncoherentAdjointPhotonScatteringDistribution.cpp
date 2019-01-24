//---------------------------------------------------------------------------//
//!
//! \file   tstIncoherentAdjointPhotonScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  Incoherent adjoint photon scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>
#include <iterator>

// FRENSIE Includes
#include "MonteCarlo_IncoherentAdjointPhotonScatteringDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Structs
//---------------------------------------------------------------------------//
class TestIncoherentAdjointPhotonScatteringDistribution : public MonteCarlo::IncoherentAdjointPhotonScatteringDistribution
{
public:

  // Constructor
  TestIncoherentAdjointPhotonScatteringDistribution(
              const double max_energy,
              const MonteCarlo::AdjointKleinNishinaSamplingType sampling_type =
              MonteCarlo::TWO_BRANCH_REJECTION_ADJOINT_KN_SAMPLING )
    : MonteCarlo::IncoherentAdjointPhotonScatteringDistribution( max_energy, sampling_type )
  { /* ... */ }

  // Destructor
  ~TestIncoherentAdjointPhotonScatteringDistribution()
  { /* ... */ }

  // Evaluate the distribution
  double evaluate( const double incoming_energy,
		   const double max_energy,
		   const double scattering_angle_cosine ) const override
  {
    return 0.0;
  }

  //! Evaluate the integrated cross section (b)
  double evaluateIntegratedCrossSectionImpl( const double incoming_energy,
                                             const double max_energy,
                                             const double precision ) const override
  {
    return 1.0;
  }

  // Sample an outgoing energy and direction from the distribution
  void sample( const double incoming_energy,
	       double& outgoing_energy,
	       double& scattering_angle_cosine ) const override
  { /* ... */ }

  // Sample an outgoing energy and direction and record the number of trials
  void sampleAndRecordTrials( const double incoming_energy,
			      double& outgoing_energy,
			      double& scattering_angle_cosine,
			      MonteCarlo::AdjointPhotonScatteringDistribution::Counter& trials ) const override
  { /* ... */ }

  // Randomly scatter the photon and return the shell that was interacted with
  void scatterAdjointPhoton( MonteCarlo::AdjointPhotonState& adjoint_photon,
			     MonteCarlo::ParticleBank& bank,
			     Data::SubshellType& shell_of_interaction ) const override
  { /* ... */ }

  using MonteCarlo::IncoherentAdjointPhotonScatteringDistribution::LineEnergyIterator;
  using MonteCarlo::IncoherentAdjointPhotonScatteringDistribution::evaluateAdjointKleinNishinaDist;
  using MonteCarlo::IncoherentAdjointPhotonScatteringDistribution::sampleAndRecordTrialsAdjointKleinNishina;
  using MonteCarlo::IncoherentAdjointPhotonScatteringDistribution::isEnergyBelowScatteringWindow;
  using MonteCarlo::IncoherentAdjointPhotonScatteringDistribution::isEnergyAboveScatteringWindow;
  using MonteCarlo::IncoherentAdjointPhotonScatteringDistribution::isEnergyInScatteringWindow;
  using MonteCarlo::IncoherentAdjointPhotonScatteringDistribution::getCriticalLineEnergiesInScatteringWindow;
};

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<TestIncoherentAdjointPhotonScatteringDistribution> distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the max energy can be returned
FRENSIE_UNIT_TEST( IncoherentAdjointPhotonScatteringDistribution,
		   getMaxEnergy )
{
  FRENSIE_CHECK_EQUAL( distribution->getMaxEnergy(), 20.0 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint Klein-Nishina distribution can be evaluated
FRENSIE_UNIT_TEST( IncoherentAdjointPhotonScatteringDistribution,
		   evaluateAdjointKleinNishinaDist )
{
  double dist_value =
    distribution->evaluateAdjointKleinNishinaDist( 0.1, 20.0, -1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 0.5617250013852311, 1e-15 );

  dist_value = distribution->evaluateAdjointKleinNishinaDist( 0.1, 20.0, 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 0.2613454621535213, 1e-15 );

  dist_value = distribution->evaluateAdjointKleinNishinaDist( 0.1, 20.0, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 0.4989344050883251, 1e-15 );

  dist_value =
    distribution->evaluateAdjointKleinNishinaDist( 1.0, 20.0, 0.5145510353765);

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 4.818399835538855, 1e-15 );

  dist_value = distribution->evaluateAdjointKleinNishinaDist( 1.0, 20.0, 0.9 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 0.4634138962142929, 1e-15 );

  dist_value = distribution->evaluateAdjointKleinNishinaDist( 1.0, 20.0, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 0.4989344050883251, 1e-15 );

  dist_value =
    distribution->evaluateAdjointKleinNishinaDist(10.0, 20.0, 0.9744500544935);

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 0.6110831116179009, 1e-15 );

  dist_value = distribution->evaluateAdjointKleinNishinaDist(10.0, 20.0, 0.99);

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 0.5058482673670551, 1e-15 );

  dist_value = distribution->evaluateAdjointKleinNishinaDist( 10.0, 20.0, 1.0);

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 0.4989344050883251, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint Klein-Nishina distribution can be evaluated
FRENSIE_UNIT_TEST( IncoherentAdjointPhotonScatteringDistribution,
		   sampleAndRecordTrialsAdjointKleinNishina_two_branch )
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

  distribution->sampleAndRecordTrialsAdjointKleinNishina(
		    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
		    outgoing_energy,
		    scattering_angle_cosine,
		    trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 0.053789358961052636, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.5, 1e-15 );
  FRENSIE_CHECK_EQUAL( trials, 2 );

  distribution->sampleAndRecordTrialsAdjointKleinNishina(
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
// Check that the adjoint Klein-Nishina distribution can be evaluated
FRENSIE_UNIT_TEST( IncoherentAdjointPhotonScatteringDistribution,
		   sampleAndRecordTrialsAdjointKleinNishina_three_branch_inv )
{
  std::unique_ptr<TestIncoherentAdjointPhotonScatteringDistribution>
    local_distribution = std::make_unique<TestIncoherentAdjointPhotonScatteringDistribution>( 20.0, MonteCarlo::THREE_BRANCH_INVERSE_MIXED_ADJOINT_KN_SAMPLING );
  
  double outgoing_energy, scattering_angle_cosine;
  MonteCarlo::AdjointPhotonScatteringDistribution::Counter trials = 0;

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

  local_distribution->sampleAndRecordTrialsAdjointKleinNishina(
		    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
		    outgoing_energy,
		    scattering_angle_cosine,
		    trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 0.053789358961052636, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.5, 1e-15 );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 0.5 );

  local_distribution->sampleAndRecordTrialsAdjointKleinNishina(
        	    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
        	    outgoing_energy,
        	    scattering_angle_cosine,
        	    trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 0.05643038946823926, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.0553851381374173, 1e-15);
  FRENSIE_CHECK_EQUAL( 2.0/trials, 2.0/3.0 );

  local_distribution->sampleAndRecordTrialsAdjointKleinNishina(
        	    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
        	    outgoing_energy,
        	    scattering_angle_cosine,
        	    trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 0.06330760990853734, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, -0.9283177667225548, 1e-15);
  FRENSIE_CHECK_EQUAL( 3.0/trials, 0.75 );

  local_distribution->sampleAndRecordTrialsAdjointKleinNishina(
        	    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
        	    outgoing_energy,
        	    scattering_angle_cosine,
        	    trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 0.056777596517404945, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine,
                                   9.536743164284545e-06,
                                   1e-15 );
  FRENSIE_CHECK_EQUAL( 4.0/trials, 0.8 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the adjoint Klein-Nishina distribution can be evaluated
FRENSIE_UNIT_TEST( IncoherentAdjointPhotonScatteringDistribution,
		   sampleAndRecordTrialsAdjointKleinNishina_three_branch_lin )
{
  std::unique_ptr<TestIncoherentAdjointPhotonScatteringDistribution>
    local_distribution = std::make_unique<TestIncoherentAdjointPhotonScatteringDistribution>( 20.0, MonteCarlo::THREE_BRANCH_LIN_MIXED_ADJOINT_KN_SAMPLING );
  
  double outgoing_energy, scattering_angle_cosine;
  MonteCarlo::AdjointPhotonScatteringDistribution::Counter trials = 0;

  // Set the fake stream
  std::vector<double> fake_stream( 12 );
  fake_stream[0] = 0.09; // branch 1
  fake_stream[1] = 0.25; // select x = 0.9
  fake_stream[2] = 0.89; // reject
  fake_stream[3] = 0.09; // branch 1
  fake_stream[4] = 0.0625; // select x = 0.95
  fake_stream[5] = 0.842; // accept
  fake_stream[6] = 0.75; // branch 2
  fake_stream[7] = 0.5; // select x = 0.8124038404635961
  fake_stream[8] = 0.76; // branch 3
  fake_stream[9] = 0.1; // select x = 0.8071682233277445
  fake_stream[10] = 0.99; // branch 3
  fake_stream[11] = 0.5; // select x = 0.9000009536743164

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  local_distribution->sampleAndRecordTrialsAdjointKleinNishina(
		    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
		    outgoing_energy,
		    scattering_angle_cosine,
		    trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 0.053789358961052636, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.5, 1e-15 );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 0.5 );

  local_distribution->sampleAndRecordTrialsAdjointKleinNishina(
        	    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
        	    outgoing_energy,
        	    scattering_angle_cosine,
        	    trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 5.643038946823925733e-02, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 5.538513813741730019e-02, 1e-15);
  FRENSIE_CHECK_EQUAL( 2.0/trials, 2.0/3.0 );

  local_distribution->sampleAndRecordTrialsAdjointKleinNishina(
        	    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
        	    outgoing_energy,
        	    scattering_angle_cosine,
        	    trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 0.06330760990853734, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, -0.9283177667225548, 1e-15);
  FRENSIE_CHECK_EQUAL( 3.0/trials, 0.75 );

  local_distribution->sampleAndRecordTrialsAdjointKleinNishina(
        	    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
        	    outgoing_energy,
        	    scattering_angle_cosine,
        	    trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 0.056777596517404945, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine,
                                   9.536743164284545e-06,
                                   1e-15 );
  FRENSIE_CHECK_EQUAL( 4.0/trials, 0.8 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check if an energy is below the scattering window
FRENSIE_UNIT_TEST( IncoherentAdjointPhotonScatteringDistribution,
		   isEnergyBelowScatteringWindow )
{
  FRENSIE_CHECK( distribution->isEnergyBelowScatteringWindow( 0.1, 0.0718 ) );

  FRENSIE_CHECK( !distribution->isEnergyBelowScatteringWindow(
						   0.1, 0.0718705616632476 ) );

  FRENSIE_CHECK( !distribution->isEnergyBelowScatteringWindow( 0.1, 0.1 ) );

  FRENSIE_CHECK( !distribution->isEnergyBelowScatteringWindow( 0.1, 0.11 ) );
}

//---------------------------------------------------------------------------//
// Check if an energy is above the scattering window
FRENSIE_UNIT_TEST( IncoherentAdjointPhotonScatteringDistribution,
		   isEnergyAboveScatteringWindow )
{
  FRENSIE_CHECK( !distribution->isEnergyAboveScatteringWindow( 0.1, 0.0718 ) );

  FRENSIE_CHECK( !distribution->isEnergyAboveScatteringWindow(
						   0.1, 0.0718705616632476 ) );

  FRENSIE_CHECK( !distribution->isEnergyAboveScatteringWindow( 0.1, 0.1 ) );
  FRENSIE_CHECK( distribution->isEnergyAboveScatteringWindow( 0.1, 0.11 ) );
}

//---------------------------------------------------------------------------//
// Check if an energy is in the scattering window
FRENSIE_UNIT_TEST( IncoherentAdjointPhotonScatteringDistribution,
		   isEnergyInScatteringWindow )
{
  FRENSIE_CHECK( !distribution->isEnergyInScatteringWindow( 0.1, 0.0718 ) );

  FRENSIE_CHECK( distribution->isEnergyInScatteringWindow( 0.1,
							 0.0718705616632476 ));

  FRENSIE_CHECK( distribution->isEnergyInScatteringWindow( 0.1, 0.1 ) );

  FRENSIE_CHECK( !distribution->isEnergyInScatteringWindow( 0.1, 0.11 ) );

  FRENSIE_CHECK( !distribution->isEnergyInScatteringWindow( 21.0, 1.0 ) );

  FRENSIE_CHECK( !distribution->isEnergyInScatteringWindow( 21.0, 21.0 ) );

  FRENSIE_CHECK( !distribution->isEnergyInScatteringWindow( 21.0, 22.0 ) );
}

//---------------------------------------------------------------------------//
// Check that the critical line energies in scattering window can be returned
FRENSIE_UNIT_TEST( IncoherentAdjointPhotonScatteringDistribution,
		   getCriticalLineEnergiesInScatteringWindow )
{
  TestIncoherentAdjointPhotonScatteringDistribution::LineEnergyIterator
    start_energy, end_energy;

  distribution->getCriticalLineEnergiesInScatteringWindow( 0.06,
							   start_energy,
							   end_energy );

  FRENSIE_CHECK_EQUAL( start_energy, end_energy );

  distribution->getCriticalLineEnergiesInScatteringWindow( 0.07,
							   start_energy,
							   end_energy );

  FRENSIE_CHECK_EQUAL( *start_energy, 0.08 );
  FRENSIE_CHECK_EQUAL( *end_energy,
		       Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( std::distance( start_energy, end_energy ), 1 );

  distribution->getCriticalLineEnergiesInScatteringWindow( 0.18,
							   start_energy,
							   end_energy );

  FRENSIE_CHECK_EQUAL( *start_energy,
		       Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( *end_energy, 1.0 );
  FRENSIE_CHECK_EQUAL( std::distance( start_energy, end_energy), 1 );

  distribution->getCriticalLineEnergiesInScatteringWindow( 0.21,
							   start_energy,
							   end_energy );

  FRENSIE_CHECK_EQUAL( *start_energy,
		       Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( *end_energy, 5.0 );
  FRENSIE_CHECK_EQUAL( std::distance( start_energy, end_energy ), 2 );

  distribution->getCriticalLineEnergiesInScatteringWindow( 0.25,
							   start_energy,
							   end_energy );

  FRENSIE_CHECK_EQUAL( *start_energy,
		       Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( std::distance( start_energy, end_energy ), 3 );

  distribution->getCriticalLineEnergiesInScatteringWindow( 0.52,
							   start_energy,
							   end_energy );

  FRENSIE_CHECK_EQUAL( *start_energy, 1.0 );
  FRENSIE_CHECK_EQUAL( std::distance( start_energy, end_energy ), 2 );

  distribution->getCriticalLineEnergiesInScatteringWindow( 1.1,
							   start_energy,
							   end_energy );

  FRENSIE_CHECK_EQUAL( *start_energy, 5.0 );
  FRENSIE_CHECK_EQUAL( std::distance( start_energy, end_energy ), 1 );

  distribution->getCriticalLineEnergiesInScatteringWindow( 5.1,
							   start_energy,
							   end_energy );

  FRENSIE_CHECK_EQUAL( std::distance( start_energy, end_energy ), 0 );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create the scattering distribution
  std::shared_ptr<std::vector<double> >
    critical_line_energies( new std::vector<double>( 5 ) );

  (*critical_line_energies)[0] = 0.08;
  (*critical_line_energies)[1] =
    Utility::PhysicalConstants::electron_rest_mass_energy;
  (*critical_line_energies)[2] = 1.0;
  (*critical_line_energies)[3] = 5.0;
  (*critical_line_energies)[4] = 21.0;

  distribution.reset( new TestIncoherentAdjointPhotonScatteringDistribution(
							              20.0 ) );

  distribution->setCriticalLineEnergies( critical_line_energies );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstIncoherentAdjointPhotonScatteringDistribution
//---------------------------------------------------------------------------//
