//---------------------------------------------------------------------------//
//!
//! \file    BigRat.hpp
//! \author  J. Ren (Florida State University, ren@csit.fsu.edu)
//! \brief   BigRat class declaration
//! \details This file originally appeared in the sprng4 library. It has been
//!          modified by Alex Robinson (aprobinson@wisc.edu) to better support
//!          the needs of FACEMC.
//!
//---------------------------------------------------------------------------//

#ifndef BIG_RAT_HPP
#define BIG_RAT_HPP

// SPRNG Includes
#include "BigNum.hpp"

namespace sprng{

//! Class for handling arighmetic on large rationals
class BigRat
{

public:

  //! Default constructor
  BigRat();

  //! Get the numerator
  BigNum br_get_num() const;

  //! Get the denominator
  BigNum br_get_den() const;

  //! Set the numerator
  void br_set_num( const BigNum &num );

  //! Set the denominator
  void br_set_den( const BigNum &den );

private:
  
  // Numerator of ratio
  BigNum d_numerator;

  // Denominator of ratio
  BigNum d_denominator;
};

} // end namespace sprng

//---------------------------------------------------------------------------//
// Definition includes.
//---------------------------------------------------------------------------//

#include "BigRat_def.hpp"

//---------------------------------------------------------------------------//

#endif // end BIG_RAT_HPP

//---------------------------------------------------------------------------//
// end BigRat.hpp
//---------------------------------------------------------------------------//
