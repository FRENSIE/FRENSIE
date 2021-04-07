//---------------------------------------------------------------------------//
//!
//! \file   tstCoherentAdjointPhotoatomicReaction.cpp
//! \author Alex Robinson
//! \brief  The coherent adjoint photoatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_CoherentAdjointPhotoatomicReaction.hpp"
#include "MonteCarlo_CoherentScatteringDistributionNativeFactory.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::AdjointPhotoatomicReaction> adjoint_coherent_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
FRENSIE_UNIT_TEST( CoherentAdjointPhotoatomicReaction, getReactionType )
{
  FRENSIE_CHECK_EQUAL( adjoint_coherent_reaction->getReactionType(),
                       MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
FRENSIE_UNIT_TEST( CoherentAdjointPhotatomicReaction, getThresholdEnergy )
{
  FRENSIE_CHECK_EQUAL( adjoint_coherent_reaction->getThresholdEnergy(), 1e-3 );
}

//---------------------------------------------------------------------------//
// Check that the max energy can be returned
FRENSIE_UNIT_TEST( CoherentAdjointPhotoatomicReaction, getMaxEnergy )
{
  FRENSIE_CHECK_EQUAL( adjoint_coherent_reaction->getMaxEnergy(), 20.0 );
}

//---------------------------------------------------------------------------//
// Check if an energy falls within the energy grid
FRENSIE_UNIT_TEST( CoherentAdjointPhotoatomicReaction,
                   isEnergyWithinEnergyGrid )
{
  FRENSIE_CHECK( !adjoint_coherent_reaction->isEnergyWithinEnergyGrid( 9e-4 ) );
  FRENSIE_CHECK( adjoint_coherent_reaction->isEnergyWithinEnergyGrid( 1e-3 ) );
  FRENSIE_CHECK( adjoint_coherent_reaction->isEnergyWithinEnergyGrid( 1.0 ) );
  FRENSIE_CHECK( adjoint_coherent_reaction->isEnergyWithinEnergyGrid( 20.0 ) );
  FRENSIE_CHECK( !adjoint_coherent_reaction->isEnergyWithinEnergyGrid( 20.1 ) );
}

//---------------------------------------------------------------------------//
// Check that the number of adjoint photons emitted from the reaction can be
// returned
FRENSIE_UNIT_TEST( CoherentAdjointPhotoatomicReaction,
                   getNumberOfEmittedAdjointPhotons )
{
  FRENSIE_CHECK_EQUAL( adjoint_coherent_reaction->getNumberOfEmittedAdjointPhotons( 9e-4 ),
                       0u );
  FRENSIE_CHECK_EQUAL( adjoint_coherent_reaction->getNumberOfEmittedAdjointPhotons( 1e-3 ),
                       1u );
  FRENSIE_CHECK_EQUAL( adjoint_coherent_reaction->getNumberOfEmittedAdjointPhotons( 20.0 ),
                       1u );
  FRENSIE_CHECK_EQUAL( adjoint_coherent_reaction->getNumberOfEmittedAdjointPhotons( 20.1 ),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of adjoint electrons emitted from the reaction can be
// returned
FRENSIE_UNIT_TEST( CoherentAdjointPhotoatomicReaction,
                   getNumberOfEmittedAdjointElectrons )
{
  FRENSIE_CHECK_EQUAL( adjoint_coherent_reaction->getNumberOfEmittedAdjointElectrons( 9e-4 ),
                       0u );
  FRENSIE_CHECK_EQUAL( adjoint_coherent_reaction->getNumberOfEmittedAdjointElectrons( 1e-3 ),
                       0u );
  FRENSIE_CHECK_EQUAL( adjoint_coherent_reaction->getNumberOfEmittedAdjointElectrons( 20.0 ),
                       0u );
  FRENSIE_CHECK_EQUAL( adjoint_coherent_reaction->getNumberOfEmittedAdjointElectrons( 20.1 ),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of adjoint positrons emitted from the reaction can be
// returned
FRENSIE_UNIT_TEST( CoherentAdjointPhotoatomicReaction,
                   getNumberOfEmittedAdjointPositrons )
{
  FRENSIE_CHECK_EQUAL( adjoint_coherent_reaction->getNumberOfEmittedAdjointPositrons( 9e-4 ),
                       0u );
  FRENSIE_CHECK_EQUAL( adjoint_coherent_reaction->getNumberOfEmittedAdjointPositrons( 1e-3 ),
                       0u );
  FRENSIE_CHECK_EQUAL( adjoint_coherent_reaction->getNumberOfEmittedAdjointPositrons( 20.0 ),
                       0u );
  FRENSIE_CHECK_EQUAL( adjoint_coherent_reaction->getNumberOfEmittedAdjointPositrons( 20.1 ),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
FRENSIE_UNIT_TEST( CoherentAdjointPhotoatomicReaction, getCrossSection )
{
  double cross_section =
    adjoint_coherent_reaction->getCrossSection( 1e-3 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 99.9639104922271571, 1e-12 );

  cross_section =
    adjoint_coherent_reaction->getCrossSection( 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.00783640704399895215, 1e-12 );

  cross_section =
    adjoint_coherent_reaction->getCrossSection( 20.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.96243862843467646e-05, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned (efficiently)
FRENSIE_UNIT_TEST( CoherentAdjointPhotoatomicReaction,
                   getCrossSection_efficient )
{
  double cross_section =
    adjoint_coherent_reaction->getCrossSection( 1e-3, 0u );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 99.9639104922271571, 1e-12 );

  cross_section =
    adjoint_coherent_reaction->getCrossSection( 20.0, 1261 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.96243862843467646e-05, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the coherent reaction can be simulated
FRENSIE_UNIT_TEST( CoherentAdjointPhotoatomicReaction, react )
{
  MonteCarlo::AdjointPhotonState adjoint_photon( 0 );
  adjoint_photon.setEnergy( 20.0 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  adjoint_coherent_reaction->react( adjoint_photon,
                                    bank,
                                    shell_of_interaction );

  FRENSIE_CHECK_EQUAL( adjoint_photon.getEnergy(), 20.0 );
  FRENSIE_CHECK( adjoint_photon.getZDirection() < 1.0 );
  FRENSIE_CHECK_EQUAL( adjoint_photon.getCollisionNumber(), 1 );
  FRENSIE_CHECK( bank.isEmpty() );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::UNKNOWN_SUBSHELL );
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

  // Create the reaction
  std::shared_ptr<std::vector<double> > incoming_energy_grid(
      new std::vector<double>( data_container.getAdjointPhotonEnergyGrid() ) );

  std::shared_ptr<std::vector<double> > coherent_cross_section(
      new std::vector<double>( data_container.getAdjointWallerHartreeCoherentCrossSection() ) );

  std::shared_ptr<const MonteCarlo::CoherentScatteringDistribution> scattering_distribution;

  MonteCarlo::CoherentScatteringDistributionNativeFactory::createEfficientCoherentDistribution(
                                                     data_container,
                                                     scattering_distribution );

  adjoint_coherent_reaction.reset(
     new MonteCarlo::CoherentAdjointPhotoatomicReaction<Utility::LinLin,false>(
                                                   incoming_energy_grid,
                                                   coherent_cross_section,
                                                   0u,
                                                   scattering_distribution ) );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstCoherentAdjointPhotoatomicReaction.cpp
//---------------------------------------------------------------------------//
