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
FRENSIE_UNIT_TEST( SimulationNeutronProperties, defaults )
{
  MonteCarlo::SimulationNeutronProperties properties;
  
  FRENSIE_CHECK_EQUAL( properties.getAbsoluteMinNeutronEnergy(), 1e-11 );
  FRENSIE_CHECK_EQUAL( properties.getMinNeutronEnergy(), 1e-11 );
  FRENSIE_CHECK_EQUAL( properties.getMaxNeutronEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( properties.getAbsoluteMaxNeutronEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( properties.getFreeGasThreshold(), 400.0 );
  FRENSIE_CHECK( properties.isUnresolvedResonanceProbabilityTableModeOn() );
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
    custom_properties.setFreeGasThreshold( 1000.0 );
    custom_properties.setUnresolvedResonanceProbabilityTableModeOff();

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
  FRENSIE_CHECK_EQUAL( default_properties.getFreeGasThreshold(), 400.0 );
  FRENSIE_CHECK( default_properties.isUnresolvedResonanceProbabilityTableModeOn() );

  MonteCarlo::SimulationNeutronProperties custom_properties;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( custom_properties ) );

  FRENSIE_CHECK_EQUAL( custom_properties.getAbsoluteMinNeutronEnergy(), 1e-11 );
  FRENSIE_CHECK_EQUAL( custom_properties.getMinNeutronEnergy(), 1e-8 );
  FRENSIE_CHECK_EQUAL( custom_properties.getMaxNeutronEnergy(), 15.0 );
  FRENSIE_CHECK_EQUAL( custom_properties.getAbsoluteMaxNeutronEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( custom_properties.getFreeGasThreshold(), 1000.0 );
  FRENSIE_CHECK( !custom_properties.isUnresolvedResonanceProbabilityTableModeOn() );
}

//---------------------------------------------------------------------------//
// end tstSimulationNeutronProperties.cpp
//---------------------------------------------------------------------------//
