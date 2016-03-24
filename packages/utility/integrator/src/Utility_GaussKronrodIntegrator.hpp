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

// Trilinos Includes
#include <Teuchos_Array.hpp>

namespace Utility{

struct BinTraits
{
  double lower_limit;
  double upper_limit;
  long double result;
  double error;

  bool operator <( const BinTraits& bins ) const
  {
    return error < bins.error;
  }
};

struct ExtrpolatedBinTraits : BinTraits
{
  int level;

  bool operator <( const ExtrpolatedBinTraits& bins ) const
  {
    return error < bins.error;
  }
};

typedef std::priority_queue<BinTraits> BinQueue;
typedef Teuchos::Array<ExtrpolatedBinTraits> BinArray;

//! The Gauss-Kronrod integrator
class GaussKronrodIntegrator
{

public:

  //! Constructor
  GaussKronrodIntegrator( const double relative_error_tol,
                          const double absolute_error_tol = 0.0,
                          const size_t subinterval_limit = 1000 );

  //! Destructor
  ~GaussKronrodIntegrator();
/*
  //! Integrate the function
  template<typename Functor>
  void integrate( Functor& integrand, 
		  double lower_limit, 
		  double upper_limit,
		  double& result,
		  double& absolute_error,
		  size_t& number_of_function_evals ) const;
*/
  //! Integrate the function adaptively with BinQueue
  template<int Points, typename Functor>
  void integrateAdaptively( Functor& integrand,
			    double lower_limit,
			    double upper_limit,
			    double& result,
			    double& absolute_error ) const;

  //! Integrate the function with point rule
  template<int Points, typename Functor>
  void integrateWithPointRule( 
                Functor& integrand,
			    double lower_limit,
			    double upper_limit,
			    long double& result,
			    double& absolute_error,
                double& result_abs, 
                double& result_asc ) const;
/*
  //! Integrate the function over a semi-infinite interval (+infinity)
  template<typename Functor>
  void integrateSemiInfiniteIntervalUpper( Functor& integrand,
					   double lower_limit,
					   double& result,
					   double& absolute_error ) const;

  //! Integrate the function over a semi-infinite interval (-infinity)
  template<typename Functor>
  void integrateSemiInfiniteIntervalLower( Functor& integrand,
					   double upper_limit,
					   double& result,
					   double& absolute_error ) const;

  //! Integrate the function over an infinite interval (-infinity,+infinity)
  template<typename Functor>
  void integrateInfiniteInterval( Functor& integrand,
				  double& result,
				  double& absolute_error ) const;

  //! Integrate a function with integrable singularities adaptively
  template<typename Functor>
  void integrateAdaptivelyWynnEpsilon( Functor& integrand,
				       double lower_limit,
				       double upper_limit,
				       double& result,
				       double& absolute_error ) const;
*/
  //! Integrate a function with known integrable singularities adaptively
  template<typename Functor>
  void integrateAdaptivelyWynnEpsilon( 
			  Functor& integrand,
			  const Teuchos::ArrayView<double>& points_of_interest,
			  double& result,
			  double& absolute_error ) const;

protected:
  
  // Calculate the quadrature upper and lower integrand values at an abscissa
  template<typename Functor>
  void calculateQuadratureIntegrandValuesAtAbscissa( 
    Functor& integrand, 
    double abscissa,
    double half_length,
    double midpoint,
    double& integrand_value_lower,
    double& integrand_value_upper ) const;

  // Bisect and integrate the given bin interval
  template<int Points, typename Functor, typename Bin>
  void bisectAndIntegrateBinInterval( 
    Functor& integrand, 
    const Bin& bin,
    Bin& bin_1,
    Bin& bin_2,
    double& bin_1_asc,
    double& bin_2_asc ) const;

  // Rescale absolute error from integration
  void rescaleAbsoluteError( 
    double& absolute_error, 
    double result_abs, 
    double result_asc ) const;

  // Test if subinterval is too small
  template<int Points>
  bool subintervalTooSmall( double& lower_limit_1, 
                                   double& lower_limit_2, 
                                   double& upper_limit_2 ) const;

  // check the roundoff error 
  void checkRoundoffError( 
                       const BinTraits& bin, 
                       const BinTraits& bin_1, 
                       const BinTraits& bin_2,    
                       const double& bin_1_asc,
                       const double& bin_2_asc,
                       int& round_off_1,
                       int& round_off_2,
                       const int number_of_iterations ) const;

  // check the roundoff error 
  void checkRoundoffError( 
                       const ExtrpolatedBinTraits& bin, 
                       const ExtrpolatedBinTraits& bin_1, 
                       const ExtrpolatedBinTraits& bin_2,    
                       const double& bin_1_asc,
                       const double& bin_2_asc,
                       int& round_off_1,
                       int& round_off_2,
                       int& round_off_3,
                       const bool extrapolate, 
                       const int number_of_iterations ) const;
 
  // Sort the bin order from highest to lowest error 
  void sortBins( 
        Teuchos::Array<int>& bin_order,
        BinArray& bin_array, 
        const ExtrpolatedBinTraits& bin_1,
        const ExtrpolatedBinTraits& bin_2,
        const int& number_of_intervals,
        int& nr_max ) const;

  // get the Wynn Epsilon-Algoirithm extrapolated value
  void getWynnEpsilonAlgorithmExtrapolation( 
        Teuchos::Array<double>& bin_extrapolated_result, 
        Teuchos::Array<double>& last_three_results, 
        double& extrapolated_result, 
        double& extrapolated_error,  
        int& number_of_extrapolated_intervals,
        int& number_of_extrapolated_calls  ) const;

private:
  // The relative error tolerance
  double d_relative_error_tol;

  // The absolute error tolerance
  double d_absolute_error_tol;

  // The subinterval limit
  size_t d_subinterval_limit;
};

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_GaussKronrodIntegrator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_GUASS_KRONROD_INTEGRATOR_HPP

//---------------------------------------------------------------------------//
// end Utility_GaussKronrodIntegrator.hpp
//---------------------------------------------------------------------------//
