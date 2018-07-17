//---------------------------------------------------------------------------//
//!
//! \file   tstHDF5FileGroupAttributeHelpers.cpp
//! \author Alex Robinson
//! \brief  HDF5 file read/write group attribute helper method unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/algorithm/string/replace.hpp>

// FRENSIE Includes
#include "Utility_HDF5File.hpp"
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
typedef std::tuple<char, unsigned char, signed char,
                   short, unsigned short,
                   int, unsigned int,
                   long, unsigned long,
                   long long, unsigned long long,
                   float, double, long double> BasicTestTypesExceptBool;

typedef decltype(std::tuple_cat( BasicTestTypesExceptBool(), std::tuple<bool>())) BasicTestTypes;

template<typename... Types>
struct PairTypes;

template<typename T, typename... Types>
struct PairTypes<T,Types...>
{
  typedef typename std::conditional<!std::is_same<T,int>::value,decltype(std::tuple_cat( std::tuple<std::pair<T,T>, std::pair<T,int>, std::pair<int,T> >(), typename PairTypes<Types...>::type())),decltype(std::tuple_cat(std::tuple<std::pair<T,T> >(), typename PairTypes<Types...>::type()))>::type type;
};

template<typename T>
struct PairTypes<T>
{
  typedef typename std::conditional<!std::is_same<T,int>::value,std::tuple<std::pair<T,T>, std::pair<T,int>, std::pair<int,T> >,std::tuple<std::pair<T,T> > >::type type;
};

template<typename... Types>
struct PairTypes<std::tuple<Types...> > : public PairTypes<Types...>
{ /* ... */ };

template<typename... Types>
struct OneElementTupleTypes;

template<typename T, typename... Types>
struct OneElementTupleTypes<T,Types...>
{
  typedef decltype(std::tuple_cat( std::tuple<std::tuple<T> >(), typename OneElementTupleTypes<Types...>::type())) type;
};

template<typename T>
struct OneElementTupleTypes<T>
{
  typedef std::tuple<std::tuple<T> > type;
};

template<typename... Types>
struct OneElementTupleTypes<std::tuple<Types...> > : public OneElementTupleTypes<Types...>
{ /* ... */ };

template<typename... Types>
struct TwoElementTupleTypes;

template<typename T, typename... Types>
struct TwoElementTupleTypes<T,Types...>
{
  typedef typename std::conditional<!std::is_same<T,int>::value,decltype(std::tuple_cat( std::tuple<std::tuple<T,T>, std::tuple<T,int>, std::tuple<int,T> >(), typename TwoElementTupleTypes<Types...>::type())),decltype(std::tuple_cat(std::tuple<std::tuple<T,T> >(), typename TwoElementTupleTypes<Types...>::type()))>::type type;
};

template<typename T>
struct TwoElementTupleTypes<T>
{
  typedef typename std::conditional<!std::is_same<T,int>::value,std::tuple<std::tuple<T,T>, std::tuple<T,int>, std::tuple<int,T> >,std::tuple<std::tuple<T,T> > >::type type;
};

template<typename... Types>
struct TwoElementTupleTypes<std::tuple<Types...> > : public TwoElementTupleTypes<Types...>
{ /* ... */ };

template<typename... Types>
struct ThreeElementTupleTypes;

template<typename T, typename... Types>
struct ThreeElementTupleTypes<T,Types...>
{
  typedef typename std::conditional<!std::is_same<T,int>::value,decltype(std::tuple_cat( std::tuple<std::tuple<T,T,T>, std::tuple<T,int,T>, std::tuple<int,T,int> >(), typename ThreeElementTupleTypes<Types...>::type())),decltype(std::tuple_cat(std::tuple<std::tuple<T,T,T> >(), typename ThreeElementTupleTypes<Types...>::type()))>::type type;
};

template<typename T>
struct ThreeElementTupleTypes<T>
{
  typedef typename std::conditional<!std::is_same<T,int>::value,std::tuple<std::tuple<T,T,T>, std::tuple<T,int,T>, std::tuple<int,T,int> >,std::tuple<std::tuple<T,T,T> > >::type type;
};

template<typename... Types>
struct ThreeElementTupleTypes<std::tuple<Types...> > : public ThreeElementTupleTypes<Types...>
{ /* ... */ };

template<typename... Types>
struct MergeTypeLists;

template<typename T, typename... Types>
struct MergeTypeLists<T,Types...>
{
  typedef decltype(std::tuple_cat( T(), typename MergeTypeLists<Types...>::type())) type;
};

template<typename T>
struct MergeTypeLists<T>
{
  typedef T type;
};

typedef typename MergeTypeLists<BasicTestTypes,typename PairTypes<BasicTestTypes>::type,typename TwoElementTupleTypes<BasicTestTypes>::type>::type TestTypes;

typedef typename MergeTypeLists<BasicTestTypesExceptBool,typename PairTypes<BasicTestTypesExceptBool>::type,typename TwoElementTupleTypes<BasicTestTypesExceptBool>::type>::type TestTypesExceptBool;                 

//---------------------------------------------------------------------------//
// Testing functions
//---------------------------------------------------------------------------//
template<typename T>
inline T zero( T )
{ return T(0); }

template<typename T1, typename T2>
inline std::pair<T1,T2> zero( std::pair<T1,T2> )
{
  return std::make_pair( zero<T1>( T1() ), zero<T2>( T2() ) );
}

template<typename... Types>
inline std::tuple<Types...> zero( std::tuple<Types...> )
{
  return std::make_tuple( zero<Types>( Types() )... );
}

template<typename T>
inline T one( T )
{ return T(1); }

template<typename T1, typename T2>
inline std::pair<T1,T2> one( std::pair<T1,T2> )
{
  return std::make_pair( one<T1>( T1() ), one<T2>( T2() ) );
}

template<typename... Types>
inline std::tuple<Types...> one( std::tuple<Types...> )
{
  return std::make_tuple( one<Types>( Types() )... );
}

//---------------------------------------------------------------------------//
// Testing variables
//---------------------------------------------------------------------------//
std::string hdf5_file_name( "container_group_attr_test_file.h5" );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an initializer_list can be written to and read from a group attr
FRENSIE_UNIT_TEST_TEMPLATE( HDF5File, group_attribute_rw_init_list, TestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  Utility::HDF5File hdf5_file( hdf5_file_name, Utility::HDF5File::READ_WRITE );
  
  std::string attribute_name = Utility::typeName<T>();
  boost::replace_all( attribute_name, ":", "_" );
  boost::replace_all( attribute_name, "<", "__" );
  boost::replace_all( attribute_name, ">", "__" );
  boost::replace_all( attribute_name, ",", "_" );
  boost::replace_all( attribute_name, " ", "_" );

  std::string path_to_group( "/init_list/" );

  FRENSIE_REQUIRE_NO_THROW( Utility::writeToGroupAttribute( hdf5_file, path_to_group, attribute_name, {zero(T()), one(T()), zero(T()), one(T())} ) );
  FRENSIE_REQUIRE( hdf5_file.doesGroupAttributeExist( path_to_group, attribute_name ) );
  
  // Init lists cannot used in read operations since their size is fixed
  std::vector<T> init_list_data;
  
  FRENSIE_REQUIRE_NO_THROW( Utility::readFromGroupAttribute( hdf5_file, path_to_group, attribute_name, init_list_data ) );
  FRENSIE_CHECK_EQUAL( init_list_data, std::vector<T>({zero(T()), one(T()), zero(T()), one(T())}) );
}

//---------------------------------------------------------------------------//
// Check that an array can be written to and read from a group attribute
FRENSIE_UNIT_TEST_TEMPLATE( HDF5File, group_attribute_rw_array, TestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  Utility::HDF5File hdf5_file( hdf5_file_name, Utility::HDF5File::READ_WRITE );

  std::string attribute_name = Utility::typeName<T>();
  boost::replace_all( attribute_name, ":", "_" );
  boost::replace_all( attribute_name, "<", "__" );
  boost::replace_all( attribute_name, ">", "__" );
  boost::replace_all( attribute_name, ",", "_" );
  boost::replace_all( attribute_name, " ", "_" );

  std::string path_to_group( "/array/" );

  std::array<T,10> array_data;
  array_data.fill( one(T()) );

  FRENSIE_REQUIRE_NO_THROW( Utility::writeToGroupAttribute( hdf5_file, path_to_group, attribute_name, array_data ) );
  FRENSIE_REQUIRE( hdf5_file.doesGroupAttributeExist( path_to_group, attribute_name ) );
  
  // Arrays cannot be used in read operations since their size is fixed
  std::vector<T> extracted_array_data;
  
  FRENSIE_REQUIRE_NO_THROW( Utility::readFromGroupAttribute( hdf5_file, path_to_group, attribute_name, extracted_array_data ) );
  FRENSIE_CHECK_EQUAL( extracted_array_data,
                       std::vector<T>(array_data.begin(), array_data.end()) );
}

//---------------------------------------------------------------------------//
// Check that an array view can be written to and read from a group attribute
FRENSIE_UNIT_TEST_TEMPLATE( HDF5File, group_attribute_rw_array_view, TestTypesExceptBool )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  Utility::HDF5File hdf5_file( hdf5_file_name, Utility::HDF5File::READ_WRITE );

  std::string attribute_name = Utility::typeName<T>();
  boost::replace_all( attribute_name, ":", "_" );
  boost::replace_all( attribute_name, "<", "__" );
  boost::replace_all( attribute_name, ">", "__" );
  boost::replace_all( attribute_name, ",", "_" );
  boost::replace_all( attribute_name, " ", "_" );

  std::string path_to_group( "/array_view/" );

  std::array<T,20> array_data;
  array_data.fill( zero(T()) );

  // Only elements 5-15 will be set to one
  Utility::ArrayView<T> array_view = array_data | Utility::Slice( 5, 10 );
  array_view.fill( one(T()) );

  FRENSIE_REQUIRE_NO_THROW( Utility::writeToGroupAttribute( hdf5_file, path_to_group, attribute_name, array_view ) );
  FRENSIE_REQUIRE( hdf5_file.doesGroupAttributeExist( path_to_group, attribute_name ) );

  // Array views cannot be used in read operations since their size is fixed
  std::vector<T> extracted_data( 10, zero(T()) );
  
  FRENSIE_REQUIRE_NO_THROW( Utility::readFromGroupAttribute( hdf5_file, path_to_group, attribute_name, extracted_data ) );
  FRENSIE_CHECK_EQUAL( Utility::arrayView(extracted_data), array_view );
  FRENSIE_CHECK_EQUAL( std::vector<T>( array_data.begin(), array_data.begin()+5 ),
                       std::vector<T>( 5, zero(T()) ) );
  FRENSIE_CHECK_EQUAL( std::vector<T>( array_data.begin()+15, array_data.end() ),
                       std::vector<T>( 5, zero(T()) ) );
}

//---------------------------------------------------------------------------//
// Check that a vector can be written to and read from a group attribute
FRENSIE_UNIT_TEST_TEMPLATE( HDF5File, group_attribute_rw_vector, TestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  Utility::HDF5File hdf5_file( hdf5_file_name, Utility::HDF5File::READ_WRITE );

  std::string attribute_name = Utility::typeName<T>();
  boost::replace_all( attribute_name, ":", "_" );
  boost::replace_all( attribute_name, "<", "__" );
  boost::replace_all( attribute_name, ">", "__" );
  boost::replace_all( attribute_name, ",", "_" );
  boost::replace_all( attribute_name, " ", "_" );

  std::string path_to_group( "/vector/" );

  std::vector<T> vector_data( 10, one(T()) );
  
  FRENSIE_REQUIRE_NO_THROW( Utility::writeToGroupAttribute( hdf5_file, path_to_group, attribute_name, vector_data ) );
  FRENSIE_REQUIRE( hdf5_file.doesGroupAttributeExist( path_to_group, attribute_name ) );
  
  std::vector<T> extracted_vector_data;
  
  FRENSIE_REQUIRE_NO_THROW( Utility::readFromGroupAttribute( hdf5_file, path_to_group, attribute_name, extracted_vector_data ) );
  FRENSIE_CHECK_EQUAL( extracted_vector_data, vector_data );
}

//---------------------------------------------------------------------------//
// Check that a deque can be written to and read from a group attribute
FRENSIE_UNIT_TEST_TEMPLATE( HDF5File, group_attribute_rw_deque, TestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  Utility::HDF5File hdf5_file( hdf5_file_name, Utility::HDF5File::READ_WRITE );

  std::string attribute_name = Utility::typeName<T>();
  boost::replace_all( attribute_name, ":", "_" );
  boost::replace_all( attribute_name, "<", "__" );
  boost::replace_all( attribute_name, ">", "__" );
  boost::replace_all( attribute_name, ",", "_" );
  boost::replace_all( attribute_name, " ", "_" );

  std::string path_to_group( "/deque/" );

  std::deque<T> deque_data( 10, one(T()) );
  
  FRENSIE_REQUIRE_NO_THROW( Utility::writeToGroupAttribute( hdf5_file, path_to_group, attribute_name, deque_data ) );
  FRENSIE_REQUIRE( hdf5_file.doesGroupAttributeExist( path_to_group, attribute_name ) );
  
  std::deque<T> extracted_deque_data;
  
  FRENSIE_REQUIRE_NO_THROW( Utility::readFromGroupAttribute( hdf5_file, path_to_group, attribute_name, extracted_deque_data ) );
  FRENSIE_CHECK_EQUAL( extracted_deque_data, deque_data );
}

//---------------------------------------------------------------------------//
// Check that a list can be written to and read from a group attribute
FRENSIE_UNIT_TEST_TEMPLATE( HDF5File, group_attribute_rw_list, TestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  Utility::HDF5File hdf5_file( hdf5_file_name, Utility::HDF5File::READ_WRITE );

  std::string attribute_name = Utility::typeName<T>();
  boost::replace_all( attribute_name, ":", "_" );
  boost::replace_all( attribute_name, "<", "__" );
  boost::replace_all( attribute_name, ">", "__" );
  boost::replace_all( attribute_name, ",", "_" );
  boost::replace_all( attribute_name, " ", "_" );

  std::string path_to_group( "/list/" );

  std::list<T> list_data( 10, one(T()) );
  
  FRENSIE_REQUIRE_NO_THROW( Utility::writeToGroupAttribute( hdf5_file, path_to_group, attribute_name, list_data ) );
  FRENSIE_REQUIRE( hdf5_file.doesGroupAttributeExist( path_to_group, attribute_name ) );
  
  std::list<T> extracted_list_data;
  
  FRENSIE_REQUIRE_NO_THROW( Utility::readFromGroupAttribute( hdf5_file, path_to_group, attribute_name, extracted_list_data ) );
  FRENSIE_CHECK_EQUAL( extracted_list_data, list_data );
}

//---------------------------------------------------------------------------//
// Check that a forward_list can be written to and read from a group attribute
FRENSIE_UNIT_TEST_TEMPLATE( HDF5File, group_attribute_rw_forward_list, TestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  Utility::HDF5File hdf5_file( hdf5_file_name, Utility::HDF5File::READ_WRITE );

  std::string attribute_name = Utility::typeName<T>();
  boost::replace_all( attribute_name, ":", "_" );
  boost::replace_all( attribute_name, "<", "__" );
  boost::replace_all( attribute_name, ">", "__" );
  boost::replace_all( attribute_name, ",", "_" );
  boost::replace_all( attribute_name, " ", "_" );

  std::string path_to_group( "/forward_list/" );

  std::forward_list<T> forward_list_data( 10, one(T()) );
  
  FRENSIE_REQUIRE_NO_THROW( Utility::writeToGroupAttribute( hdf5_file, path_to_group, attribute_name, forward_list_data ) );
  FRENSIE_REQUIRE( hdf5_file.doesGroupAttributeExist( path_to_group, attribute_name ) );
    
  std::forward_list<T> extracted_forward_list_data;
  
  FRENSIE_REQUIRE_NO_THROW( Utility::readFromGroupAttribute( hdf5_file, path_to_group, attribute_name, extracted_forward_list_data ) );
  FRENSIE_CHECK_EQUAL( extracted_forward_list_data, forward_list_data );
}

//---------------------------------------------------------------------------//
// Check that a set can be written to and read from a group attribute
FRENSIE_UNIT_TEST_TEMPLATE( HDF5File, group_attribute_rw_set, BasicTestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  Utility::HDF5File hdf5_file( hdf5_file_name, Utility::HDF5File::READ_WRITE );

  std::string attribute_name = Utility::typeName<T>();
  boost::replace_all( attribute_name, ":", "_" );
  boost::replace_all( attribute_name, "<", "__" );
  boost::replace_all( attribute_name, ">", "__" );
  boost::replace_all( attribute_name, ",", "_" );
  boost::replace_all( attribute_name, " ", "_" );

  std::string path_to_group( "/set/" );

  std::set<T> set_data;
  set_data.insert( zero(T()) );
  set_data.insert( one(T()) );
  
  FRENSIE_REQUIRE_NO_THROW( Utility::writeToGroupAttribute( hdf5_file, path_to_group, attribute_name, set_data ) );
  FRENSIE_REQUIRE( hdf5_file.doesGroupAttributeExist( path_to_group, attribute_name ) );
  
  std::set<T> extracted_set_data;
  
  FRENSIE_REQUIRE_NO_THROW( Utility::readFromGroupAttribute( hdf5_file, path_to_group, attribute_name, extracted_set_data ) );
  FRENSIE_CHECK_EQUAL( extracted_set_data, set_data );
}

//---------------------------------------------------------------------------//
// Check that an unordered_set can be written to and read from a group attr
FRENSIE_UNIT_TEST_TEMPLATE( HDF5File, group_attribute_rw_unordered_set, BasicTestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  Utility::HDF5File hdf5_file( hdf5_file_name, Utility::HDF5File::READ_WRITE );

  std::string attribute_name = Utility::typeName<T>();
  boost::replace_all( attribute_name, ":", "_" );
  boost::replace_all( attribute_name, "<", "__" );
  boost::replace_all( attribute_name, ">", "__" );
  boost::replace_all( attribute_name, ",", "_" );
  boost::replace_all( attribute_name, " ", "_" );

  std::string path_to_group( "/unordered_set/" );

  std::unordered_set<T> unordered_set_data;
  unordered_set_data.insert( zero(T()) );
  unordered_set_data.insert( one(T()) );
  
  FRENSIE_REQUIRE_NO_THROW( Utility::writeToGroupAttribute( hdf5_file, path_to_group, attribute_name, unordered_set_data ) );
  FRENSIE_REQUIRE( hdf5_file.doesGroupAttributeExist( path_to_group, attribute_name ) );
  
  std::unordered_set<T> extracted_unordered_set_data;
  
  FRENSIE_REQUIRE_NO_THROW( Utility::readFromGroupAttribute( hdf5_file, path_to_group, attribute_name, extracted_unordered_set_data ) );
  FRENSIE_CHECK_EQUAL( extracted_unordered_set_data, unordered_set_data );
}

//---------------------------------------------------------------------------//
// Check that a map can be written to and read from a group attribute
FRENSIE_UNIT_TEST_TEMPLATE( HDF5File, group_attribute_rw_map, BasicTestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  Utility::HDF5File hdf5_file( hdf5_file_name, Utility::HDF5File::READ_WRITE );

  std::string attribute_name = Utility::typeName<T>();
  boost::replace_all( attribute_name, ":", "_" );
  boost::replace_all( attribute_name, "<", "__" );
  boost::replace_all( attribute_name, ">", "__" );
  boost::replace_all( attribute_name, ",", "_" );
  boost::replace_all( attribute_name, " ", "_" );

  std::string path_to_group( "/map/" );

  std::map<T,T> map_data;
  map_data[zero(T())] = one(T());
  map_data[one(T())] = zero(T());
  
  FRENSIE_REQUIRE_NO_THROW( Utility::writeToGroupAttribute( hdf5_file, path_to_group, attribute_name, map_data ) );
  FRENSIE_REQUIRE( hdf5_file.doesGroupAttributeExist( path_to_group, attribute_name ) );
  
  std::map<T,T> extracted_map_data;
  
  FRENSIE_REQUIRE_NO_THROW( Utility::readFromGroupAttribute( hdf5_file, path_to_group, attribute_name, extracted_map_data ) );
  FRENSIE_CHECK_EQUAL( extracted_map_data, map_data );
}

//---------------------------------------------------------------------------//
// Check that an unordered_map can be written to and read from a group attr
FRENSIE_UNIT_TEST_TEMPLATE( HDF5File, group_attribute_rw_unordered_map, BasicTestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  Utility::HDF5File hdf5_file( hdf5_file_name, Utility::HDF5File::READ_WRITE );

  std::string attribute_name = Utility::typeName<T>();
  boost::replace_all( attribute_name, ":", "_" );
  boost::replace_all( attribute_name, "<", "__" );
  boost::replace_all( attribute_name, ">", "__" );
  boost::replace_all( attribute_name, ",", "_" );
  boost::replace_all( attribute_name, " ", "_" );

  std::string path_to_group( "/unordered_map/" );

  std::unordered_map<T,T> unordered_map_data;
  unordered_map_data[zero(T())] = one(T());
  unordered_map_data[one(T())] = zero(T());
  
  FRENSIE_REQUIRE_NO_THROW( Utility::writeToGroupAttribute( hdf5_file, path_to_group, attribute_name, unordered_map_data ) );
  FRENSIE_REQUIRE( hdf5_file.doesGroupAttributeExist( path_to_group, attribute_name ) );
  
  std::unordered_map<T,T> extracted_unordered_map_data;
  
  FRENSIE_REQUIRE_NO_THROW( Utility::readFromGroupAttribute( hdf5_file, path_to_group, attribute_name, extracted_unordered_map_data ) );
  FRENSIE_CHECK_EQUAL( extracted_unordered_map_data, unordered_map_data );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Delete any existing hdf5 test file
  Utility::HDF5File hdf5_file( hdf5_file_name, Utility::HDF5File::OVERWRITE  );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstHDF5FileGroupAttributeHelpers.cpp
//---------------------------------------------------------------------------//
