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
#include "Data_ExplicitTemplateInstantiationMacros.hpp"
#include "Data_ACETableName.hpp"

namespace Data{

//! The ACE nuclear data properties class
class ACENuclearDataProperties : public NuclearDataProperties
{

public:

  //! Constructor
  ACENuclearDataProperties( const double atomic_weight_ratio,
                            const double evaluation_temp_in_mev,
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
  double evaluationTemperatureInMeV() const override;

  //! Get the nuclear data file type
  FileType fileType() const override;

  //! Get the nuclear data file path (relative to the data directory)
  boost::filesystem::path filePath() const override;

  //! Get the nuclear data file start line
  size_t fileStartLine() const override;

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
  double d_evaluation_temp;

  // The file path (relative to the data directory)
  boost::filesystem::path d_file_path;

  // The file start line
  size_t d_file_start_line;

  // The file table name
  ACETableName d_file_table_name;
};
  
} // end Data namespace

BOOST_SERIALIZATION_CLASS_VERSION( ACENuclearDataProperties, Data, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ACENuclearDataProperties, Data );
EXTERN_EXPLICIT_DATA_CLASS_SAVE_LOAD_INST( ACENuclearDataProperties );

#endif // end DATA_ACE_NUCLEAR_DATA_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end Data_ACENuclearDataProperties.hpp
//---------------------------------------------------------------------------//
