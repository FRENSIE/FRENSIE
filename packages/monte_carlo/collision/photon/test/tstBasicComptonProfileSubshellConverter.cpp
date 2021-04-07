//---------------------------------------------------------------------------//
//!
//! \file   tstBasicComptonProfileSubshellConverter.cpp
//! \author Alex Robinson
//! \brief  Basic Compton profile subshell converter unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_BasicComptonProfileSubshellConverter.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a converter can be constructed
FRENSIE_UNIT_TEST( BasicComptonProfileSubshellConverter, constructor )
{
  std::unique_ptr<const MonteCarlo::ComptonProfileSubshellConverter>
    converter = std::make_unique<MonteCarlo::BasicComptonProfileSubshellConverter>( std::vector<Data::SubshellType>({
                                                   Data::K_SUBSHELL,
                                                   Data::L1_SUBSHELL,
                                                   Data::L2_SUBSHELL,
                                                   Data::L3_SUBSHELL,
                                                   Data::M1_SUBSHELL,
                                                   Data::M2_SUBSHELL,
                                                   Data::M3_SUBSHELL,
                                                   Data::M4_SUBSHELL,
                                                   Data::M5_SUBSHELL,
                                                   Data::N1_SUBSHELL,
                                                   Data::N2_SUBSHELL,
                                                   Data::N3_SUBSHELL,
                                                   Data::N4_SUBSHELL,
                                                   Data::N5_SUBSHELL,
                                                   Data::N6_SUBSHELL,
                                                   Data::N7_SUBSHELL,
                                                   Data::O1_SUBSHELL,
                                                   Data::O2_SUBSHELL,
                                                   Data::O3_SUBSHELL,
                                                   Data::O4_SUBSHELL,
                                                   Data::O5_SUBSHELL,
                                                   Data::P1_SUBSHELL,
                                                   Data::P2_SUBSHELL,
                                                   Data::P3_SUBSHELL}) );
    
  FRENSIE_CHECK( converter->isSubshellValid( Data::K_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O4_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O5_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P3_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check that a subshell can be converted to an index
FRENSIE_UNIT_TEST( BasicComptonProfileSubshellConverter, convertSubshellToIndex )
{
  std::unique_ptr<const MonteCarlo::ComptonProfileSubshellConverter>
    converter = std::make_unique<MonteCarlo::BasicComptonProfileSubshellConverter>( std::vector<Data::SubshellType>({
                                                   Data::K_SUBSHELL,
                                                   Data::L1_SUBSHELL,
                                                   Data::L2_SUBSHELL,
                                                   Data::L3_SUBSHELL,
                                                   Data::M1_SUBSHELL,
                                                   Data::M2_SUBSHELL,
                                                   Data::M3_SUBSHELL,
                                                   Data::M4_SUBSHELL,
                                                   Data::M5_SUBSHELL,
                                                   Data::N1_SUBSHELL,
                                                   Data::N2_SUBSHELL,
                                                   Data::N3_SUBSHELL,
                                                   Data::N4_SUBSHELL,
                                                   Data::N5_SUBSHELL,
                                                   Data::N6_SUBSHELL,
                                                   Data::N7_SUBSHELL,
                                                   Data::O1_SUBSHELL,
                                                   Data::O2_SUBSHELL,
                                                   Data::O3_SUBSHELL,
                                                   Data::O4_SUBSHELL,
                                                   Data::O5_SUBSHELL,
                                                   Data::P1_SUBSHELL,
                                                   Data::P2_SUBSHELL,
                                                   Data::P3_SUBSHELL}) );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0 );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1 );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2 );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3 );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4 );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5 );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6 );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7 );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8 );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9 );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10 );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11 );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12 );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13 );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14 );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15 );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16 );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17 );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18 );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19 );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20 );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 21 );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 22 );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 23 );
}

//---------------------------------------------------------------------------//
// end tstBasicComptonProfileSubshellConverter.cpp
//---------------------------------------------------------------------------//
