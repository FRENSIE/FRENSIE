//---------------------------------------------------------------------------//
//!
//! \file   tstSimulationAdjointElectronProperties.cpp
//! \author Luke Kersting
//! \brief  Simulation adjoint electron properties unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_SimulationAdjointElectronProperties.hpp"
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
FRENSIE_UNIT_TEST( SimulationAdjointElectronProperties, defaults )
{
  MonteCarlo::SimulationAdjointElectronProperties properties;

  FRENSIE_CHECK_EQUAL( properties.getAbsoluteMinAdjointElectronEnergy(), 1e-5 );
  FRENSIE_CHECK_EQUAL( properties.getMinAdjointElectronEnergy(), 1e-5 );
  FRENSIE_CHECK_EQUAL( properties.getMaxAdjointElectronEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( properties.getAbsoluteMaxAdjointElectronEnergy(), 20.0 );
  FRENSIE_CHECK( properties.isAdjointElasticModeOn() );
  FRENSIE_CHECK( properties.isAdjointElectroionizationModeOn() );
  FRENSIE_CHECK( properties.isAdjointBremsstrahlungModeOn() );
  FRENSIE_CHECK( properties.isAdjointAtomicExcitationModeOn() );
  FRENSIE_CHECK_EQUAL( properties.getAdjointElasticElectronDistributionMode(),
                       MonteCarlo::COUPLED_DISTRIBUTION );
  FRENSIE_CHECK_EQUAL( properties.getAdjointCoupledElasticSamplingMode(),
                       MonteCarlo::MODIFIED_TWO_D_UNION );
  FRENSIE_CHECK_EQUAL(
             properties.getAdjointBremsstrahlungAngularDistributionFunction(),
             MonteCarlo::TWOBS_DISTRIBUTION );
  FRENSIE_CHECK_EQUAL( properties.getAdjointElectronEvaluationTolerance(), 1e-12 );
  FRENSIE_CHECK_EQUAL( properties.getAdjointElasticCutoffAngleCosine(),
                       1.0 );
  FRENSIE_CHECK_EQUAL( properties.getNumberOfAdjointElectronHashGridBins(),
                       500 );

}

//---------------------------------------------------------------------------//
// Check that the min adjoint electron energy can be set
FRENSIE_UNIT_TEST( SimulationAdjointElectronProperties,
                   setMinAdjointElectronEnergy )
{
  MonteCarlo::SimulationAdjointElectronProperties properties;

  properties.setMinAdjointElectronEnergy( 1e-2 );

  FRENSIE_CHECK_EQUAL( properties.getMinAdjointElectronEnergy(), 1e-2 );
}

//---------------------------------------------------------------------------//
// Check that the max adjoint electron energy can be set
FRENSIE_UNIT_TEST( SimulationAdjointElectronProperties,
                   setMaxAdjointElectronEnergy )
{
  MonteCarlo::SimulationAdjointElectronProperties properties;

  properties.setMaxAdjointElectronEnergy( 15.0 );

  FRENSIE_CHECK_EQUAL( properties.getMaxAdjointElectronEnergy(), 15.0 );
}

//---------------------------------------------------------------------------//
// Test that adjoint elastic mode can be turned off
FRENSIE_UNIT_TEST( SimulationAdjointElectronProperties,
                   setAdjointElasticModeOffOn )
{
  MonteCarlo::SimulationAdjointElectronProperties properties;

  properties.setAdjointElasticModeOff();

  FRENSIE_CHECK( !properties.isAdjointElasticModeOn() );

  properties.setAdjointElasticModeOn();

  FRENSIE_CHECK( properties.isAdjointElasticModeOn() );
}

//---------------------------------------------------------------------------//
// Test that adjoint electroionization mode can be turned off
FRENSIE_UNIT_TEST( SimulationAdjointElectronProperties,
                   setAdjointElectroionizationModeOffOn )
{
  MonteCarlo::SimulationAdjointElectronProperties properties;

  properties.setAdjointElectroionizationModeOff();

  FRENSIE_CHECK( !properties.isAdjointElectroionizationModeOn() );

  properties.setAdjointElectroionizationModeOn();

  FRENSIE_CHECK( properties.isAdjointElectroionizationModeOn() );
}

//---------------------------------------------------------------------------//
// Test that adjoint bremsstrahlung mode can be turned off
FRENSIE_UNIT_TEST( SimulationAdjointElectronProperties,
                   setAdjointBremsstrahlungModeOffOn )
{
  MonteCarlo::SimulationAdjointElectronProperties properties;

  properties.setAdjointBremsstrahlungModeOff();

  FRENSIE_CHECK( !properties.isAdjointBremsstrahlungModeOn() );

  properties.setAdjointBremsstrahlungModeOn();

  FRENSIE_CHECK( properties.isAdjointBremsstrahlungModeOn() );
}

//---------------------------------------------------------------------------//
// Test that adjoint atomic excitation mode can be turned off
FRENSIE_UNIT_TEST( SimulationAdjointElectronProperties,
                   setAdjointAtomicExcitationModeOffOn )
{
  MonteCarlo::SimulationAdjointElectronProperties properties;

  properties.setAdjointAtomicExcitationModeOff();

  FRENSIE_CHECK( !properties.isAdjointAtomicExcitationModeOn() );

  properties.setAdjointAtomicExcitationModeOn();

  FRENSIE_CHECK( properties.isAdjointAtomicExcitationModeOn() );
}

//---------------------------------------------------------------------------//
// Test that the adjoint electron evaluation tolerance can be set
FRENSIE_UNIT_TEST( SimulationAdjointElectronProperties,
                   setAdjointElectronEvaluationTolerance )
{
  MonteCarlo::SimulationAdjointElectronProperties properties;

  FRENSIE_CHECK_EQUAL( properties.getAdjointElectronEvaluationTolerance(), 1e-12 );

  properties.setAdjointElectronEvaluationTolerance( 1e-4 );

  FRENSIE_CHECK_EQUAL( properties.getAdjointElectronEvaluationTolerance(), 1e-4 );
}

//---------------------------------------------------------------------------//
// Test that the adjoint bremsstrahlung angular distribution function can be turned to Dipole
FRENSIE_UNIT_TEST( SimulationAdjointElectronProperties,
                   setAdjointBremsstrahlungAngularDistributionFunction_Dipole )
{
  MonteCarlo::SimulationAdjointElectronProperties properties;

  MonteCarlo::BremsstrahlungAngularDistributionType function;
  function = MonteCarlo::DIPOLE_DISTRIBUTION;

  properties.setAdjointBremsstrahlungAngularDistributionFunction( function );

  FRENSIE_CHECK_EQUAL(
             properties.getAdjointBremsstrahlungAngularDistributionFunction(),
             MonteCarlo::DIPOLE_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Test that the adjoint coupled elastic electron distribution mode can be set
FRENSIE_UNIT_TEST( SimulationAdjointElectronProperties,
                   setAdjointElasticElectronDistributionMode )
{
  MonteCarlo::SimulationAdjointElectronProperties properties;

  FRENSIE_CHECK_EQUAL( properties.getAdjointElasticElectronDistributionMode(),
                       MonteCarlo::COUPLED_DISTRIBUTION );

  MonteCarlo::ElasticElectronDistributionType mode;
  mode = MonteCarlo::DECOUPLED_DISTRIBUTION;

  properties.setAdjointElasticElectronDistributionMode( mode );

  FRENSIE_CHECK_EQUAL( properties.getAdjointElasticElectronDistributionMode(),
                       mode );
}

//---------------------------------------------------------------------------//
// Test that the adjoint coupled elastic sampling mode can be set
FRENSIE_UNIT_TEST( SimulationAdjointElectronProperties,
                   setAdjointCoupledElasticSamplingMode )
{
  MonteCarlo::SimulationAdjointElectronProperties properties;

  FRENSIE_CHECK_EQUAL( properties.getAdjointCoupledElasticSamplingMode(),
                       MonteCarlo::MODIFIED_TWO_D_UNION );

  MonteCarlo::CoupledElasticSamplingMethod mode;
  mode = MonteCarlo::TWO_D_UNION;

  properties.setAdjointCoupledElasticSamplingMode( mode );

  FRENSIE_CHECK_EQUAL( properties.getAdjointCoupledElasticSamplingMode(),
                       mode );
}

//---------------------------------------------------------------------------//
// Test that the adjoint bremsstrahlung angular distribution function can be turned to Tabular
FRENSIE_UNIT_TEST( SimulationAdjointElectronProperties,
                   setAdjointBremsstrahlungAngularDistributionFunction_Tabular )
{
  MonteCarlo::SimulationAdjointElectronProperties properties;

  MonteCarlo::BremsstrahlungAngularDistributionType function;
  function = MonteCarlo::TABULAR_DISTRIBUTION;

  properties.setAdjointBremsstrahlungAngularDistributionFunction( function );

  FRENSIE_CHECK_EQUAL(
             properties.getAdjointBremsstrahlungAngularDistributionFunction(),
             MonteCarlo::TABULAR_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Test that the adjoint elastic cutoff angle cosine can be set
FRENSIE_UNIT_TEST( SimulationAdjointElectronProperties,
                   setAdjointElasticCutoffAngleCosine )
{
  MonteCarlo::SimulationAdjointElectronProperties properties;

  properties.setAdjointElasticCutoffAngleCosine( 0.9 );

  FRENSIE_CHECK_EQUAL( properties.getAdjointElasticCutoffAngleCosine(), 0.9 );
}

//---------------------------------------------------------------------------//
// Check that the number of adjoint electron hash grid bins can be set
FRENSIE_UNIT_TEST( SimulationAdjointElectronProperties,
                   setNumberOfAdjointElectronHashGridBins )
{
  MonteCarlo::SimulationAdjointElectronProperties properties;

  properties.setNumberOfAdjointElectronHashGridBins( 750 );

  FRENSIE_CHECK_EQUAL( properties.getNumberOfAdjointElectronHashGridBins(),
                       750 );
}

//---------------------------------------------------------------------------//
// Check that the properties can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( SimulationAdjointElectronProperties,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_simulation_adjoint_electron_props" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    MonteCarlo::SimulationAdjointElectronProperties default_properties;

    MonteCarlo::SimulationAdjointElectronProperties custom_properties;
    custom_properties.setMinAdjointElectronEnergy( 1e-2 );
    custom_properties.setMaxAdjointElectronEnergy( 15.0 );
    custom_properties.setAdjointElasticModeOff();
    custom_properties.setAdjointElectroionizationModeOff();
    custom_properties.setAdjointBremsstrahlungModeOff();
    custom_properties.setAdjointAtomicExcitationModeOff();
    custom_properties.setAdjointElectronEvaluationTolerance( 1e-4 );
    custom_properties.setAdjointBremsstrahlungAngularDistributionFunction( MonteCarlo::DIPOLE_DISTRIBUTION );
    custom_properties.setAdjointElasticElectronDistributionMode( MonteCarlo::DECOUPLED_DISTRIBUTION );
    custom_properties.setAdjointCoupledElasticSamplingMode( MonteCarlo::TWO_D_UNION );
    custom_properties.setAdjointElasticCutoffAngleCosine( 0.9 );
    custom_properties.setNumberOfAdjointElectronHashGridBins( 750 );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( default_properties ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( custom_properties ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  MonteCarlo::SimulationAdjointElectronProperties default_properties;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( default_properties ) );

  FRENSIE_CHECK_EQUAL( default_properties.getAbsoluteMinAdjointElectronEnergy(), 1e-5 );
  FRENSIE_CHECK_EQUAL( default_properties.getMinAdjointElectronEnergy(), 1e-5 );
  FRENSIE_CHECK_EQUAL( default_properties.getMaxAdjointElectronEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( default_properties.getAbsoluteMaxAdjointElectronEnergy(), 20.0 );
  FRENSIE_CHECK( default_properties.isAdjointElasticModeOn() );
  FRENSIE_CHECK( default_properties.isAdjointElectroionizationModeOn() );
  FRENSIE_CHECK( default_properties.isAdjointBremsstrahlungModeOn() );
  FRENSIE_CHECK( default_properties.isAdjointAtomicExcitationModeOn() );
  FRENSIE_CHECK_EQUAL( default_properties.getAdjointElasticElectronDistributionMode(),
                       MonteCarlo::COUPLED_DISTRIBUTION );
  FRENSIE_CHECK_EQUAL( default_properties.getAdjointCoupledElasticSamplingMode(),
                       MonteCarlo::MODIFIED_TWO_D_UNION );
  FRENSIE_CHECK_EQUAL(
             default_properties.getAdjointBremsstrahlungAngularDistributionFunction(),
             MonteCarlo::TWOBS_DISTRIBUTION );
  FRENSIE_CHECK_EQUAL( default_properties.getAdjointElectronEvaluationTolerance(), 1e-12 );
  FRENSIE_CHECK_EQUAL( default_properties.getAdjointElasticCutoffAngleCosine(),
                       1.0 );
  FRENSIE_CHECK_EQUAL( default_properties.getNumberOfAdjointElectronHashGridBins(),
                       500 );

  MonteCarlo::SimulationAdjointElectronProperties custom_properties;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( custom_properties ) );

  FRENSIE_CHECK_EQUAL( custom_properties.getAbsoluteMinAdjointElectronEnergy(), 1e-5 );
  FRENSIE_CHECK_EQUAL( custom_properties.getMinAdjointElectronEnergy(), 1e-2 );
  FRENSIE_CHECK_EQUAL( custom_properties.getMaxAdjointElectronEnergy(), 15.0 );
  FRENSIE_CHECK_EQUAL( custom_properties.getAbsoluteMaxAdjointElectronEnergy(), 20.0 );
  FRENSIE_CHECK( !custom_properties.isAdjointElasticModeOn() );
  FRENSIE_CHECK( !custom_properties.isAdjointElectroionizationModeOn() );
  FRENSIE_CHECK( !custom_properties.isAdjointBremsstrahlungModeOn() );
  FRENSIE_CHECK( !custom_properties.isAdjointAtomicExcitationModeOn() );
  FRENSIE_CHECK_EQUAL( custom_properties.getAdjointElasticElectronDistributionMode(),
                       MonteCarlo::DECOUPLED_DISTRIBUTION );
  FRENSIE_CHECK_EQUAL( custom_properties.getAdjointCoupledElasticSamplingMode(),
                       MonteCarlo::TWO_D_UNION );
  FRENSIE_CHECK_EQUAL(
             custom_properties.getAdjointBremsstrahlungAngularDistributionFunction(),
             MonteCarlo::DIPOLE_DISTRIBUTION );
  FRENSIE_CHECK_EQUAL( custom_properties.getAdjointElectronEvaluationTolerance(), 1e-4 );
  FRENSIE_CHECK_EQUAL( custom_properties.getAdjointElasticCutoffAngleCosine(),
                       0.9 );
  FRENSIE_CHECK_EQUAL( custom_properties.getNumberOfAdjointElectronHashGridBins(),
                       750 );
}

//---------------------------------------------------------------------------//
// end tstSimulationAdjointElectronProperties.cpp
//---------------------------------------------------------------------------//
