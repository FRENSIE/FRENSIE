//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IndependentParticleSourceDimension_def.hpp
//! \author Alex Robinson
//! \brief  Independent particle source dimension class template definitions
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_INDEPENDENT_PARTICLE_SOURCE_DIMENSION_DEF_HPP
#define MONTE_CARLO_INDEPENDENT_PARTICLE_SOURCE_DIMENSION_DEF_HPP

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
template<ParticleSourceDimensionType dimension>
IndependentParticleSourceDimension<dimension>::IndependentParticleSourceDimension(
                        const std::shared_ptr<const Utility::OneDDistribution>&
                        dimension_distribution )
  : d_dimension_distribution( dimension_distribution )
{
  // Make sure that the dimension distribution is valid
  testPrecondition( dimension_distribution.get() );
}

// Return the dimension type
template<ParticleSourceDimensionType dimension>
ParticleSourceDimensionType IndependentParticleSourceDimension<dimension>::getDimensionType() const override
{
  return dimension;
}

// Check if the dimension is independent
template<ParticleSourceDimensionType dimension>
bool IndependentParticleSourceDimension<dimension>::isIndependent() const override
{
  return true;
}

// Check if the dimension is dependent on the dimension of interest
template<ParticleSourceDimensionType dimension>
bool IndependentParticleSourceDimension<dimension>::isDependentOnDimension( const ParticleSourceDimensionType dimension ) const override
{
  return false;
}

// Set the dimension importance distribution
template<ParticleSourceDimensionType dimension>
void IndependentParticleSourceDimension<dimension>::setImportanceDistribution(
                        const std::shared_ptr<const Utility::OneDDistribution>&
                        importance_distribution )
{
  // Make sure that the importance distribution is valid
  testPrecondition( importance_distribution.get() );
  
  d_dimension_importance_distribution = importance_distribution;
}

// Sample a value for this dimension only
/*! \details A phase space dimension value will be sampled from the
 * distribution that was specified. If an importance function
 * has been set, the particle energy will instead be sampled from the
 * importance function with the weight of the particle multiplied by the
 * PDF value of the original function divided by the importance PDF value
 * corresponding to the sampled point.
 */
template<ParticleSourceDimensionType dimension>
void IndependentParticleSourceDimension<dimension>::sampleDimension( ParticleSourcePhaseSpacePoint& phase_space_sample ) const override
{
  double sample;
  double weight = 1.0;
  
  if( !d_dimension_importance_distribution.get() )
    sample = d_dimension_distribution->sample();
  // Use importance sampling
  else
  {
    sample = d_dimension_importance_distribution->sample();

    double weight_numerator =
      d_dimension_distribution->evaluatePDF( sample );

    double weight_denominator =
      d_dimension_importance_distribution->evaluatePDF( sample );

    // If both evaluate to 0, a weight of 1 is desired but nan will result
    if( weight_numerator > 0.0 || weight_denominator > 0.0 )
      weight = weight_numerator/weight_denominator;
  }

  // Make sure that the weight is valid
  testPostcondition( !Teuchos::ScalarTraits<double>::isnaninf( weight ) );
  testPostcondition( weight > 0.0 );

  phase_space_sample.setCoordinate<dimension>( sample );
  phase_space_sample.setCoordinateWeight<dimension>( weight );
}

// Set the value for this dimension only
template<ParticleSourceDimensionType dimension>
void IndependentParticleSourceDimension<dimension>::setDimensionValue(
                                  ParticleSourcePhasePoint& phase_space_sample,
                                  const double dimension_value ) const override
{
  double weight = d_dimension_distribution->evaluatePDF( dimension_value );

  // Make sure that the weight is valid
  testPostcondition( weight > 0.0 );

  phase_space_sample.setCoordinate<dimension>( dimension_value );
  phase_space_sample.setCoordinateWeight<dimension>( weight );
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_INDEPENDENT_PARTICLE_SOURCE_DIMENSION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_IndependentParticleSourceDimension.cpp
//---------------------------------------------------------------------------//
