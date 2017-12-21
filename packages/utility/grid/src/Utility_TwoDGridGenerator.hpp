//---------------------------------------------------------------------------//
//!
//! \file   Utility_TwoDGridGenerator.hpp
//! \author Alex Robinson
//! \brief  Two-dimensional grid generator class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TWO_D_GRID_GENERATOR_HPP
#define UTILITY_TWO_D_GRID_GENERATOR_HPP

// Std Lib Includes
#include <functional>
#include <iostream>

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// FRENSIE Includes
#include "Utility_TwoDInterpolationPolicy.hpp"
#include "Utility_GridGenerator.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Deque.hpp"

namespace Utility{

//! The two-dimensional grid generator class
template<typename TwoDInterpPolicy>
class TwoDGridGenerator
{

public:

  //! Constructor
  TwoDGridGenerator( const double convergence_tol = 0.001,
                     const double absolute_diff_tol = 1e-12,
                     const double distance_tol = 1e-14 );

  //! Destructor
  virtual ~TwoDGridGenerator()
  { /* ... */ }

  //! Set verbose mode to on
  void setVerboseModeOn();

  //! Set verbose mode to off (default)
  void setVerboseModeOff();

  //! Check if verbose mode is on
  bool isVerboseModeOn() const;

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

  //! Generate the primary grid in place
  template<typename STLCompliantContainer, typename Functor>
  void generateInPlace( STLCompliantContainer& primary_grid,
                        const Functor& function ) const;

  //! Generate the primary grid in place (return secondary grids and evaluated function)
  template<typename STLCompliantContainerA,
           typename STLCompliantContainerB,
           typename STLCompliantContainerC,
           typename Functor>
  void generateAndEvaluateInPlace( STLCompliantContainerA& primary_grid,
                                   STLCompliantContainerB& secondary_grids,
                                   STLCompliantContainerC& evaluated_function,
                                   const Functor& function ) const;

  //! Generate the primary grid
  template<typename STLCompliantContainerA,
           typename STLCompliantContainerB,
           typename Functor>
  void generate( STLCompliantContainerA& primary_grid,
                 const STLCompliantContainerB& initial_primary_grid,
                 const Functor& function ) const;

  //! Generate the primary grid (return secondary grids and evaluated function)
  template<typename STLCompliantContainerA,
           typename STLCompliantContainerB,
           typename STLCompliantContainerC,
           typename STLCompliantContainerD,
           typename Functor>
  void generateAndEvaluate( STLCompliantContainerA& primary_grid,
                            STLCompliantContainerB& secondary_grids,
                            STLCompliantContainerC& evaluated_function,
                            const STLCompliantContainerD& initial_primary_grid,
                            const Functor& function ) const;

  //! Generate and evaluate the secondary grid in place
  template<typename STLCompliantContainerA,
           typename STLCompliantContainerB,
           typename Functor>
  void generateAndEvaluateSecondaryInPlace(
                                    STLCompliantContainerA& secondary_grid,
                                    STLCompliantContainerB& evaluated_function,
                                    const double primary_value,
                                    const Functor& function ) const;

protected:

  //! Add critical values to primary grid
  virtual void addCriticalValuesToPrimaryGrid(
                                      std::deque<double>& primary_grid ) const;

  //! Initialize secondary grid at a primary grid point
  virtual void initializeSecondaryGrid(
                                   std::vector<double>& secondary_grid,
                                   const double primary_grid_point ) const = 0;

  // The secondary grid generator
  Utility::GridGenerator<typename TwoDInterpPolicy::ZYInterpPolicy>
  d_secondary_grid_generator;

private:

  // Check for 2D grid convergence
  template<typename STLCompliantContainerA,
           typename STLCompliantContainerB,
           typename Functor>
  bool hasGridConverged(
                    const double primary_value_0,
                    const double primary_value_1,
                    const STLCompliantContainerA& secondary_grid_0,
                    const STLCompliantContainerA& secondary_grid_1,
                    const STLCompliantContainerB& evaluated_function_0,
                    const STLCompliantContainerB& evaluated_function_1,
                    const Functor& function ) const;

  // Check for 2D grid convergence at the intermediate value
  template<typename STLCompliantContainerA,
           typename STLCompliantContainerB>
  bool hasGridConvergedAtSecondaryPoint(
                    const double primary_value_0,
                    const double primary_value_1,
                    const double intermediate_primary_value,
                    const double secondary_value,
                    const double exact_function_value,
                    const STLCompliantContainerA& secondary_grid_0,
                    const STLCompliantContainerA& secondary_grid_1,
                    const STLCompliantContainerB& evaluated_function_0,
                    const STLCompliantContainerB& evaluated_function_1 ) const;

  // Calculate the midpoint between two primary values
  double calculatePrimaryMidpoint( const double primary_value_0,
                                   const double primary_value_1 ) const;

  // Calculate the midpoint between two secondary values
  double calculateSecondaryMidpoint( const double secondary_value_0,
                                     const double secondary_value_1 ) const;

  // Log added primary grid point
  void logAddedPrimaryGridPoint( const double primary_grid_point,
                                 const double primary_grid_point_id ) const;

  // Log secondary grid check
  void logSecondaryGridCheck( const double primary_grid_point_0,
                              const double primary_grid_point_1,
                              const double primary_point,
                              const double secondary_point,
                              const double interp_function_value,
                              const double exact_function_value,
                              const bool converged ) const;

  // The convergence tolerance
  double d_convergence_tol;

  // The absolute difference tolerance
  double d_absolute_diff_tol;

  // The distance tolerance
  double d_distance_tol;

  // Verbose mode
  bool d_verbose_mode_on;

  // Throw exception on dirty convergence
  bool d_throw_exceptions;
};
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_TwoDGridGenerator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_TWO_D_GRID_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end Utility_TwoDGridGenerator.hpp
//---------------------------------------------------------------------------//
