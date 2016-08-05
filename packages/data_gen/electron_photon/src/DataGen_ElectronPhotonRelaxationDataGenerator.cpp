//---------------------------------------------------------------------------//
//!
//! \file   DataGen_ElectronPhotonRelaxationDataGenerator.cpp
//! \author Alex Robinson
//! \brief  The electron-photon-relaxation data generator base class decl.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "DataGen_ElectronPhotonRelaxationDataGenerator.hpp"
#include "Utility_ContractException.hpp"

namespace DataGen{

// Constructor
ElectronPhotonRelaxationDataGenerator::ElectronPhotonRelaxationDataGenerator(
						 const unsigned atomic_number )
  : d_atomic_number( atomic_number )
{
  // Make sure the atomic number is valid
  testPrecondition( atomic_number <= 100u );
}

// Set the atomic number
void ElectronPhotonRelaxationDataGenerator::setAtomicNumber(
			   Data::ElectronPhotonRelaxationVolatileDataContainer&
			   data_container ) const
{
  data_container.setAtomicNumber( d_atomic_number );
}

// Get the atomic number
unsigned ElectronPhotonRelaxationDataGenerator::getAtomicNumber() const
{
  return d_atomic_number;
}


} // end DataGen

//---------------------------------------------------------------------------//
// end DataGen_ElectronPhotonRelaxationDataGenerator.cpp
//---------------------------------------------------------------------------//
