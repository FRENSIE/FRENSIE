//---------------------------------------------------------------------------//
//!
//! \file   Utility_IArchivableObject.hpp
//! \author Alex Robinson
//! \brief  IArchivable object base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_IARCHIVABLE_OBJECT_HPP
#define UTILITY_IARCHIVABLE_OBJECT_HPP

// Std Lib Includes
#include <iostream>
#include <memory>

// Boost Includes
#include <boost/filesystem/path.hpp>

namespace boost{
namespace archive{
namespace detail{

class basic_pointer_iserializer;
  
}
}
}

namespace Utility{

//! The input archivable object base class
template<typename DerivedType>
class IArchivableObject
{

public:

  //! Constructor
  IArchivableObject()
  { /* ... */ }

  //! Destructor
  virtual ~IArchivableObject()
  { /* ... */ }

  //! The name that will be used when loading the object from an archive
  virtual const char* getIArchiveName() const = 0;

  //! Load the archived object
  void loadFromFile( const boost::filesystem::path& archive_name_with_path );

protected:

  //! Load the archived object (implementation)
  virtual void loadFromFileImpl( const boost::filesystem::path& archive_name_with_path );

  //! Reset the bpis pointer
  template<typename T>
  const boost::archive::detail::basic_pointer_iserializer* resetBpisPointer( const std::string& extension ) const;

  //! Restore the bpis pointer
  template<typename T>
  void restoreBpisPointer( const std::string& extension, const boost::archive::detail::basic_pointer_iserializer* bpis ) const;

private:

  // Archive the object using the required archive
  template<typename Archive>
  void loadFromArchive( Archive& archive );
};
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_IArchivableObject_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_IARCHIVABLE_OBJECT_HPP

//---------------------------------------------------------------------------//
// end Utility_IArchivableObject.hpp
//---------------------------------------------------------------------------//
