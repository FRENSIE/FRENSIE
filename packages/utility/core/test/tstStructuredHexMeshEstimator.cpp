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
#include <math.h>

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
  x_planes.push_back(1);
  x_planes.push_back(2);
  y_planes.push_back(0);
  y_planes.push_back(1);
  y_planes.push_back(2);
  z_planes.push_back(0);
  z_planes.push_back(1);
  z_planes.push_back(2);
  z_planes.push_back(3);
  
  TEST_NOTHROW( hex_mesh.reset( new Utility::StructuredHexMesh( x_planes,
                                                                y_planes,
                                                                z_planes ) ) );

}

TEUCHOS_UNIT_TEST( StructuredHexMesh, estimator_calculation)
{
 
  double start_point_1[3] = { 0.5, 0.5, 0.0 };
  double end_point_1[3] = { 0.5, 0.5, 2.0 };

  double start_point_2[3] = { 0.5, 1.5, -1.0 };
  double end_point_2[3] = { 0.5, 1.5, 2.0 };

  double start_point_3[3] = { 1.5, 0.5, 0.0 };
  double end_point_3[3] = { 1.5, 0.5, 3.0 };

  double start_point_4[3] = { 1.5, 1.5, 0.0 };
  double end_point_4[3] = { 1.5, 1.5, 2.0 };

  double direction[3] = {0, 0, 1};

  double ray_length_1 = fabs(end_point_1[2] - start_point_1[2]);
  double ray_length_2 = fabs(end_point_2[2] - start_point_2[2]);

  double ray_length_3 = fabs(end_point_3[2] - start_point_3[2]);

  double ray_length_4 = fabs(end_point_4[2] - start_point_4[2]); 

  Teuchos::Array<std::pair<unsigned long,double>> contribution1 =
    hex_mesh->computeTrackLengths( start_point_1,
                                   end_point_1,
                                   direction,
                                   ray_length_1 );

  Teuchos::Array<std::pair<unsigned long,double>> contribution2 =
    hex_mesh->computeTrackLengths( start_point_2,
                                   end_point_2,
                                   direction,
                                   ray_length_2 );
                                   
  Teuchos::Array<std::pair<unsigned long,double>> contribution3 =
    hex_mesh->computeTrackLengths( start_point_3,
                                   end_point_3,
                                   direction,
                                   ray_length_3 );
                                  
  Teuchos::Array<std::pair<unsigned long,double>> contribution4 =
    hex_mesh->computeTrackLengths( start_point_4,
                                   end_point_4,
                                   direction,
                                   ray_length_4 );

  std::cout << std::endl;
  std::cout << "FIRST RAY CONTRIBUTIONS: " << std::endl;
  for(unsigned i = 0; i < contribution1.size(); ++i)
  {
  
    std::cout << "HEX: " << contribution1[i].first << ", CONTRIBUTION: " << contribution1[i].second << std::endl;
  
  }

  std::cout << std::endl;
  std::cout << "SECOND RAY CONTRIBUTIONS: " << std::endl;
  for(unsigned i = 0; i < contribution2.size(); ++i)
  {
  
    std::cout << "HEX: " << contribution2[i].first << ", CONTRIBUTION: " << contribution2[i].second << std::endl;
  
  }

  std::cout << std::endl;
  std::cout << "THIRD RAY CONTRIBUTIONS: " << std::endl;
  for(unsigned i = 0; i < contribution3.size(); ++i)
  {
  
    std::cout << "HEX: " << contribution3[i].first << ", CONTRIBUTION: " << contribution3[i].second << std::endl;
  
  }

  std::cout << std::endl;
  std::cout << "FOURTH RAY CONTRIBUTIONS: " << std::endl;
  for(unsigned i = 0; i < contribution4.size(); ++i)
  {
  
    std::cout << "HEX: " << contribution4[i].first << ", CONTRIBUTION: " << contribution4[i].second << std::endl;
  
  }

}
