//---------------------------------------------------------------------------//
//!
//! \file   tstStandardParticleSourceComponentDagMCRejection.cpp
//! \author Alex Robinson
//! \brief  The standard particle source component unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_StandardParticleSourceComponent.hpp"
#include "MonteCarlo_StandardParticleDistribution.hpp"
#include "MonteCarlo_IndependentPhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_DependentPhaseSpaceDimensionDistribution.hpp"
#include "Geometry_RootModel.hpp"
#include "Utility_BasicCartesianCoordinateConversionPolicy.hpp"
#include "Utility_BasicSphericalCoordinateConversionPolicy.hpp"
#include "Utility_BasicCylindricalSpatialCoordinateConversionPolicy.hpp"
#include "Utility_HistogramFullyTabularBasicBivariateDistribution.hpp"
#include "Utility_HistogramPartiallyTabularBasicBivariateDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_PowerDistribution.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_ExponentialDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

using namespace MonteCarlo;

typedef std::tuple<MonteCarlo::NeutronState,
                   MonteCarlo::PhotonState,
                   MonteCarlo::ElectronState,
                   MonteCarlo::PositronState
                  > TestParticleStateTypes;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<const Geometry::Model> model;
std::shared_ptr<const MonteCarlo::ParticleDistribution> particle_distribution;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a particle state an be sampled
FRENSIE_UNIT_TEST_TEMPLATE( StandardParticleSource,
                            sampleParticleState,
                            TestParticleStateTypes )
{
  FETCH_TEMPLATE_PARAM( 0, ParticleStateType );

  constexpr const MonteCarlo::ParticleType particle_type =
    ParticleStateType::type;

  // Construct a source component
  std::unique_ptr<MonteCarlo::ParticleSourceComponent>
    source_component( new MonteCarlo::StandardParticleSourceComponent<ParticleStateType>( 2, 1.0, model, particle_distribution ) );

  MonteCarlo::ParticleBank bank;

  // Set the random number generator stream
  std::vector<double> fake_stream( 7 );
  fake_stream[0] = 1.0-1e-12; // r
  fake_stream[1] = 0.0; // theta
  fake_stream[2] = 0.0; // mu
  fake_stream[3] = 0.5; // energy
  fake_stream[4] = 0.0; // theta
  fake_stream[5] = 0.0; // mu
  fake_stream[6] = 0.0; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  source_component->sampleParticleState( bank, 0ull );

  FRENSIE_CHECK_EQUAL( bank.size(), 1 );
  FRENSIE_CHECK_EQUAL( bank.top().getHistoryNumber(), 0ull );
  FRENSIE_CHECK_EQUAL( bank.top().getParticleType(), particle_type );
  FRENSIE_CHECK( bank.top().isEmbeddedInModel( *model ) );
  FRENSIE_CHECK_SMALL( bank.top().getXPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( bank.top().getYPosition(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getZPosition(), -2.0, 1e-12 );
  FRENSIE_CHECK_SMALL( bank.top().getXDirection(), 1e-12 );
  FRENSIE_CHECK_SMALL( bank.top().getYDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getZDirection(), -1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceEnergy(), 5.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(), 5.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceId(), 2 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceCell(), 3 );
  FRENSIE_CHECK_EQUAL( bank.top().getCell(), 3 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getWeight(), 1.0 );

  bank.pop();

  fake_stream[0] = 0.0; // r
  fake_stream[1] = 0.0; // theta
  fake_stream[2] = 0.0; // mu
  fake_stream[3] = 0.5; // energy
  fake_stream[4] = 0.0; // theta
  fake_stream[5] = 0.0; // mu
  fake_stream[6] = 0.0; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  source_component->sampleParticleState( bank, 0ull );

  FRENSIE_CHECK_EQUAL( bank.size(), 1 );
  FRENSIE_CHECK_EQUAL( bank.top().getHistoryNumber(), 0ull );
  FRENSIE_CHECK_EQUAL( bank.top().getParticleType(), particle_type );
  FRENSIE_CHECK( bank.top().isEmbeddedInModel( *model ) );
  FRENSIE_CHECK_SMALL( bank.top().getXPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( bank.top().getYPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( bank.top().getZPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( bank.top().getXDirection(), 1e-12 );
  FRENSIE_CHECK_SMALL( bank.top().getYDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getZDirection(), -1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceEnergy(), 5.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(), 5.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceId(), 2 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceCell(), 2 );
  FRENSIE_CHECK_EQUAL( bank.top().getCell(), 2 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getWeight(), 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  MonteCarlo::ParticleSourceComponent::CellIdSet start_cell_cache;
  source_component->getStartingCells( start_cell_cache );

  FRENSIE_CHECK_EQUAL( start_cell_cache.size(), 2 );
  FRENSIE_CHECK( start_cell_cache.count( 2 ) );
  FRENSIE_CHECK( start_cell_cache.count( 3 ) );
}

//---------------------------------------------------------------------------//
// Check that a particle state can be sampled from a source with rejection
// cells
FRENSIE_UNIT_TEST_TEMPLATE( StandardParticleSource,
                            sampleParticleState_rejection_cells_larger,
                            TestParticleStateTypes )
{
  FETCH_TEMPLATE_PARAM( 0, ParticleStateType );

  constexpr const MonteCarlo::ParticleType particle_type =
    ParticleStateType::type;

  // Construct a source component
  std::unique_ptr<MonteCarlo::ParticleSourceComponent>
    source_component( new MonteCarlo::StandardParticleSourceComponent<ParticleStateType>( 2, 1.0, MonteCarlo::ParticleSourceComponent::CellIdSet( {2, 3} ), model, particle_distribution ) );

  MonteCarlo::ParticleBank bank;

  // Set the random number generator stream
  std::vector<double> fake_stream( 7 );
  fake_stream[0] = 1.0-1e-12; // r
  fake_stream[1] = 0.0; // theta
  fake_stream[2] = 0.0; // mu
  fake_stream[3] = 0.5; // energy
  fake_stream[4] = 0.0; // theta
  fake_stream[5] = 0.0; // mu
  fake_stream[6] = 0.0; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  source_component->sampleParticleState( bank, 0ull );

  FRENSIE_CHECK_EQUAL( bank.size(), 1 );
  FRENSIE_CHECK_EQUAL( bank.top().getHistoryNumber(), 0ull );
  FRENSIE_CHECK_EQUAL( bank.top().getParticleType(), particle_type );
  FRENSIE_CHECK( bank.top().isEmbeddedInModel( *model ) );
  FRENSIE_CHECK_SMALL( bank.top().getXPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( bank.top().getYPosition(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getZPosition(), -2.0, 1e-12 );
  FRENSIE_CHECK_SMALL( bank.top().getXDirection(), 1e-12 );
  FRENSIE_CHECK_SMALL( bank.top().getYDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getZDirection(), -1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceEnergy(), 5.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(), 5.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceId(), 2 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceCell(), 3 );
  FRENSIE_CHECK_EQUAL( bank.top().getCell(), 3 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getWeight(), 1.0 );

  bank.pop();

  fake_stream[0] = 0.0; // r
  fake_stream[1] = 0.0; // theta
  fake_stream[2] = 0.0; // mu
  fake_stream[3] = 0.5; // energy
  fake_stream[4] = 0.0; // theta
  fake_stream[5] = 0.0; // mu
  fake_stream[6] = 0.0; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  source_component->sampleParticleState( bank, 0ull );

  FRENSIE_CHECK_EQUAL( bank.size(), 1 );
  FRENSIE_CHECK_EQUAL( bank.top().getHistoryNumber(), 0ull );
  FRENSIE_CHECK_EQUAL( bank.top().getParticleType(), particle_type );
  FRENSIE_CHECK( bank.top().isEmbeddedInModel( *model ) );
  FRENSIE_CHECK_SMALL( bank.top().getXPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( bank.top().getYPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( bank.top().getZPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( bank.top().getXDirection(), 1e-12 );
  FRENSIE_CHECK_SMALL( bank.top().getYDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getZDirection(), -1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceEnergy(), 5.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(), 5.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceId(), 2 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceCell(), 2 );
  FRENSIE_CHECK_EQUAL( bank.top().getCell(), 2 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getWeight(), 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_EQUAL( source_component->getNumberOfTrials(), 2 );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfSamples(), 2 );
  FRENSIE_CHECK_EQUAL( source_component->getSamplingEfficiency(), 1.0 );

  MonteCarlo::ParticleSourceComponent::CellIdSet start_cell_cache;
  source_component->getStartingCells( start_cell_cache );

  FRENSIE_CHECK_EQUAL( start_cell_cache.size(), 2 );
  FRENSIE_CHECK( start_cell_cache.count( 2 ) );
  FRENSIE_CHECK( start_cell_cache.count( 3 ) );
}

//---------------------------------------------------------------------------//
// Check that a particle state can be sampled from a source with rejection
// cells
FRENSIE_UNIT_TEST_TEMPLATE( StandardParticleSource,
                            sampleParticleState_rejection_cells_smaller,
                            TestParticleStateTypes )
{
  FETCH_TEMPLATE_PARAM( 0, ParticleStateType );

  constexpr const MonteCarlo::ParticleType particle_type =
    ParticleStateType::type;

  // Construct a source component
  std::unique_ptr<MonteCarlo::ParticleSourceComponent>
    source_component( new MonteCarlo::StandardParticleSourceComponent<ParticleStateType>( 2, 1.0, MonteCarlo::ParticleSourceComponent::CellIdSet( {2} ), model, particle_distribution ) );

  MonteCarlo::ParticleBank bank;

  // Set the random number generator stream
  std::vector<double> fake_stream( 14 );
  fake_stream[0] = 1.0-1e-12; // r
  fake_stream[1] = 0.0; // theta
  fake_stream[2] = 0.0; // mu
  fake_stream[3] = 0.5; // energy
  fake_stream[4] = 0.0; // theta
  fake_stream[5] = 0.0; // mu
  fake_stream[6] = 0.0; // time

  fake_stream[7] = 0.0; // r
  fake_stream[8] = 0.0; // theta
  fake_stream[9] = 0.0; // mu
  fake_stream[10] = 0.5; // energy
  fake_stream[11] = 0.0; // theta
  fake_stream[12] = 0.0; // mu
  fake_stream[13] = 0.0; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  source_component->sampleParticleState( bank, 0ull );

  FRENSIE_CHECK_EQUAL( bank.size(), 1 );
  FRENSIE_CHECK_EQUAL( bank.top().getHistoryNumber(), 0ull );
  FRENSIE_CHECK_EQUAL( bank.top().getParticleType(), particle_type );
  FRENSIE_CHECK( bank.top().isEmbeddedInModel( *model ) );
  FRENSIE_CHECK_SMALL( bank.top().getXPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( bank.top().getYPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( bank.top().getZPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( bank.top().getXDirection(), 1e-12 );
  FRENSIE_CHECK_SMALL( bank.top().getYDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getZDirection(), -1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceEnergy(), 5.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(), 5.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceId(), 2 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceCell(), 2 );
  FRENSIE_CHECK_EQUAL( bank.top().getCell(), 2 );
  FRENSIE_CHECK_EQUAL( bank.top().getSourceWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getWeight(), 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_EQUAL( source_component->getNumberOfTrials(), 2 );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfSamples(), 1 );
  FRENSIE_CHECK_EQUAL( source_component->getSamplingEfficiency(), 0.5 );

  MonteCarlo::ParticleSourceComponent::CellIdSet start_cell_cache;
  source_component->getStartingCells( start_cell_cache );

  FRENSIE_CHECK_EQUAL( start_cell_cache.size(), 1 );
  FRENSIE_CHECK( start_cell_cache.count( 2 ) );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_root_geom_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_root_file",
                                        test_root_geom_file_name, "",
                                        "Test ROOT file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Initialize the geometry model
  Geometry::RootModelProperties local_properties( test_root_geom_file_name );

  std::shared_ptr<Geometry::RootModel> tmp_model =
    Geometry::RootModel::getInstance();

  tmp_model->initialize( local_properties );

  model = tmp_model;

  // Create the particle distribution
  std::shared_ptr<MonteCarlo::StandardParticleDistribution>
    tmp_particle_distribution;

  {
    std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
    spatial_coord_conversion_policy( new Utility::BasicSphericalCoordinateConversionPolicy );

  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
    directional_coord_conversion_policy( new Utility::BasicSphericalCoordinateConversionPolicy );

    tmp_particle_distribution.reset(
                                  new MonteCarlo::StandardParticleDistribution(
                                       "source distribution",
                                       spatial_coord_conversion_policy,
                                       directional_coord_conversion_policy ) );
  }

  // Set the dimension distributions
  {
    std::shared_ptr<const Utility::UnivariateDistribution> raw_power_dist(
           new Utility::PowerDistribution<2>( 0.5, 0.0, 2.0 ) );
    std::shared_ptr<const Utility::UnivariateDistribution> raw_uniform_dist_a(
           new Utility::UniformDistribution( 0.0, 2*Utility::PhysicalConstants::pi, 0.1 ) );
    std::shared_ptr<const Utility::UnivariateDistribution> raw_uniform_dist_b(
                          new Utility::UniformDistribution( -1.0, 1.0, 2.0 ) );
    std::shared_ptr<const Utility::UnivariateDistribution> raw_uniform_dist_c(
                           new Utility::UniformDistribution( 0.0, 1.0, 1.0 ) );

    std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
      r_dimension_dist( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_power_dist ) );
    tmp_particle_distribution->setDimensionDistribution( r_dimension_dist );

    std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
      theta_dimension_dist( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_uniform_dist_a ) );
    tmp_particle_distribution->setDimensionDistribution( theta_dimension_dist );

    std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
      mu_dimension_dist( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_uniform_dist_b ) );
    tmp_particle_distribution->setDimensionDistribution( mu_dimension_dist );

    std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
      time_dimension_dist( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION>( raw_uniform_dist_c ) );
    tmp_particle_distribution->setDimensionDistribution( time_dimension_dist );

    std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
      energy_dimension_dist;

    // Create the fully tabular energy distribution
    {
      std::vector<double> primary_grid( {-1.0, 0.0, 1.0} );
      std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> > secondary_dists( 3 );

      // Create the secondary distribution in the first bin
      secondary_dists[0].reset( new Utility::UniformDistribution( 0.0, 10.0, 0.5 ) );

      // Create the secondary distribution in the second bin
      secondary_dists[1].reset( new Utility::UniformDistribution( 0.0, 20.0, 0.25 ) );

      // Create the secondary distribution in the third bin
      secondary_dists[2] = secondary_dists[1];

      std::shared_ptr<Utility::HistogramFullyTabularBasicBivariateDistribution>
        raw_dependent_distribution( new Utility::HistogramFullyTabularBasicBivariateDistribution( primary_grid, secondary_dists ) );

      raw_dependent_distribution->limitToPrimaryIndepLimits();

      energy_dimension_dist.reset( new MonteCarlo::TertiarySpatialDependentEnergyDimensionDistribution( raw_dependent_distribution ) );
    }

    tmp_particle_distribution->setDimensionDistribution( energy_dimension_dist );
    tmp_particle_distribution->constructDimensionDistributionDependencyTree();

    particle_distribution = tmp_particle_distribution;
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstStandardParticleSourceComponentDagMCRejection.cpp
//---------------------------------------------------------------------------//
