//---------------------------------------------------------------------------//
//!
//! \file   Utility_TwoDInterpolationPolicy.hpp
//! \author Alex Robinson
//! \brief  Policy struct declarations for interpolating on 2D grids
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TWO_D_INTERPOLATION_POLICY_HPP
#define UTILITY_TWO_D_INTERPOLATION_POLICY_HPP

// Std Lib Includes
#include <iterator>

// FRENSIE Includes
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_TupleMemberTraits.hpp"

namespace Utility{

namespace {

//! Helper class used by unit base interpolation methods (Lin-Lin)
template<typename YProcessingTag, typename XProcessingTag>
struct UnitBaseHelper
{ /* ... */ };

//! Helper class used by unit base interpolation methods (Lin-Lin)
template<>
struct UnitBaseHelper<LinIndepVarProcessingTag,LinIndepVarProcessingTag>
{
  //! The YX interpolation policy
  typedef LinLin YXInterpPolicy;
};

//! Helper class used by unit base interpolation methods (Lin-Log)
template<>
struct UnitBaseHelper<LinIndepVarProcessingTag,LogIndepVarProcessingTag>
{
  //! The YX interpolation policy
  typedef LinLog YXInterpPolicy;
};
  
//! Helper class used by unit base interpolation methods (Log-Lin)
template<>
struct UnitBaseHelper<LogIndepVarProcessingTag,LinIndepVarProcessingTag>
{
  //! The YX interpolation policy
  typedef LogLin YXInterpPolicy;
};

//! Helper class used by unit base interpolation methods (Log-Lin)
template<>
struct UnitBaseHelper<LogIndepVarProcessingTag,LogIndepVarProcessingTag>
{
  //! The YX interpolation policy
  typedef LogLog YXInterpPolicy;
};

} // end local namespace

/*! \brief Policy struct for interpolating 2D tables
 * \details A Z-Y interpolation policy and a Z-X interpolation policy must
 * be specified (the Z variable must be processed in the same way in both).
 * This class should never be used directly! It is the base implementation of
 * the concrete policy types that are safe to use as policies 
 * (e.g. LinLinLin, LogLogLog). 
 */
template<typename ZYInterpPolicy,typename ZXInterpPolicy>
struct TwoDInterpolationPolicyImpl
{

private:

  //! Typedef for interp policy between y min and x
  typedef typename UnitBaseHelper<typename ZYInterpPolicy::IndepVarProcessingTag,typename ZXInterpPolicy::IndepVarProcessingTag>::YXInterpPolicy
  YMinXInterpPolicy;

  //! Typedef for interp policy between grid length and x
  typedef typename UnitBaseHelper<LinIndepVarProcessingTag,typename ZXInterpPolicy::IndepVarProcessingTag>::YXInterpPolicy
  LXInterpPolicy;

public:

  //! Dependent variable processing tag
  typedef typename ZYInterpPolicy::DepVarProcessingTag DepVarProcessingTag;
  
  //! Second independent variable processing tag
  typedef typename ZYInterpPolicy::IndepVarProcessingTag 
  SecondIndepVarProcessingTag;

  //! First independent variable processing tag
  typedef typename ZXInterpPolicy::IndepVarProcessingTag 
  FirstIndepVarProcessingTag;

  //! Process the dependent variable (z - ZYX)
  template<typename T>
  static T processDepVar( const T dep_var );

  //! Recover the processed dependent variable (z - ZYX)
  template<typename T>
  static T recoverProcessedDepVar( const T processed_dep_var );

  //! Process the second independent variable (y - ZYX)
  template<typename T>
  static T processSecondIndepVar( const T second_indep_var );

  //! Recover the processed second independent variable (y - ZYX)
  template<typename T>
  static T recoverProcessedSecondIndepVar( const T processed_second_indep_var);

  //! Process the first independent variable (x - ZYX)
  template<typename T>
  static T processFirstIndepVar( const T first_indep_var );

  //! Recover the first independent variable (x - ZYX)
  template<typename T>
  static T recoverProcessedFirstIndepVar( const T processed_first_indep_var );
  
  //! Conduct the interpolation between two grids
  template<TupleMember YIndepMember,
	   TupleMember DepMember,
	   typename YIterator,
	   typename ZIterator,
	   typename T >
  static T interpolate( const T indep_var_x_0,
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
			ZIterator end_dep_grid_1 );

  //! Conduct the interpolation between two grids
  template<TupleMember YIndepMember,
	   TupleMember DepMember,
	   typename Iterator,
	   typename T >
  static T interpolate( const T indep_var_x_0,
			const T indep_var_x_1,
			const T indep_var_x,
			const T indep_var_y,
			Iterator start_grid_0,
			Iterator end_grid_0,
			Iterator start_grid_1,
			Iterator end_grid_1 );
  
  //! Conduct the interpolation between two grids (no tuples)
  template<typename YIterator, typename ZIterator, typename T>
  static T interpolate( const T indep_var_x_0,
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
			ZIterator end_dep_var_1 );

  //! Conduct unit base interpolation between two grids
  template<TupleMember YIndepMember,
	   TupleMember DepMember,
	   typename YIterator,
	   typename ZIterator,
	   typename T >
  static T interpolateUnitBase( const T indep_var_x_0,
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
				ZIterator end_dep_grid_1 );

  //! Conduct the interpolation between two grids
  template<TupleMember YIndepMember,
	   TupleMember DepMember,
	   typename Iterator,
	   typename T>
  static T interpolateUnitBase( const T indep_var_x_0,
				const T indep_var_x_1,
				const T indep_var_x,
				const T indep_var_y,
				Iterator start_grid_0,
				Iterator end_grid_0,
				Iterator start_grid_1,
				Iterator end_grid_1 );

  //! Conduct unit base interpolation between two grids (no tuples)
  template<typename YIterator, typename ZIterator, typename T>
  static T interpolateUnitBase( const T indep_var_x_0,
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
				ZIterator end_dep_var_1 );
  
  //! Calculate the length of a grid
  template<TupleMember YIndepMember,
	   typename YIterator>
  static typename TupleMemberTraits<typename std::iterator_traits<YIterator>::value_type,YIndepMember>::tupleMemberType calculateGridLength( 
						  YIterator start_indep_y_grid,
						  YIterator end_indep_y_grid );

  //! Calculate the length of an intermediate grid
  template<typename T>
  static T calculateIntermediateGridLength( const T indep_var_x_0,
					    const T indep_var_x_1,
					    const T indep_var_x,
					    const T grid_0_length,
					    const T grid_1_length );

  //! Calculate the min value of an intermediate grid
  template<typename T>
  static T calculateIntermediateGridLimit( const T indep_var_x_0,
					   const T indep_var_x_1,
					   const T indep_var_x,
					   const T grid_0_y_limit,
					   const T grid_1_y_limit );

  //! Calculate the unit base independent variable (eta)
  template<typename T>
  static T calculateUnitBaseIndepVar( const T indep_var_y,
				      const T intermediate_indep_var_y_min,
				      const T intermediate_grid_length );

  //! Calculate the independent y variable on a grid given eta
  template<typename T>
  static T calculateGridIndepVar( const T eta,
				  const T grid_indep_var_min,
				  const T grid_length );
  
  //! Conduct the interpolation between two processed grids
  template<TupleMember YIndepMember,
	   TupleMember DepMember,
	   typename T, 
	   typename YIterator,
	   typename ZIterator>
  static T interpolateProcessed( const T processed_indep_var_x_0,
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
				 ZIterator end_processed_dep_grid_1 );

  //! Conduct the interpolation between two processed grids
  template<TupleMember YIndepMember,
	   TupleMember DepMember,
	   typename T, 
	   typename Iterator>
  static T interpolateProcessed( const T processed_indep_var_x_0,
				 const T processed_indep_var_x_1,
				 const T processed_indep_var_x,
				 const T processed_indep_var_y,
				 Iterator start_processed_grid_0,
				 Iterator end_processed_grid_0,
				 Iterator start_processed_grid_1,
				 Iterator end_processed_grid_1 );
  
  //! Conduct the interpolation between two processed grids (no tuples)
  template<typename T, typename YIterator, typename ZIterator>
  static T interpolateProcessed( const T processed_indep_var_x_0,
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
				 ZIterator end_processed_dep_grid_1 );

  //! Conduct unit base interpolation between two processed grids
  template<TupleMember YIndepMember,
	   TupleMember DepMember,
	   typename T, 
	   typename YIterator,
	   typename ZIterator>
  static T interpolateProcessedUnitBase( 
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
				      ZIterator end_processed_dep_grid_1 );

  //! Conduct unit base interpolation between two processed grids
  template<TupleMember YIndepMember,
	   TupleMember DepMember,
	   typename T, 
	   typename Iterator>
  static T interpolateProcessedUnitBase( 
				      const T processed_indep_var_x_0,
				      const T processed_indep_var_x_1,
				      const T processed_indep_var_x,
				      const T processed_indep_var_y,
				      Iterator start_processed_grid_0,
				      Iterator end_processed_grid_0,
				      Iterator start_processed_grid_1,
				      Iterator end_processed_grid_1 );
				      

  //! Conduct unit base interpolation between two processed grids (no tuples)
  template<typename T, typename YIterator, typename ZIterator>
  static T interpolateProcessedUnitBase( 
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
				      ZIterator end_processed_dep_grid_1 );

  //! Calculate the length of a grid
  template<TupleMember YIndepMember,
	   typename YIterator>
  static typename TupleMemberTraits<typename std::iterator_traits<YIterator>::value_type,YIndepMember>::tupleMemberType calculateGridLengthProcessed( 
					YIterator start_processed_indep_y_grid,
					YIterator end_processed_indep_y_grid );

  //! Calculate the length of an intermediate grid
  template<typename T>
  static T calculateIntermediateGridLengthProcessed( 
					    const T processed_indep_var_x_0,
					    const T processed_indep_var_x_1,
					    const T processed_indep_var_x,
					    const T grid_0_length,
					    const T grid_1_length );

  //! Calculate the min value of an intermediate grid
  template<typename T>
  static T calculateIntermediateProcessedGridLimit( 
					    const T processed_indep_var_x_0,
					    const T processed_indep_var_x_1,
					    const T processed_indep_var_x,
					    const T processed_grid_0_y_limit,
					    const T processed_grid_1_y_limit );

  //! Calculate the unit base independent variable (eta)
  template<typename T>
  static T calculateUnitBaseIndepVarProcessed( 
			        const T processed_indep_var_y,
				const T processed_intermediate_indep_var_y_min,
				const T intermediate_grid_length );

  //! Calculate the independent y variable on a grid given eta
  template<typename T>
  static T calculateProcessedGridIndepVar( 
				  const T eta,
				  const T processed_grid_indep_var_min,
				  const T grid_length );

private:

  // Tolerance for certain tests
  static const double s_tol;

  // Interpolate on the specified y grid
  template<TupleMember YIndepMember,
	   TupleMember DepMember,
	   typename YIterator,
	   typename ZIterator,
	   typename T>
  static T interpolateAndProcessOnYGrid( const T indep_var_y,
					 YIterator start_indep_y_grid,
					 YIterator end_indep_y_grid,
					 ZIterator start_dep_grid,
					 ZIterator end_dep_grid );

  // Interpolate on the specified processed y grid
  template<TupleMember YIndepMember,
	   TupleMember DepMember,
	   typename YIterator,
	   typename ZIterator,
	   typename T>
  static T interpolateAndProcessOnProcessedYGrid( 
					const T processed_indep_var_y,
					YIterator start_processed_indep_y_grid,
					YIterator end_processed_indep_y_grid,
					ZIterator start_processed_dep_grid,
					ZIterator end_processed_dep_grid );
};

/*! \brief Policy struct for interpolating 2D tables (Z-Y interpolation policy
 * is Lin-Lin and Z-X policy interpolation policy is Lin-Lin).
 */
struct LinLinLin : public TwoDInterpolationPolicyImpl<LinLin,LinLin>
{ 
  typedef LinLin ZYInterpPolicy;
  typedef LinLin ZXInterpPolicy;
};

/*! \brief Policy struct for interpolating 2D tables (Z-Y interpolation policy
 * is Lin-Log and Z-X policy interpolation policy is Lin-Lin).
 */
struct LinLogLin : public TwoDInterpolationPolicyImpl<LinLog,LinLin>
{ 
  typedef LinLog ZYInterpPolicy;
  typedef LinLin ZXInterpPolicy;
};

/*! \brief Policy struct for interpolating 2D tables (Z-Y interpolation policy
 * is Lin-Lin and Z-X policy interpolation policy is Lin-Log).
 */
struct LinLinLog : public TwoDInterpolationPolicyImpl<LinLin,LinLog>
{ 
  typedef LinLin ZYInterpPolicy;
  typedef LinLog ZXInterpPolicy;
};

/*! \brief Policy struct for interpolating 2D tables (Z-Y interpolation policy
 * is Lin-Log and Z-X policy interpolation policy is Lin-Log).
 */
struct LinLogLog : public TwoDInterpolationPolicyImpl<LinLog,LinLog>
{ 
  typedef LinLog ZYInterpPolicy;
  typedef LinLog ZXInterpPolicy;
};

/*! \brief Policy struct for interpolating 2D tables (Z-Y interpolation policy
 * is Log-Lin and Z-X policy interpolation policy is Log-Lin).
 */
struct LogLinLin : public TwoDInterpolationPolicyImpl<LogLin,LogLin>
{ 
  typedef LogLin ZYInterpPolicy;
  typedef LogLin ZXInterpPolicy;
};

/*! \brief Policy struct for interpolating 2D tables (Z-Y interpolation policy
 * is Log-Log and Z-X policy interpolation policy is Log-Lin).
 */
struct LogLogLin : public TwoDInterpolationPolicyImpl<LogLog,LogLin>
{ 
  typedef LogLog ZYInterpPolicy;
  typedef LogLin ZXInterpPolicy;
};

/*! \brief Policy struct for interpolating 2D tables (Z-Y interpolation policy
 * is Log-Lin and Z-X policy interpolation policy is Log-Log).
 */
struct LogLinLog : public TwoDInterpolationPolicyImpl<LogLin,LogLog>
{ 
  typedef LogLin ZYInterpPolicy;
  typedef LogLog ZXInterpPolicy;
};

/*! \brief Policy struct for interpolating 2D tables (Z-Y interpolation policy
 * is Log-Log and Z-X policy interpolation policy is Log-Log).
 */
struct LogLogLog : public TwoDInterpolationPolicyImpl<LogLog,LogLog>
{
  typedef LogLog ZYInterpPolicy;
  typedef LogLog ZXInterpPolicy;
};

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_TwoDInterpolationPolicy_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_TWO_D_INTERPOLATION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_TwoDInterpolationPolicy.hpp
//---------------------------------------------------------------------------//
