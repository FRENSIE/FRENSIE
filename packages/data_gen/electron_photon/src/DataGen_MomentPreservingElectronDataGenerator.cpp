//---------------------------------------------------------------------------//
//!
//! \file   DataGen_MomentPreservingElectronDataGenerator.cpp
//! \author Luke Kersting
//! \brief  The moment preserving electron scattering data generator base class def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "DataGen_MomentPreservingElectronDataGenerator.hpp"
#include "Utility_DesignByContract.hpp"

namespace DataGen{

// Constructor
MomentPreservingElectronDataGenerator::MomentPreservingElectronDataGenerator(
                                                const unsigned atomic_number )
  : d_atomic_number( atomic_number )
{
  // Make sure the atomic number is valid
  testPrecondition( atomic_number <= 100u );
}

// Set the atomic number
void MomentPreservingElectronDataGenerator::setAtomicNumber(
               Data::MomentPreservingElectronVolatileDataContainer&
               data_container ) const
{
  data_container.setAtomicNumber( d_atomic_number );
}

// Get the atomic number
unsigned MomentPreservingElectronDataGenerator::getAtomicNumber() const
{
  return d_atomic_number;
}


} // end DataGen

//---------------------------------------------------------------------------//
// end DataGen_MomentPreservingElectronDataGenerator.cpp
//---------------------------------------------------------------------------//
