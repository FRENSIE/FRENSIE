//---------------------------------------------------------------------------//
//!
//! \file   Utility_SerializableObject.hpp
//! \author Alex Robinson
//! \brief  Serializable object base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_SERIALIZABLE_OBJECT_HPP
#define UTILITY_SERIALIZABLE_OBJECT_HPP

// Std Lib Includes
#include <string>

namespace Utility{

//! The base class for serializable objects
class SerializableObject
{

public:

  //! The archive types that are supported
  enum ArchiveType{
    ASCII_ARCHIVE=0,
    BINARY_ARCHIVE=1,
    XML_ARCHIVE=2
  };

  //! Export the data in the container to the desired archive type
  virtual void exportData( const std::string& archive_name,
			   const ArchiveType archive_type ) const = 0;
  
  //! Import data from the desired archive
  virtual void importData( const std::string& archive_name,
			   const ArchiveType archive_type ) = 0;

  //! Pack the data in the container into a string
  virtual std::string packDataInString() const = 0;

  //! Unpack the data from a string and store in the container
  virtual void unpackDataFromString( const std::string& packed_string ) = 0;
};

} // end Utility namespace

#endif // end UTILITY_SERIALIZABLE_OBJECT_HPP

//---------------------------------------------------------------------------//
// end Utility_SerializableObject.hpp
//---------------------------------------------------------------------------//
