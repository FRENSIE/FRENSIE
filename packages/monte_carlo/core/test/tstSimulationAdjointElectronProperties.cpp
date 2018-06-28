//---------------------------------------------------------------------------//
//!
//! \file   tstSimulationAdjointElectronProperties.cpp
//! \author Luke Kersting
//! \brief  Simulation adjoint electron properties unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_SimulationAdjointElectronProperties.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Test the simulation properties defaults
TEUCHOS_UNIT_TEST( SimulationAdjointElectronProperties, defaults )
{
  MonteCarlo::SimulationAdjointElectronProperties properties;

  TEST_EQUALITY_CONST( properties.getAbsoluteMinAdjointElectronEnergy(), 1e-5 );
  TEST_EQUALITY_CONST( properties.getMinAdjointElectronEnergy(), 1e-5 );
  TEST_EQUALITY_CONST( properties.getMaxAdjointElectronEnergy(), 20.0 );
  TEST_EQUALITY_CONST( properties.getAbsoluteMaxAdjointElectronEnergy(), 20.0 );
  TEST_ASSERT( properties.isAdjointElasticModeOn() );
  TEST_ASSERT( properties.isAdjointElectroionizationModeOn() );
  TEST_ASSERT( properties.isAdjointBremsstrahlungModeOn() );
  TEST_ASSERT( properties.isAdjointAtomicExcitationModeOn() );
  TEST_EQUALITY_CONST( properties.getAdjointElasticElectronDistributionMode(),
                       MonteCarlo::COUPLED_DISTRIBUTION );
  TEST_EQUALITY_CONST( properties.getAdjointCoupledElasticSamplingMode(),
                       MonteCarlo::MODIFIED_TWO_D_UNION );
  TEST_EQUALITY_CONST(
             properties.getAdjointBremsstrahlungAngularDistributionFunction(),
             MonteCarlo::TWOBS_DISTRIBUTION );
  TEST_EQUALITY( properties.getAdjointElectronEvaluationTolerance(), 1e-12 );
  TEST_EQUALITY_CONST( properties.getAdjointElasticCutoffAngleCosine(),
                       1.0 );
  TEST_EQUALITY_CONST( properties.getNumberOfAdjointElectronHashGridBins(),
                       500 );

}

//---------------------------------------------------------------------------//
// Check that the min adjoint electron energy can be set
TEUCHOS_UNIT_TEST( SimulationAdjointElectronProperties,
                   setMinAdjointElectronEnergy )
{
  MonteCarlo::SimulationAdjointElectronProperties properties;

  properties.setMinAdjointElectronEnergy( 1e-2 );

  TEST_EQUALITY_CONST( properties.getMinAdjointElectronEnergy(), 1e-2 );
}

//---------------------------------------------------------------------------//
// Check that the max adjoint electron energy can be set
TEUCHOS_UNIT_TEST( SimulationAdjointElectronProperties,
                   setMaxAdjointElectronEnergy )
{
  MonteCarlo::SimulationAdjointElectronProperties properties;

  properties.setMaxAdjointElectronEnergy( 15.0 );

  TEST_EQUALITY_CONST( properties.getMaxAdjointElectronEnergy(), 15.0 );
}

//---------------------------------------------------------------------------//
// Test that adjoint elastic mode can be turned off
TEUCHOS_UNIT_TEST( SimulationAdjointElectronProperties,
                   setAdjointElasticModeOffOn )
{
  MonteCarlo::SimulationAdjointElectronProperties properties;

  properties.setAdjointElasticModeOff();

  TEST_ASSERT( !properties.isAdjointElasticModeOn() );

  properties.setAdjointElasticModeOn();

  TEST_ASSERT( properties.isAdjointElasticModeOn() );
}

//---------------------------------------------------------------------------//
// Test that adjoint electroionization mode can be turned off
TEUCHOS_UNIT_TEST( SimulationAdjointElectronProperties,
                   setAdjointElectroionizationModeOffOn )
{
  MonteCarlo::SimulationAdjointElectronProperties properties;

  properties.setAdjointElectroionizationModeOff();

  TEST_ASSERT( !properties.isAdjointElectroionizationModeOn() );

  properties.setAdjointElectroionizationModeOn();

  TEST_ASSERT( properties.isAdjointElectroionizationModeOn() );
}

//---------------------------------------------------------------------------//
// Test that adjoint bremsstrahlung mode can be turned off
TEUCHOS_UNIT_TEST( SimulationAdjointElectronProperties,
                   setAdjointBremsstrahlungModeOffOn )
{
  MonteCarlo::SimulationAdjointElectronProperties properties;

  properties.setAdjointBremsstrahlungModeOff();

  TEST_ASSERT( !properties.isAdjointBremsstrahlungModeOn() );

  properties.setAdjointBremsstrahlungModeOn();

  TEST_ASSERT( properties.isAdjointBremsstrahlungModeOn() );
}

//---------------------------------------------------------------------------//
// Test that adjoint atomic excitation mode can be turned off
TEUCHOS_UNIT_TEST( SimulationAdjointElectronProperties,
                   setAdjointAtomicExcitationModeOffOn )
{
  MonteCarlo::SimulationAdjointElectronProperties properties;

  properties.setAdjointAtomicExcitationModeOff();

  TEST_ASSERT( !properties.isAdjointAtomicExcitationModeOn() );

  properties.setAdjointAtomicExcitationModeOn();

  TEST_ASSERT( properties.isAdjointAtomicExcitationModeOn() );
}

//---------------------------------------------------------------------------//
// Test that the adjoint electron evaluation tolerance can be set
TEUCHOS_UNIT_TEST( SimulationAdjointElectronProperties,
                   setAdjointElectronEvaluationTolerance )
{
  MonteCarlo::SimulationAdjointElectronProperties properties;

  TEST_EQUALITY( properties.getAdjointElectronEvaluationTolerance(), 1e-12 );

  properties.setAdjointElectronEvaluationTolerance( 1e-4 );

  TEST_EQUALITY( properties.getAdjointElectronEvaluationTolerance(), 1e-4 );
}

//---------------------------------------------------------------------------//
// Test that the adjoint bremsstrahlung angular distribution function can be turned to Dipole
TEUCHOS_UNIT_TEST( SimulationAdjointElectronProperties,
                   setAdjointBremsstrahlungAngularDistributionFunction_Dipole )
{
  MonteCarlo::SimulationAdjointElectronProperties properties;

  MonteCarlo::BremsstrahlungAngularDistributionType function;
  function = MonteCarlo::DIPOLE_DISTRIBUTION;

  properties.setAdjointBremsstrahlungAngularDistributionFunction( function );

  TEST_EQUALITY_CONST(
             properties.getAdjointBremsstrahlungAngularDistributionFunction(),
             MonteCarlo::DIPOLE_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Test that the adjoint coupled elastic electron distribution mode can be set
TEUCHOS_UNIT_TEST( SimulationAdjointElectronProperties,
                   setAdjointElasticElectronDistributionMode )
{
  MonteCarlo::SimulationAdjointElectronProperties properties;

  TEST_EQUALITY_CONST( properties.getAdjointElasticElectronDistributionMode(),
                       MonteCarlo::COUPLED_DISTRIBUTION );

  MonteCarlo::ElasticElectronDistributionType mode;
  mode = MonteCarlo::DECOUPLED_DISTRIBUTION;

  properties.setAdjointElasticElectronDistributionMode( mode );

  TEST_EQUALITY_CONST( properties.getAdjointElasticElectronDistributionMode(),
                       mode );
}

//---------------------------------------------------------------------------//
// Test that the adjoint coupled elastic sampling mode can be set
TEUCHOS_UNIT_TEST( SimulationAdjointElectronProperties,
                   setAdjointCoupledElasticSamplingMode )
{
  MonteCarlo::SimulationAdjointElectronProperties properties;

  TEST_EQUALITY_CONST( properties.getAdjointCoupledElasticSamplingMode(),
                       MonteCarlo::MODIFIED_TWO_D_UNION );

  MonteCarlo::CoupledElasticSamplingMethod mode;
  mode = MonteCarlo::TWO_D_UNION;

  properties.setAdjointCoupledElasticSamplingMode( mode );

  TEST_EQUALITY_CONST( properties.getAdjointCoupledElasticSamplingMode(),
                       mode );
}

//---------------------------------------------------------------------------//
// Test that the adjoint bremsstrahlung angular distribution function can be turned to Tabular
TEUCHOS_UNIT_TEST( SimulationAdjointElectronProperties,
                   setAdjointBremsstrahlungAngularDistributionFunction_Tabular )
{
  MonteCarlo::SimulationAdjointElectronProperties properties;

  MonteCarlo::BremsstrahlungAngularDistributionType function;
  function = MonteCarlo::TABULAR_DISTRIBUTION;

  properties.setAdjointBremsstrahlungAngularDistributionFunction( function );

  TEST_EQUALITY_CONST(
             properties.getAdjointBremsstrahlungAngularDistributionFunction(),
             MonteCarlo::TABULAR_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Test that the adjoint elastic cutoff angle cosine can be set
TEUCHOS_UNIT_TEST( SimulationAdjointElectronProperties,
                   setAdjointElasticCutoffAngleCosine )
{
  MonteCarlo::SimulationAdjointElectronProperties properties;

  properties.setAdjointElasticCutoffAngleCosine( 0.9 );

  TEST_EQUALITY( properties.getAdjointElasticCutoffAngleCosine(), 0.9 );
}

//---------------------------------------------------------------------------//
// Check that the number of adjoint electron hash grid bins can be set
TEUCHOS_UNIT_TEST( SimulationAdjointElectronProperties,
                   setNumberOfAdjointElectronHashGridBins )
{
  MonteCarlo::SimulationAdjointElectronProperties properties;

  properties.setNumberOfAdjointElectronHashGridBins( 750 );

  TEST_EQUALITY_CONST( properties.getNumberOfAdjointElectronHashGridBins(),
                       750 );
}

//---------------------------------------------------------------------------//
// end tstSimulationAdjointElectronProperties.cpp
//---------------------------------------------------------------------------//
