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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_IncoherentAdjointModelType.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a string can be converted to a model type
TEUCHOS_UNIT_TEST( IncoherentAdjointModelType,
                   convertStringToIncoherentAdjointModelTypeEnum )
{
  TEST_THROW( MonteCarlo::convertStringToIncoherentAdjointModelTypeEnum( "Dummy Model" ),
              std::logic_error );
  
  MonteCarlo::IncoherentAdjointModelType model =
    MonteCarlo::convertStringToIncoherentAdjointModelTypeEnum( "Klein-Nishina Adjoint Model" );

  TEST_EQUALITY_CONST( model, MonteCarlo::KN_INCOHERENT_ADJOINT_MODEL );

  model = MonteCarlo::convertStringToIncoherentAdjointModelTypeEnum( "Waller-Hartree Adjoint Model" );

  TEST_EQUALITY_CONST( model, MonteCarlo::WH_INCOHERENT_ADJOINT_MODEL );

  model = MonteCarlo::convertStringToIncoherentAdjointModelTypeEnum( "Impulse Adjoint Model" );

  TEST_EQUALITY_CONST( model, MonteCarlo::IMPULSE_INCOHERENT_ADJOINT_MODEL );

  model = MonteCarlo::convertStringToIncoherentAdjointModelTypeEnum( "Doppler Broadened Impulse Adjoint Model" );

  TEST_EQUALITY_CONST( model, MonteCarlo::DB_IMPULSE_INCOHERENT_ADJOINT_MODEL );
}

//---------------------------------------------------------------------------//
// Check that an unsigned int can be converted to a model type
TEUCHOS_UNIT_TEST( IncoherentAdjointModelType,
                   convertUnsignedToIncoherentAdjointModelTypeEnum )
{
  TEST_THROW( MonteCarlo::convertUnsignedToIncoherentAdjointModelTypeEnum( 4 ),
              std::logic_error );

  MonteCarlo::IncoherentAdjointModelType model =
    MonteCarlo::convertUnsignedToIncoherentAdjointModelTypeEnum( 0 );

  TEST_EQUALITY_CONST( model, MonteCarlo::KN_INCOHERENT_ADJOINT_MODEL );

  model = MonteCarlo::convertUnsignedToIncoherentAdjointModelTypeEnum( 1 );

  TEST_EQUALITY_CONST( model, MonteCarlo::WH_INCOHERENT_ADJOINT_MODEL );

  model = MonteCarlo::convertUnsignedToIncoherentAdjointModelTypeEnum( 2 );

  TEST_EQUALITY_CONST( model, MonteCarlo::IMPULSE_INCOHERENT_ADJOINT_MODEL );

  model = MonteCarlo::convertUnsignedToIncoherentAdjointModelTypeEnum( 3 );

  TEST_EQUALITY_CONST( model, MonteCarlo::DB_IMPULSE_INCOHERENT_ADJOINT_MODEL );
}

//---------------------------------------------------------------------------//
// Check that a model type can be converted to a string
TEUCHOS_UNIT_TEST( IncoherentAdjointModelType,
                   convertIncoherentAdjointModelTypeToString )
{
  std::string model_name =
    MonteCarlo::convertIncoherentAdjointModelTypeToString( MonteCarlo::KN_INCOHERENT_ADJOINT_MODEL );

  TEST_EQUALITY_CONST( model_name, "Klein-Nishina Adjoint Model" );

  model_name = MonteCarlo::convertIncoherentAdjointModelTypeToString( MonteCarlo::WH_INCOHERENT_ADJOINT_MODEL );

  TEST_EQUALITY_CONST( model_name, "Waller-Hartree Adjoint Model" );

  model_name = MonteCarlo::convertIncoherentAdjointModelTypeToString( MonteCarlo::IMPULSE_INCOHERENT_ADJOINT_MODEL );

  TEST_EQUALITY_CONST( model_name, "Impulse Adjoint Model" );

  model_name = MonteCarlo::convertIncoherentAdjointModelTypeToString( MonteCarlo::DB_IMPULSE_INCOHERENT_ADJOINT_MODEL );

  TEST_EQUALITY_CONST( model_name, "Doppler Broadened Impulse Adjoint Model" );
}

//---------------------------------------------------------------------------//
// Check that a model type can be placed in an ostream
TEUCHOS_UNIT_TEST( IncoherentAdjointModelType,
                   ostream_operator )
{
  std::ostringstream oss;

  oss << MonteCarlo::KN_INCOHERENT_ADJOINT_MODEL;

  TEST_EQUALITY_CONST( oss.str(), "Klein-Nishina Adjoint Model" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::WH_INCOHERENT_ADJOINT_MODEL;

  TEST_EQUALITY_CONST( oss.str(), "Waller-Hartree Adjoint Model" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::IMPULSE_INCOHERENT_ADJOINT_MODEL;

  TEST_EQUALITY_CONST( oss.str(), "Impulse Adjoint Model" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::DB_IMPULSE_INCOHERENT_ADJOINT_MODEL;

  TEST_EQUALITY_CONST( oss.str(), "Doppler Broadened Impulse Adjoint Model" );
}

//---------------------------------------------------------------------------//
// end tstIncoherentAdjointModelTypeHelpers.cpp
//---------------------------------------------------------------------------//
