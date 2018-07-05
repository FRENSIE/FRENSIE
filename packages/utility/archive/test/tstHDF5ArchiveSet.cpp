//---------------------------------------------------------------------------//
//!
//! \file   tstHDF5ArchiveSet.cpp
//! \author Alex Robinson
//! \brief  HDF5 archive set unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// FRENSIE Includes
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_Set.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Template Types
//---------------------------------------------------------------------------//
typedef std::tuple<bool,
                   char, unsigned char, signed char,
                   short, unsigned short,
                   int, unsigned int,
                   long, unsigned long,
                   long long, unsigned long long,
                   float, double, long double> BasicTestTypes;

//---------------------------------------------------------------------------//
// Testing functions
//---------------------------------------------------------------------------//
template<typename T>
inline T zero( T )
{ return T(0); }

template<typename T>
inline T one( T )
{ return T(1); }

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that sets of basic types can be archived
FRENSIE_UNIT_TEST_TEMPLATE( HDF5Archive,
                            archive_set_basic_types,
                            BasicTestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  std::string archive_name( "test_set_basic_types.h5a" );

  std::set<T> set;
  set.insert( zero(T()) );
  set.insert( one(T()) );

  {
    Utility::HDF5OArchive archive( archive_name, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE );

    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "set", set ) );
  }

  {
    Utility::HDF5IArchive archive( archive_name );

    std::set<T> extracted_set;

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "set", extracted_set ) );
    FRENSIE_CHECK_EQUAL( set, extracted_set );
  }
}

//---------------------------------------------------------------------------//
// Check that a set of strings can be archived
FRENSIE_UNIT_TEST( HDF5Archive, archive_set_string )
{
  std::string archive_name( "test_set_string.h5a" );

  std::set<std::string> set;
  set.insert( std::string("Test message 0") );
  set.insert( std::string("Test message 1") );

  {
    Utility::HDF5OArchive archive( archive_name, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE );

    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "set", set ) );
  }

  {
    Utility::HDF5IArchive archive( archive_name );

    std::set<std::string> extracted_set;
    
    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "set", extracted_set ) );
    FRENSIE_CHECK_EQUAL( extracted_set, set );
  }
}

//---------------------------------------------------------------------------//
// end tstHDF5ArchiveSet.cpp
//---------------------------------------------------------------------------//
