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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleType.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Test that particle type names are valid
TEUCHOS_UNIT_TEST( ParticleType, isValidParticleTypeName )
{
  TEST_ASSERT( MonteCarlo::isValidParticleTypeName( "Neutron" ) );
  TEST_ASSERT( MonteCarlo::isValidParticleTypeName( "Photon" ) );
  TEST_ASSERT( MonteCarlo::isValidParticleTypeName( "Electron" ) );
  TEST_ASSERT( MonteCarlo::isValidParticleTypeName( "Adjoint Neutron" ) );
  TEST_ASSERT( MonteCarlo::isValidParticleTypeName( "Adjoint Photon" ) );
  TEST_ASSERT( MonteCarlo::isValidParticleTypeName( "Adjoint Electron" ) );
}

//---------------------------------------------------------------------------//
// Check that a particle type name can be converted to an enum
TEUCHOS_UNIT_TEST( ParticleType, convertParticleTypeNameToParticleTypeEnum )
{
  MonteCarlo::ParticleType type =
    MonteCarlo::convertParticleTypeNameToParticleTypeEnum( "Neutron" );

  TEST_EQUALITY_CONST( type, MonteCarlo::NEUTRON );

  type = MonteCarlo::convertParticleTypeNameToParticleTypeEnum( "Photon" );

  TEST_EQUALITY_CONST( type, MonteCarlo::PHOTON );

  type = MonteCarlo::convertParticleTypeNameToParticleTypeEnum( "Electron" );

  TEST_EQUALITY_CONST( type, MonteCarlo::ELECTRON );

  type = MonteCarlo::convertParticleTypeNameToParticleTypeEnum( "Adjoint Neutron" );

  TEST_EQUALITY_CONST( type, MonteCarlo::ADJOINT_NEUTRON );

  type = MonteCarlo::convertParticleTypeNameToParticleTypeEnum( "Adjoint Photon" );

  TEST_EQUALITY_CONST( type, MonteCarlo::ADJOINT_PHOTON );

  type = MonteCarlo::convertParticleTypeNameToParticleTypeEnum( "Adjoint Electron" );

  TEST_EQUALITY_CONST( type, MonteCarlo::ADJOINT_ELECTRON );
}

//---------------------------------------------------------------------------//
// Check that a geometry particle type can be converted to an enum
TEUCHOS_UNIT_TEST( ParticleType,
                   convertGeometryParticleTypeEnumToParticleTypeEnum )
{
  MonteCarlo::ParticleType type =
    MonteCarlo::convertGeometryParticleTypeEnumToParticleTypeEnum( Geometry::NEUTRON );

  TEST_EQUALITY_CONST( type, MonteCarlo::NEUTRON );

  type = MonteCarlo::convertGeometryParticleTypeEnumToParticleTypeEnum( Geometry::PHOTON );

  TEST_EQUALITY_CONST( type, MonteCarlo::PHOTON );

  type = MonteCarlo::convertGeometryParticleTypeEnumToParticleTypeEnum( Geometry::ELECTRON );

  TEST_EQUALITY_CONST( type, MonteCarlo::ELECTRON );

  type = MonteCarlo::convertGeometryParticleTypeEnumToParticleTypeEnum( Geometry::ADJOINT_NEUTRON );

  TEST_EQUALITY_CONST( type, MonteCarlo::ADJOINT_NEUTRON );

  type = MonteCarlo::convertGeometryParticleTypeEnumToParticleTypeEnum( Geometry::ADJOINT_PHOTON );

  TEST_EQUALITY_CONST( type, MonteCarlo::ADJOINT_PHOTON );

  type = MonteCarlo::convertGeometryParticleTypeEnumToParticleTypeEnum( Geometry::ADJOINT_ELECTRON );

  TEST_EQUALITY_CONST( type, MonteCarlo::ADJOINT_ELECTRON );
}

//---------------------------------------------------------------------------//
// Check that a particle type enum can be converted to a string
TEUCHOS_UNIT_TEST( ParticleType, convertParticleTypeEnumToString )
{
  std::string type = MonteCarlo::convertParticleTypeEnumToString( MonteCarlo::NEUTRON );

  TEST_EQUALITY_CONST( type, "Neutron" );

  type = MonteCarlo::convertParticleTypeEnumToString( MonteCarlo::PHOTON );

  TEST_EQUALITY_CONST( type, "Photon" );

  type = MonteCarlo::convertParticleTypeEnumToString( MonteCarlo::ELECTRON );

  TEST_EQUALITY_CONST( type, "Electron" );

  type = MonteCarlo::convertParticleTypeEnumToString( MonteCarlo::ADJOINT_NEUTRON );

  TEST_EQUALITY_CONST( type, "Adjoint Neutron" );

  type = MonteCarlo::convertParticleTypeEnumToString( MonteCarlo::ADJOINT_PHOTON );

  TEST_EQUALITY_CONST( type, "Adjoint Photon" );

  type = MonteCarlo::convertParticleTypeEnumToString( MonteCarlo::ADJOINT_ELECTRON );

  TEST_EQUALITY_CONST( type, "Adjoint Electron" );
}

//---------------------------------------------------------------------------//
// Check that a particle type enum can be placed in a stream
TEUCHOS_UNIT_TEST( ParticleTYpe, stream_operator )
{
  std::ostringstream oss;
  oss << MonteCarlo::NEUTRON;

  TEST_EQUALITY_CONST( oss.str(), "Neutron" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::PHOTON;

  TEST_EQUALITY_CONST( oss.str(), "Photon" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::ELECTRON;

  TEST_EQUALITY_CONST( oss.str(), "Electron" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::ADJOINT_NEUTRON;

  TEST_EQUALITY_CONST( oss.str(), "Adjoint Neutron" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::ADJOINT_PHOTON;

  TEST_EQUALITY_CONST( oss.str(), "Adjoint Photon" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::ADJOINT_ELECTRON;

  TEST_EQUALITY_CONST( oss.str(), "Adjoint Electron" );
}

//---------------------------------------------------------------------------//
// end tstParticleType.cpp
//---------------------------------------------------------------------------//
