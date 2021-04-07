//---------------------------------------------------------------------------//
//!
//! \file   tstSubshellTypeHelpers.cpp
//! \author Alex Robinson
//! \brief  Subshell type helper function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// FRENSIE Includes
#include "Data_SubshellType.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an ENDF designator can be converted to a subshell type
FRENSIE_UNIT_TEST( SubshellType, convertENDFDesignatorToSubshellEnum )
{
  Data::SubshellType subshell = Data::convertENDFDesignatorToSubshellEnum( 0 );

  FRENSIE_CHECK_EQUAL( subshell, Data::INVALID_SUBSHELL );
  
  subshell = Data::convertENDFDesignatorToSubshellEnum( 1 );

  FRENSIE_CHECK_EQUAL( subshell, Data::K_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 2 );

  FRENSIE_CHECK_EQUAL( subshell, Data::L1_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 3 );

  FRENSIE_CHECK_EQUAL( subshell, Data::L2_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 4 );

  FRENSIE_CHECK_EQUAL( subshell, Data::L3_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 5 );

  FRENSIE_CHECK_EQUAL( subshell, Data::M1_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 6 );

  FRENSIE_CHECK_EQUAL( subshell, Data::M2_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 7 );

  FRENSIE_CHECK_EQUAL( subshell, Data::M3_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 8 );

  FRENSIE_CHECK_EQUAL( subshell, Data::M4_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 9 );

  FRENSIE_CHECK_EQUAL( subshell, Data::M5_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 10 );

  FRENSIE_CHECK_EQUAL( subshell, Data::N1_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 11 );

  FRENSIE_CHECK_EQUAL( subshell, Data::N2_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 12 );

  FRENSIE_CHECK_EQUAL( subshell, Data::N3_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 13 );

  FRENSIE_CHECK_EQUAL( subshell, Data::N4_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 14 );

  FRENSIE_CHECK_EQUAL( subshell, Data::N5_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 15 );

  FRENSIE_CHECK_EQUAL( subshell, Data::N6_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 16 );

  FRENSIE_CHECK_EQUAL( subshell, Data::N7_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 17 );

  FRENSIE_CHECK_EQUAL( subshell, Data::O1_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 18 );

  FRENSIE_CHECK_EQUAL( subshell, Data::O2_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 19 );

  FRENSIE_CHECK_EQUAL( subshell, Data::O3_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 20 );

  FRENSIE_CHECK_EQUAL( subshell, Data::O4_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 21 );

  FRENSIE_CHECK_EQUAL( subshell, Data::O5_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 22 );

  FRENSIE_CHECK_EQUAL( subshell, Data::O6_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 23 );

  FRENSIE_CHECK_EQUAL( subshell, Data::O7_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 24 );

  FRENSIE_CHECK_EQUAL( subshell, Data::O8_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 25 );

  FRENSIE_CHECK_EQUAL( subshell, Data::O9_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 26 );

  FRENSIE_CHECK_EQUAL( subshell, Data::P1_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 27 );

  FRENSIE_CHECK_EQUAL( subshell, Data::P2_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 28 );

  FRENSIE_CHECK_EQUAL( subshell, Data::P3_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 29 );

  FRENSIE_CHECK_EQUAL( subshell, Data::P4_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 30 );

  FRENSIE_CHECK_EQUAL( subshell, Data::P5_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 31 );

  FRENSIE_CHECK_EQUAL( subshell, Data::P6_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 32 );

  FRENSIE_CHECK_EQUAL( subshell, Data::P7_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 33 );

  FRENSIE_CHECK_EQUAL( subshell, Data::P8_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 34 );

  FRENSIE_CHECK_EQUAL( subshell, Data::P9_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 35 );

  FRENSIE_CHECK_EQUAL( subshell, Data::P10_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 36 );

  FRENSIE_CHECK_EQUAL( subshell, Data::P11_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 37 );

  FRENSIE_CHECK_EQUAL( subshell, Data::Q1_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 38 );

  FRENSIE_CHECK_EQUAL( subshell, Data::Q2_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 39 );

  FRENSIE_CHECK_EQUAL( subshell, Data::Q3_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 40 );

  FRENSIE_CHECK_EQUAL( subshell, Data::INVALID_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that a SubshellType enum can be converted to an integer
FRENSIE_UNIT_TEST( SubshellType, endf_integer_conversion )
{
  FRENSIE_CHECK_EQUAL( Data::K_SUBSHELL, 1 );
  FRENSIE_CHECK_EQUAL( Data::L1_SUBSHELL, 2 );
  FRENSIE_CHECK_EQUAL( Data::L2_SUBSHELL, 3 );
  FRENSIE_CHECK_EQUAL( Data::L3_SUBSHELL, 4 );
  FRENSIE_CHECK_EQUAL( Data::M1_SUBSHELL, 5 );
  FRENSIE_CHECK_EQUAL( Data::M2_SUBSHELL, 6 );
  FRENSIE_CHECK_EQUAL( Data::M3_SUBSHELL, 7 );
  FRENSIE_CHECK_EQUAL( Data::M4_SUBSHELL, 8 );
  FRENSIE_CHECK_EQUAL( Data::M5_SUBSHELL, 9 );
  FRENSIE_CHECK_EQUAL( Data::N1_SUBSHELL, 10 );
  FRENSIE_CHECK_EQUAL( Data::N2_SUBSHELL, 11 );
  FRENSIE_CHECK_EQUAL( Data::N3_SUBSHELL, 12 );
  FRENSIE_CHECK_EQUAL( Data::N4_SUBSHELL, 13 );
  FRENSIE_CHECK_EQUAL( Data::N5_SUBSHELL, 14 );
  FRENSIE_CHECK_EQUAL( Data::N6_SUBSHELL, 15 );
  FRENSIE_CHECK_EQUAL( Data::N7_SUBSHELL, 16 );
  FRENSIE_CHECK_EQUAL( Data::O1_SUBSHELL, 17 );
  FRENSIE_CHECK_EQUAL( Data::O2_SUBSHELL, 18 );
  FRENSIE_CHECK_EQUAL( Data::O3_SUBSHELL, 19 );
  FRENSIE_CHECK_EQUAL( Data::O4_SUBSHELL, 20 );
  FRENSIE_CHECK_EQUAL( Data::O5_SUBSHELL, 21 );
  FRENSIE_CHECK_EQUAL( Data::O6_SUBSHELL, 22 );
  FRENSIE_CHECK_EQUAL( Data::O7_SUBSHELL, 23 );
  FRENSIE_CHECK_EQUAL( Data::O8_SUBSHELL, 24 );
  FRENSIE_CHECK_EQUAL( Data::O9_SUBSHELL, 25 );
  FRENSIE_CHECK_EQUAL( Data::P1_SUBSHELL, 26 );
  FRENSIE_CHECK_EQUAL( Data::P2_SUBSHELL, 27 );
  FRENSIE_CHECK_EQUAL( Data::P3_SUBSHELL, 28 );
  FRENSIE_CHECK_EQUAL( Data::P4_SUBSHELL, 29 );
  FRENSIE_CHECK_EQUAL( Data::P5_SUBSHELL, 30 );
  FRENSIE_CHECK_EQUAL( Data::P6_SUBSHELL, 31 );
  FRENSIE_CHECK_EQUAL( Data::P7_SUBSHELL, 32 );
  FRENSIE_CHECK_EQUAL( Data::P8_SUBSHELL, 33 );
  FRENSIE_CHECK_EQUAL( Data::P9_SUBSHELL, 34 );
  FRENSIE_CHECK_EQUAL( Data::P10_SUBSHELL, 35 );
  FRENSIE_CHECK_EQUAL( Data::P11_SUBSHELL, 36 );
  FRENSIE_CHECK_EQUAL( Data::Q1_SUBSHELL, 37 );
  FRENSIE_CHECK_EQUAL( Data::Q2_SUBSHELL, 38 );
  FRENSIE_CHECK_EQUAL( Data::Q3_SUBSHELL, 39 );
}

//---------------------------------------------------------------------------//
// Check that an EADL designator can be converted to a subshell type
FRENSIE_UNIT_TEST( SubshellType, convertEADLDesignatorToSubshellEnum )
{
  Data::SubshellType subshell = Data::convertEADLDesignatorToSubshellEnum( 0 );

  FRENSIE_CHECK_EQUAL( subshell, Data::INVALID_SUBSHELL );
  
  subshell = Data::convertEADLDesignatorToSubshellEnum( 1 );

  FRENSIE_CHECK_EQUAL( subshell, Data::K_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 2 );

  FRENSIE_CHECK_EQUAL( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 3 );

  FRENSIE_CHECK_EQUAL( subshell, Data::L1_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 4 );

  FRENSIE_CHECK_EQUAL( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 5 );

  FRENSIE_CHECK_EQUAL( subshell, Data::L2_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 6 );

  FRENSIE_CHECK_EQUAL( subshell, Data::L3_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 7 );

  FRENSIE_CHECK_EQUAL( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 8 );

  FRENSIE_CHECK_EQUAL( subshell, Data::M1_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 9 );

  FRENSIE_CHECK_EQUAL( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 10 );

  FRENSIE_CHECK_EQUAL( subshell, Data::M2_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 11 );

  FRENSIE_CHECK_EQUAL( subshell, Data::M3_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 12 );

  FRENSIE_CHECK_EQUAL( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 13 );

  FRENSIE_CHECK_EQUAL( subshell, Data::M4_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 14 );

  FRENSIE_CHECK_EQUAL( subshell, Data::M5_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 15 );

  FRENSIE_CHECK_EQUAL( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 16 );

  FRENSIE_CHECK_EQUAL( subshell, Data::N1_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 17 );

  FRENSIE_CHECK_EQUAL( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 18 );

  FRENSIE_CHECK_EQUAL( subshell, Data::N2_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 19 );

  FRENSIE_CHECK_EQUAL( subshell, Data::N3_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 20 );

  FRENSIE_CHECK_EQUAL( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 21 );

  FRENSIE_CHECK_EQUAL( subshell, Data::N4_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 22 );

  FRENSIE_CHECK_EQUAL( subshell, Data::N5_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 23 );

  FRENSIE_CHECK_EQUAL( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 24 );

  FRENSIE_CHECK_EQUAL( subshell, Data::N6_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 25 );

  FRENSIE_CHECK_EQUAL( subshell, Data::N7_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 26 );

  FRENSIE_CHECK_EQUAL( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 27 );

  FRENSIE_CHECK_EQUAL( subshell, Data::O1_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 28 );

  FRENSIE_CHECK_EQUAL( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 29 );

  FRENSIE_CHECK_EQUAL( subshell, Data::O2_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 30 );

  FRENSIE_CHECK_EQUAL( subshell, Data::O3_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 31 );

  FRENSIE_CHECK_EQUAL( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 32 );

  FRENSIE_CHECK_EQUAL( subshell, Data::O4_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 33 );

  FRENSIE_CHECK_EQUAL( subshell, Data::O5_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 34 );

  FRENSIE_CHECK_EQUAL( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 35 );

  FRENSIE_CHECK_EQUAL( subshell, Data::O6_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 36 );

  FRENSIE_CHECK_EQUAL( subshell, Data::O7_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 37 );

  FRENSIE_CHECK_EQUAL( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 38 );

  FRENSIE_CHECK_EQUAL( subshell, Data::O8_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 39 );

  FRENSIE_CHECK_EQUAL( subshell, Data::O9_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 40 );

  FRENSIE_CHECK_EQUAL( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 41 );

  FRENSIE_CHECK_EQUAL( subshell, Data::P1_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 42 );

  FRENSIE_CHECK_EQUAL( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 43 );

  FRENSIE_CHECK_EQUAL( subshell, Data::P2_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 44 );

  FRENSIE_CHECK_EQUAL( subshell, Data::P3_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 45 );

  FRENSIE_CHECK_EQUAL( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 46 );

  FRENSIE_CHECK_EQUAL( subshell, Data::P4_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 47 );

  FRENSIE_CHECK_EQUAL( subshell, Data::P5_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 48 );

  FRENSIE_CHECK_EQUAL( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 49 );

  FRENSIE_CHECK_EQUAL( subshell, Data::P6_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 50 );

  FRENSIE_CHECK_EQUAL( subshell, Data::P7_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 51 );

  FRENSIE_CHECK_EQUAL( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 52 );

  FRENSIE_CHECK_EQUAL( subshell, Data::P8_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 53 );

  FRENSIE_CHECK_EQUAL( subshell, Data::P9_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 54 );

  FRENSIE_CHECK_EQUAL( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 55 );

  FRENSIE_CHECK_EQUAL( subshell, Data::P10_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 56 );

  FRENSIE_CHECK_EQUAL( subshell, Data::P11_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 57 );

  FRENSIE_CHECK_EQUAL( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 58 );

  FRENSIE_CHECK_EQUAL( subshell, Data::Q1_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 59 );

  FRENSIE_CHECK_EQUAL( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 60 );

  FRENSIE_CHECK_EQUAL( subshell, Data::Q2_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 61 );

  FRENSIE_CHECK_EQUAL( subshell, Data::Q3_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 62 );

  FRENSIE_CHECK_EQUAL( subshell, Data::INVALID_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that an EADL designator can be converted to an ENDF designator
FRENSIE_UNIT_TEST( SubshellType, convertEADLDesignatorToENDFDesignator )
{
  FRENSIE_CHECK_THROW( Data::convertEADLDesignatorToENDFDesignator( 0 ),
              std::logic_error );

  unsigned endf_designator = Data::convertEADLDesignatorToENDFDesignator( 1 );

  FRENSIE_CHECK_EQUAL( endf_designator, 1 );

  FRENSIE_CHECK_THROW( Data::convertEADLDesignatorToENDFDesignator( 2 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 3 );

  FRENSIE_CHECK_EQUAL( endf_designator, 2 );

  FRENSIE_CHECK_THROW( Data::convertEADLDesignatorToENDFDesignator( 4 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 5 );

  FRENSIE_CHECK_EQUAL( endf_designator, 3 );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 6 );

  FRENSIE_CHECK_EQUAL( endf_designator, 4 );

  FRENSIE_CHECK_THROW( Data::convertEADLDesignatorToENDFDesignator( 7 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 8 );

  FRENSIE_CHECK_EQUAL( endf_designator, 5 );

  FRENSIE_CHECK_THROW( Data::convertEADLDesignatorToENDFDesignator( 9 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 10 );

  FRENSIE_CHECK_EQUAL( endf_designator, 6 );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 11 );

  FRENSIE_CHECK_EQUAL( endf_designator, 7 );

  FRENSIE_CHECK_THROW( Data::convertEADLDesignatorToENDFDesignator( 12 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 13 );

  FRENSIE_CHECK_EQUAL( endf_designator, 8 );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 14 );

  FRENSIE_CHECK_EQUAL( endf_designator, 9 );

  FRENSIE_CHECK_THROW( Data::convertEADLDesignatorToENDFDesignator( 15 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 16 );

  FRENSIE_CHECK_EQUAL( endf_designator, 10 );

  FRENSIE_CHECK_THROW( Data::convertEADLDesignatorToENDFDesignator( 17 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 18 );

  FRENSIE_CHECK_EQUAL( endf_designator, 11 );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 19 );

  FRENSIE_CHECK_EQUAL( endf_designator, 12 );

  FRENSIE_CHECK_THROW( Data::convertEADLDesignatorToENDFDesignator( 20 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 21 );

  FRENSIE_CHECK_EQUAL( endf_designator, 13 );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 22 );

  FRENSIE_CHECK_EQUAL( endf_designator, 14 );

  FRENSIE_CHECK_THROW( Data::convertEADLDesignatorToENDFDesignator( 23 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 24 );

  FRENSIE_CHECK_EQUAL( endf_designator, 15 );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 25 );

  FRENSIE_CHECK_EQUAL( endf_designator, 16 );

  FRENSIE_CHECK_THROW( Data::convertEADLDesignatorToENDFDesignator( 26 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 27 );

  FRENSIE_CHECK_EQUAL( endf_designator, 17 );

  FRENSIE_CHECK_THROW( Data::convertEADLDesignatorToENDFDesignator( 28 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 29 );

  FRENSIE_CHECK_EQUAL( endf_designator, 18 );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 30 );

  FRENSIE_CHECK_EQUAL( endf_designator, 19 );

  FRENSIE_CHECK_THROW( Data::convertEADLDesignatorToENDFDesignator( 31 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 32 );

  FRENSIE_CHECK_EQUAL( endf_designator, 20 );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 33 );

  FRENSIE_CHECK_EQUAL( endf_designator, 21 );

  FRENSIE_CHECK_THROW( Data::convertEADLDesignatorToENDFDesignator( 34 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 35 );

  FRENSIE_CHECK_EQUAL( endf_designator, 22 );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 36 );

  FRENSIE_CHECK_EQUAL( endf_designator, 23 );

  FRENSIE_CHECK_THROW( Data::convertEADLDesignatorToENDFDesignator( 37 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 38 );

  FRENSIE_CHECK_EQUAL( endf_designator, 24 );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 39 );

  FRENSIE_CHECK_EQUAL( endf_designator, 25 );

  FRENSIE_CHECK_THROW( Data::convertEADLDesignatorToENDFDesignator( 40 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 41 );

  FRENSIE_CHECK_EQUAL( endf_designator, 26 );

  FRENSIE_CHECK_THROW( Data::convertEADLDesignatorToENDFDesignator( 42 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 43 );

  FRENSIE_CHECK_EQUAL( endf_designator, 27 );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 44 );

  FRENSIE_CHECK_EQUAL( endf_designator, 28 );

  FRENSIE_CHECK_THROW( Data::convertEADLDesignatorToENDFDesignator( 45 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 46 );

  FRENSIE_CHECK_EQUAL( endf_designator, 29 );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 47 );

  FRENSIE_CHECK_EQUAL( endf_designator, 30 );

  FRENSIE_CHECK_THROW( Data::convertEADLDesignatorToENDFDesignator( 48 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 49 );

  FRENSIE_CHECK_EQUAL( endf_designator, 31 );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 50 );

  FRENSIE_CHECK_EQUAL( endf_designator, 32 );

  FRENSIE_CHECK_THROW( Data::convertEADLDesignatorToENDFDesignator( 51 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 52 );

  FRENSIE_CHECK_EQUAL( endf_designator, 33 );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 53 );

  FRENSIE_CHECK_EQUAL( endf_designator, 34 );

  FRENSIE_CHECK_THROW( Data::convertEADLDesignatorToENDFDesignator( 54 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 55 );

  FRENSIE_CHECK_EQUAL( endf_designator, 35 );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 56 );

  FRENSIE_CHECK_EQUAL( endf_designator, 36 );

  FRENSIE_CHECK_THROW( Data::convertEADLDesignatorToENDFDesignator( 57 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 58 );

  FRENSIE_CHECK_EQUAL( endf_designator, 37 );

  FRENSIE_CHECK_THROW( Data::convertEADLDesignatorToENDFDesignator( 59 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 60 );

  FRENSIE_CHECK_EQUAL( endf_designator, 38 );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 61 );

  FRENSIE_CHECK_EQUAL( endf_designator, 39 );

  FRENSIE_CHECK_THROW( Data::convertEADLDesignatorToENDFDesignator( 62 ),
                       std::logic_error );
}

//---------------------------------------------------------------------------//
// Check that a subshell type can be converted to a string
FRENSIE_UNIT_TEST( SubshellType, toString )
{
  std::string subshell_name = Utility::toString( Data::K_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "K" );

  subshell_name = Utility::toString( Data::L1_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "L1" );

  subshell_name = Utility::toString( Data::L2_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "L2" );

  subshell_name = Utility::toString( Data::L3_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "L3" );

  subshell_name = Utility::toString( Data::M1_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "M1" );

  subshell_name = Utility::toString( Data::M2_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "M2" );

  subshell_name = Utility::toString( Data::M3_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "M3" );

  subshell_name = Utility::toString( Data::M4_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "M4" );

  subshell_name = Utility::toString( Data::M5_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "M5" );

  subshell_name = Utility::toString( Data::N1_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "N1" );

  subshell_name = Utility::toString( Data::N2_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "N2" );

  subshell_name = Utility::toString( Data::N3_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "N3" );

  subshell_name = Utility::toString( Data::N4_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "N4" );

  subshell_name = Utility::toString( Data::N5_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "N5" );

  subshell_name = Utility::toString( Data::N6_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "N6" );

  subshell_name = Utility::toString( Data::N7_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "N7" );

  subshell_name = Utility::toString( Data::O1_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "O1" );

  subshell_name = Utility::toString( Data::O2_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "O2" );

  subshell_name = Utility::toString( Data::O3_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "O3" );

  subshell_name = Utility::toString( Data::O4_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "O4" );

  subshell_name = Utility::toString( Data::O5_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "O5" );

  subshell_name = Utility::toString( Data::O6_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "O6" );

  subshell_name = Utility::toString( Data::O7_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "O7" );

  subshell_name = Utility::toString( Data::O8_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "O8" );

  subshell_name = Utility::toString( Data::O9_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "O9" );

  subshell_name = Utility::toString( Data::P1_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "P1" );

  subshell_name = Utility::toString( Data::P2_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "P2" );

  subshell_name = Utility::toString( Data::P3_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "P3" );

  subshell_name = Utility::toString( Data::P4_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "P4" );

  subshell_name = Utility::toString( Data::P5_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "P5" );

  subshell_name = Utility::toString( Data::P6_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "P6" );

  subshell_name = Utility::toString( Data::P7_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "P7" );

  subshell_name = Utility::toString( Data::P8_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "P8" );

  subshell_name = Utility::toString( Data::P9_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "P9" );

  subshell_name = Utility::toString( Data::P10_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "P10" );

  subshell_name = Utility::toString( Data::P11_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "P11" );

  subshell_name = Utility::toString( Data::Q1_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "Q1" );

  subshell_name = Utility::toString( Data::Q2_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "Q2" );

  subshell_name = Utility::toString( Data::Q3_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "Q3" );

  subshell_name = Utility::toString( Data::UNKNOWN_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "Unknown" );

  subshell_name = Utility::toString( Data::INVALID_SUBSHELL );

  FRENSIE_CHECK_EQUAL( subshell_name, "Invalid" );
}

//---------------------------------------------------------------------------//
// Check that a subshell type can be placed in an output stream
FRENSIE_UNIT_TEST( SubshellType, stream_operator )
{
  std::ostringstream oss;
  oss << Data::K_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "K" );

  oss.str( "" );
  oss.clear();

  oss << Data::L1_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "L1" );

  oss.str( "" );
  oss.clear();

  oss << Data::L2_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "L2" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::L3_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "L3" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::M1_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "M1" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::M2_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "M2" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::M3_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "M3" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::M4_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "M4" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::M5_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "M5" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::N1_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "N1" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::N2_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "N2" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::N3_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "N3" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::N4_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "N4" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::N5_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "N5" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::N6_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "N6" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::N7_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "N7" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::O1_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "O1" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::O2_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "O2" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::O3_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "O3" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::O4_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "O4" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::O5_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "O5" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::O6_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "O6" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::O7_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "O7" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::O8_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "O8" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::O9_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "O9" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::P1_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "P1" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::P2_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "P2" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::P3_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "P3" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::P4_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "P4" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::P5_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "P5" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::P6_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "P6" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::P7_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "P7" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::P8_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "P8" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::P9_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "P9" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::P10_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "P10" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::P11_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "P11" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::Q1_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "Q1" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::Q2_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "Q2" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::Q3_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "Q3" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::UNKNOWN_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "Unknown" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::INVALID_SUBSHELL;

  FRENSIE_CHECK_EQUAL( oss.str(), "Invalid" );
}

//---------------------------------------------------------------------------//
// end tstSubshellTypeHelpers.cpp
//---------------------------------------------------------------------------//
