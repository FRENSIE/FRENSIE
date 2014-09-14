//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonProductionReaction.cpp
//! \author Alex Robinson
//! \brief  The photon production reaction base class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_PhotonProductionReaction.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
PhotonProductionReaction::PhotonProductionReaction(
			      const NuclearReactionType base_reaction_type,
			      const unsigned photon_production_id,
			      const double temperature,
		              const Teuchos::RCP<PhotonProductionDistribution>&
			      photon_production_distribution )
  : d_base_reaction_type( base_reaction_type ),
    d_photon_production_id( photon_production_id ),
    d_temperature( temperature ),
    d_photon_production_distribution( photon_production_distribution )
{ 
  // Make sure the photon production distribution is valid
  testPrecondition( photon_production_distribution.get() != NULL );
}

// Return the photon production reaction id
unsigned PhotonProductionReaction::getPhotonProductionReactionId() const
{
  return static_cast<unsigned>( d_base_reaction_type )*1000u + 
    d_photon_production_id;
}

// Return the temperature (in MeV) at which the reaction occurs
double PhotonProductionReaction::getTemperature() const
{
  return d_temperature;
}

// Simulate the reaction
void PhotonProductionReaction::react( const NeutronState& neutron, 
				      ParticleBank& bank ) const
{
  Teuchos::RCP<PhotonState> new_photon;

  d_photon_production_distribution->createPhoton( neutron, new_photon );

  bank.push( new_photon );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonProductionReaction.cpp
//---------------------------------------------------------------------------//
