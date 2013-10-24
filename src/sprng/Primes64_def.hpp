//---------------------------------------------------------------------------//
//! 
//! \file    Primes64.hpp
//! \author  ?
//! \brief   Prime array helper function definitions.
//! \details This file originally appeared in the sprng4 library. It has been
//!          modified by Alex Robinson (aprobinson@wisc.edu) to better support
//!          the needs of FACEMC.
//!
//---------------------------------------------------------------------------//

#ifndef PRIMES_64_DEF_HPP
#define PRIMES_64_DEF_HPP

// Std Lib Includes
#include <cstdio>
#include <cstdlib>
#include <cstring>

// Trilinos Includes
#include <Teuch_ArrayView.hpp>

#define MAXPRIME 3037000501U  /* largest odd # < sqrt(2)*2^31+2 */
#define MINPRIME 55108   /* sqrt(MAXPRIME) */
#define MAXPRIMEOFFSET 146138719U /* Total number of available primes */
#define PRIMELISTSIZE1 1000
#define STEP 10000
#define YES 1
#define NO  0

namespace SPRNG{

// Initialize the primes global array
int init_prime_64()
{
  {
  int i, j, obtained = 0, isprime;
  
  for(i=3; i < MINPRIME; i += 2)
  {
    isprime = YES;
    
    for(j=0; j < obtained; j++)
      if(i%primes[j] == 0)
      {
	isprime = NO;
	break;
      }
    else if(primes[j]*primes[j] > i)
      break;

    if(isprime == YES)
    {
      primes[obtained] = i;
      obtained++;
    }
  }
  
  return obtained;
}

// Get the number of primes requested
int getprime_64( int need, 
		 Teuchos::ArrayRCP<unsigned int> prime_array,
		 int offset )
{
  static int initiallized = NO, num_prime;
  unsigned int largest;
  int i, isprime, index, obtained = 0;

  prime_array.resize( need );
  
  if(need <= 0)
  {
    fprintf(stderr,"WARNING: Number of primes needed = %d < 1; None returned\n"
	    , need);
    return 0;
  }
  
  if(offset < 0)
  {
    fprintf(stderr,"WARNING: Offset of prime = %d < 1; None returned\n"
	    , offset);
    return 0;
  }
  

  if(offset+need-1<PRIMELISTSIZE1) 
  {
    Teuchos::ArrayView partial_prime_array( prime_list_64+offset, need );
    prime_array.deepCopy( partial_prime_array );
    //memcpy(prime_array,prime_list_64+offset,need*sizeof(unsigned int));
    return need;
  }

  if(!initiallized)
  {
    num_prime = init_prime_64();

    
    largest = MAXPRIME;
    initiallized = YES;
  }
  
  if(offset > MAXPRIMEOFFSET)
  {
    fprintf(stderr,"WARNING: generator has branched maximum number of times;\nindependence of generators no longer guaranteed");
    offset = offset % MAXPRIMEOFFSET;
  }
  
  if(offset < PRIMELISTSIZE1)	/* search table for previous prime */
  {
    largest = prime_list_64[offset] + 2;
    offset = 0;
  }
  else
  {
    index = (unsigned int) ((offset-PRIMELISTSIZE1+1)/STEP) + PRIMELISTSIZE1 -  1;
    largest = prime_list_64[index] + 2;
    offset -= (index-PRIMELISTSIZE1+1)*STEP + PRIMELISTSIZE1 - 1;
  }
  
  
  while(need > obtained && largest > MINPRIME)
  {
    isprime = YES;
    largest -= 2;
    for(i=0; i<num_prime; i++)
      if(largest%primes[i] == 0)
      {
	isprime = NO;
	break;
      }
    
    if(isprime == YES && offset > 0)
      offset--;
    else if(isprime == YES)
      prime_array[obtained++] = largest;
  }
  
  if(need > obtained)
    fprintf(stderr,"ERROR: Insufficient number of primes: needed %d, obtained %d\n", need, obtained);
  
  return obtained;
}

} // end SPRNG namespace

#endif // end PRIMES_64_DEF_HPP

//---------------------------------------------------------------------------//
// end Primes64_def.hpp
//---------------------------------------------------------------------------//
