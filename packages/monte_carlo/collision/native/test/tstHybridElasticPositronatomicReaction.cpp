//---------------------------------------------------------------------------//
//!
//! \file   tstHybridElasticPositronatomicReaction.cpp
//! \author Luke Kersting
//! \brief  Hybrid Elastic positron-atomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_ArrayRCP.hpp>

// FRENSIE Includes
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "MonteCarlo_HybridElasticPositronatomicReaction.hpp"
#include "MonteCarlo_HybridElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_TabularDistribution.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

  typedef MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::TwoDFunction
            TwoDFunction;

  typedef MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::TwoDDist
            TwoDDist;

  Teuchos::RCP<MonteCarlo::HybridElasticPositronatomicReaction<Utility::LogLog> >
    hybrid_elastic_reaction;

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
TEUCHOS_UNIT_TEST( HybridElasticPositronatomicReaction, getReactionType )
{
  TEST_EQUALITY_CONST( hybrid_elastic_reaction->getReactionType(),
                       MonteCarlo::HYBRID_ELASTIC_POSITRONATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
TEUCHOS_UNIT_TEST( HybridElasticPositronatomicReaction, getThresholdEnergy )
{
  TEST_EQUALITY_CONST( hybrid_elastic_reaction->getThresholdEnergy(),
                       1.0e-5 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( HybridElasticPositronatomicReaction, getNumberOfEmittedElectrons )
{
  TEST_EQUALITY_CONST( hybrid_elastic_reaction->getNumberOfEmittedElectrons(1e-3),
                       0u );

  TEST_EQUALITY_CONST( hybrid_elastic_reaction->getNumberOfEmittedElectrons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( HybridElasticPositronatomicReaction, getNumberOfEmittedPhotons )
{
  TEST_EQUALITY_CONST( hybrid_elastic_reaction->getNumberOfEmittedPhotons(1e-3),
                       0u );

  TEST_EQUALITY_CONST( hybrid_elastic_reaction->getNumberOfEmittedPhotons(20.0),
                       0u );
}


//---------------------------------------------------------------------------//
// Check that the hybrid cross section can be returned
TEUCHOS_UNIT_TEST( HybridElasticPositronatomicReaction,
                   getCrossSection )
{

  double ratio = 9.500004750002375431e-01;
  double cross_section = hybrid_elastic_reaction->getCrossSection( 1.0E-05 );
  TEST_FLOATING_EQUALITY( cross_section, 3.62586e+09*ratio + 1.611494138359356821e+08, 1e-12 );

  cross_section = hybrid_elastic_reaction->getCrossSection( 1.0E-03 );
  TEST_FLOATING_EQUALITY( cross_section, 7.5860420097891897e+07, 1e-12 );

  ratio = 8.6868172466733646e-06;
  cross_section = hybrid_elastic_reaction->getCrossSection( 1.0E+05 );
  TEST_FLOATING_EQUALITY( cross_section, 2.2177e-03*ratio + 6.8080603251349155e-05, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the elastic reaction can be simulated
TEUCHOS_UNIT_TEST( HybridElasticPositronatomicReaction, react )
{
  MonteCarlo::PositronState positron( 0 );
  positron.setEnergy( 20.0 );
  positron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  hybrid_elastic_reaction->react( positron, bank, shell_of_interaction );

  TEST_EQUALITY_CONST( positron.getEnergy(), 20.0 );
  TEST_ASSERT( positron.getZDirection() < 2.0 );
  TEST_ASSERT( positron.getZDirection() > 0.0 );
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
  double evaluation_tol = 1e-15;

  // Get native data container
  Data::ElectronPhotonRelaxationDataContainer data_container =
        Data::ElectronPhotonRelaxationDataContainer( test_native_file_name );

  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.assign(
        data_container.getElectronEnergyGrid().begin(),
        data_container.getElectronEnergyGrid().end() );

  // Construct the grid searcher
  Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
    new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>,false>(
                    energy_grid,
                    energy_grid[0],
                    energy_grid[energy_grid.size()-1],
                    energy_grid.size()/10+1 ) );

  Teuchos::ArrayRCP<double> cutoff_cross_section;
  cutoff_cross_section.assign(
        data_container.getCutoffElasticCrossSection().begin(),
        data_container.getCutoffElasticCrossSection().end() );

  // Moment preserving elastic cross section
  std::vector<double> moment_preserving_cross_sections;
  unsigned mp_threshold_energy_index;
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::calculateMomentPreservingCrossSections<Utility::Correlated<Utility::LogLogCosLog> >(
                               moment_preserving_cross_sections,
                               mp_threshold_energy_index,
                               data_container,
                               energy_grid,
                               evaluation_tol );

  Teuchos::ArrayRCP<double> mp_cross_section;
  mp_cross_section.assign(
    moment_preserving_cross_sections.begin(),
    moment_preserving_cross_sections.end() );

  // Calculate the hybrid cross section
  unsigned hybrid_threshold_energy_index =
    std::min( mp_threshold_energy_index,
              data_container.getCutoffElasticCrossSectionThresholdEnergyIndex() );

  unsigned mp_threshold_diff =
    mp_threshold_energy_index - hybrid_threshold_energy_index;
  unsigned cutoff_threshold_diff =
    data_container.getCutoffElasticCrossSectionThresholdEnergyIndex() -
    hybrid_threshold_energy_index;

  Teuchos::Array<double> combined_cross_section(
                           energy_grid.size() - hybrid_threshold_energy_index );

  std::shared_ptr<const MonteCarlo::CutoffElasticElectronScatteringDistribution>
        cutoff_elastic_distribution;

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<Utility::Correlated<Utility::LogLogCosLog> >(
        cutoff_elastic_distribution,
        data_container,
        data_container.getCutoffAngleCosine(),
        evaluation_tol );


  for (unsigned i = 0; i < combined_cross_section.size(); ++i )
  {
    double energy = energy_grid[i + hybrid_threshold_energy_index];
    double reduced_cutoff_ratio =
        cutoff_elastic_distribution->evaluateCutoffCrossSectionRatio( energy );
    if ( i < mp_threshold_diff )
    {
      combined_cross_section[i] = cutoff_cross_section[i]*reduced_cutoff_ratio;
    }
    else if ( i < cutoff_threshold_diff )
    {
      combined_cross_section[i] = mp_cross_section[i];
    }
    else
    {
      combined_cross_section[i] =
        cutoff_cross_section[i-cutoff_threshold_diff]*reduced_cutoff_ratio +
        mp_cross_section[i-mp_threshold_diff];
    }
  }

  Teuchos::ArrayRCP<double> hybrid_cross_section;
  hybrid_cross_section.assign( combined_cross_section.begin(),
                               combined_cross_section.end() );

  // Create hybrid distribution
  std::shared_ptr<const MonteCarlo::HybridElasticElectronScatteringDistribution>
        hybrid_elastic_distribution;

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createHybridElasticDistribution<Utility::Correlated<Utility::LogLogCosLog> >(
        hybrid_elastic_distribution,
        energy_grid,
        cutoff_cross_section,
        mp_cross_section,
        data_container,
        data_container.getCutoffAngleCosine(),
        evaluation_tol );

  // Create the reaction
  hybrid_elastic_reaction.reset(
    new MonteCarlo::HybridElasticPositronatomicReaction<Utility::LogLog>(
            energy_grid,
            hybrid_cross_section,
            hybrid_threshold_energy_index,
            grid_searcher,
            data_container.getCutoffAngleCosine(),
            hybrid_elastic_distribution ) );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstHybridElasticPositronatomicReaction.cpp
//---------------------------------------------------------------------------//
