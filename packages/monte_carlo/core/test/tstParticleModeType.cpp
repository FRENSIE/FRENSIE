//---------------------------------------------------------------------------//
//!
//! \file   tstParticleModeType.cpp
//! \author Luke Kersting
//! \brief  Particle mode type unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleType.hpp"
#include "MonteCarlo_ParticleModeType.hpp"
#include "MonteCarlo_UnitTestHarnessExtensions.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Get the history number
TEUCHOS_UNIT_TEST( ParticleState, isParticleModeTypeCompatible )
{

  // Check neutron mode
  MonteCarlo::ParticleModeType particle_mode = MonteCarlo::NEUTRON_MODE;

  TEST_ASSERT(  isParticleModeTypeCompatible( particle_mode, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::ADJOINT_NEUTRON ) );
  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::ADJOINT_PHOTON ) );
  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::ADJOINT_ELECTRON ) );

  // Check neutron-photon mode
  particle_mode = MonteCarlo::NEUTRON_PHOTON_MODE;

  TEST_ASSERT(  isParticleModeTypeCompatible( particle_mode, MonteCarlo::NEUTRON ) );
  TEST_ASSERT(  isParticleModeTypeCompatible( particle_mode, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::ADJOINT_NEUTRON ) );
  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::ADJOINT_PHOTON ) );
  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::ADJOINT_ELECTRON ) );

  // Check neutron-photon-electron mode
  particle_mode = MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE;

  TEST_ASSERT(  isParticleModeTypeCompatible( particle_mode, MonteCarlo::NEUTRON ) );
  TEST_ASSERT(  isParticleModeTypeCompatible( particle_mode, MonteCarlo::PHOTON ) );
  TEST_ASSERT(  isParticleModeTypeCompatible( particle_mode, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::ADJOINT_NEUTRON ) );
  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::ADJOINT_PHOTON ) );
  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::ADJOINT_ELECTRON ) );

  // Check adjoint neutron mode
  particle_mode = MonteCarlo::ADJOINT_NEUTRON_MODE;

  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::ELECTRON ) );
  TEST_ASSERT(  isParticleModeTypeCompatible( particle_mode, MonteCarlo::ADJOINT_NEUTRON ) );
  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::ADJOINT_PHOTON ) );
  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::ADJOINT_ELECTRON ) );

  // Check photon mode
  particle_mode = MonteCarlo::PHOTON_MODE;

  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::NEUTRON ) );
  TEST_ASSERT(  isParticleModeTypeCompatible( particle_mode, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::ADJOINT_NEUTRON ) );
  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::ADJOINT_PHOTON ) );
  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::ADJOINT_ELECTRON ) );

  // Check photon-electron mode
  particle_mode = MonteCarlo::PHOTON_ELECTRON_MODE;

  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::NEUTRON ) );
  TEST_ASSERT(  isParticleModeTypeCompatible( particle_mode, MonteCarlo::PHOTON ) );
  TEST_ASSERT(  isParticleModeTypeCompatible( particle_mode, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::ADJOINT_NEUTRON ) );
  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::ADJOINT_PHOTON ) );
  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::ADJOINT_ELECTRON ) );

  // Check adjoint photon mode
  particle_mode = MonteCarlo::ADJOINT_PHOTON_MODE;

  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::ADJOINT_NEUTRON ) );
  TEST_ASSERT(  isParticleModeTypeCompatible( particle_mode, MonteCarlo::ADJOINT_PHOTON ) );
  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::ADJOINT_ELECTRON ) );

  // Check electron mode
  particle_mode = MonteCarlo::ELECTRON_MODE;

  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::PHOTON ) );
  TEST_ASSERT(  isParticleModeTypeCompatible( particle_mode, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::ADJOINT_NEUTRON ) );
  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::ADJOINT_PHOTON ) );
  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::ADJOINT_ELECTRON ) );

  // Check adjoint electron mode
  particle_mode = MonteCarlo::ADJOINT_ELECTRON_MODE;

  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::ADJOINT_NEUTRON ) );
  TEST_ASSERT( !isParticleModeTypeCompatible( particle_mode, MonteCarlo::ADJOINT_PHOTON ) );
  TEST_ASSERT(  isParticleModeTypeCompatible( particle_mode, MonteCarlo::ADJOINT_ELECTRON ) );

}

//---------------------------------------------------------------------------//
// end tstParticleState.cpp
//---------------------------------------------------------------------------//
