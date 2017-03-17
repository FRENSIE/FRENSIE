//---------------------------------------------------------------------------//
//!
//! \file   tstRootNavigator.cpp
//! \author Alex Robinson
//! \brief  Root navigator class unit tests
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
#include "Geometry_RootNavigator.hpp"
#include "Geometry_RootModel.hpp"
#include "Geometry_RootModelPropertiesFactory.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<const Geometry::RootModel> model;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a point location w.r.t. a given cell can be determined
TEUCHOS_UNIT_TEST( RootNavigator, getPointLocation )
{
  std::shared_ptr<Geometry::Navigator> navigator = model->createNavigator();
  
  // Initialize the ray
  std::shared_ptr<Geometry::Ray>
    ray( new Geometry::Ray( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 ) );

  // Point inside of cell 2
  Geometry::PointLocation location =
    navigator->getPointLocation( *ray, 2 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_INSIDE_CELL );

  location = navigator->getPointLocation( *ray, 1 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_OUTSIDE_CELL );

  location = navigator->getPointLocation( *ray, 3 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_OUTSIDE_CELL );

  // Point on boundary between cell 2 and cell 1
  ray.reset( new Geometry::Ray( 0.0, 0.0, 2.5, 0.0, 0.0, 1.0 ) );

  location = navigator->getPointLocation( *ray, 2 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_INSIDE_CELL );

  location = navigator->getPointLocation( *ray, 1 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_OUTSIDE_CELL );

  location = navigator->getPointLocation( *ray, 3 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_OUTSIDE_CELL );

  // Point in cell 1
  ray.reset( new Geometry::Ray( 0.0, 0.0, 4.0, 0.0, 0.0, 1.0 ) );

  location = navigator->getPointLocation( ray->getPosition(),
                                          ray->getDirection(),
                                          2 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_OUTSIDE_CELL );

  location = navigator->getPointLocation( ray->getPosition(),
                                          ray->getDirection(),
                                          1 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_INSIDE_CELL );

  location = navigator->getPointLocation( ray->getPosition(),
                                          ray->getDirection(),
                                          3 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_OUTSIDE_CELL );

  // Point on boundary between cell 1 and 3
  ray.reset( new Geometry::Ray( 0.0, 0.0, 5.0, 0.0, 0.0, 1.0 ) );

  location = navigator->getPointLocation( ray->getPosition(),
                                          ray->getDirection(),
                                          2 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_OUTSIDE_CELL );

  location = navigator->getPointLocation( ray->getPosition(),
                                          ray->getDirection(),
                                          1 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_INSIDE_CELL );

  location = navigator->getPointLocation( ray->getPosition(),
                                          ray->getDirection(),
                                          3 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_OUTSIDE_CELL );

  // Point in cell 3
  ray.reset( new Geometry::Ray( 0.0, 0.0, 6.0, 0.0, 0.0, 1.0 ) );

  location = navigator->getPointLocation( ray->getPosition(),
                                          ray->getDirection(),
                                          2 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_OUTSIDE_CELL );

  location = navigator->getPointLocation( ray->getPosition(),
                                          ray->getDirection(),
                                          1 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_OUTSIDE_CELL );

  location = navigator->getPointLocation( ray->getPosition(),
                                          ray->getDirection(),
                                          3 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_INSIDE_CELL );
}

//---------------------------------------------------------------------------//
// Check that the surface normal can be returned
TEUCHOS_UNIT_TEST( RootNavigator, getSurfaceNormal )
{
  std::shared_ptr<Geometry::Navigator> navigator = model->createNavigator();

  std::shared_ptr<Geometry::Ray>
    ray( new Geometry::Ray( 2.5, 0.0, 0.0, 1.0, 0.0, 0.0 ) );

  double normal[3];

  navigator->getSurfaceNormal( 0, *ray, normal );

  UTILITY_TEST_FLOATING_EQUALITY( normal[0], 1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( normal[1], 0.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( normal[2], 0.0, 1e-15 );

  ray.reset( new Geometry::Ray( 2.5, 0.0, 0.0, -1.0, 0.0, 0.0 ) );

  navigator->getSurfaceNormal( 0, *ray, normal );

  UTILITY_TEST_FLOATING_EQUALITY( normal[0], -1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( normal[1], 0.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( normal[2], 0.0, 1e-15 );
  
  ray.reset( new Geometry::Ray( 2.5, 0.0, 0.0, 1/sqrt(3), 1/sqrt(3), 1/sqrt(3) ) );

  navigator->getSurfaceNormal( 0, *ray, normal );

  UTILITY_TEST_FLOATING_EQUALITY( normal[0], 1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( normal[1], 0.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( normal[2], 0.0, 1e-15 );

  ray.reset( new Geometry::Ray( 2.5, 0.0, 0.0, -1/sqrt(3), -1/sqrt(3), -1/sqrt(3) ) );

  navigator->getSurfaceNormal( 0, *ray, normal );

  UTILITY_TEST_FLOATING_EQUALITY( normal[0], -1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( normal[1], 0.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( normal[2], 0.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the cell containing the external ray can be found can cached
TEUCHOS_UNIT_TEST( RootNavigator, findCellContainingRay_cache )
{
  std::shared_ptr<Geometry::Navigator> navigator = model->createNavigator();

  // Initialize the found cell cache
  Geometry::Navigator::CellIdSet found_cell_cache;
  
  // Initialize the ray
  std::shared_ptr<Geometry::Ray>
    ray( new Geometry::Ray( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 ) );

  Geometry::ModuleTraits::InternalCellHandle cell;

  cell = navigator->findCellContainingRay( *ray, found_cell_cache );

  TEST_EQUALITY_CONST( cell, 2 );

  // Check that the direction is used to correctly determine the cell when
  // on a boundary
  ray.reset( new Geometry::Ray( 0.0, 0.0, 2.5, 0.0, 0.0, 1.0 ) );

  cell = navigator->findCellContainingRay( *ray, found_cell_cache );

  TEST_EQUALITY_CONST( cell, 1 );

  ray.reset( new Geometry::Ray( 0.0, 0.0, 2.5, 0.0, 0.0, -1.0 ) );

  cell = navigator->findCellContainingRay( ray->getPosition(),
                                           ray->getDirection() );

  TEST_EQUALITY_CONST( cell, 2 );

  // Check the found cell cache
  TEST_EQUALITY_CONST( found_cell_cache.size(), 2 );
  TEST_ASSERT( found_cell_cache.count( 1 ) );
  TEST_ASSERT( found_cell_cache.count( 2 ) );
}

//---------------------------------------------------------------------------//
// Check that a cell containing an external ray can be determined
TEUCHOS_UNIT_TEST( RootNavigator, findCellContainingRay )
{
  std::shared_ptr<Geometry::Navigator> navigator = model->createNavigator();
  
  // Initialize the ray
  std::shared_ptr<Geometry::Ray>
    ray( new Geometry::Ray( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 ) );

  Geometry::ModuleTraits::InternalCellHandle cell;

  cell = navigator->findCellContainingRay( *ray );

  TEST_EQUALITY_CONST( cell, 2 );

  // Check that the direction is used to correctly determine the cell when
  // on a boundary
  ray.reset( new Geometry::Ray( 0.0, 0.0, 2.5, 0.0, 0.0, 1.0 ) );

  cell = navigator->findCellContainingRay( *ray );

  TEST_EQUALITY_CONST( cell, 1 );

  ray.reset( new Geometry::Ray( 0.0, 0.0, 2.5, 0.0, 0.0, -1.0 ) );

  cell = navigator->findCellContainingRay( ray->getPosition(),
                                           ray->getDirection() );

  TEST_EQUALITY_CONST( cell, 2 );
}

//---------------------------------------------------------------------------//
// Check that the internal ray can be set
TEUCHOS_UNIT_TEST( RootNavigator, setInternalRay )
{
  std::shared_ptr<Geometry::Navigator> navigator = model->createNavigator();
  
  std::shared_ptr<Geometry::Ray>
    ray( new Geometry::Ray( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 ) );

  TEST_ASSERT( !navigator->isInternalRaySet() );
  
  navigator->setInternalRay( *ray );

  TEST_ASSERT( navigator->isInternalRaySet() );

  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[0], 0.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[1], 0.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[2], 0.0 );

  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[0], 0.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[1], 0.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[2], 1.0 );

  TEST_EQUALITY_CONST( navigator->getCellContainingInternalRay(), 2 );

  ray.reset( new Geometry::Ray( 1.0, 1.0, 1.0, 0.0, 1.0, 0.0 ) );

  navigator->setInternalRay( ray->getPosition(), ray->getDirection() );

  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[0], 1.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[1], 1.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[2], 1.0 );

  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[0], 0.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[1], 1.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[2], 0.0 );

  TEST_EQUALITY_CONST( navigator->getCellContainingInternalRay(), 2 );

  navigator->setInternalRay( -1.0, -1.0, -1.0, 1.0, 0.0, 0.0, 2 );

  // Check that the internal ray state does not change is a find call is made
  ray.reset( new Geometry::Ray( 0.0, 0.0, 2.5, 0.0, 0.0, 1.0 ) );
  Geometry::ModuleTraits::InternalCellHandle cell =
    navigator->findCellContainingRay( *ray );

  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[0], -1.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[1], -1.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[2], -1.0 );

  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[0], 1.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[1], 0.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[2], 0.0 );

  TEST_EQUALITY_CONST( cell, 1 );
  TEST_EQUALITY_CONST( navigator->getCellContainingInternalRay(), 2 );
}

//---------------------------------------------------------------------------//
// Check that an internal ray can be fired
TEUCHOS_UNIT_TEST( RootNavigator, fireInternalRay )
{
  std::shared_ptr<Geometry::Navigator> navigator = model->createNavigator();
  
  // Initialize the ray
  navigator->setInternalRay( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 );

  // Fire a ray through the geometry
  double distance_to_boundary = navigator->fireInternalRay();

  TEST_FLOATING_EQUALITY( distance_to_boundary, 2.5, 1e-9 );
}

//---------------------------------------------------------------------------//
// Check that the internal ray direction can be changed
TEUCHOS_UNIT_TEST( RootNavigator, changeInternalRayDirection )
{
  std::shared_ptr<Geometry::Navigator> navigator = model->createNavigator();
  
  // Initailize the ray
  navigator->setInternalRay( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 );

  navigator->changeInternalRayDirection( 1.0, 0.0, 0.0 );

  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[0], 1.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[1], 0.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[2], 0.0 );

  {
    const double direction[3] = {0.0, 1.0, 0.0};

    navigator->changeInternalRayDirection( direction );
  }

  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[0], 0.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[1], 1.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[2], 0.0 );
}

//---------------------------------------------------------------------------//
// Check that a simple internal ray trace can be done
TEUCHOS_UNIT_TEST( RootNavigator, ray_trace )
{
  std::shared_ptr<Geometry::Navigator> navigator = model->createNavigator();
  
  // Initialize the ray
  navigator->setInternalRay( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 );

  Geometry::ModuleTraits::InternalCellHandle cell =
    navigator->getCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 2 );

  // Fire a ray through the geometry
  double distance_to_boundary = navigator->fireInternalRay();

  TEST_FLOATING_EQUALITY( distance_to_boundary, 2.5, 1e-9 );

  double surface_normal[3];
  
  // Advance the ray to the cell boundary
  navigator->advanceInternalRayToCellBoundary( surface_normal );

  TEST_EQUALITY_CONST( surface_normal[0], 0.0 );
  TEST_EQUALITY_CONST( surface_normal[1], 0.0 );
  TEST_EQUALITY_CONST( surface_normal[2], 1.0 );

  // Find the new cell
  cell = navigator->getCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 1 );

  // Fire a ray through the geometry
  distance_to_boundary = navigator->fireInternalRay();

  TEST_FLOATING_EQUALITY( distance_to_boundary, 2.5, 1e-6 );

  // Advance the ray a substep
  navigator->advanceInternalRayBySubstep( 0.5*distance_to_boundary );

  // Change the ray direction
  navigator->changeInternalRayDirection( 0.0, 1.0, 0.0 );

  // Fire a ray through the geometry
  distance_to_boundary = navigator->fireInternalRay();

  TEST_FLOATING_EQUALITY( distance_to_boundary, 5.0, 1e-9 );

  // Advance the ray to the cell boundary
  navigator->advanceInternalRayToCellBoundary();

  // Find the new cell
  cell = navigator->getCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 3 );
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

  std::shared_ptr<const Geometry::RootModelProperties> model_properties =
    Geometry::RootModelPropertiesFactory::createProperties(
                                                       *raw_model_properties );

  std::shared_ptr<Geometry::RootModel> tmp_model =
    Geometry::RootModel::getInstance();

  tmp_model->initialize( *model_properties );

  model = tmp_model;
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstRootNavigator.cpp
//---------------------------------------------------------------------------//
