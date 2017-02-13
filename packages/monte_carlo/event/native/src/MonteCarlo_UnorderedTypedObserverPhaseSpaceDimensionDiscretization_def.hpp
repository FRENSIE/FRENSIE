//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_UnorderedTypedObserverPhaseSpaceDimensionDiscretization_def.hpp
//! \author Alex Robinson
//! \brief  Unordered typed observer phase space dimension discretization def.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_UNORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_DEF_HPP
#define MONTE_CARLO_UNORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_DEF_HPP

// Trilinos Includes
#include <Teuchos_TwoDArray.hpp>

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

//! Constructor
template<ObserverPhaseSpaceDimension dimension>
UnorderedTypedObserverPhaseSpaceDimensionDiscretization<dimension,typename boost::enable_if<boost::is_integral<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType> >::type>::UnorderedTypedObserverPhaseSpaceDimensionDiscretization(
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
template<ObserverPhaseSpaceDimension dimension>
size_t UnorderedTypedObserverPhaseSpaceDimensionDiscretization<dimension,typename boost::enable_if<boost::is_integral<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType> >::type>::getNumberOfBins() const
{
  return d_dimension_bins.size();
}

// Print the boundaries of a bin
template<ObserverPhaseSpaceDimension dimension>
void UnorderedTypedObserverPhaseSpaceDimensionDiscretization<dimension,typename boost::enable_if<boost::is_integral<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType> >::type>::printBoundariesOfBin(
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
template<ObserverPhaseSpaceDimension dimension>
void UnorderedTypedObserverPhaseSpaceDimensionDiscretization<dimension,typename boost::enable_if<boost::is_integral<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType> >::type>::print(
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

// Export the dimension discretization
/*! \details The array of sets will be converted to a Teuchos::TwoDArray. 
 * Every row of the TwoDArray must have the same number of columns so a
 * padding will be applied (values of -1).
 */
template<ObserverPhaseSpaceDimension dimension>
void UnorderedTypedObserverPhaseSpaceDimensionDiscretization<dimension,typename boost::enable_if<boost::is_integral<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType> >::type>::exportData(
                            const ParticleHistoryObserver::idType estimator_id,
                            EstimatorHDF5FileHandler& hdf5_file ) const
{
  size_t num_columns = 0;
  
  // Calculate the columns
  for( size_t i = 0; i < d_dimension_bins.size(); ++i )
  {
    if( d_dimension_bins[i].size() > num_columns )
      num_columns = d_dimension_bins[i].size();
  }
  
  // Convert the bin sets to a TwoDArray
  Teuchos::TwoDArray<long long>
    padded_two_d_array_copy( d_dimension_bins.size(), num_columns, -1ll );

  for( size_t i = 0; i < d_dimension_bins.size(); ++i )
  {
    BinSet::const_iterator bin_it = d_dimension_bins[i].begin();
    BinSet::const_iterator bin_end = d_dimension_bins[i].end();

    size_t j = 0;

    while( bin_it != bin_end )
    {
      padded_two_d_array_copy( i, j ) = *bin_it;

      ++bin_it;
      ++j;
    }
  }

  hdf5_file.setEstimatorBinBoundaries<dimension>( estimator_id,
                                                  padded_two_d_array_copy );
}

// Check if the value is contained in the discretization
template<ObserverPhaseSpaceDimension dimension>
inline bool UnorderedTypedObserverPhaseSpaceDimensionDiscretization<dimension,typename boost::enable_if<boost::is_integral<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType> >::type>::isValueInDiscretization(
                                         const DimensionValueType value ) const
{
  return d_merged_bin_set.find( value ) != d_merged_bin_set.end();
}

// Check if the value range intersects the discretization
/*! \details With unordered discretizations the range simply consists of the
 * start value and the end value.
 */
template<ObserverPhaseSpaceDimension dimension>
inline bool UnorderedTypedObserverPhaseSpaceDimensionDiscretization<dimension,typename boost::enable_if<boost::is_integral<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType> >::type>::doesRangeIntersectDiscreteization(
                                     const DimensionValueType range_start,
                                     const DimensionValueType range_end ) const
{
  return this->isValueInDiscretization( range_start ) ||
    this->isValueInDiscretization( range_end );
}

// Calculate the bin indices that the value falls in
/*! \details Because the bins are not ordered this operation is O(N), where
 * N is the number of bins.
 */
template<ObserverPhaseSpaceDimension dimension>
inline void UnorderedTypedObserverPhaseSpaceDimensionDiscretization<dimension,typename boost::enable_if<boost::is_integral<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType> >::type>::calculateBinIndicesOfValue(
                                             const DimensionValueType value,
                                             BinIndexArray& bin_indices ) const
{
  // Make sure that the value is in the discretization
  testPrecondition( this->isValueInDiscretization( value ) );

  std::set<size_t> bin_index_set;

  this->calculateSetOfBinIndicesOfValue( value, bin_index_set );
  
  // Set the bin indices
  bin_indices.assign( bin_index_set.begin(), bin_index_set.end() );
}

// Calculate the index of bins that the value falls in
/*! \details Because the bins are not ordered this operation is O(N), where
 * N is the number of bins. The weight will always be 1.0.
 */
template<ObserverPhaseSpaceDimension dimension>
void UnorderedTypedObserverPhaseSpaceDimensionDiscretization<dimension,typename boost::enable_if<boost::is_integral<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType> >::type>::calculateBinIndicesOfValue(
                       const DimensionValueType value,
                       BinIndexWeightPairArray& bin_indices_and_weights ) const
{
  // Make sure that the value is in the discretization
  testPrecondition( this->isValueInDiscretization( value ) );

  std::set<size_t> bin_index_set;

  this->calculateSetOfBinIndicesOfValue( value, bin_index_set );
  
  // Set the bin indices
  bin_indices_and_weights.resize( bin_index_set.size() );

  std::set<size_t>::const_iterator bin_index_set_it = bin_index_set.begin();
  BinIndexWeightPairArray::iterator bin_indices_and_weights_it =
    bin_indices_and_weights.begin();

  while( bin_index_set_it != bin_index_set.end() )
  {
    bin_indices_and_weights_it->first = *bin_index_set_it;
    bin_indices_and_weights_it->second = 1.0;
    
    ++bin_index_set_it;
    ++bin_indices_and_weights;
  }
}

// Calculate the index of bins that the range falls in
template<ObserverPhaseSpaceDimension dimension>
inline void UnorderedTypedObserverPhaseSpaceDimensionDiscretization<dimension,typename boost::enable_if<boost::is_integral<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType> >::type>::calculateBinIndicesOfRange(
                       const DimensionValueType range_start,
                       const DimensionValueType range_end,
                       BinIndexWeightPairArray& bin_indices_and_weights ) const
{
  // Make sure that the range intersects the discretization
  testPrecondition( this->doesRangeIntersectDiscretization( range_start, range_end ) );
  
  std::set<size_t> bin_indices;

  if( this->isValueInDiscretization( range_start ) )
    this->calculateSetOfBinIndicesOfValue( range_start, bin_indices );

  if( this->isValueInDiscretization( range_end ) )
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
template<ObserverPhaseSpaceDimension dimension>
inline void UnorderedTypedObserverPhaseSpaceDimensionDiscretization<dimension,typename boost::enable_if<boost::is_integral<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType> >::type>::calculateSetOfBinIndicesOfValue(
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

#endif // end MONTE_CARLO_UNORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_UnorderedTypedObserverPhaseSpaceDimensionDiscretization_def.hpp
//---------------------------------------------------------------------------//
