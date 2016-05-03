//---------------------------------------------------------------------------//
//!
//! \file   tstRootInstanceFactoryAdvanced.cpp
//! \author Eli Moll
//! \brief  Root instance factory class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <string>
#include <map>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_UnitTestRepository.hpp>
#include <Teuchos_GlobalMPISession.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_VerboseObject.hpp>

// // FRENSIE Includes
#include "Geometry_RootInstanceFactory.hpp"
#include "Geometry_Root.hpp"
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
  
  TEST_NOTHROW( Geometry::RootInstanceFactory::initializeRoot( *geom_rep ) );
  
  // Test that all nodes can be read in and numbered
  TEST_ASSERT( Geometry::Root::doesCellExist( 1 ) );
  TEST_ASSERT( Geometry::Root::doesCellExist( 2 ) );
  TEST_ASSERT( Geometry::Root::doesCellExist( 3 ) );

  TEST_ASSERT( Geometry::Root::isTerminationCell( 3 ) );
  TEST_ASSERT( Geometry::Root::isVoidCell( 1 ) );
  
  std::map<unsigned,unsigned> cell_id_mat_id_map;

  Geometry::Root::getCellMaterialIds( cell_id_mat_id_map );

  TEST_EQUALITY_CONST( cell_id_mat_id_map.size(), 1 );
  TEST_ASSERT( cell_id_mat_id_map.find( 2 ) !=
               cell_id_mat_id_map.end() );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 2 )->second, 1 );

  std::map<unsigned,double> cell_id_density_map;

  Geometry::Root::getCellDensities( cell_id_density_map );

  TEST_EQUALITY_CONST( cell_id_density_map.size(), 1 );
  TEST_ASSERT( cell_id_density_map.find( 2 ) !=
               cell_id_density_map.end() );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 2 )->second, 1.0 );
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
// end tstRootInstanceFactoryAdvanced.cpp
//---------------------------------------------------------------------------//
