//---------------------------------------------------------------------------//
//!
//! \file   tstSimulationGeneralProperties.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation general properties unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_SimulationGeneralProperties.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Test the simulation properties defaults
TEUCHOS_UNIT_TEST( SimulationGeneralProperties, defaults )
{
  MonteCarlo::SimulationGeneralProperties properties;
  
  TEST_EQUALITY_CONST( properties.getParticleMode(),
                       MonteCarlo::NEUTRON_MODE );
  TEST_EQUALITY_CONST( properties.getNumberOfHistories(), 0 );
  TEST_EQUALITY_CONST( properties.getSurfaceFluxEstimatorAngleCosineCutoff(),
                       0.001 );
  TEST_ASSERT( properties.displayWarnings() );
  TEST_ASSERT( !properties.isImplicitCaptureModeOn() );
}

//---------------------------------------------------------------------------//
// Test that the particle mode can be set
TEUCHOS_UNIT_TEST( SimulationGeneralProperties, setParticleMode )
{
  MonteCarlo::SimulationGeneralProperties properties;
  
  properties.setParticleMode( MonteCarlo::NEUTRON_MODE );

  TEST_EQUALITY_CONST( properties.getParticleMode(),
                       MonteCarlo::NEUTRON_MODE );

  properties.setParticleMode( MonteCarlo::PHOTON_MODE );

  TEST_EQUALITY_CONST( properties.getParticleMode(), MonteCarlo::PHOTON_MODE );

  properties.setParticleMode( MonteCarlo::ELECTRON_MODE );

  TEST_EQUALITY_CONST( properties.getParticleMode(),
                       MonteCarlo::ELECTRON_MODE );

  properties.setParticleMode( MonteCarlo::NEUTRON_PHOTON_MODE );

  TEST_EQUALITY_CONST( properties.getParticleMode(),
                       MonteCarlo::NEUTRON_PHOTON_MODE );

  properties.setParticleMode( MonteCarlo::PHOTON_ELECTRON_MODE );

  TEST_EQUALITY_CONST( properties.getParticleMode(),
                       MonteCarlo::PHOTON_ELECTRON_MODE );

  properties.setParticleMode( MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE );

  TEST_EQUALITY_CONST( properties.getParticleMode(),
                       MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE );

  properties.setParticleMode( MonteCarlo::ADJOINT_PHOTON_MODE );

  TEST_EQUALITY_CONST( properties.getParticleMode(),
                       MonteCarlo::ADJOINT_PHOTON_MODE );

  properties.setParticleMode( MonteCarlo::ADJOINT_ELECTRON_MODE );

  TEST_EQUALITY_CONST( properties.getParticleMode(),
                       MonteCarlo::ADJOINT_ELECTRON_MODE );
}

//---------------------------------------------------------------------------//
// Test that the number of histories to run can be set
TEUCHOS_UNIT_TEST( SimulationGeneralProperties, setNumberOfHistories )
{
  MonteCarlo::SimulationGeneralProperties properties;
  
  properties.setNumberOfHistories( 1000000000 );

  TEST_EQUALITY_CONST(properties.getNumberOfHistories(), 1000000000 );
}

//---------------------------------------------------------------------------//
// Test that the surface flux angle cosine cutoff can be set
TEUCHOS_UNIT_TEST( SimulationGeneralProperties,
                   setSurfaceFluxEstimatorAngleCosineCutoff )
{
  MonteCarlo::SimulationGeneralProperties properties;
  
  properties.setSurfaceFluxEstimatorAngleCosineCutoff( 0.1 );

  TEST_EQUALITY_CONST( properties.getSurfaceFluxEstimatorAngleCosineCutoff(),
                       0.1 );
}

//---------------------------------------------------------------------------//
// Test that warnings can be disabled/enabled
TEUCHOS_UNIT_TEST( SimulationGeneralProperties, setWarningsOnOff )
{
  MonteCarlo::SimulationGeneralProperties properties;
  
  properties.setWarningsOff();

  TEST_ASSERT( !properties.displayWarnings() );

  properties.setWarningsOn();

  TEST_ASSERT( properties.displayWarnings() );
}

//---------------------------------------------------------------------------//
// Test that implicit capture mode can be turned on/off
TEUCHOS_UNIT_TEST( SimulationGeneralProperties, setImplicitCaptureModeOnOff )
{
  MonteCarlo::SimulationGeneralProperties properties;
  
  properties.setImplicitCaptureModeOn();

  TEST_ASSERT( properties.isImplicitCaptureModeOn() );

  properties.setAnalogueCaptureModeOn();

  TEST_ASSERT( !properties.isImplicitCaptureModeOn() );
}

//---------------------------------------------------------------------------//
// Test that the number of batches per processor can be set
TEUCHOS_UNIT_TEST( SimulationGeneralProperties, setNumberOfBatchesPerProcessor )
{
  MonteCarlo::SimulationGeneralProperties properties;
  
  properties.setNumberOfBatchesPerProcessor( 25 );

  TEST_EQUALITY_CONST( properties.getNumberOfBatchesPerProcessor(), 25 );
}

//---------------------------------------------------------------------------//
// end tstSimulationGeneralProperties.cpp
//---------------------------------------------------------------------------//
