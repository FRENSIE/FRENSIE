//---------------------------------------------------------------------------//
//!
//! \file   tstACEThermalNuclearDataProperties.cpp
//! \author Alex Robinson
//! \brief  ACEThermalNuclearDataProperties class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <memory>
#include <iostream>

// FRENSIE Includes
#include "Data_ACEThermalNuclearDataProperties.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

using Utility::Units::MeV;

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::unique_ptr<const Data::ACEThermalNuclearDataProperties> properties;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the name can be returned
FRENSIE_UNIT_TEST( ACEThermalNuclearDataProperties, name )
{
  FRENSIE_CHECK_EQUAL( properties->name(), "benz", SHOW_LHS );
}

//---------------------------------------------------------------------------//
// Check that the zaids can be returned
FRENSIE_UNIT_TEST( ACEThermalNuclearDataProperties, zaids )
{
  std::set<Data::ZAID> zaids = properties->zaids();

  FRENSIE_CHECK_EQUAL( zaids, std::set<Data::ZAID>({Data::ZAID(1001), Data::ZAID(6000), Data::ZAID(6012)}) );
}

//---------------------------------------------------------------------------//
// Check that the properties have data for the ZAID of interest
FRENSIE_UNIT_TEST( ACEThermalNuclearDataProperties, hasDataForZAID )
{
  FRENSIE_CHECK( properties->hasDataForZAID( Data::ZAID(1001) ) );
  FRENSIE_CHECK( !properties->hasDataForZAID( Data::ZAID(1002) ) );
  FRENSIE_CHECK( properties->hasDataForZAID( Data::ZAID(6000) ) );
  FRENSIE_CHECK( properties->hasDataForZAID( Data::ZAID(6012) ) );
  FRENSIE_CHECK( !properties->hasDataForZAID( Data::ZAID(6014) ) );
}

//---------------------------------------------------------------------------//
// Check that the evaluation temperature can be returned
FRENSIE_UNIT_TEST( ACEThermalNuclearDataProperties, evaluationTemperatureInMeV )
{
  FRENSIE_CHECK_EQUAL( properties->evaluationTemperatureInMeV(),
                       2.5301e-8*MeV );
}

//---------------------------------------------------------------------------//
// Check that the evaluation temperature can be returned
FRENSIE_UNIT_TEST( ACEThermalNuclearDataProperties, evaluationTemperature )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( properties->evaluationTemperature(),
                                   293.6059397103837227*boost::units::si::kelvin,
                                   1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the file type can be returned
FRENSIE_UNIT_TEST( ACEThermalNuclearDataProperties, fileType )
{
  FRENSIE_CHECK_EQUAL( properties->fileType(),
                       Data::ThermalNuclearDataProperties::STANDARD_ACE_FILE );

  std::unique_ptr<const Data::ThermalNuclearDataProperties> local_properties(
                 new Data::ACEThermalNuclearDataProperties( {Data::ZAID(1001)},
                                                            2.5301e-8*MeV,
                                                            "dummy.txt",
                                                            0,
                                                            "h2o.00t" ) );

  FRENSIE_CHECK_EQUAL( local_properties->fileType(),
                       Data::ThermalNuclearDataProperties::STANDARD_ACE_FILE );

  local_properties.reset(
                 new Data::ACEThermalNuclearDataProperties( {Data::ZAID(1001)},
                                                            2.5301e-8*MeV,
                                                            "dummy.txt",
                                                            0,
                                                            "h2o.19t" ) );

  FRENSIE_CHECK_EQUAL( local_properties->fileType(),
                       Data::ThermalNuclearDataProperties::STANDARD_ACE_FILE );

  local_properties.reset(
                 new Data::ACEThermalNuclearDataProperties( {Data::ZAID(1001)},
                                                            2.5301e-8*MeV,
                                                            "dummy.txt",
                                                            0,
                                                            "h2o.60t" ) );

  
  FRENSIE_CHECK_EQUAL( local_properties->fileType(),
                       Data::ThermalNuclearDataProperties::STANDARD_ACE_FILE );

  local_properties.reset(
                 new Data::ACEThermalNuclearDataProperties( {Data::ZAID(1001)},
                                                            2.5301e-8*MeV,
                                                            "dummy.txt",
                                                            0,
                                                            "h2o.69t" ) );

  
  FRENSIE_CHECK_EQUAL( local_properties->fileType(),
                       Data::ThermalNuclearDataProperties::STANDARD_ACE_FILE );

  local_properties.reset(
                 new Data::ACEThermalNuclearDataProperties( {Data::ZAID(1001)},
                                                            2.5301e-8*MeV,
                                                            "dummy.txt",
                                                            0,
                                                            "h2o.20t" ) );

  
  FRENSIE_CHECK_EQUAL( local_properties->fileType(),
                       Data::ThermalNuclearDataProperties::MCNP6_ACE_FILE );

  local_properties.reset(
                 new Data::ACEThermalNuclearDataProperties( {Data::ZAID(1001)},
                                                            2.5301e-8*MeV,
                                                            "dummy.txt",
                                                            0,
                                                            "h2o.29t" ) );

  
  FRENSIE_CHECK_EQUAL( local_properties->fileType(),
                       Data::ThermalNuclearDataProperties::MCNP6_ACE_FILE );
}

//---------------------------------------------------------------------------//
// Check that the file path can be returned
FRENSIE_UNIT_TEST( ACEThermalNuclearDataProperties, filePath )
{
  FRENSIE_CHECK_EQUAL( properties->filePath().string(),
                       "sab_data/benz.txt" );
}

//---------------------------------------------------------------------------//
// Check that the file start line can be returned
FRENSIE_UNIT_TEST( ACEThermalNuclearDataProperties, fileStartLine )
{
  FRENSIE_CHECK_EQUAL( properties->fileStartLine(), 10 );
}

//---------------------------------------------------------------------------//
// Check that the file major version can be returned
FRENSIE_UNIT_TEST( ACEThermalNuclearDataProperties, fileMajorVersion )
{
  FRENSIE_CHECK_EQUAL( properties->fileMajorVersion(), 1 );
}

//---------------------------------------------------------------------------//
// Check that the file version can be returned
FRENSIE_UNIT_TEST( ACEThermalNuclearDataProperties, fileVersion )
{
  FRENSIE_CHECK_EQUAL( properties->fileVersion(), 12 );
}

//---------------------------------------------------------------------------//
// Check that the table name can be returned
FRENSIE_UNIT_TEST( ACEThermalNuclearDataProperties, tableName )
{
  FRENSIE_CHECK_EQUAL( properties->tableName(), "benz.12t", SHOW_LHS );
}

//---------------------------------------------------------------------------//
// Check that the properties can be cloned
FRENSIE_UNIT_TEST( ACEThermalNuclearDataProperties, clone )
{
  std::unique_ptr<const Data::ACEThermalNuclearDataProperties>
    properties_clone( properties->clone() );

  FRENSIE_REQUIRE( properties_clone.get() != NULL );
  FRENSIE_CHECK( properties_clone.get() != properties.get() );
}

//---------------------------------------------------------------------------//
// Check that the properties can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( ACEThermalNuclearDataProperties,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_ace_thermal_nuclear_data_properties" );
  std::ostringstream archive_ostream;

  // Create and archive some properties
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    Data::ACEThermalNuclearDataProperties local_properties( {Data::ZAID(1001)},
                                                            2.5301e-8*MeV,
                                                            "h2o.txt",
                                                            5,
                                                            "h2o.22t" );

    std::shared_ptr<const Data::ThermalNuclearDataProperties>
      shared_properties( properties->clone() );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( local_properties ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( shared_properties ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  Data::ACEThermalNuclearDataProperties local_properties( {Data::ZAID(6000)},
                                                          0.1*MeV,
                                                          "dummy.txt",
                                                          0,
                                                          "dummy.00t" );

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( local_properties ) );
  FRENSIE_CHECK_EQUAL( local_properties.name(), "h2o" );
  FRENSIE_CHECK_EQUAL( local_properties.zaids(), std::set<Data::ZAID>( {Data::ZAID(1001)} ) );
  FRENSIE_CHECK_EQUAL( local_properties.evaluationTemperatureInMeV(),
                       2.5301e-8*MeV );
  FRENSIE_CHECK_EQUAL( local_properties.filePath().string(), "h2o.txt" );
  FRENSIE_CHECK_EQUAL( local_properties.fileStartLine(), 5 );
  FRENSIE_CHECK_EQUAL( local_properties.fileVersion(), 22 );
  FRENSIE_CHECK_EQUAL( local_properties.tableName(), "h2o.22t" );

  std::shared_ptr<const Data::ThermalNuclearDataProperties> shared_properties;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( shared_properties ) );
  FRENSIE_CHECK_EQUAL( shared_properties->name(), "benz" );
  FRENSIE_CHECK_EQUAL( shared_properties->zaids(), std::set<Data::ZAID>( {Data::ZAID(1001), Data::ZAID(6000), Data::ZAID(6012)} ) );
  FRENSIE_CHECK_EQUAL( shared_properties->evaluationTemperatureInMeV(),
                       2.5301e-8*MeV );
  FRENSIE_CHECK_EQUAL( shared_properties->filePath().string(), "sab_data/benz.txt" );
  FRENSIE_CHECK_EQUAL( shared_properties->fileStartLine(), 10 );
  FRENSIE_CHECK_EQUAL( shared_properties->fileVersion(), 12 );
  FRENSIE_CHECK_EQUAL( shared_properties->tableName(), "benz.12t" );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  properties.reset( new Data::ACEThermalNuclearDataProperties(
                        {Data::ZAID(1001), Data::ZAID(6000), Data::ZAID(6012)},
                        2.5301e-8*MeV,
                        "sab_data/benz.txt",
                        10,
                        "benz.12t" ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstACEThermalNuclearDataProperties.cpp
//---------------------------------------------------------------------------//
