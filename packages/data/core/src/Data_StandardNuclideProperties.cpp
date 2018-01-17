//---------------------------------------------------------------------------//
//!
//! \file   Data_StandardNuclideProperties.cpp
//! \author Alex Robinson
//! \brief  The standard nuclide properties class definition
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>

// FRENSIE Includes
#include "Data_StandardNuclideProperties.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace Data{

// Default constructor
StandardNuclideProperties::StandardNuclideProperties()
{ /* ... */ }

// Constructor
StandardNuclideProperties::StandardNuclideProperties(
                                             const std::string& name,
                                             const ZAID& zaid,
                                             const double atomic_weight_ratio )
  : StandardAtomProperties( name, zaid, AtomicWeight::from_value(atomic_weight_ratio) )
{ /* ... */ }

// Copy constructor
StandardNuclideProperties::StandardNuclideProperties( const StandardNuclideProperties& other )
  : StandardAtomProperties( other ),
    d_nuclear_data_properties( other.d_nuclear_data_properties ),
    d_thermal_nuclear_data_properties( other.d_thermal_nuclear_data_properties ),
    d_adjoint_nuclear_data_properties( other.d_adjoint_nuclear_data_properties ),
    d_adjoint_thermal_nuclear_data_properties( other.d_adjoint_thermal_nuclear_data_properties ),
    d_photonuclear_data_properties( other.d_photonuclear_data_properties ),
    d_adjoint_photonuclear_data_properties( other.d_adjoint_photonuclear_data_properties )
{ /* ... */ }

// Check if the scattering center is a nuclide
bool StandardNuclideProperties::isNuclide() const
{
  return true;
}

// Get the atomic weight
auto StandardNuclideProperties::atomicWeight() const -> AtomicWeight
{
  return AtomicWeight::from_value( StandardAtomProperties::atomicWeight().value()*Utility::PhysicalConstants::neutron_rest_mass_amu );
}

// Get the atomic weight ratio (atomic weight/neutron weight)
double StandardNuclideProperties::atomicWeightRatio() const
{
  return StandardAtomProperties::atomicWeight().value();
}

// Check if there is nuclear data
bool StandardNuclideProperties::nuclearDataAvailable() const
{
  return !d_nuclear_data_properties.empty();
}

// Check if there is nuclear data available at the evaluation temp
bool StandardNuclideProperties::nuclearDataAvailable(
                                           const Energy evaluation_temp ) const
{
  return this->dataAvailable( d_nuclear_data_properties, evaluation_temp );
}

// Check if the nuclear data is evaluated at discrete temps
bool StandardNuclideProperties::nuclearDataEvaluatedAtDiscreteTemps() const
{
  return true;
}

// Get the nuclear data evaluation temps
auto StandardNuclideProperties::getNuclearDataEvaluationTempsInMeV() const -> std::vector<Energy>
{
  return this->getEvaluationTemps( d_nuclear_data_properties );
}

// Get the nuclear data properties
const NuclearDataProperties* StandardNuclideProperties::getNuclearDataProperties(
                                        const Energy evaluation_temp,
                                        const bool find_exact ) const
{
  return this->getDataProperties( d_nuclear_data_properties,
                                  "nuclear",
                                  evaluation_temp,
                                  find_exact );
}

// Add the nuclear data properties
void StandardNuclideProperties::addNuclearDataProperties(
               const std::shared_ptr<const NuclearDataProperties>& properties )
{
  this->addDataProperties( d_nuclear_data_properties,
                           "nuclear",
                           properties );
}

// Check if there is any thermal nuclear data
bool StandardNuclideProperties::thermalNuclearDataAvailable() const
{
  return !d_thermal_nuclear_data_properties.empty();
}

// Check if there is thermal nuclear data available at the evaluation temp
bool StandardNuclideProperties::thermalNuclearDataAvailable( const Energy evaluation_temp ) const
{
  return this->dataAvailable( d_thermal_nuclear_data_properties, evaluation_temp );
}

// Check if the thermal nuclear data is evaluated at discrete temps
bool StandardNuclideProperties::thermalNuclearDataEvaluatedAtDiscreteTemps() const
{
  return true;
}

// Get the thermal nuclear data evaluation temps
auto StandardNuclideProperties::getThermalNuclearDataEvaluationTempsInMeV() const -> std::vector<Energy>
{
  return this->getEvaluationTemps( d_thermal_nuclear_data_properties );
}

// Get the thermal nuclear data properties
const ThermalNuclearDataProperties* StandardNuclideProperties::getThermalNuclearDataProperties(
                                                  const Energy evaluation_temp,
                                                  const bool find_exact ) const
{
  return this->getDataProperties( d_thermal_nuclear_data_properties,
                                  "S(A,B)",
                                  evaluation_temp,
                                  find_exact );
}

// Add the thermal nuclear data properties
void StandardNuclideProperties::addThermalNuclearDataProperties(
        const std::shared_ptr<const ThermalNuclearDataProperties>& properties )
{
  this->addDataProperties( d_thermal_nuclear_data_properties,
                           "S(A,B)",
                           properties );
}

// Check if there is adjoint nuclear data
bool StandardNuclideProperties::adjointNuclearDataAvailable() const
{
  return !d_adjoint_nuclear_data_properties.empty();
}

// Check if there is nuclear data available at the evaluation temp
bool StandardNuclideProperties::adjointNuclearDataAvailable(
                                           const Energy evaluation_temp ) const
{
  return this->dataAvailable( d_adjoint_nuclear_data_properties, evaluation_temp );
}

// Check if the nuclear data is evaluated at discrete temps
bool StandardNuclideProperties::adjointNuclearDataEvaluatedAtDiscreteTemps() const
{
  return true;
}

// Get the nuclear data evaluation temps
auto StandardNuclideProperties::getAdjointNuclearDataEvaluationTempsInMeV() const -> std::vector<Energy>
{
  return this->getEvaluationTemps( d_adjoint_nuclear_data_properties );
}

// Get the nuclear data properties
const AdjointNuclearDataProperties* StandardNuclideProperties::getAdjointNuclearDataProperties(
                                        const Energy evaluation_temp,
                                        const bool find_exact ) const
{
  return this->getDataProperties( d_adjoint_nuclear_data_properties,
                                  "adjoint nuclear",
                                  evaluation_temp,
                                  find_exact );
}

// Add the nuclear data properties
void StandardNuclideProperties::addAdjointNuclearDataProperties(
        const std::shared_ptr<const AdjointNuclearDataProperties>& properties )
{
  this->addDataProperties( d_adjoint_nuclear_data_properties,
                           "adjoint nuclear",
                           properties );
}

// Check if there is any adjoint thermal nuclear data
bool StandardNuclideProperties::adjointThermalNuclearDataAvailable() const
{
  return !d_adjoint_thermal_nuclear_data_properties.empty();
}

// Check if there is thermal nuclear data available at the evaluation temp
bool StandardNuclideProperties::adjointThermalNuclearDataAvailable( const Energy evaluation_temp ) const
{
  return this->dataAvailable( d_adjoint_thermal_nuclear_data_properties, evaluation_temp );
}

// Check if the thermal nuclear data is evaluated at discrete temps
bool StandardNuclideProperties::adjointThermalNuclearDataEvaluatedAtDiscreteTemps() const
{
  return true;
}

// Get the thermal nuclear data evaluation temps
auto StandardNuclideProperties::getAdjointThermalNuclearDataEvaluationTempsInMeV() const -> std::vector<Energy>
{
  return this->getEvaluationTemps( d_adjoint_thermal_nuclear_data_properties );
}

// Get the thermal nuclear data properties
const AdjointThermalNuclearDataProperties* StandardNuclideProperties::getAdjointThermalNuclearDataProperties(
                                                  const Energy evaluation_temp,
                                                  const bool find_exact ) const
{
  return this->getDataProperties( d_adjoint_thermal_nuclear_data_properties,
                                  "adjoint S(A,B)",
                                  evaluation_temp,
                                  find_exact );
}

// Add the thermal nuclear data properties
void StandardNuclideProperties::addAdjointThermalNuclearDataProperties(
 const std::shared_ptr<const AdjointThermalNuclearDataProperties>& properties )
{
  this->addDataProperties( d_adjoint_thermal_nuclear_data_properties,
                           "adjoint S(A,B)",
                           properties );
}

// Check if there is photonuclear data
bool StandardNuclideProperties::photonuclearDataAvailable() const
{
  return d_photonuclear_data_properties.get();
}

// Get the photonuclear data properties
const PhotonuclearDataProperties* StandardNuclideProperties::getPhotonuclearDataProperties() const
{
  return d_photonuclear_data_properties.get();
}

// Set the photonuclear data properties
void StandardNuclideProperties::setPhotonuclearDataProperties( const std::shared_ptr<const PhotonuclearDataProperties>& properties )
{
  if( properties.get() )
    d_photonuclear_data_properties = properties;
}

// Check if there is adjoint photonuclear data
bool StandardNuclideProperties::adjointPhotonuclearDataAvailable() const
{
  return d_adjoint_photonuclear_data_properties.get();
}

// Get the adjoint photonuclear data
const AdjointPhotonuclearDataProperties* StandardNuclideProperties::getAdjointPhotonuclearDataProperties() const
{
  return d_adjoint_photonuclear_data_properties.get();
}

// Set the adjoint photonuclear data properties
void StandardNuclideProperties::setAdjointPhotonuclearDataProperties( const std::shared_ptr<const AdjointPhotonuclearDataProperties>& properties )
{
  if( properties.get() )
    d_adjoint_photonuclear_data_properties = properties;
}

// Clone the properties
StandardNuclideProperties* StandardNuclideProperties::clone() const
{
  return new StandardNuclideProperties( *this );
}

// Deep clone the properties
StandardNuclideProperties* StandardNuclideProperties::deepClone() const
{
  StandardNuclideProperties* nuclide_properties_clone =
    new StandardNuclideProperties( this->name(),
                                   this->zaid(),
                                   this->atomicWeightRatio() );

  // Clone the atomic data properties
  StandardAtomProperties::cloneStoredAtomProperties( *this, *nuclide_properties_clone );
  
  // Clone the nuclear data properties
  this->cloneDataProperties( d_nuclear_data_properties,
                             nuclide_properties_clone->d_nuclear_data_properties );

  // Clone the thermal nuclear data properties
  this->cloneDataProperties( d_thermal_nuclear_data_properties,
                             nuclide_properties_clone->d_thermal_nuclear_data_properties );

  // Clone the adjoint nuclear data properties
  this->cloneDataProperties( d_adjoint_nuclear_data_properties,
                             nuclide_properties_clone->d_adjoint_nuclear_data_properties );

  // Clone the adjoint thermal nuclear data properties
  this->cloneDataProperties( d_adjoint_thermal_nuclear_data_properties,
                             nuclide_properties_clone->d_adjoint_thermal_nuclear_data_properties );

  // Clone the photonuclear data properties
  if( d_photonuclear_data_properties.get() )
  {
    std::shared_ptr<const PhotonuclearDataProperties>
      properties_clone( d_photonuclear_data_properties->clone() );

    nuclide_properties_clone->setPhotonuclearDataProperties( properties_clone );
  }
  
  // Clone the adjoint photonuclear data properties
  if( d_adjoint_photonuclear_data_properties.get() )
  {
    std::shared_ptr<const AdjointPhotonuclearDataProperties>
      properties_clone( d_adjoint_photonuclear_data_properties->clone() );

    nuclide_properties_clone->setAdjointPhotonuclearDataProperties( properties_clone );
  }
  
  return nuclide_properties_clone;
}

// Save the properties to an archive
template<typename Archive>
void StandardNuclideProperties::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( StandardAtomProperties );

  // Save the local member data
  ar & BOOST_SERIALIZATION_NVP( d_nuclear_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_thermal_nuclear_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_nuclear_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_thermal_nuclear_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_photonuclear_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_photonuclear_data_properties );
}

// Load the properties from an archive
template<typename Archive>
void StandardNuclideProperties::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( StandardAtomProperties );

  // Load the local member data
  ar & BOOST_SERIALIZATION_NVP( d_nuclear_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_thermal_nuclear_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_nuclear_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_thermal_nuclear_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_photonuclear_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_photonuclear_data_properties );
}

EXPLICIT_DATA_CLASS_SAVE_LOAD_INST( StandardNuclideProperties );
  
} // end Data namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( StandardNuclideProperties, Data );

//---------------------------------------------------------------------------//
// end Data_StandardNuclideProperties.cpp
//---------------------------------------------------------------------------//
