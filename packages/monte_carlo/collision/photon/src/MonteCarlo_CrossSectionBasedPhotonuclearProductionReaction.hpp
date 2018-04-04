//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CrossSectionBasedPhotonuclearProductionReaction.hpp
//! \author Alex Robinson, Ryan Pease
//! \brief  The cross section based photonuclear production reaction decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_CROSS_SECTION_BASED_PHOTONUCLEAR_PRODUCTION_REACTION_HPP
#define MONTE_CARLO_CROSS_SECTION_BASED_PHOTONUCLEAR_PRODUCTION_REACTION_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_PhotonuclearReaction.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

//! The cross section based photonuclear reaction class
template<typename OutgoingParticleType>
class CrossSectionBasedPhotonuclearProductionReaction : public PhotonuclearReaction<OutgoingParticleType>
{

public:

  //! Constructor
  CrossSectionBasedPhotonuclearProductionReaction(
		   const PhotonuclearReactionType reaction_type,
		   const std::vector<unsigned>& photon_production_ids,
      		   const double q_value,
		   const unsigned threshold_energy_index,
		   const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
		   const std::shared_ptr<const std::vector<double> >& cross_section,
                   const std::vector<std::shared_ptr<const NuclearScatteringDistribution<PhotonState,OutgoingParticleType> > >&
		   outgoing_particle_distributions );

  //! Destructor
  ~CrossSectionBasedPhotonuclearProductionReaction()
  { /* ... */ }

  //! Return the photon production ids
  const std::vector<unsigned>& getPhotonProductionIds() const;

  //! Return the number of particle emitted from the rxn at the given energy
  size_t getNumberOfEmittedParticles( const double energy) const override;

  //! Simulate the reaction
  void react( PhotonState& photon, ParticleBank& bank ) const override;

private:

  // The photon production id
  std::vector<unsigned> d_photon_production_ids;

  // The outgoing particle distribution (energy and angle)
  std::vector<std::shared_ptr<const NuclearScatteringDistribution<PhotonState,OutgoingParticleType> > >
  d_outgoing_particle_distributions;
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
