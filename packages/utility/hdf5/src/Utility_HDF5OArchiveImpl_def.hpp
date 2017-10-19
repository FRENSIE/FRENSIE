//---------------------------------------------------------------------------//
//!
//! \file   Utility_HDF5OArchiveImpl_def.hpp
//! \author Alex Robinson
//! \brief  HDF5 output archive implementation class definition
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_HDF5_OARCHIVE_IMPL_DEF_HPP
#define UTILITY_HDF5_OARCHIVE_IMPL_DEF_HPP

// Std Lib Includes
#include <sstream>

// FRENSIE Includes
#include "Utility_TypeNameTraits.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Constructor
template<typename Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(BOOST_PP_EMPTY())
HDF5OArchiveImpl<Archive>::HDF5OArchiveImpl( const std::string& hdf5_filename,
                                             unsigned flags )
  : boost::archive::detail::common_oarchive<Archive>( flags ),
    HDF5CommonArchive( hdf5_filename, ((flags & OVERWRITE_EXISTING_ARCHIVE) ? HDF5File::OVERWRITE : HDF5File::READ_WRITE ) ),
  
{
  this->init( flags );
}

// Initialize the archive
template<typename Archive>
void HDF5OArchiveImpl<Archive>::init( unsigned flags )
{
  // Add a header to the archive
  if( 0 != (flags & boost::archive::no_header ) )
  {
    const std::string archive_signature =
      boost::archive::BOOST_ARCHIVE_SIGNATURE();

    try{
      this->writeToGroupAttribute( this->getPropertiesDir(),
                                   this->getSignatureAttributeName(),
                                   archive_signature.data(),
                                   archive_signature.size() );
    }
    HDF5_FILE_EXCEPTION_CATCH( "The archive signature could not be set in "
                               "hdf5 archive " << hdf5_filename << "!" );

    const unsigned version = boost::archive::BOOST_ARCHIVE_VERSION();

    try{
      this->writeToGroupAttribute( this->getPropertiesDir(),
                                   this->getVersionAttributeName(),
                                   &version, 1 );
    }
    HDF5_FILE_EXCEPTION_CATCH( "The archive version could not be set in "
                               "hdf5 archive " << hdf5_filename << "!" );
  }
}

// Save opaque object
template<typename Archive>
inline void HDF5OArchiveImpl<Archive>::save_binary( const void* address,
                                                    std::size_t count )
{
  this->saveImpl( address, count );
}

// Save an array
template<typename Archive>
template<typename ValueType>
inline void HDF5OArchiveImpl<Archive>::save_array(
                               const boost::serialization::array<ValueType>& a,
                               unsigned int )
{
  this->saveImpl( a.address(), a.count() );
}

// Intercept any type that is not a name-value pair or an attribute here
/*! \details This method should never be called as it will cause a compilation
 * error (by design). To avoid this method, only serialize your types using
 * the boost::serialization::nvp wrapper.
 */
template<typename Archive>
template<typename T>
void HDF5OArchiveImpl<Archive>::save_override( const T& t, BOOST_PFTO int )
{
  testStaticPrecondition((boost::serialization::is_wrapper<T>::value));

  // This should never be called
  this->CommonOArchive::save_override( t, 0 );
}

// Save a type that is wrapped in a boost::serialization::nvp
template<typename Archive>
template<typename T>
inline void HDF5OArchiveImpl<Archive>::save_override(
       HANDLE_BOOST_FUNCTION_TEMPLATE_ORDERING boost::serialization::nvp<T>& t,
       int )
{
  this->save_override( t.const_value(), 0 );
}

// Save a boost::archive::object_id_type attribute
template<typename Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
HDF5OArchiveImpl<Archive>::save_override(
                                 const boost::archive::object_id_type& t, int )
{
  unsigned object_id = t;
  this->writeToCurrentGroupAttribute( "object_id", &object_id, 1 );
  this->linkTrackedObject( object_id );

  d_next_object_is_attribute = true;
  this->save( object_id );
}

// Save a boost::archive::object_reference_type attribute
template<typename Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
HDF5OArchiveImpl<Archive>::save_override(
                          const boost::archive::object_reference_type& t, int )
{
  unsigned object_reference = t;
  this->writeToCurrentGroupAttribute( "object_reference", &object_reference, 1 );
  this->linkTrackedObjectReference( object_reference );

  d_next_object_is_attribute = true;
  this->save( object_reference );
}

// Save a boost::archive::version_type attribute
template<typename Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
HDF5OArchiveImpl<Archive>::save_override(
                                   const boost::archive::version_type& t, int )
{
  unsigned version = t;
  this->writeToCurrentGroupAttribute( "version", &version, 1 );

  d_next_object_is_attribute = true;
  this->save( version );
}

// Save a boost::archive::class_id_type attribute
template<typename Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
HDF5OArchiveImpl<Archive>::save_override(
                                  const boost::arhcive::class_id_type& t, int )
{
  size_t class_id = t;
  this->writeToCurrentGroupAttribute( "class_id", &class_id, 1 );

  d_next_object_is_attribute = true;
  this->save( class_id );
}

// Save a boost::archive::class_id_optional_type attribute
template<typename Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
HDF5OArchiveImpl<Archive>::save_override(
                         const boost::archive::class_id_optional_type& t, int )
{
  // Ignore the writing of this type - it is not needed by this archive type
  // Note: this implementation of this method is similar to the implementation
  //       of the equivalent method for other archive types.
#if 0
  size_t class_id_optional = t;
  this->writeToCurrentGroupAttribute( "class_id_optional", &class_id_optional, 1 );

  d_next_object_is_attribute = true;
  this->save( class_id_optional );
#endif
}

// Save a boost::archive::class_id_reference_type attribute
template<typename Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
HDF5OArchiveImpl<Archive>::save_override(
                        const boost::archive::class_id_reference_type& t, int )
{
  size_t class_id_reference = t;
  this->writeToCurrentGroupAttribute( "class_id_reference", &class_id_reference, 1 );

  d_next_object_is_attribute = true;
  this->save( class_id_reference );
}

// Save a boost::archive::class_name_type attribute
template<typename Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
HDF5OArchiveImpl<Archive>::save_override(
                                const boost::archive::class_name_type& t, int )
{
  const std::string class_name( t );
  this->writeToCurrentGroupAttribute( "class_name", class_name.data(), class_name.size() );

  d_next_object_is_attribute = true;
  this->save( class_name );
}

// Save a boost::archive::tracking_type attribute
template<typename Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
HDF5OArchiveImpl<Archive>::save_override(
                                  const boost::archive::tracking_type& t, int )
{
  this->writeToCurrentGroupAttribute( "class_tracking", &t.t, 1 );

  d_next_object_is_attribute = true;
  this->save( t.t );
}

// Save any type with a Utility::HDF5TypeTraits specialization
template<typename Archive>
template<typename T>
void HDF5OArchiveImpl<Archive>::save( const T& t )
{
  this->saveImpl( &t, 1 );
}

// Save a std::string
template<typename Archive>
void HDF5OArchiveImpl<Archive>::save( const std::string& t )
{
  this->saveContainerImpl( t );
}

// Save a std::wstring
template<typename Archive>
void HDF5OArchiveImpl<Archive>::save( const std::wstring& t )
{
  this->saveContainerImpl( t );
}

// Save a bost::serialization::collection_size_type
template<typename Archive>
void HDF5OArchiveImpl<Archive>::save(
                          const boost::serialization::collection_size_type& t )
{
  size_t collection_size = t;
  
  this->save( collection_size );
}

// Save a boost::serialization::item_version_type attribute
template<typename Archive>
void HDF5OArchiveImpl<Archive>::save(
                             const boost::serialization::item_version_type& t )
{
  unsigned version = t;

  this->save( version );
}

// Write to current group attribute
template<typename Archive>
template<typename T>
void HDF5OArchiveImpl<Archive>::writeToCurrentGroupAttribute(
                                             const std::string& attribute_name,
                                             const T* const data,
                                             const size_t size )
{
  std::ostringstream oss full_attribute_name;
  full_attribute_name << attribute_name << "_d" << d_object_count;

  try{
    this->writeToGroupAttribute( this->getTreeObjectPath(),
                                 full_attribute_name.str(),
                                 data,
                                 size );
  }
  HDF5_FILE_EXCEPTION_CATCH_RETHROW( "Could not write data to group attribute "
                                     << this->getTreeObjectPath() << ":"
                                     << full_attribute_name << "!" );
}

// Save implementation
template<typename Archive>
template<typename T>
void HDF5OArchiveImpl<Archive>::saveImpl( const T* data, size_t count )
{
  try{
    this->saveImpl( this->getObjectDataPath( d_object_count ), data, count );
  }
  HDF5_FILE_EXCEPTION_CATCH_RETHROW( "Could not save data for primitive "
                                     "object " << d_object_count <<
                                     " of type " << Utility::typeName<T>() <<
                                     "!" );
}

// Save implementation (object data set path already determined)
template<typename Archive>
template<typename T>
void HDF5OArchiveImpl<Archive>::saveImpl(
                                       const std::string& object_data_set_path,
                                       const T* data,
                                       size_t count )
{
  this->readFromDataSet( object_data_set_path, data, count );
  this->linkDataAndUpdateObjectCount();
}

// Save container implementation
template<typename Archive>
template<typename T>
void HDF5OArchiveImpl<Archive>::saveContainerImpl( const T& container )
{
  std::string object_data_set_path = this->getObjectDataPath( d_object_count );

  try{
    hsize_t container_size = this->getDataSetSize( object_data_set_path );

    container.resize( container_size );

    this->saveImpl( object_data_set_path, container.data(), container_size );
  }
  HDF5_FILE_EXCEPTION_CATCH_RETHROW( "Could not save data for container "
                                     "object " << d_object_count <<
                                     " of type " << Utility::typeName<T>() <<
                                     "!" );
}

// Get the tree object path
template<typename Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(std::string)
HDF5OArchive<Archive>::getTreeObjectPath() const
{
  std::ostringstream oss;

  oss << this->getTreeDir();

  GroupStack::const_iterator it = d_group_stack.begin();
  GroupStack::const_iterator end = d_group_stack.end();

  while( it != end )
  {
    oss << "/" << *it;

    ++it;
  }

  return oss.str();
}

// Link the data object
template<typename Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
HDF5OArchiveImpl<Archive>::linkDataObject()
{
  if( !d_next_object_is_attribute )
  {
    std::ostringstream source_path;

    source_path << this->getTreeObjectPath() << "/<data>_d" << d_object_count;

    const std::string target_path = this->getObjectDataPath( d_object_count );

    try{
      this->createHardLink( source_path.str(), target_path );
    }
    HDF5_FILE_EXCEPTION_CATCH_RETHROW( "Could link data object "
                                       << d_object_count << " with source "
                                       "path " << source_path.str() << " to "
                                       "target at " << target_path << "!" );
  }

  d_next_object_is_attribute = false;
}

// Link the tracked object
template<typename Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
HDF5OArchiveImpl<Archive>::linkTrackedObject( unsigned object )
{
  const std::string source_path = this->getTrackedObjectsPath( object );
  const std::string target_path = this->getTreeObjectPath();

  try{
    this->createSoftLink( source_path, target_path );
  }
  HDF5_FILE_EXCEPTION_CATCH_RETHROW( "Could not link tracked object "
                                     << object << " with source path "
                                     << source_path << " to target at "
                                     << target_path << "!" );
}

// Link the tracked object reference
template<typename Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
HDF5OArchiveImpl<Archive>::linkTrackedObjectReference( unsigned object_reference )
{
  std::ostringstream oss source_path;
  source_path << this->getTreeObjectPath()
              << "/<reference>_o"
              << object_reference;

  const std::string target_path =
    this->getTrackedObjectsPath( object_reference );

  try{
    this->createSoftLink( source_path.str(), target_path );
  }
  HDF5_FILE_EXCEPTION_CATCH_RETHROW( "Could not link tracked object reference "
                                     << object << " with source path "
                                     << source_path.str() << " to target at "
                                     << target_path << "!" );
}

// Link the data and update the object count
template<typename Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
HDF5OArchiveImpl<Archive>::linkDataAndUpdateObjectCount()
{
  this-linkDataObject();

  ++d_object_count;
}
  
} // end Utility namespace

#endif // end UTILITY_HDF5_OARCHIVE_IMPL_DEF_HPP

//---------------------------------------------------------------------------//
// end Uitlity_HDF5OArchiveImpl_def.hpp
//---------------------------------------------------------------------------//
