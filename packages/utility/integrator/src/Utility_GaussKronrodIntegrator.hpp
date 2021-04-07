//---------------------------------------------------------------------------//
//!
//! \file   Utility_GaussKronrodIntegrator.hpp
//! \author Luke Kersting
//! \brief  Gauss-Kronrod integrator
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_GAUSS_KRONROD_INTEGRATOR_HPP
#define UTILITY_GAUSS_KRONROD_INTEGRATOR_HPP

// std Includes
#include <queue>

// Boost Includes
#include <boost/numeric/odeint.hpp>

// FRENSIE Includes
#include "Utility_Vector.hpp"
#include "Utility_ArrayView.hpp"

namespace Utility{

template<typename T>
struct BinTraits
{
  T lower_limit;
  T upper_limit;
  T result;
  T error;

  bool operator <( const BinTraits<T>& bins ) const
  {
    return error < bins.error;
  }
};

template<typename T>
struct ExtrapolatedBinTraits
{
  T lower_limit;
  T upper_limit;
  T result;
  T error;
  int level;

  bool operator <( const ExtrapolatedBinTraits<T>& bins ) const
  {
    return error < bins.error;
  }
};

//! The Gauss-Kronrod integrator
template<typename T>
class GaussKronrodIntegrator
{

public:

typedef std::priority_queue<BinTraits<T>> BinQueue;
typedef std::vector<ExtrapolatedBinTraits<T>> BinArray;

  //! Constructor
  GaussKronrodIntegrator( const T relative_error_tol,
                          const T absolute_error_tol = 0.0,
                          const size_t subinterval_limit = 1000 );

  //! Destructor
  ~GaussKronrodIntegrator()
  { /* ... */ }

  //! Throw exception on dirty integration
  void throwExceptionOnDirtyIntegration();

  //! Check if an exception will be thrown on dirty integration
  bool isExceptionThrownOnDirtyIntegration() const;

  //! Warn on dirty integration (default)
  void warnOnDirtyIntegration();

  //! Use heuristic roundoff error estimator (default)
  void estimateRoundoff();

  //! Don't use heuristic roundoff error estimator
  void dontEstimateRoundoff();

  //! Set the realtive error tolerance
  void setRelativeErrorTolerance( const double relative_error_tol );

  //! Get the relative error tolerance
  double getRelativeErrorTolerance() const;

  //! Set the absolute error tolerance
  void setAbsoluteErrorTolerance( const double absolute_error_tol );

  //! Get the absolute error tolerance
  double getAbsoluteErrorTolerance() const;

/*
  //! Integrate the function
  template<typename Functor>
  void integrate( Functor& integrand,
		  T lower_limit,
		  T upper_limit,
		  T& result,
		  T& absolute_error,
		  size_t& number_of_function_eval ) const;
*/
  //! Integrate the function adaptively with BinQueue
  template<int Points, typename FunctorType = double, typename Functor>
  void integrateAdaptively( Functor& integrand,
			    T lower_limit,
			    T upper_limit,
			    T& result,
			    T& absolute_error ) const;

  //! Integrate the function adaptively with BinQueue
  template<int Points, typename FunctorType = double,
                       typename ParameterType = double, typename Functor>
  void integrateAdaptively( Functor& integrand,
                            ParameterType integrand_parameter,
			    T lower_limit,
			    T upper_limit,
			    T& result,
			    T& absolute_error ) const;
/*
  //! Integrate the function over a semi-infinite interval (+infinity)
  template<typename Functor>
  void integrateSemiInfiniteIntervalUpper( Functor& integrand,
					   T lower_limit,
					   T& result,
					   T& absolute_error ) const;

  //! Integrate the function over a semi-infinite interval (-infinity)
  template<typename Functor>
  void integrateSemiInfiniteIntervalLower( Functor& integrand,
					   T upper_limit,
					   T& result,
					   T& absolute_error ) const;

  //! Integrate the function over an infinite interval (-infinity,+infinity)
  template<typename Functor>
  void integrateInfiniteInterval( Functor& integrand,
				  T& result,
				  T& absolute_error ) const;

  //! Integrate a function with integrable singularities adaptively
  template<typename Functor>
  void integrateAdaptivelyWynnEpsilon( Functor& integrand,
				       T lower_limit,
				       T upper_limit,
				       T& result,
				       T& absolute_error ) const;
*/
  //! Integrate a function with known integrable singularities adaptively
  template<typename FunctorType = double, typename Functor>
  void integrateAdaptivelyWynnEpsilon(
			  Functor& integrand,
			  const Utility::ArrayView<T>& points_of_interest,
			  T& result,
			  T& absolute_error ) const;

  //! Integrate a function with known integrable singularities adaptively
  template<typename FunctorType = double, typename ParameterType = double, typename Functor>
  void integrateAdaptivelyWynnEpsilon(
			  Functor& integrand,
                          ParameterType integrand_parameter,
			  const Utility::ArrayView<T>& points_of_interest,
			  T& result,
			  T& absolute_error ) const;

  //! Integrate the function with point rule
  template<int Points, typename FunctorType = double, typename Functor>
  void integrateWithPointRule(
                Functor& integrand,
			    T lower_limit,
			    T upper_limit,
			    T& result,
			    T& absolute_error,
                T& result_abs,
                T& result_asc ) const;

  //! Integrate the function with point rule
  template<int Points, typename FunctorType = double,
                       typename ParameterType = double, typename Functor>
  void integrateWithPointRule(
                Functor& integrand,
                ParameterType integrand_parameter,
			    T lower_limit,
			    T upper_limit,
			    T& result,
			    T& absolute_error,
                T& result_abs,
                T& result_asc ) const;

protected:

  // Calculate the quadrature upper and lower integrand values at an abscissa
  template<typename FunctorType = double, typename Functor>
  void calculateQuadratureIntegrandValuesAtAbscissa(
    Functor& integrand,
    T abscissa,
    T half_length,
    T midpoint,
    T& integrand_value_lower,
    T& integrand_value_upper ) const;

  // Calculate the quadrature upper and lower integrand values at an abscissa
  template<typename FunctorType = double, typename ParameterType = double, typename Functor>
  void calculateQuadratureIntegrandValuesAtAbscissa(
    Functor& integrand,
    ParameterType functor_parameter,
    T abscissa,
    T half_length,
    T midpoint,
    T& integrand_value_lower,
    T& integrand_value_upper ) const;

  // Bisect and integrate the given bin interval
  template<int Points, typename FunctorType = double, typename Functor, typename Bin>
  void bisectAndIntegrateBinInterval(
    Functor& integrand,
    const Bin& bin,
    Bin& bin_1,
    Bin& bin_2,
    T& bin_1_asc,
    T& bin_2_asc ) const;

  // Bisect and integrate the given bin interval
  template<int Points, typename FunctorType = double, typename ParameterType = double, typename Functor, typename Bin>
  void bisectAndIntegrateBinInterval(
    Functor& integrand,
    ParameterType functor_parameter,
    const Bin& bin,
    Bin& bin_1,
    Bin& bin_2,
    T& bin_1_asc,
    T& bin_2_asc ) const;

  // Rescale absolute error from integration
  void rescaleAbsoluteError(
    T& absolute_error,
    T result_abs,
    T result_asc ) const;

  // Test if subinterval is too small
  template<int Points>
  bool subintervalTooSmall( T& lower_limit_1,
                                   T& lower_limit_2,
                                   T& upper_limit_2 ) const;

  // check the roundoff error
  void checkRoundoffError(
                       const BinTraits<T>& bin,
                       const BinTraits<T>& bin_1,
                       const BinTraits<T>& bin_2,
                       const T& bin_1_asc,
                       const T& bin_2_asc,
                       int& round_off_1,
                       int& round_off_2,
                       const int number_of_iterations ) const;

  // check the roundoff error
  void checkRoundoffError(
                       const ExtrapolatedBinTraits<T>& bin,
                       const ExtrapolatedBinTraits<T>& bin_1,
                       const ExtrapolatedBinTraits<T>& bin_2,
                       const T& bin_1_asc,
                       const T& bin_2_asc,
                       int& round_off_1,
                       int& round_off_2,
                       int& round_off_3,
                       const bool extrapolate,
                       const int number_of_iterations ) const;

  // Sort the bin order from highest to lowest error
  void sortBins(
        std::vector<int>& bin_order,
        BinArray& bin_array,
        const ExtrapolatedBinTraits<T>& bin_1,
        const ExtrapolatedBinTraits<T>& bin_2,
        const int& number_of_intervals,
        int& nr_max ) const;

  // get the Wynn Epsilon-Algorithm extrapolated value
  void getWynnEpsilonAlgorithmExtrapolation(
        std::vector<T>& bin_extrapolated_result,
        std::vector<T>& last_three_results,
        T& extrapolated_result,
        T& extrapolated_error,
        int& number_of_extrapolated_intervals,
        int& number_of_extrapolated_calls  ) const;

private:
  // The relative error tolerance
  T d_relative_error_tol;

  // The absolute error tolerance
  T d_absolute_error_tol;

  // The subinterval limit
  size_t d_subinterval_limit;

  // Throw exception on dirty integration
  bool d_throw_exceptions;

  // Estimate roundoff error and throw exceptions/warnings
  bool d_estimate_roundoff;

  // return epsilon numerical limit for type T
  T getLimitEpsilon() const;

  // return min numerical limit for type T
  T getLimitMin() const;

  // return max numerical limit for type T
  T getLimitMax() const;

  // return max of two variables of type T
  T getMax( T variable_1, T variable_2 ) const;
};

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_GaussKronrodIntegrator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_GAUSS_KRONROD_INTEGRATOR_HPP

//---------------------------------------------------------------------------//
// end Utility_GaussKronrodIntegrator.hpp
//---------------------------------------------------------------------------//
