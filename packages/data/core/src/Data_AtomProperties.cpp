//---------------------------------------------------------------------------//
//!
//! \file   Data_AtomProperties.hpp
//! \author Alex Robinson
//! \brief  The atom properties class definition
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
#include <boost/serialization/shared_ptr.hpp>

// FRENSIE Includes
#include "Data_AtomProperties.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
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
                      InvalidScatteringCenterPropertiesData,
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
const Data::ZAID& AtomProperties::zaid() const
{
  return d_zaid;
}

// Set the zaid
void AtomProperties::setZAID( const Data::ZAID zaid )
{
  d_zaid = zaid;
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

// Set the atomic weight ratio
void AtomProperties::setAtomicWeightRatio( const double atomic_weight_ratio )
{
  TEST_FOR_EXCEPTION( atomic_weight_ratio <= 0.0,
                      InvalidScatteringCenterPropertiesData,
                      "The atomic weight ratio cannot be zero or negative!" );
  
  d_atomic_weight_ratio = atomic_weight_ratio;
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
  return this->getMaxDataFileVersion( d_photoatomic_data_properties,
                                      file_type,
                                      "Photoatomic" );
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
                       d_zaid.atom(),
                       "AtomProperties",
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
bool AtomProperties::adjointPhotoatomicDataAvailable(
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
                                      file_type,
                                      "Adjoint photoatomic" );
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
                       d_zaid.atom(),
                       "AtomProperties",
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
  return this->getMaxDataFileVersion( d_electroatomic_data_properties,
                                      file_type,
                                      "Electroatomic" );
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
                       d_zaid.atom(),
                       "AtomProperties",
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
bool AtomProperties::adjointElectroatomicDataAvailable(
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
           const AdjointElectroatomicDataProperties::FileType file_type ) const
{
  return this->getDataFileVersions( d_adjoint_electroatomic_data_properties,
                                    file_type );
}

// Get the recommended adjoint electroatomic data file version
unsigned AtomProperties::getRecommendedDataFileVersion(
           const AdjointElectroatomicDataProperties::FileType file_type ) const
{
  return this->getMaxDataFileVersion( d_adjoint_electroatomic_data_properties,
                                      file_type,
                                      "Adjoint electroatomic" );
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

// Set the adjoint electroatomic data properties
void AtomProperties::setAdjointElectroatomicDataProperties( const std::shared_ptr<const AdjointElectroatomicDataProperties>& properties )
{
  this->setProperties( d_adjoint_electroatomic_data_properties,
                       properties,
                       d_zaid.atom(),
                       "AtomProperties",
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

// Place the object in an output stream
void AtomProperties::toStream( std::ostream& os ) const
{
  os << Utility::Bold( d_zaid.toName() + " Properties:" ) << "\n"
     << "  " << Utility::Underlined("Atomic Weight:") << " "
     << this->atomicWeight() << "\n";

  // Print the photoatomic properties
  this->printProperties( d_photoatomic_data_properties,
                         "Photoatomic Data",
                         os );

  // Print the adjoint photoatomic properties
  this->printProperties( d_adjoint_photoatomic_data_properties,
                         "Adjoint Photoatomic Data",
                         os );

  // Print the electroatomic properties
  this->printProperties( d_electroatomic_data_properties,
                         "Electroatomic Data",
                         os );

  // Print the adjoint electroatomic properties
  this->printProperties( d_adjoint_electroatomic_data_properties,
                         "Adjoint Electroatomic Data",
                         os );

  os.flush();
}

EXPLICIT_DATA_CLASS_SAVE_LOAD_INST( AtomProperties );
  
} // end Data namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( AtomProperties, Data );

//---------------------------------------------------------------------------//
// end Data_AtomProperties.cpp
//---------------------------------------------------------------------------//
