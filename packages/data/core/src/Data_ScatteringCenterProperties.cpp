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
  return this->atomicWeight()/Utility::PhysicalConstants::neutron_rest_mass_amu_q;
}

// Get the nuclear data evaluation temps
auto ScatteringCenterProperties::getNuclearDataEvaluationTemps() const -> std::vector<Temperature>
{
  std::vector<Energy> energies = this->getNuclearDataEvaluationTempsInMeV();
  std::vector<Temperature> temps( energies.size() );

  for( size_t i = 0; i < energies.size(); ++i )
    temps[i] = energies[i]/Utility::PhysicalConstants::boltzmann_constant_q;
}

// Get the nuclear data properties (closest to evaluation temp)
const NuclearDataProperties* ScatteringCenterProperties::getNuclearDataProperties(
                                           const Energy evaluation_temp ) const
{
  return this->getNuclearDataProperties( evaluation_temp, false );
}

//Get the thermal nuclear data evaluation temps
auto ScatteringCenterProperties::getThermalNuclearDataEvaluationTemps() const -> std::vector<Temperature>
{
  std::vector<Energy> energies = this->getThermalNuclearDataEvaluationTempsInMeV();
  std::vector<Temperature> temps( energies.size() );

  for( size_t i = 0; i < energies.size(); ++i )
    temps[i] = energies[i]/Utility::PhysicalConstants::boltzmann_constant_q;
}

// Get the thermal nuclear data properties
const ThermalNuclearDataProperties* ScatteringCenterProperties::getThermalNuclearDataProperties(
                                           const Energy evaluation_temp ) const
{
  return this->getThermalNuclearDataProperties( evaluation_temp, false );
}

// Get the adjoint nuclear data evaluation temps
auto ScatteringCenterProperties::getAdjointNuclearDataEvaluationTemps() const -> std::vector<Temperature>
{
  std::vector<Energy> energies = this->getAdjointNuclearDataEvaluationTempsInMeV();
  std::vector<Temperature> temps( energies.size() );

  for( size_t i = 0; i < energies.size(); ++i )
    temps[i] = energies[i]/Utility::PhysicalConstants::boltzmann_constant_q;
}

// Get the adjoint nuclear data
const AdjointNuclearDataProperties* ScatteringCenterProperties::getAdjointNuclearDataProperties(
                                           const Energy evaluation_temp ) const
{
  return this->getAdjointNuclearDataProperties( evaluation_temp, false );
}

// Get the adjoint thermal nuclear data evaluation temps
auto ScatteringCenterProperties::getAdjointThermalNuclearDataEvaluationTemps() const -> std::vector<Temperature>
{
  std::vector<Energy> energies = this->getAdjointThermalNuclearDataEvaluationTempsInMeV();
  std::vector<Temperature> temps( energies.size() );

  for( size_t i = 0; i < energies.size(); ++i )
    temps[i] = energies[i]/Utility::PhysicalConstants::boltzmann_constant_q;
}

// Get the adjoint thermal nuclear data
const AdjointThermalNuclearDataProperties* ScatteringCenterProperties::getAdjointThermalNuclearDataProperties(
                                           const Energy evaluation_temp ) const
{
  return this->getAdjointThermalNuclearDataProperties( evaluation_temp, false );
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
