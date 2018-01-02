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
#include "Data_PhotoatomicDataProperties.hpp"
#include "Data_AdjointPhotoatomicDataProperties.hpp"
#include "Data_ElectroatomicDataProperties.hpp"
#include "Data_AdjointElectroatomicDataProperties.hpp"
#include "Data_ExplicitTemplateInstantiationMacros.hpp"

namespace Data{

//! The standard atom properties
class StandardAtomProperties : public ScatteringCenterProperties
{

public:

  //! Partial constructor (forward data only)
  StandardAtomProperties(
                      const std::string& name,
                      const unsigned atomic_number,
                      const double atomic_weight,
                      const std::shared_ptr<const PhotoatomicDataProperties>&
                      photoatomic_data_properties,
                      const std::shared_ptr<const ElectroatomicDataProperties>&
                      electroatomic_data_properties );

  //! Complete constructor (forward and adjoint data)
  StandardAtomProperties(
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
               adjoint_electroatomic_data_properties );

  //! Destructor
  ~StandardAtomProperties()
  { /* ... */ }

  //! Check if the scattering center is an atom
  bool isAtom() const override;

  //! Check if the scattering center is a nuclide
  bool isNuclide() const override;

  //! Check if the scattering center is a mixture (or lattice)
  bool isMixture() const override;

  //! Get the name of the properties
  std::string name() const override;

  //! Get the atomic number(s)
  std::vector<unsigned> atomicNumbers() const override;

  //! Get the atomic mass number(s)
  std::vector<unsigned> atomicMassNumbers() const override;

  //! Get the isomer number(s)
  std::vector<unsigned> isomerNumbers() const override;

  //! Get the atomic weight(s)
  std::vector<double> atomicWeights() const override;

  //! Check if there is nuclear data
  bool nuclearDataAvailable() const override;

  //! Get the nuclear data properties
  const NuclearDataProperties* getNuclearDataProperties() const override;

  //! Check if there is adjoint nuclear data
  bool adjointNuclearDataAvailable() const override;

  //! Get the adjoint nuclear data
  const AdjointNuclearDataProperties* getAdjointNuclearDataProperties() const override;

  //! Check if there is photoatomic data
  bool photoatomicDataAvailable() const override;

  //! Get the photoatomic data
  const PhotoatomicDataProperties* getPhotoatomicDataProperties() const override;

  //! Check if there is adjoint photoatomic data
  bool adjointPhotoatomicDataAvailable() const override;

  //! Get the adjoint photoatomic data properties
  const AdjointPhotoatomicDataProperties* getAdjointPhotoatomicDataProperties() const override;

  //! Check if there is electroatomic data
  bool electroatomicDataAvailable() const override;

  //! Get the electroatomic data properties
  const ElectroatomicDataProperties* getElectroatomicDataProperties() const override;

  //! Check if there is adjoint electroatomic data
  bool adjointElectroatomicDataAvailable() const override;

  //! Get the adjoint electroatomic data properties
  const AdjointElectroatomicDataProperties* getAdjointElectroatomicDataProperties() const override;

  //! Clone the properties
  StandardAtomProperties* clone() const override;

  //! Deep clone the properties
  StandardAtomProperties* deepClone() const override;

private:

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

  // The atomic number
  unsigned d_atomic_number;

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
