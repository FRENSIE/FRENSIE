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

// FRENSIE Includes
#include "MonteCarlo_PhotonuclearReactionType.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_PhotonState.hpp"

namespace MonteCarlo{

//! The photonuclear reaction base class
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
		   const Teuchos::ArrayRCP<const double>& cross_section );

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
  double getCrossSection( const double energy ) const;

  //! Return the number of photons emitted from the rxn at the given energy
  virtual unsigned getNumberOfEmittedPhotons( const double energy ) const = 0;

  //! Return the average number of photons emitted from the rxn
  virtual double getAverageNumberOfEmittedPhotons( const double energy ) const;

  //! Return the number of neutrons emitted from the rxn at the given energy
  virtual unsigned getNumberOfEmittedNeutrons( const double energy) const = 0;

  //! Return the average number of neutrons emitted from the rxn
  virtual double getAverageNumberOfEmittedNeutrons( const double energy) const;


  //! Simulate the reaction
  virtual void react( PhotonState& photon, ParticleBank& bank ) const = 0;

protected:

  //! Return an integer number of emitted photons given a non-integer value
  unsigned sampleNumberOfEmittedPhotons(
				     const double average_multiplicity ) const;

  //! Return an integer number of emitted photons given a non-integer value
  unsigned sampleNumberOfEmittedNeutrons(
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
};

// Return the average number of photons emitted from the rxn
/*! \details If the neutron multiplicity for the reaction is not an integer
 * at the desired energy, this function should be overridden in the derived
 * class. It will be used in implicit multiplication weighting games.
 */
  inline double PhotonuclearReaction::getAverageNumberOfEmittedPhotons(
								       const double energy) const
  {
    return this->getNumberOfEmittedPhotons( energy );
  }

// Return the average number of neutrosn emitted from the rxn
/*! \details If the neutron multiplicity for the reaction is not an integer
 * at the desired energy, this function should be overridden in the derived
 * class. It will be used in implicit multiplication weighting games.
 */
  inline double PhotonuclearReaction::getAverageNumberOfEmittedNeutrons(
								       const double energy) const
  {
    return this->getNumberOfEmittedNeutrons( energy );
  }

// Return the threshold energy
inline double PhotonuclearReaction::getThresholdEnergy() const
{
  return d_incoming_energy_grid[d_threshold_energy_index];
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTONUCLEAR_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonuclearReaction.hpp
//---------------------------------------------------------------------------//
