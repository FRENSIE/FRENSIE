//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_GeneralEstimatorDimensionDiscretization.hpp
//! \author Alex Robinson
//! \brief  General estimator dimension discretization class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_GENERAL_ESTIMATOR_DIMENSION_DISCRETIZATION_DEF_HPP
#define MONTE_CARLO_GENERAL_ESTIMATOR_DIMENSION_DISCRETIZATION_DEF_HPP

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
template<PhaseSpaceDimension dimension>
GeneralEstimatorDimensionDiscretization<dimension>::GeneralEstimatorDimensionDiscretization( const InputArray& dimension_bin_boundaries )
  : BaseEstimatorDimensionDiscretization( dimension, dimension_bin_boundaries )
{
  // Make sure the bins bounds are valid
  testPrecondition( GeneralEstimatorDimensionDiscretizationHelper<dimension>::areInputArrayBoundsValid( dimension_bin_boundaries ) );
}

// Return the dimension name that has been discretized
template<PhaseSpaceDimension dimension>
inline std::string GeneralEstimatorDimensionDiscretization<dimension>::getDimensionName() const
{
  return DT::name();
}

// Check if the value is contained in the dimension discretization
template<PhaseSpaceDimension dimension>
inline bool GeneralEstimatorDimensionDiscretization<dimension>::isValueInDiscretization(
            const EstimatorParticleStateWrapper& particle_state_wrapper ) const
{
  return this->isValueInDiscretization(
                      getDimensionValue<dimension>( particle_state_wrapper ) );
}

// Check if the value is contained in the dimension discretization
template<PhaseSpaceDimension dimension>
inline bool GeneralEstimatorDimensionDiscretization<dimension>::isValueInDiscretization(
                                          const boost::any& any_value ) const
{
  return this->isValueInDiscretization(
                                   getDimensionValue<dimension>( any_value ) );
}W

// Calculate the index of bins that the value falls in
template<PhaseSpaceDimension dimension>
void GeneralEstimatorDimensionDiscretization<dimension>::calculatecalculateBinIndicesOfValue(
                   const EstimatorParticleStateWrapper& particle_state_wrapper,
                   BinIndexArray& bin_indices ) const
{
  // Make sure the value is in the dimension discretization
  testPrecondition( this->isValueInDiscretization( particle_state_wrapper ) );

  return this->calculateBinIndicesOfValue(
                        getDimensionValue<dimension>( particle_state_wrapper ),
                        bin_indices );
}

// Calculate the index of the bin that the value falls in
template<PhaseSpaceDimension dimension>
void GeneralEstimatorDimensionDiscretization<dimension>::calculateBinIndicesOfValue(
                                             const boost::any& any_value,
                                             BinIndexArray& bin_indices ) const
{
  // Make sure that the value is in the dimension discretization
  testPrecondition( this->isValueInDiscretization( any_value ) );

  return this->calculateBinIndicesOfValue(
                                     getDimensionValue<dimension>( any_value ),
                                     bin_indices );
}

// Calculate the index of bins that the value range falls in
template<PhaseSpaceDimension dimension>
void GeneralEstimatorDimensionDiscretization<dimension>::calculateBinIndicesOfRange(
                   const EstimatorParticleStateWrapper& particle_state_wrapper,
                   BinIndexWeightPairArray& bin_indices_and_weights ) const
{
  // Make sure that the value is in the dimension discretization
  testPrecondition( this->doesRangeIntersectDiscretization( particle_state_wrapper ) );

  typename DT::dimensionType range_start, range_end;

  getDimensionRange<dimension>( particle_state_wrapper,
                                range_start,
                                range_end );

  this->calculateBinIndicesOfRange( range_start, range_end, bin_indices_and_weights );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_GENERAL_ESTIMATOR_DIMENSION_DISCRETIZATION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_GeneralEstimatorDimensionDiscretization_def.hpp
//---------------------------------------------------------------------------//
