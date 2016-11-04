//---------------------------------------------------------------------------//
//!
//! \file   tstStandardComptonProfileSubshellConverter.cpp
//! \author Alex Robinson
//! \brief  Standard Compton profile subshell-to-index converter unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_ComptonProfileSubshellConverterFactory.hpp"

using namespace MonteCarlo;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<ComptonProfileSubshellConverter> converter;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check the Z=1 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_1 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 1 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_THROW( converter->convertSubshellToIndex( Data::L1_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::L1_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=2 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_2 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 2 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_THROW( converter->convertSubshellToIndex( Data::L1_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::L1_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=3 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_3 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 3 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_THROW( converter->convertSubshellToIndex( Data::L2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::L2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=4 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_4 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 4 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_THROW( converter->convertSubshellToIndex( Data::L2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::L2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=5 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_5 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 5 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  TEST_THROW( converter->convertSubshellToIndex( Data::M1_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::M1_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=6 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_6 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 6 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  TEST_THROW( converter->convertSubshellToIndex( Data::M1_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::M1_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=7 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_7 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 7 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  TEST_THROW( converter->convertSubshellToIndex( Data::M1_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::M1_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=8 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_8 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 8 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  TEST_THROW( converter->convertSubshellToIndex( Data::M1_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::M1_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=9 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_9 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 9 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  TEST_THROW( converter->convertSubshellToIndex( Data::M1_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::M1_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=10 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_10 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 10 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  TEST_THROW( converter->convertSubshellToIndex( Data::M1_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::M1_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=11 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_11 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 11 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  TEST_THROW( converter->convertSubshellToIndex( Data::M2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::M2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=12 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_12 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 12 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  TEST_THROW( converter->convertSubshellToIndex( Data::M2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::M2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=13 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_13 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 13 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  TEST_THROW( converter->convertSubshellToIndex( Data::M4_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::M4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=14 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_14 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 14 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  TEST_THROW( converter->convertSubshellToIndex( Data::M4_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::M4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=15 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_15 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 15 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  TEST_THROW( converter->convertSubshellToIndex( Data::M4_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::M4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=16 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_16 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 16 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  TEST_THROW( converter->convertSubshellToIndex( Data::M4_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::M4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=17 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_17 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 17 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  TEST_THROW( converter->convertSubshellToIndex( Data::M4_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::M4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=18 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_18 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 18 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  TEST_THROW( converter->convertSubshellToIndex( Data::M4_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::M4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=19 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_19 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 19 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 5u );
  TEST_THROW( converter->convertSubshellToIndex( Data::M4_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::N2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::N2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=20 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_20 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 20 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 5u );
  TEST_THROW( converter->convertSubshellToIndex( Data::M4_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::N2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::N2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=21 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_21 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 21 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 6u );
  TEST_THROW( converter->convertSubshellToIndex( Data::N2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::N2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=22 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_22 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 22 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 6u );
  TEST_THROW( converter->convertSubshellToIndex( Data::N2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::N2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=22 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_23 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 23 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 6u );
  TEST_THROW( converter->convertSubshellToIndex( Data::N2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::N2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=24 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_24 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 24 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 6u );
  TEST_THROW( converter->convertSubshellToIndex( Data::N2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::N2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=25 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_25 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 25 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 6u );
  TEST_THROW( converter->convertSubshellToIndex( Data::N2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::N2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=26 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_26 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 26 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 6u );
  TEST_THROW( converter->convertSubshellToIndex( Data::N2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::N2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=27 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_27 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 27 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 6u );
  TEST_THROW( converter->convertSubshellToIndex( Data::N2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::N2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=28 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_28 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 28 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 6u );
  TEST_THROW( converter->convertSubshellToIndex( Data::N2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::N2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=29 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_29 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 29 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 6u );
  TEST_THROW( converter->convertSubshellToIndex( Data::N2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::N2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=30 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_30 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 30 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 6u );
  TEST_THROW( converter->convertSubshellToIndex( Data::N2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::N2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=31 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_31 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 31 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 7u );
  TEST_THROW( converter->convertSubshellToIndex( Data::N4_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::N4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=32 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_32 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 32 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 7u );
  TEST_THROW( converter->convertSubshellToIndex( Data::N4_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::N4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=33 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_33 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 33 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 7u );
  TEST_THROW( converter->convertSubshellToIndex( Data::N4_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::N4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=34 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_34 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 34 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 7u );
  TEST_THROW( converter->convertSubshellToIndex( Data::N4_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::N4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=35 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_35 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 35 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 7u );
  TEST_THROW( converter->convertSubshellToIndex( Data::N4_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::N4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=36 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_36 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 36 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_THROW( converter->convertSubshellToIndex( Data::N4_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::N4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=37 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_37 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 37 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 12u );
  TEST_THROW( converter->convertSubshellToIndex( Data::N4_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::O2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=38 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_38 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 38 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 12u );
  TEST_THROW( converter->convertSubshellToIndex( Data::N4_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::O2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=39 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_39 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 39 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 13u );
  TEST_THROW( converter->convertSubshellToIndex( Data::N6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::O2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=40 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_40 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 40 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 13u );
  TEST_THROW( converter->convertSubshellToIndex( Data::N6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::O2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=41 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_41 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 41 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 13u );
  TEST_THROW( converter->convertSubshellToIndex( Data::N6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::O2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=42 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_42 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 42 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 14u );
  TEST_THROW( converter->convertSubshellToIndex( Data::N6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::O2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=43 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_43 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 43 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 14u );
  TEST_THROW( converter->convertSubshellToIndex( Data::N6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::O2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=44 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_44 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 44 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 14u );
  TEST_THROW( converter->convertSubshellToIndex( Data::N6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::O2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=45 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_45 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 45 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 14u );
  TEST_THROW( converter->convertSubshellToIndex( Data::N6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::O2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=46 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_46 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 46 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O1_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::N6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::O2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=47 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_47 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 47 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 14u );
  TEST_THROW( converter->convertSubshellToIndex( Data::N6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::O2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=48 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_48 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 48 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 14u );
  TEST_THROW( converter->convertSubshellToIndex( Data::N6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::O2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=49 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_49 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 49 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 15u );
  TEST_THROW( converter->convertSubshellToIndex( Data::N6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::O4_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=50 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_50 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 50 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 15u );
  TEST_THROW( converter->convertSubshellToIndex( Data::N6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::O4_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=51 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_51 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 51 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 16u );
  TEST_THROW( converter->convertSubshellToIndex( Data::N6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::O4_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=52 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_52 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 52 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 16u );
  TEST_THROW( converter->convertSubshellToIndex( Data::N6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::O4_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=53 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_53 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 53 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 16u );
  TEST_THROW( converter->convertSubshellToIndex( Data::N6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::O4_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=54 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_54 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 54 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 16u );
  TEST_THROW( converter->convertSubshellToIndex( Data::N6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::O4_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=55 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_55 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 55 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 17u );
  TEST_THROW( converter->convertSubshellToIndex( Data::N6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::O4_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=56 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_56 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 56 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 17u );
  TEST_THROW( converter->convertSubshellToIndex( Data::N6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::O4_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=57 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_57 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 57 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 18u );
  TEST_THROW( converter->convertSubshellToIndex( Data::N6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=58 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_58 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 58 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 19u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O4_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=59 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_59 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 59 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 18u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O4_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=60 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_60 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 60 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 18u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O4_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=61 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_61 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 61 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 18u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O4_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=62 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_62 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 62 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 18u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O4_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=63 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_63 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 63 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 19u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O4_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=64 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_64 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 64 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 19u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 20u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=65 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_65 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 65 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 19u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O4_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=66 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_66 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 66 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 19u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O4_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=67 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_67 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 67 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 19u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O4_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=68 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_68 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 68 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 19u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O4_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=69 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_69 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 69 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 19u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O4_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=70 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_70 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 70 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 19u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O4_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=71 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_71 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 71 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 19u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 20u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=72 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_72 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 72 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 19u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 20u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=73 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_73 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 73 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 19u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 20u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=74 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_74 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 74 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 19u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 20u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=75 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_75 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 75 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 21u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=76 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_76 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 76 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 21u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=77 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_77 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 77 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P1_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P1_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=78 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_78 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 78 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 21u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=79 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_79 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 79 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 21u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=80 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_80 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 80 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 21u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=81 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_81 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 81 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 21u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 22u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 22u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P4_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=82 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_82 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 82 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 21u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 22u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 22u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P4_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=83 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_83 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 83 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 21u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 22u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 23u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P4_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=84 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_84 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 84 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 21u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 22u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 23u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P4_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=85 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_85 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 85 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 21u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 22u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 23u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P4_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=86 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_86 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 86 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 21u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 22u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 23u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P4_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=87 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_87 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 87 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 21u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 22u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 23u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::Q1_SUBSHELL ), 24u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P4_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::Q2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::Q1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::Q2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=88 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_88 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 88 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 21u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 22u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 23u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::Q1_SUBSHELL ), 24u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P4_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::Q2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::Q1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::Q2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=89 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_89 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 89 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 21u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 22u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 23u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P4_SUBSHELL ), 24u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P5_SUBSHELL ), 24u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::Q1_SUBSHELL ), 25u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::Q2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::Q1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::Q2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=90 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_90 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 90 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 21u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 22u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 23u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P4_SUBSHELL ), 24u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P5_SUBSHELL ), 24u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::Q1_SUBSHELL ), 25u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::Q2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::Q1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::Q2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=91 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_91 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 91 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O6_SUBSHELL ), 21u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O7_SUBSHELL ), 21u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 22u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 23u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 24u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P4_SUBSHELL ), 25u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P5_SUBSHELL ), 25u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::Q1_SUBSHELL ), 26u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O8_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::Q2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O7_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O8_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::Q1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::Q2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=92 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_92 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 92 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O6_SUBSHELL ), 21u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O7_SUBSHELL ), 21u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 22u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 23u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 24u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P4_SUBSHELL ), 25u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P5_SUBSHELL ), 25u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::Q1_SUBSHELL ), 26u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O8_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::Q2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O7_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O8_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::Q1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::Q2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=93 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_93 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 93 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O6_SUBSHELL ), 21u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O7_SUBSHELL ), 21u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 22u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 23u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 24u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P4_SUBSHELL ), 25u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P5_SUBSHELL ), 25u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::Q1_SUBSHELL ), 26u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O8_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::Q2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O7_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O8_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::Q1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::Q2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=94 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_94 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 94 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O6_SUBSHELL ), 21u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O7_SUBSHELL ), 21u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 22u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 23u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 24u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::Q1_SUBSHELL ), 25u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O8_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P4_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::Q2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O7_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O8_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::Q1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::Q2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=95 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_95 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 95 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O6_SUBSHELL ), 21u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O7_SUBSHELL ), 22u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 23u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 24u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 25u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::Q1_SUBSHELL ), 26u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O8_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P4_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::Q2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O7_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O8_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::Q1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::Q2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=96 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_96 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 96 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O6_SUBSHELL ), 21u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O7_SUBSHELL ), 22u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 23u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 24u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 25u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P4_SUBSHELL ), 26u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P5_SUBSHELL ), 26u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::Q1_SUBSHELL ), 27u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O8_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::Q2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O7_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O8_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::Q1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::Q2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=97 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_97 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 97 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O6_SUBSHELL ), 21u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O7_SUBSHELL ), 22u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 23u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 24u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 25u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P4_SUBSHELL ), 21u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P5_SUBSHELL ), 22u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::Q1_SUBSHELL ), 26u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O8_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P6_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::Q2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O7_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O8_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P5_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::Q1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::Q2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=98 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_98 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 98 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O6_SUBSHELL ), 21u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O7_SUBSHELL ), 22u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 23u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 24u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 25u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::Q1_SUBSHELL ), 26u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O8_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P4_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::Q2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O7_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O8_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::Q1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::Q2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=99 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_99 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 99 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O6_SUBSHELL ), 21u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O7_SUBSHELL ), 22u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 23u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 24u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 25u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::Q1_SUBSHELL ), 26u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O8_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P4_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::Q2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O7_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O8_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::Q1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::Q2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=100 converter
TEUCHOS_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_100 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 100 );

  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O6_SUBSHELL ), 21u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::O7_SUBSHELL ), 22u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 23u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 24u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 25u );
  TEST_EQUALITY_CONST( converter->convertSubshellToIndex( Data::Q1_SUBSHELL ), 26u );
  TEST_THROW( converter->convertSubshellToIndex( Data::O8_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::P4_SUBSHELL ),
	      std::logic_error );
  TEST_THROW( converter->convertSubshellToIndex( Data::Q2_SUBSHELL ),
	      std::logic_error );

  TEST_ASSERT( converter->isSubshellValid( Data::K_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::M5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::N7_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O5_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O6_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::O7_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::O8_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::P3_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::P4_SUBSHELL ) );
  TEST_ASSERT( converter->isSubshellValid( Data::Q1_SUBSHELL ) );
  TEST_ASSERT( !converter->isSubshellValid( Data::Q2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// end tstStandardComptonProfileSubshellConverter.cpp
//---------------------------------------------------------------------------//
