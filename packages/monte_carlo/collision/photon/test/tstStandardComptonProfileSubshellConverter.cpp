//---------------------------------------------------------------------------//
//!
//! \file   tstStandardComptonProfileSubshellConverter.cpp
//! \author Alex Robinson
//! \brief  Standard Compton profile subshell-to-index converter unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_ComptonProfileSubshellConverterFactory.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

using namespace MonteCarlo;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<const ComptonProfileSubshellConverter> converter;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check the Z=1 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_1 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 1 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::L1_SUBSHELL ),
	      std::logic_error );

  FRENSIE_CHECK( converter->isSubshellValid( Data::K_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::L1_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=2 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_2 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 2 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::L1_SUBSHELL ),
	      std::logic_error );

  FRENSIE_CHECK( converter->isSubshellValid( Data::K_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::L1_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=3 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_3 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 3 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::L2_SUBSHELL ),
	      std::logic_error );

  FRENSIE_CHECK( converter->isSubshellValid( Data::K_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::L2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=4 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_4 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 4 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::L2_SUBSHELL ),
	      std::logic_error );

  FRENSIE_CHECK( converter->isSubshellValid( Data::K_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::L2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=5 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_5 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 5 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::M1_SUBSHELL ),
	      std::logic_error );

  FRENSIE_CHECK( converter->isSubshellValid( Data::K_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::M1_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=6 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_6 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 6 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::M1_SUBSHELL ),
	      std::logic_error );

  FRENSIE_CHECK( converter->isSubshellValid( Data::K_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::M1_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=7 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_7 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 7 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::M1_SUBSHELL ),
	      std::logic_error );

  FRENSIE_CHECK( converter->isSubshellValid( Data::K_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::M1_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=8 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_8 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 8 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::M1_SUBSHELL ),
	      std::logic_error );

  FRENSIE_CHECK( converter->isSubshellValid( Data::K_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::M1_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=9 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_9 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 9 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::M1_SUBSHELL ),
	      std::logic_error );

  FRENSIE_CHECK( converter->isSubshellValid( Data::K_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::M1_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=10 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_10 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 10 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::M1_SUBSHELL ),
	      std::logic_error );

  FRENSIE_CHECK( converter->isSubshellValid( Data::K_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::M1_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=11 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_11 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 11 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::M2_SUBSHELL ),
	      std::logic_error );

  FRENSIE_CHECK( converter->isSubshellValid( Data::K_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::M2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=12 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_12 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 12 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::M2_SUBSHELL ),
	      std::logic_error );

  FRENSIE_CHECK( converter->isSubshellValid( Data::K_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::M2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=13 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_13 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 13 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::M4_SUBSHELL ),
	      std::logic_error );

  FRENSIE_CHECK( converter->isSubshellValid( Data::K_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::M4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=14 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_14 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 14 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::M4_SUBSHELL ),
	      std::logic_error );

  FRENSIE_CHECK( converter->isSubshellValid( Data::K_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::M4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=15 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_15 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 15 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::M4_SUBSHELL ),
	      std::logic_error );

  FRENSIE_CHECK( converter->isSubshellValid( Data::K_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::M4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=16 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_16 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 16 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::M4_SUBSHELL ),
	      std::logic_error );

  FRENSIE_CHECK( converter->isSubshellValid( Data::K_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::M4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=17 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_17 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 17 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::M4_SUBSHELL ),
	      std::logic_error );

  FRENSIE_CHECK( converter->isSubshellValid( Data::K_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::M4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=18 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_18 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 18 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::M4_SUBSHELL ),
	      std::logic_error );

  FRENSIE_CHECK( converter->isSubshellValid( Data::K_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::M4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=19 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_19 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 19 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 5u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::M4_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::N2_SUBSHELL ),
	      std::logic_error );

  FRENSIE_CHECK( converter->isSubshellValid( Data::K_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::M4_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::N2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=20 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_20 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 20 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 5u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::M4_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::N2_SUBSHELL ),
	      std::logic_error );

  FRENSIE_CHECK( converter->isSubshellValid( Data::K_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::L3_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::M1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::M2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::M3_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::M4_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::N1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::N2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=21 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_21 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 21 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 6u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::N2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::N2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=22 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_22 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 22 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 6u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::N2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::N2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=22 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_23 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 23 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 6u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::N2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::N2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=24 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_24 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 24 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 6u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::N2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::N2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=25 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_25 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 25 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 6u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::N2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::N2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=26 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_26 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 26 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 6u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::N2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::N2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=27 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_27 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 27 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 6u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::N2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::N2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=28 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_28 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 28 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 6u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::N2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::N2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=29 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_29 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 29 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 6u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::N2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::N2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=30 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_30 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 30 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 6u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::N2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::N2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=31 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_31 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 31 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 7u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::N4_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::N4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=32 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_32 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 32 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 7u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::N4_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::N4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=33 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_33 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 33 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 7u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::N4_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::N4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=34 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_34 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 34 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 7u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::N4_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::N4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=35 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_35 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 35 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 7u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::N4_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::N4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=36 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_36 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 36 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::N4_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::N4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=37 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_37 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 37 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 12u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::N4_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::N4_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=38 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_38 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 38 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 12u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::N4_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::N4_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=39 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_39 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 39 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 13u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::N6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::N6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=40 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_40 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 40 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 13u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::N6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::N6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=41 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_41 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 41 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 13u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::N6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::N6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=42 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_42 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 42 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 14u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::N6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::N6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=43 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_43 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 43 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 14u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::N6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::N6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=44 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_44 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 44 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 14u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::N6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::N6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=45 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_45 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 45 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 14u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::N6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::N6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=46 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_46 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 46 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O1_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::N6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::N6_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=47 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_47 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 47 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 14u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::N6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::N6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=48 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_48 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 48 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 14u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::N6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::N6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=49 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_49 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 49 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 15u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::N6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O4_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::N6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=50 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_50 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 50 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 15u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::N6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O4_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::N6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=51 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_51 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 51 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 16u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::N6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O4_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::N6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=52 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_52 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 52 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 16u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::N6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O4_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::N6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=53 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_53 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 53 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 16u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::N6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O4_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::N6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=54 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_54 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 54 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 16u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::N6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O4_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::N6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=55 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_55 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 55 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 17u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::N6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O4_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::N6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O4_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=56 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_56 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 56 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 17u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::N6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O4_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::N6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O4_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=57 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_57 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 57 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 18u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::N6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::N6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O3_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O4_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O5_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=58 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_58 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 58 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 19u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O4_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O4_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=59 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_59 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 59 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 18u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O4_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O4_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=60 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_60 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 60 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 18u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O4_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O4_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=61 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_61 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 61 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 18u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O4_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O4_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=62 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_62 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 62 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 18u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O4_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O4_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=63 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_63 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 63 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 19u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O4_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O4_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=64 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_64 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 64 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 19u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 20u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=65 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_65 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 65 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 19u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O4_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O4_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=66 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_66 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 66 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 19u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O4_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O4_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=67 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_67 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 67 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 19u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O4_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O4_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=68 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_68 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 68 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 19u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O4_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O4_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=69 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_69 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 69 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 19u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O4_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O4_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=70 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_70 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 70 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 19u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O4_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O4_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=71 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_71 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 71 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 19u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 20u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=72 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_72 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 72 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 19u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 20u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=73 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_73 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 73 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 19u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 20u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=74 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_74 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 74 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 19u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 20u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=75 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_75 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 75 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 21u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=76 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_76 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 76 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 21u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=77 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_77 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 77 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P1_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P1_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=78 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_78 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 78 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 21u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=79 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_79 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 79 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 21u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=80 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_80 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 80 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 21u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=81 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_81 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 81 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 21u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 22u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 22u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P4_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P3_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=82 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_82 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 82 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 21u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 22u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 22u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P4_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P3_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=83 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_83 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 83 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 21u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 22u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 23u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P4_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P3_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=84 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_84 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 84 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 21u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 22u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 23u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P4_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P3_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=85 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_85 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 85 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 21u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 22u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 23u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P4_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P3_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=86 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_86 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 86 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 21u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 22u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 23u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P4_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P3_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P4_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=87 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_87 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 87 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 21u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 22u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 23u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::Q1_SUBSHELL ), 24u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P4_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::Q2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P3_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P4_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::Q1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::Q2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=88 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_88 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 88 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 21u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 22u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 23u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::Q1_SUBSHELL ), 24u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P4_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::Q2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P3_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P4_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::Q1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::Q2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=89 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_89 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 89 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 21u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 22u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 23u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P4_SUBSHELL ), 24u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P5_SUBSHELL ), 24u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::Q1_SUBSHELL ), 25u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::Q2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P3_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P4_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P5_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::Q1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::Q2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=90 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_90 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 90 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 21u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 22u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 23u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P4_SUBSHELL ), 24u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P5_SUBSHELL ), 24u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::Q1_SUBSHELL ), 25u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::Q2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P3_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P4_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P5_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::Q1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::Q2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=91 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_91 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 91 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O6_SUBSHELL ), 21u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O7_SUBSHELL ), 21u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 22u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 23u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 24u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P4_SUBSHELL ), 25u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P5_SUBSHELL ), 25u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::Q1_SUBSHELL ), 26u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O8_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::Q2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( converter->isSubshellValid( Data::O6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O7_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O8_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P3_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P4_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P5_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::Q1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::Q2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=92 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_92 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 92 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O6_SUBSHELL ), 21u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O7_SUBSHELL ), 21u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 22u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 23u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 24u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P4_SUBSHELL ), 25u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P5_SUBSHELL ), 25u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::Q1_SUBSHELL ), 26u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O8_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::Q2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( converter->isSubshellValid( Data::O6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O7_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O8_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P3_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P4_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P5_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::Q1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::Q2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=93 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_93 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 93 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O6_SUBSHELL ), 21u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O7_SUBSHELL ), 21u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 22u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 23u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 24u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P4_SUBSHELL ), 25u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P5_SUBSHELL ), 25u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::Q1_SUBSHELL ), 26u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O8_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::Q2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( converter->isSubshellValid( Data::O6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O7_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O8_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P3_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P4_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P5_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::Q1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::Q2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=94 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_94 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 94 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O6_SUBSHELL ), 21u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O7_SUBSHELL ), 21u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 22u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 23u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 24u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::Q1_SUBSHELL ), 25u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O8_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P4_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::Q2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( converter->isSubshellValid( Data::O6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O7_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O8_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P3_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P4_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::Q1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::Q2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=95 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_95 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 95 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O6_SUBSHELL ), 21u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O7_SUBSHELL ), 22u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 23u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 24u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 25u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::Q1_SUBSHELL ), 26u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O8_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P4_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::Q2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( converter->isSubshellValid( Data::O6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O7_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O8_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P3_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P4_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::Q1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::Q2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=96 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_96 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 96 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O6_SUBSHELL ), 21u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O7_SUBSHELL ), 22u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 23u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 24u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 25u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P4_SUBSHELL ), 26u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P5_SUBSHELL ), 26u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::Q1_SUBSHELL ), 27u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O8_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::Q2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( converter->isSubshellValid( Data::O6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O7_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O8_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P3_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P4_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P5_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::Q1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::Q2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=97 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_97 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 97 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O6_SUBSHELL ), 21u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O7_SUBSHELL ), 22u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 23u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 24u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 25u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P4_SUBSHELL ), 21u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P5_SUBSHELL ), 22u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::Q1_SUBSHELL ), 26u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O8_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P6_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::Q2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( converter->isSubshellValid( Data::O6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O7_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O8_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P3_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P4_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P5_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::Q1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::Q2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=98 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_98 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 98 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O6_SUBSHELL ), 21u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O7_SUBSHELL ), 22u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 23u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 24u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 25u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::Q1_SUBSHELL ), 26u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O8_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P4_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::Q2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( converter->isSubshellValid( Data::O6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O7_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O8_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P3_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P4_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::Q1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::Q2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=99 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_99 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 99 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O6_SUBSHELL ), 21u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O7_SUBSHELL ), 22u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 23u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 24u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 25u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::Q1_SUBSHELL ), 26u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O8_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P4_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::Q2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( converter->isSubshellValid( Data::O6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O7_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O8_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P3_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P4_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::Q1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::Q2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// Check the Z=100 converter
FRENSIE_UNIT_TEST( StandardComptonProfileSubshellConverter,
		   convertSubshellToIndex_100 )
{
  ComptonProfileSubshellConverterFactory::createConverter( converter, 100 );

  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::K_SUBSHELL ), 0u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L1_SUBSHELL ), 1u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L2_SUBSHELL ), 2u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::L3_SUBSHELL ), 3u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M1_SUBSHELL ), 4u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M2_SUBSHELL ), 5u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M3_SUBSHELL ), 6u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M4_SUBSHELL ), 7u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::M5_SUBSHELL ), 8u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N1_SUBSHELL ), 9u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N2_SUBSHELL ), 10u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N3_SUBSHELL ), 11u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N4_SUBSHELL ), 12u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N5_SUBSHELL ), 13u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N6_SUBSHELL ), 14u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::N7_SUBSHELL ), 15u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O1_SUBSHELL ), 16u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O2_SUBSHELL ), 17u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O3_SUBSHELL ), 18u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O4_SUBSHELL ), 19u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O5_SUBSHELL ), 20u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O6_SUBSHELL ), 21u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::O7_SUBSHELL ), 22u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P1_SUBSHELL ), 23u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P2_SUBSHELL ), 24u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::P3_SUBSHELL ), 25u );
  FRENSIE_CHECK_EQUAL( converter->convertSubshellToIndex( Data::Q1_SUBSHELL ), 26u );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::O8_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::P4_SUBSHELL ),
	      std::logic_error );
  FRENSIE_CHECK_THROW( converter->convertSubshellToIndex( Data::Q2_SUBSHELL ),
	      std::logic_error );

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
  FRENSIE_CHECK( converter->isSubshellValid( Data::O6_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::O7_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::O8_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P1_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P2_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::P3_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::P4_SUBSHELL ) );
  FRENSIE_CHECK( converter->isSubshellValid( Data::Q1_SUBSHELL ) );
  FRENSIE_CHECK( !converter->isSubshellValid( Data::Q2_SUBSHELL ) );
}

//---------------------------------------------------------------------------//
// end tstStandardComptonProfileSubshellConverter.cpp
//---------------------------------------------------------------------------//
