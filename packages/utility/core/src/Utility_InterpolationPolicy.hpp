//---------------------------------------------------------------------------//
//!
//! \file   Utility_InterpolationPolicy.hpp
//! \author Alex Robinson
//! \brief  Interpolation policy struct declarations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INTERPOLATION_POLICY_HPP
#define UTILITY_INTERPOLATION_POLICY_HPP

// FRENSIE Includes
#include "Utility_QuantityTraits.hpp"

namespace Utility{

//! The log independent variable processing tag
struct LogIndepVarProcessingTag{};

//! The lin independent variable processing tag
struct LinIndepVarProcessingTag{};

//! The log dependent variable processing tag
struct LogDepVarProcessingTag{};

//! The lin dependent variable processing tag
struct LinDepVarProcessingTag{};

/*! \brief Policy struct for interpolating data tables that require log-log 
 * interpolation between evaluated points.
 * \ingroup policies
 */
struct LogLog
{
  //! Independent variable processing tag
  typedef LogIndepVarProcessingTag IndepVarProcessingTag;

  //! Dependent variable processing tag
  typedef LogDepVarProcessingTag DepVarProcessingTag;
  
  //! Interpolate between two points
  template<typename IndepType, typename DepType>
  static DepType interpolate( const IndepType indep_var_0,
			      const IndepType indep_var_1,
			      const IndepType indep_var,
			      const DepType dep_var_0,
			      const DepType dep_var_1 );
  
  //! Interpolate between two processed points
  template<typename T>
  static T interpolate( const T processed_indep_var_0,
			const T processed_indep_var,
			const T processed_dep_var_0,
			const T processed_slope );

  //! Interpolate between two points and return the processed value
  template<typename IndepType, typename DepType>
  static typename QuantityTraits<DepType>::RawType 
  interpolateAndProcess( const IndepType indep_var_0,
			 const IndepType indep_var_1,
			 const IndepType indep_var,
			 const DepType dep_var_0,
			 const DepType dep_var_1 );

  //! Interpolate between two processed points and return the processed value
  template<typename T>
  static T interpolateAndProcess( const T processed_indep_var_0,
				  const T processed_indep_var,
				  const T processed_dep_var_0,
				  const T processed_slope );

  //! Process the independent value
  template<typename T>
  static typename QuantityTraits<T>::RawType  
  processIndepVar( const T indep_var );

  //! Process the dependent value
  template<typename T>
  static typename QuantityTraits<T>::RawType  
  processDepVar( const T dep_var );

  //! Recover the processed independent value
  template<typename T>
  static T recoverProcessedIndepVar( const T processed_indep_var );
  
  //! Recover the processed dependent value
  template<typename T>
  static T recoverProcessedDepVar( const T processed_dep_var );

  //! Test if the independent value is in a valid range (doesn't check nan/inf)
  template<typename T>
  static bool isIndepVarInValidRange( const T indep_var );

  //! Test if the dependent value is in a valid range (doesn't check nan/inf)
  template<typename T>
  static bool isDepVarInValidRange( const T dep_var );

  //! The name of the policy
  static const std::string name();
};

/*! \brief Policy struct for interpolating data tables that require log-lin 
 * interpolation between evaluated points.
 * \ingroup policies
 */
struct LogLin
{
  //! Independent variable processing tag
  typedef LinIndepVarProcessingTag IndepVarProcessingTag;

  //! Dependent variable processing tag
  typedef LogDepVarProcessingTag DepVarProcessingTag;
  
  //! Interpolate between two points
  template<typename IndepType, typename DepType>
  static DepType interpolate( const IndepType indep_var_0,
			      const IndepType indep_var_1,
			      const IndepType indep_var,
			      const DepType dep_var_0,
			      const DepType dep_var_1 );
  
  //! Interpolate between two processed points
  template<typename T>
  static T interpolate( const T processed_indep_var_0,
			const T processed_indep_var,
			const T processed_dep_var_0,
			const T processed_slope );

  //! Interpolate between two points and return the processed value
  template<typename IndepType, typename DepType>
  static typename QuantityTraits<DepType>::RawType 
  interpolateAndProcess( const IndepType indep_var_0,
			 const IndepType indep_var_1,
			 const IndepType indep_var,
			 const DepType dep_var_0,
			 const DepType dep_var_1 );

  //! Interpolate between two processed points and return the processed value
  template<typename T>
  static T interpolateAndProcess( const T processed_indep_var_0,
				  const T processed_indep_var,
				  const T processed_dep_var_0,
				  const T processed_slope );

  //! Process the independent value
  template<typename T>
  static typename QuantityTraits<T>::RawType  
  processIndepVar( const T indep_var );

  //! Process the dependent value
  template<typename T>
  static typename QuantityTraits<T>::RawType  
  processDepVar( const T dep_var );
  
  //! Recover the processed independent value
  template<typename T>
  static T recoverProcessedIndepVar( const T processed_indep_var );
  
  //! Recover the processed dependent value
  template<typename T>
  static T recoverProcessedDepVar( const T processed_dep_var );

  //! Test if the independent value is in a valid range (doesn't check nan/inf)
  template<typename T>
  static bool isIndepVarInValidRange( const T indep_var );

  //! Test if the dependent value is in a valid range (doesn't check nan/inf)
  template<typename T>
  static bool isDepVarInValidRange( const T dep_var );

  //! The name of the policy
  static const std::string name();
};

/*! \brief Policy struct for interpolating data tables that require lin-log
 * interpolation between evaluated points.
 * \ingroup policies
 */
struct LinLog
{
  //! Independent variable processing tag
  typedef LogIndepVarProcessingTag IndepVarProcessingTag;

  //! Dependent variable processing tag
  typedef LinDepVarProcessingTag DepVarProcessingTag;
  
  //! Interpolate between two points
  template<typename IndepType, typename DepType>
  static DepType interpolate( const IndepType indep_var_0,
			      const IndepType indep_var_1,
			      const IndepType indep_var,
			      const DepType dep_var_0,
			      const DepType dep_var_1 );
  
  //! Interpolate between two processed points
  template<typename T>
  static T interpolate( const T processed_indep_var_0,
			const T processed_indep_var,
			const T processed_dep_var_0,
			const T processed_slope );

  //! Interpolate between two points and return the processed value
  template<typename IndepType, typename DepType>
  static typename QuantityTraits<DepType>::RawType 
  interpolateAndProcess( const IndepType indep_var_0,
			 const IndepType indep_var_1,
			 const IndepType indep_var,
			 const DepType dep_var_0,
			 const DepType dep_var_1 );

  //! Interpolate between two processed points and return the processed value
  template<typename T>
  static T interpolateAndProcess( const T processed_indep_var_0,
				  const T processed_indep_var,
				  const T processed_dep_var_0,
				  const T processed_slope );

  //! Process the independent value
  template<typename T>
  static typename QuantityTraits<T>::RawType 
  processIndepVar( const T indep_var );

  //! Process the dependent value
  template<typename T>
  static typename QuantityTraits<T>::RawType 
  processDepVar( const T dep_var );

  //! Recover the processed independent value
  template<typename T>
  static T recoverProcessedIndepVar( const T processed_indep_var );
  
  //! Recover the processed dependent value
  template<typename T>
  static T recoverProcessedDepVar( const T processed_dep_var );

  //! Test if the independent value is in a valid range (doesn't check nan/inf)
  template<typename T>
  static bool isIndepVarInValidRange( const T indep_var );

  //! Test if the dependent value is in a valid range (doesn't check nan/inf)
  template<typename T>
  static bool isDepVarInValidRange( const T dep_var );

  //! The name of the policy
  static const std::string name();
};

/*! \brief Policy struct for interpolating data tables that require lin-lin
 * interpolation between evaluated points.
 * \ingroup policies
 */
struct LinLin
{
  //! Independent variable processing tag
  typedef LinIndepVarProcessingTag IndepVarProcessingTag;

  //! Dependent variable processing tag
  typedef LinDepVarProcessingTag DepVarProcessingTag;
  
  //! Interpolate between two points
  template<typename IndepType, typename DepType>
  static DepType interpolate( const IndepType indep_var_0,
			      const IndepType indep_var_1,
			      const IndepType indep_var,
			      const DepType dep_var_0,
			      const DepType dep_var_1 );
  
  //! Interpolate between two processed points
  template<typename T>
  static T interpolate( const T processed_indep_var_0,
			const T processed_indep_var,
			const T processed_dep_var_0,
			const T processed_slope );

  //! Interpolate between two points and return the processed value
  template<typename IndepType, typename DepType>
  static typename QuantityTraits<DepType>::RawType
  interpolateAndProcess( const IndepType indep_var_0,
			 const IndepType indep_var_1,
			 const IndepType indep_var,
			 const DepType dep_var_0,
			 const DepType dep_var_1 );

  //! Interpolate between two processed points and return the processed value
  template<typename T>
  static T interpolateAndProcess( const T processed_indep_var_0,
				  const T processed_indep_var,
				  const T processed_dep_var_0,
				  const T processed_slope );
  
  //! Test if the independent value is in a valid range (doesn't check nan/inf)
  template<typename T>
  static bool isIndepVarInValidRange( const T indep_var );

  //! Test if the dependent value is in a valid range (doesn't check nan/inf)
  template<typename T>
  static bool isDepVarInValidRange( const T dep_var );

  //! Process the independent value
  template<typename T>
  static typename QuantityTraits<T>::RawType 
  processIndepVar( const T indep_var );

  //! Process the dependent value
  template<typename T>
  static typename QuantityTraits<T>::RawType
  processDepVar( const T dep_var );

  //! Recover the processed independent value
  template<typename T>
  static T recoverProcessedIndepVar( const T processed_indep_var );
  
  //! Recover the processed dependent value
  template<typename T>
  static T recoverProcessedDepVar( const T processed_dep_var );

  //! The name of the policy
  static const std::string name();
};

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template includes
//---------------------------------------------------------------------------//

#include "Utility_InterpolationPolicy_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_INTERPOLATION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_InterpolationPolicy.hpp
//---------------------------------------------------------------------------//
