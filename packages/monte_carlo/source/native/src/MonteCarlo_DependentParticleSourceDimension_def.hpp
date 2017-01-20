//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DependentParticleSourceDimenion_def.hpp
//! \author Alex Robinson
//! \brief  Dependent particle source dimension class template definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DEPENDENT_PARTICLE_SOURCE_DIMENSION_DEF_HPP
#define MONTE_CARLO_DEPENDENT_PARTICLE_SOURCE_DIMENSION_DEF_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleSourceDimensionTraits.hpp"
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
ParticleSourceDimensionType DependentParticleSourceDimension<indep_dimension,dep_dimension>::getDimensionType() const
{
  return dep_dimension;
}

// Return the dimension class type
template<ParticleSourceDimensionType indep_dimension,
         ParticleSourceDimensionType dep_dimension>
ParticleSourceDimensionClassType DependentParticleSourceDimension<indep_dimension,dep_dimension>::getDimensionClassType() const
{
  return ParticleSourceDimensionTraits<dep_dimension>::getClass();
}

// Return the independent dimension type
template<ParticleSourceDimensionType indep_dimension,
         ParticleSourceDimensionType dep_dimension>
ParticleSourceDimensionType DependentParticleSourceDimension<indep_dimension,dep_dimension>::getIndepDimensionType() const
{
  return indep_dimension;
}

// Return the independent dimension class type
template<ParticleSourceDimensionType indep_dimension,
         ParticleSourceDimensionType dep_dimension>
ParticleSourceDimensionClassType DependentParticleSourceDimension<indep_dimension,dep_dimension>::getIndepDimensionClassType() const
{
  return ParticleSourceDimensionTraits<indep_dimension>::getClass();
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
                      ParticleSourcePhaseSpacePoint& phase_space_sample ) const
{
  const double sample =
    d_dimension_distribution->sampleSecondaryConditionalExact(
                        getCoordinate<indep_dimension>( phase_space_sample ) );

  setCoordinate<dep_dimension>( sample );
  setCoordinateWeight<dep_dimension>( 1.0 );
}

// Set the value for this dimension only
template<ParticleSourceDimensionType indep_dimension,
         ParticleSourceDimensionType dep_dimension>
void DependentParticleSourceDimension<indep_dimension,dep_dimension>::setDimensionValue(
                                  ParticleSourcePhasePoint& phase_space_sample,
                                  const double dimension_value ) const override
{
  const double weight = this->evaluateDimensionConditionalPDF(
                          getCoordinate<indep_dimension>( phase_space_sample ),
                          dimension_value );

  // Make sure that the weight is valid
  testPostcondition( weight > 0.0 );

  setCoordinate<dep_dimension>( phase_space_sample, dimension_value );
  setCoordinateWeight<dep_dimension>( phase_space_sample, weight );
}

// Evaluate the conditional pdf of the dimension distribution
template<ParticleSourceDimensionType indep_dimension,
         ParticleSourceDimensionType dep_dimension>
inline double DependentParticleSourceDimension<indep_dimension,dep_dimension>::evaluateDimensionConditionalPDF(
                                           const double indep_dimension_value,
                                           const double dimension_value ) const
{
  return d_dimension_distribution->evaluateSecondaryConditionalPDF(
                                      indep_dimension_value, dimension_value );
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DEPENDENT_PARTICLE_SOURCE_DIMENSION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DependentParticleSourceDimension_def.hpp
//---------------------------------------------------------------------------//
