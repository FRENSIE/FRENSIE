//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NeutronFissionReaction.cpp
//! \author Alex Robinson
//! \brief  The neutron fission reaction class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_NeutronFissionReaction.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Basic Constructor (delayed neutron data)
/*! \details This constructor should be used when delayed neutron data is
 * available.
 */
NeutronFissionReaction::NeutronFissionReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const NuclearReactionType reaction_type,
       const double q_value,
       const double temperature,
       const std::shared_ptr<const FissionNeutronMultiplicityDistribution>&
       fission_neutron_multiplicity_distribution,
       const std::shared_ptr<const ScatteringDistribution>&
       prompt_neutron_emission_distribution )
  : StandardNeutronNuclearReaction( incoming_energy_grid,
                                    cross_section,
                                    threshold_energy_index,
                                    reaction_type,
                                    q_value,
                                    temperature ),
    d_fission_neutron_multiplicity_distribution( fission_neutron_multiplicity_distribution ),
    d_prompt_neutron_emission_distribution( prompt_neutron_emission_distribution )
{
  // Make sure the distributions are valid
  testPrecondition( fission_neutron_multiplicity_distribution.get() );
  testPrecondition( prompt_neutron_emission_distribution.get() )
}

// Constructor (delayed neutron data)
/*! \details This constructor should be used when delayed neutron data is
 * available.
 */
NeutronFissionReaction::NeutronFissionReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
       grid_searcher,
       const NuclearReactionType reaction_type,
       const double q_value,
       const double temperature,
       const std::shared_ptr<const FissionNeutronMultiplicityDistribution>&
       fission_neutron_multiplicity_distribution,
       const std::shared_ptr<const ScatteringDistribution>&
       prompt_neutron_emission_distribution )
  : StandardNeutronNuclearReaction( incoming_energy_grid,
                                    cross_section,
                                    threshold_energy_index,
                                    grid_searcher,
                                    reaction_type,
                                    q_value,
                                    temperature ),
    d_fission_neutron_multiplicity_distribution( fission_neutron_multiplicity_distribution ),
    d_prompt_neutron_emission_distribution( prompt_neutron_emission_distribution )
{
  // Make sure the distributions are valid
  testPrecondition( fission_neutron_multiplicity_distribution.get() );
  testPrecondition( prompt_neutron_emission_distribution.get() )
}

// Return the number of neutrons emitted from the rxn at the given energy
unsigned NeutronFissionReaction::getNumberOfEmittedParticles(
						    const double energy ) const
{
  double average_multiplicity =
    this->getAverageNumberOfEmittedParticles( energy );

  return this->sampleNumberOfEmittedParticles( average_multiplicity );
}

// Return the number of prompt neutrons emitted from the rxn
unsigned NeutronFissionReaction::getNumberOfPromptParticles(
						    const double energy ) const
{
  double average_prompt_multiplicity =
    this->getAverageNumberOfPromptParticles( energy );

  return this->sampleNumberOfEmittedParticles( average_prompt_multiplicity );
}

// Return the number of delayed neutrons emitted from the rxn
unsigned NeutronFissionReaction::getNumberOfDelayedParticles(
						    const double energy ) const
{
  double average_delayed_multiplicity =
    this->getAverageNumberOfDelayedParticles( energy );

  return this->sampleNumberOfEmittedParticles( average_delayed_multiplicity );
}

// Simulate the reaction
/*! \details This will only sample prompt neutrons since there is no outgoing
 * energy distribution to use for the delayed neutrons.
 */
void NeutronFissionReaction::react( NeutronState& neutron,
				    ParticleBank& bank ) const
{
  this->reactImplementation( neutron, bank, true );
}

// The implementation of the reaction simulation
/*! \details This will only sample prompt neutrons since there is no outgoing
 * energy distribution to use for the delayed neutrons. This function should
 * be used by derived classes to sample the prompt neutrons.
 */
void NeutronFissionReaction::reactImplementation(
				  NeutronState& neutron,
				  ParticleBank& bank,
				  const bool increment_collision_number ) const
{
  if( increment_collision_number )
    neutron.incrementCollisionNumber();

  int num_prompt_neutrons =
    this->getNumberOfPromptParticles( neutron.getEnergy() );

  // Create the additional prompt neutrons
  for( int i = 0; i < num_prompt_neutrons; ++i )
  {
    std::shared_ptr<NeutronState> new_neutron(
				    new NeutronState( neutron, true, false ) );

    d_prompt_neutron_emission_distribution->scatterParticle(
						      *new_neutron,
						      this->getTemperature() );

    bank.push( new_neutron, this->getReactionType() );
  }

  // Kill the original neutron
  neutron.setAsGone();
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronFissionReaction.cpp
//---------------------------------------------------------------------------//
