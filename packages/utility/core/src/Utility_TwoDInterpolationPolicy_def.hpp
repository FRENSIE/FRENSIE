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
#include <iterator>

// FRENSIE Includes
#include "Utility_SortAlgorithms.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Conduct the interpolation between two grids
template<ZYInterpPolicy,ZXInterpPolicy>
template<TupleMember YIndepMember,
	 TupleMember DepMember,
	 typename T, 
	 typename YIterator,
	 typename ZIterator>
inline T 
TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::interpolateGrids( 
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
  testStaticPrecondition( (boost::is_same<typename TupleMemberTraits<typename std::iterator_traits<ZIterator>::value_type,ZIndepMember>::tupleMemberType,T>::value) );
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
  testPrecondition( start_indep_var_y_1 != end_indep_var_y_1 );
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
  YIterator lower_y_bin_boundary =
    Search::binaryLowerBound<YIndepMember>( start_indep_y_grid_0,
					    end_indep_y_grid_0,
					    indep_var_y );
    
  YIterator upper_y_bin_boundary = lower_y_bin_boundary;
  ++upper_y_bin_boundary;
  
  ZIterator lower_dep_bin_boundary = start_dep_grid_0;
  std::advance( lower_dep_bin_boundary, 
		std::distance( start_indep_y_grid_0, 
			       lower_y_bin_boundary ) );
  
  ZIterator upper_dep_bin_boundary = lower_dep_bin_boundary;
  ++upper_dep_bin_boundary;
  
  T processed_dep_var_0 = ZYInterpPolicy::interpolateAndProcess(
				  get<YIndepMember>( lower_y_bin_boundary ),
				  get<YIndepMember>( upper_y_bin_bouneary ),
				  indep_var_y,
				  get<DepMember>( lower_dep_bin_boundary ),
				  get<DepMember>( upper_dep_bin_boundary ) );

  // Conduct the ZY interpolation on the second y grid
  lower_y_bin_boundary = 
    Search::binaryLowerBound<YIndepMember>( start_indep_y_grid_1,
					    end_indep_y_grid_1,
					    indep_var_y );

  upper_y_bin_boundary = lower_y_bin_boundary;
  ++upper_y_bin_boundary;

  lower_dep_bin_boundary = start_dep_grid_1;
  std::advance( lower_dep_bin_boundary, 
		std::distance( start_indep_y_grid_1, 
			       lower_y_bin_boundary ) );
  
  upper_dep_bin_boundary = lower_dep_bin_boundary;
  ++upper_dep_bin_boundary;
  
  T processed_dep_var_1 = ZYInterpPolicy::interpolateAndProcess(
				  get<YIndepMember>( lower_y_bin_boundary ),
				  get<YIndepMember>( upper_y_bin_bouneary ),
				  indep_var_y,
				  get<DepMember>( lower_dep_bin_boundary ),
				  get<DepMember>( upper_dep_bin_boundary ) );

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
template<ZYInterpPolicy,ZXInterpPolicy>
template<TupleMember YIndepMember,
	 TupleMember DepMember,
	 typename T, 
	 typename Iterator>
inline T 
TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::interpolateGrids( 
						const T indep_var_x_0,
						const T indep_var_x_1,
						const T indep_var_x,
						const T indep_var_y,
			                        Iterator start_grid_0,
						Iterator end_grid_0,
						Iterator start_grid_1,
						Iterator end_grid_1 )
{
  // The interpolation type on the Z variable must be consistent
  testStaticPrecondition( (boost::is_same<typename ZYInterpPolicy::DepVarProcessingTag,typename ZXInterpPolicy::DepVarProcessingTag>::value) );
  // T must be a floating point type
  testStaticPrecondition( (boost::is_floating_point<T>::value) );
  // The y iterator must have T as the value type
  testStaticPrecondition( (boost::is_same<typename TupleMemberTraits<typename std::iterator_traits<Iterator>::value_type,YIndepMember>::tupleMemberType,T>::value) );
  // The z iterator must have T as the value type
  testStaticPrecondition( (boost::is_same<typename TupleMemberTraits<typename std::iterator_traits<Iterator>::value_type,ZIndepMember>::tupleMemberType,T>::value) );
  // Make sure the first independent variables are valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( indep_var_x_0 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( indep_var_x_1 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( indep_var_x ) );
  testPrecondition( ZXInterpPolicy::isIndepVarInValidRange( indep_var_x_0 ) );
  testPrecondition( indep_var_x_0 < indep_var_x_1 );
  testPrecondition( indep_var_x >= indep_var_x_0 );
  testPrecondition( indep_var_x <= indep_var_x_1 );
  // Make sure the second independent variables are valid
  testPrecondition( start_grid_0 != end_grid_0 );
  testPrecondition( Sort::isSortedAscending<YIndepMember>( start_grid_0,
							   end_grid_0 ) );
  testPrecondition( ZYInterpPolicy::isIndepVarInValidRange( 
				get<YIndepMember>( *start_grid_0 ) ) );
  testPrecondition( start_indep_var_y_1 != end_indep_var_y_1 );
  testPrecondition( Sort::isSortedAscending<YIndepMember>( start_grid_1,
							   end_grid_1 ) );
  testPrecondition( ZYInterpPolicy::isIndepVarInValidRange( 
				get<YIndepMember>( *start_grid_1 ) ) );
  // Make sure the right type of interpolation is being used
  // Note: if this fails - use unit base interpolation
  testPrecondition( indep_var_y >= get<YIndepMember>( *start_grid_0 ) );
  remember( Iterator true_end_grid_0 = end_grid_0 );
  remember( --true_end_grid_0 );
  testPrecondition(indep_var_y <= get<YIndepMember>( *true_end_grid_0 ) );
  testPrecondition( indep_var_y >= get<YIndepMember>( *start_grid_1 ) );
  remember( Iterator true_end_grid_1 = end_grid_1 );
  remember( --true_end_grid_1 );
  testPrecondition(indep_var_y <= get<YIndepMember>( *true_end_grid_1 ) );
    
  // Conduct the ZY interpolation on the first y grid
  Iterator lower_bin_boundary =
    Search::binaryLowerBound<YIndepMember>( start_grid_0, 
					    end_grid_0,
					    indep_var_y );
    
  Iterator upper_bin_boundary = lower_bin_boundary;
  ++upper_bin_boundary;
  
  T processed_dep_var_0 = ZYInterpPolicy::interpolateAndProcess(
				  get<YIndepMember>( lower_bin_boundary ),
				  get<YIndepMember>( upper_bin_bouneary ),
				  indep_var_y,
				  get<DepMember>( lower_bin_boundary ),
				  get<DepMember>( upper_bin_boundary ) );

  // Conduct the ZY interpolation on the second y grid
  lower_bin_boundary = 
    Search::binaryLowerBound<YIndepMember>( start_grid_1,
					    end_grid_1,
					    indep_var_y );

  upper_bin_boundary = lower_bin_boundary;
  ++upper_bin_boundary;

  T processed_dep_var_1 = ZYInterpPolicy::interpolateAndProcess(
				  get<YIndepMember>( lower_bin_boundary ),
				  get<YIndepMember>( upper_bin_bouneary ),
				  indep_var_y,
				  get<DepMember>( lower_bin_boundary ),
				  get<DepMember>( upper_bin_boundary ) );

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

// Conduct the interpolation between two grids (no tuples)
template<ZYInterpPolicy,ZXInterpPolicy>
template<typename T, typename YIterator, typename ZIterator>
inline T 
TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::interpolateGrids( 
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
  return TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::interpolateGrids<FIRST,FIRST>( 
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
template<ZYInterpPolicy,ZXInterpPolicy>
template<TupleMember YIndepMember,
	 TupleMember DepMember,
	 typename T, 
	 typename YIterator,
	 typename ZIterator>
inline T TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy>::interpolateProcessedGridsUnitBase( 
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
  testStaticPrecondition( (boost::is_same<typename TupleMemberTraits<typename std::iterator_traits<ZIterator>::value_type,ZIndepMember>::tupleMemberType,T>::value) );
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
  testPrecondition( start_indep_var_y_1 != end_indep_var_y_1 );
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
  YIterator true_end_y_grid = end_indep_y_grid_0;
  --true_end;
  
  T processed_y_0_min = 
    ZYInterpPolicy::processIndepVar( get<YIndepMember>(start_indep_y_grid_0) );

  T L0 = processed_y_0_min -
    ZYInterpPolicy::processIndepVar( get<YIndepMember>(true_end_y_grid) );

  // Calculate the length of the first y grid
  true_end_y_grid = end_indep_y_grid_0;
  --true_end;

  T processed_y_1_min = 
    ZYInterpPolicy::processIndepVar( get<YIndepMember>(start_indep_y_grid_1) );

  T L1 = processed_y_1_min -
    ZYInterpPolicy::processIndepVar( get<YIndepMember>(true_end_y_grid) );

  // Calculate the intermediate length
  typedef UnitBaseHelper<LinIndepVarProcessingTag,
			 ZXInterpPolicy::IndepVarProcessingTag>::YXInterpPolicy
    LXInterpPolicy;
  
  T Lx = LXInterpPolicy::interpolate( indep_var_x_0,
				      indep_var_x_1,
				      indep_var_x,
				      L0,
				      L1 );

  // Calculate the intermediate y min
  typedef UnitBaseHelper<ZYInterpPolicy::IndepVarProcessingTag,
			 ZXInterpPolicy::IndepVarProcessingTag>::YXInterpPolicy
    YMinXInterpPolicy;

  T processed_y_x_min = YMinXInterpPolicy::interpolateAndProcess( 
				  indep_var_x_0,
				  indep_var_x_1,
				  indep_var_x,
				  get<YIndepMember>( *start_indep_y_grid_0 ),
				  get<YIndepMember>( *start_indep_y_grid_1 ) );

  // Calculate the unit base independent variable
  T eta = (ZYInterpPolicy::processIndepVar(indep_var_y)-processed_y_x_min)/Lx;

  // Calculate the y value on the first grid
  T indep_var_y_0 = 
    ZYInerpPolicy::recoverProcessedIndepVar( processed_y_0_min - L0*eta );

  // Calculate the y value on the second grid
  T indep_var_y_1 = 
    ZYInterpPolicy::recoverProcessedIndepVar( processed_y_1_min - L1*eta );
  
  // Conduct the ZY interpolation on the first y grid
  YIterator lower_y_bin_boundary =
    Search::binaryLowerBound<YIndepMember>( start_indep_y_grid_0,
					    end_indep_y_grid_0,
					    indep_var_y_0 );
    
  YIterator upper_y_bin_boundary = lower_y_bin_boundary;
  ++upper_y_bin_boundary;
  
  ZIterator lower_dep_bin_boundary = start_dep_grid_0;
  std::advance( lower_dep_bin_boundary, 
		std::distance( start_indep_y_grid_0, 
			       lower_y_bin_boundary ) );
  
  ZIterator upper_dep_bin_boundary = lower_dep_bin_boundary;
  ++upper_dep_bin_boundary;
  
  T processed_dep_var_0 = ZYInterpPolicy::interpolateAndProcess(
				  get<YIndepMember>( lower_y_bin_boundary ),
				  get<YIndepMember>( upper_y_bin_bouneary ),
				  indep_var_y_0,
				  get<DepMember>( lower_dep_bin_boundary ),
				  get<DepMember>( upper_dep_bin_boundary ) ); 

  // Conduct the ZY interpolation on the second y grid
  lower_y_bin_boundary = 
    Search::binaryLowerBound<YIndepMember>( start_indep_y_grid_1,
					    end_indep_y_grid_1,
					    indep_var_y_1 );

  upper_y_bin_boundary = lower_y_bin_boundary;
  ++upper_y_bin_boundary;

  lower_dep_bin_boundary = start_dep_grid_1;
  std::advance( lower_dep_bin_boundary, 
		std::distance( start_indep_y_grid_1, 
			       lower_y_bin_boundary ) );
  
  upper_dep_bin_boundary = lower_dep_bin_boundary;
  ++upper_dep_bin_boundary;
  
  T processed_dep_var_1 = ZYInterpPolicy::interpolateAndProcess(
				  get<YIndepMember>( lower_y_bin_boundary ),
				  get<YIndepMember>( upper_y_bin_bouneary ),
				  indep_var_y_1,
				  get<DepMember>( lower_dep_bin_boundary ),
				  get<DepMember>( upper_dep_bin_boundary ) );

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

} // end Utility namespace

#endif // end UTILITY_TWO_D_INTERPOLATION_POLICY_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_TwoDInterpolationPolicy_def.hpp
//---------------------------------------------------------------------------//
