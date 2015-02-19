//---------------------------------------------------------------------------//
//!
//! \file   Utility_LinearGridGenerator.hpp
//! \author Alex Robinson
//! \brief  Linear grid generator class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_LINEAR_GRID_GENERATOR_HPP
#define UTILITY_LINEAR_GRID_GENERATOR_HPP

// Boost Includes
#include <boost/function.hpp>

namespace Utility{

//! The linear grid generator class
class LinearGridGenerator
{
  
public:

  //! Constructor
  LinearGridGenerator( const boost::function<double (double x)>& function);

  //! Destructor
  ~LinearGridGenerator()
  { /* ... */ }

  //! Reset the function
  void resetFunction( const boost::function<double (double x)>& function );

  //! Generate the linear grid in place
  template<typename STLCompliantContainer>
  void generateInPlace( STLCompliantContainer& linearized_grid,
			const double convergence_tol = 0.001,
			const double absolute_diff_tol = 1e-12,
			const double distance_tol = 1e-14 ) const;

  //! Generate the linear grid in place (return evaluated function on grid)
  template<typename STLCompliantContainerA, typename STLCompliantContainerB>
  void generateAndEvaluateInPlace( STLCompliantContainerA& linearized_grid,
				   STLCompliantContainerB& evaluated_function,
				   const double convergence_tol = 0.001,
				   const double absolute_diff_tol = 1e-12,
				   const double distance_tol = 1e-14 ) const;

  //! Generate the linear grid
  template<typename STLCompliantContainerA, typename STLCompliantContainerB>
  void generate( STLCompliantContainerA& linearized_grid,
		 const STLCompliantContainerB& initial_grid_points,
		 const double convergence_tol = 0.001,
		 const double absolute_diff_tol = 1e-12,
		 const double distance_tol = 1e-14 ) const;

  //! Generate the linear grid (return evaluated function on grid)
  template<typename STLCompliantContainerA, 
	   typename STLCompliantContainerB,
	   typename STLCompliantContainerC>
  void generateAndEvaluate( STLCompliantContainerA& linearized_grid,
			    STLCompliantContainerB& evaluated_function,
			    const STLCompliantContainerC& initial_grid_points,
			    const double convergence_tol = 0.001,
			    const double absolute_diff_tol = 1e-12,
			    const double distance_tol = 1e-14 ) const;
  
private:

  // The function used to generate the grid
  boost::function<double (double x)> d_function;
};

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_LinearGridGenerator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_LINEAR_GRID_GENERATOR_HPP

//---------------------------------------------------------------------------//
// End Utility_LinearGridGenerator.hpp
//---------------------------------------------------------------------------//
