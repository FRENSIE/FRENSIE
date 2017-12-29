//---------------------------------------------------------------------------//
//!
//! \file   tstRootNavigator.cpp
//! \author Alex Robinson
//! \brief  Root navigator class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <fstream>
#include <memory>

// FRENSIE Includes
#include "Geometry_RootNavigator.hpp"
#include "Geometry_RootModel.hpp"
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
std::shared_ptr<const Geometry::RootModel> model;

bool cache_test_archive;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a point location w.r.t. a given cell can be determined
FRENSIE_UNIT_TEST( RootNavigator, getPointLocation )
{
  std::shared_ptr<Geometry::Navigator> navigator = model->createNavigator();
  
  // Initialize the ray
  std::shared_ptr<Geometry::Ray>
    ray( new Geometry::Ray( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 ) );

  // Point inside of cell 2
  Geometry::PointLocation location =
    navigator->getPointLocation( *ray, 2 );

  FRENSIE_CHECK_EQUAL( location, Geometry::POINT_INSIDE_CELL );

  location = navigator->getPointLocation( *ray, 1 );

  FRENSIE_CHECK_EQUAL( location, Geometry::POINT_OUTSIDE_CELL );

  location = navigator->getPointLocation( *ray, 3 );

  FRENSIE_CHECK_EQUAL( location, Geometry::POINT_OUTSIDE_CELL );

  // Point on boundary between cell 2 and cell 1
  ray.reset( new Geometry::Ray( 0.0, 0.0, 2.5, 0.0, 0.0, 1.0 ) );

  location = navigator->getPointLocation( *ray, 2 );

  FRENSIE_CHECK_EQUAL( location, Geometry::POINT_INSIDE_CELL );

  location = navigator->getPointLocation( *ray, 1 );

  FRENSIE_CHECK_EQUAL( location, Geometry::POINT_OUTSIDE_CELL );

  location = navigator->getPointLocation( *ray, 3 );

  FRENSIE_CHECK_EQUAL( location, Geometry::POINT_OUTSIDE_CELL );

  // Point in cell 1
  ray.reset( new Geometry::Ray( 0.0, 0.0, 4.0, 0.0, 0.0, 1.0 ) );

  location = navigator->getPointLocation( ray->getPosition(),
                                          ray->getDirection(),
                                          2 );

  FRENSIE_CHECK_EQUAL( location, Geometry::POINT_OUTSIDE_CELL );

  location = navigator->getPointLocation( ray->getPosition(),
                                          ray->getDirection(),
                                          1 );

  FRENSIE_CHECK_EQUAL( location, Geometry::POINT_INSIDE_CELL );

  location = navigator->getPointLocation( ray->getPosition(),
                                          ray->getDirection(),
                                          3 );

  FRENSIE_CHECK_EQUAL( location, Geometry::POINT_OUTSIDE_CELL );

  // Point on boundary between cell 1 and 3
  ray.reset( new Geometry::Ray( 0.0, 0.0, 5.0, 0.0, 0.0, 1.0 ) );

  location = navigator->getPointLocation( ray->getPosition(),
                                          ray->getDirection(),
                                          2 );

  FRENSIE_CHECK_EQUAL( location, Geometry::POINT_OUTSIDE_CELL );

  location = navigator->getPointLocation( ray->getPosition(),
                                          ray->getDirection(),
                                          1 );

  FRENSIE_CHECK_EQUAL( location, Geometry::POINT_INSIDE_CELL );

  location = navigator->getPointLocation( ray->getPosition(),
                                          ray->getDirection(),
                                          3 );

  FRENSIE_CHECK_EQUAL( location, Geometry::POINT_OUTSIDE_CELL );

  // Point in cell 3
  ray.reset( new Geometry::Ray( 0.0, 0.0, 6.0, 0.0, 0.0, 1.0 ) );

  location = navigator->getPointLocation( ray->getPosition(),
                                          ray->getDirection(),
                                          2 );

  FRENSIE_CHECK_EQUAL( location, Geometry::POINT_OUTSIDE_CELL );

  location = navigator->getPointLocation( ray->getPosition(),
                                          ray->getDirection(),
                                          1 );

  FRENSIE_CHECK_EQUAL( location, Geometry::POINT_OUTSIDE_CELL );

  location = navigator->getPointLocation( ray->getPosition(),
                                          ray->getDirection(),
                                          3 );

  FRENSIE_CHECK_EQUAL( location, Geometry::POINT_INSIDE_CELL );
}

//---------------------------------------------------------------------------//
// Check that the surface normal can be returned
FRENSIE_UNIT_TEST( RootNavigator, getSurfaceNormal )
{
  std::shared_ptr<Geometry::Navigator> navigator = model->createNavigator();

  std::shared_ptr<Geometry::Ray>
    ray( new Geometry::Ray( 2.5, 0.0, 0.0, 1.0, 0.0, 0.0 ) );

  double normal[3];

  navigator->getSurfaceNormal( 0, *ray, normal );

  FRENSIE_CHECK_FLOATING_EQUALITY( normal[0], 1.0, 1e-15 );
  FRENSIE_CHECK_SMALL( normal[1], 1e-15 );
  FRENSIE_CHECK_SMALL( normal[2], 1e-15 );

  ray.reset( new Geometry::Ray( 2.5, 0.0, 0.0, -1.0, 0.0, 0.0 ) );

  navigator->getSurfaceNormal( 0, *ray, normal );

  FRENSIE_CHECK_FLOATING_EQUALITY( normal[0], -1.0, 1e-15 );
  FRENSIE_CHECK_SMALL( normal[1], 1e-15 );
  FRENSIE_CHECK_SMALL( normal[2], 1e-15 );
  
  ray.reset( new Geometry::Ray( 2.5, 0.0, 0.0, 1/sqrt(3), 1/sqrt(3), 1/sqrt(3) ) );

  navigator->getSurfaceNormal( 0, *ray, normal );

  FRENSIE_CHECK_FLOATING_EQUALITY( normal[0], 1.0, 1e-15 );
  FRENSIE_CHECK_SMALL( normal[1], 1e-15 );
  FRENSIE_CHECK_SMALL( normal[2], 1e-15 );

  ray.reset( new Geometry::Ray( 2.5, 0.0, 0.0, -1/sqrt(3), -1/sqrt(3), -1/sqrt(3) ) );

  navigator->getSurfaceNormal( 0, *ray, normal );

  FRENSIE_CHECK_FLOATING_EQUALITY( normal[0], -1.0, 1e-15 );
  FRENSIE_CHECK_SMALL( normal[1], 1e-15 );
  FRENSIE_CHECK_SMALL( normal[2], 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the cell containing the external ray can be found can cached
FRENSIE_UNIT_TEST( RootNavigator, findCellContainingRay_cache )
{
  std::shared_ptr<Geometry::Navigator> navigator = model->createNavigator();

  // Initialize the found cell cache
  Geometry::Navigator::CellIdSet found_cell_cache;
  
  // Initialize the ray
  std::shared_ptr<Geometry::Ray>
    ray( new Geometry::Ray( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 ) );

  Geometry::ModuleTraits::InternalCellHandle cell;

  cell = navigator->findCellContainingRay( *ray, found_cell_cache );

  FRENSIE_CHECK_EQUAL( cell, 2 );

  // Check that the direction is used to correctly determine the cell when
  // on a boundary
  ray.reset( new Geometry::Ray( 0.0, 0.0, 2.5, 0.0, 0.0, 1.0 ) );

  cell = navigator->findCellContainingRay( *ray, found_cell_cache );

  FRENSIE_CHECK_EQUAL( cell, 1 );

  ray.reset( new Geometry::Ray( 0.0, 0.0, 2.5, 0.0, 0.0, -1.0 ) );

  cell = navigator->findCellContainingRay( ray->getPosition(),
                                           ray->getDirection() );

  FRENSIE_CHECK_EQUAL( cell, 2 );

  // Check the found cell cache
  FRENSIE_CHECK_EQUAL( found_cell_cache.size(), 2 );
  FRENSIE_CHECK( found_cell_cache.count( 1 ) );
  FRENSIE_CHECK( found_cell_cache.count( 2 ) );
}

//---------------------------------------------------------------------------//
// Check that a cell containing an external ray can be determined
FRENSIE_UNIT_TEST( RootNavigator, findCellContainingRay )
{
  std::shared_ptr<Geometry::Navigator> navigator = model->createNavigator();
  
  // Initialize the ray
  std::shared_ptr<Geometry::Ray>
    ray( new Geometry::Ray( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 ) );

  Geometry::ModuleTraits::InternalCellHandle cell;

  cell = navigator->findCellContainingRay( *ray );

  FRENSIE_CHECK_EQUAL( cell, 2 );

  // Check that the direction is used to correctly determine the cell when
  // on a boundary
  ray.reset( new Geometry::Ray( 0.0, 0.0, 2.5, 0.0, 0.0, 1.0 ) );

  cell = navigator->findCellContainingRay( *ray );

  FRENSIE_CHECK_EQUAL( cell, 1 );

  ray.reset( new Geometry::Ray( 0.0, 0.0, 2.5, 0.0, 0.0, -1.0 ) );

  cell = navigator->findCellContainingRay( ray->getPosition(),
                                           ray->getDirection() );

  FRENSIE_CHECK_EQUAL( cell, 2 );
}

//---------------------------------------------------------------------------//
// Check that the internal ray can be set
FRENSIE_UNIT_TEST( RootNavigator, setInternalRay )
{
  std::shared_ptr<Geometry::Navigator> navigator = model->createNavigator();
  
  std::shared_ptr<Geometry::Ray>
    ray( new Geometry::Ray( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 ) );

  FRENSIE_CHECK( !navigator->isInternalRaySet() );
  
  navigator->setInternalRay( *ray );

  FRENSIE_CHECK( navigator->isInternalRaySet() );

  FRENSIE_CHECK_EQUAL( navigator->getInternalRayPosition()[0], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayPosition()[1], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayPosition()[2], 0.0 );

  FRENSIE_CHECK_EQUAL( navigator->getInternalRayDirection()[0], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayDirection()[1], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayDirection()[2], 1.0 );

  FRENSIE_CHECK_EQUAL( navigator->getCellContainingInternalRay(), 2 );

  ray.reset( new Geometry::Ray( 1.0, 1.0, 1.0, 0.0, 1.0, 0.0 ) );

  navigator->setInternalRay( ray->getPosition(), ray->getDirection() );

  FRENSIE_CHECK_EQUAL( navigator->getInternalRayPosition()[0], 1.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayPosition()[1], 1.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayPosition()[2], 1.0 );

  FRENSIE_CHECK_EQUAL( navigator->getInternalRayDirection()[0], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayDirection()[1], 1.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayDirection()[2], 0.0 );

  FRENSIE_CHECK_EQUAL( navigator->getCellContainingInternalRay(), 2 );

  navigator->setInternalRay( -1.0, -1.0, -1.0, 1.0, 0.0, 0.0, 2 );

  // Check that the internal ray state does not change is a find call is made
  ray.reset( new Geometry::Ray( 0.0, 0.0, 2.5, 0.0, 0.0, 1.0 ) );
  Geometry::ModuleTraits::InternalCellHandle cell =
    navigator->findCellContainingRay( *ray );

  FRENSIE_CHECK_EQUAL( navigator->getInternalRayPosition()[0], -1.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayPosition()[1], -1.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayPosition()[2], -1.0 );

  FRENSIE_CHECK_EQUAL( navigator->getInternalRayDirection()[0], 1.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayDirection()[1], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayDirection()[2], 0.0 );

  FRENSIE_CHECK_EQUAL( cell, 1 );
  FRENSIE_CHECK_EQUAL( navigator->getCellContainingInternalRay(), 2 );
}

//---------------------------------------------------------------------------//
// Check that an internal ray can be fired
FRENSIE_UNIT_TEST( RootNavigator, fireInternalRay )
{
  std::shared_ptr<Geometry::Navigator> navigator = model->createNavigator();
  
  // Initialize the ray
  navigator->setInternalRay( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 );

  // Fire a ray through the geometry
  double distance_to_boundary = navigator->fireInternalRay();

  FRENSIE_CHECK_FLOATING_EQUALITY( distance_to_boundary, 2.5, 1e-9 );
}

//---------------------------------------------------------------------------//
// Check that the internal ray direction can be changed
FRENSIE_UNIT_TEST( RootNavigator, changeInternalRayDirection )
{
  std::shared_ptr<Geometry::Navigator> navigator = model->createNavigator();
  
  // Initailize the ray
  navigator->setInternalRay( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 );

  navigator->changeInternalRayDirection( 1.0, 0.0, 0.0 );

  FRENSIE_CHECK_EQUAL( navigator->getInternalRayDirection()[0], 1.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayDirection()[1], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayDirection()[2], 0.0 );

  {
    const double direction[3] = {0.0, 1.0, 0.0};

    navigator->changeInternalRayDirection( direction );
  }

  FRENSIE_CHECK_EQUAL( navigator->getInternalRayDirection()[0], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayDirection()[1], 1.0 );
  FRENSIE_CHECK_EQUAL( navigator->getInternalRayDirection()[2], 0.0 );
}

//---------------------------------------------------------------------------//
// Check that a simple internal ray trace can be done
FRENSIE_UNIT_TEST( RootNavigator, ray_trace )
{
  std::shared_ptr<Geometry::Navigator> navigator = model->createNavigator();
  
  // Initialize the ray
  navigator->setInternalRay( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 );

  Geometry::ModuleTraits::InternalCellHandle cell =
    navigator->getCellContainingInternalRay();

  FRENSIE_CHECK_EQUAL( cell, 2 );

  // Fire a ray through the geometry
  double distance_to_boundary = navigator->fireInternalRay();

  FRENSIE_CHECK_FLOATING_EQUALITY( distance_to_boundary, 2.5, 1e-9 );

  double surface_normal[3];
  
  // Advance the ray to the cell boundary
  navigator->advanceInternalRayToCellBoundary( surface_normal );

  FRENSIE_CHECK_EQUAL( surface_normal[0], 0.0 );
  FRENSIE_CHECK_EQUAL( surface_normal[1], 0.0 );
  FRENSIE_CHECK_EQUAL( surface_normal[2], 1.0 );

  // Find the new cell
  cell = navigator->getCellContainingInternalRay();

  FRENSIE_CHECK_EQUAL( cell, 1 );

  // Fire a ray through the geometry
  distance_to_boundary = navigator->fireInternalRay();

  FRENSIE_CHECK_FLOATING_EQUALITY( distance_to_boundary, 2.5, 1e-6 );

  // Advance the ray a substep
  navigator->advanceInternalRayBySubstep( 0.5*distance_to_boundary );

  // Change the ray direction
  navigator->changeInternalRayDirection( 0.0, 1.0, 0.0 );

  // Fire a ray through the geometry
  distance_to_boundary = navigator->fireInternalRay();

  FRENSIE_CHECK_FLOATING_EQUALITY( distance_to_boundary, 5.0, 1e-9 );

  // Advance the ray to the cell boundary
  navigator->advanceInternalRayToCellBoundary();

  // Find the new cell
  cell = navigator->getCellContainingInternalRay();

  FRENSIE_CHECK_EQUAL( cell, 3 );
}

//---------------------------------------------------------------------------//
// Check that the ray can be cloned
FRENSIE_UNIT_TEST( RootNavigator, clone )
{
  std::shared_ptr<Geometry::Navigator> navigator = model->createNavigator();

  // Initialize the ray
  navigator->setInternalRay( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 );

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
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( RootNavigator, archive, TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_name( "test_root_navigator" );
  std::ostringstream archive_ostream;

  std::unique_ptr<OArchive> oarchive;

  createOArchive( archive_name, archive_ostream, oarchive );

  std::shared_ptr<Geometry::Navigator> navigator = model->createNavigator();

  // Initialize the ray
  navigator->setInternalRay( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 );

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

std::string test_root_geom_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_root_file",
                                        test_root_geom_file_name, "",
                                        "Test ROOT file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "cache_test_archive",
                                        cache_test_archive, false,
                                        "Cache the test archive" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  Geometry::RootModelProperties local_properties( test_root_geom_file_name );
  
  std::shared_ptr<Geometry::RootModel> tmp_model =
    Geometry::RootModel::getInstance();

  tmp_model->initialize( local_properties );

  model = tmp_model;
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstRootNavigator.cpp
//---------------------------------------------------------------------------//
