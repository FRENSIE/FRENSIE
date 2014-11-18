//---------------------------------------------------------------------------//
//!
//! \file   tstPhotoatomFactory.cpp
//! \author Alex Robinson
//! \brief  Photoatom factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhotoatomFactory.hpp"
#include "MonteCarlo_AtomicRelaxationModelFactory.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::string cross_sections_xml_directory;
Teuchos::RCP<MonteCarlo::PhotoatomFactory> photoatom_factory;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a photoatom map can be created
TEUCHOS_UNIT_TEST( PhotoatomFactory, createPhotoatomMap )
{
  boost::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Photoatom> > 
    photoatom_map;

  photoatom_factory->createPhotoatomMap( photoatom_map );

  TEST_EQUALITY_CONST( photoatom_map.size(), 1 );
  TEST_ASSERT( photoatom_map.count( "H" ) );
  TEST_ASSERT( !photoatom_map["H"].is_null() );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_cross_sections_xml_directory",
		 &cross_sections_xml_directory,
		 "Test cross_sections.xml file name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  {
    std::string cross_sections_xml_file = cross_sections_xml_directory;
    cross_sections_xml_file += "/cross_sections.xml";
    
    // Read in the xml file storing the cross section table info
    Teuchos::ParameterList cross_section_table_info;
    Teuchos::updateParametersFromXmlFile(
			       cross_sections_xml_file,
			       Teuchos::inoutArg( cross_section_table_info ) );

    // Create the atomic relaxation model factory
    Teuchos::RCP<MonteCarlo::AtomicRelaxationModelFactory> 
      atomic_relaxation_model_factory(
				new MonteCarlo::AtomicRelaxationModelFactory );

    // Create the set of photoatom aliases
    boost::unordered_set<std::string> photoatom_aliases;
    photoatom_aliases.insert( "H" );
    
    // Create the photoatom factory
    photoatom_factory.reset( new MonteCarlo::PhotoatomFactory(
					   cross_sections_xml_directory,
					   cross_section_table_info,
					   photoatom_aliases,
					   atomic_relaxation_model_factory ) );
  }
  
  // Run the unit tests
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  const bool success = Teuchos::UnitTestRepository::runUnitTests( *out );

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}


//---------------------------------------------------------------------------//
// end tstPhotoatomFactory.cpp
//---------------------------------------------------------------------------//
