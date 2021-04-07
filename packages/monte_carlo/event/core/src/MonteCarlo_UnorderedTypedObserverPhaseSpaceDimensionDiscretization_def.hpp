//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_UnorderedTypedObserverPhaseSpaceDimensionDiscretization_def.hpp
//! \author Alex Robinson
//! \brief  Unordered typed observer phase space dimension discretization def.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_UNORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_DEF_HPP
#define MONTE_CARLO_UNORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_DEF_HPP

// FRENSIE Includes
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Default constructor
template<ObserverPhaseSpaceDimension dimension>
UnorderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::UnorderedTypedObserverPhaseSpaceDimensionDiscretization()
{ /* ... */ }

// Constructor
template<ObserverPhaseSpaceDimension dimension>
UnorderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::UnorderedTypedObserverPhaseSpaceDimensionDiscretization(
                                            const BinSetArray& dimension_bins )
  : d_dimension_bins( dimension_bins )
{
  // Make sure that there is at least one bin
  TEST_FOR_EXCEPTION( dimension_bins.empty(),
                      std::runtime_error,
                      "At least one bin must be specified!" );

  // Create the set of values in all bins (for fast lookup)
  for( size_t i = 0; i < d_dimension_bins.size(); ++i )
  {
    d_merged_bin_set.insert( d_dimension_bins[i].begin(),
                             d_dimension_bins[i].end() );
  }
}

// Return the number of bins in the discretization
template<ObserverPhaseSpaceDimension dimension>
size_t UnorderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::getNumberOfBins() const
{
  return d_dimension_bins.size();
}

// Print the boundaries of a bin
template<ObserverPhaseSpaceDimension dimension>
void UnorderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::printBoundariesOfBin(
                                               std::ostream& os,
                                               const size_t bin_index ) const
{
  // Make sure the bin requested is valid
  testPrecondition( bin_index < this->getNumberOfBins() );

  os << this->getDimensionName() << " Bin: {";

  typename BinSet::const_iterator bin_values_it, bin_values_end;

  bin_values_it = d_dimension_bins[bin_index].begin();
  bin_values_end = d_dimension_bins[bin_index].end();

  while( bin_values_it != bin_values_end )
  {
    os << *bin_values_it;

    ++bin_values_it;

    if( bin_values_it != bin_values_end )
      os << ",";
  }

  os << "}";
}

// Print the dimension discretization
template<ObserverPhaseSpaceDimension dimension>
void UnorderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::print(
                                                       std::ostream& os ) const
{
  os << this->getDimensionName() << " Bins: ";

  for( size_t i = 0; i < d_dimension_bins.size(); ++i )
  {
    os << "{";

    typename BinSet::const_iterator bin_values_it, bin_values_end;

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

// Return the bin set array
template<ObserverPhaseSpaceDimension dimension>
auto UnorderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::getBinBoundaries() const -> const BinSetArray&
{
  return d_dimension_bins;
}

// Check if the value is contained in the discretization
template<ObserverPhaseSpaceDimension dimension>
inline bool UnorderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::isValueInDiscretization(
                                         const DimensionValueType value ) const
{
  return d_merged_bin_set.find( value ) != d_merged_bin_set.end();
}

// Check if the value range intersects the discretization
/*! \details With unordered discretizations the range simply consists of the
 * start value and the end value.
 */
template<ObserverPhaseSpaceDimension dimension>
inline bool UnorderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::doesRangeIntersectDiscretization(
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
inline void UnorderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::calculateBinIndicesOfValue(
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
void UnorderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::calculateBinIndicesOfValue(
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
  typename BinIndexWeightPairArray::iterator bin_indices_and_weights_it =
    bin_indices_and_weights.begin();

  while( bin_index_set_it != bin_index_set.end() )
  {
    bin_indices_and_weights_it->first = *bin_index_set_it;
    bin_indices_and_weights_it->second = 1.0;

    ++bin_index_set_it;
    ++bin_indices_and_weights_it;
  }
}

// Calculate the index of bins that the range falls in
template<ObserverPhaseSpaceDimension dimension>
inline void UnorderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::calculateBinIndicesOfRange(
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
    typename BinIndexWeightPairArray::value_type
      index_and_weight( *bin_indices_it, 1.0 );

    bin_indices_and_weights.push_back( index_and_weight );

    ++bin_indices_it;
  }
}

// Calculate the set of bin indices that the value falls in
template<ObserverPhaseSpaceDimension dimension>
inline void UnorderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::calculateSetOfBinIndicesOfValue(
                                        const DimensionValueType value,
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

// Serialize the discretization
template<ObserverPhaseSpaceDimension dimension>
template<typename Archive>
void UnorderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::serialize( Archive& ar, const unsigned version )
{
  // Serialize the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Serialize the local data
  ar & BOOST_SERIALIZATION_NVP( d_dimension_bins );
  ar & BOOST_SERIALIZATION_NVP( d_merged_bin_set );
}

} // end MonteCarlo namespace

BOOST_CLASS_EXPORT_KEY2( MonteCarlo::UnorderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION>,
                         "UnorderedTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_SOURCE_ID_DIMENSION>" );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::UnorderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, UnorderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION> );

#endif // end MONTE_CARLO_UNORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_UnorderedTypedObserverPhaseSpaceDimensionDiscretization_def.hpp
//---------------------------------------------------------------------------//
