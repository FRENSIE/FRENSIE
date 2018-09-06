//---------------------------------------------------------------------------//
//!
//! \file   Data_AtomProperties.hpp
//! \author Alex Robinson
//! \brief  The atom properties class declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ATOM_PROPRETIES_HPP
#define DATA_ATOM_PROPRETIES_HPP

// Std Lib Includes
#include <stdexcept>

// FRENSIE Includes
#include "Data_ScatteringCenterPropertiesHelper.hpp"
#include "Data_PhotoatomicDataProperties.hpp"
#include "Data_AdjointPhotoatomicDataProperties.hpp"
#include "Data_ElectroatomicDataProperties.hpp"
#include "Data_AdjointElectroatomicDataProperties.hpp"
#include "Data_ZAID.hpp"
#include "Utility_Set.hpp"
#include "Utility_OStreamableObject.hpp"

namespace Data{

//! The atom propreties base class
class AtomProperties : public Utility::OStreamableObject,
                       private ScatteringCenterPropertiesHelper
{
  // The base type
  typedef ScatteringCenterPropertiesHelper BaseType;

public:

  //! The atomic mass unit
  typedef ScatteringCenterPropertiesHelper::AtomicMassUnit AtomicMassUnit;

  //! The atomic mass quantity
  typedef ScatteringCenterPropertiesHelper::AtomicWeight AtomicWeight;

  //! Constructor
  AtomProperties( const Data::AtomType atom,
                  const double atomic_weight_ratio );

  //! Constructor
  AtomProperties( const Data::AtomType atom,
                  const AtomicWeight atomic_weight );

  //! Copy constructor
  AtomProperties( const AtomProperties& other );

  //! Destructor
  ~AtomProperties()
  { /* ... */ }

  //! Check if there are no properties
  bool empty() const;

  //! Get the atom
  AtomType atom() const;

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

  //! Get the shared photoatomic data properties
  const std::shared_ptr<const PhotoatomicDataProperties>&
  getSharedPhotoatomicDataProperties(
                           const PhotoatomicDataProperties::FileType file_type,
                           const unsigned table_version ) const;

  //! Set the photoatomic data
  void setPhotoatomicDataProperties( const std::shared_ptr<const PhotoatomicDataProperties>& properties );

  //! Check if there is adjoint photoatomic data with the desired format
  bool adjointPhotoatomicDataAvailable(
            const AdjointPhotoatomicDataProperties::FileType file_type ) const;

  //! Check if there is adjoint photoatomic data with the desired format and version
  bool adjointPhotoatomicDataAvailable(
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

  //! Get the shared adjoint photoatomic data properties
  const std::shared_ptr<const AdjointPhotoatomicDataProperties>&
  getSharedAdjointPhotoatomicDataProperties(
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

  //! Get the shared electroatomic data properties
  const std::shared_ptr<const ElectroatomicDataProperties>&
  getSharedElectroatomicDataProperties(
                         const ElectroatomicDataProperties::FileType file_type,
                         const unsigned table_version ) const;

  //! Set the electroatomic data properties
  void setElectroatomicDataProperties( const std::shared_ptr<const ElectroatomicDataProperties>& properties );

  //! Check if there is adjoint electroatomic data with the desired format
  bool adjointElectroatomicDataAvailable(
          const AdjointElectroatomicDataProperties::FileType file_type ) const;

  //! Check if there is adjoint electroatomic data with the desired format and version
  bool adjointElectroatomicDataAvailable(
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

  //! Get the shared adjoint electroatomic data properties
  const std::shared_ptr<const AdjointElectroatomicDataProperties>&
  getSharedAdjointElectroatomicDataProperties(
                  const AdjointElectroatomicDataProperties::FileType file_type,
                  const unsigned table_version ) const;

  //! Set the adjoint electroatomic data properties
  void setAdjointElectroatomicDataProperties( const std::shared_ptr<const AdjointElectroatomicDataProperties>& properties );

  //! Place the object in an output stream
  void toStream( std::ostream& os ) const final override;

private:

  //! Default constructor
  AtomProperties();

  // Save the properties to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the properties from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The atom
  Data::AtomType d_atom;

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

// Save the properties to an archive
template<typename Archive>
void AtomProperties::save( Archive& ar, const unsigned version ) const
{
  // Save the local member data
  Data::ZAID zaid( d_atom );

  ar & BOOST_SERIALIZATION_NVP( zaid );
  ar & BOOST_SERIALIZATION_NVP( d_atomic_weight_ratio );
  ar & BOOST_SERIALIZATION_NVP( d_photoatomic_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_photoatomic_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_electroatomic_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_electroatomic_data_properties );
}

// Load the properties from an archive
template<typename Archive>
void AtomProperties::load( Archive& ar, const unsigned version )
{
  // Load the local member data
  Data::ZAID zaid;
  ar & BOOST_SERIALIZATION_NVP( zaid );

  d_atom = zaid.atom();

  ar & BOOST_SERIALIZATION_NVP( d_atomic_weight_ratio );
  ar & BOOST_SERIALIZATION_NVP( d_photoatomic_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_photoatomic_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_electroatomic_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_electroatomic_data_properties );
}

} // end Data namespace

BOOST_SERIALIZATION_CLASS_VERSION( AtomProperties, Data, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( AtomProperties, Data );

EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Data, AtomProperties );

#endif // end DATA_ATOM_PROPRETIES_HPP

//---------------------------------------------------------------------------//
// end Data_AtomProperties.hpp
//---------------------------------------------------------------------------//
