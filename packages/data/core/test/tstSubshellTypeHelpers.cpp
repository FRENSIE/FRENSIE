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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Data_SubshellType.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an ENDF designator can be converted to a subshell type
TEUCHOS_UNIT_TEST( SubshellType, convertENDFDesignatorToSubshellEnum )
{
  Data::SubshellType subshell = Data::convertENDFDesignatorToSubshellEnum( 0 );

  TEST_EQUALITY_CONST( subshell, Data::INVALID_SUBSHELL );
  
  subshell = Data::convertENDFDesignatorToSubshellEnum( 1 );

  TEST_EQUALITY_CONST( subshell, Data::K_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 2 );

  TEST_EQUALITY_CONST( subshell, Data::L1_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 3 );

  TEST_EQUALITY_CONST( subshell, Data::L2_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 4 );

  TEST_EQUALITY_CONST( subshell, Data::L3_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 5 );

  TEST_EQUALITY_CONST( subshell, Data::M1_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 6 );

  TEST_EQUALITY_CONST( subshell, Data::M2_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 7 );

  TEST_EQUALITY_CONST( subshell, Data::M3_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 8 );

  TEST_EQUALITY_CONST( subshell, Data::M4_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 9 );

  TEST_EQUALITY_CONST( subshell, Data::M5_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 10 );

  TEST_EQUALITY_CONST( subshell, Data::N1_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 11 );

  TEST_EQUALITY_CONST( subshell, Data::N2_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 12 );

  TEST_EQUALITY_CONST( subshell, Data::N3_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 13 );

  TEST_EQUALITY_CONST( subshell, Data::N4_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 14 );

  TEST_EQUALITY_CONST( subshell, Data::N5_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 15 );

  TEST_EQUALITY_CONST( subshell, Data::N6_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 16 );

  TEST_EQUALITY_CONST( subshell, Data::N7_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 17 );

  TEST_EQUALITY_CONST( subshell, Data::O1_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 18 );

  TEST_EQUALITY_CONST( subshell, Data::O2_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 19 );

  TEST_EQUALITY_CONST( subshell, Data::O3_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 20 );

  TEST_EQUALITY_CONST( subshell, Data::O4_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 21 );

  TEST_EQUALITY_CONST( subshell, Data::O5_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 22 );

  TEST_EQUALITY_CONST( subshell, Data::O6_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 23 );

  TEST_EQUALITY_CONST( subshell, Data::O7_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 24 );

  TEST_EQUALITY_CONST( subshell, Data::O8_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 25 );

  TEST_EQUALITY_CONST( subshell, Data::O9_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 26 );

  TEST_EQUALITY_CONST( subshell, Data::P1_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 27 );

  TEST_EQUALITY_CONST( subshell, Data::P2_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 28 );

  TEST_EQUALITY_CONST( subshell, Data::P3_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 29 );

  TEST_EQUALITY_CONST( subshell, Data::P4_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 30 );

  TEST_EQUALITY_CONST( subshell, Data::P5_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 31 );

  TEST_EQUALITY_CONST( subshell, Data::P6_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 32 );

  TEST_EQUALITY_CONST( subshell, Data::P7_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 33 );

  TEST_EQUALITY_CONST( subshell, Data::P8_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 34 );

  TEST_EQUALITY_CONST( subshell, Data::P9_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 35 );

  TEST_EQUALITY_CONST( subshell, Data::P10_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 36 );

  TEST_EQUALITY_CONST( subshell, Data::P11_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 37 );

  TEST_EQUALITY_CONST( subshell, Data::Q1_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 38 );

  TEST_EQUALITY_CONST( subshell, Data::Q2_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 39 );

  TEST_EQUALITY_CONST( subshell, Data::Q3_SUBSHELL );

  subshell = Data::convertENDFDesignatorToSubshellEnum( 40 );

  TEST_EQUALITY_CONST( subshell, Data::INVALID_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that a SubshellType enum can be converted to an integer
TEUCHOS_UNIT_TEST( SubshellType, endf_integer_conversion )
{
  TEST_EQUALITY_CONST( Data::K_SUBSHELL, 1 );
  TEST_EQUALITY_CONST( Data::L1_SUBSHELL, 2 );
  TEST_EQUALITY_CONST( Data::L2_SUBSHELL, 3 );
  TEST_EQUALITY_CONST( Data::L3_SUBSHELL, 4 );
  TEST_EQUALITY_CONST( Data::M1_SUBSHELL, 5 );
  TEST_EQUALITY_CONST( Data::M2_SUBSHELL, 6 );
  TEST_EQUALITY_CONST( Data::M3_SUBSHELL, 7 );
  TEST_EQUALITY_CONST( Data::M4_SUBSHELL, 8 );
  TEST_EQUALITY_CONST( Data::M5_SUBSHELL, 9 );
  TEST_EQUALITY_CONST( Data::N1_SUBSHELL, 10 );
  TEST_EQUALITY_CONST( Data::N2_SUBSHELL, 11 );
  TEST_EQUALITY_CONST( Data::N3_SUBSHELL, 12 );
  TEST_EQUALITY_CONST( Data::N4_SUBSHELL, 13 );
  TEST_EQUALITY_CONST( Data::N5_SUBSHELL, 14 );
  TEST_EQUALITY_CONST( Data::N6_SUBSHELL, 15 );
  TEST_EQUALITY_CONST( Data::N7_SUBSHELL, 16 );
  TEST_EQUALITY_CONST( Data::O1_SUBSHELL, 17 );
  TEST_EQUALITY_CONST( Data::O2_SUBSHELL, 18 );
  TEST_EQUALITY_CONST( Data::O3_SUBSHELL, 19 );
  TEST_EQUALITY_CONST( Data::O4_SUBSHELL, 20 );
  TEST_EQUALITY_CONST( Data::O5_SUBSHELL, 21 );
  TEST_EQUALITY_CONST( Data::O6_SUBSHELL, 22 );
  TEST_EQUALITY_CONST( Data::O7_SUBSHELL, 23 );
  TEST_EQUALITY_CONST( Data::O8_SUBSHELL, 24 );
  TEST_EQUALITY_CONST( Data::O9_SUBSHELL, 25 );
  TEST_EQUALITY_CONST( Data::P1_SUBSHELL, 26 );
  TEST_EQUALITY_CONST( Data::P2_SUBSHELL, 27 );
  TEST_EQUALITY_CONST( Data::P3_SUBSHELL, 28 );
  TEST_EQUALITY_CONST( Data::P4_SUBSHELL, 29 );
  TEST_EQUALITY_CONST( Data::P5_SUBSHELL, 30 );
  TEST_EQUALITY_CONST( Data::P6_SUBSHELL, 31 );
  TEST_EQUALITY_CONST( Data::P7_SUBSHELL, 32 );
  TEST_EQUALITY_CONST( Data::P8_SUBSHELL, 33 );
  TEST_EQUALITY_CONST( Data::P9_SUBSHELL, 34 );
  TEST_EQUALITY_CONST( Data::P10_SUBSHELL, 35 );
  TEST_EQUALITY_CONST( Data::P11_SUBSHELL, 36 );
  TEST_EQUALITY_CONST( Data::Q1_SUBSHELL, 37 );
  TEST_EQUALITY_CONST( Data::Q2_SUBSHELL, 38 );
  TEST_EQUALITY_CONST( Data::Q3_SUBSHELL, 39 );
}

//---------------------------------------------------------------------------//
// Check that an EADL designator can be converted to a subshell type
TEUCHOS_UNIT_TEST( SubshellType, convertEADLDesignatorToSubshellEnum )
{
  Data::SubshellType subshell = Data::convertEADLDesignatorToSubshellEnum( 0 );

  TEST_EQUALITY_CONST( subshell, Data::INVALID_SUBSHELL );
  
  subshell = Data::convertEADLDesignatorToSubshellEnum( 1 );

  TEST_EQUALITY_CONST( subshell, Data::K_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 2 );

  TEST_EQUALITY_CONST( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 3 );

  TEST_EQUALITY_CONST( subshell, Data::L1_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 4 );

  TEST_EQUALITY_CONST( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 5 );

  TEST_EQUALITY_CONST( subshell, Data::L2_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 6 );

  TEST_EQUALITY_CONST( subshell, Data::L3_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 7 );

  TEST_EQUALITY_CONST( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 8 );

  TEST_EQUALITY_CONST( subshell, Data::M1_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 9 );

  TEST_EQUALITY_CONST( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 10 );

  TEST_EQUALITY_CONST( subshell, Data::M2_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 11 );

  TEST_EQUALITY_CONST( subshell, Data::M3_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 12 );

  TEST_EQUALITY_CONST( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 13 );

  TEST_EQUALITY_CONST( subshell, Data::M4_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 14 );

  TEST_EQUALITY_CONST( subshell, Data::M5_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 15 );

  TEST_EQUALITY_CONST( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 16 );

  TEST_EQUALITY_CONST( subshell, Data::N1_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 17 );

  TEST_EQUALITY_CONST( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 18 );

  TEST_EQUALITY_CONST( subshell, Data::N2_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 19 );

  TEST_EQUALITY_CONST( subshell, Data::N3_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 20 );

  TEST_EQUALITY_CONST( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 21 );

  TEST_EQUALITY_CONST( subshell, Data::N4_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 22 );

  TEST_EQUALITY_CONST( subshell, Data::N5_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 23 );

  TEST_EQUALITY_CONST( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 24 );

  TEST_EQUALITY_CONST( subshell, Data::N6_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 25 );

  TEST_EQUALITY_CONST( subshell, Data::N7_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 26 );

  TEST_EQUALITY_CONST( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 27 );

  TEST_EQUALITY_CONST( subshell, Data::O1_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 28 );

  TEST_EQUALITY_CONST( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 29 );

  TEST_EQUALITY_CONST( subshell, Data::O2_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 30 );

  TEST_EQUALITY_CONST( subshell, Data::O3_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 31 );

  TEST_EQUALITY_CONST( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 32 );

  TEST_EQUALITY_CONST( subshell, Data::O4_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 33 );

  TEST_EQUALITY_CONST( subshell, Data::O5_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 34 );

  TEST_EQUALITY_CONST( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 35 );

  TEST_EQUALITY_CONST( subshell, Data::O6_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 36 );

  TEST_EQUALITY_CONST( subshell, Data::O7_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 37 );

  TEST_EQUALITY_CONST( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 38 );

  TEST_EQUALITY_CONST( subshell, Data::O8_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 39 );

  TEST_EQUALITY_CONST( subshell, Data::O9_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 40 );

  TEST_EQUALITY_CONST( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 41 );

  TEST_EQUALITY_CONST( subshell, Data::P1_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 42 );

  TEST_EQUALITY_CONST( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 43 );

  TEST_EQUALITY_CONST( subshell, Data::P2_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 44 );

  TEST_EQUALITY_CONST( subshell, Data::P3_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 45 );

  TEST_EQUALITY_CONST( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 46 );

  TEST_EQUALITY_CONST( subshell, Data::P4_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 47 );

  TEST_EQUALITY_CONST( subshell, Data::P5_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 48 );

  TEST_EQUALITY_CONST( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 49 );

  TEST_EQUALITY_CONST( subshell, Data::P6_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 50 );

  TEST_EQUALITY_CONST( subshell, Data::P7_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 51 );

  TEST_EQUALITY_CONST( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 52 );

  TEST_EQUALITY_CONST( subshell, Data::P8_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 53 );

  TEST_EQUALITY_CONST( subshell, Data::P9_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 54 );

  TEST_EQUALITY_CONST( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 55 );

  TEST_EQUALITY_CONST( subshell, Data::P10_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 56 );

  TEST_EQUALITY_CONST( subshell, Data::P11_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 57 );

  TEST_EQUALITY_CONST( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 58 );

  TEST_EQUALITY_CONST( subshell, Data::Q1_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 59 );

  TEST_EQUALITY_CONST( subshell, Data::INVALID_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 60 );

  TEST_EQUALITY_CONST( subshell, Data::Q2_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 61 );

  TEST_EQUALITY_CONST( subshell, Data::Q3_SUBSHELL );

  subshell = Data::convertEADLDesignatorToSubshellEnum( 62 );

  TEST_EQUALITY_CONST( subshell, Data::INVALID_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that an EADL designator can be converted to an ENDF designator
TEUCHOS_UNIT_TEST( SubshellType, convertEADLDesignatorToENDFDesignator )
{
  TEST_THROW( Data::convertEADLDesignatorToENDFDesignator( 0 ),
              std::logic_error );

  unsigned endf_designator = Data::convertEADLDesignatorToENDFDesignator( 1 );

  TEST_EQUALITY_CONST( endf_designator, 1 );

  TEST_THROW( Data::convertEADLDesignatorToENDFDesignator( 2 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 3 );

  TEST_EQUALITY_CONST( endf_designator, 2 );

  TEST_THROW( Data::convertEADLDesignatorToENDFDesignator( 4 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 5 );

  TEST_EQUALITY_CONST( endf_designator, 3 );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 6 );

  TEST_EQUALITY_CONST( endf_designator, 4 );

  TEST_THROW( Data::convertEADLDesignatorToENDFDesignator( 7 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 8 );

  TEST_EQUALITY_CONST( endf_designator, 5 );

  TEST_THROW( Data::convertEADLDesignatorToENDFDesignator( 9 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 10 );

  TEST_EQUALITY_CONST( endf_designator, 6 );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 11 );

  TEST_EQUALITY_CONST( endf_designator, 7 );

  TEST_THROW( Data::convertEADLDesignatorToENDFDesignator( 12 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 13 );

  TEST_EQUALITY_CONST( endf_designator, 8 );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 14 );

  TEST_EQUALITY_CONST( endf_designator, 9 );

  TEST_THROW( Data::convertEADLDesignatorToENDFDesignator( 15 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 16 );

  TEST_EQUALITY_CONST( endf_designator, 10 );

  TEST_THROW( Data::convertEADLDesignatorToENDFDesignator( 17 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 18 );

  TEST_EQUALITY_CONST( endf_designator, 11 );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 19 );

  TEST_EQUALITY_CONST( endf_designator, 12 );

  TEST_THROW( Data::convertEADLDesignatorToENDFDesignator( 20 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 21 );

  TEST_EQUALITY_CONST( endf_designator, 13 );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 22 );

  TEST_EQUALITY_CONST( endf_designator, 14 );

  TEST_THROW( Data::convertEADLDesignatorToENDFDesignator( 23 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 24 );

  TEST_EQUALITY_CONST( endf_designator, 15 );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 25 );

  TEST_EQUALITY_CONST( endf_designator, 16 );

  TEST_THROW( Data::convertEADLDesignatorToENDFDesignator( 26 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 27 );

  TEST_EQUALITY_CONST( endf_designator, 17 );

  TEST_THROW( Data::convertEADLDesignatorToENDFDesignator( 28 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 29 );

  TEST_EQUALITY_CONST( endf_designator, 18 );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 30 );

  TEST_EQUALITY_CONST( endf_designator, 19 );

  TEST_THROW( Data::convertEADLDesignatorToENDFDesignator( 31 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 32 );

  TEST_EQUALITY_CONST( endf_designator, 20 );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 33 );

  TEST_EQUALITY_CONST( endf_designator, 21 );

  TEST_THROW( Data::convertEADLDesignatorToENDFDesignator( 34 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 35 );

  TEST_EQUALITY_CONST( endf_designator, 22 );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 36 );

  TEST_EQUALITY_CONST( endf_designator, 23 );

  TEST_THROW( Data::convertEADLDesignatorToENDFDesignator( 37 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 38 );

  TEST_EQUALITY_CONST( endf_designator, 24 );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 39 );

  TEST_EQUALITY_CONST( endf_designator, 25 );

  TEST_THROW( Data::convertEADLDesignatorToENDFDesignator( 40 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 41 );

  TEST_EQUALITY_CONST( endf_designator, 26 );

  TEST_THROW( Data::convertEADLDesignatorToENDFDesignator( 42 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 43 );

  TEST_EQUALITY_CONST( endf_designator, 27 );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 44 );

  TEST_EQUALITY_CONST( endf_designator, 28 );

  TEST_THROW( Data::convertEADLDesignatorToENDFDesignator( 45 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 46 );

  TEST_EQUALITY_CONST( endf_designator, 29 );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 47 );

  TEST_EQUALITY_CONST( endf_designator, 30 );

  TEST_THROW( Data::convertEADLDesignatorToENDFDesignator( 48 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 49 );

  TEST_EQUALITY_CONST( endf_designator, 31 );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 50 );

  TEST_EQUALITY_CONST( endf_designator, 32 );

  TEST_THROW( Data::convertEADLDesignatorToENDFDesignator( 51 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 52 );

  TEST_EQUALITY_CONST( endf_designator, 33 );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 53 );

  TEST_EQUALITY_CONST( endf_designator, 34 );

  TEST_THROW( Data::convertEADLDesignatorToENDFDesignator( 54 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 55 );

  TEST_EQUALITY_CONST( endf_designator, 35 );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 56 );

  TEST_EQUALITY_CONST( endf_designator, 36 );

  TEST_THROW( Data::convertEADLDesignatorToENDFDesignator( 57 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 58 );

  TEST_EQUALITY_CONST( endf_designator, 37 );

  TEST_THROW( Data::convertEADLDesignatorToENDFDesignator( 59 ),
              std::logic_error );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 60 );

  TEST_EQUALITY_CONST( endf_designator, 38 );

  endf_designator = Data::convertEADLDesignatorToENDFDesignator( 61 );

  TEST_EQUALITY_CONST( endf_designator, 39 );

  TEST_THROW( Data::convertEADLDesignatorToENDFDesignator( 62 ),
              std::logic_error );
}

//---------------------------------------------------------------------------//
// Check that a subshell type can be converted to a string
TEUCHOS_UNIT_TEST( SubshellType, convertSubshellEnumToString )
{
  std::string subshell_name =
    Data::convertSubshellEnumToString( Data::K_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "K" );

  subshell_name = Data::convertSubshellEnumToString( Data::L1_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "L1" );

  subshell_name = Data::convertSubshellEnumToString( Data::L2_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "L2" );

  subshell_name = Data::convertSubshellEnumToString( Data::L3_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "L3" );

  subshell_name = Data::convertSubshellEnumToString( Data::M1_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "M1" );

  subshell_name = Data::convertSubshellEnumToString( Data::M2_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "M2" );

  subshell_name = Data::convertSubshellEnumToString( Data::M3_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "M3" );

  subshell_name = Data::convertSubshellEnumToString( Data::M4_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "M4" );

  subshell_name = Data::convertSubshellEnumToString( Data::M5_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "M5" );

  subshell_name = Data::convertSubshellEnumToString( Data::N1_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "N1" );

  subshell_name = Data::convertSubshellEnumToString( Data::N2_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "N2" );

  subshell_name = Data::convertSubshellEnumToString( Data::N3_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "N3" );

  subshell_name = Data::convertSubshellEnumToString( Data::N4_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "N4" );

  subshell_name = Data::convertSubshellEnumToString( Data::N5_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "N5" );

  subshell_name = Data::convertSubshellEnumToString( Data::N6_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "N6" );

  subshell_name = Data::convertSubshellEnumToString( Data::N7_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "N7" );

  subshell_name = Data::convertSubshellEnumToString( Data::O1_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "O1" );

  subshell_name = Data::convertSubshellEnumToString( Data::O2_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "O2" );

  subshell_name = Data::convertSubshellEnumToString( Data::O3_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "O3" );

  subshell_name = Data::convertSubshellEnumToString( Data::O4_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "O4" );

  subshell_name = Data::convertSubshellEnumToString( Data::O5_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "O5" );

  subshell_name = Data::convertSubshellEnumToString( Data::O6_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "O6" );

  subshell_name = Data::convertSubshellEnumToString( Data::O7_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "O7" );

  subshell_name = Data::convertSubshellEnumToString( Data::O8_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "O8" );

  subshell_name = Data::convertSubshellEnumToString( Data::O9_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "O9" );

  subshell_name = Data::convertSubshellEnumToString( Data::P1_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "P1" );

  subshell_name = Data::convertSubshellEnumToString( Data::P2_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "P2" );

  subshell_name = Data::convertSubshellEnumToString( Data::P3_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "P3" );

  subshell_name = Data::convertSubshellEnumToString( Data::P4_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "P4" );

  subshell_name = Data::convertSubshellEnumToString( Data::P5_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "P5" );

  subshell_name = Data::convertSubshellEnumToString( Data::P6_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "P6" );

  subshell_name = Data::convertSubshellEnumToString( Data::P7_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "P7" );

  subshell_name = Data::convertSubshellEnumToString( Data::P8_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "P8" );

  subshell_name = Data::convertSubshellEnumToString( Data::P9_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "P9" );

  subshell_name = Data::convertSubshellEnumToString( Data::P10_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "P10" );

  subshell_name = Data::convertSubshellEnumToString( Data::P11_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "P11" );

  subshell_name = Data::convertSubshellEnumToString( Data::Q1_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "Q1" );

  subshell_name = Data::convertSubshellEnumToString( Data::Q2_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "Q2" );

  subshell_name = Data::convertSubshellEnumToString( Data::Q3_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "Q3" );

  subshell_name = Data::convertSubshellEnumToString( Data::UNKNOWN_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "Unknown" );

  subshell_name = Data::convertSubshellEnumToString( Data::INVALID_SUBSHELL );

  TEST_EQUALITY_CONST( subshell_name, "Invalid" );
}

//---------------------------------------------------------------------------//
// Check that a subshell type can be placed in an output stream
TEUCHOS_UNIT_TEST( SubshellType, stream_operator )
{
  std::ostringstream oss;
  oss << Data::K_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "K" );

  oss.str( "" );
  oss.clear();

  oss << Data::L1_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "L1" );

  oss.str( "" );
  oss.clear();

  oss << Data::L2_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "L2" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::L3_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "L3" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::M1_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "M1" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::M2_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "M2" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::M3_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "M3" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::M4_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "M4" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::M5_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "M5" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::N1_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "N1" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::N2_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "N2" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::N3_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "N3" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::N4_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "N4" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::N5_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "N5" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::N6_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "N6" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::N7_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "N7" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::O1_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "O1" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::O2_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "O2" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::O3_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "O3" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::O4_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "O4" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::O5_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "O5" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::O6_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "O6" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::O7_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "O7" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::O8_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "O8" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::O9_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "O9" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::P1_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "P1" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::P2_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "P2" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::P3_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "P3" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::P4_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "P4" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::P5_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "P5" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::P6_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "P6" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::P7_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "P7" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::P8_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "P8" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::P9_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "P9" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::P10_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "P10" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::P11_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "P11" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::Q1_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "Q1" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::Q2_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "Q2" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::Q3_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "Q3" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::UNKNOWN_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "Unknown" );

  oss.str( "" );
  oss.clear();
  
  oss << Data::INVALID_SUBSHELL;

  TEST_EQUALITY_CONST( oss.str(), "Invalid" );
}

//---------------------------------------------------------------------------//
// end tstSubshellTypeHelpers.cpp
//---------------------------------------------------------------------------//
