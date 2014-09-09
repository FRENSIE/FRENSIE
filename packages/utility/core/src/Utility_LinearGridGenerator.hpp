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

// Trilinos Includes
#include <Teuchos_Array.hpp>

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

  //! Generate the linear grid
  void generate( Teuchos::Array<double>& linearized_grid,
		 const Teuchos::Array<double>& initial_grid_points,
		 const double convergence_tol = 0.001,
		 const double absolute_diff_tol = 1e-12,
		 const double distance_tol = 1e-14 ) const;
  
private:

  // The function used to generate the grid
  boost::function<double (double x)> d_function;
};

} // end Utility namespace

#endif // end UTILITY_LINEAR_GRID_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end Utility_LinearGridGenerator.hpp
//---------------------------------------------------------------------------//
