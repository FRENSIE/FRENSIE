//---------------------------------------------------------------------------//
//!
//! \file    Store.hpp
//! \author  ?
//! \brief   Definition of array storage functions.
//! \details Numbers are stored with the most significant bit first (left 
//!          most). This file originally appeared in the sprng4 library. It has
//!          been modified by Alex Robinson (aprobinson@wisc.edu) to better 
//!          support the needs of FACEMC.
//!
//---------------------------------------------------------------------------//

#ifndef STORE_DEF_HPP
#define STORE_DEF_HPP

// Std Lib Includes
#include <iostream>
#include <cstdio>

namespace SPRNG{

// Store an unsigned long in a character buffer
int store_long( unsigned long l, int nbytes, unsigned char *c )
{
  int i;
  
  for(i=0; i<nbytes; i++)
    c[i] = (l>>(8*(nbytes-i-1)))&0xff;
  
  return nbytes;		/* return number of chars filled */
}

// Store an array of unsigned longs in a character buffer
int store_longarray( unsigned long *l, int n, int nbytes, unsigned char *c )
{
  int i;
  
  for(i=0; i<n; i++)
    c += store_long(l[i],nbytes,c);

  return nbytes*n;
}

// Load an unsigned long from a character buffer
int load_long( unsigned char *c, int nbytes, unsigned long *l )
{
  int i;
  
  *l = 0;
  
  for(i=0; i<nbytes;i++)
    *l = (*l<<8) + (c[i]&0xff);
 
  return nbytes;
}

// Load an array of unsigned longs from a character buffer
int load_longarray( unsigned char *c, int n, int nbytes, unsigned long *l )
{
  int i;
  
  for(i=0; i<n; i++)
    load_long(c+nbytes*i,nbytes,l+i);

  return nbytes*n;
}

// Store an int in a character buffer
int store_int( unsigned int l, int nbytes, unsigned char *c )
{
  int i;
  
  for(i=0; i<nbytes; i++)
    c[i] = (l>>(8*(nbytes-i-1)))&0xff;

  return nbytes;		/* return number of chars filled */
}

// Store an array of ints in a character buffer
int store_intarray( unsigned int *l, int n, int nbytes, unsigned char *c )
{
  int i;
  
  for(i=0; i<n; i++)
    c += store_int(l[i],nbytes,c);

  return nbytes*n;
}

// Load an int from a character buffer
int load_int( unsigned char *c, int nbytes, unsigned int *l )
{
  int i;
  
  *l = 0;
  
  for(i=0; i<nbytes;i++)
    *l = (*l<<8) + (c[i]&0xff);
 
  return nbytes;
}

// Load an array of ints from a charater buffer
int load_intarray( unsigned char *c, int n, int nbytes, unsigned int *l )
{
  int i;
  
  for(i=0; i<n; i++)
    load_int(c+nbytes*i,nbytes,l+i);

  return nbytes*n;
}

// Store a long long in a character buffer
int store_longlong( unsigned long long l, int nbytes, unsigned char *c )
{
  int i;
  
  for(i=0; i<nbytes; i++)
    c[i] = (l>>(8*(nbytes-i-1)))&0xff;
  
  return nbytes;		/* return number of chars filled */
}
  
// Store an array of long longs in a character buffer
int store_longlongarray( unsigned long long *l, int n, int nbytes, unsigned char *c )
{
  int i;
 
  for(i=0; i<n; i++)
    c += store_longlong(l[i],nbytes,c);

  return nbytes*n;
}

// Load a long long from a character buffer
int load_longlong( unsigned char *c, int nbytes, unsigned long long *l )
{
  int i;
 
  *l = 0;
  
  for(i=0; i<nbytes;i++)
    *l = (*l<<8) + (c[i]&0xff);
 
  return nbytes;
}

// Load a long long from a character buffer
int load_longlongarray( unsigned char *c, int n, int nbytes, unsigned long long *l )
{
  int i;

  for(i=0; i<n; i++)
    load_longlong(c+nbytes*i,nbytes,l+i);

  return nbytes*n;
}

} // end SPRNG namespace

#endif // end STORE_DEF_HPP

//---------------------------------------------------------------------------//
// end Store_def.hpp
//---------------------------------------------------------------------------//
