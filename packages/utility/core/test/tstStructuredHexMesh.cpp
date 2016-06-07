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

  double point_in_mesh[3] {0.5, 0.5, 0.5};
  
  double point_outside_of_mesh[3] {2, -10, 0.5};
  
  bool inside_mesh = hex_mesh->isPointInMesh(point_in_mesh);
  bool outside_mesh = hex_mesh->isPointInMesh(point_outside_of_mesh);
  TEST_ASSERT(inside_mesh);
  TEST_ASSERT(!outside_mesh);

}

//---------------------------------------------------------------------------//
// test whether or not the whichHexIsPointIn method works
//---------------------------------------------------------------------------//

TEUCHOS_UNIT_TEST( StructuredHexMesh, which_hex_is_point_in)
{

  double point1[3] {0.25, 0.25, 0.25};
  double point2[3] {0.75, 0.25, 0.25};
  double point3[3] {0.25, 0.75, 0.25};
  double point4[3] {0.75, 0.75, 0.25};
  double point5[3] {0.25, 0.25, 0.75};
  double point6[3] {0.75, 0.25, 0.75};
  double point7[3] {0.25, 0.75, 0.75};
  double point8[3] {0.75, 0.75, 0.75};
  
  TEST_ASSERT(hex_mesh->whichHexIsPointIn(point1) == 0);
  TEST_ASSERT(hex_mesh->whichHexIsPointIn(point2) == 1);
  TEST_ASSERT(hex_mesh->whichHexIsPointIn(point3) == 2);
  TEST_ASSERT(hex_mesh->whichHexIsPointIn(point4) == 3);
  TEST_ASSERT(hex_mesh->whichHexIsPointIn(point5) == 4);
  TEST_ASSERT(hex_mesh->whichHexIsPointIn(point6) == 5);
  TEST_ASSERT(hex_mesh->whichHexIsPointIn(point7) == 6);
  TEST_ASSERT(hex_mesh->whichHexIsPointIn(point8) == 7);
}

//---------------------------------------------------------------------------//
// test simple cases of rays not interacting with mesh and computeTrackLengths
// returning empty arrays
//---------------------------------------------------------------------------//

TEUCHOS_UNIT_TEST( StructuredHexMesh, ray_does_not_intersect_with_mesh)
{

  //ray travels parallel with two planes away from mesh
  double start_point1[3] {1.1, 1, 1};
  double end_point1[3] {3, 1, 1};
  double ray1[3] { end_point1[0] - start_point1[0],
                   end_point1[1] - start_point1[1],
                   end_point1[2] - start_point1[2] };
  
  //function relies on directions being unit vectors
  double magnitude1 = Utility::vectorMagnitude( ray1 );

  double direction1[3] { ray1[0]/magnitude1,
                         ray1[1]/magnitude1,
                         ray1[2]/magnitude1 };

  Teuchos::Array<std::pair<unsigned, double>> track1 =
    hex_mesh->computeTrackLengths( start_point1,
                                   end_point1,
                                   direction1);

  TEST_ASSERT(track1.size() == 0);

  //ray travels towards mesh but doesn't enter
  double start_point2[3] {1, 1, 2};
  double end_point2[3] {1, 1, 1.1};
  double ray2[3] { end_point2[0] - start_point2[0],
                   end_point2[1] - start_point2[1],
                   end_point2[2] - start_point2[2] };
  
  //function relies on directions being unit vectors
  double magnitude2 = Utility::vectorMagnitude( ray2 );

  double direction2[3] { ray2[0]/magnitude2,
                         ray2[1]/magnitude2,
                         ray2[2]/magnitude2 };

  Teuchos::Array<std::pair<unsigned, double>> track2 =
    hex_mesh->computeTrackLengths( start_point2,
                                   end_point2,
                                   direction2);

  TEST_ASSERT(track2.size() == 0);

  //ray interacts with multiple planar dimensions but doesn't enter mesh
  double start_point3[3] {0, 0, 3};
  double end_point3[3] {3, 3, 0};
  double ray3[3] { end_point3[0] - start_point3[0],
                   end_point3[1] - start_point3[1],
                   end_point3[2] - start_point3[2] };
  
  //function relies on directions being unit vectors
  double magnitude3 = Utility::vectorMagnitude( ray3 );

  double direction3[3] { ray3[0]/magnitude3,
                         ray3[1]/magnitude3,
                         ray3[2]/magnitude3 };

  Teuchos::Array<std::pair<unsigned, double>> track3 =
    hex_mesh->computeTrackLengths( start_point3,
                                   end_point3,
                                   direction3);

  TEST_ASSERT(track3.size() == 0);

}

//---------------------------------------------------------------------------//
// testing cases of rays interacting with mesh and returning appropriate results
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( StructuredHexMesh, interacting_with_mesh)
{

  double start_point[3], end_point[3], direction[3], vector_magnitude;
  
  //start with simple test - particle travels 0.5 cm from 0.25 outside the mesh
  //to 0.25 inside the mesh. Intention is for index to be zero and contribution
  //amount to be ~0.25
  
  start_point[0] = -0.25;
  start_point[1] = 0.25;
  start_point[2] = 0.25;
  end_point[0] = 0.25;
  end_point[1] = 0.25;
  end_point[2] = 0.25;
  vector_magnitude = Utility::vectorMagnitude( end_point[0] - start_point[0],
                                               end_point[1] - start_point[1],
                                               end_point[2] - start_point[2] );
  direction[0] = (end_point[0] - start_point[0]) / vector_magnitude;
  direction[1] = (end_point[1] - start_point[1]) / vector_magnitude;
  direction[2] = (end_point[2] - start_point[2]) / vector_magnitude;

  Teuchos::Array<std::pair<unsigned, double>> contribution_array_1 =
    hex_mesh->computeTrackLengths( start_point,
                                   end_point,
                                   direction);
  std::cout << " hex index: " << contribution_array_1[0].first << std::endl;
  TEST_ASSERT(contribution_array_1.size() == 1);
  TEST_ASSERT(contribution_array_1[0].first == 0);
  TEST_ASSERT( contribution_array_1[0].second > 0.2499 && 
               contribution_array_1[0].second < 0.2501);

}
