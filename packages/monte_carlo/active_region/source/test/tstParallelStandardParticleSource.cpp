//---------------------------------------------------------------------------//
//!
//! \file   tstStandardParticleSource.cpp
//! \author Alex Robinson
//! \brief  Standard particle source unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_DefaultComm.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardParticleSource.hpp"
#include "MonteCarlo_StandardParticleDistribution.hpp"
#include "MonteCarlo_IndependentPhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_FullyTabularDependentPhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_PartiallyTabularDependentPhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_SourceUnitTestHarnessExtensions.hpp"
#include "Geometry_InfiniteMediumModel.hpp"
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
#include "Utility_OpenMPProperties.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

using namespace MonteCarlo;

//---------------------------------------------------------------------------//
// Testing variables
//---------------------------------------------------------------------------//
std::shared_ptr<const ParticleDistribution> particle_distribution;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a source can manage shared and distributed parallel operations
TEUCHOS_UNIT_TEST( StandardParticleSource, parallel_ops )
{
  // Create the particle source
  std::shared_ptr<MonteCarlo::ParticleSource> source(
               new MonteCarlo::StandardParticleSource( particle_distribution,
                                                       MonteCarlo::NEUTRON ) );

  // Get the default communicator
  Teuchos::RCP<const Teuchos::Comm<unsigned long long> > comm =
    Teuchos::DefaultComm<unsigned long long>::getComm();

  // Create a dummy geometry model for each source
  {
    std::shared_ptr<const Geometry::Model> model(
                        new Geometry::InfiniteMediumModel( comm->getRank() ) );

    source->embedInModel( model );
  }

  // Enable thread support
  source->enableThreadSupport( Utility::OpenMPProperties::getRequestedNumberOfThreads() );

  // Generate samples in each distributed particle source using the number
  // of requested threads
  Teuchos::Array<MonteCarlo::ParticleBank> banks( Utility::OpenMPProperties::getRequestedNumberOfThreads() );

  #pragma omp parallel for num_threads( Utility::OpenMPProperties::getRequestedNumberOfThreads() )
  for( unsigned long long history = 1000*comm->getRank();
       history < 1000*(comm->getRank()+1);
       ++history )
  {
    source->sampleParticleState( banks[Utility::OpenMPProperties::getThreadId()], history );
  }

  MonteCarlo::ParticleBank combined_bank;
  
  for( int i = 0; i < Utility::OpenMPProperties::getRequestedNumberOfThreads(); ++i )
  {
    combined_bank.merge( banks[i], [](const ParticleState& a, const ParticleState& b){ return a.getHistoryNumber() < b.getHistoryNumber(); } );
  }

  // Reduce the distributed source data
  comm->barrier();
  
  source->reduceData( comm, 0 );
  
  TEST_EQUALITY_CONST( combined_bank.size(), 1000 );

  std::set<Geometry::ModuleTraits::InternalCellHandle> starting_cells;
  source->getStartingCells( starting_cells );

  TEST_EQUALITY( starting_cells.size(), comm->getSize() );

  for( int i = 0; i < comm->getSize(); ++i )
    TEST_ASSERT( starting_cells.count( i ) );

  if( comm->getRank() == 0 )
  {
    TEST_EQUALITY_CONST( source->getNumberOfTrials(), 1000*comm->getSize() );
    TEST_EQUALITY_CONST( source->getNumberOfSamples(), 1000*comm->getSize() );
    TEST_EQUALITY_CONST( source->getSamplingEfficiency(), 1.0 );

    TEST_EQUALITY_CONST( source->getNumberOfDimensionTrials( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 1000*comm->getSize() );
    TEST_EQUALITY_CONST( source->getNumberOfDimensionSamples( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 1000*comm->getSize() );
    TEST_EQUALITY_CONST( source->getDimensionSamplingEfficiency( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 1.0 );
  
    TEST_EQUALITY_CONST( source->getNumberOfDimensionTrials( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 1000*comm->getSize() );
    TEST_EQUALITY_CONST( source->getNumberOfDimensionSamples( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 1000*comm->getSize() );
    TEST_EQUALITY_CONST( source->getDimensionSamplingEfficiency( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 1.0 );
  
    TEST_EQUALITY_CONST( source->getNumberOfDimensionTrials( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 1000*comm->getSize() );
    TEST_EQUALITY_CONST( source->getNumberOfDimensionSamples( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 1000*comm->getSize() );
    TEST_EQUALITY_CONST( source->getDimensionSamplingEfficiency( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 1.0 );
  
    TEST_EQUALITY_CONST( source->getNumberOfDimensionTrials( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 1000*comm->getSize() );
    TEST_EQUALITY_CONST( source->getNumberOfDimensionSamples( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 1000*comm->getSize() );
    TEST_EQUALITY_CONST( source->getDimensionSamplingEfficiency( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 1.0 );
  
    TEST_EQUALITY_CONST( source->getNumberOfDimensionTrials( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 1000*comm->getSize() );
    TEST_EQUALITY_CONST( source->getNumberOfDimensionSamples( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 1000*comm->getSize() );
    TEST_EQUALITY_CONST( source->getDimensionSamplingEfficiency( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 1.0 );
  
    TEST_EQUALITY_CONST( source->getNumberOfDimensionTrials( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 1000*comm->getSize() );
    TEST_EQUALITY_CONST( source->getNumberOfDimensionSamples( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 1000*comm->getSize() );
    TEST_EQUALITY_CONST( source->getDimensionSamplingEfficiency( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 1.0 );
  
    TEST_EQUALITY_CONST( source->getNumberOfDimensionTrials( MonteCarlo::ENERGY_DIMENSION ), 1000*comm->getSize() );
    TEST_EQUALITY_CONST( source->getNumberOfDimensionSamples( MonteCarlo::ENERGY_DIMENSION ), 1000*comm->getSize() );
    TEST_EQUALITY_CONST( source->getDimensionSamplingEfficiency( MonteCarlo::ENERGY_DIMENSION ), 1.0 );
  
    TEST_EQUALITY_CONST( source->getNumberOfDimensionTrials( MonteCarlo::TIME_DIMENSION ), 1000*comm->getSize() );
    TEST_EQUALITY_CONST( source->getNumberOfDimensionSamples( MonteCarlo::TIME_DIMENSION ), 1000*comm->getSize() );
    TEST_EQUALITY_CONST( source->getDimensionSamplingEfficiency( MonteCarlo::TIME_DIMENSION ), 1.0 );
  
    TEST_EQUALITY_CONST( source->getNumberOfDimensionTrials( MonteCarlo::WEIGHT_DIMENSION ), 1000*comm->getSize() );
    TEST_EQUALITY_CONST( source->getNumberOfDimensionSamples( MonteCarlo::WEIGHT_DIMENSION ), 1000*comm->getSize() );
    TEST_EQUALITY_CONST( source->getDimensionSamplingEfficiency( MonteCarlo::WEIGHT_DIMENSION ), 1.0 );
  }
  else
  {
    TEST_EQUALITY_CONST( source->getNumberOfTrials(), 0 );
    TEST_EQUALITY_CONST( source->getNumberOfSamples(), 0 );
    TEST_EQUALITY_CONST( source->getSamplingEfficiency(), 1.0 );

    TEST_EQUALITY_CONST( source->getNumberOfDimensionTrials( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 0 );
    TEST_EQUALITY_CONST( source->getNumberOfDimensionSamples( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 0 );
    TEST_EQUALITY_CONST( source->getDimensionSamplingEfficiency( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 1.0 );
  
    TEST_EQUALITY_CONST( source->getNumberOfDimensionTrials( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 0 );
    TEST_EQUALITY_CONST( source->getNumberOfDimensionSamples( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 0 );
    TEST_EQUALITY_CONST( source->getDimensionSamplingEfficiency( MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 1.0 );
  
    TEST_EQUALITY_CONST( source->getNumberOfDimensionTrials( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 0 );
    TEST_EQUALITY_CONST( source->getNumberOfDimensionSamples( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 0 );
    TEST_EQUALITY_CONST( source->getDimensionSamplingEfficiency( MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 1.0 );
  
    TEST_EQUALITY_CONST( source->getNumberOfDimensionTrials( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 0 );
    TEST_EQUALITY_CONST( source->getNumberOfDimensionSamples( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 0 );
    TEST_EQUALITY_CONST( source->getDimensionSamplingEfficiency( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 1.0 );
  
    TEST_EQUALITY_CONST( source->getNumberOfDimensionTrials( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 0 );
    TEST_EQUALITY_CONST( source->getNumberOfDimensionSamples( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 0 );
    TEST_EQUALITY_CONST( source->getDimensionSamplingEfficiency( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 1.0 );
  
    TEST_EQUALITY_CONST( source->getNumberOfDimensionTrials( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 0 );
    TEST_EQUALITY_CONST( source->getNumberOfDimensionSamples( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 0 );
    TEST_EQUALITY_CONST( source->getDimensionSamplingEfficiency( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 1.0 );
  
    TEST_EQUALITY_CONST( source->getNumberOfDimensionTrials( MonteCarlo::ENERGY_DIMENSION ), 0 );
    TEST_EQUALITY_CONST( source->getNumberOfDimensionSamples( MonteCarlo::ENERGY_DIMENSION ), 0 );
    TEST_EQUALITY_CONST( source->getDimensionSamplingEfficiency( MonteCarlo::ENERGY_DIMENSION ), 1.0 );
  
    TEST_EQUALITY_CONST( source->getNumberOfDimensionTrials( MonteCarlo::TIME_DIMENSION ), 0 );
    TEST_EQUALITY_CONST( source->getNumberOfDimensionSamples( MonteCarlo::TIME_DIMENSION ), 0 );
    TEST_EQUALITY_CONST( source->getDimensionSamplingEfficiency( MonteCarlo::TIME_DIMENSION ), 1.0 );
  
    TEST_EQUALITY_CONST( source->getNumberOfDimensionTrials( MonteCarlo::WEIGHT_DIMENSION ), 0 );
    TEST_EQUALITY_CONST( source->getNumberOfDimensionSamples( MonteCarlo::WEIGHT_DIMENSION ), 0 );
    TEST_EQUALITY_CONST( source->getDimensionSamplingEfficiency( MonteCarlo::WEIGHT_DIMENSION ), 1.0 );
  }
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

int threads = 1;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "threads",
                   &threads,
                   "Number of threads to use" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
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
                                       2,
                                       "source distribution",
                                       spatial_coord_conversion_policy,
                                       directional_coord_conversion_policy ) );
  }

  // Set the dimension distributions
  {
    std::shared_ptr<const Utility::OneDDistribution> raw_uniform_dist_a(
                          new Utility::UniformDistribution( -1.0, 1.0, 0.5 ) );
    std::shared_ptr<const Utility::OneDDistribution> raw_uniform_dist_b(
                           new Utility::UniformDistribution( 0.0, 1.0, 1.0 ) );

    std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
      x_dimension_dist( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_uniform_dist_a ) );
    tmp_particle_distribution->setDimensionDistribution( x_dimension_dist );

    std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
      y_dimension_dist( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_uniform_dist_a ) );
    tmp_particle_distribution->setDimensionDistribution( y_dimension_dist );

    std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
      z_dimension_dist( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_uniform_dist_a ) );
    tmp_particle_distribution->setDimensionDistribution( z_dimension_dist );

    std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
      time_dimension_dist( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION>( raw_uniform_dist_b ) );
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
      
      energy_dimension_dist.reset( new MonteCarlo::FullyTabularDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION>( raw_dependent_distribution ) );
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

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstParallelStandardParticleSource.cpp
//---------------------------------------------------------------------------//
