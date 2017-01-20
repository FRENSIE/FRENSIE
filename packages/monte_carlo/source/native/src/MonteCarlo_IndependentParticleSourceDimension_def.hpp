//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IndependentParticleSourceDimension_def.hpp
//! \author Alex Robinson
//! \brief  Independent particle source dimension class template definitions
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_INDEPENDENT_PARTICLE_SOURCE_DIMENSION_DEF_HPP
#define MONTE_CARLO_INDEPENDENT_PARTICLE_SOURCE_DIMENSION_DEF_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleSourceDimensionTraits.hpp"
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
ParticleSourceDimensionType IndependentParticleSourceDimension<dimension>::getDimensionType() const
{
  return dimension;
}

// Return the dimension class type
template<ParticleSourceDimensionType dimension>
ParticleSourceDimensionClassType IndependentParticleSourceDimension<dimension>::getDimensionClassType() const
{
  return ParticleSourceDimensionTraits<dimension>::getClass();
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

// Sample a value for this dimension only
/*! \details A phase space dimension value will be sampled from the
 * distribution that was specified. The weight of the dimension will be 1.0.
 */
template<ParticleSourceDimensionType dimension>
void IndependentParticleSourceDimension<dimension>::sampleDimension( ParticleSourcePhaseSpacePoint& phase_space_sample ) const
{
  const double sample = d_dimension_distribution->sample();
  
  setCoordinate<dimension>( phase_space_sample, sample );
  setCoordinateWeight<dimension>( phase_space_sample, 1.0 );
}

// Set the value for this dimension only
/*! \details The weight associated with the dimension will be the value
 * of the PDF at the specified dimension value.
 */
template<ParticleSourceDimensionType dimension>
void IndependentParticleSourceDimension<dimension>::setDimensionValue(
                                  ParticleSourcePhasePoint& phase_space_sample,
                                  const double dimension_value ) const override
{
  double weight = this->evaluateDimensionPDF( dimension_value );

  // Make sure that the weight is valid
  testPostcondition( weight > 0.0 );

  setCoordinate<dimension>( phase_space_sample, dimension_value );
  setCoordinateWeight<dimension>( phase_space_sample, weight );
}

// Evaluate the pdf of the dimension distribution
template<ParticleSourceDimensionType dimension>
inline double IndependentParticleSourceDimension<dimension>::evaluateDimensionPDF( const double dimension_value ) const
{
  return d_dimension_distribution->evaluatePDF( dimension_value );
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_INDEPENDENT_PARTICLE_SOURCE_DIMENSION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_IndependentParticleSourceDimension.cpp
//---------------------------------------------------------------------------//
