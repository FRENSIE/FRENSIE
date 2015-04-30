//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CrossSectionBasedPhotonuclearProductionReaction.hpp
//! \author Alex Robinson
//! \brief  The cross section based photonuclear production reaction
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_CROSS_SECTION_BASED_PHOTONUCLEAR_PRODUCTION_REACTION_HPP
#define MONTE_CARLO_CROSS_SECTION_BASED_PHOTONUCLEAR_PRODUCTION_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_PhotonuclearProductionReaction.hpp"

namespace MonteCarlo{

//! The cross section based photonuclear reaction class
template<typename OutgoingParticleType>
class CrossSectionBasedPhotonuclearProductionReaction
{

public:

  //! Constructor
  CrossSectionBasedPhotonuclearProductionReaction(
		   const PhotonuclearReactionType reaction_type,
		   const unsigned photon_production_id,
      		   const double q_value,
		   const unsigned threshold_energy_index,
		   const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		   const Teuchos::ArrayRCP<const double>& cross_section,
                   const Teuchos::RCP<const NuclearScatteringDistribution<PhotonState,OutgoingParticleType> >&
		   outgoing_particle_distribution );

  //! Destructor
  ~CrossSectionBasedPhotonuclearProductionReaction()
  { /* ... */ }

  //! Return the photon production id
  unsigned getPhotonProductionId() const;

  //! Return the number of particle emitted from the rxn at the given energy
  unsigned getNumberOfEmittedParticles( const double energy) const;

  //! Return the average number of particles emitted from the rxn
  double getAverageNumberOfEmittedParticles(const double energy) const;

  //! Simulate the reaction
  void react( PhotonState& photon, ParticleBank& bank ) const;

private:
  
  // The photon production id
  unsigned d_photon_production_id;
}; 

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_CrossSectionBasedPhotonuclearProductionReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_CROSS_SECTION_BASED_PHOTONUCLEAR_PRODUCTION_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CrossSectionBasedPhotonuclearProductionReaction.hpp
//---------------------------------------------------------------------------//
