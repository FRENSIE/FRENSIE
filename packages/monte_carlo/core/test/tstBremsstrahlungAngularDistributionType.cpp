//---------------------------------------------------------------------------//
//!
//! \file   tstBremsstrahlungAngularDistributionType.cpp
//! \author Luke Kersting
//! \brief  Bremsstrahlung angular distribution type helper unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// FRENSIE Includes
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the bremsstrahlung angular distribution types can be converted to int
FRENSIE_UNIT_TEST( BremsstrahlungAngularDistributionType, convert_to_int )
{
  FRENSIE_CHECK_EQUAL( (unsigned)MonteCarlo::DIPOLE_DISTRIBUTION, 1 );
  FRENSIE_CHECK_EQUAL( (unsigned)MonteCarlo::TABULAR_DISTRIBUTION, 2 );
  FRENSIE_CHECK_EQUAL( (unsigned)MonteCarlo::TWOBS_DISTRIBUTION, 3 );
}

//---------------------------------------------------------------------------//
// Check that a bremsstrahlung angular distribution type can be converted to a string
FRENSIE_UNIT_TEST( BremsstrahlungAngularDistributionType, toString )
{
  std::string type_string =
    Utility::toString( MonteCarlo::DIPOLE_DISTRIBUTION );
  
  FRENSIE_CHECK_EQUAL( type_string, "Dipole Distribution" );

  type_string =
    Utility::toString( MonteCarlo::TABULAR_DISTRIBUTION );

  FRENSIE_CHECK_EQUAL( type_string, "Tabular Distribution" );

  type_string =
    Utility::toString( MonteCarlo::TWOBS_DISTRIBUTION );

  FRENSIE_CHECK_EQUAL( type_string, "2BS Distribution" );
}


//---------------------------------------------------------------------------//
// Check that a bremsstrahlung angular distribution type can be sent to a stream
FRENSIE_UNIT_TEST( BremsstrahlungAngularDistributionType, stream_operator )
{
  std::stringstream ss;

  ss << MonteCarlo::DIPOLE_DISTRIBUTION;

  FRENSIE_CHECK_EQUAL( ss.str(), "Dipole Distribution" );

  ss.str( "" );
  ss << MonteCarlo::TABULAR_DISTRIBUTION;

  FRENSIE_CHECK_EQUAL( ss.str(), "Tabular Distribution" );

  ss.str( "" );
  ss << MonteCarlo::TWOBS_DISTRIBUTION;

  FRENSIE_CHECK_EQUAL( ss.str(), "2BS Distribution" );
}

//---------------------------------------------------------------------------//
// Check that an elastic electron distribution type can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( BremsstrahlungAngularDistributionType,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_bremss_angular_dist_type" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    MonteCarlo::BremsstrahlungAngularDistributionType type_1 =
      MonteCarlo::DIPOLE_DISTRIBUTION;

    MonteCarlo::BremsstrahlungAngularDistributionType type_2 =
      MonteCarlo::TABULAR_DISTRIBUTION;

    MonteCarlo::BremsstrahlungAngularDistributionType type_3 =
      MonteCarlo::TWOBS_DISTRIBUTION;

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_1 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_2 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_3 ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  MonteCarlo::BremsstrahlungAngularDistributionType type_1;
  
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_1 ) );
  FRENSIE_CHECK_EQUAL( type_1, MonteCarlo::DIPOLE_DISTRIBUTION );

  MonteCarlo::BremsstrahlungAngularDistributionType type_2;
  
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_2 ) );
  FRENSIE_CHECK_EQUAL( type_2, MonteCarlo::TABULAR_DISTRIBUTION );

  MonteCarlo::BremsstrahlungAngularDistributionType type_3;
  
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_3 ) );
  FRENSIE_CHECK_EQUAL( type_3, MonteCarlo::TWOBS_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// end tstBremsstrahlungAngularDistributionType.cpp
//---------------------------------------------------------------------------//
