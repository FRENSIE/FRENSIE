//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DecoupledPhotonProductionReaction.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  The decoupled photon production reaction base class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_DecoupledPhotonProductionReaction.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
DecoupledPhotonProductionReaction::PhotonProductionReaction(
			      const NuclearReactionType base_reaction_type,
			      const unsigned photon_production_id,
			      const double temperature,
		        const Teuchos::RCP<NuclearScatteringDistribution<NeutronState,PhotonState> >&
			      photon_production_distribution,
			      const Teuchos::RCP<NuclearReaction>& total_reaction )
  : d_base_reaction_type( base_reaction_type ),
    d_photon_production_id( photon_production_id ),
    d_temperature( temperature ),
    d_photon_production_distribution( photon_production_distribution ),
    d_total_reaction( total_reaction )
{ 
  // Make sure the photon production distribution is valid
  testPrecondition( photon_production_distribution.get() != NULL );
}

// Return the photon production reaction id
unsigned DecoupledPhotonProductionReaction::getPhotonProductionReactionId() const
{
  return d_photon_production_id;
}

// Return the temperature (in MeV) at which the reaction occurs
double DecoupledPhotonProductionReaction::getTemperature() const
{
  return d_temperature;
}

// Simulate the reaction
void DecoupledPhotonProductionReaction::react( const NeutronState& neutron, 
				      ParticleBank& bank ) const
{
  Teuchos::RCP<PhotonState> new_photon(
			   new PhotonState( neutron, true, false ) );
	
	// Adjust the photon weight as Wp = Wn * (sigma_gamma)/(sigma_total)		   
	new_photon->setWeight( neutron->getWeight()*this->getCrossSection( neutron->getEnergy() )/d_total_reaction->getCrossSection( neutron->getEnergy() ) );
				   
  d_photon_production_distribution->scatterParticle( neutron, *new_photon,
					this->getTemperature() );

  bank.push( new_photon );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_DecoupledPhotonProductionReaction.cpp
//---------------------------------------------------------------------------//
