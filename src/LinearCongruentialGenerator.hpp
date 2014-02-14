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
  virtual double getRandomNumber();

  //! Initialize the generator for the desired history
  void changeHistory( const unsigned long long history_number );

  //! Initialize the generator for the next history
  void nextHistory();

protected:

  //! Advance the generator state
  void advanceState();

private:

  // Initial seed of generator
  static const unsigned long long initial_seed = 19073486328125ULL;

  // Random number seed multiplier (g)
  static const unsigned long long multiplier = 19073486328125ULL;

  // Random number stride between starting seed of consecutive histories (L)
  static const unsigned long long stride = 152917ULL;

  // Initial random number seed for current history (sh)
  unsigned long long d_initial_history_seed;

  // Random number state (sk)
  unsigned long long d_state;

  // History counter
  unsigned long long d_history;
};

// Advance the generator state
inline void LinearCongruentialGenerator::advanceState()
{
  d_state *= LinearCongruentialGenerator::multiplier;
}

} // end FACEMC namespace

#endif // end LINEAR_CONGRUENTIAL_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end LinearCongruentialGenerator.hpp
//---------------------------------------------------------------------------//
