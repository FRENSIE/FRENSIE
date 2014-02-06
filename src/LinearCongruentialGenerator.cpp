//---------------------------------------------------------------------------//
//!
//! \file   LinearCongruentialGenerator.cpp
//! \author Alex Robinson
//! \brief  Definition of a linear congruential pseudo-random number 
//!         generator that can be used to create reproducible parallel random
//!         number streams.
//!
//---------------------------------------------------------------------------//

// FACEMC Includes
#include "LinearCongruentialGenerator.hpp"

namespace FACEMC{

// Constructor
LinearCongruentialGenerator::LinearCongruentialGenerator()
  : d_initial_history_seed( d_initial_seed ),
    d_state( d_initial_history_seed ),
    d_history( 0 )
{ /* ... */ }

// Initialize the generator for the desired history
void LinearCongruentialGenerator::changeHistory( 
				      const unsigned long long history_number )
{
  d_history = history_number;

  unsigned long long history_diff = history_number - d_history;

  // Initialize the generator state
  d_initial_history_seed = exponentiate( d_initial_history_seed, 
					 history_diff*d_stride );
  d_state = d_initial_history_seed;
}

// Advance the generator state
void LinearCongruentialGenerator::advanceState()
{
  d_state *= d_multiplier;
}

// A recursive modular exponentiation algorithm
/*! \details Recursively evaluates the function (x^y)mod(2^64). This algorithm 
 * was taken from "Algorithms" by Desgupta et al.
 */
unsigned long long LinearCongruentialGenerator::exponentiate( 
					     const unsigned long long x,
					     const unsigned long long y ) const
{
  // The output integer
  unsigned long long z;

  if( y == 0 )
    z = 1;
  else
  {
    z = exponentiate( x, y/2 );
    
    if( y%2 == 0 )
      z = (z*z);
    else
      z = (x*z*z);
  }

  // Return the output integer
  return z;
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end LinearCongruentialGenerator.cpp
//---------------------------------------------------------------------------//
