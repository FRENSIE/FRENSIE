//---------------------------------------------------------------------------//
//!
//! \file   tstElasticElectronDistributionType.cpp
//! \author Luke Kersting
//! \brief  Elastic electron distribution type helper unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// FRENSIE Includes
#include "MonteCarlo_ElasticElectronDistributionType.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the elastic electron distribution types can be converted to int
FRENSIE_UNIT_TEST( ElasticElectronDistributionType, convert_to_int )
{
  FRENSIE_CHECK_EQUAL( (unsigned)MonteCarlo::COUPLED_DISTRIBUTION, 0 );
  FRENSIE_CHECK_EQUAL( (unsigned)MonteCarlo::DECOUPLED_DISTRIBUTION, 1 );
  FRENSIE_CHECK_EQUAL( (unsigned)MonteCarlo::HYBRID_DISTRIBUTION, 2 );
  FRENSIE_CHECK_EQUAL( (unsigned)MonteCarlo::CUTOFF_DISTRIBUTION, 3 );
  FRENSIE_CHECK_EQUAL( (unsigned)MonteCarlo::SCREENED_RUTHERFORD_DISTRIBUTION, 4 );
}

//---------------------------------------------------------------------------//
// Check that an elastic electron distribution type can be converted to a string
FRENSIE_UNIT_TEST( ElasticElectronDistributionType, toString )
{
  std::string type_string =
    Utility::toString( MonteCarlo::COUPLED_DISTRIBUTION );

  FRENSIE_CHECK_EQUAL( type_string, "Coupled Distribution" );

  type_string =
    Utility::toString( MonteCarlo::DECOUPLED_DISTRIBUTION );

  FRENSIE_CHECK_EQUAL( type_string, "Decoupled Distribution" );

  type_string =
    Utility::toString( MonteCarlo::HYBRID_DISTRIBUTION );

  FRENSIE_CHECK_EQUAL( type_string, "Hybrid Distribution" );

  type_string =
    Utility::toString( MonteCarlo::CUTOFF_DISTRIBUTION );

  FRENSIE_CHECK_EQUAL( type_string, "Cutoff Distribution" );

  type_string =
    Utility::toString( MonteCarlo::SCREENED_RUTHERFORD_DISTRIBUTION );

  FRENSIE_CHECK_EQUAL( type_string, "Screened Rutherford Distribution" );
}

//---------------------------------------------------------------------------//
// Check that a coupled elastic electron sampling method can be converted to a string
FRENSIE_UNIT_TEST( CoupledElasticSamplingMethod, toString )
{
  std::string type_string = Utility::toString( MonteCarlo::ONE_D_UNION );

  FRENSIE_CHECK_EQUAL( type_string, "One D Union" );

  type_string = Utility::toString( MonteCarlo::TWO_D_UNION );

  FRENSIE_CHECK_EQUAL( type_string, "Two D Union" );

  type_string = Utility::toString( MonteCarlo::MODIFIED_TWO_D_UNION );

  FRENSIE_CHECK_EQUAL( type_string, "Modified Two D Union" );
}

//---------------------------------------------------------------------------//
// Check that an elastic electron distribution type can be sent to a stream
FRENSIE_UNIT_TEST( ElasticElectronDistributionType, stream_operator )
{
  std::stringstream ss;

  ss << MonteCarlo::COUPLED_DISTRIBUTION;

  FRENSIE_CHECK_EQUAL( ss.str(), "Coupled Distribution" );

  ss.str( "" );
  ss << MonteCarlo::DECOUPLED_DISTRIBUTION;

  FRENSIE_CHECK_EQUAL( ss.str(), "Decoupled Distribution" );

  ss.str( "" );
  ss << MonteCarlo::HYBRID_DISTRIBUTION;

  FRENSIE_CHECK_EQUAL( ss.str(), "Hybrid Distribution" );

  ss.str( "" );
  ss << MonteCarlo::CUTOFF_DISTRIBUTION;

  FRENSIE_CHECK_EQUAL( ss.str(), "Cutoff Distribution" );

  ss.str( "" );
  ss << MonteCarlo::SCREENED_RUTHERFORD_DISTRIBUTION;

  FRENSIE_CHECK_EQUAL( ss.str(), "Screened Rutherford Distribution" );
}

//---------------------------------------------------------------------------//
// Check that an elastic electron distribution type can be sent to a stream
FRENSIE_UNIT_TEST( CoupledElasticSamplingMethod, stream_operator )
{
  std::stringstream ss;

  ss << MonteCarlo::ONE_D_UNION;

  FRENSIE_CHECK_EQUAL( ss.str(), "One D Union" );

  ss.str( "" );
  ss << MonteCarlo::TWO_D_UNION;

  FRENSIE_CHECK_EQUAL( ss.str(), "Two D Union" );

  ss.str( "" );
  ss << MonteCarlo::MODIFIED_TWO_D_UNION;

  FRENSIE_CHECK_EQUAL( ss.str(), "Modified Two D Union" );
}

//---------------------------------------------------------------------------//
// Check that an elastic electron distribution type can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( ElasticElectronDistributionType,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_elastic_electron_dist_type" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    MonteCarlo::ElasticElectronDistributionType type_1 =
      MonteCarlo::COUPLED_DISTRIBUTION;

    MonteCarlo::ElasticElectronDistributionType type_2 =
      MonteCarlo::DECOUPLED_DISTRIBUTION;

    MonteCarlo::ElasticElectronDistributionType type_3 =
      MonteCarlo::HYBRID_DISTRIBUTION;

    MonteCarlo::ElasticElectronDistributionType type_4 =
      MonteCarlo::CUTOFF_DISTRIBUTION;

    MonteCarlo::ElasticElectronDistributionType type_5 =
      MonteCarlo::SCREENED_RUTHERFORD_DISTRIBUTION;

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

  MonteCarlo::ElasticElectronDistributionType type_1;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_1 ) );
  FRENSIE_CHECK_EQUAL( type_1, MonteCarlo::COUPLED_DISTRIBUTION );

  MonteCarlo::ElasticElectronDistributionType type_2;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_2 ) );
  FRENSIE_CHECK_EQUAL( type_2, MonteCarlo::DECOUPLED_DISTRIBUTION );

  MonteCarlo::ElasticElectronDistributionType type_3;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_3 ) );
  FRENSIE_CHECK_EQUAL( type_3, MonteCarlo::HYBRID_DISTRIBUTION );

  MonteCarlo::ElasticElectronDistributionType type_4;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_4 ) );
  FRENSIE_CHECK_EQUAL( type_4, MonteCarlo::CUTOFF_DISTRIBUTION );

  MonteCarlo::ElasticElectronDistributionType type_5;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_5 ) );
  FRENSIE_CHECK_EQUAL( type_5, MonteCarlo::SCREENED_RUTHERFORD_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that a coupled elastic electron sampling method type can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( CoupledElasticSamplingMethod,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_coupled_elastic_sampling_type" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    MonteCarlo::CoupledElasticSamplingMethod type_1 =
      MonteCarlo::ONE_D_UNION;

    MonteCarlo::CoupledElasticSamplingMethod type_2 =
      MonteCarlo::TWO_D_UNION;

    MonteCarlo::CoupledElasticSamplingMethod type_3 =
      MonteCarlo::MODIFIED_TWO_D_UNION;

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_1 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_2 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_3 ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  MonteCarlo::CoupledElasticSamplingMethod type_1;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_1 ) );
  FRENSIE_CHECK_EQUAL( type_1, MonteCarlo::ONE_D_UNION );

  MonteCarlo::CoupledElasticSamplingMethod type_2;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_2 ) );
  FRENSIE_CHECK_EQUAL( type_2, MonteCarlo::TWO_D_UNION );

  MonteCarlo::CoupledElasticSamplingMethod type_3;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_3 ) );
  FRENSIE_CHECK_EQUAL( type_3, MonteCarlo::MODIFIED_TWO_D_UNION );
}

//---------------------------------------------------------------------------//
// end tstElasticElectronDistributionType.cpp
//---------------------------------------------------------------------------//
