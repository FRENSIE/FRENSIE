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

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// FRENSIE Includes
#include "Utility_TwoDInterpolationPolicy.hpp"

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

  //! Set the convergence tolerance
  void setConvergenceTolerance( const double convergence_tol );

  //! Set the absolute difference tolerance
  void setAbsoluteDifferenceTolerance( const double absolute_diff_tol );

  //! Set the distance tolerance
  void setDistanceTolerance( const double distance_tol );

  //! Add critical values to primary grid
  virtual void addCriticalValuesToPrimaryGrid(
                                      std::deque<double>& primary_grid ) const;

  //! Initialize secondary grid at a primary grid point
  virtual void initializeSecondaryGrid(
                                   std::deque<double>& secondary_grid,
                                   const double primary_grid_point ) const = 0;

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
                                   const Function& function ) const;

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
                    const STLCompliantContainerB& evaluated_function_1 ) const;

  // Calculate the midpoint between two primary values
  double calculatePrimaryMidpoint( const double primary_value_0,
                                   const double primary_value_1 ) const;

  // Calculate the midpoint between two secondary values
  double calculateSecondaryMidpoint( const double secondary_value_0,
                                     const double secondary_value_1 ) const;

  // The convergence tolerance
  double d_convergence_tol;

  // The absolute difference tolerance
  double d_absolute_diff_tol;

  // The distance tolerance
  double d_distance_tol;

  // The secondary grid generator
  Utility::GridGenerator<typename TwoDInterpPolicy::ZYInterpPolicy>
  d_secondary_grid_generator;
};
  
} // end Utility namespace

#endif // end UTILITY_TWO_D_GRID_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end Utility_TwoDGridGenerator.hpp
//---------------------------------------------------------------------------//
