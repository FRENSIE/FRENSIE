//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardImportanceSampledDependentPhaseSpaceDimensionDistribution_def.hpp
//! \author Alex Robinson
//! \brief  Standard importance sampled dependent phase space dimension
//!         distribution template definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_IMPORTANCE_SAMPLED_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_DEF_HPP
#define MONTE_CARLO_STANDARD_IMPORTANCE_SAMPLED_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_DEF_HPP

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
template<PhaseSpaceDimension indep_dimension,
         PhaseSpaceDimension dep_dimension,
         typename TwoDDistributionBaseType>
StandardImportanceSampledDependentPhaseSpaceDimensionDistribution<indep_dimension,dep_dimension,TwoDDistributionBaseType>::StandardImportanceSampledDependentPhaseSpaceDimensionDistribution(
                        const std::shared_ptr<const Utility::TwoDDistribution>&
                        dimension_distribution,
                        const std::shared_ptr<const TwoDDistributionBaseType>&
                        importance_distribution )
  : StandardDependentPhaseSpaceDimensionDistribution<indep_dimension,dep_dimension,Utility::TwoDDistribution>( dimension_distribution ),
    d_dimension_importance_distribution( importance_distribution )
{
  // Make sure that the dimension distribution is valid
  testPrecondition( dimension_distribution.get() );
  // Make sure that the dimension distribution is valid
  testPrecondition( importance_distribution.get() );
  testPrecondition( importance_distribution->hasSamePrimaryBounds( dimension_distribution ) );
}

// Sample a dimension value without a cascade to the dependent dists.
template<PhaseSpaceDimension indep_dimension,
         PhaseSpaceDimension dep_dimension,
         typename TwoDDistributionBaseType>
void StandardImportanceSampledDependentPhaseSpaceDimensionDistribution<indep_dimension,dep_dimension,TwoDDistributionBaseType>::sampleWithoutCascade(
                                    PhaseSpacePoint& phase_space_sample ) const
{
  const double sample =
    TwoDDistributionSamplingPolicy<TwoDDistributionBaseType>::sample(
                        *d_dimension_importance_distribution,
                        getCoordinate<indep_dimension>( phase_space_sample ) );

  const double weight = this->calculateSampleWeight(
                          getCoordinate<indep_dimension>( phase_space_sample ),
                          sample );

  setCoordinate<dep_dimension>( phase_space_sample, sample );
  setCoordinateWeight<dep_dimension>( phase_space_sample, weight );
}

// Sample a dimension value without a cascade to the dependent dists.
template<PhaseSpaceDimension indep_dimension,
         PhaseSpaceDimension dep_dimension,
         typename TwoDDistributionBaseType>
void StandardImportanceSampledDependentPhaseSpaceDimensionDistribution<indep_dimension,dep_dimension,TwoDDistributionBaseType>::sampleAndRecordTrialsWithoutCascade(
                                  PhaseSpacePoint& phase_space_sample,
                                  ModuleTraits::InternalCounter& trials ) const
{
  const double sample =
    TwoDDistributionSamplingPolicy<TwoDDistributionBaseType>::sample(
                          *d_dimension_importance_distribution,
                          getCoordinate<indep_dimension>( phase_space_sample ),
                          trials );
  
  const double weight = this->calculateSampleWeight(
                          getCoordinate<indep_dimension>( phase_space_sample ),
                          sample );

  setCoordinate<dep_dimension>( phase_space_sample, sample );
  setCoordinateWeight<dep_dimension>( phase_space_sample, sample );
}

// Calculate the weight of a sample
template<PhaseSpaceDimension indep_dimension,
         PhaseSpaceDimension dep_dimension,
         typename TwoDDistributionBaseType>
double StandardImportanceSampledDependentPhaseSpaceDimensionDistribution<indep_dimension,dep_dimension,TwoDDistributionBaseType>::calculateSampleWeight(
                                      const double indep_dimension_value,
                                      const double dep_dimension_sample ) const
{
  const double weight_numerator =
    this->evaluatePDFWithoutCascade(
                                 indep_dimension_value, dep_dimension_sample );

  const double weight_denominator =
    d_dimension_importance_distribution->evaluateSecondaryConditionalPDF(
                                 indep_dimension_value, dep_dimension_sample );

  double weight = 1.0;

  // If both evaluate to 0, a weight of 1 is desired but nan will result
  if( weight_numerator > 0.0 || weight_denominator > 0.0 )
    weight = weight_numerator/weight_denominator;

  // Make sure that the weight is valid
  testPostcondition( !Teuchos::ScalarTraits<double>::isnaninf( weight ) );
  testPostcondition( weight > 0.0 );
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_IMPORTANCE_SAMPLED_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardImportanceSampledDependentPhaseSpaceDimensionDistribution_def.hpp
//---------------------------------------------------------------------------//
