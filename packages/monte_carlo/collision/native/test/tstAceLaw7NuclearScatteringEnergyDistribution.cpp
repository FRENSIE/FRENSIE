//---------------------------------------------------------------------------//
//!
//! \file   tstAceLaw7NuclearScatteringEnergyDistribution.cpp
//! \author Eli Moll
//! \brief  Ace law 7 neutron scattering energy distribution unit tests
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
#include "MonteCarlo_AceLaw7NuclearScatteringEnergyDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_MaxwellFissionDistribution.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( AceLaw7NuclearScatteringEnergyDistribution,
		   sampleEnergy_lower_bound )
{
   MonteCarlo::AceLaw7NuclearScatteringEnergyDistribution::EnergyDistribution
     energy_distribution;

   energy_distribution.resize(2);

   energy_distribution[0].first = 1.0;
   energy_distribution[0].second = 1.0;

   energy_distribution[1].first = 2.0;
   energy_distribution[1].second = 2.0;

   double restriction_energy = 0.05;

   // Create the fake stream
   std::vector<double> fake_stream( 3 );
   fake_stream[0] = 0.75;
   fake_stream[1] = 0.75;
   fake_stream[2] = 0.5;

   Utility::RandomNumberGenerator::setFakeStream( fake_stream );

   MonteCarlo::AceLaw7NuclearScatteringEnergyDistribution distribution( energy_distribution, restriction_energy );

   TEST_COMPARE(distribution.sampleEnergy(0.5) ,==,
     Utility::MaxwellFissionDistribution::sample( 0.5,
                                                  energy_distribution[0].second,
                                                  restriction_energy ));
}

//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( AceLaw7NuclearScatteringEnergyDistribution,
		   sampleEnergy_upper_bound )
{
   MonteCarlo::AceLaw7NuclearScatteringEnergyDistribution::EnergyDistribution
     energy_distribution;

   energy_distribution.resize(2);

   energy_distribution[0].first = 1.0;
   energy_distribution[0].second = 1.0;

   energy_distribution[1].first = 2.0;
   energy_distribution[1].second = 2.0;

   double restriction_energy = 0.05;

   // Create the fake stream
   std::vector<double> fake_stream( 3 );
   fake_stream[0] = 0.75;
   fake_stream[1] = 0.75;
   fake_stream[2] = 0.5;

   Utility::RandomNumberGenerator::setFakeStream( fake_stream );

   MonteCarlo::AceLaw7NuclearScatteringEnergyDistribution distribution( energy_distribution, restriction_energy );

   TEST_COMPARE(distribution.sampleEnergy(3.0) ,==,
     Utility::MaxwellFissionDistribution::sample( 3.0,
                                                  energy_distribution[1].second,
                                                  restriction_energy ));
}

//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( AceLaw7NuclearScatteringEnergyDistribution,
		   sampleEnergy )
{
   MonteCarlo::AceLaw7NuclearScatteringEnergyDistribution::EnergyDistribution
     energy_distribution;

   energy_distribution.resize(2);

   energy_distribution[0].first = 1.0;
   energy_distribution[0].second = 1.0;

   energy_distribution[1].first = 2.0;
   energy_distribution[1].second = 2.0;

   double restriction_energy = 0.05;

   // Create the fake stream
   std::vector<double> fake_stream( 3 );
   fake_stream[0] = 0.75;
   fake_stream[1] = 0.75;
   fake_stream[2] = 0.5;

   Utility::RandomNumberGenerator::setFakeStream( fake_stream );

   MonteCarlo::AceLaw7NuclearScatteringEnergyDistribution distribution( energy_distribution, restriction_energy );

   TEST_COMPARE(distribution.sampleEnergy(1.5) ,==,
     Utility::MaxwellFissionDistribution::sample( 1.5,
                                                  1.5,
                                                  restriction_energy ));
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
// tstAceLaw7NuclearScatteringDistribution.cpp
//---------------------------------------------------------------------------//
