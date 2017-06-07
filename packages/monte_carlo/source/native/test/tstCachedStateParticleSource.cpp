//---------------------------------------------------------------------------//
//!
//! \file   tstCachedStateParticleSource.cpp
//! \author Alex Robinson
//! \brief  Cached state particle source unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <memory>

// Boost Includes
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/nvp.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "MonteCarlo_CachedStateParticleSource.hpp"
#include "MonteCarlo_SourceHDF5FileHandler.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing functions
//---------------------------------------------------------------------------//
// Initialize the source
void initializeSource( std::shared_ptr<MonteCarlo::ParticleSource>& source )
{
  MonteCarlo::ParticleBank bank;

  boost::shared_ptr<MonteCarlo::ParticleState> particle(
					 new MonteCarlo::PhotonState( 1ull ) );
  particle->setSourceId( 0 );

  bank.push( *particle );

  particle.reset( new MonteCarlo::NeutronState( 10ull ) );
  particle->setSourceId( 0 );

  bank.push( *particle );

  particle.reset( new MonteCarlo::PhotonState( 1ull ) );
  particle->setSourceId( 0 );

  bank.push( *particle );

  particle.reset( new MonteCarlo::ElectronState( 11ull ) );
  particle->setSourceId( 0 );

  bank.push( *particle );

  particle.reset( new MonteCarlo::NeutronState( 12ull ) );
  particle->setSourceId( 0 );

  bank.push( *particle );

  particle.reset( new MonteCarlo::PhotonState( 13ull ) );
  particle->setSourceId( 1 );

  bank.push( *particle );

  particle.reset( new MonteCarlo::ElectronState( 14ull ) );
  particle->setSourceId( 1 );

  bank.push( *particle );

  particle.reset( new MonteCarlo::NeutronState( 15ull ) );
  particle->setSourceId( 2 );

  bank.push( *particle );

  particle.reset( new MonteCarlo::PhotonState( 16ull ) );
  particle->setSourceId( 0 );

  bank.push( *particle );

  std::string bank_archive_name( "test_state_source_bank_archive.xml" );
  std::string bank_name_in_archive( "state_bank" );

  {
    std::ofstream ofs( bank_archive_name.c_str() );

    boost::archive::xml_oarchive ar(ofs);
    ar << boost::serialization::make_nvp( bank_name_in_archive.c_str(), bank );
  }

  source.reset( new MonteCarlo::CachedStateParticleSource(
				    bank_archive_name,
				    bank_name_in_archive,
				    Utility::ArchivableObject::XML_ARCHIVE ) );
}

// Compare history numbers
bool compareHistoryNumbers( const MonteCarlo::ParticleState& state_a,
			    const MonteCarlo::ParticleState& state_b )
{
  return state_a.getHistoryNumber() < state_b.getHistoryNumber();
}


//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the source id can be returned
TEUCHOS_UNIT_TEST( CachedStateParticleSource, getId )
{
  std::shared_ptr<MonteCarlo::ParticleSource> source;

  initializeSource( source );

  TEST_EQUALITY_CONST( source->getId(), MonteCarlo::ModuleTraits::reserved_internal_roi_handle );
}

//---------------------------------------------------------------------------//
// Check that particle states can be "sampled"
TEUCHOS_UNIT_TEST( CachedStateParticleSource, sampleParticleState )
{
  std::shared_ptr<MonteCarlo::ParticleSource> source;

  initializeSource( source );

  MonteCarlo::ParticleBank bank;
  source->sampleParticleState( bank, 0 );

  TEST_EQUALITY_CONST( bank.size(), 2 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 0ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );
  TEST_EQUALITY( bank.top().getSourceId(), source->getId() );

  bank.pop();

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 0ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );
  TEST_EQUALITY( bank.top().getSourceId(), source->getId() );

  bank.pop();

  // Sample from the source again
  source->sampleParticleState( bank, 1 );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 1ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::NEUTRON );
  TEST_EQUALITY( bank.top().getSourceId(), source->getId() );

  bank.pop();

  // Sample from the source again
  source->sampleParticleState( bank, 2 );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 2ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::ELECTRON );
  TEST_EQUALITY( bank.top().getSourceId(), source->getId() );

  bank.pop();

  // Sample from the source again
  source->sampleParticleState( bank, 3 );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 3ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::NEUTRON );
  TEST_EQUALITY( bank.top().getSourceId(), source->getId() );

  bank.pop();

  // Sample from the source again
  source->sampleParticleState( bank, 4 );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 4ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );
  TEST_EQUALITY( bank.top().getSourceId(), source->getId() );

  bank.pop();

  // Sample from the source again
  source->sampleParticleState( bank, 5 );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 5ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::ELECTRON );
  TEST_EQUALITY( bank.top().getSourceId(), source->getId() );

  bank.pop();

  // Sample from the source again
  source->sampleParticleState( bank, 6 );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 6ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::NEUTRON );
  TEST_EQUALITY( bank.top().getSourceId(), source->getId() );

  bank.pop();

  // Sample from the source again
  source->sampleParticleState( bank, 7 );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 7ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );
  TEST_EQUALITY( bank.top().getSourceId(), source->getId() );

  bank.pop();

  // Attempting to get another particle state should do nothing
  source->sampleParticleState( bank, 8 );

  TEST_EQUALITY_CONST( bank.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the source can accumulate sampling statistics
TEUCHOS_UNIT_TEST( CachedStateParticleSource, sampling_statistics )
{
  std::shared_ptr<MonteCarlo::ParticleSource> source;

  initializeSource( source );

  MonteCarlo::ParticleBank bank;

  for( unsigned long long i = 0; i < 8; ++i )
    source->sampleParticleState( bank, i );

  TEST_EQUALITY_CONST( bank.size(), 9 );

  TEST_EQUALITY_CONST( source->getNumberOfTrials(), 9 );
  TEST_EQUALITY_CONST( source->getNumberOfSamples(), 9 );
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

//---------------------------------------------------------------------------//
// Check that a summary of the source data can be printed
TEUCHOS_UNIT_TEST( StandardParticleSource, printSummary )
{
  std::shared_ptr<MonteCarlo::ParticleSource> source;

  initializeSource( source );

  MonteCarlo::ParticleBank bank;

  for( unsigned long long i = 0; i < 8; ++i )
    source->sampleParticleState( bank, i );

  std::ostringstream oss;

  source->printSummary( oss );

  TEST_ASSERT( oss.str().size() > 0 );
}

//---------------------------------------------------------------------------//
// Check that the source data can be exported
TEUCHOS_UNIT_TEST( CachedStateParticleSource, exportData )
{
  std::shared_ptr<MonteCarlo::ParticleSource> source;

  initializeSource( source );

  MonteCarlo::ParticleBank bank;

  for( unsigned long long i = 0; i < 8; ++i )
    source->sampleParticleState( bank, i );

  // Export the source data
  {
    std::shared_ptr<Utility::HDF5FileHandler> hdf5_file(
                                                new Utility::HDF5FileHandler );
    hdf5_file->openHDF5FileAndOverwrite( "test_standard_particle_source.h5" );

    source->exportData( hdf5_file );

    hdf5_file->closeHDF5File();
  }

  // Check that the source data was written correctly
  MonteCarlo::SourceHDF5FileHandler exported_source_data(
                                 "test_standard_particle_source.h5",
                                 MonteCarlo::HDF5FileHandler::READ_ONLY_FILE );

  TEST_ASSERT( exported_source_data.doesSourceExist( source->getId() ) );
  TEST_EQUALITY_CONST( exported_source_data.getNumberOfSourceSamplingTrials( source->getId() ), 9 );
  TEST_EQUALITY_CONST( exported_source_data.getNumberOfSourceSamples( source->getId() ), 9 );
  
  TEST_ASSERT( !exported_source_data.doesSourceDimensionExist( source->getId(), MonteCarlo::PRIMARY_SPATIAL_DIMENSION ) );
  TEST_ASSERT( !exported_source_data.doesSourceDimensionExist( source->getId(), MonteCarlo::SECONDARY_SPATIAL_DIMENSION ) );
  TEST_ASSERT( !exported_source_data.doesSourceDimensionExist( source->getId(), MonteCarlo::TERTIARY_SPATIAL_DIMENSION ) );
  TEST_ASSERT( !exported_source_data.doesSourceDimensionExist( source->getId(), MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ) );
  TEST_ASSERT( !exported_source_data.doesSourceDimensionExist( source->getId(), MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ) );
  TEST_ASSERT( !exported_source_data.doesSourceDimensionExist( source->getId(), MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ) );
  TEST_ASSERT( !exported_source_data.doesSourceDimensionExist( source->getId(), MonteCarlo::ENERGY_DIMENSION ) );
  TEST_ASSERT( !exported_source_data.doesSourceDimensionExist( source->getId(), MonteCarlo::TIME_DIMENSION ) );
  TEST_ASSERT( !exported_source_data.doesSourceDimensionExist( source->getId(), MonteCarlo::WEIGHT_DIMENSION ) );
}

//---------------------------------------------------------------------------//
// Check that the source data can be reset
TEUCHOS_UNIT_TEST( CachedStateParticleSource, resetData )
{
  std::shared_ptr<MonteCarlo::ParticleSource> source;

  initializeSource( source );

  MonteCarlo::ParticleBank bank;

  for( unsigned long long i = 0; i < 8; ++i )
    source->sampleParticleState( bank, i );

  source->resetData();
  
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

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstCachedStateParticleSource.cpp
//---------------------------------------------------------------------------//
