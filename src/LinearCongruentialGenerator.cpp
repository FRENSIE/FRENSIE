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
  : d_initial_history_seed( LinearCongruentialGenerator::initial_seed ),
    d_state( d_initial_history_seed ),
    d_history( 0ULL )
{ /* ... */ }

// Initialize the generator for the desired history
void LinearCongruentialGenerator::changeHistory( 
				      const unsigned long long history_number )
{
  unsigned long long history_diff = history_number - d_history;

  d_history = history_number;

  // Initialize the generator state
  d_initial_history_seed = Exponentiation::recursive( 
			    d_initial_history_seed, 
		            history_diff*LinearCongruentialGenerator::stride );
  
  d_state = d_initial_history_seed;
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end LinearCongruentialGenerator.cpp
//---------------------------------------------------------------------------//
