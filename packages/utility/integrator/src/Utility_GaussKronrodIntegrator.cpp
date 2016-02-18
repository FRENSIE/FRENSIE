//---------------------------------------------------------------------------//
//!
//! \file   Utility_GaussKronrodIntegrator.cpp
//! \author Luke Kersting
//! \brief  Gauss-Kronrod integrator
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_GaussKronrodIntegrator.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Initialize static member data

// Constructor
GaussKronrodIntegrator::GaussKronrodIntegrator( 
    const double relative_error_tol,
    const double absolute_error_tol,
    const size_t subinterval_limit )
  : d_relative_error_tol( relative_error_tol ),
    d_absolute_error_tol( absolute_error_tol ),
    d_subinterval_limit( subinterval_limit ) 
{
  // Make sure the error tolerances are valid
  testPrecondition( relative_error_tol >= 0.0 );
  testPrecondition( absolute_error_tol >= 0.0 );
  // Make sure the subinterval limit is valid
  testPrecondition( subinterval_limit > 0 );

}

// Destructor
GaussKronrodIntegrator::~GaussKronrodIntegrator()
{ /* ... */ }

// Rescale absolute error from integration
void GaussKronrodIntegrator::rescaleAbsoluteError( 
    double& absolute_error, 
    double result_abs, 
    double result_asc ) const
{
  if ( result_asc != 0 && absolute_error != 0 )
    {
      double scale = 200.0 * absolute_error/result_asc;

      if ( scale < 1.0 )
      {
        absolute_error = result_asc * pow( scale, 1.5 );
      }  
      else
      {    
      absolute_error = result_asc;
      }  
    };

  if ( result_abs > std::numeric_limits<double>::min() / ( 50.0 *
                    std::numeric_limits<double>::epsilon() ) )
    {
      double min_error = 50.0*std::numeric_limits<double>::epsilon() * result_abs;

      if ( min_error > absolute_error ) 
        {
          absolute_error = min_error;
        }
    };
};
/*
// Update the integral results and errors
inline void GaussKronrodIntegrator::updateIntegral( 
        Teuchos::Array<double>& bin_lower_limit, 
        Teuchos::Array<double>& bin_upper_limit, 
        Teuchos::Array<double>& bin_result, 
        Teuchos::Array<double>& bin_error,
        double& lower_limit_1, 
        double& upper_limit_1,
        double& area_1, 
        double& error_1,
        double& lower_limit_2,
        double& upper_limit_2, 
        double& area_2, 
        double& error_2,
        int& last,
        int& bin_with_max_error ) const
*/
// Update the integral results and errors
void GaussKronrodIntegrator::updateIntegral( 
    Teuchos::Array<double>& bin_lower_limit, 
    Teuchos::Array<double>& bin_upper_limit, 
    Teuchos::Array<double>& bin_result, 
    Teuchos::Array<double>& bin_error,
    double& lower_limit_1, 
    double& upper_limit_1,
    double& area_1, 
    double& error_1,
    double& lower_limit_2,
    double& upper_limit_2, 
    double& area_2, 
    double& error_2,
    int& last,
    int& bin_with_max_error ) const
{
    if ( error_2 <= error_1 )
    {
      bin_lower_limit[last] = lower_limit_2;
      bin_upper_limit[last] = upper_limit_2;
      bin_error[last] = error_2;
      bin_result[last] = area_2;

      // Lower limit already set as lower_limit_1
      bin_upper_limit[bin_with_max_error] = upper_limit_1;
      bin_error[bin_with_max_error] = error_1;
      bin_result[bin_with_max_error] = area_1;
    }
    else
    {
      bin_lower_limit[last] = lower_limit_1;
      bin_upper_limit[last] = upper_limit_1;
      bin_error[last] = error_1;
      bin_result[last] = area_1;

      bin_lower_limit[bin_with_max_error] = lower_limit_2;
      // Upper limit already set as upper_limit_2
      bin_error[bin_with_max_error] = error_2;
      bin_result[bin_with_max_error] = area_2;
    }
};

// Sort the bin order from highest to lowest error 
/*! \details The error list will be correctly sorted with the exception
 *  of two bins: bin_with_larger_error & bin_with_smaller_error.
 *  The bin_with_larger_error is located near the fron of the order list.
 *  The bin_with_smaller_error is at the end of the used list entries.
 */
void GaussKronrodIntegrator::sortErrorList( 
        Teuchos::Array<double>& bin_error,
        Teuchos::Array<double>& bin_order, 
        double& maximum_bin_error, 
        int& bin_with_larger_error,
        int bin_with_smaller_error, 
        int nr_max ) const
{

  //  Check whether the list contains more than two error estimates.
  if ( bin_with_smaller_error < 2 )
  {
    bin_order[0] = 0;
    bin_order[1] = 1;
  }
  else
  {
    double larger_bin_error = bin_error[bin_with_larger_error];
    double smaller_bin_error = bin_error[bin_with_smaller_error];

   /*
    *  This part of the routine is only executed if, due to a
    *  difficult integrand, subdivision increased the error
    *  estimate. in the normal case the insert procedure should
    *  start after the nr_max-th largest error estimate.
    */
    while ( nr_max > 0 && larger_bin_error > bin_error[ bin_order[nr_max-1] ] )
    {
      bin_order[nr_max] = bin_order[nr_max-1];
      nr_max--; 
    }

    /*
     *  Compute the number of elements in the list to be maintained
     *  in descending order. This number depends on the number of
     *  subdivisions still allowed.
     */
    int max_bin;
    if ( (d_subinterval_limit/2+2) < bin_with_smaller_error )
      max_bin = d_subinterval_limit + 1 - bin_with_smaller_error;
    else
      max_bin = bin_with_smaller_error;

    /*
     *  Insert larger_bin_error by traversing the list top-down, starting
     *  comparison from the element bin_error[ bin_order[nr_max+1] ].
     */
    int large_bin = nr_max+1;
    while ( large_bin < max_bin && larger_bin_error < bin_error[ bin_order[large_bin] ] )
    {
      bin_order[large_bin-1] = bin_order[large_bin];
      large_bin++;
    }
    bin_order[large_bin-1] = bin_with_larger_error;

    //  Insert smaller_bin_error by traversing the list bottom-up.
    int small_bin = max_bin-1;
    while ( small_bin > large_bin -2 && 
            bin_error[ bin_order[small_bin] ] < smaller_bin_error )
    {
      bin_order[small_bin+1] = bin_order[small_bin];
      small_bin--;
    }
    bin_order[small_bin+1] = bin_with_smaller_error;
  }

  // Set bin_with_larger_error to the bin with maximum error.
  bin_with_larger_error = bin_order[nr_max];

  // Set maximum_bin_error.
  maximum_bin_error = bin_error[bin_with_larger_error];
};

// get the Wynn Epsilon-Algoirithm extrapolated value
void GaussKronrodIntegrator::getWynnEpsilonAlgorithmExtrapolation( 
        Teuchos::Array<double>& bin_extrapolated_result, 
        Teuchos::Array<double>& last_three_results, 
        double& extrapolated_result, 
        double& extrapolated_error,  
        int& number_of_extrapolations,
        int& last_extrapolated_bin  ) const
{

};  

// check the roundoff error 
void GaussKronrodIntegrator::checkRoundoffError( 
                       const BinTraits& bin, 
                       const BinTraits& bin_1, 
                       const BinTraits& bin_2,    
                       const double& bin_1_asc,
                       const double& bin_2_asc,
                       int& round_off_1,
                       int& round_off_2,
                       const int number_of_iterations ) const
{
    if (bin_1_asc != bin_1.error && bin_2_asc != bin_2.error)
    {
       double area_12 = bin_1.result + bin_2.result;
       double error_12 = bin_1.error + bin_2.error;
       double delta = bin.result - area_12;

       if ( fabs (delta) <= 1.0e-5 * fabs (area_12) && 
            error_12 >= 0.99 * bin.error )
       {
         round_off_1++;
       }
       if ( number_of_iterations >= 10 && error_12 > bin.error )
       {
          round_off_2++;
       }
     }

    TEST_FOR_EXCEPTION( round_off_1 >= 6 || round_off_2 >= 20, 
                        Utility::IntegratorException,
                        "Roundoff error prevented tolerance from being achieved" );
};

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_GaussKronrodIntegrator.cpp
//---------------------------------------------------------------------------//
