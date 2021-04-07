//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotoatomicReaction.hpp
//! \author Alex Robinson
//! \brief  The photoatomic reaction base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTOATOMIC_REACTION_HPP
#define MONTE_CARLO_PHOTOATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_AtomicReaction.hpp"
#include "MonteCarlo_PhotoatomicReactionType.hpp"
#include "MonteCarlo_StandardReactionBaseImpl.hpp"
#include "Data_SubshellType.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_DistributionTraits.hpp"

namespace MonteCarlo{

//! The photoatomic reaction base class
class PhotoatomicReaction : public AtomicReaction
{

public:

  //! The trials counter type
  typedef Utility::DistributionTraits::Counter Counter;

  //! Constructor
  PhotoatomicReaction()
  { /* ... */ }

  //! Destructor
  virtual ~PhotoatomicReaction()
  { /* ... */ }

  //! Return the reaction type
  virtual PhotoatomicReactionType getReactionType() const = 0;

  //! Simulate the reaction
  virtual void react( PhotonState& photon,
		      ParticleBank& bank,
		      Data::SubshellType& shell_of_interaction ) const = 0;

  //! Simulate the reaction and track the number of sampling trials
  virtual void react( PhotonState& photon,
		      ParticleBank& bank,
		      Data::SubshellType& shell_of_interaction,
		      Counter& trials ) const;

};

// Simulate the reaction and track the number of sampling trials
inline void PhotoatomicReaction::react(
        PhotonState& photon,
        ParticleBank& bank,
        Data::SubshellType& shell_of_interaction,
        Counter& trials ) const
{
  ++trials;

  this->react( photon, bank, shell_of_interaction );
}

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<PhotoatomicReaction,Utility::LinLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<PhotoatomicReaction,Utility::LinLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<PhotoatomicReaction,Utility::LinLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<PhotoatomicReaction,Utility::LinLog,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<PhotoatomicReaction,Utility::LogLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<PhotoatomicReaction,Utility::LogLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<PhotoatomicReaction,Utility::LogLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<PhotoatomicReaction,Utility::LogLog,true> );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTOATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotoatomicReaction.hpp
//---------------------------------------------------------------------------//
