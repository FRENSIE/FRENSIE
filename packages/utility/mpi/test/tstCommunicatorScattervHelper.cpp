//---------------------------------------------------------------------------//
//!
//! \file   tstCommunicatorScattervHelper.cpp
//! \author Alex Robinson
//! \brief  Communicator scatterv helper function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <utility>

// FRENSIE Includes
#include "Utility_Communicator.hpp"
#include "Utility_GlobalMPISession.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_Array.hpp"
#include "Utility_Vector.hpp"
#include "Utility_List.hpp"
#include "Utility_Set.hpp"
#include "Utility_Map.hpp"
#include "Utility_TypeTraits.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

/*! NOTE: Due to scatterv changes introduced in boost 1.72, 
 *  anything involving scatterv does not function properly 
 * at the moment and its tests are disabled. If you require
 * scatterv, please find the bug, fix it, and submit it for
 * a pull request. This test will not run until the bug is fixed.
 *  \ingroup mpi
 */

//---------------------------------------------------------------------------//
// Template Types
//---------------------------------------------------------------------------//
typedef std::tuple<char, unsigned char,
                   short, unsigned short,
                   int, unsigned int,
                   long, unsigned long,
                   long long, unsigned long long,
                   float, double,
                   std::string,
                   std::pair<float,int>, std::tuple<float,int>,
                   std::pair<double,int>, std::tuple<double,int>,
                   std::pair<long,int>, std::tuple<long,int>,
                   std::pair<int,int>, std::tuple<int,int>,
                   std::pair<short,int>, std::tuple<short,int> > BasicTypesNoBool;

typedef decltype(std::tuple_cat( BasicTypesNoBool(), std::tuple<bool>())) BasicTypes;

typedef std::tuple<bool,char,short,int,long,long long,double,std::string,std::pair<float,int>, std::tuple<float,int> > BasicTypesSubset;
typedef std::tuple<char,int,double> BasicTypesMinSubset;

template<typename T>
struct SequenceContainerList
{
  typedef std::tuple<std::array<T,10>,
                     std::vector<T>,
                     std::list<T>,
                     std::forward_list<T>,
                     std::deque<T> > type;
};

template<typename T, typename Enabled = void>
struct SetList;

template<typename T>
struct SetList<T,typename std::enable_if<Utility::IsHashable<T>::value>::type>
{
  typedef std::tuple<std::set<T>,std::unordered_set<T> > type;
};

template<typename T>
struct SetList<T,typename std::enable_if<!Utility::IsHashable<T>::value>::type>
{
  typedef std::tuple<> type;
};

template<typename T, typename Enabled = void>
struct MapList;

template<typename T>
struct MapList<T,typename std::enable_if<Utility::IsHashable<T>::value>::type>
{
  typedef std::tuple<std::map<T,T>,std::unordered_map<T,T> > type;
};

template<typename T>
struct MapList<T,typename std::enable_if<!Utility::IsHashable<T>::value>::type>
{
  typedef std::tuple<> type;
};

template<typename... Types>
struct MergeContainerLists;

template<typename T, typename... Types>
struct MergeContainerLists<T,Types...>
{
  typedef decltype(std::tuple_cat( typename MergeContainerLists<T>::type(),
                                   typename MergeContainerLists<Types...>::type() )) type;
};

template<typename T>
struct MergeContainerLists<T>
{
  typedef decltype(std::tuple_cat( typename SequenceContainerList<T>::type(),
                                   typename SetList<T>::type(),
                                   typename MapList<T>::type() )) type;
};

template<typename... Types>
struct MergeContainerLists<std::tuple<Types...> > : public MergeContainerLists<Types...>
{ /* ... */ };

typedef typename MergeContainerLists<BasicTypesSubset>::type ContainerTypes;
typedef typename MergeContainerLists<BasicTypesMinSubset>::type ContainerTypesSubset;

typedef decltype(std::tuple_cat(BasicTypes(), ContainerTypes())) Types;
typedef decltype(std::tuple_cat(BasicTypesNoBool(), ContainerTypes())) TypesNoBool;
typedef decltype(std::tuple_cat(BasicTypes(), ContainerTypesSubset())) TypesSubset;

//---------------------------------------------------------------------------//
// Testing functions
//---------------------------------------------------------------------------//
template<typename T>
inline T initializeValue( T, int i )
{ return T(i); }

inline bool initializeValue( bool, int i )
{ return (i%2 == 0 ? true : false); }

inline char initializeValue( char, int i )
{ return 48+i; }

inline unsigned char initializeValue( unsigned char, int i )
{ return 48+i; }

inline std::string initializeValue( std::string, int i )
{ return Utility::toString(i); }

template<typename T1, typename T2>
inline std::pair<T1,T2> initializeValue( std::pair<T1,T2>, int i )
{
  return std::make_pair( initializeValue( T1(), i ),
                         initializeValue( T2(), i ) );
}

template<typename... Types>
inline std::tuple<Types...> initializeValue( std::tuple<Types...>, int i )
{
  return std::make_tuple( initializeValue<Types>( Types(), i )... );
}

template<template<typename,typename...> class SequenceContainer,
         typename T>
inline SequenceContainer<T> initializeValue( SequenceContainer<T>, int i )
{
  return SequenceContainer<T>( 10, initializeValue( T(), i ) );
}

template<typename T, size_t N>
inline std::array<T,N> initializeValue( std::array<T,N>, int i )
{
  std::array<T,N> container;
  container.fill( initializeValue( T(), i ) );

  return container;
}

template<template<typename,typename...> class Set, typename T>
inline void fillSet( Set<T>& container, const int seed )
{
  size_t size = 10;
  
  for( size_t i = 0; i < size; ++i )
    container.insert( initializeValue( T(), seed*size+i ) );
}

template<typename T>
inline std::set<T> initializeValue( std::set<T>, int i )
{
  std::set<T> container;
  fillSet( container, i );
  return container;
}

template<typename T>
inline std::unordered_set<T> initializeValue( std::unordered_set<T>, int i )
{
  std::unordered_set<T> container;
  fillSet( container, i );
  return container;
}

template<template<typename,typename,typename...> class Map,
         typename Key, typename T>
inline void fillMap( Map<Key,T>& container, const int seed )
{
  size_t size = 10;
  
  for( size_t i = 0; i < size; ++i )
    container.insert( initializeValue( std::pair<const Key,T>(), seed*size+i ) );
}

template<typename Key, typename T>
inline std::map<Key,T> initializeValue( std::map<Key,T>, int i )
{
  std::map<Key,T> container;
  fillMap( container, i );
  return container;
}

template<typename Key, typename T>
inline std::unordered_map<Key,T> initializeValue( std::unordered_map<Key,T>, int i )
{
  std::unordered_map<Key,T> container;
  fillMap( container, i );
  return container;
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a scatterv operation can be conducted - single value per proc
FRENSIE_UNIT_TEST_TEMPLATE( Communicator, scatterv_single_value, Types )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  T scattered_values[4] = {initializeValue( T(), 0 ),
                           initializeValue( T(), 0 ),
                           initializeValue( T(), 0 ),
                           initializeValue( T(), 0 )};

  if( comm->rank() == 0 )
  {
    std::vector<int> sizes( comm->size(), 1 );
    
    T values[comm->size()];

    for( int i = 0; i < comm->size(); ++i )
      values[i] = initializeValue( T(), i );

    Utility::ArrayView<T> values_view( values, comm->size() );
    Utility::ArrayView<const T> values_view_of_const = values_view.toConst();

    // Scatter using a view lvalue
    FRENSIE_REQUIRE_NO_THROW( Utility::scatterv( *comm, values_view, sizes, Utility::ArrayView<T>(scattered_values, 1), 0 ) );
    
    // Scatter using a view-of-const lvalue
    FRENSIE_REQUIRE_NO_THROW( Utility::scatterv( *comm, values_view_of_const, sizes, Utility::ArrayView<T>(scattered_values+1, 1), 0 ) );

    // Scatter using a view rvalue
    FRENSIE_REQUIRE_NO_THROW( Utility::scatterv( *comm, Utility::ArrayView<T>( values, comm->size() ), sizes, Utility::ArrayView<T>(scattered_values+2, 1), 0 ) );

    // Scatter using a view-of-const rvalues
    FRENSIE_REQUIRE_NO_THROW( Utility::scatterv( *comm, Utility::ArrayView<const T>( values, comm->size() ), sizes, Utility::ArrayView<T>(scattered_values+3, 1), 0 ) );
  }
  else
  {
    Utility::ArrayView<T> dummy_view;
    Utility::ArrayView<const T> dummy_view_of_const;
    std::vector<int> dummy_sizes;
    
    FRENSIE_REQUIRE_NO_THROW( Utility::scatterv( *comm, dummy_view, dummy_sizes, Utility::ArrayView<T>(scattered_values, 1), 0 ) );
    FRENSIE_REQUIRE_NO_THROW( Utility::scatterv( *comm, dummy_view_of_const, dummy_sizes, Utility::ArrayView<T>(scattered_values+1, 1), 0 ) );
    FRENSIE_REQUIRE_NO_THROW( Utility::scatterv( *comm, Utility::ArrayView<T>(), dummy_sizes, Utility::ArrayView<T>(scattered_values+2, 1), 0 ) );
    FRENSIE_REQUIRE_NO_THROW( Utility::scatterv( *comm, Utility::ArrayView<const T>(), dummy_sizes, Utility::ArrayView<T>(scattered_values+3, 1), 0 ) );
  }

  const T expected_scattered_values[4] = {initializeValue( T(), comm->rank() ),
                                          initializeValue( T(), comm->rank() ),
                                          initializeValue( T(), comm->rank() ),
                                          initializeValue( T(), comm->rank() )};

  Utility::ArrayView<const T> scattered_values_view( scattered_values, 4 );
  Utility::ArrayView<const T> expected_scattered_values_view( expected_scattered_values, 4 );
  FRENSIE_CHECK_EQUAL( scattered_values_view, expected_scattered_values_view );

  if( comm->size() > 1 )
  {
    scattered_values[0] = initializeValue( T(), 0 );
    scattered_values[1] = initializeValue( T(), 0 );
    scattered_values[2] = initializeValue( T(), 0 );
    scattered_values[3] = initializeValue( T(), 0 );
    
    if( comm->rank() == 1 )
    {
      std::vector<int> sizes( comm->size(), 1 );
      T values[comm->size()];

      for( int i = 0; i < comm->size(); ++i )
        values[i] = initializeValue( T(), i );

      Utility::ArrayView<T> values_view( values, comm->size() );
      Utility::ArrayView<const T> values_view_of_const = values_view.toConst();

      // Scatter using a view lvalue
      FRENSIE_REQUIRE_NO_THROW( Utility::scatterv( *comm, values_view, sizes, Utility::ArrayView<T>(scattered_values, 1), 1 ) );
      
      // Scatter using a view-of-const lvalue
      FRENSIE_REQUIRE_NO_THROW( Utility::scatterv( *comm, values_view_of_const, sizes, Utility::ArrayView<T>(scattered_values+1, 1), 1 ) );
      
      // Scatter using a view rvalue
      FRENSIE_REQUIRE_NO_THROW( Utility::scatterv( *comm, Utility::ArrayView<T>( values, comm->size() ), sizes, Utility::ArrayView<T>(scattered_values+2, 1), 1 ) );
      
      // Scatter using a view-of-const rvalues
      FRENSIE_REQUIRE_NO_THROW( Utility::scatterv( *comm, Utility::ArrayView<const T>( values, comm->size() ), sizes, Utility::ArrayView<T>(scattered_values+3, 1), 1 ) );
    }
    else
    {
      FRENSIE_REQUIRE_NO_THROW( Utility::scatterv( *comm, Utility::ArrayView<T>(), std::vector<int>(), Utility::ArrayView<T>(scattered_values, 1), 1 ) );
      FRENSIE_REQUIRE_NO_THROW( Utility::scatterv( *comm, Utility::ArrayView<const T>(), std::vector<int>(), Utility::ArrayView<T>(scattered_values+1, 1), 1 ) );
      FRENSIE_REQUIRE_NO_THROW( Utility::scatterv( *comm, Utility::ArrayView<T>(scattered_values+2, 1), 1 ) );
      FRENSIE_REQUIRE_NO_THROW( Utility::scatterv( *comm, Utility::ArrayView<T>(scattered_values+3, 1), 1 ) );
    }

    FRENSIE_CHECK_EQUAL( scattered_values_view, expected_scattered_values_view );
  }
}

//---------------------------------------------------------------------------//
// Check that a scatterv operation can be conducted - variable values per proc
FRENSIE_UNIT_TEST_TEMPLATE( Communicator, scatterv_multiple_values, TypesNoBool )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  std::vector<T> scattered_values, values;
  Utility::ArrayView<T> values_view;
  Utility::ArrayView<const T> values_view_of_const;
  
  std::vector<int> sizes;

  if( comm->rank() == 0 )
  {
    for( int i = 0; i < comm->size(); ++i )
      sizes.push_back( i+1 );

    for( int i = 0; i < comm->size(); ++i )
    {
      for( int j = 0; j < i+1; ++j )
        values.push_back( initializeValue( T(), i ) );
    }

    values_view = Utility::arrayView( values );
    values_view_of_const = values_view.toConst();
  }

  // Scatter using a view lvalue
  FRENSIE_REQUIRE_NO_THROW( Utility::scatterv( *comm, values_view, sizes, scattered_values, 0 ) );
  FRENSIE_CHECK_EQUAL( scattered_values,
                       std::vector<T>( comm->rank()+1, initializeValue(T(), comm->rank()) ) );

  scattered_values.clear();
    
  // Scatter using a view-of-const lvalue
  FRENSIE_REQUIRE_NO_THROW( Utility::scatterv( *comm, values_view_of_const, sizes, scattered_values, 0 ) );
  FRENSIE_CHECK_EQUAL( scattered_values,
                       std::vector<T>( comm->rank()+1, initializeValue(T(), comm->rank()) ) );

  scattered_values.clear();

  // Scatter using a view rvalue
  FRENSIE_REQUIRE_NO_THROW( Utility::scatterv( *comm, Utility::ArrayView<T>( values ), sizes, scattered_values, 0 ) );
  FRENSIE_CHECK_EQUAL( scattered_values,
                       std::vector<T>( comm->rank()+1, initializeValue(T(), comm->rank()) ) );

  scattered_values.clear();

  // Scatter using a view-of-const rvalues
  FRENSIE_REQUIRE_NO_THROW( Utility::scatterv( *comm, Utility::ArrayView<const T>( values ), sizes, scattered_values, 0 ) );
  FRENSIE_CHECK_EQUAL( scattered_values,
                       std::vector<T>( comm->rank()+1, initializeValue(T(), comm->rank()) ) );

  scattered_values.clear();
  values.clear();
  sizes.clear();

  if( comm->size() > 1 )
  {
    if( comm->rank() == 1 )
    {
      for( int i = 0; i < comm->size(); ++i )
        sizes.push_back( i+1 );

      for( int i = 0; i < comm->size(); ++i )
      {
        for( int j = 0; j < i+1; ++j )
          values.push_back( initializeValue( T(), i ) );
      }

      values_view = Utility::arrayView( values );
      values_view_of_const = values_view.toConst();

      // Scatter using a view lvalue
      FRENSIE_REQUIRE_NO_THROW( Utility::scatterv( *comm, values_view, sizes, scattered_values, 1 ) );
      FRENSIE_CHECK_EQUAL( scattered_values,
                           std::vector<T>( 2, initializeValue(T(), 1) ) );

      scattered_values.clear();
    
      // Scatter using a view-of-const lvalue
      FRENSIE_REQUIRE_NO_THROW( Utility::scatterv( *comm, values_view_of_const, sizes, scattered_values, 1 ) );
      FRENSIE_CHECK_EQUAL( scattered_values,
                           std::vector<T>( 2, initializeValue(T(), 1) ) );

      scattered_values.clear();
      
      // Scatter using a view rvalue
      FRENSIE_REQUIRE_NO_THROW( Utility::scatterv( *comm, Utility::ArrayView<T>( values ), sizes, scattered_values, 1 ) );
      FRENSIE_CHECK_EQUAL( scattered_values,
                           std::vector<T>( 2, initializeValue(T(), 1) ) );
      
      scattered_values.clear();

      // Scatter using a view-of-const rvalues
      FRENSIE_REQUIRE_NO_THROW( Utility::scatterv( *comm, Utility::ArrayView<const T>( values ), sizes, scattered_values, 1 ) );
      FRENSIE_CHECK_EQUAL( scattered_values,
                           std::vector<T>( 2, initializeValue(T(), 1) ) );
    }
    else
    {
      // Scatter using a view lvalue
      FRENSIE_REQUIRE_NO_THROW( Utility::scatterv( *comm, scattered_values, 1 ) );
      FRENSIE_CHECK_EQUAL( scattered_values,
                           std::vector<T>( comm->rank()+1, initializeValue(T(), comm->rank()) ) );

      scattered_values.clear();
    
      // Scatter using a view-of-const lvalue
      FRENSIE_REQUIRE_NO_THROW( Utility::scatterv( *comm, scattered_values, 1 ) );
      FRENSIE_CHECK_EQUAL( scattered_values,
                           std::vector<T>( comm->rank()+1, initializeValue(T(), comm->rank()) ) );

      scattered_values.clear();

      // Scatter using a view rvalue
      FRENSIE_REQUIRE_NO_THROW( Utility::scatterv( *comm, scattered_values, 1 ) );
      FRENSIE_CHECK_EQUAL( scattered_values,
                           std::vector<T>( comm->rank()+1, initializeValue(T(), comm->rank()) ) );

      scattered_values.clear();

      // Scatter using a view-of-const rvalues
      FRENSIE_REQUIRE_NO_THROW( Utility::scatterv( *comm, scattered_values, 1 ) );
      FRENSIE_CHECK_EQUAL( scattered_values,
                           std::vector<T>( comm->rank()+1, initializeValue(T(), comm->rank()) ) );
    }
  }
}

//---------------------------------------------------------------------------//
// end tstCommunicatorScattervHelper.cpp
//---------------------------------------------------------------------------//
