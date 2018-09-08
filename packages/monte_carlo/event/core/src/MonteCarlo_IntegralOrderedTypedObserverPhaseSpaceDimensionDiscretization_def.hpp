//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization_def.hpp
//! \author Alex Robinson
//! \brief  Integral ordered typed observer phase space dimension
//!         discretization definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_INTEGRAL_ORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_DEF_HPP
#define MONTE_CARLO_INTEGRAL_ORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_DEF_HPP

// Std Lib Includes
#include <type_traits>

// FRENSIE Includes
#include "Utility_DesignByContract.hpp"
#include "Utility_SearchAlgorithms.hpp"

namespace MonteCarlo{

// Default constructor
template<ObserverPhaseSpaceDimension dimension>
IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization()
{ 
  // Make sure that the dimension type is a floating point type
  testStaticPrecondition((std::is_integral<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType>::value));
}

// Constructor
template<ObserverPhaseSpaceDimension dimension>
IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization(
                             const BinBoundaryArray& dimension_bin_boundaries )
  : OrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>( dimension_bin_boundaries )
{
  // Make sure that there is at least one bin
  testPrecondition( dimension_bin_boundaries.size() >= 1 );

  // Make sure that the dimension type is a floating point type
  testStaticPrecondition((std::is_integral<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType>::value));
}

// Return the number of bins in the discretization
template<ObserverPhaseSpaceDimension dimension>
size_t IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::getNumberOfBins() const
{
  return this->getBinBoundaries().size();
}

// Print the boundaries of a bin
template<ObserverPhaseSpaceDimension dimension>
void IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::printBoundariesOfBin(
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

// Check if the value is contained in the discretization
template<ObserverPhaseSpaceDimension dimension>
bool IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::isValueInDiscretization(
                                         const DimensionValueType value ) const
{
  return value <= this->getBinBoundaries().back();
}

// Check if the value range intersects the discretization
template<ObserverPhaseSpaceDimension dimension>
bool IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::doesRangeIntersectDiscretization(
                                     const DimensionValueType range_start,
                                     const DimensionValueType range_end ) const
{
  // Make sure that the range is valid
  testPrecondition( range_start <= range_end );

  return range_start <= this->getBinBoundaries().back();
}

// Calculate the index of the bin  that the value falls in
template<ObserverPhaseSpaceDimension dimension>
size_t IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::calculateBinIndexOfValue(
                                         const DimensionValueType value ) const
{
  // Make sure the value is in the discretization
  testPrecondition( this->isValueInDiscretization( value ) );

  return Utility::Search::binaryUpperBoundIndex(
                                              this->getBinBoundaries().begin(),
                                              this->getBinBoundaries().end(),
                                              value );
}

// Calculate the size of a bin
template<ObserverPhaseSpaceDimension dimension>
double IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::calculateBinSize(
                                                 const size_t bin_index ) const
{
  // Make sure that the bin index is valid
  testPrecondition( bin_index < this->getNumberOfBins() );

  if( bin_index == 0 )
    return this->getBinBoundaries().front() + 1; // +1 from counting zero
  else
  {
    return this->getBinBoundaries()[bin_index] -
      this->getBinBoundaries()[bin_index-1];
  }
}

// Calculate the size of a bin intersection
template<ObserverPhaseSpaceDimension dimension>
double IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::calculateBinIntersectionSize(
                                     const size_t bin_index,
                                     const DimensionValueType range_start,
                                     const DimensionValueType range_end ) const
{
  // Make sure that the bin index is valid
  testPrecondition( bin_index < this->getNumberOfBins() );

  DimensionValueType intersection_start_value;

  if( bin_index == 0 )
    intersection_start_value = range_start;
  else
  {
    if( range_start <= this->getBinBoundaries()[bin_index-1] )
      intersection_start_value = this->getBinBoundaries()[bin_index-1] + 1;
    else
      intersection_start_value = range_start;
  }

  DimensionValueType intersection_end_value;

  if( range_end > this->getBinBoundaries()[bin_index] )
    intersection_end_value = this->getBinBoundaries()[bin_index];
  else
    intersection_end_value = range_end;

  return this->calculateRangeSize( range_start, range_end );
}

// Calculate the size of a range
/*! \details Both the start and end value of the range are included in the
 * range. Therefore the range size equals (range_end - range_start) + 1.
 */
template<ObserverPhaseSpaceDimension dimension>
double IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::calculateRangeSize(
                                     const DimensionValueType range_start,
                                     const DimensionValueType range_end ) const
{
  return range_end - range_start + 1;
}

// Serialize the discretization
template<ObserverPhaseSpaceDimension dimension>
template<typename Archive>
void IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::serialize( Archive& ar, const unsigned version )
{
  // Serialize the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );
}

} // end MonteCarlo namespace

BOOST_CLASS_EXPORT_KEY2( MonteCarlo::IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION>,
                         "IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_COLLISION_NUMBER_DIMENSION>" );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION> );

#endif // end MONTE_CARLO_INTEGRAL_ORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization_def.hpp
//---------------------------------------------------------------------------//
