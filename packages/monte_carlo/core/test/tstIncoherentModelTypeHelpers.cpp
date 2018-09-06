//---------------------------------------------------------------------------//
//!
//! \file   tstIncoherentModelTypeHelpers.cpp
//! \author Alex Robinson
//! \brief  Incoherent model type helper function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// FRENSIE Includes
#include "MonteCarlo_IncoherentModelType.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a model type can be converted to a string
FRENSIE_UNIT_TEST( IncoherentModelType, toString )
{
  std::string model_name =
    Utility::toString( MonteCarlo::KN_INCOHERENT_MODEL );

  FRENSIE_CHECK_EQUAL( model_name, "Klein-Nishina Model" );

  model_name = Utility::toString( MonteCarlo::WH_INCOHERENT_MODEL );

  FRENSIE_CHECK_EQUAL( model_name, "Waller-Hartree Model" );

  model_name = Utility::toString( MonteCarlo::IMPULSE_INCOHERENT_MODEL );

  FRENSIE_CHECK_EQUAL( model_name, "Impulse Model" );

  model_name = Utility::toString( MonteCarlo::DECOUPLED_HALF_PROFILE_DB_HYBRID_INCOHERENT_MODEL );

  FRENSIE_CHECK_EQUAL( model_name, "DHP Doppler Broadened Hybrid Model" );

  model_name = Utility::toString( MonteCarlo::DECOUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL );

  FRENSIE_CHECK_EQUAL( model_name, "DFP Doppler Broadened Hybrid Model" );

  model_name = Utility::toString( MonteCarlo::COUPLED_HALF_PROFILE_DB_HYBRID_INCOHERENT_MODEL );

  FRENSIE_CHECK_EQUAL( model_name, "CHP Doppler Broadened Hybrid Model" );

  model_name = Utility::toString( MonteCarlo::COUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL );

  FRENSIE_CHECK_EQUAL( model_name, "CFP Doppler Broadened Hybrid Model" );

  model_name = Utility::toString( MonteCarlo::FULL_PROFILE_DB_IMPULSE_INCOHERENT_MODEL );

  FRENSIE_CHECK_EQUAL( model_name, "FP Doppler Broadened Impulse Model" );
}

//---------------------------------------------------------------------------//
// Check that a model type can be placed in an ostream
FRENSIE_UNIT_TEST( IncoherentModelType,
                   ostream_operator )
{
  std::ostringstream oss;

  oss << MonteCarlo::KN_INCOHERENT_MODEL;

  FRENSIE_CHECK_EQUAL( oss.str(), "Klein-Nishina Model" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::WH_INCOHERENT_MODEL;

  FRENSIE_CHECK_EQUAL( oss.str(), "Waller-Hartree Model" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::IMPULSE_INCOHERENT_MODEL;

  FRENSIE_CHECK_EQUAL( oss.str(), "Impulse Model" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::DECOUPLED_HALF_PROFILE_DB_HYBRID_INCOHERENT_MODEL;

  FRENSIE_CHECK_EQUAL( oss.str(), "DHP Doppler Broadened Hybrid Model" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::DECOUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL;

  FRENSIE_CHECK_EQUAL( oss.str(), "DFP Doppler Broadened Hybrid Model" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::COUPLED_HALF_PROFILE_DB_HYBRID_INCOHERENT_MODEL;

  FRENSIE_CHECK_EQUAL( oss.str(), "CHP Doppler Broadened Hybrid Model" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::COUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL;

  FRENSIE_CHECK_EQUAL( oss.str(), "CFP Doppler Broadened Hybrid Model" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::FULL_PROFILE_DB_IMPULSE_INCOHERENT_MODEL;

  FRENSIE_CHECK_EQUAL( oss.str(), "FP Doppler Broadened Impulse Model" );
}

//---------------------------------------------------------------------------//
// Check that a ParticleType can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( IncoherentModelType,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_incoherent_model_type" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    MonteCarlo::IncoherentModelType type_1 =
      MonteCarlo::KN_INCOHERENT_MODEL;

    MonteCarlo::IncoherentModelType type_2 =
      MonteCarlo::WH_INCOHERENT_MODEL;

    MonteCarlo::IncoherentModelType type_3 =
      MonteCarlo::IMPULSE_INCOHERENT_MODEL;

    MonteCarlo::IncoherentModelType type_4 =
      MonteCarlo::DECOUPLED_HALF_PROFILE_DB_HYBRID_INCOHERENT_MODEL;

    MonteCarlo::IncoherentModelType type_5 =
      MonteCarlo::DECOUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL;

    MonteCarlo::IncoherentModelType type_6 =
      MonteCarlo::COUPLED_HALF_PROFILE_DB_HYBRID_INCOHERENT_MODEL;

    MonteCarlo::IncoherentModelType type_7 =
      MonteCarlo::COUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL;

    MonteCarlo::IncoherentModelType type_8 =
      MonteCarlo::FULL_PROFILE_DB_IMPULSE_INCOHERENT_MODEL;

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

  MonteCarlo::IncoherentModelType type_1;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_1 ) );
  FRENSIE_CHECK_EQUAL( type_1, MonteCarlo::KN_INCOHERENT_MODEL );
  
  MonteCarlo::IncoherentModelType type_2;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_2 ) );
  FRENSIE_CHECK_EQUAL( type_2, MonteCarlo::WH_INCOHERENT_MODEL );
  
  MonteCarlo::IncoherentModelType type_3;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_3 ) );
  FRENSIE_CHECK_EQUAL( type_3, MonteCarlo::IMPULSE_INCOHERENT_MODEL );
  
  MonteCarlo::IncoherentModelType type_4;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_4 ) );
  FRENSIE_CHECK_EQUAL( type_4, MonteCarlo::DECOUPLED_HALF_PROFILE_DB_HYBRID_INCOHERENT_MODEL );

  MonteCarlo::IncoherentModelType type_5;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_5 ) );
  FRENSIE_CHECK_EQUAL( type_5, MonteCarlo::DECOUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL );

  MonteCarlo::IncoherentModelType type_6;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_6 ) );
  FRENSIE_CHECK_EQUAL( type_6, MonteCarlo::COUPLED_HALF_PROFILE_DB_HYBRID_INCOHERENT_MODEL );

  MonteCarlo::IncoherentModelType type_7;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_7 ) );
  FRENSIE_CHECK_EQUAL( type_7, MonteCarlo::COUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL );

  MonteCarlo::IncoherentModelType type_8;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_8 ) );
  FRENSIE_CHECK_EQUAL( type_8, MonteCarlo::FULL_PROFILE_DB_IMPULSE_INCOHERENT_MODEL );
}

//---------------------------------------------------------------------------//
// end tstIncoherentModelTypeHelpers.cpp
//---------------------------------------------------------------------------//
