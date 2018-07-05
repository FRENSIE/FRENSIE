//---------------------------------------------------------------------------//
//!
//! \file   tstHDF5ArchiveArray.cpp
//! \author Alex Robinson
//! \brief  HDF5 archive array unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// FRENSIE Includes
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_Array.hpp"
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
                   float, double, long double> BasicTestTypes;

template<typename... Types>
struct PairTypes;

template<typename T, typename... Types>
struct PairTypes<T,Types...>
{
  typedef decltype(std::tuple_cat( std::tuple<std::pair<T,T> >(), typename PairTypes<Types...>::type())) type;
};

template<typename T>
struct PairTypes<T>
{
  typedef std::pair<T,T> type;
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
  typedef decltype(std::tuple_cat( std::tuple<std::tuple<T,T> >(), typename TwoElementTupleTypes<Types...>::type())) type;
};

template<typename T>
struct TwoElementTupleTypes<T>
{
  typedef std::tuple<T,T> type;
};

template<typename... Types>
struct TwoElementTupleTypes<std::tuple<Types...> > : public TwoElementTupleTypes<Types...>
{ /* ... */ };

template<typename... Types>
struct ThreeElementTupleTypes;

template<typename T, typename... Types>
struct ThreeElementTupleTypes<T,Types...>
{
  typedef decltype(std::tuple_cat( std::tuple<std::tuple<T,T,T> >(), typename ThreeElementTupleTypes<Types...>::type())) type;
};

template<typename T>
struct ThreeElementTupleTypes<T>
{
  typedef std::tuple<std::tuple<T,T,T> > type;
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

typedef typename MergeTypeLists<typename PairTypes<BasicTestTypes>::type,typename OneElementTupleTypes<BasicTestTypes>::type,typename TwoElementTupleTypes<BasicTestTypes>::type,typename ThreeElementTupleTypes<BasicTestTypes>::type>::type BasicTupleTestTypes;

typedef typename MergeTypeLists<BasicTestTypes,typename PairTypes<BasicTestTypes>::type,typename TwoElementTupleTypes<BasicTestTypes>::type>::type AllBasicTestTypes;

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
// Tests.
//---------------------------------------------------------------------------//
// Check that arrays of basic types can be archived
FRENSIE_UNIT_TEST_TEMPLATE( HDF5Archive,
                            archive_array_basic_types,
                            AllBasicTestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  std::string archive_name( "test_array_basic_types.h5a" );

  std::array<T,10> array;
  array.fill( one(T()) );

  {
    Utility::HDF5OArchive archive( archive_name, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE );

    // Array optimization should be used with this type
    FRENSIE_REQUIRE( Utility::HDF5OArchive::use_array_optimization::apply<T>::type::value );

    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "array", array ) );
  }

  {
    Utility::HDF5IArchive archive( archive_name );

    std::array<T,10> extracted_array;
    extracted_array.fill( zero(T()) );

    // Array optimization should be used with this type
    FRENSIE_REQUIRE( Utility::HDF5IArchive::use_array_optimization::apply<T>::type::value );

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "array", extracted_array ) );
    FRENSIE_CHECK_EQUAL( array, extracted_array );
  }
}

//---------------------------------------------------------------------------//
// Check that an array of strings can be archived
FRENSIE_UNIT_TEST( HDF5Archive, archive_array_string )
{
  std::string archive_name( "test_array_string.h5a" );

  std::array<std::string,5> array_a;
  array_a.fill( std::string("Test message a") );

  std::array<std::tuple<std::string>, 10> array_b;
  array_b.fill( std::make_tuple(std::string("Test message b")) );
  
  std::array<std::pair<std::string,std::string>,10> array_c;
  array_c.fill( std::make_pair(std::string("Test message c-0"), std::string("Test message c-1")) );

  std::array<std::tuple<std::string,std::string,std::string>,20> array_d;
  array_d.fill( std::make_tuple(std::string("Test message d-0"), std::string("Test message d-1"), std::string("Test message d-2")) );

  {
    Utility::HDF5OArchive archive( archive_name, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE );

    // Array optimization should be done with strings
    FRENSIE_REQUIRE( Utility::HDF5OArchive::use_array_optimization::apply<std::string>::type::value );

    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "array_a", array_a ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "array_b", array_b ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "array_c", array_c ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "array_d", array_d ) );
  }

  {
    Utility::HDF5IArchive archive( archive_name );

    std::array<std::string,5> extracted_array_a;
    std::array<std::tuple<std::string>, 10> extracted_array_b;
    std::array<std::pair<std::string,std::string>,10> extracted_array_c;
    std::array<std::tuple<std::string,std::string,std::string>,20> extracted_array_d;

    // Array optimization should be done with strings
    FRENSIE_REQUIRE( Utility::HDF5IArchive::use_array_optimization::apply<std::string>::type::value );

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "array_a", extracted_array_a ) );
    FRENSIE_CHECK_EQUAL( extracted_array_a, array_a );

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "array_b", extracted_array_b ) );
    FRENSIE_CHECK_EQUAL( extracted_array_b, array_b );

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "array_c", extracted_array_c ) );
    FRENSIE_CHECK_EQUAL( extracted_array_c, array_c );

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "array_d", extracted_array_d ) );
    FRENSIE_CHECK_EQUAL( extracted_array_d, array_d );
  }
}

//---------------------------------------------------------------------------//
// Check that arrays of advanced types can be archived
FRENSIE_UNIT_TEST_TEMPLATE( HDF5Archive,
                            archive_array_advanced_types,
                            BasicTestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  std::string archive_name( "test_array_advanced_types.h5a" );
  
  std::array<std::pair<T,std::array<T,3> >,10> array_a;
  array_a.fill( std::make_pair( one(T()), std::array<T,3>({one(T()), one(T()), one(T())}) ) );

  std::array<std::tuple<std::array<T,3> ,T>,10> array_b;
  array_b.fill( std::make_tuple( std::array<T,3>({one(T()), one(T()), one(T())}), one(T()) ) );

  std::array<std::tuple<T,std::array<T,3> ,T>,20> array_c;
  array_c.fill( std::make_tuple( zero(T()), std::array<T,3>({one(T()), one(T()), one(T())}), one(T()) ) );

  {
    Utility::HDF5OArchive archive( archive_name, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE );

    // Array optimization should not be used with these types
    FRENSIE_REQUIRE( !(Utility::HDF5OArchive::use_array_optimization::apply<std::pair<T,std::array<T,3> > >::type::value) );
    FRENSIE_REQUIRE( !(Utility::HDF5OArchive::use_array_optimization::apply<std::tuple<std::array<T,3> ,T> >::type::value) );
    FRENSIE_REQUIRE( !(Utility::HDF5OArchive::use_array_optimization::apply<std::tuple<T,std::array<T,3> ,T> >::type::value) );

    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "array_a", array_a ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "array_b", array_b ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "array_c", array_c ) );
  }

  {
    Utility::HDF5IArchive archive( archive_name );

    std::array<std::pair<T,std::array<T,3> >,10> extracted_array_a;
    std::array<std::tuple<std::array<T,3> ,T>,10> extracted_array_b;
    std::array<std::tuple<T,std::array<T,3> ,T>,20> extracted_array_c;

    // Array optimization should not be used with these types
    FRENSIE_REQUIRE( !(Utility::HDF5IArchive::use_array_optimization::apply<std::pair<T,std::array<T,3> > >::type::value) );
    FRENSIE_REQUIRE( !(Utility::HDF5IArchive::use_array_optimization::apply<std::tuple<std::array<T,3> ,T> >::type::value) );
    FRENSIE_REQUIRE( !(Utility::HDF5IArchive::use_array_optimization::apply<std::tuple<T,std::array<T,3> ,T> >::type::value) );

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "array_a", extracted_array_a ) );
    FRENSIE_CHECK_EQUAL( extracted_array_a, array_a );
    
    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "array_b", extracted_array_b ) );
    FRENSIE_CHECK_EQUAL( extracted_array_b, array_b );

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "array_c", extracted_array_c ) );
    FRENSIE_CHECK_EQUAL( extracted_array_c, array_c );
  }
}

//---------------------------------------------------------------------------//
// end tstHDF5ArchiveArray.cpp
//---------------------------------------------------------------------------//
