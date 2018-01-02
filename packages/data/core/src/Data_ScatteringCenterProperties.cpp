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

// Get the atomic weight ratio(s) (atomic weight/neutron weight)
std::vector<double> ScatteringCenterProperties::atomicWeightRatios() const
{
  std::vector<double> atomic_weight_ratios = this->atomicWeights();
  
  for( size_t i = 0; i < atomic_weight_ratios.size(); ++i )
  {
    atomic_weight_ratios[i] /=
      Utility::PhysicalConstants::neutron_rest_mass_amu;
  }
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
