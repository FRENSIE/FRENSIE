//---------------------------------------------------------------------------//
//!
//! \file   Data_ACEElectroatomicDataProperties.hpp
//! \author Alex Robinson
//! \brief  The ACE electroatomic data properties class declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ACE_ELECTROATOMIC_DATA_PROPERTIES_HPP
#define DATA_ACE_ELECTROATOMIC_DATA_PROPERTIES_HPP

// FRENSIE Includes
#include "Data_ElectroatomicDataProperties.hpp"
#include "Data_ExplicitTemplateInstantiationMacros.hpp"
#include "Data_ACETableName.hpp"

namespace Data{

//! The ACE electroatomic data properties class
class ACEElectroatomicDataProperties : public ElectroatomicDataProperties
{

public:

  //! Constructor
  ACEElectroatomicDataProperties( const boost::filesystem::path& file_path,
                                  const size_t file_start_line,
                                  const ACETableName& file_table_name );
  
  //! Destructor
  ~ACEElectroatomicDataProperties()
  { /* ... */ }

  //! Get the atom that the file specifies data for
  AtomType atom() const override;

  //! Get the electroatomic data file type
  FileType fileType() const override;

  //! Get the electroatomic data file path (relative to the data directory)
  boost::filesystem::path filePath() const override;

  //! Get the electroatomic data file start line
  size_t fileStartLine() const override;

  //! Get the photoatomic data file version
  size_t fileVersion() const override;

  //! Get the electroatomic table name
  std::string tableName() const override;

  //! Clone the properties
  ACEElectroatomicDataProperties* clone() const override;

private:

  // Default constructor
  ACEElectroatomicDataProperties();

  // Copy constructor
  ACEElectroatomicDataProperties( const ACEElectroatomicDataProperties& other );

  // Assignment operator
  ACEElectroatomicDataProperties& operator=( const ACEElectroatomicDataProperties& other );

  // Save the properties to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the properties from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The file path (relative to the data directory)
  boost::filesystem::path d_file_path;

  // The file start line
  size_t d_file_start_line;

  // The file table name
  ACETableName d_file_table_name;
};
  
} // end Data namespace

BOOST_SERIALIZATION_CLASS_VERSION( ACEElectroatomicDataProperties, Data, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ACEElectroatomicDataProperties, Data );
EXTERN_EXPLICIT_DATA_CLASS_SAVE_LOAD_INST( ACEElectroatomicDataProperties );

#endif // end DATA_ACE_ELECTROATOMIC_DATA_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end Data_ACEElectroatomicDataProperties.hpp
//---------------------------------------------------------------------------//
