//---------------------------------------------------------------------------//
//!
//! \file   tstObserverParticleStateWrapper.cpp
//! \author Alex Robinson
//! \brief  The observer particle state wrapper unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_ObserverParticleStateWrapper.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Get the particle state can be returned
FRENSIE_UNIT_TEST( ObserverParticleStateWrapper, getParticleState )
{
  MonteCarlo::NeutronState neutron( 0ull );

  std::shared_ptr<MonteCarlo::ObserverParticleStateWrapper> particle_wrapper(
                    new MonteCarlo::ObserverParticleStateWrapper( neutron ) );

  FRENSIE_CHECK( &neutron == &particle_wrapper->getParticleState() );
}

//---------------------------------------------------------------------------//
// Set/get the angle cosine
FRENSIE_UNIT_TEST( ObserverParticleStateWrapper, setgetAngleCosine )
{
  MonteCarlo::PhotonState photon( 1ull );

  MonteCarlo::ObserverParticleStateWrapper particle_wrapper( photon );
  particle_wrapper.setAngleCosine( 0.5 );

  FRENSIE_CHECK_EQUAL( particle_wrapper.getAngleCosine(), 0.5 );
}

//---------------------------------------------------------------------------//
// Check that the particle start time can be set
FRENSIE_UNIT_TEST( ObserverParticleStateWrapper, setStartTime )
{

  {
    MonteCarlo::PhotonState photon( 1ull );

    MonteCarlo::ObserverParticleStateWrapper particle_wrapper( photon );
    particle_wrapper.setStartTime( 1.0 );

    FRENSIE_CHECK_EQUAL( particle_wrapper.getStartTime(), 1.0 );
  }

  {
    MonteCarlo::ElectronState electron( 1ull );

    MonteCarlo::ObserverParticleStateWrapper particle_wrapper( electron );
    particle_wrapper.setStartTime( 1.0 );

    FRENSIE_CHECK_EQUAL( particle_wrapper.getStartTime(), 1.0 );
  }
}

//---------------------------------------------------------------------------//
// Check that the particle end time can be set
FRENSIE_UNIT_TEST( ObserverParticleStateWrapper, setEndTime )
{
  MonteCarlo::PhotonState photon( 1ull );

  MonteCarlo::ObserverParticleStateWrapper particle_wrapper( photon );
  particle_wrapper.setEndTime( 2.0 );

  FRENSIE_CHECK_EQUAL( particle_wrapper.getEndTime(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the particle track start/end times can be calculated
FRENSIE_UNIT_TEST( ObserverParticleStateWrapper,
                   calculateStateTimesUsingParticleTimeAsStartTime )
{
  MonteCarlo::PhotonState photon( 1ull );
  photon.setTime( 0.0 );

  MonteCarlo::ObserverParticleStateWrapper particle_wrapper( photon );
  particle_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 1.0 );

  FRENSIE_CHECK_EQUAL( particle_wrapper.getStartTime(), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle_wrapper.getEndTime(),
                                   3.33564095198152e-11,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle_wrapper.getTimeDuration(),
                                   3.33564095198152e-11,
                                   1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the particle track start/end times can be calculated
FRENSIE_UNIT_TEST( ObserverParticleStateWrapper,
                   calculateStateTimesUsingParticleTimeAsEndTime )
{
  MonteCarlo::PhotonState photon( 1ull );
  photon.setTime( 1.0 );

  MonteCarlo::ObserverParticleStateWrapper particle_wrapper( photon );
  particle_wrapper.calculateStateTimesUsingParticleTimeAsEndTime( 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( particle_wrapper.getStartTime(),
                                   0.9999999999666436,
                                   1e-15 );
  FRENSIE_CHECK_EQUAL( particle_wrapper.getEndTime(), 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle_wrapper.getTimeDuration(),
                                   3.33564095198152e-11,
                                   1e-6 );
}

//---------------------------------------------------------------------------//
// end tstObserverParticleStateWrapper.cpp
//---------------------------------------------------------------------------//
