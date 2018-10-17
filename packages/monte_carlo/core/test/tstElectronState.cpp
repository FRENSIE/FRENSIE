//---------------------------------------------------------------------------//
//!
//! \file   tstElectronState.cpp
//! \author Luke Kersting
//! \brief  Electron state unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_ElectronState.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types.
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Get the particle type
FRENSIE_UNIT_TEST( ElectronState, getParticleType )
{
  MonteCarlo::ElectronState particle( 1ull );

  FRENSIE_CHECK_EQUAL( particle.getParticleType(), MonteCarlo::ELECTRON );
}

//---------------------------------------------------------------------------//
// Get the particle charge
FRENSIE_UNIT_TEST( ElectronState, getCharge )
{
  MonteCarlo::ElectronState particle( 1ull );

  FRENSIE_CHECK_EQUAL( particle.getCharge(), -1 );
}

//---------------------------------------------------------------------------//
// Get the particle speed
FRENSIE_UNIT_TEST( ElectronState, getSpeed )
{
  MonteCarlo::ElectronState particle( 1ull );

  particle.setEnergy( 1.0 );

  double speed_of_light = Utility::PhysicalConstants::speed_of_light;
  double rest_mass = Utility::PhysicalConstants::electron_rest_mass_energy;

  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getSpeed(),
                          speed_of_light * sqrt( 1.0 - rest_mass * rest_mass /
                          ((1.0 + rest_mass) * (1.0 + rest_mass))),
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Set the particle speed
FRENSIE_UNIT_TEST( ElectronState, setSpeed )
{
  MonteCarlo::ElectronState particle( 1ull );

  double speed_of_light = Utility::PhysicalConstants::speed_of_light;
  double rest_mass = Utility::PhysicalConstants::electron_rest_mass_energy;

  particle.setSpeed( speed_of_light * sqrt( 1 - rest_mass * rest_mass /
                     ((1 + rest_mass) * (1 + rest_mass))) );

  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getEnergy(), 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Advance the particle along its direction by a specified distance
FRENSIE_UNIT_TEST( ElectronState, advance )
{
  const double position[3] = {1.0, 1.0, 1.0};
  const double direction[3] = {0.5773502691896258,
			       0.5773502691896258,
			       0.5773502691896258};

  MonteCarlo::ElectronState particle( 1ull );
  particle.setPosition( position );
  particle.setDirection( direction );
  particle.setEnergy( 1.0 );
  particle.setTime( 0.0 );

  particle.advance( 1.7320508075688772 );

  double speed_of_light = Utility::PhysicalConstants::speed_of_light;
  double rest_mass = Utility::PhysicalConstants::electron_rest_mass_energy;

  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getXPosition(), 2.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getYPosition(), 2.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getZPosition(), 2.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getTime(),
                          1.7320508075688772 / ( speed_of_light * sqrt( 1 - rest_mass * rest_mass /
                          ((1 + rest_mass) * (1 + rest_mass)))),
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the electron state can be cloned
FRENSIE_UNIT_TEST( ElectronState, clone )
{
  boost::shared_ptr<MonteCarlo::ParticleState> particle(
				       new MonteCarlo::ElectronState( 0ull ) );
  particle->setPosition( 1.0, 1.0, 1.0 );
  particle->setDirection( 0.0, 0.0, 1.0 );
  particle->setEnergy( 1.0 );
  particle->setTime( 0.5 );
  particle->setWeight( 0.25 );
  particle->setRaySafetyDistance( 1.5 );

  boost::shared_ptr<MonteCarlo::ParticleState> particle_clone(
							   particle->clone() );

  FRENSIE_CHECK_EQUAL( particle_clone->getXPosition(), 1.0 );
  FRENSIE_CHECK_EQUAL( particle_clone->getYPosition(), 1.0 );
  FRENSIE_CHECK_EQUAL( particle_clone->getZPosition(), 1.0 );
  FRENSIE_CHECK_EQUAL( particle_clone->getXDirection(), 0.0 );
  FRENSIE_CHECK_EQUAL( particle_clone->getYDirection(), 0.0 );
  FRENSIE_CHECK_EQUAL( particle_clone->getZDirection(), 1.0 );
  FRENSIE_CHECK_EQUAL( particle_clone->getEnergy(), 1.0 );
  FRENSIE_CHECK_EQUAL( particle_clone->getCharge(), -1 );
  FRENSIE_CHECK_EQUAL( particle_clone->getTime(), 0.5 );
  FRENSIE_CHECK_EQUAL( particle_clone->getCollisionNumber(), 0 );
  FRENSIE_CHECK_EQUAL( particle_clone->getGenerationNumber(), 0 );
  FRENSIE_CHECK_EQUAL( particle_clone->getWeight(), 0.25 );
  FRENSIE_CHECK_EQUAL( particle_clone->getRaySafetyDistance(), 1.5 );
  FRENSIE_CHECK_EQUAL( particle_clone->getHistoryNumber(), 0ull );
  FRENSIE_CHECK_EQUAL( particle_clone->getParticleType(),
		       MonteCarlo::ELECTRON );
}

//---------------------------------------------------------------------------//
// Check that the electron state can be cloned with a new history number
FRENSIE_UNIT_TEST( ElectronState, clone_new_hist )
{
  boost::shared_ptr<MonteCarlo::ParticleState> particle(
				       new MonteCarlo::ElectronState( 0ull ) );
  particle->setPosition( 1.0, 1.0, 1.0 );
  particle->setDirection( 0.0, 0.0, 1.0 );
  particle->setEnergy( 1.0 );
  particle->setTime( 0.5 );
  particle->setWeight( 0.25 );
  particle->setRaySafetyDistance( 1.5 );

  boost::shared_ptr<MonteCarlo::ParticleState> particle_clone(
						    particle->clone( 10ull ) );

  FRENSIE_CHECK_EQUAL( particle_clone->getXPosition(), 1.0 );
  FRENSIE_CHECK_EQUAL( particle_clone->getYPosition(), 1.0 );
  FRENSIE_CHECK_EQUAL( particle_clone->getZPosition(), 1.0 );
  FRENSIE_CHECK_EQUAL( particle_clone->getXDirection(), 0.0 );
  FRENSIE_CHECK_EQUAL( particle_clone->getYDirection(), 0.0 );
  FRENSIE_CHECK_EQUAL( particle_clone->getZDirection(), 1.0 );
  FRENSIE_CHECK_EQUAL( particle_clone->getEnergy(), 1.0 );
  FRENSIE_CHECK_EQUAL( particle_clone->getCharge(), -1 );
  FRENSIE_CHECK_EQUAL( particle_clone->getTime(), 0.5 );
  FRENSIE_CHECK_EQUAL( particle_clone->getCollisionNumber(), 0 );
  FRENSIE_CHECK_EQUAL( particle_clone->getGenerationNumber(), 0 );
  FRENSIE_CHECK_EQUAL( particle_clone->getWeight(), 0.25 );
  FRENSIE_CHECK_EQUAL( particle_clone->getRaySafetyDistance(), 1.5 );
  FRENSIE_CHECK_EQUAL( particle_clone->getHistoryNumber(), 10ull );
  FRENSIE_CHECK_EQUAL( particle_clone->getParticleType(),
		       MonteCarlo::ELECTRON );
}

//---------------------------------------------------------------------------//
// Create new particles
FRENSIE_UNIT_TEST( ElectronState, copy_constructor )
{
  MonteCarlo::ElectronState particle_gen_a( 1ull );
  particle_gen_a.setPosition( 1.0, 1.0, 1.0 );
  particle_gen_a.setDirection( 0.0, 0.0, 1.0 );
  particle_gen_a.setEnergy( 1.0 );
  particle_gen_a.setTime( 1.0 );
  particle_gen_a.incrementCollisionNumber();
  particle_gen_a.setWeight( 0.5 );
  particle_gen_a.setRaySafetyDistance( 1.5 );

  MonteCarlo::ElectronState particle_gen_a_copy( particle_gen_a );

  FRENSIE_CHECK_EQUAL( particle_gen_a_copy.getXPosition(),
		 particle_gen_a.getXPosition() );
  FRENSIE_CHECK_EQUAL( particle_gen_a_copy.getYPosition(),
		 particle_gen_a.getYPosition() );
  FRENSIE_CHECK_EQUAL( particle_gen_a_copy.getZPosition(),
		 particle_gen_a.getZPosition() );
  FRENSIE_CHECK_EQUAL( particle_gen_a_copy.getXDirection(),
		 particle_gen_a.getXDirection() );
  FRENSIE_CHECK_EQUAL( particle_gen_a_copy.getYDirection(),
		 particle_gen_a.getYDirection() );
  FRENSIE_CHECK_EQUAL( particle_gen_a_copy.getZDirection(),
		 particle_gen_a.getZDirection() );
  FRENSIE_CHECK_EQUAL( particle_gen_a_copy.getEnergy(),
		 particle_gen_a.getEnergy() );
  FRENSIE_CHECK_EQUAL( particle_gen_a_copy.getCharge(),
		 particle_gen_a.getCharge() );
  FRENSIE_CHECK_EQUAL( particle_gen_a_copy.getSpeed(),
		 particle_gen_a.getSpeed() );
  FRENSIE_CHECK_EQUAL( particle_gen_a_copy.getTime(),
		 particle_gen_a.getTime() );
  FRENSIE_CHECK_EQUAL( particle_gen_a_copy.getCollisionNumber(),
		 particle_gen_a.getCollisionNumber() );
  FRENSIE_CHECK_EQUAL( particle_gen_a_copy.getGenerationNumber(),
		 particle_gen_a.getGenerationNumber() );
  FRENSIE_CHECK_EQUAL( particle_gen_a_copy.getWeight(),
		 particle_gen_a.getWeight() );
  FRENSIE_CHECK_EQUAL( particle_gen_a_copy.getRaySafetyDistance(),
		 particle_gen_a.getRaySafetyDistance() );

  //Create a second generation particle with the same collision number
  MonteCarlo::ElectronState particle_gen_b( particle_gen_a, true );

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
  FRENSIE_CHECK_EQUAL( particle_gen_b.getEnergy(),
		 particle_gen_a.getEnergy() );
  FRENSIE_CHECK_EQUAL( particle_gen_b.getCharge(),
		 particle_gen_a.getCharge() );
  FRENSIE_CHECK_EQUAL( particle_gen_b.getSpeed(),
		 particle_gen_a.getSpeed() );
  FRENSIE_CHECK_EQUAL( particle_gen_b.getTime(),
		 particle_gen_a.getTime() );
  FRENSIE_CHECK_EQUAL( particle_gen_b.getCollisionNumber(),
		 particle_gen_a.getCollisionNumber() );
  FRENSIE_CHECK_EQUAL( particle_gen_b.getGenerationNumber(),
		 particle_gen_a.getGenerationNumber()+1u );
  FRENSIE_CHECK_EQUAL( particle_gen_b.getWeight(),
		 particle_gen_a.getWeight() );
  FRENSIE_CHECK_EQUAL( particle_gen_b.getRaySafetyDistance(),
		 particle_gen_a.getRaySafetyDistance() );

  // Create a third generation particle and reset the collision counter
  MonteCarlo::ElectronState particle_gen_c( particle_gen_b, true, true );

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
  FRENSIE_CHECK_EQUAL( particle_gen_c.getEnergy(),
		 particle_gen_b.getEnergy() );
  FRENSIE_CHECK_EQUAL( particle_gen_c.getCharge(),
		 particle_gen_b.getCharge() );
  FRENSIE_CHECK_EQUAL( particle_gen_c.getSpeed(),
		 particle_gen_b.getSpeed() );
  FRENSIE_CHECK_EQUAL( particle_gen_c.getTime(),
		 particle_gen_b.getTime() );
  FRENSIE_CHECK_EQUAL( particle_gen_c.getCollisionNumber(), 0u );
  FRENSIE_CHECK_EQUAL( particle_gen_c.getGenerationNumber(),
		 particle_gen_b.getGenerationNumber()+1u );
  FRENSIE_CHECK_EQUAL( particle_gen_c.getWeight(),
		 particle_gen_b.getWeight() );
  FRENSIE_CHECK_EQUAL( particle_gen_c.getRaySafetyDistance(),
		 particle_gen_b.getRaySafetyDistance() );
}

//---------------------------------------------------------------------------//
// Create new particles
FRENSIE_UNIT_TEST( ElectronState, assignment_operator )
{
  MonteCarlo::ElectronState particle_gen_a( 1ull );
  particle_gen_a.setPosition( 1.0, 1.0, 1.0 );
  particle_gen_a.setDirection( 0.0, 0.0, 1.0 );
  particle_gen_a.setEnergy( 1.0 );
  particle_gen_a.setTime( 1.0 );
  particle_gen_a.incrementCollisionNumber();
  particle_gen_a.setWeight( 0.5 );
  particle_gen_a.setRaySafetyDistance( 1.5 );

  MonteCarlo::ElectronState particle_gen_a_copy = particle_gen_a;

  FRENSIE_CHECK_EQUAL( particle_gen_a_copy.getXPosition(),
		 particle_gen_a.getXPosition() );
  FRENSIE_CHECK_EQUAL( particle_gen_a_copy.getYPosition(),
		 particle_gen_a.getYPosition() );
  FRENSIE_CHECK_EQUAL( particle_gen_a_copy.getZPosition(),
		 particle_gen_a.getZPosition() );
  FRENSIE_CHECK_EQUAL( particle_gen_a_copy.getXDirection(),
		 particle_gen_a.getXDirection() );
  FRENSIE_CHECK_EQUAL( particle_gen_a_copy.getYDirection(),
		 particle_gen_a.getYDirection() );
  FRENSIE_CHECK_EQUAL( particle_gen_a_copy.getZDirection(),
		 particle_gen_a.getZDirection() );
  FRENSIE_CHECK_EQUAL( particle_gen_a_copy.getEnergy(),
		 particle_gen_a.getEnergy() );
  FRENSIE_CHECK_EQUAL( particle_gen_a_copy.getCharge(),
		 particle_gen_a.getCharge() );
  FRENSIE_CHECK_EQUAL( particle_gen_a_copy.getTime(),
		 particle_gen_a.getTime() );
  FRENSIE_CHECK_EQUAL( particle_gen_a_copy.getCollisionNumber(),
		 particle_gen_a.getCollisionNumber() );
  FRENSIE_CHECK_EQUAL( particle_gen_a_copy.getGenerationNumber(),
		 particle_gen_a.getGenerationNumber() );
  FRENSIE_CHECK_EQUAL( particle_gen_a_copy.getWeight(),
		 particle_gen_a.getWeight() );
  FRENSIE_CHECK_EQUAL( particle_gen_a_copy.getRaySafetyDistance(),
		 particle_gen_a.getRaySafetyDistance() );
}

//---------------------------------------------------------------------------//
// Check that a particle can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( ElectronState, archive, TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_electron_state" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    MonteCarlo::ElectronState particle( 1ull );
    particle.setPosition( 1.0, 1.0, 1.0 );
    particle.setDirection( 0.0, 0.0, 1.0 );
    particle.setEnergy( 1.0 );
    particle.setTime( 0.5 );
    particle.incrementCollisionNumber();
    particle.setWeight( 0.25 );
    particle.setRaySafetyDistance( 1.5 );

    std::shared_ptr<MonteCarlo::ParticleState>
      shared_particle( particle.clone() );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) <<  BOOST_SERIALIZATION_NVP( particle ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( shared_particle ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  MonteCarlo::ElectronState particle( 10ull );

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( particle ) );

  FRENSIE_CHECK_EQUAL( particle.getXPosition(), 1.0 );
  FRENSIE_CHECK_EQUAL( particle.getYPosition(), 1.0 );
  FRENSIE_CHECK_EQUAL( particle.getZPosition(), 1.0 );
  FRENSIE_CHECK_EQUAL( particle.getXDirection(), 0.0 );
  FRENSIE_CHECK_EQUAL( particle.getYDirection(), 0.0 );
  FRENSIE_CHECK_EQUAL( particle.getZDirection(), 1.0 );
  FRENSIE_CHECK_EQUAL( particle.getEnergy(), 1.0 );
  FRENSIE_CHECK_EQUAL( particle.getCharge(), -1 );
  FRENSIE_CHECK_EQUAL( particle.getTime(), 0.5 );
  FRENSIE_CHECK_EQUAL( particle.getCollisionNumber(), 1.0 );
  FRENSIE_CHECK_EQUAL( particle.getGenerationNumber(), 0.0 );
  FRENSIE_CHECK_EQUAL( particle.getWeight(), 0.25 );
  FRENSIE_CHECK_EQUAL( particle.getRaySafetyDistance(), 1.5 );
  FRENSIE_CHECK_EQUAL( particle.getHistoryNumber(), 1ull );
  FRENSIE_CHECK_EQUAL( particle.getParticleType(),
		       MonteCarlo::ELECTRON );

  std::shared_ptr<MonteCarlo::ParticleState> shared_particle;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( shared_particle) );

  FRENSIE_CHECK_EQUAL( shared_particle->getXPosition(), 1.0 );
  FRENSIE_CHECK_EQUAL( shared_particle->getYPosition(), 1.0 );
  FRENSIE_CHECK_EQUAL( shared_particle->getZPosition(), 1.0 );
  FRENSIE_CHECK_EQUAL( shared_particle->getXDirection(), 0.0 );
  FRENSIE_CHECK_EQUAL( shared_particle->getYDirection(), 0.0 );
  FRENSIE_CHECK_EQUAL( shared_particle->getZDirection(), 1.0 );
  FRENSIE_CHECK_EQUAL( shared_particle->getEnergy(), 1.0 );
  FRENSIE_CHECK_EQUAL( shared_particle->getCharge(), -1 );
  FRENSIE_CHECK_EQUAL( shared_particle->getTime(), 0.5 );
  FRENSIE_CHECK_EQUAL( shared_particle->getCollisionNumber(), 1.0 );
  FRENSIE_CHECK_EQUAL( shared_particle->getGenerationNumber(), 0.0 );
  FRENSIE_CHECK_EQUAL( shared_particle->getWeight(), 0.25 );
  FRENSIE_CHECK_EQUAL( shared_particle->getRaySafetyDistance(), 1.5 );
  FRENSIE_CHECK_EQUAL( shared_particle->getHistoryNumber(), 1ull );
  FRENSIE_CHECK_EQUAL( shared_particle->getParticleType(),
		       MonteCarlo::ELECTRON );
}

//---------------------------------------------------------------------------//
// end tstElectronState.cpp
//---------------------------------------------------------------------------//
