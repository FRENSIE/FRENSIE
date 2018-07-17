//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ScatteringCenterDefinition.hpp
//! \author Alex Robinson
//! \brief  The scattering center definition declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SCATTERING_CENTER_DEFINITION_HPP
#define MONTE_CARLO_SCATTERING_CENTER_DEFINITION_HPP

// Boost Includes
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/optional.hpp>

// FRENSIE Includes
#include "Data_PhotoatomicDataProperties.hpp"
#include "Data_AdjointPhotoatomicDataProperties.hpp"
#include "Data_ElectroatomicDataProperties.hpp"
#include "Data_AdjointElectroatomicDataProperties.hpp"
#include "Data_NuclearDataProperties.hpp"
#include "Data_ThermalNuclearDataProperties.hpp"
#include "Data_AdjointNuclearDataProperties.hpp"
#include "Data_AdjointThermalNuclearDataProperties.hpp"
#include "Data_PhotonuclearDataProperties.hpp"
#include "Data_AdjointPhotonuclearDataProperties.hpp"
#include "Data_ZAID.hpp"
#include "Utility_OStreamableObject.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace MonteCarlo{

//! The scattering center definition class
class ScatteringCenterDefinition : public Utility::OStreamableObject
{

public:

  //! Basic Constructor
  ScatteringCenterDefinition( const Data::ZAID& zaid );
  
  //! Constructor
  ScatteringCenterDefinition( const std::string& name,
                              const Data::ZAID& zaid );

  //! Destructor
  ~ScatteringCenterDefinition()
  { /* ... */ }

  //! Return the name
  const std::string& getName() const;

  //! Return the zaid
  const Data::ZAID& getZAID() const;

  //! Check if an atomic weight (or atomic weight ratio) override has been set
  bool isAtomicWeightSet() const;

  //! Set the atomic weight override
  void setAtomicWeight( const double atomic_weight );

  //! Set the atomic weight ratio override
  void setAtomicWeightRatio( const double atomic_weight_ratio );

  //! Get the atomic weight override
  double getAtomicWeight() const;

  //! Get the atomic weight ratio override
  double getAtomicWeightRatio() const;

  //! Check if there are photoatomic data properties
  bool hasPhotoatomicDataProperties() const;

  //! Set the photoatomic data properties
  void setPhotoatomicDataProperties( const std::shared_ptr<const Data::PhotoatomicDataProperties>& properties );

  //! Set the photoatomic data properties
  void setDataProperties( const std::shared_ptr<const Data::PhotoatomicDataProperties>& properties );

  //! Get the photoatomic data properties
  const Data::PhotoatomicDataProperties& getPhotoatomicDataProperties(
                                          double* atomic_weight = NULL ) const;

  //! Check if there are adjoint photoatomic data properties
  bool hasAdjointPhotoatomicDataProperties() const;

  //! Set the adjoint photoatomic data properties
  void setAdjointPhotoatomicDataProperties( const std::shared_ptr<const Data::AdjointPhotoatomicDataProperties>& properties );

  //! Set the adjoint photoatomic data properties
  void setDataProperties( const std::shared_ptr<const Data::AdjointPhotoatomicDataProperties>& properties );

  //! Get the adjoint photoatomic data properties
  const Data::AdjointPhotoatomicDataProperties& getAdjointPhotoatomicDataProperties(
                                          double* atomic_weight = NULL ) const;

  //! Check if there are electroatomic data properties
  bool hasElectroatomicDataProperties() const;

  //! Set the electroatomic data properties
  void setElectroatomicDataProperties( const std::shared_ptr<const Data::ElectroatomicDataProperties>& properties );

  //! Set the electroatomic data properties
  void setDataProperties( const std::shared_ptr<const Data::ElectroatomicDataProperties>& properties );

  //! Get the electroatomic data properties
  const Data::ElectroatomicDataProperties& getElectroatomicDataProperties(
                                          double* atomic_weight = NULL ) const;

  //! Check if there are adjoint electroatomic data properties
  bool hasAdjointElectroatomicDataProperties() const;

  //! Set the adjoint electroatomic data properties
  void setAdjointElectroatomicDataProperties( const std::shared_ptr<const Data::AdjointElectroatomicDataProperties>& properties );

  //! Set the adjoint electroatomic data properties
  void setDataProperties( const std::shared_ptr<const Data::AdjointElectroatomicDataProperties>& properties );

  //! Get the adjoint electroatomic data properties
  const Data::AdjointElectroatomicDataProperties& getAdjointElectroatomicDataProperties(
                                          double* atomic_weight = NULL ) const;

  //! Check if there are nuclear data properties
  bool hasNuclearDataProperties() const;

  //! Set the nuclear data properties
  void setNuclearDataProperties( const std::shared_ptr<const Data::NuclearDataProperties>& properties );

  //! Set the nuclear data properties
  void setDataProperties( const std::shared_ptr<const Data::NuclearDataProperties>& properties );

  //! Get the nuclear data properties
  const Data::NuclearDataProperties& getNuclearDataProperties(
                                    double* atomic_weight_ratio = NULL ) const;

  //! Check if there are thermal nuclear data properties
  bool hasThermalNuclearDataProperties() const;

  //! Set the thermal nuclear data properties
  void setThermalNuclearDataProperties( const std::shared_ptr<const Data::ThermalNuclearDataProperties>& properties );

  //! Set the thermal nuclear data properties
  void setDataProperties( const std::shared_ptr<const Data::ThermalNuclearDataProperties>& properties );

  //! Get the thermal nuclear data properties
  const Data::ThermalNuclearDataProperties& getThermalNuclearDataProperties() const;

  //! Check if there are adjoint nuclear data properties
  bool hasAdjointNuclearDataProperties() const;

  //! Set the adjoint nuclear data properties
  void setAdjointNuclearDataProperties( const std::shared_ptr<const Data::AdjointNuclearDataProperties>& properties );

  //! Set the adjoint nuclear data properties
  void setDataProperties( const std::shared_ptr<const Data::AdjointNuclearDataProperties>& properties );

  //! Get the adjoint nuclear data properties
  const Data::AdjointNuclearDataProperties& getAdjointNuclearDataProperties(
                                    double* atomic_weight_ratio = NULL ) const;

  //! Check if there are adjoint thermal nuclear data properties
  bool hasAdjointThermalNuclearDataProperties() const;

  //! Set the adjoint thermal nuclear data properties
  void setAdjointThermalNuclearDataProperties( const std::shared_ptr<const Data::AdjointThermalNuclearDataProperties>& properties );

  //! Set the adjoint thermal nuclear data properties
  void setDataProperties( const std::shared_ptr<const Data::AdjointThermalNuclearDataProperties>& properties );

  //! Get the adjoint thermal nuclear data properties
  const Data::AdjointThermalNuclearDataProperties& getAdjointThermalNuclearDataProperties() const;

  //! Check if there are photonuclear data properties
  bool hasPhotonuclearDataProperties() const;

  //! Set the photonuclear data properties
  void setPhotonuclearDataProperties( const std::shared_ptr<const Data::PhotonuclearDataProperties>& properties );

  //! Set the photonuclear data properties
  void setDataProperties( const std::shared_ptr<const Data::PhotonuclearDataProperties>& properties );

  //! Get the photonuclear data properties
  const Data::PhotonuclearDataProperties& getPhotonuclearDataProperties(
                                          double* atomic_weight = NULL ) const;

  //! Check if there are adjoint photonuclear data properties
  bool hasAdjointPhotonuclearDataProperties() const;

  //! Set the adjoint photonuclear data properties
  void setAdjointPhotonuclearDataProperties( const std::shared_ptr<const Data::AdjointPhotonuclearDataProperties>& properties );

  //! Set the adjoint photonuclear data properties
  void setDataProperties( const std::shared_ptr<const Data::AdjointPhotonuclearDataProperties>& properties );

  //! Get the adjoint photonuclear data properties
  const Data::AdjointPhotonuclearDataProperties& getAdjointPhotonuclearDataProperties(
                                          double* atomic_weight = NULL ) const;

  //! Place the object in an output stream
  void toStream( std::ostream& os ) const final override;

private:

  // Default constructor
  ScatteringCenterDefinition();

  // Get the atomic weight
  template<typename DataProperties>
  double getAtomicWeight( const DataProperties& properties ) const;

  // Get the atomic weight ratio
  template<typename DataProperties>
  double getAtomicWeightRatio( const DataProperties& properties ) const;

  // Verify consistent atom
  void verifyConsistentAtom( const Data::AtomType atom,
                             const std::string& type ) const;

  // Verify consistent zaid
  void verifyConsistentZaid( const Data::ZAID& zaid,
                             const std::string& type ) const;

  // Verify consistent zaid
  void verifyConsistentZaid( const std::set<Data::ZAID>& zaids,
                             const std::string& type ) const;

  // Verify consistent temperature
  void verifyConsistentTemp(
                         const Data::NuclearDataProperties::Energy temp_in_mev,
                         const std::string& type );

  // Save the object to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the object from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The scattering center name
  std::string d_name;

  // The scattering center zaid
  Data::ZAID d_zaid;

  // The atomic weight ratio override
  boost::optional<double> d_atomic_weight_ratio;

  // The scattering center temperature
  boost::optional<Data::NuclearDataProperties::Energy> d_temperature;

  // The photoatomic data properties
  std::shared_ptr<const Data::PhotoatomicDataProperties> d_photoatomic_data_properties;

  // The adjoint photoatomic data properties
  std::shared_ptr<const Data::AdjointPhotoatomicDataProperties> d_adjoint_photoatomic_data_properties;

  // The electroatomic data properties
  std::shared_ptr<const Data::ElectroatomicDataProperties> d_electroatomic_data_properties;

  // The adjoint electroatomic data properties
  std::shared_ptr<const Data::AdjointElectroatomicDataProperties> d_adjoint_electroatomic_data_properties;

  // The nuclear data properties
  std::shared_ptr<const Data::NuclearDataProperties> d_nuclear_data_properties;

  // The thermal nuclear data properties
  std::shared_ptr<const Data::ThermalNuclearDataProperties> d_thermal_nuclear_data_properties;

  // The adjoint nuclear data properties
  std::shared_ptr<const Data::AdjointNuclearDataProperties> d_adjoint_nuclear_data_properties;

  // The adjoint thermal nuclear data properties
  std::shared_ptr<const Data::AdjointThermalNuclearDataProperties> d_adjoint_thermal_nuclear_data_properties;

  // The photonuclear data properties
  std::shared_ptr<const Data::PhotonuclearDataProperties> d_photonuclear_data_properties;

  // The adjoint photonuclear data properties
  std::shared_ptr<const Data::AdjointPhotonuclearDataProperties> d_adjoint_photonuclear_data_properties;
};

// Get the atomic weight
template<typename DataProperties>
double ScatteringCenterDefinition::getAtomicWeight(
                                       const DataProperties& properties ) const
{
  // Check for an override
  if( this->isAtomicWeightSet() )
    return this->getAtomicWeight();
  else
    return properties.atomicWeight().value();
}

// Get the atomic weight ratio
template<typename DataProperties>
double ScatteringCenterDefinition::getAtomicWeightRatio(
                                       const DataProperties& properties ) const
{
  // Check for an override
  if( this->isAtomicWeightSet() )
    return this->getAtomicWeightRatio();
  else
    return properties.atomicWeightRatio();
}

// Save the object to an archive
template<typename Archive>
void ScatteringCenterDefinition::save( Archive& ar,
                                       const unsigned version ) const
{
  ar & BOOST_SERIALIZATION_NVP( d_name );
  ar & BOOST_SERIALIZATION_NVP( d_zaid );
  ar & BOOST_SERIALIZATION_NVP( d_atomic_weight_ratio );
  ar & BOOST_SERIALIZATION_NVP( d_temperature );
  ar & BOOST_SERIALIZATION_NVP( d_photoatomic_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_photoatomic_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_electroatomic_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_electroatomic_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_nuclear_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_thermal_nuclear_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_nuclear_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_thermal_nuclear_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_photonuclear_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_photonuclear_data_properties );
}

// Load the object from an archive
template<typename Archive>
void ScatteringCenterDefinition::load( Archive& ar,
                                       const unsigned version )
{
  ar & BOOST_SERIALIZATION_NVP( d_name );
  ar & BOOST_SERIALIZATION_NVP( d_zaid );
  ar & BOOST_SERIALIZATION_NVP( d_atomic_weight_ratio );
  ar & BOOST_SERIALIZATION_NVP( d_temperature );
  ar & BOOST_SERIALIZATION_NVP( d_photoatomic_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_photoatomic_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_electroatomic_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_electroatomic_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_nuclear_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_thermal_nuclear_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_nuclear_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_thermal_nuclear_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_photonuclear_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_photonuclear_data_properties );
}

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_VERSION( ScatteringCenterDefinition, MonteCarlo, 0 );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ScatteringCenterDefinition );

#endif // end MONTE_CARLO_SCATTERING_CENTER_DEFINITION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ScatteringCenterDefinition.hpp
//---------------------------------------------------------------------------//
