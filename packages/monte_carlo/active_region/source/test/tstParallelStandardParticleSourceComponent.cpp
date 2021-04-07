//---------------------------------------------------------------------------//
//!
//! \file   tstParallelStandardParticleSourceComponent.cpp
//! \author Alex Robinson
//! \brief  Standard particle source shared and distribution parallel unit
//!         tests.
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
#include "Geometry_InfiniteMediumModel.hpp"
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
#include "Utility_OpenMPProperties.hpp"
#include "Utility_Communicator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

using namespace MonteCarlo;

typedef std::tuple<MonteCarlo::NeutronState,
                   MonteCarlo::PhotonState,
                   MonteCarlo::ElectronState,
                   MonteCarlo::PositronState
                  > TestParticleStateTypes;

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<const MonteCarlo::ParticleDistribution> particle_distribution;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the source comp. can manage shared and distributed parallel ops
FRENSIE_UNIT_TEST_TEMPLATE( StandardParticleSourceComponent,
                            parallel_ops,
                            TestParticleStateTypes )
{
  FETCH_TEMPLATE_PARAM( 0, ParticleStateType );

  // Get the default communicator
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();
  
  // Construct a source component
  std::unique_ptr<MonteCarlo::ParticleSourceComponent>
    source_component;

  // Create a dummy geometry model for each source
  {
    std::shared_ptr<const Geometry::Model> model(
                           new Geometry::InfiniteMediumModel( comm->rank() ) );
    
    source_component.reset( new MonteCarlo::StandardParticleSourceComponent<ParticleStateType>( 0, 1.0, model, particle_distribution ) );
  }

  // Enable thread support
  source_component->enableThreadSupport( Utility::OpenMPProperties::getRequestedNumberOfThreads() );

  // Generate samples in each distibuted particle source component using the
  // number of requested threads
  std::vector<MonteCarlo::ParticleBank> banks( Utility::OpenMPProperties::getRequestedNumberOfThreads() );

  #pragma omp parallel for num_threads( Utility::OpenMPProperties::getRequestedNumberOfThreads() )
  for( unsigned long long history = 1000*comm->rank();
       history < 1000*(comm->rank()+1);
       ++history )
  {
    source_component->sampleParticleState( banks[Utility::OpenMPProperties::getThreadId()], history );
  }

  MonteCarlo::ParticleBank combined_bank;

  for( int i = 0; i < Utility::OpenMPProperties::getRequestedNumberOfThreads(); ++i )
  {
    combined_bank.merge( banks[i], [](const ParticleState& a, const ParticleState& b){ return a.getHistoryNumber() < b.getHistoryNumber(); } );
  }

  FRENSIE_CHECK_EQUAL( combined_bank.size(), 1000 );

  // Reduce the distributed source component data
  comm->barrier();

  source_component->reduceData( *comm, 0 );

  MonteCarlo::ParticleSourceComponent::CellIdSet starting_cells;
  source_component->getStartingCells( starting_cells );
  
  FRENSIE_CHECK_EQUAL( starting_cells.size(), comm->size() );

  for( size_t i = 0; i < comm->size(); ++i )
  {
    FRENSIE_CHECK( starting_cells.count( i ) );
  }

  if( comm->rank() == 0 )
  {
    FRENSIE_CHECK_EQUAL( source_component->getNumberOfTrials(), 1000*comm->size() );
    FRENSIE_CHECK_EQUAL( source_component->getNumberOfSamples(), 1000*comm->size() );
    FRENSIE_CHECK_EQUAL( source_component->getSamplingEfficiency(), 1.0 );

    FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 1000*comm->size() );
    FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 1000*comm->size() );
    FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 1.0 );
  
    FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 1000*comm->size() );
    FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 1000*comm->size() );
    FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 1.0 );
  
    FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 1000*comm->size() );
    FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 1000*comm->size() );
    FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 1.0 );
  
    FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 1000*comm->size() );
    FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 1000*comm->size() );
    FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 1.0 );
  
    FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 1000*comm->size() );
    FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 1000*comm->size() );
    FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 1.0 );
  
    FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 1000*comm->size() );
    FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 1000*comm->size() );
    FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 1.0 );
  
    FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::ENERGY_DIMENSION ), 1000*comm->size() );
    FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::ENERGY_DIMENSION ), 1000*comm->size() );
    FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::ENERGY_DIMENSION ), 1.0 );
  
    FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::TIME_DIMENSION ), 1000*comm->size() );
    FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::TIME_DIMENSION ), 1000*comm->size() );
    FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::TIME_DIMENSION ), 1.0 );
  
    FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::WEIGHT_DIMENSION ), 1000*comm->size() );
    FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::WEIGHT_DIMENSION ), 1000*comm->size() );
    FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::WEIGHT_DIMENSION ), 1.0 );
  }
  else
  {
    FRENSIE_CHECK_EQUAL( source_component->getNumberOfTrials(), 0 );
    FRENSIE_CHECK_EQUAL( source_component->getNumberOfSamples(), 0 );
    FRENSIE_CHECK_EQUAL( source_component->getSamplingEfficiency(), 1.0 );

    FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 1.0 );
  
    FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 1.0 );
  
    FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 1.0 );
  
    FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 1.0 );
  
    FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 1.0 );
  
    FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 1.0 );
  
    FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::ENERGY_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::ENERGY_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::ENERGY_DIMENSION ), 1.0 );
  
    FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::TIME_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::TIME_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::TIME_DIMENSION ), 1.0 );
  
    FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::WEIGHT_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::WEIGHT_DIMENSION ), 0 );
    FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::WEIGHT_DIMENSION ), 1.0 );
  }
}

//---------------------------------------------------------------------------//
// Check that the distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( StandardParticleSourceComponent,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_parallel_standard_particle_source_component" );
  std::ostringstream archive_ostream;

  // Get the default communicator
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );
  
    // Construct a source component
    std::shared_ptr<MonteCarlo::ParticleSourceComponent>
      source_component;

    // Create a dummy geometry model for each source
    {
      std::shared_ptr<const Geometry::Model> model(
                                      new Geometry::InfiniteMediumModel( 0 ) );
    
      source_component.reset( new MonteCarlo::StandardNeutronSourceComponent( 0, 1.0, model, particle_distribution ) );
    }

    // Enable thread support
    source_component->enableThreadSupport( Utility::OpenMPProperties::getRequestedNumberOfThreads() );

    // Generate samples in each distibuted particle source component using the
    // number of requested threads
    std::vector<MonteCarlo::ParticleBank> banks( Utility::OpenMPProperties::getRequestedNumberOfThreads() );

    #pragma omp parallel for num_threads( Utility::OpenMPProperties::getRequestedNumberOfThreads() )
    for( unsigned long long history = 1000*comm->rank();
         history < 1000*(comm->rank()+1);
         ++history )
    {
      source_component->sampleParticleState( banks[Utility::OpenMPProperties::getThreadId()], history );
    }

    // Reduce the distributed source component data
    comm->barrier();

    source_component->reduceData( *comm, 0 );

    if( comm->rank() == 0 )
    {
      FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(source_component) );
    }
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<MonteCarlo::ParticleSourceComponent> source_component;

  if( comm->rank() == 0 )
  {
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(source_component) );
  }

  iarchive.reset();

  FRENSIE_REQUIRE_NO_THROW( Utility::broadcast( *comm, source_component, 0 ) );

  // Enabling thread support should not destroy the current data
  source_component->enableThreadSupport( Utility::OpenMPProperties::getRequestedNumberOfThreads() );

  MonteCarlo::ParticleSourceComponent::CellIdSet starting_cells;
  source_component->getStartingCells( starting_cells );
  
  FRENSIE_CHECK_EQUAL( starting_cells.size(), 1 );
  FRENSIE_CHECK( starting_cells.count( 0 ) );
  
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfTrials(), 1000*comm->size() );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfSamples(), 1000*comm->size() );
  FRENSIE_CHECK_EQUAL( source_component->getSamplingEfficiency(), 1.0 );
  
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 1000*comm->size() );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 1000*comm->size() );
  FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 1.0 );
  
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 1000*comm->size() );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 1000*comm->size() );
  FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 1.0 );
  
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 1000*comm->size() );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 1000*comm->size() );
  FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 1.0 );
  
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 1000*comm->size() );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 1000*comm->size() );
  FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 1.0 );
  
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 1000*comm->size() );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 1000*comm->size() );
  FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 1.0 );
  
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 1000*comm->size() );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 1000*comm->size() );
  FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 1.0 );
  
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::ENERGY_DIMENSION ), 1000*comm->size() );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::ENERGY_DIMENSION ), 1000*comm->size() );
  FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::ENERGY_DIMENSION ), 1.0 );
  
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::TIME_DIMENSION ), 1000*comm->size() );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::TIME_DIMENSION ), 1000*comm->size() );
  FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::TIME_DIMENSION ), 1.0 );
  
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionTrials( MonteCarlo::WEIGHT_DIMENSION ), 1000*comm->size() );
  FRENSIE_CHECK_EQUAL( source_component->getNumberOfDimensionSamples( MonteCarlo::WEIGHT_DIMENSION ), 1000*comm->size() );
  FRENSIE_CHECK_EQUAL( source_component->getDimensionSamplingEfficiency( MonteCarlo::WEIGHT_DIMENSION ), 1.0 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

int threads = 1;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "threads",
                                        threads, 1,
                                        "Number of threads to use" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create the particle distribution
  std::shared_ptr<MonteCarlo::StandardParticleDistribution>
    tmp_particle_distribution;

  {
    std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
    spatial_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );

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
    std::shared_ptr<const Utility::UnivariateDistribution> raw_uniform_dist_a(
                          new Utility::UniformDistribution( -1.0, 1.0, 0.5 ) );
    std::shared_ptr<const Utility::UnivariateDistribution> raw_uniform_dist_b(
                           new Utility::UniformDistribution( 0.0, 1.0, 1.0 ) );

    std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
      x_dimension_dist( new MonteCarlo::IndependentPrimarySpatialDimensionDistribution( raw_uniform_dist_a ) );
    tmp_particle_distribution->setDimensionDistribution( x_dimension_dist );

    std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
      y_dimension_dist( new MonteCarlo::IndependentSecondarySpatialDimensionDistribution( raw_uniform_dist_a ) );
    tmp_particle_distribution->setDimensionDistribution( y_dimension_dist );

    std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
      z_dimension_dist( new MonteCarlo::IndependentTertiarySpatialDimensionDistribution( raw_uniform_dist_a ) );
    tmp_particle_distribution->setDimensionDistribution( z_dimension_dist );

    std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
      time_dimension_dist( new MonteCarlo::IndependentTimeDimensionDistribution( raw_uniform_dist_b ) );
    tmp_particle_distribution->setDimensionDistribution( time_dimension_dist );

    std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
      energy_dimension_dist;

    // Create the fully tabular energy distribution
    {
      std::vector<double> primary_grid( {-1.0, 0.0, 1.0} );
      std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
        secondary_dists( 3 );

      secondary_dists[0].reset( new Utility::UniformDistribution( 0.0, 10.0, 0.5 ) );
      secondary_dists[1].reset( new Utility::UniformDistribution( 0.0, 20.0, 0.25 ) );
      secondary_dists[2] = secondary_dists[1];

      std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution>
        raw_dependent_dist( new Utility::HistogramFullyTabularBasicBivariateDistribution( primary_grid, secondary_dists ) );
      raw_dependent_dist->limitToPrimaryIndepLimits();

      energy_dimension_dist.reset( new MonteCarlo::PrimarySpatialDependentEnergyDimensionDistribution( raw_dependent_dist ) );
    }

    tmp_particle_distribution->setDimensionDistribution( energy_dimension_dist );
    tmp_particle_distribution->constructDimensionDistributionDependencyTree();

    particle_distribution = tmp_particle_distribution;
  }

  // Set the number of threads to use
  Utility::OpenMPProperties::setNumberOfThreads( threads );
    
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstParallelStandardParticleSourceComponent.cpp
//---------------------------------------------------------------------------//

