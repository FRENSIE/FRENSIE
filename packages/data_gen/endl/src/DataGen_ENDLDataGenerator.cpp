//---------------------------------------------------------------------------//
//!
//! \file   DataGen_ENDLDataGenerator.cpp
//! \author Alex Robinson
//! \brief  The electron-photon-relaxation data generator base class decl.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "DataGen_ENDLDataGenerator.hpp"
#include "Utility_DesignByContract.hpp"

namespace DataGen{

// Constructor
ENDLDataGenerator::ENDLDataGenerator( const unsigned atomic_number )
  : d_atomic_number( atomic_number )
{
  // Make sure the atomic number is valid
  testPrecondition( atomic_number <= 100u );
}

// Set the atomic number
void ENDLDataGenerator::setAtomicNumber(
        Data::ENDLVolatileDataContainer& data_container ) const
{
  data_container.setAtomicNumber( d_atomic_number );
}

// Get the atomic number
unsigned ENDLDataGenerator::getAtomicNumber() const
{
  return d_atomic_number;
}


} // end DataGen

//---------------------------------------------------------------------------//
// end DataGen_ENDLDataGenerator.cpp
//---------------------------------------------------------------------------//
