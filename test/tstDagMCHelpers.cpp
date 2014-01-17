//---------------------------------------------------------------------------//
//!
//! \file   tstDagMCHelpers.cpp
//! \author Alex Robinson
//! \brief  DagMC helper function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_UnitTestRepository.hpp>
#include <Teuchos_GlobalMPISession.hpp>

// FACEMC Includes
#include "DagMCHelpers.hpp"

//---------------------------------------------------------------------------//
// Test Sat File Name
//---------------------------------------------------------------------------//
std::string test_geometry_file_name;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a set of property names can be validated
TEUCHOS_UNIT_TEST( DagMCHelpers, validatePropertyNames )
{
  std::vector<std::string> available_property_names( 3 );
  std::vector<std::string> valid_property_names( 3 );
  std::string invalid_property_names;

  available_property_names[0] = "graveyard";
  available_property_names[1] = "material";
  available_property_names[2] = "badprop";
  
  valid_property_names[0] = "graveyard";
  valid_property_names[1] = "material";
  valid_property_names[2] = "density";

  FACEMC::validatePropertyNames( available_property_names,
				 valid_property_names,
				 invalid_property_names );
  
  TEST_EQUALITY_CONST( invalid_property_names.compare( "badprop" ), 0 );
}

//---------------------------------------------------------------------------//
// Check that DagMC can be initialized
TEUCHOS_UNIT_TEST( DagMCHelpers, initializeDagMC )
{
  // Set up the valid property names
  std::vector<std::string> property_names( 6 );
  property_names[0] = "graveyard";
  property_names[1] = "mat";
  property_names[2] = "rho";
  property_names[3] = "tally";
  property_names[4] = "cell.flux";
  property_names[5] = "surf.flux";
  
  // Initialize DagMC
  FACEMC::initializeDagMC( test_geometry_file_name,
			   property_names,
			   1e-3 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char* argv[] )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();
  
  clp.setOption( "test_sat_file",
		 &test_geometry_file_name,
		 "Test sat file name" );
  
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );
}
				  
//---------------------------------------------------------------------------//
// end tstDagMCHelpers.cpp
//---------------------------------------------------------------------------//
