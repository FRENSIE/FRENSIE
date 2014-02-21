//---------------------------------------------------------------------------//
//!
//! \file   InterpolationPolicy.hpp
//! \author Alex Robinson
//! \brief  Interpolation policy struct declarations
//!
//---------------------------------------------------------------------------//

#ifndef INTERPOLATION_POLICY_HPP
#define INTERPOLATION_POLICY_HPP

namespace FACEMC{

/*! \brief Policy struct for interpolating data tables that require log-log 
 * interpolation between evaluated points.
 * \ingroup policies
 */
struct LogLog
{
  //! Interpolate between two points
  template<typename T>
  static T interpolate( const T indep_var_0,
			const T indep_var_1,
			const T indep_var,
			const T dep_var_0,
			const T dep_var_1 );
  
  //! Interpolate between two processed points
  template<typename T>
  static T interpolate( const T processed_indep_var_0,
			const T processed_indep_var,
			const T processed_dep_var,
			const T processed_slope );
};

/*! \brief Policy struct for interpolating data tables that require log-lin 
 * interpolation between evaluated points.
 * \ingroup policies
 */
struct LogLin
{
  //! Interpolate between two points
  template<typename T>
  static T interpolate( const T indep_var_0,
			const T indep_var_1,
			const T indep_var,
			const T dep_var_0,
			const T dep_var_1 );
  
  //! Interpolate between two processed points
  template<typename T>
  static T interpolate( const T processed_indep_var_0,
			const T processed_indep_var,
			const T processed_dep_var,
			const T processed_slope );
};

/*! \brief Policy struct for interpolating data tables that require lin-log
 * interpolation between evaluated points.
 * \ingroup policies
 */
struct LinLog
{
  //! Interpolate between two points
  template<typename T>
  static T interpolate( const T indep_var_0,
			const T indep_var_1,
			const T indep_var,
			const T dep_var_0,
			const T dep_var_1 );
  
  //! Interpolate between two processed points
  template<typename T>
  static T interpolate( const T processed_indep_var_0,
			const T processed_indep_var,
			const T processed_dep_var,
			const T processed_slope );
};

/*! \brief Policy struct for interpolating data tables that require lin-lin
 * interpolation between evaluated points.
 * \ingroup policies
 */
struct LinLin
{
  //! Interpolate between two points
  template<typename T>
  static T interpolate( const T indep_var_0,
			const T indep_var_1,
			const T indep_var,
			const T dep_var_0,
			const T dep_var_1 );
  
  //! Interpolate between two processed points
  template<typename T>
  static T interpolate( const T processed_indep_var_0,
			const T processed_indep_var,
			const T processed_dep_var,
			const T processed_slope );
};

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "InterpolationPolicy_def.hpp"

//---------------------------------------------------------------------------//

#endif // end INTERPOLATION_POLICY_HPP

//---------------------------------------------------------------------------//
// end InterpolationPolicy.hpp
//---------------------------------------------------------------------------//
