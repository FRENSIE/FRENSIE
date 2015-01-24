//---------------------------------------------------------------------------//
//!
//! \file   Utility_UnitBaseInterpolationPolicy.hpp
//! \author Alex Robinson
//! \brief  Unit base interpolation policy struct declarations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_UNIT_BASE_INTERPOLATION_POLICY_HPP
#define UTILITY_UNIT_BASE_INTERPOLATION_POLICY_HPP

namespace Utility{

/*! \brief Policy struct for interpolating 2D tables using the unit base
 * method.
 * \details A Z-Y interpolation policy, a Z-X interpolation policy and a
 * R-X (Range-X) interpolation policy can be specified
 */
template<typename ZYInterpPolicy, 
	 typename ZXInterpPolicy,
	 typename RXInterpPolicy>
struct UnitBaseImpl
{
  //! Calculate the intermediate range of the Y independent variable
  template<typename T>
  static T calculateIntermediateRange( const T indep_var_x_0,
				       const T indep_var_x_1,
				       const T indep_var_x,
				       const T indep_var_y_0_range,
				       const T indep_var_y_1_range );

  //! Calculate the intermediate min Y independent variable
  template<typename T>
  static T calculateIntermediateMinYIndepValue( const T indep_var_x_0,
						const T indep_var_x_1,
						const T indep_var_x,
						const T min_indep_var_y_0,
						const T min_indep_var_y_1 );

  //! Calculate the unit base y independent variable
  template<typename T>
  static T calculateUnitBaseIndepYVariable( const T indep_var_y,
					    const T min_indep_var_y,
					    const T indep_var_y_range );
  
  //! Calculate the independent y variable
  template<typename T>
  static T calculateIndepYVariable( const T unit_base_indep_var_y,
				    const T min_indep_var_y,
				    const T indep_var_y_range );
  
  //! Conduct unit base interpolation between two grids
  template<TupleMember YIndepMember,
	   TupleMember DepMember,
	   typename T, 
	   typename Iterator>
  static T interpolateGrids( const T indep_var_x_0,
			     const T indep_var_x_1,
			     const T indep_var_x,
			     const T indep_var_y,
			     Iterator start_indep_var_y_0,
			     Iterator end_indep_var_y_0,
			     Iterator start_dep_var_0,
			     Iterator end_dep_var_0,
			     Iterator start_indep_var_y_1,
			     Iterator end_indep_var_y_1,
			     Iterator start_dep_var_1,
			     Iterator end_dep_var_1 );

  //! Conduct unit base interpolation between two grids (no tuples)
  template<typename T, typename Iterator>
  static T interpolateGrids( const T indep_var_x_0,
			     const T indep_var_x_1,
			     const T indep_var_x,
			     const T indep_var_y,
			     Iterator start_indep_var_y_0,
			     Iterator end_indep_var_y_0,
			     Iterator start_dep_var_0,
			     Iterator end_dep_var_0,
			     Iterator start_indep_var_y_1,
			     Iterator end_indep_var_y_1,
			     Iterator start_dep_var_1,
			     Iterator end_dep_var_1 );

  //! Conduct unit base interpolation between two processed grids
  template<TupleMember YIndepMember,
	   TupleMember DepMember,
	   typename T, 
	   typename Iterator>
  static T interpolateProcessedGrids( const T processed_indep_var_x_0,
				      const T processed_indep_var_x_1,
				      const T processed_indep_var_x,
				      const T processed_indep_var_y,
				      Iterator start_indep_var_y_0,
				      Iterator end_indep_var_y_0,
				      Iterator start_dep_var_0,
				      Iterator end_dep_var_0,
				      Iterator start_indep_var_y_1,
				      Iterator end_indep_var_y_1,
				      Iterator start_dep_var_1,
				      Iterator end_dep_var_1 );

  //! Conduct unit base interpolation between two processed grids (no tuples)
  template<typename T, typename Iterator>
  static T interpolateProcessedGrids( const T processed_indep_var_x_0,
				      const T processed_indep_var_x_1,
				      const T processed_indep_var_x,
				      const T processed_indep_var_y,
				      Iterator start_indep_var_y_0,
				      Iterator end_indep_var_y_0,
				      Iterator start_dep_var_0,
				      Iterator end_dep_var_0,
				      Iterator start_indep_var_y_1,
				      Iterator end_indep_var_y_1,
				      Iterator start_dep_var_1,
				      Iterator end_dep_var_1 );

  //! Conduct the unit base interpolation between two distributions
  double interpolateDistributions( const T indep_var_x_0,
				   const T indep_var_x_1,
				   const T indep_var_x,
				   const T indep_var_y,
				   const OneDDistribution& first_distribution,
				   const OneDDistribution& second_distribution );
};

/*! \brief Policy struct for interpolating 2D tables using the unit 
 * base method (Z-Y interpolation policy is lin-lin and Z-X interpolation 
 * policy is lin-lin).
 */
struct UnitBaseLinLinLin : public UnitBaseImpl<LinLin,LinLin,LinLin>
{ /* ... */ };

/*! \brief Policy struct for interpolating 2D tables using the unit 
 * base method (Z-Y interpolation policy is log-log and Z-X interpolation 
 * policy is log-log).
 */
struct UnitBaseLogLogLog : public UnitBaseImpl<LogLog,LogLog,LogLog>
{ /* ... */ };

/*! \brief Policy struct for interpolating 2D tables using the unit 
 * base method (Z-Y interpolation policy is lin-log and Z-X interpolation 
 * policy is lin-log).
 */
struct UnitBaseLinLogLog : public UnitBaseImpl<LinLog,LinLog,LogLog>
{ /* ... */ };

/*! \brief Policy struct for interpolating 2D tables using the unit 
 * base method (Z-Y interpolation policy is log-lin and Z-X interpolation 
 * policy is log-lin).
 */
struct UnitBaseLogLinLin : public UnitBaseImpl<LogLin,LogLin,LinLin>
{ /* ... */ };

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_UnitBaseInterpolationPolicy_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_UNIT_BASE_INTERPOLATION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_UnitBaseInterpolationPolicy.hpp
//---------------------------------------------------------------------------//
