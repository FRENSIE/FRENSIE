//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_OrderedTypedObserverPhaseSpaceDimesionDiscretization_def.hpp
//! \author Alex Robinson
//! \brief  Ordered typed observer phase space dimension discretization def.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_DEF_HPP
#define MONTE_CARLO_ORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_DEF_HPP

// FRENSIE Includes
#include "Utility_ContractException.hpp"
#include "Utility_SortAlgorithms.hpp"

namespace MonteCarlo{

// Constructor
template<ObserverPhaseSpaceDimension dimension>
OrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::OrderedTypedObserverPhaseSpaceDimensionDiscretization(
                             const BinBoundaryArray& dimension_bin_boundaries )
  : d_dimension_bin_boundaries( dimension_bin_boundaries )
{
  // Make sure that the bins are sorted
  testPrecondition( Utility::Sort::isSortedAscending(
                                            dimension_bin_boundaries.begin(),
                                            dimension_bin_boundaries.end() ) );
}

// Print the dimension discretization
template<ObserverPhaseSpaceDimension dimension>
void OrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::print( std::ostream& os ) const
{
  os << this->getDimensionName() << " Bin Boundaries: ";

  for( unsigned i = 0; i < d_dimension_bin_boundaries.size(); ++i )
    os << d_dimension_bin_boundaries[i] << " ";
}

// Export the bin boundaries
template<ObserverPhaseSpaceDimension dimension>
void OrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::exportData(
                            const ParticleHistoryObserver::idType estimator_id,
                            EstimatorHDF5FileHandler& hdf5_file ) const
{
  hdf5_file.setEstimatorBinBoundaries<dimension>( estimator_id,
                                                  this->getBinBoundaries() );
}

// Return the boundaries array
template<ObserverPhaseSpaceDimension dimension>
auto OrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::getBinBoundaries() const -> const BinBoundaryArray&
{
  return d_dimension_bin_boundaries;
}

// Calculate the index of bins that the value falls in
/*! \details With ordered discretizations there will only ever be one bin that
 * the value falls in.
 */
template<ObserverPhaseSpaceDimension dimension>
void OrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::calculateBinIndicesOfValue(
                                             const DimensionValueType value,
                                             BinIndexArray& bin_indices ) const
{
  // Make sure that the value is in the discretization
  testPrecondition( this->isValueInDiscretization( value ) );

  // There will only ever be one bin that the value falls in
  bin_indices.resize( 1 );

  bin_indices[0] = this->calculateBinIndexOfValue( value );
}

// Calculate the index of bins that the value falls in
/*! \details With ordered discretizations there will only ever be one bin that
 * the value falls in. The weight will also always be 1.0.
 */
template<ObserverPhaseSpaceDimension dimension>
void OrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::calculateBinIndicesOfValue(
                       const DimensionValueType value,
                       BinIndexWeightPairArray& bin_indices_and_weights ) const
{
  // Make sure that the value is in the discretization
  testPrecondition( this->isValueInDiscretization( value ) );

  // There will only ever be one bin that the value falls in
  bin_indices_and_weights.resize( 1 );

  bin_indices_and_weights[0].first = this->calculateBinIndexOfValue( value );
  bin_indices_and_weights[0].second = 1.0;
}

// Calculate the index of bins that the range falls in
template<ObserverPhaseSpaceDimension dimension>
void OrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::calculateBinIndicesOfRange(
                       const DimensionValueType range_start,
                       const DimensionValueType range_end,
                       BinIndexWeightPairArray& bin_indices_and_weights ) const
{
  // Make sure that the range intersects the discretization
  testPrecondition( this->doesRangeIntersectDiscretization( range_start, range_end ) );

  // Find the bin index that the lower boundary of the range falls in (or is
  // closest to)
  size_t start_bin_index;

  if( this->isValueInDiscretization( range_start ) )
    start_bin_index = this->calculateBinIndexOfValue( range_start );
  else
    start_bin_index = 0;

  // Find the bin index that the upper boundary of the range falls in (or is
  // closest to)
  size_t end_bin_index;

  if( this->isValueInDiscretization( range_end ) )
    end_bin_index = this->calculateBinIndexOfValue( range_end );
  else
    end_bin_index = this->getNumberOfBins()-1;

  // Resize the bin indices and weights array
  bin_indices_and_weights_array.resize( end_bin_index - start_bin_index + 1 );

  // Calculate the size of the range
  double range_size = this->calculateRangeSize( range_start, range_end );

  // Set the bin indices and weights array
  for( size_t i = 0; i < bin_indices_and_weigts_array.size(); ++i )
  {
    // Set the bin index
    size_t bin_index = start_bin_index + i;

    bin_indices_and_weights_array[i].first = bin_index;

    // Set the weight associated with the bin index (fraction of range that
    // intersects the bin)
    const double bin_intersection_size =
      this->calculateBinIntersectionSize( bin_index, range_start, range_end );

    bin_indices_and_weights_array[i].second =
      bin_intersection_size/range_size;
  }
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_OrderedTypedObserverPhaseSpaceDimensionDiscretization_def.hpp
//---------------------------------------------------------------------------//
