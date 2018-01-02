//---------------------------------------------------------------------------//
//!
//! \file   Utility_ArchivableObject.hpp
//! \author Alex Robinson
//! \brief  Archivable object base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ARCHIVABLE_OBJECT_HPP
#define UTILITY_ARCHIVABLE_OBJECT_HPP

// FRENSIE Includes
#include "Utility_OArchivableObject.hpp"
#include "Utility_IArchivableObject.hpp"

namespace Utility{

//! The archivable object base class
template<typename DerivedType>
class ArchivableObject : public OArchivableObject<DerivedType>,
                         public IArchivableObject<DerivedType>
{

public:

  
  //! Constructor
  ArchivableObject()
  { /* ... */ }

  //! Destructor
  virtual ~ArchivableObject()
  { /* ... */ }

  //! The name that will be used when archiving the object
  virtual const char* getArchiveName() const = 0;

  //! The name that will be used when loading the object from an archive
  const char* getIArchiveName() const override
  { return this->getArchiveName(); }

  //! The name that will be used when archiving the object
  const char* getOArchiveName() const override
  { return this->getArchiveName(); }
};
  
} // end Utility namespace

#endif // end UTILITY_ARCHIVABLE_OBJECT_HPP

//---------------------------------------------------------------------------//
// end Utility_ArchivableObject.hpp
//---------------------------------------------------------------------------//
