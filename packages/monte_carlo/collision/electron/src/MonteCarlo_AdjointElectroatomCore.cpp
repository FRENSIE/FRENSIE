//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectroatomCore.cpp
//! \author Luke Kersting
//! \brief  The adjoint electroatom core class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatomCore.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Default constructor
AdjointElectroatomCore::AdjointElectroatomCore()
  : BaseType()
{ /* ... */ }

// Copy constructor
AdjointElectroatomCore::AdjointElectroatomCore(
                                       const AdjointElectroatomCore& instance )
  : BaseType( instance )
{ /* ... */ }

// Assignment operator
AdjointElectroatomCore& AdjointElectroatomCore::operator=(
                                       const AdjointElectroatomCore& instance )
{
  // Avoid self-assignment
  if( this != &instance )
    BaseType::operator=( instance );

  return *this;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectroatomCore.cpp
//---------------------------------------------------------------------------//

