//---------------------------------------------------------------------------//
//!
//! \file   tstHDF5FileHelpers.cpp
//! \author Alex Robinson
//! \brief  HDF5 file helper method unit tests
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
typedef std::tuple<bool,
                   char, unsigned char, signed char, wchar_t,
                   short, unsigned short,
                   int, unsigned int,
                   long, unsigned long,
                   long long, unsigned long long,
                   float, double, long double> BasicTestTypes;

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

typedef typename MergeTypeLists<BasicTestTypes,typename PairTypes<BasicTestTypes>::type,typename OneElementTupleTypes<BasicTestTypes>::type,typename TwoElementTupleTypes<BasicTestTypes>::type,typename ThreeElementTupleTypes<BasicTestTypes>::type>::type TestTypes;

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
std::string hdf5_file_name( "container_test_file.h5" );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that containers can be written to and read from a data set
FRENSIE_UNIT_TEST_TEMPLATE( HDF5File, data_set_rw_sequence_containers, TestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  Utility::HDF5File hdf5_file( hdf5_file_name, Utility::HDF5File::READ_WRITE );

  std::string data_set_name = Utility::typeName<T>();
  boost::replace_all( data_set_name, ":", "_" );
  boost::replace_all( data_set_name, "<", "__" );
  boost::replace_all( data_set_name, ">", "__" );
  boost::replace_all( data_set_name, ",", "_" );
  boost::replace_all( data_set_name, " ", "_" );

  // Read/write an initializer list
  {
    std::string data_set_name_with_path( "/init_list/" );
    data_set_name_with_path += data_set_name;
    
    FRENSIE_REQUIRE_NO_THROW( Utility::writeToDataSet( hdf5_file, data_set_name_with_path, {zero(T()), one(T()), zero(T()), one(T())} ) );
    FRENSIE_REQUIRE( hdf5_file.doesDataSetExist( data_set_name_with_path ) );

    // Init lists cannot used in read operations since their size is fixed
    std::vector<T> init_list_data;
    
    FRENSIE_REQUIRE_NO_THROW( Utility::readFromDataSet( hdf5_file, data_set_name_with_path, init_list_data ) );
    FRENSIE_CHECK_EQUAL( init_list_data, std::vector<T>({zero(T()), one(T()), zero(T()), one(T())}) );
  }

  // Read/write an array 
  {
    std::string data_set_name_with_path( "/array/" );
    data_set_name_with_path += data_set_name;

    std::array<T,10> array_data;
    array_data.fill( one(T()) );

    FRENSIE_REQUIRE_NO_THROW( Utility::writeToDataSet( hdf5_file, data_set_name_with_path, array_data ) );
    FRENSIE_REQUIRE( hdf5_file.doesDataSetExist( data_set_name_with_path ) );

    // Arrays cannot be used in read operations since their size is fixed
    std::vector<T> extracted_array_data;

    FRENSIE_REQUIRE_NO_THROW( Utility::readFromDataSet( hdf5_file, data_set_name_with_path, extracted_array_data ) );
    FRENSIE_CHECK_EQUAL( extracted_array_data,
                         std::vector<T>(array_data.begin(), array_data.end()) );
  }

  // Read/write a vector 
  {
    std::string data_set_name_with_path( "/vector/" );
    data_set_name_with_path += data_set_name;

    std::vector<T> vector_data( 10, one(T()) );

    FRENSIE_REQUIRE_NO_THROW( Utility::writeToDataSet( hdf5_file, data_set_name_with_path, vector_data ) );
    FRENSIE_REQUIRE( hdf5_file.doesDataSetExist( data_set_name_with_path ) );

    std::vector<T> extracted_vector_data;

    FRENSIE_REQUIRE_NO_THROW( Utility::readFromDataSet( hdf5_file, data_set_name_with_path, extracted_vector_data ) );
    FRENSIE_CHECK_EQUAL( extracted_vector_data, vector_data );
  }

  // Read/write a deque 
  {
    std::string data_set_name_with_path( "/deque/" );
    data_set_name_with_path += data_set_name;

    std::deque<T> deque_data( 10, one(T()) );

    FRENSIE_REQUIRE_NO_THROW( Utility::writeToDataSet( hdf5_file, data_set_name_with_path, deque_data ) );
    FRENSIE_REQUIRE( hdf5_file.doesDataSetExist( data_set_name_with_path ) );

    std::deque<T> extracted_deque_data;

    FRENSIE_REQUIRE_NO_THROW( Utility::readFromDataSet( hdf5_file, data_set_name_with_path, extracted_deque_data ) );
    FRENSIE_CHECK_EQUAL( extracted_deque_data, deque_data );
  }

  // Read/write a list 
  {
    std::string data_set_name_with_path( "/list/" );
    data_set_name_with_path += data_set_name;

    std::list<T> list_data( 10, one(T()) );

    FRENSIE_REQUIRE_NO_THROW( Utility::writeToDataSet( hdf5_file, data_set_name_with_path, list_data ) );
    FRENSIE_REQUIRE( hdf5_file.doesDataSetExist( data_set_name_with_path ) );

    std::list<T> extracted_list_data;

    FRENSIE_REQUIRE_NO_THROW( Utility::readFromDataSet( hdf5_file, data_set_name_with_path, extracted_list_data ) );
    FRENSIE_CHECK_EQUAL( extracted_list_data, list_data );
  }

  // Read/write a forward_list
  {
    std::string data_set_name_with_path( "/forward_list/" );
    data_set_name_with_path += data_set_name;

    std::forward_list<T> forward_list_data( 10, one(T()) );

    FRENSIE_REQUIRE_NO_THROW( Utility::writeToDataSet( hdf5_file, data_set_name_with_path, forward_list_data ) );
    FRENSIE_REQUIRE( hdf5_file.doesDataSetExist( data_set_name_with_path ) );

    std::forward_list<T> extracted_forward_list_data;

    FRENSIE_REQUIRE_NO_THROW( Utility::readFromDataSet( hdf5_file, data_set_name_with_path, extracted_forward_list_data ) );
    FRENSIE_CHECK_EQUAL( extracted_forward_list_data, forward_list_data );
  }
}

//---------------------------------------------------------------------------//
// Check that containers can be written to and read from a data set
FRENSIE_UNIT_TEST_TEMPLATE( HDF5File, data_set_rw_associative_containers, BasicTestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  Utility::HDF5File hdf5_file( hdf5_file_name, Utility::HDF5File::READ_WRITE );

  std::string data_set_name = Utility::typeName<T>();
  boost::replace_all( data_set_name, ":", "_" );
  boost::replace_all( data_set_name, "<", "__" );
  boost::replace_all( data_set_name, ">", "__" );
  boost::replace_all( data_set_name, ",", "_" );
  boost::replace_all( data_set_name, " ", "_" );

  // Read/write a set
  {
    std::string data_set_name_with_path( "/set/" );
    data_set_name_with_path += data_set_name;

    std::set<T> set_data;
    set_data.insert( zero(T()) );
    set_data.insert( one(T()) );
    
    FRENSIE_REQUIRE_NO_THROW( Utility::writeToDataSet( hdf5_file, data_set_name_with_path, set_data ) );
    FRENSIE_REQUIRE( hdf5_file.doesDataSetExist( data_set_name_with_path ) );

    std::set<T> extracted_set_data;
    
    FRENSIE_REQUIRE_NO_THROW( Utility::readFromDataSet( hdf5_file, data_set_name_with_path, extracted_set_data ) );
    FRENSIE_CHECK_EQUAL( extracted_set_data, set_data );
  }

  // Read/write an unordered_set
  {
    std::string data_set_name_with_path( "/unordered_set/" );
    data_set_name_with_path += data_set_name;

    std::unordered_set<T> unordered_set_data;
    unordered_set_data.insert( zero(T()) );
    unordered_set_data.insert( one(T()) );
    
    FRENSIE_REQUIRE_NO_THROW( Utility::writeToDataSet( hdf5_file, data_set_name_with_path, unordered_set_data ) );
    FRENSIE_REQUIRE( hdf5_file.doesDataSetExist( data_set_name_with_path ) );

    std::unordered_set<T> extracted_unordered_set_data;
    
    FRENSIE_REQUIRE_NO_THROW( Utility::readFromDataSet( hdf5_file, data_set_name_with_path, extracted_unordered_set_data ) );
    FRENSIE_CHECK_EQUAL( extracted_unordered_set_data, unordered_set_data );
  }

  // Read/write a map
  {
    std::string data_set_name_with_path( "/map/" );
    data_set_name_with_path += data_set_name;

    std::map<T,T> map_data;
    map_data[zero(T())] = one(T());
    map_data[one(T())] = zero(T());
    
    FRENSIE_REQUIRE_NO_THROW( Utility::writeToDataSet( hdf5_file, data_set_name_with_path, map_data ) );
    FRENSIE_REQUIRE( hdf5_file.doesDataSetExist( data_set_name_with_path ) );

    std::map<T,T> extracted_map_data;
    
    FRENSIE_REQUIRE_NO_THROW( Utility::readFromDataSet( hdf5_file, data_set_name_with_path, extracted_map_data ) );
    FRENSIE_CHECK_EQUAL( extracted_map_data, map_data );
  }

  // Read/write a unordered_map
  {
    std::string data_set_name_with_path( "/unordered_map/" );
    data_set_name_with_path += data_set_name;

    std::unordered_map<T,T> unordered_map_data;
    unordered_map_data[zero(T())] = one(T());
    unordered_map_data[one(T())] = zero(T());
    
    FRENSIE_REQUIRE_NO_THROW( Utility::writeToDataSet( hdf5_file, data_set_name_with_path, unordered_map_data ) );
    FRENSIE_REQUIRE( hdf5_file.doesDataSetExist( data_set_name_with_path ) );

    std::unordered_map<T,T> extracted_unordered_map_data;
    
    FRENSIE_REQUIRE_NO_THROW( Utility::readFromDataSet( hdf5_file, data_set_name_with_path, extracted_unordered_map_data ) );
    FRENSIE_CHECK_EQUAL( extracted_unordered_map_data, unordered_map_data );
  }
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
// end tstHDF5FileHelpers.cpp
//---------------------------------------------------------------------------//
