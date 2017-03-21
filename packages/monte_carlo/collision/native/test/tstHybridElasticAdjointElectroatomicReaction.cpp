//---------------------------------------------------------------------------//
//!
//! \file   tstHybridElasticAdjointElectroatomicReaction.cpp
//! \author Luke Kersting
//! \brief  Hybrid Elastic adjoint electroatomic reaction unit tests
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
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "MonteCarlo_HybridElasticAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_TabularDistribution.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::HybridElasticAdjointElectroatomicReaction<Utility::LinLin> >
    hybrid_elastic_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
TEUCHOS_UNIT_TEST( HybridElasticAdjointElectroatomicReaction, getReactionType )
{
  TEST_EQUALITY_CONST( hybrid_elastic_reaction->getReactionType(),
		       MonteCarlo::HYBRID_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
TEUCHOS_UNIT_TEST( HybridElasticAdjointElectroatomicReaction, getThresholdEnergy )
{
  TEST_EQUALITY_CONST( hybrid_elastic_reaction->getThresholdEnergy(),
                       1.0e-5 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( HybridElasticAdjointElectroatomicReaction, getNumberOfEmittedElectrons )
{
  TEST_EQUALITY_CONST( hybrid_elastic_reaction->getNumberOfEmittedElectrons(1e-3),
                       0u );

  TEST_EQUALITY_CONST( hybrid_elastic_reaction->getNumberOfEmittedElectrons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( HybridElasticAdjointElectroatomicReaction, getNumberOfEmittedPhotons )
{
  TEST_EQUALITY_CONST( hybrid_elastic_reaction->getNumberOfEmittedPhotons(1e-3),
                       0u );

  TEST_EQUALITY_CONST( hybrid_elastic_reaction->getNumberOfEmittedPhotons(20.0),
                       0u );
}


//---------------------------------------------------------------------------//
// Check that the hybrid cross section can be returned
TEUCHOS_UNIT_TEST( HybridElasticAdjointElectroatomicReaction,
                   getCrossSection )
{

  double cross_section = hybrid_elastic_reaction->getCrossSection( 1e-5 );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.74896E+08*9.50000475000238E-01 + 1.22176061033364E+07,
                          1e-12 );

  cross_section = hybrid_elastic_reaction->getCrossSection( 1e-3 );

  TEST_FLOATING_EQUALITY( cross_section,
                          1.9754757077506483e+06,
                          1e-12 );

  cross_section = hybrid_elastic_reaction->getCrossSection( 20.0 );

  TEST_FLOATING_EQUALITY( cross_section,
                          3.04727623729037E+02*8.2702774720157165e-06 + 2.0520968300008926,
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the elastic reaction can be simulated
TEUCHOS_UNIT_TEST( HybridElasticAdjointElectroatomicReaction, react )
{
  MonteCarlo::AdjointElectronState electron( 0 );
  electron.setEnergy( 20.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  hybrid_elastic_reaction->react( electron, bank, shell_of_interaction );

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

std::string test_native_file_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_native_file",
                   &test_native_file_name,
                   "Test Native file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Create reaction
  {
    // Get native data container
    Data::AdjointElectronPhotonRelaxationDataContainer data_container =
        Data::AdjointElectronPhotonRelaxationDataContainer( test_native_file_name );

  // Extract the energy grid and cross section
    Teuchos::ArrayRCP<double> energy_grid;
    energy_grid.assign(
        data_container.getAdjointElectronEnergyGrid().begin(),
        data_container.getAdjointElectronEnergyGrid().end() );

    Teuchos::ArrayRCP<double> cutoff_cross_section;
    cutoff_cross_section.assign(
        data_container.getAdjointCutoffElasticCrossSection().begin(),
        data_container.getAdjointCutoffElasticCrossSection().end() );

    Teuchos::ArrayRCP<double> mp_cross_section;
    mp_cross_section.assign(
        data_container.getAdjointMomentPreservingCrossSection().begin(),
        data_container.getAdjointMomentPreservingCrossSection().end() );

  // Reduced cutoff elastic cross section ratio
  std::vector<double> reduced_cutoff_ratio =
    data_container.getReducedCutoffCrossSectionRatios();

    // Create the hash-based grid searcher
    Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
      new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>,false>(
                 energy_grid,
                 energy_grid[0],
                 energy_grid[energy_grid.size()-1],
                 100 ) );

    // Create the Hybrid Distribution
    std::shared_ptr<const MonteCarlo::HybridElasticElectronScatteringDistribution>
        hybrid_elastic_distribution;

    double cutoff_angle_cosine = data_container.getCutoffAngleCosine();
    double evaluation_tol = 1e-7;

    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory<Utility::LinLinLog>::createHybridElasticDistribution(
        hybrid_elastic_distribution,
        grid_searcher,
        energy_grid,
        cutoff_cross_section,
        mp_cross_section,
        data_container,
        cutoff_angle_cosine,
        evaluation_tol );

  // Calculate the hybrid cross section
  unsigned hybrid_threshold_energy_index =
    std::min( data_container.getAdjointMomentPreservingCrossSectionThresholdEnergyIndex(),
              data_container.getAdjointCutoffElasticCrossSectionThresholdEnergyIndex() );

  unsigned mp_threshold_diff =
    data_container.getAdjointMomentPreservingCrossSectionThresholdEnergyIndex() -
    hybrid_threshold_energy_index;
  unsigned cutoff_threshold_diff =
    data_container.getAdjointCutoffElasticCrossSectionThresholdEnergyIndex() - 
    hybrid_threshold_energy_index;

  Teuchos::Array<double> combined_cross_section(
                           energy_grid.size() - hybrid_threshold_energy_index );

  for (unsigned i = 0; i < combined_cross_section.size(); ++i )
  {
    double energy = energy_grid[i + hybrid_threshold_energy_index];

    if ( i < mp_threshold_diff )
    {
      combined_cross_section[i] = cutoff_cross_section[i]*reduced_cutoff_ratio[i];
    }
    else if ( i < cutoff_threshold_diff )
    {
      combined_cross_section[i] = mp_cross_section[i];
    }
    else
    {
      combined_cross_section[i] =
        cutoff_cross_section[i-cutoff_threshold_diff]*reduced_cutoff_ratio[i] +
        mp_cross_section[i-mp_threshold_diff];
    }
  }

  Teuchos::ArrayRCP<double> hybrid_cross_section;
  hybrid_cross_section.assign( combined_cross_section.begin(),
                               combined_cross_section.end() );

    // Create the reaction
    hybrid_elastic_reaction.reset(
      new MonteCarlo::HybridElasticAdjointElectroatomicReaction<Utility::LinLin>(
            energy_grid,
            hybrid_cross_section,
            hybrid_threshold_energy_index,
            cutoff_angle_cosine,
            hybrid_elastic_distribution ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstHybridElasticAdjointElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
