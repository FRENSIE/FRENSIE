//---------------------------------------------------------------------------//
//!
//! \file   tstObserverPhaseSpaceDimension.cpp
//! \author Alex Robinson
//! \brief  Observer phase space dimension unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <string>

// FRENSIE Includes
#include "MonteCarlo_ObserverPhaseSpaceDimension.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types.
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check if the dimension enum can be converted to a string
FRENSIE_UNIT_TEST( ObserverPhaseSpaceDimension, toString )
{
  std::string dimension_name =
    Utility::toString( MonteCarlo::OBSERVER_COSINE_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension_name, "Cosine" );

  dimension_name =
    Utility::toString( MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension_name, "Source Energy" );

  dimension_name =
    Utility::toString( MonteCarlo::OBSERVER_ENERGY_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension_name, "Energy" );

  dimension_name =
    Utility::toString( MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension_name, "Source Time" );

  dimension_name =
    Utility::toString( MonteCarlo::OBSERVER_TIME_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension_name, "Time" );

  dimension_name =
    Utility::toString( MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension_name, "Collision Number" );

  dimension_name =
    Utility::toString( MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension_name, "Source Id" );
}

//---------------------------------------------------------------------------//
// Check if a dimension enum can be placed in a stream
FRENSIE_UNIT_TEST( ObserverPhaseSpaceDimension, stream_operator )
{
  std::ostringstream oss;

  oss << MonteCarlo::OBSERVER_COSINE_DIMENSION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Cosine" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Source Energy" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::OBSERVER_ENERGY_DIMENSION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Energy" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Source Time" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::OBSERVER_TIME_DIMENSION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Time" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Collision Number" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Source Id" );
}

//---------------------------------------------------------------------------//
// Check that an enum can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( ObserverPhaseSpaceDimension,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_observer_phase_space_dimension_enum" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    MonteCarlo::ObserverPhaseSpaceDimension dimension_1 =
      MonteCarlo::OBSERVER_COSINE_DIMENSION;

    MonteCarlo::ObserverPhaseSpaceDimension dimension_2 =
      MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION;

    MonteCarlo::ObserverPhaseSpaceDimension dimension_3 =
      MonteCarlo::OBSERVER_ENERGY_DIMENSION;

    MonteCarlo::ObserverPhaseSpaceDimension dimension_4 =
      MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION;

    MonteCarlo::ObserverPhaseSpaceDimension dimension_5 =
      MonteCarlo::OBSERVER_TIME_DIMENSION;

    MonteCarlo::ObserverPhaseSpaceDimension dimension_6 =
      MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION;

    MonteCarlo::ObserverPhaseSpaceDimension dimension_7 =
      MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION;

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( dimension_1 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( dimension_2 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( dimension_3 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( dimension_4 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( dimension_5 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( dimension_6 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( dimension_7 ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  MonteCarlo::ObserverPhaseSpaceDimension dimension_1, dimension_2,
    dimension_3, dimension_4, dimension_5, dimension_6, dimension_7;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( dimension_1 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( dimension_2 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( dimension_3 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( dimension_4 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( dimension_5 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( dimension_6 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( dimension_7 ) );

  iarchive.reset();

  FRENSIE_CHECK_EQUAL( dimension_1, MonteCarlo::OBSERVER_COSINE_DIMENSION );
  FRENSIE_CHECK_EQUAL( dimension_2, MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION );
  FRENSIE_CHECK_EQUAL( dimension_3, MonteCarlo::OBSERVER_ENERGY_DIMENSION );
  FRENSIE_CHECK_EQUAL( dimension_4, MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION );
  FRENSIE_CHECK_EQUAL( dimension_5, MonteCarlo::OBSERVER_TIME_DIMENSION );
  FRENSIE_CHECK_EQUAL( dimension_6, MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION );
  FRENSIE_CHECK_EQUAL( dimension_7, MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION );
}

//---------------------------------------------------------------------------//
// end tstObserverPhaseSpaceDimension.cpp
//---------------------------------------------------------------------------//
