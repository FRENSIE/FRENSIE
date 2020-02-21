//---------------------------------------------------------------------------//
//!
//! \file   Utility_SampleMomentHistogram_def.hpp
//! \author Alex Robinson
//! \brief  The sample moment histogram class definition
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_SAMPLE_MOMENT_HISTOGRAM_DEF_HPP
#define UTILITY_SAMPLE_MOMENT_HISTOGRAM_DEF_HPP

// FRENSIE Includes
#include "Utility_SampleMomentHistogram.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{

// Default constructor
template<typename T>
SampleMomentHistogram<T>::SampleMomentHistogram()
  : d_bin_boundaries( std::make_shared<std::vector<T> >( std::vector<T>({Utility::QuantityTraits<T>::lowest(), Utility::QuantityTraits<T>::max()}) ) ),
    d_histogram_values( 1, 0.0 ),
    d_number_of_scores( 0 )
{ /* ... */ }

// Constructor
template<typename T>
SampleMomentHistogram<T>::SampleMomentHistogram(
                 const std::shared_ptr<const std::vector<T> >& bin_boundaries )
  : d_bin_boundaries( bin_boundaries ),
    d_histogram_values( bin_boundaries->size() > 1 ? bin_boundaries->size() - 1 : 1, 0.0 ),
    d_number_of_scores( 0 )
{
  // Make sure that the bin boundaries are valid
  TEST_FOR_EXCEPTION( bin_boundaries->size() <= 1,
                      std::runtime_error,
                      "There must be at least 2 bin boundaries!" );
  TEST_FOR_EXCEPTION( !Utility::Sort::isSortedAscending( bin_boundaries->begin(),
                                                         bin_boundaries->end(),
                                                         true ),
                      std::runtime_error,
                      "The bin boundaries must be sorted!" );
  TEST_FOR_EXCEPTION( bin_boundaries->front() ==
                      -Utility::QuantityTraits<T>::inf(),
                      std::runtime_error,
                      "A bin boundary of -Inf is not allowed!" );
  TEST_FOR_EXCEPTION( bin_boundaries->back() ==
                      Utility::QuantityTraits<T>::inf(),
                      std::runtime_error,
                      "A bin boundary of Inf is not allowed!" );
}

// Copy constructor
template<typename T>
SampleMomentHistogram<T>::SampleMomentHistogram( const SampleMomentHistogram<T>& other_histogram )
  : d_bin_boundaries( other_histogram.d_bin_boundaries ),
    d_histogram_values( other_histogram.d_histogram_values ),
    d_number_of_scores( other_histogram.d_number_of_scores )
{ /* ... */ }

// Assignment Operator
template<typename T>
SampleMomentHistogram<T>& SampleMomentHistogram<T>::operator=( const SampleMomentHistogram<T>& other_histogram )
{
  if( this != &other_histogram )
  {
    d_bin_boundaries = other_histogram.d_bin_boundaries;
    d_histogram_values = other_histogram.d_histogram_values;
    d_number_of_scores = other_histogram.d_number_of_scores;
  }

  return *this;
}

// Clear the histogram
template<typename T>
void SampleMomentHistogram<T>::clear()
{
  d_bin_boundaries = std::make_shared<std::vector<T> >( std::vector<T>({Utility::QuantityTraits<T>::lowest(), Utility::QuantityTraits<T>::max()}) );
  
  d_histogram_values.clear();
  d_histogram_values.resize( 1, 0.0 );

  d_number_of_scores = 0;
}

// Reset the histogram
template<typename T>
void SampleMomentHistogram<T>::reset()
{
  for( auto&& histogram_value : d_histogram_values )
    histogram_value = 0.0;

  d_number_of_scores = 0;
}

// Set the histogram bin boundaries
template<typename T>
void SampleMomentHistogram<T>::setBinBoundaries(
                 const std::shared_ptr<const std::vector<T> >& bin_boundaries )
{
  // Make sure that the bin boundaries are valid
  TEST_FOR_EXCEPTION( bin_boundaries->size() <= 1,
                      std::runtime_error,
                      "There must be at least 2 bin boundaries!" );
  TEST_FOR_EXCEPTION( !Utility::Sort::isSortedAscending( bin_boundaries->begin(),
                                                         bin_boundaries->end(),
                                                         true ),
                      std::runtime_error,
                      "The bin boundaries must be sorted!" );
  TEST_FOR_EXCEPTION( bin_boundaries->front() ==
                      -Utility::QuantityTraits<T>::inf(),
                      std::runtime_error,
                      "A bin boundary of -Inf is not allowed!" );
  TEST_FOR_EXCEPTION( bin_boundaries->back() ==
                      Utility::QuantityTraits<T>::inf(),
                      std::runtime_error,
                      "A bin boundary of Inf is not allowed!" );

  d_bin_boundaries = bin_boundaries;

  d_histogram_values.clear();
  d_histogram_values.resize( d_bin_boundaries->size() - 1, 0.0 );

  d_number_of_scores = 0;
}

// Get the number of histogram bins (number of bin boundaries - 1)
template<typename T>
size_t SampleMomentHistogram<T>::size() const
{
  return d_bin_boundaries->size() - 1;
}

// Add a raw score
template<typename T>
void SampleMomentHistogram<T>::addRawScore( const T& raw_score )
{
  if( raw_score >= d_bin_boundaries->front() &&
      raw_score < d_bin_boundaries->back() )
  {
    size_t bin_index = Search::binaryLowerBoundIndex( d_bin_boundaries->begin(),
                                                      d_bin_boundaries->end(),
                                                      raw_score );

    d_histogram_values[bin_index] += 1.0;
    ++d_number_of_scores;
  }
  else if( raw_score == d_bin_boundaries->back() )
  {
    d_histogram_values.back() += 1.0;
    ++d_number_of_scores;
  }
}

// Merge histograms
/*! \details The histograms must have the same bin boundaries. If 
 * Design by Contract is not enabled this method will not check if this
 * is true before conducting the merge.
 */
template<typename T>
void SampleMomentHistogram<T>::mergeHistograms( const SampleMomentHistogram<T>& histogram )
{
  // Make sure that the histograms have the same properties
  testPrecondition( this->checkBinBoundariesEqual( *d_bin_boundaries,
                                                   *histogram.d_bin_boundaries ) );

  for( size_t i = 0; i < d_histogram_values.size(); ++i )
    d_histogram_values[i] += histogram.d_histogram_values[i];

  d_number_of_scores += histogram.d_number_of_scores;
}

// Get the number of scores
template<typename T>
uint64_t SampleMomentHistogram<T>::getNumberOfScores() const
{
  return d_number_of_scores;
}

// Get the bin boundaries
template<typename T>
const std::vector<T>& SampleMomentHistogram<T>::getBinBoundaries() const
{
  return *d_bin_boundaries;
}

// Get the histogram values
template<typename T>
auto SampleMomentHistogram<T>::getHistogramValues() const -> const std::vector<HistogramValueType>&
{
  return d_histogram_values;
}

// Get the normalized histogram values
/* \details Returns the histogram values divided by the number of scores.
 */
template<typename T>
void SampleMomentHistogram<T>::getNormalizedHistogramValues(
                                std::vector<HistogramValueType>& values ) const
{
  values.resize( d_histogram_values.size() );
  
  for( size_t i = 0; i < d_histogram_values.size(); ++i )
    values[i] = d_histogram_values[i]/(double)d_number_of_scores;
}

// Get the density values
/*! \details Returns the normalized histogram values divided by the width of
 * each bin. If a bin has an infinite width the density value in that bin will
 * be 0.0. Check the histogram values to see if there are any scores in those
 * bins.
 */
template<typename T>
void SampleMomentHistogram<T>::getDensityValues(
                                  std::vector<DensityValueType>& values ) const
{
  values.resize( d_histogram_values.size() );

  for( size_t i = 0; i < d_histogram_values.size(); ++i )
  {
    const T bin_width =
      (*d_bin_boundaries)[i+1] - (*d_bin_boundaries)[i];

    if( bin_width < Utility::QuantityTraits<T>::inf() )
      values[i] = d_histogram_values[i]/((double)d_number_of_scores*bin_width);
    else
      values[i] = Utility::QuantityTraits<DensityValueType>::zero();
  }
}

// Check that bin boundaries are the same
template<typename T>
bool SampleMomentHistogram<T>::checkBinBoundariesEqual(
                                   const std::vector<T>& bin_boundaries,
                                   const std::vector<T>& other_bin_boundaries )
{
  if( bin_boundaries.size() != other_bin_boundaries.size() )
    return false;

  for( size_t i = 0; i < bin_boundaries.size(); ++i )
  {
    if( bin_boundaries[i] != other_bin_boundaries[i] )
      return false;
  }

  return true;
}

// Save the collection data to an archive
template<typename T>
template<typename Archive>
void SampleMomentHistogram<T>::save( Archive& ar, const unsigned version ) const
{
  ar & BOOST_SERIALIZATION_NVP( d_bin_boundaries );
  ar & BOOST_SERIALIZATION_NVP( d_histogram_values );
  ar & BOOST_SERIALIZATION_NVP( d_number_of_scores );
}

// Load the collection data from an archive
template<typename T>
template<typename Archive>
void SampleMomentHistogram<T>::load( Archive& ar, const unsigned version )
{
  ar & BOOST_SERIALIZATION_NVP( d_bin_boundaries );
  ar & BOOST_SERIALIZATION_NVP( d_histogram_values );
  ar & BOOST_SERIALIZATION_NVP( d_number_of_scores );
}
  
} // end Utility namespace

#if !defined SWIG

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( Utility::SampleMomentHistogram<double> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, SampleMomentHistogram<double> );

#endif // end !defined SWIG

#endif // end UTILITY_SAMPLE_MOMENT_HISTOGRAM_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_SampleMomentHistogram_def.hpp
//---------------------------------------------------------------------------//
