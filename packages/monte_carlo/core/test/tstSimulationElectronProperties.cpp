//---------------------------------------------------------------------------//
//!
//! \file   tstSimulationElectronProperties.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation electron properties unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_SimulationElectronProperties.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "MonteCarlo_ElasticElectronDistributionType.hpp"
#include "MonteCarlo_TwoDInterpolationType.hpp"
#include "MonteCarlo_TwoDGridType.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Test the simulation properties defaults
FRENSIE_UNIT_TEST( SimulationElectronProperties, defaults )
{
  MonteCarlo::SimulationElectronProperties properties;

  FRENSIE_CHECK_EQUAL( properties.getMinElectronEnergy(), 1e-4 );
  FRENSIE_CHECK_EQUAL( properties.getMaxElectronEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( properties.getElectronEvaluationTolerance(), 1e-7 );
  FRENSIE_CHECK_EQUAL( properties.getElectronTwoDInterpPolicy(),
                       MonteCarlo::LOGLOGLOG_INTERPOLATION );
  FRENSIE_CHECK_EQUAL( properties.getElectronTwoDGridPolicy(),
                       MonteCarlo::UNIT_BASE_CORRELATED_GRID );
  FRENSIE_CHECK( properties.isAtomicRelaxationModeOn() );
  FRENSIE_CHECK( properties.isElasticModeOn() );
  FRENSIE_CHECK_EQUAL( properties.getElasticElectronDistributionMode(),
                       MonteCarlo::COUPLED_DISTRIBUTION );
  FRENSIE_CHECK_EQUAL( properties.getCoupledElasticSamplingMode(),
                       MonteCarlo::MODIFIED_TWO_D_UNION );
  FRENSIE_CHECK_EQUAL( properties.getElasticCutoffAngleCosine(), 1.0 );
  FRENSIE_CHECK( properties.isElectroionizationModeOn() );
  FRENSIE_CHECK_EQUAL( properties.getElectroionizationSamplingMode(),
                       MonteCarlo::KNOCK_ON_SAMPLING );
  FRENSIE_CHECK( properties.isBremsstrahlungModeOn() );
  FRENSIE_CHECK_EQUAL( properties.getBremsstrahlungAngularDistributionFunction(),
                       MonteCarlo::TWOBS_DISTRIBUTION );
  FRENSIE_CHECK( properties.isAtomicExcitationModeOn() );
  FRENSIE_CHECK_SMALL( properties.getElectronRouletteThresholdWeight(), 1e-30 );
  FRENSIE_CHECK_SMALL( properties.getElectronRouletteSurvivalWeight(), 1e-30 );
}

//---------------------------------------------------------------------------//
// Test that the min electron energy can be set
FRENSIE_UNIT_TEST( SimulationElectronProperties, setMinElectronEnergy )
{
  MonteCarlo::SimulationElectronProperties properties;

  properties.setMinElectronEnergy( 1e-2 );

  FRENSIE_CHECK_EQUAL( properties.getMinElectronEnergy(), 1e-2 );
}

//---------------------------------------------------------------------------//
// Test that the max electron energy can be set
FRENSIE_UNIT_TEST( SimulationElectronProperties, setMaxElectronEnergy )
{
  MonteCarlo::SimulationElectronProperties properties;

  properties.setMaxElectronEnergy( 15.0 );

  FRENSIE_CHECK_EQUAL( properties.getMaxElectronEnergy(), 15.0 );
}

//---------------------------------------------------------------------------//
// Test that the electron evaluation tolerance can be set
FRENSIE_UNIT_TEST( SimulationElectronProperties, setElectronEvaluationTolerance )
{
  MonteCarlo::SimulationElectronProperties properties;

  properties.setElectronEvaluationTolerance( 1e-4 );

  FRENSIE_CHECK_EQUAL( properties.getElectronEvaluationTolerance(), 1e-4 );
}

//---------------------------------------------------------------------------//
// Test that the electron 2D interpolation policy can be set
FRENSIE_UNIT_TEST( SimulationElectronProperties, setElectronTwoDInterpPolicy )
{
  MonteCarlo::SimulationElectronProperties properties;

  FRENSIE_CHECK_EQUAL( properties.getElectronTwoDInterpPolicy(),
                       MonteCarlo::LOGLOGLOG_INTERPOLATION );

  MonteCarlo::TwoDInterpolationType interp;

  interp = MonteCarlo::LINLINLIN_INTERPOLATION;
  properties.setElectronTwoDInterpPolicy( interp );
  FRENSIE_CHECK_EQUAL( properties.getElectronTwoDInterpPolicy(), interp );

  interp = MonteCarlo::LINLINLOG_INTERPOLATION;
  properties.setElectronTwoDInterpPolicy( interp );
  FRENSIE_CHECK_EQUAL( properties.getElectronTwoDInterpPolicy(), interp );

  interp = MonteCarlo::LINLOGLIN_INTERPOLATION;
  properties.setElectronTwoDInterpPolicy( interp );
  FRENSIE_CHECK_EQUAL( properties.getElectronTwoDInterpPolicy(), interp );

  interp = MonteCarlo::LOGLINLIN_INTERPOLATION;
  properties.setElectronTwoDInterpPolicy( interp );
  FRENSIE_CHECK_EQUAL( properties.getElectronTwoDInterpPolicy(), interp );

  interp = MonteCarlo::LINLOGLOG_INTERPOLATION;
  properties.setElectronTwoDInterpPolicy( interp );
  FRENSIE_CHECK_EQUAL( properties.getElectronTwoDInterpPolicy(), interp );

  interp = MonteCarlo::LOGLINLOG_INTERPOLATION;
  properties.setElectronTwoDInterpPolicy( interp );
  FRENSIE_CHECK_EQUAL( properties.getElectronTwoDInterpPolicy(), interp );

  interp = MonteCarlo::LOGLOGLIN_INTERPOLATION;
  properties.setElectronTwoDInterpPolicy( interp );
  FRENSIE_CHECK_EQUAL( properties.getElectronTwoDInterpPolicy(), interp );

  interp = MonteCarlo::LOGLOGLOG_INTERPOLATION;
  properties.setElectronTwoDInterpPolicy( interp );
  FRENSIE_CHECK_EQUAL( properties.getElectronTwoDInterpPolicy(), interp );
}

//---------------------------------------------------------------------------//
// Test that the electron 2D sampling policy can be set
FRENSIE_UNIT_TEST( SimulationElectronProperties, setElectronTwoDGridPolicy )
{
  MonteCarlo::SimulationElectronProperties properties;

  FRENSIE_CHECK_EQUAL( properties.getElectronTwoDGridPolicy(),
                       MonteCarlo::UNIT_BASE_CORRELATED_GRID );

  MonteCarlo::TwoDGridType type = MonteCarlo::CORRELATED_GRID;
  properties.setElectronTwoDGridPolicy( type );
  FRENSIE_CHECK_EQUAL( properties.getElectronTwoDGridPolicy(), type );

  type = MonteCarlo::DIRECT_GRID;
  properties.setElectronTwoDGridPolicy( type );
  FRENSIE_CHECK_EQUAL( properties.getElectronTwoDGridPolicy(), type );

  type = MonteCarlo::UNIT_BASE_GRID;
  properties.setElectronTwoDGridPolicy( type );
  FRENSIE_CHECK_EQUAL( properties.getElectronTwoDGridPolicy(), type );

  type = MonteCarlo::UNIT_BASE_CORRELATED_GRID;
  properties.setElectronTwoDGridPolicy( type );
  FRENSIE_CHECK_EQUAL( properties.getElectronTwoDGridPolicy(), type );
}

//---------------------------------------------------------------------------//
// Test that atomic relaxation mode can be turned off
FRENSIE_UNIT_TEST( SimulationElectronProperties, setAtomicRelaxationModeOffOn )
{
  MonteCarlo::SimulationElectronProperties properties;

  properties.setAtomicRelaxationModeOff();

  FRENSIE_CHECK( !properties.isAtomicRelaxationModeOn() );

  properties.setAtomicRelaxationModeOn();

  FRENSIE_CHECK( properties.isAtomicRelaxationModeOn() );
}

//---------------------------------------------------------------------------//
// Test that elastic mode can be turned off
FRENSIE_UNIT_TEST( SimulationElectronProperties, setElasticModeOffOn )
{
  MonteCarlo::SimulationElectronProperties properties;

  properties.setElasticModeOff();

  FRENSIE_CHECK( !properties.isElasticModeOn() );

  properties.setElasticModeOn();

  FRENSIE_CHECK( properties.isElasticModeOn() );
}

//---------------------------------------------------------------------------//
// Test that the elastic distribution mode can be set
FRENSIE_UNIT_TEST( SimulationElectronProperties, setElasticElectronDistributionMode )
{
  MonteCarlo::SimulationElectronProperties properties;

  FRENSIE_CHECK_EQUAL( properties.getElasticElectronDistributionMode(),
                       MonteCarlo::COUPLED_DISTRIBUTION );

  MonteCarlo::ElasticElectronDistributionType mode;

  mode = MonteCarlo::DECOUPLED_DISTRIBUTION;
  properties.setElasticElectronDistributionMode( mode );
  FRENSIE_CHECK_EQUAL( properties.getElasticElectronDistributionMode(),
                       mode );

  mode = MonteCarlo::HYBRID_DISTRIBUTION;
  properties.setElasticElectronDistributionMode( mode );
  FRENSIE_CHECK_EQUAL( properties.getElasticElectronDistributionMode(),
                       mode );

  mode = MonteCarlo::CUTOFF_DISTRIBUTION;
  properties.setElasticElectronDistributionMode( mode );
  FRENSIE_CHECK_EQUAL( properties.getElasticElectronDistributionMode(),
                       mode );

  mode = MonteCarlo::SCREENED_RUTHERFORD_DISTRIBUTION;
  properties.setElasticElectronDistributionMode( mode );
  FRENSIE_CHECK_EQUAL( properties.getElasticElectronDistributionMode(),
                       mode );
}

//---------------------------------------------------------------------------//
// Test that the coupled elastic sampling mode can be set
FRENSIE_UNIT_TEST( SimulationElectronProperties, setCoupledElasticSamplingMode )
{
  MonteCarlo::SimulationElectronProperties properties;

  FRENSIE_CHECK_EQUAL( properties.getCoupledElasticSamplingMode(),
                       MonteCarlo::MODIFIED_TWO_D_UNION );

  MonteCarlo::CoupledElasticSamplingMethod mode;

  mode = MonteCarlo::ONE_D_UNION;
  properties.setCoupledElasticSamplingMode( mode );
  FRENSIE_CHECK_EQUAL( properties.getCoupledElasticSamplingMode(),
                       mode );

  mode = MonteCarlo::TWO_D_UNION;
  properties.setCoupledElasticSamplingMode( mode );
  FRENSIE_CHECK_EQUAL( properties.getCoupledElasticSamplingMode(),
                       mode );

  mode = MonteCarlo::MODIFIED_TWO_D_UNION;
  properties.setCoupledElasticSamplingMode( mode );
  FRENSIE_CHECK_EQUAL( properties.getCoupledElasticSamplingMode(),
                       mode );
}

//---------------------------------------------------------------------------//
// Test that the elastic cutoff angle cosine can be set
FRENSIE_UNIT_TEST( SimulationElectronProperties, setElasticCutoffAngleCosine )
{
  MonteCarlo::SimulationElectronProperties properties;

  properties.setElasticCutoffAngleCosine( 0.9 );

  FRENSIE_CHECK_EQUAL( properties.getElasticCutoffAngleCosine(), 0.9 );
}

//---------------------------------------------------------------------------//
// Test that electroionization mode can be turned off
FRENSIE_UNIT_TEST( SimulationElectronProperties, setElectroionizationModeOffOn )
{
  MonteCarlo::SimulationElectronProperties properties;

  properties.setElectroionizationModeOff();

  FRENSIE_CHECK( !properties.isElectroionizationModeOn() );

  properties.setElectroionizationModeOn();

  FRENSIE_CHECK( properties.isElectroionizationModeOn() );
}

//---------------------------------------------------------------------------//
// Test that the electroionization sampling mode can be set
FRENSIE_UNIT_TEST( SimulationElectronProperties,
                   setElectroionizationSamplingMode )
{
  MonteCarlo::SimulationElectronProperties properties;

  MonteCarlo::ElectroionizationSamplingType function;

  function = MonteCarlo::KNOCK_ON_SAMPLING;
  properties.setElectroionizationSamplingMode( function );
  FRENSIE_CHECK_EQUAL( properties.getElectroionizationSamplingMode(), function);

  function = MonteCarlo::OUTGOING_ENERGY_SAMPLING;
  properties.setElectroionizationSamplingMode( function );
  FRENSIE_CHECK_EQUAL( properties.getElectroionizationSamplingMode(), function);

  function = MonteCarlo::OUTGOING_ENERGY_RATIO_SAMPLING;
  properties.setElectroionizationSamplingMode( function );
  FRENSIE_CHECK_EQUAL( properties.getElectroionizationSamplingMode(), function);
}

//---------------------------------------------------------------------------//
// Test that bremsstrahlung mode can be turned off
FRENSIE_UNIT_TEST( SimulationElectronProperties, setBremsstrahlungModeOffOn )
{
  MonteCarlo::SimulationElectronProperties properties;

  properties.setBremsstrahlungModeOff();

  FRENSIE_CHECK( !properties.isBremsstrahlungModeOn() );

  properties.setBremsstrahlungModeOn();

  FRENSIE_CHECK( properties.isBremsstrahlungModeOn() );
}

//---------------------------------------------------------------------------//
// Test that the bremsstrahlung angular distribution function can be set
FRENSIE_UNIT_TEST( SimulationElectronProperties,
                   setBremsstrahlungAngularDistributionFunction )
{
  MonteCarlo::SimulationElectronProperties properties;

  MonteCarlo::BremsstrahlungAngularDistributionType function;

  function = MonteCarlo::DIPOLE_DISTRIBUTION;
  properties.setBremsstrahlungAngularDistributionFunction( function );
  FRENSIE_CHECK_EQUAL( properties.getBremsstrahlungAngularDistributionFunction(),
                       function );

  function = MonteCarlo::TABULAR_DISTRIBUTION;
  properties.setBremsstrahlungAngularDistributionFunction( function );
  FRENSIE_CHECK_EQUAL( properties.getBremsstrahlungAngularDistributionFunction(),
                       function );

  function = MonteCarlo::TWOBS_DISTRIBUTION;
  properties.setBremsstrahlungAngularDistributionFunction( function );
  FRENSIE_CHECK_EQUAL( properties.getBremsstrahlungAngularDistributionFunction(),
                       function );
}

//---------------------------------------------------------------------------//
// Test that atomic excitation mode can be turned off
FRENSIE_UNIT_TEST( SimulationElectronProperties, setAtomicExcitationModeOffOn )
{
  MonteCarlo::SimulationElectronProperties properties;

  properties.setAtomicExcitationModeOff();

  FRENSIE_CHECK( !properties.isAtomicExcitationModeOn() );

  properties.setAtomicExcitationModeOn();

  FRENSIE_CHECK( properties.isAtomicExcitationModeOn() );
}

//---------------------------------------------------------------------------//
// Check that the critical line energies can be set
FRENSIE_UNIT_TEST( SimulationElectronProperties,
                   getElectronRouletteThresholdWeight )
{
  MonteCarlo::SimulationElectronProperties properties;

  double weight = 1e-14;

  properties.setElectronRouletteThresholdWeight( weight );

  FRENSIE_CHECK_EQUAL( properties.getElectronRouletteThresholdWeight(),
                       weight );
}

//---------------------------------------------------------------------------//
// Check that the critical line energies can be set
FRENSIE_UNIT_TEST( SimulationElectronProperties,
                   getElectronRouletteSurvivalWeight )
{
  MonteCarlo::SimulationElectronProperties properties;

  double weight = 1e-12;

  properties.setElectronRouletteSurvivalWeight( weight );

  FRENSIE_CHECK_EQUAL( properties.getElectronRouletteSurvivalWeight(),
                       weight );
}

//---------------------------------------------------------------------------//
// Check that the properties can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( SimulationElectronProperties,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_simulation_electron_props" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    MonteCarlo::SimulationElectronProperties default_properties;

    MonteCarlo::SimulationElectronProperties custom_properties;
    custom_properties.setMinElectronEnergy( 1e-2 );
    custom_properties.setMaxElectronEnergy( 15.0 );
    custom_properties.setElectronEvaluationTolerance( 1e-4 );
    custom_properties.setElectronTwoDInterpPolicy( MonteCarlo::LINLINLIN_INTERPOLATION );
    custom_properties.setElectronTwoDGridPolicy( MonteCarlo::DIRECT_GRID );
    custom_properties.setAtomicRelaxationModeOff();
    custom_properties.setElasticModeOff();
    custom_properties.setElasticElectronDistributionMode( MonteCarlo::COUPLED_DISTRIBUTION );
    custom_properties.setCoupledElasticSamplingMode( MonteCarlo::ONE_D_UNION );
    custom_properties.setElasticCutoffAngleCosine( 0.9 );
    custom_properties.setElectroionizationModeOff();
    custom_properties.setElectroionizationSamplingMode( MonteCarlo::OUTGOING_ENERGY_SAMPLING );
    custom_properties.setBremsstrahlungModeOff();
    custom_properties.setBremsstrahlungAngularDistributionFunction( MonteCarlo::DIPOLE_DISTRIBUTION );
    custom_properties.setAtomicExcitationModeOff();
    custom_properties.setElectronRouletteThresholdWeight( 1e-15 );
    custom_properties.setElectronRouletteSurvivalWeight( 1e-13 );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( default_properties ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( custom_properties ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  MonteCarlo::SimulationElectronProperties default_properties;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( default_properties ) );

  FRENSIE_CHECK_EQUAL( default_properties.getMinElectronEnergy(), 1e-4 );
  FRENSIE_CHECK_EQUAL( default_properties.getMaxElectronEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( default_properties.getElectronEvaluationTolerance(), 1e-7 );
  FRENSIE_CHECK_EQUAL( default_properties.getElectronTwoDInterpPolicy(),
                       MonteCarlo::LOGLOGLOG_INTERPOLATION );
  FRENSIE_CHECK_EQUAL( default_properties.getElectronTwoDGridPolicy(),
                       MonteCarlo::UNIT_BASE_CORRELATED_GRID );
  FRENSIE_CHECK( default_properties.isAtomicRelaxationModeOn() );
  FRENSIE_CHECK( default_properties.isElasticModeOn() );
  FRENSIE_CHECK_EQUAL( default_properties.getElasticElectronDistributionMode(),
                       MonteCarlo::COUPLED_DISTRIBUTION );
  FRENSIE_CHECK_EQUAL( default_properties.getCoupledElasticSamplingMode(),
                       MonteCarlo::MODIFIED_TWO_D_UNION );
  FRENSIE_CHECK_EQUAL( default_properties.getElasticCutoffAngleCosine(), 1.0 );
  FRENSIE_CHECK( default_properties.isElectroionizationModeOn() );
  FRENSIE_CHECK_EQUAL( default_properties.getElectroionizationSamplingMode(),
                       MonteCarlo::KNOCK_ON_SAMPLING );
  FRENSIE_CHECK( default_properties.isBremsstrahlungModeOn() );
  FRENSIE_CHECK_EQUAL( default_properties.getBremsstrahlungAngularDistributionFunction(),
                       MonteCarlo::TWOBS_DISTRIBUTION );
  FRENSIE_CHECK( default_properties.isAtomicExcitationModeOn() );
  FRENSIE_CHECK_SMALL( default_properties.getElectronRouletteThresholdWeight(), 1e-30 );
  FRENSIE_CHECK_SMALL( default_properties.getElectronRouletteSurvivalWeight(), 1e-30  );

  MonteCarlo::SimulationElectronProperties custom_properties;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( custom_properties ) );

  FRENSIE_CHECK_EQUAL( custom_properties.getMinElectronEnergy(), 1e-2 );
  FRENSIE_CHECK_EQUAL( custom_properties.getMaxElectronEnergy(), 15.0 );
  FRENSIE_CHECK_EQUAL( custom_properties.getElectronEvaluationTolerance(), 1e-4 );
  FRENSIE_CHECK_EQUAL( custom_properties.getElectronTwoDInterpPolicy(),
                       MonteCarlo::LINLINLIN_INTERPOLATION );
  FRENSIE_CHECK_EQUAL( custom_properties.getElectronTwoDGridPolicy(),
                       MonteCarlo::DIRECT_GRID )
  FRENSIE_CHECK( !custom_properties.isAtomicRelaxationModeOn() );
  FRENSIE_CHECK( !custom_properties.isElasticModeOn() );
  FRENSIE_CHECK_EQUAL( custom_properties.getElasticElectronDistributionMode(),
                       MonteCarlo::COUPLED_DISTRIBUTION );
  FRENSIE_CHECK_EQUAL( custom_properties.getCoupledElasticSamplingMode(),
                       MonteCarlo::ONE_D_UNION );
  FRENSIE_CHECK_EQUAL( custom_properties.getElasticCutoffAngleCosine(), 0.9 );
  FRENSIE_CHECK( !custom_properties.isElectroionizationModeOn() );
  FRENSIE_CHECK_EQUAL( custom_properties.getElectroionizationSamplingMode(),
                       MonteCarlo::OUTGOING_ENERGY_SAMPLING );
  FRENSIE_CHECK( !custom_properties.isBremsstrahlungModeOn() );
  FRENSIE_CHECK_EQUAL( custom_properties.getBremsstrahlungAngularDistributionFunction(),
                       MonteCarlo::DIPOLE_DISTRIBUTION );
  FRENSIE_CHECK( !custom_properties.isAtomicExcitationModeOn() );
  FRENSIE_CHECK_EQUAL( custom_properties.getElectronRouletteThresholdWeight(), 1e-15 );
  FRENSIE_CHECK_EQUAL( custom_properties.getElectronRouletteSurvivalWeight(), 1e-13 );
}

//---------------------------------------------------------------------------//
// end tstSimulationElectronProperties.cpp
//---------------------------------------------------------------------------//
