//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_UnorderedEstimatorDimensionDiscretization_def.hpp
//! \author Alex Robinson
//! \brief  Unordered estimator dimension discretization definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_UNORDERED_ESTIMATOR_DIMENSION_DISCRETIZATION_DEF_HPP
#define MONTE_CARLO_UNORDERED_ESTIMATOR_DIMENSION_DISCRETIZATION_DEF_HPP

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

//! Constructor
template<typename T>
UnorderedEstimatorDimensionDiscretization<T>::UnorderedEstimatorDimensionDiscretization(
                                   const ObserverPhaseSpaceDimension dimension,
                                   const BinSetArray& dimension_bins )
  : d_dimension_bins( dimension_bins )
{
  // Make sure that there is at least one bin
  testPrecondition( dimension_bins.size() > 0 );

  // Create the set of values in all bins (for fast lookup)
  for( size_t i = 0; i < d_dimension_bins.size(); ++i )
  {
    d_merged_bin_set.insert( d_dimension_bins[i].begin(),
                             d_dimension_bins[i].end() );
  }
}

// Return the number of bins in the discretization
template<typename T>
size_t UnorderedEstimatorDimensionDiscretization<T>::getNumberOfBins() const
{
  return d_dimension_bins.size();
}

// Print the boundaries of a bin
template<typename T>
void UnorderedEstimatorDimensionDiscretization<T>::printBoundariesOfBin(
                                               std::ostream& os,
                                               const size_t bin_index ) const
{
  // Make sure the bin requested is valid
  testPrecondition( bin_index < this->getNumberOfBins );

  os << this->getDimensionName() << " Bin: {";

  BinSet::const_iterator bin_values_it, bin_values_end;

  bin_values_it = d_dimension_bins[bin_index].begin();
  bin_values_end = d_dimension_bins[bin_index].end();

  while( bin_values_it != bin_values_end )
  {
    os << *bin_values_it;
    
    ++bin_values_it;

    if( bin_values_it != bin_values_end )
      os << ",";
  }
}

// Print the dimension discretization
template<typename T>
void UnorderedEstimatorDimensionDiscretization<T>::print(
                                                       std::ostream& os ) const
{
  os << this->getDimensionName() << " Bins: ";

  for( size_t i = 0; i < d_dimension_bins.size(); ++i )
  {
    os << "{";

    BinSet::const_iterator bin_values_it, bin_values_end;
    
    bin_values_it = d_dimension_bins[i].begin();
    bin_values_end = d_dimension_bins[i].end();

    while( bin_values_it != bin_values_end )
    {
      os << *bin_values_it;
        
      ++bin_values_it;

      if( bin_values_it != bin_values_end )
        os << ",";
    }

    os << "} ";
  }
}

// Check if the value is contained in the discretization
template<typename T>
inline bool UnorderedEstimatorDimensionDiscretization<T>::isValueInDiscretization(
                                                          const T value ) const
{
  return d_merged_bin_set.find( value ) != d_merged_bin_set.end();
}

// Check if the value range intersects the discretization
/*! \details With unordered discretizations the range simply consists of the
 * start value and the end value.
 */
template<typename T>
inline bool UnorderedEstimatorDimensionDiscretization<T>::doesRangeIntersectDiscreteization(
                                                      const T range_start,
                                                      const T range_end ) const
{
  return this->isValueInDiscretization( range_start ) ||
    this->isValueInDiscretization( range_end );
}

// Calculate the bin indices that the value falls in
/*! \details Because the bins are not ordered this operation is O(N), where
 * N is the number of bins.
 */
template<typename T>
inline void UnorderedEstimatorDimensionDiscretization<T>::calculateBinIndicesOfValue(
                                             const T value,
                                             BinIndexArray& bin_indices ) const
{
  // Make sure that the value is in the discretization
  testPrecondition( this->isValueInDiscretization( value ) );

  std::set<size_t> bin_indices;

  this->calculateSetOfBinIndicesOfValue( value, bin_indices );
  
  // Set the bin indices
  bin_indices.assign( bin_indices.begin(), bin_indices.end() );
}

// Calculate the index of bins that the range falls in
template<typename T>
inline void UnorderedEstimatorDimensionDiscretization<T>::calculateBinIndicesOfRange(
                       const T range_start,
                       const T range_end,
                       BinIndexWeightPairArray& bin_indices_and_weights ) const
{
  // Make sure that the value is in the discretization
  testPrecondition( this->isValueInDiscretization( value ) );
  
  std::set<size_t> bin_indices;

  this->calculateSetOfBinIndicesOfValue( range_start, bin_indices );
  this->calculateSetOfBinIndicesOfValue( range_end, bin_indices );

  // Reset the bin indices and weights array
  bin_indices_and_weights.clear();

  std::set<size_t>::const_iterator bin_indices_it = bin_indices.begin();

  while( bin_indices_it != bin_indices.end() )
  {
    BinIndexWeightPairArray::value_type
      index_and_weight( *bin_indices_it, 1.0 );

    bin_indices_and_weights.push_back( bin_indices_and_weights );

    ++bin_indices_it;
  }
}

// Calculate the set of bin indices that the value falls in
template<typename T>
inline void UnorderedEstimatorDimensionDiscretization<T>::calculateSetOfBinIndicesOfValue(
                                        const T value,
                                        std::set<size_t>& bin_index_set ) const
{
  // Make sure that the value is in the discretization
  testPrecondition( this->isValueInDiscretization( value ) );

  for( size_t i = 0; i < d_dimension_bins.size(); ++i )
  {
    if( d_dimension_bins[i].find( value ) !=
        d_dimension_bins[i].end() )
      bin_index_set.insert( i );
  }
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_UNORDERED_ESTIMATOR_DIMENSION_DISCRETIZATION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_UnorderedEstimatorDimensionDiscretization_def.hpp
//---------------------------------------------------------------------------//
