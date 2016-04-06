//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointElectronProbeState.cpp
//! \author Luke Kersting
//! \brief  Adjoint electron probe state unit tests
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
#include "MonteCarlo_AdjointElectronProbeState.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Get the particle type
TEUCHOS_UNIT_TEST( AdjointElectronProbeState, getParticleType )
{
  MonteCarlo::AdjointElectronProbeState particle( 1ull );

  TEST_EQUALITY_CONST( particle.getParticleType(), 
		       MonteCarlo::ADJOINT_ELECTRON_PROBE );
}

//---------------------------------------------------------------------------//
// Get the particle speed
TEUCHOS_UNIT_TEST( AdjointElectronProbeState, getSpeed )
{
  MonteCarlo::AdjointElectronProbeState particle( 1ull );

  particle.setEnergy( 1.0 );
 
  double speed_of_light = Utility::PhysicalConstants::speed_of_light;
  double rest_mass = Utility::PhysicalConstants::electron_rest_mass_energy;
 
  TEST_FLOATING_EQUALITY( particle.getSpeed(),
                          speed_of_light * sqrt( 1.0 - rest_mass * rest_mass /
                          ((1.0 + rest_mass) * (1.0 + rest_mass))),
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Set the particle speed
TEUCHOS_UNIT_TEST( AdjointElectronProbeState, setSpeed )
{
  MonteCarlo::AdjointElectronProbeState particle( 1ull );

  double speed_of_light = Utility::PhysicalConstants::speed_of_light;
  double rest_mass = Utility::PhysicalConstants::electron_rest_mass_energy;
 
  particle.setSpeed( speed_of_light * sqrt( 1 - rest_mass * rest_mass /
                     ((1 + rest_mass) * (1 + rest_mass))) );

  TEST_FLOATING_EQUALITY( particle.getEnergy(), 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint electron probe can be activated
TEUCHOS_UNIT_TEST( AdjointElectronProbeState, activate )
{
  MonteCarlo::AdjointElectronProbeState particle( 1ull );

  TEST_ASSERT( !particle.isActive() );

  particle.activate();

  TEST_ASSERT( particle.isActive() );
}

//---------------------------------------------------------------------------//
// Check that the adjoint electron probe behaves correctly when its energy is set
TEUCHOS_UNIT_TEST( AdjointElectronProbeState, setEnergy )
{
  MonteCarlo::AdjointElectronProbeState particle_a( 1ull );

  particle_a.setEnergy( 0.1 );

  TEST_ASSERT( !particle_a.isActive() );
  TEST_ASSERT( !particle_a.isGone() );

  particle_a.activate();

  TEST_ASSERT( particle_a.isActive() );
  TEST_ASSERT( !particle_a.isGone() );
  
  particle_a.setEnergy( 1.0 );

  TEST_ASSERT( particle_a.isActive() );
  TEST_ASSERT( particle_a.isGone() );

  MonteCarlo::AdjointElectronProbeState particle_b( particle_a, true );

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
TEUCHOS_UNIT_TEST( AdjointElectronProbeState, advance )
{
  const double position[3] = {1.0, 1.0, 1.0};
  const double direction[3] = {0.5773502691896258, 
			       0.5773502691896258,
			       0.5773502691896258};
  
  MonteCarlo::AdjointElectronProbeState particle( 1ull );
  particle.setPosition( position );
  particle.setDirection( direction );
  particle.setEnergy( 1.0 );
  particle.setTime( 0.0 );
  
  particle.advance( 1.7320508075688772 );

  double speed_of_light = Utility::PhysicalConstants::speed_of_light;
  double rest_mass = Utility::PhysicalConstants::electron_rest_mass_energy;

  TEST_FLOATING_EQUALITY( particle.getXPosition(), 2.0, 1e-12 );
  TEST_FLOATING_EQUALITY( particle.getYPosition(), 2.0, 1e-12 );
  TEST_FLOATING_EQUALITY( particle.getZPosition(), 2.0, 1e-12 );
  TEST_FLOATING_EQUALITY( particle.getTime(), 
                          1.7320508075688772 / ( speed_of_light * sqrt( 1 - rest_mass * rest_mass /
                          ((1 + rest_mass) * (1 + rest_mass)))), 
                          1e-12 );
}


//---------------------------------------------------------------------------//
// Check if the particle is a probe
TEUCHOS_UNIT_TEST( AdjointElectronProbeState, isProbe )
{
  MonteCarlo::AdjointElectronProbeState particle( 1ull );

  TEST_ASSERT( particle.isProbe() );
}

//---------------------------------------------------------------------------//
// Check that the particle can be cloned
TEUCHOS_UNIT_TEST( AdjointElectronProbeState, clone )
{
  boost::shared_ptr<MonteCarlo::ParticleState> particle( 
			     new MonteCarlo::AdjointElectronProbeState( 0ull ) );
  particle->setPosition( 1.0, 1.0, 1.0 );
  particle->setDirection( 0.0, 0.0, 1.0 );
  particle->setEnergy( 1.0 );
  particle->setTime( 0.5 );
  particle->incrementCollisionNumber();
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
  TEST_EQUALITY_CONST( particle_clone->getCollisionNumber(), 1 );
  TEST_EQUALITY_CONST( particle_clone->getGenerationNumber(), 0 );
  TEST_EQUALITY_CONST( particle_clone->getWeight(), 0.25 );
  TEST_EQUALITY_CONST( particle_clone->getHistoryNumber(), 0ull );
  TEST_EQUALITY_CONST( particle_clone->getParticleType(), 
		       MonteCarlo::ADJOINT_ELECTRON_PROBE );
}

//---------------------------------------------------------------------------//
// Check that the particle can be cloned
TEUCHOS_UNIT_TEST( AdjointElectronProbeState, clone_new_hist )
{
  boost::shared_ptr<MonteCarlo::ParticleState> particle( 
			     new MonteCarlo::AdjointElectronProbeState( 0ull ) );
  particle->setPosition( 1.0, 1.0, 1.0 );
  particle->setDirection( 0.0, 0.0, 1.0 );
  particle->setEnergy( 1.0 );
  particle->setTime( 0.5 );
  particle->incrementCollisionNumber();
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
  TEST_EQUALITY_CONST( particle_clone->getCollisionNumber(), 1 );
  TEST_EQUALITY_CONST( particle_clone->getGenerationNumber(), 0 );
  TEST_EQUALITY_CONST( particle_clone->getWeight(), 0.25 );
  TEST_EQUALITY_CONST( particle_clone->getHistoryNumber(), 10ull );
  TEST_EQUALITY_CONST( particle_clone->getParticleType(), 
		       MonteCarlo::ADJOINT_ELECTRON_PROBE );
}

//---------------------------------------------------------------------------//
// Archive an adjoint electron probe state
TEUCHOS_UNIT_TEST( AdjointElectronProbeState, archive )
{
  // Create and archive an adjoint electron probe
  {
    MonteCarlo::AdjointElectronProbeState particle( 1ull );
    particle.setPosition( 1.0, 1.0, 1.0 );
    particle.setDirection( 0.0, 0.0, 1.0 );
    particle.setEnergy( 1.0 );
    particle.setTime( 0.5 );
    particle.incrementCollisionNumber();
    particle.setWeight( 0.25 );
    particle.activate();

    std::ofstream ofs( "test_adjoint_electron_probe_state_archive.xml" );

    boost::archive::xml_oarchive ar(ofs);
    ar << BOOST_SERIALIZATION_NVP( particle );
  }
  
  // Load the archived particle
  MonteCarlo::AdjointElectronProbeState loaded_particle;

  std::ifstream ifs( "test_adjoint_electron_probe_state_archive.xml" );

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
		       MonteCarlo::ADJOINT_ELECTRON_PROBE );
}

//---------------------------------------------------------------------------//
// Create new particles
TEUCHOS_UNIT_TEST( AdjointElectronProbeState, copy_constructor )
{
  MonteCarlo::AdjointElectronProbeState particle_gen_a( 1ull );
  particle_gen_a.setPosition( 1.0, 1.0, 1.0 );
  particle_gen_a.setPosition( 0.0, 0.0, 1.0 );
  particle_gen_a.setEnergy( 1.0 );
  particle_gen_a.setTime( 1.0 );
  particle_gen_a.incrementCollisionNumber();
  particle_gen_a.setWeight( 0.5 );

  MonteCarlo::AdjointElectronProbeState particle_gen_a_copy( particle_gen_a );
  
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
  MonteCarlo::AdjointElectronProbeState particle_gen_b( particle_gen_a, true );

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
  MonteCarlo::AdjointElectronProbeState particle_gen_c( particle_gen_b, true, true );

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
TEUCHOS_UNIT_TEST( AdjointElectronProbeState, probe_nonprobe_copy_constructor )
{
  MonteCarlo::AdjointElectronState particle_gen_a( 1ull );
  particle_gen_a.setPosition( 1.0, 1.0, 1.0 );
  particle_gen_a.setPosition( 0.0, 0.0, 1.0 );
  particle_gen_a.setEnergy( 1.0 );
  particle_gen_a.setTime( 1.0 );
  particle_gen_a.incrementCollisionNumber();
  particle_gen_a.setWeight( 0.5 );

  MonteCarlo::AdjointElectronProbeState probe_gen_a( particle_gen_a );

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

  MonteCarlo::AdjointElectronState particle_gen_b( probe_gen_a, true );
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
// end tstAdjointElectronProbeState.cpp
//---------------------------------------------------------------------------//

