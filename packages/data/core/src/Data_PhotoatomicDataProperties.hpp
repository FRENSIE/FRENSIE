//---------------------------------------------------------------------------//
//!
//! \file   Data_PhotoatomicDataProperties.hpp
//! \author Alex Robinson
//! \brief  The photoatomic data properties class declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_PHOTOATOMIC_DATA_PROPERTIES_HPP
#define DATA_PHOTOATOMIC_DATA_PROPERTIES_HPP

// Std Lib Includes
#include <string>

// Boost Includes
#include <boost/filesystem/path.hpp>
#include <boost/serialization/split_member.hpp>

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace Data{

//! The photoatomic data properties base class
class PhotoatomicDataProperties
{

public:

  enum FileType{
    ACE_EPR_FILE,
    Native_EPR_FILE
  };

  //! Default constructor
  PhotoatomicDataProperties();

  //! Destructor
  virtual ~PhotoatomicDataProperties()
  { /* ... */ }

  //! Get the photoatomic data file type
  virtual FileType fileType() const = 0;

  //! Get the photoatomic data file path (relative to the data directory)
  virtual boost::filesystem::path filePath() const = 0;

  //! Get the photoatomic data file start line
  virtual size_t fileStartLine() const = 0;

  //! Get the photoatomic table name
  virtual std::string tableName() const = 0;

  //! Clone the properties
  virtual PhotoatomicDataProperties* clone() const = 0;

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

namespace Utility{

/*! \brief Specialization of Utility::ToStringTraits for 
 * Data::PhotoatomicDataProperties::FileType
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<Data::PhotoatomicDataProperties::FileType>
{
  //! Convert a Data::PhotoatomicDataProperties::FileType to a string
  static std::string toString( const Data::PhotoatomicDataProperties::FileType type );

  //! Place the Data::PhotoatomicDataProperties::FileType in a stream
  static void toStream( std::ostream& os, const Data::PhotoatomicDataProperties::FileType type );
};
  
} // end Utility namespace

namespace std{

//! Stream operator for printing Datea::PhotoatomicDataProperties::FileType enums
inline std::ostream& operator<<( std::ostream& os,
                                 const Data::PhotoatomicDataProperties::FileType type )
{
  Utility::toStream( os, type );

  return os;
}
  
} // end std namespace

BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS( PhotoatomicDataProperties, Data );
BOOST_SERIALIZATION_CLASS_VERSION( PhotoatomicDataProperties, Data, 0 );

#endif // end DATA_PHOTOATOMIC_DATA_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end Data_PhotoatomicDataProperties.hpp
//---------------------------------------------------------------------------//
