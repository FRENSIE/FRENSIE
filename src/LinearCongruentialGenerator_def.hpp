//---------------------------------------------------------------------------//
//!
//! \file   LinearCongruentialGenerator_def.hpp
//! \author Alex Robinson
//! \brief  Definition of a linear congruential pseudo-random number that
//!         can be used to create reproducible parallel random number streams.
//!
//---------------------------------------------------------------------------//

#ifndef LINEAR_CONGRUENTIAL_GENERATOR_DEF_HPP
#define LINEAR_CONGRUENTIAL_GENERATOR_DEF_HPP

namespace FACEMC{

// Constructor
template<typename ScalarType>
LinearCongruentialGenerator<ScalarType>::LinearCongruentialGenerator()
  : d_initial_history_seed( d_initial_seed ),
    d_state( d_initial_history_seed ),
    d_history( 0 )
{ /* ... */ }

// Return a random number for the current history
template<typename ScalarType>
ScalarType LinearCongruentialGenerator<ScalarType>::rnd()
{
  // Advance the generator state
  advanceState();
    
  // Return the uniform random number (state*2^-64)
  return d_state*5.4210108624275222e-20;
}

// Initialize the generator for the desired history
template<typename ScalarType>
void LinearCongruentialGenerator<ScalarType>::changeHistory( 
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
template<typename ScalarType>
void LinearCongruentialGenerator<ScalarType>::advanceState()
{
  d_state = d_state*d_multiplier;
}
    
// A recursive modular exponentiation algorithm
/*! \details Recursively evaluates the function (x^y)mod(2^64). This algorithm 
  was taken from "Algorithms" by Desgupta et al.
 */
template<typename ScalarType>
unsigned long long LinearCongruentialGenerator<ScalarType>::exponentiate( 
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

#endif // end LINEAR_CONGRUENTIAL_GENERATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end LinearCongruentialGenerator_def.hpp
//---------------------------------------------------------------------------//
