//---------------------------------------------------------------------------//
//!
//! \file   Utility_HDF5File.hpp
//! \author Alex Robinson
//! \brief  The hdf5 file class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_HDF5_FILE_HPP
#define UTILITY_HDF5_FILE_HPP

// Std Lib Includes
#include <string>
#include <memory>
#include <stdexcept>
#include <sstream>
#include <initializer_list>

// Boost Includes
#include <boost/noncopyable.hpp>

// FRENSIE Includes
#include "Utility_ExceptionCatchMacros.hpp"

namespace Utility{

/*! The HDF5 file class
 * 
 * This class wraps the H5::File object and provides a simplified interface
 * for querying file properties and for reading from and writing to files. 
 * Objects of this class cannot be copied - use smart pointers instead.
 * \ingroup hdf5
 */
class HDF5File : private boost::noncopyable
{

public:

  //! File opening modes
  enum OpenMode{
    READ_ONLY,
    READ_WRITE,
    OVERWRITE,
  };

  //! The exception class
  class Exception;

  //! Constructor
  HDF5File( const std::string& filename,
            const HDF5File::OpenMode mode = HDF5File::OVERWRITE );

  //! Destructor
  virtual ~HDF5File();

  //! Get the file name
  const std::string& getFilename() const throw();

  //! Check if the group exists
  bool doesGroupExist( const std::string& path_to_group ) const throw();

  //! Check if the group attribute exists
  bool doesGroupAttributeExist( const std::string& path_to_group,
                                const std::string& attribute_name ) const throw();

  //! Check if the data set exists
  bool doesDataSetExist( const std::string& path_to_data_set ) const throw();

  //! Check if the data set attribute exists
  bool doesDataSetAttributeExist( const std::string& path_to_data_set,
                                  const std::string& attribute_name ) const throw();

  //! Get the size of a data set
  HDF5_ENABLED_DISABLED_SWITCH(hsize_t,size_t) getDataSetSize(
                                   const std::string& path_to_data_set ) const;

  //! Get the size of a data set attribute
  HDF5_ENABLED_DISABLED_SWITCH(hsize_t,size_t) getDataSetAttributeSize(
                                     const std::string& path_to_data_set,
                                     const std::string& attribute_name ) const;

  //! Get the size of a group attribute
  HDF5_ENABLED_DISABLED_SWITCH(hsize_t,size_t) getGroupAttributeSize(
                                     const std::string& path_to_group,
                                     const std::string& attribute_name ) const;

  //! Create a group
  void createGroup( const std::string& path_to_group );

  //! Create a hard link
  void createHardLink( const std::string& existing_object_path,
                       const std::string& path_to_link );

  //! Create a soft link
  void createSoftLink( const std::string& existing_object_path,
                       const std::string& path_to_link );

  //! Write data to a data set
  template<typename T>
  void writeToDataSet( const std::string& path_to_data_set,
                       const T* data,
                       const size_t size );

  //! Write data to a data set
  template<typename T>
  void writeToDataSet( const std::string& path_to_data_set,
                       const T& data );

  //! Read data from a data set
  template<typename T>
  void readFromDataSet( const std::string& path_to_data_set,
                        T* data,
                        const size_t size ) const;

  //! Write data to a data set attribute
  template<typename T>
  void writeToDataSetAttribute( const std::string& path_to_data_set,
                                const std::string& attribute_name,
                                const T* data,
                                const size_t size );

  //! Write data to a data set attribute
  template<typename T>
  void writeToDataSetAttribute( const std::string& path_to_data_set,
                                const std::string& attribute_name,
                                const T& data );

  //! Read data from a data set attribute
  template<typename T>
  void readFromDataSetAttribute( const std::string& path_to_data_set,
                                 const std::string& attribute_name,
                                 T* data,
                                 const size_t size ) const;

  //! Write data to a group attribute
  template<typename T>
  void writeToGroupAttribute( const std::string& path_to_group,
                              const std::string& attribute_name,
                              const T* data,
                              const size_t size );

  //! Write data to a group attribute
  template<typename T>
  void writeToGroupAttribute( const std::string& path_to_group,
                              const std::string& attribute_name,
                              const T& data );

  //! Read data from a group attribute
  template<typename T>
  void readFromGroupAttribute( const std::string& path_to_group,
                               const std::string& attribute_name,
                               T* data,
                               const size_t size ) const;

protected:

  //! Write opaque data to a data set
  void writeToDataSet( const std::string& path_to_data_set,
                       const void* data,
                       const size_t size );

  //! Read data from a data set
  void readFromDataSet( const std::string& path_to_data_set,
                        void* data,
                        const size_t size ) const;

  //! Write data to a data set attribute
  void writeToDataSetAttribute( const std::string& path_to_data_set,
                                const std::string& attribute_name,
                                const void* data,
                                const size_t size );

  //! Read data from a data set attribute
  void readFromDataSetAttribute( const std::string& path_to_data_set,
                                 const std::string& attribute_name,
                                 void* data,
                                 const size_t size ) const;

  //! Write data to a group attribute
  void writeToGroupAttribute( const std::string& path_to_group,
                              const std::string& attribute_name,
                              const void* data,
                              const size_t size );

  //! Read data from a group attribute
  void readFromGroupAttribute( const std::string& path_to_group,
                               const std::string& attribute_name,
                               void* data,
                               const size_t size ) const;
  
private:

  // Extract the parent group path
  std::string extractParentGroupPath( const std::string& path ) const;

  // Check if the parent group exists
  bool doesParentGroupExist( const std::string& path ) const;

  // Create the parent group, if necessary, for the specified path
  void createParentGroup( const std::string& path );

#ifdef HAVE_FRENSIE_HDF5
  // Create a group
  void createGroup( const std::string& path_to_group,
                    std::unique_ptr<const H5::Group>& group );

  // Open a group
  void openGroup( const std::string& path_to_group,
                  std::unique_ptr<const H5::Group>& group ) const;

  // Create a data set
  template<typename T>
  void createDataSet( const std::string& path_to_data_set,
                      const size_t data_set_size,
                      std::unique_ptr<H5::DataSet>& data_set );
  
  // Open a data set
  void openDataSet( const std::string& path_to_data_set,
                    std::unique_ptr<const H5::DataSet>& data_set ) const;

  // Create a data set attribute
  template<typename T>
  void createDataSetAttribute( const H5::DataSet& data_set,
                               const std::string& data_set_name,
                               const std::string& attribute_name,
                               const size_t attribute_size,
                               std::unique_ptr<H5::Attribute>& attribute );

  // Open a data set attribute
  void openDataSetAttribute( const H5::DataSet& data_set,
                             const std::string& data_set_name,
                             const std::string& attribute_name,
                             std::unique_ptr<const H5::Attribute>& attribute ) const;

  // Create a group attribute
  template<typename T>
  void createGroupAttribute( const H5::Group& group,
                             const std::string& group_name,
                             const std::string& attribute_name,
                             const size_t attribute_size,
                             std::unique_ptr<H5::Attribute>& attribute );

  // Open a group attribute
  void openGroupAttribute( const H5::Group& group,
                           const std::string& group_name,
                           const std::string& attribute_name,
                           std::unique_ptr<const H5::Attribute>& attribute ) const;

  // Get the size of a data set
  HDF5_ENABLED_DISABLED_SWITCH(hsize_t,size_t) getDataSetSize( const H5::DataSet& data_set ) const;

  //! Get the size of an attribute
  HDF5_ENABLED_DISABLED_SWITCH(hsize_t,size_t) getAttributeSize( const H5::Attribute& attribute ) const;

  //! Get the size of a data space
  HDF5_ENABLED_DISABLED_SWITCH(hsize_t,size_t) getDataSpaceSize( const H5::DataSpace& data_space ) const;

  //! Check if the group attribute exists
  bool doesGroupAttributeExist( const H5::Group& group,
                                const std::string& attribute_name ) const;

  //! Check if the data set attribute exists
  bool doesDataSetAttributeExist( const H5::DataSet& data_set,
                                  const std::string& attribute_name ) const;

  // Check that the type matches the data set type
  template<typename T>
  bool doesDataSetTypeMatch( const T& data_type,
                             const H5::DataSet& data_set ) const;

  // Check that the type matches the attribute type
  template<typename T>
  bool doesAttributeTypeMatch( const T& data_type,
                               const H5::Attribute& attribute ) const;

  // Check if an array can store the contents of a data set
  template<typename ExternalT, typename InternalT>
  bool canArrayStoreDataSetContents( const InternalT* data,
                                     const size_t size,
                                     const H5::DataSet& data_set ) const;

  // Check if an array can store the contents of a data set attribute
  template<typename ExternalT, typename InternalT>
  bool canArrayStoreAttributeContents( const InternalT* data,
                                       const size_t size,
                                       const H5::Attribute& attribute ) const;
#endif // end HAVE_FRENSIE_HDF5

  // The filename
  std::string d_filename;

  // The HDF5 file object
  std::unique_ptr<HDF5_ENABLED_DISABLED_SWITCH(H5::H5File,int)> d_hdf5_file;
};

/*! The HDF5File::Exception class
 * \ingroup hdf5
 */
class HDF5File::Exception : public std::runtime_error
{
public:

  //! Constructor
  Exception( const std::string& message );

  //! Constructor (extra details)
  Exception( const std::string& file,
             const size_t line,
             const std::string& hdf5_function_name,
             const std::string& hdf5_error_message,
             const std::string& message );

  //! Destructor
  ~Exception() throw()
  { /* ... */ }

private:

  // Create an error message
  static std::string createErrorMessage( const std::string& file,
                                         const size_t line,
                                         const std::string& hdf5_function_name,
                                         const std::string& hdf5_error_message,
                                         const std::string& message );
};

//! Write a container to a data set
template<typename Container>
void writeToDataSet( HDF5File& hdf5_file,
                     const std::string& path_to_data_set,
                     const Container& container );

//! Write an initializer list to a data set
template<typename T>
void writeToDataSet( HDF5File& hdf5_file,
                     const std::string& path_to_data_set,
                     std::initializer_list<T> container );

//! Write a container to a data set attribute
template<typename Container>
void writeToDataSetAttribute( HDF5File& hdf5_file,
                              const std::string& path_to_data_set,
                              const std::string& attribute_name,
                              const Container& container );

//! Write an initializer list to a data set attribute
template<typename T>
void writeToDataSetAttribute( HDF5File& hdf5_file,
                              const std::string& path_to_data_set,
                              const std::string& attribute_name,
                              std::initializer_list<T> container );

//! Write a container to a group attribute
template<typename Container>
void writeToGroupAttribute( HDF5File& hdf5_file,
                            const std::string& path_to_group,
                            const std::string& attribute_name,
                            const Container& container );

//! Write an initializer list to a group attribute
template<typename T>
void writeToGroupAttribute( HDF5File& hdf5_file,
                            const std::string& path_to_group,
                            const std::string& attribute_name,
                            std::initializer_list<T> container );

//! Read a container from a data set
template<typename Container>
void readFromDataSet( const HDF5File& hdf5_file,
                      const std::string& path_to_data_set,
                      Container& container );

//! Read a container from a data set attribute
template<typename Container>
void readFromDataSetAttribute( const HDF5File& hdf5_file,
                               const std::string& path_to_data_set,
                               const std::string& attribute_name,
                               Container& container );

//! Read a container from a group attribute
template<typename Container>
void readFromGroupAttribute( const HDF5File& hdf5_file,
                             const std::string& path_to_group,
                             const std::string& attribute_name,
                             Container& container );
  
} // end Utility namespace

/*! Catch statement macro for catching an H5::Exception
 * \ingroup hdf5
 */
#ifdef HAVE_FRENSIE_HDF5
#define HDF5_EXCEPTION_CATCH( raw_msg ) \
catch( const H5::Exception& exception )       \
{                                           \
  std::ostringstream msg;                                               \
  msg << raw_msg;                                                       \
                                                                        \
  throw HDF5File::Exception( __FILE__, __LINE__, exception.getFuncName(), exception.getDetailMsg(), msg.str() ); \
}
#else
#define HDF5_EXCEPTION_CATCH( raw_msg )         \
EXCEPTION_CATCH_RETHROW( std::runtime_error, raw_msg )
#endif // end HAVE_FRENSIE_HDF5 

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "Utility_HDF5File_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_HDF5_FILE_HPP

//---------------------------------------------------------------------------//
// end Utility_HDF5File.hpp
//---------------------------------------------------------------------------//
