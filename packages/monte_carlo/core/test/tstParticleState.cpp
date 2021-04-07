//---------------------------------------------------------------------------//
//!
//! \file   tstParticleState.cpp
//! \author Alex Robinson
//! \brief  Particle state unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_ParticleState.hpp"
#include "Geometry_InfiniteMediumModel.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "TestParticleState.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types.
//---------------------------------------------------------------------------//

namespace cgs = boost::units::cgs;

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Get the history number
FRENSIE_UNIT_TEST( ParticleState, getHistoryNumber )
{
  TestParticleState particle( 1ull );

  FRENSIE_CHECK_EQUAL( particle.getHistoryNumber(), 1ull );
}

//---------------------------------------------------------------------------//
// Set/get the source id that created the particle (history)
FRENSIE_UNIT_TEST( ParticleState, setgetSourceId )
{
  TestParticleState particle( 1ull );

  particle.setSourceId( 2 );

  FRENSIE_CHECK_EQUAL( particle.getSourceId(), 2 );
}

//---------------------------------------------------------------------------//
// Set/get the source cell where the particle (history) started
FRENSIE_UNIT_TEST( ParticleState, setgetSourceCell )
{
  TestParticleState particle( 1ull );

  particle.setSourceCell( 1 );

  FRENSIE_CHECK_EQUAL( particle.getSourceCell(), 1 );
}

//---------------------------------------------------------------------------//
// Set/get the position of a particle
FRENSIE_UNIT_TEST( ParticleState, setgetPosition )
{
  TestParticleState particle( 1ull );

  double position[3] = {1.0, 1.0, 1.0};

  particle.setPosition( position[0], position[1], position[2] );

  FRENSIE_CHECK_EQUAL( particle.getXPosition(), 1.0 );
  FRENSIE_CHECK_EQUAL( particle.getYPosition(), 1.0 );
  FRENSIE_CHECK_EQUAL( particle.getZPosition(), 1.0 );

  const double* particle_position = particle.getPosition();

  FRENSIE_CHECK_EQUAL( particle_position[0], 1.0 );
  FRENSIE_CHECK_EQUAL( particle_position[1], 1.0 );
  FRENSIE_CHECK_EQUAL( particle_position[2], 1.0 );

  position[0] = 2.0;

  particle.setPosition( position );

  FRENSIE_CHECK_EQUAL( particle.getXPosition(), 2.0 );
  FRENSIE_CHECK_EQUAL( particle.getYPosition(), 1.0 );
  FRENSIE_CHECK_EQUAL( particle.getZPosition(), 1.0 );

  particle_position = particle.getPosition();

  FRENSIE_CHECK_EQUAL( particle_position[0], 2.0 );
  FRENSIE_CHECK_EQUAL( particle_position[1], 1.0 );
  FRENSIE_CHECK_EQUAL( particle_position[2], 1.0 );
}

//---------------------------------------------------------------------------//
// Set/get the direction of a particle
FRENSIE_UNIT_TEST( ParticleState, setgetDirection )
{
  TestParticleState particle( 1ull );

  double direction[3] =
    {0.5773502691896258, 0.5773502691896258, 0.5773502691896258};

  particle.setDirection( direction[0], direction[1], direction[2] );

  FRENSIE_CHECK_EQUAL( particle.getXDirection(), 0.5773502691896258 );
  FRENSIE_CHECK_EQUAL( particle.getYDirection(), 0.5773502691896258 );
  FRENSIE_CHECK_EQUAL( particle.getZDirection(), 0.5773502691896258 );

  const double* particle_direction = particle.getDirection();

  FRENSIE_CHECK_EQUAL( direction[0], 0.5773502691896258 );
  FRENSIE_CHECK_EQUAL( direction[1], 0.5773502691896258 );
  FRENSIE_CHECK_EQUAL( direction[2], 0.5773502691896258 );

  particle.setDirection( direction );

  FRENSIE_CHECK_EQUAL( particle.getXDirection(), 0.5773502691896258 );
  FRENSIE_CHECK_EQUAL( particle.getYDirection(), 0.5773502691896258 );
  FRENSIE_CHECK_EQUAL( particle.getZDirection(), 0.5773502691896258 );

  particle_direction = particle.getDirection();

  FRENSIE_CHECK_EQUAL( direction[0], 0.5773502691896258 );
  FRENSIE_CHECK_EQUAL( direction[1], 0.5773502691896258 );
  FRENSIE_CHECK_EQUAL( direction[2], 0.5773502691896258 );
}

//---------------------------------------------------------------------------//
// Rotate the direction using a polar and azimuthal angle
FRENSIE_UNIT_TEST( ParticleState, rotateDirection )
{
  TestParticleState particle( 1ull );

  // Rotate x direction to neg. x direction
  particle.setDirection( 1.0, 0.0, 0.0 );
  particle.rotateDirection( -1.0, 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getXDirection(), -1.0, 1e-15 );
  FRENSIE_CHECK_SMALL( particle.getYDirection(), 1e-15 );
  FRENSIE_CHECK_SMALL( particle.getZDirection(), 1e-15 );

  // Rotate x direction to y direction
  particle.setDirection( 1.0, 0.0, 0.0 );
  particle.rotateDirection( 0.0, Utility::PhysicalConstants::pi/2 );

  FRENSIE_CHECK_SMALL( particle.getXDirection(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getYDirection(), 1.0, 1e-15 );
  FRENSIE_CHECK_SMALL( particle.getZDirection(), 1e-15 );

  // Rotate x direction to neg. y direction
  particle.setDirection( 1.0, 0.0, 0.0 );
  particle.rotateDirection( 0.0, 3*Utility::PhysicalConstants::pi/2 );

  FRENSIE_CHECK_SMALL( particle.getXDirection(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getYDirection(), -1.0, 1e-15 );
  FRENSIE_CHECK_SMALL( particle.getZDirection(), 1e-15 );

  // Rotate x direction to z direction
  particle.setDirection( 1.0, 0.0, 0.0 );
  particle.rotateDirection( 0.0, Utility::PhysicalConstants::pi );

  FRENSIE_CHECK_SMALL( particle.getXDirection(), 1e-15 );
  FRENSIE_CHECK_SMALL( particle.getYDirection(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getZDirection(), 1.0, 1e-15 );

  // Rotate x direction to neg. z direction
  particle.setDirection( 1.0, 0.0, 0.0 );
  particle.rotateDirection( 0.0, 0.0 );

  FRENSIE_CHECK_SMALL( particle.getXDirection(), 1e-15 );
  FRENSIE_CHECK_SMALL( particle.getYDirection(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getZDirection(), -1.0, 1e-15 );

  // Rotate y direction to neg. y direction
  particle.setDirection( 0.0, 1.0, 0.0 );
  particle.rotateDirection( -1.0, 0.0 );

  FRENSIE_CHECK_SMALL( particle.getXDirection(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getYDirection(), -1.0, 1e-15 );
  FRENSIE_CHECK_SMALL( particle.getZDirection(), 1e-15 );

  // Rotate y direction to x direction
  particle.setDirection( 0.0, 1.0, 0.0 );
  particle.rotateDirection( 0.0, 3*Utility::PhysicalConstants::pi/2 );

  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getXDirection(), 1.0, 1e-15 );
  FRENSIE_CHECK_SMALL( particle.getYDirection(), 1e-15 );
  FRENSIE_CHECK_SMALL( particle.getZDirection(), 1e-15 );

  // Rotate y direction to neg. x direction
  particle.setDirection( 0.0, 1.0, 0.0 );
  particle.rotateDirection( 0.0, Utility::PhysicalConstants::pi/2 );

  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getXDirection(), -1.0, 1e-15 );
  FRENSIE_CHECK_SMALL( particle.getYDirection(), 1e-15 );
  FRENSIE_CHECK_SMALL( particle.getZDirection(), 1e-15 );

  // Rotate the y direction to z direction
  particle.setDirection( 0.0, 1.0, 0.0 );
  particle.rotateDirection( 0.0, Utility::PhysicalConstants::pi );

  FRENSIE_CHECK_SMALL( particle.getXDirection(), 1e-15 );
  FRENSIE_CHECK_SMALL( particle.getYDirection(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getZDirection(), 1.0, 1e-15 );

  // Rotate the y direction to neg. z direction
  particle.setDirection( 0.0, 1.0, 0.0 );
  particle.rotateDirection( 0.0, 0.0 );

  FRENSIE_CHECK_SMALL( particle.getXDirection(), 1e-15 );
  FRENSIE_CHECK_SMALL( particle.getYDirection(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getZDirection(), -1.0, 1e-15 );

  // Rotate the z direction to neg. z direction
  particle.setDirection( 0.0, 0.0, 1.0 );
  particle.rotateDirection( -1.0, 0.0 );

  FRENSIE_CHECK_SMALL( particle.getXDirection(), 1e-15 );
  FRENSIE_CHECK_SMALL( particle.getYDirection(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getZDirection(), -1.0, 1e-15 );

  // Rotate z direction to x direction
  particle.setDirection( 0.0, 0.0, 1.0 );
  particle.rotateDirection( 0.0, 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getXDirection(), 1.0, 1e-15 );
  FRENSIE_CHECK_SMALL( particle.getYDirection(), 1e-15 );
  FRENSIE_CHECK_SMALL( particle.getZDirection(), 1e-15 );

  // Rotate z direction to neg. x direction
  particle.setDirection( 0.0, 0.0, 1.0 );
  particle.rotateDirection( 0.0, Utility::PhysicalConstants::pi );

  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getXDirection(), -1.0, 1e-15 );
  FRENSIE_CHECK_SMALL( particle.getYDirection(), 1e-15 );
  FRENSIE_CHECK_SMALL( particle.getZDirection(), 1e-15 );

  // Rotate z direction to y direction
  particle.setDirection( 0.0, 0.0, 1.0 );
  particle.rotateDirection( 0.0, Utility::PhysicalConstants::pi/2 );

  FRENSIE_CHECK_SMALL( particle.getXDirection(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getYDirection(), 1.0, 1e-15 );
  FRENSIE_CHECK_SMALL( particle.getZDirection(), 1e-15 );

  // Rotate z direction to neg. y direction
  particle.setDirection( 0.0, 0.0, 1.0 );
  particle.rotateDirection( 0.0, 3*Utility::PhysicalConstants::pi/2 );

  FRENSIE_CHECK_SMALL( particle.getXDirection(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getYDirection(), -1.0, 1e-15 );
  FRENSIE_CHECK_SMALL( particle.getZDirection(), 1e-15 );
}

//---------------------------------------------------------------------------//
// Set/get the source energy of a particle
FRENSIE_UNIT_TEST( ParticleState, setgetSourceEnergy )
{
  TestParticleState particle( 1ull );

  particle.setSourceEnergy( 1.0 );

  FRENSIE_CHECK_EQUAL( particle.getSourceEnergy(), 1.0 );
}

//---------------------------------------------------------------------------//
// Set/get the energy of a particle
FRENSIE_UNIT_TEST( ParticleState, setgetEnergy )
{
  TestParticleState particle( 1ull );

  particle.setEnergy( 1.0 );

  FRENSIE_CHECK_EQUAL( particle.getEnergy(), 1.0 );
}

//---------------------------------------------------------------------------//
// Get the charge of a particle
FRENSIE_UNIT_TEST( ParticleState, getCharge )
{
  TestParticleState particle( 1ull );

  FRENSIE_CHECK_EQUAL( particle.getCharge(), 1 );
}

//---------------------------------------------------------------------------//
// Set/get the source time of a particle
FRENSIE_UNIT_TEST( ParticleState, setgetSourceTime )
{
  TestParticleState particle( 1ull );

  particle.setSourceTime( 1.0 );

  FRENSIE_CHECK_EQUAL( particle.getSourceTime(), 1.0 );
}

//---------------------------------------------------------------------------//
// Set/get the time state of a particle
FRENSIE_UNIT_TEST( ParticleState, setgetTime )
{
  TestParticleState particle( 1ull );

  particle.setTime( 1.0 );

  FRENSIE_CHECK_EQUAL( particle.getTime(), 1.0 );
}

//---------------------------------------------------------------------------//
// Increment/get the collision number of the particle
FRENSIE_UNIT_TEST( ParticleState, incrementgetCollisionNumber )
{
  TestParticleState particle( 1ull );

  particle.incrementCollisionNumber();
  particle.incrementCollisionNumber();

  FRENSIE_CHECK_EQUAL( particle.getCollisionNumber(), 2u );
}

//---------------------------------------------------------------------------//
// Get the generation number of the particle
FRENSIE_UNIT_TEST( ParticleState, getGenerationNumber )
{
  TestParticleState particle( 1ull );

  FRENSIE_CHECK_EQUAL( particle.getGenerationNumber(), 0u );
}

//---------------------------------------------------------------------------//
// Set/get the source weight of the particle
FRENSIE_UNIT_TEST( ParticleState, setgetSourceWeight )
{
  TestParticleState particle( 1ull );

  particle.setSourceWeight( 1.0 );

  FRENSIE_CHECK_EQUAL( particle.getSourceWeight(), 1.0 );
}

//---------------------------------------------------------------------------//
// Set/get the weight of a particle
FRENSIE_UNIT_TEST( ParticleState, setgetWeight )
{
  TestParticleState particle( 1ull );

  particle.setWeight( 1.0 );

  FRENSIE_CHECK_EQUAL( particle.getWeight(), 1.0 );
}

//---------------------------------------------------------------------------//
// Multiply the weight of a particle
FRENSIE_UNIT_TEST( ParticleState, multiplyWeight )
{
  TestParticleState particle( 1ull );

  particle.setWeight( 1.0 );
  particle.multiplyWeight( 0.5 );

  FRENSIE_CHECK_EQUAL( particle.getWeight(), 0.5 );
}

//---------------------------------------------------------------------------//
// Set/get the ray safety distance of a particle
FRENSIE_UNIT_TEST( ParticleState, setRaySafetyDistance )
{
  TestParticleState particle( 1ull );

  particle.setRaySafetyDistance( 1.0 );

  FRENSIE_CHECK_EQUAL( particle.getRaySafetyDistance(), 1.0 );
}

//---------------------------------------------------------------------------//
// Test if a particle is lost
FRENSIE_UNIT_TEST( ParticleState, lost )
{
  TestParticleState particle( 1ull );

  FRENSIE_CHECK( !particle.isLost() );
  FRENSIE_CHECK( (bool)particle );

  particle.setAsLost();

  FRENSIE_CHECK( particle.isLost() );
  FRENSIE_CHECK( !(bool)particle );
}

//---------------------------------------------------------------------------//
// Test if a particle is gone
FRENSIE_UNIT_TEST( ParticleState, gone )
{
  TestParticleState particle( 1ull );

  FRENSIE_CHECK( !particle.isGone() );
  FRENSIE_CHECK( (bool)particle );

  particle.setAsGone();

  FRENSIE_CHECK( particle.isGone() );
  FRENSIE_CHECK( !(bool)particle );
}

//---------------------------------------------------------------------------//
// Test if the navigator can be returned
FRENSIE_UNIT_TEST( ParticleState, navigator )
{
  TestParticleState particle( 1ull );

  particle.setPosition( 0.1, -10.0, sqrt(2.0) );
  particle.setDirection( 0.0, -1.0/sqrt(2.0), 1.0/sqrt(2.0) );

  // Get the particle location and direction from the navigator
  const Geometry::Navigator& const_particle_navigator =
    dynamic_cast<const MonteCarlo::ParticleState&>( particle ).navigator();

  FRENSIE_CHECK_EQUAL( const_particle_navigator.getPosition()[0],
                       0.1*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( const_particle_navigator.getPosition()[1],
                       -10.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( const_particle_navigator.getPosition()[2],
                       sqrt(2.0)*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( const_particle_navigator.getDirection()[0], 0.0 );
  FRENSIE_CHECK_EQUAL( const_particle_navigator.getDirection()[1],
                       -1.0/sqrt(2.0) );
  FRENSIE_CHECK_EQUAL( const_particle_navigator.getDirection()[2],
                       1.0/sqrt(2.0) );
  FRENSIE_CHECK_EQUAL( particle.getTime(), 0.0 );

  // Change the particle location and direction from the navigator - the
  // time state should still be updated if the navigator has been bound
  // to the particle state (internally)
  Geometry::Navigator& particle_navigator = particle.navigator();

  particle_navigator.advanceBySubstep( 1.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( particle.getXPosition(), 0.1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getYPosition(),
                                   -10.0-1.0/sqrt(2.0),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getZPosition(),
                                   3.0/sqrt(2.0),
                                   1e-15 );
  FRENSIE_CHECK_EQUAL( particle.getTime(), 1.0 );

  particle_navigator.changeDirection( 1.0, 0.0, 0.0 );

  FRENSIE_CHECK_EQUAL( particle.getXDirection(), 1.0 );
  FRENSIE_CHECK_EQUAL( particle.getYDirection(), 0.0 );
  FRENSIE_CHECK_EQUAL( particle.getZDirection(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that a particle position can be advanced along it's direction
FRENSIE_UNIT_TEST( ParticleState, advance )
{
  TestParticleState particle( 1ull );

  particle.setPosition( 0.0, 0.0, 0.0 );
  particle.setDirection( 0.0, -1.0/sqrt(2.0), 1.0/sqrt(2.0) );

  FRENSIE_CHECK_EQUAL( particle.getTime(), 0.0 );

  particle.advance( sqrt(2.0) );

  FRENSIE_REQUIRE( (bool)particle );
  FRENSIE_CHECK_EQUAL( particle.getXPosition(), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getYPosition(), -1.0, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getZPosition(), 1.0, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getTime(), sqrt(2.0), 1e-15 );

  particle.setDirection( -1.0, 0.0, 0.0 );

  particle.advance( 2.0 );

  FRENSIE_REQUIRE( (bool)particle );
  FRENSIE_CHECK_EQUAL( particle.getXPosition(), -2.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getYPosition(), -1.0, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getZPosition(), 1.0, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getTime(), 2.0+sqrt(2.0), 1e-15 );
}

//---------------------------------------------------------------------------//
// Test if the particle can be embedded inside of a geometry model
FRENSIE_UNIT_TEST( ParticleState, embedInModel )
{
  TestParticleState particle( 1ull );

  particle.setPosition( 0.1, -10.0, sqrt(2.0) );
  particle.setDirection( 0.0, -1.0/sqrt(2.0), 1.0/sqrt(2.0) );

  FRENSIE_CHECK_EQUAL( particle.getCell(), 0 );

  // Embed the particle in a model
  std::shared_ptr<Geometry::InfiniteMediumModel>
    model( new Geometry::InfiniteMediumModel( 2 ) );

  FRENSIE_CHECK( !particle.isEmbeddedInModel( *model ) );

  particle.embedInModel( model );

  FRENSIE_CHECK( particle.isEmbeddedInModel( *model ) );

  // Verify that the particle position and direction are unchanged
  FRENSIE_CHECK_EQUAL( particle.getXPosition(), 0.1 );
  FRENSIE_CHECK_EQUAL( particle.getYPosition(), -10.0 );
  FRENSIE_CHECK_EQUAL( particle.getZPosition(), sqrt(2.0) );
  FRENSIE_CHECK_EQUAL( particle.getXDirection(), 0.0 );
  FRENSIE_CHECK_EQUAL( particle.getYDirection(), -1.0/sqrt(2.0) );
  FRENSIE_CHECK_EQUAL( particle.getZDirection(), 1.0/sqrt(2.0) );

  // Verify that the particle is in the correct cell in the new model
  FRENSIE_CHECK_EQUAL( particle.getCell(), 2 );

  // Extract the particle from the model
  particle.extractFromModel();

  FRENSIE_CHECK( !particle.isEmbeddedInModel( *model ) );

  FRENSIE_CHECK_EQUAL( particle.getCell(), 0 );

  // Embed the particle in a model with the cell specified
  model.reset( new Geometry::InfiniteMediumModel( 3 ) );

  particle.embedInModel( model, 3 );

  // Verify that the particle position and direction are unchanged
  FRENSIE_CHECK_EQUAL( particle.getXPosition(), 0.1 );
  FRENSIE_CHECK_EQUAL( particle.getYPosition(), -10.0 );
  FRENSIE_CHECK_EQUAL( particle.getZPosition(), sqrt(2.0) );
  FRENSIE_CHECK_EQUAL( particle.getXDirection(), 0.0 );
  FRENSIE_CHECK_EQUAL( particle.getYDirection(), -1.0/sqrt(2.0) );
  FRENSIE_CHECK_EQUAL( particle.getZDirection(), 1.0/sqrt(2.0) );

  // Verify that the particle is in the correct cell in the new model
  FRENSIE_CHECK_EQUAL( particle.getCell(), 3 );

  // Extract the particle from the model
  particle.extractFromModel();

  // Embed the particle in a model at a new location and with a new direction
  model.reset( new Geometry::InfiniteMediumModel( 4 ) );

  particle.embedInModel( model,
                         (const double[3]){-1.0, 2.0, -0.3},
                         (const double[3]){1.0, 0.0, 0.0} );

  // Verify that the particle position and direction are correct
  FRENSIE_CHECK_EQUAL( particle.getXPosition(), -1.0 );
  FRENSIE_CHECK_EQUAL( particle.getYPosition(), 2.0 );
  FRENSIE_CHECK_EQUAL( particle.getZPosition(), -0.3 );
  FRENSIE_CHECK_EQUAL( particle.getXDirection(), 1.0 );
  FRENSIE_CHECK_EQUAL( particle.getYDirection(), 0.0 );
  FRENSIE_CHECK_EQUAL( particle.getZDirection(), 0.0 );

  // Verify that the particle is in the correct cell in the new model
  FRENSIE_CHECK_EQUAL( particle.getCell(), 4 );

  // Extract the particle from the model
  particle.extractFromModel();

  // Embed the particle in a model at a new location and with a new direction
  model.reset( new Geometry::InfiniteMediumModel( 5 ) );

  particle.embedInModel( model,
                         (const double[3]){1.0, -2.0, 0.3},
                         (const double[3]){0.0, 0.0, 1.0},
                         5 );

  // Verify that the particle position and direction are correct
  FRENSIE_CHECK_EQUAL( particle.getXPosition(), 1.0 );
  FRENSIE_CHECK_EQUAL( particle.getYPosition(), -2.0 );
  FRENSIE_CHECK_EQUAL( particle.getZPosition(), 0.3 );
  FRENSIE_CHECK_EQUAL( particle.getXDirection(), 0.0 );
  FRENSIE_CHECK_EQUAL( particle.getYDirection(), 0.0 );
  FRENSIE_CHECK_EQUAL( particle.getZDirection(), 1.0 );

  // Verify that the particle is in the correct cell in the new model
  FRENSIE_CHECK_EQUAL( particle.getCell(), 5 );
}

//---------------------------------------------------------------------------//
// Create new particles
FRENSIE_UNIT_TEST( ParticleState, copy_constructor )
{
  TestParticleState particle_gen_a( 1ull );
  particle_gen_a.setSourceId( 10 );
  particle_gen_a.setSourceCell( 1 );
  particle_gen_a.setPosition( 1.0, 1.0, 1.0 );
  particle_gen_a.setDirection( 0.0, 0.0, 1.0 );
  particle_gen_a.setSourceEnergy( 2.0 );
  particle_gen_a.setEnergy( 1.0 );
  particle_gen_a.setSourceTime( 0.0 );
  particle_gen_a.setTime( 1.0 );
  particle_gen_a.incrementCollisionNumber();
  particle_gen_a.setSourceWeight( 1.0 );
  particle_gen_a.setWeight( 0.5 );
  particle_gen_a.setRaySafetyDistance( 1.0 );

  // Create a second generation particle with the same collision number
  TestParticleState particle_gen_b( particle_gen_a, true );

  FRENSIE_CHECK_EQUAL( particle_gen_b.getSourceId(),
                 particle_gen_a.getSourceId() );
  FRENSIE_CHECK_EQUAL( particle_gen_b.getXPosition(),
                 particle_gen_a.getXPosition() );
  FRENSIE_CHECK_EQUAL( particle_gen_b.getYPosition(),
                 particle_gen_a.getYPosition() );
  FRENSIE_CHECK_EQUAL( particle_gen_b.getZPosition(),
                 particle_gen_a.getZPosition() );
  FRENSIE_CHECK_EQUAL( particle_gen_b.getXDirection(),
                 particle_gen_a.getXDirection() );
  FRENSIE_CHECK_EQUAL( particle_gen_b.getYDirection(),
                 particle_gen_a.getYDirection() );
  FRENSIE_CHECK_EQUAL( particle_gen_b.getZDirection(),
                 particle_gen_a.getZDirection() );
  FRENSIE_CHECK_EQUAL( particle_gen_b.getSourceEnergy(),
                 particle_gen_a.getSourceEnergy() );
  FRENSIE_CHECK_EQUAL( particle_gen_b.getEnergy(),
                 particle_gen_a.getEnergy() );
  FRENSIE_CHECK_EQUAL( particle_gen_b.getCharge(),
                 particle_gen_a.getCharge() );
  FRENSIE_CHECK_EQUAL( particle_gen_b.getSourceTime(),
                 particle_gen_a.getSourceTime() );
  FRENSIE_CHECK_EQUAL( particle_gen_b.getTime(),
                 particle_gen_a.getTime() );
  FRENSIE_CHECK_EQUAL( particle_gen_b.getCollisionNumber(),
                 particle_gen_a.getCollisionNumber() );
  FRENSIE_CHECK_EQUAL( particle_gen_b.getGenerationNumber(),
                 particle_gen_a.getGenerationNumber()+1u );
  FRENSIE_CHECK_EQUAL( particle_gen_b.getSourceWeight(),
                 particle_gen_a.getSourceWeight() );
  FRENSIE_CHECK_EQUAL( particle_gen_b.getWeight(),
                 particle_gen_a.getWeight() );
  FRENSIE_CHECK_EQUAL( particle_gen_b.getRaySafetyDistance(),
                 particle_gen_a.getRaySafetyDistance() );
  FRENSIE_CHECK_EQUAL( particle_gen_b.getSourceCell(),
                 particle_gen_a.getSourceCell() );
  FRENSIE_CHECK_EQUAL( particle_gen_b.getCell(),
                 particle_gen_a.getCell() );

  // Create a third generation particle and reset the collision counter
  TestParticleState particle_gen_c( particle_gen_b, true, true );

  FRENSIE_CHECK_EQUAL( particle_gen_c.getSourceId(),
                 particle_gen_b.getSourceId() );
  FRENSIE_CHECK_EQUAL( particle_gen_c.getXPosition(),
                 particle_gen_b.getXPosition() );
  FRENSIE_CHECK_EQUAL( particle_gen_c.getYPosition(),
                 particle_gen_b.getYPosition() );
  FRENSIE_CHECK_EQUAL( particle_gen_c.getZPosition(),
                 particle_gen_b.getZPosition() );
  FRENSIE_CHECK_EQUAL( particle_gen_c.getXDirection(),
                 particle_gen_b.getXDirection() );
  FRENSIE_CHECK_EQUAL( particle_gen_c.getYDirection(),
                 particle_gen_b.getYDirection() );
  FRENSIE_CHECK_EQUAL( particle_gen_c.getZDirection(),
                 particle_gen_b.getZDirection() );
  FRENSIE_CHECK_EQUAL( particle_gen_c.getSourceEnergy(),
                 particle_gen_b.getSourceEnergy() );
  FRENSIE_CHECK_EQUAL( particle_gen_c.getEnergy(),
                 particle_gen_b.getEnergy() );
  FRENSIE_CHECK_EQUAL( particle_gen_c.getCharge(),
                 particle_gen_b.getCharge() );
  FRENSIE_CHECK_EQUAL( particle_gen_c.getSourceTime(),
                 particle_gen_b.getSourceTime() );
  FRENSIE_CHECK_EQUAL( particle_gen_c.getTime(),
                 particle_gen_b.getTime() );
  FRENSIE_CHECK_EQUAL( particle_gen_c.getCollisionNumber(), 0u );
  FRENSIE_CHECK_EQUAL( particle_gen_c.getGenerationNumber(),
                 particle_gen_b.getGenerationNumber()+1u );
  FRENSIE_CHECK_EQUAL( particle_gen_c.getSourceWeight(),
                 particle_gen_b.getSourceWeight() );
  FRENSIE_CHECK_EQUAL( particle_gen_c.getWeight(),
                 particle_gen_b.getWeight() );
  FRENSIE_CHECK_EQUAL( particle_gen_c.getSourceCell(),
                 particle_gen_b.getSourceCell() );
  FRENSIE_CHECK_EQUAL( particle_gen_c.getCell(),
                 particle_gen_b.getCell() );

  // Create a second third generation particle after the second gen particle
  // has been set to gone
  particle_gen_b.setAsGone();

  TestParticleState particle_gen_2c( particle_gen_b, true );

  FRENSIE_CHECK( !particle_gen_2c.isGone() );
  FRENSIE_CHECK( !particle_gen_2c.isLost() );

  // Create a second second generation particle after the first gen particle
  // has been set to lost
  particle_gen_a.setAsLost();

  TestParticleState particle_gen_2b( particle_gen_a, true );

  FRENSIE_CHECK( !particle_gen_2b.isGone() );
  FRENSIE_CHECK( !particle_gen_2b.isLost() );
}

//---------------------------------------------------------------------------//
// Check that a particle can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( ParticleState, archive, TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_particle_state" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    TestParticleState particle( 1ull );
    particle.setSourceId( 10 );
    particle.setSourceCell( 1 );
    particle.setPosition( 1.0, 1.0, 1.0 );
    particle.setDirection( 0.0, 0.0, 1.0 );
    particle.setSourceEnergy( 2.0 );
    particle.setEnergy( 1.0 );
    particle.setSourceTime( 0.0 );
    particle.setTime( 0.5 );
    particle.incrementCollisionNumber();
    particle.setSourceWeight( 1.0 );
    particle.setWeight( 0.25 );
    particle.setRaySafetyDistance( 0.5 );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( particle ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  TestParticleState particle( 10ull );

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( particle ) );

  FRENSIE_CHECK_EQUAL( particle.getSourceId(), 10 );
  FRENSIE_CHECK_EQUAL( particle.getSourceCell(), 1 );
  FRENSIE_CHECK_EQUAL( particle.getCell(), 0 );
  FRENSIE_CHECK_EQUAL( particle.getXPosition(), 1.0 );
  FRENSIE_CHECK_EQUAL( particle.getYPosition(), 1.0 );
  FRENSIE_CHECK_EQUAL( particle.getZPosition(), 1.0 );
  FRENSIE_CHECK_EQUAL( particle.getXDirection(), 0.0 );
  FRENSIE_CHECK_EQUAL( particle.getYDirection(), 0.0 );
  FRENSIE_CHECK_EQUAL( particle.getZDirection(), 1.0 );
  FRENSIE_CHECK_EQUAL( particle.getSourceEnergy(), 2.0 );
  FRENSIE_CHECK_EQUAL( particle.getEnergy(), 1.0 );
  FRENSIE_CHECK_EQUAL( particle.getCharge(), 1 );
  FRENSIE_CHECK_EQUAL( particle.getSourceTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( particle.getTime(), 0.5 );
  FRENSIE_CHECK_EQUAL( particle.getCollisionNumber(), 1.0 );
  FRENSIE_CHECK_EQUAL( particle.getGenerationNumber(), 0.0 );
  FRENSIE_CHECK_EQUAL( particle.getSourceWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( particle.getWeight(), 0.25 );
  FRENSIE_CHECK_EQUAL( particle.getRaySafetyDistance(), 0.5 );
  FRENSIE_CHECK_EQUAL( particle.getHistoryNumber(), 1ull );
}

//---------------------------------------------------------------------------//
// end tstParticleState.cpp
//---------------------------------------------------------------------------//
