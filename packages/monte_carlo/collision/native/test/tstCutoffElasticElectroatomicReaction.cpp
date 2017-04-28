//---------------------------------------------------------------------------//
//!
//! \file   tstCutoffElasticElectroatomicReaction.cpp
//! \author Luke Kersting
//! \brief  CutoffElastic electroatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_CutoffElasticElectroatomicReaction.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::ElectroatomicReaction>
    ace_elastic_reaction, test_elastic_reaction;
std::shared_ptr<const MonteCarlo::CutoffElasticElectronScatteringDistribution>
    elastic_scattering_distribution;
std::shared_ptr<Utility::FullyTabularTwoDDistribution>
    full_elastic_scattering_function, partial_elastic_scattering_function;
Teuchos::ArrayRCP<double> energy_grid;
Teuchos::ArrayRCP<double> elastic_cross_section;
unsigned elastic_threshold_index;
double upper_cutoff_angle_cosine;
bool correlated_sampling_mode_on = true;

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
TEUCHOS_UNIT_TEST( CutoffElasticElectroatomicReaction, getReactionType_ace )
{
  TEST_EQUALITY_CONST( ace_elastic_reaction->getReactionType(),
                       MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
TEUCHOS_UNIT_TEST( CutoffElasticElectroatomicReaction, getThresholdEnergy_ace )
{
  TEST_EQUALITY_CONST( ace_elastic_reaction->getThresholdEnergy(),
                       1e-5 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( CutoffElasticElectroatomicReaction, getNumberOfEmittedElectrons_ace )
{
  TEST_EQUALITY_CONST( ace_elastic_reaction->getNumberOfEmittedElectrons(1e-3),
                       0u );

  TEST_EQUALITY_CONST( ace_elastic_reaction->getNumberOfEmittedElectrons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( CutoffElasticElectroatomicReaction, getNumberOfEmittedPhotons_ace )
{
  TEST_EQUALITY_CONST( ace_elastic_reaction->getNumberOfEmittedPhotons(1e-3),
                       0u );

  TEST_EQUALITY_CONST( ace_elastic_reaction->getNumberOfEmittedPhotons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
TEUCHOS_UNIT_TEST( CutoffElasticElectroatomicReaction, getCrossSection_ace )
{
  double cross_section = ace_elastic_reaction->getCrossSection( 1.0E-05 );
  TEST_FLOATING_EQUALITY( cross_section, 2.48924E+09, 1e-12 );

  cross_section = ace_elastic_reaction->getCrossSection( 1.0E-03 );
  TEST_FLOATING_EQUALITY( cross_section, 2.90281E+08, 1e-12 );

  cross_section = ace_elastic_reaction->getCrossSection( 1.0E+05 );
  TEST_FLOATING_EQUALITY( cross_section, 8.83051E-02, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the cutoff cross section can be returned
TEUCHOS_UNIT_TEST( CutoffElasticElectroatomicReaction,
                   getCrossSection_cutoff_ace )
{
  double cutoff_angle_cosine = 0.9;
  // Create the reaction
  elastic_scattering_distribution.reset(
          new MonteCarlo::CutoffElasticElectronScatteringDistribution(
                full_elastic_scattering_function,
                partial_elastic_scattering_function,
                cutoff_angle_cosine,
                correlated_sampling_mode_on ) );

  test_elastic_reaction.reset(
    new MonteCarlo::CutoffElasticElectroatomicReaction<Utility::LinLin>(
                energy_grid,
                elastic_cross_section,
                elastic_threshold_index,
                elastic_scattering_distribution ) );

  // cross section ratio for cutoff angle
  double ratio = 9.5E-01;

  double cross_section =
    test_elastic_reaction->getCrossSection( 1.0E-05 );

  TEST_FLOATING_EQUALITY( cross_section, 2.48924E+09*ratio, 1e-12 );

  ratio = 2.439675590438E-01;
  cross_section =
    test_elastic_reaction->getCrossSection( 1.0E-03 );

  TEST_FLOATING_EQUALITY( cross_section, 2.90281E+08*ratio, 1e-12 );

  ratio = 7.776633431294E-06;
  cross_section =
    test_elastic_reaction->getCrossSection( 1.0E+05 );

  TEST_FLOATING_EQUALITY( cross_section, 8.83051E-02*ratio, 1e-12 );
}


//---------------------------------------------------------------------------//
// Check that the elastic reaction can be simulated
TEUCHOS_UNIT_TEST( CutoffElasticElectroatomicReaction, react_ace )
{
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 20.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  ace_elastic_reaction->react( electron, bank, shell_of_interaction );

  TEST_EQUALITY_CONST( electron.getEnergy(), 20.0 );
  TEST_ASSERT( electron.getZDirection() < 2.0 );
  TEST_ASSERT( electron.getZDirection() > 0.0 );
  TEST_ASSERT( bank.isEmpty() );
  TEST_EQUALITY_CONST( shell_of_interaction, Data::UNKNOWN_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_ace_file_name, test_ace_table_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_ace_file",
                   &test_ace_file_name,
                   "Test ACE file name" );
  clp().setOption( "test_ace_table",
                   &test_ace_table_name,
                   "Test ACE table name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
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
  energy_grid.deepCopy( xss_data_extractor->extractElectronEnergyGrid() );

  Teuchos::ArrayView<const double> raw_elastic_cross_section =
    xss_data_extractor->extractElasticCrossSection();

  Teuchos::ArrayView<const double>::iterator start =
    std::find_if( raw_elastic_cross_section.begin(),
                  raw_elastic_cross_section.end(),
                  notEqualZero );

  elastic_cross_section.assign( start, raw_elastic_cross_section.end() );

  elastic_threshold_index =
    energy_grid.size() - elastic_cross_section.size();

  // Extract the elastic scattering information data block (ELASI)
  Teuchos::ArrayView<const double> elasi_block(
              xss_data_extractor->extractELASIBlock() );

  // Extract the number of tabulated distributions
  int size = elasi_block.size()/3;

  // Extract the energy grid for elastic scattering angular distributions
  Teuchos::Array<double> elastic_energy_grid(elasi_block(0,size));

  // Extract the table lengths for elastic scattering angular distributions
  Teuchos::Array<double> table_length(elasi_block(size,size));

  // Extract the offsets for elastic scattering angular distributions
  Teuchos::Array<double> offset(elasi_block(2*size,size));

  // Extract the elastic scattering angular distributions block (elas)
  Teuchos::ArrayView<const double> elas_block =
    xss_data_extractor->extractELASBlock();

  // Create the scattering function
  Utility::FullyTabularTwoDDistribution::DistributionType function_data( size );
  Utility::FullyTabularTwoDDistribution::DistributionType partial_function_data( size );

  for( unsigned n = 0; n < size; ++n )
  {
    function_data[n].first = elastic_energy_grid[n];
    partial_function_data[n].first = elastic_energy_grid[n];

    Teuchos::Array<double> angles = elas_block( offset[n], table_length[n] );
    Teuchos::Array<double> pdfs =
            elas_block( offset[n] + 1 + table_length[n], table_length[n]-1 );

    function_data[n].second.reset(
      new Utility::HistogramDistribution( angles, pdfs, true ) );

    unsigned index = 0;
    for( unsigned i = 0; i < angles.size(); ++i )
    {
      if( angles[i] <= 0.9 )
      {
        index = i;
      }
    }

    Teuchos::Array<double> partial_angles(index+1), partial_pdfs(index);
    partial_angles[0] = angles[0];
    for( unsigned i = 1; i <= index; ++i )
    {
      partial_angles[i] = angles[i];
      partial_pdfs[i-1] = pdfs[i-1];
    }

    if( angles[index] != 0.9 )
    {
      partial_angles.push_back(0.9);
      partial_pdfs.push_back(function_data[n].second->evaluate( 0.9 ) );

    }

    partial_function_data[n].second.reset(
      new Utility::HistogramDistribution( partial_angles, partial_pdfs, true ) );
  }

  // Get the atomic number
  const int atomic_number = xss_data_extractor->extractAtomicNumber();

  // Create the scattering function
  full_elastic_scattering_function.reset(
    new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LinLinLin>(
            function_data ) );

  partial_elastic_scattering_function.reset(
    new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LinLinLin>(
            partial_function_data ) );

  elastic_scattering_distribution.reset(
          new MonteCarlo::CutoffElasticElectronScatteringDistribution(
                full_elastic_scattering_function,
                correlated_sampling_mode_on ) );

  // Create the reaction
  ace_elastic_reaction.reset(
    new MonteCarlo::CutoffElasticElectroatomicReaction<Utility::LinLin>(
                energy_grid,
                elastic_cross_section,
                elastic_threshold_index,
                elastic_scattering_distribution ) );

  // Clear setup data
  ace_file_handler.reset();
  xss_data_extractor.reset();

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstCutoffElasticElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
