//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardOrderedEstimatorDimensionDiscretization_def.hpp
//! \author Alex Robinson
//! \brief  The standard ordered estimator dimension discretization definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_ORDERED_ESTIMATOR_DIMENSION_DISCRETIZATION_DEF_HPP
#define MONTE_CARLO_STANDARD_ORDERED_ESTIMATOR_DIMENSION_DISCRETIZATION_DEF_HPP

// FRENSIE Includes
#include "Utility_ContractException.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_SortAlgorithms.hpp"

namespace MonteCarlo{

// Constructor
template<typename T>
StandardOrderedEstimatorDimensionDiscretization<T,typename boost::enable_if<boost::is_floating_point<T> >::type>::StandardOrderedEstimatorDimensionDiscretization(
                       const ObserverPhaseSpaceDimension dimension,
                       const BinBoundaryArray& dimension_bin_boundaries )
  : OrderedEstimatorDimensionDiscretization<T>( dimension, dimension_bin_boundaries )
{
  // Make sure there is at least one bin
  testPrecondition( dimension_bin_boundaries.size() >= 2 );
  // Make sure the bins are sorted
  testPrecondition( Utility::Sort::isSortedAscending(
                                            this->getBinBoundaries().begin(),
                                            this->getBinBoundaries().end() ) );
}

// Constructor
template<typename T>
StandardOrderedEstimatorDimensionDiscretization<T,typename boost::enable_if<boost::is_integral<T> >::type>::StandardOrderedEstimatorDimensionDiscretization(
                       const ObserverPhaseSpaceDimension dimension,
                       const BinBoundaryArray& dimension_bin_boundaries )
  : OrderedEstimatorDimensionDiscretization<T>( dimension, dimension_bin_boundaries )
{
  // Make sure there is at least one bin
  testPrecondition( dimension_bin_boundaries.size() >= 1 );
  // Make sure the bins are sorted
  testPrecondition( Utility::Sort::isSortedAscending(
                                            this->getBinBoundaries().begin(),
                                            this->getBinBoundaries().end() ) );
}

// Return the number of bins in the discretization
template<typename T>
size_t StandardOrderedEstimatorDimensionDiscretization<T,typename boost::enable_if<boost::is_floating_point<T> >::type>::getNumberOfBins() const
{
  return this->getBinBoundaries().size() - 1;
}

// Return the number of bins in the discretization
template<typename T>
size_t StandardOrderedEstimatorDimensionDiscretization<T,typename boost::enable_if<boost::is_integral<T> >::type>::getNumberOfBins() const
{
  return this->getBinBoundaries().size();
}

// Print the boundaries of a bin
template<typename T>
void StandardOrderedEstimatorDimensionDiscretization<T,typename boost::enable_if<boost::is_floating_point<T> >::type>::printBoundariesOfBin(
                                                 std::ostream& os,
                                                 const size_t bin_index ) const
{
  // Make sure the bin requested is valid
  testPrecondition( bin_index < this->getNumberOfBins() );

  os << this->getDimensionName();

  if( bin_index == 0u )
    os << " Bin: [";
  else
    os << " Bin: (";

  os << this->getBinBoundaries()[bin_index] << ","
     << this->getBinBoundaries()[bin_index+1] << "]";
}

// Print the boundaries of a bin
template<typename T>
void StandardOrderedEstimatorDimensionDiscretization<T,typename boost::enable_if<boost::is_integral<T> >::type>::printBoundariesOfBin(
                                                 std::ostream& os,
                                                 const size_t bin_index ) const
{
  // Make sure the bin requested is valid
  testPrecondition( bin_index < this->getNumberOfBins() );

  os << this->getDimensionName() << " Bin: [";

  if( bin_index == 0u )
    os << 0u;
  else
    os << this->getBinBoundaries()[bin_index-1]+1;

  os << "," << this->getBinBoundaries()[bin_index] << "]";
}

// Check if the value is contianed in the discretization
template<typename T>
bool StandardOrderedEstimatorDimensionDiscretization<T,typename boost::enable_if<boost::is_floating_point<T> >::type>::isValueInDiscretization(
                                                          const T value ) const
{
  return value >= this->getBinBoundaries().front() &&
    value <= this->getBinBoundaries().back();
}

// Check if the value is contianed in the discretization
template<typename T>
bool StandardOrderedEstimatorDimensionDiscretization<T,typename boost::enable_if<boost::is_integral<T> >::type>::isValueInDiscretization(
                                                          const T value ) const
{
  return value <= this->getBinBoundaries().back();
}

// Check if the value range intersects the discretization
template<typename T>
bool StandardOrderedEstimatorDimensionDiscretization<T,typename boost::enable_if<boost::is_floating_point<T> >::type>::doesRangeIntersectDiscretization(
                                                      const T range_start,
                                                      const T range_end ) const
{
  // Make sure that the range is valid
  testPrecondition( range_start < range_end );
  
  return (range_start <= this->getBinBoundaries().front() &&
          range_end > this->getBinBoundaries().front()) ||
    (range_start < this->getBinBoundaries().back() &&
     range_end >= this->getBinBoundaries().back()) ||
    (range_start >= this->getBinBoundaries().front() &&
     range_start <= this->getBinBoundaries().back());
}

// Check if the value range intersects the discretization
template<typename T>
bool StandardOrderedEstimatorDimensionDiscretization<T,typename boost::enable_if<boost::is_integral<T> >::type>::doesRangeIntersectDiscretization(
                                                      const T range_start,
                                                      const T range_end ) const
{
  // Make sure that the range is valid
  testPrecondition( range_start < range_end );
  
  return range_start <= this->getBinBoundaries().back();
}

// Calculate the index of bins that the value falls in
template<typename T>
void StandardOrderedEstimatorDimensionDiscretization<T,typename boost::enable_if<boost::is_floating_point<T> >::type>::calculateBinIndicesOfValue(
                                    const T value,
                                    BinIndexArray& bin_indices ) const
{
  // Make sure the value is in the discretization
  testPrecondition( this->isValueInDiscretization( value ) );

  // There will only ever be one bin that the value falls in
  bin_indices.resize( 1 );
  
  bin_indices[0] = this->calculateBinIndexOfValue( value );
}

// Calculate the index of bins that the value falls in
template<typename T>
void StandardOrderedEstimatorDimensionDiscretization<T,typename boost::enable_if<boost::is_integral<T> >::type>::calculateBinIndicesOfValue(
                                    const T value,
                                    BinIndexArray& bin_indices ) const
{
  // Make sure the value is in the discretization
  testPrecondition( this->isValueInDiscretization( value ) );

  // There will only ever be one bin that the value falls in
  bin_indices.resize( 1 );

  bin_indices[0] = this->calculateBinIndexOfValue( value );
}

// Calculate the index of bins that the range falls in
template<typename T>
void StandardOrderedEstimatorDimensionDiscretization<T,typename boost::enable_if<boost::is_floating_point<T> >::type>::calculateBinIndicesOfRange(
                       const T range_start,
                       const T range_end,
                       BinIndexWeightPairArray& bin_indices_and_weights ) const
{
  // Make sure that the range intersects the discretization
  testPrecondition( this->doesRangeIntersectDiscretization(
                                                     range_start, range_end) );

  size_t start_bin_index;
  
  if( range_start >= this->getBinBoundaries().front() )
    start_bin_index = this->calculateBinIndexOfValue( range_start );
  else
    start_bin_index = 0;

  size_t end_bin_index;

  if( range_end <= this->getBinBoundaries().back() )
    end_bin_index = this->calculateBinIndexOfValue( range_end );
  else
    end_bin_index = this->getNumberOfBins()-1;

  // Resize the bin indices and weights array
  bin_indices_and_weights_array.resize( end_bin_index - start_bin_index + 1 );

  // Calculate the size of the range
  double range_size = range_end - range_start;
  
  // Set the bin indices and weights array
  for( size_t i = 0; i < bin_indices_and_weights_array.size(); ++i )
  {
    size_t bin_index = start_bin_index + i;
    
    bin_indices_and_weights_array[i].first = bin_index;

    const double bin_intersection_size =
      this->calculateBinIntersectionSize( bin_index, range_start, range_end )
    
    bin_indices_and_weights_array[i].second =
      bin_intersection_size/range_size;
  }
}

// Calculate the index of bins that the range falls in
template<typename T>
void StandardOrderedEstimatorDimensionDiscretization<T,typename boost::enable_if<boost::is_integral<T> >::type>::calculateBinIndicesOfRange(
                       const T range_start,
                       const T range_end,
                       BinIndexWeightPairArray& bin_indices_and_weights ) const
{
  // Make sure that the range intersects the discretization
  testPrecondition( this->doesRangeIntersectDiscretization(
                                                     range_start, range_end) );

  size_t start_bin_index = this->calculateBinIndexOfValue( range_start );
  
  size_t end_bin_index;

  if( this->isValueInDiscretization( range_end ) )
    end_bin_index = this->calculateBinIndexOfValue( range_end );
  else
    end_bin_index = this->getNumberOfBins()-1;

  // Resize the bin indices and weights array
  bin_indices_and_weights_array.resize( end_bin_index - start_bin_index + 1 );

  // Calculate the size of the range
  double range_size = range_end - range_start;
  
  // Set the bin indices and weights array
  for( size_t i = 0; i < bin_indices_and_weights_array.size(); ++i )
  {
    size_t bin_index = start_bin_index + i;
    
    bin_indices_and_weights_array[i].first = bin_index;

    const double bin_intersection_size =
      this->calculateBinIntersectionSize( bin_index, range_start, range_end )
    
    bin_indices_and_weights_array[i].second =
      bin_intersection_size/range_size;
  }
}

// Calculate the index of bins that the range falls in
template<typename T>
size_t StandardOrderedEstimatorDimensionDiscretization<T,typename boost::enable_if<boost::is_floating_point<T> >::type>::calculateBinIndexOfValue( const T value ) const
{
  // Make sure the value is in the discretization
  testPrecondition( this->isValueInDiscretization( value ) );
  
  unsigned bin =
    Utility::Search::binaryUpperBoundIndex( this->getBinBoundaries().begin(),
					    this->getBinBoundaries().end(),
					    value );
  if( bin != 0u )
    return bin - 1;
  else
    return bin;
}

// Calculate the index of the bin that the value falls in
template<typename T>
size_t StandardOrderedEstimatorDimensionDiscretization<T,typename boost::enable_if<boost::is_integral<T> >::type>::calculateBinIndexOfValue( const T value ) const
{
  // Make sure the value is in the discretization
  testPrecondition( this->isValueInDiscretization( value ) );

  return Utility::Search::binaryUpperBoundIndex(
                                              this->getBinBoundaries().begin(),
                                              this->getBinBoundaries().end(),
                                              value );
}

// Calculate the size of a bin
template<typename T>
double StandardOrderedEstimatorDimensionDiscretization<T,typename boost::enable_if<boost::is_floating_point<T> >::type>::calculateBinSize( const size_t bin_index ) const
{
  // Make sure that the bin index is valid
  testPrecondition( bin_index < this->getNumberOfBins() );

  return this->getBinBoundaries()[bin_index+1] -
    this->getBinBoundaries()[bin_index];
}

// Calculate the size of a bin
template<typename T>
double StandardOrderedEstimatorDimensionDiscretization<T,typename boost::enable_if<boost::is_integral<T> >::type>::calculateBinSize( const size_t bin_index ) const
{
  // Make sure that the bin index is valid
  testPrecondition( bin_index < this->getNumberOfBins() );

  if( bin_index == 0 )
    return this->getBinBoundaries().front();
  else
  {
    return this->getBinBoundaries()[bin_index] -
      this->getBinBoundaries()[bin_index-1];
  }
}

// Calculate the size of a bin intersection
template<typename T>
double StandardOrderedEstimatorDimensionDiscretization<T,typename boost::enable_if<boost::is_floating_point<T> >::type>::calculateBinIntersectionSize(
                                                      const size_t bin_index,
                                                      const T range_start,
                                                      const T range_end ) const
{
  // Make sure that the bin index is valid
  testPrecondition( bin_index < this->getNumberOfBins() );

  T intersection_start_value;

  if( range_start <= this->getBinBoundaries()[bin_index] )
    intersection_start_value = this->getBinBoundaries()[bin_index];
  else
    intersection_start_value = range_start;

  T intersection_end_value;

  if( range_end >= this->getBinBoundaries()[bin_index+1] )
    intersection_end_value = this->getBinBoundaries()[bin_index+1];
  else
    intersection_end_value = range_end;

  return intersection_end_value - intersection_start_value;
}

// Calculate the size of a bin intersection
template<typename T>
double StandardOrderedEstimatorDimensionDiscretization<T,typename boost::enable_if<boost::is_integral<T> >::type>::calculateBinIntersectionSize(
                                                      const size_t bin_index,
                                                      const T range_start,
                                                      const T range_end ) const
{
  // Make sure that the bin index is valid
  testPrecondition( bin_index < this->getNumberOfBins() );

  T intersection_start_value;

  if( bin_index == 0 )
    intersection_start_value = range_start;
  else
  {
    if( range_start <= this->getBinBoundaries()[bin_index-1] )
      intersection_start_value = this->getBinBoundaries()[bin_index-1] + 1;
    else
      intersection_start_value = range_start;
  }

  T intersection_end_value;

  if( range_end > this->getBinBoundaries()[bin_index] )
    intersection_end_value = this->getBinBoundaries()[bin_index];
  else
    intersection_end_value = range_end;

  return intersection_end_value - intersection_start_value;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_ORDERED_ESTIMATOR_DIMENSION_DISCRETIZATION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardOrderedEstimatorDimensionDiscretization_def.hpp
//---------------------------------------------------------------------------//
