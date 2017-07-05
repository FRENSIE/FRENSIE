//---------------------------------------------------------------------------//
//!
//! \file   Utility_StandardArchivableObject.hpp
//! \author Alex Robinson
//! \brief  Standard archivable object base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_STANDARD_ARCHIVABLE_OBJECT_HPP
#define UTILITY_STANDARD_ARCHIVABLE_OBJECT_HPP

// FRENSIE Includes
#include "Utility_ArchivableObject.hpp"

namespace Utility{

//! The base class for standard archivable objects (using boost serialization)
template<typename DerivedType, bool export_allowed=true>
class StandardArchivableObject : public StandardArchivableObject<DerivedType,false>
{

public:

  // Add the exportData member function to the public interface
  using StandardArchivableObject<DerivedType,false>::exportData;
};

//! The base class for standard archivable objects (using boost serialization)
template<typename DerivedType>
class StandardArchivableObject<DerivedType,false> : public virtual ArchivableObject
{

public:

  //! Import data from the desired archive
  void importData( const std::string& archive_name,
		   const ArchivableObject::ArchiveType archive_type,
                   const std::string& object_name = std::string() );

protected:

  //! Export the data in the container to the desired archive type
  void exportData( const std::string& archive_name,
		   const ArchivableObject::ArchiveType archive_type,
                   const std::string& object_name = std::string() ) const;
};

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_StandardArchivableObject_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_STANDARD_ARCHIVABLE_OBJECT_HPP

//---------------------------------------------------------------------------//
// end Utility_StandardArchivableObject.hpp
//---------------------------------------------------------------------------//
