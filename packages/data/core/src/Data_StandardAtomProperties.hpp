//---------------------------------------------------------------------------//
//!
//! \file   Data_StandardAtomProperties.hpp
//! \author Alex Robinson
//! \brief  The standard atom properties class declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_STANDARD_ATOM_PROPERTIES_HPP
#define DATA_STANDARD_ATOM_PROPERTIES_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "Data_ScatteringCenterProperties.hpp"
#include "Data_ExplicitTemplateInstantiationMacros.hpp"

namespace Data{

//! The standard atom properties
class StandardAtomProperties : public ScatteringCenterProperties
{

public:

  //! Constructor
  StandardAtomProperties( const std::string& name,
                          const ZAID& zaid,
                          const double atomic_weight );
                         
  //! Destructor
  ~StandardAtomProperties()
  { /* ... */ }

  //! Check if the scattering center is an atom
  bool isAtom() const override;

  //! Check if the scattering center is a nuclide
  virtual bool isNuclide() const override;

  //! Get the name of the properties
  std::string name() const override;

  //! Get the zaid
  Data::ZAID zaid() const override;

  //! Get the atomic weight
  virtual double atomicWeight() const override;

  //! Check if there is nuclear data
  virtual bool nuclearDataAvailable() const override;

  //! Check if there is nuclear data available at the evaluation temp
  virtual bool nuclearDataAvailable( const double evaluation_temp_in_mev ) const override;

  //! Check if the nuclear data is evaluated at discrete temps
  virtual bool nuclearDataEvaluatedAtDiscreteTemps() const override;

  //! Get the nuclear data evaluation temps (in MeV)
  virtual std::vector<double> getNuclearDataEvaluationTemps() const override;

  //! Get the nuclear data properties
  virtual const NuclearDataProperties* getNuclearDataProperties(
                                        const double evaluation_temp_in_mev,
                                        const bool find_exact ) const override;

  //! Check if there is any thermal nuclear data
  virtual bool thermalNuclearDataAvailable() const override;

  //! Check if there is thermal nuclear data available at the evaluation temp
  virtual bool thermalNuclearDataAvailable( const double evaluation_temp_in_mev ) const override;

  //! Check if the thermal nuclear data is evaluated at discrete temps
  virtual bool thermalNuclearDataEvaluatedAtDiscreteTemps() const override;

  //! Get the thermal nuclear data evaluation temps
  virtual std::vector<double> getThermalNuclearDataEvaluationTemps() const override;

  //! Get the thermal nuclear data properties
  virtual const ThermalNuclearDataProperties* getThermalNuclearDataProperties(
                                        const double evaluation_temp_in_mev,
                                        const bool find_exact ) const override;

  //! Check if there is adjoint nuclear data
  virtual bool adjointNuclearDataAvailable() const override;

  //! Check if there is adjoint nuclear data available at the evaluation temp
  virtual bool adjointNuclearDataAvailable( const double evaluation_temp_in_mev ) const override;

  //! Check if the adjoint nuclear data is evaluation at discrete temps
  virtual bool adjointNuclearDataEvaluatedAtDiscreteTemps() const override;

  //! Get the adjoint nuclear data evaluation temps
  virtual std::vector<double> getAdjointNuclearDataEvaluationTemps() const override;

  //! Get the adjoint nuclear data
  virtual const AdjointNuclearDataProperties* getAdjointNuclearDataProperties(
                                        const double evaluation_temp_in_mev,
                                        const bool find_exact ) const override;

  //! Check if there is any adjoint thermal nuclear data
  virtual bool adjointThermalNuclearDataAvailable() const override;

  //! Check if there is adjoint thermal nuclear data available at the evaluation temp
  virtual bool adjointThermalNuclearDataAvailable( const double evaluation_temp_in_mev ) const override;

  //! Check if the adjoint thermal nuclear data is evaluated at discrete temps
  virtual bool adjointThermalNuclearDataEvaluatedAtDiscreteTemps() const override;

  //! Get the adjoint thermal nuclear data evaluation temps
  virtual std::vector<double> getAdjointThermalNuclearDataEvaluationTemps() const override;

  //! Get the adjoint thermal nuclear data
  virtual const AdjointThermalNuclearDataProperties* getAdjointThermalNuclearDataProperties(
                                        const double evaluation_temp_in_mev,
                                        const bool find_exact ) const override;

  //! Check if there is photonuclear data
  virtual bool photonuclearDataAvailable() const override;

  //! Get the photonuclear data properties
  virtual const PhotonuclearDataProperties* getPhotonuclearDataProperties() const override;

  //! Check if there is adjoint photonuclear data
  virtual bool adjointPhotonuclearDataAvailable() const override;

  //! Get the adjoint photonuclear data
  virtual const AdjointPhotonuclearDataProperties* getAdjointPhotonuclearDataProperties() const override;

  //! Check if there is photoatomic data
  bool photoatomicDataAvailable() const override;

  //! Get the photoatomic data
  const PhotoatomicDataProperties* getPhotoatomicDataProperties() const override;

  //! Set the photoatomic data
  void setPhotoatomicDataProperties( const std::shared_ptr<const PhotoatomicDataProperties>& properties );

  //! Check if there is adjoint photoatomic data
  bool adjointPhotoatomicDataAvailable() const override;

  //! Get the adjoint photoatomic data properties
  const AdjointPhotoatomicDataProperties* getAdjointPhotoatomicDataProperties() const override;

  //! Set the adjoint photoatomic data properties
  void setAdjointPhotoatomicDataProperties( const std::shared_ptr<const AdjointPhotoatomicDataProperties>& properties );

  //! Check if there is electroatomic data
  bool electroatomicDataAvailable() const override;

  //! Get the electroatomic data properties
  const ElectroatomicDataProperties* getElectroatomicDataProperties() const override;

  //! Set the electroatomic data properties
  void setElectroatomicDataProperties( const std::shared_ptr<const ElectroatomicDataProperties>& properties );

  //! Check if there is adjoint electroatomic data
  bool adjointElectroatomicDataAvailable() const override;

  //! Get the adjoint electroatomic data properties
  const AdjointElectroatomicDataProperties* getAdjointElectroatomicDataProperties() const override;

  //! Set the adjoint electroatomic data properties
  void setAdjointElectroatomicDataProperties( const std::shared_ptr<const AdjointElectroatomicDataProperties>& properties );

  //! Clone the properties
  virtual StandardAtomProperties* clone() const override;

  //! Deep clone the properties
  virtual StandardAtomProperties* deepClone() const override;

protected:

  // Default constructor
  StandardAtomProperties();

  // Copy constructor
  StandardAtomProperties( const StandardAtomProperties& other );

  // Clone the stored properties
  static void cloneStoredAtomProperties(
                             const StandardAtomProperties& original_properties,
                             StandardAtomProperties& new_properties );

private:

  // Assignment operator
  StandardAtomProperties& operator=( const StandardAtomProperties& other );

  // Save the properties to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the properties from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The properties name
  std::string d_name;

  // The zaid
  Data::ZAID d_zaid;
  
  // The atomic weight
  double d_atomic_weight;

  // The photoatomic data properties
  std::shared_ptr<const PhotoatomicDataProperties>
  d_photoatomic_data_properties;

  // The adjoint photoatomic data properties
  std::shared_ptr<const AdjointPhotoatomicDataProperties>
  d_adjoint_photoatomic_data_properties;

  // The electroatomic data properties
  std::shared_ptr<const ElectroatomicDataProperties>
  d_electroatomic_data_properties;

  // The adjoint electroatomic data properties
  std::shared_ptr<const AdjointElectroatomicDataProperties>
  d_adjoint_electroatomic_data_properties;
};
  
} // end Data namespace

BOOST_SERIALIZATION_CLASS_VERSION( StandardAtomProperties, Data, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( StandardAtomProperties, Data );

EXTERN_EXPLICIT_DATA_CLASS_SAVE_LOAD_INST( StandardAtomProperties );

#endif // end DATA_STANDARD_ATOM_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end Data_StandardAtomProperties.hpp
//---------------------------------------------------------------------------//
