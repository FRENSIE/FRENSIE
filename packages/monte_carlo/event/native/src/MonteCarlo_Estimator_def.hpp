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

// Set the bin boundaries for a dimension of the sphase space
template<PhaseSpaceDimension dimension, typename InputDataType>
void Estimator::setBinBoundaries( const InputDataType& bin_data )
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
template<template<typename,...> class STLCompliantContainer>
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

//! Set the particle types that can contribute to the estimator
template<template<typename,...> class STLCompliantContainer>
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

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_Estimator_def.hpp
//---------------------------------------------------------------------------//
