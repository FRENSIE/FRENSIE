//---------------------------------------------------------------------------//
//!
//! \file   Utility_HDF5File_def.hpp
//! \author Alex Robinson
//! \brief  The hdf5 file template definitions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_HDF5_FILE_DEF_HPP
#define UTILITY_HDF5_FILE_DEF_HPP

// FRENSIE Includes
#include "Utility_HDF5TypeTraits.hpp"
#include "Utility_Array.hpp"
#include "Utility_Vector.hpp"
#include "Utility_ArrayView.hpp"
#include "Utility_TypeTraits.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{

// Write data to a data set
/*! \details Once a data set has been created its allocated memory cannot be
 * reduced or freed. While increasing it is possible, data sets that allow this
 * operation use chunked data, which can incur a large performance penalty. 
 * Furthermore, it isn't obvious how we would determine the optimal chunk size.
 */ 
template<typename T>
void HDF5File::writeToDataSet( const std::string& path_to_data_set,
                               const T* data,
                               const size_t size )
{
#ifdef HAVE_FRENSIE_HDF5
  std::unique_ptr<H5::DataSet> data_set;
  
  if( this->doesDataSetExist( path_to_data_set ) )
  {
    THROW_EXCEPTION( HDF5File::Exception,
                     "Overwriting the data in an existing data set ("
                     << path_to_data_set << ") is not currently supported!" );
  }
  else
  {
    if( !this->doesParentGroupExist( path_to_data_set ) )
      this->createParentGroup( path_to_data_set );

    // Create the data set
    std::unique_ptr<H5::DataSet> data_set;
    
    this->createDataSet<T>( path_to_data_set, size, data_set );

    // Convert the data to a format that is compatible with HDF5
    typename HDF5TypeTraits<T>::InternalType* internal_data =
      HDF5TypeTraits<T>::initializeInternalData( data, size );

    HDF5TypeTraits<T>::convertExternalDataToInternalData( data, size, internal_data );

    // Write the data to the data set
    data_set->write( internal_data, HDF5TypeTraits<T>::dataType() );

    // Clean up the temporary data
    HDF5TypeTraits<T>::freeInternalData( internal_data );
  }
#endif
}

// Write data to a data set
template<typename T>
inline void HDF5File::writeToDataSet( const std::string& path_to_data_set,
                                      const T& data )
{ this->writeToDataSet( path_to_data_set, &data, 1 ); }

// Read data from a data set
template<typename T>
void HDF5File::readFromDataSet( const std::string& path_to_data_set,
                                T* data,
                                const size_t size ) const
{
#ifdef HAVE_FRENSIE_HDF5
  // Open the data set
  std::unique_ptr<const H5::DataSet> data_set;

  this->openDataSet( path_to_data_set, data_set );

  // Load the data from the data set in its internal format
  typename HDF5TypeTraits<T>::InternalType* internal_data =
    HDF5TypeTraits<T>::initializeInternalData( data, size );

  // Check if the array can store the data set contents
  TEST_FOR_EXCEPTION( !this->canArrayStoreDataSetContents<T>( internal_data, size, *data_set ),
                      HDF5File::Exception,
                      "Cannot store the contents of data set "
                      << path_to_data_set << " in the desired memory "
                      "location!" );

  try{
    data_set->read( internal_data, HDF5TypeTraits<T>::dataType() );
  }
  HDF5_EXCEPTION_CATCH( "Could not read data from data set "
                        << path_to_data_set << "!" );

  // Convert the internal data to the desired format
  HDF5TypeTraits<T>::convertInternalDataToExternalData( internal_data,
                                                        size,
                                                        data );

  // Clean up temporary data
  HDF5TypeTraits<T>::freeInternalData( internal_data );
#endif
}

// Write data to a data set attribute
template<typename T>
void HDF5File::writeToDataSetAttribute( const std::string& path_to_data_set,
                                        const std::string& attribute_name,
                                        const T* data,
                                        const size_t size )
{
#ifdef HAVE_FRENSIE_HDF5
  // Open the data set
  std::unique_ptr<const H5::DataSet> data_set;

  this->openDataSet( path_to_data_set, data_set );

  // Make sure that the attribute doesn't exist yet
  TEST_FOR_EXCEPTION( this->doesDataSetAttributeExist( *data_set, attribute_name ),
                      HDF5File::Exception,
                      "Overwriting the data in an existing data set attribute "
                      "(" << path_to_data_set << ":" << attribute_name << ")"
                      " is not currently supported!" );

  try{
    // Create the attribute
    std::unique_ptr<H5::Attribute> attribute;
    
    this->createDataSetAttribute<T>( *data_set,
                                     path_to_data_set,
                                     attribute_name,
                                     size,
                                     attribute );

    // Convert the data to a format that is compatible with HDF5
    typename HDF5TypeTraits<T>::InternalType* internal_data =
      HDF5TypeTraits<T>::initializeInternalData( data, size );

    HDF5TypeTraits<T>::convertExternalDataToInternalData( data, size, internal_data );
    
    attribute->write( HDF5TypeTraits<T>::dataType(), internal_data );

    // Clean up the temporary data
    HDF5TypeTraits<T>::freeInternalData( internal_data );
  }
  HDF5_EXCEPTION_CATCH( "Could not write data to data set attribute ("
                        << path_to_data_set << ":" << attribute_name << ")!" );
#endif
}

// Write data to a data set attribute
template<typename T>
inline void HDF5File::writeToDataSetAttribute(
                                           const std::string& path_to_data_set,
                                           const std::string& attribute_name,
                                           const T& data )
{
  this->writeToDataSetAttribute( path_to_data_set, attribute_name, &data, 1 );
}
  
// Read data from a data set attribute
template<typename T>
void HDF5File::readFromDataSetAttribute( const std::string& path_to_data_set,
                                         const std::string& attribute_name,
                                         T* data,
                                         const size_t size ) const
{
#ifdef HAVE_FRENSIE_HDF5
  // Open the data set
  std::unique_ptr<const H5::DataSet> data_set;

  this->openDataSet( path_to_data_set, data_set );

  // Open the attribute
  std::unique_ptr<const H5::Attribute> attribute;

  this->openDataSetAttribute( *data_set,
                              path_to_data_set,
                              attribute_name,
                              attribute );

  // Load the data from the attribute in its internal format
  typename HDF5TypeTraits<T>::InternalType* internal_data =
    HDF5TypeTraits<T>::initializeInternalData( data, size );
  
  // Check if the array of interest can store the contents of the attribute
  TEST_FOR_EXCEPTION( !this->canArrayStoreAttributeContents<T>( internal_data, size, *attribute ),
                      HDF5File::Exception,
                      "Cannot store the contents of data set attribute "
                      << path_to_data_set << ":" << attribute_name <<
                      " in the desired memory location!" ); 
  
  try{
    attribute->read( HDF5TypeTraits<T>::dataType(), internal_data );
  }
  HDF5_EXCEPTION_CATCH( "Could not read data from data set attribute "
                        << path_to_data_set << ":" << attribute_name << "!" );

  // Convert the internal data to the desired format
  HDF5TypeTraits<T>::convertInternalDataToExternalData( internal_data,
                                                        size,
                                                        data );

  // Clean up temporary data
  HDF5TypeTraits<T>::freeInternalData( internal_data );
#endif
}

// Write data to a group attribute
template<typename T>
void HDF5File::writeToGroupAttribute( const std::string& path_to_group,
                                      const std::string& attribute_name,
                                      const T* data,
                                      const size_t size )
{
#ifdef HAVE_FRENSIE_HDF5
  // Open the group
  std::unique_ptr<const H5::Group> group;
  
  if( !this->doesGroupExist( path_to_group ) )
    this->createGroup( path_to_group, group );
  else
    this->openGroup( path_to_group, group );

  // Make sure that the group attribute hasn't been created yet
  TEST_FOR_EXCEPTION( this->doesGroupAttributeExist( *group, attribute_name ),
                      HDF5File::Exception,
                      "Overwriting the data in an existing group attribute "
                      "(" << path_to_group << ":" << attribute_name << ")"
                      " is not currently supported!" );

  try{
    // Create the group attribute
    std::unique_ptr<H5::Attribute> attribute;

    this->createGroupAttribute<T>( *group,
                                   path_to_group,
                                   attribute_name,
                                   size,
                                   attribute );

    // Convert the data to a format that is compatible with HDF5
    typename HDF5TypeTraits<T>::InternalType* internal_data =
      HDF5TypeTraits<T>::initializeInternalData( data, size );

    HDF5TypeTraits<T>::convertExternalDataToInternalData( data, size, internal_data );
    
    attribute->write( HDF5TypeTraits<T>::dataType(), internal_data );
    
    // Clean up the temporary data
    HDF5TypeTraits<T>::freeInternalData( internal_data );
  }
  HDF5_EXCEPTION_CATCH( "Could not write data to group attribute ("
                        << path_to_group << ":" << attribute_name << ")!" );
#endif
}

// Write data to a group attribute
template<typename T>
inline void HDF5File::writeToGroupAttribute( const std::string& path_to_group,
                                             const std::string& attribute_name,
                                             const T& data )
{ this->writeToGroupAttribute( path_to_group, attribute_name, &data, 1 ); }

// Read data from a group attribute
template<typename T>
void HDF5File::readFromGroupAttribute( const std::string& path_to_group,
                                       const std::string& attribute_name,
                                       T* data,
                                       const size_t size ) const
{
#ifdef HAVE_FRENSIE_HDF5
  // Open the group
  std::unique_ptr<const H5::Group> group;

  this->openGroup( path_to_group, group );

  // Open the attribute
  std::unique_ptr<const H5::Attribute> attribute;

  this->openGroupAttribute( *group, path_to_group, attribute_name, attribute );

  // Load the data from the attribute in its internal format
  typename HDF5TypeTraits<T>::InternalType* internal_data =
    HDF5TypeTraits<T>::initializeInternalData( data, size );
  
  // Check if the array of interest can store the contents of the attribute
  TEST_FOR_EXCEPTION( !this->canArrayStoreAttributeContents<T>( internal_data, size, *attribute ),
                      HDF5File::Exception,
                      "Cannot store the contents of group attribute "
                      << path_to_group << ":" << attribute_name <<
                      " in the desired memory location!" ); 
  
  try{
    attribute->read( HDF5TypeTraits<T>::dataType(), internal_data );
  }
  HDF5_EXCEPTION_CATCH( "Could not read data from group attribute "
                        << path_to_group << ":" << attribute_name << "!" );

  // Convert the internal data to the desired format
  HDF5TypeTraits<T>::convertInternalDataToExternalData( internal_data,
                                                        size,
                                                        data );

  // Clean up temporary data
  HDF5TypeTraits<T>::freeInternalData( internal_data );
#endif
}

#ifdef HAVE_FRENSIE_HDF5

// Create a data set
template<typename T>
void HDF5File::createDataSet( const std::string& path_to_data_set,
                              const size_t array_size,
                              std::unique_ptr<H5::DataSet>& data_set )
{
  try{
    hsize_t data_set_size =
      HDF5TypeTraits<T>::calculateInternalDataSize( array_size );
    
    H5::DataSpace space( 1, &data_set_size );

    data_set.reset( new H5::DataSet( d_hdf5_file->createDataSet(
                                                 path_to_data_set,
                                                 HDF5TypeTraits<T>::dataType(),
                                                 space ) ) );
  }
  HDF5_EXCEPTION_CATCH( "Could not create data set "
                        << path_to_data_set << "!" );
}

// Create a data set attribute
template<typename T>
void HDF5File::createDataSetAttribute( const H5::DataSet& data_set,
                                       const std::string& data_set_name,
                                       const std::string& attribute_name,
                                       const size_t array_size,
                                       std::unique_ptr<H5::Attribute>& attribute )
{
  try{
    hsize_t attribute_size =
      HDF5TypeTraits<T>::calculateInternalDataSize( array_size );
    
    H5::DataSpace space( 1, &attribute_size );
    
    attribute.reset( new H5::Attribute( data_set.createAttribute(
                                                 attribute_name,
                                                 HDF5TypeTraits<T>::dataType(),
                                                 space ) ) );
  }
  HDF5_EXCEPTION_CATCH( "Could not create data set attribute "
                        << data_set_name << ":" << attribute_name << "!" );
}

// Create a group attribute
template<typename T>
void HDF5File::createGroupAttribute( const H5::Group& group,
                                     const std::string& group_name,
                                     const std::string& attribute_name,
                                     const size_t array_size,
                                     std::unique_ptr<H5::Attribute>& attribute )
{
  try{
    hsize_t attribute_size =
      HDF5TypeTraits<T>::calculateInternalDataSize( array_size );
    
    H5::DataSpace space( 1, &attribute_size );
    
    attribute.reset( new H5::Attribute( group.createAttribute(
                                                 attribute_name,
                                                 HDF5TypeTraits<T>::dataType(),
                                                 space ) ) );
  }
  HDF5_EXCEPTION_CATCH( "Could not create group attribute "
                        << group_name << ":" << attribute_name << "!" );
}

// Check that the type matches the data set type
template<typename T>
bool HDF5File::doesDataSetTypeMatch( const T& data_type,
                                     const H5::DataSet& data_set ) const
{
  try{
    H5::DataType data_set_data_type;
    data_set_data_type.copy( data_set );

    return data_set_data_type == data_type;
  }
  catch( ... )
  {
    return false;
  }
}

// Check that the type matches the attribute type
template<typename T>
bool HDF5File::doesAttributeTypeMatch( const T& data_type,
                                       const H5::Attribute& attribute ) const
{
  // For some reason, H5::Attribute has no getType method - we will use the
  // C interface instead
  try{
    hid_t attribute_data_type_id = H5Aget_type( attribute.getId() );
    
    H5::DataType attribute_type( attribute_data_type_id );

    const bool do_types_match = attribute_type == data_type;

    attribute_type.close();

    return do_types_match;
  }
  catch( ... )
  {
    return false;
  }
}


// Check if an array can store the contents of a data set
template<typename ExternalT, typename InternalT>
bool HDF5File::canArrayStoreDataSetContents( const InternalT*,
                                             const size_t size,
                                             const H5::DataSet& data_set ) const
{
  // Check that the types are equal
  if( !this->doesDataSetTypeMatch( HDF5TypeTraits<ExternalT>::dataType(), data_set ) )
    return false;
  
  // Check that the sizes are equal
  if( HDF5TypeTraits<ExternalT>::calculateInternalDataSize( size ) != this->getDataSetSize( data_set ) )
    return false;

  return true;
}

// Check if an array can store the contents of a data set attribute
template<typename ExternalT, typename InternalT>
bool HDF5File::canArrayStoreAttributeContents(
                                         const InternalT*,
                                         const size_t size,
                                         const H5::Attribute& attribute ) const
{
  // Check that the types are equal
  if( !this->doesAttributeTypeMatch( HDF5TypeTraits<ExternalT>::dataType(), attribute ) )
    return false;

  // Check that the sizes are equal
  if( HDF5TypeTraits<ExternalT>::calculateInternalDataSize( size ) != this->getAttributeSize( attribute ) )
    return false;

  return true;
}

#endif // end HAVE_FRENSIE_HDF5

namespace Details{

/*! Helper used to determine if a container has a contiguous memory layout
 * \ingroup hdf5
 */
template<typename Container, typename Enabled = void>
struct IsContiguousMemoryContainer : public std::false_type
{ /* ... */ };

/*! Specialization of ContiguousMemoryContainer for std::string
 * \ingroup hdf5
 */
template<>
struct IsContiguousMemoryContainer<std::string> : public std::true_type
{ /* ... */ };

/*! Specialization of ContiguousMemoryContainer for std::wstring
 * \ingroup hdf5
 */
template<>
struct IsContiguousMemoryContainer<std::wstring> : public std::true_type
{ /* ... */ };

/*! Specialization of ContiguousMemoryContainer for std::vector
 *
 * std::vector<bool> is a specialization of std::vector and it is not
 * guaranteed to be implemented as a contiguous memory container.
 * \ingroup hdf5
 */
template<typename T>
struct IsContiguousMemoryContainer<std::vector<T>,typename std::enable_if<!std::is_same<T,bool>::value>::type> : public std::true_type
{ /* ... */ };

/*! Specialization of ContiguousMemoryContainer for std::array
 * \ingroup HDF5
 */
template<typename T, size_t N>
struct IsContiguousMemoryContainer<std::array<T,N> > : public std::true_type
{ /* ... */ };

/*! Specialization of ContiguousMemoryContainer for Utility::ArrayView
 * \ingroup HDF5
 */
template<typename T>
struct IsContiguousMemoryContainer<Utility::ArrayView<T> > : public std::true_type
{ /* ... */ };

/*! Specialization of ContiguousMemoryContainer for Utility::ArrayView of const
 * \ingroup HDF5
 */
template<typename T>
struct IsContiguousMemoryContainer<Utility::ArrayView<const T> > : public std::true_type
{ /* ... */ };

/*! \brief Helper used to copy contents of a container that does not have 
 * contiguous memory to an array (usually a std::vector)
 * \ingroup hdf5
 */
template<typename Container, typename Enable = void>
struct CopyContainerContentsToFromArrayHelper;

/*! \brief Specialization of CopyContainerContentsToFromArrayHelper for
 * containers with a value_type==bool
 * \ingroup hdf5
 */
template<template<typename,typename...> class Container, typename T>
struct CopyContainerContentsToFromArrayHelper<Container<T>,typename std::enable_if<std::is_same<T,typename Container<T>::value_type>::value && std::is_same<T,bool>::value>::type>
{
  struct ArrayType : private boost::noncopyable
  {
    typedef bool value_type;
    typedef bool* pointer;
    
    ArrayType()
      : d_data( NULL ), d_size( 0 )
    { /* ... */ }
    
    ArrayType( const size_t size )
      : d_data( new bool[size] ), d_size( size )
    { /* ... */ }

    ~ArrayType()
    { this->clear(); }

    void resize( const size_t size )
    {
      this->clear();
      
      d_data = new bool[size];
      d_size = size;
    }
    
    size_t size() const
    { return d_size; }

    bool* data()
    { return d_data; }

    const bool* data() const
    { return d_data; }

    bool& operator[]( const size_t i )
    { return d_data[i]; }

    const bool& operator[]( const size_t i ) const
    { return d_data[i]; }

    void clear()
    {
      if( d_data )
      {
        delete[] d_data;
        d_data = NULL;
      }
      
      d_size = 0;
    }

  private:

    bool* d_data;
    size_t d_size;
  };

  static inline void resizeArray( ArrayType& container_copy,
                                  const size_t size )
  { container_copy.resize( size ); }
  
  static inline void copyToArray( const Container<bool>& container,
                                  ArrayType& container_copy )
  {
    // Get the container size using its iterators
    // (required by std::forward_list )
    container_copy.resize( std::distance( container.begin(), container.end() ) );

    typename Container<bool>::const_iterator it = container.begin();
    bool* copy_it = container_copy.data();
    
    while( it != container.end() )
    {
      *copy_it = *it;

      ++it;
      ++copy_it;
    }
  }

  static inline void copyFromArray( Container<bool>& container,
                                    const ArrayType& container_copy )
  {
    container = Container<bool>( container_copy.data(),
                                 container_copy.data()+container_copy.size() );
  }

  static inline void freeArray( ArrayType& container_copy )
  { container_copy.clear(); }
};

/*! \brief Specialization of CopyContainerContentsToFromArrayHelper for non-map 
 * containers
 * \ingroup hdf5
 */
template<template<typename,typename...> class Container, typename T>
struct CopyContainerContentsToFromArrayHelper<Container<T>,typename std::enable_if<std::is_same<T,typename Container<T>::value_type>::value && !std::is_same<T,bool>::value>::type>
{
  typedef std::vector<T> ArrayType;
  
  static inline void copyToArray( const Container<T>& container,
                                  ArrayType& container_copy )
  { container_copy.assign( container.begin(), container.end() ); }

  static inline void copyFromArray( Container<T>& container,
                                    const ArrayType& container_copy )
  { container = Container<T>( container_copy.begin(), container_copy.end() ); }

  static inline void freeArray( ArrayType& container_copy )
  { container_copy.clear(); }
};

/*! \brief Specialization of CopyContainerContentsToFromArrayHelper for map 
 * containers
 * \ingroup hdf5
 */
template<template<typename,typename,typename...> class Container,
         typename Key, typename T>
struct CopyContainerContentsToFromArrayHelper<Container<Key,T>,typename std::enable_if<!std::is_same<Key,typename Container<Key,T>::value_type>::value>::type>
{
  typedef std::vector<std::pair<Key,T> > ArrayType;
  
  static inline void copyToArray( const Container<Key,T>& container,
                                   ArrayType& container_copy )
  { container_copy.assign( container.begin(), container.end() ); }

  static inline void copyFromArray( Container<Key,T>& container,
                                     const ArrayType& container_copy )
  { container.insert( container_copy.begin(), container_copy.end() ); }

  static inline void freeArray( ArrayType& container_copy )
  { container_copy.clear(); }
};

/*! Implementation of writeToDataSet for containers with contiguous memory
 * \ingroup HDF5
 */
template<typename Container>
inline void writeToDataSetImpl( HDF5File& hdf5_file,
                                const std::string& path_to_data_set,
                                const Container& container,
                                std::true_type )
{
  hdf5_file.writeToDataSet( path_to_data_set, container.data(), container.size() );
}

/*! \brief Implementation of writeToDataSet for containers with memory that is
 * not contiguous
 * \ingroup HDF5
 */
template<typename Container>
inline void writeToDataSetImpl( HDF5File& hdf5_file,
                                const std::string& path_to_data_set,
                                const Container& container,
                                std::false_type )
{
  typename CopyContainerContentsToFromArrayHelper<Container>::ArrayType container_copy;

  CopyContainerContentsToFromArrayHelper<Container>::copyToArray( container, container_copy );

  hdf5_file.writeToDataSet( path_to_data_set, container_copy.data(), container_copy.size() );

  CopyContainerContentsToFromArrayHelper<Container>::freeArray( container_copy );
}

/*! \brief Implementation of writeToDataSetAttribute for containers with 
 * contiguous memory
 * \ingroup HDF5
 */
template<typename Container>
inline void writeToDataSetAttributeImpl( HDF5File& hdf5_file,
                                         const std::string& path_to_data_set,
                                         const std::string& attribute_name,
                                         const Container& container,
                                         std::true_type )
{
  hdf5_file.writeToDataSetAttribute( path_to_data_set, attribute_name, container.data(), container.size() );
}

/*! \brief Implementation of writeToDataSetAttribute for containers with 
 * memory that is not contiguous
 * \ingroup HDF5
 */
template<typename Container>
inline void writeToDataSetAttributeImpl( HDF5File& hdf5_file,
                                         const std::string& path_to_data_set,
                                         const std::string& attribute_name,
                                         const Container& container,
                                         std::false_type )
{
  typename CopyContainerContentsToFromArrayHelper<Container>::ArrayType container_copy;

  CopyContainerContentsToFromArrayHelper<Container>::copyToArray( container, container_copy );

  hdf5_file.writeToDataSetAttribute( path_to_data_set, attribute_name, container_copy.data(), container_copy.size() );

  CopyContainerContentsToFromArrayHelper<Container>::freeArray( container_copy );
}

/*! \brief Implementation of writeToGroupAttribute for containers with 
 * contiguous memory
 * \ingroup HDF5
 */
template<typename Container>
inline void writeToGroupAttributeImpl( HDF5File& hdf5_file,
                                       const std::string& path_to_group,
                                       const std::string& attribute_name,
                                       const Container& container,
                                       std::true_type )
{
  hdf5_file.writeToGroupAttribute( path_to_group, attribute_name, container.data(), container.size() );
}

/*! \brief Implementation of writeToGroupAttribute for containers with 
 * memory that is not contiguous
 * \ingroup HDF5
 */
template<typename Container>
inline void writeToGroupAttributeImpl( HDF5File& hdf5_file,
                                       const std::string& path_to_group,
                                       const std::string& attribute_name,
                                       const Container& container,
                                       std::false_type )
{
  typename CopyContainerContentsToFromArrayHelper<Container>::ArrayType container_copy;

  CopyContainerContentsToFromArrayHelper<Container>::copyToArray( container, container_copy );

  hdf5_file.writeToGroupAttribute( path_to_group, attribute_name, container_copy.data(), container_copy.size() );

  CopyContainerContentsToFromArrayHelper<Container>::freeArray( container_copy );
}
  
} // end Details namespace
    
// Write a container to a data set
/*! \ingroup hdf5
 */
template<typename Container>
void writeToDataSet( HDF5File& hdf5_file,
                     const std::string& path_to_data_set,
                     const Container& container )
{
  Details::writeToDataSetImpl( hdf5_file,
                               path_to_data_set,
                               container,
                               Details::IsContiguousMemoryContainer<Container>() );
}

// Write an initializer list to a data set
/*! \ingroup hdf5
 */
template<typename T>
inline void writeToDataSet( HDF5File& hdf5_file,
                            const std::string& path_to_data_set,
                            std::initializer_list<T> container )
{
  hdf5_file.writeToDataSet( path_to_data_set,
                            container.begin(),
                            container.size() );
}

// Write a container to a data set attribute
/*! \ingroup hdf5
 */
template<typename Container>
void writeToDataSetAttribute( HDF5File& hdf5_file,
                              const std::string& path_to_data_set,
                              const std::string& attribute_name,
                              const Container& container )
{
  Details::writeToDataSetAttributeImpl( hdf5_file,
                                        path_to_data_set,
                                        attribute_name,
                                        container,
                                        Details::IsContiguousMemoryContainer<Container>() );
}

// Write an initializer list to a data set attribute
/*! \ingroup hdf5
 */
template<typename T>
inline void writeToDataSetAttribute( HDF5File& hdf5_file,
                                     const std::string& path_to_data_set,
                                     const std::string& attribute_name,
                                     std::initializer_list<T> container )
{
  hdf5_file.writeToDataSetAttribute( path_to_data_set,
                                     attribute_name,
                                     container.begin(),
                                     container.size() );
}

// Write a container to a group attribute
/*! \ingroup hdf5
 */
template<typename Container>
void writeToGroupAttribute( HDF5File& hdf5_file,
                            const std::string& path_to_group,
                            const std::string& attribute_name,
                            const Container& container )
{
  Details::writeToGroupAttributeImpl( hdf5_file,
                                      path_to_group,
                                      attribute_name,
                                      container,
                                      Details::IsContiguousMemoryContainer<Container>() );
}

// Write an initializer list to a group attribute
/*! \ingroup hdf5
 */
template<typename T>
void writeToGroupAttribute( HDF5File& hdf5_file,
                            const std::string& path_to_group,
                            const std::string& attribute_name,
                            std::initializer_list<T> container )
{
  hdf5_file.writeToGroupAttribute( path_to_group,
                                   attribute_name,
                                   container.begin(),
                                   container.size() );
}

namespace Details{

/*! Implementation of readFromDataSet for containers with contiguous memory
 * \ingroup HDF5
 */
template<typename Container>
inline void readFromDataSetImpl( const HDF5File& hdf5_file,
                                 const std::string& path_to_data_set,
                                 Container& container,
                                 std::true_type )
{
  // Extract the data set size
  HDF5_ENABLED_DISABLED_SWITCH(hsize_t,size_t) data_set_size =
    hdf5_file.getDataSetSize( path_to_data_set );

  container.resize( Utility::HDF5TypeTraits<typename Container::value_type>::calculateExternalDataSize( data_set_size ) );

  // Note: we have to do a const cast of the pointer returned by the data
  //       method since std::string will return a const pointer regardless of
  //       the const qualifier of the string
  hdf5_file.readFromDataSet( path_to_data_set,
                             const_cast<typename Container::pointer>(container.data()),
                             container.size() );
}

/*! \brief Implementation of readFromDataSet for containers with memory that is
 * not contiguous
 * \ingroup HDF5
 */
template<typename Container>
inline void readFromDataSetImpl( const HDF5File& hdf5_file,
                                 const std::string& path_to_data_set,
                                 Container& container,
                                 std::false_type )
{
  typename CopyContainerContentsToFromArrayHelper<Container>::ArrayType container_copy;

  Details::readFromDataSetImpl( hdf5_file, path_to_data_set, container_copy, std::true_type() );

  CopyContainerContentsToFromArrayHelper<Container>::copyFromArray( container, container_copy );

  CopyContainerContentsToFromArrayHelper<Container>::freeArray( container_copy );
}

/*! \brief Implementation of readFromDataSetAttribute for containers with 
 * contiguous memory
 * \ingroup HDF5
 */
template<typename Container>
inline void readFromDataSetAttributeImpl( const HDF5File& hdf5_file,
                                          const std::string& path_to_data_set,
                                          const std::string& attribute_name,
                                          Container& container,
                                          std::true_type )
{
  // Extract the data set size
  HDF5_ENABLED_DISABLED_SWITCH(hsize_t,size_t) data_set_attribute_size =
    hdf5_file.getDataSetAttributeSize( path_to_data_set, attribute_name );

  container.resize( Utility::HDF5TypeTraits<typename Container::value_type>::calculateExternalDataSize( data_set_attribute_size ) );
  
  hdf5_file.readFromDataSetAttribute( path_to_data_set,
                                      attribute_name,
                                      const_cast<typename Container::pointer>(container.data()),
                                      container.size() );
}

/*! \brief Implementation of readFromDataSetAttribute for containers with 
 * memory that is not contiguous
 * \ingroup HDF5
 */
template<typename Container>
inline void readFromDataSetAttributeImpl( const HDF5File& hdf5_file,
                                          const std::string& path_to_data_set,
                                          const std::string& attribute_name,
                                          Container& container,
                                          std::false_type )
{
  typename CopyContainerContentsToFromArrayHelper<Container>::ArrayType container_copy;

  Details::readFromDataSetAttributeImpl( hdf5_file, path_to_data_set, attribute_name, container_copy, std::true_type() );

  CopyContainerContentsToFromArrayHelper<Container>::copyFromArray( container, container_copy );

  CopyContainerContentsToFromArrayHelper<Container>::freeArray( container_copy );
}

/*! \brief Implementation of readFromGroupAttribute for containers with 
 * contiguous memory
 * \ingroup HDF5
 */
template<typename Container>
inline void readFromGroupAttributeImpl( const HDF5File& hdf5_file,
                                        const std::string& path_to_group,
                                        const std::string& attribute_name,
                                        Container& container,
                                        std::true_type )
{
  // Extract the data set size
  HDF5_ENABLED_DISABLED_SWITCH(hsize_t,size_t) group_attribute_size =
    hdf5_file.getGroupAttributeSize( path_to_group, attribute_name );

  container.resize( Utility::HDF5TypeTraits<typename Container::value_type>::calculateExternalDataSize( group_attribute_size ) );
  
  hdf5_file.readFromGroupAttribute( path_to_group,
                                    attribute_name,
                                    const_cast<typename Container::pointer>(container.data()),
                                    container.size() );
}

/*! \brief Implementation of readFromGroupAttribute for containers with 
 * memory that is not contiguous
 * \ingroup HDF5
 */
template<typename Container>
inline void readFromGroupAttributeImpl( const HDF5File& hdf5_file,
                                        const std::string& path_to_group,
                                        const std::string& attribute_name,
                                        Container& container,
                                        std::false_type )
{
  typename CopyContainerContentsToFromArrayHelper<Container>::ArrayType container_copy;

  Details::readFromGroupAttributeImpl( hdf5_file, path_to_group, attribute_name, container_copy, std::true_type() );

  CopyContainerContentsToFromArrayHelper<Container>::copyFromArray( container, container_copy );

  CopyContainerContentsToFromArrayHelper<Container>::freeArray( container_copy );
}
  
} // end Details namespace

// Read a container from a data set
/*! \details Only containers that can be resized can be passed to this method
 * (std::array and Utility::ArrayView cannot be used).
 * \ingroup hdf5
 */
template<typename Container>
void readFromDataSet( const HDF5File& hdf5_file,
                      const std::string& path_to_data_set,
                      Container& container )
{
  Details::readFromDataSetImpl( hdf5_file,
                                path_to_data_set,
                                container,
                                Details::IsContiguousMemoryContainer<Container>() );
}

// Read a container from a data set attribute
/*! \details Only containers that can be resized can be passed to this method
 * (std::array and Utility::ArrayView cannot be used).
 * \ingroup hdf5
 */
template<typename Container>
void readFromDataSetAttribute( const HDF5File& hdf5_file,
                               const std::string& path_to_data_set,
                               const std::string& attribute_name,
                               Container& container )
{
  Details::readFromDataSetAttributeImpl( hdf5_file,
                                         path_to_data_set,
                                         attribute_name,
                                         container,
                                         Details::IsContiguousMemoryContainer<Container>() );
}

// Read a container from a group attribute
/*! \details Only containers that can be resized can be passed to this method
 * (std::array and Utility::ArrayView cannot be used).
 * \ingroup hdf5
 */
template<typename Container>
void readFromGroupAttribute( const HDF5File& hdf5_file,
                             const std::string& path_to_group,
                             const std::string& attribute_name,
                             Container& container )
{
  Details::readFromGroupAttributeImpl( hdf5_file,
                                       path_to_group,
                                       attribute_name,
                                       container,
                                       Details::IsContiguousMemoryContainer<Container>() );
}

} // end Utility namespace

#endif // end UTILITY_HDF5_FILE_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_HDF5File_def.hpp
//---------------------------------------------------------------------------//
