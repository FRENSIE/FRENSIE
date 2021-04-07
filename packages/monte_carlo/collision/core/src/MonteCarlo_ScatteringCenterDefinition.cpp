//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ScatteringCenterDefinition.cpp
//! \author Alex Robinson
//! \brief  The scattering center definition def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_ScatteringCenterDefinition.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_StaticOutputFormatter.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

// Default constructor
ScatteringCenterDefinition::ScatteringCenterDefinition()
{ /* ... */ }

// Basic Constructor
ScatteringCenterDefinition::ScatteringCenterDefinition(
                                                       const Data::ZAID& zaid )
  : ScatteringCenterDefinition( zaid.toName(), zaid )
{ /* ... */ }

// Constructor
ScatteringCenterDefinition::ScatteringCenterDefinition(
                                                       const std::string& name,
                                                       const Data::ZAID& zaid )
  : d_name( name ),
    d_zaid( zaid ),
    d_atomic_weight_ratio(),
    d_temperature()
{
  // White space characters are not allowed in scattering center names
  TEST_FOR_EXCEPTION( d_name.empty(),
                      std::runtime_error,
                      "Scattering center names cannot be empty!" );
}

// Return the name
const std::string& ScatteringCenterDefinition::getName() const
{
  return d_name;
}

// Return the zaid
const Data::ZAID& ScatteringCenterDefinition::getZAID() const
{
  return d_zaid;
}

// Check if an atomic weight override has been set
/*! If the atomic weight is set it should be used when constructing the
 * scattering center instead of the atomic weights stored in the various
 * properties classes.
 */
bool ScatteringCenterDefinition::isAtomicWeightSet() const
{
  return d_atomic_weight_ratio != boost::none;
}

// Set the atomic weight override
void ScatteringCenterDefinition::setAtomicWeight( const double atomic_weight )
{
  TEST_FOR_EXCEPTION( atomic_weight <= 0.0,
                      std::runtime_error,
                      "The atomic weight ratio must be greater than 0.0!" );

  d_atomic_weight_ratio =
    atomic_weight/Utility::PhysicalConstants::neutron_rest_mass_amu;
}

// Set the atomic weight ratio override
void ScatteringCenterDefinition::setAtomicWeightRatio(
                                             const double atomic_weight_ratio )
{
  TEST_FOR_EXCEPTION( atomic_weight_ratio <= 0.0,
                      std::runtime_error,
                      "The atomic weight ratio must be greater than 0.0!" );

  d_atomic_weight_ratio = atomic_weight_ratio;
}

// Get the atomic weight override
double ScatteringCenterDefinition::getAtomicWeight() const
{
  return this->getAtomicWeightRatio()*
    Utility::PhysicalConstants::neutron_rest_mass_amu;
}

// Get the atomic weight ratio override
double ScatteringCenterDefinition::getAtomicWeightRatio() const
{
  TEST_FOR_EXCEPTION( !this->isAtomicWeightSet(),
                      std::runtime_error,
                      "The atomic weight has not been set!" );

  return d_atomic_weight_ratio.value();
}

// Check if there are photoatomic data properties
bool ScatteringCenterDefinition::hasPhotoatomicDataProperties() const
{
  return (bool)d_photoatomic_data_properties;
}

// Set the photoatomic data properties
void ScatteringCenterDefinition::setPhotoatomicDataProperties(
     const std::shared_ptr<const Data::PhotoatomicDataProperties>& properties )
{
  if( properties )
  {
    this->verifyConsistentAtom( properties->atom(),
                                "photoatomic data properties" );

    d_photoatomic_data_properties = properties;
  }
}

// Set the photoatomic data properties
void ScatteringCenterDefinition::setDataProperties(
     const std::shared_ptr<const Data::PhotoatomicDataProperties>& properties )
{
  this->setPhotoatomicDataProperties( properties );
}

// Get the photoatomic data properties
/*! \details If an atomic weight has been set for this definition, that atomic
 * weight will be returned. Otherwise, the atomic weight specified in the
 * PhotoatomicDataProperties will be returned.
 */
const Data::PhotoatomicDataProperties& ScatteringCenterDefinition::getPhotoatomicDataProperties(
                                                  double* atomic_weight ) const
{
  TEST_FOR_EXCEPTION( d_photoatomic_data_properties.get() == NULL,
                      std::logic_error,
                      "The photoatomic data properties have not been set!" );

  // Get the atomic weight
  if( atomic_weight )
    *atomic_weight = this->getAtomicWeight( *d_photoatomic_data_properties );

  return *d_photoatomic_data_properties;
}

// Check if there are adjoint photoatomic data properties
bool ScatteringCenterDefinition::hasAdjointPhotoatomicDataProperties() const
{
  return (bool)d_adjoint_photoatomic_data_properties;
}

// Set the adjoint photoatomic data properties
void ScatteringCenterDefinition::setAdjointPhotoatomicDataProperties(
           const std::shared_ptr<const Data::AdjointPhotoatomicDataProperties>&
           properties )
{
  if( properties )
  {
    this->verifyConsistentAtom( properties->atom(),
                                "adjoint photoatomic data properties" );

    d_adjoint_photoatomic_data_properties = properties;
  }
}

// Set the adjoint photoatomic data properties
void ScatteringCenterDefinition::setDataProperties(
           const std::shared_ptr<const Data::AdjointPhotoatomicDataProperties>&
           properties )
{
  this->setAdjointPhotoatomicDataProperties( properties );
}

// Get the adjoint photoatomic data properties
const Data::AdjointPhotoatomicDataProperties& ScatteringCenterDefinition::getAdjointPhotoatomicDataProperties(
                                                  double* atomic_weight ) const
{
  TEST_FOR_EXCEPTION( d_adjoint_photoatomic_data_properties.get() == NULL,
                      std::logic_error,
                      "The adjoint photoatomic data properties have not been "
                      "set!" );

  // Get the atomic weight
  if( atomic_weight )
  {
    *atomic_weight =
      this->getAtomicWeight( *d_adjoint_photoatomic_data_properties );
  }

  return *d_adjoint_photoatomic_data_properties;
}

// Check if there are electroatomic data properties
bool ScatteringCenterDefinition::hasElectroatomicDataProperties() const
{
  return (bool)d_electroatomic_data_properties;
}

// Set the electroatomic data properties
void ScatteringCenterDefinition::setElectroatomicDataProperties(
                const std::shared_ptr<const Data::ElectroatomicDataProperties>&
                properties )
{
  if( properties )
  {
    this->verifyConsistentAtom( properties->atom(),
                                "electroatomic data properties" );

    d_electroatomic_data_properties = properties;
  }
}

// Set the electroatomic data properties
void ScatteringCenterDefinition::setDataProperties(
                const std::shared_ptr<const Data::ElectroatomicDataProperties>&
                properties )
{
  this->setElectroatomicDataProperties( properties );
}

// Get the electroatomic data properties
const Data::ElectroatomicDataProperties& ScatteringCenterDefinition::getElectroatomicDataProperties(
                                                  double* atomic_weight ) const
{
  TEST_FOR_EXCEPTION( d_electroatomic_data_properties.get() == NULL,
                      std::logic_error,
                      "The electroatomic data properties have not been set!" );

  // Get the atomic weight
  if( atomic_weight )
    *atomic_weight = this->getAtomicWeight( *d_electroatomic_data_properties );

  return *d_electroatomic_data_properties;
}

// Check if there are adjoint electroatomic data properties
bool ScatteringCenterDefinition::hasAdjointElectroatomicDataProperties() const
{
  return (bool)d_adjoint_electroatomic_data_properties;
}

// Set the adjoint electroatomic data properties
void ScatteringCenterDefinition::setAdjointElectroatomicDataProperties(
         const std::shared_ptr<const Data::AdjointElectroatomicDataProperties>&
         properties )
{
  if( properties )
  {
    this->verifyConsistentAtom( properties->atom(),
                                "adjoint electroatomic data properties" );

    d_adjoint_electroatomic_data_properties = properties;
  }
}

// Set the adjoint electroatomic data properties
void ScatteringCenterDefinition::setDataProperties(
         const std::shared_ptr<const Data::AdjointElectroatomicDataProperties>&
         properties )
{
  this->setAdjointElectroatomicDataProperties( properties );
}

// Get the adjoint electroatomic data properties
const Data::AdjointElectroatomicDataProperties& ScatteringCenterDefinition::getAdjointElectroatomicDataProperties(
                                                  double* atomic_weight ) const
{
  TEST_FOR_EXCEPTION( d_adjoint_electroatomic_data_properties.get() == NULL,
                      std::logic_error,
                      "The adjoint electroatomic data properties have not been"
                      " set!" );

  // Get the atomic weight
  if( atomic_weight )
  {
    *atomic_weight =
      this->getAtomicWeight( *d_adjoint_electroatomic_data_properties );
  }

  return *d_adjoint_electroatomic_data_properties;
}

// Check if there are nuclear data properties
bool ScatteringCenterDefinition::hasNuclearDataProperties() const
{
  return (bool)d_nuclear_data_properties;
}

// Set the nuclear data properties
void ScatteringCenterDefinition::setNuclearDataProperties(
                      const std::shared_ptr<const Data::NuclearDataProperties>&
                      properties )
{
  if( properties )
  {
    this->verifyConsistentZaid( properties->zaid(),
                                "nuclear data properties" );
    this->verifyConsistentTemp( properties->evaluationTemperatureInMeV(),
                                "nuclear data properties" );

    d_nuclear_data_properties = properties;
  }
}

// Set the nuclear data properties
void ScatteringCenterDefinition::setDataProperties(
                      const std::shared_ptr<const Data::NuclearDataProperties>&
                      properties )
{
  this->setNuclearDataProperties( properties );
}

// Get the nuclear data properties
const Data::NuclearDataProperties& ScatteringCenterDefinition::getNuclearDataProperties(
                                            double* atomic_weight_ratio ) const
{
  TEST_FOR_EXCEPTION( d_nuclear_data_properties.get() == NULL,
                      std::logic_error,
                      "The nuclear data properties have not been set!" );

  // Get the atomic weight ratio
  if( atomic_weight_ratio )
  {
    *atomic_weight_ratio =
      this->getAtomicWeightRatio( *d_nuclear_data_properties );
  }

  return *d_nuclear_data_properties;
}

// Check if there are thermal nuclear data properties
bool ScatteringCenterDefinition::hasThermalNuclearDataProperties() const
{
  return (bool)d_thermal_nuclear_data_properties;
}

// Set the thermal nuclear data properties
void ScatteringCenterDefinition::setThermalNuclearDataProperties(
               const std::shared_ptr<const Data::ThermalNuclearDataProperties>&
               properties )
{
  if( properties )
  {
    this->verifyConsistentZaid( properties->zaids(),
                                "thermal nuclear data properties" );
    this->verifyConsistentTemp( properties->evaluationTemperatureInMeV(),
                                "thermal nuclear data properties" );

    d_thermal_nuclear_data_properties = properties;
  }
}

// Set the thermal nuclear data properties
void ScatteringCenterDefinition::setDataProperties(
               const std::shared_ptr<const Data::ThermalNuclearDataProperties>&
               properties )
{
  this->setThermalNuclearDataProperties( properties );
}

// Get the thermal nuclear data properties
const Data::ThermalNuclearDataProperties& ScatteringCenterDefinition::getThermalNuclearDataProperties() const
{
  TEST_FOR_EXCEPTION( d_thermal_nuclear_data_properties.get() == NULL,
                      std::logic_error,
                      "The thermal nuclear data properties have not been "
                      "set!" );

  return *d_thermal_nuclear_data_properties;
}

// Check if there are adjoint nuclear data properties
bool ScatteringCenterDefinition::hasAdjointNuclearDataProperties() const
{
  return (bool)d_adjoint_nuclear_data_properties;
}

// Set the adjoint nuclear data properties
void ScatteringCenterDefinition::setAdjointNuclearDataProperties(
               const std::shared_ptr<const Data::AdjointNuclearDataProperties>&
               properties )
{
  if( properties )
  {
    this->verifyConsistentZaid( properties->zaid(),
                                "adjoint nuclear data properties" );
    this->verifyConsistentTemp( properties->evaluationTemperatureInMeV(),
                                "adjoint nuclear data properties" );

    d_adjoint_nuclear_data_properties = properties;
  }
}

// Set the adjoint nuclear data properties
void ScatteringCenterDefinition::setDataProperties(
               const std::shared_ptr<const Data::AdjointNuclearDataProperties>&
               properties )
{
  this->setAdjointNuclearDataProperties( properties );
}

// Get the adjoint nuclear data properties
const Data::AdjointNuclearDataProperties& ScatteringCenterDefinition::getAdjointNuclearDataProperties(
                                            double* atomic_weight_ratio ) const
{
  TEST_FOR_EXCEPTION( d_adjoint_nuclear_data_properties.get() == NULL,
                      std::logic_error,
                      "The adjoint nuclear data properties have not been "
                      "set!" );

  // Get the atomic weight ratio
  if( atomic_weight_ratio )
  {
    *atomic_weight_ratio =
      this->getAtomicWeightRatio( *d_adjoint_nuclear_data_properties );
  }

  return *d_adjoint_nuclear_data_properties;
}

// Check if there are adjoint thermal nuclear data properties
bool ScatteringCenterDefinition::hasAdjointThermalNuclearDataProperties() const
{
  return (bool)d_adjoint_thermal_nuclear_data_properties;
}

// Set the adjoint thermal nuclear data properties
void ScatteringCenterDefinition::setAdjointThermalNuclearDataProperties(
        const std::shared_ptr<const Data::AdjointThermalNuclearDataProperties>&
        properties )
{
  if( properties )
  {
    this->verifyConsistentZaid( properties->zaids(),
                                "adjoint thermal nuclear data properties" );
    this->verifyConsistentTemp( properties->evaluationTemperatureInMeV(),
                                "adjoint thermal nuclear data properties" );

    d_adjoint_thermal_nuclear_data_properties = properties;
  }
}

// Set the adjoint thermal nuclear data properties
void ScatteringCenterDefinition::setDataProperties(
        const std::shared_ptr<const Data::AdjointThermalNuclearDataProperties>&
        properties )
{
  this->setAdjointThermalNuclearDataProperties( properties );
}

// Get the adjoint thermal nuclear data properties
const Data::AdjointThermalNuclearDataProperties& ScatteringCenterDefinition::getAdjointThermalNuclearDataProperties() const
{
  TEST_FOR_EXCEPTION( d_adjoint_thermal_nuclear_data_properties.get() == NULL,
                      std::logic_error,
                      "The adjoint thermal nuclear data properties have not "
                      "been set!" );

  return *d_adjoint_thermal_nuclear_data_properties;
}

// Check if there are photonuclear data properties
bool ScatteringCenterDefinition::hasPhotonuclearDataProperties() const
{
  return (bool)d_photonuclear_data_properties;
}

// Set the photonuclear data properties
void ScatteringCenterDefinition::setPhotonuclearDataProperties(
                 const std::shared_ptr<const Data::PhotonuclearDataProperties>&
                 properties )
{
  if( properties )
  {
    this->verifyConsistentZaid( properties->zaid(),
                                "photonuclear data properties" );

    d_photonuclear_data_properties = properties;
  }
}

// Set the photonuclear data properties
void ScatteringCenterDefinition::setDataProperties(
                 const std::shared_ptr<const Data::PhotonuclearDataProperties>&
                 properties )
{
  this->setPhotonuclearDataProperties( properties );
}

// Get the photonuclear data properties
const Data::PhotonuclearDataProperties& ScatteringCenterDefinition::getPhotonuclearDataProperties(
                                                  double* atomic_weight ) const
{
  TEST_FOR_EXCEPTION( d_photonuclear_data_properties.get() == NULL,
                      std::logic_error,
                      "The photonuclear data properties have not been set!" );

  // Get the atomic weight
  if( atomic_weight )
    *atomic_weight = this->getAtomicWeight( *d_photonuclear_data_properties );

  return *d_photonuclear_data_properties;
}

// Check if there are adjoint photonuclear data properties
bool ScatteringCenterDefinition::hasAdjointPhotonuclearDataProperties() const
{
  return (bool)d_adjoint_photonuclear_data_properties;
}

// Set the adjoint photonuclear data properties
void ScatteringCenterDefinition::setAdjointPhotonuclearDataProperties(
          const std::shared_ptr<const Data::AdjointPhotonuclearDataProperties>&
          properties )
{
  if( properties )
  {
    this->verifyConsistentZaid( properties->zaid(),
                                "adjoint photonuclear data properties" );

    d_adjoint_photonuclear_data_properties = properties;
  }
}

// Set the adjoint photonuclear data properties
void ScatteringCenterDefinition::setDataProperties(
          const std::shared_ptr<const Data::AdjointPhotonuclearDataProperties>&
          properties )
{
  this->setAdjointPhotonuclearDataProperties( properties );
}

// Get the adjoint photonuclear data properties
const Data::AdjointPhotonuclearDataProperties& ScatteringCenterDefinition::getAdjointPhotonuclearDataProperties(
                                                  double* atomic_weight ) const
{
  TEST_FOR_EXCEPTION( d_adjoint_photonuclear_data_properties.get() == NULL,
                      std::logic_error,
                      "The adjoint photonuclear data properties have not been "
                      "set!" );

  // Get the atomic weight
  if( atomic_weight )
  {
    *atomic_weight =
      this->getAtomicWeight( *d_adjoint_photonuclear_data_properties );
  }

  return *d_adjoint_photonuclear_data_properties;
}

// Verify consistent atom
void ScatteringCenterDefinition::verifyConsistentAtom(
                                                const Data::AtomType atom,
                                                const std::string& type ) const
{
  if( atom != d_zaid.atom() )
  {
    FRENSIE_LOG_TAGGED_WARNING( "ScatteringCenterDefinition",
                                "The " << type <<
                                " specify properties for " << atom <<
                                " and not " << d_zaid.atom() << "!" );
  }
}

// Verify consistent zaid
void ScatteringCenterDefinition::verifyConsistentZaid(
                                                const Data::ZAID& zaid,
                                                const std::string& type ) const
{
  if( zaid != d_zaid )
  {
    FRENSIE_LOG_TAGGED_WARNING( "ScatteringCenterDefinition",
                                "The " << type <<
                                " specify properties for " << zaid <<
                                " and not " << d_zaid << "!" );
  }
}

// Verify consistent zaid
void ScatteringCenterDefinition::verifyConsistentZaid(
                                             const std::set<Data::ZAID>& zaids,
                                             const std::string& type ) const
{
  if( zaids.find( d_zaid ) == zaids.end() )
  {
    FRENSIE_LOG_TAGGED_WARNING( "ScatteringCenterDefinition",
                                "The " << type <<
                                " do not specify properties for "
                                << d_zaid << "!" );
  }
}

// Verify consistent temperature
void ScatteringCenterDefinition::verifyConsistentTemp(
                         const Data::NuclearDataProperties::Energy temp_in_mev,
                         const std::string& type )
{
  // No temperature has been set - use the given temperature
  if( d_temperature == boost::none )
    d_temperature = temp_in_mev;
  else if( d_temperature.value() != temp_in_mev )
  {
    FRENSIE_LOG_TAGGED_WARNING( "ScatteringCenterDefinition",
                                "The " << type << " describe an evaluation at "
                                << temp_in_mev << " and not at the expected "
                                << d_temperature.value() << "!" );
  }
}

namespace Details{

//! Place the atomic data properties in a stream
template<typename DataProperties>
inline void atomicDataPropertiesToStreamImpl(
                      std::ostream& os,
                      const std::string& name,
                      const std::string& indent,
                      const Data::ZAID& reference_zaid,
                      const std::shared_ptr<const DataProperties>& properties )
{
  os << indent << name << ": ";

  if( properties )
  {
    if( properties->atom() == reference_zaid.atom() )
      os << properties->atom();
    else
      os << Utility::BoldMagenta(Utility::toString( properties->atom() ));

    os << " "
       << properties->fileType() << " version "
       << properties->fileVersion();

    if( !properties->tableName().empty() )
      os << " (" << Utility::Italicized(properties->tableName()) << ")";

    os << " located at "
       << Utility::Bold(properties->filePath().string()) << "\n";
  }
  else
    os << "Not Set\n";
}

//! Place the photonuclear data properties in a stream
template<typename DataProperties>
inline void photonuclearDataPropertiesToStreamImpl(
                      std::ostream& os,
                      const std::string& name,
                      const std::string& indent,
                      const Data::ZAID& reference_zaid,
                      const std::shared_ptr<const DataProperties>& properties )
{
  os << indent << name << ": ";

  if( properties )
  {
    if( properties->zaid() == reference_zaid )
      os << properties->zaid();
    else
      os << Utility::BoldMagenta(Utility::toString( properties->zaid() ));

    os << " "
       << properties->fileType() << " version "
       << properties->fileVersion();

    if( !properties->tableName().empty() )
      os << " (" << Utility::Italicized(properties->tableName()) << ")";

    os << " located at "
       << Utility::Bold(properties->filePath().string()) << "\n";
  }
  else
    os << "Not Set\n";
}

//! Place the nuclear data properties in a stream
template<typename DataProperties>
inline void nuclearDataPropertiesToStreamImpl(
                      std::ostream& os,
                      const std::string& name,
                      const std::string& indent,
                      const Data::ZAID& reference_zaid,
                      const std::shared_ptr<const DataProperties>& properties )
{
  os << indent << name << ": ";

  if( properties )
  {
    if( properties->zaid() == reference_zaid )
      os << properties->zaid();
    else
      os << Utility::BoldMagenta(Utility::toString( properties->zaid() ));

    os << " "
       << properties->fileType() << " version "
       << properties->fileVersion() << " @ "
       << properties->evaluationTemperature();

    if( !properties->tableName().empty() )
      os << " (" << Utility::Italicized(properties->tableName()) << ")";

    os << " located at "
       << Utility::Bold(properties->filePath().string()) << "\n";
  }
  else
    os << "Not Set\n";
}

//! Place the thermal nuclear data properties in a stream
template<typename DataProperties>
inline void thermalNuclearDataPropertiesToStreamImpl(
                      std::ostream& os,
                      const std::string& name,
                      const std::string& indent,
                      const Data::ZAID& reference_zaid,
                      const std::shared_ptr<const DataProperties>& properties )
{
  os << indent << name << ": ";

  if( properties )
  {
    if( properties->hasDataForZAID( reference_zaid ) )
      os << properties->name();
    else
      os << Utility::BoldMagenta(properties->name());

    os << " "
       << properties->fileType() << " version "
       << properties->fileVersion() << " @ "
       << properties->evaluationTemperature();

    if( !properties->tableName().empty() )
      os << " (" << Utility::Italicized(properties->tableName()) << ")";

    os << " located at "
       << Utility::Bold(properties->filePath().string()) << "\n";
  }
  else
    os << "Not Set\n";
}

} // end Details namespace

// Place the object in an output stream
void ScatteringCenterDefinition::toStream( std::ostream& os ) const
{
  os << Utility::Underlined(d_name) << ":\n";

  const std::string indent( "  " );

  os << indent << "zaid: " << d_zaid << "\n";

  Details::atomicDataPropertiesToStreamImpl( os, "photoatomic data", indent, d_zaid, d_photoatomic_data_properties );
  Details::atomicDataPropertiesToStreamImpl( os, "adjoint photoatomic data", indent, d_zaid, d_adjoint_photoatomic_data_properties );
  Details::atomicDataPropertiesToStreamImpl( os, "electroatomic data", indent, d_zaid, d_electroatomic_data_properties );
  Details::atomicDataPropertiesToStreamImpl( os, "adjoint electroatomic data", indent, d_zaid, d_adjoint_electroatomic_data_properties );

  Details::nuclearDataPropertiesToStreamImpl( os, "nuclear data", indent, d_zaid, d_nuclear_data_properties );
  Details::thermalNuclearDataPropertiesToStreamImpl( os, "thermal nuclear data", indent, d_zaid, d_thermal_nuclear_data_properties );
  Details::nuclearDataPropertiesToStreamImpl( os, "adjoint nuclear data", indent, d_zaid, d_adjoint_nuclear_data_properties );
  Details::thermalNuclearDataPropertiesToStreamImpl( os, "adjoint thermal nuclear data", indent, d_zaid, d_adjoint_thermal_nuclear_data_properties );

  Details::photonuclearDataPropertiesToStreamImpl( os, "photonuclear data", indent, d_zaid, d_photonuclear_data_properties );
  Details::photonuclearDataPropertiesToStreamImpl( os, "adjoint photonuclear data", indent, d_zaid, d_adjoint_photonuclear_data_properties );
}

EXPLICIT_CLASS_SAVE_LOAD_INST( ScatteringCenterDefinition );

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ScatteringCenterDefinition.cpp
//---------------------------------------------------------------------------//
