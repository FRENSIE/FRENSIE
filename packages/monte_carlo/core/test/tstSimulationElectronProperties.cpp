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
#include "MonteCarlo_TwoDSamplingType.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef std::tuple<
  std::tuple<boost::archive::xml_oarchive,boost::archive::xml_iarchive>,
  std::tuple<boost::archive::text_oarchive,boost::archive::text_iarchive>,
  std::tuple<boost::archive::binary_oarchive,boost::archive::binary_iarchive>,
  std::tuple<Utility::HDF5OArchive,Utility::HDF5IArchive>,
  std::tuple<boost::archive::polymorphic_oarchive*,boost::archive::polymorphic_iarchive*>
  > TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Test the simulation properties defaults
FRENSIE_UNIT_TEST( SimulationElectronProperties, defaults )
{
  MonteCarlo::SimulationElectronProperties properties;

  FRENSIE_CHECK_EQUAL( properties.getMinElectronEnergy(), 1.5e-5 );
  FRENSIE_CHECK_EQUAL( properties.getMaxElectronEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( properties.getElectronEvaluationTolerance(), 1e-7 );
  FRENSIE_CHECK_EQUAL( properties.getElectronTwoDInterpPolicy(),
                       MonteCarlo::LOGLOGLOG_INTERPOLATION );
  FRENSIE_CHECK_EQUAL( properties.getElectronTwoDSamplingPolicy(),
                       MonteCarlo::UNIT_BASE_CORRELATED_SAMPLING );
  FRENSIE_CHECK( properties.isAtomicRelaxationModeOn() );
  FRENSIE_CHECK( properties.isElasticModeOn() );
  FRENSIE_CHECK_EQUAL( properties.getElasticElectronDistributionMode(),
                       MonteCarlo::DECOUPLED_DISTRIBUTION );
  FRENSIE_CHECK_EQUAL( properties.getCoupledElasticSamplingMode(),
                       MonteCarlo::SIMPLIFIED_UNION );
  FRENSIE_CHECK_EQUAL( properties.getElasticCutoffAngleCosine(), 1.0 );
  FRENSIE_CHECK( properties.isElectroionizationModeOn() );
  FRENSIE_CHECK( properties.isBremsstrahlungModeOn() );
  FRENSIE_CHECK_EQUAL( properties.getBremsstrahlungAngularDistributionFunction(),
                       MonteCarlo::TWOBS_DISTRIBUTION );
  FRENSIE_CHECK( properties.isAtomicExcitationModeOn() );
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
FRENSIE_UNIT_TEST( SimulationElectronProperties, setElectronTwoDSamplingPolicy )
{
  MonteCarlo::SimulationElectronProperties properties;

  FRENSIE_CHECK_EQUAL( properties.getElectronTwoDSamplingPolicy(),
                       MonteCarlo::UNIT_BASE_CORRELATED_SAMPLING );

  MonteCarlo::TwoDSamplingType type = MonteCarlo::CORRELATED_SAMPLING;
  properties.setElectronTwoDSamplingPolicy( type );
  FRENSIE_CHECK_EQUAL( properties.getElectronTwoDSamplingPolicy(), type );

  type = MonteCarlo::DIRECT_SAMPLING;
  properties.setElectronTwoDSamplingPolicy( type );
  FRENSIE_CHECK_EQUAL( properties.getElectronTwoDSamplingPolicy(), type );

  type = MonteCarlo::UNIT_BASE_SAMPLING;
  properties.setElectronTwoDSamplingPolicy( type );
  FRENSIE_CHECK_EQUAL( properties.getElectronTwoDSamplingPolicy(), type );

  type = MonteCarlo::UNIT_BASE_CORRELATED_SAMPLING;
  properties.setElectronTwoDSamplingPolicy( type );
  FRENSIE_CHECK_EQUAL( properties.getElectronTwoDSamplingPolicy(), type );
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
                       MonteCarlo::DECOUPLED_DISTRIBUTION );

  MonteCarlo::ElasticElectronDistributionType mode;

  mode = MonteCarlo::COUPLED_DISTRIBUTION;
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
                       MonteCarlo::SIMPLIFIED_UNION );

  MonteCarlo::CoupledElasticSamplingMethod mode;

  mode = MonteCarlo::ONE_D_UNION;
  properties.setCoupledElasticSamplingMode( mode );
  FRENSIE_CHECK_EQUAL( properties.getCoupledElasticSamplingMode(),
                       mode );

  mode = MonteCarlo::TWO_D_UNION;
  properties.setCoupledElasticSamplingMode( mode );
  FRENSIE_CHECK_EQUAL( properties.getCoupledElasticSamplingMode(),
                       mode );

  mode = MonteCarlo::SIMPLIFIED_UNION;
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
// Test that the bremsstrahlung angular distribution function can be turned to Dipole
FRENSIE_UNIT_TEST( SimulationElectronProperties,
                   setBremsstrahlungAngularDistributionFunction_Dipole )
{
  MonteCarlo::SimulationElectronProperties properties;
  
  MonteCarlo::BremsstrahlungAngularDistributionType function;
  function = MonteCarlo::DIPOLE_DISTRIBUTION;

  properties.setBremsstrahlungAngularDistributionFunction( function );

  FRENSIE_CHECK_EQUAL(
                     properties.getBremsstrahlungAngularDistributionFunction(),
                     MonteCarlo::DIPOLE_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Test that the bremsstrahlung angular distribution function can be turned to Tabular
FRENSIE_UNIT_TEST( SimulationElectronProperties,
                   setBremsstrahlungAngularDistributionFunction_Tabular )
{
  MonteCarlo::SimulationElectronProperties properties;
  
  MonteCarlo::BremsstrahlungAngularDistributionType function;
  function = MonteCarlo::TABULAR_DISTRIBUTION;

  properties.setBremsstrahlungAngularDistributionFunction( function );

  FRENSIE_CHECK_EQUAL(
                     properties.getBremsstrahlungAngularDistributionFunction(),
                     MonteCarlo::TABULAR_DISTRIBUTION );
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
    custom_properties.setElectronTwoDSamplingPolicy( MonteCarlo::DIRECT_SAMPLING );
    custom_properties.setAtomicRelaxationModeOff();
    custom_properties.setElasticModeOff();
    custom_properties.setElasticElectronDistributionMode( MonteCarlo::COUPLED_DISTRIBUTION );
    custom_properties.setCoupledElasticSamplingMode( MonteCarlo::ONE_D_UNION );
    custom_properties.setElasticCutoffAngleCosine( 0.9 );
    custom_properties.setElectroionizationModeOff();
    custom_properties.setBremsstrahlungModeOff();
    custom_properties.setBremsstrahlungAngularDistributionFunction( MonteCarlo::DIPOLE_DISTRIBUTION );
    custom_properties.setAtomicExcitationModeOff();

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

  FRENSIE_CHECK_EQUAL( default_properties.getMinElectronEnergy(), 1.5e-5 );
  FRENSIE_CHECK_EQUAL( default_properties.getMaxElectronEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( default_properties.getElectronEvaluationTolerance(), 1e-7 );
  FRENSIE_CHECK_EQUAL( default_properties.getElectronTwoDInterpPolicy(),
                       MonteCarlo::LOGLOGLOG_INTERPOLATION );
  FRENSIE_CHECK_EQUAL( default_properties.getElectronTwoDSamplingPolicy(),
                       MonteCarlo::UNIT_BASE_CORRELATED_SAMPLING );
  FRENSIE_CHECK( default_properties.isAtomicRelaxationModeOn() );
  FRENSIE_CHECK( default_properties.isElasticModeOn() );
  FRENSIE_CHECK_EQUAL( default_properties.getElasticElectronDistributionMode(),
                       MonteCarlo::DECOUPLED_DISTRIBUTION );
  FRENSIE_CHECK_EQUAL( default_properties.getCoupledElasticSamplingMode(),
                       MonteCarlo::SIMPLIFIED_UNION );
  FRENSIE_CHECK_EQUAL( default_properties.getElasticCutoffAngleCosine(), 1.0 );
  FRENSIE_CHECK( default_properties.isElectroionizationModeOn() );
  FRENSIE_CHECK( default_properties.isBremsstrahlungModeOn() );
  FRENSIE_CHECK_EQUAL( default_properties.getBremsstrahlungAngularDistributionFunction(),
                       MonteCarlo::TWOBS_DISTRIBUTION );
  FRENSIE_CHECK( default_properties.isAtomicExcitationModeOn() );

  MonteCarlo::SimulationElectronProperties custom_properties;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( custom_properties ) );

  FRENSIE_CHECK_EQUAL( custom_properties.getMinElectronEnergy(), 1e-2 );
  FRENSIE_CHECK_EQUAL( custom_properties.getMaxElectronEnergy(), 15.0 );
  FRENSIE_CHECK_EQUAL( custom_properties.getElectronEvaluationTolerance(), 1e-4 );
  FRENSIE_CHECK_EQUAL( custom_properties.getElectronTwoDInterpPolicy(),
                       MonteCarlo::LINLINLIN_INTERPOLATION );
  FRENSIE_CHECK_EQUAL( custom_properties.getElectronTwoDSamplingPolicy(),
                       MonteCarlo::DIRECT_SAMPLING )
  FRENSIE_CHECK( !custom_properties.isAtomicRelaxationModeOn() );
  FRENSIE_CHECK( !custom_properties.isElasticModeOn() );
  FRENSIE_CHECK_EQUAL( custom_properties.getElasticElectronDistributionMode(),
                       MonteCarlo::COUPLED_DISTRIBUTION );
  FRENSIE_CHECK_EQUAL( custom_properties.getCoupledElasticSamplingMode(),
                       MonteCarlo::ONE_D_UNION );
  FRENSIE_CHECK_EQUAL( custom_properties.getElasticCutoffAngleCosine(), 0.9 );
  FRENSIE_CHECK( !custom_properties.isElectroionizationModeOn() );
  FRENSIE_CHECK( !custom_properties.isBremsstrahlungModeOn() );
  FRENSIE_CHECK_EQUAL( custom_properties.getBremsstrahlungAngularDistributionFunction(),
                       MonteCarlo::DIPOLE_DISTRIBUTION );
  FRENSIE_CHECK( !custom_properties.isAtomicExcitationModeOn() );
}

//---------------------------------------------------------------------------//
// end tstSimulationElectronProperties.cpp
//---------------------------------------------------------------------------//
