//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointPhotonState.cpp
//! \author Alex Robinson
//! \brief  Adjoint photon state unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/shared_ptr.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotonState.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Get the particle type
TEUCHOS_UNIT_TEST( AdjointPhotonState, getParticleType )
{
  MonteCarlo::AdjointPhotonState particle( 1ull );

  TEST_EQUALITY_CONST( particle.getParticleType(),
		       MonteCarlo::ADJOINT_PHOTON );
}

//---------------------------------------------------------------------------//
// Get the particle speed
TEUCHOS_UNIT_TEST( AdjointPhotonState, getSpeed )
{
  MonteCarlo::AdjointPhotonState particle( 1ull );

  TEST_EQUALITY_CONST( particle.getSpeed(),
		       Utility::PhysicalConstants::speed_of_light );
}

//---------------------------------------------------------------------------//
// Advance the particle along its direction by a specified distance
TEUCHOS_UNIT_TEST( AdjointPhotonState, advance )
{
  const double position[3] = {1.0, 1.0, 1.0};
  const double direction[3] = {0.5773502691896258,
			       0.5773502691896258,
			       0.5773502691896258};

  MonteCarlo::AdjointPhotonState particle( 1ull );
  particle.setPosition( position );
  particle.setDirection( direction );
  particle.setEnergy( 1.0 );
  particle.setTime( 0.0 );

  particle.advance( 1.7320508075688772 );

  TEST_FLOATING_EQUALITY( particle.getXPosition(), 2.0, 1e-12 );
  TEST_FLOATING_EQUALITY( particle.getYPosition(), 2.0, 1e-12 );
  TEST_FLOATING_EQUALITY( particle.getZPosition(), 2.0, 1e-12 );
  TEST_FLOATING_EQUALITY( particle.getTime(), 5.7774996046392e-11, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check if the state is a probe
TEUCHOS_UNIT_TEST( AdjointPhotonState, isProbe )
{
  MonteCarlo::AdjointPhotonState particle( 1ull );

  TEST_ASSERT( !particle.isProbe() );
}

//---------------------------------------------------------------------------//
// Check that the state can be cloned
TEUCHOS_UNIT_TEST( AdjointPhotonState, clone )
{
  boost::shared_ptr<MonteCarlo::ParticleState> particle(
				  new MonteCarlo::AdjointPhotonState( 0ull ) );
  particle->setPosition( 1.0, 1.0, 1.0 );
  particle->setDirection( 0.0, 0.0, 1.0 );
  particle->setEnergy( 1.0 );
  particle->setTime( 0.5 );
  particle->setWeight( 0.25 );

  boost::shared_ptr<MonteCarlo::ParticleState> particle_clone(
							   particle->clone() );

  TEST_EQUALITY_CONST( particle_clone->getXPosition(), 1.0 );
  TEST_EQUALITY_CONST( particle_clone->getYPosition(), 1.0 );
  TEST_EQUALITY_CONST( particle_clone->getZPosition(), 1.0 );
  TEST_EQUALITY_CONST( particle_clone->getXDirection(), 0.0 );
  TEST_EQUALITY_CONST( particle_clone->getYDirection(), 0.0 );
  TEST_EQUALITY_CONST( particle_clone->getZDirection(), 1.0 );
  TEST_EQUALITY_CONST( particle_clone->getEnergy(), 1.0 );
  TEST_EQUALITY_CONST( particle_clone->getTime(), 0.5 );
  TEST_EQUALITY_CONST( particle_clone->getCollisionNumber(), 0 );
  TEST_EQUALITY_CONST( particle_clone->getGenerationNumber(), 0 );
  TEST_EQUALITY_CONST( particle_clone->getWeight(), 0.25 );
  TEST_EQUALITY_CONST( particle_clone->getHistoryNumber(), 0ull );
  TEST_EQUALITY_CONST( particle_clone->getParticleType(),
		       MonteCarlo::ADJOINT_PHOTON );
}

//---------------------------------------------------------------------------//
// Check that the state can be cloned with a new history number
TEUCHOS_UNIT_TEST( AdjointPhotonState, clone_new_hist )
{
  boost::shared_ptr<MonteCarlo::ParticleState> particle(
				  new MonteCarlo::AdjointPhotonState( 0ull ) );
  particle->setPosition( 1.0, 1.0, 1.0 );
  particle->setDirection( 0.0, 0.0, 1.0 );
  particle->setEnergy( 1.0 );
  particle->setTime( 0.5 );
  particle->setWeight( 0.25 );

  boost::shared_ptr<MonteCarlo::ParticleState> particle_clone(
						    particle->clone( 10ull ) );

  TEST_EQUALITY_CONST( particle_clone->getXPosition(), 1.0 );
  TEST_EQUALITY_CONST( particle_clone->getYPosition(), 1.0 );
  TEST_EQUALITY_CONST( particle_clone->getZPosition(), 1.0 );
  TEST_EQUALITY_CONST( particle_clone->getXDirection(), 0.0 );
  TEST_EQUALITY_CONST( particle_clone->getYDirection(), 0.0 );
  TEST_EQUALITY_CONST( particle_clone->getZDirection(), 1.0 );
  TEST_EQUALITY_CONST( particle_clone->getEnergy(), 1.0 );
  TEST_EQUALITY_CONST( particle_clone->getTime(), 0.5 );
  TEST_EQUALITY_CONST( particle_clone->getCollisionNumber(), 0 );
  TEST_EQUALITY_CONST( particle_clone->getGenerationNumber(), 0 );
  TEST_EQUALITY_CONST( particle_clone->getWeight(), 0.25 );
  TEST_EQUALITY_CONST( particle_clone->getHistoryNumber(), 10ull );
  TEST_EQUALITY_CONST( particle_clone->getParticleType(),
		       MonteCarlo::ADJOINT_PHOTON );
}

//---------------------------------------------------------------------------//
// Archive an adjoint photon state
TEUCHOS_UNIT_TEST( AdjointPhotonState, archive )
{
  // Create and archive an adjoint photon
  {
    MonteCarlo::AdjointPhotonState particle( 1ull );
    particle.setPosition( 1.0, 1.0, 1.0 );
    particle.setDirection( 0.0, 0.0, 1.0 );
    particle.setEnergy( 1.0 );
    particle.setTime( 0.5 );
    particle.incrementCollisionNumber();
    particle.setWeight( 0.25 );

    std::ofstream ofs( "test_adjoint_photon_state_archive.xml" );

    boost::archive::xml_oarchive ar(ofs);
    ar << BOOST_SERIALIZATION_NVP( particle );
  }

  // Load the archived particle
  MonteCarlo::AdjointPhotonState loaded_particle;

  std::ifstream ifs( "test_adjoint_photon_state_archive.xml" );

  boost::archive::xml_iarchive ar(ifs);
  ar >> boost::serialization::make_nvp( "particle", loaded_particle );

  TEST_EQUALITY_CONST( loaded_particle.getXPosition(), 1.0 );
  TEST_EQUALITY_CONST( loaded_particle.getYPosition(), 1.0 );
  TEST_EQUALITY_CONST( loaded_particle.getZPosition(), 1.0 );
  TEST_EQUALITY_CONST( loaded_particle.getXDirection(), 0.0 );
  TEST_EQUALITY_CONST( loaded_particle.getYDirection(), 0.0 );
  TEST_EQUALITY_CONST( loaded_particle.getZDirection(), 1.0 );
  TEST_EQUALITY_CONST( loaded_particle.getEnergy(), 1.0 );
  TEST_EQUALITY_CONST( loaded_particle.getTime(), 0.5 );
  TEST_EQUALITY_CONST( loaded_particle.getCollisionNumber(), 1.0 );
  TEST_EQUALITY_CONST( loaded_particle.getGenerationNumber(), 0.0 );
  TEST_EQUALITY_CONST( loaded_particle.getWeight(), 0.25 );
  TEST_EQUALITY_CONST( loaded_particle.getHistoryNumber(), 1ull );
  TEST_EQUALITY_CONST( loaded_particle.getParticleType(),
		       MonteCarlo::ADJOINT_PHOTON );
}

//---------------------------------------------------------------------------//
// Create new particles
TEUCHOS_UNIT_TEST( AdjointPhotonState, copy_constructor )
{
  MonteCarlo::AdjointPhotonState particle_gen_a( 1ull );
  particle_gen_a.setPosition( 1.0, 1.0, 1.0 );
  particle_gen_a.setPosition( 0.0, 0.0, 1.0 );
  particle_gen_a.setEnergy( 1.0 );
  particle_gen_a.setTime( 1.0 );
  particle_gen_a.incrementCollisionNumber();
  particle_gen_a.setWeight( 0.5 );

  MonteCarlo::AdjointPhotonState particle_gen_a_copy( particle_gen_a );

  TEST_EQUALITY( particle_gen_a_copy.getXPosition(),
		 particle_gen_a.getXPosition() );
  TEST_EQUALITY( particle_gen_a_copy.getYPosition(),
		 particle_gen_a.getYPosition() );
  TEST_EQUALITY( particle_gen_a_copy.getZPosition(),
		 particle_gen_a.getZPosition() );
  TEST_EQUALITY( particle_gen_a_copy.getXDirection(),
		 particle_gen_a.getXDirection() );
  TEST_EQUALITY( particle_gen_a_copy.getYDirection(),
		 particle_gen_a.getYDirection() );
  TEST_EQUALITY( particle_gen_a_copy.getZDirection(),
		 particle_gen_a.getZDirection() );
  TEST_EQUALITY( particle_gen_a_copy.getEnergy(),
		 particle_gen_a.getEnergy() );
  TEST_EQUALITY( particle_gen_a_copy.getSpeed(),
		 particle_gen_a.getSpeed() );
  TEST_EQUALITY( particle_gen_a_copy.getTime(),
		 particle_gen_a.getTime() );
  TEST_EQUALITY( particle_gen_a_copy.getCollisionNumber(),
		 particle_gen_a.getCollisionNumber() );
  TEST_EQUALITY( particle_gen_a_copy.getGenerationNumber(),
		 particle_gen_a.getGenerationNumber() );
  TEST_EQUALITY( particle_gen_a_copy.getWeight(),
		 particle_gen_a.getWeight() );
  TEST_ASSERT( !particle_gen_a_copy.isProbe() );
  TEST_ASSERT( !particle_gen_a.isProbe() );

  // Create a second generation particle with the same collision number
  MonteCarlo::AdjointPhotonState particle_gen_b( particle_gen_a, true );

  TEST_EQUALITY( particle_gen_b.getXPosition(),
		 particle_gen_a.getXPosition() );
  TEST_EQUALITY( particle_gen_b.getYPosition(),
		 particle_gen_a.getYPosition() );
  TEST_EQUALITY( particle_gen_b.getZPosition(),
		 particle_gen_a.getZPosition() );
  TEST_EQUALITY( particle_gen_b.getXDirection(),
		 particle_gen_a.getXDirection() );
  TEST_EQUALITY( particle_gen_b.getYDirection(),
		 particle_gen_a.getYDirection() );
  TEST_EQUALITY( particle_gen_b.getZDirection(),
		 particle_gen_a.getZDirection() );
  TEST_EQUALITY( particle_gen_b.getEnergy(),
		 particle_gen_a.getEnergy() );
  TEST_EQUALITY( particle_gen_b.getTime(),
		 particle_gen_a.getTime() );
  TEST_EQUALITY( particle_gen_b.getCollisionNumber(),
		 particle_gen_a.getCollisionNumber() );
  TEST_EQUALITY( particle_gen_b.getGenerationNumber(),
		 particle_gen_a.getGenerationNumber()+1u );
  TEST_EQUALITY( particle_gen_b.getWeight(),
		 particle_gen_a.getWeight() );
  TEST_ASSERT( !particle_gen_b.isProbe() );
  TEST_ASSERT( !particle_gen_a.isProbe() );

  // Create a third generation particle and reset the collision counter
  MonteCarlo::AdjointPhotonState particle_gen_c( particle_gen_b, true, true );

  TEST_EQUALITY( particle_gen_c.getXPosition(),
		 particle_gen_b.getXPosition() );
  TEST_EQUALITY( particle_gen_c.getYPosition(),
		 particle_gen_b.getYPosition() );
  TEST_EQUALITY( particle_gen_c.getZPosition(),
		 particle_gen_b.getZPosition() );
  TEST_EQUALITY( particle_gen_c.getXDirection(),
		 particle_gen_b.getXDirection() );
  TEST_EQUALITY( particle_gen_c.getYDirection(),
		 particle_gen_b.getYDirection() );
  TEST_EQUALITY( particle_gen_c.getZDirection(),
		 particle_gen_b.getZDirection() );
  TEST_EQUALITY( particle_gen_c.getEnergy(),
		 particle_gen_b.getEnergy() );
  TEST_EQUALITY( particle_gen_c.getTime(),
		 particle_gen_b.getTime() );
  TEST_EQUALITY_CONST( particle_gen_c.getCollisionNumber(), 0u );
  TEST_EQUALITY( particle_gen_c.getGenerationNumber(),
		 particle_gen_b.getGenerationNumber()+1u );
  TEST_EQUALITY( particle_gen_c.getWeight(),
		 particle_gen_b.getWeight() );
  TEST_ASSERT( !particle_gen_c.isProbe() );
  TEST_ASSERT( !particle_gen_b.isProbe() );
}

//---------------------------------------------------------------------------//
// end tstAdjointPhotonState.cpp
//---------------------------------------------------------------------------//
