//---------------------------------------------------------------------------//
//!
//! \file   Utility_CosineInterpolationPolicy.hpp
//! \author Luke Kersting
//! \brief  Cosine interpolation policy struct declarations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_COSINE_INTERPOLATION_POLICY_HPP
#define UTILITY_COSINE_INTERPOLATION_POLICY_HPP

// FRENSIE Includes
#include "Utility_InterpolationType.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_QuantityTraits.hpp"

namespace Utility{

//! The log cosine independent variable processing tag
struct LogCosIndepVarProcessingTag{};

//! The log cosine dependent variable processing tag
struct LogCosDepVarProcessingTag{};

//! The nudged log cosine independent variable processing tag
struct NudgedLogCosIndepVarProcessingTag{};

//! The nudged log cosine dependent variable processing tag
struct NudgedLogCosDepVarProcessingTag{};

//! Helper struct for turning the cosine interp nudge factor on/off
template<bool use_nudge>
struct CosNudgeHelper
{
  //! Convert from cosine variable
  /*! \details This function converts from cosine (mu) to the delta cosine
  * (1 - mu) + nudge.
  */
  template<typename T>
  static inline T convertFromCosineVar( const T cosine_var )
  {
    return QuantityTraits<T>::one() - cosine_var;
  }

  //! Convert to cosine variable
  /*! \details This function converts from the delta cosine (1 - mu) + nudge
  *  back to cosine (mu).
  */
  template<typename T>
  static inline T convertToCosineVar( const T delta_cosine )
  {
    return QuantityTraits<T>::one() - delta_cosine;
  }
};

template<>
struct CosNudgeHelper<true>
{
  //! Convert from cosine variable
  /*! \details This function converts from cosine (mu) to the delta cosine
  * (1 - mu) + nudge.
  */
  template<typename T>
  static inline T convertFromCosineVar( const T cosine_var )
  {
    return (QuantityTraits<T>::one() - cosine_var) + QuantityTraits<T>::one()*1e-10;
  }

  // Convert to cosine variable
  /*! \details This function converts from the delta cosine (1 - mu) + nudge
  *  back to cosine (mu).
  */
  template<typename T>
  static inline T convertToCosineVar( const T delta_cosine )
  {
    return (QuantityTraits<T>::one()*1e-10 - delta_cosine) + QuantityTraits<T>::one();
  }

};

template<>
struct CosNudgeHelper<false>
{
  //! Convert from cosine variable
  /*! \details This function converts from cosine (mu) to the delta cosine
  * (1 - mu).
  */
  template<typename T>
  static inline T convertFromCosineVar( const T cosine_var )
  {
    return QuantityTraits<T>::one() - cosine_var;
  }

  // Convert to cosine variable
  /*! \details This function converts from the delta cosine (1 - mu)
  *  back to cosine (mu).
  */
  template<typename T>
  static inline T convertToCosineVar( const T delta_cosine )
  {
    return QuantityTraits<T>::one() - delta_cosine;
  }
};

/*! \brief Helper policy struct for interpolating data tables that require
 * logcos-log interpolation between evaluated points.
 * \ingroup policies
 */
template<bool use_nudge = false>
struct LogCosLogHelper : public InterpolationHelper<LogCosLogHelper<use_nudge> >
{
  //! Force base class template methods to be visible
  using InterpolationHelper<LogCosLogHelper<use_nudge> >::interpolate;
  using InterpolationHelper<LogCosLogHelper<use_nudge> >::interpolateAndProcess;
  using InterpolationHelper<LogCosLogHelper<use_nudge> >::calculateUnitBaseIndepVar;
  using InterpolationHelper<LogCosLogHelper<use_nudge> >::calculateUnitBaseIndepVarProcessed;
  using InterpolationHelper<LogCosLogHelper<use_nudge> >::calculateIndepVar;
  using InterpolationHelper<LogCosLogHelper<use_nudge> >::calculateProcessedIndepVar;

  //! Interpolate between two points
  template<typename IndepType, typename DepCosineType>
  static DepCosineType interpolate( const IndepType indep_var_0,
                              const IndepType indep_var_1,
                              const IndepType indep_var,
                              const DepCosineType dep_var_0,
                              const DepCosineType dep_var_1 );

  //! Interpolate between two points using the indep variable ratio (beta)
  template<typename T, typename DepCosineType>
  static DepCosineType interpolate( const T beta,
                              const DepCosineType dep_var_0,
                              const DepCosineType dep_var_1 );

  //! Interpolate between two points and return the processed value
  template<typename IndepType, typename DepCosineType>
  static typename QuantityTraits<DepCosineType>::RawType
  interpolateAndProcess( const IndepType indep_var_0,
                         const IndepType indep_var_1,
                         const IndepType indep_var,
                         const DepCosineType dep_var_0,
                         const DepCosineType dep_var_1 );

  //! Process the independent value
  template<typename T>
  static typename QuantityTraits<T>::RawType
  processIndepVar( const T cosine_var );

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
};

/*! \brief Policy struct for interpolating data tables that require logcos-log
 * interpolation between evaluated points.
 * \details The dependent variable is always assumed to be an angle cosine.
 * Since the angle cosine goes below zero a direct log interpolation
 * cannot be performed on it. Instead a log interpolation will be performed
 * on the change in the angle cosine (eg: 1 - mu ) instead of the cosine
 * ( mu ). The interpolated value will always be cast into the cosine before
 * returned.
 * \ingroup policies
 */
struct LogCosLog : public LogCosLogHelper<false>
{
  //! Independent variable processing tag
  typedef LogIndepVarProcessingTag IndepVarProcessingTag;

  //! Dependent variable processing tag
  typedef LogCosDepVarProcessingTag DepVarProcessingTag;

  //! Get the interpolation type
  static InterpolationType getInterpolationType();

  //! Force base class template methods to be visible
  using LogCosLogHelper<false>::interpolate;
  using LogCosLogHelper<false>::interpolateAndProcess;
  using LogCosLogHelper<false>::calculateUnitBaseIndepVar;
  using LogCosLogHelper<false>::calculateUnitBaseIndepVarProcessed;
  using LogCosLogHelper<false>::calculateIndepVar;
  using LogCosLogHelper<false>::calculateProcessedIndepVar;
  using LogCosLogHelper<false>::processIndepVar;
  using LogCosLogHelper<false>::processDepVar;
  using LogCosLogHelper<false>::recoverProcessedIndepVar;
  using LogCosLogHelper<false>::recoverProcessedDepVar;
  using LogCosLogHelper<false>::isIndepVarInValidRange;
  using LogCosLogHelper<false>::isDepVarInValidRange;

  //! The name of the policy
  static const std::string name();
};

/*! \brief Policy struct for interpolating data tables that require
 * nudgedlogcos-log interpolation between evaluated points.
 * \details The dependent variable is always assumed to be an angle cosine.
 * Since the angle cosine goes below zero a direct log interpolation
 * cannot be performed on it. Instead a log interpolation will be performed
 * on the change in the angle cosine (eg: 1 - mu + nudge ) instead of the cosine
 * ( mu ). The interpolated value will always be cast into the cosine before
 * returned.
 * \ingroup policies
 */
struct NudgedLogCosLog : public LogCosLogHelper<true>
{
  //! Independent variable processing tag
  typedef LogIndepVarProcessingTag IndepVarProcessingTag;

  //! Dependent variable processing tag
  typedef NudgedLogCosDepVarProcessingTag DepVarProcessingTag;

  //! Get the interpolation type
  static InterpolationType getInterpolationType();

  //! Force base class template methods to be visible
  using LogCosLogHelper<true>::interpolate;
  using LogCosLogHelper<true>::interpolateAndProcess;
  using LogCosLogHelper<true>::calculateUnitBaseIndepVar;
  using LogCosLogHelper<true>::calculateUnitBaseIndepVarProcessed;
  using LogCosLogHelper<true>::calculateIndepVar;
  using LogCosLogHelper<true>::calculateProcessedIndepVar;
  using LogCosLogHelper<true>::processIndepVar;
  using LogCosLogHelper<true>::processDepVar;
  using LogCosLogHelper<true>::recoverProcessedIndepVar;
  using LogCosLogHelper<true>::recoverProcessedDepVar;
  using LogCosLogHelper<true>::isIndepVarInValidRange;
  using LogCosLogHelper<true>::isDepVarInValidRange;

  //! The name of the policy
  static const std::string name();
};

/*! \brief Helper policy struct for interpolating data tables that require
 * log-log cosine interpolation between evaluated points.
 * \ingroup policies
 */
template<bool use_nudge = false>
struct LogLogCosHelper : public InterpolationHelper<LogLogCosHelper<use_nudge> >
{
  //! Force base class template methods to be visible
  using InterpolationHelper<LogLogCosHelper<use_nudge> >::interpolate;
  using InterpolationHelper<LogLogCosHelper<use_nudge> >::interpolateAndProcess;
  using InterpolationHelper<LogLogCosHelper<use_nudge> >::calculateUnitBaseIndepVar;
  using InterpolationHelper<LogLogCosHelper<use_nudge> >::calculateUnitBaseIndepVarProcessed;
  using InterpolationHelper<LogLogCosHelper<use_nudge> >::calculateIndepVar;
  using InterpolationHelper<LogLogCosHelper<use_nudge> >::calculateProcessedIndepVar;

  //! Interpolate between two points
  template<typename IndepCosineType, typename DepType>
  static DepType interpolate( const IndepCosineType indep_var_0,
                              const IndepCosineType indep_var_1,
                              const IndepCosineType indep_var,
                              const DepType dep_var_0,
                              const DepType dep_var_1 );

  //! Interpolate between two points using the indep variable ratio (beta)
  template<typename T, typename DepType>
  static DepType interpolate( const T beta,
                              const DepType dep_var_0,
                              const DepType dep_var_1 );

  //! Interpolate between two points and return the processed value
  template<typename IndepCosineType, typename DepType>
  static typename QuantityTraits<DepType>::RawType
  interpolateAndProcess( const IndepCosineType indep_var_0,
                         const IndepCosineType indep_var_1,
                         const IndepCosineType indep_var,
                         const DepType dep_var_0,
                         const DepType dep_var_1 );

  //! Process the independent value
  template<typename T>
  static typename QuantityTraits<T>::RawType
  processIndepVar( const T cosine_var );

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
};

/*! \brief Policy struct for interpolating data tables that require log-log
 * cosine interpolation between evaluated points.
 * \details The unprocessed independent variable is always assumed to be an angle
 * cosine. Since the angle cosine goes below zero a direct log interpolation
 * cannot be performed on it. Instead a log interpolation will be performed
 * on the change in the angle cosine (eg: 1 - mu ) instead of the cosine
 * ( mu ). The interpolated value will always be cast into the cosine before
 * returned. When a processed cosine grid is used, it is assumed that the
 * independent and dependent grids are inverted to maintain an ascending order.
 * \ingroup policies
 */
struct LogLogCos : public LogLogCosHelper<false>
{
  //! Independent variable processing tag
  typedef LogCosIndepVarProcessingTag IndepVarProcessingTag;

  //! Dependent variable processing tag
  typedef LogDepVarProcessingTag DepVarProcessingTag;

  //! Get the interpolation type
  static InterpolationType getInterpolationType();

  //! Force base class template methods to be visible
  using LogLogCosHelper<false>::interpolate;
  using LogLogCosHelper<false>::interpolateAndProcess;
  using LogLogCosHelper<false>::calculateUnitBaseIndepVar;
  using LogLogCosHelper<false>::calculateUnitBaseIndepVarProcessed;
  using LogLogCosHelper<false>::calculateIndepVar;
  using LogLogCosHelper<false>::calculateProcessedIndepVar;
  using LogLogCosHelper<false>::processIndepVar;
  using LogLogCosHelper<false>::processDepVar;
  using LogLogCosHelper<false>::recoverProcessedIndepVar;
  using LogLogCosHelper<false>::recoverProcessedDepVar;
  using LogLogCosHelper<false>::isIndepVarInValidRange;
  using LogLogCosHelper<false>::isDepVarInValidRange;

  //! The name of the policy
  static const std::string name();
};

/*! \brief Policy struct for interpolating data tables that require log-nudged
 * log cosine interpolation between evaluated points.
 * \details The unprocessed independent variable is always assumed to be an angle
 * cosine. Since the angle cosine goes below zero a direct log interpolation
 * cannot be performed on it. Instead a log interpolation will be performed
 * on the change in the angle cosine (eg: 1 - mu + nudge ) instead of the cosine
 * ( mu ). The interpolated value will always be cast into the cosine before
 * returned. When a processed cosine grid is used, it is assumed that the
 * independent and dependent grids are inverted to maintain an ascending order.
 * \ingroup policies
 */
struct LogNudgedLogCos : public LogLogCosHelper<true>
{
  //! Independent variable processing tag
  typedef NudgedLogCosIndepVarProcessingTag IndepVarProcessingTag;

  //! Dependent variable processing tag
  typedef LogDepVarProcessingTag DepVarProcessingTag;

  //! Get the interpolation type
  static InterpolationType getInterpolationType();

  //! Force base class template methods to be visible
  using LogLogCosHelper<true>::interpolate;
  using LogLogCosHelper<true>::interpolateAndProcess;
  using LogLogCosHelper<true>::calculateUnitBaseIndepVar;
  using LogLogCosHelper<true>::calculateUnitBaseIndepVarProcessed;
  using LogLogCosHelper<true>::calculateIndepVar;
  using LogLogCosHelper<true>::calculateProcessedIndepVar;
  using LogLogCosHelper<true>::processIndepVar;
  using LogLogCosHelper<true>::processDepVar;
  using LogLogCosHelper<true>::recoverProcessedIndepVar;
  using LogLogCosHelper<true>::recoverProcessedDepVar;
  using LogLogCosHelper<true>::isIndepVarInValidRange;
  using LogLogCosHelper<true>::isDepVarInValidRange;

  //! The name of the policy
  static const std::string name();
};

/*! \brief Helper policy struct for interpolating data tables that require
 * logcos-lin interpolation between evaluated points.
 * \ingroup policies
 */
template<bool use_nudge = false>
struct LogCosLinHelper : public InterpolationHelper<LogCosLinHelper<use_nudge> >
{
  //! Force base class template methods to be visible
  using InterpolationHelper<LogCosLinHelper<use_nudge> >::interpolate;
  using InterpolationHelper<LogCosLinHelper<use_nudge> >::interpolateAndProcess;
  using InterpolationHelper<LogCosLinHelper<use_nudge> >::calculateUnitBaseIndepVar;
  using InterpolationHelper<LogCosLinHelper<use_nudge> >::calculateUnitBaseIndepVarProcessed;
  using InterpolationHelper<LogCosLinHelper<use_nudge> >::calculateIndepVar;
  using InterpolationHelper<LogCosLinHelper<use_nudge> >::calculateProcessedIndepVar;

  //! Interpolate between two points
  template<typename IndepType, typename DepCosineType>
  static DepCosineType interpolate( const IndepType indep_var_0,
                              const IndepType indep_var_1,
                              const IndepType indep_var,
                              const DepCosineType dep_var_0,
                              const DepCosineType dep_var_1 );

  //! Interpolate between two points using the indep variable ratio (beta)
  template<typename T, typename DepCosineType>
  static DepCosineType interpolate( const T beta,
                              const DepCosineType dep_var_0,
                              const DepCosineType dep_var_1 );

  //! Interpolate between two points and return the processed value
  template<typename IndepType, typename DepCosineType>
  static typename QuantityTraits<DepCosineType>::RawType
  interpolateAndProcess( const IndepType indep_var_0,
                         const IndepType indep_var_1,
                         const IndepType indep_var,
                         const DepCosineType dep_var_0,
                         const DepCosineType dep_var_1 );

  //! Process the independent value
  template<typename T>
  static typename QuantityTraits<T>::RawType
  processIndepVar( const T cosine_var );

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
};

/*! \brief Policy struct for interpolating data tables that require logcos-lin
 * interpolation between evaluated points.
 * \details The dependent variable is always assumed to be an angle cosine.
 * Since the angle cosine goes below zero a direct log interpolation
 * cannot be performed on it. Instead a log interpolation will be performed
 * on the change in the angle cosine (eg: 1 - mu ) instead of the cosine
 * ( mu ). The interpolated value will always be cast into the cosine before
 * returned.
 * \ingroup policies
 */
struct LogCosLin : public LogCosLinHelper<false>
{
  //! Independent variable processing tag
  typedef LinIndepVarProcessingTag IndepVarProcessingTag;

  //! Dependent variable processing tag
  typedef LogCosDepVarProcessingTag DepVarProcessingTag;

  //! Get the interpolation type
  static InterpolationType getInterpolationType();

  //! Force base class template methods to be visible
  using LogCosLinHelper<false>::interpolate;
  using LogCosLinHelper<false>::interpolateAndProcess;
  using LogCosLinHelper<false>::calculateUnitBaseIndepVar;
  using LogCosLinHelper<false>::calculateUnitBaseIndepVarProcessed;
  using LogCosLinHelper<false>::calculateIndepVar;
  using LogCosLinHelper<false>::calculateProcessedIndepVar;
  using LogCosLinHelper<false>::processIndepVar;
  using LogCosLinHelper<false>::processDepVar;
  using LogCosLinHelper<false>::recoverProcessedIndepVar;
  using LogCosLinHelper<false>::recoverProcessedDepVar;
  using LogCosLinHelper<false>::isIndepVarInValidRange;
  using LogCosLinHelper<false>::isDepVarInValidRange;

  //! The name of the policy
  static const std::string name();
};

/*! \brief Policy struct for interpolating data tables that require
 * nudgedlogcos-lin interpolation between evaluated points.
 * \details The dependent variable is always assumed to be an angle cosine.
 * Since the angle cosine goes below zero a direct log interpolation
 * cannot be performed on it. Instead a log interpolation will be performed
 * on the change in the angle cosine (eg: 1 - mu + nudge ) instead of the cosine
 * ( mu ). The interpolated value will always be cast into the cosine before
 * returned.
 * \ingroup policies
 */
struct NudgedLogCosLin : public LogCosLinHelper<true>
{
  //! Independent variable processing tag
  typedef LinIndepVarProcessingTag IndepVarProcessingTag;

  //! Dependent variable processing tag
  typedef NudgedLogCosDepVarProcessingTag DepVarProcessingTag;

  //! Get the interpolation type
  static InterpolationType getInterpolationType();

  //! Force base class template methods to be visible
  using LogCosLinHelper<true>::interpolate;
  using LogCosLinHelper<true>::interpolateAndProcess;
  using LogCosLinHelper<true>::calculateUnitBaseIndepVar;
  using LogCosLinHelper<true>::calculateUnitBaseIndepVarProcessed;
  using LogCosLinHelper<true>::calculateIndepVar;
  using LogCosLinHelper<true>::calculateProcessedIndepVar;
  using LogCosLinHelper<true>::processIndepVar;
  using LogCosLinHelper<true>::processDepVar;
  using LogCosLinHelper<true>::recoverProcessedIndepVar;
  using LogCosLinHelper<true>::recoverProcessedDepVar;
  using LogCosLinHelper<true>::isIndepVarInValidRange;
  using LogCosLinHelper<true>::isDepVarInValidRange;

  //! The name of the policy
  static const std::string name();
};

/*! \brief Helper policy struct for interpolating data tables that require
 * lin-logcos interpolation between evaluated points.
 * \ingroup policies
 */
template<bool use_nudge = false>
struct LinLogCosHelper : public InterpolationHelper<LinLogCosHelper<use_nudge> >
{
  //! Force base class template methods to be visible
  using InterpolationHelper<LinLogCosHelper<use_nudge> >::interpolate;
  using InterpolationHelper<LinLogCosHelper<use_nudge> >::interpolateAndProcess;
  using InterpolationHelper<LinLogCosHelper<use_nudge> >::calculateUnitBaseIndepVar;
  using InterpolationHelper<LinLogCosHelper<use_nudge> >::calculateUnitBaseIndepVarProcessed;
  using InterpolationHelper<LinLogCosHelper<use_nudge> >::calculateIndepVar;
  using InterpolationHelper<LinLogCosHelper<use_nudge> >::calculateProcessedIndepVar;

  //! Interpolate between two points
  template<typename IndepCosineType, typename DepType>
  static DepType interpolate( const IndepCosineType indep_var_0,
                              const IndepCosineType indep_var_1,
                              const IndepCosineType indep_var,
                              const DepType dep_var_0,
                              const DepType dep_var_1 );

  //! Interpolate between two points using the indep variable ratio (beta)
  template<typename T, typename DepType>
  static DepType interpolate( const T beta,
                              const DepType dep_var_0,
                              const DepType dep_var_1 );

  //! Interpolate between two points and return the processed value
  template<typename IndepCosineType, typename DepType>
  static typename QuantityTraits<DepType>::RawType
  interpolateAndProcess( const IndepCosineType indep_var_0,
                         const IndepCosineType indep_var_1,
                         const IndepCosineType indep_var,
                         const DepType dep_var_0,
                         const DepType dep_var_1 );

  //! Process the independent value
  template<typename T>
  static typename QuantityTraits<T>::RawType
  processIndepVar( const T cosine_var );

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
};

/*! \brief Policy struct for interpolating data tables that require lin-logcos
 * interpolation between evaluated points.
 * \details The unprocessed independent variable is always assumed to be an
 * angle cosine. Since the angle cosine goes below zero a direct log
 * interpolation cannot be performed on it. Instead a log interpolation will be
 * performed on the change in the angle cosine (eg: 1 - mu ) instead of
 * the cosine ( mu ). The interpolated value will always be cast into the cosine
 * before returned. When a processed cosine grid is used, it is assumed that the
 * independent and dependent grids are inverted to maintain an ascending order.
 * \ingroup policies
 */
struct LinLogCos : public LinLogCosHelper<false>
{
  //! Independent variable processing tag
  typedef LogCosIndepVarProcessingTag IndepVarProcessingTag;

  //! Dependent variable processing tag
  typedef LinDepVarProcessingTag DepVarProcessingTag;

  //! Get the interpolation type
  static InterpolationType getInterpolationType();

  //! Force base class template methods to be visible
  using LinLogCosHelper<false>::interpolate;
  using LinLogCosHelper<false>::interpolateAndProcess;
  using LinLogCosHelper<false>::calculateUnitBaseIndepVar;
  using LinLogCosHelper<false>::calculateUnitBaseIndepVarProcessed;
  using LinLogCosHelper<false>::calculateIndepVar;
  using LinLogCosHelper<false>::calculateProcessedIndepVar;
  using LinLogCosHelper<false>::processIndepVar;
  using LinLogCosHelper<false>::processDepVar;
  using LinLogCosHelper<false>::recoverProcessedIndepVar;
  using LinLogCosHelper<false>::recoverProcessedDepVar;
  using LinLogCosHelper<false>::isIndepVarInValidRange;
  using LinLogCosHelper<false>::isIndepVarInValidRange;

  //! The name of the policy
  static const std::string name();
};

/*! \brief Policy struct for interpolating data tables that require
 * lin-nudgedlogcos interpolation between evaluated points.
 * \details The unprocessed independent variable is always assumed to be an
 * angle cosine. Since the angle cosine goes below zero a direct log
 * interpolation cannot be performed on it. Instead a log interpolation will be
 * performed on the change in the angle cosine (eg: 1 - mu + nudge ) instead of
 * the cosine ( mu ). The interpolated value will always be cast into the cosine
 * before returned. When a processed cosine grid is used, it is assumed that the
 * independent and dependent grids are inverted to maintain an ascending order.
 * \ingroup policies
 */
struct LinNudgedLogCos : public LinLogCosHelper<true>
{
  //! Independent variable processing tag
  typedef NudgedLogCosIndepVarProcessingTag IndepVarProcessingTag;

  //! Dependent variable processing tag
  typedef LinDepVarProcessingTag DepVarProcessingTag;

  //! Get the interpolation type
  static InterpolationType getInterpolationType();

  //! Force base class template methods to be visible
  using LinLogCosHelper<true>::interpolate;
  using LinLogCosHelper<true>::interpolateAndProcess;
  using LinLogCosHelper<true>::calculateUnitBaseIndepVar;
  using LinLogCosHelper<true>::calculateUnitBaseIndepVarProcessed;
  using LinLogCosHelper<true>::calculateIndepVar;
  using LinLogCosHelper<true>::calculateProcessedIndepVar;
  using LinLogCosHelper<true>::processIndepVar;
  using LinLogCosHelper<true>::processDepVar;
  using LinLogCosHelper<true>::recoverProcessedIndepVar;
  using LinLogCosHelper<true>::recoverProcessedDepVar;
  using LinLogCosHelper<true>::isIndepVarInValidRange;
  using LinLogCosHelper<true>::isIndepVarInValidRange;

  //! The name of the policy
  static const std::string name();
};

//! Helper class used to invert the cosine interpolation policy (LogCos-Log)
template<>
struct InverseInterpPolicy<LogCosLog>
{
  //! The inverse cosine interpolation policy
  typedef LogLogCos InterpPolicy;
};

//! Helper class used to invert the cosine interpolation policy (NudgedLogCos-Log)
template<>
struct InverseInterpPolicy<NudgedLogCosLog >
{
  //! The inverse cosine interpolation policy
  typedef LogNudgedLogCos InterpPolicy;
};

//! Helper class used to invert the cosine interpolation policy (Log-LogCos)
template<>
struct InverseInterpPolicy<LogLogCos>
{
  //! The inverse cosine interpolation policy
  typedef LogCosLog InterpPolicy;
};

//! Helper class used to invert the cosine interpolation policy (Log-NudgedLogCos)
template<>
struct InverseInterpPolicy<LogNudgedLogCos>
{
  //! The inverse cosine interpolation policy
  typedef NudgedLogCosLog InterpPolicy;
};

//! Helper class used to invert the cosine interpolation policy (LogCos-Lin)
template<>
struct InverseInterpPolicy<LogCosLin>
{
  //! The inverse cosine interpolation policy
  typedef LinLogCos InterpPolicy;
};

//! Helper class used to invert the cosine interpolation policy (NudgedLogCos-Lin)
template<>
struct InverseInterpPolicy<NudgedLogCosLin>
{
  //! The inverse cosine interpolation policy
  typedef LinNudgedLogCos InterpPolicy;
};

//! Helper class used to invert the cosine interpolation policy (Lin-LogCos)
template<>
struct InverseInterpPolicy<LinLogCos>
{
  //! The inverse cosine interpolation policy
  typedef LogCosLin InterpPolicy;
};

//! Helper class used to invert the cosine interpolation policy (Lin-NudgedLogCos)
template<>
struct InverseInterpPolicy<LinNudgedLogCos>
{
  //! The inverse cosine interpolation policy
  typedef NudgedLogCosLin InterpPolicy;
};

// use_nudge = true
TYPE_NAME_TRAITS_QUICK_DECL( NudgedLogCosLog );
TYPE_NAME_TRAITS_QUICK_DECL( LogNudgedLogCos );
TYPE_NAME_TRAITS_QUICK_DECL( NudgedLogCosLin );
TYPE_NAME_TRAITS_QUICK_DECL( LinNudgedLogCos );
// use_nudge = true
TYPE_NAME_TRAITS_QUICK_DECL( LogCosLog );
TYPE_NAME_TRAITS_QUICK_DECL( LogLogCos );
TYPE_NAME_TRAITS_QUICK_DECL( LogCosLin );
TYPE_NAME_TRAITS_QUICK_DECL( LinLogCos );

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template includes
//---------------------------------------------------------------------------//

#include "Utility_CosineInterpolationPolicy_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_COSINE_INTERPOLATION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_CosineInterpolationPolicy.hpp
//---------------------------------------------------------------------------//
