//---------------------------------------------------------------------------//
//!
//! \file   tstBasicParticleState.cpp
//! \author Alex Robinson
//! \brief  Basic particle state unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FACEMC Includes
#include "BasicParticleState.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Get the particle type
TEUCHOS_UNIT_TEST( BasicParticleState, getParticleType )
{
  FACEMC::BasicParticleState particle;
  particle.setParticleType( FACEMC::PHOTON );
  
  TEST_EQUALITY_CONST( particle.getParticleType(), FACEMC::PHOTON );
}

//---------------------------------------------------------------------------//
// Set/get the position of a particle
TEUCHOS_UNIT_TEST( BasicParticleState, setgetPosition )
{
  FACEMC::BasicParticleState particle;
  
  particle.setPosition( 1.0, 1.0, 1.0 );

  TEST_EQUALITY_CONST( particle.getXPosition(), 1.0 );
  TEST_EQUALITY_CONST( particle.getYPosition(), 1.0 );
  TEST_EQUALITY_CONST( particle.getZPosition(), 1.0 );

  const double* position = particle.getPosition();

  TEST_EQUALITY_CONST( position[0], 1.0 );
  TEST_EQUALITY_CONST( position[1], 1.0 );
  TEST_EQUALITY_CONST( position[2], 1.0 );
}

//---------------------------------------------------------------------------//
// Set/get the direction of a particle
TEUCHOS_UNIT_TEST( BasicParticleState, setgetDirection )
{
  FACEMC::BasicParticleState particle;
  
  particle.setDirection( 0.5773502691896258, 
			 0.5773502691896258,
			 0.5773502691896258 );
  
  TEST_EQUALITY_CONST( particle.getXDirection(), 0.5773502691896258 );
  TEST_EQUALITY_CONST( particle.getYDirection(), 0.5773502691896258 );
  TEST_EQUALITY_CONST( particle.getZDirection(), 0.5773502691896258 );

  const double* direction = particle.getDirection();

  TEST_EQUALITY_CONST( direction[0], 0.5773502691896258 );
  TEST_EQUALITY_CONST( direction[1], 0.5773502691896258 );
  TEST_EQUALITY_CONST( direction[2], 0.5773502691896258 );
}

//---------------------------------------------------------------------------//
// Set/get the energy of a particle
TEUCHOS_UNIT_TEST( BasicParticleState, setgetEnergy )
{
  FACEMC::BasicParticleState particle;
  
  particle.setEnergy( 1.0 );
  
  TEST_EQUALITY_CONST( particle.getEnergy(), 1.0 );
}
	
//---------------------------------------------------------------------------//
// Set/get the time state of a particle
TEUCHOS_UNIT_TEST( BasicParticleState, setgetTime )
{
  FACEMC::BasicParticleState particle;
  
  particle.setTime( 1.0 );

  TEST_EQUALITY_CONST( particle.getTime(), 1.0 );
}

//---------------------------------------------------------------------------//
// Advance a photon along its direction by a specified distance
TEUCHOS_UNIT_TEST( BasicParticleState, advance_photon )
{
  FACEMC::BasicParticleState particle;

  particle.setPosition( 1.0, 1.0, 1.0 );
  particle.setDirection( 0.5773502691896258, 
			 0.5773502691896258,
			 0.5773502691896258 );
  particle.setTime( 0.0 );
  
  particle.advance( 1.7320508075688772 );

  TEST_FLOATING_EQUALITY( particle.getXPosition(), 2.0, 1e-12 );
  TEST_FLOATING_EQUALITY( particle.getYPosition(), 2.0, 1e-12 );
  TEST_FLOATING_EQUALITY( particle.getZPosition(), 2.0, 1e-12 );
  TEST_FLOATING_EQUALITY( particle.getTime(), 5.7774996046392e-11, 1e-12 );
}

//---------------------------------------------------------------------------//
// Advance a neutron along its direction by a specified distance
TEUCHOS_UNIT_TEST( BasicParticleState, advance_neutron )
{
  const double position[3] = {1.0, 1.0, 1.0};
  const double direction[3] = {0.5773502691896258, 
			       0.5773502691896258,
			       0.5773502691896258};
  FACEMC::BasicParticleState particle( FACEMC::NEUTRON,
				       position,
				       direction,
				       1.0,
				       0.0,
				       1.0 );

  particle.advance( 1.7320508075688772 );

  TEST_FLOATING_EQUALITY( particle.getXPosition(), 2.0, 1e-12 );
  TEST_FLOATING_EQUALITY( particle.getYPosition(), 2.0, 1e-12 );
  TEST_FLOATING_EQUALITY( particle.getZPosition(), 2.0, 1e-12 );
  TEST_FLOATING_EQUALITY( particle.getTime(), 5.4283416756994e-8, 1e-12 );
}

//---------------------------------------------------------------------------//
// increment/get the collision number of a particle
TEUCHOS_UNIT_TEST( BasicParticleState, incrementgetWeight )
{
  FACEMC::BasicParticleState particle_1;

  TEST_EQUALITY_CONST( particle_1.getCollisionNumber(), 0u );

  particle_1.incrementCollisionNumber();
  
  TEST_EQUALITY_CONST( particle_1.getCollisionNumber(), 1u );

  const double position[3] = {1.0, 1.0, 1.0};
  const double direction[3] = {0.5773502691896258, 
			       0.5773502691896258,
			       0.5773502691896258};
  FACEMC::BasicParticleState particle_2( FACEMC::NEUTRON,
					 position,
					 direction,
					 1.0,
					 0.0,
					 1.0 );
  TEST_EQUALITY_CONST( particle_2.getCollisionNumber(), 0u );
  
  particle_2.incrementCollisionNumber();

  TEST_EQUALITY_CONST( particle_2.getCollisionNumber(), 1u );
}

//---------------------------------------------------------------------------//
// Set/get the weight of a particle
TEUCHOS_UNIT_TEST( BasicParticleState, setgetWeight )
{
  FACEMC::BasicParticleState particle;

  particle.setWeight( 1.0 );

  TEST_EQUALITY_CONST( particle.getWeight(), 1.0 );
}

//---------------------------------------------------------------------------//
// Multiply the weight of a particle
TEUCHOS_UNIT_TEST( BasicParticleState, multipyWeight )
{
  FACEMC::BasicParticleState particle;

  particle.setWeight( 1.0 );
  particle.multiplyWeight( 0.5 );

  TEST_EQUALITY_CONST( particle.getWeight(), 0.5 );
}

//---------------------------------------------------------------------------//
// end tstBasicParticleState.cpp
//---------------------------------------------------------------------------//
