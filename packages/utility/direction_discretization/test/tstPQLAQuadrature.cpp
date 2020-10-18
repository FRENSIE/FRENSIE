//---------------------------------------------------------------------------//
//!
//! \file   tstPQLAQuadrature.cpp
//! \author Philip Britt
//! \brief  PQLA Quadrature class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <memory>
#include <array>
#include <utility>
#include <cmath>

// FRENSIE Includes
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_PQLAQuadrature.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "FRENSIE_config.hpp"
#include "ArchiveTestHelpers.hpp"
#include "Utility_RandomNumberGenerator.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

unsigned quadrature_order;
unsigned number_of_triangles_per_side;
double type_1_triangle_area;
double type_2_triangle_area;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// test constructing the quadrature.
FRENSIE_UNIT_TEST( PQLAQuadrature, constructor )
{
  std::shared_ptr<Utility::PQLAQuadrature> PQLAQuadrature;
  
  FRENSIE_CHECK_NO_THROW(
                PQLAQuadrature.reset( new Utility::PQLAQuadrature( quadrature_order ) ) );

  FRENSIE_CHECK_EQUAL( quadrature_order, PQLAQuadrature->getQuadratureOrder() );

}

//---------------------------------------------------------------------------//
// Test the findTriangleBin method
FRENSIE_UNIT_TEST( PQLAQuadrature, findTriangleBin )
{

  std::shared_ptr<Utility::PQLAQuadrature> PQLAQuadrature(
              new Utility::PQLAQuadrature( quadrature_order ) );

  std::array<double, 3> direction_1 {1, 1, 2};
  std::array<double, 3> direction_2 {-1, -1, -2};
  std::array<double, 3> direction_3 {-1, 1, 2};
  std::array<double, 3> direction_4 {2, 1, 1};
  std::array<double, 3> direction_5 {-0.670743813270348,  -0.494811928758853,  -0.552506915900151};
  // Begin edge cases
  std::array<double, 3> direction_6 {1, 1, 1};
  std::array<double, 3> direction_7 {0, 1, 0};
  std::array<double, 3> direction_8 {0, 0, 1};
  std::array<double, 3> direction_9 {1, 0, 0};
  std::array<double, 3> direction_10 {1, 2, 0};
  std::array<double, 3> direction_11 {2, 1, 0};
  std::array<double, 3> direction_12 {2, 0, 1};
  std::array<double, 3> direction_13 {1, 0, 2};
  std::array<double, 3> direction_14 {0, 2, 1};
  std::array<double, 3> direction_15 {0, 1, 2};


  std::array< std::pair< std::array<double, 3>, unsigned >, 15 > direction_index_array
  { 
    std::make_pair(direction_1, 3),
    std::make_pair(direction_2, 3+(number_of_triangles_per_side*7)),
    std::make_pair(direction_3, 3+(number_of_triangles_per_side*1)),
    std::make_pair(direction_4, 1),
    std::make_pair(direction_5, 64),
    // Begin edge cases
    std::make_pair(direction_6, 5),
    std::make_pair(direction_7, 8),
    std::make_pair(direction_8, 4),
    std::make_pair(direction_9, 0),
    std::make_pair(direction_10, 8),
    std::make_pair(direction_11, 5),
    std::make_pair(direction_12, 0),
    std::make_pair(direction_13, 2),
    std::make_pair(direction_14, 8),
    std::make_pair(direction_15, 7)
  };

  for(auto it = direction_index_array.begin(); it != direction_index_array.end(); ++it)
  {
    std::array<double, 3> normalize_direction = it->first;
    Utility::normalizeVector(normalize_direction[0],
                             normalize_direction[1],
                             normalize_direction[2]);
    FRENSIE_CHECK_EQUAL( PQLAQuadrature->findTriangleBin(normalize_direction), it->second);
  }
 
}

//---------------------------------------------------------------------------//
// Test the getQuadratureOrder method
FRENSIE_UNIT_TEST( PQLAQuadrature, getQuadratureOrder )
{
  std::shared_ptr<Utility::PQLAQuadrature> PQLAQuadrature(
              new Utility::PQLAQuadrature( quadrature_order ) );

  FRENSIE_CHECK_EQUAL(PQLAQuadrature->getQuadratureOrder(), quadrature_order);

}

//---------------------------------------------------------------------------//
// Test the getNumberOfTriangles method
FRENSIE_UNIT_TEST( PQLAQuadrature, getNumberOfTriangles )
{
  std::shared_ptr<Utility::PQLAQuadrature> PQLAQuadrature(
              new Utility::PQLAQuadrature( quadrature_order ) );

  FRENSIE_CHECK_EQUAL(PQLAQuadrature->getNumberOfTriangles(), 8*pow(quadrature_order,2));

}

//---------------------------------------------------------------------------//
// Test the getTriangleArea method
FRENSIE_UNIT_TEST(PQLAQuadrature, getTriangleArea)
{
  std::shared_ptr<Utility::PQLAQuadrature> PQLAQuadrature(
              new Utility::PQLAQuadrature( quadrature_order ) );

  std::vector<double> positive_domain_triangle_area {type_1_triangle_area,
                                                      type_2_triangle_area,
                                                      type_2_triangle_area,
                                                      type_2_triangle_area,
                                                      type_1_triangle_area,
                                                      type_2_triangle_area,
                                                      type_2_triangle_area,
                                                      type_2_triangle_area,
                                                      type_1_triangle_area};

  size_t triangles_per_octant = PQLAQuadrature->getQuadratureOrder()*PQLAQuadrature->getQuadratureOrder();
  // Iterate over octants of 3-d cartesian space
  for(size_t octant = 0; octant < 8; ++octant)
  {
    // Iterate over triangles in that octant
    for(size_t triangle = 0; triangle < triangles_per_octant; ++triangle)
    {
      size_t local_triangle_index = octant*triangles_per_octant + triangle;
      FRENSIE_CHECK_FLOATING_EQUALITY(PQLAQuadrature->getTriangleArea(local_triangle_index), positive_domain_triangle_area[triangle], 1e-14);
    }
  }
}

//---------------------------------------------------------------------------//
// Test the sampleIsotropicallyFromTriangle method
FRENSIE_UNIT_TEST(PQLAQuadrature, sampleIsotropicallyFromTriangle)
{
  std::shared_ptr<Utility::PQLAQuadrature> PQLAQuadrature(
              new Utility::PQLAQuadrature( quadrature_order ) );

  std::vector<double> fake_stream = {0.32, 0.45, 0.83, 0.92};
  Utility::RandomNumberGenerator::setFakeStream(fake_stream);

  std::array<size_t, 2> desired_triangles_to_sample_from = {5, 64};
  double precalculated_results_array[2][3]= {{0.730188313787608, 0.669484176934741, 0.136440328503061}, {-0.670743813270348,  -0.494811928758853,  -0.552506915900151}};

  for(int test_index = 0; test_index < 2; ++test_index)
  {
    std::array<double, 3> direction_vector;
    PQLAQuadrature->sampleIsotropicallyFromTriangle(direction_vector, desired_triangles_to_sample_from[test_index]);
    for(int vert = 0; vert < 3; ++vert)
    {
      FRENSIE_CHECK_FLOATING_EQUALITY(direction_vector[vert], precalculated_results_array[test_index][vert], 1e-14);
    }
  }

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Integration test for sampleIsotrpicallyFromTriangle method and findTriangleBin method
FRENSIE_UNIT_TEST(PQLAQuadrature, sampleIsotropicallyFromTriangle_and_findTriangleBin)
{
  std::shared_ptr<Utility::PQLAQuadrature> PQLAQuadrature(
              new Utility::PQLAQuadrature( quadrature_order ) );
  for(size_t tri = 0; tri < 8*quadrature_order*quadrature_order; ++tri)
  {
    std::array<double, 3> direction_vector;
    PQLAQuadrature->sampleIsotropicallyFromTriangle(direction_vector, tri);

    FRENSIE_CHECK_EQUAL(PQLAQuadrature->findTriangleBin(direction_vector), tri);
  }
}

//---------------------------------------------------------------------------//
// Check that an estimator can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( PQLAQuadrature,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  // Define local quadrature order (smaller to make the discretization simpler)
  unsigned local_quad_order = 2; 

  std::string archive_base_name( "test_PQLA_Quadrature" );
  std::ostringstream archive_ostream;
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<Utility::PQLAQuadrature> direction_discretization_archive_test;
    { 
      direction_discretization_archive_test = std::make_shared<Utility::PQLAQuadrature>(local_quad_order);
    }

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( direction_discretization_archive_test ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<Utility::PQLAQuadrature> direction_discretization_archive_test;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( direction_discretization_archive_test ) );

  iarchive.reset();
  {
    const std::vector<Utility::SphericalTriangle>& underlying_triangle_discretization = direction_discretization_archive_test->getSphericalTriangleVector();
  
    double half_angle_coordinate = 1/sqrt(2);

    // Positive octant triangles (1/sqrt(2) used repeatedly due to intermediate vertices being at angle of pi/4 on their respective axis' plane)
    std::vector<std::array<double, 3>> triangle_1 {{1, 0, 0}, 
                                                   {half_angle_coordinate, half_angle_coordinate, 0},
                                                   {half_angle_coordinate, 0, half_angle_coordinate}};
    std::vector<std::array<double, 3>> triangle_2 {{half_angle_coordinate, 0, half_angle_coordinate},
                                                   {half_angle_coordinate, half_angle_coordinate, 0},
                                                   {0, half_angle_coordinate, half_angle_coordinate}};
    std::vector<std::array<double, 3>> triangle_3 {{half_angle_coordinate, 0, half_angle_coordinate},
                                                   {0, half_angle_coordinate, half_angle_coordinate},
                                                   {0, 0, 1}};
    std::vector<std::array<double, 3>> triangle_4 {{half_angle_coordinate, half_angle_coordinate, 0},
                                                   {0, 1, 0},
                                                   {0, half_angle_coordinate, half_angle_coordinate}};
    std::vector<std::vector<std::array<double, 3>>> triangle_vector;
    triangle_vector.push_back(triangle_1);
    triangle_vector.push_back(triangle_2);
    triangle_vector.push_back(triangle_3);
    triangle_vector.push_back(triangle_4);

    for(int octant = 0; octant < 8; ++octant)
    {
      // Leaving this the way it is so it can be tested using a separate method
      int i = octant;
      int x_multiplier = 1;
      int y_multiplier = 1;
      int z_multiplier = 1;
      if(i >= 4)
      {
        i -= 4;
        z_multiplier = -1;
      }
      if(i >= 2)
      {
        i -= 2;
        y_multiplier = -1;
      }
      if(i >= 1)
      {
        i -= 1;
        x_multiplier = -1;
      }

      for(int local_triangle = 0; local_triangle < local_quad_order*local_quad_order; ++local_triangle)
      {
        int total_index = local_triangle + octant * local_quad_order*local_quad_order;
        Utility::SphericalTriangle triangle = underlying_triangle_discretization[total_index];
        for(int vertex = 0; vertex < 3; ++vertex)
        {
          FRENSIE_CHECK_FLOATING_EQUALITY(std::get<0>(triangle.triangle_parameter_vector[vertex])[0], x_multiplier*triangle_vector[local_triangle][vertex][0], 1e-15 );
          FRENSIE_CHECK_FLOATING_EQUALITY(std::get<0>(triangle.triangle_parameter_vector[vertex])[1], y_multiplier*triangle_vector[local_triangle][vertex][1], 1e-15 );
          FRENSIE_CHECK_FLOATING_EQUALITY(std::get<0>(triangle.triangle_parameter_vector[vertex])[2], z_multiplier*triangle_vector[local_triangle][vertex][2], 1e-15 );
        }
      }
    }
  }

}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  quadrature_order = 3;
  number_of_triangles_per_side = quadrature_order*quadrature_order;

  // Set type 1 triangle area (hand-calculated values based on knowledge of triangles)
  type_1_triangle_area = 0.111341014340963;

  // Set type 2 triangle area (hand-calculated values based on knowledge of triangles)
  type_2_triangle_area = 0.206128880628667;

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();
//---------------------------------------------------------------------------//
// end tstPQLAQuadrature.cpp
//---------------------------------------------------------------------------//
