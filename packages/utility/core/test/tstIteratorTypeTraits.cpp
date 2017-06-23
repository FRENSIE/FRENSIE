//---------------------------------------------------------------------------//
//!
//! \file   tstIteratorTypeTraits.cpp
//! \author Alex Robinson
//! \brief  Iterator type traits unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <type_traits>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_IteratorTypeTraits.hpp"

typedef bool* bool_p;
typedef char* char_p;
typedef unsigned char uchar;
typedef unsigned char* uchar_p;
typedef signed char schar;
typedef signed char* schar_p;
typedef short* short_p;
typedef unsigned short ushort;
typedef unsigned short* ushort_p;
typedef int* int_p;
typedef unsigned int uint;
typedef unsigned int* uint_p;
typedef long* long_p;
typedef unsigned long ulong;
typedef unsigned long* ulong_p;
typedef long long longlong;
typedef long long* longlong_p;
typedef unsigned long long ulonglong;
typedef unsigned long long* ulonglong_p;
typedef float* float_p;
typedef double* double_p;
typedef std::string string;
typedef std::string* string_p;
typedef std::pair<int,double> pair_int_double;

//---------------------------------------------------------------------------//
// Instantiation Macros
//---------------------------------------------------------------------------//
#define UNIT_TEST_TEMPLATE_1_INSTANT( type, name )      \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, bool );       \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, bool_p );       \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, char );       \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, char_p );       \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, schar );       \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, schar_p );       \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, uchar );       \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, uchar_p );       \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, short );        \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, short_p );        \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, ushort );      \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, ushort_p );       \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, int );           \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, int_p );           \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, uint );           \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, uint_p );           \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, long );      \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, long_p );      \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, ulong );         \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, ulong_p );         \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, longlong );       \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, longlong_p );       \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, ulonglong );       \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, ulonglong_p );     \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, float );           \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, float_p );     \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, double );           \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, double_p );     \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, string );           \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, string_p )

#define UNIT_TEST_TEMPLATE_2_INSTANT( type, name )      \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, bool, bool );        \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, bool_p, bool_p );     \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, char, char );       \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, char_p, char_p );   \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, schar, schar );     \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, schar_p, schar_p ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, uchar, uchar );     \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, uchar_p, uchar_p ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, short, short );     \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, short_p, short_p ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, ushort, ushort );   \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, ushort_p, ushort_p ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, int, int );         \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, int_p, int_p );     \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, uint, uint );         \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, uint_p, uint_p );   \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, long, long );       \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, long_p, long_p );   \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, ulong, ulong );     \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, ulong_p, ulong_p ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, longlong, longlong ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, longlong_p, longlong_p ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, ulonglong, ulonglong ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, ulonglong_p, ulonglong_p ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, float, float ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, float_p, float_p ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, double, double ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, double_p, double_p ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, string, string );   \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, string_p, string_p ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, int, pair_int_double )

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check if a std::string iterator is a const iterator
TEUCHOS_UNIT_TEST( IteratorTypeTraits, string_IsConstIterator )
{
  TEST_ASSERT( !Utility::IsConstIterator<std::string::iterator>::value );
  TEST_ASSERT( Utility::IsConstIterator<std::string::const_iterator>::value );
  TEST_ASSERT( !Utility::IsConstIterator<std::string::reverse_iterator>::value );
  TEST_ASSERT( Utility::IsConstIterator<std::string::const_reverse_iterator>::value );
}

//---------------------------------------------------------------------------//
// Check if std::string iterator types can be converted to const iterator types
TEUCHOS_UNIT_TEST( IteratorTypeTraits, string_ConstIterator )
{
  TEST_ASSERT( (std::is_same<Utility::ConstIterator<std::string::iterator>::type,std::string::const_iterator>::value) );
  TEST_ASSERT( (std::is_same<Utility::ConstIterator<std::string::const_iterator>::type,std::string::const_iterator>::value) );
  TEST_ASSERT( (std::is_same<Utility::ConstIterator<std::string::reverse_iterator>::type,std::string::const_reverse_iterator>::value) );
  TEST_ASSERT( (std::is_same<Utility::ConstIterator<std::string::const_reverse_iterator>::type,std::string::const_reverse_iterator>::value) );
}

//---------------------------------------------------------------------------//
// Check if std::string const iterator types can be converted to non-const
// iterator types
TEUCHOS_UNIT_TEST( IteratorTypeTraits, string_NonConstIterator )
{
  TEST_ASSERT( (std::is_same<Utility::NonConstIterator<std::string::iterator>::type,std::string::iterator>::value) );
  TEST_ASSERT( (std::is_same<Utility::NonConstIterator<std::string::const_iterator>::type,std::string::iterator>::value) );
  TEST_ASSERT( (std::is_same<Utility::NonConstIterator<std::string::reverse_iterator>::type,std::string::reverse_iterator>::value) );
  TEST_ASSERT( (std::is_same<Utility::NonConstIterator<std::string::const_reverse_iterator>::type,std::string::reverse_iterator>::value) );
}

//---------------------------------------------------------------------------//
// Check if a std::array iterator is a const iterator
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( IteratorTypeTraits,
                                   array_IsConstIterator,
                                   T )
{

  TEST_ASSERT( !(Utility::IsConstIterator<typename std::array<T,1>::iterator>::value) );
  TEST_ASSERT( (Utility::IsConstIterator<typename std::array<T,1>::const_iterator>::value) );
  TEST_ASSERT( !(Utility::IsConstIterator<typename std::array<T,1>::reverse_iterator>::value) );
  TEST_ASSERT( (Utility::IsConstIterator<typename std::array<T,1>::const_reverse_iterator>::value) );

  TEST_ASSERT( !(Utility::IsConstIterator<typename std::array<T,10>::iterator>::value) );
  TEST_ASSERT( (Utility::IsConstIterator<typename std::array<T,10>::const_iterator>::value) );
  TEST_ASSERT( !(Utility::IsConstIterator<typename std::array<T,10>::reverse_iterator>::value) );
  TEST_ASSERT( (Utility::IsConstIterator<typename std::array<T,10>::const_reverse_iterator>::value) );

  TEST_ASSERT( !(Utility::IsConstIterator<typename std::array<T,100>::iterator>::value) );
  TEST_ASSERT( (Utility::IsConstIterator<typename std::array<T,100>::const_iterator>::value) );
  TEST_ASSERT( !(Utility::IsConstIterator<typename std::array<T,100>::reverse_iterator>::value) );
  TEST_ASSERT( (Utility::IsConstIterator<typename std::array<T,100>::const_reverse_iterator>::value) );
}

UNIT_TEST_TEMPLATE_1_INSTANT( IteratorTypeTraits, array_IsConstIterator );

//---------------------------------------------------------------------------//
// Check if std::array iterator types can be converted to const iterator types
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( IteratorTypeTraits,
                                   array_ConstIterator,
                                   T )
{
  TEST_ASSERT( (std::is_same<typename Utility::ConstIterator<typename std::array<T,1>::iterator>::type,typename std::array<T,1>::const_iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::ConstIterator<typename std::array<T,1>::const_iterator>::type,typename std::array<T,1>::const_iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::ConstIterator<typename std::array<T,1>::reverse_iterator>::type,typename std::array<T,1>::const_reverse_iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::ConstIterator<typename std::array<T,1>::const_reverse_iterator>::type,typename std::array<T,1>::const_reverse_iterator>::value) );

  TEST_ASSERT( (std::is_same<typename Utility::ConstIterator<typename std::array<T,10>::iterator>::type,typename std::array<T,10>::const_iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::ConstIterator<typename std::array<T,10>::const_iterator>::type,typename std::array<T,10>::const_iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::ConstIterator<typename std::array<T,10>::reverse_iterator>::type,typename std::array<T,10>::const_reverse_iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::ConstIterator<typename std::array<T,10>::const_reverse_iterator>::type,typename std::array<T,10>::const_reverse_iterator>::value) );

  TEST_ASSERT( (std::is_same<typename Utility::ConstIterator<typename std::array<T,100>::iterator>::type,typename std::array<T,100>::const_iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::ConstIterator<typename std::array<T,100>::const_iterator>::type,typename std::array<T,100>::const_iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::ConstIterator<typename std::array<T,100>::reverse_iterator>::type,typename std::array<T,100>::const_reverse_iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::ConstIterator<typename std::array<T,100>::const_reverse_iterator>::type,typename std::array<T,100>::const_reverse_iterator>::value) );
}

UNIT_TEST_TEMPLATE_1_INSTANT( IteratorTypeTraits, array_ConstIterator );

//---------------------------------------------------------------------------//
// Check if std::array const iterator types can be converted to non-const
// iterator types
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( IteratorTypeTraits,
                                   array_NonConstIterator,
                                   T )
{
  TEST_ASSERT( (std::is_same<typename Utility::NonConstIterator<typename std::array<T,1>::iterator>::type,typename std::array<T,1>::iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::NonConstIterator<typename std::array<T,1>::const_iterator>::type,typename std::array<T,1>::iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::NonConstIterator<typename std::array<T,1>::reverse_iterator>::type,typename std::array<T,1>::reverse_iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::NonConstIterator<typename std::array<T,1>::const_reverse_iterator>::type,typename std::array<T,1>::reverse_iterator>::value) );

  TEST_ASSERT( (std::is_same<typename Utility::NonConstIterator<typename std::array<T,10>::iterator>::type,typename std::array<T,10>::iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::NonConstIterator<typename std::array<T,10>::const_iterator>::type,typename std::array<T,10>::iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::NonConstIterator<typename std::array<T,10>::reverse_iterator>::type,typename std::array<T,10>::reverse_iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::NonConstIterator<typename std::array<T,10>::const_reverse_iterator>::type,typename std::array<T,10>::reverse_iterator>::value) );

  TEST_ASSERT( (std::is_same<typename Utility::NonConstIterator<typename std::array<T,100>::iterator>::type,typename std::array<T,100>::iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::NonConstIterator<typename std::array<T,100>::const_iterator>::type,typename std::array<T,100>::iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::NonConstIterator<typename std::array<T,100>::reverse_iterator>::type,typename std::array<T,100>::reverse_iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::NonConstIterator<typename std::array<T,100>::const_reverse_iterator>::type,typename std::array<T,100>::reverse_iterator>::value) );
}

UNIT_TEST_TEMPLATE_1_INSTANT( IteratorTypeTraits, array_NonConstIterator );

//---------------------------------------------------------------------------//
// Check if a std::vector iterator is a const iterator
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( IteratorTypeTraits,
                                   vector_IsConstIterator,
                                   T )
{

  TEST_ASSERT( !(Utility::IsConstIterator<typename std::vector<T>::iterator>::value) );
  TEST_ASSERT( (Utility::IsConstIterator<typename std::vector<T>::const_iterator>::value) );
  TEST_ASSERT( !(Utility::IsConstIterator<typename std::vector<T>::reverse_iterator>::value) );
  TEST_ASSERT( (Utility::IsConstIterator<typename std::vector<T>::const_reverse_iterator>::value) );
}

UNIT_TEST_TEMPLATE_1_INSTANT( IteratorTypeTraits, vector_IsConstIterator );

//---------------------------------------------------------------------------//
// Check if std::vector iterator types can be converted to const iterator types
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( IteratorTypeTraits,
                                   vector_ConstIterator,
                                   T )
{
  TEST_ASSERT( (std::is_same<typename Utility::ConstIterator<typename std::vector<T>::iterator>::type,typename std::vector<T>::const_iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::ConstIterator<typename std::vector<T>::const_iterator>::type,typename std::vector<T>::const_iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::ConstIterator<typename std::vector<T>::reverse_iterator>::type,typename std::vector<T>::const_reverse_iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::ConstIterator<typename std::vector<T>::const_reverse_iterator>::type,typename std::vector<T>::const_reverse_iterator>::value) );
}

UNIT_TEST_TEMPLATE_1_INSTANT( IteratorTypeTraits, vector_ConstIterator );

//---------------------------------------------------------------------------//
// Check if std::vector const iterator types can be converted to non-const
// iterator types
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( IteratorTypeTraits,
                                   vector_NonConstIterator,
                                   T )
{
  TEST_ASSERT( (std::is_same<typename Utility::NonConstIterator<typename std::vector<T>::iterator>::type,typename std::vector<T>::iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::NonConstIterator<typename std::vector<T>::const_iterator>::type,typename std::vector<T>::iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::NonConstIterator<typename std::vector<T>::reverse_iterator>::type,typename std::vector<T>::reverse_iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::NonConstIterator<typename std::vector<T>::const_reverse_iterator>::type,typename std::vector<T>::reverse_iterator>::value) );
}

UNIT_TEST_TEMPLATE_1_INSTANT( IteratorTypeTraits, vector_NonConstIterator );

//---------------------------------------------------------------------------//
// Check if a std::list iterator is a const iterator
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( IteratorTypeTraits,
                                   list_IsConstIterator,
                                   T )
{

  TEST_ASSERT( !(Utility::IsConstIterator<typename std::list<T>::iterator>::value) );
  TEST_ASSERT( (Utility::IsConstIterator<typename std::list<T>::const_iterator>::value) );
  TEST_ASSERT( !(Utility::IsConstIterator<typename std::list<T>::reverse_iterator>::value) );
  TEST_ASSERT( (Utility::IsConstIterator<typename std::list<T>::const_reverse_iterator>::value) );
}

UNIT_TEST_TEMPLATE_1_INSTANT( IteratorTypeTraits, list_IsConstIterator );

//---------------------------------------------------------------------------//
// Check if std::list iterator types can be converted to const iterator types
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( IteratorTypeTraits,
                                   list_ConstIterator,
                                   T )
{
  TEST_ASSERT( (std::is_same<typename Utility::ConstIterator<typename std::list<T>::iterator>::type,typename std::list<T>::const_iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::ConstIterator<typename std::list<T>::const_iterator>::type,typename std::list<T>::const_iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::ConstIterator<typename std::list<T>::reverse_iterator>::type,typename std::list<T>::const_reverse_iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::ConstIterator<typename std::list<T>::const_reverse_iterator>::type,typename std::list<T>::const_reverse_iterator>::value) );
}

UNIT_TEST_TEMPLATE_1_INSTANT( IteratorTypeTraits, list_ConstIterator );

//---------------------------------------------------------------------------//
// Check if std::list const iterator types can be converted to non-const
// iterator types
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( IteratorTypeTraits,
                                   list_NonConstIterator,
                                   T )
{
  TEST_ASSERT( (std::is_same<typename Utility::NonConstIterator<typename std::list<T>::iterator>::type,typename std::list<T>::iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::NonConstIterator<typename std::list<T>::const_iterator>::type,typename std::list<T>::iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::NonConstIterator<typename std::list<T>::reverse_iterator>::type,typename std::list<T>::reverse_iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::NonConstIterator<typename std::list<T>::const_reverse_iterator>::type,typename std::list<T>::reverse_iterator>::value) );
}

UNIT_TEST_TEMPLATE_1_INSTANT( IteratorTypeTraits, list_NonConstIterator );

//---------------------------------------------------------------------------//
// Check if a std::forward_list iterator is a const iterator
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( IteratorTypeTraits,
                                   forward_list_IsConstIterator,
                                   T )
{

  TEST_ASSERT( !(Utility::IsConstIterator<typename std::forward_list<T>::iterator>::value) );
  TEST_ASSERT( (Utility::IsConstIterator<typename std::forward_list<T>::const_iterator>::value) );
}

UNIT_TEST_TEMPLATE_1_INSTANT( IteratorTypeTraits, forward_list_IsConstIterator );

//---------------------------------------------------------------------------//
// Check if std::forward_list iterator types can be converted to const iterator types
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( IteratorTypeTraits,
                                   forward_list_ConstIterator,
                                   T )
{
  TEST_ASSERT( (std::is_same<typename Utility::ConstIterator<typename std::forward_list<T>::iterator>::type,typename std::forward_list<T>::const_iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::ConstIterator<typename std::forward_list<T>::const_iterator>::type,typename std::forward_list<T>::const_iterator>::value) );
}

UNIT_TEST_TEMPLATE_1_INSTANT( IteratorTypeTraits, forward_list_ConstIterator );

//---------------------------------------------------------------------------//
// Check if std::forward_list const iterator types can be converted to non-const
// iterator types
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( IteratorTypeTraits,
                                   forward_list_NonConstIterator,
                                   T )
{
  TEST_ASSERT( (std::is_same<typename Utility::NonConstIterator<typename std::forward_list<T>::iterator>::type,typename std::forward_list<T>::iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::NonConstIterator<typename std::forward_list<T>::const_iterator>::type,typename std::forward_list<T>::iterator>::value) );
}

UNIT_TEST_TEMPLATE_1_INSTANT( IteratorTypeTraits, forward_list_NonConstIterator );

//---------------------------------------------------------------------------//
// Check if a std::deque iterator is a const iterator
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( IteratorTypeTraits,
                                   deque_IsConstIterator,
                                   T )
{

  TEST_ASSERT( !(Utility::IsConstIterator<typename std::deque<T>::iterator>::value) );
  TEST_ASSERT( (Utility::IsConstIterator<typename std::deque<T>::const_iterator>::value) );
  TEST_ASSERT( !(Utility::IsConstIterator<typename std::deque<T>::reverse_iterator>::value) );
  TEST_ASSERT( (Utility::IsConstIterator<typename std::deque<T>::const_reverse_iterator>::value) );
}

UNIT_TEST_TEMPLATE_1_INSTANT( IteratorTypeTraits, deque_IsConstIterator );

//---------------------------------------------------------------------------//
// Check if std::deque iterator types can be converted to const iterator types
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( IteratorTypeTraits,
                                   deque_ConstIterator,
                                   T )
{
  TEST_ASSERT( (std::is_same<typename Utility::ConstIterator<typename std::deque<T>::iterator>::type,typename std::deque<T>::const_iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::ConstIterator<typename std::deque<T>::const_iterator>::type,typename std::deque<T>::const_iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::ConstIterator<typename std::deque<T>::reverse_iterator>::type,typename std::deque<T>::const_reverse_iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::ConstIterator<typename std::deque<T>::const_reverse_iterator>::type,typename std::deque<T>::const_reverse_iterator>::value) );
}

UNIT_TEST_TEMPLATE_1_INSTANT( IteratorTypeTraits, deque_ConstIterator );

//---------------------------------------------------------------------------//
// Check if std::deque const iterator types can be converted to non-const
// iterator types
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( IteratorTypeTraits,
                                   deque_NonConstIterator,
                                   T )
{
  TEST_ASSERT( (std::is_same<typename Utility::NonConstIterator<typename std::deque<T>::iterator>::type,typename std::deque<T>::iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::NonConstIterator<typename std::deque<T>::const_iterator>::type,typename std::deque<T>::iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::NonConstIterator<typename std::deque<T>::reverse_iterator>::type,typename std::deque<T>::reverse_iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::NonConstIterator<typename std::deque<T>::const_reverse_iterator>::type,typename std::deque<T>::reverse_iterator>::value) );
}

UNIT_TEST_TEMPLATE_1_INSTANT( IteratorTypeTraits, deque_NonConstIterator );

//---------------------------------------------------------------------------//
// Check if a std::set iterator is a const iterator
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( IteratorTypeTraits,
                                   set_IsConstIterator,
                                   T )
{
  // std::set only provides a const iterator type
  TEST_ASSERT( (Utility::IsConstIterator<typename std::set<T>::iterator>::value) );
  TEST_ASSERT( (Utility::IsConstIterator<typename std::set<T>::const_iterator>::value) );
  TEST_ASSERT( (Utility::IsConstIterator<typename std::set<T>::reverse_iterator>::value) );
  TEST_ASSERT( (Utility::IsConstIterator<typename std::set<T>::const_reverse_iterator>::value) );
}

UNIT_TEST_TEMPLATE_1_INSTANT( IteratorTypeTraits, set_IsConstIterator );

//---------------------------------------------------------------------------//
// Check if std::set iterator types can be converted to const iterator types
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( IteratorTypeTraits,
                                   set_ConstIterator,
                                   T )
{
  TEST_ASSERT( (std::is_same<typename Utility::ConstIterator<typename std::set<T>::iterator>::type,typename std::set<T>::const_iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::ConstIterator<typename std::set<T>::const_iterator>::type,typename std::set<T>::const_iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::ConstIterator<typename std::set<T>::reverse_iterator>::type,typename std::set<T>::const_reverse_iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::ConstIterator<typename std::set<T>::const_reverse_iterator>::type,typename std::set<T>::const_reverse_iterator>::value) );
}

UNIT_TEST_TEMPLATE_1_INSTANT( IteratorTypeTraits, set_ConstIterator );

//---------------------------------------------------------------------------//
// Check if a std::unordered_set iterator is a const iterator
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( IteratorTypeTraits,
                                   unordered_set_IsConstIterator,
                                   T )
{
  // std::unordered_set only provides a const iterator type
  TEST_ASSERT( (Utility::IsConstIterator<typename std::unordered_set<T>::iterator>::value) );
  TEST_ASSERT( (Utility::IsConstIterator<typename std::unordered_set<T>::const_iterator>::value) );
}

UNIT_TEST_TEMPLATE_1_INSTANT( IteratorTypeTraits, unordered_set_IsConstIterator );

//---------------------------------------------------------------------------//
// Check if std::unordered_set iterator types can be converted to const iterator types
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( IteratorTypeTraits,
                                   unordered_set_ConstIterator,
                                   T )
{
  TEST_ASSERT( (std::is_same<typename Utility::ConstIterator<typename std::unordered_set<T>::iterator>::type,typename std::unordered_set<T>::const_iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::ConstIterator<typename std::unordered_set<T>::const_iterator>::type,typename std::unordered_set<T>::const_iterator>::value) );
}

UNIT_TEST_TEMPLATE_1_INSTANT( IteratorTypeTraits, unordered_set_ConstIterator );

//---------------------------------------------------------------------------//
// Check if a std::map iterator is a const iterator
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( IteratorTypeTraits,
                                   map_IsConstIterator,
                                   Key,
                                   T )
{
  TEST_ASSERT( !(Utility::IsConstIterator<typename std::map<Key,T>::iterator>::value) );
  TEST_ASSERT( (Utility::IsConstIterator<typename std::map<Key,T>::const_iterator>::value) );
  TEST_ASSERT( !(Utility::IsConstIterator<typename std::map<Key,T>::reverse_iterator>::value) );
  TEST_ASSERT( (Utility::IsConstIterator<typename std::map<Key,T>::const_reverse_iterator>::value) );
}

UNIT_TEST_TEMPLATE_2_INSTANT( IteratorTypeTraits, map_IsConstIterator );

//---------------------------------------------------------------------------//
// Check if std::map iterator types can be converted to const iterator types
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( IteratorTypeTraits,
                                   map_ConstIterator,
                                   Key,
                                   T )
{
  TEST_ASSERT( (std::is_same<typename Utility::ConstIterator<typename std::map<Key,T>::iterator>::type,typename std::map<Key,T>::const_iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::ConstIterator<typename std::map<Key,T>::const_iterator>::type,typename std::map<Key,T>::const_iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::ConstIterator<typename std::map<Key,T>::reverse_iterator>::type,typename std::map<Key,T>::const_reverse_iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::ConstIterator<typename std::map<Key,T>::const_reverse_iterator>::type,typename std::map<Key,T>::const_reverse_iterator>::value) );
}

UNIT_TEST_TEMPLATE_2_INSTANT( IteratorTypeTraits, map_ConstIterator );

//---------------------------------------------------------------------------//
// Check if std::map const iterator types can be converted to non-const
// iterator types
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( IteratorTypeTraits,
                                   map_NonConstIterator,
                                   Key,
                                   T )
{
  TEST_ASSERT( (std::is_same<typename Utility::NonConstIterator<typename std::map<Key,T>::iterator>::type,typename std::map<Key,T>::iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::NonConstIterator<typename std::map<Key,T>::const_iterator>::type,typename std::map<Key,T>::iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::NonConstIterator<typename std::map<Key,T>::reverse_iterator>::type,typename std::map<Key,T>::reverse_iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::NonConstIterator<typename std::map<Key,T>::const_reverse_iterator>::type,typename std::map<Key,T>::reverse_iterator>::value) );
}

UNIT_TEST_TEMPLATE_2_INSTANT( IteratorTypeTraits, map_NonConstIterator );

//---------------------------------------------------------------------------//
// Check if a std::unordered_map iterator is a const iterator
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( IteratorTypeTraits,
                                   unordered_map_IsConstIterator,
                                   Key,
                                   T )
{
  TEST_ASSERT( !(Utility::IsConstIterator<typename std::unordered_map<Key,T>::iterator>::value) );
  TEST_ASSERT( (Utility::IsConstIterator<typename std::unordered_map<Key,T>::const_iterator>::value) );
}

UNIT_TEST_TEMPLATE_2_INSTANT( IteratorTypeTraits, unordered_map_IsConstIterator );

//---------------------------------------------------------------------------//
// Check if std::unordered_map iterator types can be converted to const iterator types
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( IteratorTypeTraits,
                                   unordered_map_ConstIterator,
                                   Key,
                                   T )
{
  TEST_ASSERT( (std::is_same<typename Utility::ConstIterator<typename std::unordered_map<Key,T>::iterator>::type,typename std::unordered_map<Key,T>::const_iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::ConstIterator<typename std::unordered_map<Key,T>::const_iterator>::type,typename std::unordered_map<Key,T>::const_iterator>::value) );
}

UNIT_TEST_TEMPLATE_2_INSTANT( IteratorTypeTraits, unordered_map_ConstIterator );

//---------------------------------------------------------------------------//
// Check if std::unordered_map const iterator types can be converted to non-const
// iterator types
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( IteratorTypeTraits,
                                   unordered_map_NonConstIterator,
                                   Key,
                                   T )
{
  TEST_ASSERT( (std::is_same<typename Utility::NonConstIterator<typename std::unordered_map<Key,T>::iterator>::type,typename std::unordered_map<Key,T>::iterator>::value) );
  TEST_ASSERT( (std::is_same<typename Utility::NonConstIterator<typename std::unordered_map<Key,T>::const_iterator>::type,typename std::unordered_map<Key,T>::iterator>::value) );
}

UNIT_TEST_TEMPLATE_2_INSTANT( IteratorTypeTraits, unordered_map_NonConstIterator );

//---------------------------------------------------------------------------//
// end tstIteratorTypeTraits.cpp
//---------------------------------------------------------------------------//
