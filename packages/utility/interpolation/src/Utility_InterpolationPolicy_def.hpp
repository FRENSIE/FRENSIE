//---------------------------------------------------------------------------//
//!
//! \file   Utility_InterpolationPolicy_def.hpp
//! \author Alex Robinson
//! \brief  Interpolation policy struct definitions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INTERPOLATION_POLICY_DEF_HPP
#define UTILITY_INTERPOLATION_POLICY_DEF_HPP

// Std Lib Includes
#include <cmath>

// Boost Includes
#include <boost/mpl/or.hpp>

// FRENSIE Includes
#include "Utility_QuantityTraits.hpp"
#include "Utility_IsFloatingPoint.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{

// Interpolate between two processed points
template<typename ParentInterpolationType>
template<typename T>
T InterpolationHelper<ParentInterpolationType>::interpolate(
                                                 const T processed_indep_var_0,
                                                 const T processed_indep_var,
                                                 const T processed_dep_var_0,
                                                 const T processed_slope )
{
  // T must be a floating point type
  testStaticPrecondition( (std::is_floating_point<T>::value) );
  // Make sure the processed independent variables are valid
  testPrecondition( !Utility::QuantityTraits<T>::isnaninf(
						     processed_indep_var_0 ) );
  testPrecondition( !Utility::QuantityTraits<T>::isnaninf(
						       processed_indep_var ) );
  testPrecondition( processed_indep_var_0 <= processed_indep_var );
  // Make sure the processed dependent variable is valid
  testPrecondition( !Utility::QuantityTraits<T>::isnaninf(
						       processed_dep_var_0 ) );
  // Make sure that the slope is valid
  testPrecondition( !Utility::QuantityTraits<T>::isnaninf( processed_slope ) );

  return ParentInterpolationType::recoverProcessedDepVar(
               processed_dep_var_0 +
               processed_slope*(processed_indep_var - processed_indep_var_0) );
}

// Interpolate between two processed points and return the processed value
template<typename ParentInterpolationType>
template<typename T>
T InterpolationHelper<ParentInterpolationType>::interpolateAndProcess(
                                                 const T processed_indep_var_0,
                                                 const T processed_indep_var,
                                                 const T processed_dep_var_0,
                                                 const T processed_slope )
{
  // T must be a floating point type
  testStaticPrecondition( (std::is_floating_point<T>::value) );
  // Make sure the processed independent variables are valid
  testPrecondition( !Utility::QuantityTraits<T>::isnaninf(
						     processed_indep_var_0 ) );
  testPrecondition( !Utility::QuantityTraits<T>::isnaninf(
						       processed_indep_var ) );
  testPrecondition( processed_indep_var_0 <= processed_indep_var );
  // Make sure the processed dependent variable is valid
  testPrecondition( !Utility::QuantityTraits<T>::isnaninf(
						       processed_dep_var_0 ) );
  // Make sure that the slope is valid
  testPrecondition( !Utility::QuantityTraits<T>::isnaninf( processed_slope ) );

  return processed_dep_var_0 +
    processed_slope*(processed_indep_var - processed_indep_var_0);
}

// Calculate the unit base grid length (L)
/*! \details For LinLog and LogLog interpolation types the grid length
 * that is calculated is not a traditional length. It is the distance between
 * the processed upper independent value and the processed lower
 * independent value. This is why any units associated with the independent
 * grid limits are stripped away.
 */
template<typename ParentInterpolationType>
template<typename IndepType>
inline typename QuantityTraits<IndepType>::RawType
InterpolationHelper<ParentInterpolationType>::calculateUnitBaseGridLength(
                                       const IndepType grid_lower_indep_value,
                                       const IndepType grid_upper_indep_value )
{
  // Make sure the grid is valid
  testPrecondition( grid_lower_indep_value <= grid_upper_indep_value );
  testPrecondition( ParentInterpolationType::isIndepVarInValidRange(
                                                    grid_lower_indep_value ) );

  return ThisType::calculateUnitBaseGridLengthProcessed(
          ParentInterpolationType::processIndepVar( grid_lower_indep_value ),
          ParentInterpolationType::processIndepVar( grid_upper_indep_value ) );
}

// Calculate the unit base grid length from a processed grid (L)
/*! \details For LinLog and LogLog interpolation types the grid length
 * that is calculated is not a traditional length. It is the distance between
 * the processed upper independent value and the processed lower
 * independent value. This is why any units associated with the independent
 * grid limits are stripped away. Due to conversion of the independent
 * values from a cosine (mu) to a delta cosine ( 1 - mu ) + nudge for LogLogCos
 * and LinLogCos, it is assumed the processed grids are inverted to ensure they
 * are in ascending order.
 */
template<typename ParentInterpolationType>
template<typename T>
inline T InterpolationHelper<ParentInterpolationType>::calculateUnitBaseGridLengthProcessed(
                                     const T processed_grid_lower_indep_value,
                                     const T processed_grid_upper_indep_value )
{
  // Make sure the grid is valid
  testPrecondition( processed_grid_lower_indep_value <=
                    processed_grid_upper_indep_value );

  const T processed_grid_length =
    processed_grid_upper_indep_value - processed_grid_lower_indep_value;

  // Make sure the grid length is valid
  testPrecondition( processed_grid_length >= 0.0 );

  return processed_grid_length;
}

// Calculate the unit base independent variable (eta)
/*! \details The independent grid length is calculated using the
 * processed independent grid limits. It has been found that a tolerance of
 * 1e-3 works best for most applications.
 */
template<typename ParentInterpolationType>
template<typename IndepType>
inline typename QuantityTraits<IndepType>::RawType
InterpolationHelper<ParentInterpolationType>::calculateUnitBaseIndepVar(
          const IndepType indep_var,
          const IndepType indep_var_min,
          const typename QuantityTraits<IndepType>::RawType indep_grid_length,
          const double tol )
{
  // Make sure the intermediate grid min indep var is valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_min ) );
  testPrecondition( ParentInterpolationType::isIndepVarInValidRange( indep_var_min ) );
  // Make sure the intermediate grid length is valid
  testPrecondition( !QuantityTraits<typename QuantityTraits<IndepType>::RawType>::isnaninf( indep_grid_length ) );
  testPrecondition( indep_grid_length > 0.0 );
  // Make sure the independent variable is valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var ) );
  testPrecondition( ParentInterpolationType::isIndepVarInValidRange( indep_var ) );
  testPrecondition( indep_var >=
                    ThisType::calculateFuzzyLowerBound( indep_var_min, tol ) );
  remember( typename QuantityTraits<IndepType>::RawType test_difference =
            ParentInterpolationType::processIndepVar(indep_var) -
            ParentInterpolationType::processIndepVar(indep_var_min) );

  testPrecondition( test_difference <= ThisType::calculateFuzzyUpperBound(
                                                    indep_grid_length, tol ) );

  return calculateUnitBaseIndepVarProcessed(
                       ParentInterpolationType::processIndepVar(indep_var),
                       ParentInterpolationType::processIndepVar(indep_var_min),
                       indep_grid_length,
                       tol );
}

// Calculate the unit base independent variable (eta)
/*! \details It has been found that a tolerance of 1e-3 works best for most
 * applications.
 */
template<typename ParentInterpolationType>
template<typename T>
inline T InterpolationHelper<ParentInterpolationType>::calculateUnitBaseIndepVarProcessed(
                                               const T processed_indep_var,
                                               const T processed_indep_var_min,
                                               const T indep_grid_length,
                                               const double tol )
{
  // Make sure the intermediate grid min indep var is valid
  testPrecondition( !QuantityTraits<T>::isnaninf( processed_indep_var_min ) );
  // Make sure the independent y variable is valid
  testPrecondition( !QuantityTraits<T>::isnaninf(processed_indep_var) );
  testPrecondition( processed_indep_var >= ThisType::calculateFuzzyLowerBound(
                                              processed_indep_var_min, tol ) );
  remember( T test_difference = processed_indep_var - processed_indep_var_min);
  testPrecondition( test_difference <= ThisType::calculateFuzzyUpperBound(
                                                    indep_grid_length, tol ) );
  // Make sure the intermediate grid length is valid
  testPrecondition( !QuantityTraits<T>::isnaninf( indep_grid_length ) );
  testPrecondition( indep_grid_length > 0.0 );

  T eta = (processed_indep_var - processed_indep_var_min)/indep_grid_length;

  // Check for rounding errors and correct
  if( eta > 1.0 )
  {
    if( eta - 1.0 < tol )
      eta = 1.0;
  }
  else if( eta < 0.0 )
  {
    if( eta > -tol )
      eta = 0.0;
  }

  // Make sure eta is valid
  testPostcondition( eta >= 0.0 );
  testPostcondition( eta <= 1.0 );

  return eta;
}

// Calculate the independent variable (from eta)
/*! \details It has been found that a tolerance of 1e-3 works best for most
 * applications.
 */
template<typename ParentInterpolationType>
template<typename IndepType>
inline IndepType
InterpolationHelper<ParentInterpolationType>::calculateIndepVar(
          const typename QuantityTraits<IndepType>::RawType eta,
          const IndepType indep_var_min,
          const typename QuantityTraits<IndepType>::RawType indep_grid_length,
          const double tol )
{
  // Make sure the eta value is valid
  testPrecondition( eta >= 0.0 );
  testPrecondition( eta <= 1.0 );
  // Make sure the grid min indep var is valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_min ) );
  testPrecondition( ParentInterpolationType::isIndepVarInValidRange( indep_var_min ) );
  // Make sure the grid length is valid
  testPrecondition( !QuantityTraits<typename QuantityTraits<IndepType>::RawType>::isnaninf( indep_grid_length ) );
  testPrecondition( indep_grid_length >= 0.0 );

  IndepType grid_indep_var( QuantityTraits<IndepType>::initializeQuantity(
    ParentInterpolationType::recoverProcessedIndepVar(
                    ParentInterpolationType::processIndepVar( indep_var_min ) +
                    indep_grid_length*eta ) ) );

  // Check for rounding errors
  if( grid_indep_var < indep_var_min &&
      grid_indep_var >= ThisType::calculateFuzzyLowerBound(indep_var_min, tol))
    grid_indep_var = indep_var_min;

  // Make sure the calculated independent variable is valid
  testPostcondition( grid_indep_var >= indep_var_min );

  return grid_indep_var;
}

// Calculate the processed independent variable (from eta)
/*! \details A tolerance is not required with this method because no variable
 * processing is done. Due to conversion of the independent values from a cosine
 * (mu) to a delta cosine ( 1 - mu ) + nudge for LogLogCos and LinLogCos, it is
 * assumed the processed grids are inverted to ensure they are in ascending
 * order.
 */
template<typename ParentInterpolationType>
template<typename T>
inline T InterpolationHelper<ParentInterpolationType>::calculateProcessedIndepVar(
                                               const T eta,
                                               const T processed_indep_var_min,
                                               const T indep_grid_length )
{
  // Make sure the eta value is valid
  testPrecondition( eta >= 0.0 );
  testPrecondition( eta <= 1.0 );
  // Make sure the grid min indep var is valid
  testPrecondition( !QuantityTraits<T>::isnaninf( processed_indep_var_min ) );
  // Make sure the grid length is valid
  testPrecondition( !QuantityTraits<T>::isnaninf( indep_grid_length ) );
  testPrecondition( indep_grid_length >= 0.0 );

  return processed_indep_var_min + indep_grid_length*eta;
}

// Calculate the "fuzzy" lower bound (lower bound with roundoff tolerance)
/*! \details It has been found that a tolerance of 1e-3 works best for most
 * applications.
 */
template<typename ParentInterpolationType>
template<typename T>
inline T InterpolationHelper<ParentInterpolationType>::calculateFuzzyLowerBound(
                                                             const T value,
                                                             const double tol )
{
  if( value < QuantityTraits<T>::zero() )
    return value*(1+tol);
  else
    return value*(1-tol);
}

// Calculate the "fuzzy" upper bound (upper bound with roundoff tolerance)
/*! \details It has been found that a tolerance of 1e-3 works best for most
 * applications
 */
template<typename ParentInterpolationType>
template<typename T>
inline T InterpolationHelper<ParentInterpolationType>::calculateFuzzyUpperBound(
                                                             const T value,
                                                             const double tol )
{
  if( value > QuantityTraits<T>::zero() )
    return value*(1+tol);
  else
    return value*(1-tol);
}

// The name of the policy
template<typename ParentInterpolationType>
inline std::string InterpolationHelper<ParentInterpolationType>::name()
{
  return Utility::typeName<ParentInterpolationType>();
}

// Get the interpolation type
inline InterpolationType LogLog::getInterpolationType()
{
  return LOGLOG_INTERPOLATION;
}

// Interpolate between two points
template<typename IndepType, typename DepType>
inline DepType LogLog::interpolate( const IndepType indep_var_0,
				    const IndepType indep_var_1,
				    const IndepType indep_var,
				    const DepType dep_var_0,
				    const DepType dep_var_1 )
{
  // The IndepType must be a floating point type
  testStaticPrecondition( (Utility::IsFloatingPoint<IndepType>::value) );
  testStaticPrecondition( (Utility::IsFloatingPoint<DepType>::value) );
  // Make sure the independent variables are valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_0 ) );
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_1 ) );
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var ) );
  testPrecondition( LogLog::isIndepVarInValidRange( indep_var_0 ) );
  testPrecondition( LogLog::isIndepVarInValidRange( indep_var_1 ) );
  testPrecondition( LogLog::isIndepVarInValidRange( indep_var ) );
  testPrecondition( indep_var_0 < indep_var_1 );
  testPrecondition( indep_var >= indep_var_0 );
  testPrecondition( indep_var <= indep_var_1 );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_0 ) );
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_1 ) );
  testPrecondition( LogLog::isDepVarInValidRange( dep_var_0 ) );
  testPrecondition( LogLog::isDepVarInValidRange( dep_var_1 ) );

  return dep_var_0*
    pow((dep_var_1/dep_var_0),
	log(indep_var/indep_var_0)/log(indep_var_1/indep_var_0));
}

// Interpolate between two points using the indep variable ratio (beta)
template<typename T, typename DepType>
inline DepType LogLog::interpolate( const T beta,
                                    const DepType dep_var_0,
                                    const DepType dep_var_1 )
{
  // The IndepType must be a floating point type
  testStaticPrecondition( (std::is_floating_point<typename QuantityTraits<T>::RawType>::value) );
  testStaticPrecondition( (std::is_floating_point<typename QuantityTraits<DepType>::RawType>::value ) );
  // Make sure the independent variables are valid
  testPrecondition( beta >= QuantityTraits<T>::zero() );
  testPrecondition( beta <= QuantityTraits<T>::one() );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_0 ) );
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_1 ) );
  testPrecondition( LogLog::isDepVarInValidRange( dep_var_0 ) );
  testPrecondition( LogLog::isDepVarInValidRange( dep_var_1 ) );

  return dep_var_0*pow((dep_var_1/dep_var_0),beta);
}

// Interpolate between two points and return the processed value
template<typename IndepType, typename DepType>
inline typename QuantityTraits<DepType>::RawType
LogLog::interpolateAndProcess( const IndepType indep_var_0,
			       const IndepType indep_var_1,
			       const IndepType indep_var,
			       const DepType dep_var_0,
			       const DepType dep_var_1 )
{
  // T must be a floating point type
  testStaticPrecondition( (Utility::IsFloatingPoint<IndepType>::value) );
  testStaticPrecondition( (Utility::IsFloatingPoint<DepType>::value) );
  // Make sure the independent variables are valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_0 ) );
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_1 ) );
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var ) );
  testPrecondition( LogLog::isIndepVarInValidRange( indep_var_0 ) );
  testPrecondition( LogLog::isIndepVarInValidRange( indep_var_1 ) );
  testPrecondition( LogLog::isIndepVarInValidRange( indep_var ) );
  testPrecondition( indep_var_0 < indep_var_1 );
  testPrecondition( indep_var >= indep_var_0 );
  testPrecondition( indep_var <= indep_var_1 );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_0 ) );
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_1 ) );
  testPrecondition( LogLog::isDepVarInValidRange( dep_var_0 ) );
  testPrecondition( LogLog::isDepVarInValidRange( dep_var_1 ) );

  return log( getRawQuantity(dep_var_0) ) + log ( dep_var_1/dep_var_0 )*
    log( indep_var/indep_var_0 )/log( indep_var_1/indep_var_0 );
}

// Process the independent value
template<typename T>
inline typename QuantityTraits<T>::RawType
LogLog::processIndepVar( const T indep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( LogLog::isIndepVarInValidRange( indep_var ) );

  return log( getRawQuantity(indep_var) );
}

// Process the dependent value
template<typename T>
inline typename QuantityTraits<T>::RawType
LogLog::processDepVar( const T dep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( LogLog::isDepVarInValidRange( dep_var ) );

  return log( getRawQuantity(dep_var) );
}

// Recover the processed independent value
template<typename T>
inline T LogLog::recoverProcessedIndepVar( const T processed_indep_var )
{
  return exp( processed_indep_var );
}

// Recover the processed dependent value
template<typename T>
inline T LogLog::recoverProcessedDepVar( const T processed_dep_var )
{
  return exp( processed_dep_var );
}

// Test if the independent value is in a valid range (doesn't check nan/inf)
template<typename T>
inline bool LogLog::isIndepVarInValidRange( const T indep_var )
{
  return indep_var > QuantityTraits<T>::zero();
}

// Test if the dependent value is in a valid range (doesn't check nan/inf)
template<typename T>
inline bool LogLog::isDepVarInValidRange( const T dep_var )
{
  // Make sure the indep var is not inf or nan
  testPrecondition( !QuantityTraits<T>::isnaninf( dep_var ) );

  return dep_var > QuantityTraits<T>::zero();
}

// Get the interpolation type
inline InterpolationType LogLin::getInterpolationType()
{
  return LOGLIN_INTERPOLATION;
}

// Interpolate between two points
template<typename IndepType, typename DepType>
inline DepType LogLin::interpolate( const IndepType indep_var_0,
				    const IndepType indep_var_1,
				    const IndepType indep_var,
				    const DepType dep_var_0,
				    const DepType dep_var_1 )
{
  // T must be a floating point type
  testStaticPrecondition( (Utility::IsFloatingPoint<IndepType>::value) );
  testStaticPrecondition( (Utility::IsFloatingPoint<DepType>::value) );
  // Make sure the independent variables are valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_0 ) );
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_1 ) );
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var ) );
  testPrecondition( LogLin::isIndepVarInValidRange( indep_var_0 ) );
  testPrecondition( LogLin::isIndepVarInValidRange( indep_var_1 ) );
  testPrecondition( LogLin::isIndepVarInValidRange( indep_var ) );
  testPrecondition( indep_var_0 < indep_var_1 );
  testPrecondition( indep_var >= indep_var_0 );
  testPrecondition( indep_var <= indep_var_1 );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_0 ) );
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_1 ) );
  testPrecondition( LogLin::isDepVarInValidRange( dep_var_0 ) );
  testPrecondition( LogLin::isDepVarInValidRange( dep_var_1 ) );

  return dep_var_0*pow((dep_var_1/dep_var_0), (indep_var-indep_var_0)/(indep_var_1-indep_var_0));
}

// Interpolate between two points using the indep variable ratio (beta)
template<typename T, typename DepType>
inline DepType LogLin::interpolate( const T beta,
                                    const DepType dep_var_0,
                                    const DepType dep_var_1 )
{
  // The IndepType must be a floating point type
  testStaticPrecondition( (std::is_floating_point<typename QuantityTraits<T>::RawType>::value) );
  testStaticPrecondition( (std::is_floating_point<typename QuantityTraits<DepType>::RawType>::value) );
  // Make sure the independent variables are valid
  testPrecondition( beta >= QuantityTraits<T>::zero() );
  testPrecondition( beta <= QuantityTraits<T>::one() );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_0 ) );
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_1 ) );
  testPrecondition( LogLin::isDepVarInValidRange( dep_var_0 ) );
  testPrecondition( LogLin::isDepVarInValidRange( dep_var_1 ) );

  return dep_var_0*pow((dep_var_1/dep_var_0),beta);
}

// Interpolate between two points and return the processed value
template<typename IndepType, typename DepType>
inline typename QuantityTraits<DepType>::RawType
LogLin::interpolateAndProcess( const IndepType indep_var_0,
			       const IndepType indep_var_1,
			       const IndepType indep_var,
			       const DepType dep_var_0,
			       const DepType dep_var_1 )
{
  // T must be a floating point type
  testStaticPrecondition( (Utility::IsFloatingPoint<IndepType>::value) );
  testStaticPrecondition( (Utility::IsFloatingPoint<DepType>::value) );
  // Make sure the independent variables are valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_0 ) );
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_1 ) );
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var ) );
  testPrecondition( LogLin::isIndepVarInValidRange( indep_var_0 ) );
  testPrecondition( LogLin::isIndepVarInValidRange( indep_var_1 ) );
  testPrecondition( LogLin::isIndepVarInValidRange( indep_var ) );
  testPrecondition( indep_var_0 < indep_var_1 );
  testPrecondition( indep_var >= indep_var_0 );
  testPrecondition( indep_var <= indep_var_1 );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_0 ) );
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_1 ) );
  testPrecondition( LogLin::isDepVarInValidRange( dep_var_0 ) );
  testPrecondition( LogLin::isDepVarInValidRange( dep_var_1 ) );

  return log( getRawQuantity(dep_var_0) ) + log( dep_var_1/dep_var_0 )*
    (indep_var-indep_var_0)/(indep_var_1-indep_var_0);
}

// Process the independent value
template<typename T>
inline typename QuantityTraits<T>::RawType
LogLin::processIndepVar( const T indep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( LogLin::isIndepVarInValidRange( indep_var ) );

  return getRawQuantity(indep_var);
}

// Process the dependent value
template<typename T>
inline typename QuantityTraits<T>::RawType
LogLin::processDepVar( const T dep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( LogLin::isDepVarInValidRange( dep_var ) );

  return log( getRawQuantity(dep_var) );
}

// Recover the processed independent value
template<typename T>
inline T LogLin::recoverProcessedIndepVar( const T processed_indep_var )
{
  return processed_indep_var;
}

// Recover the processed dependent value
template<typename T>
inline T LogLin::recoverProcessedDepVar( const T processed_dep_var )
{
  return exp( processed_dep_var );
}

// Test if the independent value is in a valid range (doesn't check nan/inf)
template<typename T>
inline bool LogLin::isIndepVarInValidRange( const T indep_var )
{
  return true;
}

// Test if the dependent value is in a valid range (doesn't check nan/inf)
template<typename T>
inline bool LogLin::isDepVarInValidRange( const T dep_var )
{
  // Make sure the indep var is not inf or nan
  testPrecondition( !QuantityTraits<T>::isnaninf( dep_var ) );

  return dep_var > QuantityTraits<T>::zero();
}

// Get the interpolation type
inline InterpolationType LinLog::getInterpolationType()
{
  return LINLOG_INTERPOLATION;
}

// Interpolate between two points
template<typename IndepType, typename DepType>
inline DepType LinLog::interpolate( const IndepType indep_var_0,
				    const IndepType indep_var_1,
				    const IndepType indep_var,
				    const DepType dep_var_0,
				    const DepType dep_var_1 )
{
  // T must be a floating point type
  testStaticPrecondition( (Utility::IsFloatingPoint<IndepType>::value) );
  testStaticPrecondition( (Utility::IsFloatingPoint<DepType>::value) );
  // Make sure the independent variables are valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_0 ) );
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_1 ) );
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var ) );
  testPrecondition( LinLog::isIndepVarInValidRange( indep_var_0 ) );
  testPrecondition( LinLog::isIndepVarInValidRange( indep_var_1 ) );
  testPrecondition( LinLog::isIndepVarInValidRange( indep_var ) );
  testPrecondition( indep_var_0 < indep_var_1 );
  testPrecondition( indep_var >= indep_var_0 );
  testPrecondition( indep_var <= indep_var_1 );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_0 ) );
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_1 ) );
  testPrecondition( LinLog::isDepVarInValidRange( dep_var_0 ) );
  testPrecondition( LinLog::isDepVarInValidRange( dep_var_1 ) );

  DepType term_2( (dep_var_1 - dep_var_0)*log(indep_var/indep_var_0)/
		  log(indep_var_1/indep_var_0) );

  return dep_var_0 + term_2;
}

// Interpolate between two points using the indep variable ratio (beta)
template<typename T, typename DepType>
inline DepType LinLog::interpolate( const T beta,
                                    const DepType dep_var_0,
                                    const DepType dep_var_1 )
{
  // The IndepType must be a floating point type
  testStaticPrecondition( (std::is_floating_point<typename QuantityTraits<T>::RawType>::value) );
  testStaticPrecondition( (std::is_floating_point<typename QuantityTraits<DepType>::RawType>::value) );
  // Make sure the independent variables are valid
  testPrecondition( beta >= QuantityTraits<T>::zero() );
  testPrecondition( beta <= QuantityTraits<T>::one() );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_0 ) );
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_1 ) );
  testPrecondition( LinLog::isDepVarInValidRange( dep_var_0 ) );
  testPrecondition( LinLog::isDepVarInValidRange( dep_var_1 ) );

  return dep_var_0 + (dep_var_1 - dep_var_0)*beta;
}

// Interpolate between two points and return the processed value
template<typename IndepType, typename DepType>
inline typename QuantityTraits<DepType>::RawType
LinLog::interpolateAndProcess( const IndepType indep_var_0,
			       const IndepType indep_var_1,
			       const IndepType indep_var,
			       const DepType dep_var_0,
			       const DepType dep_var_1 )
{
  return getRawQuantity( interpolate( indep_var_0,
				      indep_var_1,
				      indep_var,
				      dep_var_0,
				      dep_var_1 ) );
}

// Process the independent value
template<typename T>
inline typename QuantityTraits<T>::RawType
LinLog::processIndepVar( const T indep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( LinLog::isIndepVarInValidRange( indep_var ) );

  return log( getRawQuantity(indep_var) );
}

// Process the dependent value
template<typename T>
inline typename QuantityTraits<T>::RawType
LinLog::processDepVar( const T dep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( LinLog::isDepVarInValidRange( dep_var ) );

  return getRawQuantity(dep_var);
}

// Recover the processed independent value
template<typename T>
inline T LinLog::recoverProcessedIndepVar( const T processed_indep_var )
{
  return exp( processed_indep_var );
}

// Recover the processed dependent value
template<typename T>
inline T LinLog::recoverProcessedDepVar( const T processed_dep_var )
{
  return processed_dep_var;
}

// Test if the independent value is in a valid range (doesn't check nan/inf)
template<typename T>
inline bool LinLog::isIndepVarInValidRange( const T indep_var )
{
  return indep_var > QuantityTraits<T>::zero();
}

// Test if the dependent value is in a valid range (doesn't check nan/inf)
template<typename T>
inline bool LinLog::isDepVarInValidRange( const T dep_var )
{
  // Make sure the indep var is not inf or nan
  testPrecondition( !QuantityTraits<T>::isnaninf( dep_var ) );

  return true;
}

// Get the interpolation type
inline InterpolationType LinLin::getInterpolationType()
{
  return LINLIN_INTERPOLATION;
}

// Interpolate between two points
template<typename IndepType, typename DepType>
inline DepType LinLin::interpolate( const IndepType indep_var_0,
				    const IndepType indep_var_1,
				    const IndepType indep_var,
				    const DepType dep_var_0,
				    const DepType dep_var_1 )
{
  // T must be a floating point type
  testStaticPrecondition( (Utility::IsFloatingPoint<IndepType>::value) );
  testStaticPrecondition( (Utility::IsFloatingPoint<DepType>::value) );
  // Make sure the independent variables are valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_0 ) );
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_1 ) );
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var ) );
  testPrecondition( LinLin::isIndepVarInValidRange( indep_var_0 ) );
  testPrecondition( LinLin::isIndepVarInValidRange( indep_var_1 ) );
  testPrecondition( LinLin::isIndepVarInValidRange( indep_var ) );
  testPrecondition( indep_var_0 < indep_var_1 );
  testPrecondition( indep_var >= indep_var_0 );
  testPrecondition( indep_var <= indep_var_1 );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_0 ) );
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_1 ) );
  testPrecondition( LinLin::isDepVarInValidRange( dep_var_0 ) );
  testPrecondition( LinLin::isDepVarInValidRange( dep_var_1 ) );

  DepType term_2( (dep_var_1 - dep_var_0)/(indep_var_1 - indep_var_0)*
		  (indep_var - indep_var_0) );

  return dep_var_0 + term_2;
}

// Interpolate between two points using the indep variable ratio (beta)
template<typename T, typename DepType>
inline DepType LinLin::interpolate( const T beta,
                                    const DepType dep_var_0,
                                    const DepType dep_var_1 )
{
  // The IndepType must be a floating point type
  testStaticPrecondition( (std::is_floating_point<typename QuantityTraits<T>::RawType>::value) );
  testStaticPrecondition( (std::is_floating_point<typename QuantityTraits<DepType>::RawType>::value) );
  // Make sure the independent variables are valid
  testPrecondition( beta >= QuantityTraits<T>::zero() );
  testPrecondition( beta <= QuantityTraits<T>::one() );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_0 ) );
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_1 ) );
  testPrecondition( LinLin::isDepVarInValidRange( dep_var_0 ) );
  testPrecondition( LinLin::isDepVarInValidRange( dep_var_1 ) );

  return dep_var_0 + (dep_var_1 - dep_var_0)*beta;
}

// Interpolate between two points and return the processed value
template<typename IndepType, typename DepType>
inline typename QuantityTraits<DepType>::RawType
LinLin::interpolateAndProcess( const IndepType indep_var_0,
			       const IndepType indep_var_1,
			       const IndepType indep_var,
			       const DepType dep_var_0,
			       const DepType dep_var_1 )
{
  return getRawQuantity( interpolate( indep_var_0,
				      indep_var_1,
				      indep_var,
				      dep_var_0,
				      dep_var_1 ) );
}

// Process the independent value
template<typename T>
inline typename QuantityTraits<T>::RawType
LinLin::processIndepVar( const T indep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( LinLin::isIndepVarInValidRange( indep_var  ) );

  return getRawQuantity(indep_var);
}

// Process the dependent value
template<typename T>
inline typename QuantityTraits<T>::RawType
LinLin::processDepVar( const T dep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( LinLin::isDepVarInValidRange( dep_var ) );

  return getRawQuantity(dep_var);
}

// Recover the processed independent value
template<typename T>
inline T LinLin::recoverProcessedIndepVar( const T processed_indep_var )
{
  return processed_indep_var;
}

// Recover the processed dependent value
template<typename T>
inline T LinLin::recoverProcessedDepVar( const T processed_dep_var )
{
  return processed_dep_var;
}

// Test if the independent value is in a valid range (doesn't check nan/inf)
template<typename T>
inline bool LinLin::isIndepVarInValidRange( const T indep_var )
{
  return true;
}

// Test if the dependent value is in a valid range (doesn't check nan/inf)
template<typename T>
inline bool LinLin::isDepVarInValidRange( const T dep_var )
{
  // Make sure the indep var is not inf or nan
  testPrecondition( !QuantityTraits<T>::isnaninf( dep_var ) );

  return true;
}

} // end Utility namespace

#endif // end UTILITY_INTERPOLATION_POLICY_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_InterpolationPolicy_def.hpp
//---------------------------------------------------------------------------//
