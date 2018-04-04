//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonuclearReaction.hpp
//! \author Alex Robinson, Ryan Pease
//! \brief  The photonuclear reaction base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTONUCLEAR_REACTION_HPP
#define MONTE_CARLO_PHOTONUCLEAR_REACTION_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_PhotonuclearReactionType.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_NuclearScatteringDistribution.hpp"
#include "Utility_Vector.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

//! The photonuclear reaction base class
template<typename OutgoingParticleType>
class PhotonuclearReaction
{
  // QuantityTraits typedef
  typedef Utility::QuantityTraits<double> QT;

public:

  //! Constructor
  PhotonuclearReaction(
       const PhotonuclearReactionType reaction_type,
       const double q_value,
       const size_t threshold_energy_index,
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section );

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
  virtual size_t getNumberOfEmittedParticles( const double energy) const = 0;

  //! Return the average number of particles emitted from the rxn
  virtual double getAverageNumberOfEmittedParticles(const double energy) const;

  //! Simulate the reaction
  virtual void react( PhotonState& photon, ParticleBank& bank ) const = 0;

protected:

  //! Return an integer number of emitted particles given a non-integer value
  size_t sampleNumberOfEmittedParticles(
				     const double average_multiplicity ) const;

private:

  // The photonuclear reaction type
  PhotonuclearReactionType d_reaction_type;

  // The Q value for the reaction
  double d_q_value;

  // The reaction threshold energy grid index
  size_t d_threshold_energy_index;

  // The incoming energy grid
  std::shared_ptr<const std::vector<double> > d_incoming_energy_grid;

  // The cross section values evaluated on the incoming energy grid
  std::shared_ptr<const std::vector<double> > d_cross_section;
};

// Return the average number of particles emitted from the rxn
/*! \details If the neutron multiplicity for the reaction is not an integer
 * at the desired energy, this function should be overridden in the derived
 * class. It will be used in implicit multiplication weighting games.
 */
template<typename OutgoingParticleType>
inline double PhotonuclearReaction<OutgoingParticleType>::getAverageNumberOfEmittedParticles(
						     const double energy) const
{
  return this->getNumberOfEmittedParticles( energy );
}

// Return the threshold energy
template<typename OutgoingParticleType>
inline double PhotonuclearReaction<OutgoingParticleType>::getThresholdEnergy() const
{
  return (*d_incoming_energy_grid)[d_threshold_energy_index];
}

// Return an integer number of emitted particles given a non-integer value
template<typename OutgoingParticleType>
size_t PhotonuclearReaction<OutgoingParticleType>::sampleNumberOfEmittedParticles(
				      const double average_multiplicity ) const
{
  // Make sure the average multiplicity is valid
  testPrecondition( average_multiplicity >= 0.0 );

  double floor_multiplicity;
  double round_down_prob = 1.0 - modf( average_multiplicity,
				       &floor_multiplicity );

  if( Utility::RandomNumberGenerator::getRandomNumber<double>() <
      round_down_prob )
    return (size_t)floor_multiplicity;
  else
    return (size_t)floor_multiplicity + 1u;
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
