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
#include "Utility_LoggingMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{

// Constructor
template<typename Archive>
HDF5OArchiveImpl<Archive>::HDF5OArchiveImpl( const std::string& hdf5_filename,
                                             unsigned flags )
  : boost::archive::detail::common_oarchive<Archive>( flags ),
    HDF5CommonArchive( hdf5_filename, ((flags & HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE) ? HDF5File::OVERWRITE : HDF5File::READ_WRITE ) ),
    d_object_count( 0 ),
    d_group_count( 0 ),
    d_group_stack(),
    d_next_object_is_attribute( false )
{
  this->init( flags );
}

// Initialize the archive
template<typename Archive>
void HDF5OArchiveImpl<Archive>::init( unsigned flags )
{
  // Add a header to the archive
  if( !(flags & boost::archive::no_header ) )
  {
    try{
      this->writeToGroupAttribute( this->getPropertiesDir(),
                                   this->getSignatureAttributeName(),
                                   std::string(boost::archive::BOOST_ARCHIVE_SIGNATURE()) );
    }
    HDF5_FILE_EXCEPTION_CATCH_RETHROW( "The archive signature could not be "
                                       "set in hdf5 archive "
                                       << this->getFilename() << "!" );

    try{
      this->writeToGroupAttribute<unsigned>( this->getPropertiesDir(),
                                             this->getVersionAttributeName(),
                                             boost::archive::BOOST_ARCHIVE_VERSION() );
    }
    HDF5_FILE_EXCEPTION_CATCH_RETHROW( "The archive version could not be set "
                                       "in hdf5 archive "
                                       << this->getFilename() << "!" );
  }

  // Create the group that will contain all serialized data
  this->createGroup( this->getDataDir() );

  // Create the group that will contain links to tracked objects
  this->createGroup( this->getTrackedObjectsDir() );

  // Create the group that will contain the hierarchical information
  // associated with the serialized objects
  this->createGroup( this->getTreeDir() );
}

// Save opaque object
template<typename Archive>
inline void HDF5OArchiveImpl<Archive>::save_binary( const void* address,
                                                    std::size_t count )
{
  this->saveImpl( address, count );
}

#ifdef BOOST_SERIALIZATION_ARRAY_WRAPPER_AVAILABLE
// Save an array
template<typename Archive>
template<typename ValueType>
inline void HDF5OArchiveImpl<Archive>::save_array(
                       const boost::serialization::array_wrapper<ValueType>& a,
                       unsigned int )
{
  this->saveImpl( a.address(), a.count() );
}
#endif

// Start a save
template<typename Archive>
void HDF5OArchiveImpl<Archive>::save_start( const char* name )
{
  // if( name )
  // {
  //   FRENSIE_LOG_TAGGED_NOTIFICATION( name,  "started" );
  // }

  this->startHDF5Group( name );
}

// Finish a save
template<typename Archive>
void HDF5OArchiveImpl<Archive>::save_end( const char* name )
{
  // if( name )
  // {
  //   FRENSIE_LOG_TAGGED_NOTIFICATION( name, "finished" );
  // }
  
  this->endHDF5Group();
}

// Intercept any type that is not a name-value pair or an attribute here
/*! \details This method should never be called as it will cause a compilation
 * error (by design). To avoid this method, only serialize your types using
 * the boost::serialization::nvp wrapper.
 */
template<typename Archive>
template<typename T>
void HDF5OArchiveImpl<Archive>::save_override( const T& t, int )
{
  testStaticPrecondition((boost::serialization::is_wrapper<T>::type::value));

  // This should never be called
#ifdef USE_OLD_BOOST_ARCHIVE_OVERRIDE
  this->CommonOArchive::save_override( t, 0 );
#else
  this->CommonOArchive::save_override( t );
#endif
}

// Save a type that is wrapped in a boost::serialization::nvp
template<typename Archive>
template<typename T>
inline void HDF5OArchiveImpl<Archive>::save_override(
                                   const boost::serialization::nvp<T>& t, int )
{
  this->save_start( t.name() );

  this->saveIntercept(t.const_value(), typename std::conditional<IsTuple<T>::value && Utility::HDF5TypeTraits<T>::IsSpecialized::value,std::true_type,std::false_type>::type());

  this->save_end( t.name() );
}

// Save a boost::archive::object_id_type attribute
template<typename Archive>
void HDF5OArchiveImpl<Archive>::save_override(
                                 const boost::archive::object_id_type& t, int )
{
  //FRENSIE_LOG_PARTIAL_NOTIFICATION( "object id type: " );
  unsigned object_id = t;
  this->writeToCurrentGroupAttribute( "object_id", &object_id, 1 );
  this->linkTrackedObject( object_id );

  d_next_object_is_attribute = true;
  this->save( object_id );
}

// Save a boost::archive::object_reference_type attribute
template<typename Archive>
void HDF5OArchiveImpl<Archive>::save_override(
                          const boost::archive::object_reference_type& t, int )
{
  //FRENSIE_LOG_PARTIAL_NOTIFICATION( "object reference type: " );
  unsigned object_reference = t;
  this->writeToCurrentGroupAttribute( "object_reference", &object_reference, 1 );
  this->linkTrackedObjectReference( object_reference );

  d_next_object_is_attribute = true;
  this->save( object_reference );
}

// Save a boost::archive::version_type attribute
template<typename Archive>
void HDF5OArchiveImpl<Archive>::save_override(
                                   const boost::archive::version_type& t, int )
{
  //FRENSIE_LOG_PARTIAL_NOTIFICATION( "version type: " );
  unsigned version = t;
  this->writeToCurrentGroupAttribute( "version", &version, 1 );

  d_next_object_is_attribute = true;
  this->save( version );
}

// Save a boost::archive::class_id_type attribute
template<typename Archive>
void HDF5OArchiveImpl<Archive>::save_override(
                                  const boost::archive::class_id_type& t, int )
{
  //FRENSIE_LOG_PARTIAL_NOTIFICATION( "class id type: " );
  size_t class_id = t;
  this->writeToCurrentGroupAttribute( "class_id", &class_id, 1 );

  d_next_object_is_attribute = true;
  this->save( class_id );
}

// Save a boost::archive::class_id_optional_type attribute
template<typename Archive>
void HDF5OArchiveImpl<Archive>::save_override(
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
void HDF5OArchiveImpl<Archive>::save_override(
                        const boost::archive::class_id_reference_type& t, int )
{
  //FRENSIE_LOG_PARTIAL_NOTIFICATION( "class id reference type: " );
  size_t class_id_reference = t;
  this->writeToCurrentGroupAttribute( "class_id_reference", &class_id_reference, 1 );

  d_next_object_is_attribute = true;
  this->save( class_id_reference );
}

// Save a boost::archive::class_name_type attribute
template<typename Archive>
void HDF5OArchiveImpl<Archive>::save_override(
                                const boost::archive::class_name_type& t, int )
{
  //FRENSIE_LOG_PARTIAL_NOTIFICATION( "class name type: " );
  const std::string class_name( t );
  this->writeToCurrentGroupAttribute( "class_name", &class_name, 1 );

  d_next_object_is_attribute = true;
  this->save( class_name );
}

// Save a boost::archive::tracking_type attribute
template<typename Archive>
void HDF5OArchiveImpl<Archive>::save_override(
                                  const boost::archive::tracking_type& t, int )
{
  //FRENSIE_LOG_PARTIAL_NOTIFICATION( "tracking type: " );
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

// Save a wide string
template<typename Archive>
void HDF5OArchiveImpl<Archive>::save( const wchar_t& t )
{
  THROW_HDF5_ARCHIVE_EXCEPTION( "Wide chars are not currently supported!" );
}

// Save a wide string
template<typename Archive>
void HDF5OArchiveImpl<Archive>::save( const std::wstring& t )
{
  THROW_HDF5_ARCHIVE_EXCEPTION( "Wide strings are not currently supported!" );
}

// Save a boost::serialization::collection_size_type
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
  std::ostringstream full_attribute_name;
  full_attribute_name << attribute_name << "_d" << d_object_count;

  try{
    this->writeToGroupAttribute( this->getTreeObjectPath(),
                                 full_attribute_name.str(),
                                 data,
                                 size );
  }
  HDF5_FILE_EXCEPTION_CATCH_RETHROW( "Could not write data to group attribute "
                                     << this->getTreeObjectPath() << ":"
                                     << full_attribute_name.str() << "!" );
}

// Intercept a type that is about to be saved
template<typename Archive>
template<typename T>
void HDF5OArchiveImpl<Archive>::saveIntercept( const T& t, std::true_type is_fast_serializable_tuple )
{
  this->save(t);
}

// Intercept a type that is about to be saved
template<typename Archive>
template<typename T>
void HDF5OArchiveImpl<Archive>::saveIntercept( const T& t, std::false_type is_fast_serializable_tuple )
{
#if USE_OLD_BOOST_ARCHIVE_OVERRIDE
  this->CommonOArchive::save_override( t, 0 );
#else
  this->CommonOArchive::save_override( t );
#endif 
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
  //FRENSIE_LOG_NOTIFICATION( object_data_set_path << " (" << Utility::typeName<T>() << ")" );
  this->writeToDataSet( object_data_set_path, data, count );
  this->linkDataAndUpdateObjectCount();
}

// Save container implementation
template<typename Archive>
template<typename T>
void HDF5OArchiveImpl<Archive>::saveContainerImpl( const T& container )
{
  std::string object_data_set_path = this->getObjectDataPath( d_object_count );

  try{
    this->saveImpl( object_data_set_path, container.data(), container.size() );
  }
  HDF5_FILE_EXCEPTION_CATCH_RETHROW( "Could not save data for container "
                                     "object " << d_object_count <<
                                     " of type " << Utility::typeName<T>() <<
                                     "!" );
}

// Start an hdf5 group
template<typename Archive>
void HDF5OArchiveImpl<Archive>::startHDF5Group( const char* group_name )
{
  std::ostringstream full_group_name;

  if( group_name == NULL )
    full_group_name << "_g" << d_group_count;
  else
    full_group_name << group_name << "_g" << d_group_count;

  d_group_stack.push_back( full_group_name.str() );

  this->createGroup( this->getTreeObjectPath() );

  ++d_group_count;
}

// End an hdf5 group
template<typename Archive>
void HDF5OArchiveImpl<Archive>::endHDF5Group()
{
  d_group_stack.pop_back();
}

// Get the tree object path
template<typename Archive>
std::string HDF5OArchiveImpl<Archive>::getTreeObjectPath() const
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
void HDF5OArchiveImpl<Archive>::linkDataObject()
{
  if( !d_next_object_is_attribute )
  {
    std::ostringstream link_path;

    link_path << this->getTreeObjectPath() << "/<data>_d" << d_object_count;

    const std::string object_path = this->getObjectDataPath( d_object_count );

    try{
      this->createHardLink( object_path, link_path.str() );
    }
    HDF5_FILE_EXCEPTION_CATCH_RETHROW( "Could not create a link with path "
                                       << link_path.str() << " to data object "
                                       << d_object_count << " at "
                                       << object_path <<  "!" );
  }

  d_next_object_is_attribute = false;
}

// Link the tracked object
template<typename Archive>
void HDF5OArchiveImpl<Archive>::linkTrackedObject( unsigned object )
{
  const std::string link_path = this->getTrackedObjectsPath( object );

  const std::string object_path = this->getTreeObjectPath();

  try{
    this->createSoftLink( object_path, link_path );
  }
  HDF5_FILE_EXCEPTION_CATCH_RETHROW( "Could not create a link with path "
                                     << link_path << " to data object "
                                     << object << " at "
                                     << object_path <<  "!" );
}

// Link the tracked object reference
template<typename Archive>
void HDF5OArchiveImpl<Archive>::linkTrackedObjectReference( unsigned object_reference )
{
  std::ostringstream link_path;
  link_path << this->getTreeObjectPath()
              << "/<reference>_o"
              << object_reference;

  const std::string object_path =
    this->getTrackedObjectsPath( object_reference );

  try{
    this->createSoftLink( object_path, link_path.str() );
  }
  HDF5_FILE_EXCEPTION_CATCH_RETHROW( "Could not create a link with path "
                                     << link_path.str() << " to data object "
                                     << object_reference << " at "
                                     << object_path <<  "!" );
}

// Link the data and update the object count
template<typename Archive>
void HDF5OArchiveImpl<Archive>::linkDataAndUpdateObjectCount()
{
  this->linkDataObject();

  ++d_object_count;
}

} // end Utility namespace

#endif // end UTILITY_HDF5_OARCHIVE_IMPL_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_HDF5OArchiveImpl_def.hpp
//---------------------------------------------------------------------------//
