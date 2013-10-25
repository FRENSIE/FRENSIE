//---------------------------------------------------------------------------//
//! 
//! \file    Primes64.hpp
//! \author  ?
//! \brief   Declaration of struct to handle 64bit primes.
//! \details This file originally appeared in the sprng4 library. It has been
//!          modified by Alex Robinson (aprobinson@wisc.edu) to better support
//!          the needs of FACEMC.
//!
//---------------------------------------------------------------------------//

#ifndef PRIMES_64_HPP
#define PRIMES_64_HPP

// Std Lib Includes
#include <vector>

namespace sprng{

//! Struct for handling 64bit primes
struct Primes64
{

public:

  //! Initialize the primes static array
  static int init_prime_64();
  
  //! Get the number of primes requested
  static int getprime_64( int need, 
			  std::vector<unsigned int> prime_array,
			  int offset );

  //! Get a single prime
  static int getprime_64( unsigned int &prime, int offset );

private:

  // Prime array sizes
  static int n_primes = 10000;
  static int full_prime_list_size = 15613;
  static int sub_prime_list_size = 1000;
  static int step = 10000;

  // Largest odd # < sqrt(2)*2^31+2 
  static unsigned int max_prime = 3037000501U; 
  // sqrt(max_prime)
  static unsigned int min_prime = 55108U;
  // Total number of available primes
  static unsigned int max_prime_offset = 146138719U;
  
  // Has the primes array been initialized?
  static bool prime_list_initialized = false;

  // Prime array (once initialized, prime_list_initialized will be set to true)
  static int primes[n_primes];

  // Full prime array
  static unsigned int prime_list_64[full_prime_list_size];
};

} // end namespace sprng

//---------------------------------------------------------------------------//
// Definition includes.
//---------------------------------------------------------------------------//

#include "Primes64_def.hpp"

//---------------------------------------------------------------------------//

#endif // end PRIMES_64_HPP

//---------------------------------------------------------------------------//
// end Primes64.hpp
//---------------------------------------------------------------------------//
