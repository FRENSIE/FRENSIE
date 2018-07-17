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
