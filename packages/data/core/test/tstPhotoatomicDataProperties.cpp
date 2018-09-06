//---------------------------------------------------------------------------//
//!
//! \file   tstPhotoatomicDataProperties.cpp
//! \author Alex Robinson
//! \brief  Photoatomic data properties class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// FRENSIE Includes
#include "Data_PhotoatomicDataProperties.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a PhotoatomicDataProperties::FileType can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( PhotoatomicDataProperties,
                                   FileType_archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_photoatomic_file_type" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    Data::PhotoatomicDataProperties::FileType type_1 =
      Data::PhotoatomicDataProperties::ACE_FILE;

    Data::PhotoatomicDataProperties::FileType type_2 =
      Data::PhotoatomicDataProperties::ACE_EPR_FILE;

    Data::PhotoatomicDataProperties::FileType type_3 =
      Data::PhotoatomicDataProperties::Native_EPR_FILE;

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_1 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_2 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_3 ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  Data::PhotoatomicDataProperties::FileType type_1;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_1 ) );
  FRENSIE_CHECK_EQUAL( type_1, Data::PhotoatomicDataProperties::ACE_FILE );

  Data::PhotoatomicDataProperties::FileType type_2;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_2 ) );
  FRENSIE_CHECK_EQUAL( type_2, Data::PhotoatomicDataProperties::ACE_EPR_FILE );

  Data::PhotoatomicDataProperties::FileType type_3;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_3 ) );
  FRENSIE_CHECK_EQUAL( type_3, Data::PhotoatomicDataProperties::Native_EPR_FILE );
}

//---------------------------------------------------------------------------//
// end tstPhotoatomicDataProperties.cpp
//---------------------------------------------------------------------------//
