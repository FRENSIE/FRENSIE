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

  std::cout << hex_mesh->d_x_planes << std::endl;
  std::cout << hex_mesh->d_y_planes << std::endl;
  std::cout << hex_mesh->d_z_planes << std::endl;

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
  double point5[3] {1.0 + 1e-6, 0.5, 0.5};
  double point6[3] {0.5, 1.0 + 1e-6, 0.5};
  double point7[3] {0.5, 0.5, 1.0 + 1e-6};
  //points on lower dimension boundaries
  double point8[3] {-1e-6, 0.5, 0.5};
  double point9[3] {0.5, -1e-6, 0.5};
  double point10[3] {0.5, 0.5, -1e-6};

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
 
 Teuchos::Array<std::pair<unsigned,double>> contribution1 =
  hex_mesh->computeTrackLengths( start_point,
                                 end_point,
                                 direction );

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
 
 Teuchos::Array<std::pair<unsigned,double>> contribution2 =
  hex_mesh->computeTrackLengths( start_point,
                                 end_point,
                                 direction );

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
 
 Teuchos::Array<std::pair<unsigned,double>> contribution3 =
  hex_mesh->computeTrackLengths( start_point,
                                 end_point,
                                 direction );

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
 
  Teuchos::Array<std::pair<unsigned,double>> contribution4 =
    hex_mesh->computeTrackLengths( start_point,
                                 end_point,
                                 direction );

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
 
  Teuchos::Array<std::pair<unsigned,double>> contribution1 =
    hex_mesh->computeTrackLengths( start_point,
                                 end_point,
                                 direction );

  TEST_ASSERT(contribution1.size() == 1);
  TEST_ASSERT(contribution1[0].first == 0);
  TEST_ASSERT(contribution1[0].second < ray_length + 1e-10 && contribution1[0].second > ray_length - 1e-10 );  

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
 
  Teuchos::Array<std::pair<unsigned,double>> contribution1 =
    hex_mesh->computeTrackLengths( start_point,
                                 end_point,
                                 direction );

  TEST_ASSERT(contribution1.size() == 2);
  TEST_ASSERT(contribution1[0].first == 0);
  TEST_ASSERT(contribution1[1].first == 1);
  TEST_ASSERT(ray_length - 1e-10 <= contribution1[0].second + contribution1[1].second &&
    contribution1[0].second + contribution1[1].second <= ray_length + 1e-10);
    
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
 
  Teuchos::Array<std::pair<unsigned,double>> contribution2 =
    hex_mesh->computeTrackLengths( start_point,
                                 end_point,
                                 direction );

  TEST_ASSERT(contribution2.size() == 2);
  TEST_ASSERT(contribution2[0].first == 7);
  TEST_ASSERT(contribution2[1].first == 3);
  TEST_ASSERT(ray_length - 1e-10 <= contribution2[0].second + contribution2[1].second &&
    contribution2[0].second + contribution2[1].second <= ray_length + 1e-10);

}
