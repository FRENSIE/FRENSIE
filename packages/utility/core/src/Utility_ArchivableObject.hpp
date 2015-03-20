//---------------------------------------------------------------------------//
//!
//! \file   Utility_ArchivableObject.hpp
//! \author Alex Robinson
//! \brief  Archivable object base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ARCHIVABLE_OBJECT_HPP
#define UTILITY_ARCHIVABLE_OBJECT_HPP

namespace Utility{

//! The base class for archivable objects
class ArchivableObject
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
};

} // end Utility namespace

#endif // end UTILITY_ARCHIVABLE_OBJECT_HPP

//---------------------------------------------------------------------------//
// end ArchivableObject.hpp
//---------------------------------------------------------------------------//
