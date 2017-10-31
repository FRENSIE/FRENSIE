//---------------------------------------------------------------------------//
//!
//! \file   tstCommunicatorGathervHelper.cpp
//! \author Alex Robinson
//! \brief  Communicator gatherv helper function unit tests
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
                   std::pair<short,int>, std::tuple<short,int> > BasicTypes;

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
typedef decltype(std::tuple_cat(BasicTypes(), ContainerTypesSubset())) TypesSubset;

//---------------------------------------------------------------------------//
// Testing functions
//---------------------------------------------------------------------------//
template<typename T>
inline T initializeValue( T, int i )
{ return T(i); }

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
// Check that a gatherv operation can be conducted - single value, vector of
// gathered values exists on all procs
FRENSIE_UNIT_TEST_TEMPLATE( Communicator, gatherv_single_value_vector, Types )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  const T value = initializeValue( T(), comm->rank() );

  std::vector<T> gathered_values;
  
  FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, value, gathered_values, 0 ) );
  
  if( comm->rank() == 0 )
  {
    FRENSIE_REQUIRE_EQUAL( gathered_values.size(), comm->size() );
    
    std::vector<T> expected_gathered_values( comm->size() );
    
    for( int i = 0; i < comm->size(); ++i )
      expected_gathered_values[i] = initializeValue( T(), i );
    
    FRENSIE_CHECK_EQUAL( gathered_values, expected_gathered_values );
  }
  else
  {
    FRENSIE_REQUIRE_EQUAL( gathered_values.size(), 0 );
  }

  if( comm->size() > 1 )
  {
    gathered_values.clear();
    
    FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, value, gathered_values, 1 ) );
    
    if( comm->rank() == 1 )
    {
      FRENSIE_REQUIRE_EQUAL( gathered_values.size(), comm->size() );
      
      std::vector<T> expected_gathered_values( comm->size() );
      
      for( int i = 0; i < comm->size(); ++i )
        expected_gathered_values[i] = initializeValue( T(), i );
      
      FRENSIE_CHECK_EQUAL( gathered_values, expected_gathered_values );
    }
    else
    {
      FRENSIE_REQUIRE_EQUAL( gathered_values.size(), 0 );
    }
  }
}

//---------------------------------------------------------------------------//
// Check that a gatherv operation can be conducted - single value, vector of
// gathered values exists on root proc only
FRENSIE_UNIT_TEST_TEMPLATE( Communicator, gatherv_single_value_root_vector, TypesSubset )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  const T value = initializeValue( T(), comm->rank() );
  
  if( comm->rank() == 0 )
  {
    std::vector<T> gathered_values;

    FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, value, gathered_values, 0 ) );
    FRENSIE_REQUIRE_EQUAL( gathered_values.size(), comm->size() );
    
    std::vector<T> expected_gathered_values( comm->size() );
    
    for( int i = 0; i < comm->size(); ++i )
      expected_gathered_values[i] = initializeValue( T(), i );
    
    FRENSIE_CHECK_EQUAL( gathered_values, expected_gathered_values );
  }
  else
  {
    FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, value, 0 ) );
  }

  if( comm->size() > 1 )
  {
    if( comm->rank() == 1 )
    {
      std::vector<T> gathered_values;
      
      FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, value, gathered_values, 1 ) );
      FRENSIE_REQUIRE_EQUAL( gathered_values.size(), comm->size() );
      
      std::vector<T> expected_gathered_values( comm->size() );
      
      for( int i = 0; i < comm->size(); ++i )
        expected_gathered_values[i] = initializeValue( T(), i );
      
      FRENSIE_CHECK_EQUAL( gathered_values, expected_gathered_values );
    }
    else
    {
      FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, value, 1 ) );
    }
  }
}

//---------------------------------------------------------------------------//
// Check that a gatherv operation can be conducted - single bool value, view
// of gathered bool values exists on all procs
FRENSIE_UNIT_TEST( Communicator, gatherv_single_value_view_bool )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  const bool value = (comm->rank()%2 == 0 ? true : false);

  bool gathered_values[comm->size()];
  
  FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, value, Utility::ArrayView<bool>( gathered_values, comm->size() ), 0 ) );
  
  if( comm->rank() == 0 )
  {
    bool expected_gathered_values[comm->size()];
    
    for( int i = 0; i < comm->size(); ++i )
      expected_gathered_values[i] = (i%2 == 0 ? true : false);
    
    FRENSIE_CHECK_EQUAL( Utility::ArrayView<const bool>(gathered_values, comm->size() ),
                         Utility::ArrayView<const bool>(expected_gathered_values, comm->size() ) );
  }
  
  if( comm->size() > 1 )
  {
    Utility::ArrayView<bool> gathered_values_view( gathered_values, comm->size() );
    gathered_values_view.fill( false );
    
    FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, value, gathered_values_view, 1 ) );
    
    if( comm->rank() == 1 )
    {
      bool expected_gathered_values[comm->size()];
    
      for( int i = 0; i < comm->size(); ++i )
        expected_gathered_values[i] = (i%2 == 0 ? true : false);
      
      FRENSIE_CHECK_EQUAL( gathered_values_view,
                           Utility::ArrayView<const bool>(expected_gathered_values, comm->size() ) );
    }
  }
}

//---------------------------------------------------------------------------//
// Check that a gatherv operation can be conducted - single value, view of
// gathered values exists on all procs
FRENSIE_UNIT_TEST_TEMPLATE( Communicator, gatherv_single_value_view, Types )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  const T value = initializeValue( T(), comm->rank() );

  std::vector<T> gathered_values( comm->size() );
  
  FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, value, Utility::arrayView(gathered_values), 0 ) );
  
  if( comm->rank() == 0 )
  {
    FRENSIE_REQUIRE_EQUAL( gathered_values.size(), comm->size() );
    
    std::vector<T> expected_gathered_values( comm->size() );
    
    for( int i = 0; i < comm->size(); ++i )
      expected_gathered_values[i] = initializeValue( T(), i );
    
    FRENSIE_CHECK_EQUAL( gathered_values, expected_gathered_values );
  }

  if( comm->size() > 1 )
  {
    gathered_values.clear();
    gathered_values.resize( comm->size() );
    Utility::ArrayView<T> gathered_values_view( gathered_values );
    
    FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, value, gathered_values_view, 1 ) );
    
    if( comm->rank() == 1 )
    {
      FRENSIE_REQUIRE_EQUAL( gathered_values.size(), comm->size() );
      
      std::vector<T> expected_gathered_values( comm->size() );
      
      for( int i = 0; i < comm->size(); ++i )
        expected_gathered_values[i] = initializeValue( T(), i );
      
      FRENSIE_CHECK_EQUAL( gathered_values, expected_gathered_values );
    }
  }
}

//---------------------------------------------------------------------------//
// Check that a gatherv operation can be conducted - single value, view of
// gathered values exists on root proc only
FRENSIE_UNIT_TEST_TEMPLATE( Communicator, gatherv_single_value_root_view, TypesSubset )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  const T value = initializeValue( T(), comm->rank() );

  if( comm->rank() == 0 )
  {
    std::vector<T> gathered_values( comm->size() );

    // Use a view rvalue
    FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, value, Utility::arrayView(gathered_values), 0 ) );
        
    std::vector<T> expected_gathered_values( comm->size() );
    
    for( int i = 0; i < comm->size(); ++i )
      expected_gathered_values[i] = initializeValue( T(), i );
    
    FRENSIE_CHECK_EQUAL( gathered_values, expected_gathered_values );
  }
  else
  {
    FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, value, 0 ) );
  }

  if( comm->size() > 1 )
  {
    if( comm->rank() == 1 )
    {
      std::vector<T> gathered_values( comm->size() );

      // Use a view lvalue
      Utility::ArrayView<T> gathered_values_view( gathered_values );
      
      FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, value, gathered_values_view, 1 ) );
      
      std::vector<T> expected_gathered_values( comm->size() );
      
      for( int i = 0; i < comm->size(); ++i )
        expected_gathered_values[i] = initializeValue( T(), i );
      
      FRENSIE_CHECK_EQUAL( gathered_values, expected_gathered_values );
    }
    else
    {
      FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, value, 1 ) );
    }
  }
}

//---------------------------------------------------------------------------//
// Check that a gatherv operation can be conducted - multiple values, vector
// of gathered values exists on all procs
FRENSIE_UNIT_TEST_TEMPLATE( Communicator, gatherv_multiple_values_vector, Types )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  const T value = initializeValue( T(), comm->rank() );
  std::vector<T> input_values( comm->rank()+1, value );
  Utility::ArrayView<const T> input_values_view( input_values );

  // Gather an initializer list of values
  std::vector<T> gathered_init_list_values;

  if( comm->rank()%2 == 0 )
  {
    FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, {value, value}, gathered_init_list_values, 0 ) );
  }
  else
  {
    FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, {value, value, value}, gathered_init_list_values, 0 ) );
  }

  // Gather using an array view rvalue
  std::vector<T> gathered_view_rvalue_values;
  FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, Utility::arrayView(input_values), gathered_view_rvalue_values, 0 ) );

  // Gather using an array view of const rvalue
  std::vector<T> gathered_const_view_rvalue_values;
  FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, Utility::arrayViewOfConst(input_values), gathered_const_view_rvalue_values, 0 ) );

  // Gather using an array view lvalue
  std::vector<T> gathered_view_lvalue_values;
  FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, input_values_view, gathered_view_lvalue_values, 0 ) );
  
  if( comm->rank() == 0 )
  {
    FRENSIE_REQUIRE_EQUAL( gathered_init_list_values.size(),
                           (comm->size()%2==0 ? comm->size()*5/2 : (comm->size()-1)*5/2 + 2) );

    std::vector<T> expected_gathered_values;
    
    for( int i = 0; i < comm->size(); ++i )
    {
      for( int j = 0; j < (i%2==0 ? 2 : 3); ++j )
        expected_gathered_values.push_back( initializeValue( T(), i ) );
    }
    
    FRENSIE_CHECK_EQUAL( gathered_init_list_values, expected_gathered_values );

    expected_gathered_values.clear();

    for( int i = 0; i < comm->size(); ++i )
    {
      for( int j = 0; j < i+1; ++j )
        expected_gathered_values.push_back( initializeValue( T(), i ) );
    }
    
    FRENSIE_REQUIRE_EQUAL( gathered_view_rvalue_values.size(),
                           comm->size()*(comm->size()+1)/2 );
    FRENSIE_CHECK_EQUAL( gathered_view_rvalue_values, expected_gathered_values );
    
    FRENSIE_REQUIRE_EQUAL( gathered_const_view_rvalue_values.size(),
                           comm->size()*(comm->size()+1)/2 );
    FRENSIE_CHECK_EQUAL( gathered_const_view_rvalue_values, expected_gathered_values );
    
    FRENSIE_REQUIRE_EQUAL( gathered_view_lvalue_values.size(),
                           comm->size()*(comm->size()+1)/2 );
    FRENSIE_CHECK_EQUAL( gathered_view_lvalue_values, expected_gathered_values );
  }
  else
  {
    FRENSIE_REQUIRE_EQUAL( gathered_init_list_values.size(), 0 );
    FRENSIE_REQUIRE_EQUAL( gathered_view_rvalue_values.size(), 0 );
    FRENSIE_REQUIRE_EQUAL( gathered_const_view_rvalue_values.size(), 0 );
    FRENSIE_REQUIRE_EQUAL( gathered_view_lvalue_values.size(), 0 );
  }

  if( comm->size() > 1 )
  {
    gathered_init_list_values.clear();
    gathered_view_rvalue_values.clear();
    gathered_const_view_rvalue_values.clear();
    gathered_view_lvalue_values.clear();

    if( comm->rank()%2 == 0 )
    {
      FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, {value, value}, gathered_init_list_values, 1 ) );
    }
    else
    {
      FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, {value, value, value}, gathered_init_list_values, 1 ) );
    }

    // Gather using an array view rvalue
    FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, Utility::arrayView(input_values), gathered_view_rvalue_values, 1 ) );

    // Gather using an array view of const rvalue
    FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, Utility::arrayViewOfConst(input_values), gathered_const_view_rvalue_values, 1 ) );

    // Gather using an array view lvalue
    FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, input_values_view, gathered_view_lvalue_values, 1 ) );
  
    if( comm->rank() == 1 )
    {
      FRENSIE_REQUIRE_EQUAL( gathered_init_list_values.size(),
                             (comm->size()%2==0 ? comm->size()*5/2 : (comm->size()-1)*5/2 + 2) );

      std::vector<T> expected_gathered_values;
      
      for( int i = 0; i < comm->size(); ++i )
      {
        for( int j = 0; j < (i%2==0 ? 2 : 3); ++j )
          expected_gathered_values.push_back( initializeValue( T(), i ) );
      }
    
      FRENSIE_CHECK_EQUAL( gathered_init_list_values, expected_gathered_values );

      expected_gathered_values.clear();

      for( int i = 0; i < comm->size(); ++i )
      {
        for( int j = 0; j < i+1; ++j )
          expected_gathered_values.push_back( initializeValue( T(), i ) );
      }
    
      FRENSIE_REQUIRE_EQUAL( gathered_view_rvalue_values.size(),
                             comm->size()*(comm->size()+1)/2 );
      FRENSIE_CHECK_EQUAL( gathered_view_rvalue_values, expected_gathered_values );
    
      FRENSIE_REQUIRE_EQUAL( gathered_const_view_rvalue_values.size(),
                             comm->size()*(comm->size()+1)/2 );
      FRENSIE_CHECK_EQUAL( gathered_const_view_rvalue_values, expected_gathered_values );
      
      FRENSIE_REQUIRE_EQUAL( gathered_view_lvalue_values.size(),
                             comm->size()*(comm->size()+1)/2 );
      FRENSIE_CHECK_EQUAL( gathered_view_lvalue_values, expected_gathered_values );
    }
    else
    {
      FRENSIE_REQUIRE_EQUAL( gathered_init_list_values.size(), 0 );
      FRENSIE_REQUIRE_EQUAL( gathered_view_rvalue_values.size(), 0 );
      FRENSIE_REQUIRE_EQUAL( gathered_const_view_rvalue_values.size(), 0 );
      FRENSIE_REQUIRE_EQUAL( gathered_view_lvalue_values.size(), 0 );
    }
  }
}

//---------------------------------------------------------------------------//
// Check that a gatherv operation can be conducted - multiple values, vector
// of gathered values only exists on root proc
FRENSIE_UNIT_TEST_TEMPLATE( Communicator, gatherv_multiple_values_root_vector, TypesSubset )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  const T value = initializeValue( T(), comm->rank() );
  std::vector<T> input_values( comm->rank()+1, value );
  Utility::ArrayView<const T> input_values_view( input_values );

  if( comm->rank() == 0 )
  {
    // Gather an initializer list of values
    std::vector<T> gathered_init_list_values;
    FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, {value, value}, gathered_init_list_values, 0 ) );

    // Gather using an array view rvalue
    std::vector<T> gathered_view_rvalue_values;
    FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, Utility::arrayView(input_values), gathered_view_rvalue_values, 0 ) );

    // Gather using an array view of const rvalue
    std::vector<T> gathered_const_view_rvalue_values;
    FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, Utility::arrayViewOfConst(input_values), gathered_const_view_rvalue_values, 0 ) );
    
    // Gather using an array view lvalue
    std::vector<T> gathered_view_lvalue_values;
    FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, input_values_view, gathered_view_lvalue_values, 0 ) );

    FRENSIE_REQUIRE_EQUAL( gathered_init_list_values.size(),
                           (comm->size()%2==0 ? comm->size()*5/2 : (comm->size()-1)*5/2 + 2) );

    std::vector<T> expected_gathered_values;
    
    for( int i = 0; i < comm->size(); ++i )
    {
      for( int j = 0; j < (i%2==0 ? 2 : 3); ++j )
        expected_gathered_values.push_back( initializeValue( T(), i ) );
    }
    
    FRENSIE_CHECK_EQUAL( gathered_init_list_values, expected_gathered_values );

    expected_gathered_values.clear();

    for( int i = 0; i < comm->size(); ++i )
    {
      for( int j = 0; j < i+1; ++j )
        expected_gathered_values.push_back( initializeValue( T(), i ) );
    }
    
    FRENSIE_REQUIRE_EQUAL( gathered_view_rvalue_values.size(),
                           comm->size()*(comm->size()+1)/2 );
    FRENSIE_CHECK_EQUAL( gathered_view_rvalue_values, expected_gathered_values );
    
    FRENSIE_REQUIRE_EQUAL( gathered_const_view_rvalue_values.size(),
                           comm->size()*(comm->size()+1)/2 );
    FRENSIE_CHECK_EQUAL( gathered_const_view_rvalue_values, expected_gathered_values );
    
    FRENSIE_REQUIRE_EQUAL( gathered_view_lvalue_values.size(),
                           comm->size()*(comm->size()+1)/2 );
    FRENSIE_CHECK_EQUAL( gathered_view_lvalue_values, expected_gathered_values );
  }
  else
  {
    // Gather an initializer list of values
    if( comm->rank()%2 == 0 )
    {
      FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, {value, value}, 0 ) );
    }
    else
    {
      FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, {value, value, value}, 0 ) );
    }

    // Gather using an array view rvalue
    FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, Utility::arrayView(input_values), 0 ) );

    // Gather using an array view of const rvalue
    FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, Utility::arrayViewOfConst(input_values), 0 ) );
    
    // Gather using an array view lvalue
    FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, input_values_view, 0 ) );
  }

  if( comm->size() > 1 )
  {
    if( comm->rank() == 1 )
    {
      // Gather an initializer list of values
      std::vector<T> gathered_init_list_values;
      FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, {value, value, value}, gathered_init_list_values, 1 ) );

      // Gather using an array view rvalue
      std::vector<T> gathered_view_rvalue_values;
      FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, Utility::arrayView(input_values), gathered_view_rvalue_values, 1 ) );
      
      // Gather using an array view of const rvalue
      std::vector<T> gathered_const_view_rvalue_values;
      FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, Utility::arrayViewOfConst(input_values), gathered_const_view_rvalue_values, 1 ) );
    
      // Gather using an array view lvalue
      std::vector<T> gathered_view_lvalue_values;
      FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, input_values_view, gathered_view_lvalue_values, 1 ) );

      FRENSIE_REQUIRE_EQUAL( gathered_init_list_values.size(),
                             (comm->size()%2==0 ? comm->size()*5/2 : (comm->size()-1)*5/2 + 2) );

      std::vector<T> expected_gathered_values;
      
      for( int i = 0; i < comm->size(); ++i )
      {
        for( int j = 0; j < (i%2==0 ? 2 : 3); ++j )
          expected_gathered_values.push_back( initializeValue( T(), i ) );
      }
    
      FRENSIE_CHECK_EQUAL( gathered_init_list_values, expected_gathered_values );
      
      expected_gathered_values.clear();

      for( int i = 0; i < comm->size(); ++i )
      {
        for( int j = 0; j < i+1; ++j )
          expected_gathered_values.push_back( initializeValue( T(), i ) );
      }
      
      FRENSIE_REQUIRE_EQUAL( gathered_view_rvalue_values.size(),
                             comm->size()*(comm->size()+1)/2 );
      FRENSIE_CHECK_EQUAL( gathered_view_rvalue_values, expected_gathered_values );
      
      FRENSIE_REQUIRE_EQUAL( gathered_const_view_rvalue_values.size(),
                             comm->size()*(comm->size()+1)/2 );
      FRENSIE_CHECK_EQUAL( gathered_const_view_rvalue_values, expected_gathered_values );
      
      FRENSIE_REQUIRE_EQUAL( gathered_view_lvalue_values.size(),
                             comm->size()*(comm->size()+1)/2 );
      FRENSIE_CHECK_EQUAL( gathered_view_lvalue_values, expected_gathered_values );
    }
    else
    {
      // Gather an initializer list of values
      if( comm->rank()%2 == 0 )
      {
        FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, {value, value}, 1 ) );
      }
      else
      {
        FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, {value, value, value}, 1 ) );
      }

      // Gather using an array view rvalue
      FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, Utility::arrayView(input_values), 1 ) );
      
      // Gather using an array view of const rvalue
      FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, Utility::arrayViewOfConst(input_values), 1 ) );
      
      // Gather using an array view lvalue
      FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, input_values_view, 1 ) );
    }
  }
}

//---------------------------------------------------------------------------//
// Check that a gatherv operation can be conducted - multiple values, view
// of gathered values exists on all procs
FRENSIE_UNIT_TEST_TEMPLATE( Communicator, gatherv_multiple_values_view, Types )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  const T value = initializeValue( T(), comm->rank() );
  std::vector<T> input_values( comm->rank()+1, value );
  Utility::ArrayView<const T> input_values_view( input_values );

  // Gather an initializer list of values using a view rvalue
  std::vector<T> gathered_init_list_values( (comm->size()%2==0 ? comm->size()*5/2 : (comm->size()-1)*5/2 + 2) );

  if( comm->rank()%2 == 0 )
  {
    FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, {value, value}, Utility::arrayView(gathered_init_list_values), 0 ) );
  }
  else
  {
    FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, {value, value, value}, Utility::arrayView(gathered_init_list_values), 0 ) );
  }

  // Gather an array view rvalue using a view rvalue
  std::vector<T> gathered_view_rvalue_values( comm->size()*(comm->size()+1)/2 );
  FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, Utility::arrayView(input_values), Utility::arrayView(gathered_view_rvalue_values), 0 ) );

  // Gather an array view of const rvalue using a view rvalue
  std::vector<T> gathered_const_view_rvalue_values( comm->size()*(comm->size()+1)/2 );
  FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, Utility::arrayViewOfConst(input_values), Utility::arrayView(gathered_const_view_rvalue_values), 0 ) );

  // Gather an array view lvalue using a view rvalue
  std::vector<T> gathered_view_lvalue_values( comm->size()*(comm->size()+1)/2 );
  FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, input_values_view, Utility::arrayView(gathered_view_lvalue_values), 0 ) );
  
  if( comm->rank() == 0 )
  {
    std::vector<T> expected_gathered_values;
    
    for( int i = 0; i < comm->size(); ++i )
    {
      for( int j = 0; j < (i%2==0 ? 2 : 3); ++j )
        expected_gathered_values.push_back( initializeValue( T(), i ) );
    }
    
    FRENSIE_CHECK_EQUAL( gathered_init_list_values, expected_gathered_values );

    expected_gathered_values.clear();

    for( int i = 0; i < comm->size(); ++i )
    {
      for( int j = 0; j < i+1; ++j )
        expected_gathered_values.push_back( initializeValue( T(), i ) );
    }
    
    FRENSIE_CHECK_EQUAL( gathered_view_rvalue_values, expected_gathered_values );
    FRENSIE_CHECK_EQUAL( gathered_const_view_rvalue_values, expected_gathered_values );
    FRENSIE_CHECK_EQUAL( gathered_view_lvalue_values, expected_gathered_values );
  }

  if( comm->size() > 1 )
  {
    gathered_init_list_values.clear();
    gathered_view_rvalue_values.clear();
    gathered_const_view_rvalue_values.clear();
    gathered_view_lvalue_values.clear();

    Utility::ArrayView<T> gathered_values_view;
    
    // Gather an initializer list of values using a view lvalue
    gathered_init_list_values.resize( (comm->size()%2==0 ? comm->size()*5/2 : (comm->size()-1)*5/2 + 2) );
    gathered_values_view = Utility::arrayView( gathered_init_list_values );

    if( comm->rank()%2 == 0 )
    {
      FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, {value, value}, gathered_values_view, 1 ) );
    }
    else
    {
      FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, {value, value, value}, gathered_values_view, 1 ) );
    }

    // Gather an array view rvalue using a view lvalue
    gathered_view_rvalue_values.resize( comm->size()*(comm->size()+1)/2 );
    gathered_values_view = Utility::arrayView( gathered_view_rvalue_values );
    
    FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, Utility::arrayView(input_values), gathered_values_view, 1 ) );

    // Gather an array view of const rvalue using a view lvalue
    gathered_const_view_rvalue_values.resize( comm->size()*(comm->size()+1)/2 );
    gathered_values_view = Utility::arrayView( gathered_const_view_rvalue_values );
    FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, Utility::arrayViewOfConst(input_values), gathered_values_view, 1 ) );

    // Gather an array view lvalue using a view lvalue
    gathered_view_lvalue_values.resize( comm->size()*(comm->size()+1)/2 );
    gathered_values_view = Utility::arrayView( gathered_view_lvalue_values );
    
    FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, input_values_view, gathered_values_view, 1 ) );
  
    if( comm->rank() == 1 )
    {
      std::vector<T> expected_gathered_values;
    
      for( int i = 0; i < comm->size(); ++i )
      {
        for( int j = 0; j < (i%2==0 ? 2 : 3); ++j )
          expected_gathered_values.push_back( initializeValue( T(), i ) );
      }
    
      FRENSIE_CHECK_EQUAL( gathered_init_list_values, expected_gathered_values );

      expected_gathered_values.clear();

      for( int i = 0; i < comm->size(); ++i )
      {
        for( int j = 0; j < i+1; ++j )
          expected_gathered_values.push_back( initializeValue( T(), i ) );
      }
    
      FRENSIE_CHECK_EQUAL( gathered_view_rvalue_values, expected_gathered_values );
      FRENSIE_CHECK_EQUAL( gathered_const_view_rvalue_values, expected_gathered_values );
      FRENSIE_CHECK_EQUAL( gathered_view_lvalue_values, expected_gathered_values );
    }
  }
}

//---------------------------------------------------------------------------//
// Check that a gatherv operation can be conducted - multiple bool values, view
// of gathered values only exists on root proc
FRENSIE_UNIT_TEST( Communicator, gatherv_multiple_values_root_view_bool )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  const bool value = (comm->rank()%2 == 0 ? true : false);
  bool input_values[comm->rank()+1];
  Utility::ArrayView<const bool> input_values_view;

  {
    Utility::ArrayView<bool> input_values_view_tmp( input_values, comm->rank()+1 );
    input_values_view_tmp.fill( value );

    input_values_view = input_values_view_tmp.toConst();
  }

  if( comm->rank() == 0 )
  {
    // Gather an initializer list of values using a view rvalue
    size_t gathered_values_size = (comm->size()%2==0 ? comm->size()*5/2 : (comm->size()-1)*5/2 + 2);
    bool gathered_init_list_values[gathered_values_size];

    FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, {value, value}, Utility::ArrayView<bool>(gathered_init_list_values, gathered_values_size), 0 ) );

    // Gather an array view rvalue using a view rvalue
    gathered_values_size = comm->size()*(comm->size()+1)/2;
    bool gathered_view_rvalue_values[gathered_values_size];
    
    FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, Utility::ArrayView<bool>(input_values, comm->rank()+1), Utility::ArrayView<bool>(gathered_view_rvalue_values, gathered_values_size), 0 ) );

    // Gather an array view of const rvalue using a view rvalue
    bool gathered_const_view_rvalue_values[gathered_values_size];
    
    FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, Utility::ArrayView<const bool>(input_values, comm->rank()+1), Utility::ArrayView<bool>(gathered_const_view_rvalue_values, gathered_values_size), 0 ) );

    // Gather an array view lvalue using a view rvalue
    bool gathered_view_lvalue_values[gathered_values_size];
    
    FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, input_values_view, Utility::ArrayView<bool>(gathered_view_lvalue_values, gathered_values_size), 0 ) );

    bool expected_gathered_init_values[(comm->size()%2==0 ? comm->size()*5/2 : (comm->size()-1)*5/2 + 2)];
    bool* element = expected_gathered_init_values;
    
    for( int i = 0; i < comm->size(); ++i )
    {
      for( int j = 0; j < (i%2==0 ? 2 : 3); ++j )
      {
        if( i%2 == 0 )
          *element = true;
        else
          *element = false;

        ++element;
      }
    }

    Utility::ArrayView<const bool> gathered_values_view( gathered_init_list_values, (comm->size()%2==0 ? comm->size()*5/2 : (comm->size()-1)*5/2 + 2) );
    Utility::ArrayView<const bool> expected_gathered_values_view( expected_gathered_init_values, gathered_values_view.size() );
    
    FRENSIE_CHECK_EQUAL( gathered_values_view, expected_gathered_values_view );
    
    bool expected_gathered_values[comm->size()*(comm->size()+1)/2];
    element = expected_gathered_values;
    
    for( int i = 0; i < comm->size(); ++i )
    {
      for( int j = 0; j < i+1; ++j )
      {
        if( i%2==0 )
          *element = true;
        else
          *element = false;

        ++element;
      }
    }

    gathered_values_view =
      Utility::ArrayView<const bool>( gathered_view_rvalue_values,
                                      comm->size()*(comm->size()+1)/2 );
    expected_gathered_values_view =
      Utility::ArrayView<const bool>( expected_gathered_values,
                                      gathered_values_view.size() );
    
    FRENSIE_CHECK_EQUAL( gathered_values_view, expected_gathered_values_view );
    
    gathered_values_view =
      Utility::ArrayView<const bool>( gathered_const_view_rvalue_values,
                                      comm->size()*(comm->size()+1)/2 );
                         
    FRENSIE_CHECK_EQUAL( gathered_values_view, expected_gathered_values_view );

    gathered_values_view =
      Utility::ArrayView<const bool>( gathered_view_lvalue_values,
                                      comm->size()*(comm->size()+1)/2 );
                         
    FRENSIE_CHECK_EQUAL( gathered_values_view, expected_gathered_values_view );
  }
  else
  {
    // Gather an initializer list of values using a view rvalue
    if( comm->rank()%2 == 0 )
    {
      FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, {value, value}, 0 ) );
    }
    else
    {
      FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, {value, value, value}, 0 ) );
    }

    // Gather an array view rvalue using a view rvalue
    FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, Utility::ArrayView<bool>(input_values, comm->rank()+1), 0 ) );

    // Gather an array view of const rvalue using a view rvalue
    FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, Utility::ArrayView<const bool>(input_values, comm->rank()+1), 0 ) );

    // Gather an array view lvalue using a view rvalue
    FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, input_values_view, 0 ) );
  }

  if( comm->size() > 1 )
  {
    if( comm->rank() == 1 )
    {
      // Gather an initializer list of values using a view lvalue
      size_t gathered_values_size = (comm->size()%2==0 ? comm->size()*5/2 : (comm->size()-1)*5/2 + 2);
      bool gathered_init_list_values[gathered_values_size];
      Utility::ArrayView<bool> gathered_values_view( gathered_init_list_values, gathered_values_size );
      
      FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, {value, value, value}, gathered_values_view, 1 ) );
      
      // Gather an array view rvalue using a view lvalue
      gathered_values_size = comm->size()*(comm->size()+1)/2;
      bool gathered_view_rvalue_values[gathered_values_size];
      gathered_values_view = Utility::ArrayView<bool>( gathered_view_rvalue_values, gathered_values_size );
      
      FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, Utility::ArrayView<bool>(input_values, comm->rank()+1), gathered_values_view, 1 ) );
      
      // Gather an array view of const rvalue using a view lvalue
      bool gathered_const_view_rvalue_values[gathered_values_size];
      gathered_values_view = Utility::ArrayView<bool>(gathered_const_view_rvalue_values, gathered_values_size);
      
      FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, Utility::ArrayView<const bool>(input_values, comm->rank()+1), gathered_values_view, 1 ) );
      
      // Gather an array view lvalue using a view lvalue
      bool gathered_view_lvalue_values[gathered_values_size];
      gathered_values_view = Utility::ArrayView<bool>(gathered_view_lvalue_values, gathered_values_size);
      
      FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, input_values_view, gathered_values_view, 1 ) );
      
      bool expected_gathered_init_values[(comm->size()%2==0 ? comm->size()*5/2 : (comm->size()-1)*5/2 + 2)];
      bool* element = expected_gathered_init_values;
    
      for( int i = 0; i < comm->size(); ++i )
      {
        for( int j = 0; j < (i%2==0 ? 2 : 3); ++j )
        {
          if( i%2 == 0 )
            *element = true;
          else
            *element = false;
          
          ++element;
        }
      }
      
      gathered_values_view =
        Utility::ArrayView<bool>( gathered_init_list_values, (comm->size()%2==0 ? comm->size()*5/2 : (comm->size()-1)*5/2 + 2) );
      Utility::ArrayView<const bool> expected_gathered_values_view( expected_gathered_init_values, gathered_values_view.size() );
      
      FRENSIE_CHECK_EQUAL( gathered_values_view, expected_gathered_values_view );
      
      bool expected_gathered_values[comm->size()*(comm->size()+1)/2];
      element = expected_gathered_values;
      
      for( int i = 0; i < comm->size(); ++i )
      {
        for( int j = 0; j < i+1; ++j )
        {
          if( i%2==0 )
            *element = true;
          else
              *element = false;
          
          ++element;
        }
      }
      
      gathered_values_view =
        Utility::ArrayView<bool>( gathered_view_rvalue_values,
                                  comm->size()*(comm->size()+1)/2 );
      expected_gathered_values_view =
        Utility::ArrayView<const bool>( expected_gathered_values,
                                        gathered_values_view.size() );
      
      FRENSIE_CHECK_EQUAL( gathered_values_view, expected_gathered_values_view );
      
      gathered_values_view =
        Utility::ArrayView<bool>( gathered_const_view_rvalue_values,
                                  comm->size()*(comm->size()+1)/2 );
      
      FRENSIE_CHECK_EQUAL( gathered_values_view, expected_gathered_values_view );
      
      gathered_values_view =
        Utility::ArrayView<bool>( gathered_view_lvalue_values,
                                  comm->size()*(comm->size()+1)/2 );
      
      FRENSIE_CHECK_EQUAL( gathered_values_view, expected_gathered_values_view );
    }
    else
    {
      // Gather an initializer list of values using a view rvalue
      if( comm->rank()%2 == 0 )
      {
        FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, {value, value}, 1 ) );
      }
      else
      {
        FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, {value, value, value}, 1 ) );
      }
      
      // Gather an array view rvalue using a view rvalue
      FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, Utility::ArrayView<bool>(input_values, comm->rank()+1), 1 ) );
      
      // Gather an array view of const rvalue using a view rvalue
      FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, Utility::ArrayView<const bool>(input_values, comm->rank()+1), 1 ) );
      
      // Gather an array view lvalue using a view rvalue
      FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, input_values_view, 1 ) );
    }
  }
}

//---------------------------------------------------------------------------//
// Check that a gatherv operation can be conducted - multiple values, view
// of gathered values only exists on root proc
FRENSIE_UNIT_TEST_TEMPLATE( Communicator, gatherv_multiple_values_root_view, TypesSubset )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  const T value = initializeValue( T(), comm->rank() );
  std::vector<T> input_values( comm->rank()+1, value );
  Utility::ArrayView<const T> input_values_view( input_values );

  if( comm->rank() == 0 )
  {
    // Gather an initializer list of values using a view rvalue
    std::vector<T> gathered_init_list_values( (comm->size()%2==0 ? comm->size()*5/2 : (comm->size()-1)*5/2 + 2) );

    FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, {value, value}, Utility::arrayView(gathered_init_list_values), 0 ) );

    // Gather an array view rvalue using a view rvalue
    std::vector<T> gathered_view_rvalue_values( comm->size()*(comm->size()+1)/2 );
    FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, Utility::arrayView(input_values), Utility::arrayView(gathered_view_rvalue_values), 0 ) );

    // Gather an array view of const rvalue using a view rvalue
    std::vector<T> gathered_const_view_rvalue_values( comm->size()*(comm->size()+1)/2 );
    FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, Utility::arrayViewOfConst(input_values), Utility::arrayView(gathered_const_view_rvalue_values), 0 ) );

    // Gather an array view lvalue using a view rvalue
    std::vector<T> gathered_view_lvalue_values( comm->size()*(comm->size()+1)/2 );
    FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, input_values_view, Utility::arrayView(gathered_view_lvalue_values), 0 ) );

    std::vector<T> expected_gathered_values;
    
    for( int i = 0; i < comm->size(); ++i )
    {
      for( int j = 0; j < (i%2==0 ? 2 : 3); ++j )
        expected_gathered_values.push_back( initializeValue( T(), i ) );
    }
    
    FRENSIE_CHECK_EQUAL( gathered_init_list_values, expected_gathered_values );
    
    expected_gathered_values.clear();
    
    for( int i = 0; i < comm->size(); ++i )
    {
      for( int j = 0; j < i+1; ++j )
        expected_gathered_values.push_back( initializeValue( T(), i ) );
    }
    
    FRENSIE_CHECK_EQUAL( gathered_view_rvalue_values, expected_gathered_values );
    FRENSIE_CHECK_EQUAL( gathered_const_view_rvalue_values, expected_gathered_values );
    FRENSIE_CHECK_EQUAL( gathered_view_lvalue_values, expected_gathered_values );
  }
  else
  {
    // Gather an initializer list of values using a view rvalue
    if( comm->rank()%2 == 0 )
    {
      FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, {value, value}, 0 ) );
    }
    else
    {
      FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, {value, value, value}, 0 ) );
    }

    // Gather an array view rvalue using a view rvalue
    FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, Utility::arrayView(input_values), 0 ) );

    // Gather an array view of const rvalue using a view rvalue
    FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, Utility::arrayViewOfConst(input_values), 0 ) );

    // Gather an array view lvalue using a view rvalue
    FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, input_values_view, 0 ) );
  }

  if( comm->size() > 1 )
  {
    if( comm->rank() == 1 )
    {
      Utility::ArrayView<T> gathered_values_view;
      
      // Gather an initializer list of values using a view lvalue
      std::vector<T> gathered_init_list_values( (comm->size()%2==0 ? comm->size()*5/2 : (comm->size()-1)*5/2 + 2) );
      gathered_values_view = Utility::arrayView(gathered_init_list_values); 

      FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, {value, value, value}, gathered_values_view, 1 ) );

      // Gather an array view rvalue using a view lvalue
      std::vector<T> gathered_view_rvalue_values( comm->size()*(comm->size()+1)/2 );
      gathered_values_view = Utility::arrayView(gathered_view_rvalue_values);
      
      FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, Utility::arrayView(input_values), gathered_values_view, 1 ) );

      // Gather an array view of const rvalue using a view lvalue
      std::vector<T> gathered_const_view_rvalue_values( comm->size()*(comm->size()+1)/2 );
      gathered_values_view = Utility::arrayView(gathered_const_view_rvalue_values);
      
      FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, Utility::arrayViewOfConst(input_values), gathered_values_view, 1 ) );

      // Gather an array view lvalue using a view lvalue
      std::vector<T> gathered_view_lvalue_values( comm->size()*(comm->size()+1)/2 );
      gathered_values_view = Utility::arrayView(gathered_view_lvalue_values);
      
      FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, input_values_view, gathered_values_view, 1 ) );

      std::vector<T> expected_gathered_values;
      
      for( int i = 0; i < comm->size(); ++i )
      {
        for( int j = 0; j < (i%2==0 ? 2 : 3); ++j )
          expected_gathered_values.push_back( initializeValue( T(), i ) );
      }
    
      FRENSIE_CHECK_EQUAL( gathered_init_list_values, expected_gathered_values );
      
      expected_gathered_values.clear();
      
      for( int i = 0; i < comm->size(); ++i )
      {
        for( int j = 0; j < i+1; ++j )
          expected_gathered_values.push_back( initializeValue( T(), i ) );
      }
    
      FRENSIE_CHECK_EQUAL( gathered_view_rvalue_values, expected_gathered_values );
      FRENSIE_CHECK_EQUAL( gathered_const_view_rvalue_values, expected_gathered_values );
      FRENSIE_CHECK_EQUAL( gathered_view_lvalue_values, expected_gathered_values );
    }
    else
    {
      // Gather an initializer list of values using a view rvalue
      if( comm->rank()%2 == 0 )
      {
        FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, {value, value}, 1 ) );
      }
      else
      {
        FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, {value, value, value}, 1 ) );
      }

      // Gather an array view rvalue using a view rvalue
      FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, Utility::arrayView(input_values), 1 ) );

      // Gather an array view of const rvalue using a view rvalue
      FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, Utility::arrayViewOfConst(input_values), 1 ) );

      // Gather an array view lvalue using a view rvalue
      FRENSIE_REQUIRE_NO_THROW( Utility::gatherv( *comm, input_values_view, 1 ) );
    }
  }
}

//---------------------------------------------------------------------------//
// end tstCommunicatorGathervHelper.cpp
//---------------------------------------------------------------------------//
