//---------------------------------------------------------------------------//
//!
//! \file   tstHDF5ArchiveTupleTypes.cpp
//! \author Alex Robinson
//! \brief  HDF5 archive tuple type unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// FRENSIE Includes
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_Tuple.hpp"
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
//---------------------------------------------------------------------------//
// Check that tuple composed of basic types can be archived
FRENSIE_UNIT_TEST_TEMPLATE( HDF5Archive,
                            archive_tuple_basic_types,
                            BasicTupleTestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  std::string archive_name( "test_tuple_basic_types.h5a" );

  const T tuple_a = zero(T());
  const T tuple_b = one(T());

  const T array_a[8] = {one(T()), one(T()), one(T()), one(T()), one(T()), one(T()), one(T()), one(T())};
  const T array_b[2][3] = {{one(T()), one(T()), one(T())},{one(T()), one(T()), one(T())}};
  std::array<T,10> array_c;
  array_c.fill( one(T()) );
  
  {
    Utility::HDF5OArchive archive( archive_name, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE );

    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "tuple_a", tuple_a ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "tuple_b", tuple_b ) );
    
    // Array optimization should be used with this type
    FRENSIE_REQUIRE( Utility::HDF5OArchive::use_array_optimization::apply<T>::type::value );

    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "array_a", array_a ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "array_b", array_b ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "array_c", array_c ) );
  }

  {
    Utility::HDF5IArchive archive( archive_name );

    T extracted_tuple;
    T extracted_array_a[8];
    T extracted_array_b[2][3];
    std::array<T,10> extracted_array_c;

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "tuple_a", extracted_tuple ) );
    FRENSIE_CHECK_EQUAL( extracted_tuple, tuple_a );

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "tuple_b", extracted_tuple ) );
    FRENSIE_CHECK_EQUAL( extracted_tuple, tuple_b );

    // Array optimization should be used with this type
    FRENSIE_REQUIRE( Utility::HDF5IArchive::use_array_optimization::apply<T>::type::value );

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "array_a", extracted_array_a ) );
    FRENSIE_CHECK_EQUAL( Utility::ArrayView<const T>( array_a, array_a+8 ),
                         Utility::ArrayView<const T>( extracted_array_a, extracted_array_a+8 ) );
    
    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "array_b", extracted_array_b ) );
    FRENSIE_CHECK_EQUAL( Utility::ArrayView<const T>( &array_b[0][0], &array_b[0][0]+6 ),
                         Utility::ArrayView<const T>( &extracted_array_b[0][0], &extracted_array_b[0][0]+6 ) );
    
    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "array_c", extracted_array_c ) );
    FRENSIE_CHECK_EQUAL( array_c, extracted_array_c );
  }
}

//---------------------------------------------------------------------------//
// Check that tuple composed of advanced types can be archived
FRENSIE_UNIT_TEST_TEMPLATE( HDF5Archive,
                            archive_tuple_advanced_types,
                            BasicTestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  std::string archive_name( "test_tuple_advanced_types.h5a" );

  const std::pair<T,std::string> pair_a =
    std::make_pair( one(T()), std::string("Test message a") );
  const std::pair<std::string,T> pair_b =
    std::make_pair( std::string("Test message b"), one(T()) );
  const std::pair<std::string,std::string> pair_c =
    std::make_pair( std::string("Test message c-0"), std::string("Test message c-1") );
  
  const std::tuple<T,std::string> tuple_a =
    std::make_tuple( one(T()), std::string("Test message a") );
  const std::tuple<std::string,T> tuple_b =
    std::make_tuple( std::string("Test message b"), one(T()) );
  const std::tuple<std::string,std::string> tuple_c =
    std::make_tuple( std::string("Test message c-0"), std::string("Test message c-1") );

  const std::pair<T,std::string> array_a[2][3] =
    {{std::make_pair(one(T()), std::string("Test message a-00")),
      std::make_pair(one(T()), std::string("Test message a-01")),
      std::make_pair(one(T()), std::string("Test message a-02"))},
     {std::make_pair(zero(T()), std::string("Test message a-10")),
      std::make_pair(zero(T()), std::string("Test message a-11")),
      std::make_pair(zero(T()), std::string("Test message a-12"))}};

  const std::tuple<std::string,T> array_b[6] =
    {std::make_tuple(std::string("Test message b-00"), zero(T())),
     std::make_tuple(std::string("Test message b-01"), zero(T())),
     std::make_tuple(std::string("Test message b-02"), zero(T())),
     std::make_tuple(std::string("Test message b-10"), one(T())),
     std::make_tuple(std::string("Test message b-11"), one(T())),
     std::make_tuple(std::string("Test message b-12"), one(T()))};
  
  {
    Utility::HDF5OArchive archive( archive_name, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE );
    
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "pair_a", pair_a ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "pair_b", pair_b ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "pair_c", pair_c ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "tuple_a", tuple_a ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "tuple_b", tuple_b ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "tuple_c", tuple_c ) );

    // Array optimization should be used with these types
    FRENSIE_REQUIRE( (Utility::HDF5OArchive::use_array_optimization::apply<std::pair<T,std::string> >::type::value) );
    FRENSIE_REQUIRE( (Utility::HDF5OArchive::use_array_optimization::apply<std::tuple<std::string,T> >::type::value) );
  
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "array_a", array_a ) );
    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "array_b", array_b ) );
  }

  {
    Utility::HDF5IArchive archive( archive_name );

    std::pair<T,std::string> extracted_pair_a;
    std::pair<std::string,T> extracted_pair_b;
    std::pair<std::string,std::string> extracted_pair_c;

    std::tuple<T,std::string> extracted_tuple_a;
    std::tuple<std::string,T> extracted_tuple_b;
    std::tuple<std::string,std::string> extracted_tuple_c;

    std::pair<T,std::string> extracted_array_a[2][3];

    std::tuple<std::string,T> extracted_array_b[6];
  
    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "pair_a", extracted_pair_a ) );
    FRENSIE_CHECK_EQUAL( extracted_pair_a, pair_a );

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "pair_b", extracted_pair_b ) );
    FRENSIE_CHECK_EQUAL( extracted_pair_b, pair_b );

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "pair_c", extracted_pair_c ) );
    FRENSIE_CHECK_EQUAL( extracted_pair_c, pair_c );

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "tuple_a", extracted_tuple_a ) );
    FRENSIE_CHECK_EQUAL( extracted_tuple_a, tuple_a );

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "tuple_b", extracted_tuple_b ) );
    FRENSIE_CHECK_EQUAL( extracted_tuple_b, tuple_b );

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "tuple_c", extracted_tuple_c ) );
    FRENSIE_CHECK_EQUAL( extracted_tuple_c, tuple_c );

    // Array optimization should not be used with these types
    FRENSIE_REQUIRE( (Utility::HDF5IArchive::use_array_optimization::apply<std::pair<T,std::string> >::type::value) );
    FRENSIE_REQUIRE( (Utility::HDF5IArchive::use_array_optimization::apply<std::tuple<std::string,T> >::type::value) );
  
    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "array_a", extracted_array_a ) );
    FRENSIE_CHECK_EQUAL( (Utility::ArrayView<const std::pair<T,std::string> >( &array_a[0][0], &array_a[0][0]+6 )),
                         (Utility::ArrayView<const std::pair<T,std::string> >( &extracted_array_a[0][0], &extracted_array_a[0][0]+6 )) );
    
    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "array_b", extracted_array_b ) );
    FRENSIE_CHECK_EQUAL( (Utility::ArrayView<const std::tuple<std::string,T> >( array_b, array_b+6 )),
                         (Utility::ArrayView<const std::tuple<std::string,T> >( extracted_array_b, extracted_array_b+6 )) );
  }
}

//---------------------------------------------------------------------------//
// end  tstHDF5ArchiveTupleTypes.cpp
//---------------------------------------------------------------------------//
