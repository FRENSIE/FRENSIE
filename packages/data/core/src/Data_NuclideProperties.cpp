//---------------------------------------------------------------------------//
//!
//! \file   Data_NuclideProperties.cpp
//! \author Alex Robinson
//! \brief  The nuclide properties class definition
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
#include <boost/serialization/map.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/shared_ptr.hpp>

// FRENSIE Includes
#include "Data_NuclideProperties.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Data{

// Default constructor
NuclideProperties::NuclideProperties()
{ /* ... */ }

// Constructor
NuclideProperties::NuclideProperties( const Data::ZAID zaid,
                                      const double atomic_weight_ratio )
  : AtomProperties( zaid, atomic_weight_ratio )
{ /* ... */ }

// Partial copy constructor
NuclideProperties::NuclideProperties( const AtomProperties& atom_properties,
                                      const Data::ZAID zaid,
                                      const double atomic_weight_ratio )
  : AtomProperties( atom_properties )
{
  this->setZAID( zaid );
  this->setAtomicWeightRatio( atomic_weight_ratio );
}

// Partial copy constructor
NuclideProperties::NuclideProperties( const AtomProperties& atom_properties )
  : AtomProperties( atom_properties )
{ /* ... */ }

// Copy constructor
NuclideProperties::NuclideProperties( const NuclideProperties& other )
  : AtomProperties( other ),
    d_nuclear_data_properties( other.d_nuclear_data_properties ),
    d_thermal_nuclear_data_properties( other.d_thermal_nuclear_data_properties ),
    d_adjoint_nuclear_data_properties( other.d_adjoint_nuclear_data_properties ),
    d_adjoint_thermal_nuclear_data_properties( other.d_adjoint_thermal_nuclear_data_properties ),
    d_photonuclear_data_properties( other.d_photonuclear_data_properties ),
    d_adjoint_photonuclear_data_properties( other.d_adjoint_photonuclear_data_properties )
{ /* ... */ }

// Check if the scattering center is a nuclide
bool NuclideProperties::isNuclide() const
{
  return true;
}

// Check if there is nuclear data with the desired format
bool NuclideProperties::nuclearDataAvailable(
                        const NuclearDataProperties::FileType file_type ) const
{
  return AtomProperties::dataAvailable( d_nuclear_data_properties, file_type );
}

// Check if there is nuclear data with the desired format and version
bool NuclideProperties::nuclearDataAvailable(
                               const NuclearDataProperties::FileType file_type,
                               const unsigned table_major_version ) const
{
  return AtomProperties::dataAvailable( d_nuclear_data_properties,
                                        file_type,
                                        table_major_version );
}
  
// Check if there is nuclear data at the evaluation temp
bool NuclideProperties::nuclearDataAvailable(
                               const NuclearDataProperties::FileType file_type,
                               const unsigned table_major_version,
                               const Energy evaluation_temp ) const
{
  return this->dataAvailable( d_nuclear_data_properties,
                              file_type,
                              table_major_version,
                              evaluation_temp );
}

// Check if there is nuclear data at the desired evaluation temp
bool NuclideProperties::nuclearDataAvailable(
                               const NuclearDataProperties::FileType file_type,
                               const unsigned table_major_version,
                               const Temperature evaluation_temp ) const
{
  return this->dataAvailable( d_nuclear_data_properties,
                              file_type,
                              table_major_version,
                              evaluation_temp );
}

// Get the nuclear data file types
std::set<NuclearDataProperties::FileType> NuclideProperties::getNuclearDataFileTypes() const
{
  return AtomProperties::getDataFileTypes( d_nuclear_data_properties );
}

// Get the nuclear data file versions
std::set<unsigned> NuclideProperties::getDataFileVersions(
                        const NuclearDataProperties::FileType file_type ) const
{
  return AtomProperties::getDataFileVersions( d_nuclear_data_properties,
                                              file_type );
}

// Get the recommended nuclear data file major version (generally the newest version)
unsigned NuclideProperties::getRecommendedDataFileVersion(
                        const NuclearDataProperties::FileType file_type ) const
{
  return AtomProperties::getMaxDataFileVersion( d_nuclear_data_properties,
                                                file_type,
                                                "Nuclear" );
}

// Get the nuclear data evaluation temps
auto NuclideProperties::getDataEvaluationTempsInMeV(
              const NuclearDataProperties::FileType file_type,
              const unsigned table_major_version ) const -> std::vector<Energy>
{
  return this->getDataEvaluationTempsInMeV( d_nuclear_data_properties,
                                            file_type,
                                            table_major_version );
}

// Get the nuclear data evaluation temps
auto NuclideProperties::getDataEvaluationTemps(
         const NuclearDataProperties::FileType file_type,
         const unsigned table_major_version ) const -> std::vector<Temperature>
{
  return this->getDataEvaluationTemps( d_nuclear_data_properties,
                                       file_type,
                                       table_major_version );
}

// Get the nuclear data properties
const NuclearDataProperties& NuclideProperties::getNuclearDataProperties(
                               const NuclearDataProperties::FileType file_type,
                               const unsigned table_major_version,
                               const Energy evaluation_temp,
                               const bool find_exact ) const
{
  return this->getProperties<NuclearDataProperties>( d_nuclear_data_properties,
                                                     file_type,
                                                     table_major_version,
                                                     evaluation_temp,
                                                     find_exact,
                                                     "Nuclear" );
}

// Get the nuclear data properties
const NuclearDataProperties& NuclideProperties::getNuclearDataProperties(
                              const NuclearDataProperties::FileType file_type,
                              const unsigned table_major_version,
                              const Temperature evaluation_temp,
                              const bool find_exact ) const
{
  return this->getProperties<NuclearDataProperties>( d_nuclear_data_properties,
                                                     file_type,
                                                     table_major_version,
                                                     evaluation_temp,
                                                     find_exact,
                                                     "Nuclear" );
}

// Set the nuclear data properties
void NuclideProperties::setNuclearDataProperties( const std::shared_ptr<const NuclearDataProperties>& properties )
{
  this->setNuclearProperties( d_nuclear_data_properties,
                              properties,
                              "Nuclear" );
}

// Check if there is thermal nuclear data available
bool NuclideProperties::thermalNuclearDataAvailable(
                                                const std::string& name ) const
{
  return this->dataAvailable( d_thermal_nuclear_data_properties, name );
}

// Check if there is thermal nuclear data with the desired format
bool NuclideProperties::thermalNuclearDataAvailable(
                 const std::string& name,
                 const ThermalNuclearDataProperties::FileType file_type ) const
{
  return this->dataAvailable( d_thermal_nuclear_data_properties,
                              name,
                              file_type );
}

// Check if there is thermal nuclear data with the desired format
bool NuclideProperties::thermalNuclearDataAvailable(
                        const std::string& name,
                        const ThermalNuclearDataProperties::FileType file_type,
                        const unsigned table_major_version ) const
{
  return this->dataAvailable( d_thermal_nuclear_data_properties,
                              name,
                              file_type,
                              table_major_version );
}

// Check if there is thermal nuclear data with the desired format
bool NuclideProperties::thermalNuclearDataAvailable(
                        const std::string& name,
                        const ThermalNuclearDataProperties::FileType file_type,
                        const unsigned table_major_version,
                        const Energy evaluation_temp ) const
{
  return this->dataAvailable( d_thermal_nuclear_data_properties,
                              name,
                              file_type,
                              table_major_version,
                              evaluation_temp );
}

// Check if there is thermal nuclear data with the desired format
bool NuclideProperties::thermalNuclearDataAvailable(
                        const std::string& name,
                        const ThermalNuclearDataProperties::FileType file_type,
                        const unsigned table_major_version,
                        const Temperature evaluation_temp ) const
{
  return this->dataAvailable( d_thermal_nuclear_data_properties,
                              name,
                              file_type,
                              table_major_version,
                              evaluation_temp );
}

// Get the thermal nuclear data names
std::set<std::string> NuclideProperties::getThermalNuclearDataNames() const
{
  return this->getThermalNuclearDataNames( d_thermal_nuclear_data_properties );
}

// Get the thermal nuclear data file types
std::set<ThermalNuclearDataProperties::FileType> NuclideProperties::getThermalNuclearDataFileTypes( const std::string& name ) const
{
  return this->getDataFileTypes( d_thermal_nuclear_data_properties, name );
}

// Get the thermal nuclear data file versions
std::set<unsigned> NuclideProperties::getDataFileVersions(
                 const std::string& name,
                 const ThermalNuclearDataProperties::FileType file_type ) const
{
  return this->getDataFileVersions( d_thermal_nuclear_data_properties,
                                    name,
                                    file_type );
}

// Get the recommended thermal nuclear data file major version (generally the newest version)
unsigned NuclideProperties::getRecommendedDataFileVersion(
                 const std::string& name,
                 const ThermalNuclearDataProperties::FileType file_type ) const
{
  switch( file_type )
  {
    case ThermalNuclearDataProperties::MCNP6_ACE_FILE:
      return 2;
    default:
    {
      return this->getMaxDataFileVersion( d_thermal_nuclear_data_properties,
                                          name,
                                          file_type,
                                          "Thermal nuclear" );
    }
  }
}

// Get the thermal nuclear data evaluation temps
auto NuclideProperties::getDataEvaluationTempsInMeV(
              const std::string& name,
              const ThermalNuclearDataProperties::FileType file_type,
              const unsigned table_major_version ) const -> std::vector<Energy>
{
  return this->getDataEvaluationTempsInMeV( d_thermal_nuclear_data_properties,
                                            name,
                                            file_type,
                                            table_major_version );
}

// Get the thermal nuclear data evaluation temps
auto NuclideProperties::getDataEvaluationTemps(
         const std::string& name,
         const ThermalNuclearDataProperties::FileType file_type,
         const unsigned table_major_version ) const -> std::vector<Temperature>
{
  return this->getDataEvaluationTemps( d_thermal_nuclear_data_properties,
                                       name,
                                       file_type,
                                       table_major_version );
}

// Get the thermal nuclear data properties
const ThermalNuclearDataProperties& NuclideProperties::getThermalNuclearDataProperties(
                        const std::string& name,
                        const ThermalNuclearDataProperties::FileType file_type,
                        const unsigned table_major_version,
                        const Energy evaluation_temp,
                        const bool find_exact ) const
{
  return this->getProperties<ThermalNuclearDataProperties>(
                                             d_thermal_nuclear_data_properties,
                                             name,
                                             file_type,
                                             table_major_version,
                                             evaluation_temp,
                                             find_exact,
                                             "Thermal nuclear" );
}

// Get the thermal nuclear data properties
const ThermalNuclearDataProperties& NuclideProperties::getThermalNuclearDataProperties(
                        const std::string& name,
                        const ThermalNuclearDataProperties::FileType file_type,
                        const unsigned table_major_version,
                        const Temperature evaluation_temp,
                        const bool find_exact ) const
{
  return this->getProperties<ThermalNuclearDataProperties>(
                                             d_thermal_nuclear_data_properties,
                                             name,
                                             file_type,
                                             table_major_version,
                                             evaluation_temp,
                                             find_exact,
                                             "Thermal nuclear" );
}

// Set the nuclear data properties
void NuclideProperties::setThermalNuclearDataProperties( const std::shared_ptr<const ThermalNuclearDataProperties>& properties )
{
  this->setThermalNuclearProperties( d_thermal_nuclear_data_properties,
                                     properties,
                                     "Thermal nuclear" );
}

// Check if there is adjoint nuclear data with the desired format
bool NuclideProperties::adjointNuclearDataAvailable(
                 const AdjointNuclearDataProperties::FileType file_type ) const
{
  return AtomProperties::dataAvailable( d_adjoint_nuclear_data_properties,
                                        file_type );
}

// Check if there is adjoint nuclear data with the desired format and version
bool NuclideProperties::adjointNuclearDataAvailable(
                        const AdjointNuclearDataProperties::FileType file_type,
                        const unsigned table_major_version ) const
{
  return AtomProperties::dataAvailable( d_adjoint_nuclear_data_properties,
                                        file_type,
                                        table_major_version );
}
  
// Check if there is adjoint nuclear data at the evaluation temp
bool NuclideProperties::adjointNuclearDataAvailable(
                        const AdjointNuclearDataProperties::FileType file_type,
                        const unsigned table_major_version,
                        const Energy evaluation_temp ) const
{
  return this->dataAvailable( d_adjoint_nuclear_data_properties,
                              file_type,
                              table_major_version,
                              evaluation_temp );
}

// Check if there is adjoint nuclear data at the desired evaluation temp
bool NuclideProperties::adjointNuclearDataAvailable(
                        const AdjointNuclearDataProperties::FileType file_type,
                        const unsigned table_major_version,
                        const Temperature evaluation_temp ) const
{
  return this->dataAvailable( d_adjoint_nuclear_data_properties,
                              file_type,
                              table_major_version,
                              evaluation_temp );
}

// Get the adjoint nuclear data file types
std::set<AdjointNuclearDataProperties::FileType> NuclideProperties::getAdjointNuclearDataFileTypes() const
{
  return AtomProperties::getDataFileTypes( d_adjoint_nuclear_data_properties );
}

// Get the adjoint nuclear data file versions
std::set<unsigned> NuclideProperties::getDataFileVersions(
                 const AdjointNuclearDataProperties::FileType file_type ) const
{
  return AtomProperties::getDataFileVersions( d_adjoint_nuclear_data_properties,
                                              file_type );
}

// Get the recommended adjoint nuclear data file major version (generally the newest version)
unsigned NuclideProperties::getRecommendedDataFileVersion(
                 const AdjointNuclearDataProperties::FileType file_type ) const
{
  return AtomProperties::getMaxDataFileVersion(
                                             d_adjoint_nuclear_data_properties,
                                             file_type,
                                             "Adjoint nuclear" );
}

// Get the adjoint nuclear data evaluation temps
auto NuclideProperties::getDataEvaluationTempsInMeV(
              const AdjointNuclearDataProperties::FileType file_type,
              const unsigned table_major_version ) const -> std::vector<Energy>
{
  return this->getDataEvaluationTempsInMeV( d_adjoint_nuclear_data_properties,
                                            file_type,
                                            table_major_version );
}

// Get the adjoint nuclear data evaluation temps
auto NuclideProperties::getDataEvaluationTemps(
         const AdjointNuclearDataProperties::FileType file_type,
         const unsigned table_major_version ) const -> std::vector<Temperature>
{
  return this->getDataEvaluationTemps( d_adjoint_nuclear_data_properties,
                                       file_type,
                                       table_major_version );
}

// Get the adjoint nuclear data properties
const AdjointNuclearDataProperties& NuclideProperties::getAdjointNuclearDataProperties(
                        const AdjointNuclearDataProperties::FileType file_type,
                        const unsigned table_major_version,
                        const Energy evaluation_temp,
                        const bool find_exact ) const
{
  return this->getProperties<AdjointNuclearDataProperties>(
                                             d_adjoint_nuclear_data_properties,
                                             file_type,
                                             table_major_version,
                                             evaluation_temp,
                                             find_exact,
                                             "Adjoint nuclear" );
}

// Get the adjoint nuclear data properties
const AdjointNuclearDataProperties& NuclideProperties::getAdjointNuclearDataProperties(
                        const AdjointNuclearDataProperties::FileType file_type,
                        const unsigned table_major_version,
                        const Temperature evaluation_temp,
                        const bool find_exact ) const
{
  return this->getProperties<AdjointNuclearDataProperties>(
                                             d_adjoint_nuclear_data_properties,
                                             file_type,
                                             table_major_version,
                                             evaluation_temp,
                                             find_exact,
                                             "Adjoint nuclear" );
}

// Set the adjoint nuclear data properties
void NuclideProperties::setAdjointNuclearDataProperties( const std::shared_ptr<const AdjointNuclearDataProperties>& properties )
{
  this->setNuclearProperties( d_adjoint_nuclear_data_properties,
                              properties,
                              "Adjoint nuclear" );
}

// Check if there is thermal nuclear data available
bool NuclideProperties::adjointThermalNuclearDataAvailable(
                                                const std::string& name ) const
{
  return this->dataAvailable( d_adjoint_thermal_nuclear_data_properties,
                              name );
                              
}

// Check if there is adjoint thermal nuclear data with the desired format
bool NuclideProperties::adjointThermalNuclearDataAvailable(
     const std::string& name,
     const AdjointThermalNuclearDataProperties::FileType file_type ) const
{
  return this->dataAvailable( d_adjoint_thermal_nuclear_data_properties,
                              name,
                              file_type );
}

// Check if there is adjoint thermal nuclear data with the desired format
bool NuclideProperties::adjointThermalNuclearDataAvailable(
                 const std::string& name,
                 const AdjointThermalNuclearDataProperties::FileType file_type,
                 const unsigned table_major_version ) const
{
  return this->dataAvailable( d_adjoint_thermal_nuclear_data_properties,
                              name,
                              file_type,
                              table_major_version );
}

// Check if there is adjoint thermal nuclear data with the desired format
bool NuclideProperties::adjointThermalNuclearDataAvailable(
                 const std::string& name,
                 const AdjointThermalNuclearDataProperties::FileType file_type,
                 const unsigned table_major_version,
                 const Energy evaluation_temp ) const
{
  return this->dataAvailable( d_adjoint_thermal_nuclear_data_properties,
                              name,
                              file_type,
                              table_major_version,
                              evaluation_temp );
}

// Check if there is adjoint thermal nuclear data with the desired format
bool NuclideProperties::adjointThermalNuclearDataAvailable(
                 const std::string& name,
                 const AdjointThermalNuclearDataProperties::FileType file_type,
                 const unsigned table_major_version,
                 const Temperature evaluation_temp ) const
{
  return this->dataAvailable( d_adjoint_thermal_nuclear_data_properties,
                              name,
                              file_type,
                              table_major_version,
                              evaluation_temp );
}

// Get the adjoint thermal nuclear data names
std::set<std::string> NuclideProperties::getAdjointThermalNuclearDataNames() const
{
  return this->getThermalNuclearDataNames( d_adjoint_thermal_nuclear_data_properties );
                                           
}

// Get the adjoint thermal nuclear data file types
std::set<AdjointThermalNuclearDataProperties::FileType> NuclideProperties::getAdjointThermalDataFileTypes( const std::string& name ) const
{
  return this->getDataFileTypes( d_adjoint_thermal_nuclear_data_properties,
                                  name );
}

// Get the adjoint thermal nuclear data file versions
std::set<unsigned> NuclideProperties::getDataFileVersions(
          const std::string& name,
          const AdjointThermalNuclearDataProperties::FileType file_type ) const
{
  return this->getDataFileVersions( d_adjoint_thermal_nuclear_data_properties,
                                    name,
                                    file_type );
}

// Get the recommended adjoint thermal nuclear data file major version (generally the newest version)
unsigned NuclideProperties::getRecommendedDataFileVersion(
          const std::string& name,
          const AdjointThermalNuclearDataProperties::FileType file_type ) const
{
  return this->getMaxDataFileVersion( d_adjoint_thermal_nuclear_data_properties,
                                      name,
                                      file_type,
                                      "Adjoint thermal nuclear" );
}

// Get the adjoint thermal nuclear data evaluation temps
auto NuclideProperties::getDataEvaluationTempsInMeV(
              const std::string& name,
              const AdjointThermalNuclearDataProperties::FileType file_type,
              const unsigned table_major_version ) const -> std::vector<Energy>
{
  return this->getDataEvaluationTempsInMeV( d_adjoint_thermal_nuclear_data_properties,
                                            name,
                                            file_type,
                                            table_major_version );
}

// Get the adjoint thermal nuclear data evaluation temps
auto NuclideProperties::getDataEvaluationTemps(
         const std::string& name,
         const AdjointThermalNuclearDataProperties::FileType file_type,
         const unsigned table_major_version ) const -> std::vector<Temperature>
{
  return this->getDataEvaluationTemps( d_adjoint_thermal_nuclear_data_properties,
                                       name,
                                       file_type,
                                       table_major_version );
}

// Get the adjoint thermal nuclear data properties
const AdjointThermalNuclearDataProperties& NuclideProperties::getAdjointThermalNuclearDataProperties(
                 const std::string& name,
                 const AdjointThermalNuclearDataProperties::FileType file_type,
                 const unsigned table_major_version,
                 const Energy evaluation_temp,
                 const bool find_exact ) const
{
  return this->getProperties<AdjointThermalNuclearDataProperties>(
                                     d_adjoint_thermal_nuclear_data_properties,
                                     name,
                                     file_type,
                                     table_major_version,
                                     evaluation_temp,
                                     find_exact,
                                     "Adjoint thermal nuclear" );
}

// Get the adjoint thermal nuclear data properties
const AdjointThermalNuclearDataProperties& NuclideProperties::getAdjointThermalNuclearDataProperties(
                 const std::string& name,
                 const AdjointThermalNuclearDataProperties::FileType file_type,
                 const unsigned table_major_version,
                 const Temperature evaluation_temp,
                 const bool find_exact ) const
{
  return this->getProperties<AdjointThermalNuclearDataProperties>(
                                     d_adjoint_thermal_nuclear_data_properties,
                                     name,
                                     file_type,
                                     table_major_version,
                                     evaluation_temp,
                                     find_exact,
                                     "Adjoint thermal nuclear" );
}

// Set the adjoint thermal nuclear data properties
void NuclideProperties::setAdjointThermalNuclearDataProperties( const std::shared_ptr<const AdjointThermalNuclearDataProperties>& properties )
{
  this->setThermalNuclearProperties( d_adjoint_thermal_nuclear_data_properties,
                                     properties,
                                     "Adjoint thermal nuclear" );
}

// Check if there is photonuclear data with the desired format
bool NuclideProperties::photonuclearDataAvailable(
                   const PhotonuclearDataProperties::FileType file_type ) const
{
  return AtomProperties::dataAvailable( d_photonuclear_data_properties,
                                        file_type );
}

// Check if there is photonuclear data with the desired format and version
bool NuclideProperties::photonuclearDataAvailable(
                          const PhotonuclearDataProperties::FileType file_type,
                          const unsigned table_version ) const
{
  return AtomProperties::dataAvailable( d_photonuclear_data_properties,
                                        file_type,
                                        table_version );
}

// Get the photonuclear data file types
std::set<PhotonuclearDataProperties::FileType> NuclideProperties::getPhotonuclearDataFileTypes() const
{
  return AtomProperties::getDataFileTypes( d_photonuclear_data_properties );
}

// Get the photonuclear data file versions
std::set<unsigned> NuclideProperties::getDataFileVersions(
                   const PhotonuclearDataProperties::FileType file_type ) const
{
  return AtomProperties::getDataFileVersions( d_photonuclear_data_properties,
                                              file_type );
}

// Get the recommended photonuclear data file version
unsigned NuclideProperties::getRecommendedDataFileVersion(
                   const PhotonuclearDataProperties::FileType file_type ) const
{
  return AtomProperties::getMaxDataFileVersion( d_photonuclear_data_properties,
                                                file_type,
                                                "Photonuclear" );
}

// Get the photonuclear data properties
const PhotonuclearDataProperties& NuclideProperties::getPhotonuclearDataProperties(
                          const PhotonuclearDataProperties::FileType file_type,
                          const unsigned table_version ) const
{
  return AtomProperties::getProperties<PhotonuclearDataProperties>(
                                                d_photonuclear_data_properties,
                                                file_type,
                                                table_version,
                                                "Photonuclear" );
}

// Set the photonuclear data properties
void NuclideProperties::setPhotonuclearDataProperties( const std::shared_ptr<const PhotonuclearDataProperties>& properties )
{
  AtomProperties::setProperties( d_photonuclear_data_properties,
                                 properties,
                                 "Photonuclear" );
}

// Check if there is adjoint photonuclear data with the desired format
bool NuclideProperties::adjointPhotonuclearDataAvailable(
            const AdjointPhotonuclearDataProperties::FileType file_type ) const
{
  return AtomProperties::dataAvailable( d_adjoint_photonuclear_data_properties,
                                        file_type );
}

// Check if there is adjoint photonuclear data with the desired format and version
bool NuclideProperties::adjointPhotonuclearDataAvailable(
                   const AdjointPhotonuclearDataProperties::FileType file_type,
                   const unsigned table_version ) const
{
  return AtomProperties::dataAvailable( d_adjoint_photonuclear_data_properties,
                                        file_type,
                                        table_version );
}

// Get the adjoint photonuclear data file types
std::set<AdjointPhotonuclearDataProperties::FileType> NuclideProperties::getAdjointPhotonuclearDataFileTypes() const
{
  return AtomProperties::getDataFileTypes( d_adjoint_photonuclear_data_properties );
}

// Get the adjoint photonuclear data file versions
std::set<unsigned> NuclideProperties::getDataFileVersions(
            const AdjointPhotonuclearDataProperties::FileType file_type ) const
{
  return AtomProperties::getDataFileVersions(
                                        d_adjoint_photonuclear_data_properties,
                                        file_type );
}

// Get the recommended adjoint photonuclear data file version
unsigned NuclideProperties::getRecommendedDataFileVersion(
            const AdjointPhotonuclearDataProperties::FileType file_type ) const
{
  return AtomProperties::getMaxDataFileVersion(
                                        d_adjoint_photonuclear_data_properties,
                                        file_type,
                                        "Adjoint photonuclear" );
}

// Get the adjoint photonuclear data properties
const AdjointPhotonuclearDataProperties& NuclideProperties::getAdjointPhotonuclearDataProperties(
                   const AdjointPhotonuclearDataProperties::FileType file_type,
                   const unsigned table_version ) const
{
  return AtomProperties::getProperties<AdjointPhotonuclearDataProperties>(
                                        d_adjoint_photonuclear_data_properties,
                                        file_type,
                                        table_version,
                                        "Adjoint photonuclear" );
}

// Set the photonuclear data properties
void NuclideProperties::setAdjointPhotonuclearDataProperties( const std::shared_ptr<const AdjointPhotonuclearDataProperties>& properties )
{
  AtomProperties::setProperties( d_adjoint_photonuclear_data_properties,
                                 properties,
                                 "Adjoint photonuclear" );
}

// Clone the properties
NuclideProperties* NuclideProperties::clone() const
{
  return new NuclideProperties( *this );
}

// Deep clone the properties
NuclideProperties* NuclideProperties::deepClone() const
{
  NuclideProperties* nuclide_properties_clone =
    new NuclideProperties( this->zaid(), this->atomicWeightRatio() );

  this->cloneStoredAtomProperties( *this, *nuclide_properties_clone );
  this->cloneStoredNuclideProperties( *this, *nuclide_properties_clone );

  return nuclide_properties_clone;
}

// Deep clone the nuclide properties only
/*! \details Only the nuclide properties will be cloned (the atom properties
 * will use the same pointers)
 */
NuclideProperties* NuclideProperties::partialDeepClone() const
{
  NuclideProperties* nuclide_properties_clone =
    new NuclideProperties( dynamic_cast<const AtomProperties&>( *this ) );

  this->cloneStoredNuclideProperties( *this, *nuclide_properties_clone );
  
  return nuclide_properties_clone;
}

// Clone the stored properties
void NuclideProperties::cloneStoredNuclideProperties(
                                  const NuclideProperties& original_properties,
                                  NuclideProperties& new_properties )
{
  // Clone the nuclear data properties
  NuclideProperties::cloneNuclearProperties(
                                 original_properties.d_nuclear_data_properties,
                                 new_properties.d_nuclear_data_properties );

  // Clone the thermal nuclear data properties
  NuclideProperties::cloneThermalNuclearProperties(
                         original_properties.d_thermal_nuclear_data_properties,
                         new_properties.d_thermal_nuclear_data_properties );

  // Clone the adjoint nuclear data properties
  NuclideProperties::cloneNuclearProperties(
                         original_properties.d_adjoint_nuclear_data_properties,
                         new_properties.d_adjoint_nuclear_data_properties );

  // Clone the adjoint thermal nuclear data properties
  NuclideProperties::cloneThermalNuclearProperties(
                 original_properties.d_adjoint_thermal_nuclear_data_properties,
                 new_properties.d_adjoint_thermal_nuclear_data_properties );

  // Clone the photonuclear data properties
  AtomProperties::cloneProperties(
                            original_properties.d_photonuclear_data_properties,
                            new_properties.d_photonuclear_data_properties );

  // Clone the adjoint photonuclear data properties
  AtomProperties::cloneProperties(
                    original_properties.d_adjoint_photonuclear_data_properties,
                    new_properties.d_adjoint_photonuclear_data_properties );
}

// Place the object in an output stream
void NuclideProperties::toStream( std::ostream& os ) const
{
  // Print the atom properties
  AtomProperties::toStream( os );

  // Print the nuclear properties
  this->printNuclearProperties( d_nuclear_data_properties,
                                "Nuclear Data",
                                false,
                                os );

  // Print the thermal nuclear properties
  this->printThermalNuclearProperties( d_thermal_nuclear_data_properties,
                                       "Thermal Nuclear Data",
                                       os );

  // Print the adjoint nuclear properties
  this->printNuclearProperties( d_adjoint_nuclear_data_properties,
                                "Adjoint Nuclear Data",
                                false,
                                os );

  // Print the adjoint thermal nuclear properties
  this->printThermalNuclearProperties( d_thermal_nuclear_data_properties,
                                       "Adjoint Thermal Nuclear Data",
                                       os );

  // Print the photonuclear properties
  this->printProperties( d_photonuclear_data_properties,
                         "Photonuclear Data",
                         os );

  // Print the adjoint photonuclear properties
  this->printProperties( d_adjoint_photonuclear_data_properties,
                         "Adjoint Photonuclear Data",
                         os );

  os.flush();
}

EXPLICIT_DATA_CLASS_SAVE_LOAD_INST( NuclideProperties );
  
} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_NuclideProperties.cpp
//---------------------------------------------------------------------------//
