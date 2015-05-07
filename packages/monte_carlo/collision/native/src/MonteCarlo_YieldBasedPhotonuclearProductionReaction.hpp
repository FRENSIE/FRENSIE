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
#include "MonteCarlo_PhotonuclearProductionReaction.hpp"

namespace MonteCarlo{

//! The yield-based photonuclear reaction class
template<typename OutgoingParticleType>
class YieldBasedPhotonuclearReaction : public PhotonuclearReaction<OutgoingParticleType>
{

public:

  //! Constructor
  YieldBasedPhotonuclearProductionReaction(
		   const PhotonuclearReactionType reaction_type,
      		   const double q_value,
		   const unsigned threshold_energy_index,
		   const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		   const Teuchos::ArrayRCP<const double>& cross_section,
		   const Teuchos::ArrayRCP<const double>& yield_energy_grid,
		   const Teuchos::ArrayRCP<const double>& yield,
                   const Teuchos::RCP<const NuclearScatteringDistribution<PhotonState,OutgoingParticleType> >&
		   outgoing_particle_distribution );

  //! Destructor
  ~YieldBasedPhotonuclearProductionReaction()
  { /* ... */ }

  //! Return the cross section at a given energy
  double getCrossSection( const double energy ) const;
  
  //! Return the number of particle emitted from the rxn at the given energy
  unsigned getNumberOfEmittedParticles( const double energy) const;

  //! Return the average number of particles emitted from the rxn
  double getAverageNumberOfEmittedParticles(const double energy) const;

  //! Simulate the reaction
  void react( PhotonState& photon, ParticleBank& bank ) const;

private:

  // The photon production yield energy grid
  Teuchos::ArrayRCP<const double> d_yield_energy_grid;

  // The photon production yield
  Teuchos::ArrayRCP<const double> d_yield;
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
