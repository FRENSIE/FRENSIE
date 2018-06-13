//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization_def.hpp
//! \author Alex Robinson
//! \brief  Floating point typed observer phase space dimension discretization
//!         definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_FLOATING_POINT_ORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_DEF_HPP
#define MONTE_CARLO_FLOATING_POINT_ORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_DEF_HPP

// FRENSIE Includes
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Default constructor
template<ObserverPhaseSpaceDimension dimension>
FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension,typename std::enable_if<std::is_floating_point<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType>::value>::type>::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization()
  : BaseType()
{ /* ... */ }

// Constructor (with number of hash grid bins specified)
template<ObserverPhaseSpaceDimension dimension>
FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension,typename std::enable_if<std::is_floating_point<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType>::value>::type>::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization(
                             const BinBoundaryArray& dimension_bin_boundaries )
  : FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization(
                                        dimension_bin_boundaries,
                                        dimension_bin_boundaries.size()/10+1 )
{ /* ... */ }
  
// Constructor (with number of hash grid bins specified)
template<ObserverPhaseSpaceDimension dimension>
FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension,typename std::enable_if<std::is_floating_point<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType>::value>::type>::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization(
                              const BinBoundaryArray& dimension_bin_boundaries,
                              const unsigned hash_grid_bins )
  : BaseType( dimension_bin_boundaries ),
    d_grid_searcher( new Utility::StandardHashBasedGridSearcher<BinBoundaryArray,false>( dimension_bin_boundaries, hash_grid_bins ) )
{ 
  // Make sure that there is at least one bin
  testPrecondition( dimension_bin_boundaries.size() >= 2 );
}

// Return the number of bins in the discretization
template<ObserverPhaseSpaceDimension dimension>
size_t FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension,typename std::enable_if<std::is_floating_point<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType>::value>::type>::getNumberOfBins() const
{
  return this->getBinBoundaries().size() - 1;
}

// Print the boundaries of a bin
template<ObserverPhaseSpaceDimension dimension>
void FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension,typename std::enable_if<std::is_floating_point<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType>::value>::type>::printBoundariesOfBin(
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

// Check if the value is contained in the discretization
template<ObserverPhaseSpaceDimension dimension>
bool FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension,typename std::enable_if<std::is_floating_point<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType>::value>::type>::isValueInDiscretization(
                                         const DimensionValueType value ) const
{
  return value >= this->getBinBoundaries().front() &&
    value <= this->getBinBoundaries().back();
}

// Check if the value range intersects the discretization
template<ObserverPhaseSpaceDimension dimension>
bool FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension,typename std::enable_if<std::is_floating_point<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType>::value>::type>::doesRangeIntersectDiscretization(
                                     const DimensionValueType range_start,
                                     const DimensionValueType range_end ) const
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

// Calculate the index of the bin  that the value falls in
template<ObserverPhaseSpaceDimension dimension>
size_t FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension,typename std::enable_if<std::is_floating_point<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType>::value>::type>::calculateBinIndexOfValue(
                                         const DimensionValueType value ) const
{
  // Make sure the value is in the discretization
  testPrecondition( this->isValueInDiscretization( value ) );

  return d_grid_searcher->findLowerBinIndexIncludingUpperBound( value );
}

// Calculate the size of a bin
template<ObserverPhaseSpaceDimension dimension>
double FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension,typename std::enable_if<std::is_floating_point<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType>::value>::type>::calculateBinSize(
                                                 const size_t bin_index ) const
{
  // Make sure that the bin index is valid
  testPrecondition( bin_index < this->getNumberOfBins() );

  return this->getBinBoundaries()[bin_index+1] -
    this->getBinBoundaries()[bin_index];
}

// Calculate the size of a bin intersection
template<ObserverPhaseSpaceDimension dimension>
double FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension,typename std::enable_if<std::is_floating_point<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType>::value>::type>::calculateBinIntersectionSize(
                                     const size_t bin_index,
                                     const DimensionValueType range_start,
                                     const DimensionValueType range_end ) const
{
  // Make sure that the bin index is valid
  testPrecondition( bin_index < this->getNumberOfBins() );

  DimensionValueType intersection_start_value;

  if( range_start <= this->getBinBoundaries()[bin_index] )
    intersection_start_value = this->getBinBoundaries()[bin_index];
  else
    intersection_start_value = range_start;

  DimensionValueType intersection_end_value;

  if( range_end >= this->getBinBoundaries()[bin_index+1] )
    intersection_end_value = this->getBinBoundaries()[bin_index+1];
  else
    intersection_end_value = range_end;

  return this->calculateRangeSize( range_start, range_end );
}

// Calculate the size of a range
template<ObserverPhaseSpaceDimension dimension>
double FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension,typename std::enable_if<std::is_floating_point<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType>::value>::type>::calculateRangeSize(
                                     const DimensionValueType range_start,
                                     const DimensionValueType range_end ) const
{
  return range_end - range_start;
}

// Serialize the discretization
template<ObserverPhaseSpaceDimension dimension>
template<typename Archive>
void FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension,typename std::enable_if<std::is_floating_point<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType>::value>::type>::serialize( Archive& ar, const unsigned version )
{
  // Serialize the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Serialize the local data
  ar & BOOST_SERIALIZATION_NVP( d_grid_searcher );
}
  
} // end MonteCarlo namespace

BOOST_CLASS_EXPORT_KEY2( MonteCarlo::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION>,
                         "FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_COSINE_DIMENSION>" );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION> );
EXTERN_EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( MonteCarlo::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION> );

BOOST_CLASS_EXPORT_KEY2( MonteCarlo::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION>,
                         "FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_SOURCE_ENERGY_DIMENSION>" );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION> );
EXTERN_EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( MonteCarlo::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION> );

BOOST_CLASS_EXPORT_KEY2( MonteCarlo::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION>,
                         "FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_ENERGY_DIMENSION>" );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION> );
EXTERN_EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( MonteCarlo::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION> );

BOOST_CLASS_EXPORT_KEY2( MonteCarlo::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION>,
                         "FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_SOURCE_TIME_DIMENSION>" );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION> );
EXTERN_EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( MonteCarlo::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION> );

BOOST_CLASS_EXPORT_KEY2( MonteCarlo::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION>,
                         "FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_TIME_DIMENSION>" );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION> );
EXTERN_EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( MonteCarlo::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION> );

#endif // end MONTE_CARLO_FLOATING_POINT_ORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization_def.hpp
//---------------------------------------------------------------------------//
