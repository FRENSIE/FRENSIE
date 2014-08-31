//---------------------------------------------------------------------------//
//!
//! \file   tstAceLaw4NeutronScatteringDistribution.cpp
//! \author Alex Bennett
//! \brief  Law 4 neutron scattering distribution unit tests
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Facemc_UnitTestHarnessExtensions.hpp"
#include "Facemc_AceLaw4NeutronScatteringEnergyDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_TabularDistribution.hpp"


//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( AceLaw4NeutronScatteringEnergyDistribution, 
		   sampleEnergy_lower_bound_histogram )
{
   Facemc::AceLaw4NeutronScatteringEnergyDistribution::EnergyDistribution 
     energy_distribution(2);

   energy_distribution[0].first = 1.0;
   energy_distribution[1].first = 2.0;

   Teuchos::Array<double> outgoing_energy_grid(5);

   Teuchos::Array<double> pdf(4);

   outgoing_energy_grid[0] = 1.0;
   outgoing_energy_grid[1] = 2.0;
   outgoing_energy_grid[2] = 3.0;
   outgoing_energy_grid[3] = 4.0;
   outgoing_energy_grid[4] = 5.0;

   pdf[0] = 0.2;
   pdf[1] = 0.2;
   pdf[2] = 0.2;
   pdf[3] = 0.2;

   energy_distribution[0].second.reset( new Utility::HistogramDistribution( 
							  outgoing_energy_grid,
							  pdf ) );

   outgoing_energy_grid[0] = 2.0;
   outgoing_energy_grid[1] = 3.0;
   outgoing_energy_grid[2] = 4.0;
   outgoing_energy_grid[3] = 5.0;
   outgoing_energy_grid[4] = 6.0;

   pdf[0] = 0.1;
   pdf[1] = 0.1;
   pdf[2] = 0.1;
   pdf[3] = 0.1;

   energy_distribution[1].second.reset( new Utility::HistogramDistribution( 
							  outgoing_energy_grid,
							  pdf ) );

   // Create the fake stream
   std::vector<double> fake_stream( 1 );
   fake_stream[0] = 0.5;

   Utility::RandomNumberGenerator::setFakeStream( fake_stream );

   Facemc::AceLaw4NeutronScatteringEnergyDistribution 
     distribution( energy_distribution );

   TEST_FLOATING_EQUALITY(distribution.sampleEnergy(0.5), 3.0, 1e-15);
}

//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( AceLaw4NeutronScatteringEnergyDistribution, 
		   sampleEnergy_upper_bound_histogram )
{
   Facemc::AceLaw4NeutronScatteringEnergyDistribution::EnergyDistribution 
     energy_distribution(2);

   energy_distribution[0].first = 1.0;
   energy_distribution[1].first = 2.0;

   Teuchos::Array<double> outgoing_energy_grid(5);

   Teuchos::Array<double> pdf(4);

   outgoing_energy_grid[0] = 1.0;
   outgoing_energy_grid[1] = 2.0;
   outgoing_energy_grid[2] = 3.0;
   outgoing_energy_grid[3] = 4.0;
   outgoing_energy_grid[4] = 5.0;

   pdf[0] = 0.2;
   pdf[1] = 0.2;
   pdf[2] = 0.2;
   pdf[3] = 0.2;

   energy_distribution[0].second.reset( new Utility::HistogramDistribution( 
							  outgoing_energy_grid,
							  pdf ) );

   outgoing_energy_grid[0] = 2.0;
   outgoing_energy_grid[1] = 3.0;
   outgoing_energy_grid[2] = 4.0;
   outgoing_energy_grid[3] = 5.0;
   outgoing_energy_grid[4] = 6.0;

   pdf[0] = 0.1;
   pdf[1] = 0.1;
   pdf[2] = 0.1;
   pdf[3] = 0.1;

   energy_distribution[1].second.reset( new Utility::HistogramDistribution( 
							  outgoing_energy_grid,
							  pdf ) );

   // Create the fake stream
   std::vector<double> fake_stream( 1 );
   fake_stream[0] = 0.5;

   Utility::RandomNumberGenerator::setFakeStream( fake_stream );

   Facemc::AceLaw4NeutronScatteringEnergyDistribution 
     distribution( energy_distribution );

   TEST_FLOATING_EQUALITY(distribution.sampleEnergy(2.5), 4.0, 1e-15);
}

//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( AceLaw4NeutronScatteringEnergyDistribution, 
		   sampleEnergy_histogram )
{
   Facemc::AceLaw4NeutronScatteringEnergyDistribution::EnergyDistribution 
     energy_distribution(2);

   energy_distribution[0].first = 1.0;
   energy_distribution[1].first = 2.0;

   Teuchos::Array<double> outgoing_energy_grid(5);

   Teuchos::Array<double> pdf(4);

   outgoing_energy_grid[0] = 1.0;
   outgoing_energy_grid[1] = 2.0;
   outgoing_energy_grid[2] = 3.0;
   outgoing_energy_grid[3] = 4.0;
   outgoing_energy_grid[4] = 5.0;

   pdf[0] = 0.2;
   pdf[1] = 0.2;
   pdf[2] = 0.2;
   pdf[3] = 0.2;

   energy_distribution[0].second.reset( new Utility::HistogramDistribution( 
							  outgoing_energy_grid,
							  pdf ) );

   outgoing_energy_grid[0] = 2.0;
   outgoing_energy_grid[1] = 3.0;
   outgoing_energy_grid[2] = 4.0;
   outgoing_energy_grid[3] = 5.0;
   outgoing_energy_grid[4] = 6.0;

   pdf[0] = 0.1;
   pdf[1] = 0.1;
   pdf[2] = 0.1;
   pdf[3] = 0.1;

   energy_distribution[1].second.reset( new Utility::HistogramDistribution( 
							  outgoing_energy_grid,
							  pdf ) );

   // Create the fake stream
   std::vector<double> fake_stream( 2 );
   fake_stream[0] = 0.25;
   fake_stream[1] = 0.5;

   Utility::RandomNumberGenerator::setFakeStream( fake_stream );

   Facemc::AceLaw4NeutronScatteringEnergyDistribution 
     distribution( energy_distribution );

   TEST_FLOATING_EQUALITY(distribution.sampleEnergy(1.5), 3.5, 1e-15);
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
// tstAceLaw4NeutronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
