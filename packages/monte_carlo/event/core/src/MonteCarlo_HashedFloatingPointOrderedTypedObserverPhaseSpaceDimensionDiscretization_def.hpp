//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization_def.hpp
//! \author Alex Robinson
//! \brief  Hashed floating point typed observer phase space dimension
//!         discretization definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_HASHED_FLOATING_POINT_ORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_DEF_HPP
#define MONTE_CARLO_HASHED_FLOATING_POINT_ORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_DEF_HPP

// Std Lib Includes
#include <type_traits>

// FRENSIE Includes
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Default constructor
template<ObserverPhaseSpaceDimension dimension>
HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization()
  : BaseType()
{ 
  // Make sure that the dimension type is a floating point type
  testStaticPrecondition((std::is_floating_point<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType>::value));
}

// Constructor (with number of hash grid bins specified)
template<ObserverPhaseSpaceDimension dimension>
HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization(
                             const BinBoundaryArray& dimension_bin_boundaries )
  : HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization(
                                        dimension_bin_boundaries,
                                        dimension_bin_boundaries.size()/10+1 )
{ 
  // Make sure that the dimension type is a floating point type
  testStaticPrecondition((std::is_floating_point<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType>::value));
}

// Constructor (with number of hash grid bins specified)
template<ObserverPhaseSpaceDimension dimension>
HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization(
                              const BinBoundaryArray& dimension_bin_boundaries,
                              const unsigned hash_grid_bins )
  : BaseType( dimension_bin_boundaries ),
    d_grid_searcher( new Utility::StandardHashBasedGridSearcher<BinBoundaryArray,false>( this->getSharedBoundaries(), hash_grid_bins ) )
{ 
  // Make sure that the dimension type is a floating point type
  testStaticPrecondition((std::is_floating_point<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType>::value));
}

// Calculate the index of the bin  that the value falls in
template<ObserverPhaseSpaceDimension dimension>
size_t HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::calculateBinIndexOfValue(
                                         const DimensionValueType value ) const
{
  // Make sure the value is in the discretization
  testPrecondition( this->isValueInDiscretization( value ) );

  return d_grid_searcher->findLowerBinIndexIncludingUpperBound( value );
}

// Serialize the discretization
template<ObserverPhaseSpaceDimension dimension>
template<typename Archive>
void HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::serialize( Archive& ar, const unsigned version )
{
  // Serialize the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Serialize the local data
  ar & BOOST_SERIALIZATION_NVP( d_grid_searcher );
}

} // end MonteCarlo namespace

BOOST_CLASS_EXPORT_KEY2( MonteCarlo::HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION>,
                         "HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_COSINE_DIMENSION>" );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION> );

BOOST_CLASS_EXPORT_KEY2( MonteCarlo::HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION>,
                         "HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_SOURCE_ENERGY_DIMENSION>" );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION> );

BOOST_CLASS_EXPORT_KEY2( MonteCarlo::HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION>,
                         "HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_ENERGY_DIMENSION>" );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION> );

BOOST_CLASS_EXPORT_KEY2( MonteCarlo::HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION>,
                         "HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_SOURCE_TIME_DIMENSION>" );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION> );

BOOST_CLASS_EXPORT_KEY2( MonteCarlo::HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION>,
                         "HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_TIME_DIMENSION>" );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION> );

#endif // end MONTE_CARLO_HASHED_FLOATING_POINT_ORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization_def.hpp
//---------------------------------------------------------------------------//
