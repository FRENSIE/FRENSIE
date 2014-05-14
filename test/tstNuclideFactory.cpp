//---------------------------------------------------------------------------//
//!
//! \file   tstNuclideFactory.cpp
//! \author Alex Robinson
//! \brief  Nuclide factory class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>

// FACEMC Includes
#include "NuclideFactory.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//
std::string test_cross_sections_xml_directory;

Teuchos::RCP<FACEMC::NuclideFactory> nuclide_factory;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
void initializeNuclideFactory()
{
  // Assign the name of the cross_sections.xml file with path
  std::string cross_section_xml_file = test_cross_sections_xml_directory;
  cross_section_xml_file += "/cross_sections.xml";

  // Read in the xml file storing the cross section table information 
  Teuchos::ParameterList cross_section_table_info;
  Teuchos::updateParametersFromXmlFile( 
			         cross_section_xml_file,
			         Teuchos::inoutArg(cross_section_table_info) );
  
  boost::unordered_set<std::string> nuclide_aliases;
  nuclide_aliases.insert( "H-1_293.6K" );
  nuclide_aliases.insert( "H-1_300K" );
  nuclide_aliases.insert( "H-1_900K" );
  
  nuclide_factory.reset( new FACEMC::NuclideFactory( 
					     test_cross_sections_xml_directory,
					     cross_section_table_info,
					     nuclide_aliases ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a nuclide map can be created
TEUCHOS_UNIT_TEST( NuclideFactory, createNuclideMap )
{
  initializeNuclideFactory();

  boost::unordered_map<unsigned,Teuchos::RCP<FACEMC::Nuclide> > nuclide_map;

  nuclide_factory->createNuclideMap( nuclide_map );

  TEST_EQUALITY_CONST( nuclide_map.size(), 3 );
  TEST_ASSERT( nuclide_map.count( 100170 ) );
  TEST_EQUALITY_CONST( nuclide_map[100170]->getId(), 100170 );
  TEST_ASSERT( nuclide_map.count( 100171 ) );
  TEST_EQUALITY_CONST( nuclide_map[100171]->getId(), 100171 );
  TEST_ASSERT( nuclide_map.count( 100172 ) );
  TEST_EQUALITY_CONST( nuclide_map[100172]->getId(), 100172 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_cross_sections_xml_directory",
		 &test_cross_sections_xml_directory,
		 "Test cross_sections.xml file name" );
  
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );
}

//---------------------------------------------------------------------------//
// end tstNuclideFactory.cpp
//---------------------------------------------------------------------------//
