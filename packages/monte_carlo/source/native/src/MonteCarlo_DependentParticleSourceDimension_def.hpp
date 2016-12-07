//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DependentParticleSourceDimenion_def.hpp
//! \author Alex Robinson
//! \brief  Dependent particle source dimension class template definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DEPENDENT_PARTICLE_SOURCE_DIMENSION_DEF_HPP
#define MONTE_CARLO_DEPENDENT_PARTICLE_SOURCE_DIMENSION_DEF_HPP

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
template<ParticleSourceDimensionType indep_dimension,
         ParticleSourceDimensionType dep_dimension>
DependentParticleSourceDimension<indep_dimension,dep_dimension>::DependentParticleSourceDimension(
            const std::shared_ptr<const Utility::FullyTabularTwoDDistribution>&
            dimension_distribution )
  : d_dimension_distribution( dimension_distribution )
{
  // Make sure that the dimension distribution is valid
  testPrecondition( dimension_distribution.get() );
}

// Return the dependent dimension type
template<ParticleSourceDimensionType indep_dimension,
         ParticleSourceDimensionType dep_dimension>
ParticleSourceDimensionType DependentParticleSourceDimension<indep_dimension,dep_dimension>::getDimensionType() const override
{
  return dep_dimension;
}

// Return the independent dimension type
template<ParticleSourceDimensionType indep_dimension,
         ParticleSourceDimensionType dep_dimension>
ParticleSourceDimensionType DependentParticleSourceDimension<indep_dimension,dep_dimension>::getIndepDimensionType() const
{
  return indep_dimension;
}

// Check if the dimension is independent
template<ParticleSourceDimensionType indep_dimension,
         ParticleSourceDimensionType dep_dimension>
bool DependentParticleSourceDimension<indep_dimension,dep_dimension>::isIndependent() const override
{
  return false;
}

// Check if the dimension is dependent on the dimension of interest
template<ParticleSourceDimensionType indep_dimension,
         ParticleSourceDimensionType dep_dimension>
bool DependentParticleSourceDimension<indep_dimension,dep_dimension>::isDependentOnDimension(
                   const ParticleSourceDimensionType dimension ) const override
{
  return dimension == indep_dimension;
}

// Set the dimension importance distribution
template<ParticleSourceDimensionType indep_dimension,
         ParticleSourceDimensionType dep_dimension>
void DependentParticleSourceDimension<indep_dimension,dep_dimension>::setImportanceDistribution(
            const std::shared_ptr<const Utility::FullyTabularTwoDDistribution>&
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
template<ParticleSourceDimensionType indep_dimension,
         ParticleSourceDimensionType dep_dimension>
void DependentParticleSourceDimension<indep_dimension,dep_dimension>::sampleDimension(
             ParticleSourcePhaseSpacePoint& phase_space_sample ) const override
{
  double sample;
  double weight = 1.0;

  double indep_dimension_value =
    phase_space_sample.getCoordinate<indep_dimension>();

  if( !d_dimension_importance_distribution.get() )
  {
    sample = d_dimension_distribution->sampleSecondaryConditionalExact(
                                                       indep_dimension_value );
  }
  // Use importance sampling
  else
  {
    sample = d_dimension_importance_distribution->sampleSecondaryConditionalExact(
                                                       indep_dimension_value );

    double weight_numerator =
      d_dimension_distribution->evaluateSecondaryConditionalPDF(
                                               indep_dimension_value, sample );

    double weight_denominator =
      d_dimension_importance_distribution->evaluateSecondaryConditionalPDF(
                                               indep_dimension_value, sample );

    // If both evaluate to 0, a weight of 1 is desired but nan will result
    if( weight_numerator > 0.0 || weight_denominator > 0.0 )
      weight = weight_numerator/weight_denominator;
  }

  // Make sure that the weight is valid
  testPostcondition( !Teuchos::ScalarTraits<double>::isnaninf( weight ) );
  testPostcondition( weight > 0.0 );

  phase_space_sample.setCoordinate<dep_dimension>( sample );
  phase_space_sample.setCoordinateWeight<dep_dimension>( weight );
}

// Set the value for this dimension only
template<ParticleSourceDimensionType indep_dimension,
         ParticleSourceDimensionType dep_dimension>
void DependentParticleSourceDimension<indep_dimension,dep_dimension>::setDimensionValue(
                                  ParticleSourcePhasePoint& phase_space_sample,
                                  const double dimension_value ) const override
{
  double indep_dimension_value =
    phase_space_sample.getCoordinate<indep_dimension>();
  
  double weight = d_dimension_distribution->evaluateSecondaryConditionalPDF(
                                      indep_dimension_value, dimension_value );

  // Make sure that the weight is valid
  testPostcondition( weight > 0.0 );

  phase_space_sample.setCoordinate<dep_dimension>( dimension_value );
  phase_space_sample.setCoordinateWeight<dep_dimension>( weight );
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DEPENDENT_PARTICLE_SOURCE_DIMENSION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DependentParticleSourceDimension_def.hpp
//---------------------------------------------------------------------------//
