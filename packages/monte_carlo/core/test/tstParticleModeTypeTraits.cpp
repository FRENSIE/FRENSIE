//---------------------------------------------------------------------------//
//!
//! \file   tstParticleModeTypeTraits.cpp
//! \author Alex Robinson
//! \brief  Particle mode type unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_ParticleModeTypeTraits.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check if a particle type is compatible with the desired mode
FRENSIE_UNIT_TEST( ParticleModeTypeTraits, isParticleTypeCompatible )
{
  // Check neutron mode
  FRENSIE_CHECK(  MonteCarlo::isParticleTypeCompatible<MonteCarlo::NEUTRON_MODE>( MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible<MonteCarlo::NEUTRON_MODE>( MonteCarlo::PHOTON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible<MonteCarlo::NEUTRON_MODE>( MonteCarlo::ELECTRON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible<MonteCarlo::NEUTRON_MODE>( MonteCarlo::ADJOINT_NEUTRON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible<MonteCarlo::NEUTRON_MODE>( MonteCarlo::ADJOINT_PHOTON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible<MonteCarlo::NEUTRON_MODE>( MonteCarlo::ADJOINT_ELECTRON ) );

  // Check photon mode
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible<MonteCarlo::PHOTON_MODE>( MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK(  MonteCarlo::isParticleTypeCompatible<MonteCarlo::PHOTON_MODE>( MonteCarlo::PHOTON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible<MonteCarlo::PHOTON_MODE>( MonteCarlo::ELECTRON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible<MonteCarlo::PHOTON_MODE>( MonteCarlo::ADJOINT_NEUTRON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible<MonteCarlo::PHOTON_MODE>( MonteCarlo::ADJOINT_PHOTON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible<MonteCarlo::PHOTON_MODE>( MonteCarlo::ADJOINT_ELECTRON ) );

  // Check electron mode
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible<MonteCarlo::ELECTRON_MODE>( MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible<MonteCarlo::ELECTRON_MODE>( MonteCarlo::PHOTON ) );
  FRENSIE_CHECK(  MonteCarlo::isParticleTypeCompatible<MonteCarlo::ELECTRON_MODE>( MonteCarlo::ELECTRON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible<MonteCarlo::ELECTRON_MODE>( MonteCarlo::ADJOINT_NEUTRON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible<MonteCarlo::ELECTRON_MODE>( MonteCarlo::ADJOINT_PHOTON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible<MonteCarlo::ELECTRON_MODE>( MonteCarlo::ADJOINT_ELECTRON ) );

  // Check neutron-photon mode
  FRENSIE_CHECK(  MonteCarlo::isParticleTypeCompatible<MonteCarlo::NEUTRON_PHOTON_MODE>( MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK(  MonteCarlo::isParticleTypeCompatible<MonteCarlo::NEUTRON_PHOTON_MODE>( MonteCarlo::PHOTON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible<MonteCarlo::NEUTRON_PHOTON_MODE>( MonteCarlo::ELECTRON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible<MonteCarlo::NEUTRON_PHOTON_MODE>( MonteCarlo::ADJOINT_NEUTRON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible<MonteCarlo::NEUTRON_PHOTON_MODE>( MonteCarlo::ADJOINT_PHOTON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible<MonteCarlo::NEUTRON_PHOTON_MODE>( MonteCarlo::ADJOINT_ELECTRON ) );

  // Check neutron-photon-electron mode
  FRENSIE_CHECK(  MonteCarlo::isParticleTypeCompatible<MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE>( MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK(  MonteCarlo::isParticleTypeCompatible<MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE>( MonteCarlo::PHOTON ) );
  FRENSIE_CHECK(  MonteCarlo::isParticleTypeCompatible<MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE>( MonteCarlo::ELECTRON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible<MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE>( MonteCarlo::ADJOINT_NEUTRON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible<MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE>( MonteCarlo::ADJOINT_PHOTON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible<MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE>( MonteCarlo::ADJOINT_ELECTRON ) );

  // Check photon-electron mode
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible<MonteCarlo::PHOTON_ELECTRON_MODE>( MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK(  MonteCarlo::isParticleTypeCompatible<MonteCarlo::PHOTON_ELECTRON_MODE>( MonteCarlo::PHOTON ) );
  FRENSIE_CHECK(  MonteCarlo::isParticleTypeCompatible<MonteCarlo::PHOTON_ELECTRON_MODE>( MonteCarlo::ELECTRON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible<MonteCarlo::PHOTON_ELECTRON_MODE>( MonteCarlo::ADJOINT_NEUTRON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible<MonteCarlo::PHOTON_ELECTRON_MODE>( MonteCarlo::ADJOINT_PHOTON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible<MonteCarlo::PHOTON_ELECTRON_MODE>( MonteCarlo::ADJOINT_ELECTRON ) );

  // Check adjoint photon mode
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible<MonteCarlo::ADJOINT_PHOTON_MODE>( MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible<MonteCarlo::ADJOINT_PHOTON_MODE>( MonteCarlo::PHOTON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible<MonteCarlo::ADJOINT_PHOTON_MODE>( MonteCarlo::ELECTRON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible<MonteCarlo::ADJOINT_PHOTON_MODE>( MonteCarlo::ADJOINT_NEUTRON ) );
  FRENSIE_CHECK(  MonteCarlo::isParticleTypeCompatible<MonteCarlo::ADJOINT_PHOTON_MODE>( MonteCarlo::ADJOINT_PHOTON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible<MonteCarlo::ADJOINT_PHOTON_MODE>( MonteCarlo::ADJOINT_ELECTRON ) );

  // Check adjoint electron mode
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible<MonteCarlo::ADJOINT_ELECTRON_MODE>( MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible<MonteCarlo::ADJOINT_ELECTRON_MODE>( MonteCarlo::PHOTON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible<MonteCarlo::ADJOINT_ELECTRON_MODE>( MonteCarlo::ELECTRON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible<MonteCarlo::ADJOINT_ELECTRON_MODE>( MonteCarlo::ADJOINT_NEUTRON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible<MonteCarlo::ADJOINT_ELECTRON_MODE>( MonteCarlo::ADJOINT_PHOTON ) );
  FRENSIE_CHECK(  MonteCarlo::isParticleTypeCompatible<MonteCarlo::ADJOINT_ELECTRON_MODE>( MonteCarlo::ADJOINT_ELECTRON ) );
}

//---------------------------------------------------------------------------//
// Check if a particle type is compatible with the desired mode
FRENSIE_UNIT_TEST( ParticleModeTypeTraits, isParticleTypeCompatible_runtime )
{
  // Check neutron mode
  FRENSIE_CHECK(  MonteCarlo::isParticleTypeCompatible( MonteCarlo::NEUTRON_MODE, MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible( MonteCarlo::NEUTRON_MODE, MonteCarlo::PHOTON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible( MonteCarlo::NEUTRON_MODE, MonteCarlo::ELECTRON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible( MonteCarlo::NEUTRON_MODE, MonteCarlo::ADJOINT_NEUTRON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible( MonteCarlo::NEUTRON_MODE, MonteCarlo::ADJOINT_PHOTON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible( MonteCarlo::NEUTRON_MODE, MonteCarlo::ADJOINT_ELECTRON ) );

  // Check photon mode
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible( MonteCarlo::PHOTON_MODE, MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK(  MonteCarlo::isParticleTypeCompatible( MonteCarlo::PHOTON_MODE, MonteCarlo::PHOTON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible( MonteCarlo::PHOTON_MODE, MonteCarlo::ELECTRON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible( MonteCarlo::PHOTON_MODE, MonteCarlo::ADJOINT_NEUTRON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible( MonteCarlo::PHOTON_MODE, MonteCarlo::ADJOINT_PHOTON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible( MonteCarlo::PHOTON_MODE, MonteCarlo::ADJOINT_ELECTRON ) );

  // Check electron mode
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible( MonteCarlo::ELECTRON_MODE, MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible( MonteCarlo::ELECTRON_MODE, MonteCarlo::PHOTON ) );
  FRENSIE_CHECK(  MonteCarlo::isParticleTypeCompatible( MonteCarlo::ELECTRON_MODE, MonteCarlo::ELECTRON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible( MonteCarlo::ELECTRON_MODE, MonteCarlo::ADJOINT_NEUTRON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible( MonteCarlo::ELECTRON_MODE, MonteCarlo::ADJOINT_PHOTON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible( MonteCarlo::ELECTRON_MODE, MonteCarlo::ADJOINT_ELECTRON ) );

  // Check neutron-photon mode
  FRENSIE_CHECK(  MonteCarlo::isParticleTypeCompatible( MonteCarlo::NEUTRON_PHOTON_MODE, MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK(  MonteCarlo::isParticleTypeCompatible( MonteCarlo::NEUTRON_PHOTON_MODE, MonteCarlo::PHOTON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible( MonteCarlo::NEUTRON_PHOTON_MODE, MonteCarlo::ELECTRON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible( MonteCarlo::NEUTRON_PHOTON_MODE, MonteCarlo::ADJOINT_NEUTRON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible( MonteCarlo::NEUTRON_PHOTON_MODE, MonteCarlo::ADJOINT_PHOTON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible( MonteCarlo::NEUTRON_PHOTON_MODE, MonteCarlo::ADJOINT_ELECTRON ) );

  // Check neutron-photon-electron mode
  FRENSIE_CHECK(  MonteCarlo::isParticleTypeCompatible( MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE, MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK(  MonteCarlo::isParticleTypeCompatible( MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE, MonteCarlo::PHOTON ) );
  FRENSIE_CHECK(  MonteCarlo::isParticleTypeCompatible( MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE, MonteCarlo::ELECTRON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible( MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE, MonteCarlo::ADJOINT_NEUTRON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible( MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE, MonteCarlo::ADJOINT_PHOTON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible( MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE, MonteCarlo::ADJOINT_ELECTRON ) );

  // Check photon-electron mode
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible( MonteCarlo::PHOTON_ELECTRON_MODE, MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK(  MonteCarlo::isParticleTypeCompatible( MonteCarlo::PHOTON_ELECTRON_MODE, MonteCarlo::PHOTON ) );
  FRENSIE_CHECK(  MonteCarlo::isParticleTypeCompatible( MonteCarlo::PHOTON_ELECTRON_MODE, MonteCarlo::ELECTRON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible( MonteCarlo::PHOTON_ELECTRON_MODE, MonteCarlo::ADJOINT_NEUTRON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible( MonteCarlo::PHOTON_ELECTRON_MODE, MonteCarlo::ADJOINT_PHOTON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible( MonteCarlo::PHOTON_ELECTRON_MODE, MonteCarlo::ADJOINT_ELECTRON ) );

  // Check adjoint photon mode
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible( MonteCarlo::ADJOINT_PHOTON_MODE, MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible( MonteCarlo::ADJOINT_PHOTON_MODE, MonteCarlo::PHOTON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible( MonteCarlo::ADJOINT_PHOTON_MODE, MonteCarlo::ELECTRON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible( MonteCarlo::ADJOINT_PHOTON_MODE, MonteCarlo::ADJOINT_NEUTRON ) );
  FRENSIE_CHECK(  MonteCarlo::isParticleTypeCompatible( MonteCarlo::ADJOINT_PHOTON_MODE, MonteCarlo::ADJOINT_PHOTON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible( MonteCarlo::ADJOINT_PHOTON_MODE, MonteCarlo::ADJOINT_ELECTRON ) );

  // Check adjoint electron mode
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible( MonteCarlo::ADJOINT_ELECTRON_MODE, MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible( MonteCarlo::ADJOINT_ELECTRON_MODE, MonteCarlo::PHOTON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible( MonteCarlo::ADJOINT_ELECTRON_MODE, MonteCarlo::ELECTRON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible( MonteCarlo::ADJOINT_ELECTRON_MODE, MonteCarlo::ADJOINT_NEUTRON ) );
  FRENSIE_CHECK( !MonteCarlo::isParticleTypeCompatible( MonteCarlo::ADJOINT_ELECTRON_MODE, MonteCarlo::ADJOINT_PHOTON ) );
  FRENSIE_CHECK(  MonteCarlo::isParticleTypeCompatible( MonteCarlo::ADJOINT_ELECTRON_MODE, MonteCarlo::ADJOINT_ELECTRON ) );
}

//---------------------------------------------------------------------------//
// Test that the correct particle states are active in neutron mode
FRENSIE_UNIT_TEST( ParticleModeTypeTraits,
                   neutron_mode_check_active_particles )
{
  FRENSIE_CHECK_EQUAL( boost::mpl::size<MonteCarlo::ParticleModeTypeTraits<MonteCarlo::NEUTRON_MODE>::ActiveParticles>::value, 1 );
  FRENSIE_CHECK( (boost::mpl::contains<MonteCarlo::ParticleModeTypeTraits<MonteCarlo::NEUTRON_MODE>::ActiveParticles, MonteCarlo::NeutronState>::value) );
}

//---------------------------------------------------------------------------//
// Test that the correct particle states are active in photon mode
FRENSIE_UNIT_TEST( ParticleModeTypeTraits,
                   photon_mode_check_active_particles )
{
  FRENSIE_CHECK_EQUAL( boost::mpl::size<MonteCarlo::ParticleModeTypeTraits<MonteCarlo::PHOTON_MODE>::ActiveParticles>::value, 1 );
  FRENSIE_CHECK( (boost::mpl::contains<MonteCarlo::ParticleModeTypeTraits<MonteCarlo::PHOTON_MODE>::ActiveParticles, MonteCarlo::PhotonState>::value) );
}

//---------------------------------------------------------------------------//
// Test that the correct particle states are active in electron mode
FRENSIE_UNIT_TEST( ParticleModeTypeTraits,
                   electron_mode_check_active_particles )
{
  FRENSIE_CHECK_EQUAL( boost::mpl::size<MonteCarlo::ParticleModeTypeTraits<MonteCarlo::ELECTRON_MODE>::ActiveParticles>::value, 1 );
  FRENSIE_CHECK( (boost::mpl::contains<MonteCarlo::ParticleModeTypeTraits<MonteCarlo::ELECTRON_MODE>::ActiveParticles, MonteCarlo::ElectronState>::value) );
}

//---------------------------------------------------------------------------//
// Test that the correct particle states are active in neutron photon mode
FRENSIE_UNIT_TEST( ParticleModeTypeTraits,
                   neutron_photon_mode_check_active_particles )
{
  FRENSIE_CHECK_EQUAL( boost::mpl::size<MonteCarlo::ParticleModeTypeTraits<MonteCarlo::NEUTRON_PHOTON_MODE>::ActiveParticles>::value, 2 );
  FRENSIE_CHECK( (boost::mpl::contains<MonteCarlo::ParticleModeTypeTraits<MonteCarlo::NEUTRON_PHOTON_MODE>::ActiveParticles, MonteCarlo::NeutronState>::value) );
  FRENSIE_CHECK( (boost::mpl::contains<MonteCarlo::ParticleModeTypeTraits<MonteCarlo::NEUTRON_PHOTON_MODE>::ActiveParticles, MonteCarlo::PhotonState>::value) );
}

//---------------------------------------------------------------------------//
// Test that the correct particle states are active in neutron photon electron
// mode
FRENSIE_UNIT_TEST( ParticleModeTypeTraits,
                   neutron_photon_electron_mode_check_active_particles )
{
  FRENSIE_CHECK_EQUAL( boost::mpl::size<MonteCarlo::ParticleModeTypeTraits<MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE>::ActiveParticles>::value, 3 );
  FRENSIE_CHECK( (boost::mpl::contains<MonteCarlo::ParticleModeTypeTraits<MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE>::ActiveParticles, MonteCarlo::NeutronState>::value) );
  FRENSIE_CHECK( (boost::mpl::contains<MonteCarlo::ParticleModeTypeTraits<MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE>::ActiveParticles, MonteCarlo::PhotonState>::value) );
  FRENSIE_CHECK( (boost::mpl::contains<MonteCarlo::ParticleModeTypeTraits<MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE>::ActiveParticles, MonteCarlo::ElectronState>::value) );
}

//---------------------------------------------------------------------------//
// Test that the correct particle states are active in photon electron mode
FRENSIE_UNIT_TEST( ParticleModeTypeTraits,
                   photon_electron_mode_check_active_particles )
{
  FRENSIE_CHECK_EQUAL( boost::mpl::size<MonteCarlo::ParticleModeTypeTraits<MonteCarlo::PHOTON_ELECTRON_MODE>::ActiveParticles>::value, 2 );
  FRENSIE_CHECK( (boost::mpl::contains<MonteCarlo::ParticleModeTypeTraits<MonteCarlo::PHOTON_ELECTRON_MODE>::ActiveParticles, MonteCarlo::PhotonState>::value) );
  FRENSIE_CHECK( (boost::mpl::contains<MonteCarlo::ParticleModeTypeTraits<MonteCarlo::PHOTON_ELECTRON_MODE>::ActiveParticles, MonteCarlo::ElectronState>::value) );
}

//---------------------------------------------------------------------------//
// Test that the correct particle states are active in adjoint photon mode
FRENSIE_UNIT_TEST( ParticleModeTypeTraits,
                   adjoint_photon_mode_check_active_particles )
{
  FRENSIE_CHECK_EQUAL( boost::mpl::size<MonteCarlo::ParticleModeTypeTraits<MonteCarlo::ADJOINT_PHOTON_MODE>::ActiveParticles>::value, 1 );
  FRENSIE_CHECK( (boost::mpl::contains<MonteCarlo::ParticleModeTypeTraits<MonteCarlo::ADJOINT_PHOTON_MODE>::ActiveParticles, MonteCarlo::AdjointPhotonState>::value) );
}

//---------------------------------------------------------------------------//
// Test that the correct particle states are active in adjoint electron mode
FRENSIE_UNIT_TEST( ParticleModeTypeTraits,
                   adjoint_electron_mode_check_active_particles )
{
  FRENSIE_CHECK_EQUAL( boost::mpl::size<MonteCarlo::ParticleModeTypeTraits<MonteCarlo::ADJOINT_ELECTRON_MODE>::ActiveParticles>::value, 1 );
  FRENSIE_CHECK( (boost::mpl::contains<MonteCarlo::ParticleModeTypeTraits<MonteCarlo::ADJOINT_ELECTRON_MODE>::ActiveParticles, MonteCarlo::AdjointElectronState>::value) );
}

//---------------------------------------------------------------------------//
// end tstParticleModeTypeTraits.cpp
//---------------------------------------------------------------------------//
