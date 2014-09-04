//---------------------------------------------------------------------------//
//!
//! \file   Utility_LinearizeGridGenerator.hpp
//! \author Alex Robinson
//! \brief  Linearized grid generator class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_LINEARIZED_GRID_GENERATOR_HPP
#define UTILITY_LINEARIZED_GRID_GENERATOR_HPP

// Boost Includes
#include <boost/function.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>

namespace Utility{

//! The linearized grid generator class
class LinearizedGridGenerator
{
  
public:

  //! Constructor
  LinearizedGridGenerator( const boost::function<double (double x)>& function);

  //! Destructor
  ~LinearizedGridGenerator()
  { /* ... */ }

  //! Reset the function
  void resetFunction( const boost::function<double (double x)>& function );

  //! Generate the linearized grid
  void generate( Teuchos::Array<double>& linearized_grid,
		 const Teuchos::Array<double>& initial_grid_points,
		 const double convergence_tol = 0.001,
		 const double absolute_diff_tol = 1e-12 ) const;
  
private:

  // The function used to generate the grid
  boost::function<double (double x)> d_function;
};

} // end Utility namespace

#endif // end UTILITY_LINEARIZED_GRID_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end Utility_LinearizedGridGenerator.hpp
//---------------------------------------------------------------------------//
