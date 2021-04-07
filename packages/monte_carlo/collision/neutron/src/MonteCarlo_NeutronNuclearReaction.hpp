//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NuclearReaction.hpp
//! \author Alex Robinson
//! \brief  The nuclear reaction base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NEUTRON_NUCLEAR_REACTION_HPP
#define MONTE_CARLO_NEUTRON_NUCLEAR_REACTION_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_NuclearReactionType.hpp"
#include "MonteCarlo_StandardReactionBaseImpl.hpp"
#include "MonteCarlo_NuclearReaction.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"

namespace MonteCarlo{

//! The nuclear reaction base class
class NeutronNuclearReaction : public NuclearReaction
{

public:

  //! Constructor
  NeutronNuclearReaction()
  { /* ... */ }

  //! Destructor
  virtual ~NeutronNuclearReaction()
  { /* ... */ }

  //! Return the reaction type
  virtual NuclearReactionType getReactionType() const = 0;

  //! Return the temperature (in MeV) at which the reaction occurs
  virtual double getTemperature() const = 0;

  //! Simulate the reaction
  virtual void react( NeutronState& neutron, ParticleBank& bank ) const = 0;
};

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<NeutronNuclearReaction,Utility::LinLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<NeutronNuclearReaction,Utility::LinLin,true> );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_NEUTRON_NUCLEAR_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearReaction.hpp
//---------------------------------------------------------------------------//
