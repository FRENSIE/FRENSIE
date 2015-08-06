//---------------------------------------------------------------------------//
//!
//! \file   DataGen_SoftElasticElectronDataGenerator.cpp
//! \author Luke Kersting
//! \brief  The soft elastic electron scattering data generator base class def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "DataGen_SoftElasticElectronDataGenerator.hpp"
#include "Utility_ContractException.hpp"

namespace DataGen{

// Constructor
SoftElasticElectronDataGenerator::SoftElasticElectronDataGenerator(
						 const unsigned atomic_number )
  : d_atomic_number( atomic_number )
{
  // Make sure the atomic number is valid
  testPrecondition( atomic_number <= 100u );
}

// Set the atomic number
void SoftElasticElectronDataGenerator::setAtomicNumber( 
			   Data::SoftElasticElectronVolatileDataContainer&
			   data_container ) const
{
  data_container.setAtomicNumber( d_atomic_number ); 
}

// Get the atomic number
unsigned SoftElasticElectronDataGenerator::getAtomicNumber() const
{
  return d_atomic_number;
}
			    

} // end DataGen

//---------------------------------------------------------------------------//
// end DataGen_SoftElasticElectronDataGenerator.cpp
//---------------------------------------------------------------------------//
