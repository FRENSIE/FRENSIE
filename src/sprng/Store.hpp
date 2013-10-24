//---------------------------------------------------------------------------//
//!
//! \file    Store.hpp
//! \author  ?
//! \brief   Declaration of array storage functions.
//! \details Numbers are stored with the most significant bit first (left 
//!          most). This file originally appeared in the sprng4 library. It has
//!          been modified by Alex Robinson (aprobinson@wisc.edu) to better 
//!          support the needs of FACEMC.
//!
//---------------------------------------------------------------------------//

#ifndef STORE_HPP
#define STORE_HPP

namespace SPRNG{

//! Store an unsigned long in a character buffer
int store_long( unsigned long l, int nbytes, unsigned char *c );

//! Store an array of unsigned longs in a character buffer
int store_longarray( unsigned long *l, int n, int nbytes, unsigned char *c );

//! Load an unsigned long from a character buffer
int load_long( unsigned char *c, int nbytes, unsigned long *l );

//! Load an array of unsigned longs from a character buffer
int load_longarray( unsigned char *c, int n, int nbytes, unsigned long *l );

//! Store an int in a character buffer
int store_int( unsigned int l, int nbytes, unsigned char *c );

//! Store an array of ints in a character buffer
int store_intarray( unsigned int *l, int n, int nbytes, unsigned char *c );

//! Load an int from a character buffer
int load_int( unsigned char *c, int nbytes, unsigned int *l );

//! Load an array of ints from a charater buffer
int load_intarray( unsigned char *c, int n, int nbytes, unsigned int *l );

//! Store a long long in a character buffer
int store_longlong( unsigned long long l, int nbytes, unsigned char *c );
  
//! Store an array of long longs in a character buffer
int store_longlongarray( unsigned long long *l, int n, int nbytes, unsigned char *c );

//! Load a long long from a character buffer
int load_longlong( unsigned char *c, int nbytes, unsigned long long *l );

//! Load a long long from a character buffer
int load_longlongarray( unsigned char *c, int n, int nbytes, unsigned long long *l );

} // end SPRNG namespace

//---------------------------------------------------------------------------//
// Definition includes.
//---------------------------------------------------------------------------//

#include "Store_def.hpp"

//---------------------------------------------------------------------------//

#endif // end STORE_HPP

//---------------------------------------------------------------------------//
// end Store.hpp
//---------------------------------------------------------------------------//
