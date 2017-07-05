//---------------------------------------------------------------------------//
//!
//! \file   Utility_StandardArchivableObject_def.hpp
//! \author Alex Robinson
//! \brief  StandardArchivableObject_def.hpp
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_STANDARD_ARCHIVABLE_OBJECT_DEF_HPP
#define UTILITY_STANDARD_ARCHIVABLE_OBJECT_DEF_HPP

// Std Lib Includes
#include <fstream>
#include <typeinfo>

// Boost Includes
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

namespace Utility{

// Export the data in the container to the desired archive type
/*! \details In order for this function to compile, the serialize member
 * function or the save and load member function must be defined in the
 * derived class as described by the boost serialization library.
 */
template<typename DerivedType>
void StandardArchivableObject<DerivedType,false>::exportData(
		       const std::string& archive_name,
		       const ArchivableObject::ArchiveType archive_type,
                       const std::string& object_name ) const
{
  std::ofstream ofs( archive_name.c_str() );

  std::string true_object_name;
  
  if( object_name.size() == 0 )
    true_object_name = typeid(*dynamic_cast<const DerivedType*>(this)).name();
  else
    true_object_name = object_name;

  switch( archive_type )
  {
    case Utility::ArchivableObject::ASCII_ARCHIVE:
    {
      boost::archive::text_oarchive ar(ofs);
      ar << *dynamic_cast<const DerivedType*>(this);

      break;
    }
    case Utility::ArchivableObject::BINARY_ARCHIVE:
    {
      boost::archive::binary_oarchive ar(ofs);
      ar << *dynamic_cast<const DerivedType*>(this);

      break;
    }
    case Utility::ArchivableObject::XML_ARCHIVE:
    {
      boost::archive::xml_oarchive ar(ofs);
      ar << boost::serialization::make_nvp(
                                     true_object_name,
                                     *dynamic_cast<const DerivedType*>(this) );

      break;
    }
  }
}

// Import data from the desired archive
/*! \details In order for this function to compile, the serialize member
 * function or the save and load member function must be defined in the
 * derived class as described by the boost serialization library.
 */
template<typename DerivedType>
void StandardArchivableObject<DerivedType,false>::importData(
			     const std::string& archive_name,
			     const ArchivableObject::ArchiveType archive_type,
                             const std::string& object_name )
{
  std::ifstream ifs( archive_name.c_str() );

  std::string true_object_name;
  
  if( object_name.size() == 0 )
    true_object_name = typeid(*dynamic_cast<const DerivedType*>(this)).name();
  else
    true_object_name = object_name;

  switch( archive_type )
  {
    case Utility::ArchivableObject::ASCII_ARCHIVE:
    {
      boost::archive::text_iarchive ar(ifs);
      ar >> *dynamic_cast<DerivedType*>(this);

      break;
    }
    case Utility::ArchivableObject::BINARY_ARCHIVE:
    {
      boost::archive::binary_iarchive ar(ifs);
      ar >> *dynamic_cast<DerivedType*>(this);

      break;
    }
    case Utility::ArchivableObject::XML_ARCHIVE:
    {
      boost::archive::xml_iarchive ar(ifs);
      ar >> boost::serialization::make_nvp( true_object_name,
                                            *dynamic_cast<DerivedType*>(this) );

      break;
    }
  }
}

} // end Utility namespace

#endif // end UTILITY_STANDARD_ARCHIVABLE_OBJECT_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_StandardArchivableObject_def.hpp
//---------------------------------------------------------------------------//
