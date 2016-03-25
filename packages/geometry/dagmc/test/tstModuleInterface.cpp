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
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Geometry_DagMCInstanceFactory.hpp"
#include "Geometry_ModuleInterface_DagMC.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the interface can be initialized
TEUCHOS_UNIT_TEST( ModuleInterface, initialize )
{
  TEST_NOTHROW( Geometry::ModuleInterface<Geometry::DagMC>::initialize() );
}

//---------------------------------------------------------------------------//
// Check if cells exist
TEUCHOS_UNIT_TEST( ModuleInterface, doesCellExist )
{
  typedef Geometry::ModuleInterface<Geometry::DagMC> GMI;
  
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
  
  // Implicit compliment cell
  TEST_ASSERT( GMI::doesCellExist( 189 ) ); 
}

//---------------------------------------------------------------------------//
// Check if the surface exists
TEUCHOS_UNIT_TEST( ModuleInterface, doesSurfaceExist )
{
  typedef Geometry::ModuleInterface<Geometry::DagMC> GMI;
  
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

  // There are more surfaces than this but too many to feasibly check
}

//---------------------------------------------------------------------------//
// Check that an internal ray can be set
TEUCHOS_UNIT_TEST( ModuleInterface, setInternalRay )
{
  // Set the internal ray
  std::shared_ptr<Geometry::Ray> ray( 
                      new Geometry::Ray( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 ) );
  
  Geometry::ModuleInterface<Geometry::DagMC>::setInternalRay( *ray, 53 );
  
  const double* ray_position = 
    Geometry::ModuleInterface<Geometry::DagMC>::getInternalRayPosition();
  
  TEST_EQUALITY_CONST( ray_position[0], -40.0 );
  TEST_EQUALITY_CONST( ray_position[1], -40.0 );
  TEST_EQUALITY_CONST( ray_position[2], 59.0 );

  const double* ray_direction = 
    Geometry::ModuleInterface<Geometry::DagMC>::getInternalRayDirection();

  TEST_EQUALITY_CONST( ray_direction[0], 0.0 );
  TEST_EQUALITY_CONST( ray_direction[1], 0.0 );
  TEST_EQUALITY_CONST( ray_direction[2], 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the cell containing the start ray can be found
TEUCHOS_UNIT_TEST( ModuleInterface, findCellContainingStartRay )
{
  // Initialize the ray
  std::shared_ptr<Geometry::Ray> ray( 
                      new Geometry::Ray( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 ) );
  
  // Find the cell that contains the point
  Geometry::ModuleTraits::InternalCellHandle cell = 
    Geometry::ModuleInterface<Geometry::DagMC>::findCellContainingStartRay( 
                                                                        *ray );
  
  TEST_EQUALITY_CONST( cell, 53 );

  // Initailize a new ray
  ray.reset( new Geometry::Ray( -40.0, -40.0, 61.0, 0.0, 0.0, 1.0 ) );

  // Find the cell that contains the point
  cell = 
    Geometry::ModuleInterface<Geometry::DagMC>::findCellContainingStartRay( 
                                                                        *ray );
  
  TEST_EQUALITY_CONST( cell, 54 );

  // Initialize the new ray
  ray.reset( new Geometry::Ray( -40.0, -40.0, 64.0, 0.0, 0.0, 1.0 ) );

  // Find the cell that contains the point
  cell = 
    Geometry::ModuleInterface<Geometry::DagMC>::findCellContainingStartRay( 
                                                                        *ray );
  
  TEST_EQUALITY_CONST( cell, 55 );

  // Check the found cell cache
  std::set<Geometry::ModuleTraits::InternalCellHandle> found_cell_cache;

  Geometry::DagMC::getFoundCellCache( found_cell_cache );

  TEST_EQUALITY_CONST( found_cell_cache.size(), 3 );
  TEST_ASSERT( found_cell_cache.count( 53 ) );
  TEST_ASSERT( found_cell_cache.count( 54 ) );
  TEST_ASSERT( found_cell_cache.count( 55 ) );

  Geometry::DagMC::clearFoundCellCache();
}

//---------------------------------------------------------------------------//
// Check that the cell containing the internal ray can be found
TEUCHOS_UNIT_TEST( ModuleInterface, findCellContainingInternalRay )
{
  std::shared_ptr<Geometry::Ray> ray( 
                      new Geometry::Ray( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 ) );

  Geometry::ModuleInterface<Geometry::DagMC>::setInternalRay( *ray, 53 );
  
  Geometry::ModuleTraits::InternalCellHandle cell = 
    Geometry::ModuleInterface<Geometry::DagMC>::findCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 53 );
}

//---------------------------------------------------------------------------//
// Check that the internal ray can be fired
TEUCHOS_UNIT_TEST( ModuleInterface, fireInternalRay )
{
  // Initialize the ray
  Geometry::Ray ray( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 );

  Geometry::ModuleInterface<Geometry::DagMC>::setInternalRay( ray, 53 );

  // Fire an external ray through the geometry
  Geometry::ModuleTraits::InternalSurfaceHandle surface_hit;
  
  double distance_to_surface_hit = 
    Geometry::ModuleInterface<Geometry::DagMC>::fireInternalRay( surface_hit );
 
  TEST_FLOATING_EQUALITY( distance_to_surface_hit, 1.959999084, 1e-9 );
  TEST_EQUALITY_CONST( surface_hit, 242 );
}

//---------------------------------------------------------------------------//
// Check that the internal ray can be advanced to a surface boundary
TEUCHOS_UNIT_TEST( ModuleInterface, advanceInternalRayToCellBoundary )
{
  // Initialize the ray
  {
    Geometry::Ray ray( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 );
    
    Geometry::ModuleInterface<Geometry::DagMC>::setInternalRay( ray, 53 );
  }

  // Find the cell that contains the ray
  Geometry::ModuleTraits::InternalCellHandle cell = 
    Geometry::ModuleInterface<Geometry::DagMC>::findCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 53 );

  // Advance the ray to the boundary surface
  double surface_normal[3];
  
  bool reflection = Geometry::ModuleInterface<Geometry::DagMC>::advanceInternalRayToCellBoundary( surface_normal );

  TEST_ASSERT( !reflection );
  TEST_EQUALITY_CONST( surface_normal[0], 0.0 );
  TEST_EQUALITY_CONST( surface_normal[1], 0.0 );
  TEST_EQUALITY_CONST( surface_normal[2], 1.0 );

  cell = Geometry::ModuleInterface<Geometry::DagMC>::findCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 54 );
}

//---------------------------------------------------------------------------//
// Check that the internal ray can be advanced by a substep
TEUCHOS_UNIT_TEST( ModuleInterface, advanceInternalRayBySubstep )
{
  // Initialize the ray
  {
    Geometry::Ray ray( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 );
    
    Geometry::ModuleInterface<Geometry::DagMC>::setInternalRay( ray, 53 );
  }

  Geometry::ModuleInterface<Geometry::DagMC>::advanceInternalRayBySubstep( 0.959999084 );

  // Find the cell that contains the ray
  Geometry::ModuleTraits::InternalCellHandle cell = 
    Geometry::ModuleInterface<Geometry::DagMC>::findCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 53 );
  
  // Fire the ray
  Geometry::ModuleTraits::InternalSurfaceHandle surface_hit;
  
  double distance_to_surface_hit = 
    Geometry::ModuleInterface<Geometry::DagMC>::fireInternalRay( surface_hit );

  TEST_FLOATING_EQUALITY( distance_to_surface_hit, 1.0, 1e-9 );
  TEST_EQUALITY_CONST( surface_hit, 242 );
}

//---------------------------------------------------------------------------//
// Check that the internal ray direction can be changed
TEUCHOS_UNIT_TEST( ModuleInterface, changeInternalRayDirection )
{
  std::shared_ptr<Geometry::Ray> ray( 
                      new Geometry::Ray( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 ) );

  Geometry::ModuleInterface<Geometry::DagMC>::setInternalRay( *ray, 53 );

  ray.reset( new Geometry::Ray( -40.0, -40.0, 59.0, 1.0, 0.0, 0.0 ) );
  
  Geometry::ModuleInterface<Geometry::DagMC>::changeInternalRayDirection( ray->getDirection() );

  const double* ray_direction = 
    Geometry::ModuleInterface<Geometry::DagMC>::getInternalRayDirection();

  TEST_EQUALITY_CONST( ray_direction[0], 1.0 );
  TEST_EQUALITY_CONST( ray_direction[1], 0.0 );
  TEST_EQUALITY_CONST( ray_direction[2], 0.0 );
}

//---------------------------------------------------------------------------//
// Check that termination cells can be tested
TEUCHOS_UNIT_TEST( ModuleInterface, isTerminationCell )
{
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 1 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 3 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 5 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 7 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 9 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 13 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 19 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 26 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 27 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 28 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 29 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 30 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 31 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 32 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 33 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 34 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 35 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 36 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 37 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 41 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 48 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 49 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 50 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 51 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 52 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 53 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 54 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 55 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 56 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 57 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 58 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 59 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 63 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 70 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 71 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 72 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 73 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 74 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 75 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 76 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 77 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 78 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 79 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 80 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 81 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 82 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 83 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 88 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 136 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 152 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 154 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 166 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 168 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 184 ) );
  TEST_ASSERT( Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 188 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::DagMC>::isTerminationCell( 189 ) );
}

//---------------------------------------------------------------------------//
// Check that the point location can be tested
TEUCHOS_UNIT_TEST( ModuleInterface, getPointLocation )
{
  // Initialize the ray
  std::shared_ptr<Geometry::Ray> ray( new Geometry::Ray( 
                                         -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 ) );
  
  Geometry::PointLocation location = 
    Geometry::ModuleInterface<Geometry::DagMC>::getPointLocation( *ray, 53 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_INSIDE_CELL );

  ray.reset( new Geometry::Ray( -42.647, -40.0, 59.0, -1.0, 0.0, 0.0 ) );

  location = 
    Geometry::ModuleInterface<Geometry::DagMC>::getPointLocation( *ray, 53 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_INSIDE_CELL );

  ray.reset( new Geometry::Ray( -42.648, -40.0, 59.0, -1.0, 0.0, 0.0 ) );

  location = 
    Geometry::ModuleInterface<Geometry::DagMC>::getPointLocation( *ray, 53 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_OUTSIDE_CELL );
}

//---------------------------------------------------------------------------//
// Check that a ray trace can be done
TEUCHOS_UNIT_TEST( ModuleInterface, ray_trace )
{
  // Initialize the ray
  {
    Geometry::Ray ray( -40.0, -40.0, 108.0, 0.0, 0.0, 1.0 );

    Geometry::ModuleTraits::InternalCellHandle start_cell =
      Geometry::ModuleInterface<Geometry::DagMC>::findCellContainingStartRay(
                                                                         ray );
    
    Geometry::ModuleInterface<Geometry::DagMC>::setInternalRay( 
                                                             ray, start_cell );
  }
  
  // Find the cell that contains the ray
  Geometry::ModuleTraits::InternalCellHandle cell = 
    Geometry::ModuleInterface<Geometry::DagMC>::findCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 82 );

  // Fire the ray
  Geometry::ModuleTraits::InternalSurfaceHandle surface_hit;
  
  double distance_to_surface_hit = 
    Geometry::ModuleInterface<Geometry::DagMC>::fireInternalRay( surface_hit );

  TEST_FLOATING_EQUALITY( distance_to_surface_hit, 1.474, 1e-6 );
  TEST_EQUALITY_CONST( surface_hit, 394 );
  
  // Advance the ray to the boundary surface
  double surface_normal[3];
  
  bool reflection = Geometry::ModuleInterface<Geometry::DagMC>::advanceInternalRayToCellBoundary( surface_normal );

  TEST_ASSERT( !reflection );
  TEST_EQUALITY_CONST( surface_normal[0], 0.0 );
  TEST_EQUALITY_CONST( surface_normal[1], 0.0 );
  TEST_EQUALITY_CONST( surface_normal[2], 1.0 );

  cell = 
    Geometry::ModuleInterface<Geometry::DagMC>::findCellContainingInternalRay();
  
  TEST_EQUALITY_CONST( cell, 83 );

  distance_to_surface_hit = 
    Geometry::ModuleInterface<Geometry::DagMC>::fireInternalRay( surface_hit );

  TEST_FLOATING_EQUALITY( distance_to_surface_hit, 17.526, 1e-6 );
  TEST_EQUALITY_CONST( surface_hit, 408 );

  // Advance the ray to the boundary surface (reflecting)  
  reflection = Geometry::ModuleInterface<Geometry::DagMC>::advanceInternalRayToCellBoundary( surface_normal );

  TEST_ASSERT( reflection );
  TEST_EQUALITY_CONST( surface_normal[0], 0.0 );
  TEST_EQUALITY_CONST( surface_normal[1], 0.0 );
  TEST_EQUALITY_CONST( surface_normal[2], 1.0 );

  cell = Geometry::ModuleInterface<Geometry::DagMC>::findCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 83 );

  distance_to_surface_hit = Geometry::ModuleInterface<Geometry::DagMC>::fireInternalRay( surface_hit );

  TEST_FLOATING_EQUALITY( distance_to_surface_hit, 17.526, 1e-6 );
  TEST_EQUALITY_CONST( surface_hit, 394 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  std::string test_geom_xml_file_name;

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

  // Initialize the global MPI session
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  out->setProcRankAndSize( mpiSession.getRank(), mpiSession.getNProc() );
  out->setOutputToRootOnly( 0 );
  
  // Initialize DagMC
  Teuchos::RCP<Teuchos::ParameterList> geom_rep = 
    Teuchos::getParametersFromXmlFile( test_geom_xml_file_name );

  Geometry::DagMCInstanceFactory::initializeDagMC( *geom_rep );
  
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
// end tstModuleInterface.cpp
//---------------------------------------------------------------------------//

