//---------------------------------------------------------------------------//
//!
//! \file   tstAceLaw5NuclearScatteringEnergyDistribution.cpp
//! \author Eli Moll
//! \brief  Ace law 11 neutron scattering energy distribution unit tests
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
#include "MonteCarlo_AceLaw11NuclearScatteringEnergyDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_WattDistribution.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( AceLaw11NuclearScatteringEnergyDistribution,
		   sample_lower_bounds )
{
   MonteCarlo::AceLaw11NuclearScatteringEnergyDistribution::EnergyDistribution
     a_distribution;

   a_distribution.resize(2);

   a_distribution[0].first = 1.0;
   a_distribution[0].second = 1.0;

   a_distribution[1].first = 2.0;
   a_distribution[1].second = 2.0;

   MonteCarlo::AceLaw11NuclearScatteringEnergyDistribution::EnergyDistribution
     b_distribution;

   b_distribution.resize(2);

   b_distribution[0].first = 1.0;
   b_distribution[0].second = 3.0;

   b_distribution[1].first = 2.0;
   b_distribution[1].second = 4.0;

   // Create the fake stream
   std::vector<double> fake_stream( 4 );
   fake_stream[0] = 0.75;
   fake_stream[1] = 0.75;
   fake_stream[2] = 0.5;
   fake_stream[3] = 0.1;

   Utility::RandomNumberGenerator::setFakeStream( fake_stream );

   double restriction_energy = 0.05;

   MonteCarlo::AceLaw11NuclearScatteringEnergyDistribution distribution(
                                                       a_distribution,
                                                       b_distribution,
                                                       restriction_energy );

   TEST_COMPARE(distribution.sampleEnergy(0.5) ,==,
     Utility::WattDistribution::sample( 0.5,
                                        a_distribution[0].second,
                                        b_distribution[0].second,
                                        restriction_energy ));
}

//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( AceLaw11NuclearScatteringEnergyDistribution,
		   sample_upper_bounds )
{
   MonteCarlo::AceLaw11NuclearScatteringEnergyDistribution::EnergyDistribution
     a_distribution;

   a_distribution.resize(2);

   a_distribution[0].first = 1.0;
   a_distribution[0].second = 1.0;

   a_distribution[1].first = 2.0;
   a_distribution[1].second = 2.0;

   MonteCarlo::AceLaw11NuclearScatteringEnergyDistribution::EnergyDistribution
     b_distribution;

   b_distribution.resize(2);

   b_distribution[0].first = 1.0;
   b_distribution[0].second = 3.0;

   b_distribution[1].first = 2.0;
   b_distribution[1].second = 4.0;

   // Create the fake stream
   std::vector<double> fake_stream( 4 );
   fake_stream[0] = 0.75;
   fake_stream[1] = 0.75;
   fake_stream[2] = 0.5;
   fake_stream[3] = 0.1;

   Utility::RandomNumberGenerator::setFakeStream( fake_stream );

   double restriction_energy = 0.05;

   MonteCarlo::AceLaw11NuclearScatteringEnergyDistribution distribution(
                                                       a_distribution,
                                                       b_distribution,
                                                       restriction_energy );

   TEST_COMPARE(distribution.sampleEnergy(3.0) ,==,
     Utility::WattDistribution::sample( 3.0,
                                        a_distribution[1].second,
                                        b_distribution[1].second,
                                        restriction_energy ));
}

//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( AceLaw11NuclearScatteringEnergyDistribution,
		   sampleEnergy )
{
   MonteCarlo::AceLaw11NuclearScatteringEnergyDistribution::EnergyDistribution
     a_distribution;

   a_distribution.resize(2);

   a_distribution[0].first = 1.0;
   a_distribution[0].second = 1.0;

   a_distribution[1].first = 2.0;
   a_distribution[1].second = 2.0;

   MonteCarlo::AceLaw11NuclearScatteringEnergyDistribution::EnergyDistribution
     b_distribution;

   b_distribution.resize(2);

   b_distribution[0].first = 1.0;
   b_distribution[0].second = 3.0;

   b_distribution[1].first = 2.0;
   b_distribution[1].second = 4.0;

   // Create the fake stream
   std::vector<double> fake_stream( 4 );
   fake_stream[0] = 0.75;
   fake_stream[1] = 0.75;
   fake_stream[2] = 0.5;
   fake_stream[3] = 0.1;

   Utility::RandomNumberGenerator::setFakeStream( fake_stream );

   double restriction_energy = 0.05;

   MonteCarlo::AceLaw11NuclearScatteringEnergyDistribution distribution(
                                                       a_distribution,
                                                       b_distribution,
                                                       restriction_energy );

   TEST_COMPARE(distribution.sampleEnergy(1.5) ,==,
     Utility::WattDistribution::sample( 1.5,
                                        1.5,
                                        3.5,
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
// tstAceLaw11NuclearScatteringDistribution.cpp
//---------------------------------------------------------------------------//
