//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointPhotoatomCore.cpp
//! \author Alex Robinson
//! \brief  The adjoint photoatom core class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <algorithm>

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotoatomCore.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Default constructor
AdjointPhotoatomCore::AdjointPhotoatomCore()
  : BaseType()
{ /* ... */ }

// Copy constructor
AdjointPhotoatomCore::AdjointPhotoatomCore(
                                         const AdjointPhotoatomCore& instance )
  : BaseType( instance )
{ /* ... */ }

// Assignment operator
AdjointPhotoatomCore& AdjointPhotoatomCore::operator=(
                                         const AdjointPhotoatomCore& instance )
{
  // Avoid self-assignment
  if( this != &instance )
    BaseType::operator=( instance );

  return *this;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotoatomCore.cpp
//---------------------------------------------------------------------------//
