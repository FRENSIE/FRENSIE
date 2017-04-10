//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ImportanceSampledIndependentPhaseSpaceDimensionDistribution_def.hpp
//! \author Alex Robinson
//! \brief  Importance sampled independent phase space dimension distribution
//!         template definitions
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_IMPORTANCE_SAMPLED_INDEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_DEF_HPP
#define MONTE_CARLO_IMPORTANCE_SAMPLED_INDEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_DEF_HPP

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
template<PhaseSpaceDimension dimension>
ImportanceSampledIndependentPhaseSpaceDimensionDistribution<dimension>::ImportanceSampledIndependentPhaseSpaceDimensionDistribution(
                        const std::shared_ptr<const Utility::OneDDistribution>&
                        dimension_distribution,
                        const std::shared_ptr<const Utility::OneDDistribution>&
                        importance_distribution )
  : IndependentPhaseSpaceDimensionDistribution<dimension>( dimension_distribution ),
    d_dimension_importance_distribution( importance_distribution )
{
  // Make sure that the dimension distribution is valid
  testPrecondition( dimension_distribution.get() );
  // Make sure that the importance distribution is valid
  testPrecondition( importance_distribution.get() );
  testPrecondition( importance_distribution->hasSameBounds( *dimension_distribution ) );
}

// Sample a dimension value without a cascade to the dependent dists.
/*! \details A phase space dimension value will be sampled from the importance
 * distribution. The weight of the dimension will be the ratio of the
 * dimension distribution PDF and the importance distribution PDF at the 
 * sampled dimension value. This preserves the expected value of the phase
 * space dimension distribution.
 */
template<PhaseSpaceDimension dimension>
void ImportanceSampledIndependentPhaseSpaceDimensionDistribution<dimension>::sampleWithoutCascade(
                                    PhaseSpacePoint& phase_space_sample ) const
{
  const double sample = d_dimension_importance_distribution->sample();

  const double weight = this->calculateSampleWeight( sample );

  setCoordinate<dimension>( phase_space_sample, sample );
  setCoordinateWeight<dimension>( phase_space_sample, weight );
}

// Sample a dimension value without a cascade to the dependent dists.
template<PhaseSpaceDimension dimension>
void ImportanceSampledIndependentPhaseSpaceDimensionDistribution<dimension>::sampleAndRecordTrialsWithoutCascade(
                                  PhaseSpacePoint& phase_space_sample,
                                  ModuleTraits::InternalCounter& trials ) const
{
  const double sample =
    d_dimension_importance_distribution->sampleAndRecordTrials( trials );

  const double weight = this->calculateSampleWeight( sample );

  setCoordinate<dimension>( phase_space_sample, sample );
  setCoordinateWeight<dimension>( phase_space_sample, weight );
}

// Calculate the weight of a sample
template<PhaseSpaceDimension dimension>
double ImportanceSampledIndependentPhaseSpaceDimensionDistribution<dimension>::calculateSampleWeight(
                                          const double dimension_sample ) const
{
  const double weight_numerator =
    this->evaluatePDFWithoutCascade( dimension_sample );

  const double weight_denominator =
    d_dimension_importance_distribution->evaluatePDF( dimension_sample );

  double weight = 1.0;

  if( weight_denominator > 0.0 )
    weight = weight_numerator/weight_denominator;
  
  // If we enter this block there is likely a problem with our distributions
  else
  {
    if( weight_numerator > 0.0 )
      weight = std::numeric_limits<double>::infinity();
    
    // If both evaluate to 0, a weight of 1 is desired but nan will result
    else
      weight = 1.0;
  }

  // Make sure that the weight is valid
  testPostcondition( !Teuchos::ScalarTraits<double>::isnaninf( weight ) );
  testPostcondition( weight > 0.0 );
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_IMPORTANCE_SAMPLED_INDEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ImportanceSampledIndependentPhaseSpaceDimensionDistribution_def.hpp
//---------------------------------------------------------------------------//
