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

// FRENSIE Includes
#include "MonteCarlo_DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "MonteCarlo_ComptonProfilePolicy.hpp"
#include "MonteCarlo_ComptonProfileHelpers.hpp"
#include "MonteCarlo_ComptonProfileSubshellConverterFactory.hpp"
#include "MonteCarlo_StandardComptonProfile.hpp"
#include "Data_SubshellType.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_AtomicMomentumUnit.hpp"
#include "Utility_InverseAtomicMomentumUnit.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<const MonteCarlo::DopplerBroadenedPhotonEnergyDistribution>
  half_distribution;

std::shared_ptr<const MonteCarlo::CompleteDopplerBroadenedPhotonEnergyDistribution>
  half_complete_distribution;

std::shared_ptr<const MonteCarlo::DopplerBroadenedPhotonEnergyDistribution>
  full_distribution;

std::shared_ptr<const MonteCarlo::CompleteDopplerBroadenedPhotonEnergyDistribution>
  full_complete_distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check if the distribution is complete
FRENSIE_UNIT_TEST(
             DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution,
             isComplete )
{
  FRENSIE_CHECK( half_distribution->isComplete() );

  FRENSIE_CHECK( full_distribution->isComplete() );
}

//---------------------------------------------------------------------------//
// Check if a subshell is valid
FRENSIE_UNIT_TEST(
             DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution,
             isValidSubshell )
{
  // Half distribution
  FRENSIE_CHECK( half_complete_distribution->isValidSubshell(
                                                    Data::K_SUBSHELL ) );
  FRENSIE_CHECK( half_complete_distribution->isValidSubshell(
                                                   Data::L1_SUBSHELL ) );
  FRENSIE_CHECK( half_complete_distribution->isValidSubshell(
                                                   Data::L2_SUBSHELL ) );
  FRENSIE_CHECK( half_complete_distribution->isValidSubshell(
                                                   Data::L3_SUBSHELL ) );
  FRENSIE_CHECK( half_complete_distribution->isValidSubshell(
                                                   Data::M1_SUBSHELL ) );
  FRENSIE_CHECK( half_complete_distribution->isValidSubshell(
                                                   Data::M2_SUBSHELL ) );
  FRENSIE_CHECK( half_complete_distribution->isValidSubshell(
                                                   Data::M3_SUBSHELL ) );
  FRENSIE_CHECK( half_complete_distribution->isValidSubshell(
                                                   Data::M4_SUBSHELL ) );
  FRENSIE_CHECK( half_complete_distribution->isValidSubshell(
                                                   Data::M5_SUBSHELL ) );
  FRENSIE_CHECK( half_complete_distribution->isValidSubshell(
                                                   Data::N1_SUBSHELL ) );
  FRENSIE_CHECK( half_complete_distribution->isValidSubshell(
                                                   Data::N2_SUBSHELL ) );
  FRENSIE_CHECK( half_complete_distribution->isValidSubshell(
                                                   Data::N3_SUBSHELL ) );
  FRENSIE_CHECK( half_complete_distribution->isValidSubshell(
                                                   Data::N4_SUBSHELL ) );
  FRENSIE_CHECK( half_complete_distribution->isValidSubshell(
                                                   Data::N5_SUBSHELL ) );
  FRENSIE_CHECK( half_complete_distribution->isValidSubshell(
                                                   Data::N6_SUBSHELL ) );
  FRENSIE_CHECK( half_complete_distribution->isValidSubshell(
                                                   Data::N7_SUBSHELL ) );
  FRENSIE_CHECK( half_complete_distribution->isValidSubshell(
                                                   Data::O1_SUBSHELL ) );
  FRENSIE_CHECK( half_complete_distribution->isValidSubshell(
                                                   Data::O2_SUBSHELL ) );
  FRENSIE_CHECK( half_complete_distribution->isValidSubshell(
                                                   Data::O3_SUBSHELL ) );
  FRENSIE_CHECK( half_complete_distribution->isValidSubshell(
                                                   Data::O4_SUBSHELL ) );
  FRENSIE_CHECK( half_complete_distribution->isValidSubshell(
                                                   Data::O5_SUBSHELL ) );
  FRENSIE_CHECK( half_complete_distribution->isValidSubshell(
                                                   Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( half_complete_distribution->isValidSubshell(
                                                   Data::P2_SUBSHELL ) );
  FRENSIE_CHECK( half_complete_distribution->isValidSubshell(
                                                   Data::P3_SUBSHELL ) );
  FRENSIE_CHECK( !half_complete_distribution->isValidSubshell(
                                                   Data::Q3_SUBSHELL ) );
  FRENSIE_CHECK( !half_complete_distribution->isValidSubshell(
                                              Data::INVALID_SUBSHELL ) );
  FRENSIE_CHECK( !half_complete_distribution->isValidSubshell(
                                              Data::UNKNOWN_SUBSHELL ) );

  // Full distribution
  FRENSIE_CHECK( full_complete_distribution->isValidSubshell(
                                                    Data::K_SUBSHELL ) );
  FRENSIE_CHECK( full_complete_distribution->isValidSubshell(
                                                   Data::L1_SUBSHELL ) );
  FRENSIE_CHECK( full_complete_distribution->isValidSubshell(
                                                   Data::L2_SUBSHELL ) );
  FRENSIE_CHECK( full_complete_distribution->isValidSubshell(
                                                   Data::L3_SUBSHELL ) );
  FRENSIE_CHECK( full_complete_distribution->isValidSubshell(
                                                   Data::M1_SUBSHELL ) );
  FRENSIE_CHECK( full_complete_distribution->isValidSubshell(
                                                   Data::M2_SUBSHELL ) );
  FRENSIE_CHECK( full_complete_distribution->isValidSubshell(
                                                   Data::M3_SUBSHELL ) );
  FRENSIE_CHECK( full_complete_distribution->isValidSubshell(
                                                   Data::M4_SUBSHELL ) );
  FRENSIE_CHECK( full_complete_distribution->isValidSubshell(
                                                   Data::M5_SUBSHELL ) );
  FRENSIE_CHECK( full_complete_distribution->isValidSubshell(
                                                   Data::N1_SUBSHELL ) );
  FRENSIE_CHECK( full_complete_distribution->isValidSubshell(
                                                   Data::N2_SUBSHELL ) );
  FRENSIE_CHECK( full_complete_distribution->isValidSubshell(
                                                   Data::N3_SUBSHELL ) );
  FRENSIE_CHECK( full_complete_distribution->isValidSubshell(
                                                   Data::N4_SUBSHELL ) );
  FRENSIE_CHECK( full_complete_distribution->isValidSubshell(
                                                   Data::N5_SUBSHELL ) );
  FRENSIE_CHECK( full_complete_distribution->isValidSubshell(
                                                   Data::N6_SUBSHELL ) );
  FRENSIE_CHECK( full_complete_distribution->isValidSubshell(
                                                   Data::N7_SUBSHELL ) );
  FRENSIE_CHECK( full_complete_distribution->isValidSubshell(
                                                   Data::O1_SUBSHELL ) );
  FRENSIE_CHECK( full_complete_distribution->isValidSubshell(
                                                   Data::O2_SUBSHELL ) );
  FRENSIE_CHECK( full_complete_distribution->isValidSubshell(
                                                   Data::O3_SUBSHELL ) );
  FRENSIE_CHECK( full_complete_distribution->isValidSubshell(
                                                   Data::O4_SUBSHELL ) );
  FRENSIE_CHECK( full_complete_distribution->isValidSubshell(
                                                   Data::O5_SUBSHELL ) );
  FRENSIE_CHECK( full_complete_distribution->isValidSubshell(
                                                   Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( full_complete_distribution->isValidSubshell(
                                                   Data::P2_SUBSHELL ) );
  FRENSIE_CHECK( full_complete_distribution->isValidSubshell(
                                                   Data::P3_SUBSHELL ) );
  FRENSIE_CHECK( !full_complete_distribution->isValidSubshell(
                                                   Data::Q3_SUBSHELL ) );
  FRENSIE_CHECK( !full_complete_distribution->isValidSubshell(
                                              Data::INVALID_SUBSHELL ) );
  FRENSIE_CHECK( !full_complete_distribution->isValidSubshell(
                                              Data::UNKNOWN_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check that the subshell binding energy can be returned
FRENSIE_UNIT_TEST(
             DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution,
             getSubshellBindingEnergy )
{
  // Half distribution
  FRENSIE_CHECK_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                      Data::K_SUBSHELL ),
                          0.088005,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     Data::L1_SUBSHELL ),
                          0.015861,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     Data::L2_SUBSHELL ),
                          0.0152,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     Data::L3_SUBSHELL ),
                          0.013035,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     Data::M1_SUBSHELL ),
                          0.003851,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     Data::M2_SUBSHELL ),
                          0.003554,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     Data::M3_SUBSHELL ),
                          0.003066,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     Data::M4_SUBSHELL ),
                          0.002586,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     Data::M5_SUBSHELL ),
                          0.002484,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     Data::N1_SUBSHELL ),
                          0.000894,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     Data::N2_SUBSHELL ),
                          0.000764,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     Data::N3_SUBSHELL ),
                          0.000645,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     Data::N4_SUBSHELL ),
                          0.000434,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     Data::N5_SUBSHELL ),
                          0.000412,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     Data::N6_SUBSHELL ),
                          0.000141,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     Data::N7_SUBSHELL ),
                          0.000136,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     Data::O1_SUBSHELL ),
                          0.000148,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     Data::O2_SUBSHELL ),
                          0.000105,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     Data::O3_SUBSHELL ),
                          8.6e-5,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     Data::O4_SUBSHELL ),
                          2.0e-5,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     Data::O5_SUBSHELL ),
                          1.8e-5,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     Data::P1_SUBSHELL ),
                          0.0,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     Data::P2_SUBSHELL ),
                          0.0,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( half_complete_distribution->getSubshellBindingEnergy(
                                                     Data::P3_SUBSHELL ),
                          0.0,
                          1e-15 );

  // Full distribution
  FRENSIE_CHECK_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                      Data::K_SUBSHELL ),
                          0.088005,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     Data::L1_SUBSHELL ),
                          0.015861,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     Data::L2_SUBSHELL ),
                          0.0152,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     Data::L3_SUBSHELL ),
                          0.013035,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     Data::M1_SUBSHELL ),
                          0.003851,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     Data::M2_SUBSHELL ),
                          0.003554,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     Data::M3_SUBSHELL ),
                          0.003066,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     Data::M4_SUBSHELL ),
                          0.002586,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     Data::M5_SUBSHELL ),
                          0.002484,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     Data::N1_SUBSHELL ),
                          0.000894,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     Data::N2_SUBSHELL ),
                          0.000764,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     Data::N3_SUBSHELL ),
                          0.000645,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     Data::N4_SUBSHELL ),
                          0.000434,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     Data::N5_SUBSHELL ),
                          0.000412,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     Data::N6_SUBSHELL ),
                          0.000141,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     Data::N7_SUBSHELL ),
                          0.000136,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     Data::O1_SUBSHELL ),
                          0.000148,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     Data::O2_SUBSHELL ),
                          0.000105,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     Data::O3_SUBSHELL ),
                          8.6e-5,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     Data::O4_SUBSHELL ),
                          2.0e-5,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     Data::O5_SUBSHELL ),
                          1.8e-5,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     Data::P1_SUBSHELL ),
                          0.0,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     Data::P2_SUBSHELL ),
                          0.0,
                          1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( full_complete_distribution->getSubshellBindingEnergy(
                                                     Data::P3_SUBSHELL ),
                          0.0,
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the subshell occupancy can be returned
FRENSIE_UNIT_TEST(
             DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution,
             getSubshellOccupancy )
{
  // Half distribution
  FRENSIE_CHECK_EQUAL( half_complete_distribution->getSubshellOccupancy(
                                                      Data::K_SUBSHELL ),
                       2 );
  FRENSIE_CHECK_EQUAL( half_complete_distribution->getSubshellOccupancy(
                                                     Data::L1_SUBSHELL ),
                       2 );
  FRENSIE_CHECK_EQUAL( half_complete_distribution->getSubshellOccupancy(
                                                     Data::L2_SUBSHELL ),
                       2 );
  FRENSIE_CHECK_EQUAL( half_complete_distribution->getSubshellOccupancy(
                                                     Data::L3_SUBSHELL ),
                       4 );
  FRENSIE_CHECK_EQUAL( half_complete_distribution->getSubshellOccupancy(
                                                     Data::M1_SUBSHELL ),
                       2 );
  FRENSIE_CHECK_EQUAL( half_complete_distribution->getSubshellOccupancy(
                                                     Data::M2_SUBSHELL ),
                       2 );
  FRENSIE_CHECK_EQUAL( half_complete_distribution->getSubshellOccupancy(
                                                     Data::M3_SUBSHELL ),
                       4 );
  FRENSIE_CHECK_EQUAL( half_complete_distribution->getSubshellOccupancy(
                                                     Data::M4_SUBSHELL ),
                       4 );
  FRENSIE_CHECK_EQUAL( half_complete_distribution->getSubshellOccupancy(
                                                     Data::M5_SUBSHELL ),
                       6 );
  FRENSIE_CHECK_EQUAL( half_complete_distribution->getSubshellOccupancy(
                                                     Data::N1_SUBSHELL ),
                       2 );
  FRENSIE_CHECK_EQUAL( half_complete_distribution->getSubshellOccupancy(
                                                     Data::N2_SUBSHELL ),
                       2 );
  FRENSIE_CHECK_EQUAL( half_complete_distribution->getSubshellOccupancy(
                                                     Data::N3_SUBSHELL ),
                       4 );
  FRENSIE_CHECK_EQUAL( half_complete_distribution->getSubshellOccupancy(
                                                     Data::N4_SUBSHELL ),
                       4 );
  FRENSIE_CHECK_EQUAL( half_complete_distribution->getSubshellOccupancy(
                                                     Data::N5_SUBSHELL ),
                       6 );
  FRENSIE_CHECK_EQUAL( half_complete_distribution->getSubshellOccupancy(
                                                     Data::N6_SUBSHELL ),
                       6 );
  FRENSIE_CHECK_EQUAL( half_complete_distribution->getSubshellOccupancy(
                                                     Data::N7_SUBSHELL ),
                       8 );
  FRENSIE_CHECK_EQUAL( half_complete_distribution->getSubshellOccupancy(
                                                     Data::O1_SUBSHELL ),
                       2 );
  FRENSIE_CHECK_EQUAL( half_complete_distribution->getSubshellOccupancy(
                                                     Data::O2_SUBSHELL ),
                       2 );
  FRENSIE_CHECK_EQUAL( half_complete_distribution->getSubshellOccupancy(
                                                     Data::O3_SUBSHELL ),
                       4 );
  FRENSIE_CHECK_EQUAL( half_complete_distribution->getSubshellOccupancy(
                                                     Data::O4_SUBSHELL ),
                       4 );
  FRENSIE_CHECK_EQUAL( half_complete_distribution->getSubshellOccupancy(
                                                     Data::O5_SUBSHELL ),
                       6 );
  FRENSIE_CHECK_EQUAL( half_complete_distribution->getSubshellOccupancy(
                                                     Data::P1_SUBSHELL ),
                       2 );
  FRENSIE_CHECK_EQUAL( half_complete_distribution->getSubshellOccupancy(
                                                     Data::P2_SUBSHELL ),
                       2 );
  FRENSIE_CHECK_EQUAL( half_complete_distribution->getSubshellOccupancy(
                                                     Data::P3_SUBSHELL ),
                       2 );

  // Full distribution
  FRENSIE_CHECK_EQUAL( full_complete_distribution->getSubshellOccupancy(
                                                      Data::K_SUBSHELL ),
                       2 );
  FRENSIE_CHECK_EQUAL( full_complete_distribution->getSubshellOccupancy(
                                                     Data::L1_SUBSHELL ),
                       2 );
  FRENSIE_CHECK_EQUAL( full_complete_distribution->getSubshellOccupancy(
                                                     Data::L2_SUBSHELL ),
                       2 );
  FRENSIE_CHECK_EQUAL( full_complete_distribution->getSubshellOccupancy(
                                                     Data::L3_SUBSHELL ),
                       4 );
  FRENSIE_CHECK_EQUAL( full_complete_distribution->getSubshellOccupancy(
                                                     Data::M1_SUBSHELL ),
                       2 );
  FRENSIE_CHECK_EQUAL( full_complete_distribution->getSubshellOccupancy(
                                                     Data::M2_SUBSHELL ),
                       2 );
  FRENSIE_CHECK_EQUAL( full_complete_distribution->getSubshellOccupancy(
                                                     Data::M3_SUBSHELL ),
                       4 );
  FRENSIE_CHECK_EQUAL( full_complete_distribution->getSubshellOccupancy(
                                                     Data::M4_SUBSHELL ),
                       4 );
  FRENSIE_CHECK_EQUAL( full_complete_distribution->getSubshellOccupancy(
                                                     Data::M5_SUBSHELL ),
                       6 );
  FRENSIE_CHECK_EQUAL( full_complete_distribution->getSubshellOccupancy(
                                                     Data::N1_SUBSHELL ),
                       2 );
  FRENSIE_CHECK_EQUAL( full_complete_distribution->getSubshellOccupancy(
                                                     Data::N2_SUBSHELL ),
                       2 );
  FRENSIE_CHECK_EQUAL( full_complete_distribution->getSubshellOccupancy(
                                                     Data::N3_SUBSHELL ),
                       4 );
  FRENSIE_CHECK_EQUAL( full_complete_distribution->getSubshellOccupancy(
                                                     Data::N4_SUBSHELL ),
                       4 );
  FRENSIE_CHECK_EQUAL( full_complete_distribution->getSubshellOccupancy(
                                                     Data::N5_SUBSHELL ),
                       6 );
  FRENSIE_CHECK_EQUAL( full_complete_distribution->getSubshellOccupancy(
                                                     Data::N6_SUBSHELL ),
                       6 );
  FRENSIE_CHECK_EQUAL( full_complete_distribution->getSubshellOccupancy(
                                                     Data::N7_SUBSHELL ),
                       8 );
  FRENSIE_CHECK_EQUAL( full_complete_distribution->getSubshellOccupancy(
                                                     Data::O1_SUBSHELL ),
                       2 );
  FRENSIE_CHECK_EQUAL( full_complete_distribution->getSubshellOccupancy(
                                                     Data::O2_SUBSHELL ),
                       2 );
  FRENSIE_CHECK_EQUAL( full_complete_distribution->getSubshellOccupancy(
                                                     Data::O3_SUBSHELL ),
                       4 );
  FRENSIE_CHECK_EQUAL( full_complete_distribution->getSubshellOccupancy(
                                                     Data::O4_SUBSHELL ),
                       4 );
  FRENSIE_CHECK_EQUAL( full_complete_distribution->getSubshellOccupancy(
                                                     Data::O5_SUBSHELL ),
                       6 );
  FRENSIE_CHECK_EQUAL( full_complete_distribution->getSubshellOccupancy(
                                                     Data::P1_SUBSHELL ),
                       2 );
  FRENSIE_CHECK_EQUAL( full_complete_distribution->getSubshellOccupancy(
                                                     Data::P2_SUBSHELL ),
                       2 );
  FRENSIE_CHECK_EQUAL( full_complete_distribution->getSubshellOccupancy(
                                                     Data::P3_SUBSHELL ),
                       2 );
}

//---------------------------------------------------------------------------//
// Check that the subshell distribution can be evaluated
FRENSIE_UNIT_TEST(
             DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution,
             evaluateSubshellWithElectronMomentumProjection_half )
{
  // pz_max <= 0.0, pz = pz_max
  double cross_section =
    half_complete_distribution->evaluateSubshellWithElectronMomentumProjection(
                        0.26055, -0.01189331797743439, 0.0, Data::K_SUBSHELL );
  
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section =
    half_complete_distribution->evaluateSubshellWithElectronMomentumProjection(
                                        0.26055, -1.0, 0.0, Data::K_SUBSHELL );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  // Mu = -1.0
  // Above pz_max (table pz_max, not the true pz_max)
  cross_section =
    half_complete_distribution->evaluateSubshellWithElectronMomentumProjection(
                             0.5, 0.7875582275970302, -1.0, Data::K_SUBSHELL );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );
  
  // pz = pz_max (table pz_max, not the true pz_max)
  cross_section =
    half_complete_distribution->evaluateSubshellWithElectronMomentumProjection(
                             0.5, 0.7297352569816316, -1.0, Data::K_SUBSHELL );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.02789302998932924, 1e-9 );
}

//---------------------------------------------------------------------------//
// Check that the subshell distribution can be evaluated
FRENSIE_UNIT_TEST( 
             DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution,
             evaluateSubshell_half )
{
  // Incoming energy below min energy (pz_max <= 0.0)
  double cross_section = half_complete_distribution->evaluateSubshell(
                                    0.26055, 0.172545, 0.0, Data::K_SUBSHELL );
  
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = half_complete_distribution->evaluateSubshell(
                                        0.26055, 1e-6, 0.0, Data::K_SUBSHELL );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  // Mu = -1.0
  // Above max energy (table max, not the true max)
  cross_section = half_complete_distribution->evaluateSubshell(
                                          0.5, 0.389, -1.0, Data::K_SUBSHELL );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );
  
  // Max energy (table max, not the true max)
  cross_section = half_complete_distribution->evaluateSubshell(
                            0.5, 0.38831779122923316, -1.0, Data::K_SUBSHELL );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.09284777712806079, 1e-9 );

  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                            0.5, 0.16909307700494494, -1.0, Data::K_SUBSHELL );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.0872312326605855, 1e-9 );

  // Min energy (corresponding to -pz_max) - not the true min energy
  cross_section = half_complete_distribution->evaluateSubshell(
                            0.5, 0.036654152201969, -1.0, Data::K_SUBSHELL );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.15368991735277307, 1e-9 );
  
  // Below the min energy
  cross_section = half_complete_distribution->evaluateSubshell(
                                          0.5, 0.036, -1.0, Data::K_SUBSHELL );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  // Mu = 0.0
  // Above max energy
  cross_section = half_complete_distribution->evaluateSubshell(
                                           0.5, 0.412, 0.0, Data::K_SUBSHELL );
  
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  // Max energy
  cross_section = half_complete_distribution->evaluateSubshell(
                                        0.5, 0.411995, 0.0, Data::K_SUBSHELL );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.23568941788995593, 1e-9 );

  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                             0.5, 0.25271981255859755, 0.0, Data::K_SUBSHELL );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.8739457040455174, 1e-9 );

  // Min energy (corresponding to -pz_max) - not the true min energy
  cross_section = half_complete_distribution->evaluateSubshell(
                              0.5, 0.1259578643763628, 0.0, Data::K_SUBSHELL );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.2961415215740492, 1e-9 );

  // Below the min energy  
  cross_section = half_complete_distribution->evaluateSubshell(
                                           0.5, 0.125, 0.0, Data::K_SUBSHELL );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                            0.5, 0.25271981255859755, 0.0, Data::L1_SUBSHELL );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.8795592631443463, 1e-9 );

  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                            0.5, 0.25271981255859755, 0.0, Data::L2_SUBSHELL );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.3641862029267904, 1e-9 );

  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                            0.5, 0.25271981255859755, 0.0, Data::L3_SUBSHELL );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.1058197315608105, 1e-9 );

  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                            0.5, 0.25271981255859755, 0.0, Data::M1_SUBSHELL );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.22294684805154, 1e-9 );

  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                            0.5, 0.25271981255859755, 0.0, Data::M2_SUBSHELL );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.5993492179041424, 1e-9 );

  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                            0.5, 0.25271981255859755, 0.0, Data::M3_SUBSHELL );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 7.849476872027157, 1e-9 );

  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                            0.5, 0.25271981255859755, 0.0, Data::M4_SUBSHELL );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 5.072957333261603, 1e-9 );

  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                            0.5, 0.25271981255859755, 0.0, Data::M5_SUBSHELL );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 7.80936397037139, 1e-9 );
  
  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                            0.5, 0.25271981255859755, 0.0, Data::N1_SUBSHELL );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 12.724993765984314, 1e-9 );
  
  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                            0.5, 0.25271981255859755, 0.0, Data::N2_SUBSHELL );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.017860671607723, 1e-9 );

  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                            0.5, 0.25271981255859755, 0.0, Data::N3_SUBSHELL );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 17.404293921844925, 1e-9 );

  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                            0.5, 0.25271981255859755, 0.0, Data::N4_SUBSHELL );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 12.934220762743779, 1e-9 );

  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                            0.5, 0.25271981255859755, 0.0, Data::N5_SUBSHELL );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 19.866582309610457, 1e-9 );
  
  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                            0.5, 0.25271981255859755, 0.0, Data::N6_SUBSHELL );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 16.340019178656313, 1e-9 );
  
  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                            0.5, 0.25271981255859755, 0.0, Data::N7_SUBSHELL );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 22.014409681317527, 1e-9 );
  
  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                            0.5, 0.25271981255859755, 0.0, Data::O1_SUBSHELL );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 29.614290862625364, 1e-9 );

  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                            0.5, 0.25271981255859755, 0.0, Data::O2_SUBSHELL );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 19.45765078643722, 1e-9 );

  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                            0.5, 0.25271981255859755, 0.0, Data::O3_SUBSHELL );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 42.95534691003039, 1e-9 );

  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                            0.5, 0.25271981255859755, 0.0, Data::O4_SUBSHELL );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 39.96137153322004, 1e-9 );

  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                            0.5, 0.25271981255859755, 0.0, Data::O5_SUBSHELL );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 61.61849575263572, 1e-9 );

  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                            0.5, 0.25271981255859755, 0.0, Data::P1_SUBSHELL );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 94.62281727761084, 1e-9 );
  
  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                            0.5, 0.25271981255859755, 0.0, Data::P2_SUBSHELL );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 73.60158341273974, 1e-15 );
 
  // Compton-line energy
  cross_section = half_complete_distribution->evaluateSubshell(
                            0.5, 0.25271981255859755, 0.0, Data::P3_SUBSHELL );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 73.60158341273974, 1e-15 );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_ace_file_name;
unsigned test_ace_file_start_line;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace_file",
                                        test_ace_file_name, "",
                                        "Test ACE file name" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace_file_start_line",
                                        test_ace_file_start_line, 1,
                                        "Test ACE file start line" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create a file handler and data extractor
  std::shared_ptr<Data::ACEFileHandler> ace_file_handler(
                        new Data::ACEFileHandler( test_ace_file_name,
                                                  "82000.12p",
						  test_ace_file_start_line ) );
  
  std::shared_ptr<Data::XSSEPRDataExtractor> xss_data_extractor(
                            new Data::XSSEPRDataExtractor(
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );

  // Create the subshell order array
  Utility::ArrayView<const double> subshell_endf_des =
    xss_data_extractor->extractSubshellENDFDesignators();

  std::vector<Data::SubshellType> subshell_order( subshell_endf_des.size() );

  for( unsigned i = 0; i < subshell_order.size(); ++i )
  {
    subshell_order[i] = Data::convertENDFDesignatorToSubshellEnum(
					      (unsigned)subshell_endf_des[i] );
  }

  // Create the Compton profile subshell converter
  std::shared_ptr<const MonteCarlo::ComptonProfileSubshellConverter> converter;

  MonteCarlo::ComptonProfileSubshellConverterFactory::createConverter(
				   converter,
			           xss_data_extractor->extractAtomicNumber() );

  // Create the compton profile distributions
  Utility::ArrayView<const double> lswd_block =
    xss_data_extractor->extractLSWDBlock();

  Utility::ArrayView<const double> swd_block =
    xss_data_extractor->extractSWDBlock();

  MonteCarlo::CompleteDopplerBroadenedPhotonEnergyDistribution::ComptonProfileArray
    half_compton_profiles( lswd_block.size() ),
    full_compton_profiles( lswd_block.size() );

  for( unsigned shell = 0; shell < lswd_block.size(); ++shell )
  {
    unsigned shell_index = lswd_block[shell]; // ignore interp parameter

    unsigned num_mom_vals = swd_block[shell_index];

    Utility::ArrayView<const double> raw_half_momentum_grid =
      swd_block( shell_index + 1, num_mom_vals );
    
    std::vector<double> half_momentum_grid( raw_half_momentum_grid.begin(),
                                            raw_half_momentum_grid.end() );

    Utility::ArrayView<const double> raw_half_profile =
      swd_block( shell_index + 1 + num_mom_vals, num_mom_vals );

    std::vector<double> half_profile( raw_half_profile.begin(),
                                      raw_half_profile.end() );
                                     
    std::vector<double> full_momentum_grid, full_profile;

    MonteCarlo::createFullProfileFromHalfProfile( half_momentum_grid.begin(),
						  half_momentum_grid.end(),
						  half_profile.begin(),
						  half_profile.end(),
						  full_momentum_grid,
						  full_profile,
                                                  true );

    // if( shell == 0 )
    // {
    //   Utility::ArrayView<const double> raw_half_cdf =
    //     swd_block( shell_index + 1 + 2*num_mom_vals, num_mom_vals );
      
    //   std::vector<double> half_cdf( raw_half_cdf.begin(),
    //                                 raw_half_cdf.end() );
                                   
    //   std::cout.precision( 18 );
    //   for( unsigned i = 0; i < half_momentum_grid.size(); ++i )
    //   {
    //     std::cout << half_momentum_grid[i] << " "
    //               << half_profile[i] << " "
    //               << half_cdf[i] << std::endl;
    //   }
    //   std::cout << std::endl << "FULL" << std::endl;
    //   for( unsigned i = 0; i < full_momentum_grid.size(); ++i )
    //   {
    //     std::cout << full_momentum_grid[i] << " "
    //               << full_profile[i] << std::endl;
    //   }
    // }

    std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<Utility::Units::AtomicMomentum,Utility::Units::InverseAtomicMomentum> > raw_compton_profile(
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

  std::vector<double> subshell_occupancies(
                      xss_data_extractor->extractSubshellOccupancies().begin(),
                      xss_data_extractor->extractSubshellOccupancies().end() );

  std::vector<double> old_subshell_binding_energies(
                               xss_data_extractor->extractLBEPSBlock().begin(),
                               xss_data_extractor->extractLBEPSBlock().end() );

  std::vector<double> old_subshell_occupancies(
                               xss_data_extractor->extractLNEPSBlock().begin(),
                               xss_data_extractor->extractLNEPSBlock().end() );

  half_complete_distribution.reset(
     new MonteCarlo::DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution<MonteCarlo::DoubledHalfComptonProfilePolicy>(
                                       subshell_occupancies,
                                       subshell_order,
                                       old_subshell_binding_energies,
                                       old_subshell_occupancies,
                                       converter,
                                       half_compton_profiles ) );

  half_distribution = half_complete_distribution;

  full_complete_distribution.reset(
      new MonteCarlo::DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution<MonteCarlo::FullComptonProfilePolicy>(
                                                 subshell_occupancies,
                                                 subshell_order,
			                         old_subshell_binding_energies,
                                                 old_subshell_occupancies,
                                                 converter,
                                                 full_compton_profiles ) );

  full_distribution = full_complete_distribution;

  // Clear setup data
  ace_file_handler.reset();
  xss_data_extractor.reset();

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstDecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution.cpp
//---------------------------------------------------------------------------//
