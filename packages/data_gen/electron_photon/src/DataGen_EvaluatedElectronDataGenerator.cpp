//---------------------------------------------------------------------------//
//!
//! \file   DataGen_EvaluatedElectronDataGenerator.cpp
//! \author Luke Kersting
//! \brief  The soft elastic electron scattering data generator base class def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "DataGen_EvaluatedElectronDataGenerator.hpp"
#include "Utility_ContractException.hpp"

namespace DataGen{

// Constructor
EvaluatedElectronDataGenerator::EvaluatedElectronDataGenerator(
						 const unsigned atomic_number )
  : d_atomic_number( atomic_number )
{
  // Make sure the atomic number is valid
  testPrecondition( atomic_number <= 100u );
}

// Set the atomic number
void EvaluatedElectronDataGenerator::setAtomicNumber( 
			   Data::EvaluatedElectronVolatileDataContainer&
			   data_container ) const
{
  data_container.setAtomicNumber( d_atomic_number ); 
}

// Get the atomic number
unsigned EvaluatedElectronDataGenerator::getAtomicNumber() const
{
  return d_atomic_number;
}
			    

} // end DataGen

//---------------------------------------------------------------------------//
// end DataGen_EvaluatedElectronDataGenerator.cpp
//---------------------------------------------------------------------------//
