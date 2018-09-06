//---------------------------------------------------------------------------//
//!
//! \file   tstACENuclearDataProperties.cpp
//! \author Alex Robinson
//! \brief  ACENuclearDataProperties class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <memory>
#include <iostream>

// FRENSIE Includes
#include "Data_ACENuclearDataProperties.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::unique_ptr<const Data::ACENuclearDataProperties> properties;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the zaid can be returned
FRENSIE_UNIT_TEST( ACENuclearDataProperties, zaid )
{
  FRENSIE_CHECK_EQUAL( properties->zaid().atom(), Data::H_ATOM );
  FRENSIE_CHECK_EQUAL( properties->zaid().atomicMassNumber(), 1 );
  FRENSIE_CHECK_EQUAL( properties->zaid().isomerNumber(), 0 )
}

//---------------------------------------------------------------------------//
// Check that the atomic weight can be returned
FRENSIE_UNIT_TEST( ACENuclearDataProperties, atomicWeightRatio )
{
  FRENSIE_CHECK_EQUAL( properties->atomicWeightRatio(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the evaluation temperature can be returned
FRENSIE_UNIT_TEST( ACENuclearDataProperties, evaluationTemperatureInMeV )
{
  FRENSIE_CHECK_EQUAL( properties->evaluationTemperatureInMeV(),
                       2.5301e-8*Utility::Units::MeV );
}

//---------------------------------------------------------------------------//
// Check that the evaluation temperature can be returned
FRENSIE_UNIT_TEST( ACENuclearDataProperties, evaluationTemperature )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( properties->evaluationTemperature(),
                                   293.6059397103837227*boost::units::si::kelvin,
                                   1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the data file type can be returned
FRENSIE_UNIT_TEST( ACENuclearDataProperties, fileType )
{
  FRENSIE_CHECK_EQUAL( properties->fileType(),
                       Data::NuclearDataProperties::ACE_FILE );
}

//---------------------------------------------------------------------------//
// Check that the data file path can be returned
FRENSIE_UNIT_TEST( ACENuclearDataProperties, filePath )
{
  FRENSIE_CHECK_EQUAL( properties->filePath().string(),
                       "neutron_data/h_data.txt" );
}

//---------------------------------------------------------------------------//
// Check that the data file start line can be returned
FRENSIE_UNIT_TEST( ACENuclearDataProperties, fileStartLine )
{
  FRENSIE_CHECK_EQUAL( properties->fileStartLine(), 10 );
}

//---------------------------------------------------------------------------//
// Check that the data file major version can be returned
FRENSIE_UNIT_TEST( ACENuclearDataProperties, fileMajorVersion )
{
  FRENSIE_CHECK_EQUAL( properties->fileMajorVersion(), 7 );
}

//---------------------------------------------------------------------------//
// Check that the data file version can be returned
FRENSIE_UNIT_TEST( ACENuclearDataProperties, fileVersion )
{
  FRENSIE_CHECK_EQUAL( properties->fileVersion(), 70 );
}

//---------------------------------------------------------------------------//
// Check that the data table name can be returned
FRENSIE_UNIT_TEST( ACENuclearDataProperties, tableName )
{
  FRENSIE_CHECK_EQUAL( properties->tableName(), "1001.70c" );
}

//---------------------------------------------------------------------------//
// Check that the properties can be cloned
FRENSIE_UNIT_TEST( ACENuclearDataProperties, clone )
{
  std::unique_ptr<const Data::ACENuclearDataProperties> properties_clone(
                                                         properties->clone() );

  FRENSIE_REQUIRE( properties_clone.get() != NULL );
  FRENSIE_CHECK( properties_clone.get() != properties.get() );
}

//---------------------------------------------------------------------------//
// Check that the properties can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( ACENuclearDataProperties,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_ace_nuclear_data_properties" );
  std::ostringstream archive_ostream;

  // Create and archive some properties
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    Data::ACENuclearDataProperties local_properties( 16.0,
                                                     2.5301e-8*Utility::Units::MeV,
                                                     "neutron_data/o_data.txt",
                                                     0,
                                                     "8016.81c" );

    std::shared_ptr<const Data::NuclearDataProperties>
      shared_properties( properties->clone() );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( local_properties ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( shared_properties ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  Data::ACENuclearDataProperties
    local_properties( 0.1, 0.1*Utility::Units::MeV, "dummy", 100000, "1000.00c" );

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( local_properties ) );
  FRENSIE_CHECK_EQUAL( local_properties.zaid(), Data::ZAID( 8016 ) );
  FRENSIE_CHECK_EQUAL( local_properties.atomicWeightRatio(), 16.0 );
  FRENSIE_CHECK_EQUAL( local_properties.evaluationTemperatureInMeV(),
                       2.5301e-8*Utility::Units::MeV );
  FRENSIE_CHECK_EQUAL( local_properties.filePath().string(),
                       "neutron_data/o_data.txt" );
  FRENSIE_CHECK_EQUAL( local_properties.fileStartLine(), 0 );
  FRENSIE_CHECK_EQUAL( local_properties.fileVersion(), 81 );
  FRENSIE_CHECK_EQUAL( local_properties.tableName(), "8016.81c" );

  std::shared_ptr<const Data::NuclearDataProperties>
    shared_properties;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( shared_properties ) );
  FRENSIE_CHECK_EQUAL( shared_properties->zaid(), Data::ZAID( 1001 ) );
  FRENSIE_CHECK_EQUAL( shared_properties->atomicWeightRatio(), 1.0 );
  FRENSIE_CHECK_EQUAL( shared_properties->evaluationTemperatureInMeV(),
                       2.5301e-8*Utility::Units::MeV );
  FRENSIE_CHECK_EQUAL( shared_properties->filePath().string(),
                       "neutron_data/h_data.txt" );
  FRENSIE_CHECK_EQUAL( shared_properties->fileStartLine(), 10 );
  FRENSIE_CHECK_EQUAL( shared_properties->fileVersion(), 70 );
  FRENSIE_CHECK_EQUAL( shared_properties->tableName(), "1001.70c" );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  properties.reset( new Data::ACENuclearDataProperties( 1.0,
                                                        2.5301e-8*Utility::Units::MeV,
                                                        "neutron_data/h_data.txt",
                                                        10,
                                                        "1001.70c" ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstACENuclearDataProperties.cpp
//---------------------------------------------------------------------------//
