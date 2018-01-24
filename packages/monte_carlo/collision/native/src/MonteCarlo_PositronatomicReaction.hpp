//---------------------------------------------------------------------------//
//!
//! \file MonteCarlo_PositronatomicReaction.hpp
//! \author Luke Kersting
//! \brief The positron reaction base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_POSITRONATOMIC_REACTION_HPP
#define MONTE_CARLO_POSITRONATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_PositronState.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "Data_SubshellType.hpp"
#include "MonteCarlo_AtomicReaction.hpp"
#include "MonteCarlo_PositronatomicReactionType.hpp"
#include "Utility_RandomNumberGenerator.hpp"

namespace MonteCarlo{

//! The positron reaction base class
class PositronatomicReaction : public AtomicReaction
{

public:

  //!Constructor
  PositronatomicReaction()
  { /* ... */ }

  //!Destructor
  virtual ~PositronatomicReaction()
  { /* ... */}

  //! Return the reaction type
  virtual PositronatomicReactionType getReactionType() const = 0;

  //! Return the differential cross section
  virtual double getDifferentialCrossSection( const double incoming_energy,
                                              const double secondary_variable ) const = 0;

  //! Simulate the reaction
  virtual void react( PositronState& positron,
                      ParticleBank& bank,
                      Data::SubshellType& shell_of_interaction ) const = 0;

  //! Simulate the reaction and track the number of sampling trials
  virtual void react( PositronState& positron,
                      ParticleBank& bank,
                      Data::SubshellType& shell_of_interaction,
                      unsigned& trials ) const;

protected:

  //! Annihilate the positron
  void annihilatePositron( PositronState& positron,
                           ParticleBank& bank ) const;

  //! Return the min electron energy
  double getMinElectronEnergy() const;

  //! Set the min electron energy
  void setMinElectronEnergy( const double min_electron_energy );

private:

  //! Min electron energy
  double d_min_electron_energy;


};

// Simulate the reaction and track the number of sampling trials
inline void PositronatomicReaction::react(
                PositronState& positron,
                ParticleBank& bank,
                Data::SubshellType& shell_of_interaction,
                unsigned& trials ) const
{
  ++trials;

  this->react( positron, bank, shell_of_interaction );
}

// Annihilate the positron
/*! \details The positron is assumed to be at rest when it annihilates, emitting
 *  two photons at the electron rest mass energy. These photons are emitted
 *  isotropically in opposite directions in the azimuthal direction to conserve
 *  momentum and at 90 degrees to positron polar angle.
 */
inline void
PositronatomicReaction::annihilatePositron( PositronState& positron,
                                            ParticleBank& bank ) const
{
  // Create the first annihilation photon
  Teuchos::RCP<PhotonState> first_photon( new PhotonState( positron, true, true ) );
  Teuchos::RCP<PhotonState> second_photon( new PhotonState( positron, true, true ) );

  // Set the photon energies to the rest mass of an electron
  first_photon->setEnergy( positron.getRestMassEnergy() );
  second_photon->setEnergy( positron.getRestMassEnergy() );

  // Sample the isotropic azimuthal angle for the first photon
  double azimuthal_angle = Utility::PhysicalConstants::pi*
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  // Rotate the photons in opposite azimuthal directions
  first_photon->rotateDirection( 0.0, azimuthal_angle );
  second_photon->rotateDirection( 0.0, azimuthal_angle +
                                       Utility::PhysicalConstants::pi );

  // Bank the photons
  bank.push( first_photon );
  bank.push( second_photon );

  // Set the positron as gone
  positron.setAsGone();
}

// Return the min electron energy
inline double PositronatomicReaction::getMinElectronEnergy() const
{
  return d_min_electron_energy;
}

// Set the min electron energy
inline void
PositronatomicReaction::setMinElectronEnergy( const double min_electron_energy )
{
  // Make sure the min electron value is valid
  testPrecondition( min_electron_energy > 0.0 );

  d_min_electron_energy = min_electron_energy;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_POSITRONATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PositroAtomicReaction.hpp
//---------------------------------------------------------------------------//
