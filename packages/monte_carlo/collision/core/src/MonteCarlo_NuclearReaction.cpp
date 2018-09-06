//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NuclearReaction.hpp
//! \author Alex Robinson
//! \brief  The nuclear reaction base class declaration
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <math.h>

// FRENSIE Includes
#include "MonteCarlo_NuclearReaction.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Return the average number of emitted primary outgoing particles
/*! \details If the average number of emitted particles for the reaction is not
 * an integer at the desired energy, this function should be overridden in the 
 * derived class. It will be used in implicit multiplication weighting games.
 */
double NuclearReaction::getAverageNumberOfEmittedParticles(
                                                    const double energy ) const
{
  return this->getNumberOfEmittedParticles( energy );
}

// Return an integer number of emitted particles given an average value
/*! In reality, only an integer number of particles can be released per
 * reaction. The integer return type of this function reflects this reality.
 * The integer value is sampled so that the expected value is the average
 * number of emitted particles.
 */
unsigned NuclearReaction::sampleNumberOfEmittedParticles(
                       const double average_number_of_emitted_particles ) const
{
  // Make sure that the average emitted particles is valid
  testPrecondition( average_number_of_emitted_particles >= 0.0 );

  double floor_multiplicity;
  double round_down_prob =
    1.0 - std::modf(average_number_of_emitted_particles, &floor_multiplicity);

  if( Utility::RandomNumberGenerator::getRandomNumber<double>() <
      round_down_prob )
    return (unsigned)floor_multiplicity;
  else
    return (unsigned)floor_multiplicity + 1u;
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearReaction.cpp
//---------------------------------------------------------------------------//
