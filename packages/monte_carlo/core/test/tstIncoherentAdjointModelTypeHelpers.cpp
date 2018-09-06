//---------------------------------------------------------------------------//
//!
//! \file   tstIncoherentAdjointModelTypeHelpers.cpp
//! \author Alex Robinson
//! \brief  Incoherent adjoint model type helper function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// FRENSIE Includes
#include "MonteCarlo_IncoherentAdjointModelType.hpp"
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
FRENSIE_UNIT_TEST( IncoherentAdjointModelType, toString )
{
  std::string model_name =
    Utility::toString( MonteCarlo::KN_INCOHERENT_ADJOINT_MODEL );

  FRENSIE_CHECK_EQUAL( model_name, "Klein-Nishina Adjoint Model" );

  model_name = Utility::toString( MonteCarlo::WH_INCOHERENT_ADJOINT_MODEL );

  FRENSIE_CHECK_EQUAL( model_name, "Waller-Hartree Adjoint Model" );

  model_name = Utility::toString( MonteCarlo::IMPULSE_INCOHERENT_ADJOINT_MODEL );

  FRENSIE_CHECK_EQUAL( model_name, "Impulse Adjoint Model" );

  model_name = Utility::toString( MonteCarlo::DB_IMPULSE_INCOHERENT_ADJOINT_MODEL );

  FRENSIE_CHECK_EQUAL( model_name, "Doppler Broadened Impulse Adjoint Model" );
}

//---------------------------------------------------------------------------//
// Check that a model type can be placed in an ostream
FRENSIE_UNIT_TEST( IncoherentAdjointModelType,
                   ostream_operator )
{
  std::ostringstream oss;

  oss << MonteCarlo::KN_INCOHERENT_ADJOINT_MODEL;

  FRENSIE_CHECK_EQUAL( oss.str(), "Klein-Nishina Adjoint Model" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::WH_INCOHERENT_ADJOINT_MODEL;

  FRENSIE_CHECK_EQUAL( oss.str(), "Waller-Hartree Adjoint Model" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::IMPULSE_INCOHERENT_ADJOINT_MODEL;

  FRENSIE_CHECK_EQUAL( oss.str(), "Impulse Adjoint Model" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::DB_IMPULSE_INCOHERENT_ADJOINT_MODEL;

  FRENSIE_CHECK_EQUAL( oss.str(), "Doppler Broadened Impulse Adjoint Model" );
}

//---------------------------------------------------------------------------//
// Check that a ParticleType can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( IncoherentAdjointModelType,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_incoherent_adjoint_model_type" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    MonteCarlo::IncoherentAdjointModelType type_1 =
      MonteCarlo::KN_INCOHERENT_ADJOINT_MODEL;

    MonteCarlo::IncoherentAdjointModelType type_2 =
      MonteCarlo::WH_INCOHERENT_ADJOINT_MODEL;

    MonteCarlo::IncoherentAdjointModelType type_3 =
      MonteCarlo::IMPULSE_INCOHERENT_ADJOINT_MODEL;

    MonteCarlo::IncoherentAdjointModelType type_4 =
      MonteCarlo::DB_IMPULSE_INCOHERENT_ADJOINT_MODEL;

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

  MonteCarlo::IncoherentAdjointModelType type_1;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_1 ) );
  FRENSIE_CHECK_EQUAL( type_1, MonteCarlo::KN_INCOHERENT_ADJOINT_MODEL );
  
  MonteCarlo::IncoherentAdjointModelType type_2;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_2 ) );
  FRENSIE_CHECK_EQUAL( type_2, MonteCarlo::WH_INCOHERENT_ADJOINT_MODEL );
  
  MonteCarlo::IncoherentAdjointModelType type_3;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_3 ) );
  FRENSIE_CHECK_EQUAL( type_3, MonteCarlo::IMPULSE_INCOHERENT_ADJOINT_MODEL );
  
  MonteCarlo::IncoherentAdjointModelType type_4;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_4 ) );
  FRENSIE_CHECK_EQUAL( type_4, MonteCarlo::DB_IMPULSE_INCOHERENT_ADJOINT_MODEL );
}

//---------------------------------------------------------------------------//
// end tstIncoherentAdjointModelTypeHelpers.cpp
//---------------------------------------------------------------------------//
