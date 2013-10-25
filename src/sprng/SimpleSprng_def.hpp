//---------------------------------------------------------------------------//
//!
//! \file    SimpleSprng_def.hpp
//! \author  ?
//! \brief   Definition of inline simple sprng interface
//! \details This file originally appeared in the sprng4 library. It has been
//!          modified by Alex Robinson (aprobinson@wisc.edu) to better support
//!          the needs of FACEMC.
//!
//---------------------------------------------------------------------------//

#ifndef SIMPLE_SPRNG_DEF_HPP
#define SIMPLE_SPRNG_DEF_HPP

namespace sprng{

// Generator initialization
/*! \ingroup simple_sprng_interface
 */
inline int init_rng_simple( int seed, int mult, int gtype )
{ return SimpleSprng::init_rng_simple( seed, mult, gtype ); }

// Generator initialization with mpi
/*! \ingroup simple_sprng_interface
 */
inline int init_rng_simple_mpi( int seed, int mult, int gtype )
{ return SimpleSprng::init_rng_simple_mpi( seed, mult, gtype ); }

// Return a random int
/*! \ingroup simple_sprng_interface
 */
inline int get_rn_int_simple()
{ return SimpleSprng::get_rn_int_simple(); }
  
// Return a random int with mpi
/*! \ingroup simple_sprng_interface
 */
inline int get_rn_int_simple_mpi()
{ return SimpleSprng::get_rn_int_simple_mpi(); }

// Return a random float in interval [0,1)
/*! \ingroup simple_sprng_interface
 */
inline int get_rn_flt_simple()
{ return SimpleSprng::get_rn_flt_simple(); }

// Return a random float in interval [0,1) with mpi
/*! \ingroup simple_sprng_interface
 */
inline int get_rn_flt_simple_mpi()
{ return SimpleSprng::get_rn_flt_simple_mpi(); }

// Return a random double in interval [0,1)
/*! \ingroup simple_sprng_interface
 */
inline int get_rn_dbl_simple()
{ return SimpleSprng::get_rn_dbl_simple(); }

// Return a random double in interval [0,1) with mpi
/*! \ingroup simple_sprng_interface
 */
inline int get_rn_dbl_simple_mpi()
{ return SimpleSprng::get_rn_dbl_simple_mpi(); }

// Pack a generator into a character buffer
/*! \ingroup simple_sprng_interface
 */
inline int pack_rng_simple( std::string &buffer )
{ return SimpleSprng::pack_rng_simple( buffer ); }

// Unpack a generator from a character buffer
/*! \ingroup simple_sprng_interface
 */
inline int unpack_rng_simple( std::string &packed, int gtype )
{ return SimpleSprng::unpack_rng_simple( packed, gtype ); }
  
// Print the generator info
/*! \ingroup simple_sprng_interface
 */
inline int print_rng_simple()
{ return SimpleSprng::print_rng_simple(); }

} // end namespace sprng

#endif // end SIMPLE_SPRNG_DEF_HPP

//---------------------------------------------------------------------------//
// end SimpleSprng_def.hpp
//---------------------------------------------------------------------------//

