//---------------------------------------------------------------------------//
//!
//! \file   tstGridGenerator.cpp
//! \author Alex Robinson
//! \brief  Grid generator class unit tests
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
#include "Utility_GridGenerator.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_InterpolationPolicy.hpp"

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
// Check that a grid can be generated for the functions
TEUCHOS_UNIT_TEST( GridGenerator, generate )
{
  // Create the different grid generators
  Utility::GridGenerator<Utility::LinLin> linlin_generator( 0.001, 1e-12 );
  Utility::GridGenerator<Utility::LogLin> loglin_generator( 0.001, 1e-12 );
  Utility::GridGenerator<Utility::LinLog> linlog_generator( 0.001, 1e-12 );
  Utility::GridGenerator<Utility::LogLog> loglog_generator( 0.001, 1e-12 );

  // Create the initial grid
  Teuchos::Array<double> initial_grid( 2 );
  initial_grid[0] = 0.0;
  initial_grid[1] = 10.0;
  
  // Create a lin-lin grid for x^2
  boost::function<double (double x)> function = &x2;

  Teuchos::Array<double> grid;
  
  linlin_generator.generate( grid, initial_grid, function );

  TEST_ASSERT( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  TEST_EQUALITY_CONST( grid.size(), 321 );
  
  grid.clear();

  // Create a log-lin grid for x^2
  initial_grid[0] = 1e-3;
  loglin_generator.generate( grid, initial_grid, function );

  TEST_ASSERT( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  TEST_EQUALITY_CONST( grid.size(), 214 );
  
  // Create a lin-lin grid for cos(x)
  function = &cos;

  linlin_generator.generate( grid, initial_grid, function );

  TEST_ASSERT( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  TEST_EQUALITY_CONST( grid.size(), 129 );

  grid.clear();

  // Create a lin-lin grid for (x-2)^3
  initial_grid[0] = 0.0;
  x3 x_cubed( 2 );
  function = boost::bind<double>(x_cubed, _1);

  linlin_generator.generate( grid, initial_grid, function );
  
  TEST_ASSERT( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  TEST_EQUALITY_CONST( grid.size(), 708 );

  grid.clear();

  // Create a log-lin grid for (x-2)^3
  initial_grid[0] = 2.0 + 1e-6;

  loglin_generator.generate( grid, initial_grid, function );

  TEST_ASSERT( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  TEST_EQUALITY_CONST( grid.size(), 266 );

  // Create a lin-lin grid for x*cos(x) in [-1, 1]
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

  linlin_generator.generate( grid, initial_grid, function );

  TEST_ASSERT( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  TEST_EQUALITY_CONST( grid.size(), 69 );
}

//---------------------------------------------------------------------------//
// Check that a grid can be generated for the functions
TEUCHOS_UNIT_TEST( GridGenerator, generateAndEvaluate )
{
  // Create the different grid generators
  Utility::GridGenerator<Utility::LinLin> linlin_generator( 0.001, 1e-12 );
  Utility::GridGenerator<Utility::LogLin> loglin_generator( 0.001, 1e-12 );
  Utility::GridGenerator<Utility::LinLog> linlog_generator( 0.001, 1e-12 );
  Utility::GridGenerator<Utility::LogLog> loglog_generator( 0.001, 1e-12 );
  
  // Create the initial grid
  Teuchos::Array<double> initial_grid( 2 );
  initial_grid[0] = 0.0;
  initial_grid[1] = 10.0;

  // Create a lin-lin grid for x^2
  boost::function<double (double x)> function = &x2;

  Teuchos::Array<double> grid, evaluated_function;
  
  linlin_generator.generateAndEvaluate( grid, 
					evaluated_function,
					initial_grid, 
					function );

  TEST_ASSERT( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  TEST_EQUALITY_CONST( grid.size(), 321 );
  TEST_EQUALITY_CONST( evaluated_function.size(), 321 );

  grid.clear();
  evaluated_function.clear();

  // Create a log-lin grid for x^2
  initial_grid[0] = 1e-3;

  loglin_generator.generateAndEvaluate( grid, 
					evaluated_function,
					initial_grid, 
					function );

  TEST_ASSERT( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  TEST_EQUALITY_CONST( grid.size(), 214 );
  TEST_EQUALITY_CONST( evaluated_function.size(), 214 );

  // Create a lin-lin grid for cos(x)
  initial_grid[0] = 0.0;
  function = &cos;

  linlin_generator.generateAndEvaluate( grid, 
					evaluated_function,
					initial_grid, 
					function );

  TEST_ASSERT( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  TEST_EQUALITY_CONST( grid.size(), 129 );
  TEST_EQUALITY_CONST( evaluated_function.size(), 129 );

  grid.clear();
  evaluated_function.clear();

  // Create a lin-lin grid for (x-2)^3
  x3 x_cubed( 2 );
  function = boost::bind<double>(x_cubed, _1);

  linlin_generator.generateAndEvaluate( grid, 
					evaluated_function,
					initial_grid, 
					function );
  
  TEST_ASSERT( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  TEST_EQUALITY_CONST( grid.size(), 708 );
  TEST_EQUALITY_CONST( evaluated_function.size(), 708 );

  // Create a log-lin grid for (x-2)^3
  initial_grid[0] = 2.0 + 1e-6;

  loglin_generator.generateAndEvaluate( grid, 
					evaluated_function,
					initial_grid, 
					function );

  TEST_ASSERT( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  TEST_EQUALITY_CONST( grid.size(), 266 );

  // Create a lin-lin grid for x*cos(x) in [-1, 1]
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

  std::list<double> grid_list, evaluated_function_list;

  linlin_generator.generateAndEvaluate( grid_list, 
					evaluated_function_list,
					initial_grid,
					function );

  TEST_ASSERT( Utility::Sort::isSortedAscending( grid_list.begin(),
						 grid_list.end() ));
  TEST_EQUALITY_CONST( grid_list.size(), 69 );
  TEST_EQUALITY_CONST( evaluated_function_list.size(), 69 );
}

//---------------------------------------------------------------------------//
// Check that a grid can be generated for the functions
TEUCHOS_UNIT_TEST( GridGenerator, generateInPlace )
{
  // Create the different grid generators
  Utility::GridGenerator<Utility::LinLin> linlin_generator( 0.001, 1e-12 );
  Utility::GridGenerator<Utility::LogLin> loglin_generator( 0.001, 1e-12 );
  Utility::GridGenerator<Utility::LinLog> linlog_generator( 0.001, 1e-12 );
  Utility::GridGenerator<Utility::LogLog> loglog_generator( 0.001, 1e-12 );
  
  // Create the initial grid
  Teuchos::Array<double> initial_grid( 2 );
  initial_grid[0] = 0.0;
  initial_grid[1] = 10.0;
  
  // Create a lin-lin grid for x^2
  boost::function<double (double x)> function = &x2;

  Teuchos::Array<double> grid = initial_grid;
  
  linlin_generator.generateInPlace( grid, function );

  TEST_ASSERT( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  TEST_EQUALITY_CONST( grid.size(), 321 );
  
  // Create a log-lin grid for x^2
  initial_grid[0] = 1e-3;
  grid = initial_grid;

  loglin_generator.generateInPlace( grid, function );

  TEST_ASSERT( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  TEST_EQUALITY_CONST( grid.size(), 214 );
  
  
  // Create a lin-lin grid for cos(x)
  function = &cos;
  
  initial_grid[0] = 0.0;
  grid = initial_grid;
  
  linlin_generator.generateInPlace( grid, function );

  TEST_ASSERT( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  TEST_EQUALITY_CONST( grid.size(), 129 );

  grid = initial_grid;

  // Create a lin-lin grid for (x-2)^3
  x3 x_cubed( 2 );
  function = boost::bind<double>(x_cubed, _1);

  linlin_generator.generateInPlace( grid, function );
  
  TEST_ASSERT( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  TEST_EQUALITY_CONST( grid.size(), 708 );

  // Create a log-lin grid for (x-2)^3
  initial_grid[0] = 2 + 1e-6;
  grid = initial_grid;
  
  loglin_generator.generateInPlace( grid, function );
  
  TEST_ASSERT( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  TEST_EQUALITY_CONST( grid.size(), 266 );

  // Create a lin-lin grid for x*cos(x) in [-1, 1]
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

  grid = initial_grid;

  linlin_generator.generateInPlace( grid, function );

  TEST_ASSERT( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  TEST_EQUALITY_CONST( grid.size(), 69 );
}

//---------------------------------------------------------------------------//
// Check that a grid can be generated for the functions
TEUCHOS_UNIT_TEST( GridGenerator, generateAndEvaluateInPlace )
{
  // Create the different grid generators
  Utility::GridGenerator<Utility::LinLin> linlin_generator( 0.001, 1e-12 );
  Utility::GridGenerator<Utility::LogLin> loglin_generator( 0.001, 1e-12 );
  Utility::GridGenerator<Utility::LinLog> linlog_generator( 0.001, 1e-12 );
  Utility::GridGenerator<Utility::LogLog> loglog_generator( 0.001, 1e-12 );
  
  // Create the initial grid
  Teuchos::Array<double> initial_grid( 2 );
  initial_grid[0] = 0.0;
  initial_grid[1] = 10.0;
  
  // Create a lin-lin grid for x^2
  boost::function<double (double x)> function = &x2;

  Teuchos::Array<double> grid = initial_grid, evaluated_function;
  
  linlin_generator.generateAndEvaluateInPlace( grid, 
					       evaluated_function,
					       function );

  TEST_ASSERT( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  TEST_EQUALITY_CONST( grid.size(), 321 );
  TEST_EQUALITY_CONST( evaluated_function.size(), 321 );
  
  evaluated_function.clear();

  // Create a log-lin grid for x^2
  initial_grid[0] = 1e-3;
  grid = initial_grid;

  loglin_generator.generateAndEvaluateInPlace( grid, 
					       evaluated_function,
					       function );
  
  TEST_ASSERT( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  TEST_EQUALITY_CONST( grid.size(), 214 );
  TEST_EQUALITY_CONST( evaluated_function.size(), 214 );
  
  evaluated_function.clear();
  
  // Create a lin-lin grid for cos(x)
  initial_grid[0] = 0.0;
  grid = initial_grid;
  
  function = &cos;

  linlin_generator.generateAndEvaluateInPlace( grid, 
					       evaluated_function,
					       function );

  TEST_ASSERT( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  TEST_EQUALITY_CONST( grid.size(), 129 );
  TEST_EQUALITY_CONST( evaluated_function.size(), 129 );

  grid = initial_grid;
  evaluated_function.clear();

  // Create a lin-lin grid for (x-2)^3
  x3 x_cubed( 2 );
  function = boost::bind<double>(x_cubed, _1);

  linlin_generator.generateAndEvaluateInPlace( grid, 
					       evaluated_function,
					       function );
  
  TEST_ASSERT( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  TEST_EQUALITY_CONST( grid.size(), 708 );
  TEST_EQUALITY_CONST( evaluated_function.size(), 708 );

  evaluated_function.clear();

  // Create a log-lin grid for (x-2)^3
  initial_grid[0] = 2.0 + 1e-6;
  grid = initial_grid;
  
  loglin_generator.generateAndEvaluateInPlace( grid, 
					       evaluated_function,
					       function );

  TEST_ASSERT( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  TEST_EQUALITY_CONST( grid.size(), 266 );
  TEST_EQUALITY_CONST( evaluated_function.size(), 266 );

  evaluated_function.clear();

  // Create a lin-lin grid for x*cos(x) in [-1, 1]
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

  grid = initial_grid;
  evaluated_function.clear();
  
  linlin_generator.generateAndEvaluateInPlace( grid, 
					       evaluated_function,
					       function );

  TEST_ASSERT( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  TEST_EQUALITY_CONST( grid.size(), 69 );
  TEST_EQUALITY_CONST( evaluated_function.size(), 69 );
}

//---------------------------------------------------------------------------//
// end tstGridGenerator.cpp
//---------------------------------------------------------------------------//
