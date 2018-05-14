//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardImportanceSampledDependentPhaseSpaceDimensionDistribution.hpp
//! \author Alex Robinson
//! \brief  Standard importance sampled dependent phase space dimension
//!         distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_IMPORTANCE_SAMPLED_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP
#define MONTE_CARLO_STANDARD_IMPORTANCE_SAMPLED_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardDependentPhaseSpaceDimensionDistribution.hpp"

namespace MonteCarlo{

/*! The standard dependent phase space dimension distribution class
 * \details The exact TwoDDistribution base class type is only of interest
 * when the distribution will be sampled from (a FullyTabularTwoDDistribution
 * has an exact sampling implementation as opposed to the stochastic sampling
 * procedure of the other classes). Since the dimension distribution will
 * not be sampled from direction (we will sample from the importance 
 * distribution), we can store the dimension distribution as the lowest base
 * class type (TwoDDistribution). 
 */
template<PhaseSpaceDimension indep_dimension,
         PhaseSpaceDimension dep_dimension,
         typename TwoDDistributionBaseType>
class StandardImportanceSampledDependentPhaseSpaceDimensionDistribution : public StandardDependentPhaseSpaceDimensionDistribution<indep_dimension,dep_dimension,Utility::TwoDDistribution>
{

public:

  //! Constructor
  StandardImportanceSampledDependentPhaseSpaceDimensionDistribution(
                        const std::shared_ptr<const Utility::TwoDDistribution>&
                        dimension_distribution,
                        const std::shared_ptr<const TwoDDistributionBaseType>&
                        importance_distribution );

  //! Destructor
  ~StandardImportanceSampledDependentPhaseSpaceDimensionDistribution()
  { /* ... */ }

  //! Sample a dimension value without a cascade to the dependent dists.
  void sampleWithoutCascade(
                          PhaseSpacePoint& phase_space_sample ) const override;

  //! Sample a dimension value without a cascade to the dependent dists.
  void sampleAndRecordTrialsWithoutCascade(
                        PhaseSpacePoint& phase_space_sample,
                        ModuleTraits::InternalCounter& trials ) const override;

private:

  // Calculate the weight of a sample
  double calculateSampleWeight( const double indep_dimension_value,
                                const double dep_dimension_sample ) const;

  // The dimension importance distribution
  std::shared_ptr<const TwoDDistributionBaseType>
  d_dimension_importance_distribution;
};
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardImportanceSampledDependentPhaseSpaceDimensionDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDARD_IMPORTANCE_SAMPLED_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardImportanceSampledDependentPhaseSpaceDimensionDistribution.hpp
//---------------------------------------------------------------------------//
