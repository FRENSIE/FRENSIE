//---------------------------------------------------------------------------//
//!
//! \file   tstRoot.cpp
//! \author Alex Robinson
//! \brief  Root wrapper class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>
#include <map>
#include <set>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_UnitTestRepository.hpp>
#include <Teuchos_GlobalMPISession.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_Tuple.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_ScalarTraits.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Geometry_Root.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::string test_root_geom_file_name;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check the default property names
TEUCHOS_UNIT_TEST( Root, default_property_names )
{
  std::string default_property = 
    Geometry::Root::getMaterialPropertyName();

  TEST_EQUALITY_CONST( default_property, "mat" );

  std::string default_void_mat_name = 
    Geometry::Root::getVoidMaterialName();

  TEST_EQUALITY_CONST( default_void_mat_name, "void" );

  std::string default_terminal_mat_name = 
    Geometry::Root::getTerminalMaterialName();

  TEST_EQUALITY_CONST( default_terminal_mat_name, "graveyard" );
}

//---------------------------------------------------------------------------//
// Check that the material property name can be set
TEUCHOS_UNIT_TEST( Root, setMaterialPropertyName )
{
  std::string default_property = 
    Geometry::Root::getMaterialPropertyName();

  Geometry::Root::setMaterialPropertyName( "material" );
    
  std::string new_property = Geometry::Root::getMaterialPropertyName();
    
  TEST_EQUALITY_CONST( new_property, "material" );

  Geometry::Root::setMaterialPropertyName( default_property );
}

//---------------------------------------------------------------------------//
// Check that the void material name can be set
TEUCHOS_UNIT_TEST( Root, setVoidMaterialName )
{
  std::string default_void_mat_name = 
    Geometry::Root::getVoidMaterialName();

  Geometry::Root::setVoidMaterialName( "empty" );

  std::string new_name = Geometry::Root::getVoidMaterialName();

  TEST_EQUALITY_CONST( new_name, "empty" );

  Geometry::Root::setVoidMaterialName( default_void_mat_name );
}

//---------------------------------------------------------------------------//
// Check that the terminal material name can be set
TEUCHOS_UNIT_TEST( Root, setTerminalMaterialName )
{
  std::string default_terminal_mat_name = 
    Geometry::Root::getTerminalMaterialName();

  Geometry::Root::setTerminalMaterialName( "terminal_mat" );

  std::string new_name = Geometry::Root::getTerminalMaterialName();

  TEST_EQUALITY_CONST( new_name, "terminal_mat" );

  Geometry::Root::setTerminalMaterialName( default_terminal_mat_name );
}

//---------------------------------------------------------------------------//
// Check that Root can be initialized
TEUCHOS_UNIT_TEST( Root, initialize )
{
  TEST_ASSERT( !Geometry::Root::isInitialized() );

  TEST_NOTHROW( Geometry::Root::initialize( test_root_geom_file_name ) );

  TEST_ASSERT( Geometry::Root::isInitialized() );
}

//---------------------------------------------------------------------------//
// Get the material ids
TEUCHOS_UNIT_TEST( Root, getMaterialIds )
{
  std::set<unsigned> material_ids;

  Geometry::Root::getMaterialIds( material_ids );

  TEST_EQUALITY_CONST( material_ids.size(), 1 );
  TEST_ASSERT( material_ids.count( 1 ) );
}

//---------------------------------------------------------------------------//
// Check if the cell exists
TEUCHOS_UNIT_TEST( Root, doesCellExist )
{
  TEST_ASSERT( Geometry::Root::doesCellExist( 1 ) );
  TEST_ASSERT( Geometry::Root::doesCellExist( 2 ) );
  TEST_ASSERT( Geometry::Root::doesCellExist( 3 ) );
  
  TEST_ASSERT( !Geometry::Root::doesCellExist( 4 ) );
}

//---------------------------------------------------------------------------//
// Get if the cell volume
TEUCHOS_UNIT_TEST( Root, getCellVolume )
{
  TEST_FLOATING_EQUALITY( Geometry::Root::getCellVolume( 1 ), 
                          934.550153050213,
                          1e-9 );

  TEST_FLOATING_EQUALITY( Geometry::Root::getCellVolume( 2 ), 
                          65.4498469497874,
                          1e-9 );

  TEST_FLOATING_EQUALITY( Geometry::Root::getCellVolume( 3 ), 
                          1744.0,
                          1e-9 );
}

//---------------------------------------------------------------------------//
// Check if a cell is a termination cell
TEUCHOS_UNIT_TEST( Root, isTerminationCell )
{
  TEST_ASSERT( !Geometry::Root::isTerminationCell( 1 ) );
  TEST_ASSERT( !Geometry::Root::isTerminationCell( 2 ) );
  TEST_ASSERT( Geometry::Root::isTerminationCell( 3 ) );
}

//---------------------------------------------------------------------------//
// Check if a cell is a void cell
TEUCHOS_UNIT_TEST( Root, isVoidCell )
{
  TEST_ASSERT( Geometry::Root::isVoidCell( 1 ) );
  TEST_ASSERT( !Geometry::Root::isVoidCell( 2 ) );
  TEST_ASSERT( !Geometry::Root::isVoidCell( 3 ) );
}

//---------------------------------------------------------------------------//
// Check if the cells can be returned
TEUCHOS_UNIT_TEST( Root, getCells )
{
  std::set<Geometry::ModuleTraits::InternalCellHandle> cells;

  // Get all cells except the termination cells
  Geometry::Root::getCells( cells );
  
  TEST_EQUALITY_CONST( cells.size(), 2 );
  TEST_ASSERT( cells.count( 1 ) );
  TEST_ASSERT( cells.count( 2 ) );
  TEST_ASSERT( !cells.count( 3 ) );

  cells.clear();

  // Get all cells except the void and termination cells
  Geometry::Root::getCells( cells, false );

  TEST_EQUALITY_CONST( cells.size(), 1 );
  TEST_ASSERT( !cells.count( 1 ) );
  TEST_ASSERT( cells.count( 2 ) );
  TEST_ASSERT( !cells.count( 3 ) );

  cells.clear();

  // Get all cells except the void cells
  Geometry::Root::getCells( cells, false, true );

  TEST_EQUALITY_CONST( cells.size(), 2 );
  TEST_ASSERT( !cells.count( 1 ) );
  TEST_ASSERT( cells.count( 2 ) );
  TEST_ASSERT( cells.count( 3 ) );

  cells.clear();

  // Get all cells
  Geometry::Root::getCells( cells, true, true );

  TEST_EQUALITY_CONST( cells.size(), 3 );
  TEST_ASSERT( cells.count( 1 ) );
  TEST_ASSERT( cells.count( 2 ) );
  TEST_ASSERT( cells.count( 3 ) );
}

//---------------------------------------------------------------------------//
// Get the cell material names
TEUCHOS_UNIT_TEST( Root, getCellMaterialNames )
{
  std::map<Geometry::ModuleTraits::InternalCellHandle,std::string>
    cell_id_material_name_map;

  Geometry::Root::getCellMaterialNames( cell_id_material_name_map );

  TEST_EQUALITY_CONST( cell_id_material_name_map.size(), 3 );
  TEST_ASSERT( cell_id_material_name_map.count( 1 ) );
  TEST_ASSERT( cell_id_material_name_map.count( 2 ) );
  TEST_ASSERT( cell_id_material_name_map.count( 3 ) );
  TEST_EQUALITY_CONST( cell_id_material_name_map.find( 1 )->second, "void" );
  TEST_EQUALITY_CONST( cell_id_material_name_map.find( 2 )->second, "mat_1" );
  TEST_EQUALITY_CONST( cell_id_material_name_map.find( 3 )->second,
                       "graveyard" );
}

//---------------------------------------------------------------------------//
// Get the cell material ids
TEUCHOS_UNIT_TEST( Root, getCellMaterialIds )
{
  std::map<Geometry::ModuleTraits::InternalCellHandle,unsigned long long>
    cell_id_mat_id_map;

  Geometry::Root::getCellMaterialIds( cell_id_mat_id_map );

  TEST_EQUALITY_CONST( cell_id_mat_id_map.size(), 1 );
  TEST_ASSERT( cell_id_mat_id_map.count( 2 ) );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 2 )->second, 1 );
}

//---------------------------------------------------------------------------//
// Get the cell densities
TEUCHOS_UNIT_TEST( Root, getCellDensities )
{
  std::map<Geometry::ModuleTraits::InternalCellHandle,double>
    cell_id_density_map;

  Geometry::Root::getCellDensities( cell_id_density_map );

  TEST_EQUALITY_CONST( cell_id_density_map.size(), 1 );
  TEST_ASSERT( cell_id_density_map.count( 2 ) );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 2 )->second, 1 );
}

//---------------------------------------------------------------------------//
// Check that a point location w.r.t. a given cell can be determined
TEUCHOS_UNIT_TEST( Root, getPointLocation )
{
  // Initialize the ray
  std::shared_ptr<Geometry::Ray> 
    ray( new Geometry::Ray( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 ) );

  // Point inside of cell 2
  Geometry::PointLocation location =
    Geometry::Root::getPointLocation( *ray, 2 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_INSIDE_CELL );

  location = Geometry::Root::getPointLocation( *ray, 1 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_OUTSIDE_CELL );

  location = Geometry::Root::getPointLocation( *ray, 3 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_OUTSIDE_CELL );

  // Point on boundary between cell 2 and cell 1
  ray.reset( new Geometry::Ray( 0.0, 0.0, 2.5, 0.0, 0.0, 1.0 ) );

  location = Geometry::Root::getPointLocation( *ray, 2 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_INSIDE_CELL );

  location = Geometry::Root::getPointLocation( *ray, 1 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_OUTSIDE_CELL );

  location = Geometry::Root::getPointLocation( *ray, 3 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_OUTSIDE_CELL );

  // Point in cell 1
  ray.reset( new Geometry::Ray( 0.0, 0.0, 4.0, 0.0, 0.0, 1.0 ) );

  location = Geometry::Root::getPointLocation( ray->getPosition(), 2 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_OUTSIDE_CELL );

  location = Geometry::Root::getPointLocation( ray->getPosition(), 1 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_INSIDE_CELL );

  location = Geometry::Root::getPointLocation( ray->getPosition(), 3 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_OUTSIDE_CELL );

  // Point on boundary between cell 1 and 3
  ray.reset( new Geometry::Ray( 0.0, 0.0, 5.0, 0.0, 0.0, 1.0 ) );

  location = Geometry::Root::getPointLocation( ray->getPosition(), 2 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_OUTSIDE_CELL );
  
  location = Geometry::Root::getPointLocation( ray->getPosition(), 1 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_INSIDE_CELL );

  location = Geometry::Root::getPointLocation( ray->getPosition(), 3 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_OUTSIDE_CELL );

  // Point in cell 3
  ray.reset( new Geometry::Ray( 0.0, 0.0, 6.0, 0.0, 0.0, 1.0 ) );

  location = Geometry::Root::getPointLocation( ray->getPosition(), 2 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_OUTSIDE_CELL );

  location = Geometry::Root::getPointLocation( ray->getPosition(), 1 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_OUTSIDE_CELL );

  location = Geometry::Root::getPointLocation( ray->getPosition(), 3 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_INSIDE_CELL );
}

//---------------------------------------------------------------------------//
// Check that a cell containing an external ray can be determined
TEUCHOS_UNIT_TEST( Root, findCellContainingExternalRay )
{
  // Initialize the ray
  std::shared_ptr<Geometry::Ray> 
    ray( new Geometry::Ray( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 ) );

  Geometry::ModuleTraits::InternalCellHandle cell;

  cell = Geometry::Root::findCellContainingExternalRay( *ray );

  TEST_EQUALITY_CONST( cell, 2 );

  // Check that the direction is used to correctly determine the cell when
  // on a boundary
  ray.reset( new Geometry::Ray( 0.0, 0.0, 2.5, 0.0, 0.0, 1.0 ) );

  cell = Geometry::Root::findCellContainingExternalRay( *ray );

  TEST_EQUALITY_CONST( cell, 1 );

  ray.reset( new Geometry::Ray( 0.0, 0.0, 2.5, 0.0, 0.0, -1.0 ) );

  cell = Geometry::Root::findCellContainingExternalRay( *ray );

  TEST_EQUALITY_CONST( cell, 2 );
}

//---------------------------------------------------------------------------//
// Check that an external ray can be fired
TEUCHOS_UNIT_TEST( Root, fireExternalRay )
{
  // Initialize the ray
  Geometry::Ray ray( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 );

  // Fire a ray through the geometry
  double distance_to_boundary = Geometry::Root::fireExternalRay( ray );

  TEST_FLOATING_EQUALITY( distance_to_boundary, 2.5, 1e-9 );
}

//---------------------------------------------------------------------------//
// Check that a simple external ray trace can be done
TEUCHOS_UNIT_TEST( Root, external_ray_trace )
{
  // Initialize the ray
  Geometry::Ray ray( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 );

  Geometry::ModuleTraits::InternalCellHandle cell = 
    Geometry::Root::findCellContainingExternalRay( ray );
  
  TEST_EQUALITY_CONST( cell, 2 );

  // Fire a ray through the geometry
  double distance_to_boundary = Geometry::Root::fireExternalRay( ray );
 
  ray.advanceHead( distance_to_boundary );
  
  // Find the new cell
  cell = Geometry::Root::findCellContainingExternalRay( ray );
  
  TEST_EQUALITY_CONST( cell, 1 );

  // Fire a ray through the geometry
  distance_to_boundary = Geometry::Root::fireExternalRay( ray );

  ray.advanceHead( distance_to_boundary );
  
  // Find the new cell
  cell = Geometry::Root::findCellContainingExternalRay( ray );

  TEST_EQUALITY_CONST( cell, 3 );
}

//---------------------------------------------------------------------------//
// Check that the internal ray can be set
TEUCHOS_UNIT_TEST( Root, setInternalRay )
{
  std::shared_ptr<Geometry::Ray> 
    ray( new Geometry::Ray( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 ) );

  Geometry::Root::setInternalRay( *ray );

  TEST_EQUALITY_CONST( Geometry::Root::getInternalRayPosition()[0], 0.0 );
  TEST_EQUALITY_CONST( Geometry::Root::getInternalRayPosition()[1], 0.0 );
  TEST_EQUALITY_CONST( Geometry::Root::getInternalRayPosition()[2], 0.0 );

  TEST_EQUALITY_CONST( Geometry::Root::getInternalRayDirection()[0], 0.0 );
  TEST_EQUALITY_CONST( Geometry::Root::getInternalRayDirection()[1], 0.0 );
  TEST_EQUALITY_CONST( Geometry::Root::getInternalRayDirection()[2], 1.0 );

  ray.reset( new Geometry::Ray( 1.0, 1.0, 1.0, 0.0, 1.0, 0.0 ) );

  Geometry::Root::setInternalRay( ray->getPosition(), ray->getDirection() );

  TEST_EQUALITY_CONST( Geometry::Root::getInternalRayPosition()[0], 1.0 );
  TEST_EQUALITY_CONST( Geometry::Root::getInternalRayPosition()[1], 1.0 );
  TEST_EQUALITY_CONST( Geometry::Root::getInternalRayPosition()[2], 1.0 );

  TEST_EQUALITY_CONST( Geometry::Root::getInternalRayDirection()[0], 0.0 );
  TEST_EQUALITY_CONST( Geometry::Root::getInternalRayDirection()[1], 1.0 );
  TEST_EQUALITY_CONST( Geometry::Root::getInternalRayDirection()[2], 0.0 );
}

//---------------------------------------------------------------------------//
// Check if the internal ray has been set
TEUCHOS_UNIT_TEST( Root, isInternalRaySet )
{
  // Initialize the ray
  Geometry::Ray ray( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 );

  // Use external ray
  Geometry::ModuleTraits::InternalCellHandle cell = 
    Geometry::Root::findCellContainingExternalRay( ray );

  TEST_ASSERT( !Geometry::Root::isInternalRaySet() );

  // Set the internal ray
  Geometry::Root::setInternalRay( ray );

  TEST_ASSERT( Geometry::Root::isInternalRaySet() );

  // Fire an external ray
  double distance_to_boundary = Geometry::Root::fireExternalRay( ray );
 
  TEST_ASSERT( !Geometry::Root::isInternalRaySet() );

  // Set the internal ray
  Geometry::Root::setInternalRay( ray );

  TEST_ASSERT( Geometry::Root::isInternalRaySet() );
}

//---------------------------------------------------------------------------//
// Check that the internal ray direction can be changed
TEUCHOS_UNIT_TEST( Root, changeInternalRayDirection )
{
  // Initailize the ray
  {
    Geometry::Ray ray( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 );
    
    Geometry::Root::setInternalRay( ray );
  }
  
  Geometry::Root::changeInternalRayDirection( 1.0, 0.0, 0.0 );

  TEST_EQUALITY_CONST( Geometry::Root::getInternalRayDirection()[0], 1.0 );
  TEST_EQUALITY_CONST( Geometry::Root::getInternalRayDirection()[1], 0.0 );
  TEST_EQUALITY_CONST( Geometry::Root::getInternalRayDirection()[2], 0.0 );

  {
    const double direction[3] = {0.0, 1.0, 0.0};

    Geometry::Root::changeInternalRayDirection( direction );
  }

  TEST_EQUALITY_CONST( Geometry::Root::getInternalRayDirection()[0], 0.0 );
  TEST_EQUALITY_CONST( Geometry::Root::getInternalRayDirection()[1], 1.0 );
  TEST_EQUALITY_CONST( Geometry::Root::getInternalRayDirection()[2], 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the cell containing the internal ray can be found
TEUCHOS_UNIT_TEST( Root, findCellContainingInternalRay )
{
  // Initialize the ray
  std::shared_ptr<Geometry::Ray> 
    ray( new Geometry::Ray( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 ) );

  Geometry::Root::setInternalRay( *ray );

  Geometry::ModuleTraits::InternalCellHandle cell;

  cell = Geometry::Root::findCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 2 );

  // Initialize the ray
  ray.reset( new Geometry::Ray( 0.0, 0.0, 3.0, 0.0, 0.0, 1.0 ) );

  Geometry::Root::setInternalRay( *ray );

  cell = Geometry::Root::findCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 1 );

  // Initialize the ray
  ray.reset( new Geometry::Ray( 0.0, 0.0, 6.0, 0.0, 0.0, 1.0 ) );

  Geometry::Root::setInternalRay( *ray );

  cell = Geometry::Root::findCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 3 );
}

//---------------------------------------------------------------------------//
// Check that an internal ray can be fired
TEUCHOS_UNIT_TEST( Root, fireInternalRay )
{
  // Initialize the ray
  Geometry::Ray ray( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 );

  Geometry::Root::setInternalRay( ray );

  // Fire a ray through the geometry
  double distance_to_boundary = Geometry::Root::fireInternalRay();

  TEST_FLOATING_EQUALITY( distance_to_boundary, 2.5, 1e-9 );
}

//---------------------------------------------------------------------------//
// Check that a simple internal ray trace can be done
TEUCHOS_UNIT_TEST( Root, internal_ray_trace )
{
  // Initialize the ray
  {
    Geometry::Ray ray( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 );

    Geometry::Root::setInternalRay( ray );
  }

  Geometry::ModuleTraits::InternalCellHandle cell = 
    Geometry::Root::findCellContainingInternalRay();
  
  TEST_EQUALITY_CONST( cell, 2 );

  // Fire a ray through the geometry
  double distance_to_boundary = Geometry::Root::fireInternalRay();

  TEST_FLOATING_EQUALITY( distance_to_boundary, 2.5, 1e-9 );
 
  // Advance the ray to the cell boundary
  Geometry::Root::advanceInternalRayToCellBoundary();

  // Find the new cell
  cell = Geometry::Root::findCellContainingInternalRay();
  
  TEST_EQUALITY_CONST( cell, 1 );

  // Fire a ray through the geometry
  distance_to_boundary = Geometry::Root::fireInternalRay();

  TEST_FLOATING_EQUALITY( distance_to_boundary, 2.5, 1e-6 );

  // Advance the ray a substep
  Geometry::Root::advanceInternalRayBySubstep( 0.5*distance_to_boundary );

  // Change the ray direction
  Geometry::Root::changeInternalRayDirection( 0.0, 1.0, 0.0 );

  // Fire a ray through the geometry
  distance_to_boundary = Geometry::Root::fireInternalRay();

  TEST_FLOATING_EQUALITY( distance_to_boundary, 5.0, 1e-9 );

  // Advance the ray to the cell boundary
  Geometry::Root::advanceInternalRayToCellBoundary();
  
  // Find the new cell
  cell = Geometry::Root::findCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 3 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_root_file",
		 &test_root_geom_file_name,
		 "Test root geometry file name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Initialize the global MPI session
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  out->setProcRankAndSize( mpiSession.getRank(), mpiSession.getNProc() );
  out->setOutputToRootOnly( 0 );
  
  mpiSession.barrier();
  
  // Run the unit tests
  const bool success = Teuchos::UnitTestRepository::runUnitTests(*out);

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstRoot.cpp
//---------------------------------------------------------------------------//
