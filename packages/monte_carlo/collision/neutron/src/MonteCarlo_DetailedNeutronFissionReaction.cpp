//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DetailedNeutronFissionReaction.cpp
//! \author Alex Robinson
//! \brief  The detailed neutron fission reaction class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_DetailedNeutronFissionReaction.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
DetailedNeutronFissionReaction::DetailedNeutronFissionReaction(
       const NuclearReactionType reaction_type,
       const double temperature,
       const double q_value,
       const unsigned threshold_energy_index,
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const std::shared_ptr<const FissionNeutronMultiplicityDistribution>&
       fission_neutron_multiplicity_distribution,
       const std::shared_ptr<const ScatteringDistribution>&
       prompt_neutron_emission_distribution,
       const std::shared_ptr<const ScatteringDistribution>&
       delayed_neutron_emission_distribution )
  : NeutronFissionReaction( reaction_type,
			    temperature,
			    q_value,
			    threshold_energy_index,
			    incoming_energy_grid,
			    cross_section,
			    fission_neutron_multiplicity_distribution,
			    prompt_neutron_emission_distribution ),
    d_delayed_neutron_emission_distribution( delayed_neutron_emission_distribution )
{
  // Make sure the distribution is valid
  testPrecondition( !delayed_neutron_emission_distribution.is_null() );
}

// Simulate the reaction
void DetailedNeutronFissionReaction::react( NeutronState& neutron,
					    ParticleBank& bank ) const
{
  neutron.incrementCollisionNumber();

  unsigned num_delayed_neutrons =
    this->getNumberOfDelayedNeutrons( neutron.getEnergy() );

  // Create the additional delayed neutrons
  for( unsigned i = 0; i < num_delayed_neutrons; ++i )
  {
    std::shared_ptr<NeutronState> new_neutron(
				    new NeutronState( neutron, true, false ) );

    d_delayed_neutron_emission_distribution->scatterParticle(
						      *new_neutron,
						      this->getTemperature() );

    bank.push( new_neutron, this->getReactionType() );
  }

  // Create the additional prompt neutrons
  NeutronFissionReaction::reactImplementation( neutron, bank, false );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_DetailedNeutronFissionReaction.cpp
//---------------------------------------------------------------------------//

