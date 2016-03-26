//---------------------------------------------------------------------------//
//!
//! \file   tstEstimatorParticleStateWrapper.cpp
//! \author Alex Robinson
//! \brief  The estimator particle state wrapper unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_EstimatorParticleStateWrapper.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_UnitTestHarnessExtensions.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Get the particle state can be returned
TEUCHOS_UNIT_TEST( EstimatorParticleStateWrapper, getParticleState )
{
  MonteCarlo::NeutronState neutron( 0ull );
  
  std::shared_ptr<MonteCarlo::EstimatorParticleStateWrapper> particle_wrapper(
                    new MonteCarlo::EstimatorParticleStateWrapper( neutron ) );

  TEST_ASSERT( &neutron == &particle_wrapper->getParticleState() );
}

//---------------------------------------------------------------------------//
// Set/get the angle cosine
TEUCHOS_UNIT_TEST( EstimatorParticleStateWrapper, setgetAngleCosine )
{
  MonteCarlo::PhotonState photon( 1ull );

  MonteCarlo::EstimatorParticleStateWrapper particle_wrapper( photon );
  particle_wrapper.setAngleCosine( 0.5 );
  
  TEST_EQUALITY_CONST( particle_wrapper.getAngleCosine(), 0.5 );
}

//---------------------------------------------------------------------------//
// end tstEstimatorParticleStateWrapper.cpp
//---------------------------------------------------------------------------//
