//---------------------------------------------------------------------------//
//!
//! \file   tstTypeTraits.cpp
//! \author Alex Robinson
//! \brief  Type traits unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <type_traits>
#include <utility>
#include <tuple>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_TypeTraits.hpp"

typedef unsigned char uchar;
typedef signed char schar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef long long longlong;
typedef unsigned long long ulonglong;
typedef std::string string;
typedef std::pair<int,double> pair_int_double;

//---------------------------------------------------------------------------//
// Instantiation Macros
//---------------------------------------------------------------------------//
#define UNIT_TEST_TEMPLATE_1_INSTANT( type, name )      \
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
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, double );           \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, string );           \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, pair_int_double )

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check if a type is a pointer-to-const
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TypeTraits, IsPointerToConst, T )
{
  TEST_ASSERT( !Utility::IsPointerToConst<T>::value );
  TEST_ASSERT( !Utility::IsPointerToConst<T*>::value );
  TEST_ASSERT( !Utility::IsPointerToConst<T* const>::value );
  TEST_ASSERT( Utility::IsPointerToConst<const T*>::value );
  TEST_ASSERT( Utility::IsPointerToConst<const T* const>::value );
}

UNIT_TEST_TEMPLATE_1_INSTANT( TypeTraits, IsPointerToConst );

//---------------------------------------------------------------------------//
// Check if a type is hashable
TEUCHOS_UNIT_TEST( TypeTraits, IsHashable )
{
  TEST_ASSERT( Utility::IsHashable<void*>::value );
  
  TEST_ASSERT( Utility::IsHashable<bool>::value );
  TEST_ASSERT( Utility::IsHashable<bool*>::value );
  TEST_ASSERT( Utility::IsHashable<std::unique_ptr<bool> >::value );
  TEST_ASSERT( Utility::IsHashable<std::shared_ptr<bool> >::value );
  
  TEST_ASSERT( Utility::IsHashable<char>::value );
  TEST_ASSERT( Utility::IsHashable<char*>::value );
  TEST_ASSERT( Utility::IsHashable<std::unique_ptr<char> >::value );
  TEST_ASSERT( Utility::IsHashable<std::shared_ptr<char> >::value );
  
  TEST_ASSERT( Utility::IsHashable<signed char>::value );
  TEST_ASSERT( Utility::IsHashable<signed char*>::value );
  TEST_ASSERT( Utility::IsHashable<std::unique_ptr<signed char> >::value );
  TEST_ASSERT( Utility::IsHashable<std::shared_ptr<signed char> >::value );
  
  TEST_ASSERT( Utility::IsHashable<unsigned char>::value );
  TEST_ASSERT( Utility::IsHashable<unsigned char*>::value );
  TEST_ASSERT( Utility::IsHashable<std::unique_ptr<unsigned char> >::value );
  TEST_ASSERT( Utility::IsHashable<std::shared_ptr<unsigned char> >::value );
  
  TEST_ASSERT( Utility::IsHashable<char16_t>::value );
  TEST_ASSERT( Utility::IsHashable<char16_t*>::value );
  TEST_ASSERT( Utility::IsHashable<std::unique_ptr<char16_t> >::value );
  TEST_ASSERT( Utility::IsHashable<std::shared_ptr<char16_t> >::value );
  
  TEST_ASSERT( Utility::IsHashable<char32_t>::value );
  TEST_ASSERT( Utility::IsHashable<char32_t*>::value );
  TEST_ASSERT( Utility::IsHashable<std::unique_ptr<char32_t> >::value );
  TEST_ASSERT( Utility::IsHashable<std::shared_ptr<char32_t> >::value );
  
  TEST_ASSERT( Utility::IsHashable<wchar_t>::value );
  TEST_ASSERT( Utility::IsHashable<wchar_t*>::value );
  TEST_ASSERT( Utility::IsHashable<std::unique_ptr<wchar_t> >::value );
  TEST_ASSERT( Utility::IsHashable<std::shared_ptr<wchar_t> >::value );
  
  TEST_ASSERT( Utility::IsHashable<short>::value );
  TEST_ASSERT( Utility::IsHashable<short*>::value );
  TEST_ASSERT( Utility::IsHashable<std::unique_ptr<short> >::value );
  TEST_ASSERT( Utility::IsHashable<std::shared_ptr<short> >::value );
  
  TEST_ASSERT( Utility::IsHashable<unsigned short>::value );
  TEST_ASSERT( Utility::IsHashable<unsigned short*>::value );
  TEST_ASSERT( Utility::IsHashable<std::unique_ptr<unsigned short> >::value );
  TEST_ASSERT( Utility::IsHashable<std::shared_ptr<unsigned short> >::value );
  
  TEST_ASSERT( Utility::IsHashable<int>::value );
  TEST_ASSERT( Utility::IsHashable<int*>::value );
  TEST_ASSERT( Utility::IsHashable<std::unique_ptr<int> >::value );
  TEST_ASSERT( Utility::IsHashable<std::shared_ptr<int> >::value );
  
  TEST_ASSERT( Utility::IsHashable<unsigned int>::value );
  TEST_ASSERT( Utility::IsHashable<unsigned int*>::value );
  TEST_ASSERT( Utility::IsHashable<std::unique_ptr<unsigned int> >::value );
  TEST_ASSERT( Utility::IsHashable<std::shared_ptr<unsigned int> >::value );
  
  TEST_ASSERT( Utility::IsHashable<long>::value );
  TEST_ASSERT( Utility::IsHashable<long*>::value );
  TEST_ASSERT( Utility::IsHashable<std::unique_ptr<long> >::value );
  TEST_ASSERT( Utility::IsHashable<std::shared_ptr<long> >::value );
  
  TEST_ASSERT( Utility::IsHashable<unsigned long>::value );
  TEST_ASSERT( Utility::IsHashable<unsigned long*>::value );
  TEST_ASSERT( Utility::IsHashable<std::unique_ptr<unsigned long> >::value );
  TEST_ASSERT( Utility::IsHashable<std::shared_ptr<unsigned long> >::value );
  
  TEST_ASSERT( Utility::IsHashable<long long>::value );
  TEST_ASSERT( Utility::IsHashable<long long*>::value );
  TEST_ASSERT( Utility::IsHashable<std::unique_ptr<long long> >::value );
  TEST_ASSERT( Utility::IsHashable<std::shared_ptr<long long> >::value );
  
  TEST_ASSERT( Utility::IsHashable<unsigned long long>::value );
  TEST_ASSERT( Utility::IsHashable<unsigned long long*>::value );
  TEST_ASSERT( Utility::IsHashable<std::unique_ptr<unsigned long long> >::value );
  TEST_ASSERT( Utility::IsHashable<std::shared_ptr<unsigned long long> >::value );
  
  TEST_ASSERT( Utility::IsHashable<float>::value );
  TEST_ASSERT( Utility::IsHashable<float*>::value );
  TEST_ASSERT( Utility::IsHashable<std::unique_ptr<float> >::value );
  TEST_ASSERT( Utility::IsHashable<std::shared_ptr<float> >::value );
  
  TEST_ASSERT( Utility::IsHashable<double>::value );
  TEST_ASSERT( Utility::IsHashable<double*>::value );
  TEST_ASSERT( Utility::IsHashable<std::unique_ptr<double> >::value );
  TEST_ASSERT( Utility::IsHashable<std::shared_ptr<double> >::value );
  
  TEST_ASSERT( Utility::IsHashable<long double>::value );
  TEST_ASSERT( Utility::IsHashable<long double*>::value );
  TEST_ASSERT( Utility::IsHashable<std::unique_ptr<long double> >::value );
  TEST_ASSERT( Utility::IsHashable<std::shared_ptr<long double> >::value );
  
  TEST_ASSERT( Utility::IsHashable<std::string>::value );
  TEST_ASSERT( Utility::IsHashable<std::string*>::value );
  TEST_ASSERT( Utility::IsHashable<std::unique_ptr<std::string> >::value );
  TEST_ASSERT( Utility::IsHashable<std::shared_ptr<std::string> >::value );
  
  TEST_ASSERT( Utility::IsHashable<std::u16string>::value );
  TEST_ASSERT( Utility::IsHashable<std::u16string*>::value );
  TEST_ASSERT( Utility::IsHashable<std::unique_ptr<std::u16string> >::value );
  TEST_ASSERT( Utility::IsHashable<std::shared_ptr<std::u16string> >::value );
  
  TEST_ASSERT( Utility::IsHashable<std::u32string>::value );
  TEST_ASSERT( Utility::IsHashable<std::u32string*>::value );
  TEST_ASSERT( Utility::IsHashable<std::unique_ptr<std::u32string> >::value );
  TEST_ASSERT( Utility::IsHashable<std::shared_ptr<std::u32string> >::value );
  
  TEST_ASSERT( Utility::IsHashable<std::wstring>::value );
  TEST_ASSERT( Utility::IsHashable<std::wstring*>::value );
  TEST_ASSERT( Utility::IsHashable<std::unique_ptr<std::wstring> >::value );
  TEST_ASSERT( Utility::IsHashable<std::shared_ptr<std::wstring> >::value );
  
  TEST_ASSERT( Utility::IsHashable<std::error_code>::value );
  TEST_ASSERT( Utility::IsHashable<std::error_code*>::value );
  TEST_ASSERT( Utility::IsHashable<std::unique_ptr<std::error_code> >::value );
  TEST_ASSERT( Utility::IsHashable<std::shared_ptr<std::error_code> >::value );
  
  TEST_ASSERT( Utility::IsHashable<std::bitset<1> >::value );
  TEST_ASSERT( Utility::IsHashable<std::bitset<1>*>::value );
  TEST_ASSERT( Utility::IsHashable<std::unique_ptr<std::bitset<1> > >::value );
  TEST_ASSERT( Utility::IsHashable<std::shared_ptr<std::bitset<1> > >::value );
  
  TEST_ASSERT( Utility::IsHashable<std::bitset<10> >::value );
  TEST_ASSERT( Utility::IsHashable<std::bitset<10>*>::value );
  TEST_ASSERT( Utility::IsHashable<std::unique_ptr<std::bitset<10> > >::value );
  TEST_ASSERT( Utility::IsHashable<std::shared_ptr<std::bitset<10> > >::value );
  
  TEST_ASSERT( Utility::IsHashable<std::bitset<100> >::value );
  TEST_ASSERT( Utility::IsHashable<std::bitset<100>*>::value );
  TEST_ASSERT( Utility::IsHashable<std::unique_ptr<std::bitset<100> > >::value );
  TEST_ASSERT( Utility::IsHashable<std::shared_ptr<std::bitset<100> > >::value );
  
  TEST_ASSERT( Utility::IsHashable<std::type_index>::value );
  TEST_ASSERT( Utility::IsHashable<std::type_index*>::value );
  TEST_ASSERT( Utility::IsHashable<std::unique_ptr<std::type_index> >::value );
  TEST_ASSERT( Utility::IsHashable<std::shared_ptr<std::type_index> >::value );
  
  TEST_ASSERT( Utility::IsHashable<std::vector<bool> >::value );
  TEST_ASSERT( Utility::IsHashable<std::vector<bool>*>::value );
  TEST_ASSERT( Utility::IsHashable<std::unique_ptr<std::vector<bool> > >::value );
  TEST_ASSERT( Utility::IsHashable<std::shared_ptr<std::vector<bool> > >::value );

  TEST_ASSERT( !Utility::IsHashable<std::vector<int> >::value );
  TEST_ASSERT( Utility::IsHashable<std::vector<int>*>::value );
  TEST_ASSERT( Utility::IsHashable<std::unique_ptr<std::vector<int> > >::value );
  TEST_ASSERT( Utility::IsHashable<std::shared_ptr<std::vector<int> > >::value );

  TEST_ASSERT( !Utility::IsHashable<std::vector<double> >::value );
  TEST_ASSERT( Utility::IsHashable<std::vector<double>*>::value );
  TEST_ASSERT( Utility::IsHashable<std::unique_ptr<std::vector<double> > >::value );
  TEST_ASSERT( Utility::IsHashable<std::shared_ptr<std::vector<double> > >::value );
  
  TEST_ASSERT( Utility::IsHashable<std::thread::id>::value );
  TEST_ASSERT( Utility::IsHashable<std::thread::id*>::value );
  TEST_ASSERT( Utility::IsHashable<std::unique_ptr<std::thread::id> >::value );
  TEST_ASSERT( Utility::IsHashable<std::shared_ptr<std::thread::id > >::value );
  
  TEST_ASSERT( !(Utility::IsHashable<std::pair<int,double> >::value) );
  TEST_ASSERT( (Utility::IsHashable<std::pair<int,double>*>::value) );
  TEST_ASSERT( (Utility::IsHashable<std::unique_ptr<std::pair<int,double> > >::value) );
  TEST_ASSERT( (Utility::IsHashable<std::shared_ptr<std::pair<int,double> > >::value) );
  
  TEST_ASSERT( !(Utility::IsHashable<std::tuple<int,double,float> >::value) );
  TEST_ASSERT( (Utility::IsHashable<std::tuple<int,double,float>*>::value) );
  TEST_ASSERT( (Utility::IsHashable<std::unique_ptr<std::tuple<int,double,float> > >::value) );
  TEST_ASSERT( (Utility::IsHashable<std::shared_ptr<std::tuple<int,double,float> > >::value) );
}

//---------------------------------------------------------------------------//
// end tstTypeTraits.cpp
//---------------------------------------------------------------------------//
