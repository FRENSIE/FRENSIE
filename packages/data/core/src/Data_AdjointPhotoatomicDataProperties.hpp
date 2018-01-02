//---------------------------------------------------------------------------//
//!
//! \file   Data_AdjointPhotoatomicDataProperties.hpp
//! \author Alex Robinson
//! \brief  The adjoint photoatomic data properties class declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ADJOINT_PHOTOATOMIC_DATA_PROPERTIES_HPP
#define DATA_ADJOINT_PHOTOATOMIC_DATA_PROPERTIES_HPP

// Boost Includes
#include <boost/filesystem/path.hpp>
#include <boost/serialization/split_member.hpp>

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace Data{

//! The adjoint photoatomic data properties base class
class AdjointPhotoatomicDataProperties
{

public:

  enum FileType{
    Native_EPR_FILE
  };

  //! Default constructor
  AdjointPhotoatomicDataProperties();

  //! Destructor
  virtual ~AdjointPhotoatomicDataProperties()
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
  virtual AdjointPhotoatomicDataProperties* clone() const = 0;

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
 * Data::AdjointPhotoatomicDataProperties::FileType
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<Data::AdjointPhotoatomicDataProperties::FileType>
{
  //! Convert a Data::AdjointPhotoatomicDataProperties::FileType to a string
  static std::string toString( const Data::AdjointPhotoatomicDataProperties::FileType type );

  //! Place the Data::AdjointPhotoatomicDataProperties::FileType in a stream
  static void toStream( std::ostream& os, const Data::AdjointPhotoatomicDataProperties::FileType type );
};
  
} // end Utility namespace

namespace std{

//! Stream operator for printing Datea::AdjointPhotoatomicDataProperties::FileType enums
inline std::ostream& operator<<( std::ostream& os,
                                 const Data::AdjointPhotoatomicDataProperties::FileType type )
{
  Utility::toStream( os, type );

  return os;
}
  
} // end std namespace

BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS( AdjointPhotoatomicDataProperties, Data );
BOOST_SERIALIZATION_CLASS_VERSION( AdjointPhotoatomicDataProperties, Data, 0 );

#endif // end DATA_ADJOINT_PHOTOATOMIC_DATA_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end Data_AdjointPhotoatomicDataProperties.hpp
//---------------------------------------------------------------------------//
