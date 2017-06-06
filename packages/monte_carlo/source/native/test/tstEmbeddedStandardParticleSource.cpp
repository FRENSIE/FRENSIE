//---------------------------------------------------------------------------//
//!
//! \file   tstStandardParticleSource_DagMC.cpp
//! \author Alex Robinson
//! \brief  Standard particle source unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardParticleSource.hpp"
#include "MonteCarlo_StandardParticleDistribution.hpp"
#include "MonteCarlo_IndependentPhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_FullyTabularDependentPhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_PartiallyTabularDependentPhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_SourceUnitTestHarnessExtensions.hpp"
#include "Geometry_ModelFactory.hpp"
#include "Utility_BasicCartesianCoordinateConversionPolicy.hpp"
#include "Utility_BasicSphericalCoordinateConversionPolicy.hpp"
#include "Utility_BasicCylindricalSpatialCoordinateConversionPolicy.hpp"
#include "Utility_HistogramFullyTabularTwoDDistribution.hpp"
#include "Utility_HistogramPartiallyTabularTwoDDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_PowerDistribution.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_ExponentialDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

using namespace MonteCarlo;

//---------------------------------------------------------------------------//
// Testing variables
//---------------------------------------------------------------------------//
std::shared_ptr<const ParticleDistribution> particle_distribution;
std::shared_ptr<const Geometry::Model> geometry_model;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a particle state can be sampled from an embedded source
TEUCHOS_UNIT_TEST( StandardParticleSource, sampleParticleState )
{
  std::shared_ptr<MonteCarlo::ParticleSource> source(
                new MonteCarlo::StandardParticleSource( particle_distribution,
                                                        MonteCarlo::PHOTON ) );

  // Embed the source in the geometry model
  source->embedInModel( geometry_model );
    
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

  source->sampleParticleState( bank, 0ull );

  TEST_EQUALITY_CONST( bank.size(), 1 );
  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 0ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getXPosition(), 0.0, 1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getYPosition(), 0.0, 1e-12 );
  TEST_FLOATING_EQUALITY( bank.top().getZPosition(), -2.0, 1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getXDirection(), 0.0, 1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getYDirection(), 0.0, 1e-12 );
  TEST_FLOATING_EQUALITY( bank.top().getZDirection(), -1.0, 1e-12 );
  TEST_EQUALITY_CONST( bank.top().getSourceEnergy(), 5.0 );
  TEST_EQUALITY_CONST( bank.top().getEnergy(), 5.0 );
  TEST_EQUALITY_CONST( bank.top().getSourceTime(), 0.0 );
  TEST_EQUALITY_CONST( bank.top().getTime(), 0.0 );
  TEST_EQUALITY_CONST( bank.top().getSourceId(), 1 );
  TEST_EQUALITY_CONST( bank.top().getSourceCell(), 3 );
  TEST_EQUALITY_CONST( bank.top().getCell(), 3 );
  TEST_EQUALITY_CONST( bank.top().getSourceWeight(), 1.0 );
  TEST_EQUALITY_CONST( bank.top().getWeight(), 1.0 );

  bank.pop();

  fake_stream[0] = 0.0; // r
  fake_stream[1] = 0.0; // theta
  fake_stream[2] = 0.0; // mu
  fake_stream[3] = 0.5; // energy
  fake_stream[4] = 0.0; // theta
  fake_stream[5] = 0.0; // mu
  fake_stream[6] = 0.0; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  source->sampleParticleState( bank, 0ull );

  TEST_EQUALITY_CONST( bank.size(), 1 );
  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 0ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getXPosition(), 0.0, 1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getYPosition(), 0.0, 1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getZPosition(), 0.0, 1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getXDirection(), 0.0, 1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getYDirection(), 0.0, 1e-12 );
  TEST_FLOATING_EQUALITY( bank.top().getZDirection(), -1.0, 1e-12 );
  TEST_EQUALITY_CONST( bank.top().getSourceEnergy(), 5.0 );
  TEST_EQUALITY_CONST( bank.top().getEnergy(), 5.0 );
  TEST_EQUALITY_CONST( bank.top().getSourceTime(), 0.0 );
  TEST_EQUALITY_CONST( bank.top().getTime(), 0.0 );
  TEST_EQUALITY_CONST( bank.top().getSourceId(), 1 );
  TEST_EQUALITY_CONST( bank.top().getSourceCell(), 2 );
  TEST_EQUALITY_CONST( bank.top().getCell(), 2 );
  TEST_EQUALITY_CONST( bank.top().getSourceWeight(), 1.0 );
  TEST_EQUALITY_CONST( bank.top().getWeight(), 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  std::set<Geometry::ModuleTraits::InternalCellHandle> start_cell_cache;
  source->getStartingCells( start_cell_cache );

  TEST_EQUALITY_CONST( start_cell_cache.size(), 2 );
  TEST_ASSERT( start_cell_cache.count( 2 ) );
  TEST_ASSERT( start_cell_cache.count( 3 ) );
}

//---------------------------------------------------------------------------//
// Check that a particle state can be sampled from a source with rejection
// cells
TEUCHOS_UNIT_TEST( StandardParticleSource,
                   sampleParticleState_rejection_cells_larger )
{
  std::shared_ptr<MonteCarlo::ParticleSource> source(
                new MonteCarlo::StandardParticleSource( particle_distribution,
                                                        MonteCarlo::PHOTON ) );

  // Embed the source in the geometry model
  source->embedInModel( geometry_model );

  // Set the rejection cell
  source->setRejectionCell( 2 );
  source->setRejectionCell( 3 );
    
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

  source->sampleParticleState( bank, 0ull );

  TEST_EQUALITY_CONST( bank.size(), 1 );
  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 0ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getXPosition(), 0.0, 1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getYPosition(), 0.0, 1e-12 );
  TEST_FLOATING_EQUALITY( bank.top().getZPosition(), -2.0, 1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getXDirection(), 0.0, 1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getYDirection(), 0.0, 1e-12 );
  TEST_FLOATING_EQUALITY( bank.top().getZDirection(), -1.0, 1e-12 );
  TEST_EQUALITY_CONST( bank.top().getSourceEnergy(), 5.0 );
  TEST_EQUALITY_CONST( bank.top().getEnergy(), 5.0 );
  TEST_EQUALITY_CONST( bank.top().getSourceTime(), 0.0 );
  TEST_EQUALITY_CONST( bank.top().getTime(), 0.0 );
  TEST_EQUALITY_CONST( bank.top().getSourceId(), 1 );
  TEST_EQUALITY_CONST( bank.top().getSourceCell(), 3 );
  TEST_EQUALITY_CONST( bank.top().getCell(), 3 );
  TEST_EQUALITY_CONST( bank.top().getSourceWeight(), 1.0 );
  TEST_EQUALITY_CONST( bank.top().getWeight(), 1.0 );

  bank.pop();

  fake_stream[0] = 0.0; // r
  fake_stream[1] = 0.0; // theta
  fake_stream[2] = 0.0; // mu
  fake_stream[3] = 0.5; // energy
  fake_stream[4] = 0.0; // theta
  fake_stream[5] = 0.0; // mu
  fake_stream[6] = 0.0; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  source->sampleParticleState( bank, 0ull );

  TEST_EQUALITY_CONST( bank.size(), 1 );
  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 0ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getXPosition(), 0.0, 1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getYPosition(), 0.0, 1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getZPosition(), 0.0, 1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getXDirection(), 0.0, 1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getYDirection(), 0.0, 1e-12 );
  TEST_FLOATING_EQUALITY( bank.top().getZDirection(), -1.0, 1e-12 );
  TEST_EQUALITY_CONST( bank.top().getSourceEnergy(), 5.0 );
  TEST_EQUALITY_CONST( bank.top().getEnergy(), 5.0 );
  TEST_EQUALITY_CONST( bank.top().getSourceTime(), 0.0 );
  TEST_EQUALITY_CONST( bank.top().getTime(), 0.0 );
  TEST_EQUALITY_CONST( bank.top().getSourceId(), 1 );
  TEST_EQUALITY_CONST( bank.top().getSourceCell(), 2 );
  TEST_EQUALITY_CONST( bank.top().getCell(), 2 );
  TEST_EQUALITY_CONST( bank.top().getSourceWeight(), 1.0 );
  TEST_EQUALITY_CONST( bank.top().getWeight(), 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_EQUALITY_CONST( source->getNumberOfTrials(), 2 );
  TEST_EQUALITY_CONST( source->getNumberOfSamples(), 2 );
  TEST_EQUALITY_CONST( source->getSamplingEfficiency(), 1.0 );

  std::set<Geometry::ModuleTraits::InternalCellHandle> start_cell_cache;
  source->getStartingCells( start_cell_cache );

  TEST_EQUALITY_CONST( start_cell_cache.size(), 2 );
  TEST_ASSERT( start_cell_cache.count( 2 ) );
  TEST_ASSERT( start_cell_cache.count( 3 ) );
}

//---------------------------------------------------------------------------//
// Check that a particle state can be sampled from a source with rejection
// cells
TEUCHOS_UNIT_TEST( StandardParticleSource,
                   sampleParticleState_rejection_cells_smaller )
{
  std::shared_ptr<MonteCarlo::ParticleSource> source(
                new MonteCarlo::StandardParticleSource( particle_distribution,
                                                        MonteCarlo::PHOTON ) );

  // Embed the source in the geometry model
  source->embedInModel( geometry_model );

  // Set the rejection cell
  source->setRejectionCell( 2 );
    
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

  source->sampleParticleState( bank, 0ull );

  TEST_EQUALITY_CONST( bank.size(), 1 );
  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 0ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getXPosition(), 0.0, 1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getYPosition(), 0.0, 1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getZPosition(), 0.0, 1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getXDirection(), 0.0, 1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getYDirection(), 0.0, 1e-12 );
  TEST_FLOATING_EQUALITY( bank.top().getZDirection(), -1.0, 1e-12 );
  TEST_EQUALITY_CONST( bank.top().getSourceEnergy(), 5.0 );
  TEST_EQUALITY_CONST( bank.top().getEnergy(), 5.0 );
  TEST_EQUALITY_CONST( bank.top().getSourceTime(), 0.0 );
  TEST_EQUALITY_CONST( bank.top().getTime(), 0.0 );
  TEST_EQUALITY_CONST( bank.top().getSourceId(), 1 );
  TEST_EQUALITY_CONST( bank.top().getSourceCell(), 2 );
  TEST_EQUALITY_CONST( bank.top().getCell(), 2 );
  TEST_EQUALITY_CONST( bank.top().getSourceWeight(), 1.0 );
  TEST_EQUALITY_CONST( bank.top().getWeight(), 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_EQUALITY_CONST( source->getNumberOfTrials(), 2 );
  TEST_EQUALITY_CONST( source->getNumberOfSamples(), 1 );
  TEST_EQUALITY_CONST( source->getSamplingEfficiency(), 0.5 );

  std::set<Geometry::ModuleTraits::InternalCellHandle> start_cell_cache;
  source->getStartingCells( start_cell_cache );

  TEST_EQUALITY_CONST( start_cell_cache.size(), 1 );
  TEST_ASSERT( start_cell_cache.count( 2 ) );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_geom_xml_file_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_geom_xml_file",
                   &test_geom_xml_file_name,
                   "Test xml geometry file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
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
                                       1,
                                       "source distribution",
                                       spatial_coord_conversion_policy,
                                       directional_coord_conversion_policy ) );
  }

  // Set the dimension distributions
  {
    std::shared_ptr<const Utility::OneDDistribution> raw_power_dist(
           new Utility::PowerDistribution<2>( 0.5, 0.0, 2.0 ) );
    std::shared_ptr<const Utility::OneDDistribution> raw_uniform_dist_a(
           new Utility::UniformDistribution( 0.0, 2*Utility::PhysicalConstants::pi, 0.1 ) );
    std::shared_ptr<const Utility::OneDDistribution> raw_uniform_dist_b(
                          new Utility::UniformDistribution( -1.0, 1.0, 2.0 ) );
    std::shared_ptr<const Utility::OneDDistribution> raw_uniform_dist_c(
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
      Utility::HistogramFullyTabularTwoDDistribution::DistributionType
        distribution_data( 3 );
      
      // Create the secondary distribution in the first bin
      Utility::get<0>( distribution_data[0] ) = -1.0;
      Utility::get<1>( distribution_data[0] ).reset( new Utility::UniformDistribution( 0.0, 10.0, 0.5 ) );
      
      
      // Create the secondary distribution in the second bin
      Utility::get<0>( distribution_data[1] ) = 0.0;
      Utility::get<1>( distribution_data[1] ).reset( new Utility::UniformDistribution( 0.0, 20.0, 0.25 ) );
      
      // Create the secondary distribution in the third bin
      Utility::get<0>( distribution_data[2] ) = 1.0;
      Utility::get<1>( distribution_data[2] ) =
        Utility::get<1>( distribution_data[1] );

      std::shared_ptr<Utility::HistogramFullyTabularTwoDDistribution>
        raw_dependent_distribution( new Utility::HistogramFullyTabularTwoDDistribution( distribution_data ) );

      raw_dependent_distribution->limitToPrimaryIndepLimits();
      
      energy_dimension_dist.reset( new MonteCarlo::FullyTabularDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION>( raw_dependent_distribution ) );
    }
    
    tmp_particle_distribution->setDimensionDistribution( energy_dimension_dist );
    tmp_particle_distribution->constructDimensionDistributionDependencyTree();
    
    particle_distribution = tmp_particle_distribution;
  }
  
  // Initialize the geometry model
  Teuchos::RCP<const Teuchos::ParameterList> model_data =
    Teuchos::getParametersFromXmlFile( test_geom_xml_file_name );
  
  geometry_model = Geometry::ModelFactory::createModel( *model_data );
                                                       
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstStandardParticleSource_DagMC.cpp
//---------------------------------------------------------------------------//
