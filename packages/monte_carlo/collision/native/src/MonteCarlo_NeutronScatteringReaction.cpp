//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NeutronScatteringReaction.cpp
//! \author Alex Robinson
//! \brief  The neutron-in, neutron-out reaction class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_NeutronScatteringReaction.hpp"
#include "MonteCarlo_SimulationGeneralProperties.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ContractException.hpp"
#include "MonteCarlo_NuclearReactionHelper.hpp"

namespace MonteCarlo{

// Constructor 
NeutronScatteringReaction::NeutronScatteringReaction( 
		   const NuclearReactionType reaction_type,
		   const double temperature,
		   const double q_value,
		   const unsigned multiplicity,
		   const unsigned threshold_energy_index,
	     const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		   const Teuchos::ArrayRCP<const double>& cross_section,
		   const Teuchos::RCP<NuclearScatteringDistribution<NeutronState,NeutronState> >& 
		   scattering_distribution,
       double sab_cutoff_energy )
  : NuclearReaction( reaction_type, 
		     temperature, 
		     q_value,
		     threshold_energy_index,
		     incoming_energy_grid,
		     cross_section ),
    d_multiplicity( multiplicity ),
    d_scattering_distribution( scattering_distribution ),
    d_sab_cutoff_energy( sab_cutoff_energy )
{
  // Make sure the multiplicity is valid
  testPrecondition( multiplicity > 0 );
  // Make sure the scattering distribution is valid
  testPrecondition( scattering_distribution.get() != NULL );
}

// Return the number of neutrons emitted from the rxn at the given energy
unsigned NeutronScatteringReaction::getNumberOfEmittedNeutrons(
						    const double energy ) const
{
  return d_multiplicity;
}

// Set the S(alpha,beta) cutoff energy
void NeutronScatteringReaction::setSABCutoffEnergy( double sab_cutoff_energy )
{
  d_sab_cutoff_energy = sab_cutoff_energy;
}

// Simulate the reaction
void NeutronScatteringReaction::react( NeutronState& neutron, 
				       ParticleBank& bank ) const
{
  neutron.incrementCollisionNumber();
  
  // There should always be at least one outgoing neutron (>= 0 additional)
  unsigned num_additional_neutrons = 
    this->getNumberOfEmittedNeutrons( neutron.getEnergy() ) - 1u;

  // Create the additional neutrons (multiplicity - 1)
  for( unsigned i = 0; i < num_additional_neutrons; ++i )
  {
    Teuchos::RCP<NeutronState> new_neutron(
				   new NeutronState( neutron, true, false ) );
					   
    d_scattering_distribution->scatterParticle( *new_neutron, 
						this->getTemperature() );

    // Add the new neutron to the bank
    bank.push( new_neutron, this->getReactionType() );
  }
  
  // Scatter the "original" neutron
  d_scattering_distribution->scatterParticle( neutron,
					      this->getTemperature() );
}

// Return the cross section value at a given energy
double NeutronScatteringReaction::getCrossSection( const double energy ) const
{
  if( energy <= d_sab_cutoff_energy )
  {
    return 0.0;
  }
  else
  {
    return MonteCarlo::getCrossSection( energy,
                            d_incoming_energy_grid,
                            d_cross_section,
                            d_threshold_energy_index );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronScatteringReaction.cpp
//---------------------------------------------------------------------------//
