//---------------------------------------------------------------------------//
//!
//! \file   Utility_HDF5File.cpp
//! \author Alex Robinson
//! \brief  The hdf5 file class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_HDF5File.hpp"
#include "Utility_LoggingMacros.hpp"
#include "FRENSIE_config.hpp"

namespace Utility{

namespace Details{

// Enable exceptions in hdf5
void enableExceptionsInHDF5()
{
#ifdef HAVE_FRENSIE_HDF5
  static bool hdf5_exceptions_enabled = false;
  
  try{
    H5::Exception::dontPrint();
    hdf5_exceptions_enabled = true;
  }
  HDF5_EXCEPTION_CATCH( "Could not enable exceptions in HDF5!" );
#endif // end HAVE_FRENSIE_HDF5
}
  
} // end Details namespace

/*! \brief Specialization of Utility::HDF5TypeTraits for void
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<void> : public Details::BasicHDF5TypeTraits<void,1>
{
  //! Check if the type has an opaque data type
  typedef std::true_type UsesOpaqueDataType;
  
  //! Returns the HDF5 data type object corresponding to void
  static inline HDF5_ENABLED_DISABLED_SWITCH(const H5::PredType&,int) dataType()
  { return HDF5_ENABLED_DISABLED_SWITCH(H5::PredType::NATIVE_OPAQUE,0); }
};

// Constructor
HDF5File::Exception::Exception( const std::string& message )
  : std::runtime_error( message )
{ /* ... */ }

// Constructor (extra details)
HDF5File::Exception::Exception( const std::string& file,
                                const size_t line,
                                const std::string& hdf5_function_name,
                                const std::string& hdf5_error_message,
                                const std::string& message )
  : std::runtime_error( HDF5File::Exception::createErrorMessage( file, line, hdf5_function_name, hdf5_error_message, message ) )
{ /* ... */ }

// Create an error message
std::string HDF5File::Exception::createErrorMessage(
                                         const std::string& file,
                                         const size_t line,
                                         const std::string& hdf5_function_name,
                                         const std::string& hdf5_error_message,
                                         const std::string& message )
{
  std::ostringstream detailed_message;

  detailed_message << FRENSIE_LOG_ERROR_MSG << message << "\n"
                   << FRENSIE_LOG_EXCEPTION_TYPE_MSG
                   << "H5::Exception" << FRENSIE_LOG_ARROW_SEP
                   << "Utility::HDF5File::Exception" << "\n"
                   << "  HDF5 " << FRENSIE_LOG_STACK_MSG_BASIC << " "
                   << hdf5_function_name << "\n"
                   << "  HDF5 Error Msg: " << hdf5_error_message << "\n"
                   << FRENSIE_LOG_LOCATION_MSG
                   << file << FRENSIE_LOG_FILE_LINE_SEP << line << "\n";

  return detailed_message.str();
}

// Constructor
HDF5File::HDF5File( const std::string& filename,
                    const HDF5File::OpenMode mode )
  : d_filename( filename ),
    d_hdf5_file()
{
#ifdef HAVE_FRENSIE_HDF5
  Details::enableExceptionsInHDF5();
  
  switch( mode )
  {
    case READ_ONLY:
    {
      try{
        d_hdf5_file.reset( new H5::H5File( filename, H5F_ACC_RDONLY ) );
      }
      HDF5_EXCEPTION_CATCH( "Could not open hdf5 file " << filename <<
                            " in read-only mode!" );
      break;
    }
    case READ_WRITE:
    {
      try{
        d_hdf5_file.reset( new H5::H5File( filename, H5F_ACC_RDWR ) );
      }
      HDF5_EXCEPTION_CATCH( "Could not open hdf5 file " << filename <<
                            " in read-write mode!" );
      break;
    }
    case OVERWRITE:
    {
      try{
        d_hdf5_file.reset( new H5::H5File( filename, H5F_ACC_TRUNC ) );
      }
      HDF5_EXCEPTION_CATCH( "Could not open hdf5 file " << filename <<
                            "and overwrite it!" );
      break;
    }
    default:
    {
      THROW_EXCEPTION( HDF5File::Exception, "Unknown HDF5 file open mode!" );
    }
  }
#else
  THROW_EXCEPTION( std::logic_error, "HDF5 has not been enabled!" );
#endif // end FRENSIE_HDF5
}

// Destructor
HDF5File::~HDF5File()
{ /* ... */ }

// Get the file name
const std::string& HDF5File::getFilename() const throw()
{
  return d_filename;
}

// Check if the group exists
bool HDF5File::doesGroupExist( const std::string& path_to_group ) const throw()
{
#ifdef HAVE_FRENSIE_HDF5
  try{
    std::unique_ptr<const H5::Group> group;
    this->openGroup( path_to_group, group );
  }
  catch( ... )
  {
    return false;
  }
  
  return true;
#else
  return false;
#endif
}

// Check if the group attribute exists
bool HDF5File::doesGroupAttributeExist( const std::string& path_to_group,
                                        const std::string& attribute_name ) const throw()
{
#ifdef HAVE_FRENSIE_HDF5
  if( this->doesGroupExist( path_to_group ) )
  {
    std::unique_ptr<const H5::Group> group;
    this->openGroup( path_to_group, group );

    return this->doesGroupAttributeExist( *group, attribute_name );
  }
  else
    return false;
#else
  return false;
#endif // end HAVE_FRENSIE_HDF5
}

// Check if the data set exists
bool HDF5File::doesDataSetExist( const std::string& path_to_data_set ) const throw()
{
#ifdef HAVE_FRENSIE_HDF5
  try{
    std::unique_ptr<const H5::DataSet> data_set;
    this->openDataSet( path_to_data_set, data_set );
  }
  catch( ... )
  {
    return false;
  }

  return true;
#else
  return false;
#endif
}

// Check if the data set attribute exists
bool HDF5File::doesDataSetAttributeExist( const std::string& path_to_data_set,
                                          const std::string& attribute_name ) const throw()
{
#ifdef HAVE_FRENSIE_HDF5
  if( this->doesDataSetExist( path_to_data_set ) )
  {
    std::unique_ptr<const H5::DataSet> data_set;
    this->openDataSet( path_to_data_set, data_set );

    return this->doesDataSetAttributeExist( *data_set, attribute_name );
  }
  else
    return false;
#else
  return false;
#endif
}

// Get the size of a data set
HDF5_ENABLED_DISABLED_SWITCH(hsize_t,size_t) HDF5File::getDataSetSize(
                                    const std::string& path_to_data_set ) const
{
#ifdef HAVE_FRENSIE_HDF5
  std::unique_ptr<const H5::DataSet> data_set;
  
  this->openDataSet( path_to_data_set, data_set );
  
  return this->getDataSetSize( *data_set );
#else
  return 0;
#endif
}

// Get the size of a data set attribute
HDF5_ENABLED_DISABLED_SWITCH(hsize_t,size_t) HDF5File::getDataSetAttributeSize(
                                      const std::string& path_to_data_set,
                                      const std::string& attribute_name ) const
{
#ifdef HAVE_FRENSIE_HDF5
  std::unique_ptr<const H5::DataSet> data_set;
  
  this->openDataSet( path_to_data_set, data_set );

  std::unique_ptr<const H5::Attribute> attribute;

  this->openDataSetAttribute( *data_set, path_to_data_set, attribute_name, attribute );

  return this->getAttributeSize( *attribute );
#else
  return 0;
#endif
}

// Get the size of a group attribute
HDF5_ENABLED_DISABLED_SWITCH(hsize_t,size_t) HDF5File::getGroupAttributeSize(
                                      const std::string& path_to_group,
                                      const std::string& attribute_name ) const
{
#ifdef HAVE_FRENSIE_HDF5
  std::unique_ptr<const H5::Group> group;

  this->openGroup( path_to_group, group );

  std::unique_ptr<const H5::Attribute> attribute;

  this->openGroupAttribute( *group, path_to_group, attribute_name, attribute );

  return this->getAttributeSize( *attribute );
#else
  return 0;
#endif
}

// Create a group
void HDF5File::createGroup( const std::string& path_to_group )
{
#ifdef HAVE_FRENSIE_HDF5
  // Check if the group exists
  if( !this->doesGroupExist( path_to_group ) )
  {
    std::unique_ptr<const H5::Group> group;

    try{
      this->createGroup( path_to_group, group );
    }
    HDF5_EXCEPTION_CATCH( "Could not create group " << path_to_group << "!" );
  }
#endif  
}

// Create a hard link
void HDF5File::createHardLink( const std::string& existing_object_path,
                               const std::string& path_to_link )
{
#ifdef HAVE_FRENSIE_HDF5
  try{
    // Check if the parent group needs to be created first
    if( !this->doesParentGroupExist( path_to_link ) )
      this->createParentGroup( path_to_link );
    
    d_hdf5_file->link( H5L_TYPE_HARD, existing_object_path, path_to_link );
  }
  HDF5_EXCEPTION_CATCH( "Could not create a hard link with name "
                        << path_to_link << " that points to object "
                        << existing_object_path << "!" );
#endif
}

// Create a soft link
void HDF5File::createSoftLink( const std::string& existing_object_path,
                               const std::string& path_to_link )
{
#ifdef HAVE_FRENSIE_HDF5
  try{
    // Check if the parent group needs to be created first
    if( !this->doesParentGroupExist( path_to_link ) )
      this->createParentGroup( path_to_link );
    
    d_hdf5_file->link( H5L_TYPE_SOFT, existing_object_path, path_to_link );
  }
  HDF5_EXCEPTION_CATCH( "Could not create a soft link with name "
                        << path_to_link << " that points to object "
                        << existing_object_path << "!" );
#endif
}

// Write opaque data to a data set
void HDF5File::writeToDataSet( const std::string& path_to_data_set,
                               const void* data,
                               const size_t size )
{
  this->writeToDataSet<void>( path_to_data_set, data, size );
}

// Read data from a data set
void HDF5File::readFromDataSet( const std::string& path_to_data_set,
                                void* data,
                                const size_t size ) const
{
  this->readFromDataSet<void>( path_to_data_set, data, size );
}

// Write data to a data set attribute
void HDF5File::writeToDataSetAttribute( const std::string& path_to_data_set,
                                        const std::string& attribute_name,
                                        const void* data,
                                        const size_t size )
{
  this->writeToDataSetAttribute<void>( path_to_data_set, attribute_name, data, size );
}

// Read data from a data set attribute
void HDF5File::readFromDataSetAttribute( const std::string& path_to_data_set,
                                         const std::string& attribute_name,
                                         void* data,
                                         const size_t size ) const
{
  this->readFromDataSetAttribute<void>( path_to_data_set, attribute_name, data, size );
}

// Write data to a group attribute
void HDF5File::writeToGroupAttribute( const std::string& path_to_group,
                                      const std::string& attribute_name,
                                      const void* data,
                                      const size_t size )
{
  this->writeToGroupAttribute<void>( path_to_group, attribute_name, data, size );
}

// Read data from a group attribute
void HDF5File::readFromGroupAttribute( const std::string& path_to_group,
                                       const std::string& attribute_name,
                                       void* data,
                                       const size_t size ) const
{
  this->readFromGroupAttribute<void>( path_to_group, attribute_name, data, size );
}

// Extract the parent group path
std::string HDF5File::extractParentGroupPath( const std::string& path ) const
{
  // Start the search for the group name deliminator from the second-to-last
  // character in case the current path is a group path (ends with "/")
  TEST_FOR_EXCEPTION( path.empty(),
                      HDF5File::Exception,
                      "All paths must be absolute (the staring character "
                      "must be '/')" );
  
  TEST_FOR_EXCEPTION( path.front() != '/',
                      HDF5File::Exception,
                      "All paths must be absolute (the staring character "
                      "must be '/')" );
  
  if( path.size() > 1 )
  {
    size_t loc = path.find_last_of( "/", path.size()-2 );

    return path.substr( 0, loc+1 );
  }
  else
    return path;
}

// Check if the parent group exists
bool HDF5File::doesParentGroupExist( const std::string& path ) const
{
#ifdef HAVE_FRENSIE_HDF5
  try{
    std::unique_ptr<const H5::Group> group;
    this->openGroup( this->extractParentGroupPath( path ), group );
  }
  catch( ... )
  {
    return false;
  }

  return true;
#else
  return false;
#endif
}

// Create the parent group, if necessary, for the specified path
void HDF5File::createParentGroup( const std::string& path )
{
#ifdef HAVE_FRENSIE_HDF5
  // Extract the parent group path
  std::string parent_group_path = this->extractParentGroupPath( path );

  std::unique_ptr<const H5::Group> group;
  this->createGroup( this->extractParentGroupPath( path ), group );
#endif
}

#ifdef HAVE_FRENSIE_HDF5

// Check if the group attribute exists
bool HDF5File::doesGroupAttributeExist( const H5::Group& group,
                                        const std::string& attribute_name ) const
{
  return group.attrExists( attribute_name );
}

// Check if the data set attribute exists
bool HDF5File::doesDataSetAttributeExist( const H5::DataSet& data_set,
                                          const std::string& attribute_name ) const
{
  return data_set.attrExists( attribute_name );
}

// Get the size of a data set
HDF5_ENABLED_DISABLED_SWITCH(hsize_t,size_t) HDF5File::getDataSetSize(
                                            const H5::DataSet& data_set ) const
{
  return this->getDataSpaceSize( data_set.getSpace() );
}

// Get the size of an attribute
HDF5_ENABLED_DISABLED_SWITCH(hsize_t,size_t) HDF5File::getAttributeSize(
                                         const H5::Attribute& attribute ) const
{
  return this->getDataSpaceSize( attribute.getSpace() );
}

// Get the size of a data space
HDF5_ENABLED_DISABLED_SWITCH(hsize_t,size_t) HDF5File::getDataSpaceSize(
                                        const H5::DataSpace& data_space ) const
{
  int rank = data_space.getSimpleExtentNdims();

  hsize_t dimension_sizes[rank];
    
  data_space.getSimpleExtentDims( dimension_sizes, NULL );

  hsize_t size = 0;
  
  for( int i = 0; i < rank; ++i )
    size += dimension_sizes[i];
  
  return size;
}

// Create a group
void HDF5File::createGroup( const std::string& path_to_group,
                            std::unique_ptr<const H5::Group>& group )
{
  // Recursively create any parent groups that are missing
  if( !this->doesParentGroupExist( path_to_group ) )
    this->createParentGroup( path_to_group );
  
  try{
    group.reset( new H5::Group( d_hdf5_file->createGroup( path_to_group ) ) );
  }
  HDF5_EXCEPTION_CATCH( "Could not create group " << path_to_group << "!" );
}

// Open a group
void HDF5File::openGroup( const std::string& path_to_group,
                          std::unique_ptr<const H5::Group>& group ) const
{
  try{
    group.reset( new H5::Group( d_hdf5_file->openGroup( path_to_group ) ) );
  }
  HDF5_EXCEPTION_CATCH( "Could not open group at location "
                        << path_to_group << "!" );
}

// Open a data set
void HDF5File::openDataSet( const std::string& path_to_data_set,
                            std::unique_ptr<const H5::DataSet>& data_set ) const
{
  try{
    data_set.reset( new H5::DataSet( d_hdf5_file->openDataSet( path_to_data_set ) ) );
  }
  HDF5_EXCEPTION_CATCH( "Could not open data set at location "
                        << path_to_data_set << "!" );
}

// Open a data set attribute
void HDF5File::openDataSetAttribute( const H5::DataSet& data_set,
                                     const std::string& path_to_data_set,
                                     const std::string& attribute_name,
                                     std::unique_ptr<const H5::Attribute>& attribute ) const
{
  try{
    attribute.reset( new H5::Attribute( data_set.openAttribute( attribute_name ) ) );
  }
  HDF5_EXCEPTION_CATCH( "Could not open data set attribute "
                        << path_to_data_set << ":" << attribute_name << "!" );
}

// Open a group attribute
void HDF5File::openGroupAttribute( const H5::Group& group,
                                   const std::string& path_to_group,
                                   const std::string& attribute_name,
                                   std::unique_ptr<const H5::Attribute>& attribute ) const
{
  try{
    attribute.reset( new H5::Attribute( group.openAttribute( attribute_name ) ) );
  }
  HDF5_EXCEPTION_CATCH( "Could not open group attribute "
                        << path_to_group << ":" << attribute_name << "!" );
}

#endif // end HAVE_FRENSIE_HDF5
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_HDF5File.cpp
//---------------------------------------------------------------------------//
