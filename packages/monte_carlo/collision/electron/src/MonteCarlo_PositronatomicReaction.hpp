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
#include "MonteCarlo_AtomicReaction.hpp"
#include "MonteCarlo_PositronatomicReactionType.hpp"
#include "MonteCarlo_StandardReactionBaseImpl.hpp"
#include "Data_SubshellType.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_DistributionTraits.hpp"

namespace MonteCarlo{

//! The positron reaction base class
class PositronatomicReaction : public AtomicReaction
{

public:

  //! The trials counter type
  typedef Utility::DistributionTraits::Counter Counter;

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
                      Counter& trials ) const;

  //! Annihilate the positron
  static void producesAnnihilationPhotons( const PositronState& positron,
                                           ParticleBank& bank );
};

// Simulate the reaction and track the number of sampling trials
inline void PositronatomicReaction::react(
                PositronState& positron,
                ParticleBank& bank,
                Data::SubshellType& shell_of_interaction,
                Counter& trials ) const
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
PositronatomicReaction::producesAnnihilationPhotons(
                            const PositronState& positron,
                            ParticleBank& bank )
{
  // Create the first annihilation photon
  std::shared_ptr<PhotonState> first_photon( new PhotonState( positron, true, true ) );
  std::shared_ptr<PhotonState> second_photon( new PhotonState( positron, true, true ) );

  // Set the photon energies to the rest mass of an electron
  first_photon->setEnergy( positron.getRestMassEnergy() );
  second_photon->setEnergy( positron.getRestMassEnergy() );

  // Sample the isotropic azimuthal angle for the first photon
  double azimuthal_angle = 2*Utility::PhysicalConstants::pi*
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  // Rotate the first photon
  first_photon->rotateDirection( 0.0, azimuthal_angle );

  // Change the second photon's direction based on the initial direction of the
  // emitted positron (to conserve momentum we must rotate the
  // azimuthal angle by pi)
  azimuthal_angle = fmod( azimuthal_angle + Utility::PhysicalConstants::pi,
                          2*Utility::PhysicalConstants::pi );

  // Rotate the second photon
  second_photon->rotateDirection( 0.0, azimuthal_angle );

  // Bank the photons
  bank.push( first_photon );
  bank.push( second_photon );

  // // Set the positron as gone
  // positron.setAsGone();
}

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<PositronatomicReaction,Utility::LinLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<PositronatomicReaction,Utility::LinLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<PositronatomicReaction,Utility::LinLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<PositronatomicReaction,Utility::LinLog,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<PositronatomicReaction,Utility::LogLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<PositronatomicReaction,Utility::LogLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<PositronatomicReaction,Utility::LogLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<PositronatomicReaction,Utility::LogLog,true> );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_POSITRONATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PositroAtomicReaction.hpp
//---------------------------------------------------------------------------//
