//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PartialFissionNeutronMultiplicityDistribution_def.hpp
//! \author Alex Robinson
//! \brief  The partial fission neutron multiplicity distribution class def.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTIAL_FISSION_NEUTRON_MULTIPLICITY_DISTRIBUTION_DEF_HPP
#define MONTE_CARLO_PARTIAL_FISSION_NEUTRON_MULTIPLICITY_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
/*! \details The first distribution must be either the prompt or delayed
 * distribution and the second distribution must be either the total or prompt
 * distribution: (prompt, total), (delayed,total), (delayed,prompt).
 */
template<typename FissionNeutronMultiplicityDistributionPolicy>
PartialFissionNeutronMultiplicityDistribution<FissionNeutronMultiplicityDistributionPolicy>::PartialFissionNeutronMultiplicityDistribution(
			      const std::shared_ptr<Utility::OneDDistribution>&
                              first_multiplicity_distribution,
                              const std::shared_ptr<Utility::OneDDistribution>&
                              second_multiplicity_distribution )
  : d_first_multiplicity_distribution( first_multiplicity_distribution ),
    d_second_multiplicity_distribution( second_multiplicity_distribution )
{
  // Make sure the distributions are valid
  testPrecondition( !first_multiplicity_distribution.is_null() );
  testPrecondition( !second_multiplicity_distribution.is_null() );
}

// Return the average number of neutrons emitted
template<typename FissionNeutronMultiplicityDistributionPolicy>
double PartialFissionNeutronMultiplicityDistribution<FissionNeutronMultiplicityDistributionPolicy>::getAverageNumberOfEmittedNeutrons(
						    const double energy ) const
{
  return FissionNeutronMultiplicityDistributionPolicy::getTotalNuBar(
					    d_first_multiplicity_distribution,
					    d_second_multiplicity_distribution,
					    energy );
}

// Return the average number of prompt neutrons emitted
template<typename FissionNeutronMultiplicityDistributionPolicy>
double PartialFissionNeutronMultiplicityDistribution<FissionNeutronMultiplicityDistributionPolicy>::getAverageNumberOfPromptNeutrons(
						    const double energy ) const
{
  return FissionNeutronMultiplicityDistributionPolicy::getPromptNuBar(
					    d_first_multiplicity_distribution,
					    d_second_multiplicity_distribution,
					    energy );
}

// Return the average number of delayed neutrons emitted
template<typename FissionNeutronMultiplicityDistributionPolicy>
double PartialFissionNeutronMultiplicityDistribution<FissionNeutronMultiplicityDistributionPolicy>::getAverageNumberOfDelayedNeutrons(
						    const double energy ) const
{
  return FissionNeutronMultiplicityDistributionPolicy::getDelayedNuBar(
					    d_first_multiplicity_distribution,
					    d_second_multiplicity_distribution,
					    energy );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTIAL_FISSION_NEUTRON_MULTIPLICITY_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PartialFissionNeutronMultiplicityDistribution_def.hpp
//---------------------------------------------------------------------------//
