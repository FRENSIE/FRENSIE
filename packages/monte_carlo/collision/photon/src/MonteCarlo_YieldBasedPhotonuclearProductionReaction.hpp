//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_YieldBasedPhotonuclearProductionReaction.hpp
//! \author Alex Robinson, Ryan Pease
//! \brief  The yield-based photonuclear reaction class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_YIELD_BASED_PHOTONUCLEAR_REACTION_HPP
#define MONTE_CARLO_YIELD_BASED_PHOTONUCLEAR_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardPhotonuclearReaction.hpp"

namespace MonteCarlo{

//! The yield-based photonuclear reaction class
template<typename OutgoingParticleType>
class YieldBasedPhotonuclearProductionReaction : public StandardPhotonuclearReaction
{

public:

  //! Basic Constructor
  YieldBasedPhotonuclearProductionReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const PhotonuclearReactionType reaction_type,
       const double q_value,
       const std::shared_ptr<const std::vector<double> >& yield_energy_grid,
       const std::shared_ptr<const std::vector<double> >& yield,
       const std::shared_ptr<const NuclearScatteringDistribution<PhotonState,OutgoingParticleType> >&
       outgoing_particle_distribution );

  //! Constructor
  YieldBasedPhotonuclearProductionReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
       grid_searcher,
       const PhotonuclearReactionType reaction_type,
       const double q_value,
       const std::shared_ptr<const std::vector<double> >& yield_energy_grid,
       const std::shared_ptr<const std::vector<double> >& yield,
       const std::shared_ptr<const NuclearScatteringDistribution<PhotonState,OutgoingParticleType> >&
       outgoing_particle_distribution );

  //! Destructor
  virtual ~YieldBasedPhotonuclearProductionReaction()
  { /* ... */ }

  //! Return the number of particle emitted from the rxn at the given energy
  unsigned getNumberOfEmittedParticles( const double energy ) const final override;

  //! Return the average number of particles emitted from the rxn
  double getAverageNumberOfEmittedParticles( const double energy ) const final override;

  //! Simulate the reaction
  void react( PhotonState& photon, ParticleBank& bank ) const final override;

private:

  // The photon production yield energy grid
  std::shared_ptr<const std::vector<double> > d_yield_energy_grid;

  // The photon production yield
  std::shared_ptr<const std::vector<double> > d_yield;

  // The outgoing particle distribution (energy and angle)
  std::shared_ptr<const NuclearScatteringDistribution<PhotonState,OutgoingParticleType> >
  d_outgoing_particle_distribution;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_YieldBasedPhotonuclearProductionReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_YIELD_BASED_PHOTONUCLEAR_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_YieldBasedPhotonuclearProductionReaction.hpp
//---------------------------------------------------------------------------//
