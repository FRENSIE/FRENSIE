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
#include "Utility_ContractException.hpp"

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
            const EstimatorParticleStateWrapper& particle_state_wrapper ) const
{
  return this->isValueInDiscretization(
                      getDimensionValue<dimension>( particle_state_wrapper ) );
}

// Check if the value is contained in the discretization
template<ObserverPhaseSpaceDimension dimension>
bool TypedObserverPhaseSpaceDimensionDiscretization<dimension>::isValueInDiscretization(
                                          const Teuchos::any& any_value ) const
{
  return this->isValueInDiscretization(
                                   getDimensionValue<dimension>( any_value ) );
}

// Check if the range intersects the discretization
template<ObserverPhaseSpaceDimension dimension>
bool TypedObserverPhaseSpaceDimensionDiscretization<dimension>::doesRangeIntersectDiscretization(
            const EstimatorParticleStateWrapper& particle_state_wrapper ) const
{
  DimensionValueType range_start, range_end;

  getDimensionRange<dimension>( particle_state_wrapper,
                                range_start,
                                range_end );

  return this->doesRangeIntersectDiscretization( range_start, range_end );
}

// Calculate the index of bins that the value falls in
template<ObserverPhaseSpaceDimension dimension>
void TypedObserverPhaseSpaceDimensionDiscretization<dimension>::calculateBinIndicesOfValue(
                   const EstimatorParticleStateWrapper& particle_state_wrapper,
                   BinIndexArray& bin_indices ) const
{
  // Make sure that the value is in the discretization
  testPrecondition( this->isValueInDiscretization( particle_state_wrapper ) );
  
  this->calculateBinIndicesOfValue(
                        getDimensionValue<dimension>( particle_state_wrapper ),
                        bin_indices );
}

// Calculate the index of bins that the value falls in
template<ObserverPhaseSpaceDimension dimension>
void TypedObserverPhaseSpaceDimensionDiscretization<dimension>::calculateBinIndicesOfValue(
                   const EstimatorParticleStateWrapper& particle_state_wrapper,
                   BinIndexWeightPairArray& bin_indices_and_weights ) const
{
  // Make sure that the value is in the discretization
  testPrecondition( this->isValueInDiscretization( particle_state_wrapper ) );
  
  this->calculateBinIndicesOfValue(
                        getDimensionValue<dimension>( particle_state_wrapper ),
                        bin_indices_and_weighs );
}

// Calculate the index of bins that the value falls in
template<ObserverPhaseSpaceDimension dimension>
void TypedObserverPhaseSpaceDimensionDiscretization<dimension>::calculateBinIndicesOfValue(
                                             const Teuchos::any& any_value,
                                             BinIndexArray& bin_indices ) const
{
  // Make sure that the value is in the discretization
  testPrecondition( this->isValueInDiscretization( any_value ) );
  
  this->calculateBinIndicesOfValue( getDimensionValue<dimension>( any_value ),
                                    bin_indices );
}

// Calculate the index of bins that the value range falls in
template<ObserverPhaseSpaceDimension dimension>
void TypedObserverPhaseSpaceDimensionDiscretization<dimension>::calculateBinIndicesOfRange(
                   const EstimatorParticleStateWrapper& particle_state_wrapper,
                   BinIndexWeightPairArray& bin_indices_and_weights ) const
{
  // Make sure that the range intersects the discretization
  testPrecondition( this->doesRangeIntersectDiscretization( particle_state_wrapper ) );
  
  DimensionValueType range_start, range_end;

  getDimensionRange<dimension>( particle_state_wrapper,
                                range_start,
                                range_end );

  this->calculateBinIndicesOfRange( range_start,
                                    range_end,
                                    bin_indices_and_weights );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_TYPED_ESTIMATOR_DIMENSION_DISCRETIZATION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_TypedObserverPhaseSpaceDimensionDiscretization_def.hpp
//---------------------------------------------------------------------------//
