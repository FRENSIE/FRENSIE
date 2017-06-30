//---------------------------------------------------------------------------//
//!
//! \file   tstArrayView.cpp
//! \author Alex Robinson
//! \brief  ArrayView unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_ArrayView.hpp"

typedef unsigned char uchar;
typedef signed char schar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef long long longlong;
typedef unsigned long long ulonglong;
typedef std::string string;

//---------------------------------------------------------------------------//
// Instantiation Macros
//---------------------------------------------------------------------------//
#define UNIT_TEST_TEMPLATE_1_INSTANT( type, name )        \
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
// Tests.
//---------------------------------------------------------------------------//
// Check that an array view can be constructed
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayView, default_constructor, T )
{
  Utility::ArrayView<T> view;

  TEST_EQUALITY_CONST( view.size(), 0 );
  TEST_ASSERT( view.empty() );

  Utility::ArrayView<const T> view_of_const;

  TEST_EQUALITY_CONST( view_of_const.size(), 0 );
  TEST_ASSERT( view_of_const.empty() );
}

UNIT_TEST_TEMPLATE_1_INSTANT( ArrayView, default_constructor );

//---------------------------------------------------------------------------//
// Check that an array view can be constructed from iterators
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayView, iterator_constructor, T )
{
  std::vector<T> container( 10, T() );

  Utility::ArrayView<T> view( container.data(), container.data()+10 );

  TEST_EQUALITY_CONST( view.size(), 10 );
  TEST_ASSERT( !view.empty() );

  {
    Utility::ArrayView<const T>
      view_of_const( container.data(), container.data()+10 );

    TEST_EQUALITY_CONST( view_of_const.size(), 10 );
    TEST_ASSERT( !view_of_const.empty() );
  }

  {
    Utility::ArrayView<const T>
      view_of_const( (const T*)container.data(),
                     (const T*)(container.data()+10) );

    TEST_EQUALITY_CONST( view_of_const.size(), 10 );
    TEST_ASSERT( !view_of_const.empty() );
  }
}

UNIT_TEST_TEMPLATE_1_INSTANT( ArrayView, iterator_constructor );

//---------------------------------------------------------------------------//
// Check that an array view can be constructed from a range
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayView, range_constructor, T )
{
  std::vector<T> container( 10, T() );

  Utility::ArrayView<T> view( container.data(), 10 );

  TEST_EQUALITY_CONST( view.size(), 10 );
  TEST_ASSERT( !view.empty() );

  {
    Utility::ArrayView<const T>
      view_of_const( container.data(), 10 );

    TEST_EQUALITY_CONST( view_of_const.size(), 10 );
    TEST_ASSERT( !view_of_const.empty() );
  }

  {
    Utility::ArrayView<const T>
      view_of_const( (const T*)container.data(), 10 );

    TEST_EQUALITY_CONST( view_of_const.size(), 10 );
    TEST_ASSERT( !view_of_const.empty() );
  }
}

UNIT_TEST_TEMPLATE_1_INSTANT( ArrayView, range_constructor );

//---------------------------------------------------------------------------//
// Check that an array view can be constructed from containers
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayView, container_constructor, T )
{
  std::vector<T> vector( 10, T() );

  {
    Utility::ArrayView<T> view( vector );

    TEST_EQUALITY_CONST( view.size(), 10 );
    TEST_ASSERT( !view.empty() );

    Utility::ArrayView<const T> view_of_const( vector );

    TEST_EQUALITY_CONST( view_of_const.size(), 10 );
    TEST_ASSERT( !view_of_const.empty() );
  }

  std::array<T,10> array;

  {
    Utility::ArrayView<T> view( array );

    TEST_EQUALITY_CONST( view.size(), 10 );
    TEST_ASSERT( !view.empty() );

    Utility::ArrayView<const T> view_of_const( array );

    TEST_EQUALITY_CONST( view_of_const.size(), 10 );
    TEST_ASSERT( !view_of_const.empty() );
  }
}

UNIT_TEST_TEMPLATE_1_INSTANT( ArrayView, container_constructor );

//---------------------------------------------------------------------------//
// Check the copy constructor
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayView, copy_constructor, T )
{
  std::vector<T> container( 10 );

  Utility::ArrayView<T> view( container );

  Utility::ArrayView<const T> view_of_const( container );

  {
    Utility::ArrayView<T> view_copy( view );

    TEST_EQUALITY_CONST( view_copy.size(), view.size() );
  }

  {
    Utility::ArrayView<const T> view_of_const_copy( view );

    TEST_EQUALITY_CONST( view_of_const_copy.size(), view.size() );
  }

  {
    Utility::ArrayView<const T> view_of_const_copy( view_of_const );

    TEST_EQUALITY_CONST( view_of_const_copy.size(), view_of_const.size() );
  }
}

UNIT_TEST_TEMPLATE_1_INSTANT( ArrayView, copy_constructor );

//---------------------------------------------------------------------------//
// Check the assignment operator
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayView, assignment_operator, T )
{
  std::vector<T> container( 10 );

  Utility::ArrayView<T> view( container );

  Utility::ArrayView<const T> view_of_const( container );

  {
    Utility::ArrayView<T> view_copy = view;

    TEST_EQUALITY_CONST( view_copy.size(), view.size() );
  }

  {
    Utility::ArrayView<const T> view_of_const_copy = view;

    TEST_EQUALITY_CONST( view_of_const_copy.size(), view.size() );
  }

  {
    Utility::ArrayView<const T> view_of_const_copy = view_of_const;

    TEST_EQUALITY_CONST( view_of_const_copy.size(), view_of_const.size() );
  }
}

UNIT_TEST_TEMPLATE_1_INSTANT( ArrayView, assignment_operator );

//---------------------------------------------------------------------------//
// Check that array view iterators can be acquired
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayView, iterator, T )
{
  std::array<T,10> container;

  Utility::ArrayView<T> view( container );

  TEST_EQUALITY_CONST( view.begin(), container.begin() );
  TEST_EQUALITY_CONST( std::distance( view.begin(), view.end() ), 10 );
  TEST_EQUALITY_CONST( view.cbegin(), container.cbegin() );
  TEST_EQUALITY_CONST( std::distance( view.cbegin(), view.cend() ), 10 );

  Utility::ArrayView<const T> view_of_const( container );

  TEST_EQUALITY_CONST( view_of_const.begin(), container.cbegin() );
  TEST_EQUALITY_CONST( std::distance( view_of_const.begin(), view_of_const.cend() ), 10 );
  TEST_EQUALITY_CONST( view_of_const.cbegin(), container.cbegin() );
  TEST_EQUALITY_CONST( std::distance( view_of_const.cbegin(), view_of_const.cend() ), 10 );
}

UNIT_TEST_TEMPLATE_1_INSTANT( ArrayView, iterator );

//---------------------------------------------------------------------------//
// Check that array view elements can be accessed
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayView, element_access, T )
{
  std::array<T,2> container( {0, 1} );

  Utility::ArrayView<T> view( container );

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

  Utility::ArrayView<T> partial_view = view( 1, 1 );

  TEST_EQUALITY_CONST( partial_view[0], 0 );
  TEST_EQUALITY_CONST( partial_view.at(0), 0 );
  TEST_EQUALITY_CONST( partial_view.front(), 0 );
  TEST_EQUALITY_CONST( partial_view.back(), 0 );

  partial_view[0] = 1;

  TEST_EQUALITY_CONST( partial_view[0], 1 );
  TEST_EQUALITY_CONST( partial_view.front(), 1 );
  TEST_EQUALITY_CONST( partial_view.back(), 1 );
  TEST_EQUALITY_CONST( view[1], 1 );

  partial_view = view | Utility::Slice( 0, 1 );

  partial_view[0] = 0;

  TEST_EQUALITY_CONST( partial_view[0], 0 );
  TEST_EQUALITY_CONST( partial_view.front(), 0 );
  TEST_EQUALITY_CONST( partial_view.back(), 0 );
  TEST_EQUALITY_CONST( view[0], 0 );

  container[0] = 1;
  container[1] = 0;

  TEST_EQUALITY_CONST( view[0], 1 );
  TEST_EQUALITY_CONST( view[1], 0 );
  TEST_EQUALITY_CONST( partial_view[0], 1 );

  Utility::ArrayView<const T> view_of_const( container );

  TEST_EQUALITY_CONST( view_of_const[0], 1 );
  TEST_EQUALITY_CONST( view_of_const[1], 0 );
  TEST_EQUALITY_CONST( view_of_const.at(0), 1 );
  TEST_EQUALITY_CONST( view_of_const.at(1), 0 );
  TEST_EQUALITY_CONST( view_of_const.front(), 1 );
  TEST_EQUALITY_CONST( view_of_const.back(), 0 );
}

UNIT_TEST_TEMPLATE_1_INSTANT( ArrayView, element_access );

//---------------------------------------------------------------------------//
// Check if an array view can be converted to an array view-of-const
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayView, to_const, T )
{
  std::vector<T> container( 10 );

  Utility::ArrayView<T> view( container );

  {
    auto view_of_const = view.toConst();

    TEST_ASSERT( Utility::IsPointerToConst<typename decltype(view_of_const)::pointer>::value );
  }

  {
    auto view_of_const = (Utility::ArrayView<const T>)view;

    TEST_ASSERT( Utility::IsPointerToConst<typename decltype(view_of_const)::pointer>::value );
  }
}

UNIT_TEST_TEMPLATE_1_INSTANT( ArrayView, to_const );

//---------------------------------------------------------------------------//
// Check if an array view can be constructed using the arrayView helper
// function
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayView,
                                   array_view_construction_helper,
                                   T )
{
  std::vector<T> vector( 10 );

  {
    auto view = Utility::arrayView( vector );
    
    TEST_EQUALITY_CONST( view.size(), vector.size() );
    TEST_EQUALITY_CONST( view.front(), vector.front() );
    TEST_EQUALITY_CONST( view.back(), vector.back() );
    TEST_ASSERT( !Utility::IsPointerToConst<typename decltype(view)::pointer>::value );
  }

  {
    auto view_of_const =
      Utility::arrayView( const_cast<const std::vector<T>&>(vector) );

    TEST_EQUALITY_CONST( view_of_const.size(), vector.size() );
    TEST_EQUALITY_CONST( view_of_const.front(), vector.front() );
    TEST_EQUALITY_CONST( view_of_const.back(), vector.back() );
    TEST_ASSERT( Utility::IsPointerToConst<typename decltype(view_of_const)::pointer>::value );
  }

  {
    auto view_of_const = Utility::arrayViewOfConst( vector );

    TEST_EQUALITY_CONST( view_of_const.size(), vector.size() );
    TEST_EQUALITY_CONST( view_of_const.front(), vector.front() );
    TEST_EQUALITY_CONST( view_of_const.back(), vector.back() );
    TEST_ASSERT( Utility::IsPointerToConst<typename decltype(view_of_const)::pointer>::value );
  }

  std::array<T,10> array({0, 0, 0, 0, 0, 0, 0, 0, 0, 0});

  {
    auto view = Utility::arrayView( array );
    
    TEST_EQUALITY_CONST( view.size(), array.size() );
    TEST_EQUALITY_CONST( view.front(), array.front() );
    TEST_EQUALITY_CONST( view.back(), array.back() );
    TEST_ASSERT( !Utility::IsPointerToConst<typename decltype(view)::pointer>::value );
  }

  {
    auto view_of_const =
      Utility::arrayView( const_cast<const std::array<T,10>&>(array) );

    TEST_EQUALITY_CONST( view_of_const.size(), array.size() );
    TEST_EQUALITY_CONST( view_of_const.front(), array.front() );
    TEST_EQUALITY_CONST( view_of_const.back(), array.back() );
    TEST_ASSERT( Utility::IsPointerToConst<typename decltype(view_of_const)::pointer>::value );
  }

  {
    auto view_of_const = Utility::arrayViewOfConst( array );

    TEST_EQUALITY_CONST( view_of_const.size(), array.size() );
    TEST_EQUALITY_CONST( view_of_const.front(), array.front() );
    TEST_EQUALITY_CONST( view_of_const.back(), array.back() );
    TEST_ASSERT( Utility::IsPointerToConst<typename decltype(view_of_const)::pointer>::value );
  }
}

UNIT_TEST_TEMPLATE_1_INSTANT( ArrayView, array_view_construction_helper );

//---------------------------------------------------------------------------//
// Check that an array view can be cast to a array view-of-const and back
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayView, array_view_const_cast_helper, T )
{
  std::vector<T> container( 10 );

  Utility::ArrayView<T> view( container );
  Utility::ArrayView<const T> view_of_const( container );

  {
    auto view_of_const_copy = Utility::av_const_cast<const T>( view );

    TEST_EQUALITY_CONST( view_of_const_copy.size(), view_of_const.size() );
    TEST_ASSERT( Utility::IsPointerToConst<typename decltype(view_of_const_copy)::pointer>::value );
  }

  {
    auto view_of_const_copy = Utility::av_const_cast<const T>( view_of_const );

    TEST_EQUALITY_CONST( view_of_const_copy.size(), view_of_const.size() );
    TEST_ASSERT( Utility::IsPointerToConst<typename decltype(view_of_const_copy)::pointer>::value );
  }

  {
    auto view_copy = Utility::av_const_cast<T>( view );

    TEST_EQUALITY_CONST( view_copy.size(), view.size() );
    TEST_ASSERT( !Utility::IsPointerToConst<typename decltype(view_copy)::pointer>::value );
  }

  {
    auto view_copy = Utility::av_const_cast<T>( view_of_const );

    TEST_EQUALITY_CONST( view_copy.size(), view.size() );
    TEST_ASSERT( !Utility::IsPointerToConst<typename decltype(view_copy)::pointer>::value );
  }
}

UNIT_TEST_TEMPLATE_1_INSTANT( ArrayView, array_view_const_cast_helper );

//---------------------------------------------------------------------------//
// Check the reinterpret cast array view helper function
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayView,
                                   array_view_reinterpret_cast_helper,
                                   T )
{
  std::vector<T> container( 10 );

  Utility::ArrayView<T> view( container );
  Utility::ArrayView<const T> view_of_const( container );

  {
    auto reinterpreted_view_copy = Utility::av_reinterpret_cast<char>( view );

    TEST_EQUALITY( reinterpreted_view_copy.size(),
                   view.size()*sizeof(T) );
    TEST_ASSERT( (std::is_same<typename decltype(reinterpreted_view_copy)::value_type,char>::value) );
  }

  {
    auto reinterpreted_view_of_const_copy =
      Utility::av_reinterpret_cast<const char>( view );

    TEST_EQUALITY( reinterpreted_view_of_const_copy.size(),
                   view.size()*sizeof(T) );
    TEST_ASSERT( (std::is_same<typename decltype(reinterpreted_view_of_const_copy)::value_type,char>::value) );
  }

  {
    auto reinterpreted_view_of_const_copy =
      Utility::av_reinterpret_cast<const char>( view_of_const );

    TEST_EQUALITY( reinterpreted_view_of_const_copy.size(),
                   view_of_const.size()*sizeof(T) );
    TEST_ASSERT( (std::is_same<typename decltype(reinterpreted_view_of_const_copy)::value_type,char>::value) );
  }
}

UNIT_TEST_TEMPLATE_1_INSTANT( ArrayView, array_view_reinterpret_cast_helper )

//---------------------------------------------------------------------------//
// end tstArrayView.cpp
//---------------------------------------------------------------------------//
