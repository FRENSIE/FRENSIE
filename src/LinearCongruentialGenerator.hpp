//---------------------------------------------------------------------------//
//!
//! \file   LinearCongruentialGenerator.hpp
//! \author Alex Robinson
//! \brief  Declaration of a linear congruential pseudo-random number that
//!         can be used to create reproducible parallel random number streams.
//!
//---------------------------------------------------------------------------//

#ifndef LINEAR_CONGRUENTIAL_GENERATOR_HPP
#define LINEAR_CONGRUENTIAL_GENERATOR_HPP

namespace FACEMC{

//! A linear congruential pseudo-random number generator (LCG)
template<typename ScalarType>
class LinearCongruentialGenerator
{
  
public:

  //@{
  //! Typedef for scalar type
  typedef ScalarType scalarType;
  //@}

  //! Constructor
  LinearCongruentialGenerator();

  //! Destructor
  ~LinearCongruentialGenerator()
  { /* ... */}

  //! Return a random number for the current history
  ScalarType rnd();

  //! Initialize the generator for the desired history
  void changeHistory( const unsigned long long history_number );

protected:

  //! Advance the generator state
  void advanceState();

  //! A recursive modular exponentiation algorithm
  unsigned long long exponentiate( const unsigned long long x, 
				   const unsigned long long y, 
				   const unsigned long long N ) const;

private:

  // Initial random number seed for current history (sh)
  unsigned long long d_initial_history_seed;

  // Random number state (sk)
  unsigned long long d_state;
 
  // Random number seed multiplier (g)
  unsigned long long d_multiplier;

  // LCG constant (c)
  //unsigned long long d_constant;

  // Modulus of generator (2^M)
  unsigned long long d_modulus;

  // Random number stride between starting seed of consecutive histories (L)
  unsigned long long d_stride;

  // History counter
  unsigned long long d_history;
};

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "LinearCongruentialGenerator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end LINEAR_CONGRUENTIAL_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end LinearCongruentialGenerator.hpp
//---------------------------------------------------------------------------//
