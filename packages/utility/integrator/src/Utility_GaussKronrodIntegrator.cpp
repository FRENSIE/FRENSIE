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

  TEST_FOR_EXCEPTION( 
    d_absolute_error_tol <= 0 && 
    (d_relative_error_tol < 50 * std::numeric_limits<double>::epsilon() ||
    d_relative_error_tol < 0.5e-28),
    Utility::IntegratorException,
    "tolerance cannot be acheived with given relative_error_tol and absolute_error_tol" );

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

// Sort the bin order from highest to lowest error 
//! \details The error list will be correctly sorted except bin_1 and bin_2
void GaussKronrodIntegrator::sortBins( 
        Teuchos::Array<int>& bin_order,
        BinArray& bin_array, 
        const ExtrpolatedBinTraits& bin_1,
        const ExtrpolatedBinTraits& bin_2,
        const int& number_of_intervals,
        int& nr_max ) const
{
  testPrecondition( bin_order.size() == number_of_intervals );

  double larger_error;
  double smaller_error;
  
  int bin_with_larger_error = bin_order[nr_max];

  // append new intervals to bin_array
  if ( bin_1.error <= bin_2.error )
  {
    bin_array[bin_with_larger_error] = bin_2;
    bin_array[number_of_intervals] = bin_1;

    larger_error = bin_2.error;
    smaller_error = bin_1.error;
  }
  else
  {
    bin_array[bin_with_larger_error] = bin_1;
    bin_array[number_of_intervals] = bin_2;

    larger_error = bin_1.error;
    smaller_error = bin_2.error;
  }

  // remove old interval from list
  bin_order.remove( nr_max ); 

  /*
   *  This part of the routine is only executed if, due to a
   *  difficult integrand, subdivision increased the error
   *  estimate. in the normal case the insert procedure should
   *  start after the nr_max-th largest error estimate.
   */
  int original_nr_max = nr_max;
  while ( nr_max > 0 && larger_error > bin_array[bin_order[nr_max-1]].error )
  {
    nr_max--; //reduce nr_max if the bin above it has larger error
  }

  
  int start_bin;
  if ( original_nr_max > nr_max )
  {
    // start insert of the bin_with_larger_error at the reduced nr_max
    start_bin = nr_max;
  }
  else
  {
    // start insert of the bin_with_larger_error right after the bin_with_larger_error
    start_bin = original_nr_max;
  }

  /*
   *  Compute the number of elements in the list to be maintained
   *  in descending order. This number depends on the number of
   *  subdivisions still allowed.
   */
  Teuchos::Array<int>::iterator max_bin;
  if ( (d_subinterval_limit/2+2) < bin_order.size()-1 )
    max_bin = bin_order.begin() + ( d_subinterval_limit - bin_order.size() );
  else
    max_bin = bin_order.end();

  Teuchos::Array<int>::iterator large_bin = bin_order.begin()+start_bin;
  while ( large_bin != max_bin && larger_error < bin_array[*large_bin].error )
  {
    large_bin++;
  }

  bin_order.insert( large_bin, bin_with_larger_error );
  max_bin;

  //  Insert smaller_bin_error by traversing the list bottom-up.
  Teuchos::Array<int>::iterator small_bin = max_bin;
  while ( small_bin != large_bin && 
          bin_array[bin_order[*small_bin]].error < smaller_error )
  {
    small_bin--;
  }
  bin_order.insert( small_bin+1, number_of_intervals );
};


// get the Wynn Epsilon-Algoirithm extrapolated value
void GaussKronrodIntegrator::getWynnEpsilonAlgorithmExtrapolation( 
        Teuchos::Array<double>& bin_extrapolated_result, 
        Teuchos::Array<double>& last_three_results, 
        double& extrapolated_result, 
        double& extrapolated_error,  
        int& number_of_extrapolated_intervals,
        int& number_of_extrapolated_calls  ) const
{
  testPrecondition( number_of_extrapolated_calls >= 0 );
  testPrecondition( number_of_extrapolated_intervals > 1 );
  testPrecondition( last_three_results.size() == 3 );
  testPrecondition( bin_extrapolated_result.size() == 52 );
 
  // update the number of extrapolated calls
  number_of_extrapolated_calls++;

  extrapolated_error = std::numeric_limits<double>::max();
  extrapolated_result = bin_extrapolated_result[number_of_extrapolated_intervals];

  if ( number_of_extrapolated_intervals < 2 )
  {
    extrapolated_error = std::max( extrapolated_error, 
        0.5*std::numeric_limits<double>::epsilon()*fabs(extrapolated_result) );
    return;
  }

  int extrapolated_interval_limit = 50;

  bin_extrapolated_result[number_of_extrapolated_intervals+2] = 
    bin_extrapolated_result[number_of_extrapolated_intervals];

  int new_element = number_of_extrapolated_intervals/2;

  bin_extrapolated_result[number_of_extrapolated_intervals] = 
     std::numeric_limits<double>::max();

  int original_number = number_of_extrapolated_intervals;
  int k1 = number_of_extrapolated_intervals;

  for ( int i = 0; i < new_element; i++ )
  {
    int k2 = k1-1;
    int k3 = k1-2;

    double result = bin_extrapolated_result[k1+2];
    double e0 = bin_extrapolated_result[k3];
    double e1 = bin_extrapolated_result[k2];
    double e2 = result;

    // Get error and tolerance estimate between e2 and e1
    double delta2 = e2 - e1;
    double error2 = fabs(delta2);
    double tolerance2 = std::max( fabs(e2), fabs(e1) )*
            std::numeric_limits<double>::epsilon();

    // Get error and tolerance estimate between e1 and e0
    double delta3 = e1 - e0;
    double error3 = fabs(delta3);
    double tolerance3 = std::max( fabs(e1), fabs(e0) )*
            std::numeric_limits<double>::epsilon();

    // If e0, e1 and e2 are equal to within machine accuracy, convergence is assumed.
    if ( error2 <= tolerance2 && error3 <= tolerance3 )
    {
      extrapolated_result = result;
      extrapolated_error = error2+error3;
      extrapolated_error = std::max( extrapolated_error, 
          0.5*std::numeric_limits<double>::epsilon()*fabs(extrapolated_error) );
     return;
    }

    double e3 = bin_extrapolated_result[k1];
    bin_extrapolated_result[k1] = e1;

    // Get error and tolerance estimate between e1 and e3
    double delta1 = e1 - e3;
    double error1 = fabs(delta1);
    double tolerance1 = std::max( fabs(e1), fabs(e3) )*
            std::numeric_limits<double>::epsilon();
    
    /* If two elements are very close to each other, omit a part of the table 
     * by adjusting the value of number_of_extrapolated_intervals.
     */
    if ( error1 <= tolerance1 || error2 <= tolerance2 || error3 <= tolerance3 )
    {
      number_of_extrapolated_intervals = 2*i;
      break;
    }

    double ss = (1.0/delta1 + 1.0/delta2) - 1.0/delta3;

    /* Test to detect irregular behavior in the table, and eventually omit a
     * part of the table adjusting the value of number_of_extrapolated_intervals.
     */
    if ( fabs ( ss*e1 ) <= 1.0E-04 ) 
    {
      number_of_extrapolated_intervals = 2*i;
      break;
    }

    /* Compute a new element and eventually adjust the value of
     * result. 
     */
    result = e1 + 1.0/ss;
    bin_extrapolated_result[k1] = result;
    k1 -= 2;

    double error = error2 + fabs(result - e2) + error3;

    if ( error <= extrapolated_error )
    {
      extrapolated_error = error;
      extrapolated_result = result;
    }
  }

  // Shift the table

  if ( number_of_extrapolated_intervals == extrapolated_interval_limit )
    number_of_extrapolated_intervals = 2*(extrapolated_interval_limit/2);

  int ib;

  if ( original_number % 2 == 1 )
  {
    ib = 1;
  }
  else
  {
    ib = 0;
  }

  int ie = new_element + 1;

  for ( int i = 0; i < ie; i++ )
  {
    bin_extrapolated_result[ib] = bin_extrapolated_result[ib+2];
    ib += 2;
  }

  if ( original_number != number_of_extrapolated_intervals ) 
  {
    for ( int i = 0; i < number_of_extrapolated_intervals; i++ )
    {
      bin_extrapolated_result[i]= 
        bin_extrapolated_result[original_number - number_of_extrapolated_intervals + i];
    }
  }
  
  if ( number_of_extrapolated_calls < 4 )
  {
    last_three_results[number_of_extrapolated_calls-1] = extrapolated_result;
    extrapolated_error = std::numeric_limits<double>::max();
  }
  else
  {
    extrapolated_error = 
      fabs( extrapolated_result - last_three_results[2] ) +
      fabs( extrapolated_result - last_three_results[1] ) +
      fabs( extrapolated_result - last_three_results[0] );

    last_three_results[0] = last_three_results[1];
    last_three_results[1] = last_three_results[2];
    last_three_results[2] = extrapolated_result;
  }

  extrapolated_error = std::max ( 
    extrapolated_error,
    0.5*std::numeric_limits<double>::epsilon()*fabs( extrapolated_result ) );

  return;
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


// check the roundoff error 
void GaussKronrodIntegrator::checkRoundoffError( 
                       const ExtrpolatedBinTraits& bin, 
                       const ExtrpolatedBinTraits& bin_1, 
                       const ExtrpolatedBinTraits& bin_2,    
                       const double& bin_1_asc,
                       const double& bin_2_asc,
                       int& round_off_1,
                       int& round_off_2,
                       int& round_off_3,
                       const bool extrapolate, 
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
         if ( extrapolate ) 
           round_off_2++;
        else
           round_off_1++; 
       }
       if ( number_of_iterations >= 10 && error_12 > bin.error )
       {
          round_off_3++;
       }
     }

    TEST_FOR_EXCEPTION( 10 <= round_off_1 + round_off_2 || 20 <= round_off_3, 
                        Utility::IntegratorException,
                        "Roundoff error prevented tolerance from being achieved" );

    TEST_FOR_EXCEPTION( 5 <= round_off_2, 
                        Utility::IntegratorException,
                        "Extremely bad integrand behavior occurs at some points "
                        "of the integration interval" );
};

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_GaussKronrodIntegrator.cpp
//---------------------------------------------------------------------------//
