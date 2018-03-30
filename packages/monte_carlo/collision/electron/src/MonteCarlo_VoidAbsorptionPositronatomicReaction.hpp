//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_VoidAbsorptionPositronatomicReaction.hpp
//! \author Luke Kersting
//! \brief  The void absorption positron-atomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_VOID_ABSORPTION_POSITRONATOMIC_REACTION_HPP
#define MONTE_CARLO_VOID_ABSORPTION_POSITRONATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_PositronatomicReaction.hpp"

namespace MonteCarlo{

/*! The void absorption positron-atomic reaction class
* \details This class can be used to ignore absorption reactions.
*/

class VoidAbsorptionPositronatomicReaction : public PositronatomicReaction
{

public:

  //! Constructor
  VoidAbsorptionPositronatomicReaction()
  { /* ... */ }

  //! Destructor
  ~VoidAbsorptionPositronatomicReaction()
  { /* ... */ }

  //! Test if the energy falls within the energy grid
  bool isEnergyWithinEnergyGrid( const double energy ) const;

  //! Return the cross section at the given energy
  double getCrossSection( const double energy ) const;

  //! Return the cross section at the given energy (efficient)
  double getCrossSection( const double energy,
                          const unsigned bin_index ) const;

  //! Return the differential cross section
  double getDifferentialCrossSection( const double incoming_energy,
                                      const double outgoing_energy ) const;

  //! Return the threshold energy
  double getThresholdEnergy() const;

  //! Return the number of electrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedElectrons( const double energy ) const;

  //! Return the number of photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPhotons( const double energy ) const;

  //! Return the reaction type
  PositronatomicReactionType getReactionType() const;

  //! Simulate the reaction
  void react( PositronState& positron,
              ParticleBank& bank,
              Data::SubshellType& shell_of_interaction ) const;

protected:

  //! Return the head of the energy grid
  const double* getEnergyGridHead() const;
};

// Test if the energy falls within the energy grid
inline bool VoidAbsorptionPositronatomicReaction::isEnergyWithinEnergyGrid(
    const double energy ) const
{
  return true;
}

// Return the cross section at the given energy
inline double VoidAbsorptionPositronatomicReaction::getCrossSection(
    const double energy ) const
{
  return 0.0;
}

// Return the cross section at the given energy (efficient)
inline double VoidAbsorptionPositronatomicReaction::getCrossSection(
    const double energy,
    const unsigned bin_index ) const
{
  return 0.0;
}

// Return the differential cross section
inline double VoidAbsorptionPositronatomicReaction::getDifferentialCrossSection(
    const double incoming_energy,
    const double outgoing_energy ) const
{
  return 0.0;
}

//! Return the threshold energy
inline double VoidAbsorptionPositronatomicReaction::getThresholdEnergy() const
{
  return 1.00000e-5;
}

// Return the number of electrons emitted from the rxn at the given energy
inline unsigned VoidAbsorptionPositronatomicReaction::getNumberOfEmittedElectrons(
                                                     const double energy ) const
{
  return 0u;
}

// Return the number of photons emitted from the rxn at the given energy
inline unsigned VoidAbsorptionPositronatomicReaction::getNumberOfEmittedPhotons(
                                                     const double energy ) const
{
  return 0u;
}

// Return reaction type
inline PositronatomicReactionType VoidAbsorptionPositronatomicReaction::getReactionType() const
{
  return TOTAL_ABSORPTION_POSITRONATOMIC_REACTION;
}

// Simulate the reaction
inline void VoidAbsorptionPositronatomicReaction::react(
       PositronState& positron,
       ParticleBank& bank,
       Data::SubshellType& shell_of_interaction ) const
{ /* ... */ }

// Return the head of the energy grid
inline const double* VoidAbsorptionPositronatomicReaction::getEnergyGridHead() const
{
  return nullptr;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_VOID_ABSORPTION_POSITRONATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_VoidAbsorptionPositronatomicReaction.hpp
//---------------------------------------------------------------------------//
