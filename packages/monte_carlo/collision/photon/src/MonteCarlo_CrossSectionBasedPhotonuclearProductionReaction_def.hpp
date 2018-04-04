//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CrossSectionBasedPhotonuclearProductionReaction_def.hpp
//! \author Alex Robinson, Ryan Pease
//! \brief  The cross section based photonuclear production reaction def.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_CROSS_SECTION_BASED_PHOTONUCLEAR_PRODUCTION_REACTION_DEF_HPP
#define MONTE_CARLO_CROSS_SECTION_BASED_PHOTONUCLEAR_PRODUCTION_REACTION_DEF_HPP
// FRENSIE Includes
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
template<typename OutgoingParticleType>
CrossSectionBasedPhotonuclearProductionReaction<OutgoingParticleType>::CrossSectionBasedPhotonuclearProductionReaction(
       const PhotonuclearReactionType reaction_type,
       const std::vector<unsigned>& photon_production_ids,
       const double q_value,
       const unsigned threshold_energy_index,
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const std::vector<std::shared_ptr<const NuclearScatteringDistribution<PhotonState,OutgoingParticleType> > >&
		   outgoing_particle_distributions )
  : PhotonuclearReaction<OutgoingParticleType>( reaction_type,
                                                q_value,
                                                threshold_energy_index,
                                                incoming_energy_grid,
                                                cross_section ),
    d_photon_production_ids( photon_production_ids ),
    d_outgoing_particle_distributions( outgoing_particle_distributions )
{
  // Make sure the photon production ids are valid
  testPrecondition( photon_production_ids.size() > 0 );
  // Make sure the outgoing particle distributions are valid
  testPrecondition( outgoing_particle_distributions.size() ==
		    photon_production_ids.size() );
}

// Return the photon production ids
template<typename OutgoingParticleType>
const std::vector<unsigned>& CrossSectionBasedPhotonuclearProductionReaction<OutgoingParticleType>::getPhotonProductionIds() const
{
  return d_photon_production_ids;
}

// Return the number of particle emitted from the rxn at the given energy
template<typename OutgoingParticleType>
size_t CrossSectionBasedPhotonuclearProductionReaction<OutgoingParticleType>::getNumberOfEmittedParticles( const double energy ) const
{
  d_photon_production_ids.size();
}

// Simulate the reaction
template<typename OutgoingParticleType>
void CrossSectionBasedPhotonuclearProductionReaction<OutgoingParticleType>::react(
						     PhotonState& photon,
						     ParticleBank& bank ) const
{
  // Make sure the photon energy is valid
  testPrecondition( photon.getEnergy() > 0.0 );

  // Create the additional particles
  for( unsigned i = 0; i < d_photon_production_ids.size(); ++i )
  {
    std::shared_ptr<OutgoingParticleType> new_particle(
			      new OutgoingParticleType( photon, true, true ) );

    d_outgoing_particle_distributions[i]->scatterParticle( photon,
							   *new_particle );

    // Add the new particle to the bank
    bank.push( new_particle );
  }

  // Kill the original photon
  photon.setAsGone();
}

class NeutronState;

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( CrossSectionBasedPhotonuclearProductionReaction<NeutronState> );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_CROSS_SECTION_BASED_PHOTONUCLEAR_PRODUCTION_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CrossSectionBasedPhotonuclearProductionReaction_def.hpp
//---------------------------------------------------------------------------//

