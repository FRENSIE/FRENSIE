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
#include "Data_AtomType.hpp"
#include "Data_NuclearDataProperties.hpp"
#include "Data_AdjointNuclearDataProperties.hpp"
#include "Data_PhotoatomicDataProperties.hpp"
#include "Data_AdjointPhotoatomicDataProperties.hpp"
#include "Data_ElectroatomicDataProperties.hpp"
#include "Data_AdjointElectroatomicDataProperties.hpp"

namespace Data{

//! The scattering center properties base class
class ScatteringCenterProperties
{

public:

  //! Default constructor
  ScatteringCenterProperties();

  //! Destructor
  virtual ~ScatteringCenterProperties()
  { /* ... */ }

  //! Check if the scattering center is an atom
  virtual bool isAtom() const = 0;

  //! Check if the scattering center is a nuclide
  virtual bool isNuclide() const = 0;

  /*! \brief Check if the scattering center is a mixture, compound or lattice
   * (or a single nuclide within one of these).
   */
  virtual bool isMixture() const = 0;

  //! Get the name of the properties
  virtual std::string name() const = 0;

  //! Get the atom type(s)
  std::vector<AtomType> atoms() const;

  //! Get the atomic number(s)
  virtual std::vector<unsigned> atomicNumbers() const = 0;

  //! Get the atomic mass number(s)
  virtual std::vector<unsigned> atomicMassNumbers() const = 0;

  //! Get the isomer number(s)
  virtual std::vector<unsigned> isomerNumbers() const = 0;

  //! Get the atomic weight(s)
  virtual std::vector<double> atomicWeights() const = 0;

  //! Get the atomic weight ratio(s) (atomic weight/neutron weight)
  virtual std::vector<double> atomicWeightRatios() const;
  
  //! Check if there is nuclear data
  virtual bool nuclearDataAvailable() const = 0;

  //! Get the nuclear data properties
  virtual const NuclearDataProperties* getNuclearDataProperties() const = 0;

  //! Check if there is adjoint nuclear data
  virtual bool adjointNuclearDataAvailable() const = 0;

  //! Get the adjoint nuclear data
  virtual const AdjointNuclearDataProperties* getAdjointNuclearDataProperties() const = 0;

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
