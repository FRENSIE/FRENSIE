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
#include <sstream>

// FRENSIE Includes
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ComparisonPolicy.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"

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
    d_verbose_mode_on( false ),
    d_throw_exceptions( false ),
    d_secondary_grid_generator( convergence_tol,
                                absolute_diff_tol,
                                distance_tol )
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

// Set verbose mode to on
template<typename TwoDInterpPolicy>
void TwoDGridGenerator<TwoDInterpPolicy>::setVerboseModeOn()
{
  d_verbose_mode_on = true;
}

// Set verbose mode to off (default)
template<typename TwoDInterpPolicy>
void TwoDGridGenerator<TwoDInterpPolicy>::setVerboseModeOff()
{
  d_verbose_mode_on = false;
}

// Check if verbose mode is on
template<typename TwoDInterpPolicy>
bool TwoDGridGenerator<TwoDInterpPolicy>::isVerboseModeOn() const
{
  return d_verbose_mode_on;
}

// Throw exception on dirty convergence
/*! \details "Dirty Convergence" has occurred when the distance tolerance or
 * the absolute difference tolerance is reached before the convergence
 * tolerance. This type of convergence should be avoided because the grid
 * has not truly converged.
 */
template<typename TwoDInterpPolicy>
void TwoDGridGenerator<TwoDInterpPolicy>::throwExceptionOnDirtyConvergence()
{
  d_throw_exceptions = true;

  d_secondary_grid_generator.throwExceptionOnDirtyConvergence();
}

// Warn on dirty convergence (default)
/*! \details "Dirty Convergence" has occurred when the distance tolerance or
 * the absolute difference tolerance is reached before the convergence
 * tolerance. This type of convergence should be avoided because the grid
 * has not truly converged.
 */
template<typename TwoDInterpPolicy>
void TwoDGridGenerator<TwoDInterpPolicy>::warnOnDirtyConvergence()
{
  d_throw_exceptions = false;

  d_secondary_grid_generator.warnOnDirtyConvergence();
}

// Check if an exception will be thrown on dirty convergence
template<typename TwoDInterpPolicy>
bool TwoDGridGenerator<TwoDInterpPolicy>::isExceptionThrownOnDirtyConvergence() const
{
  return d_throw_exceptions;
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

// Get the convergence tolerance
template<typename TwoDInterpPolicy>
double TwoDGridGenerator<TwoDInterpPolicy>::getConvergenceTolerance() const
{
  return d_convergence_tol;
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

  d_secondary_grid_generator.setAbsoluteDifferenceTolerance(absolute_diff_tol);
}

// Get the absolute difference tolerance
template<typename TwoDInterpPolicy>
double TwoDGridGenerator<TwoDInterpPolicy>::getAbsoluteDifferenceTolerance() const
{
  return d_absolute_diff_tol;
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

// Get the distance tolerance
template<typename TwoDInterpPolicy>
double TwoDGridGenerator<TwoDInterpPolicy>::getDistanceTolerance() const
{
  return d_distance_tol;
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
/*! \details The container must have a push_back method defined. The
 * function must have the following signature: double (double,double).
 * The first function parameter must correspond to the primary value.
 */
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
/*! \details The containers must have a push_back method defined. The
 * function must have the following signature: double (double,double).
 * The first function parameter must correspond to the primary value.
 */
template<typename TwoDInterpPolicy>
template<typename STLCompliantContainerA,
         typename STLCompliantContainerB,
         typename STLCompliantContainerC,
         typename Functor>
void TwoDGridGenerator<TwoDInterpPolicy>::generateAndEvaluateInPlace(
                                    STLCompliantContainerA& primary_grid,
                                    STLCompliantContainerB& secondary_grids,
                                    STLCompliantContainerC& evaluated_function,
                                    const Functor& function ) const
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

  std::vector<double> secondary_grid_0, secondary_grid_1;

  typename STLCompliantContainerC::value_type
    evaluated_function_0, evaluated_function_1;

  // Generate the initial secondary grid
  primary_value_0 = primary_grid_queue.front();
  primary_grid_queue.pop_front();

  this->initializeSecondaryGrid( secondary_grid_0, primary_value_0 );

  this->generateAndEvaluateSecondaryInPlace( secondary_grid_0,
                                             evaluated_function_0,
                                             primary_value_0,
                                             function );

  // Optimize the 2D grid
  while( !primary_grid_queue.empty() )
  {
    // Generate the secondary grid at the second primary grid point
    primary_value_1 = primary_grid_queue.front();

    this->initializeSecondaryGrid( secondary_grid_1, primary_value_1 );

    this->generateAndEvaluateSecondaryInPlace( secondary_grid_1,
                                               evaluated_function_1,
                                               primary_value_1,
                                               function );

    bool converged = this->hasGridConverged( primary_value_0,
                                             primary_value_1,
                                             secondary_grid_0,
                                             secondary_grid_1,
                                             evaluated_function_0,
                                             evaluated_function_1,
                                             function );

    // Keep the grid points
    if( converged )
    {
      primary_grid.push_back( primary_value_0 );
      secondary_grids.push_back(typename STLCompliantContainerB::value_type());
      secondary_grids.back().assign( secondary_grid_0.begin(),
                                     secondary_grid_0.end() );
      evaluated_function.push_back( evaluated_function_0 );

      this->logAddedPrimaryGridPoint( primary_value_0, primary_grid.size()-1 );

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

  secondary_grids.push_back( typename STLCompliantContainerB::value_type() );
  secondary_grids.back().assign( secondary_grid_0.begin(),
                                 secondary_grid_0.end() );

  evaluated_function.push_back( evaluated_function_0 );

  // Make sure there is a secondary grid for every primary grid point
  testPostcondition( primary_grid.size() == secondary_grids.size() );
  testPostcondition( secondary_grids.size() == evaluated_function.size() );
  // Make sure the optimized primary grid has at least 2 grid points
  testPostcondition( primary_grid.size() >= 2 );
}

// Generate the primary grid
/*! \details The container must have a push_back method defined. The
 * function must have the following signature: double (double,double).
 * The first function parameter must correspond to the primary value.
 */
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

  primary_grid.clear();
  primary_grid.assign( initial_primary_grid.begin(),
                       initial_primary_grid.end() );

  std::vector<STLCompliantContainerA> secondary_grids, evaluated_function;

  this->generateAndEvaluateInPlace(
                 primary_grid, secondary_grids, evaluated_function, function );
}

// Generate the primary grid (return secondary grids and evaluated function)
/*! \details The container must have a push_back method defined. The
 * function must have the following signature: double (double,double).
 * The first function parameter must correspond to the primary value.
 */
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

  primary_grid.clear();
  primary_grid.assign( initial_primary_grid.begin(),
                       initial_primary_grid.end() );

  this->generateAndEvaluateInPlace(
                 primary_grid, secondary_grids, evaluated_function, function );
}

// Generate and evaluate the secondary grid in place
/*! \details The container must have a push_back method defined. The
 * function must have the following signature: double (double,double).
 * The first function parameter must correspond to the primary value. It is
 * acceptable to pass an empty secondary grid (it will be initialized with the
 * initializeSecondaryGrid method).
 */
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
  std::vector<double> initial_secondary_grid;

  this->initializeSecondaryGrid( initial_secondary_grid, primary_value );

  // Create a function for this secondary grid
  std::function<double (double)> secondary_grid_function =
    std::bind<double>( function, primary_value, std::placeholders::_1 );

  d_secondary_grid_generator.generateAndEvaluate( secondary_grid,
                                                  evaluated_function,
                                                  initial_secondary_grid,
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
                    const STLCompliantContainerB& evaluated_function_1,
                    const Functor& function ) const
{
  // Make sure the same interpolation is used for the primary and secondary
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

  double distance = Utility::RelativeErrorComparisonPolicy::calculateRelativeError( primary_value_0, primary_value_1 );

  // Check if the distance tolerance was hit - dirty convergence
  if( distance <= d_distance_tol )
  {
    std::ostringstream oss;
    oss.precision( 18 );
    oss << "distance tolerance hit before convergence - "
        << "relError(primary_0,primary_1) =\n"
        << "relError(" << primary_value_0 << ","
        << primary_value_1 << ") = " << distance;

    if( d_throw_exceptions )
    {
      THROW_EXCEPTION( std::runtime_error, oss.str() );
    }
    else
    {
      FRENSIE_LOG_TAGGED_WARNING( "2D Grid Generator", oss.str() );
    }
  }
  // The distance tolerance has not been hit - continue checking convergence
  else
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

    typename STLCompliantContainerA::const_iterator
      secondary_grid_mid_value_it = secondary_grid_mid.begin();

    typename STLCompliantContainerA::const_iterator
      next_secondary_grid_mid_value_it = secondary_grid_mid_value_it;
    ++next_secondary_grid_mid_value_it;

    typename STLCompliantContainerB::const_iterator
      evaluated_function_mid_value_it = evaluated_function_mid.begin();

    while( secondary_grid_mid_value_it != secondary_grid_mid.end() )
    {
      // Check for convergence at the current secondary grid mid point
      converged = this->hasGridConvergedAtSecondaryPoint(
                                              primary_value_0,
                                              primary_value_1,
                                              intermediate_primary_value,
                                              *secondary_grid_mid_value_it,
                                              *evaluated_function_mid_value_it,
                                              secondary_grid_0,
                                              secondary_grid_1,
                                              evaluated_function_0,
                                              evaluated_function_1 );

      if( !converged )
        break;

      // Check for convergence at the secondary grid mid point
      if( next_secondary_grid_mid_value_it != secondary_grid_mid.end() )
      {
        double secondary_grid_mid_midpoint_value =
          this->calculateSecondaryMidpoint(*secondary_grid_mid_value_it,
                                           *next_secondary_grid_mid_value_it );
        double exact_function_value =
          function( intermediate_primary_value,
                    secondary_grid_mid_midpoint_value );

        converged = this->hasGridConvergedAtSecondaryPoint(
                                             primary_value_0,
                                             primary_value_1,
                                             intermediate_primary_value,
                                             secondary_grid_mid_midpoint_value,
                                             exact_function_value,
                                             secondary_grid_0,
                                             secondary_grid_1,
                                             evaluated_function_0,
                                             evaluated_function_1 );
        if( !converged )
          break;
      }

      // Increment iterators
      ++secondary_grid_mid_value_it;
      ++next_secondary_grid_mid_value_it;
      ++evaluated_function_mid_value_it;
    }
  }

  return converged;
}

// Check for 2D grid convergence at the intermediate value
template<typename TwoDInterpPolicy>
template<typename STLCompliantContainerA,
         typename STLCompliantContainerB>
bool TwoDGridGenerator<TwoDInterpPolicy>::hasGridConvergedAtSecondaryPoint(
                     const double primary_value_0,
                     const double primary_value_1,
                     const double intermediate_primary_value,
                     const double secondary_value,
                     const double exact_function_value,
                     const STLCompliantContainerA& secondary_grid_0,
                     const STLCompliantContainerA& secondary_grid_1,
                     const STLCompliantContainerB& evaluated_function_0,
                     const STLCompliantContainerB& evaluated_function_1 ) const
{
  bool converged = true;

  // Check for convergence at the grid point
  double interp_function_value = TwoDInterpPolicy::interpolateUnitBase(
                                                  primary_value_0,
                                                  primary_value_1,
                                                  intermediate_primary_value,
                                                  secondary_value,
                                                  secondary_grid_0.begin(),
                                                  secondary_grid_0.end(),
                                                  evaluated_function_0.begin(),
                                                  evaluated_function_0.end(),
                                                  secondary_grid_1.begin(),
                                                  secondary_grid_1.end(),
                                                  evaluated_function_1.begin(),
                                                  evaluated_function_1.end() );

  double relative_error =
    Utility::RelativeErrorComparisonPolicy::calculateRelativeError( exact_function_value, interp_function_value );
  
  double abs_diff =
    Utility::CloseComparisonPolicy::calculateDistance( exact_function_value, interp_function_value );
  
  // Not converged
  if( relative_error > d_convergence_tol &&
      abs_diff > d_absolute_diff_tol )
  {
    converged = false;
  }
  // Check if the absolute difference tolerance was hit - dirty convergence
  else if( relative_error > d_convergence_tol &&
           abs_diff <= d_absolute_diff_tol )
  {
    std::ostringstream oss;
    oss.precision( 18 );
    oss << "absolute difference tolerance hit before "
        << "convergence - primary_0="
        << primary_value_0 << ", primary_1="
        << primary_value_1 << ", secondary="
        << secondary_value << ", abs_diff_val="
        << abs_diff;

    if( d_throw_exceptions )
    {
      THROW_EXCEPTION( std::runtime_error, oss.str() );
    }
    else
    {
      FRENSIE_LOG_TAGGED_WARNING( "2D Grid Generator", oss.str() );
    }
  }
  // else - clean convergence

  // Log the check details
  this->logSecondaryGridCheck( primary_value_0,
                               primary_value_1,
                               intermediate_primary_value,
                               secondary_value,
                               interp_function_value,
                               exact_function_value,
                               converged );

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

// Log added primary grid point
template<typename TwoDInterpPolicy>
inline void TwoDGridGenerator<TwoDInterpPolicy>::logAddedPrimaryGridPoint(
                                     const double primary_grid_point,
                                     const double primary_grid_point_id ) const
{
  if( d_verbose_mode_on )
  {
    FRENSIE_LOG_TAGGED_NOTIFICATION( "2D Grid Generator",
                                     "Added " << primary_grid_point << " ("
                                     << primary_grid_point_id << ")" );
  }
}

// Log secondary grid check
template<typename TwoDInterpPolicy>
inline void TwoDGridGenerator<TwoDInterpPolicy>::logSecondaryGridCheck(
                                            const double primary_grid_point_0,
                                            const double primary_grid_point_1,
                                            const double primary_point,
                                            const double secondary_point,
                                            const double interp_function_value,
                                            const double exact_function_value,
                                            const bool converged ) const
{
  if( d_verbose_mode_on )
  {
    FRENSIE_LOG_TAGGED_NOTIFICATION( "2D Grid Generator",
               "Secondary convergence ("
                << (converged ? "passed" : "FAILED" ) << "): "
                << "f(x=" << primary_point << ",y=" << secondary_point << ")= "
                << exact_function_value << " "
                << (converged ? "~=" : "!=") << " "
                << "Interp(x in [" << primary_grid_point_0 << ","
                << primary_grid_point_1 << "],y)= " << interp_function_value );
  }
}

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( TwoDGridGenerator<Utility::LinLinLin> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( TwoDGridGenerator<Utility::LinLinLog> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( TwoDGridGenerator<Utility::LinLogLin> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( TwoDGridGenerator<Utility::LinLogLog> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( TwoDGridGenerator<Utility::LogLinLin> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( TwoDGridGenerator<Utility::LogLinLog> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( TwoDGridGenerator<Utility::LogLogLin> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( TwoDGridGenerator<Utility::LogLogLog> );
  
} // end Utility namespace

#endif // end UTILITY_TWO_D_GRID_GENERATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_TwoDGridGenerator_def.hpp
//---------------------------------------------------------------------------//
