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
// Tests.
//---------------------------------------------------------------------------//
// test constructing the quadrature.
FRENSIE_UNIT_TEST( PQLAQuadrature, constructor )
{
  std::shared_ptr<Utility::PQLAQuadrature> PQLAQuadrature;
  
  FRENSIE_CHECK_NO_THROW(
                PQLAQuadrature.reset( new Utility::PQLAQuadrature( 3 ) ) );

  FRENSIE_CHECK_EQUAL( 3, PQLAQuadrature->getQuadratureOrder() );

}

//---------------------------------------------------------------------------//
// Test the findTriangleBin method
FRENSIE_UNIT_TEST( PQLAQuadrature, findTriangleBin )
{

  std::shared_ptr<Utility::PQLAQuadrature> PQLAQuadrature(
              new Utility::PQLAQuadrature( 3 ) );

  std::array<double, 3> direction {1, 1, 2};

  Utility::normalizeVector(direction[0],
                  direction[1],
                  direction[2]);
  FRENSIE_CHECK_EQUAL( PQLAQuadrature->findTriangleBin(direction),  3);

  direction[0] = -1;
  direction[1] = -1;
  direction[2] = -2;

  Utility::normalizeVector(direction[0],
                           direction[1],
                           direction[2]);

  FRENSIE_CHECK_EQUAL( PQLAQuadrature->findTriangleBin(direction), 3+(9*7));

  direction[0] = -1;
  direction[1] = 1;
  direction[2] = 2;

  Utility::normalizeVector(direction[0],
                           direction[1],
                           direction[2]);

  FRENSIE_CHECK_EQUAL( PQLAQuadrature->findTriangleBin(direction), 3+(9*1));

  direction[0] = 2;
  direction[1] = 1;
  direction[2] = 1;

  Utility::normalizeVector(direction[0],
                           direction[1],
                           direction[2]);

  FRENSIE_CHECK_EQUAL( PQLAQuadrature->findTriangleBin(direction), 6);

  direction[0] = 1;
  direction[1] = 1;
  direction[2] = 1;

  Utility::normalizeVector(direction[0],
                           direction[1],
                           direction[2]); 
  FRENSIE_CHECK_EQUAL( PQLAQuadrature->findTriangleBin(direction), 5);

  direction[0] = 0;
  direction[1] = 1;
  direction[2] = 0;

  FRENSIE_CHECK_EQUAL( PQLAQuadrature->findTriangleBin(direction), 0);

  direction[0] = 0;
  direction[1] = 0;
  direction[2] = 1;

  FRENSIE_CHECK_EQUAL( PQLAQuadrature->findTriangleBin(direction), 4);

  direction[0] = 1;
  direction[1] = 0;
  direction[2] = 0;

  FRENSIE_CHECK_EQUAL( PQLAQuadrature->findTriangleBin(direction), 8);

  direction[0] = 1;
  direction[1] = 2;
  direction[2] = 0;

  Utility::normalizeVector(direction[0],
                           direction[1],
                           direction[2]); 

  FRENSIE_CHECK_EQUAL( PQLAQuadrature->findTriangleBin(direction), 5);
}
//---------------------------------------------------------------------------//
// end tstPQLAQuadrature.cpp
//---------------------------------------------------------------------------//
