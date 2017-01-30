//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_UnorderedEstimatorDimensionDiscretization.hpp
//! \author Alex Robinson
//! \brief  Unordered estimator dimension discretization declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_UNORDERED_ESTIMATOR_DIMENSION_DISCRETIZATION_HPP
#define MONTE_CARLO_UNORDERED_ESTIMATOR_DIMENSION_DISCRETIZATION_HPP

// Std Lib Includes
#include <set>
#include <unordered_set>
#include <vector>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_EstimatorDimensionDiscretization.hpp"

namespace MonteCarlo{

//! The unordered estimator dimension discretization class
template<typename T>
class UnorderedEstimatorDimensionDiscretization : public EstimatorDimensionDiscretization
{

public:

  //! Typedef for the bin set
  typedef std::set<T> BinSet;
  
  //! Typedef for the bin set array
  typedef std::vector<BinSet> BinSetArray;

  //! Constructor
  UnorderedEstimatorDimensionDiscretization(
                                   const ObserverPhaseSpaceDimension dimension,
                                   const BinSetArray& dimension_bins );

  //! Destructor
  virtual ~UnorderedEstimatorDimensionDiscretization()
  { /* ... */ }

  //! Return the number of bins in the discretization
  size_t getNumberOfBins() const override;

  //! Print the boundaries of a bin
  void printBoundariesOfBin( std::ostream& os,
                             const size_t bin_index ) const override;

  //! Print the dimension discretization
  void print( std::ostream& os ) const override;

protected:

  //! Check if the value is contained in the discretization
  bool isValueInDiscretization( const T value ) const;

  //! Check if the value range intersects the discretization
  bool doesRangeIntersectDiscretization( const T range_start,
                                         const T range_end ) const;

  //! Calculate the index of bins that the value falls in
  void calculateBinIndicesOfValue( const T value,
                                   BinIndexArray& bin_indices ) const;

  //! Calculate the index of bins that the range falls in
  void calculateBinIndicesOfRange(
                      const T range_start,
                      const T range_end,
                      BinIndexWeightPairArray& bin_indices_and_weights ) const;

private:

  //! Calculate the set of bin indices that the value falls in
  void calculateSetOfBinIndicesOfValue(const T value,
                                       std::set<size_t>& bin_index_set ) const;

  // The bin set array
  BinSetArray d_dimension_bins;

  // The set of values in all bins (for fast lookup)
  BinSet d_merged_bin_set;
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_UNORDERED_ESTIMATOR_DIMENSION_DISCRETIZATION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_UnorderedEstimatorDimensionDiscretization.hpp
//---------------------------------------------------------------------------//
