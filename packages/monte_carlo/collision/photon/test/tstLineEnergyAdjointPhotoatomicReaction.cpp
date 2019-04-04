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

// FRENSIE Includes
#include "MonteCarlo_LineEnergyAdjointPhotoatomicReaction.hpp"
#include "MonteCarlo_LineEnergyAdjointPhotonScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_AdjointPhotonProbeState.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::AdjointPhotoatomicReaction> reaction;
std::shared_ptr<MonteCarlo::LineEnergyAdjointPhotoatomicReaction> full_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the min outgoing energy can be returned
FRENSIE_UNIT_TEST( LineEnergyAdjointPhotoatomicReaction,
                   getMinOutgoingEnergy )
{
  FRENSIE_CHECK_EQUAL( full_reaction->getMinOutgoingEnergy(),
                       2*Utility::PhysicalConstants::electron_rest_mass_energy );
}

//---------------------------------------------------------------------------//
// Check that the max outgoing energy can be returned
FRENSIE_UNIT_TEST( LineEnergyAdjointPhotoatomicReaction,
                   getMaxOutgoingEnergy )
{
  FRENSIE_CHECK_EQUAL( full_reaction->getMaxOutgoingEnergy(), 20.0 );
}

//---------------------------------------------------------------------------//
// Check if an energy falls within the energy grid
FRENSIE_UNIT_TEST( LineEnergyAdjointPhotoatomicReaction,
                   isEnergyWithinEnergyGrid )
{
  FRENSIE_CHECK( !full_reaction->isEnergyWithinEnergyGrid( 0.5 ) );
  FRENSIE_CHECK( full_reaction->isEnergyWithinEnergyGrid( Utility::PhysicalConstants::electron_rest_mass_energy ) );
  FRENSIE_CHECK( !full_reaction->isEnergyWithinEnergyGrid( 0.52 ) );
}

//---------------------------------------------------------------------------//
// Check that the cross section at a given energy can be returned
FRENSIE_UNIT_TEST( LineEnergyAdjointPhotoatomicReaction, getCrossSection )
{
  FRENSIE_CHECK_EQUAL( reaction->getCrossSection( 0.5 ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( reaction->getCrossSection( Utility::PhysicalConstants::electron_rest_mass_energy ),
                          14.739362127632583,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( reaction->getCrossSection( 0.52 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the cross section at a given energy can be returned
FRENSIE_UNIT_TEST( LineEnergyAdjointPhotoatomicReaction,
                   getCrossSection_indexed )
{
  FRENSIE_CHECK_EQUAL( reaction->getCrossSection( 0.5, 0 ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( reaction->getCrossSection( Utility::PhysicalConstants::electron_rest_mass_energy, 0 ),
                          14.739362127632583,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( reaction->getCrossSection( 0.52, 0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the line energy where the reaction is defined can be returned
FRENSIE_UNIT_TEST( LineEnergyAdjointPhotoatomicReaction, getLineEnergy )
{
  FRENSIE_CHECK_EQUAL( full_reaction->getLineEnergy(),
                       Utility::PhysicalConstants::electron_rest_mass_energy );
}

//---------------------------------------------------------------------------//
// Check that the max energy where the reaction is defined can be returned
FRENSIE_UNIT_TEST( LineEnergyAdjointPhotoatomicReaction, getMaxEnergy )
{
  FRENSIE_CHECK_EQUAL( reaction->getMaxEnergy(),
                       Utility::PhysicalConstants::electron_rest_mass_energy );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
FRENSIE_UNIT_TEST( LineEnergyAdjointPhotoatomicReaction, getThresholdEnergy )
{
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(),
                       Utility::PhysicalConstants::electron_rest_mass_energy );
}

//---------------------------------------------------------------------------//
// Check that the number of adjoint photons emitted from the reaction can be
// returned
FRENSIE_UNIT_TEST( LineEnergyAdjointPhotoatomicReaction,
                   getNumberOfEmittedAdjointPhotons )
{
  FRENSIE_CHECK_EQUAL( reaction->getNumberOfEmittedAdjointPhotons( 0.5 ), 0 );
  FRENSIE_CHECK_EQUAL( reaction->getNumberOfEmittedAdjointPhotons( Utility::PhysicalConstants::electron_rest_mass_energy ), 1 );
  FRENSIE_CHECK_EQUAL( reaction->getNumberOfEmittedAdjointPhotons( 0.52 ), 0 );
}

//---------------------------------------------------------------------------//
// Check that the number of adjoint electrons emitted from the reaction can be
// returned
FRENSIE_UNIT_TEST( LineEnergyAdjointPhotoatomicReaction,
                   getNumberOfEmittedAdjointElectrons )
{
  FRENSIE_CHECK_EQUAL( reaction->getNumberOfEmittedAdjointElectrons( 0.5 ), 0 );
  FRENSIE_CHECK_EQUAL( reaction->getNumberOfEmittedAdjointElectrons( Utility::PhysicalConstants::electron_rest_mass_energy ), 0 );
  FRENSIE_CHECK_EQUAL( reaction->getNumberOfEmittedAdjointElectrons( 0.52 ), 0 );
}

//---------------------------------------------------------------------------//
// Check that the number of adjoint positrons emitted from the reaction can be
// returned
FRENSIE_UNIT_TEST( LineEnergyAdjointPhotoatomicReaction,
                   getNumberOfEmittedAdjointPositrons )
{
  FRENSIE_CHECK_EQUAL( reaction->getNumberOfEmittedAdjointPositrons( 0.5 ), 0 );
  FRENSIE_CHECK_EQUAL( reaction->getNumberOfEmittedAdjointPositrons( Utility::PhysicalConstants::electron_rest_mass_energy ), 0 );
  FRENSIE_CHECK_EQUAL( reaction->getNumberOfEmittedAdjointPositrons( 0.52 ), 0 );
}

//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
FRENSIE_UNIT_TEST( LineEnergyAdjointPhotoatomicReaction, getReactionType )
{
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that a reaction can be simulated
FRENSIE_UNIT_TEST( LineEnergyAdjointPhotoatomicReaction, react )
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

  FRENSIE_CHECK( adjoint_photon_probe.isGone() );
  FRENSIE_CHECK_EQUAL( bank.size(), 1 );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::UNKNOWN_SUBSHELL );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getEnergy(), 
                                   2*Utility::PhysicalConstants::electron_rest_mass_energy,
                                   1e-15 );
  FRENSIE_CHECK_EQUAL( bank.top().getXDirection(), 1.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getYDirection(), 0.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getZDirection(), 0.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_native_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_native_file",
                                        test_native_file_name, "",
                                        "Test Native file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create the native data file container
  Data::AdjointElectronPhotonRelaxationDataContainer
    data_container( test_native_file_name );

  // Create the adjoint pair production distribution
  std::shared_ptr<MonteCarlo::LineEnergyAdjointPhotonScatteringDistribution>
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

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstLineEnergyAdjointPhotoatomicReaction.cpp
//---------------------------------------------------------------------------//
