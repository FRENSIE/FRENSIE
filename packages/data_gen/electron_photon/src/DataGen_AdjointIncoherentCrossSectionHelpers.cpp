//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointIncoherentCrossSectionHelpers.cpp
//! \author Alex Robinson
//! \brief  The adjoint incoherent cross section helper function definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "DataGen_AdjointIncoherentCrossSectionHelpers.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_DesignByContract.hpp"

namespace DataGen{

// Return the energy of the max cross section value
double getEnergyOfMaxCrossSection( const double max_energy )
{
  // Make sure the max energy is valid
  testPrecondition( !Utility::QuantityTraits<double>::isnaninf( max_energy ) );
  testPrecondition( max_energy > 0.0 );

  return max_energy/(1.0 + 2.0*max_energy/Utility::PhysicalConstants::electron_rest_mass_energy);
}

// Check if the energy corresponds to the max cross section value at any max
// energy
double doesEnergyCorrespondToAMaxCrossSectionValue( const double energy )
{
  return energy < Utility::PhysicalConstants::electron_rest_mass_energy/2.0;
}

// Return the max energy that results in a max cross section value at energy
double getMaxEnergyResultingInMaxCrossSectionValueAtEnergy(
						          const double energy )
{
  // Make sure the energy is valid
  testPrecondition( !Utility::QuantityTraits<double>::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );
  testPrecondition( energy <
		    Utility::PhysicalConstants::electron_rest_mass_energy/2.0);

  return energy/(1.0 - 2.0*energy/Utility::PhysicalConstants::electron_rest_mass_energy);
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_AdjointIncoherentCrossSectionHelpers.cpp
//---------------------------------------------------------------------------//
