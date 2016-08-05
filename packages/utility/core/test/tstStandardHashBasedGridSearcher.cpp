//---------------------------------------------------------------------------//
//!
//! \file   tstHashBasedGridGenerator.cpp
//! \author Alex Robinson
//! \brief  Hash-based grid searcher unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_ArrayRCP.hpp>

// FRENSIE Includes
#include "Utility_StandardHashBasedGridSearcher.hpp"

//---------------------------------------------------------------------------//
// Testing variables
//---------------------------------------------------------------------------//

Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher;

Teuchos::RCP<Utility::HashBasedGridSearcher> processed_grid_searcher;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a value can be tested for containment within the grid
TEUCHOS_UNIT_TEST( HashBasedGridGenerator, isValueWithinGridBounds )
{
  TEST_ASSERT( !grid_searcher->isValueWithinGridBounds( 0.5 ) );
  TEST_ASSERT( grid_searcher->isValueWithinGridBounds( 1.0 ) );
  TEST_ASSERT( grid_searcher->isValueWithinGridBounds( 500.0 ) );
  TEST_ASSERT( grid_searcher->isValueWithinGridBounds( 1000.0 ) );
  TEST_ASSERT( !grid_searcher->isValueWithinGridBounds( 1000.5 ) );

  TEST_ASSERT( !processed_grid_searcher->isValueWithinGridBounds( 0.5 ) );
  TEST_ASSERT( processed_grid_searcher->isValueWithinGridBounds( 1.0 ) );
  TEST_ASSERT( processed_grid_searcher->isValueWithinGridBounds( 500.0 ) );
  TEST_ASSERT( processed_grid_searcher->isValueWithinGridBounds( 1000.0 ) );
  TEST_ASSERT( !processed_grid_searcher->isValueWithinGridBounds( 1000.5 ) );
}

//---------------------------------------------------------------------------//
// Check that the index of the lower bin boundary of a value can be found
TEUCHOS_UNIT_TEST( HashBasedGridGenerator, findLowerBinIndex )
{
  unsigned grid_index = grid_searcher->findLowerBinIndex( 1.0 );

  TEST_EQUALITY_CONST( grid_index, 0u );

  grid_index = grid_searcher->findLowerBinIndex( 1.5 );

  TEST_EQUALITY_CONST( grid_index, 0u );

  grid_index = grid_searcher->findLowerBinIndex( 10.0 );

  TEST_EQUALITY_CONST( grid_index, 9u );

  grid_index = grid_searcher->findLowerBinIndex( 10.5 );

  TEST_EQUALITY_CONST( grid_index, 9u );

  grid_index = grid_searcher->findLowerBinIndex( 100.0 );

  TEST_EQUALITY_CONST( grid_index, 99u );

  grid_index = grid_searcher->findLowerBinIndex( 100.5 );

  TEST_EQUALITY_CONST( grid_index, 99u );

  grid_index = grid_searcher->findLowerBinIndex( 1000.0 );

  TEST_EQUALITY_CONST( grid_index, 998u );
}

//---------------------------------------------------------------------------//
// Check that the index of the lower bin boundary of a value can be found
TEUCHOS_UNIT_TEST( HashBasedGridGenerator, findLowerBinIndex_processed )
{
  unsigned grid_index = grid_searcher->findLowerBinIndex( 1.0 );

  TEST_EQUALITY_CONST( grid_index, 0u );

  grid_index = processed_grid_searcher->findLowerBinIndex( 1.5 );

  TEST_EQUALITY_CONST( grid_index, 0u );

  grid_index = processed_grid_searcher->findLowerBinIndex( 10.0 );

  TEST_EQUALITY_CONST( grid_index, 9u );

  grid_index = processed_grid_searcher->findLowerBinIndex( 10.5 );

  TEST_EQUALITY_CONST( grid_index, 9u );

  grid_index = processed_grid_searcher->findLowerBinIndex( 100.0 );

  TEST_EQUALITY_CONST( grid_index, 99u );

  grid_index = processed_grid_searcher->findLowerBinIndex( 100.5 );

  TEST_EQUALITY_CONST( grid_index, 99u );

  grid_index = processed_grid_searcher->findLowerBinIndex( 1000.0 );

  TEST_EQUALITY_CONST( grid_index, 998u );
}


//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  const Teuchos::RCP<Teuchos::FancyOStream> out =
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return =
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  {
    // Create the grid and processed grid
    Teuchos::ArrayRCP<double> grid( 1000 ), processed_grid( 1000 );

    for( unsigned i = 0; i < grid.size(); ++i )
    {
      grid[i] = i+1;

      processed_grid[i] = log( i+1 );
    }

    grid_searcher.reset(
	new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<double> >(
						       grid,
						       grid[0],
						       grid[grid.size()-1],
						       100 ) );

    processed_grid_searcher.reset(
    new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<double>,true>(
				       processed_grid,
				       processed_grid[0],
				       processed_grid[processed_grid.size()-1],
				       100 ) );
  }

  // Run the unit tests
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  const bool success = Teuchos::UnitTestRepository::runUnitTests( *out );

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstHashBasedGridSearcher.cpp
//---------------------------------------------------------------------------//
