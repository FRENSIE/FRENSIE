//---------------------------------------------------------------------------//
//!
//! \file   tstTwoDInterpolationType.cpp
//! \author Luke Kersting
//! \brief  TwoDInterpolation type helper unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// FRENSIE Includes
#include "MonteCarlo_TwoDInterpolationType.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an 2D interpolation type can be converted to a string
FRENSIE_UNIT_TEST( TwoDInterpolationType, toString )
{
  std::string type_string =
    Utility::toString( MonteCarlo::LINLINLIN_INTERPOLATION );
  FRENSIE_CHECK_EQUAL( type_string, "Lin-Lin-Lin" );

  type_string =
    Utility::toString( MonteCarlo::LINLINLOG_INTERPOLATION );
  FRENSIE_CHECK_EQUAL( type_string, "Lin-Lin-Log" );

  type_string =
    Utility::toString( MonteCarlo::LINLOGLIN_INTERPOLATION );
  FRENSIE_CHECK_EQUAL( type_string, "Lin-Log-Lin" );

  type_string =
    Utility::toString( MonteCarlo::LOGLINLIN_INTERPOLATION );
  FRENSIE_CHECK_EQUAL( type_string, "Log-Lin-Lin" );

  type_string =
    Utility::toString( MonteCarlo::LOGLOGLIN_INTERPOLATION );
  FRENSIE_CHECK_EQUAL( type_string, "Log-Log-Lin" );

  type_string =
    Utility::toString( MonteCarlo::LOGLINLOG_INTERPOLATION );
  FRENSIE_CHECK_EQUAL( type_string, "Log-Lin-Log" );

  type_string =
    Utility::toString( MonteCarlo::LINLOGLOG_INTERPOLATION );
  FRENSIE_CHECK_EQUAL( type_string, "Lin-Log-Log" );

  type_string =
    Utility::toString( MonteCarlo::LOGLOGLOG_INTERPOLATION );
  FRENSIE_CHECK_EQUAL( type_string, "Log-Log-Log" );
}

//---------------------------------------------------------------------------//
// Check that a 2D interpolation type can be sent to a stream
FRENSIE_UNIT_TEST( TwoDInterpolationType, stream_operator )
{
  std::stringstream ss;

  ss << MonteCarlo::LINLINLIN_INTERPOLATION;
  FRENSIE_CHECK_EQUAL( ss.str(), "Lin-Lin-Lin" );

  ss.str( "" );
  ss << MonteCarlo::LINLINLOG_INTERPOLATION;
  FRENSIE_CHECK_EQUAL( ss.str(), "Lin-Lin-Log" );

  ss.str( "" );
  ss << MonteCarlo::LINLOGLIN_INTERPOLATION;
  FRENSIE_CHECK_EQUAL( ss.str(), "Lin-Log-Lin" );

  ss.str( "" );
  ss << MonteCarlo::LOGLINLIN_INTERPOLATION;
  FRENSIE_CHECK_EQUAL( ss.str(), "Log-Lin-Lin" );

  ss.str( "" );
  ss << MonteCarlo::LOGLOGLIN_INTERPOLATION;
  FRENSIE_CHECK_EQUAL( ss.str(), "Log-Log-Lin" );

  ss.str( "" );
  ss << MonteCarlo::LOGLINLOG_INTERPOLATION;
  FRENSIE_CHECK_EQUAL( ss.str(), "Log-Lin-Log" );

  ss.str( "" );
  ss << MonteCarlo::LINLOGLOG_INTERPOLATION;
  FRENSIE_CHECK_EQUAL( ss.str(), "Lin-Log-Log" );

  ss.str( "" );
  ss << MonteCarlo::LOGLOGLOG_INTERPOLATION;
  FRENSIE_CHECK_EQUAL( ss.str(), "Log-Log-Log" );
}

//---------------------------------------------------------------------------//
// Check that an elastic electron distribution type can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( TwoDInterpolationType,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_two_d_interp_type" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    MonteCarlo::TwoDInterpolationType type_1 =
      MonteCarlo::LINLINLIN_INTERPOLATION;

    MonteCarlo::TwoDInterpolationType type_2 =
      MonteCarlo::LINLINLOG_INTERPOLATION;

    MonteCarlo::TwoDInterpolationType type_3 =
      MonteCarlo::LINLOGLIN_INTERPOLATION;

    MonteCarlo::TwoDInterpolationType type_4 =
      MonteCarlo::LOGLINLIN_INTERPOLATION;

    MonteCarlo::TwoDInterpolationType type_5 =
      MonteCarlo::LOGLOGLIN_INTERPOLATION;

    MonteCarlo::TwoDInterpolationType type_6 =
      MonteCarlo::LOGLINLOG_INTERPOLATION;

    MonteCarlo::TwoDInterpolationType type_7 =
      MonteCarlo::LINLOGLOG_INTERPOLATION;

    MonteCarlo::TwoDInterpolationType type_8 =
      MonteCarlo::LOGLOGLOG_INTERPOLATION;

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_1 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_2 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_3 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_4 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_5 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_6 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_7 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_8 ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  MonteCarlo::TwoDInterpolationType type_1;
  
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_1 ) );
  FRENSIE_CHECK_EQUAL( type_1, MonteCarlo::LINLINLIN_INTERPOLATION );

  MonteCarlo::TwoDInterpolationType type_2;
  
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_2 ) );
  FRENSIE_CHECK_EQUAL( type_2, MonteCarlo::LINLINLOG_INTERPOLATION );

  MonteCarlo::TwoDInterpolationType type_3;
  
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_3 ) );
  FRENSIE_CHECK_EQUAL( type_3, MonteCarlo::LINLOGLIN_INTERPOLATION );

  MonteCarlo::TwoDInterpolationType type_4;
  
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_4 ) );
  FRENSIE_CHECK_EQUAL( type_4, MonteCarlo::LOGLINLIN_INTERPOLATION );

  MonteCarlo::TwoDInterpolationType type_5;
  
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_5 ) );
  FRENSIE_CHECK_EQUAL( type_5, MonteCarlo::LOGLOGLIN_INTERPOLATION );

  MonteCarlo::TwoDInterpolationType type_6;
  
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_6 ) );
  FRENSIE_CHECK_EQUAL( type_6, MonteCarlo::LOGLINLOG_INTERPOLATION );

  MonteCarlo::TwoDInterpolationType type_7;
  
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_7 ) );
  FRENSIE_CHECK_EQUAL( type_7, MonteCarlo::LINLOGLOG_INTERPOLATION );

  MonteCarlo::TwoDInterpolationType type_8;
  
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_8 ) );
  FRENSIE_CHECK_EQUAL( type_8, MonteCarlo::LOGLOGLOG_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// end tstTwoDInterpolationType.cpp
//---------------------------------------------------------------------------//
