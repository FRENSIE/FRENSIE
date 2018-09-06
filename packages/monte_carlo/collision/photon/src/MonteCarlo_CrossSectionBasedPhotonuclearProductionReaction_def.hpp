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
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Basic Constructor
template<typename OutgoingParticleType>
CrossSectionBasedPhotonuclearProductionReaction<OutgoingParticleType>::CrossSectionBasedPhotonuclearProductionReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const PhotonuclearReactionType reaction_type,
       const double q_value,
       const std::vector<unsigned>& photon_production_ids,
       const std::vector<std::shared_ptr<const NuclearScatteringDistribution<PhotonState,OutgoingParticleType> > >&
       outgoing_particle_distributions )
  : StandardPhotonuclearReaction( incoming_energy_grid,
                                  cross_section,
                                  threshold_energy_index,
                                  reaction_type,
                                  q_value ),
    d_photon_production_ids( photon_production_ids ),
    d_outgoing_particle_distributions( outgoing_particle_distributions )
{
  // Make sure the photon production ids are valid
  testPrecondition( photon_production_ids.size() > 0 );
  // Make sure the outgoing particle distributions are valid
  testPrecondition( outgoing_particle_distributions.size() ==
		    photon_production_ids.size() );
}

// Constructor
template<typename OutgoingParticleType>
CrossSectionBasedPhotonuclearProductionReaction<OutgoingParticleType>::CrossSectionBasedPhotonuclearProductionReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
       grid_searcher,
       const PhotonuclearReactionType reaction_type,
       const double q_value,
       const std::vector<unsigned>& photon_production_ids,
       const std::vector<std::shared_ptr<const NuclearScatteringDistribution<PhotonState,OutgoingParticleType> > >&
       outgoing_particle_distributions )
  : StandardPhotonuclearReaction( incoming_energy_grid,
                                  cross_section,
                                  threshold_energy_index,
                                  grid_searcher,
                                  reaction_type,
                                  q_value ),
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
unsigned CrossSectionBasedPhotonuclearProductionReaction<OutgoingParticleType>::getNumberOfEmittedParticles( const double energy ) const
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
  for( size_t i = 0; i < d_photon_production_ids.size(); ++i )
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

