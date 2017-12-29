//---------------------------------------------------------------------------//
//!
//! \file tstDagMCNavigator.cpp
//! \author Alex Robinson
//! \brief  DagMC navigator class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <fstream>
#include <memory>

// FRENSIE Includes
#include "Geometry_DagMCNavigator.hpp"
#include "Geometry_DagMCModel.hpp"
#include "Utility_Array.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef std::tuple<
  std::tuple<boost::archive::xml_oarchive,boost::archive::xml_iarchive>,
  std::tuple<boost::archive::text_oarchive,boost::archive::text_iarchive>,
  std::tuple<boost::archive::binary_oarchive,boost::archive::binary_iarchive>,
  std::tuple<Utility::HDF5OArchive,Utility::HDF5IArchive>,
  std::tuple<boost::archive::polymorphic_oarchive*,boost::archive::polymorphic_iarchive*>
  > TestArchives;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<const Geometry::DagMCModel> model;

bool cache_test_archive;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the point location w.r.t. a given cell can be returned
FRENSIE_UNIT_TEST( DagMCNavigator, getPointLocation )
{
  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator();
  
  // Initialize the ray
  std::shared_ptr<Geometry::Ray> ray( new Geometry::Ray(
                                         -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 ) );

  Geometry::PointLocation location =
    navigator->getPointLocation( *ray, 53 );

  FRENSIE_CHECK_EQUAL( location, Geometry::POINT_INSIDE_CELL );

  ray.reset( new Geometry::Ray( -42.647, -40.0, 59.0, -1.0, 0.0, 0.0 ) );

  location = navigator->getPointLocation( *ray, 53 );

  FRENSIE_CHECK_EQUAL( location, Geometry::POINT_INSIDE_CELL );

  ray.reset( new Geometry::Ray( -42.648, -40.0, 59.0, -1.0, 0.0, 0.0 ) );

  location = navigator->getPointLocation( *ray, 53 );

  FRENSIE_CHECK_EQUAL( location, Geometry::POINT_OUTSIDE_CELL );
}

//---------------------------------------------------------------------------//
// Check that the surface normal can be found
FRENSIE_UNIT_TEST( DagMCNavigator, getSurfaceNormal )
{
  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator();
  
  // Initialize the ray (on cell 53)
  Geometry::Ray ray( -40.0, -40.0, 60.959999084, 0.0, 0.0, 1.0 );

  // Get the surface normal
  std::array<double,3> normal;

  navigator->getSurfaceNormal( 242,
                               ray.getPosition(),
                               ray.getDirection(),
                               normal.data() );

  std::array<double,3> ref_normal( {0.0, 0.0, 1.0} );

  FRENSIE_CHECK_EQUAL( normal, ref_normal );
}

//---------------------------------------------------------------------------//
// Check that the boundary cell can be found
FRENSIE_UNIT_TEST( DagMCNavigator, getBoundaryCell )
{
  std::shared_ptr<Geometry::DagMCNavigator>
    navigator( model->createNavigatorAdvanced() );
  
  FRENSIE_CHECK_EQUAL( navigator->getBoundaryCell( 53, 242 ), 54 );
  FRENSIE_CHECK_EQUAL( navigator->getBoundaryCell( 54, 248 ), 55 );
}

//---------------------------------------------------------------------------//
// Check that the cell containing the external ray can be found and cached
FRENSIE_UNIT_TEST( DagMCNavigator, findCellContainingRay_cache )
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

  FRENSIE_CHECK_EQUAL( cell, 53 );

  // Initailize a new ray
  ray.reset( new Geometry::Ray( -39.0, -39.0, 59.0, 1.0, 0.0, 0.0 ) );

  // Find the cell that contains the point
  cell = navigator->findCellContainingRay( *ray, found_cell_cache );

  FRENSIE_CHECK_EQUAL( cell, 53 );

  // Initailize a new ray
  ray.reset( new Geometry::Ray( -40.0, -40.0, 61.0, 0.0, 0.0, 1.0 ) );

  // Find the cell that contains the point
  cell = navigator->findCellContainingRay( *ray, found_cell_cache );

  FRENSIE_CHECK_EQUAL( cell, 54 );

  // Initialize the new ray
  ray.reset( new Geometry::Ray( -40.0, -40.0, 64.0, 0.0, 0.0, 1.0 ) );

  // Find the cell that contains the point
  cell = navigator->findCellContainingRay( *ray, found_cell_cache );

  FRENSIE_CHECK_EQUAL( cell, 55 );

  // Check the found cell cache
  FRENSIE_CHECK_EQUAL( found_cell_cache.size(), 3 );
  FRENSIE_CHECK( found_cell_cache.count( 53 ) );
  FRENSIE_CHECK( found_cell_cache.count( 54 ) );
  FRENSIE_CHECK( found_cell_cache.count( 55 ) );
}

//---------------------------------------------------------------------------//
// Check that the cell containing the external ray can be found
FRENSIE_UNIT_TEST( DagMCNavigator, findCellContainingRay )
{
  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator();
  
  // Initialize the ray
  std::shared_ptr<Geometry::Ray> ray(
                      new Geometry::Ray( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 ) );

  // Find the cell that contains the point
  Geometry::ModuleTraits::InternalCellHandle cell =
    navigator->findCellContainingRay( *ray );

  FRENSIE_CHECK_EQUAL( cell, 53 );

  // Initailize a new ray
  ray.reset( new Geometry::Ray( -40.0, -40.0, 61.0, 0.0, 0.0, 1.0 ) );

  // Find the cell that contains the point
  cell = navigator->findCellContainingRay( *ray );

  FRENSIE_CHECK_EQUAL( cell, 54 );

  // Initialize the new ray
  ray.reset( new Geometry::Ray( -40.0, -40.0, 64.0, 0.0, 0.0, 1.0 ) );

  // Find the cell that contains the point
  cell = navigator->findCellContainingRay( *ray );

  FRENSIE_CHECK_EQUAL( cell, 55 );
}

//---------------------------------------------------------------------------//
// Check that the internal ray can be set
FRENSIE_UNIT_TEST( DagMCNavigator, setInternalRay_unknown_cell )
{
  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator();
  
  FRENSIE_CHECK( !navigator->isInternalRaySet() );

  std::shared_ptr<Geometry::Ray> ray(
                      new Geometry::Ray( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 ) );

  navigator->setInternalRay( ray->getPosition(), ray->getDirection() );

  FRENSIE_CHECK( navigator->isInternalRaySet() );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayPosition()[0], -40.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayPosition()[1], -40.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayPosition()[2], 59.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayDirection()[0], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayDirection()[1], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayDirection()[2], 1.0 );
  FRENSIE_CHECK_EQUAL( navigator->getCellContainingInternalRay(), 53 );

  ray.reset( new Geometry::Ray( -40.0, -40.0, 61.0, 0.0, 0.0, 1.0 ) );

  navigator->setInternalRay( ray->getPosition(), ray->getDirection() );

  FRENSIE_CHECK( navigator->isInternalRaySet() );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayPosition()[0], -40.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayPosition()[1], -40.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayPosition()[2], 61.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayDirection()[0], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayDirection()[1], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayDirection()[2], 1.0 );
  FRENSIE_CHECK_EQUAL( navigator->getCellContainingInternalRay(), 54 );
}

//---------------------------------------------------------------------------//
// Check that the internal ray can be set
FRENSIE_UNIT_TEST( DagMCNavigator, setInternalRay_known_cell )
{
  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator();
  
  // Set the internal ray but do not cache its starting cell
  std::shared_ptr<Geometry::Ray> ray(
                      new Geometry::Ray( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 ) );

  FRENSIE_CHECK( !navigator->isInternalRaySet() );
  
  navigator->setInternalRay( ray->getPosition(),
                             ray->getDirection(),
                             53 );

  FRENSIE_CHECK( navigator->isInternalRaySet() );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayPosition()[0], -40.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayPosition()[1], -40.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayPosition()[2], 59.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayDirection()[0], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayDirection()[1], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayDirection()[2], 1.0 );
  FRENSIE_CHECK_EQUAL( navigator->getCellContainingInternalRay(), 53 );

  ray.reset( new Geometry::Ray( -40.0, -40.0, 61.0, 0.0, 0.0, 1.0 ) );

  navigator->setInternalRay( ray->getPosition(), ray->getDirection(), 54 );

  FRENSIE_CHECK( navigator->isInternalRaySet() );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayPosition()[0], -40.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayPosition()[1], -40.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayPosition()[2], 61.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayDirection()[0], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayDirection()[1], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayDirection()[2], 1.0 );
  FRENSIE_CHECK_EQUAL( navigator->getCellContainingInternalRay(), 54 );
}

//---------------------------------------------------------------------------//
// Check that the internal ray can be fired
FRENSIE_UNIT_TEST( DagMCNavigator, fireInternalRay )
{
  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator();
  
  // Initialize the ray
  Geometry::Ray ray( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 );

  navigator->setInternalRay( ray.getPosition(), ray.getDirection(), 53 );

  // Fire an external ray through the geometry
  Geometry::ModuleTraits::InternalSurfaceHandle surface_hit;

  double distance_to_surface_hit = navigator->fireInternalRay( &surface_hit );

  FRENSIE_CHECK_FLOATING_EQUALITY( distance_to_surface_hit, 1.959999084, 1e-9 );
  FRENSIE_CHECK_EQUAL( surface_hit, 242 );
}

//---------------------------------------------------------------------------//
// Check that an internal ray can be advanced by a substep
FRENSIE_UNIT_TEST( DagMCNavigator, advanceInternalRayBySubstep )
{
  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator();
  
  // Initialize the ray
  navigator->setInternalRay( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0, 53 );

  navigator->advanceInternalRayBySubstep( 0.959999084 );

  // Find the cell that contains the ray
  Geometry::ModuleTraits::InternalCellHandle cell =
    navigator->getCellContainingInternalRay();

  FRENSIE_CHECK_EQUAL( cell, 53 );

  // Fire the ray
  Geometry::ModuleTraits::InternalSurfaceHandle surface_hit;

  double distance_to_surface_hit =
    navigator->fireInternalRay( &surface_hit );

  FRENSIE_CHECK_FLOATING_EQUALITY( distance_to_surface_hit, 1.0, 1e-9 );
  FRENSIE_CHECK_EQUAL( surface_hit, 242 );
}

//---------------------------------------------------------------------------//
// Check that an internal ray can be advanced
FRENSIE_UNIT_TEST( DagMCNavigator, advanceInternalRayToCellBoundary_basic )
{
  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator();
  
  // Initialize the ray
  navigator->setInternalRay( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0, 53 );

  // Find the cell that contains the ray
  Geometry::ModuleTraits::InternalCellHandle cell =
    navigator->getCellContainingInternalRay();

  FRENSIE_CHECK_EQUAL( cell, 53 );

  // Advance the ray to the boundary surface
  navigator->advanceInternalRayToCellBoundary();

  cell = navigator->getCellContainingInternalRay();

  FRENSIE_CHECK_EQUAL( cell, 54 );
}

//---------------------------------------------------------------------------//
// Check that an internal ray can be advanced
FRENSIE_UNIT_TEST( DagMCNavigator, advanceInternalRayToCellBoundary_advanced )
{
  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator();
  
  // Initialize the ray
  navigator->setInternalRay( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0, 53 );

  // Find the cell that contains the ray
  Geometry::ModuleTraits::InternalCellHandle cell =
    navigator->getCellContainingInternalRay();

  FRENSIE_CHECK_EQUAL( cell, 53 );

  // Advance the ray to the boundary surface
  double surface_normal[3];

  bool reflection =
    navigator->advanceInternalRayToCellBoundary( surface_normal );

  FRENSIE_CHECK( !reflection );
  FRENSIE_CHECK_EQUAL( surface_normal[0], 0.0 );
  FRENSIE_CHECK_EQUAL( surface_normal[1], 0.0 );
  FRENSIE_CHECK_EQUAL( surface_normal[2], 1.0 );

  cell = navigator->getCellContainingInternalRay();

  FRENSIE_CHECK_EQUAL( cell, 54 );
}

//---------------------------------------------------------------------------//
// Check that the internal ray direction can be changed
FRENSIE_UNIT_TEST( DagMCNavigator, changeInternalRayDirection )
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

  FRENSIE_CHECK_EQUAL( navigator->getInternalRayDirection()[0], 1.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayDirection()[1], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayDirection()[2], 0.0 );
}

//---------------------------------------------------------------------------//
// Check that an internal ray trace can be done
FRENSIE_UNIT_TEST( DagMCNavigator, ray_trace )
{
  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator();
  
  // Initialize the ray
  navigator->setInternalRay( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 );

  // Find the cell that contains the ray
  Geometry::ModuleTraits::InternalCellHandle cell =
    navigator->getCellContainingInternalRay();

  FRENSIE_CHECK_EQUAL( cell, 53 );

  // Fire the ray
  Geometry::ModuleTraits::InternalSurfaceHandle surface_hit;

  double distance_to_surface_hit =
    navigator->fireInternalRay( &surface_hit );

  FRENSIE_CHECK_FLOATING_EQUALITY( distance_to_surface_hit, 1.959999084, 1e-9 );
  FRENSIE_CHECK_EQUAL( surface_hit, 242 );

  // Advance the ray to the boundary surface
  navigator->advanceInternalRayToCellBoundary();

  cell = navigator->getCellContainingInternalRay();

  FRENSIE_CHECK_EQUAL( cell, 54 );

  // Fire the ray
  distance_to_surface_hit = navigator->fireInternalRay( &surface_hit );

  FRENSIE_CHECK_FLOATING_EQUALITY( distance_to_surface_hit, 2.54, 1e-6 );
  FRENSIE_CHECK_EQUAL( surface_hit, 248 );

  // Advance the ray to the boundary surface
  navigator->advanceInternalRayToCellBoundary();

  cell = navigator->getCellContainingInternalRay();

  FRENSIE_CHECK_EQUAL( cell, 55 );

  // Fire the ray
  distance_to_surface_hit = navigator->fireInternalRay( &surface_hit );

  FRENSIE_CHECK_FLOATING_EQUALITY( distance_to_surface_hit, 2.54, 1e-6 );
  FRENSIE_CHECK_EQUAL( surface_hit, 254 );

  // Advance the ray a substep
  navigator->advanceInternalRayBySubstep( 0.5*distance_to_surface_hit );

  // Change the ray direction
  navigator->changeInternalRayDirection( 0.0, 0.0, -1.0 );

  // Fire the ray
  distance_to_surface_hit = navigator->fireInternalRay( &surface_hit );

  FRENSIE_CHECK_FLOATING_EQUALITY( distance_to_surface_hit, 1.27, 1e-6 );
  FRENSIE_CHECK_EQUAL( surface_hit, 248 );
}

//---------------------------------------------------------------------------//
// Check that an internal ray trace can be done
FRENSIE_UNIT_TEST( DagMCNavigator, ray_trace_with_reflection )
{
  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator();
  
  // Initialize the ray
  navigator->setInternalRay( -40.0, -40.0, 108.0, 0.0, 0.0, 1.0 );

  // Find the cell that contains the ray
  Geometry::ModuleTraits::InternalCellHandle cell =
    navigator->getCellContainingInternalRay();

  FRENSIE_CHECK_EQUAL( cell, 82 );

  // Fire the ray
  Geometry::ModuleTraits::InternalSurfaceHandle surface_hit;

  double distance_to_surface_hit =
    navigator->fireInternalRay( &surface_hit );

  FRENSIE_CHECK_FLOATING_EQUALITY( distance_to_surface_hit, 1.474, 1e-6 );
  FRENSIE_CHECK_EQUAL( surface_hit, 394 );

  // Advance the ray to the boundary surface
  bool reflection = navigator->advanceInternalRayToCellBoundary();

  FRENSIE_CHECK( !reflection );

  cell = navigator->getCellContainingInternalRay();

  FRENSIE_CHECK_EQUAL( cell, 83 );

  distance_to_surface_hit = navigator->fireInternalRay( &surface_hit );

  FRENSIE_CHECK_FLOATING_EQUALITY( distance_to_surface_hit, 17.526, 1e-6 );
  FRENSIE_CHECK_EQUAL( surface_hit, 408 );

  // Advance the ray to the boundary surface (reflecting)
  double surface_normal[3];

  reflection =
    navigator->advanceInternalRayToCellBoundary( surface_normal );

  FRENSIE_CHECK( reflection );
  FRENSIE_CHECK_EQUAL( surface_normal[0], 0.0 );
  FRENSIE_CHECK_EQUAL( surface_normal[1], 0.0 );
  FRENSIE_CHECK_EQUAL( surface_normal[2], 1.0 );

  cell = navigator->getCellContainingInternalRay();

  FRENSIE_CHECK_EQUAL( cell, 83 );

  distance_to_surface_hit = navigator->fireInternalRay( &surface_hit );

  FRENSIE_CHECK_FLOATING_EQUALITY( distance_to_surface_hit, 17.526, 1e-6 );
  FRENSIE_CHECK_EQUAL( surface_hit, 394 );
}

//---------------------------------------------------------------------------//
// Check that the ray can be cloned
FRENSIE_UNIT_TEST( DagMCNavigator, clone )
{
  std::shared_ptr<Geometry::Navigator> navigator = model->createNavigator();

  // Initialize the ray
  navigator->setInternalRay( -40.0, -40.0, 108.0, 0.0, 0.0, 1.0 );

  // Clone the ray
  std::shared_ptr<Geometry::Navigator> navigator_clone( navigator->clone() );

  FRENSIE_CHECK_EQUAL( navigator_clone->getInternalRayPosition()[0],
                       navigator->getInternalRayPosition()[0] );
  FRENSIE_CHECK_EQUAL( navigator_clone->getInternalRayPosition()[1],
                       navigator->getInternalRayPosition()[1] );
  FRENSIE_CHECK_EQUAL( navigator_clone->getInternalRayPosition()[2],
                       navigator->getInternalRayPosition()[2] );
  FRENSIE_CHECK_EQUAL( navigator_clone->getInternalRayDirection()[0],
                       navigator->getInternalRayDirection()[0] );
  FRENSIE_CHECK_EQUAL( navigator_clone->getInternalRayDirection()[1],
                       navigator->getInternalRayDirection()[1] );
  FRENSIE_CHECK_EQUAL( navigator_clone->getInternalRayDirection()[2],
                       navigator->getInternalRayDirection()[2] );
  FRENSIE_CHECK_EQUAL( navigator_clone->getCellContainingInternalRay(),
                       navigator->getCellContainingInternalRay() );
}

//---------------------------------------------------------------------------//
// Check that a navigator can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( DagMCNavigator, archive, TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_name( "test_dagmc_navigator" );
  std::ostringstream archive_ostream;

  std::unique_ptr<OArchive> oarchive;

  createOArchive( archive_name, archive_ostream, oarchive );

  std::shared_ptr<Geometry::Navigator> navigator = model->createNavigator();

  // Initialize the ray
  navigator->setInternalRay( -40.0, -40.0, 108.0, 0.0, 0.0, 1.0 );

  FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( navigator ) );

  if( cache_test_archive && archive_name.find(".h5a") >= archive_name.size() )
  {
    std::unique_ptr<std::ofstream> ofstream;
    
    if( archive_name.find( ".bin" ) < archive_name.size() )
    {
      ofstream.reset( new std::ofstream( archive_name, std::ofstream::binary ) );
    }
    else
    {
      ofstream.reset( new std::ofstream( archive_name ) );
    }

    (*ofstream) << archive_ostream.str();
  }
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_dagmc_geom_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_cad_file",
                                        test_dagmc_geom_file_name, "",
                                        "Test CAD file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "cache_test_archive",
                                        cache_test_archive, false,
                                        "Cache the test archive" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  Geometry::DagMCModelProperties local_properties( test_dagmc_geom_file_name );
  
  local_properties.setFacetTolerance( 1e-3 );
  local_properties.setTerminationCellPropertyName( "graveyard" );
  local_properties.setMaterialPropertyName( "mat" );
  local_properties.setDensityPropertyName( "rho" );
  local_properties.setEstimatorPropertyName( "tally" );
  
  std::shared_ptr<Geometry::DagMCModel> tmp_model =
    Geometry::DagMCModel::getInstance();

  tmp_model->initialize( local_properties );

  model = tmp_model;
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstDagMCNavigator.cpp
//---------------------------------------------------------------------------//
