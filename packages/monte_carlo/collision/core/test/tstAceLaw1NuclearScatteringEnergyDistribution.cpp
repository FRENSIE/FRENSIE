//---------------------------------------------------------------------------//
//!
//! \file   tstAceLaw1NuclearScatteringEnergyDistribution.cpp
//! \author Alex Bennett
//! \brief  Ace law 1 neutron scattering energy distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_AceLaw1NuclearScatteringEnergyDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
FRENSIE_UNIT_TEST( AceLaw1NuclearScatteringEnergyDistribution,
		   sampleEnergy_lower_bound )
{
   MonteCarlo::AceLaw1NuclearScatteringEnergyDistribution::EnergyDistArray
     energy_grid;

   energy_grid.resize(2);

   energy_grid[0].first = 1.0;
   energy_grid[0].second.resize(5);
   energy_grid[0].second[0] = 1.0;
   energy_grid[0].second[1] = 2.0;
   energy_grid[0].second[2] = 3.0;
   energy_grid[0].second[3] = 4.0;
   energy_grid[0].second[4] = 5.0;

   energy_grid[1].first = 2.0;
   energy_grid[1].second.resize(5);
   energy_grid[1].second[0] = 2.0;
   energy_grid[1].second[1] = 3.0;
   energy_grid[1].second[2] = 4.0;
   energy_grid[1].second[3] = 5.0;
   energy_grid[1].second[4] = 6.0;

   // Create the fake stream
   std::vector<double> fake_stream( 1 );
   fake_stream[0] = 0.5;

   Utility::RandomNumberGenerator::setFakeStream( fake_stream );

   MonteCarlo::AceLaw1NuclearScatteringEnergyDistribution distribution( energy_grid );

   FRENSIE_CHECK_EQUAL( distribution.sampleEnergy(0.5), 3)
}

//---------------------------------------------------------------------------//
FRENSIE_UNIT_TEST( AceLaw1NuclearScatteringEnergyDistribution,
		   sampleEnergy_upper_bound )
{
   MonteCarlo::AceLaw1NuclearScatteringEnergyDistribution::EnergyDistArray energy_grid;

   energy_grid.resize(2);

   energy_grid[0].first = 1.0;
   energy_grid[0].second.resize(5);
   energy_grid[0].second[0] = 1.0;
   energy_grid[0].second[1] = 2.0;
   energy_grid[0].second[2] = 3.0;
   energy_grid[0].second[3] = 4.0;
   energy_grid[0].second[4] = 5.0;

   energy_grid[1].first = 2.0;
   energy_grid[1].second.resize(5);
   energy_grid[1].second[0] = 2.0;
   energy_grid[1].second[1] = 3.0;
   energy_grid[1].second[2] = 4.0;
   energy_grid[1].second[3] = 5.0;
   energy_grid[1].second[4] = 6.0;

   // Create the fake stream
   std::vector<double> fake_stream( 1 );
   fake_stream[0] = 0.5;

   Utility::RandomNumberGenerator::setFakeStream( fake_stream );

   MonteCarlo::AceLaw1NuclearScatteringEnergyDistribution distribution( energy_grid );

   FRENSIE_CHECK_EQUAL(distribution.sampleEnergy(3.0), 4)
}

//---------------------------------------------------------------------------//
FRENSIE_UNIT_TEST( AceLaw1NuclearScatteringEnergyDistribution,
		   sampleEnergy )
{
   MonteCarlo::AceLaw1NuclearScatteringEnergyDistribution::EnergyDistArray energy_grid;

   energy_grid.resize(2);

   energy_grid[0].first = 1.0;
   energy_grid[0].second.resize(5);
   energy_grid[0].second[0] = 1.0;
   energy_grid[0].second[1] = 2.0;
   energy_grid[0].second[2] = 3.0;
   energy_grid[0].second[3] = 4.0;
   energy_grid[0].second[4] = 5.0;

   energy_grid[1].first = 2.0;
   energy_grid[1].second.resize(5);
   energy_grid[1].second[0] = 2.0;
   energy_grid[1].second[1] = 3.0;
   energy_grid[1].second[2] = 4.0;
   energy_grid[1].second[3] = 5.0;
   energy_grid[1].second[4] = 6.0;

   // Create the fake stream
   std::vector<double> fake_stream( 3 );
   fake_stream[0] = 0.5;
   fake_stream[1] = 0.75;
   fake_stream[2] = 0.5;

   Utility::RandomNumberGenerator::setFakeStream( fake_stream );

   MonteCarlo::AceLaw1NuclearScatteringEnergyDistribution distribution( energy_grid );

   FRENSIE_CHECK_EQUAL( distribution.sampleEnergy(1.5), 4 )
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
// tstAceLaw1NuclearScatteringDistribution.cpp
//---------------------------------------------------------------------------//
