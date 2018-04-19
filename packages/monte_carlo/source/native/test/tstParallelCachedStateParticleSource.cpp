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
#include "MonteCarlo_CachedStateParticleSource.hpp"
#include "MonteCarlo_SourceHDF5FileHandler.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "Geometry_InfiniteMediumModel.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_OpenMPProperties.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a source can manage shared and distributed parallel operations
TEUCHOS_UNIT_TEST( CachedStateParticleSource, parallel_ops )
{
  // Get the default communicator
  Teuchos::RCP<const Teuchos::Comm<unsigned long long> > comm =
    Teuchos::DefaultComm<unsigned long long>::getComm();
  
  std::shared_ptr<MonteCarlo::ParticleSource> source(
                      new MonteCarlo::CachedStateParticleSource(
                                 "test_parallel_state_source_bank_archive.xml",
                                 "state_bank",
                                 Utility::ArchivableObject::XML_ARCHIVE ) );

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
    combined_bank.merge( banks[i], [](const MonteCarlo::ParticleState& a, const MonteCarlo::ParticleState& b){ return a.getHistoryNumber() < b.getHistoryNumber(); } );
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
  // Get the default communicator
  Teuchos::RCP<const Teuchos::Comm<unsigned long long> > comm =
    Teuchos::DefaultComm<unsigned long long>::getComm();
  
  // Create a particle state cache
  if( comm->getRank() == 0 )
  {
    MonteCarlo::ParticleBank bank;
    
    for( unsigned long long i = 0; i < 1000*comm->getSize(); ++i )
    {
      MonteCarlo::PhotonState particle( i );
      particle.setSourceId( 0 );

      bank.push( particle );
    }

    std::ofstream ofs( "test_parallel_state_source_bank_archive.xml" );

    boost::archive::xml_oarchive ar(ofs);
    ar << boost::serialization::make_nvp( "state_bank", bank );
  }
  
  comm->barrier();
  
  // Set the number of threads to use
  Utility::OpenMPProperties::setNumberOfThreads( threads );
  
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstParallelCachedStateParticleSource.cpp
//---------------------------------------------------------------------------//
