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

//! The log independent variable processing tag
template<bool use_nudge = false>
struct LogCosIndepVarProcessingTag{};

//! The log dependent variable processing tag
template<bool use_nudge = false>
struct LogCosDepVarProcessingTag{};

//! Helper struct for turning the cosine interp nudge factor on/off
template<bool use_nudge>
struct CosNudgeHelper
{
  static constexpr double nudge_factor = 1e-10;

  //! Convert from cosine variable
  /*! \details This function converts from cosine (mu) to the delta cosine
  * (1 - mu) + nudge.
  */
  template<typename T>
  static inline T convertFromCosineVar( const T cosine_var )
  {
    return (QuantityTraits<T>::one() - cosine_var) + QuantityTraits<T>::one()*nudge_factor;
  }

  //! Convert to cosine variable
  /*! \details This function converts from the delta cosine (1 - mu) + nudge
  *  back to cosine (mu).
  */
  template<typename T>
  static inline T convertToCosineVar( const T delta_cosine )
  {
    return (QuantityTraits<T>::one()*nudge_factor - delta_cosine) + QuantityTraits<T>::one();
  }
};

template<>
struct CosNudgeHelper<true>
{
  static constexpr double nudge_factor = 1e-10;

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
  static constexpr double nudge_factor = 0.0;

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

/*! \brief Policy struct for interpolating data tables that require logcos-log
 * interpolation between evaluated points.
 * \details The dependent variable is always assumed to be an angle cosine.
 * Since the angle cosine goes below zero a direct log interpolation
 * cannot be performed on it. Instead a log interpolation will be performed
 * on the change in the angle cosine (eg: 1 - mu + nudge ) instead of the cosine
 * ( mu ). The interpolated value will always be cast into the cosine before
 * returned.
 * \ingroup policies
 */
template<bool use_nudge = false>
struct LogCosLog : public InterpolationHelper<LogCosLog<use_nudge> >
{
  //! Independent variable processing tag
  typedef LogIndepVarProcessingTag IndepVarProcessingTag;

  //! Dependent variable processing tag
  typedef LogCosDepVarProcessingTag<use_nudge> DepVarProcessingTag;

  //! Get the interpolation type
  static InterpolationType getInterpolationType();

  //! Force base class template methods to be visible
  using InterpolationHelper<LogCosLog<use_nudge> >::interpolate;
  using InterpolationHelper<LogCosLog<use_nudge> >::interpolateAndProcess;
  using InterpolationHelper<LogCosLog<use_nudge> >::calculateUnitBaseIndepVar;
  using InterpolationHelper<LogCosLog<use_nudge> >::calculateUnitBaseIndepVarProcessed;
  using InterpolationHelper<LogCosLog<use_nudge> >::calculateIndepVar;
  using InterpolationHelper<LogCosLog<use_nudge> >::calculateProcessedIndepVar;
  // using InterpolationHelper<LogCosLog<use_nudge> >::convertFromCosineVar;
  // using InterpolationHelper<LogCosLog<use_nudge> >::convertToCosineVar;

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

  //! The name of the policy
  static const std::string name();

  //! Return if the cosine nudge factor is on
  static const bool isCosineNudgeOn();
};

/*! \brief Policy struct for interpolating data tables that require log-log
 * cosine interpolation between evaluated points.
 * \details The unprocessed independent variable is always assumed to be an angle
 * cosine. Since the angle cosine goes below zero a direct log interpolation
 * cannot be performed on it. Instead a log interpolation will be performed
 * on the change in the angle cosine (eg: 1 - mu + nudge ) instead of the cosine
 * ( mu ). The interpolated value will always be cast into the cosine before
 * returned. When a processed cosine grid is used, it is assumed that the
 * independent and dependent grids are inverted to maintain an ascending order.
 * \ingroup policies
 */
template<bool use_nudge = false>
struct LogLogCos : public InterpolationHelper<LogLogCos<use_nudge> >
{
  //! Independent variable processing tag
  typedef LogCosIndepVarProcessingTag<use_nudge> IndepVarProcessingTag;

  //! Dependent variable processing tag
  typedef LogDepVarProcessingTag DepVarProcessingTag;

  //! Get the interpolation type
  static InterpolationType getInterpolationType();

  //! Force base class template methods to be visible
  using InterpolationHelper<LogLogCos<use_nudge> >::interpolate;
  using InterpolationHelper<LogLogCos<use_nudge> >::interpolateAndProcess;
  using InterpolationHelper<LogLogCos<use_nudge> >::calculateUnitBaseIndepVar;
  using InterpolationHelper<LogLogCos<use_nudge> >::calculateUnitBaseIndepVarProcessed;
  using InterpolationHelper<LogLogCos<use_nudge> >::calculateIndepVar;
  using InterpolationHelper<LogLogCos<use_nudge> >::calculateProcessedIndepVar;
  // using InterpolationHelper<LogLogCos<use_nudge> >::convertFromCosineVar;
  // using InterpolationHelper<LogLogCos<use_nudge> >::convertToCosineVar;

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

  //! The name of the policy
  static const std::string name();

  //! Return if the cosine nudge factor is on
  static const bool isCosineNudgeOn();
};

/*! \brief Policy struct for interpolating data tables that require logcos-lin
 * interpolation between evaluated points.
 * \details The dependent variable is always assumed to be an angle cosine.
 * Since the angle cosine goes below zero a direct log interpolation
 * cannot be performed on it. Instead a log interpolation will be performed
 * on the change in the angle cosine (eg: 1 - mu + nudge ) instead of the cosine
 * ( mu ). The interpolated value will always be cast into the cosine before
 * returned.
 * \ingroup policies
 */
template<bool use_nudge = false>
struct LogCosLin : public InterpolationHelper<LogCosLin<use_nudge> >
{
  //! Independent variable processing tag
  typedef LinIndepVarProcessingTag IndepVarProcessingTag;

  //! Dependent variable processing tag
  typedef LogCosDepVarProcessingTag<use_nudge> DepVarProcessingTag;

  //! Get the interpolation type
  static InterpolationType getInterpolationType();

  //! Force base class template methods to be visible
  using InterpolationHelper<LogCosLin<use_nudge> >::interpolate;
  using InterpolationHelper<LogCosLin<use_nudge> >::interpolateAndProcess;
  using InterpolationHelper<LogCosLin<use_nudge> >::calculateUnitBaseIndepVar;
  using InterpolationHelper<LogCosLin<use_nudge> >::calculateUnitBaseIndepVarProcessed;
  using InterpolationHelper<LogCosLin<use_nudge> >::calculateIndepVar;
  using InterpolationHelper<LogCosLin<use_nudge> >::calculateProcessedIndepVar;
  // using InterpolationHelper<LogCosLin<use_nudge> >::convertFromCosineVar;
  // using InterpolationHelper<LogCosLin<use_nudge> >::convertToCosineVar;

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

  //! The name of the policy
  static const std::string name();

  //! Return if the cosine nudge factor is on
  static const bool isCosineNudgeOn();
};

/*! \brief Policy struct for interpolating data tables that require lin-logcos
 * interpolation between evaluated points.
 * \details The unprocessed independent variable is always assumed to be an
 * angle cosine. Since the angle cosine goes below zero a direct log
 * interpolation cannot be performed on it. Instead a log interpolation will be
 * performed on the change in the angle cosine (eg: 1 - mu + nudge ) instead of
 * the cosine ( mu ). The interpolated value will always be cast into the cosine
 * before returned. When a processed cosine grid is used, it is assumed that the
 * independent and dependent grids are inverted to maintain an ascending order.
 * \ingroup policies
 */
template<bool use_nudge = false>
struct LinLogCos : public InterpolationHelper<LinLogCos<use_nudge> >
{
  //! Independent variable processing tag
  typedef LogCosIndepVarProcessingTag<use_nudge> IndepVarProcessingTag;

  //! Dependent variable processing tag
  typedef LinDepVarProcessingTag DepVarProcessingTag;

  //! Get the interpolation type
  static InterpolationType getInterpolationType();

  //! Force base class template methods to be visible
  using InterpolationHelper<LinLogCos<use_nudge> >::interpolate;
  using InterpolationHelper<LinLogCos<use_nudge> >::interpolateAndProcess;
  using InterpolationHelper<LinLogCos<use_nudge> >::calculateUnitBaseIndepVar;
  using InterpolationHelper<LinLogCos<use_nudge> >::calculateUnitBaseIndepVarProcessed;
  using InterpolationHelper<LinLogCos<use_nudge> >::calculateIndepVar;
  using InterpolationHelper<LinLogCos<use_nudge> >::calculateProcessedIndepVar;
  // using InterpolationHelper<LinLogCos<use_nudge> >::convertFromCosineVar;
  // using InterpolationHelper<LinLogCos<use_nudge> >::convertToCosineVar;

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

  //! The name of the policy
  static const std::string name();

  //! Return if the cosine nudge factor is on
  static const bool isCosineNudgeOn();
};

//! Helper class used to invert the cosine interpolation policy (LogCos-Log)
template<>
struct InverseInterpPolicy<LogCosLog<false> >
{
  //! The inverse cosine interpolation policy
  typedef LogLogCos<false> InterpPolicy;
};

//! Helper class used to invert the cosine interpolation policy (LogCos-Log)
template<>
struct InverseInterpPolicy<LogCosLog<true> >
{
  //! The inverse cosine interpolation policy
  typedef LogLogCos<true> InterpPolicy;
};

//! Helper class used to invert the cosine interpolation policy (Log-LogCos)
template<>
struct InverseInterpPolicy<LogLogCos<false> >
{
  //! The inverse cosine interpolation policy
  typedef LogCosLog<false> InterpPolicy;
};

//! Helper class used to invert the cosine interpolation policy (Log-LogCos)
template<>
struct InverseInterpPolicy<LogLogCos<true> >
{
  //! The inverse cosine interpolation policy
  typedef LogCosLog<true> InterpPolicy;
};

//! Helper class used to invert the cosine interpolation policy (LogCos-Lin)
template<>
struct InverseInterpPolicy<LogCosLin<false> >
{
  //! The inverse cosine interpolation policy
  typedef LinLogCos<false> InterpPolicy;
};

//! Helper class used to invert the cosine interpolation policy (LogCos-Lin)
template<>
struct InverseInterpPolicy<LogCosLin<true> >
{
  //! The inverse cosine interpolation policy
  typedef LinLogCos<true> InterpPolicy;
};

//! Helper class used to invert the cosine interpolation policy (Lin-LogCos)
template<>
struct InverseInterpPolicy<LinLogCos<false> >
{
  //! The inverse cosine interpolation policy
  typedef LogCosLin<false> InterpPolicy;
};

//! Helper class used to invert the cosine interpolation policy (Lin-LogCos)
template<>
struct InverseInterpPolicy<LinLogCos<true> >
{
  //! The inverse cosine interpolation policy
  typedef LogCosLin<true> InterpPolicy;
};

// use_nudge = true
TYPE_NAME_TRAITS_QUICK_DECL( LogCosLog<true> );
TYPE_NAME_TRAITS_QUICK_DECL( LogLogCos<true> );
TYPE_NAME_TRAITS_QUICK_DECL( LogCosLin<true> );
TYPE_NAME_TRAITS_QUICK_DECL( LinLogCos<true> );
// use_nudge = true
TYPE_NAME_TRAITS_QUICK_DECL( LogCosLog<false> );
TYPE_NAME_TRAITS_QUICK_DECL( LogLogCos<false> );
TYPE_NAME_TRAITS_QUICK_DECL( LogCosLin<false> );
TYPE_NAME_TRAITS_QUICK_DECL( LinLogCos<false> );

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
