//---------------------------------------------------------------------------//
//!
//! \file   tstNativeEPRAdjointPhotoatomicDataProperties.cpp
//! \author Alex Robinson
//! \brief  NativeEPRAdjointPhotoatomicDataProperties class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <memory>
#include <iostream>

// FRENSIE Includes
#include "Data_NativeEPRAdjointPhotoatomicDataProperties.hpp"
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
// Testing Variables
//---------------------------------------------------------------------------//
std::unique_ptr<const Data::AdjointPhotoatomicDataProperties> properties;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the atom can be returned
FRENSIE_UNIT_TEST( NativeEPRAdjointPhotoatomicDataProperties, atom )
{
  FRENSIE_CHECK_EQUAL( properties->atom(), Data::H_ATOM );
}

//---------------------------------------------------------------------------//
// Check that the file type can be returned
FRENSIE_UNIT_TEST( NativeEPRAdjointPhotoatomicDataProperties, fileType )
{
  FRENSIE_CHECK_EQUAL( properties->fileType(),
                       Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE );
}

//---------------------------------------------------------------------------//
// Check that the file path can be returned
FRENSIE_UNIT_TEST( NativeEPRAdjointPhotoatomicDataProperties, fileStartLine )
{
  FRENSIE_CHECK_EQUAL( properties->fileStartLine(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the file version can be returned
FRENSIE_UNIT_TEST( NativeEPRAdjointPhotoatomicDataProperties, fileVersion )
{
  FRENSIE_CHECK_EQUAL( properties->fileVersion(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the table name can be returned
FRENSIE_UNIT_TEST( NativeEPRAdjointPhotoatomicDataProperties, tableName )
{
  FRENSIE_CHECK_EQUAL( properties->tableName(), "" );
}

//---------------------------------------------------------------------------//
// Check that the properties can be cloned
FRENSIE_UNIT_TEST( NativeEPRAdjointPhotoatomicDataProperties, clone )
{
  std::unique_ptr<const Data::AdjointPhotoatomicDataProperties>
    properties_clone( properties->clone() );

  FRENSIE_REQUIRE( properties_clone.get() != NULL );
  FRENSIE_CHECK( properties_clone.get() != properties.get() );
}

//---------------------------------------------------------------------------//
// Check that the properties can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( NativeEPRAdjointPhotoatomicDataProperties,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_endl_photoatomic_data_properties" );
  std::ostringstream archive_ostream;

  // Create and archive some properties
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    Data::NativeEPRAdjointPhotoatomicDataProperties local_properties( "adjoint_photoatomic_data/he_data.xml",
                                                          1,
                                                          Data::He_ATOM );

    std::shared_ptr<const Data::AdjointPhotoatomicDataProperties>
      shared_properties( properties->clone() );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( local_properties ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( shared_properties ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  Data::NativeEPRAdjointPhotoatomicDataProperties
    local_properties( "dummy", 10, Data::Pb_ATOM );

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( local_properties ) );
  FRENSIE_CHECK_EQUAL( local_properties.atom(), Data::He_ATOM );
  FRENSIE_CHECK_EQUAL( local_properties.atomicNumber(), 2 );
  FRENSIE_CHECK_EQUAL( local_properties.filePath().string(),
                       "adjoint_photoatomic_data/he_data.xml" );
  FRENSIE_CHECK_EQUAL( local_properties.fileStartLine(), 0 );
  FRENSIE_CHECK_EQUAL( local_properties.fileVersion(), 1 );
  FRENSIE_CHECK_EQUAL( local_properties.tableName(), "" );

  std::shared_ptr<const Data::AdjointPhotoatomicDataProperties>
    shared_properties;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( shared_properties ) );
  FRENSIE_CHECK_EQUAL( shared_properties->atom(), Data::H_ATOM );
  FRENSIE_CHECK_EQUAL( shared_properties->atomicNumber(), 1 );
  FRENSIE_CHECK_EQUAL( shared_properties->filePath().string(),
                       "adjoint_photoatomic_data/h_data.xml" );
  FRENSIE_CHECK_EQUAL( shared_properties->fileStartLine(), 0 );
  FRENSIE_CHECK_EQUAL( shared_properties->fileVersion(), 0 );
  FRENSIE_CHECK_EQUAL( shared_properties->tableName(), "" );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  properties.reset( new Data::NativeEPRAdjointPhotoatomicDataProperties(
                                         "adjoint_photoatomic_data/h_data.xml",
                                         0,
                                         Data::H_ATOM ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstNativeEPRAdjointPhotoatomicDataProperties.cpp
//---------------------------------------------------------------------------//
