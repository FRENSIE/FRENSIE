//---------------------------------------------------------------------------//
//!
//! \file   tstBremsstrahlungElectroatomicReaction.cpp
//! \author Luke Kersting
//! \brief  Bremsstrahlung electroatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_BremsstrahlungElectroatomicReaction.hpp"
#include "MonteCarlo_BremsstrahlungElectronScatteringDistribution.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::BremsstrahlungElectroatomicReaction<Utility::LinLin> >
  ace_dipole_bremsstrahlung_reaction;

std::shared_ptr<MonteCarlo::BremsstrahlungElectroatomicReaction<Utility::LinLin> >
  ace_twobs_bremsstrahlung_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
FRENSIE_UNIT_TEST( BremsstrahlungElectroatomicReaction, getReactionType_ace )
{
  FRENSIE_CHECK_EQUAL( ace_twobs_bremsstrahlung_reaction->getReactionType(),
               MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( ace_dipole_bremsstrahlung_reaction->getReactionType(),
               MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
FRENSIE_UNIT_TEST( BremsstrahlungElectroatomicReaction, getThresholdEnergy_ace )
{
  FRENSIE_CHECK_EQUAL( ace_twobs_bremsstrahlung_reaction->getThresholdEnergy(),
                       1.000000000000E-05 );

  FRENSIE_CHECK_EQUAL( ace_dipole_bremsstrahlung_reaction->getThresholdEnergy(),
                       1.000000000000E-05 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( BremsstrahlungElectroatomicReaction, getNumberOfEmittedElectrons_ace )
{
  FRENSIE_CHECK_EQUAL( ace_twobs_bremsstrahlung_reaction->getNumberOfEmittedElectrons(1e-8),
                       0u );

  FRENSIE_CHECK_EQUAL( ace_twobs_bremsstrahlung_reaction->getNumberOfEmittedElectrons(20.0),
                       1u );


  FRENSIE_CHECK_EQUAL( ace_dipole_bremsstrahlung_reaction->getNumberOfEmittedElectrons(1e-8),
                       0u );

  FRENSIE_CHECK_EQUAL( ace_dipole_bremsstrahlung_reaction->getNumberOfEmittedElectrons(20.0),
                       1u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( BremsstrahlungElectroatomicReaction, getNumberOfEmittedPhotons_ace )
{
  FRENSIE_CHECK_EQUAL( ace_twobs_bremsstrahlung_reaction->getNumberOfEmittedPhotons(1e-8),
                       0u );

  FRENSIE_CHECK_EQUAL( ace_twobs_bremsstrahlung_reaction->getNumberOfEmittedPhotons(20.0),
                       1u );


  FRENSIE_CHECK_EQUAL( ace_dipole_bremsstrahlung_reaction->getNumberOfEmittedPhotons(1e-8),
                       0u );

  FRENSIE_CHECK_EQUAL( ace_dipole_bremsstrahlung_reaction->getNumberOfEmittedPhotons(20.0),
                       1u );
}

//---------------------------------------------------------------------------//
// Check that the number of positrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( BremsstrahlungElectroatomicReaction, getNumberOfEmittedPositrons_ace )
{
  FRENSIE_CHECK_EQUAL( ace_twobs_bremsstrahlung_reaction->getNumberOfEmittedPositrons(1e-8),
                       0u );

  FRENSIE_CHECK_EQUAL( ace_twobs_bremsstrahlung_reaction->getNumberOfEmittedPositrons(20.0),
                       0u );


  FRENSIE_CHECK_EQUAL( ace_dipole_bremsstrahlung_reaction->getNumberOfEmittedPositrons(1e-8),
                       0u );

  FRENSIE_CHECK_EQUAL( ace_dipole_bremsstrahlung_reaction->getNumberOfEmittedPositrons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
FRENSIE_UNIT_TEST( BremsstrahlungElectroatomicReaction, getCrossSection_ace )
{
  // 2BS
  double cross_section =
    ace_twobs_bremsstrahlung_reaction->getCrossSection( 9.000000000000E-05 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 7.249970966838E+03, 1e-12 );

  cross_section =
    ace_twobs_bremsstrahlung_reaction->getCrossSection( 4.000000000000E-04 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.914234996439E+03, 1e-12 );

  cross_section =
    ace_twobs_bremsstrahlung_reaction->getCrossSection( 2.000000000000E-03 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.258661418255E+03, 1e-12 );


  // Dipole
  cross_section =
    ace_dipole_bremsstrahlung_reaction->getCrossSection( 9.000000000000E-05 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 7.249970966838E+03, 1e-12 );

  cross_section =
    ace_dipole_bremsstrahlung_reaction->getCrossSection( 4.000000000000E-04 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.914234996439E+03, 1e-12 );

  cross_section =
    ace_dipole_bremsstrahlung_reaction->getCrossSection( 2.000000000000E-03 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.258661418255E+03, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the differential cross section can be returned
FRENSIE_UNIT_TEST( BremsstrahlungElectroatomicReaction, getDifferentialCrossSection_ace )
{
  // 2BS
  double diff_cross_section =
    ace_twobs_bremsstrahlung_reaction->getDifferentialCrossSection(
        1.0e-5,
        9.0e-6 );

  FRENSIE_CHECK_FLOATING_EQUALITY( diff_cross_section,
                                  8.859383971725880E+08,
                                  1e-12 );

  diff_cross_section =
    ace_twobs_bremsstrahlung_reaction->getDifferentialCrossSection(
        3.16228E-01,
        3.16115596E-01 );

  FRENSIE_CHECK_FLOATING_EQUALITY( diff_cross_section,
                                  9.504071722591320E+05,
                                  1e-12 );

  diff_cross_section =
    ace_twobs_bremsstrahlung_reaction->getDifferentialCrossSection(
        1.0e5,
        8.0E4 );

  FRENSIE_CHECK_FLOATING_EQUALITY( diff_cross_section,
                                  2.665370886148930E-03,
                                  1e-12 );


  // Dipole
  diff_cross_section =
    ace_dipole_bremsstrahlung_reaction->getDifferentialCrossSection(
        1.0e-5,
        9.0e-6 );

  FRENSIE_CHECK_FLOATING_EQUALITY( diff_cross_section,
                                  8.859383971725880E+08,
                                  1e-12 );

  diff_cross_section =
    ace_dipole_bremsstrahlung_reaction->getDifferentialCrossSection(
        3.16228E-01,
        3.16115596E-01 );

  FRENSIE_CHECK_FLOATING_EQUALITY( diff_cross_section,
                                  9.504071722591320E+05,
                                  1e-12 );

  diff_cross_section =
    ace_dipole_bremsstrahlung_reaction->getDifferentialCrossSection(
        1.0e5,
        8.0E4 );

  FRENSIE_CHECK_FLOATING_EQUALITY( diff_cross_section,
                                  2.665370886148930E-03,
                                  1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the detailed 2BS bremsstrahlung reaction can be simulated
FRENSIE_UNIT_TEST( BremsstrahlungElectroatomicReaction, react_detailed_2BS_ace )
{
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 20 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  ace_twobs_bremsstrahlung_reaction->react( electron, bank, shell_of_interaction );

  FRENSIE_CHECK( electron.getEnergy() < 20.0 );
  FRENSIE_CHECK_EQUAL( electron.getZDirection(), 1.0 );
  FRENSIE_CHECK( !bank.isEmpty() );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::UNKNOWN_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that the basic dipole bremsstrahlung reaction can be simulated
FRENSIE_UNIT_TEST( BremsstrahlungElectroatomicReaction, react_basic_ace )
{
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 20 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  ace_dipole_bremsstrahlung_reaction->react( electron, bank, shell_of_interaction );

  FRENSIE_CHECK( electron.getEnergy() < 20.0 );
  FRENSIE_CHECK_EQUAL( electron.getZDirection(), 1.0 );
  FRENSIE_CHECK( !bank.isEmpty() );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::UNKNOWN_SUBSHELL );
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
  std::unique_ptr<Data::ACEFileHandler> ace_file_handler(
                 new Data::ACEFileHandler( test_ace_file_name,
                                           "82000.12p",
                                           test_ace_file_start_line ) );
  
  std::unique_ptr<Data::XSSEPRDataExtractor> xss_data_extractor(
                            new Data::XSSEPRDataExtractor(
                      ace_file_handler->getTableNXSArray(),
                      ace_file_handler->getTableJXSArray(),
                      ace_file_handler->getTableXSSArray() ) );

  // Extract the energy grid and cross section
  std::shared_ptr<const std::vector<double> > energy_grid(
     new std::vector<double>( xss_data_extractor->extractElectronEnergyGrid() ) );

  Utility::ArrayView<const double> raw_bremsstrahlung_cross_section =
    xss_data_extractor->extractBremsstrahlungCrossSection();

  Utility::ArrayView<const double>::iterator start =
    std::find_if( raw_bremsstrahlung_cross_section.begin(),
                  raw_bremsstrahlung_cross_section.end(),
                  []( const double element ){ return element != 0.0; } );

  std::shared_ptr<const std::vector<double> > bremsstrahlung_cross_section(
    new std::vector<double>( start, raw_bremsstrahlung_cross_section.end() ) );

  size_t bremsstrahlung_threshold_index =
    energy_grid->size() - bremsstrahlung_cross_section->size();

  // Extract the elastic scattering information data block (BREMI)
  Utility::ArrayView<const double> bremi_block(
                      xss_data_extractor->extractBREMIBlock() );

  // Extract the number of tabulated distributions
  int N = bremi_block.size()/3;

  // Extract the electron energy grid for bremsstrahlung energy distributions
  std::vector<double> bremsstrahlung_energy_grid(bremi_block(0,N));

  // Extract the table lengths for bremsstrahlung energy distributions
  std::vector<double> table_length(bremi_block(N,N));

  // Extract the offsets for bremsstrahlung energy distributions
  std::vector<double> offset(bremi_block(2*N,N));

  // Extract the bremsstrahlung photon energy distributions block (BREME)
  Utility::ArrayView<const double> breme_block =
    xss_data_extractor->extractBREMEBlock();

  // Create the bremsstrahlung scattering distributions
  std::vector<double> primary_grid( N );
  std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
    secondary_dists( N );

  for( unsigned n = 0; n < N; ++n )
  {
    primary_grid[n] = bremsstrahlung_energy_grid[n];

    secondary_dists[n].reset(
      new Utility::HistogramDistribution(
         breme_block( offset[n], table_length[n] ),
         breme_block( offset[n] + 1 + table_length[n], table_length[n]-1 ),
         true ) );
  }

  // Create the scattering function
  std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution> scattering_function(
     new Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::Correlated<Utility::LinLinLin> >(
                                                          primary_grid,
                                                          secondary_dists ) );

  std::shared_ptr<const MonteCarlo::BremsstrahlungElectronScatteringDistribution>
        dipole_scattering_distribution, twobs_scattering_distribution;

  // Create the distributions
  dipole_scattering_distribution.reset(
   new MonteCarlo::BremsstrahlungElectronScatteringDistribution(
        scattering_function ) );

  twobs_scattering_distribution.reset(
   new MonteCarlo::BremsstrahlungElectronScatteringDistribution(
        xss_data_extractor->extractAtomicNumber(),
        scattering_function ) );


  // Create the reactions
  ace_dipole_bremsstrahlung_reaction.reset(
    new MonteCarlo::BremsstrahlungElectroatomicReaction<Utility::LinLin>(
                              energy_grid,
                              bremsstrahlung_cross_section,
                              bremsstrahlung_threshold_index,
                              dipole_scattering_distribution ) );

  ace_twobs_bremsstrahlung_reaction.reset(
        new MonteCarlo::BremsstrahlungElectroatomicReaction<Utility::LinLin>(
                              energy_grid,
                              bremsstrahlung_cross_section,
                              bremsstrahlung_threshold_index,
                              twobs_scattering_distribution ) );

  // Clear setup data
  ace_file_handler.reset();
  xss_data_extractor.reset();

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstBremsstrahlungElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
