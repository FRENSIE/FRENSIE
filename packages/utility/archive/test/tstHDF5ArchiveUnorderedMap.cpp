//---------------------------------------------------------------------------//
//!
//! \file   tstHDF5ArchiveUnorderedMap.cpp
//! \author Alex Robinson
//! \brief  HDF5 archive unordered map unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// FRENSIE Includes
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_Map.hpp"
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
// Tests.
//---------------------------------------------------------------------------//
// Check that unordered_maps of basic types can be archived
FRENSIE_UNIT_TEST_TEMPLATE( HDF5Archive,
                            archive_unordered_map_basic_types,
                            BasicTestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  std::string archive_name( "test_unordered_map_basic_types.h5a" );

  std::unordered_map<T,T> unordered_map_a;
  unordered_map_a[T(0)] = T(1);
  unordered_map_a[T(1)] = T(0);

  std::unordered_map<T,std::string> unordered_map_b;
  unordered_map_b[T(0)] = "Test message 0";
  unordered_map_b[T(1)] = "Test message 1";

  std::unordered_map<std::string,T> unordered_map_c;
  unordered_map_c["0"] = T(0);
  unordered_map_c["1"] = T(1);

  {
    Utility::HDF5OArchive archive( archive_name, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE );

    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "unordered_map_a", unordered_map_a ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "unordered_map_b", unordered_map_b ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "unordered_map_c", unordered_map_c ) );
  }

  {
    Utility::HDF5IArchive archive( archive_name );

    std::unordered_map<T,T> extracted_unordered_map_a;
    std::unordered_map<T,std::string> extracted_unordered_map_b;
    std::unordered_map<std::string,T> extracted_unordered_map_c;

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "unordered_map_a", extracted_unordered_map_a ) );
    FRENSIE_CHECK_EQUAL( unordered_map_a, extracted_unordered_map_a );

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "unordered_map_b", extracted_unordered_map_b ) );
    FRENSIE_CHECK_EQUAL( unordered_map_b, extracted_unordered_map_b );

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "unordered_map_c", extracted_unordered_map_c ) );
    FRENSIE_CHECK_EQUAL( unordered_map_c, extracted_unordered_map_c );
  }
}

//---------------------------------------------------------------------------//
// Check that a unordered_map of strings can be archived
FRENSIE_UNIT_TEST( HDF5Archive, archive_unordered_map_string )
{
  std::string archive_name( "test_unordered_map_string.h5a" );

  std::unordered_map<std::string,std::string> unordered_map;
  unordered_map["0"] = "0";
  unordered_map["1"] = "1";
  unordered_map["2"] = "2";

  {
    Utility::HDF5OArchive archive( archive_name, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE );

    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "unordered_map", unordered_map ) );
  }

  {
    Utility::HDF5IArchive archive( archive_name );

    std::unordered_map<std::string,std::string> extracted_unordered_map;
    
    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "unordered_map", extracted_unordered_map ) );
    FRENSIE_CHECK_EQUAL( extracted_unordered_map, unordered_map );
  }
}

//---------------------------------------------------------------------------//
// end tstHDF5ArchiveUnorderedMap.cpp
//---------------------------------------------------------------------------//
