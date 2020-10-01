//---------------------------------------------------------------------------//
//!
//! \file   tstStructuredHexMesh.cpp
//! \author Philip Britt
//! \brief  StructuredHexMesh class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <iomanip>
#include <memory>
#include <utility>

// FRENSIE Includes
#include "Utility_StructuredHexMesh.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "FRENSIE_config.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// test constructing the mesh.
FRENSIE_UNIT_TEST( StructuredHexMesh, constructor )
{
  std::vector<double> x_planes( {0.0, 0.5, 1.0} ),
    y_planes( {0.0, 0.5, 1.0} ),
    z_planes( {0.0, 0.5, 1.0} );

  std::shared_ptr<Utility::StructuredHexMesh> hex_mesh;
  
  FRENSIE_CHECK_NO_THROW(
                hex_mesh.reset( new Utility::StructuredHexMesh( x_planes,
                                                                y_planes,
                                                                z_planes ) ) );

  FRENSIE_CHECK_EQUAL( x_planes.size(), hex_mesh->getNumberOfXPlanes() );
  
  for( size_t i = 0; i < x_planes.size(); ++i )
  {
    FRENSIE_CHECK_FLOATING_EQUALITY( hex_mesh->getXPlaneLocation(i),
                                     x_planes[i],
                                     1e-12 );
  }

  FRENSIE_CHECK_EQUAL( y_planes.size(), hex_mesh->getNumberOfYPlanes() );
  
  for( size_t i = 0; i < y_planes.size(); ++i )
  {
    FRENSIE_CHECK_FLOATING_EQUALITY( hex_mesh->getYPlaneLocation(i),
                                     y_planes[i],
                                     1e-12 );
  }

  FRENSIE_CHECK_EQUAL( z_planes.size(), hex_mesh->getNumberOfZPlanes() );
  
  for( size_t i = 0; i < z_planes.size(); ++i )
  {
    FRENSIE_CHECK_FLOATING_EQUALITY( hex_mesh->getZPlaneLocation(i),
                                     z_planes[i],
                                     1e-12 );
  }

  FRENSIE_CHECK_EQUAL( hex_mesh->getNumberOfElements(), (z_planes.size()-1)*(y_planes.size()-1)*(x_planes.size()-1) );
  
  FRENSIE_CHECK_EQUAL( (z_planes.size()-1)*(y_planes.size()-1)*(x_planes.size()-1),
                       std::distance( hex_mesh->getStartElementHandleIterator(), hex_mesh->getEndElementHandleIterator() ) );

}

//---------------------------------------------------------------------------//
// Test the getMeshTypeName method
FRENSIE_UNIT_TEST( StructuredHexMesh, getMeshTypeName )
{
  std::vector<double> x_planes( {0.0, 0.5, 1.0} ),
    y_planes( {0.0, 0.5, 1.0} ),
    z_planes( {0.0, 0.5, 1.0} );

  std::shared_ptr<Utility::StructuredHexMesh> hex_mesh(
              new Utility::StructuredHexMesh( x_planes, y_planes, z_planes ) );

  FRENSIE_CHECK_EQUAL( hex_mesh->getMeshTypeName(),
                       "Structured Hex Mesh" );
}

//---------------------------------------------------------------------------//
// Test the getMeshElementTypeName method
FRENSIE_UNIT_TEST( StructuredHexMex, getMeshElementTypeName )
{
  std::vector<double> x_planes( {0.0, 0.5, 1.0} ),
    y_planes( {0.0, 0.5, 1.0} ),
    z_planes( {0.0, 0.5, 1.0} );

  std::shared_ptr<Utility::StructuredHexMesh> hex_mesh(
              new Utility::StructuredHexMesh( x_planes, y_planes, z_planes ) );

  FRENSIE_CHECK_EQUAL( hex_mesh->getMeshElementTypeName(), "Hex" );
}

//---------------------------------------------------------------------------//
// Test the getElementVolumes method
FRENSIE_UNIT_TEST( StructuredHexMesh, getElementVolumes )
{
  std::vector<double> x_planes( {0.0, 0.5, 1.0} ),
    y_planes( {0.0, 0.5, 1.0} ),
    z_planes( {0.0, 0.5, 1.5} );

  std::shared_ptr<Utility::StructuredHexMesh> hex_mesh(
              new Utility::StructuredHexMesh( x_planes, y_planes, z_planes ) );
  
  Utility::StructuredHexMesh::ElementHandleVolumeMap volume_map;
  
  hex_mesh->getElementVolumes( volume_map );

  FRENSIE_REQUIRE_EQUAL( volume_map.size(), 8 );
  FRENSIE_CHECK_FLOATING_EQUALITY( volume_map[0], 0.125, 1e-12);
  FRENSIE_CHECK_FLOATING_EQUALITY( volume_map[1], 0.125, 1e-12);
  FRENSIE_CHECK_FLOATING_EQUALITY( volume_map[2], 0.125, 1e-12);
  FRENSIE_CHECK_FLOATING_EQUALITY( volume_map[3], 0.125, 1e-12);
  FRENSIE_CHECK_FLOATING_EQUALITY( volume_map[4], 0.25, 1e-12);
  FRENSIE_CHECK_FLOATING_EQUALITY( volume_map[5], 0.25, 1e-12);
  FRENSIE_CHECK_FLOATING_EQUALITY( volume_map[6], 0.25, 1e-12);
  FRENSIE_CHECK_FLOATING_EQUALITY( volume_map[7], 0.25, 1e-12);
}

//---------------------------------------------------------------------------//
// Test the getElementVolume method
FRENSIE_UNIT_TEST( StructuredHexMesh, getElementVolume )
{
  std::vector<double> x_planes( {0.0, 0.5, 1.0} ),
  y_planes( {0.0, 0.5, 1.0} ),
  z_planes( {0.0, 0.5, 2.0} );

  std::shared_ptr<Utility::StructuredHexMesh> hex_mesh(
              new Utility::StructuredHexMesh( x_planes, y_planes, z_planes ) );

  for( size_t i = 0; i < hex_mesh->getNumberOfElements(); ++i)
  {
    if(i < 4)
    {
      FRENSIE_CHECK_FLOATING_EQUALITY(hex_mesh->getElementVolume(i), 0.125, 1e-15);
    }
    else
    {
      FRENSIE_CHECK_FLOATING_EQUALITY(hex_mesh->getElementVolume(i), 0.375, 1e-15);
    }
  }
}

//---------------------------------------------------------------------------//
// test whether or not the point in mesh method works
FRENSIE_UNIT_TEST( StructuredHexMesh, isPointInMesh )
{
  std::vector<double> x_planes( {0.0, 0.5, 1.0} ),
    y_planes( {0.0, 0.5, 1.0} ),
    z_planes( {0.0, 0.5, 1.0} );

  std::shared_ptr<Utility::StructuredHexMesh> hex_mesh(
              new Utility::StructuredHexMesh( x_planes, y_planes, z_planes ) );
  
  //points inside mesh and not in boundary region
  double point1[3] {0.5, 0.5, 0.5};
  double point2[3] {0.25, 0.25, 0.25};
  double point3[3] {0.75, 0.75, 0.75};
  double point4[3] {0.25, 0.9, 0.23};
  
  FRENSIE_CHECK( hex_mesh->isPointInMesh(point1) );
  FRENSIE_CHECK( hex_mesh->isPointInMesh(point2) );
  FRENSIE_CHECK( hex_mesh->isPointInMesh(point3) );
  FRENSIE_CHECK( hex_mesh->isPointInMesh(point4) );
  
  //points not inside mesh but inside boundary region (should return false)
  //points on upper dimension boundaries
  double point5[3] {1.0 + 1e-13, 0.5, 0.5};
  double point6[3] {0.5, 1.0 + 1e-13, 0.5};
  double point7[3] {0.5, 0.5, 1.0 + 1e-13};
  //points on lower dimension boundaries
  double point8[3] {-1e-13, 0.5, 0.5};
  double point9[3] {0.5, -1e-13, 0.5};
  double point10[3] {0.5, 0.5, -1e-13};

  FRENSIE_CHECK( !hex_mesh->isPointInMesh(point5) );
  FRENSIE_CHECK( !hex_mesh->isPointInMesh(point6) );
  FRENSIE_CHECK( !hex_mesh->isPointInMesh(point7) );
  FRENSIE_CHECK( !hex_mesh->isPointInMesh(point8) );
  FRENSIE_CHECK( !hex_mesh->isPointInMesh(point9) );
  FRENSIE_CHECK( !hex_mesh->isPointInMesh(point10) );

  //points outside of mesh
  //points on upper dimension boundaries
  double point11[3] {1.0 + 1e-5, 0.5, 0.5};
  double point12[3] {0.5, 1.0 + 1e-5, 0.5};
  double point13[3] {0.5, 0.5, 1.0 + 1e-5};
  //points on lower dimension boundaries
  double point14[3] {-1e-5, 0.5, 0.5};
  double point15[3] {0.5, -1e-5, 0.5};
  double point16[3] {0.5, 0.5, -1e-5};

  FRENSIE_CHECK( !hex_mesh->isPointInMesh(point11) );
  FRENSIE_CHECK( !hex_mesh->isPointInMesh(point12) );
  FRENSIE_CHECK( !hex_mesh->isPointInMesh(point13) );
  FRENSIE_CHECK( !hex_mesh->isPointInMesh(point14) );
  FRENSIE_CHECK( !hex_mesh->isPointInMesh(point15) );
  FRENSIE_CHECK( !hex_mesh->isPointInMesh(point16) );  
}

//---------------------------------------------------------------------------//
// test whether or not the whichHexIsPointIn method works
FRENSIE_UNIT_TEST( StructuredHexMesh, whichElementIsPointIn )
{
  std::vector<double> x_planes( {0.0, 0.5, 1.0} ),
    y_planes( {0.0, 0.5, 1.0} ),
    z_planes( {0.0, 0.5, 1.0} );

  std::shared_ptr<Utility::StructuredHexMesh> hex_mesh(
              new Utility::StructuredHexMesh( x_planes, y_planes, z_planes ) );
  
  //test points in the middle of the mesh elements. Points should be in order for index returned
  double point1[3] {0.25, 0.25, 0.25};
  double point2[3] {0.75, 0.25, 0.25};
  double point3[3] {0.25, 0.75, 0.25};
  double point4[3] {0.75, 0.75, 0.25};
  double point5[3] {0.25, 0.25, 0.75};
  double point6[3] {0.75, 0.25, 0.75};
  double point7[3] {0.25, 0.75, 0.75};
  double point8[3] {0.75, 0.75, 0.75};
  
  FRENSIE_CHECK_EQUAL( hex_mesh->whichElementIsPointIn(point1), 0);
  FRENSIE_CHECK_EQUAL( hex_mesh->whichElementIsPointIn(point2), 1);
  FRENSIE_CHECK_EQUAL( hex_mesh->whichElementIsPointIn(point3), 2);
  FRENSIE_CHECK_EQUAL( hex_mesh->whichElementIsPointIn(point4), 3);
  FRENSIE_CHECK_EQUAL( hex_mesh->whichElementIsPointIn(point5), 4);
  FRENSIE_CHECK_EQUAL( hex_mesh->whichElementIsPointIn(point6), 5);
  FRENSIE_CHECK_EQUAL( hex_mesh->whichElementIsPointIn(point7), 6);
  FRENSIE_CHECK_EQUAL( hex_mesh->whichElementIsPointIn(point8), 7);
  
  /* test points on mesh boundaries.*/
  double point9[3] {0, 0, 0};
  double point10[3] {0.5, 0.5, 0.5};
  double point11[3] {1.0, 1.0, 1.0};
  FRENSIE_CHECK_EQUAL( hex_mesh->whichElementIsPointIn(point9), 0);
  FRENSIE_CHECK_EQUAL( hex_mesh->whichElementIsPointIn(point10), 7);
  FRENSIE_CHECK_EQUAL( hex_mesh->whichElementIsPointIn(point11), 7);
}

//---------------------------------------------------------------------------//
// test simple cases of rays not interacting with mesh and computeTrackLengths
// returning empty arrays
FRENSIE_UNIT_TEST( StructuredHexMesh, computeTrackLengths_no_intersection )
{
  std::vector<double> x_planes( {0.0, 0.5, 1.0} ),
    y_planes( {0.0, 0.5, 1.0} ),
    z_planes( {0.0, 0.5, 1.0} );

  std::shared_ptr<Utility::StructuredHexMesh> hex_mesh(
              new Utility::StructuredHexMesh( x_planes, y_planes, z_planes ) );
  
  double start_point[3], end_point[3], ray[3], direction[3], ray_length;
 
  // test a point heading away from the mesh and not intersecting with anything
  
  start_point[0] = 1.1;
  start_point[1] = 1.1;
  start_point[2] = 1.1;
 
  end_point[0] = 2;
  end_point[1] = 2;
  end_point[2] = 2;
  
  ray[0] = end_point[0] - start_point[0];
  ray[1] = end_point[1] - start_point[1];
  ray[2] = end_point[2] - start_point[2];
  
  ray_length = Utility::vectorMagnitude(ray);
  
  direction[0] = ray[0] / ray_length;
  direction[1] = ray[1] / ray_length;
  direction[2] = ray[2] / ray_length;
  
  Utility::StructuredHexMesh::ElementHandleTrackLengthArray contribution;
  
  hex_mesh->computeTrackLengths( start_point, end_point, contribution );
  
  FRENSIE_CHECK( contribution.empty() );
  
  /*reverse order of last example making particle travel towards mesh but never enter
    it due to short length */
  start_point[0] = 2;
  start_point[1] = 2;
  start_point[2] = 2;
  
  end_point[0] = 1.1;
  end_point[1] = 1.1;
  end_point[2] = 1.1;
  
  ray[0] = end_point[0] - start_point[0];
  ray[1] = end_point[1] - start_point[1];
  ray[2] = end_point[2] - start_point[2];
  
  ray_length = Utility::vectorMagnitude(ray);
 
  direction[0] = ray[0] / ray_length;
  direction[1] = ray[1] / ray_length;
  direction[2] = ray[2] / ray_length;
  
  hex_mesh->computeTrackLengths( start_point, end_point, contribution );
  
  FRENSIE_CHECK( contribution.empty() );
  
  //particle crosses planes but still never actually crosses mesh
  start_point[0] = 2;
  start_point[1] = 2;
  start_point[2] = 2;
  
  end_point[0] = 1;
  end_point[1] = 2;
  end_point[2] = 2;
  
  ray[0] = end_point[0] - start_point[0];
  ray[1] = end_point[1] - start_point[1];
  ray[2] = end_point[2] - start_point[2];
  
  ray_length = Utility::vectorMagnitude(ray);
  
  direction[0] = ray[0] / ray_length;
  direction[1] = ray[1] / ray_length;
  direction[2] = ray[2] / ray_length;
  
  hex_mesh->computeTrackLengths( start_point, end_point, contribution );
  
  FRENSIE_CHECK( contribution.empty() );
  
  // particle ends in boundary region. Should give zero since pushing it up to
  // the actual boundary would be longer than the particle track length
  start_point[0] = 2;
  start_point[1] = 0.25;
  start_point[2] = 0.25;
 
  end_point[0] = 1+1e-7;
  end_point[1] = 0.25;
  end_point[2] = 0.25;
 
  ray[0] = end_point[0] - start_point[0];
  ray[1] = end_point[1] - start_point[1];
  ray[2] = end_point[2] - start_point[2];
 
  ray_length = Utility::vectorMagnitude(ray);
 
  direction[0] = ray[0] / ray_length;
  direction[1] = ray[1] / ray_length;
  direction[2] = ray[2] / ray_length;
 
  hex_mesh->computeTrackLengths( start_point, end_point, contribution );

  FRENSIE_CHECK( contribution.empty() );
}

//---------------------------------------------------------------------------//
// testing cases of rays interacting with mesh and returning appropriate
// results (particle track is entirely within one cell)
FRENSIE_UNIT_TEST( StructuredHexMesh, computeTrackLengths_one_cell )
{
  std::vector<double> x_planes( {0.0, 0.5, 1.0} ),
    y_planes( {0.0, 0.5, 1.0} ),
    z_planes( {0.0, 0.5, 1.0} );

  std::shared_ptr<Utility::StructuredHexMesh> hex_mesh(
              new Utility::StructuredHexMesh( x_planes, y_planes, z_planes ) );
  
  double start_point[3], end_point[3], ray[3], direction[3], ray_length;  
  
  // should also note that because all direction components are positive, this
  // also tests whether or not the function appropriately finds different
  // interaction planes and hex index planes
  start_point[0] = 0.1;
  start_point[1] = 0.1;
  start_point[2] = 0.1;
 
  end_point[0] = 0.4;
  end_point[1] = 0.25;
  end_point[2] = 0.15;
 
  ray[0] = end_point[0] - start_point[0];
  ray[1] = end_point[1] - start_point[1];
  ray[2] = end_point[2] - start_point[2];
 
  ray_length = Utility::vectorMagnitude(ray);
 
  direction[0] = ray[0] / ray_length;
  direction[1] = ray[1] / ray_length;
  direction[2] = ray[2] / ray_length;

  Utility::StructuredHexMesh::ElementHandleTrackLengthArray contribution;
  
  hex_mesh->computeTrackLengths( start_point, end_point, contribution );

  FRENSIE_REQUIRE_EQUAL( contribution.size(), 1 );
  FRENSIE_CHECK_EQUAL( Utility::get<0>(contribution[0]), 0 );
  FRENSIE_CHECK_EQUAL( Utility::get<1>(contribution[0]),
                       (std::array<double,3>( {0.1, 0.1, 0.1} )) );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<2>(contribution[0]),
                                   0.339116499156263,
                                   1e-10 );
}

//---------------------------------------------------------------------------//
// testing cases of rays interacting with mesh and returning appropriate
// results (particle starts in mesh and crosses into another mesh element and
// dies in that mesh element)
FRENSIE_UNIT_TEST( StructuredHexMesh, computeTrackLengths_multiple_elements )
{
  std::vector<double> x_planes( {0.0, 0.5, 1.0} ),
    y_planes( {0.0, 0.5, 1.0} ),
    z_planes( {0.0, 0.5, 1.0} );

  std::shared_ptr<Utility::StructuredHexMesh> hex_mesh(
              new Utility::StructuredHexMesh( x_planes, y_planes, z_planes ) );
  
  double start_point[3], end_point[3], ray[3], direction[3], ray_length;  
  
  start_point[0] = 0.1;
  start_point[1] = 0.1;
  start_point[2] = 0.1;
 
  end_point[0] = 0.6;
  end_point[1] = 0.25;
  end_point[2] = 0.15;
 
  ray[0] = end_point[0] - start_point[0];
  ray[1] = end_point[1] - start_point[1];
  ray[2] = end_point[2] - start_point[2];
 
  ray_length = Utility::vectorMagnitude(ray);
 
  direction[0] = ray[0] / ray_length;
  direction[1] = ray[1] / ray_length;
  direction[2] = ray[2] / ray_length;
 
  Utility::StructuredHexMesh::ElementHandleTrackLengthArray contribution;
  
  hex_mesh->computeTrackLengths( start_point, end_point, contribution );

  FRENSIE_REQUIRE_EQUAL(contribution.size(), 2);
  FRENSIE_CHECK_EQUAL( Utility::get<0>(contribution[0]), 0);
  FRENSIE_CHECK_EQUAL( Utility::get<1>(contribution[0]),
                       (std::array<double,3>( {0.1, 0.1, 0.1} )) );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<2>(contribution[0]),
                                   0.419523539268061,
                                   1e-10 );
  FRENSIE_CHECK_EQUAL( Utility::get<0>(contribution[1]), 1);
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<1>(contribution[1]),
                                   (std::array<double,3>( {0.5, 0.22, 0.14} )),
                                   1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<2>(contribution[1]),
                                   0.104880884817015,
                                   1e-10 );
    
  //one extra check with different plane dimension crossing to make sure any of the planes work
  start_point[0] = 0.7;
  start_point[1] = 0.6;
  start_point[2] = 0.8;
 
  end_point[0] = 0.76;
  end_point[1] = 0.55;
  end_point[2] = 0.25;
 
  ray[0] = end_point[0] - start_point[0];
  ray[1] = end_point[1] - start_point[1];
  ray[2] = end_point[2] - start_point[2];
 
  ray_length = Utility::vectorMagnitude(ray);
 
  direction[0] = ray[0] / ray_length;
  direction[1] = ray[1] / ray_length;
  direction[2] = ray[2] / ray_length;
 
  hex_mesh->computeTrackLengths( start_point, end_point, contribution );

  FRENSIE_REQUIRE_EQUAL( contribution.size(), 2 );
  FRENSIE_CHECK_EQUAL( Utility::get<0>(contribution[0]), 7 );
  FRENSIE_CHECK_EQUAL( Utility::get<1>(contribution[0]),
                       (std::array<double,3>( {0.7, 0.6, 0.8} )) );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<2>(contribution[0]),
                                   0.303009696269043,
                                   1e-10 );
  FRENSIE_CHECK_EQUAL( Utility::get<0>(contribution[1]), 3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<1>(contribution[1]),
                                   (std::array<double,3>( {7.327272727272726716e-01, 5.727272727272727515e-01, 0.5} )),
                                   1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<2>(contribution[1]),
                                   0.252508080224203,
                                   1e-10 );
  
  //test multiple plane crossings
  start_point[0] = 0.7;
  start_point[1] = 0.6;
  start_point[2] = 0.8;
 
  end_point[0] = 0.36;
  end_point[1] = 0.2;
  end_point[2] = 0.81;
 
  ray[0] = end_point[0] - start_point[0];
  ray[1] = end_point[1] - start_point[1];
  ray[2] = end_point[2] - start_point[2];
 
  ray_length = Utility::vectorMagnitude(ray);
 
  direction[0] = ray[0] / ray_length;
  direction[1] = ray[1] / ray_length;
  direction[2] = ray[2] / ray_length;
 
  hex_mesh->computeTrackLengths( start_point, end_point, contribution );

  FRENSIE_REQUIRE_EQUAL( contribution.size(), 3 );
  FRENSIE_CHECK_EQUAL( Utility::get<0>(contribution[0]), 7 );
  FRENSIE_CHECK_EQUAL( Utility::get<1>(contribution[0]),
                       (std::array<double,3>( {0.7, 0.6, 0.8} )) );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<2>(contribution[0]),
                                   0.131267855928251,
                                   1e-10 );
  FRENSIE_CHECK_EQUAL( Utility::get<0>(contribution[1]), 5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<1>(contribution[1]),
                                   (std::array<double,3>( {6.149999999999999911e-01, 0.5, 8.024999999999999911e-01} )),
                                   1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<2>(contribution[1]),
                                   0.177597687432339,
                                   1e-10 );
  FRENSIE_CHECK_EQUAL( Utility::get<0>(contribution[2]), 4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<1>(contribution[2]),
                                   (std::array<double,3>( {0.5, 3.647058823529412130e-01, 8.058823529411764941e-01} )),
                                   1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<2>(contribution[2]),
                                   0.216205880352413,
                                   1e-10 );
  
  double sum_of_segments = Utility::get<2>(contribution[0]) +
    Utility::get<2>(contribution[1]) +
    Utility::get<2>(contribution[2]);
  
  FRENSIE_CHECK_FLOATING_EQUALITY( sum_of_segments, ray_length, 1e-10 );
}

//---------------------------------------------------------------------------//
// testing cases of rays interacting with mesh and returning appropriate
// results (particle starts in mesh and exits mesh)
FRENSIE_UNIT_TEST(StructuredHexMesh,
                  computeTrackLengths_starts_mesh_exits_mesh )
{
  std::vector<double> x_planes( {0.0, 0.5, 1.0} ),
    y_planes( {0.0, 0.5, 1.0} ),
    z_planes( {0.0, 0.5, 1.0} );

  std::shared_ptr<Utility::StructuredHexMesh> hex_mesh(
              new Utility::StructuredHexMesh( x_planes, y_planes, z_planes ) );
  
  double start_point[3], end_point[3], ray[3], direction[3], ray_length;
    
  //particle starts in first cell and exits in the negative direction  
  start_point[0] = 0.25;
  start_point[1] = 0.25;
  start_point[2] = 0.25;
 
  end_point[0] = -0.25;
  end_point[1] = 0.25;
  end_point[2] = 0.25;
 
  ray[0] = end_point[0] - start_point[0];
  ray[1] = end_point[1] - start_point[1];
  ray[2] = end_point[2] - start_point[2];
 
  ray_length = Utility::vectorMagnitude(ray);
 
  direction[0] = ray[0] / ray_length;
  direction[1] = ray[1] / ray_length;
  direction[2] = ray[2] / ray_length;

  Utility::StructuredHexMesh::ElementHandleTrackLengthArray contribution;

  hex_mesh->computeTrackLengths( start_point, end_point, contribution );

  FRENSIE_REQUIRE_EQUAL( contribution.size(), 1 );
  FRENSIE_CHECK_EQUAL( Utility::get<0>(contribution[0]), 0 );
  FRENSIE_CHECK_EQUAL( Utility::get<1>(contribution[0]),
                       (std::array<double,3>( {0.25, 0.25, 0.25} )) );
  FRENSIE_CHECK_EQUAL( Utility::get<2>(contribution[0]), 0.25 );

  //particle starts in another cell and crosses multiple planes before exiting  
  start_point[0] = 0.268;
  start_point[1] = 0.138;
  start_point[2] = 0.922;
 
  end_point[0] = 1.3;
  end_point[1] = 0.9;
  end_point[2] = -1.2;
 
  ray[0] = end_point[0] - start_point[0];
  ray[1] = end_point[1] - start_point[1];
  ray[2] = end_point[2] - start_point[2];
 
  ray_length = Utility::vectorMagnitude(ray);
 
  direction[0] = ray[0] / ray_length;
  direction[1] = ray[1] / ray_length;
  direction[2] = ray[2] / ray_length;
 
  hex_mesh->computeTrackLengths( start_point, end_point, contribution );
  
  FRENSIE_REQUIRE_EQUAL( contribution.size(), 3 );
  FRENSIE_CHECK_EQUAL( Utility::get<0>(contribution[0]), 4 );
  FRENSIE_CHECK_EQUAL( Utility::get<1>(contribution[0]),
                       (std::array<double,3>( {0.268, 0.138, 0.922} )) );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<2>(contribution[0]),
                                   0.493120998659465,
                                   1e-10 );
  FRENSIE_CHECK_EQUAL( Utility::get<0>(contribution[1]), 0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<1>(contribution[1]),
                                   (std::array<double,3>( {4.732327992459943733e-01, 2.895381715362865815e-01, 0.5} )),
                                   1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<2>(contribution[1]),
                                   0.064314616453253,
                                   1e-10 );
  FRENSIE_CHECK_EQUAL( Utility::get<0>(contribution[2]), 1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<1>(contribution[2]),
                                   (std::array<double,3>( {0.5, 3.093023255813953654e-01, 4.449612403100776103e-01} )),
                                   1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<2>(contribution[2]),
                                   0.519951969636160,
                                   1e-10 );
}

//---------------------------------------------------------------------------//
// testing cases of where the particle starts outside of the mesh and enters
// the mesh (simple cases of particle entering mesh)
FRENSIE_UNIT_TEST( StructuredHexMesh, computeTrackLengths_enters_mesh )
{
  std::vector<double> x_planes( {0.0, 0.5, 1.0} ),
    y_planes( {0.0, 0.5, 1.0} ),
    z_planes( {0.0, 0.5, 1.0} );

  std::shared_ptr<Utility::StructuredHexMesh> hex_mesh(
              new Utility::StructuredHexMesh( x_planes, y_planes, z_planes ) );
  
  double start_point[3], end_point[3], ray[3], direction[3], ray_length;
    
  // particle starts outside mesh and enters first cell
  start_point[0] = -0.25;
  start_point[1] = 0.25;
  start_point[2] = 0.25;
 
  end_point[0] = 0.25;
  end_point[1] = 0.25;
  end_point[2] = 0.25;
 
  ray[0] = end_point[0] - start_point[0];
  ray[1] = end_point[1] - start_point[1];
  ray[2] = end_point[2] - start_point[2];
 
  ray_length = Utility::vectorMagnitude(ray);
 
  direction[0] = ray[0] / ray_length;
  direction[1] = ray[1] / ray_length;
  direction[2] = ray[2] / ray_length;

  Utility::StructuredHexMesh::ElementHandleTrackLengthArray contribution;

  hex_mesh->computeTrackLengths( start_point, end_point, contribution );

  FRENSIE_REQUIRE_EQUAL( contribution.size(), 1 );
  FRENSIE_CHECK_EQUAL( Utility::get<0>(contribution[0]), 0 );
  FRENSIE_CHECK_EQUAL( Utility::get<1>(contribution[0]),
                       (std::array<double,3>( {0.0, 0.25, 0.25} )) );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<2>(contribution[0]),
                                   0.25,
                                   1e-12 );

  // particle starts outside mesh,crosses multiple planes inside mesh, and
  // dies inside mesh
  start_point[0] = -0.25;
  start_point[1] = 0.25;
  start_point[2] = 0.25;
 
  end_point[0] = 0.83;
  end_point[1] = 0.73;
  end_point[2] = 0.52;
 
  ray[0] = end_point[0] - start_point[0];
  ray[1] = end_point[1] - start_point[1];
  ray[2] = end_point[2] - start_point[2];
 
  ray_length = Utility::vectorMagnitude(ray);
 
  direction[0] = ray[0] / ray_length;
  direction[1] = ray[1] / ray_length;
  direction[2] = ray[2] / ray_length;
 
  hex_mesh->computeTrackLengths( start_point, end_point, contribution );

  FRENSIE_REQUIRE_EQUAL( contribution.size(), 4 );
  FRENSIE_CHECK_EQUAL( Utility::get<0>(contribution[0]), 0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<1>(contribution[0]),
                                   (std::array<double,3>( {0.0, 3.611111111111111049e-01, 0.3125} )),
                                   1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<2>(contribution[0]),
                                   0.350784676235707,
                                   1e-10 );
  
  FRENSIE_CHECK_EQUAL( Utility::get<0>(contribution[1]), 2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<1>(contribution[1]),
                                   (std::array<double,3>( {0.3125, 0.5, 3.906250000000000000e-01} )),
                                   1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<2>(contribution[1]),
                                   0.210470805741424,
                                   1e-10 );
  
  FRENSIE_CHECK_EQUAL( Utility::get<0>(contribution[2]), 3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<1>(contribution[2]),
                                   (std::array<double,3>( {0.5, 5.833333333333333703e-01, 4.375000000000000000e-01} )),
                                   1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<2>(contribution[2]),
                                   0.280627740988566,
                                   1e-10 );

  FRENSIE_CHECK_EQUAL( Utility::get<0>(contribution[3]), 7 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<1>(contribution[3]),
                                   (std::array<double,3>( {0.75, 6.944444444444444198e-01, 0.5} )),
                                   1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<2>(contribution[3]),
                                   0.089800877116341,
                                   1e-10 );

  // particle starts outside mesh, and returns interaction planes that are
  // outside mesh before actual interaction plane
  start_point[0] = -0.25;
  start_point[1] = 0.25;
  start_point[2] = 0.25;
 
  end_point[0] = 0.01;
  end_point[1] = 0.99;
  end_point[2] = 0.25;
 
  ray[0] = end_point[0] - start_point[0];
  ray[1] = end_point[1] - start_point[1];
  ray[2] = end_point[2] - start_point[2];
 
  ray_length = Utility::vectorMagnitude(ray);
 
  direction[0] = ray[0] / ray_length;
  direction[1] = ray[1] / ray_length;
  direction[2] = ray[2] / ray_length;
 
  hex_mesh->computeTrackLengths( start_point, end_point, contribution );

  FRENSIE_REQUIRE_EQUAL( contribution.size(), 1 );
  FRENSIE_CHECK_EQUAL( Utility::get<0>(contribution[0]), 2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<1>(contribution[0]),
                                   (std::array<double,3>( {0.0, 9.615384615384614531e-01, 2.500000000000000000e-01} )),
                                   1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<2>(contribution[0]),
                                   0.030167187001735,
                                   1e-12);
  
  // particle starts outside mesh, enters mesh, and then exits mesh
  start_point[0] = 1.2;
  start_point[1] = 1.3;
  start_point[2] = 1.1;
 
  end_point[0] = -0.2;
  end_point[1] = -3;
  end_point[2] = 0.25;
 
  ray[0] = end_point[0] - start_point[0];
  ray[1] = end_point[1] - start_point[1];
  ray[2] = end_point[2] - start_point[2];
 
  ray_length = Utility::vectorMagnitude(ray);
 
  direction[0] = ray[0] / ray_length;
  direction[1] = ray[1] / ray_length;
  direction[2] = ray[2] / ray_length;
 
  hex_mesh->computeTrackLengths( start_point, end_point, contribution );
  
  FRENSIE_REQUIRE_EQUAL( contribution.size(), 2 );
  FRENSIE_CHECK_EQUAL( Utility::get<0>(contribution[0]), 7 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<1>(contribution[0]),
                                   (std::array<double,3>( {1.0, 6.857142857142859427e-01, 9.785714285714286476e-01} )),
                                   1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<2>(contribution[0]),
                                   0.198729768889349,
                                   1e-12 );
  FRENSIE_CHECK_EQUAL( Utility::get<0>(contribution[1]), 5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<1>(contribution[1]),
                                   (std::array<double,3>( {9.395348837209301918e-01, 0.5, 9.418604651162790775e-01} )),
                                   1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<2>(contribution[1]),
                                   0.535041685471324,
                                   1e-12 );
}

//---------------------------------------------------------------------------//
// bounding region cases (particle starts in boundary region and travels away
// from mesh on negative side)
FRENSIE_UNIT_TEST( StructuredHexMesh,
                   computeTrackLengths_boundary_region_special_case_negative_away_from_mesh )
{
  std::vector<double> x_planes( {0.0, 0.5, 1.0} ),
    y_planes( {0.0, 0.5, 1.0} ),
    z_planes( {0.0, 0.5, 1.0} );

  std::shared_ptr<Utility::StructuredHexMesh> hex_mesh(
              new Utility::StructuredHexMesh( x_planes, y_planes, z_planes ) );
  
  double start_point[3], end_point[3], ray[3], direction[3], ray_length;

  start_point[0] = -1e-13;
  start_point[1] = 0.25;
  start_point[2] = 0.25;
 
  end_point[0] = -0.25;
  end_point[1] = 0.25;
  end_point[2] = 0.25;
 
  ray[0] = end_point[0] - start_point[0];
  ray[1] = end_point[1] - start_point[1];
  ray[2] = end_point[2] - start_point[2];
 
  ray_length = Utility::vectorMagnitude(ray);
 
  direction[0] = ray[0] / ray_length;
  direction[1] = ray[1] / ray_length;
  direction[2] = ray[2] / ray_length;

  Utility::StructuredHexMesh::ElementHandleTrackLengthArray contribution;

  hex_mesh->computeTrackLengths( start_point, end_point, contribution );

  FRENSIE_CHECK_EQUAL( contribution.size(), 0 );
}

//---------------------------------------------------------------------------//
// bounding region cases (particle starts in boundary region and travels away
// from mesh on positive side)
FRENSIE_UNIT_TEST( StructuredHexMesh,
                   computeTrackLengths_boundary_region_special_case_positive_away_from_mesh )
{
  std::vector<double> x_planes( {0.0, 0.5, 1.0} ),
    y_planes( {0.0, 0.5, 1.0} ),
    z_planes( {0.0, 0.5, 1.0} );

  std::shared_ptr<Utility::StructuredHexMesh> hex_mesh(
              new Utility::StructuredHexMesh( x_planes, y_planes, z_planes ) );
  
  double start_point[3], end_point[3], ray[3], direction[3], ray_length;
  
  start_point[0] = 1+1e-13;
  start_point[1] = 0.25;
  start_point[2] = 0.25;
 
  end_point[0] = 2;
  end_point[1] = 0.25;
  end_point[2] = 0.25;
 
  ray[0] = end_point[0] - start_point[0];
  ray[1] = end_point[1] - start_point[1];
  ray[2] = end_point[2] - start_point[2];
 
  ray_length = Utility::vectorMagnitude(ray);
 
  direction[0] = ray[0] / ray_length;
  direction[1] = ray[1] / ray_length;
  direction[2] = ray[2] / ray_length;

  Utility::StructuredHexMesh::ElementHandleTrackLengthArray contribution;

  hex_mesh->computeTrackLengths( start_point, end_point, contribution );

  FRENSIE_CHECK_EQUAL( contribution.size(), 0 );
}

//---------------------------------------------------------------------------//
// bounding region cases (particle starts in boundary region and dies in
// boundary region)
FRENSIE_UNIT_TEST( StructuredHexMesh,
                   computeTrackLengths_boundary_region_special_case_stays_in_region )
{
  std::vector<double> x_planes( {0.0, 0.5, 1.0} ),
    y_planes( {0.0, 0.5, 1.0} ),
    z_planes( {0.0, 0.5, 1.0} );

  std::shared_ptr<Utility::StructuredHexMesh> hex_mesh(
              new Utility::StructuredHexMesh( x_planes, y_planes, z_planes ) );
  
  double start_point[3], end_point[3], ray[3], direction[3], ray_length;
  
  start_point[0] = 1+1e-13;
  start_point[1] = 0.25;
  start_point[2] = 0.25;
 
  end_point[0] = 1+1e-13;
  end_point[1] = 0.75;
  end_point[2] = 0.25;
 
  ray[0] = end_point[0] - start_point[0];
  ray[1] = end_point[1] - start_point[1];
  ray[2] = end_point[2] - start_point[2];
 
  ray_length = Utility::vectorMagnitude(ray);
 
  direction[0] = ray[0] / ray_length;
  direction[1] = ray[1] / ray_length;
  direction[2] = ray[2] / ray_length;

  Utility::StructuredHexMesh::ElementHandleTrackLengthArray contribution;

  hex_mesh->computeTrackLengths( start_point, end_point, contribution );

  FRENSIE_CHECK_EQUAL( contribution.size(), 0 );

  // particle starts in boundary region and dies in boundary region going
  // towards boundary region
  start_point[0] = 1+1e-13;
  start_point[1] = 0.25;
  start_point[2] = 0.25;
 
  end_point[0] = 1+1e-14;
  end_point[1] = 0.75;
  end_point[2] = 0.25;
 
  ray[0] = end_point[0] - start_point[0];
  ray[1] = end_point[1] - start_point[1];
  ray[2] = end_point[2] - start_point[2];
 
  ray_length = Utility::vectorMagnitude(ray);
 
  direction[0] = ray[0] / ray_length;
  direction[1] = ray[1] / ray_length;
  direction[2] = ray[2] / ray_length;
 
  hex_mesh->computeTrackLengths( start_point, end_point, contribution );

  FRENSIE_CHECK_EQUAL( contribution.size(), 0 );
  
  // same as last but on other side for y dimension
  start_point[0] = 0.25;
  start_point[1] = -1e-13;
  start_point[2] = 0.25;
 
  end_point[0] = 0.75;
  end_point[1] = -5e-10;
  end_point[2] = 0.25;
 
  ray[0] = end_point[0] - start_point[0];
  ray[1] = end_point[1] - start_point[1];
  ray[2] = end_point[2] - start_point[2];
 
  ray_length = Utility::vectorMagnitude(ray);
 
  direction[0] = ray[0] / ray_length;
  direction[1] = ray[1] / ray_length;
  direction[2] = ray[2] / ray_length;
 
  hex_mesh->computeTrackLengths( start_point, end_point, contribution );

  FRENSIE_CHECK_EQUAL( contribution.size(), 0 );
  
  // test particle starting in boundary region and stopping at hex face
  start_point[0] = 0.25;
  start_point[1] = -1e-13;
  start_point[2] = 0.25;
 
  end_point[0] = 0.75;
  end_point[1] = 0;
  end_point[2] = 0.25;
 
  ray[0] = end_point[0] - start_point[0];
  ray[1] = end_point[1] - start_point[1];
  ray[2] = end_point[2] - start_point[2];
 
  ray_length = Utility::vectorMagnitude(ray);
 
  direction[0] = ray[0] / ray_length;
  direction[1] = ray[1] / ray_length;
  direction[2] = ray[2] / ray_length;
 
  hex_mesh->computeTrackLengths( start_point, end_point, contribution );

  FRENSIE_REQUIRE_EQUAL( contribution.size(), 0 );
}

//---------------------------------------------------------------------------//
// bounding region cases (particle starts in boundary region and dies inside
// mesh)
FRENSIE_UNIT_TEST( StructuredHexMesh,
                   computeTrackLengths_boundary_region_special_case_enters_mesh )
{
  std::vector<double> x_planes( {0.0, 0.5, 1.0} ),
    y_planes( {0.0, 0.5, 1.0} ),
    z_planes( {0.0, 0.5, 1.0} );

  std::shared_ptr<Utility::StructuredHexMesh> hex_mesh(
              new Utility::StructuredHexMesh( x_planes, y_planes, z_planes ) );
  
  double start_point[3], end_point[3], ray[3], direction[3], ray_length;

  start_point[0] = 1+5e-13;
  start_point[1] = 0.25;
  start_point[2] = 0.25;
 
  end_point[0] = 0.5;
  end_point[1] = 0.75;
  end_point[2] = 0.25;
 
  ray[0] = end_point[0] - start_point[0];
  ray[1] = end_point[1] - start_point[1];
  ray[2] = end_point[2] - start_point[2];
 
  ray_length = Utility::vectorMagnitude(ray);
 
  direction[0] = ray[0] / ray_length;
  direction[1] = ray[1] / ray_length;
  direction[2] = ray[2] / ray_length;

  Utility::StructuredHexMesh::ElementHandleTrackLengthArray contribution;

  hex_mesh->computeTrackLengths( start_point, end_point, contribution );

  FRENSIE_REQUIRE_EQUAL( contribution.size(), 2 );
  FRENSIE_CHECK_EQUAL( Utility::get<0>(contribution[0]), 1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<1>(contribution[0]),
                                   (std::array<double,3>( {1.0, 0.25, 0.25} )),
                                   1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<2>(contribution[0]),
                                   0.353553390592743,
                                   1e-10 );
  FRENSIE_CHECK_EQUAL( Utility::get<0>(contribution[1]), 3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<1>(contribution[1]),
                                   (std::array<double,3>( {0.75, 0.5, 0.25} )),
                                   1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<2>(contribution[1]),
                                   0.353553390593451,
                                   1e-10 );
}

//---------------------------------------------------------------------------//
// Test the ability for the function computeTrackLengths to find the correct
// entry point that a particle enters a mesh at. Specifically test the other
// dimensions under specific conditions where multiple intersection points are
// inside mesh but a dimension after the first one in order of x,y,z is the
// true intersection point
FRENSIE_UNIT_TEST( StructuredHexMesh,
                   computeTrackLengths_enters_correct_dimension )
{
  std::vector<double> x_planes( {0.0, 0.5, 1.0} ),
    y_planes( {0.0, 0.5, 1.0} ),
    z_planes( {0.0, 0.5, 1.0} );

  std::shared_ptr<Utility::StructuredHexMesh> hex_mesh(
              new Utility::StructuredHexMesh( x_planes, y_planes, z_planes ) );
  
  double start_point[3], end_point[3], ray[3], direction[3], ray_length;

  start_point[0] = 0.25;
  start_point[1] = 0.25;
  start_point[2] = -1e-9;
 
  end_point[0] = 0.6;
  end_point[1] = 0.25;
  end_point[2] = 0.25;
 
  ray[0] = end_point[0] - start_point[0];
  ray[1] = end_point[1] - start_point[1];
  ray[2] = end_point[2] - start_point[2];
 
  ray_length = Utility::vectorMagnitude(ray);
 
  direction[0] = ray[0] / ray_length;
  direction[1] = ray[1] / ray_length;
  direction[2] = ray[2] / ray_length;

  Utility::StructuredHexMesh::ElementHandleTrackLengthArray contribution;

  hex_mesh->computeTrackLengths( start_point, end_point, contribution );

  FRENSIE_REQUIRE_EQUAL( contribution.size(), 2 );
  
  FRENSIE_CHECK_EQUAL( Utility::get<0>(contribution[0]), 0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<1>(contribution[0]),
                                   (std::array<double,3>( {0.25, 0.25, 0.0} )),
                                   1e-8 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<2>(contribution[0]),
                                   0.307225901089085,
                                   1e-10 );
  FRENSIE_CHECK_EQUAL( Utility::get<0>(contribution[1]), 1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<1>(contribution[1]),
                                   (std::array<double,3>( {0.5, 0.25, 1.785714282857143176e-01} )),
                                   1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<2>(contribution[1]),
                                   0.122890361123820,
                                   1e-10 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( ray_length - 1.720465048851618e-09,
                                   Utility::get<2>(contribution[0]) +
                                   Utility::get<2>(contribution[1]),
                                   1e-10);
}

//---------------------------------------------------------------------------//
// Check that the mesh data can be exported
FRENSIE_UNIT_TEST( StructuredHexMesh, exportData )
{
  std::vector<double> x_planes( {0.0, 0.5, 1.0} ),
    y_planes( {0.0, 0.5, 1.0} ),
    z_planes( {0.0, 0.5, 1.0} );

  std::shared_ptr<Utility::StructuredHexMesh> hex_mesh(
              new Utility::StructuredHexMesh( x_planes, y_planes, z_planes ) );

  // Export an empty mesh
#ifdef HAVE_FRENSIE_MOAB
  FRENSIE_CHECK_NO_THROW( hex_mesh->exportData( "empty_test_hex_mesh.vtk" ) );
#else
  FRENSIE_CHECK_THROW( hex_mesh->exportData( "empty_test_hex_mesh.vtk" ),
                       std::logic_error );
#endif

  // Export the mesh with tag data
  Utility::StructuredHexMesh::TagNameSet tag_name_set( {"mean", "rel_err"} );
  
  Utility::StructuredHexMesh::MeshElementHandleDataMap element_data_map;

  for( size_t i = 0; i < 8; ++i )
  {
    element_data_map[i]["mean"] = std::vector<std::pair<std::string,double> >( {std::make_pair("b0", 0.1*i), std::make_pair("b1", 0.2*i), std::make_pair("b2", 0.3*i)} );
    element_data_map[i]["rel_err"] = std::vector<std::pair<std::string,double> >( {std::make_pair("b0", 0.01), std::make_pair("b1", 0.001), std::make_pair("b2", 0.01)} );
  }

#ifdef HAVE_FRENSIE_MOAB
  FRENSIE_CHECK_NO_THROW( hex_mesh->exportData( "test_hex_mesh.vtk",
                                                tag_name_set,
                                                element_data_map ) );
#else
  FRENSIE_CHECK_THROW( hex_mesh->exportData( "test_hex_mesh.vtk",
                                             tag_name_set,
                                             element_data_map ),
                       std::logic_error );
#endif
}

//---------------------------------------------------------------------------//
// Check that a structured hex mesh can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( StructuredHexMesh, archive, TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;
  
  std::string archive_base_name( "test_structured_hex_mesh" );
  std::ostringstream archive_ostream;

  // Create and archive some uniform distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::vector<double> x_planes( {0.0, 0.5, 1.0} ),
    y_planes( {0.0, 0.5, 1.0} ),
    z_planes( {0.0, 0.5, 1.0} );

    std::unique_ptr<Utility::StructuredHexMesh> concrete_hex_mesh(
              new Utility::StructuredHexMesh( x_planes, y_planes, z_planes ) );

    std::shared_ptr<Utility::Mesh> hex_mesh( 
              new Utility::StructuredHexMesh( x_planes, y_planes, z_planes ) );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( concrete_hex_mesh ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( hex_mesh ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::unique_ptr<Utility::StructuredHexMesh> concrete_hex_mesh;
  std::shared_ptr<Utility::Mesh> hex_mesh;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( concrete_hex_mesh ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( hex_mesh ) );

  iarchive.reset();

  {
    FRENSIE_CHECK_EQUAL( concrete_hex_mesh->getNumberOfElements(), 8 );

    FRENSIE_CHECK_EQUAL( concrete_hex_mesh->getXPlaneLocation( 0 ), 0.0 );
    FRENSIE_CHECK_EQUAL( concrete_hex_mesh->getXPlaneLocation( 1 ), 0.5 );
    FRENSIE_CHECK_EQUAL( concrete_hex_mesh->getXPlaneLocation( 2 ), 1.0 );

    FRENSIE_CHECK_EQUAL( concrete_hex_mesh->getYPlaneLocation( 0 ), 0.0 );
    FRENSIE_CHECK_EQUAL( concrete_hex_mesh->getYPlaneLocation( 1 ), 0.5 );
    FRENSIE_CHECK_EQUAL( concrete_hex_mesh->getYPlaneLocation( 2 ), 1.0 );

    FRENSIE_CHECK_EQUAL( concrete_hex_mesh->getZPlaneLocation( 0 ), 0.0 );
    FRENSIE_CHECK_EQUAL( concrete_hex_mesh->getZPlaneLocation( 1 ), 0.5 );
    FRENSIE_CHECK_EQUAL( concrete_hex_mesh->getZPlaneLocation( 2 ), 1.0 );
  }

  {
    FRENSIE_CHECK_EQUAL( hex_mesh->getNumberOfElements(), 8 );

    Utility::StructuredHexMesh::ElementHandleVolumeMap volume_map;
  
    hex_mesh->getElementVolumes( volume_map );

    FRENSIE_REQUIRE_EQUAL( volume_map.size(), 8 );
    FRENSIE_CHECK_FLOATING_EQUALITY( volume_map[0], 0.125, 1e-12);
    FRENSIE_CHECK_FLOATING_EQUALITY( volume_map[1], 0.125, 1e-12);
    FRENSIE_CHECK_FLOATING_EQUALITY( volume_map[2], 0.125, 1e-12);
    FRENSIE_CHECK_FLOATING_EQUALITY( volume_map[3], 0.125, 1e-12);
    FRENSIE_CHECK_FLOATING_EQUALITY( volume_map[4], 0.125, 1e-12);
    FRENSIE_CHECK_FLOATING_EQUALITY( volume_map[5], 0.125, 1e-12);
    FRENSIE_CHECK_FLOATING_EQUALITY( volume_map[6], 0.125, 1e-12);
    FRENSIE_CHECK_FLOATING_EQUALITY( volume_map[7], 0.125, 1e-12);

    double point1[3] {0.25, 0.25, 0.25};
    double point2[3] {0.75, 0.25, 0.25};
    double point3[3] {0.25, 0.75, 0.25};
    double point4[3] {0.75, 0.75, 0.25};
    double point5[3] {0.25, 0.25, 0.75};
    double point6[3] {0.75, 0.25, 0.75};
    double point7[3] {0.25, 0.75, 0.75};
    double point8[3] {0.75, 0.75, 0.75};
    
    FRENSIE_CHECK_EQUAL( hex_mesh->whichElementIsPointIn(point1), 0);
    FRENSIE_CHECK_EQUAL( hex_mesh->whichElementIsPointIn(point2), 1);
    FRENSIE_CHECK_EQUAL( hex_mesh->whichElementIsPointIn(point3), 2);
    FRENSIE_CHECK_EQUAL( hex_mesh->whichElementIsPointIn(point4), 3);
    FRENSIE_CHECK_EQUAL( hex_mesh->whichElementIsPointIn(point5), 4);
    FRENSIE_CHECK_EQUAL( hex_mesh->whichElementIsPointIn(point6), 5);
    FRENSIE_CHECK_EQUAL( hex_mesh->whichElementIsPointIn(point7), 6);
    FRENSIE_CHECK_EQUAL( hex_mesh->whichElementIsPointIn(point8), 7);
  }
}

//---------------------------------------------------------------------------//
// end tstStructuredHexMesh.cpp
//---------------------------------------------------------------------------//
