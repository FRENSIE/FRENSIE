//---------------------------------------------------------------------------//
//! 
//! \file   tstGeometryHandlerTraits.cpp
//! \author Alex Robinson
//! \brief  GeometryHandlerTraits unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_UnitTestRepository.hpp>
#include <Teuchos_GlobalMPISession.hpp>

// FACEMC Includes
#include "ParticleState.hpp"
#include "DagMCHelpers.hpp"
#include "GeometryHandlerTraits.hpp"

//---------------------------------------------------------------------------//
// Test Set File Name
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
TEUCHOS_UNIT_TEST( GeometryHandlerTraits_DagMC, 
		   updateCellContainingParticle_start )
{
  typedef FACEMC::Traits::GeometryHandlerTraits<moab::DagMC> GHT;
  typedef FACEMC::ParticleState<typename GHT::CellHandle> ParticleState;
  
  // Initialize DagMC
  initializeDagMC();

  // Initialize the particle state
  ParticleState particle( 1ull, FACEMC::PHOTON );
  particle.setPosition( -40.0, -40.0, 59.0 );
  particle.setDirection( 0.0, 0.0, 1.0 );

  // Find the cell that contains the particle
  GHT::updateCellContainingParticle( particle );
  
  // Get the cell id associated with the cell handle
  GHT::CellId cell_id = GHT::getCellId( particle.getCell() );

  TEST_EQUALITY_CONST( cell_id, 53 );
}

//---------------------------------------------------------------------------//
// Check that a ray can be fired through a CAD geometry
TEUCHOS_UNIT_TEST( GeometryHandlerTraits_DagMC, fireRay )
{
  typedef FACEMC::Traits::GeometryHandlerTraits<moab::DagMC> GHT;
  typedef FACEMC::ParticleState<typename GHT::CellHandle> ParticleState;

  // Initialize the particle state
  ParticleState particle( 1ull, FACEMC::PHOTON );
  particle.setPosition( -40.0, -40.0, 59.0 );
  particle.setDirection( 0.0, 0.0, 1.0 );

  // Find the cell that contains the particle
  GHT::updateCellContainingParticle( particle );

  // Fire a ray through the geometry
  typename GHT::SurfaceHandle surface_hit;
  double distance_to_surface_hit;

  GHT::fireRay( particle, surface_hit, distance_to_surface_hit );
  
  // Get the surface id associated with the surface handle
  GHT::SurfaceId surface_id = GHT::getSurfaceId( surface_hit );
						
  TEST_FLOATING_EQUALITY( distance_to_surface_hit, 1.959999084, 1e-9 );
  TEST_EQUALITY_CONST( surface_id, 242 );
}

//---------------------------------------------------------------------------//
// Check that a surface crossing can be completed
TEUCHOS_UNIT_TEST( GeometryHandlerTraits_DagMC, 
		   updateCellContainingParticle_crossing )
{
  typedef FACEMC::Traits::GeometryHandlerTraits<moab::DagMC> GHT;
  typedef FACEMC::ParticleState<typename GHT::CellHandle> ParticleState;

  // Initialize the particle state
  ParticleState particle( 1ull, FACEMC::PHOTON );
  particle.setPosition( -40.0, -40.0, 59.0 );
  particle.setDirection( 0.0, 0.0, 1.0 );

  // Find the cell that contains the particle
  GHT::updateCellContainingParticle( particle );

  // Fire a ray through the geometry
  typename GHT::SurfaceHandle surface_hit;
  double distance_to_surface_hit;

  GHT::fireRay( particle, surface_hit, distance_to_surface_hit );
  
  // Advance the particle to the surface intersection point
  particle.advance( distance_to_surface_hit );
  
  // Find the cell that the particle enters
  GHT::updateCellContainingParticle( surface_hit, particle );

  // Get the cell id associated with the cell handle
  GHT::CellId cell_id = GHT::getCellId( particle.getCell() );

  TEST_EQUALITY_CONST( cell_id, 54 );

  // Complete another sequence
  GHT::fireRay( particle, surface_hit, distance_to_surface_hit );
  particle.advance( distance_to_surface_hit );
  GHT::updateCellContainingParticle( surface_hit, particle );
  cell_id = GHT::getCellId( particle.getCell() );

  TEST_EQUALITY_CONST( cell_id, 55 );
}

//---------------------------------------------------------------------------//
// Check that the termination cell can be deterimed
TEUCHOS_UNIT_TEST( GeometryHandlerTraits_DagMC, 
		   isTerminationCell )
{
  typedef FACEMC::Traits::GeometryHandlerTraits<moab::DagMC> GHT;
  typedef FACEMC::ParticleState<typename GHT::CellHandle> ParticleState;

  // Get the cell handle associated with the termination cell
  GHT::CellHandle cell = GHT::getCellHandle( 188 );
  
  TEST_ASSERT( GHT::isTerminationCell( cell ) );
}

//---------------------------------------------------------------------------//
// Check that the surface normal at a point on the surface can be calculated
TEUCHOS_UNIT_TEST( GeometryHandlerTraits_DagMC,
		   getSurfaceNormal )
{
  typedef FACEMC::Traits::GeometryHandlerTraits<moab::DagMC> GHT;
  typedef FACEMC::ParticleState<typename GHT::CellHandle> ParticleState;

  // Initialize the particle state (on cell 53)
  ParticleState particle( 1ull, FACEMC::PHOTON );
  particle.setPosition( -40.0, -40.0, 60.959999084 );
  particle.setDirection( 0.0, 0.0, 1.0 );

  // Get the surface handle associated with surface 242
  GHT::SurfaceHandle surface = GHT::getSurfaceHandle( 242 );

  // Get the surface normal
  double normal[3];
  GHT::getSurfaceNormal( surface, particle, normal );
  
  TEST_EQUALITY_CONST( normal[0], 0.0 );
  TEST_EQUALITY_CONST( normal[1], 0.0 );
  TEST_EQUALITY_CONST( normal[2], 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the volume of a cell can be calculated
TEUCHOS_UNIT_TEST( GeometryHandlerTraits_DagMC,
		   getCellVolume )
{
  typedef FACEMC::Traits::GeometryHandlerTraits<moab::DagMC> GHT;
  typedef FACEMC::ParticleState<typename GHT::CellHandle> ParticleState;

  // Get the cell handle associated with cell 53
  GHT::CellHandle cell = GHT::getCellHandle( 53 );

  // Get the volume of cell 53
  double cell_volume = GHT::getCellVolume( cell );

  TEST_FLOATING_EQUALITY( cell_volume, 98.322384, 1e-6 );
}

//---------------------------------------------------------------------------//
// Check that the surface area of a surface bounding a cell can be calculated
TEUCHOS_UNIT_TEST( GeometryHandlerTraits_DagMC,
		   getCellSurfaceArea )
{
  typedef FACEMC::Traits::GeometryHandlerTraits<moab::DagMC> GHT;
  typedef FACEMC::ParticleState<typename GHT::CellHandle> ParticleState;

  // Get the cell handle associated with cell 53
  GHT::CellHandle cell = GHT::getCellHandle( 53 );

  // Get the cell handle associated with surface 242
  GHT::SurfaceHandle surface = GHT::getSurfaceHandle( 242 );
  
  // Get the surface area of surface 242 on cell 53
  double surface_area = GHT::getCellSurfaceArea( surface, cell );

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
// end tstGeometryHandlerTraits.cpp
//---------------------------------------------------------------------------//

