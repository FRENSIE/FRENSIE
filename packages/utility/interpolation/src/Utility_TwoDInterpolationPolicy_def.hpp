//---------------------------------------------------------------------------//
//!
//! \file   Utility_TwoDInterpolationPolicy_def.hpp
//! \author Alex Robinson
//! \brief  Policy struct declarations for interpolating on 2D grids
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TWO_D_INTERPOLATION_POLICY_DEF_HPP
#define UTILITY_TWO_D_INTERPOLATION_POLICY_DEF_HPP

// Std Lib Includes
#include <functional>

// FRENSIE Includes
#include "Utility_SortAlgorithms.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_ComparePolicy.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Initialize static member data
template<typename ZYInterpPolicy, typename ZXInterpPolicy>
const double TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::s_tol=
  1e-3;

// Process the dependent variable (z - ZYX)
template<typename ZYInterpPolicy, typename ZXInterpPolicy>
template<typename T>
inline typename QuantityTraits<T>::RawType
TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::processDepVar(
							      const T dep_var )
{
  // Make sure the dependent variable is valid
  testPrecondition( ZYInterpPolicy::isDepVarInValidRange( dep_var ) );

  return ZYInterpPolicy::processDepVar( dep_var );
}

// Recover the processed dependent variable (z - ZYX)
template<typename ZYInterpPolicy, typename ZXInterpPolicy>
template<typename T>
inline T TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::recoverProcessedDepVar(
						    const T processed_dep_var )
{
  return ZYInterpPolicy::recoverProcessedDepVar( processed_dep_var );
}

// Test if the dependent variable is in a valid range (z - ZYX)
template<typename ZYInterpPolicy, typename ZXInterpPolicy>
template<typename T>
inline bool TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::isDepVarInValidRange( const T dep_var )
{
  return ZYInterpPolicy::isDepVarInValidRange( dep_var );
}

// Process the second independent variable (y - ZYX)
template<typename ZYInterpPolicy, typename ZXInterpPolicy>
template<typename T>
inline typename QuantityTraits<T>::RawType
TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::processSecondIndepVar(
						     const T second_indep_var )
{
  // Make sure the indep var is valid
  testPrecondition( ZYInterpPolicy::isIndepVarInValidRange(second_indep_var) );

  return ZYInterpPolicy::processIndepVar( second_indep_var );
}

// Recover the processed second independent variable (y - ZYX)
template<typename ZYInterpPolicy, typename ZXInterpPolicy>
template<typename T>
inline T TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::recoverProcessedSecondIndepVar(
					   const T processed_second_indep_var )
{
  return ZYInterpPolicy::recoverProcessedIndepVar( processed_second_indep_var);
}

// Test if the second independent variable is in a valid range (y - ZYX)
template<typename ZYInterpPolicy, typename ZXInterpPolicy>
template<typename T> 
inline bool TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::isSecondIndepVarInValidRange( const T second_indep_var )
{
  return ZYInterpPolicy::isIndepVarInValidRange( second_indep_var );
}

// Process the first independent variable (x - ZYX)
template<typename ZYInterpPolicy, typename ZXInterpPolicy>
template<typename T>
inline typename QuantityTraits<T>::RawType
TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::processFirstIndepVar(
						      const T first_indep_var )
{
  // Make sure the indep var is valid
  testPrecondition( ZXInterpPolicy::isIndepVarInValidRange(first_indep_var) );

  return ZXInterpPolicy::processIndepVar( first_indep_var );
}

// Recover the first independent variable (x - ZYX)
template<typename ZYInterpPolicy, typename ZXInterpPolicy>
template<typename T>
inline T TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::recoverProcessedFirstIndepVar(
					    const T processed_first_indep_var )
{
  return ZXInterpPolicy::recoverProcessedIndepVar( processed_first_indep_var );
}

// Test if the first independent variable is in a valid range (x - ZYX)
template<typename ZYInterpPolicy, typename ZXInterpPolicy>
template<typename T>
inline bool TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::isFirstIndepVarInValidRange( const T first_indep_var )
{
  return ZXInterpPolicy::isIndepVarInValidRange( first_indep_var );
}

//! Conduct the interpolation between two grids
template<typename ZYInterpPolicy, typename ZXInterpPolicy>
template<typename FirstIndepType,
         typename SecondIndepType,
         typename ZYLowerFunctor,
         typename ZYUpperFunctor>
inline typename ZYLowerFunctor::result_type TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::interpolate(
                            const FirstIndepType indep_var_x_0,
                            const FirstIndepType indep_var_x_1,
                            const FirstIndepType indep_var_x,
                            const SecondIndepType indep_var_y,
                            const ZYLowerFunctor& evaluate_z_with_y_0_functor,
                            const ZYUpperFunctor& evaluate_z_with_y_1_functor )
{
  // The interpolation type on the Z variable must be consistent
  testStaticPrecondition( (boost::is_same<typename ZYInterpPolicy::DepVarProcessingTag,typename ZXInterpPolicy::DepVarProcessingTag>::value) );
  // All types must be a floating point type
  testStaticPrecondition( (QuantityTraits<FirstIndepType>::is_floating_point::value) );
  testStaticPrecondition( (QuantityTraits<SecondIndepType>::is_floating_point::value) );
  testStaticPrecondition( (QuantityTraits<typename ZYLowerFunctor::result_type>::is_floating_point::value) );
  testStaticPrecondition( (QuantityTraits<typename ZYUpperFunctor::result_type>::is_floating_point::value) );
  // Make sure the first independent variables are valid
  testPrecondition( !QuantityTraits<FirstIndepType>::isnaninf(indep_var_x_0) );
  testPrecondition( !QuantityTraits<FirstIndepType>::isnaninf(indep_var_x_1) );
  testPrecondition( !QuantityTraits<FirstIndepType>::isnaninf( indep_var_x ) );
  testPrecondition( ThisType::isFirstIndepVarInValidRange( indep_var_x_0 ) );
  testPrecondition( indep_var_x_0 < indep_var_x_1 );
  testPrecondition( indep_var_x >= indep_var_x_0 );
  testPrecondition( indep_var_x <= indep_var_x_1 );
  // Make sure the second independent variable is valid
  testPrecondition( !QuantityTraits<SecondIndepType>::isnaninf(indep_var_y) );
  testPrecondition( ThisType::isSecondIndepVarInValidRange( indep_var_y ) );

  // Conduct the ZY interpolation on the y grids
  const auto dep_var_0 = evaluate_z_with_y_0_functor( indep_var_y );

  const auto dep_var_1 = evaluate_z_with_y_1_functor( indep_var_y );
  
  // Process the dependent values
  const auto processed_dep_var_0 = ThisType::processDepVar( dep_var_0 );

  const auto processed_dep_var_1 = ThisType::processDepVar( dep_var_1 );

  // Conduct the ZX interpolation
  const auto processed_indep_var_x_0 =
    ThisType::processFirstIndepVar( indep_var_x_0 );

  const auto processed_indep_var_x_1 =
    ThisType::processFirstIndepVar( indep_var_x_1 );

  const auto processed_indep_var_x =
    ThisType::processFirstIndepVar( indep_var_x );

  const auto processed_slope = (processed_dep_var_1 - processed_dep_var_0)/
    (processed_indep_var_x_1 - processed_indep_var_x_0);

  return QuantityTraits<typename ZYUpperFunctor::result_type>::initializeQuantity(
                          ZXInterpPolicy::interpolate( processed_indep_var_x_0,
                                                       processed_indep_var_x,
                                                       processed_dep_var_0,
                                                       processed_slope ) );
}

// Conduct the interpolation between two grids
/*! \details Make sure that the y variable lies inside of both grids - this
 * policy does not do extrapolation.
 */
template<typename ZYInterpPolicy, typename ZXInterpPolicy>
template<TupleMember YIndepMember,
	 TupleMember DepMember,
	 typename YIterator,
	 typename ZIterator,
	 typename T >
inline T
TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::interpolate(
						const T indep_var_x_0,
						const T indep_var_x_1,
						const T indep_var_x,
						const T indep_var_y,
			                        YIterator start_indep_y_grid_0,
						YIterator end_indep_y_grid_0,
						ZIterator start_dep_grid_0,
						ZIterator end_dep_grid_0,
						YIterator start_indep_y_grid_1,
						YIterator end_indep_y_grid_1,
						ZIterator start_dep_grid_1,
						ZIterator end_dep_grid_1 )
{
  // The interpolation type on the Z variable must be consistent
  testStaticPrecondition( (boost::is_same<typename ZYInterpPolicy::DepVarProcessingTag,typename ZXInterpPolicy::DepVarProcessingTag>::value) );
  // T must be a floating point type
  testStaticPrecondition( (boost::is_floating_point<T>::value) );
  // The y iterator must have T as the value type
  testStaticPrecondition( (boost::is_same<typename TupleMemberTraits<typename std::iterator_traits<YIterator>::value_type,YIndepMember>::tupleMemberType,T>::value) );
  // The z iterator must have T as the value type
  testStaticPrecondition( (boost::is_same<typename TupleMemberTraits<typename std::iterator_traits<ZIterator>::value_type,DepMember>::tupleMemberType,T>::value) );
  // Make sure the first independent variables are valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( indep_var_x_0 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( indep_var_x_1 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( indep_var_x ) );
  testPrecondition( ThisType::isFirstIndepVarInValidRange( indep_var_x_0 ) );
  testPrecondition( indep_var_x_0 < indep_var_x_1 );
  testPrecondition( indep_var_x >= indep_var_x_0 );
  testPrecondition( indep_var_x <= indep_var_x_1 );
  // Make sure the second independent variables are valid
  testPrecondition( start_indep_y_grid_0 != end_indep_y_grid_0 );
  testPrecondition( Sort::isSortedAscending<YIndepMember>(start_indep_y_grid_0,
							  end_indep_y_grid_0));
  testPrecondition( ThisType::isSecondIndepVarInValidRange(
				get<YIndepMember>( *start_indep_y_grid_0 ) ) );
  testPrecondition( start_indep_y_grid_1 != end_indep_y_grid_1 );
  testPrecondition( Sort::isSortedAscending<YIndepMember>(start_indep_y_grid_1,
							  end_indep_y_grid_1));
  testPrecondition( ThisType::isSecondIndepVarInValidRange(
				get<YIndepMember>( *start_indep_y_grid_1 ) ) );
  // Make sure the right type of interpolation is being used
  // Note: if this fails - use unit base interpolation
  testPrecondition( indep_var_y >= get<YIndepMember>( *start_indep_y_grid_0 ));
  remember( YIterator true_end_indep_y_grid_0 = end_indep_y_grid_0 );
  remember( --true_end_indep_y_grid_0 );
  testPrecondition(indep_var_y <= get<YIndepMember>(*true_end_indep_y_grid_0));
  testPrecondition( indep_var_y >= get<YIndepMember>( *start_indep_y_grid_0 ));
  remember( YIterator true_end_indep_y_grid_1 = end_indep_y_grid_1 );
  remember( --true_end_indep_y_grid_1 );
  testPrecondition(indep_var_y <= get<YIndepMember>(*true_end_indep_y_grid_1));
  testPrecondition( indep_var_y >= get<YIndepMember>( *start_indep_y_grid_1 ));
  // Make sure the dependent variables are valid
  testPrecondition( start_dep_grid_0 != end_dep_grid_0 );
  testPrecondition( start_dep_grid_1 != end_dep_grid_1 );
  testPrecondition( std::distance( start_indep_y_grid_0, end_indep_y_grid_0 )==
		    std::distance( start_dep_grid_0, end_dep_grid_0 ) );
  testPrecondition( std::distance( start_indep_y_grid_1, end_indep_y_grid_1 )==
		    std::distance( start_dep_grid_1, end_dep_grid_1 ) );

  // Create the grid interpolation functors
  std::function<T(T)> interpolate_grid_0_functor =
    std::bind<T>( &ThisType::interpolateOnYGrid<YIndepMember,DepMember,YIterator,ZIterator,T>,
                       std::placeholders::_1,
                       start_indep_y_grid_0,
                       end_indep_y_grid_0,
                       start_dep_grid_0,
                       end_dep_grid_0 );

  std::function<T(T)> interpolate_grid_1_functor =
    std::bind<T>( &ThisType::interpolateOnYGrid<YIndepMember,DepMember,YIterator,ZIterator,T>,
                       std::placeholders::_1,
                       start_indep_y_grid_1,
                       end_indep_y_grid_1,
                       start_dep_grid_1,
                       end_dep_grid_1 );
  
  return ThisType::interpolate( indep_var_x_0,
                                indep_var_x_1,
                                indep_var_x,
                                indep_var_y,
                                interpolate_grid_0_functor,
                                interpolate_grid_1_functor );
}

// Conduct the interpolation between two grids
/*! \details Make sure that the y variable lies inside of both grids - this
 * policy does not do extrapolation.
 */
template<typename ZYInterpPolicy, typename ZXInterpPolicy>
template<TupleMember YIndepMember,
	 TupleMember DepMember,
	 typename Iterator,
	 typename T >
inline T
TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::interpolate(
						const T indep_var_x_0,
						const T indep_var_x_1,
						const T indep_var_x,
						const T indep_var_y,
			                        Iterator start_grid_0,
						Iterator end_grid_0,
						Iterator start_grid_1,
						Iterator end_grid_1 )
{
  // Make sure the tuple members are valid
  testStaticPrecondition( YIndepMember != DepMember );

  return ThisType::interpolate<YIndepMember,DepMember>( indep_var_x_0,
                                                        indep_var_x_1,
                                                        indep_var_x,
                                                        indep_var_y,
                                                        start_grid_0,
                                                        end_grid_0,
                                                        start_grid_0,
                                                        end_grid_0,
                                                        start_grid_1,
                                                        end_grid_1,
                                                        start_grid_1,
                                                        end_grid_1 );
}

// Conduct the interpolation between two grids (no tuples)
/*! \details Make sure that the y variable lies inside of both grids - this
 * policy does not do extrapolation.
 */
template<typename ZYInterpPolicy, typename ZXInterpPolicy>
template<typename YIterator, typename ZIterator, typename T>
inline T
TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::interpolate(
						const T indep_var_x_0,
						const T indep_var_x_1,
						const T indep_var_x,
						const T indep_var_y,
			                        YIterator start_indep_y_grid_0,
						YIterator end_indep_y_grid_0,
						ZIterator start_dep_grid_0,
						ZIterator end_dep_grid_0,
						YIterator start_indep_y_grid_1,
						YIterator end_indep_y_grid_1,
						ZIterator start_dep_grid_1,
						ZIterator end_dep_grid_1 )
{
  // Make sure no tuples are being used
  testStaticPrecondition( (boost::is_floating_point<typename std::iterator_traits<YIterator>::value_type>::value) );

  return ThisType::interpolate<FIRST,FIRST>( indep_var_x_0,
                                             indep_var_x_1,
                                             indep_var_x,
                                             indep_var_y,
                                             start_indep_y_grid_0,
                                             end_indep_y_grid_0,
                                             start_dep_grid_0,
                                             end_dep_grid_0,
                                             start_indep_y_grid_1,
                                             end_indep_y_grid_1,
                                             start_dep_grid_1,
                                             end_dep_grid_1 );
}

// Conduct unit base interpolation
/*! \details Make sure that the y variable is valid (call
 * calculateIntermediateGridLimit to get the y range at x).
 */
template<typename ZYInterpPolicy, typename ZXInterpPolicy>
template<typename FirstIndepType,
         typename SecondIndepType,
         typename ZYLowerFunctor,
         typename ZYUpperFunctor>
inline typename ZYLowerFunctor::result_type
TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::interpolateUnitBase(
         const FirstIndepType indep_var_x_0,
         const FirstIndepType indep_var_x_1,
         const FirstIndepType indep_var_x,
         const SecondIndepType indep_var_y,
         const SecondIndepType indep_var_y_0_min,
         const SecondIndepType indep_var_y_1_min,
         const typename QuantityTraits<SecondIndepType>::RawType grid_0_length,
         const typename QuantityTraits<SecondIndepType>::RawType grid_1_length,
         const ZYLowerFunctor& evaluate_z_with_y_0_functor,
         const ZYUpperFunctor& evaluate_z_with_y_1_functor )
{
  // The interpolation type on the Z variable must be consistent
  testStaticPrecondition( (boost::is_same<typename ZYInterpPolicy::DepVarProcessingTag,typename ZXInterpPolicy::DepVarProcessingTag>::value) );
  // All types must be a floating point type
  testStaticPrecondition( (QuantityTraits<FirstIndepType>::is_floating_point::value) );
  testStaticPrecondition( (QuantityTraits<SecondIndepType>::is_floating_point::value) );
  testStaticPrecondition( (QuantityTraits<typename ZYLowerFunctor::result_type>::is_floating_point::value) );
  testStaticPrecondition( (QuantityTraits<typename ZYUpperFunctor::result_type>::is_floating_point::value) );
  // Make sure the first independent variables are valid
  testPrecondition( !QuantityTraits<FirstIndepType>::isnaninf(indep_var_x_0) );
  testPrecondition( !QuantityTraits<FirstIndepType>::isnaninf(indep_var_x_1) );
  testPrecondition( !QuantityTraits<FirstIndepType>::isnaninf( indep_var_x ) );
  testPrecondition( ThisType::isFirstIndepVarInValidRange( indep_var_x_0 ) );
  testPrecondition( indep_var_x_0 < indep_var_x_1 );
  testPrecondition( indep_var_x >= indep_var_x_0 );
  testPrecondition( indep_var_x <= indep_var_x_1 );
  // Make sure the second independent variables are valid
  testPrecondition( ThisType::isSecondIndepVarInValidRange(
                                                         indep_var_y_0_min ) );
  testPrecondition( ThisType::isSecondIndepVarInValidRange(
                                                         indep_var_y_1_min ) );
  remember( SecondIndepType test_y_min =
            ThisType::calculateIntermediateGridLimit( indep_var_x_0,
                                                      indep_var_x_1,
                                                      indep_var_x,
                                                      indep_var_y_0_min,
                                                      indep_var_y_1_min ) );
  testPrecondition( indep_var_y >= test_y_min ||
		    Policy::relError( indep_var_y, test_y_min ) <= s_tol );
  // Make sure the grid lengths are valid
  testPrecondition( grid_0_length > 0.0 );
  testPrecondition( grid_1_length > 0.0 );

  // Calculate the intermediate grid length
  const auto Lx = calculateIntermediateGridLength( indep_var_x_0,
                                                   indep_var_x_1,
                                                   indep_var_x,
                                                   grid_0_length,
                                                   grid_1_length );

  // Calculate the intermediate y min
  const auto y_x_min = calculateIntermediateGridLimit( indep_var_x_0,
                                                       indep_var_x_1,
                                                       indep_var_x,
                                                       indep_var_y_0_min,
                                                       indep_var_y_1_min );

  // Calculate the unit base independent variable
  const auto eta =
    ZYInterpPolicy::calculateUnitBaseIndepVar( indep_var_y, y_x_min, Lx );

  // Calculate the y value on the first grid
  const auto indep_var_y_0 =
    ZYInterpPolicy::calculateIndepVar( eta, indep_var_y_0_min, grid_0_length );

  // Calculate the y value on the second grid
  const auto indep_var_y_1 =
    ZYInterpPolicy::calculateIndepVar( eta, indep_var_y_1_min, grid_1_length );

  // Evaluate the dependent value on the first y grid
  const auto dep_var_0 = evaluate_z_with_y_0_functor( indep_var_y_0 );

  // Evaluate the dependent value on the second y grid
  const auto dep_var_1 = evaluate_z_with_y_1_functor( indep_var_y_1 );

  // Process and scale the dependent values
  const auto scaled_processed_dep_var_0 =
    ThisType::processDepVar( dep_var_0 )*grid_0_length;

  const auto scaled_processed_dep_var_1 =
    ThisType::processDepVar( dep_var_1)*grid_1_length;

  // Calculate the processed slope
  const auto processed_indep_var_x_0 =
    ThisType::processFirstIndepVar( indep_var_x_0 );

  const auto processed_indep_var_x_1 =
    ThisType::processFirstIndepVar( indep_var_x_1 );
  
  const auto processed_slope =
    (scaled_processed_dep_var_1 - scaled_processed_dep_var_0)/
    (processed_indep_var_x_1 - processed_indep_var_x_0);

  // Interpolate to find the processed dependent value at (x,y)
  const auto processed_indep_var_x =
    ThisType::processFirstIndepVar( indep_var_x );
  
  const auto processed_dep_var_yx = ZXInterpPolicy::interpolateAndProcess(
                                                    processed_indep_var_x_0,
                                                    processed_indep_var_x,
                                                    scaled_processed_dep_var_0,
                                                    processed_slope )/Lx;

  return QuantityTraits<typename ZYLowerFunctor::result_type>::initializeQuantity(
                    ThisType::recoverProcessedDepVar( processed_dep_var_yx ) );
}

// Conduct unit base interpolation
/*! \details Make sure that the y variable is valid (call
 * calculateIntermediateGridLimit to get the y range at x).
 */
template<typename ZYInterpPolicy, typename ZXInterpPolicy>
template<TupleMember YIndepMember,
	 TupleMember DepMember,
	 typename YIterator,
	 typename ZIterator,
	 typename T>
inline T TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::interpolateUnitBase(
				                const T indep_var_x_0,
						const T indep_var_x_1,
						const T indep_var_x,
						const T indep_var_y,
				                YIterator start_indep_y_grid_0,
						YIterator end_indep_y_grid_0,
						ZIterator start_dep_grid_0,
						ZIterator end_dep_grid_0,
						YIterator start_indep_y_grid_1,
						YIterator end_indep_y_grid_1,
						ZIterator start_dep_grid_1,
						ZIterator end_dep_grid_1 )
{
  // The interpolation type on the Z variable must be consistent
  testStaticPrecondition( (boost::is_same<typename ZYInterpPolicy::DepVarProcessingTag,typename ZXInterpPolicy::DepVarProcessingTag>::value) );
  // T must be a floating point type
  testStaticPrecondition( (boost::is_floating_point<T>::value) );
  // The y iterator must have T as the value type
  testStaticPrecondition( (boost::is_same<typename TupleMemberTraits<typename std::iterator_traits<YIterator>::value_type,YIndepMember>::tupleMemberType,T>::value) );
  // The z iterator must have T as the value type
  testStaticPrecondition( (boost::is_same<typename TupleMemberTraits<typename std::iterator_traits<ZIterator>::value_type,DepMember>::tupleMemberType,T>::value) );
  // Make sure the first independent variables are valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( indep_var_x_0 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( indep_var_x_1 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( indep_var_x ) );
  testPrecondition( ThisType::isFirstIndepVarInValidRange( indep_var_x_0 ) );
  testPrecondition( indep_var_x_0 < indep_var_x_1 );
  testPrecondition( indep_var_x >= indep_var_x_0 );
  testPrecondition( indep_var_x <= indep_var_x_1 );
  // Make sure the second independent variables are valid
  testPrecondition( start_indep_y_grid_0 != end_indep_y_grid_0 );
  testPrecondition( Sort::isSortedAscending<YIndepMember>(start_indep_y_grid_0,
							  end_indep_y_grid_0));
  testPrecondition( ThisType::isSecondIndepVarInValidRange(
				get<YIndepMember>( *start_indep_y_grid_0 ) ) );
  testPrecondition( start_indep_y_grid_1 != end_indep_y_grid_1 );
  testPrecondition( Sort::isSortedAscending<YIndepMember>(start_indep_y_grid_1,
							  end_indep_y_grid_1));
  testPrecondition( ThisType::isSecondIndepVarInValidRange(
				get<YIndepMember>( *start_indep_y_grid_1 ) ) );
  remember( T test_y_min = calculateIntermediateGridLimit(
				indep_var_x_0,
				indep_var_x_1,
				indep_var_x,
				get<YIndepMember>( *start_indep_y_grid_0 ),
			        get<YIndepMember>( *start_indep_y_grid_1 ) ) );
  testPrecondition( indep_var_y >= test_y_min ||
		    Policy::relError( indep_var_y, test_y_min ) <= s_tol );
  remember( YIterator true_end_indep_y_grid_0 = end_indep_y_grid_0 );
  remember( --true_end_indep_y_grid_0 );
  remember( YIterator true_end_indep_y_grid_1 = end_indep_y_grid_1 );
  remember( --true_end_indep_y_grid_1 );
  remember( T test_y_max = calculateIntermediateGridLimit(
			     indep_var_x_0,
			     indep_var_x_1,
			     indep_var_x,
			     get<YIndepMember>( *true_end_indep_y_grid_0 ),
			     get<YIndepMember>( *true_end_indep_y_grid_1 ) ) );
  testPrecondition( indep_var_y <= test_y_max ||
		    Policy::relError( indep_var_y, test_y_max ) <= s_tol );
  // Make sure the dependent variables are valid
  testPrecondition( start_dep_grid_0 != end_dep_grid_0 );
  testPrecondition( start_dep_grid_1 != end_dep_grid_1 );
  testPrecondition( std::distance( start_indep_y_grid_0, end_indep_y_grid_0 )==
		    std::distance( start_dep_grid_0, end_dep_grid_0 ) );
  testPrecondition( std::distance( start_indep_y_grid_1, end_indep_y_grid_1 )==
		    std::distance( start_dep_grid_1, end_dep_grid_1 ) );

  // Calculate the length of the first y grid
  const T L0 = calculateGridLength<YIndepMember>( start_indep_y_grid_0,
						  end_indep_y_grid_0 );

  // Calculate the length of the first y grid
  const T L1 = calculateGridLength<YIndepMember>( start_indep_y_grid_1,
						  end_indep_y_grid_1 );

  // Create the grid interpolation functors
  std::function<T(T)> interpolate_grid_0_functor =
    std::bind<T>( &ThisType::interpolateOnYGrid<YIndepMember,DepMember,YIterator,ZIterator,T>,
                  std::placeholders::_1,
                  start_indep_y_grid_0,
                  end_indep_y_grid_0,
                  start_dep_grid_0,
                  end_dep_grid_0 );

  std::function<T(T)> interpolate_grid_1_functor =
    std::bind<T>( &ThisType::interpolateOnYGrid<YIndepMember,DepMember,YIterator,ZIterator,T>,
                  std::placeholders::_1,
                  start_indep_y_grid_1,
                  end_indep_y_grid_1,
                  start_dep_grid_1,
                  end_dep_grid_1 );
  
  return ThisType::interpolateUnitBase(
                                    indep_var_x_0,
                                    indep_var_x_1,
                                    indep_var_x,
                                    indep_var_y,
                                    get<YIndepMember>( *start_indep_y_grid_0 ),
                                    get<YIndepMember>( *start_indep_y_grid_1 ),
                                    L0,
                                    L1,
                                    interpolate_grid_0_functor,
                                    interpolate_grid_1_functor );
}

// Conduct the interpolation between two grids
/*! \details Make sure that the y variable is valid (call
 * calculateIntermediateGridLimit to get the y range at x).
 */
template<typename ZYInterpPolicy, typename ZXInterpPolicy>
template<TupleMember YIndepMember,
	 TupleMember DepMember,
	 typename Iterator,
	 typename T>
inline T TwoDInterpolationPolicyImpl<ZYInterpPolicy,
				     ZXInterpPolicy>::interpolateUnitBase(
				     const T indep_var_x_0,
				     const T indep_var_x_1,
				     const T indep_var_x,
				     const T indep_var_y,
				     Iterator start_grid_0,
				     Iterator end_grid_0,
				     Iterator start_grid_1,
				     Iterator end_grid_1 )
{
  // Make sure the tuple members are valid
  testStaticPrecondition( YIndepMember != DepMember );

  return ThisType::interpolateUnitBase<YIndepMember,DepMember>( indep_var_x_0,
                                                                indep_var_x_1,
                                                                indep_var_x,
                                                                indep_var_y,
                                                                start_grid_0,
                                                                end_grid_0,
                                                                start_grid_0,
                                                                end_grid_0,
                                                                start_grid_1,
                                                                end_grid_1,
                                                                start_grid_1,
                                                                end_grid_1 );
}

// Conduct unit base interpolation between two grids (no tuples)
/*! \details Make sure that the y variable is valid (call
 * calculateIntermediateGridLimit to get the y range at x).
 */
template<typename ZYInterpPolicy, typename ZXInterpPolicy>
template<typename YIterator, typename ZIterator, typename T>
inline T TwoDInterpolationPolicyImpl<ZYInterpPolicy,
				     ZXInterpPolicy>::interpolateUnitBase(
				     const T indep_var_x_0,
				     const T indep_var_x_1,
				     const T indep_var_x,
				     const T indep_var_y,
				     YIterator start_indep_var_y_0,
				     YIterator end_indep_var_y_0,
				     ZIterator start_dep_var_0,
				     ZIterator end_dep_var_0,
				     YIterator start_indep_var_y_1,
				     YIterator end_indep_var_y_1,
				     ZIterator start_dep_var_1,
				     ZIterator end_dep_var_1 )
{
  // Make sure no tuples are being used
  testStaticPrecondition( (boost::is_floating_point<typename std::iterator_traits<YIterator>::value_type>::value) );

  return ThisType::interpolateUnitBase<FIRST,FIRST>( indep_var_x_0,
                                                     indep_var_x_1,
                                                     indep_var_x,
                                                     indep_var_y,
                                                     start_indep_var_y_0,
                                                     end_indep_var_y_0,
                                                     start_dep_var_0,
                                                     end_dep_var_0,
                                                     start_indep_var_y_1,
                                                     end_indep_var_y_1,
                                                     start_dep_var_1,
                                                     end_dep_var_1 );
}

// Calculate the length of a grid
template<typename ZYInterpPolicy, typename ZXInterpPolicy>
template<typename T>
inline typename QuantityTraits<T>::RawType
TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::calculateGridLength(
                                                      const T grid_front_value,
                                                      const T grid_back_value )
{
  // Make sure the grid is valid
  testPrecondition( grid_front_value <= grid_back_value );

  const typename QuantityTraits<T>::RawType grid_length =
    ThisType::processSecondIndepVar( grid_back_value ) -
    ThisType::processSecondIndepVar( grid_front_value );

  // Make sure the grid length is valid
  testPostcondition( grid_length >= 0.0 );

  return grid_length;
}

// Calculate the length of a grid
template<typename ZYInterpPolicy, typename ZXInterpPolicy>
template<TupleMember YIndepMember,
	 typename YIterator>
inline typename TupleMemberTraits<typename std::iterator_traits<YIterator>::value_type,YIndepMember>::tupleMemberType
TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::calculateGridLength(
						  YIterator start_indep_y_grid,
						  YIterator end_indep_y_grid )
{
  // The return type must be a floating point type
  testStaticPrecondition( (boost::is_floating_point<typename TupleMemberTraits<typename std::iterator_traits<YIterator>::value_type,YIndepMember>::tupleMemberType>::value) );
  // Make sure the grid is valid
  testPrecondition( ThisType::isSecondIndepVarInValidRange(
				get<YIndepMember>( *start_indep_y_grid ) ) );
  testPrecondition( start_indep_y_grid != end_indep_y_grid );
  testPrecondition( Sort::isSortedAscending<YIndepMember>( start_indep_y_grid,
							   end_indep_y_grid ));

  YIterator true_end_y_grid = end_indep_y_grid;
  --true_end_y_grid;

  return ThisType::calculateGridLength(
                                      get<YIndepMember>( *start_indep_y_grid ),
                                      get<YIndepMember>( *true_end_y_grid ) );
}

// Calculate the length of an intermediate grid
template<typename ZYInterpPolicy, typename ZXInterpPolicy>
template<typename IndepType, typename LengthType>
inline LengthType
TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::calculateIntermediateGridLength(
					       const IndepType indep_var_x_0,
                                               const IndepType indep_var_x_1,
                                               const IndepType indep_var_x,
                                               const LengthType grid_0_length,
					       const LengthType grid_1_length )
{
  // Make sure the first independent variables are valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_x_0 ) );
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_x_1 ) );
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_x ) );
  testPrecondition( ThisType::isFirstIndepVarInValidRange( indep_var_x_0 ) );
  testPrecondition( indep_var_x_0 < indep_var_x_1 );
  testPrecondition( indep_var_x >= indep_var_x_0 );
  testPrecondition( indep_var_x <= indep_var_x_1 );
  // Make sure the grid lengths are valid
  testPrecondition( !QuantityTraits<LengthType>::isnaninf( grid_0_length ) );
  testPrecondition( !QuantityTraits<LengthType>::isnaninf( grid_1_length ) );
  testPrecondition( grid_0_length >= QuantityTraits<LengthType>::zero() );
  testPrecondition( grid_1_length >= QuantityTraits<LengthType>::zero() );
  testPrecondition( grid_0_length + grid_1_length >
                    QuantityTraits<LengthType>::zero() );

  return LXInterpPolicy::interpolate( indep_var_x_0,
				      indep_var_x_1,
				      indep_var_x,
				      grid_0_length,
				      grid_1_length );
}

// Calculate the min value of an intermediate grid
template<typename ZYInterpPolicy, typename ZXInterpPolicy>
template<typename IndepType, typename LimitType>
inline LimitType
TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::calculateIntermediateGridLimit(
					 const IndepType indep_var_x_0,
					 const IndepType indep_var_x_1,
					 const IndepType indep_var_x,
					 const LimitType grid_0_y_limit,
					 const LimitType grid_1_y_limit )
{
  // Make sure the first independent variables are valid
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_x_0 ) );
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_x_1 ) );
  testPrecondition( !QuantityTraits<IndepType>::isnaninf( indep_var_x ) );
  testPrecondition( ThisType::isFirstIndepVarInValidRange( indep_var_x_0 ) );
  testPrecondition( indep_var_x_0 < indep_var_x_1 );
  testPrecondition( indep_var_x >= indep_var_x_0 );
  testPrecondition( indep_var_x <= indep_var_x_1 );
  // Make sure the grid min values are valid
  testPrecondition( ThisType::isSecondIndepVarInValidRange( grid_0_y_limit ) );
  testPrecondition( ThisType::isSecondIndepVarInValidRange( grid_1_y_limit ) );

  return YMinXInterpPolicy::interpolate( indep_var_x_0,
					 indep_var_x_1,
					 indep_var_x,
					 grid_0_y_limit,
					 grid_1_y_limit );
}

// Interpolate on the specified y grid
template<typename ZYInterpPolicy, typename ZXInterpPolicy>
template<TupleMember YIndepMember,
	 TupleMember DepMember,
	 typename YIterator,
	 typename ZIterator,
	 typename T>
inline T
TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::interpolateOnYGrid(
						  const T indep_var_y,
						  YIterator start_indep_y_grid,
						  YIterator end_indep_y_grid,
						  ZIterator start_dep_grid,
						  ZIterator end_dep_grid )
{
  // The interpolation type on the Z variable must be consistent
  testStaticPrecondition( (boost::is_same<typename ZYInterpPolicy::DepVarProcessingTag,typename ZXInterpPolicy::DepVarProcessingTag>::value) );
  // T must be a floating point type
  testStaticPrecondition( (boost::is_floating_point<T>::value) );
  // The y iterator must have T as the value type
  testStaticPrecondition( (boost::is_same<typename TupleMemberTraits<typename std::iterator_traits<YIterator>::value_type,YIndepMember>::tupleMemberType,T>::value) );
  // The z iterator must have T as the value type
  testStaticPrecondition( (boost::is_same<typename TupleMemberTraits<typename std::iterator_traits<ZIterator>::value_type,DepMember>::tupleMemberType,T>::value) );
  // Make sure the second independent variables are valid
  testPrecondition( start_indep_y_grid != end_indep_y_grid );
  testPrecondition( Sort::isSortedAscending<YIndepMember>( start_indep_y_grid,
							   end_indep_y_grid ));
  testPrecondition( ThisType::isSecondIndepVarInValidRange(
				get<YIndepMember>( *start_indep_y_grid ) ) );
  remember( YIterator true_end_indep_y_grid_test = end_indep_y_grid );
  remember( --true_end_indep_y_grid_test );
  testPrecondition( indep_var_y <= get<YIndepMember>(*true_end_indep_y_grid_test) ||
		    Policy::relError( indep_var_y, get<YIndepMember>(*true_end_indep_y_grid_test) ) <= s_tol );
  // Make sure the dependent variables are valid
  testPrecondition( start_dep_grid != end_dep_grid );
  testPrecondition( std::distance( start_indep_y_grid, end_indep_y_grid )==
		    std::distance( start_dep_grid, end_dep_grid ) );

  // Conduct the ZY interpolation on the y grid
  YIterator true_end_indep_y_grid = end_indep_y_grid;
  --true_end_indep_y_grid;

  T dep_var;

  if( indep_var_y < get<YIndepMember>( *true_end_indep_y_grid ) )
  {
    YIterator lower_y_bin_boundary =
      Search::binaryLowerBound<YIndepMember>( start_indep_y_grid,
					      end_indep_y_grid,
					      indep_var_y );

    YIterator upper_y_bin_boundary = lower_y_bin_boundary;
    ++upper_y_bin_boundary;

    ZIterator lower_dep_bin_boundary = start_dep_grid;
    std::advance( lower_dep_bin_boundary,
		  std::distance( start_indep_y_grid, lower_y_bin_boundary ) );

    ZIterator upper_dep_bin_boundary = lower_dep_bin_boundary;
    ++upper_dep_bin_boundary;

    dep_var = ZYInterpPolicy::interpolate(
				   get<YIndepMember>( *lower_y_bin_boundary ),
                                   get<YIndepMember>( *upper_y_bin_boundary ),
                                   indep_var_y,
                                   get<DepMember>( *lower_dep_bin_boundary ),
                                   get<DepMember>( *upper_dep_bin_boundary ) );
  }
  else if( indep_var_y == get<YIndepMember>( *true_end_indep_y_grid ) )
  {
    ZIterator true_end_dep_grid = end_dep_grid;
    --true_end_dep_grid;

    dep_var = get<DepMember>( *true_end_dep_grid );
  }
  else if( indep_var_y > get<YIndepMember>( *true_end_indep_y_grid ) &&
	   Policy::relError( indep_var_y, get<YIndepMember>( *true_end_indep_y_grid ) ) <= s_tol )
  {
    ZIterator true_end_dep_grid = end_dep_grid;
    --true_end_dep_grid;

    dep_var = get<DepMember>( *true_end_dep_grid );
  }

  return dep_var;
}

// Conduct the interpolation between two processed grids
/*! \details Make sure that the y variable lies inside of both grids - this
 * policy does not do extrapolation.
 */
template<typename ZYInterpPolicy, typename ZXInterpPolicy>
template<TupleMember YIndepMember,
	 TupleMember DepMember,
	 typename T,
	 typename YIterator,
	 typename ZIterator>
inline T TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::interpolateProcessed(
				      const T processed_indep_var_x_0,
				      const T processed_indep_var_x_1,
				      const T processed_indep_var_x,
				      const T processed_indep_var_y,
			              YIterator start_processed_indep_y_grid_0,
				      YIterator end_processed_indep_y_grid_0,
				      ZIterator start_processed_dep_grid_0,
				      ZIterator end_processed_dep_grid_0,
				      YIterator start_processed_indep_y_grid_1,
				      YIterator end_processed_indep_y_grid_1,
				      ZIterator start_processed_dep_grid_1,
				      ZIterator end_processed_dep_grid_1 )
{
  // The interpolation type on the Z variable must be consistent
  testStaticPrecondition( (boost::is_same<typename ZYInterpPolicy::DepVarProcessingTag,typename ZXInterpPolicy::DepVarProcessingTag>::value) );
  // T must be a floating point type
  testStaticPrecondition( (boost::is_floating_point<T>::value) );
  // The y iterator must have T as the value type
  testStaticPrecondition( (boost::is_same<typename TupleMemberTraits<typename std::iterator_traits<YIterator>::value_type,YIndepMember>::tupleMemberType,T>::value) );
  // The z iterator must have T as the value type
  testStaticPrecondition( (boost::is_same<typename TupleMemberTraits<typename std::iterator_traits<ZIterator>::value_type,DepMember>::tupleMemberType,T>::value) );
  // Make sure the first independent variables are valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf(
						   processed_indep_var_x_0 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf(
						   processed_indep_var_x_1 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf(
						   processed_indep_var_x ) );
  testPrecondition( processed_indep_var_x_0 < processed_indep_var_x_1 );
  testPrecondition( processed_indep_var_x >= processed_indep_var_x_0 );
  testPrecondition( processed_indep_var_x <= processed_indep_var_x_1 );
  // Make sure the second independent variables are valid
  testPrecondition( start_processed_indep_y_grid_0 !=
		    end_processed_indep_y_grid_0 );
  testPrecondition( Sort::isSortedAscending<YIndepMember>(
					      start_processed_indep_y_grid_0,
					      end_processed_indep_y_grid_0 ) );
  testPrecondition( start_processed_indep_y_grid_1 !=
		    end_processed_indep_y_grid_1 );
  testPrecondition( Sort::isSortedAscending<YIndepMember>(
					      start_processed_indep_y_grid_1,
					      end_processed_indep_y_grid_1 ) );
  // Make sure the right type of interpolation is being used
  // Note: if this fails - use unit base interpolation
  testPrecondition( processed_indep_var_y >=
		    get<YIndepMember>( *start_processed_indep_y_grid_0 ) );
  remember( YIterator true_end_processed_indep_y_grid_0 =
	    end_processed_indep_y_grid_0 );
  remember( --true_end_processed_indep_y_grid_0 );
  testPrecondition( processed_indep_var_y <=
		    get<YIndepMember>( *true_end_processed_indep_y_grid_0 ) );
  testPrecondition( processed_indep_var_y >=
		    get<YIndepMember>( *start_processed_indep_y_grid_1 ) );
  remember( YIterator true_end_processed_indep_y_grid_1 =
	    end_processed_indep_y_grid_1 );
  remember( --true_end_processed_indep_y_grid_1 );
  testPrecondition( processed_indep_var_y <=
		    get<YIndepMember>( *true_end_processed_indep_y_grid_1 ) );
  testPrecondition( processed_indep_var_y >=
		    get<YIndepMember>( *start_processed_indep_y_grid_1 ) );
  // Make sure the dependent variables are valid
  testPrecondition( start_processed_dep_grid_0 != end_processed_dep_grid_0 );
  testPrecondition( start_processed_dep_grid_1 != end_processed_dep_grid_1 );
  testPrecondition( std::distance( start_processed_indep_y_grid_0,
				   end_processed_indep_y_grid_0 ) ==
		    std::distance( start_processed_dep_grid_0,
				   end_processed_dep_grid_0 ) );
  testPrecondition( std::distance( start_processed_indep_y_grid_1,
				   end_processed_indep_y_grid_1 ) ==
		    std::distance( start_processed_dep_grid_1,
				   end_processed_dep_grid_1 ) );

  // Conduct the ZY interpolation on the first y grid
  T processed_dep_var_0 =
    interpolateAndProcessOnProcessedYGrid<YIndepMember,DepMember>(
						processed_indep_var_y,
						start_processed_indep_y_grid_0,
						end_processed_indep_y_grid_0,
						start_processed_dep_grid_0,
						end_processed_dep_grid_0 );

  // Conduct the ZY interpolation on the second y grid
  T processed_dep_var_1 =
    interpolateAndProcessOnProcessedYGrid<YIndepMember,DepMember>(
						processed_indep_var_y,
						start_processed_indep_y_grid_1,
						end_processed_indep_y_grid_1,
						start_processed_dep_grid_1,
						end_processed_dep_grid_1 );

  // Conduct the ZX interpolation
  T processed_slope = (processed_dep_var_1 - processed_dep_var_0)/
    (processed_indep_var_x_1 - processed_indep_var_x_0);

  return ZXInterpPolicy::interpolate( processed_indep_var_x_0,
				      processed_indep_var_x,
				      processed_dep_var_0,
				      processed_slope );
}

// Conduct the interpolation between two processed grids
/*! \details Make sure that the y variable lies inside of both grids - this
 * policy does not do extrapolation.
 */
template<typename ZYInterpPolicy, typename ZXInterpPolicy>
template<TupleMember YIndepMember,
	 TupleMember DepMember,
	 typename T,
	 typename Iterator>
inline T TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::interpolateProcessed(
					       const T processed_indep_var_x_0,
					       const T processed_indep_var_x_1,
					       const T processed_indep_var_x,
					       const T processed_indep_var_y,
					       Iterator start_processed_grid_0,
					       Iterator end_processed_grid_0,
					       Iterator start_processed_grid_1,
					       Iterator end_processed_grid_1 )
{
  // Make sure the tuple members are valid
  testStaticPrecondition( YIndepMember != DepMember );

  return TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::interpolateProcessed<YIndepMember,DepMember>(
					               processed_indep_var_x_0,
						       processed_indep_var_x_1,
						       processed_indep_var_x,
						       processed_indep_var_y,
						       start_processed_grid_0,
						       end_processed_grid_0,
						       start_processed_grid_0,
						       end_processed_grid_0,
						       start_processed_grid_1,
						       end_processed_grid_1,
						       start_processed_grid_1,
						       end_processed_grid_1 );
}

// Conduct the interpolation between two processed grids (no tuples)
/*! \details Make sure that the y variable lies inside of both grids - this
 * policy does not do extrapolation.
 */
template<typename ZYInterpPolicy, typename ZXInterpPolicy>
template<typename T, typename YIterator, typename ZIterator>
inline T TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::interpolateProcessed(
			              const T processed_indep_var_x_0,
				      const T processed_indep_var_x_1,
				      const T processed_indep_var_x,
				      const T processed_indep_var_y,
			              YIterator start_processed_indep_y_grid_0,
				      YIterator end_processed_indep_y_grid_0,
				      ZIterator start_processed_dep_grid_0,
				      ZIterator end_processed_dep_grid_0,
				      YIterator start_processed_indep_y_grid_1,
				      YIterator end_processed_indep_y_grid_1,
				      ZIterator start_processed_dep_grid_1,
				      ZIterator end_processed_dep_grid_1 )
{
  // Make sure no tuples are being used
  testStaticPrecondition( (boost::is_floating_point<typename std::iterator_traits<YIterator>::value_type>::value) );

  return TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::interpolateProcessed<FIRST,FIRST>(
					        processed_indep_var_x_0,
						processed_indep_var_x_1,
						processed_indep_var_x,
						processed_indep_var_y,
						start_processed_indep_y_grid_0,
						end_processed_indep_y_grid_0,
						start_processed_dep_grid_0,
						end_processed_dep_grid_0,
						start_processed_indep_y_grid_1,
						end_processed_indep_y_grid_1,
						start_processed_dep_grid_1,
						end_processed_dep_grid_1 );
}

// Conduct unit base interpolation between two processed grids
/*! \details Make sure that the y variable is valid (call
 * calculateIntermediateGridLimit to get the y range at x).
 */
template<typename ZYInterpPolicy, typename ZXInterpPolicy>
template<TupleMember YIndepMember,
	 TupleMember DepMember,
	 typename T,
	 typename YIterator,
	 typename ZIterator>
inline T TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::interpolateProcessedUnitBase(
				      const T processed_indep_var_x_0,
				      const T processed_indep_var_x_1,
				      const T processed_indep_var_x,
				      const T processed_indep_var_y,
				      YIterator start_processed_indep_y_grid_0,
				      YIterator end_processed_indep_y_grid_0,
				      ZIterator start_processed_dep_grid_0,
				      ZIterator end_processed_dep_grid_0,
				      YIterator start_processed_indep_y_grid_1,
				      YIterator end_processed_indep_y_grid_1,
				      ZIterator start_processed_dep_grid_1,
				      ZIterator end_processed_dep_grid_1 )
{
  // The interpolation type on the Z variable must be consistent
  testStaticPrecondition( (boost::is_same<typename ZYInterpPolicy::DepVarProcessingTag,typename ZXInterpPolicy::DepVarProcessingTag>::value) );
  // T must be a floating point type
  testStaticPrecondition( (boost::is_floating_point<T>::value) );
  // The y iterator must have T as the value type
  testStaticPrecondition( (boost::is_same<typename TupleMemberTraits<typename std::iterator_traits<YIterator>::value_type,YIndepMember>::tupleMemberType,T>::value) );
  // The z iterator must have T as the value type
  testStaticPrecondition( (boost::is_same<typename TupleMemberTraits<typename std::iterator_traits<ZIterator>::value_type,DepMember>::tupleMemberType,T>::value) );
  // Make sure the first independent variables are valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf(
						   processed_indep_var_x_0 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf(
						   processed_indep_var_x_1 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf(
						     processed_indep_var_x ) );
  testPrecondition( processed_indep_var_x_0 < processed_indep_var_x_1 );
  testPrecondition( processed_indep_var_x >= processed_indep_var_x_0 );
  testPrecondition( processed_indep_var_x <= processed_indep_var_x_1 );
  // Make sure the second independent variables are valid
  testPrecondition( start_processed_indep_y_grid_0 !=
		    end_processed_indep_y_grid_0 );
  testPrecondition( Sort::isSortedAscending<YIndepMember>(
					      start_processed_indep_y_grid_0,
					      end_processed_indep_y_grid_0 ) );
  testPrecondition( start_processed_indep_y_grid_1 !=
		    end_processed_indep_y_grid_1 );
  testPrecondition( Sort::isSortedAscending<YIndepMember>(
					      start_processed_indep_y_grid_1,
					      end_processed_indep_y_grid_1 ) );
  remember( T test_processed_y_min = calculateIntermediateProcessedGridLimit(
		      processed_indep_var_x_0,
		      processed_indep_var_x_1,
		      processed_indep_var_x,
		      get<YIndepMember>( *start_processed_indep_y_grid_0 ),
		      get<YIndepMember>( *start_processed_indep_y_grid_1 ) ) );
  testPrecondition( processed_indep_var_y >= test_processed_y_min ||
		    Policy::relError( processed_indep_var_y,
				      test_processed_y_min ) <= s_tol );
  remember( YIterator true_end_processed_indep_y_grid_0 =
	    end_processed_indep_y_grid_0 );
  remember( --true_end_processed_indep_y_grid_0 );
  remember( YIterator true_end_processed_indep_y_grid_1 =
	    end_processed_indep_y_grid_1 );
  remember( --true_end_processed_indep_y_grid_1 );
  remember( T test_processed_y_max = calculateIntermediateProcessedGridLimit(
		   processed_indep_var_x_0,
		   processed_indep_var_x_1,
		   processed_indep_var_x,
		   get<YIndepMember>( *true_end_processed_indep_y_grid_0 ),
		   get<YIndepMember>( *true_end_processed_indep_y_grid_1 ) ) );
  testPrecondition( processed_indep_var_y <= test_processed_y_max ||
		    Policy::relError( processed_indep_var_y,
				      test_processed_y_max ) <= s_tol );
  // Make sure the dependent variables are valid
  testPrecondition( start_processed_dep_grid_0 !=
		    end_processed_dep_grid_0 );
  testPrecondition( start_processed_dep_grid_1 !=
		    end_processed_dep_grid_1 );
  testPrecondition( std::distance( start_processed_indep_y_grid_0,
				   end_processed_indep_y_grid_0 ) ==
		    std::distance( start_processed_dep_grid_0,
				   end_processed_dep_grid_0 ) );
  testPrecondition( std::distance( start_processed_indep_y_grid_1,
				   end_processed_indep_y_grid_1 ) ==
		    std::distance( start_processed_dep_grid_1,
				   end_processed_dep_grid_1 ) );

  // Calculate the length of the first y grid
  const T L0 = calculateGridLengthProcessed<YIndepMember>(
						start_processed_indep_y_grid_0,
						end_processed_indep_y_grid_0 );

  // Calculate the length of the first y grid
  const T L1 = calculateGridLengthProcessed<YIndepMember>(
						start_processed_indep_y_grid_1,
						end_processed_indep_y_grid_1 );

  const T Lx = calculateIntermediateGridLengthProcessed(
						processed_indep_var_x_0,
						processed_indep_var_x_1,
						processed_indep_var_x,
						L0,
						L1 );

  // Calculate the intermediate y min
  const T processed_y_x_min = calculateIntermediateProcessedGridLimit(
			processed_indep_var_x_0,
			processed_indep_var_x_1,
			processed_indep_var_x,
			get<YIndepMember>( *start_processed_indep_y_grid_0 ),
			get<YIndepMember>( *start_processed_indep_y_grid_1 ) );

  // Calculate the unit base independent variable
  const T eta =
    ZYInterpPolicy::calculateUnitBaseIndepVarProcessed( processed_indep_var_y, 
                                                        processed_y_x_min, 
                                                        Lx );
  
  // Calculate the y value on the first grid
  T processed_indep_var_y_0 = ZYInterpPolicy::calculateProcessedIndepVar( 
			  eta,
			  get<YIndepMember>( *start_processed_indep_y_grid_0 ),
			  L0 );
  // Calculate the y value on the second grid
  T processed_indep_var_y_1 = ZYInterpPolicy::calculateProcessedIndepVar(
			  eta,
			  get<YIndepMember>( *start_processed_indep_y_grid_1 ),
			  L1 );

  // Conduct the ZY interpolation on the first y grid
  T processed_dep_var_0 =
    interpolateAndProcessOnProcessedYGrid<YIndepMember,DepMember>(
						processed_indep_var_y_0,
						start_processed_indep_y_grid_0,
						end_processed_indep_y_grid_0,
						start_processed_dep_grid_0,
						end_processed_dep_grid_0 );

  // Conduct the ZY interpolation on the second y grid
  T processed_dep_var_1 =
    interpolateAndProcessOnProcessedYGrid<YIndepMember,DepMember>(
						processed_indep_var_y_1,
						start_processed_indep_y_grid_1,
						end_processed_indep_y_grid_1,
						start_processed_dep_grid_1,
						end_processed_dep_grid_1 );

  // Conduct the ZX interpolation
  T scaled_processed_dep_var_0 = processed_dep_var_0*L0;

  T processed_slope = (processed_dep_var_1*L1 - scaled_processed_dep_var_0)/
    (processed_indep_var_x_1 - processed_indep_var_x_0 );

  T processed_dep_var_yx = ZXInterpPolicy::interpolateAndProcess(
						    processed_indep_var_x_0,
						    processed_indep_var_x,
						    scaled_processed_dep_var_0,
						    processed_slope )/Lx;

  return ZXInterpPolicy::recoverProcessedDepVar( processed_dep_var_yx );
}

// Conduct unit base interpolation between two processed grids
/*! \details Make sure that the y variable is valid (call
 * calculateIntermediateGridLimit to get the y range at x).
 */
template<typename ZYInterpPolicy, typename ZXInterpPolicy>
template<TupleMember YIndepMember,
	 TupleMember DepMember,
	 typename T,
	 typename Iterator>
inline T TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::interpolateProcessedUnitBase(
				      const T processed_indep_var_x_0,
				      const T processed_indep_var_x_1,
				      const T processed_indep_var_x,
				      const T processed_indep_var_y,
				      Iterator start_processed_grid_0,
				      Iterator end_processed_grid_0,
				      Iterator start_processed_grid_1,
				      Iterator end_processed_grid_1 )
{
  // Make sure the tuple members are valid
  testStaticPrecondition( YIndepMember != DepMember );

  return TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::interpolateProcessedUnitBase<YIndepMember,DepMember>(
						       processed_indep_var_x_0,
						       processed_indep_var_x_1,
						       processed_indep_var_x,
						       processed_indep_var_y,
						       start_processed_grid_0,
						       end_processed_grid_0,
						       start_processed_grid_0,
						       end_processed_grid_0,
						       start_processed_grid_1,
						       end_processed_grid_1,
						       start_processed_grid_1,
						       end_processed_grid_1 );
}

// Conduct unit base interpolation between two processed grids (no tuples)
/*! \details Make sure that the y variable is valid (call
 * calculateIntermediateGridLimit to get the y range at x).
 */
template<typename ZYInterpPolicy, typename ZXInterpPolicy>
template<typename T, typename YIterator, typename ZIterator>
inline T TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::interpolateProcessedUnitBase(
				      const T processed_indep_var_x_0,
				      const T processed_indep_var_x_1,
				      const T processed_indep_var_x,
				      const T processed_indep_var_y,
				      YIterator start_processed_indep_y_grid_0,
				      YIterator end_processed_indep_y_grid_0,
				      ZIterator start_processed_dep_grid_0,
				      ZIterator end_processed_dep_grid_0,
				      YIterator start_processed_indep_y_grid_1,
				      YIterator end_processed_indep_y_grid_1,
				      ZIterator start_processed_dep_grid_1,
				      ZIterator end_processed_dep_grid_1 )
{
  // Make sure no tuples are being used
  testStaticPrecondition( (boost::is_floating_point<typename std::iterator_traits<YIterator>::value_type>::value) );

  return TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::interpolateProcessedUnitBase<FIRST,FIRST>(
					        processed_indep_var_x_0,
						processed_indep_var_x_1,
						processed_indep_var_x,
						processed_indep_var_y,
					        start_processed_indep_y_grid_0,
						end_processed_indep_y_grid_0,
						start_processed_dep_grid_0,
						end_processed_dep_grid_0,
						start_processed_indep_y_grid_1,
						end_processed_indep_y_grid_1,
						start_processed_dep_grid_1,
						end_processed_dep_grid_1 );
}

// Calculate the length of a grid
template<typename ZYInterpPolicy, typename ZXInterpPolicy>
template<TupleMember YIndepMember,
	 typename YIterator>
inline typename TupleMemberTraits<typename std::iterator_traits<YIterator>::value_type,YIndepMember>::tupleMemberType
TwoDInterpolationPolicyImpl<ZYInterpPolicy,
			    ZXInterpPolicy>::calculateGridLengthProcessed(
					YIterator start_processed_indep_y_grid,
					YIterator end_processed_indep_y_grid )
{
  // The return type must be a floating point type
  testStaticPrecondition( (boost::is_floating_point<typename TupleMemberTraits<typename std::iterator_traits<YIterator>::value_type,YIndepMember>::tupleMemberType>::value) );
  // Make sure the grid is valid
  testPrecondition( start_processed_indep_y_grid !=
		    end_processed_indep_y_grid );
  testPrecondition( Sort::isSortedAscending<YIndepMember>(
						start_processed_indep_y_grid,
						end_processed_indep_y_grid ) );

  YIterator true_end_processed_y_grid = end_processed_indep_y_grid;
  --true_end_processed_y_grid;

  typename TupleMemberTraits<typename std::iterator_traits<YIterator>::value_type,YIndepMember>::tupleMemberType grid_length =
    get<YIndepMember>( *true_end_processed_y_grid ) -
    get<YIndepMember>( *start_processed_indep_y_grid );

  // Make sure the grid length is valid
  testPostcondition( grid_length >= 0.0 );

  return grid_length;
}

// Calculate the length of an intermediate grid
template<typename ZYInterpPolicy, typename ZXInterpPolicy>
template<typename T>
inline T TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::calculateIntermediateGridLengthProcessed(
					    const T processed_indep_var_x_0,
					    const T processed_indep_var_x_1,
					    const T processed_indep_var_x,
					    const T grid_0_length,
					    const T grid_1_length )
{
  // Make sure the first independent variables are valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf(
						   processed_indep_var_x_0 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf(
						   processed_indep_var_x_1 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf(
						     processed_indep_var_x ) );
  testPrecondition( processed_indep_var_x_0 < processed_indep_var_x_1 );
  testPrecondition( processed_indep_var_x >= processed_indep_var_x_0 );
  testPrecondition( processed_indep_var_x <= processed_indep_var_x_1 );
  // Make sure the grid lengths are valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( grid_0_length ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( grid_1_length ) );
  testPrecondition( grid_0_length >= 0.0 );
  testPrecondition( grid_1_length >= 0.0 );
  testPrecondition( grid_0_length + grid_1_length > 0.0 );

  T processed_slope = (grid_1_length - grid_0_length)/
    (processed_indep_var_x_1 - processed_indep_var_x_0);

  return LXInterpPolicy::interpolate( processed_indep_var_x_0,
				      processed_indep_var_x,
				      grid_0_length,
				      processed_slope );
}

// Calculate the min value of an intermediate grid
template<typename ZYInterpPolicy, typename ZXInterpPolicy>
template<typename T>
inline T TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::calculateIntermediateProcessedGridLimit(
					    const T processed_indep_var_x_0,
					    const T processed_indep_var_x_1,
					    const T processed_indep_var_x,
					    const T processed_grid_0_y_limit,
					    const T processed_grid_1_y_limit )
{
  // Make sure the first independent variables are valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf(
						   processed_indep_var_x_0 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf(
						   processed_indep_var_x_1 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf(
						     processed_indep_var_x ) );
  testPrecondition( processed_indep_var_x_0 < processed_indep_var_x_1 );
  testPrecondition( processed_indep_var_x >= processed_indep_var_x_0 );
  testPrecondition( processed_indep_var_x <= processed_indep_var_x_1 );
  // Make sure the grid min values are valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf(
						  processed_grid_0_y_limit ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf(
						  processed_grid_1_y_limit ) );

  T processed_slope = (processed_grid_1_y_limit - processed_grid_0_y_limit)/
    (processed_indep_var_x_1 - processed_indep_var_x_0);

  return YMinXInterpPolicy::interpolateAndProcess( processed_indep_var_x_0,
						   processed_indep_var_x,
						   processed_grid_0_y_limit,
						   processed_slope );
}

// Interpolate on the specified processed y grid
template<typename ZYInterpPolicy, typename ZXInterpPolicy>
template<TupleMember YIndepMember,
	 TupleMember DepMember,
	 typename YIterator,
	 typename ZIterator,
	 typename T>
inline T TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::interpolateAndProcessOnProcessedYGrid(
					const T processed_indep_var_y,
					YIterator start_processed_indep_y_grid,
					YIterator end_processed_indep_y_grid,
					ZIterator start_processed_dep_grid,
					ZIterator end_processed_dep_grid )
{
  // The interpolation type on the Z variable must be consistent
  testStaticPrecondition( (boost::is_same<typename ZYInterpPolicy::DepVarProcessingTag,typename ZXInterpPolicy::DepVarProcessingTag>::value) );
  // T must be a floating point type
  testStaticPrecondition( (boost::is_floating_point<T>::value) );
  // The y iterator must have T as the value type
  testStaticPrecondition( (boost::is_same<typename TupleMemberTraits<typename std::iterator_traits<YIterator>::value_type,YIndepMember>::tupleMemberType,T>::value) );
  // The z iterator must have T as the value type
  testStaticPrecondition( (boost::is_same<typename TupleMemberTraits<typename std::iterator_traits<ZIterator>::value_type,DepMember>::tupleMemberType,T>::value) );
  // Make sure the second independent variables are valid
  testPrecondition( start_processed_indep_y_grid !=
		    end_processed_indep_y_grid );
  testPrecondition( Sort::isSortedAscending<YIndepMember>(
						start_processed_indep_y_grid,
						end_processed_indep_y_grid ) );
  remember( YIterator true_end_processed_indep_y_grid_test =
	    end_processed_indep_y_grid );
  remember( --true_end_processed_indep_y_grid_test );
  testPrecondition( processed_indep_var_y <= get<YIndepMember>(*true_end_processed_indep_y_grid_test) ||
		    Policy::relError( processed_indep_var_y, get<YIndepMember>(*true_end_processed_indep_y_grid_test) ) <= s_tol )
  // Make sure the dependent variables are valid
  testPrecondition( start_processed_dep_grid != end_processed_dep_grid );
  testPrecondition( std::distance( start_processed_indep_y_grid,
				   end_processed_indep_y_grid ) ==
		    std::distance( start_processed_dep_grid,
				   end_processed_dep_grid ) );

  // Conduct the ZY interpolation on the first y grid
  YIterator true_end_processed_indep_y_grid = end_processed_indep_y_grid;
  --true_end_processed_indep_y_grid;

  T processed_dep_var;

  if( processed_indep_var_y <
      get<YIndepMember>( *true_end_processed_indep_y_grid ) )
  {
    YIterator lower_y_bin_boundary =
      Search::binaryLowerBound<YIndepMember>( start_processed_indep_y_grid,
					      end_processed_indep_y_grid,
					      processed_indep_var_y );

    YIterator upper_y_bin_boundary = lower_y_bin_boundary;
    ++upper_y_bin_boundary;

    ZIterator lower_dep_bin_boundary = start_processed_dep_grid;
    std::advance( lower_dep_bin_boundary,
		  std::distance( start_processed_indep_y_grid,
				 lower_y_bin_boundary ) );

    ZIterator upper_dep_bin_boundary = lower_dep_bin_boundary;
    ++upper_dep_bin_boundary;

    T processed_slope = (get<DepMember>( *upper_dep_bin_boundary ) -
			 get<DepMember>( *lower_dep_bin_boundary ))/
      (get<YIndepMember>( *upper_y_bin_boundary ) -
       get<YIndepMember>( *lower_y_bin_boundary ) );

    processed_dep_var = ZYInterpPolicy::interpolateAndProcess(
				  get<YIndepMember>( *lower_y_bin_boundary ),
				  processed_indep_var_y,
				  get<DepMember>( *lower_dep_bin_boundary ),
				  processed_slope );
  }
  else if( processed_indep_var_y == get<YIndepMember>( *true_end_processed_indep_y_grid ) )
  {
    ZIterator true_end_processed_dep_grid = end_processed_dep_grid;
    --true_end_processed_dep_grid;

    processed_dep_var = get<DepMember>( *true_end_processed_dep_grid );
  }
  else if( processed_indep_var_y > get<YIndepMember>( *true_end_processed_indep_y_grid ) &&
	   Policy::relError(
	     processed_indep_var_y,
	     get<YIndepMember>( *true_end_processed_indep_y_grid ) ) <= s_tol )
  {
    ZIterator true_end_processed_dep_grid = end_processed_dep_grid;
    --true_end_processed_dep_grid;

    processed_dep_var = get<DepMember>( *true_end_processed_dep_grid );
  }

  return processed_dep_var;
}

// The name of the policy
inline const std::string LinLinLin::name()
{
  return "LinLinLin";
}

// The name of the policy
inline const std::string LinLogLin::name()
{
  return "LinLogLin";
}

// The name of the policy
inline const std::string LinLinLog::name()
{
  return "LinLinLog";
}

// The name of the policy
inline const std::string LinLogLog::name()
{
  return "LinLogLog";
}

// The name of the policy
inline const std::string LogLinLin::name()
{
  return "LogLinLin";
}

// The name of the policy
inline const std::string LogLogLin::name()
{
  return "LogLogLin";
}

// The name of the policy
inline const std::string LogLinLog::name()
{
  return "LogLinLog";
}

// The name of the policy
inline const std::string LogLogLog::name()
{
  return "LogLogLog";
}

} // end Utility namespace

#endif // end UTILITY_TWO_D_INTERPOLATION_POLICY_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_TwoDInterpolationPolicy_def.hpp
//---------------------------------------------------------------------------//
