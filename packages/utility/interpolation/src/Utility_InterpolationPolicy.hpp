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
#include "Utility_InterpolationType.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_TypeNameTraits.hpp"

namespace Utility{

//! The log independent variable processing tag
struct LogIndepVarProcessingTag{};

//! The lin independent variable processing tag
struct LinIndepVarProcessingTag{};

//! The log dependent variable processing tag
struct LogDepVarProcessingTag{};

//! The lin dependent variable processing tag
struct LinDepVarProcessingTag{};

/*! \brief Helper policy struct for use with the interpolation structs
 * \ingroup policies
 */
template<typename ParentInterpolationType>
class InterpolationHelper
{

private:

  // Typedef for this type
  typedef InterpolationHelper<ParentInterpolationType> ThisType;

public:

  //! Interpolate between two processed points
  template<typename T>
  static T interpolate( const T processed_indep_var_0,
			const T processed_indep_var,
			const T processed_dep_var_0,
			const T processed_slope );

  //! Interpolate between two processed points and return the processed value
  template<typename T>
  static T interpolateAndProcess( const T processed_indep_var_0,
				  const T processed_indep_var,
				  const T processed_dep_var_0,
				  const T processed_slope );

  //! Calculate the unit base grid length (L)
  template<typename IndepType>
  static typename QuantityTraits<IndepType>::RawType
  calculateUnitBaseGridLength( const IndepType grid_lower_indep_value,
                               const IndepType grid_upper_indep_value );

  //! Calculate the unit base grid length from a processed grid (L)
  template<typename T>
  static T calculateUnitBaseGridLengthProcessed(
                                    const T processed_grid_lower_indep_value,
                                    const T processed_grid_upper_indep_value );

  //! Calculate the unit base independent variable (eta)
  template<typename IndepType>
  static typename QuantityTraits<IndepType>::RawType
  calculateUnitBaseIndepVar(
         const IndepType indep_var,
         const IndepType indep_var_min,
         const typename QuantityTraits<IndepType>::RawType indep_grid_length,
         const double tol = 1e-3 );

  //! Calculate the unit base independent variable (eta)
  template<typename T>
  static T calculateUnitBaseIndepVarProcessed( const T processed_indep_var,
                                               const T processed_indep_var_min,
                                               const T indep_grid_length,
                                               const double tol = 1e-3 );

  //! Calculate the independent variable (from eta)
  template<typename IndepType>
  static IndepType calculateIndepVar(
         const typename QuantityTraits<IndepType>::RawType eta,
         const IndepType indep_var_min,
         const typename QuantityTraits<IndepType>::RawType indep_grid_length,
         const double tol = 1e-3 );

  //! Calculate the processed independent variable (from eta)
  template<typename T>
  static T calculateProcessedIndepVar( const T eta,
                                       const T processed_indep_var_min,
                                       const T indep_grid_length );

  //! Calculate the "fuzzy" lower bound (lower bound with roundoff tolerance)
  template<typename T>
  static T calculateFuzzyLowerBound( const T value, const double tol = 1e-3 );

  //! Calculate the "fuzzy" upper bound (upper bound with roundoff tolerance)
  template<typename T>
  static T calculateFuzzyUpperBound( const T value, const double tol = 1e-3 );

  //! The name of the policy
  static std::string name();
};

/*! \brief Policy struct for interpolating data tables that require log-log
 * interpolation between evaluated points.
 * \ingroup policies
 */
struct LogLog : public InterpolationHelper<LogLog>
{
  //! Independent variable processing tag
  typedef LogIndepVarProcessingTag IndepVarProcessingTag;

  //! Dependent variable processing tag
  typedef LogDepVarProcessingTag DepVarProcessingTag;

  //! Get the interpolation type
  static InterpolationType getInterpolationType();

  //! Force base class template methods to be visible
  using InterpolationHelper<LogLog>::interpolate;
  using InterpolationHelper<LogLog>::interpolateAndProcess;
  using InterpolationHelper<LogLog>::calculateUnitBaseIndepVar;
  using InterpolationHelper<LogLog>::calculateUnitBaseIndepVarProcessed;
  using InterpolationHelper<LogLog>::calculateIndepVar;
  using InterpolationHelper<LogLog>::calculateProcessedIndepVar;

  //! Interpolate between two points
  template<typename IndepType, typename DepType>
  static DepType interpolate( const IndepType indep_var_0,
                              const IndepType indep_var_1,
                              const IndepType indep_var,
                              const DepType dep_var_0,
                              const DepType dep_var_1 );

  //! Interpolate between two points using the indep variable ratio (beta)
  template<typename T, typename DepType>
  static DepType interpolate( const T beta,
                              const DepType dep_var_0,
                              const DepType dep_var_1 );

  //! Interpolate between two points and return the processed value
  template<typename IndepType, typename DepType>
  static typename QuantityTraits<DepType>::RawType
  interpolateAndProcess( const IndepType indep_var_0,
                         const IndepType indep_var_1,
                         const IndepType indep_var,
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

/*! \brief Policy struct for interpolating data tables that require log-lin
 * interpolation between evaluated points.
 * \ingroup policies
 */
struct LogLin : public InterpolationHelper<LogLin>
{
  //! Independent variable processing tag
  typedef LinIndepVarProcessingTag IndepVarProcessingTag;

  //! Dependent variable processing tag
  typedef LogDepVarProcessingTag DepVarProcessingTag;

  //! Get the interpolation type
  static InterpolationType getInterpolationType();

  //! Force base class template methods to be visible
  using InterpolationHelper<LogLin>::interpolate;
  using InterpolationHelper<LogLin>::interpolateAndProcess;
  using InterpolationHelper<LogLin>::calculateUnitBaseIndepVar;
  using InterpolationHelper<LogLin>::calculateUnitBaseIndepVarProcessed;
  using InterpolationHelper<LogLin>::calculateIndepVar;
  using InterpolationHelper<LogLin>::calculateProcessedIndepVar;

  //! Interpolate between two points
  template<typename IndepType, typename DepType>
  static DepType interpolate( const IndepType indep_var_0,
                              const IndepType indep_var_1,
                              const IndepType indep_var,
                              const DepType dep_var_0,
                              const DepType dep_var_1 );

  //! Interpolate between two points using the indep variable ratio (beta)
  template<typename T, typename DepType>
  static DepType interpolate( const T beta,
                              const DepType dep_var_0,
                              const DepType dep_var_1 );

  //! Interpolate between two points and return the processed value
  template<typename IndepType, typename DepType>
  static typename QuantityTraits<DepType>::RawType
  interpolateAndProcess( const IndepType indep_var_0,
                         const IndepType indep_var_1,
                         const IndepType indep_var,
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

/*! \brief Policy struct for interpolating data tables that require lin-log
 * interpolation between evaluated points.
 * \ingroup policies
 */
struct LinLog : public InterpolationHelper<LinLog>
{
  //! Independent variable processing tag
  typedef LogIndepVarProcessingTag IndepVarProcessingTag;

  //! Dependent variable processing tag
  typedef LinDepVarProcessingTag DepVarProcessingTag;

  //! Get the interpolation type
  static InterpolationType getInterpolationType();

  //! Force base class template methods to be visible
  using InterpolationHelper<LinLog>::interpolate;
  using InterpolationHelper<LinLog>::interpolateAndProcess;
  using InterpolationHelper<LinLog>::calculateUnitBaseIndepVar;
  using InterpolationHelper<LinLog>::calculateUnitBaseIndepVarProcessed;
  using InterpolationHelper<LinLog>::calculateIndepVar;
  using InterpolationHelper<LinLog>::calculateProcessedIndepVar;

  //! Interpolate between two points
  template<typename IndepType, typename DepType>
  static DepType interpolate( const IndepType indep_var_0,
                              const IndepType indep_var_1,
                              const IndepType indep_var,
                              const DepType dep_var_0,
                              const DepType dep_var_1 );

  //! Interpolate between two points using the indep variable ratio (beta)
  template<typename T, typename DepType>
  static DepType interpolate( const T beta,
                              const DepType dep_var_0,
                              const DepType dep_var_1 );

  //! Interpolate between two points and return the processed value
  template<typename IndepType, typename DepType>
  static typename QuantityTraits<DepType>::RawType
  interpolateAndProcess( const IndepType indep_var_0,
                         const IndepType indep_var_1,
                         const IndepType indep_var,
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

/*! \brief Policy struct for interpolating data tables that require lin-lin
 * interpolation between evaluated points.
 * \ingroup policies
 */
struct LinLin : public InterpolationHelper<LinLin>
{
  //! Independent variable processing tag
  typedef LinIndepVarProcessingTag IndepVarProcessingTag;

  //! Dependent variable processing tag
  typedef LinDepVarProcessingTag DepVarProcessingTag;

  //! Get the interpolation type
  static InterpolationType getInterpolationType();

  //! Force base class template methods to be visible
  using InterpolationHelper<LinLin>::interpolate;
  using InterpolationHelper<LinLin>::interpolateAndProcess;
  using InterpolationHelper<LinLin>::calculateUnitBaseIndepVar;
  using InterpolationHelper<LinLin>::calculateUnitBaseIndepVarProcessed;
  using InterpolationHelper<LinLin>::calculateIndepVar;
  using InterpolationHelper<LinLin>::calculateProcessedIndepVar;

  //! Interpolate between two points
  template<typename IndepType, typename DepType>
  static DepType interpolate( const IndepType indep_var_0,
                              const IndepType indep_var_1,
                              const IndepType indep_var,
                              const DepType dep_var_0,
                              const DepType dep_var_1 );

  //! Interpolate between two points using the indep variable ratio (beta)
  template<typename T, typename DepType>
  static DepType interpolate( const T beta,
                              const DepType dep_var_0,
                              const DepType dep_var_1 );

  //! Interpolate between two points and return the processed value
  template<typename IndepType, typename DepType>
  static typename QuantityTraits<DepType>::RawType
  interpolateAndProcess( const IndepType indep_var_0,
                         const IndepType indep_var_1,
                         const IndepType indep_var,
                         const DepType dep_var_0,
                         const DepType dep_var_1 );

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
};

TYPE_NAME_TRAITS_QUICK_DECL( LinLin );
TYPE_NAME_TRAITS_QUICK_DECL( LinLog );
TYPE_NAME_TRAITS_QUICK_DECL( LogLin );
TYPE_NAME_TRAITS_QUICK_DECL( LogLog );

//! Helper class used to create an interpolation policy from tags
template<typename DepVarProcessingTag, typename IndepVarProcessingTag>
struct InterpPolicyCreationHelper;

//! Specialization of Utility::InterpPolicyCreationHelper for LinLin tags
template<>
struct InterpPolicyCreationHelper<LinDepVarProcessingTag,LinIndepVarProcessingTag>
{ typedef LinLin Policy; };

//! Specialization of Utility::InterpPolicyCreationHelper for LinLog tags
template<>
struct InterpPolicyCreationHelper<LinDepVarProcessingTag,LogIndepVarProcessingTag>
{ typedef LinLog Policy; };

//! Specialization of Utility::InterpPolicyCreationHelper for LogLin tags
template<>
struct InterpPolicyCreationHelper<LogDepVarProcessingTag,LinIndepVarProcessingTag>
{ typedef LogLin Policy; };

//! Specialization of Utility::InterpPolicyCreationHelper for LogLog tags
template<>
struct InterpPolicyCreationHelper<LogDepVarProcessingTag,LogIndepVarProcessingTag>
{ typedef LogLog Policy; };

//! Helper class used to invert the interpolation policy
template<typename ParentInterpolationType>
struct InverseInterpPolicy
{
  //! The inverse interpolation policy
  typedef ParentInterpolationType InterpPolicy;
};

//! Helper class used to invert the interpolation policy (Lin-Log)
template<>
struct InverseInterpPolicy<LinLog>
{
  //! The inverse interpolation policy
  typedef LogLin InterpPolicy;
};

//! Helper class used to invert the interpolation policy (Log-Lin)
template<>
struct InverseInterpPolicy<LogLin>
{
  //! The inverse interpolation policy
  typedef LinLog InterpPolicy;
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
