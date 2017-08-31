//---------------------------------------------------------------------------//
//!
//! \file   tstMomentPreservingElasticElectroatomicReaction.cpp
//! \author Luke Kersting
//! \brief  Moment preserving Elastic electroatomic reaction unit tests
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
#include "MonteCarlo_MomentPreservingElasticElectroatomicReaction.hpp"
#include "MonteCarlo_MomentPreservingElasticElectronScatteringDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_DiscreteDistribution.hpp"

typedef Utility::FullyTabularTwoDDistribution TwoDDist;


//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::ElectroatomicReaction>
    mp_elastic_reaction;
std::shared_ptr<const MonteCarlo::MomentPreservingElasticElectronScatteringDistribution>
    discrete_elastic_distribution;
double cutoff_angle_cosine = 0.9;

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
TEUCHOS_UNIT_TEST( MomentPreservingElasticElectroatomicReaction, getReactionType )
{
  TEST_EQUALITY_CONST( mp_elastic_reaction->getReactionType(),
                       MonteCarlo::MOMENT_PRESERVING_ELASTIC_ELECTROATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
TEUCHOS_UNIT_TEST( MomentPreservingElasticElectroatomicReaction, getThresholdEnergy )
{
  TEST_EQUALITY_CONST( mp_elastic_reaction->getThresholdEnergy(),
                       1.000000000000E-05 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( MomentPreservingElasticElectroatomicReaction, getNumberOfEmittedElectrons )
{
  TEST_EQUALITY_CONST( mp_elastic_reaction->getNumberOfEmittedElectrons(1e-3),
                       0u );

  TEST_EQUALITY_CONST( mp_elastic_reaction->getNumberOfEmittedElectrons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( MomentPreservingElasticElectroatomicReaction, getNumberOfEmittedPhotons )
{
  TEST_EQUALITY_CONST( mp_elastic_reaction->getNumberOfEmittedPhotons(1e-3),
                       0u );

  TEST_EQUALITY_CONST( mp_elastic_reaction->getNumberOfEmittedPhotons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the moment preserving cross section can be returned
TEUCHOS_UNIT_TEST( MomentPreservingElasticElectroatomicReaction,
                   getCrossSection )
{

  double cross_section = mp_elastic_reaction->getCrossSection( 1.0E-05 );
  TEST_FLOATING_EQUALITY( cross_section, 1.611494138359356821e+08, 1e-12 );

  cross_section = mp_elastic_reaction->getCrossSection( 1.0E-03 );
  TEST_FLOATING_EQUALITY( cross_section, 5.730253976136980951e+07, 1e-12 );

  cross_section = mp_elastic_reaction->getCrossSection( 1.0E+05 );
  TEST_FLOATING_EQUALITY( cross_section, 6.8080603251349155e-05, 1e-12 );
}


//---------------------------------------------------------------------------//
// Check that the elastic reaction can be simulated
TEUCHOS_UNIT_TEST( MomentPreservingElasticElectroatomicReaction, react )
{
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 20.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  mp_elastic_reaction->react( electron, bank, shell_of_interaction );

  TEST_EQUALITY_CONST( electron.getEnergy(), 20.0 );
  TEST_ASSERT( electron.getZDirection() < 1.0 );
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
    Data::ElectronPhotonRelaxationDataContainer data_container =
        Data::ElectronPhotonRelaxationDataContainer( test_native_file_name );

    // Get the energy grid
    std::vector<double> angular_energy_grid =
        data_container.getElasticAngularEnergyGrid();

    // Get size of paramters
    int size = angular_energy_grid.size();

    // Create the scattering function
    TwoDDist::DistributionType function_data(size);

    for( unsigned n = 0; n < angular_energy_grid.size(); ++n )
    {
    function_data[n].first = angular_energy_grid[n];

    // Get the moment preserving elastic scattering angle cosines at the energy
    std::vector<double> discrete_angles(
        data_container.getMomentPreservingElasticDiscreteAngles(
            angular_energy_grid[n] ) );

    // Get the cutoff elastic scatering pdf at the energy
    std::vector<double> weights(
        data_container.getMomentPreservingElasticWeights(
            angular_energy_grid[n] ) );

    function_data[n].second.reset(
      new const Utility::DiscreteDistribution(
        discrete_angles,
        weights,
        false,
        true ) );
    }

    std::shared_ptr<TwoDDist> scattering_function(
      new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LinLinLog>(
        function_data ) );

    bool correlated_sampling_mode_on = true;

    discrete_elastic_distribution.reset(
        new MonteCarlo::MomentPreservingElasticElectronScatteringDistribution(
                scattering_function,
                cutoff_angle_cosine,
                correlated_sampling_mode_on ) );

    Teuchos::ArrayRCP<double> energy_grid;
    energy_grid.assign(
        data_container.getElectronEnergyGrid().begin(),
        data_container.getElectronEnergyGrid().end() );

    Teuchos::ArrayRCP<double> cross_section;
    cross_section.assign(
        data_container.getMomentPreservingCrossSection().begin(),
        data_container.getMomentPreservingCrossSection().end() );

    unsigned threshold_index(
        data_container.getMomentPreservingCrossSectionThresholdEnergyIndex() );

    // Create the reaction
    mp_elastic_reaction.reset(
      new MonteCarlo::MomentPreservingElasticElectroatomicReaction<Utility::LinLin>(
                energy_grid,
                cross_section,
                threshold_index,
                discrete_elastic_distribution ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstCutoffElasticElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
