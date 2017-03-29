//---------------------------------------------------------------------------//
//!
//! \file   tstLineEnergyAdjointPhotoatomicReaction.cpp
//! \author Alex Robinson
//! \brief  The line energy adjoint photoatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "MonteCarlo_LineEnergyAdjointPhotoatomicReaction.hpp"
#include "MonteCarlo_LineEnergyAdjointPhotonScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_AdjointPhotonProbeState.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::AdjointPhotoatomicReaction> reaction;
std::shared_ptr<MonteCarlo::LineEnergyAdjointPhotoatomicReaction> full_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the min outgoing energy can be returned
TEUCHOS_UNIT_TEST( LineEnergyAdjointPhotoatomicReaction,
                   getMinOutgoingEnergy )
{
  TEST_EQUALITY_CONST( full_reaction->getMinOutgoingEnergy(),
                       2*Utility::PhysicalConstants::electron_rest_mass_energy );
}

//---------------------------------------------------------------------------//
// Check that the max outgoing energy can be returned
TEUCHOS_UNIT_TEST( LineEnergyAdjointPhotoatomicReaction,
                   getMaxOutgoingEnergy )
{
  TEST_EQUALITY_CONST( full_reaction->getMaxOutgoingEnergy(), 20.0 );
}

//---------------------------------------------------------------------------//
// Check if an energy falls within the energy grid
TEUCHOS_UNIT_TEST( LineEnergyAdjointPhotoatomicReaction,
                   isEnergyWithinEnergyGrid )
{
  TEST_ASSERT( !full_reaction->isEnergyWithinEnergyGrid( 0.5 ) );
  TEST_ASSERT( full_reaction->isEnergyWithinEnergyGrid( Utility::PhysicalConstants::electron_rest_mass_energy ) );
  TEST_ASSERT( !full_reaction->isEnergyWithinEnergyGrid( 0.52 ) );
}

//---------------------------------------------------------------------------//
// Check that the cross section at a given energy can be returned
TEUCHOS_UNIT_TEST( LineEnergyAdjointPhotoatomicReaction, getCrossSection )
{
  TEST_EQUALITY_CONST( reaction->getCrossSection( 0.5 ), 0.0 );
  TEST_FLOATING_EQUALITY( reaction->getCrossSection( Utility::PhysicalConstants::electron_rest_mass_energy ),
                          14.739362127632583,
                          1e-15 );
  TEST_EQUALITY_CONST( reaction->getCrossSection( 0.52 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the cross section at a given energy can be returned
TEUCHOS_UNIT_TEST( LineEnergyAdjointPhotoatomicReaction,
                   getCrossSection_indexed )
{
  TEST_EQUALITY_CONST( reaction->getCrossSection( 0.5, 0 ), 0.0 );
  TEST_FLOATING_EQUALITY( reaction->getCrossSection( Utility::PhysicalConstants::electron_rest_mass_energy, 0 ),
                          14.739362127632583,
                          1e-15 );
  TEST_EQUALITY_CONST( reaction->getCrossSection( 0.52, 0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the line energy where the reaction is defined can be returned
TEUCHOS_UNIT_TEST( LineEnergyAdjointPhotoatomicReaction, getLineEnergy )
{
  TEST_EQUALITY_CONST( full_reaction->getLineEnergy(),
                       Utility::PhysicalConstants::electron_rest_mass_energy );
}

//---------------------------------------------------------------------------//
// Check that the max energy where the reaction is defined can be returned
TEUCHOS_UNIT_TEST( LineEnergyAdjointPhotoatomicReaction, getMaxEnergy )
{
  TEST_EQUALITY_CONST( reaction->getMaxEnergy(),
                       Utility::PhysicalConstants::electron_rest_mass_energy );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
TEUCHOS_UNIT_TEST( LineEnergyAdjointPhotoatomicReaction, getThresholdEnergy )
{
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(),
                       Utility::PhysicalConstants::electron_rest_mass_energy );
}

//---------------------------------------------------------------------------//
// Check that the number of adjoint photons emitted from the reaction can be
// returned
TEUCHOS_UNIT_TEST( LineEnergyAdjointPhotoatomicReaction,
                   getNumberOfEmittedPhotons )
{
  TEST_EQUALITY_CONST( reaction->getNumberOfEmittedPhotons( 0.5 ), 0 );
  TEST_EQUALITY_CONST( reaction->getNumberOfEmittedPhotons( Utility::PhysicalConstants::electron_rest_mass_energy ), 1 );
  TEST_EQUALITY_CONST( reaction->getNumberOfEmittedPhotons( 0.52 ), 0 );
}

//---------------------------------------------------------------------------//
// Check that the number of adjoint electrons emitted from the reaction can be
// returned
TEUCHOS_UNIT_TEST( LineEnergyAdjointPhotoatomicReaction,
                   getNumberOfEmittedElectrons )
{
  TEST_EQUALITY_CONST( reaction->getNumberOfEmittedElectrons( 0.5 ), 0 );
  TEST_EQUALITY_CONST( reaction->getNumberOfEmittedElectrons( Utility::PhysicalConstants::electron_rest_mass_energy ), 0 );
  TEST_EQUALITY_CONST( reaction->getNumberOfEmittedElectrons( 0.52 ), 0 );
}

//---------------------------------------------------------------------------//
// Check that the number of adjoint electrons emitted from the reaction can
// be returned
TEUCHOS_UNIT_TEST( LineEnergyAdjointPhotoatomicReaction, getReactionType )
{
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that a reaction can be simulated
TEUCHOS_UNIT_TEST( LineEnergyAdjointPhotoatomicReaction, react )
{
  MonteCarlo::AdjointPhotonProbeState adjoint_photon_probe( 0 );
  adjoint_photon_probe.setEnergy( Utility::PhysicalConstants::electron_rest_mass_energy );
  adjoint_photon_probe.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  // Set the fake stream
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.0;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  reaction->react( adjoint_photon_probe,
                   bank,
                   shell_of_interaction );

  TEST_ASSERT( adjoint_photon_probe.isGone() );
  TEST_EQUALITY_CONST( bank.size(), 1 );
  TEST_EQUALITY_CONST( shell_of_interaction, Data::UNKNOWN_SUBSHELL );
  TEST_FLOATING_EQUALITY( bank.top().getEnergy(), 
                          2*Utility::PhysicalConstants::electron_rest_mass_energy,
                          1e-15 );
  TEST_EQUALITY_CONST( bank.top().getXDirection(), 0.0 );
  TEST_EQUALITY_CONST( bank.top().getYDirection(), -1.0 );
  TEST_EQUALITY_CONST( bank.top().getZDirection(), 0.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_native_file_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_native_file",
                   &test_native_file_name,
                   "Test Native file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Create the native data file container
  Data::AdjointElectronPhotonRelaxationDataContainer
    data_container( test_native_file_name );

  // Create the adjoint pair production distribution
  std::shared_ptr<const MonteCarlo::LineEnergyAdjointPhotonScatteringDistribution>
    scattering_distribution;

  double cross_section;

  MonteCarlo::LineEnergyAdjointPhotonScatteringDistributionNativeFactory::createPairProductionDistribution(
                                                       data_container,
                                                       scattering_distribution,
                                                       cross_section,
                                                       20.0 );

  // Create the adjoint pair production reaction
  full_reaction.reset(
            new MonteCarlo::LineEnergyAdjointPhotoatomicReaction(
                      MonteCarlo::PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION,
                      cross_section,
                      scattering_distribution ) );

  reaction = full_reaction;
  
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstLineEnergyAdjointPhotoatomicReaction.cpp
//---------------------------------------------------------------------------//
