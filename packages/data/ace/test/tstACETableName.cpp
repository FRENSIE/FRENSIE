//---------------------------------------------------------------------------//
//!
//! \file   tstACETableName.cpp
//! \author Alex Robinson
//! \brief  ACE table name unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// FRENSIE Includes
#include "Data_ACETableName.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an ACETableName can be constructed from a raw table name
FRENSIE_UNIT_TEST( ACETableName, raw_table_name_constructor )
{
  Data::ACETableName ace_table_name( "1001.70c" );

  FRENSIE_CHECK_EQUAL( ace_table_name.zaid(), Data::ZAID( 1001 ) );
  FRENSIE_CHECK_EQUAL( ace_table_name.version(), 70 );
  FRENSIE_CHECK_EQUAL( ace_table_name.typeKey(), 'c' );
  FRENSIE_CHECK_EQUAL( ace_table_name.toRaw(), "1001.70c" );
}

//---------------------------------------------------------------------------//
// Check that an ACETableName can be constructed from components
FRENSIE_UNIT_TEST( ACETableName, component_constructor )
{
  Data::ACETableName ace_table_name( 1001, 70, 'c' );

  FRENSIE_CHECK_EQUAL( ace_table_name.zaid(), Data::ZAID( 1001 ) );
  FRENSIE_CHECK_EQUAL( ace_table_name.version(), 70 );
  FRENSIE_CHECK_EQUAL( ace_table_name.typeKey(), 'c' );
  FRENSIE_CHECK_EQUAL( ace_table_name.toRaw(), "1001.70c" );
}

//---------------------------------------------------------------------------//
// Check that an ACETableName can be copied
FRENSIE_UNIT_TEST( ACETableName, copy_constructor )
{
  Data::ACETableName ace_table_name( 92000, 12, 'p' );
  
  Data::ACETableName ace_table_name_copy( ace_table_name );

  FRENSIE_CHECK_EQUAL( ace_table_name_copy.zaid(), Data::ZAID( 92000 ) );
  FRENSIE_CHECK_EQUAL( ace_table_name_copy.version(), 12 );
  FRENSIE_CHECK_EQUAL( ace_table_name_copy.typeKey(), 'p' );
  FRENSIE_CHECK_EQUAL( ace_table_name_copy.toRaw(), "92000.12p" );
  FRENSIE_CHECK_EQUAL( (std::string)ace_table_name_copy, "92000.12p" );
  FRENSIE_CHECK_EQUAL( ace_table_name, ace_table_name_copy );
}

//---------------------------------------------------------------------------//
// Check that an ACETableName can be assigned
FRENSIE_UNIT_TEST( ACETableName, assignment_operator )
{
  Data::ACETableName ace_table_name( "92000.12p" );
  
  Data::ACETableName ace_table_name_copy = ace_table_name;

  FRENSIE_CHECK_EQUAL( ace_table_name_copy.zaid(), Data::ZAID( 92000 ) );
  FRENSIE_CHECK_EQUAL( ace_table_name_copy.version(), 12 );
  FRENSIE_CHECK_EQUAL( ace_table_name_copy.typeKey(), 'p' );
  FRENSIE_CHECK_EQUAL( ace_table_name_copy.toRaw(), "92000.12p" );
  FRENSIE_CHECK_EQUAL( (std::string)ace_table_name_copy, "92000.12p" );
  FRENSIE_CHECK_EQUAL( ace_table_name, ace_table_name_copy );
}

//---------------------------------------------------------------------------//
// Check that an ACETableName can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( ACETableName, archive, TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_ace_table_name" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    Data::ACETableName h1_ace_table_name( "1001.70c" );
    Data::ACETableName u_ace_table_name( 92000, 12, 'p' );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( h1_ace_table_name ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( u_ace_table_name ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  Data::ACETableName h1_ace_table_name;
  Data::ACETableName u_ace_table_name;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( h1_ace_table_name ) );
  FRENSIE_CHECK_EQUAL( h1_ace_table_name.zaid(), Data::ZAID( 1001 ) );
  FRENSIE_CHECK_EQUAL( h1_ace_table_name.version(), 70 );
  FRENSIE_CHECK_EQUAL( h1_ace_table_name.typeKey(), 'c' );
  FRENSIE_CHECK_EQUAL( h1_ace_table_name.toRaw(), "1001.70c" );
  
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( u_ace_table_name ) );
  FRENSIE_CHECK_EQUAL( u_ace_table_name.zaid(), Data::ZAID( 92000 ) );
  FRENSIE_CHECK_EQUAL( u_ace_table_name.version(), 12 );
  FRENSIE_CHECK_EQUAL( u_ace_table_name.typeKey(), 'p' );
  FRENSIE_CHECK_EQUAL( u_ace_table_name.toRaw(), "92000.12p" );
}

//---------------------------------------------------------------------------//
// end tstACETableName.cpp
//---------------------------------------------------------------------------//
