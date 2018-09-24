//---------------------------------------------------------------------------//
//!
//! \file   tstTwoDGridType.cpp
//! \author Luke Kersting
//! \brief  TwoDGrid type helper unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// FRENSIE Includes
#include "MonteCarlo_TwoDGridType.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the 2D grid types can be converted to int
FRENSIE_UNIT_TEST( TwoDGridType, convert_to_int )
{
  FRENSIE_CHECK_EQUAL( (unsigned)MonteCarlo::CORRELATED_GRID, 0 );
  FRENSIE_CHECK_EQUAL( (unsigned)MonteCarlo::UNIT_BASE_CORRELATED_GRID, 1 );
  FRENSIE_CHECK_EQUAL( (unsigned)MonteCarlo::DIRECT_GRID, 2 );
  FRENSIE_CHECK_EQUAL( (unsigned)MonteCarlo::UNIT_BASE_GRID, 3 );
}

//---------------------------------------------------------------------------//
// Check that an 2D grid type can be converted to a string
FRENSIE_UNIT_TEST( TwoDGridType, toString )
{
  std::string type_string =
    Utility::toString( MonteCarlo::CORRELATED_GRID );
  FRENSIE_CHECK_EQUAL( type_string, "Correlated" );

  type_string =
    Utility::toString( MonteCarlo::UNIT_BASE_CORRELATED_GRID );
  FRENSIE_CHECK_EQUAL( type_string, "Unit-base Correlated" );

  type_string =
    Utility::toString( MonteCarlo::DIRECT_GRID );
  FRENSIE_CHECK_EQUAL( type_string, "Direct" );

  type_string =
    Utility::toString( MonteCarlo::UNIT_BASE_GRID );
  FRENSIE_CHECK_EQUAL( type_string, "Unit-base" );
}

//---------------------------------------------------------------------------//
// Check that a 2D grid type can be sent to a stream
FRENSIE_UNIT_TEST( TwoDGridType, stream_operator )
{
  std::stringstream ss;

  ss << MonteCarlo::CORRELATED_GRID;
  FRENSIE_CHECK_EQUAL( ss.str(), "Correlated" );

  ss.str( "" );
  ss << MonteCarlo::UNIT_BASE_CORRELATED_GRID;
  FRENSIE_CHECK_EQUAL( ss.str(), "Unit-base Correlated" );

  ss.str( "" );
  ss << MonteCarlo::DIRECT_GRID;
  FRENSIE_CHECK_EQUAL( ss.str(), "Direct" );

  ss.str( "" );
  ss << MonteCarlo::UNIT_BASE_GRID;
  FRENSIE_CHECK_EQUAL( ss.str(), "Unit-base" );
}

//---------------------------------------------------------------------------//
// Check that an elastic electron distribution type can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( TwoDGridType,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_two_d_sampling_type" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    MonteCarlo::TwoDGridType type_1 =
      MonteCarlo::CORRELATED_GRID;

    MonteCarlo::TwoDGridType type_2 =
      MonteCarlo::UNIT_BASE_CORRELATED_GRID;

    MonteCarlo::TwoDGridType type_3 =
      MonteCarlo::DIRECT_GRID;

    MonteCarlo::TwoDGridType type_4 =
      MonteCarlo::UNIT_BASE_GRID;

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_1 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_2 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_3 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_4 ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  MonteCarlo::TwoDGridType type_1;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_1 ) );
  FRENSIE_CHECK_EQUAL( type_1, MonteCarlo::CORRELATED_GRID );

  MonteCarlo::TwoDGridType type_2;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_2 ) );
  FRENSIE_CHECK_EQUAL( type_2, MonteCarlo::UNIT_BASE_CORRELATED_GRID );

  MonteCarlo::TwoDGridType type_3;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_3 ) );
  FRENSIE_CHECK_EQUAL( type_3, MonteCarlo::DIRECT_GRID );

  MonteCarlo::TwoDGridType type_4;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_4 ) );
  FRENSIE_CHECK_EQUAL( type_4, MonteCarlo::UNIT_BASE_GRID );
}

// //---------------------------------------------------------------------------//
// // Check that a string can be converted to a TwoDGridType
// FRENSIE_UNIT_TEST( TwoDGridType,
//                    convertStringToTwoDGridType_Correlated )
// {
//   MonteCarlo::TwoDGridType interp =
//     MonteCarlo::convertStringToTwoDGridType( "Correlated" );
//   FRENSIE_CHECK_EQUAL( interp, MonteCarlo::CORRELATED_GRID );

//   interp =
//     MonteCarlo::convertStringToTwoDGridType( "correlated" );
//   FRENSIE_CHECK_EQUAL( interp, MonteCarlo::CORRELATED_GRID );

//   interp =
//     MonteCarlo::convertStringToTwoDGridType( "CORRELATED" );
//   FRENSIE_CHECK_EQUAL( interp, MonteCarlo::CORRELATED_GRID );
// }

// //---------------------------------------------------------------------------//
// // Check that a string can be converted to a TwoDGridType
// FRENSIE_UNIT_TEST( TwoDGridType,
//                    convertStringToTwoDGridType_UnitBaseCorrelated )
// {
//   MonteCarlo::TwoDGridType interp =
//     MonteCarlo::convertStringToTwoDGridType( "Unit-base Correlated" );
//   FRENSIE_CHECK_EQUAL( interp, MonteCarlo::UNIT_BASE_CORRELATED_GRID );

//   interp =
//     MonteCarlo::convertStringToTwoDGridType( "unit-base correlated" );
//   FRENSIE_CHECK_EQUAL( interp, MonteCarlo::UNIT_BASE_CORRELATED_GRID );

//   interp =
//     MonteCarlo::convertStringToTwoDGridType( "UNIT-BASE CORRELATED" );
//   FRENSIE_CHECK_EQUAL( interp, MonteCarlo::UNIT_BASE_CORRELATED_GRID );
// }

// //---------------------------------------------------------------------------//
// // Check that a string can be converted to a TwoDGridType
// FRENSIE_UNIT_TEST( TwoDGridType,
//                    convertStringToTwoDGridType_Direct )
// {
//   MonteCarlo::TwoDGridType interp =
//     MonteCarlo::convertStringToTwoDGridType( "Direct" );
//   FRENSIE_CHECK_EQUAL( interp, MonteCarlo::DIRECT_GRID );

//   interp =
//     MonteCarlo::convertStringToTwoDGridType( "direct" );
//   FRENSIE_CHECK_EQUAL( interp, MonteCarlo::DIRECT_GRID );

//   interp =
//     MonteCarlo::convertStringToTwoDGridType( "DIRECT" );
//   FRENSIE_CHECK_EQUAL( interp, MonteCarlo::DIRECT_GRID );
// }

// //---------------------------------------------------------------------------//
// // Check that a string can be converted to a TwoDGridType
// FRENSIE_UNIT_TEST( TwoDGridType,
//                    convertStringToTwoDGridType_UnitBase )
// {
//   MonteCarlo::TwoDGridType interp =
//     MonteCarlo::convertStringToTwoDGridType( "Unit-base" );
//   FRENSIE_CHECK_EQUAL( interp, MonteCarlo::UNIT_BASE_GRID );

//   interp =
//     MonteCarlo::convertStringToTwoDGridType( "unit-base" );
//   FRENSIE_CHECK_EQUAL( interp, MonteCarlo::UNIT_BASE_GRID );

//   interp =
//     MonteCarlo::convertStringToTwoDGridType( "UNIT-BASE" );
//   FRENSIE_CHECK_EQUAL( interp, MonteCarlo::UNIT_BASE_GRID );
// }

//---------------------------------------------------------------------------//
// end tstTwoDGridType.cpp
//---------------------------------------------------------------------------//