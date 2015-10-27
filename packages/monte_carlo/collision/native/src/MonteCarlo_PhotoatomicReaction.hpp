//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotoatomicReaction.hpp
//! \author Alex Robinson
//! \brief  The photoatomic reaction base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTOATOMIC_REACTION_HPP
#define MONTE_CARLO_PHOTOATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_SubshellType.hpp"
#include "MonteCarlo_PhotoatomicReactionType.hpp"

namespace MonteCarlo{

//! The photoatomic reaction base class
class PhotoatomicReaction
{

public:

  //! Constructor
  PhotoatomicReaction()
  { /* ... */ }

  //! Destructor
  virtual ~PhotoatomicReaction()
  { /* ... */ }
  
  //! Test if two photoatomic reactions share the same energy grid
  bool isEnergyGridShared( const PhotoatomicReaction& other_reaction ) const;
  
  //! Test if the energy falls within the energy grid
  virtual bool isEnergyWithinEnergyGrid( const double energy ) const = 0;

  //! Return the cross section at the given energy
  virtual double getCrossSection( const double energy ) const = 0;

  //! Return the cross section at the given energy (efficient)
  virtual double getCrossSection( const double energy,
				  const unsigned bin_index ) const = 0;

  //! Return the threshold energy
  virtual double getThresholdEnergy() const = 0;

  //! Return the number of photons emitted from the rxn at the given energy
  virtual unsigned getNumberOfEmittedPhotons( const double energy ) const = 0;
  
  //! Return the reaction type
  virtual PhotoatomicReactionType getReactionType() const = 0;

  //! Simulate the reaction
  virtual void react( PhotonState& photon, 
		      ParticleBank& bank,
		      SubshellType& shell_of_interaction ) const = 0;

  //! Simulate the reaction and track the number of sampling trials
  virtual void react( PhotonState& photon, 
		      ParticleBank& bank,
		      SubshellType& shell_of_interaction,
		      unsigned& trials ) const;

protected:

  //! Return the head of the energy grid
  virtual const double* getEnergyGridHead() const = 0;
};

// Test if two photoatomic reactions share the same energy grid
inline bool PhotoatomicReaction::isEnergyGridShared( 
			      const PhotoatomicReaction& other_reaction ) const
{
  return this->getEnergyGridHead() == other_reaction.getEnergyGridHead();
}

// Simulate the reaction and track the number of sampling trials
inline void PhotoatomicReaction::react( PhotonState& photon, 
					ParticleBank& bank,
					SubshellType& shell_of_interaction,
					unsigned& trials ) const
{
  ++trials;

  this->react( photon, bank, shell_of_interaction );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTOATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotoatomicReaction.hpp
//---------------------------------------------------------------------------//
