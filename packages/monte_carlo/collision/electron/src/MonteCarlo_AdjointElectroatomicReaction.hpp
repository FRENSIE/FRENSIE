//---------------------------------------------------------------------------//
//!
//! \file MonteCarlo_AdjointElectroAtomicReaction.hpp
//! \author Luke Kersting
//! \brief The Adjoint Electron reaction base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_ELECTROATOMIC_REACTION_HPP
#define MONTE_CARLO_ADJOINT_ELECTROATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_AdjointElectronState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_AdjointAtomicReaction.hpp"
#include "MonteCarlo_AdjointElectroatomicReactionType.hpp"
#include "MonteCarlo_StandardReactionBaseImpl.hpp"
#include "Data_SubshellType.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_DistributionTraits.hpp"

namespace MonteCarlo{

//! The electron/positron reaction base class
class AdjointElectroatomicReaction : public AdjointAtomicReaction
{

public:

  //! The trials counter type
  typedef Utility::DistributionTraits::Counter Counter;

  //! Constructor
  AdjointElectroatomicReaction()
  { /* ... */ }

  //! Destructor
  virtual ~AdjointElectroatomicReaction()
  { /* ... */}

  //! Return the reaction type
  virtual AdjointElectroatomicReactionType getReactionType() const = 0;

  //! Simulate the reaction
  virtual void react( AdjointElectronState& electron,
                      ParticleBank& bank,
                      Data::SubshellType& shell_of_interaction ) const = 0;

  //! Simulate the reaction and track the number of sampling trials
  virtual void react( AdjointElectronState& electron,
                      ParticleBank& bank,
                      Data::SubshellType& shell_of_interaction,
                      Counter& trials ) const;

};

// Simulate the reaction and track the number of sampling trials
inline void AdjointElectroatomicReaction::react(
                AdjointElectronState& electron,
                ParticleBank& bank,
                Data::SubshellType& shell_of_interaction,
                Counter& trials ) const
{
  ++trials;

  this->react( electron, bank, shell_of_interaction );
}

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<AdjointElectroatomicReaction,Utility::LinLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<AdjointElectroatomicReaction,Utility::LinLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<AdjointElectroatomicReaction,Utility::LinLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<AdjointElectroatomicReaction,Utility::LinLog,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<AdjointElectroatomicReaction,Utility::LogLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<AdjointElectroatomicReaction,Utility::LogLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<AdjointElectroatomicReaction,Utility::LogLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<AdjointElectroatomicReaction,Utility::LogLog,true> );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_ELECTROATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectroAtomicReaction.hpp
//---------------------------------------------------------------------------//
