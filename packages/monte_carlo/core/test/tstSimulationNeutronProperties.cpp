//---------------------------------------------------------------------------//
//!
//! \file   tstSimulationNeutronProperties.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation neutron properties unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_SimulationNeutronProperties.hpp"
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
FRENSIE_UNIT_TEST( SimulationNeutronProperties, defaults )
{
  MonteCarlo::SimulationNeutronProperties properties;

  FRENSIE_CHECK_EQUAL( properties.getAbsoluteMinNeutronEnergy(), 1e-11 );
  FRENSIE_CHECK_EQUAL( properties.getMinNeutronEnergy(), 1e-11 );
  FRENSIE_CHECK_EQUAL( properties.getMaxNeutronEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( properties.getNumberOfNeutronHashGridBins(), 1000u );
  FRENSIE_CHECK_EQUAL( properties.getAbsoluteMaxNeutronEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( properties.getFreeGasThreshold(), 400.0 );
  FRENSIE_CHECK( properties.isUnresolvedResonanceProbabilityTableModeOn() );
  FRENSIE_CHECK_SMALL( properties.getNeutronRouletteThresholdWeight(), 1e-30 );
  FRENSIE_CHECK_SMALL( properties.getNeutronRouletteSurvivalWeight(), 1e-30 );
}

//---------------------------------------------------------------------------//
// Test that the min neutron energy can be set
FRENSIE_UNIT_TEST( SimulationNeutronProperties, setMinNeutronEnergy )
{
  MonteCarlo::SimulationNeutronProperties properties;

  properties.setMinNeutronEnergy( 1e-8 );

  FRENSIE_CHECK_EQUAL( properties.getMinNeutronEnergy(), 1e-8 );
}

//---------------------------------------------------------------------------//
// Test that the max neutron energy can be set
FRENSIE_UNIT_TEST( SimulationNeutronProperties, setMaxNeutronEnergy )
{
  MonteCarlo::SimulationNeutronProperties properties;

  properties.setMaxNeutronEnergy( 15.0 );

  FRENSIE_CHECK_EQUAL( properties.getMaxNeutronEnergy(), 15.0 );
}

//---------------------------------------------------------------------------//
// Test that the number of hash grid bins can be set
FRENSIE_UNIT_TEST( SimulationNeutronProperties,
                   getNumberOfNeutronHashGridBins )
{
  MonteCarlo::SimulationNeutronProperties properties;

  properties.setNumberOfNeutronHashGridBins( 150u );

  FRENSIE_CHECK_EQUAL( properties.getNumberOfNeutronHashGridBins(), 150u );
}

//---------------------------------------------------------------------------//
// Test that the free gas thermal treatment temp threshold can be set
FRENSIE_UNIT_TEST( SimulationNeutronProperties, setFreeGasThreshold )
{
  MonteCarlo::SimulationNeutronProperties properties;

  properties.setFreeGasThreshold( 1000.0 );

  FRENSIE_CHECK_EQUAL( properties.getFreeGasThreshold(), 1000.0 );
}

//---------------------------------------------------------------------------//
// Test that the unresolved resonance probability table mode can be toggled
FRENSIE_UNIT_TEST( SimulationNeutronProperties,
                   setUnresolvedResonanceProbabilityTableModeOn_Off )
{
  MonteCarlo::SimulationNeutronProperties properties;

  properties.setUnresolvedResonanceProbabilityTableModeOff();

  FRENSIE_CHECK( !properties.isUnresolvedResonanceProbabilityTableModeOn() );

  properties.setUnresolvedResonanceProbabilityTableModeOn();

  FRENSIE_CHECK( properties.isUnresolvedResonanceProbabilityTableModeOn() );
}

//---------------------------------------------------------------------------//
// Check that the critical line energies can be set
FRENSIE_UNIT_TEST( SimulationNeutronProperties,
                   getNeutronRouletteThresholdWeight )
{
  MonteCarlo::SimulationNeutronProperties properties;

  double weight = 1e-14;

  properties.setNeutronRouletteThresholdWeight( weight );

  FRENSIE_CHECK_EQUAL( properties.getNeutronRouletteThresholdWeight(),
                       weight );
}

//---------------------------------------------------------------------------//
// Check that the critical line energies can be set
FRENSIE_UNIT_TEST( SimulationNeutronProperties,
                   getNeutronRouletteSurvivalWeight )
{
  MonteCarlo::SimulationNeutronProperties properties;

  double weight = 1e-12;

  properties.setNeutronRouletteSurvivalWeight( weight );

  FRENSIE_CHECK_EQUAL( properties.getNeutronRouletteSurvivalWeight(),
                       weight );
}

//---------------------------------------------------------------------------//
// Check that the properties can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( SimulationNeutronProperties,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_simulation_neutron_props" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    MonteCarlo::SimulationNeutronProperties default_properties;

    MonteCarlo::SimulationNeutronProperties custom_properties;
    custom_properties.setMinNeutronEnergy( 1e-8 );
    custom_properties.setMaxNeutronEnergy( 15.0 );
    custom_properties.setNumberOfNeutronHashGridBins( 150u );
    custom_properties.setFreeGasThreshold( 1000.0 );
    custom_properties.setUnresolvedResonanceProbabilityTableModeOff();
    custom_properties.setNeutronRouletteThresholdWeight( 1e-15 );
    custom_properties.setNeutronRouletteSurvivalWeight( 1e-13 );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( default_properties ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( custom_properties ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  MonteCarlo::SimulationNeutronProperties default_properties;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( default_properties ) );

  FRENSIE_CHECK_EQUAL( default_properties.getAbsoluteMinNeutronEnergy(), 1e-11 );
  FRENSIE_CHECK_EQUAL( default_properties.getMinNeutronEnergy(), 1e-11 );
  FRENSIE_CHECK_EQUAL( default_properties.getMaxNeutronEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( default_properties.getAbsoluteMaxNeutronEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( default_properties.getNumberOfNeutronHashGridBins(), 1000u );
  FRENSIE_CHECK_EQUAL( default_properties.getFreeGasThreshold(), 400.0 );
  FRENSIE_CHECK( default_properties.isUnresolvedResonanceProbabilityTableModeOn() );
  FRENSIE_CHECK_SMALL( default_properties.getNeutronRouletteThresholdWeight(), 1e-30 );
  FRENSIE_CHECK_SMALL( default_properties.getNeutronRouletteSurvivalWeight(), 1e-30  );

  MonteCarlo::SimulationNeutronProperties custom_properties;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( custom_properties ) );

  FRENSIE_CHECK_EQUAL( custom_properties.getAbsoluteMinNeutronEnergy(), 1e-11 );
  FRENSIE_CHECK_EQUAL( custom_properties.getMinNeutronEnergy(), 1e-8 );
  FRENSIE_CHECK_EQUAL( custom_properties.getMaxNeutronEnergy(), 15.0 );
  FRENSIE_CHECK_EQUAL( custom_properties.getAbsoluteMaxNeutronEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( custom_properties.getNumberOfNeutronHashGridBins(), 150u );
  FRENSIE_CHECK_EQUAL( custom_properties.getFreeGasThreshold(), 1000.0 );
  FRENSIE_CHECK( !custom_properties.isUnresolvedResonanceProbabilityTableModeOn() );
  FRENSIE_CHECK_EQUAL( custom_properties.getNeutronRouletteThresholdWeight(), 1e-15 );
  FRENSIE_CHECK_EQUAL( custom_properties.getNeutronRouletteSurvivalWeight(), 1e-13 );
}

//---------------------------------------------------------------------------//
// end tstSimulationNeutronProperties.cpp
//---------------------------------------------------------------------------//
