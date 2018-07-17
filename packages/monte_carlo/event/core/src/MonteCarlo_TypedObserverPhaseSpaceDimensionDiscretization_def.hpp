//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_TypedObserverPhaseSpaceDimensionDiscretization_def.hpp
//! \author Alex Robinson
//! \brief  Typed observer phase space dimension discretization base class
//!         template definitions
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_TYPED_ESTIMATOR_DIMENSION_DISCRETIZATION_DEF_HPP
#define MONTE_CARLO_TYPED_ESTIMATOR_DIMENSION_DISCRETIZATION_DEF_HPP

// FRENSIE Includes
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Return the dimension that has been discretized
template<ObserverPhaseSpaceDimension dimension>
ObserverPhaseSpaceDimension
TypedObserverPhaseSpaceDimensionDiscretization<dimension>::getDimension() const
{
  return dimension;
}

// Return the dimension name that has been discretized
template<ObserverPhaseSpaceDimension dimension>
std::string
TypedObserverPhaseSpaceDimensionDiscretization<dimension>::getDimensionName() const
{
  return DT::name();
}

// Check if the value is in the discretization
template<ObserverPhaseSpaceDimension dimension>
bool TypedObserverPhaseSpaceDimensionDiscretization<dimension>::isValueInDiscretization(
            const ObserverParticleStateWrapper& particle_state_wrapper ) const
{
  return this->isValueInDiscretization(
          MonteCarlo::getDimensionValue<dimension>( particle_state_wrapper ) );
}

// Check if the value is contained in the discretization
template<ObserverPhaseSpaceDimension dimension>
bool TypedObserverPhaseSpaceDimensionDiscretization<dimension>::isValueInDiscretization(
                                          const boost::any& any_value ) const
{
  return this->isValueInDiscretization(
                       MonteCarlo::getDimensionValue<dimension>( any_value ) );
}

// Check if the range intersects the discretization
template<ObserverPhaseSpaceDimension dimension>
bool TypedObserverPhaseSpaceDimensionDiscretization<dimension>::doesRangeIntersectDiscretization(
            const ObserverParticleStateWrapper& particle_state_wrapper ) const
{
  DimensionValueType range_start, range_end;

  MonteCarlo::getDimensionRange<dimension>( particle_state_wrapper,
                                            range_start,
                                            range_end );

  return this->doesRangeIntersectDiscretization( range_start, range_end );
}

// Calculate the index of bins that the value falls in
template<ObserverPhaseSpaceDimension dimension>
void TypedObserverPhaseSpaceDimensionDiscretization<dimension>::calculateBinIndicesOfValue(
                   const ObserverParticleStateWrapper& particle_state_wrapper,
                   BinIndexArray& bin_indices ) const
{
  // Make sure that the value is in the discretization
  testPrecondition( this->isValueInDiscretization( particle_state_wrapper ) );
  
  this->calculateBinIndicesOfValue(
            MonteCarlo::getDimensionValue<dimension>( particle_state_wrapper ),
            bin_indices );
}

// Calculate the index of bins that the value falls in
template<ObserverPhaseSpaceDimension dimension>
void TypedObserverPhaseSpaceDimensionDiscretization<dimension>::calculateBinIndicesOfValue(
                   const ObserverParticleStateWrapper& particle_state_wrapper,
                   BinIndexWeightPairArray& bin_indices_and_weights ) const
{
  // Make sure that the value is in the discretization
  testPrecondition( this->isValueInDiscretization( particle_state_wrapper ) );
  
  this->calculateBinIndicesOfValue(
            MonteCarlo::getDimensionValue<dimension>( particle_state_wrapper ),
            bin_indices_and_weights );
}

// Calculate the index of bins that the value falls in
template<ObserverPhaseSpaceDimension dimension>
void TypedObserverPhaseSpaceDimensionDiscretization<dimension>::calculateBinIndicesOfValue(
                                             const boost::any& any_value,
                                             BinIndexArray& bin_indices ) const
{
  // Make sure that the value is in the discretization
  testPrecondition( this->isValueInDiscretization( any_value ) );
  
  this->calculateBinIndicesOfValue(
                         MonteCarlo::getDimensionValue<dimension>( any_value ),
                         bin_indices );
}

// Calculate the index of bins that the value range falls in
template<ObserverPhaseSpaceDimension dimension>
void TypedObserverPhaseSpaceDimensionDiscretization<dimension>::calculateBinIndicesOfRange(
                   const ObserverParticleStateWrapper& particle_state_wrapper,
                   BinIndexWeightPairArray& bin_indices_and_weights ) const
{
  // Make sure that the range intersects the discretization
  testPrecondition( this->doesRangeIntersectDiscretization( particle_state_wrapper ) );
  
  DimensionValueType range_start, range_end;

  MonteCarlo::getDimensionRange<dimension>( particle_state_wrapper,
                                            range_start,
                                            range_end );

  this->calculateBinIndicesOfRange( range_start,
                                    range_end,
                                    bin_indices_and_weights );
}

// Serialize the discretization
template<ObserverPhaseSpaceDimension dimension>
template<typename Archive>
void TypedObserverPhaseSpaceDimensionDiscretization<dimension>::serialize( Archive& ar, const unsigned version )
{
  // Serialize the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ObserverPhaseSpaceDimensionDiscretization );
}

} // end MonteCarlo namespace

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::TypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, TypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::TypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, TypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::TypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, TypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::TypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, TypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::TypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, TypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::TypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, TypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::TypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, TypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION> );

#endif // end MONTE_CARLO_TYPED_ESTIMATOR_DIMENSION_DISCRETIZATION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_TypedObserverPhaseSpaceDimensionDiscretization_def.hpp
//---------------------------------------------------------------------------//
