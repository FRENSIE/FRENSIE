//---------------------------------------------------------------------------//
//!
//! \file   Utility_SampleMoment_def.hpp
//! \author Alex Robinson
//! \brief  The sample moment class template definition
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_SAMPLE_MOMENT_DEF_HPP
#define UTILITY_SAMPLE_MOMENT_DEF_HPP

// FRENSIE Includes
#include "Utility_ExponentiationAlgorithms.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{

// Process a raw score
template<size_t N, typename T>
inline auto SampleMoment<N,T,typename std::enable_if<(N>0) && std::is_floating_point<typename QuantityTraits<T>::RawType>::value>::type>::processRawScore( const T& raw_score ) -> ValueType
{
  return Exponentiation::recursive<N>( raw_score );
}
  
// Default constructor
template<size_t N, typename T>
SampleMoment<N,T,typename std::enable_if<(N>0) && std::is_floating_point<typename QuantityTraits<T>::RawType>::value>::type>::SampleMoment()
  : d_current_score( QuantityTraits<ValueType>::zero() )
{ /* ... */ }
  
// Constructor
template<size_t N, typename T>
SampleMoment<N,T,typename std::enable_if<(N>0) && std::is_floating_point<typename QuantityTraits<T>::RawType>::value>::type>::SampleMoment( const ValueType& starting_score )
  : d_current_score( starting_score )
{ /* ... */ }

// Copy constructor
template<size_t N, typename T>
SampleMoment<N,T,typename std::enable_if<(N>0) && std::is_floating_point<typename QuantityTraits<T>::RawType>::value>::type>::SampleMoment( const SampleMoment& other_moment )
  : d_current_score( other_moment.d_current_score )
{ /* ... */ }

// Assignment operator
template<size_t N, typename T>
auto SampleMoment<N,T,typename std::enable_if<(N>0) && std::is_floating_point<typename QuantityTraits<T>::RawType>::value>::type>::operator=(
                            const SampleMoment& other_moment ) -> SampleMoment&
{
  if( this != &other_moment )
    d_current_score = other_moment.d_current_score;

  return *this;
}

// Return the current score
template<size_t N, typename T>
auto SampleMoment<N,T,typename std::enable_if<(N>0) && std::is_floating_point<typename QuantityTraits<T>::RawType>::value>::type>::getCurrentScore() const -> const ValueType&
{
  return d_current_score;
}

// Return the value of the moment given the number of samples
template<size_t N, typename T>
auto SampleMoment<N,T,typename std::enable_if<(N>0) && std::is_floating_point<typename QuantityTraits<T>::RawType>::value>::type>::get( const size_t number_of_samples ) const -> ValueType
{
  // Make sure that there is at least one sample
  testPrecondition( number_of_samples > 0 );

  return d_current_score/(typename QuantityTraits<T>::RawType)number_of_samples;
}

// Add a raw score
template<size_t N, typename T>
void SampleMoment<N,T,typename std::enable_if<(N>0) && std::is_floating_point<typename QuantityTraits<T>::RawType>::value>::type>::addRawScore( const T& raw_score )
{
  d_current_score += this->processRawScore( raw_score );
}

// Add a processed score (raw_score^N)
template<size_t N, typename T>
void SampleMoment<N,T,typename std::enable_if<(N>0) && std::is_floating_point<typename QuantityTraits<T>::RawType>::value>::type>::addProcessedScore( const ValueType& processed_score )
{
  d_current_score += processed_score;
}

// Calculate the mean
template<typename T>
inline T calculateMean( const SampleMoment<1,T>& first_moment,
                        const size_t number_of_samples )
{
  // Make sure that there is at least one sample
  testPrecondition( number_of_samples > 0 );
  
  return first_moment.get( number_of_samples );
}

// Calculate the variance of the population
template<typename T>
inline typename QuantityTraits<T>::template GetQuantityToPowerType<2>::type
calculateVariance( const SampleMoment<1,T>& first_moment,
                   const SampleMoment<2,T>& second_moment,
                   const size_t number_of_samples )
{
  // Make sure that there is at least one sample
  testPrecondition( number_of_samples > 1 );

  typedef typename QuantityTraits<typename SampleMoment<2,T>::ValueType>::RawType RawReturnType;

  return (second_moment.getCurrentScore() -
          first_moment.getCurrentScore()*first_moment.getCurrentScore()/
          (RawReturnType)number_of_samples)/
    (RawReturnType)(number_of_samples-1);
}

// Calculate the standard deviation of the population
template<typename T>
inline T calculateStdDev( const SampleMoment<1,T>& first_moment,
                          const SampleMoment<2,T>& second_moment,
                          const size_t number_of_samples )
{
  // Make sure that there is at least one sample
  testPrecondition( number_of_samples > 1 );

  return Utility::sqrt( Utility::calculateVariance( first_moment,
                                                    second_moment,
                                                    number_of_samples ) );
}

// Calculate the variance of the mean
template<typename T>
inline typename QuantityTraits<T>::template GetQuantityToPowerType<2>::type
calculateVarianceOfMean( const SampleMoment<1,T>& first_moment,
                         const SampleMoment<2,T>& second_moment,
                         const size_t number_of_samples )
{
  // Make sure that there is at least one sample
  testPrecondition( number_of_samples > 1 );

  typedef typename QuantityTraits<typename SampleMoment<2,T>::ValueType>::RawType RawReturnType;

  return calculateVariance( first_moment, second_moment, number_of_samples )/
    (RawReturnType)number_of_samples;
}

// Calculate the standard deviation of the mean
template<typename T>
inline T calculateStdDevOfMean( const SampleMoment<1,T>& first_moment,
                                const SampleMoment<2,T>& second_moment,
                                const size_t number_of_samples )
{
  // Make sure that there is at least one sample
  testPrecondition( number_of_samples > 1 );

  return Utility::sqrt( Utility::calculateVarianceOfMean( first_moment,
                                                          second_moment,
                                                          number_of_samples ) );
}

// Calculate the relative error
template<typename T>
typename QuantityTraits<T>::RawType
calculateRelativeError( const SampleMoment<1,T>& first_moment,
                        const SampleMoment<2,T>& second_moment,
                        const size_t number_of_samples )
{
  // Make sure that there is at least one sample
  testPrecondition( number_of_samples > 0 );

  typename QuantityTraits<T>::RawType relative_error;

  if( first_moment.getCurrentScore() > QuantityTraits<T>::zero() )
  {
    typename QuantityTraits<T>::RawType argument =
      second_moment.getCurrentScore()/
      (first_moment.getCurrentScore()*first_moment.getCurrentScore()) -
      1.0/number_of_samples;

    if( number_of_samples > 1 )
      argument *= number_of_samples/(number_of_samples-1.0);
    
    if( argument < 0.0 )
      relative_error = 0.0;
    else
      relative_error = std::sqrt( argument );
  }
  else
    relative_error = 0.0;

  return relative_error;
}

// Calculate the relative variance of the variance (VOV)
/*! \details The relative variance of the variance is a measure of the
 * relative statistical uncertainty in the relative error 
 * (i.e. S^2(S^2_xbar)/S^4_xbar). This measure can be useful when constructing
 * confidence intervals because it can indicate if the population variance
 * (S) is a good approximation of the true variance (sigma), which is a 
 * requirement of the Central Limit Theorem. 
 */
template<typename T>
typename QuantityTraits<T>::RawType
calculateRelativeVOV( const SampleMoment<1,T>& first_moment,
                      const SampleMoment<2,T>& second_moment,
                      const SampleMoment<3,T>& third_moment,
                      const SampleMoment<4,T>& fourth_moment,
                      const size_t number_of_samples )
{
  typename SampleMoment<2,T>::ValueType first_moment_score_squared =
    first_moment.getCurrentScore()*first_moment.getCurrentScore();

  const typename QuantityTraits<T>::RawType num_samples_squared =
    number_of_samples*number_of_samples;
  const typename QuantityTraits<T>::RawType num_samples_cubed =
    num_samples_squared*number_of_samples;

  typename SampleMoment<4,T>::ValueType vov_numerator =
    fourth_moment.getCurrentScore() -
    4.*first_moment.getCurrentScore()*third_moment.getCurrentScore()/
    (typename QuantityTraits<T>::RawType)number_of_samples +
    8.*second_moment.getCurrentScore()*first_moment_score_squared/
    num_samples_squared -
    4.*first_moment_score_squared*first_moment_score_squared/
    num_samples_cubed -
    second_moment.getCurrentScore()*second_moment.getCurrentScore()/
    (typename QuantityTraits<T>::RawType)number_of_samples;

  typename SampleMoment<2,T>::ValueType vov_denominator_root =
    second_moment.getCurrentScore() -
    first_moment_score_squared/
    (typename QuantityTraits<T>::RawType)number_of_samples;
  
  typename SampleMoment<4,T>::ValueType vov_denominator =
    vov_denominator_root*vov_denominator_root;

  typename QuantityTraits<T>::RawType vov;

  if( vov_denominator == QuantityTraits<typename SampleMoment<4,T>::ValueType>::zero() )
    vov = 0.0;
  else
    vov = vov_numerator/vov_denominator;

  return vov;
}

// Calculate the figure of merit (FOM)
/*! \details This is a measure commonly used in Monte Carlo calculations that
 * can be used to determine the efficiency of the calculation.
 */
template<typename T>
inline typename std::enable_if<std::is_floating_point<T>::value,T>::type
calculateFOM( const T relative_error, const T time )
{
  // Make sure that the time is valid
  testPrecondition( time > 0.0 );

  T fom;

  if( relative_error > 0.0 )
    fom = 1.0/(relative_error*relative_error*time);
  else
    fom = 0.0;

  return fom;
}

// Explicit instantiation (extern declaration)
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( SampleMoment<1,double> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( SampleMoment<2,double> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( SampleMoment<3,double> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( SampleMoment<4,double> );

EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( double calculateMean( const SampleMoment<1,double>&, const size_t ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( double calculateVariance( const SampleMoment<1,double>&, const SampleMoment<2,double>&, const size_t ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( double calculateStdDev( const SampleMoment<1,double>&, const SampleMoment<2,double>&, const size_t ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( double calculateVarianceOfMean( const SampleMoment<1,double>&, const SampleMoment<2,double>&, const size_t ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( double calculateStdDevOfMean( const SampleMoment<1,double>&, const SampleMoment<2,double>&, const size_t ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( double calculateRelativeError( const SampleMoment<1,double>&, const SampleMoment<2,double>&, const size_t ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( double calculateRelativeVOV( const SampleMoment<1,double>&, const SampleMoment<2,double>&, const SampleMoment<3,double>&, const SampleMoment<4,double>&, const size_t ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( double calculateFOM( const double, const double ) );
  
} // end Utility namespace

#endif // end UTILITY_SAMPLE_MOMENT_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_SampleMoment_def.hpp
//---------------------------------------------------------------------------//
