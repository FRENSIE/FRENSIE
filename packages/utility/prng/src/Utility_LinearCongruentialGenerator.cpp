//---------------------------------------------------------------------------//
//!
//! \file   Utility_LinearCongruentialGenerator.cpp
//! \author Alex Robinson
//! \brief  Definition of a linear congruential pseudo-random number
//!         generator that can be used to create reproducible parallel random
//!         number streams.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_LinearCongruentialGenerator.hpp"
#include "Utility_ExponentiationAlgorithms.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{

// Constructor
LinearCongruentialGenerator::LinearCongruentialGenerator()
  : d_initial_history_seed( LinearCongruentialGenerator::initial_seed ),
    d_state( d_initial_history_seed ),
    d_history( 0ULL )
{ /* ... */ }

// Initialize the generator for the desired history
/*! \details The first history number is assumed to be 0.
 */
void LinearCongruentialGenerator::changeHistory(
				      const unsigned long long history_number )
{
  long long history_diff = (long long)history_number - d_history;

  // Set the state to the initial history seed
  if( history_number == 0ULL )
  {
    d_initial_history_seed = LinearCongruentialGenerator::initial_seed;

    d_state = d_initial_history_seed;

    d_history = history_number;
  }
  else
  {
    // Calculate the next history seed from the current history seed
    if( history_diff == 1LL )
      this->nextHistory();

    // Calculate the new history seed from the current history seed
    else if( history_diff > 1LL )
    {
      d_initial_history_seed =
	d_initial_history_seed*
	Exponentiation::recursive(
			    LinearCongruentialGenerator::multiplier,
		            history_diff*LinearCongruentialGenerator::stride );

      d_state = d_initial_history_seed;

      d_history = history_number;
    }
    // Calculate the history seed from the first history seed
    else if( history_diff < 0LL )
    {
      d_initial_history_seed =
	LinearCongruentialGenerator::initial_seed*
	Exponentiation::recursive(
			  LinearCongruentialGenerator::multiplier,
			  history_number*LinearCongruentialGenerator::stride );

      d_state = d_initial_history_seed;

      d_history = history_number;
    }

    // Set the state to the history initial seed for the current history
    else
      d_state = d_initial_history_seed;
  }
}

// Initialize the generator for the next history
void LinearCongruentialGenerator::nextHistory()
{
  d_initial_history_seed =
    d_initial_history_seed*
    Exponentiation::recursive( LinearCongruentialGenerator::multiplier,
			       LinearCongruentialGenerator::stride );

  d_state = d_initial_history_seed;

  ++d_history;
}

// Return a random number for the current history
double LinearCongruentialGenerator::getRandomNumber()
{
  // Advance the generator state
  advanceState();

  // Return the uniform random number (state*2^-64)
  return d_state*5.4210108624275222e-20;
}

// Return the state of the random number
unsigned long long LinearCongruentialGenerator::getGeneratorState() const
{
  return d_state;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_LinearCongruentialGenerator.cpp
//---------------------------------------------------------------------------//
