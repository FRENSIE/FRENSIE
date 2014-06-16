//---------------------------------------------------------------------------//
//! 
//! \file   tstModuleInterface.cpp
//! \author Alex Robinson
//! \brief  Geometry module interface unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_UnitTestRepository.hpp>
#include <Teuchos_GlobalMPISession.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_Tuple.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Geometry_Ray.hpp"
#include "Geometry_DagMCHelpers.hpp"
#include "Geometry_DagMCInstanceFactory.hpp"
#include "Geometry_ModuleInterface_DagMC.hpp"

//---------------------------------------------------------------------------//
// Test Sat File Name
//---------------------------------------------------------------------------//
std::string test_geom_xml_file_name;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that surface ids can be checked for existence
TEUCHOS_UNIT_TEST( ModuleInterface_DagMC, doesSufaceExist )
{
  typedef Geometry::ModuleInterface<moab::DagMC> GMI;
  
  TEST_ASSERT( !GMI::doesSurfaceExist( 0 ) );
  TEST_ASSERT( GMI::doesSurfaceExist( 1 ) );
  TEST_ASSERT( !GMI::doesSurfaceExist( 2 ) );
  TEST_ASSERT( !GMI::doesSurfaceExist( 3 ) );
  TEST_ASSERT( !GMI::doesSurfaceExist( 4 ) );
  TEST_ASSERT( !GMI::doesSurfaceExist( 5 ) );
  TEST_ASSERT( !GMI::doesSurfaceExist( 6 ) );
  TEST_ASSERT( GMI::doesSurfaceExist( 7 ) );
  TEST_ASSERT( GMI::doesSurfaceExist( 8 ) );
  TEST_ASSERT( GMI::doesSurfaceExist( 9 ) );
}

//---------------------------------------------------------------------------//
// Check that cell ids can be checked for existence
TEUCHOS_UNIT_TEST( ModuleInterface_DagMC, doesCellExist )
{
  typedef Geometry::ModuleInterface<moab::DagMC> GMI;
  
  TEST_ASSERT( !GMI::doesCellExist( 0 ) );
  TEST_ASSERT( GMI::doesCellExist( 1 ) );
  TEST_ASSERT( !GMI::doesCellExist( 2 ) );
  TEST_ASSERT( GMI::doesCellExist( 3 ) );
  TEST_ASSERT( !GMI::doesCellExist( 4 ) );
  TEST_ASSERT( GMI::doesCellExist( 5 ) );
  TEST_ASSERT( !GMI::doesCellExist( 6 ) );
  TEST_ASSERT( GMI::doesCellExist( 7 ) );
  TEST_ASSERT( !GMI::doesCellExist( 8 ) );
  TEST_ASSERT( GMI::doesCellExist( 9 ) );
  TEST_ASSERT( GMI::doesCellExist( 13 ) );
  TEST_ASSERT( GMI::doesCellExist( 19 ) );
  TEST_ASSERT( GMI::doesCellExist( 26 ) );
  TEST_ASSERT( GMI::doesCellExist( 27 ) );
  TEST_ASSERT( GMI::doesCellExist( 28 ) );
  TEST_ASSERT( GMI::doesCellExist( 29 ) );
  TEST_ASSERT( GMI::doesCellExist( 30 ) );
  TEST_ASSERT( GMI::doesCellExist( 31 ) );
  TEST_ASSERT( GMI::doesCellExist( 32 ) );
  TEST_ASSERT( GMI::doesCellExist( 33 ) );
  TEST_ASSERT( GMI::doesCellExist( 34 ) );
  TEST_ASSERT( GMI::doesCellExist( 35 ) );
  TEST_ASSERT( GMI::doesCellExist( 36 ) );
  TEST_ASSERT( GMI::doesCellExist( 37 ) );
  TEST_ASSERT( GMI::doesCellExist( 41 ) );
  TEST_ASSERT( GMI::doesCellExist( 48 ) );
  TEST_ASSERT( GMI::doesCellExist( 49 ) );
  TEST_ASSERT( GMI::doesCellExist( 50 ) );
  TEST_ASSERT( GMI::doesCellExist( 51 ) );
  TEST_ASSERT( GMI::doesCellExist( 52 ) );
  TEST_ASSERT( GMI::doesCellExist( 53 ) );
  TEST_ASSERT( GMI::doesCellExist( 54 ) );
  TEST_ASSERT( GMI::doesCellExist( 55 ) );
  TEST_ASSERT( GMI::doesCellExist( 56 ) );
  TEST_ASSERT( GMI::doesCellExist( 57 ) );
  TEST_ASSERT( GMI::doesCellExist( 58 ) );
  TEST_ASSERT( GMI::doesCellExist( 59 ) );
  TEST_ASSERT( GMI::doesCellExist( 63 ) );
  TEST_ASSERT( GMI::doesCellExist( 70 ) );
  TEST_ASSERT( GMI::doesCellExist( 71 ) );
  TEST_ASSERT( GMI::doesCellExist( 72 ) );
  TEST_ASSERT( GMI::doesCellExist( 73 ) );
  TEST_ASSERT( GMI::doesCellExist( 74 ) );
  TEST_ASSERT( GMI::doesCellExist( 75 ) );
  TEST_ASSERT( GMI::doesCellExist( 76 ) );
  TEST_ASSERT( GMI::doesCellExist( 77 ) );
  TEST_ASSERT( GMI::doesCellExist( 78 ) );
  TEST_ASSERT( GMI::doesCellExist( 79 ) );
  TEST_ASSERT( GMI::doesCellExist( 80 ) );
  TEST_ASSERT( GMI::doesCellExist( 81 ) );
  TEST_ASSERT( GMI::doesCellExist( 82 ) );
  TEST_ASSERT( GMI::doesCellExist( 83 ) );
  TEST_ASSERT( GMI::doesCellExist( 88 ) );
  TEST_ASSERT( GMI::doesCellExist( 136 ) );
  TEST_ASSERT( GMI::doesCellExist( 152 ) );
  TEST_ASSERT( GMI::doesCellExist( 154 ) );
  TEST_ASSERT( GMI::doesCellExist( 166 ) );
  TEST_ASSERT( GMI::doesCellExist( 168 ) );
  TEST_ASSERT( GMI::doesCellExist( 184 ) );
  TEST_ASSERT( GMI::doesCellExist( 188 ) );
}

//---------------------------------------------------------------------------//
// Check that the cell containing a point can be deterimined
TEUCHOS_UNIT_TEST( ModuleInterface_DagMC, 
		   updateCellContainingParticle_start )
{
  typedef Geometry::ModuleInterface<moab::DagMC> GMI;
  
  // Initialize the ray
  Geometry::Ray ray( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 );
  
  // Find the cell that contains the point
  GMI::InternalCellHandle cell = GMI::findCellContainingPoint( ray );
  
  // Get the cell id associated with the cell handle
  TEST_EQUALITY_CONST( cell, 53 );
}

//---------------------------------------------------------------------------//
// Check that a ray can be fired through a CAD geometry
TEUCHOS_UNIT_TEST( ModuleInterface_DagMC, fireRay )
{
  typedef Geometry::ModuleInterface<moab::DagMC> GMI;
  
  // Initialize the ray
  Geometry::Ray ray( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 );

  // Find the cell that contains the point
  GMI::InternalCellHandle cell = GMI::findCellContainingPoint( ray );
 
  // Fire a ray through the geometry
  GMI::InternalSurfaceHandle surface_hit;
  double distance_to_surface_hit;

  GMI::fireRay( ray, cell, surface_hit, distance_to_surface_hit );
  
  // Get the surface id associated with the surface handle
  TEST_FLOATING_EQUALITY( distance_to_surface_hit, 1.959999084, 1e-9 );
  TEST_EQUALITY_CONST( surface_hit, 242 );
}

//---------------------------------------------------------------------------//
// Check that a surface crossing can be completed
TEUCHOS_UNIT_TEST( ModuleInterface_DagMC, 
		   updateCellContainingParticle_crossing )
{
  typedef Geometry::ModuleInterface<moab::DagMC> GMI;
  
  // Initialize the ray
  Geometry::Ray ray( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 );

  // Find the cell that contains the point
  GMI::InternalCellHandle cell = GMI::findCellContainingPoint( ray );
 
  // Fire a ray through the geometry
  GMI::InternalSurfaceHandle surface_hit;
  double distance_to_surface_hit;

  GMI::fireRay( ray, cell, surface_hit, distance_to_surface_hit );
  
  // Advance the ray head to the surface intersection point
  ray.advanceHead( distance_to_surface_hit );
  
  // Find the cell that the particle enters
  cell = GMI::findCellContainingPoint( ray, cell, surface_hit );

  TEST_EQUALITY_CONST( cell, 54 );

  // Complete another sequence
  GMI::fireRay( ray, cell, surface_hit, distance_to_surface_hit );
  ray.advanceHead( distance_to_surface_hit );
  cell = GMI::findCellContainingPoint( ray, cell, surface_hit );
  
  TEST_EQUALITY_CONST( cell, 55 );
}

//---------------------------------------------------------------------------//
// Check that the termination cell can be deterimed
TEUCHOS_UNIT_TEST( ModuleInterface_DagMC, 
		   isTerminationCell )
{
  typedef Geometry::ModuleInterface<moab::DagMC> GMI;

  TEST_ASSERT( GMI::isTerminationCell( 188 ) );
  TEST_ASSERT( !GMI::isTerminationCell( 54 ) );
}

//---------------------------------------------------------------------------//
// Check that the surface normal at a point on the surface can be calculated
TEUCHOS_UNIT_TEST( ModuleInterface_DagMC,
		   getSurfaceNormal )
{
  typedef Geometry::ModuleInterface<moab::DagMC> GMI;

  // Initialize the ray (on cell 53)
  Geometry::Ray ray( -40.0, -40.0, 60.959999084, 0.0, 0.0, 1.0 );

  // Get the surface normal
  Teuchos::Tuple<double,3> normal;
  GMI::getSurfaceNormal( 242, ray.getPosition(), normal.getRawPtr() );

  Teuchos::Tuple<double,3> ref_normal = Teuchos::tuple( 0.0, 0.0, 1.0 );
  
  TEST_COMPARE_ARRAYS( normal, ref_normal );
}

//---------------------------------------------------------------------------//
// Check that the volume of a cell can be calculated
TEUCHOS_UNIT_TEST( ModuleInterface_DagMC,
		   getCellVolume )
{
  typedef Geometry::ModuleInterface<moab::DagMC> GMI;

  // Get the volume of cell 53
  double cell_volume = GMI::getCellVolume( 53 );

  TEST_FLOATING_EQUALITY( cell_volume, 98.322384, 1e-6 );
}

//---------------------------------------------------------------------------//
// Check that the surface area of a surface bounding a cell can be calculated
TEUCHOS_UNIT_TEST( ModuleInterface_DagMC,
		   getCellSurfaceArea )
{
  typedef Geometry::ModuleInterface<moab::DagMC> GMI;

  // Get the surface area of surface 242 on cell 53
  double surface_area = GMI::getCellSurfaceArea( 242, 53 );

  TEST_FLOATING_EQUALITY( surface_area, 38.7096, 1e-6 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_xml_file",
		 &test_geom_xml_file_name,
		 "Test xml geometry file name" );
  
  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }
  
  // Initialize DagMC
  Teuchos::RCP<Teuchos::ParameterList> geom_rep = 
    Teuchos::getParametersFromXmlFile( test_geom_xml_file_name );

  Geometry::DagMCInstanceFactory::initializeDagMC( *geom_rep );
  
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
// end tstModuleInterface.cpp
//---------------------------------------------------------------------------//

