//---------------------------------------------------------------------------//
//!
//! \file   tstSimulationElectronProperties.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation electron properties unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_SimulationElectronProperties.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Test the simulation properties defaults
TEUCHOS_UNIT_TEST( SimulationElectronProperties, defaults )
{
  MonteCarlo::SimulationElectronProperties properties;
  
  TEST_EQUALITY_CONST( properties.getAbsoluteMinElectronEnergy(), 1.5e-5 );
  TEST_EQUALITY_CONST( properties.getMinElectronEnergy(), 1.5e-5 );
  TEST_EQUALITY_CONST( properties.getMaxElectronEnergy(), 20.0 );
  TEST_EQUALITY_CONST( properties.getAbsoluteMaxElectronEnergy(), 1.0e5 );
  TEST_ASSERT( properties.isAtomicRelaxationModeOn() );
  TEST_EQUALITY_CONST(
                     properties.getBremsstrahlungAngularDistributionFunction(),
                     MonteCarlo::TWOBS_DISTRIBUTION );
  TEST_EQUALITY_CONST( properties.getElasticCutoffAngleCosine(),
                       1.0 );
}

//---------------------------------------------------------------------------//
// Test that the min electron energy can be set
TEUCHOS_UNIT_TEST( SimulationElectronProperties, setMinElectronEnergy )
{
  MonteCarlo::SimulationElectronProperties properties;
  
  properties.setMinElectronEnergy( 1e-2 );

  TEST_EQUALITY_CONST( properties.getMinElectronEnergy(), 1e-2 );
}

//---------------------------------------------------------------------------//
// Test that the max electron energy can be set
TEUCHOS_UNIT_TEST( SimulationElectronProperties, setMaxElectronEnergy )
{
  MonteCarlo::SimulationElectronProperties properties;
  
  properties.setMaxElectronEnergy( 15.0 );

  TEST_EQUALITY_CONST( properties.getMaxElectronEnergy(), 15.0 );
}

//---------------------------------------------------------------------------//
// Test that atomic relaxation mode can be turned off
TEUCHOS_UNIT_TEST( SimulationElectronProperties, setAtomicRelaxationModeOffOn )
{
  MonteCarlo::SimulationElectronProperties properties;

  properties.setAtomicRelaxationModeOff();

  TEST_ASSERT( !properties.isAtomicRelaxationModeOn() );

  properties.setAtomicRelaxationModeOn();
  
  TEST_ASSERT( properties.isAtomicRelaxationModeOn() );
}

//---------------------------------------------------------------------------//
// Test that the bremsstrahlung angular distribution function can be turned to Dipole
TEUCHOS_UNIT_TEST( SimulationElectronProperties, setBremsstrahlungAngularDistributionFunction_Dipole )
{
  MonteCarlo::SimulationElectronProperties properties;
  
  MonteCarlo::BremsstrahlungAngularDistributionType function;
  function = MonteCarlo::DIPOLE_DISTRIBUTION;

  properties.setBremsstrahlungAngularDistributionFunction( function );

  TEST_EQUALITY_CONST(
                     properties.getBremsstrahlungAngularDistributionFunction(),
                     MonteCarlo::DIPOLE_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Test that the bremsstrahlung angular distribution function can be turned to Tabular
TEUCHOS_UNIT_TEST( SimulationElectronProperties, setBremsstrahlungAngularDistributionFunction_Tabular )
{
  MonteCarlo::SimulationElectronProperties properties;
  
  MonteCarlo::BremsstrahlungAngularDistributionType function;
  function = MonteCarlo::TABULAR_DISTRIBUTION;

  properties.setBremsstrahlungAngularDistributionFunction( function );

  TEST_EQUALITY_CONST(
                     properties.getBremsstrahlungAngularDistributionFunction(),
                     MonteCarlo::TABULAR_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Test that the elastic cutoff angle cosine can be set
TEUCHOS_UNIT_TEST( SimulationElectronProperties, setElasticCutoffAngleCosine )
{
  MonteCarlo::SimulationElectronProperties properties;
  
  properties.setElasticCutoffAngleCosine( 0.9 );

  TEST_EQUALITY( properties.getElasticCutoffAngleCosine(), 0.9 );
}

//---------------------------------------------------------------------------//
// end tstSimulationElectronProperties.cpp
//---------------------------------------------------------------------------//
