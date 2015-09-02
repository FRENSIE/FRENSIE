//---------------------------------------------------------------------------//
//!
//! \file   tstXsdir.cpp
//! \author Alex Robinson
//! \brief  Xsdir entry unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "DataGen_Xsdir.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::string xsdir_file_name;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the xsdir file can be exported
TEUCHOS_UNIT_TEST( XsdirEntry, exportInfo )
{
  // Construct the xsdir object from the xsdir file
  DataGen::Xsdir xsdir( xsdir_file_name );

  Teuchos::ParameterList cross_sections( "Cross Sections Directory" );

  xsdir.exportInfo( cross_sections );

  TEST_EQUALITY_CONST( cross_sections.numParams(), 29 );
  TEST_ASSERT( cross_sections.isSublist( "H-1_900.0K_v8" ) );
  TEST_ASSERT( cross_sections.isSublist( "H-1_600.0K_v8" ) );
  TEST_ASSERT( cross_sections.isSublist( "H-1_293.6K_v8" ) );
  TEST_ASSERT( cross_sections.isSublist( "H-1_900.0K_v7" ) );
  TEST_ASSERT( cross_sections.isSublist( "H-1_600.0K_v7" ) );
  TEST_ASSERT( cross_sections.isSublist( "H-1_293.6K_v7" ) );
  TEST_ASSERT( cross_sections.isSublist( "H-2_900.0K_v8" ) );
  TEST_ASSERT( cross_sections.isSublist( "H-2_600.0K_v8" ) );
  TEST_ASSERT( cross_sections.isSublist( "H-2_293.6K_v8" ) );
  TEST_ASSERT( cross_sections.isSublist( "H-2_900.0K_v7" ) );
  TEST_ASSERT( cross_sections.isSublist( "H-2_600.0K_v7" ) );
  TEST_ASSERT( cross_sections.isSublist( "H-2_293.6K_v7" ) );
  TEST_ASSERT( cross_sections.isSublist( "He-3_900.0K_v8" ) );
  TEST_ASSERT( cross_sections.isSublist( "He-3_600.0K_v8" ) );
  TEST_ASSERT( cross_sections.isSublist( "He-3_293.6K_v8" ) );
  TEST_ASSERT( cross_sections.isSublist( "He-3_900.0K_v7" ) );
  TEST_ASSERT( cross_sections.isSublist( "He-3_600.0K_v7" ) );
  TEST_ASSERT( cross_sections.isSublist( "He-3_293.6K_v7" ) );
  TEST_ASSERT( cross_sections.isSublist( "He-4_900.0K_v8" ) );
  TEST_ASSERT( cross_sections.isSublist( "He-4_600.0K_v8" ) );
  TEST_ASSERT( cross_sections.isSublist( "He-4_293.6K_v8" ) );
  TEST_ASSERT( cross_sections.isSublist( "He-4_900.0K_v7" ) );
  TEST_ASSERT( cross_sections.isSublist( "He-4_600.0K_v7" ) );
  TEST_ASSERT( cross_sections.isSublist( "He-4_293.6K_v7" ) );
  TEST_ASSERT( cross_sections.isSublist( "be_293.6K_v2" ) );
  TEST_ASSERT( cross_sections.isSublist( "be_400.0K_v2" ) );
  TEST_ASSERT( cross_sections.isSublist( "H" ) );
  TEST_ASSERT( cross_sections.isSublist( "He" ) );
  TEST_ASSERT( cross_sections.isSublist( "Miscellaneous" ) );

  Teuchos::ParameterList& misc_list = 
    cross_sections.sublist( "Miscellaneous" );
  
  TEST_EQUALITY_CONST( misc_list.numParams(), 4 );
  TEST_ASSERT( misc_list.isSublist( "H-2_v7" ) );
  TEST_ASSERT( misc_list.isSublist( "H-2_v2" ) );
  TEST_ASSERT( misc_list.isSublist( "C-12_v7" ) );
  TEST_ASSERT( misc_list.isSublist( "C-12_v2" ) );
		       
  Teuchos::ParameterList& h2_list = 
    cross_sections.sublist( "H-2_900.0K_v8" );

  TEST_EQUALITY_CONST( h2_list.numParams(), 21 );

  h2_list = cross_sections.sublist( "H-2_600.0K_v8" );

  TEST_EQUALITY_CONST( h2_list.numParams(), 21 );

  h2_list = cross_sections.sublist( "H-2_293.6K_v8" );

  TEST_EQUALITY_CONST( h2_list.numParams(), 21 );
  
  h2_list = cross_sections.sublist( "H-2_900.0K_v7" );

  TEST_EQUALITY_CONST( h2_list.numParams(), 21 );

  h2_list = cross_sections.sublist( "H-2_600.0K_v7" );

  TEST_EQUALITY_CONST( h2_list.numParams(), 21 );

  h2_list = cross_sections.sublist( "H-2_293.6K_v7" );

  TEST_EQUALITY_CONST( h2_list.numParams(), 21 );

  Teuchos::ParameterList& other_list = 
    cross_sections.sublist( "H-1_900.0K_v8" );

  TEST_EQUALITY_CONST( other_list.numParams(), 17 );
  
  other_list = cross_sections.sublist( "H-1_600.0K_v8" );

  TEST_EQUALITY_CONST( other_list.numParams(), 17 );

  other_list = cross_sections.sublist( "H-1_293.6K_v8" );

  TEST_EQUALITY_CONST( other_list.numParams(), 17 );

  other_list = cross_sections.sublist( "H-1_900.0K_v7" );

  TEST_EQUALITY_CONST( other_list.numParams(), 17 );

  other_list = cross_sections.sublist( "H-1_600.0K_v7" );

  TEST_EQUALITY_CONST( other_list.numParams(), 17 );

  other_list = cross_sections.sublist( "H-1_293.6K_v7" );

  TEST_EQUALITY_CONST( other_list.numParams(), 17 );

  other_list = cross_sections.sublist( "He-3_900.0K_v8" );
  
  TEST_EQUALITY_CONST( other_list.numParams(), 17 );

  other_list = cross_sections.sublist( "He-3_600.0K_v8" );

  TEST_EQUALITY_CONST( other_list.numParams(), 17 );

  other_list = cross_sections.sublist( "He-3_293.6K_v8" );

  TEST_EQUALITY_CONST( other_list.numParams(), 17 );

  other_list = cross_sections.sublist( "He-3_900.0K_v7" );
  
  TEST_EQUALITY_CONST( other_list.numParams(), 17 );

  other_list = cross_sections.sublist( "He-3_600.0K_v7" );

  TEST_EQUALITY_CONST( other_list.numParams(), 17 );

  other_list = cross_sections.sublist( "He-3_293.6K_v7" );

  TEST_EQUALITY_CONST( other_list.numParams(), 17 );

  other_list = cross_sections.sublist( "He-4_900.0K_v8" );
  
  TEST_EQUALITY_CONST( other_list.numParams(), 17 );

  other_list = cross_sections.sublist( "He-4_600.0K_v8" );

  TEST_EQUALITY_CONST( other_list.numParams(), 17 );

  other_list = cross_sections.sublist( "He-4_293.6K_v8" );

  TEST_EQUALITY_CONST( other_list.numParams(), 17 );

  other_list = cross_sections.sublist( "He-4_900.0K_v7" );
  
  TEST_EQUALITY_CONST( other_list.numParams(), 17 );

  other_list = cross_sections.sublist( "He-4_600.0K_v7" );

  TEST_EQUALITY_CONST( other_list.numParams(), 17 );

  other_list = cross_sections.sublist( "He-4_293.6K_v7" );

  TEST_EQUALITY_CONST( other_list.numParams(), 17 );

  other_list = cross_sections.sublist( "be_293.6K_v2" );
  
  TEST_EQUALITY_CONST( other_list.numParams(), 5 );

  other_list = cross_sections.sublist( "be_400.0K_v2" );

  TEST_EQUALITY_CONST( other_list.numParams(), 5 );
  
  other_list = cross_sections.sublist( "H" );

  TEST_EQUALITY_CONST( other_list.numParams(), 10 );

  other_list = cross_sections.sublist( "He" );

  TEST_EQUALITY_CONST( other_list.numParams(), 10 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_xsdir_file",
		 &xsdir_file_name,
		 "Test xsdir file" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
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
// end tstXsdir.cpp
//---------------------------------------------------------------------------//
