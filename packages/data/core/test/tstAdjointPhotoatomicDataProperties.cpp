//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointPhotoatomicDataProperties.cpp
//! \author Alex Robinson
//! \brief  Adjoint photoatomic data properties class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// FRENSIE Includes
#include "Data_AdjointPhotoatomicDataProperties.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an AdjointPhotoatomicDataProperties::FileType can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( AdjointPhotoatomicDataProperties,
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

    Data::AdjointPhotoatomicDataProperties::FileType type_1 =
      Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE;

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_1 ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  Data::AdjointPhotoatomicDataProperties::FileType type_1;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_1 ) );
  FRENSIE_CHECK_EQUAL( type_1, Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE );
}

//---------------------------------------------------------------------------//
// end tstAdjointPhotoatomicDataProperties.cpp
//---------------------------------------------------------------------------//
