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
/*! \details A modulus of 2^64 is used so that modular arithmetic is done
 * implicitly (using integer overflow).
 */
class LinearCongruentialGenerator
{
  
public:

  //! Constructor
  LinearCongruentialGenerator();

  //! Destructor
  ~LinearCongruentialGenerator()
  { /* ... */}

  //! Return a random number for the current history
  template<typename ScalarType>
  ScalarType rnd();

  //! Initialize the generator for the desired history
  void changeHistory( const unsigned long long history_number );

protected:

  //! Advance the generator state
  void advanceState();

  //! A recursive modular exponentiation algorithm (assuming mod 2^64)
  unsigned long long exponentiate( const unsigned long long x, 
				   const unsigned long long y ) const;

private:

  // Initial seed of generator
  static const unsigned long long d_initial_seed = 19073486328125ULL;

  // Random number seed multiplier (g)
  static const unsigned long long d_multiplier = 19073486328125ULL;

  // Random number stride between starting seed of consecutive histories (L)
  static const unsigned long long d_stride = 152917ULL;

  // Initial random number seed for current history (sh)
  unsigned long long d_initial_history_seed;

  // Random number state (sk)
  unsigned long long d_state;

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
