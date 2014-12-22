//---------------------------------------------------------------------------//
//!
//! \file   Utility_BilinearGridGenerator.hpp
//! \author Alex Robinson
//! \brief  Bilinear grid generator class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_BILINEAR_GRID_GENERATOR_HPP
#define UTILITY_BILINEAR_GRID_GENERATOR_HPP

// Boost Includes
#include <boost/function.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>

namespace Utility{

//! The Bilinear grid generator class
class BilinearGridGenerator
{

public:

  //! Constructor
  BilinearGridGenerator( 
	       const boost::function<double (double x, double y)>& function,
	       const boost::function<double (double x)>& lower_ylim_function,
	       const boost::function<double (double x)>& upper_ylim_function );

  //! Destructor
  ~BilinearGridGenerator()
  { /* ... */ }

  //! Reset the function
  void resetFunction( 
	       const boost::function<double (double x, double y)>& function,
	       const boost::function<double (double x)>& lower_ylim_function,
	       const boost::function<double (double x)>& upper_ylim_function );
  
  //! Generate the bilinear grid
  void generate( Teuchos::Array<double>& linear_x_grid,
		 Teuchos::Array<Teuchos::Array<double> >& linear_y_grids,
		 const Teuchos::Array<double>& initial_x_grid,
		 const double convergence_tol = 0.001,
		 const double absolute_diff_tol = 1e-12,
		 const double distance_tol = 1e-14 ) const;
  
private:

  // Test if x grid has converged
  bool hasXGridConverged( const double x0, 
			  const double x_mid,
			  const double x1,
			  const Teuchos::Array<double>& x0_y_grid,
			  const Teuchos::Array<double>& x_mid_y_grid,
			  const Teuchos::Array<double>& x1_y_grid,
			  const double convergence_tol,
			  const double absolute_diff_tol ) const;

  // Use lin-lin interpolation to find f(x,y) on y grid
  double calculateInterpolatedFunctionOnYGrid(
				  const double x,
				  const double y,
				  const Teuchos::Array<double>& y_grid ) const;

  // The function used to generate the bilinear grid
  boost::function<double (double x, double y)> d_function;

  // The function used to determine the lower y limit of the function
  boost::function<double (double x)> d_lower_ylim_function;

  // The function used to determine the upper y limit of the function
  boost::function<double (double x)> d_upper_ylim_function;
};

} // end Utility namespace

#endif // end UTILITY_BILINEAR_GRID_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end Utility_BilinearGridGenerator.hpp
//---------------------------------------------------------------------------//
