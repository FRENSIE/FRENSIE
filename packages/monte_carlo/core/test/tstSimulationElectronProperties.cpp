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
#include "MonteCarlo_ElasticElectronDistributionType.hpp"
#include "MonteCarlo_TwoDInterpolationType.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Test the simulation properties defaults
TEUCHOS_UNIT_TEST( SimulationElectronProperties, defaults )
{
  MonteCarlo::SimulationElectronProperties properties;

  TEST_EQUALITY_CONST( properties.getMinElectronEnergy(), 1.5e-5 );
  TEST_EQUALITY_CONST( properties.getMaxElectronEnergy(), 20.0 );
  TEST_EQUALITY_CONST( properties.getElectronEvaluationTolerance(), 1e-7 );
  TEST_ASSERT( properties.isCorrelatedSamplingModeOn() );
  TEST_ASSERT( properties.isUnitBasedInterpolationModeOn() );
  TEST_ASSERT( properties.isAtomicRelaxationModeOn() );
  TEST_ASSERT( properties.isElasticModeOn() );
  TEST_EQUALITY_CONST( properties.getElasticTwoDInterpPolicy(),
                       MonteCarlo::LOGLOGLOG_INTERPOLATION );
  TEST_EQUALITY_CONST( properties.getElasticElectronDistributionMode(),
                       MonteCarlo::DECOUPLED_DISTRIBUTION );
  TEST_EQUALITY_CONST( properties.getCoupledElasticSamplingMode(),
                       MonteCarlo::SIMPLIFIED_UNION );
  TEST_EQUALITY_CONST( properties.getElasticCutoffAngleCosine(), 1.0 );
  TEST_ASSERT( properties.isElectroionizationModeOn() );
  TEST_EQUALITY_CONST( properties.getElectroionizationTwoDInterpPolicy(),
                       MonteCarlo::LOGLOGLOG_INTERPOLATION );
  TEST_ASSERT( properties.isBremsstrahlungModeOn() );
  TEST_EQUALITY_CONST( properties.getBremsstrahlungTwoDInterpPolicy(),
                       MonteCarlo::LOGLOGLOG_INTERPOLATION );
  TEST_EQUALITY_CONST( properties.getBremsstrahlungAngularDistributionFunction(),
                       MonteCarlo::TWOBS_DISTRIBUTION );
  TEST_ASSERT( properties.isAtomicExcitationModeOn() );
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
// Test that the electron evaluation tolerance can be set
TEUCHOS_UNIT_TEST( SimulationElectronProperties, setElectronEvaluationTolerance )
{
  MonteCarlo::SimulationElectronProperties properties;
  
  properties.setElectronEvaluationTolerance( 1e-4 );

  TEST_EQUALITY( properties.getElectronEvaluationTolerance(), 1e-4 );
}

//---------------------------------------------------------------------------//
// Test that correlated sampling mode can be turned off
TEUCHOS_UNIT_TEST( SimulationElectronProperties, setCorrelatedSamplingModeOffOn )
{
  MonteCarlo::SimulationElectronProperties properties;

  properties.setCorrelatedSamplingModeOff();

  TEST_ASSERT( !properties.isCorrelatedSamplingModeOn() );

  properties.setCorrelatedSamplingModeOn();
  
  TEST_ASSERT( properties.isCorrelatedSamplingModeOn() );
}

//---------------------------------------------------------------------------//
// Test that unit based interpolation mode can be turned off
TEUCHOS_UNIT_TEST( SimulationElectronProperties, setUnitBasedInterpolationModeOffOn )
{
  MonteCarlo::SimulationElectronProperties properties;

  properties.setUnitBasedInterpolationModeOff();

  TEST_ASSERT( !properties.isUnitBasedInterpolationModeOn() );

  properties.setUnitBasedInterpolationModeOn();
  
  TEST_ASSERT( properties.isUnitBasedInterpolationModeOn() );
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
// Test that elastic mode can be turned off
TEUCHOS_UNIT_TEST( SimulationElectronProperties, setElasticModeOffOn )
{
  MonteCarlo::SimulationElectronProperties properties;

  properties.setElasticModeOff();

  TEST_ASSERT( !properties.isElasticModeOn() );

  properties.setElasticModeOn();
  
  TEST_ASSERT( properties.isElasticModeOn() );
}

//---------------------------------------------------------------------------//
// Test that the elastic 2D interpolation policy can be set
TEUCHOS_UNIT_TEST( SimulationElectronProperties, setElasticTwoDInterpPolicy )
{
  MonteCarlo::SimulationElectronProperties properties;

  TEST_EQUALITY_CONST( properties.getElasticTwoDInterpPolicy(),
                       MonteCarlo::LOGLOGLOG_INTERPOLATION );

  MonteCarlo::TwoDInterpolationType interp;

  interp = MonteCarlo::LINLINLIN_INTERPOLATION;
  properties.setElasticTwoDInterpPolicy( interp );
  TEST_EQUALITY_CONST( properties.getElasticTwoDInterpPolicy(),
                       interp );

  interp = MonteCarlo::LINLINLOG_INTERPOLATION;
  properties.setElasticTwoDInterpPolicy( interp );
  TEST_EQUALITY_CONST( properties.getElasticTwoDInterpPolicy(),
                       interp );

  interp = MonteCarlo::LINLOGLIN_INTERPOLATION;
  properties.setElasticTwoDInterpPolicy( interp );
  TEST_EQUALITY_CONST( properties.getElasticTwoDInterpPolicy(),
                       interp );

  interp = MonteCarlo::LOGLINLIN_INTERPOLATION;
  properties.setElasticTwoDInterpPolicy( interp );
  TEST_EQUALITY_CONST( properties.getElasticTwoDInterpPolicy(),
                       interp );

  interp = MonteCarlo::LINLOGLOG_INTERPOLATION;
  properties.setElasticTwoDInterpPolicy( interp );
  TEST_EQUALITY_CONST( properties.getElasticTwoDInterpPolicy(),
                       interp );

  interp = MonteCarlo::LOGLINLOG_INTERPOLATION;
  properties.setElasticTwoDInterpPolicy( interp );
  TEST_EQUALITY_CONST( properties.getElasticTwoDInterpPolicy(),
                       interp );

  interp = MonteCarlo::LOGLOGLIN_INTERPOLATION;
  properties.setElasticTwoDInterpPolicy( interp );
  TEST_EQUALITY_CONST( properties.getElasticTwoDInterpPolicy(),
                       interp );

  interp = MonteCarlo::LOGLOGLOG_INTERPOLATION;
  properties.setElasticTwoDInterpPolicy( interp );
  TEST_EQUALITY_CONST( properties.getElasticTwoDInterpPolicy(),
                       interp );
}

//---------------------------------------------------------------------------//
// Test that the elastic distribution mode can be set
TEUCHOS_UNIT_TEST( SimulationElectronProperties, setElasticElectronDistributionMode )
{
  MonteCarlo::SimulationElectronProperties properties;

  TEST_EQUALITY_CONST( properties.getElasticElectronDistributionMode(),
                       MonteCarlo::DECOUPLED_DISTRIBUTION );

  MonteCarlo::ElasticElectronDistributionType mode;

  mode = MonteCarlo::COUPLED_DISTRIBUTION;
  properties.setElasticElectronDistributionMode( mode );
  TEST_EQUALITY_CONST( properties.getElasticElectronDistributionMode(),
                       mode );

  mode = MonteCarlo::HYBRID_DISTRIBUTION;
  properties.setElasticElectronDistributionMode( mode );
  TEST_EQUALITY_CONST( properties.getElasticElectronDistributionMode(),
                       mode );

  mode = MonteCarlo::CUTOFF_DISTRIBUTION;
  properties.setElasticElectronDistributionMode( mode );
  TEST_EQUALITY_CONST( properties.getElasticElectronDistributionMode(),
                       mode );

  mode = MonteCarlo::SCREENED_RUTHERFORD_DISTRIBUTION;
  properties.setElasticElectronDistributionMode( mode );
  TEST_EQUALITY_CONST( properties.getElasticElectronDistributionMode(),
                       mode );
}

//---------------------------------------------------------------------------//
// Test that the coupled elastic sampling mode can be set
TEUCHOS_UNIT_TEST( SimulationElectronProperties, setCoupledElasticSamplingMode )
{
  MonteCarlo::SimulationElectronProperties properties;

  TEST_EQUALITY_CONST( properties.getCoupledElasticSamplingMode(),
                       MonteCarlo::SIMPLIFIED_UNION );

  MonteCarlo::CoupledElasticSamplingMethod mode;

  mode = MonteCarlo::ONE_D_UNION;
  properties.setCoupledElasticSamplingMode( mode );
  TEST_EQUALITY_CONST( properties.getCoupledElasticSamplingMode(),
                       mode );

  mode = MonteCarlo::TWO_D_UNION;
  properties.setCoupledElasticSamplingMode( mode );
  TEST_EQUALITY_CONST( properties.getCoupledElasticSamplingMode(),
                       mode );

  mode = MonteCarlo::SIMPLIFIED_UNION;
  properties.setCoupledElasticSamplingMode( mode );
  TEST_EQUALITY_CONST( properties.getCoupledElasticSamplingMode(),
                       mode );
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
// Test that electroionization mode can be turned off
TEUCHOS_UNIT_TEST( SimulationElectronProperties, setElectroionizationModeOffOn )
{
  MonteCarlo::SimulationElectronProperties properties;

  properties.setElectroionizationModeOff();

  TEST_ASSERT( !properties.isElectroionizationModeOn() );

  properties.setElectroionizationModeOn();
  
  TEST_ASSERT( properties.isElectroionizationModeOn() );
}

//---------------------------------------------------------------------------//
// Test that the electroionization 2D interpolation policy can be set
TEUCHOS_UNIT_TEST( SimulationElectronProperties, setElectroionizationTwoDInterpPolicy )
{
  MonteCarlo::SimulationElectronProperties properties;

  TEST_EQUALITY_CONST( properties.getElectroionizationTwoDInterpPolicy(),
                       MonteCarlo::LOGLOGLOG_INTERPOLATION );

  MonteCarlo::TwoDInterpolationType interp;

  interp = MonteCarlo::LINLINLIN_INTERPOLATION;
  properties.setElectroionizationTwoDInterpPolicy( interp );
  TEST_EQUALITY_CONST( properties.getElectroionizationTwoDInterpPolicy(),
                       interp );

  interp = MonteCarlo::LINLINLOG_INTERPOLATION;
  properties.setElectroionizationTwoDInterpPolicy( interp );
  TEST_EQUALITY_CONST( properties.getElectroionizationTwoDInterpPolicy(),
                       interp );

  interp = MonteCarlo::LINLOGLIN_INTERPOLATION;
  properties.setElectroionizationTwoDInterpPolicy( interp );
  TEST_EQUALITY_CONST( properties.getElectroionizationTwoDInterpPolicy(),
                       interp );

  interp = MonteCarlo::LOGLINLIN_INTERPOLATION;
  properties.setElectroionizationTwoDInterpPolicy( interp );
  TEST_EQUALITY_CONST( properties.getElectroionizationTwoDInterpPolicy(),
                       interp );

  interp = MonteCarlo::LINLOGLOG_INTERPOLATION;
  properties.setElectroionizationTwoDInterpPolicy( interp );
  TEST_EQUALITY_CONST( properties.getElectroionizationTwoDInterpPolicy(),
                       interp );

  interp = MonteCarlo::LOGLINLOG_INTERPOLATION;
  properties.setElectroionizationTwoDInterpPolicy( interp );
  TEST_EQUALITY_CONST( properties.getElectroionizationTwoDInterpPolicy(),
                       interp );

  interp = MonteCarlo::LOGLOGLIN_INTERPOLATION;
  properties.setElectroionizationTwoDInterpPolicy( interp );
  TEST_EQUALITY_CONST( properties.getElectroionizationTwoDInterpPolicy(),
                       interp );

  interp = MonteCarlo::LOGLOGLOG_INTERPOLATION;
  properties.setElectroionizationTwoDInterpPolicy( interp );
  TEST_EQUALITY_CONST( properties.getElectroionizationTwoDInterpPolicy(),
                       interp );
}

//---------------------------------------------------------------------------//
// Test that bremsstrahlung mode can be turned off
TEUCHOS_UNIT_TEST( SimulationElectronProperties, setBremsstrahlungModeOffOn )
{
  MonteCarlo::SimulationElectronProperties properties;

  properties.setBremsstrahlungModeOff();

  TEST_ASSERT( !properties.isBremsstrahlungModeOn() );

  properties.setBremsstrahlungModeOn();
  
  TEST_ASSERT( properties.isBremsstrahlungModeOn() );
}

//---------------------------------------------------------------------------//
// Test that the bremsstrahlung 2D interpolation policy can be set
TEUCHOS_UNIT_TEST( SimulationElectronProperties, setBremsstrahlungTwoDInterpPolicy )
{
  MonteCarlo::SimulationElectronProperties properties;

  TEST_EQUALITY_CONST( properties.getBremsstrahlungTwoDInterpPolicy(),
                       MonteCarlo::LOGLOGLOG_INTERPOLATION );

  MonteCarlo::TwoDInterpolationType interp;

  interp = MonteCarlo::LINLINLIN_INTERPOLATION;
  properties.setBremsstrahlungTwoDInterpPolicy( interp );
  TEST_EQUALITY_CONST( properties.getBremsstrahlungTwoDInterpPolicy(),
                       interp );

  interp = MonteCarlo::LINLINLOG_INTERPOLATION;
  properties.setBremsstrahlungTwoDInterpPolicy( interp );
  TEST_EQUALITY_CONST( properties.getBremsstrahlungTwoDInterpPolicy(),
                       interp );

  interp = MonteCarlo::LINLOGLIN_INTERPOLATION;
  properties.setBremsstrahlungTwoDInterpPolicy( interp );
  TEST_EQUALITY_CONST( properties.getBremsstrahlungTwoDInterpPolicy(),
                       interp );

  interp = MonteCarlo::LOGLINLIN_INTERPOLATION;
  properties.setBremsstrahlungTwoDInterpPolicy( interp );
  TEST_EQUALITY_CONST( properties.getBremsstrahlungTwoDInterpPolicy(),
                       interp );

  interp = MonteCarlo::LINLOGLOG_INTERPOLATION;
  properties.setBremsstrahlungTwoDInterpPolicy( interp );
  TEST_EQUALITY_CONST( properties.getBremsstrahlungTwoDInterpPolicy(),
                       interp );

  interp = MonteCarlo::LOGLINLOG_INTERPOLATION;
  properties.setBremsstrahlungTwoDInterpPolicy( interp );
  TEST_EQUALITY_CONST( properties.getBremsstrahlungTwoDInterpPolicy(),
                       interp );

  interp = MonteCarlo::LOGLOGLIN_INTERPOLATION;
  properties.setBremsstrahlungTwoDInterpPolicy( interp );
  TEST_EQUALITY_CONST( properties.getBremsstrahlungTwoDInterpPolicy(),
                       interp );

  interp = MonteCarlo::LOGLOGLOG_INTERPOLATION;
  properties.setBremsstrahlungTwoDInterpPolicy( interp );
  TEST_EQUALITY_CONST( properties.getBremsstrahlungTwoDInterpPolicy(),
                       interp );
}

//---------------------------------------------------------------------------//
// Test that the bremsstrahlung angular distribution function can be turned to Dipole
TEUCHOS_UNIT_TEST( SimulationElectronProperties,
                   setBremsstrahlungAngularDistributionFunction_Dipole )
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
TEUCHOS_UNIT_TEST( SimulationElectronProperties,
                   setBremsstrahlungAngularDistributionFunction_Tabular )
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
// Test that atomic excitation mode can be turned off
TEUCHOS_UNIT_TEST( SimulationElectronProperties, setAtomicExcitationModeOffOn )
{
  MonteCarlo::SimulationElectronProperties properties;

  properties.setAtomicExcitationModeOff();

  TEST_ASSERT( !properties.isAtomicExcitationModeOn() );

  properties.setAtomicExcitationModeOn();
  
  TEST_ASSERT( properties.isAtomicExcitationModeOn() );
}

//---------------------------------------------------------------------------//
// end tstSimulationElectronProperties.cpp
//---------------------------------------------------------------------------//
