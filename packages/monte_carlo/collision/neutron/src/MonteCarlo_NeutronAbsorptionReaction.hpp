//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NeutronAbsorptionReaction.hpp
//! \author Alex Robinson
//! \brief  The neutron absorption reaction class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NEUTRON_ABSORPTION_REACTION_HPP
#define MONTE_CARLO_NEUTRON_ABSORPTION_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardNeutronNuclearReaction.hpp"
#include "Utility_QuantityTraits.hpp"

namespace MonteCarlo{

//! The neutron absorption reaction class
class NeutronAbsorptionReaction : public StandardNeutronNuclearReaction
{
  // Typedef for QuantityTraits
  typedef Utility::QuantityTraits<double> QT;

public:

  //! Inherit base constructors
  using StandardNeutronNuclearReaction::StandardNeutronNuclearReaction;

  //! Destructor
  ~NeutronAbsorptionReaction()
  { /* ... */ }

  //! Return the number of neutrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedParticles( const double energy ) const override;

  //! Simulate the reaction
  virtual void react( NeutronState& neutron, ParticleBank& bank ) const override;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_NEUTRON_ABSORPTION_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronAbsorptionReaction.hpp
//---------------------------------------------------------------------------//
