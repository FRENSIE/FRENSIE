//---------------------------------------------------------------------------//
//!
//! \file   Utility_LinearGridGenerator_def.hpp
//! \author Alex Robinson
//! \brief  Linear grid generator class template definitions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_LINEAR_GRID_GENERATOR_DEF_HPP
#define UTILITY_LINEAR_GRID_GENERATOR_DEF_HPP

// Std Lib Includes
#include <list>
#include <iterator>

// FRENSIE Includes
#include "Utility_ContractException.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ComparePolicy.hpp"

namespace Utility{

// Generate the linear grid in place
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
template<typename STLCompliantContainer>
void LinearGridGenerator::generateInPlace( 
				      STLCompliantContainer& linearized_grid,
				      const double convergence_tol,
				      const double absolute_diff_tol,
				      const double distance_tol ) const
{
  // Make sure the container value type is a floating point type
  testStaticPrecondition( (boost::is_float<typename STLCompliantContainer::value_type>::value) );
  // Make sure at least 2 initial grid points have been given
  testPrecondition( linearized_grid.size() >= 2 );
  // Make sure the intial grid points are sorted
  testPrecondition( Sort::isSortedAscending( linearized_grid.begin(),
					     linearized_grid.end(),
					     true ) );
  // Make sure the convergence tolerance is valid
  testPrecondition( convergence_tol <= 1.0 );
  testPrecondition( convergence_tol > 0.0 );
  // Make sure the absolute difference tolerance is valid
  testPrecondition( absolute_diff_tol <= 1.0 );
  testPrecondition( absolute_diff_tol >= 0.0 );
  // Make sure the distance tolerance is valid
  testPrecondition( distance_tol <= 1.0 );
  testPrecondition( distance_tol >= 0.0 );

  STLCompliantContainer evaluated_function;

  this->generateAndEvaluateInPlace( linearized_grid,
				    evaluated_function,
				    convergence_tol,
				    absolute_diff_tol,
				    distance_tol );
}

// Generate the linear grid in place (return evaluated function on grid)
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
template<typename STLCompliantContainerA, typename STLCompliantContainerB>
void LinearGridGenerator::generateAndEvaluateInPlace( 
				    STLCompliantContainerA& linearized_grid,
				    STLCompliantContainerB& evaluated_function,
				    const double convergence_tol,
				    const double absolute_diff_tol,
				    const double distance_tol ) const
{
  // Make sure the container value type is a floating point type
  testStaticPrecondition( (boost::is_float<typename STLCompliantContainerA::value_type>::value) );
  testStaticPrecondition( (boost::is_float<typename STLCompliantContainerB::value_type>::value) );
  // Make sure at least 2 initial grid points have been given
  testPrecondition( linearized_grid.size() >= 2 );
  // Make sure the intial grid points are sorted
  testPrecondition( Sort::isSortedAscending( linearized_grid.begin(),
					     linearized_grid.end(),
					     true ) );
  // Make sure the convergence tolerance is valid
  testPrecondition( convergence_tol <= 1.0 );
  testPrecondition( convergence_tol > 0.0 );
  // Make sure the absolute difference tolerance is valid
  testPrecondition( absolute_diff_tol <= 1.0 );
  testPrecondition( absolute_diff_tol >= 0.0 );
  // Make sure the distance tolerance is valid
  testPrecondition( distance_tol <= 1.0 );
  testPrecondition( distance_tol >= 0.0 );

  // Use a queue data structure to calculate the grid points
  std::deque<double> grid_queue( linearized_grid.begin(),
				 linearized_grid.end() );

  // Clear the initial grid
  linearized_grid.clear();
  evaluated_function.clear();
  
  // Variables used to calculate the linearized grid
  double x0, x1, x_mid, y0, y1, y_mid_exact, y_mid_estimated;
  double relative_error, abs_diff, relative_distance;

  // Evaluate the first grid point
  x0 = grid_queue.front();
  grid_queue.pop_front();

  y0 = d_function( x0 );
  
  // Calculate the grid points
  while( !grid_queue.empty() )
  {
    x1 = grid_queue.front();

    x_mid = 0.5*(x0 + x1);
    
    y1 = d_function( x1 );
    y_mid_exact = d_function( x_mid );

    y_mid_estimated = 0.5*(y0 + y1);

    relative_error = Policy::relError( y_mid_exact, y_mid_estimated );
    
    abs_diff = 
      Teuchos::ScalarTraits<double>::magnitude( y_mid_exact - y_mid_estimated);
    
    relative_distance = Policy::relError( x0, x1 );

    bool converged = false;

    // Check if the distance tolerance was hit
    if( relative_distance <= distance_tol &&
	relative_error > convergence_tol )
    {
      converged = true;

      std::cerr.precision( 18 );
      std::cerr << "Warning: distance tolerance hit before convergence - "
		<< "relError(x0,x1) = relError(" << x0 << "," << x1 << ") = "
		<< relative_distance << std::endl;
    }

    // Check if the absolute difference tolerance was hit
    if( abs_diff <= absolute_diff_tol && 
	relative_error > convergence_tol )
    {
      converged = true;

      std::cerr.precision( 18 );
      std::cerr << "Warning: absolute difference tolerance hit before "
		<< "convergence - x_mid=" << x_mid << ", y_mid_exact=" 
		<< y_mid_exact << ", y_mid_estimated="
		<< y_mid_estimated << ", abs_diff=" << abs_diff << std::endl;
    }
    
    // Check if the convergence tolerance was hit
    if( relative_error <= convergence_tol )
      converged = true;
              
    // Keep the grid points
    if( converged )
    {
      linearized_grid.push_back( x0 );
      evaluated_function.push_back( y0 );

      x0 = x1;
      grid_queue.pop_front();
      
      y0 = y1;
    }
    // Refine the grid
    else
      grid_queue.push_front( x_mid );
  }

  // Add the last point to the linearized grid
  linearized_grid.push_back( x0 );
  evaluated_function.push_back( y0 );
  
  // Make sure the linearized grid has at least 2 points
  testPostcondition( linearized_grid.size() >= 2 );
  testPostcondition( linearized_grid.size() == evaluated_function.size() );
  // Make sure the linearized grid is sorted
  testPostcondition( Sort::isSortedAscending( linearized_grid.begin(),
					      linearized_grid.end() ) );
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
template<typename STLCompliantContainerA, typename STLCompliantContainerB>
void LinearGridGenerator::generate( 
			     STLCompliantContainerA& linearized_grid,
			     const STLCompliantContainerB& initial_grid_points,
			     const double convergence_tol,
			     const double absolute_diff_tol,
			     const double distance_tol ) const
{
  // Make sure the container value type is a floating point type
  testStaticPrecondition( (boost::is_float<typename STLCompliantContainerA::value_type>::value) );
  testStaticPrecondition( (boost::is_float<typename STLCompliantContainerB::value_type>::value) );
  // Make sure at least 2 initial grid points have been given
  testPrecondition( initial_grid_points.size() >= 2 );
  // Make sure the intial grid points are sorted
  testPrecondition( Sort::isSortedAscending( initial_grid_points.begin(),
					     initial_grid_points.end(),
					     true ) );
  // Make sure the convergence tolerance is valid
  testPrecondition( convergence_tol <= 1.0 );
  testPrecondition( convergence_tol > 0.0 );
  // Make sure the absolute difference tolerance is valid
  testPrecondition( absolute_diff_tol <= 1.0 );
  testPrecondition( absolute_diff_tol >= 0.0 );
  // Make sure the distance tolerance is valid
  testPrecondition( distance_tol <= 1.0 );
  testPrecondition( distance_tol >= 0.0 );
  
  linearized_grid.assign( initial_grid_points.begin(), 
			  initial_grid_points.end() );

  STLCompliantContainerA evaluated_function;

  this->generateAndEvaluateInPlace( linearized_grid,
				    evaluated_function,
				    convergence_tol,
				    absolute_diff_tol,
				    distance_tol );
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
template<typename STLCompliantContainerA, 
	 typename STLCompliantContainerB,
	 typename STLCompliantContainerC>
void LinearGridGenerator::generateAndEvaluate( 
			     STLCompliantContainerA& linearized_grid,
			     STLCompliantContainerB& evaluated_function,
			     const STLCompliantContainerC& initial_grid_points,
			     const double convergence_tol,
			     const double absolute_diff_tol,
			     const double distance_tol ) const
{
  // Make sure the container value type is a floating point type
  testStaticPrecondition( (boost::is_float<typename STLCompliantContainerA::value_type>::value) );
  testStaticPrecondition( (boost::is_float<typename STLCompliantContainerB::value_type>::value) );
  testStaticPrecondition( (boost::is_float<typename STLCompliantContainerC::value_type>::value) );
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

  linearized_grid.assign( initial_grid_points.begin(),
			  initial_grid_points.end() );

  this->generateAndEvaluateInPlace( linearized_grid,
				    evaluated_function,
				    convergence_tol,
				    absolute_diff_tol,
				    distance_tol );
}

} // end Utility namespace

#endif // end UTILITY_LINEAR_GRID_GENERATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_LinearGridGenerator_def.hpp
//---------------------------------------------------------------------------//
