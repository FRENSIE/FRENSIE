//---------------------------------------------------------------------------//
//!
//! \file   tstCommunicator.cpp
//! \author Alex Robinson
//! \brief  Communicator unit tests
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

template<typename T, typename Enabled = void>
struct TypeOpPairList
{
  typedef std::tuple<std::tuple<T,std::plus<T> >,
                     std::tuple<T,std::multiplies<T> >,
                     std::tuple<T,std::logical_and<T> >,
                     std::tuple<T,std::logical_or<T> >,
                     std::tuple<T,std::bit_and<T> >,
                     std::tuple<T,std::bit_or<T> >,
                     std::tuple<T,std::bit_xor<T> >,
                     std::tuple<T,Utility::maximum<T> >,
                     std::tuple<T,Utility::minimum<T> >,
                     std::tuple<T,Utility::bitwiseAnd<T> >,
                     std::tuple<T,Utility::bitwiseOr<T> >,
                     std::tuple<T,Utility::bitwiseXor<T> >,
                     std::tuple<T,Utility::logicalXor<T> > > type;
};

template<typename T>
struct TypeOpPairList<T,typename std::enable_if<std::is_floating_point<T>::value>::type>
{
  typedef std::tuple<std::tuple<T,std::plus<T> >,
                     std::tuple<T,std::multiplies<T> >,
                     std::tuple<T,Utility::maximum<T> >,
                     std::tuple<T,Utility::minimum<T> > > type;
};

template<typename T,typename OtherTypeOpPairList,typename Enabled = void>
struct MergeTypeOpPairList
{
  typedef OtherTypeOpPairList type;
};

template<typename T,typename OtherTypeOpPairList>
struct MergeTypeOpPairList<T,OtherTypeOpPairList,typename std::enable_if<std::is_arithmetic<T>::value>::type>
{
  typedef decltype(std::tuple_cat( typename TypeOpPairList<T>::type(), OtherTypeOpPairList() )) type;
};


template<typename... Types>
struct MergeContainerLists;

template<typename T, typename... Types>
struct MergeContainerLists<T,Types...>
{
  typedef typename MergeTypeOpPairList<T,typename MergeContainerLists<Types...>::TypeOpPairList>::type TypeOpPairList;
};

template<typename T>
struct MergeContainerLists<T>
{
  typedef typename TypeOpPairList<T>::type TypeOpPairList;
};

template<typename... Types>
struct MergeContainerLists<std::tuple<Types...> > : public MergeContainerLists<Types...>
{ /* ... */ };

typedef typename MergeContainerLists<BasicTypes>::TypeOpPairList BasicTypeOpPairs;

//---------------------------------------------------------------------------//
// Testing functions
//---------------------------------------------------------------------------//
template<typename T>
inline void initializeValue( T& value, int i )
{ value = T(i); }

inline void initializeValue( char& value, int i )
{ value = 48+i; }

inline void initializeValue( unsigned char& value, int i )
{ value = 48+i; }

inline void initializeValue( std::string& value, int i )
{ value = Utility::toString(i); }

template<typename T1, typename T2>
inline void initializeValue( std::pair<T1,T2>& value, int i )
{
  initializeValue( value.first, i );
  initializeValue( value.second, i );
}

template<typename... Types>
inline void initializeValue( std::tuple<Types...>& value, int i )
{
  initializeValue( Utility::get<0>( value ), i );
  initializeValue( Utility::get<1>( value ), i );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the default communicator can be created
FRENSIE_UNIT_TEST( Communicator, getDefault )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  FRENSIE_REQUIRE( comm.get() != NULL );
  FRENSIE_REQUIRE( comm->isValid() );
  FRENSIE_REQUIRE( (bool)*comm );
  FRENSIE_CHECK_EQUAL( comm->rank(), Utility::GlobalMPISession::rank() );
  FRENSIE_CHECK_EQUAL( comm->size(), Utility::GlobalMPISession::size() );
  FRENSIE_CHECK_EQUAL( comm->isMPIUsed(), Utility::GlobalMPISession::isMPIUsed() );

  std::shared_ptr<Utility::Timer> timer = comm->createTimer();

  FRENSIE_REQUIRE( timer.get() != NULL );
}

//---------------------------------------------------------------------------//
// Check that the null communicator can be created
FRENSIE_UNIT_TEST( Communicator, getNull )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getNull();

  FRENSIE_REQUIRE( comm.get() != NULL );
  FRENSIE_REQUIRE( !comm->isValid() );
  FRENSIE_REQUIRE( !(*comm) );
  FRENSIE_REQUIRE( !comm->isMPIUsed() );

  std::shared_ptr<Utility::Timer> timer = comm->createTimer();

  FRENSIE_REQUIRE( timer.get() != NULL );
}

//---------------------------------------------------------------------------//
// end tstCommunicator.cpp
//---------------------------------------------------------------------------//
