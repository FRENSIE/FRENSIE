//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NeutronFissionReaction.cpp
//! \author Alex Robinson
//! \brief  The neutron fission reaction class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_NeutronFissionReaction.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor (delayed neutron data)
/*! \details This constructor should be used when delayed neutron data is
 * available.
 */
NeutronFissionReaction::NeutronFissionReaction(
		   const NuclearReactionType reaction_type,
		   const double temperature,
		   const double q_value,
		   const unsigned threshold_energy_index,
		   const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		   const Teuchos::ArrayRCP<const double>& cross_section,
		   const Teuchos::RCP<FissionNeutronMultiplicityDistribution>&
		   fission_neutron_multiplicity_distribution,
		   const Teuchos::RCP<NeutronScatteringDistribution>&
		   prompt_neutron_emission_distribution )
  : NuclearReaction( reaction_type, 
		     temperature,
		     q_value,
		     threshold_energy_index,
		     incoming_energy_grid,
		     cross_section ),
    d_fission_neutron_multiplicity_distribution( fission_neutron_multiplicity_distribution ),
    d_prompt_neutron_emission_distribution( prompt_neutron_emission_distribution )
{
  // Make sure the distributions are valid
  testPrecondition( !fission_neutron_multiplicity_distribution.is_null() );
  testPrecondition( !prompt_neutron_emission_distribution.is_null() );
}

// Return the number of neutrons emitted from the rxn at the given energy
unsigned NeutronFissionReaction::getNumberOfEmittedNeutrons( 
						    const double energy ) const
{
  double average_multiplicity = getAverageNumberOfEmittedNeutrons( energy );

  return sampleNumberOfEmittedNeutrons( average_multiplicity );
}
  
// Return the number of prompt neutrons emitted from the rxn
unsigned NeutronFissionReaction::getNumberOfPromptNeutrons( 
						    const double energy ) const
{
  double average_prompt_multiplicity = 
    getAverageNumberOfPromptNeutrons( energy );

  return sampleNumberOfEmittedNeutrons( average_prompt_multiplicity );
}

// Return the number of delayed neutrons emitted from the rxn
unsigned NeutronFissionReaction::getNumberOfDelayedNeutrons( 
						    const double energy ) const
{
  double average_delayed_multiplicity = 
    getAverageNumberOfDelayedNeutrons( energy );

  return sampleNumberOfEmittedNeutrons( average_delayed_multiplicity );
}

// Simulate the reaction
/*! \details This will only sample prompt neutrons since there is no outgoing
 * energy distribution to use for the delayed neutrons.
 */
void NeutronFissionReaction::react( NeutronState& neutron, 
				    ParticleBank& bank ) const
{
  reactImplementation( neutron, bank, true );
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
    this->getNumberOfPromptNeutrons( neutron.getEnergy() );

  // Create the additional prompt neutrons
  for( int i = 0; i < num_prompt_neutrons; ++i )
  {
    Teuchos::RCP<NeutronState> new_neutron(
				    new NeutronState( neutron, true, false ) );

    d_prompt_neutron_emission_distribution->scatterNeutron( 
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
