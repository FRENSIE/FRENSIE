//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointIncoherentGridGenerator.cpp
//! \author Alex Robinson
//! \brief  Adjoint incoherent grid generator definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <deque>

// Boost Includes
#include <boost/bind.hpp>

// FRENSIE Includes
#include "DataGen_AdjointIncoherentGridGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_SortAlgorithms.hpp"


namespace DataGen{

// Initialize the static member data
double AdjointIncoherentGridGenerator::s_min_table_energy = 0.0001;
double AdjointIncoherentGridGenerator::s_max_table_energy = 20;
double AdjointIncoherentGridGenerator::s_max_table_energy_nudge_factor = 0.01;
double AdjointIncoherentGridGenerator::s_nudged_max_table_energy = 
  s_max_table_energy*(1.0+s_max_table_energy_nudge_factor);

//! Set the min table energy (default is 0.0001 MeV)
void AdjointIncoherentGridGenerator::setMinTableEnergy( 
						      const double min_energy )
{
  // Make sure the min energy is valid
  testPrecondition( min_energy > 0.0 );
  testPrecondition( min_energy < s_max_table_energy );

  s_min_table_energy = min_energy;
}

// Get the min table energy
double AdjointIncoherentGridGenerator::getMinTableEnergy()
{
  return s_min_table_energy;
}

// Set the max table energy (default is 20.0 MeV)
void AdjointIncoherentGridGenerator::setMaxTableEnergy( 
						      const double max_energy )
{
  // Make sure the max energy is valid
  testPrecondition( max_energy > 0.0 );
  testPrecondition( max_energy > s_min_table_energy );

  s_max_table_energy = max_energy;
  s_nudged_max_table_energy = 
    s_max_table_energy*(1.0+s_max_table_energy_nudge_factor);
}

// Get the max table energy
double AdjointIncoherentGridGenerator::getMaxTableEnergy()
{
  return s_max_table_energy;
}

// Constructor
AdjointIncoherentGridGenerator::AdjointIncoherentGridGenerator(
     const Teuchos::RCP<const Utility::OneDDistribution>& scattering_function )
  : d_adjoint_incoherent_cross_section( scattering_function )
{
  // Make sure the scattering function is valid
  testPrecondition( !scattering_function.is_null() );
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_AdjointIncoherentGridGenerator.cpp
//---------------------------------------------------------------------------//
