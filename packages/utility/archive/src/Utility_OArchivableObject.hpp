//---------------------------------------------------------------------------//
//!
//! \file   Utility_OArchivableObject.hpp
//! \author Alex Robinson
//! \brief  OArchivable object base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_OARCHIVABLE_OBJECT_HPP
#define UTILITY_OARCHIVABLE_OBJECT_HPP

// Std Lib Includes
#include <iostream>
#include <memory>

// Boost Includes
#include <boost/filesystem/path.hpp>

namespace boost{
namespace archive{
namespace detail{
  
class basic_pointer_oserializer;

}
}
}

namespace Utility{

//! The output archivable object base class
template<typename DerivedType>
class OArchivableObject
{

public:

  //! Constructor
  OArchivableObject()
  { /* ... */ }

  //! Destructor
  virtual ~OArchivableObject()
  { /* ... */ }

  //! The name that will be used when archiving the object
  virtual const char* getOArchiveName() const = 0;

  //! Archive the object
  void saveToFile( const boost::filesystem::path& archive_name_with_path,
                   const bool overwrite = false ) const;

protected:

  //! Archive the object (implementation)
  virtual void saveToFileImpl( const boost::filesystem::path& archive_name_with_path,
                               const bool overwrite ) const;

  //! Reset the bpos pointer
  template<typename T>
  const boost::archive::detail::basic_pointer_oserializer* resetBposPointer( const std::string& extension ) const;

  //! Restore the bpos pointer
  template<typename T>
  void restoreBposPointer( const std::string& extension, const boost::archive::detail::basic_pointer_oserializer* bpos ) const;

private:

  // Archive the object using the required archive
  template<typename Archive>
  void saveToArchive( Archive& archive ) const;
};
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_OArchivableObject_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_OARCHIVABLE_OBJECT_HPP

//---------------------------------------------------------------------------//
// end Utility_OArchivableObject.hpp
//---------------------------------------------------------------------------//
