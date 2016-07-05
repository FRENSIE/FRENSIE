//---------------------------------------------------------------------------//
//!
//! \file   tstStructuredHexMesh.cpp
//! \author Philip Britt
//! \brief  StructuredHexMesh class unit tests
//!
//---------------------------------------------------------------------------//

// std includes
#include <iostream>
#include <memory>
#include <utility>

// boost includes
#include <boost/unordered_map.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>

// Frensie Includes
#include "Utility_StructuredHexMesh.hpp"
#include "Utility_DirectionHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<Utility::StructuredHexMesh> hex_mesh;

//---------------------------------------------------------------------------//
// test constructing the mesh.
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( StructuredHexMesh, construct_mesh)
{

  Teuchos::Array<double> x_planes, y_planes, z_planes;
  
  x_planes.push_back(0);
  x_planes.push_back(0.5);
  x_planes.push_back(1);
  y_planes.push_back(0);
  y_planes.push_back(0.5);
  y_planes.push_back(1);
  z_planes.push_back(0);
  z_planes.push_back(0.5);
  z_planes.push_back(1);
  
  TEST_NOTHROW( hex_mesh.reset( new Utility::StructuredHexMesh( x_planes,
                                                                y_planes,
                                                                z_planes ) ) );

  TEST_EQUALITY( x_planes.size(), hex_mesh->getNumberOfXPlanes() );
  for(unsigned i = 0; i < x_planes.size(); ++i)
  {
    TEST_FLOATING_EQUALITY( hex_mesh->getXPlaneLocation(i), x_planes[i], 1e-12 );
  }

  TEST_EQUALITY( y_planes.size(), hex_mesh->getNumberOfYPlanes() );
  for(unsigned i = 0; i < y_planes.size(); ++i)
  {
    TEST_FLOATING_EQUALITY( hex_mesh->getYPlaneLocation(i), y_planes[i], 1e-12 );
  }

  TEST_EQUALITY( z_planes.size(), hex_mesh->getNumberOfZPlanes() );
  for(unsigned i = 0; i < z_planes.size(); ++i)
  {
    TEST_FLOATING_EQUALITY( hex_mesh->getZPlaneLocation(i), z_planes[i], 1e-12 );
  }
  
  TEST_EQUALITY( (z_planes.size()-1) * (y_planes.size()-1) * (x_planes.size()-1),
                 std::distance( hex_mesh->getStartHexIDIterator(), hex_mesh->getEndHexIDIterator() ) );

}

//---------------------------------------------------------------------------//
// Test the calculateVolumes method
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( StructuredHexMesh, calculate_volume)
{

  boost::unordered_map<unsigned long, double> volume_map =
    hex_mesh->calculateVolumes();
    
  TEST_FLOATING_EQUALITY( volume_map[0], 0.125, 1e-12);
  TEST_FLOATING_EQUALITY( volume_map[1], 0.125, 1e-12);
  TEST_FLOATING_EQUALITY( volume_map[2], 0.125, 1e-12);
  TEST_FLOATING_EQUALITY( volume_map[3], 0.125, 1e-12);
  TEST_FLOATING_EQUALITY( volume_map[4], 0.125, 1e-12);
  TEST_FLOATING_EQUALITY( volume_map[5], 0.125, 1e-12);
  TEST_FLOATING_EQUALITY( volume_map[6], 0.125, 1e-12);
  TEST_FLOATING_EQUALITY( volume_map[7], 0.125, 1e-12);
  TEST_EQUALITY(volume_map.size(), 8);
  
}


//---------------------------------------------------------------------------//
// test whether or not the point in mesh method works
//---------------------------------------------------------------------------//

TEUCHOS_UNIT_TEST( StructuredHexMesh, is_point_in_mesh)
{

  //points inside mesh and not in boundary region
  double point1[3] {0.5, 0.5, 0.5};
  double point2[3] {0.25, 0.25, 0.25};
  double point3[3] {0.75, 0.75, 0.75};
  double point4[3] {0.25, 0.9, 0.23};
  
  TEST_ASSERT( hex_mesh->isPointInMesh(point1) );
  TEST_ASSERT( hex_mesh->isPointInMesh(point2) );
  TEST_ASSERT( hex_mesh->isPointInMesh(point3) );
  TEST_ASSERT( hex_mesh->isPointInMesh(point4) );
  
  //points not inside mesh but inside boundary region (should still return true)
  //points on upper dimension boundaries
  double point5[3] {1.0 + 1e-10, 0.5, 0.5};
  double point6[3] {0.5, 1.0 + 1e-10, 0.5};
  double point7[3] {0.5, 0.5, 1.0 + 1e-10};
  //points on lower dimension boundaries
  double point8[3] {-1e-10, 0.5, 0.5};
  double point9[3] {0.5, -1e-10, 0.5};
  double point10[3] {0.5, 0.5, -1e-10};

  TEST_ASSERT( hex_mesh->isPointInMesh(point5) );
  TEST_ASSERT( hex_mesh->isPointInMesh(point6) );
  TEST_ASSERT( hex_mesh->isPointInMesh(point7) );
  TEST_ASSERT( hex_mesh->isPointInMesh(point8) );
  TEST_ASSERT( hex_mesh->isPointInMesh(point9) );
  TEST_ASSERT( hex_mesh->isPointInMesh(point10) );

  //points outside of mesh
  //points on upper dimension boundaries
  double point11[3] {1.0 + 1e-5, 0.5, 0.5};
  double point12[3] {0.5, 1.0 + 1e-5, 0.5};
  double point13[3] {0.5, 0.5, 1.0 + 1e-5};
  //points on lower dimension boundaries
  double point14[3] {-1e-5, 0.5, 0.5};
  double point15[3] {0.5, -1e-5, 0.5};
  double point16[3] {0.5, 0.5, -1e-5};

  TEST_ASSERT( !hex_mesh->isPointInMesh(point11) );
  TEST_ASSERT( !hex_mesh->isPointInMesh(point12) );
  TEST_ASSERT( !hex_mesh->isPointInMesh(point13) );
  TEST_ASSERT( !hex_mesh->isPointInMesh(point14) );
  TEST_ASSERT( !hex_mesh->isPointInMesh(point15) );
  TEST_ASSERT( !hex_mesh->isPointInMesh(point16) );  
}

//---------------------------------------------------------------------------//
// test whether or not the whichHexIsPointIn method works
//---------------------------------------------------------------------------//

TEUCHOS_UNIT_TEST( StructuredHexMesh, which_hex_is_point_in)
{

  //test points in the middle of the mesh elements. Points should be in order for index returned
  double point1[3] {0.25, 0.25, 0.25};
  double point2[3] {0.75, 0.25, 0.25};
  double point3[3] {0.25, 0.75, 0.25};
  double point4[3] {0.75, 0.75, 0.25};
  double point5[3] {0.25, 0.25, 0.75};
  double point6[3] {0.75, 0.25, 0.75};
  double point7[3] {0.25, 0.75, 0.75};
  double point8[3] {0.75, 0.75, 0.75};
  
  TEST_ASSERT( hex_mesh->whichHexIsPointIn(point1) == 0);
  TEST_ASSERT( hex_mesh->whichHexIsPointIn(point2) == 1);
  TEST_ASSERT( hex_mesh->whichHexIsPointIn(point3) == 2);
  TEST_ASSERT( hex_mesh->whichHexIsPointIn(point4) == 3);
  TEST_ASSERT( hex_mesh->whichHexIsPointIn(point5) == 4);
  TEST_ASSERT( hex_mesh->whichHexIsPointIn(point6) == 5);
  TEST_ASSERT( hex_mesh->whichHexIsPointIn(point7) == 6);
  TEST_ASSERT( hex_mesh->whichHexIsPointIn(point8) == 7);
  
  /* test points on mesh boundaries.*/
  double point9[3] {0, 0, 0};
  double point10[3] {0.5, 0.5, 0.5};
  double point11[3] {1.0, 1.0, 1.0};
  TEST_ASSERT( hex_mesh->whichHexIsPointIn(point9) == 0);
  TEST_ASSERT( hex_mesh->whichHexIsPointIn(point10) == 7);
  TEST_ASSERT( hex_mesh->whichHexIsPointIn(point11) == 7);
}

//---------------------------------------------------------------------------//
// test simple cases of rays not interacting with mesh and computeTrackLengths
// returning empty arrays
//---------------------------------------------------------------------------//

TEUCHOS_UNIT_TEST( StructuredHexMesh, ray_does_not_intersect_with_mesh)
{

 double start_point[3], end_point[3], ray[3], direction[3], ray_length;
 
 //test a point heading away from the mesh and not intersecting with anything
 
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
 
 Teuchos::Array<std::pair<unsigned long,double>> contribution1 =
  hex_mesh->computeTrackLengths( start_point,
                                 end_point,
                                 direction,
                                 ray_length );

  TEST_ASSERT(contribution1.size() == 0);
  
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
 
 Teuchos::Array<std::pair<unsigned long,double>> contribution2 =
  hex_mesh->computeTrackLengths( start_point,
                                 end_point,
                                 direction,
                                 ray_length );

  TEST_ASSERT(contribution2.size() == 0);
  
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
 
 Teuchos::Array<std::pair<unsigned long,double>> contribution3 =
  hex_mesh->computeTrackLengths( start_point,
                                 end_point,
                                 direction,
                                 ray_length );

  TEST_ASSERT(contribution3.size() == 0);
  
  //particle ends in boundary region. Should give zero since pushing it up to the
  //  actual boundary would be longer than the particle track length
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
 
  Teuchos::Array<std::pair<unsigned long,double>> contribution4 =
    hex_mesh->computeTrackLengths( start_point,
                                   end_point,
                                   direction,
                                   ray_length );

  TEST_ASSERT(contribution4.size() == 0);
 
}

//---------------------------------------------------------------------------//
// testing cases of rays interacting with mesh and returning appropriate results
// First test is particle track is entirely within one cell
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( StructuredHexMesh, track_length_in_one_cell)
{


  double start_point[3], end_point[3], ray[3], direction[3], ray_length;  
  
  //should also note that because all direction components are positive, this also
  //tests whether or not the function appropriately finds different interaction planes and hex index planes
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
 
  Teuchos::Array<std::pair<unsigned long,double>> contribution1 =
    hex_mesh->computeTrackLengths( start_point,
                                   end_point,
                                   direction,
                                   ray_length );

  TEST_ASSERT(contribution1.size() == 1);
  TEST_ASSERT(contribution1[0].first == 0);
  TEST_FLOATING_EQUALITY(contribution1[0].second, 0.339116499156263, 1e-10);  

}

//---------------------------------------------------------------------------//
// second test: particle starts in mesh and crosses into another mesh element and dies in that mesh element
//---------------------------------------------------------------------------//

TEUCHOS_UNIT_TEST( StructuredHexMesh, particle_starts_in_one_hex_element_and_ends_in_another)
{


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
 
  Teuchos::Array<std::pair<unsigned long,double>> contribution1 =
    hex_mesh->computeTrackLengths( start_point,
                                   end_point,
                                   direction,
                                   ray_length );

  TEST_ASSERT(contribution1.size() == 2);
  TEST_ASSERT(contribution1[0].first == 0);
  TEST_ASSERT(contribution1[1].first == 1);
  TEST_FLOATING_EQUALITY(contribution1[0].second, 0.419523539268061, 1e-10);
  TEST_FLOATING_EQUALITY(contribution1[1].second, 0.104880884817015, 1e-10);
    
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
 
  Teuchos::Array<std::pair<unsigned long,double>> contribution2 =
    hex_mesh->computeTrackLengths( start_point,
                                   end_point,
                                   direction,
                                   ray_length );

  TEST_ASSERT(contribution2.size() == 2);
  TEST_ASSERT(contribution2[0].first == 7);
  TEST_ASSERT(contribution2[1].first == 3);
  TEST_FLOATING_EQUALITY(contribution2[0].second, 0.303009696269043, 1e-10);
  TEST_FLOATING_EQUALITY(contribution2[1].second, 0.252508080224203, 1e-10);
  
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
 
  Teuchos::Array<std::pair<unsigned long,double>> contribution3 =
    hex_mesh->computeTrackLengths( start_point,
                                   end_point,
                                   direction,
                                   ray_length );

  TEST_ASSERT(contribution3.size() == 3);
  TEST_EQUALITY(contribution3[0].first, 7);
  TEST_EQUALITY(contribution3[1].first, 5);
  TEST_EQUALITY(contribution3[2].first, 4);
  TEST_FLOATING_EQUALITY(contribution3[0].second, 0.131267855928251, 1e-10);
  TEST_FLOATING_EQUALITY(contribution3[1].second, 0.177597687432339, 1e-10);
  TEST_FLOATING_EQUALITY(contribution3[2].second, 0.216205880352413, 1e-10);
  
  double sum_of_segments = contribution3[0].second + contribution3[1].second + contribution3[2].second;
  
  TEST_FLOATING_EQUALITY(sum_of_segments, ray_length, 1e-10);
}

//---------------------------------------------------------------------------//
// third test: Particle starts in mesh and exits mesh
//---------------------------------------------------------------------------//

TEUCHOS_UNIT_TEST(StructuredHexMesh, starts_in_mesh_and_exits_mesh)
{

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
 
  Teuchos::Array<std::pair<unsigned long,double>> contribution1 =
    hex_mesh->computeTrackLengths( start_point,
                                   end_point,
                                   direction,
                                   ray_length );

  TEST_ASSERT(contribution1.size() == 1);
  TEST_ASSERT(contribution1[0].first == 0);
  TEST_ASSERT(contribution1[0].second == 0.25);

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
 
  Teuchos::Array<std::pair<unsigned long,double>> contribution2 =
    hex_mesh->computeTrackLengths( start_point,
                                   end_point,
                                   direction,
                                   ray_length );
  
  TEST_EQUALITY( contribution2.size(), 3);
  TEST_EQUALITY( contribution2[0].first, 4);
  TEST_EQUALITY( contribution2[1].first, 0);
  TEST_EQUALITY( contribution2[2].first, 1);
  TEST_FLOATING_EQUALITY( contribution2[0].second, 0.493120998659465, 1e-10);
  TEST_FLOATING_EQUALITY( contribution2[1].second, 0.064314616453253, 1e-10);
  TEST_FLOATING_EQUALITY( contribution2[2].second, 0.519951969636160, 1e-10);

}

//---------------------------------------------------------------------------//
// testing cases of where the particle starts outside of the mesh and enters the mesh
// simple cases of particle entering mesh
//---------------------------------------------------------------------------//

TEUCHOS_UNIT_TEST(StructuredHexMesh, particle_starts_outside_mesh_and_dies_in_mesh)
{

  double start_point[3], end_point[3], ray[3], direction[3], ray_length;
    
  //particle starts outside mesh and enters first cell
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
 
  Teuchos::Array<std::pair<unsigned long,double>> contribution1 =
    hex_mesh->computeTrackLengths( start_point,
                                   end_point,
                                   direction,
                                   ray_length );

  TEST_ASSERT(contribution1.size() == 1);
  TEST_ASSERT(contribution1[0].first == 0);
  TEST_ASSERT(contribution1[0].second == 0.25);

  //particle starts outside mesh,crosses multiple planes inside mesh, and dies inside mesh
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
 
  Teuchos::Array<std::pair<unsigned long,double>> contribution2 =
    hex_mesh->computeTrackLengths( start_point,
                                   end_point,
                                   direction,
                                   ray_length );

  TEST_EQUALITY(contribution2.size(), 4);
  TEST_EQUALITY(contribution2[0].first, 0);
  TEST_EQUALITY(contribution2[1].first, 2);
  TEST_EQUALITY(contribution2[2].first, 3);
  TEST_EQUALITY(contribution2[3].first, 7);
  
  TEST_FLOATING_EQUALITY(contribution2[0].second, 0.350784676235707, 1e-10);
  TEST_FLOATING_EQUALITY(contribution2[1].second, 0.210470805741424, 1e-10);
  TEST_FLOATING_EQUALITY(contribution2[2].second, 0.280627740988566, 1e-10);
  TEST_FLOATING_EQUALITY(contribution2[3].second, 0.089800877116341, 1e-10);

  

  //particle starts outside mesh, and returns interaction planes that are outside mesh before actual interaction plane
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
 
  Teuchos::Array<std::pair<unsigned long,double>> contribution3 =
    hex_mesh->computeTrackLengths( start_point,
                                   end_point,
                                   direction,
                                   ray_length );

  TEST_EQUALITY(contribution3.size(), 1);
  TEST_EQUALITY(contribution3[0].first, 2);
  TEST_FLOATING_EQUALITY(contribution3[0].second, 0.030167187001735, 1e-10);
  
  //particle starts outside mesh, enters mesh, and then exits mesh
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
 
  Teuchos::Array<std::pair<unsigned long,double>> contribution4 =
    hex_mesh->computeTrackLengths( start_point,
                                   end_point,
                                   direction,
                                   ray_length );
  
  TEST_EQUALITY(contribution4.size(), 2);
  TEST_EQUALITY(contribution4[0].first, 7);
  TEST_EQUALITY(contribution4[1].first, 5);
  TEST_FLOATING_EQUALITY(contribution4[0].second, 0.198729768889349, 1e-10);
  TEST_FLOATING_EQUALITY(contribution4[1].second, 0.535041685471324, 1e-10);

}

//---------------------------------------------------------------------------//
// boundary region cases
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
// particle starts in boundary region and travels away from mesh on negative side
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST(StructuredHexMesh, boundary_region_particle_travles_away_from_mesh_negative)
{

  double start_point[3], end_point[3], ray[3], direction[3], ray_length;

  start_point[0] = -1e-11;
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
 
  Teuchos::Array<std::pair<unsigned long,double>> contribution1 =
    hex_mesh->computeTrackLengths( start_point,
                                   end_point,
                                   direction,
                                   ray_length );

  TEST_EQUALITY(contribution1.size(), 0);
}

//---------------------------------------------------------------------------//
// particle starts in boundary region and travels away from mesh on positive side
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST(StructuredHexMesh, boundary_region_particle_travels_away_from_mesh_positive)
{
  double start_point[3], end_point[3], ray[3], direction[3], ray_length;
  start_point[0] = 1+1e-11;
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
 
  Teuchos::Array<std::pair<unsigned long,double>> contribution1 =
    hex_mesh->computeTrackLengths( start_point,
                                   end_point,
                                   direction,
                                   ray_length );

  TEST_EQUALITY(contribution1.size(), 0);
}

//---------------------------------------------------------------------------//
// particle starts in boundary region and dies in boundary region
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST(StructuredHexMesh, boundary_region_particle_starts_and_dies_in_mesh)
{
  double start_point[3], end_point[3], ray[3], direction[3], ray_length;
  start_point[0] = 1+1e-11;
  start_point[1] = 0.25;
  start_point[2] = 0.25;
 
  end_point[0] = 1+1e-11;
  end_point[1] = 0.75;
  end_point[2] = 0.25;
 
  ray[0] = end_point[0] - start_point[0];
  ray[1] = end_point[1] - start_point[1];
  ray[2] = end_point[2] - start_point[2];
 
  ray_length = Utility::vectorMagnitude(ray);
 
  direction[0] = ray[0] / ray_length;
  direction[1] = ray[1] / ray_length;
  direction[2] = ray[2] / ray_length;
 
  Teuchos::Array<std::pair<unsigned long,double>> contribution1 =
    hex_mesh->computeTrackLengths( start_point,
                                   end_point,
                                   direction,
                                   ray_length );

  TEST_EQUALITY(contribution1.size(), 0);

  //particle starts in boundary region and dies in boundary region going towards boundary region
  start_point[0] = 1+1e-11;
  start_point[1] = 0.25;
  start_point[2] = 0.25;
 
  end_point[0] = 1+1e-12;
  end_point[1] = 0.75;
  end_point[2] = 0.25;
 
  ray[0] = end_point[0] - start_point[0];
  ray[1] = end_point[1] - start_point[1];
  ray[2] = end_point[2] - start_point[2];
 
  ray_length = Utility::vectorMagnitude(ray);
 
  direction[0] = ray[0] / ray_length;
  direction[1] = ray[1] / ray_length;
  direction[2] = ray[2] / ray_length;
 
  Teuchos::Array<std::pair<unsigned long,double>> contribution2 =
    hex_mesh->computeTrackLengths( start_point,
                                   end_point,
                                   direction,
                                   ray_length );

  TEST_EQUALITY(contribution2.size(), 0);
  
  //same as last but on other side for y dimension
  start_point[0] = 0.25;
  start_point[1] = -1e-11;
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
 
  Teuchos::Array<std::pair<unsigned long,double>> contribution3 =
    hex_mesh->computeTrackLengths( start_point,
                                   end_point,
                                   direction,
                                   ray_length );

  TEST_EQUALITY(contribution3.size(), 0);
  
  //test particle starting in boundary region and stopping at hex face
  start_point[0] = 0.25;
  start_point[1] = -1e-11;
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
 
  Teuchos::Array<std::pair<unsigned long,double>> contribution4 =
    hex_mesh->computeTrackLengths( start_point,
                                   end_point,
                                   direction,
                                   ray_length );

  TEST_EQUALITY(contribution4.size(), 0);
}

//---------------------------------------------------------------------------//
// particle starts in boundary region and dies inside mesh
//---------------------------------------------------------------------------//

TEUCHOS_UNIT_TEST(StructuredHexMesh, boundary_region_enters_mesh)
{
  double start_point[3], end_point[3], ray[3], direction[3], ray_length;

  start_point[0] = 1+1e-11;
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
 
  Teuchos::Array<std::pair<unsigned long,double>> contribution1 =
    hex_mesh->computeTrackLengths( start_point,
                                   end_point,
                                   direction,
                                   ray_length );

  TEST_EQUALITY(contribution1.size(), 2);
  TEST_EQUALITY(contribution1[0].first, 1);
  TEST_EQUALITY(contribution1[1].first, 3);
  TEST_FLOATING_EQUALITY(contribution1[0].second, 0.353553390596809, 1e-12);
  TEST_FLOATING_EQUALITY(contribution1[1].second, 0.353553390596809, 1e-12);


}

//---------------------------------------------------------------------------//
// Test the ability for the function computeTrackLengths to find the correct entry
// point that a particle enters a mesh at. Specifically test the other dimensions 
// under specific conditions where multiple intersection points are inside mesh
// but a dimension after the first one in order of x,y,z is the true intersection point
//---------------------------------------------------------------------------//

TEUCHOS_UNIT_TEST(StructuredHexMesh, particle_enters_mesh_dimension_test)
{

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
 
  Teuchos::Array<std::pair<unsigned long,double>> contribution1 =
    hex_mesh->computeTrackLengths( start_point,
                                   end_point,
                                   direction,
                                   ray_length );

  TEST_EQUALITY(contribution1.size(), 2);
  TEST_EQUALITY(contribution1[0].first, 0);
  TEST_EQUALITY(contribution1[1].first, 1);
  TEST_FLOATING_EQUALITY(contribution1[0].second, 0.307225901089085,1e-10);
  TEST_FLOATING_EQUALITY(contribution1[1].second,  0.122890361123820 ,1e-10);
  TEST_FLOATING_EQUALITY(ray_length - 1.720465048851618e-09, contribution1[0].second
    + contribution1[1].second, 1e-10);

}
