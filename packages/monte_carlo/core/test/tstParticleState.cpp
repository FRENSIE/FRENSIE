//---------------------------------------------------------------------------//
//!
//! \file   tstParticleState.cpp
//! \author Alex Robinson
//! \brief  Particle state unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/serialization/base_object.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_UnitTestHarnessExtensions.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestParticleState : public MonteCarlo::ParticleState
{
public:

  TestParticleState()
  { /* ... */ }
  
  TestParticleState( const unsigned long long history_number )
  : MonteCarlo::ParticleState( history_number, MonteCarlo::PHOTON )
  { /* ... */ }

  TestParticleState( const MonteCarlo::ParticleState& existing_base_state,
		     const bool increment_generation_number = false,
		     const bool reset_collision_number = false )
    : MonteCarlo::ParticleState( existing_base_state, 
			     MonteCarlo::PHOTON,
			     increment_generation_number,
			     reset_collision_number )
  { /* ... */ }

  ~TestParticleState()
  { /* ... */ }

  double getSpeed() const
  { return 1.0; }

  MonteCarlo::ParticleState::timeType calculateTraversalTime( 
						  const double distance ) const
  { return 1.0; }

  void print( std::ostream& os ) const
  { printImplementation<TestParticleState>( os ); }

private:
  TestParticleState( const TestParticleState& state );

  // Save the state to an archive
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  {
    ar & boost::serialization::make_nvp("ParticleState",boost::serialization::base_object<MonteCarlo::ParticleState>(*this));
  }
  
  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
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
// Rotate the direction using a polar and azimuthal angle
TEUCHOS_UNIT_TEST( ParticleState, rotateDirection )
{
  TestParticleState particle( 1ull );

  // Set the initial direction
  particle.setDirection( 1.0, 0.0, 0.0 );

  // Set the new direction
  particle.rotateDirection( -1.0, 0.0 );

  UTILITY_TEST_FLOATING_EQUALITY( particle.getXDirection(), -1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( particle.getYDirection(), 0.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( particle.getZDirection(), 0.0, 1e-15 );

  // Set the initial direction
  particle.setDirection( 1.0, 0.0, 0.0 );

  // Set the new direction
  particle.rotateDirection( 0.0, Utility::PhysicalConstants::pi/2 );

  UTILITY_TEST_FLOATING_EQUALITY( particle.getXDirection(), 0.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( particle.getYDirection(), 1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( particle.getZDirection(), 0.0, 1e-15 );

  // Set the initial direction
  particle.setDirection( 1.0, 0.0, 0.0 );

  // Set the new direction
  particle.rotateDirection( 0.0, 3*Utility::PhysicalConstants::pi/2 );

  UTILITY_TEST_FLOATING_EQUALITY( particle.getXDirection(), 0.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( particle.getYDirection(), -1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( particle.getZDirection(), 0.0, 1e-15 );

  // Set the initial direction
  particle.setDirection( 1.0, 0.0, 0.0 );

  // Set the new direction
  particle.rotateDirection( 0.0, Utility::PhysicalConstants::pi );

  UTILITY_TEST_FLOATING_EQUALITY( particle.getXDirection(), 0.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( particle.getYDirection(), 0.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( particle.getZDirection(), 1.0, 1e-15 );

  // Set the initial direction
  particle.setDirection( 1.0, 0.0, 0.0 );

  // Set the new direction
  particle.rotateDirection( 0.0, 0.0 );

  UTILITY_TEST_FLOATING_EQUALITY( particle.getXDirection(), 0.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( particle.getYDirection(), 0.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( particle.getZDirection(), -1.0, 1e-15 );

  // Set the initial direction
  particle.setDirection( 0.0, 1.0, 0.0 );

  // Set the new direction
  particle.rotateDirection( -1.0, 0.0 );

  UTILITY_TEST_FLOATING_EQUALITY( particle.getXDirection(), 0.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( particle.getYDirection(), -1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( particle.getZDirection(), 0.0, 1e-15 );

  // Set the initial direction
  particle.setDirection( 0.0, 1.0, 0.0 );

  // Set the new direction
  particle.rotateDirection( 0.0, 3*Utility::PhysicalConstants::pi/2 );

  UTILITY_TEST_FLOATING_EQUALITY( particle.getXDirection(), 1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( particle.getYDirection(), 0.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( particle.getZDirection(), 0.0, 1e-15 );

  // Set the initial direction
  particle.setDirection( 0.0, 1.0, 0.0 );

  // Set the new direction
  particle.rotateDirection( 0.0, Utility::PhysicalConstants::pi/2 );

  UTILITY_TEST_FLOATING_EQUALITY( particle.getXDirection(), -1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( particle.getYDirection(), 0.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( particle.getZDirection(), 0.0, 1e-15 );

  // Set the initial direction
  particle.setDirection( 0.0, 1.0, 0.0 );

  // Set the new direction
  particle.rotateDirection( 0.0, Utility::PhysicalConstants::pi );

  UTILITY_TEST_FLOATING_EQUALITY( particle.getXDirection(), 0.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( particle.getYDirection(), 0.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( particle.getZDirection(), 1.0, 1e-15 );

  // Set the initial direction
  particle.setDirection( 0.0, 1.0, 0.0 );

  // Set the new direction
  particle.rotateDirection( 0.0, 0.0 );

  UTILITY_TEST_FLOATING_EQUALITY( particle.getXDirection(), 0.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( particle.getYDirection(), 0.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( particle.getZDirection(), -1.0, 1e-15 );

  // Set the initial direction
  particle.setDirection( 0.0, 0.0, 1.0 );

  // Set the new direction
  particle.rotateDirection( -1.0, 0.0 );

  UTILITY_TEST_FLOATING_EQUALITY( particle.getXDirection(), 0.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( particle.getYDirection(), 0.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( particle.getZDirection(), -1.0, 1e-15 );

  // Set the initial direction
  particle.setDirection( 0.0, 0.0, 1.0 );

  // Set the new direction
  particle.rotateDirection( 0.0, Utility::PhysicalConstants::pi/2 );

  UTILITY_TEST_FLOATING_EQUALITY( particle.getXDirection(), 1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( particle.getYDirection(), 0.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( particle.getZDirection(), 0.0, 1e-15 );

  // Set the initial direction
  particle.setDirection( 0.0, 0.0, 1.0 );

  // Set the new direction
  particle.rotateDirection( 0.0, 3*Utility::PhysicalConstants::pi/2 );

  UTILITY_TEST_FLOATING_EQUALITY( particle.getXDirection(), -1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( particle.getYDirection(), 0.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( particle.getZDirection(), 0.0, 1e-15 );

  // Set the initial direction
  particle.setDirection( 0.0, 0.0, 1.0 );

  // Set the new direction
  particle.rotateDirection( 0.0, Utility::PhysicalConstants::pi );

  UTILITY_TEST_FLOATING_EQUALITY( particle.getXDirection(), 0.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( particle.getYDirection(), 1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( particle.getZDirection(), 0.0, 1e-15 );

  // Set the initial direction
  particle.setDirection( 0.0, 0.0, 1.0 );

  // Set the new direction
  particle.rotateDirection( 0.0, 0.0 );

  UTILITY_TEST_FLOATING_EQUALITY( particle.getXDirection(), 0.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( particle.getYDirection(), -1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( particle.getZDirection(), 0.0, 1e-15 );
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
// Get a ray object from the particle
TEUCHOS_UNIT_TEST( ParticleState, ray )
{
  TestParticleState particle( 1ull );
  particle.setPosition( 1.0, 1.0, -1.0 );
  particle.setDirection( 0.0, 0.0, 1.0 );

  TEST_EQUALITY_CONST( particle.ray().getXPosition(), 1.0 );
  TEST_EQUALITY_CONST( particle.ray().getYPosition(), 1.0 );
  TEST_EQUALITY_CONST( particle.ray().getZPosition(), -1.0 );
  TEST_EQUALITY_CONST( particle.ray().getXDirection(), 0.0 );
  TEST_EQUALITY_CONST( particle.ray().getYDirection(), 0.0 );
  TEST_EQUALITY_CONST( particle.ray().getZDirection(), 1.0 );
}

//---------------------------------------------------------------------------//
// Archive a particle state
TEUCHOS_UNIT_TEST( ParticleState, archive )
{
  // Create and archive a particle
  {
    TestParticleState particle( 1ull );
    particle.setPosition( 1.0, 1.0, 1.0 );
    particle.setDirection( 0.0, 0.0, 1.0 );
    particle.setEnergy( 1.0 );
    particle.setTime( 0.5 );
    particle.incrementCollisionNumber();
    particle.setWeight( 0.25 );
  
    std::ofstream ofs( "test_particle_state_archive.xml" );

    boost::archive::xml_oarchive ar(ofs);
    ar << BOOST_SERIALIZATION_NVP( particle );
  }

  // Load the archived particle
  TestParticleState loaded_particle;

  std::ifstream ifs( "test_particle_state_archive.xml" );

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

  // Create a second third generation particle after the second gen particle
  // has been set to gone
  particle_gen_b.setAsGone();

  TestParticleState particle_gen_2c( particle_gen_b, true );

  TEST_ASSERT( !particle_gen_2c.isGone() );
  TEST_ASSERT( !particle_gen_2c.isLost() );

  // Create a second second generation particle after the first gen particle
  // has been set to lost
  particle_gen_a.setAsLost();

  TestParticleState particle_gen_2b( particle_gen_a, true );

  TEST_ASSERT( !particle_gen_2b.isGone() );
  TEST_ASSERT( !particle_gen_2b.isLost() );
}

//---------------------------------------------------------------------------//
// end tstParticleState.cpp
//---------------------------------------------------------------------------//
