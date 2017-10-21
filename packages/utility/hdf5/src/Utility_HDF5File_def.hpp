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
#include "Utility_ContractException.hpp"

namespace Utility{

// Write data to a data set
/*! \details Once a data set has been created its allocated memory cannot be
 * reduced or freed. While increasing it is possible, data sets that allow this
 * operation use chunked data, which can incur a large performance penalty. 
 * Furthermore, it isn't obvious how we would determine the optimal chunk size.
 * 
 */ 
template<typename T>
void HDF5File::writeToDataSet( const std::string& path_to_data_set,
                               const T* data,
                               const size_t size )
{
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
}

// Read data from a data set
template<typename T>
void HDF5File::readFromDataSet( const std::string& path_to_data_set,
                                T* data,
                                const size_t size ) const
{
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
}

// Write data to a data set attribute
template<typename T>
void HDF5File::writeToDataSetAttribute( const std::string& path_to_data_set,
                                        const std::string& attribute_name,
                                        const T* data,
                                        const size_t size )
{
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
}
  
// Read data from a data set attribute
template<typename T>
void HDF5File::readFromDataSetAttribute( const std::string& path_to_data_set,
                                         const std::string& attribute_name,
                                         T* data,
                                         const size_t size ) const
{
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
}

// Write data to a group attribute
template<typename T>
void HDF5File::writeToGroupAttribute( const std::string& path_to_group,
                                      const std::string& attribute_name,
                                      const T* data,
                                      const size_t size )
{
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
}

// Read data from a group attribute
template<typename T>
void HDF5File::readFromGroupAttribute( const std::string& path_to_group,
                                       const std::string& attribute_name,
                                       T* data,
                                       const size_t size ) const
{
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
}

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

} // end Utility namespace

#endif // end UTILITY_HDF5_FILE_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_HDF5File_def.hpp
//---------------------------------------------------------------------------//
