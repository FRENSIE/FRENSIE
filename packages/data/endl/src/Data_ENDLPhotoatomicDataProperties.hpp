//---------------------------------------------------------------------------//
//!
//! \file   Data_ENDLPhotoatomicDataProperties.hpp
//! \author Alex Robinson
//! \brief  The ENDL photoatomic data properties class declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ENDL_PHOTOATOMIC_DATA_PROPERTIES_HPP
#define DATA_ENDL_PHOTOATOMIC_DATA_PROPERTIES_HPP

// FRENSIE Includes
#include "Data_PhotoatomicDataProperties.hpp"
#include "Data_ExplicitTemplateInstantiationMacros.hpp"

namespace Data{

//! The ENDL photoatomic data properties class
class ENDLPhotoatomicDataProperties : public PhotoatomicDataProperties
{

public:

  //! Constructor
  ENDLPhotoatomicDataProperties( const boost::filesystem::path& file_path,
                                 const unsigned file_version,
                                 const AtomType atom );

  //! Destructor
  ~ENDLPhotoatomicDataProperties()
  { /* ... */ }

  //! Get the atom that the file specifies data for
  AtomType atom() const override;

  //! Get the photoatomic data file type
  FileType fileType() const override;

  //! Get the photoatomic data file path (relative to the data directory)
  boost::filesystem::path filePath() const override;

  //! Get the photoatomic data file start line
  size_t fileStartLine() const override;

  //! Get the photoatomic data file version
  unsigned fileVersion() const override;

  //! Get the photoatomic table name
  std::string tableName() const override;

  //! Clone the properties
  ENDLPhotoatomicDataProperties* clone() const override;

private:

  // Default constructor
  ENDLPhotoatomicDataProperties();

  // Copy constructor
  ENDLPhotoatomicDataProperties( const ENDLPhotoatomicDataProperties& other );

  // Assignment operator
  ENDLPhotoatomicDataProperties& operator=( const ENDLPhotoatomicDataProperties& other );

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

  // The file version
  unsigned d_file_version;

  // The atom type
  AtomType d_atom;
};
  
} // end Data namespace

BOOST_SERIALIZATION_CLASS_VERSION( ENDLPhotoatomicDataProperties, Data, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ENDLPhotoatomicDataProperties, Data );
EXTERN_EXPLICIT_DATA_CLASS_SAVE_LOAD_INST( ENDLPhotoatomicDataProperties );

#endif // end DATA_ENDL_PHOTOATOMIC_DATA_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end Data_ENDLPhotoatomicDataProperties.hpp
//---------------------------------------------------------------------------//
