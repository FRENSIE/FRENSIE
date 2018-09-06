//---------------------------------------------------------------------------//
//!
//! \file   Data_ACENuclearDataProperties.hpp
//! \author Alex Robinson
//! \brief  The ACE nuclear data properties class declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ACE_NUCLEAR_DATA_PROPERTIES_HPP
#define DATA_ACE_NUCLEAR_DATA_PROPERTIES_HPP

// FRENSIE Includes
#include "Data_NuclearDataProperties.hpp"
#include "Data_ACETableName.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"

namespace Data{

//! The ACE nuclear data properties class
class ACENuclearDataProperties : public NuclearDataProperties
{

public:

  //! Constructor
  ACENuclearDataProperties( const double atomic_weight_ratio,
                            const Energy evaluation_temp,
                            const boost::filesystem::path& file_path,
                            const size_t file_start_line,
                            const ACETableName& file_table_name );

  //! Destructor
  ~ACENuclearDataProperties()
  { /* ... */ }

  //! Get the ZAID that the file specifies data for
  Data::ZAID zaid() const override;

  //! Get the atomic weight ratio of the nuclide that the file specifies data for
  double atomicWeightRatio() const override;

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
  ACENuclearDataProperties* clone() const override;

private:

  // Default constructor
  ACENuclearDataProperties();

  // Copy constructor
  ACENuclearDataProperties( const ACENuclearDataProperties& other );

  // Assignment operator
  ACENuclearDataProperties& operator=( const ACENuclearDataProperties& other );

  // Save the properties to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the properties from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The atomic weight ratio of the nuclide that the file specifies data for
  double d_atomic_weight_ratio;

  // The evaluation temperature (MeV)
  Energy d_evaluation_temp;

  // The file path (relative to the data directory)
  boost::filesystem::path d_file_path;

  // The file start line
  size_t d_file_start_line;

  // The file table name
  ACETableName d_file_table_name;
};

// Save the properties to an archive
template<typename Archive>
void ACENuclearDataProperties::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( NuclearDataProperties );

  // Save the local member data
  ar & BOOST_SERIALIZATION_NVP( d_atomic_weight_ratio );
  ar & BOOST_SERIALIZATION_NVP( d_evaluation_temp );

  std::string raw_path = d_file_path.string();

  ar & BOOST_SERIALIZATION_NVP( raw_path );
  ar & BOOST_SERIALIZATION_NVP( d_file_start_line );
  ar & BOOST_SERIALIZATION_NVP( d_file_table_name );
}

// Load the properties from an archive
template<typename Archive>
void ACENuclearDataProperties::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( NuclearDataProperties );

  // Load the local member data
  ar & BOOST_SERIALIZATION_NVP( d_atomic_weight_ratio );
  ar & BOOST_SERIALIZATION_NVP( d_evaluation_temp );

  std::string raw_path;
  ar & BOOST_SERIALIZATION_NVP( raw_path );

  d_file_path = raw_path;
  d_file_path.make_preferred();

  ar & BOOST_SERIALIZATION_NVP( d_file_start_line );
  ar & BOOST_SERIALIZATION_NVP( d_file_table_name );
}
  
} // end Data namespace

BOOST_SERIALIZATION_CLASS_VERSION( ACENuclearDataProperties, Data, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ACENuclearDataProperties, Data );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Data, ACENuclearDataProperties );

#endif // end DATA_ACE_NUCLEAR_DATA_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end Data_ACENuclearDataProperties.hpp
//---------------------------------------------------------------------------//
