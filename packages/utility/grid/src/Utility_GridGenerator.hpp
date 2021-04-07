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
#include <iostream>

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

  //! Throw exception on dirty convergence
  void throwExceptionOnDirtyConvergence();

  //! Warn on dirty convergence (default)
  void warnOnDirtyConvergence();

  //! Check if an exception will be thrown on dirty convergence
  bool isExceptionThrownOnDirtyConvergence() const;

  //! Set the convergence tolerance
  void setConvergenceTolerance( const double convergence_tol );

  //! Get the convergence tolerance
  double getConvergenceTolerance() const;

  //! Set the absolute difference tolerance
  void setAbsoluteDifferenceTolerance( const double absolute_diff_tol );

  //! Get the absolute difference tolerance
  double getAbsoluteDifferenceTolerance() const;

  //! Set the distance tolerance
  void setDistanceTolerance( const double distance_tol );

  //! Get the distance tolerance
  double getDistanceTolerance() const;

  //! Generate the grid in place
  template<typename STLCompliantContainer, typename Functor>
  void generateInPlace( STLCompliantContainer& grid,
                        const Functor& function ) const;

  //! Refine the grid in place between an min and max value
  template<typename STLCompliantContainer, typename Functor>
  void refineInPlace( STLCompliantContainer& grid,
                      const Functor& function,
                      const double min_value,
                      const double max_value ) const;

  //! Generate the grid in place (return evaluated function on grid)
  template<typename STLCompliantContainerA,
           typename STLCompliantContainerB,
           typename Functor>
  void generateAndEvaluateInPlace( STLCompliantContainerA& grid,
                                   STLCompliantContainerB& evaluated_function,
                                   const Functor& function ) const;

  //! Generate the grid in place between an min and max value (return evaluated function on grid)
  template<typename STLCompliantContainerA,
           typename STLCompliantContainerB,
           typename Functor>
  void generateAndEvaluateInPlace( STLCompliantContainerA& grid,
                                   STLCompliantContainerB& evaluated_function,
                                   const Functor& function,
                                   const double min_value,
                                   const double max_value ) const;

  //! Refine the grid in place between min and max (return evaluated function on grid)
  template<typename STLCompliantContainerA,
           typename STLCompliantContainerB,
           typename Functor>
  void refineAndEvaluateInPlace(
        STLCompliantContainerA& grid,
        STLCompliantContainerB& evaluated_function,
        const Functor& function,
        const double min_value,
        const double max_value ) const;

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

  // Check for convergence
  bool hasGridConverged( const double lower_grid_point,
                         const double mid_grid_point,
                         const double upper_grid_point,
                         const double y_mid_estimated,
                         const double y_mid_exact ) const;

  // The convergence tolerance
  double d_convergence_tol;

  // The absolute difference tolerance
  double d_absolute_diff_tol;

  // The distance tolerance
  double d_distance_tol;

  // Throw exception on dirty convergence
  bool d_throw_exceptions;
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
