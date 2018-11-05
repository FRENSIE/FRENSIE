//---------------------------------------------------------------------------//
//!
//! \file   tstDefaultCollisionForcer.cpp
//! \author Alex Robinson
//! \brief  Default collision forcer unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_CollisionForcer.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the cells can be returned
FRENSIE_UNIT_TEST( DefaultCollisionForcer, getCells )
{
  std::shared_ptr<const MonteCarlo::CollisionForcer> collision_forcer =
    MonteCarlo::CollisionForcer::getDefault();

  std::set<MonteCarlo::CollisionForcer::CellIdType> cells;

  collision_forcer->getCells( MonteCarlo::PHOTON, cells );

  FRENSIE_CHECK( cells.empty() );

  collision_forcer->getCells( MonteCarlo::ELECTRON, cells );

  FRENSIE_CHECK( cells.empty() );

  collision_forcer->getCells( MonteCarlo::POSITRON, cells );

  FRENSIE_CHECK( cells.empty() );

  collision_forcer->getCells( MonteCarlo::NEUTRON, cells );

  FRENSIE_CHECK( cells.empty() ); 
}

//---------------------------------------------------------------------------//
// Check that the particle types can be returned
FRENSIE_UNIT_TEST( DefaultCollisionForcer, getParticleTypes )
{
  std::shared_ptr<const MonteCarlo::CollisionForcer> collision_forcer =
    MonteCarlo::CollisionForcer::getDefault();

  std::set<MonteCarlo::ParticleType> particle_types;

  collision_forcer->getParticleTypes( particle_types );

  FRENSIE_CHECK( particle_types.empty() );
}

//---------------------------------------------------------------------------//
// Check that the generation probability can be returned
FRENSIE_UNIT_TEST( DefaultCollisionForcer, getGenerationProbability )
{
  std::shared_ptr<const MonteCarlo::CollisionForcer> collision_forcer =
    MonteCarlo::CollisionForcer::getDefault();

  FRENSIE_CHECK_EQUAL( collision_forcer->getGenerationProbability( MonteCarlo::PHOTON ), 0.0 );
  FRENSIE_CHECK_EQUAL( collision_forcer->getGenerationProbability( MonteCarlo::ELECTRON ), 0.0 );
  FRENSIE_CHECK_EQUAL( collision_forcer->getGenerationProbability( MonteCarlo::POSITRON ), 0.0 );
  FRENSIE_CHECK_EQUAL( collision_forcer->getGenerationProbability( MonteCarlo::NEUTRON ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that a collision can be forced
FRENSIE_UNIT_TEST( DefaultCollisionForcer, forceCollision )
{
  std::shared_ptr<const MonteCarlo::CollisionForcer> collision_forcer =
    MonteCarlo::CollisionForcer::getDefault();

  MonteCarlo::CollisionForcer::SimulateParticleForOpticalPath simulate_method =
    [](MonteCarlo::ParticleState&, MonteCarlo::ParticleBank&, const double)
    {
      // This function should never be called
      throw std::runtime_error( "This method should never be called!" );
    };

  {
    MonteCarlo::PhotonState photon( 0 );
    photon.setEnergy( 1.0 );
    photon.setPosition( 0.0, 0.0, 0.0 );
    photon.setDirection( 0.0, 0.0, 1.0 );
    photon.setWeight( 1.0 );
    
    MonteCarlo::ParticleBank bank;

    FRENSIE_REQUIRE_NO_THROW( collision_forcer->forceCollision( 1, 1.0, simulate_method, photon, bank ) );

    FRENSIE_CHECK_EQUAL( photon.getWeight(), 1.0 );
    FRENSIE_CHECK_EQUAL( bank.size(), 0 );
  }

  {
    MonteCarlo::ElectronState electron( 0 );
    electron.setEnergy( 1.0 );
    electron.setPosition( 0.0, 0.0, 0.0 );
    electron.setDirection( 0.0, 0.0, 1.0 );
    electron.setWeight( 1.0 );
    
    MonteCarlo::ParticleBank bank;

    FRENSIE_REQUIRE_NO_THROW( collision_forcer->forceCollision( 1, 1.0, simulate_method, electron, bank ) );

    FRENSIE_CHECK_EQUAL( electron.getWeight(), 1.0 );
    FRENSIE_CHECK_EQUAL( bank.size(), 0 );
  }

  {
    MonteCarlo::PositronState positron( 0 );
    positron.setEnergy( 1.0 );
    positron.setPosition( 0.0, 0.0, 0.0 );
    positron.setDirection( 0.0, 0.0, 1.0 );
    positron.setWeight( 1.0 );
    
    MonteCarlo::ParticleBank bank;

    FRENSIE_REQUIRE_NO_THROW( collision_forcer->forceCollision( 1, 1.0, simulate_method, positron, bank ) );

    FRENSIE_CHECK_EQUAL( positron.getWeight(), 1.0 );
    FRENSIE_CHECK_EQUAL( bank.size(), 0 );
  }
  
  {
    MonteCarlo::NeutronState neutron( 0 );
    neutron.setEnergy( 1.0 );
    neutron.setPosition( 0.0, 0.0, 0.0 );
    neutron.setDirection( 0.0, 0.0, 1.0 );
    neutron.setWeight( 1.0 );
    
    MonteCarlo::ParticleBank bank;

    FRENSIE_REQUIRE_NO_THROW( collision_forcer->forceCollision( 1, 1.0, simulate_method, neutron, bank ) );

    FRENSIE_CHECK_EQUAL( neutron.getWeight(), 1.0 );
    FRENSIE_CHECK_EQUAL( bank.size(), 0 );
  }
}

//---------------------------------------------------------------------------//
// Check that a collision forcer can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( StandardCollisionForcer,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_default_collision_forcer" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<const MonteCarlo::CollisionForcer> collision_forcer =
      MonteCarlo::CollisionForcer::getDefault();

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(collision_forcer) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<const MonteCarlo::CollisionForcer> collision_forcer;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(collision_forcer) );

  iarchive.reset();

  std::set<MonteCarlo::CollisionForcer::CellIdType> cells;

  collision_forcer->getCells( MonteCarlo::PHOTON, cells );

  FRENSIE_CHECK( cells.empty() );

  collision_forcer->getCells( MonteCarlo::ELECTRON, cells );

  FRENSIE_CHECK( cells.empty() );

  collision_forcer->getCells( MonteCarlo::POSITRON, cells );

  FRENSIE_CHECK( cells.empty() );

  collision_forcer->getCells( MonteCarlo::NEUTRON, cells );

  FRENSIE_CHECK( cells.empty() );

  std::set<MonteCarlo::ParticleType> particle_types;

  collision_forcer->getParticleTypes( particle_types );

  FRENSIE_CHECK( particle_types.empty() );

  FRENSIE_CHECK_EQUAL( collision_forcer->getGenerationProbability( MonteCarlo::PHOTON ), 0.0 );
  FRENSIE_CHECK_EQUAL( collision_forcer->getGenerationProbability( MonteCarlo::ELECTRON ), 0.0 );
  FRENSIE_CHECK_EQUAL( collision_forcer->getGenerationProbability( MonteCarlo::POSITRON ), 0.0 );
  FRENSIE_CHECK_EQUAL( collision_forcer->getGenerationProbability( MonteCarlo::NEUTRON ), 0.0 );
}

//---------------------------------------------------------------------------//
// end tstDefaultCollisionForcer.cpp
//---------------------------------------------------------------------------//
