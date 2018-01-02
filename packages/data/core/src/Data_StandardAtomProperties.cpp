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
#include "Utility_ContractException.hpp"

namespace Data{

// Default constructor
StandardAtomProperties::StandardAtomProperties()
{ /* ... */ }

// Constructor
StandardAtomProperties::StandardAtomProperties(
                      const std::string& name,
                      const unsigned atomic_number,
                      const double atomic_weight,
                      const std::shared_ptr<const PhotoatomicDataProperties>&
                      photoatomic_data_properties,
                      const std::shared_ptr<const ElectroatomicDataProperties>&
                      electroatomic_data_properties )
  : d_name( name ),
    d_atomic_number( atomic_number ),
    d_atomic_weight( atomic_weight ),
    d_photoatomic_data_properties( photoatomic_data_properties ),
    d_adjoint_photoatomic_data_properties(),
    d_electroatomic_data_properties( electroatomic_data_properties ),
    d_adjoint_electroatomic_data_properties()
{
  // Make sure that the name is valid
  testPrecondition( !name.empty() );
  // Make sure that the atomic weight is valid
  testPrecondition( atomic_weight > 0.0 );
  // Make sure that the properties are valid
  testPrecondition( photoatomic_data_properties.get() );
  testPrecondition( electroatomic_data_properties.get() );
}

// Constructor
StandardAtomProperties::StandardAtomProperties(
               const std::string& name,
               const unsigned atomic_number,
               const double atomic_weight,
               const std::shared_ptr<const PhotoatomicDataProperties>&
               photoatomic_data_properties,
               const std::shared_ptr<const AdjointPhotoatomicDataProperties>&
               adjoint_photoatomic_data_properties,
               const std::shared_ptr<const ElectroatomicDataProperties>&
               electroatomic_data_properties,
               const std::shared_ptr<const AdjointElectroatomicDataProperties>&
               adjoint_electroatomic_data_properties )
  : d_name(),
    d_atomic_number( atomic_number ),
    d_atomic_weight( atomic_weight ),
    d_photoatomic_data_properties( photoatomic_data_properties ),
    d_adjoint_photoatomic_data_properties( adjoint_photoatomic_data_properties ),
    d_electroatomic_data_properties( electroatomic_data_properties ),
    d_adjoint_electroatomic_data_properties( adjoint_electroatomic_data_properties )
{
  // Make sure that the name is valid
  testPrecondition( !name.empty() );
  // Make sure that the atomic weight is valid
  testPrecondition( atomic_weight > 0.0 );
  // Make sure that the properties are valid
  testPrecondition( photoatomic_data_properties.get() );
  testPrecondition( adjoint_photoatomic_data_properties.get() );
  testPrecondition( electroatomic_data_properties.get() );
  testPrecondition( adjoint_electroatomic_data_properties.get() );
}

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

// Check if the scattering center is a mixture (or lattice)
bool StandardAtomProperties::isMixture() const
{
  return false;
}

// Get the name of the properties
std::string StandardAtomProperties::name() const
{
  return d_name;
}

// Get the atomic number(s)
std::vector<unsigned> StandardAtomProperties::atomicNumbers() const
{
  return {d_atomic_number};
}

// Get the atomic mass number(s)
/*! \details The atomic mass number is not available with atomic data - zero
 * will be returned to indicate this.
 */
std::vector<unsigned> StandardAtomProperties::atomicMassNumbers() const
{
  return {0u};
}

// Get the isomer number(s)
/*! \details The isomer number is not available with atomic data - zero
 * will be returned to indicate this.
 */
std::vector<unsigned> StandardAtomProperties::isomerNumbers() const
{
  return {0u};
}

// Get the atomic weight(s)
std::vector<double> StandardAtomProperties::atomicWeights() const
{
  return {d_atomic_weight};
}

// Check if there is nuclear data
bool StandardAtomProperties::nuclearDataAvailable() const
{
  return false;
}

// Get the nuclear data properties
const NuclearDataProperties* StandardAtomProperties::getNuclearDataProperties() const
{
  return NULL;
}

// Check if there is adjoint nuclear data
bool StandardAtomProperties::adjointNuclearDataAvailable() const
{
  return false;
}

// Get the adjoint nuclear data
const AdjointNuclearDataProperties* StandardAtomProperties::getAdjointNuclearDataProperties() const
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

// Clone the properties
StandardAtomProperties* StandardAtomProperties::clone() const
{
  if( d_adjoint_photoatomic_data_properties &&
      d_adjoint_electroatomic_data_properties )
  {
    return new StandardAtomProperties(
                                     d_name,
                                     d_atomic_number,
                                     d_atomic_weight,
                                     d_photoatomic_data_properties,
                                     d_adjoint_photoatomic_data_properties,
                                     d_electroatomic_data_properties,
                                     d_adjoint_electroatomic_data_properties );
  }
  else
  {
    return new StandardAtomProperties( d_name,
                                       d_atomic_number,
                                       d_atomic_weight,
                                       d_photoatomic_data_properties,
                                       d_electroatomic_data_properties );
  }
}

// Deep clone the properties
StandardAtomProperties* StandardAtomProperties::deepClone() const
{
  std::shared_ptr<const PhotoatomicDataProperties>
    photoatomic_data_properties_clone( d_photoatomic_data_properties->clone() );

  std::shared_ptr<const ElectroatomicDataProperties>
    electroatomic_data_properties_clone( d_electroatomic_data_properties->clone() );

  if( d_adjoint_photoatomic_data_properties &&
      d_adjoint_electroatomic_data_properties )
  {
    std::shared_ptr<const AdjointPhotoatomicDataProperties>
      adjoint_photoatomic_data_properties_clone( d_adjoint_photoatomic_data_properties->clone() );

    std::shared_ptr<const AdjointElectroatomicDataProperties>
      adjoint_electroatomic_data_properties_clone( d_adjoint_electroatomic_data_properties->clone() );
    
    return new StandardAtomProperties(
                                 d_name,
                                 d_atomic_number,
                                 d_atomic_weight,
                                 photoatomic_data_properties_clone,
                                 adjoint_photoatomic_data_properties_clone,
                                 electroatomic_data_properties_clone,
                                 adjoint_electroatomic_data_properties_clone );
  }
  else
  {
    return new StandardAtomProperties( d_name,
                                       d_atomic_number,
                                       d_atomic_weight,
                                       photoatomic_data_properties_clone,
                                       electroatomic_data_properties_clone );
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
  ar & BOOST_SERIALIZATION_NVP( d_atomic_number );
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
  ar & BOOST_SERIALIZATION_NVP( d_atomic_number );
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
