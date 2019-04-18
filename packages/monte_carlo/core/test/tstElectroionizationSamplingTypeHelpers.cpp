//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationSamplingType.hpp
//! \author Luke Kersting
//! \brief  Electroionization sampling type helper function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationSamplingType.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a sampling type can be converted to a string
FRENSIE_UNIT_TEST( ElectroionizationSamplingType, toString )
{
  std::string sampling_name =
    Utility::toString( MonteCarlo::KNOCK_ON_SAMPLING );

  FRENSIE_CHECK_EQUAL( sampling_name, "Knock-on Electroionization Sampling" );

  sampling_name = Utility::toString( MonteCarlo::OUTGOING_ENERGY_SAMPLING );

  FRENSIE_CHECK_EQUAL( sampling_name, "Outgoing Energy Electroionization Sampling" )

  sampling_name = Utility::toString( MonteCarlo::OUTGOING_ENERGY_RATIO_SAMPLING );

  FRENSIE_CHECK_EQUAL( sampling_name, "Outgoing Energy Ratio Electroionization Sampling" );
}

//---------------------------------------------------------------------------//
// Check that a sampling type can be placed in a stream
FRENSIE_UNIT_TEST( ElectroionizationSamplingType, ostream_operator )
{
  std::ostringstream oss;

  oss << MonteCarlo::KNOCK_ON_SAMPLING;

  FRENSIE_CHECK_EQUAL( oss.str(), "Knock-on Electroionization Sampling" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::OUTGOING_ENERGY_SAMPLING;

  FRENSIE_CHECK_EQUAL( oss.str(), "Outgoing Energy Electroionization Sampling" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::OUTGOING_ENERGY_RATIO_SAMPLING;

  FRENSIE_CHECK_EQUAL( oss.str(), "Outgoing Energy Ratio Electroionization Sampling" );
}

//---------------------------------------------------------------------------//
// Check that a sampling type can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( ElectroionizationSamplingType,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_adjoint_kn_sampling_type" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    MonteCarlo::ElectroionizationSamplingType type_1 =
      MonteCarlo::KNOCK_ON_SAMPLING;

    MonteCarlo::ElectroionizationSamplingType type_2 =
      MonteCarlo::OUTGOING_ENERGY_SAMPLING;

    MonteCarlo::ElectroionizationSamplingType type_3 =
      MonteCarlo::OUTGOING_ENERGY_RATIO_SAMPLING;

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_1 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_2 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_3 ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  MonteCarlo::ElectroionizationSamplingType type_1, type_2, type_3;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_1 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_2 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_3 ) );

  iarchive.reset();

  FRENSIE_CHECK_EQUAL( type_1, MonteCarlo::KNOCK_ON_SAMPLING );
  FRENSIE_CHECK_EQUAL( type_2, MonteCarlo::OUTGOING_ENERGY_SAMPLING );
  FRENSIE_CHECK_EQUAL( type_3, MonteCarlo::OUTGOING_ENERGY_RATIO_SAMPLING );
}

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationSamplingType.hpp
//---------------------------------------------------------------------------//
