//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NuclearReaction.hpp
//! \author Alex Robinson
//! \brief  The nuclear reaction base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NUCLEAR_REACTION_HPP
#define MONTE_CARLO_NUCLEAR_REACTION_HPP

// std includes
#include <cstdlib>

// FRENSIE Includes
#include "MonteCarlo_Reaction.hpp"

namespace MonteCarlo{

//! The nuclear reaction base class
class NuclearReaction : public Reaction
{

public:

  //! Constructor
  NuclearReaction()
  { /* ... */ }

  //! Destructor
  virtual ~NuclearReaction()
  { /* ... */ }

  //! Return the reaction Q value
  virtual double getQValue() const = 0;

  //! Return the number of emitted primary outgoing particles
  virtual unsigned getNumberOfEmittedParticles( const double energy ) const = 0;

  //! Return the average number of emitted primary outgoing particles
  virtual double getAverageNumberOfEmittedParticles( const double energy ) const;

protected:

  //! Return an integer number of emitted particles given an average value
  unsigned sampleNumberOfEmittedParticles(
                      const double average_number_of_emitted_particles ) const;
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_NUCLEAR_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearReaction.hpp
//---------------------------------------------------------------------------//
