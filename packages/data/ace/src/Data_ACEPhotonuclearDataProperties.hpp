//---------------------------------------------------------------------------//
//!
//! \file   Data_ACEPhotonuclearDataProperties.hpp
//! \author Alex Robinson
//! \brief  The ACE photonuclear data properties class declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ACE_PHOTONUCLEAR_DATA_PROPERTIES_HPP
#define DATA_ACE_PHOTONUCLEAR_DATA_PROPERTIES_HPP

// FRENSIE Includes
#include "Data_PhotonuclearDataProperties.hpp"
#include "Data_ExplicitTemplateInstantiationMacros.hpp"
#include "Data_ACETableName.hpp"

namespace Data{

//! The ACE photonuclear data properties class
class ACEPhotonuclearDataProperties : public PhotonuclearDataProperties
{

public:

  //! Constructor
  ACEPhotonuclearDataProperties( const AtomicWeight atomic_weight,
                                 const boost::filesystem::path& file_path,
                                 const size_t file_start_line,
                                 const ACETableName& file_table_name );

  //! Destructor
  ~ACEPhotonuclearDataProperties()
  { /* ... */ }

  //! Get the ZAID that the file specifies data for
  Data::ZAID zaid() const override;

  //! Get the atomic weight of the nuclide that the file specifies data for
  AtomicWeight atomicWeight() const override;

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
  ACEPhotonuclearDataProperties* clone() const override;

private:

  // Default constructor
  ACEPhotonuclearDataProperties();

  // Copy constructor
  ACEPhotonuclearDataProperties( const ACEPhotonuclearDataProperties& other );

  // Assignment operator
  ACEPhotonuclearDataProperties& operator=( const ACEPhotonuclearDataProperties& other );

  // Save the properties to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the properties from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The atomic weight of the nuclide that the file specifies data for
  AtomicWeight d_atomic_weight;

  // The file path (relative to the data directory)
  boost::filesystem::path d_file_path;

  // The file start line
  size_t d_file_start_line;

  // The file table name
  ACETableName d_file_table_name;
};
  
} // end Data namespace

BOOST_SERIALIZATION_CLASS_VERSION( ACEPhotonuclearDataProperties, Data, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ACEPhotonuclearDataProperties, Data );
EXTERN_EXPLICIT_DATA_CLASS_SAVE_LOAD_INST( ACEPhotonuclearDataProperties );

#endif // end DATA_ACE_PHOTONUCLEAR_DATA_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end Data_ACEPhotonuclearDataProperties.hpp
//---------------------------------------------------------------------------//
