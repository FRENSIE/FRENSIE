//---------------------------------------------------------------------------//
//!
//! \file   Data_ScatteringCenterPropertiesHelper.hpp
//! \author Alex Robinson
//! \brief  The scattering center properties helper class declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_SCATTERING_CENTER_PROPERTIES_HELPER_HPP
#define DATA_SCATTERING_CENTER_PROPERTIES_HELPER_HPP

// FRENSIE Includes
#include "Data_PhotoatomicDataProperties.hpp"

namespace Data{

//! The scattering center properties helper class
class ScatteringCenterPropertiesHelper
{

public:

  //! The atomic mass unit
  typedef PhotoatomicDataProperties::AtomicMassUnit AtomicMassUnit;

  //! The atomic mass quantity
  typedef PhotoatomicDataProperties::AtomicWeight AtomicWeight;

  //! Default constructor
  ScatteringCenterPropertiesHelper()
  { /* ... */ }

  //! Destructor
  virtual ~ScatteringCenterPropertiesHelper()
  { /* ... */ }

protected:

  //! The properties map type helper class
  template<typename Properties>
  struct PropertiesMapTypeHelper
  {
    //! The version properties map type
    typedef std::map<unsigned,std::shared_ptr<const Properties> > VersionPropertiesMap;

    //! The file type version properties map type
    typedef std::map<typename Properties::FileType,VersionPropertiesMap> FileTypeVersionPropertiesMap;
  };

  //! Check if there is data available with the desired format
  template<typename PropertiesMap>
  static bool dataAvailable( const PropertiesMap& properties,
                             const typename PropertiesMap::key_type file_type );

  //! Check if there is data available with the desired format and table version
  template<typename PropertiesMap>
  static bool dataAvailable( const PropertiesMap& properties,
                             const typename PropertiesMap::key_type file_type,
                             const unsigned table_version );

  //! Get the data file types
  template<typename PropertiesMap>
  static std::set<typename PropertiesMap::key_type> getDataFileTypes(
                                             const PropertiesMap& properties );

  //! Get the data file versions
  template<typename PropertiesMap>
  static std::set<unsigned> getDataFileVersions(
                            const PropertiesMap& properties,
                            const typename PropertiesMap::key_type file_type );

  //! Get the max data file version
  template<typename PropertiesMap>
  static unsigned getMaxDataFileVersion(
                            const PropertiesMap& properties,
                            const typename PropertiesMap::key_type file_type,
                            const std::string& type_name );

  //! Get the properties
  template<typename Properties, typename PropertiesMap>
  static const Properties& getProperties(
                              const PropertiesMap& properties,
                              const typename PropertiesMap::key_type file_type,
                              const unsigned table_version,
                              const std::string& type_name );

  //! Get the shared properties
  template<typename Properties, typename PropertiesMap>
  static const std::shared_ptr<const Properties>& getSharedProperties(
                              const PropertiesMap& properties,
                              const typename PropertiesMap::key_type file_type,
                              const unsigned table_version,
                              const std::string& type_name );

  //! Set the properties
  template<typename Properties, typename PropertiesMap>
  static void setPropertiesImpl(
                       PropertiesMap& properties,
                       const std::shared_ptr<const Properties>& new_properties,
                       const std::string& warning_tag,
                       const std::string& type_name );

  //! Print properties
  template<typename PropertiesMap>
  static void printProperties( const PropertiesMap& properties,
                               const std::string& type_name,
                               std::ostream& os );

  // Set the properties
  template<typename Properties, typename PropertiesMap>
  static void setProperties(
                       PropertiesMap& properties,
                       const std::shared_ptr<const Properties>& new_properties,
                       const AtomType expected_atom,
                       const std::string& warning_tag,
                       const std::string& type_name );
};

//! The invalid data error
class InvalidScatteringCenterPropertiesData : public std::runtime_error
{

public:

  //! Constructor
  InvalidScatteringCenterPropertiesData( const std::string& what )
    : std::runtime_error( what )
  { /* ... */ }
};

//! The invalid request error
class InvalidScatteringCenterPropertiesRequest : public std::runtime_error
{

public:

  //! Constructor
  InvalidScatteringCenterPropertiesRequest( const std::string& what )
    : std::runtime_error( what )
  { /* ... */ }
};
  
} // end Data namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Data_ScatteringCenterPropertiesHelper_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_SCATTERING_CENTER_PROPERTIES_HELPER_HPP

//---------------------------------------------------------------------------//
// end Data_ScatteringCenterPropertiesHelper.hpp
//---------------------------------------------------------------------------//
