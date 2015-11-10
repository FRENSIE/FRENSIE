//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointPhotonProbeState.cpp
//! \author Alex Robinson
//! \brief  Adjoint photon probe state unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotonProbeState.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Get the particle type
TEUCHOS_UNIT_TEST( AdjointPhotonProbeState, getParticleType )
{
  MonteCarlo::AdjointPhotonProbeState particle( 1ull );

  TEST_EQUALITY_CONST( particle.getParticleType(), 
		       MonteCarlo::ADJOINT_PHOTON_PROBE );
}

//---------------------------------------------------------------------------//
// Get the particle speed
TEUCHOS_UNIT_TEST( AdjointPhotonProbeState, getSpeed )
{
  MonteCarlo::AdjointPhotonProbeState particle( 1ull );

  TEST_EQUALITY_CONST( particle.getSpeed(), 
		       Utility::PhysicalConstants::speed_of_light );
}

//---------------------------------------------------------------------------//
// Check that the adjoint photon probe can be activated
TEUCHOS_UNIT_TEST( AdjointPhotonProbeState, activate )
{
  MonteCarlo::AdjointPhotonProbeState particle( 1ull );

  TEST_ASSERT( !particle.isActive() );

  particle.activate();

  TEST_ASSERT( particle.isActive() );
}

//---------------------------------------------------------------------------//
// Check that the adjoint photon probe behaves correctly when its energy is set
TEUCHOS_UNIT_TEST( AdjointPhotonProbeState, setEnergy )
{
  MonteCarlo::AdjointPhotonProbeState particle_a( 1ull );

  particle_a.setEnergy( 0.1 );

  TEST_ASSERT( !particle_a.isActive() );
  TEST_ASSERT( !particle_a.isGone() );

  particle_a.activate();

  TEST_ASSERT( particle_a.isActive() );
  TEST_ASSERT( !particle_a.isGone() );
  
  particle_a.setEnergy( 1.0 );

  TEST_ASSERT( particle_a.isActive() );
  TEST_ASSERT( particle_a.isGone() );

  MonteCarlo::AdjointPhotonProbeState particle_b( particle_a, true );

  particle_b.setEnergy( 2.0 );

  TEST_ASSERT( !particle_b.isActive() );
  TEST_ASSERT( !particle_b.isGone() );

  particle_b.activate();

  TEST_ASSERT( particle_b.isActive() );
  TEST_ASSERT( !particle_b.isGone() );

  particle_b.setEnergy( 10.0 );

  TEST_ASSERT( particle_b.isActive() );
  TEST_ASSERT( particle_b.isGone() );
}

//---------------------------------------------------------------------------//
// Advance the particle along its direction by a specified distance
TEUCHOS_UNIT_TEST( AdjointPhotonProbeState, advance )
{
  const double position[3] = {1.0, 1.0, 1.0};
  const double direction[3] = {0.5773502691896258, 
			       0.5773502691896258,
			       0.5773502691896258};
  
  MonteCarlo::AdjointPhotonProbeState particle( 1ull );
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
// Check if the particle is a probe
TEUCHOS_UNIT_TEST( AdjointPhotonProbeState, isProbe )
{
  MonteCarlo::AdjointPhotonProbeState particle( 1ull );

  TEST_ASSERT( particle.isProbe() );
}

//---------------------------------------------------------------------------//
// Archive an adjoint photon probe state
TEUCHOS_UNIT_TEST( AdjointPhotonProbeState, archive )
{
  // Create and archive an adjoint photon probe
  {
    MonteCarlo::AdjointPhotonProbeState particle( 1ull );
    particle.setPosition( 1.0, 1.0, 1.0 );
    particle.setDirection( 0.0, 0.0, 1.0 );
    particle.setEnergy( 1.0 );
    particle.setTime( 0.5 );
    particle.incrementCollisionNumber();
    particle.setWeight( 0.25 );
    particle.activate();

    std::ofstream ofs( "test_adjoint_photon_probe_state_archive.xml" );

    boost::archive::xml_oarchive ar(ofs);
    ar << BOOST_SERIALIZATION_NVP( particle );
  }
  
  // Load the archived particle
  MonteCarlo::AdjointPhotonProbeState loaded_particle;

  std::ifstream ifs( "test_adjoint_photon_probe_state_archive.xml" );

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
  TEST_ASSERT( loaded_particle.isActive() );
  TEST_EQUALITY_CONST( loaded_particle.getParticleType(), 
		       MonteCarlo::ADJOINT_PHOTON_PROBE );
}

//---------------------------------------------------------------------------//
// Create new particles
TEUCHOS_UNIT_TEST( AdjointPhotonProbeState, copy_constructor )
{
  MonteCarlo::AdjointPhotonProbeState particle_gen_a( 1ull );
  particle_gen_a.setPosition( 1.0, 1.0, 1.0 );
  particle_gen_a.setPosition( 0.0, 0.0, 1.0 );
  particle_gen_a.setEnergy( 1.0 );
  particle_gen_a.setTime( 1.0 );
  particle_gen_a.incrementCollisionNumber();
  particle_gen_a.setWeight( 0.5 );

  MonteCarlo::AdjointPhotonProbeState particle_gen_a_copy( particle_gen_a );
  
  TEST_ASSERT( !particle_gen_a_copy.isActive() );
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
  TEST_ASSERT( !particle_gen_a_copy.isGone() );

  // Create a second generation particle with the same collision number
  MonteCarlo::AdjointPhotonProbeState particle_gen_b( particle_gen_a, true );

  TEST_ASSERT( !particle_gen_b.isActive() );
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
  TEST_ASSERT( !particle_gen_b.isGone() );

  // Create a third generation particle and reset the collision counter
  MonteCarlo::AdjointPhotonProbeState particle_gen_c( particle_gen_b, true, true );

  TEST_ASSERT( !particle_gen_c.isActive() );
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
  TEST_ASSERT( !particle_gen_c.isGone() );
}

//---------------------------------------------------------------------------//
// Check that a probe state can create a non-probe state (and vice versa)
TEUCHOS_UNIT_TEST( AdjointPhotonProbeState, probe_nonprobe_copy_constructor )
{
  MonteCarlo::AdjointPhotonState particle_gen_a( 1ull );
  particle_gen_a.setPosition( 1.0, 1.0, 1.0 );
  particle_gen_a.setPosition( 0.0, 0.0, 1.0 );
  particle_gen_a.setEnergy( 1.0 );
  particle_gen_a.setTime( 1.0 );
  particle_gen_a.incrementCollisionNumber();
  particle_gen_a.setWeight( 0.5 );

  MonteCarlo::AdjointPhotonProbeState probe_gen_a( particle_gen_a );

  TEST_ASSERT( !probe_gen_a.isActive() );
  TEST_EQUALITY( probe_gen_a.getXPosition(), 
		 particle_gen_a.getXPosition() );
  TEST_EQUALITY( probe_gen_a.getYPosition(), 
		 particle_gen_a.getYPosition() );
  TEST_EQUALITY( probe_gen_a.getZPosition(), 
		 particle_gen_a.getZPosition() );
  TEST_EQUALITY( probe_gen_a.getXDirection(), 
		 particle_gen_a.getXDirection() );
  TEST_EQUALITY( probe_gen_a.getYDirection(), 
		 particle_gen_a.getYDirection() );
  TEST_EQUALITY( probe_gen_a.getZDirection(), 
		 particle_gen_a.getZDirection() );
  TEST_EQUALITY( probe_gen_a.getEnergy(),
		 particle_gen_a.getEnergy() );
  TEST_EQUALITY( probe_gen_a.getSpeed(),
		 particle_gen_a.getSpeed() );
  TEST_EQUALITY( probe_gen_a.getTime(),
		 particle_gen_a.getTime() );
  TEST_EQUALITY( probe_gen_a.getCollisionNumber(),
		 particle_gen_a.getCollisionNumber() );
  TEST_EQUALITY( probe_gen_a.getGenerationNumber(),
		 particle_gen_a.getGenerationNumber() );
  TEST_EQUALITY( probe_gen_a.getWeight(),
		 particle_gen_a.getWeight() );
  TEST_ASSERT( !probe_gen_a.isGone() );
  TEST_ASSERT( probe_gen_a.isProbe() );
  TEST_ASSERT( !particle_gen_a.isProbe() );

  MonteCarlo::AdjointPhotonState particle_gen_b( probe_gen_a, true );
  TEST_EQUALITY( particle_gen_b.getXPosition(), 
		 probe_gen_a.getXPosition() );
  TEST_EQUALITY( particle_gen_b.getYPosition(), 
		 probe_gen_a.getYPosition() );
  TEST_EQUALITY( particle_gen_b.getZPosition(), 
		 probe_gen_a.getZPosition() );
  TEST_EQUALITY( particle_gen_b.getXDirection(), 
		 probe_gen_a.getXDirection() );
  TEST_EQUALITY( particle_gen_b.getYDirection(), 
		 probe_gen_a.getYDirection() );
  TEST_EQUALITY( particle_gen_b.getZDirection(), 
		 probe_gen_a.getZDirection() );
  TEST_EQUALITY( particle_gen_b.getEnergy(),
		 probe_gen_a.getEnergy() );
  TEST_EQUALITY( particle_gen_b.getTime(),
		 probe_gen_a.getTime() );
  TEST_EQUALITY( particle_gen_b.getCollisionNumber(),
		 probe_gen_a.getCollisionNumber() );
  TEST_EQUALITY( particle_gen_b.getGenerationNumber(),
		 probe_gen_a.getGenerationNumber()+1u );
  TEST_EQUALITY( particle_gen_b.getWeight(),
		 probe_gen_a.getWeight() );
  TEST_ASSERT( !particle_gen_b.isProbe() );
  TEST_ASSERT( probe_gen_a.isProbe() );
}

//---------------------------------------------------------------------------//
// end tstAdjointPhotonProbeState.cpp
//---------------------------------------------------------------------------//
