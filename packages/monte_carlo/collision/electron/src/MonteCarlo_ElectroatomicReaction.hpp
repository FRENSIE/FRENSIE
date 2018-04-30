//---------------------------------------------------------------------------//
//!
//! \file MonteCarlo_ElectroAtomicReaction.hpp
//! \author Luke Kersting
//! \brief The Electron reaction base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROATOMIC_REACTION_HPP
#define MONTE_CARLO_ELECTROATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_AtomicReaction.hpp"
#include "MonteCarlo_ElectroatomicReactionType.hpp"
#include "MonteCarlo_StandardReactionBaseImpl.hpp"
#include "Data_SubshellType.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_DistributionTraits.hpp"

namespace MonteCarlo{

//! The electron reaction base class
class ElectroatomicReaction : public AtomicReaction
{

public:

  //! The trials counter type
  typedef Utility::DistributionTraits::Counter Counter;

  //!Constructor
  ElectroatomicReaction()
  { /* ... */ }

  //!Destructor
  virtual ~ElectroatomicReaction()
  { /* ... */}

  //! Return the reaction type
  virtual ElectroatomicReactionType getReactionType() const = 0;

  //! Return the differential cross section
  virtual double getDifferentialCrossSection( const double incoming_energy,
                                              const double secondary_variable ) const = 0;

  //! Simulate the reaction
  virtual void react( ElectronState& electron,
                      ParticleBank& bank,
                      Data::SubshellType& shell_of_interaction ) const = 0;

  //! Simulate the reaction and track the number of sampling trials
  virtual void react( ElectronState& electron,
                      ParticleBank& bank,
                      Data::SubshellType& shell_of_interaction,
                      Counter& trials ) const;

};

// Simulate the reaction and track the number of sampling trials
inline void ElectroatomicReaction::react(
                ElectronState& electron,
                ParticleBank& bank,
                Data::SubshellType& shell_of_interaction,
                Counter& trials ) const
{
  ++trials;

  this->react( electron, bank, shell_of_interaction );
}

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<ElectroatomicReaction,Utility::LinLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<ElectroatomicReaction,Utility::LinLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<ElectroatomicReaction,Utility::LinLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<ElectroatomicReaction,Utility::LinLog,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<ElectroatomicReaction,Utility::LogLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<ElectroatomicReaction,Utility::LogLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<ElectroatomicReaction,Utility::LogLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<ElectroatomicReaction,Utility::LogLog,true> );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTROATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroAtomicReaction.hpp
//---------------------------------------------------------------------------//
