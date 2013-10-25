//---------------------------------------------------------------------------//
//!
//! \file    BigNum_def.hpp
//! \author  J. Ren (Florida State University, ren@csit.fsu.edu)
//! \brief   Implementation file for arithmetic on large integers
//! \details This file originally appeared in the sprng4 library. It has been
//!          modified by Alex Robinson (aprobinson@wisc.edu) to better support
//!          the needs of FACEMC.
//!
//---------------------------------------------------------------------------//

#ifndef BIG_NUM_DEF_HPP
#define BIG_NUM_DEF_HPP

// Std Lib Includes
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <iomanip>
#include <ctype.h>
#include <cstring>

using namespace std;

#define NUMBITS 64

namespace sprng{

// Default constructor
BigNum::BigNum()
  : d_size( 1 ),
    d_v( d_size ),
    d_sign( '+' )
{
  d_v[0] = 0;
}

// Constructor by size
BigNum::BigNum( unsigned long s )
  : d_size( s ),
    d_sign( '+' ),
    d_v( s )
{
  for( unsigned long i = 0; i < s; i++ )
    d_v[i] = 0;
}

// Implicit conversion from char* to BigNum
BigNum::BigNum( char* c, char s )
{
  unsigned long hexdigits = strlen( c );
  unsigned long index;
  int n = NUMBITS / 4;
  int mod = hexdigits % n;
  int i, temp;

  d_sign = s;

  if( mod == 0 )
    d_size = hexdigits / n;
  else
    d_size = hexdigits / n + 1;

  d_v.resize( d_size );

  if( mod > 0 )
  {
    index = d_size - 1;
    d_v[index] = 0;

    temp = mod * 4 - 4;

    for( i = temp; i >= 0; i-=4 )
      d_v[index] = d_v[index] ^ (static_cast<unsigned long int>(C2I(*c++)) << static_cast<unsigned long int>(i));

    index = d_size - 1;
  }
  else
    index = d_size;

  for( unsigned long j = index; j > 0; j-- )
  {
    temp = j - 1;

    d_v[temp] = 0;

    for( i = NUMBITS - 4; i >= 0; i-= 4 )
      d_v[temp] = d_v[temp] ^ (static_cast<unsigned long int>(C2I(*c++)) << static_cast<unsigned long int>(i));
  }
}

// Copy constructor
BigNum::BigNum( const BigNum &bn )
  : d_size( bn.d_size ),
    d_sign( bn.d_sign ),
    d_v( d_size )
{
  // Do a deep copy of the stored array
  for( unsigned long i = 0; i < d_size; i++ )
    d_v[i] = bn.d_v[i];
}

// Assignment operator
BigNum& operator=( const BigNum &bn )
{
  if( this != &bn )
  {
    if( d_size != bn.d_size )
      d_v.resize( bn.d_size );
    
    d_size = bn.d_size;
    d_sign = bn.d_sign;

    // Do a deep copy of the stored array
    for( unsigned long i = 0; i < d_size; i++ )
      d_v[i] = bn.d_v[i];
  }

  return *this;      
}

// Get the unsigned long
unsigned long BigNum::b_get_ui() const
{
  return d_v[0];
}

// Get the size of the unsigned long array
unsigned long BigNum::Size() const
{
  return d_size;
}

// Get the head of the unsigned long array
unsigned long* BigNum::V() const
{
  return &d_v[0];
}

// Get the sign of the BigNum
char BigNum::Sign() const
{
  return d_sign;
}

// Erase the leading bits of the BigNum
BigNum BigNum::EraseLeadingBits( unsigned long numbits )
{
  unsigned long int zsize;
  unsigned long int modulus;
  unsigned long int *zptr, *xptr;
  unsigned long int xbits;
  unsigned long int shiftamount;

  xbits = GetTotalBits();
  zsize = CeilDiv(GetTotalBits() - numbits, NUMBITS);
  modulus = numbits % NUMBITS;
  shiftamount = NUMBITS - (xbits - modulus) % NUMBITS;
  BigNum z(zsize);

  zptr = z.V();
  xptr = V();

  for (unsigned int i = 0; i < z.size; i++)
    *(zptr++) = *(xptr++);

  *(zptr--);
  *zptr = (*zptr << shiftamount) >> shiftamount;

  if (z.d_size != 1)
    while (*zptr == 0 && z.d_size != 1) {
      *(zptr--);
      z.d_size--;
    }

  return z;
}

// Get the total number of bits in the BigNum
unsigned long BigNum::GetTotalBits() const
{
  return (d_size - 1) * NUMBITS + GetNumBits( d_v[d_size - 1] );
}

// Free the unsigned long array
void BigNum::b_clear() const
{
  d_v.clear();
  d_size = 0;
  d_sign = 0;
}

// Print the BigNum with its sign
void BigNum::b_print_w_sign() const
{
  cout << d_sign << *this;
}

// Set BigNum as an unsigned long 
BigNum Set_ui( unsigned long n )
{
  BigNum bn;
  
  bn.d_v[0] = n;

  return bn;
}

// Set BigNum as a signed long
BigNum Set_si( signed long n )
{
  BigNum bn;

  if( n < 0 )
  {
    bn.d_sign = '-';
    bn.d_v[0] = 0 - n;
  }
  else
    bn.d_v[0] = n;

  return bn;
}

// BigNum addition operator
BigNum operator+( const BigNum &x, const BigNum &y )
{
  unsigned long int * xptr, * yptr, * zptr;
  unsigned long int zsize;
  unsigned long int temp, andtemp, ztemp;
  unsigned long int carry = 0;
  unsigned long int smallersize = SmallerSize(x, y);
  unsigned long int biggersize = BiggerSize(x, y);
  unsigned long int i;
  BigNum zero;

  if (x.d_sign == '-') {
    if (y.d_sign == '-')
      return b_neg(b_abs(x) + b_abs(y));
    else if (y.d_sign == '+') {
      if (b_cmp(b_abs(x), y) < 0)
	return y - b_abs(x);
      else if (b_cmp(b_abs(x), y) > 0)
	return b_neg(b_abs(x) - y);
      else if (b_cmp(b_abs(x), y) == 0)
	return zero;
    }  
  }
  else if (x.d_sign == '+' && y.d_sign == '-') {
    if (b_cmp(x, b_abs(y)) < 0)
      return b_neg(b_abs(y) - x);
    else if (b_cmp(x, b_abs(y)) > 0)
      return x - b_abs(y);
    else if (b_cmp(x, b_abs(y)) == 0)
      return zero; 
  }

  if (x.d_size > y.d_size)
    zd_size = x.d_size + 1;
  else
    zd_size = y.d_size + 1;

  BigNum z(zsize);
  xptr = x.V();
  yptr = y.V();
  zptr = z.V();

  for (i = 0; i < smallersize; i++) {
    ztemp = *zptr;
    *zptr ^= *xptr ^ *yptr;
    andtemp = *xptr & *yptr | *xptr & ztemp | *yptr & ztemp;

    if ((Test(*xptr, NUMBITS - 1) == 1) && (Test(*yptr, NUMBITS - 1) == 1)) {
      *zptr = Set(*(++zptr), 0);
      *(zptr--);
    }

    carry = andtemp << 1;

    do {
      andtemp = carry & *zptr;

      if ((Test(carry, NUMBITS - 1) == 1) && (Test(*zptr, NUMBITS - 1) == 1)) {
	*zptr = Set(*(++zptr), 0);
	*(zptr--);
      }

      temp = andtemp << 1;
      *zptr ^= carry;
      carry = temp;
    } while (temp != 0);

    *(++xptr);
    *(++yptr);
    *(++zptr);
  }

  if (x.d_size != y.d_size) {
    if (*zptr == 0) {
      if (smallersize == x.d_size) {
	while (i < z.d_size - 1) {
	  *(zptr++) = *(yptr++);
	  i++;
	}
      }
      else {
	while (i < z.d_size - 1) {
	  *(zptr++) = *(xptr++);
	  i++;
	}
      }
    }
    else {
      if (smallersize == x.d_size) {
	for (i = smallersize; i < biggersize; i++) {
	  ztemp = *zptr;
	  *zptr ^= *yptr;
	  andtemp = *yptr & ztemp;
	  carry = andtemp << 1;

	  do {
	    andtemp = carry & *zptr;

	    if ((Test(carry, NUMBITS - 1) == 1) && (Test(*zptr, NUMBITS - 1) == 1)) {
	      *zptr = Set(*(++zptr), 0);
	      *(zptr--);
	    }

	    temp = andtemp << 1;
	    *zptr ^= carry;
	    carry = temp;
	  } while (temp != 0);

	  *(++yptr);
	  *(++zptr);
	}
      }
      else {
	for (i = smallersize; i < biggersize; i++) {
	  ztemp = *zptr;
	  *zptr ^= *xptr;
	  andtemp = *xptr & ztemp;
	  carry = andtemp << 1;

	  do {
	    andtemp = carry & *zptr;

	    if ((Test(carry, NUMBITS - 1) == 1) && (Test(*zptr, NUMBITS - 1) == 1)) {
	      *zptr = Set(*(++zptr), 0);
	      *(zptr--);
	    }

	    temp = andtemp << 1;
	    *zptr ^= carry;
	    carry = temp;
	  } while (temp != 0);

	  *(++xptr);
	  *(++zptr);
	}
      }
    }
  }

  if (*zptr == 0) 
    z.d_size--;

  zero.b_clear();

  return z;
}

// BigNum and unsigned long addition operator
BigNum operator+( const BignNum &x, const unsigned long y )
{
  BigNum bn_y = Set_ui(y);

  return x + bn_y;
}

// BigNum subtraction operator
BigNum operator-( const BigNum &x, const BigNum &y )
{
  unsigned long int *xptr, *yptr, *zptr;
  unsigned long int i;
  unsigned long int temp, andtemp, ztemp;
  unsigned long int carry = 0;
  unsigned long int biggersize = BiggerSize(x, y);
  unsigned long int smallersize = SmallerSize(x, y);
  BigNum zero;

  if (x.d_sign == '+' && y.d_sign == '+' && b_cmp(x, y) == -1)
    return b_neg(y - x);
  else if ((x.d_sign == '-' && y.d_sign == '-') || (x.d_sign == '+' && y.d_sign == '-'))
    return x + b_neg(y);
  else if (x.d_sign == '-' && y.d_sign == '+')
    return b_neg(b_abs(x) + y);

  BigNum z(biggersize + 1);
  xptr = x.V();
  yptr = y.V();
  zptr = z.V();

  for (i = 0; i < smallersize; i++) {
    ztemp = *zptr;
    *zptr ^= *xptr ^ *yptr;
    andtemp = (*yptr & *zptr) | (ztemp == 1 && Test(*xptr, 0) == 0 &&
				 (Test(*yptr, 0) == 0 | Test(*yptr, 0) == 1));

    if ((Test(*xptr, NUMBITS - 1) == 0) && (Test(*yptr, NUMBITS - 1) == 1)) {
      *zptr = Set(*(++zptr), 0);
      *(zptr--);
    }

    carry = andtemp << 1;

    do {
      andtemp = (carry ^ *zptr) & carry;

      if ((Test(carry, NUMBITS - 1) == 1) && (Test(*zptr, NUMBITS - 1) == 0)) {
	*zptr = Set(*(++zptr), 0);
	*(zptr--);
      }

      temp = andtemp << 1;
      *zptr ^= carry;
      carry = temp;
    } while (temp != 0);

    *(++xptr);
    *(++yptr);
    *(++zptr);
  }

  if (x.d_size != y.d_size) {
    if (*zptr == 0 && smallersize == y.d_size) {
      while (i < biggersize) {
	i++;
	*(zptr++) = *(xptr++);
      }
    }
    else {
      if (smallersize == x.d_size) {
	for (i = smallersize; i < biggersize; i++) {
	  ztemp = *zptr;
	  *zptr ^= *yptr;
	  andtemp = (*yptr & *zptr) | (ztemp == 1 &&
				       (Test(*yptr, 0) == 0 | Test(*yptr, 0) == 1));

	  if (Test(*yptr, NUMBITS - 1) == 1) {
	    *zptr = Set(*(++zptr), 0);
	    *(zptr--);
	  }

	  carry = andtemp << 1;

	  do {
	    andtemp = (carry ^ *zptr) & carry;

	    if ((Test(carry, NUMBITS - 1) == 1) && (Test(*zptr, NUMBITS - 1) == 0)) {
	      *zptr = Set(*(++zptr), 0);
	      *(zptr--);
	    }

	    temp = andtemp << 1;
	    *zptr ^= carry;
	    carry = temp;
	  } while (temp != 0);

	  *(++yptr);
	  *(++zptr);
	}
      }
      else {
	for (i = smallersize; i < biggersize; i++) {
	  ztemp = *zptr;
	  *zptr ^= *xptr;
	  andtemp = (ztemp == 1 && Test(*xptr, 0) == 0);
	  carry = andtemp << 1;

	  do {
	    andtemp = (carry ^ *zptr) & carry;

	    if ((Test(carry, NUMBITS - 1) == 1) && (Test(*zptr, NUMBITS - 1) == 0)) {
	      *zptr = Set(*(++zptr), 0);
	      *(zptr--);
	    }

	    temp = andtemp << 1;
	    *zptr ^= carry;
	    carry = temp;
	  } while (temp != 0);

	  *(++xptr);
	  *(++zptr);
	}
      }
    }
  }

  if (z.d_size != 1) {
    while (*zptr == 0) {
      *(zptr--);
      z.d_size--;
    }
  }

  if (z.d_size == 0) {
    z.d_size++;
    z.d_v[0] = 0;
  }

  if ((x.d_size < y.d_size) || (x.d_size == y.d_size && z.d_size > x.d_size))
    z.d_sign = '-';

  zero.b_clear();

  return z;
}

// BigNum and unsigned long subtraction operator
BigNum operator-( const BigNum &x, const unsigned long y )
{
  BigNum bn_y = Set_ui(y);

  return x - bn_y;
}

// BigNum multiplication operator
BigNum operator*( const BigNum &x, const BigNum &y )
{
  unsigned long int j, k;
  unsigned long int ysize;
  int i;
  unsigned long int *yptr;
  BigNum z(1);
  BigNum xcopy, ycopy;

  if (x.d_sign == '-' && y.d_sign == '-')
    return b_abs(x) * b_abs(y);
  else if (x.d_sign != y.d_sign)
    return b_neg(b_abs(x) * b_abs(y)); 

  if (x.d_size < y.d_size) {
    xcopy = y;
    ycopy = x;
    yptr = ycopy.V();
    ysize = ycopy.d_size;
  }
  else {
    xcopy = x;
    yptr = y.V();
    ysize = y.d_size;
  }

  k = 0;

  for (j = 0; j < ysize; j++) {
    for (i = 0; i < NUMBITS; i++) {
      if (Test(*yptr, i) == 1) {
	if (k != 0) {
	  xcopy = xcopy << k;
	  k = 0;
	}

	z = z + xcopy;
	xcopy = xcopy << 1;
      }
      else
	k++;
    }

    *(yptr++);
  }

  xcopy.b_clear();
  ycopy.b_clear();

  return z;
}

// BigNum and unsigned long multiplication operator
BigNum operator*( const BigNum &x, const unsigned long y )
{
  BigNum bn_y = Set_ui(y);

  return x * bn_y;
}

// BigNum division substitute function
BigNum Sub4Div( const BigNum &x, const BigNum &y )
{
  unsigned long int *xptr, *yptr, *zptr;
  unsigned long int i;
  unsigned long int temp, andtemp, ztemp;
  unsigned long int carry = 0;
  unsigned long int biggersize = BiggerSize(x, y);
  unsigned long int smallersize = SmallerSize(x, y);
  BigNum zero;
  BigNum z(biggersize + 1);
  xptr = x.V();
  yptr = y.V();
  zptr = z.V();

  for (i = 0; i < smallersize; i++) {
    ztemp = *zptr;
    *zptr ^= *xptr ^ *yptr;
    andtemp = (*yptr & *zptr) | (ztemp == 1 && Test(*xptr, 0) == 0 &&
				 (Test(*yptr, 0) == 0 | Test(*yptr, 0) == 1));

    if ((Test(*xptr, NUMBITS - 1) == 0) && (Test(*yptr, NUMBITS - 1) == 1)) {
      *zptr = Set(*(++zptr), 0);
      *(zptr--);
    }

    carry = andtemp << 1;

    do {
      andtemp = (carry ^ *zptr) & carry;

      if ((Test(carry, NUMBITS - 1) == 1) && (Test(*zptr, NUMBITS - 1) == 0)) {
	*zptr = Set(*(++zptr), 0);
	*(zptr--);
      }

      temp = andtemp << 1;
      *zptr ^= carry;
      carry = temp;
    } while (temp != 0);

    *(++xptr);
    *(++yptr);
    *(++zptr);
  }

  if (x.d_size != y.d_size) {
    if (*zptr == 0 && smallersize == y.d_size) {
      while (i < biggersize) {
	i++;
	*(zptr++) = *(xptr++);
      }
    }
    else {
      if (smallersize == x.d_size) {
	for (i = smallersize; i < biggersize; i++) {
	  ztemp = *zptr;
	  *zptr ^= *yptr;
	  andtemp = (*yptr & *zptr) | (ztemp == 1 &&
				       (Test(*yptr, 0) == 0 | Test(*yptr, 0) == 1));

	  if (Test(*yptr, NUMBITS - 1) == 1) {
	    *zptr = Set(*(++zptr), 0);
	    *(zptr--);
	  }

	  carry = andtemp << 1;

	  do {
	    andtemp = (carry ^ *zptr) & carry;

	    if ((Test(carry, NUMBITS - 1) == 1) && (Test(*zptr, NUMBITS - 1) == 0)) {
	      *zptr = Set(*(++zptr), 0);
	      *(zptr--);
	    }

	    temp = andtemp << 1;
	    *zptr ^= carry;
	    carry = temp;
	  } while (temp != 0);

	  *(++yptr);
	  *(++zptr);
	}
      }
      else {
	for (i = smallersize; i < biggersize; i++) {
	  ztemp = *zptr;
	  *zptr ^= *xptr;
	  andtemp = (ztemp == 1 && Test(*xptr, 0) == 0);
	  carry = andtemp << 1;

	  do {
	    andtemp = (carry ^ *zptr) & carry;

	    if ((Test(carry, NUMBITS - 1) == 1) && (Test(*zptr, NUMBITS - 1) == 0)) {
	      *zptr = Set(*(++zptr), 0);
	      *(zptr--);
	    }

	    temp = andtemp << 1;
	    *zptr ^= carry;
	    carry = temp;
	  } while (temp != 0);

	  *(++xptr);
	  *(++zptr);
	}
      }
    }
  }

  if (z.d_size != 1) {
    while (*zptr == 0) {
      *(zptr--);
      z.d_size--;
    }
  }

  if (z.d_size == 0) {
    z.d_size++;
    z.d_v[0] = 0;
  }

  if ((x.d_size < y.d_size) || (x.d_size == y.d_size && z.d_size > x.d_size))
    z.d_sign = '-';

  zero.b_clear();

  return z;
}

// BigNum division operator
BigNum operator/( const BigNum &x, const BigNum &y )
{
  BigNum z;
  BigNum xcopy = x;
  BigNum xtemp, t;
  BigNum difference;
  BigNum zero(1);
  unsigned long int diffbits = 0;
  unsigned long int lostbits;
  unsigned long int tempbits;
  unsigned long int xtempbits;
  unsigned long int shiftbits;
  unsigned long int xbits = x.GetTotalBits();
  unsigned long int ybits = y.GetTotalBits();
  bool prevneg = false;

  if (x.d_sign == '-' && y.d_sign == '-')
    return b_abs(x) / b_abs(y);
  else if (x.d_sign != y.d_sign)
    return b_neg(b_abs(x) / b_abs(y)); 

  if (y == zero) {
    cerr << "Division by 0 error";
    exit(EXIT_FAILURE);
  }

  if (ybits > xbits)
    return zero;

  z = zero;

  while (true) {
    xbits = xcopy.GetTotalBits();

    if (prevneg == false)
      xtemp = xcopy >> (xbits - ybits);
    else
      xtemp = xcopy >> (xbits - ybits - 1);

    if (xbits < ybits) {
      z = z << (xbits - diffbits);
      break;
    }

    difference = Sub4Div(xtemp, y);
    diffbits = difference.GetTotalBits();
    xtempbits = xtemp.GetTotalBits();
    z = z << shiftbits;

    if (difference == zero) {
      z = z << 1;
      z = z ^ 1;
      shiftbits = ybits - 1;
      tempbits = xbits - ybits;

      if (tempbits == 0)
	break;

      xcopy = xcopy.EraseLeadingBits(ybits);
      lostbits = tempbits - xcopy.GetTotalBits();
      z = z << lostbits;
      prevneg = false;
    }
    else if (difference.d_sign == '-') {
      z = z << 1;
      tempbits = xbits - ybits;
      shiftbits = 0;

      if (tempbits == 0)
	break;

      prevneg = true;
    }
    else { /* difference is non-zero positive */
      z = z << 1;
      z = z ^ 1;
      tempbits = xbits - ybits;

      if (prevneg == false) {
	if (tempbits == 0)
	  break;

	xcopy = xcopy.EraseLeadingBits(ybits);
	lostbits = tempbits - xcopy.GetTotalBits();
      }
      else {
	if (tempbits - 1 == 0)
	  break;

	xcopy = xcopy.EraseLeadingBits(ybits + 1);
	lostbits = tempbits - xcopy.GetTotalBits() - 1;
      }

      xbits = xcopy.GetTotalBits();

      if (lostbits == 0) {
	t = difference << xbits;
	xcopy = t ^ xcopy;
      }
      else {
	t = difference << (xbits + lostbits);
	xcopy = t ^ xcopy;
      }

      if (ybits == diffbits) {
	shiftbits =  0;
	prevneg = true;
      }
      else {
	shiftbits = ybits - diffbits - 1;
	prevneg = false;
      }
    }
  }

  xtemp.b_clear();
  t.b_clear();
  difference.b_clear();
  zero.b_clear();

  return z;
}
  
// BigNum and unsigned long division operator
BigNum operator/( const BigNum &x, const unsigned long y )
{
  BigNum bn_y = Set_ui(y);

  return x / bn_y;
}

// BigNum modulo operator
BigNum operator%( const BigNum &x, const BigNum &y )
{
  if (x.GetTotalBits() < y.GetTotalBits())
    return x;

  if (x.sign == '+')
    return x - x / y * y;
  else 
    return y - b_abs(x) % y;
}
  
// BigNum and unsigned long modulo operator
BigNum operator%( const BigNum &x, const unsigned long y )
{
  BigNum bn_y = Set_ui(y);

  return x % bn_y;
}

// BigNum bitwise exclusive or operator
BigNum operator^( const BigNum &x, const BigNum &y )
{
  unsigned long int zsize;
  unsigned long int biggersize, smallersize;
  unsigned long int *xptr, *yptr, *zptr;
  unsigned long int i;

  biggersize = BiggerSize(x, y);
  smallersize = SmallerSize(x, y);
  zsize = biggersize;
  BigNum z(zsize);
  xptr = x.V();
  yptr = y.V();
  zptr = z.V();

  for (i = 0; i < smallersize; i++)
    *(zptr++) = *(xptr++) ^ *(yptr++);

  if (biggersize == smallersize)
    return z;

  if (biggersize == x.d_size) {
    for (i = smallersize; i < biggersize; i++)
      *(zptr++) = *(xptr++);

    while (*(zptr--) == 0 && zsize > 1)
      zsize--;
  }
  else
    for (i = smallersize; i < biggersize; i++)
      *(zptr++) = *(yptr++);

  return z;
}

// BigNum and unsigned long bitwise exclusive or operator
BigNum operator^( const BigNum &x, const unsigned long y )
{
  BigNum z = x;
  *(z.v) ^= y;

  return z;
}

// BigNum and unsigned long bitwise and operator
unsigned long operator&( const BigNum &x, const unsigned long y )
{
  return x.d_v[0] & y;
}

// BigNum and unsigned long right bitshift operator
BigNum operator>>( const BigNum &x, const unsigned long y )
{
  unsigned long int indexmod;
  unsigned long int zsize;
  unsigned long int lastbits;
  unsigned long int bitscopy = 0;
  unsigned long int *xptr, *zptr;
  unsigned long int xbits = x.GetTotalBits();
  unsigned long int shiftamount;
  unsigned long int zfirstbits;
  unsigned long int i;
  BigNum zero(1);

  if (index >= xbits)
    return zero;

  zsize = CeilDiv(xbits - index, NUMBITS);
  indexmod = index % NUMBITS;
  shiftamount = NUMBITS - indexmod;
  BigNum z(zsize);
  zfirstbits = (xbits - index) % NUMBITS;
  xptr = &(x.d_v[x.d_size-1]);
  zptr = &(z.d_v[z.d_size-1]);

  if (index == 0 || x == zero)
    return x;

  if (indexmod == 0) {
    for (i = 0; i < zsize; i++)
      *(zptr--) = *(xptr--);
  }
  else {
    if (GetNumBits(*xptr) < static_cast<int>(zfirstbits % NUMBITS) || ((xbits - index) % NUMBITS == 0)) {
      bitscopy = *xptr << shiftamount;
      *(xptr--);
    }

    for (i = 0; i < zsize; i++) {
      *zptr = *xptr;
      lastbits = *zptr << shiftamount;
      *zptr >>= indexmod;
      *zptr ^= bitscopy;
      bitscopy = lastbits;
      *(xptr--);
      *(zptr--);
    }
  }

  zero.b_clear();

  return z;
}

// BigNum and unsigned long left bitshift operator
BigNum operator<<( const BigNum &x, const unsigned long y )
{
  BigNum zero(1);

  if (index == 0 || x == zero) {
    return x;
  }
  
  unsigned long int indexmod;
  unsigned long int zsize;
  unsigned long int amount;
  unsigned long int shiftamount;
  unsigned long int firstbits;
  unsigned long int bitscopy = 0;
  unsigned long int *xptr, *zptr;
  unsigned long int i;
  zsize = CeilDiv(index + x.GetTotalBits(), NUMBITS);
  indexmod = index % NUMBITS;
  amount = (index - indexmod) / NUMBITS;
  shiftamount = NUMBITS - indexmod;
  BigNum z(zsize);

  xptr = x.V();
  zptr = z.V();

  for (i = 0; i < amount; i++)
    *(zptr++) = 0;

  if (indexmod == 0) {
    for (i = 0; i < x.d_size; i++)
      *(zptr++) = *(xptr++);
  }
  else {
    for (i = 0; i < x.d_size; i++) {
      *zptr = *xptr;
      firstbits = *zptr >> shiftamount;
      *zptr <<= indexmod;
      *zptr ^= bitscopy;
      bitscopy = firstbits;
      *(xptr++);
      *(zptr++);
    }
  }

  if (x.d_size + amount < zsize)
    *zptr = bitscopy;

  zero.b_clear();

  return z;
}

// BigNum divided by 2^(ex_of_2)
BigNum b_div_2exp( const BigNum &x, const unsigned long ex_of_2 )
{
  BigNum two = "2";
  BigNum z = x / (two << (ex_of_2 - 1));

  two.b_clear();

  return z;
}

// BigNum exponentiation
BigNum b_pow( const BigNum &base, const unsigned long exp )
{
   BigNum product = "1";

  for (unsigned long int i = 0; i < exp; i++) 
    product = product * base;

  return product;
}

// BigNum modular exponentiation
BigNum b_powm( const BigNum &base, 
	       const BigNum &exp, 
	       const BigNum &mod )
{
  BigNum product = "1";
  BigNum ex = exp;
  BigNum y = base;
  unsigned long int zero = 0;

  if (exp.d_sign == '-') {
    cerr << "exp is negative\n";
    exit(EXIT_FAILURE);
  }

  while (b_cmp(ex, zero) > 0) {
    if ((ex & 1) == 1)
      product = (product * y) % mod;

    y = (y * y) % mod;
    ex = ex >> 1;
  }

  ex.b_clear();
  y.b_clear();

  return product;
}

// BigNum and unsigned long modular exponentiation
BigNum b_powm( const BigNum &base,
	       const unsigned long exp,
	       const BigNum &mod )
{
  BigNum product = "1";
  BigNum y = base;
  unsigned long int ex = exp;

  while (ex > 0) {
    if (ex & 1 == 1)
      product = (product * y) % mod;

    y = (y * y) % mod;
    ex = ex >> 1;
  }

  y.b_clear();

  return product;
}

// BigNum absolute value
BigNum b_abs( const BigNum &x )
{
  BigNum bn = x;
  bn.d_sign = '+';

  return bn;
}

// BigNum absolute value (implementation 2)
BigNum b_abs2( const BigNum &x )
{
  BigNum bn = x;
  bn.d_sign = '+';

  return bn;
}

// BigNum sign reversal
BigNum b_neg( const BigNum &x )
{
  BigNum bn = x;

  if (bn.d_sign == '+')
    bn.d_sign = '-';
  else
    bn.d_sign = '+';

  return bn;
}

// BigNum stream operator
std::ostream& operator<<( std::ostream &os, const BigNum &bn )
{
  unsigned long int * ptr;
  unsigned long int i = 1;

  if (bn.d_v.size() == 0)
    return os;

  ptr = bn.V() + bn.Size() - 1;

  os.setf(ios::uppercase);
  os << hex << *ptr--;

  while (i < bn.d_size) {
    i++;

    if (NUMBITS == 32)
      os << setw(8) << setfill('0') << hex << *ptr--;
    else
      os << setw(16) << setfill('0') << hex << *ptr--;
  }

  os << endl;
  //  ptr = 0;

  return os;
}

// BigNum equality operator
bool operator==( const BigNum &x, const BigNum &y )
{
  if (x.GetTotalBits() != y.GetTotalBits() || x.d_sign != y.d_sign)
    return false;

  return memcmp(x.V(), 
		y.V(), 
		sizeof(unsigned long int) * x.d_size) == 0;
}

// BigNum and unsigned long equality operator
bool operator==( const BigNum &x, const unsigned long y )
{
  return (x.d_size == 1 && x.d_v[0] == y && x.d_sign == '+');
}

// BigNum comparison function
int b_cmp( const BigNum &x, const BigNum &y )
{
  unsigned long int * xptr, * yptr;  
  xptr = x.V() + x.d_size - 1;
  yptr = y.V() + y.d_size - 1;

  if (x == y)
    return 0;
  else if (x.d_sign == '+' && y.d_sign == '-')
    return 1;
  else if (x.d_sign == '-' && y.d_sign == '+')
    return -1; 
  else if (x.d_sign == y.d_sign) {
    if (x.d_size > y.d_size) {
      if (x.d_sign == '+')
        return 1;
      else
        return -1;
    }
    else if (x.d_size < y.d_size) {
      if (x.d_sign == '+')
        return -1;
      else
        return 1;
    }
    
    for (unsigned long int i = 0; i < x.d_size; i++) {
      if (*xptr > *yptr) {
        if (x.d_sign == '+')
          return 1;
        else
          return -1;
      }      
      else if (*xptr < *yptr) {
        if (x.d_sign == '+')
          return -1;
        else
          return 1; 
      }

      *xptr--;
      *yptr--;
    }
  }

  //  xptr = 0;
  //  yptr = 0;  

  return 0; 
}

// BigNum and unsigned long comparison function
int b_cmp( const BigNum &x, const unsigned long )
{
  unsigned long int x_ui = x.b_get_ui();
  BigNum bn;
  bn = Set_ui(y);
  int result;
  
  if (x == bn)
    result = 0;
  else {
    if (x.d_size > 1) {
      if (x.d_sign == '+')
	result = 1;
      else
	result = -1;
    }
    else { /* size == 1 */
      if (x_ui > y) {
	if (x.d_sign == '+')
	  result = 1;
	else
	  result = -1;
      }
      else {
	if (x.d_sign == '-')
	  result = -1;
	else
	  result = 1;
      }
    }
  }

  bn.b_clear();

  return result;
}

// BigNum and signed long comparison function
int b_cmp( const BigNum &x, const signed long )
{
  int result;
  unsigned long int x_ui;
  BigNum bn;
  bn = Set_si(y);
  
  if (x == bn)
    result = 0;
  else {
    if (x.d_size > 1) {
      if (x.d_sign == '+')
	result = 1;
      else  
	result = -1;
    }
    else {
      x_ui = x.b_get_ui();
      
      if (x_ui > 0)
	result = 1;
      else
	result = -1;
    }
  }

  bn.b_clear();

  return result;
}

// BigNum size comparison function (returns smaller size)
unsigned long SmallerSize( const BigNum &x, const BigNum &y )
{
  if (x.Size() < y.Size())
    return x.Size();
  
  return y.Size();
}

// BigNum size comparison function (returns larger size)
unsigned long BiggerSize( const BigNum &x, const BigNum &y )
{
  if (x.Size() > y.Size())
    return x.Size();
  
  return y.Size();
}

// Test bit value
int Test( const unsigned long num, int index )
{
  return 0 != (num & (static_cast<unsigned long int>(1) << static_cast<unsigned long int>(index)));
}

// Set bit value
unsigned long int Set( const unsigned long int num, int index )
{
  return (num | (static_cast<unsigned long int>(1) << static_cast<unsigned long int>(index)));
}
  
// Unset bit value
unsigned long int Unset( const unsigned long int num, int index )
{
  return (num & ~(static_cast<unsigned long int>(1) << static_cast<unsigned long int>(index)));
}

// Return the cieling of division of two unsigned long variables
unsigned long int CeilDiv( unsigned long int x, unsigned long int y )
{
  if (x % y > 0)
    return x / y + 1;

  return x / y;
}

// Return number of bits used by variable (returns 0 if x = 0)
int GetNumBits( unsigned long x )
{
  if (x == 0)
    return 0;

  int bits = NUMBITS - 1;

  for (int i = bits; i > 0; i--)
    if (Test(x, i) == 1)
      return i + 1;

  return 1;
}
  
// Convert a character to an integer
int C2I( char c ) 
{
  if (c < 65)
    return c - '0';
  else
    return toupper(c) - 55;  
} 

} // end namespace sprng

#endif // end BIG_NUM_DEF_HPP

//---------------------------------------------------------------------------//
// end BigNum_def.hpp
//---------------------------------------------------------------------------//

