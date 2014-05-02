//---------------------------------------------------------------------------//
//!
//! \file   EstimatorContributionMultiplierPolicy.hpp
//! \author Alex Robinson
//! \brief  Estimator contribution multiplier policy structs.
//!
//---------------------------------------------------------------------------//

#ifndef ESTIMATOR_CONTRIBUTION_MULTIPLIER_POLICY_HPP
#define ESTIMATOR_CONTRIBUTION_MULTIPLIER_POLICY_HPP

// FACEMC Includes
#include "ParticleState.hpp"

namespace FACEMC{

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

} // end FACEMC namespace

#endif // end ESTIMATOR_CONTRIBUTION_MULTIPLIER_POLICY_HPP

//---------------------------------------------------------------------------//
// end EstimatorContributionMultiplierPolicy.hpp
//---------------------------------------------------------------------------//
