//---------------------------------------------------------------------------//
//!
//! \file   Utility_CosineInterpolationPolicy_def.hpp
//! \author Luke Kersting
//! \brief  Intrepolation policy struct definitions
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

// // Interpolate between two processed points
// template<typename ParentInterpolationType>
// template<typename T>
// T InterpolationHelper<ParentInterpolationType>::interpolate(
//                                                  const T processed_indep_var_0,
//                                                  const T processed_indep_var,
//                                                  const T processed_dep_var_0,
//                                                  const T processed_slope )
// {
//   // T must be a floating point type
//   testStaticPrecondition( (boost::is_floating_point<T>::value) );
//   // Make sure the processed independent variables are valid
//   testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( 
// 						     processed_indep_var_0 ) );
//   testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( 
// 						       processed_indep_var ) );
//   testPrecondition( processed_indep_var_0 <= processed_indep_var );
//   // Make sure the processed dependent variable is valid
//   testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( 
// 						       processed_dep_var_0 ) );
//   // Make sure that the slope is valid
//   testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( processed_slope ) );
  
//   return ParentInterpolationType::recoverProcessedDepVar(
//                processed_dep_var_0 +
//                processed_slope*(processed_indep_var - processed_indep_var_0) );
// }

// // Interpolate between two processed points and return the processed value
// template<typename ParentInterpolationType>
// template<typename T>
// T InterpolationHelper<ParentInterpolationType>::interpolateAndProcess(
//                                                  const T processed_indep_var_0,
//                                                  const T processed_indep_var,
//                                                  const T processed_dep_var_0,
//                                                  const T processed_slope )
// {
//   // T must be a floating point type
//   testStaticPrecondition( (boost::is_floating_point<T>::value) );
//   // Make sure the processed independent variables are valid
//   testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( 
// 						     processed_indep_var_0 ) );
//   testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( 
// 						       processed_indep_var ) );
//   testPrecondition( processed_indep_var_0 <= processed_indep_var );
//   // Make sure the processed dependent variable is valid
//   testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( 
// 						       processed_dep_var_0 ) );
//   // Make sure that the slope is valid
//   testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( processed_slope ) );
  
//   return processed_dep_var_0 + 
//     processed_slope*(processed_indep_var - processed_indep_var_0);
// }

// // Calculate the unit base grid length (L)
// /*! \details For LinLog and LogLog interpolation types the grid length
//  * that is calculated is not a traditional length. It is the distance between
//  * the processed upper independent value and the processed lower
//  * independent value. This is why any units associated with the independent
//  * grid limits are stripped away.
//  */
// template<typename ParentInterpolationType>
// template<typename IndepType>
// inline typename QuantityTraits<IndepType>::RawType
// InterpolationHelper<ParentInterpolationType>::calculateUnitBaseGridLength(
//                                        const IndepType grid_lower_indep_value,
//                                        const IndepType grid_upper_indep_value )
// {
//   // Make sure the grid is valid
//   testPrecondition( grid_lower_indep_value <= grid_upper_indep_value );
//   testPrecondition( ParentInterpolationType::isIndepVarInValidRange(
//                                                     grid_lower_indep_value ) );

//   return ThisType::calculateUnitBaseGridLengthProcessed(
//           ParentInterpolationType::processIndepVar( grid_lower_indep_value ),
//           ParentInterpolationType::processIndepVar( grid_upper_indep_value ) );
// }

// // Calculate the unit base grid length from a processed grid (L)
// /*! \details For LinLog and LogLog interpolation types the grid length
//  * that is calculated is not a traditional length. It is the distance between
//  * the processed upper independent value and the processed lower
//  * independent value. This is why any units associated with the independent
//  * grid limits are stripped away.
//  */
// template<typename ParentInterpolationType>
// template<typename T>
// inline T InterpolationHelper<ParentInterpolationType>::calculateUnitBaseGridLengthProcessed(
//                                      const T processed_grid_lower_indep_value,
//                                      const T processed_grid_upper_indep_value )
// {
//   // Make sure the grid is valid
//   testPrecondition( processed_grid_lower_indep_value <=
//                     processed_grid_upper_indep_value );

//   const T processed_grid_length =
//     processed_grid_upper_indep_value - processed_grid_lower_indep_value;

//   // Make sure the grid length is valid
//   testPrecondition( processed_grid_length >= 0.0 );

//   return processed_grid_length;
// }

// // Calculate the unit base independent variable (eta)
// /*! \details The independent grid length is calculated using the
//  * processed independent grid limits. It has been found that a tolerance of
//  * 1e-3 works best for most applications.
//  */
// template<typename ParentInterpolationType>
// template<typename IndepType>
// inline typename QuantityTraits<IndepType>::RawType
// InterpolationHelper<ParentInterpolationType>::calculateUnitBaseIndepVar(
//           const IndepType indep_var,
//           const IndepType indep_var_min,
//           const typename QuantityTraits<IndepType>::RawType indep_grid_length,
//           const double tol )
// {
//   // Make sure the intermediate grid min indep var is valid
//   testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_min ) );
//   testPrecondition( ParentInterpolationType::isIndepVarInValidRange( indep_var_min ) );
//   // Make sure the intermediate grid length is valid
//   testPrecondition( !QuantityTraits<typename QuantityTraits<IndepType>::RawType>::isnaninf( indep_grid_length ) );
//   testPrecondition( indep_grid_length > 0.0 );
//   // Make sure the independent variable is valid
//   testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var ) );
//   testPrecondition( ParentInterpolationType::isIndepVarInValidRange( indep_var ) );
//   testPrecondition( indep_var >=
//                     ThisType::calculateFuzzyLowerBound( indep_var_min, tol ) );
//   remember( typename QuantityTraits<IndepType>::RawType test_difference =
//             ParentInterpolationType::processIndepVar(indep_var) -
//             ParentInterpolationType::processIndepVar(indep_var_min) );

//   testPrecondition( test_difference <= ThisType::calculateFuzzyUpperBound(
//                                                     indep_grid_length, tol ) );

//   return calculateUnitBaseIndepVarProcessed(
//                        ParentInterpolationType::processIndepVar(indep_var),
//                        ParentInterpolationType::processIndepVar(indep_var_min),
//                        indep_grid_length,
//                        tol );
// }

// // Calculate the unit base independent variable (eta)
// /*! \details It has been found that a tolerance of 1e-3 works best for most 
//  * applications.
//  */
// template<typename ParentInterpolationType>
// template<typename T>
// inline T InterpolationHelper<ParentInterpolationType>::calculateUnitBaseIndepVarProcessed(
//                                                const T processed_indep_var,
//                                                const T processed_indep_var_min,
//                                                const T indep_grid_length,
//                                                const double tol )
// {
//   // Make sure the intermediate grid min indep var is valid
//   testPrecondition( !QuantityTraits<T>::isnaninf( processed_indep_var_min ) );
//   // Make sure the independent y variable is valid
//   testPrecondition( !QuantityTraits<T>::isnaninf(processed_indep_var) );
//   testPrecondition( processed_indep_var >= ThisType::calculateFuzzyLowerBound(
//                                               processed_indep_var_min, tol ) );
//   remember( T test_difference = processed_indep_var - processed_indep_var_min);
//   testPrecondition( test_difference <= ThisType::calculateFuzzyUpperBound(
//                                                     indep_grid_length, tol ) );
//   // Make sure the intermediate grid length is valid
//   testPrecondition( !QuantityTraits<T>::isnaninf( indep_grid_length ) );
//   testPrecondition( indep_grid_length > 0.0 );
  
//   T eta = (processed_indep_var - processed_indep_var_min)/indep_grid_length;

//   // Check for rounding errors and correct
//   if( eta > 1.0 )
//   {
//     if( eta - 1.0 < tol )
//       eta = 1.0;
//   }
//   else if( eta < 0.0 )
//   {
//     if( eta > -tol )
//       eta = 0.0;
//   }
  
//   // Make sure eta is valid
//   testPostcondition( eta >= 0.0 );
//   testPostcondition( eta <= 1.0 );

//   return eta;
// }

// // Calculate the independent variable (from eta)
// /*! \details It has been found that a tolerance of 1e-3 works best for most 
//  * applications. 
//  */
// template<typename ParentInterpolationType>
// template<typename IndepType>
// inline IndepType
// InterpolationHelper<ParentInterpolationType>::calculateIndepVar(
//           const typename QuantityTraits<IndepType>::RawType eta,
//           const IndepType indep_var_min,
//           const typename QuantityTraits<IndepType>::RawType indep_grid_length,
//           const double tol )
// {
//   // Make sure the eta value is valid
//   testPrecondition( eta >= 0.0 );
//   testPrecondition( eta <= 1.0 );
//   // Make sure the grid min indep var is valid
//   testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_min ) );
//   testPrecondition( ParentInterpolationType::isIndepVarInValidRange( indep_var_min ) );
//   // Make sure the grid length is valid
//   testPrecondition( !QuantityTraits<typename QuantityTraits<IndepType>::RawType>::isnaninf( indep_grid_length ) );
//   testPrecondition( indep_grid_length >= 0.0 );

//   IndepType grid_indep_var( QuantityTraits<IndepType>::initializeQuantity(
//     ParentInterpolationType::recoverProcessedIndepVar( 
//                     ParentInterpolationType::processIndepVar( indep_var_min ) +
//                     indep_grid_length*eta ) ) );

//   // Check for rounding errors
//   if( grid_indep_var < indep_var_min &&
//       grid_indep_var >= ThisType::calculateFuzzyLowerBound(indep_var_min, tol))
//     grid_indep_var = indep_var_min;

//   // Make sure the calculated independent variable is valid
//   testPostcondition( grid_indep_var >= indep_var_min );

//   return grid_indep_var;
// }

// // Calculate the processed independent variable (from eta)
// /*! \details A tolerance is not required with this method because no variable 
//  * processing is done.
//  */
// template<typename ParentInterpolationType>
// template<typename T>
// inline T InterpolationHelper<ParentInterpolationType>::calculateProcessedIndepVar(
//                                                const T eta,
//                                                const T processed_indep_var_min,
//                                                const T indep_grid_length )
// {
//   // Make sure the eta value is valid
//   testPrecondition( eta >= 0.0 );
//   testPrecondition( eta <= 1.0 );
//   // Make sure the grid min indep var is valid
//   testPrecondition( !QuantityTraits<T>::isnaninf( processed_indep_var_min ) );
//   // Make sure the grid length is valid
//   testPrecondition( !QuantityTraits<T>::isnaninf( indep_grid_length ) );
//   testPrecondition( indep_grid_length >= 0.0 );
  
//   return processed_indep_var_min + indep_grid_length*eta;
// }

// // Calculate the "fuzzy" lower bound (lower bound with roundoff tolerance)
// /*! \details It has been found that a tolerance of 1e-3 works best for most
//  * applications. 
//  */
// template<typename ParentInterpolationType>
// template<typename T>
// inline T InterpolationHelper<ParentInterpolationType>::calculateFuzzyLowerBound(
//                                                              const T value,
//                                                              const double tol )
// {
//   if( value < QuantityTraits<T>::zero() )
//     return value*(1+tol);
//   else
//     return value*(1-tol);
// }

// // Calculate the "fuzzy" upper bound (upper bound with roundoff tolerance)
// /*! \details It has been found that a tolerance of 1e-3 works best for most
//  * applications
//  */
// template<typename ParentInterpolationType>
// template<typename T>
// inline T InterpolationHelper<ParentInterpolationType>::calculateFuzzyUpperBound(
//                                                              const T value,
//                                                              const double tol )
// {
//   if( value > QuantityTraits<T>::zero() )
//     return value*(1+tol);
//   else
//     return value*(1-tol);
// }

// // Convert the cosine variable
// /*! \details This function converts from cosine (mu) to delta cosine (1 - mu) or
//  *  from delta cosine (1 - mu) back to cosine (mu).
//  */
// template<typename ParentInterpolationType>
// template<typename T>
// inline T InterpolationHelper<ParentInterpolationType>::convertCosineVar(
//           const T cosine_var )
// {
//   return QuantityTraits<T>::one() - cosine_var;
// }

// Get the interpolation type
inline InterpolationType LogCosLog::getInterpolationType()
{
  return LOGCOSLOG_INTERPOLATION;
}

// Interpolate between two points
template<typename IndepType, typename CosineType>
inline CosineType LogCosLog::interpolate( const IndepType indep_var_0,
                                          const IndepType indep_var_1,
                                          const IndepType indep_var,
                                          const CosineType raw_dep_var_0,
                                          const CosineType raw_dep_var_1 )
{
  // The IndepType must be a floating point type
  testStaticPrecondition( (QuantityTraits<IndepType>::is_floating_point::value) );
  testStaticPrecondition( (QuantityTraits<CosineType>::is_floating_point::value) );
  // Make sure the independent variables are valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_0 ) );
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_1 ) );
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var ) );
  testPrecondition( LogCosLog::isIndepVarInValidRange( indep_var_0 ) );
  testPrecondition( LogCosLog::isIndepVarInValidRange( indep_var_1 ) );
  testPrecondition( LogCosLog::isIndepVarInValidRange( indep_var ) );
  testPrecondition( indep_var_0 < indep_var_1 );
  testPrecondition( indep_var >= indep_var_0 );
  testPrecondition( indep_var <= indep_var_1 );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<CosineType>::isnaninf( raw_dep_var_0 ) );
  testPrecondition( !QuantityTraits<CosineType>::isnaninf( raw_dep_var_1 ) );
  testPrecondition( LogCosLog::isDepVarInValidRange( raw_dep_var_0 ) );
  testPrecondition( LogCosLog::isDepVarInValidRange( raw_dep_var_1 ) );

  CosineType dep_var_0 = convertCosineVar(raw_dep_var_0);
  CosineType dep_var_1 = convertCosineVar(raw_dep_var_1);

  return convertCosineVar( dep_var_0*
            pow((dep_var_1/dep_var_0),
            log(indep_var/indep_var_0)/log(indep_var_1/indep_var_0)) );
}

// Interpolate between two points using the indep variable ratio (beta)
template<typename T, typename CosineType>
inline CosineType LogCosLog::interpolate( const T beta,
                                          const CosineType raw_dep_var_0,
                                          const CosineType raw_dep_var_1 )
{
  // The IndepType must be a floating point type
  testStaticPrecondition( (QuantityTraits<T>::is_floating_point::value) );
  testStaticPrecondition( (QuantityTraits<CosineType>::is_floating_point::value) );
  // Make sure the independent variables are valid
  testPrecondition( beta >= QuantityTraits<T>::zero() );
  testPrecondition( beta <= QuantityTraits<T>::one() );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<CosineType>::isnaninf( raw_dep_var_0 ) );
  testPrecondition( !QuantityTraits<CosineType>::isnaninf( raw_dep_var_1 ) );
  testPrecondition( LogCosLog::isDepVarInValidRange( raw_dep_var_0 ) );
  testPrecondition( LogCosLog::isDepVarInValidRange( raw_dep_var_1 ) );

  CosineType dep_var_0 = convertCosineVar(raw_dep_var_0);
  CosineType dep_var_1 = convertCosineVar(raw_dep_var_1);

  return convertCosineVar( dep_var_0*pow((dep_var_1/dep_var_0),beta) );
}

// Interpolate between two points and return the processed value
template<typename IndepType, typename CosineType>
inline typename QuantityTraits<CosineType>::RawType
LogCosLog::interpolateAndProcess( const IndepType indep_var_0,
                                  const IndepType indep_var_1,
                                  const IndepType indep_var,
                                  const CosineType raw_dep_var_0,
                                  const CosineType raw_dep_var_1 )
{
  // T must be a floating point type
  testStaticPrecondition( (QuantityTraits<IndepType>::is_floating_point::value) );
  testStaticPrecondition( (QuantityTraits<CosineType>::is_floating_point::value) );
  // Make sure the independent variables are valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_0 ) );
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_1 ) );
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var ) );
  testPrecondition( LogCosLog::isIndepVarInValidRange( indep_var_0 ) );
  testPrecondition( LogCosLog::isIndepVarInValidRange( indep_var_1 ) );
  testPrecondition( LogCosLog::isIndepVarInValidRange( indep_var ) );
  testPrecondition( indep_var_0 < indep_var_1 );
  testPrecondition( indep_var >= indep_var_0 );
  testPrecondition( indep_var <= indep_var_1 );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<CosineType>::isnaninf( raw_dep_var_0 ) );
  testPrecondition( !QuantityTraits<CosineType>::isnaninf( raw_dep_var_1 ) );
  testPrecondition( LogCosLog::isDepVarInValidRange( raw_dep_var_0 ) );
  testPrecondition( LogCosLog::isDepVarInValidRange( raw_dep_var_1 ) );

  CosineType dep_var_0 = convertCosineVar(raw_dep_var_0);
  CosineType dep_var_1 = convertCosineVar(raw_dep_var_1);

  return log( getRawQuantity(dep_var_0) ) +  log ( dep_var_1/dep_var_0 )*
         log( indep_var/indep_var_0 )/log( indep_var_1/indep_var_0 );
}

// Process the independent value
template<typename T>
inline typename QuantityTraits<T>::RawType
LogCosLog::processIndepVar( const T indep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( LogCosLog::isIndepVarInValidRange( indep_var ) );

  return log( getRawQuantity(indep_var) );
}

// Process the dependent value
template<typename T>
inline typename QuantityTraits<T>::RawType
LogCosLog::processDepVar( const T dep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( LogCosLog::isDepVarInValidRange( dep_var ) );

  return log( convertCosineVar( getRawQuantity(dep_var) ) );
}

// Recover the processed independent value
template<typename T>
inline T LogCosLog::recoverProcessedIndepVar( const T processed_indep_var )
{
  return exp( processed_indep_var );
}

// Recover the processed dependent value
template<typename T>
inline T LogCosLog::recoverProcessedDepVar( const T processed_dep_var )
{
  return convertCosineVar( exp( processed_dep_var ) );
}

// Test if the independent value is in a valid range (doesn't check nan/inf)
template<typename T>
inline bool LogCosLog::isIndepVarInValidRange( const T indep_var )
{
  return indep_var > QuantityTraits<T>::zero();
}

// Test if the dependent value is in a valid range (doesn't check nan/inf)
template<typename T>
inline bool LogCosLog::isDepVarInValidRange( const T dep_var )
{
  // Make sure the indep var is not inf or nan
  testPrecondition( !QuantityTraits<T>::isnaninf( dep_var ) );
  
  return dep_var >= QuantityTraits<T>::initializeQuantity(-1.0) &&
         dep_var < QuantityTraits<T>::one();
}

// The name of the policy
inline const std::string LogCosLog::name()
{
  return "LogCosLog";
}

// Get the interpolation type
inline InterpolationType LogLogCos::getInterpolationType()
{
  return LOGLOGCOS_INTERPOLATION;
}

// // Calculate the unit base grid length (L)
// /*! \details For LinLogCos and LogLogCos interpolation types the grid length
//  * that is calculated is not a traditional length. It is the negative of the
//  * distance between the processed upper independent value and the processed
//  * lower independent value. This is why any units associated with the independent
//  * grid limits are stripped away. Due to conversion of the independent
//  * values from a cosine (mu) to a delta cosine ( 1 - mu ) for LogLogCos and
//  * LinLogCos, the negative of the grid length is used to ensure a positive value.
//  */
// template<>
// template<typename IndepType>
// inline typename QuantityTraits<IndepType>::RawType
// InterpolationHelper<LogLogCos>::calculateUnitBaseGridLength(
//                                        const IndepType grid_lower_indep_value,
//                                        const IndepType grid_upper_indep_value )
// {
//   // Make sure the grid is valid
//   testPrecondition( grid_lower_indep_value <= grid_upper_indep_value );
//   testPrecondition( LogLogCos::isIndepVarInValidRange( grid_lower_indep_value ) );

//   return ThisType::calculateUnitBaseGridLengthProcessed(
//           LogLogCos::processIndepVar( grid_lower_indep_value ),
//           LogLogCos::processIndepVar( grid_upper_indep_value ) );
// }

// Calculate the unit base grid length from a processed grid (L)
/*! \details For LinLogCos and LogLogCos interpolation types the grid length
 * that is calculated is not a traditional length. It is the negative of the
 * distance between the processed upper independent value and the processed
 *lower independent value. This is why any units associated with the independent
 * grid limits are stripped away. Due to conversion of the independent
 * values from a cosine (mu) to a delta cosine ( 1 - mu ) for LogLogCos and
 * LinLogCos, the negative of the grid length is used to ensure a positive value.
 */
template<>
template<typename T>
inline T InterpolationHelper<LogLogCos>::calculateUnitBaseGridLengthProcessed(
                                     const T processed_grid_lower_indep_value,
                                     const T processed_grid_upper_indep_value )
{
  // Make sure the grid is valid
  testPrecondition( processed_grid_lower_indep_value >=
                    processed_grid_upper_indep_value );

  const T processed_grid_length =
    processed_grid_lower_indep_value - processed_grid_upper_indep_value;

  // Make sure the grid length is valid
  testPrecondition( processed_grid_length >= 0.0 );

  return processed_grid_length;
}

// Calculate the unit base independent variable (eta)
/*! \details The independent grid length is calculated using the
 * processed independent grid limits. It has been found that a tolerance of
 * 1e-3 works best for most applications. Due to conversion of the independent
 * values from a cosine (mu) to a delta cosine ( 1 - mu ) for LogLogCos and
 * LinLogCos, the negative of eta is used to ensure a positive value.
 */
template<>
template<typename IndepType>
inline typename QuantityTraits<IndepType>::RawType
InterpolationHelper<LogLogCos>::calculateUnitBaseIndepVar(
          const IndepType indep_var,
          const IndepType indep_var_min,
          const typename QuantityTraits<IndepType>::RawType indep_grid_length,
          const double tol )
{
  // Make sure the intermediate grid min indep var is valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_min ) );
  testPrecondition( LogLogCos::isIndepVarInValidRange( indep_var_min ) );
  // Make sure the intermediate grid length is valid
  testPrecondition( !QuantityTraits<typename QuantityTraits<IndepType>::RawType>::isnaninf( indep_grid_length ) );
  testPrecondition( indep_grid_length > 0.0 );
  // Make sure the independent variable is valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var ) );
  testPrecondition( LogLogCos::isIndepVarInValidRange( indep_var ) );
  testPrecondition( indep_var >=
                    ThisType::calculateFuzzyLowerBound( indep_var_min, tol ) );
  remember( typename QuantityTraits<IndepType>::RawType test_difference =
            LogLogCos::processIndepVar(indep_var) -
            LogLogCos::processIndepVar(indep_var_min) );

  testPrecondition( test_difference <= ThisType::calculateFuzzyUpperBound(
                                                    indep_grid_length, tol ) );

  return calculateUnitBaseIndepVarProcessed(
                       LogLogCos::processIndepVar(indep_var_min),
                       LogLogCos::processIndepVar(indep_var),
                       indep_grid_length,
                       tol );
}

// Calculate the independent variable (from eta)
/*! \details It has been found that a tolerance of 1e-3 works best for most 
 * applications. Due to conversion of the independent values from a cosine (mu)
 * to a delta cosine ( 1 - mu ) for LogLogCos and LinLogCos, the negative of eta
 * is used to ensure a positive value.
 */
template<>
template<typename IndepType>
inline IndepType
InterpolationHelper<LogLogCos>::calculateIndepVar(
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
  testPrecondition( LogLogCos::isIndepVarInValidRange( indep_var_min ) );
  // Make sure the grid length is valid
  testPrecondition( !QuantityTraits<typename QuantityTraits<IndepType>::RawType>::isnaninf( indep_grid_length ) );
  testPrecondition( indep_grid_length >= 0.0 );

  IndepType grid_indep_var( QuantityTraits<IndepType>::initializeQuantity(
    LogLogCos::recoverProcessedIndepVar( 
                    LogLogCos::processIndepVar( indep_var_min ) -
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
/*! \details Due to conversion of the independent values from a cosine (mu)
 * to a delta cosine ( 1 - mu ) for LogLogCos and LinLogCos, the negative of eta
 * is used to ensure a positive value. A tolerance is not required with this
 * method because no variable processing is done.
 */
template<>
template<typename T>
inline T InterpolationHelper<LogLogCos>::calculateProcessedIndepVar(
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
  
  return processed_indep_var_min - indep_grid_length*eta;
}

// Interpolate between two points
template<typename CosineType, typename DepType>
inline DepType LogLogCos::interpolate( const CosineType raw_indep_var_0,
                                       const CosineType raw_indep_var_1,
                                       const CosineType raw_indep_var,
                                       const DepType dep_var_0,
                                       const DepType dep_var_1 )
{
  // The CosineType must be a floating point type
  testStaticPrecondition( (QuantityTraits<CosineType>::is_floating_point::value) );
  testStaticPrecondition( (QuantityTraits<DepType>::is_floating_point::value) );
  // Make sure the independent variables are valid
  testPrecondition( !QuantityTraits<CosineType>::isnaninf( raw_indep_var_0 ) );
  testPrecondition( !QuantityTraits<CosineType>::isnaninf( raw_indep_var_1 ) );
  testPrecondition( !QuantityTraits<CosineType>::isnaninf( raw_indep_var ) );
  testPrecondition( LogLogCos::isIndepVarInValidRange( raw_indep_var_0 ) );
  testPrecondition( LogLogCos::isIndepVarInValidRange( raw_indep_var_1 ) );
  testPrecondition( LogLogCos::isIndepVarInValidRange( raw_indep_var ) );
  testPrecondition( raw_indep_var_0 < raw_indep_var_1 );
  testPrecondition( raw_indep_var >= raw_indep_var_0 );
  testPrecondition( raw_indep_var <= raw_indep_var_1 );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_0 ) );
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_1 ) );
  testPrecondition( LogLogCos::isDepVarInValidRange( dep_var_0 ) );
  testPrecondition( LogLogCos::isDepVarInValidRange( dep_var_1 ) );

  CosineType indep_var_0 = convertCosineVar(raw_indep_var_0);
  CosineType indep_var_1 = convertCosineVar(raw_indep_var_1);
  CosineType indep_var = convertCosineVar(raw_indep_var);

  return dep_var_0*
         pow((dep_var_1/dep_var_0),
         log(indep_var/indep_var_0)/log(indep_var_1/indep_var_0));
}

// Interpolate between two processed points
/*! \details Due to conversion of the independent values from a cosine (mu)
 * to a delta cosine ( 1 - mu ), the absolute value of the difference between
 * the processed_indep_var and processed_indep_var_0 is used for
 * LinLogCos and LogLogCos.
 */
template<>
template<typename T>
T InterpolationHelper<LogLogCos>::interpolate( const T processed_indep_var_0,
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
  
  return LogLogCos::recoverProcessedDepVar(
               processed_dep_var_0 +
               processed_slope*(processed_indep_var_0 - processed_indep_var) );
}

// Interpolate between two points using the indep variable ratio (beta)
template<typename T, typename DepType>
inline DepType LogLogCos::interpolate( const T beta,
                                       const DepType dep_var_0,
                                       const DepType dep_var_1 )
{
  // The CosineType must be a floating point type
  testStaticPrecondition( (QuantityTraits<T>::is_floating_point::value) );
  testStaticPrecondition( (QuantityTraits<DepType>::is_floating_point::value) );
  // Make sure the independent variables are valid
  testPrecondition( beta >= QuantityTraits<T>::zero() );
  testPrecondition( beta <= QuantityTraits<T>::one() );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_0 ) );
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_1 ) );
  testPrecondition( LogLogCos::isDepVarInValidRange( dep_var_0 ) );
  testPrecondition( LogLogCos::isDepVarInValidRange( dep_var_1 ) );

  return dep_var_0*pow((dep_var_1/dep_var_0),beta);
}

// Interpolate between two points and return the processed value
template<typename CosineType, typename DepType>
inline typename QuantityTraits<DepType>::RawType
LogLogCos::interpolateAndProcess( const CosineType raw_indep_var_0,
                                  const CosineType raw_indep_var_1,
                                  const CosineType raw_indep_var,
                                  const DepType dep_var_0,
                                  const DepType dep_var_1 )
{
  // T must be a floating point type
  testStaticPrecondition( (QuantityTraits<CosineType>::is_floating_point::value) );
  testStaticPrecondition( (QuantityTraits<DepType>::is_floating_point::value) );
  // Make sure the independent variables are valid
  testPrecondition( !QuantityTraits<CosineType>::isnaninf( raw_indep_var_0 ) );
  testPrecondition( !QuantityTraits<CosineType>::isnaninf( raw_indep_var_1 ) );
  testPrecondition( !QuantityTraits<CosineType>::isnaninf( raw_indep_var ) );
  testPrecondition( LogLogCos::isIndepVarInValidRange( raw_indep_var_0 ) );
  testPrecondition( LogLogCos::isIndepVarInValidRange( raw_indep_var_1 ) );
  testPrecondition( LogLogCos::isIndepVarInValidRange( raw_indep_var ) );
  testPrecondition( raw_indep_var_0 < raw_indep_var_1 );
  testPrecondition( raw_indep_var >= raw_indep_var_0 );
  testPrecondition( raw_indep_var <= raw_indep_var_1 );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_0 ) );
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_1 ) );
  testPrecondition( LogLogCos::isDepVarInValidRange( dep_var_0 ) );
  testPrecondition( LogLogCos::isDepVarInValidRange( dep_var_1 ) );

  CosineType indep_var_0 = convertCosineVar(raw_indep_var_0);
  CosineType indep_var_1 = convertCosineVar(raw_indep_var_1);
  CosineType indep_var = convertCosineVar(raw_indep_var);

  return log( getRawQuantity(dep_var_0) ) + log ( dep_var_1/dep_var_0 )*
         log( indep_var_0/indep_var )/log( indep_var_0/indep_var_1 );
}

// Interpolate between two processed points and return the processed value
/*! \details Due to conversion of the independent values from a cosine (mu)
 * to a delta cosine ( 1 - mu ), the absolute value of the difference between
 * the processed_indep_var and processed_indep_var_0 is used for
 * LinLogCos and LogLogCos.
 */
template<>
template<typename T>
T InterpolationHelper<LogLogCos>::interpolateAndProcess(
                                                 const T processed_indep_var_0,
                                                 const T processed_indep_var,
                                                 const T processed_dep_var_0,
                                                 const T processed_slope )
{
  // T must be a floating point type
  testStaticPrecondition( (boost::is_floating_point<T>::value) );
  // Make sure the processed independent variables are valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( processed_indep_var_0 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( processed_indep_var ) );
  testPrecondition( processed_indep_var_0 >= processed_indep_var );
  // Make sure the processed dependent variable is valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( processed_dep_var_0 ) );
  // Make sure that the slope is valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( processed_slope ) );
  
  return processed_dep_var_0 +
    processed_slope*(processed_indep_var_0 - processed_indep_var);
}

// Process the independent value
template<typename T>
inline typename QuantityTraits<T>::RawType
LogLogCos::processIndepVar( const T indep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( LogLogCos::isIndepVarInValidRange( indep_var ) );

  return log( convertCosineVar( getRawQuantity(indep_var) ) );
}

// Process the dependent value
template<typename T>
inline typename QuantityTraits<T>::RawType
LogLogCos::processDepVar( const T dep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( LogLogCos::isDepVarInValidRange( dep_var ) );

  return log( getRawQuantity(dep_var) );
}

// Recover the processed independent value
template<typename T>
inline T LogLogCos::recoverProcessedIndepVar( const T processed_indep_var )
{
  return convertCosineVar( exp( processed_indep_var ) );
}

// Recover the processed dependent value
template<typename T>
inline T LogLogCos::recoverProcessedDepVar( const T processed_dep_var )
{
  return exp( processed_dep_var );
}

// Test if the independent value is in a valid range (doesn't check nan/inf)
template<typename T>
inline bool LogLogCos::isIndepVarInValidRange( const T indep_var )
{
  return indep_var >= QuantityTraits<T>::initializeQuantity(-1.0) &&
         indep_var < QuantityTraits<T>::one();
}

// Test if the dependent value is in a valid range (doesn't check nan/inf)
template<typename T>
inline bool LogLogCos::isDepVarInValidRange( const T dep_var )
{
  // Make sure the indep var is not inf or nan
  testPrecondition( !QuantityTraits<T>::isnaninf( dep_var ) );
  
  return dep_var > QuantityTraits<T>::zero();
}

// The name of the policy
inline const std::string LogLogCos::name()
{
  return "LogLogCos";
}

// Get the interpolation type
inline InterpolationType LogCosLin::getInterpolationType()
{
  return LOGCOSLIN_INTERPOLATION;
}

// Interpolate between two points
template<typename IndepType, typename CosineType>
inline CosineType LogCosLin::interpolate( const IndepType indep_var_0,
                                          const IndepType indep_var_1,
                                          const IndepType indep_var,
                                          const CosineType raw_dep_var_0,
                                          const CosineType raw_dep_var_1 )
{
  // T must be a floating point type
  testStaticPrecondition( (QuantityTraits<IndepType>::is_floating_point::value) );
  testStaticPrecondition( (QuantityTraits<CosineType>::is_floating_point::value) );
  // Make sure the independent variables are valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_0 ) );
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_1 ) );
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var ) );
  testPrecondition( LogCosLin::isIndepVarInValidRange( indep_var_0 ) );
  testPrecondition( LogCosLin::isIndepVarInValidRange( indep_var_1 ) );
  testPrecondition( LogCosLin::isIndepVarInValidRange( indep_var ) );
  testPrecondition( indep_var_0 < indep_var_1 );
  testPrecondition( indep_var >= indep_var_0 );
  testPrecondition( indep_var <= indep_var_1 );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<CosineType>::isnaninf( raw_dep_var_0 ) );
  testPrecondition( !QuantityTraits<CosineType>::isnaninf( raw_dep_var_1 ) );
  testPrecondition( LogCosLin::isDepVarInValidRange( raw_dep_var_0 ) );
  testPrecondition( LogCosLin::isDepVarInValidRange( raw_dep_var_1 ) );

  CosineType dep_var_0 = convertCosineVar(raw_dep_var_0);
  CosineType dep_var_1 = convertCosineVar(raw_dep_var_1);

  return convertCosineVar( dep_var_0*pow((dep_var_1/dep_var_0),
            (indep_var-indep_var_0)/(indep_var_1-indep_var_0)) );
}

// Interpolate between two points using the indep variable ratio (beta)
template<typename T, typename CosineType>
inline CosineType LogCosLin::interpolate( const T beta,
                                          const CosineType raw_dep_var_0,
                                          const CosineType raw_dep_var_1 )
{
  // The IndepType must be a floating point type
  testStaticPrecondition( (QuantityTraits<T>::is_floating_point::value) );
  testStaticPrecondition( (QuantityTraits<CosineType>::is_floating_point::value) );
  // Make sure the independent variables are valid
  testPrecondition( beta >= QuantityTraits<T>::zero() );
  testPrecondition( beta <= QuantityTraits<T>::one() );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<CosineType>::isnaninf( raw_dep_var_0 ) );
  testPrecondition( !QuantityTraits<CosineType>::isnaninf( raw_dep_var_1 ) );
  testPrecondition( LogCosLin::isDepVarInValidRange( raw_dep_var_0 ) );
  testPrecondition( LogCosLin::isDepVarInValidRange( raw_dep_var_1 ) );

  CosineType dep_var_0 = convertCosineVar(raw_dep_var_0);
  CosineType dep_var_1 = convertCosineVar(raw_dep_var_1);

  return convertCosineVar( dep_var_0*pow((dep_var_1/dep_var_0),beta) );
}

// Interpolate between two points and return the processed value
template<typename IndepType, typename CosineType>
inline typename QuantityTraits<CosineType>::RawType
LogCosLin::interpolateAndProcess( const IndepType indep_var_0,
                                  const IndepType indep_var_1,
                                  const IndepType indep_var,
                                  const CosineType raw_dep_var_0,
                                  const CosineType raw_dep_var_1 )
{
  // T must be a floating point type
  testStaticPrecondition( (QuantityTraits<IndepType>::is_floating_point::value) );
  testStaticPrecondition( (QuantityTraits<CosineType>::is_floating_point::value) );
  // Make sure the independent variables are valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_0 ) );
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_1 ) );
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var ) );
  testPrecondition( LogCosLin::isIndepVarInValidRange( indep_var_0 ) );
  testPrecondition( LogCosLin::isIndepVarInValidRange( indep_var_1 ) );
  testPrecondition( LogCosLin::isIndepVarInValidRange( indep_var ) );
  testPrecondition( indep_var_0 < indep_var_1 );
  testPrecondition( indep_var >= indep_var_0 );
  testPrecondition( indep_var <= indep_var_1 );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<CosineType>::isnaninf( raw_dep_var_0 ) );
  testPrecondition( !QuantityTraits<CosineType>::isnaninf( raw_dep_var_1 ) );
  testPrecondition( LogCosLin::isDepVarInValidRange( raw_dep_var_0 ) );
  testPrecondition( LogCosLin::isDepVarInValidRange( raw_dep_var_1 ) );

  CosineType dep_var_0 = convertCosineVar(raw_dep_var_0);
  CosineType dep_var_1 = convertCosineVar(raw_dep_var_1);

  return log( getRawQuantity(dep_var_0) ) + log( dep_var_1/dep_var_0 )*
         (indep_var-indep_var_0)/(indep_var_1-indep_var_0);
}

// Process the independent value
template<typename T>
inline typename QuantityTraits<T>::RawType
LogCosLin::processIndepVar( const T indep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( LogCosLin::isIndepVarInValidRange( indep_var ) );

  return getRawQuantity(indep_var);
}

// Process the dependent value
template<typename T>
inline typename QuantityTraits<T>::RawType
LogCosLin::processDepVar( const T dep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( LogCosLin::isDepVarInValidRange( dep_var ) );

  return log( convertCosineVar( getRawQuantity(dep_var) ) );
}

// Recover the processed independent value
template<typename T>
inline T LogCosLin::recoverProcessedIndepVar( const T processed_indep_var )
{
  return processed_indep_var;
}

// Recover the processed dependent value
template<typename T>
inline T LogCosLin::recoverProcessedDepVar( const T processed_dep_var )
{
  return convertCosineVar( exp( processed_dep_var ) );
}

// Test if the independent value is in a valid range (doesn't check nan/inf)
template<typename T>
inline bool LogCosLin::isIndepVarInValidRange( const T indep_var )
{
  return true;
}

// Test if the dependent value is in a valid range (doesn't check nan/inf)
template<typename T>
inline bool LogCosLin::isDepVarInValidRange( const T dep_var )
{
  // Make sure the indep var is not inf or nan
  testPrecondition( !QuantityTraits<T>::isnaninf( dep_var ) );
  
  return dep_var >= QuantityTraits<T>::initializeQuantity(-1.0) &&
         dep_var < QuantityTraits<T>::one();
}

// The name of the policy
inline const std::string LogCosLin::name()
{
  return "LogCosLin";
}

// Get the interpolation type
inline InterpolationType LinLogCos::getInterpolationType()
{
  return LINLOGCOS_INTERPOLATION;
}

// // Calculate the unit base grid length (L)
// /*! \details For LinLogCos and LogLogCos interpolation types the grid length
//  * that is calculated is not a traditional length. It is the negative of the
//  * distance between the processed upper independent value and the processed
//  *lower independent value. This is why any units associated with the independent
//  * grid limits are stripped away. Due to conversion of the independent
//  * values from a cosine (mu) to a delta cosine ( 1 - mu ) for LogLogCos and
//  * LinLogCos, the negative of the grid length is used to ensure a positive value.
//  */
// template<>
// template<typename IndepType>
// inline typename QuantityTraits<IndepType>::RawType
// InterpolationHelper<LinLogCos>::calculateUnitBaseGridLength(
//                                        const IndepType grid_lower_indep_value,
//                                        const IndepType grid_upper_indep_value )
// {
//   // Make sure the grid is valid
//   testPrecondition( grid_lower_indep_value <= grid_upper_indep_value );
//   testPrecondition( LinLogCos::isIndepVarInValidRange( grid_lower_indep_value ) );

//   return ThisType::calculateUnitBaseGridLengthProcessed(
//           LinLogCos::processIndepVar( grid_upper_indep_value ),
//           LinLogCos::processIndepVar( grid_lower_indep_value ) );
// }

// Calculate the unit base grid length from a processed grid (L)
/*! \details For LinLogCos and LogLogCos interpolation types the grid length
 * that is calculated is not a traditional length. It is the negative of the
 * distance between the processed upper independent value and the processed
 *lower independent value. This is why any units associated with the independent
 * grid limits are stripped away. Due to conversion of the independent
 * values from a cosine (mu) to a delta cosine ( 1 - mu ) for LogLogCos and
 * LinLogCos, the negative of the grid length is used to ensure a positive value.
 */
template<>
template<typename T>
inline T InterpolationHelper<LinLogCos>::calculateUnitBaseGridLengthProcessed(
                                     const T processed_grid_lower_indep_value,
                                     const T processed_grid_upper_indep_value )
{
  // Make sure the grid is valid
  testPrecondition( processed_grid_lower_indep_value >=
                    processed_grid_upper_indep_value );

  const T processed_grid_length =
    processed_grid_lower_indep_value - processed_grid_upper_indep_value;

  // Make sure the grid length is valid
  testPrecondition( processed_grid_length >= 0.0 );

  return processed_grid_length;
}

// Calculate the unit base independent variable (eta)
/*! \details The independent grid length is calculated using the
 * processed independent grid limits. It has been found that a tolerance of
 * 1e-3 works best for most applications. Due to conversion of the independent
 * values from a cosine (mu) to a delta cosine ( 1 - mu ) for LogLogCos and
 * LinLogCos, the negative of eta is used to ensure a positive value.
 */
template<>
template<typename IndepType>
inline typename QuantityTraits<IndepType>::RawType
InterpolationHelper<LinLogCos>::calculateUnitBaseIndepVar(
          const IndepType indep_var,
          const IndepType indep_var_min,
          const typename QuantityTraits<IndepType>::RawType indep_grid_length,
          const double tol )
{
  // Make sure the intermediate grid min indep var is valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_min ) );
  testPrecondition( LinLogCos::isIndepVarInValidRange( indep_var_min ) );
  // Make sure the intermediate grid length is valid
  testPrecondition( !QuantityTraits<typename QuantityTraits<IndepType>::RawType>::isnaninf( indep_grid_length ) );
  testPrecondition( indep_grid_length > 0.0 );
  // Make sure the independent variable is valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var ) );
  testPrecondition( LinLogCos::isIndepVarInValidRange( indep_var ) );
  testPrecondition( indep_var >=
                    ThisType::calculateFuzzyLowerBound( indep_var_min, tol ) );
  remember( typename QuantityTraits<IndepType>::RawType test_difference =
            LinLogCos::processIndepVar(indep_var) -
            LinLogCos::processIndepVar(indep_var_min) );

  testPrecondition( test_difference <= ThisType::calculateFuzzyUpperBound(
                                                    indep_grid_length, tol ) );

  return calculateUnitBaseIndepVarProcessed(
                       LinLogCos::processIndepVar(indep_var_min),
                       LinLogCos::processIndepVar(indep_var),
                       indep_grid_length,
                       tol );
}

// Calculate the independent variable (from eta)
/*! \details It has been found that a tolerance of 1e-3 works best for most 
 * applications. Due to conversion of the independent values from a cosine (mu)
 * to a delta cosine ( 1 - mu ) for LogLogCos and LinLogCos, the negative of eta
 * is used to ensure a positive value.
 */
template<>
template<typename IndepType>
inline IndepType
InterpolationHelper<LinLogCos>::calculateIndepVar(
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
  testPrecondition( LinLogCos::isIndepVarInValidRange( indep_var_min ) );
  // Make sure the grid length is valid
  testPrecondition( !QuantityTraits<typename QuantityTraits<IndepType>::RawType>::isnaninf( indep_grid_length ) );
  testPrecondition( indep_grid_length >= 0.0 );

  IndepType grid_indep_var( QuantityTraits<IndepType>::initializeQuantity(
    LinLogCos::recoverProcessedIndepVar( 
                    LinLogCos::processIndepVar( indep_var_min ) -
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
/*! \details Due to conversion of the independent values from a cosine (mu)
 * to a delta cosine ( 1 - mu ) for LogLogCos and LinLogCos, the negative of eta
 * is used to ensure a positive value. A tolerance is not required with this
 * method because no variable processing is done.
 */
template<>
template<typename T>
inline T InterpolationHelper<LinLogCos>::calculateProcessedIndepVar(
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
  
  return processed_indep_var_min - indep_grid_length*eta;
}

// Interpolate between two points
template<typename CosineType, typename DepType>
inline DepType LinLogCos::interpolate( const CosineType raw_indep_var_0,
                                       const CosineType raw_indep_var_1,
                                       const CosineType raw_indep_var,
                                       const DepType dep_var_0,
                                       const DepType dep_var_1 )
{
  // T must be a floating point type
  testStaticPrecondition( (QuantityTraits<CosineType>::is_floating_point::value) );
  testStaticPrecondition( (QuantityTraits<DepType>::is_floating_point::value) );
  // Make sure the independent variables are valid
  testPrecondition( !QuantityTraits<CosineType>::isnaninf( raw_indep_var_0 ) );
  testPrecondition( !QuantityTraits<CosineType>::isnaninf( raw_indep_var_1 ) );
  testPrecondition( !QuantityTraits<CosineType>::isnaninf( raw_indep_var ) );
  testPrecondition( LinLogCos::isIndepVarInValidRange( raw_indep_var_0 ) );
  testPrecondition( LinLogCos::isIndepVarInValidRange( raw_indep_var_1 ) );
  testPrecondition( LinLogCos::isIndepVarInValidRange( raw_indep_var ) );
  testPrecondition( raw_indep_var_0 < raw_indep_var_1 );
  testPrecondition( raw_indep_var >= raw_indep_var_0 );
  testPrecondition( raw_indep_var <= raw_indep_var_1 );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_0 ) );
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_1 ) );
  testPrecondition( LinLogCos::isDepVarInValidRange( dep_var_0 ) );
  testPrecondition( LinLogCos::isDepVarInValidRange( dep_var_1 ) );

  // Convert cosine variables
  CosineType indep_var_0 = convertCosineVar(raw_indep_var_0);
  CosineType indep_var_1 = convertCosineVar(raw_indep_var_1);
  CosineType indep_var = convertCosineVar(raw_indep_var);

  DepType term_2( (dep_var_1 - dep_var_0)*log(indep_var/indep_var_0)/
                  log(indep_var_1/indep_var_0) );

  return dep_var_0 + term_2;
}

// Interpolate between two processed points
/*! \details Due to conversion of the independent values from a cosine (mu)
 * to a delta cosine ( 1 - mu ), the absolute value of the difference between
 * the processed_indep_var and processed_indep_var_0 is used for
 * LinLogCos and LogLogCos.
 */
template<>
template<typename T>
T InterpolationHelper<LinLogCos>::interpolate( const T processed_indep_var_0,
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
  
  return LinLogCos::recoverProcessedDepVar(
               processed_dep_var_0 +
               processed_slope*(processed_indep_var_0 - processed_indep_var) );
}

// Interpolate between two points using the indep variable ratio (beta)
template<typename T, typename DepType>
inline DepType LinLogCos::interpolate( const T beta,
                                       const DepType dep_var_0,
                                       const DepType dep_var_1 )
{
  // The CosineType must be a floating point type
  testStaticPrecondition( (QuantityTraits<T>::is_floating_point::value) );
  testStaticPrecondition( (QuantityTraits<DepType>::is_floating_point::value) );
  // Make sure the independent variables are valid
  testPrecondition( beta >= QuantityTraits<T>::zero() );
  testPrecondition( beta <= QuantityTraits<T>::one() );
  // Make sure the dependent variables are valid
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_0 ) );
  testPrecondition( !QuantityTraits<DepType>::isnaninf( dep_var_1 ) );
  testPrecondition( LinLogCos::isDepVarInValidRange( dep_var_0 ) );
  testPrecondition( LinLogCos::isDepVarInValidRange( dep_var_1 ) );

  return dep_var_0 + (dep_var_1 - dep_var_0)*beta;
}

// Interpolate between two points and return the processed value
template<typename CosineType, typename DepType>
inline typename QuantityTraits<DepType>::RawType
LinLogCos::interpolateAndProcess( const CosineType raw_indep_var_0,
                                  const CosineType raw_indep_var_1,
                                  const CosineType raw_indep_var,
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
template<typename T>
inline typename QuantityTraits<T>::RawType
LinLogCos::processIndepVar( const T indep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( LinLogCos::isIndepVarInValidRange( indep_var ) );

  return log( convertCosineVar( getRawQuantity(indep_var) ) );
}

// Process the dependent value
template<typename T>
inline typename QuantityTraits<T>::RawType
LinLogCos::processDepVar( const T dep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( LinLogCos::isDepVarInValidRange( dep_var ) );

  return getRawQuantity(dep_var);
}

// Recover the processed independent value
template<typename T>
inline T LinLogCos::recoverProcessedIndepVar( const T processed_indep_var )
{
  return convertCosineVar( exp( processed_indep_var ) );
}

// Recover the processed dependent value
template<typename T>
inline T LinLogCos::recoverProcessedDepVar( const T processed_dep_var )
{
  return processed_dep_var;
}

// Test if the independent value is in a valid range (doesn't check nan/inf)
template<typename T>
inline bool LinLogCos::isIndepVarInValidRange( const T indep_var )
{
  return indep_var >= QuantityTraits<T>::initializeQuantity(-1.0) &&
         indep_var < QuantityTraits<T>::one();
}

// Test if the dependent value is in a valid range (doesn't check nan/inf)
template<typename T>
inline bool LinLogCos::isDepVarInValidRange( const T dep_var )
{
  // Make sure the indep var is not inf or nan
  testPrecondition( !QuantityTraits<T>::isnaninf( dep_var ) );
  
  return true;
}

// The name of the policy
inline const std::string LinLogCos::name()
{
  return "LinLogCos";
}

} // end Utility namespace

#endif // end UTILITY_COSINE_INTERPOLATION_POLICY_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_CosineInterpolationPolicy_def.hpp
//---------------------------------------------------------------------------//
