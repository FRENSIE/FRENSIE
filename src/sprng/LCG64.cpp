//---------------------------------------------------------------------------//
//!
//! \file    LCG64.cpp
//! \author  ?
//! \brief   Definition of the 64bit linear congruential generator class
//! \details This file originally appeared in the sprng4 library. It has been
//!          modified by Alex Robinson (aprobinson@wisc.edu) to better support
//!          the needs of FACEMC.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

// SPRNG Includes
#include "LCG64.hpp"
#include "Primes64.hpp"
#include "Store.hpp"

#define GENTYPE "64 bit Linear Congruential Generator with Prime Addend"
#define INIT_SEED1 0x2bc6ffffU
#define INIT_SEED0 0x8cfe166dU
#define TWO_M22  2.384185791015625e-07 /* 2^(-22) */
#define TWO_P22  4194304  /* 2^(22) */
#define TWO_M20  9.5367431640625e-07 /* 2^(-20) */
#define TWO_P20  1048576 /* 2^(20) */
#define TWO_M42  2.273736754432321e-13 /* 2^(-42) */
#define TWO_M64 5.4210108624275222e-20 /* 2^(-64) */
#define EXPO 0x3ff0000000000000ULL


namespace SPRNG{

// Default constructor
LCG64::LCG64()
: d_rng_type( LCG64 ),
  d_gentype( GENTYPE ),
  d_stream_number( 0 ),
  d_init_seed( 0 ),
  d_parameter( 0 ),
  d_spawn_offset( 0 ),
  d_prime( 0 ),
  d_state( 0 ),
  d_multiplier( 0 )
{ /* ... */ }

// Copy constructor
LCG64::LCG64( const LCG64 &c )
: d_rng_type( c.d_rng_type ),
  d_gentype( c.d_gentype ),
  d_stream_number( c.d_stream_number ),
  d_init_seed( c.d_init_seed ),
  d_parameter( c.d_parameter ),
  d_spawn_offset( c.d_spawn_offset ),
  d_prime( c.d_prime ),
  d_state( c.d_state ),
  d_multiplier( c.d_multiplier )
{ /* ... */ }

// Assignment operator
LCG64& LCG64::operator=( const LCG64 &c )
{
  if( this != &c )
  {
    this->free_rnd();
    
    d_rng_type = c.d_rng_type;
    d_gentype = c.d_gentype;
    d_stream_number = c.d_stream_number;
    d_init_seed = c.d_init_seed;
    d_parameter = c.d_parameter;
    d_spawn_offset = c.d_spawn_offset;
    d_prime = c.d_prime;
    d_state = c.d_state;
    d_multiplier = c.d_multiplier;
  }

  return *this;
}
  
// Destructor
LCG64::~LCG64()
{
  free_rng();
}

// Initialize the generator
/*! \details Gives back one stream (node gn) with updated spawning info. It
 * should be called tn times with a different value of gn in [0,tn) each call.
 */
int LCG64::init_rng( int gn, int tg, int s, int m )
{
  int i;
  double tempdbl;

  // Check if tn is valid?
  if (tg <= 0) 
  {
    tg = 1;
    fprintf(stderr,"WARNING - lcg64 init_rng: Total_gen <= 0. Default value of 1 used for total_gen\n");
  }

  // Check if gn is valid
  if (gn >= LCG64::max_streams) 
    fprintf(stderr,"WARNING - lcg64 init_rng: gennum: %d > maximum number of independent streams: %d\n\tIndependence of streams cannot be guranteed.\n",
	    gn, LCG64::max_streams); 
  
  if (gn < 0 || gn >= tg) 
  {
    fprintf(stderr,"ERROR - lcg64 init_rng: gennum %d out of range [%d,%d).\n",
	    gn, 0, tg); 
    return 0;
  }

  // Check if the parameter is valid
  if (m < 0 || m >= 3)   
  {
    fprintf(stderr,"WARNING - lcg64 init_rng: parameter not valid. Using Default parameter.\n");
    m = 0;
  }

  // Set the generator type
  d_rng_type = LCG64;

  // Set the generator type description
  d_gentype = GENTYPE;

  // Set the stream number
  d_stream_number = gn;
  
  // Set the initial seed (only 31 LSB of seed considered)
  d_init_seed = s & 0x7fffffff; 

  // Set the parameter
  d_parameter = m;

  // Set the spawn offset
  d_spawn_offset = tg;

  // Set the prime for this generator
  Primes64::getprime_64( d_prime, gn );
  
  // Set the multiplier
  d_multiplier = ((unsigned long long) LCG64::parameter_list[m][1])<<32 | ((unsigned long long) LCG64::parameter_list[m][0]);

  // Set the generator state
  d_state = (((unsigned long long) INIT_SEED1)<<32 | INIT_SEED0) ^(((unsigned long long) s<<33)|gn);

  // Initialize this generator
  for(i=0; i<127*d_stream_number; i++)
    tempdbl = get_rn_dbl();
  
  // Increment the number of LCG64 streams being used
  LCG64::num_generators++;

  return 1;
}
  
// Return a random int
int LCG64::get_rn_int()
{
  advance_state();
  return state>>33;
}

// Return a random float in interval [0,1)
float LCG64::get_rnd_flt()
{
  return (float)get_rn_dbl();
}

// Return a random double in interval [0,1)
double LCG64::get_rnd_dbl()
{
  static double dtemp[1] = {0.0};

  advance_state();	
#if defined(CONVEX) || defined(O2K) || defined(SGI) || defined(GENERIC)
  *((unsigned long long *) dtemp) = (state>>12) | EXPO;
  return *dtemp - (double) 1.0;
#else
  return d_state*TWO_M64;
#endif
}

// Spawn new generators
int LCG64::spawn_rng( int nspawned, Sprng ***newgens )
{

}

// Return the generator seed
  int get_seed_rng()

// Free the memory allocated to this generator
  int free_rng()

// Pack this generator into a character buffer
  int pack_rng( std::string &buffer )

// Print this generators info
  int print_rng()

// Unpack this generator from a character buffer
  int unpack_rng( std::string &packed )

// Advance the seed state
void advance_state()

} // end SPRNG namespace

//---------------------------------------------------------------------------//
// end LCG64.cpp
//---------------------------------------------------------------------------//

