//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointElectronGridGenerator.cpp
//! \author Luke Kersting
//! \brief  Adjoint electron grid generator definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "DataGen_AdjointElectronGridGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace DataGen{

// Initialize the static member data
double AdjointElectronGridGenerator::s_min_table_energy = 0.00001;
double AdjointElectronGridGenerator::s_max_table_energy = 20;

//! Set the min table energy (default is 0.00001 MeV)
void AdjointElectronGridGenerator::setMinTableEnergy( 
						      const double min_energy )
{
  // Make sure the min energy is valid
  testPrecondition( min_energy > 0.0 );
  testPrecondition( min_energy < s_max_table_energy );

  s_min_table_energy = min_energy;
}

// Get the min table energy
double AdjointElectronGridGenerator::getMinTableEnergy()
{
  return s_min_table_energy;
}

// Set the max table energy (default is 20.0 MeV)
void AdjointElectronGridGenerator::setMaxTableEnergy( 
						      const double max_energy )
{
  // Make sure the max energy is valid
  testPrecondition( max_energy > 0.0 );
  testPrecondition( max_energy > s_min_table_energy );

  s_max_table_energy = max_energy;
}

// Get the max table energy
double AdjointElectronGridGenerator::getMaxTableEnergy()
{
  return s_max_table_energy;
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_AdjointElectronGridGenerator.cpp
//---------------------------------------------------------------------------//
