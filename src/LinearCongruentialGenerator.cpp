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
#include "ExponentiationAlgorithms.hpp"

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
  d_initial_history_seed = Exponentiation::recursive( d_initial_history_seed, 
						      history_diff*d_stride );
  d_state = d_initial_history_seed;
}

// Advance the generator state
void LinearCongruentialGenerator::advanceState()
{
  d_state *= d_multiplier;
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end LinearCongruentialGenerator.cpp
//---------------------------------------------------------------------------//
