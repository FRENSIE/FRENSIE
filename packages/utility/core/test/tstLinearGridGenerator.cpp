//---------------------------------------------------------------------------//
//!
//! \file   tstLinearGridGenerator.cpp
//! \author Alex Robinson
//! \brief  Linear grid generator class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>
#include <list>

// Boost Includes
#include <boost/bind.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_LinearGridGenerator.hpp"
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

struct xcosxAB
{
  xcosxAB( const double a,
	   const double b )
    : d_a( a ),
      d_b( b )
  { /* ... */ }
  
  double operator()( const double x )
  {
    if( x < d_a )
      return 0.0;
    else if( x > d_b )
      return 0.0;
    else
      return x*cos(x);
  }

private:

  double d_a;
  double d_b;
};

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a linearized grid can be generated for the functions
TEUCHOS_UNIT_TEST( LinearGridGenerator, generate )
{
  // Create a linearized grid for x^2
  boost::function<double (double x)> function = &x2;

  Utility::LinearGridGenerator generator( function );
  
  Teuchos::Array<double> initial_grid( 2 );
  initial_grid[0] = 0.0;
  initial_grid[1] = 10.0;

  Teuchos::Array<double> linearized_grid;
  
  generator.generate( linearized_grid,
		      initial_grid, 
		      0.001, 
		      1e-12 );

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

  // Create a linearized grid for x*cos(x) in [-1, 1]
  xcosxAB x_cos_x( -1, 1 );
  function = boost::bind<double>(x_cos_x, _1);

  initial_grid.resize( 7 );
  initial_grid[0] = -2.0;
  initial_grid[1] = -1.0 - 1e-15;
  initial_grid[2] = -1.0;
  initial_grid[3] = 0.0;
  initial_grid[4] = 1.0;
  initial_grid[5] = 1.0 + 1e-15;
  initial_grid[6] = 2.0;

  generator.resetFunction( function );

  generator.generate( linearized_grid, initial_grid, 0.001, 1e-12, 1e-14 );

  TEST_ASSERT( Utility::Sort::isSortedAscending( linearized_grid.begin(),
						 linearized_grid.end() ) );
  TEST_EQUALITY_CONST( linearized_grid.size(), 69 );
}

//---------------------------------------------------------------------------//
// Check that a linearized grid can be generated for the functions
TEUCHOS_UNIT_TEST( LinearGridGenerator, generateAndEvaluate )
{
  // Create a linearized grid for x^2
  boost::function<double (double x)> function = &x2;

  Utility::LinearGridGenerator generator( function );
  
  Teuchos::Array<double> initial_grid( 2 );
  initial_grid[0] = 0.0;
  initial_grid[1] = 10.0;

  Teuchos::Array<double> linearized_grid, evaluated_function;
  
  generator.generateAndEvaluate( linearized_grid, 
				 evaluated_function,
				 initial_grid, 
				 0.001, 
				 1e-12 );

  TEST_ASSERT( Utility::Sort::isSortedAscending( linearized_grid.begin(),
						 linearized_grid.end() ) );
  TEST_EQUALITY_CONST( linearized_grid.size(), 321 );
  TEST_EQUALITY_CONST( evaluated_function.size(), 321 );

  linearized_grid.clear();
  evaluated_function.clear();

  // Create a linearized grid for cos(x)
  function = &cos;

  generator.resetFunction( function );

  generator.generateAndEvaluate( linearized_grid, 
				 evaluated_function,
				 initial_grid, 
				 0.001, 
				 1e-12 );

  TEST_ASSERT( Utility::Sort::isSortedAscending( linearized_grid.begin(),
						 linearized_grid.end() ) );
  TEST_EQUALITY_CONST( linearized_grid.size(), 129 );
  TEST_EQUALITY_CONST( evaluated_function.size(), 129 );

  linearized_grid.clear();
  evaluated_function.clear();

  // Create a linearized grid for (x-2)^3
  x3 x_cubed( 2 );
  function = boost::bind<double>(x_cubed, _1);

  generator.resetFunction( function );
  
  generator.generateAndEvaluate( linearized_grid, 
				 evaluated_function,
				 initial_grid, 
				 0.001, 
				 1e-12 );
  
  TEST_ASSERT( Utility::Sort::isSortedAscending( linearized_grid.begin(),
						 linearized_grid.end() ) );
  TEST_EQUALITY_CONST( linearized_grid.size(), 708 );
  TEST_EQUALITY_CONST( evaluated_function.size(), 708 );

  // Create a linearized grid for x*cos(x) in [-1, 1]
  xcosxAB x_cos_x( -1, 1 );
  function = boost::bind<double>(x_cos_x, _1);

  initial_grid.resize( 7 );
  initial_grid[0] = -2.0;
  initial_grid[1] = -1.0 - 1e-15;
  initial_grid[2] = -1.0;
  initial_grid[3] = 0.0;
  initial_grid[4] = 1.0;
  initial_grid[5] = 1.0 + 1e-15;
  initial_grid[6] = 2.0;

  generator.resetFunction( function );

  std::list<double> linearized_grid_list, evaluated_function_list;

  generator.generateAndEvaluate( linearized_grid_list, 
				 evaluated_function_list,
				 initial_grid, 
				 0.001, 
				 1e-12, 
				 1e-14 );

  TEST_ASSERT( Utility::Sort::isSortedAscending( linearized_grid_list.begin(),
						 linearized_grid_list.end() ));
  TEST_EQUALITY_CONST( linearized_grid_list.size(), 69 );
  TEST_EQUALITY_CONST( evaluated_function_list.size(), 69 );
}

//---------------------------------------------------------------------------//
// Check that a linearized grid can be generated for the functions
TEUCHOS_UNIT_TEST( LinearGridGenerator, generateInPlace )
{
  // Create a linearized grid for x^2
  boost::function<double (double x)> function = &x2;

  Utility::LinearGridGenerator generator( function );
  
  Teuchos::Array<double> initial_grid( 2 );
  initial_grid[0] = 0.0;
  initial_grid[1] = 10.0;

  Teuchos::Array<double> linearized_grid = initial_grid;
  
  generator.generateInPlace( linearized_grid, 0.001, 1e-12 );

  TEST_ASSERT( Utility::Sort::isSortedAscending( linearized_grid.begin(),
						 linearized_grid.end() ) );
  TEST_EQUALITY_CONST( linearized_grid.size(), 321 );
  
  linearized_grid = initial_grid;
  
  // Create a linearized grid for cos(x)
  function = &cos;

  generator.resetFunction( function );

  generator.generateInPlace( linearized_grid, 0.001, 1e-12 );

  TEST_ASSERT( Utility::Sort::isSortedAscending( linearized_grid.begin(),
						 linearized_grid.end() ) );
  TEST_EQUALITY_CONST( linearized_grid.size(), 129 );

  linearized_grid = initial_grid;

  // Create a linearized grid for (x-2)^3
  x3 x_cubed( 2 );
  function = boost::bind<double>(x_cubed, _1);

  generator.resetFunction( function );
  
  generator.generateInPlace( linearized_grid, 0.001, 1e-12 );
  
  TEST_ASSERT( Utility::Sort::isSortedAscending( linearized_grid.begin(),
						 linearized_grid.end() ) );
  TEST_EQUALITY_CONST( linearized_grid.size(), 708 );

  // Create a linearized grid for x*cos(x) in [-1, 1]
  xcosxAB x_cos_x( -1, 1 );
  function = boost::bind<double>(x_cos_x, _1);

  initial_grid.resize( 7 );
  initial_grid[0] = -2.0;
  initial_grid[1] = -1.0 - 1e-15;
  initial_grid[2] = -1.0;
  initial_grid[3] = 0.0;
  initial_grid[4] = 1.0;
  initial_grid[5] = 1.0 + 1e-15;
  initial_grid[6] = 2.0;

  linearized_grid = initial_grid;

  generator.resetFunction( function );

  generator.generateInPlace( linearized_grid, 0.001, 1e-12, 1e-14 );

  TEST_ASSERT( Utility::Sort::isSortedAscending( linearized_grid.begin(),
						 linearized_grid.end() ) );
  TEST_EQUALITY_CONST( linearized_grid.size(), 69 );
}

//---------------------------------------------------------------------------//
// Check that a linearized grid can be generated for the functions
TEUCHOS_UNIT_TEST( LinearGridGenerator, generateAndEvaluateInPlace )
{
  // Create a linearized grid for x^2
  boost::function<double (double x)> function = &x2;

  Utility::LinearGridGenerator generator( function );
  
  Teuchos::Array<double> initial_grid( 2 );
  initial_grid[0] = 0.0;
  initial_grid[1] = 10.0;

  Teuchos::Array<double> linearized_grid = initial_grid, evaluated_function;
  
  generator.generateAndEvaluateInPlace( linearized_grid, 
					evaluated_function,
					0.001, 
					1e-12 );

  TEST_ASSERT( Utility::Sort::isSortedAscending( linearized_grid.begin(),
						 linearized_grid.end() ) );
  TEST_EQUALITY_CONST( linearized_grid.size(), 321 );
  TEST_EQUALITY_CONST( evaluated_function.size(), 321 );
  
  linearized_grid = initial_grid;
  evaluated_function.clear();
  
  // Create a linearized grid for cos(x)
  function = &cos;

  generator.resetFunction( function );

  generator.generateAndEvaluateInPlace( linearized_grid, 
					evaluated_function,
					0.001, 
					1e-12 );

  TEST_ASSERT( Utility::Sort::isSortedAscending( linearized_grid.begin(),
						 linearized_grid.end() ) );
  TEST_EQUALITY_CONST( linearized_grid.size(), 129 );
  TEST_EQUALITY_CONST( evaluated_function.size(), 129 );

  linearized_grid = initial_grid;
  evaluated_function.clear();

  // Create a linearized grid for (x-2)^3
  x3 x_cubed( 2 );
  function = boost::bind<double>(x_cubed, _1);

  generator.resetFunction( function );
  
  generator.generateAndEvaluateInPlace( linearized_grid, 
					evaluated_function,
					0.001, 
					1e-12 );
  
  TEST_ASSERT( Utility::Sort::isSortedAscending( linearized_grid.begin(),
						 linearized_grid.end() ) );
  TEST_EQUALITY_CONST( linearized_grid.size(), 708 );
  TEST_EQUALITY_CONST( evaluated_function.size(), 708 );

  // Create a linearized grid for x*cos(x) in [-1, 1]
  xcosxAB x_cos_x( -1, 1 );
  function = boost::bind<double>(x_cos_x, _1);

  initial_grid.resize( 7 );
  initial_grid[0] = -2.0;
  initial_grid[1] = -1.0 - 1e-15;
  initial_grid[2] = -1.0;
  initial_grid[3] = 0.0;
  initial_grid[4] = 1.0;
  initial_grid[5] = 1.0 + 1e-15;
  initial_grid[6] = 2.0;

  linearized_grid = initial_grid;
  evaluated_function.clear();

  generator.resetFunction( function );

  generator.generateAndEvaluateInPlace( linearized_grid, 
					evaluated_function,
					0.001, 
					1e-12, 
					1e-14 );

  TEST_ASSERT( Utility::Sort::isSortedAscending( linearized_grid.begin(),
						 linearized_grid.end() ) );
  TEST_EQUALITY_CONST( linearized_grid.size(), 69 );
  TEST_EQUALITY_CONST( evaluated_function.size(), 69 );
}

//---------------------------------------------------------------------------//
// end tstLinearGridGenerator.cpp
//---------------------------------------------------------------------------//
