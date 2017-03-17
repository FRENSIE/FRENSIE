//---------------------------------------------------------------------------//
//!
//! \file   tstRootModelPropertiesFactory.cpp
//! \author Alex Robinson
//! \brief  Root model properties factory class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Geometry_RootModelPropertiesFactory.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
Teuchos::RCP<const Teuchos::ParameterList> basic_model_raw_properties;
Teuchos::RCP<const Teuchos::ParameterList> advanced_model_raw_properties;

//---------------------------------------------------------------------------//
// Check that the basic properties file can be parsed
TEUCHOS_UNIT_TEST( RootModelPropertiesFactory, createProperties_basic )
{
  std::shared_ptr<const Geometry::RootModelProperties> properties;

  TEST_NOTHROW( properties = Geometry::RootModelPropertiesFactory::createProperties( *basic_model_raw_properties ) );
  TEST_ASSERT( properties->getModelFileName().find( "basic_root_geometry.root" ) < properties->getModelFileName().size() );
  TEST_EQUALITY_CONST( properties->getMaterialPropertyName(), "mat" );
  TEST_EQUALITY_CONST( properties->getVoidMaterialName(), "void" );
  TEST_EQUALITY_CONST( properties->getTerminalMaterialName(), "graveyard" );
}

//---------------------------------------------------------------------------//
// Check that the advanced properties file can be parsed
TEUCHOS_UNIT_TEST( RootModelPropertiesFactory, createProperties_advanced )
{
  std::shared_ptr<const Geometry::RootModelProperties> properties;

  TEST_NOTHROW( properties = Geometry::RootModelPropertiesFactory::createProperties( *advanced_model_raw_properties ) );
  TEST_ASSERT( properties->getModelFileName().find( "advanced_root_geometry.root" ) < properties->getModelFileName().size() );
  TEST_EQUALITY_CONST( properties->getMaterialPropertyName(), "material" );
  TEST_EQUALITY_CONST( properties->getVoidMaterialName(), "empty" );
  TEST_EQUALITY_CONST( properties->getTerminalMaterialName(), "killzone" );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string basic_xml_file_name, advanced_xml_file_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_basic_xml_file",
                   &basic_xml_file_name,
                   "Basic model properties xml file name" );
  clp().setOption( "test_advanced_xml_file",
                   &advanced_xml_file_name,
                   "Advanced model properties xml file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Load the model properties files
  basic_model_raw_properties =
    Teuchos::getParametersFromXmlFile( basic_xml_file_name );

  advanced_model_raw_properties =
    Teuchos::getParametersFromXmlFile( advanced_xml_file_name );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstRootModelPropertiesFactory.cpp
//---------------------------------------------------------------------------//
