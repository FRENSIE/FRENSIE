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

// Boost Includes
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/shared_ptr.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_ElectronState.hpp"

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
TEUCHOS_UNIT_TEST( ParticleBank, push )
{
  MonteCarlo::ParticleBank bank;

  TEST_ASSERT( bank.isEmpty() );
  TEST_EQUALITY_CONST( bank.size(), 0 );

  {
    MonteCarlo::PhotonState photon( 0ull );

    bank.push( photon );
  }

  TEST_ASSERT( !bank.isEmpty() );
  TEST_EQUALITY_CONST( bank.size(), 1 );

  {
    MonteCarlo::NeutronState neutron( 0ull );

    bank.push( neutron );
  }

  TEST_ASSERT( !bank.isEmpty() );
  TEST_EQUALITY_CONST( bank.size(), 2 );

  {
    MonteCarlo::NeutronState neutron( 1ull );

    bank.push( neutron, MonteCarlo::N__N_ELASTIC_REACTION );
  }

  TEST_ASSERT( !bank.isEmpty() );
  TEST_EQUALITY_CONST( bank.size(), 3 );

  {
    MonteCarlo::ElectronState electron( 2ull );

    bank.push( electron );
  }

  TEST_ASSERT( !bank.isEmpty() );
  TEST_EQUALITY_CONST( bank.size(), 4 );
}

//---------------------------------------------------------------------------//
// Check that particle smart pointers can be pushed to the bank
TEUCHOS_UNIT_TEST( ParticleBank, push_smart_ptr )
{
  MonteCarlo::ParticleBank bank;

  TEST_ASSERT( bank.isEmpty() );
  TEST_EQUALITY_CONST( bank.size(), 0 );

  {
    Teuchos::RCP<MonteCarlo::ParticleState> photon(
					 new MonteCarlo::PhotonState( 0ull ) );

    bank.push( photon );
  }

  TEST_ASSERT( !bank.isEmpty() );
  TEST_EQUALITY_CONST( bank.size(), 1 );

  {
    boost::shared_ptr<MonteCarlo::NeutronState> neutron(
					new MonteCarlo::NeutronState( 0ull ) );

    bank.push( neutron );
  }

  TEST_ASSERT( !bank.isEmpty() );
  TEST_EQUALITY_CONST( bank.size(), 2 );

  {
    std::shared_ptr<MonteCarlo::NeutronState> neutron(
					new MonteCarlo::NeutronState( 1ull ) );

    bank.push( neutron, MonteCarlo::N__N_ELASTIC_REACTION );
  }

  TEST_ASSERT( !bank.isEmpty() );
  TEST_EQUALITY_CONST( bank.size(), 3 );

  {
    std::shared_ptr<MonteCarlo::ElectronState> electron(
				       new MonteCarlo::ElectronState( 2ull ) );

    bank.push( electron );
  }

  TEST_ASSERT( !bank.isEmpty() );
  TEST_EQUALITY_CONST( bank.size(), 4 );
}

//---------------------------------------------------------------------------//
// Check that that the top element of the bank can be accessed
TEUCHOS_UNIT_TEST( ParticleBank, top )
{
  MonteCarlo::ParticleBank bank;

  MonteCarlo::PhotonState particle( 1ull );

  bank.push( particle );

  MonteCarlo::ParticleState& base_particle = particle;

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 1ull );

  const MonteCarlo::ParticleBank& const_bank = bank;

  TEST_EQUALITY( const_bank.top().getHistoryNumber(), 1ull );
}

//---------------------------------------------------------------------------//
// Check that particles can be removed from the bank
TEUCHOS_UNIT_TEST( ParticleBank, pop )
{
  MonteCarlo::ParticleBank bank;

  MonteCarlo::PhotonState particle( 0ull );

  bank.push( particle );

  TEST_ASSERT( !bank.isEmpty() );

  bank.pop();

  TEST_ASSERT( bank.isEmpty() );
}

//---------------------------------------------------------------------------//
// Check that the top particle can be removed from the bank and stored
TEUCHOS_UNIT_TEST( ParticleBank, pop_store )
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
  }

  TEST_EQUALITY_CONST( bank.size(), 3 );

  std::shared_ptr<MonteCarlo::ParticleState> particle_1;

  bank.pop( particle_1 );

  TEST_EQUALITY_CONST( particle_1->getHistoryNumber(), 0ull );
  TEST_EQUALITY_CONST( particle_1->getParticleType(), MonteCarlo::PHOTON );
  TEST_EQUALITY_CONST( bank.size(), 2 );

  boost::shared_ptr<MonteCarlo::ParticleState> particle_2;

  bank.pop( particle_2 );

  TEST_EQUALITY_CONST( particle_2->getHistoryNumber(), 1ull );
  TEST_EQUALITY_CONST( particle_2->getParticleType(), MonteCarlo::NEUTRON );
  TEST_EQUALITY_CONST( bank.size(), 1 );

  Teuchos::RCP<MonteCarlo::ParticleState> particle_3;

  bank.pop( particle_3 );

  TEST_EQUALITY_CONST( particle_3->getHistoryNumber(), 2ull );
  TEST_EQUALITY_CONST( particle_3->getParticleType(), MonteCarlo::ELECTRON );
  TEST_EQUALITY_CONST( bank.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the bank can be sorted
TEUCHOS_UNIT_TEST( ParticleBank, sort )
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
    MonteCarlo::ElectronState electron( 0ull );

    bank.push( electron );
  }

  TEST_ASSERT( !bank.isSorted( compareHistoryNumbers ) );

  bank.sort( compareHistoryNumbers );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 0ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::ELECTRON );

  bank.pop();

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 1ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );

  bank.pop();

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 2ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::NEUTRON );
}

//---------------------------------------------------------------------------//
// Check that banks can be merged
TEUCHOS_UNIT_TEST( ParticleBank, merge )
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

  bank_a.sort( compareHistoryNumbers );
  bank_b.sort( compareHistoryNumbers );

  bank_a.merge( bank_b, compareHistoryNumbers );

  TEST_ASSERT( bank_a.isSorted( compareHistoryNumbers ) );
  TEST_EQUALITY_CONST( bank_a.size(), 6 );
  TEST_EQUALITY_CONST( bank_b.size(), 0 );

  TEST_EQUALITY_CONST( bank_a.top().getHistoryNumber(), 0ull );
  TEST_EQUALITY_CONST( bank_a.top().getParticleType(),
		       MonteCarlo::ELECTRON );

  bank_a.pop();

  TEST_EQUALITY_CONST( bank_a.top().getHistoryNumber(), 1ull );
  TEST_EQUALITY_CONST( bank_a.top().getParticleType(),
		       MonteCarlo::NEUTRON );

  bank_a.pop();

  TEST_EQUALITY_CONST( bank_a.top().getHistoryNumber(), 2ull );
  TEST_EQUALITY_CONST( bank_a.top().getParticleType(),
		       MonteCarlo::PHOTON );

  bank_a.pop();

  TEST_EQUALITY_CONST( bank_a.top().getHistoryNumber(), 3ull );
  TEST_EQUALITY_CONST( bank_a.top().getParticleType(),
		       MonteCarlo::PHOTON );

  bank_a.pop();

  TEST_EQUALITY_CONST( bank_a.top().getHistoryNumber(), 4ull );
  TEST_EQUALITY_CONST( bank_a.top().getParticleType(),
		       MonteCarlo::NEUTRON );

  bank_a.pop();

  TEST_EQUALITY_CONST( bank_a.top().getHistoryNumber(), 5ull );
  TEST_EQUALITY_CONST( bank_a.top().getParticleType(),
		       MonteCarlo::ELECTRON );
}

//---------------------------------------------------------------------------//
// Check that banks can be spliced
TEUCHOS_UNIT_TEST( ParticleBank, splice )
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

  bank_a.splice( bank_b );

  TEST_EQUALITY_CONST( bank_a.size(), 6 );
  TEST_EQUALITY_CONST( bank_b.size(), 0 );

  TEST_EQUALITY_CONST( bank_a.top().getHistoryNumber(), 2ull );
  TEST_EQUALITY_CONST( bank_a.top().getParticleType(),
		       MonteCarlo::PHOTON );

  bank_a.pop();

  TEST_EQUALITY_CONST( bank_a.top().getHistoryNumber(), 4ull );
  TEST_EQUALITY_CONST( bank_a.top().getParticleType(),
		       MonteCarlo::NEUTRON );

  bank_a.pop();

  TEST_EQUALITY_CONST( bank_a.top().getHistoryNumber(), 0ull );
  TEST_EQUALITY_CONST( bank_a.top().getParticleType(),
		       MonteCarlo::ELECTRON );

  bank_a.pop();

  TEST_EQUALITY_CONST( bank_a.top().getHistoryNumber(), 3ull );
  TEST_EQUALITY_CONST( bank_a.top().getParticleType(),
		       MonteCarlo::PHOTON );

  bank_a.pop();

  TEST_EQUALITY_CONST( bank_a.top().getHistoryNumber(), 1ull );
  TEST_EQUALITY_CONST( bank_a.top().getParticleType(),
		       MonteCarlo::NEUTRON );

  bank_a.pop();

  TEST_EQUALITY_CONST( bank_a.top().getHistoryNumber(), 5ull );
  TEST_EQUALITY_CONST( bank_a.top().getParticleType(),
		       MonteCarlo::ELECTRON );
}

//---------------------------------------------------------------------------//
// Check that the bank can be archived
TEUCHOS_UNIT_TEST( ParticleBank, archive )
{
  // Create a bank, fill it with some particles and archive it
  {
    MonteCarlo::ParticleBank bank;

    MonteCarlo::PhotonState photon( 0ull );
    bank.push( photon );

    MonteCarlo::NeutronState neutron( 1ull );
    bank.push( neutron );

    MonteCarlo::ElectronState electron( 2ull );
    bank.push( electron );

    std::ofstream ofs( "test_particle_bank_archive.xml" );

    boost::archive::xml_oarchive ar(ofs);
    ar << BOOST_SERIALIZATION_NVP( bank );
  }

  // Load the archived bank
  MonteCarlo::ParticleBank loaded_bank;

  std::ifstream ifs( "test_particle_bank_archive.xml" );

  boost::archive::xml_iarchive ar(ifs);
  ar >> boost::serialization::make_nvp( "bank", loaded_bank );

  TEST_EQUALITY_CONST( loaded_bank.size(), 3 );
  TEST_EQUALITY_CONST( loaded_bank.top().getParticleType(),
                       MonteCarlo::PHOTON );

  loaded_bank.pop();

  TEST_EQUALITY_CONST( loaded_bank.top().getParticleType(),
                       MonteCarlo::NEUTRON );

  loaded_bank.pop();

  TEST_EQUALITY_CONST( loaded_bank.top().getParticleType(),
                       MonteCarlo::ELECTRON );
}

//---------------------------------------------------------------------------//
// end tstParticleBank.cpp
//---------------------------------------------------------------------------//
