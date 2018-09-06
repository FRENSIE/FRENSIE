//---------------------------------------------------------------------------//
//!
//! \file   Data_AtomProperties.hpp
//! \author Alex Robinson
//! \brief  The atom properties class definition
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/serialization/map.hpp>
#include <boost/serialization/shared_ptr.hpp>

// FRENSIE Includes
#include "FRENSIE_Archives.hpp" // Must include first
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
AtomProperties::AtomProperties( const AtomType atom,
                                const double atomic_weight_ratio )
  : d_atom( atom ),
    d_atomic_weight_ratio( atomic_weight_ratio ),
    d_photoatomic_data_properties(),
    d_adjoint_photoatomic_data_properties(),
    d_electroatomic_data_properties(),
    d_adjoint_electroatomic_data_properties()
{
  TEST_FOR_EXCEPTION( atomic_weight_ratio <= 0.0,
                      InvalidScatteringCenterPropertiesData,
                      "The atomic weight ratio cannot be zero or negative!" );
}

// Constructor
AtomProperties::AtomProperties( const AtomType atom,
                                const AtomicWeight atomic_weight )
  : AtomProperties( atom, atomic_weight/Utility::PhysicalConstants::neutron_rest_mass_amu_q )
{ /* ... */ }

// Copy constructor
AtomProperties::AtomProperties( const AtomProperties& other )
  : d_atom( other.d_atom ),
    d_atomic_weight_ratio( other.d_atomic_weight_ratio ),
    d_photoatomic_data_properties( other.d_photoatomic_data_properties ),
    d_adjoint_photoatomic_data_properties( other.d_adjoint_photoatomic_data_properties ),
    d_electroatomic_data_properties( other.d_electroatomic_data_properties ),
    d_adjoint_electroatomic_data_properties( other.d_adjoint_electroatomic_data_properties )
{ /* ... */ }

// Check if there are no properties
bool AtomProperties::empty() const
{
  return d_photoatomic_data_properties.empty() &&
    d_adjoint_photoatomic_data_properties.empty() &&
    d_electroatomic_data_properties.empty() &&
    d_adjoint_electroatomic_data_properties.empty();
}

// Get the atom
AtomType AtomProperties::atom() const
{
  return d_atom;
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
  return BaseType::dataAvailable( d_photoatomic_data_properties, file_type );
}

// Check if there is photoatomic data with the desired format and version
bool AtomProperties::photoatomicDataAvailable(
                           const PhotoatomicDataProperties::FileType file_type,
                           const unsigned table_version ) const
{
  return BaseType::dataAvailable( d_photoatomic_data_properties,
                                  file_type,
                                  table_version );
}

// Get the photoatomic data file types
std::set<PhotoatomicDataProperties::FileType>
AtomProperties::getPhotoatomicDataFileTypes() const
{
  return BaseType::getDataFileTypes( d_photoatomic_data_properties );
}

// Get the photoatomic data file versions
std::set<unsigned> AtomProperties::getDataFileVersions(
                    const PhotoatomicDataProperties::FileType file_type ) const
{
  return BaseType::getDataFileVersions( d_photoatomic_data_properties,
                                        file_type );
}

// Get the recommended photoatomic data file version
unsigned AtomProperties::getRecommendedDataFileVersion(
                    const PhotoatomicDataProperties::FileType file_type ) const
{
  return BaseType::getMaxDataFileVersion( d_photoatomic_data_properties,
                                          file_type,
                                          "Photoatomic" );
}

// Get the photoatomic data properties
const PhotoatomicDataProperties& AtomProperties::getPhotoatomicDataProperties(
                           const PhotoatomicDataProperties::FileType file_type,
                           const unsigned table_version ) const
{
  return BaseType::getProperties<PhotoatomicDataProperties>(
                                                d_photoatomic_data_properties,
                                                file_type,
                                                table_version,
                                                "Photoatomic" );
}

// Get the shared photoatomic data properties
const std::shared_ptr<const PhotoatomicDataProperties>&
AtomProperties::getSharedPhotoatomicDataProperties(
                           const PhotoatomicDataProperties::FileType file_type,
                           const unsigned table_version ) const
{
  return BaseType::getSharedProperties<PhotoatomicDataProperties>(
                                                d_photoatomic_data_properties,
                                                file_type,
                                                table_version,
                                                "Photoatomic" );
}  

// Set the photoatomic data
void AtomProperties::setPhotoatomicDataProperties( const std::shared_ptr<const PhotoatomicDataProperties>& properties )
{
  BaseType::setProperties( d_photoatomic_data_properties,
                           properties,
                           d_atom,
                           "AtomProperties",
                           "Photoatomic" );
}

// Check if there is adjoint photoatomic data with the desired format
bool AtomProperties::adjointPhotoatomicDataAvailable(
             const AdjointPhotoatomicDataProperties::FileType file_type ) const
{
  return BaseType::dataAvailable( d_adjoint_photoatomic_data_properties,
                                  file_type );
}

// Check if there is adjoint photoatomic data with the desired format and version
bool AtomProperties::adjointPhotoatomicDataAvailable(
                    const AdjointPhotoatomicDataProperties::FileType file_type,
                    const unsigned table_version ) const
{
  return BaseType::dataAvailable( d_adjoint_photoatomic_data_properties,
                                  file_type,
                                  table_version );
}

// Get the adjoint photoatomic data file types
std::set<AdjointPhotoatomicDataProperties::FileType>
AtomProperties::getAdjointPhotoatomicDataFileTypes() const
{
  return BaseType::getDataFileTypes( d_adjoint_photoatomic_data_properties );
}

// Get the adjoint photoatomic data file versions
std::set<unsigned> AtomProperties::getDataFileVersions(
             const AdjointPhotoatomicDataProperties::FileType file_type ) const
{
  return BaseType::getDataFileVersions( d_adjoint_photoatomic_data_properties,
                                        file_type );
}

// Get the recommended adjoint photoatomic data file version
unsigned AtomProperties::getRecommendedDataFileVersion(
             const AdjointPhotoatomicDataProperties::FileType file_type ) const
{
  return BaseType::getMaxDataFileVersion(
                                         d_adjoint_photoatomic_data_properties,
                                         file_type,
                                         "Adjoint photoatomic" );
}

// Get the adjoint photoatomic data properties
const AdjointPhotoatomicDataProperties& AtomProperties::getAdjointPhotoatomicDataProperties(
                    const AdjointPhotoatomicDataProperties::FileType file_type,
                    const unsigned table_version ) const
{
  return BaseType::getProperties<AdjointPhotoatomicDataProperties>(
                                        d_adjoint_photoatomic_data_properties,
                                        file_type,
                                        table_version,
                                        "Adjoint photoatomic" );
}

// Get the shared adjoint photoatomic data properties
const std::shared_ptr<const AdjointPhotoatomicDataProperties>&
AtomProperties::getSharedAdjointPhotoatomicDataProperties(
                    const AdjointPhotoatomicDataProperties::FileType file_type,
                    const unsigned table_version ) const
{
  return BaseType::getSharedProperties<AdjointPhotoatomicDataProperties>(
                                        d_adjoint_photoatomic_data_properties,
                                        file_type,
                                        table_version,
                                        "Adjoint photoatomic" );
}

// Set the adjoint photoatomic data properties
void AtomProperties::setAdjointPhotoatomicDataProperties( const std::shared_ptr<const AdjointPhotoatomicDataProperties>& properties )
{
  BaseType::setProperties( d_adjoint_photoatomic_data_properties,
                           properties,
                           d_atom,
                           "AtomProperties",
                           "Adjoint photoatomic" );
}

// Check if there is electroatomic data with the desired format
bool AtomProperties::electroatomicDataAvailable(
                  const ElectroatomicDataProperties::FileType file_type ) const
{
  return BaseType::dataAvailable( d_electroatomic_data_properties, file_type );
}

// Check if there is electroatomic data with the desired format and version
bool AtomProperties::electroatomicDataAvailable(
                         const ElectroatomicDataProperties::FileType file_type,
                         const unsigned table_version ) const
{
  return BaseType::dataAvailable( d_electroatomic_data_properties,
                                  file_type,
                                  table_version );
}

// Get the electroatomic data file types
std::set<ElectroatomicDataProperties::FileType>
AtomProperties::getElectroatomicDataFileTypes() const
{
  return BaseType::getDataFileTypes( d_electroatomic_data_properties );
}

// Get the electroatomic data file versions
std::set<unsigned> AtomProperties::getDataFileVersions(
                  const ElectroatomicDataProperties::FileType file_type ) const
{
  return BaseType::getDataFileVersions( d_electroatomic_data_properties,
                                        file_type );
}

// Get the recommended electroatomic data file version
unsigned AtomProperties::getRecommendedDataFileVersion(
                  const ElectroatomicDataProperties::FileType file_type ) const
{
  return BaseType::getMaxDataFileVersion( d_electroatomic_data_properties,
                                          file_type,
                                          "Electroatomic" );
}

// Get the electroatomic data properties
const ElectroatomicDataProperties& AtomProperties::getElectroatomicDataProperties(
                         const ElectroatomicDataProperties::FileType file_type,
                         const unsigned table_version ) const
{
  return BaseType::getProperties<ElectroatomicDataProperties>(
                                              d_electroatomic_data_properties,
                                              file_type,
                                              table_version,
                                              "Electroatomic" );
}

// Get the shared electroatomic data properties
const std::shared_ptr<const ElectroatomicDataProperties>&
AtomProperties::getSharedElectroatomicDataProperties(
                         const ElectroatomicDataProperties::FileType file_type,
                         const unsigned table_version ) const
{
  return BaseType::getSharedProperties<ElectroatomicDataProperties>(
                                              d_electroatomic_data_properties,
                                              file_type,
                                              table_version,
                                              "Electroatomic" );
}

// Set the electroatomic data properties
void AtomProperties::setElectroatomicDataProperties( const std::shared_ptr<const ElectroatomicDataProperties>& properties )
{
  BaseType::setProperties( d_electroatomic_data_properties,
                           properties,
                           d_atom,
                           "AtomProperties",
                           "Electroatomic" );
}

// Check if there is adjoint electroatomic data with the desired format
bool AtomProperties::adjointElectroatomicDataAvailable(
           const AdjointElectroatomicDataProperties::FileType file_type ) const
{
  return BaseType::dataAvailable( d_adjoint_electroatomic_data_properties,
                                  file_type );
}

// Check if there is adjoint electroatomic data with the desired format and version
bool AtomProperties::adjointElectroatomicDataAvailable(
                  const AdjointElectroatomicDataProperties::FileType file_type,
                  const unsigned table_version ) const
{
  return BaseType::dataAvailable( d_adjoint_electroatomic_data_properties,
                                  file_type,
                                  table_version );
}

// Get the adjoint electroatomic data file types
std::set<AdjointElectroatomicDataProperties::FileType>
AtomProperties::getAdjointElectroatomicDataFileTypes() const
{
  return BaseType::getDataFileTypes( d_adjoint_electroatomic_data_properties );
}

// Get the adjoint electroatomic data file versions
std::set<unsigned> AtomProperties::getDataFileVersions(
           const AdjointElectroatomicDataProperties::FileType file_type ) const
{
  return BaseType::getDataFileVersions(
                                       d_adjoint_electroatomic_data_properties,
                                       file_type );
}

// Get the recommended adjoint electroatomic data file version
unsigned AtomProperties::getRecommendedDataFileVersion(
           const AdjointElectroatomicDataProperties::FileType file_type ) const
{
  return BaseType::getMaxDataFileVersion(
                                       d_adjoint_electroatomic_data_properties,
                                       file_type,
                                       "Adjoint electroatomic" );
}

// Get the adjoint electroatomic data properties
const AdjointElectroatomicDataProperties& AtomProperties::getAdjointElectroatomicDataProperties(
                  const AdjointElectroatomicDataProperties::FileType file_type,
                  const unsigned table_version ) const
{
  return BaseType::getProperties<AdjointElectroatomicDataProperties>(
                                       d_adjoint_electroatomic_data_properties,
                                       file_type,
                                       table_version,
                                       "Adjoint electroatomic" );
}

// Get the shared adjoint electroatomic data properties
const std::shared_ptr<const AdjointElectroatomicDataProperties>&
AtomProperties::getSharedAdjointElectroatomicDataProperties(
                  const AdjointElectroatomicDataProperties::FileType file_type,
                  const unsigned table_version ) const
{
  return BaseType::getSharedProperties<AdjointElectroatomicDataProperties>(
                                      d_adjoint_electroatomic_data_properties,
                                      file_type,
                                      table_version,
                                      "Adjoint electroatomic" );
}

// Set the adjoint electroatomic data properties
void AtomProperties::setAdjointElectroatomicDataProperties( const std::shared_ptr<const AdjointElectroatomicDataProperties>& properties )
{
  BaseType::setProperties( d_adjoint_electroatomic_data_properties,
                           properties,
                           d_atom,
                           "AtomProperties",
                           "Adjoint electroatomic" );
}

// Place the object in an output stream
void AtomProperties::toStream( std::ostream& os ) const
{
  os << Utility::Bold( Utility::toString(d_atom) + " Properties:" ) << "\n"
     << "  " << Utility::Underlined("Atomic Weight:") << " "
     << this->atomicWeight() << "\n";

  // Print the photoatomic properties
  BaseType::printProperties( d_photoatomic_data_properties,
                             "Photoatomic Data",
                             os );

  // Print the adjoint photoatomic properties
  BaseType::printProperties( d_adjoint_photoatomic_data_properties,
                             "Adjoint Photoatomic Data",
                             os );

  // Print the electroatomic properties
  BaseType::printProperties( d_electroatomic_data_properties,
                             "Electroatomic Data",
                             os );

  // Print the adjoint electroatomic properties
  BaseType::printProperties( d_adjoint_electroatomic_data_properties,
                             "Adjoint Electroatomic Data",
                             os );

  os.flush();
}

EXPLICIT_CLASS_SAVE_LOAD_INST( AtomProperties );
  
} // end Data namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( AtomProperties, Data );

//---------------------------------------------------------------------------//
// end Data_AtomProperties.cpp
//---------------------------------------------------------------------------//
