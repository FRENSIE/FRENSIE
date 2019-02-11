//---------------------------------------------------------------------------//
//!
//! \file   tstAbsorptionAdjointElectroatomicReaction.cpp
//! \author Luke Kersting
//! \brief  Absorption adjoint electroatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_AbsorptionAdjointElectroatomicReaction.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::AdjointElectroatomicReaction> absorption_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
FRENSIE_UNIT_TEST( AbsorptionAdjointElectroatomicReaction, getReactionType )
{
  FRENSIE_CHECK_EQUAL( absorption_reaction->getReactionType(),
                       MonteCarlo::TOTAL_ADJOINT_ELECTROATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
FRENSIE_UNIT_TEST( AbsorptionAdjointElectroatomicReaction, getThresholdEnergy )
{
  FRENSIE_CHECK_EQUAL( absorption_reaction->getThresholdEnergy(),
                       1e-5 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( AbsorptionAdjointElectroatomicReaction,
                   getNumberOfEmittedAdjointElectrons )
{
  FRENSIE_CHECK_EQUAL( absorption_reaction->getNumberOfEmittedAdjointElectrons( 1e-3 ),
                       0u );

  FRENSIE_CHECK_EQUAL( absorption_reaction->getNumberOfEmittedAdjointElectrons( 20.0 ),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( AbsorptionAdjointElectroatomicReaction,
                   getNumberOfEmittedAdjointPhotons )
{
  FRENSIE_CHECK_EQUAL( absorption_reaction->getNumberOfEmittedAdjointPhotons( 1e-3 ),
                       0u );

  FRENSIE_CHECK_EQUAL( absorption_reaction->getNumberOfEmittedAdjointPhotons( 20.0 ),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of positrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( AbsorptionAdjointElectroatomicReaction,
                   getNumberOfEmittedAdjointPositrons )
{
  FRENSIE_CHECK_EQUAL( absorption_reaction->getNumberOfEmittedAdjointPositrons( 1e-3 ),
                       0u );

  FRENSIE_CHECK_EQUAL( absorption_reaction->getNumberOfEmittedAdjointPositrons( 20.0 ),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
FRENSIE_UNIT_TEST( AbsorptionAdjointElectroatomicReaction, getCrossSection )
{
  double cross_section = absorption_reaction->getCrossSection( 1e-5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.422553386152458188e+01, 1e-12 );

  cross_section = absorption_reaction->getCrossSection( 2e-2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.615627502403220728, 1e-12 );

  cross_section = absorption_reaction->getCrossSection( 20.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 7.140740238621433311e-02, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the absorption reaction can be simulated
FRENSIE_UNIT_TEST( AbsorptionAdjointElectroatomicReaction, react )
{
  MonteCarlo::AdjointElectronState electron( 0 );
  electron.setEnergy( 20.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  absorption_reaction->react( electron, bank, shell_of_interaction );

  FRENSIE_CHECK( electron.isGone() );
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

    // Get the energy grid
    auto energy_grid = std::make_shared<const std::vector<double> >( data_container.getAdjointElectronEnergyGrid() );

    // Get the cross section (use the brem cross sections as a filler)
    std::vector<double> temp = data_container.getAdjointBremsstrahlungElectronCrossSection();
    temp.back() = temp[temp.size()-2]/2.0;

    auto cross_section = std::make_shared<const std::vector<double> >( temp );

    // Create the reaction
    absorption_reaction.reset(
      new MonteCarlo::AbsorptionAdjointElectroatomicReaction<Utility::LogLog>(
        energy_grid,
        cross_section,
        data_container.getAdjointBremsstrahlungElectronCrossSectionThresholdEnergyIndex(),
        MonteCarlo::TOTAL_ADJOINT_ELECTROATOMIC_REACTION ) );
  }
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAbsorptionAdjointElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
