//---------------------------------------------------------------------------//
//!
//! \file   tstRootModelProperties.cpp
//! \author Alex Robinson
//! \brief  Root model properties class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <algorithm>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Tuple.hpp>

// FRENSIE Includes
#include "Geometry_RootModelProperties.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the default properties are correct
TEUCHOS_UNIT_TEST( RootModelProperties, default_properties )
{
  const Geometry::RootModelProperties default_properties( "dummy.c" );

  TEST_EQUALITY_CONST( default_properties.getMaterialPropertyName(), "mat" );
  TEST_EQUALITY_CONST( default_properties.getVoidMaterialName(), "void" );
  TEST_EQUALITY_CONST( default_properties.getTerminalMaterialName(), "graveyard" );
}

//---------------------------------------------------------------------------//
// Check that the file name can be returned
TEUCHOS_UNIT_TEST( RootModelProperties, getModelFileName )
{
  const Geometry::RootModelProperties properties( "dummy.c" );

  TEST_EQUALITY_CONST( properties.getModelFileName(), "dummy.c" );
}

//---------------------------------------------------------------------------//
// Check that the material property name can be set
TEUCHOS_UNIT_TEST( RootModelProperties, setMaterialPropertyName )
{
  Geometry::RootModelProperties properties( "dummy.c" );
  properties.setMaterialPropertyName( "fill" );

  TEST_EQUALITY_CONST( properties.getMaterialPropertyName(), "fill" );
}

//---------------------------------------------------------------------------//
// Check that the void material name can be set
TEUCHOS_UNIT_TEST( RootModelProperties, setVoidMaterialName )
{
  Geometry::RootModelProperties properties( "dummy.c" );
  properties.setVoidMaterialName( "empty" );

  TEST_EQUALITY_CONST( properties.getVoidMaterialName(), "empty" );
}

//---------------------------------------------------------------------------//
// Check that the terminal material name can be set
TEUCHOS_UNIT_TEST( RootModelProperties, setTerminalMaterialName )
{
  Geometry::RootModelProperties properties( "dummy.c" );
  properties.setTerminalMaterialName( "blackhole" );

  TEST_EQUALITY_CONST( properties.getTerminalMaterialName(), "blackhole" );
}

//---------------------------------------------------------------------------//
// end tstRootModelProperties.cpp
//---------------------------------------------------------------------------//
