//---------------------------------------------------------------------------//
//!
//! \file   tstInfiniteMediumNavigator.cpp
//! \author Alex Robinson
//! \brief  Infinite medium navigator class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "Geometry_InfiniteMediumNavigator.hpp"
#include "Geometry_InfiniteMediumModel.hpp"
#include "Utility_Vector.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

namespace cgs = boost::units::cgs;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the location of a point w.r.t. a cell can be returned
FRENSIE_UNIT_TEST( InfiniteMediumNavigator, getPointLocation )
{
  std::unique_ptr<Geometry::Navigator>
    navigator( new Geometry::InfiniteMediumNavigator( 1 ) );

  std::unique_ptr<Geometry::Navigator::Ray>
    ray( new Geometry::Navigator::Ray( 0.0*cgs::centimeter,
                                       0.0*cgs::centimeter,
                                       0.0*cgs::centimeter,
                                       0.0, 0.0, 1.0 ) );

  Geometry::PointLocation location = navigator->getPointLocation( *ray, 1 );

  FRENSIE_CHECK_EQUAL( location, Geometry::POINT_INSIDE_CELL );

  location = navigator->getPointLocation( *ray, 2 );

  FRENSIE_CHECK_EQUAL( location, Geometry::POINT_OUTSIDE_CELL );

  ray.reset( new Geometry::Navigator::Ray(
                   Utility::QuantityTraits<Geometry::Navigator::Length>::max(),
                   Utility::QuantityTraits<Geometry::Navigator::Length>::max(),
                   Utility::QuantityTraits<Geometry::Navigator::Length>::max(),
                   1.0, 0.0, 0.0 ) );

  location = navigator->getPointLocation( *ray, 1 );

  FRENSIE_CHECK_EQUAL( location, Geometry::POINT_INSIDE_CELL );

  location = navigator->getPointLocation( *ray, 2 );

  FRENSIE_CHECK_EQUAL( location, Geometry::POINT_OUTSIDE_CELL );
}

//---------------------------------------------------------------------------//
// Check that the surface normal at a point on the surface can be returned
FRENSIE_UNIT_TEST( InfiniteMediumNavigator, getSurfaceNormal )
{
  std::unique_ptr<Geometry::Navigator>
    navigator( new Geometry::InfiniteMediumNavigator( 1 ) );

  std::unique_ptr<Geometry::Navigator::Ray>
    ray( new Geometry::Navigator::Ray( 0.0*cgs::centimeter,
                                       0.0*cgs::centimeter,
                                       0.0*cgs::centimeter,
                                       0.0, 0.0, 1.0 ) );

  std::vector<double> normal( 3 );

  navigator->getSurfaceNormal( 0, *ray, normal.data() );

  FRENSIE_CHECK_EQUAL( normal[0], 0.0 );
  FRENSIE_CHECK_EQUAL( normal[1], 0.0 );
  FRENSIE_CHECK_EQUAL( normal[2], 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the cell containing a ray can be found
FRENSIE_UNIT_TEST( InfiniteMediumNavigator, findCellContainingRay_cache )
{
  std::unique_ptr<Geometry::Navigator>
    navigator( new Geometry::InfiniteMediumNavigator( 1 ) );

  std::unique_ptr<Geometry::Navigator::Ray>
    ray( new Geometry::Navigator::Ray( 0.0*cgs::centimeter,
                                       0.0*cgs::centimeter,
                                       0.0*cgs::centimeter,
                                       0.0, 0.0, 1.0 ) );

  Geometry::Navigator::CellIdSet cell_cache;

  Geometry::Navigator::EntityId cell =
    navigator->findCellContainingRay( *ray, cell_cache );

  FRENSIE_CHECK_EQUAL( cell, 1 );
  FRENSIE_CHECK_EQUAL( cell_cache.size(), 1 );
  FRENSIE_CHECK( cell_cache.count( 1 ) );

  ray.reset( new Geometry::Navigator::Ray(
                   Utility::QuantityTraits<Geometry::Navigator::Length>::max(),
                   Utility::QuantityTraits<Geometry::Navigator::Length>::max(),
                   Utility::QuantityTraits<Geometry::Navigator::Length>::max(),
                   1.0, 0.0, 0.0 ) );

  cell = navigator->findCellContainingRay( *ray, cell_cache );

  FRENSIE_CHECK_EQUAL( cell, 1 );
  FRENSIE_CHECK_EQUAL( cell_cache.size(), 1 );
  FRENSIE_CHECK( cell_cache.count( 1 ) );
}

//---------------------------------------------------------------------------//
// Check that the cell containing a ray can be found
FRENSIE_UNIT_TEST( InfiniteMediumNavigator, findCellContainingRay )
{
  std::unique_ptr<Geometry::Navigator>
    navigator( new Geometry::InfiniteMediumNavigator( 1 ) );

  std::unique_ptr<Geometry::Navigator::Ray>
    ray( new Geometry::Navigator::Ray( 0.0*cgs::centimeter,
                                       0.0*cgs::centimeter,
                                       0.0*cgs::centimeter,
                                       0.0, 0.0, 1.0 ) );

  Geometry::Navigator::EntityId cell =
    navigator->findCellContainingRay( *ray );

  FRENSIE_CHECK_EQUAL( cell, 1 );

  ray.reset( new Geometry::Navigator::Ray(
                   Utility::QuantityTraits<Geometry::Navigator::Length>::max(),
                   Utility::QuantityTraits<Geometry::Navigator::Length>::max(),
                   Utility::QuantityTraits<Geometry::Navigator::Length>::max(),
                   1.0, 0.0, 0.0 ) );

  cell = navigator->findCellContainingRay( *ray );

  FRENSIE_CHECK_EQUAL( cell, 1 );
}

//---------------------------------------------------------------------------//
// Check that the internal ray can be set
FRENSIE_UNIT_TEST( InfiniteMediumNavigator, setState )
{
  std::unique_ptr<Geometry::Navigator>
    navigator( new Geometry::InfiniteMediumNavigator( 1 ) );

  FRENSIE_CHECK( navigator->isStateSet() );

  navigator->setState( 0.0*cgs::centimeter,
                       0.0*cgs::centimeter,
                       0.0*cgs::centimeter,
                       0.0, 0.0, 1.0 );

  FRENSIE_CHECK( navigator->isStateSet() );

  FRENSIE_CHECK_EQUAL( navigator->getPosition()[0], 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( navigator->getPosition()[1], 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( navigator->getPosition()[2], 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[0], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[1], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[2], 1.0 );
  FRENSIE_CHECK_EQUAL( navigator->getCurrentCell(), 1 );

  navigator->setState(
                   Utility::QuantityTraits<Geometry::Navigator::Length>::max(),
                   Utility::QuantityTraits<Geometry::Navigator::Length>::max(),
                   Utility::QuantityTraits<Geometry::Navigator::Length>::max(),
                   1.0, 0.0, 0.0 );

  FRENSIE_CHECK( navigator->isStateSet() );

  FRENSIE_CHECK_EQUAL( navigator->getPosition()[0],
                       Utility::QuantityTraits<Geometry::Navigator::Length>::max() );
  FRENSIE_CHECK_EQUAL( navigator->getPosition()[1],
                       Utility::QuantityTraits<Geometry::Navigator::Length>::max() );
  FRENSIE_CHECK_EQUAL( navigator->getPosition()[2],
                       Utility::QuantityTraits<Geometry::Navigator::Length>::max() );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[0], 1.0 );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[1], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[2], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getCurrentCell(), 1 );
}

//---------------------------------------------------------------------------//
// Check that the distance to closest boundary
FRENSIE_UNIT_TEST( InfiniteMediumNavigator, getDistanceToClosestBoundary )
{
  std::unique_ptr<Geometry::Navigator>
    navigator( new Geometry::InfiniteMediumNavigator( 1 ) );

  navigator->setState( 0.0*cgs::centimeter,
                       0.0*cgs::centimeter,
                       0.0*cgs::centimeter,
                       0.0, 0.0, 1.0 );

  // Get safety distance
  Geometry::Navigator::Length safety_distance =
    navigator->getDistanceToClosestBoundary();

  FRENSIE_CHECK_EQUAL( safety_distance,
                       Utility::QuantityTraits<Geometry::Navigator::Length>::inf() );

  navigator->setState( 1000.0*cgs::centimeter,
                       10.0*cgs::centimeter,
                       -120.0*cgs::centimeter,
                       0.0, 0.0, 1.0 );

  // Get safety distance
  safety_distance = navigator->getDistanceToClosestBoundary();

  FRENSIE_CHECK_EQUAL( safety_distance,
                       Utility::QuantityTraits<Geometry::Navigator::Length>::inf() );
}

//---------------------------------------------------------------------------//
// Check that the internal ray can be fired through the geometry
FRENSIE_UNIT_TEST( InfiniteMediumNavigator, fireRay )
{
  std::unique_ptr<Geometry::Navigator>
    navigator( new Geometry::InfiniteMediumNavigator( 1 ) );

  navigator->setState( 0.0*cgs::centimeter,
                       0.0*cgs::centimeter,
                       0.0*cgs::centimeter,
                       0.0, 0.0, 1.0 );

  Geometry::Navigator::Length distance_to_boundary = navigator->fireRay();

  FRENSIE_CHECK_EQUAL( distance_to_boundary,
                       Utility::QuantityTraits<Geometry::Navigator::Length>::inf() );

  Geometry::Navigator::EntityId surface_hit;

  navigator->setState( 1.0*cgs::centimeter,
                       -1.0*cgs::centimeter,
                       1.0*cgs::centimeter,
                       1.0, 0.0, 0.0 );

  distance_to_boundary = navigator->fireRay( &surface_hit );

  FRENSIE_CHECK_EQUAL( distance_to_boundary,
                       Utility::QuantityTraits<Geometry::Navigator::Length>::inf() );
  FRENSIE_CHECK_EQUAL( surface_hit,
                       Geometry::Navigator::invalidSurfaceId() );
}

//---------------------------------------------------------------------------//
// Check that the internal ray can be advanced to the cell boundary
FRENSIE_UNIT_TEST( InfiniteMediumNavigator, advanceToCellBoundary )
{
  std::unique_ptr<Geometry::Navigator>
    navigator( new Geometry::InfiniteMediumNavigator( 1 ) );

  navigator->setState( 0.0*cgs::centimeter,
                       0.0*cgs::centimeter,
                       0.0*cgs::centimeter,
                       0.0, 0.0, 1.0 );

  bool reflected = navigator->advanceToCellBoundary();

  FRENSIE_CHECK_EQUAL( navigator->getPosition()[0],
                       Utility::QuantityTraits<Geometry::Navigator::Length>::inf() );
  FRENSIE_CHECK_EQUAL( navigator->getPosition()[1],
                       Utility::QuantityTraits<Geometry::Navigator::Length>::inf() );
  FRENSIE_CHECK_EQUAL( navigator->getPosition()[2],
                       Utility::QuantityTraits<Geometry::Navigator::Length>::inf() );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[0], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[1], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[2], 1.0 );
  FRENSIE_CHECK_EQUAL( navigator->getCurrentCell(), 1 );
  FRENSIE_CHECK( !reflected );

  navigator->setState( 1.0*cgs::centimeter,
                       -1.0*cgs::centimeter,
                       1.0*cgs::centimeter,
                       1.0/sqrt(3), 1.0/sqrt(3), 1.0/sqrt(3) );

  std::vector<double> surface_normal( 3 );

  reflected = navigator->advanceToCellBoundary( surface_normal.data() );

  FRENSIE_CHECK_EQUAL( navigator->getPosition()[0],
                       Utility::QuantityTraits<Geometry::Navigator::Length>::inf() );
  FRENSIE_CHECK_EQUAL( navigator->getPosition()[1],
                       Utility::QuantityTraits<Geometry::Navigator::Length>::inf() );
  FRENSIE_CHECK_EQUAL( navigator->getPosition()[2],
                       Utility::QuantityTraits<Geometry::Navigator::Length>::inf() );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[0], 1.0/sqrt(3.0) );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[1], 1.0/sqrt(3.0) );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[2], 1.0/sqrt(3.0) );
  FRENSIE_CHECK_EQUAL( navigator->getCurrentCell(), 1 );
  FRENSIE_CHECK( !reflected );
  FRENSIE_CHECK_EQUAL( surface_normal[0], 1.0/sqrt(3.0) );
  FRENSIE_CHECK_EQUAL( surface_normal[1], 1.0/sqrt(3.0) );
  FRENSIE_CHECK_EQUAL( surface_normal[2], 1.0/sqrt(3.0) );
}

//---------------------------------------------------------------------------//
// Check that the internal ray can be advanced to the cell boundary
FRENSIE_UNIT_TEST( InfiniteMediumNavigator,
                   advanceToCellBoundary_with_callback )
{
  Geometry::InfiniteMediumModel model( 1 );

  bool advance_finished = false;

  std::unique_ptr<Geometry::Navigator>
    navigator( model.createNavigatorAdvanced( [&advance_finished](const Geometry::Navigator::Length){ advance_finished = true; } ) );

  navigator->setState( 0.0*cgs::centimeter,
                       0.0*cgs::centimeter,
                       0.0*cgs::centimeter,
                       0.0, 0.0, 1.0 );

  navigator->advanceToCellBoundary();

  FRENSIE_CHECK( advance_finished );
}

//---------------------------------------------------------------------------//
// Check that the internal ray can be advanced by a substep
FRENSIE_UNIT_TEST( InfiniteMediumNavigator, advanceBySubstep )
{
  std::unique_ptr<Geometry::Navigator>
    navigator( new Geometry::InfiniteMediumNavigator( 1 ) );

  navigator->setState( 0.0*cgs::centimeter,
                       0.0*cgs::centimeter,
                       0.0*cgs::centimeter,
                       0.0, 0.0, 1.0 );

  navigator->advanceBySubstep( 1.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( navigator->getPosition()[0], 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( navigator->getPosition()[1], 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( navigator->getPosition()[2], 1.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[0], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[1], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[2], 1.0 );

  navigator->setState( 1.0*cgs::centimeter,
                       -1.0*cgs::centimeter,
                       1.0*cgs::centimeter,
                       1.0/sqrt(3), 1.0/sqrt(3), -1.0/sqrt(3) );

  navigator->advanceBySubstep( 2.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( navigator->getPosition()[0],
                       (1.0+2.0/sqrt(3.0))*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( navigator->getPosition()[1],
                       (-1.0+2.0/sqrt(3.0))*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( navigator->getPosition()[2],
                       (1.0-2.0/sqrt(3.0))*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[0], 1.0/sqrt(3) );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[1], 1.0/sqrt(3) );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[2], -1.0/sqrt(3) );
}

//---------------------------------------------------------------------------//
// Check that the internal ray can be advanced by a substep
FRENSIE_UNIT_TEST( InfiniteMediumNavigator, advanceBySubstep_with_callback )
{
  Geometry::InfiniteMediumModel model( 1 );

  Geometry::Navigator::Length distance_traveled = 0.0*cgs::centimeter;

  std::unique_ptr<Geometry::Navigator>
    navigator( model.createNavigatorAdvanced( [&distance_traveled](const Geometry::Navigator::Length distance){ distance_traveled += distance; } ) );

  navigator->setState( 0.0*cgs::centimeter,
                       0.0*cgs::centimeter,
                       0.0*cgs::centimeter,
                       0.0, 0.0, 1.0 );

  navigator->advanceBySubstep( 1.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( navigator->getPosition()[0], 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( navigator->getPosition()[1], 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( navigator->getPosition()[2], 1.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[0], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[1], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[2], 1.0 );
  FRENSIE_CHECK_EQUAL( distance_traveled, 1.0*cgs::centimeter );

  navigator->changeDirection( 0.0, 0.0, -1.0 );

  navigator->advanceBySubstep( 1.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( navigator->getPosition()[0], 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( navigator->getPosition()[1], 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( navigator->getPosition()[2], 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[0], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[1], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[2], -1.0 );
  FRENSIE_CHECK_EQUAL( distance_traveled, 2.0*cgs::centimeter );
}

//---------------------------------------------------------------------------//
// Check that the internal ray direction can be changed
FRENSIE_UNIT_TEST( InfiniteMediumNavigator, changeDirection )
{
  std::unique_ptr<Geometry::Navigator>
    navigator( new Geometry::InfiniteMediumNavigator( 1 ) );

  navigator->setState( 0.0*cgs::centimeter,
                       0.0*cgs::centimeter,
                       0.0*cgs::centimeter,
                       0.0, 0.0, 1.0 );

  navigator->changeDirection( 1.0, 0.0, 0.0 );

  FRENSIE_CHECK_EQUAL( navigator->getPosition()[0], 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( navigator->getPosition()[1], 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( navigator->getPosition()[2], 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[0], 1.0 );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[1], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[2], 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the navigator can be cloned
FRENSIE_UNIT_TEST( InfiniteMediumNavigator, clone )
{
  size_t number_of_advances = 0;

  std::unique_ptr<Geometry::Navigator>
    navigator( new Geometry::InfiniteMediumNavigator( 1, [&number_of_advances](const Geometry::Navigator::Length){ ++number_of_advances; } ) );

  navigator->setState( 0.0*cgs::centimeter,
                       0.0*cgs::centimeter,
                       0.0*cgs::centimeter,
                       0.0, 0.0, 1.0 );

  navigator->advanceBySubstep( 1.0*cgs::centimeter );

  std::unique_ptr<Geometry::Navigator> navigator_clone( navigator->clone() );

  FRENSIE_CHECK_EQUAL( navigator_clone->getPosition()[0],
                       navigator->getPosition()[0] );
  FRENSIE_CHECK_EQUAL( navigator_clone->getPosition()[1],
                       navigator->getPosition()[1] );
  FRENSIE_CHECK_EQUAL( navigator_clone->getPosition()[2],
                       navigator->getPosition()[2] );
  FRENSIE_CHECK_EQUAL( navigator_clone->getDirection()[0],
                       navigator->getDirection()[0] );
  FRENSIE_CHECK_EQUAL( navigator_clone->getDirection()[1],
                       navigator->getDirection()[1] );
  FRENSIE_CHECK_EQUAL( navigator_clone->getDirection()[2],
                       navigator->getDirection()[2] );
  FRENSIE_CHECK_EQUAL( navigator_clone->getCurrentCell(),
                       navigator->getCurrentCell() );

  navigator_clone->advanceBySubstep( 1.0*cgs::centimeter );

  // The callback should've been copied during the clone
  FRENSIE_CHECK_EQUAL( number_of_advances, 2 );

  navigator_clone.reset( navigator->clone( [](const Geometry::Navigator::Length distance){ std::cout << "advanced " << distance << std::endl; } ) );

  FRENSIE_CHECK_EQUAL( navigator_clone->getPosition()[0],
                       navigator->getPosition()[0] );
  FRENSIE_CHECK_EQUAL( navigator_clone->getPosition()[1],
                       navigator->getPosition()[1] );
  FRENSIE_CHECK_EQUAL( navigator_clone->getPosition()[2],
                       navigator->getPosition()[2] );
  FRENSIE_CHECK_EQUAL( navigator_clone->getDirection()[0],
                       navigator->getDirection()[0] );
  FRENSIE_CHECK_EQUAL( navigator_clone->getDirection()[1],
                       navigator->getDirection()[1] );
  FRENSIE_CHECK_EQUAL( navigator_clone->getDirection()[2],
                       navigator->getDirection()[2] );
  FRENSIE_CHECK_EQUAL( navigator_clone->getCurrentCell(),
                       navigator->getCurrentCell() );

  navigator_clone->advanceBySubstep( 1.0*cgs::centimeter );

  // A new callback was set so the number of advances counter should be
  // unmodified
  FRENSIE_CHECK_EQUAL( number_of_advances, 2 );
}

// //---------------------------------------------------------------------------//
// // Check that the navigator can be archived
// FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( InfiniteMediumNavigator,
//                                    archive,
//                                    TestArchives )
// {
//   FETCH_TEMPLATE_PARAM( 0, RawOArchive );
//   FETCH_TEMPLATE_PARAM( 1, RawIArchive );

//   typedef typename std::remove_pointer<RawOArchive>::type OArchive;
//   typedef typename std::remove_pointer<RawIArchive>::type IArchive;

//   std::string archive_base_name( "test_infinite_medium_navigator" );
//   std::ostringstream archive_ostream;

//   // Create and archive some infinite medium navigators
//   {
//     std::unique_ptr<OArchive> oarchive;

//     createOArchive( archive_base_name, archive_ostream, oarchive );

//     Geometry::InfiniteMediumNavigator navigator( 1 );

//     std::unique_ptr<Geometry::Navigator> unique_navigator( new Geometry::InfiniteMediumNavigator( 2 ) );

//     std::shared_ptr<Geometry::Navigator> shared_navigator( new Geometry::InfiniteMediumNavigator( 3 ) );

//     FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( navigator ) );
//     FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( unique_navigator ) );
//     FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( shared_navigator ) );
//   }

//   // Copy the archive ostream to an istream
//   std::istringstream archive_istream( archive_ostream.str() );

//   // Load the archived distributions
//   std::unique_ptr<IArchive> iarchive;

//   createIArchive( archive_istream, iarchive );

//   Geometry::InfiniteMediumNavigator navigator( 100 );

//   FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( navigator ) );
//   FRENSIE_CHECK_EQUAL( navigator.getCurrentCell(), 1 );

//   std::unique_ptr<Geometry::Navigator> unique_navigator;

//   FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( unique_navigator ) );
//   FRENSIE_CHECK_EQUAL( unique_navigator->getCurrentCell(), 2 );

//   std::shared_ptr<Geometry::Navigator> shared_navigator;

//   FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( shared_navigator ) );
//   FRENSIE_CHECK_EQUAL( shared_navigator->getCurrentCell(), 3 );
// }

//---------------------------------------------------------------------------//
// end tstInfiniteMediumNavigator.cpp
//---------------------------------------------------------------------------//

