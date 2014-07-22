//---------------------------------------------------------------------------//
//!
//! \file   tstLaw44NeutronScatteringDistribution.cpp
//! \author Alex Bennett
//! \brief  Law 44 neutron scattering distribution unit tests
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Facemc_Law44NeutronScatteringDistribution.hpp"
#include "Facemc_Law4NeutronScatteringEnergyDistribution.hpp"
#include "Facemc_Law44ARDistribution.hpp"
#include "Facemc_StandardLaw44ARDistribution.hpp"
#include "Facemc_Law44InterpolationPolicy.hpp"
#include "Facemc_NeutronScatteringDistribution.hpp"
#include "Facemc_NeutronScatteringEnergyDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_DirectionHelpers.hpp"


//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( Law44NeutronScatteringDistribution, 
		   sampleAngle )
{
   Facemc::Law4NeutronScatteringEnergyDistribution::EnergyDistribution energy_distribution(2);

   Teuchos::Array<Teuchos::RCP<Facemc::Law44ARDistribution> > ar_distribution(2);

   energy_distribution[0].first = 1.0;
   energy_distribution[1].first = 2.0;

   Teuchos::Array<double> outgoing_energy_grid(5);

   Teuchos::Array<double> pdf(4);
   Teuchos::Array<double> pdf_linear(5);

   Teuchos::Array<double> r_array(5);

   Teuchos::Array<double> a_array(5);

   outgoing_energy_grid[0] = 1.0;
   outgoing_energy_grid[1] = 2.0;
   outgoing_energy_grid[2] = 3.0;
   outgoing_energy_grid[3] = 4.0;
   outgoing_energy_grid[4] = 5.0;

   pdf_linear[0] = 0.0;
   pdf_linear[1] = 0.4;
   pdf_linear[2] = 0.8;
   pdf_linear[3] = 1.2;
   pdf_linear[4] = 1.6;

   r_array[0] = 0.1;
   r_array[1] = 0.3;
   r_array[2] = 0.5;
   r_array[3] = 0.7;
   r_array[4] = 0.9;

   a_array[0] = 1.0;
   a_array[1] = 2.0;
   a_array[2] = 3.0;
   a_array[3] = 4.0;
   a_array[4] = 5.0;

   energy_distribution[0].second.reset( new Utility::TabularDistribution<Utility::LinLin>( outgoing_energy_grid, pdf_linear ) );

   ar_distribution[0].reset( new Facemc::StandardLaw44ARDistribution<Facemc::Law44LinLinInterpolationPolicy>(
                                                      outgoing_energy_grid, a_array(), r_array()) );


   outgoing_energy_grid[0] = 2.0;
   outgoing_energy_grid[1] = 3.0;
   outgoing_energy_grid[2] = 4.0;
   outgoing_energy_grid[3] = 5.0;
   outgoing_energy_grid[4] = 6.0;

   pdf[0] = 0.1;
   pdf[1] = 0.1;
   pdf[2] = 0.1;
   pdf[3] = 0.1;

   r_array[0] = 0.3;
   r_array[1] = 0.5;
   r_array[2] = 0.7;
   r_array[3] = 0.9;
   r_array[4] = 1.0;

   a_array[0] = 2.0;
   a_array[1] = 3.0;
   a_array[2] = 4.0;
   a_array[3] = 5.0;
   a_array[4] = 6.0;

   energy_distribution[1].second.reset( new Utility::HistogramDistribution( outgoing_energy_grid, pdf ) );

   ar_distribution[1].reset( new Facemc::StandardLaw44ARDistribution<Facemc::Law44HistogramInterpolationPolicy>(
                                                      outgoing_energy_grid, a_array(), r_array()) );

   // Create the fake stream
   std::vector<double> fake_stream( 4 );
   fake_stream[0] = 0.35;
   fake_stream[1] = 0.35;
   fake_stream[2] = 0.4;
   fake_stream[3] = 0.4;

   Utility::RandomNumberGenerator::setFakeStream( fake_stream );

   Teuchos::RCP<Facemc::NeutronScatteringEnergyDistribution> energy_scattering_distribution;

   energy_scattering_distribution.reset( new Facemc::Law4NeutronScatteringEnergyDistribution( energy_distribution ) );

   Facemc::Law44NeutronScatteringDistribution distribution( 1.0, energy_scattering_distribution, ar_distribution );

   Facemc::NeutronState neutron( 0ull );
   
   double initial_angle[3];
   initial_angle[0] = 0.0;
   initial_angle[1] = 0.0;
   initial_angle[2] = 1.0;

   neutron.setDirection( initial_angle );
   neutron.setEnergy( 1.5 );

   distribution.scatterNeutron( neutron, 1.0 );

   double angle = Utility::calculateCosineOfAngleBetweenVectors( initial_angle, neutron.getDirection() );

   TEST_FLOATING_EQUALITY( angle, 0.6958068, 1e-7);

   // Test 2

   fake_stream[0] = 0.35;
   fake_stream[1] = 0.35;
   fake_stream[2] = 0.6;
   fake_stream[3] = 0.6;

   Utility::RandomNumberGenerator::setFakeStream( fake_stream );
 
   initial_angle[0] = 0.0;
   initial_angle[1] = 0.0;
   initial_angle[2] = 1.0;

   neutron.setDirection( initial_angle );
   neutron.setEnergy( 1.5 );

   distribution.scatterNeutron( neutron, 1.0 );

   angle = Utility::calculateCosineOfAngleBetweenVectors( initial_angle, neutron.getDirection() );

   TEST_FLOATING_EQUALITY( angle, 0.48174437, 1e-7);

   // Test 3

   fake_stream[0] = 0.6;
   fake_stream[1] = 0.6;
   fake_stream[2] = 0.2;
   fake_stream[3] = 0.2;

   Utility::RandomNumberGenerator::setFakeStream( fake_stream );
 
   initial_angle[0] = 0.0;
   initial_angle[1] = 0.0;
   initial_angle[2] = 1.0;

   neutron.setDirection( initial_angle );
   neutron.setEnergy( 1.5 );

   distribution.scatterNeutron( neutron, 1.0 );

   angle = Utility::calculateCosineOfAngleBetweenVectors( initial_angle, neutron.getDirection() );

   TEST_FLOATING_EQUALITY( angle, 0.607568, 1e-6);

   // Test 4

   fake_stream[0] = 0.6;
   fake_stream[1] = 0.2;
   fake_stream[2] = 0.2;
   fake_stream[3] = 0.2;

   Utility::RandomNumberGenerator::setFakeStream( fake_stream );
 
   initial_angle[0] = 0.0;
   initial_angle[1] = 0.0;
   initial_angle[2] = 1.0;

   neutron.setDirection( initial_angle );
   neutron.setEnergy( 0.5 );

   distribution.scatterNeutron( neutron, 1.0 );

   angle = Utility::calculateCosineOfAngleBetweenVectors( initial_angle, neutron.getDirection() );

   TEST_FLOATING_EQUALITY( angle, 0.607568, 1e-6);

   // Test 5
   fake_stream[0] = 0.35;
   fake_stream[1] = 0.4;
   fake_stream[2] = 0.4;
   fake_stream[3] = 0.4;

   Utility::RandomNumberGenerator::setFakeStream( fake_stream );
   
   initial_angle[0] = 0.0;
   initial_angle[1] = 0.0;
   initial_angle[2] = 1.0;

   neutron.setDirection( initial_angle );
   neutron.setEnergy( 2.5 );

   distribution.scatterNeutron( neutron, 1.0 );

   angle = Utility::calculateCosineOfAngleBetweenVectors( initial_angle, neutron.getDirection() );

   TEST_FLOATING_EQUALITY( angle, 0.6958068, 1e-7);
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );
}


//---------------------------------------------------------------------------//
// tstLaw44NeutronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
