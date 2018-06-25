//---------------------------------------------------------------------------//
//!
//! \file   Utility_CosineInterpolationPolicy_def.hpp
//! \author Luke Kersting
//! \brief  Interpolation policy struct definitions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_COSINE_INTERPOLATION_POLICY_DEF_HPP
#define UTILITY_COSINE_INTERPOLATION_POLICY_DEF_HPP

// Std Lib Includes
#include <cmath>

// Boost Includes
#include <boost/mpl/or.hpp>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace Utility{

// Get the interpolation type
template<bool use_nudge>
inline InterpolationType LogCosLog<use_nudge>::getInterpolationType()
{
  return LOGCOSLOG_INTERPOLATION;
}

// Interpolate between two points
template<bool use_nudge>
template<typename IndepType, typename DepCosineType>
inline DepCosineType LogCosLog<use_nudge>::interpolate( const IndepType indep_var_0,
                                          const IndepType indep_var_1,
                                          const IndepType indep_var,
                                          const DepCosineType raw_dep_var_0,
                                          const DepCosineType raw_dep_var_1 )
{
  // The IndepType must be a floating point type
  testStaticPrecondition( (QuantityTraits<IndepType>::is_floating_point::value) );
  testStaticPrecondition( (QuantityTraits<DepCosineType>::is_floating_point::value) );
  // Make sure the independent variables are valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_0 ) );
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_1 ) );
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var ) );
  testPrecondition( LogCosLog<use_nudge>::isIndepVarInValidRange( indep_var_0 ) );
  testPrecondition( LogCosLog<use_nudge>::isIndepVarInValidRange( indep_var_1 ) );
  testPrecondition( LogCosLog<use_nudge>::isIndepVarInValidRange( indep_var ) );
  testPrecondition( indep_var_0 < indep_var_1 );
  testPrecondition( indep_var >= indep_var_0 );
  testPrecondition( indep_var <= indep_var_1 );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<DepCosineType>::isnaninf( raw_dep_var_0 ) );
  testPrecondition( !QuantityTraits<DepCosineType>::isnaninf( raw_dep_var_1 ) );
  testPrecondition( LogCosLog<use_nudge>::isDepVarInValidRange( raw_dep_var_0 ) );
  testPrecondition( LogCosLog<use_nudge>::isDepVarInValidRange( raw_dep_var_1 ) );

  DepCosineType dep_var_0 = CosNudgeHelper<use_nudge>::convertFromCosineVar(raw_dep_var_0);
  DepCosineType dep_var_1 = CosNudgeHelper<use_nudge>::convertFromCosineVar(raw_dep_var_1);

  return CosNudgeHelper<use_nudge>::convertToCosineVar( dep_var_0*
            pow((dep_var_1/dep_var_0),
            log(indep_var/indep_var_0)/log(indep_var_1/indep_var_0)) );
}

// Interpolate between two points using the indep variable ratio (beta)
template<bool use_nudge>
template<typename T, typename DepCosineType>
inline DepCosineType LogCosLog<use_nudge>::interpolate( const T beta,
                                          const DepCosineType raw_dep_var_0,
                                          const DepCosineType raw_dep_var_1 )
{
  // The IndepType must be a floating point type
  testStaticPrecondition( (QuantityTraits<T>::is_floating_point::value) );
  testStaticPrecondition( (QuantityTraits<DepCosineType>::is_floating_point::value) );
  // Make sure the independent variables are valid
  testPrecondition( beta >= QuantityTraits<T>::zero() );
  testPrecondition( beta <= QuantityTraits<T>::one() );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<DepCosineType>::isnaninf( raw_dep_var_0 ) );
  testPrecondition( !QuantityTraits<DepCosineType>::isnaninf( raw_dep_var_1 ) );
  testPrecondition( LogCosLog<use_nudge>::isDepVarInValidRange( raw_dep_var_0 ) );
  testPrecondition( LogCosLog<use_nudge>::isDepVarInValidRange( raw_dep_var_1 ) );

  DepCosineType dep_var_0 = CosNudgeHelper<use_nudge>::convertFromCosineVar(raw_dep_var_0);
  DepCosineType dep_var_1 = CosNudgeHelper<use_nudge>::convertFromCosineVar(raw_dep_var_1);

  return CosNudgeHelper<use_nudge>::convertToCosineVar( dep_var_0*pow((dep_var_1/dep_var_0),beta) );
}

// Interpolate between two points and return the processed value
template<bool use_nudge>
template<typename IndepType, typename DepCosineType>
inline typename QuantityTraits<DepCosineType>::RawType
LogCosLog<use_nudge>::interpolateAndProcess( const IndepType indep_var_0,
                                  const IndepType indep_var_1,
                                  const IndepType indep_var,
                                  const DepCosineType raw_dep_var_0,
                                  const DepCosineType raw_dep_var_1 )
{
  // T must be a floating point type
  testStaticPrecondition( (QuantityTraits<IndepType>::is_floating_point::value) );
  testStaticPrecondition( (QuantityTraits<DepCosineType>::is_floating_point::value) );
  // Make sure the independent variables are valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_0 ) );
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_1 ) );
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var ) );
  testPrecondition( LogCosLog<use_nudge>::isIndepVarInValidRange( indep_var_0 ) );
  testPrecondition( LogCosLog<use_nudge>::isIndepVarInValidRange( indep_var_1 ) );
  testPrecondition( LogCosLog<use_nudge>::isIndepVarInValidRange( indep_var ) );
  testPrecondition( indep_var_0 < indep_var_1 );
  testPrecondition( indep_var >= indep_var_0 );
  testPrecondition( indep_var <= indep_var_1 );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<DepCosineType>::isnaninf( raw_dep_var_0 ) );
  testPrecondition( !QuantityTraits<DepCosineType>::isnaninf( raw_dep_var_1 ) );
  testPrecondition( LogCosLog<use_nudge>::isDepVarInValidRange( raw_dep_var_0 ) );
  testPrecondition( LogCosLog<use_nudge>::isDepVarInValidRange( raw_dep_var_1 ) );

  DepCosineType dep_var_0 = CosNudgeHelper<use_nudge>::convertFromCosineVar(raw_dep_var_0);
  DepCosineType dep_var_1 = CosNudgeHelper<use_nudge>::convertFromCosineVar(raw_dep_var_1);

  return log( getRawQuantity(dep_var_0) ) + log ( dep_var_1/dep_var_0 )*
         log( indep_var/indep_var_0 )/log( indep_var_1/indep_var_0 );
}

// Process the independent value
template<bool use_nudge>
template<typename T>
inline typename QuantityTraits<T>::RawType
LogCosLog<use_nudge>::processIndepVar( const T indep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( LogCosLog<use_nudge>::isIndepVarInValidRange( indep_var ) );

  return log( getRawQuantity(indep_var) );
}

// Process the dependent value
template<bool use_nudge>
template<typename T>
inline typename QuantityTraits<T>::RawType
LogCosLog<use_nudge>::processDepVar( const T dep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( LogCosLog<use_nudge>::isDepVarInValidRange( dep_var ) );

  return log( CosNudgeHelper<use_nudge>::convertFromCosineVar( getRawQuantity(dep_var) ) );
}

// Recover the processed independent value
template<bool use_nudge>
template<typename T>
inline T LogCosLog<use_nudge>::recoverProcessedIndepVar( const T processed_indep_var )
{
  return exp( processed_indep_var );
}

// Recover the processed dependent value
template<bool use_nudge>
template<typename T>
inline T LogCosLog<use_nudge>::recoverProcessedDepVar( const T processed_dep_var )
{
  return CosNudgeHelper<use_nudge>::convertToCosineVar( exp( processed_dep_var ) );
}

// Test if the independent value is in a valid range (doesn't check nan/inf)
template<bool use_nudge>
template<typename T>
inline bool LogCosLog<use_nudge>::isIndepVarInValidRange( const T indep_var )
{
  return indep_var > QuantityTraits<T>::zero();
}

// Test if the dependent value is in a valid range (doesn't check nan/inf)
template<>
template<typename T>
inline bool LogCosLog<true>::isDepVarInValidRange( const T dep_var )
{
  // Make sure the indep var is not inf or nan
  testPrecondition( !QuantityTraits<T>::isnaninf( dep_var ) );

  return dep_var >= QuantityTraits<T>::initializeQuantity(-1.0) &&
         dep_var <= QuantityTraits<T>::one();
}

// Test if the dependent value is in a valid range (doesn't check nan/inf)
template<>
template<typename T>
inline bool LogCosLog<false>::isDepVarInValidRange( const T dep_var )
{
  // Make sure the indep var is not inf or nan
  testPrecondition( !QuantityTraits<T>::isnaninf( dep_var ) );

  return dep_var >= QuantityTraits<T>::initializeQuantity(-1.0) &&
         dep_var < QuantityTraits<T>::one();
}

// The name of the policy
template<bool use_nudge>
inline const std::string LogCosLog<use_nudge>::name()
{
  return "LogCosLog";
}

// Return if the cosine nudge factor is on
template<bool use_nudge>
inline const bool LogCosLog<use_nudge>::isCosineNudgeOn()
{
  return use_nudge;
}

// Get the interpolation type
template<bool use_nudge>
inline InterpolationType LogLogCos<use_nudge>::getInterpolationType()
{
  return LOGLOGCOS_INTERPOLATION;
}

// Calculate the unit base grid length (L)
/*! \details For LinLogCos and LogLogCos interpolation types the grid length
 * that is calculated is not a traditional length. It is the negative of the
 * distance between the processed upper independent value and the processed
 * lower independent value. This is why any units associated with the
 * independent grid limits are stripped away. Due to conversion of the
 * independent values from a cosine (mu) to a delta cosine ( 1 - mu ) + nudge
 * for LogLogCos and LinLogCos, the negative of the grid length is used to
 * ensure a positive value.
 */
template<>
template<typename IndepType>
inline typename QuantityTraits<IndepType>::RawType
InterpolationHelper<LogLogCos<false> >::calculateUnitBaseGridLength(
                                       const IndepType grid_lower_indep_value,
                                       const IndepType grid_upper_indep_value )
{
  // Make sure the grid is valid
  testPrecondition( grid_lower_indep_value <= grid_upper_indep_value );
  testPrecondition( LinLogCos<false>::isIndepVarInValidRange( grid_lower_indep_value ) );

  return ThisType::calculateUnitBaseGridLengthProcessed(
          LinLogCos<false>::processIndepVar( grid_upper_indep_value ),
          LinLogCos<false>::processIndepVar( grid_lower_indep_value ) );
}

// Calculate the unit base grid length (L)
/*! \details For LinLogCos and LogLogCos interpolation types the grid length
 * that is calculated is not a traditional length. It is the negative of the
 * distance between the processed upper independent value and the processed
 * lower independent value. This is why any units associated with the
 * independent grid limits are stripped away. Due to conversion of the
 * independent values from a cosine (mu) to a delta cosine ( 1 - mu ) + nudge
 * for LogLogCos and LinLogCos, the negative of the grid length is used to
 * ensure a positive value.
 */
template<>
template<typename IndepType>
inline typename QuantityTraits<IndepType>::RawType
InterpolationHelper<LogLogCos<true> >::calculateUnitBaseGridLength(
                                       const IndepType grid_lower_indep_value,
                                       const IndepType grid_upper_indep_value )
{
  // Make sure the grid is valid
  testPrecondition( grid_lower_indep_value <= grid_upper_indep_value );
  testPrecondition( LinLogCos<true>::isIndepVarInValidRange( grid_lower_indep_value ) );

  return ThisType::calculateUnitBaseGridLengthProcessed(
          LinLogCos<true>::processIndepVar( grid_upper_indep_value ),
          LinLogCos<true>::processIndepVar( grid_lower_indep_value ) );
}

// Calculate the unit base independent variable (eta)
/*! \details The independent grid length is calculated using the
 * processed independent grid limits. It has been found that a tolerance of
 * 1e-3 works best for most applications. Due to conversion of the independent
 * values from a cosine (mu) to a delta cosine ( 1 - mu ) + nudge for LogLogCos
 * and LinLogCos, the negative of eta is used to ensure a positive value.
 */
template<>
template<typename IndepType>
inline typename QuantityTraits<IndepType>::RawType
InterpolationHelper<LogLogCos<false> >::calculateUnitBaseIndepVar(
          const IndepType indep_var,
          const IndepType indep_var_min,
          const typename QuantityTraits<IndepType>::RawType indep_grid_length,
          const double tol )
{
  // Make sure the intermediate grid min indep var is valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_min ) );
  testPrecondition( LogLogCos<false>::isIndepVarInValidRange( indep_var_min ) );
  // Make sure the intermediate grid length is valid
  testPrecondition( !QuantityTraits<typename QuantityTraits<IndepType>::RawType>::isnaninf( indep_grid_length ) );
  testPrecondition( indep_grid_length > 0.0 );
  // Make sure the independent variable is valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var ) );
  testPrecondition( LogLogCos<false>::isIndepVarInValidRange( indep_var ) );
  testPrecondition( indep_var >=
                    ThisType::calculateFuzzyLowerBound( indep_var_min, tol ) );
  remember( typename QuantityTraits<IndepType>::RawType test_difference =
            LogLogCos<false>::processIndepVar(indep_var) -
            LogLogCos<false>::processIndepVar(indep_var_min) );

  testPrecondition( test_difference <= ThisType::calculateFuzzyUpperBound(
                                                    indep_grid_length, tol ) );

  return calculateUnitBaseIndepVarProcessed(
                       LogLogCos<false>::processIndepVar(indep_var_min),
                       LogLogCos<false>::processIndepVar(indep_var),
                       indep_grid_length,
                       tol );
}

// Calculate the unit base independent variable (eta)
/*! \details The independent grid length is calculated using the
 * processed independent grid limits. It has been found that a tolerance of
 * 1e-3 works best for most applications. Due to conversion of the independent
 * values from a cosine (mu) to a delta cosine ( 1 - mu ) + nudge for LogLogCos
 * and LinLogCos, the negative of eta is used to ensure a positive value.
 */
template<>
template<typename IndepType>
inline typename QuantityTraits<IndepType>::RawType
InterpolationHelper<LogLogCos<true> >::calculateUnitBaseIndepVar(
          const IndepType indep_var,
          const IndepType indep_var_min,
          const typename QuantityTraits<IndepType>::RawType indep_grid_length,
          const double tol )
{
  // Make sure the intermediate grid min indep var is valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_min ) );
  testPrecondition( LogLogCos<true>::isIndepVarInValidRange( indep_var_min ) );
  // Make sure the intermediate grid length is valid
  testPrecondition( !QuantityTraits<typename QuantityTraits<IndepType>::RawType>::isnaninf( indep_grid_length ) );
  testPrecondition( indep_grid_length > 0.0 );
  // Make sure the independent variable is valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var ) );
  testPrecondition( LogLogCos<true>::isIndepVarInValidRange( indep_var ) );
  testPrecondition( indep_var >=
                    ThisType::calculateFuzzyLowerBound( indep_var_min, tol ) );
  remember( typename QuantityTraits<IndepType>::RawType test_difference =
            LogLogCos<true>::processIndepVar(indep_var) -
            LogLogCos<true>::processIndepVar(indep_var_min) );

  testPrecondition( test_difference <= ThisType::calculateFuzzyUpperBound(
                                                    indep_grid_length, tol ) );

  return calculateUnitBaseIndepVarProcessed(
                       LogLogCos<true>::processIndepVar(indep_var_min),
                       LogLogCos<true>::processIndepVar(indep_var),
                       indep_grid_length,
                       tol );
}

// Calculate the independent variable (from eta)
/*! \details It has been found that a tolerance of 1e-3 works best for most
 * applications. Due to conversion of the independent values from a cosine (mu)
 * to a delta cosine ( 1 - mu ) + nudge for LogLogCos and LinLogCos, the
 * negative of eta is used to ensure a positive value.
 */
template<>
template<typename IndepType>
inline IndepType
InterpolationHelper<LogLogCos<false> >::calculateIndepVar(
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
  testPrecondition( LogLogCos<false>::isIndepVarInValidRange( indep_var_min ) );
  // Make sure the grid length is valid
  testPrecondition( !QuantityTraits<typename QuantityTraits<IndepType>::RawType>::isnaninf( indep_grid_length ) );
  testPrecondition( indep_grid_length >= 0.0 );

  IndepType grid_indep_var( QuantityTraits<IndepType>::initializeQuantity(
    LogLogCos<false>::recoverProcessedIndepVar(
                    LogLogCos<false>::processIndepVar( indep_var_min ) -
                    indep_grid_length*eta ) ) );

  // Check for rounding errors
  if( grid_indep_var < indep_var_min &&
      grid_indep_var >= ThisType::calculateFuzzyLowerBound(indep_var_min, tol))
    grid_indep_var = indep_var_min;

  // Make sure the calculated independent variable is valid
  testPostcondition( grid_indep_var >= indep_var_min );

  return grid_indep_var;
}

// Calculate the independent variable (from eta)
/*! \details It has been found that a tolerance of 1e-3 works best for most
 * applications. Due to conversion of the independent values from a cosine (mu)
 * to a delta cosine ( 1 - mu ) + nudge for LogLogCos and LinLogCos, the
 * negative of eta is used to ensure a positive value.
 */
template<>
template<typename IndepType>
inline IndepType
InterpolationHelper<LogLogCos<true> >::calculateIndepVar(
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
  testPrecondition( LogLogCos<true>::isIndepVarInValidRange( indep_var_min ) );
  // Make sure the grid length is valid
  testPrecondition( !QuantityTraits<typename QuantityTraits<IndepType>::RawType>::isnaninf( indep_grid_length ) );
  testPrecondition( indep_grid_length >= 0.0 );

  IndepType grid_indep_var( QuantityTraits<IndepType>::initializeQuantity(
    LogLogCos<true>::recoverProcessedIndepVar(
                    LogLogCos<true>::processIndepVar( indep_var_min ) -
                    indep_grid_length*eta ) ) );

  // Check for rounding errors
  if( grid_indep_var < indep_var_min &&
      grid_indep_var >= ThisType::calculateFuzzyLowerBound(indep_var_min, tol))
    grid_indep_var = indep_var_min;

  // Make sure the calculated independent variable is valid
  testPostcondition( grid_indep_var >= indep_var_min );

  return grid_indep_var;
}

// Interpolate between two points
template<bool use_nudge>
template<typename IndepCosineType, typename DepType>
inline DepType LogLogCos<use_nudge>::interpolate( const IndepCosineType raw_indep_var_0,
                                       const IndepCosineType raw_indep_var_1,
                                       const IndepCosineType raw_indep_var,
                                       const DepType dep_var_0,
                                       const DepType dep_var_1 )
{
  // The IndepCosineType must be a floating point type
  testStaticPrecondition( (QuantityTraits<IndepCosineType>::is_floating_point::value) );
  testStaticPrecondition( (QuantityTraits<DepType>::is_floating_point::value) );
  // Make sure the independent variables are valid
  testPrecondition( !QuantityTraits<IndepCosineType>::isnaninf( raw_indep_var_0 ) );
  testPrecondition( !QuantityTraits<IndepCosineType>::isnaninf( raw_indep_var_1 ) );
  testPrecondition( !QuantityTraits<IndepCosineType>::isnaninf( raw_indep_var ) );
  testPrecondition( LogLogCos<use_nudge>::isIndepVarInValidRange( raw_indep_var_0 ) );
  testPrecondition( LogLogCos<use_nudge>::isIndepVarInValidRange( raw_indep_var_1 ) );
  testPrecondition( LogLogCos<use_nudge>::isIndepVarInValidRange( raw_indep_var ) );
  testPrecondition( raw_indep_var_0 < raw_indep_var_1 );
  testPrecondition( raw_indep_var >= raw_indep_var_0 );
  testPrecondition( raw_indep_var <= raw_indep_var_1 );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_0 ) );
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_1 ) );
  testPrecondition( LogLogCos<use_nudge>::isDepVarInValidRange( dep_var_0 ) );
  testPrecondition( LogLogCos<use_nudge>::isDepVarInValidRange( dep_var_1 ) );

  IndepCosineType indep_var_0 = CosNudgeHelper<use_nudge>::convertFromCosineVar(raw_indep_var_0);
  IndepCosineType indep_var_1 = CosNudgeHelper<use_nudge>::convertFromCosineVar(raw_indep_var_1);
  IndepCosineType indep_var = CosNudgeHelper<use_nudge>::convertFromCosineVar(raw_indep_var);

  return dep_var_0*
         pow((dep_var_1/dep_var_0),
         log(indep_var/indep_var_0)/log(indep_var_1/indep_var_0));
}

// Interpolate between two processed points
/*! \details Due to conversion of the independent values from a cosine (mu)
 * to a delta cosine ( 1 - mu ) + nudge , the absolute value of the difference
 * between the processed_indep_var and processed_indep_var_0 is used for
 * LinLogCos and LogLogCos.
 */
template<>
template<typename T>
T InterpolationHelper<LogLogCos<false> >::interpolate( const T processed_indep_var_0,
                                               const T processed_indep_var,
                                               const T processed_dep_var_0,
                                               const T processed_slope )
{
  // T must be a floating point type
  testStaticPrecondition( (boost::is_floating_point<T>::value) );
  // Make sure the processed independent variables are valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( processed_indep_var_0 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( processed_indep_var ) );
  testPrecondition( processed_indep_var <= processed_indep_var_0 );
  // Make sure the processed dependent variable is valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( processed_dep_var_0 ) );
  // Make sure that the slope is valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( processed_slope ) );

  return LogLogCos<false>::recoverProcessedDepVar(
               processed_dep_var_0 +
               processed_slope*(processed_indep_var_0 - processed_indep_var) );
}

// Interpolate between two processed points
/*! \details Due to conversion of the independent values from a cosine (mu)
 * to a delta cosine ( 1 - mu ) + nudge , the absolute value of the difference
 * between the processed_indep_var and processed_indep_var_0 is used for
 * LinLogCos and LogLogCos.
 */
template<>
template<typename T>
T InterpolationHelper<LogLogCos<true> >::interpolate( const T processed_indep_var_0,
                                               const T processed_indep_var,
                                               const T processed_dep_var_0,
                                               const T processed_slope )
{
  // T must be a floating point type
  testStaticPrecondition( (boost::is_floating_point<T>::value) );
  // Make sure the processed independent variables are valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( processed_indep_var_0 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( processed_indep_var ) );
  testPrecondition( processed_indep_var <= processed_indep_var_0 );
  // Make sure the processed dependent variable is valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( processed_dep_var_0 ) );
  // Make sure that the slope is valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( processed_slope ) );

  return LogLogCos<true>::recoverProcessedDepVar(
               processed_dep_var_0 +
               processed_slope*(processed_indep_var_0 - processed_indep_var) );
}

// Interpolate between two points using the indep variable ratio (beta)
template<bool use_nudge>
template<typename T, typename DepType>
inline DepType LogLogCos<use_nudge>::interpolate( const T beta,
                                       const DepType dep_var_0,
                                       const DepType dep_var_1 )
{
  // T must be a floating point type
  testStaticPrecondition( (QuantityTraits<T>::is_floating_point::value) );
  testStaticPrecondition( (QuantityTraits<DepType>::is_floating_point::value) );
  // Make sure the independent variables are valid
  testPrecondition( beta >= QuantityTraits<T>::zero() );
  testPrecondition( beta <= QuantityTraits<T>::one() );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_0 ) );
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_1 ) );
  testPrecondition( LogLogCos<use_nudge>::isDepVarInValidRange( dep_var_0 ) );
  testPrecondition( LogLogCos<use_nudge>::isDepVarInValidRange( dep_var_1 ) );

  return dep_var_0*pow((dep_var_1/dep_var_0),beta);
}

// Interpolate between two points and return the processed value
template<bool use_nudge>
template<typename IndepCosineType, typename DepType>
inline typename QuantityTraits<DepType>::RawType
LogLogCos<use_nudge>::interpolateAndProcess( const IndepCosineType raw_indep_var_0,
                                  const IndepCosineType raw_indep_var_1,
                                  const IndepCosineType raw_indep_var,
                                  const DepType dep_var_0,
                                  const DepType dep_var_1 )
{
  // T must be a floating point type
  testStaticPrecondition( (QuantityTraits<IndepCosineType>::is_floating_point::value) );
  testStaticPrecondition( (QuantityTraits<DepType>::is_floating_point::value) );
  // Make sure the independent variables are valid
  testPrecondition( !QuantityTraits<IndepCosineType>::isnaninf( raw_indep_var_0 ) );
  testPrecondition( !QuantityTraits<IndepCosineType>::isnaninf( raw_indep_var_1 ) );
  testPrecondition( !QuantityTraits<IndepCosineType>::isnaninf( raw_indep_var ) );
  testPrecondition( LogLogCos<use_nudge>::isIndepVarInValidRange( raw_indep_var_0 ) );
  testPrecondition( LogLogCos<use_nudge>::isIndepVarInValidRange( raw_indep_var_1 ) );
  testPrecondition( LogLogCos<use_nudge>::isIndepVarInValidRange( raw_indep_var ) );
  testPrecondition( raw_indep_var_0 < raw_indep_var_1 );
  testPrecondition( raw_indep_var >= raw_indep_var_0 );
  testPrecondition( raw_indep_var <= raw_indep_var_1 );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_0 ) );
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_1 ) );
  testPrecondition( LogLogCos<use_nudge>::isDepVarInValidRange( dep_var_0 ) );
  testPrecondition( LogLogCos<use_nudge>::isDepVarInValidRange( dep_var_1 ) );

  IndepCosineType indep_var_0 = CosNudgeHelper<use_nudge>::convertFromCosineVar(raw_indep_var_0);
  IndepCosineType indep_var_1 = CosNudgeHelper<use_nudge>::convertFromCosineVar(raw_indep_var_1);
  IndepCosineType indep_var = CosNudgeHelper<use_nudge>::convertFromCosineVar(raw_indep_var);

  return log( getRawQuantity(dep_var_0) ) + log ( dep_var_1/dep_var_0 )*
         log( indep_var_0/indep_var )/log( indep_var_0/indep_var_1 );
}

// Process the independent value
template<bool use_nudge>
template<typename T>
inline typename QuantityTraits<T>::RawType
LogLogCos<use_nudge>::processIndepVar( const T indep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( LogLogCos<use_nudge>::isIndepVarInValidRange( indep_var ) );

  return log( CosNudgeHelper<use_nudge>::convertFromCosineVar( getRawQuantity(indep_var) ) );
}

// Process the dependent value
template<bool use_nudge>
template<typename T>
inline typename QuantityTraits<T>::RawType
LogLogCos<use_nudge>::processDepVar( const T dep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( LogLogCos<use_nudge>::isDepVarInValidRange( dep_var ) );

  return log( getRawQuantity(dep_var) );
}

// Recover the processed independent value
template<bool use_nudge>
template<typename T>
inline T LogLogCos<use_nudge>::recoverProcessedIndepVar( const T processed_indep_var )
{
  return CosNudgeHelper<use_nudge>::convertToCosineVar( exp( processed_indep_var ) );
}

// Recover the processed dependent value
template<bool use_nudge>
template<typename T>
inline T LogLogCos<use_nudge>::recoverProcessedDepVar( const T processed_dep_var )
{
  return exp( processed_dep_var );
}

// Test if the independent value is in a valid range (doesn't check nan/inf)
template<>
template<typename T>
inline bool LogLogCos<false>::isIndepVarInValidRange( const T indep_var )
{
  return indep_var >= QuantityTraits<T>::initializeQuantity(-1.0) &&
         indep_var < QuantityTraits<T>::one();
}

// Test if the independent value is in a valid range (doesn't check nan/inf)
template<>
template<typename T>
inline bool LogLogCos<true>::isIndepVarInValidRange( const T indep_var )
{
  return indep_var >= QuantityTraits<T>::initializeQuantity(-1.0) &&
         indep_var <= QuantityTraits<T>::one();
}


// Test if the dependent value is in a valid range (doesn't check nan/inf)
template<bool use_nudge>
template<typename T>
inline bool LogLogCos<use_nudge>::isDepVarInValidRange( const T dep_var )
{
  // Make sure the indep var is not inf or nan
  testPrecondition( !QuantityTraits<T>::isnaninf( dep_var ) );

  return dep_var > QuantityTraits<T>::zero();
}

// The name of the policy
template<bool use_nudge>
inline const std::string LogLogCos<use_nudge>::name()
{
  return "LogLogCos";
}

// Return if the cosine nudge factor is on
template<bool use_nudge>
inline const bool LogLogCos<use_nudge>::isCosineNudgeOn()
{
  return use_nudge;
}

// Get the interpolation type
template<bool use_nudge>
inline InterpolationType LogCosLin<use_nudge>::getInterpolationType()
{
  return LOGCOSLIN_INTERPOLATION;
}

// Interpolate between two points
template<bool use_nudge>
template<typename IndepType, typename DepCosineType>
inline DepCosineType LogCosLin<use_nudge>::interpolate( const IndepType indep_var_0,
                                          const IndepType indep_var_1,
                                          const IndepType indep_var,
                                          const DepCosineType raw_dep_var_0,
                                          const DepCosineType raw_dep_var_1 )
{
  // T must be a floating point type
  testStaticPrecondition( (QuantityTraits<IndepType>::is_floating_point::value) );
  testStaticPrecondition( (QuantityTraits<DepCosineType>::is_floating_point::value) );
  // Make sure the independent variables are valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_0 ) );
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_1 ) );
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var ) );
  testPrecondition( LogCosLin<use_nudge>::isIndepVarInValidRange( indep_var_0 ) );
  testPrecondition( LogCosLin<use_nudge>::isIndepVarInValidRange( indep_var_1 ) );
  testPrecondition( LogCosLin<use_nudge>::isIndepVarInValidRange( indep_var ) );
  testPrecondition( indep_var_0 < indep_var_1 );
  testPrecondition( indep_var >= indep_var_0 );
  testPrecondition( indep_var <= indep_var_1 );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<DepCosineType>::isnaninf( raw_dep_var_0 ) );
  testPrecondition( !QuantityTraits<DepCosineType>::isnaninf( raw_dep_var_1 ) );
  testPrecondition( LogCosLin<use_nudge>::isDepVarInValidRange( raw_dep_var_0 ) );
  testPrecondition( LogCosLin<use_nudge>::isDepVarInValidRange( raw_dep_var_1 ) );

  DepCosineType dep_var_0 = CosNudgeHelper<use_nudge>::convertFromCosineVar(raw_dep_var_0);
  DepCosineType dep_var_1 = CosNudgeHelper<use_nudge>::convertFromCosineVar(raw_dep_var_1);

  return CosNudgeHelper<use_nudge>::convertToCosineVar( dep_var_0*pow((dep_var_1/dep_var_0),
            (indep_var-indep_var_0)/(indep_var_1-indep_var_0)) );
}

// Interpolate between two points using the indep variable ratio (beta)
template<bool use_nudge>
template<typename T, typename DepCosineType>
inline DepCosineType LogCosLin<use_nudge>::interpolate( const T beta,
                                          const DepCosineType raw_dep_var_0,
                                          const DepCosineType raw_dep_var_1 )
{
  // The IndepType must be a floating point type
  testStaticPrecondition( (QuantityTraits<T>::is_floating_point::value) );
  testStaticPrecondition( (QuantityTraits<DepCosineType>::is_floating_point::value) );
  // Make sure the independent variables are valid
  testPrecondition( beta >= QuantityTraits<T>::zero() );
  testPrecondition( beta <= QuantityTraits<T>::one() );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<DepCosineType>::isnaninf( raw_dep_var_0 ) );
  testPrecondition( !QuantityTraits<DepCosineType>::isnaninf( raw_dep_var_1 ) );
  testPrecondition( LogCosLin<use_nudge>::isDepVarInValidRange( raw_dep_var_0 ) );
  testPrecondition( LogCosLin<use_nudge>::isDepVarInValidRange( raw_dep_var_1 ) );

  DepCosineType dep_var_0 = CosNudgeHelper<use_nudge>::convertFromCosineVar(raw_dep_var_0);
  DepCosineType dep_var_1 = CosNudgeHelper<use_nudge>::convertFromCosineVar(raw_dep_var_1);

  return CosNudgeHelper<use_nudge>::convertToCosineVar( dep_var_0*pow((dep_var_1/dep_var_0),beta) );
}

// Interpolate between two points and return the processed value
template<bool use_nudge>
template<typename IndepType, typename DepCosineType>
inline typename QuantityTraits<DepCosineType>::RawType
LogCosLin<use_nudge>::interpolateAndProcess( const IndepType indep_var_0,
                                  const IndepType indep_var_1,
                                  const IndepType indep_var,
                                  const DepCosineType raw_dep_var_0,
                                  const DepCosineType raw_dep_var_1 )
{
  // T must be a floating point type
  testStaticPrecondition( (QuantityTraits<IndepType>::is_floating_point::value) );
  testStaticPrecondition( (QuantityTraits<DepCosineType>::is_floating_point::value) );
  // Make sure the independent variables are valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_0 ) );
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_1 ) );
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var ) );
  testPrecondition( LogCosLin<use_nudge>::isIndepVarInValidRange( indep_var_0 ) );
  testPrecondition( LogCosLin<use_nudge>::isIndepVarInValidRange( indep_var_1 ) );
  testPrecondition( LogCosLin<use_nudge>::isIndepVarInValidRange( indep_var ) );
  testPrecondition( indep_var_0 < indep_var_1 );
  testPrecondition( indep_var >= indep_var_0 );
  testPrecondition( indep_var <= indep_var_1 );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<DepCosineType>::isnaninf( raw_dep_var_0 ) );
  testPrecondition( !QuantityTraits<DepCosineType>::isnaninf( raw_dep_var_1 ) );
  testPrecondition( LogCosLin<use_nudge>::isDepVarInValidRange( raw_dep_var_0 ) );
  testPrecondition( LogCosLin<use_nudge>::isDepVarInValidRange( raw_dep_var_1 ) );

  DepCosineType dep_var_0 = CosNudgeHelper<use_nudge>::convertFromCosineVar(raw_dep_var_0);
  DepCosineType dep_var_1 = CosNudgeHelper<use_nudge>::convertFromCosineVar(raw_dep_var_1);

  return log( getRawQuantity(dep_var_0) ) + log( dep_var_1/dep_var_0 )*
         (indep_var-indep_var_0)/(indep_var_1-indep_var_0);
}

// Process the independent value
template<bool use_nudge>
template<typename T>
inline typename QuantityTraits<T>::RawType
LogCosLin<use_nudge>::processIndepVar( const T indep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( LogCosLin<use_nudge>::isIndepVarInValidRange( indep_var ) );

  return getRawQuantity(indep_var);
}

// Process the dependent value
template<bool use_nudge>
template<typename T>
inline typename QuantityTraits<T>::RawType
LogCosLin<use_nudge>::processDepVar( const T dep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( LogCosLin<use_nudge>::isDepVarInValidRange( dep_var ) );

  return log( CosNudgeHelper<use_nudge>::convertFromCosineVar( getRawQuantity(dep_var) ) );
}

// Recover the processed independent value
template<bool use_nudge>
template<typename T>
inline T LogCosLin<use_nudge>::recoverProcessedIndepVar( const T processed_indep_var )
{
  return processed_indep_var;
}

// Recover the processed dependent value
template<bool use_nudge>
template<typename T>
inline T LogCosLin<use_nudge>::recoverProcessedDepVar( const T processed_dep_var )
{
  return CosNudgeHelper<use_nudge>::convertToCosineVar( exp( processed_dep_var ) );
}

// Test if the independent value is in a valid range (doesn't check nan/inf)
template<bool use_nudge>
template<typename T>
inline bool LogCosLin<use_nudge>::isIndepVarInValidRange( const T indep_var )
{
  return true;
}

// Test if the dependent value is in a valid range (doesn't check nan/inf)
template<>
template<typename T>
inline bool LogCosLin<false>::isDepVarInValidRange( const T dep_var )
{
  // Make sure the indep var is not inf or nan
  testPrecondition( !QuantityTraits<T>::isnaninf( dep_var ) );

  return dep_var >= QuantityTraits<T>::initializeQuantity(-1.0) &&
         dep_var < QuantityTraits<T>::one();
}

// Test if the dependent value is in a valid range (doesn't check nan/inf)
template<>
template<typename T>
inline bool LogCosLin<true>::isDepVarInValidRange( const T dep_var )
{
  // Make sure the indep var is not inf or nan
  testPrecondition( !QuantityTraits<T>::isnaninf( dep_var ) );

  return dep_var >= QuantityTraits<T>::initializeQuantity(-1.0) &&
         dep_var <= QuantityTraits<T>::one();
}

// The name of the policy
template<bool use_nudge>
inline const std::string LogCosLin<use_nudge>::name()
{
  return "LogCosLin";
}

// Return if the cosine nudge factor is on
template<bool use_nudge>
inline const bool LogCosLin<use_nudge>::isCosineNudgeOn()
{
  return use_nudge;
}

// Get the interpolation type
template<bool use_nudge>
inline InterpolationType LinLogCos<use_nudge>::getInterpolationType()
{
  return LINLOGCOS_INTERPOLATION;
}

// Calculate the unit base grid length (L)
/*! \details For LinLogCos and LogLogCos interpolation types the grid length
 * that is calculated is not a traditional length. It is the negative of the
 * distance between the processed upper independent value and the processed
 * lower independent value. This is why any units associated with the
 * independent grid limits are stripped away. Due to conversion of the
 * independent values from a cosine (mu) to a delta cosine ( 1 - mu ) +nudge for
 * LogLogCos and LinLogCos, the negative of the grid length is used to ensure a
 * positive value.
 */
template<>
template<typename IndepType>
inline typename QuantityTraits<IndepType>::RawType
InterpolationHelper<LinLogCos<false> >::calculateUnitBaseGridLength(
                                       const IndepType grid_lower_indep_value,
                                       const IndepType grid_upper_indep_value )
{
  // Make sure the grid is valid
  testPrecondition( grid_lower_indep_value <= grid_upper_indep_value );
  testPrecondition( LinLogCos<false>::isIndepVarInValidRange( grid_lower_indep_value ) );

  return ThisType::calculateUnitBaseGridLengthProcessed(
          LinLogCos<false>::processIndepVar( grid_upper_indep_value ),
          LinLogCos<false>::processIndepVar( grid_lower_indep_value ) );
}

// Calculate the unit base grid length (L)
/*! \details For LinLogCos and LogLogCos interpolation types the grid length
 * that is calculated is not a traditional length. It is the negative of the
 * distance between the processed upper independent value and the processed
 * lower independent value. This is why any units associated with the
 * independent grid limits are stripped away. Due to conversion of the
 * independent values from a cosine (mu) to a delta cosine ( 1 - mu ) +nudge for
 * LogLogCos and LinLogCos, the negative of the grid length is used to ensure a
 * positive value.
 */
template<>
template<typename IndepType>
inline typename QuantityTraits<IndepType>::RawType
InterpolationHelper<LinLogCos<true> >::calculateUnitBaseGridLength(
                                       const IndepType grid_lower_indep_value,
                                       const IndepType grid_upper_indep_value )
{
  // Make sure the grid is valid
  testPrecondition( grid_lower_indep_value <= grid_upper_indep_value );
  testPrecondition( LinLogCos<true>::isIndepVarInValidRange( grid_lower_indep_value ) );

  return ThisType::calculateUnitBaseGridLengthProcessed(
          LinLogCos<true>::processIndepVar( grid_upper_indep_value ),
          LinLogCos<true>::processIndepVar( grid_lower_indep_value ) );
}

// Calculate the unit base independent variable (eta)
/*! \details The independent grid length is calculated using the
 * processed independent grid limits. It has been found that a tolerance of
 * 1e-3 works best for most applications. Due to conversion of the independent
 * values from a cosine (mu) to a delta cosine ( 1 - mu ) +nudge for LogLogCos
 * and LinLogCos, the negative of eta is used to ensure a positive value.
 */
template<>
template<typename IndepType>
inline typename QuantityTraits<IndepType>::RawType
InterpolationHelper<LinLogCos<false> >::calculateUnitBaseIndepVar(
          const IndepType indep_var,
          const IndepType indep_var_min,
          const typename QuantityTraits<IndepType>::RawType indep_grid_length,
          const double tol )
{
  // Make sure the intermediate grid min indep var is valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_min ) );
  testPrecondition( LinLogCos<false>::isIndepVarInValidRange( indep_var_min ) );
  // Make sure the intermediate grid length is valid
  testPrecondition( !QuantityTraits<typename QuantityTraits<IndepType>::RawType>::isnaninf( indep_grid_length ) );
  testPrecondition( indep_grid_length > 0.0 );
  // Make sure the independent variable is valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var ) );
  testPrecondition( LinLogCos<false>::isIndepVarInValidRange( indep_var ) );
  testPrecondition( indep_var >=
                    ThisType::calculateFuzzyLowerBound( indep_var_min, tol ) );
  remember( typename QuantityTraits<IndepType>::RawType test_difference =
            LinLogCos<false>::processIndepVar(indep_var) -
            LinLogCos<false>::processIndepVar(indep_var_min) );

  testPrecondition( test_difference <= ThisType::calculateFuzzyUpperBound(
                                                    indep_grid_length, tol ) );

  return calculateUnitBaseIndepVarProcessed(
                       LinLogCos<false>::processIndepVar(indep_var_min),
                       LinLogCos<false>::processIndepVar(indep_var),
                       indep_grid_length,
                       tol );
}

// Calculate the unit base independent variable (eta)
/*! \details The independent grid length is calculated using the
 * processed independent grid limits. It has been found that a tolerance of
 * 1e-3 works best for most applications. Due to conversion of the independent
 * values from a cosine (mu) to a delta cosine ( 1 - mu ) +nudge for LogLogCos
 * and LinLogCos, the negative of eta is used to ensure a positive value.
 */
template<>
template<typename IndepType>
inline typename QuantityTraits<IndepType>::RawType
InterpolationHelper<LinLogCos<true> >::calculateUnitBaseIndepVar(
          const IndepType indep_var,
          const IndepType indep_var_min,
          const typename QuantityTraits<IndepType>::RawType indep_grid_length,
          const double tol )
{
  // Make sure the intermediate grid min indep var is valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_min ) );
  testPrecondition( LinLogCos<true>::isIndepVarInValidRange( indep_var_min ) );
  // Make sure the intermediate grid length is valid
  testPrecondition( !QuantityTraits<typename QuantityTraits<IndepType>::RawType>::isnaninf( indep_grid_length ) );
  testPrecondition( indep_grid_length > 0.0 );
  // Make sure the independent variable is valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var ) );
  testPrecondition( LinLogCos<true>::isIndepVarInValidRange( indep_var ) );
  testPrecondition( indep_var >=
                    ThisType::calculateFuzzyLowerBound( indep_var_min, tol ) );
  remember( typename QuantityTraits<IndepType>::RawType test_difference =
            LinLogCos<true>::processIndepVar(indep_var) -
            LinLogCos<true>::processIndepVar(indep_var_min) );

  testPrecondition( test_difference <= ThisType::calculateFuzzyUpperBound(
                                                    indep_grid_length, tol ) );

  return calculateUnitBaseIndepVarProcessed(
                       LinLogCos<true>::processIndepVar(indep_var_min),
                       LinLogCos<true>::processIndepVar(indep_var),
                       indep_grid_length,
                       tol );
}

// Calculate the independent variable (from eta)
/*! \details It has been found that a tolerance of 1e-3 works best for most
 * applications. Due to conversion of the independent values from a cosine (mu)
 * to a delta cosine ( 1 - mu ) +nudge for LogLogCos and LinLogCos, the negative
 * of eta is used to ensure a positive value.
 */
template<>
template<typename IndepType>
inline IndepType
InterpolationHelper<LinLogCos<false> >::calculateIndepVar(
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
  testPrecondition( LinLogCos<false>::isIndepVarInValidRange( indep_var_min ) );
  // Make sure the grid length is valid
  testPrecondition( !QuantityTraits<typename QuantityTraits<IndepType>::RawType>::isnaninf( indep_grid_length ) );
  testPrecondition( indep_grid_length >= 0.0 );

  IndepType grid_indep_var( QuantityTraits<IndepType>::initializeQuantity(
    LinLogCos<false>::recoverProcessedIndepVar(
                    LinLogCos<false>::processIndepVar( indep_var_min ) -
                    indep_grid_length*eta ) ) );

  // Check for rounding errors
  if( grid_indep_var < indep_var_min &&
      grid_indep_var >= ThisType::calculateFuzzyLowerBound(indep_var_min, tol))
    grid_indep_var = indep_var_min;

  // Make sure the calculated independent variable is valid
  testPostcondition( grid_indep_var >= indep_var_min );

  return grid_indep_var;
}

// Calculate the independent variable (from eta)
/*! \details It has been found that a tolerance of 1e-3 works best for most
 * applications. Due to conversion of the independent values from a cosine (mu)
 * to a delta cosine ( 1 - mu ) +nudge for LogLogCos and LinLogCos, the negative
 * of eta is used to ensure a positive value.
 */
template<>
template<typename IndepType>
inline IndepType
InterpolationHelper<LinLogCos<true> >::calculateIndepVar(
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
  testPrecondition( LinLogCos<true>::isIndepVarInValidRange( indep_var_min ) );
  // Make sure the grid length is valid
  testPrecondition( !QuantityTraits<typename QuantityTraits<IndepType>::RawType>::isnaninf( indep_grid_length ) );
  testPrecondition( indep_grid_length >= 0.0 );

  IndepType grid_indep_var( QuantityTraits<IndepType>::initializeQuantity(
    LinLogCos<true>::recoverProcessedIndepVar(
                    LinLogCos<true>::processIndepVar( indep_var_min ) -
                    indep_grid_length*eta ) ) );

  // Check for rounding errors
  if( grid_indep_var < indep_var_min &&
      grid_indep_var >= ThisType::calculateFuzzyLowerBound(indep_var_min, tol))
    grid_indep_var = indep_var_min;

  // Make sure the calculated independent variable is valid
  testPostcondition( grid_indep_var >= indep_var_min );

  return grid_indep_var;
}

// Interpolate between two points
template<bool use_nudge>
template<typename IndepCosineType, typename DepType>
inline DepType LinLogCos<use_nudge>::interpolate( const IndepCosineType raw_indep_var_0,
                                       const IndepCosineType raw_indep_var_1,
                                       const IndepCosineType raw_indep_var,
                                       const DepType dep_var_0,
                                       const DepType dep_var_1 )
{
  // T must be a floating point type
  testStaticPrecondition( (QuantityTraits<IndepCosineType>::is_floating_point::value) );
  testStaticPrecondition( (QuantityTraits<DepType>::is_floating_point::value) );
  // Make sure the independent variables are valid
  testPrecondition( !QuantityTraits<IndepCosineType>::isnaninf( raw_indep_var_0 ) );
  testPrecondition( !QuantityTraits<IndepCosineType>::isnaninf( raw_indep_var_1 ) );
  testPrecondition( !QuantityTraits<IndepCosineType>::isnaninf( raw_indep_var ) );
  testPrecondition( LinLogCos<use_nudge>::isIndepVarInValidRange( raw_indep_var_0 ) );
  testPrecondition( LinLogCos<use_nudge>::isIndepVarInValidRange( raw_indep_var_1 ) );
  testPrecondition( LinLogCos<use_nudge>::isIndepVarInValidRange( raw_indep_var ) );
  testPrecondition( raw_indep_var_0 < raw_indep_var_1 );
  testPrecondition( raw_indep_var >= raw_indep_var_0 );
  testPrecondition( raw_indep_var <= raw_indep_var_1 );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_0 ) );
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_1 ) );
  testPrecondition( LinLogCos<use_nudge>::isDepVarInValidRange( dep_var_0 ) );
  testPrecondition( LinLogCos<use_nudge>::isDepVarInValidRange( dep_var_1 ) );

  // Convert cosine variables
  IndepCosineType indep_var_0 = CosNudgeHelper<use_nudge>::convertFromCosineVar(raw_indep_var_0);
  IndepCosineType indep_var_1 = CosNudgeHelper<use_nudge>::convertFromCosineVar(raw_indep_var_1);
  IndepCosineType indep_var = CosNudgeHelper<use_nudge>::convertFromCosineVar(raw_indep_var);

  DepType term_2( (dep_var_1 - dep_var_0)*log(indep_var/indep_var_0)/
                  log(indep_var_1/indep_var_0) );

  return dep_var_0 + term_2;
}

// Interpolate between two processed points
/*! \details Due to conversion of the independent values from a cosine (mu)
 * to a delta cosine ( 1 - mu ) + nudge , the absolute value of the difference
 * between the processed_indep_var and processed_indep_var_0 is used for
 * LinLogCos and LogLogCos.
 */
template<>
template<typename T>
T InterpolationHelper<LinLogCos<false> >::interpolate( const T processed_indep_var_0,
                                               const T processed_indep_var,
                                               const T processed_dep_var_0,
                                               const T processed_slope )
{
  // T must be a floating point type
  testStaticPrecondition( (boost::is_floating_point<T>::value) );
  // Make sure the processed independent variables are valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( processed_indep_var_0 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( processed_indep_var ) );
  testPrecondition( processed_indep_var <= processed_indep_var_0 );
  // Make sure the processed dependent variable is valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( processed_dep_var_0 ) );
  // Make sure that the slope is valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( processed_slope ) );

  return LinLogCos<false>::recoverProcessedDepVar(
               processed_dep_var_0 +
               processed_slope*(processed_indep_var_0 - processed_indep_var) );
}

// Interpolate between two processed points
/*! \details Due to conversion of the independent values from a cosine (mu)
 * to a delta cosine ( 1 - mu ) + nudge , the absolute value of the difference
 * between the processed_indep_var and processed_indep_var_0 is used for
 * LinLogCos and LogLogCos.
 */
template<>
template<typename T>
T InterpolationHelper<LinLogCos<true> >::interpolate( const T processed_indep_var_0,
                                               const T processed_indep_var,
                                               const T processed_dep_var_0,
                                               const T processed_slope )
{
  // T must be a floating point type
  testStaticPrecondition( (boost::is_floating_point<T>::value) );
  // Make sure the processed independent variables are valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( processed_indep_var_0 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( processed_indep_var ) );
  testPrecondition( processed_indep_var <= processed_indep_var_0 );
  // Make sure the processed dependent variable is valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( processed_dep_var_0 ) );
  // Make sure that the slope is valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( processed_slope ) );

  return LinLogCos<true>::recoverProcessedDepVar(
               processed_dep_var_0 +
               processed_slope*(processed_indep_var_0 - processed_indep_var) );
}

// Interpolate between two points using the indep variable ratio (beta)
template<bool use_nudge>
template<typename T, typename DepType>
inline DepType LinLogCos<use_nudge>::interpolate( const T beta,
                                       const DepType dep_var_0,
                                       const DepType dep_var_1 )
{
  // T must be a floating point type
  testStaticPrecondition( (QuantityTraits<T>::is_floating_point::value) );
  testStaticPrecondition( (QuantityTraits<DepType>::is_floating_point::value) );
  // Make sure the independent variables are valid
  testPrecondition( beta >= QuantityTraits<T>::zero() );
  testPrecondition( beta <= QuantityTraits<T>::one() );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_0 ) );
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_1 ) );
  testPrecondition( LinLogCos<use_nudge>::isDepVarInValidRange( dep_var_0 ) );
  testPrecondition( LinLogCos<use_nudge>::isDepVarInValidRange( dep_var_1 ) );

  return dep_var_0 + (dep_var_1 - dep_var_0)*beta;
}

// Interpolate between two points and return the processed value
template<bool use_nudge>
template<typename IndepCosineType, typename DepType>
inline typename QuantityTraits<DepType>::RawType
LinLogCos<use_nudge>::interpolateAndProcess( const IndepCosineType raw_indep_var_0,
                                  const IndepCosineType raw_indep_var_1,
                                  const IndepCosineType raw_indep_var,
                                  const DepType dep_var_0,
                                  const DepType dep_var_1 )
{
  return getRawQuantity( interpolate( raw_indep_var_0,
                                      raw_indep_var_1,
                                      raw_indep_var,
                                      dep_var_0,
                                      dep_var_1 ) );
}

// Process the independent value
template<bool use_nudge>
template<typename T>
inline typename QuantityTraits<T>::RawType
LinLogCos<use_nudge>::processIndepVar( const T indep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( LinLogCos<use_nudge>::isIndepVarInValidRange( indep_var ) );

  return log( CosNudgeHelper<use_nudge>::convertFromCosineVar( getRawQuantity(indep_var) ) );
}

// Process the dependent value
template<bool use_nudge>
template<typename T>
inline typename QuantityTraits<T>::RawType
LinLogCos<use_nudge>::processDepVar( const T dep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( LinLogCos<use_nudge>::isDepVarInValidRange( dep_var ) );

  return getRawQuantity(dep_var);
}

// Recover the processed independent value
template<bool use_nudge>
template<typename T>
inline T LinLogCos<use_nudge>::recoverProcessedIndepVar( const T processed_indep_var )
{
  return CosNudgeHelper<use_nudge>::convertToCosineVar( exp( processed_indep_var ) );
}

// Recover the processed dependent value
template<bool use_nudge>
template<typename T>
inline T LinLogCos<use_nudge>::recoverProcessedDepVar( const T processed_dep_var )
{
  return processed_dep_var;
}

// Test if the independent value is in a valid range (doesn't check nan/inf)
template<>
template<typename T>
inline bool LinLogCos<false>::isIndepVarInValidRange( const T indep_var )
{
  return indep_var >= QuantityTraits<T>::initializeQuantity(-1.0) &&
         indep_var < QuantityTraits<T>::one();
}

// Test if the independent value is in a valid range (doesn't check nan/inf)
template<>
template<typename T>
inline bool LinLogCos<true>::isIndepVarInValidRange( const T indep_var )
{
  return indep_var >= QuantityTraits<T>::initializeQuantity(-1.0) &&
         indep_var <= QuantityTraits<T>::one();
}

// Test if the dependent value is in a valid range (doesn't check nan/inf)
template<bool use_nudge>
template<typename T>
inline bool LinLogCos<use_nudge>::isDepVarInValidRange( const T dep_var )
{
  // Make sure the indep var is not inf or nan
  testPrecondition( !QuantityTraits<T>::isnaninf( dep_var ) );

  return true;
}

// The name of the policy
template<bool use_nudge>
inline const std::string LinLogCos<use_nudge>::name()
{
  return "LinLogCos";
}

// Return if the cosine nudge factor is on
template<bool use_nudge>
inline const bool LinLogCos<use_nudge>::isCosineNudgeOn()
{
  return use_nudge;
}

} // end Utility namespace

#endif // end UTILITY_COSINE_INTERPOLATION_POLICY_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_CosineInterpolationPolicy_def.hpp
//---------------------------------------------------------------------------//
