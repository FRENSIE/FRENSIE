//---------------------------------------------------------------------------//
//!
//! \file   tstParticleType.cpp
//! \author Alex Robinson
//! \brief  Particle type enum helper function unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// FRENSIE Includes
#include "MonteCarlo_ParticleType.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a geometry particle type can be converted to an enum
FRENSIE_UNIT_TEST( ParticleType,
                   convertGeometryParticleTypeEnumToParticleTypeEnum )
{
  MonteCarlo::ParticleType type =
    MonteCarlo::convertGeometryParticleTypeEnumToParticleTypeEnum( Geometry::NEUTRON );

  FRENSIE_CHECK_EQUAL( type, MonteCarlo::NEUTRON );

  type = MonteCarlo::convertGeometryParticleTypeEnumToParticleTypeEnum( Geometry::PHOTON );

  FRENSIE_CHECK_EQUAL( type, MonteCarlo::PHOTON );

  type = MonteCarlo::convertGeometryParticleTypeEnumToParticleTypeEnum( Geometry::ELECTRON );

  FRENSIE_CHECK_EQUAL( type, MonteCarlo::ELECTRON );

  type = MonteCarlo::convertGeometryParticleTypeEnumToParticleTypeEnum( Geometry::POSITRON );

  FRENSIE_CHECK_EQUAL( type, MonteCarlo::POSITRON );

  type = MonteCarlo::convertGeometryParticleTypeEnumToParticleTypeEnum( Geometry::ADJOINT_NEUTRON );

  FRENSIE_CHECK_EQUAL( type, MonteCarlo::ADJOINT_NEUTRON );

  type = MonteCarlo::convertGeometryParticleTypeEnumToParticleTypeEnum( Geometry::ADJOINT_PHOTON );

  FRENSIE_CHECK_EQUAL( type, MonteCarlo::ADJOINT_PHOTON );

  type = MonteCarlo::convertGeometryParticleTypeEnumToParticleTypeEnum( Geometry::ADJOINT_ELECTRON );

  FRENSIE_CHECK_EQUAL( type, MonteCarlo::ADJOINT_ELECTRON );

  type = MonteCarlo::convertGeometryParticleTypeEnumToParticleTypeEnum( Geometry::ADJOINT_POSITRON );

  FRENSIE_CHECK_EQUAL( type, MonteCarlo::ADJOINT_POSITRON );
}

//---------------------------------------------------------------------------//
// Check that a short particle type name can be convert to a particle type enum
FRENSIE_UNIT_TEST( ParticleType,
                   convertShortParticleTypeNameToParticleTypeEnum )
{
  MonteCarlo::ParticleType type =
    MonteCarlo::convertShortParticleTypeNameToParticleTypeEnum( "n" );

  FRENSIE_CHECK_EQUAL( type, MonteCarlo::NEUTRON );

  type = MonteCarlo::convertShortParticleTypeNameToParticleTypeEnum( "p" );

  FRENSIE_CHECK_EQUAL( type, MonteCarlo::PHOTON );

  type = MonteCarlo::convertShortParticleTypeNameToParticleTypeEnum( "e" );

  FRENSIE_CHECK_EQUAL( type, MonteCarlo::ELECTRON );

  type = MonteCarlo::convertShortParticleTypeNameToParticleTypeEnum( "e+" );

  FRENSIE_CHECK_EQUAL( type, MonteCarlo::POSITRON );

  type = MonteCarlo::convertShortParticleTypeNameToParticleTypeEnum( "an" );

  FRENSIE_CHECK_EQUAL( type, MonteCarlo::ADJOINT_NEUTRON );

  type = MonteCarlo::convertShortParticleTypeNameToParticleTypeEnum( "ap" );

  FRENSIE_CHECK_EQUAL( type, MonteCarlo::ADJOINT_PHOTON );

  type = MonteCarlo::convertShortParticleTypeNameToParticleTypeEnum( "ae" );

  FRENSIE_CHECK_EQUAL( type, MonteCarlo::ADJOINT_ELECTRON );

  type = MonteCarlo::convertShortParticleTypeNameToParticleTypeEnum( "ae+" );

  FRENSIE_CHECK_EQUAL( type, MonteCarlo::ADJOINT_POSITRON );
}

//---------------------------------------------------------------------------//
// Check that an int can be converted to a particle type enum
FRENSIE_UNIT_TEST( ParticleType, convertIntToParticleType )
{
  MonteCarlo::ParticleType type = MonteCarlo::convertIntToParticleType( 0 );

  FRENSIE_CHECK_EQUAL( type, MonteCarlo::PHOTON );

  type = MonteCarlo::convertIntToParticleType( 1 );

  FRENSIE_CHECK_EQUAL( type, MonteCarlo::NEUTRON );

  type = MonteCarlo::convertIntToParticleType( 2 );

  FRENSIE_CHECK_EQUAL( type, MonteCarlo::ELECTRON );

  type = MonteCarlo::convertIntToParticleType( 3 );

  FRENSIE_CHECK_EQUAL( type, MonteCarlo::POSITRON );

  type = MonteCarlo::convertIntToParticleType( 4 );

  FRENSIE_CHECK_EQUAL( type, MonteCarlo::ADJOINT_PHOTON );

  type = MonteCarlo::convertIntToParticleType( 5 );

  FRENSIE_CHECK_EQUAL( type, MonteCarlo::ADJOINT_NEUTRON );

  type = MonteCarlo::convertIntToParticleType( 6 );

  FRENSIE_CHECK_EQUAL( type, MonteCarlo::ADJOINT_ELECTRON );

  type = MonteCarlo::convertIntToParticleType( 7 );

  FRENSIE_CHECK_EQUAL( type, MonteCarlo::ADJOINT_POSITRON );
}

//---------------------------------------------------------------------------//
// Check that a particle type enum can be converted to a string
FRENSIE_UNIT_TEST( ParticleType, toString )
{
  std::string type = Utility::toString( MonteCarlo::NEUTRON );

  FRENSIE_CHECK_EQUAL( type, "Neutron" );

  type = Utility::toString( MonteCarlo::PHOTON );

  FRENSIE_CHECK_EQUAL( type, "Photon" );

  type = Utility::toString( MonteCarlo::ELECTRON );

  FRENSIE_CHECK_EQUAL( type, "Electron" );

  type = Utility::toString( MonteCarlo::ADJOINT_NEUTRON );

  FRENSIE_CHECK_EQUAL( type, "Adjoint Neutron" );

  type = Utility::toString( MonteCarlo::ADJOINT_PHOTON );

  FRENSIE_CHECK_EQUAL( type, "Adjoint Photon" );

  type = Utility::toString( MonteCarlo::ADJOINT_ELECTRON );

  FRENSIE_CHECK_EQUAL( type, "Adjoint Electron" );
}

//---------------------------------------------------------------------------//
// Check that a particle type enum can be placed in a stream
FRENSIE_UNIT_TEST( ParticleTYpe, stream_operator )
{
  std::ostringstream oss;
  oss << MonteCarlo::NEUTRON;

  FRENSIE_CHECK_EQUAL( oss.str(), "Neutron" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::PHOTON;

  FRENSIE_CHECK_EQUAL( oss.str(), "Photon" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::ELECTRON;

  FRENSIE_CHECK_EQUAL( oss.str(), "Electron" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::ADJOINT_NEUTRON;

  FRENSIE_CHECK_EQUAL( oss.str(), "Adjoint Neutron" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::ADJOINT_PHOTON;

  FRENSIE_CHECK_EQUAL( oss.str(), "Adjoint Photon" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::ADJOINT_ELECTRON;

  FRENSIE_CHECK_EQUAL( oss.str(), "Adjoint Electron" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::ADJOINT_POSITRON;

  FRENSIE_CHECK_EQUAL( oss.str(), "Adjoint Positron" );
}

//---------------------------------------------------------------------------//
// Check that a ParticleType can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( ParticleType, archive, TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_particle_type" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    MonteCarlo::ParticleType type_1 = MonteCarlo::PHOTON;
    MonteCarlo::ParticleType type_2 = MonteCarlo::NEUTRON;
    MonteCarlo::ParticleType type_3 = MonteCarlo::ELECTRON;
    MonteCarlo::ParticleType type_4 = MonteCarlo::POSITRON;
    MonteCarlo::ParticleType type_5 = MonteCarlo::ADJOINT_PHOTON;
    MonteCarlo::ParticleType type_6 = MonteCarlo::ADJOINT_NEUTRON;
    MonteCarlo::ParticleType type_7 = MonteCarlo::ADJOINT_ELECTRON;
    MonteCarlo::ParticleType type_8 = MonteCarlo::ADJOINT_POSITRON;

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

  MonteCarlo::ParticleType type_1;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_1 ) );
  FRENSIE_CHECK_EQUAL( type_1, MonteCarlo::PHOTON );

  MonteCarlo::ParticleType type_2;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_2 ) );
  FRENSIE_CHECK_EQUAL( type_2, MonteCarlo::NEUTRON );

  MonteCarlo::ParticleType type_3;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_3 ) );
  FRENSIE_CHECK_EQUAL( type_3, MonteCarlo::ELECTRON );

  MonteCarlo::ParticleType type_4;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_4 ) );
  FRENSIE_CHECK_EQUAL( type_4, MonteCarlo::POSITRON );

  MonteCarlo::ParticleType type_5;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_5 ) );
  FRENSIE_CHECK_EQUAL( type_5, MonteCarlo::ADJOINT_PHOTON );

  MonteCarlo::ParticleType type_6;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_6 ) );
  FRENSIE_CHECK_EQUAL( type_6, MonteCarlo::ADJOINT_NEUTRON );

  MonteCarlo::ParticleType type_7;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_7 ) );
  FRENSIE_CHECK_EQUAL( type_7, MonteCarlo::ADJOINT_ELECTRON );

  MonteCarlo::ParticleType type_8;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_8 ) );
  FRENSIE_CHECK_EQUAL( type_8, MonteCarlo::ADJOINT_POSITRON );
}

//---------------------------------------------------------------------------//
// end tstParticleType.cpp
//---------------------------------------------------------------------------//
