//---------------------------------------------------------------------------//
//!
//! \file   tstStandardCollisionForcer.cpp
//! \author Alex Robinson
//! \brief  Standard collision forcer unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_CollisionForcer.hpp"
#include "MonteCarlo_StandardCollisionForcer.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Geometry_InfiniteMediumModel.hpp"
#include "Data_ScatteringCenterPropertiesDatabase.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_OpenMPProperties.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

using boost::units::si::kelvin;
using boost::units::cgs::cubic_centimeter;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<const MonteCarlo::FilledGeometryModel> filled_model;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the forced collision cells can be set
FRENSIE_UNIT_TEST( StandardCollisionForcer,
                   setForcedCollisionCells_default )
{
  std::shared_ptr<MonteCarlo::StandardCollisionForcer>
    collision_forcer( new MonteCarlo::StandardCollisionForcer );

  std::shared_ptr<const MonteCarlo::CollisionForcer> base_collision_forcer =
    collision_forcer;

  std::vector<MonteCarlo::StandardCollisionForcer::CellIdType> cells( {1} );
  std::set<MonteCarlo::StandardCollisionForcer::CellIdType>
    cells_set( cells.begin(), cells.end() );

  FRENSIE_CHECK( !collision_forcer->hasForcedCollisionCells( MonteCarlo::PHOTON ) );
  FRENSIE_CHECK( !collision_forcer->isForcedCollisionCell( MonteCarlo::PHOTON, 1 ) );
  FRENSIE_CHECK( !base_collision_forcer->hasForcedCollisionCells<MonteCarlo::PhotonState>() );
  FRENSIE_CHECK( !base_collision_forcer->isForcedCollisionCell<MonteCarlo::PhotonState>( 1 ) );

  collision_forcer->setForcedCollisionCells( *filled_model,
                                             MonteCarlo::PHOTON,
                                             cells );

  std::set<MonteCarlo::StandardCollisionForcer::CellIdType> test_cells;

  collision_forcer->getCells( MonteCarlo::PHOTON, test_cells );

  FRENSIE_CHECK( collision_forcer->hasForcedCollisionCells( MonteCarlo::PHOTON ) );
  FRENSIE_CHECK( collision_forcer->isForcedCollisionCell( MonteCarlo::PHOTON, 1 ) );
  FRENSIE_CHECK( base_collision_forcer->hasForcedCollisionCells<MonteCarlo::PhotonState>() );
  FRENSIE_CHECK( base_collision_forcer->isForcedCollisionCell<MonteCarlo::PhotonState>( 1 ) );
  FRENSIE_CHECK_EQUAL( cells_set, test_cells );
  FRENSIE_CHECK_EQUAL( collision_forcer->getGenerationProbability( MonteCarlo::PHOTON ), 1.0 );

  test_cells.clear();

  FRENSIE_CHECK( !collision_forcer->hasForcedCollisionCells( MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK( !collision_forcer->isForcedCollisionCell( MonteCarlo::NEUTRON, 1 ) );
  FRENSIE_CHECK( !base_collision_forcer->hasForcedCollisionCells<MonteCarlo::NeutronState>() );
  FRENSIE_CHECK( !base_collision_forcer->isForcedCollisionCell<MonteCarlo::NeutronState>( 1 ) );

  collision_forcer->setForcedCollisionCells( *filled_model,
                                             MonteCarlo::NEUTRON,
                                             cells );

  collision_forcer->getCells( MonteCarlo::NEUTRON, test_cells );

  FRENSIE_CHECK( collision_forcer->hasForcedCollisionCells( MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK( collision_forcer->isForcedCollisionCell( MonteCarlo::NEUTRON, 1 ) );
  FRENSIE_CHECK( base_collision_forcer->hasForcedCollisionCells<MonteCarlo::NeutronState>() );
  FRENSIE_CHECK( base_collision_forcer->isForcedCollisionCell<MonteCarlo::NeutronState>( 1 ) );
  FRENSIE_CHECK_EQUAL( cells_set, test_cells );
  FRENSIE_CHECK_EQUAL( collision_forcer->getGenerationProbability( MonteCarlo::NEUTRON ), 1.0 );

  test_cells.clear();

  FRENSIE_CHECK( !collision_forcer->hasForcedCollisionCells( MonteCarlo::ELECTRON ) );
  FRENSIE_CHECK( !collision_forcer->isForcedCollisionCell( MonteCarlo::ELECTRON, 1 ) );
  FRENSIE_CHECK( !base_collision_forcer->hasForcedCollisionCells<MonteCarlo::ElectronState>() );
  FRENSIE_CHECK( !base_collision_forcer->isForcedCollisionCell<MonteCarlo::ElectronState>( 1 ) );

  collision_forcer->setForcedCollisionCells( *filled_model,
                                             MonteCarlo::ELECTRON,
                                             cells );

  collision_forcer->getCells( MonteCarlo::ELECTRON, test_cells );

  FRENSIE_CHECK( collision_forcer->hasForcedCollisionCells( MonteCarlo::ELECTRON ) );
  FRENSIE_CHECK( collision_forcer->isForcedCollisionCell( MonteCarlo::ELECTRON, 1 ) );
  FRENSIE_CHECK( base_collision_forcer->hasForcedCollisionCells<MonteCarlo::ElectronState>() );
  FRENSIE_CHECK( base_collision_forcer->isForcedCollisionCell<MonteCarlo::ElectronState>( 1 ) );
  FRENSIE_CHECK_EQUAL( cells_set, test_cells );
  FRENSIE_CHECK_EQUAL( collision_forcer->getGenerationProbability( MonteCarlo::ELECTRON ), 1.0 );

  test_cells.clear();

  FRENSIE_CHECK( !collision_forcer->hasForcedCollisionCells( MonteCarlo::POSITRON ) );
  FRENSIE_CHECK( !collision_forcer->isForcedCollisionCell( MonteCarlo::POSITRON, 1 ) );
  FRENSIE_CHECK( !base_collision_forcer->hasForcedCollisionCells<MonteCarlo::PositronState>() );
  FRENSIE_CHECK( !base_collision_forcer->isForcedCollisionCell<MonteCarlo::PositronState>( 1 ) );

  collision_forcer->setForcedCollisionCells( *filled_model,
                                             MonteCarlo::POSITRON,
                                             cells );

  collision_forcer->getCells( MonteCarlo::POSITRON, test_cells );

  FRENSIE_CHECK( collision_forcer->hasForcedCollisionCells( MonteCarlo::POSITRON ) );
  FRENSIE_CHECK( collision_forcer->isForcedCollisionCell( MonteCarlo::POSITRON, 1 ) );
  FRENSIE_CHECK( base_collision_forcer->hasForcedCollisionCells<MonteCarlo::PositronState>() );
  FRENSIE_CHECK( base_collision_forcer->isForcedCollisionCell<MonteCarlo::PositronState>( 1 ) );
  FRENSIE_CHECK_EQUAL( cells_set, test_cells );
  FRENSIE_CHECK_EQUAL( collision_forcer->getGenerationProbability( MonteCarlo::POSITRON ), 1.0 );

  test_cells.clear();

  std::set<MonteCarlo::ParticleType> particle_types;

  collision_forcer->getParticleTypes( particle_types );

  FRENSIE_REQUIRE_EQUAL( particle_types.size(), 4 );
  FRENSIE_CHECK( particle_types.count( MonteCarlo::PHOTON ) );
  FRENSIE_CHECK( particle_types.count( MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK( particle_types.count( MonteCarlo::ELECTRON ) );
  FRENSIE_CHECK( particle_types.count( MonteCarlo::POSITRON ) );
}

//---------------------------------------------------------------------------//
// Check that the forced collision cells can be set
FRENSIE_UNIT_TEST( StandardCollisionForcer,
                   setForcedCollisionCells )
{
  std::shared_ptr<MonteCarlo::StandardCollisionForcer>
    collision_forcer( new MonteCarlo::StandardCollisionForcer );

  std::vector<MonteCarlo::StandardCollisionForcer::CellIdType> cells( {1} );
  std::set<MonteCarlo::StandardCollisionForcer::CellIdType>
    cells_set( cells.begin(), cells.end() );

  collision_forcer->setForcedCollisionCells( *filled_model,
                                             MonteCarlo::PHOTON,
                                             cells,
                                             0.5 );

  std::set<MonteCarlo::StandardCollisionForcer::CellIdType> test_cells;

  collision_forcer->getCells( MonteCarlo::PHOTON, test_cells );

  FRENSIE_CHECK_EQUAL( cells_set, test_cells );
  FRENSIE_CHECK_EQUAL( collision_forcer->getGenerationProbability( MonteCarlo::PHOTON ), 0.5 );

  test_cells.clear();

  collision_forcer->setForcedCollisionCells( *filled_model,
                                             MonteCarlo::NEUTRON,
                                             cells,
                                             0.75 );

  collision_forcer->getCells( MonteCarlo::NEUTRON, test_cells );

  FRENSIE_CHECK_EQUAL( cells_set, test_cells );
  FRENSIE_CHECK_EQUAL( collision_forcer->getGenerationProbability( MonteCarlo::NEUTRON ), 0.75 );

  test_cells.clear();

  collision_forcer->setForcedCollisionCells( *filled_model,
                                             MonteCarlo::ELECTRON,
                                             cells,
                                             0.25 );

  collision_forcer->getCells( MonteCarlo::ELECTRON, test_cells );

  FRENSIE_CHECK_EQUAL( cells_set, test_cells );
  FRENSIE_CHECK_EQUAL( collision_forcer->getGenerationProbability( MonteCarlo::ELECTRON ), 0.25 );

  test_cells.clear();

  collision_forcer->setForcedCollisionCells( *filled_model,
                                             MonteCarlo::POSITRON,
                                             cells,
                                             1.0 );

  collision_forcer->getCells( MonteCarlo::POSITRON, test_cells );

  FRENSIE_CHECK_EQUAL( cells_set, test_cells );
  FRENSIE_CHECK_EQUAL( collision_forcer->getGenerationProbability( MonteCarlo::POSITRON ), 1.0 );

  test_cells.clear();

  std::set<MonteCarlo::ParticleType> particle_types;

  collision_forcer->getParticleTypes( particle_types );

  FRENSIE_REQUIRE_EQUAL( particle_types.size(), 4 );
  FRENSIE_CHECK( particle_types.count( MonteCarlo::PHOTON ) );
  FRENSIE_CHECK( particle_types.count( MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK( particle_types.count( MonteCarlo::ELECTRON ) );
  FRENSIE_CHECK( particle_types.count( MonteCarlo::POSITRON ) );
}

//---------------------------------------------------------------------------//
// Check that a collision can be forced
FRENSIE_UNIT_TEST( StandardCollisionForcer,
                   forceCollision )
{
  std::shared_ptr<MonteCarlo::StandardCollisionForcer>
    collision_forcer( new MonteCarlo::StandardCollisionForcer );

  std::set<MonteCarlo::StandardCollisionForcer::CellIdType> cells( {1} );

  collision_forcer->setForcedCollisionCells( *filled_model,
                                             MonteCarlo::PHOTON,
                                             cells,
                                             0.5 );

  collision_forcer->setForcedCollisionCells( *filled_model,
                                             MonteCarlo::NEUTRON,
                                             cells,
                                             0.75 );

  collision_forcer->setForcedCollisionCells( *filled_model,
                                             MonteCarlo::ELECTRON,
                                             cells,
                                             0.25 );

  collision_forcer->setForcedCollisionCells( *filled_model,
                                             MonteCarlo::POSITRON,
                                             cells,
                                             1.0 );

  MonteCarlo::CollisionForcer::SimulateParticleForOpticalPath simulate_method =
    [](MonteCarlo::ParticleState& particle, MonteCarlo::ParticleBank& bank, const double op_to_collision)
    {
      particle.navigator().advanceBySubstep( op_to_collision*boost::units::cgs::centimeter );
      std::shared_ptr<MonteCarlo::ParticleState> particle_clone( particle.clone() );
      bank.push( particle_clone );
    };

  {
    MonteCarlo::PhotonState photon( 0 );
    photon.setEnergy( 1.0 );
    photon.setPosition( 0.0, 0.0, 0.0 );
    photon.setDirection( 0.0, 0.0, 1.0 );
    photon.setWeight( 1.0 );
    photon.embedInModel( *filled_model );

    MonteCarlo::ParticleBank bank;

    std::vector<double> fake_stream( 2 );
    fake_stream[0] = 0.499; // generate a forced collision particle
    fake_stream[1] = 0.25; // distance to forced collision site

    Utility::RandomNumberGenerator::setFakeStream( fake_stream );

    collision_forcer->forceCollision( 1, 1.0, simulate_method, photon, bank );

    FRENSIE_CHECK_EQUAL( photon.getXPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( photon.getYPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( photon.getZPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( photon.getXDirection(), 0.0 );
    FRENSIE_CHECK_EQUAL( photon.getYDirection(), 0.0 );
    FRENSIE_CHECK_EQUAL( photon.getZDirection(), 1.0 );
    FRENSIE_CHECK_EQUAL( photon.getWeight(), std::exp(-1.0) );

    FRENSIE_REQUIRE_EQUAL( bank.size(), 2 );
    FRENSIE_CHECK_EQUAL( bank.top().getXPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getYPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getZPosition(),
                         -std::log(1.0-0.25*(1.0-std::exp(-1.0))) );
    FRENSIE_CHECK_EQUAL( bank.top().getXDirection(), 0.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getYDirection(), 0.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getZDirection(), 1.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getWeight(), (1.0 - std::exp(-1.0))/0.5 );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::PhotonState photon( 0 );
    photon.setEnergy( 1.0 );
    photon.setPosition( 0.0, 0.0, 0.0 );
    photon.setDirection( 0.0, 0.0, 1.0 );
    photon.setWeight( 1.0 );
    photon.embedInModel( *filled_model );

    MonteCarlo::ParticleBank bank;

    std::vector<double> fake_stream( 1 );
    fake_stream[0] = 0.51; // no forced collision particle will be generated

    Utility::RandomNumberGenerator::setFakeStream( fake_stream );

    collision_forcer->forceCollision( 1, 1.5, simulate_method, photon, bank );

    FRENSIE_CHECK_EQUAL( photon.getXPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( photon.getYPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( photon.getZPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( photon.getXDirection(), 0.0 );
    FRENSIE_CHECK_EQUAL( photon.getYDirection(), 0.0 );
    FRENSIE_CHECK_EQUAL( photon.getZDirection(), 1.0 );
    FRENSIE_CHECK_EQUAL( photon.getWeight(), std::exp(-1.5) );

    FRENSIE_REQUIRE_EQUAL( bank.size(), 0 );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::NeutronState neutron( 0 );
    neutron.setEnergy( 1.0 );
    neutron.setPosition( 0.0, 0.0, 0.0 );
    neutron.setDirection( 0.0, 0.0, 1.0 );
    neutron.setWeight( 1.0 );
    neutron.embedInModel( *filled_model );

    MonteCarlo::ParticleBank bank;

    std::vector<double> fake_stream( 2 );
    fake_stream[0] = 0.749; // generate a forced collision particle
    fake_stream[1] = 0.5; // distance to forced collision site

    Utility::RandomNumberGenerator::setFakeStream( fake_stream );

    collision_forcer->forceCollision( 1, 2.0, simulate_method, neutron, bank );

    FRENSIE_CHECK_EQUAL( neutron.getXPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( neutron.getYPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( neutron.getZPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( neutron.getXDirection(), 0.0 );
    FRENSIE_CHECK_EQUAL( neutron.getYDirection(), 0.0 );
    FRENSIE_CHECK_EQUAL( neutron.getZDirection(), 1.0 );
    FRENSIE_CHECK_EQUAL( neutron.getWeight(), std::exp(-2.0) );

    FRENSIE_REQUIRE_EQUAL( bank.size(), 2 );
    FRENSIE_CHECK_EQUAL( bank.top().getXPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getYPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getZPosition(),
                         -std::log(1.0-0.5*(1.0-std::exp(-2.0))) );
    FRENSIE_CHECK_EQUAL( bank.top().getXDirection(), 0.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getYDirection(), 0.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getZDirection(), 1.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getWeight(), (1.0 - std::exp(-2.0))/0.75 );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::NeutronState neutron( 0 );
    neutron.setEnergy( 1.0 );
    neutron.setPosition( 0.0, 0.0, 0.0 );
    neutron.setDirection( 0.0, 0.0, 1.0 );
    neutron.setWeight( 1.0 );
    neutron.embedInModel( *filled_model );

    MonteCarlo::ParticleBank bank;

    std::vector<double> fake_stream( 2 );
    fake_stream[0] = 0.751; // do not generate a forced collision particle
    fake_stream[1] = 0.5;

    Utility::RandomNumberGenerator::setFakeStream( fake_stream );

    collision_forcer->forceCollision( 1, 2.0, simulate_method, neutron, bank );

    FRENSIE_CHECK_EQUAL( neutron.getXPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( neutron.getYPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( neutron.getZPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( neutron.getXDirection(), 0.0 );
    FRENSIE_CHECK_EQUAL( neutron.getYDirection(), 0.0 );
    FRENSIE_CHECK_EQUAL( neutron.getZDirection(), 1.0 );
    FRENSIE_CHECK_EQUAL( neutron.getWeight(), std::exp(-2.0) );

    FRENSIE_REQUIRE_EQUAL( bank.size(), 0 );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::ElectronState electron( 0 );
    electron.setEnergy( 1.0 );
    electron.setPosition( 0.0, 0.0, 0.0 );
    electron.setDirection( 0.0, 0.0, 1.0 );
    electron.setWeight( 1.0 );
    electron.embedInModel( *filled_model );

    MonteCarlo::ParticleBank bank;

    std::vector<double> fake_stream( 2 );
    fake_stream[0] = 0.249; // generate a forced collision particle
    fake_stream[1] = 0.75; // distance to forced collision site

    Utility::RandomNumberGenerator::setFakeStream( fake_stream );

    collision_forcer->forceCollision( 1, 0.5, simulate_method, electron, bank );

    FRENSIE_CHECK_EQUAL( electron.getXPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( electron.getYPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( electron.getZPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( electron.getXDirection(), 0.0 );
    FRENSIE_CHECK_EQUAL( electron.getYDirection(), 0.0 );
    FRENSIE_CHECK_EQUAL( electron.getZDirection(), 1.0 );
    FRENSIE_CHECK_EQUAL( electron.getWeight(), std::exp(-0.5) );

    FRENSIE_REQUIRE_EQUAL( bank.size(), 2 );
    FRENSIE_CHECK_EQUAL( bank.top().getXPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getYPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getZPosition(),
                         -std::log(1.0-0.75*(1.0-std::exp(-0.5))) );
    FRENSIE_CHECK_EQUAL( bank.top().getXDirection(), 0.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getYDirection(), 0.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getZDirection(), 1.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getWeight(), (1.0 - std::exp(-0.5))/0.25 );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::ElectronState electron( 0 );
    electron.setEnergy( 1.0 );
    electron.setPosition( 0.0, 0.0, 0.0 );
    electron.setDirection( 0.0, 0.0, 1.0 );
    electron.setWeight( 1.0 );
    electron.embedInModel( *filled_model );

    MonteCarlo::ParticleBank bank;

    std::vector<double> fake_stream( 2 );
    fake_stream[0] = 0.251; // do not generate a forced collision particle
    fake_stream[1] = 0.75;

    Utility::RandomNumberGenerator::setFakeStream( fake_stream );

    collision_forcer->forceCollision( 1, 0.5, simulate_method, electron, bank );

    FRENSIE_CHECK_EQUAL( electron.getXPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( electron.getYPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( electron.getZPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( electron.getXDirection(), 0.0 );
    FRENSIE_CHECK_EQUAL( electron.getYDirection(), 0.0 );
    FRENSIE_CHECK_EQUAL( electron.getZDirection(), 1.0 );
    FRENSIE_CHECK_EQUAL( electron.getWeight(), std::exp(-0.5) );

    FRENSIE_REQUIRE_EQUAL( bank.size(), 0 );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::PositronState positron( 0 );
    positron.setEnergy( 1.0 );
    positron.setPosition( 0.0, 0.0, 0.0 );
    positron.setDirection( 0.0, 0.0, 1.0 );
    positron.setWeight( 1.0 );
    positron.embedInModel( *filled_model );

    MonteCarlo::ParticleBank bank;

    std::vector<double> fake_stream( 2 );
    fake_stream[0] = 0.99; // generate a forced collision particle
    fake_stream[1] = 0.9; // distance to forced collision site

    Utility::RandomNumberGenerator::setFakeStream( fake_stream );

    collision_forcer->forceCollision( 1, 0.25, simulate_method, positron, bank );

    FRENSIE_CHECK_EQUAL( positron.getXPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( positron.getYPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( positron.getZPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( positron.getXDirection(), 0.0 );
    FRENSIE_CHECK_EQUAL( positron.getYDirection(), 0.0 );
    FRENSIE_CHECK_EQUAL( positron.getZDirection(), 1.0 );
    FRENSIE_CHECK_EQUAL( positron.getWeight(), std::exp(-0.25) );

    FRENSIE_REQUIRE_EQUAL( bank.size(), 2 );
    FRENSIE_CHECK_EQUAL( bank.top().getXPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getYPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getZPosition(),
                         -std::log(1.0-0.9*(1.0-std::exp(-0.25))) );
    FRENSIE_CHECK_EQUAL( bank.top().getXDirection(), 0.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getYDirection(), 0.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getZDirection(), 1.0 );
    FRENSIE_CHECK_EQUAL( bank.top().getWeight(), (1.0 - std::exp(-0.25)) );

    Utility::RandomNumberGenerator::unsetFakeStream();
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

  std::string archive_base_name( "test_standard_collision_forcer" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<const MonteCarlo::StandardCollisionForcer>
      collision_forcer;

    {
      std::shared_ptr<MonteCarlo::StandardCollisionForcer>
        tmp_collision_forcer( new MonteCarlo::StandardCollisionForcer );

      std::set<MonteCarlo::StandardCollisionForcer::CellIdType> cells( {1} );

      tmp_collision_forcer->setForcedCollisionCells( *filled_model,
                                                     MonteCarlo::PHOTON,
                                                     cells,
                                                     0.5 );

      tmp_collision_forcer->setForcedCollisionCells( *filled_model,
                                                     MonteCarlo::NEUTRON,
                                                     cells,
                                                     0.75 );

      tmp_collision_forcer->setForcedCollisionCells( *filled_model,
                                                     MonteCarlo::ELECTRON,
                                                     cells,
                                                     0.25 );

      tmp_collision_forcer->setForcedCollisionCells( *filled_model,
                                                     MonteCarlo::POSITRON,
                                                     cells,
                                                     1.0 );

      collision_forcer = tmp_collision_forcer;
    }

    std::shared_ptr<const MonteCarlo::CollisionForcer> base_collision_forcer =
      collision_forcer;

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(base_collision_forcer) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(collision_forcer) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<const MonteCarlo::CollisionForcer> base_collision_forcer;
  std::shared_ptr<const MonteCarlo::StandardCollisionForcer> collision_forcer;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(base_collision_forcer) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(collision_forcer) );

  iarchive.reset();

  FRENSIE_CHECK( collision_forcer.get() == base_collision_forcer.get() );

  {
    std::set<MonteCarlo::StandardCollisionForcer::CellIdType> cells( {1} );
    std::set<MonteCarlo::StandardCollisionForcer::CellIdType> test_cells;

    base_collision_forcer->getCells( MonteCarlo::PHOTON, test_cells );

    FRENSIE_CHECK_EQUAL( cells, test_cells );
    FRENSIE_CHECK_EQUAL( base_collision_forcer->getGenerationProbability( MonteCarlo::PHOTON ), 0.5 );

    test_cells.clear();

    base_collision_forcer->getCells( MonteCarlo::NEUTRON, test_cells );

    FRENSIE_CHECK_EQUAL( cells, test_cells );
    FRENSIE_CHECK_EQUAL( base_collision_forcer->getGenerationProbability( MonteCarlo::NEUTRON ), 0.75 );

    test_cells.clear();

    base_collision_forcer->getCells( MonteCarlo::ELECTRON, test_cells );

    FRENSIE_CHECK_EQUAL( cells, test_cells );
    FRENSIE_CHECK_EQUAL( base_collision_forcer->getGenerationProbability( MonteCarlo::ELECTRON ), 0.25 );

    test_cells.clear();

    base_collision_forcer->getCells( MonteCarlo::POSITRON, test_cells );

    FRENSIE_CHECK_EQUAL( cells, test_cells );
    FRENSIE_CHECK_EQUAL( base_collision_forcer->getGenerationProbability( MonteCarlo::POSITRON ), 1.0 );

    std::set<MonteCarlo::ParticleType> particle_types;

    base_collision_forcer->getParticleTypes( particle_types );

    FRENSIE_REQUIRE_EQUAL( particle_types.size(), 4 );
    FRENSIE_CHECK( particle_types.count( MonteCarlo::PHOTON ) );
    FRENSIE_CHECK( particle_types.count( MonteCarlo::NEUTRON ) );
    FRENSIE_CHECK( particle_types.count( MonteCarlo::ELECTRON ) );
    FRENSIE_CHECK( particle_types.count( MonteCarlo::POSITRON ) );
  }
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_scattering_center_database_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_database",
                                        test_scattering_center_database_name, "",
                                        "Test scattering center database name "
                                        "with path" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Determine the database directory
  boost::filesystem::path database_path =
    test_scattering_center_database_name;

  // Load the database
  const Data::ScatteringCenterPropertiesDatabase database( database_path );

  const Data::AtomProperties& h_properties =
    database.getAtomProperties( 1001 );

  const Data::NuclideProperties& h1_properties =
    database.getNuclideProperties( 1001 );

  // Set the sattering center definitions
  std::shared_ptr<MonteCarlo::ScatteringCenterDefinitionDatabase>
    scattering_center_definition_database(
                          new MonteCarlo::ScatteringCenterDefinitionDatabase );

  MonteCarlo::ScatteringCenterDefinition& h_definition =
    scattering_center_definition_database->createDefinition( "H1 @ 293.6K", 1001 );

  h_definition.setPhotoatomicDataProperties(
          h_properties.getSharedPhotoatomicDataProperties(
                Data::PhotoatomicDataProperties::Native_EPR_FILE, 0 ) );

  h_definition.setElectroatomicDataProperties(
          h_properties.getSharedElectroatomicDataProperties(
              Data::ElectroatomicDataProperties::Native_EPR_FILE, 0 ) );

  h_definition.setNuclearDataProperties(
          h1_properties.getSharedNuclearDataProperties(
             Data::NuclearDataProperties::ACE_FILE, 7, 293.6*kelvin, false ) );

  // Set the material definitions
  std::shared_ptr<MonteCarlo::MaterialDefinitionDatabase>
    material_definition_database( new MonteCarlo::MaterialDefinitionDatabase );

  material_definition_database->addDefinition( "H1 @ 293.6K", 2,
                                               {"H1 @ 293.6K"}, {1.0} );

  // Create the unfilled model
  std::shared_ptr<const Geometry::Model> unfilled_model(
             new Geometry::InfiniteMediumModel( 1, 2, 1e24/cubic_centimeter ) );
  std::shared_ptr<MonteCarlo::SimulationProperties>
    properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE );

  filled_model.reset( new MonteCarlo::FilledGeometryModel(
                                         database_path,
                                         scattering_center_definition_database,
                                         material_definition_database,
                                         properties,
                                         unfilled_model,
                                         true ) );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstStandardCollisionForcer.cpp
//---------------------------------------------------------------------------//
