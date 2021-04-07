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
#include "MonteCarlo_StandardPhotonuclearReaction.hpp"
#include "MonteCarlo_NuclearScatteringDistribution.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

//! The cross section based photonuclear reaction class
template<typename OutgoingParticleType>
class CrossSectionBasedPhotonuclearProductionReaction : public StandardPhotonuclearReaction
{

public:

  //! Basic Constructor
  CrossSectionBasedPhotonuclearProductionReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const PhotonuclearReactionType reaction_type,
       const double q_value,
       const std::vector<unsigned>& photon_production_ids,
       const std::vector<std::shared_ptr<const NuclearScatteringDistribution<PhotonState,OutgoingParticleType> > >&
       outgoing_particle_distributions );

  //! Constructor
  CrossSectionBasedPhotonuclearProductionReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
       grid_searcher,
       const PhotonuclearReactionType reaction_type,
       const double q_value,
       const std::vector<unsigned>& photon_production_ids,
       const std::vector<std::shared_ptr<const NuclearScatteringDistribution<PhotonState,OutgoingParticleType> > >&
       outgoing_particle_distributions );

  //! Destructor
  ~CrossSectionBasedPhotonuclearProductionReaction()
  { /* ... */ }

  //! Return the photon production ids
  const std::vector<unsigned>& getPhotonProductionIds() const;

  //! Return the number of particles emitted from the rxn at the given energy
  unsigned getNumberOfEmittedParticles( const double energy ) const final override;

  //! Simulate the reaction
  void react( PhotonState& photon, ParticleBank& bank ) const final override;

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
