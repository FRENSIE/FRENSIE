//---------------------------------------------------------------------------//
//!
//! \file   Data_NuclideProperties.cpp
//! \author Alex Robinson
//! \brief  The nuclide properties class definition
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/serialization/map.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/shared_ptr.hpp>

// FRENSIE Includes
#include "FRENSIE_Archives.hpp" // Must include first
#include "Data_NuclideProperties.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Data{

// Initialize static member data
double NuclideProperties::s_energy_comp_tol = 1e-9;

// Default constructor
NuclideProperties::NuclideProperties()
{ /* ... */ }

// Constructor
NuclideProperties::NuclideProperties( const Data::ZAID zaid,
                                      const double atomic_weight_ratio )
  : d_zaid( zaid ),
    d_atomic_weight_ratio( atomic_weight_ratio )
{
  TEST_FOR_EXCEPTION( atomic_weight_ratio <= 0.0,
                      InvalidScatteringCenterPropertiesData,
                      "The atomic weight ratio cannot be zero or negative!" );
}

// Tie constructor
NuclideProperties::NuclideProperties( const Data::ZAID zaid,
                                      const AtomicWeight atomic_weight )
  : NuclideProperties( zaid, atomic_weight/Utility::PhysicalConstants::neutron_rest_mass_amu_q )
{ /* ... */ }

// Copy constructor
NuclideProperties::NuclideProperties( const NuclideProperties& other )
  : d_zaid( other.d_zaid ),
    d_atomic_weight_ratio( other.d_atomic_weight_ratio ),
    d_nuclear_data_properties( other.d_nuclear_data_properties ),
    d_thermal_nuclear_data_properties( other.d_thermal_nuclear_data_properties ),
    d_adjoint_nuclear_data_properties( other.d_adjoint_nuclear_data_properties ),
    d_adjoint_thermal_nuclear_data_properties( other.d_adjoint_thermal_nuclear_data_properties ),
    d_photonuclear_data_properties( other.d_photonuclear_data_properties ),
    d_adjoint_photonuclear_data_properties( other.d_adjoint_photonuclear_data_properties )
{ /* ... */ }

// Check if there are no properties
/*! \details Nuclide properties are considered empty if there are no properties
 * stored for nuclear and photonuclear interaction types (there may be stored
 * atomic data).
 */
bool NuclideProperties::empty() const
{
  return d_nuclear_data_properties.empty() &&
    d_thermal_nuclear_data_properties.empty() &&
    d_adjoint_nuclear_data_properties.empty() &&
    d_adjoint_thermal_nuclear_data_properties.empty() &&
    d_photonuclear_data_properties.empty() &&
    d_adjoint_photonuclear_data_properties.empty();
}

// Get the zaid
const Data::ZAID& NuclideProperties::zaid() const
{
  return d_zaid;
}

// Get the atomic weight
auto NuclideProperties::atomicWeight() const -> AtomicWeight
{
  return d_atomic_weight_ratio*Utility::PhysicalConstants::neutron_rest_mass_amu_q;
}

// Get the atomic weight ratio (atomic weight/neutron weight)
double NuclideProperties::atomicWeightRatio() const
{
  return d_atomic_weight_ratio;
}

// Check if there is nuclear data with the desired format
bool NuclideProperties::nuclearDataAvailable(
                        const NuclearDataProperties::FileType file_type ) const
{
  return BaseType::dataAvailable( d_nuclear_data_properties, file_type );
}

// Check if there is nuclear data with the desired format and version
bool NuclideProperties::nuclearDataAvailable(
                               const NuclearDataProperties::FileType file_type,
                               const unsigned table_major_version ) const
{
  return BaseType::dataAvailable( d_nuclear_data_properties,
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
  return BaseType::getDataFileTypes( d_nuclear_data_properties );
}

// Get the nuclear data file versions
std::set<unsigned> NuclideProperties::getDataFileVersions(
                        const NuclearDataProperties::FileType file_type ) const
{
  return BaseType::getDataFileVersions( d_nuclear_data_properties,
                                        file_type );
}

// Get the recommended nuclear data file major version (generally the newest version)
unsigned NuclideProperties::getRecommendedDataFileVersion(
                        const NuclearDataProperties::FileType file_type ) const
{
  return BaseType::getMaxDataFileVersion( d_nuclear_data_properties,
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
const std::shared_ptr<const NuclearDataProperties>&
NuclideProperties::getSharedNuclearDataProperties(
                               const NuclearDataProperties::FileType file_type,
                               const unsigned table_major_version,
                               const Energy evaluation_temp,
                               const bool find_exact ) const
{
  return this->getSharedProperties<NuclearDataProperties>(
                                                     d_nuclear_data_properties,
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

// Get the nuclear data properties
const std::shared_ptr<const NuclearDataProperties>&
NuclideProperties::getSharedNuclearDataProperties(
                              const NuclearDataProperties::FileType file_type,
                              const unsigned table_major_version,
                              const Temperature evaluation_temp,
                              const bool find_exact ) const
{
  return this->getSharedProperties<NuclearDataProperties>(
                                                     d_nuclear_data_properties,
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
                              this->zaid(),
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
  return this->getMaxDataFileVersion( d_thermal_nuclear_data_properties,
                                      name,
                                      file_type,
                                      "Thermal nuclear" );
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
const std::shared_ptr<const ThermalNuclearDataProperties>&
NuclideProperties::getSharedThermalNuclearDataProperties(
                        const std::string& name,
                        const ThermalNuclearDataProperties::FileType file_type,
                        const unsigned table_major_version,
                        const Energy evaluation_temp,
                        const bool find_exact ) const
{
  return this->getSharedProperties<ThermalNuclearDataProperties>(
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

// Get the thermal nuclear data properties
const std::shared_ptr<const ThermalNuclearDataProperties>&
NuclideProperties::getSharedThermalNuclearDataProperties(
                        const std::string& name,
                        const ThermalNuclearDataProperties::FileType file_type,
                        const unsigned table_major_version,
                        const Temperature evaluation_temp,
                        const bool find_exact ) const
{
  return this->getSharedProperties<ThermalNuclearDataProperties>(
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
                                     this->zaid(),
                                     "Thermal nuclear" );
}

// Check if there is adjoint nuclear data with the desired format
bool NuclideProperties::adjointNuclearDataAvailable(
                 const AdjointNuclearDataProperties::FileType file_type ) const
{
  return BaseType::dataAvailable( d_adjoint_nuclear_data_properties,
                                  file_type );
}

// Check if there is adjoint nuclear data with the desired format and version
bool NuclideProperties::adjointNuclearDataAvailable(
                        const AdjointNuclearDataProperties::FileType file_type,
                        const unsigned table_major_version ) const
{
  return BaseType::dataAvailable( d_adjoint_nuclear_data_properties,
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
  return BaseType::getDataFileTypes( d_adjoint_nuclear_data_properties );
}

// Get the adjoint nuclear data file versions
std::set<unsigned> NuclideProperties::getDataFileVersions(
                 const AdjointNuclearDataProperties::FileType file_type ) const
{
  return BaseType::getDataFileVersions( d_adjoint_nuclear_data_properties,
                                        file_type );
}

// Get the recommended adjoint nuclear data file major version (generally the newest version)
unsigned NuclideProperties::getRecommendedDataFileVersion(
                 const AdjointNuclearDataProperties::FileType file_type ) const
{
  return BaseType::getMaxDataFileVersion( d_adjoint_nuclear_data_properties,
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

// Get the shared adjoint nuclear data properties
const std::shared_ptr<const AdjointNuclearDataProperties>&
NuclideProperties::getSharedAdjointNuclearDataProperties(
                        const AdjointNuclearDataProperties::FileType file_type,
                        const unsigned table_major_version,
                        const Energy evaluation_temp,
                        const bool find_exact ) const
{
  return this->getSharedProperties<AdjointNuclearDataProperties>(
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

// Get the shared adjoint nuclear data properties
const std::shared_ptr<const AdjointNuclearDataProperties>&
NuclideProperties::getSharedAdjointNuclearDataProperties(
                        const AdjointNuclearDataProperties::FileType file_type,
                        const unsigned table_major_version,
                        const Temperature evaluation_temp,
                        const bool find_exact ) const
{
  return this->getSharedProperties<AdjointNuclearDataProperties>(
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
                              this->zaid(),
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
std::set<AdjointThermalNuclearDataProperties::FileType> NuclideProperties::getAdjointThermalNuclearDataFileTypes( const std::string& name ) const
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

// Get the shared adjoint thermal nuclear data properties
const std::shared_ptr<const AdjointThermalNuclearDataProperties>&
NuclideProperties::getSharedAdjointThermalNuclearDataProperties(
                 const std::string& name,
                 const AdjointThermalNuclearDataProperties::FileType file_type,
                 const unsigned table_major_version,
                 const Energy evaluation_temp,
                 const bool find_exact ) const
{
  return this->getSharedProperties<AdjointThermalNuclearDataProperties>(
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

// Get the shared adjoint thermal nuclear data properties
const std::shared_ptr<const AdjointThermalNuclearDataProperties>&
NuclideProperties::getSharedAdjointThermalNuclearDataProperties(
                 const std::string& name,
                 const AdjointThermalNuclearDataProperties::FileType file_type,
                 const unsigned table_major_version,
                 const Temperature evaluation_temp,
                 const bool find_exact ) const
{
  return this->getSharedProperties<AdjointThermalNuclearDataProperties>(
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
                                     this->zaid(),
                                     "Adjoint thermal nuclear" );
}

// Check if there is photonuclear data with the desired format
bool NuclideProperties::photonuclearDataAvailable(
                   const PhotonuclearDataProperties::FileType file_type ) const
{
  return BaseType::dataAvailable( d_photonuclear_data_properties,
                                  file_type );
}

// Check if there is photonuclear data with the desired format and version
bool NuclideProperties::photonuclearDataAvailable(
                          const PhotonuclearDataProperties::FileType file_type,
                          const unsigned table_version ) const
{
  return BaseType::dataAvailable( d_photonuclear_data_properties,
                                  file_type,
                                  table_version );
}

// Get the photonuclear data file types
std::set<PhotonuclearDataProperties::FileType> NuclideProperties::getPhotonuclearDataFileTypes() const
{
  return BaseType::getDataFileTypes( d_photonuclear_data_properties );
}

// Get the photonuclear data file versions
std::set<unsigned> NuclideProperties::getDataFileVersions(
                   const PhotonuclearDataProperties::FileType file_type ) const
{
  return BaseType::getDataFileVersions( d_photonuclear_data_properties,
                                        file_type );
}

// Get the recommended photonuclear data file version
unsigned NuclideProperties::getRecommendedDataFileVersion(
                   const PhotonuclearDataProperties::FileType file_type ) const
{
  return BaseType::getMaxDataFileVersion( d_photonuclear_data_properties,
                                          file_type,
                                          "Photonuclear" );
}

// Get the photonuclear data properties
const PhotonuclearDataProperties& NuclideProperties::getPhotonuclearDataProperties(
                          const PhotonuclearDataProperties::FileType file_type,
                          const unsigned table_version ) const
{
  return BaseType::getProperties<PhotonuclearDataProperties>(
                                                d_photonuclear_data_properties,
                                                file_type,
                                                table_version,
                                                "Photonuclear" );
}

// Get the photonuclear data properties
const std::shared_ptr<const PhotonuclearDataProperties>&
NuclideProperties::getSharedPhotonuclearDataProperties(
                          const PhotonuclearDataProperties::FileType file_type,
                          const unsigned table_version ) const
{
  return BaseType::getSharedProperties<PhotonuclearDataProperties>(
                                                d_photonuclear_data_properties,
                                                file_type,
                                                table_version,
                                                "Photonuclear" );
}

// Set the photonuclear data properties
void NuclideProperties::setPhotonuclearDataProperties( const std::shared_ptr<const PhotonuclearDataProperties>& properties )
{
  this->setPhotonuclearProperties( d_photonuclear_data_properties,
                                   properties,
                                   this->zaid(),
                                   "NuclideProperties",
                                   "Photonuclear" );
}

// Check if there is adjoint photonuclear data with the desired format
bool NuclideProperties::adjointPhotonuclearDataAvailable(
            const AdjointPhotonuclearDataProperties::FileType file_type ) const
{
  return BaseType::dataAvailable( d_adjoint_photonuclear_data_properties,
                                  file_type );
}

// Check if there is adjoint photonuclear data with the desired format and version
bool NuclideProperties::adjointPhotonuclearDataAvailable(
                   const AdjointPhotonuclearDataProperties::FileType file_type,
                   const unsigned table_version ) const
{
  return BaseType::dataAvailable( d_adjoint_photonuclear_data_properties,
                                  file_type,
                                  table_version );
}

// Get the adjoint photonuclear data file types
std::set<AdjointPhotonuclearDataProperties::FileType> NuclideProperties::getAdjointPhotonuclearDataFileTypes() const
{
  return BaseType::getDataFileTypes( d_adjoint_photonuclear_data_properties );
}

// Get the adjoint photonuclear data file versions
std::set<unsigned> NuclideProperties::getDataFileVersions(
            const AdjointPhotonuclearDataProperties::FileType file_type ) const
{
  return BaseType::getDataFileVersions( d_adjoint_photonuclear_data_properties,
                                        file_type );
}

// Get the recommended adjoint photonuclear data file version
unsigned NuclideProperties::getRecommendedDataFileVersion(
            const AdjointPhotonuclearDataProperties::FileType file_type ) const
{
  return BaseType::getMaxDataFileVersion(
                                        d_adjoint_photonuclear_data_properties,
                                        file_type,
                                        "Adjoint photonuclear" );
}

// Get the adjoint photonuclear data properties
const AdjointPhotonuclearDataProperties& NuclideProperties::getAdjointPhotonuclearDataProperties(
                   const AdjointPhotonuclearDataProperties::FileType file_type,
                   const unsigned table_version ) const
{
  return BaseType::getProperties<AdjointPhotonuclearDataProperties>(
                                        d_adjoint_photonuclear_data_properties,
                                        file_type,
                                        table_version,
                                        "Adjoint photonuclear" );
}

// Get the shared adjoint photonuclear data properties
const std::shared_ptr<const AdjointPhotonuclearDataProperties>&
NuclideProperties::getSharedAdjointPhotonuclearDataProperties(
                   const AdjointPhotonuclearDataProperties::FileType file_type,
                   const unsigned table_version ) const
{
  return BaseType::getSharedProperties<AdjointPhotonuclearDataProperties>(
                                        d_adjoint_photonuclear_data_properties,
                                        file_type,
                                        table_version,
                                        "Adjoint photonuclear" );
}

// Set the photonuclear data properties
void NuclideProperties::setAdjointPhotonuclearDataProperties( const std::shared_ptr<const AdjointPhotonuclearDataProperties>& properties )
{
  this->setPhotonuclearProperties( d_adjoint_photonuclear_data_properties,
                                   properties,
                                   this->zaid(),
                                   "NuclideProperties",
                                   "Adjoint photonuclear" );
}

// Place the object in an output stream
void NuclideProperties::toStream( std::ostream& os ) const
{
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

EXPLICIT_CLASS_SAVE_LOAD_INST( NuclideProperties );
  
} // end Data namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( NuclideProperties, Data );

//---------------------------------------------------------------------------//
// end Data_NuclideProperties.cpp
//---------------------------------------------------------------------------//
