//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_OrderedTypedObserverPhaseSpaceDimesionDiscretization_def.hpp
//! \author Alex Robinson
//! \brief  Ordered typed observer phase space dimension discretization def.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_DEF_HPP
#define MONTE_CARLO_ORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_DEF_HPP

// Boost Includes
#include <boost/serialization/shared_ptr.hpp>

// FRENSIE Includes
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Default constructor
template<ObserverPhaseSpaceDimension dimension>
OrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::OrderedTypedObserverPhaseSpaceDimensionDiscretization()
{ /* ... */ }
  
// Constructor
template<ObserverPhaseSpaceDimension dimension>
OrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::OrderedTypedObserverPhaseSpaceDimensionDiscretization(
                             const BinBoundaryArray& dimension_bin_boundaries )
  : d_dimension_bin_boundaries( new BinBoundaryArray( dimension_bin_boundaries ) )
{
  // Make sure that there is at least one bin
  TEST_FOR_EXCEPTION( dimension_bin_boundaries.size() <= 1,
                      std::runtime_error,
                      "At least one bin (two boundaries) must be specified!" );
  
  // Make sure that the bins are sorted
  TEST_FOR_EXCEPTION( !Utility::Sort::isSortedAscending(
                                            dimension_bin_boundaries.begin(),
                                            dimension_bin_boundaries.end() ),
                      std::runtime_error,
                      Utility::toString(dimension) << " dimension bin "
                      "boundaries must be sorted!" );

  // Make sure that the bins have a valid range
  TEST_FOR_EXCEPTION( dimension_bin_boundaries.front() < ObserverPhaseSpaceDimensionTraits<dimension>::lowerBound(),
                      std::runtime_error,
                      Utility::toString(dimension) << " dimension bin "
                      "boundaries cannot have a value lower than "
                      << Utility::toString(ObserverPhaseSpaceDimensionTraits<dimension>::lowerBound()) <<
                      "!" );

  TEST_FOR_EXCEPTION( dimension_bin_boundaries.back() > ObserverPhaseSpaceDimensionTraits<dimension>::upperBound(),
                      std::runtime_error,
                      Utility::toString(dimension) << " dimension bin "
                      "boundaries cannot have a value greater than "
                      << ObserverPhaseSpaceDimensionTraits<dimension>::upperBound() <<
                      "!" );
    
}

// Print the dimension discretization
template<ObserverPhaseSpaceDimension dimension>
void OrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::print( std::ostream& os ) const
{
  os << this->getDimensionName() << " Bin Boundaries: ";

  for( size_t i = 0; i < d_dimension_bin_boundaries->size(); ++i )
    os << Utility::toString((*d_dimension_bin_boundaries)[i]) << " ";
}

// Return the boundaries array
template<ObserverPhaseSpaceDimension dimension>
auto OrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::getBinBoundaries() const -> const BinBoundaryArray&
{
  return (*d_dimension_bin_boundaries);
}

// Return the shared boundaries array
template<ObserverPhaseSpaceDimension dimension>
auto OrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::getSharedBoundaries() const -> std::shared_ptr<const BinBoundaryArray>
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
  
  if( range_start != range_end )
  {
    // Find the bin index that the upper boundary of the range falls in (or is
    // closest to)
    size_t end_bin_index;

    if( this->isValueInDiscretization( range_end ) )
      end_bin_index = this->calculateBinIndexOfValue( range_end );
    else
      end_bin_index = this->getNumberOfBins()-1;

    // Resize the bin indices and weights array
    bin_indices_and_weights.resize( end_bin_index - start_bin_index + 1 );

    // Calculate the size of the range
    const double range_size =
      this->calculateRangeSize( range_start, range_end );
    
    // Set the bin indices and weights array
    for( size_t i = 0; i < bin_indices_and_weights.size(); ++i )
    {
      // Set the bin index
      size_t bin_index = start_bin_index + i;
      
      bin_indices_and_weights[i].first = bin_index;
      
      // Set the weight associated with the bin index (fraction of range that
      // intersects the bin)
      const double bin_intersection_size =
        this->calculateBinIntersectionSize( bin_index, range_start, range_end );
      
      bin_indices_and_weights[i].second =
        bin_intersection_size/range_size;
    }
  }
  // Handle the special case of range_start == range_end
  else
  {
    bin_indices_and_weights.resize( 1 );
    
    bin_indices_and_weights.front().first = start_bin_index;
    bin_indices_and_weights.front().second = 1.0;
  }
}

// Serialize the discretization
template<ObserverPhaseSpaceDimension dimension>
template<typename Archive>
void OrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::serialize( Archive& ar, const unsigned version )
{
  // Serialize the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Serialize the local data
  ar & BOOST_SERIALIZATION_NVP( d_dimension_bin_boundaries );
}

} // end MonteCarlo namespace

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::OrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, OrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::OrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, OrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::OrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, OrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::OrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, OrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::OrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, OrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::OrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, OrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION> );

#endif // end MONTE_CARLO_ORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_OrderedTypedObserverPhaseSpaceDimensionDiscretization_def.hpp
//---------------------------------------------------------------------------//
