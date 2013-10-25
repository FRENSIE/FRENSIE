//---------------------------------------------------------------------------//
//!
//! \file    BigNum.hpp
//! \author  J. Ren (Florida State University, ren@csit.fsu.edu)
//! \brief   BigNum class declaration
//! \details This file originally appeared in the sprng4 library. It has been
//!          modified by Alex Robinson (aprobinson@wisc.edu) to better support
//!          the needs of FACEMC.
//!
//---------------------------------------------------------------------------//

#ifndef BIG_NUM_HPP
#define BIG_NUM_HPP

// Std Lib Includes
#include <iostream>
#include <vector>

// SPRNG Includes
#include "BigNumHelpers.hpp"

namespace sprng{

//! Class for handling big numbers
class BigNum
{
  
public:
  
  //! Default constructor
  BigNum()

  //! Constructor by size
  BigNum( unsigned long s );

  //! Implicit conversion from char* to BigNum
  BigNum( char* c, char s = '+' );

  //! Copy constructor
  BigNum( const BigNum &bn )

  //! Assignment operator
  BigNum& operator=( const Bignum &bn );
  
  //! Destructor
  ~BigNum()
  { /* ... */ }

  //! Get the unsigned long
  unsigned long b_get_ui() const;

  //! Get the size of the unsigned long array
  unsigned long Size() const;

  //! Get the head of the unsigned long array
  unsigned long* V() const;
  
  //! Get the sign of the BigNum
  char Sign() const;

  //! Erase the leading bits of the BigNum
  BigNum EraseLeadingBits( unsigned long numbits );

  //! Get the total number of bits in the BigNum
  unsigned long GetTotalBits() const;

  //! Free the unsigned long array
  void b_clear() const;

  //! Print the BigNum with its sign
  void b_print_w_sign() const;

  //! Set BigNum as an unsigned long 
  friend BigNum Set_ui( unsigned long n );

  //! Set BigNum as a signed long
  friend BigNum Set_si( signed long n );

  //! BigNum addition operator
  friend BigNum operator+( const BigNum &x, const BigNum &y );

  //! BigNum and unsigned long addition operator
  friend BigNum operator+( const BignNum &x, const unsigned long y );

  //! BigNum subtraction operator
  friend BigNum operator-( const BigNum &x, const BigNum &y );

  //! BigNum and unsigned long subtraction operator
  friend BigNum operator-( const BigNum &x, const unsigned long y );

  //! BigNum multiplication operator
  friend BigNum operator*( const BigNum &x, const BigNum &y );

  //! BigNum and unsigned long multiplication operator
  friend BigNum operator*( const BigNum &x, const unsigned long y );

  //! BigNum division substitute function
  friend BigNum Sub4Div( const BigNum &x, const BigNum &y );

  //! BigNum division operator
  friend BigNum operator/( const BigNum &x, const BigNum &y );
  
  //! BigNum and unsigned long division operator
  friend BigNum operator/( const BigNum &x, const unsigned long y );

  //! BigNum modulo operator
  friend BigNum operator%( const BigNum &x, const BigNum &y );
  
  //! BigNum and unsigned long modulo operator
  friend BigNum operator%( const BigNum &x, const unsigned long y );

  //! BigNum bitwise exclusive or operator
  friend BigNum operator^( const BigNum &x, const BigNum &y );

  //! BigNum and unsigned long bitwise exclusive or operator
  friend BigNum operator^( const BigNum &x, const unsigned long y );

  //! BigNum and unsigned long bitwise and operator
  friend unsigned long operator&( const BigNum &x, const unsigned long y );

  //! BigNum and unsigned long right bitshift operator
  friend BigNum operator>>( const BigNum &x, const unsigned long y );

  //! BigNum and unsigned long left bitshift operator
  friend BigNum operator<<( const BigNum &x, const unsigned long y );

  //! BigNum divided by 2^(ex_of_2)
  friend BigNum b_div_2exp( const BigNum &x, const unsigned long ex_of_2 );

  //! BigNum exponentiation
  friend BigNum b_pow( const BigNum &base, const unsigned long exp );

  //! BigNum modular exponentiation
  friend BigNum b_powm( const BigNum &base, 
			const BigNum &exp, 
			const BigNum &mod );

  //! BigNum and unsigned long modular exponentiation
  friend BigNum b_powm( const BigNum &base,
			const unsigned long exp,
			const BigNum &mod );

  //! BigNum absolute value
  friend BigNum b_abs( const BigNum &x );

  //! BigNum absolute value (implementation 2)
  friend BigNum b_abs2( const BigNum &x );

  //! BigNum sign reversal
  friend BigNum b_neg( const BigNum &x );

  //! BigNum stream operator
  friend std::ostream& operator<<( std::ostream &os, const BigNum &bn );

  //! BigNum equality operator
  friend bool operator==( const BigNum &x, const BigNum &y );

  //! BigNum and unsigned long equality operator
  friend bool operator==( const BigNum &x, const unsigned long y );

  //! BigNum comparison function
  friend int b_cmp( const BigNum &x, const BigNum &y );

  //! BigNum and unsigned long comparison function
  friend int b_cmp( const BigNum &x, const unsigned long );

  //! BigNum and signed long comparison function
  friend int b_cmp( const BigNum &x, const signed long );

  //! BigNum size comparison function (returns smaller size)
  friend unsigned long SmallerSize( const BigNum &x, const BigNum &y );

  //! BigNum size comparison function (returns larger size)
  friend unsigned long BiggerSize( const BigNum &x, const BigNum &y );

  //! Test bit value
  friend int Test( const unsigned long num, int index );

  //! Set bit value
  friend unsigned long int Set( const unsigned long int num, int index );
  
  //! Unset bit value
  friend unsigned long int Unset( const unsigned long int num, int index );

  //! Return the cieling of division of two unsigned long variables
  friend unsigned long int CeilDiv( unsigned long int x, unsigned long int y );

  //! Return number of bits used by variable (returns 0 if x = 0)
  friend int GetNumBits( unsigned long x );
  
  //! Convert a character to an integer
  friend int C2I( char c );  

private:
  
  // Unsigned long array
  std::vector<unsigned long> d_v;

  // Size of the unsigned long array
  unsigned long int d_size;

  // Sign bit
  char d_sign;
};

//! Set BigNum as a signed long
BigNum Set_si( signed long n );

//! BigNum addition operator
BigNum operator+( const BigNum &x, const BigNum &y );

//! BigNum and unsigned long addition operator
BigNum operator+( const BignNum &x, const unsigned long y );

//! BigNum subtraction operator
BigNum operator-( const BigNum &x, const BigNum &y );

//! BigNum and unsigned long subtraction operator
BigNum operator-( const BigNum &x, const unsigned long y );

//! BigNum multiplication operator
BigNum operator*( const BigNum &x, const BigNum &y );

//! BigNum and unsigned long multiplication operator
BigNum operator*( const BigNum &x, const unsigned long y );

//! BigNum division substitute function
BigNum Sub4Div( const BigNum &x, const BigNum &y );

//! BigNum division operator
BigNum operator/( const BigNum &x, const BigNum &y );
  
//! BigNum and unsigned long division operator
BigNum operator/( const BigNum &x, const unsigned long y );

//! BigNum modulo operator
BigNum operator%( const BigNum &x, const BigNum &y );
  
//! BigNum and unsigned long modulo operator
BigNum operator%( const BigNum &x, const unsigned long y );

//! BigNum bitwise exclusive or operator
BigNum operator^( const BigNum &x, const BigNum &y );

//! BigNum and unsigned long bitwise exclusive or operator
BigNum operator^( const BigNum &x, const unsigned long y );

//! BigNum and unsigned long bitwise and operator
unsigned long operator&( const BigNum &x, const unsigned long y );

//! BigNum and unsigned long right bitshift operator
BigNum operator>>( const BigNum &x, const unsigned long y );

//! BigNum and unsigned long left bitshift operator
BigNum operator<<( const BigNum &x, const unsigned long y );

//! BigNum divided by 2^(ex_of_2)
BigNum b_div_2exp( const BigNum &x, const unsigned long ex_of_2 );

//! BigNum exponentiation
BigNum b_pow( const BigNum &base, const unsigned long exp );

//! BigNum modular exponentiation
BigNum b_powm( const BigNum &base, 
			const BigNum &exp, 
			const BigNum &mod );

//! BigNum and unsigned long modular exponentiation
BigNum b_powm( const BigNum &base,
			const unsigned long exp,
			const BigNum &mod );

//! BigNum absolute value
BigNum b_abs( const BigNum &x );

//! BigNum absolute value (implementation 2)
BigNum b_abs2( const BigNum &x );

//! BigNum sign reversal
BigNum b_neg( const BigNum &x );

//! BigNum stream operator
std::ostream& operator<<( std::ostream &os, const BigNum &bn );

//! BigNum equality operator
bool operator==( const BigNum &x, const BigNum &y );

//! BigNum and unsigned long equality operator
bool operator==( const BigNum &x, const unsigned long y );

//! BigNum comparison function
int b_cmp( const BigNum &x, const BigNum &y );

//! BigNum and unsigned long comparison function
int b_cmp( const BigNum &x, const unsigned long );

//! BigNum and signed long comparison function
int b_cmp( const BigNum &x, const signed long );

//! BigNum size comparison function (returns smaller size)
unsigned long SmallerSize( const BigNum &x, const BigNum &y );

//! BigNum size comparison function (returns larger size)
unsigned long BiggerSize( const BigNum &x, const BigNum &y );

//! Test bit value
int Test( const unsigned long num, int index );

//! Set bit value
unsigned long int Set( const unsigned long int num, int index );
  
//! Unset bit value
unsigned long int Unset( const unsigned long int num, int index );

//! Return the cieling of division of two unsigned long variables
unsigned long int CeilDiv( unsigned long int x, unsigned long int y );

//! Return number of bits used by variable (returns 0 if x = 0)
int GetNumBits( unsigned long x );
  
//! Convert a character to an integer
int C2I( char c );  

} // end namespace sprng

//---------------------------------------------------------------------------//
// Definition includes.
//---------------------------------------------------------------------------//

#include "BigNum_def.hpp"

//---------------------------------------------------------------------------//

#endif // end BIG_NUM_HPP

//---------------------------------------------------------------------------//
// end BigNum.hpp
//---------------------------------------------------------------------------//
