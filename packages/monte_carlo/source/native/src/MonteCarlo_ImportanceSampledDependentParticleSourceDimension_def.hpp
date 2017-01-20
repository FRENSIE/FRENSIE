//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ImportanceSampledDependentParticleSourceDimension_def.hpp
//! \author Alex Robinson
//! \brief  Importance sampled dependent particle source dimension template
//!         definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_IMPORTANCE_SAMPLED_DEPENDENT_PARTICLE_SOURCE_DIMENSION_DEF_HPP
#define MONTE_CARLO_IMPORTANCE_SAMPLED_DEPENDENT_PARTICLE_SOURCE_DIMENSION_DEF_HPP

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleSourceDimensionTraits.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
template<ParticleSourceDimensionType indep_dimension,
         ParticleSourceDimensionType dep_dimension>
ImportanceSampledDependentParticleSourceDimension<indep_dimension,dep_dimension>::ImportanceSampledDependentParticleSourceDimension(
            const std::shared_ptr<const Utility::FullyTabularTwoDDistribution>&
            dimension_distribution,
            const std::shared_ptr<const Utility::FullyTabularTwoDDistribution>&
            importance_distribution )
  : DependentParticleSourceDimension<indep_dimension,dep_dimension>( dimension_distribution )
{
  // Make sure that the dimension distribution is valid
  testPrecondition( dimension_distribution.get() );
  // Make sure that the importance distribution is valid
  testPrecondition( importance_distribution.get() );
  testPrecondition( importance_distribution->hasSamePrimaryBounds( dimension_distribution ) );
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
void ImportanceSampledDependentParticleSourceDimension<indep_dimension,dep_dimension>::sampleDimension(
                      ParticleSourcePhaseSpacePoint& phase_space_sample ) const
{
  const double indep_dimension_value =
    getCoordinate<indep_dimension>( phase_space_sample );
  
  const double sample =
    d_dimension_importance_distribution->sampleSecondaryConditionalExact(
                                                       indep_dimension_value );

  const double weight_numerator =
    this->evaluateDimensionConditionalPDF( indep_dimension_value, sample );

  const double weight_denominator =
    d_dimension_importance_distribution->evaluateSecondaryConditionalPDF(
                                               indep_dimension_value, sample );

  double weight = 1.0;

  // If both evaluate to 0, a weight of 1 is desired but nan will result
  if( weight_numerator > 0.0 || weight_denominator > 0.0 )
    weight = weight_numerator/weight_denominator;

  // Make sure that the weight is valid
  testPostcondition( !Teuchos::ScalarTraits<double>::isnaninf( weight ) );
  testPostcondition( weight > 0.0 );

  setCoordinate<dep_dimension>( phase_space_sample, sample );
  setCoordinateWeight<dep_dimension>( phase_space_sample, weight );
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_IMPORTANCE_SAMPLED_DEPENDENT_PARTICLE_SOURCE_DIMENSION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ImportanceSampledDependentParticleSourceDimension_def.hpp
//---------------------------------------------------------------------------//
