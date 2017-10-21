//---------------------------------------------------------------------------//
//!
//! \file   tstTypeTraits.cpp
//! \author Alex Robinson
//! \brief  Type traits unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <initializer_list>
#include <deque>
#include <list>
#include <forward_list>
#include <type_traits>
#include <utility>
#include <tuple>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>

// FRENSIE Includes
#include "Utility_TypeTraits.hpp"

//---------------------------------------------------------------------------//
// Template Test Types
//---------------------------------------------------------------------------//
typedef boost::mpl::list<bool, char, signed char, unsigned char, short, unsigned short, int, long, unsigned, unsigned long, long long, unsigned long long, float, double, std::string, std::pair<int,double>, std::tuple<bool,unsigned short, float> > TestTypes;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check if a types associated null pointer can be retrieved
BOOST_AUTO_TEST_CASE_TEMPLATE( NullPointer, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::NullPointer<T>::value, (T*)NULL );
  BOOST_CHECK_EQUAL( Utility::nullPointer<T>(), (T*)NULL );
  
  BOOST_CHECK_EQUAL( Utility::NullPointer<const T>::value, (T*)NULL );
  BOOST_CHECK_EQUAL( Utility::nullPointer<const T>(), (T*)NULL );

  BOOST_CHECK_EQUAL( Utility::NullPointer<T*>::value, (T**)NULL );
  BOOST_CHECK_EQUAL( Utility::nullPointer<T*>(), (T**)NULL );
  
  BOOST_CHECK_EQUAL( Utility::NullPointer<const T*>::value, (T**)NULL );
  BOOST_CHECK_EQUAL( Utility::nullPointer<const T*>(), (T**)NULL );
}

//---------------------------------------------------------------------------//
// Check if a type is a pointer-to-const
BOOST_AUTO_TEST_CASE_TEMPLATE( IsPointerToConst, T, TestTypes )
{
  BOOST_CHECK( !Utility::IsPointerToConst<T>::value );
  BOOST_CHECK( !Utility::IsPointerToConst<T*>::value );
  BOOST_CHECK( !Utility::IsPointerToConst<T* const>::value );
  BOOST_CHECK( Utility::IsPointerToConst<const T*>::value );
  BOOST_CHECK( Utility::IsPointerToConst<const T* const>::value );
}

//---------------------------------------------------------------------------//
// Check if a type is hashable
BOOST_AUTO_TEST_CASE( IsHashable )
{
  BOOST_CHECK( Utility::IsHashable<void*>::value );
  BOOST_CHECK( Utility::IsHashable<const void*>::value );
  BOOST_CHECK( Utility::IsHashable<void* const>::value );
  BOOST_CHECK( Utility::IsHashable<const void* const>::value );
  
  BOOST_CHECK( Utility::IsHashable<bool>::value );
  BOOST_CHECK( Utility::IsHashable<const bool>::value );
  BOOST_CHECK( Utility::IsHashable<bool*>::value );
  BOOST_CHECK( Utility::IsHashable<const bool*>::value );
  BOOST_CHECK( Utility::IsHashable<bool* const>::value );
  BOOST_CHECK( Utility::IsHashable<const bool* const>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<bool> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<bool> >::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<const bool> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<const bool> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<bool> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<bool> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<const bool> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<const bool> >::value );
  
  BOOST_CHECK( Utility::IsHashable<char>::value );
  BOOST_CHECK( Utility::IsHashable<const char>::value );
  BOOST_CHECK( Utility::IsHashable<char*>::value );
  BOOST_CHECK( Utility::IsHashable<const char*>::value );
  BOOST_CHECK( Utility::IsHashable<char* const>::value );
  BOOST_CHECK( Utility::IsHashable<const char* const>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<char> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<char> >::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<const char> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<const char> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<char> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<char> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<const char> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<const char> >::value );
  
  BOOST_CHECK( Utility::IsHashable<signed char>::value );
  BOOST_CHECK( Utility::IsHashable<const signed char>::value );
  BOOST_CHECK( Utility::IsHashable<signed char*>::value );
  BOOST_CHECK( Utility::IsHashable<const signed char*>::value );
  BOOST_CHECK( Utility::IsHashable<signed char* const>::value );
  BOOST_CHECK( Utility::IsHashable<const signed char* const>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<signed char> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<signed char> >::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<const signed char> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<const signed char> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<signed char> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<signed char> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<const signed char> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<const signed char> >::value );
  
  BOOST_CHECK( Utility::IsHashable<unsigned char>::value );
  BOOST_CHECK( Utility::IsHashable<const unsigned char>::value );
  BOOST_CHECK( Utility::IsHashable<unsigned char*>::value );
  BOOST_CHECK( Utility::IsHashable<const unsigned char*>::value );
  BOOST_CHECK( Utility::IsHashable<unsigned char* const>::value );
  BOOST_CHECK( Utility::IsHashable<const unsigned char* const>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<unsigned char> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<unsigned char> >::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<const unsigned char> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<const unsigned char> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<unsigned char> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<unsigned char> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<const unsigned char> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<const unsigned char> >::value );
  
  BOOST_CHECK( Utility::IsHashable<char16_t>::value );
  BOOST_CHECK( Utility::IsHashable<const char16_t>::value );
  BOOST_CHECK( Utility::IsHashable<char16_t*>::value );
  BOOST_CHECK( Utility::IsHashable<const char16_t*>::value );
  BOOST_CHECK( Utility::IsHashable<char16_t* const>::value );
  BOOST_CHECK( Utility::IsHashable<const char16_t* const>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<char16_t> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<char16_t> >::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<const char16_t> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<const char16_t> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<char16_t> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<char16_t> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<const char16_t> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<const char16_t> >::value );
  
  BOOST_CHECK( Utility::IsHashable<char32_t>::value );
  BOOST_CHECK( Utility::IsHashable<const char32_t>::value );
  BOOST_CHECK( Utility::IsHashable<char32_t*>::value );
  BOOST_CHECK( Utility::IsHashable<const char32_t*>::value );
  BOOST_CHECK( Utility::IsHashable<char32_t* const>::value );
  BOOST_CHECK( Utility::IsHashable<const char32_t* const>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<char32_t> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<char32_t> >::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<const char32_t> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<const char32_t> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<char32_t> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<char32_t> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<const char32_t> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<const char32_t> >::value );
  
  BOOST_CHECK( Utility::IsHashable<wchar_t>::value );
  BOOST_CHECK( Utility::IsHashable<const wchar_t>::value );
  BOOST_CHECK( Utility::IsHashable<wchar_t*>::value );
  BOOST_CHECK( Utility::IsHashable<const wchar_t*>::value );
  BOOST_CHECK( Utility::IsHashable<wchar_t* const>::value );
  BOOST_CHECK( Utility::IsHashable<const wchar_t* const>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<wchar_t> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<wchar_t> >::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<const wchar_t> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<const wchar_t> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<wchar_t> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<wchar_t> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<const wchar_t> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<const wchar_t> >::value );
  
  BOOST_CHECK( Utility::IsHashable<short>::value );
  BOOST_CHECK( Utility::IsHashable<const short>::value );
  BOOST_CHECK( Utility::IsHashable<short*>::value );
  BOOST_CHECK( Utility::IsHashable<const short*>::value );
  BOOST_CHECK( Utility::IsHashable<short* const>::value );
  BOOST_CHECK( Utility::IsHashable<const short* const>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<short> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<short> >::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<const short> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<const short> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<short> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<short> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<const short> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<const short> >::value );
  
  BOOST_CHECK( Utility::IsHashable<unsigned short>::value );
  BOOST_CHECK( Utility::IsHashable<const unsigned short>::value );
  BOOST_CHECK( Utility::IsHashable<unsigned short*>::value );
  BOOST_CHECK( Utility::IsHashable<const unsigned short*>::value );
  BOOST_CHECK( Utility::IsHashable<unsigned short* const>::value );
  BOOST_CHECK( Utility::IsHashable<const unsigned short* const>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<unsigned short> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<unsigned short> >::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<const unsigned short> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<const unsigned short> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<unsigned short> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<unsigned short> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<const unsigned short> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<const unsigned short> >::value );
  
  BOOST_CHECK( Utility::IsHashable<int>::value );
  BOOST_CHECK( Utility::IsHashable<const int>::value );
  BOOST_CHECK( Utility::IsHashable<int*>::value );
  BOOST_CHECK( Utility::IsHashable<const int*>::value );
  BOOST_CHECK( Utility::IsHashable<int* const>::value );
  BOOST_CHECK( Utility::IsHashable<const int* const>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<int> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<int> >::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<const int> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<const int> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<int> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<int> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<const int> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<const int> >::value );
  
  BOOST_CHECK( Utility::IsHashable<unsigned int>::value );
  BOOST_CHECK( Utility::IsHashable<const unsigned int>::value );
  BOOST_CHECK( Utility::IsHashable<unsigned int*>::value );
  BOOST_CHECK( Utility::IsHashable<const unsigned int*>::value );
  BOOST_CHECK( Utility::IsHashable<unsigned int* const>::value );
  BOOST_CHECK( Utility::IsHashable<const unsigned int* const>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<unsigned int> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<unsigned int> >::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<const unsigned int> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<const unsigned int> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<unsigned int> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<unsigned int> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<const unsigned int> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<const unsigned int> >::value );
  
  BOOST_CHECK( Utility::IsHashable<long>::value );
  BOOST_CHECK( Utility::IsHashable<const long>::value );
  BOOST_CHECK( Utility::IsHashable<long*>::value );
  BOOST_CHECK( Utility::IsHashable<const long*>::value );
  BOOST_CHECK( Utility::IsHashable<long* const>::value );
  BOOST_CHECK( Utility::IsHashable<const long* const>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<long> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<long> >::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<const long> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<const long> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<long> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<long> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<const long> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<const long> >::value );
  
  BOOST_CHECK( Utility::IsHashable<unsigned long>::value );
  BOOST_CHECK( Utility::IsHashable<const unsigned long>::value );
  BOOST_CHECK( Utility::IsHashable<unsigned long*>::value );
  BOOST_CHECK( Utility::IsHashable<const unsigned long*>::value );
  BOOST_CHECK( Utility::IsHashable<unsigned long* const>::value );
  BOOST_CHECK( Utility::IsHashable<const unsigned long* const>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<unsigned long> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<unsigned long> >::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<const unsigned long> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<const unsigned long> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<unsigned long> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<unsigned long> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<const unsigned long> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<const unsigned long> >::value );
  
  BOOST_CHECK( Utility::IsHashable<long long>::value );
  BOOST_CHECK( Utility::IsHashable<const long long>::value );
  BOOST_CHECK( Utility::IsHashable<long long*>::value );
  BOOST_CHECK( Utility::IsHashable<const long long*>::value );
  BOOST_CHECK( Utility::IsHashable<long long* const>::value );
  BOOST_CHECK( Utility::IsHashable<const long long* const>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<long long> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<long long> >::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<const long long> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<const long long> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<long long> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<long long> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<const long long> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<const long long> >::value );
  
  BOOST_CHECK( Utility::IsHashable<unsigned long long>::value );
  BOOST_CHECK( Utility::IsHashable<const unsigned long long>::value );
  BOOST_CHECK( Utility::IsHashable<unsigned long long*>::value );
  BOOST_CHECK( Utility::IsHashable<const unsigned long long*>::value );
  BOOST_CHECK( Utility::IsHashable<unsigned long long* const>::value );
  BOOST_CHECK( Utility::IsHashable<const unsigned long long* const>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<unsigned long long> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<unsigned long long> >::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<const unsigned long long> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<const unsigned long long> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<unsigned long long> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<unsigned long long> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<const unsigned long long> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<const unsigned long long> >::value );
  
  BOOST_CHECK( Utility::IsHashable<float>::value );
  BOOST_CHECK( Utility::IsHashable<const float>::value );
  BOOST_CHECK( Utility::IsHashable<float*>::value );
  BOOST_CHECK( Utility::IsHashable<const float*>::value );
  BOOST_CHECK( Utility::IsHashable<float* const>::value );
  BOOST_CHECK( Utility::IsHashable<const float* const>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<float> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<float> >::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<const float> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<const float> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<float> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<float> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<const float> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<const float> >::value );
  
  BOOST_CHECK( Utility::IsHashable<double>::value );
  BOOST_CHECK( Utility::IsHashable<const double>::value );
  BOOST_CHECK( Utility::IsHashable<double*>::value );
  BOOST_CHECK( Utility::IsHashable<const double*>::value );
  BOOST_CHECK( Utility::IsHashable<double* const>::value );
  BOOST_CHECK( Utility::IsHashable<const double* const>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<double> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<double> >::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<const double> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<const double> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<double> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<double> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<const double> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<const double> >::value );
  
  BOOST_CHECK( Utility::IsHashable<long double>::value );
  BOOST_CHECK( Utility::IsHashable<const long double>::value );
  BOOST_CHECK( Utility::IsHashable<long double*>::value );
  BOOST_CHECK( Utility::IsHashable<const long double*>::value );
  BOOST_CHECK( Utility::IsHashable<long double* const>::value );
  BOOST_CHECK( Utility::IsHashable<const long double* const>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<long double> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<long double> >::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<const long double> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<const long double> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<long double> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<long double> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<const long double> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<const long double> >::value );
  
  BOOST_CHECK( Utility::IsHashable<std::string>::value );
  BOOST_CHECK( Utility::IsHashable<const std::string>::value );
  BOOST_CHECK( Utility::IsHashable<std::string*>::value );
  BOOST_CHECK( Utility::IsHashable<const std::string*>::value );
  BOOST_CHECK( Utility::IsHashable<std::string* const>::value );
  BOOST_CHECK( Utility::IsHashable<const std::string* const>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<std::string> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<std::string> >::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<const std::string> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<const std::string> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<std::string> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<std::string> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<const std::string> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<const std::string> >::value );
  
  BOOST_CHECK( Utility::IsHashable<std::u16string>::value );
  BOOST_CHECK( Utility::IsHashable<const std::u16string>::value );
  BOOST_CHECK( Utility::IsHashable<std::u16string*>::value );
  BOOST_CHECK( Utility::IsHashable<const std::u16string*>::value );
  BOOST_CHECK( Utility::IsHashable<std::u16string* const>::value );
  BOOST_CHECK( Utility::IsHashable<const std::u16string* const>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<std::u16string> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<std::u16string> >::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<const std::u16string> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<const std::u16string> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<std::u16string> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<std::u16string> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<const std::u16string> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<const std::u16string> >::value );
  
  BOOST_CHECK( Utility::IsHashable<std::u32string>::value );
  BOOST_CHECK( Utility::IsHashable<const std::u32string>::value );
  BOOST_CHECK( Utility::IsHashable<std::u32string*>::value );
  BOOST_CHECK( Utility::IsHashable<const std::u32string*>::value );
  BOOST_CHECK( Utility::IsHashable<std::u32string* const>::value );
  BOOST_CHECK( Utility::IsHashable<const std::u32string* const>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<std::u32string> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<std::u32string> >::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<const std::u32string> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<const std::u32string> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<std::u32string> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<std::u32string> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<const std::u32string> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<const std::u32string> >::value );
  
  BOOST_CHECK( Utility::IsHashable<std::wstring>::value );
  BOOST_CHECK( Utility::IsHashable<const std::wstring>::value );
  BOOST_CHECK( Utility::IsHashable<std::wstring*>::value );
  BOOST_CHECK( Utility::IsHashable<const std::wstring*>::value );
  BOOST_CHECK( Utility::IsHashable<std::wstring* const>::value );
  BOOST_CHECK( Utility::IsHashable<const std::wstring* const>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<std::wstring> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<std::wstring> >::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<const std::wstring> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<const std::wstring> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<std::wstring> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<std::wstring> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<const std::wstring> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<const std::wstring> >::value );
  
  BOOST_CHECK( Utility::IsHashable<std::error_code>::value );
  BOOST_CHECK( Utility::IsHashable<const std::error_code>::value );
  BOOST_CHECK( Utility::IsHashable<std::error_code*>::value );
  BOOST_CHECK( Utility::IsHashable<const std::error_code*>::value );
  BOOST_CHECK( Utility::IsHashable<std::error_code* const>::value );
  BOOST_CHECK( Utility::IsHashable<const std::error_code* const>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<std::error_code> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<std::error_code> >::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<const std::error_code> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<const std::error_code> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<std::error_code> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<std::error_code> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<const std::error_code> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<const std::error_code> >::value );
  
  BOOST_CHECK( Utility::IsHashable<std::bitset<1> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::bitset<1> >::value );
  BOOST_CHECK( Utility::IsHashable<std::bitset<1>*>::value );
  BOOST_CHECK( Utility::IsHashable<const std::bitset<1>*>::value );
  BOOST_CHECK( Utility::IsHashable<std::bitset<1>* const>::value );
  BOOST_CHECK( Utility::IsHashable<const std::bitset<1>* const>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<std::bitset<1> > >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<std::bitset<1> > >::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<const std::bitset<1> > >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<const std::bitset<1> > >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<std::bitset<1> > >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<std::bitset<1> > >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<const std::bitset<1> > >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<const std::bitset<1> > >::value );
  
  BOOST_CHECK( Utility::IsHashable<std::bitset<10> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::bitset<10> >::value );
  BOOST_CHECK( Utility::IsHashable<std::bitset<10>*>::value );
  BOOST_CHECK( Utility::IsHashable<const std::bitset<10>*>::value );
  BOOST_CHECK( Utility::IsHashable<std::bitset<10>* const>::value );
  BOOST_CHECK( Utility::IsHashable<const std::bitset<10>* const>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<std::bitset<10> > >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<std::bitset<10> > >::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<const std::bitset<10> > >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<const std::bitset<10> > >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<std::bitset<10> > >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<std::bitset<10> > >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<const std::bitset<10> > >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<const std::bitset<10> > >::value );
  
  BOOST_CHECK( Utility::IsHashable<std::bitset<100> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::bitset<100> >::value );
  BOOST_CHECK( Utility::IsHashable<std::bitset<100>*>::value );
  BOOST_CHECK( Utility::IsHashable<const std::bitset<100>*>::value );
  BOOST_CHECK( Utility::IsHashable<std::bitset<100>* const>::value );
  BOOST_CHECK( Utility::IsHashable<const std::bitset<100>* const>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<std::bitset<100> > >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<std::bitset<100> > >::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<const std::bitset<100> > >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<const std::bitset<100> > >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<std::bitset<100> > >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<std::bitset<100> > >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<const std::bitset<100> > >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<const std::bitset<100> > >::value );
  
  BOOST_CHECK( Utility::IsHashable<std::type_index>::value );
  BOOST_CHECK( Utility::IsHashable<const std::type_index>::value );
  BOOST_CHECK( Utility::IsHashable<std::type_index*>::value );
  BOOST_CHECK( Utility::IsHashable<std::type_index* const>::value );
  BOOST_CHECK( Utility::IsHashable<const std::type_index* const>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<std::type_index> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<std::type_index> >::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<const std::type_index> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<const std::type_index> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<std::type_index> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<std::type_index> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<const std::type_index> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<const std::type_index> >::value );
  
  BOOST_CHECK( Utility::IsHashable<std::vector<bool> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::vector<bool> >::value );
  BOOST_CHECK( Utility::IsHashable<std::vector<bool>*>::value );
  BOOST_CHECK( Utility::IsHashable<const std::vector<bool>*>::value );
  BOOST_CHECK( Utility::IsHashable<std::vector<bool>* const>::value );
  BOOST_CHECK( Utility::IsHashable<const std::vector<bool>* const>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<std::vector<bool> > >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<std::vector<bool> > >::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<const std::vector<bool> > >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<const std::vector<bool> > >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<std::vector<bool> > >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<std::vector<bool> > >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<const std::vector<bool> > >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<const std::vector<bool> > >::value );

  BOOST_CHECK( !Utility::IsHashable<std::vector<int> >::value );
  BOOST_CHECK( !Utility::IsHashable<const std::vector<int> >::value );
  BOOST_CHECK( Utility::IsHashable<std::vector<int>*>::value );
  BOOST_CHECK( Utility::IsHashable<const std::vector<int>*>::value );
  BOOST_CHECK( Utility::IsHashable<std::vector<int>* const>::value );
  BOOST_CHECK( Utility::IsHashable<const std::vector<int>* const>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<std::vector<int> > >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<std::vector<int> > >::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<const std::vector<int> > >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<const std::vector<int> > >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<std::vector<int> > >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<std::vector<int> > >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<const std::vector<int> > >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<const std::vector<int> > >::value );

  BOOST_CHECK( !Utility::IsHashable<std::vector<double> >::value );
  BOOST_CHECK( !Utility::IsHashable<const std::vector<double> >::value );
  BOOST_CHECK( Utility::IsHashable<std::vector<double>*>::value );
  BOOST_CHECK( Utility::IsHashable<const std::vector<double>*>::value );
  BOOST_CHECK( Utility::IsHashable<std::vector<double>* const>::value );
  BOOST_CHECK( Utility::IsHashable<const std::vector<double>* const>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<std::vector<double> > >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<std::vector<double> > >::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<const std::vector<double> > >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<const std::vector<double> > >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<std::vector<double> > >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<std::vector<double> > >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<const std::vector<double> > >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<const std::vector<double> > >::value );
  
  BOOST_CHECK( Utility::IsHashable<std::thread::id>::value );
  BOOST_CHECK( Utility::IsHashable<const std::thread::id>::value );
  BOOST_CHECK( Utility::IsHashable<std::thread::id*>::value );
  BOOST_CHECK( Utility::IsHashable<const std::thread::id*>::value );
  BOOST_CHECK( Utility::IsHashable<std::thread::id* const>::value );
  BOOST_CHECK( Utility::IsHashable<const std::thread::id* const>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<std::thread::id> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<std::thread::id> >::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<const std::thread::id> >::value );
  BOOST_CHECK( Utility::IsHashable<const std::unique_ptr<const std::thread::id> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<std::thread::id > >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<std::thread::id > >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<const std::thread::id > >::value );
  BOOST_CHECK( Utility::IsHashable<const std::shared_ptr<const std::thread::id > >::value );
  
  BOOST_CHECK( !(Utility::IsHashable<std::pair<int,double> >::value) );
  BOOST_CHECK( !(Utility::IsHashable<const std::pair<int,double> >::value) );
  BOOST_CHECK( (Utility::IsHashable<std::pair<int,double>*>::value) );
  BOOST_CHECK( (Utility::IsHashable<const std::pair<int,double>*>::value) );
  BOOST_CHECK( (Utility::IsHashable<std::pair<int,double>* const>::value) );
  BOOST_CHECK( (Utility::IsHashable<const std::pair<int,double>* const>::value) );
  BOOST_CHECK( (Utility::IsHashable<std::unique_ptr<std::pair<int,double> > >::value) );
  BOOST_CHECK( (Utility::IsHashable<const std::unique_ptr<std::pair<int,double> > >::value) );
  BOOST_CHECK( (Utility::IsHashable<std::unique_ptr<const std::pair<int,double> > >::value) );
  BOOST_CHECK( (Utility::IsHashable<const std::unique_ptr<const std::pair<int,double> > >::value) );
  BOOST_CHECK( (Utility::IsHashable<std::shared_ptr<std::pair<int,double> > >::value) );
  BOOST_CHECK( (Utility::IsHashable<const std::shared_ptr<std::pair<int,double> > >::value) );
  BOOST_CHECK( (Utility::IsHashable<std::shared_ptr<const std::pair<int,double> > >::value) );
  BOOST_CHECK( (Utility::IsHashable<const std::shared_ptr<const std::pair<int,double> > >::value) );
  
  BOOST_CHECK( !(Utility::IsHashable<std::tuple<int,double,float> >::value) );
  BOOST_CHECK( !(Utility::IsHashable<const std::tuple<int,double,float> >::value) );
  BOOST_CHECK( (Utility::IsHashable<std::tuple<int,double,float>*>::value) );
  BOOST_CHECK( (Utility::IsHashable<const std::tuple<int,double,float>*>::value) );
  BOOST_CHECK( (Utility::IsHashable<std::tuple<int,double,float>* const>::value) );
  BOOST_CHECK( (Utility::IsHashable<const std::tuple<int,double,float>* const>::value) );
  BOOST_CHECK( (Utility::IsHashable<std::unique_ptr<std::tuple<int,double,float> > >::value) );
  BOOST_CHECK( (Utility::IsHashable<const std::unique_ptr<std::tuple<int,double,float> > >::value) );
  BOOST_CHECK( (Utility::IsHashable<std::unique_ptr<const std::tuple<int,double,float> > >::value) );
  BOOST_CHECK( (Utility::IsHashable<const std::unique_ptr<const std::tuple<int,double,float> > >::value) );
  BOOST_CHECK( (Utility::IsHashable<std::shared_ptr<std::tuple<int,double,float> > >::value) );
  BOOST_CHECK( (Utility::IsHashable<const std::shared_ptr<std::tuple<int,double,float> > >::value) );
  BOOST_CHECK( (Utility::IsHashable<std::shared_ptr<const std::tuple<int,double,float> > >::value) );
  BOOST_CHECK( (Utility::IsHashable<const std::shared_ptr<const std::tuple<int,double,float> > >::value) );
}

//---------------------------------------------------------------------------//
// Check if a type is a tuple
BOOST_AUTO_TEST_CASE( IsTuple )
{
  // Non-tuple types
  BOOST_CHECK( !Utility::IsTuple<char>::value );
  BOOST_CHECK( !Utility::IsTuple<char*>::value );
  BOOST_CHECK( !Utility::IsTuple<const char>::value );
  BOOST_CHECK( !Utility::IsTuple<const char*>::value );
  BOOST_CHECK( !Utility::IsTuple<signed char>::value );
  BOOST_CHECK( !Utility::IsTuple<signed char*>::value );
  BOOST_CHECK( !Utility::IsTuple<const signed char>::value );
  BOOST_CHECK( !Utility::IsTuple<const signed char*>::value );
  BOOST_CHECK( !Utility::IsTuple<unsigned char>::value );
  BOOST_CHECK( !Utility::IsTuple<unsigned char*>::value );
  BOOST_CHECK( !Utility::IsTuple<const unsigned char>::value );
  BOOST_CHECK( !Utility::IsTuple<const unsigned char*>::value );
  BOOST_CHECK( !Utility::IsTuple<short>::value );
  BOOST_CHECK( !Utility::IsTuple<short*>::value );
  BOOST_CHECK( !Utility::IsTuple<const short>::value );
  BOOST_CHECK( !Utility::IsTuple<const short*>::value );
  BOOST_CHECK( !Utility::IsTuple<unsigned short>::value );
  BOOST_CHECK( !Utility::IsTuple<unsigned short*>::value );
  BOOST_CHECK( !Utility::IsTuple<const unsigned short>::value );
  BOOST_CHECK( !Utility::IsTuple<const unsigned short*>::value );
  BOOST_CHECK( !Utility::IsTuple<int>::value );
  BOOST_CHECK( !Utility::IsTuple<int*>::value );
  BOOST_CHECK( !Utility::IsTuple<const int>::value );
  BOOST_CHECK( !Utility::IsTuple<const int*>::value );
  BOOST_CHECK( !Utility::IsTuple<unsigned int>::value );
  BOOST_CHECK( !Utility::IsTuple<unsigned int*>::value );
  BOOST_CHECK( !Utility::IsTuple<const unsigned int>::value );
  BOOST_CHECK( !Utility::IsTuple<const unsigned int*>::value );
  BOOST_CHECK( !Utility::IsTuple<long>::value );
  BOOST_CHECK( !Utility::IsTuple<long*>::value );
  BOOST_CHECK( !Utility::IsTuple<const long>::value );
  BOOST_CHECK( !Utility::IsTuple<const long*>::value );
  BOOST_CHECK( !Utility::IsTuple<unsigned long>::value );
  BOOST_CHECK( !Utility::IsTuple<unsigned long*>::value );
  BOOST_CHECK( !Utility::IsTuple<const unsigned long>::value );
  BOOST_CHECK( !Utility::IsTuple<const unsigned long*>::value );
  BOOST_CHECK( !Utility::IsTuple<long long>::value );
  BOOST_CHECK( !Utility::IsTuple<long long*>::value );
  BOOST_CHECK( !Utility::IsTuple<const long long>::value );
  BOOST_CHECK( !Utility::IsTuple<const long long*>::value );
  BOOST_CHECK( !Utility::IsTuple<unsigned long long>::value );
  BOOST_CHECK( !Utility::IsTuple<unsigned long long*>::value );
  BOOST_CHECK( !Utility::IsTuple<const unsigned long long>::value );
  BOOST_CHECK( !Utility::IsTuple<const unsigned long long*>::value );
  BOOST_CHECK( !Utility::IsTuple<float>::value );
  BOOST_CHECK( !Utility::IsTuple<float*>::value );
  BOOST_CHECK( !Utility::IsTuple<const float>::value );
  BOOST_CHECK( !Utility::IsTuple<const float*>::value );
  BOOST_CHECK( !Utility::IsTuple<double>::value );
  BOOST_CHECK( !Utility::IsTuple<double*>::value );
  BOOST_CHECK( !Utility::IsTuple<const double>::value );
  BOOST_CHECK( !Utility::IsTuple<const double*>::value );
  BOOST_CHECK( !Utility::IsTuple<std::string>::value );
  BOOST_CHECK( !Utility::IsTuple<std::string*>::value );
  BOOST_CHECK( !Utility::IsTuple<const std::string>::value );
  BOOST_CHECK( !Utility::IsTuple<const std::string*>::value );

  // std::pair types
  BOOST_CHECK( (Utility::IsTuple<std::pair<int,int> >::value) );
  BOOST_CHECK( !(Utility::IsTuple<std::pair<int,int>*>::value) );
  BOOST_CHECK( (Utility::IsTuple<const std::pair<int,int> >::value) );
  BOOST_CHECK( !(Utility::IsTuple<const std::pair<int,int>*>::value) );
  BOOST_CHECK( (Utility::IsTuple<std::pair<int,double> >::value) );
  BOOST_CHECK( !(Utility::IsTuple<std::pair<int,double>*>::value) );
  BOOST_CHECK( (Utility::IsTuple<const std::pair<int,double> >::value) );
  BOOST_CHECK( !(Utility::IsTuple<const std::pair<int,double>*>::value) );
  BOOST_CHECK( (Utility::IsTuple<std::pair<double,double> >::value) );
  BOOST_CHECK( !(Utility::IsTuple<std::pair<double,double>*>::value) );
  BOOST_CHECK( (Utility::IsTuple<const std::pair<double,double> >::value) );
  BOOST_CHECK( !(Utility::IsTuple<const std::pair<double,double>*>::value) );

  // Empty std::tuple type
  BOOST_CHECK( Utility::IsTuple<std::tuple<> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<>*>::value );

  // Single element std::tuple types
  BOOST_CHECK( Utility::IsTuple<std::tuple<char> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<char>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<char*> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<char*>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<char&> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<char&>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<const char> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<const char>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<const char*> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<const char*>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<const char&> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<const char&>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<short> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<short>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<short*> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<short*>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<short&> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<short&>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<const short> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<const short>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<const short*> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<const short*>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<const short&> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<const short&>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<int> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<int>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<int*> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<int*>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<int&> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<int&>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<const int> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<const int>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<const int*> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<const int*>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<const int&> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<const int&>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<long> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<long>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<long*> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<long*>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<long&> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<long&>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<const long> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<const long>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<const long*> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<const long*>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<const long&> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<const long&>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<long long> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<long long>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<long long*> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<long long*>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<long long&> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<long long&>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<const long long> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<const long long>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<const long long*> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<const long long*>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<const long long&> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<const long long&>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<float> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<float>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<float*> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<float*>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<float&> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<float&>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<const float> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<const float>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<const float*> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<const float*>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<const float&> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<const float&>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<double> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<double>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<double*> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<double*>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<double&> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<double&>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<const double> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<const double>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<const double*> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<const double*>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<const double&> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<const double&>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<std::string> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<std::string>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<std::string*> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<std::string*>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<std::string&> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<std::string&>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<const std::string> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<const std::string>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<const std::string*> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<const std::string*>*>::value );
  BOOST_CHECK( Utility::IsTuple<std::tuple<const std::string&> >::value );
  BOOST_CHECK( !Utility::IsTuple<std::tuple<const std::string&>*>::value );

  // Two element std::tuple types
  BOOST_CHECK( (Utility::IsTuple<std::tuple<int,int> >::value) );
  BOOST_CHECK( !(Utility::IsTuple<std::tuple<int,int>*>::value) );
  BOOST_CHECK( (Utility::IsTuple<std::tuple<int,double> >::value) );
  BOOST_CHECK( !(Utility::IsTuple<std::tuple<int,double>*>::value) );
  BOOST_CHECK( (Utility::IsTuple<std::tuple<double,double> >::value) );
  BOOST_CHECK( !(Utility::IsTuple<std::tuple<double,double>*>::value) );

  // Three element std::tuple types
  BOOST_CHECK( (Utility::IsTuple<std::tuple<int,int,int> >::value) );
  BOOST_CHECK( !(Utility::IsTuple<std::tuple<int,int,int>*>::value) );
  BOOST_CHECK( (Utility::IsTuple<std::tuple<int,int,double> >::value) );
  BOOST_CHECK( !(Utility::IsTuple<std::tuple<int,int,double>*>::value) );
  BOOST_CHECK( (Utility::IsTuple<std::tuple<int,double,int> >::value) );
  BOOST_CHECK( !(Utility::IsTuple<std::tuple<int,double,int>*>::value) );
  BOOST_CHECK( (Utility::IsTuple<std::tuple<double,int,int> >::value) );
  BOOST_CHECK( !(Utility::IsTuple<std::tuple<double,int,int>*>::value) );
  BOOST_CHECK( (Utility::IsTuple<std::tuple<int,double,double> >::value) );
  BOOST_CHECK( !(Utility::IsTuple<std::tuple<int,double,double>*>::value) );
  BOOST_CHECK( (Utility::IsTuple<std::tuple<double,int,double> >::value) );
  BOOST_CHECK( !(Utility::IsTuple<std::tuple<double,int,double>*>::value) );
  BOOST_CHECK( (Utility::IsTuple<std::tuple<double,double,int> >::value) );
  BOOST_CHECK( !(Utility::IsTuple<std::tuple<double,double,int>*>::value) );
  BOOST_CHECK( (Utility::IsTuple<std::tuple<double,double,double> >::value) );
  BOOST_CHECK( !(Utility::IsTuple<std::tuple<double,double,double>*>::value) );

  // Four element std::tuple types
  BOOST_CHECK( (Utility::IsTuple<std::tuple<int,int,int,int> >::value) );
  BOOST_CHECK( !(Utility::IsTuple<std::tuple<int,int,int,int>*>::value) );
  BOOST_CHECK( (Utility::IsTuple<std::tuple<int,int,int,double> >::value) );
  BOOST_CHECK( !(Utility::IsTuple<std::tuple<int,int,int,double>*>::value) );
  BOOST_CHECK( (Utility::IsTuple<std::tuple<int,int,double,int> >::value) );
  BOOST_CHECK( !(Utility::IsTuple<std::tuple<int,int,double,int>*>::value) );
  BOOST_CHECK( (Utility::IsTuple<std::tuple<int,double,int,int> >::value) );
  BOOST_CHECK( !(Utility::IsTuple<std::tuple<int,double,int,int>*>::value) );
  BOOST_CHECK( (Utility::IsTuple<std::tuple<double,int,int,int> >::value) );
  BOOST_CHECK( !(Utility::IsTuple<std::tuple<double,int,int,int>*>::value) );
  BOOST_CHECK( (Utility::IsTuple<std::tuple<int,int,double,double> >::value) );
  BOOST_CHECK( !(Utility::IsTuple<std::tuple<int,int,double,double>*>::value) );
  BOOST_CHECK( (Utility::IsTuple<std::tuple<int,double,int,double> >::value) );
  BOOST_CHECK( !(Utility::IsTuple<std::tuple<int,double,int,double>*>::value) );
  BOOST_CHECK( (Utility::IsTuple<std::tuple<double,int,int,double> >::value) );
  BOOST_CHECK( !(Utility::IsTuple<std::tuple<double,int,int,double>*>::value) );
  BOOST_CHECK( (Utility::IsTuple<std::tuple<int,double,double,int> >::value) );
  BOOST_CHECK( !(Utility::IsTuple<std::tuple<int,double,double,int>*>::value) );
  BOOST_CHECK( (Utility::IsTuple<std::tuple<double,int,double,int> >::value) );
  BOOST_CHECK( !(Utility::IsTuple<std::tuple<double,int,double,int>*>::value) );
  BOOST_CHECK( (Utility::IsTuple<std::tuple<double,double,int,int> >::value) );
  BOOST_CHECK( !(Utility::IsTuple<std::tuple<double,double,int,int>*>::value) );
  BOOST_CHECK( (Utility::IsTuple<std::tuple<int,double,double,double> >::value) );
  BOOST_CHECK( !(Utility::IsTuple<std::tuple<int,double,double,double>*>::value) );
  BOOST_CHECK( (Utility::IsTuple<std::tuple<double,int,double,double> >::value) );
  BOOST_CHECK( !(Utility::IsTuple<std::tuple<double,int,double,double>*>::value) );
  BOOST_CHECK( (Utility::IsTuple<std::tuple<double,double,int,double> >::value) );
  BOOST_CHECK( !(Utility::IsTuple<std::tuple<double,double,int,double>*>::value) );
  BOOST_CHECK( (Utility::IsTuple<std::tuple<double,double,double,int> >::value) );
  BOOST_CHECK( !(Utility::IsTuple<std::tuple<double,double,double,int>*>::value) );
  BOOST_CHECK( (Utility::IsTuple<std::tuple<double,double,double,double> >::value) );
  BOOST_CHECK( !(Utility::IsTuple<std::tuple<double,double,double,double>*>::value) );
}

//---------------------------------------------------------------------------//
// Check if a type is a pair
BOOST_AUTO_TEST_CASE( IsPair )
{
  // Non-tuple types
  BOOST_CHECK( !Utility::IsPair<char>::value );
  BOOST_CHECK( !Utility::IsPair<char*>::value );
  BOOST_CHECK( !Utility::IsPair<const char>::value );
  BOOST_CHECK( !Utility::IsPair<const char*>::value );
  BOOST_CHECK( !Utility::IsPair<signed char>::value );
  BOOST_CHECK( !Utility::IsPair<signed char*>::value );
  BOOST_CHECK( !Utility::IsPair<const signed char>::value );
  BOOST_CHECK( !Utility::IsPair<const signed char*>::value );
  BOOST_CHECK( !Utility::IsPair<unsigned char>::value );
  BOOST_CHECK( !Utility::IsPair<unsigned char*>::value );
  BOOST_CHECK( !Utility::IsPair<const unsigned char>::value );
  BOOST_CHECK( !Utility::IsPair<const unsigned char*>::value );
  BOOST_CHECK( !Utility::IsPair<short>::value );
  BOOST_CHECK( !Utility::IsPair<short*>::value );
  BOOST_CHECK( !Utility::IsPair<const short>::value );
  BOOST_CHECK( !Utility::IsPair<const short*>::value );
  BOOST_CHECK( !Utility::IsPair<unsigned short>::value );
  BOOST_CHECK( !Utility::IsPair<unsigned short*>::value );
  BOOST_CHECK( !Utility::IsPair<const unsigned short>::value );
  BOOST_CHECK( !Utility::IsPair<const unsigned short*>::value );
  BOOST_CHECK( !Utility::IsPair<int>::value );
  BOOST_CHECK( !Utility::IsPair<int*>::value );
  BOOST_CHECK( !Utility::IsPair<const int>::value );
  BOOST_CHECK( !Utility::IsPair<const int*>::value );
  BOOST_CHECK( !Utility::IsPair<unsigned int>::value );
  BOOST_CHECK( !Utility::IsPair<unsigned int*>::value );
  BOOST_CHECK( !Utility::IsPair<const unsigned int>::value );
  BOOST_CHECK( !Utility::IsPair<const unsigned int*>::value );
  BOOST_CHECK( !Utility::IsPair<long>::value );
  BOOST_CHECK( !Utility::IsPair<long*>::value );
  BOOST_CHECK( !Utility::IsPair<const long>::value );
  BOOST_CHECK( !Utility::IsPair<const long*>::value );
  BOOST_CHECK( !Utility::IsPair<unsigned long>::value );
  BOOST_CHECK( !Utility::IsPair<unsigned long*>::value );
  BOOST_CHECK( !Utility::IsPair<const unsigned long>::value );
  BOOST_CHECK( !Utility::IsPair<const unsigned long*>::value );
  BOOST_CHECK( !Utility::IsPair<long long>::value );
  BOOST_CHECK( !Utility::IsPair<long long*>::value );
  BOOST_CHECK( !Utility::IsPair<const long long>::value );
  BOOST_CHECK( !Utility::IsPair<const long long*>::value );
  BOOST_CHECK( !Utility::IsPair<unsigned long long>::value );
  BOOST_CHECK( !Utility::IsPair<unsigned long long*>::value );
  BOOST_CHECK( !Utility::IsPair<const unsigned long long>::value );
  BOOST_CHECK( !Utility::IsPair<const unsigned long long*>::value );
  BOOST_CHECK( !Utility::IsPair<float>::value );
  BOOST_CHECK( !Utility::IsPair<float*>::value );
  BOOST_CHECK( !Utility::IsPair<const float>::value );
  BOOST_CHECK( !Utility::IsPair<const float*>::value );
  BOOST_CHECK( !Utility::IsPair<double>::value );
  BOOST_CHECK( !Utility::IsPair<double*>::value );
  BOOST_CHECK( !Utility::IsPair<const double>::value );
  BOOST_CHECK( !Utility::IsPair<const double*>::value );
  BOOST_CHECK( !Utility::IsPair<std::string>::value );
  BOOST_CHECK( !Utility::IsPair<std::string*>::value );
  BOOST_CHECK( !Utility::IsPair<const std::string>::value );
  BOOST_CHECK( !Utility::IsPair<const std::string*>::value );

  // std::pair types
  BOOST_CHECK( (Utility::IsPair<std::pair<int,int> >::value) );
  BOOST_CHECK( !(Utility::IsPair<std::pair<int,int>*>::value) );
  BOOST_CHECK( (Utility::IsPair<const std::pair<int,int> >::value) );
  BOOST_CHECK( !(Utility::IsPair<const std::pair<int,int>*>::value) );
  BOOST_CHECK( (Utility::IsPair<std::pair<int,double> >::value) );
  BOOST_CHECK( !(Utility::IsPair<std::pair<int,double>*>::value) );
  BOOST_CHECK( (Utility::IsPair<const std::pair<int,double> >::value) );
  BOOST_CHECK( !(Utility::IsPair<const std::pair<int,double>*>::value) );
  BOOST_CHECK( (Utility::IsPair<std::pair<double,double> >::value) );
  BOOST_CHECK( !(Utility::IsPair<std::pair<double,double>*>::value) );
  BOOST_CHECK( (Utility::IsPair<const std::pair<double,double> >::value) );
  BOOST_CHECK( !(Utility::IsPair<const std::pair<double,double>*>::value) );

  // Empty std::tuple type
  BOOST_CHECK( !Utility::IsPair<std::tuple<> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<>*>::value );

  // Single element std::tuple types
  BOOST_CHECK( !Utility::IsPair<std::tuple<char> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<char>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<char*> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<char*>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<char&> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<char&>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const char> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const char>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const char*> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const char*>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const char&> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const char&>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<short> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<short>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<short*> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<short*>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<short&> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<short&>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const short> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const short>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const short*> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const short*>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const short&> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const short&>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<int> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<int>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<int*> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<int*>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<int&> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<int&>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const int> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const int>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const int*> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const int*>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const int&> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const int&>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<long> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<long>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<long*> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<long*>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<long&> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<long&>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const long> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const long>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const long*> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const long*>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const long&> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const long&>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<long long> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<long long>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<long long*> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<long long*>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<long long&> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<long long&>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const long long> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const long long>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const long long*> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const long long*>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const long long&> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const long long&>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<float> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<float>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<float*> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<float*>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<float&> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<float&>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const float> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const float>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const float*> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const float*>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const float&> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const float&>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<double> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<double>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<double*> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<double*>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<double&> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<double&>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const double> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const double>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const double*> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const double*>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const double&> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const double&>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<std::string> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<std::string>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<std::string*> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<std::string*>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<std::string&> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<std::string&>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const std::string> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const std::string>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const std::string*> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const std::string*>*>::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const std::string&> >::value );
  BOOST_CHECK( !Utility::IsPair<std::tuple<const std::string&>*>::value );

  // Two element std::tuple types
  BOOST_CHECK( !(Utility::IsPair<std::tuple<int,int> >::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<int,int>*>::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<int,double> >::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<int,double>*>::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<double,double> >::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<double,double>*>::value) );

  // Three element std::tuple types
  BOOST_CHECK( !(Utility::IsPair<std::tuple<int,int,int> >::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<int,int,int>*>::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<int,int,double> >::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<int,int,double>*>::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<int,double,int> >::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<int,double,int>*>::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<double,int,int> >::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<double,int,int>*>::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<int,double,double> >::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<int,double,double>*>::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<double,int,double> >::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<double,int,double>*>::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<double,double,int> >::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<double,double,int>*>::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<double,double,double> >::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<double,double,double>*>::value) );

  // Four element std::tuple types
  BOOST_CHECK( !(Utility::IsPair<std::tuple<int,int,int,int> >::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<int,int,int,int>*>::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<int,int,int,double> >::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<int,int,int,double>*>::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<int,int,double,int> >::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<int,int,double,int>*>::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<int,double,int,int> >::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<int,double,int,int>*>::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<double,int,int,int> >::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<double,int,int,int>*>::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<int,int,double,double> >::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<int,int,double,double>*>::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<int,double,int,double> >::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<int,double,int,double>*>::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<double,int,int,double> >::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<double,int,int,double>*>::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<int,double,double,int> >::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<int,double,double,int>*>::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<double,int,double,int> >::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<double,int,double,int>*>::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<double,double,int,int> >::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<double,double,int,int>*>::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<int,double,double,double> >::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<int,double,double,double>*>::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<double,int,double,double> >::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<double,int,double,double>*>::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<double,double,int,double> >::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<double,double,int,double>*>::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<double,double,double,int> >::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<double,double,double,int>*>::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<double,double,double,double> >::value) );
  BOOST_CHECK( !(Utility::IsPair<std::tuple<double,double,double,double>*>::value) );
}

//---------------------------------------------------------------------------//
// Check if a type is a sequence container with contiguous memory
BOOST_AUTO_TEST_CASE( IsSequenceContainerWithContiguousMemory )
{
  // Basic Types
  BOOST_CHECK( !Utility::IsSequenceContainerWithContiguousMemory<int>::value );
  BOOST_CHECK( !Utility::IsSequenceContainerWithContiguousMemory<int*>::value );
  BOOST_CHECK( !Utility::IsSequenceContainerWithContiguousMemory<double>::value );
  BOOST_CHECK( !Utility::IsSequenceContainerWithContiguousMemory<double*>::value );

  // Sequence Container type
  BOOST_CHECK( (Utility::IsSequenceContainerWithContiguousMemory<std::array<int,1> >::value) );
  BOOST_CHECK( !(Utility::IsSequenceContainerWithContiguousMemory<std::array<int,1>*>::value) );
  BOOST_CHECK( (Utility::IsSequenceContainerWithContiguousMemory<std::array<int,10> >::value) );
  BOOST_CHECK( !(Utility::IsSequenceContainerWithContiguousMemory<std::array<int,10>*>::value) );
  BOOST_CHECK( (Utility::IsSequenceContainerWithContiguousMemory<std::array<double,1> >::value) );
  BOOST_CHECK( !(Utility::IsSequenceContainerWithContiguousMemory<std::array<double,1>*>::value) );
  BOOST_CHECK( (Utility::IsSequenceContainerWithContiguousMemory<std::array<double,10> >::value) );
  BOOST_CHECK( !(Utility::IsSequenceContainerWithContiguousMemory<std::array<double,10>*>::value) );

  BOOST_CHECK( Utility::IsSequenceContainerWithContiguousMemory<std::vector<int> >::value );
  BOOST_CHECK( !Utility::IsSequenceContainerWithContiguousMemory<std::vector<int>*>::value );
  BOOST_CHECK( Utility::IsSequenceContainerWithContiguousMemory<std::vector<double> >::value );
  BOOST_CHECK( !Utility::IsSequenceContainerWithContiguousMemory<std::vector<double>*>::value );

  BOOST_CHECK( Utility::IsSequenceContainerWithContiguousMemory<std::initializer_list<int> >::value );
  BOOST_CHECK( !Utility::IsSequenceContainerWithContiguousMemory<std::initializer_list<int>*>::value );
  BOOST_CHECK( Utility::IsSequenceContainerWithContiguousMemory<std::initializer_list<double> >::value );
  BOOST_CHECK( !Utility::IsSequenceContainerWithContiguousMemory<std::initializer_list<double>*>::value );

  BOOST_CHECK( Utility::IsSequenceContainerWithContiguousMemory<std::string>::value );
  BOOST_CHECK( !Utility::IsSequenceContainerWithContiguousMemory<std::string*>::value );
  BOOST_CHECK( Utility::IsSequenceContainerWithContiguousMemory<std::string>::value );
  BOOST_CHECK( !Utility::IsSequenceContainerWithContiguousMemory<std::string*>::value );

  BOOST_CHECK( !Utility::IsSequenceContainerWithContiguousMemory<std::deque<int> >::value );
  BOOST_CHECK( !Utility::IsSequenceContainerWithContiguousMemory<std::deque<int>*>::value );
  BOOST_CHECK( !Utility::IsSequenceContainerWithContiguousMemory<std::deque<double> >::value );
  BOOST_CHECK( !Utility::IsSequenceContainerWithContiguousMemory<std::deque<double>*>::value );

  BOOST_CHECK( !Utility::IsSequenceContainerWithContiguousMemory<std::list<int> >::value );
  BOOST_CHECK( !Utility::IsSequenceContainerWithContiguousMemory<std::list<int>*>::value );
  BOOST_CHECK( !Utility::IsSequenceContainerWithContiguousMemory<std::list<double> >::value );
  BOOST_CHECK( !Utility::IsSequenceContainerWithContiguousMemory<std::list<double>*>::value );

  BOOST_CHECK( !Utility::IsSequenceContainerWithContiguousMemory<std::forward_list<int> >::value );
  BOOST_CHECK( !Utility::IsSequenceContainerWithContiguousMemory<std::forward_list<int>*>::value );
  BOOST_CHECK( !Utility::IsSequenceContainerWithContiguousMemory<std::forward_list<double> >::value );
  BOOST_CHECK( !Utility::IsSequenceContainerWithContiguousMemory<std::forward_list<double>*>::value );
}

//---------------------------------------------------------------------------//
// end tstTypeTraits.cpp
//---------------------------------------------------------------------------//
