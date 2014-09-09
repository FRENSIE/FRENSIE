//---------------------------------------------------------------------------//
//!
//! \file   tstBilinearGridGenerator.cpp
//! \author Alex Robinson
//! \brief  Bilinear grid generator class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/bind.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Utility_BilinearGridGenerator.hpp"
#include "Utility_SortAlgorithms.hpp"

//---------------------------------------------------------------------------//
// Testing Functions
//---------------------------------------------------------------------------//
double x2_plus_y2( const double x, const double y )
{
  return x*x + y*y;
}

struct CosxCosy
{
  CosxCosy( const double x_min,
	    const double x_max,
	    const double y_min,
	    const double y_max )
    : d_x_min( x_min ),
      d_x_max( x_max ),
      d_y_min( y_min ),
      d_y_max( y_max )
  { /* ... */ }

  double operator()( const double x, const double y )
  {
    if( x < d_x_min )
      return 0.0;
    else if( x > d_x_max )
      return 0.0;
    else if( y < d_y_min )
      return 0.0;
    else if( y > d_y_max )
      return 0.0;
    else
      return cos( x )*cos( y );
  }

  double ymin( const double x )
  {
    return d_y_min;
  }

  double ymax( const double x )
  {
    return d_y_max;
  }

private:

  double d_x_min;
  double d_x_max;
  double d_y_min;
  double d_y_max;
};

double default_ymin( const double x )
{
  return 0.0;
}

double default_ymax( const double x )
{
  return 1.0;
}

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a bilinear grid can be generated for the functions
TEUCHOS_UNIT_TEST( BilinearGridGenerator, generate )
{
  // Create a bilinear grid for x^2 + y^2
  boost::function<double (double x, double y)> function = &x2_plus_y2;
  boost::function<double (double x)> ymin_function = default_ymin;
  boost::function<double (double x)> ymax_function = default_ymax;

  Utility::BilinearGridGenerator generator( function, 
					    ymin_function,
					    ymax_function );

  Teuchos::Array<double> initial_x_grid( 2 );
  initial_x_grid[0] = 0.0;
  initial_x_grid[1] = 1.0;

  Teuchos::Array<double> linear_x_grid;
  Teuchos::Array<Teuchos::Array<double> > linear_y_grids;

  generator.generate( linear_x_grid,
		      linear_y_grids,
		      initial_x_grid,
		      0.001,
		      1e-12 );

  TEST_ASSERT( Utility::Sort::isSortedAscending( linear_x_grid.begin(),
						 linear_x_grid.end() ) );
  TEST_ASSERT( Utility::Sort::isSortedAscending(linear_y_grids.front().begin(),
						linear_y_grids.front().end()));
  TEST_ASSERT( Utility::Sort::isSortedAscending(linear_y_grids.back().begin(),
						linear_y_grids.back().end()));
  TEST_EQUALITY_CONST( linear_x_grid.size(), 257 );
  TEST_EQUALITY_CONST( linear_y_grids.size(), 257 );	       
						
  linear_x_grid.clear();
  linear_y_grids.clear();
  
  // Create the bilinear grid for cos(x)*cos(y)
  CosxCosy cosxcosy( -1.0, 1.0, -1.0, 1.0 );
  function = boost::bind<double>(cosxcosy, _1, _2);
  ymin_function = boost::bind<double>(&CosxCosy::ymin, cosxcosy, _1);
  ymax_function = boost::bind<double>(&CosxCosy::ymax, cosxcosy, _1);

  generator.resetFunction( function, ymin_function, ymax_function );

  initial_x_grid.resize( 6 );
  initial_x_grid[0] = -2.0;
  initial_x_grid[1] = -1.0 - 1e-15;
  initial_x_grid[2] = -1.0;
  initial_x_grid[3] = 1.0;
  initial_x_grid[4] = 1.0 + 1e-15;
  initial_x_grid[5] = 2.0;

  generator.generate( linear_x_grid,
		      linear_y_grids,
		      initial_x_grid,
		      0.001,
		      1e-12,
		      1e-14 );  

  TEST_ASSERT( Utility::Sort::isSortedAscending( linear_x_grid.begin(),
						 linear_x_grid.end() ) );
  TEST_ASSERT( Utility::Sort::isSortedAscending(linear_y_grids.front().begin(),
						linear_y_grids.front().end()));
  TEST_ASSERT( Utility::Sort::isSortedAscending(linear_y_grids.back().begin(),
						linear_y_grids.back().end()));
  TEST_EQUALITY_CONST( linear_x_grid.size(), 37 );
  TEST_EQUALITY_CONST( linear_y_grids.size(), 37 );	       
						
  linear_x_grid.clear();
  linear_y_grids.clear();
}

//---------------------------------------------------------------------------//
// end tstBilinearGridGenerator.cpp
//---------------------------------------------------------------------------//
