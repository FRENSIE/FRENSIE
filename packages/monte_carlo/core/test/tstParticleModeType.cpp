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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleModeType.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Test that a particle mode type name is valid
TEUCHOS_UNIT_TEST( ParticleModeType, isValidParticleModeTypeName )
{
  TEST_ASSERT( MonteCarlo::isValidParticleModeTypeName( "Neutron Mode" ) );
  TEST_ASSERT( MonteCarlo::isValidParticleModeTypeName( "Photon Mode" ) );
  TEST_ASSERT( MonteCarlo::isValidParticleModeTypeName( "Electron Mode" ) );
  TEST_ASSERT( MonteCarlo::isValidParticleModeTypeName( "Neutron-Photon Mode" ) );
  TEST_ASSERT( MonteCarlo::isValidParticleModeTypeName( "Neutron-Photon-Electron Mode" ) );
  TEST_ASSERT( MonteCarlo::isValidParticleModeTypeName( "Photon-Electron Mode" ) );
  TEST_ASSERT( MonteCarlo::isValidParticleModeTypeName( "Adjoint Neutron Mode" ) );
  TEST_ASSERT( MonteCarlo::isValidParticleModeTypeName( "Adjoint Photon Mode" ) );
  TEST_ASSERT( MonteCarlo::isValidParticleModeTypeName( "Adjoint Electron Mode" ) );
}

//---------------------------------------------------------------------------//
// Test that a particle mode type name can be converted to an enum
TEUCHOS_UNIT_TEST( ParticleModeType,
                   convertParticleModeTypeNameToParticleModeTypeEnum )
{
  MonteCarlo::ParticleModeType mode =
    MonteCarlo::convertParticleModeTypeNameToParticleModeTypeEnum( "Neutron Mode" );

  TEST_EQUALITY_CONST( mode, MonteCarlo::NEUTRON_MODE );

  mode = MonteCarlo::convertParticleModeTypeNameToParticleModeTypeEnum( "Photon Mode" );

  TEST_EQUALITY_CONST( mode, MonteCarlo::PHOTON_MODE );

  mode = MonteCarlo::convertParticleModeTypeNameToParticleModeTypeEnum( "Electron Mode" );

  TEST_EQUALITY_CONST( mode, MonteCarlo::ELECTRON_MODE );

  mode = MonteCarlo::convertParticleModeTypeNameToParticleModeTypeEnum( "Neutron-Photon Mode" );

  TEST_EQUALITY_CONST( mode, MonteCarlo::NEUTRON_PHOTON_MODE );

  mode = MonteCarlo::convertParticleModeTypeNameToParticleModeTypeEnum( "Neutron-Photon-Electron Mode" );

  TEST_EQUALITY_CONST( mode, MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE );

  mode = MonteCarlo::convertParticleModeTypeNameToParticleModeTypeEnum( "Photon-Electron Mode" );

  TEST_EQUALITY_CONST( mode, MonteCarlo::PHOTON_ELECTRON_MODE );

  mode = MonteCarlo::convertParticleModeTypeNameToParticleModeTypeEnum( "Adjoint Neutron Mode" );

  TEST_EQUALITY_CONST( mode, MonteCarlo::ADJOINT_NEUTRON_MODE );

  mode = MonteCarlo::convertParticleModeTypeNameToParticleModeTypeEnum( "Adjoint Photon Mode" );

  TEST_EQUALITY_CONST( mode, MonteCarlo::ADJOINT_PHOTON_MODE );

  mode = MonteCarlo::convertParticleModeTypeNameToParticleModeTypeEnum( "Adjoint Electron Mode" );

  TEST_EQUALITY_CONST( mode, MonteCarlo::ADJOINT_ELECTRON_MODE );
}

//---------------------------------------------------------------------------//
// Test that an unsigned int can be converted to an enum
TEUCHOS_UNIT_TEST( ParticleModeType, convertUnsignedToParticleModeTypeEnum )
{
  MonteCarlo::ParticleModeType mode =
    MonteCarlo::convertUnsignedToParticleModeTypeEnum( 0 );

  TEST_EQUALITY_CONST( mode, MonteCarlo::NEUTRON_MODE );

  mode = MonteCarlo::convertUnsignedToParticleModeTypeEnum( 1 );

  TEST_EQUALITY_CONST( mode, MonteCarlo::PHOTON_MODE );

  mode = MonteCarlo::convertUnsignedToParticleModeTypeEnum( 2 );

  TEST_EQUALITY_CONST( mode, MonteCarlo::ELECTRON_MODE );

  mode = MonteCarlo::convertUnsignedToParticleModeTypeEnum( 3 );

  TEST_EQUALITY_CONST( mode, MonteCarlo::NEUTRON_PHOTON_MODE );

  mode = MonteCarlo::convertUnsignedToParticleModeTypeEnum( 4 );

  TEST_EQUALITY_CONST( mode, MonteCarlo::PHOTON_ELECTRON_MODE );

  mode = MonteCarlo::convertUnsignedToParticleModeTypeEnum( 5 );

  TEST_EQUALITY_CONST( mode, MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE );

  mode = MonteCarlo::convertUnsignedToParticleModeTypeEnum( 6 );

  TEST_EQUALITY_CONST( mode, MonteCarlo::ADJOINT_NEUTRON_MODE );

  mode = MonteCarlo::convertUnsignedToParticleModeTypeEnum( 7 );

  TEST_EQUALITY_CONST( mode, MonteCarlo::ADJOINT_PHOTON_MODE );

  mode = MonteCarlo::convertUnsignedToParticleModeTypeEnum( 8 );

  TEST_EQUALITY_CONST( mode, MonteCarlo::ADJOINT_ELECTRON_MODE );
}

//---------------------------------------------------------------------------//
// Test that an enum can be converted to a string
TEUCHOS_UNIT_TEST( ParticleModeType, convertParticleModeTypeEnumToString )
{
  std::string mode =
    MonteCarlo::convertParticleModeTypeEnumToString( MonteCarlo::NEUTRON_MODE );
  
  TEST_EQUALITY_CONST( mode, "Neutron Mode" );

  mode = MonteCarlo::convertParticleModeTypeEnumToString( MonteCarlo::PHOTON_MODE );

  TEST_EQUALITY_CONST( mode, "Photon Mode" );

  mode = MonteCarlo::convertParticleModeTypeEnumToString( MonteCarlo::ELECTRON_MODE );

  TEST_EQUALITY_CONST( mode, "Electron Mode" );

  mode = MonteCarlo::convertParticleModeTypeEnumToString( MonteCarlo::NEUTRON_PHOTON_MODE );

  TEST_EQUALITY_CONST( mode, "Neutron-Photon Mode" );

  mode = MonteCarlo::convertParticleModeTypeEnumToString( MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE );

  TEST_EQUALITY_CONST( mode, "Neutron-Photon-Electron Mode" );

  mode = MonteCarlo::convertParticleModeTypeEnumToString( MonteCarlo::PHOTON_ELECTRON_MODE );

  TEST_EQUALITY_CONST( mode, "Photon-Electron Mode" );

  mode = MonteCarlo::convertParticleModeTypeEnumToString( MonteCarlo::ADJOINT_NEUTRON_MODE );
  
  TEST_EQUALITY_CONST( mode, "Adjoint Neutron Mode" );

  mode = MonteCarlo::convertParticleModeTypeEnumToString( MonteCarlo::ADJOINT_PHOTON_MODE );

  TEST_EQUALITY_CONST( mode, "Adjoint Photon Mode" );

  mode = MonteCarlo::convertParticleModeTypeEnumToString( MonteCarlo::ADJOINT_ELECTRON_MODE );

  TEST_EQUALITY_CONST( mode, "Adjoint Electron Mode" );
}

//---------------------------------------------------------------------------//
// Test that an enum can be placed in a stream
TEUCHOS_UNIT_TEST( ParticleModeType, stream_operator )
{
  std::ostringstream oss;
  oss << MonteCarlo::NEUTRON_MODE;

  TEST_EQUALITY_CONST( oss.str(), "Neutron Mode" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::PHOTON_MODE;

  TEST_EQUALITY_CONST( oss.str(), "Photon Mode" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::ELECTRON_MODE;

  TEST_EQUALITY_CONST( oss.str(), "Electron Mode" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::NEUTRON_PHOTON_MODE;

  TEST_EQUALITY_CONST( oss.str(), "Neutron-Photon Mode" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE;

  TEST_EQUALITY_CONST( oss.str(), "Neutron-Photon-Electron Mode" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::PHOTON_ELECTRON_MODE;

  TEST_EQUALITY_CONST( oss.str(), "Photon-Electron Mode" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::ADJOINT_NEUTRON_MODE;

  TEST_EQUALITY_CONST( oss.str(), "Adjoint Neutron Mode" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::ADJOINT_PHOTON_MODE;

  TEST_EQUALITY_CONST( oss.str(), "Adjoint Photon Mode" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::ADJOINT_ELECTRON_MODE;

  TEST_EQUALITY_CONST( oss.str(), "Adjoint Electron Mode" );

  oss.str( "" );
  oss.clear();
}

//---------------------------------------------------------------------------//
// end tstParticleState.cpp
//---------------------------------------------------------------------------//
