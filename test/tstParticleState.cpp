//---------------------------------------------------------------------------//
//!
//! \file   tstParticleState.cpp
//! \author Alex Robinson
//! \brief  Particle state unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FACEMC Includes
#include "ParticleState.hpp"
#include "PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestParticleState : public FACEMC::ParticleState
{
public:
  
  TestParticleState( const unsigned long long history_number )
  : FACEMC::ParticleState( history_number, FACEMC::PHOTON )
  { /* ... */ }

  TestParticleState( const FACEMC::ParticleState& existing_base_state,
		     const bool increment_generation_number = false,
		     const bool reset_collision_number = false )
    : FACEMC::ParticleState( existing_base_state, 
			     FACEMC::PHOTON,
			     increment_generation_number,
			     reset_collision_number )
  { /* ... */ }

  TestParticleState( const FACEMC::ParticleStateCore& core )
    : FACEMC::ParticleState( core )
  { /* ... */ }

  TestParticleState& operator=(
			     const FACEMC::ParticleState& existing_base_state )
  { FACEMC::ParticleState::operator=( existing_base_state ); }

  ~TestParticleState()
  { /* ... */ }

  double getSpeed() const
  { return 1.0; }

  FACEMC::ParticleState::timeType calculateTraversalTime( 
						  const double distance ) const
  { return 1.0; }

  void print( std::ostream& os ) const
  { printImplementation( os ); }

  // Allow public access to protected member functions
  using FACEMC::ParticleState::calculateSpeed;
  using FACEMC::ParticleState::calculateKineticEnergy;
};

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Get the history number
TEUCHOS_UNIT_TEST( ParticleState, getHistoryNumber )
{
  TestParticleState particle( 1ull );

  TEST_EQUALITY_CONST( particle.getHistoryNumber(), 1ull );
}

//---------------------------------------------------------------------------//
// Set/get the cell containing a particle
TEUCHOS_UNIT_TEST( ParticleState, setgetCell )
{
  TestParticleState particle( 1ull );

  particle.setCell( 1 );
  
  TEST_EQUALITY_CONST( particle.getCell(), 1 );
}

//---------------------------------------------------------------------------//
// Set/get the position of a particle
TEUCHOS_UNIT_TEST( ParticleState, setgetPosition )
{
  TestParticleState particle( 1ull );

  double position[3] = {1.0, 1.0, 1.0};

  particle.setPosition( position[0], position[1], position[2] );

  TEST_EQUALITY_CONST( particle.getXPosition(), 1.0 );
  TEST_EQUALITY_CONST( particle.getYPosition(), 1.0 );
  TEST_EQUALITY_CONST( particle.getZPosition(), 1.0 );

  const double* particle_position = particle.getPosition();

  TEST_EQUALITY_CONST( particle_position[0], 1.0 );
  TEST_EQUALITY_CONST( particle_position[1], 1.0 );
  TEST_EQUALITY_CONST( particle_position[2], 1.0 );

  position[0] = 2.0;

  particle.setPosition( position );

  TEST_EQUALITY_CONST( particle.getXPosition(), 2.0 );
  TEST_EQUALITY_CONST( particle.getYPosition(), 1.0 );
  TEST_EQUALITY_CONST( particle.getZPosition(), 1.0 );

  particle_position = particle.getPosition();

  TEST_EQUALITY_CONST( particle_position[0], 2.0 );
  TEST_EQUALITY_CONST( particle_position[1], 1.0 );
  TEST_EQUALITY_CONST( particle_position[2], 1.0 );  
}

//---------------------------------------------------------------------------//
// Set/get the direction of a particle
TEUCHOS_UNIT_TEST( ParticleState, setgetDirection )
{
  TestParticleState particle( 1ull );

  double direction[3] = 
    {0.5773502691896258, 0.5773502691896258, 0.5773502691896258};

  particle.setDirection( direction[0], direction[1], direction[2] );

  TEST_EQUALITY_CONST( particle.getXDirection(), 0.5773502691896258 );
  TEST_EQUALITY_CONST( particle.getYDirection(), 0.5773502691896258 );
  TEST_EQUALITY_CONST( particle.getZDirection(), 0.5773502691896258 );

  const double* particle_direction = particle.getDirection();

  TEST_EQUALITY_CONST( direction[0], 0.5773502691896258 );
  TEST_EQUALITY_CONST( direction[1], 0.5773502691896258 );
  TEST_EQUALITY_CONST( direction[2], 0.5773502691896258 );

  particle.setDirection( direction );

  TEST_EQUALITY_CONST( particle.getXDirection(), 0.5773502691896258 );
  TEST_EQUALITY_CONST( particle.getYDirection(), 0.5773502691896258 );
  TEST_EQUALITY_CONST( particle.getZDirection(), 0.5773502691896258 );

  particle_direction = particle.getDirection();

  TEST_EQUALITY_CONST( direction[0], 0.5773502691896258 );
  TEST_EQUALITY_CONST( direction[1], 0.5773502691896258 );
  TEST_EQUALITY_CONST( direction[2], 0.5773502691896258 );
}

//---------------------------------------------------------------------------//
// Set/get the enegy of a particle
TEUCHOS_UNIT_TEST( ParticleState, setgetEnergy )
{
  TestParticleState particle( 1ull );

  particle.setEnergy( 1.0 );

  TEST_EQUALITY_CONST( particle.getEnergy(), 1.0 );
}

//---------------------------------------------------------------------------//
// Set/get the time state of a particle
TEUCHOS_UNIT_TEST( ParticleState, setgetTime )
{
  TestParticleState particle( 1ull );

  particle.setTime( 1.0 );

  TEST_EQUALITY_CONST( particle.getTime(), 1.0 );
}

//---------------------------------------------------------------------------//
// Increment/get the collision number of the particle
TEUCHOS_UNIT_TEST( ParticleState, incrementgetCollisionNumber )
{
  TestParticleState particle( 1ull );

  particle.incrementCollisionNumber();
  particle.incrementCollisionNumber();
  
  TEST_EQUALITY_CONST( particle.getCollisionNumber(), 2u );
}

//---------------------------------------------------------------------------//
// Get the generation number of the particle
TEUCHOS_UNIT_TEST( ParticleState, getGenerationNumber )
{
  TestParticleState particle( 1ull );

  TEST_EQUALITY_CONST( particle.getGenerationNumber(), 0u );
}

//---------------------------------------------------------------------------//
// Set/get the weight of a particle
TEUCHOS_UNIT_TEST( ParticleState, setgetWeight )
{
  TestParticleState particle( 1ull );

  particle.setWeight( 1.0 );

  TEST_EQUALITY_CONST( particle.getWeight(), 1.0 );
}

//---------------------------------------------------------------------------//
// Multiply the weight of a particle
TEUCHOS_UNIT_TEST( ParticleState, multiplyWeight )
{
  TestParticleState particle( 1ull );

  particle.setWeight( 1.0 );
  particle.multiplyWeight( 0.5 );

  TEST_EQUALITY_CONST( particle.getWeight(), 0.5 );
}

//---------------------------------------------------------------------------//
// Test if a particle is lost
TEUCHOS_UNIT_TEST( ParticleState, lost )
{
  TestParticleState particle( 1ull );

  TEST_ASSERT( !particle.isLost() );

  particle.setAsLost();

  TEST_ASSERT( particle.isLost() );
}

//---------------------------------------------------------------------------//
// Test if a particle is gone
TEUCHOS_UNIT_TEST( ParticleState, gone )
{
  TestParticleState particle( 1ull );

  TEST_ASSERT( !particle.isGone() );

  particle.setAsGone();

  TEST_ASSERT( particle.isGone() );
}

//---------------------------------------------------------------------------//
// Spawn a ray 
TEUCHOS_UNIT_TEST( ParticleState, spawnRay )
{
  TestParticleState particle( 1ull );
  particle.setPosition( 1.0, 1.0, -1.0 );
  particle.setDirection( 0.0, 0.0, 1.0 );

  Teuchos::RCP<FACEMC::Ray> ray;

  particle.spawnRay( ray );

  TEST_EQUALITY_CONST( ray->getXPosition(), 1.0 );
  TEST_EQUALITY_CONST( ray->getYPosition(), 1.0 );
  TEST_EQUALITY_CONST( ray->getZPosition(), -1.0 );
  TEST_EQUALITY_CONST( ray->getXDirection(), 0.0 );
  TEST_EQUALITY_CONST( ray->getYDirection(), 0.0 );
  TEST_EQUALITY_CONST( ray->getZDirection(), 1.0 );
}

//---------------------------------------------------------------------------//
// Export a particle state core
TEUCHOS_UNIT_TEST( ParticleState, exportCore )
{
  TestParticleState particle( 1ull );
  particle.setPosition( 1.0, 1.0, 1.0 );
  particle.setDirection( 0.0, 0.0, 1.0 );
  particle.setEnergy( 1.0 );
  particle.setTime( 0.5 );
  particle.incrementCollisionNumber();
  particle.setWeight( 0.25 );

  FACEMC::ParticleStateCore test_core = particle.exportCore();
  
  // Verify that a core copy has been made
  test_core.x_position = 2.0;
  
  TEST_EQUALITY_CONST( particle.getXPosition(), 1.0 );
}

//---------------------------------------------------------------------------//
// Calculate the speed of a massive particle (cm/s)
TEUCHOS_UNIT_TEST( ParticleState, calculateSpeed )
{
  TestParticleState particle( 1ull );
  
  double speed = particle.calculateSpeed( 1.0, 1.0 );

  TEST_EQUALITY_CONST( speed, 
		       FACEMC::PhysicalConstants::speed_of_light*sqrt(3)/2 );
}

//---------------------------------------------------------------------------//
// Calculate the kinetic energy of a massive particle (MeV)
TEUCHOS_UNIT_TEST( ParticleState, calculateKineticEnergy )
{
  TestParticleState particle( 1ull );

  double kinetic_energy = 
    particle.calculateKineticEnergy( 
			 1.0, 
			 FACEMC::PhysicalConstants::speed_of_light*sqrt(3)/2 );
  
  TEST_FLOATING_EQUALITY( kinetic_energy, 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Create new particles
TEUCHOS_UNIT_TEST( ParticleState, copy_constructor )
{
  TestParticleState particle_gen_a( 1ull );
  particle_gen_a.setPosition( 1.0, 1.0, 1.0 );
  particle_gen_a.setPosition( 0.0, 0.0, 1.0 );
  particle_gen_a.setEnergy( 1.0 );
  particle_gen_a.setTime( 1.0 );
  particle_gen_a.incrementCollisionNumber();
  particle_gen_a.setWeight( 0.5 );

  TestParticleState particle_gen_a_copy( particle_gen_a );

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

  // Create a second generation particle with the same collision number
  TestParticleState particle_gen_b( particle_gen_a, true );

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

  // Create a third generation particle and reset the collision counter
  TestParticleState particle_gen_c( particle_gen_b, true, true );

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
}

//---------------------------------------------------------------------------//
// Core constructor
TEUCHOS_UNIT_TEST( ParticleState, core_constructor )
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

  TestParticleState particle( core );

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
TEUCHOS_UNIT_TEST( ParticleState, assignment_operator )
{
  TestParticleState particle_gen_a( 1ull );
  particle_gen_a.setPosition( 1.0, 1.0, 1.0 );
  particle_gen_a.setPosition( 0.0, 0.0, 1.0 );
  particle_gen_a.setEnergy( 1.0 );
  particle_gen_a.setTime( 1.0 );
  particle_gen_a.incrementCollisionNumber();
  particle_gen_a.setWeight( 0.5 );

  TestParticleState particle_gen_a_copy = particle_gen_a;

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
// end tstParticleState.cpp
//---------------------------------------------------------------------------//
