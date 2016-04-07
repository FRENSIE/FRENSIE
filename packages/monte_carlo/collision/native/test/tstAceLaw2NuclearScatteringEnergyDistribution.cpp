//---------------------------------------------------------------------------//
//!
//! \file   tstAceLaw2NuclearScatteringEnergyDistribution.cpp
//! \author Eli Moll
//! \brief  Ace law 2 neutron scattering energy distribution unit tests
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
#include "MonteCarlo_AceLaw2NuclearScatteringEnergyDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"


//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( AceLaw2NuclearScatteringEnergyDistribution, 
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

   TEST_COMPARE(distribution_0.sampleEnergy(2.0) ,==, 1.0)
   TEST_COMPARE(distribution_1.sampleEnergy(2.0) ,==, 1.0)
}

//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( AceLaw2NuclearScatteringEnergyDistribution, 
		   sampleEnergy_LP_is_2 )
{
   int LP_2 = 2;
   double EG = 1.0;
   const double atomic_weight_ratio = 1.0;
   
   MonteCarlo::AceLaw2NuclearScatteringEnergyDistribution distribution_2( 
                                                      LP_2,
                                                      EG,
                                                      atomic_weight_ratio );

   TEST_COMPARE(distribution_2.sampleEnergy(2.0) ,==, 2.0)
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
