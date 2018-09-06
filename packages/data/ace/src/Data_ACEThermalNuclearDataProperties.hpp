//---------------------------------------------------------------------------//
//!
//! \file   Data_ACEThermalNuclearDataProperties.hpp
//! \author Alex Robinson
//! \brief  The ACE thermal nuclear data properties class declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ACE_THERMAL_NUCLEAR_DATA_PROPERTIES_HPP
#define DATA_ACE_THERMAL_NUCLEAR_DATA_PROPERTIES_HPP

// FRENSIE Includes
#include "Data_ThermalNuclearDataProperties.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"

namespace Data{

//! The ACE thermal nuclear data properties class
class ACEThermalNuclearDataProperties : public ThermalNuclearDataProperties
{

public:

  //! Constructor
  template<template<typename...> class STLCompliantContainer>
  ACEThermalNuclearDataProperties( const STLCompliantContainer<Data::ZAID>& zaids,
                                   const Energy evaluation_temp,
                                   const boost::filesystem::path& file_path,
                                   const size_t file_start_line,
                                   const std::string& file_table_name );

  //! Constructor
  ACEThermalNuclearDataProperties( const std::set<Data::ZAID>& zaids,
                                   const Energy evaluation_temp,
                                   const boost::filesystem::path& file_path,
                                   const size_t file_start_line,
                                   const std::string& file_table_name );

  //! Destructor
  ~ACEThermalNuclearDataProperties()
  { /* ... */ }

  //! Get the name of the properties
  std::string name() const override;

  //! Check if the file specifies data for the ZAID of interest
  bool hasDataForZAID( const Data::ZAID& zaid ) const override;

  //! Get the ZAIDS that the file specifies data for
  std::set<Data::ZAID> zaids() const override;

  //! Get the nuclear data evaluation temperature (MeV)
  Energy evaluationTemperatureInMeV() const override;

  //! Get the nuclear data file type
  FileType fileType() const override;

  //! Get the nuclear data file path (relative to the data directory)
  boost::filesystem::path filePath() const override;

  //! Get the nuclear data file start line
  size_t fileStartLine() const override;

  //! Get the nuclear data file major version
  unsigned fileMajorVersion() const override;

  //! Get the nuclear data file version
  unsigned fileVersion() const override;

  //! Get the nuclear data file table name
  std::string tableName() const override;

  //! Clone the properties
  ACEThermalNuclearDataProperties* clone() const override;

private:

  // Default constructor
  ACEThermalNuclearDataProperties();

  // Copy constructor
  ACEThermalNuclearDataProperties( const ACEThermalNuclearDataProperties& other );

  // Assignment operator
  ACEThermalNuclearDataProperties& operator=( const ACEThermalNuclearDataProperties& other );

  // Save the properties to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the properties from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The zaids that the file specifies data for
  std::set<Data::ZAID> d_zaids;

  // The evaluation temperature (MeV)
  Energy d_evaluation_temp;

  // The file path (relative to the data directory)
  boost::filesystem::path d_file_path;

  // The file start line
  size_t d_file_start_line;

  // The file table name
  std::string d_file_table_name;

  // The properties name
  std::string d_name;

  // The file version
  unsigned d_file_version;
};

// Constructor
template<template<typename...> class STLCompliantContainer>
ACEThermalNuclearDataProperties::ACEThermalNuclearDataProperties(
                                const STLCompliantContainer<Data::ZAID>& zaids,
                                const Energy evaluation_temp,
                                const boost::filesystem::path& file_path,
                                const size_t file_start_line,
                                const std::string& file_table_name )
  : ACEThermalNuclearDataProperties( std::set<Data::ZAID>( zaids.begin(), zaids.end() ),
                                     evaluation_temp,
                                     file_path,
                                     file_start_line,
                                     file_table_name )
{ /* ... */ }

// Save the properties to an archive
template<typename Archive>
void ACEThermalNuclearDataProperties::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ThermalNuclearDataProperties );

  // Save the local member data
  ar & BOOST_SERIALIZATION_NVP( d_zaids );
  ar & BOOST_SERIALIZATION_NVP( d_evaluation_temp );

  std::string raw_path = d_file_path.string();

  ar & BOOST_SERIALIZATION_NVP( raw_path );
  ar & BOOST_SERIALIZATION_NVP( d_file_start_line );
  ar & BOOST_SERIALIZATION_NVP( d_file_table_name );
  ar & BOOST_SERIALIZATION_NVP( d_name );
  ar & BOOST_SERIALIZATION_NVP( d_file_version );
}

// Load the properties from an archive
template<typename Archive>
void ACEThermalNuclearDataProperties::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ThermalNuclearDataProperties );

  // Load the local member data
  ar & BOOST_SERIALIZATION_NVP( d_zaids );
  ar & BOOST_SERIALIZATION_NVP( d_evaluation_temp );

  std::string raw_path;
  ar & BOOST_SERIALIZATION_NVP( raw_path );

  d_file_path = raw_path;
  d_file_path.make_preferred();

  ar & BOOST_SERIALIZATION_NVP( d_file_start_line );
  ar & BOOST_SERIALIZATION_NVP( d_file_table_name );
  ar & BOOST_SERIALIZATION_NVP( d_name );
  ar & BOOST_SERIALIZATION_NVP( d_file_version );
}

} // end Data namespace

BOOST_SERIALIZATION_CLASS_VERSION( ACEThermalNuclearDataProperties, Data, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ACEThermalNuclearDataProperties, Data );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Data, ACEThermalNuclearDataProperties );

#endif // end DATA_ACE_THERMAL_NUCLEAR_DATA_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end Data_ACEThermalNuclearDataProperties.hpp
//---------------------------------------------------------------------------//
