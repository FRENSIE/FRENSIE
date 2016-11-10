//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_VoidAbsorptionAdjointElectroatomicReaction.hpp
//! \author Luke Kersting
//! \brief  The void absorption adjoint electroatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_VOID_ABSORPTION_ADJOINT_ELECTROATOMIC_REACTION_HPP
#define MONTE_CARLO_VOID_ABSORPTION_ADJOINT_ELECTROATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatomicReaction.hpp"

namespace MonteCarlo{

/*! The void absorption adjoint electroatomic reaction class
* \details This class can be used to ignore absorption reactions.
*/

class VoidAbsorptionAdjointElectroatomicReaction : public AdjointElectroatomicReaction
{

public:

  //! Constructor
  VoidAbsorptionAdjointElectroatomicReaction()
  { /* ... */ }

  //! Destructor
  ~VoidAbsorptionAdjointElectroatomicReaction()
  { /* ... */ }

  //! Test if the energy falls within the energy grid
  bool isEnergyWithinEnergyGrid( const double energy ) const;

  //! Return the cross section at the given energy
  double getCrossSection( const double energy ) const;

  //! Return the cross section at the given energy (efficient)
  double getCrossSection( const double energy,
                          const unsigned bin_index ) const;

  //! Return the threshold energy
  double getThresholdEnergy() const;

  //! Return the number of electrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedElectrons( const double energy ) const;

  //! Return the number of photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPhotons( const double energy ) const;

  //! Return the reaction type
  AdjointElectroatomicReactionType getReactionType() const;

  //! Simulate the reaction
  void react( AdjointElectronState& electron,
              ParticleBank& bank,
              Data::SubshellType& shell_of_interaction ) const;

protected:

  //! Return the head of the energy grid
  const double* getEnergyGridHead() const;
};

// Test if the energy falls within the energy grid
inline bool VoidAbsorptionAdjointElectroatomicReaction::isEnergyWithinEnergyGrid(
    const double energy ) const
{
  return true;
}

// Return the cross section at the given energy
inline double VoidAbsorptionAdjointElectroatomicReaction::getCrossSection(
    const double energy ) const
{
  return 0.0;
}

// Return the cross section at the given energy (efficient)
inline double VoidAbsorptionAdjointElectroatomicReaction::getCrossSection(
    const double energy,
    const unsigned bin_index ) const
{
  return 0.0;
}

//! Return the threshold energy
inline double VoidAbsorptionAdjointElectroatomicReaction::getThresholdEnergy() const
{
  return 1.00000e-5;
}

// Return the number of electrons emitted from the rxn at the given energy
inline unsigned VoidAbsorptionAdjointElectroatomicReaction::getNumberOfEmittedElectrons(
                                                     const double energy ) const
{
  return 0u;
}

// Return the number of photons emitted from the rxn at the given energy
inline unsigned VoidAbsorptionAdjointElectroatomicReaction::getNumberOfEmittedPhotons(
                                                     const double energy ) const
{
  return 0u;
}

// Return reaction type
inline AdjointElectroatomicReactionType VoidAbsorptionAdjointElectroatomicReaction::getReactionType() const
{
  return TOTAL_ABSORPTION_ADJOINT_ELECTROATOMIC_REACTION;
}

// Simulate the reaction
inline void VoidAbsorptionAdjointElectroatomicReaction::react(
       AdjointElectronState& electron,
       ParticleBank& bank,
       Data::SubshellType& shell_of_interaction ) const
{ /* ... */ }

// Return the head of the energy grid
inline const double* VoidAbsorptionAdjointElectroatomicReaction::getEnergyGridHead() const
{
  return nullptr;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_VOID_ABSORPTION_ADJOINT_ELECTROATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_VoidAbsorptionAdjointElectroatomicReaction.hpp
//---------------------------------------------------------------------------//
