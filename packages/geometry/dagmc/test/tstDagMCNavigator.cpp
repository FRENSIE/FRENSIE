//---------------------------------------------------------------------------//
//!
//! \file tstDagMCNavigator.cpp
//! \author Alex Robinson
//! \brief  DagMC navigator class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Geometry_DagMCNavigator.hpp"
#include "Geometry_DagMCModel.hpp"
#include "Geometry_DagMCModelPropertiesFactory.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<const Geometry::DagMCModel> model;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the point location w.r.t. a given cell can be returned
TEUCHOS_UNIT_TEST( DagMCNavigator, getPointLocation )
{
  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator();
  
  // Initialize the ray
  std::shared_ptr<Geometry::Ray> ray( new Geometry::Ray(
                                         -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 ) );

  Geometry::PointLocation location =
    navigator->getPointLocation( *ray, 53 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_INSIDE_CELL );

  ray.reset( new Geometry::Ray( -42.647, -40.0, 59.0, -1.0, 0.0, 0.0 ) );

  location = navigator->getPointLocation( *ray, 53 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_INSIDE_CELL );

  ray.reset( new Geometry::Ray( -42.648, -40.0, 59.0, -1.0, 0.0, 0.0 ) );

  location = navigator->getPointLocation( *ray, 53 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_OUTSIDE_CELL );
}

//---------------------------------------------------------------------------//
// Check that the surface normal can be found
TEUCHOS_UNIT_TEST( DagMCNavigator, getSurfaceNormal )
{
  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator();
  
  // Initialize the ray (on cell 53)
  Geometry::Ray ray( -40.0, -40.0, 60.959999084, 0.0, 0.0, 1.0 );

  // Get the surface normal
  Teuchos::Tuple<double,3> normal;

  navigator->getSurfaceNormal( 242,
                               ray.getPosition(),
                               ray.getDirection(),
                               normal.getRawPtr() );

  Teuchos::Tuple<double,3> ref_normal = Teuchos::tuple( 0.0, 0.0, 1.0 );

  TEST_COMPARE_ARRAYS( normal, ref_normal );
}

//---------------------------------------------------------------------------//
// Check that the boundary cell can be found
TEUCHOS_UNIT_TEST( DagMCNavigator, getBoundaryCell )
{
  std::shared_ptr<Geometry::DagMCNavigator>
    navigator( model->createNavigatorAdvanced() );
  
  TEST_EQUALITY_CONST( navigator->getBoundaryCell( 53, 242 ), 54 );
  TEST_EQUALITY_CONST( navigator->getBoundaryCell( 54, 248 ), 55 );
}

//---------------------------------------------------------------------------//
// Check that the cell containing the external ray can be found and cached
TEUCHOS_UNIT_TEST( DagMCNavigator, findCellContainingRay_cache )
{
  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator();

  // Initialize the start cell cache
  Geometry::Navigator::CellIdSet found_cell_cache;
  
  // Initialize the ray
  std::shared_ptr<Geometry::Ray> ray(
                      new Geometry::Ray( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 ) );

  // Find the cell that contains the point
  Geometry::ModuleTraits::InternalCellHandle cell =
    navigator->findCellContainingRay( *ray, found_cell_cache );

  TEST_EQUALITY_CONST( cell, 53 );

  // Initailize a new ray
  ray.reset( new Geometry::Ray( -39.0, -39.0, 59.0, 1.0, 0.0, 0.0 ) );

  // Find the cell that contains the point
  cell = navigator->findCellContainingRay( *ray, found_cell_cache );

  TEST_EQUALITY_CONST( cell, 53 );

  // Initailize a new ray
  ray.reset( new Geometry::Ray( -40.0, -40.0, 61.0, 0.0, 0.0, 1.0 ) );

  // Find the cell that contains the point
  cell = navigator->findCellContainingRay( *ray, found_cell_cache );

  TEST_EQUALITY_CONST( cell, 54 );

  // Initialize the new ray
  ray.reset( new Geometry::Ray( -40.0, -40.0, 64.0, 0.0, 0.0, 1.0 ) );

  // Find the cell that contains the point
  cell = navigator->findCellContainingRay( *ray, found_cell_cache );

  TEST_EQUALITY_CONST( cell, 55 );

  // Check the found cell cache
  TEST_EQUALITY_CONST( found_cell_cache.size(), 3 );
  TEST_ASSERT( found_cell_cache.count( 53 ) );
  TEST_ASSERT( found_cell_cache.count( 54 ) );
  TEST_ASSERT( found_cell_cache.count( 55 ) );
}

//---------------------------------------------------------------------------//
// Check that the cell containing the external ray can be found
TEUCHOS_UNIT_TEST( DagMCNavigator, findCellContainingRay )
{
  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator();
  
  // Initialize the ray
  std::shared_ptr<Geometry::Ray> ray(
                      new Geometry::Ray( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 ) );

  // Find the cell that contains the point
  Geometry::ModuleTraits::InternalCellHandle cell =
    navigator->findCellContainingRay( *ray );

  TEST_EQUALITY_CONST( cell, 53 );

  // Initailize a new ray
  ray.reset( new Geometry::Ray( -40.0, -40.0, 61.0, 0.0, 0.0, 1.0 ) );

  // Find the cell that contains the point
  cell = navigator->findCellContainingRay( *ray );

  TEST_EQUALITY_CONST( cell, 54 );

  // Initialize the new ray
  ray.reset( new Geometry::Ray( -40.0, -40.0, 64.0, 0.0, 0.0, 1.0 ) );

  // Find the cell that contains the point
  cell = navigator->findCellContainingRay( *ray );

  TEST_EQUALITY_CONST( cell, 55 );
}

//---------------------------------------------------------------------------//
// Check that the internal ray can be set
TEUCHOS_UNIT_TEST( DagMCNavigator, setInternalRay_unknown_cell )
{
  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator();
  
  TEST_ASSERT( !navigator->isInternalRaySet() );

  std::shared_ptr<Geometry::Ray> ray(
                      new Geometry::Ray( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 ) );

  navigator->setInternalRay( ray->getPosition(), ray->getDirection() );

  TEST_ASSERT( navigator->isInternalRaySet() );
  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[0], -40.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[1], -40.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[2], 59.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[0], 0.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[1], 0.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[2], 1.0 );
  TEST_EQUALITY_CONST( navigator->getCellContainingInternalRay(), 53 );

  ray.reset( new Geometry::Ray( -40.0, -40.0, 61.0, 0.0, 0.0, 1.0 ) );

  navigator->setInternalRay( ray->getPosition(), ray->getDirection() );

  TEST_ASSERT( navigator->isInternalRaySet() );
  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[0], -40.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[1], -40.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[2], 61.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[0], 0.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[1], 0.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[2], 1.0 );
  TEST_EQUALITY_CONST( navigator->getCellContainingInternalRay(), 54 );
}

//---------------------------------------------------------------------------//
// Check that the internal ray can be set
TEUCHOS_UNIT_TEST( DagMCNavigator, setInternalRay_known_cell )
{
  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator();
  
  // Set the internal ray but do not cache its starting cell
  std::shared_ptr<Geometry::Ray> ray(
                      new Geometry::Ray( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 ) );

  TEST_ASSERT( !navigator->isInternalRaySet() );
  
  navigator->setInternalRay( ray->getPosition(),
                             ray->getDirection(),
                             53 );

  TEST_ASSERT( navigator->isInternalRaySet() );
  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[0], -40.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[1], -40.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[2], 59.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[0], 0.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[1], 0.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[2], 1.0 );
  TEST_EQUALITY_CONST( navigator->getCellContainingInternalRay(), 53 );

  ray.reset( new Geometry::Ray( -40.0, -40.0, 61.0, 0.0, 0.0, 1.0 ) );

  navigator->setInternalRay( ray->getPosition(), ray->getDirection(), 54 );

  TEST_ASSERT( navigator->isInternalRaySet() );
  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[0], -40.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[1], -40.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[2], 61.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[0], 0.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[1], 0.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[2], 1.0 );
  TEST_EQUALITY_CONST( navigator->getCellContainingInternalRay(), 54 );
}

//---------------------------------------------------------------------------//
// Check that the internal ray can be fired
TEUCHOS_UNIT_TEST( DagMCNavigator, fireInternalRay )
{
  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator();
  
  // Initialize the ray
  Geometry::Ray ray( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 );

  navigator->setInternalRay( ray.getPosition(), ray.getDirection(), 53 );

  // Fire an external ray through the geometry
  Geometry::ModuleTraits::InternalSurfaceHandle surface_hit;

  double distance_to_surface_hit = navigator->fireInternalRay( &surface_hit );

  TEST_FLOATING_EQUALITY( distance_to_surface_hit, 1.959999084, 1e-9 );
  TEST_EQUALITY_CONST( surface_hit, 242 );
}

//---------------------------------------------------------------------------//
// Check that an internal ray can be advanced by a substep
TEUCHOS_UNIT_TEST( DagMCNavigator, advanceInternalRayBySubstep )
{
  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator();
  
  // Initialize the ray
  navigator->setInternalRay( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0, 53 );

  navigator->advanceInternalRayBySubstep( 0.959999084 );

  // Find the cell that contains the ray
  Geometry::ModuleTraits::InternalCellHandle cell =
    navigator->getCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 53 );

  // Fire the ray
  Geometry::ModuleTraits::InternalSurfaceHandle surface_hit;

  double distance_to_surface_hit =
    navigator->fireInternalRay( &surface_hit );

  TEST_FLOATING_EQUALITY( distance_to_surface_hit, 1.0, 1e-9 );
  TEST_EQUALITY_CONST( surface_hit, 242 );
}

//---------------------------------------------------------------------------//
// Check that an internal ray can be advanced
TEUCHOS_UNIT_TEST( DagMCNavigator, advanceInternalRayToCellBoundary_basic )
{
  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator();
  
  // Initialize the ray
  navigator->setInternalRay( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0, 53 );

  // Find the cell that contains the ray
  Geometry::ModuleTraits::InternalCellHandle cell =
    navigator->getCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 53 );

  // Advance the ray to the boundary surface
  navigator->advanceInternalRayToCellBoundary();

  cell = navigator->getCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 54 );
}

//---------------------------------------------------------------------------//
// Check that an internal ray can be advanced
TEUCHOS_UNIT_TEST( DagMCNavigator, advanceInternalRayToCellBoundary_advanced )
{
  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator();
  
  // Initialize the ray
  navigator->setInternalRay( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0, 53 );

  // Find the cell that contains the ray
  Geometry::ModuleTraits::InternalCellHandle cell =
    navigator->getCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 53 );

  // Advance the ray to the boundary surface
  double surface_normal[3];

  bool reflection =
    navigator->advanceInternalRayToCellBoundary( surface_normal );

  TEST_ASSERT( !reflection );
  TEST_EQUALITY_CONST( surface_normal[0], 0.0 );
  TEST_EQUALITY_CONST( surface_normal[1], 0.0 );
  TEST_EQUALITY_CONST( surface_normal[2], 1.0 );

  cell = navigator->getCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 54 );
}

//---------------------------------------------------------------------------//
// Check that the internal ray direction can be changed
TEUCHOS_UNIT_TEST( DagMCNavigator, changeInternalRayDirection )
{
  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator();
  
  std::shared_ptr<Geometry::Ray> ray(
                      new Geometry::Ray( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 ) );

  navigator->setInternalRay( ray->getPosition(),
                             ray->getDirection(),
                             53 );

  ray.reset( new Geometry::Ray( -40.0, -40.0, 59.0, 1.0, 0.0, 0.0 ) );

  navigator->changeInternalRayDirection( ray->getDirection() );

  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[0], 1.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[1], 0.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[2], 0.0 );
}

//---------------------------------------------------------------------------//
// Check that an internal ray trace can be done
TEUCHOS_UNIT_TEST( DagMCNavigator, ray_trace )
{
  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator();
  
  // Initialize the ray
  navigator->setInternalRay( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 );

  // Find the cell that contains the ray
  Geometry::ModuleTraits::InternalCellHandle cell =
    navigator->getCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 53 );

  // Fire the ray
  Geometry::ModuleTraits::InternalSurfaceHandle surface_hit;

  double distance_to_surface_hit =
    navigator->fireInternalRay( &surface_hit );

  TEST_FLOATING_EQUALITY( distance_to_surface_hit, 1.959999084, 1e-9 );
  TEST_EQUALITY_CONST( surface_hit, 242 );

  // Advance the ray to the boundary surface
  navigator->advanceInternalRayToCellBoundary();

  cell = navigator->getCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 54 );

  // Fire the ray
  distance_to_surface_hit = navigator->fireInternalRay( &surface_hit );

  TEST_FLOATING_EQUALITY( distance_to_surface_hit, 2.54, 1e-6 );
  TEST_EQUALITY_CONST( surface_hit, 248 );

  // Advance the ray to the boundary surface
  navigator->advanceInternalRayToCellBoundary();

  cell = navigator->getCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 55 );

  // Fire the ray
  distance_to_surface_hit = navigator->fireInternalRay( &surface_hit );

  TEST_FLOATING_EQUALITY( distance_to_surface_hit, 2.54, 1e-6 );
  TEST_EQUALITY_CONST( surface_hit, 254 );

  // Advance the ray a substep
  navigator->advanceInternalRayBySubstep( 0.5*distance_to_surface_hit );

  // Change the ray direction
  navigator->changeInternalRayDirection( 0.0, 0.0, -1.0 );

  // Fire the ray
  distance_to_surface_hit = navigator->fireInternalRay( &surface_hit );

  TEST_FLOATING_EQUALITY( distance_to_surface_hit, 1.27, 1e-6 );
  TEST_EQUALITY_CONST( surface_hit, 248 );
}

//---------------------------------------------------------------------------//
// Check that an internal ray trace can be done
TEUCHOS_UNIT_TEST( DagMCNavigator, ray_trace_with_reflection )
{
  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator();
  
  // Initialize the ray
  navigator->setInternalRay( -40.0, -40.0, 108.0, 0.0, 0.0, 1.0 );

  // Find the cell that contains the ray
  Geometry::ModuleTraits::InternalCellHandle cell =
    navigator->getCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 82 );

  // Fire the ray
  Geometry::ModuleTraits::InternalSurfaceHandle surface_hit;

  double distance_to_surface_hit =
    navigator->fireInternalRay( &surface_hit );

  TEST_FLOATING_EQUALITY( distance_to_surface_hit, 1.474, 1e-6 );
  TEST_EQUALITY_CONST( surface_hit, 394 );

  // Advance the ray to the boundary surface
  bool reflection = navigator->advanceInternalRayToCellBoundary();

  TEST_ASSERT( !reflection );

  cell = navigator->getCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 83 );

  distance_to_surface_hit = navigator->fireInternalRay( &surface_hit );

  TEST_FLOATING_EQUALITY( distance_to_surface_hit, 17.526, 1e-6 );
  TEST_EQUALITY_CONST( surface_hit, 408 );

  // Advance the ray to the boundary surface (reflecting)
  double surface_normal[3];

  reflection =
    navigator->advanceInternalRayToCellBoundary( surface_normal );

  TEST_ASSERT( reflection );
  TEST_EQUALITY_CONST( surface_normal[0], 0.0 );
  TEST_EQUALITY_CONST( surface_normal[1], 0.0 );
  TEST_EQUALITY_CONST( surface_normal[2], 1.0 );

  cell = navigator->getCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 83 );

  distance_to_surface_hit = navigator->fireInternalRay( &surface_hit );

  TEST_FLOATING_EQUALITY( distance_to_surface_hit, 17.526, 1e-6 );
  TEST_EQUALITY_CONST( surface_hit, 394 );
}

//---------------------------------------------------------------------------//
// Check that the ray can be cloned
TEUCHOS_UNIT_TEST( DagMCNavigator, clone )
{
  std::shared_ptr<Geometry::Navigator> navigator = model->createNavigator();

  // Initialize the ray
  navigator->setInternalRay( -40.0, -40.0, 108.0, 0.0, 0.0, 1.0 );

  // Clone the ray
  std::shared_ptr<Geometry::Navigator> navigator_clone( navigator->clone() );

  TEST_EQUALITY_CONST( navigator_clone->getInternalRayPosition()[0],
                       navigator->getInternalRayPosition()[0] );
  TEST_EQUALITY_CONST( navigator_clone->getInternalRayPosition()[1],
                       navigator->getInternalRayPosition()[1] );
  TEST_EQUALITY_CONST( navigator_clone->getInternalRayPosition()[2],
                       navigator->getInternalRayPosition()[2] );
  TEST_EQUALITY_CONST( navigator_clone->getInternalRayDirection()[0],
                       navigator->getInternalRayDirection()[0] );
  TEST_EQUALITY_CONST( navigator_clone->getInternalRayDirection()[1],
                       navigator->getInternalRayDirection()[1] );
  TEST_EQUALITY_CONST( navigator_clone->getInternalRayDirection()[2],
                       navigator->getInternalRayDirection()[2] );
  TEST_EQUALITY_CONST( navigator_clone->getCellContainingInternalRay(),
                       navigator->getCellContainingInternalRay() );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string xml_file_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_xml_file",
                   &xml_file_name,
                   "Model properties xml file name" );

}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  Teuchos::RCP<const Teuchos::ParameterList> raw_model_properties =
    Teuchos::getParametersFromXmlFile( xml_file_name );

  std::shared_ptr<const Geometry::DagMCModelProperties> model_properties =
    Geometry::DagMCModelPropertiesFactory::createProperties(
                                                       *raw_model_properties );

  std::shared_ptr<Geometry::DagMCModel> tmp_model =
    Geometry::DagMCModel::getInstance();

  tmp_model->initialize( *model_properties );

  model = tmp_model;
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstDagMCNavigator.cpp
//---------------------------------------------------------------------------//
