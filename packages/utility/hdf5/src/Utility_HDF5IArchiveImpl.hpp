//---------------------------------------------------------------------------//
//!
//! \file   Utility_HDF5IArchiveImpl.hpp
//! \author Alex Robinson
//! \brief  HDF5 input archive implementation class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_HDF5_IARCHIVE_IMPL_HPP
#define UTILITY_HDF5_IARCHIVE_IMPL_HPP

// Std Lib Includes
#include <cstddef>
#include <type_traits>

// Boost Includes
#include <boost/archive/detail/common_iarchive.hpp>
#include <boost/serialization/collection_size_type.hpp>
#include <boost/serialization/item_version_type.hpp>
#include <boost/serialization/binary_object.hpp>
#include <boost/serialization/nvp.hpp>

// FRENSIE Includes
#include "Utility_BoostVersion.hpp"
#include "Utility_HDF5CommonArchive.hpp"

namespace boost{
namespace archive{
namespace detail{

template<class Archive> class interface_iarchive;

} // end detail namespace
} // end archive namespace
} // end boost namespace

namespace Utility{

/*! The HDF5 input archive implementation
 * \ingroup hdf5
 */
template<typename Archive>
class HDF5IArchiveImpl : public boost::archive::detail::common_iarchive<Archive>,
                         public Utility::HDF5CommonArchive
{

public:

  //! Load opaque object
  void load_binary( void* address, std::size_t count );

  /*! Use optimized array loading (load_array) when possible
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
  //! Load an array
  template<typename ValueType>
  void load_array( boost::serialization::array_wrapper<ValueType>& array,
                   unsigned version );
#endif

protected:

  //! The common archive type
  typedef boost::archive::detail::common_iarchive<Archive> CommonIArchive;

  //! The interface_iarchive is a friend
  friend class boost::archive::detail::interface_iarchive<Archive>;

  //! Constructor
  HDF5IArchiveImpl( const std::string& hdf5_filename, unsigned flags );

  //! Initialize the archive
  void init( unsigned flags );

  //! Start a load
  void load_start( const char* name );

  //! Finish a load
  void load_end( const char* name );

  //! Intercept any type that is not a name-value pair or an attribute here
  template<typename T>
  void load_override( T& t, int = 0 );

  //! Load a type that is wrapped in a boost::serialization::nvp
  template<typename T>
  void load_override( const boost::serialization::nvp<T>& t, int = 0 );

  //! Load a boost::archive::object_id_type attribute
  void load_override( boost::archive::object_id_type& t, int = 0 );

  //! Load a boost::archive::object_reference_type attribute
  void load_override( boost::archive::object_reference_type& t, int = 0 );

  //! Load a boost::archive::version_type attribute
  void load_override( boost::archive::version_type& t, int = 0 );

  //! Load a boost::archive::class_id_type attribute
  void load_override( boost::archive::class_id_type& t, int = 0 );

  //! Load a boost::archive::class_id_optional_type attribute
  void load_override( boost::archive::class_id_optional_type& t, int = 0 );

  //! Load a boost::archive::class_id_reference_type attribute
  void load_override( boost::archive::class_id_reference_type& t, int = 0 );

  //! Load a boost::archive::class_name_type attribute
  void load_override( boost::archive::class_name_type& t, int = 0 );

  //! Load a boost::archive::tracking_type attribute
  void load_override( boost::archive::tracking_type& t, int = 0 );

  //! Load any type with a Utility::HDF5TypeTraits specialization
  template<typename T>
  void load( T& t );

  //! Load a wide char
  void load( wchar_t& t );

  //! Load a wide string
  void load( std::wstring& t );

  //! Load a boost::serialization::collection_size_type
  void load( boost::serialization::collection_size_type& t );

  //! Load a boost::serialization::item_version_type attribute
  void load( boost::serialization::item_version_type& t );

private:

  friend class boost::archive::detail::interface_iarchive<Archive>;
  friend class boost::archive::load_access;

  // Intercept a type that is about to be loaded using load_override
  template<typename T>
  void loadIntercept( T& t, std::true_type is_fast_serializable_tuple );

  // Intercept a type that is about to be loaded using load_override
  template<typename T>
  void loadIntercept( T& t, std::false_type is_fast_serializable_tuple );

  // Intercept a type that is about to be loaded using load_override

  // Load implementation
  template<typename T>
  void loadImpl( T* data, size_t count );

  // Load implementation (object data set path already determined)
  template<typename T>
  void loadImpl( const std::string& object_data_set_path,
                 T* data,
                 size_t count );

  // Load container implementation
  template<typename T>
  void loadContainerImpl( T& container );

  // Update the object count
  void updateObjectCount();

  // The object count
  std::size_t d_object_count;
};

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "Utility_HDF5IArchiveImpl_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_HDF5_IARCHIVE_IMPL_HPP

//---------------------------------------------------------------------------//
// end Utility_HDF5IArchiveImpl.hpp
//---------------------------------------------------------------------------//
