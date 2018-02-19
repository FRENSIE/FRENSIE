//---------------------------------------------------------------------------//
//!
//! \file   Data_AtomProperties.hpp
//! \author Alex Robinson
//! \brief  The atom properties class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Data{

// Default constructor
AtomProperties::AtomProperties()
{ /* ... */ }

// Constructor
AtomProperties::AtomProperties( const Data::ZAID zaid,
                                const double atomic_weight_ratio )
  : d_zaid( zaid ),
    d_atomic_weight_ratio( atomic_weight_ratio )
{
  TEST_FOR_EXCEPTION( atomic_weight_ratio <= 0.0,
                      std::runtime_error,
                      "The atomic weight ratio cannot be zero or negative!" );
}

// Constructor
AtomProperties::AtomProperties( const Data::ZAID zaid,
                                const AtomicWeight atomic_weight )
  : AtomProperties( zaid, atomic_weight/Utility::PhysicalConstants::neutron_rest_mass_amu_q )
{ /* ... */ }

// Copy constructor
AtomProperties::AtomProperties( const AtomProperties& other )
  : d_zaid( other.d_zaid ),
    d_atomic_weight_ratio( other.d_atomic_weight_ratio ),
    d_photoatomic_data_properties( other.d_photoatomic_data_properties ),
    d_adjoint_photoatomic_data_properties( other.d_adjoint_photoatomic_data_properties ),
    d_electroatomic_data_properties( other.d_electroatomic_data_properties ),
    d_adjoint_electroatomic_data_properties( other.d_adjoint_electroatomic_data_properties )
{ /* ... */ }

// Check if the scattering center is a nuclide
bool AtomProperties::isNuclide() const
{
  return false;
}

// Get the zaid
Data::ZAID AtomProperties::zaid() const
{
  return d_zaid;
}

// Get the atomic weight
auto AtomProperties::atomicWeight() const -> AtomicWeight
{
  return d_atomic_weight_ratio*Utility::PhysicalConstants::neutron_rest_mass_amu_q;
}

// Get the atomic weight ratio (atomic weight/neutron weight)
double AtomProperties::atomicWeightRatio() const
{
  return d_atomic_weight_ratio;
}

// Check if there is photoatomic data with the desired format
bool AtomProperties::photoatomicDataAvailable(
                    const PhotoatomicDataProperties::FileType file_type ) const
{
  return this->dataAvailable( d_photoatomic_data_properties, file_type );
}

// Check if there is photoatomic data with the desired format and version
bool AtomProperties::photoatomicDataAvailable(
                           const PhotoatomicDataProperties::FileType file_type,
                           const unsigned table_version ) const
{
  return this->dataAvailable( d_photoatomic_data_properties,
                              file_type,
                              table_version );
}

// Get the photoatomic data file types
std::set<PhotoatomicDataProperties::FileType>
AtomProperties::getPhotoatomicDataFileTypes() const
{
  return this->getDataFileTypes( d_photoatomic_data_properties );
}

// Get the photoatomic data file versions
std::set<unsigned> AtomProperties::getDataFileVersions(
                    const PhotoatomicDataProperties::FileType file_type ) const
{
  return this->getDataFileVersions( d_photoatomic_data_properties,
                                    file_type );
}

// Get the recommended photoatomic data file version
unsigned AtomProperties::getRecommendedDataFileVersion(
                    const PhotoatomicDataProperties::FileType file_type ) const
{
  switch( file_type )
  {
    case PhotoatomicDataProperties::ACE_FILE:
      return 4;
    case PhotoatomicDataProperties::ACE_EPR_FILE:
      return 12;
    case PhotoatomicDataProperties::Native_EPR_File:
      return 0;
    default:
      return 0;
  }
}

// Get the photoatomic data properties
const PhotoatomicDataProperties& AtomProperties::getPhotoatomicDataProperties(
                           const PhotoatomicDataProperties::FileType file_type,
                           const unsigned table_version ) const
{
  return this->getProperties<PhotoatomicDataProperties>(
                                                 d_photoatomic_data_properties,
                                                 file_type,
                                                 table_version,
                                                 "Photoatomic" );
}

// Set the photoatomic data
void AtomProperties::setPhotoatomicDataProperties( const std::shared_ptr<const PhotoatomicDataProperties>& properties )
{
  this->setProperties( d_photoatomic_data_properties,
                       properties,
                       "Photoatomic" );
}

// Check if there is adjoint photoatomic data with the desired format
bool AtomProperties::adjointPhotoatomicDataAvailable(
             const AdjointPhotoatomicDataProperties::FileType file_type ) const
{
  return this->dataAvailable( d_adjoint_photoatomic_data_properties,
                              file_type );
}

// Check if there is adjoint photoatomic data with the desired format and version
bool AtomProperties::adjointPhotoatomicataAvailable(
                    const AdjointPhotoatomicDataProperties::FileType file_type,
                    const unsigned table_version ) const
{
  return this->dataAvailable( d_adjoint_photoatomic_data_properties,
                              file_type,
                              table_version );
}

// Get the adjoint photoatomic data file types
std::set<AdjointPhotoatomicDataProperties::FileType>
AtomProperties::getAdjointPhotoatomicDataFileTypes() const
{
  return this->getDataFileTypes( d_adjoint_photoatomic_data_properties );
}

// Get the adjoint photoatomic data file versions
std::set<unsigned> AtomProperties::getDataFileVersions(
             const AdjointPhotoatomicDataProperties::FileType file_type ) const
{
  return this->getDataFileVersions( d_adjoint_photoatomic_data_properties,
                                    file_type );
}

// Get the recommended adjoint photoatomic data file version
unsigned AtomProperties::getRecommendedDataFileVersion(
             const AdjointPhotoatomicDataProperties::FileType file_type ) const
{
  return this->getMaxDataFileVersion( d_adjoint_photoatomic_data_properties,
                                      file_type );
}

// Get the adjoint photoatomic data properties
const AdjointPhotoatomicDataProperties& AtomProperties::getAdjointPhotoatomicDataProperties(
                    const AdjointPhotoatomicDataProperties::FileType file_type,
                    const unsigned table_version ) const
{
  return this->getProperties<AdjointPhotoatomicDataProperties>(
                                         d_adjoint_photoatomic_data_properties,
                                         file_type,
                                         table_version,
                                         "Adjoint photoatomic" );
}

// Set the adjoint photoatomic data properties
void AtomProperties::setAdjointPhotoatomicDataProperties( const std::shared_ptr<const AdjointPhotoatomicDataProperties>& properties )
{
  this->setProperties( d_adjoint_photoatomic_data_properties,
                       properties,
                       "Adjoint photoatomic" );
}

// Check if there is electroatomic data with the desired format
bool AtomProperties::electroatomicDataAvailable(
                  const ElectroatomicDataProperties::FileType file_type ) const
{
  return this->dataAvailable( d_electroatomic_data_properties, file_type );
}

// Check if there is electroatomic data with the desired format and version
bool AtomProperties::electroatomicDataAvailable(
                         const ElectroatomicDataProperties::FileType file_type,
                         const unsigned table_version ) const
{
  return this->dataAvailable( d_electroatomic_data_properties,
                              file_type,
                              table_version );
}

// Get the electroatomic data file types
std::set<ElectroatomicDataProperties::FileType>
AtomProperties::getElectroatomicDataFileTypes() const
{
  return this->getDataFileTypes( d_electroatomic_data_properties );
}

// Get the electroatomic data file versions
std::set<unsigned> AtomProperties::getDataFileVersions(
                  const ElectroatomicDataProperties::FileType file_type ) const
{
  return this->getDataFileVersions( d_electroatomic_data_properties,
                                    file_type );
}

// Get the recommended electroatomic data file version
unsigned AtomProperties::getRecommendedDataFileVersion(
                  const ElectroatomicDataProperties::FileType file_type ) const
{
  switch( file_type )
  {
    case PhotoatomicDataProperties::ACE_FILE:
      return 3;
    case PhotoatomicDataProperties::ACE_EPR_FILE:
      return 12;
    case PhotoatomicDataProperties::Native_EPR_File:
      return 0;
    default:
      return 0;
  }
}

// Get the electroatomic data properties
const ElectroatomicDataProperties& AtomProperties::getElectroatomicDataProperties(
                         const ElectroatomicDataProperties::FileType file_type,
                         const unsigned table_version ) const
{
  return this->getProperties<ElectroatomicDataProperties>(
                                              d_electroatomic_data_properties,
                                              file_type,
                                              table_version,
                                              "Electroatomic" );
}

// Set the electroatomic data properties
void AtomProperties::setElectroatomicDataProperties( const std::shared_ptr<const ElectroatomicDataProperties>& properties )
{
  this->setProperties( d_electroatomic_data_properties,
                       properties,
                       "Electroatomic" );
}

// Check if there is adjoint electroatomic data with the desired format
bool AtomProperties::adjointElectroatomicDataAvailable(
           const AdjointElectroatomicDataProperties::FileType file_type ) const
{
  return this->dataAvailable( d_adjoint_electroatomic_data_properties,
                              file_type );
}

// Check if there is adjoint electroatomic data with the desired format and version
bool AtomProperties::adjointElectroatomicataAvailable(
                  const AdjointElectroatomicDataProperties::FileType file_type,
                  const unsigned table_version ) const
{
  return this->dataAvailable( d_adjoint_electroatomic_data_properties,
                              file_type,
                              table_version );
}

// Get the adjoint electroatomic data file types
std::set<AdjointElectroatomicDataProperties::FileType>
AtomProperties::getAdjointElectroatomicDataFileTypes() const
{
  return this->getDataFileTypes( d_adjoint_electroatomic_data_properties );
}

// Get the adjoint electroatomic data file versions
std::set<unsigned> AtomProperties::getDataFileVersions(
                  const ElectroatomicDataProperties::FileType file_type ) const
{
  return this->getDataFileVersions( d_adjoint_electroatomic_data_properties,
                                    file_type );
}

// Get the recommended adjoint electroatomic data file version
unsigned AtomProperties::getRecommendedDataFileVersion(
           const AdjointElectroatomicDataProperties::FileType file_type ) const
{
  return this->getMaxDataFileVersion( d_adjoint_photoatomic_data_properties,
                                      file_type );
}

// Get the adjoint electroatomic data properties
const AdjointElectroatomicDataProperties& AtomProperties::getAdjointElectroatomicDataProperties(
                  const AdjointElectroatomicDataProperties::FileType file_type,
                  const unsigned table_version ) const
{
  return this->getProperties<AdjointElectroatomicDataProperties>(
                                       d_adjoint_electroatomic_data_properties,
                                       file_type,
                                       table_version,
                                       "Adjoint electroatomic" );
}

// Clone the properties
AtomProperties* AtomProperties::clone() const
{
  return new AtomProperties( *this );
}

// Deep clone the properties
AtomProperties* AtomProperties::deepClone() const
{
  AtomProperties* atom_properties_clone =
    new AtomProperties( d_zaid, d_atomic_weight_ratio );

  this->cloneStoredAtomProperties( *this, *atom_properties_clone );

  return atom_properties_clone;
}

// Clone the stored properties
void AtomProperties::cloneStoredAtomProperties(
                                     const AtomProperties& original_properties,
                                     AtomProperties& new_properties )
{
  // Clone the photoatomic data properties
  AtomProperties::cloneProperties(
                             original_properties.d_photoatomic_data_properties,
                             new_properties.d_photoatomic_data_properties );

  // Clone the adjoint photoatomic data properties
  AtomProperties::cloneProperties(
                     original_properties.d_adjoint_photoatomic_data_properties,
                     new_properties.d_adjoint_photoatomic_data_properties );

  // Clone the electroatomic data properties
  AtomProperties::cloneProperties(
                           original_properties.d_electroatomic_data_properties,
                           new_properties.d_electroatomic_data_properties );

  // Clone the adjoint electroatomic data properties
  AtomProperties::cloneProperties(
                   original_properties.d_adjoint_electroatomic_data_properties,
                   new_properties.d_adjoint_electroatomic_data_properties );
}

// Save the properties to an archive
template<typename Archive>
void AtomProperties::save( Archive& ar, const unsigned version ) const
{
  // Save the local member data
  ar & BOOST_SERIALIZATION_NVP( d_zaid );
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
  ar & BOOST_SERIALIZATION_NVP( d_zaid );
  ar & BOOST_SERIALIZATION_NVP( d_atomic_weight_ratio );
  ar & BOOST_SERIALIZATION_NVP( d_photoatomic_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_photoatomic_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_electroatomic_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_electroatomic_data_properties );
}
  
} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_AtomProperties.cpp
//---------------------------------------------------------------------------//
