//---------------------------------------------------------------------------//
//!
//! \file   tstMomentPreservingElasticPositronatomicReaction.cpp
//! \author Luke Kersting
//! \brief  Moment preserving Elastic positron-atomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "MonteCarlo_MomentPreservingElasticPositronatomicReaction.hpp"
#include "MonteCarlo_MomentPreservingElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

typedef Utility::FullyTabularBasicBivariateDistribution BasicBivariateDist;

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::PositronatomicReaction>
  mp_elastic_reaction;
std::shared_ptr<const MonteCarlo::MomentPreservingElasticElectronScatteringDistribution>
  discrete_elastic_distribution;
double cutoff_angle_cosine = 0.9;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
FRENSIE_UNIT_TEST( MomentPreservingElasticPositronatomicReaction, getReactionType )
{
  FRENSIE_CHECK_EQUAL( mp_elastic_reaction->getReactionType(),
                       MonteCarlo::MOMENT_PRESERVING_ELASTIC_POSITRONATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
FRENSIE_UNIT_TEST( MomentPreservingElasticPositronatomicReaction, getThresholdEnergy )
{
  FRENSIE_CHECK_EQUAL( mp_elastic_reaction->getThresholdEnergy(),
                       1.000000000000E-05 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( MomentPreservingElasticPositronatomicReaction, getNumberOfEmittedElectrons )
{
  FRENSIE_CHECK_EQUAL( mp_elastic_reaction->getNumberOfEmittedElectrons(1e-3),
                       0u );

  FRENSIE_CHECK_EQUAL( mp_elastic_reaction->getNumberOfEmittedElectrons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( MomentPreservingElasticPositronatomicReaction, getNumberOfEmittedPhotons )
{
  FRENSIE_CHECK_EQUAL( mp_elastic_reaction->getNumberOfEmittedPhotons(1e-3),
                       0u );

  FRENSIE_CHECK_EQUAL( mp_elastic_reaction->getNumberOfEmittedPhotons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of positrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( MomentPreservingElasticPositronatomicReaction, getNumberOfEmittedPositrons )
{
  FRENSIE_CHECK_EQUAL( mp_elastic_reaction->getNumberOfEmittedPositrons(1e-3),
                       1u );

  FRENSIE_CHECK_EQUAL( mp_elastic_reaction->getNumberOfEmittedPositrons(20.0),
                       1u );
}

//---------------------------------------------------------------------------//
// Check that the moment preserving cross section can be returned
FRENSIE_UNIT_TEST( MomentPreservingElasticPositronatomicReaction,
                   getCrossSection )
{

  double cross_section = mp_elastic_reaction->getCrossSection( 1.0E-05 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.611494138359356821e+08, 1e-12 );

  cross_section = mp_elastic_reaction->getCrossSection( 1.0E-03 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 5.730253976136980951e+07, 1e-12 );

  cross_section = mp_elastic_reaction->getCrossSection( 1.0E+05 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.8080603251349155e-05, 1e-12 );
}


//---------------------------------------------------------------------------//
// Check that the elastic reaction can be simulated
FRENSIE_UNIT_TEST( MomentPreservingElasticPositronatomicReaction, react )
{
  MonteCarlo::PositronState positron( 0 );
  positron.setEnergy( 20.0 );
  positron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  mp_elastic_reaction->react( positron, bank, shell_of_interaction );

  FRENSIE_CHECK_EQUAL( positron.getEnergy(), 20.0 );
  FRENSIE_CHECK( positron.getZDirection() < 1.0 );
  FRENSIE_CHECK( positron.getZDirection() > 0.0 );
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
    Data::ElectronPhotonRelaxationDataContainer data_container =
        Data::ElectronPhotonRelaxationDataContainer( test_native_file_name );

    // Get the energy grid
    std::vector<double> angular_energy_grid =
        data_container.getElasticAngularEnergyGrid();

    // Get size of paramters
    int size = angular_energy_grid.size();

    // Create the scattering function
    std::vector<double> primary_grid( size );
    std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
      secondary_dists( size );

    for( unsigned n = 0; n < angular_energy_grid.size(); ++n )
    {
      primary_grid[n] = angular_energy_grid[n];

    // Get the moment preserving elastic scattering angle cosines at the energy
    std::vector<double> discrete_angles(
        data_container.getMomentPreservingElasticDiscreteAngles(
            angular_energy_grid[n] ) );

    // Get the cutoff elastic scattering pdf at the energy
    std::vector<double> weights(
        data_container.getMomentPreservingElasticWeights(
            angular_energy_grid[n] ) );

    secondary_dists[n].reset(
      new const Utility::DiscreteDistribution(
        discrete_angles,
        weights,
        false,
        true ) );
    }

    std::shared_ptr<BasicBivariateDist> scattering_function(
       new Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::Correlated<Utility::LinLinLog> >(
                                                           primary_grid,
                                                           secondary_dists ) );

    discrete_elastic_distribution.reset(
        new MonteCarlo::MomentPreservingElasticElectronScatteringDistribution(
                scattering_function,
                cutoff_angle_cosine ) );

    std::shared_ptr<const std::vector<double> > energy_grid(
           new std::vector<double>( data_container.getElectronEnergyGrid() ) );

    // Moment preserving elastic cross section
    std::vector<double> moment_preserving_cross_sections;
    size_t threshold_index;
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::calculateMomentPreservingCrossSections<Utility::LogLogCosLog,Utility::Correlated>(
                               moment_preserving_cross_sections,
                               threshold_index,
                               data_container,
                               energy_grid,
                               1e-15 );

    std::shared_ptr<const std::vector<double> > cross_section(
                 new std::vector<double>( moment_preserving_cross_sections ) );

    // Create the reaction
    mp_elastic_reaction.reset(
      new MonteCarlo::MomentPreservingElasticPositronatomicReaction<Utility::LinLin>(
                energy_grid,
                cross_section,
                threshold_index,
                discrete_elastic_distribution ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstMomentPreservingElasticPositronatomicReaction.cpp
//---------------------------------------------------------------------------//
