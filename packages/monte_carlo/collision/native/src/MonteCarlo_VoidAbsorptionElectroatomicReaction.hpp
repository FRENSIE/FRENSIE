//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_VoidAbsorptionElectroatomicReaction.hpp
//! \author Luke Kersting
//! \brief  The void absorption electroatomic reaction class decl.
//! 
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_VOID_ABSORPTION_ELECTROATOMIC_REACTION_HPP
#define MONTE_CARLO_VOID_ABSORPTION_ELECTROATOMIC_REACTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroatomicReaction.hpp"

namespace MonteCarlo{

/*! The void absorption electroatomic reaction class
* \details This class can be used to ignore absorption reactions.
*/

class VoidAbsorptionElectroatomicReaction : public ElectroatomicReaction
{

public:

  //! Constructor
  VoidAbsorptionElectroatomicReaction()
  { /* ... */ }

  //! Destructor
  ~VoidAbsorptionElectroatomicReaction()
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
  ElectroatomicReactionType getReactionType() const;

  //! Simulate the reaction
  void react( ElectronState& electron, 
		      ParticleBank& bank,
		      SubshellType& shell_of_interaction ) const;

protected:

  //! Return the head of the energy grid
  const double* getEnergyGridHead() const;
};

// Test if the energy falls within the energy grid
inline bool VoidAbsorptionElectroatomicReaction::isEnergyWithinEnergyGrid( 
    const double energy ) const
{
  return true;
}

// Return the cross section at the given energy
inline double VoidAbsorptionElectroatomicReaction::getCrossSection( 
    const double energy ) const
{
  return 0.0;
}

// Return the cross section at the given energy (efficient)
inline double VoidAbsorptionElectroatomicReaction::getCrossSection( 
    const double energy,
    const unsigned bin_index ) const
{
  return 0.0;
}

//! Return the threshold energy
inline double VoidAbsorptionElectroatomicReaction::getThresholdEnergy() const
{ 
  return 1.00000e-5;
}

// Return the number of electrons emitted from the rxn at the given energy
inline unsigned VoidAbsorptionElectroatomicReaction::getNumberOfEmittedElectrons( 
                                                     const double energy ) const
{
  return 0u;
}

// Return the number of photons emitted from the rxn at the given energy
inline unsigned VoidAbsorptionElectroatomicReaction::getNumberOfEmittedPhotons( 
                                                     const double energy ) const
{
  return 0u;
}

// Return reaction type
inline ElectroatomicReactionType VoidAbsorptionElectroatomicReaction::getReactionType() const
{
  return TOTAL_ABSORPTION_ELECTROATOMIC_REACTION;
}

// Simulate the reaction
inline void VoidAbsorptionElectroatomicReaction::react( 
       ElectronState& electron, 
       ParticleBank& bank,
       SubshellType& shell_of_interaction ) const
{ /* ... */ }

// Return the head of the energy grid
inline const double* VoidAbsorptionElectroatomicReaction::getEnergyGridHead() const
{
  return nullptr;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_VOID_ABSORPTION_ELECTROATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_VoidAbsorptionElectroatomicReaction.hpp
//---------------------------------------------------------------------------//
