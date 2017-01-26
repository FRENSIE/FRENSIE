//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardDependentPhaseSpaceDimensionDistribution_def.hpp
//! \author Alex Robinson
//! \brief  Standard dependent phase space dimension distribution class def.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_DEF_HPP
#define MONTE_CARLO_STANDARD_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "Utility_FullyTabularTwoDDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

//! The generic TwoDDistribution sampling policy class
template<typename T>
struct TwoDDistributionSamplingPolicy
{
  //! Generate a sample from the TwoDDistribution object
  static inline double sample( const T& distribution,
                               const double indep_dimension_value )
  {
    return distribution->sampleSecondaryConditional( indep_dimension_value );
  }

  //! Generate a sample from the TwoDDistribution object
  static inline double sampleAndRecordTrials(
                                  const T& distribution,
                                  const double indep_dimension_value,
                                  ModuleTraits::InternalCounter& trials )
  {
    return distribution->sampleSecondaryConditionAndRecordTrials(
                                               indep_dimension_value, trials );
  }
};

/*! \brief The TwoDDistribution sampling policy specialization for 
 * the Utility::FullyTabularTwoDDistribution class
 */
template<>
struct TwoDDistributionSamplingPolicy<Utility::FullyTabularTwoDDistribution>
{
  //! Generate a sample from the Utility::FullyTabularTwoDDistribution object
  static inline double sample(
                     const Utility::FullyTabularTwoDDistribution& distribution,
                     const double indep_dimension_value )
  {
    return distribution->sampleSecondaryConditionalExact(
                                                       indep_dimension_value );
  }

  //! Generate a sample from the Utility::FullyTabularTwoDDistribution object
  static inline double sampleAndRecordTrials(
                     const Utility::FullyTabularTwoDDistribution& distribution,
                     const double indep_dimension_value,
                     ModuleTraits::InternalCounter& trials )
  {
    // The number of trials can be tracked when we use exact sampling. We
    // will simply increment the trials counter. Since the underlying
    // conditional distributions are tabular the sampling efficiency should
    // always be one anyway.
    ++trials;
    
    return distribution->sampleSecondaryConditionalExact(
                                                       indep_dimension_value );
  }
};

// Constructor
template<PhaseSpaceDimension indep_dimension,
         PhaseSpaceDimension dep_dimension,
         typename TwoDDistributionBaseType>
StandardDependentPhaseSpaceDimensionDistribution<indep_dimension,dep_dimension,TwoDDistributionBaseType>::StandardDependentPhaseSpaceDimensionDistribution(
                         const std::shared_ptr<const TwoDDistributionBaseType>&
                         dimension_distribution )
  : d_dimension_distribution( dimension_distribution )
{
  // Make sure that the dimension distribution is valid
  testPrecondition( dimension_distribution.get() );
}

// Check if the dimension distribution is continuous
/*! \details This method only checks if the distribution is continuous w.r.t.
 * the independent dimension. More information is needed to check if the
 * distribution is continuous w.r.t. the dependent dimension.
 */
template<PhaseSpaceDimension indep_dimension,
         PhaseSpaceDimension dep_dimension,
         typename TwoDDistributionBaseType>
bool StandardDependentPhaseSpaceDimensionDistribution<indep_dimension,dep_dimension,TwoDDistributionBaseType>::isContinuous() const
{
  return d_dimension_distribution->isPrimaryDimensionContinuous();
}

// Check if the dimension distribution is tabular
/*! \details This method only checks if the distribution is tabular w.r.t.
 * the independent dimension. More information is needed to check if the 
 * distribution is tabular w.r.t. the dependent dimension.
 */
template<PhaseSpaceDimension indep_dimension,
         PhaseSpaceDimension dep_dimension,
         typename TwoDDistributionBaseType>
bool StandardDependentPhaseSpaceDimensionDistribution<indep_dimension,dep_dimension,TwoDDistributionBaseType>::isTabular() const
{
  return d_dimension_distribution->isPrimaryDimensionTabular();
}

// Check if the dimension distribution is uniform (somewhere)
/*! \details This method will always return false since we cannot test
 * if the two-d distribution is constant everywhere that it is defined.
 */
template<PhaseSpaceDimension indep_dimension,
         PhaseSpaceDimension dep_dimension,
         typename TwoDDistributionBaseType>
bool StandardDependentPhaseSpaceDimensionDistribution<indep_dimension,dep_dimension,TwoDDistributionBaseType>::isUniform() const
{
  return false;
}

// Check if the underlying distribution has the form of interest
/*! \details This method will always return false since we cannot test
 * if the two-d distribution has the form of interest everywhere that it is 
 * defined.
 */
template<PhaseSpaceDimension indep_dimension,
         PhaseSpaceDimension dep_dimension,
         typename TwoDDistributionBaseType>
bool StandardDependentPhaseSpaceDimensionDistribution<indep_dimension,dep_dimension,TwoDDistributionBaseType>::hasForm(
                           const OneDDistributionType distribution_type ) const
{
  return false;
}

// Evaluate the dimension distribution without cascade to dependent dists.
template<PhaseSpaceDimension indep_dimension,
         PhaseSpaceDimension dep_dimension,
         typename TwoDDistributionBaseType>
double StandardDependentPhaseSpaceDimensionDistribution<indep_dimension,dep_dimension,TwoDDistributionBaseType>::evaluateWithoutCascade(
                               const PhaseSpacePoint& phase_space_point ) const
{
  return d_dimension_distribution->evaluate(
                           getCoordinate<indep_dimension>( phase_space_point ),
                           getCoordinate<dep_dimension>( phase_space_point ) );
}

// Sample a dimension value without a cascade to the dependent dists.
template<PhaseSpaceDimension indep_dimension,
         PhaseSpaceDimension dep_dimension,
         typename TwoDDistributionBaseType>
void StandardDependentPhaseSpaceDimensionDistribution<indep_dimension,dep_dimension,TwoDDistributionBaseType>::sampleWithoutCascade(
                                    PhaseSpacePoint& phase_space_sample ) const
{
  const double sample =
    TwoDDistributionSamplingPolicy<TwoDDistributionBaseType>::sample(
                        *d_dimension_distribution,
                        getCoordinate<indep_dimension>( phase_space_sample ) );

  setCoordinate<dep_dimension>( phase_space_sample, sample );
  setCoordinateWeight<dep_dimension>( phase_space_sample, 1.0 );
}

// Sample a dimension value without a cascade to the dependent dists.
template<PhaseSpaceDimension indep_dimension,
         PhaseSpaceDimension dep_dimension,
         typename TwoDDistributionBaseType>
void StandardDependentPhaseSpaceDimensionDistribution<indep_dimension,dep_dimension,TwoDDistributionBaseType>::sampleAndRecordTrialsWithoutCascade(
                                  PhaseSpacePoint& phase_space_sample,
                                  ModuleTraits::InternalCounter& trials ) const
{
  const double sample =
    TwoDDistributionSamplingPolicy<TwoDDistributionBaseType>::sampleAndRecordTrials(
                        *d_dimension_distribution,
                        getCoordinate<indep_dimension>( phase_space_sample ),
                        trials );

  setCoordinate<dep_dimension>( phase_space_sample, sample );
  setCoordinateWeight<dep_dimension>( phase_space_sample, 1.0 );
}

// Set the dimension value (weight appropriately)
template<PhaseSpaceDimension indep_dimension,
         PhaseSpaceDimension dep_dimension,
         typename TwoDDistributionBaseType>
void StandardDependentPhaseSpaceDimensionDistribution<indep_dimension,dep_dimension,TwoDDistributionBaseType>::setDimensionValueAndApplyWeight(
                                           PhaseSpacePoint& phase_space_sample,
                                           const double dimension_value ) const
{
  const double weight = this->evaluatePDFWithoutCascade(
                          getCoordinate<indep_dimension>( phase_space_sample ),
                          dimension_value );

  // Make sure that the weight is valid
  testPostcondition( weight > 0.0 );

  setCoordinate<dep_dimension>( phase_space_sample, dimension_value );
  setCoordinateWeight<dep_dimension>( phase_space_sample, weight );
}

// Evaluate the PDF of this dimension distribution
template<PhaseSpaceDimension indep_dimension,
         PhaseSpaceDimension dep_dimension,
         typename TwoDDistributionBaseType>
double StandardDependentPhaseSpaceDimensionDistribution<indep_dimension,dep_dimension>::evaluatePDFWithoutCascade(
                                          const double indep_dimension_value,
                                          const double dimension_value ) const
{
  return d_dimension_distribution->evaluateSecondaryConditionalPDF(
                                      indep_dimension_value, dimension_value );
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardDependentPhaseSpaceDimensionDistribution_def.hpp
//---------------------------------------------------------------------------//
