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

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a view can be constructed
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( View, default_constructor, Container )
{
  Utility::View<typename Container::iterator> view;

  TEST_EQUALITY_CONST( view.size(), 0 );

  Utility::View<typename Container::const_iterator> view_of_const;

  TEST_EQUALITY_CONST( view_of_const.size(), 0 );
}

UNIT_TEST_TEMPLATE_1_INSTANT( View, default_constructor );

//---------------------------------------------------------------------------//
// end tstView.cpp
//---------------------------------------------------------------------------//
