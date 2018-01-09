//---------------------------------------------------------------------------//
//!
//! \file   Data_StandardNuclideProperties.hpp
//! \author Alex Robinson
//! \brief  The standard nuclide properties class declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_STANDARD_NUCLIDE_PROPERTIES_HPP
#define DATA_STANDARD_NUCLIDE_PROPERTIES_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "Data_StandardAtomProperties.hpp"
#include "Data_ExplicitTemplateInstantiationMacros.hpp"

namespace Data{

//! The standard nuclide properties
class StandardNuclideProperties : public StandardAtomProperties
{

public:

  //! Constructor
  StandardNuclideProperties( const std::string& name,
                             const ZAID& zaid,
                             const double atomic_weight_ratio );
  
  //! Destructor
  ~StandardNuclideProperties()
  { /* ... */ }

  //! Check if the scattering center is a nuclide
  bool isNuclide() const override;

  //! Get the atomic weight
  double atomicWeight() const override;

  //! Get the atomic weight ratio (atomic weight/neutron weight)
  double atomicWeightRatio() const override;

  //! Check if there is nuclear data
  bool nuclearDataAvailable() const override;

  //! Get the nuclear data properties
  const NuclearDataProperties* getNuclearDataProperties() const override;

  //! Set the nuclear data properties
  void setNuclearDataProperties( const std::shared_ptr<const NuclearDataProperties>& properties );

  //! Check if there is any thermal nuclear data
  bool thermalNuclearDataAvailable() const override;

  //! Get the thermal nuclear data properties
  const ThermalNuclearDataProperties* getThermalNuclearDataProperties() const override;

  //! Set the thermal nuclear data properties
  void setThermalNuclearDataProperties( const std::shared_ptr<const ThermalNuclearDataProperties>& properties );

  //! Check if there is adjoint nuclear data
  bool adjointNuclearDataAvailable() const override;

  //! Get the adjoint nuclear data properties
  const AdjointNuclearDataProperties* getAdjointNuclearDataProperties() const override;

  //! Set the adjoint nuclear data properties
  void setAdjointNuclearDataProperties( const std::shared_ptr<const AdjointNuclearDataProperties>& properties );

  //! Check if there is any adjoint thermal nuclear data
  bool adjointThermalNuclearDataAvailable() const override;

  //! Get the adjoint thermal nuclear data
  const AdjointThermalNuclearDataProperties* getAdjointThermalNuclearDataProperties() const override;

  //! Set the adjoint thermal nuclear data properties
  void setAdjointThermalNuclearDataProperties( const std::shared_ptr<const AdjointThermalNuclearDataProperties>& properties );

  //! Check if there is photonuclear data
  bool photonuclearDataAvailable() const override;

  //! Get the photonuclear data properties
  const PhotonuclearDataProperties* getPhotonuclearDataProperties() const override;

  //! Set the photonuclear data properties
  void setPhotonuclearDataProperties( const std::shared_ptr<const PhotonuclearDataProperties>& properties );

  //! Check if there is adjoint photonuclear data
  bool adjointPhotonuclearDataAvailable() const override;

  //! Get the adjoint photonuclear data
  const AdjointPhotonuclearDataProperties* getAdjointPhotonuclearDataProperties() const override;

  //! Set the adjoint photonuclear data properties
  void setAdjointPhotonuclearDataProperties( const std::shared_ptr<const AdjointPhotonuclearDataProperties>& properties );

  //! Clone the properties
  StandardNuclideProperties* clone() const override;

  //! Deep clone the properties
  StandardNuclideProperties* deepClone() const override;

private:

  // Default constructor
  StandardNuclideProperties();

  // Copy constructor
  StandardNuclideProperties( const StandardNuclideProperties& other );

  // Assignment operator
  StandardNuclideProperties& operator=( const StandardNuclideProperties& other );

  // Save the properties to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the properties from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The nuclear data properties
  std::shared_ptr<const NuclearDataProperties>
  d_nuclear_data_properties;

  // The thermal nuclear data properties
  std::shared_ptr<const ThermalNuclearDataProperties>
  d_thermal_nuclear_data_properties;

  // The adjoint nuclear data properties
  std::shared_ptr<const AdjointNuclearDataProperties>
  d_adjoint_nuclear_data_properties;

  // The thermal adjoint nuclear data properties
  std::shared_ptr<const AdjointThermalNuclearDataProperties>
  d_adjoint_thermal_nuclear_data_properties;

  // The photonuclear data properties
  std::shared_ptr<const PhotonuclearDataProperties>
  d_photonuclear_data_properties;

  // The adjoint photonuclear data properties
  std::shared_ptr<const AdjointPhotonuclearDataProperties>
  d_adjoint_photonuclear_data_properties;
};

} // end Data namespace

BOOST_SERIALIZATION_CLASS_VERSION( StandardNuclideProperties, Data, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( StandardNuclideProperties, Data );

EXTERN_EXPLICIT_DATA_CLASS_SAVE_LOAD_INST( StandardNuclideProperties );

#endif // end DATA_STANDARD_NUCLIDE_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end Data_StandardNuclideProperties.hpp
//---------------------------------------------------------------------------//
