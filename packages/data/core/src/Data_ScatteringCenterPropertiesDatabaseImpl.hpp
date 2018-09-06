//---------------------------------------------------------------------------//
//!
//! \file   Data_ScatteringCenterPropertiesDatabaseImpl.hpp
//! \author Alex Robinson
//! \brief  The scattering center properties database impl. declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_SCATTERING_CENTER_PROPERTIES_DATABASE_IMPL_HPP
#define DATA_SCATTERING_CENTER_PROPERTIES_DATABASE_IMPL_HPP

// Std Lib Includes
#include <string>
#include <memory>

// Boost Includes
#include <boost/filesystem/path.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/serialization/split_member.hpp>

// FRENSIE Includes
#include "Data_AtomProperties.hpp"
#include "Data_NuclideProperties.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_Map.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace Data{

//! The scattering center properties database
class ScatteringCenterPropertiesDatabaseImpl
{

public:

  //! Default constructor
  ScatteringCenterPropertiesDatabaseImpl();

  //! Destructor
  virtual ~ScatteringCenterPropertiesDatabaseImpl()
  { /* ... */ }

  //! Check if the atom properties exist
  bool doAtomPropertiesExist( const AtomType atom );

  //! Check if the atom properties exist
  bool doAtomPropertiesExist( const Data::ZAID zaid );
  
  //! Check if nuclide properties with zaid exist
  bool doNuclidePropertiesExist( const Data::ZAID zaid );

  //! Remove atom properties from the database
  void removeAtomProperties( const AtomType atom );

  //! Remove atom properties from the database
  void removeAtomProperties( const Data::ZAID zaid );
  
  //! Remove nuclide properties from the database
  void removeNuclideProperties( const Data::ZAID zaid );

  //! Remove empty properties from the database
  void removeEmptyProperties( const bool include_atom_properties = false );

  //! Return the desired properties
  const AtomProperties& getAtomProperties( const AtomType atom ) const;

  //! Return the desired properties
  AtomProperties& getAtomProperties( const AtomType atom );

  //! Return the desired properties
  const AtomProperties& getAtomProperties( const Data::ZAID zaid ) const;

  //! Return the desired properties
  AtomProperties& getAtomProperties( const Data::ZAID zaid );

  //! Initialize the atom properties
  AtomProperties& initializeAtomProperties( const AtomType atom,
                                            const double atomic_weight_ratio );

  //! Initialize the atom properties
  AtomProperties& initializeAtomProperties( const AtomType atom,
                                            const AtomProperties::AtomicWeight atomic_weight );

  //! Initialize the atom properties
  AtomProperties& initializeAtomProperties( const Data::ZAID zaid,
                                            const double atomic_weight_ratio );

  //! Initialize the atom properties
  AtomProperties& initializeAtomProperties( const Data::ZAID zaid,
                                            const AtomProperties::AtomicWeight atomic_weight );

  //! Return the nuclide properties
  const NuclideProperties& getNuclideProperties( const Data::ZAID zaid ) const;

  //! Return the nuclide properties
  NuclideProperties& getNuclideProperties( const Data::ZAID zaid );

  //! Initialize the nuclide properties
  NuclideProperties& initializeNuclideProperties( const Data::ZAID zaid,
                                                  const double atomic_weight_ratio );

  //! Initialize the nuclide properties
  NuclideProperties& initializeNuclideProperties( const Data::ZAID zaid,
                                                  const NuclideProperties::AtomicWeight atomic_weight );

  //! Return the number of stored atom properties
  size_t getNumberOfAtomProperties() const;

  //! Return the number of stored nuclide properties
  size_t getNumberOfNuclideProperties() const;

  //! List the atoms
  void listAtoms( std::ostream& os = std::cout ) const;

  //! Log the atoms
  void logAtoms() const;

  //! List the zaids
  void listZaids( std::ostream& os = std::cout ) const;

  //! List the zaids associated with the atom type
  void listZaids( const AtomType atom,
                  std::ostream& os = std::cout ) const;
  
  //! Log the zaids
  void logZaids() const;

  //! Log the properties zaids associated with the atom type
  void logZaids( const AtomType atom ) const;

private:

  // Initialize the atom properties
  template<typename WeightDataType>
  AtomProperties& initializeAtomPropertiesImpl( const AtomType atom,
                                                const WeightDataType weight_data );

  // Initialize the nuclide properties
  template<typename WeightDataType>
  NuclideProperties& initializeNuclidePropertiesImpl( const Data::ZAID zaid,
                                                      const WeightDataType weight_data );

  // Save the model to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the model from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The atom properties
  typedef std::map<Data::AtomType,std::unique_ptr<AtomProperties> > AtomPropertiesMap;
  AtomPropertiesMap d_atom_properties;

  // The nuclide properties
  typedef std::map<Data::ZAID,std::unique_ptr<NuclideProperties> > NuclidePropertiesMap;
  NuclidePropertiesMap d_nuclide_properties;
};
  
} // end Data namespace

BOOST_SERIALIZATION_CLASS_VERSION( ScatteringCenterPropertiesDatabaseImpl, Data, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ScatteringCenterPropertiesDatabaseImpl, Data );

EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Data, ScatteringCenterPropertiesDatabaseImpl );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Data_ScatteringCenterPropertiesDatabaseImpl_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_SCATTERING_CENTER_PROPERTIES_DATABASE_IMPL_HPP

//---------------------------------------------------------------------------//
// end Data_ScatteringCenterPropertiesDatabaseImpl.hpp
//---------------------------------------------------------------------------//
