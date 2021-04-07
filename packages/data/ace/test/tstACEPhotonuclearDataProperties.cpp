//---------------------------------------------------------------------------//
//!
//! \file   tstACEPhotonuclearDataProperties.cpp
//! \author Alex Robinson
//! \brief  ACEPhotonuclearDataProperties class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <memory>
#include <iostream>

// FRENSIE Includes
#include "Data_ACEPhotonuclearDataProperties.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

using Utility::Units::amu;

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::unique_ptr<const Data::ACEPhotonuclearDataProperties> properties;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the zaid can be returned
FRENSIE_UNIT_TEST( ACEPhotonuclearDataProperties, zaid )
{
  FRENSIE_CHECK_EQUAL( properties->zaid().atom(), Data::H_ATOM );
  FRENSIE_CHECK_EQUAL( properties->zaid().atomicMassNumber(), 1 );
  FRENSIE_CHECK_EQUAL( properties->zaid().isomerNumber(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the atomic weight can be returned
FRENSIE_UNIT_TEST( ACEPhotonuclearDataProperties, atomicWeight )
{
  FRENSIE_CHECK_EQUAL( properties->atomicWeight(), 1.0*amu );
}

//---------------------------------------------------------------------------//
// Check that the file type can be returned
FRENSIE_UNIT_TEST( ACEPhotonuclearDataProperties, fileType )
{
  FRENSIE_CHECK_EQUAL( properties->fileType(),
                       Data::PhotonuclearDataProperties::ACE_FILE );
}

//---------------------------------------------------------------------------//
// Check that the file path can be returned
FRENSIE_UNIT_TEST( ACEPhotonuclearDataProperties, filePath )
{
  FRENSIE_CHECK_EQUAL( properties->filePath().string(),
                       "photonuclear_data/h_data.txt" );
}

//---------------------------------------------------------------------------//
// Check that the file start line can be returned
FRENSIE_UNIT_TEST( ACEPhotonuclearDataProperties, fileStartLine )
{
  FRENSIE_CHECK_EQUAL( properties->fileStartLine(), 10 );
}

//---------------------------------------------------------------------------//
// Check that the file version can be returned
FRENSIE_UNIT_TEST( ACEPhotonuclearDataProperties, fileVersion )
{
  FRENSIE_CHECK_EQUAL( properties->fileVersion(), 70 );
}

//---------------------------------------------------------------------------//
// Check that the table name can be returned
FRENSIE_UNIT_TEST( ACEPhotonuclearDataProperties, tableName )
{
  FRENSIE_CHECK_EQUAL( properties->tableName(), "1001.70u" );
}

//---------------------------------------------------------------------------//
// Check that the properties can be cloned
FRENSIE_UNIT_TEST( ACEPhotonuclearDataProperties, clone )
{
  std::unique_ptr<const Data::ACEPhotonuclearDataProperties>
    properties_clone( properties->clone() );

  FRENSIE_REQUIRE( properties_clone.get() != NULL );
  FRENSIE_CHECK( properties_clone.get() != properties.get() );
}

//---------------------------------------------------------------------------//
// Check that the properties can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( ACEPhotonuclearDataProperties,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_ace_photonuclear_data_properties" );
  std::ostringstream archive_ostream;

  // Create and archive some properties
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    Data::ACEPhotonuclearDataProperties local_properties( 4.0*amu,
                                                          "photonuclear_data/he_data.txt",
                                                          2,
                                                          "2004.24u" );

    std::shared_ptr<const Data::PhotonuclearDataProperties>
      shared_properties( properties->clone() );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( local_properties ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( shared_properties ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  Data::ACEPhotonuclearDataProperties
    local_properties( 0.1*amu, "dummy", 100000, "1000.00u" );

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( local_properties ) );
  FRENSIE_CHECK_EQUAL( local_properties.zaid(), Data::ZAID( 2004 ) );
  FRENSIE_CHECK_EQUAL( local_properties.atomicWeight(), 4.0*amu );
  FRENSIE_CHECK_EQUAL( local_properties.filePath().string(),
                       "photonuclear_data/he_data.txt" );
  FRENSIE_CHECK_EQUAL( local_properties.fileStartLine(), 2 );
  FRENSIE_CHECK_EQUAL( local_properties.fileVersion(), 24 );
  FRENSIE_CHECK_EQUAL( local_properties.tableName(), "2004.24u" );

  std::shared_ptr<const Data::PhotonuclearDataProperties>
    shared_properties;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( shared_properties ) );
  FRENSIE_CHECK_EQUAL( shared_properties->zaid(), Data::ZAID( 1001 ) );
  FRENSIE_CHECK_EQUAL( shared_properties->atomicWeight(), 1.0*amu );
  FRENSIE_CHECK_EQUAL( shared_properties->filePath().string(),
                       "photonuclear_data/h_data.txt" );
  FRENSIE_CHECK_EQUAL( shared_properties->fileStartLine(), 10 );
  FRENSIE_CHECK_EQUAL( shared_properties->fileVersion(), 70 );
  FRENSIE_CHECK_EQUAL( shared_properties->tableName(), "1001.70u" );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  properties.reset( new Data::ACEPhotonuclearDataProperties( 1.0*amu,
                                                             "photonuclear_data/h_data.txt",
                                                             10,
                                                             "1001.70u" ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstACEPhotonuclearDataProperties.cpp
//---------------------------------------------------------------------------//
