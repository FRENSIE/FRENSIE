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
#include <iostream>
#include <utility>

// FRENSIE Includes
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_PQLAQuadrature.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "FRENSIE_config.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

unsigned quadrature_order;
unsigned number_of_triangles_per_side;

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
  // Begin edge cases
  std::array<double, 3> direction_5 {1, 1, 1};
  std::array<double, 3> direction_6 {0, 1, 0};
  std::array<double, 3> direction_7 {0, 0, 1};
  std::array<double, 3> direction_8 {1, 0, 0};
  std::array<double, 3> direction_9 {1, 2, 0};

  std::array< std::pair< std::array<double, 3>, unsigned >, 9 > direction_index_array
  { 
    std::make_pair(direction_1, 3),
    std::make_pair(direction_2, 3+(number_of_triangles_per_side*7)),
    std::make_pair(direction_3, 3+(number_of_triangles_per_side*1)),
    std::make_pair(direction_4, 6),
    // Begin edge cases
    std::make_pair(direction_5, 5),
    std::make_pair(direction_6, 0),
    std::make_pair(direction_7, 4),
    std::make_pair(direction_8, 8),
    std::make_pair(direction_9, 5)
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
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  quadrature_order = 3;
  number_of_triangles_per_side = quadrature_order*quadrature_order;
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();
//---------------------------------------------------------------------------//
// end tstPQLAQuadrature.cpp
//---------------------------------------------------------------------------//
