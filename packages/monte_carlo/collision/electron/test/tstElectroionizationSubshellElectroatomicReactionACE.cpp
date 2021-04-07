//---------------------------------------------------------------------------//
//!
//! \file   tstElectroionizationSubshellElectroatomicReactionACE.cpp
//! \author Luke Kersting
//! \brief  Electroionization Subshell electroatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationSubshellElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_ElectroatomicReactionType.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Data_SubshellType.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::ElectroionizationSubshellElectroatomicReaction<Utility::LinLin> >
    ace_first_subshell_reaction, ace_last_subshell_reaction;

double max_ionization_subshell_adjoint_energy;

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
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectroatomicReaction, getReactionType_ace )
{
  FRENSIE_CHECK_EQUAL( ace_first_subshell_reaction->getReactionType(),
                       MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( ace_last_subshell_reaction->getReactionType(),
                       MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectroatomicReaction, getThresholdEnergy_ace )
{
  FRENSIE_CHECK_EQUAL( ace_first_subshell_reaction->getThresholdEnergy(),
                       8.9754e-2 );

  FRENSIE_CHECK_EQUAL( ace_last_subshell_reaction->getThresholdEnergy(),
                       1e-5 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectroatomicReaction, getNumberOfEmittedElectrons_ace )
{
  FRENSIE_CHECK_EQUAL( ace_first_subshell_reaction->getNumberOfEmittedElectrons(1e-3),
                       0u );

  FRENSIE_CHECK_EQUAL( ace_first_subshell_reaction->getNumberOfEmittedElectrons(20.0),
                       2u );

  FRENSIE_CHECK_EQUAL( ace_last_subshell_reaction->getNumberOfEmittedElectrons(1e-3),
                       2u );

  FRENSIE_CHECK_EQUAL( ace_last_subshell_reaction->getNumberOfEmittedElectrons(20.0),
                       2u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectroatomicReaction, getNumberOfEmittedPhotons_ace )
{
  FRENSIE_CHECK_EQUAL( ace_first_subshell_reaction->getNumberOfEmittedPhotons(1e-3),
                       0u );

  FRENSIE_CHECK_EQUAL( ace_first_subshell_reaction->getNumberOfEmittedPhotons(20.0),
                       0u );

  FRENSIE_CHECK_EQUAL( ace_last_subshell_reaction->getNumberOfEmittedPhotons(1e-3),
                       0u );

  FRENSIE_CHECK_EQUAL( ace_last_subshell_reaction->getNumberOfEmittedPhotons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of positrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectroatomicReaction, getNumberOfEmittedPositrons_ace )
{
  FRENSIE_CHECK_EQUAL( ace_first_subshell_reaction->getNumberOfEmittedPositrons(1e-3),
                       0u );

  FRENSIE_CHECK_EQUAL( ace_first_subshell_reaction->getNumberOfEmittedPositrons(20.0),
                       0u );

  FRENSIE_CHECK_EQUAL( ace_last_subshell_reaction->getNumberOfEmittedPositrons(1e-3),
                       0u );

  FRENSIE_CHECK_EQUAL( ace_last_subshell_reaction->getNumberOfEmittedPositrons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectroatomicReaction, getCrossSection_ace )
{
  // First Subshell
  double cross_section =
    ace_first_subshell_reaction->getCrossSection( 2e-1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.991897715052E+00, 1e-12 );

  cross_section =
    ace_first_subshell_reaction->getCrossSection( 1.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.174906212079E+01, 1e-12 );

  cross_section =
    ace_first_subshell_reaction->getCrossSection( 6e1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.443293975497E+01, 1e-12 );

  // Last Subshell
  cross_section =
    ace_last_subshell_reaction->getCrossSection( 2e-1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.567266284782E+05, 1e-12 );

  cross_section =
    ace_last_subshell_reaction->getCrossSection( 1.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.949916537107E+05, 1e-12 );

  cross_section =
    ace_last_subshell_reaction->getCrossSection( 6e1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.870602125397E+05, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the first_subshell reaction can be simulated
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectroatomicReaction, react_ace )
{
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 20.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  ace_first_subshell_reaction->react( electron, bank, shell_of_interaction );

  FRENSIE_CHECK( electron.getEnergy() < 20.0 );
  FRENSIE_CHECK( electron.getZDirection() < 1.0 );
  FRENSIE_CHECK( !bank.isEmpty() );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::K_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that the hydrogen differential cross section can be evaluated for the first subshell
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectroatomicReaction,
                   getDifferentialCrossSection_ace )
{

  double diff_cross_section =
    ace_first_subshell_reaction->getDifferentialCrossSection( 8.829E-02, 1e-8 );
  FRENSIE_CHECK_EQUAL( diff_cross_section, 0.0 );

  diff_cross_section =
    ace_first_subshell_reaction->getDifferentialCrossSection( 1.0, 9.7163E-02 );
  FRENSIE_CHECK_EQUAL( diff_cross_section, 0.0 );

  diff_cross_section =
    ace_first_subshell_reaction->getDifferentialCrossSection( 1.0, 8.145469e-1 );
  FRENSIE_CHECK_EQUAL( diff_cross_section, 0.0 );

  diff_cross_section =
    ace_first_subshell_reaction->getDifferentialCrossSection( 1e5, 1.75297e2 );
  FRENSIE_CHECK_EQUAL( diff_cross_section, 0.0 );

  diff_cross_section =
    ace_first_subshell_reaction->getDifferentialCrossSection( 1e5, 9.982461471e4 );
  FRENSIE_CHECK_EQUAL( diff_cross_section, 0.0 );

  diff_cross_section =
    ace_first_subshell_reaction->getDifferentialCrossSection( 1e5, 1e-7 );
  FRENSIE_CHECK_EQUAL( diff_cross_section, 0.0 );

  diff_cross_section =
    ace_first_subshell_reaction->getDifferentialCrossSection(
      1.0E+05,
      max_ionization_subshell_adjoint_energy );
  FRENSIE_CHECK_EQUAL( diff_cross_section, 0.0 );

  diff_cross_section =
    ace_first_subshell_reaction->getDifferentialCrossSection( 1e5, 1e-7 - 1e-10 );
  FRENSIE_CHECK_EQUAL( diff_cross_section, 0.0 );

  diff_cross_section =
    ace_first_subshell_reaction->getDifferentialCrossSection(
      1.0E+05,
      max_ionization_subshell_adjoint_energy+1.0e-10 );
  FRENSIE_CHECK_EQUAL( diff_cross_section, 0.0 );
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

  // Extract the energy grid and cross section
  std::shared_ptr<const std::vector<double> > energy_grid(
     new std::vector<double>( xss_data_extractor->extractElectronEnergyGrid() ) );

  Utility::ArrayView<const double> raw_subshell_cross_sections =
    xss_data_extractor->extractElectroionizationSubshellCrossSections();

   // Extract the subshell information
  Utility::ArrayView<const double> subshell_endf_designators =
    xss_data_extractor->extractSubshellENDFDesignators();

  // Extract the subshell binding energies
  Utility::ArrayView<const double> binding_energies =
    xss_data_extractor->extractSubshellBindingEnergies();

  // Extract the electroionization data block (EION)
  Utility::ArrayView<const double> eion_block(
    xss_data_extractor->extractEIONBlock() );

  // Extract the location of info about first knock-on table relative to the EION block
  unsigned eion_loc = xss_data_extractor->returnEIONLoc();

  // Extract the number of subshells (N_s)
  int num_shells = subshell_endf_designators.size();

  // Extract the number of knock-on tables by subshell (N_i)
  std::vector<double> num_tables(eion_block(0,num_shells));

  // Extract the location of info about knock-on tables by subshell
  std::vector<double> table_info(eion_block(num_shells,num_shells));

  // Extract the location of knock-on tables by subshell
  std::vector<double> table_loc(eion_block(2*num_shells,num_shells));

  //-------------------------------------------------------------------------//
  // Use the first subshell for test
  unsigned first_subshell = 0;

  // Assign raw cross sections for first subshell
  Utility::ArrayView<const double> raw_first_subshell_cross_section(
                                 raw_subshell_cross_sections(
                                            first_subshell*energy_grid->size(),
                                            energy_grid->size()) );

  // Eliminate any cross sections entries equal to zero
  Utility::ArrayView<const double>::iterator first_start =
    std::find_if( raw_first_subshell_cross_section.begin(),
                  raw_first_subshell_cross_section.end(),
                  notEqualZero );

  // Assign cross sections for first subshell
  std::shared_ptr<const std::vector<double> > first_subshell_cross_section(
     new std::vector<double>( first_start, raw_first_subshell_cross_section.end() ) );

  // Calculate threshold energy index
  size_t first_subshell_threshold_index =
    energy_grid->size() - first_subshell_cross_section->size();

  // Assign subshell type for the first subshell
  Data::SubshellType interaction_first_subshell;
  interaction_first_subshell = Data::convertENDFDesignatorToSubshellEnum(
                                   subshell_endf_designators[first_subshell] );

  // Subshell table info realtive to the EION Block
  unsigned first_subshell_info = table_info[first_subshell]- eion_loc - 1;

  // Subshell table loc realtive to the EION Block
  unsigned first_subshell_loc = table_loc[first_subshell]- eion_loc - 1;

  // Extract the energies for which knock-on sampling tables are given
  std::vector<double> first_energy_grid(
                                     eion_block( first_subshell_info,
                                                 num_tables[first_subshell] ) );

  // Extract the length of the knock-on sampling tables
  std::vector<double> first_table_length(eion_block(
                               first_subshell_info + num_tables[first_subshell],
                               num_tables[first_subshell] ) );

  // Extract the offset of the knock-on sampling tables
  std::vector<double> first_table_offset(eion_block(
                             first_subshell_info + 2*num_tables[first_subshell],
                             num_tables[first_subshell] ) );

  // Create the electroionization sampling table for the first subshell
  std::shared_ptr<const MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution>
    first_subshell_distribution;

   // Create the electroionization sampling table for the last_subshell
  MonteCarlo::ElectroionizationSubshellElectronScatteringDistributionACEFactory::createElectroionizationSubshellDistribution(
    first_subshell_info,
    first_subshell_loc,
    num_tables[first_subshell],
    binding_energies[first_subshell],
    xss_data_extractor->isEPRVersion14(),
    eion_block,
    first_subshell_distribution );


  // Set the max allowed adjoint energy
  max_ionization_subshell_adjoint_energy = 9.99999117099E+04;

  // Create the reaction
  ace_first_subshell_reaction.reset(
    new MonteCarlo::ElectroionizationSubshellElectroatomicReaction<Utility::LinLin>(
                      energy_grid,
                      first_subshell_cross_section,
                      first_subshell_threshold_index,
                      interaction_first_subshell,
                      first_subshell_distribution ) );

  //-------------------------------------------------------------------------//
  // Use the last subshell for test
  unsigned last_subshell = subshell_endf_designators.size() -1;

  // Assign raw cross sections for last subshell
  Utility::ArrayView<const double> raw_last_subshell_cross_section(
                           raw_subshell_cross_sections(
                               last_subshell*energy_grid->size(),
                               energy_grid->size()) );

  // Eliminate any cross sections entries equal to zero
  Utility::ArrayView<const double>::iterator last_start =
    std::find_if( raw_last_subshell_cross_section.begin(),
                  raw_last_subshell_cross_section.end(),
                  notEqualZero );

  // Assign cross sections for last subshell
  std::shared_ptr<const std::vector<double> > last_subshell_cross_section(
     new std::vector<double>( last_start, raw_last_subshell_cross_section.end() ) );

  // Calculate threshold energy index
  size_t last_subshell_threshold_index =
    energy_grid->size() - last_subshell_cross_section->size();

  // Assign subshell type for the last subshell
  Data::SubshellType interaction_last_subshell;
  interaction_last_subshell = Data::convertENDFDesignatorToSubshellEnum(
                                     subshell_endf_designators[last_subshell] );

  // Subshell table info realtive to the EION Block
  unsigned last_subshell_info = table_info[last_subshell]- eion_loc - 1;

  // Subshell table loc realtive to the EION Block
  unsigned last_subshell_loc = table_loc[last_subshell]- eion_loc - 1;

  // Extract the energies for which knock-on sampling tables are given
  std::vector<double> last_energy_grid(
                                      eion_block( last_subshell_info,
                                                  num_tables[last_subshell] ) );

  // Extract the length of the knock-on sampling tables
  std::vector<double> last_table_length(eion_block(
                               last_subshell_info + num_tables[last_subshell],
                               num_tables[last_subshell] ) );

  // Extract the offset of the knock-on sampling tables
  std::vector<double> last_table_offset(eion_block(
                             last_subshell_info + 2*num_tables[last_subshell],
                             num_tables[last_subshell] ) );

  // Create the subshell distribution from the function
  std::shared_ptr<const MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution>
    last_subshell_distribution;

   // Create the electroionization sampling table for the last_subshell
MonteCarlo::ElectroionizationSubshellElectronScatteringDistributionACEFactory::createElectroionizationSubshellDistribution(
    last_subshell_info,
    last_subshell_loc,
    num_tables[last_subshell],
    binding_energies[last_subshell],
    xss_data_extractor->isEPRVersion14(),
    eion_block,
    last_subshell_distribution );

  // Create the reaction
  ace_last_subshell_reaction.reset(
    new MonteCarlo::ElectroionizationSubshellElectroatomicReaction<Utility::LinLin>(
                      energy_grid,
                      last_subshell_cross_section,
                      last_subshell_threshold_index,
                      interaction_last_subshell,
                      last_subshell_distribution ) );


  // Clear setup data
  ace_file_handler.reset();
  xss_data_extractor.reset();

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstElectroionizationSubshellElectroatomicReactionACE.cpp
//---------------------------------------------------------------------------//
