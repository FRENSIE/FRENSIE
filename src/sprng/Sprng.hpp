//---------------------------------------------------------------------------//
//!
//! \file    Spring.hpp
//! \author  ?
//! \brief   Declaration of main Sprng abstract base class
//! \details This file originally appeared in the sprng4 library. It has been
//!          modified by Alex Robinson (aprobinson@wisc.edu) to better support
//!          the needs of FACEMC.
//!
//---------------------------------------------------------------------------//

#ifndef SPRNG_HPP
#define SPRNG_HPP

// Std Lib Includes
#include <string>

namespace sprng{

//! The main Sprng abstract base class
class Sprng
{
  
public:
  
  //! Destructor
  virtual ~Sprng()
  { /* ... */ }

  //! Initialize the generator
  virtual int init_rng( int gn, int tg, int s, int m ) = 0;
  
  //! Return a random int
  virtual int get_rn_int() = 0;

  //! Return a random float in interval [0,1)
  virtual float get_rn_flt() = 0;

  //! Return a random double in interval [0,1)
  virtual double get_rn_dbl() = 0;

  //! Spawn new generators
  virtual int spawn_rng( int nspawned, Sprng ***newgens ) = 0;

  //! Return the generator seed
  virtual int get_seed_rng() = 0;

  //! Free the memory allocated to this generator
  virtual int free_rng() = 0;

  //! Pack this generator into a character buffer
  virtual int pack_rng( std::string &buffer ) = 0;

  //! Print this generators info
  virtual int print_rng() = 0;

  //! Unpack this generator from a character buffer
  virtual int unpack_rng( std::string &packed ) = 0;
};

} // end namespace sprng

#endif // end SPRNG_HPP

//---------------------------------------------------------------------------//
// end Sprng.hpp
//---------------------------------------------------------------------------//
