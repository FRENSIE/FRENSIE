//---------------------------------------------------------------------------//
//! 
//! \file   tstGeometryModuleInterface.cpp
//! \author Alex Robinson
//! \brief  GeometryModuleInterface unit tests
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

// FACEMC Includes
#include "NeutronState.hpp"
#include "PhotonState.hpp"
#include "DagMCHelpers.hpp"
#include "GeometryModuleInterface.hpp"

//---------------------------------------------------------------------------//
// Test Sat File Name
//---------------------------------------------------------------------------//
std::string test_geometry_file_name;

//---------------------------------------------------------------------------//
// DagMC Initialization Function
//---------------------------------------------------------------------------//
void initializeDagMC()
{
  // Set up the valid property names
  std::vector<std::string> property_names( 6 );
  property_names[0] = "graveyard";
  property_names[1] = "mat";
  property_names[2] = "rho";
  property_names[3] = "tally";
  property_names[4] = "cell.flux";
  property_names[5] = "surf.flux";
  
  std::cout << std::endl;

  // Initialize DagMC
  FACEMC::initializeDagMC( test_geometry_file_name,
			   property_names,
			   1e-3 );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the cell containing a point can be deterimined
TEUCHOS_UNIT_TEST( GeometryModuleInterface_DagMC, 
		   updateCellContainingParticle_start )
{
  typedef FACEMC::GeometryModuleInterface<moab::DagMC> GMI;
  
  // Initialize DagMC
  initializeDagMC();

  // Initialize the particle state
  FACEMC::NeutronState particle( 1ull );
  particle.setPosition( -40.0, -40.0, 59.0 );
  particle.setDirection( 0.0, 0.0, 1.0 );

  // Find the cell that contains the particle
  GMI::updateCellContainingParticle( particle );
  
  // Get the cell id associated with the cell handle
  TEST_EQUALITY_CONST( particle.getCell(), 53 );
}

//---------------------------------------------------------------------------//
// Check that a ray can be fired through a CAD geometry
TEUCHOS_UNIT_TEST( GeometryModuleInterface_DagMC, fireRay )
{
  typedef FACEMC::GeometryModuleInterface<moab::DagMC> GMI;
  
  // Initialize the particle state
  FACEMC::NeutronState particle( 1ull );
  particle.setPosition( -40.0, -40.0, 59.0 );
  particle.setDirection( 0.0, 0.0, 1.0 );

  // Find the cell that contains the particle
  GMI::updateCellContainingParticle( particle );

  // Fire a ray through the geometry
  typename GMI::InternalSurfaceHandle surface_hit;
  double distance_to_surface_hit;

  GMI::fireRay( particle, surface_hit, distance_to_surface_hit );
  
  // Get the surface id associated with the surface handle
  TEST_FLOATING_EQUALITY( distance_to_surface_hit, 1.959999084, 1e-9 );
  TEST_EQUALITY_CONST( surface_hit, 242 );
}

//---------------------------------------------------------------------------//
// Check that a surface crossing can be completed
TEUCHOS_UNIT_TEST( GeometryModuleInterface_DagMC, 
		   updateCellContainingParticle_crossing )
{
  typedef FACEMC::GeometryModuleInterface<moab::DagMC> GMI;
  
  // Initialize the particle state
  FACEMC::NeutronState particle( 1ull );
  particle.setPosition( -40.0, -40.0, 59.0 );
  particle.setDirection( 0.0, 0.0, 1.0 );
  particle.setEnergy( 1.0 );

  // Find the cell that contains the particle
  GMI::updateCellContainingParticle( particle );

  // Fire a ray through the geometry
  typename GMI::InternalSurfaceHandle surface_hit;
  double distance_to_surface_hit;

  GMI::fireRay( particle, surface_hit, distance_to_surface_hit );
  
  // Advance the particle to the surface intersection point
  particle.advance( distance_to_surface_hit );
  
  // Find the cell that the particle enters
  GMI::updateCellContainingParticle( particle, surface_hit );

  TEST_EQUALITY_CONST( particle.getCell(), 54 );

  // Complete another sequence
  GMI::fireRay( particle, surface_hit, distance_to_surface_hit );
  particle.advance( distance_to_surface_hit );
  GMI::updateCellContainingParticle( particle, surface_hit );
  
  TEST_EQUALITY_CONST( particle.getCell(), 55 );
}

//---------------------------------------------------------------------------//
// Check that the termination cell can be deterimed
TEUCHOS_UNIT_TEST( GeometryModuleInterface_DagMC, 
		   isTerminationCell )
{
  typedef FACEMC::GeometryModuleInterface<moab::DagMC> GMI;

  TEST_ASSERT( GMI::isTerminationCell( 188 ) );
  TEST_ASSERT( !GMI::isTerminationCell( 54 ) );
}

//---------------------------------------------------------------------------//
// Check that the surface normal at a point on the surface can be calculated
TEUCHOS_UNIT_TEST( GeometryModuleInterface_DagMC,
		   getSurfaceNormal )
{
  typedef FACEMC::GeometryModuleInterface<moab::DagMC> GMI;

  // Initialize the particle state (on cell 53)
  FACEMC::NeutronState particle( 1ull );
  particle.setPosition( -40.0, -40.0, 60.959999084 );
  particle.setDirection( 0.0, 0.0, 1.0 );

  // Get the surface normal
  Teuchos::Tuple<double,3> normal;
  GMI::getSurfaceNormal( 242, particle, normal.getRawPtr() );

  Teuchos::Tuple<double,3> ref_normal = Teuchos::tuple( 0.0, 0.0, 1.0 );
  
  TEST_COMPARE_ARRAYS( normal, ref_normal );
}

//---------------------------------------------------------------------------//
// Check that the volume of a cell can be calculated
TEUCHOS_UNIT_TEST( GeometryModuleInterface_DagMC,
		   getCellVolume )
{
  typedef FACEMC::GeometryModuleInterface<moab::DagMC> GMI;

  // Get the volume of cell 53
  double cell_volume = GMI::getCellVolume( 53 );

  TEST_FLOATING_EQUALITY( cell_volume, 98.322384, 1e-6 );
}

//---------------------------------------------------------------------------//
// Check that the surface area of a surface bounding a cell can be calculated
TEUCHOS_UNIT_TEST( GeometryModuleInterface_DagMC,
		   getCellSurfaceArea )
{
  typedef FACEMC::GeometryModuleInterface<moab::DagMC> GMI;

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

  clp.setOption( "test_sat_file",
		 &test_geometry_file_name,
		 "Test sat file name" );

  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );
}

//---------------------------------------------------------------------------//
// end tstGeometryModuleInterface.cpp
//---------------------------------------------------------------------------//

