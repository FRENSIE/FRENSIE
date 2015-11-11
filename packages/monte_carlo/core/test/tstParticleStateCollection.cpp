//---------------------------------------------------------------------------//
//!
//! \file   tstParticleStateCollection.cpp
//! \author Alex Robinson
//! \brief  Particle state collection unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleStateCollection.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_ElectronState.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that particle state copies can be pushed into the collection
TEUCHOS_UNIT_TEST( ParticleStateCollection, push )
{
  MonteCarlo::ParticleStateCollection collection;

  TEST_ASSERT( collection.empty() );
  TEST_EQUALITY_CONST( collection.size(), 0 );

  MonteCarlo::ParticleState::pointerType particle( 
					 new MonteCarlo::PhotonState( 0ull ) );

  collection.push( particle );

  TEST_ASSERT( !collection.empty() );
  TEST_EQUALITY_CONST( collection.size(), 1 );

  // Make sure a copy of the state (and not the pointer) was made
  TEST_ASSERT( particle.unique() );
}

//---------------------------------------------------------------------------//
// Check that the top element of the collection can be accessed
TEUCHOS_UNIT_TEST( ParticleStateCollection, top )
{
  MonteCarlo::ParticleStateCollection collection;

  MonteCarlo::ParticleState::pointerType particle( 
					 new MonteCarlo::PhotonState( 0ull ) );

  collection.push( particle );
  
  TEST_ASSERT( particle != collection.top() );

  const MonteCarlo::ParticleStateCollection& const_collection = collection;

  TEST_ASSERT( particle != const_collection.top() );
}

//---------------------------------------------------------------------------//
// Check that particle states can be removed from the collection
TEUCHOS_UNIT_TEST( ParticleStateCollection, pop )
{
  MonteCarlo::ParticleStateCollection collection;

  MonteCarlo::ParticleState::pointerType particle( 
					 new MonteCarlo::PhotonState( 0ull ) );

  collection.push( particle );

  TEST_ASSERT( !collection.empty() );

  collection.pop();

  TEST_ASSERT( collection.empty() );
}

//---------------------------------------------------------------------------//
// Check that the collection can be sorted
TEUCHOS_UNIT_TEST( ParticleStateCollection, sort )
{
  MonteCarlo::ParticleStateCollection collection;

  {
    MonteCarlo::ParticleState::pointerType particle( 
					 new MonteCarlo::PhotonState( 1ull ) );

    collection.push( particle );
  }

  {
    MonteCarlo::ParticleState::pointerType particle(
					new MonteCarlo::NeutronState( 2ull ) );

    collection.push( particle );
  }

  {
    MonteCarlo::ParticleState::pointerType particle(
				       new MonteCarlo::ElectronState( 0ull ) );

    collection.push( particle );
  }

  TEST_ASSERT( !collection.isSorted() );
  
  collection.sort();
  
  TEST_EQUALITY_CONST( collection.top()->getHistoryNumber(), 0ull );
  TEST_EQUALITY_CONST( collection.top()->getParticleType(), 
		       MonteCarlo::ELECTRON );

  collection.pop();

  TEST_EQUALITY_CONST( collection.top()->getHistoryNumber(), 1ull );
  TEST_EQUALITY_CONST( collection.top()->getParticleType(),
		       MonteCarlo::PHOTON );

  collection.pop();

  TEST_EQUALITY_CONST( collection.top()->getHistoryNumber(), 2ull );
  TEST_EQUALITY_CONST( collection.top()->getParticleType(),
		       MonteCarlo::NEUTRON );
}

//---------------------------------------------------------------------------//
// Check that collections can be merged
TEUCHOS_UNIT_TEST( ParticleStateCollection, merge )
{
  MonteCarlo::ParticleStateCollection collection_a, collection_b;

  {
    MonteCarlo::ParticleState::pointerType particle( 
					 new MonteCarlo::PhotonState( 2ull ) );

    collection_a.push( particle );
  }

  {
    MonteCarlo::ParticleState::pointerType particle(
					new MonteCarlo::NeutronState( 4ull ) );

    collection_a.push( particle );
  }

  {
    MonteCarlo::ParticleState::pointerType particle(
				       new MonteCarlo::ElectronState( 0ull ) );

    collection_a.push( particle );
  }

  {
    MonteCarlo::ParticleState::pointerType particle( 
					 new MonteCarlo::PhotonState( 3ull ) );

    collection_b.push( particle );
  }

  {
    MonteCarlo::ParticleState::pointerType particle(
					new MonteCarlo::NeutronState( 1ull ) );

    collection_b.push( particle );
  }

  {
    MonteCarlo::ParticleState::pointerType particle(
				       new MonteCarlo::ElectronState( 5ull ) );

    collection_b.push( particle );
  }

  collection_a.sort();
  collection_b.sort();

  collection_a.merge( collection_b );

  TEST_EQUALITY_CONST( collection_a.size(), 6 );
  TEST_EQUALITY_CONST( collection_b.size(), 0 );
  
  TEST_EQUALITY_CONST( collection_a.top()->getHistoryNumber(), 0ull );
  TEST_EQUALITY_CONST( collection_a.top()->getParticleType(), 
		       MonteCarlo::ELECTRON );
  
  collection_a.pop();
  
  TEST_EQUALITY_CONST( collection_a.top()->getHistoryNumber(), 1ull );
  TEST_EQUALITY_CONST( collection_a.top()->getParticleType(),
		       MonteCarlo::NEUTRON );
  
  collection_a.pop();

  TEST_EQUALITY_CONST( collection_a.top()->getHistoryNumber(), 2ull );
  TEST_EQUALITY_CONST( collection_a.top()->getParticleType(),
		       MonteCarlo::PHOTON );

  collection_a.pop();

  TEST_EQUALITY_CONST( collection_a.top()->getHistoryNumber(), 3ull );
  TEST_EQUALITY_CONST( collection_a.top()->getParticleType(),
		       MonteCarlo::PHOTON );

  collection_a.pop();

  TEST_EQUALITY_CONST( collection_a.top()->getHistoryNumber(), 4ull );
  TEST_EQUALITY_CONST( collection_a.top()->getParticleType(),
		       MonteCarlo::NEUTRON );

  collection_a.pop();

  TEST_EQUALITY_CONST( collection_a.top()->getHistoryNumber(), 5ull );
  TEST_EQUALITY_CONST( collection_a.top()->getParticleType(),
		       MonteCarlo::ELECTRON );
}

//---------------------------------------------------------------------------//
// Check that the collection can be archived
TEUCHOS_UNIT_TEST( ParticleStateCollection, archive )
{
  // Create a collection, fill it with some particles and archive it
  {
    MonteCarlo::ParticleStateCollection collection;
  
    MonteCarlo::ParticleState::pointerType photon(
                                         new MonteCarlo::PhotonState( 0ull ) );

    collection.push( photon );
  
    MonteCarlo::ParticleState::pointerType neutron(
                                        new MonteCarlo::NeutronState( 1ull ) );
    collection.push( neutron );

    MonteCarlo::ParticleState::pointerType electron(
                                       new MonteCarlo::ElectronState( 2ull ) );
    
    collection.push( electron );

    std::ofstream ofs( "test_particle_collection_archive.xml" );
    
    boost::archive::xml_oarchive ar(ofs);
    ar << BOOST_SERIALIZATION_NVP( collection );
  }

  // Load the archived collection
  MonteCarlo::ParticleStateCollection loaded_collection;

  std::ifstream ifs( "test_particle_collection_archive.xml" );

  boost::archive::xml_iarchive ar(ifs);
  ar >> boost::serialization::make_nvp( "collection", loaded_collection );

  TEST_EQUALITY_CONST( loaded_collection.size(), 3 );
  TEST_EQUALITY_CONST( loaded_collection.top()->getParticleType(), 
                       MonteCarlo::PHOTON );
  
  loaded_collection.pop();

  TEST_EQUALITY_CONST( loaded_collection.top()->getParticleType(), 
                       MonteCarlo::NEUTRON );

  loaded_collection.pop();

  TEST_EQUALITY_CONST( loaded_collection.top()->getParticleType(), 
                       MonteCarlo::ELECTRON );
}

//---------------------------------------------------------------------------//
// end tstParticleStateCollection.cpp
//---------------------------------------------------------------------------//
