//---------------------------------------------------------------------------//
//!
//! \file   Utility_BilinearGridGenerator.cpp
//! \author Alex Robinson
//! \brief  Bilinear grid generator class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <deque>
#include <algorithm>

// Boost Includes
#include <boost/bind.hpp>

// FRENSIE Includes
#include "Utility_BilinearGridGenerator.hpp"
#include "Utility_LinearGridGenerator.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_ComparePolicy.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Constructor
BilinearGridGenerator::BilinearGridGenerator(
		const boost::function<double (double x, double y)>& function,
		const boost::function<double (double x)>& lower_ylim_function,
		const boost::function<double (double x)>& upper_ylim_function )
  : d_function( function ),
    d_lower_ylim_function( lower_ylim_function ),
    d_upper_ylim_function( upper_ylim_function )
{
  // Make sure the function wrappers are not empty
  testPrecondition( !function.empty() );
  testPrecondition( !lower_ylim_function.empty() );
  testPrecondition( !upper_ylim_function.empty() );
}

// Reset the function
void BilinearGridGenerator::resetFunction(
		const boost::function<double (double x, double y)>& function,
		const boost::function<double (double x)>& lower_ylim_function,
		const boost::function<double (double x)>& upper_ylim_function )
{
  // Make sure the function wrappers are not empty
  testPrecondition( !function.empty() );
  testPrecondition( !lower_ylim_function.empty() );
  testPrecondition( !upper_ylim_function.empty() );

  d_function = function;
  d_lower_ylim_function = lower_ylim_function;
  d_upper_ylim_function = upper_ylim_function;
}

// Generate the bilinear grid
void BilinearGridGenerator::generate(
		       Teuchos::Array<double>& linear_x_grid,
		       Teuchos::Array<Teuchos::Array<double> >& linear_y_grids,
		       const Teuchos::Array<double>& initial_x_grid,
		       const double convergence_tol,
		       const double absolute_diff_tol,
		       const double distance_tol ) const
{
  // Make sure at least 2 initial x grid points have been given
  testPrecondition( initial_x_grid.size() >= 2 );
  // Make sure the initial x grid points are sorted
  testPrecondition( Sort::isSortedAscending( initial_x_grid.begin(),
					     initial_x_grid.end() ) );
  // Make sure the convergence tolerance is valid
  testPrecondition( convergence_tol <= 1.0 );
  testPrecondition( convergence_tol > 0.0 );
  // Make sure the absolute difference tolerance is valid
  testPrecondition( absolute_diff_tol <= 1.0 );
  testPrecondition( absolute_diff_tol >= 0.0 );
  // Make sure the distance tolerance is valid
  testPrecondition( distance_tol <= 1.0 );
  testPrecondition( distance_tol >= 0.0 );

  // Clear the linear grid
  linear_x_grid.clear();
  linear_y_grids.clear();

  // Use a queue data structure to calculate the x grid points
  std::deque<double> x_grid_queue( initial_x_grid.begin(), 
				   initial_x_grid.end() );
  
  // Calculate the x grid points
  while( x_grid_queue.size() > 1 )
  {
    double x0 = x_grid_queue.front();

    x_grid_queue.pop_front();

    // Generate the y-grid at x0
    boost::function<double (double y)> x0_function = 
      boost::bind(d_function, x0, _1);
    
    Teuchos::Array<double> x0_y_grid, x0_initial_y_grid( 2 );
    x0_initial_y_grid[0] = d_lower_ylim_function( x0 );
    x0_initial_y_grid[1] = d_upper_ylim_function( x0 );
    
    LinearGridGenerator x0_y_grid_generator( x0_function );
    x0_y_grid_generator.generate( x0_y_grid,
				  x0_initial_y_grid,
				  convergence_tol,
				  absolute_diff_tol,
				  distance_tol );
    
    double x1 = x_grid_queue.front();

    double relative_distance = 
      Utility::Policy::relError( x0, x1 );

    if( relative_distance > distance_tol )
    {
      double x_mid = 0.5*(x0 + x1);
      
      // Generate the y-grid at x_mid
      boost::function<double (double y)> x_mid_function =
	boost::bind(d_function, x_mid, _1 );
      
      Teuchos::Array<double> x_mid_y_grid, x_mid_initial_y_grid( 2 );
      x_mid_initial_y_grid[0] = d_lower_ylim_function( x_mid );
      x_mid_initial_y_grid[1] = d_upper_ylim_function( x_mid );
      
      LinearGridGenerator x_mid_y_grid_generator( x_mid_function );
      x_mid_y_grid_generator.generate( x_mid_y_grid,
				       x_mid_initial_y_grid,
				       convergence_tol,
				       absolute_diff_tol,
				       distance_tol );
      
      // Generate the y-grid at x1
      boost::function<double (double y)> x1_function = 
	boost::bind(d_function, x1, _1);
      
      Teuchos::Array<double> x1_y_grid, x1_initial_y_grid( 2 );
      x1_initial_y_grid[0] = d_lower_ylim_function( x1 );
      x1_initial_y_grid[1] = d_upper_ylim_function( x1 );
      
      LinearGridGenerator x1_y_grid_generator( x1_function );
      x1_y_grid_generator.generate( x1_y_grid,
				    x1_initial_y_grid,
				    convergence_tol,
				    absolute_diff_tol,
				    distance_tol );

      bool converged = hasXGridConverged( x0, 
					  x_mid, 
					  x1, 
					  x0_y_grid,
					  x_mid_y_grid,
					  x1_y_grid,
					  convergence_tol,
					  absolute_diff_tol );
      // Refine the grid
      if( !converged )
      {
	x_grid_queue.push_front( x_mid );
	x_grid_queue.push_front( x0 );
      }
      // Keep the grid points
      else
      {
	linear_x_grid.push_back( x0 );
	linear_y_grids.push_back( x0_y_grid );
      }
    }
    // Keep the grid points (distance tolerance satisified)
    else
    {
      linear_x_grid.push_back( x0 );
      linear_y_grids.push_back( x0_y_grid );
    }

    x0_y_grid.clear();
    x0_initial_y_grid.clear();
  }

  // Add the last x point to the grid
  linear_x_grid.push_back( x_grid_queue.front() );

  // Generate the grid at the last x point
  boost::function<double (double y)> x1_function = 
    boost::bind(d_function, x_grid_queue.front(), _1);
  
  Teuchos::Array<double> x1_y_grid, x1_initial_y_grid( 2 );
  x1_initial_y_grid[0] = d_lower_ylim_function( x_grid_queue.front() );
  x1_initial_y_grid[1] = d_upper_ylim_function( x_grid_queue.front() );
  
  LinearGridGenerator x1_y_grid_generator( x1_function );
  x1_y_grid_generator.generate( x1_y_grid,
				x1_initial_y_grid,
				convergence_tol,
				absolute_diff_tol,
				distance_tol );
  
  // Add the last y grid to the y grids
  linear_y_grids.push_back( x1_y_grid );

  // Make sure grid has at least 2 x points
  testPostcondition( linear_x_grid.size() >= 2 );
  // Make sure the linearized grid is sorted
  testPostcondition( Sort::isSortedAscending( linear_x_grid.begin(),
					      linear_x_grid.end() ) );
  // Make sure each x grid point has a y grid
  testPostcondition( linear_x_grid.size() == linear_y_grids.size() );	   
}

// Test if x grid has converged
bool BilinearGridGenerator::hasXGridConverged(
				    const double x0, 
				    const double x_mid,
				    const double x1,
				    const Teuchos::Array<double>& x0_y_grid,
				    const Teuchos::Array<double>& x_mid_y_grid,
				    const Teuchos::Array<double>& x1_y_grid,
				    const double convergence_tol,
				    const double absolute_diff_tol ) const
{
  // Calculate the length of each y grid
  double L0 = x0_y_grid.back() - x0_y_grid.front();
  double L1 = x1_y_grid.back() - x1_y_grid.front();
  double Lx = x_mid_y_grid.back() - x_mid_y_grid.front();

  double alpha = (x_mid - x0)/(x1 - x0);

  double converged = true;

  // Loop through all of the x_mid grid points
  for( unsigned i = 0; i < x_mid_y_grid.size(); ++i )
  {
    double f_xy_exact = d_function( x_mid, x_mid_y_grid[i] );
    double f_x0y_estimated = 
      calculateInterpolatedFunctionOnYGrid( x0, x_mid_y_grid[i], x0_y_grid );
    double f_x1y_estimated = 
      calculateInterpolatedFunctionOnYGrid( x1, x_mid_y_grid[i], x1_y_grid );

    // Use unit-base interpolate to calculate the interpolated function value
    double f_xy_estimated = 
      ((1-alpha)*L0*f_x0y_estimated + alpha*L1*f_x1y_estimated)/Lx;

    double relative_error = 
      Utility::Policy::relError( f_xy_exact, f_xy_estimated );

    double abs_diff = 
      Teuchos::ScalarTraits<double>::magnitude( f_xy_exact - f_xy_estimated );

    if( relative_error > convergence_tol && abs_diff > absolute_diff_tol )
    {
      converged = false;
      break;
    }
  }

  return converged;
}

// Use lin-lin interpolation to find f(x,y) on y grid
double BilinearGridGenerator::calculateInterpolatedFunctionOnYGrid(
				   const double x,
				   const double y,
				   const Teuchos::Array<double>& y_grid ) const
{
  if( y < y_grid.front() )
    return 0.0;
  else if( y > y_grid.back() )
    return 0.0;
  else if( y >= y_grid.front() && y < y_grid.back() )
  {
    Teuchos::Array<double>::const_iterator 
      lower_bin_boundary, upper_bin_boundary;

    lower_bin_boundary = y_grid.begin();
    upper_bin_boundary = y_grid.end();

    lower_bin_boundary = Utility::Search::binaryLowerBound<Utility::FIRST>(
							    lower_bin_boundary,
							    upper_bin_boundary,
							    y );

    upper_bin_boundary = lower_bin_boundary;
    ++upper_bin_boundary;

    // Calculate the interpolation fraction
    double alpha = (y - *lower_bin_boundary)/
      (*upper_bin_boundary - *lower_bin_boundary);

    return (1 - alpha)*d_function( x, *lower_bin_boundary ) + 
      alpha*d_function( x, *upper_bin_boundary );
  }
  else // y == y_grid.back()
    return d_function( x, y_grid.back() );
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_BilinearGridGenerator.cpp
//---------------------------------------------------------------------------//
