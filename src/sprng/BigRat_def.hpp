//---------------------------------------------------------------------------//
//!
//! \file    BigRat_def.hpp
//! \author  J. Ren (Florida State University, ren@csit.fsu.edu)
//! \brief   Implementation file for arithmetic on large rationals
//! \details This file originally appeared in the sprng4 library. It has been
//!          modified by Alex Robinson (aprobinson@wisc.edu) to better support
//!          the needs of FACEMC.
//!
//---------------------------------------------------------------------------//

#ifndef BIG_RAT_DEF_HPP
#define BIG_RAT_DEF_HPP

namespace sprng{

// Default constructor
BigRat::BigRat()
  : d_numerator( "0" ),
    d_denominator( "1" )
{ /* ... */ }
  
// Get the numerator
BigNum BigRat::br_get_num() const
{
  return d_numerator;
}

// Get the denominator
BigNum BigRat::br_get_den() const
{
  return d_denominator;
}

// Set the numerator
void BigRat::br_set_num( const BigNum &num )
{
  d_numerator = num;
}

// Set the denominator
void BigRat::br_set_den( const BigNum &den )
{
  d_denominator = den;
}

} // end namespace sprng

#endif // end BIG_RAT_DEF_HPP

//---------------------------------------------------------------------------//
// end BigRat_def.hpp
//---------------------------------------------------------------------------//
