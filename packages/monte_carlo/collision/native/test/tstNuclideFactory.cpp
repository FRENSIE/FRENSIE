//---------------------------------------------------------------------------//
//!
//! \file   tstNuclideFactory.cpp
//! \author Alex Robinson
//! \brief  Nuclide factory class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "MonteCarlo_NuclideFactory.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//
std::string test_cross_sections_xml_directory;

Teuchos::ParameterList cross_section_table_info;

std::shared_ptr<const MonteCarlo::SimulationProperties> properties;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a factory can be constructed
TEUCHOS_UNIT_TEST( NuclideFactory, constructor )
{
  std::unordered_set<std::string> nuclide_aliases;
  nuclide_aliases.insert( "H-1_293.6K" );
  nuclide_aliases.insert( "H-1_300K" );
  nuclide_aliases.insert( "H-1_900K" );

  std::shared_ptr<MonteCarlo::NuclideFactory> factory;

  TEST_NOTHROW( factory.reset( new MonteCarlo::NuclideFactory(
                                             test_cross_sections_xml_directory,
                                             cross_section_table_info,
                                             nuclide_aliases,
                                             *properties ) ) );
}

//---------------------------------------------------------------------------//
// Check that a nuclide map can be created
TEUCHOS_UNIT_TEST( NuclideFactory, createNuclideMap )
{
  std::unordered_set<std::string> nuclide_aliases;
  nuclide_aliases.insert( "H-1_293.6K" );
  nuclide_aliases.insert( "H-1_300K" );
  nuclide_aliases.insert( "H-1_900K" );

  std::shared_ptr<MonteCarlo::NuclideFactory> factory(
                                      new MonteCarlo::NuclideFactory(
                                             test_cross_sections_xml_directory,
                                             cross_section_table_info,
                                             nuclide_aliases,
                                             *properties ) );
  
  std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Nuclide> > nuclide_map;

  factory->createNuclideMap( nuclide_map );

  TEST_EQUALITY_CONST( nuclide_map.size(), 3 );
  TEST_ASSERT( nuclide_map.count( "H-1_293.6K" ) );
  TEST_ASSERT( !nuclide_map["H-1_293.6K"].is_null() );
  TEST_ASSERT( nuclide_map.count( "H-1_300K" ) );
  TEST_ASSERT( !nuclide_map["H-1_300K"].is_null() );
  TEST_ASSERT( nuclide_map.count( "H-1_900K" ) );
  TEST_ASSERT( !nuclide_map["H-1_900K"].is_null() );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_cross_sections_xml_directory",
                   &test_cross_sections_xml_directory,
                   "Test cross_sections.xml file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Assign the name of the cross_sections.xml file with path
  std::string cross_section_xml_file = test_cross_sections_xml_directory;
  cross_section_xml_file += "/cross_sections.xml";

  // Read in the xml file storing the cross section table information
  Teuchos::updateParametersFromXmlFile(
			         cross_section_xml_file,
			         Teuchos::inoutArg(cross_section_table_info) );

  // Create the simulation properties
  properties.reset( new MonteCarlo::SimulationProperties );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstNuclideFactory.cpp
//---------------------------------------------------------------------------//
