//---------------------------------------------------------------------------//
//!
//! \file   Utility_TwoDGridGenerator_def.hpp
//! \author Alex Robinson
//! \brief  The two-dimensional grid generator class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TWO_D_GRID_GENERATOR_DEF_HPP
#define UTILITY_TWO_D_GRID_GENERATOR_DEF_HPP

// Std Lib Includes
#include <vector>
#include <deque>
#include <algorithm>
#include <iterator>

// FRENSIE Includes
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ComparePolicy.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Constructor
template<typename TwoDInterpPolicy>
TwoDGridGenerator<TwoDInterpPolicy>::TwoDGridGenerator(
                                                const double convergence_tol,
                                                const double absolute_diff_tol,
                                                const double distance_tol )
  : d_convergence_tol( convergence_tol ),
    d_absolute_diff_tol( absolute_diff_tol ),
    d_distance_tol( distance_tol ),
    d_secondary_grid_generator( convergence_tol,
                                absolute_diff_tol,
                                distance_tol );
{
  // Make sure the convergence tolerance is valid
  testPrecondition( convergence_tol <= 1.0 );
  testPrecondition( convergence_tol > 0.0 );
  // Make sure the absolute difference tolerance is valid
  testPrecondition( absolute_diff_tol <= 1.0 );
  testPrecondition( absolute_diff_tol >= 0.0 );
  // Make sure the distance tolerance is valid
  testPrecondition( distance_tol <= 1.0 );
  testPrecondition( distance_tol >= 0.0 );
}

// Set the convergence tolerance
template<typename TwoDInterpPolicy>
void TwoDGridGenerator<TwoDInterpPolicy>::setConvergenceTolerance(
                                                 const double convergence_tol )
{
  // Make sure the convergence tolerance is valid
  testPrecondition( convergence_tol <= 1.0 );
  testPrecondition( convergence_tol > 0.0 );

  d_convergence_tol = convergence_tol;

  d_secondary_grid_generator.setConvergenceTolerance( convergence_tol );
}

// Set the absolute difference tolerance
template<typename TwoDInterpPolicy>
void TwoDGridGenerator<TwoDInterpPolicy>::setAbsoluteDifferenceTolerance(
                                               const double absolute_diff_tol )
{
  // Make sure the absolute difference tolerance is valid
  testPrecondition( absolute_diff_tol <= 1.0 );
  testPrecondition( absolute_diff_tol >= 0.0 );

  d_absolute_diff_tol = absolute_diff_tol;

  d_secondary_grid_generator.setAbsoluteDifferenceTolerance(
                                                           absolute_diff_tol );
}

// Set the distance tolerance
template<typename TwoDInterpPolicy>
void TwoDGridGenerator<TwoDInterpPolicy>::setDistanceTolerance(
                                                    const double distance_tol )
{
  // Make sure the distance tolerance is valid
  testPrecondition( distance_tol <= 1.0 );
  testPrecondition( distance_tol >= 0.0 );

  d_distance_tol = distance_tol;

  d_secondary_grid_generator.setDistanceTolerance( distance_tol );
}

// Add critical values to primary grid
/*! \details Use this method to add critical grid points to the supplied
 * primary grid. The default does nothing.
 */
template<typename TwoDInterpPolicy>
void TwoDGridGenerator<TwoDInterpPolicy>::addCriticalValuesToPrimaryGrid(
                                       std::deque<double>& primary_grid ) const
{ /* ... */ }

// Generate the primary grid in place
template<typename TwoDInterpPolicy>
template<typename STLCompliantContainer, typename Functor>
void TwoDGridGenerator<TwoDInterpPolicy>::generateInPlace(
                                           STLCompliantContainer& primary_grid,
                                           const Functor& function ) const
{
  // Make sure the container value type is a floating point type
  testStaticPrecondition( (boost::is_float<typename STLCompliantContainer::value_type>::value) );
  // Make sure at least 2 initial grid points have been given
  testPrecondition( primary_grid.size() >= 2 );
  // Make sure the initial grid points are sorted
  testPrecondition( Sort::isSortedAscending( primary_grid.begin(),
                                             primary_grid.end(),
                                             true ) );

  std::vector<STLCompliantContainer> secondary_grids, evaluated_function;

  this->generateAndEvaluateInPlace(
                 primary_grid, secondary_grids, evaluated_function, function );
}

// Generate the primary grid in place (return secondary grids and evaluated function)
template<typename TwoDInterpPolicy>
template<typename STLCompliantContainerA,
         typename STLCompliantContainerB,
         typename STLCompliantContainerC,
         typename Functor>
void TwoDGridGenerator<TwoDInterpPolicy>::generateAndEvaluateInPlace(
                                    STLCompliantContainerA& primary_grid,
                                    STLCompliantContainerB& secondary_grids,
                                    STLCompliantContainerC& evaluated_function,
                                    const Function& function ) const
{
  // Make sure the container value type is a floating point type
  testStaticPrecondition( (boost::is_float<typename STLCompliantContainerA::value_type>::value) );
  testStaticPrecondition( (boost::is_float<typename STLCompliantContainerB::value_type::value_type>::value) );
  testStaticPrecondition( (boost::is_float<typename STLCompliantContainerC::value_type::value_type>::value) );
  testPrecondition( primary_grid.size() >= 2 );
  // Make sure the initial grid points are sorted
  testPrecondition( Sort::isSortedAscending( primary_grid.begin(),
                                             primary_grid.end(),
                                             true ) );

  // Use a queue data structure to calculate the primary grid points
  std::deque<double> primary_grid_queue( primary_grid.begin(),
                                         primary_grid.end() );

  // Initialize the primary grid
  this->addCriticalValuesToPrimaryGrid( primary_grid_queue );

  // Clear the input data
  primary_grid.clear();
  secondary_grids.clear();
  evaluated_function.clear();

  double primary_value_0, primary_value_1;
  typename STLCompliantContainerB::value_type
    secondary_grid_0, secondary_grid_1;
  typename STLCompliantContainerC::value_type
    evaluated_function_0, evaluated_funtion_1;

  // Generate the initial secondary grid
  primary_value_0 = primary_grid_queue.front();
  primary_grid_queue.pop_front();

  this->generateAndEvaluateSecondaryInPlace( secondary_grid_0,
                                             evaluated_function_0,
                                             primary_value_0 );
  
  // Optimize the 2D grid
  while( !primary_grid_queue.empty() )
  {
    // Generate the secondary grid at the second primary grid point
    primary_value_1 = primary_grid_queue.front();

    this->initializeSecondaryGrid( secondary_grid_1, primary_value_1 );
    
    this->generateAndEvaluateSecondaryInPlace( secondary_grid_1,
                                               evaluated_function_1,
                                               primary_value_1 );

    bool converged = this->hasGridConverged( primary_value_0,
                                             primary_value_1,
                                             secondary_grid_0,
                                             secondary_grid_1,
                                             evaluated_function_0,
                                             evaluated_function_1 );

    // Keep the grid points
    if( converged )
    {
      primary_grid.push_back( primary_value_0 );
      secondary_grids.push_back( secondary_grid_0 );

      if( d_verbose )
      {
        std::cout.precision( 18 );
        std::cout << "Added " << primary_value_0 << " ("
                  << primary_grid.size()-1 << ")" << std::endl;
      }

      primary_value_0 = primary_value_1;
      primary_grid_queue.pop_front();

      secondary_grid_0 = secondary_grid_1;
      evaluated_function_0 = evaluated_function_1;
    }
    // Refine the grid
    else
    {
      primary_grid_queue.push_front(
          this->calculatePrimaryMidpoint( primary_value_0, primary_value_1 ) );
    }
  }

  primary_grid.push_back( primary_value_0 );
  secondary_grids.push_back( secondary_grid_0 );
  evaluated_function_0.push_back( evaluated_function_0 );

  // Make sure there is a secondary grid for every primary grid point
  testPostcondition( primary_grid.size() == secondary_grids.size() );
  testPostcondition( seconary_grids.size() == evaluated_function.size() );
  // Make sure the optimized primary grid has at least 2 grid points
  testPostcondition( primary_grid.size() >= 2 );
}

// Generate the primary grid
template<typename TwoDInterpPolicy>
template<typename STLCompliantContainerA,
         typename STLCompliantContainerB,
         typename Functor>
void TwoDGridGenerator<TwoDInterpPolicy>::generate(
                            STLCompliantContainerA& primary_grid,
                            const STLCompliantContainerB& initial_primary_grid,
                            const Functor& function ) const
{
  // Make sure the container value type is a floating point type
  testStaticPrecondition( (boost::is_float<typename STLCompliantContainerA::value_type>::value) );
  testStaticPrecondition( (boost::is_float<typename STLCompliantContainerB::value_type>::value) );
  // Make sure at least 2 initial grid points have been given
  testPrecondition( initial_primary_grid.size() >= 2 );
  // Make sure the initial grid points are sorted
  testPrecondition( Sort::isSortedAscending( initial_primary_grid.begin(),
                                             initial_primary_grid.end(),
                                             true ) );

  primary_grid.assign( initial_primary_grid.begin(),
                       initial_primary_grid.end() );

  std::vector<STLCompliantContainerA> secondary_grids, evaluated_function;

  this->generateAndEvaluateInPlace(
                 primary_grid, secondary_grids, evaluated_function, function );
}

// Generate the primary grid (return secondary grids and evaluated function)
template<typename TwoDInterpPolicy>
template<typename STLCompliantContainerA,
         typename STLCompliantContainerB,
         typename STLCompliantContainerC,
         typename STLCompliantContainerD,
         typename Functor>
void TwoDGridGenerator<TwoDInterpPolicy>::generateAndEvaluate(
                            STLCompliantContainerA& primary_grid,
                            STLCompliantContainerB& secondary_grids,
                            STLCompliantContainerC& evaluated_function,
                            const STLCompliantContainerD& initial_primary_grid,
                            const Functor& function ) const
{
  // Make sure the container value type is a floating point type
  testStaticPrecondition( (boost::is_float<typename STLCompliantContainerA::value_type>::value) );
  testStaticPrecondition( (boost::is_float<typename STLCompliantContainerD::value_type>::value) );
  testStaticPrecondition( (boost::is_float<typename STLCompliantContainerB::value_type::value_type>::value) );
  testStaticPrecondition( (boost::is_float<typename STLCompliantContainerC::value_type::value_type>::value) );
  // Make sure at least 2 initial grid points have been given
  testPrecondition( initial_primary_grid.size() >= 2 );
  // Make sure the initial grid points are sorted
  testPrecondition( Sort::isSortedAscending( initial_primary_grid.begin(),
                                             initial_primary_grid.end(),
                                             true ) );

  primary_grid.assign( initial_primary_grid.begin(),
                       initial_primary_grid.end() );

  this->generateAndEvaluateInPlace(
                 primary_grid, secondary_grids, evaluated_function, function );
}

// Generate and evaluate the secondary grid in place
template<typename TwoDInterpPolicy>
template<typename STLCompliantContainerA,
         typename STLCompliantContainerB,
         typename Functor>
void TwoDGridGenerator<TwoDInterpPolicy>::generateAndEvaluateSecondaryInPlace(
                                    STLCompliantContainerA& secondary_grid,
                                    STLCompliantContainerB& evaluated_function,
                                    const double primary_value,
                                    const Functor& function ) const
{
  // Make sure the container value type is a floating point type
  testStaticPrecondition( (boost::is_float<typename STLCompliantContainerA::value_type>::value) );
  testStaticPrecondition( (boost::is_float<typename STLCompliantContainerB::value_type>::value) );

  // Initialize the secondary grid
  std::deque<double> secondary_grid_queue;
  
  this->initializeSecondaryGrid( seconary_grid_queue, primary_value );

  // Create a function for this secondary grid
  std::function<double (double)> secondary_grid_function =
    std::bind( function, primary_value, _1 );

  d_secondary_grid_generator.generateAndEvaluate( secondary_grid,
                                                  evaluated_function,
                                                  secondary_grid_queue,
                                                  secondary_grid_function );
}

// Check for 2D grid convergence
template<typename TwoDInterpPolicy>
template<typename STLCompliantContainerA,
         typename STLCompliantContainerB,
         typename Functor>
bool TwoDGridGenerator<TwoDInterpPolicy>::hasGridConverged(
                    const double primary_value_0,
                    const double primary_value_1,
                    const STLCompliantContainerA& secondary_grid_0,
                    const STLCompliantContainerA& secondary_grid_1,
                    const STLCompliantContainerB& evaluated_function_0,
                    const STLCompliantContainerB& evaluated_function_1 ) const
{
  // Make sure the same inerpolation is used for the primary and secondary
  testStaticPrecondition( (boost::is_same<typename TwoDInterpPolicy::FirstIndepVarProcessingTag,typename TwoDInterpPolicy::SecondIndepVarProcessingTag>::value) );
  // Make sure the primary values are valid
  testPrecondition( primary_value_0 < primary_value_1 );
  // Make sure the secondary grids are valid
  testPrecondition( Utility::Sort::isSortedAscending(
                                                    secondary_grid_0.begin(),
                                                    secondary_grid_0.end() ) );
  testPrecondition( Utility::Sort::isSortedAscending(
                                                    secondary_grid_1.begin(),
                                                    secondary_grid_1.end() ) );
  // Make sure the evaluated functions are valid
  testPrecondition( secondary_grid_0.size() == evaluated_function_0.size() );
  testPrecondition( secondary_grid_1.size() == evaluated_function_1.size() );

  bool converged = true;

  double distance =
    Utility::Policy::relError( primary_value_0, primary_value_1 );

  if( distance > d_distance_tol )
  {
    // Generate an optimized grid at the intermediate primary value
    const double intermediate_primary_value =
      this->calculatePrimaryMidpoint( primary_value_0, primary_value_1 );

    STLCompliantContainerA secondary_grid_mid;
    STLCompliantContainerB evaluated_function_mid;

    this->generateAndEvaluateSecondaryInPlace( secondary_grid_mid,
                                               evaluated_function_mid,
                                               intermediate_primary_value,
                                               function );

    STLCompliantContainerA::const_iterator secondary_grid_mid_value_it =
      secondary_grid_mid.begin();

    while( secondary_grid_mid_value_it != secondary_grid_mid.end() )
    {
      // Check for convergence at the grid point
      double interp_secondary_value = TwoDInterpPolicy::interpolateUnitBase(
                                                  primary_value_0,
                                                  primary_value_1,
                                                  intermediate_primary_value,
                                                  *secondary_grid_mid_value_it,
                                                  secondary_grid_0.begin(),
                                                  secondary_grid_0.end(),
                                                  evaluated_function_0.begin(),
                                                  evaluated_function_0.end(),
                                                  secondary_grid_1.begin(),
                                                  secondary_grid_1.end(),
                                                  evaluated_function_1.begin(),
                                                  evaluated_function_1.end() );

      double relative_error =
        Utility::Policy::relError( *secondary_grid_mid_value_it,
                                   interp_secondary_value );

      double abs_diff = fabs( *secondary_grid_mid_value_it,
                              interp_secondary_value );

      if( relative_error > d_convergence_tol &&
          abs_diff > d_absolute_diff_tol )
      {
        converged = false;

        break;
      }
      else if( relative_error > d_convergence_tol &&
               abs_diff <= d_absolute_diff_dol )
      {
        std::cerr << "Warning: absolute difference tolerance hit before "
                  << "convergence - primary_0="
                  << primary_value_0 << ", primary_1="
                  << primary_value_1 << ", secondary="
                  << *secondary_grid_mid_value_it << ", abs_diff_val="
                  << abs_diff << std::endl;
      }

      // Check for convergence at the grid mid point
      STLCompliantContainerA::const_iterator next_secondary_grid_mid_value_it =
        secondary_grid_mid_value_it;
      ++next_secondary_grid_mid_value_it;

      if( next_secondary_grid_mid_value_it != secondary_grid_mid.end() )
      {
        double secondary_grid_mid_midpoint_value =
          this->calculateSecondaryMidpoint(*secondary_grid_mid_value_it,
                                           *next_secondary_grid_mid_value_it );

        interp_secondary_value = TwoDInterpPolicy::interpolateUnitBase(
                                             primary_value_0,
                                             primary_value_1,
                                             intermediate_primary_value,
                                             secondary_grid_mid_midpoint_value,
                                             secondary_grid_0.begin(),
                                             secondary_grid_0.end(),
                                             evaluated_function_0.begin(),
                                             evaluated_function_0.end(),
                                             secondary_grid_1.begin(),
                                             secondary_grid_1.end(),
                                             evaluated_function_1.begin(),
                                             evaluated_function_1.end() );

        double true_secondary_value =
          function( intermediate_primary_value,
                    secondary_grid_mid_midpoint_value );

        relative_error = Utility::Policy::relError( true_secondary_value,
                                                    interp_secondary_value );

        abs_diff = fabs( true_secondary_value - interp_secondary_value );

        if( relative_error > d_convergence_tol &&
            abs_diff > d_absolute_diff_tol )
        {
          converged = false;

          break;
        }
        else if( relative_error > d_convergence_tol &&
                 abs_diff <= d_absolute_diff_tol )
        {
          std::cerr << "Warning: absolute difference tolerance hit before "
                  << "convergence - primary_0="
                  << primary_value_0 << ", primary_1="
                  << primary_value_1 << ", secondary="
                  << secondary_grid_mid_midpoint_value << ", abs_diff_val="
                  << abs_diff << std::endl;
        }
      }
    }
  }
  else
  {
    std::cerr.precision( 18 );
    std::cerr << "Warning: distance tolerance hit before convergence - "
              << "relError(primary_0,primary_1) =\n"
              << "relError(" << primary_value_0 << ","
              << primary_value_1 << ") = " << distance << std::endl;
  }

  return converged;
}

// Calculate the midpoint between two primary values
template<typename TwoDInterpPolicy>
double TwoDGridGenerator<TwoDInterpPolicy>::calculatePrimaryMidpoint(
                                           const double primary_value_0,
                                           const double primary_value_1 ) const
{
  return TwoDInterpPolicy::recoverProcessedFirstIndepVar(
              0.5*(TwoDInterpPolicy::processFirstIndepVar(primary_value_0) +
                   TwoDInterpPolicy::processFirstIndepVar(primary_value_1) ) );
}
  
// Calculate the midpoint between two secondary values
template<typename TwoDInterpPolicy>
double TwoDGridGenerator<TwoDInterpPolicy>::calculateSecondaryMidpoint(
                                         const double secondary_value_0,
                                         const double secondary_value_1 ) const
{
  return TwoDInterpPolicy::recoverProcessedSecondIndepVar(
           0.5*(TwoDInterpPolicy::processSecondIndepVar(secondary_value_0) +
                TwoDInterpPolicy::processSecondIndepVar(secondary_value_1) ) );
}
  
} // end Utility namespace

#endif // end UTILITY_TWO_D_GRID_GENERATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_TwoDGridGenerator_def.hpp
//---------------------------------------------------------------------------//
