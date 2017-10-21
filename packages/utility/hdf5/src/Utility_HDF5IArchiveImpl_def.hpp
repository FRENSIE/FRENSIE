//---------------------------------------------------------------------------//
//!
//! \file   Utility_HDF5IArchiveImpl_def.hpp
//! \author Alex Robinson
//! \brief  HDF5 input archive implementation class definition.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_HDF5_IARCHIVE_IMPL_DEF_HPP
#define UTILITY_HDF5_IARCHIVE_IMPL_DEF_HPP

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "Utility_TypeNameTraits.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Constructor
template<typename Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(BOOST_PP_EMPTY())
HDF5IArchiveImpl<Archive>::HDF5IArchiveImpl( const std::string& hdf5_filename,
                                             unsigned flags )
  : boost::archive::detail::common_iarchive<Archive>( flags ),
    Utility::HDF5CommonArchive( hdf5_filename, HDF5File::READ_ONLY ),
    d_object_count( 0 )
{
  this->init( flags );
}

// Initialize the archive
template<typename Archive>
void HDF5IArchiveImpl<Archive>::init( unsigned flags )
{
  // Check that the signature and version number in the archive are valid
  if( 0 != (flags & boost::archive::no_header) )
  {
    // Load the signature
    if( this->doesGroupAttributeExist( this->getPropertiesDir(), this->getSignatureAttributeName() ) )
    {
      std::string archive_signature;
      
      try{
        Utility::readFromGroupAttribute( *this,
                                         this->getPropertiesDir(),
                                         this->getSignatureAttributeName(),
                                         archive_signature );
      }
      HDF5_FILE_EXCEPTION_CATCH( "The archive signature could not be "
                                 "retrieved from hdf5 archive "
                                 << hdf5_filename << "!" );

      TEST_FOR_ARCHIVE_EXCEPTION(
                archive_signature != boost::archive::BOOST_ARCHIVE_SIGNATURE(),
                boost::archive::archive_exception::invalid_signature );
    }
    else
    {
      THROW_HDF5_ARCHIVE_EXCEPTION( "The hdf5 archive does not have a "
                                    "signature attribute!" );
    }

    // Load the version
    if( this->doesGroupAttributeExist( this->getPropertiesDir(), this->getVersionAttributeName() ) )
    {
      unsigned version = std::numeric_limits<unsigned>::max();
      
      try{
        this->readFromGroupAttribute( this->getPropertiesDir(),
                                      this->getVersionAttributeName(),
                                      &version,
                                      1 );
      }
      HDF5_FILE_EXCEPTION_CATCH_RETHROW( "The archive signature could not be "
                                         "retrieved from hdf5 archive "
                                         << hdf5_filename << "!" );

      TEST_FOR_ARCHIVE_EXCEPTION( 
                      version != boost::archive::BOOST_ARCHIVE_VERSION(),
                      boost::archive::archive_exception::unsupported_version );
    }
    else
    {
      THROW_HDF5_ARCHIVE_EXCEPTION( "The hdf5 archive does not have a version "
                                    "attribute!" );
    }
  }
}

// Load object from memory
/*! \details This is a required boost::archive interface method
 */
template<typename Archive>
inline void HDF5IArchiveImpl<Archive>::load_binary( void* address, std::size_t count )
{
  this->loadImpl( address, count );
}

// Load an array
/*! \details This is a required boost::archive interface method
 */
template<typename Archive>
template<typename ValueType>
inline void HDF5IArchiveImpl<Archive>::load_array(
                                 boost::serialization::array<ValueType>& array,
                                 unsigned )
{
  this->loadImpl( array.address(), array.count() );
}

// Intercept any type that is not a name-value pair or an attribute here
/*! \details This method should never be called as it will cause a compilation
 * error (by design). To avoid this method, only serialize your types using
 * the boost::serialization::nvp wrapper.
 */
template<typename Archive>
template<typename T>
inline void HDF5IArchiveImpl<Archive>::load_override( T& t, BOOST_PFTO int )
{
  testStaticPrecondition((boost::serialization::is_wrapper<T>::value));

  // This should never be called
  this->CommonIArchive::load_override( t, 0 );
}

// Load a type that is wrapped in a boost::serialization::nvp
template<typename Archive>
template<typename T>
inline void HDF5IArchiveImpl<Archive>::load_override(
       HANDLE_BOOST_FUNCTION_TEMPLATE_ORDERING boost::serialization::nvp<T>& t,
       int )
{
  this->CommonIArchive::load_override( t.value(), 0 );
}

// Load a boost::archive::object_id_type attribute
template<typename Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
HDF5IArchiveImpl<Archive>::load_override( boost::archive::object_id_type& t, int )
{
  unsigned i;
  this->load(i);

  t = boost::archive::object_id_type(i);
}

// Load a boost::archive::object_reference_type attribute
template<typename Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
HDF5IArchiveImpl<Archive>::load_override( boost::archive::object_reference_type& t, int )
{
  unsigned i;
  this->load(i);

  t = boost::archive::object_reference_type( boost::archive::object_id_type(i) );
}

// Load a boost::archive::version_type attribute
template<typename Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
HDF5IArchiveImpl<Archive>::load_override( boost::archive::version_type& t, int )
{
  unsigned i;
  this->load(i);

  t = boost::archive::version_type(i);
}

// Load a boost::archive::class_id_type attribute
template<typename Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
HDF5IArchiveImpl<Archive>::load_override( boost::arhcive::class_id_type& t, int )
{
  size_t i;
  this->load(i);

  t = boost::archive::class_id_type(i);
}

// Load a boost::archive::class_id_optional_type attribute
template<typename Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
HDF5IArchiveImpl<Archive>::load_override( boost::archive::class_id_optional_type& t, int )
{
  // Ignore the reading of this type - it is not needed by this archive type
  // Note: this implementation of this method is similar to the implementation
  //       of the equivalent method for other archive types.
#if 0
  size_t i;
  this->load(i);

  t = boost::archive::class_id_optional_type( boost::archive::class_id_type(i) );
#endif
}

// Load a boost::archive::class_id_reference_type attribute
template<typename Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
HDF5IArchiveImpl<Archive>::load_override( boost::archive::class_id_reference_type& t, int )
{
  size_t i;
  this->load(i);

  t = boost::archive::class_id_reference_type( boost::archive::class_id_type(i) );
}

// Load a boost::archive::class_name_type attribute
template<typename Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
HDF5IArchiveImpl<Archive>::load_override( boost::archive::class_name_type& t, int )
{
  std::string s;
  s.reserve(BOOST_SERIALIZATION_MAX_KEY_SIZE);
  this->load(s);

  TEST_FOR_ARCHIVE_EXCEPTION(
                       s.size() > (BOOST_SERIALIZATION_MAX_KEY_SIZE-1),
                       boost::archive::archive_exception::invalid_class_name );

  std::memcpy( t, s.data(), s.size() );

  // This step is required by some compilers
  t.t[s.size()] = '\0'
}

// Load a boost::archive::tracking_type attribute
template<typename Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
HDF5IArchiveImpl<Archive>::load_override( boost::archive::tracking_type& t, int )
{
  bool i;
  this->load(i);

  t = boost::archive::tracking_type(i);
}

// Serialization of types with a corresponding HDF5 type
template<typename Archive>
template<typename T>
inline void HDF5IArchiveImpl<Archive>::load( T& t )
{
  this->loadImpl( &t, 1 );
}

// Load a std::string
template<typename Archive>
inline void HDF5IArchiveImpl<Archive>::load( std::string& t )
{
  this->loadContainerImpl( t );
}

// Load a std::wstring
template<typename Archive>
inline void HDF5IArchiveImpl<Archive>::load( std::wstring& t )
{
  this->loadContainerImpl( t );
}

// Load a bost::serialization::collection_size_type
template<typename Archive>
inline void HDF5IArchiveImpl<Archive>::load( boost::serialization::collection_size_type& t )
{
  size_t i;
  this->load(i);

  t = boost::serialization::collection_size_type(i);
}

// Load a boost::serialization::item_version_type attribute
template<typename Archive>
inline void HDF5IArchiveImpl<Archive>::load( boost::serialization::item_version_type& t )
{
  unsigned version;
  this->load(version);
  
  t = boost::serialization::item_version_type(version);
}

// Load implementation
template<typename Archive>
template<typename T>
inline void HDF5IArchiveImpl<Archive>::loadImpl( T* data, size_t count )
{
  try{
    this->loadImpl( this->getObjectDataPath( d_object_count ), data, count );
  }
  HDF5_FILE_EXCEPTION_CATCH_RETHROW( "Could not load data for primitive "
                                     "object " << d_object_count <<
                                     " of type " << Utility::typeName<T>() <<
                                     "!" );
}

// Load implementation (object data set path already determined)
template<typename Archive>
template<typename T>
void HDF5IArchiveImpl<Archive>::loadImpl(
                                       const std::string& object_data_set_path,
                                       T* data,
                                       size_t count )
{
  this->readFromDataSet( object_data_set_path, data, count );
  this->updateObjectCount();
}

// Load container implementation
template<typename Archive>
template<typename T>
inline void HDF5IArchiveImpl<Archive>::loadContainerImpl( T& container )
{
  std::string object_data_set_path = this->getObjectDataPath( d_object_count );

  try{
    hsize_t data_set_size = this->getDataSetSize( object_data_set_path );
    size_t container_size = Utility::HDF5TypeTraits<typename T::value_type>::calculateExternalDataSize( data_set_size );

    container.resize( container_size );

    this->loadImpl( object_data_set_path, container.data(), container_size );
  }
  HDF5_FILE_EXCEPTION_CATCH_RETHROW( "Could not load data for container "
                                     "object " << d_object_count <<
                                     " of type " << Utility::typeName<T>() <<
                                     "!" );
}

// Update the object count
template<typename Archive>
inline void HDF5IArchiveImpl<Archive>::updateObjectCount()
{
  ++d_object_count;
}
  
} // end Utility namespace

#endif // end UTILITY_HDF5_IARCHIVE_IMPL_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_HDF5IArchiveImpl_def.hpp
//---------------------------------------------------------------------------//
