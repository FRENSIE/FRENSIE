//---------------------------------------------------------------------------//
//!
//! \file   tstAtomicExcitationAdjointElectroatomicReaction.cpp
//! \author Luke Kersting
//! \brief  Atomic Excitation adjoint electroatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_AtomicExcitationAdjointElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_AtomicExcitationAdjointElectroatomicReaction.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::AdjointElectroatomicReaction>
    excitation_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
FRENSIE_UNIT_TEST( AtomicExcitationAdjointElectroatomicReaction, getReactionType )
{
  FRENSIE_CHECK_EQUAL( excitation_reaction->getReactionType(),
                 MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
FRENSIE_UNIT_TEST( AtomicExcitationAdjointElectroatomicReaction, getThresholdEnergy )
{
  FRENSIE_CHECK_EQUAL( excitation_reaction->getThresholdEnergy(), 1e-05 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( AtomicExcitationAdjointElectroatomicReaction, getNumberOfEmittedAdjointElectrons )
{
  FRENSIE_CHECK_EQUAL( excitation_reaction->getNumberOfEmittedAdjointElectrons(1e-3),
                       1u );

  FRENSIE_CHECK_EQUAL( excitation_reaction->getNumberOfEmittedAdjointElectrons(20.0),
                       1u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( AtomicExcitationAdjointElectroatomicReaction, getNumberOfEmittedAdjointPhotons )
{
  FRENSIE_CHECK_EQUAL( excitation_reaction->getNumberOfEmittedAdjointPhotons(1e-3),
                       0u );

  FRENSIE_CHECK_EQUAL( excitation_reaction->getNumberOfEmittedAdjointPhotons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of positron emitted from the rxn can be returned
FRENSIE_UNIT_TEST( AtomicExcitationAdjointElectroatomicReaction, getNumberOfEmittedAdjointPositrons )
{
  FRENSIE_CHECK_EQUAL( excitation_reaction->getNumberOfEmittedAdjointPositrons(1e-3),
                       0u );

  FRENSIE_CHECK_EQUAL( excitation_reaction->getNumberOfEmittedAdjointPositrons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
FRENSIE_UNIT_TEST( AtomicExcitationAdjointElectroatomicReaction, getCrossSection )
{
  double cross_section = excitation_reaction->getCrossSection( 1e-5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.124055828282346576e+07, 1e-12 );

  cross_section = excitation_reaction->getCrossSection( 1e-3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.050254326707092859e+07, 1e-12 );

  cross_section = excitation_reaction->getCrossSection( 20.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.182929983612992510e+04, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the atomic excitation reaction can be simulated
FRENSIE_UNIT_TEST( AtomicExcitationAdjointElectroatomicReaction, react )
{
  MonteCarlo::AdjointElectronState electron( 0 );
  electron.setEnergy( 1.99999789891999988e+01 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  excitation_reaction->react( electron, bank, shell_of_interaction );

  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getEnergy(), 20.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getZDirection(), 1.0, 1e-12 );
  FRENSIE_CHECK( bank.isEmpty() );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::UNKNOWN_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Custom setup
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
  // Create Native Reaction
  {
    // Get native data container
    Data::AdjointElectronPhotonRelaxationDataContainer data_container =
      Data::AdjointElectronPhotonRelaxationDataContainer( test_native_file_name );

    std::shared_ptr<MonteCarlo::AtomicExcitationAdjointElectronScatteringDistribution>
        scattering_distribution;

    MonteCarlo::AtomicExcitationAdjointElectronScatteringDistributionNativeFactory::createAtomicExcitationDistribution(
      data_container,
      scattering_distribution );

    // Get the energy grid
    auto energy_grid =
       std::make_shared<const std::vector<double> >( data_container.getAdjointElectronEnergyGrid() );

    // Get the cross section
    auto cross_section =
      std::make_shared<const std::vector<double> >( data_container.getAdjointAtomicExcitationCrossSection() );

    // Create the reaction
    excitation_reaction.reset(
      new MonteCarlo::AtomicExcitationAdjointElectroatomicReaction<Utility::LogLog>(
        energy_grid,
        cross_section,
        data_container.getAdjointAtomicExcitationCrossSectionThresholdEnergyIndex(),
        scattering_distribution ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAtomicExcitationAdjointElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
