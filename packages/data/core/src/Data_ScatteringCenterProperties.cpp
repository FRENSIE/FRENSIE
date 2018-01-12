//---------------------------------------------------------------------------//
//!
//! \file   Data_ScatteringCenterProperties.cpp
//! \author Alex Robinson
//! \brief  The scattering center properties class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_ScatteringCenterProperties.hpp"
#include "Utility_PhysicalConstants.hpp"

namespace Data{

// Default constructor
ScatteringCenterProperties::ScatteringCenterProperties()
{ /* ... */ }

// Get the atomic weight ratio (atomic weight/neutron weight)
double ScatteringCenterProperties::atomicWeightRatio() const
{
  return this->atomicWeight()/Utility::PhysicalConstants::neutron_rest_mass_amu;
}

// Get the nuclear data properties (closest to evaluation temp)
const NuclearDataProperties* ScatteringCenterProperties::getNuclearDataProperties(
                                    const double evaluation_temp_in_mev ) const
{
  return this->getNuclearDataProperties( evaluation_temp_in_mev, false );
}

// Get the thermal nuclear data properties
const ThermalNuclearDataProperties* ScatteringCenterProperties::getThermalNuclearDataProperties(
                                   c onst double evaluation_temp_in_mev ) const
{
  return this->getThermalNuclearDataProperties( evaluation_temp_in_mev, false );
}

// Get the adjoint nuclear data
const AdjointNuclearDataProperties* ScatteringCenterProperties::getAdjointNuclearDataProperties(
                                    const double evaluation_temp_in_mev ) const
{
  return this->getAdjointNuclearDataProperties( evaluation_temp_in_mev, false );
}

// Get the adjoint thermal nuclear data
const AdjointThermalNuclearDataProperties* ScatteringCenterProperties::getAdjointThermalNuclearDataProperties(
                                    const double evaluation_temp_in_mev ) const
{
  return this->getAdjointThermalNuclearDataProperties( evaluation_temp_in_mev, false );
}

// Deep clone the properties
ScatteringCenterProperties* ScatteringCenterProperties::deepClone() const
{
  return this->clone();
}
  
} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_ScatteringCenterProperties.cpp
//---------------------------------------------------------------------------//
