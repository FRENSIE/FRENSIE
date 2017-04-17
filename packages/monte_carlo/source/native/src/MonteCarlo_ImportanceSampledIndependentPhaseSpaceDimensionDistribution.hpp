//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ImportanceSampledIndependentPhaseSpaceDimensionDistribution.hpp
//! \author Alex Robinson
//! \brief  Importance sampled independent phase space dimension distribution
//!         class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_IMPORTANCE_SAMPLED_INDEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP
#define MONTE_CARLO_IMPORTANCE_SAMPLED_INDEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_IndependentPhaseSpaceDimensionDistribution.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"

namespace MonteCarlo{

//! The importance sampled independent phase space dimension distribution class
template<PhaseSpaceDimension dimension>
class ImportanceSampledIndependentPhaseSpaceDimensionDistribution : public IndependentPhaseSpaceDimensionDistribution<dimension>
{

public:

  //! Constructor
  ImportanceSampledIndependentPhaseSpaceDimensionDistribution(
                        const std::shared_ptr<const Utility::OneDDistribution>&
                        dimension_distribution,
                        const std::shared_ptr<const Utility::OneDDistribution>&
                        importance_distribution );

  //! Destructor
  ~ImportanceSampledIndependentPhaseSpaceDimensionDistribution()
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
  double calculateSampleWeight( const double dimension_sample ) const;

  // The dimension importance distribution
  std::shared_ptr<const Utility::OneDDistribution>
  d_dimension_importance_distribution;
};

// Explicit instantiation (extern declaration)
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( ImportanceSampledIndependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( ImportanceSampledIndependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( ImportanceSampledIndependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( ImportanceSampledIndependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( ImportanceSampledIndependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( ImportanceSampledIndependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( ImportanceSampledIndependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( ImportanceSampledIndependentPhaseSpaceDimensionDistribution<TIME_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( ImportanceSampledIndependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_ImportanceSampledIndependentPhaseSpaceDimensionDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_IMPORTANCE_SAMPLED_INDEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ImportanceSampledIndependentPhaseSpaceDimensionDistribution.hpp
//---------------------------------------------------------------------------//
