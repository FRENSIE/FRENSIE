//---------------------------------------------------------------------------//
//!
//! \file   tstNativeEPRAdjointElectroatomicDataProperties.cpp
//! \author Alex Robinson
//! \brief  NativeEPRAdjointElectroatomicDataProperties class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <memory>
#include <iostream>

// FRENSIE Includes
#include "Data_NativeEPRAdjointElectroatomicDataProperties.hpp"
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
std::unique_ptr<const Data::AdjointElectroatomicDataProperties> properties;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the atom can be returned
FRENSIE_UNIT_TEST( NativeEPRAdjointElectroatomicDataProperties, atom )
{
  FRENSIE_CHECK_EQUAL( properties->atom(), Data::H_ATOM );
}

//---------------------------------------------------------------------------//
// Check that the file type can be returned
FRENSIE_UNIT_TEST( NativeEPRAdjointElectroatomicDataProperties, fileType )
{
  FRENSIE_CHECK_EQUAL( properties->fileType(),
                       Data::AdjointElectroatomicDataProperties::Native_EPR_FILE );
}

//---------------------------------------------------------------------------//
// Check that the atomic weight can be returned
FRENSIE_UNIT_TEST( NativeEPRAdjointElectroatomicDataProperties, atomicWeight )
{
  FRENSIE_CHECK_EQUAL( properties->atomicWeight(), 1.0*amu );
}

//---------------------------------------------------------------------------//
// Check that the file path can be returned
FRENSIE_UNIT_TEST( NativeEPRAdjointElectroatomicDataProperties, fileStartLine )
{
  FRENSIE_CHECK_EQUAL( properties->fileStartLine(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the file version can be returned
FRENSIE_UNIT_TEST( NativeEPRAdjointElectroatomicDataProperties, fileVersion )
{
  FRENSIE_CHECK_EQUAL( properties->fileVersion(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the table name can be returned
FRENSIE_UNIT_TEST( NativeEPRAdjointElectroatomicDataProperties, tableName )
{
  FRENSIE_CHECK_EQUAL( properties->tableName(), "" );
}

//---------------------------------------------------------------------------//
// Check that the properties can be cloned
FRENSIE_UNIT_TEST( NativeEPRAdjointElectroatomicDataProperties, clone )
{
  std::unique_ptr<const Data::AdjointElectroatomicDataProperties>
    properties_clone( properties->clone() );

  FRENSIE_REQUIRE( properties_clone.get() != NULL );
  FRENSIE_CHECK( properties_clone.get() != properties.get() );
}

//---------------------------------------------------------------------------//
// Check that the properties can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( NativeEPRAdjointElectroatomicDataProperties,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_endl_electroatomic_data_properties" );
  std::ostringstream archive_ostream;

  // Create and archive some properties
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    Data::NativeEPRAdjointElectroatomicDataProperties local_properties(
                                      4.0*amu,
                                      "adjoint_electroatomic_data/he_data.xml",
                                      1,
                                      Data::He_ATOM );

    std::shared_ptr<const Data::AdjointElectroatomicDataProperties>
      shared_properties( properties->clone() );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( local_properties ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( shared_properties ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  Data::NativeEPRAdjointElectroatomicDataProperties
    local_properties( 10.0*amu, "dummy", 10, Data::Pb_ATOM );

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( local_properties ) );
  FRENSIE_CHECK_EQUAL( local_properties.atom(), Data::He_ATOM );
  FRENSIE_CHECK_EQUAL( local_properties.atomicNumber(), 2 );
  FRENSIE_CHECK_EQUAL( local_properties.atomicWeight(), 4.0*amu );
  FRENSIE_CHECK_EQUAL( local_properties.filePath().string(),
                       "adjoint_electroatomic_data/he_data.xml" );
  FRENSIE_CHECK_EQUAL( local_properties.fileStartLine(), 0 );
  FRENSIE_CHECK_EQUAL( local_properties.fileVersion(), 1 );
  FRENSIE_CHECK_EQUAL( local_properties.tableName(), "" );

  std::shared_ptr<const Data::AdjointElectroatomicDataProperties>
    shared_properties;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( shared_properties ) );
  FRENSIE_CHECK_EQUAL( shared_properties->atom(), Data::H_ATOM );
  FRENSIE_CHECK_EQUAL( shared_properties->atomicNumber(), 1 );
  FRENSIE_CHECK_EQUAL( shared_properties->atomicWeight(), 1.0*amu );
  FRENSIE_CHECK_EQUAL( shared_properties->filePath().string(),
                       "adjoint_electroatomic_data/h_data.xml" );
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
  properties.reset( new Data::NativeEPRAdjointElectroatomicDataProperties(
                                       1.0*amu,
                                       "adjoint_electroatomic_data/h_data.xml",
                                       0,
                                       Data::H_ATOM ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstNativeEPRAdjointElectroatomicDataProperties.cpp
//---------------------------------------------------------------------------//
