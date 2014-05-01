//---------------------------------------------------------------------------//
//!
//! \file   tstNeutronState.cpp
//! \author Alex Robinson
//! \brief  Neutron state unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FACEMC Includes
#include "NeutronState.hpp"
#include "PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Get the particle type
TEUCHOS_UNIT_TEST( NeutronState, getParticleType )
{
  FACEMC::NeutronState particle( 1ull );

  TEST_EQUALITY_CONST( particle.getParticleType(), FACEMC::NEUTRON );
}

//---------------------------------------------------------------------------//
// Get the particle speed
TEUCHOS_UNIT_TEST( NeutronState, getSpeed )
{
  FACEMC::NeutronState particle( 1ull );

  particle.setEnergy( 1.0 );
  
  TEST_FLOATING_EQUALITY( particle.getSpeed(), 31907549.506739, 1e-13 );
}

//---------------------------------------------------------------------------//
// Set the particle speed
TEUCHOS_UNIT_TEST( NeutronState, setSpeed )
{
  FACEMC::NeutronState particle( 1ull );

  particle.setSpeed( 31907549.506739 );

  TEST_FLOATING_EQUALITY( particle.getEnergy(), 1.0, 1e-13 );
}

//---------------------------------------------------------------------------//
// Advance the particle along its direction by a specified distance
TEUCHOS_UNIT_TEST( NeutronState, advance )
{
  const double position[3] = {1.0, 1.0, 1.0};
  const double direction[3] = {0.5773502691896258, 
			       0.5773502691896258,
			       0.5773502691896258};
  
  FACEMC::NeutronState particle( 1ull );
  particle.setPosition( position );
  particle.setDirection( direction );
  particle.setEnergy( 1.0 );
  particle.setTime( 0.0 );

  particle.advance( 1.7320508075688772 );

  TEST_FLOATING_EQUALITY( particle.getXPosition(), 2.0, 1e-12 );
  TEST_FLOATING_EQUALITY( particle.getYPosition(), 2.0, 1e-12 );
  TEST_FLOATING_EQUALITY( particle.getZPosition(), 2.0, 1e-12 );
  TEST_FLOATING_EQUALITY( particle.getTime(), 5.4283416756994e-8, 1e-12 );
}

//---------------------------------------------------------------------------//
// Create new particles
TEUCHOS_UNIT_TEST( NeutronState, copy_constructor )
{
  FACEMC::NeutronState particle_gen_a( 1ull );
  particle_gen_a.setPosition( 1.0, 1.0, 1.0 );
  particle_gen_a.setPosition( 0.0, 0.0, 1.0 );
  particle_gen_a.setEnergy( 1.0 );
  particle_gen_a.setTime( 1.0 );
  particle_gen_a.incrementCollisionNumber();
  particle_gen_a.setWeight( 0.5 );

  FACEMC::NeutronState particle_gen_a_copy( particle_gen_a );

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

  //Create a second generation particle with the same collision number
  FACEMC::NeutronState particle_gen_b( particle_gen_a, true );

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
  TEST_EQUALITY( particle_gen_b.getSpeed(),
		 particle_gen_a.getSpeed() );
  TEST_EQUALITY( particle_gen_b.getTime(),
		 particle_gen_a.getTime() );
  TEST_EQUALITY( particle_gen_b.getCollisionNumber(),
		 particle_gen_a.getCollisionNumber() );
  TEST_EQUALITY( particle_gen_b.getGenerationNumber(),
		 particle_gen_a.getGenerationNumber()+1u );
  TEST_EQUALITY( particle_gen_b.getWeight(),
		 particle_gen_a.getWeight() );  

  // Create a third generation particle and reset the collision counter
  FACEMC::NeutronState particle_gen_c( particle_gen_b, true, true );

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
  TEST_EQUALITY( particle_gen_c.getSpeed(),
		 particle_gen_b.getSpeed() );
  TEST_EQUALITY( particle_gen_c.getTime(),
		 particle_gen_b.getTime() );
  TEST_EQUALITY_CONST( particle_gen_c.getCollisionNumber(), 0u );
  TEST_EQUALITY( particle_gen_c.getGenerationNumber(),
		 particle_gen_b.getGenerationNumber()+1u );
  TEST_EQUALITY( particle_gen_c.getWeight(),
		 particle_gen_b.getWeight() );
}

//---------------------------------------------------------------------------//
// Create new particles
TEUCHOS_UNIT_TEST( NeutronState, core_constructor )
{
  FACEMC::ParticleStateCore core( 1ull, 
				  FACEMC::NEUTRON, 
				  1.0, 1.0, 1.0,
				  0.0, 1.0, 0.0,
				  2.0,
				  0.5,
				  1u,
				  2u,
				  0.25 );

  FACEMC::NeutronState particle( core );

  TEST_EQUALITY_CONST( particle.getHistoryNumber(), 1ull );
  TEST_EQUALITY_CONST( particle.getParticleType(), FACEMC::NEUTRON );
  TEST_EQUALITY_CONST( particle.getXPosition(), 1.0 );
  TEST_EQUALITY_CONST( particle.getYPosition(), 1.0 );
  TEST_EQUALITY_CONST( particle.getZPosition(), 1.0 );
  TEST_EQUALITY_CONST( particle.getXDirection(), 0.0 );
  TEST_EQUALITY_CONST( particle.getYDirection(), 1.0 );
  TEST_EQUALITY_CONST( particle.getZDirection(), 0.0 );
  TEST_EQUALITY_CONST( particle.getEnergy(), 2.0 );
  TEST_EQUALITY_CONST( particle.getTime(), 0.5 );
  TEST_EQUALITY_CONST( particle.getCollisionNumber(), 1u );
  TEST_EQUALITY_CONST( particle.getGenerationNumber(), 2u );
  TEST_EQUALITY_CONST( particle.getWeight(), 0.25 );
}

//---------------------------------------------------------------------------//
// Create new particles
TEUCHOS_UNIT_TEST( NeutronState, assignment_operator )
{
  FACEMC::NeutronState particle_gen_a( 1ull );
  particle_gen_a.setPosition( 1.0, 1.0, 1.0 );
  particle_gen_a.setPosition( 0.0, 0.0, 1.0 );
  particle_gen_a.setEnergy( 1.0 );
  particle_gen_a.setTime( 1.0 );
  particle_gen_a.incrementCollisionNumber();
  particle_gen_a.setWeight( 0.5 );

  FACEMC::NeutronState particle_gen_a_copy = particle_gen_a;

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
  TEST_EQUALITY( particle_gen_a_copy.getTime(),
		 particle_gen_a.getTime() );
  TEST_EQUALITY( particle_gen_a_copy.getCollisionNumber(),
		 particle_gen_a.getCollisionNumber() );
  TEST_EQUALITY( particle_gen_a_copy.getGenerationNumber(),
		 particle_gen_a.getGenerationNumber() );
  TEST_EQUALITY( particle_gen_a_copy.getWeight(),
		 particle_gen_a.getWeight() );
}

//---------------------------------------------------------------------------//
// end tstNeutronState.cpp
//---------------------------------------------------------------------------//
