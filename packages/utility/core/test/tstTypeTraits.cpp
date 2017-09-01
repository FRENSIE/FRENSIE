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
  
  BOOST_CHECK( Utility::IsHashable<bool>::value );
  BOOST_CHECK( Utility::IsHashable<bool*>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<bool> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<bool> >::value );
  
  BOOST_CHECK( Utility::IsHashable<char>::value );
  BOOST_CHECK( Utility::IsHashable<char*>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<char> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<char> >::value );
  
  BOOST_CHECK( Utility::IsHashable<signed char>::value );
  BOOST_CHECK( Utility::IsHashable<signed char*>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<signed char> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<signed char> >::value );
  
  BOOST_CHECK( Utility::IsHashable<unsigned char>::value );
  BOOST_CHECK( Utility::IsHashable<unsigned char*>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<unsigned char> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<unsigned char> >::value );
  
  BOOST_CHECK( Utility::IsHashable<char16_t>::value );
  BOOST_CHECK( Utility::IsHashable<char16_t*>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<char16_t> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<char16_t> >::value );
  
  BOOST_CHECK( Utility::IsHashable<char32_t>::value );
  BOOST_CHECK( Utility::IsHashable<char32_t*>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<char32_t> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<char32_t> >::value );
  
  BOOST_CHECK( Utility::IsHashable<wchar_t>::value );
  BOOST_CHECK( Utility::IsHashable<wchar_t*>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<wchar_t> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<wchar_t> >::value );
  
  BOOST_CHECK( Utility::IsHashable<short>::value );
  BOOST_CHECK( Utility::IsHashable<short*>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<short> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<short> >::value );
  
  BOOST_CHECK( Utility::IsHashable<unsigned short>::value );
  BOOST_CHECK( Utility::IsHashable<unsigned short*>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<unsigned short> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<unsigned short> >::value );
  
  BOOST_CHECK( Utility::IsHashable<int>::value );
  BOOST_CHECK( Utility::IsHashable<int*>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<int> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<int> >::value );
  
  BOOST_CHECK( Utility::IsHashable<unsigned int>::value );
  BOOST_CHECK( Utility::IsHashable<unsigned int*>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<unsigned int> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<unsigned int> >::value );
  
  BOOST_CHECK( Utility::IsHashable<long>::value );
  BOOST_CHECK( Utility::IsHashable<long*>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<long> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<long> >::value );
  
  BOOST_CHECK( Utility::IsHashable<unsigned long>::value );
  BOOST_CHECK( Utility::IsHashable<unsigned long*>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<unsigned long> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<unsigned long> >::value );
  
  BOOST_CHECK( Utility::IsHashable<long long>::value );
  BOOST_CHECK( Utility::IsHashable<long long*>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<long long> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<long long> >::value );
  
  BOOST_CHECK( Utility::IsHashable<unsigned long long>::value );
  BOOST_CHECK( Utility::IsHashable<unsigned long long*>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<unsigned long long> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<unsigned long long> >::value );
  
  BOOST_CHECK( Utility::IsHashable<float>::value );
  BOOST_CHECK( Utility::IsHashable<float*>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<float> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<float> >::value );
  
  BOOST_CHECK( Utility::IsHashable<double>::value );
  BOOST_CHECK( Utility::IsHashable<double*>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<double> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<double> >::value );
  
  BOOST_CHECK( Utility::IsHashable<long double>::value );
  BOOST_CHECK( Utility::IsHashable<long double*>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<long double> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<long double> >::value );
  
  BOOST_CHECK( Utility::IsHashable<std::string>::value );
  BOOST_CHECK( Utility::IsHashable<std::string*>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<std::string> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<std::string> >::value );
  
  BOOST_CHECK( Utility::IsHashable<std::u16string>::value );
  BOOST_CHECK( Utility::IsHashable<std::u16string*>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<std::u16string> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<std::u16string> >::value );
  
  BOOST_CHECK( Utility::IsHashable<std::u32string>::value );
  BOOST_CHECK( Utility::IsHashable<std::u32string*>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<std::u32string> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<std::u32string> >::value );
  
  BOOST_CHECK( Utility::IsHashable<std::wstring>::value );
  BOOST_CHECK( Utility::IsHashable<std::wstring*>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<std::wstring> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<std::wstring> >::value );
  
  BOOST_CHECK( Utility::IsHashable<std::error_code>::value );
  BOOST_CHECK( Utility::IsHashable<std::error_code*>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<std::error_code> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<std::error_code> >::value );
  
  BOOST_CHECK( Utility::IsHashable<std::bitset<1> >::value );
  BOOST_CHECK( Utility::IsHashable<std::bitset<1>*>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<std::bitset<1> > >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<std::bitset<1> > >::value );
  
  BOOST_CHECK( Utility::IsHashable<std::bitset<10> >::value );
  BOOST_CHECK( Utility::IsHashable<std::bitset<10>*>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<std::bitset<10> > >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<std::bitset<10> > >::value );
  
  BOOST_CHECK( Utility::IsHashable<std::bitset<100> >::value );
  BOOST_CHECK( Utility::IsHashable<std::bitset<100>*>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<std::bitset<100> > >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<std::bitset<100> > >::value );
  
  BOOST_CHECK( Utility::IsHashable<std::type_index>::value );
  BOOST_CHECK( Utility::IsHashable<std::type_index*>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<std::type_index> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<std::type_index> >::value );
  
  BOOST_CHECK( Utility::IsHashable<std::vector<bool> >::value );
  BOOST_CHECK( Utility::IsHashable<std::vector<bool>*>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<std::vector<bool> > >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<std::vector<bool> > >::value );

  BOOST_CHECK( !Utility::IsHashable<std::vector<int> >::value );
  BOOST_CHECK( Utility::IsHashable<std::vector<int>*>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<std::vector<int> > >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<std::vector<int> > >::value );

  BOOST_CHECK( !Utility::IsHashable<std::vector<double> >::value );
  BOOST_CHECK( Utility::IsHashable<std::vector<double>*>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<std::vector<double> > >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<std::vector<double> > >::value );
  
  BOOST_CHECK( Utility::IsHashable<std::thread::id>::value );
  BOOST_CHECK( Utility::IsHashable<std::thread::id*>::value );
  BOOST_CHECK( Utility::IsHashable<std::unique_ptr<std::thread::id> >::value );
  BOOST_CHECK( Utility::IsHashable<std::shared_ptr<std::thread::id > >::value );
  
  BOOST_CHECK( !(Utility::IsHashable<std::pair<int,double> >::value) );
  BOOST_CHECK( (Utility::IsHashable<std::pair<int,double>*>::value) );
  BOOST_CHECK( (Utility::IsHashable<std::unique_ptr<std::pair<int,double> > >::value) );
  BOOST_CHECK( (Utility::IsHashable<std::shared_ptr<std::pair<int,double> > >::value) );
  
  BOOST_CHECK( !(Utility::IsHashable<std::tuple<int,double,float> >::value) );
  BOOST_CHECK( (Utility::IsHashable<std::tuple<int,double,float>*>::value) );
  BOOST_CHECK( (Utility::IsHashable<std::unique_ptr<std::tuple<int,double,float> > >::value) );
  BOOST_CHECK( (Utility::IsHashable<std::shared_ptr<std::tuple<int,double,float> > >::value) );
}

//---------------------------------------------------------------------------//
// Check if a type is hashable
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
// end tstTypeTraits.cpp
//---------------------------------------------------------------------------//