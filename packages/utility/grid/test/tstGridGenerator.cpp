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

// Boost Includes
#include <boost/bind.hpp>

// FRENSIE Includes
#include "Utility_GridGenerator.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_List.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

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
// Check if exceptions/warnings on dirty convergence can be set
FRENSIE_UNIT_TEST( GridGenerator, dirty_convergence_handling )
{
  Utility::GridGenerator<Utility::LinLin> generator;

  FRENSIE_CHECK( !generator.isExceptionThrownOnDirtyConvergence() );

  generator.throwExceptionOnDirtyConvergence();

  FRENSIE_CHECK( generator.isExceptionThrownOnDirtyConvergence() );

  generator.warnOnDirtyConvergence();

  FRENSIE_CHECK( !generator.isExceptionThrownOnDirtyConvergence() );
}

//---------------------------------------------------------------------------//
// Check that the convergence tolerance can be set
FRENSIE_UNIT_TEST( GridGenerator, setConvergenceTolerance )
{
  Utility::GridGenerator<Utility::LinLin> generator;

  FRENSIE_CHECK_EQUAL( generator.getConvergenceTolerance(), 0.001 );

  generator.setConvergenceTolerance( 0.0001 );

  FRENSIE_CHECK_EQUAL( generator.getConvergenceTolerance(), 0.0001 );
}

//---------------------------------------------------------------------------//
// Check that the absolute difference tolerance can be set
FRENSIE_UNIT_TEST( GridGenerator, setAbsoluteDifferenceTolerance )
{
  Utility::GridGenerator<Utility::LinLin> generator;

  FRENSIE_CHECK_EQUAL( generator.getAbsoluteDifferenceTolerance(), 1e-12 );

  generator.setAbsoluteDifferenceTolerance( 1e-14 );

  FRENSIE_CHECK_EQUAL( generator.getAbsoluteDifferenceTolerance(), 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the distance tolerance can be set
FRENSIE_UNIT_TEST( GridGenerator, setDistanceTolerance )
{
  Utility::GridGenerator<Utility::LinLin> generator;

  FRENSIE_CHECK_EQUAL( generator.getDistanceTolerance(), 1e-14 );

  generator.setDistanceTolerance( 1e-16 );

  FRENSIE_CHECK_EQUAL( generator.getDistanceTolerance(), 1e-16 );
}

//---------------------------------------------------------------------------//
// Check that a grid can be generated for the functions
FRENSIE_UNIT_TEST( GridGenerator, generate )
{
  // Create the different grid generators
  Utility::GridGenerator<Utility::LinLin> linlin_generator( 0.001, 1e-12 );
  Utility::GridGenerator<Utility::LogLin> loglin_generator( 0.001, 1e-12 );
  Utility::GridGenerator<Utility::LinLog> linlog_generator( 0.001, 1e-12 );
  Utility::GridGenerator<Utility::LogLog> loglog_generator( 0.001, 1e-12 );

  // Create the initial grid
  std::vector<double> initial_grid( 2 );
  initial_grid[0] = 0.0;
  initial_grid[1] = 10.0;

  // Create a lin-lin grid for x^2
  boost::function<double (double x)> function = &x2;

  std::vector<double> grid;

  linlin_generator.generate( grid, initial_grid, function );

  FRENSIE_CHECK( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  FRENSIE_CHECK_EQUAL( grid.size(), 321 );

  grid.clear();

  // Create a log-lin grid for x^2
  initial_grid[0] = 1e-3;
  loglin_generator.generate( grid, initial_grid, function );

  FRENSIE_CHECK( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  FRENSIE_CHECK_EQUAL( grid.size(), 214 );

  // Create a lin-lin grid for cos(x)
  function = static_cast<double(*)(double)>(&std::cos);

  linlin_generator.generate( grid, initial_grid, function );

  FRENSIE_CHECK( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  FRENSIE_CHECK_EQUAL( grid.size(), 129 );

  grid.clear();

  // Create a lin-lin grid for (x-2)^3
  initial_grid[0] = 0.0;
  x3 x_cubed( 2 );
  function = boost::bind<double>(x_cubed, _1);

  linlin_generator.generate( grid, initial_grid, function );

  FRENSIE_CHECK( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  FRENSIE_CHECK_EQUAL( grid.size(), 708 );

  grid.clear();

  // Create a log-lin grid for (x-2)^3
  initial_grid[0] = 2.0 + 1e-6;

  loglin_generator.generate( grid, initial_grid, function );

  FRENSIE_CHECK( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  FRENSIE_CHECK_EQUAL( grid.size(), 266 );

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

  FRENSIE_CHECK( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  FRENSIE_CHECK_EQUAL( grid.size(), 69 );
}

//---------------------------------------------------------------------------//
// Check that a grid can be generated for the functions
FRENSIE_UNIT_TEST( GridGenerator, generateAndEvaluate )
{
  // Create the different grid generators
  Utility::GridGenerator<Utility::LinLin> linlin_generator( 0.001, 1e-12 );
  Utility::GridGenerator<Utility::LogLin> loglin_generator( 0.001, 1e-12 );
  Utility::GridGenerator<Utility::LinLog> linlog_generator( 0.001, 1e-12 );
  Utility::GridGenerator<Utility::LogLog> loglog_generator( 0.001, 1e-12 );

  // Create the initial grid
  std::vector<double> initial_grid( 2 );
  initial_grid[0] = 0.0;
  initial_grid[1] = 10.0;

  // Create a lin-lin grid for x^2
  boost::function<double (double x)> function = &x2;

  std::vector<double> grid, evaluated_function;

  linlin_generator.generateAndEvaluate( grid,
					evaluated_function,
					initial_grid,
					function );

  FRENSIE_CHECK( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  FRENSIE_CHECK_EQUAL( grid.size(), 321 );
  FRENSIE_CHECK_EQUAL( evaluated_function.size(), 321 );

  grid.clear();
  evaluated_function.clear();

  // Create a log-lin grid for x^2
  initial_grid[0] = 1e-3;

  loglin_generator.generateAndEvaluate( grid,
					evaluated_function,
					initial_grid,
					function );

  FRENSIE_CHECK( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  FRENSIE_CHECK_EQUAL( grid.size(), 214 );
  FRENSIE_CHECK_EQUAL( evaluated_function.size(), 214 );

  // Create a lin-lin grid for cos(x)
  initial_grid[0] = 0.0;
  function = static_cast<double(*)(double)>(&std::cos);

  linlin_generator.generateAndEvaluate( grid,
					evaluated_function,
					initial_grid,
					function );

  FRENSIE_CHECK( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  FRENSIE_CHECK_EQUAL( grid.size(), 129 );
  FRENSIE_CHECK_EQUAL( evaluated_function.size(), 129 );

  grid.clear();
  evaluated_function.clear();

  // Create a lin-lin grid for (x-2)^3
  x3 x_cubed( 2 );
  function = boost::bind<double>(x_cubed, _1);

  linlin_generator.generateAndEvaluate( grid,
					evaluated_function,
					initial_grid,
					function );

  FRENSIE_CHECK( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  FRENSIE_CHECK_EQUAL( grid.size(), 708 );
  FRENSIE_CHECK_EQUAL( evaluated_function.size(), 708 );

  // Create a log-lin grid for (x-2)^3
  initial_grid[0] = 2.0 + 1e-6;

  loglin_generator.generateAndEvaluate( grid,
					evaluated_function,
					initial_grid,
					function );

  FRENSIE_CHECK( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  FRENSIE_CHECK_EQUAL( grid.size(), 266 );

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

  FRENSIE_CHECK( Utility::Sort::isSortedAscending( grid_list.begin(),
						 grid_list.end() ));
  FRENSIE_CHECK_EQUAL( grid_list.size(), 69 );
  FRENSIE_CHECK_EQUAL( evaluated_function_list.size(), 69 );
}

//---------------------------------------------------------------------------//
// Check that a grid can be generated for the functions
FRENSIE_UNIT_TEST( GridGenerator, generateInPlace )
{
  // Create the different grid generators
  Utility::GridGenerator<Utility::LinLin> linlin_generator( 0.001, 1e-12 );
  Utility::GridGenerator<Utility::LogLin> loglin_generator( 0.001, 1e-12 );
  Utility::GridGenerator<Utility::LinLog> linlog_generator( 0.001, 1e-12 );
  Utility::GridGenerator<Utility::LogLog> loglog_generator( 0.001, 1e-12 );

  // Create the initial grid
  std::vector<double> initial_grid( 2 );
  initial_grid[0] = 0.0;
  initial_grid[1] = 10.0;

  // Create a lin-lin grid for x^2
  boost::function<double (double x)> function = &x2;

  std::vector<double> grid = initial_grid;

  linlin_generator.generateInPlace( grid, function );

  FRENSIE_CHECK( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  FRENSIE_CHECK_EQUAL( grid.size(), 321 );

  // Create a log-lin grid for x^2
  initial_grid[0] = 1e-3;
  grid = initial_grid;

  loglin_generator.generateInPlace( grid, function );

  FRENSIE_CHECK( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  FRENSIE_CHECK_EQUAL( grid.size(), 214 );


  // Create a lin-lin grid for cos(x)
  function = static_cast<double(*)(double)>(&std::cos);

  initial_grid[0] = 0.0;
  grid = initial_grid;

  linlin_generator.generateInPlace( grid, function );

  FRENSIE_CHECK( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  FRENSIE_CHECK_EQUAL( grid.size(), 129 );

  grid = initial_grid;

  // Create a lin-lin grid for (x-2)^3
  x3 x_cubed( 2 );
  function = boost::bind<double>(x_cubed, _1);

  linlin_generator.generateInPlace( grid, function );

  FRENSIE_CHECK( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  FRENSIE_CHECK_EQUAL( grid.size(), 708 );

  // Create a log-lin grid for (x-2)^3
  initial_grid[0] = 2 + 1e-6;
  grid = initial_grid;

  loglin_generator.generateInPlace( grid, function );

  FRENSIE_CHECK( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  FRENSIE_CHECK_EQUAL( grid.size(), 266 );

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

  FRENSIE_CHECK( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  FRENSIE_CHECK_EQUAL( grid.size(), 69 );
}

//---------------------------------------------------------------------------//
// Check that a grid can be refined for the functions
FRENSIE_UNIT_TEST( GridGenerator, refineInPlace )
{
  // Create the different grid generators
  Utility::GridGenerator<Utility::LinLin> linlin_generator( 0.001, 1e-12 );
  Utility::GridGenerator<Utility::LogLin> loglin_generator( 0.001, 1e-12 );
  Utility::GridGenerator<Utility::LinLog> linlog_generator( 0.001, 1e-12 );
  Utility::GridGenerator<Utility::LogLog> loglog_generator( 0.001, 1e-12 );

  // Create the initial grid
  std::vector<double> initial_grid( 4 );
  initial_grid[0] = -1.0;
  initial_grid[1] = 0.0;
  initial_grid[2] = 10.0;
  initial_grid[3] = 20.0;

  // Create a lin-lin grid for x^2
  boost::function<double (double x)> function = &x2;

  std::vector<double> grid = initial_grid;

  linlin_generator.refineInPlace( grid, function, initial_grid[1], initial_grid[2] );

  FRENSIE_CHECK( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  FRENSIE_CHECK_EQUAL( grid.size(), 323 );

  // Create a log-lin grid for x^2
  initial_grid[0] = 1e-4;
  initial_grid[1] = 1e-3;
  grid = initial_grid;

  loglin_generator.refineInPlace( grid, function, initial_grid[1], initial_grid[2] );

  FRENSIE_CHECK( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  FRENSIE_CHECK_EQUAL( grid.size(), 216 );


  // Create a lin-lin grid for cos(x)
  function = static_cast<double(*)(double)>(&std::cos);

  initial_grid[0] = -1.0;
  initial_grid[1] = 0.0;
  grid = initial_grid;

  linlin_generator.refineInPlace( grid, function, initial_grid[1], initial_grid[2] );

  FRENSIE_CHECK( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  FRENSIE_CHECK_EQUAL( grid.size(), 131 );

  grid = initial_grid;

  // Create a lin-lin grid for (x-2)^3
  x3 x_cubed( 2 );
  function = boost::bind<double>(x_cubed, _1);

  linlin_generator.refineInPlace( grid, function, initial_grid[1], initial_grid[2] );

  FRENSIE_CHECK( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  FRENSIE_CHECK_EQUAL( grid.size(), 710 );

  // Create a log-lin grid for (x-2)^3
  initial_grid[0] = 2;
  initial_grid[1] = 2 + 1e-6;


  grid = initial_grid;

  loglin_generator.refineInPlace( grid, function, initial_grid[1], initial_grid[2] );

  FRENSIE_CHECK( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  FRENSIE_CHECK_EQUAL( grid.size(), 268 );

  // Create a lin-lin grid for x*cos(x) in [-1, 1]
  xcosxAB x_cos_x( -1, 1 );
  function = boost::bind<double>(x_cos_x, _1);

  initial_grid.resize( 9 );
  initial_grid[0] = -3.0;
  initial_grid[1] = -2.0;
  initial_grid[2] = -1.0 - 1e-15;
  initial_grid[3] = -1.0;
  initial_grid[4] = 0.0;
  initial_grid[5] = 1.0;
  initial_grid[6] = 1.0 + 1e-15;
  initial_grid[7] = 2.0;
  initial_grid[8] = 3.0;

  grid = initial_grid;

  linlin_generator.refineInPlace( grid, function, initial_grid[1], initial_grid[7] );

  FRENSIE_CHECK( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  FRENSIE_CHECK_EQUAL( grid.size(), 71 );
}

//---------------------------------------------------------------------------//
// Check that a grid can be generated for the functions
FRENSIE_UNIT_TEST( GridGenerator, generateAndEvaluateInPlace )
{
  // Create the different grid generators
  Utility::GridGenerator<Utility::LinLin> linlin_generator( 0.001, 1e-12 );
  Utility::GridGenerator<Utility::LogLin> loglin_generator( 0.001, 1e-12 );
  Utility::GridGenerator<Utility::LinLog> linlog_generator( 0.001, 1e-12 );
  Utility::GridGenerator<Utility::LogLog> loglog_generator( 0.001, 1e-12 );

  // Create the initial grid
  std::vector<double> initial_grid( 2 );
  initial_grid[0] = 0.0;
  initial_grid[1] = 10.0;

  // Create a lin-lin grid for x^2
  boost::function<double (double x)> function = &x2;

  std::vector<double> grid = initial_grid, evaluated_function;

  linlin_generator.generateAndEvaluateInPlace( grid,
					       evaluated_function,
					       function );

  FRENSIE_CHECK( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  FRENSIE_CHECK_EQUAL( grid.size(), 321 );
  FRENSIE_CHECK_EQUAL( evaluated_function.size(), 321 );

  evaluated_function.clear();

  // Create a log-lin grid for x^2
  initial_grid[0] = 1e-3;
  grid = initial_grid;

  loglin_generator.generateAndEvaluateInPlace( grid,
					       evaluated_function,
					       function );

  FRENSIE_CHECK( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  FRENSIE_CHECK_EQUAL( grid.size(), 214 );
  FRENSIE_CHECK_EQUAL( evaluated_function.size(), 214 );

  evaluated_function.clear();

  // Create a lin-lin grid for cos(x)
  initial_grid[0] = 0.0;
  grid = initial_grid;

  function = static_cast<double(*)(double)>(&std::cos);

  linlin_generator.generateAndEvaluateInPlace( grid,
					       evaluated_function,
					       function );

  FRENSIE_CHECK( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  FRENSIE_CHECK_EQUAL( grid.size(), 129 );
  FRENSIE_CHECK_EQUAL( evaluated_function.size(), 129 );

  grid = initial_grid;
  evaluated_function.clear();

  // Create a lin-lin grid for (x-2)^3
  x3 x_cubed( 2 );
  function = boost::bind<double>(x_cubed, _1);

  linlin_generator.generateAndEvaluateInPlace( grid,
					       evaluated_function,
					       function );

  FRENSIE_CHECK( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  FRENSIE_CHECK_EQUAL( grid.size(), 708 );
  FRENSIE_CHECK_EQUAL( evaluated_function.size(), 708 );

  evaluated_function.clear();

  // Create a log-lin grid for (x-2)^3
  initial_grid[0] = 2.0 + 1e-6;
  grid = initial_grid;

  loglin_generator.generateAndEvaluateInPlace( grid,
					       evaluated_function,
					       function );

  FRENSIE_CHECK( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  FRENSIE_CHECK_EQUAL( grid.size(), 266 );
  FRENSIE_CHECK_EQUAL( evaluated_function.size(), 266 );

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

  FRENSIE_CHECK( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  FRENSIE_CHECK_EQUAL( grid.size(), 69 );
  FRENSIE_CHECK_EQUAL( evaluated_function.size(), 69 );
}

//---------------------------------------------------------------------------//
// Check that a grid can be refined for the functions
FRENSIE_UNIT_TEST( GridGenerator, refineAndEvaluateInPlace )
{
  // Create the different grid generators
  Utility::GridGenerator<Utility::LinLin> linlin_generator( 0.001, 1e-12 );
  Utility::GridGenerator<Utility::LogLin> loglin_generator( 0.001, 1e-12 );
  Utility::GridGenerator<Utility::LinLog> linlog_generator( 0.001, 1e-12 );
  Utility::GridGenerator<Utility::LogLog> loglog_generator( 0.001, 1e-12 );

  // Create the initial grid
  std::vector<double> initial_grid( 4 );
  initial_grid[0] = -1.0;
  initial_grid[1] = 0.0;
  initial_grid[2] = 10.0;
  initial_grid[3] = 20.0;

  // Create a lin-lin grid for x^2
  boost::function<double (double x)> function = &x2;

  std::vector<double> grid = initial_grid, evaluated_function;

  linlin_generator.refineAndEvaluateInPlace(
                        grid,
                        evaluated_function,
                        function,
                        initial_grid[1],
                        initial_grid[2] );

  FRENSIE_CHECK( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  FRENSIE_CHECK_EQUAL( grid.size(), 323 );
  FRENSIE_CHECK_EQUAL( evaluated_function.size(), 323 );
  FRENSIE_CHECK_EQUAL( grid[0], initial_grid[0] );
  FRENSIE_CHECK_EQUAL( grid[1], initial_grid[1] );
  FRENSIE_CHECK( grid[2] > initial_grid[1] );
  FRENSIE_CHECK_EQUAL( grid.back(), initial_grid[3] );
  grid.pop_back();
  FRENSIE_CHECK_EQUAL( grid.back(), initial_grid[2] );
  grid.pop_back();
  FRENSIE_CHECK( grid.back() < initial_grid[2] );

  evaluated_function.clear();

  // Create a log-lin grid for x^2
  initial_grid[0] = 1e-4;
  initial_grid[1] = 1e-3;
  grid = initial_grid;

  loglin_generator.refineAndEvaluateInPlace(
                        grid,
                        evaluated_function,
                        function,
                        initial_grid[1],
                        initial_grid[2] );

  FRENSIE_CHECK( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  FRENSIE_CHECK_EQUAL( grid.size(), 216 );
  FRENSIE_CHECK_EQUAL( evaluated_function.size(), 216 );
  FRENSIE_CHECK_EQUAL( grid[0], initial_grid[0] );
  FRENSIE_CHECK_EQUAL( grid[1], initial_grid[1] );
  FRENSIE_CHECK_EQUAL( grid.back(), initial_grid[3] );
  grid.pop_back();
  FRENSIE_CHECK_EQUAL( grid.back(), initial_grid[2] );

  evaluated_function.clear();

  // Create a lin-lin grid for cos(x)
  initial_grid[0] = -1.0;
  initial_grid[1] = 0.0;
  grid = initial_grid;

  function = static_cast<double(*)(double)>(&std::cos);

  linlin_generator.refineAndEvaluateInPlace(
                        grid,
                        evaluated_function,
                        function,
                        initial_grid[1],
                        initial_grid[2] );

  FRENSIE_CHECK( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  FRENSIE_CHECK_EQUAL( grid.size(), 131 );
  FRENSIE_CHECK_EQUAL( evaluated_function.size(), 131 );
  FRENSIE_CHECK_EQUAL( grid[0], initial_grid[0] );
  FRENSIE_CHECK_EQUAL( grid[1], initial_grid[1] );
  FRENSIE_CHECK_EQUAL( grid.back(), initial_grid[3] );
  grid.pop_back();
  FRENSIE_CHECK_EQUAL( grid.back(), initial_grid[2] );
  grid.pop_back();
  FRENSIE_CHECK( grid.back() < initial_grid[2] );

  grid = initial_grid;
  evaluated_function.clear();

  // Create a lin-lin grid for (x-2)^3
  x3 x_cubed( 2 );
  function = boost::bind<double>(x_cubed, _1);

  linlin_generator.refineAndEvaluateInPlace(
                        grid,
                        evaluated_function,
                        function,
                        initial_grid[1],
                        initial_grid[2] );

  FRENSIE_CHECK( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  FRENSIE_CHECK_EQUAL( grid.size(), 710 );
  FRENSIE_CHECK_EQUAL( evaluated_function.size(), 710 );
  FRENSIE_CHECK_EQUAL( grid[0], initial_grid[0] );
  FRENSIE_CHECK_EQUAL( grid[1], initial_grid[1] );
  FRENSIE_CHECK_EQUAL( grid.back(), initial_grid[3] );
  grid.pop_back();
  FRENSIE_CHECK_EQUAL( grid.back(), initial_grid[2] );

  evaluated_function.clear();

  // Create a log-lin grid for (x-2)^3
  initial_grid[0] = 2.0;
  initial_grid[1] = 2.0 + 1e-6;
  grid = initial_grid;

  loglin_generator.refineAndEvaluateInPlace(
                        grid,
                        evaluated_function,
                        function,
                        initial_grid[1],
                        initial_grid[2] );

  FRENSIE_CHECK( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  FRENSIE_CHECK_EQUAL( grid.size(), 268 );
  FRENSIE_CHECK_EQUAL( evaluated_function.size(), 268 );
  FRENSIE_CHECK_EQUAL( grid[0], initial_grid[0] );
  FRENSIE_CHECK_EQUAL( grid[1], initial_grid[1] );
  FRENSIE_CHECK_EQUAL( grid.back(), initial_grid[3] );
  grid.pop_back();
  FRENSIE_CHECK_EQUAL( grid.back(), initial_grid[2] );

  evaluated_function.clear();

  // Create a lin-lin grid for x*cos(x) in [-1, 1]
  xcosxAB x_cos_x( -1, 1 );
  function = boost::bind<double>(x_cos_x, _1);

  initial_grid.resize( 9 );
  initial_grid[0] = -3.0;
  initial_grid[1] = -2.0;
  initial_grid[2] = -1.0 - 1e-15;
  initial_grid[3] = -1.0;
  initial_grid[4] = 0.0;
  initial_grid[5] = 1.0;
  initial_grid[6] = 1.0 + 1e-15;
  initial_grid[7] = 2.0;
  initial_grid[8] = 3.0;

  grid = initial_grid;
  evaluated_function.clear();

  linlin_generator.refineAndEvaluateInPlace(
                        grid,
                        evaluated_function,
                        function,
                        initial_grid[1],
                        initial_grid[7] );

  FRENSIE_CHECK( Utility::Sort::isSortedAscending( grid.begin(), grid.end() ) );
  FRENSIE_CHECK_EQUAL( grid.size(), 71 );
  FRENSIE_CHECK_EQUAL( evaluated_function.size(), 71 );
  FRENSIE_CHECK_EQUAL( grid[0], initial_grid[0] );
  FRENSIE_CHECK_EQUAL( grid[1], initial_grid[1] );
  FRENSIE_CHECK_EQUAL( grid.back(), initial_grid[8] );
  grid.pop_back();
  FRENSIE_CHECK_EQUAL( grid.back(), initial_grid[7] );
}

//---------------------------------------------------------------------------//
// end tstGridGenerator.cpp
//---------------------------------------------------------------------------//
