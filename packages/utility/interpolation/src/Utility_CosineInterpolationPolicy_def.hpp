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

// FRENSIE Includes
#include "Utility_QuantityTraits.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{

// Interpolate between two points
template<bool use_nudge>
template<typename IndepType, typename DepCosineType>
inline DepCosineType LogCosLogHelper<use_nudge>::interpolate( const IndepType indep_var_0,
                                          const IndepType indep_var_1,
                                          const IndepType indep_var,
                                          const DepCosineType raw_dep_var_0,
                                          const DepCosineType raw_dep_var_1 )
{
  // The IndepType must be a floating point type
  testStaticPrecondition( (std::is_floating_point<typename QuantityTraits<IndepType>::RawType>::value) );
  testStaticPrecondition( (std::is_floating_point<typename QuantityTraits<DepCosineType>::RawType>::value) );
  // Make sure the independent variables are valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_0 ) );
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_1 ) );
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var ) );
  testPrecondition( LogCosLogHelper<use_nudge>::isIndepVarInValidRange( indep_var_0 ) );
  testPrecondition( LogCosLogHelper<use_nudge>::isIndepVarInValidRange( indep_var_1 ) );
  testPrecondition( LogCosLogHelper<use_nudge>::isIndepVarInValidRange( indep_var ) );
  testPrecondition( indep_var_0 < indep_var_1 );
  testPrecondition( indep_var >= indep_var_0 );
  testPrecondition( indep_var <= indep_var_1 );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<DepCosineType>::isnaninf( raw_dep_var_0 ) );
  testPrecondition( !QuantityTraits<DepCosineType>::isnaninf( raw_dep_var_1 ) );
  testPrecondition( LogCosLogHelper<use_nudge>::isDepVarInValidRange( raw_dep_var_0 ) );
  testPrecondition( LogCosLogHelper<use_nudge>::isDepVarInValidRange( raw_dep_var_1 ) );

  DepCosineType dep_var_0 = CosNudgeHelper<use_nudge>::convertFromCosineVar(raw_dep_var_0);
  DepCosineType dep_var_1 = CosNudgeHelper<use_nudge>::convertFromCosineVar(raw_dep_var_1);

  return CosNudgeHelper<use_nudge>::convertToCosineVar( dep_var_0*
            pow((dep_var_1/dep_var_0),
            log(indep_var/indep_var_0)/log(indep_var_1/indep_var_0)) );
}

// Interpolate between two points using the indep variable ratio (beta)
template<bool use_nudge>
template<typename T, typename DepCosineType>
inline DepCosineType LogCosLogHelper<use_nudge>::interpolate( const T beta,
                                          const DepCosineType raw_dep_var_0,
                                          const DepCosineType raw_dep_var_1 )
{
  // The IndepType must be a floating point type
  testStaticPrecondition( (std::is_floating_point<typename QuantityTraits<T>::RawType>::value) );
  testStaticPrecondition( (std::is_floating_point<typename QuantityTraits<DepCosineType>::RawType>::value) );
  // Make sure the independent variables are valid
  testPrecondition( beta >= QuantityTraits<T>::zero() );
  testPrecondition( beta <= QuantityTraits<T>::one() );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<DepCosineType>::isnaninf( raw_dep_var_0 ) );
  testPrecondition( !QuantityTraits<DepCosineType>::isnaninf( raw_dep_var_1 ) );
  testPrecondition( LogCosLogHelper<use_nudge>::isDepVarInValidRange( raw_dep_var_0 ) );
  testPrecondition( LogCosLogHelper<use_nudge>::isDepVarInValidRange( raw_dep_var_1 ) );

  DepCosineType dep_var_0 = CosNudgeHelper<use_nudge>::convertFromCosineVar(raw_dep_var_0);
  DepCosineType dep_var_1 = CosNudgeHelper<use_nudge>::convertFromCosineVar(raw_dep_var_1);

  return CosNudgeHelper<use_nudge>::convertToCosineVar( dep_var_0*pow((dep_var_1/dep_var_0),beta) );
}

// Interpolate between two points and return the processed value
template<bool use_nudge>
template<typename IndepType, typename DepCosineType>
inline typename QuantityTraits<DepCosineType>::RawType
LogCosLogHelper<use_nudge>::interpolateAndProcess( const IndepType indep_var_0,
                                  const IndepType indep_var_1,
                                  const IndepType indep_var,
                                  const DepCosineType raw_dep_var_0,
                                  const DepCosineType raw_dep_var_1 )
{
  // T must be a floating point type
  testStaticPrecondition( (std::is_floating_point<typename QuantityTraits<IndepType>::RawType>::value) );
  testStaticPrecondition( (std::is_floating_point<typename QuantityTraits<DepCosineType>::RawType>::value) );
  // Make sure the independent variables are valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_0 ) );
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_1 ) );
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var ) );
  testPrecondition( LogCosLogHelper<use_nudge>::isIndepVarInValidRange( indep_var_0 ) );
  testPrecondition( LogCosLogHelper<use_nudge>::isIndepVarInValidRange( indep_var_1 ) );
  testPrecondition( LogCosLogHelper<use_nudge>::isIndepVarInValidRange( indep_var ) );
  testPrecondition( indep_var_0 < indep_var_1 );
  testPrecondition( indep_var >= indep_var_0 );
  testPrecondition( indep_var <= indep_var_1 );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<DepCosineType>::isnaninf( raw_dep_var_0 ) );
  testPrecondition( !QuantityTraits<DepCosineType>::isnaninf( raw_dep_var_1 ) );
  testPrecondition( LogCosLogHelper<use_nudge>::isDepVarInValidRange( raw_dep_var_0 ) );
  testPrecondition( LogCosLogHelper<use_nudge>::isDepVarInValidRange( raw_dep_var_1 ) );

  DepCosineType dep_var_0 = CosNudgeHelper<use_nudge>::convertFromCosineVar(raw_dep_var_0);
  DepCosineType dep_var_1 = CosNudgeHelper<use_nudge>::convertFromCosineVar(raw_dep_var_1);

  return log( getRawQuantity(dep_var_0) ) + log ( dep_var_1/dep_var_0 )*
         log( indep_var/indep_var_0 )/log( indep_var_1/indep_var_0 );
}

// Process the independent value
template<bool use_nudge>
template<typename T>
inline typename QuantityTraits<T>::RawType
LogCosLogHelper<use_nudge>::processIndepVar( const T indep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( LogCosLogHelper<use_nudge>::isIndepVarInValidRange( indep_var ) );

  return log( getRawQuantity(indep_var) );
}

// Process the dependent value
template<bool use_nudge>
template<typename T>
inline typename QuantityTraits<T>::RawType
LogCosLogHelper<use_nudge>::processDepVar( const T dep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( LogCosLogHelper<use_nudge>::isDepVarInValidRange( dep_var ) );

  return log( CosNudgeHelper<use_nudge>::convertFromCosineVar( getRawQuantity(dep_var) ) );
}

// Recover the processed independent value
template<bool use_nudge>
template<typename T>
inline T LogCosLogHelper<use_nudge>::recoverProcessedIndepVar( const T processed_indep_var )
{
  return exp( processed_indep_var );
}

// Recover the processed dependent value
template<bool use_nudge>
template<typename T>
inline T LogCosLogHelper<use_nudge>::recoverProcessedDepVar( const T processed_dep_var )
{
  return CosNudgeHelper<use_nudge>::convertToCosineVar( exp( processed_dep_var ) );
}

// Test if the independent value is in a valid range (doesn't check nan/inf)
template<bool use_nudge>
template<typename T>
inline bool LogCosLogHelper<use_nudge>::isIndepVarInValidRange( const T indep_var )
{
  return indep_var > QuantityTraits<T>::zero();
}

// Test if the dependent value is in a valid range (doesn't check nan/inf)
template<>
template<typename T>
inline bool LogCosLogHelper<true>::isDepVarInValidRange( const T dep_var )
{
  // Make sure the indep var is not inf or nan
  testPrecondition( !QuantityTraits<T>::isnaninf( dep_var ) );

  return dep_var >= QuantityTraits<T>::initializeQuantity(-1.0) &&
         dep_var <= QuantityTraits<T>::one();
}

// Test if the dependent value is in a valid range (doesn't check nan/inf)
template<>
template<typename T>
inline bool LogCosLogHelper<false>::isDepVarInValidRange( const T dep_var )
{
  // Make sure the indep var is not inf or nan
  testPrecondition( !QuantityTraits<T>::isnaninf( dep_var ) );

  return dep_var >= QuantityTraits<T>::initializeQuantity(-1.0) &&
         dep_var < QuantityTraits<T>::one();
}

// Get the interpolation type
inline InterpolationType LogCosLog::getInterpolationType()
{
  return LOGCOSLOG_INTERPOLATION;
}

// The name of the policy
inline const std::string LogCosLog::name()
{
  return "LogCosLog";
}

// Get the interpolation type
inline InterpolationType NudgedLogCosLog::getInterpolationType()
{
  return NUDGEDLOGCOSLOG_INTERPOLATION;
}

// The name of the policy
inline const std::string NudgedLogCosLog::name()
{
  return "NudgedLogCosLog";
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
InterpolationHelper<LogLogCosHelper<false> >::calculateUnitBaseGridLength(
                                       const IndepType grid_lower_indep_value,
                                       const IndepType grid_upper_indep_value )
{
  // Make sure the grid is valid
  testPrecondition( grid_lower_indep_value <= grid_upper_indep_value );
  testPrecondition( LinLogCosHelper<false>::isIndepVarInValidRange( grid_lower_indep_value ) );

  return ThisType::calculateUnitBaseGridLengthProcessed(
          LinLogCosHelper<false>::processIndepVar( grid_upper_indep_value ),
          LinLogCosHelper<false>::processIndepVar( grid_lower_indep_value ) );
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
InterpolationHelper<LogLogCosHelper<true> >::calculateUnitBaseGridLength(
                                       const IndepType grid_lower_indep_value,
                                       const IndepType grid_upper_indep_value )
{
  // Make sure the grid is valid
  testPrecondition( grid_lower_indep_value <= grid_upper_indep_value );
  testPrecondition( LinLogCosHelper<true>::isIndepVarInValidRange( grid_lower_indep_value ) );

  return ThisType::calculateUnitBaseGridLengthProcessed(
          LinLogCosHelper<true>::processIndepVar( grid_upper_indep_value ),
          LinLogCosHelper<true>::processIndepVar( grid_lower_indep_value ) );
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
InterpolationHelper<LogLogCosHelper<false> >::calculateUnitBaseIndepVar(
          const IndepType indep_var,
          const IndepType indep_var_min,
          const typename QuantityTraits<IndepType>::RawType indep_grid_length,
          const double tol )
{
  // Make sure the intermediate grid min indep var is valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_min ) );
  testPrecondition( LogLogCosHelper<false>::isIndepVarInValidRange( indep_var_min ) );
  // Make sure the intermediate grid length is valid
  testPrecondition( !QuantityTraits<typename QuantityTraits<IndepType>::RawType>::isnaninf( indep_grid_length ) );
  testPrecondition( indep_grid_length > 0.0 );
  // Make sure the independent variable is valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var ) );
  testPrecondition( LogLogCosHelper<false>::isIndepVarInValidRange( indep_var ) );
  testPrecondition( indep_var >=
                    ThisType::calculateFuzzyLowerBound( indep_var_min, tol ) );
  remember( typename QuantityTraits<IndepType>::RawType test_difference =
            LogLogCosHelper<false>::processIndepVar(indep_var) -
            LogLogCosHelper<false>::processIndepVar(indep_var_min) );

  testPrecondition( test_difference <= ThisType::calculateFuzzyUpperBound(
                                                    indep_grid_length, tol ) );

  return calculateUnitBaseIndepVarProcessed(
                       LogLogCosHelper<false>::processIndepVar(indep_var_min),
                       LogLogCosHelper<false>::processIndepVar(indep_var),
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
InterpolationHelper<LogLogCosHelper<true> >::calculateUnitBaseIndepVar(
          const IndepType indep_var,
          const IndepType indep_var_min,
          const typename QuantityTraits<IndepType>::RawType indep_grid_length,
          const double tol )
{
  // Make sure the intermediate grid min indep var is valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_min ) );
  testPrecondition( LogLogCosHelper<true>::isIndepVarInValidRange( indep_var_min ) );
  // Make sure the intermediate grid length is valid
  testPrecondition( !QuantityTraits<typename QuantityTraits<IndepType>::RawType>::isnaninf( indep_grid_length ) );
  testPrecondition( indep_grid_length > 0.0 );
  // Make sure the independent variable is valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var ) );
  testPrecondition( LogLogCosHelper<true>::isIndepVarInValidRange( indep_var ) );
  testPrecondition( indep_var >=
                    ThisType::calculateFuzzyLowerBound( indep_var_min, tol ) );
  remember( typename QuantityTraits<IndepType>::RawType test_difference =
            LogLogCosHelper<true>::processIndepVar(indep_var) -
            LogLogCosHelper<true>::processIndepVar(indep_var_min) );

  testPrecondition( test_difference <= ThisType::calculateFuzzyUpperBound(
                                                    indep_grid_length, tol ) );

  return calculateUnitBaseIndepVarProcessed(
                       LogLogCosHelper<true>::processIndepVar(indep_var_min),
                       LogLogCosHelper<true>::processIndepVar(indep_var),
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
InterpolationHelper<LogLogCosHelper<false> >::calculateIndepVar(
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
  testPrecondition( LogLogCosHelper<false>::isIndepVarInValidRange( indep_var_min ) );
  // Make sure the grid length is valid
  testPrecondition( !QuantityTraits<typename QuantityTraits<IndepType>::RawType>::isnaninf( indep_grid_length ) );
  testPrecondition( indep_grid_length >= 0.0 );

  IndepType grid_indep_var( QuantityTraits<IndepType>::initializeQuantity(
    LogLogCosHelper<false>::recoverProcessedIndepVar(
                    LogLogCosHelper<false>::processIndepVar( indep_var_min ) -
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
InterpolationHelper<LogLogCosHelper<true> >::calculateIndepVar(
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
  testPrecondition( LogLogCosHelper<true>::isIndepVarInValidRange( indep_var_min ) );
  // Make sure the grid length is valid
  testPrecondition( !QuantityTraits<typename QuantityTraits<IndepType>::RawType>::isnaninf( indep_grid_length ) );
  testPrecondition( indep_grid_length >= 0.0 );

  IndepType grid_indep_var( QuantityTraits<IndepType>::initializeQuantity(
    LogLogCosHelper<true>::recoverProcessedIndepVar(
                    LogLogCosHelper<true>::processIndepVar( indep_var_min ) -
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
inline DepType LogLogCosHelper<use_nudge>::interpolate( const IndepCosineType raw_indep_var_0,
                                       const IndepCosineType raw_indep_var_1,
                                       const IndepCosineType raw_indep_var,
                                       const DepType dep_var_0,
                                       const DepType dep_var_1 )
{
  // The IndepCosineType must be a floating point type
  testStaticPrecondition( (std::is_floating_point<typename QuantityTraits<IndepCosineType>::RawType>::value) );
  testStaticPrecondition( (std::is_floating_point<typename QuantityTraits<DepType>::RawType>::value) );
  // Make sure the independent variables are valid
  testPrecondition( !QuantityTraits<IndepCosineType>::isnaninf( raw_indep_var_0 ) );
  testPrecondition( !QuantityTraits<IndepCosineType>::isnaninf( raw_indep_var_1 ) );
  testPrecondition( !QuantityTraits<IndepCosineType>::isnaninf( raw_indep_var ) );
  testPrecondition( LogLogCosHelper<use_nudge>::isIndepVarInValidRange( raw_indep_var_0 ) );
  testPrecondition( LogLogCosHelper<use_nudge>::isIndepVarInValidRange( raw_indep_var_1 ) );
  testPrecondition( LogLogCosHelper<use_nudge>::isIndepVarInValidRange( raw_indep_var ) );
  testPrecondition( raw_indep_var_0 < raw_indep_var_1 );
  testPrecondition( raw_indep_var >= raw_indep_var_0 );
  testPrecondition( raw_indep_var <= raw_indep_var_1 );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_0 ) );
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_1 ) );
  testPrecondition( LogLogCosHelper<use_nudge>::isDepVarInValidRange( dep_var_0 ) );
  testPrecondition( LogLogCosHelper<use_nudge>::isDepVarInValidRange( dep_var_1 ) );

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
T InterpolationHelper<LogLogCosHelper<false> >::interpolate( const T processed_indep_var_0,
                                               const T processed_indep_var,
                                               const T processed_dep_var_0,
                                               const T processed_slope )
{
  // T must be a floating point type
  testStaticPrecondition( (std::is_floating_point<T>::value) );
  // Make sure the processed independent variables are valid
  testPrecondition( !Utility::QuantityTraits<T>::isnaninf( processed_indep_var_0 ) );
  testPrecondition( !Utility::QuantityTraits<T>::isnaninf( processed_indep_var ) );
  testPrecondition( processed_indep_var <= processed_indep_var_0 );
  // Make sure the processed dependent variable is valid
  testPrecondition( !Utility::QuantityTraits<T>::isnaninf( processed_dep_var_0 ) );
  // Make sure that the slope is valid
  testPrecondition( !Utility::QuantityTraits<T>::isnaninf( processed_slope ) );

  return LogLogCosHelper<false>::recoverProcessedDepVar(
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
T InterpolationHelper<LogLogCosHelper<true> >::interpolate( const T processed_indep_var_0,
                                               const T processed_indep_var,
                                               const T processed_dep_var_0,
                                               const T processed_slope )
{
  // T must be a floating point type
  testStaticPrecondition( (boost::is_floating_point<T>::value) );
  // Make sure the processed independent variables are valid
  testPrecondition( !QuantityTraits<T>::isnaninf( processed_indep_var_0 ) );
  testPrecondition( !QuantityTraits<T>::isnaninf( processed_indep_var ) );
  testPrecondition( processed_indep_var <= processed_indep_var_0 );
  // Make sure the processed dependent variable is valid
  testPrecondition( !QuantityTraits<T>::isnaninf( processed_dep_var_0 ) );
  // Make sure that the slope is valid
  testPrecondition( !QuantityTraits<T>::isnaninf( processed_slope ) );

  return LogLogCosHelper<true>::recoverProcessedDepVar(
               processed_dep_var_0 +
               processed_slope*(processed_indep_var_0 - processed_indep_var) );
}

// Interpolate between two points using the indep variable ratio (beta)
template<bool use_nudge>
template<typename T, typename DepType>
inline DepType LogLogCosHelper<use_nudge>::interpolate( const T beta,
                                       const DepType dep_var_0,
                                       const DepType dep_var_1 )
{
  // T must be a floating point type
  testStaticPrecondition( (std::is_floating_point<typename QuantityTraits<T>::RawType>::value) );
  testStaticPrecondition( (std::is_floating_point<typename QuantityTraits<DepType>::RawType>::value) );
  // Make sure the independent variables are valid
  testPrecondition( beta >= QuantityTraits<T>::zero() );
  testPrecondition( beta <= QuantityTraits<T>::one() );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_0 ) );
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_1 ) );
  testPrecondition( LogLogCosHelper<use_nudge>::isDepVarInValidRange( dep_var_0 ) );
  testPrecondition( LogLogCosHelper<use_nudge>::isDepVarInValidRange( dep_var_1 ) );

  return dep_var_0*pow((dep_var_1/dep_var_0),beta);
}

// Interpolate between two points and return the processed value
template<bool use_nudge>
template<typename IndepCosineType, typename DepType>
inline typename QuantityTraits<DepType>::RawType
LogLogCosHelper<use_nudge>::interpolateAndProcess( const IndepCosineType raw_indep_var_0,
                                  const IndepCosineType raw_indep_var_1,
                                  const IndepCosineType raw_indep_var,
                                  const DepType dep_var_0,
                                  const DepType dep_var_1 )
{
  // T must be a floating point type
  testStaticPrecondition( (std::is_floating_point<typename QuantityTraits<IndepCosineType>::RawType>::value) );
  testStaticPrecondition( (std::is_floating_point<typename QuantityTraits<DepType>::RawType>::value) );
  // Make sure the independent variables are valid
  testPrecondition( !QuantityTraits<IndepCosineType>::isnaninf( raw_indep_var_0 ) );
  testPrecondition( !QuantityTraits<IndepCosineType>::isnaninf( raw_indep_var_1 ) );
  testPrecondition( !QuantityTraits<IndepCosineType>::isnaninf( raw_indep_var ) );
  testPrecondition( LogLogCosHelper<use_nudge>::isIndepVarInValidRange( raw_indep_var_0 ) );
  testPrecondition( LogLogCosHelper<use_nudge>::isIndepVarInValidRange( raw_indep_var_1 ) );
  testPrecondition( LogLogCosHelper<use_nudge>::isIndepVarInValidRange( raw_indep_var ) );
  testPrecondition( raw_indep_var_0 < raw_indep_var_1 );
  testPrecondition( raw_indep_var >= raw_indep_var_0 );
  testPrecondition( raw_indep_var <= raw_indep_var_1 );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_0 ) );
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_1 ) );
  testPrecondition( LogLogCosHelper<use_nudge>::isDepVarInValidRange( dep_var_0 ) );
  testPrecondition( LogLogCosHelper<use_nudge>::isDepVarInValidRange( dep_var_1 ) );

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
LogLogCosHelper<use_nudge>::processIndepVar( const T indep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( LogLogCosHelper<use_nudge>::isIndepVarInValidRange( indep_var ) );

  return log( CosNudgeHelper<use_nudge>::convertFromCosineVar( getRawQuantity(indep_var) ) );
}

// Process the dependent value
template<bool use_nudge>
template<typename T>
inline typename QuantityTraits<T>::RawType
LogLogCosHelper<use_nudge>::processDepVar( const T dep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( LogLogCosHelper<use_nudge>::isDepVarInValidRange( dep_var ) );

  return log( getRawQuantity(dep_var) );
}

// Recover the processed independent value
template<bool use_nudge>
template<typename T>
inline T LogLogCosHelper<use_nudge>::recoverProcessedIndepVar( const T processed_indep_var )
{
  return CosNudgeHelper<use_nudge>::convertToCosineVar( exp( processed_indep_var ) );
}

// Recover the processed dependent value
template<bool use_nudge>
template<typename T>
inline T LogLogCosHelper<use_nudge>::recoverProcessedDepVar( const T processed_dep_var )
{
  return exp( processed_dep_var );
}

// Test if the independent value is in a valid range (doesn't check nan/inf)
template<>
template<typename T>
inline bool LogLogCosHelper<false>::isIndepVarInValidRange( const T indep_var )
{
  return indep_var >= QuantityTraits<T>::initializeQuantity(-1.0) &&
         indep_var < QuantityTraits<T>::one();
}

// Test if the independent value is in a valid range (doesn't check nan/inf)
template<>
template<typename T>
inline bool LogLogCosHelper<true>::isIndepVarInValidRange( const T indep_var )
{
  return indep_var >= QuantityTraits<T>::initializeQuantity(-1.0) &&
         indep_var <= QuantityTraits<T>::one();
}


// Test if the dependent value is in a valid range (doesn't check nan/inf)
template<bool use_nudge>
template<typename T>
inline bool LogLogCosHelper<use_nudge>::isDepVarInValidRange( const T dep_var )
{
  // Make sure the indep var is not inf or nan
  testPrecondition( !QuantityTraits<T>::isnaninf( dep_var ) );

  return dep_var > QuantityTraits<T>::zero();
}

// Get the interpolation type
inline InterpolationType LogLogCos::getInterpolationType()
{
  return LOGLOGCOS_INTERPOLATION;
}

// The name of the policy
inline const std::string LogLogCos::name()
{
  return "LogLogCos";
}

// Get the interpolation type
inline InterpolationType LogNudgedLogCos::getInterpolationType()
{
  return LOGNUDGEDLOGCOS_INTERPOLATION;
}

// The name of the policy
inline const std::string LogNudgedLogCos::name()
{
  return "LogNudgedLogCos";
}

// Interpolate between two points
template<bool use_nudge>
template<typename IndepType, typename DepCosineType>
inline DepCosineType LogCosLinHelper<use_nudge>::interpolate( const IndepType indep_var_0,
                                          const IndepType indep_var_1,
                                          const IndepType indep_var,
                                          const DepCosineType raw_dep_var_0,
                                          const DepCosineType raw_dep_var_1 )
{
  // T must be a floating point type
  testStaticPrecondition( (std::is_floating_point<typename QuantityTraits<IndepType>::RawType>::value) );
  testStaticPrecondition( (std::is_floating_point<typename QuantityTraits<DepCosineType>::RawType>::value) );
  // Make sure the independent variables are valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_0 ) );
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_1 ) );
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var ) );
  testPrecondition( LogCosLinHelper<use_nudge>::isIndepVarInValidRange( indep_var_0 ) );
  testPrecondition( LogCosLinHelper<use_nudge>::isIndepVarInValidRange( indep_var_1 ) );
  testPrecondition( LogCosLinHelper<use_nudge>::isIndepVarInValidRange( indep_var ) );
  testPrecondition( indep_var_0 < indep_var_1 );
  testPrecondition( indep_var >= indep_var_0 );
  testPrecondition( indep_var <= indep_var_1 );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<DepCosineType>::isnaninf( raw_dep_var_0 ) );
  testPrecondition( !QuantityTraits<DepCosineType>::isnaninf( raw_dep_var_1 ) );
  testPrecondition( LogCosLinHelper<use_nudge>::isDepVarInValidRange( raw_dep_var_0 ) );
  testPrecondition( LogCosLinHelper<use_nudge>::isDepVarInValidRange( raw_dep_var_1 ) );

  DepCosineType dep_var_0 = CosNudgeHelper<use_nudge>::convertFromCosineVar(raw_dep_var_0);
  DepCosineType dep_var_1 = CosNudgeHelper<use_nudge>::convertFromCosineVar(raw_dep_var_1);

  return CosNudgeHelper<use_nudge>::convertToCosineVar( dep_var_0*pow((dep_var_1/dep_var_0),
            (indep_var-indep_var_0)/(indep_var_1-indep_var_0)) );
}

// Interpolate between two points using the indep variable ratio (beta)
template<bool use_nudge>
template<typename T, typename DepCosineType>
inline DepCosineType LogCosLinHelper<use_nudge>::interpolate( const T beta,
                                          const DepCosineType raw_dep_var_0,
                                          const DepCosineType raw_dep_var_1 )
{
  // The IndepType must be a floating point type
  testStaticPrecondition( (std::is_floating_point<typename QuantityTraits<T>::RawType>::value) );
  testStaticPrecondition( (std::is_floating_point<typename QuantityTraits<DepCosineType>::RawType>::value) );
  // Make sure the independent variables are valid
  testPrecondition( beta >= QuantityTraits<T>::zero() );
  testPrecondition( beta <= QuantityTraits<T>::one() );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<DepCosineType>::isnaninf( raw_dep_var_0 ) );
  testPrecondition( !QuantityTraits<DepCosineType>::isnaninf( raw_dep_var_1 ) );
  testPrecondition( LogCosLinHelper<use_nudge>::isDepVarInValidRange( raw_dep_var_0 ) );
  testPrecondition( LogCosLinHelper<use_nudge>::isDepVarInValidRange( raw_dep_var_1 ) );

  DepCosineType dep_var_0 = CosNudgeHelper<use_nudge>::convertFromCosineVar(raw_dep_var_0);
  DepCosineType dep_var_1 = CosNudgeHelper<use_nudge>::convertFromCosineVar(raw_dep_var_1);

  return CosNudgeHelper<use_nudge>::convertToCosineVar( dep_var_0*pow((dep_var_1/dep_var_0),beta) );
}

// Interpolate between two points and return the processed value
template<bool use_nudge>
template<typename IndepType, typename DepCosineType>
inline typename QuantityTraits<DepCosineType>::RawType
LogCosLinHelper<use_nudge>::interpolateAndProcess( const IndepType indep_var_0,
                                  const IndepType indep_var_1,
                                  const IndepType indep_var,
                                  const DepCosineType raw_dep_var_0,
                                  const DepCosineType raw_dep_var_1 )
{
  // T must be a floating point type
  testStaticPrecondition( (std::is_floating_point<typename QuantityTraits<IndepType>::RawType>::value) );
  testStaticPrecondition( (std::is_floating_point<typename QuantityTraits<DepCosineType>::RawType>::value) );
  // Make sure the independent variables are valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_0 ) );
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_1 ) );
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var ) );
  testPrecondition( LogCosLinHelper<use_nudge>::isIndepVarInValidRange( indep_var_0 ) );
  testPrecondition( LogCosLinHelper<use_nudge>::isIndepVarInValidRange( indep_var_1 ) );
  testPrecondition( LogCosLinHelper<use_nudge>::isIndepVarInValidRange( indep_var ) );
  testPrecondition( indep_var_0 < indep_var_1 );
  testPrecondition( indep_var >= indep_var_0 );
  testPrecondition( indep_var <= indep_var_1 );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<DepCosineType>::isnaninf( raw_dep_var_0 ) );
  testPrecondition( !QuantityTraits<DepCosineType>::isnaninf( raw_dep_var_1 ) );
  testPrecondition( LogCosLinHelper<use_nudge>::isDepVarInValidRange( raw_dep_var_0 ) );
  testPrecondition( LogCosLinHelper<use_nudge>::isDepVarInValidRange( raw_dep_var_1 ) );

  DepCosineType dep_var_0 = CosNudgeHelper<use_nudge>::convertFromCosineVar(raw_dep_var_0);
  DepCosineType dep_var_1 = CosNudgeHelper<use_nudge>::convertFromCosineVar(raw_dep_var_1);

  return log( getRawQuantity(dep_var_0) ) + log( dep_var_1/dep_var_0 )*
         (indep_var-indep_var_0)/(indep_var_1-indep_var_0);
}

// Process the independent value
template<bool use_nudge>
template<typename T>
inline typename QuantityTraits<T>::RawType
LogCosLinHelper<use_nudge>::processIndepVar( const T indep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( LogCosLinHelper<use_nudge>::isIndepVarInValidRange( indep_var ) );

  return getRawQuantity(indep_var);
}

// Process the dependent value
template<bool use_nudge>
template<typename T>
inline typename QuantityTraits<T>::RawType
LogCosLinHelper<use_nudge>::processDepVar( const T dep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( LogCosLinHelper<use_nudge>::isDepVarInValidRange( dep_var ) );

  return log( CosNudgeHelper<use_nudge>::convertFromCosineVar( getRawQuantity(dep_var) ) );
}

// Recover the processed independent value
template<bool use_nudge>
template<typename T>
inline T LogCosLinHelper<use_nudge>::recoverProcessedIndepVar( const T processed_indep_var )
{
  return processed_indep_var;
}

// Recover the processed dependent value
template<bool use_nudge>
template<typename T>
inline T LogCosLinHelper<use_nudge>::recoverProcessedDepVar( const T processed_dep_var )
{
  return CosNudgeHelper<use_nudge>::convertToCosineVar( exp( processed_dep_var ) );
}

// Test if the independent value is in a valid range (doesn't check nan/inf)
template<bool use_nudge>
template<typename T>
inline bool LogCosLinHelper<use_nudge>::isIndepVarInValidRange( const T indep_var )
{
  return true;
}

// Test if the dependent value is in a valid range (doesn't check nan/inf)
template<>
template<typename T>
inline bool LogCosLinHelper<false>::isDepVarInValidRange( const T dep_var )
{
  // Make sure the indep var is not inf or nan
  testPrecondition( !QuantityTraits<T>::isnaninf( dep_var ) );

  return dep_var >= QuantityTraits<T>::initializeQuantity(-1.0) &&
         dep_var < QuantityTraits<T>::one();
}

// Test if the dependent value is in a valid range (doesn't check nan/inf)
template<>
template<typename T>
inline bool LogCosLinHelper<true>::isDepVarInValidRange( const T dep_var )
{
  // Make sure the indep var is not inf or nan
  testPrecondition( !QuantityTraits<T>::isnaninf( dep_var ) );

  return dep_var >= QuantityTraits<T>::initializeQuantity(-1.0) &&
         dep_var <= QuantityTraits<T>::one();
}

// Get the interpolation type
inline InterpolationType LogCosLin::getInterpolationType()
{
  return LOGCOSLIN_INTERPOLATION;
}

// The name of the policy
inline const std::string LogCosLin::name()
{
  return "LogCosLin";
}

// Get the interpolation type
inline InterpolationType NudgedLogCosLin::getInterpolationType()
{
  return NUDGEDLOGCOSLIN_INTERPOLATION;
}

// The name of the policy
inline const std::string NudgedLogCosLin::name()
{
  return "NudgedLogCosLin";
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
InterpolationHelper<LinLogCosHelper<false> >::calculateUnitBaseGridLength(
                                       const IndepType grid_lower_indep_value,
                                       const IndepType grid_upper_indep_value )
{
  // Make sure the grid is valid
  testPrecondition( grid_lower_indep_value <= grid_upper_indep_value );
  testPrecondition( LinLogCosHelper<false>::isIndepVarInValidRange( grid_lower_indep_value ) );

  return ThisType::calculateUnitBaseGridLengthProcessed(
          LinLogCosHelper<false>::processIndepVar( grid_upper_indep_value ),
          LinLogCosHelper<false>::processIndepVar( grid_lower_indep_value ) );
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
InterpolationHelper<LinLogCosHelper<true> >::calculateUnitBaseGridLength(
                                       const IndepType grid_lower_indep_value,
                                       const IndepType grid_upper_indep_value )
{
  // Make sure the grid is valid
  testPrecondition( grid_lower_indep_value <= grid_upper_indep_value );
  testPrecondition( LinLogCosHelper<true>::isIndepVarInValidRange( grid_lower_indep_value ) );

  return ThisType::calculateUnitBaseGridLengthProcessed(
          LinLogCosHelper<true>::processIndepVar( grid_upper_indep_value ),
          LinLogCosHelper<true>::processIndepVar( grid_lower_indep_value ) );
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
InterpolationHelper<LinLogCosHelper<false> >::calculateUnitBaseIndepVar(
          const IndepType indep_var,
          const IndepType indep_var_min,
          const typename QuantityTraits<IndepType>::RawType indep_grid_length,
          const double tol )
{
  // Make sure the intermediate grid min indep var is valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_min ) );
  testPrecondition( LinLogCosHelper<false>::isIndepVarInValidRange( indep_var_min ) );
  // Make sure the intermediate grid length is valid
  testPrecondition( !QuantityTraits<typename QuantityTraits<IndepType>::RawType>::isnaninf( indep_grid_length ) );
  testPrecondition( indep_grid_length > 0.0 );
  // Make sure the independent variable is valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var ) );
  testPrecondition( LinLogCosHelper<false>::isIndepVarInValidRange( indep_var ) );
  testPrecondition( indep_var >=
                    ThisType::calculateFuzzyLowerBound( indep_var_min, tol ) );
  remember( typename QuantityTraits<IndepType>::RawType test_difference =
            LinLogCosHelper<false>::processIndepVar(indep_var) -
            LinLogCosHelper<false>::processIndepVar(indep_var_min) );

  testPrecondition( test_difference <= ThisType::calculateFuzzyUpperBound(
                                                    indep_grid_length, tol ) );

  return calculateUnitBaseIndepVarProcessed(
                       LinLogCosHelper<false>::processIndepVar(indep_var_min),
                       LinLogCosHelper<false>::processIndepVar(indep_var),
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
InterpolationHelper<LinLogCosHelper<true> >::calculateUnitBaseIndepVar(
          const IndepType indep_var,
          const IndepType indep_var_min,
          const typename QuantityTraits<IndepType>::RawType indep_grid_length,
          const double tol )
{
  // Make sure the intermediate grid min indep var is valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_min ) );
  testPrecondition( LinLogCosHelper<true>::isIndepVarInValidRange( indep_var_min ) );
  // Make sure the intermediate grid length is valid
  testPrecondition( !QuantityTraits<typename QuantityTraits<IndepType>::RawType>::isnaninf( indep_grid_length ) );
  testPrecondition( indep_grid_length > 0.0 );
  // Make sure the independent variable is valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var ) );
  testPrecondition( LinLogCosHelper<true>::isIndepVarInValidRange( indep_var ) );
  testPrecondition( indep_var >=
                    ThisType::calculateFuzzyLowerBound( indep_var_min, tol ) );
  remember( typename QuantityTraits<IndepType>::RawType test_difference =
            LinLogCosHelper<true>::processIndepVar(indep_var) -
            LinLogCosHelper<true>::processIndepVar(indep_var_min) );

  testPrecondition( test_difference <= ThisType::calculateFuzzyUpperBound(
                                                    indep_grid_length, tol ) );

  return calculateUnitBaseIndepVarProcessed(
                       LinLogCosHelper<true>::processIndepVar(indep_var_min),
                       LinLogCosHelper<true>::processIndepVar(indep_var),
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
InterpolationHelper<LinLogCosHelper<false> >::calculateIndepVar(
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
  testPrecondition( LinLogCosHelper<false>::isIndepVarInValidRange( indep_var_min ) );
  // Make sure the grid length is valid
  testPrecondition( !QuantityTraits<typename QuantityTraits<IndepType>::RawType>::isnaninf( indep_grid_length ) );
  testPrecondition( indep_grid_length >= 0.0 );

  IndepType grid_indep_var( QuantityTraits<IndepType>::initializeQuantity(
    LinLogCosHelper<false>::recoverProcessedIndepVar(
                    LinLogCosHelper<false>::processIndepVar( indep_var_min ) -
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
InterpolationHelper<LinLogCosHelper<true> >::calculateIndepVar(
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
  testPrecondition( LinLogCosHelper<true>::isIndepVarInValidRange( indep_var_min ) );
  // Make sure the grid length is valid
  testPrecondition( !QuantityTraits<typename QuantityTraits<IndepType>::RawType>::isnaninf( indep_grid_length ) );
  testPrecondition( indep_grid_length >= 0.0 );

  IndepType grid_indep_var( QuantityTraits<IndepType>::initializeQuantity(
    LinLogCosHelper<true>::recoverProcessedIndepVar(
                    LinLogCosHelper<true>::processIndepVar( indep_var_min ) -
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
inline DepType LinLogCosHelper<use_nudge>::interpolate( const IndepCosineType raw_indep_var_0,
                                       const IndepCosineType raw_indep_var_1,
                                       const IndepCosineType raw_indep_var,
                                       const DepType dep_var_0,
                                       const DepType dep_var_1 )
{
  // T must be a floating point type
  testStaticPrecondition( (std::is_floating_point<typename QuantityTraits<IndepCosineType>::RawType>::value) );
  testStaticPrecondition( (std::is_floating_point<typename QuantityTraits<DepType>::RawType>::value) );
  // Make sure the independent variables are valid
  testPrecondition( !QuantityTraits<IndepCosineType>::isnaninf( raw_indep_var_0 ) );
  testPrecondition( !QuantityTraits<IndepCosineType>::isnaninf( raw_indep_var_1 ) );
  testPrecondition( !QuantityTraits<IndepCosineType>::isnaninf( raw_indep_var ) );
  testPrecondition( LinLogCosHelper<use_nudge>::isIndepVarInValidRange( raw_indep_var_0 ) );
  testPrecondition( LinLogCosHelper<use_nudge>::isIndepVarInValidRange( raw_indep_var_1 ) );
  testPrecondition( LinLogCosHelper<use_nudge>::isIndepVarInValidRange( raw_indep_var ) );
  testPrecondition( raw_indep_var_0 < raw_indep_var_1 );
  testPrecondition( raw_indep_var >= raw_indep_var_0 );
  testPrecondition( raw_indep_var <= raw_indep_var_1 );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_0 ) );
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_1 ) );
  testPrecondition( LinLogCosHelper<use_nudge>::isDepVarInValidRange( dep_var_0 ) );
  testPrecondition( LinLogCosHelper<use_nudge>::isDepVarInValidRange( dep_var_1 ) );

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
T InterpolationHelper<LinLogCosHelper<false> >::interpolate( const T processed_indep_var_0,
                                               const T processed_indep_var,
                                               const T processed_dep_var_0,
                                               const T processed_slope )
{
  // T must be a floating point type
  testStaticPrecondition( (std::is_floating_point<T>::value) );
  // Make sure the processed independent variables are valid
  testPrecondition( !Utility::QuantityTraits<T>::isnaninf( processed_indep_var_0 ) );
  testPrecondition( !Utility::QuantityTraits<T>::isnaninf( processed_indep_var ) );
  testPrecondition( processed_indep_var <= processed_indep_var_0 );
  // Make sure the processed dependent variable is valid
  testPrecondition( !Utility::QuantityTraits<T>::isnaninf( processed_dep_var_0 ) );
  // Make sure that the slope is valid
  testPrecondition( !Utility::QuantityTraits<T>::isnaninf( processed_slope ) );

  return LinLogCosHelper<false>::recoverProcessedDepVar(
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
T InterpolationHelper<LinLogCosHelper<true> >::interpolate( const T processed_indep_var_0,
                                               const T processed_indep_var,
                                               const T processed_dep_var_0,
                                               const T processed_slope )
{
  // T must be a floating point type
  testStaticPrecondition( (boost::is_floating_point<T>::value) );
  // Make sure the processed independent variables are valid
  testPrecondition( !QuantityTraits<T>::isnaninf( processed_indep_var_0 ) );
  testPrecondition( !QuantityTraits<T>::isnaninf( processed_indep_var ) );
  testPrecondition( processed_indep_var <= processed_indep_var_0 );
  // Make sure the processed dependent variable is valid
  testPrecondition( !QuantityTraits<T>::isnaninf( processed_dep_var_0 ) );
  // Make sure that the slope is valid
  testPrecondition( !QuantityTraits<T>::isnaninf( processed_slope ) );

  return LinLogCosHelper<true>::recoverProcessedDepVar(
               processed_dep_var_0 +
               processed_slope*(processed_indep_var_0 - processed_indep_var) );
}

// Interpolate between two points using the indep variable ratio (beta)
template<bool use_nudge>
template<typename T, typename DepType>
inline DepType LinLogCosHelper<use_nudge>::interpolate( const T beta,
                                       const DepType dep_var_0,
                                       const DepType dep_var_1 )
{
  // T must be a floating point type
  testStaticPrecondition( (std::is_floating_point<typename QuantityTraits<T>::RawType>::value) );
  testStaticPrecondition( (std::is_floating_point<typename QuantityTraits<DepType>::RawType>::value) );
  // Make sure the independent variables are valid
  testPrecondition( beta >= QuantityTraits<T>::zero() );
  testPrecondition( beta <= QuantityTraits<T>::one() );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_0 ) );
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_1 ) );
  testPrecondition( LinLogCosHelper<use_nudge>::isDepVarInValidRange( dep_var_0 ) );
  testPrecondition( LinLogCosHelper<use_nudge>::isDepVarInValidRange( dep_var_1 ) );

  return dep_var_0 + (dep_var_1 - dep_var_0)*beta;
}

// Interpolate between two points and return the processed value
template<bool use_nudge>
template<typename IndepCosineType, typename DepType>
inline typename QuantityTraits<DepType>::RawType
LinLogCosHelper<use_nudge>::interpolateAndProcess( const IndepCosineType raw_indep_var_0,
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
LinLogCosHelper<use_nudge>::processIndepVar( const T indep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( LinLogCosHelper<use_nudge>::isIndepVarInValidRange( indep_var ) );

  return log( CosNudgeHelper<use_nudge>::convertFromCosineVar( getRawQuantity(indep_var) ) );
}

// Process the dependent value
template<bool use_nudge>
template<typename T>
inline typename QuantityTraits<T>::RawType
LinLogCosHelper<use_nudge>::processDepVar( const T dep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( LinLogCosHelper<use_nudge>::isDepVarInValidRange( dep_var ) );

  return getRawQuantity(dep_var);
}

// Recover the processed independent value
template<bool use_nudge>
template<typename T>
inline T LinLogCosHelper<use_nudge>::recoverProcessedIndepVar( const T processed_indep_var )
{
  return CosNudgeHelper<use_nudge>::convertToCosineVar( exp( processed_indep_var ) );
}

// Recover the processed dependent value
template<bool use_nudge>
template<typename T>
inline T LinLogCosHelper<use_nudge>::recoverProcessedDepVar( const T processed_dep_var )
{
  return processed_dep_var;
}

// Test if the independent value is in a valid range (doesn't check nan/inf)
template<>
template<typename T>
inline bool LinLogCosHelper<false>::isIndepVarInValidRange( const T indep_var )
{
  return indep_var >= QuantityTraits<T>::initializeQuantity(-1.0) &&
         indep_var < QuantityTraits<T>::one();
}

// Test if the independent value is in a valid range (doesn't check nan/inf)
template<>
template<typename T>
inline bool LinLogCosHelper<true>::isIndepVarInValidRange( const T indep_var )
{
  return indep_var >= QuantityTraits<T>::initializeQuantity(-1.0) &&
         indep_var <= QuantityTraits<T>::one();
}

// Test if the dependent value is in a valid range (doesn't check nan/inf)
template<bool use_nudge>
template<typename T>
inline bool LinLogCosHelper<use_nudge>::isDepVarInValidRange( const T dep_var )
{
  // Make sure the indep var is not inf or nan
  testPrecondition( !QuantityTraits<T>::isnaninf( dep_var ) );

  return true;
}

// Get the interpolation type
inline InterpolationType LinLogCos::getInterpolationType()
{
  return LINLOGCOS_INTERPOLATION;
}

// The name of the policy
inline const std::string LinLogCos::name()
{
  return "LinLogCos";
}

// Get the interpolation type
inline InterpolationType LinNudgedLogCos::getInterpolationType()
{
  return LINNUDGEDLOGCOS_INTERPOLATION;
}

// The name of the policy
inline const std::string LinNudgedLogCos::name()
{
  return "LinNudgedLogCos";
}

} // end Utility namespace

#endif // end UTILITY_COSINE_INTERPOLATION_POLICY_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_CosineInterpolationPolicy_def.hpp
//---------------------------------------------------------------------------//
