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
  //! Interpolate between four points (x0,y00), (x0,y01), (x1,y10), (x0,y11)
  template<typename T>
  static T interpolate( const T indep_var_x_0,
			const T indep_var_x_1,
			const T indep_var_x,
			const T indep_var_y_0_0,
			const T indep_var_y_0_1,
			const T indep_var_y_0_range,
			const T indep_var_y_1_0,
			const T indep_var_y_1_1,
			const T indep_var_y_1_range,
			const T indep_var_y,
			const T dep_var_0_0,
			const T dep_var_0_1,
			const T dep_var_1_0,
			const T dep_var_1_1 );

  //! Interpolate between four processed points
  template<typename T>
  static T interpolate( const T processed_indep_var_x_0,
			const T processed_indep_var_x_1,
			const T processed_indep_var_x,
			const T processed_indep_var_y_0_0,
			const T indep_var_y_0_range,
			const T processed_dep_var_0_0,
			const T processed_slope_0,
			const T processed_indep_var_y_1_0,
			const T indep_var_y_1_range,
			const T processed_dep_var_1_0,
			const T processed_slope_1,
			const T processed_indep_var_y );
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
