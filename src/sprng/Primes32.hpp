//---------------------------------------------------------------------------//
//!
//! \file    Primes32.hpp
//! \author  ?
//! \brief   Declaration of struct to handle 32bit primes.
//! \details This file originally appeared in the sprng4 library. It has been
//!          modified by Alex Robinson (aprobinson@wisc.edu) to better support
//!          the needs of FACEMC.
//!
//---------------------------------------------------------------------------//

#ifndef PRIMES_32_HPP
#define PRIMES_32_HPP

// Std Lib Includes
#include <vector>

namespace sprng{

//! Struct for handling 32bit primes
struct Primes32
{

public:

  //! Initialize the primes static array
  static int init_prime_32();

  //! Get the number of primes requested
  static int getprime_32( int need,
			  std::vector<unsigned int> &prime_array,
			  int offset );

  //! Get a single prime
  static int getprime_32( unsigned int &prime, int offset );

private:

  // Prime array sizes
  static int n_primes = 1000;
  static int full_prime_list_size = 1778;
  static int sub_prime_list_size = 1000;
  static int step = 1000;

  // sqrt(2)*2^23 + 2
  static int max_prime = 11863285; 
  // sqrt(max_prime)
  static int min_prime = 3444;
  // Total number of available primes
  static int max_prime_offset = 779156;
  
  // Has the primes array been initialized?
  static bool prime_list_initialized = false;

  // Prime array (once initialized, prime_list_initialized will be set to true)
  static int primes[n_primes];

  // Full prime array
  static int prime_list_32[full_prime_list_size];
};

} // end namespace sprng

//---------------------------------------------------------------------------//
// Definition includes.
//---------------------------------------------------------------------------//

#include "Primes32_def.hpp"

//---------------------------------------------------------------------------//

#endif // end PRIMES_32_HPP

//---------------------------------------------------------------------------//
// end Primes32.hpp
//---------------------------------------------------------------------------//

