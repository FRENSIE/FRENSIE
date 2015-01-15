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

  //! Return the cross section at the given energy
  double getCrossSection( const double energy ) const;

  //! Return the threshold energy
  double getThresholdEnergy() const;

  //! Return the number of electrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedElectrons( const double energy ) const;

  //! Return the number of photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPhotons( const double energy ) const;

  //! Return reaction type
  ElectroatomicReactionType getReactionType() const;

  //! Simulate the reaction
  void react( ElectronState& electron, 
              ParticleBank& bank,
              SubshellType& shell_of_interaction ) const;
};

// Return the cross section at the given energy
inline double VoidAbsorptionElectroatomicReaction::getCrossSection( 
                                                     const double energy ) const
{
  return 0.0;
}

//! Return the threshold energy
inline double VoidAbsorptionElectroatomicReaction::getThresholdEnergy() const
{ 
  return 0.0;
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

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_VOID_ABSORPTION_ELECTROATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_VoidAbsorptionElectroatomicReaction.hpp
//---------------------------------------------------------------------------//
