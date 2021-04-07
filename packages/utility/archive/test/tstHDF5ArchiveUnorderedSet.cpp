//---------------------------------------------------------------------------//
//!
//! \file   tstHDF5ArchiveUnorderedSet.cpp
//! \author Alex Robinson
//! \brief  HDF5 archive unordered set unit tests
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
// Check that unordered_sets of basic types can be archived
FRENSIE_UNIT_TEST_TEMPLATE( HDF5Archive,
                            archive_unordered_set_basic_types,
                            BasicTestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  std::string archive_name( "test_unordered_set_basic_types.h5a" );

  std::unordered_set<T> unordered_set;
  unordered_set.insert( zero(T()) );
  unordered_set.insert( one(T()) );

  {
    Utility::HDF5OArchive archive( archive_name, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE );

    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "unordered_set", unordered_set ) );
  }

  {
    Utility::HDF5IArchive archive( archive_name );

    std::unordered_set<T> extracted_unordered_set;

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "unordered_set", extracted_unordered_set ) );
    FRENSIE_CHECK_EQUAL( unordered_set, extracted_unordered_set );
  }
}

//---------------------------------------------------------------------------//
// Check that a unordered_set of strings can be archived
FRENSIE_UNIT_TEST( HDF5Archive, archive_unordered_set_string )
{
  std::string archive_name( "test_unordered_set_string.h5a" );

  std::unordered_set<std::string> unordered_set;
  unordered_set.insert( std::string("Test message 0") );
  unordered_set.insert( std::string("Test message 1") );

  {
    Utility::HDF5OArchive archive( archive_name, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE );

    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "unordered_set", unordered_set ) );
  }

  {
    Utility::HDF5IArchive archive( archive_name );

    std::unordered_set<std::string> extracted_unordered_set;
    
    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "unordered_set", extracted_unordered_set ) );
    FRENSIE_CHECK_EQUAL( extracted_unordered_set, unordered_set );
  }
}

//---------------------------------------------------------------------------//
// end tstHDF5ArchiveUnorderedSet.cpp
//---------------------------------------------------------------------------//
