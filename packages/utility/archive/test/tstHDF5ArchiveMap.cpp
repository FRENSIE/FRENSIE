//---------------------------------------------------------------------------//
//!
//! \file   tstHDF5ArchiveMap.cpp
//! \author Alex Robinson
//! \brief  HDF5 archive map unit tests
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
// Check that maps of basic types can be archived
FRENSIE_UNIT_TEST_TEMPLATE( HDF5Archive,
                            archive_map_basic_types,
                            BasicTestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  std::string archive_name( "test_map_basic_types.h5a" );

  std::map<T,T> map_a;
  map_a[T(0)] = T(1);
  map_a[T(1)] = T(0);

  std::map<T,std::string> map_b;
  map_b[T(0)] = "Test message 0";
  map_b[T(1)] = "Test message 1";

  std::map<std::string,T> map_c;
  map_c["0"] = T(0);
  map_c["1"] = T(1);

  {
    Utility::HDF5OArchive archive( archive_name, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE );

    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "map_a", map_a ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "map_b", map_b ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "map_c", map_c ) );
  }

  {
    Utility::HDF5IArchive archive( archive_name );

    std::map<T,T> extracted_map_a;
    std::map<T,std::string> extracted_map_b;
    std::map<std::string,T> extracted_map_c;

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "map_a", extracted_map_a ) );
    FRENSIE_CHECK_EQUAL( map_a, extracted_map_a );

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "map_b", extracted_map_b ) );
    FRENSIE_CHECK_EQUAL( map_b, extracted_map_b );

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "map_c", extracted_map_c ) );
    FRENSIE_CHECK_EQUAL( map_c, extracted_map_c );
  }
}

//---------------------------------------------------------------------------//
// Check that a map of strings can be archived
FRENSIE_UNIT_TEST( HDF5Archive, archive_map_string )
{
  std::string archive_name( "test_map_string.h5a" );

  std::map<std::string,std::string> map;
  map["0"] = "0";
  map["1"] = "1";
  map["2"] = "2";

  {
    Utility::HDF5OArchive archive( archive_name, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE );

    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "map", map ) );
  }

  {
    Utility::HDF5IArchive archive( archive_name );

    std::map<std::string,std::string> extracted_map;
    
    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "map", extracted_map ) );
    FRENSIE_CHECK_EQUAL( extracted_map, map );
  }
}

//---------------------------------------------------------------------------//
// end tstHDF5ArchiveMap.cpp
//---------------------------------------------------------------------------//
