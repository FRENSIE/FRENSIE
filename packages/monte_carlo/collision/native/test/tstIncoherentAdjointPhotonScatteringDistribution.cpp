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
  
// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_UnitTestHarnessExtensions.hpp"
#include "MonteCarlo_IncoherentAdjointPhotonScatteringDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"

//---------------------------------------------------------------------------//
// Testing Structs
//---------------------------------------------------------------------------//
class TestIncoherentAdjointPhotonScatteringDistribution : public MonteCarlo::IncoherentAdjointPhotonScatteringDistribution
{
public:
  
  // Constructor
  TestIncoherentAdjointPhotonScatteringDistribution(
	       const double max_energy,
	       const Teuchos::ArrayRCP<const double>& critical_line_energies )
    : MonteCarlo::IncoherentAdjointPhotonScatteringDistribution( 
						       max_energy,
						       critical_line_energies )
  { /* ... */ }

  // Destructor
  ~TestIncoherentAdjointPhotonScatteringDistribution()
  { /* ... */ }

  // Evaluate the distribution
  double evaluate( const double incoming_energy,
		   const double scattering_angle_cosine ) const
  { /* ... */ }

  //! Evaluate the integrated cross section (cm^2)
  double evaluateIntegratedCrossSection( const double incoming_energy,
					 const double precision ) const
  { /* ... */ }
  
  // Sample an outgoing energy and direction from the distribution
  void sample( const double incoming_energy,
	       double& outgoing_energy,
	       double& scattering_angle_cosine ) const
  { /* ... */ }

  // Sample an outgoing energy and direction and record the number of trials
  void sampleAndRecordTrials( const double incoming_energy,
			      double& outgoing_energy,
			      double& scattering_angle_cosine,
			      unsigned& trials ) const
  { /* ... */ }

  // Randomly scatter the photon and return the shell that was interacted with
  void scatterAdjointPhoton( MonteCarlo::AdjointPhotonState& adjoint_photon,
			     MonteCarlo::ParticleBank& bank,
			     MonteCarlo::SubshellType& shell_of_interaction ) const
  { /* ... */ }

  // Create a probe particle
  void createProbeParticle( 
			  const double energy_of_interest, 
			  const MonteCarlo::AdjointPhotonState& adjoint_photon,
			  MonteCarlo::ParticleBank& bank ) const
  { /* ... */ }

  using MonteCarlo::IncoherentAdjointPhotonScatteringDistribution::LineEnergyIterator;
  using MonteCarlo::IncoherentAdjointPhotonScatteringDistribution::evaluateAdjointKleinNishinaDist;
  using MonteCarlo::IncoherentAdjointPhotonScatteringDistribution::sampleAndRecordTrialsAdjointKleinNishina;
  using MonteCarlo::IncoherentAdjointPhotonScatteringDistribution::getCriticalLineEnergiesInScatteringWindow;
};

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<TestIncoherentAdjointPhotonScatteringDistribution> distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the max energy can be returned
TEUCHOS_UNIT_TEST( IncoherentAdjointPhotonScatteringDistribution, 
		   getMaxEnergy )
{
  TEST_EQUALITY_CONST( distribution->getMaxEnergy(), 20.0 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint Klein-Nishina distribution can be evaluated
TEUCHOS_UNIT_TEST( IncoherentAdjointPhotonScatteringDistribution,
		   evaluateAdjointKleinNishinaDist )
{
  double dist_value = 
    distribution->evaluateAdjointKleinNishinaDist( 0.1, -1.0 );

  TEST_FLOATING_EQUALITY( dist_value, 0.5617250013852311, 1e-15 );

  dist_value = distribution->evaluateAdjointKleinNishinaDist( 0.1, 0.0 );

  TEST_FLOATING_EQUALITY( dist_value, 0.2613454621535213, 1e-15 );

  dist_value = distribution->evaluateAdjointKleinNishinaDist( 0.1, 1.0 );

  TEST_FLOATING_EQUALITY( dist_value, 0.4989344050883251, 1e-15 );

  dist_value = 
    distribution->evaluateAdjointKleinNishinaDist( 1.0, 0.5145510353765 );

  TEST_FLOATING_EQUALITY( dist_value, 4.818399835538855, 1e-15 );

  dist_value = distribution->evaluateAdjointKleinNishinaDist( 1.0, 0.9 );

  TEST_FLOATING_EQUALITY( dist_value, 0.4634138962142929, 1e-15 );

  dist_value = distribution->evaluateAdjointKleinNishinaDist( 1.0, 1.0 );

  TEST_FLOATING_EQUALITY( dist_value, 0.4989344050883251, 1e-15 );

  dist_value = 
    distribution->evaluateAdjointKleinNishinaDist( 10.0, 0.9744500544935 );
  
  TEST_FLOATING_EQUALITY( dist_value, 0.6110831116179009, 1e-15 );

  dist_value = distribution->evaluateAdjointKleinNishinaDist( 10.0, 0.99 );

  TEST_FLOATING_EQUALITY( dist_value, 0.5058482673670551, 1e-15 );

  dist_value = distribution->evaluateAdjointKleinNishinaDist( 10.0, 1.0 );

  TEST_FLOATING_EQUALITY( dist_value, 0.4989344050883251, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint Klein-Nishina distribution can be evaluated
TEUCHOS_UNIT_TEST( IncoherentAdjointPhotonScatteringDistribution,
		   sampleAndRecordTrialsAdjointKleinNishina )
{
  double outgoing_energy, scattering_angle_cosine;
  unsigned trials = 0;

  // 1st branch of rejections scheme
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

  distribution->sampleAndRecordTrialsAdjointKleinNishina(
		    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
		    outgoing_energy,
		    scattering_angle_cosine,
		    trials );

  TEST_FLOATING_EQUALITY( outgoing_energy, 0.053789358961052636, 1e-15 );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.5, 1e-15 );
  TEST_EQUALITY_CONST( 1.0/trials, 0.5 );

  distribution->sampleAndRecordTrialsAdjointKleinNishina(
		    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
		    outgoing_energy,
		    scattering_angle_cosine,
		    trials );

  TEST_FLOATING_EQUALITY( outgoing_energy, 0.06289961773671575, 1e-15 );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -0.8759615953640385, 1e-15);
  TEST_EQUALITY_CONST( 2.0/trials, 2.0/3.0 );

  distribution->sampleAndRecordTrialsAdjointKleinNishina(
		    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
		    outgoing_energy,
		    scattering_angle_cosine,
		    trials ); 
  
  TEST_FLOATING_EQUALITY( outgoing_energy, 0.06330760990853734, 1e-15 );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -0.9283177667225548, 1e-15);
  TEST_EQUALITY_CONST( 3.0/trials, 0.75 );

  distribution->sampleAndRecordTrialsAdjointKleinNishina(
		    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
		    outgoing_energy,
		    scattering_angle_cosine,
		    trials ); 

  TEST_FLOATING_EQUALITY( outgoing_energy, 0.056777596517404945, 1e-15 );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 
			  9.536743164284545e-06, 
			  1e-15 );
  TEST_EQUALITY_CONST( 4.0/trials, 0.8 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check if an energy is below the scattering window
TEUCHOS_UNIT_TEST( IncoherentAdjointPhotonScatteringDistribution,
		   isEnergyBelowScatteringWindow )
{
  TEST_ASSERT( distribution->isEnergyBelowScatteringWindow( 0.1, 0.0718 ) );

  TEST_ASSERT( !distribution->isEnergyBelowScatteringWindow( 
						   0.1, 0.0718705616632476 ) );

  TEST_ASSERT( !distribution->isEnergyBelowScatteringWindow( 0.1, 0.1 ) );

  TEST_ASSERT( !distribution->isEnergyBelowScatteringWindow( 0.1, 0.11 ) );
}

//---------------------------------------------------------------------------//
// Check if an energy is above the scattering window
TEUCHOS_UNIT_TEST( IncoherentAdjointPhotonScatteringDistribution,
		   isEnergyAboveScattringWindow )
{
  TEST_ASSERT( !distribution->isEnergyAboveScatteringWindow( 0.1, 0.0718 ) );
  
  TEST_ASSERT( !distribution->isEnergyAboveScatteringWindow( 
						   0.1, 0.0718705616632476 ) );

  TEST_ASSERT( !distribution->isEnergyAboveScatteringWindow( 0.1, 0.1 ) );
  TEST_ASSERT( distribution->isEnergyAboveScatteringWindow( 0.1, 0.11 ) );
}

//---------------------------------------------------------------------------//
// Check if an energy is in the scattering window
TEUCHOS_UNIT_TEST( IncoherentAdjointPhotonScatteringDistribution,
		   isEnergyInScatteringWindow )
{
  TEST_ASSERT( !distribution->isEnergyInScatteringWindow( 0.1, 0.0718 ) );

  TEST_ASSERT( distribution->isEnergyInScatteringWindow( 0.1, 
							 0.0718705616632476 ));

  TEST_ASSERT( distribution->isEnergyInScatteringWindow( 0.1, 0.1 ) );

  TEST_ASSERT( !distribution->isEnergyInScatteringWindow( 0.1, 0.11 ) );
}

//---------------------------------------------------------------------------//
// Check that the critical line energies in scattering window can be returned
TEUCHOS_UNIT_TEST( IncoherentAdjointPhotonScatteringDistribution,
		   getCriticalLineEnergiesInScatteringWindow )
{
  TestIncoherentAdjointPhotonScatteringDistribution::LineEnergyIterator
    start_energy, end_energy;

  distribution->getCriticalLineEnergiesInScatteringWindow( 0.06,
							   start_energy,
							   end_energy );

  TEST_EQUALITY( start_energy, end_energy );

  distribution->getCriticalLineEnergiesInScatteringWindow( 0.07,
							   start_energy,
							   end_energy );

  TEST_EQUALITY_CONST( *start_energy, 0.08 );
  TEST_EQUALITY_CONST( *end_energy, 
		       Utility::PhysicalConstants::electron_rest_mass_energy );
  TEST_EQUALITY_CONST( std::distance( start_energy, end_energy ), 1 );
  
  distribution->getCriticalLineEnergiesInScatteringWindow( 0.18,
							   start_energy,
							   end_energy );

  TEST_EQUALITY_CONST( *start_energy, 
		       Utility::PhysicalConstants::electron_rest_mass_energy );
  TEST_EQUALITY_CONST( *end_energy, 1.0 );
  TEST_EQUALITY_CONST( std::distance( start_energy, end_energy), 1 );

  distribution->getCriticalLineEnergiesInScatteringWindow( 0.21,
							   start_energy,
							   end_energy );

  TEST_EQUALITY_CONST( *start_energy,
		       Utility::PhysicalConstants::electron_rest_mass_energy );
  TEST_EQUALITY_CONST( *end_energy, 5.0 );
  TEST_EQUALITY_CONST( std::distance( start_energy, end_energy ), 2 );
					
  distribution->getCriticalLineEnergiesInScatteringWindow( 0.25,
							   start_energy,
							   end_energy );

  TEST_EQUALITY_CONST( *start_energy,
		       Utility::PhysicalConstants::electron_rest_mass_energy );
  TEST_EQUALITY_CONST( std::distance( start_energy, end_energy ), 3 );

  distribution->getCriticalLineEnergiesInScatteringWindow( 0.52,
							   start_energy,
							   end_energy );

  TEST_EQUALITY_CONST( *start_energy, 1.0 );
  TEST_EQUALITY_CONST( std::distance( start_energy, end_energy ), 2 );

  distribution->getCriticalLineEnergiesInScatteringWindow( 1.1,
							   start_energy,
							   end_energy );

  TEST_EQUALITY_CONST( *start_energy, 5.0 );
  TEST_EQUALITY_CONST( std::distance( start_energy, end_energy ), 1 );

  distribution->getCriticalLineEnergiesInScatteringWindow( 5.1,
							   start_energy,
							   end_energy );

  TEST_EQUALITY_CONST( std::distance( start_energy, end_energy ), 0 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  // Create the scattering distribution
  Teuchos::ArrayRCP<double> critical_line_energies( 4 );

  critical_line_energies[0] = 0.08;
  critical_line_energies[1] = 
    Utility::PhysicalConstants::electron_rest_mass_energy;
  critical_line_energies[2] = 1.0;
  critical_line_energies[3] = 5.0;

  distribution.reset( new TestIncoherentAdjointPhotonScatteringDistribution(
						    20.0,
						    critical_line_energies ) );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();

  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );
}

//---------------------------------------------------------------------------//
// end tstIncoherentAdjointPhotonScatteringDistribution
//---------------------------------------------------------------------------//
