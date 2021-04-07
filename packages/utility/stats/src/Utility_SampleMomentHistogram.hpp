//---------------------------------------------------------------------------//
//!
//! \file   Utility_SampleMomentHistogram.hpp
//! \author Alex Robinson
//! \brief  The sample moment histogram class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_SAMPLE_MOMENT_HISTOGRAM_HPP
#define UTILITY_SAMPLE_MOMENT_HISTOGRAM_HPP

// Std Lib Includes
#include <memory>

// Boost Includes
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/access.hpp>

// FRENSIE Includes
#include "Utility_Vector.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace Utility{

/*! The sample moment histogram
 * 
 * This class can be used to construct the distribution of sample
 * moments (as a histogram).
 */
template<typename T>
class SampleMomentHistogram
{

  // The unit type
  typedef typename Utility::QuantityTraits<T>::UnitType UnitType;

  // The inverse unit type
  typedef typename Utility::UnitTraits<UnitType>::InverseUnit InverseUnitType;

public:

  //! The histogram (raw) value type
  typedef typename Utility::QuantityTraits<T>::RawType HistogramValueType;

  //! The density value type
  typedef typename Utility::UnitTraits<InverseUnitType>::template GetQuantityType<HistogramValueType>::type DensityValueType;

  //! Default constructor
  SampleMomentHistogram();

  //! Constructor
  SampleMomentHistogram( const std::shared_ptr<const std::vector<T> >& bin_boundaries );

  //! Copy constructor
  SampleMomentHistogram( const SampleMomentHistogram& other_histogram );

  //! Assignment Operator
  SampleMomentHistogram& operator=( const SampleMomentHistogram& other_histogram );

  //! Destructor
  ~SampleMomentHistogram()
  { /* ... */ }

  //! Clear the histogram
  void clear();

  //! Reset the histogram
  void reset();

  //! Set the histogram bin boundaries
  void setBinBoundaries( const std::shared_ptr<const std::vector<T> >& bin_boundaries );

  //! Get the number of histogram bins (number of bin boundaries - 1)
  size_t size() const;

  //! Add a raw score
  void addRawScore( const T& raw_score );

  //! Merge histograms
  void mergeHistograms( const SampleMomentHistogram& histogram );

  //! Get the number of scores
  uint64_t getNumberOfScores() const;

  //! Get the bin boundaries
  const std::vector<T>& getBinBoundaries() const;

  //! Get the histogram values
  const std::vector<HistogramValueType>& getHistogramValues() const;

  //! Get the normalized histogram values
  void getNormalizedHistogramValues( std::vector<HistogramValueType>& values ) const;

  //! Get the density values
  void getDensityValues( std::vector<DensityValueType>& values ) const;

private:

  // Check that bin boundaries are the same
  static bool checkBinBoundariesEqual( const std::vector<T>& bin_boundaries,
                                       const std::vector<T>& other_bin_boundaries );

  // Save the collection data to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the collection data from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Make the boost::serialization::access class a friend
  friend class boost::serialization::access;

  // The bin boundaries
  std::shared_ptr<const std::vector<T> > d_bin_boundaries;

  // The histogram values
  std::vector<HistogramValueType> d_histogram_values;

  // The number of scores
  uint64_t d_number_of_scores;
};
  
} // end Utility namespace

BOOST_SERIALIZATION_CLASS1_VERSION( SampleMomentHistogram, Utility, 0 );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_SampleMomentHistogram_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_SAMPLE_MOMENT_HISTOGRAM_HPP

//---------------------------------------------------------------------------//
// end Utility_SampleMomentHistogram.hpp
//---------------------------------------------------------------------------//
