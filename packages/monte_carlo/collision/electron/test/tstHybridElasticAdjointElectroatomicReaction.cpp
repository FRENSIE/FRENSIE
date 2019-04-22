//---------------------------------------------------------------------------//
//!
//! \file   tstHybridElasticAdjointElectroatomicReaction.cpp
//! \author Luke Kersting
//! \brief  Hybrid Elastic adjoint electroatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "MonteCarlo_HybridElasticAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::HybridElasticAdjointElectroatomicReaction<Utility::LogLog> >
    hybrid_elastic_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
FRENSIE_UNIT_TEST( HybridElasticAdjointElectroatomicReaction, getReactionType )
{
  FRENSIE_CHECK_EQUAL( hybrid_elastic_reaction->getReactionType(),
                       MonteCarlo::HYBRID_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
FRENSIE_UNIT_TEST( HybridElasticAdjointElectroatomicReaction, getThresholdEnergy )
{
  FRENSIE_CHECK_EQUAL( hybrid_elastic_reaction->getThresholdEnergy(),
                       1.0e-5 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( HybridElasticAdjointElectroatomicReaction, getNumberOfEmittedAdjointElectrons )
{
  FRENSIE_CHECK_EQUAL( hybrid_elastic_reaction->getNumberOfEmittedAdjointElectrons(1e-3),
                       1u );

  FRENSIE_CHECK_EQUAL( hybrid_elastic_reaction->getNumberOfEmittedAdjointElectrons(20.0),
                       1u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( HybridElasticAdjointElectroatomicReaction, getNumberOfEmittedAdjointPhotons )
{
  FRENSIE_CHECK_EQUAL( hybrid_elastic_reaction->getNumberOfEmittedAdjointPhotons(1e-3),
                       0u );

  FRENSIE_CHECK_EQUAL( hybrid_elastic_reaction->getNumberOfEmittedAdjointPhotons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of positrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( HybridElasticAdjointElectroatomicReaction, getNumberOfEmittedAdjointPositrons )
{
  FRENSIE_CHECK_EQUAL( hybrid_elastic_reaction->getNumberOfEmittedAdjointPositrons(1e-3),
                       0u );

  FRENSIE_CHECK_EQUAL( hybrid_elastic_reaction->getNumberOfEmittedAdjointPositrons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the hybrid cross section can be returned
FRENSIE_UNIT_TEST( HybridElasticAdjointElectroatomicReaction,
                   getCrossSection )
{
  // Cross section ratio for cutoff angle
  double ratio = 9.500004750002375431e-01;
  double cross_section = hybrid_elastic_reaction->getCrossSection( 1e-5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          2.74896E+08*ratio + 1.2217606103336416e+07,
                          1e-12 );

  cross_section = hybrid_elastic_reaction->getCrossSection( 1e-3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                                   1.951042366659260122e+06,
                                   1e-12 );

  cross_section = hybrid_elastic_reaction->getCrossSection( 20.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                                   2.053710715519123209,
                                   1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the elastic reaction can be simulated
FRENSIE_UNIT_TEST( HybridElasticAdjointElectroatomicReaction, react )
{
  MonteCarlo::AdjointElectronState electron( 0 );
  electron.setEnergy( 20.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  hybrid_elastic_reaction->react( electron, bank, shell_of_interaction );

  FRENSIE_CHECK_EQUAL( electron.getEnergy(), 20.0 );
  FRENSIE_CHECK( electron.getZDirection() < 2.0 );
  FRENSIE_CHECK( electron.getZDirection() > 0.0 );
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
  // Create reaction
  {
    // Get native data container
    Data::AdjointElectronPhotonRelaxationDataContainer data_container =
        Data::AdjointElectronPhotonRelaxationDataContainer( test_native_file_name );

    // Extract the energy grid and cross section
    std::shared_ptr<const std::vector<double> > energy_grid(
       new std::vector<double>( data_container.getAdjointElectronEnergyGrid() ) );

    std::shared_ptr<const std::vector<double> > cutoff_cross_section(
       new std::vector<double>( data_container.getAdjointCutoffElasticCrossSection() ) );

    double cutoff_angle_cosine = data_container.getCutoffAngleCosine();
    double evaluation_tol = 1e-15;

    // Moment preserving elastic cross section
    std::vector<double> moment_preserving_cross_sections;
    size_t mp_threshold_energy_index;
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::calculateMomentPreservingCrossSections<Utility::LogNudgedLogCosLog,Utility::Correlated>(
                                  moment_preserving_cross_sections,
                                  mp_threshold_energy_index,
                                  data_container,
                                  energy_grid,
                                  evaluation_tol );

    std::shared_ptr<const std::vector<double> > mp_cross_section(
                 new std::vector<double>( moment_preserving_cross_sections ) );

    // Create the cutoff elastic scattering distribution
    std::shared_ptr<const MonteCarlo::CutoffElasticElectronScatteringDistribution>
          cutoff_distribution;
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<Utility::LogNudgedLogCosLog,Utility::Correlated>(
              cutoff_distribution,
              data_container,
              cutoff_angle_cosine,
              evaluation_tol );

    // Create the hash-based grid searcher
    std::shared_ptr<Utility::HashBasedGridSearcher<double> > grid_searcher(
        new Utility::StandardHashBasedGridSearcher<std::vector<double>,false>(
                 energy_grid,
                 energy_grid->front(),
                 energy_grid->back(),
                 100 ) );

    // Create the Hybrid Distribution
    std::shared_ptr<const MonteCarlo::HybridElasticElectronScatteringDistribution>
        hybrid_elastic_distribution;

    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createHybridElasticDistribution<Utility::LogNudgedLogCosLog,Utility::Correlated>(
        hybrid_elastic_distribution,
        energy_grid,
        cutoff_cross_section,
        mp_cross_section,
        data_container,
        cutoff_angle_cosine,
        evaluation_tol );

    // Calculate the hybrid cross section
    size_t hybrid_threshold_energy_index =
    std::min( mp_threshold_energy_index,
              (size_t)data_container.getAdjointCutoffElasticCrossSectionThresholdEnergyIndex() );

    size_t mp_threshold_diff =
      mp_threshold_energy_index - hybrid_threshold_energy_index;

    size_t cutoff_threshold_diff =
      data_container.getAdjointCutoffElasticCrossSectionThresholdEnergyIndex() -
      hybrid_threshold_energy_index;

    std::vector<double> combined_cross_section(
                         energy_grid->size() - hybrid_threshold_energy_index );

    for (unsigned i = 0; i < combined_cross_section.size(); ++i )
    {
      double energy = (*energy_grid)[i + hybrid_threshold_energy_index];
      double reduced_cutoff_ratio =
                cutoff_distribution->evaluateCutoffCrossSectionRatio( energy );

      if ( i < mp_threshold_diff )
      {
        combined_cross_section[i] =
          (*cutoff_cross_section)[i]*reduced_cutoff_ratio;
      }
      else if ( i < cutoff_threshold_diff )
      {
        combined_cross_section[i] = (*mp_cross_section)[i];
      }
      else
      {
        combined_cross_section[i] =
          (*cutoff_cross_section)[i-cutoff_threshold_diff]*reduced_cutoff_ratio +
          (*mp_cross_section)[i-mp_threshold_diff];
      }
    }

    std::shared_ptr<const std::vector<double> > hybrid_cross_section(
                           new std::vector<double>( combined_cross_section ) );

    // Create the reaction
    hybrid_elastic_reaction.reset(
      new MonteCarlo::HybridElasticAdjointElectroatomicReaction<Utility::LogLog>(
            energy_grid,
            hybrid_cross_section,
            hybrid_threshold_energy_index,
            grid_searcher,
            cutoff_angle_cosine,
            hybrid_elastic_distribution ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstHybridElasticAdjointElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
