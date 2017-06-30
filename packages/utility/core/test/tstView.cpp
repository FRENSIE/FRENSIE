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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_View.hpp"
#include "Utility_Tuple.hpp"

typedef unsigned char uchar;
typedef signed char schar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef long long longlong;
typedef unsigned long long ulonglong;

typedef std::string string;
typedef std::array<int,1> array_int_1;
typedef std::array<double,2> array_double_2;
typedef std::vector<int> array_int;
typedef std::vector<double> vector_double;
typedef std::vector<int> vector_int;
typedef std::vector<bool> vector_bool;
typedef std::list<double> list_double;
typedef std::list<int> list_int;
typedef std::forward_list<double> forward_list_double;
typedef std::forward_list<int> forward_list_int;
typedef std::deque<double> deque_double;
typedef std::deque<int> deque_int;
typedef std::set<int> set_int;
typedef std::set<std::string> set_string;
typedef std::unordered_set<int> unordered_set_int;
typedef std::unordered_set<std::string> unordered_set_string;
typedef std::map<int,double> map_int_double;
typedef std::map<long,std::string> map_long_string;
typedef std::unordered_map<int,double> unordered_map_int_double;
typedef std::unordered_map<long,std::string> unordered_map_long_string;

//---------------------------------------------------------------------------//
// Instantiation Macros
//---------------------------------------------------------------------------//
#define UNIT_TEST_TEMPLATE_1_INSTANT( type, name )      \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, string );   \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, array_int_1 ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, vector_int ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, list_int ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, forward_list_int ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, deque_int );        \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, set_int );          \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, unordered_set_int ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, map_int_double );   \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, unordered_map_int_double )

#define UNIT_TEST_TEMPLATE_1_BIDIR_CONTAINER_INSTANT( type, name )      \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, string );   \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, array_int_1 ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, vector_int ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, list_int ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, deque_int );        \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, set_int );          \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, map_int_double )

#define UNIT_TEST_TEMPLATE_1_BASIC_INSTANT( type, name )        \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, bool );       \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, char );         \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, schar );       \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, uchar );       \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, short );        \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, ushort );      \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, int );           \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, uint );           \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, long );      \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, ulong );         \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, longlong );       \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, ulonglong );       \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, float );           \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, double )

//---------------------------------------------------------------------------//
// Testing functions
//---------------------------------------------------------------------------//
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
{ container.resize( 10, 0 ); }

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
// Check that a view can be constructed
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( View, default_constructor, Container )
{
  Utility::View<typename Container::iterator> view;

  TEST_EQUALITY_CONST( view.size(), 0 );
  TEST_ASSERT( view.empty() );

  Utility::View<typename Container::const_iterator> view_of_const;

  TEST_EQUALITY_CONST( view_of_const.size(), 0 );
  TEST_ASSERT( view.empty() );
}

UNIT_TEST_TEMPLATE_1_INSTANT( View, default_constructor );

//---------------------------------------------------------------------------//
// Check that a view can be constructed from iterators
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( View, iterator_constructor, Container )
{
  Container container = initializeContainer<Container>();

  // Construct a view from iterators
  {
    Utility::View<typename Container::iterator>
      view( container.begin(), container.end() );

    TEST_EQUALITY( view.size(), size(container) );
    TEST_ASSERT( !view.empty() );
  }

  // Construct a view of const from iterators
  {
    Utility::View<typename Container::const_iterator>
      view( container.begin(), container.end() );

    TEST_EQUALITY( view.size(), size(container) );
    TEST_ASSERT( !view.empty() );
  }

  // Construct a view of const from const iterators
  {
    Utility::View<typename Container::const_iterator>
      view( container.cbegin(), container.cend() );

    TEST_EQUALITY( view.size(), size(container) );
    TEST_ASSERT( !view.empty() );
  }
}

UNIT_TEST_TEMPLATE_1_INSTANT( View, iterator_constructor );

//---------------------------------------------------------------------------//
// Check the copy constructor
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( View, copy_constructor, Container )
{
  Container container = initializeContainer<Container>();

  Utility::View<typename Container::iterator>
    view( container.begin(), container.end() );

  Utility::View<typename Container::const_iterator>
    view_of_const( container.cbegin(), container.cend() );

  {
    Utility::View<typename Container::iterator> view_copy( view );

    TEST_EQUALITY_CONST( view_copy.size(), view.size() );
  }

  {
    Utility::View<typename Container::const_iterator>
      view_of_const_copy( view );

    TEST_EQUALITY_CONST( view_of_const_copy.size(), view.size() );
  }

  {
    Utility::View<typename Container::const_iterator>
      view_of_const_copy( view_of_const );

    TEST_EQUALITY_CONST( view_of_const_copy.size(), view_of_const.size() );
  }
}

UNIT_TEST_TEMPLATE_1_INSTANT( View, copy_constructor );

//---------------------------------------------------------------------------//
// Check the assignment operator
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( View, assignment_operator, Container )
{
  Container container = initializeContainer<Container>();

  Utility::View<typename Container::iterator>
    view( container.begin(), container.end() );

  Utility::View<typename Container::const_iterator>
    view_of_const( container.cbegin(), container.cend() );

  {
    Utility::View<typename Container::iterator> view_copy = view;

    TEST_EQUALITY_CONST( view_copy.size(), view.size() );
  }

  {
    Utility::View<typename Container::const_iterator>
      view_of_const_copy = view;

    TEST_EQUALITY_CONST( view_of_const_copy.size(), view.size() );
  }

  {
    Utility::View<typename Container::const_iterator>
      view_of_const_copy = view_of_const;

    TEST_EQUALITY_CONST( view_of_const_copy.size(), view_of_const.size() );
  }
}

UNIT_TEST_TEMPLATE_1_INSTANT( View, assignment_operator );

//---------------------------------------------------------------------------//
// Check that view iterators can be acquired
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( View, iterator, Container )
{
  Container container = initializeContainer<Container>();

  Utility::View<typename Container::iterator>
    view( container.begin(), container.end() );

  TEST_ASSERT( view.begin() == container.begin() );
  TEST_ASSERT( view.end() == container.end() );
  TEST_ASSERT( view.cbegin() == container.cbegin() );
  TEST_ASSERT( view.cend() == container.cend() );

  Utility::View<typename Container::const_iterator>
    view_of_const( container.cbegin(), container.cend() );

  TEST_ASSERT( view_of_const.begin() == container.cbegin() );
  TEST_ASSERT( view_of_const.end() == container.cend() );
  TEST_ASSERT( view_of_const.cbegin() == container.cbegin() );
  TEST_ASSERT( view_of_const.cend() == container.cend() );
}

UNIT_TEST_TEMPLATE_1_INSTANT( View, iterator );

//---------------------------------------------------------------------------//
// Check if a view can be converted to a view-of-const
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( View, to_const, Container )
{
  Container container = initializeContainer<Container>();

  Utility::View<typename Container::iterator>
    view( container.begin(), container.end() );

  {
    auto view_of_const = view.toConst();

    TEST_ASSERT( Utility::IsPointerToConst<typename decltype(view_of_const)::pointer>::value );
  }
  
  {
    auto view_of_const =
      (Utility::View<typename Container::const_iterator>)view;

    TEST_ASSERT( Utility::IsPointerToConst<typename decltype(view_of_const)::pointer>::value );
  }
}

UNIT_TEST_TEMPLATE_1_INSTANT( View, to_const );

//---------------------------------------------------------------------------//
// Check if a view can be constructed using the view helper function
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( View, view_construction_helper, Container )
{
  Container container = initializeContainer<Container>();

  auto view = Utility::view( container );

  TEST_EQUALITY_CONST( view.size(), size(container) );
  TEST_ASSERT( view.begin() == container.begin() );
  TEST_ASSERT( view.end() == container.end() );
  TEST_ASSERT( (std::is_same<typename decltype(view)::iterator,typename Container::iterator>::value) );

  auto view_to_const =
    Utility::view( const_cast<const Container&>(container) );

  TEST_EQUALITY_CONST( view_to_const.size(), size(container) );
  TEST_ASSERT( view_to_const.begin() == container.cbegin() );
  TEST_ASSERT( view_to_const.end() == container.cend() );
  TEST_ASSERT( (std::is_same<typename decltype(view_to_const)::iterator,typename Container::const_iterator>::value) );
}

UNIT_TEST_TEMPLATE_1_INSTANT( View, view_construction_helper );

//---------------------------------------------------------------------------//
// Check if a reverse view can be constructed using the reverseView helper
// function
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( View,
                                   reverse_view_construction_helper,
                                   Container )
{
  Container container = initializeContainer<Container>();

  auto reverse_view = Utility::reverseView( container );

  TEST_EQUALITY_CONST( reverse_view.size(), size(container) );
  TEST_ASSERT( reverse_view.begin() == container.rbegin() );
  TEST_ASSERT( reverse_view.end() == container.rend() );
  TEST_ASSERT( (std::is_same<typename decltype(reverse_view)::iterator,typename Container::reverse_iterator>::value) );

  auto reverse_view_to_const =
    Utility::reverseView( const_cast<const Container&>(container) );

  TEST_EQUALITY_CONST( reverse_view_to_const.size(), size(container) );
  TEST_ASSERT( reverse_view_to_const.begin() == container.crbegin() );
  TEST_ASSERT( reverse_view_to_const.end() == container.crend() );
  TEST_ASSERT( (std::is_same<typename decltype(reverse_view_to_const)::iterator,typename Container::const_reverse_iterator>::value) );
}

UNIT_TEST_TEMPLATE_1_BIDIR_CONTAINER_INSTANT( View, reverse_view_construction_helper );

//---------------------------------------------------------------------------//
// Check that a view can be converted to a string
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( View, toString, Container )
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
  
  TEST_EQUALITY( Utility::toString(Utility::view( container )),
                 container_string );
  TEST_EQUALITY( Utility::toString(Utility::viewOfConst( container )),
                 container_string );
}

UNIT_TEST_TEMPLATE_1_INSTANT( View, toString );

//---------------------------------------------------------------------------//
// Check that a view can be placed in a stream
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( View, ostream_operator, Container )
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

  TEST_EQUALITY( oss.str(), container_string );

  oss.str( "" );
  oss.clear();

  oss << Utility::viewOfConst( container );
  
  TEST_EQUALITY( oss.str(), container_string );
}

UNIT_TEST_TEMPLATE_1_INSTANT( View, ostream_operator );

//---------------------------------------------------------------------------//
// Check the element access for std::array views
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( View_array, element_access, T )
{
  std::array<T,2> container( {0, 1} );

  Utility::View<typename std::array<T,2>::iterator>
    view( container.begin(), container.end() );

  TEST_EQUALITY_CONST( view[0], 0 );
  TEST_EQUALITY_CONST( view[1], 1 );
  TEST_EQUALITY_CONST( view.at(0), 0 );
  TEST_EQUALITY_CONST( view.at(1), 1 );
  TEST_EQUALITY_CONST( view.front(), 0 );
  TEST_EQUALITY_CONST( view.back(), 1 );

  view[0] = 1;
  view[1] = 0;

  TEST_EQUALITY_CONST( view[0], 1 );
  TEST_EQUALITY_CONST( view[1], 0 );
  TEST_EQUALITY_CONST( view.at(0), 1 );
  TEST_EQUALITY_CONST( view.at(1), 0 );
  TEST_EQUALITY_CONST( view.front(), 1 );
  TEST_EQUALITY_CONST( view.back(), 0 );

  Utility::View<typename std::array<T,2>::reverse_iterator>
    reverse_view( container.rbegin(), container.rend() );

  reverse_view[0] = 1;
  reverse_view[1] = 0;

  TEST_EQUALITY_CONST( reverse_view[0], 1 );
  TEST_EQUALITY_CONST( reverse_view[1], 0 );
  TEST_EQUALITY_CONST( reverse_view.at(0), 1 );
  TEST_EQUALITY_CONST( reverse_view.at(1), 0 );
  TEST_EQUALITY_CONST( reverse_view.front(), 1 );
  TEST_EQUALITY_CONST( reverse_view.back(), 0 );
  TEST_EQUALITY_CONST( view[0], 0 );
  TEST_EQUALITY_CONST( view[1], 1 );

  container[0] = 1;
  container[1] = 0;

  TEST_EQUALITY_CONST( view[0], 1 );
  TEST_EQUALITY_CONST( view[1], 0 );
  TEST_EQUALITY_CONST( reverse_view[0], 0 );
  TEST_EQUALITY_CONST( reverse_view[1], 1 );

  Utility::View<typename std::array<T,2>::const_iterator>
    view_of_const( container.begin(), container.end() );

  TEST_EQUALITY_CONST( view_of_const[0], 1 );
  TEST_EQUALITY_CONST( view_of_const[1], 0 );
  TEST_EQUALITY_CONST( view_of_const.at(0), 1 );
  TEST_EQUALITY_CONST( view_of_const.at(1), 0 );
  TEST_EQUALITY_CONST( view_of_const.front(), 1 );
  TEST_EQUALITY_CONST( view_of_const.back(), 0 );

  Utility::View<typename std::array<T,2>::const_reverse_iterator>
    reverse_view_of_const( container.rbegin(), container.rend() );

  TEST_EQUALITY_CONST( reverse_view_of_const[0], 0 );
  TEST_EQUALITY_CONST( reverse_view_of_const[1], 1 );
  TEST_EQUALITY_CONST( reverse_view_of_const.at(0), 0 );
  TEST_EQUALITY_CONST( reverse_view_of_const.at(1), 1 );
  TEST_EQUALITY_CONST( reverse_view_of_const.front(), 0 );
  TEST_EQUALITY_CONST( reverse_view_of_const.back(), 1 );
}

UNIT_TEST_TEMPLATE_1_BASIC_INSTANT( View_array, element_access );

//---------------------------------------------------------------------------//
// Check the element access for vector views
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( View_vector, element_access, T )
{
  std::vector<T> container( {0, 1} );

  Utility::View<typename std::vector<T>::iterator>
    view( container.begin(), container.end() );

  TEST_EQUALITY_CONST( view[0], 0 );
  TEST_EQUALITY_CONST( view[1], 1 );
  TEST_EQUALITY_CONST( view.at(0), 0 );
  TEST_EQUALITY_CONST( view.at(1), 1 );
  TEST_EQUALITY_CONST( view.front(), 0 );
  TEST_EQUALITY_CONST( view.back(), 1 );

  view[0] = 1;
  view[1] = 0;

  TEST_EQUALITY_CONST( view[0], 1 );
  TEST_EQUALITY_CONST( view[1], 0 );
  TEST_EQUALITY_CONST( view.at(0), 1 );
  TEST_EQUALITY_CONST( view.at(1), 0 );
  TEST_EQUALITY_CONST( view.front(), 1 );
  TEST_EQUALITY_CONST( view.back(), 0 );

  Utility::View<typename std::vector<T>::reverse_iterator>
    reverse_view( container.rbegin(), container.rend() );

  reverse_view[0] = 1;
  reverse_view[1] = 0;

  TEST_EQUALITY_CONST( reverse_view[0], 1 );
  TEST_EQUALITY_CONST( reverse_view[1], 0 );
  TEST_EQUALITY_CONST( reverse_view.at(0), 1 );
  TEST_EQUALITY_CONST( reverse_view.at(1), 0 );
  TEST_EQUALITY_CONST( reverse_view.front(), 1 );
  TEST_EQUALITY_CONST( reverse_view.back(), 0 );
  TEST_EQUALITY_CONST( view[0], 0 );
  TEST_EQUALITY_CONST( view[1], 1 );

  container[0] = 1;
  container[1] = 0;

  TEST_EQUALITY_CONST( view[0], 1 );
  TEST_EQUALITY_CONST( view[1], 0 );
  TEST_EQUALITY_CONST( reverse_view[0], 0 );
  TEST_EQUALITY_CONST( reverse_view[1], 1 );

  Utility::View<typename std::vector<T>::const_iterator>
    view_of_const( container.begin(), container.end() );

  TEST_EQUALITY_CONST( view_of_const[0], 1 );
  TEST_EQUALITY_CONST( view_of_const[1], 0 );
  TEST_EQUALITY_CONST( view_of_const.at(0), 1 );
  TEST_EQUALITY_CONST( view_of_const.at(1), 0 );
  TEST_EQUALITY_CONST( view_of_const.front(), 1 );
  TEST_EQUALITY_CONST( view_of_const.back(), 0 );

  Utility::View<typename std::vector<T>::const_reverse_iterator>
    reverse_view_of_const( container.rbegin(), container.rend() );

  TEST_EQUALITY_CONST( reverse_view_of_const[0], 0 );
  TEST_EQUALITY_CONST( reverse_view_of_const[1], 1 );
  TEST_EQUALITY_CONST( reverse_view_of_const.at(0), 0 );
  TEST_EQUALITY_CONST( reverse_view_of_const.at(1), 1 );
  TEST_EQUALITY_CONST( reverse_view_of_const.front(), 0 );
  TEST_EQUALITY_CONST( reverse_view_of_const.back(), 1 );
}

UNIT_TEST_TEMPLATE_1_BASIC_INSTANT( View_vector, element_access );

//---------------------------------------------------------------------------//
// Check the element access for list views
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( View_list, element_access, T )
{
  std::list<T> container( {0, 1} );

  Utility::View<typename std::list<T>::iterator>
    view( container.begin(), container.end() );

  TEST_EQUALITY_CONST( view[0], 0 );
  TEST_EQUALITY_CONST( view[1], 1 );
  TEST_EQUALITY_CONST( view.at(0), 0 );
  TEST_EQUALITY_CONST( view.at(1), 1 );
  TEST_EQUALITY_CONST( view.front(), 0 );
  TEST_EQUALITY_CONST( view.back(), 1 );

  view[0] = 1;
  view[1] = 0;

  TEST_EQUALITY_CONST( view[0], 1 );
  TEST_EQUALITY_CONST( view[1], 0 );
  TEST_EQUALITY_CONST( view.at(0), 1 );
  TEST_EQUALITY_CONST( view.at(1), 0 );
  TEST_EQUALITY_CONST( view.front(), 1 );
  TEST_EQUALITY_CONST( view.back(), 0 );

  Utility::View<typename std::list<T>::reverse_iterator>
    reverse_view( container.rbegin(), container.rend() );

  reverse_view[0] = 1;
  reverse_view[1] = 0;

  TEST_EQUALITY_CONST( reverse_view[0], 1 );
  TEST_EQUALITY_CONST( reverse_view[1], 0 );
  TEST_EQUALITY_CONST( reverse_view.at(0), 1 );
  TEST_EQUALITY_CONST( reverse_view.at(1), 0 );
  TEST_EQUALITY_CONST( reverse_view.front(), 1 );
  TEST_EQUALITY_CONST( reverse_view.back(), 0 );
  TEST_EQUALITY_CONST( view[0], 0 );
  TEST_EQUALITY_CONST( view[1], 1 );

  container.front() = 1;
  container.back() = 0;

  TEST_EQUALITY_CONST( view[0], 1 );
  TEST_EQUALITY_CONST( view[1], 0 );
  TEST_EQUALITY_CONST( reverse_view[0], 0 );
  TEST_EQUALITY_CONST( reverse_view[1], 1 );

  Utility::View<typename std::list<T>::const_iterator>
    view_of_const( container.begin(), container.end() );

  TEST_EQUALITY_CONST( view_of_const[0], 1 );
  TEST_EQUALITY_CONST( view_of_const[1], 0 );
  TEST_EQUALITY_CONST( view_of_const.at(0), 1 );
  TEST_EQUALITY_CONST( view_of_const.at(1), 0 );
  TEST_EQUALITY_CONST( view_of_const.front(), 1 );
  TEST_EQUALITY_CONST( view_of_const.back(), 0 );

  Utility::View<typename std::list<T>::const_reverse_iterator>
    reverse_view_of_const( container.rbegin(), container.rend() );

  TEST_EQUALITY_CONST( reverse_view_of_const[0], 0 );
  TEST_EQUALITY_CONST( reverse_view_of_const[1], 1 );
  TEST_EQUALITY_CONST( reverse_view_of_const.at(0), 0 );
  TEST_EQUALITY_CONST( reverse_view_of_const.at(1), 1 );
  TEST_EQUALITY_CONST( reverse_view_of_const.front(), 0 );
  TEST_EQUALITY_CONST( reverse_view_of_const.back(), 1 );
}

UNIT_TEST_TEMPLATE_1_BASIC_INSTANT( View_list, element_access );

//---------------------------------------------------------------------------//
// Check the element access for forward_list views
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( View_forward_list, element_access, T )
{
  std::forward_list<T> container( {0, 1} );

  Utility::View<typename std::forward_list<T>::iterator>
    view( container.begin(), container.end() );

  TEST_EQUALITY_CONST( view[0], 0 );
  TEST_EQUALITY_CONST( view[1], 1 );
  TEST_EQUALITY_CONST( view.at(0), 0 );
  TEST_EQUALITY_CONST( view.at(1), 1 );
  TEST_EQUALITY_CONST( view.front(), 0 );
  TEST_EQUALITY_CONST( view.back(), 1 );

  view[0] = 1;
  view[1] = 0;

  TEST_EQUALITY_CONST( view[0], 1 );
  TEST_EQUALITY_CONST( view[1], 0 );
  TEST_EQUALITY_CONST( view.at(0), 1 );
  TEST_EQUALITY_CONST( view.at(1), 0 );
  TEST_EQUALITY_CONST( view.front(), 1 );
  TEST_EQUALITY_CONST( view.back(), 0 );

  container.front() = 1;
  *(++container.begin()) = 0;

  Utility::View<typename std::forward_list<T>::const_iterator>
    view_of_const( container.begin(), container.end() );

  TEST_EQUALITY_CONST( view_of_const[0], 1 );
  TEST_EQUALITY_CONST( view_of_const[1], 0 );
  TEST_EQUALITY_CONST( view_of_const.at(0), 1 );
  TEST_EQUALITY_CONST( view_of_const.at(1), 0 );
  TEST_EQUALITY_CONST( view_of_const.front(), 1 );
  TEST_EQUALITY_CONST( view_of_const.back(), 0 );
}

UNIT_TEST_TEMPLATE_1_BASIC_INSTANT( View_forward_list, element_access );

//---------------------------------------------------------------------------//
// Check the element access for deque views
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( View_deque, element_access, T )
{
  std::deque<T> container( {0, 1} );

  Utility::View<typename std::deque<T>::iterator>
    view( container.begin(), container.end() );

  TEST_EQUALITY_CONST( view[0], 0 );
  TEST_EQUALITY_CONST( view[1], 1 );
  TEST_EQUALITY_CONST( view.at(0), 0 );
  TEST_EQUALITY_CONST( view.at(1), 1 );
  TEST_EQUALITY_CONST( view.front(), 0 );
  TEST_EQUALITY_CONST( view.back(), 1 );

  view[0] = 1;
  view[1] = 0;

  TEST_EQUALITY_CONST( view[0], 1 );
  TEST_EQUALITY_CONST( view[1], 0 );
  TEST_EQUALITY_CONST( view.at(0), 1 );
  TEST_EQUALITY_CONST( view.at(1), 0 );
  TEST_EQUALITY_CONST( view.front(), 1 );
  TEST_EQUALITY_CONST( view.back(), 0 );

  Utility::View<typename std::deque<T>::reverse_iterator>
    reverse_view( container.rbegin(), container.rend() );

  reverse_view[0] = 1;
  reverse_view[1] = 0;

  TEST_EQUALITY_CONST( reverse_view[0], 1 );
  TEST_EQUALITY_CONST( reverse_view[1], 0 );
  TEST_EQUALITY_CONST( reverse_view.at(0), 1 );
  TEST_EQUALITY_CONST( reverse_view.at(1), 0 );
  TEST_EQUALITY_CONST( reverse_view.front(), 1 );
  TEST_EQUALITY_CONST( reverse_view.back(), 0 );
  TEST_EQUALITY_CONST( view[0], 0 );
  TEST_EQUALITY_CONST( view[1], 1 );

  container.front() = 1;
  container.back() = 0;

  TEST_EQUALITY_CONST( view[0], 1 );
  TEST_EQUALITY_CONST( view[1], 0 );
  TEST_EQUALITY_CONST( reverse_view[0], 0 );
  TEST_EQUALITY_CONST( reverse_view[1], 1 );

  Utility::View<typename std::deque<T>::const_iterator>
    view_of_const( container.begin(), container.end() );

  TEST_EQUALITY_CONST( view_of_const[0], 1 );
  TEST_EQUALITY_CONST( view_of_const[1], 0 );
  TEST_EQUALITY_CONST( view_of_const.at(0), 1 );
  TEST_EQUALITY_CONST( view_of_const.at(1), 0 );
  TEST_EQUALITY_CONST( view_of_const.front(), 1 );
  TEST_EQUALITY_CONST( view_of_const.back(), 0 );

  Utility::View<typename std::deque<T>::const_reverse_iterator>
    reverse_view_of_const( container.rbegin(), container.rend() );

  TEST_EQUALITY_CONST( reverse_view_of_const[0], 0 );
  TEST_EQUALITY_CONST( reverse_view_of_const[1], 1 );
  TEST_EQUALITY_CONST( reverse_view_of_const.at(0), 0 );
  TEST_EQUALITY_CONST( reverse_view_of_const.at(1), 1 );
  TEST_EQUALITY_CONST( reverse_view_of_const.front(), 0 );
  TEST_EQUALITY_CONST( reverse_view_of_const.back(), 1 );
}

UNIT_TEST_TEMPLATE_1_BASIC_INSTANT( View_deque, element_access );

//---------------------------------------------------------------------------//
// Check the element access for set views
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( View_set, element_access, T )
{
  std::set<T> container( {0, 1} );

  Utility::View<typename std::set<T>::iterator>
    view( container.begin(), container.end() );

  TEST_EQUALITY_CONST( view[0], 0 );
  TEST_EQUALITY_CONST( view[1], 1 );
  TEST_EQUALITY_CONST( view.at(0), 0 );
  TEST_EQUALITY_CONST( view.at(1), 1 );
  TEST_EQUALITY_CONST( view.front(), 0 );
  TEST_EQUALITY_CONST( view.back(), 1 );

  Utility::View<typename std::set<T>::reverse_iterator>
    reverse_view( container.rbegin(), container.rend() );

  TEST_EQUALITY_CONST( reverse_view[0], 1 );
  TEST_EQUALITY_CONST( reverse_view[1], 0 );
  TEST_EQUALITY_CONST( reverse_view.at(0), 1 );
  TEST_EQUALITY_CONST( reverse_view.at(1), 0 );
  TEST_EQUALITY_CONST( reverse_view.front(), 1 );
  TEST_EQUALITY_CONST( reverse_view.back(), 0 );
  
  Utility::View<typename std::set<T>::const_iterator>
    view_of_const( container.begin(), container.end() );

  TEST_EQUALITY_CONST( view_of_const[0], 0 );
  TEST_EQUALITY_CONST( view_of_const[1], 1 );
  TEST_EQUALITY_CONST( view_of_const.at(0), 0 );
  TEST_EQUALITY_CONST( view_of_const.at(1), 1 );
  TEST_EQUALITY_CONST( view_of_const.front(), 0 );
  TEST_EQUALITY_CONST( view_of_const.back(), 1 );

  Utility::View<typename std::set<T>::const_reverse_iterator>
    reverse_view_of_const( container.rbegin(), container.rend() );

  TEST_EQUALITY_CONST( reverse_view_of_const[0], 1 );
  TEST_EQUALITY_CONST( reverse_view_of_const[1], 0 );
  TEST_EQUALITY_CONST( reverse_view_of_const.at(0), 1 );
  TEST_EQUALITY_CONST( reverse_view_of_const.at(1), 0 );
  TEST_EQUALITY_CONST( reverse_view_of_const.front(), 1 );
  TEST_EQUALITY_CONST( reverse_view_of_const.back(), 0 );
}

UNIT_TEST_TEMPLATE_1_BASIC_INSTANT( View_set, element_access );

//---------------------------------------------------------------------------//
// Check the element access for unordered_set views
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( View_unordered_set, element_access, T )
{
  std::unordered_set<T> container( {0, 1} );

  Utility::View<typename std::unordered_set<T>::iterator>
    view( container.begin(), container.end() );

  TEST_EQUALITY_CONST( view[0], 1 );
  TEST_EQUALITY_CONST( view[1], 0 );
  TEST_EQUALITY_CONST( view.at(0), 1 );
  TEST_EQUALITY_CONST( view.at(1), 0 );
  TEST_EQUALITY_CONST( view.front(), 1 );
  TEST_EQUALITY_CONST( view.back(), 0 );

  Utility::View<typename std::unordered_set<T>::const_iterator>
    view_of_const( container.begin(), container.end() );

  TEST_EQUALITY_CONST( view_of_const[0], 1 );
  TEST_EQUALITY_CONST( view_of_const[1], 0 );
  TEST_EQUALITY_CONST( view_of_const.at(0), 1 );
  TEST_EQUALITY_CONST( view_of_const.at(1), 0 );
  TEST_EQUALITY_CONST( view_of_const.front(), 1 );
  TEST_EQUALITY_CONST( view_of_const.back(), 0 );
}

UNIT_TEST_TEMPLATE_1_BASIC_INSTANT( View_unordered_set, element_access );

//---------------------------------------------------------------------------//
// Check the element access for map views
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( View_map, element_access, T )
{
  std::map<T,T> container( {std::make_pair((T)0, (T)0), std::make_pair((T)1, (T)1)} );

  Utility::View<typename std::map<T,T>::iterator>
    view( container.begin(), container.end() );

  TEST_EQUALITY_CONST( view[0], (std::pair<const T,T>({0, 0})) );
  TEST_EQUALITY_CONST( view[1], (std::pair<const T,T>({1, 1})) );
  TEST_EQUALITY_CONST( view.at(0), (std::pair<const T,T>({0, 0})) );
  TEST_EQUALITY_CONST( view.at(1), (std::pair<const T,T>({1, 1})) );
  TEST_EQUALITY_CONST( view.front(), (std::pair<const T,T>({0, 0})) );
  TEST_EQUALITY_CONST( view.back(), (std::pair<const T,T>({1, 1})) );

  Utility::View<typename std::map<T,T>::reverse_iterator>
    reverse_view( container.rbegin(), container.rend() );

  TEST_EQUALITY_CONST( reverse_view[0], (std::pair<const T,T>({1, 1})) );
  TEST_EQUALITY_CONST( reverse_view[1], (std::pair<const T,T>({0, 0})) );
  TEST_EQUALITY_CONST( reverse_view.at(0), (std::pair<const T,T>({1, 1})) );
  TEST_EQUALITY_CONST( reverse_view.at(1), (std::pair<const T,T>({0, 0})) );
  TEST_EQUALITY_CONST( reverse_view.front(), (std::pair<const T,T>({1, 1})) );
  TEST_EQUALITY_CONST( reverse_view.back(), (std::pair<const T,T>({0, 0})) );
  
  Utility::View<typename std::map<T,T>::const_iterator>
    view_of_const( container.begin(), container.end() );

  TEST_EQUALITY_CONST( view_of_const[0], (std::pair<const T,T>({0, 0})) );
  TEST_EQUALITY_CONST( view_of_const[1], (std::pair<const T,T>({1, 1})) );
  TEST_EQUALITY_CONST( view_of_const.at(0), (std::pair<const T,T>({0, 0})) );
  TEST_EQUALITY_CONST( view_of_const.at(1), (std::pair<const T,T>({1, 1})) );
  TEST_EQUALITY_CONST( view_of_const.front(), (std::pair<const T,T>({0, 0})) );
  TEST_EQUALITY_CONST( view_of_const.back(), (std::pair<const T,T>({1, 1})) );

  Utility::View<typename std::map<T,T>::const_reverse_iterator>
    reverse_view_of_const( container.rbegin(), container.rend() );

  TEST_EQUALITY_CONST( reverse_view_of_const[0], (std::pair<const T,T>({1, 1})) );
  TEST_EQUALITY_CONST( reverse_view_of_const[1], (std::pair<const T,T>({0, 0})) );
  TEST_EQUALITY_CONST( reverse_view_of_const.at(0), (std::pair<const T,T>({1, 1})) );
  TEST_EQUALITY_CONST( reverse_view_of_const.at(1), (std::pair<const T,T>({0, 0})) );
  TEST_EQUALITY_CONST( reverse_view_of_const.front(), (std::pair<const T,T>({1, 1})) );
  TEST_EQUALITY_CONST( reverse_view_of_const.back(), (std::pair<const T,T>({0, 0})) );
}

UNIT_TEST_TEMPLATE_1_BASIC_INSTANT( View_map, element_access );

//---------------------------------------------------------------------------//
// Check the element access for unordered_map views
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( View_unordered_map, element_access, T )
{
  std::unordered_map<T,T> container( {std::make_pair((T)0, (T)0), std::make_pair((T)1, (T)1)} );

  Utility::View<typename std::unordered_map<T,T>::iterator>
    view( container.begin(), container.end() );

  TEST_EQUALITY_CONST( view[0], (std::pair<const T,T>({1, 1})) );
  TEST_EQUALITY_CONST( view[1], (std::pair<const T,T>({0, 0})) );
  TEST_EQUALITY_CONST( view.at(0), (std::pair<const T,T>({1, 1})) );
  TEST_EQUALITY_CONST( view.at(1), (std::pair<const T,T>({0, 0})) );
  TEST_EQUALITY_CONST( view.front(), (std::pair<const T,T>({1, 1})) );
  TEST_EQUALITY_CONST( view.back(), (std::pair<const T,T>({0, 0})) );

  Utility::View<typename std::unordered_map<T,T>::const_iterator>
    view_of_const( container.begin(), container.end() );

  TEST_EQUALITY_CONST( view_of_const[0], (std::pair<const T,T>({1, 1})) );
  TEST_EQUALITY_CONST( view_of_const[1], (std::pair<const T,T>({0, 0})) );
  TEST_EQUALITY_CONST( view_of_const.at(0), (std::pair<const T,T>({1, 1})) );
  TEST_EQUALITY_CONST( view_of_const.at(1), (std::pair<const T,T>({0, 0})) );
  TEST_EQUALITY_CONST( view_of_const.front(), (std::pair<const T,T>({1, 1})) );
  TEST_EQUALITY_CONST( view_of_const.back(), (std::pair<const T,T>({0, 0})) );
}

UNIT_TEST_TEMPLATE_1_BASIC_INSTANT( View_unordered_map, element_access );

//---------------------------------------------------------------------------//
// end tstView.cpp
//---------------------------------------------------------------------------//
