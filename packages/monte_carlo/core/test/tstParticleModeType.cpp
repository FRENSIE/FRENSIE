//---------------------------------------------------------------------------//
//!
//! \file   tstParticleModeType.cpp
//! \author Luke Kersting, Alex Robinson
//! \brief  Particle mode type unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// FRENSIE Includes
#include "MonteCarlo_ParticleModeType.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Test that an enum can be converted to a string
FRENSIE_UNIT_TEST( ParticleModeType, toString )
{
  std::string mode =
    Utility::toString( MonteCarlo::NEUTRON_MODE );
  
  FRENSIE_CHECK_EQUAL( mode, "Neutron Mode" );

  mode = Utility::toString( MonteCarlo::PHOTON_MODE );

  FRENSIE_CHECK_EQUAL( mode, "Photon Mode" );

  mode = Utility::toString( MonteCarlo::ELECTRON_MODE );

  FRENSIE_CHECK_EQUAL( mode, "Electron Mode" );

  mode = Utility::toString( MonteCarlo::NEUTRON_PHOTON_MODE );

  FRENSIE_CHECK_EQUAL( mode, "Neutron-Photon Mode" );

  mode = Utility::toString( MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE );

  FRENSIE_CHECK_EQUAL( mode, "Neutron-Photon-Electron Mode" );

  mode = Utility::toString( MonteCarlo::PHOTON_ELECTRON_MODE );

  FRENSIE_CHECK_EQUAL( mode, "Photon-Electron Mode" );

  mode = Utility::toString( MonteCarlo::ADJOINT_NEUTRON_MODE );
  
  FRENSIE_CHECK_EQUAL( mode, "Adjoint Neutron Mode" );

  mode = Utility::toString( MonteCarlo::ADJOINT_PHOTON_MODE );

  FRENSIE_CHECK_EQUAL( mode, "Adjoint Photon Mode" );

  mode = Utility::toString( MonteCarlo::ADJOINT_ELECTRON_MODE );

  FRENSIE_CHECK_EQUAL( mode, "Adjoint Electron Mode" );
}

//---------------------------------------------------------------------------//
// Test that an enum can be placed in a stream
FRENSIE_UNIT_TEST( ParticleModeType, stream_operator )
{
  std::ostringstream oss;
  oss << MonteCarlo::NEUTRON_MODE;

  FRENSIE_CHECK_EQUAL( oss.str(), "Neutron Mode" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::PHOTON_MODE;

  FRENSIE_CHECK_EQUAL( oss.str(), "Photon Mode" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::ELECTRON_MODE;

  FRENSIE_CHECK_EQUAL( oss.str(), "Electron Mode" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::NEUTRON_PHOTON_MODE;

  FRENSIE_CHECK_EQUAL( oss.str(), "Neutron-Photon Mode" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE;

  FRENSIE_CHECK_EQUAL( oss.str(), "Neutron-Photon-Electron Mode" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::PHOTON_ELECTRON_MODE;

  FRENSIE_CHECK_EQUAL( oss.str(), "Photon-Electron Mode" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::ADJOINT_NEUTRON_MODE;

  FRENSIE_CHECK_EQUAL( oss.str(), "Adjoint Neutron Mode" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::ADJOINT_PHOTON_MODE;

  FRENSIE_CHECK_EQUAL( oss.str(), "Adjoint Photon Mode" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::ADJOINT_ELECTRON_MODE;

  FRENSIE_CHECK_EQUAL( oss.str(), "Adjoint Electron Mode" );

  oss.str( "" );
  oss.clear();
}

//---------------------------------------------------------------------------//
// Check that a particle mode type can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( ParticleModeType,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_particle_mode_type" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    MonteCarlo::ParticleModeType type_1 =
      MonteCarlo::NEUTRON_MODE;

    MonteCarlo::ParticleModeType type_2 =
      MonteCarlo::PHOTON_MODE;

    MonteCarlo::ParticleModeType type_3 =
      MonteCarlo::ELECTRON_MODE;

    MonteCarlo::ParticleModeType type_4 =
      MonteCarlo::NEUTRON_PHOTON_MODE;

    MonteCarlo::ParticleModeType type_5 =
      MonteCarlo::PHOTON_ELECTRON_MODE;

    MonteCarlo::ParticleModeType type_6 =
      MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE;

    MonteCarlo::ParticleModeType type_7 =
      MonteCarlo::ADJOINT_NEUTRON_MODE;

    MonteCarlo::ParticleModeType type_8 =
      MonteCarlo::ADJOINT_PHOTON_MODE;

    MonteCarlo::ParticleModeType type_9 =
      MonteCarlo::ADJOINT_ELECTRON_MODE;

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_1 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_2 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_3 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_4 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_5 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_6 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_7 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_8 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_9 ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  MonteCarlo::ParticleModeType type_1;
  
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_1 ) );
  FRENSIE_CHECK_EQUAL( type_1, MonteCarlo::NEUTRON_MODE );

  MonteCarlo::ParticleModeType type_2;
  
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_2 ) );
  FRENSIE_CHECK_EQUAL( type_2, MonteCarlo::PHOTON_MODE );

  MonteCarlo::ParticleModeType type_3;
  
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_3 ) );
  FRENSIE_CHECK_EQUAL( type_3, MonteCarlo::ELECTRON_MODE );

  MonteCarlo::ParticleModeType type_4;
  
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_4 ) );
  FRENSIE_CHECK_EQUAL( type_4, MonteCarlo::NEUTRON_PHOTON_MODE );

  MonteCarlo::ParticleModeType type_5;
  
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_5 ) );
  FRENSIE_CHECK_EQUAL( type_5, MonteCarlo::PHOTON_ELECTRON_MODE );

  MonteCarlo::ParticleModeType type_6;
  
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_6 ) );
  FRENSIE_CHECK_EQUAL( type_6, MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE );

  MonteCarlo::ParticleModeType type_7;
  
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_7 ) );
  FRENSIE_CHECK_EQUAL( type_7, MonteCarlo::ADJOINT_NEUTRON_MODE );

  MonteCarlo::ParticleModeType type_8;
  
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_8 ) );
  FRENSIE_CHECK_EQUAL( type_8, MonteCarlo::ADJOINT_PHOTON_MODE );

  MonteCarlo::ParticleModeType type_9;
  
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_9 ) );
  FRENSIE_CHECK_EQUAL( type_9, MonteCarlo::ADJOINT_ELECTRON_MODE );
}

//---------------------------------------------------------------------------//
// end tstParticleState.cpp
//---------------------------------------------------------------------------//
