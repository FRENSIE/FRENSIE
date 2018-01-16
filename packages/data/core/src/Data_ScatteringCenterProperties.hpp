//---------------------------------------------------------------------------//
//!
//! \file   Data_ScatteringCenterProperties.hpp
//! \author Alex Robinson
//! \brief  The scattering center properties class declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_SCATTERING_CENTER_PROPERTIES_HPP
#define DATA_SCATTERING_CENTER_PROPERTIES_HPP

// Boost Includes
#include <boost/filesystem/path.hpp>

// FRENSIE Includes
#include "Data_ZAID.hpp"
#include "Data_NuclearDataProperties.hpp"
#include "Data_ThermalNuclearDataProperties.hpp"
#include "Data_AdjointNuclearDataProperties.hpp"
#include "Data_AdjointThermalNuclearDataProperties.hpp"
#include "Data_PhotonuclearDataProperties.hpp"
#include "Data_AdjointPhotonuclearDataProperties.hpp"
#include "Data_PhotoatomicDataProperties.hpp"
#include "Data_AdjointPhotoatomicDataProperties.hpp"
#include "Data_ElectroatomicDataProperties.hpp"
#include "Data_AdjointElectroatomicDataProperties.hpp"

namespace Data{

//! The scattering center properties base class
class ScatteringCenterProperties
{

public:

  //! The atomic mass unit
  typedef PhotonuclearDataProperties::AtomicMassUnit AtomicMassUnit;

  //! The atomic mass quantity
  typedef PhotonuclearDataProperties::AtomicWeight AtomicWeight;

  //! The energy unit
  typedef NuclearDataProperties::EnergyUnit EnergyUnit;

  //! The energy quantity
  typedef NuclearDataProperties::Energy Energy;

  //! The temperature unit
  typedef NuclearDataProperties::TemperatureUnit TemperatureUnit;

  //! The temperature quantity
  typedef NuclearDataProperties::Temperature Temperature;

  //! Default constructor
  ScatteringCenterProperties();

  //! Destructor
  virtual ~ScatteringCenterProperties()
  { /* ... */ }

  //! Check if the scattering center is an atom
  virtual bool isAtom() const = 0;

  //! Check if the scattering center is a nuclide
  virtual bool isNuclide() const = 0;

  //! Get the name of the properties
  virtual std::string name() const = 0;

  //! Get the zaid
  virtual Data::ZAID zaid() const = 0;

  //! Get the atomic weight
  virtual AtomicWeight atomicWeight() const = 0;

  //! Get the atomic weight ratio (atomic weight/neutron weight)
  virtual double atomicWeightRatio() const;

  //! Check if there is nuclear data
  virtual bool nuclearDataAvailable() const = 0;

  //! Check if there is nuclear data available at the evaluation temp
  virtual bool nuclearDataAvailable( const Energy evaluation_temp ) const = 0;

  //! Check if the nuclear data is evaluated at discrete temps
  virtual bool nuclearDataEvaluatedAtDiscreteTemps() const = 0;

  //! Get the nuclear data evaluation temps
  virtual std::vector<Energy> getNuclearDataEvaluationTempsInMeV() const = 0;

  //! Get the nuclear data evaluation temps
  virtual std::vector<Temperature> getNuclearDataEvaluationTemps() const;

  //! Get the nuclear data properties
  virtual const NuclearDataProperties* getNuclearDataProperties(
                                             const Energy evaluation_temp,
                                             const bool find_exact ) const = 0;

  //! Get the nuclear data properties (closest to evaluation temp)
  const NuclearDataProperties* getNuclearDataProperties(
                                          const Energy evaluation_temp ) const;
                                   
  //! Check if there is thermal nuclear data
  virtual bool thermalNuclearDataAvailable() const = 0;

  //! Check if there is thermal nuclear data available at the evaluation temp
  virtual bool thermalNuclearDataAvailable( const Energy evaluation_temp ) const = 0;

  //! Check if the thermal nuclear data is evaluated at discrete temps
  virtual bool thermalNuclearDataEvaluatedAtDiscreteTemps() const = 0;

  //! Get the thermal nuclear data evaluation temps
  virtual std::vector<Energy> getThermalNuclearDataEvaluationTempsInMeV() const = 0;

  //! Get the thermal nuclear data evaluation temps
  virtual std::vector<Temperature> getThermalNuclearDataEvaluationTemps() const;

  //! Get the thermal nuclear data properties
  virtual const ThermalNuclearDataProperties* getThermalNuclearDataProperties(
                                             const Energy evaluation_temp,
                                             const bool find_exact ) const = 0;

  //! Get the thermal nuclear data properties
  const ThermalNuclearDataProperties* getThermalNuclearDataProperties(
                                          const Energy evaluation_temp ) const;
  
  //! Check if there is adjoint nuclear data
  virtual bool adjointNuclearDataAvailable() const = 0;

  //! Check if there is adjoint nuclear data available at the evaluation temp
  virtual bool adjointNuclearDataAvailable( const Energy evaluation_temp ) const = 0;

  //! Check if the adjoint nuclear data is evaluation at discrete temps
  virtual bool adjointNuclearDataEvaluatedAtDiscreteTemps() const = 0;

  //! Get the adjoint nuclear data evaluation temps
  virtual std::vector<Energy> getAdjointNuclearDataEvaluationTempsInMeV() const = 0;

  //! Get the adjoint nuclear data evaluation temps
  virtual std::vector<Temperature> getAdjointNuclearDataEvaluationTemps() const;

  //! Get the adjoint nuclear data
  virtual const AdjointNuclearDataProperties* getAdjointNuclearDataProperties(
                                             const Energy evaluation_temp,
                                             const bool find_exact ) const = 0;

  //! Get the adjoint nuclear data
  const AdjointNuclearDataProperties* getAdjointNuclearDataProperties(
                                          const Energy evaluation_temp ) const;

  //! Check if there is adjoint thermal nuclear data
  virtual bool adjointThermalNuclearDataAvailable() const = 0;

  //! Check if there is adjoint thermal nuclear data available at the evaluation temp
  virtual bool adjointThermalNuclearDataAvailable( const Energy evaluation_temp ) const = 0;

  //! Check if the adjoint thermal nuclear data is evaluated at discrete temps
  virtual bool adjointThermalNuclearDataEvaluatedAtDiscreteTemps() const = 0;

  //! Get the adjoint thermal nuclear data evaluation temps
  virtual std::vector<Energy> getAdjointThermalNuclearDataEvaluationTempsInMeV() const = 0;

  //! Get the adjoint thermal nuclear data evaluation temps
  virtual std::vector<Temperature> getAdjointThermalNuclearDataEvaluationTemps() const;

  //! Get the adjoint thermal nuclear data
  virtual const AdjointThermalNuclearDataProperties* getAdjointThermalNuclearDataProperties(
                                             const Energy evaluation_temp,
                                             const bool find_exact ) const = 0;

  //! Get the adjoint thermal nuclear data
  const AdjointThermalNuclearDataProperties* getAdjointThermalNuclearDataProperties(
                                          const Energy evaluation_temp ) const;

  //! Check if there is photonuclear data
  virtual bool photonuclearDataAvailable() const = 0;

  //! Get the photonuclear data properties
  virtual const PhotonuclearDataProperties* getPhotonuclearDataProperties() const = 0;

  //! Check if there is adjoit photonuclear data
  virtual bool adjointPhotonuclearDataAvailable() const = 0;

  //! Get the adjoint photonuclear data properties
  virtual const AdjointPhotonuclearDataProperties* getAdjointPhotonuclearDataProperties() const = 0;

  //! Check if there is photoatomic data
  virtual bool photoatomicDataAvailable() const = 0;

  //! Get the photoatomic data
  virtual const PhotoatomicDataProperties* getPhotoatomicDataProperties() const = 0;

  //! Check if there is adjoint photoatomic data
  virtual bool adjointPhotoatomicDataAvailable() const = 0;

  //! Get the adjoint photoatomic data properties
  virtual const AdjointPhotoatomicDataProperties* getAdjointPhotoatomicDataProperties() const = 0;

  //! Check if there is electroatomic data
  virtual bool electroatomicDataAvailable() const = 0;

  //! Get the electroatomic data properties
  virtual const ElectroatomicDataProperties* getElectroatomicDataProperties() const = 0;

  //! Check if there is adjoint electroatomic data
  virtual bool adjointElectroatomicDataAvailable() const = 0;

  //! Get the adjoint electroatomic data properties
  virtual const AdjointElectroatomicDataProperties* getAdjointElectroatomicDataProperties() const = 0;

  //! Clone the properties
  virtual ScatteringCenterProperties* clone() const = 0;

  //! Deep clone the properties
  virtual ScatteringCenterProperties* deepClone() const;

private:

  // Save the properties to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const
  { /* ... */ }

  // Load the properties from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version )
  { /* ... */ }

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};
  
} // end Data namespace

BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS( ScatteringCenterProperties, Data );
BOOST_SERIALIZATION_CLASS_VERSION( ScatteringCenterProperties, Data, 0 );

#endif // end DATA_SCATTERING_CENTER_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end Data_ScatteringCenterProperties.hpp
//---------------------------------------------------------------------------//
