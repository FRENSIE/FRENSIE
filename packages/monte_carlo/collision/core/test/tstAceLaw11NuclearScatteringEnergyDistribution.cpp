//---------------------------------------------------------------------------//
//!
//! \file   tstAceLaw5NuclearScatteringEnergyDistribution.cpp
//! \author Eli Moll
//! \brief  Ace law 11 neutron scattering energy distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_AceLaw11NuclearScatteringEnergyDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_WattDistribution.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
FRENSIE_UNIT_TEST( AceLaw11NuclearScatteringEnergyDistribution,
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

   FRENSIE_CHECK_EQUAL(distribution.sampleEnergy(0.5),
     Utility::WattDistribution::sample( 0.5,
                                        a_distribution[0].second,
                                        b_distribution[0].second,
                                        restriction_energy ));
}

//---------------------------------------------------------------------------//
FRENSIE_UNIT_TEST( AceLaw11NuclearScatteringEnergyDistribution,
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

   FRENSIE_CHECK_EQUAL(distribution.sampleEnergy(3.0),
     Utility::WattDistribution::sample( 3.0,
                                        a_distribution[1].second,
                                        b_distribution[1].second,
                                        restriction_energy ));
}

//---------------------------------------------------------------------------//
FRENSIE_UNIT_TEST( AceLaw11NuclearScatteringEnergyDistribution,
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

   FRENSIE_CHECK_EQUAL(distribution.sampleEnergy(1.5),
     Utility::WattDistribution::sample( 1.5,
                                        1.5,
                                        3.5,
                                        restriction_energy ));
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
// tstAceLaw11NuclearScatteringDistribution.cpp
//---------------------------------------------------------------------------//
