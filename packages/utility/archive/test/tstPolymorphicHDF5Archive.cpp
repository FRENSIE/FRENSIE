//---------------------------------------------------------------------------//
//!
//! \file   tstPolymorphicHDF5Archive.cpp
//! \author Alex Robinson
//! \brief  Polymorphic hdf5 archive unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "Utility_PolymorphicHDF5IArchive.hpp"
#include "Utility_PolymorphicHDF5OArchive.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_Array.hpp"
#include "Utility_ArrayView.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Deque.hpp"
#include "Utility_List.hpp"
#include "Utility_Set.hpp"
#include "Utility_Map.hpp"
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
                   float, double> BasicTestTypes;

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
inline T zero( T )
{ return T(0); }

template<typename T>
inline T one( T )
{ return T(1); }

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that basic types can be archived
FRENSIE_UNIT_TEST_TEMPLATE( PolymorphicHDF5Archive,
                            archive_single_value,
                            BasicTestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  std::string archive_name( "test_polymorphic_basic_types.h5a" );

  std::shared_ptr<boost::archive::polymorphic_oarchive> oarchive;

#ifdef HAVE_FRENSIE_HDF5
  {
    std::ostringstream archive_name_stream( archive_name );

    oarchive.reset( new Utility::PolymorphicHDF5OArchive( archive_name_stream, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE ) );

    T value = zero(T());

    FRENSIE_REQUIRE_NO_THROW( *oarchive << boost::serialization::make_nvp( "basic_value_a", value ) );

    value = one(T());
    FRENSIE_REQUIRE_NO_THROW( *oarchive << boost::serialization::make_nvp( "basic_value_b", value ) );
  }

  std::shared_ptr<boost::archive::polymorphic_iarchive> iarchive;

  {
    std::istringstream archive_name_string( archive_name );
    
    iarchive.reset( new Utility::PolymorphicHDF5IArchive( archive_name_string ) );

    T extracted_value;

    FRENSIE_REQUIRE_NO_THROW( *iarchive >> boost::serialization::make_nvp( "basic_value_a", extracted_value ) );
    FRENSIE_CHECK_EQUAL( extracted_value, zero(T()) );

    FRENSIE_REQUIRE_NO_THROW( *iarchive >> boost::serialization::make_nvp( "basic_value_b", extracted_value ) );
    FRENSIE_CHECK_EQUAL( extracted_value, one(T()) );
  }
#else
  std::ostringstream archive_name_stream( archive_name );
  
  FRENSIE_CHECK_THROW( oarchive.reset( new Utility::PolymorphicHDF5OArchive( archive_name_stream, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE ) ),
                       std::logic_error );
#endif
}

#ifdef HAVE_FRENSIE_HDF5

//---------------------------------------------------------------------------//
// Check that arrays of basic types can be archived
FRENSIE_UNIT_TEST_TEMPLATE( PolymorphicHDF5Archive,
                            archive_c_array,
                            BasicTestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  std::string archive_name( "test_polymorphic_c_array_basic_types.h5a" );

  const T array_a[8] = {one(T()), one(T()), one(T()), one(T()), one(T()), one(T()), one(T()), one(T())};
  const T array_b[2][3] = {{one(T()), one(T()), one(T())},{one(T()), one(T()), one(T())}};
  
  {
    std::ostringstream archive_name_stream( archive_name );
    Utility::PolymorphicHDF5OArchive archive_impl( archive_name_stream, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE );

    boost::archive::polymorphic_oarchive& archive = archive_impl;

    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "array_a", array_a ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "array_b", array_b ) );
  }

  {
    std::istringstream archive_name_stream( archive_name );
    Utility::PolymorphicHDF5IArchive archive_impl( archive_name_stream );

    boost::archive::polymorphic_iarchive& archive = archive_impl;

    T extracted_array_a[8];
    T extracted_array_b[2][3];
  
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
FRENSIE_UNIT_TEST_TEMPLATE( PolymorphicHDF5Archive,
                            archive_binary,
                            BasicTestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  std::string archive_name( "test_polymorphic_binary.h5a" );

  T value_a = zero(T());
  T value_b = one(T());
  T array_a[8] = {one(T()), one(T()), one(T()), one(T()), one(T()), one(T()), one(T()), one(T())};
  T array_b[2][3] = {{one(T()), one(T()), one(T())},{one(T()), one(T()), one(T())}};

  {
    std::ostringstream archive_name_stream( archive_name );
    Utility::PolymorphicHDF5OArchive archive( archive_name_stream, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE );

    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "value_a", boost::serialization::make_binary_object( &value_a, sizeof(value_a) ) ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "value_b", boost::serialization::make_binary_object( &value_b, sizeof(value_b) ) ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "array_a", boost::serialization::make_binary_object( array_a, sizeof(array_a) ) ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "array_b", boost::serialization::make_binary_object( array_b, sizeof(array_b) ) ) );
  }

  {
    std::istringstream archive_name_stream( archive_name );
    Utility::PolymorphicHDF5IArchive archive( archive_name_stream );
    
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
FRENSIE_UNIT_TEST( PolymorphicHDF5Archive, archive_class_info )
{
  std::string archive_name( "test_polymorphic_class_info.h5a" );

  std::shared_ptr<boost::archive::polymorphic_oarchive> oarchive;

  {
    std::ostringstream archive_name_stream( archive_name );
    oarchive.reset( new Utility::PolymorphicHDF5OArchive( archive_name_stream, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE ) );
  }
  
  TestClassNoSerializationInfo basic_class;
    
  *oarchive << BOOST_SERIALIZATION_NVP(basic_class);

  // Classes that don't save class info always have a version number of 0
  FRENSIE_CHECK_EQUAL( basic_class.getFileVersion(), 0 );
  FRENSIE_CHECK_EQUAL( basic_class.getSerializationCount(), 1 );

  // Archive the class object a second time to check tracking - when a class
  // has no tracking there will be redundant saves
  *oarchive << BOOST_SERIALIZATION_NVP(basic_class);
  FRENSIE_CHECK_EQUAL( basic_class.getFileVersion(), 0 );
  FRENSIE_CHECK_EQUAL( basic_class.getSerializationCount(), 2 );

  // Archive the class object twice to check tracking - when a class has
  // tracking there will be no redundant saves
  TestClass advanced_class;

  *oarchive << BOOST_SERIALIZATION_NVP(advanced_class);
  FRENSIE_CHECK_EQUAL( advanced_class.getFileVersion(), 2 );
  FRENSIE_CHECK_EQUAL( advanced_class.getSerializationCount(), 1 );

  // Archive the class object a second time to check tracking - when a class
  // has tracking enabled there will be no redundant saves
  *oarchive << BOOST_SERIALIZATION_NVP(advanced_class);
  FRENSIE_CHECK_EQUAL( advanced_class.getFileVersion(), 2 );
  FRENSIE_CHECK_EQUAL( advanced_class.getSerializationCount(), 1 );  
}

//---------------------------------------------------------------------------//
// Check that containers can be archived
FRENSIE_UNIT_TEST_TEMPLATE( PolymorphicHDF5Archive,
                            archive_containers,
                            BasicTestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  const std::string archive_name( "test_polymorphic_container_basic_types.h5a" );

  const std::tuple<T> tuple_t = std::make_tuple( one(T()) );
  const std::pair<T,T> pair_tt = std::make_pair( one(T()), one(T()) );
  const std::pair<std::string,T> pair_st = std::make_pair( "1", one(T()) );
  const std::pair<T,std::string> pair_ts = std::make_pair( one(T()), "1" );
  const std::tuple<T,T> tuple_tt = std::make_tuple( one(T()), one(T()) );
  const std::tuple<std::string,T> tuple_st = std::make_tuple( "1", one(T()) );
  const std::tuple<T,std::string> tuple_ts = std::make_tuple( one(T()), "1");
  const std::tuple<T,T,T> tuple_ttt =
    std::make_tuple( one(T()), zero(T()), one(T()) );
  const std::tuple<T,std::string,T> tuple_tst =
    std::make_tuple( one(T()), "0", one(T()) );

  const std::array<T,5> array = {zero(T()), one(T()), zero(T()), one(T()), zero(T())};
  const std::vector<T> vector( 10, one(T()) );
  const std::deque<T> deque( 10, one(T()) );
  const std::list<T> list( 20, one(T()) );
  const std::forward_list<T> forward_list( 20, one(T()) );
  const std::set<T> set( {zero(T()), one(T())} );
  const std::unordered_set<T> unordered_set( {zero(T()), one(T())} );
  const std::map<T,T> map( {std::make_pair(zero(T()), one(T())), std::make_pair(one(T()), zero(T()))} );
  const std::unordered_map<T,T> unordered_map( {std::make_pair(zero(T()), one(T())), std::make_pair(one(T()), zero(T()))} );

  {
    std::ostringstream archive_name_stream( archive_name );
    Utility::PolymorphicHDF5OArchive archive_impl( archive_name_stream, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE );

    boost::archive::polymorphic_oarchive& archive = archive_impl;

    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp("tuple_t", tuple_t) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp("pair_tt", pair_tt) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp("pair_st", pair_st) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp("pair_ts", pair_ts) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp("tuple_tt", tuple_tt) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp("tuple_st", tuple_st) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp("tuple_ts", tuple_ts) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp("tuple_ttt", tuple_ttt) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp("tuple_tst", tuple_tst) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp("array", array) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp("vector", vector) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp("deque", deque) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp("list", list) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp("forward_list", forward_list) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp("set", set) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp("unordered_set", unordered_set) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp("map", map) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp("unordered_map", unordered_map) );
  }

  {
    std::istringstream archive_name_stream( archive_name );
    Utility::PolymorphicHDF5IArchive archive_impl( archive_name_stream );

    boost::archive::polymorphic_iarchive& archive = archive_impl;

    std::tuple<T> extracted_tuple_t;
    std::pair<T,T> extracted_pair_tt;
    std::pair<std::string,T> extracted_pair_st;
    std::pair<T,std::string> extracted_pair_ts;
    std::tuple<T,T> extracted_tuple_tt;
    std::tuple<std::string,T> extracted_tuple_st;
    std::tuple<T,std::string> extracted_tuple_ts;
    std::tuple<T,T,T> extracted_tuple_ttt;
    std::tuple<T,std::string,T> extracted_tuple_tst;
    
    std::array<T,5> extracted_array;
    std::vector<T> extracted_vector;
    std::deque<T> extracted_deque;
    std::list<T> extracted_list;
    std::forward_list<T> extracted_forward_list;
    std::set<T> extracted_set;
    std::unordered_set<T> extracted_unordered_set;
    std::map<T,T> extracted_map;
    std::unordered_map<T,T> extracted_unordered_map;
    
    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp("tuple_t", extracted_tuple_t) );
    FRENSIE_CHECK_EQUAL( extracted_tuple_t, tuple_t );
    
    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp("pair_tt", extracted_pair_tt) );
    FRENSIE_CHECK_EQUAL( extracted_pair_tt, pair_tt );
    
    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp("pair_st", extracted_pair_st) );
    FRENSIE_CHECK_EQUAL( extracted_pair_st, pair_st );
    
    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp("pair_ts", extracted_pair_ts) );
    FRENSIE_CHECK_EQUAL( extracted_pair_ts, pair_ts );
    
    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp("tuple_tt", extracted_tuple_tt) );
    FRENSIE_CHECK_EQUAL( extracted_tuple_tt, tuple_tt );
    
    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp("tuple_st", extracted_tuple_st) );
    FRENSIE_CHECK_EQUAL( extracted_tuple_st, tuple_st );
    
    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp("tuple_ts", extracted_tuple_ts) );
    FRENSIE_CHECK_EQUAL( extracted_tuple_ts, tuple_ts );
    
    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp("tuple_ttt", extracted_tuple_ttt) );
    FRENSIE_CHECK_EQUAL( extracted_tuple_ttt, tuple_ttt );
    
    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp("tuple_tst", extracted_tuple_tst) );
    FRENSIE_CHECK_EQUAL( extracted_tuple_tst, tuple_tst );
    
    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp("array", extracted_array) );
    FRENSIE_CHECK_EQUAL( extracted_array, array );
    
    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp("vector", extracted_vector) );
    FRENSIE_CHECK_EQUAL( extracted_vector, vector );
    
    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp("deque", extracted_deque) );
    FRENSIE_CHECK_EQUAL( extracted_deque, deque );
    
    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp("list", extracted_list) );
    FRENSIE_CHECK_EQUAL( extracted_list, list );
    
    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp("forward_list", extracted_forward_list) );
    FRENSIE_CHECK_EQUAL( extracted_forward_list, forward_list );
    
    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp("set", extracted_set) );
    FRENSIE_CHECK_EQUAL( extracted_set, set );
    
    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp("unordered_set", extracted_unordered_set) );
    FRENSIE_CHECK_EQUAL( extracted_unordered_set, unordered_set );
    
    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp("map", extracted_map) );
    FRENSIE_CHECK_EQUAL( extracted_map, map );
    
    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp("unordered_map", extracted_unordered_map) );
    FRENSIE_CHECK_EQUAL( extracted_unordered_map, unordered_map );
  }
}

#endif // end HAVE_FRENSIE_HDF5

//---------------------------------------------------------------------------//
// end tstPolymorphicHDF5Archive.cpp
//---------------------------------------------------------------------------//

