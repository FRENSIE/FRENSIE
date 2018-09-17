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

// Std Lib Includes
#include <type_traits>

// FRENSIE Includes
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Default constructor
template<ObserverPhaseSpaceDimension dimension>
FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization()
  : BaseType()
{ 
  // Make sure that the dimension type is a floating point type
  testStaticPrecondition((std::is_floating_point<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType>::value));
}

// Constructor (with number of hash grid bins specified)
template<ObserverPhaseSpaceDimension dimension>
FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization(
                             const BinBoundaryArray& dimension_bin_boundaries )
  : BaseType( dimension_bin_boundaries )
{ 
  // Make sure that the dimension type is a floating point type
  testStaticPrecondition((std::is_floating_point<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType>::value));
}

// Return the number of bins in the discretization
template<ObserverPhaseSpaceDimension dimension>
size_t FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::getNumberOfBins() const
{
  return this->getBinBoundaries().size() - 1;
}

// Print the boundaries of a bin
template<ObserverPhaseSpaceDimension dimension>
void FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::printBoundariesOfBin(
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

  os << Utility::toString(this->getBinBoundaries()[bin_index]) << ","
     << Utility::toString(this->getBinBoundaries()[bin_index+1]) << "]";
}

// Check if the value is contained in the discretization
template<ObserverPhaseSpaceDimension dimension>
bool FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::isValueInDiscretization(
                                         const DimensionValueType value ) const
{
  return value >= this->getBinBoundaries().front() &&
    value <= this->getBinBoundaries().back();
}

// Check if the value range intersects the discretization
template<ObserverPhaseSpaceDimension dimension>
bool FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::doesRangeIntersectDiscretization(
                                     const DimensionValueType range_start,
                                     const DimensionValueType range_end ) const
{
  // Make sure that the range is valid
  testPrecondition( range_start <= range_end );

  if( range_start >= this->getBinBoundaries().front() &&
      range_end <= this->getBinBoundaries().back() )
    return true;
  else if( range_start <= this->getBinBoundaries().front() &&
           range_end > this->getBinBoundaries().front() )
    return true;
  else if( range_start < this->getBinBoundaries().back() &&
           range_end >= this->getBinBoundaries().back() )
    return true;
  else
    return false;
}

// Calculate the index of the bin  that the value falls in
template<ObserverPhaseSpaceDimension dimension>
size_t FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::calculateBinIndexOfValue(
                                         const DimensionValueType value ) const
{
  // Make sure the value is in the discretization
  testPrecondition( this->isValueInDiscretization( value ) );

  size_t bin =
    Utility::Search::binaryUpperBoundIndex( this->getBinBoundaries().begin(),
                                            this->getBinBoundaries().end(),
                                            value );

  if( bin != 0 )
    return bin - 1;
  else
    return bin;
}

// Calculate the size of a bin
template<ObserverPhaseSpaceDimension dimension>
double FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::calculateBinSize(
                                                 const size_t bin_index ) const
{
  // Make sure that the bin index is valid
  testPrecondition( bin_index < this->getNumberOfBins() );

  return this->getBinBoundaries()[bin_index+1] -
    this->getBinBoundaries()[bin_index];
}

// Calculate the size of a bin intersection
template<ObserverPhaseSpaceDimension dimension>
double FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::calculateBinIntersectionSize(
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

  return this->calculateRangeSize( intersection_start_value,
                                   intersection_end_value );
}

// Calculate the size of a range
template<ObserverPhaseSpaceDimension dimension>
double FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::calculateRangeSize(
                                     const DimensionValueType range_start,
                                     const DimensionValueType range_end ) const
{
  return range_end - range_start;
}

// Serialize the discretization
template<ObserverPhaseSpaceDimension dimension>
template<typename Archive>
void FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::serialize( Archive& ar, const unsigned version )
{
  // Serialize the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );
}

} // end MonteCarlo namespace

BOOST_CLASS_EXPORT_KEY2( MonteCarlo::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION>,
                         "FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_COSINE_DIMENSION>" );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION> );

BOOST_CLASS_EXPORT_KEY2( MonteCarlo::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION>,
                         "FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_SOURCE_ENERGY_DIMENSION>" );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION> );

BOOST_CLASS_EXPORT_KEY2( MonteCarlo::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION>,
                         "FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_ENERGY_DIMENSION>" );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION> );

BOOST_CLASS_EXPORT_KEY2( MonteCarlo::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION>,
                         "FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_SOURCE_TIME_DIMENSION>" );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION> );

BOOST_CLASS_EXPORT_KEY2( MonteCarlo::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION>,
                         "FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_TIME_DIMENSION>" );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION> );

#endif // end MONTE_CARLO_FLOATING_POINT_ORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization_def.hpp
//---------------------------------------------------------------------------//
