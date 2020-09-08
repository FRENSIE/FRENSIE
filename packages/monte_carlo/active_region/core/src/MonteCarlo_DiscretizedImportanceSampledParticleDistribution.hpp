//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DiscretizedImportanceSampledParticleDistribution.hpp
//! \author Philip Britt
//! \brief  Discretized Importance Sampled Particle distribution class declaration (strictly for my thesis).
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DISCRETIZED_IMPORTANCE_SAMPLED_PARTICLE_DISTRIBUTION_HPP
#define MONTE_CARLO_DISCRETIZED_IMPORTANCE_SAMPLED_PARTICLE_DISTRIBUTION_HPP

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_PhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "Utility_TypeNameTraits.hpp"
#include "Utility_Set.hpp"

namespace MonteCarlo{

//! The particle distribution base class
class DiscretizedImportanceSampledParticleDistribution
{

public:

  //! Constructor
  DiscretizedImportanceSampledParticleDistribution( const std::string& name );

  //! Destructor
  ~DiscretizedImportanceSampledParticleDistribution()
  { /* ... */ }

  //! Return the dimension distribution type name
  std::string getDimensionDistributionTypeName( const PhaseSpaceDimension dimension ) const override;

  //! Check if the distribution is spatially uniform (somewhere) (Only apply to primary PDF)
  bool isSpatiallyUniform() const override;

  //! Check if the distribution is directionally uniform (isotropic) (only apply to primary PDF)
  bool isDirectionallyUniform() const override;

  //! Initialize dimension counter map
  void initializeDimensionCounters( DimensionCounterMap& trials ) const override;

  //! Evaluate the distribution at the desired phase space point
  double evaluate( const ParticleState& particle ) const override;

  //! Sample a particle state from the distribution
  void sample( ParticleState& particle ) const override;

  //! Sample a particle state from the dist. and record the number of trials
  void sampleAndRecordTrials( ParticleState& particle,
                                      DimensionCounterMap& trials ) const override;

  //! Sample a particle state with the desired dimension value
  void sampleWithDimensionValue( ParticleState& particle,
                                 const PhaseSpaceDimension dimension,
                                 const double dimension_value ) const override;

  //! Sample a particle state with the desired dim. value and record trials
  void sampleWithDimensionValueAndRecordTrials(
                                      ParticleState& particle,
                                      DimensionCounterMap& trials,
                                      const PhaseSpaceDimension dimension,
                                      const double dimension_value ) const override;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleDistribution.hpp
//---------------------------------------------------------------------------//
