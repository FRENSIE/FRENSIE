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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_CoherentAdjointPhotoatomicReaction.hpp"
#include "MonteCarlo_CoherentScatteringDistributionNativeFactory.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_InverseSquareAngstromUnit.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::AdjointPhotoatomicReaction> adjoint_coherent_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
TEUCHOS_UNIT_TEST( CoherentAdjointPhotoatomicReaction, getReactionType )
{
  TEST_EQUALITY_CONST( adjoint_coherent_reaction->getReactionType(),
                       MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
TEUCHOS_UNIT_TEST( CoherentAdjointPhotatomicReaction, getThresholdEnergy )
{
  TEST_EQUALITY_CONST( adjoint_coherent_reaction->getThresholdEnergy(), 1e-3 );
}

//---------------------------------------------------------------------------//
// Check that the max energy can be returned
TEUCHOS_UNIT_TEST( CoherentAdjointPhotoatomicReaction, getMaxEnergy )
{
  TEST_EQUALITY_CONST( adjoint_coherent_reaction->getMaxEnergy(), 20.0 );
}

//---------------------------------------------------------------------------//
// Check if an energy falls within the energy grid
TEUCHOS_UNIT_TEST( CoherentAdjointPhotoatomicReaction,
                   isEnergyWithinEnergyGrid )
{
  TEST_ASSERT( !adjoint_coherent_reaction->isEnergyWithinEnergyGrid( 9e-4 ) );
  TEST_ASSERT( adjoint_coherent_reaction->isEnergyWithinEnergyGrid( 1e-3 ) );
  TEST_ASSERT( adjoint_coherent_reaction->isEnergyWithinEnergyGrid( 1.0 ) );
  TEST_ASSERT( adjoint_coherent_reaction->isEnergyWithinEnergyGrid( 20.0 ) );
  TEST_ASSERT( !adjoint_coherent_reaction->isEnergyWithinEnergyGrid( 20.1 ) );
}

//---------------------------------------------------------------------------//
// Check that the number of adjoint photons emitted from the reaction can be
// returned
TEUCHOS_UNIT_TEST( CoherentAdjointPhotoatomicReaction,
                   getNumberOfEmittedPhotons )
{
  TEST_EQUALITY_CONST( adjoint_coherent_reaction->getNumberOfEmittedPhotons( 9e-4 ),
                       0u );
  TEST_EQUALITY_CONST( adjoint_coherent_reaction->getNumberOfEmittedPhotons( 1e-3 ),
                       1u );
  TEST_EQUALITY_CONST( adjoint_coherent_reaction->getNumberOfEmittedPhotons( 20.0 ),
                       1u );
  TEST_EQUALITY_CONST( adjoint_coherent_reaction->getNumberOfEmittedPhotons( 20.1 ),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of adjoint electrons emitted from the reaction can be
// returned
TEUCHOS_UNIT_TEST( CoherentAdjointPhotoatomicReaction,
                   getNumberOfEmittedElectrons )
{
  TEST_EQUALITY_CONST( adjoint_coherent_reaction->getNumberOfEmittedElectrons( 9e-4 ),
                       0u );
  TEST_EQUALITY_CONST( adjoint_coherent_reaction->getNumberOfEmittedElectrons( 1e-3 ),
                       0u );
  TEST_EQUALITY_CONST( adjoint_coherent_reaction->getNumberOfEmittedElectrons( 20.0 ),
                       0u );
  TEST_EQUALITY_CONST( adjoint_coherent_reaction->getNumberOfEmittedElectrons( 20.1 ),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
TEUCHOS_UNIT_TEST( CoherentAdjointPhotoatomicReaction, getCrossSection )
{
  double cross_section = 
    adjoint_coherent_reaction->getCrossSection( 1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 99.9639104922271571, 1e-12 );

  cross_section =
    adjoint_coherent_reaction->getCrossSection( 1.0 );

  TEST_FLOATING_EQUALITY( cross_section, 0.00783640704399895215, 1e-12 );

  cross_section =
    adjoint_coherent_reaction->getCrossSection( 20.0 );

  TEST_FLOATING_EQUALITY( cross_section, 1.96243862843467646e-05, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned (efficiently)
TEUCHOS_UNIT_TEST( CoherentAdjointPhotoatomicReaction,
                   getCrossSection_efficient )
{
  double cross_section = 
    adjoint_coherent_reaction->getCrossSection( 1e-3, 0u );
  
  TEST_FLOATING_EQUALITY( cross_section, 99.9639104922271571, 1e-12 );

  cross_section =
    adjoint_coherent_reaction->getCrossSection( 20.0, 1166 );

  TEST_FLOATING_EQUALITY( cross_section, 1.96243862843467646e-05, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the coherent reaction can be simulated
TEUCHOS_UNIT_TEST( CoherentAdjointPhotoatomicReaction, react )
{
  MonteCarlo::AdjointPhotonState adjoint_photon( 0 );
  adjoint_photon.setEnergy( 20.0 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  adjoint_coherent_reaction->react( adjoint_photon,
                                    bank,
                                    shell_of_interaction );

  TEST_EQUALITY_CONST( adjoint_photon.getEnergy(), 20.0 );
  TEST_ASSERT( adjoint_photon.getZDirection() < 1.0 );
  TEST_EQUALITY_CONST( adjoint_photon.getCollisionNumber(), 1 );
  TEST_ASSERT( bank.isEmpty() );
  TEST_EQUALITY_CONST( shell_of_interaction, Data::UNKNOWN_SUBSHELL );
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

  // Create the reaction
  Teuchos::ArrayRCP<double> incoming_energy_grid;
  incoming_energy_grid.assign(
                           data_container.getAdjointPhotonEnergyGrid().begin(),
                           data_container.getAdjointPhotonEnergyGrid().end() );
  std::cout << incoming_energy_grid.size() << std::endl;
  Teuchos::ArrayRCP<double> coherent_cross_section;
  coherent_cross_section.assign(
          data_container.getAdjointWallerHartreeCoherentCrossSection().begin(),
          data_container.getAdjointWallerHartreeCoherentCrossSection().end() );

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

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstCoherentAdjointPhotoatomicReaction.cpp
//---------------------------------------------------------------------------//
