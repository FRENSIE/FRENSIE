//---------------------------------------------------------------------------//
//! 
//! \file   tstModuleInterface.cpp
//! \author Alex Robinson, Eli Moll
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
#include <Teuchos_ScalarTraits.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Geometry_RootInstanceFactory.hpp"
#include "Geometry_ModuleInterface_Root.hpp"
#include "Geometry_Ray.hpp"

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the interface can be initialized
TEUCHOS_UNIT_TEST( ModuleInterface, initialize )
{
  // Initialize the Module Interface
  TEST_NOTHROW( Geometry::ModuleInterface<Geometry::Root>::initialize() );
}

//---------------------------------------------------------------------------//
// Check if the cell exists
TEUCHOS_UNIT_TEST( ModuleInterface, doesCellExist )
{
  typedef Geometry::ModuleInterface<Geometry::Root> GMI;
  
  TEST_ASSERT( GMI::doesCellExist( 1 ) );
  TEST_ASSERT( GMI::doesCellExist( 2 ) );
  TEST_ASSERT( GMI::doesCellExist( 3 ) );
  
  TEST_ASSERT( !GMI::doesCellExist( 4 ) );
}

//---------------------------------------------------------------------------//
// Check if the surface exists
TEUCHOS_UNIT_TEST( ModuleInterface, doesSurfaceExist )
{
  typedef Geometry::ModuleInterface<Geometry::Root> GMI;

  TEST_ASSERT( !GMI::doesSurfaceExist( 1 ) );
  TEST_ASSERT( !GMI::doesSurfaceExist( 2 ) );
  TEST_ASSERT( !GMI::doesSurfaceExist( 3 ) );
  TEST_ASSERT( !GMI::doesSurfaceExist( 4 ) );
}

//---------------------------------------------------------------------------//
// Check that an internal ray can be set
TEUCHOS_UNIT_TEST( ModuleInterface, setInternalRay )
{
  {
    std::shared_ptr<Geometry::Ray> 
      ray( new Geometry::Ray( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 ) );

    Geometry::ModuleInterface<Geometry::Root>::setInternalRay( *ray, 2 );
  }

  const double* ray_position = 
    Geometry::ModuleInterface<Geometry::Root>::getInternalRayPosition();
  
  TEST_EQUALITY_CONST( ray_position[0], 0.0 );
  TEST_EQUALITY_CONST( ray_position[1], 0.0 );
  TEST_EQUALITY_CONST( ray_position[2], 0.0 );

  const double* ray_direction =
    Geometry::ModuleInterface<Geometry::Root>::getInternalRayDirection();

  TEST_EQUALITY_CONST( ray_direction[0], 0.0 );
  TEST_EQUALITY_CONST( ray_direction[1], 0.0 );
  TEST_EQUALITY_CONST( ray_direction[2], 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the cell containing the start ray can be found
TEUCHOS_UNIT_TEST( ModuleInterface, findCellContainingStartRay )
{
  // Initialize the ray
  std::shared_ptr<Geometry::Ray> 
    ray( new Geometry::Ray( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 ) );

  Geometry::ModuleTraits::InternalCellHandle cell;

  cell = Geometry::ModuleInterface<Geometry::Root>::findCellContainingStartRay( *ray );

  TEST_EQUALITY_CONST( cell, 2 );

  // Check that the direction is used to correctly determine the cell when
  // on a boundary
  ray.reset( new Geometry::Ray( 0.0, 0.0, 2.5, 0.0, 0.0, 1.0 ) );

  cell = Geometry::ModuleInterface<Geometry::Root>::findCellContainingStartRay( *ray );

  TEST_EQUALITY_CONST( cell, 1 );

  ray.reset( new Geometry::Ray( 0.0, 0.0, 2.5, 0.0, 0.0, -1.0 ) );

  cell = Geometry::ModuleInterface<Geometry::Root>::findCellContainingStartRay( *ray );

  TEST_EQUALITY_CONST( cell, 2 );
}

//---------------------------------------------------------------------------//
// Check that the cell containing the internal ray can be found
TEUCHOS_UNIT_TEST( ModuleInterface, findCellContainingInternalRay )
{
  // Initialize the ray
  std::shared_ptr<Geometry::Ray> 
    ray( new Geometry::Ray( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 ) );

  Geometry::ModuleInterface<Geometry::Root>::setInternalRay( *ray, 2 );

  Geometry::ModuleTraits::InternalCellHandle cell;

  cell = Geometry::ModuleInterface<Geometry::Root>::findCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 2 );

  // Initialize the ray
  ray.reset( new Geometry::Ray( 0.0, 0.0, 3.0, 0.0, 0.0, 1.0 ) );

  Geometry::ModuleInterface<Geometry::Root>::setInternalRay( *ray, 1 );

  cell = Geometry::ModuleInterface<Geometry::Root>::findCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 1 );

  // Initialize the ray
  ray.reset( new Geometry::Ray( 0.0, 0.0, 6.0, 0.0, 0.0, 1.0 ) );

  Geometry::ModuleInterface<Geometry::Root>::setInternalRay( *ray, 3 );

  cell = Geometry::ModuleInterface<Geometry::Root>::findCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 3 );
}

//---------------------------------------------------------------------------//
// Check that the internal ray can be fired
TEUCHOS_UNIT_TEST( ModuleInterface, fireInternalRay )
{
  // Initialize the ray
  Geometry::Ray ray( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 );

  Geometry::ModuleInterface<Geometry::Root>::setInternalRay( ray, 2 );

  // Fire a ray through the geometry
  Geometry::ModuleTraits::InternalSurfaceHandle surface_hit;
  
  double distance_to_boundary = 
    Geometry::ModuleInterface<Geometry::Root>::fireInternalRay( surface_hit );
  
  // Dummy return surface
  TEST_EQUALITY_CONST( surface_hit, 0 );
  TEST_FLOATING_EQUALITY( distance_to_boundary, 2.5, 1e-9 );
}

//---------------------------------------------------------------------------//
// Check that the internal ray can be advanced to a surface boundary
TEUCHOS_UNIT_TEST( ModuleInterface, advanceInternalRayToCellBoundary )
{
  // Initialize the ray
  {
    Geometry::Ray ray( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 );

    Geometry::ModuleInterface<Geometry::Root>::setInternalRay( ray, 2 );
  }

  // Find the cell that contains the ray
  Geometry::ModuleTraits::InternalCellHandle cell = 
    Geometry::ModuleInterface<Geometry::Root>::findCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 2 );

  // Advance the ray to the boundary surface
  double surface_normal[3];

  bool reflection = 
    Geometry::ModuleInterface<Geometry::Root>::advanceInternalRayToCellBoundary( surface_normal );

  TEST_ASSERT( !reflection );
  
  // Dummy surface normal
  TEST_EQUALITY_CONST( surface_normal[0], 0.0 );
  TEST_EQUALITY_CONST( surface_normal[1], 0.0 );
  TEST_EQUALITY_CONST( surface_normal[2], 1.0 );

  cell = Geometry::ModuleInterface<Geometry::Root>::findCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 1 );
}

//---------------------------------------------------------------------------//
// Check that the internal ray can be advanced by a substep
TEUCHOS_UNIT_TEST( ModuleInterface, advanceInternalRayBySubstep )
{
  // Initialize the ray
  {
    Geometry::Ray ray( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 );

    Geometry::ModuleInterface<Geometry::Root>::setInternalRay( ray, 2 );
  }

  // Find the cell that contains the ray
  Geometry::ModuleTraits::InternalCellHandle cell = 
    Geometry::ModuleInterface<Geometry::Root>::findCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 2 );

  // Fire a ray through the geometry
  Geometry::ModuleTraits::InternalSurfaceHandle surface_hit;
  
  double distance_to_boundary = 
    Geometry::ModuleInterface<Geometry::Root>::fireInternalRay( surface_hit );

  // Advance the internal ray by the substep
  Geometry::ModuleInterface<Geometry::Root>::advanceInternalRayBySubstep( 
                                                    0.5*distance_to_boundary );

  // Fire a ray through the geometry
  distance_to_boundary = 
    Geometry::ModuleInterface<Geometry::Root>::fireInternalRay( surface_hit );

  TEST_FLOATING_EQUALITY( distance_to_boundary, 1.25, 1e-6 );
}

//---------------------------------------------------------------------------//
// Check that the internal ray direction can be changed
TEUCHOS_UNIT_TEST( ModuleInterface, changeInternalRayDirection )
{
  // Initailize the ray
  std::shared_ptr<Geometry::Ray> ray( 
                           new Geometry::Ray( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 ) );
    
  Geometry::ModuleInterface<Geometry::Root>::setInternalRay( *ray, 2 );

  ray.reset( new Geometry::Ray( 0.0, 0.0, 0.0, 1.0, 0.0, 0.0 ) );
  
  Geometry::ModuleInterface<Geometry::Root>::changeInternalRayDirection( 
                                                         ray->getDirection() );

  const double* ray_direction = 
    Geometry::ModuleInterface<Geometry::Root>::getInternalRayDirection();

  TEST_EQUALITY_CONST( ray_direction[0], 1.0 );
  TEST_EQUALITY_CONST( ray_direction[1], 0.0 );
  TEST_EQUALITY_CONST( ray_direction[2], 0.0 );
}

//---------------------------------------------------------------------------//
// Check that termination cells can be tested
TEUCHOS_UNIT_TEST( ModuleInterface, isTerminationCell )
{
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::Root>::isTerminationCell( 1 ) );
  TEST_ASSERT( !Geometry::ModuleInterface<Geometry::Root>::isTerminationCell( 2 ) );
  TEST_ASSERT( Geometry::ModuleInterface<Geometry::Root>::isTerminationCell( 3 ) );
}

//---------------------------------------------------------------------------//
// Check that the point location can be tested
TEUCHOS_UNIT_TEST( ModuleInterface, getPointLocation )
{
  // Initialize the ray
  std::shared_ptr<Geometry::Ray> 
    ray( new Geometry::Ray( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 ) );

  // Point inside of cell 2
  Geometry::PointLocation location =
    Geometry::ModuleInterface<Geometry::Root>::getPointLocation( *ray, 2 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_INSIDE_CELL );

  location = 
    Geometry::ModuleInterface<Geometry::Root>::getPointLocation( *ray, 1 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_OUTSIDE_CELL );

  location = 
    Geometry::ModuleInterface<Geometry::Root>::getPointLocation( *ray, 3 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_OUTSIDE_CELL );
}

//---------------------------------------------------------------------------//
// Check that a ray trace can be done
TEUCHOS_UNIT_TEST( ModuleInterface, ray_trace )
{
  // Initialize the ray
  {
    Geometry::Ray ray( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 );

    Geometry::ModuleTraits::InternalCellHandle start_cell = 
      Geometry::ModuleInterface<Geometry::Root>::findCellContainingStartRay(
                                                                         ray );

    Geometry::ModuleInterface<Geometry::Root>::setInternalRay( 
                                                             ray, start_cell );
  }

  Geometry::ModuleTraits::InternalCellHandle cell = 
    Geometry::ModuleInterface<Geometry::Root>::findCellContainingInternalRay();
  
  TEST_EQUALITY_CONST( cell, 2 );

  // Fire a ray through the geometry
  Geometry::ModuleTraits::InternalSurfaceHandle surface_hit;
  
  double distance_to_boundary = 
    Geometry::ModuleInterface<Geometry::Root>::fireInternalRay( surface_hit );

  TEST_FLOATING_EQUALITY( distance_to_boundary, 2.5, 1e-9 );
 
  // Advance the ray to the cell boundary
  double surface_normal[3];
  
  bool reflection = Geometry::ModuleInterface<Geometry::Root>::advanceInternalRayToCellBoundary( surface_normal );

  // Find the new cell
  cell = Geometry::ModuleInterface<Geometry::Root>::findCellContainingInternalRay();
  
  TEST_EQUALITY_CONST( cell, 1 );

  // Fire a ray through the geometry
  distance_to_boundary = Geometry::ModuleInterface<Geometry::Root>::fireInternalRay( surface_hit );

  TEST_FLOATING_EQUALITY( distance_to_boundary, 2.5, 1e-6 );

  // Advance the ray a substep
  Geometry::ModuleInterface<Geometry::Root>::advanceInternalRayBySubstep( 0.5*distance_to_boundary );

  // Change the ray direction
  {
    double new_direction[3] = {0.0, 1.0, 0.0};

    Geometry::ModuleInterface<Geometry::Root>::changeInternalRayDirection( 
                                                               new_direction );
  }

  // Fire a ray through the geometry
  distance_to_boundary = 
    Geometry::ModuleInterface<Geometry::Root>::fireInternalRay( surface_hit );

  TEST_FLOATING_EQUALITY( distance_to_boundary, 5.0, 1e-9 );

  // Advance the ray to the cell boundary
  reflection = Geometry::ModuleInterface<Geometry::Root>::advanceInternalRayToCellBoundary( surface_normal );
  
  // Find the new cell
  cell = Geometry::ModuleInterface<Geometry::Root>::findCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 3 );
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

  // Initialize Root
  Teuchos::RCP<Teuchos::ParameterList> geom_rep = 
    Teuchos::getParametersFromXmlFile( test_geom_xml_file_name );
  
  Geometry::RootInstanceFactory::initializeRoot( *geom_rep );
  
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

