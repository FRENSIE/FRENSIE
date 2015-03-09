//---------------------------------------------------------------------------//
//!
//! \file   tstCrossSectionInfoHelpers.cpp
//! \author Alex Robinson
//! \brief  Cross section info helper function unit tests
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
#include "MonteCarlo_CrossSectionInfoHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
Teuchos::RCP<Teuchos::ParameterList> cross_section_info;
std::string cross_sections_xml_directory;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that photoatom cross section info can be extracted
TEUCHOS_UNIT_TEST( CrossSectionInfoHelpers, 
		   extractInfoFromPhotoatomTableInfoParameterList )
{
  std::string data_file_path, data_file_type, data_file_table_name;
  int data_file_start_line;
  double atomic_weight;

  MonteCarlo::extractInfoFromPhotoatomTableInfoParameterList(
						  cross_sections_xml_directory,
						  "H",
						  *cross_section_info,
						  data_file_path,
						  data_file_type,
						  data_file_table_name,
						  data_file_start_line,
						  atomic_weight );

  TEST_EQUALITY( data_file_path, 
		 cross_sections_xml_directory + "/test_h_epr_ace_file.txt" );
  TEST_EQUALITY_CONST( data_file_type, "ACE" );
  TEST_EQUALITY_CONST( data_file_table_name, "1000.12p" );
  TEST_EQUALITY_CONST( data_file_start_line, 1 );
  TEST_EQUALITY_CONST( atomic_weight, 
		       0.999242*Utility::PhysicalConstants::neutron_rest_mass_amu );
}

//---------------------------------------------------------------------------//
// Check that nuclide cross section info can be extracted
TEUCHOS_UNIT_TEST( CrossSectionInfoHelpers,
		   extractInfoFromNuclideTableInfoParameterList )
{
  std::string data_file_path, data_file_type, data_file_table_name;
  int data_file_start_line;
  int atomic_number, atomic_mass_number, isomer_number;
  double atomic_weight_ratio, temperature;

  MonteCarlo::extractInfoFromNuclideTableInfoParameterList(
						  cross_sections_xml_directory,
						  "H-1_293.6K",
						  *cross_section_info,
						  data_file_path,
						  data_file_type,
						  data_file_table_name,
						  data_file_start_line,
						  atomic_number,
						  atomic_mass_number,
						  isomer_number,
						  atomic_weight_ratio,
						  temperature );

  TEST_EQUALITY( data_file_path, 
		 cross_sections_xml_directory + "/test_h1_ace_file.txt" );
  TEST_EQUALITY_CONST( data_file_type, "ACE" );
  TEST_EQUALITY_CONST( data_file_table_name, "1001.70c" );
  TEST_EQUALITY_CONST( data_file_start_line, 1 );
  TEST_EQUALITY_CONST( atomic_number, 1 );
  TEST_EQUALITY_CONST( atomic_mass_number, 1 );
  TEST_EQUALITY_CONST( isomer_number, 0 );
  TEST_EQUALITY_CONST( atomic_weight_ratio, 0.999167 );
  TEST_EQUALITY_CONST( temperature, 2.53010e-08 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();
  
  clp.setOption( "test_cross_sections_xml_directory",
		 &cross_sections_xml_directory,
		 "Test cross_section.xml file directory" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();
  
  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  std::string cross_sections_xml_file = cross_sections_xml_directory;
  cross_sections_xml_file += "/cross_sections.xml";
  
  cross_section_info = 
    Teuchos::getParametersFromXmlFile( cross_sections_xml_file );
  
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
// end tstCrossSectionInfoHelpers.cpp
//---------------------------------------------------------------------------//
