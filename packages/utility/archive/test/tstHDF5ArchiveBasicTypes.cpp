//---------------------------------------------------------------------------//
//!
//! \file   tstHDF5ArchiveBasicTypes.cpp
//! \author Alex Robinson
//! \brief  HDF5 archive basic types unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// FRENSIE Includes
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_ArrayView.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Template Types
//---------------------------------------------------------------------------//
typedef std::tuple<bool,
                   char, unsigned char, signed char,
                   short, unsigned short,
                   int, unsigned int,
                   long, unsigned long,
                   long long, unsigned long long,
                   float, double, long double> BasicTestTypesNoString;

typedef decltype(std::tuple_cat(BasicTestTypesNoString(), std::tuple<std::string>())) BasicTestTypes;

class TestClassNoSerializationInfo
{
public:
  TestClassNoSerializationInfo()
    : d_file_version(std::numeric_limits<unsigned>::max()),
      d_serialization_count(0)
  { /* ... */ }
  
  const unsigned& getFileVersion() const
  { return d_file_version; }

  const unsigned& getSerializationCount() const
  { return d_serialization_count; }
  
private:
  friend class boost::serialization::access;
  
  template<class Archive>
  void serialize( Archive&, const unsigned file_version )
  {
    d_file_version = file_version;
    ++d_serialization_count;
  }

  unsigned d_file_version;
  unsigned d_serialization_count;
};

BOOST_CLASS_IMPLEMENTATION(TestClassNoSerializationInfo, boost::serialization::object_serializable)
BOOST_CLASS_TRACKING(TestClassNoSerializationInfo, boost::serialization::track_never)

class TestClass;
BOOST_CLASS_VERSION(TestClass, 2)

class TestClass
{
public:
  TestClass()
    : d_file_version(std::numeric_limits<unsigned>::max()),
      d_serialization_count(0)
  { /* ... */ }

  const unsigned& getFileVersion() const
  { return d_file_version; }

  const unsigned& getSerializationCount() const
  { return d_serialization_count; }

private:
  friend class boost::serialization::access;

  template<class Archive>
  void serialize( Archive&, const unsigned file_version )
  {
    d_file_version = file_version;
    ++d_serialization_count;
  }

  unsigned d_file_version;
  unsigned d_serialization_count;
};

BOOST_CLASS_IMPLEMENTATION(TestClass, boost::serialization::object_class_info)
BOOST_CLASS_TRACKING(TestClass, boost::serialization::track_always)

//---------------------------------------------------------------------------//
// Testing functions
//---------------------------------------------------------------------------//
template<typename T>
inline typename std::enable_if<!std::is_same<T,std::string>::value,T>::type zero( T )
{ return T(0); }

template<typename T>
inline typename std::enable_if<std::is_same<T,std::string>::value,T>::type zero( T )
{ return "Zero"; }

template<typename T>
inline typename std::enable_if<!std::is_same<T,std::string>::value,T>::type one( T )
{ return T(1); }

template<typename T>
inline typename std::enable_if<std::is_same<T,std::string>::value,T>::type one( T )
{ return "one"; }

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that basic types can be archived
FRENSIE_UNIT_TEST_TEMPLATE( HDF5Archive, archive_single_value, BasicTestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  std::string archive_name( "test_basic_types.h5a" );

#ifdef HAVE_FRENSIE_HDF5
  {
    Utility::HDF5OArchive archive( archive_name, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE );

    T value = zero(T());

    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "basic_value_a", value ) );

    value = one(T());
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "basic_value_b", value ) );
  }

  {
    Utility::HDF5IArchive archive( archive_name );

    T extracted_value;

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "basic_value_a", extracted_value ) );
    FRENSIE_CHECK_EQUAL( extracted_value, zero(T()) );

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "basic_value_b", extracted_value ) );
    FRENSIE_CHECK_EQUAL( extracted_value, one(T()) );
  }
#else
  FRENSIE_CHECK_THROW( Utility::HDF5IArchive archive( archive_name ),
                       std::logic_error );
#endif
}

#ifdef HAVE_FRENSIE_HDF5

//---------------------------------------------------------------------------//
// Check that arrays of basic types can be archived
FRENSIE_UNIT_TEST_TEMPLATE( HDF5Archive, archive_c_array, BasicTestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  std::string archive_name( "test_c_array_basic_types.h5a" );

  const T array_a[8] = {one(T()), one(T()), one(T()), one(T()), one(T()), one(T()), one(T()), one(T())};
  const T array_b[2][3] = {{one(T()), one(T()), one(T())},{one(T()), one(T()), one(T())}};
  
  {
    Utility::HDF5OArchive archive( archive_name, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE );

    // Array optimization should be used with this type
    FRENSIE_REQUIRE( Utility::HDF5OArchive::use_array_optimization::apply<T>::type::value );

    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "array_a", array_a ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "array_b", array_b ) );
  }

  {
    Utility::HDF5IArchive archive( archive_name );

    T extracted_array_a[8];
    T extracted_array_b[2][3];
  
    // Array optimization should be used with this type
    FRENSIE_REQUIRE( Utility::HDF5IArchive::use_array_optimization::apply<T>::type::value );

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "array_a", extracted_array_a ) );
    FRENSIE_CHECK_EQUAL( Utility::ArrayView<const T>( array_a, array_a+8 ),
                         Utility::ArrayView<const T>( extracted_array_a, extracted_array_a+8 ) );
    
    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "array_b", extracted_array_b ) );
    FRENSIE_CHECK_EQUAL( Utility::ArrayView<const T>( &array_b[0][0], &array_b[0][0]+6 ),
                         Utility::ArrayView<const T>( &extracted_array_b[0][0], &extracted_array_b[0][0]+6 ) );
  }
}

//---------------------------------------------------------------------------//
// Check that basic types can be archived
FRENSIE_UNIT_TEST_TEMPLATE( HDF5Archive, archive_binary, BasicTestTypesNoString )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  std::string archive_name( "test_binary.h5a" );

  T value_a = zero(T());
  T value_b = one(T());
  T array_a[8] = {one(T()), one(T()), one(T()), one(T()), one(T()), one(T()), one(T()), one(T())};
  T array_b[2][3] = {{one(T()), one(T()), one(T())},{one(T()), one(T()), one(T())}};

  {
    Utility::HDF5OArchive archive( archive_name, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE );

    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "value_a", boost::serialization::make_binary_object( &value_a, sizeof(value_a) ) ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "value_b", boost::serialization::make_binary_object( &value_b, sizeof(value_b) ) ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "array_a", boost::serialization::make_binary_object( array_a, sizeof(array_a) ) ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "array_b", boost::serialization::make_binary_object( array_b, sizeof(array_b) ) ) );
  }

  {
    Utility::HDF5IArchive archive( archive_name );
    
    T extracted_value;
    T extracted_array_a[8];
    T extracted_array_b[2][3];

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "value_a", boost::serialization::make_binary_object( &extracted_value, sizeof(extracted_value) ) ) );
    FRENSIE_CHECK_EQUAL( extracted_value, value_a );
    
    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "value_b", boost::serialization::make_binary_object( &extracted_value, sizeof(extracted_value) ) ) );
    FRENSIE_CHECK_EQUAL( extracted_value, value_b );
    
    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "array_a", boost::serialization::make_binary_object( extracted_array_a, sizeof(extracted_array_a) ) ) );
    FRENSIE_CHECK_EQUAL( Utility::ArrayView<const T>( array_a, array_a+8 ),
                         Utility::ArrayView<const T>( extracted_array_a, extracted_array_a+8 ) );
    
    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "array_b", boost::serialization::make_binary_object( extracted_array_b, sizeof(extracted_array_b) ) ) );
    FRENSIE_CHECK_EQUAL( Utility::ArrayView<const T>( &array_b[0][0], &array_b[0][0]+6 ),
                         Utility::ArrayView<const T>( &extracted_array_b[0][0], &extracted_array_b[0][0]+6 ) );
  }
}

//---------------------------------------------------------------------------//
// Check that class info can be archived
FRENSIE_UNIT_TEST( HDF5Archive, archive_class_info )
{
  std::string archive_name( "test_class_info.h5a" );

  Utility::HDF5OArchive oarchive( archive_name, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE );
  
  TestClassNoSerializationInfo basic_class;
    
  oarchive << BOOST_SERIALIZATION_NVP(basic_class);

  // Classes that don't save class info always have a version number of 0
  FRENSIE_CHECK_EQUAL( basic_class.getFileVersion(), 0 );
  FRENSIE_CHECK_EQUAL( basic_class.getSerializationCount(), 1 );

  // Archive the class object a second time to check tracking - when a class
  // has no tracking there will be redundant saves
  oarchive << BOOST_SERIALIZATION_NVP(basic_class);
  FRENSIE_CHECK_EQUAL( basic_class.getFileVersion(), 0 );
  FRENSIE_CHECK_EQUAL( basic_class.getSerializationCount(), 2 );

  // Archive the class object twice to check tracking - when a class has
  // tracking there will be no redundant saves
  TestClass advanced_class;

  oarchive << BOOST_SERIALIZATION_NVP(advanced_class);
  FRENSIE_CHECK_EQUAL( advanced_class.getFileVersion(), 2 );
  FRENSIE_CHECK_EQUAL( advanced_class.getSerializationCount(), 1 );

  // Archive the class object a second time to check tracking - when a class
  // has tracking enabled there will be no redundant saves
  oarchive << BOOST_SERIALIZATION_NVP(advanced_class);
  FRENSIE_CHECK_EQUAL( advanced_class.getFileVersion(), 2 );
  FRENSIE_CHECK_EQUAL( advanced_class.getSerializationCount(), 1 );  
}

#endif // end HAVE_FRENSIE_HDF5

//---------------------------------------------------------------------------//
// end tstHDF5ArchiveBasicTypes.cpp
//---------------------------------------------------------------------------//
