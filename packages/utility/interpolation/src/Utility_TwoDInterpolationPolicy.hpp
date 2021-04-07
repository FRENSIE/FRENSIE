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
#include "Utility_CosineInterpolationPolicy.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_TypeNameTraits.hpp"

namespace Utility{

namespace {

//! Helper class used by unit base interpolation methods
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

//! Helper class used by unit base interpolation methods (LogCos-Lin)
template<>
struct UnitBaseHelper<LogCosIndepVarProcessingTag,LinIndepVarProcessingTag>
{
  //! The YX interpolation policy
  typedef LogCosLin YXInterpPolicy;
};

//! Helper class used by unit base interpolation methods (LogCos-Lin)
template<>
struct UnitBaseHelper<NudgedLogCosIndepVarProcessingTag,LinIndepVarProcessingTag>
{
  //! The YX interpolation policy
  typedef NudgedLogCosLin YXInterpPolicy;
};

//! Helper class used by unit base interpolation methods (Log-Lin)
template<>
struct UnitBaseHelper<LogCosIndepVarProcessingTag,LogIndepVarProcessingTag>
{
  //! The YX interpolation policy
  typedef LogCosLog YXInterpPolicy;
};

//! Helper class used by unit base interpolation methods (Log-Lin)
template<>
struct UnitBaseHelper<NudgedLogCosIndepVarProcessingTag,LogIndepVarProcessingTag>
{
  //! The YX interpolation policy
  typedef NudgedLogCosLog YXInterpPolicy;
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

  //! This type
  typedef TwoDInterpolationPolicyImpl<ZYInterpPolicy,ZXInterpPolicy> ThisType;

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

  //! The ZX interpolation policy
  typedef ZXInterpPolicy PrimaryBasePolicy;

  //! The ZY interpolation policy
  typedef ZYInterpPolicy SecondaryBasePolicy;

  //! Process the dependent variable (z - ZYX)
  template<typename T>
  static typename QuantityTraits<T>::RawType processDepVar( const T dep_var );

  //! Recover the processed dependent variable (z - ZYX)
  template<typename T>
  static T recoverProcessedDepVar( const T processed_dep_var );

  //! Test if the dependent variable is in a valid range (z - ZYX)
  template<typename T>
  static bool isDepVarInValidRange( const T dep_var );

  //! Process the second independent variable (y - ZYX)
  template<typename T>
  static typename QuantityTraits<T>::RawType
  processSecondIndepVar( const T second_indep_var );

  //! Recover the processed second independent variable (y - ZYX)
  template<typename T>
  static T recoverProcessedSecondIndepVar( const T processed_second_indep_var);

  //! Test if the second independent variable is in a valid range (y - ZYX)
  template<typename T>
  static bool isSecondIndepVarInValidRange( const T second_indep_var );

  //! Process the first independent variable (x - ZYX)
  template<typename T>
  static typename QuantityTraits<T>::RawType
  processFirstIndepVar( const T first_indep_var );

  //! Recover the first independent variable (x - ZYX)
  template<typename T>
  static T recoverProcessedFirstIndepVar( const T processed_first_indep_var );

  //! Test if the first independent variable is in a valid range (x - ZYX)
  template<typename T>
  static bool isFirstIndepVarInValidRange( const T first_indep_var );

  //! Calculate the length of an intermediate grid
  template<typename IndepType, typename LengthType>
  static LengthType calculateIntermediateGridLength(
                                              const IndepType indep_var_x_0,
                                              const IndepType indep_var_x_1,
                                              const IndepType indep_var_x,
                                              const LengthType grid_0_length,
                                              const LengthType grid_1_length );

  //! Calculate the length of an intermediate grid using the indep variable ratio (beta)
  template<typename IndepRatioType, typename LengthType>
  static LengthType calculateIntermediateGridLength(
                       const IndepRatioType beta,
                       const LengthType grid_0_length,
                       const LengthType grid_1_length );

  //! Calculate the length of a processed intermediate grid
  template<typename T>
  static T calculateIntermediateGridLengthProcessed(
					    const T processed_indep_var_x_0,
					    const T processed_indep_var_x_1,
					    const T processed_indep_var_x,
					    const T grid_0_length,
					    const T grid_1_length );

  //! Calculate the min value of an intermediate grid
  template<typename IndepType, typename LimitType>
  static LimitType calculateIntermediateGridLimit(
                                              const IndepType indep_var_x_0,
                                              const IndepType indep_var_x_1,
                                              const IndepType indep_var_x,
                                              const LimitType grid_0_y_limit,
                                              const LimitType grid_1_y_limit );

  //! Calculate the processed min value of a processed intermediate grid
  template<typename T>
  static T calculateIntermediateProcessedGridLimit(
					    const T processed_indep_var_x_0,
					    const T processed_indep_var_x_1,
					    const T processed_indep_var_x,
					    const T processed_grid_0_y_limit,
					    const T processed_grid_1_y_limit );

  //! Conduct the interpolation between two grids
  template<typename FirstIndepType,
           typename SecondIndepType,
           typename ZYLowerFunctor,
           typename ZYUpperFunctor>
  static typename ZYLowerFunctor::result_type interpolate(
                           const FirstIndepType indep_var_x_0,
                           const FirstIndepType indep_var_x_1,
                           const FirstIndepType indep_var_x,
                           const SecondIndepType indep_var_y,
                           const ZYLowerFunctor& evaluate_z_with_y_0_functor,
                           const ZYUpperFunctor& evaluate_z_with_y_1_functor );

  //! Conduct the interpolation between two grids
  template<size_t YIndepMember,
	   size_t DepMember,
	   typename YIterator,
	   typename ZIterator,
	   typename T>
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
  template<size_t YIndepMember,
	   size_t DepMember,
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
  template<typename FirstIndepType,
           typename SecondIndepType,
           typename ZYLowerFunctor,
           typename ZYUpperFunctor>
  static typename ZYLowerFunctor::result_type interpolateUnitBase(
    const FirstIndepType indep_var_x_0,
    const FirstIndepType indep_var_x_1,
    const FirstIndepType indep_var_x,
    const SecondIndepType indep_var_y,
    const SecondIndepType indep_var_y_min,
    const SecondIndepType indep_var_y_max,
    const SecondIndepType indep_var_y_0_min,
    const SecondIndepType indep_var_y_0_max,
    const SecondIndepType indep_var_y_1_min,
    const SecondIndepType indep_var_y_1_max,
    const ZYLowerFunctor& evaluate_z_with_y_0_functor,
    const ZYUpperFunctor& evaluate_z_with_y_1_functor,
    const typename ZYLowerFunctor::result_type below_lower_limit_return_value =
    QuantityTraits<typename ZYLowerFunctor::result_type>::zero(),
    const typename ZYLowerFunctor::result_type above_upper_limit_return_value =
    QuantityTraits<typename ZYLowerFunctor::result_type>::zero(),
    const double fuzzy_boundary_tol = 1e-3 );

  //! Conduct unit base interpolation between two grids
  template<typename FirstIndepType,
           typename SecondIndepType,
           typename ZYLowerFunctor,
           typename ZYUpperFunctor>
  static typename ZYLowerFunctor::result_type interpolateUnitBase(
    const FirstIndepType indep_var_x_0,
    const FirstIndepType indep_var_x_1,
    const FirstIndepType indep_var_x,
    const SecondIndepType indep_var_y,
    const SecondIndepType indep_var_y_0_min,
    const SecondIndepType indep_var_y_0_max,
    const SecondIndepType indep_var_y_1_min,
    const SecondIndepType indep_var_y_1_max,
    const ZYLowerFunctor& evaluate_z_with_y_0_functor,
    const ZYUpperFunctor& evaluate_z_with_y_1_functor,
    const typename ZYLowerFunctor::result_type below_lower_limit_return_value =
    QuantityTraits<typename ZYLowerFunctor::result_type>::zero(),
    const typename ZYLowerFunctor::result_type above_upper_limit_return_value =
    QuantityTraits<typename ZYLowerFunctor::result_type>::zero(),
    const double fuzzy_boundary_tol = 1e-3 );

  //! Conduct unit base interpolation between two grids
  template<size_t YIndepMember,
	   size_t DepMember,
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
				ZIterator end_dep_grid_1,
				const double fuzzy_boundary_tol = 1e-3 );

  //! Conduct the interpolation between two grids
  template<size_t YIndepMember,
	   size_t DepMember,
	   typename Iterator,
	   typename T>
  static T interpolateUnitBase( const T indep_var_x_0,
				const T indep_var_x_1,
				const T indep_var_x,
				const T indep_var_y,
				Iterator start_grid_0,
				Iterator end_grid_0,
				Iterator start_grid_1,
				Iterator end_grid_1,
				const double fuzzy_boundary_tol = 1e-3 );

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
				ZIterator end_dep_var_1,
				const double fuzzy_boundary_tol = 1e-3 );

  //! Conduct the interpolation between two processed grids
  template<size_t YIndepMember,
	   size_t DepMember,
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
  template<size_t YIndepMember,
	   size_t DepMember,
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
  template<size_t YIndepMember,
	   size_t DepMember,
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
  template<size_t YIndepMember,
	   size_t DepMember,
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

private:

  // Calculate the "fuzzy" lower bound (lower bound with roundoff tolerance)
  template<typename T>
  static T calculateFuzzyLowerBound( const T lower_bound,
                                     const double tol = 1e-3 );

  // Calculate the "fuzzy" upper bound (upper bound with roundoff tolerance)
  template<typename T>
  static T calculateFuzzyUpperBound( const T upper_bound,
                                     const double tol = 1e-3 );

  // Interpolate on the specified y grid
  template<size_t YIndepMember,
	   size_t DepMember,
	   typename YIterator,
	   typename ZIterator,
	   typename T>
  static T interpolateOnYGrid( const T indep_var_y,
                               YIterator start_indep_y_grid,
                               YIterator end_indep_y_grid,
                               ZIterator start_dep_grid,
                               ZIterator end_dep_grid );

  // Interpolate on the specified processed y grid
  template<size_t YIndepMember,
	   size_t DepMember,
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
  typedef LinLin YXInterpPolicy;

  //! The name of the policy
  static const std::string name();
};

/*! \brief Policy struct for interpolating 2D tables (Z-Y interpolation policy
 * is Lin-Log and Z-X policy interpolation policy is Lin-Lin).
 */
struct LinLogLin : public TwoDInterpolationPolicyImpl<LinLog,LinLin>
{
  typedef LinLog ZYInterpPolicy;
  typedef LinLin ZXInterpPolicy;
  typedef LogLin YXInterpPolicy;

  //! The name of the policy
  static const std::string name();
};

/*! \brief Policy struct for interpolating 2D tables (Z-Y interpolation policy
 * is Lin-Lin and Z-X policy interpolation policy is Lin-Log).
 */
struct LinLinLog : public TwoDInterpolationPolicyImpl<LinLin,LinLog>
{
  typedef LinLin ZYInterpPolicy;
  typedef LinLog ZXInterpPolicy;
  typedef LinLog YXInterpPolicy;

  //! The name of the policy
  static const std::string name();
};

/*! \brief Policy struct for interpolating 2D tables (Z-Y interpolation policy
 * is Lin-Log and Z-X policy interpolation policy is Lin-Log).
 */
struct LinLogLog : public TwoDInterpolationPolicyImpl<LinLog,LinLog>
{
  typedef LinLog ZYInterpPolicy;
  typedef LinLog ZXInterpPolicy;
  typedef LogLog YXInterpPolicy;

  //! The name of the policy
  static const std::string name();
};

/*! \brief Policy struct for interpolating 2D tables (Z-Y interpolation policy
 * is Log-Lin and Z-X policy interpolation policy is Log-Lin).
 */
struct LogLinLin : public TwoDInterpolationPolicyImpl<LogLin,LogLin>
{
  typedef LogLin ZYInterpPolicy;
  typedef LogLin ZXInterpPolicy;
  typedef LinLin YXInterpPolicy;

  //! The name of the policy
  static const std::string name();
};

/*! \brief Policy struct for interpolating 2D tables (Z-Y interpolation policy
 * is Log-Log and Z-X policy interpolation policy is Log-Lin).
 */
struct LogLogLin : public TwoDInterpolationPolicyImpl<LogLog,LogLin>
{
  typedef LogLog ZYInterpPolicy;
  typedef LogLin ZXInterpPolicy;
  typedef LogLin YXInterpPolicy;

  //! The name of the policy
  static const std::string name();
};

/*! \brief Policy struct for interpolating 2D tables (Z-Y interpolation policy
 * is Log-Lin and Z-X policy interpolation policy is Log-Log).
 */
struct LogLinLog : public TwoDInterpolationPolicyImpl<LogLin,LogLog>
{
  typedef LogLin ZYInterpPolicy;
  typedef LogLog ZXInterpPolicy;
  typedef LinLog YXInterpPolicy;

  //! The name of the policy
  static const std::string name();
};

/*! \brief Policy struct for interpolating 2D tables (Z-Y interpolation policy
 * is Log-Log and Z-X policy interpolation policy is Log-Log).
 */
struct LogLogLog : public TwoDInterpolationPolicyImpl<LogLog,LogLog>
{
  typedef LogLog ZYInterpPolicy;
  typedef LogLog ZXInterpPolicy;
  typedef LogLog YXInterpPolicy;

  //! The name of the policy
  static const std::string name();
};

/*! \brief Policy struct for interpolating 2D tables (Z-Y interpolation policy
 * is Lin-LogCos and Z-X policy interpolation policy is Lin-Lin).
 */
struct LinLogCosLin : public TwoDInterpolationPolicyImpl<LinLogCos,LinLin>
{
  typedef LinLogCos ZYInterpPolicy;
  typedef LinLin ZXInterpPolicy;
  typedef LogCosLin YXInterpPolicy;

  //! The name of the policy
  static const std::string name();
};

/*! \brief Policy struct for interpolating 2D tables (Z-Y interpolation policy
 * is Lin-NudgedLogCos and Z-X policy interpolation policy is Lin-Lin).
 */
struct LinNudgedLogCosLin : public TwoDInterpolationPolicyImpl<LinNudgedLogCos,LinLin>
{
  typedef LinNudgedLogCos ZYInterpPolicy;
  typedef LinLin ZXInterpPolicy;
  typedef NudgedLogCosLin YXInterpPolicy;

  //! The name of the policy
  static const std::string name();
};

/*! \brief Policy struct for interpolating 2D tables (Z-Y interpolation policy
 * is Lin-LogCos and Z-X policy interpolation policy is Lin-Log).
 */
struct LinLogCosLog : public TwoDInterpolationPolicyImpl<LinLogCos,LinLog>
{
  typedef LinLogCos ZYInterpPolicy;
  typedef LinLog ZXInterpPolicy;
  typedef LogCosLog YXInterpPolicy;

  //! The name of the policy
  static const std::string name();
};

/*! \brief Policy struct for interpolating 2D tables (Z-Y interpolation policy
 * is Lin-NudgedLogCos and Z-X policy interpolation policy is Lin-Log).
 */
struct LinNudgedLogCosLog : public TwoDInterpolationPolicyImpl<LinNudgedLogCos,LinLog>
{
  typedef LinNudgedLogCos ZYInterpPolicy;
  typedef LinLog ZXInterpPolicy;
  typedef NudgedLogCosLog YXInterpPolicy;

  //! The name of the policy
  static const std::string name();
};

/*! \brief Policy struct for interpolating 2D tables (Z-Y interpolation policy
 * is Log-LogCos and Z-X policy interpolation policy is Log-Lin).
 */
struct LogLogCosLin : public TwoDInterpolationPolicyImpl<LogLogCos,LogLin>
{
  typedef LogLogCos ZYInterpPolicy;
  typedef LogLin ZXInterpPolicy;
  typedef LogCosLin YXInterpPolicy;

  //! The name of the policy
  static const std::string name();
};

/*! \brief Policy struct for interpolating 2D tables (Z-Y interpolation policy
 * is Log-NudgedLogCos and Z-X policy interpolation policy is Log-Lin).
 */
struct LogNudgedLogCosLin : public TwoDInterpolationPolicyImpl<LogNudgedLogCos,LogLin>
{
  typedef LogNudgedLogCos ZYInterpPolicy;
  typedef LogLin ZXInterpPolicy;
  typedef NudgedLogCosLin YXInterpPolicy;

  //! The name of the policy
  static const std::string name();
};

/*! \brief Policy struct for interpolating 2D tables (Z-Y interpolation policy
 * is Log-LogCos and Z-X policy interpolation policy is Log-Log).
 */
struct LogLogCosLog : public TwoDInterpolationPolicyImpl<LogLogCos,LogLog>
{
  typedef LogLogCos ZYInterpPolicy;
  typedef LogLog ZXInterpPolicy;
  typedef LogCosLog YXInterpPolicy;

  //! The name of the policy
  static const std::string name();
};

/*! \brief Policy struct for interpolating 2D tables (Z-Y interpolation policy
 * is Log-NudgedLogCos and Z-X policy interpolation policy is Log-Log).
 */
struct LogNudgedLogCosLog : public TwoDInterpolationPolicyImpl<LogNudgedLogCos,LogLog>
{
  typedef LogNudgedLogCos ZYInterpPolicy;
  typedef LogLog ZXInterpPolicy;
  typedef NudgedLogCosLog YXInterpPolicy;

  //! The name of the policy
  static const std::string name();
};

TYPE_NAME_TRAITS_QUICK_DECL( LinLinLin );
TYPE_NAME_TRAITS_QUICK_DECL( LinLogLin );
TYPE_NAME_TRAITS_QUICK_DECL( LinLinLog );
TYPE_NAME_TRAITS_QUICK_DECL( LinLogLog );
TYPE_NAME_TRAITS_QUICK_DECL( LogLinLin );
TYPE_NAME_TRAITS_QUICK_DECL( LogLogLin );
TYPE_NAME_TRAITS_QUICK_DECL( LogLinLog );
TYPE_NAME_TRAITS_QUICK_DECL( LogLogLog );
// Log cosines with Nudge
TYPE_NAME_TRAITS_QUICK_DECL( LinNudgedLogCosLin );
TYPE_NAME_TRAITS_QUICK_DECL( LinNudgedLogCosLog );
TYPE_NAME_TRAITS_QUICK_DECL( LogNudgedLogCosLin );
TYPE_NAME_TRAITS_QUICK_DECL( LogNudgedLogCosLog );
// Log cosines without Nudge
TYPE_NAME_TRAITS_QUICK_DECL( LinLogCosLin );
TYPE_NAME_TRAITS_QUICK_DECL( LinLogCosLog );
TYPE_NAME_TRAITS_QUICK_DECL( LogLogCosLin );
TYPE_NAME_TRAITS_QUICK_DECL( LogLogCosLog );

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
