//---------------------------------------------------------------------------//
//!
//! \file   Data_StandardAtomProperties.cpp
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
#include "Data_StandardAtomProperties.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Data{

// Default constructor
StandardAtomProperties::StandardAtomProperties()
{ /* ... */ }

// Constructor
StandardAtomProperties::StandardAtomProperties( const std::string& name,
                                                const ZAID& zaid,
                                                const double atomic_weight )
  : d_name( name ),
    d_zaid( zaid ),
    d_atomic_weight( atomic_weight )
{
  TEST_FOR_EXCEPTION( name.empty(),
                      std::runtime_error,
                      "The properties name cannot be empty!" );

  TEST_FOR_EXCEPTION( atomic_weight <= 0.0,
                      std::runtime_error,
                      "The atomic weight cannot be zero or negative!" );
}

// Copy constructor
StandardAtomProperties::StandardAtomProperties( const StandardAtomProperties& other )
  : d_name( other.d_name ),
    d_zaid( other.d_zaid ),
    d_atomic_weight( other.d_atomic_weight ),
    d_photoatomic_data_properties( other.d_photoatomic_data_properties ),
    d_adjoint_photoatomic_data_properties( other.d_adjoint_photoatomic_data_properties ),
    d_electroatomic_data_properties( other.d_electroatomic_data_properties ),
    d_adjoint_electroatomic_data_properties( other.d_adjoint_electroatomic_data_properties )
{ /* ... */ }

// Check if the scattering center is an atom
bool StandardAtomProperties::isAtom() const
{
  return true;
}

// Check if the scattering center is a nuclide
bool StandardAtomProperties::isNuclide() const
{
  return false;
}

// Get the name of the properties
std::string StandardAtomProperties::name() const
{
  return d_name;
}

// Get the zaid
Data::ZAID StandardAtomProperties::zaid() const
{
  return d_zaid;
}

// Get the atomic weight
auto StandardAtomProperties::atomicWeight() const -> AtomicWeight
{
  return AtomicWeight::from_value(d_atomic_weight);
}

// Check if there is nuclear data
bool StandardAtomProperties::nuclearDataAvailable() const
{
  return false;
}

// Check if there is nuclear data available at the evaluation temp
bool StandardAtomProperties::nuclearDataAvailable( const Energy ) const
{
  return false;
}

// Check if the nuclear data is evaluated at discrete temps
bool StandardAtomProperties::nuclearDataEvaluatedAtDiscreteTemps() const
{
  return false;
}

// Get the nuclear data evaluation temps (in MeV)
auto StandardAtomProperties::getNuclearDataEvaluationTempsInMeV() const -> std::vector<Energy>
{
  return std::vector<Energy>();
}

//  Get the nuclear data properties
const NuclearDataProperties* StandardAtomProperties::getNuclearDataProperties(
                                               const Energy, const bool ) const
{
  return NULL;
}

// Check if there is any thermal nuclear data
bool StandardAtomProperties::thermalNuclearDataAvailable() const
{
  return false;
}

// Check if there is thermal nuclear data available at the evaluation temp
bool StandardAtomProperties::thermalNuclearDataAvailable( const Energy ) const
{
  return false;
}

// Check if the thermal nuclear data is evaluated at discrete temps
bool StandardAtomProperties::thermalNuclearDataEvaluatedAtDiscreteTemps() const
{
  return false;
}

// Get the thermal nuclear data evaluation temps
auto StandardAtomProperties::getThermalNuclearDataEvaluationTempsInMeV() const -> std::vector<Energy>
{
  return std::vector<Energy>();
}

// Get the thermal nuclear data properties
const ThermalNuclearDataProperties* StandardAtomProperties::getThermalNuclearDataProperties(
                                               const Energy, const bool ) const
{
  return NULL;
}

// Check if there is adjoint nuclear data
bool StandardAtomProperties::adjointNuclearDataAvailable() const
{
  return false;
}

// Check if there is adjoint nuclear data available at the evaluation temp
bool StandardAtomProperties::adjointNuclearDataAvailable( const Energy ) const
{
  return false;
}

// Check if the adjoint nuclear data is evaluation at discrete temps
bool StandardAtomProperties::adjointNuclearDataEvaluatedAtDiscreteTemps() const
{
  return false;
}

// Get the adjoint nuclear data evaluation temps
auto StandardAtomProperties::getAdjointNuclearDataEvaluationTempsInMeV() const -> std::vector<Energy>
{
  return std::vector<Energy>();
}

// Get the adjoint nuclear data
const AdjointNuclearDataProperties* StandardAtomProperties::getAdjointNuclearDataProperties(
                                               const Energy, const bool ) const
{
  return NULL;
}

// Check if there is any adjoint thermal nuclear data
bool StandardAtomProperties::adjointThermalNuclearDataAvailable() const
{
  return false;
}

// Check if there is adjoint thermal nuclear data available at the evaluation temp
bool StandardAtomProperties::adjointThermalNuclearDataAvailable( const Energy ) const
{
  return false;
}

// Check if the adjoint thermal nuclear data is evaluated at discrete temps
bool StandardAtomProperties::adjointThermalNuclearDataEvaluatedAtDiscreteTemps() const
{
  return false;
}

// Get the adjoint thermal nuclear data evaluation temps
auto StandardAtomProperties::getAdjointThermalNuclearDataEvaluationTempsInMeV() const -> std::vector<Energy>
{
  return std::vector<Energy>();
}

// Get the adjoint thermal nuclear data
const AdjointThermalNuclearDataProperties* StandardAtomProperties::getAdjointThermalNuclearDataProperties(
                                               const Energy, const bool ) const
{
  return NULL;
}

// Check if there is photonuclear data
bool StandardAtomProperties::photonuclearDataAvailable() const
{
  return false;
}

// Get the photonuclear data properties
const PhotonuclearDataProperties* StandardAtomProperties::getPhotonuclearDataProperties() const
{
  return NULL;
}

// Check if there is adjoint photonuclear data
bool StandardAtomProperties::adjointPhotonuclearDataAvailable() const
{
  return false;
}

// Get the adjoint photonuclear data
const AdjointPhotonuclearDataProperties* StandardAtomProperties::getAdjointPhotonuclearDataProperties() const
{
  return NULL;
}

// Check if there is photoatomic data
bool StandardAtomProperties::photoatomicDataAvailable() const
{
  return d_photoatomic_data_properties.get();
}

// Get the photoatomic data
const PhotoatomicDataProperties* StandardAtomProperties::getPhotoatomicDataProperties() const
{
  return d_photoatomic_data_properties.get();
}

// Set the photoatomic data
void StandardAtomProperties::setPhotoatomicDataProperties( const std::shared_ptr<const PhotoatomicDataProperties>& properties )
{
  if( properties.get() )
    d_photoatomic_data_properties = properties;
}

// Check if there is adjoint photoatomic data
bool StandardAtomProperties::adjointPhotoatomicDataAvailable() const
{
  return d_adjoint_photoatomic_data_properties.get();
}

// Get the adjoint photoatomic data properties
const AdjointPhotoatomicDataProperties* StandardAtomProperties::getAdjointPhotoatomicDataProperties() const
{
  return d_adjoint_photoatomic_data_properties.get();
}

// Set the adjoint photoatomic data properties
void StandardAtomProperties::setAdjointPhotoatomicDataProperties( const std::shared_ptr<const AdjointPhotoatomicDataProperties>& properties )
{
  if( properties.get() )
    d_adjoint_photoatomic_data_properties = properties;
}

// Check if there is electroatomic data
bool StandardAtomProperties::electroatomicDataAvailable() const
{
  return d_electroatomic_data_properties.get();
}

// Get the electroatomic data properties
const ElectroatomicDataProperties* StandardAtomProperties::getElectroatomicDataProperties() const
{
  return d_electroatomic_data_properties.get();
}

// Set the electroatomic data properties
void StandardAtomProperties::setElectroatomicDataProperties( const std::shared_ptr<const ElectroatomicDataProperties>& properties )
{
  if( properties )
    d_electroatomic_data_properties = properties;
}

// Check if there is adjoint electroatomic data
bool StandardAtomProperties::adjointElectroatomicDataAvailable() const
{
  return d_adjoint_electroatomic_data_properties.get();
}

// Get the adjoint electroatomic data properties
const AdjointElectroatomicDataProperties* StandardAtomProperties::getAdjointElectroatomicDataProperties() const
{
  return d_adjoint_electroatomic_data_properties.get();
}

// Set the adjoint electroatomic data properties
void StandardAtomProperties::setAdjointElectroatomicDataProperties( const std::shared_ptr<const AdjointElectroatomicDataProperties>& properties )
{
  if( properties )
    d_adjoint_electroatomic_data_properties = properties;
}

// Clone the properties
StandardAtomProperties* StandardAtomProperties::clone() const
{
  return new StandardAtomProperties( *this );
}

// Deep clone the properties
StandardAtomProperties* StandardAtomProperties::deepClone() const
{
  StandardAtomProperties* atom_properties_clone =
    new StandardAtomProperties( d_name, d_zaid, d_atomic_weight );
  
  StandardAtomProperties::cloneStoredAtomProperties( *this, *atom_properties_clone );

  return atom_properties_clone;
}

// Clone the stored properties
void StandardAtomProperties::cloneStoredAtomProperties(
                             const StandardAtomProperties& original_properties,
                             StandardAtomProperties& new_properties )
{
  // Clone the photoatomic data properties
  if( original_properties.photoatomicDataAvailable() )
  {
    std::shared_ptr<const PhotoatomicDataProperties>
      properties_clone( original_properties.getPhotoatomicDataProperties()->clone() );

    new_properties.setPhotoatomicDataProperties( properties_clone );
  }

  // Clone the adjoint photoatomic data properties
  if( original_properties.adjointPhotoatomicDataAvailable() )
  {
    std::shared_ptr<const AdjointPhotoatomicDataProperties>
      properties_clone( original_properties.getAdjointPhotoatomicDataProperties()->clone() );

    new_properties.setAdjointPhotoatomicDataProperties( properties_clone );
  }

  // Clone the electroatomic data properties
  if( original_properties.electroatomicDataAvailable() )
  {
    std::shared_ptr<const ElectroatomicDataProperties>
      properties_clone( original_properties.getElectroatomicDataProperties()->clone() );

    new_properties.setElectroatomicDataProperties( properties_clone );
  }

  // Clone the adjoint electroatomic data properties
  if( original_properties.adjointElectroatomicDataAvailable() )
  {
    std::shared_ptr<const AdjointElectroatomicDataProperties>
      properties_clone( original_properties.getAdjointElectroatomicDataProperties()->clone() );

    new_properties.setAdjointElectroatomicDataProperties( properties_clone );
  }
}

// Save the properties to an archive
template<typename Archive>
void StandardAtomProperties::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ScatteringCenterProperties );

  // Save the local member data
  ar & BOOST_SERIALIZATION_NVP( d_name );
  ar & BOOST_SERIALIZATION_NVP( d_zaid );
  ar & BOOST_SERIALIZATION_NVP( d_atomic_weight );
  ar & BOOST_SERIALIZATION_NVP( d_photoatomic_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_photoatomic_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_electroatomic_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_electroatomic_data_properties );
}

// Load the properties from an archive
template<typename Archive>
void StandardAtomProperties::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ScatteringCenterProperties );

  // Load the local member data
  ar & BOOST_SERIALIZATION_NVP( d_name );
  ar & BOOST_SERIALIZATION_NVP( d_zaid );
  ar & BOOST_SERIALIZATION_NVP( d_atomic_weight );
  ar & BOOST_SERIALIZATION_NVP( d_photoatomic_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_photoatomic_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_electroatomic_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_electroatomic_data_properties );
}

EXPLICIT_DATA_CLASS_SAVE_LOAD_INST( StandardAtomProperties );
  
} // end Data namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( StandardAtomProperties, Data );

//---------------------------------------------------------------------------//
// end Data_StandardAtomProperties.cpp
//---------------------------------------------------------------------------//
