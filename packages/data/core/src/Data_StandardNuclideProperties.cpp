//---------------------------------------------------------------------------//
//!
//! \file   Data_StandardNuclideProperties.cpp
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
#include "Data_StandardNuclideProperties.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace Data{

// Constructor
StandardNuclideProperties::StandardNuclideProperties(
                      const std::string& name,
                      const unsigned atomic_number,
                      const unsigned atomic_mass_number,
                      const unsigned isomer_number,
                      const double atomic_weight_ratio,
                      const std::shared_ptr<const NuclearDataProperties>&
                      nuclear_data_properties,
                      const std::shared_ptr<const PhotoatomicDataProperties>&
                      photoatomic_data_properties,
                      const std::shared_ptr<const ElectroatomicDataProperties>&
                      electroatomic_data_properties )
  : d_name( name ),
    d_atomic_number( atomic_number ),
    d_atomic_mass_number( atomic_mass_number ),
    d_isomer_number( isomer_number ),
    d_atomic_weight_ratio( atomic_weight_ratio ),
    d_nuclear_data_properties( nuclear_data_properties ),
    d_adjoint_nuclear_data_properties(),
    d_photoatomic_data_properties( photoatomic_data_properties ),
    d_adjoint_photoatomic_data_properties(),
    d_electroatomic_data_properties( electroatomic_data_properties ),
    d_adjoint_electroatomic_data_properties()
{
  // Make sure that the name is valid
  testPrecondition( !name.empty() );
  // Make sure that the atomic mass number is valid
  testPrecondition( atomic_mass_number >= atomic_number );
  // Make sure that the atomic weight ratio is valid
  testPrecondition( atomic_weight_ratio > 0.0 );
  // Make sure that the properties are valid
  testPrecondition( nuclear_data_properties.get() );
  testPrecondition( photoatomic_data_properties.get() );
  testPrecondition( electroatomic_data_properties.get() );
}

// Constructor
StandardNuclideProperties::StandardNuclideProperties(
               const std::string& name,
               const unsigned atomic_number,
               const unsigned atomic_mass_number,
               const unsigned isomer_number,
               const double atomic_weight_ratio,
               const std::shared_ptr<const NuclearDataProperties>&
               nuclear_data_properties,
               const std::shared_ptr<const AdjointNuclearDataProperties>&
               adjoint_nuclear_data_properties,
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
    d_atomic_mass_number( atomic_mass_number ),
    d_isomer_number( isomer_number ),
    d_atomic_weight_ratio( atomic_weight_ratio ),
    d_nuclear_data_properties( nuclear_data_properties ),
    d_adjoint_nuclear_data_properties( adjoint_nuclear_data_properties ),
    d_photoatomic_data_properties( photoatomic_data_properties ),
    d_adjoint_photoatomic_data_properties( adjoint_photoatomic_data_properties ),
    d_electroatomic_data_properties( electroatomic_data_properties ),
    d_adjoint_electroatomic_data_properties( adjoint_electroatomic_data_properties )
{
  // Make sure that the name is valid
  testPrecondition( !name.empty() );
  // Make sure that the atomic mass number is valid
  testPrecondition( atomic_mass_number >= atomic_number );
  // Make sure that the atomic weight ratio is valid
  testPrecondition( atomic_weight_ratio > 0.0 );
  // Make sure that the properties are valid
  testPrecondition( nuclear_data_properties.get() );
  testPrecondition( adjoint_nuclear_data_properties.get() );
  testPrecondition( photoatomic_data_properties.get() );
  testPrecondition( adjoint_photoatomic_data_properties.get() );
  testPrecondition( electroatomic_data_properties.get() );
  testPrecondition( adjoint_electroatomic_data_properties.get() );
}

// Check if the scattering center is an atom
bool StandardNuclideProperties::isAtom() const
{
  return false;
}

// Check if the scattering center is a nuclide
bool StandardNuclideProperties::isNuclide() const
{
  return true;
}

// Check if the scattering center is a mixture (or lattice)
bool StandardNuclideProperties::isMixture() const
{
  return false;
}

// Get the name of the properties
std::string StandardNuclideProperties::name() const
{
  return d_name;
}

// Get the atomic number(s)
std::vector<unsigned> StandardNuclideProperties::atomicNumbers() const
{
  return {d_atomic_number};
}

// Get the atomic mass number(s)
std::vector<unsigned> StandardNuclideProperties::atomicMassNumbers() const
{
  return {d_atomic_mass_number};
}

// Get the isomer number(s)
std::vector<unsigned> StandardNuclideProperties::isomerNumbers() const
{
  return {d_isomer_number};
}

// Get the atomic weight(s)
std::vector<double> StandardNuclideProperties::atomicWeights() const
{
  return {d_atomic_weight_ratio*Utility::PhysicalConstants::neutron_rest_mass_amu};
}

// Get the atomic weight ratio(s) (atomic weight/neutron weight)
std::vector<double> StandardNuclideProperties::atomicWeightRatios() const
{
  return {d_atomic_weight_ratio};
}

// Check if there is nuclear data
bool StandardNuclideProperties::nuclearDataAvailable() const
{
  return d_nuclear_data_properties.get();
}

// Get the nuclear data properties
const NuclearDataProperties* StandardNuclideProperties::getNuclearDataProperties() const
{
  return d_nuclear_data_properties.get();
}

// Check if there is adjoint nuclear data
bool StandardNuclideProperties::adjointNuclearDataAvailable() const
{
  return d_adjoint_nuclear_data_properties.get();
}

// Get the adjoint nuclear data
const AdjointNuclearDataProperties* StandardNuclideProperties::getAdjointNuclearDataProperties() const
{
  return d_adjoint_nuclear_data_properties.get();
}

// Check if there is photoatomic data
bool StandardNuclideProperties::photoatomicDataAvailable() const
{
  return d_photoatomic_data_properties.get();
}

// Get the photoatomic data
const PhotoatomicDataProperties* StandardNuclideProperties::getPhotoatomicDataProperties() const
{
  return d_photoatomic_data_properties.get();
}

// Check if there is adjoint photoatomic data
bool StandardNuclideProperties::adjointPhotoatomicDataAvailable() const
{
  return d_adjoint_photoatomic_data_properties.get();
}

// Get the adjoint photoatomic data properties
const AdjointPhotoatomicDataProperties* StandardNuclideProperties::getAdjointPhotoatomicDataProperties() const
{
  return d_adjoint_photoatomic_data_properties.get();
}

// Check if there is electroatomic data
bool StandardNuclideProperties::electroatomicDataAvailable() const
{
  return d_electroatomic_data_properties.get();
}

// Get the electroatomic data properties
const ElectroatomicDataProperties* StandardNuclideProperties::getElectroatomicDataProperties() const
{
  return d_electroatomic_data_properties.get();
}

// Check if there is adjoint electroatomic data
bool StandardNuclideProperties::adjointElectroatomicDataAvailable() const
{
  return d_adjoint_electroatomic_data_properties.get();
}

// Get the adjoint electroatomic data properties
const AdjointElectroatomicDataProperties* StandardNuclideProperties::getAdjointElectroatomicDataProperties() const
{
  return d_adjoint_electroatomic_data_properties.get();
}

// Clone the properties
StandardNuclideProperties* StandardNuclideProperties::clone() const
{
  if( d_adjoint_nuclear_data_properties &&
      d_adjoint_photoatomic_data_properties &&
      d_adjoint_electroatomic_data_properties )
  {
    return new StandardNuclideProperties(
                                     d_name,
                                     d_atomic_number,
                                     d_atomic_mass_number,
                                     d_isomer_number,
                                     d_atomic_weight_ratio,
                                     d_nuclear_data_properties,
                                     d_adjoint_nuclear_data_properties,
                                     d_photoatomic_data_properties,
                                     d_adjoint_photoatomic_data_properties,
                                     d_electroatomic_data_properties,
                                     d_adjoint_electroatomic_data_properties );
  }
  else
  {
    return new StandardNuclideProperties( d_name,
                                          d_atomic_number,
                                          d_atomic_mass_number,
                                          d_isomer_number,
                                          d_atomic_weight_ratio,
                                          d_nuclear_data_properties,
                                          d_photoatomic_data_properties,
                                          d_electroatomic_data_properties );
  }
}

// Deep clone the properties
StandardNuclideProperties* StandardNuclideProperties::deepClone() const
{
  std::shared_ptr<const NuclearDataProperties>
    nuclear_data_properties_clone( d_nuclear_data_properties->clone() );

  std::shared_ptr<const PhotoatomicDataProperties>
    photoatomic_data_properties_clone( d_photoatomic_data_properties->clone() );

  std::shared_ptr<const ElectroatomicDataProperties>
    electroatomic_data_properties_clone( d_electroatomic_data_properties->clone() );

  if( d_adjoint_nuclear_data_properties &&
      d_adjoint_photoatomic_data_properties &&
      d_adjoint_electroatomic_data_properties )
  {
    std::shared_ptr<const AdjointNuclearDataProperties>
      adjoint_nuclear_data_properties_clone( d_adjoint_nuclear_data_properties->clone() );

    std::shared_ptr<const AdjointPhotoatomicDataProperties>
      adjoint_photoatomic_data_properties_clone( d_adjoint_photoatomic_data_properties->clone() );

    std::shared_ptr<const AdjointElectroatomicDataProperties>
      adjoint_electroatomic_data_properties_clone( d_adjoint_electroatomic_data_properties->clone() );
    
    return new StandardNuclideProperties(
                                 d_name,
                                 d_atomic_number,
                                 d_atomic_mass_number,
                                 d_isomer_number,
                                 d_atomic_weight_ratio,
                                 nuclear_data_properties_clone,
                                 adjoint_nuclear_data_properties_clone,
                                 photoatomic_data_properties_clone,
                                 adjoint_photoatomic_data_properties_clone,
                                 electroatomic_data_properties_clone,
                                 adjoint_electroatomic_data_properties_clone );
  }
  else
  {
    return new StandardNuclideProperties(
                                         d_name,
                                         d_atomic_number,
                                         d_atomic_mass_number,
                                         d_isomer_number,
                                         d_atomic_weight_ratio,
                                         nuclear_data_properties_clone,
                                         photoatomic_data_properties_clone,
                                         electroatomic_data_properties_clone );
  }
}

// Save the properties to an archive
template<typename Archive>
void StandardNuclideProperties::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ScatteringCenterProperties );

  // Save the local member data
  ar & BOOST_SERIALIZATION_NVP( d_name );
  ar & BOOST_SERIALIZATION_NVP( d_atomic_number );
  ar & BOOST_SERIALIZATION_NVP( d_atomic_mass_number );
  ar & BOOST_SERIALIZATION_NVP( d_isomer_number );
  ar & BOOST_SERIALIZATION_NVP( d_atomic_weight_ratio );
  ar & BOOST_SERIALIZATION_NVP( d_nuclear_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_nuclear_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_photoatomic_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_photoatomic_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_electroatomic_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_electroatomic_data_properties );
}

// Load the properties from an archive
template<typename Archive>
void StandardNuclideProperties::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ScatteringCenterProperties );

  // Load the local member data
  ar & BOOST_SERIALIZATION_NVP( d_name );
  ar & BOOST_SERIALIZATION_NVP( d_atomic_number );
  ar & BOOST_SERIALIZATION_NVP( d_atomic_mass_number );
  ar & BOOST_SERIALIZATION_NVP( d_isomer_number );
  ar & BOOST_SERIALIZATION_NVP( d_atomic_weight_ratio );
  ar & BOOST_SERIALIZATION_NVP( d_nuclear_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_nuclear_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_photoatomic_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_photoatomic_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_electroatomic_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_electroatomic_data_properties );
}

EXPLICIT_DATA_CLASS_SAVE_LOAD_INST( StandardNuclideProperties );
  
} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_StandardNuclideProperties.cpp
//---------------------------------------------------------------------------//
