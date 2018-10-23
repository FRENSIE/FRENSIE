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
#include "Utility_TypeNameTraits.hpp"

namespace MonteCarlo{

//! The weight multiplier policy
struct WeightMultiplier
{
  //! Return the estimator contribution multiplier
  inline static double multiplier( const ParticleState& particle )
  { return particle.getWeight(); }
};

//! The weight and energy multiplier policy
struct WeightAndEnergyMultiplier
{
  //! Return the estimator contribution multiplier
  inline static double multiplier( const ParticleState& particle )
  { return particle.getWeight()*particle.getEnergy(); }
};

//! The weight and charge multiplier policy
struct WeightAndChargeMultiplier
{
  //! Return the estimator contribution multiplier
  inline static double multiplier( const ParticleState& particle )
  { return particle.getWeight()*particle.getCharge(); }
};

} // end MonteCarlo namespace

TYPE_NAME_TRAITS_QUICK_DECL2( WeightMultiplier, MonteCarlo );
TYPE_NAME_TRAITS_QUICK_DECL2( WeightAndEnergyMultiplier, MonteCarlo );
TYPE_NAME_TRAITS_QUICK_DECL2( WeightAndChargeMultiplier, MonteCarlo );

#endif // end MONTE_CARLO_ESTIMATOR_CONTRIBUTION_MULTIPLIER_POLICY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_EstimatorContributionMultiplierPolicy.hpp
//---------------------------------------------------------------------------//
