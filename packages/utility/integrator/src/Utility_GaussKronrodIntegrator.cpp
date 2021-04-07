//---------------------------------------------------------------------------//
//!
//! \file   Utility_GaussKronrodIntegrator.cpp
//! \author Alex Robinson
//! \brief  Gauss-Kronrod integrator explicit instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_GaussKronrodIntegrator.hpp"

namespace Utility{

EXPLICIT_TEMPLATE_CLASS_INST( GaussKronrodIntegrator<double> );
EXPLICIT_TEMPLATE_CLASS_INST( GaussKronrodIntegrator<long double> );
  
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

    /*TEST_FOR_EXCEPTION( round_off_1 >= 6 || round_off_2 >= 20, 
                        Utility::IntegratorException,
                        "Roundoff error prevented tolerance from being achieved" );*/
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

    /*TEST_FOR_EXCEPTION( 10 <= round_off_1 + round_off_2 || 20 <= round_off_3, 
                        Utility::IntegratorException,
                        "Roundoff error prevented tolerance from being achieved" );

    TEST_FOR_EXCEPTION( 5 <= round_off_2, 
                        Utility::IntegratorException,
                        "Extremely bad integrand behavior occurs at some points "
                        "of the integration interval" );*/
};

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_GaussKronrodIntegrator.cpp
//---------------------------------------------------------------------------//
