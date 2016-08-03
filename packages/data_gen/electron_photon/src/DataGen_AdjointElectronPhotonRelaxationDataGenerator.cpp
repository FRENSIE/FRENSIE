//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointElectronPhotonRelaxationDataGenerator.cpp
//! \author Luke Kersting
//! \brief  The adjoint electron-photon-relaxation data generator base class decl.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "DataGen_AdjointElectronPhotonRelaxationDataGenerator.hpp"
#include "Utility_ContractException.hpp"

namespace DataGen{

// Constructor
AdjointElectronPhotonRelaxationDataGenerator::AdjointElectronPhotonRelaxationDataGenerator(
						 const unsigned atomic_number )
  : d_atomic_number( atomic_number )
{
  // Make sure the atomic number is valid
  testPrecondition( atomic_number <= 100u );
}

// Set the atomic number
void AdjointElectronPhotonRelaxationDataGenerator::setAtomicNumber(
			   Data::AdjointElectronPhotonRelaxationVolatileDataContainer&
			   data_container ) const
{
  data_container.setAtomicNumber( d_atomic_number );
}

// Get the atomic number
unsigned AdjointElectronPhotonRelaxationDataGenerator::getAtomicNumber() const
{
  return d_atomic_number;
}


} // end DataGen

//---------------------------------------------------------------------------//
// end DataGen_AdjointElectronPhotonRelaxationDataGenerator.cpp
//---------------------------------------------------------------------------//
