//---------------------------------------------------------------------------//
//!
//! \file   tstHDF5File.cpp
//! \author Alex Robinson
//! \brief  HDF5 file unit tests
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
#include "Utility_Vector.hpp"
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
                   float, double, long double,
                   std::string> BasicTestTypes;

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
inline typename std::enable_if<!std::is_same<T,std::string>::value,T>::type zero( T )
{ return T(0); }

template<typename T>
inline typename std::enable_if<std::is_same<T,std::string>::value,T>::type zero( T )
{ return "Zero"; }

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
inline typename std::enable_if<!std::is_same<T,std::string>::value,T>::type one( T )
{ return T(1); }

template<typename T>
inline typename std::enable_if<std::is_same<T,std::string>::value,T>::type one( T )
{ return "one"; }

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
std::string hdf5_file_name( "test_file.h5" );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the filename can be returned
FRENSIE_UNIT_TEST( HDF5File, constructor )
{
  std::unique_ptr<Utility::HDF5File> hdf5_file;
  
#ifdef HAVE_FRENSIE_HDF5
  FRENSIE_REQUIRE_NO_THROW(hdf5_file.reset( new Utility::HDF5File( hdf5_file_name ) ));

  FRENSIE_CHECK_EQUAL( hdf5_file->getFilename(), hdf5_file_name );
#else
  FRENSIE_REQUIRE_THROW(hdf5_file.reset( new Utility::HDF5File( hdf5_file_name ) ),
                        std::logic_error);
#endif
}

#ifdef HAVE_FRENSIE_HDF5

//---------------------------------------------------------------------------//
// Check that a group exists
FRENSIE_UNIT_TEST( HDF5File, doesGroupExist )
{
  Utility::HDF5File hdf5_file( hdf5_file_name, Utility::HDF5File::OVERWRITE );

  // The root group should always exist
  FRENSIE_CHECK( hdf5_file.doesGroupExist( "/" ) );

  // No other groups should exist
  FRENSIE_CHECK( !hdf5_file.doesGroupExist( "dummy" ) );
  FRENSIE_CHECK( !hdf5_file.doesGroupExist( "/dummy" ) );
  FRENSIE_CHECK( !hdf5_file.doesGroupExist( "/dummy/" ) );
}

//---------------------------------------------------------------------------//
// Check that a group can be created
FRENSIE_UNIT_TEST( HDF5File, createGroup )
{
  Utility::HDF5File hdf5_file( hdf5_file_name, Utility::HDF5File::OVERWRITE );

  FRENSIE_REQUIRE_NO_THROW(hdf5_file.createGroup( "/test_dir/" ));
  FRENSIE_REQUIRE( hdf5_file.doesGroupExist( "/test_dir/" ) );

  // If the group already exists nothing should happen
  FRENSIE_REQUIRE_NO_THROW(hdf5_file.createGroup( "/test_dir/" ));
  FRENSIE_REQUIRE( hdf5_file.doesGroupExist( "/test_dir/" ) );

  // Check that parent groups that do not exists will be created
  FRENSIE_REQUIRE_NO_THROW(hdf5_file.createGroup( "/test_dir/__a__/__b__/" ));
  FRENSIE_REQUIRE( hdf5_file.doesGroupExist( "/test_dir/__a__/" ) );
  FRENSIE_REQUIRE( hdf5_file.doesGroupExist( "/test_dir/__a__/__b__/" ) );
}

//---------------------------------------------------------------------------//
// Check that data can be written to and read from a data set
FRENSIE_UNIT_TEST_TEMPLATE( HDF5File, data_set_rw, TestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  Utility::HDF5File hdf5_file( hdf5_file_name, Utility::HDF5File::READ_WRITE  );

  std::array<T,10> data;
  data.fill( one(T()) );

  std::string data_set_1_name = "/";
  std::string data_set_2_name = "/test_dir/";

  {
    std::string type_name = Utility::typeName<T>();
    boost::replace_all( type_name, ":", "_" );
    boost::replace_all( type_name, "<", "__" );
    boost::replace_all( type_name, ">", "__" );
    boost::replace_all( type_name, ",", "_" );
    boost::replace_all( type_name, " ", "_" );

    data_set_1_name += type_name;
    data_set_2_name += type_name;
  }

  FRENSIE_REQUIRE_NO_THROW(hdf5_file.writeToDataSet( data_set_1_name, data.data(), data.size() ));
  FRENSIE_REQUIRE_NO_THROW(hdf5_file.writeToDataSet( data_set_2_name, data[0] ));

  // Check that expected groups exist
  FRENSIE_REQUIRE( hdf5_file.doesGroupExist( "/" ) );
  FRENSIE_REQUIRE( hdf5_file.doesGroupExist( "/test_dir/" ) );

  // Check that expected data sets exist
  FRENSIE_REQUIRE( hdf5_file.doesDataSetExist( data_set_1_name ) );
  FRENSIE_REQUIRE( hdf5_file.doesDataSetExist( data_set_2_name ) );

  // Extract the data set sizes
  hsize_t data_set_1_size = 0, data_set_2_size = 0;

  FRENSIE_REQUIRE_NO_THROW( data_set_1_size = hdf5_file.getDataSetSize( data_set_1_name ));
  if( Utility::HDF5TypeTraits<T>::UsesOpaqueDataType::value )
  {
    FRENSIE_CHECK_EQUAL( data_set_1_size, data.size()*sizeof(T) );
  }
  else
  {
    FRENSIE_CHECK_EQUAL( data_set_1_size, data.size() );
  }
  
  FRENSIE_CHECK_NO_THROW( data_set_2_size = hdf5_file.getDataSetSize( data_set_2_name ));

  if( Utility::HDF5TypeTraits<T>::UsesOpaqueDataType::value )
  {
    FRENSIE_CHECK_EQUAL( data_set_2_size, sizeof(T) );
  }
  else
  {
    FRENSIE_CHECK_EQUAL( data_set_2_size, 1 );
  }

  // Extract data set data
  T* extracted_data;
  Utility::ArrayView<T> extracted_data_view;

  if( Utility::HDF5TypeTraits<T>::UsesOpaqueDataType::value )
  {
    extracted_data = new T[data_set_1_size/sizeof(T)];
    extracted_data_view =
      Utility::ArrayView<T>( extracted_data,
                             extracted_data+data_set_1_size/sizeof(T) );
  }
  else
  {
    extracted_data = new T[data_set_1_size];
    extracted_data_view =
      Utility::ArrayView<T>( extracted_data, extracted_data+data_set_1_size );
  }

  extracted_data_view.fill( zero(T()) );

  FRENSIE_REQUIRE_NO_THROW( hdf5_file.readFromDataSet( data_set_1_name, extracted_data_view.data(), extracted_data_view.size() ) );
  FRENSIE_REQUIRE_EQUAL( extracted_data_view, Utility::arrayView(data) );

  if( Utility::HDF5TypeTraits<T>::UsesOpaqueDataType::value )
  {
    extracted_data_view =
      Utility::ArrayView<T>( extracted_data,
                             extracted_data+data_set_2_size/sizeof(T) );
  }
  else
  {
    extracted_data_view =
      Utility::ArrayView<T>( extracted_data, extracted_data+data_set_2_size );
  }

  extracted_data_view.fill( zero(T()) );
  
  FRENSIE_REQUIRE_NO_THROW( hdf5_file.readFromDataSet( data_set_2_name, extracted_data_view.data(), extracted_data_view.size() ) );
  FRENSIE_CHECK_EQUAL( extracted_data_view,
                       data | Utility::Slice(0, 1) );

  delete[] extracted_data;
}

//---------------------------------------------------------------------------//
// Check that data can be written to and read from a data set attribute
FRENSIE_UNIT_TEST_TEMPLATE( HDF5File, data_set_attribute_rw, TestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  Utility::HDF5File hdf5_file( hdf5_file_name, Utility::HDF5File::READ_WRITE  );

  std::array<T,10> data;
  data.fill( one(T()) );

  std::string data_set_1_name = "/";
  std::string data_set_2_name = "/test_dir/";
  
  {
    std::string type_name = Utility::typeName<T>();
    boost::replace_all( type_name, ":", "_" );
    boost::replace_all( type_name, "<", "__" );
    boost::replace_all( type_name, ">", "__" );
    boost::replace_all( type_name, ",", "_" );
    boost::replace_all( type_name, " ", "_" );

    data_set_1_name += type_name;
    data_set_2_name += type_name;
  }

  std::string attribute_name( "test_attribute" );

  FRENSIE_REQUIRE_NO_THROW(hdf5_file.writeToDataSetAttribute( data_set_1_name, attribute_name, data.data(), data.size() ));
  FRENSIE_REQUIRE_NO_THROW(hdf5_file.writeToDataSetAttribute( data_set_2_name, attribute_name, data[0] ));

  // Check that expected attributes exist
  FRENSIE_REQUIRE( hdf5_file.doesDataSetAttributeExist( data_set_1_name, attribute_name ) );
  FRENSIE_REQUIRE( hdf5_file.doesDataSetAttributeExist( data_set_2_name, attribute_name ) );

  // Extract the data set attribute sizes
  hsize_t data_set_attr_1_size = 0, data_set_attr_2_size = 0;

  FRENSIE_REQUIRE_NO_THROW( data_set_attr_1_size = hdf5_file.getDataSetAttributeSize( data_set_1_name, attribute_name ));
  
  if( Utility::HDF5TypeTraits<T>::UsesOpaqueDataType::value )
  {
    FRENSIE_CHECK_EQUAL( data_set_attr_1_size, data.size()*sizeof(T) );
  }
  else
  {
    FRENSIE_CHECK_EQUAL( data_set_attr_1_size, data.size() );
  }
  
  FRENSIE_REQUIRE_NO_THROW( data_set_attr_2_size = hdf5_file.getDataSetAttributeSize( data_set_2_name, attribute_name ));

  if( Utility::HDF5TypeTraits<T>::UsesOpaqueDataType::value )
  {
    FRENSIE_CHECK_EQUAL( data_set_attr_2_size, sizeof(T) );
  }
  else
  {
    FRENSIE_CHECK_EQUAL( data_set_attr_2_size, 1 );
  }

  // Extract data set attribute data
  T* extracted_data;
  Utility::ArrayView<T> extracted_data_view;

  if( Utility::HDF5TypeTraits<T>::UsesOpaqueDataType::value )
  {
    extracted_data = new T[data_set_attr_1_size/sizeof(T)];
    extracted_data_view =
      Utility::ArrayView<T>( extracted_data,
                             extracted_data+data_set_attr_1_size/sizeof(T) );
  }
  else
  {
    extracted_data = new T[data_set_attr_1_size];
    extracted_data_view =
      Utility::ArrayView<T>( extracted_data,
                             extracted_data+data_set_attr_1_size );
  }

  extracted_data_view.fill( zero(T()) );

  FRENSIE_REQUIRE_NO_THROW( hdf5_file.readFromDataSetAttribute( data_set_1_name, attribute_name, extracted_data_view.data(), extracted_data_view.size() ) );
  FRENSIE_CHECK_EQUAL( extracted_data_view, Utility::arrayView(data) );

  if( Utility::HDF5TypeTraits<T>::UsesOpaqueDataType::value )
  {
    extracted_data_view =
      Utility::ArrayView<T>( extracted_data,
                             extracted_data+data_set_attr_2_size/sizeof(T) );
  }
  else
  {
    extracted_data_view =
      Utility::ArrayView<T>( extracted_data,
                             extracted_data+data_set_attr_2_size );
  }

  extracted_data_view.fill( zero(T()) );
  
  FRENSIE_REQUIRE_NO_THROW( hdf5_file.readFromDataSetAttribute( data_set_2_name, attribute_name, extracted_data_view.data(), extracted_data_view.size() ) );
  FRENSIE_CHECK_EQUAL( extracted_data_view,
                       data | Utility::Slice(0, 1) );

  delete[] extracted_data;
}

//---------------------------------------------------------------------------//
// Check that data can be written to and read from a group attribute
FRENSIE_UNIT_TEST_TEMPLATE( HDF5File, group_attribute_rw, TestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  Utility::HDF5File hdf5_file( hdf5_file_name, Utility::HDF5File::READ_WRITE  );

  std::array<T,10> data;
  data.fill( one(T()) );

  std::string group_1_name = "/";
  std::string group_2_name = "/test_dir/";

  std::string attribute_name = Utility::typeName<T>();
  boost::replace_all( attribute_name, ":", "_" );
  boost::replace_all( attribute_name, "<", "__" );
  boost::replace_all( attribute_name, ">", "__" );
  boost::replace_all( attribute_name, ",", "_" );
  boost::replace_all( attribute_name, " ", "_" );  

  FRENSIE_REQUIRE_NO_THROW(hdf5_file.writeToGroupAttribute( group_1_name, attribute_name, data.data(), data.size() ));
  FRENSIE_REQUIRE_NO_THROW(hdf5_file.writeToGroupAttribute( group_2_name, attribute_name, data[0] ));

  // Check that expected attributes exist
  FRENSIE_REQUIRE( hdf5_file.doesGroupAttributeExist( group_1_name, attribute_name ) );
  FRENSIE_REQUIRE( hdf5_file.doesGroupAttributeExist( group_2_name, attribute_name ) );

  // Extract the group attribute sizes
  hsize_t group_attr_1_size = 0, group_attr_2_size = 0;

  FRENSIE_REQUIRE_NO_THROW( group_attr_1_size = hdf5_file.getGroupAttributeSize( group_1_name, attribute_name ));
  
  if( Utility::HDF5TypeTraits<T>::UsesOpaqueDataType::value )
  {
    FRENSIE_CHECK_EQUAL( group_attr_1_size, data.size()*sizeof(T) );
  }
  else
  {
    FRENSIE_CHECK_EQUAL( group_attr_1_size, data.size() );
  }
  
  FRENSIE_REQUIRE_NO_THROW( group_attr_2_size = hdf5_file.getGroupAttributeSize( group_2_name, attribute_name ));

  if( Utility::HDF5TypeTraits<T>::UsesOpaqueDataType::value )
  {
    FRENSIE_CHECK_EQUAL( group_attr_2_size, sizeof(T) );
  }
  else
  {
    FRENSIE_CHECK_EQUAL( group_attr_2_size, 1 );
  }

  // Extract group attribute data
  T* extracted_data;
  Utility::ArrayView<T> extracted_data_view;

  if( Utility::HDF5TypeTraits<T>::UsesOpaqueDataType::value )
  {
    extracted_data = new T[group_attr_1_size/sizeof(T)];
    extracted_data_view =
      Utility::ArrayView<T>( extracted_data,
                             extracted_data+group_attr_1_size/sizeof(T) );
  }
  else
  {
    extracted_data = new T[group_attr_1_size];
    extracted_data_view =
      Utility::ArrayView<T>( extracted_data,
                             extracted_data+group_attr_1_size );
  }

  extracted_data_view.fill( zero(T()) );

  FRENSIE_REQUIRE_NO_THROW( hdf5_file.readFromGroupAttribute( group_1_name, attribute_name, extracted_data_view.data(), extracted_data_view.size() ) );
  FRENSIE_CHECK_EQUAL( extracted_data_view, Utility::arrayView(data) );

  if( Utility::HDF5TypeTraits<T>::UsesOpaqueDataType::value )
  {
    extracted_data_view =
      Utility::ArrayView<T>( extracted_data,
                             extracted_data+group_attr_2_size/sizeof(T) );
  }
  else
  {
    extracted_data_view =
      Utility::ArrayView<T>( extracted_data,
                             extracted_data+group_attr_2_size );
  }

  extracted_data_view.fill( zero(T()) );
  
  FRENSIE_REQUIRE_NO_THROW( hdf5_file.readFromGroupAttribute( group_2_name, attribute_name, extracted_data_view.data(), extracted_data_view.size() ) );
  FRENSIE_CHECK_EQUAL( extracted_data_view,
                       data | Utility::Slice(0, 1) );

  delete[] extracted_data;
}

//---------------------------------------------------------------------------//
// Check that a hard link can be created
FRENSIE_UNIT_TEST( HDF5File, createHardLink )
{
  Utility::HDF5File hdf5_file( hdf5_file_name, Utility::HDF5File::READ_WRITE  );
  // Link to the root group
  FRENSIE_REQUIRE_NO_THROW(hdf5_file.createHardLink( "/", "/link_dir/hard_links/link_to_root" ));
  FRENSIE_REQUIRE(hdf5_file.doesGroupExist( "/link_dir/hard_links/link_to_root" ));

  // Link to a non-root group
  if( !hdf5_file.doesGroupExist( "/test_dir/" ) )
    hdf5_file.createGroup( "/test_dir/" );
  
  FRENSIE_REQUIRE_NO_THROW(hdf5_file.createHardLink( "/test_dir", "/link_dir/hard_links/link_to_test_dir" ));
  FRENSIE_REQUIRE(hdf5_file.doesGroupExist( "/link_dir/hard_links/link_to_test_dir" ));

  // Link to a data set
  if( !hdf5_file.doesDataSetExist( "/int" ) )
  {
    std::array<int,10> data;
    data.fill( 1 );
    
    hdf5_file.writeToDataSet( "/int", data.data(), data.size() );
  }
  
  FRENSIE_REQUIRE_NO_THROW(hdf5_file.createHardLink( "/int", "/link_dir/hard_links/link_to_int_data_set" ));
  FRENSIE_REQUIRE(hdf5_file.doesDataSetExist( "/link_dir/hard_links/link_to_int_data_set" ));

  if( !hdf5_file.doesDataSetExist( "/test_dir/int" ) )
  {
    std::array<int,10> data;
    data.fill( 1 );
    
    hdf5_file.writeToDataSet( "/test_dir/int", data.data(), data.size() );
  }
  
  FRENSIE_REQUIRE_NO_THROW(hdf5_file.createHardLink( "/test_dir/int", "/link_dir/hard_links/link_to_test_dir_int_data_set" ));
  FRENSIE_REQUIRE(hdf5_file.doesDataSetExist( "/link_dir/hard_links/link_to_test_dir_int_data_set" ));
}

//---------------------------------------------------------------------------//
// Check that a soft link can be created
FRENSIE_UNIT_TEST( HDF5File, createSoftLink )
{
  Utility::HDF5File hdf5_file( hdf5_file_name, Utility::HDF5File::READ_WRITE  );
  // Link to the root group
  FRENSIE_REQUIRE_NO_THROW(hdf5_file.createSoftLink( "/", "/link_dir/soft_links/link_to_root" ));
  FRENSIE_REQUIRE(hdf5_file.doesGroupExist( "/link_dir/soft_links/link_to_root" ));

  // Link to a non-root group
  if( !hdf5_file.doesGroupExist( "/test_dir/" ) )
    hdf5_file.createGroup( "/test_dir/" );
  
  FRENSIE_REQUIRE_NO_THROW(hdf5_file.createSoftLink( "/test_dir", "/link_dir/soft_links/link_to_test_dir" ));
  FRENSIE_REQUIRE(hdf5_file.doesGroupExist( "/link_dir/soft_links/link_to_test_dir" ));

  // Link to a data set
  if( !hdf5_file.doesDataSetExist( "/int" ) )
  {
    std::array<int,10> data;
    data.fill( 1 );
    
    hdf5_file.writeToDataSet( "/int", data.data(), data.size() );
  }
  
  FRENSIE_REQUIRE_NO_THROW(hdf5_file.createSoftLink( "/int", "/link_dir/soft_links/link_to_int_data_set" ));
  FRENSIE_REQUIRE(hdf5_file.doesDataSetExist( "/link_dir/soft_links/link_to_int_data_set" ));

  if( !hdf5_file.doesDataSetExist( "/test_dir/int" ) )
  {
    std::array<int,10> data;
    data.fill( 1 );
    
    hdf5_file.writeToDataSet( "/test_dir/int", data.data(), data.size() );
  }
  
  FRENSIE_REQUIRE_NO_THROW(hdf5_file.createSoftLink( "/test_dir/int", "/link_dir/soft_links/link_to_test_dir_int_data_set" ));
  FRENSIE_REQUIRE(hdf5_file.doesDataSetExist( "/link_dir/soft_links/link_to_test_dir_int_data_set" ));
}

#endif // end HAVE_FRENSIE_HDF5

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
#ifdef HAVE_FRENSIE_HDF5
  // Delete any existing hdf5 test file
  Utility::HDF5File hdf5_file( hdf5_file_name, Utility::HDF5File::OVERWRITE  );
#endif
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstHDF5File.cpp
//---------------------------------------------------------------------------//

