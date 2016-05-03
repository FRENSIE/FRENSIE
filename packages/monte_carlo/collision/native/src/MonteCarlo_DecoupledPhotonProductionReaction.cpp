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
DecoupledPhotonProductionReaction::DecoupledPhotonProductionReaction(
			      const NuclearReactionType base_reaction_type,
			      const unsigned photon_production_id,
			      const double temperature,
		        const Teuchos::RCP<NuclearScatteringDistribution<NeutronState,PhotonState> >&
			      photon_production_distribution,
			      const Teuchos::RCP<NuclearReaction>& total_reaction,
            const Teuchos::Array<std::shared_ptr<Utility::OneDDistribution> >& total_mt_yield_array )
  : d_base_reaction_type( base_reaction_type ),
    d_photon_production_id( photon_production_id ),
    d_temperature( temperature ),
    d_photon_production_distribution( photon_production_distribution ),
    d_total_neutron_reaction( total_reaction ),
    d_total_mt_yield_array( total_mt_yield_array )
{ 
  // Make sure the photon production distribution is valid
  testPrecondition( photon_production_distribution.get() != NULL );
  
  // Make sure the total reaction is valid
  testPrecondition( d_total_neutron_reaction.get() != NULL );
  testPrecondition( d_total_neutron_reaction->getReactionType() == N__TOTAL_REACTION );
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

// Return the total neutron reaction cross section
double DecoupledPhotonProductionReaction::getTotalCrossSection( 
                                                   const double energy ) const
{
  TEST_FOR_EXCEPTION( 
       d_total_neutron_reaction->getReactionType() != N__TOTAL_REACTION,
       std::runtime_error,
       "Error: the total neutron reaction was found to have type " << 
       d_total_neutron_reaction->getReactionType() << " != 1 ");
       
  return d_total_neutron_reaction->getCrossSection( energy );
} 

// Return the total yield for this photon production reaction
double DecoupledPhotonProductionReaction::getTotalYield(
                                                   const double energy ) const
{
  if ( d_total_mt_yield_array.size() == 0 )
  {
    return 1.0;
  }
  else
  {
    double yield = 0.0;
    
    for ( int i = 0; i < d_total_mt_yield_array.size(); ++i )
    {
      yield += d_total_mt_yield_array[i]->evaluate( energy );
    }
    
    return yield;
  }
}

// Simulate the reaction
void DecoupledPhotonProductionReaction::react( const NeutronState& neutron, 
				      ParticleBank& bank,
				      double total_photon_production_cross_section ) const
{
  Teuchos::RCP<PhotonState> new_photon(
			   new PhotonState( neutron, true, false ) );

	// Adjust the photon weight as Wp = Wn * (sigma_gamma)/(sigma_total)		   
	new_photon->setWeight( (neutron.getWeight()*total_photon_production_cross_section)/(this->getTotalCrossSection( neutron.getEnergy() ) ) );

  d_photon_production_distribution->scatterParticle( neutron, *new_photon,
					this->getTemperature() );
					
  bank.push( new_photon ); 
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_DecoupledPhotonProductionReaction.cpp
//---------------------------------------------------------------------------//
