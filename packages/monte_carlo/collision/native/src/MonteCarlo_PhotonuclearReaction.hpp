//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonuclearReaction.hpp
//! \author Alex Robinson, Ryan Pease
//! \brief  The photonuclear reaction base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTONUCLEAR_REACTION_HPP
#define MONTE_CARLO_PHOTONUCLEAR_REACTION_HPP

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhotonuclearReactionType.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_NuclearScatteringDistribution.hpp"

namespace MonteCarlo{

//! The photonuclear reaction base class
template<typename OutgoingParticleType>
class PhotonuclearReaction
{
  
private:

  // Teuchos ScalarTraits typedef
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Constructor
  PhotonuclearReaction( 
		   const PhotonuclearReactionType reaction_type,
      		   const double q_value,
		   const unsigned threshold_energy_index,
		   const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		   const Teuchos::ArrayRCP<const double>& cross_section,
                   const Teuchos::RCP<const NuclearScatteringDistribution<PhotonState,OutgoingParticleType> >&
		   outgoing_particle_distribution );

  //! Destructor
  virtual ~PhotonuclearReaction()
  { /* ... */ }

  //! Return the reaction type
  PhotonuclearReactionType getReactionType() const;

  //! Return the reaction Q value
  double getQValue() const;

  //! Return the threshold energy
  double getThresholdEnergy() const;

  //! Return the cross section at a given energy
  virtual double getCrossSection( const double energy ) const;

  //! Return the number of particle emitted from the rxn at the given energy
  virtual unsigned getNumberOfEmittedParticles( const double energy) const = 0;

  //! Return the average number of particles emitted from the rxn
  virtual double getAverageNumberOfEmittedParticles(const double energy) const;

  //! Simulate the reaction
  virtual void react( PhotonState& photon, ParticleBank& bank ) const = 0;

protected:

  //! Return an integer number of emitted particles given a non-integer value
  unsigned sampleNumberOfEmittedParticles(
				     const double average_multiplicity ) const;

private:

  // The photonuclear reaction type
  PhotonuclearReactionType d_reaction_type;

  // The Q value for the reaction
  double d_q_value;

  // The reaction threshold energy grid index
  unsigned d_threshold_energy_index;

  // The incoming energy grid
  Teuchos::ArrayRCP<const double> d_incoming_energy_grid;

  // The cross section values evaluated on the incoming energy grid
  Teuchos::ArrayRCP<const double> d_cross_section;

  // The outgoing particle distribution (energy and angle)
  Teuchos::RCP<const NuclearScatteringDistribution<PhotonState,OutgoingParticleType> >
  d_outgoing_particle_distribution;
};

// Return the average number of particles emitted from the rxn
/*! \details If the neutron multiplicity for the reaction is not an integer
 * at the desired energy, this function should be overridden in the derived
 * class. It will be used in implicit multiplication weighting games.
 */
tempate<typename OutgoingParticleType>
inline double PhotonuclearReaction<OutgoingParticleType>::getAverageNumberOfEmittedParticles(
						     const double energy) const
{
  return this->getNumberOfEmittedParticles( energy );
}

// Return the threshold energy
tempate<typename OutgoingParticleType>
inline double PhotonuclearReaction<OutgoingParticleType>::getThresholdEnergy() const
{
  return d_incoming_energy_grid[d_threshold_energy_index];
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_PhotonuclearReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_PHOTONUCLEAR_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonuclearReaction.hpp
//---------------------------------------------------------------------------//
