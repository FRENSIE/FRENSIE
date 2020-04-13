//---------------------------------------------------------------------------//
//!
//! \file   tstView.cpp
//! \author Alex Robinson
//! \brief  View unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <type_traits>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/insert_range.hpp>

// FRENSIE Includes
#include "Utility_Tuple.hpp"
#include "Utility_View.hpp"

//---------------------------------------------------------------------------//
// Template Test Types
//---------------------------------------------------------------------------//
template<typename Policy>
struct TypeList
{
  typedef boost::mpl::list<std::tuple<Policy,std::string>,std::tuple<Policy,std::array<int,4> >,std::tuple<Policy,std::vector<int> >,std::tuple<Policy,std::list<int> >,std::tuple<Policy,std::forward_list<int> >,std::tuple<Policy,std::deque<int> >,std::tuple<Policy,std::set<int> >,std::tuple<Policy,std::unordered_set<int> >,std::tuple<Policy,std::map<int,double> >,std::tuple<Policy,std::unordered_map<int,double> > > type;
};

template<typename... TypeLists>
struct MergeTypeLists
{ /* ... */ };

template<typename FrontList, typename... TypeLists>
struct MergeTypeLists<FrontList,TypeLists...>
{
private:
  typedef typename MergeTypeLists<TypeLists...>::type BackMergedListType;

public:
  typedef typename boost::mpl::insert_range<FrontList,typename boost::mpl::end<FrontList>::type,BackMergedListType>::type type;
};

template<typename FrontList>
struct MergeTypeLists<FrontList>
{ 
  typedef FrontList type;
};

typedef boost::mpl::list<bool,char,signed char,unsigned char,short,unsigned short,int,unsigned int,long,unsigned long,long long,unsigned long long,float,double> TestTypes;

typedef boost::mpl::list<std::string,std::array<int,1>,std::vector<int>,std::list<int>,std::forward_list<int>,std::deque<int>,std::set<int>,std::unordered_set<int>,std::map<int,double>,std::unordered_map<int,double> > TestContainers;

typedef boost::mpl::list<std::string,std::array<int,1>,std::vector<int>,std::list<int>,std::deque<int>,std::set<int>,std::map<int,double> > BidirTestContainers;

typedef typename MergeTypeLists<typename TypeList<Utility::EqualityComparisonPolicy>::type, typename TypeList<Utility::CloseComparisonPolicy>::type, typename TypeList<Utility::RelativeErrorComparisonPolicy>::type>::type TestEqualityPolicyContainers;

typedef typename TypeList<Utility::InequalityComparisonPolicy>::type TestInequalityPolicyContainers;

//---------------------------------------------------------------------------//
// Testing functions
//---------------------------------------------------------------------------//
template<typename T>
T initializeValue( const size_t index, const T dummy )
{ return T(index); }

template<typename T1, typename T2>
std::pair<T1,T2> initializeValue( const size_t index,
                                  const std::pair<T1,T2>& dummy )
{ return std::make_pair( T1(index), T2(index) ); }

template<typename T>
T initializeTolerance( const double raw_tolerance, const T dummy )
{ return T(raw_tolerance); }

std::string initializeTolerance( const double raw_tolerance,
                                 const std::string& dummy )
{ return Utility::toString( raw_tolerance ); }

void initializeContainer( std::string& container )
{ container = "test string"; }

template<typename T, size_t N>
void initializeContainer( std::array<T,N>& container )
{
  for( int i = 0; i < N; ++i )
    container[i] = i;
}

template<typename T>
void initializeContainer( std::vector<T>& container )
{ container.resize( 10, T(0) ); }

template<typename T>
void initializeContainer( std::list<T>& container )
{ container = std::list<T>({T(), T(), T()}); }

template<typename T>
void initializeContainer( std::forward_list<T>& container )
{ container = std::forward_list<T>({T(), T(), T(), T()}); }

template<typename T>
void initializeContainer( std::deque<T>& container )
{ container = std::deque<T>({T(), T()}); }

template<typename T>
void initializeContainer( std::set<T>& container )
{ container.insert( T() ); }

template<typename T>
void initializeContainer( std::unordered_set<T>& container )
{ container.insert( T() ); }

template<typename Key, typename T>
void initializeContainer( std::map<Key,T>& container )
{ container.insert( std::make_pair( Key(), T() ) ); }

template<typename Key, typename T>
void initializeContainer( std::unordered_map<Key,T>& container )
{ container.insert( std::make_pair( Key(), T() ) ); }

template<typename Container>
Container initializeContainer()
{
  Container tmp_container;
  initializeContainer( tmp_container );

  return tmp_container;
}

template<typename Container>
typename Container::size_type size( const Container& container )
{ return container.size(); }

template<typename T>
typename std::forward_list<T>::size_type size( const std::forward_list<T>& container )
{ return std::distance( container.begin(), container.end() ); }

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a view of contiguous memory is a container with contiguous memory
BOOST_AUTO_TEST_CASE_TEMPLATE( IsSequenceContainerWithContiguousMemory,
                               Container,
                               TestContainers )
{
  if( std::is_pointer<typename Container::iterator>::value )
  {
    BOOST_CHECK( Utility::IsSequenceContainerWithContiguousMemory<Utility::View<typename Container::iterator> >::value );
    BOOST_CHECK( !Utility::IsSequenceContainerWithContiguousMemory<Utility::View<typename Container::iterator>*>::value );
    
    BOOST_CHECK( Utility::IsSequenceContainerWithContiguousMemory<Utility::View<typename Container::const_iterator> >::value );
    BOOST_CHECK( !Utility::IsSequenceContainerWithContiguousMemory<Utility::View<typename Container::const_iterator>*>::value );
    
    BOOST_CHECK( Utility::IsSequenceContainerWithContiguousMemory<const Utility::View<typename Container::iterator> >::value );
    BOOST_CHECK( !Utility::IsSequenceContainerWithContiguousMemory<const Utility::View<typename Container::iterator>*>::value );
    
    BOOST_CHECK( Utility::IsSequenceContainerWithContiguousMemory<const Utility::View<typename Container::const_iterator> >::value );
    BOOST_CHECK( !Utility::IsSequenceContainerWithContiguousMemory<const Utility::View<typename Container::const_iterator>*>::value );
  }
  else
  {
    BOOST_CHECK( !Utility::IsSequenceContainerWithContiguousMemory<Utility::View<typename Container::iterator> >::value );
    BOOST_CHECK( !Utility::IsSequenceContainerWithContiguousMemory<Utility::View<typename Container::iterator>*>::value );
    
    BOOST_CHECK( !Utility::IsSequenceContainerWithContiguousMemory<Utility::View<typename Container::const_iterator> >::value );
    BOOST_CHECK( !Utility::IsSequenceContainerWithContiguousMemory<Utility::View<typename Container::const_iterator>*>::value );
    
    BOOST_CHECK( !Utility::IsSequenceContainerWithContiguousMemory<const Utility::View<typename Container::iterator> >::value );
    BOOST_CHECK( !Utility::IsSequenceContainerWithContiguousMemory<const Utility::View<typename Container::iterator>*>::value );
    
    BOOST_CHECK( !Utility::IsSequenceContainerWithContiguousMemory<const Utility::View<typename Container::const_iterator> >::value );
    BOOST_CHECK( !Utility::IsSequenceContainerWithContiguousMemory<const Utility::View<typename Container::const_iterator>*>::value );
  }
}


//---------------------------------------------------------------------------//
// Check that a view can be constructed
/*
BOOST_AUTO_TEST_CASE_TEMPLATE( default_constructor,
                               Container,
                               TestContainers )
{
  Utility::View<typename Container::iterator> view;

  BOOST_CHECK_EQUAL( view.size(), 0 );
  BOOST_CHECK( view.empty() );

  Utility::View<typename Container::const_iterator> view_of_const;

  BOOST_CHECK_EQUAL( view_of_const.size(), 0 );
  BOOST_CHECK( view.empty() );
}
*/

//---------------------------------------------------------------------------//
// Check that a view can be constructed from iterators
BOOST_AUTO_TEST_CASE_TEMPLATE( iterator_constructor,
                               Container,
                               TestContainers )
{
  Container container = initializeContainer<Container>();

  // Construct a view from iterators
  {
    Utility::View<typename Container::iterator>
      view( container.begin(), container.end() );

    BOOST_CHECK_EQUAL( view.size(), size(container) );
    BOOST_CHECK( !view.empty() );
  }

  // Construct a view of const from iterators
  {
    Utility::View<typename Container::const_iterator>
      view( container.begin(), container.end() );

    BOOST_CHECK_EQUAL( view.size(), size(container) );
    BOOST_CHECK( !view.empty() );
  }

  // Construct a view of const from const iterators
  {
    Utility::View<typename Container::const_iterator>
      view( container.cbegin(), container.cend() );

    BOOST_CHECK_EQUAL( view.size(), size(container) );
    BOOST_CHECK( !view.empty() );
  }
}

//---------------------------------------------------------------------------//
// Check the copy constructor
BOOST_AUTO_TEST_CASE_TEMPLATE( copy_constructor,
                               Container,
                               TestContainers )
{
  Container container = initializeContainer<Container>();

  Utility::View<typename Container::iterator>
    view( container.begin(), container.end() );

  Utility::View<typename Container::const_iterator>
    view_of_const( container.cbegin(), container.cend() );

  {
    Utility::View<typename Container::iterator> view_copy( view );

    BOOST_CHECK_EQUAL( view_copy.size(), view.size() );
  }

  {
    Utility::View<typename Container::const_iterator>
      view_of_const_copy( view );

    BOOST_CHECK_EQUAL( view_of_const_copy.size(), view.size() );
  }

  {
    Utility::View<typename Container::const_iterator>
      view_of_const_copy( view_of_const );

    BOOST_CHECK_EQUAL( view_of_const_copy.size(), view_of_const.size() );
  }
}

//---------------------------------------------------------------------------//
// Check the assignment operator
BOOST_AUTO_TEST_CASE_TEMPLATE( assignment_operator,
                               Container,
                               TestContainers )
{
  Container container = initializeContainer<Container>();

  Utility::View<typename Container::iterator>
    view( container.begin(), container.end() );

  Utility::View<typename Container::const_iterator>
    view_of_const( container.cbegin(), container.cend() );

  {
    Utility::View<typename Container::iterator> view_copy = view;

    BOOST_CHECK_EQUAL( view_copy.size(), view.size() );
  }

  {
    Utility::View<typename Container::const_iterator>
      view_of_const_copy = view;

    BOOST_CHECK_EQUAL( view_of_const_copy.size(), view.size() );
  }

  {
    Utility::View<typename Container::const_iterator>
      view_of_const_copy = view_of_const;

    BOOST_CHECK_EQUAL( view_of_const_copy.size(), view_of_const.size() );
  }
}

//---------------------------------------------------------------------------//
// Check that view iterators can be acquired
BOOST_AUTO_TEST_CASE_TEMPLATE( iterator, Container, TestContainers )
{
  Container container = initializeContainer<Container>();

  Utility::View<typename Container::iterator>
    view( container.begin(), container.end() );

  BOOST_CHECK( view.begin() == container.begin() );
  BOOST_CHECK( view.end() == container.end() );
  BOOST_CHECK( view.cbegin() == container.cbegin() );
  BOOST_CHECK( view.cend() == container.cend() );

  Utility::View<typename Container::const_iterator>
    view_of_const( container.cbegin(), container.cend() );

  BOOST_CHECK( view_of_const.begin() == container.cbegin() );
  BOOST_CHECK( view_of_const.end() == container.cend() );
  BOOST_CHECK( view_of_const.cbegin() == container.cbegin() );
  BOOST_CHECK( view_of_const.cend() == container.cend() );
}

//---------------------------------------------------------------------------//
// Check if a view can be converted to a view-of-const
BOOST_AUTO_TEST_CASE_TEMPLATE( to_const, Container, TestContainers )
{
  Container container = initializeContainer<Container>();

  Utility::View<typename Container::iterator>
    view( container.begin(), container.end() );

  {
    auto view_of_const = view.toConst();

    BOOST_CHECK( Utility::IsPointerToConst<typename decltype(view_of_const)::pointer>::value );
  }
  
  {
    auto view_of_const =
      (Utility::View<typename Container::const_iterator>)view;

    BOOST_CHECK( Utility::IsPointerToConst<typename decltype(view_of_const)::pointer>::value );
  }
}

//---------------------------------------------------------------------------//
// Check if a view can be constructed using the view helper function
BOOST_AUTO_TEST_CASE_TEMPLATE( view_construction_helper,
                               Container,
                               TestContainers )
{
  Container container = initializeContainer<Container>();

  auto view = Utility::view( container );

  BOOST_CHECK_EQUAL( view.size(), size(container) );
  BOOST_CHECK( view.begin() == container.begin() );
  BOOST_CHECK( view.end() == container.end() );
  BOOST_CHECK( (std::is_same<typename decltype(view)::iterator,typename Container::iterator>::value) );

  auto view_to_const =
    Utility::view( const_cast<const Container&>(container) );

  BOOST_CHECK_EQUAL( view_to_const.size(), size(container) );
  BOOST_CHECK( view_to_const.begin() == container.cbegin() );
  BOOST_CHECK( view_to_const.end() == container.cend() );
  BOOST_CHECK( (std::is_same<typename decltype(view_to_const)::iterator,typename Container::const_iterator>::value) );
}

//---------------------------------------------------------------------------//
// Check if a reverse view can be constructed using the reverseView helper
// function
BOOST_AUTO_TEST_CASE_TEMPLATE( reverse_view_construction_helper,
                               Container,
                               BidirTestContainers )
{
  Container container = initializeContainer<Container>();

  auto reverse_view = Utility::reverseView( container );

  BOOST_CHECK_EQUAL( reverse_view.size(), size(container) );
  BOOST_CHECK( reverse_view.begin() == container.rbegin() );
  BOOST_CHECK( reverse_view.end() == container.rend() );
  BOOST_CHECK( (std::is_same<typename decltype(reverse_view)::iterator,typename Container::reverse_iterator>::value) );

  auto reverse_view_to_const =
    Utility::reverseView( const_cast<const Container&>(container) );

  BOOST_CHECK_EQUAL( reverse_view_to_const.size(), size(container) );
  BOOST_CHECK( reverse_view_to_const.begin() == container.crbegin() );
  BOOST_CHECK( reverse_view_to_const.end() == container.crend() );
  BOOST_CHECK( (std::is_same<typename decltype(reverse_view_to_const)::iterator,typename Container::const_reverse_iterator>::value) );
}

//---------------------------------------------------------------------------//
// Check that a view can be converted to a string
BOOST_AUTO_TEST_CASE_TEMPLATE( toString, Container, TestContainers )
{
  Container container = initializeContainer<Container>();

  std::string container_string;

  if( !std::is_same<Container,std::string>::value )
    container_string += "{";

  typename Container::iterator container_it, container_end;
  container_it = container.begin();
  container_end = container.end();

  while( container_it != container_end )
  {
    container_string += Utility::toString( *container_it );

    ++container_it;
    
    if( container_it != container_end &&
        !std::is_same<Container,std::string>::value )
      container_string += ", ";
  }

  if( !std::is_same<Container,std::string>::value )
    container_string += "}";
  
  BOOST_CHECK_EQUAL( Utility::toString(Utility::view( container )),
                 container_string );
  BOOST_CHECK_EQUAL( Utility::toString(Utility::viewOfConst( container )),
                 container_string );
}

//---------------------------------------------------------------------------//
// Check that a view can be placed in a stream
BOOST_AUTO_TEST_CASE_TEMPLATE( ostream_operator, Container, TestContainers )
{
  Container container = initializeContainer<Container>();

  std::string container_string;
  
  if( !std::is_same<Container,std::string>::value )
    container_string += "{";

  typename Container::iterator container_it, container_end;
  container_it = container.begin();
  container_end = container.end();

  while( container_it != container_end )
  {
    container_string += Utility::toString( *container_it );

    ++container_it;
    
    if( container_it != container_end &&
        !std::is_same<Container,std::string>::value )
      container_string += ", ";
  }

  if( !std::is_same<Container,std::string>::value )
    container_string += "}";

  std::ostringstream oss;

  oss << Utility::view( container );

  BOOST_CHECK_EQUAL( oss.str(), container_string );

  oss.str( "" );
  oss.clear();

  oss << Utility::viewOfConst( container );
  
  BOOST_CHECK_EQUAL( oss.str(), container_string );
}

//---------------------------------------------------------------------------//
// Check the element access for std::array views
BOOST_AUTO_TEST_CASE_TEMPLATE( element_access_array, T, TestTypes )
{
  std::array<T,2> container( {0, 1} );

  Utility::View<typename std::array<T,2>::iterator>
    view( container.begin(), container.end() );

  BOOST_CHECK_EQUAL( view[0], 0 );
  BOOST_CHECK_EQUAL( view[1], 1 );
  BOOST_CHECK_EQUAL( view.at(0), 0 );
  BOOST_CHECK_EQUAL( view.at(1), 1 );
  BOOST_CHECK_EQUAL( view.front(), 0 );
  BOOST_CHECK_EQUAL( view.back(), 1 );

  view[0] = 1;
  view[1] = 0;

  BOOST_CHECK_EQUAL( view[0], 1 );
  BOOST_CHECK_EQUAL( view[1], 0 );
  BOOST_CHECK_EQUAL( view.at(0), 1 );
  BOOST_CHECK_EQUAL( view.at(1), 0 );
  BOOST_CHECK_EQUAL( view.front(), 1 );
  BOOST_CHECK_EQUAL( view.back(), 0 );

  Utility::View<typename std::array<T,2>::reverse_iterator>
    reverse_view( container.rbegin(), container.rend() );

  reverse_view[0] = 1;
  reverse_view[1] = 0;

  BOOST_CHECK_EQUAL( reverse_view[0], 1 );
  BOOST_CHECK_EQUAL( reverse_view[1], 0 );
  BOOST_CHECK_EQUAL( reverse_view.at(0), 1 );
  BOOST_CHECK_EQUAL( reverse_view.at(1), 0 );
  BOOST_CHECK_EQUAL( reverse_view.front(), 1 );
  BOOST_CHECK_EQUAL( reverse_view.back(), 0 );
  BOOST_CHECK_EQUAL( view[0], 0 );
  BOOST_CHECK_EQUAL( view[1], 1 );

  container[0] = 1;
  container[1] = 0;

  BOOST_CHECK_EQUAL( view[0], 1 );
  BOOST_CHECK_EQUAL( view[1], 0 );
  BOOST_CHECK_EQUAL( reverse_view[0], 0 );
  BOOST_CHECK_EQUAL( reverse_view[1], 1 );

  Utility::View<typename std::array<T,2>::const_iterator>
    view_of_const( container.begin(), container.end() );

  BOOST_CHECK_EQUAL( view_of_const[0], 1 );
  BOOST_CHECK_EQUAL( view_of_const[1], 0 );
  BOOST_CHECK_EQUAL( view_of_const.at(0), 1 );
  BOOST_CHECK_EQUAL( view_of_const.at(1), 0 );
  BOOST_CHECK_EQUAL( view_of_const.front(), 1 );
  BOOST_CHECK_EQUAL( view_of_const.back(), 0 );

  Utility::View<typename std::array<T,2>::const_reverse_iterator>
    reverse_view_of_const( container.rbegin(), container.rend() );

  BOOST_CHECK_EQUAL( reverse_view_of_const[0], 0 );
  BOOST_CHECK_EQUAL( reverse_view_of_const[1], 1 );
  BOOST_CHECK_EQUAL( reverse_view_of_const.at(0), 0 );
  BOOST_CHECK_EQUAL( reverse_view_of_const.at(1), 1 );
  BOOST_CHECK_EQUAL( reverse_view_of_const.front(), 0 );
  BOOST_CHECK_EQUAL( reverse_view_of_const.back(), 1 );
}

//---------------------------------------------------------------------------//
// Check the element access for vector views
BOOST_AUTO_TEST_CASE_TEMPLATE( element_access_vector, T, TestTypes )
{
  std::vector<T> container( {0, 1} );

  Utility::View<typename std::vector<T>::iterator>
    view( container.begin(), container.end() );

  BOOST_CHECK_EQUAL( view[0], 0 );
  BOOST_CHECK_EQUAL( view[1], 1 );
  BOOST_CHECK_EQUAL( view.at(0), 0 );
  BOOST_CHECK_EQUAL( view.at(1), 1 );
  BOOST_CHECK_EQUAL( view.front(), 0 );
  BOOST_CHECK_EQUAL( view.back(), 1 );

  view[0] = 1;
  view[1] = 0;

  BOOST_CHECK_EQUAL( view[0], 1 );
  BOOST_CHECK_EQUAL( view[1], 0 );
  BOOST_CHECK_EQUAL( view.at(0), 1 );
  BOOST_CHECK_EQUAL( view.at(1), 0 );
  BOOST_CHECK_EQUAL( view.front(), 1 );
  BOOST_CHECK_EQUAL( view.back(), 0 );

  Utility::View<typename std::vector<T>::reverse_iterator>
    reverse_view( container.rbegin(), container.rend() );

  reverse_view[0] = 1;
  reverse_view[1] = 0;

  BOOST_CHECK_EQUAL( reverse_view[0], 1 );
  BOOST_CHECK_EQUAL( reverse_view[1], 0 );
  BOOST_CHECK_EQUAL( reverse_view.at(0), 1 );
  BOOST_CHECK_EQUAL( reverse_view.at(1), 0 );
  BOOST_CHECK_EQUAL( reverse_view.front(), 1 );
  BOOST_CHECK_EQUAL( reverse_view.back(), 0 );
  BOOST_CHECK_EQUAL( view[0], 0 );
  BOOST_CHECK_EQUAL( view[1], 1 );

  container[0] = 1;
  container[1] = 0;

  BOOST_CHECK_EQUAL( view[0], 1 );
  BOOST_CHECK_EQUAL( view[1], 0 );
  BOOST_CHECK_EQUAL( reverse_view[0], 0 );
  BOOST_CHECK_EQUAL( reverse_view[1], 1 );

  Utility::View<typename std::vector<T>::const_iterator>
    view_of_const( container.begin(), container.end() );

  BOOST_CHECK_EQUAL( view_of_const[0], 1 );
  BOOST_CHECK_EQUAL( view_of_const[1], 0 );
  BOOST_CHECK_EQUAL( view_of_const.at(0), 1 );
  BOOST_CHECK_EQUAL( view_of_const.at(1), 0 );
  BOOST_CHECK_EQUAL( view_of_const.front(), 1 );
  BOOST_CHECK_EQUAL( view_of_const.back(), 0 );

  Utility::View<typename std::vector<T>::const_reverse_iterator>
    reverse_view_of_const( container.rbegin(), container.rend() );

  BOOST_CHECK_EQUAL( reverse_view_of_const[0], 0 );
  BOOST_CHECK_EQUAL( reverse_view_of_const[1], 1 );
  BOOST_CHECK_EQUAL( reverse_view_of_const.at(0), 0 );
  BOOST_CHECK_EQUAL( reverse_view_of_const.at(1), 1 );
  BOOST_CHECK_EQUAL( reverse_view_of_const.front(), 0 );
  BOOST_CHECK_EQUAL( reverse_view_of_const.back(), 1 );
}

//---------------------------------------------------------------------------//
// Check the element access for list views
BOOST_AUTO_TEST_CASE_TEMPLATE( element_access_list, T, TestTypes )
{
  std::list<T> container( {0, 1} );

  Utility::View<typename std::list<T>::iterator>
    view( container.begin(), container.end() );

  BOOST_CHECK_EQUAL( view[0], 0 );
  BOOST_CHECK_EQUAL( view[1], 1 );
  BOOST_CHECK_EQUAL( view.at(0), 0 );
  BOOST_CHECK_EQUAL( view.at(1), 1 );
  BOOST_CHECK_EQUAL( view.front(), 0 );
  BOOST_CHECK_EQUAL( view.back(), 1 );

  view[0] = 1;
  view[1] = 0;

  BOOST_CHECK_EQUAL( view[0], 1 );
  BOOST_CHECK_EQUAL( view[1], 0 );
  BOOST_CHECK_EQUAL( view.at(0), 1 );
  BOOST_CHECK_EQUAL( view.at(1), 0 );
  BOOST_CHECK_EQUAL( view.front(), 1 );
  BOOST_CHECK_EQUAL( view.back(), 0 );

  Utility::View<typename std::list<T>::reverse_iterator>
    reverse_view( container.rbegin(), container.rend() );

  reverse_view[0] = 1;
  reverse_view[1] = 0;

  BOOST_CHECK_EQUAL( reverse_view[0], 1 );
  BOOST_CHECK_EQUAL( reverse_view[1], 0 );
  BOOST_CHECK_EQUAL( reverse_view.at(0), 1 );
  BOOST_CHECK_EQUAL( reverse_view.at(1), 0 );
  BOOST_CHECK_EQUAL( reverse_view.front(), 1 );
  BOOST_CHECK_EQUAL( reverse_view.back(), 0 );
  BOOST_CHECK_EQUAL( view[0], 0 );
  BOOST_CHECK_EQUAL( view[1], 1 );

  container.front() = 1;
  container.back() = 0;

  BOOST_CHECK_EQUAL( view[0], 1 );
  BOOST_CHECK_EQUAL( view[1], 0 );
  BOOST_CHECK_EQUAL( reverse_view[0], 0 );
  BOOST_CHECK_EQUAL( reverse_view[1], 1 );

  Utility::View<typename std::list<T>::const_iterator>
    view_of_const( container.begin(), container.end() );

  BOOST_CHECK_EQUAL( view_of_const[0], 1 );
  BOOST_CHECK_EQUAL( view_of_const[1], 0 );
  BOOST_CHECK_EQUAL( view_of_const.at(0), 1 );
  BOOST_CHECK_EQUAL( view_of_const.at(1), 0 );
  BOOST_CHECK_EQUAL( view_of_const.front(), 1 );
  BOOST_CHECK_EQUAL( view_of_const.back(), 0 );

  Utility::View<typename std::list<T>::const_reverse_iterator>
    reverse_view_of_const( container.rbegin(), container.rend() );

  BOOST_CHECK_EQUAL( reverse_view_of_const[0], 0 );
  BOOST_CHECK_EQUAL( reverse_view_of_const[1], 1 );
  BOOST_CHECK_EQUAL( reverse_view_of_const.at(0), 0 );
  BOOST_CHECK_EQUAL( reverse_view_of_const.at(1), 1 );
  BOOST_CHECK_EQUAL( reverse_view_of_const.front(), 0 );
  BOOST_CHECK_EQUAL( reverse_view_of_const.back(), 1 );
}

//---------------------------------------------------------------------------//
// Check the element access for forward_list views
BOOST_AUTO_TEST_CASE_TEMPLATE( element_access_forward_list, T, TestTypes )
{
  std::forward_list<T> container( {0, 1} );

  Utility::View<typename std::forward_list<T>::iterator>
    view( container.begin(), container.end() );

  BOOST_CHECK_EQUAL( view[0], 0 );
  BOOST_CHECK_EQUAL( view[1], 1 );
  BOOST_CHECK_EQUAL( view.at(0), 0 );
  BOOST_CHECK_EQUAL( view.at(1), 1 );
  BOOST_CHECK_EQUAL( view.front(), 0 );
  BOOST_CHECK_EQUAL( view.back(), 1 );

  view[0] = 1;
  view[1] = 0;

  BOOST_CHECK_EQUAL( view[0], 1 );
  BOOST_CHECK_EQUAL( view[1], 0 );
  BOOST_CHECK_EQUAL( view.at(0), 1 );
  BOOST_CHECK_EQUAL( view.at(1), 0 );
  BOOST_CHECK_EQUAL( view.front(), 1 );
  BOOST_CHECK_EQUAL( view.back(), 0 );

  container.front() = 1;
  *(++container.begin()) = 0;

  Utility::View<typename std::forward_list<T>::const_iterator>
    view_of_const( container.begin(), container.end() );

  BOOST_CHECK_EQUAL( view_of_const[0], 1 );
  BOOST_CHECK_EQUAL( view_of_const[1], 0 );
  BOOST_CHECK_EQUAL( view_of_const.at(0), 1 );
  BOOST_CHECK_EQUAL( view_of_const.at(1), 0 );
  BOOST_CHECK_EQUAL( view_of_const.front(), 1 );
  BOOST_CHECK_EQUAL( view_of_const.back(), 0 );
}

//---------------------------------------------------------------------------//
// Check the element access for deque views
BOOST_AUTO_TEST_CASE_TEMPLATE( element_access_deque, T, TestTypes )
{
  std::deque<T> container( {0, 1} );

  Utility::View<typename std::deque<T>::iterator>
    view( container.begin(), container.end() );

  BOOST_CHECK_EQUAL( view[0], 0 );
  BOOST_CHECK_EQUAL( view[1], 1 );
  BOOST_CHECK_EQUAL( view.at(0), 0 );
  BOOST_CHECK_EQUAL( view.at(1), 1 );
  BOOST_CHECK_EQUAL( view.front(), 0 );
  BOOST_CHECK_EQUAL( view.back(), 1 );

  view[0] = 1;
  view[1] = 0;

  BOOST_CHECK_EQUAL( view[0], 1 );
  BOOST_CHECK_EQUAL( view[1], 0 );
  BOOST_CHECK_EQUAL( view.at(0), 1 );
  BOOST_CHECK_EQUAL( view.at(1), 0 );
  BOOST_CHECK_EQUAL( view.front(), 1 );
  BOOST_CHECK_EQUAL( view.back(), 0 );

  Utility::View<typename std::deque<T>::reverse_iterator>
    reverse_view( container.rbegin(), container.rend() );

  reverse_view[0] = 1;
  reverse_view[1] = 0;

  BOOST_CHECK_EQUAL( reverse_view[0], 1 );
  BOOST_CHECK_EQUAL( reverse_view[1], 0 );
  BOOST_CHECK_EQUAL( reverse_view.at(0), 1 );
  BOOST_CHECK_EQUAL( reverse_view.at(1), 0 );
  BOOST_CHECK_EQUAL( reverse_view.front(), 1 );
  BOOST_CHECK_EQUAL( reverse_view.back(), 0 );
  BOOST_CHECK_EQUAL( view[0], 0 );
  BOOST_CHECK_EQUAL( view[1], 1 );

  container.front() = 1;
  container.back() = 0;

  BOOST_CHECK_EQUAL( view[0], 1 );
  BOOST_CHECK_EQUAL( view[1], 0 );
  BOOST_CHECK_EQUAL( reverse_view[0], 0 );
  BOOST_CHECK_EQUAL( reverse_view[1], 1 );

  Utility::View<typename std::deque<T>::const_iterator>
    view_of_const( container.begin(), container.end() );

  BOOST_CHECK_EQUAL( view_of_const[0], 1 );
  BOOST_CHECK_EQUAL( view_of_const[1], 0 );
  BOOST_CHECK_EQUAL( view_of_const.at(0), 1 );
  BOOST_CHECK_EQUAL( view_of_const.at(1), 0 );
  BOOST_CHECK_EQUAL( view_of_const.front(), 1 );
  BOOST_CHECK_EQUAL( view_of_const.back(), 0 );

  Utility::View<typename std::deque<T>::const_reverse_iterator>
    reverse_view_of_const( container.rbegin(), container.rend() );

  BOOST_CHECK_EQUAL( reverse_view_of_const[0], 0 );
  BOOST_CHECK_EQUAL( reverse_view_of_const[1], 1 );
  BOOST_CHECK_EQUAL( reverse_view_of_const.at(0), 0 );
  BOOST_CHECK_EQUAL( reverse_view_of_const.at(1), 1 );
  BOOST_CHECK_EQUAL( reverse_view_of_const.front(), 0 );
  BOOST_CHECK_EQUAL( reverse_view_of_const.back(), 1 );
}

//---------------------------------------------------------------------------//
// Check the element access for set views
BOOST_AUTO_TEST_CASE_TEMPLATE( element_access_set, T, TestTypes )
{
  std::set<T> container( {0, 1} );

  Utility::View<typename std::set<T>::iterator>
    view( container.begin(), container.end() );

  BOOST_CHECK_EQUAL( view[0], 0 );
  BOOST_CHECK_EQUAL( view[1], 1 );
  BOOST_CHECK_EQUAL( view.at(0), 0 );
  BOOST_CHECK_EQUAL( view.at(1), 1 );
  BOOST_CHECK_EQUAL( view.front(), 0 );
  BOOST_CHECK_EQUAL( view.back(), 1 );

  Utility::View<typename std::set<T>::reverse_iterator>
    reverse_view( container.rbegin(), container.rend() );

  BOOST_CHECK_EQUAL( reverse_view[0], 1 );
  BOOST_CHECK_EQUAL( reverse_view[1], 0 );
  BOOST_CHECK_EQUAL( reverse_view.at(0), 1 );
  BOOST_CHECK_EQUAL( reverse_view.at(1), 0 );
  BOOST_CHECK_EQUAL( reverse_view.front(), 1 );
  BOOST_CHECK_EQUAL( reverse_view.back(), 0 );
  
  Utility::View<typename std::set<T>::const_iterator>
    view_of_const( container.begin(), container.end() );

  BOOST_CHECK_EQUAL( view_of_const[0], 0 );
  BOOST_CHECK_EQUAL( view_of_const[1], 1 );
  BOOST_CHECK_EQUAL( view_of_const.at(0), 0 );
  BOOST_CHECK_EQUAL( view_of_const.at(1), 1 );
  BOOST_CHECK_EQUAL( view_of_const.front(), 0 );
  BOOST_CHECK_EQUAL( view_of_const.back(), 1 );

  Utility::View<typename std::set<T>::const_reverse_iterator>
    reverse_view_of_const( container.rbegin(), container.rend() );

  BOOST_CHECK_EQUAL( reverse_view_of_const[0], 1 );
  BOOST_CHECK_EQUAL( reverse_view_of_const[1], 0 );
  BOOST_CHECK_EQUAL( reverse_view_of_const.at(0), 1 );
  BOOST_CHECK_EQUAL( reverse_view_of_const.at(1), 0 );
  BOOST_CHECK_EQUAL( reverse_view_of_const.front(), 1 );
  BOOST_CHECK_EQUAL( reverse_view_of_const.back(), 0 );
}

//---------------------------------------------------------------------------//
// Check the element access for unordered_set views
BOOST_AUTO_TEST_CASE_TEMPLATE( element_access_unordered_set, T, TestTypes )
{
  std::unordered_set<T> container( {0, 1} );

  Utility::View<typename std::unordered_set<T>::iterator>
    view( container.begin(), container.end() );

  BOOST_CHECK_EQUAL( view[0], 1 );
  BOOST_CHECK_EQUAL( view[1], 0 );
  BOOST_CHECK_EQUAL( view.at(0), 1 );
  BOOST_CHECK_EQUAL( view.at(1), 0 );
  BOOST_CHECK_EQUAL( view.front(), 1 );
  BOOST_CHECK_EQUAL( view.back(), 0 );

  Utility::View<typename std::unordered_set<T>::const_iterator>
    view_of_const( container.begin(), container.end() );

  BOOST_CHECK_EQUAL( view_of_const[0], 1 );
  BOOST_CHECK_EQUAL( view_of_const[1], 0 );
  BOOST_CHECK_EQUAL( view_of_const.at(0), 1 );
  BOOST_CHECK_EQUAL( view_of_const.at(1), 0 );
  BOOST_CHECK_EQUAL( view_of_const.front(), 1 );
  BOOST_CHECK_EQUAL( view_of_const.back(), 0 );
}

//---------------------------------------------------------------------------//
// Check the element access for map views
BOOST_AUTO_TEST_CASE_TEMPLATE( element_access_map, T, TestTypes )
{
  std::map<T,T> container( {std::make_pair((T)0, (T)0), std::make_pair((T)1, (T)1)} );

  Utility::View<typename std::map<T,T>::iterator>
    view( container.begin(), container.end() );

  BOOST_CHECK_EQUAL( view[0], (std::pair<const T,T>({0, 0})) );
  BOOST_CHECK_EQUAL( view[1], (std::pair<const T,T>({1, 1})) );
  BOOST_CHECK_EQUAL( view.at(0), (std::pair<const T,T>({0, 0})) );
  BOOST_CHECK_EQUAL( view.at(1), (std::pair<const T,T>({1, 1})) );
  BOOST_CHECK_EQUAL( view.front(), (std::pair<const T,T>({0, 0})) );
  BOOST_CHECK_EQUAL( view.back(), (std::pair<const T,T>({1, 1})) );

  Utility::View<typename std::map<T,T>::reverse_iterator>
    reverse_view( container.rbegin(), container.rend() );

  BOOST_CHECK_EQUAL( reverse_view[0], (std::pair<const T,T>({1, 1})) );
  BOOST_CHECK_EQUAL( reverse_view[1], (std::pair<const T,T>({0, 0})) );
  BOOST_CHECK_EQUAL( reverse_view.at(0), (std::pair<const T,T>({1, 1})) );
  BOOST_CHECK_EQUAL( reverse_view.at(1), (std::pair<const T,T>({0, 0})) );
  BOOST_CHECK_EQUAL( reverse_view.front(), (std::pair<const T,T>({1, 1})) );
  BOOST_CHECK_EQUAL( reverse_view.back(), (std::pair<const T,T>({0, 0})) );
  
  Utility::View<typename std::map<T,T>::const_iterator>
    view_of_const( container.begin(), container.end() );

  BOOST_CHECK_EQUAL( view_of_const[0], (std::pair<const T,T>({0, 0})) );
  BOOST_CHECK_EQUAL( view_of_const[1], (std::pair<const T,T>({1, 1})) );
  BOOST_CHECK_EQUAL( view_of_const.at(0), (std::pair<const T,T>({0, 0})) );
  BOOST_CHECK_EQUAL( view_of_const.at(1), (std::pair<const T,T>({1, 1})) );
  BOOST_CHECK_EQUAL( view_of_const.front(), (std::pair<const T,T>({0, 0})) );
  BOOST_CHECK_EQUAL( view_of_const.back(), (std::pair<const T,T>({1, 1})) );

  Utility::View<typename std::map<T,T>::const_reverse_iterator>
    reverse_view_of_const( container.rbegin(), container.rend() );

  BOOST_CHECK_EQUAL( reverse_view_of_const[0], (std::pair<const T,T>({1, 1})) );
  BOOST_CHECK_EQUAL( reverse_view_of_const[1], (std::pair<const T,T>({0, 0})) );
  BOOST_CHECK_EQUAL( reverse_view_of_const.at(0), (std::pair<const T,T>({1, 1})) );
  BOOST_CHECK_EQUAL( reverse_view_of_const.at(1), (std::pair<const T,T>({0, 0})) );
  BOOST_CHECK_EQUAL( reverse_view_of_const.front(), (std::pair<const T,T>({1, 1})) );
  BOOST_CHECK_EQUAL( reverse_view_of_const.back(), (std::pair<const T,T>({0, 0})) );
}

//---------------------------------------------------------------------------//
// Check the element access for unordered_map views
BOOST_AUTO_TEST_CASE_TEMPLATE( element_access_unordered_map, T, TestTypes )
{
  std::unordered_map<T,T> container( {std::make_pair((T)0, (T)0), std::make_pair((T)1, (T)1)} );

  Utility::View<typename std::unordered_map<T,T>::iterator>
    view( container.begin(), container.end() );

  BOOST_CHECK_EQUAL( view[0], (std::pair<const T,T>({1, 1})) );
  BOOST_CHECK_EQUAL( view[1], (std::pair<const T,T>({0, 0})) );
  BOOST_CHECK_EQUAL( view.at(0), (std::pair<const T,T>({1, 1})) );
  BOOST_CHECK_EQUAL( view.at(1), (std::pair<const T,T>({0, 0})) );
  BOOST_CHECK_EQUAL( view.front(), (std::pair<const T,T>({1, 1})) );
  BOOST_CHECK_EQUAL( view.back(), (std::pair<const T,T>({0, 0})) );

  Utility::View<typename std::unordered_map<T,T>::const_iterator>
    view_of_const( container.begin(), container.end() );

  BOOST_CHECK_EQUAL( view_of_const[0], (std::pair<const T,T>({1, 1})) );
  BOOST_CHECK_EQUAL( view_of_const[1], (std::pair<const T,T>({0, 0})) );
  BOOST_CHECK_EQUAL( view_of_const.at(0), (std::pair<const T,T>({1, 1})) );
  BOOST_CHECK_EQUAL( view_of_const.at(1), (std::pair<const T,T>({0, 0})) );
  BOOST_CHECK_EQUAL( view_of_const.front(), (std::pair<const T,T>({1, 1})) );
  BOOST_CHECK_EQUAL( view_of_const.back(), (std::pair<const T,T>({0, 0})) );
}

//---------------------------------------------------------------------------//
// Check that the correct comparison policies are allowed for views
BOOST_AUTO_TEST_CASE_TEMPLATE( IsComparisonAllowed,
                               Container,
                               TestContainers )
{
  typedef Utility::View<typename Container::iterator> View;
  typedef Utility::View<typename Container::const_iterator> ViewOfConst;

  BOOST_CHECK( Utility::ComparisonTraits<View>::template IsComparisonAllowed<Utility::EqualityComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<View>::template IsComparisonAllowed<Utility::InequalityComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<View>::template IsComparisonAllowed<Utility::GreaterThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<View>::template IsComparisonAllowed<Utility::GreaterThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<View>::template IsComparisonAllowed<Utility::LessThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<View>::template IsComparisonAllowed<Utility::LessThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<View>::template IsComparisonAllowed<Utility::CloseComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<View>::template IsComparisonAllowed<Utility::RelativeErrorComparisonPolicy>::value );

  BOOST_CHECK( Utility::ComparisonTraits<const View>::template IsComparisonAllowed<Utility::EqualityComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<const View>::template IsComparisonAllowed<Utility::InequalityComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const View>::template IsComparisonAllowed<Utility::GreaterThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const View>::template IsComparisonAllowed<Utility::GreaterThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const View>::template IsComparisonAllowed<Utility::LessThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const View>::template IsComparisonAllowed<Utility::LessThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<const View>::template IsComparisonAllowed<Utility::CloseComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<const View>::template IsComparisonAllowed<Utility::RelativeErrorComparisonPolicy>::value );

  BOOST_CHECK( Utility::ComparisonTraits<ViewOfConst>::template IsComparisonAllowed<Utility::EqualityComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<ViewOfConst>::template IsComparisonAllowed<Utility::InequalityComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<ViewOfConst>::template IsComparisonAllowed<Utility::GreaterThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<ViewOfConst>::template IsComparisonAllowed<Utility::GreaterThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<ViewOfConst>::template IsComparisonAllowed<Utility::LessThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<ViewOfConst>::template IsComparisonAllowed<Utility::LessThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<ViewOfConst>::template IsComparisonAllowed<Utility::CloseComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<ViewOfConst>::template IsComparisonAllowed<Utility::RelativeErrorComparisonPolicy>::value );

  BOOST_CHECK( Utility::ComparisonTraits<const ViewOfConst>::template IsComparisonAllowed<Utility::EqualityComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<const ViewOfConst>::template IsComparisonAllowed<Utility::InequalityComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const ViewOfConst>::template IsComparisonAllowed<Utility::GreaterThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const ViewOfConst>::template IsComparisonAllowed<Utility::GreaterThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const ViewOfConst>::template IsComparisonAllowed<Utility::LessThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const ViewOfConst>::template IsComparisonAllowed<Utility::LessThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<const ViewOfConst>::template IsComparisonAllowed<Utility::CloseComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<const ViewOfConst>::template IsComparisonAllowed<Utility::RelativeErrorComparisonPolicy>::value );
}

//---------------------------------------------------------------------------//
// Check that two views can be compared
BOOST_AUTO_TEST_CASE_TEMPLATE( compare_equal,
                               PolicyContainerPair,
                               TestEqualityPolicyContainers )
{
  typedef typename Utility::TupleElement<0,PolicyContainerPair>::type Policy;
  typedef typename Utility::TupleElement<1,PolicyContainerPair>::type Container;
  typedef Utility::View<typename Container::iterator> View;
  typedef Utility::View<typename Container::const_iterator> ViewOfConst;

  Container left_container = initializeContainer<Container>();
  Container right_container = initializeContainer<Container>();
  Container empty_container;

  // Construct a view from iterators
  View left_view( left_container.begin(), left_container.end() );
  ViewOfConst left_view_of_const = left_view.toConst();

  View right_view( right_container.begin(), right_container.end() );
  ViewOfConst right_view_of_const = right_view.toConst();

  View empty_view( empty_container.begin(), empty_container.end() );
  ViewOfConst emtpy_view_of_const = empty_view.toConst();

  std::ostringstream oss;

  // No details logging
  bool compare_result =
    Utility::ComparisonTraits<View>::template compare<Policy,0,0>(
                                                      empty_view, "lhs", false,
                                                      right_view, "rhs", false,
                                                      "", oss );
 
  BOOST_CHECK( !compare_result );
  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result =
    Utility::ComparisonTraits<View>::template compare<Policy,0,0>(
                                                       left_view, "lhs", false,
                                                       empty_view, "rhs", false,
                                                       "", oss );

  BOOST_CHECK( !compare_result );
  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::ComparisonTraits<View>::template compare<Policy,0,0>(
                                                      left_view, "lhs", false,
                                                      right_view, "rhs", false,
                                                      "", oss );

  bool expected_compare_result =
    Policy::compare( left_view.size(), right_view.size() );

  for( size_t i = 0; i < left_view.size(); ++i )
  {
    std::ostringstream local_oss;
    bool local_expected_compare_result =
      Utility::ComparisonTraits<typename View::value_type>::template compare<Policy,0,0>(
                                                   left_view[i], "lhs", false,
                                                   right_view[i], "rhs", false,
                                                   "", local_oss, false );
    if( !local_expected_compare_result )
      expected_compare_result = local_expected_compare_result;
  }

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result =
    Utility::ComparisonTraits<ViewOfConst>::template compare<Policy,0,0>(
                                             left_view_of_const, "lhs", false,
                                             right_view_of_const, "rhs", false,
                                             "", oss );

  expected_compare_result =
    Policy::compare( left_view_of_const.size(), right_view_of_const.size() );

  for( size_t i = 0; i < left_view_of_const.size(); ++i )
  {
    std::ostringstream local_oss;
    bool local_expected_compare_result =
      Utility::ComparisonTraits<typename View::value_type>::template compare<Policy,0,0>(
                                          left_view_of_const[i], "lhs", false,
                                          right_view_of_const[i], "rhs", false,
                                          "", local_oss, false );
    if( !local_expected_compare_result )
      expected_compare_result = local_expected_compare_result;
  }

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result =
    Utility::ComparisonTraits<ViewOfConst>::template compare<Policy,0,0>(
                                             left_view, "lhs", false,
                                             right_view_of_const, "rhs", false,
                                             "", oss );

  expected_compare_result =
    Policy::compare( left_view.size(), right_view_of_const.size() );

  for( size_t i = 0; i < left_view.size(); ++i )
  {
    std::ostringstream local_oss;
    bool local_expected_compare_result =
      Utility::ComparisonTraits<typename View::value_type>::template compare<Policy,0,0>(
                                          left_view[i], "lhs", false,
                                          right_view_of_const[i], "rhs", false,
                                          "", local_oss, false );
    if( !local_expected_compare_result )
      expected_compare_result = local_expected_compare_result;
  }

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result =
    Utility::ComparisonTraits<ViewOfConst>::template compare<Policy,0,0>(
                                             left_view_of_const, "lhs", false,
                                             right_view, "rhs", false,
                                             "", oss );

  expected_compare_result =
    Policy::compare( left_view_of_const.size(), right_view.size() );

  for( size_t i = 0; i < left_view_of_const.size(); ++i )
  {
    std::ostringstream local_oss;
    bool local_expected_compare_result =
      Utility::ComparisonTraits<typename View::value_type>::template compare<Policy,0,0>(
                                           left_view_of_const[i], "lhs", false,
                                           right_view[i], "rhs", false,
                                           "", local_oss, false );
    if( !local_expected_compare_result )
      expected_compare_result = local_expected_compare_result;
  }

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), "" );

  // Details logging - default tolerance
  compare_result =
    Utility::ComparisonTraits<View>::template compare<Policy,0,Utility::Details::incrementRightShift(0)>(
                                                      left_view, "lhs", false,
                                                      right_view, "rhs", false,
                                                      "", oss, true );

  std::string expected_details =
    Utility::ComparisonTraits<View>::template createComparisonHeader<Policy,0>(
                                                      left_view, "lhs", false,
                                                      right_view, "rhs", false,
                                                      "" );
  std::ostringstream local_oss;

  expected_compare_result =
    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                               left_view.size(), "lhs", false,
                                               right_view.size(), "rhs", false,
                                               ".size()", local_oss, true );
  
  for( size_t i = 0; i < left_view.size(); ++i )
  {
    
    bool local_expected_compare_result =
      Utility::ComparisonTraits<typename View::value_type>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                                   left_view[i], "lhs", false,
                                                   right_view[i], "rhs", false,
                                                   "", local_oss, true );
    if( !local_expected_compare_result )
      expected_compare_result = local_expected_compare_result;
  }
  
  expected_details += (expected_compare_result ? "passed\n" : "failed!\n" );
  expected_details += local_oss.str();
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();
  
  local_oss.str( "" );
  local_oss.clear();

  compare_result =
    Utility::ComparisonTraits<View>::template compare<Policy,0,Utility::Details::incrementRightShift(0)>(
                                                      left_view, "lhs", true,
                                                      right_view, "rhs", false,
                                                      "", oss, true );

  expected_details =
    Utility::ComparisonTraits<View>::template createComparisonHeader<Policy,0>(
                                                      left_view, "lhs", true,
                                                      right_view, "rhs", false,
                                                      "" );

  expected_compare_result =
    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                               left_view.size(), "lhs", true,
                                               right_view.size(), "rhs", false,
                                               ".size()", local_oss, true );
  
  for( size_t i = 0; i < left_view.size(); ++i )
  {
    bool local_expected_compare_result =
      Utility::ComparisonTraits<typename View::value_type>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
              left_view[i], "lhs", true,
              right_view[i], "rhs", false,
              std::string("[") + Utility::toString(i) + "]", local_oss, true );
    
    if( !local_expected_compare_result )
      expected_compare_result = local_expected_compare_result;
  }

  expected_details += (expected_compare_result ? "passed\n" : "failed!\n" );
  expected_details += local_oss.str();
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  local_oss.str( "" );
  local_oss.clear();

  compare_result =
    Utility::ComparisonTraits<View>::template compare<Policy,0,Utility::Details::incrementRightShift(0)>(
                                                      left_view, "lhs", false,
                                                      right_view, "rhs", true,
                                                      "", oss, true );

  expected_details =
    Utility::ComparisonTraits<View>::template createComparisonHeader<Policy,0>(
                                                      left_view, "lhs", false,
                                                      right_view, "rhs", true,
                                                      "" );

  expected_compare_result =
    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                               left_view.size(), "lhs", false,
                                               right_view.size(), "rhs", true,
                                               ".size()", local_oss, true );
  
  for( size_t i = 0; i < left_view.size(); ++i )
  {
    bool local_expected_compare_result =
      Utility::ComparisonTraits<typename View::value_type>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
              left_view[i], "lhs", false,
              right_view[i], "rhs", true,
              std::string("[") + Utility::toString(i) + "]", local_oss, true );
       
    if( !local_expected_compare_result )
      expected_compare_result = local_expected_compare_result;
  }

  expected_details += (expected_compare_result ? "passed\n" : "failed!\n" );
  expected_details += local_oss.str();
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  local_oss.str( "" );
  local_oss.clear();

  compare_result =
    Utility::ComparisonTraits<View>::template compare<Policy,0,Utility::Details::incrementRightShift(0)>(
                                                      left_view, "lhs", true,
                                                      right_view, "rhs", true,
                                                      "", oss, true );

  expected_details =
    Utility::ComparisonTraits<View>::template createComparisonHeader<Policy,0>(
                                                      left_view, "lhs", true,
                                                      right_view, "rhs", true,
                                                      "" );

  expected_compare_result =
    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                               left_view.size(), "lhs", true,
                                               right_view.size(), "rhs", true,
                                               ".size()", local_oss, true );
  
  for( size_t i = 0; i < left_view.size(); ++i )
  {
    bool local_expected_compare_result =
      Utility::ComparisonTraits<typename View::value_type>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
              left_view[i], "lhs", true,
              right_view[i], "rhs", true,
              std::string("[") + Utility::toString(i) + "]", local_oss, true );
    
    if( !local_expected_compare_result )
      expected_compare_result = local_expected_compare_result;
  }

  expected_details += (expected_compare_result ? "passed\n" : "failed!\n" );
  expected_details += local_oss.str();
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  local_oss.str( "" );
  local_oss.clear();

  // Details logging - custom tolerance
  typedef typename Utility::ComparisonTraits<View>::ExtraDataType ExtraDataType;
  ExtraDataType tol = initializeTolerance( 1e-6, ExtraDataType() );
  
  compare_result =
    Utility::ComparisonTraits<View>::template compare<Policy,0,Utility::Details::incrementRightShift(0)>(
                                                      left_view, "lhs", false,
                                                      right_view, "rhs", false,
                                                      "", oss, true, tol );

  
  expected_details =
    Utility::ComparisonTraits<View>::template createComparisonHeader<Policy,0>(
                                                      left_view, "lhs", false,
                                                      right_view, "rhs", false,
                                                      "" );
  
  expected_compare_result =
    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                               left_view.size(), "lhs", false,
                                               right_view.size(), "rhs", false,
                                               ".size()", local_oss, true );
  
  for( size_t i = 0; i < left_view.size(); ++i )
  {
    bool local_expected_compare_result =
      Utility::ComparisonTraits<typename View::value_type>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                                   left_view[i], "lhs", false,
                                                   right_view[i], "rhs", false,
                                                   "", local_oss, true, tol );
    if( !local_expected_compare_result )
      expected_compare_result = local_expected_compare_result;
  }

  expected_details += (expected_compare_result ? "passed\n" : "failed!\n" );
  expected_details += local_oss.str();
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );
  
  oss.str( "" );
  oss.clear();

  local_oss.str( "" );
  local_oss.clear();

  compare_result =
    Utility::ComparisonTraits<View>::template compare<Policy,0,Utility::Details::incrementRightShift(0)>(
                                                      left_view, "lhs", true,
                                                      right_view, "rhs", false,
                                                      "", oss, true, tol );

  expected_details =
    Utility::ComparisonTraits<View>::template createComparisonHeader<Policy,0>(
                                                      left_view, "lhs", true,
                                                      right_view, "rhs", false,
                                                      "", tol );

  expected_compare_result =
    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                               left_view.size(), "lhs", true,
                                               right_view.size(), "rhs", false,
                                               ".size()", local_oss, true );

  for( size_t i = 0; i < left_view.size(); ++i )
  {
    bool local_expected_compare_result =
      Utility::ComparisonTraits<typename View::value_type>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                left_view[i], "lhs", true,
                right_view[i], "rhs", false,
                std::string("[") + Utility::toString(i) + "]", local_oss, true,
                tol );
    
    if( !local_expected_compare_result )
      expected_compare_result = local_expected_compare_result;
  }

  expected_details += (expected_compare_result ? "passed\n" : "failed!\n" );
  expected_details += local_oss.str();
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  local_oss.str( "" );
  local_oss.clear();

  compare_result =
    Utility::ComparisonTraits<View>::template compare<Policy,0,Utility::Details::incrementRightShift(0)>(
                                                      left_view, "lhs", false,
                                                      right_view, "rhs", true,
                                                      "", oss, true, tol );

  expected_details =
    Utility::ComparisonTraits<View>::template createComparisonHeader<Policy,0>(
                                                      left_view, "lhs", false,
                                                      right_view, "rhs", true,
                                                      "", tol );

  expected_compare_result =
    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                               left_view.size(), "lhs", false,
                                               right_view.size(), "rhs", true,
                                               ".size()", local_oss, true );

  for( size_t i = 0; i < left_view.size(); ++i )
  {
    bool local_expected_compare_result =
      Utility::ComparisonTraits<typename View::value_type>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                left_view[i], "lhs", false,
                right_view[i], "rhs", true,
                std::string("[") + Utility::toString(i) + "]", local_oss, true,
                tol );
    
    if( !local_expected_compare_result )
      expected_compare_result = local_expected_compare_result;
  }

  expected_details += (expected_compare_result ? "passed\n" : "failed!\n" );
  expected_details += local_oss.str();
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  local_oss.str( "" );
  local_oss.clear();

  compare_result =
    Utility::ComparisonTraits<View>::template compare<Policy,0,Utility::Details::incrementRightShift(0)>(
                                                      left_view, "lhs", true,
                                                      right_view, "rhs", true,
                                                      "", oss, true, tol );

  expected_details =
    Utility::ComparisonTraits<View>::template createComparisonHeader<Policy,0>(
                                                      left_view, "lhs", true,
                                                      right_view, "rhs", true,
                                                      "", tol );

  expected_compare_result =
    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                               left_view.size(), "lhs", true,
                                               right_view.size(), "rhs", true,
                                               ".size()", local_oss, true );
  
  for( size_t i = 0; i < left_view.size(); ++i )
  {
    bool local_expected_compare_result =
      Utility::ComparisonTraits<typename View::value_type>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                left_view[i], "lhs", true,
                right_view[i], "rhs", true,
                std::string("[") + Utility::toString(i) + "]", local_oss, true,
                tol );
    
    if( !local_expected_compare_result )
      expected_compare_result = local_expected_compare_result;
  }

  expected_details += (expected_compare_result ? "passed\n" : "failed!\n" );
  expected_details += local_oss.str();
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  local_oss.str( "" );
  local_oss.clear();

  // Details logging - default tolerance, view of const
  compare_result =
    Utility::ComparisonTraits<ViewOfConst>::template compare<Policy,0,Utility::Details::incrementRightShift(0)>(
                                              left_view_of_const, "lhs", false,
                                              right_view, "rhs", false,
                                              "", oss, true );

  expected_details =
    Utility::ComparisonTraits<ViewOfConst>::template createComparisonHeader<Policy,0>(
                                              left_view_of_const, "lhs", false,
                                              right_view, "rhs", false,
                                              "" );

  expected_compare_result =
    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                       left_view_of_const.size(), "lhs", false,
                                       right_view.size(), "rhs", false,
                                       ".size()", local_oss, true );
  
  for( size_t i = 0; i < left_view.size(); ++i )
  {
    bool local_expected_compare_result =
      Utility::ComparisonTraits<typename ViewOfConst::value_type>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                      left_view_of_const[i], "lhs", false,
                      right_view[i], "rhs", false,
                      std::string("[") + Utility::toString(i) + "]", local_oss,
                      true );
        
    if( !local_expected_compare_result )
      expected_compare_result = local_expected_compare_result;
  }

  expected_details += (expected_compare_result ? "passed\n" : "failed!\n" );
  expected_details += local_oss.str();
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  local_oss.str( "" );
  local_oss.clear();

  compare_result =
    Utility::ComparisonTraits<ViewOfConst>::template compare<Policy,0,Utility::Details::incrementRightShift(0)>(
                                             left_view, "lhs", false,
                                             right_view_of_const, "rhs", false,
                                             "", oss, true );

  expected_details =
    Utility::ComparisonTraits<ViewOfConst>::template createComparisonHeader<Policy,0>(
                                             left_view, "lhs", false,
                                             right_view_of_const, "rhs", false,
                                             "" );

  expected_compare_result =
    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                      left_view.size(), "lhs", false,
                                      right_view_of_const.size(), "rhs", false,
                                      ".size()", local_oss, true );
  
  for( size_t i = 0; i < left_view.size(); ++i )
  {
    bool local_expected_compare_result =
      Utility::ComparisonTraits<typename ViewOfConst::value_type>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                      left_view[i], "lhs", false,
                      right_view_of_const[i], "rhs", false,
                      std::string("[") + Utility::toString(i) + "]", local_oss,
                      true );
        
    if( !local_expected_compare_result )
      expected_compare_result = local_expected_compare_result;
  }

  expected_details += (expected_compare_result ? "passed\n" : "failed!\n" );
  expected_details += local_oss.str();
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  local_oss.str( "" );
  local_oss.clear();

  compare_result =
    Utility::ComparisonTraits<ViewOfConst>::template compare<Policy,0,Utility::Details::incrementRightShift(0)>(
                                             left_view_of_const, "lhs", false,
                                             right_view_of_const, "rhs", false,
                                             "", oss, true );

  expected_details =
    Utility::ComparisonTraits<ViewOfConst>::template createComparisonHeader<Policy,0>(
                                             left_view_of_const, "lhs", false,
                                             right_view_of_const, "rhs", false,
                                             "" );

  expected_compare_result =
    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                      left_view_of_const.size(), "lhs", false,
                                      right_view_of_const.size(), "rhs", false,
                                      ".size()", local_oss, true );
  
  for( size_t i = 0; i < left_view.size(); ++i )
  {
    bool local_expected_compare_result =
      Utility::ComparisonTraits<typename ViewOfConst::value_type>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                      left_view_of_const[i], "lhs", false,
                      right_view_of_const[i], "rhs", false,
                      std::string("[") + Utility::toString(i) + "]", local_oss,
                      true );
    
    if( !local_expected_compare_result )
      expected_compare_result = local_expected_compare_result;
  }

  expected_details += (expected_compare_result ? "passed\n" : "failed!\n" );
  expected_details += local_oss.str();
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  local_oss.str( "" );
  local_oss.clear();

  // Details logging - custom tolerance, view of const
  compare_result =
    Utility::ComparisonTraits<ViewOfConst>::template compare<Policy,0,Utility::Details::incrementRightShift(0)>(
                                              left_view_of_const, "lhs", true,
                                              right_view, "rhs", true,
                                              "", oss, true, tol );

  expected_details =
    Utility::ComparisonTraits<ViewOfConst>::template createComparisonHeader<Policy,0>(
                                             left_view_of_const, "lhs", true,
                                             right_view, "rhs", true,
                                             "", tol );

  expected_compare_result =
    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                      left_view_of_const.size(), "lhs", true,
                                      right_view.size(), "rhs", true,
                                      ".size()", local_oss, true );
  
  for( size_t i = 0; i < left_view.size(); ++i )
  {
    bool local_expected_compare_result =
      Utility::ComparisonTraits<typename ViewOfConst::value_type>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                left_view_of_const[i], "lhs", true,
                right_view[i], "rhs", true,
                std::string("[") + Utility::toString(i) + "]", local_oss, true,
                tol );
        
    if( !local_expected_compare_result )
      expected_compare_result = local_expected_compare_result;
  }

  expected_details += (expected_compare_result ? "passed\n" : "failed!\n" );
  expected_details += local_oss.str();
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  local_oss.str( "" );
  local_oss.clear();
  
  compare_result =
    Utility::ComparisonTraits<ViewOfConst>::template compare<Policy,0,Utility::Details::incrementRightShift(0)>(
                                             left_view, "lhs", true,
                                             right_view_of_const, "rhs", true,
                                             "", oss, true, tol );

  expected_details =
    Utility::ComparisonTraits<ViewOfConst>::template createComparisonHeader<Policy,0>(
                                             left_view, "lhs", true,
                                             right_view_of_const, "rhs", true,
                                             "", tol );

  expected_compare_result =
    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                      left_view.size(), "lhs", true,
                                      right_view_of_const.size(), "rhs", true,
                                      ".size()", local_oss, true );
  
  for( size_t i = 0; i < left_view.size(); ++i )
  {
    bool local_expected_compare_result =
      Utility::ComparisonTraits<typename ViewOfConst::value_type>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                left_view[i], "lhs", true,
                right_view_of_const[i], "rhs", true,
                std::string("[") + Utility::toString(i) + "]", local_oss, true,
                tol );

    if( !local_expected_compare_result )
      expected_compare_result = local_expected_compare_result;
  }

  expected_details += (expected_compare_result ? "passed\n" : "failed!\n" );
  expected_details += local_oss.str();
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  local_oss.str( "" );
  local_oss.clear();

  compare_result =
    Utility::ComparisonTraits<ViewOfConst>::template compare<Policy,0,Utility::Details::incrementRightShift(0)>(
                                             left_view_of_const, "lhs", true,
                                             right_view_of_const, "rhs", true,
                                             "", oss, true, tol );

  expected_details =
    Utility::ComparisonTraits<ViewOfConst>::template createComparisonHeader<Policy,0>(
                                             left_view_of_const, "lhs", true,
                                             right_view_of_const, "rhs", true,
                                             "", tol );

  expected_compare_result =
    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                      left_view_of_const.size(), "lhs", true,
                                      right_view_of_const.size(), "rhs", true,
                                      ".size()", local_oss, true );
  
  for( size_t i = 0; i < left_view.size(); ++i )
  {
    bool local_expected_compare_result =
      Utility::ComparisonTraits<typename ViewOfConst::value_type>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                left_view_of_const[i], "lhs", true,
                right_view_of_const[i], "rhs", true,
                std::string("[") + Utility::toString(i) + "]", local_oss, true,
                tol );

    if( !local_expected_compare_result )
      expected_compare_result = local_expected_compare_result;
  }

  expected_details += (expected_compare_result ? "passed\n" : "failed!\n" );
  expected_details += local_oss.str();
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  local_oss.str( "" );
  local_oss.clear();

  // Make sure that these containers do not compare equal
  typedef typename std::remove_const<typename Utility::TupleElement<0,typename View::value_type>::type>::type BasicValueType;
  const_cast<BasicValueType&>(Utility::get<0>(left_view[0])) = initializeValue( 10, BasicValueType() );

  compare_result =
    Utility::ComparisonTraits<ViewOfConst>::template compare<Policy,0,Utility::Details::incrementRightShift(0)>(
                                             left_view_of_const, "lhs", true,
                                             right_view_of_const, "rhs", true,
                                             "", oss, true, tol );

  expected_details =
    Utility::ComparisonTraits<ViewOfConst>::template createComparisonHeader<Policy,0>(
                                             left_view_of_const, "lhs", true,
                                             right_view_of_const, "rhs", true,
                                             "", tol );

  expected_compare_result =
    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                      left_view_of_const.size(), "lhs", true,
                                      right_view_of_const.size(), "rhs", true,
                                      ".size()", local_oss, true );
  
  for( size_t i = 0; i < left_view.size(); ++i )
  {
    bool local_expected_compare_result =
      Utility::ComparisonTraits<typename ViewOfConst::value_type>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                left_view_of_const[i], "lhs", true,
                right_view_of_const[i], "rhs", true,
                std::string("[") + Utility::toString(i) + "]", local_oss, true,
                tol );

    if( !local_expected_compare_result )
      expected_compare_result = local_expected_compare_result;
  }

  expected_details += (expected_compare_result ? "passed\n" : "failed!\n" );
  expected_details += local_oss.str();
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

}

//---------------------------------------------------------------------------//
// Check that two views can be compared
BOOST_AUTO_TEST_CASE_TEMPLATE( compare_inequality,
                               PolicyContainerPair,
                               TestInequalityPolicyContainers )
{
  typedef typename Utility::TupleElement<0,PolicyContainerPair>::type Policy;
  typedef typename Utility::TupleElement<1,PolicyContainerPair>::type Container;
  typedef Utility::View<typename Container::iterator> View;
  typedef Utility::View<typename Container::const_iterator> ViewOfConst;

  Container left_container = initializeContainer<Container>();
  Container right_container = initializeContainer<Container>();
  Container empty_container;

  // Construct a view from iterators
  View left_view( left_container.begin(), left_container.end() );
  ViewOfConst left_view_of_const = left_view.toConst();

  View right_view( right_container.begin(), right_container.end() );
  ViewOfConst right_view_of_const = right_view.toConst();

  View empty_view( empty_container.begin(), empty_container.end() );
  ViewOfConst empty_view_of_const = empty_view.toConst();
  
  std::ostringstream oss;

  // No details logging
  bool compare_result =
    Utility::ComparisonTraits<View>::template compare<Policy,0,0>(
                                                      left_view, "lhs", false,
                                                      right_view, "rhs", false,
                                                      "", oss );

  BOOST_CHECK( !compare_result );
  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::ComparisonTraits<View>::template compare<Policy,0,0>(
                                                      empty_view, "lhs", false,
                                                      right_view, "rhs", false,
                                                      "", oss );

  BOOST_CHECK( compare_result );
  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::ComparisonTraits<View>::template compare<Policy,0,0>(
                                                      left_view, "lhs", false,
                                                      empty_view, "rhs", false,
                                                      "", oss );

  BOOST_CHECK( compare_result );
  BOOST_CHECK_EQUAL( oss.str(), "" );

  // Details logging - default tolerance
  compare_result =
    Utility::ComparisonTraits<View>::template compare<Policy,0,0>(
                                                      left_view, "lhs", false,
                                                      right_view, "rhs", false,
                                                      "", oss, true );

  std::string expected_details =
    Utility::ComparisonTraits<View>::template createComparisonHeader<Policy,0>(
                                                      left_view, "lhs", false,
                                                      right_view, "rhs", false,
                                                      "" ) + "failed!\n";

  BOOST_CHECK( !compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );
  
  oss.str( "" );
  oss.clear();

  compare_result =
    Utility::ComparisonTraits<View>::template compare<Policy,0,0>(
                                                      empty_view, "lhs", false,
                                                      right_view, "rhs", false,
                                                      "", oss, true );

  expected_details =
    Utility::ComparisonTraits<View>::template createComparisonHeader<Policy,0>(
                                                      empty_view, "lhs", false,
                                                      right_view, "rhs", false,
                                                      "" ) + "passed\n";

  BOOST_CHECK( compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );
  
  oss.str( "" );
  oss.clear();

  compare_result =
    Utility::ComparisonTraits<View>::template compare<Policy,0,0>(
                                                      left_view, "lhs", true,
                                                      right_view, "rhs", false,
                                                      "", oss, true );

  expected_details =
    Utility::ComparisonTraits<View>::template createComparisonHeader<Policy,0>(
                                                      left_view, "lhs", true,
                                                      right_view, "rhs", false,
                                                      "" ) + "failed!\n";

  BOOST_CHECK( !compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );
  
  oss.str( "" );
  oss.clear();

  compare_result =
    Utility::ComparisonTraits<View>::template compare<Policy,0,0>(
                                                      empty_view, "lhs", true,
                                                      right_view, "rhs", false,
                                                      "", oss, true );

  expected_details =
    Utility::ComparisonTraits<View>::template createComparisonHeader<Policy,0>(
                                                      empty_view, "lhs", true,
                                                      right_view, "rhs", false,
                                                      "" ) + "passed\n";

  BOOST_CHECK( compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );
  
  oss.str( "" );
  oss.clear();

  compare_result =
    Utility::ComparisonTraits<View>::template compare<Policy,0,0>(
                                                      left_view, "lhs", false,
                                                      right_view, "rhs", true,
                                                      "", oss, true );

  expected_details =
    Utility::ComparisonTraits<View>::template createComparisonHeader<Policy,0>(
                                                      left_view, "lhs", false,
                                                      right_view, "rhs", true,
                                                      "" ) + "failed!\n";

  BOOST_CHECK( !compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );
  
  oss.str( "" );
  oss.clear();

  compare_result =
    Utility::ComparisonTraits<View>::template compare<Policy,0,0>(
                                                      empty_view, "lhs", false,
                                                      right_view, "rhs", true,
                                                      "", oss, true );

  expected_details =
    Utility::ComparisonTraits<View>::template createComparisonHeader<Policy,0>(
                                                      empty_view, "lhs", false,
                                                      right_view, "rhs", true,
                                                      "" ) + "passed\n";

  BOOST_CHECK( compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );
  
  oss.str( "" );
  oss.clear();

  compare_result =
    Utility::ComparisonTraits<View>::template compare<Policy,0,0>(
                                                      left_view, "lhs", true,
                                                      right_view, "rhs", true,
                                                      "", oss, true );

  expected_details =
    Utility::ComparisonTraits<View>::template createComparisonHeader<Policy,0>(
                                                      left_view, "lhs", true,
                                                      right_view, "rhs", true,
                                                      "" ) + "failed!\n";

  BOOST_CHECK( !compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );
  
  oss.str( "" );
  oss.clear();

  compare_result =
    Utility::ComparisonTraits<View>::template compare<Policy,0,0>(
                                                      empty_view, "lhs", true,
                                                      right_view, "rhs", true,
                                                      "", oss, true );

  expected_details =
    Utility::ComparisonTraits<View>::template createComparisonHeader<Policy,0>(
                                                      empty_view, "lhs", true,
                                                      right_view, "rhs", true,
                                                      "" ) + "passed\n";

  BOOST_CHECK( compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );
}

//---------------------------------------------------------------------------//
// Check that two views can be compared
BOOST_AUTO_TEST_CASE_TEMPLATE( compare_equality_helper,
                               PolicyContainerPair,
                               TestEqualityPolicyContainers )
{
  typedef typename Utility::TupleElement<0,PolicyContainerPair>::type Policy;
  typedef typename Utility::TupleElement<1,PolicyContainerPair>::type Container;
  typedef typename Container::value_type T;
  typedef Utility::View<typename Container::iterator> View;
  typedef Utility::View<typename Container::const_iterator> ViewOfConst;

  Container left_container = initializeContainer<Container>();
  Container right_container = initializeContainer<Container>();

  // Construct a view from iterators
  View left_view( left_container.begin(), left_container.end() );
  ViewOfConst left_view_of_const = left_view.toConst();

  View right_view( right_container.begin(), right_container.end() );
  ViewOfConst right_view_of_const = right_view.toConst();
  
  std::ostringstream oss;

  // No details logging
  bool compare_result = Utility::compare<Policy,0,0>( left_view, "lhs",
                                                    right_view, "rhs",
                                                    oss );

  bool expected_compare_result =
    Policy::compare( left_view.size(), right_view.size() );

  for( size_t i = 0; i < left_view.size(); ++i )
  {
    std::ostringstream local_oss;
    bool local_expected_compare_result =
      Utility::ComparisonTraits<typename View::value_type>::template compare<Policy,0,0>(
                                                   left_view[i], "lhs", true,
                                                   right_view[i], "rhs", true,
                                                   "", local_oss, false );
    
    if( !local_expected_compare_result )
      expected_compare_result = local_expected_compare_result;
  }

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0,0>( left_view_of_const, "lhs",
                                               right_view.toConst(), "rhs",
                                               oss );

  expected_compare_result =
    Policy::compare( left_view_of_const.size(), right_view.size() );

  for( size_t i = 0; i < left_view_of_const.size(); ++i )
  {
    std::ostringstream local_oss;
    bool local_expected_compare_result =
      Utility::ComparisonTraits<typename ViewOfConst::value_type>::template compare<Policy,0,0>(
                                            left_view_of_const[i], "lhs", true,
                                            right_view[i], "rhs", true,
                                            "", local_oss, false );
    
    if( !local_expected_compare_result )
      expected_compare_result = local_expected_compare_result;
  }

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0,0>( left_view.toConst(), "lhs",
                                               right_view_of_const, "rhs",
                                               oss );

  expected_compare_result =
    Policy::compare( left_view.size(), right_view_of_const.size() );

  for( size_t i = 0; i < left_view_of_const.size(); ++i )
  {
    std::ostringstream local_oss;
    bool local_expected_compare_result =
      Utility::ComparisonTraits<typename ViewOfConst::value_type>::template compare<Policy,0,0>(
                                           left_view[i], "lhs", true,
                                           right_view_of_const[i], "rhs", true,
                                           "", local_oss, false );
    
    if( !local_expected_compare_result )
      expected_compare_result = local_expected_compare_result;
  }

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0,0>( left_view_of_const, "lhs",
                                               right_view_of_const, "rhs",
                                               oss );

  expected_compare_result =
    Policy::compare( left_view_of_const.size(), right_view_of_const.size() );

  for( size_t i = 0; i < left_view_of_const.size(); ++i )
  {
    std::ostringstream local_oss;
    bool local_expected_compare_result =
      Utility::ComparisonTraits<typename ViewOfConst::value_type>::template compare<Policy,0,0>(
                                           left_view_of_const[i], "lhs", true,
                                           right_view_of_const[i], "rhs", true,
                                           "", local_oss, false );
    
    if( !local_expected_compare_result )
      expected_compare_result = local_expected_compare_result;
  }

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0,0>( {initializeValue(0, T()),
                                                initializeValue(1, T()),
                                                initializeValue(2, T())}, "lhs",
                                               right_view, "rhs",
                                               oss );

  expected_compare_result =
    Policy::compare( size_t(3), right_view.size() );

  if( expected_compare_result )
  {
    for( size_t i = 0; i < 3; ++i )
    {
      std::ostringstream local_oss;
      bool local_expected_compare_result =
        Utility::ComparisonTraits<typename View::value_type>::template compare<Policy,0,0>(
                                         initializeValue(i, T()), "lhs", false,
                                         right_view[i], "rhs", true,
                                         "", local_oss, false );
    
      if( !local_expected_compare_result )
        expected_compare_result = local_expected_compare_result;
    }
  }

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0,0>( left_view, "lhs",
                                               {initializeValue(0, T()),
                                                initializeValue(1, T()),
                                                initializeValue(2, T())}, "rhs",
                                               oss );

  expected_compare_result =
    Policy::compare( left_view.size(), size_t(3) );

  if( expected_compare_result )
  {
    for( size_t i = 0; i < 3; ++i )
    {
      std::ostringstream local_oss;
      bool local_expected_compare_result =
        Utility::ComparisonTraits<typename View::value_type>::template compare<Policy,0,0>(
                                         left_view[i], "lhs", true,
                                         initializeValue(i, T()), "rhs", false,
                                         "", local_oss, false );
    
      if( !local_expected_compare_result )
        expected_compare_result = local_expected_compare_result;
    }
  }

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), "" );

  typedef typename Utility::ComparisonTraits<View>::ExtraDataType ExtraDataType;
  ExtraDataType tol = initializeTolerance( 1e-6, ExtraDataType() );

  compare_result = Utility::compare<Policy,0,0>( left_view, "lhs",
                                               right_view, "rhs",
                                               oss, tol, false );

  expected_compare_result =
    Policy::compare( left_view.size(), right_view.size() );

  for( size_t i = 0; i < left_view.size(); ++i )
  {
    std::ostringstream local_oss;
      bool local_expected_compare_result =
        Utility::ComparisonTraits<typename View::value_type>::template compare<Policy,0,0>(
                                                    left_view[i], "lhs", true,
                                                    right_view[i], "rhs", true,
                                                    "", local_oss, false,
                                                    tol );
    
      if( !local_expected_compare_result )
        expected_compare_result = local_expected_compare_result;
  }

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0,0>( {initializeValue(0, T()),
                                                initializeValue(1, T()),
                                                initializeValue(2, T())}, "lhs",
                                               right_view, "rhs",
                                               oss, tol, false );

  expected_compare_result =
    Policy::compare( size_t(3), right_view.size() );

  if( expected_compare_result )
  {
    for( size_t i = 0; i < 3; ++i )
    {
      std::ostringstream local_oss;
      bool local_expected_compare_result =
        Utility::ComparisonTraits<typename View::value_type>::template compare<Policy,0,0>(
                                         initializeValue(i, T()), "lhs", false,
                                         right_view[i], "rhs", true,
                                         "", local_oss, false,
                                         tol );
    
      if( !local_expected_compare_result )
        expected_compare_result = local_expected_compare_result;
    }
  }

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0,0>( left_view, "lhs",
                                               {initializeValue(0, T()),
                                                initializeValue(1, T()),
                                                initializeValue(2, T())}, "rhs",
                                               oss, tol, false );

  expected_compare_result =
    Policy::compare( left_view.size(), size_t(3) );

  if( expected_compare_result )
  {
    for( size_t i = 0; i < 3; ++i )
    {
      std::ostringstream local_oss;
      bool local_expected_compare_result =
        Utility::ComparisonTraits<typename View::value_type>::template compare<Policy,0,0>(
                                         left_view[i], "lhs", true,
                                         initializeValue(i, T()), "rhs", false,
                                         "", local_oss, false,
                                         tol );
    
      if( !local_expected_compare_result )
        expected_compare_result = local_expected_compare_result;
    }
  }

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), "" );

  // Details logging 
  compare_result = Utility::compare<Policy,0,Utility::Details::incrementRightShift(0)>( left_view, "lhs",
                                               right_view, "rhs",
                                               oss, tol, true );

  std::string expected_details =
    Utility::createComparisonHeader<Policy,0>( left_view, "lhs",
                                               right_view, "rhs",
                                               tol );
  std::ostringstream local_oss;

  expected_compare_result =
    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                               left_view.size(), "lhs", true,
                                               right_view.size(), "rhs", true,
                                               ".size()", local_oss, true );
  
  for( size_t i = 0; i < left_view.size(); ++i )
  {
    bool local_expected_compare_result =
      Utility::ComparisonTraits<typename View::value_type>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
              left_view[i], "lhs", true,
              right_view[i], "rhs", true,
              std::string("[") + Utility::toString(i) + "]", local_oss, true,
              tol );
    if( !local_expected_compare_result )
      expected_compare_result = local_expected_compare_result;
  }
  
  expected_details += (expected_compare_result ? "passed\n" : "failed!\n" );
  expected_details += local_oss.str();
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );
  
  oss.str( "" );
  oss.clear();
  
  local_oss.str( "" );
  local_oss.clear();

  compare_result = Utility::compare<Policy,0,Utility::Details::incrementRightShift(0)>( left_view_of_const, "lhs",
                                               right_view.toConst(), "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( left_view_of_const, "lhs",
                                               right_view.toConst(), "rhs",
                                               tol );
  expected_compare_result =
    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                     left_view_of_const.size(), "lhs", true,
                                     right_view.toConst().size(), "rhs", false,
                                     ".size()", local_oss, true );
  
  for( size_t i = 0; i < left_view.size(); ++i )
  {
    bool local_expected_compare_result =
      Utility::ComparisonTraits<typename ViewOfConst::value_type>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
              left_view_of_const[i], "lhs", true,
              right_view.toConst()[i], "rhs", false,
              std::string("[") + Utility::toString(i) + "]", local_oss, true,
              tol );
    if( !local_expected_compare_result )
      expected_compare_result = local_expected_compare_result;
  }
  
  expected_details += (expected_compare_result ? "passed\n" : "failed!\n" );
  expected_details += local_oss.str();
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );
  
  oss.str( "" );
  oss.clear();
  
  local_oss.str( "" );
  local_oss.clear();

  compare_result = Utility::compare<Policy,0,Utility::Details::incrementRightShift(0)>( left_view.toConst(), "lhs",
                                               right_view_of_const, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( left_view.toConst(), "lhs",
                                               right_view_of_const, "rhs",
                                               tol );
  expected_compare_result =
    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                      left_view.toConst().size(), "lhs", false,
                                      right_view_of_const.size(), "rhs", true,
                                     ".size()", local_oss, true );
  
  for( size_t i = 0; i < left_view.size(); ++i )
  {
    bool local_expected_compare_result =
      Utility::ComparisonTraits<typename ViewOfConst::value_type>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
              left_view.toConst()[i], "lhs", false,
              right_view_of_const[i], "rhs", true,
              std::string("[") + Utility::toString(i) + "]", local_oss, true,
              tol );
    if( !local_expected_compare_result )
      expected_compare_result = local_expected_compare_result;
  }
  
  expected_details += (expected_compare_result ? "passed\n" : "failed!\n" );
  expected_details += local_oss.str();
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );
  
  oss.str( "" );
  oss.clear();
  
  local_oss.str( "" );
  local_oss.clear();

  compare_result = Utility::compare<Policy,0,Utility::Details::incrementRightShift(0)>( left_view_of_const, "lhs",
                                               right_view_of_const, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( left_view_of_const, "lhs",
                                               right_view_of_const, "rhs",
                                               tol );
  expected_compare_result =
    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                       left_view_of_const.size(), "lhs", true,
                                       right_view_of_const.size(), "rhs", true,
                                       ".size()", local_oss, true );
  
  for( size_t i = 0; i < left_view.size(); ++i )
  {
    bool local_expected_compare_result =
      Utility::ComparisonTraits<typename ViewOfConst::value_type>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
              left_view_of_const[i], "lhs", true,
              right_view_of_const[i], "rhs", true,
              std::string("[") + Utility::toString(i) + "]", local_oss, true,
              tol );
    if( !local_expected_compare_result )
      expected_compare_result = local_expected_compare_result;
  }
  
  expected_details += (expected_compare_result ? "passed\n" : "failed!\n" );
  expected_details += local_oss.str();
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );
  
  oss.str( "" );
  oss.clear();
  
  local_oss.str( "" );
  local_oss.clear();

  compare_result = Utility::compare<Policy,0,Utility::Details::incrementRightShift(0)>( {initializeValue(0, T()),
                                                initializeValue(1, T()),
                                                initializeValue(2, T())}, "lhs",
                                               right_view, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( {initializeValue(0, T()),
                                                initializeValue(1, T()),
                                                initializeValue(2, T())}, "lhs",
                                               right_view, "rhs",
                                               tol );
  expected_compare_result =
    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                                size_t(3), "lhs", false,
                                                right_view.size(), "rhs", true,
                                                ".size()", local_oss, true );

  if( expected_compare_result )
  {
    for( size_t i = 0; i < left_view.size(); ++i )
    {
      bool local_expected_compare_result =
        Utility::ComparisonTraits<typename ViewOfConst::value_type>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
              initializeValue(i, T()), "lhs", false,
              right_view[i], "rhs", true,
              std::string("[") + Utility::toString(i) + "]", local_oss, true,
              tol );
      if( !local_expected_compare_result )
        expected_compare_result = local_expected_compare_result;
    }
  }
  
  expected_details += (expected_compare_result ? "passed\n" : "failed!\n" );
  expected_details += local_oss.str();
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );
  
  oss.str( "" );
  oss.clear();
  
  local_oss.str( "" );
  local_oss.clear();

  compare_result = Utility::compare<Policy,0,Utility::Details::incrementRightShift(0)>( {initializeValue(0, T()),
                                                initializeValue(1, T()),
                                                initializeValue(2, T())}, "lhs",
                                               right_view_of_const, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( {initializeValue(0, T()),
                                                initializeValue(1, T()),
                                                initializeValue(2, T())}, "lhs",
                                               right_view_of_const, "rhs",
                                               tol );
  expected_compare_result =
    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                       size_t(3), "lhs", false,
                                       right_view_of_const.size(), "rhs", true,
                                       ".size()", local_oss, true );

  if( expected_compare_result )
  {
    for( size_t i = 0; i < left_view.size(); ++i )
    {
      bool local_expected_compare_result =
        Utility::ComparisonTraits<typename ViewOfConst::value_type>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
              initializeValue(i, T()), "lhs", false,
              right_view_of_const[i], "rhs", true,
              std::string("[") + Utility::toString(i) + "]", local_oss, true,
              tol );
      if( !local_expected_compare_result )
        expected_compare_result = local_expected_compare_result;
    }
  }
  
  expected_details += (expected_compare_result ? "passed\n" : "failed!\n" );
  expected_details += local_oss.str();
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );
  
  oss.str( "" );
  oss.clear();
  
  local_oss.str( "" );
  local_oss.clear();

  compare_result = Utility::compare<Policy,0,Utility::Details::incrementRightShift(0)>( left_view, "lhs",
                                               {initializeValue(0, T()),
                                                initializeValue(1, T()),
                                                initializeValue(2, T())}, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( left_view, "lhs",
                                               {initializeValue(0, T()),
                                                initializeValue(1, T()),
                                                initializeValue(2, T())}, "rhs",
                                               tol );
  expected_compare_result =
    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                                left_view.size(), "lhs", true,
                                                size_t(3), "rhs", false,
                                                ".size()", local_oss, true );

  if( expected_compare_result )
  {
    for( size_t i = 0; i < left_view.size(); ++i )
    {
      bool local_expected_compare_result =
        Utility::ComparisonTraits<typename ViewOfConst::value_type>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
              left_view[i], "lhs", true,
              initializeValue(i, T()), "rhs", false,
              std::string("[") + Utility::toString(i) + "]", local_oss, true,
              tol );
      if( !local_expected_compare_result )
        expected_compare_result = local_expected_compare_result;
    }
  }
  
  expected_details += (expected_compare_result ? "passed\n" : "failed!\n" );
  expected_details += local_oss.str();
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );
  
  oss.str( "" );
  oss.clear();
  
  local_oss.str( "" );
  local_oss.clear();

  compare_result = Utility::compare<Policy,0,Utility::Details::incrementRightShift(0)>( left_view_of_const, "lhs",
                                               {initializeValue(0, T()),
                                                initializeValue(1, T()),
                                                initializeValue(2, T())}, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( left_view_of_const, "lhs",
                                               {initializeValue(0, T()),
                                                initializeValue(1, T()),
                                                initializeValue(2, T())}, "rhs",
                                               tol );
  expected_compare_result =
    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                        left_view_of_const.size(), "lhs", true,
                                        size_t(3), "rhs", false,
                                        ".size()", local_oss, true );

  if( expected_compare_result )
  {
    for( size_t i = 0; i < left_view.size(); ++i )
    {
      bool local_expected_compare_result =
        Utility::ComparisonTraits<typename ViewOfConst::value_type>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
              left_view_of_const[i], "lhs", true,
              initializeValue(i, T()), "rhs", false,
              std::string("[") + Utility::toString(i) + "]", local_oss, true,
              tol );
      if( !local_expected_compare_result )
        expected_compare_result = local_expected_compare_result;
    }
  }
  
  expected_details += (expected_compare_result ? "passed\n" : "failed!\n" );
  expected_details += local_oss.str();
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );
}

//---------------------------------------------------------------------------//
// Check that two views can be compared
BOOST_AUTO_TEST_CASE_TEMPLATE( compare_inequality_helper,
                               PolicyContainerPair,
                               TestInequalityPolicyContainers )
{
  typedef typename Utility::TupleElement<0,PolicyContainerPair>::type Policy;
  typedef typename Utility::TupleElement<1,PolicyContainerPair>::type Container;
  typedef typename Container::value_type T;
  typedef Utility::View<typename Container::iterator> View;
  typedef Utility::View<typename Container::const_iterator> ViewOfConst;

  Container left_container = initializeContainer<Container>();
  Container right_container = initializeContainer<Container>();
  Container empty_container;

  // Construct a view from iterators
  View left_view( left_container.begin(), left_container.end() );
  ViewOfConst left_view_of_const = left_view.toConst();

  View right_view( right_container.begin(), right_container.end() );
  ViewOfConst right_view_of_const = right_view.toConst();

  View empty_view( empty_container.begin(), empty_container.end() );
  ViewOfConst empty_view_of_const = empty_view.toConst();
  
  std::ostringstream oss;

  // No details logging
  bool compare_result = Utility::compare<Policy,0,0>( left_view, "lhs",
                                                    right_view, "rhs",
                                                    oss );

  BOOST_CHECK( !compare_result );
  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0,0>( empty_view, "lhs",
                                               right_view, "rhs",
                                               oss );

  BOOST_CHECK( compare_result );
  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0,0>( left_view, "lhs",
                                               empty_view, "rhs",
                                               oss );

  BOOST_CHECK( compare_result );
  BOOST_CHECK_EQUAL( oss.str(), "" );

  // Details logging
  typedef typename Utility::ComparisonTraits<View>::ExtraDataType ExtraDataType;
  ExtraDataType tol = initializeTolerance( 1e-6, ExtraDataType() );
  
  compare_result = Utility::compare<Policy,0,0>( left_view, "lhs",
                                               right_view, "rhs",
                                               oss, tol, true );

  std::string expected_details =
    Utility::createComparisonHeader<Policy,0>( left_view, "lhs",
                                               right_view, "rhs",
                                               tol ) + "failed!\n";

  BOOST_CHECK( !compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0,0>( empty_view, "lhs",
                                               right_view, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( empty_view, "lhs",
                                               right_view, "rhs",
                                               tol ) + "passed\n";

  BOOST_CHECK( compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0,0>( left_view, "lhs",
                                               empty_view, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( left_view, "lhs",
                                               empty_view, "rhs",
                                               tol ) + "passed\n";

  BOOST_CHECK( compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0,0>( {}, "lhs",
                                               right_view, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( {}, "lhs",
                                               right_view, "rhs",
                                               tol ) + "passed\n";

  BOOST_CHECK( compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0,0>( left_view, "lhs",
                                               {}, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( left_view, "lhs",
                                               {}, "rhs",
                                               tol ) + "passed\n";

  BOOST_CHECK( compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );
}

//---------------------------------------------------------------------------//
// end tstView.cpp
//---------------------------------------------------------------------------//
