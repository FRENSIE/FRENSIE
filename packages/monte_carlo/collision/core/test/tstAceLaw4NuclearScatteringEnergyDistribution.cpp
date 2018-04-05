//---------------------------------------------------------------------------//
//!
//! \file   tstAceLaw4NuclearScatteringDistribution.cpp
//! \author Alex Bennett
//! \brief  Law 4 neutron scattering distribution unit tests
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_AceLaw4NuclearScatteringEnergyDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
FRENSIE_UNIT_TEST( AceLaw4NuclearScatteringEnergyDistribution,
		   sampleEnergy_lower_bound_histogram )
{
   MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution::EnergyDistribution
     energy_distribution(2);

   energy_distribution[0].first = 1.0;
   energy_distribution[1].first = 2.0;

   std::vector<double> outgoing_energy_grid(5);

   std::vector<double> pdf(4);

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

   MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution
     distribution( energy_distribution );

   FRENSIE_CHECK_FLOATING_EQUALITY(distribution.sampleEnergy(0.5), 3.0, 1e-15);
}

//---------------------------------------------------------------------------//
FRENSIE_UNIT_TEST( AceLaw4NuclearScatteringEnergyDistribution,
		   sampleEnergy_upper_bound_histogram )
{
   MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution::EnergyDistribution
     energy_distribution(2);

   energy_distribution[0].first = 1.0;
   energy_distribution[1].first = 2.0;

   std::vector<double> outgoing_energy_grid(5);

   std::vector<double> pdf(4);

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

   MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution
     distribution( energy_distribution );

   FRENSIE_CHECK_FLOATING_EQUALITY(distribution.sampleEnergy(2.5), 4.0, 1e-15);
}

//---------------------------------------------------------------------------//
FRENSIE_UNIT_TEST( AceLaw4NuclearScatteringEnergyDistribution,
		   sampleEnergy_histogram )
{
   MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution::EnergyDistribution
     energy_distribution(2);

   energy_distribution[0].first = 1.0;
   energy_distribution[1].first = 2.0;

   std::vector<double> outgoing_energy_grid(5);

   std::vector<double> pdf(4);

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

   MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution
     distribution( energy_distribution );

   FRENSIE_CHECK_FLOATING_EQUALITY(distribution.sampleEnergy(1.5), 3.5, 1e-15);
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
// tstAceLaw4NuclearScatteringDistribution.cpp
//---------------------------------------------------------------------------//
