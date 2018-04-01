//---------------------------------------------------------------------------//
//!
//! \file   tstAceLaw2NuclearScatteringEnergyDistribution.cpp
//! \author Eli Moll
//! \brief  Ace law 2 neutron scattering energy distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_AceLaw2NuclearScatteringEnergyDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
FRENSIE_UNIT_TEST( AceLaw2NuclearScatteringEnergyDistribution,
		   sampleEnergy_LP_is_0_or_1 )
{
   int LP_0 = 0;
   int LP_1 = 1;
   double EG = 1.0;
   const double atomic_weight_ratio = 1.0;

   MonteCarlo::AceLaw2NuclearScatteringEnergyDistribution distribution_0(
                                                      LP_0,
                                                      EG,
                                                      atomic_weight_ratio );

   MonteCarlo::AceLaw2NuclearScatteringEnergyDistribution distribution_1(
                                                      LP_0,
                                                      EG,
                                                      atomic_weight_ratio );

   FRENSIE_CHECK_EQUAL(distribution_0.sampleEnergy(2.0), 1.0)
   FRENSIE_CHECK_EQUAL(distribution_1.sampleEnergy(2.0), 1.0)
}

//---------------------------------------------------------------------------//
FRENSIE_UNIT_TEST( AceLaw2NuclearScatteringEnergyDistribution,
		   sampleEnergy_LP_is_2 )
{
   int LP_2 = 2;
   double EG = 1.0;
   const double atomic_weight_ratio = 1.0;

   MonteCarlo::AceLaw2NuclearScatteringEnergyDistribution distribution_2(
                                                      LP_2,
                                                      EG,
                                                      atomic_weight_ratio );

   FRENSIE_CHECK_EQUAL(distribution_2.sampleEnergy(2.0), 2.0)
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
// tstAceLaw5NuclearScatteringDistribution.cpp
//---------------------------------------------------------------------------//
