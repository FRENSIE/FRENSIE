//---------------------------------------------------------------------------//
//!
//! \file   tstTwoDSamplingType.cpp
//! \author Luke Kersting
//! \brief  TwoDSampling type helper unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// FRENSIE Includes
#include "MonteCarlo_TwoDSamplingType.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the 2D sampling types can be converted to int
FRENSIE_UNIT_TEST( TwoDSamplingType, convert_to_int )
{
  FRENSIE_CHECK_EQUAL( (unsigned)MonteCarlo::CORRELATED_SAMPLING, 1 );
  FRENSIE_CHECK_EQUAL( (unsigned)MonteCarlo::UNIT_BASE_CORRELATED_SAMPLING, 2 );
  FRENSIE_CHECK_EQUAL( (unsigned)MonteCarlo::DIRECT_SAMPLING, 3 );
  FRENSIE_CHECK_EQUAL( (unsigned)MonteCarlo::UNIT_BASE_SAMPLING, 4 );
  FRENSIE_CHECK_EQUAL( (unsigned)MonteCarlo::CUMULATIVE_POINTS_SAMPLING, 5 );
}

//---------------------------------------------------------------------------//
// Check that an 2D sampling type can be converted to a string
FRENSIE_UNIT_TEST( TwoDSamplingType, toString )
{
  std::string type_string =
    Utility::toString( MonteCarlo::CORRELATED_SAMPLING );
  FRENSIE_CHECK_EQUAL( type_string, "Correlated" );

  type_string =
    Utility::toString( MonteCarlo::UNIT_BASE_CORRELATED_SAMPLING );
  FRENSIE_CHECK_EQUAL( type_string, "Unit-base Correlated" );

  type_string =
    Utility::toString( MonteCarlo::DIRECT_SAMPLING );
  FRENSIE_CHECK_EQUAL( type_string, "Direct" );

  type_string =
    Utility::toString( MonteCarlo::UNIT_BASE_SAMPLING );
  FRENSIE_CHECK_EQUAL( type_string, "Unit-base" );

  type_string =
    Utility::toString( MonteCarlo::CUMULATIVE_POINTS_SAMPLING );
  FRENSIE_CHECK_EQUAL( type_string, "Cumulative Points" );
}

//---------------------------------------------------------------------------//
// Check that a 2D Sampling type can be sent to a stream
FRENSIE_UNIT_TEST( TwoDSamplingType, stream_operator )
{
  std::stringstream ss;

  ss << MonteCarlo::CORRELATED_SAMPLING;
  FRENSIE_CHECK_EQUAL( ss.str(), "Correlated" );

  ss.str( "" );
  ss << MonteCarlo::UNIT_BASE_CORRELATED_SAMPLING;
  FRENSIE_CHECK_EQUAL( ss.str(), "Unit-base Correlated" );

  ss.str( "" );
  ss << MonteCarlo::DIRECT_SAMPLING;
  FRENSIE_CHECK_EQUAL( ss.str(), "Direct" );

  ss.str( "" );
  ss << MonteCarlo::UNIT_BASE_SAMPLING;
  FRENSIE_CHECK_EQUAL( ss.str(), "Unit-base" );

  ss.str( "" );
  ss << MonteCarlo::CUMULATIVE_POINTS_SAMPLING;
  FRENSIE_CHECK_EQUAL( ss.str(), "Cumulative Points" );
}

//---------------------------------------------------------------------------//
// Check that an elastic electron distribution type can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( TwoDSamplingType,
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

    MonteCarlo::TwoDSamplingType type_1 =
      MonteCarlo::CORRELATED_SAMPLING;

    MonteCarlo::TwoDSamplingType type_2 =
      MonteCarlo::UNIT_BASE_CORRELATED_SAMPLING;

    MonteCarlo::TwoDSamplingType type_3 =
      MonteCarlo::DIRECT_SAMPLING;

    MonteCarlo::TwoDSamplingType type_4 =
      MonteCarlo::UNIT_BASE_SAMPLING;

    MonteCarlo::TwoDSamplingType type_5 =
      MonteCarlo::CUMULATIVE_POINTS_SAMPLING;

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_1 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_2 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_3 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_4 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_5 ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  MonteCarlo::TwoDSamplingType type_1;
  
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_1 ) );
  FRENSIE_CHECK_EQUAL( type_1, MonteCarlo::CORRELATED_SAMPLING );

  MonteCarlo::TwoDSamplingType type_2;
  
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_2 ) );
  FRENSIE_CHECK_EQUAL( type_2, MonteCarlo::UNIT_BASE_CORRELATED_SAMPLING );

  MonteCarlo::TwoDSamplingType type_3;
  
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_3 ) );
  FRENSIE_CHECK_EQUAL( type_3, MonteCarlo::DIRECT_SAMPLING );

  MonteCarlo::TwoDSamplingType type_4;
  
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_4 ) );
  FRENSIE_CHECK_EQUAL( type_4, MonteCarlo::UNIT_BASE_SAMPLING );

  MonteCarlo::TwoDSamplingType type_5;
  
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_5 ) );
  FRENSIE_CHECK_EQUAL( type_5, MonteCarlo::CUMULATIVE_POINTS_SAMPLING );
}

//---------------------------------------------------------------------------//
// end tstTwoDSamplingType.cpp
//---------------------------------------------------------------------------//
