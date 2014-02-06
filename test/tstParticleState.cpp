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

// Moab Includes
#include <moab/EntityHandle.hpp>

// FACEMC Includes
#include "ParticleState.hpp"

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name )		  \
  typedef unsigned long long ull;			  \
  typedef moab::EntityHandle eh;			  \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, ull ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, eh ) 

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Get the particle type
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ParticleState,
				   getParticleType,
				   CellHandle )
{
  FACEMC::ParticleState<CellHandle> particle( 1ull );
  particle.setParticleType( FACEMC::PHOTON );
  
  TEST_EQUALITY_CONST( particle.getParticleType(), FACEMC::PHOTON );
}

UNIT_TEST_INSTANTIATION( ParticleState, getParticleType );

//---------------------------------------------------------------------------//
// Get the history number
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ParticleState,
				   getHistoryNumber,
				   CellHandle )
{
  FACEMC::ParticleState<CellHandle> particle( 1ull );

  TEST_EQUALITY_CONST( particle.getHistoryNumber(), 1ull );
}

UNIT_TEST_INSTANTIATION( ParticleState, getHistoryNumber );

//---------------------------------------------------------------------------//
// Set/get the energy of a particle
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ParticleState,
				   setgetEnergy,
				   CellHandle )
{
  FACEMC::ParticleState<CellHandle> particle( 1ull );
  
  particle.setEnergy( 1.0 );
  
  TEST_EQUALITY_CONST( particle.getEnergy(), 1.0 );
}
	
UNIT_TEST_INSTANTIATION( ParticleState, setgetEnergy );

//---------------------------------------------------------------------------//
// Set/get the position of a particle
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ParticleState,
				   setgetPosition,
				   CellHandle )
{
  FACEMC::ParticleState<CellHandle> particle( 1ull );
  
  particle.setPosition( 1.0, 1.0, 1.0 );

  TEST_EQUALITY_CONST( particle.getXPosition(), 1.0 );
  TEST_EQUALITY_CONST( particle.getYPosition(), 1.0 );
  TEST_EQUALITY_CONST( particle.getZPosition(), 1.0 );

  const double* position = particle.getPosition();

  TEST_EQUALITY_CONST( position[0], 1.0 );
  TEST_EQUALITY_CONST( position[1], 1.0 );
  TEST_EQUALITY_CONST( position[2], 1.0 );
}

UNIT_TEST_INSTANTIATION( ParticleState, setgetPosition );

//---------------------------------------------------------------------------//
// Set/get the direction of a particle
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ParticleState,
				   setgetDirection,
				   CellHandle )
{
  FACEMC::ParticleState<CellHandle> particle( 1ull );
  
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

UNIT_TEST_INSTANTIATION( ParticleState, setgetDirection );

//---------------------------------------------------------------------------//
// Advance a particle along its direction by a specified distance
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ParticleState,
				   advance,
				   CellHandle )
{
  FACEMC::ParticleState<CellHandle> particle( 1ull );

  particle.setPosition( 1.0, 1.0, 1.0 );
  particle.setDirection( 0.5773502691896258, 
			 0.5773502691896258,
			 0.5773502691896258 );
  
  particle.advance( 1.7320508075688772 );

  TEST_FLOATING_EQUALITY( particle.getXPosition(), 2.0, 1e-12 );
  TEST_FLOATING_EQUALITY( particle.getYPosition(), 2.0, 1e-12 );
  TEST_FLOATING_EQUALITY( particle.getZPosition(), 2.0, 1e-12 );
}

UNIT_TEST_INSTANTIATION( ParticleState, advance );

//---------------------------------------------------------------------------//
// Set/get the cell containing a particle
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ParticleState,
				   setgetCell,
				   CellHandle )
{
  FACEMC::ParticleState<CellHandle> particle( 1ull );

  particle.setCell( 1 );

  TEST_EQUALITY_CONST( particle.getCell(), 1 );
}

UNIT_TEST_INSTANTIATION( ParticleState, setgetCell );

//---------------------------------------------------------------------------//
// Test if a particle is lost
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ParticleState,
				   lost,
				   CellHandle )
{
  FACEMC::ParticleState<CellHandle> particle( 1ull );

  TEST_ASSERT( !particle.isLost() );

  particle.setAsLost();

  TEST_ASSERT( particle.isLost() );
}

UNIT_TEST_INSTANTIATION( ParticleState, lost );

//---------------------------------------------------------------------------//
// Test if a particle is gone
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ParticleState,
				   gone,
				   CellHandle )
{
  FACEMC::ParticleState<CellHandle> particle( 1ull );

  TEST_ASSERT( !particle.isGone() );

  particle.setAsGone();
  
  TEST_ASSERT( particle.isGone() );
}

UNIT_TEST_INSTANTIATION( ParticleState, gone );

//---------------------------------------------------------------------------//
// Spawn a child state
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ParticleState,
				   spawnChildState,
				   CellHandle )
{
  FACEMC::ParticleState<CellHandle> particle( 1ull );

  particle.setEnergy( 1.0 );
  particle.setPosition( 1.0, 1.0, 1.0 );
  particle.setDirection( 0.5773502691896258,
			 0.5773502691896258,
			 0.5773502691896258 );
  particle.setCell( 1 );

  typename FACEMC::ParticleState<CellHandle>::ParticleStatePtr 
    child_particle_1 = particle.spawnChildState( FACEMC::NEUTRON );
  typename FACEMC::ParticleState<CellHandle>::ParticleStatePtr 
    child_particle_2 = particle.spawnChildState();

  TEST_EQUALITY_CONST( child_particle_1->getParticleType(), FACEMC::NEUTRON );
  TEST_EQUALITY_CONST( child_particle_1->getHistoryNumber(), 1ull );
  TEST_EQUALITY_CONST( child_particle_1->getEnergy(), 1.0 );
  TEST_EQUALITY_CONST( child_particle_1->getXPosition(), 1.0 );
  TEST_EQUALITY_CONST( child_particle_1->getYPosition(), 1.0 );
  TEST_EQUALITY_CONST( child_particle_1->getZPosition(), 1.0 );
  TEST_EQUALITY_CONST( child_particle_1->getXDirection(), 0.5773502691896258 );
  TEST_EQUALITY_CONST( child_particle_1->getYDirection(), 0.5773502691896258 );
  TEST_EQUALITY_CONST( child_particle_1->getZDirection(), 0.5773502691896258 );
  TEST_ASSERT( !child_particle_1->isLost() );
  TEST_ASSERT( !child_particle_1->isGone() );
  
  TEST_EQUALITY_CONST( child_particle_2->getParticleType(), FACEMC::PHOTON );
  TEST_EQUALITY_CONST( child_particle_2->getHistoryNumber(), 1ull );
  TEST_EQUALITY_CONST( child_particle_2->getEnergy(), 1.0 );
  TEST_EQUALITY_CONST( child_particle_2->getXPosition(), 1.0 );
  TEST_EQUALITY_CONST( child_particle_2->getYPosition(), 1.0 );
  TEST_EQUALITY_CONST( child_particle_2->getZPosition(), 1.0 );
  TEST_EQUALITY_CONST( child_particle_2->getXDirection(), 0.5773502691896258 );
  TEST_EQUALITY_CONST( child_particle_2->getYDirection(), 0.5773502691896258 );
  TEST_EQUALITY_CONST( child_particle_2->getZDirection(), 0.5773502691896258 );
  TEST_ASSERT( !child_particle_2->isLost() );
  TEST_ASSERT( !child_particle_2->isGone() );
}

UNIT_TEST_INSTANTIATION( ParticleState, spawnChildState );

//---------------------------------------------------------------------------//
// Test if a particle is the root history
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ParticleState,
				   isRootHistory,
				   CellHandle )
{
  FACEMC::ParticleState<CellHandle> particle( 1ull );

  particle.setEnergy( 1.0 );
  particle.setPosition( 1.0, 1.0, 1.0 );
  particle.setDirection( 0.5773502691896258,
			 0.5773502691896258,
			 0.5773502691896258 );
  particle.setCell( 1 );

  typename FACEMC::ParticleState<CellHandle>::ParticleStatePtr 
    child_particle_1 = particle.spawnChildState( FACEMC::NEUTRON );
  typename FACEMC::ParticleState<CellHandle>::ParticleStatePtr 
    child_particle_2 = particle.spawnChildState();

  TEST_ASSERT( particle.isRootHistory() );
  TEST_ASSERT( !child_particle_1->isRootHistory() );
  TEST_ASSERT( !child_particle_2->isRootHistory() );
}

UNIT_TEST_INSTANTIATION( ParticleState, isRootHistory );

//---------------------------------------------------------------------------//
// end tstParticleState.cpp
//---------------------------------------------------------------------------//
