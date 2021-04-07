//---------------------------------------------------------------------------//
//!
//! \file   tstPositronatomCoreACE.cpp
//! \author Luke Kersting
//! \brief  PositronatomCore unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <algorithm>

// FRENSIE Includes
#include "MonteCarlo_PositronatomCore.hpp"
#include "MonteCarlo_BremsstrahlungPositronatomicReaction.hpp"
#include "MonteCarlo_BremsstrahlungElectronScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_AtomicExcitationPositronatomicReaction.hpp"
#include "MonteCarlo_VoidAbsorptionPositronatomicReaction.hpp"
#include "MonteCarlo_VoidAtomicRelaxationModel.hpp"
#include "MonteCarlo_PositronState.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::PositronatomCore> ace_positronatom_core;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
bool notEqualZero( const double value )
{
  return value != 0.0;
}

//---------------------------------------------------------------------------//
// Check that the total reaction can be returned
FRENSIE_UNIT_TEST( PositronatomCore, getTotalReaction_ace )
{
  const MonteCarlo::PositronatomicReaction& total_reaction =
    ace_positronatom_core->getTotalReaction();

  double cross_section = total_reaction.getCrossSection( 2e-3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.258661418255E+03 + 1.96517E+08, 1e-12 );

  cross_section = total_reaction.getCrossSection( 4e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.914234996439E+03 + 6.22682E+08, 1e-12 );

  cross_section = total_reaction.getCrossSection( 9e-5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 7.249970966838E+03 + 1.16042E+09, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the absorption reaction can be returned
FRENSIE_UNIT_TEST( PositronatomCore, getTotalAbsorptionReaction_ace )
{
  const MonteCarlo::PositronatomicReaction& absorption_reaction =
    ace_positronatom_core->getTotalAbsorptionReaction();

  double cross_section = absorption_reaction.getCrossSection( 1.e-2 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = absorption_reaction.getCrossSection( 2e-3 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = absorption_reaction.getCrossSection( 4e-4 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = absorption_reaction.getCrossSection( 9e-5 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the scattering reactions can be returned
FRENSIE_UNIT_TEST( PositronatomCore, getScatteringReactions_ace )
{
  const MonteCarlo::PositronatomCore::ConstReactionMap& scattering_reactions =
    ace_positronatom_core->getScatteringReactions();

  FRENSIE_CHECK_EQUAL( scattering_reactions.size(), 2 );

  const MonteCarlo::PositronatomicReaction& ae_reaction =
    *(scattering_reactions.find(MonteCarlo::ATOMIC_EXCITATION_POSITRONATOMIC_REACTION)->second);

  const MonteCarlo::PositronatomicReaction& b_reaction =
    *(scattering_reactions.find(MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION)->second);

  double cross_section =
    ae_reaction.getCrossSection( 2e-3 ) +
     b_reaction.getCrossSection( 2e-3 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          9.258661418255E+03 + 1.96517E+08,
                          1e-12 );

  cross_section = ae_reaction.getCrossSection( 4e-4 ) +
                   b_reaction.getCrossSection( 4e-4 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          8.914234996439E+03 + 6.22682E+08,
                          1e-12 );

  cross_section = ae_reaction.getCrossSection( 9e-5 ) +
                   b_reaction.getCrossSection( 9e-5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          7.249970966838E+03 + 1.16042E+09,
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the scattering reaction types can be returned
FRENSIE_UNIT_TEST( PositronatomCore, getScatteringReactionTypes_ace )
{
  MonteCarlo::PositronatomCore::ReactionEnumTypeSet reaction_types;

  ace_positronatom_core->getScatteringReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 2 );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::ATOMIC_EXCITATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION ) );
}

//---------------------------------------------------------------------------//
// Check that the absorption reactions can be returned
FRENSIE_UNIT_TEST( PositronatomCore, getAbsorptionReactions_ace )
{
  const MonteCarlo::PositronatomCore::ConstReactionMap& absorption_reactions =
    ace_positronatom_core->getAbsorptionReactions();

  FRENSIE_CHECK_EQUAL( absorption_reactions.size(), 0 );

}

//---------------------------------------------------------------------------//
// Check that the absorption reaction types can be returned
FRENSIE_UNIT_TEST( PositronatomCore, getAbsorptionReactionTypes_ace )
{
  MonteCarlo::PositronatomCore::ReactionEnumTypeSet reaction_types;

  ace_positronatom_core->getAbsorptionReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that miscellaneous reactions can be returned
FRENSIE_UNIT_TEST( PositronatomCore, getMiscReactions_ace )
{
  const MonteCarlo::PositronatomCore::ConstReactionMap& misc_reactions =
    ace_positronatom_core->getMiscReactions();

  FRENSIE_CHECK_EQUAL( misc_reactions.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the misc reaction types can be returned
FRENSIE_UNIT_TEST( PositronatomCore, getMiscReactionTypes_ace )
{
  MonteCarlo::PositronatomCore::ReactionEnumTypeSet reaction_types;

  ace_positronatom_core->getMiscReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the reaction types can be returned
FRENSIE_UNIT_TEST( PositronatomCore, getReactionTypes_ace )
{
  MonteCarlo::PositronatomCore::ReactionEnumTypeSet reaction_types;

  ace_positronatom_core->getReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 3 );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::ATOMIC_EXCITATION_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::TOTAL_POSITRONATOMIC_REACTION ) );
}

//---------------------------------------------------------------------------//
// Check that the atomic relaxation model can be returned
FRENSIE_UNIT_TEST( PositronatomCore, getAtomicRelaxationModel_ace )
{
  Data::SubshellType vacancy = Data::K_SUBSHELL;

  MonteCarlo::PositronState positron( 0u );
  positron.setEnergy( 1.0 );
  positron.setDirection( 0.0, 0.0, 1.0 );
  positron.setPosition( 0.0, 0.0, 0.0 );

  MonteCarlo::ParticleBank bank;

  const MonteCarlo::AtomicRelaxationModel& relaxation_model =
    ace_positronatom_core->getAtomicRelaxationModel();

  relaxation_model.relaxAtom( vacancy, positron, bank );

  FRENSIE_CHECK_EQUAL( bank.size(), 0u );
}

//---------------------------------------------------------------------------//
// Custom setup
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

  // Create the atomic excitation, bremsstrahlung cross sections
  std::shared_ptr<const std::vector<double> > energy_grid(
       new std::vector<double>( xss_data_extractor->extractElectronEnergyGrid() ) );

  // Create the hash-based grid searcher
  std::shared_ptr<Utility::HashBasedGridSearcher<double> > grid_searcher(
       new Utility::StandardHashBasedGridSearcher<std::vector<double>,false>(
                                             energy_grid,
                                             energy_grid->front(),
                                             energy_grid->back(),
                                             100 ) );

  Utility::ArrayView<const double> raw_ae_cross_section =
    xss_data_extractor->extractExcitationCrossSection();

  Utility::ArrayView<const double>::iterator start =
    std::find_if( raw_ae_cross_section.begin(),
                  raw_ae_cross_section.end(),
                  notEqualZero );

  std::shared_ptr<const std::vector<double> > ae_cross_section(
                new std::vector<double>( start, raw_ae_cross_section.end() ) );

  size_t ae_threshold_index =
    energy_grid->size() - ae_cross_section->size();

  // Extract the atomic excitation information data block (EXCIT)
  Utility::ArrayView<const double> excit_block(
                                      xss_data_extractor->extractEXCITBlock() );

  // Extract the number of tabulated energies
  int size = excit_block.size()/2;

  // Extract the energy grid for atomic excitation energy loss
  std::vector<double> ae_energy_grid(excit_block(0,size));
  
  // Extract the energy loss for atomic excitation
  std::vector<double> energy_loss(excit_block(size,size));
  
  // Create the energy loss distributions
  MonteCarlo::AtomicExcitationElectronScatteringDistribution::AtomicDistribution
    ae_energy_loss_function;
  
  ae_energy_loss_function.reset(
      new Utility::TabularDistribution<Utility::LinLin>( ae_energy_grid,
                                                         energy_loss ) );

  std::shared_ptr<const MonteCarlo::AtomicExcitationElectronScatteringDistribution>
    ae_energy_loss_distribution;

  ae_energy_loss_distribution.reset(
    new MonteCarlo::AtomicExcitationElectronScatteringDistribution(
                      ae_energy_loss_function ) );

  std::shared_ptr<MonteCarlo::PositronatomicReaction> ae_reaction(
            new MonteCarlo::AtomicExcitationPositronatomicReaction<Utility::LinLin>(
                            energy_grid,
                            ae_cross_section,
                            ae_threshold_index,
                            ae_energy_loss_distribution ) );

  // Bremsstrahlung
  Utility::ArrayView<const double> raw_b_cross_section =
    xss_data_extractor->extractBremsstrahlungCrossSection();

  start = std::find_if( raw_b_cross_section.begin(),
                        raw_b_cross_section.end(),
                        notEqualZero );

  std::shared_ptr<const std::vector<double> > b_cross_section(
                 new std::vector<double>( start, raw_b_cross_section.end() ) );

  size_t b_threshold_index =
    energy_grid->size() - b_cross_section->size();

  std::shared_ptr<const MonteCarlo::BremsstrahlungElectronScatteringDistribution>
    b_scattering_distribution;


  MonteCarlo::BremsstrahlungElectronScatteringDistributionACEFactory::createBremsstrahlungDistribution(
        xss_data_extractor->extractAtomicNumber(),
        *xss_data_extractor,
        b_scattering_distribution );

  // Create the bremsstrahlung scattering reaction
  std::shared_ptr<MonteCarlo::PositronatomicReaction> b_reaction(
          new MonteCarlo::BremsstrahlungPositronatomicReaction<Utility::LinLin>(
            energy_grid,
            b_cross_section,
            b_threshold_index,
            b_scattering_distribution ) );

  // Create the reaction maps
  MonteCarlo::PositronatomCore::ConstReactionMap scattering_reactions,
    absorption_reactions;

  scattering_reactions[ae_reaction->getReactionType()] = ae_reaction;
  
  scattering_reactions[b_reaction->getReactionType()] = b_reaction;
  
  // Create a void atomic relaxation model
  std::shared_ptr<MonteCarlo::AtomicRelaxationModel> relaxation_model(
                                   new MonteCarlo::VoidAtomicRelaxationModel );

  // Create a test positronatom core
  ace_positronatom_core.reset(
      new MonteCarlo::PositronatomCore( energy_grid,
                                        grid_searcher,
                                        scattering_reactions,
                                        absorption_reactions,
                                        relaxation_model,
                                        false,
                                        Utility::LinLin() ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstPositronatomCoreACE.cpp
//---------------------------------------------------------------------------//
