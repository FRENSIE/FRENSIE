//---------------------------------------------------------------------------//
//!
//! \file   tstParticleBank.cpp
//! \author Alex Robinson
//! \brief  Particle bank unit test
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_PositronState.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types.
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Testing functions
//---------------------------------------------------------------------------//
bool compareHistoryNumbers( const MonteCarlo::ParticleState& state_a,
			    const MonteCarlo::ParticleState& state_b )
{
  return state_a.getHistoryNumber() < state_b.getHistoryNumber();
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that particles can be pushed to the particle bank
FRENSIE_UNIT_TEST( ParticleBank, push )
{
  MonteCarlo::ParticleBank bank;

  FRENSIE_CHECK( bank.isEmpty() );
  FRENSIE_CHECK_EQUAL( bank.size(), 0 );

  {
    MonteCarlo::PhotonState photon( 0ull );

    bank.push( photon );
  }

  FRENSIE_CHECK( !bank.isEmpty() );
  FRENSIE_CHECK_EQUAL( bank.size(), 1 );

  {
    MonteCarlo::NeutronState neutron( 0ull );

    bank.push( neutron );
  }

  FRENSIE_CHECK( !bank.isEmpty() );
  FRENSIE_CHECK_EQUAL( bank.size(), 2 );

  {
    MonteCarlo::NeutronState neutron( 1ull );

    bank.push( neutron, 0 );
  }

  FRENSIE_CHECK( !bank.isEmpty() );
  FRENSIE_CHECK_EQUAL( bank.size(), 3 );

  {
    MonteCarlo::ElectronState electron( 2ull );

    bank.push( electron );
  }

  FRENSIE_CHECK( !bank.isEmpty() );
  FRENSIE_CHECK_EQUAL( bank.size(), 4 );

  {
    MonteCarlo::PositronState positron( 3ull );

    bank.push( positron );
  }

  FRENSIE_CHECK( !bank.isEmpty() );
  FRENSIE_CHECK_EQUAL( bank.size(), 5 );
}

//---------------------------------------------------------------------------//
// Check that particle smart pointers can be pushed to the bank
FRENSIE_UNIT_TEST( ParticleBank, push_smart_ptr )
{
  MonteCarlo::ParticleBank bank;

  FRENSIE_CHECK( bank.isEmpty() );
  FRENSIE_CHECK_EQUAL( bank.size(), 0 );

  {
    std::shared_ptr<MonteCarlo::ParticleState> photon(
					 new MonteCarlo::PhotonState( 0ull ) );

    bank.push( photon );
  }

  FRENSIE_CHECK( !bank.isEmpty() );
  FRENSIE_CHECK_EQUAL( bank.size(), 1 );

  {
    boost::shared_ptr<MonteCarlo::NeutronState> neutron(
					new MonteCarlo::NeutronState( 0ull ) );

    bank.push( neutron );
  }

  FRENSIE_CHECK( !bank.isEmpty() );
  FRENSIE_CHECK_EQUAL( bank.size(), 2 );

  {
    std::shared_ptr<MonteCarlo::NeutronState> neutron(
					new MonteCarlo::NeutronState( 1ull ) );

    bank.push( neutron, 1 );
  }

  FRENSIE_CHECK( !bank.isEmpty() );
  FRENSIE_CHECK_EQUAL( bank.size(), 3 );

  {
    std::shared_ptr<MonteCarlo::ElectronState> electron(
					new MonteCarlo::ElectronState( 2ull ) );

    bank.push( electron );
  }

  FRENSIE_CHECK( !bank.isEmpty() );
  FRENSIE_CHECK_EQUAL( bank.size(), 4 );

  {
    std::shared_ptr<MonteCarlo::PositronState> positron(
					new MonteCarlo::PositronState( 2ull ) );

    bank.push( positron );
  }

  FRENSIE_CHECK( !bank.isEmpty() );
  FRENSIE_CHECK_EQUAL( bank.size(), 5 );
}

//---------------------------------------------------------------------------//
// Check that that the top element of the bank can be accessed
FRENSIE_UNIT_TEST( ParticleBank, top )
{
  MonteCarlo::ParticleBank bank;

  MonteCarlo::PhotonState particle( 1ull );

  bank.push( particle );

  MonteCarlo::ParticleState& base_particle = particle;

  FRENSIE_CHECK_EQUAL( bank.top().getHistoryNumber(), 1ull );

  const MonteCarlo::ParticleBank& const_bank = bank;

  FRENSIE_CHECK_EQUAL( const_bank.top().getHistoryNumber(), 1ull );
}

//---------------------------------------------------------------------------//
// Check that particles can be removed from the bank
FRENSIE_UNIT_TEST( ParticleBank, pop )
{
  MonteCarlo::ParticleBank bank;

  MonteCarlo::PhotonState particle( 0ull );

  bank.push( particle );

  FRENSIE_CHECK( !bank.isEmpty() );

  bank.pop();

  FRENSIE_CHECK( bank.isEmpty() );
}

//---------------------------------------------------------------------------//
// Check that the top particle can be removed from the bank and stored
FRENSIE_UNIT_TEST( ParticleBank, pop_store )
{
  MonteCarlo::ParticleBank bank;

  {
    std::shared_ptr<MonteCarlo::ParticleState> particle;

    particle.reset( new MonteCarlo::PhotonState( 0ull ) );

    bank.push( particle );

    particle.reset( new MonteCarlo::NeutronState( 1ull ) );

    bank.push( particle );

    particle.reset( new MonteCarlo::ElectronState( 2ull ) );

    bank.push( particle );

    particle.reset( new MonteCarlo::PositronState( 3ull ) );

    bank.push( particle );
  }

  FRENSIE_CHECK_EQUAL( bank.size(), 4 );

  std::shared_ptr<MonteCarlo::ParticleState> particle_1;

  bank.pop( particle_1 );

  FRENSIE_CHECK_EQUAL( particle_1->getHistoryNumber(), 0ull );
  FRENSIE_CHECK_EQUAL( particle_1->getParticleType(), MonteCarlo::PHOTON );
  FRENSIE_CHECK_EQUAL( bank.size(), 3 );

  boost::shared_ptr<MonteCarlo::ParticleState> particle_2;

  bank.pop( particle_2 );

  FRENSIE_CHECK_EQUAL( particle_2->getHistoryNumber(), 1ull );
  FRENSIE_CHECK_EQUAL( particle_2->getParticleType(), MonteCarlo::NEUTRON );
  FRENSIE_CHECK_EQUAL( bank.size(), 2 );

  std::shared_ptr<MonteCarlo::ParticleState> particle_3;

  bank.pop( particle_3 );

  FRENSIE_CHECK_EQUAL( particle_3->getHistoryNumber(), 2ull );
  FRENSIE_CHECK_EQUAL( particle_3->getParticleType(), MonteCarlo::ELECTRON );
  FRENSIE_CHECK_EQUAL( bank.size(), 1 );

  std::shared_ptr<MonteCarlo::ParticleState> particle_4;

  bank.pop( particle_4 );

  FRENSIE_CHECK_EQUAL( particle_4->getHistoryNumber(), 3ull );
  FRENSIE_CHECK_EQUAL( particle_4->getParticleType(), MonteCarlo::POSITRON );
  FRENSIE_CHECK_EQUAL( bank.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the bank can be sorted
FRENSIE_UNIT_TEST( ParticleBank, sort )
{
  MonteCarlo::ParticleBank bank;

  {
    MonteCarlo::PhotonState photon( 1ull );

    bank.push( photon );
  }

  {
    MonteCarlo::NeutronState neutron( 2ull );

    bank.push( neutron );
  }

  {
    MonteCarlo::ElectronState electron( 3ull );

    bank.push( electron );
  }

  {
    MonteCarlo::PositronState positron( 0ull );

    bank.push( positron );
  }

  FRENSIE_CHECK( !bank.isSorted( compareHistoryNumbers ) );

  bank.sort( compareHistoryNumbers );

  FRENSIE_CHECK_EQUAL( bank.top().getHistoryNumber(), 0ull );
  FRENSIE_CHECK_EQUAL( bank.top().getParticleType(), MonteCarlo::POSITRON );

  bank.pop();

  FRENSIE_CHECK_EQUAL( bank.top().getHistoryNumber(), 1ull );
  FRENSIE_CHECK_EQUAL( bank.top().getParticleType(), MonteCarlo::PHOTON );

  bank.pop();

  FRENSIE_CHECK_EQUAL( bank.top().getHistoryNumber(), 2ull );
  FRENSIE_CHECK_EQUAL( bank.top().getParticleType(), MonteCarlo::NEUTRON );

  bank.pop();

  FRENSIE_CHECK_EQUAL( bank.top().getHistoryNumber(), 3ull );
  FRENSIE_CHECK_EQUAL( bank.top().getParticleType(), MonteCarlo::ELECTRON );
}

//---------------------------------------------------------------------------//
// Check that banks can be merged
FRENSIE_UNIT_TEST( ParticleBank, merge )
{
  MonteCarlo::ParticleBank bank_a, bank_b;

  {
    MonteCarlo::PhotonState photon( 2ull );

    bank_a.push( photon );
  }

  {
    MonteCarlo::NeutronState neutron( 4ull );

    bank_a.push( neutron );
  }

  {
    MonteCarlo::ElectronState electron( 0ull );

    bank_a.push( electron );
  }

  {
    MonteCarlo::PositronState positron( 6ull );

    bank_a.push( positron );
  }

  {
    MonteCarlo::PhotonState photon( 3ull );

    bank_b.push( photon );
  }

  {
    MonteCarlo::NeutronState neutron( 1ull );

    bank_b.push( neutron );
  }

  {
    MonteCarlo::ElectronState electron( 5ull );

    bank_b.push( electron );
  }

  {
    MonteCarlo::PositronState positron( 7ull );

    bank_a.push( positron );
  }

  bank_a.sort( compareHistoryNumbers );
  bank_b.sort( compareHistoryNumbers );

  bank_a.merge( bank_b, compareHistoryNumbers );

  FRENSIE_CHECK( bank_a.isSorted( compareHistoryNumbers ) );
  FRENSIE_CHECK_EQUAL( bank_a.size(), 8 );
  FRENSIE_CHECK_EQUAL( bank_b.size(), 0 );

  FRENSIE_CHECK_EQUAL( bank_a.top().getHistoryNumber(), 0ull );
  FRENSIE_CHECK_EQUAL( bank_a.top().getParticleType(),
		       MonteCarlo::ELECTRON );

  bank_a.pop();

  FRENSIE_CHECK_EQUAL( bank_a.top().getHistoryNumber(), 1ull );
  FRENSIE_CHECK_EQUAL( bank_a.top().getParticleType(),
		       MonteCarlo::NEUTRON );

  bank_a.pop();

  FRENSIE_CHECK_EQUAL( bank_a.top().getHistoryNumber(), 2ull );
  FRENSIE_CHECK_EQUAL( bank_a.top().getParticleType(),
		       MonteCarlo::PHOTON );

  bank_a.pop();

  FRENSIE_CHECK_EQUAL( bank_a.top().getHistoryNumber(), 3ull );
  FRENSIE_CHECK_EQUAL( bank_a.top().getParticleType(),
		       MonteCarlo::PHOTON );

  bank_a.pop();

  FRENSIE_CHECK_EQUAL( bank_a.top().getHistoryNumber(), 4ull );
  FRENSIE_CHECK_EQUAL( bank_a.top().getParticleType(),
		       MonteCarlo::NEUTRON );

  bank_a.pop();

  FRENSIE_CHECK_EQUAL( bank_a.top().getHistoryNumber(), 5ull );
  FRENSIE_CHECK_EQUAL( bank_a.top().getParticleType(),
		       MonteCarlo::ELECTRON );

  bank_a.pop();

  FRENSIE_CHECK_EQUAL( bank_a.top().getHistoryNumber(), 6ull );
  FRENSIE_CHECK_EQUAL( bank_a.top().getParticleType(),
		       MonteCarlo::POSITRON );

  bank_a.pop();

  FRENSIE_CHECK_EQUAL( bank_a.top().getHistoryNumber(), 7ull );
  FRENSIE_CHECK_EQUAL( bank_a.top().getParticleType(),
		       MonteCarlo::POSITRON );
}

//---------------------------------------------------------------------------//
// Check that banks can be spliced
FRENSIE_UNIT_TEST( ParticleBank, splice )
{
  MonteCarlo::ParticleBank bank_a, bank_b;

  {
    MonteCarlo::PhotonState photon( 2ull );
    bank_a.push( photon );
  }

  {
    MonteCarlo::NeutronState neutron( 4ull );
    bank_a.push( neutron );
  }

  {
    MonteCarlo::ElectronState electron( 0ull );
    bank_a.push( electron );
  }

  {
    MonteCarlo::PositronState positron( 6ull );
    bank_a.push( positron );
  }

  {
    MonteCarlo::PhotonState photon( 3ull );
    bank_b.push( photon );
  }

  {
    MonteCarlo::NeutronState neutron( 1ull );
    bank_b.push( neutron );
  }

  {
    MonteCarlo::ElectronState electron( 5ull );
    bank_b.push( electron );
  }

  {
    MonteCarlo::PositronState positron( 7ull );
    bank_b.push( positron );
  }

  bank_a.splice( bank_b );

  FRENSIE_CHECK_EQUAL( bank_a.size(), 8 );
  FRENSIE_CHECK_EQUAL( bank_b.size(), 0 );

  FRENSIE_CHECK_EQUAL( bank_a.top().getHistoryNumber(), 2ull );
  FRENSIE_CHECK_EQUAL( bank_a.top().getParticleType(),
		       MonteCarlo::PHOTON );

  bank_a.pop();

  FRENSIE_CHECK_EQUAL( bank_a.top().getHistoryNumber(), 4ull );
  FRENSIE_CHECK_EQUAL( bank_a.top().getParticleType(),
		       MonteCarlo::NEUTRON );

  bank_a.pop();

  FRENSIE_CHECK_EQUAL( bank_a.top().getHistoryNumber(), 0ull );
  FRENSIE_CHECK_EQUAL( bank_a.top().getParticleType(),
		       MonteCarlo::ELECTRON );

  bank_a.pop();

  FRENSIE_CHECK_EQUAL( bank_a.top().getHistoryNumber(), 6ull );
  FRENSIE_CHECK_EQUAL( bank_a.top().getParticleType(),
		       MonteCarlo::POSITRON );

  bank_a.pop();

  FRENSIE_CHECK_EQUAL( bank_a.top().getHistoryNumber(), 3ull );
  FRENSIE_CHECK_EQUAL( bank_a.top().getParticleType(),
		       MonteCarlo::PHOTON );

  bank_a.pop();

  FRENSIE_CHECK_EQUAL( bank_a.top().getHistoryNumber(), 1ull );
  FRENSIE_CHECK_EQUAL( bank_a.top().getParticleType(),
		       MonteCarlo::NEUTRON );

  bank_a.pop();

  FRENSIE_CHECK_EQUAL( bank_a.top().getHistoryNumber(), 5ull );
  FRENSIE_CHECK_EQUAL( bank_a.top().getParticleType(),
		       MonteCarlo::ELECTRON );

  bank_a.pop();

  FRENSIE_CHECK_EQUAL( bank_a.top().getHistoryNumber(), 7ull );
  FRENSIE_CHECK_EQUAL( bank_a.top().getParticleType(),
		       MonteCarlo::POSITRON );
}

//---------------------------------------------------------------------------//
// Check that a particle bank can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( ParticleBank, archive, TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_particle_bank" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    MonteCarlo::ParticleBank bank;

    MonteCarlo::PhotonState photon( 0ull );
    bank.push( photon );

    MonteCarlo::NeutronState neutron( 1ull );
    bank.push( neutron );

    MonteCarlo::ElectronState electron( 2ull );
    bank.push( electron );

    MonteCarlo::PositronState positron( 3ull );
    bank.push( positron );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( bank ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  MonteCarlo::ParticleBank bank;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( bank ) );

  FRENSIE_CHECK_EQUAL( bank.size(), 4 );
  FRENSIE_CHECK_EQUAL( bank.top().getParticleType(),
                       MonteCarlo::PHOTON );

  bank.pop();

  FRENSIE_CHECK_EQUAL( bank.top().getParticleType(),
                       MonteCarlo::NEUTRON );

  bank.pop();

  FRENSIE_CHECK_EQUAL( bank.top().getParticleType(),
                       MonteCarlo::ELECTRON );

  bank.pop();

  FRENSIE_CHECK_EQUAL( bank.top().getParticleType(),
                       MonteCarlo::POSITRON );
}

//---------------------------------------------------------------------------//
// end tstParticleBank.cpp
//---------------------------------------------------------------------------//
