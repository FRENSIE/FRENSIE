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

// Deep clone the properties
ScatteringCenterProperties* ScatteringCenterProperties::deepClone() const
{
  return this->clone();
}
  
} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_ScatteringCenterProperties.cpp
//---------------------------------------------------------------------------//
