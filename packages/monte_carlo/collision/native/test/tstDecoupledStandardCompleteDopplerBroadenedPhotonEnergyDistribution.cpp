//---------------------------------------------------------------------------//
//!
//! \file   tstDecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution.cpp
//! \author Alex Robinson
//! \brief  Decoupled complete DB photon energy distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_UnitTestHarnessExtensions.hpp"
#include "MonteCarlo_DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "MonteCarlo_ComptonProfilePolicy.hpp"
#include "MonteCarlo_ComptonProfileHelpers.hpp"
#include "MonteCarlo_ComptonProfileSubshellConverterFactory.hpp"
#include "MonteCarlo_StandardComptonProfile.hpp"
#include "MonteCarlo_SubshellType.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_AtomicMomentumUnit.hpp"
#include "Utility_InverseAtomicMomentumUnit.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::DopplerBroadenedPhotonEnergyDistribution> 
  half_distribution;

Teuchos::RCP<MonteCarlo::CompleteDopplerBroadenedPhotonEnergyDistribution> 
  half_complete_distribution;

Teuchos::RCP<MonteCarlo::DopplerBroadenedPhotonEnergyDistribution> 
  full_distribution;

Teuchos::RCP<MonteCarlo::CompleteDopplerBroadenedPhotonEnergyDistribution> 
  full_complete_distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check if the distribution is complete
TEUCHOS_UNIT_TEST( 
             DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution,
             isComplete )
{
  TEST_ASSERT( half_distribution->isComplete() );

  TEST_ASSERT( full_distribution->isComplete() );
}
                  
//---------------------------------------------------------------------------//
// Check if a subshell is valid
TEUCHOS_UNIT_TEST( 
             DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution,
             isValidSubshell )
{
  // Half distribution
  TEST_ASSERT( half_complete_distribution->isValidSubshell( 
                                                    MonteCarlo::K_SUBSHELL ) );
  TEST_ASSERT( half_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::L1_SUBSHELL ) );
  TEST_ASSERT( half_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::L2_SUBSHELL ) );
  TEST_ASSERT( half_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::L3_SUBSHELL ) );
  TEST_ASSERT( half_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::M1_SUBSHELL ) );
  TEST_ASSERT( half_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::M2_SUBSHELL ) );
  TEST_ASSERT( half_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::M3_SUBSHELL ) );
  TEST_ASSERT( half_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::M4_SUBSHELL ) );
  TEST_ASSERT( half_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::M5_SUBSHELL ) );
  TEST_ASSERT( half_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::N1_SUBSHELL ) );
  TEST_ASSERT( half_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::N2_SUBSHELL ) );
  TEST_ASSERT( half_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::N3_SUBSHELL ) );
  TEST_ASSERT( half_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::N4_SUBSHELL ) );
  TEST_ASSERT( half_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::N5_SUBSHELL ) );
  TEST_ASSERT( half_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::N6_SUBSHELL ) );
  TEST_ASSERT( half_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::N7_SUBSHELL ) );
  TEST_ASSERT( half_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::O1_SUBSHELL ) );
  TEST_ASSERT( half_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::O2_SUBSHELL ) );
  TEST_ASSERT( half_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::O3_SUBSHELL ) );
  TEST_ASSERT( half_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::O4_SUBSHELL ) );
  TEST_ASSERT( half_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::O5_SUBSHELL ) );
  TEST_ASSERT( half_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::P1_SUBSHELL ) );
  TEST_ASSERT( half_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::P2_SUBSHELL ) );
  TEST_ASSERT( half_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::P3_SUBSHELL ) );
  TEST_ASSERT( !half_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::Q3_SUBSHELL ) );
  TEST_ASSERT( !half_complete_distribution->isValidSubshell( 
                                              MonteCarlo::INVALID_SUBSHELL ) );
  TEST_ASSERT( !half_complete_distribution->isValidSubshell( 
                                              MonteCarlo::UNKNOWN_SUBSHELL ) );

  // Full distribution
  TEST_ASSERT( full_complete_distribution->isValidSubshell( 
                                                    MonteCarlo::K_SUBSHELL ) );
  TEST_ASSERT( full_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::L1_SUBSHELL ) );
  TEST_ASSERT( full_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::L2_SUBSHELL ) );
  TEST_ASSERT( full_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::L3_SUBSHELL ) );
  TEST_ASSERT( full_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::M1_SUBSHELL ) );
  TEST_ASSERT( full_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::M2_SUBSHELL ) );
  TEST_ASSERT( full_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::M3_SUBSHELL ) );
  TEST_ASSERT( full_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::M4_SUBSHELL ) );
  TEST_ASSERT( full_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::M5_SUBSHELL ) );
  TEST_ASSERT( full_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::N1_SUBSHELL ) );
  TEST_ASSERT( full_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::N2_SUBSHELL ) );
  TEST_ASSERT( full_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::N3_SUBSHELL ) );
  TEST_ASSERT( full_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::N4_SUBSHELL ) );
  TEST_ASSERT( full_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::N5_SUBSHELL ) );
  TEST_ASSERT( full_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::N6_SUBSHELL ) );
  TEST_ASSERT( full_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::N7_SUBSHELL ) );
  TEST_ASSERT( full_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::O1_SUBSHELL ) );
  TEST_ASSERT( full_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::O2_SUBSHELL ) );
  TEST_ASSERT( full_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::O3_SUBSHELL ) );
  TEST_ASSERT( full_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::O4_SUBSHELL ) );
  TEST_ASSERT( full_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::O5_SUBSHELL ) );
  TEST_ASSERT( full_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::P1_SUBSHELL ) );
  TEST_ASSERT( full_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::P2_SUBSHELL ) );
  TEST_ASSERT( full_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::P3_SUBSHELL ) );
  TEST_ASSERT( !full_complete_distribution->isValidSubshell( 
                                                   MonteCarlo::Q3_SUBSHELL ) );
  TEST_ASSERT( !full_complete_distribution->isValidSubshell( 
                                              MonteCarlo::INVALID_SUBSHELL ) );
  TEST_ASSERT( !full_complete_distribution->isValidSubshell( 
                                              MonteCarlo::UNKNOWN_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check that the subshell binding energy can be returned
TEUCHOS_UNIT_TEST( 
             DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution,
             getSubshellBindingEnergy )
{
  // Half distribution 
  TEST_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                      MonteCarlo::K_SUBSHELL ),
                          0.088005,
                          1e-15 );
  TEST_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::L1_SUBSHELL ),
                          0.015861,
                          1e-15 );
  TEST_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::L2_SUBSHELL ),
                          0.0152,
                          1e-15 );
  TEST_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::L3_SUBSHELL ),
                          0.013035,
                          1e-15 );
  TEST_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::M1_SUBSHELL ),
                          0.003851,
                          1e-15 );
  TEST_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::M2_SUBSHELL ),
                          0.003554,
                          1e-15 );
  TEST_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::M3_SUBSHELL ),
                          0.003066,
                          1e-15 );
  TEST_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::M4_SUBSHELL ),
                          0.002586,
                          1e-15 );
  TEST_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::M5_SUBSHELL ),
                          0.002484,
                          1e-15 );
  TEST_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::N1_SUBSHELL ),
                          0.000894,
                          1e-15 );
  TEST_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::N2_SUBSHELL ),
                          0.000764,
                          1e-15 );
  TEST_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::N3_SUBSHELL ),
                          0.000645,
                          1e-15 );
  TEST_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::N4_SUBSHELL ),
                          0.000434,
                          1e-15 );
  TEST_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::N5_SUBSHELL ),
                          0.000412,
                          1e-15 );
  TEST_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::N6_SUBSHELL ),
                          0.000141,
                          1e-15 );
  TEST_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::N7_SUBSHELL ),
                          0.000136,
                          1e-15 );
  TEST_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::O1_SUBSHELL ),
                          0.000148,
                          1e-15 );
  TEST_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::O2_SUBSHELL ),
                          0.000105,
                          1e-15 );
  TEST_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::O3_SUBSHELL ),
                          8.6e-5,
                          1e-15 );
  TEST_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::O4_SUBSHELL ),
                          2.0e-5,
                          1e-15 );
  TEST_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::O5_SUBSHELL ),
                          1.8e-5,
                          1e-15 );
  TEST_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::P1_SUBSHELL ),
                          0.0,
                          1e-15 );
  TEST_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::P2_SUBSHELL ),
                          0.0,
                          1e-15 );
  TEST_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::P3_SUBSHELL ),
                          0.0,
                          1e-15 );

  // Full distribution
  TEST_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                      MonteCarlo::K_SUBSHELL ),
                          0.088005,
                          1e-15 );
  TEST_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::L1_SUBSHELL ),
                          0.015861,
                          1e-15 );
  TEST_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::L2_SUBSHELL ),
                          0.0152,
                          1e-15 );
  TEST_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::L3_SUBSHELL ),
                          0.013035,
                          1e-15 );
  TEST_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::M1_SUBSHELL ),
                          0.003851,
                          1e-15 );
  TEST_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::M2_SUBSHELL ),
                          0.003554,
                          1e-15 );
  TEST_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::M3_SUBSHELL ),
                          0.003066,
                          1e-15 );
  TEST_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::M4_SUBSHELL ),
                          0.002586,
                          1e-15 );
  TEST_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::M5_SUBSHELL ),
                          0.002484,
                          1e-15 );
  TEST_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::N1_SUBSHELL ),
                          0.000894,
                          1e-15 );
  TEST_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::N2_SUBSHELL ),
                          0.000764,
                          1e-15 );
  TEST_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::N3_SUBSHELL ),
                          0.000645,
                          1e-15 );
  TEST_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::N4_SUBSHELL ),
                          0.000434,
                          1e-15 );
  TEST_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::N5_SUBSHELL ),
                          0.000412,
                          1e-15 );
  TEST_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::N6_SUBSHELL ),
                          0.000141,
                          1e-15 );
  TEST_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::N7_SUBSHELL ),
                          0.000136,
                          1e-15 );
  TEST_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::O1_SUBSHELL ),
                          0.000148,
                          1e-15 );
  TEST_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::O2_SUBSHELL ),
                          0.000105,
                          1e-15 );
  TEST_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::O3_SUBSHELL ),
                          8.6e-5,
                          1e-15 );
  TEST_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::O4_SUBSHELL ),
                          2.0e-5,
                          1e-15 );
  TEST_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::O5_SUBSHELL ),
                          1.8e-5,
                          1e-15 );
  TEST_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::P1_SUBSHELL ),
                          0.0,
                          1e-15 );
  TEST_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::P2_SUBSHELL ),
                          0.0,
                          1e-15 );
  TEST_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     MonteCarlo::P3_SUBSHELL ),
                          0.0,
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the subshell occupancy can be returned
TEUCHOS_UNIT_TEST( 
             DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution,
             getSubshellOccupancy )
{
  // Half distribution
  TEST_EQUALITY_CONST( half_complete_distribution->getSubshellOccupancy(
                                                      MonteCarlo::K_SUBSHELL ),
                       2 );
  TEST_EQUALITY_CONST( half_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::L1_SUBSHELL ),
                       2 );
  TEST_EQUALITY_CONST( half_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::L2_SUBSHELL ),
                       2 );
  TEST_EQUALITY_CONST( half_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::L3_SUBSHELL ),
                       4 );
  TEST_EQUALITY_CONST( half_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::M1_SUBSHELL ),
                       2 );
  TEST_EQUALITY_CONST( half_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::M2_SUBSHELL ),
                       2 );
  TEST_EQUALITY_CONST( half_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::M3_SUBSHELL ),
                       4 );
  TEST_EQUALITY_CONST( half_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::M4_SUBSHELL ),
                       4 );
  TEST_EQUALITY_CONST( half_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::M5_SUBSHELL ),
                       6 );
  TEST_EQUALITY_CONST( half_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::N1_SUBSHELL ),
                       2 );
  TEST_EQUALITY_CONST( half_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::N2_SUBSHELL ),
                       2 );
  TEST_EQUALITY_CONST( half_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::N3_SUBSHELL ),
                       4 );
  TEST_EQUALITY_CONST( half_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::N4_SUBSHELL ),
                       4 );
  TEST_EQUALITY_CONST( half_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::N5_SUBSHELL ),
                       6 );
  TEST_EQUALITY_CONST( half_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::N6_SUBSHELL ),
                       6 );
  TEST_EQUALITY_CONST( half_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::N7_SUBSHELL ),
                       8 );
  TEST_EQUALITY_CONST( half_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::O1_SUBSHELL ),
                       2 );
  TEST_EQUALITY_CONST( half_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::O2_SUBSHELL ),
                       2 );
  TEST_EQUALITY_CONST( half_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::O3_SUBSHELL ),
                       4 );
  TEST_EQUALITY_CONST( half_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::O4_SUBSHELL ),
                       4 );
  TEST_EQUALITY_CONST( half_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::O5_SUBSHELL ),
                       6 );
  TEST_EQUALITY_CONST( half_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::P1_SUBSHELL ),
                       2 );
  TEST_EQUALITY_CONST( half_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::P2_SUBSHELL ),
                       2 );
  TEST_EQUALITY_CONST( half_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::P3_SUBSHELL ),
                       2 );

  // Full distribution
  TEST_EQUALITY_CONST( full_complete_distribution->getSubshellOccupancy(
                                                      MonteCarlo::K_SUBSHELL ),
                       2 );
  TEST_EQUALITY_CONST( full_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::L1_SUBSHELL ),
                       2 );
  TEST_EQUALITY_CONST( full_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::L2_SUBSHELL ),
                       2 );
  TEST_EQUALITY_CONST( full_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::L3_SUBSHELL ),
                       4 );
  TEST_EQUALITY_CONST( full_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::M1_SUBSHELL ),
                       2 );
  TEST_EQUALITY_CONST( full_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::M2_SUBSHELL ),
                       2 );
  TEST_EQUALITY_CONST( full_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::M3_SUBSHELL ),
                       4 );
  TEST_EQUALITY_CONST( full_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::M4_SUBSHELL ),
                       4 );
  TEST_EQUALITY_CONST( full_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::M5_SUBSHELL ),
                       6 );
  TEST_EQUALITY_CONST( full_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::N1_SUBSHELL ),
                       2 );
  TEST_EQUALITY_CONST( full_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::N2_SUBSHELL ),
                       2 );
  TEST_EQUALITY_CONST( full_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::N3_SUBSHELL ),
                       4 );
  TEST_EQUALITY_CONST( full_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::N4_SUBSHELL ),
                       4 );
  TEST_EQUALITY_CONST( full_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::N5_SUBSHELL ),
                       6 );
  TEST_EQUALITY_CONST( full_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::N6_SUBSHELL ),
                       6 );
  TEST_EQUALITY_CONST( full_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::N7_SUBSHELL ),
                       8 );
  TEST_EQUALITY_CONST( full_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::O1_SUBSHELL ),
                       2 );
  TEST_EQUALITY_CONST( full_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::O2_SUBSHELL ),
                       2 );
  TEST_EQUALITY_CONST( full_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::O3_SUBSHELL ),
                       4 );
  TEST_EQUALITY_CONST( full_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::O4_SUBSHELL ),
                       4 );
  TEST_EQUALITY_CONST( full_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::O5_SUBSHELL ),
                       6 );
  TEST_EQUALITY_CONST( full_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::P1_SUBSHELL ),
                       2 );
  TEST_EQUALITY_CONST( full_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::P2_SUBSHELL ),
                       2 );
  TEST_EQUALITY_CONST( full_complete_distribution->getSubshellOccupancy(
                                                     MonteCarlo::P3_SUBSHELL ),
                       2 );
}

//---------------------------------------------------------------------------//
// Check that the subshell distribution can be evaluated
TEUCHOS_UNIT_TEST( 
             DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution,
             evaluateSubshell_half )
{
  // Above max energy
  double cross_section = half_complete_distribution->evaluateSubshell(
                                                      0.5,
                                                      0.412,
                                                      0.0,
                                                      MonteCarlo::K_SUBSHELL );
  
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  // Max energy
  cross_section = half_complete_distribution->evaluateSubshell(
                                                      0.5,
                                                      0.411995,
                                                      0.0,
                                                      MonteCarlo::K_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section, 
                          0.077179060436207,
                          1e-15 );

  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                                                      0.5,
                                                      0.25271981255859755,
                                                      0.0,
                                                      MonteCarlo::K_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          0.24747240367306983,
                          1e-15 );

  // Min energy (for Compton profile grid)
  cross_section = half_complete_distribution->evaluateSubshell(
                                                      0.5,
                                                      0.0666690829629601,
                                                      0.0,
                                                      MonteCarlo::K_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          0.02805809565454027,
                          1e-15 );

  // Below min energy (for Compton profile grid)
  cross_section = half_complete_distribution->evaluateSubshell(
                                                      0.5,
                                                      0.066,
                                                      0.0,
                                                      MonteCarlo::K_SUBSHELL );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::L1_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          0.815395566418701,
                          1e-15 );

  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::L2_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          0.38629223432666243,
                          1e-15 );

  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::L3_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          0.8794650180059378,
                          1e-15 );

  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::M1_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          1.7621319119578402,
                          1e-15 );

  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::M2_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          1.0192161806966558,
                          1e-15 );

  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::M3_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.2227112051752336,
                          1e-15 );

  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::M4_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          1.4364930672258214,
                          1e-15 );
  
  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::M5_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.2113525633910784,
                          1e-15 );
  
  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::N1_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          3.6032956960778817,
                          1e-15 );
  
  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::N2_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.2703919059658135,
                          1e-15 );

  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::N3_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          4.928318122205952,
                          1e-15 );

  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::N4_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          3.662541834095016,
                          1e-15 );

  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::N5_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          5.625556432361759,
                          1e-15 );
  
  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::N6_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          4.626950854598549,
                          1e-15 );
  
  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::N7_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          6.233749824572172,
                          1e-15 );
  
  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::O1_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          8.385783818059283,
                          1e-15 );

  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::O2_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          5.509760603731998,
                          1e-15 );

  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::O3_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          12.163527895643893,
                          1e-15 );

  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::O4_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          11.315733485067268,
                          1e-15 );

  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::O5_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          17.448311930633853,
                          1e-15 );

  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::P1_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          26.794039864962183,
                          1e-14 );
  
  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::P2_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          20.841524452812,
                          1e-15 );
 
  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::P3_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          20.841524452812,
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the subshell distribution can be evaluated
TEUCHOS_UNIT_TEST( 
             DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution,
             evaluateSubshell_full )
{
  // Above max energy
  double cross_section = full_complete_distribution->evaluateSubshell(
                                                      0.5,
                                                      0.412,
                                                      0.0,
                                                      MonteCarlo::K_SUBSHELL );
  
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  // Max energy
  cross_section = full_complete_distribution->evaluateSubshell(
                                                      0.5,
                                                      0.411995,
                                                      0.0,
                                                      MonteCarlo::K_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section, 
                          0.077179060436207,
                          1e-15 );

  // Compton-line energy
  cross_section = full_complete_distribution->evaluateSubshell(
                                                      0.5,
                                                      0.25271981255859755,
                                                      0.0,
                                                      MonteCarlo::K_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          0.24747240367306983,
                          1e-15 );

  // Min energy
  cross_section = full_complete_distribution->evaluateSubshell(
                                                      0.5,
                                                      0.0,
                                                      0.0,
                                                      MonteCarlo::K_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          0.009842522369949987,
                          1e-15 ); 

  // Compton-line energy
  cross_section = full_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::L1_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          0.815395566418701,
                          1e-15 );

  // Compton-line energy
  cross_section = full_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::L2_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          0.38629223432666243,
                          1e-15 );

  // Compton-line energy
  cross_section = full_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::L3_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          0.8794650180059378,
                          1e-15 );

  // Compton-line energy
  cross_section = full_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::M1_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          1.7621319119578402,
                          1e-15 );

  // Compton-line energy
  cross_section = full_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::M2_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          1.0192161806966558,
                          1e-15 );

  // Compton-line energy
  cross_section = full_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::M3_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.2227112051752336,
                          1e-15 );

  // Compton-line energy
  cross_section = full_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::M4_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          1.4364930672258214,
                          1e-15 );

  // Compton-line energy
  cross_section = full_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::M5_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.2113525633910784,
                          1e-15 );

  // Compton-line energy
  cross_section = full_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::N1_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          3.6032956960778817,
                          1e-15 );

  // Compton-line energy
  cross_section = full_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::N2_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.2703919059658135,
                          1e-15 );

  // Compton-line energy
  cross_section = full_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::N3_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          4.928318122205952,
                          1e-15 );

  // Compton-line energy
  cross_section = full_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::N4_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          3.662541834095016,
                          1e-15 );

  // Compton-line energy
  cross_section = full_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::N5_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          5.625556432361759,
                          1e-15 );

  // Compton-line energy
  cross_section = full_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::N6_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          4.626950854598549,
                          1e-15 );

  // Compton-line energy
  cross_section = full_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::N7_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          6.233749824572172,
                          1e-15 );

  // Compton-line energy
  cross_section = full_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::O1_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          8.385783818059283,
                          1e-15 );

  // Compton-line energy
  cross_section = full_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::O2_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          5.509760603731998,
                          1e-15 );

  // Compton-line energy
  cross_section = full_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::O3_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          12.163527895643893,
                          1e-15 );

  // Compton-line energy
  cross_section = full_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::O4_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          11.315733485067268,
                          1e-15 );

  // Compton-line energy
  cross_section = full_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::O5_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          17.448311930633853,
                          1e-15 );
  
  // Compton-line energy
  cross_section = full_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::P1_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          26.794039864962183,
                          1e-14 );

  // Compton-line energy
  cross_section = full_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::P2_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          20.841524452812,
                          1e-15 );
 
  // Compton-line energy
  cross_section = full_complete_distribution->evaluateSubshell(
                                                     0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::P3_SUBSHELL );

  TEST_FLOATING_EQUALITY( cross_section,
                          20.841524452812,
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the complete distribution can be evaluated
TEUCHOS_UNIT_TEST(
             DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution,
             evaluate )
{
  // Compton-line energy
  double cross_section = half_distribution->evaluate( 0.5,
                                                      0.25271981255859755,
                                                      0.0 );

  TEST_FLOATING_EQUALITY( cross_section, 144.39001687165862, 1e-15 );

  // Compton-line energy
  cross_section = full_distribution->evaluate( 0.5,
                                               0.25271981255859755,
                                               0.0 );

  TEST_FLOATING_EQUALITY( cross_section, 144.39001687165862, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the subshell integrated cross section can be evaluated
TEUCHOS_UNIT_TEST(
             DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution,
             evaluateSubshellIntegratedCrossSection_half )
{
  double cross_section = 
    half_complete_distribution->evaluateSubshellIntegratedCrossSection( 
                                                        0.5,
                                                        0.0,
                                                        MonteCarlo::K_SUBSHELL,
                                                        1e-3 );

  TEST_FLOATING_EQUALITY( cross_section, 0.0506787976678307606, 1e-12 );
  
  cross_section = 
    half_complete_distribution->evaluateSubshellIntegratedCrossSection( 
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::L1_SUBSHELL,
                                                       1e-3 );
                                                              
  TEST_FLOATING_EQUALITY( cross_section, 0.0539421594075661509, 1e-12 );

  cross_section = 
    half_complete_distribution->evaluateSubshellIntegratedCrossSection( 
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::L2_SUBSHELL,
                                                       1e-3 );

  TEST_FLOATING_EQUALITY( cross_section, 0.0544804774400405936, 1e-12 );

  cross_section = 
    half_complete_distribution->evaluateSubshellIntegratedCrossSection( 
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::L3_SUBSHELL,
                                                       1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.108643678063119545, 1e-12 );

  cross_section = 
    half_complete_distribution->evaluateSubshellIntegratedCrossSection( 
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::M1_SUBSHELL,
                                                       1e-3 );

  TEST_FLOATING_EQUALITY( cross_section, 0.0537557438879969415, 1e-12 );
  
  cross_section = 
    half_complete_distribution->evaluateSubshellIntegratedCrossSection(
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::M2_SUBSHELL,
                                                       1e-3 );

  TEST_FLOATING_EQUALITY( cross_section, 0.0538845285472215121, 1e-12 );

  cross_section = 
    half_complete_distribution->evaluateSubshellIntegratedCrossSection(
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::M3_SUBSHELL,
                                                       1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.107670237956284012, 1e-12 );

  cross_section = 
    half_complete_distribution->evaluateSubshellIntegratedCrossSection(
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::M4_SUBSHELL,
                                                       1e-3 );

  TEST_FLOATING_EQUALITY( cross_section, 0.107645274793230467, 1e-12 );

  cross_section = 
    half_complete_distribution->evaluateSubshellIntegratedCrossSection(
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::M5_SUBSHELL,
                                                       1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.161418283770527915, 1e-12 );

  cross_section = 
    half_complete_distribution->evaluateSubshellIntegratedCrossSection(
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::N1_SUBSHELL,
                                                       1e-3 );

  TEST_FLOATING_EQUALITY( cross_section, 0.0536342777913152297, 1e-12 );
 
  cross_section = 
    half_complete_distribution->evaluateSubshellIntegratedCrossSection(
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::N2_SUBSHELL,
                                                       1e-3 );

  TEST_FLOATING_EQUALITY( cross_section, 0.053665026335982989, 1e-12 );

  cross_section = 
    half_complete_distribution->evaluateSubshellIntegratedCrossSection(
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::N3_SUBSHELL,
                                                       1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.10729807014692927, 1e-12 );

  cross_section = 
    half_complete_distribution->evaluateSubshellIntegratedCrossSection(
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::N4_SUBSHELL,
                                                       1e-3 );

  TEST_FLOATING_EQUALITY( cross_section, 0.107276124378478083, 1e-12 );

  cross_section = 
    half_complete_distribution->evaluateSubshellIntegratedCrossSection(
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::N5_SUBSHELL,
                                                       1e-3 );

  TEST_FLOATING_EQUALITY( cross_section, 0.160895822405358047, 1e-12 );

  cross_section = 
    half_complete_distribution->evaluateSubshellIntegratedCrossSection(
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::N6_SUBSHELL,
                                                       1e-3 );

  TEST_FLOATING_EQUALITY( cross_section, 0.160854431039325119, 1e-12 );

  cross_section = 
    half_complete_distribution->evaluateSubshellIntegratedCrossSection(
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::N7_SUBSHELL,
                                                       1e-3 );

  TEST_FLOATING_EQUALITY( cross_section, 0.21446862724054877, 1e-12 );

  cross_section = 
    half_complete_distribution->evaluateSubshellIntegratedCrossSection(
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::O1_SUBSHELL,
                                                       1e-3 );

  TEST_FLOATING_EQUALITY( cross_section, 0.0535797701764630513, 1e-12 );

  cross_section = 
    half_complete_distribution->evaluateSubshellIntegratedCrossSection(
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::O2_SUBSHELL,
                                                       1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.0535831274038866892, 1e-12 );
  
  cross_section = 
    half_complete_distribution->evaluateSubshellIntegratedCrossSection(
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::O3_SUBSHELL,
                                                       1e-3 );

  TEST_FLOATING_EQUALITY( cross_section, 0.107157222253782866, 1e-12 );

  cross_section = 
    half_complete_distribution->evaluateSubshellIntegratedCrossSection(
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::O4_SUBSHELL,
                                                       1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.107143514635324733, 1e-12 );

  cross_section = 
    half_complete_distribution->evaluateSubshellIntegratedCrossSection(
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::O5_SUBSHELL,
                                                       1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.16071289870148503, 1e-12 );
  
  cross_section = 
    half_complete_distribution->evaluateSubshellIntegratedCrossSection(
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::P1_SUBSHELL,
                                                       1e-3 );

  TEST_FLOATING_EQUALITY( cross_section, 0.0535621266370162954, 1e-12 );

  cross_section = 
    half_complete_distribution->evaluateSubshellIntegratedCrossSection(
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::P2_SUBSHELL,
                                                       1e-3 );

  TEST_FLOATING_EQUALITY( cross_section, 0.0535613424402932373, 1e-12 );

  cross_section = 
    half_complete_distribution->evaluateSubshellIntegratedCrossSection(
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::P3_SUBSHELL,
                                                       1e-3 );

  TEST_FLOATING_EQUALITY( cross_section, 0.0535613424402932373, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the subshell integrated cross section can be evaluated
TEUCHOS_UNIT_TEST(
             DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution,
             evaluateSubshellIntegratedCrossSection_full )
{
  double cross_section = 
    full_complete_distribution->evaluateSubshellIntegratedCrossSection( 
                                                        0.5,
                                                        0.0,
                                                        MonteCarlo::K_SUBSHELL,
                                                        1e-3 );

  TEST_FLOATING_EQUALITY( cross_section, 0.0519379030758085128, 1e-12 );
  
  cross_section = 
    full_complete_distribution->evaluateSubshellIntegratedCrossSection( 
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::L1_SUBSHELL,
                                                       1e-3 );
                                                              
  TEST_FLOATING_EQUALITY( cross_section, 0.0542261359375576096, 1e-12 );
  
  cross_section = 
    full_complete_distribution->evaluateSubshellIntegratedCrossSection( 
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::L2_SUBSHELL,
                                                       1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.0545496676195199245, 1e-12 );

  cross_section = 
    full_complete_distribution->evaluateSubshellIntegratedCrossSection( 
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::L3_SUBSHELL,
                                                       1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.108712226617216717, 1e-12 );

  cross_section = 
    full_complete_distribution->evaluateSubshellIntegratedCrossSection( 
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::M1_SUBSHELL,
                                                       1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.0538286427776931836, 1e-12 );
  
  cross_section = 
    full_complete_distribution->evaluateSubshellIntegratedCrossSection(
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::M2_SUBSHELL,
                                                       1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.0539132788874106678, 1e-12 );

  cross_section = 
    full_complete_distribution->evaluateSubshellIntegratedCrossSection(
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::M3_SUBSHELL,
                                                       1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.107691472905151867, 1e-12 );

  cross_section = 
    full_complete_distribution->evaluateSubshellIntegratedCrossSection(
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::M4_SUBSHELL,
                                                       1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.107646395205054715, 1e-12 );

  cross_section = 
    full_complete_distribution->evaluateSubshellIntegratedCrossSection(
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::M5_SUBSHELL,
                                                       1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.161419179774725308, 1e-12 );

  cross_section = 
    full_complete_distribution->evaluateSubshellIntegratedCrossSection(
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::N1_SUBSHELL,
                                                       1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.0536534010499861644, 1e-12 );
 
  cross_section = 
    full_complete_distribution->evaluateSubshellIntegratedCrossSection(
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::N2_SUBSHELL,
                                                       1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.0536725588587172869, 1e-12 );

  cross_section = 
    full_complete_distribution->evaluateSubshellIntegratedCrossSection(
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::N3_SUBSHELL,
                                                       1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.107304077175130422, 1e-12 );

  cross_section = 
    full_complete_distribution->evaluateSubshellIntegratedCrossSection(
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::N4_SUBSHELL,
                                                       1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.10727645774553729, 1e-12 );

  cross_section = 
    full_complete_distribution->evaluateSubshellIntegratedCrossSection(
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::N5_SUBSHELL,
                                                       1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.160896098697318413, 1e-12 );

  cross_section = 
    full_complete_distribution->evaluateSubshellIntegratedCrossSection(
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::N6_SUBSHELL,
                                                       1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.160854432895073562, 1e-12 );
  
  cross_section = 
    full_complete_distribution->evaluateSubshellIntegratedCrossSection(
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::N7_SUBSHELL,
                                                       1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.214468628834499186, 1e-12 );

  cross_section = 
    full_complete_distribution->evaluateSubshellIntegratedCrossSection(
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::O1_SUBSHELL,
                                                       1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.0535835334668938595, 1e-12 );

  cross_section = 
    full_complete_distribution->evaluateSubshellIntegratedCrossSection(
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::O2_SUBSHELL,
                                                       1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.0535845893672419471, 1e-12 );
  
  cross_section = 
    full_complete_distribution->evaluateSubshellIntegratedCrossSection(
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::O3_SUBSHELL,
                                                       1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.107158181783069198, 1e-12 );

  cross_section = 
    full_complete_distribution->evaluateSubshellIntegratedCrossSection(
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::O4_SUBSHELL,
                                                       1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.107143553741129008, 1e-12 );

  cross_section = 
    full_complete_distribution->evaluateSubshellIntegratedCrossSection(
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::O5_SUBSHELL,
                                                       1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.160712932063177688, 1e-12 );
  
  cross_section = 
    full_complete_distribution->evaluateSubshellIntegratedCrossSection(
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::P1_SUBSHELL,
                                                       1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.05356259121654907, 1e-12 );

  cross_section = 
    full_complete_distribution->evaluateSubshellIntegratedCrossSection(
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::P2_SUBSHELL,
                                                       1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.0535614418966963851, 1e-12 );

  cross_section = 
    full_complete_distribution->evaluateSubshellIntegratedCrossSection(
                                                       0.5,
                                                       0.0,
                                                       MonteCarlo::P3_SUBSHELL,
                                                       1e-3 );

  TEST_FLOATING_EQUALITY( cross_section, 0.0535614418966963851, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the complete integrated cross section can be evaluated
TEUCHOS_UNIT_TEST(
             DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution,
             evaluateIntegratedCrossSection )
{
  double cross_section = 
    half_complete_distribution->evaluateIntegratedCrossSection(
                                                              0.5, 0.0, 1e-4 );

  TEST_FLOATING_EQUALITY( cross_section, 2.1995115631200073, 1e-5 );

  cross_section = 
    full_complete_distribution->evaluateIntegratedCrossSection(
                                                              0.5, 0.0, 1e-4 );

  TEST_FLOATING_EQUALITY( cross_section, 2.201357381591158, 1e-4 );
}

//---------------------------------------------------------------------------//
// Check that the subshell PDF can be evaluated
TEUCHOS_UNIT_TEST( 
             DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution,
             evaluateSubshellPDF_half )
{
  // Compton-line energy
  double pdf_value = 
    half_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::K_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 4.8831545944539485, 1e-12 );
                                                     
  // Compton-line energy
  pdf_value = 
    half_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::L1_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 15.116109094889707, 1e-12 );

  // Compton-line energy
  pdf_value = 
    half_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::L2_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 7.090470797577038, 1e-12 );

  // Compton-line energy
  pdf_value = 
    half_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::L3_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 8.094948861129208, 1e-12 );

  // Compton-line energy
  pdf_value = 
    half_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::M1_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 32.78034651756172, 1e-12 );

  // Compton-line energy
  pdf_value = 
    half_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::M2_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 18.91482041646647, 1e-12 );

  // Compton-line energy
  pdf_value = 
    half_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::M3_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 20.64369177002927, 1e-12 );

  // Compton-line energy
  pdf_value = 
    half_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::M4_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 13.344692277344242, 1e-12 );
  
  // Compton-line energy
  pdf_value = 
    half_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::M5_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 13.699517252548263, 1e-12 );

  // Compton-line energy
  pdf_value = 
    half_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::N1_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 67.18270189258236, 1e-12 );
  
  // Compton-line energy
  pdf_value = 
    half_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::N2_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 42.30673235398174, 1e-12 );

  // Compton-line energy
  pdf_value = 
    half_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::N3_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 45.93109750676158, 1e-12 );

  // Compton-line energy
  pdf_value = 
    half_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::N4_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 34.14125794825788, 1e-12 );

  // Compton-line energy
  pdf_value = 
    half_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::N5_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 34.96396828867833, 1e-12 );

  // Compton-line energy
  pdf_value =
    half_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::N6_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 28.764833052484384, 1e-12 );

  // Compton-line energy
  pdf_value =
    half_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::N7_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 29.066021938865568, 1e-12 );
  
  // Compton-line energy
  pdf_value =
    half_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::O1_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 156.51026106384936, 1e-12 );

  // Compton-line energy
  pdf_value =
    half_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::O2_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 102.82640955616084, 1e-12 );

  // Compton-line energy
  pdf_value =
    half_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::O3_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 113.51104143812852, 1e-12 );
  
  // Compton-line energy
  pdf_value =
    half_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::O4_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 105.61286442377467, 1e-12 );
  
  // Compton-line energy
  pdf_value =
    half_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::O5_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 108.56821121149143, 1e-12 );
  
  // Compton-line energy
  pdf_value =
    half_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::P1_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 500.24227093412435, 1e-12 );
  
  // Compton-line energy
  pdf_value =
    half_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::P2_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 389.11505020705556, 1e-12 );
  
  // Compton-line energy
  pdf_value =
    half_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::P3_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 389.11505020705556, 1e-12 );

  // Check that the pdf evaluates to 1.0
  boost::function<double (double x)> double_diff_cs_wrapper = 
    boost::bind<double>( &MonteCarlo::CompleteDopplerBroadenedPhotonEnergyDistribution::evaluateSubshellPDF,
                         boost::cref( *half_complete_distribution ),
                         0.5,
                         _1,
                         -1.0,
                         MonteCarlo::K_SUBSHELL );

  Utility::GaussKronrodIntegrator quadrature_set( 1e-3 );

  double abs_error, value;

  const double binding_energy = half_complete_distribution->getSubshellBindingEnergy( MonteCarlo::K_SUBSHELL );
  
  quadrature_set.integrateAdaptively<15>( double_diff_cs_wrapper,
                                          0.0,
                                          0.5 - binding_energy,
                                          value,
                                          abs_error );
  std::cout.precision( 18 );
  std::cout << value << std::endl;
}

//---------------------------------------------------------------------------//
// Check that the subshell PDF can be evaluated
TEUCHOS_UNIT_TEST( 
             DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution,
             evaluateSubshellPDF_full )
{
  // Compton-line energy
  double pdf_value =
    full_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::K_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 4.7647746446724915, 1e-12 );

  // Compton-line energy
  pdf_value =
    full_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::L1_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 15.036947632736435, 1e-12 );

  // Compton-line energy
  pdf_value =
    full_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::L2_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 7.081477324867008, 1e-12 );

  // Compton-line energy
  pdf_value =
    full_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::L3_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 8.089844586686603, 1e-12 );

  // Compton-line energy
  pdf_value =
    full_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::M1_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 32.73595285014459, 1e-12 );

  // Compton-line energy
  pdf_value =
    full_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::M1_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 32.73595285014459, 1e-12 );

  // Compton-line energy
  pdf_value =
    full_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::M2_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 18.904733708093087, 1e-12 );

  // Compton-line energy
  pdf_value =
    full_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::M3_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 20.63962118089761, 1e-12 );

  // Compton-line energy
  pdf_value =
    full_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::M4_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 13.344553382298198, 1e-12 );

  // Compton-line energy
  pdf_value =
    full_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::M5_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 13.699441209385501, 1e-12 );

  // Compton-line energy
  pdf_value =
    full_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::N1_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 67.15875649189272, 1e-12 );
  
  // Compton-line energy
  pdf_value =
    full_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::N2_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 42.300794935866286, 1e-12 );

  // Compton-line energy
  pdf_value =
    full_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::N3_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 45.92852622144515, 1e-12 );

  // Compton-line energy
  pdf_value =
    full_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::N4_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 34.141151852558984, 1e-12 );

  // Compton-line energy
  pdf_value =
    full_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::N5_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 34.96390824829563, 1e-12 );

  // Compton-line energy
  pdf_value =
    full_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::N6_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 28.764832720629716, 1e-12 );

  // Compton-line energy
  pdf_value =
    full_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::N7_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 29.06602172284424, 1e-12 );

  // Compton-line energy
  pdf_value =
    full_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::O1_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 156.49926900099578, 1e-12 );

  // Compton-line energy
  pdf_value =
    full_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::O2_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 102.82360411443777, 1e-12 );

  // Compton-line energy
  pdf_value =
    full_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::O3_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 113.51002502326621, 1e-12 );

  // Compton-line energy
  pdf_value =
    full_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::O4_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 105.61282587664924, 1e-12 );

  // Compton-line energy
  pdf_value =
    full_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::O5_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 108.56818867429266, 1e-12 );

  // Compton-line energy
  pdf_value =
    full_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::P1_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 500.23793204171403, 1e-12 );

  // Compton-line energy
  pdf_value =
    full_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::P2_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 389.1143276726739, 1e-12 );

  // Compton-line energy
  pdf_value =
    full_complete_distribution->evaluateSubshellPDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0,
                                                     MonteCarlo::P3_SUBSHELL );

  TEST_FLOATING_EQUALITY( pdf_value, 389.1143276726739, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the complete PDF can be evaluated
TEUCHOS_UNIT_TEST(
             DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution,
             evaluatePDF )
{
  // Compton-line energy
  double pdf_value = half_distribution->evaluatePDF( 0.5,
                                                     0.25271981255859755,
                                                     0.0 );

  TEST_FLOATING_EQUALITY( pdf_value, 65.64640045212646, 1e-4 );

  // Compton-line energy
  pdf_value = full_distribution->evaluatePDF( 0.5,
                                              0.25271981255859755,
                                              0.0 );

  TEST_FLOATING_EQUALITY( pdf_value, 65.59135653261916, 1e-5 );
}

//---------------------------------------------------------------------------//
// Check that the subshell momentum can be sampled
TEUCHOS_UNIT_TEST(
             DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution,
             sampleSubshellMomentum )
{
  
}

//---------------------------------------------------------------------------//
// Check that the electron momentum can be sampled
TEUCHOS_UNIT_TEST(
             DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution,
             sampleMomentumAndRecordTrials )
{
  
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( 
             DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution,
             sample_half )
{
  double incoming_energy = 20.0, scattering_angle_cosine = 0.0;
  double outgoing_energy;
  MonteCarlo::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.005; // select first shell for collision - old
  fake_stream[1] = 0.005; // select first shell for collision - endf
  fake_stream[2] = 6.427713151861e-01; // select pz = 0.291894102792
  fake_stream[3] = 0.25; // select energy loss
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  half_distribution->sample( incoming_energy,
			     scattering_angle_cosine,
			     outgoing_energy,
			     shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();
  
  TEST_FLOATING_EQUALITY( outgoing_energy, 0.352804013048420073, 1e-12 );
  TEST_EQUALITY_CONST( shell_of_interaction, MonteCarlo::K_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( 
             DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution,
             sample_full )
{
  double incoming_energy = 20.0, scattering_angle_cosine = 0.0;
  double outgoing_energy;
  MonteCarlo::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.005; // select first shell for collision - old
  fake_stream[1] = 0.005; // select first shell for collision - endf
  fake_stream[2] = 0.5; // select pz = 0.0
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  full_distribution->sample( incoming_energy,
			     scattering_angle_cosine,
			     outgoing_energy,
			     shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( outgoing_energy, 0.4982681851517501, 1e-12 );
  TEST_EQUALITY_CONST( shell_of_interaction, MonteCarlo::K_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_ace_file_name, test_ace_table_name;
  
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();
  
  clp.setOption( "test_ace_file",
		 &test_ace_file_name,
		 "Test ACE file name" );
  clp.setOption( "test_ace_table",
		 &test_ace_table_name,
		 "Test ACE table name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Create a file handler and data extractor
  Teuchos::RCP<Data::ACEFileHandler> ace_file_handler( 
				 new Data::ACEFileHandler( test_ace_file_name,
							   test_ace_table_name,
							   1u ) );
  Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor(
                            new Data::XSSEPRDataExtractor( 
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );

  // Create the subshell order array
  Teuchos::ArrayView<const double> subshell_endf_des = 
    xss_data_extractor->extractSubshellENDFDesignators();

  Teuchos::Array<MonteCarlo::SubshellType> subshell_order( 
						    subshell_endf_des.size() );

  for( unsigned i = 0; i < subshell_order.size(); ++i )
  {
    subshell_order[i] = MonteCarlo::convertENDFDesignatorToSubshellEnum( 
					      (unsigned)subshell_endf_des[i] );
  }

  // Create the Compton profile subshell converter
  std::shared_ptr<MonteCarlo::ComptonProfileSubshellConverter> converter;
  
  MonteCarlo::ComptonProfileSubshellConverterFactory::createConverter(
				   converter,
			           xss_data_extractor->extractAtomicNumber() );

  // Create the compton profile distributions
  Teuchos::ArrayView<const double> lswd_block = 
    xss_data_extractor->extractLSWDBlock();

  Teuchos::ArrayView<const double> swd_block = 
    xss_data_extractor->extractSWDBlock();

  MonteCarlo::DopplerBroadenedPhotonEnergyDistribution::ElectronMomentumDistArray
    half_compton_profiles( lswd_block.size() ),
    full_compton_profiles( lswd_block.size() );
  
  for( unsigned shell = 0; shell < lswd_block.size(); ++shell )
  {
    unsigned shell_index = lswd_block[shell]; // ignore interp parameter

    unsigned num_mom_vals = swd_block[shell_index];

    Teuchos::Array<double> half_momentum_grid( 
				  swd_block( shell_index + 1, num_mom_vals ) );

    Teuchos::Array<double> half_profile(
		   swd_block( shell_index + 1 + num_mom_vals, num_mom_vals ) );

    Teuchos::Array<double> full_momentum_grid, full_profile;

    MonteCarlo::createFullProfileFromHalfProfile( half_momentum_grid.begin(),
						  half_momentum_grid.end(),
						  half_profile.begin(),
						  half_profile.end(),
						  full_momentum_grid,
						  full_profile,
                                                  true );

    if( shell == 0 )
    {
      Teuchos::Array<double> half_cdf(
                 swd_block( shell_index + 1 + 2*num_mom_vals, num_mom_vals ) );
      std::cout.precision( 18 );
      for( unsigned i = 0; i < half_momentum_grid.size(); ++i )
      {
        std::cout << half_momentum_grid[i] << " "
                  << half_profile[i] << " "
                  << half_cdf[i] << std::endl;
      }
      // std::cout << std::endl << "FULL" << std::endl;
      // for( unsigned i = 0; i < full_momentum_grid.size(); ++i )
      // {
      //   std::cout << full_momentum_grid[i] << " "
      //             << full_profile[i] << std::endl;
      // }
    }

    std::shared_ptr<Utility::UnitAwareTabularOneDDistribution<Utility::Units::AtomicMomentum,Utility::Units::InverseAtomicMomentum> > raw_compton_profile(
       new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::AtomicMomentum,Utility::Units::InverseAtomicMomentum>(
                                                       half_momentum_grid,
                                                       half_profile ) );

    if( shell == 0 )
    {
      std::shared_ptr<Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::AtomicMomentum,Utility::Units::InverseAtomicMomentum> > raw_compton_profile_copy = std::dynamic_pointer_cast<Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::AtomicMomentum,Utility::Units::InverseAtomicMomentum> >( raw_compton_profile );
      
      raw_compton_profile_copy->toStream( std::cout );
    }

    half_compton_profiles[shell].reset( 
       new MonteCarlo::StandardComptonProfile<Utility::Units::AtomicMomentum>( 
                                                       raw_compton_profile ) );
    
    raw_compton_profile.reset(
       new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::AtomicMomentum,Utility::Units::InverseAtomicMomentum>(
                                                       full_momentum_grid,
                                                       full_profile ) );
    
    full_compton_profiles[shell].reset( 
       new MonteCarlo::StandardComptonProfile<Utility::Units::AtomicMomentum>( 
                                                       raw_compton_profile ) );
    
  }

  half_complete_distribution.reset(
     new MonteCarlo::DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution<MonteCarlo::DoubledHalfComptonProfilePolicy>(
			  xss_data_extractor->extractSubshellOccupancies(),
			  subshell_order,
			  xss_data_extractor->extractLBEPSBlock(),
			  xss_data_extractor->extractLNEPSBlock(),
                          converter,
			  half_compton_profiles ) );

  half_distribution = half_complete_distribution;
  
  full_complete_distribution.reset(
      new MonteCarlo::DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution<MonteCarlo::FullComptonProfilePolicy>(
			  xss_data_extractor->extractSubshellOccupancies(),
			  subshell_order,
			  xss_data_extractor->extractLBEPSBlock(),
			  xss_data_extractor->extractLNEPSBlock(),
                          converter,
			  full_compton_profiles ) );
  
  full_distribution = full_complete_distribution;

  // Clear setup data
  ace_file_handler.reset();
  xss_data_extractor.reset();

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
  
  // Run the unit tests
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  const bool success = Teuchos::UnitTestRepository::runUnitTests( *out );

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstDecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution.cpp
//---------------------------------------------------------------------------//
