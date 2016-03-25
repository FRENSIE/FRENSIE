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
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "MonteCarlo_NuclideFactory.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//
std::string test_cross_sections_xml_directory;

Teuchos::RCP<MonteCarlo::NuclideFactory> nuclide_factory;

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
  
  std::unordered_set<std::string> nuclide_aliases;
  nuclide_aliases.insert( "H-1_293.6K" );
  nuclide_aliases.insert( "H-1_300K" );
  nuclide_aliases.insert( "H-1_900K" );
  
  nuclide_factory.reset( new MonteCarlo::NuclideFactory( 
					     test_cross_sections_xml_directory,
					     cross_section_table_info,
					     nuclide_aliases,
					     false,
					     true ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a nuclide map can be created
TEUCHOS_UNIT_TEST( NuclideFactory, createNuclideMap )
{
  std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Nuclide> > nuclide_map;

  nuclide_factory->createNuclideMap( nuclide_map );

  TEST_EQUALITY_CONST( nuclide_map.size(), 3 );
  TEST_ASSERT( nuclide_map.count( "H-1_293.6K" ) );
  TEST_ASSERT( !nuclide_map["H-1_293.6K"].is_null() );
  TEST_ASSERT( nuclide_map.count( "H-1_300K" ) );
  TEST_ASSERT( !nuclide_map["H-1_300K"].is_null() );
  TEST_ASSERT( nuclide_map.count( "H-1_900K" ) );
  TEST_ASSERT( !nuclide_map["H-1_900K"].is_null() );
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

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Initialize the nuclide factory
  initializeNuclideFactory();
  
  // Run the unit tests
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  const bool success = Teuchos::UnitTestRepository::runUnitTests(*out);

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstNuclideFactory.cpp
//---------------------------------------------------------------------------//
