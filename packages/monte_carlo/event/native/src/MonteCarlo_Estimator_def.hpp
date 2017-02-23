//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_Estimator_def.hpp
//! \author Alex Robinson
//! \brief  Estimator base class template definitions
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ESTIMATOR_DEF_HPP
#define MONTE_CARLO_ESTIMATOR_DEF_HPP

// FRENSIE Includes
#include "MonteCarlo_DefaultTypedObserverPhaseSpaceDimensionDiscretization.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Set the discretization for a dimension of the phase space
/*! \details This method is a factory method that will create
 * a phase space dimension discretization and assign it to the underlying
 * phase space discretization. Before it is added to the phase space 
 * discretization the object will determine if discretizations of the
 * phase space dimension are supported (e.g. cosine binning is not supported
 * in cell estimators).
 */
template<PhaseSpaceDimension dimension, typename InputDataType>
void Estimator::setDiscretization( const InputDataType& bin_data )
{
  // Make sure the DimensionType matches the type associated with the dimension
  testStaticPrecondition((boost::is_same<typename DefaultTypedObserverPhaseSpaceDimensionDiscretization<dimension>::InputDataType,InputDataType>::value));

  std::shared_ptr<ObserverPhaseSpaceDimensionDiscretization>
    dimension_bin_boundaries(
          new DefaultTypedObserverPhaseSpaceDimensionDiscretization<dimension>(
                                                                  bin_data ) );

  this->assignBins( dimension_bins );
}

// Set the response functions
/*! \details Before the response functions are assigned, the object will check
 * if each response function is compatible with the estimator type (e.g. cell
 * track-length flux estimators are only compatible with spatially uniform
 * response functions).
 */
template<template<typename,typename...> class STLCompliantContainer>
void Estimator::setResponseFunctions(
     const STLCompliantContainer<ResponseFunctionPointer>& response_functions )
{
  // Make sure that there is at least one response function
  testPrecondition( response_functions.size() > 0 );

  // Assign each response function individually
  STLCompliantContainer<ResponseFunctionPointer>::const_iterator
    response_function_it = response_functions.begin();

  while( response_function_it != response_functions.end() )
  {
    this->assignResponseFunction( *response_function_it );
    
    ++response_function_it;
  }
}

// Set the particle types that can contribute to the estimator
/*! \details Before each particle type is assigned the object will check
 * if the particle type is compatible with the estimator type (e.g. cell
 * pulse height estimators are not compatible with neutrons).
 */
template<template<typename,typename...> class STLCompliantContainer>
void Estimator::setParticleTypes(
                    const STLCompliantContainer<ParticleType>& particle_types )
{
  // Make sure that there is at least one particle type
  testPrecondition( particle_types.size() > 0 );

  // Assign each particle type individually
  STLCompliantContainer<ParticleType>::const_iterator
    particle_type_it = particle_types.begin();

  while( particle_type_it != particle_types.end() )
  {
    this->assignParticleType( *particle_type_it );

    ++particle_type_it;
  }
}

// Check if the point is in the estimator phase space
/*! \details The PointType should be either EstimatorParticleStateWrapper or
 * ObserverPhaseSpaceDiscretization::DimensionValueMap.
 */
template<typename PointType>
inline bool Estimator::isPointInEstimatorPhaseSpace(
		              const PointType& phase_space_point ) const
{
  return d_phase_space_discretization.doesRangeIntersectDiscretization(
                                                           phase_space_point );
}

// Check if the range intersects the estimator phase space
template<ObserverPhaseSpaceDimensions... RangeDimensions>
inline bool Estimator::doesRangeIntersectEstimatorPhaseSpace(
            const EstimatorParticleStateWrapper& particle_state_wrapper ) const
{
  return d_phase_space_discretization.doesRangeIntersectDiscretization<RangeDimensions...>( particle_state_wrapper );
}

// Calculate the bin index for the desired response function
/*! \details The PointType should be either EstimatorParticleStateWrapper or
 * ObserverPhaseSpaceDiscretization::DimensionValueMap.
 */
template<typename PointType>
void Estimator::calculateBinIndices(
                   const PointType& phase_space_point,
                   const size_t response_function_index,
                   ObserverPhaseSpaceDimensionDiscretization::BinIndexArray&
                   bin_indices ) const
{
  // Make sure the response function is valid
  testPrecondition( response_function_index <
                    this->getNumberOfResponseFunctions() );

  d_phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point,
                                                           bin_indices );

  // Add the response function index to each phase space bin index
  for( size_t i = 0; i < bin_indices.size(); ++i )
    bin_indices[i] += response_function_index*this->getNumberOfBins();
}

// Calculate the bin indices for the desired response function
template<ObserverPhaseSpaceDimension... RangeDimensions>
inline void Estimator::calculateBinIndicesAndWeightsOfRange(
            const EstimatorParticleStateWrapper& particle_state_wrapper,
            const size_t response_function_index,
            ObserverPhaseSpaceDimensionDiscretization::BinIndexWeightPairArray&
            bin_indices_and_weights ) const
{
  // Make sure the response function is valid
  testPrecondition( response_function_index <
                    this->getNumberOfResponseFunctions() );

  d_phase_space_discretization.calculateBinIndicesAndWeightsOfRange<RangeDimensions...>(
                                                     particle_state_wrapper,
                                                     bin_indices_and_weights );

  // Add the response function index to each phase space bin index
  for( size_t i = 0; i < bin_indices_and_weights.size(); ++i )
  {
    bin_indices_and_weights[i] +=
      response_function_index*this->getNumberOfBins();
  }
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_Estimator_def.hpp
//---------------------------------------------------------------------------//
