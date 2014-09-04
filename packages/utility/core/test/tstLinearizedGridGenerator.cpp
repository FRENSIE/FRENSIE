//---------------------------------------------------------------------------//
//!
//! \file   tstLinearizedGridGenerator.cpp
//! \author Alex Robinson
//! \brief  Linearized grid generator class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>

// Boost Includes
#include <boost/bind.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Utility_LinearizedGridGenerator.hpp"
#include "Utility_SortAlgorithms.hpp"

//---------------------------------------------------------------------------//
// Testing Functions
//---------------------------------------------------------------------------//
double x2( const double x )
{
  return x*x;
}

struct x3
{
  x3( const double a )
    : d_a( a )
  { /* ... */ }
  
  double operator()( const double x )
  {
    return (x-d_a)*(x-d_a)*(x-d_a);
  }

private:

  double d_a;
};

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a linearized grid can be generated for the functions
TEUCHOS_UNIT_TEST( LinearizedGridGenerator, generate )
{
  // Create a linearized grid for x^2
  boost::function<double (double x)> function = &x2;

  Utility::LinearizedGridGenerator generator( function );
  
  Teuchos::Array<double> initial_grid( 2 );
  initial_grid[0] = 0.0;
  initial_grid[1] = 10.0;

  Teuchos::Array<double> linearized_grid;
  
  generator.generate( linearized_grid, initial_grid, 0.001, 1e-12 );

  TEST_ASSERT( Utility::Sort::isSortedAscending( linearized_grid.begin(),
						 linearized_grid.end() ) );
  TEST_EQUALITY_CONST( linearized_grid.size(), 321 );

  linearized_grid.clear();

  // Create a linearized grid for cos(x)
  function = &cos;

  generator.resetFunction( function );

  generator.generate( linearized_grid, initial_grid, 0.001, 1e-12 );

  TEST_ASSERT( Utility::Sort::isSortedAscending( linearized_grid.begin(),
						 linearized_grid.end() ) );
  TEST_EQUALITY_CONST( linearized_grid.size(), 129 );

  linearized_grid.clear();

  // Create a linearized grid for (x-2)^3
  x3 x_cubed( 2 );
  function = boost::bind<double>(x_cubed, _1);


  generator.resetFunction( function );
  
  generator.generate( linearized_grid, initial_grid, 0.001, 1e-12 );
  
  TEST_ASSERT( Utility::Sort::isSortedAscending( linearized_grid.begin(),
						 linearized_grid.end() ) );
  TEST_EQUALITY_CONST( linearized_grid.size(), 708 );
}

//---------------------------------------------------------------------------//
// end tstLinearizedGridGenerator.cpp
//---------------------------------------------------------------------------//
