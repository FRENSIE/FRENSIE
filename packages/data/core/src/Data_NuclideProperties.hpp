//---------------------------------------------------------------------------//
//!
//! \file   Data_NuclideProperties.hpp
//! \author Alex Robinson
//! \brief  The nuclide properties class declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_NUCLIDE_PROPRETIES_HPP
#define DATA_NUCLIDE_PROPRETIES_HPP

// FRENSIE Includes
#include "Data_ScatteringCenterPropertiesHelper.hpp"
#include "Data_NuclearDataProperties.hpp"
#include "Data_ThermalNuclearDataProperties.hpp"
#include "Data_AdjointNuclearDataProperties.hpp"
#include "Data_AdjointThermalNuclearDataProperties.hpp"
#include "Data_PhotonuclearDataProperties.hpp"
#include "Data_AdjointPhotonuclearDataProperties.hpp"
#include "Data_ZAID.hpp"
#include "Utility_Vector.hpp"
#include "Utility_List.hpp"
#include "Utility_Map.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_OStreamableObject.hpp"

namespace Data{

//! The nuclide propreties base class
class NuclideProperties : public Utility::OStreamableObject,
                          private ScatteringCenterPropertiesHelper
{
  // The base type
  typedef ScatteringCenterPropertiesHelper BaseType;

public:

  //! The atomic mass unit
  typedef ScatteringCenterPropertiesHelper::AtomicMassUnit AtomicMassUnit;

  //! The atomic mass quantity
  typedef ScatteringCenterPropertiesHelper::AtomicWeight AtomicWeight;

  //! The energy unit
  typedef NuclearDataProperties::EnergyUnit EnergyUnit;

  //! The energy quantity
  typedef NuclearDataProperties::Energy Energy;

  //! The temperature unit
  typedef NuclearDataProperties::TemperatureUnit TemperatureUnit;

  //! The temperature quantity
  typedef NuclearDataProperties::Temperature Temperature;

  //! Constructor
  NuclideProperties( const Data::ZAID zaid,
                     const double atomic_weight_ratio );

  //! Constructor
  NuclideProperties( const Data::ZAID atom,
                     const AtomicWeight atomic_weight );

  //! Copy constructor
  NuclideProperties( const NuclideProperties& other );

  //! Destructor
  ~NuclideProperties()
  { /* ... */ }

  //! Check if there are no properties
  bool empty() const;

  //! Get the zaid
  const Data::ZAID& zaid() const;

  //! Get the atomic weight
  AtomicWeight atomicWeight() const;

  //! Get the atomic weight ratio (atomic weight/neutron weight)
  double atomicWeightRatio() const;

  //! Check if there is nuclear data with the desired format
  bool nuclearDataAvailable(
                       const NuclearDataProperties::FileType file_type ) const;

  //! Check if there is nuclear data with the desired format and version
  bool nuclearDataAvailable( const NuclearDataProperties::FileType file_type,
                             const unsigned table_major_version ) const;
  
  //! Check if there is nuclear data at the evaluation temp
  bool nuclearDataAvailable( const NuclearDataProperties::FileType file_type,
                             const unsigned table_major_version,
                             const Energy evaluation_temp ) const;

  //! Check if there is nuclear data at the evaluation temp
  bool nuclearDataAvailable( const NuclearDataProperties::FileType file_type,
                             const unsigned table_major_version,
                             const Temperature evaluation_temp ) const;

  //! Get the nuclear data file types
  std::set<NuclearDataProperties::FileType> getNuclearDataFileTypes() const;

  //! Get the nuclear data file versions
  std::set<unsigned> getDataFileVersions(
                       const NuclearDataProperties::FileType file_type ) const;

  //! Get the recommended nuclear data file major version (generally the newest version)
  unsigned getRecommendedDataFileVersion(
                       const NuclearDataProperties::FileType file_type ) const;

  //! Get the nuclear data evaluation temps
  std::vector<Energy> getDataEvaluationTempsInMeV(
                               const NuclearDataProperties::FileType file_type,
                               const unsigned table_major_version ) const;

  //! Get the nuclear data evaluation temps
  std::vector<Temperature> getDataEvaluationTemps(
                               const NuclearDataProperties::FileType file_type,
                               const unsigned table_major_version ) const;

  //! Get the nuclear data properties
  const NuclearDataProperties& getNuclearDataProperties(
                               const NuclearDataProperties::FileType file_type,
                               const unsigned table_major_version,
                               const Energy evaluation_temp,
                               const bool find_exact ) const;

  //! Get the shared nuclear data properties
  const std::shared_ptr<const NuclearDataProperties>&
  getSharedNuclearDataProperties(
                               const NuclearDataProperties::FileType file_type,
                               const unsigned table_major_version,
                               const Energy evaluation_temp,
                               const bool find_exact ) const;

  //! Get the nuclear data properties
  const NuclearDataProperties& getNuclearDataProperties(
                               const NuclearDataProperties::FileType file_type,
                               const unsigned table_major_version,
                               const Temperature evaluation_temp,
                               const bool find_exact ) const;

  //! Get the nuclear data properties
  const std::shared_ptr<const NuclearDataProperties>&
  getSharedNuclearDataProperties(
                               const NuclearDataProperties::FileType file_type,
                               const unsigned table_major_version,
                               const Temperature evaluation_temp,
                               const bool find_exact ) const;

  //! Set the nuclear data properties
  void setNuclearDataProperties( const std::shared_ptr<const NuclearDataProperties>& properties );

  //! Check if there is thermal nuclear data available
  bool thermalNuclearDataAvailable( const std::string& name ) const;

  //! Check if there is thermal nuclear data with the desired format
  bool thermalNuclearDataAvailable(
                const std::string& name,
                const ThermalNuclearDataProperties::FileType file_type ) const;

  //! Check if there is thermal nuclear data with the desired format
  bool thermalNuclearDataAvailable(
                        const std::string& name,
                        const ThermalNuclearDataProperties::FileType file_type,
                        const unsigned table_major_version ) const;

  //! Check if there is thermal nuclear data with the desired format
  bool thermalNuclearDataAvailable(
                        const std::string& name,
                        const ThermalNuclearDataProperties::FileType file_type,
                        const unsigned table_major_version,
                        const Energy evaluation_temp ) const;

  //! Check if there is thermal nuclear data with the desired format
  bool thermalNuclearDataAvailable(
                        const std::string& name,
                        const ThermalNuclearDataProperties::FileType file_type,
                        const unsigned table_major_version,
                        const Temperature evaluation_temp ) const;

  //! Get the thermal nuclear data names
  std::set<std::string> getThermalNuclearDataNames() const;

  //! Get the thermal nuclear data file types
  std::set<ThermalNuclearDataProperties::FileType> getThermalNuclearDataFileTypes( const std::string& name ) const;

  //! Get the thermal nuclear data file versions
  std::set<unsigned> getDataFileVersions(
                const std::string& name,
                const ThermalNuclearDataProperties::FileType file_type ) const;

  //! Get the recommended thermal nuclear data file major version (generally the newest version)
  unsigned getRecommendedDataFileVersion(
                const std::string& name,
                const ThermalNuclearDataProperties::FileType file_type ) const;

  //! Get the thermal nuclear data evaluation temps
  std::vector<Energy> getDataEvaluationTempsInMeV(
                        const std::string& name,
                        const ThermalNuclearDataProperties::FileType file_type,
                        const unsigned table_major_version ) const;

  //! Get the thermal nuclear data evaluation temps
  std::vector<Temperature> getDataEvaluationTemps(
                        const std::string& name,
                        const ThermalNuclearDataProperties::FileType file_type,
                        const unsigned table_major_version ) const;

  //! Get the thermal nuclear data properties
  const ThermalNuclearDataProperties& getThermalNuclearDataProperties(
                        const std::string& name,
                        const ThermalNuclearDataProperties::FileType file_type,
                        const unsigned table_major_version,
                        const Energy evaluation_temp,
                        const bool find_exact ) const;

  //! Get the thermal nuclear data properties
  const std::shared_ptr<const ThermalNuclearDataProperties>&
  getSharedThermalNuclearDataProperties(
                        const std::string& name,
                        const ThermalNuclearDataProperties::FileType file_type,
                        const unsigned table_major_version,
                        const Energy evaluation_temp,
                        const bool find_exact ) const;

  //! Get the thermal nuclear data properties
  const ThermalNuclearDataProperties& getThermalNuclearDataProperties(
                        const std::string& name,
                        const ThermalNuclearDataProperties::FileType file_type,
                        const unsigned table_major_version,
                        const Temperature evaluation_temp,
                        const bool find_exact ) const;

  //! Get the thermal nuclear data properties
  const std::shared_ptr<const ThermalNuclearDataProperties>&
  getSharedThermalNuclearDataProperties(
                        const std::string& name,
                        const ThermalNuclearDataProperties::FileType file_type,
                        const unsigned table_major_version,
                        const Temperature evaluation_temp,
                        const bool find_exact ) const;

  //! Set the thermal nuclear data properties
  void setThermalNuclearDataProperties( const std::shared_ptr<const ThermalNuclearDataProperties>& properties );

  //! Check if there is adjoint nuclear data with the desired format
  bool adjointNuclearDataAvailable(
                const AdjointNuclearDataProperties::FileType file_type ) const;

  //! Check if there is adjoint nuclear data with the desired format and version
  bool adjointNuclearDataAvailable(
                        const AdjointNuclearDataProperties::FileType file_type,
                        const unsigned table_major_version ) const;
  
  //! Check if there is adjoint nuclear data at the evaluation temp
  bool adjointNuclearDataAvailable(
                        const AdjointNuclearDataProperties::FileType file_type,
                        const unsigned table_major_version,
                        const Energy evaluation_temp ) const;

  //! Check if there is adjoint nuclear data at the desired evaluation temp
  bool adjointNuclearDataAvailable(
                        const AdjointNuclearDataProperties::FileType file_type,
                        const unsigned table_major_version,
                        const Temperature evaluation_temp ) const;

  //! Get the adjoint nuclear data file types
  std::set<AdjointNuclearDataProperties::FileType> getAdjointNuclearDataFileTypes() const;

  //! Get the adjoint nuclear data file versions
  std::set<unsigned> getDataFileVersions(
                const AdjointNuclearDataProperties::FileType file_type ) const;

  //! Get the recommended adjoint nuclear data file major version (generally the newest version)
  unsigned getRecommendedDataFileVersion(
                const AdjointNuclearDataProperties::FileType file_type ) const;

  //! Get the adjoint nuclear data evaluation temps
  std::vector<Energy> getDataEvaluationTempsInMeV(
                        const AdjointNuclearDataProperties::FileType file_type,
                        const unsigned table_major_version ) const;

  //! Get the adjoint nuclear data evaluation temps
  std::vector<Temperature> getDataEvaluationTemps(
                        const AdjointNuclearDataProperties::FileType file_type,
                        const unsigned table_major_version ) const;

  //! Get the adjoint nuclear data properties
  const AdjointNuclearDataProperties& getAdjointNuclearDataProperties(
                        const AdjointNuclearDataProperties::FileType file_type,
                        const unsigned table_major_version,
                        const Energy evaluation_temp,
                        const bool find_exact ) const;

  //! Get the shared adjoint nuclear data properties
  const std::shared_ptr<const AdjointNuclearDataProperties>&
  getSharedAdjointNuclearDataProperties(
                        const AdjointNuclearDataProperties::FileType file_type,
                        const unsigned table_major_version,
                        const Energy evaluation_temp,
                        const bool find_exact ) const;

  //! Get the adjoint nuclear data properties
  const AdjointNuclearDataProperties& getAdjointNuclearDataProperties(
                        const AdjointNuclearDataProperties::FileType file_type,
                        const unsigned table_major_version,
                        const Temperature evaluation_temp,
                        const bool find_exact ) const;

  //! Get the shared adjoint nuclear data properties
  const std::shared_ptr<const AdjointNuclearDataProperties>&
  getSharedAdjointNuclearDataProperties(
                        const AdjointNuclearDataProperties::FileType file_type,
                        const unsigned table_major_version,
                        const Temperature evaluation_temp,
                        const bool find_exact ) const;

  //! Set the nuclear data properties
  void setAdjointNuclearDataProperties( const std::shared_ptr<const AdjointNuclearDataProperties>& properties );
  
  //! Check if there is thermal nuclear data available
  bool adjointThermalNuclearDataAvailable( const std::string& name ) const;

  //! Check if there is adjoint thermal nuclear data with the desired format
  bool adjointThermalNuclearDataAvailable(
     const std::string& name,
     const AdjointThermalNuclearDataProperties::FileType file_type ) const;

  //! Check if there is adjoint thermal nuclear data with the desired format
  bool adjointThermalNuclearDataAvailable(
                 const std::string& name,
                 const AdjointThermalNuclearDataProperties::FileType file_type,
                 const unsigned table_major_version ) const;

  //! Check if there is adjoint thermal nuclear data with the desired format
  bool adjointThermalNuclearDataAvailable(
                 const std::string& name,
                 const AdjointThermalNuclearDataProperties::FileType file_type,
                 const unsigned table_major_version,
                 const Energy evaluation_temp ) const;

  //! Check if there is adjoint thermal nuclear data with the desired format
  bool adjointThermalNuclearDataAvailable(
                 const std::string& name,
                 const AdjointThermalNuclearDataProperties::FileType file_type,
                 const unsigned table_major_version,
                 const Temperature evaluation_temp ) const;

  //! Get the adjoint thermal nuclear data names
  std::set<std::string> getAdjointThermalNuclearDataNames() const;

  //! Get the adjoint thermal nuclear data file types
  std::set<AdjointThermalNuclearDataProperties::FileType> getAdjointThermalNuclearDataFileTypes( const std::string& name ) const;

  //! Get the adjoint thermal nuclear data file versions
  std::set<unsigned> getDataFileVersions(
         const std::string& name,
         const AdjointThermalNuclearDataProperties::FileType file_type ) const;

  //! Get the recommended adjoint thermal nuclear data file major version (generally the newest version)
  unsigned getRecommendedDataFileVersion(
         const std::string& name,
         const AdjointThermalNuclearDataProperties::FileType file_type ) const;

  //! Get the adjoint thermal nuclear data evaluation temps
  std::vector<Energy> getDataEvaluationTempsInMeV(
                 const std::string& name,
                 const AdjointThermalNuclearDataProperties::FileType file_type,
                 const unsigned table_major_version ) const;

  //! Get the adjoint thermal nuclear data evaluation temps
  std::vector<Temperature> getDataEvaluationTemps(
                 const std::string& name,
                 const AdjointThermalNuclearDataProperties::FileType file_type,
                 const unsigned table_major_version ) const;

  //! Get the adjoint thermal nuclear data properties
  const AdjointThermalNuclearDataProperties& getAdjointThermalNuclearDataProperties(
                 const std::string& name,
                 const AdjointThermalNuclearDataProperties::FileType file_type,
                 const unsigned table_major_version,
                 const Energy evaluation_temp,
                 const bool find_exact ) const;

  //! Get the shared adjoint thermal nuclear data properties
  const std::shared_ptr<const AdjointThermalNuclearDataProperties>&
  getSharedAdjointThermalNuclearDataProperties(
                 const std::string& name,
                 const AdjointThermalNuclearDataProperties::FileType file_type,
                 const unsigned table_major_version,
                 const Energy evaluation_temp,
                 const bool find_exact ) const;

  //! Get the adjoint thermal nuclear data properties
  const AdjointThermalNuclearDataProperties& getAdjointThermalNuclearDataProperties(
                 const std::string& name,
                 const AdjointThermalNuclearDataProperties::FileType file_type,
                 const unsigned table_major_version,
                 const Temperature evaluation_temp,
                 const bool find_exact ) const;

  //! Get the shared adjoint thermal nuclear data properties
  const std::shared_ptr<const AdjointThermalNuclearDataProperties>&
  getSharedAdjointThermalNuclearDataProperties(
                 const std::string& name,
                 const AdjointThermalNuclearDataProperties::FileType file_type,
                 const unsigned table_major_version,
                 const Temperature evaluation_temp,
                 const bool find_exact ) const;

  //! Set the nuclear data properties
  void setAdjointThermalNuclearDataProperties( const std::shared_ptr<const AdjointThermalNuclearDataProperties>& properties );

  //! Check if there is photonuclear data with the desired format
  bool photonuclearDataAvailable(
                  const PhotonuclearDataProperties::FileType file_type ) const;

  //! Check if there is photonuclear data with the desired format and version
  bool photonuclearDataAvailable(
                          const PhotonuclearDataProperties::FileType file_type,
                          const unsigned table_version ) const;

  //! Get the photonuclear data file types
  std::set<PhotonuclearDataProperties::FileType> getPhotonuclearDataFileTypes() const;

  //! Get the photonuclear data file versions
  std::set<unsigned> getDataFileVersions(
                  const PhotonuclearDataProperties::FileType file_type ) const;

  //! Get the recommended photonuclear data file version
  unsigned getRecommendedDataFileVersion(
                  const PhotonuclearDataProperties::FileType file_type ) const;

  //! Get the photonuclear data properties
  const PhotonuclearDataProperties& getPhotonuclearDataProperties(
                          const PhotonuclearDataProperties::FileType file_type,
                          const unsigned table_version ) const;

  //! Get the shared photonuclear data properties
  const std::shared_ptr<const PhotonuclearDataProperties>&
  getSharedPhotonuclearDataProperties(
                          const PhotonuclearDataProperties::FileType file_type,
                          const unsigned table_version ) const;

  //! Set the photonuclear data properties
  void setPhotonuclearDataProperties( const std::shared_ptr<const PhotonuclearDataProperties>& properties );

  //! Check if there is adjoint photonuclear data with the desired format
  bool adjointPhotonuclearDataAvailable(
           const AdjointPhotonuclearDataProperties::FileType file_type ) const;

  //! Check if there is adjoint photonuclear data with the desired format and version
  bool adjointPhotonuclearDataAvailable(
                   const AdjointPhotonuclearDataProperties::FileType file_type,
                   const unsigned table_version ) const;

  //! Get the adjoint photonuclear data file types
  std::set<AdjointPhotonuclearDataProperties::FileType> getAdjointPhotonuclearDataFileTypes() const;

  //! Get the adjoint photonuclear data file versions
  std::set<unsigned> getDataFileVersions(
           const AdjointPhotonuclearDataProperties::FileType file_type ) const;

  //! Get the recommended adjoint photonuclear data file version
  unsigned getRecommendedDataFileVersion(
           const AdjointPhotonuclearDataProperties::FileType file_type ) const;

  //! Get the adjoint photonuclear data properties
  const AdjointPhotonuclearDataProperties& getAdjointPhotonuclearDataProperties(
                   const AdjointPhotonuclearDataProperties::FileType file_type,
                   const unsigned table_version ) const;

  //! Get the shared adjoint photonuclear data properties
  const std::shared_ptr<const AdjointPhotonuclearDataProperties>&
  getSharedAdjointPhotonuclearDataProperties(
                   const AdjointPhotonuclearDataProperties::FileType file_type,
                   const unsigned table_version ) const;

  //! Set the adjoint photonuclear data properties
  void setAdjointPhotonuclearDataProperties( const std::shared_ptr<const AdjointPhotonuclearDataProperties>& properties );

  //! Place the object in an output stream
  void toStream( std::ostream& os ) const override;

private:

  // Default constructor
  NuclideProperties();

  // Check if there is data available with the desired format, table version, and evaluation temp
  template<typename PropertiesMap>
  static bool dataAvailable( const PropertiesMap& properties,
                             const typename PropertiesMap::key_type file_type,
                             const unsigned table_version,
                             const Energy evaluation_temp );

  // Check if there is data available with the desired format, table version, and evaluation temp key
  template<typename PropertiesMap>
  static bool dataAvailable( const PropertiesMap& properties,
                             const typename PropertiesMap::key_type file_type,
                             const unsigned table_version,
                             const Temperature evaluation_temp );

  
  // Check if there is data available with the desired format, table version, and evaluation temp comparison function
  template<typename PropertiesMap, typename EvaluationTempCompFunc>
  static bool dataAvailableImpl( const PropertiesMap& properties,
                                 const typename PropertiesMap::key_type file_type,
                                 const unsigned table_version,
                                 const EvaluationTempCompFunc temp_comp_func );

  // Check if there is data available with the desired format
  template<typename PropertiesMap>
  static bool dataAvailable( const PropertiesMap& properties,
                             const std::string& name );

  // Check if there is data available with the desired name and format
  template<typename PropertiesMap>
  static bool dataAvailable( const PropertiesMap& properties,
                             const std::string& name,
                             const typename PropertiesMap::mapped_type::key_type file_type );

  // Check if there is data available with the desired name, format and table version
  template<typename PropertiesMap>
  static bool dataAvailable( const PropertiesMap& properties,
                             const std::string& name,
                             const typename PropertiesMap::mapped_type::key_type file_type,
                             const unsigned table_version );

  // Check if there is data available with the desired name, format and table version, and evaluation temp
  template<typename PropertiesMap>
  static bool dataAvailable( const PropertiesMap& properties,
                             const std::string& name,
                             const typename PropertiesMap::mapped_type::key_type file_type,
                             const unsigned table_version,
                             const Energy evaluation_temp );

  // Check if there is data available with the desired name, format and table version, and evaluation temp key
  template<typename PropertiesMap>
  static bool dataAvailable( const PropertiesMap& properties,
                             const std::string& name,
                             const typename PropertiesMap::mapped_type::key_type file_type,
                             const unsigned table_version,
                             const Temperature evaluation_temp );

  // Get the max data file version
  template<typename PropertiesMap>
  static unsigned getMaxDataFileVersion(
                 const PropertiesMap& properties,
                 const std::string& name,
                 const typename PropertiesMap::mapped_type::key_type file_type,
                 const std::string& type_name );

  // Get the data file types
  template<typename PropertiesMap>
  static std::set<typename PropertiesMap::mapped_type::key_type>
  getDataFileTypes( const PropertiesMap& properties,
                    const std::string& name );

  // Get the data file versions
  template<typename PropertiesMap>
  static std::set<unsigned> getDataFileVersions(
               const PropertiesMap& properties,
               const std::string& name,
               const typename PropertiesMap::mapped_type::key_type file_type );

  // Get the data file names
  template<typename PropertiesMap>
  static std::set<std::string> getThermalNuclearDataNames(
                                             const PropertiesMap& properties );

  // Get the data evaluation temps
  template<typename PropertiesMap>
  static std::vector<Energy> getDataEvaluationTempsInMeV(
                              const PropertiesMap& properties,
                              const typename PropertiesMap::key_type file_type,
                              const unsigned table_version );

  // Get the data evaluation temps
  template<typename PropertiesMap>
  static std::vector<Energy> getDataEvaluationTempsInMeV(
                 const PropertiesMap& properties,
                 const std::string& name,
                 const typename PropertiesMap::mapped_type::key_type file_type,
                 const unsigned table_version );

  // Get the data evaluation temps
  template<typename PropertiesMap>
  static std::vector<Temperature> getDataEvaluationTemps(
                              const PropertiesMap& properties,
                              const typename PropertiesMap::key_type file_type,
                              const unsigned table_version );

  // Get the data evaluation temps
  template<typename PropertiesMap>
  static std::vector<Temperature> getDataEvaluationTemps(
                 const PropertiesMap& properties,
                 const std::string& name,
                 const typename PropertiesMap::mapped_type::key_type file_type,
                 const unsigned table_version );

  // Get the data properties
  template<typename Properties, typename PropertiesMap>
  static const Properties& getProperties(
                              const PropertiesMap& properties,
                              const typename PropertiesMap::key_type file_type,
                              const unsigned table_version,
                              const Energy evaluation_temp,
                              const bool find_exact,
                              const std::string& type_name );

  // Get the shared data properties
  template<typename Properties, typename PropertiesMap>
  static const std::shared_ptr<const Properties>& getSharedProperties(
                              const PropertiesMap& properties,
                              const typename PropertiesMap::key_type file_type,
                              const unsigned table_version,
                              const Energy evaluation_temp,
                              const bool find_exact,
                              const std::string& type_name );

  // Get the data properties
  template<typename Properties, typename PropertiesMap>
  static const Properties& getProperties(
                              const PropertiesMap& properties,
                              const typename PropertiesMap::key_type file_type,
                              const unsigned table_version,
                              const Temperature evaluation_temp,
                              const bool find_exact,
                              const std::string& type_name );

  // Get the data properties
  template<typename Properties, typename PropertiesMap>
  static const std::shared_ptr<const Properties>& getSharedProperties(
                              const PropertiesMap& properties,
                              const typename PropertiesMap::key_type file_type,
                              const unsigned table_version,
                              const Temperature evaluation_temp,
                              const bool find_exact,
                              const std::string& type_name );

  // Get the data properties
  template<typename Properties, typename PropertiesMap>
  static const Properties& getProperties(
                 const PropertiesMap& properties,
                 const std::string& name,
                 const typename PropertiesMap::mapped_type::key_type file_type,
                 const unsigned table_version,
                 const Energy evaluation_temp,
                 const bool find_exact,
                 const std::string& type_name );

  // Get the shared data properties
  template<typename Properties, typename PropertiesMap>
  static const std::shared_ptr<const Properties>& getSharedProperties(
                 const PropertiesMap& properties,
                 const std::string& name,
                 const typename PropertiesMap::mapped_type::key_type file_type,
                 const unsigned table_version,
                 const Energy evaluation_temp,
                 const bool find_exact,
                 const std::string& type_name );

  // Get the data properties
  template<typename Properties, typename PropertiesMap>
  static const Properties& getProperties(
                 const PropertiesMap& properties,
                 const std::string& name,
                 const typename PropertiesMap::mapped_type::key_type file_type,
                 const unsigned table_version,
                 const Temperature evaluation_temp,
                 const bool find_exact,
                 const std::string& type_name );

  // Get the data properties
  template<typename Properties, typename PropertiesMap>
  static const std::shared_ptr<const Properties>& getSharedProperties(
                 const PropertiesMap& properties,
                 const std::string& name,
                 const typename PropertiesMap::mapped_type::key_type file_type,
                 const unsigned table_version,
                 const Temperature evaluation_temp,
                 const bool find_exact,
                 const std::string& type_name );

  // Set the nuclear properties
  template<typename Properties, typename PropertiesMap>
  static void setNuclearPropertiesImpl(
                       PropertiesMap& properties,
                       const std::shared_ptr<const Properties>& new_properties,
                       const Data::ZAID& nuclide_zaid,
                       const std::string& type_name );

  // Set the nuclear properties
  template<typename Properties, typename PropertiesMap>
  static void setNuclearProperties(
                       PropertiesMap& properties,
                       const std::shared_ptr<const Properties>& new_properties,
                       const Data::ZAID& expected_zaid,
                       const std::string& type_name );

  // Set the thermal nuclear properties
  template<typename Properties, typename PropertiesMap>
  static void setThermalNuclearProperties(
                       PropertiesMap& properties,
                       const std::shared_ptr<const Properties>& new_properties,
                       const Data::ZAID& expected_zaid,
                       const std::string& type_name );

  // Set the photonuclear properties
  template<typename Properties, typename PropertiesMap>
  static void setPhotonuclearProperties(
                       PropertiesMap& properties,
                       const std::shared_ptr<const Properties>& new_properties,
                       const ZAID& expected_zaid,
                       const std::string& warning_tag,
                       const std::string& type_name );

  // Print nuclear properties
  template<typename PropertiesMap>
  static void printNuclearProperties( const PropertiesMap& properties,
                                      const std::string& type_name,
                                      const bool extra_indent,
                                      std::ostream& os );

  // Print thermal nuclear properties
  template<typename PropertiesMap>
  static void printThermalNuclearProperties( const PropertiesMap& properties,
                                             const std::string& type_name,
                                             std::ostream& os );

  // Save the properties to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the properties from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The nuclear properties map type helper class
  template<typename Properties>
  struct NuclearPropertiesMapTypeHelper
  {
    // The properties grid type
    typedef std::list<std::pair<Energy,std::shared_ptr<const Properties> > > PropertiesGrid;

    // The version properties grid map type
    typedef std::map<unsigned,PropertiesGrid> VersionPropertiesGridMap;

    // The file type version properties grid map type
    typedef std::map<typename Properties::FileType,VersionPropertiesGridMap> FileTypeVersionPropertiesGridMap;
  };

  // The named nuclear properties map type helper class
  template<typename Properties>
  struct NamedNuclearPropertiesMapTypeHelper : public NuclearPropertiesMapTypeHelper<Properties>
  {
    typedef std::map<std::string, typename NuclearPropertiesMapTypeHelper<Properties>::FileTypeVersionPropertiesGridMap> NameFileTypeVersionPropertiesGridMap;
  };

  // The energy comparison tolerance
  static double s_energy_comp_tol;

  // The zaid
  Data::ZAID d_zaid;

  // The atomic weight ratio
  double d_atomic_weight_ratio;

  // The nuclear data properties
  typename NuclearPropertiesMapTypeHelper<NuclearDataProperties>::FileTypeVersionPropertiesGridMap d_nuclear_data_properties;

  // The thermal nuclear data properties
  typename NamedNuclearPropertiesMapTypeHelper<ThermalNuclearDataProperties>::NameFileTypeVersionPropertiesGridMap d_thermal_nuclear_data_properties;

  // The adjoint nuclear data properties
  typename NuclearPropertiesMapTypeHelper<AdjointNuclearDataProperties>::FileTypeVersionPropertiesGridMap d_adjoint_nuclear_data_properties;

  // The adjoint thermal nuclear data properties
  typename NamedNuclearPropertiesMapTypeHelper<AdjointThermalNuclearDataProperties>::NameFileTypeVersionPropertiesGridMap d_adjoint_thermal_nuclear_data_properties;
  
  // The photonuclear data properties
  typename PropertiesMapTypeHelper<PhotonuclearDataProperties>::FileTypeVersionPropertiesMap d_photonuclear_data_properties;

  // The adjoint photonuclear data properties
  typename PropertiesMapTypeHelper<AdjointPhotonuclearDataProperties>::FileTypeVersionPropertiesMap d_adjoint_photonuclear_data_properties;
};
  
} // end Data namespace

BOOST_SERIALIZATION_CLASS_VERSION( NuclideProperties, Data, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( NuclideProperties, Data );

EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Data, NuclideProperties );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Data_NuclideProperties_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_NUCLIDE_PROPRETIES_HPP

//---------------------------------------------------------------------------//
// end Data_NuclideProperties.hpp
//---------------------------------------------------------------------------//
