//---------------------------------------------------------------------------//
//!
//! \file   tstAtomicExcitationAdjointElectroatomicReaction.cpp
//! \author Luke Kersting
//! \brief  Atomic Excitation Adjoint electroatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_AtomicExcitationAdjointElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_AtomicExcitationAdjointElectronScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_AtomicExcitationAdjointElectroatomicReaction.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::AdjointElectroatomicReaction>
    ace_excitation_reaction, native_excitation_reaction;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
bool notEqualZero( double value )
{
  return value != 0.0;
}

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
TEUCHOS_UNIT_TEST( AtomicExcitationAdjointElectroatomicReaction, getReactionType )
{
  TEST_EQUALITY_CONST( ace_excitation_reaction->getReactionType(),
                 MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( native_excitation_reaction->getReactionType(),
                 MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
TEUCHOS_UNIT_TEST( AtomicExcitationAdjointElectroatomicReaction, getThresholdEnergy )
{
  TEST_EQUALITY_CONST( ace_excitation_reaction->getThresholdEnergy(), 1e-05 );

  TEST_EQUALITY_CONST( native_excitation_reaction->getThresholdEnergy(), 1e-05 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( AtomicExcitationAdjointElectroatomicReaction, getNumberOfEmittedElectrons )
{
  TEST_EQUALITY_CONST( ace_excitation_reaction->getNumberOfEmittedElectrons(1e-3),
                       0u );

  TEST_EQUALITY_CONST( ace_excitation_reaction->getNumberOfEmittedElectrons(20.0),
                       0u );

  TEST_EQUALITY_CONST( native_excitation_reaction->getNumberOfEmittedElectrons(1e-3),
                       0u );

  TEST_EQUALITY_CONST( native_excitation_reaction->getNumberOfEmittedElectrons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( AtomicExcitationAdjointElectroatomicReaction, getNumberOfEmittedPhotons )
{
  TEST_EQUALITY_CONST( ace_excitation_reaction->getNumberOfEmittedPhotons(1e-3),
                       0u );

  TEST_EQUALITY_CONST( ace_excitation_reaction->getNumberOfEmittedPhotons(20.0),
                       0u );

  TEST_EQUALITY_CONST( native_excitation_reaction->getNumberOfEmittedPhotons(1e-3),
                       0u );

  TEST_EQUALITY_CONST( native_excitation_reaction->getNumberOfEmittedPhotons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
TEUCHOS_UNIT_TEST( AtomicExcitationAdjointElectroatomicReaction, getCrossSection_ace )
{
  double cross_section = ace_excitation_reaction->getCrossSection( 9e-05 );
  TEST_FLOATING_EQUALITY( cross_section, 1.16042e+09, 1e-12 );

  cross_section = ace_excitation_reaction->getCrossSection( 4e-04 );
  TEST_FLOATING_EQUALITY( cross_section, 6.22682e+08, 1e-12 );

  cross_section = ace_excitation_reaction->getCrossSection( 2e-03 );
  TEST_FLOATING_EQUALITY( cross_section, 1.96517e+08, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
TEUCHOS_UNIT_TEST( AtomicExcitationAdjointElectroatomicReaction, getCrossSection_native )
{
  double cross_section = native_excitation_reaction->getCrossSection( 1e-5 );
  TEST_FLOATING_EQUALITY( cross_section, 6.12229969785753563e+07, 1e-12 );

  cross_section =
    native_excitation_reaction->getCrossSection( 6.20350838928222553e-04 );
  TEST_FLOATING_EQUALITY( cross_section, 1.58264020015645381e+07, 1e-12 );

  cross_section = native_excitation_reaction->getCrossSection( 20.0 );
  TEST_FLOATING_EQUALITY( cross_section, 8.18292998537648382e+04, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the atomic excitation reaction can be simulated
TEUCHOS_UNIT_TEST( AtomicExcitationAdjointElectroatomicReaction, react_ace )
{
  MonteCarlo::AdjointElectronState electron( 0 );
  electron.setEnergy( 1e-3 - 9.32298e-6 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  ace_excitation_reaction->react( electron, bank, shell_of_interaction );

  TEST_FLOATING_EQUALITY( electron.getEnergy(), 1e-3, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 1.0, 1e-12 );
  TEST_ASSERT( bank.isEmpty() );
  TEST_EQUALITY_CONST( shell_of_interaction, Data::UNKNOWN_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that the atomic excitation reaction can be simulated
TEUCHOS_UNIT_TEST( AtomicExcitationAdjointElectroatomicReaction, react_native )
{
  MonteCarlo::AdjointElectronState electron( 0 );
  electron.setEnergy( 9.2946e-06 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  double final_energy = 9.2946e-06 + 1.57054e-05;

  native_excitation_reaction->react( electron, bank, shell_of_interaction );

  TEST_FLOATING_EQUALITY( electron.getEnergy(), final_energy, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 1.0, 1e-12 );
  TEST_ASSERT( bank.isEmpty() );
  TEST_EQUALITY_CONST( shell_of_interaction, Data::UNKNOWN_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_ace_file_name, test_ace_table_name, test_native_file_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_ace_file",
                   &test_ace_file_name,
                   "Test ACE file name" );
  clp().setOption( "test_ace_table",
                   &test_ace_table_name,
                   "Test ACE table name" );
  clp().setOption( "test_native_file",
                   &test_native_file_name,
                   "Test Native file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Create ACE Reaction
  {
    // Create a file handler and data extractor
    Teuchos::RCP<Data::ACEFileHandler> ace_file_handler(
       new Data::ACEFileHandler( test_ace_file_name,
                                 test_ace_table_name,
                                 1u ) );
    Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor(
      new Data::XSSEPRDataExtractor( ace_file_handler->getTableNXSArray(),
                                     ace_file_handler->getTableJXSArray(),
                                     ace_file_handler->getTableXSSArray() ) );

    // Extract the energy grid and cross section
    Teuchos::ArrayRCP<double> energy_grid;
    energy_grid.deepCopy( xss_data_extractor->extractElectronEnergyGrid() );

    Teuchos::ArrayView<const double> raw_excitation_cross_section =
      xss_data_extractor->extractExcitationCrossSection();

    Teuchos::ArrayView<const double>::iterator start =
      std::find_if( raw_excitation_cross_section.begin(),
                    raw_excitation_cross_section.end(),
                    notEqualZero );

    Teuchos::ArrayRCP<double> excitation_cross_section;
    excitation_cross_section.assign( start, raw_excitation_cross_section.end() );

    unsigned excitation_threshold_index =
      energy_grid.size() - excitation_cross_section.size();

    std::shared_ptr<const MonteCarlo::AtomicExcitationAdjointElectronScatteringDistribution>
        scattering_distribution;

    MonteCarlo::AtomicExcitationAdjointElectronScatteringDistributionACEFactory::createAtomicExcitationAdjointDistribution(
      *xss_data_extractor,
      scattering_distribution );

    // Create the reaction
    ace_excitation_reaction.reset(
      new MonteCarlo::AtomicExcitationAdjointElectroatomicReaction<Utility::LinLin>(
            energy_grid,
            excitation_cross_section,
            excitation_threshold_index,
            scattering_distribution ) );

    // Clear setup data
    ace_file_handler.reset();
    xss_data_extractor.reset();
  }

  // Create Native Reaction
  {
    // Get native data container
    Data::AdjointElectronPhotonRelaxationDataContainer data_container =
      Data::AdjointElectronPhotonRelaxationDataContainer( test_native_file_name );

    std::shared_ptr<const MonteCarlo::AtomicExcitationAdjointElectronScatteringDistribution>
        scattering_distribution;

    MonteCarlo::AtomicExcitationAdjointElectronScatteringDistributionNativeFactory::createAtomicExcitationAdjointDistribution(
      data_container,
      scattering_distribution );

    // Get the energy grid
    Teuchos::ArrayRCP<double> energy_grid;
    energy_grid.assign(
        data_container.getAdjointElectronEnergyGrid().begin(),
        data_container.getAdjointElectronEnergyGrid().end() );

    // Get the cross section
    Teuchos::ArrayRCP<double> cross_section;
    cross_section.assign(
        data_container.getAdjointAtomicExcitationCrossSection().begin(),
        data_container.getAdjointAtomicExcitationCrossSection().end() );

    // Create the reaction
    native_excitation_reaction.reset(
      new MonteCarlo::AtomicExcitationAdjointElectroatomicReaction<Utility::LinLin>(
        energy_grid,
        cross_section,
        data_container.getAdjointAtomicExcitationCrossSectionThresholdEnergyIndex(),
        scattering_distribution ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAtomicExcitationAdjointElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
