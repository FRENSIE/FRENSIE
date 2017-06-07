//---------------------------------------------------------------------------//
//!
//! \file   tstCachedStateParticleSource_DagMC.cpp
//! \author Alex Robinson
//! \brief  Cached state particle source unit tests
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
#include <Teuchos_XMLParameterListCoreHelpers.hpp>

// FRENSIE Includes
#include "MonteCarlo_CachedStateParticleSource.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_SourceUnitTestHarnessExtensions.hpp"
#include "Geometry_ModelFactory.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing variables
//---------------------------------------------------------------------------//
std::shared_ptr<const Geometry::Model> geometry_model;

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
  particle->setPosition( 0.0, 0.0, 0.0 );
  particle->setDirection( 1.0, 0.0, 0.0 );

  bank.push( *particle );

  particle.reset( new MonteCarlo::NeutronState( 10ull ) );
  particle->setSourceId( 0 );
  particle->setPosition( 1.0, 1.0, 1.0 );
  particle->setDirection( 0.0, 1.0, 0.0 );

  bank.push( *particle );

  particle.reset( new MonteCarlo::PhotonState( 1ull ) );
  particle->setSourceId( 0 );
  particle->setPosition( 0.0, 0.0, 2.0 );
  particle->setDirection( 0.0, 0.0, 1.0 );

  bank.push( *particle );

  particle.reset( new MonteCarlo::ElectronState( 11ull ) );
  particle->setSourceId( 0 );
  particle->setPosition( -1.0, -1.0, -1.0 );
  particle->setDirection( -1.0, 0.0, 0.0 );

  bank.push( *particle );

  particle.reset( new MonteCarlo::NeutronState( 12ull ) );
  particle->setSourceId( 0 );
  particle->setPosition( 0.0, 0.0, 0.0 );
  particle->setDirection( 1.0, 0.0, 0.0 );

  bank.push( *particle );

  particle.reset( new MonteCarlo::PhotonState( 13ull ) );
  particle->setSourceId( 1 );
  particle->setPosition( 0.0, 0.0, 0.0 );
  particle->setDirection( 1.0, 0.0, 0.0 );

  bank.push( *particle );

  particle.reset( new MonteCarlo::ElectronState( 14ull ) );
  particle->setSourceId( 1 );
  particle->setPosition( 0.0, 0.0, 0.0 );
  particle->setDirection( 1.0, 0.0, 0.0 );

  bank.push( *particle );

  particle.reset( new MonteCarlo::NeutronState( 15ull ) );
  particle->setSourceId( 2 );
  particle->setPosition( 0.0, 0.0, 0.0 );
  particle->setDirection( 1.0, 0.0, 0.0 );

  bank.push( *particle );

  particle.reset( new MonteCarlo::PhotonState( 16ull ) );
  particle->setSourceId( 0 );
  particle->setPosition( 0.0, 0.0, 0.0 );
  particle->setDirection( 1.0, 0.0, 0.0 );

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

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a particle state can be sampled from an embedded source
TEUCHOS_UNIT_TEST( CachedStateParticleSource, sampleParticleState )
{
  std::shared_ptr<MonteCarlo::ParticleSource> source;

  initializeSource( source );

  source->embedInModel( geometry_model );

  MonteCarlo::ParticleBank bank;

  // Sample from the source
  source->sampleParticleState( bank, 0 );

  TEST_EQUALITY_CONST( bank.size(), 2 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 0ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );
  TEST_EQUALITY( bank.top().getSourceId(), source->getId() );
  TEST_EQUALITY_CONST( bank.top().getSourceCell(), 2 );
  TEST_EQUALITY_CONST( bank.top().getCell(), 2 );

  bank.pop();

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 0ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );
  TEST_EQUALITY( bank.top().getSourceId(), source->getId() );
  TEST_EQUALITY_CONST( bank.top().getSourceCell(), 3 );
  TEST_EQUALITY_CONST( bank.top().getCell(), 3 );

  bank.pop();

  // Sample from the source again
  source->sampleParticleState( bank, 1 );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 1ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::NEUTRON );
  TEST_EQUALITY( bank.top().getSourceId(), source->getId() );
  TEST_EQUALITY_CONST( bank.top().getSourceCell(), 2 );
  TEST_EQUALITY_CONST( bank.top().getCell(), 2 );

  bank.pop();

  // Sample from the source again
  source->sampleParticleState( bank, 2 );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 2ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::ELECTRON );
  TEST_EQUALITY( bank.top().getSourceId(), source->getId() );
  TEST_EQUALITY_CONST( bank.top().getSourceCell(), 2 );
  TEST_EQUALITY_CONST( bank.top().getCell(), 2 );

  bank.pop();

  // Sample from the source again
  source->sampleParticleState( bank, 3 );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 3ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::NEUTRON );
  TEST_EQUALITY( bank.top().getSourceId(), source->getId() );
  TEST_EQUALITY_CONST( bank.top().getSourceCell(), 2 );
  TEST_EQUALITY_CONST( bank.top().getCell(), 2 );

  bank.pop();

  // Sample from the source again
  source->sampleParticleState( bank, 4 );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 4ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );
  TEST_EQUALITY( bank.top().getSourceId(), source->getId() );
  TEST_EQUALITY_CONST( bank.top().getSourceCell(), 2 );
  TEST_EQUALITY_CONST( bank.top().getCell(), 2 );

  bank.pop();

  // Sample from the source again
  source->sampleParticleState( bank, 5 );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 5ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::ELECTRON );
  TEST_EQUALITY( bank.top().getSourceId(), source->getId() );
  TEST_EQUALITY_CONST( bank.top().getSourceCell(), 2 );
  TEST_EQUALITY_CONST( bank.top().getCell(), 2 );

  bank.pop();

  // Sample from the source again
  source->sampleParticleState( bank, 6 );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 6ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::NEUTRON );
  TEST_EQUALITY( bank.top().getSourceId(), source->getId() );
  TEST_EQUALITY_CONST( bank.top().getSourceCell(), 2 );
  TEST_EQUALITY_CONST( bank.top().getCell(), 2 );

  bank.pop();

  // Sample from the source again
  source->sampleParticleState( bank, 7 );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 7ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );
  TEST_EQUALITY( bank.top().getSourceId(), source->getId() );
  TEST_EQUALITY_CONST( bank.top().getSourceCell(), 2 );
  TEST_EQUALITY_CONST( bank.top().getCell(), 2 );

  bank.pop();

  // Attempting to get another particle state should do nothing
  source->sampleParticleState( bank, 8 );
  
  TEST_EQUALITY_CONST( bank.size(), 0 );

  std::set<Geometry::ModuleTraits::InternalCellHandle> starting_cells;
  source->getStartingCells( starting_cells );

  TEST_EQUALITY_CONST( starting_cells.size(), 2 );
  TEST_ASSERT( starting_cells.count( 2 ) );
  TEST_ASSERT( starting_cells.count( 3 ) );
}

//---------------------------------------------------------------------------//
// Check that a particle state can be sampled from a source with rejection
// cells
TEUCHOS_UNIT_TEST( CachedStateParticleSource,
                   sampleParticleState_rejection_cells_larger )
{
  std::shared_ptr<MonteCarlo::ParticleSource> source;

  initializeSource( source );

  source->embedInModel( geometry_model );

  // Set the rejection cells
  source->setRejectionCell( 2 );
  source->setRejectionCell( 3 );

  MonteCarlo::ParticleBank bank;

  // Sample from the source
  source->sampleParticleState( bank, 0 );

  TEST_EQUALITY_CONST( bank.size(), 2 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 0ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );
  TEST_EQUALITY( bank.top().getSourceId(), source->getId() );
  TEST_EQUALITY_CONST( bank.top().getSourceCell(), 2 );
  TEST_EQUALITY_CONST( bank.top().getCell(), 2 );

  bank.pop();

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 0ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );
  TEST_EQUALITY( bank.top().getSourceId(), source->getId() );
  TEST_EQUALITY_CONST( bank.top().getSourceCell(), 3 );
  TEST_EQUALITY_CONST( bank.top().getCell(), 3 );

  bank.pop();

  // Sample from the source again
  source->sampleParticleState( bank, 1 );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 1ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::NEUTRON );
  TEST_EQUALITY( bank.top().getSourceId(), source->getId() );
  TEST_EQUALITY_CONST( bank.top().getSourceCell(), 2 );
  TEST_EQUALITY_CONST( bank.top().getCell(), 2 );

  bank.pop();

  // Sample from the source again
  source->sampleParticleState( bank, 2 );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 2ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::ELECTRON );
  TEST_EQUALITY( bank.top().getSourceId(), source->getId() );
  TEST_EQUALITY_CONST( bank.top().getSourceCell(), 2 );
  TEST_EQUALITY_CONST( bank.top().getCell(), 2 );

  bank.pop();

  // Sample from the source again
  source->sampleParticleState( bank, 3 );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 3ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::NEUTRON );
  TEST_EQUALITY( bank.top().getSourceId(), source->getId() );
  TEST_EQUALITY_CONST( bank.top().getSourceCell(), 2 );
  TEST_EQUALITY_CONST( bank.top().getCell(), 2 );

  bank.pop();

  // Sample from the source again
  source->sampleParticleState( bank, 4 );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 4ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );
  TEST_EQUALITY( bank.top().getSourceId(), source->getId() );
  TEST_EQUALITY_CONST( bank.top().getSourceCell(), 2 );
  TEST_EQUALITY_CONST( bank.top().getCell(), 2 );

  bank.pop();

  // Sample from the source again
  source->sampleParticleState( bank, 5 );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 5ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::ELECTRON );
  TEST_EQUALITY( bank.top().getSourceId(), source->getId() );
  TEST_EQUALITY_CONST( bank.top().getSourceCell(), 2 );
  TEST_EQUALITY_CONST( bank.top().getCell(), 2 );

  bank.pop();

  // Sample from the source again
  source->sampleParticleState( bank, 6 );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 6ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::NEUTRON );
  TEST_EQUALITY( bank.top().getSourceId(), source->getId() );
  TEST_EQUALITY_CONST( bank.top().getSourceCell(), 2 );
  TEST_EQUALITY_CONST( bank.top().getCell(), 2 );

  bank.pop();

  // Sample from the source again
  source->sampleParticleState( bank, 7 );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 7ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );
  TEST_EQUALITY( bank.top().getSourceId(), source->getId() );
  TEST_EQUALITY_CONST( bank.top().getSourceCell(), 2 );
  TEST_EQUALITY_CONST( bank.top().getCell(), 2 );

  bank.pop();

  // Attempting to get another particle state should do nothing
  source->sampleParticleState( bank, 8 );

  TEST_EQUALITY_CONST( bank.size(), 0 );

  std::set<Geometry::ModuleTraits::InternalCellHandle> starting_cells;
  source->getStartingCells( starting_cells );

  TEST_EQUALITY_CONST( starting_cells.size(), 2 );
  TEST_ASSERT( starting_cells.count( 2 ) );
  TEST_ASSERT( starting_cells.count( 3 ) );
}

//---------------------------------------------------------------------------//
// Check that a particle state can be sampled from a source with rejection
// cells
TEUCHOS_UNIT_TEST( CachedStateParticleSource,
                   sampleParticleState_rejection_cells_smaller )
{
  std::shared_ptr<MonteCarlo::ParticleSource> source;

  initializeSource( source );

  source->embedInModel( geometry_model );

  // Set the rejection cells
  source->setRejectionCell( 2 );

  MonteCarlo::ParticleBank bank;

  // Sample from the source
  source->sampleParticleState( bank, 0 );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 0ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );
  TEST_EQUALITY( bank.top().getSourceId(), source->getId() );
  TEST_EQUALITY_CONST( bank.top().getSourceCell(), 2 );
  TEST_EQUALITY_CONST( bank.top().getCell(), 2 );

  bank.pop();

  // Sample from the source again
  source->sampleParticleState( bank, 1 );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 1ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::NEUTRON );
  TEST_EQUALITY( bank.top().getSourceId(), source->getId() );
  TEST_EQUALITY_CONST( bank.top().getSourceCell(), 2 );
  TEST_EQUALITY_CONST( bank.top().getCell(), 2 );

  bank.pop();

  // Sample from the source again
  source->sampleParticleState( bank, 2 );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 2ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::ELECTRON );
  TEST_EQUALITY( bank.top().getSourceId(), source->getId() );
  TEST_EQUALITY_CONST( bank.top().getSourceCell(), 2 );
  TEST_EQUALITY_CONST( bank.top().getCell(), 2 );

  bank.pop();

  // Sample from the source again
  source->sampleParticleState( bank, 3 );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 3ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::NEUTRON );
  TEST_EQUALITY( bank.top().getSourceId(), source->getId() );
  TEST_EQUALITY_CONST( bank.top().getSourceCell(), 2 );
  TEST_EQUALITY_CONST( bank.top().getCell(), 2 );

  bank.pop();

  // Sample from the source again
  source->sampleParticleState( bank, 4 );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 4ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );
  TEST_EQUALITY( bank.top().getSourceId(), source->getId() );
  TEST_EQUALITY_CONST( bank.top().getSourceCell(), 2 );
  TEST_EQUALITY_CONST( bank.top().getCell(), 2 );

  bank.pop();

  // Sample from the source again
  source->sampleParticleState( bank, 5 );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 5ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::ELECTRON );
  TEST_EQUALITY( bank.top().getSourceId(), source->getId() );
  TEST_EQUALITY_CONST( bank.top().getSourceCell(), 2 );
  TEST_EQUALITY_CONST( bank.top().getCell(), 2 );

  bank.pop();

  // Sample from the source again
  source->sampleParticleState( bank, 6 );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 6ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::NEUTRON );
  TEST_EQUALITY( bank.top().getSourceId(), source->getId() );
  TEST_EQUALITY_CONST( bank.top().getSourceCell(), 2 );
  TEST_EQUALITY_CONST( bank.top().getCell(), 2 );

  bank.pop();

  // Sample from the source again
  source->sampleParticleState( bank, 7 );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 7ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );
  TEST_EQUALITY( bank.top().getSourceId(), source->getId() );
  TEST_EQUALITY_CONST( bank.top().getSourceCell(), 2 );
  TEST_EQUALITY_CONST( bank.top().getCell(), 2 );

  bank.pop();

  // Attempting to get another particle state should do nothing
  source->sampleParticleState( bank, 8 );

  TEST_EQUALITY_CONST( bank.size(), 0 );

  std::set<Geometry::ModuleTraits::InternalCellHandle> starting_cells;
  source->getStartingCells( starting_cells );

  TEST_EQUALITY_CONST( starting_cells.size(), 1 );
  TEST_ASSERT( starting_cells.count( 2 ) );
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
  // Initialize the geometry model
  Teuchos::RCP<const Teuchos::ParameterList> model_data =
    Teuchos::getParametersFromXmlFile( test_geom_xml_file_name );
  
  geometry_model = Geometry::ModelFactory::createModel( *model_data );
                                                       
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstEmbeddedCachedStateParticleSource.cpp
//---------------------------------------------------------------------------//
