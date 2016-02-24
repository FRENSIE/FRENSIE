//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EstimatorContributionMultiplierPolicy.hpp
//! \author Alex Robinson
//! \brief  Estimator contribution multiplier policy structs.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ESTIMATOR_CONTRIBUTION_MULTIPLIER_POLICY_HPP
#define MONTE_CARLO_ESTIMATOR_CONTRIBUTION_MULTIPLIER_POLICY_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleState.hpp"

namespace MonteCarlo{

struct WeightMultiplier
{
  //! Return the estimator contribution multiplier
  inline static double multiplier( const ParticleState& particle )
  { return particle.getWeight(); }
};

struct WeightAndEnergyMultiplier
{
  //! Return the estimator contribution multiplier
  inline static double multiplier( const ParticleState& particle )
  { return particle.getWeight()*particle.getEnergy(); }
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ESTIMATOR_CONTRIBUTION_MULTIPLIER_POLICY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_EstimatorContributionMultiplierPolicy.hpp
//---------------------------------------------------------------------------//
