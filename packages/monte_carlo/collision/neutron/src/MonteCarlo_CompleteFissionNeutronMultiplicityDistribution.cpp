//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CompleteFissionNeutronMultiplicityDistribution.hpp
//! \author Alex Robinson
//! \brief  The complete fission neutron multiplicity distribution class def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_CompleteFissionNeutronMultiplicityDistribution.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
CompleteFissionNeutronMultiplicityDistribution::CompleteFissionNeutronMultiplicityDistribution(
                        const std::shared_ptr<const Utility::UnivariateDistribution>&
                        prompt_multiplicity_distribution,
                        const std::shared_ptr<const Utility::UnivariateDistribution>&
                        delayed_multiplicity_distribution,
                        const std::shared_ptr<const Utility::UnivariateDistribution>&
                        total_multiplicity_distribution )
  : d_prompt_multiplicity_distribution( prompt_multiplicity_distribution ),
    d_delayed_multiplicity_distribution( delayed_multiplicity_distribution ),
    d_total_multiplicity_distribution( total_multiplicity_distribution )
{
  // Make sure the distributions are valid
  testPrecondition( prompt_multiplicity_distribution.get() );
  testPrecondition( delayed_multiplicity_distribution.get() );
  testPrecondition( total_multiplicity_distribution.get() );
}

// Return the average number of neutrons emitted
double CompleteFissionNeutronMultiplicityDistribution::getAverageNumberOfEmittedNeutrons(
						     const double energy) const
{
  return d_total_multiplicity_distribution->evaluate( energy );
}

// Return the average number of prompt neutrons emitted
double CompleteFissionNeutronMultiplicityDistribution::getAverageNumberOfPromptNeutrons(
						    const double energy ) const
{
  return d_prompt_multiplicity_distribution->evaluate( energy );
}

// Return the average number of delayed neutrons emitted
double CompleteFissionNeutronMultiplicityDistribution::getAverageNumberOfDelayedNeutrons(
						     const double energy) const
{
  return d_delayed_multiplicity_distribution->evaluate( energy );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_CompleteFissionNeutronMultiplicityDistribution.cpp
//---------------------------------------------------------------------------//
