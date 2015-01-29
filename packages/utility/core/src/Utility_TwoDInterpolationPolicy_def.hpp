//---------------------------------------------------------------------------//
//!
//! \file   Utility_TwoDInterpolationPolicy_def.hpp
//! \author Alex Robinson
//! \brief  Policy struct declarations for interpolating on 2D grids
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TWO_D_INTERPOLATION_POLICY_DEF_HPP
#define UTILITY_TWO_D_INTERPOLATION_POLICY_DEF_HPP

// FRENSIE Includes
#include "Utility_SortAlgorithms.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Conduct the interpolation between two grids
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
  testPrecondition( ZXInterpPolicy::isIndepVarInValidRange( indep_var_x_0 ) );
  testPrecondition( indep_var_x_0 < indep_var_x_1 );
  testPrecondition( indep_var_x >= indep_var_x_0 );
  testPrecondition( indep_var_x <= indep_var_x_1 );
  // Make sure the second independent variables are valid
  testPrecondition( start_indep_y_grid_0 != end_indep_y_grid_0 );
  testPrecondition( Sort::isSortedAscending<YIndepMember>(start_indep_y_grid_0,
							  end_indep_y_grid_0));
  testPrecondition( ZYInterpPolicy::isIndepVarInValidRange( 
				get<YIndepMember>( *start_indep_y_grid_0 ) ) );
  testPrecondition( start_indep_y_grid_1 != end_indep_y_grid_1 );
  testPrecondition( Sort::isSortedAscending<YIndepMember>(start_indep_y_grid_1,
							  end_indep_y_grid_1));
  testPrecondition( ZYInterpPolicy::isIndepVarInValidRange( 
				get<YIndepMember>( *start_indep_y_grid_1 ) ) );
  // Make sure the right type of interpolation is being used
  // Note: if this fails - use unit base interpolation
  testPrecondition( indep_var_y >= get<YIndepMember>( *start_indep_y_grid_0 ));
  remember( YIterator true_end_indep_y_grid_0 = end_indep_y_grid_0 );
  remember( --true_end_indep_y_grid_0 );
  testPrecondition(indep_var_y <= get<YIndepMember>(*true_end_indep_y_grid_0));
  testPrecondition( indep_var_y >= get<YIndepMember>( *start_indep_y_grid_1 ));
  remember( YIterator true_end_indep_y_grid_1 = end_indep_y_grid_1 );
  remember( --true_end_indep_y_grid_1 );
  testPrecondition(indep_var_y <= get<YIndepMember>(*true_end_indep_y_grid_1));
  // Make sure the dependent variables are valid
  testPrecondition( start_dep_grid_0 != end_dep_grid_0 );
  testPrecondition( start_dep_grid_1 != end_dep_grid_1 );
  testPrecondition( std::distance( start_indep_y_grid_0, end_indep_y_grid_0 )==
		    std::distance( start_dep_grid_0, end_dep_grid_0 ) );
  testPrecondition( std::distance( start_indep_y_grid_1, end_indep_y_grid_1 )==
		    std::distance( start_dep_grid_1, end_dep_grid_1 ) );
  
  // Conduct the ZY interpolation on the first y grid
  T processed_dep_var_0 = 
    interpolateAndProcessOnYGrid<YIndepMember,DepMember>( indep_var_y,
							  start_indep_y_grid_0,
							  end_indep_y_grid_0,
							  start_dep_grid_0,
							  end_dep_grid_0 );
  
  // Conduct the ZY interpolation on the second y grid
  T processed_dep_var_1 = interpolateAndProcessOnYGrid<YIndepMember,DepMember>(
							  indep_var_y,
							  start_indep_y_grid_1,
							  end_indep_y_grid_1,
							  start_dep_grid_1,
							  end_dep_grid_1 );
  
  // Conduct the ZX interpolation
  T processed_indep_var_x_0 = ZXInterpPolicy::processIndepVar( indep_var_x_0 );
  
  T processed_slope = (processed_dep_var_1 - processed_dep_var_0)/
    (ZXInterpPolicy::processIndepVar( indep_var_x_1 ) - 
     processed_indep_var_x_0 );
  
  return ZXInterpPolicy::interpolate( 
				processed_indep_var_x_0,
				ZXInterpPolicy::processIndepVar( indep_var_x ),
				processed_dep_var_0,
				processed_slope );
}

// Conduct the interpolation between two grids
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
  return TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::interpolate<YIndepMember,DepMember>(
						                 indep_var_x_0,
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
  
  return TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::interpolate<FIRST,FIRST>( 
							  indep_var_x_0,
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

// Conduct unit base interpolation between two processed grids
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
  testPrecondition( ZXInterpPolicy::isIndepVarInValidRange( indep_var_x_0 ) );
  testPrecondition( indep_var_x_0 < indep_var_x_1 );
  testPrecondition( indep_var_x >= indep_var_x_0 );
  testPrecondition( indep_var_x <= indep_var_x_1 );
  // Make sure the second independent variables are valid
  testPrecondition( start_indep_y_grid_0 != end_indep_y_grid_0 );
  testPrecondition( Sort::isSortedAscending<YIndepMember>(start_indep_y_grid_0,
							  end_indep_y_grid_0));
  testPrecondition( ZYInterpPolicy::isIndepVarInValidRange( 
				get<YIndepMember>( *start_indep_y_grid_0 ) ) );
  testPrecondition( start_indep_y_grid_1 != end_indep_y_grid_1 );
  testPrecondition( Sort::isSortedAscending<YIndepMember>(start_indep_y_grid_1,
							  end_indep_y_grid_1));
  testPrecondition( ZYInterpPolicy::isIndepVarInValidRange( 
				get<YIndepMember>( *start_indep_y_grid_1 ) ) );
  testPrecondition( indep_var_y >= get<YIndepMember>( *start_indep_y_grid_0 )||
		    indep_var_y >= get<YIndepMember>( *start_indep_y_grid_1 ));
  remember( YIterator true_end_indep_y_grid_0 = end_indep_y_grid_0 );
  remember( --true_end_indep_y_grid_0 );
  remember( YIterator true_end_indep_y_grid_1 = end_indep_y_grid_1 );
  remember( --true_end_indep_y_grid_1 );
  testPrecondition(indep_var_y <= get<YIndepMember>(*true_end_indep_y_grid_0)||
		   indep_var_y <= get<YIndepMember>(*true_end_indep_y_grid_1));
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
  
  const T Lx = calculateIntermediateGridLength( indep_var_x_0,
						indep_var_x_1,
						indep_var_x,
						L0,
						L1 );
  
  // Calculate the intermediate y min
  const T y_x_min = calculateIntermediateGridMin( 
				  indep_var_x_0,
				  indep_var_x_1,
				  indep_var_x,
				  get<YIndepMember>( *start_indep_y_grid_0 ),
				  get<YIndepMember>( *start_indep_y_grid_1 ) );
  
  // Calculate the unit base independent variable
  const T eta = calculateUnitBaseIndepVar( indep_var_y, y_x_min, Lx );
  
  // Calculate the y value on the first grid
  T indep_var_y_0 = calculateGridIndepVar( 
				    eta,
				    get<YIndepMember>( *start_indep_y_grid_0 ),
				    L0 );
  // Calculate the y value on the second grid
  T indep_var_y_1 = calculateGridIndepVar(
				    eta,
				    get<YIndepMember>( *start_indep_y_grid_1 ),
				    L1 );
  
  // Conduct the ZY interpolation on the first y grid
  T processed_dep_var_0 = interpolateAndProcessOnYGrid<YIndepMember,DepMember>(
							  indep_var_y_0,
							  start_indep_y_grid_0,
							  end_indep_y_grid_0,
							  start_dep_grid_0,
							  end_dep_grid_0 );
  
  // Conduct the ZY interpolation on the second y grid
  T processed_dep_var_1 = interpolateAndProcessOnYGrid<YIndepMember,DepMember>(
							  indep_var_y_1,
							  start_indep_y_grid_1,
							  end_indep_y_grid_1,
							  start_dep_grid_1,
							  end_dep_grid_1 );

  // Conduct the ZX interpolation
  T processed_indep_var_x_0 = ZXInterpPolicy::processIndepVar( indep_var_x_0 );
  T processed_slope = (processed_dep_var_1*L1 - processed_dep_var_0*L0)/
    (ZXInterpPolicy::processIndepVar( indep_var_x_1 ) - 
     processed_indep_var_x_0 );

  T processed_dep_var_yx = ZXInterpPolicy::interpolateAndProcess( 
				processed_indep_var_x_0,
				ZXInterpPolicy::processIndepVar( indep_var_x ),
				processed_dep_var_0*L0,
				processed_slope )/Lx;
  
  return ZXInterpPolicy::recoverProcessedDepVar( processed_dep_var_yx );
}

// Conduct the interpolation between two grids
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
  return TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::interpolateUnitBase<YIndepMember,DepMember>(
							         indep_var_x_0,
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
  
  TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::interpolateUnitBase<FIRST,FIRST>(
							   indep_var_x_0,
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
template<TupleMember YIndepMember,
	 typename YIterator>
inline typename TupleMemberTraits<typename std::iterator_traits<YIterator>::value_type,YIndepMember>::tupleMemberType 
TwoDInterpolationPolicyImpl<ZYInterpPolicy,
			    ZXInterpPolicy>::calculateGridLength( 
						  YIterator start_indep_y_grid,
						  YIterator end_indep_y_grid )
{
  // The return type must be a floating point type
  testStaticPrecondition( (boost::is_floating_point<typename TupleMemberTraits<typename std::iterator_traits<YIterator>::value_type,YIndepMember>::tupleMemberType>::value) );
  // Make sure the grid is valid
  testPrecondition( ZYInterpPolicy::isIndepVarInValidRange( 
				get<YIndepMember>( *start_indep_y_grid ) ) );
  testPrecondition( start_indep_y_grid != end_indep_y_grid );
  testPrecondition( Sort::isSortedAscending<YIndepMember>( start_indep_y_grid,
							   end_indep_y_grid ));
  
  YIterator true_end_y_grid = end_indep_y_grid;
  --true_end_y_grid;
  
  typename TupleMemberTraits<typename std::iterator_traits<YIterator>::value_type,YIndepMember>::tupleMemberType grid_length = 
    ZYInterpPolicy::processIndepVar( get<YIndepMember>( *true_end_y_grid ) )-
    ZYInterpPolicy::processIndepVar( get<YIndepMember>( *start_indep_y_grid ));
  
  // Make sure the grid length is valid
  testPostcondition( grid_length > 0.0 );

  return grid_length;
}

// Calculate the length of an intermediate grid
template<typename ZYInterpPolicy, typename ZXInterpPolicy>
template<typename T>
inline T 
TwoDInterpolationPolicyImpl<ZYInterpPolicy,
			    ZXInterpPolicy>::calculateIntermediateGridLength( 
					    const T indep_var_x_0,
					    const T indep_var_x_1,
					    const T indep_var_x,
					    const T grid_0_length,
					    const T grid_1_length )
{
  // Make sure the first independent variables are valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( indep_var_x_0 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( indep_var_x_1 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( indep_var_x ) );
  testPrecondition( ZXInterpPolicy::isIndepVarInValidRange( indep_var_x_0 ) );
  testPrecondition( indep_var_x_0 < indep_var_x_1 );
  testPrecondition( indep_var_x >= indep_var_x_0 );
  testPrecondition( indep_var_x <= indep_var_x_1 );
  // Make sure the grid lengths are valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( grid_0_length ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( grid_1_length ) );
  testPrecondition( grid_0_length > 0.0 );
  testPrecondition( grid_1_length > 0.0 );
  
  return LXInterpPolicy::interpolate( indep_var_x_0,
				      indep_var_x_1,
				      indep_var_x,
				      grid_0_length,
				      grid_1_length );
}

// Calculate the min value of an intermediate grid
template<typename ZYInterpPolicy, typename ZXInterpPolicy>
template<typename T>
inline T 
TwoDInterpolationPolicyImpl<ZYInterpPolicy,
			    ZXInterpPolicy>::calculateIntermediateGridMin( 
					 const T indep_var_x_0,
					 const T indep_var_x_1,
					 const T indep_var_x,
					 const T grid_0_y_min,
					 const T grid_1_y_min )
{
  // Make sure the first independent variables are valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( indep_var_x_0 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( indep_var_x_1 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( indep_var_x ) );
  testPrecondition( ZXInterpPolicy::isIndepVarInValidRange( indep_var_x_0 ) );
  testPrecondition( indep_var_x_0 < indep_var_x_1 );
  testPrecondition( indep_var_x >= indep_var_x_0 );
  testPrecondition( indep_var_x <= indep_var_x_1 );
  // Make sure the grid min values are valid
  testPrecondition( ZYInterpPolicy::isIndepVarInValidRange( grid_0_y_min ) );
  testPrecondition( ZYInterpPolicy::isIndepVarInValidRange( grid_1_y_min ) );

  return YMinXInterpPolicy::interpolate( indep_var_x_0,
					 indep_var_x_1,
					 indep_var_x,
					 grid_0_y_min,
					 grid_1_y_min );
}
  
// Calculate the unit base independent variable (eta)
template<typename ZYInterpPolicy, typename ZXInterpPolicy>
template<typename T>
inline T 
TwoDInterpolationPolicyImpl<ZYInterpPolicy,
			    ZXInterpPolicy>::calculateUnitBaseIndepVar( 
				      const T indep_var_y,
				      const T intermediate_indep_var_y_min,
				      const T intermediate_grid_length )
{
  // Make sure the intermediate grid min indep var is valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( 
					      intermediate_indep_var_y_min ) );
  testPrecondition( ZYInterpPolicy::isIndepVarInValidRange(
					      intermediate_indep_var_y_min ) );
  // Make sure the independent y variable is valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( indep_var_y ) );
  testPrecondition( ZYInterpPolicy::isIndepVarInValidRange( indep_var_y ) );
  testPrecondition( indep_var_y >= intermediate_indep_var_y_min );
  remember( double test_difference = 
	    ZYInterpPolicy::processIndepVar(indep_var_y) -
	    ZYInterpPolicy::processIndepVar(intermediate_indep_var_y_min) );
  testPrecondition( test_difference/intermediate_grid_length <= 1.0+1e-12 );
  // Make sure the intermediate grid length is valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( 
						  intermediate_grid_length ) );
  testPrecondition( intermediate_grid_length > 0.0 );
  
  T eta = (ZYInterpPolicy::processIndepVar(indep_var_y) - 
	   ZYInterpPolicy::processIndepVar(intermediate_indep_var_y_min))/
    intermediate_grid_length;

  // Check for rounding errors
  if( eta > 1.0 )
  {
    if( eta - 1.0 < 1e-12 )
      eta = 1.0;
  }
  else if( eta < 0.0 )
  {
    if( eta > -1e-12 )
      eta = 0.0;
  }
  
  // Make sure eta is valid
  testPostcondition( eta >= 0.0 );
  testPostcondition( eta <= 1.0 );

  return eta;
}

// Calculate the independent y variable on a grid given eta
template<typename ZYInterpPolicy, typename ZXInterpPolicy>
template<typename T>
inline T TwoDInterpolationPolicyImpl<ZYInterpPolicy,
				     ZXInterpPolicy>::calculateGridIndepVar( 
						    const T eta,
					            const T grid_indep_var_min,
						    const T grid_length )
{
  // Make sure the eta value is valid
  testPrecondition( eta >= 0.0 );
  testPrecondition( eta <= 1.0 );
  // Make sure the grid min indep var is valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( grid_indep_var_min ));
  testPrecondition( ZYInterpPolicy::isIndepVarInValidRange( 
							grid_indep_var_min ) );
  // Make sure the grid length is valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( grid_length ) );
  testPrecondition( grid_length > 0.0 );
  
  return ZYInterpPolicy::recoverProcessedIndepVar( 
	                ZYInterpPolicy::processIndepVar( grid_indep_var_min ) +
			grid_length*eta );
}

// Interpolate on the specified y grid
template<typename ZYInterpPolicy, typename ZXInterpPolicy>
template<TupleMember YIndepMember,
	 TupleMember DepMember,
	 typename YIterator,
	 typename ZIterator,
	 typename T>
inline T 
TwoDInterpolationPolicyImpl<ZYInterpPolicy,
			    ZXInterpPolicy>::interpolateAndProcessOnYGrid( 
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
  testPrecondition( ZYInterpPolicy::isIndepVarInValidRange( 
				get<YIndepMember>( *start_indep_y_grid ) ) );
  remember( YIterator true_end_indep_y_grid_test = end_indep_y_grid );
  remember( --true_end_indep_y_grid_test );
  testPrecondition(
	       indep_var_y <= get<YIndepMember>(*true_end_indep_y_grid_test) ||
	       indep_var_y <= get<YIndepMember>(*true_end_indep_y_grid_test ));
  // Make sure the dependent variables are valid
  testPrecondition( start_dep_grid != end_dep_grid );
  testPrecondition( std::distance( start_indep_y_grid, end_indep_y_grid )==
		    std::distance( start_dep_grid, end_dep_grid ) );
  
  // Conduct the ZY interpolation on the first y grid
  YIterator true_end_indep_y_grid = end_indep_y_grid;
  --true_end_indep_y_grid;
  
  T processed_dep_var;
  
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
    
    processed_dep_var = ZYInterpPolicy::interpolateAndProcess(
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
    
    processed_dep_var = ZYInterpPolicy::processDepVar( 
					get<DepMember>( *true_end_dep_grid ) );
  }

  return processed_dep_var;
}

} // end Utility namespace

#endif // end UTILITY_TWO_D_INTERPOLATION_POLICY_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_TwoDInterpolationPolicy_def.hpp
//---------------------------------------------------------------------------//
