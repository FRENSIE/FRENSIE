//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardAceLaw61AngleDistribution_def.hpp
//! \author Eli Moll
//! \brief  The standard law 61 angle distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_ACE_LAW_61_ANGLE_DISTRIBUTION_DEF_HPP
#define MONTE_CARLO_STANDARD_ACE_LAW_61_ANGLE_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardAceLaw61AngleDistribution.hpp"

namespace MonteCarlo{

//Constructor
template<typename AceLaw61InterpolationPolicy>
StandardAceLaw61AngleDistribution<AceLaw61InterpolationPolicy>::StandardAceLaw61AngleDistribution(
    const Utility::ArrayView<const double>& outgoing_energy_grid,
    const std::vector<std::shared_ptr<const Utility::UnivariateDistribution> >& cosine_distributions ) :
      AceLaw61AngleDistribution( outgoing_energy_grid, cosine_distributions )
{ /* ... */ }

// Sample the coupled angle
template<typename AceLaw61InterpolationPolicy>
double StandardAceLaw61AngleDistribution<AceLaw61InterpolationPolicy>::sampleCoupledAngle(
    const unsigned outgoing_index,
    const double energy_prime ) const
{
  if( d_outgoing_energy_grid.size() - 1 == outgoing_index )
  {
    return d_cosine_distributions[ outgoing_index ]->sample();
  }

  // Determine which cosine distribution should be sampled from and then sample
  if( AceLaw61InterpolationPolicy::useLowerBin(
                                energy_prime,
                                d_outgoing_energy_grid[outgoing_index],
                                d_outgoing_energy_grid[outgoing_index + 1] ) )
  {
    return d_cosine_distributions[ outgoing_index ]->sample();
  }
  else
  {
    return d_cosine_distributions[ outgoing_index + 1]->sample();
  }
}

#endif // MONTE_CARLO_STANDARD_ACE_LAW_61_ANGLE_DISTRIBUTION_DEF_HPP

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardAceLaw61AngleDistribution_def.hpp
//---------------------------------------------------------------------------//
