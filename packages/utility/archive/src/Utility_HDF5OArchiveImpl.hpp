//---------------------------------------------------------------------------//
//!
//! \file   Utility_HDF5OArchiveImpl.hpp
//! \author Alex Robinson
//! \brief  HDF5 output archive implementation class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_HDF5_OARCHIVE_IMPL_HPP
#define UTILITY_HDF5_OARCHIVE_IMPL_HPP

// Std Lib Includes
#include <cstddef>
#include <type_traits>

// Boost Includes
#include <boost/archive/detail/common_oarchive.hpp>
#include <boost/serialization/collection_size_type.hpp>
#include <boost/serialization/item_version_type.hpp>
#include <boost/serialization/binary_object.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/nvp.hpp>

// FRENSIE Includes
#include "Utility_HDF5CommonArchive.hpp"
#include "Utility_Deque.hpp"

namespace boost{
namespace archive{
namespace detail{

template<class Archive> class interface_oarchive;
  
} // end detail namespace
} // end archive namespace
} // end boost namespace

namespace Utility{

/*! HDF5 output archive flags
 * \ingroup hdf5
 */
enum HDF5OArchiveFlags{
  OVERWRITE_EXISTING_ARCHIVE = 16
};

/*! The HDF5 output archive implementation
 * \ingroup hdf5
 */
template<typename Archive>
class HDF5OArchiveImpl : public boost::archive::detail::common_oarchive<Archive>,
                         public Utility::HDF5CommonArchive
{

public:

  //! Save opaque object
  void save_binary( const void* address, std::size_t count );

  /*! Use optimized array saving (save_array) when possible
   *
   * This struct is used by the boost::serialization library when serializing
   * std::vector, std::array and c-array types.
   */
  struct use_array_optimization
  {
    template<typename T>
    struct apply : public std::conditional<HDF5TypeTraits<T>::IsSpecialized::value,boost::mpl::true_,boost::mpl::false_>::type
    { /* ... */ };
  };

#ifdef BOOST_SERIALIZATION_ARRAY_WRAPPER_AVAILABLE
  //! Save an array
  template<typename ValueType>
  void save_array( const boost::serialization::array_wrapper<ValueType>& a,
                   unsigned int version );
#endif

protected:

  //! The common archive type
  typedef boost::archive::detail::common_oarchive<Archive> CommonOArchive;

  //! The interface_oarchive is a friend
  friend class boost::archive::detail::interface_oarchive<Archive>;

  //! Constructor
  HDF5OArchiveImpl( const std::string& hdf5_filename, unsigned flags );

  //! Initialize the archive
  void init( unsigned flags );

  //! Start a save (required by boost::serialization::polymorphic_oarchive_route)
  void save_start( const char* name );

  //! Finish a save (required by boost::serialization::polymorphic_oarchive_route)
  void save_end( const char* name );

  //! Intercept any type that is not a name-value pair or an attribute here
  template<typename T>
  void save_override( const T& t, int = 0 );

  //! Save a type that is wrapped in a boost::serialization::nvp
  template<typename T>
  void save_override( const boost::serialization::nvp<T>& t, int = 0 );

  //! Save a boost::archive::object_id_type attribute
  void save_override( const boost::archive::object_id_type& t, int = 0 );

  //! Save a boost::archive::object_reference_type attribute
  void save_override( const boost::archive::object_reference_type& t, int = 0 );

  //! Save a boost::archive::version_type attribute
  void save_override( const boost::archive::version_type& t, int = 0 );

  //! Save a boost::archive::class_id_type attribute
  void save_override( const boost::archive::class_id_type& t, int = 0 );

  //! Save a boost::archive::class_id_optional_type attribute
  void save_override( const boost::archive::class_id_optional_type& t, int = 0 );

  //! Save a boost::archive::class_id_reference_type attribute
  void save_override( const boost::archive::class_id_reference_type& t, int = 0 );

  //! Save a boost::archive::class_name_type attribute
  void save_override( const boost::archive::class_name_type& t, int = 0 );

  //! Save a boost::archive::tracking_type attribute
  void save_override( const boost::archive::tracking_type& t, int = 0 );

  //! Save any type with a Utility::HDF5TypeTraits specialization
  template<typename T>
  void save( const T& t );

  //! Save a wide char
  void save( const wchar_t& t );
  
  //! Save a wide string
  void save( const std::wstring& t );

  //! Save a boost::serialization::collection_size_type
  void save( const boost::serialization::collection_size_type& t );

  //! Save a boost::serialization::item_version_type attribute
  void save( const boost::serialization::item_version_type& t );

private:

  friend class boost::archive::detail::interface_oarchive<Archive>;
  friend class boost::archive::save_access;

  // Write to current group attribute
  template<typename T>
  void writeToCurrentGroupAttribute( const std::string& attribute_name,
                                     const T* const data,
                                     const size_t size );

  // Intercept a type that is about to be saved using save_override
  template<typename T>
  void saveIntercept( const T& t, std::true_type is_fast_serializable_tuple );

  // Intercept a type that is about to be saved using save_override
  template<typename T>
  void saveIntercept( const T& t, std::false_type is_fast_serializable_tuple );

  // Save implementation
  template<typename T>
  void saveImpl( const T* data, size_t count );

  // Save implementation (object data set path already determined)
  template<typename T>
  void saveImpl( const std::string& object_data_set_path,
                 const T* data,
                 size_t count );

  // Save container implementation
  template<typename T>
  void saveContainerImpl( const T& container );

  // Start an hdf5 group
  void startHDF5Group( const char* group_name );

  // End an hdf5 group
  void endHDF5Group();

  // Get the tree object path
  std::string getTreeObjectPath() const;

  // Link the data object
  void linkDataObject();

  // Link the tracked object
  void linkTrackedObject( unsigned object );

  // Link the tracked object reference
  void linkTrackedObjectReference( unsigned object_reference );

  // Link the data and update the object count
  void linkDataAndUpdateObjectCount();

  // The object count
  std::size_t d_object_count;

  // The group count
  std::size_t d_group_count;

  // The group stack
  typedef std::deque<std::string> GroupStack;
  GroupStack d_group_stack;

  // Keep track of the next object type
  bool d_next_object_is_attribute;
};
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "Utility_HDF5OArchiveImpl_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_HDF5_OARCHIVE_IMPL_HPP

//---------------------------------------------------------------------------//
// end Utility_HDF5OArchiveImpl.hpp
//---------------------------------------------------------------------------//
