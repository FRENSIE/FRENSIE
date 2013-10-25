//---------------------------------------------------------------------------//
//!
//! \file    SimpleSprng.hpp
//! \author  ?
//! \brief   Declaration of a simple struct to aid the Sprng class 
//! \details This file originally appeared in the sprng4 library. It has been
//!          modified by Alex Robinson (aprobinson@wisc.edu) to better support
//!          the needs of FACEMC.
//!
//---------------------------------------------------------------------------//

#ifndef SIMPLE_SPRNG_HPP
#define SIMPLE_SPRNG_HPP

// Boost Includes
#include <boost/scoped_ptr.hpp>

// SPRNG Includes
#include "Sprng.hpp"

/*! \defgroup simple_sprng_interface Simple Sprng Interface
 *
 * Use this interface if only one random number generator is needed. The
 * SimpleSprng struct stores a heap allocated generator and forwards calls
 * to it. Calls to this struct are never made directly and are instead
 * wrapped in several functions which can be accessed in the global sprng
 * namespace scope. 
 */

namespace sprng{

//! A simple struct to aid the Sprng class
struct SimpleSprng
{
  
  //! Generator initialization
  static int init_rng_simple( int seed, int mult, int gtype = 0 );

  //! Generator initialization with mpi
  static int init_rng_simple_mpi( int seed, int mult, int gtype = 0 );

  //! Return a random int
  static int get_rn_int_simple();
  
  //! Return a random int with mpi
  static int get_rn_int_simple_mpi();

  //! Return a random float in interval [0,1)
  static int get_rn_flt_simple();

  //! Return a random float in interval [0,1) with mpi
  static int get_rn_flt_simple_mpi();

  //! Return a random double in interval [0,1)
  static int get_rn_dbl_simple();

  //! Return a random double in interval [0,1) with mpi
  static int get_rn_dbl_simple_mpi();

  //! Pack a generator into a character buffer
  static int pack_rng_simple( std::string &buffer );

  //! Unpack a generator from a character buffer
  static int unpack_rng_simple( std::string &packed, int gtype );
  
  //! Print the generator info
  static int print_rng_simple();
  
private:

  // pointer to default generator (auto initializes to NULL)
  static boost::scoped_ptr<Sprng> default_generator;
};  

//! Generator initialization
int init_rng_simple( int seed, int mult, int gtype = 0 );

//! Generator initialization with mpi
int init_rng_simple_mpi( int seed, int mult, int gtype = 0 );

//! Return a random int
int get_rn_int_simple();
  
//! Return a random int with mpi
int get_rn_int_simple_mpi();

//! Return a random float in interval [0,1)
int get_rn_flt_simple();

//! Return a random float in interval [0,1) with mpi
int get_rn_flt_simple_mpi();

//! Return a random double in interval [0,1)
int get_rn_dbl_simple();

//! Return a random double in interval [0,1) with mpi
int get_rn_dbl_simple_mpi();

//! Pack a generator into a character buffer
int pack_rng_simple( std::string &buffer );

//! Unpack a generator from a character buffer
int unpack_rng_simple( std::string &packed, int gtype );
  
//! Print the generator info
int print_rng_simple();

} // end namespace sprng

//---------------------------------------------------------------------------//
// Definition includes.
//---------------------------------------------------------------------------//
 
#include "SimpleSprng_def.hpp"

//---------------------------------------------------------------------------//

#endif // end SIMPLE_SPRNG_HPP

//---------------------------------------------------------------------------//
// end SimpleSprng.hpp
//---------------------------------------------------------------------------//
