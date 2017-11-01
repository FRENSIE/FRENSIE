//---------------------------------------------------------------------------//
//!
//! \file   tstHDF5ArchiveVector.cpp
//! \author Alex Robinson
//! \brief  HDF5 archive vector unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// FRENSIE Includes
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_Vector.hpp"
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
// Check that vectors of basic types can be archived
FRENSIE_UNIT_TEST_TEMPLATE( HDF5Archive,
                            archive_vector_basic_types,
                            AllBasicTestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  std::string archive_name( "test_vector_basic_types.h5a" );

  std::vector<T> vector( 10, one(T()) );

  {
    Utility::HDF5OArchive archive( archive_name, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE );

    // Array optimization should be used with this type
    FRENSIE_REQUIRE( Utility::HDF5OArchive::use_array_optimization::apply<T>::type::value );

    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "vector", vector ) );
  }

  {
    Utility::HDF5IArchive archive( archive_name );

    std::vector<T> extracted_vector;

    // Array optimization should be used with this type
    FRENSIE_REQUIRE( Utility::HDF5IArchive::use_array_optimization::apply<T>::type::value );

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "vector", extracted_vector ) );
    FRENSIE_CHECK_EQUAL( vector, extracted_vector );
  }
}

//---------------------------------------------------------------------------//
// Check that a vector of strings can be archived
FRENSIE_UNIT_TEST( HDF5Archive, archive_vector_string )
{
  std::string archive_name( "test_vector_string.h5a" );

  std::vector<std::string> vector_a( 5, std::string("Test message a") );

  std::vector<std::tuple<std::string> > vector_b( 10, std::make_tuple(std::string("Test message b")) );
  
  std::vector<std::pair<std::string,std::string> > vector_c( 10, std::make_pair(std::string("Test message c-0"), std::string("Test message c-1")) );

  std::vector<std::tuple<std::string,std::string,std::string> > vector_d( 20, std::make_tuple(std::string("Test message d-0"), std::string("Test message d-1"), std::string("Test message d-2")) );

  {
    Utility::HDF5OArchive archive( archive_name, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE );

    // Array optimization should done with strings
    FRENSIE_REQUIRE( Utility::HDF5OArchive::use_array_optimization::apply<std::string>::type::value );

    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "vector_a", vector_a ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "vector_b", vector_b ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "vector_c", vector_c ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "vector_d", vector_d ) );
  }

  {
    Utility::HDF5IArchive archive( archive_name );

    std::vector<std::string> extracted_vector_a;
    std::vector<std::tuple<std::string> > extracted_vector_b;
    std::vector<std::pair<std::string,std::string> > extracted_vector_c;
    std::vector<std::tuple<std::string,std::string,std::string> > extracted_vector_d;

    // Array optimization should not be done with strings
    FRENSIE_REQUIRE( Utility::HDF5IArchive::use_array_optimization::apply<std::string>::type::value );

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "vector_a", extracted_vector_a ) );
    FRENSIE_CHECK_EQUAL( extracted_vector_a, vector_a );

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "vector_b", extracted_vector_b ) );
    FRENSIE_CHECK_EQUAL( extracted_vector_b, vector_b );

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "vector_c", extracted_vector_c ) );
    FRENSIE_CHECK_EQUAL( extracted_vector_c, vector_c );

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "vector_d", extracted_vector_d ) );
    FRENSIE_CHECK_EQUAL( extracted_vector_d, vector_d );
  }
}

//---------------------------------------------------------------------------//
// Check that vectors of advanced types can be archived
FRENSIE_UNIT_TEST_TEMPLATE( HDF5Archive,
                            archive_vector_advanced_types,
                            BasicTestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  std::string archive_name( "test_vector_advanced_types.h5a" );
  
  std::vector<std::pair<T,std::vector<T> > > vector_a( 10, std::make_pair( one(T()), std::vector<T>( {zero(T()), one(T()), zero(T())} ) ) );

  std::vector<std::tuple<std::vector<T> ,T> > vector_b( 10, std::make_tuple( std::vector<T>( {zero(T()), one(T()), zero(T())} ), one(T()) ) );

  std::vector<std::tuple<T,std::vector<T> ,T> > vector_c( 20, std::make_tuple( zero(T()), std::vector<T>( {zero(T()), one(T()), zero(T())} ), one(T()) ) );

  {
    Utility::HDF5OArchive archive( archive_name, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE );

    // Array optimization should not be used with these types
    FRENSIE_REQUIRE( !(Utility::HDF5OArchive::use_array_optimization::apply<std::pair<T,std::vector<T> > >::type::value) );
    FRENSIE_REQUIRE( !(Utility::HDF5OArchive::use_array_optimization::apply<std::tuple<std::vector<T> ,T> >::type::value) );
    FRENSIE_REQUIRE( !(Utility::HDF5OArchive::use_array_optimization::apply<std::tuple<T,std::vector<T> ,T> >::type::value) );

    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "vector_a", vector_a ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "vector_b", vector_b ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "vector_c", vector_c ) );
  }

  {
    Utility::HDF5IArchive archive( archive_name );

    std::vector<std::pair<T,std::vector<T> > > extracted_vector_a;
    std::vector<std::tuple<std::vector<T> ,T> > extracted_vector_b;
    std::vector<std::tuple<T,std::vector<T> ,T> > extracted_vector_c;

    // Array optimization should not be used with these types
    FRENSIE_REQUIRE( !(Utility::HDF5IArchive::use_array_optimization::apply<std::pair<T,std::vector<T> > >::type::value) );
    FRENSIE_REQUIRE( !(Utility::HDF5IArchive::use_array_optimization::apply<std::tuple<std::vector<T> ,T> >::type::value) );
    FRENSIE_REQUIRE( !(Utility::HDF5IArchive::use_array_optimization::apply<std::tuple<T,std::vector<T> ,T> >::type::value) );

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "vector_a", extracted_vector_a ) );
    FRENSIE_CHECK_EQUAL( extracted_vector_a, vector_a );
    
    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "vector_b", extracted_vector_b ) );
    FRENSIE_CHECK_EQUAL( extracted_vector_b, vector_b );

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "vector_c", extracted_vector_c ) );
    FRENSIE_CHECK_EQUAL( extracted_vector_c, vector_c );
  }
}

//---------------------------------------------------------------------------//
// end tstHDF5ArchiveVector.cpp
//---------------------------------------------------------------------------//
