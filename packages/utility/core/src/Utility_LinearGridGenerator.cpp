//---------------------------------------------------------------------------//
//! 
//! \file   Utility_LinearGridGenerator.cpp
//! \author Alex Robinson
//! \brief  Linear grid generator class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <deque>

// FRENSIE Includes
#include "Utility_LinearGridGenerator.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ComparePolicy.hpp"

namespace Utility{

// Constructor
LinearGridGenerator::LinearGridGenerator( 
			   const boost::function<double (double x)>& function )
  : d_function( function )
{
  // Make sure the function wrapper is not empty
  testPrecondition( !function.empty() );
}

// Reset the function
void LinearGridGenerator::resetFunction( 
			   const boost::function<double (double x)>& function )
{
  // Make sure the function wrapper is not empty
  testPrecondition( !function.empty() );

  d_function = function;
}

// Generate the linearized grid
/*! \details There must be at least two initial grid points given (the lower
 * grid boundary and the upper grid boundary). If there are discontinuities in
 * the function, the grid points just below and just above the discontinuity
 * should also be given to speed up the algorithm. The convergence tolerance
 * is used to determine if two consecutive grid points are acceptable - if
 * the relative error between the estimated value of the function (from 
 * lin-lin interpolation) at the midpoint between two grid points end the
 * actual value of the function at the midpoint is less that or equal to the
 * convergence tolerance, the two grid points are kept. Otherwise the midpoint
 * is inserted into the grid and the process is repeated.
 */ 
void LinearGridGenerator::generate( 
			     Teuchos::Array<double>& linearized_grid,
			     const Teuchos::Array<double>& initial_grid_points,
			     const double convergence_tol,
			     const double absolute_diff_tol,
			     const double distance_tol ) const
{
  // Make sure at least 2 initial grid points have been given
  testPrecondition( initial_grid_points.size() >= 2 );
  // Make sure the intial grid points are sorted
  testPrecondition( Sort::isSortedAscending( initial_grid_points.begin(),
					     initial_grid_points.end() ) );
  // Make sure the convergence tolerance is valid
  testPrecondition( convergence_tol <= 1.0 );
  testPrecondition( convergence_tol > 0.0 );
  // Make sure the absolute difference tolerance is valid
  testPrecondition( absolute_diff_tol <= 1.0 );
  testPrecondition( absolute_diff_tol >= 0.0 );
  // Make sure the distance tolerance is valid
  testPrecondition( distance_tol <= 1.0 );
  testPrecondition( distance_tol >= 0.0 );

  // Clear the linearized grid
  linearized_grid.clear();

  // Use a queue data structure to calculate the grid points
  std::deque<double> grid_queue( initial_grid_points.begin(),
				 initial_grid_points.end() );
  
  // Variables used to calculate the linearized grid
  double x0, x1, x_mid, y0, y1, y_mid_exact, y_mid_estimated;
  double relative_error, abs_diff, relative_distance;

  // Calculate the grid points
  while( grid_queue.size() > 1 )
  {
    x0 = grid_queue.front();
    
    grid_queue.pop_front();

    x1 = grid_queue.front();

    x_mid = 0.5*(x0 + x1);

    y0 = d_function( x0 );
    y1 = d_function( x1 );
    y_mid_exact = d_function( x_mid );

    y_mid_estimated = 0.5*(y0 + y1);

    relative_error = Utility::Policy::relError( y_mid_exact, y_mid_estimated );
    
    abs_diff = 
      Teuchos::ScalarTraits<double>::magnitude( y_mid_exact - y_mid_estimated);
    
    relative_distance = Utility::Policy::relError( x0, x1 );
              
    // Refine the grid
    if( relative_error > convergence_tol && 
	abs_diff > absolute_diff_tol &&
	relative_distance > distance_tol )
    {
      grid_queue.push_front( x_mid );
      grid_queue.push_front( x0 );
    }
    // Keep the grid points
    else
      linearized_grid.push_back( x0 );
  }

  // Add the last point to the linearized grid
  linearized_grid.push_back( grid_queue.front() );  

  // Make sure the linearized grid has at least 2 points
  testPostcondition( linearized_grid.size() >= 2 );
  // Make sure the linearized grid is sorted
  testPostcondition( Sort::isSortedAscending( linearized_grid.begin(),
					      linearized_grid.end() ) );
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_LinearGridGenerator.cpp
//---------------------------------------------------------------------------//
