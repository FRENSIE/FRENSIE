//---------------------------------------------------------------------------//
//!
//! \file   tstRootInstanceFactory.cpp
//! \author Eli Moll
//! \brief  Root instance factory class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <string>

// // Boost Include
// #include <boost/unordered_map.hpp>

// // Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_UnitTestRepository.hpp>
#include <Teuchos_GlobalMPISession.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_VerboseObject.hpp>

// // FRENSIE Includes
#include "Geometry_RootInstanceFactory.hpp"
#include "Geometry_Root.hpp"
#include "Geometry_ModuleInterface_Root.hpp"
#include "Geometry_ModuleTraits.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::string test_geom_xml_file_name;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that Root can be properly initialized
TEUCHOS_UNIT_TEST( RootInstanceFactory, initializeRoot )
{
  Teuchos::RCP<Teuchos::ParameterList> geom_rep = 
    Teuchos::getParametersFromXmlFile( test_geom_xml_file_name );
  
  Geometry::RootInstanceFactory::initializeRoot( *geom_rep );
  
  // Test that all nodes can be read in and numbered
  TEST_EQUALITY_CONST( Geometry::Root::getManager()->GetNNodes(), 2);
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char* argv[] )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();
  
  clp.setOption( "test_xml_file",
  		 &test_geom_xml_file_name,
  		 "Test xml geometry file name" );
  
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );
}

//---------------------------------------------------------------------------//
// end tstRootInstanceFactory.cpp
//---------------------------------------------------------------------------//
