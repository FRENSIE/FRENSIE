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
#define TWO_M64 5.4210108624275222e-20 /* 2^(-64) */
#define EXPO 0x3ff0000000000000ULL


namespace sprng{

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
float LCG64::get_rn_flt()
{
  return (float)get_rn_dbl();
}

// Return a random double in interval [0,1)
double LCG64::get_rn_dbl()
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
  LCG64 ** genptr;
  int i, j;
  
  // Check that nspawned is valid
  if (nspawned <= 0) 
  {
    nspawned = 1;
    fprintf(stderr,"WARNING - spawn_rng: nspawned <= 0. Default value of 1 used for nspawned\n");
  }
  
  // Allocate memory for pointers to structures
  genptr = new LCG64 * [nspawned];

  if(genptr == NULL)	   
  {
    *newgens = NULL;
    return 0;
  }
  
  // Create nspawned new streams
  for(i=0; i<nspawned; i++)	
  {
    int s, gn;
    
    gn = d_stream_number + d_spawn_offset*(i+1);
  
    // Change seed to avoid repeating sequence
    if(gn > LCG64::max_streams)   
      s = (d_init_seed)^gn; 
    else
      s = d_init_seed;
    
    // Initialize a stream. The spawning info will be incorrect but it will be
    // corrected below.
    genptr[i] = new LCG64;
    genptr[i]->init_rng (gn, gn+1, s, d_parameter);
  
    if(genptr[i] == NULL)	/* Was generator initiallized? */
    {
      nspawned = i;
      break;
    }
    genptr[i]->d_spawn_offset = (nspawned+1)*d_spawn_offset;
  }
  
  d_spawn_offset *= (nspawned+1);
  *newgens = (Sprng **) genptr;
 
  return nspawned;
}

// Return the generator seed
int LCG64::get_seed_rng()
{
  return d_init_seed;
}

// Free the memory allocated to this generator
int LCG64::free_rng()
{
  assert( this != NULL );

  LCG64::num_generators--;
  return LCG64::num_generators;
}

// Pack this generator into a character buffer
int LCG64::pack_rng( std::string &buffer )
{
  // Clear the buffer
  buffer.clear();

  // All member data will be stored in a sub buffer and appended to main buffer
  std::string partial_buffer;

  // Store the generator type
  store_value( generatorTypeToInt( d_rng_type ), partial_buffer );
  buffer += partial_buffer;

  // Store the stream number
  store_value( d_stream_number, partial_buffer );
  buffer += partial_buffer;
  
  // Store the initial seed
  store_value( d_init_seed, partial_buffer );
  buffer += partial_buffer;
  
  // Store the parameter
  store_value( d_parameter, partial_buffer );
  buffer += partial_buffer;
  
  // Store the spawn offset
  store_value( d_spawn_offset, partial_buffer );
  buffer += d_spawn_offset;
  
  // Store the prime
  store_value( d_prime, partial_buffer );
  buffer += d_partial_buffer;
  
  // Store the state
  store_value( d_state, partial_buffer );
  buffer += partial_buffer;
  
  // Store the multiplier
  store_value( d_multiplier, partial_buffer );
  buffer += partial_buffer;

  return buffer.size();
}

// Print this generators info
int LCG64::print_rng()
{
  std::cout << d_gentype << std::endl << std::endl
	    << "\tseed = " << d_init_seed 
	    << ", stream_number = " << d_stream_number
	    << "\tparameter = " << d_parameter
	    << std::endl << std::endl;

  return 1;    
}

// Unpack this generator from a character buffer
int LCG64::unpack_rng( std::string &packed )
{
  std::size_t nbytes, offset = 0;
  int generator_type;

  // Load the generator type
  nbytes = sizeof( generator_type );
  load_value( packed.substr( offset, nbytes ), generator_type );
  d_rng_type = intToGeneratorType( generator_type );
  offset += nbytes;

  // Load the generator description (not packed because always the same)
  d_gentype = GENTYPE;

  // Load the stream number
  nbytes = sizeof( d_stream_number );
  load_value( packed.substr( offset, nbytes ), d_stream_number );
  offset += nbytes;

  // Load the initial seed
  nbytes = sizeof( d_init_seed );
  load_value( packed.substr( offset, nbytes ), d_init_seed );
  offset += nbytes;

  // Load the parameter
  nbytes = sizeof( d_parameter );
  load_value( packed.substr( offset, nbytes), d_parameter );
  offset += nbytes;
  
  // Load the spawn offset
  nbytes = sizeof( d_spawn_offset );
  load_value( packed.substr( offset, nbytes), d_spawn_offset );
  offset += nbytes;
  
  // Load the prime
  nbytes = sizeof( d_prime );
  load_value( packed.substr( offset, nbytes ), d_prime );
  offset += nbytes;
  
  // Load the state
  nbytes = sizeof( d_state );
  load_value( packed.substr( offset, nbytes ), d_state );
  offset += nbytes;
  
  // Load the multiplier
  nbytes = sizeof( d_multiplier );
  load_value( packed.substr( offset, nbytes ), d_multiplier );
  offset += nbytes;

  // Increment the number of streams
  LCG64::num_generators++;

  return 1;
}

// Advance the seed state
void LCG64::advance_state()
{
  d_state = d_state*d_multiplier + d_prime;
}

} // end namespace sprng

//---------------------------------------------------------------------------//
// end LCG64.cpp
//---------------------------------------------------------------------------//

