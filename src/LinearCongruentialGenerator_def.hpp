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

// Return a random number for the current history
template<typename ScalarType>
inline ScalarType LinearCongruentialGenerator::rnd()
{
  // Advance the generator state
  advanceState();
    
  // Return the uniform random number (state*2^-64)
  return static_cast<ScalarType>( d_state*5.4210108624275222e-20 );
}

} // end FACEMC namespace

#endif // end LINEAR_CONGRUENTIAL_GENERATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end LinearCongruentialGenerator_def.hpp
//---------------------------------------------------------------------------//
