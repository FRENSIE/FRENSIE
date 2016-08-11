//---------------------------------------------------------------------------//
//!
//! \file   Utility_GridGenerator.hpp
//! \author Alex Robinson
//! \brief  Grid generator class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_GRID_GENERATOR_HPP
#define UTILITY_GRID_GENERATOR_HPP

// Std Lib Includes
#include <functional>

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// FRENSIE Includes
#include "Utility_InterpolationPolicy.hpp"

namespace Utility{

//! The grid generator class
template<typename InterpPolicy>
class GridGenerator
{

public:

  //! Constructor
  GridGenerator( const double convergence_tol = 0.001,
		 const double absolute_diff_tol = 1e-12,
		 const double distance_tol = 1e-14 );

  //! Destructor
  ~GridGenerator()
  { /* ... */ }

  //! Set the convergence tolerance
  void setConvergenceTolerance( const double convergence_tol );

  //! Set the absolute difference tolerance
  void setAbsoluteDifferenceTolerance( const double absolute_diff_tol );

  //! Set the distance tolerance
  void setDistanceTolerance( const double distance_tol );

  //! Generate the grid in place
  template<typename STLCompliantContainer, typename Functor>
  void generateInPlace( STLCompliantContainer& grid,
			const Functor& function ) const;

  //! Generate the grid in place (return evaluated function on grid)
  template<typename STLCompliantContainerA,
	   typename STLCompliantContainerB,
	   typename Functor>
  void generateAndEvaluateInPlace( STLCompliantContainerA& grid,
				   STLCompliantContainerB& evaluated_function,
				   const Functor& function ) const;

  //! Generate the grid
  template<typename STLCompliantContainerA,
	   typename STLCompliantContainerB,
	   typename Functor>
  void generate( STLCompliantContainerA& grid,
		 const STLCompliantContainerB& initial_grid_points,
		 const Functor& evaluated_function ) const;

  //! Generate the grid (return evaluated function on grid)
  template<typename STLCompliantContainerA,
	   typename STLCompliantContainerB,
	   typename STLCompliantContainerC,
	   typename Functor>
  void generateAndEvaluate( STLCompliantContainerA& grid,
			    STLCompliantContainerB& evaluated_function,
			    const STLCompliantContainerC& initial_grid_points,
			    const Functor& function ) const;

private:

  // The convergence tolerance
  double d_convergence_tol;

  // The absolute difference tolerance
  double d_absolute_diff_tol;

  // The distance tolerance
  double d_distance_tol;
};

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_GridGenerator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_GRID_GENERATOR_HPP

//---------------------------------------------------------------------------//
// End Utility_GridGenerator.hpp
//---------------------------------------------------------------------------//
