//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ImportanceSampledIndependentParticleSourceDimension_def.hpp
//! \author Alex Robinson
//! \brief  Importance sampled independent particle source dimension class
//!         template defs.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_IMPORTANCE_SAMPLED_INDEPENDENT_PARTICLE_SOURCE_DIMENSION_DEF_HPP
#define MONTE_CARLO_IMPORTANCE_SAMPLED_INDEPENDENT_PARTICLE_SOURCE_DIMENSION_DEF_HPP

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleSourceDimensionTraits.hpp"
#include "Utiilty_ContractException.hpp"

namespace MonteCarlo{

// Constructor
template<ParticleSourceDimensionType dimension>
ImportanceSampledIndependentParticleSourceDimension<dimension>::ImportanceSampledIndependentParticleSourceDimension(
                        const std::shared_ptr<const Utility::OneDDistribution>&
                        dimension_distribution,
                        const std::shared_ptr<const Utility::OneDDistribution>&
                        importance_distribution )
  : IndependentParticleSourceDimension<dimension>( dimension_distribution ),
  d_importance_distribution( importance_distribution )
{
  // Make sure that the dimension distribution is valid
  testPrecondition( dimension_distribution.get() );
  // Make sure that the importance distribution is valid
  testPrecondition( importance_distribution.get() );
  testPrecondition( importance_distribution->hasSameBounds( dimension_distribution ) );
}

// Sample a value for this dimension only
/*! \details A phase space dimension value will be sampled from the importance
 * distribution. The weight of the dimension will be the ratio of the
 * dimension distribution PDF and the importance distribution PDF at the
 * sampled dimension value.
 */
void ImportanceSampledIndependentParticleSourceDimension<dimension>::sampleDimension( ParticleSourcePhaseSpacePoint& phase_space_sample ) const
{
  const double sample = d_dimension_importance_distribution->sample();

  const double weight_numerator = this->evaluateDimensionPDF( sample );

  const double weight_denominator =
    d_importance_distribution->evaluatePDF( sample );

  double weight = 1.0;
  
  // If both evaluate to 0, a weight of 1 is desired but nan will result
  if( weight_numerator > 0.0 || weight_denominator > 0.0 )
    weight = weight_numerator/weight_denominator;

  // Make sure that the weight is valid
  testPostcondition( !Teuchos::ScalarTraits<double>::isnaninf( weight ) );
  testPostcondition( weight > 0.0 );

  setCoordinate<dimension>( phase_space_sample, sample );
  setCoordinateWeight<dimension>( phase_space_sample, weight );
}

} // end MonteCarlo namespace

#endif MONTE_CARLO_IMPORTANCE_SAMPLED_INDEPENDENT_PARTICLE_SOURCE_DIMENSION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ImportanceSampledIndependentParticleSourceDimension_def.hpp
//---------------------------------------------------------------------------//
