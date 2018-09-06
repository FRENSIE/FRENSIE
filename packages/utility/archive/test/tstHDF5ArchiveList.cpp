//---------------------------------------------------------------------------//
//!
//! \file   tstHDF5ArchiveList.cpp
//! \author Alex Robinson
//! \brief  HDF5 archive list unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// FRENSIE Includes
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_List.hpp"
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
// Check that lists of basic types can be archived
FRENSIE_UNIT_TEST_TEMPLATE( HDF5Archive,
                            archive_list_basic_types,
                            AllBasicTestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  std::string archive_name( "test_list_basic_types.h5a" );

  std::list<T> list( 10, one(T()) );

  {
    Utility::HDF5OArchive archive( archive_name, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE );

    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "list", list ) );
  }

  {
    Utility::HDF5IArchive archive( archive_name );

    std::list<T> extracted_list;

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "list", extracted_list ) );
    FRENSIE_CHECK_EQUAL( list, extracted_list );
  }
}

//---------------------------------------------------------------------------//
// Check that a list of strings can be archived
FRENSIE_UNIT_TEST( HDF5Archive, archive_list_string )
{
  std::string archive_name( "test_list_string.h5a" );

  std::list<std::string> list_a( 5, std::string("Test message a") );

  std::list<std::tuple<std::string> > list_b( 10, std::make_tuple(std::string("Test message b")) );
  
  std::list<std::pair<std::string,std::string> > list_c( 10, std::make_pair(std::string("Test message c-0"), std::string("Test message c-1")) );

  std::list<std::tuple<std::string,std::string,std::string> > list_d( 20, std::make_tuple(std::string("Test message d-0"), std::string("Test message d-1"), std::string("Test message d-2")) );

  {
    Utility::HDF5OArchive archive( archive_name, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE );

    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "list_a", list_a ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "list_b", list_b ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "list_c", list_c ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "list_d", list_d ) );
  }

  {
    Utility::HDF5IArchive archive( archive_name );

    std::list<std::string> extracted_list_a;
    std::list<std::tuple<std::string> > extracted_list_b;
    std::list<std::pair<std::string,std::string> > extracted_list_c;
    std::list<std::tuple<std::string,std::string,std::string> > extracted_list_d;

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "list_a", extracted_list_a ) );
    FRENSIE_CHECK_EQUAL( extracted_list_a, list_a );

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "list_b", extracted_list_b ) );
    FRENSIE_CHECK_EQUAL( extracted_list_b, list_b );

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "list_c", extracted_list_c ) );
    FRENSIE_CHECK_EQUAL( extracted_list_c, list_c );

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "list_d", extracted_list_d ) );
    FRENSIE_CHECK_EQUAL( extracted_list_d, list_d );
  }
}

//---------------------------------------------------------------------------//
// Check that lists of advanced types can be archived
FRENSIE_UNIT_TEST_TEMPLATE( HDF5Archive,
                            archive_list_advanced_types,
                            BasicTestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  std::string archive_name( "test_list_advanced_types.h5a" );
  
  std::list<std::pair<T,std::string> > list_a( 10, std::make_pair( one(T()), std::string("Test message a-1") ) );

  std::list<std::tuple<std::string,T> > list_b( 10, std::make_tuple( std::string("Test message b-0"), one(T()) ) );

  std::list<std::tuple<T,std::string,T> > list_c( 20, std::make_tuple( zero(T()), std::string("Test message c-1"), one(T()) ) );

  {
    Utility::HDF5OArchive archive( archive_name, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE );

    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "list_a", list_a ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "list_b", list_b ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "list_c", list_c ) );
  }

  {
    Utility::HDF5IArchive archive( archive_name );

    std::list<std::pair<T,std::string> > extracted_list_a;
    std::list<std::tuple<std::string,T> > extracted_list_b;
    std::list<std::tuple<T,std::string,T> > extracted_list_c;

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "list_a", extracted_list_a ) );
    FRENSIE_CHECK_EQUAL( extracted_list_a, list_a );
    
    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "list_b", extracted_list_b ) );
    FRENSIE_CHECK_EQUAL( extracted_list_b, list_b );

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "list_c", extracted_list_c ) );
    FRENSIE_CHECK_EQUAL( extracted_list_c, list_c );
  }
}

//---------------------------------------------------------------------------//
// end tstHDF5ArchiveList.cpp
//---------------------------------------------------------------------------//
