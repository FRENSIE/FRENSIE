//---------------------------------------------------------------------------//
//!
//! \file   Data_AtomProperties.hpp
//! \author Alex Robinson
//! \brief  The atom properties class declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ATOM_PROPRETIES_HPP
#define DATA_ATOM_PROPRETIES_HPP

// FRENSIE Includes
#include "Data_ZAID.hpp"
#include "Data_PhotoatomicDataProperties.hpp"
#include "Data_AdjointPhotoatomicDataProperties.hpp"
#include "Data_ElectroatomicDataProperties.hpp"
#include "Data_AdjointElectroatomicDataProperties.hpp"
#include "Data_PhotonuclearDataProperties.hpp"
#include "Utility_Set.hpp"
#include "Utility_OStreamableObject.hpp"

namespace Data{

//! The atom propreties base class
class AtomProperties : public Utility::OStreamableObject
{

public:

  //! The atomic mass unit
  typedef PhotonuclearDataProperties::AtomicMassUnit AtomicMassUnit;

  //! The atomic mass quantity
  typedef PhotonuclearDataProperties::AtomicWeight AtomicWeight;

  //! Constructor
  AtomProperties( const Data::ZAID zaid,
                  const double atomic_weight_ratio );

  //! Constructor
  AtomProperties( const Data::ZAID zaid,
                  const AtomicWeight atomic_weight );

  //! Destructor
  virtual ~AtomProperties()
  { /* ... */ }

  //! Check if the scattering center is a nuclide
  virtual bool isNuclide() const;

  //! Get the zaid
  const Data::ZAID& zaid() const;

  //! Get the atomic weight
  AtomicWeight atomicWeight() const;

  //! Get the atomic weight ratio (atomic weight/neutron weight)
  double atomicWeightRatio() const;

  //! Check if there is photoatomic data with the desired format
  bool photoatomicDataAvailable(
                   const PhotoatomicDataProperties::FileType file_type ) const;

  //! Check if there is photoatomic data with the desired format and version
  bool photoatomicDataAvailable(
                           const PhotoatomicDataProperties::FileType file_type,
                           const unsigned table_version ) const;

  //! Get the photoatomic data file types
  std::set<PhotoatomicDataProperties::FileType>
  getPhotoatomicDataFileTypes() const;

  //! Get the photoatomic data file versions
  std::set<unsigned> getDataFileVersions(
                   const PhotoatomicDataProperties::FileType file_type ) const;

  //! Get the recommended photoatomic data file version
  unsigned getRecommendedDataFileVersion(
                   const PhotoatomicDataProperties::FileType file_type ) const;

  //! Get the photoatomic data properties
  const PhotoatomicDataProperties& getPhotoatomicDataProperties(
                           const PhotoatomicDataProperties::FileType file_type,
                           const unsigned table_version ) const;

  //! Set the photoatomic data
  void setPhotoatomicDataProperties( const std::shared_ptr<const PhotoatomicDataProperties>& properties );

  //! Check if there is adjoint photoatomic data with the desired format
  bool adjointPhotoatomicDataAvailable(
            const AdjointPhotoatomicDataProperties::FileType file_type ) const;

  //! Check if there is adjoint photoatomic data with the desired format and version
  bool adjointPhotoatomicataAvailable(
                    const AdjointPhotoatomicDataProperties::FileType file_type,
                    const unsigned table_version ) const;

  //! Get the adjoint photoatomic data file types
  std::set<AdjointPhotoatomicDataProperties::FileType>
  getAdjointPhotoatomicDataFileTypes() const;

  //! Get the adjoint photoatomic data file versions
  std::set<unsigned> getDataFileVersions(
            const AdjointPhotoatomicDataProperties::FileType file_type ) const;

  //! Get the recommended adjoint photoatomic data file version
  unsigned getRecommendedDataFileVersion(
            const AdjointPhotoatomicDataProperties::FileType file_type ) const;

  //! Get the adjoint photoatomic data properties
  const AdjointPhotoatomicDataProperties& getAdjointPhotoatomicDataProperties(
                    const AdjointPhotoatomicDataProperties::FileType file_type,
                    const unsigned table_version ) const;

  //! Set the adjoint photoatomic data properties
  void setAdjointPhotoatomicDataProperties( const std::shared_ptr<const AdjointPhotoatomicDataProperties>& properties );

  //! Check if there is electroatomic data with the desired format
  bool electroatomicDataAvailable(
                 const ElectroatomicDataProperties::FileType file_type ) const;

  //! Check if there is electroatomic data with the desired format and version
  bool electroatomicDataAvailable(
                         const ElectroatomicDataProperties::FileType file_type,
                         const unsigned table_version ) const;

  //! Get the electroatomic data file types
  std::set<ElectroatomicDataProperties::FileType>
  getElectroatomicDataFileTypes() const;

  //! Get the electroatomic data file versions
  std::set<unsigned> getDataFileVersions(
                 const ElectroatomicDataProperties::FileType file_type ) const;

  //! Get the recommended electroatomic data file version
  unsigned getRecommendedDataFileVersion(
                 const ElectroatomicDataProperties::FileType file_type ) const;

  //! Get the electroatomic data properties
  const ElectroatomicDataProperties& getElectroatomicDataProperties(
                         const ElectroatomicDataProperties::FileType file_type,
                         const unsigned table_version ) const;

  //! Set the electroatomic data properties
  void setElectroatomicDataProperties( const std::shared_ptr<const ElectroatomicDataProperties>& properties );

  //! Check if there is adjoint electroatomic data with the desired format
  bool adjointElectroatomicDataAvailable(
          const AdjointElectroatomicDataProperties::FileType file_type ) const;

  //! Check if there is adjoint electroatomic data with the desired format and version
  bool adjointElectroatomicataAvailable(
                  const AdjointElectroatomicDataProperties::FileType file_type,
                  const unsigned table_version ) const;

  //! Get the adjoint electroatomic data file types
  std::set<AdjointElectroatomicDataProperties::FileType> getAdjointElectroatomicDataFileTypes() const;

  //! Get the adjoint electroatomic data file versions
  std::set<unsigned> getDataFileVersions(
          const AdjointElectroatomicDataProperties::FileType file_type ) const;

  //! Get the recommended adjoint electroatomic data file version
  unsigned getRecommendedDataFileVersion(
          const AdjointElectroatomicDataProperties::FileType file_type ) const;

  //! Get the adjoint electroatomic data properties
  const AdjointElectroatomicDataProperties& getAdjointElectroatomicDataProperties(
                  const AdjointElectroatomicDataProperties::FileType file_type,
                  const unsigned table_version ) const;

  //! Set the adjoint electroatomic data properties
  void setAdjointElectroatomicDataProperties( const std::shared_ptr<const AdjointElectroatomicDataProperties>& properties );

  //! Clone the properties
  virtual AtomProperties* clone() const;

  //! Deep clone the properties
  virtual AtomProperties* deepClone() const;

  //! Place the object in an output stream
  virtual void toStream( std::ostream& os ) const override;

protected:

  //! The properties map type helper class
  template<typename Properties>
  struct PropertiesMapTypeHelper
  {
    //! The version properties map type
    typedef std::map<unsigned,std::shared_ptr<const Properties> > VersionPropertiesMap;

    //! The file type version properties map type
    typedef std::map<typename Properties::FileType,VersionPropertiesMap> FileTypeVersionPropertiesMap;
  };

  //! Default constructor
  AtomProperties();

  //! Copy constructor
  AtomProperties( const AtomProperties& other );

  //! Set the zaid
  void setZAID( const Data::ZAID zaid );

  //! Set the atomic weight ratio
  void setAtomicWeightRatio( const double atomic_weight_ratio );

  //! Check if there is data available with the desired format
  template<typename PropertiesMap>
  static bool dataAvailable( const PropertiesMap& properties,
                             const typename PropertiesMap::key_type file_type );

  //! Check if there is data available with the desired format and table version
  template<typename PropertiesMap>
  static bool dataAvailable( const PropertiesMap& properties,
                             const typename PropertiesMap::key_type file_type,
                             const unsigned table_version );

  //! Get the data file types
  template<typename PropertiesMap>
  static std::set<typename PropertiesMap::key_type> getDataFileTypes(
                                             const PropertiesMap& properties );

  //! Get the data file versions
  template<typename PropertiesMap>
  static std::set<unsigned> getDataFileVersions(
                            const PropertiesMap& properties,
                            const typename PropertiesMap::key_type file_type );

  //! Get the max data file version
  template<typename PropertiesMap>
  static unsigned getMaxDataFileVersion(
                            const PropertiesMap& properties,
                            const typename PropertiesMap::key_type file_type,
                            const std::string& type_name );

  //! Get the properties
  template<typename Properties, typename PropertiesMap>
  static const Properties& getProperties(
                              const PropertiesMap& properties,
                              const typename PropertiesMap::key_type file_type,
                              const unsigned table_version,
                              const std::string& type_name );

  //! Set the properties
  template<typename Properties, typename PropertiesMap>
  static void setProperties( PropertiesMap& properties,
                             const std::shared_ptr<const Properties>& new_properties,
                             const std::string& type_name );

  //! Clone the stored properties
  static void cloneStoredAtomProperties(
                                     const AtomProperties& original_properties,
                                     AtomProperties& new_properties );

  //! Clone properties
  template<typename PropertiesMap>
  static void cloneProperties( const PropertiesMap& original_properties,
                               PropertiesMap& new_properties );

  //! Print properties
  template<typename PropertiesMap>
  static void printProperties( const PropertiesMap& properties,
                               const std::string& type_name,
                               std::ostream& os );

private:

  // Save the properties to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the properties from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );
  
  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The zaid
  Data::ZAID d_zaid;

  // The atomic weight ratio
  double d_atomic_weight_ratio;

  // The photoatomic data properties
  typename PropertiesMapTypeHelper<PhotoatomicDataProperties>::FileTypeVersionPropertiesMap d_photoatomic_data_properties;

  // The adjoint photoatomic data properties
  typename PropertiesMapTypeHelper<AdjointPhotoatomicDataProperties>::FileTypeVersionPropertiesMap d_adjoint_photoatomic_data_properties;

  // The electroatomic data properties
  typename PropertiesMapTypeHelper<ElectroatomicDataProperties>::FileTypeVersionPropertiesMap d_electroatomic_data_properties;

  // The adjoint electroatomic data properties
  typename PropertiesMapTypeHelper<AdjointElectroatomicDataProperties>::FileTypeVersionPropertiesMap d_adjoint_electroatomic_data_properties;
};
  
} // end Data namespace

BOOST_SERIALIZATION_CLASS_VERSION( AtomProperties, Data, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( AtomProperties, Data );

EXTERN_EXPLICIT_DATA_CLASS_SAVE_LOAD_INST( AtomProperties );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Data_AtomProperties_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_ATOM_PROPRETIES_HPP

//---------------------------------------------------------------------------//
// end Data_AtomProperties.hpp
//---------------------------------------------------------------------------//
