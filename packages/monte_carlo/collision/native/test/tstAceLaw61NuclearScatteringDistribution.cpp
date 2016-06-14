//---------------------------------------------------------------------------//
//!
//! \file   tstAceLaw61NuclearScatteringDistribution.cpp
//! \author Eli Moll
//! \brief  Law 61 neutron scattering distribution unit tests
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_AceLaw61NuclearScatteringDistribution.hpp"
#include "MonteCarlo_AceLaw4NuclearScatteringEnergyDistribution.hpp"
#include "MonteCarlo_AceLaw61AngleDistribution.hpp"
#include "MonteCarlo_StandardAceLaw61AngleDistribution.hpp"
#include "MonteCarlo_AceLaw61InterpolationPolicy.hpp"
#include "MonteCarlo_NuclearScatteringDistribution.hpp"
#include "MonteCarlo_NuclearScatteringEnergyDistribution.hpp"
#include "MonteCarlo_LabSystemConversionPolicy.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_DiscreteDistribution.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( AceLaw61NuclearScatteringDistribution, 
		   sampleAngle )
{
  MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution::EnergyDistribution 
    energy_distribution(2);

  Teuchos::Array< Teuchos::RCP<MonteCarlo::AceLaw61AngleDistribution> > 
    angle_distribution(2);

  energy_distribution[0].first = 1.0;
  energy_distribution[1].first = 2.0;

  // ----------------------------------------------------------------------- //
  // Distributions for E_in(1)
  // ----------------------------------------------------------------------- //

  // Construct the outgoing energy grid
  std::vector<double> outgoing_energy_grid(3);
  std::vector<double> pdf(3);

  outgoing_energy_grid[0] = 1.0;
  outgoing_energy_grid[1] = 2.0;
  outgoing_energy_grid[2] = 3.0;

  pdf[0] = 0.5;
  pdf[1] = 0.5;
  pdf[2] = 0.5;

  // Construct the cosine arrays for each outgoing energy grid point
  std::vector<double> cosine_vector_1 = {-1.0, -0.75, -0.5};
  std::vector<double> cosine_vector_2 = {-0.25, 0.00, 0.25};
  std::vector<double> cosine_vector_3 = {0.50,  0.75,  1.0};

  std::vector<double> probability = {1.0, 1.0, 1.0}; 

  // Construct the cosine discrete distributions
  Teuchos::Array< Teuchos::RCP<Utility::OneDDistribution> > cosine_arrays(3);
    
  cosine_arrays[0].reset( 
    new Utility::DiscreteDistribution( cosine_vector_1, probability ) );
    
  cosine_arrays[1].reset( 
    new Utility::DiscreteDistribution( cosine_vector_2, probability ) );
    
  cosine_arrays[2].reset( 
    new Utility::DiscreteDistribution( cosine_vector_3, probability ) );

  energy_distribution[0].second.reset( 
         new Utility::TabularDistribution<Utility::LinLin>( 
					    outgoing_energy_grid,
					    pdf ) );

  angle_distribution[0].reset( 
   new MonteCarlo::StandardAceLaw61AngleDistribution<MonteCarlo::AceLaw61LinLinInterpolationPolicy>(
                                                        outgoing_energy_grid,
                                                        cosine_arrays ) );

  // ----------------------------------------------------------------------- //
  // Distributions for E_in(2)
  // ----------------------------------------------------------------------- //

  // Construct the outgoing energy grid
  outgoing_energy_grid[0] = 4.0;
  outgoing_energy_grid[1] = 5.0;
  outgoing_energy_grid[2] = 6.0;

  pdf[0] = 0.5;
  pdf[1] = 0.5;
  pdf[2] = 0.5;

  energy_distribution[1].second.reset( 
         new Utility::TabularDistribution<Utility::LinLin>( 
					    outgoing_energy_grid,
					    pdf ) );

  angle_distribution[1].reset( 
   new MonteCarlo::StandardAceLaw61AngleDistribution<MonteCarlo::AceLaw61HistogramInterpolationPolicy>(
                                                        outgoing_energy_grid,
                                                        cosine_arrays ) );

  // Create the fake stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.0;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Construct the energy distribution
  Teuchos::RCP<MonteCarlo::NuclearScatteringEnergyDistribution> 
  energy_scattering_distribution;

  energy_scattering_distribution.reset( 
     new MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution(
					   energy_distribution));
   
  Teuchos::RCP<MonteCarlo::NuclearScatteringDistribution<MonteCarlo::NeutronState,MonteCarlo::NeutronState> > distribution( new MonteCarlo::AceLaw61NuclearScatteringDistribution<MonteCarlo::NeutronState,MonteCarlo::NeutronState,MonteCarlo::LabSystemConversionPolicy>( 1.0, energy_scattering_distribution, angle_distribution ) );

  MonteCarlo::NeutronState neutron( 0ull );

  // Test 1 - E_in(1)
  double initial_angle[3];
  initial_angle[0] = 0.0;
  initial_angle[1] = 0.0;
  initial_angle[2] = 1.0;

  neutron.setDirection( initial_angle );
  neutron.setEnergy( 1.0 );

  distribution->scatterParticle( neutron, 1.0 );

  double angle = 
    Utility::calculateCosineOfAngleBetweenVectors( initial_angle, 
				                                           neutron.getDirection() );
	double energy = neutron.getEnergy();
				      
	TEST_FLOATING_EQUALITY( angle, -1.0, 1e-6 );
	TEST_FLOATING_EQUALITY( energy, 1.0, 1e-6 );

	// Test 2 - E_in(2)
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  initial_angle[0] = 0.0;
  initial_angle[1] = 0.0;
  initial_angle[2] = 1.0;
  
  neutron.setDirection( initial_angle );
  neutron.setEnergy( 2.0 );

  distribution->scatterParticle( neutron, 1.0 );

  angle = 
    Utility::calculateCosineOfAngleBetweenVectors( initial_angle, 
				                                           neutron.getDirection() );
	energy = neutron.getEnergy();
  
	TEST_FLOATING_EQUALITY( angle, -1.0, 1e-6 );
	TEST_FLOATING_EQUALITY( energy, 4.0, 1e-6 );	
	
	// Test 3 - LinLin
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.6;
  fake_stream[2] = 0.5;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  initial_angle[0] = 0.0;
  initial_angle[1] = 0.0;
  initial_angle[2] = 1.0;
  
  neutron.setDirection( initial_angle );
  neutron.setEnergy( 1.0 );

  distribution->scatterParticle( neutron, 1.0 );

  angle = 
    Utility::calculateCosineOfAngleBetweenVectors( initial_angle, 
				                                           neutron.getDirection() );
	energy = neutron.getEnergy();
  
	TEST_FLOATING_EQUALITY( angle,  0.0, 1e-6 );
	TEST_FLOATING_EQUALITY( energy, 2.2, 1e-6 );	
	
	// Test 4 - Histogram
  fake_stream[0] = 0.6;
  fake_stream[1] = 0.5;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  initial_angle[0] = 0.0;
  initial_angle[1] = 0.0;
  initial_angle[2] = 1.0;
  
  neutron.setDirection( initial_angle );
  neutron.setEnergy( 2.0 );

  distribution->scatterParticle( neutron, 1.0 );

  angle = 
    Utility::calculateCosineOfAngleBetweenVectors( initial_angle, 
				                                           neutron.getDirection() );
	energy = neutron.getEnergy();
  
	TEST_FLOATING_EQUALITY( angle,  0.0, 1e-6 );
	TEST_FLOATING_EQUALITY( energy, 5.2, 1e-6 );	
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();

  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );
}


//---------------------------------------------------------------------------//
// tstAceLaw61NuclearScatteringDistribution.cpp
//---------------------------------------------------------------------------//
