//---------------------------------------------------------------------------//
//!
//! \file   tstAceLaw5NuclearScatteringEnergyDistribution.cpp
//! \author Eli Moll
//! \brief  Ace law 5 neutron scattering energy distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_UnitTestHarnessExtensions.hpp"
#include "MonteCarlo_AceLaw5NuclearScatteringEnergyDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"


//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( AceLaw5NuclearScatteringEnergyDistribution,
		   sampleEnergy_lower_bound )
{
   MonteCarlo::AceLaw5NuclearScatteringEnergyDistribution::EnergyDistribution
     energy_distribution;

   energy_distribution.resize(2);

   energy_distribution[0].first = 1.0;
   energy_distribution[0].second = 1.0;

   energy_distribution[1].first = 2.0;
   energy_distribution[1].second = 2.0;

   MonteCarlo::AceLaw5NuclearScatteringEnergyDistribution::EnergyDistribution
     probabilistic_function;

   probabilistic_function.resize(2);

   probabilistic_function[0].first = 0.0;
   probabilistic_function[0].second = 1.0;

   probabilistic_function[1].first = 1.0;
   probabilistic_function[1].second = 2.0;

   // Create the fake stream
   std::vector<double> fake_stream( 1 );
   fake_stream[0] = 0.5;

   Utility::RandomNumberGenerator::setFakeStream( fake_stream );

   MonteCarlo::AceLaw5NuclearScatteringEnergyDistribution distribution( energy_distribution, probabilistic_function );

   TEST_COMPARE(distribution.sampleEnergy(0.5) ,==, 1.50)
}

//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( AceLaw5NuclearScatteringEnergyDistribution,
		   sampleEnergy_upper_bound )
{
   MonteCarlo::AceLaw5NuclearScatteringEnergyDistribution::EnergyDistribution
     energy_distribution;

   energy_distribution.resize(2);

   energy_distribution[0].first = 1.0;
   energy_distribution[0].second = 1.0;

   energy_distribution[1].first = 2.0;
   energy_distribution[1].second = 2.0;

   MonteCarlo::AceLaw5NuclearScatteringEnergyDistribution::EnergyDistribution
     probabilistic_function;

   probabilistic_function.resize(2);

   probabilistic_function[0].first = 0.0;
   probabilistic_function[0].second = 1.0;

   probabilistic_function[1].first = 1.0;
   probabilistic_function[1].second = 2.0;

   // Create the fake stream
   std::vector<double> fake_stream( 1 );
   fake_stream[0] = 0.5;

   Utility::RandomNumberGenerator::setFakeStream( fake_stream );

   MonteCarlo::AceLaw5NuclearScatteringEnergyDistribution distribution( energy_distribution, probabilistic_function );

   TEST_COMPARE(distribution.sampleEnergy(3.0) ,==, 3.0)
}

//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( AceLaw5NuclearScatteringEnergyDistribution,
		   sampleProb_lower_bound )
{
   MonteCarlo::AceLaw5NuclearScatteringEnergyDistribution::EnergyDistribution
     energy_distribution;

   energy_distribution.resize(2);

   energy_distribution[0].first = 1.0;
   energy_distribution[0].second = 1.0;

   energy_distribution[1].first = 2.0;
   energy_distribution[1].second = 2.0;

   MonteCarlo::AceLaw5NuclearScatteringEnergyDistribution::EnergyDistribution
     probabilistic_function;

   probabilistic_function.resize(2);

   probabilistic_function[0].first = 0.0;
   probabilistic_function[0].second = 1.0;

   probabilistic_function[1].first = 1.0;
   probabilistic_function[1].second = 2.0;

   // Create the fake stream
   std::vector<double> fake_stream( 1 );
   fake_stream[0] = 0.0;

   Utility::RandomNumberGenerator::setFakeStream( fake_stream );

   MonteCarlo::AceLaw5NuclearScatteringEnergyDistribution distribution( energy_distribution, probabilistic_function );

   TEST_COMPARE(distribution.sampleEnergy(0.5) ,==, 1.0)
}

//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( AceLaw5NuclearScatteringEnergyDistribution,
		   sampleEnergy )
{
   MonteCarlo::AceLaw5NuclearScatteringEnergyDistribution::EnergyDistribution
     energy_distribution;

   energy_distribution.resize(2);

   energy_distribution[0].first = 1.0;
   energy_distribution[0].second = 1.0;

   energy_distribution[1].first = 2.0;
   energy_distribution[1].second = 2.0;

   MonteCarlo::AceLaw5NuclearScatteringEnergyDistribution::EnergyDistribution
     probabilistic_function;

   probabilistic_function.resize(2);

   probabilistic_function[0].first = 0.0;
   probabilistic_function[0].second = 1.0;

   probabilistic_function[1].first = 1.0;
   probabilistic_function[1].second = 2.0;

   // Create the fake stream
   std::vector<double> fake_stream( 1 );
   fake_stream[0] = 0.5;

   Utility::RandomNumberGenerator::setFakeStream( fake_stream );

   MonteCarlo::AceLaw5NuclearScatteringEnergyDistribution distribution( energy_distribution, probabilistic_function );

   TEST_COMPARE(distribution.sampleEnergy(1.5) ,==, 2.25)
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
// tstAceLaw5NuclearScatteringDistribution.cpp
//---------------------------------------------------------------------------//
