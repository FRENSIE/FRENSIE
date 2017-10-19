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
#include <boost/serialization/string.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/pfto.hpp>

// FRENSIE Includes
#include "Utility_HDF5CommonArchive.hpp"
#include "Utility_Deque.hpp"

namespace Utility{

/*! The HDF5 output archive implementation
 * \ingroup hdf5
 */
template<typename Archive>
class HDF5OArchiveImpl : public boost::archive::details::common_oarchive<Archive>,
                         public Utility::HDF5CommonArchive
{

public:

  //! HDF5 archive flags
  enum HDF5ArchiveFlags{
    OVERWRITE_EXISTING_ARCHIVE = 16
  };

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

  //! Save an array
  template<typename ValueType>
  void save_array( const boost::serialization::array<ValueType>& a,
                   unsigned int version );

protected:

  //! The common archive type
  typedef boost::archive::detail::common_oarchive<Archive> CommonOArchive;

  //! Constructor
  BOOST_ARCHIVE_OR_WARCHIVE_DECL(BOOST_PP_EMPTY())
  HDF5OArchiveImpl( const std::string& hdf5_filename, unsigned flags );

  //! Initialize the archive
  void init( unsigned flags );

  //! Intercept any type that is not a name-value pair or an attribute here
  template<typename T>
  void save_override( const T& t, BOOST_PFTO int );

  //! Save a type that is wrapped in a boost::serialization::nvp
  template<typename T>
  void save_override(
       HANDLE_BOOST_FUNCTION_TEMPLATE_ORDERING boost::serialization::nvp<T>& t,
       int );

  //! Save a boost::archive::object_id_type attribute
  BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
  save_override( const boost::archive::object_id_type& t, int );

  //! Save a boost::archive::object_reference_type attribute
  BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
  save_override( const boost::archive::object_reference_type& t, int );

  //! Save a boost::archive::version_type attribute
  BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
  save_override( const boost::archive::version_type& t, int );

  //! Save a boost::archive::class_id_type attribute
  BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
  save_override( const boost::arhcive::class_id_type& t, int );

  //! Save a boost::archive::class_id_optional_type attribute
  BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
  save_override( const boost::archive::class_id_optional_type& t, int );

  //! Save a boost::archive::class_id_reference_type attribute
  BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
  save_override( const boost::archive::class_id_reference_type& t, int );

  //! Save a boost::archive::class_name_type attribute
  BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
  save_override( const boost::archive::class_name_type& t, int );

  //! Save a boost::archive::tracking_type attribute
  BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
  save_override( const boost::archive::tracking_type& t, int );

  //! Save any type with a Utility::HDF5TypeTraits specialization
  template<typename T>
  void save( const T& t );

  //! Save a std::string
  void save( const std::string& t );

  //! Save a std::wstring
  void save( const std::wstring& t );

  //! Save a bost::serialization::collection_size_type
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

  // Get the tree object path
  BOOST_ARCHIVE_OR_WARCHIVE_DECL(std::string) getTreeObjectPath() const;

  // Link the data object
  BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) linkDataObject();

  // Link the tracked object
  BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) linkTrackedObject( unsigned object );

  // Link the tracked object reference
  BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
  linkTrackedObjectReference( unsigned object_reference );

  // Link the data and update the object count
  BOOST_ARCHIVE_OR_WARCHIVE_DECL(void) linkDataAndUpdateObjectCount();

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

#include "Utility_HDf5OArchiveImpl_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_HDF5_OARCHIVE_IMPL_HPP

//---------------------------------------------------------------------------//
// end Utility_HDF5OArchiveImpl.hpp
//---------------------------------------------------------------------------//
