//---------------------------------------------------------------------------//
//!
//! \file   tstTypeNameTraits.cpp
//! \author Alex Robinson
//! \brief  TypeNameTraits unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <utility>
#include <tuple>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>
#include <boost/units/systems/cgs/energy.hpp>
#include <boost/units/systems/si/energy.hpp>

// FRENSIE Includes
#include "Utility_TypeNameTraits.hpp"
#include "Utility_ElectronVoltUnit.hpp"

using namespace Utility::Units;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

//---------------------------------------------------------------------------//
// Template Test Types
//---------------------------------------------------------------------------//
typedef boost::mpl::list<std::tuple<si::energy,double>,
                         std::tuple<cgs::energy,double>,
                         std::tuple<ElectronVolt,double>,
                         std::tuple<KiloElectronVolt,double>,
                         std::tuple<MegaElectronVolt,double>,
                         std::tuple<si::energy,float>,
                         std::tuple<cgs::energy,float>,
                         std::tuple<ElectronVolt,float>,
                         std::tuple<KiloElectronVolt,float>,
                         std::tuple<MegaElectronVolt,float> > QuantityTypes;

typedef boost::mpl::list<float,double,char,short,unsigned short,int,unsigned int,long int,unsigned long int,long long int,unsigned long long int,std::complex<float>,std::complex<double>, boost::units::quantity<si::energy,double>,boost::units::quantity<ElectronVolt,float>,std::string> TestTypes;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the type name for char can be returned
BOOST_AUTO_TEST_CASE( name_char )
{
  BOOST_CHECK_EQUAL( Utility::TypeNameTraits<char>::name(), "char" );
  BOOST_CHECK_EQUAL( Utility::typeName<char>(), "char" );
}

//---------------------------------------------------------------------------//
// Check that the type name for short can be returned
BOOST_AUTO_TEST_CASE( name_short )
{
  BOOST_CHECK_EQUAL( Utility::TypeNameTraits<short>::name(), "short" );
  BOOST_CHECK_EQUAL( Utility::typeName<short>(), "short" );
}

//---------------------------------------------------------------------------//
// Check that the type name for unsigned short can be returned
BOOST_AUTO_TEST_CASE( name_unsigned_short )
{
  BOOST_CHECK_EQUAL( Utility::TypeNameTraits<unsigned short>::name(), "unsigned short" );
  BOOST_CHECK_EQUAL( Utility::typeName<unsigned short>(), "unsigned short" );
}

//---------------------------------------------------------------------------//
// Check that the type name for int can be returned
BOOST_AUTO_TEST_CASE( name_int )
{
  BOOST_CHECK_EQUAL( Utility::TypeNameTraits<int>::name(), "int" );
  BOOST_CHECK_EQUAL( Utility::typeName<int>(), "int" );
}

//---------------------------------------------------------------------------//
// Check that the type name for unsigned int can be returned
BOOST_AUTO_TEST_CASE( name_unsigned_int )
{
  BOOST_CHECK_EQUAL( Utility::TypeNameTraits<unsigned int>::name(), "unsigned int" );
  BOOST_CHECK_EQUAL( Utility::typeName<unsigned int>(), "unsigned int" );
}

//---------------------------------------------------------------------------//
// Check that the type name for long int can be returned
BOOST_AUTO_TEST_CASE( name_long_int )
{
  BOOST_CHECK_EQUAL( Utility::TypeNameTraits<long int>::name(), "long int" );
  BOOST_CHECK_EQUAL( Utility::typeName<long int>(), "long int" );
}

//---------------------------------------------------------------------------//
// Check that the type name for unsigned long int can be returned
BOOST_AUTO_TEST_CASE( name_unsigned_long_int )
{
  BOOST_CHECK_EQUAL( Utility::TypeNameTraits<unsigned long int>::name(), "unsigned long int" );
  BOOST_CHECK_EQUAL( Utility::typeName<unsigned long int>(), "unsigned long int" );
}

//---------------------------------------------------------------------------//
// Check that the type name for long long int can be returned
BOOST_AUTO_TEST_CASE( name_long_long_int )
{
  BOOST_CHECK_EQUAL( Utility::TypeNameTraits<long long int>::name(), "long long int" );
  BOOST_CHECK_EQUAL( Utility::typeName<long long int>(), "long long int" );
}

//---------------------------------------------------------------------------//
// Check that the type name for unsigned long long int can be returned
BOOST_AUTO_TEST_CASE( name_unsigned_long_long_int )
{
  BOOST_CHECK_EQUAL( Utility::TypeNameTraits<unsigned long long int>::name(), "unsigned long long int" );
  BOOST_CHECK_EQUAL( Utility::typeName<unsigned long long int>(), "unsigned long long int" );
}
//---------------------------------------------------------------------------// // Check that the type name for float can be returned
BOOST_AUTO_TEST_CASE( name_float )
{
  BOOST_CHECK_EQUAL( Utility::TypeNameTraits<float>::name(), "float" );
  BOOST_CHECK_EQUAL( Utility::typeName<float>(), "float" );
}

//---------------------------------------------------------------------------// // Check that the type name for double can be returned
BOOST_AUTO_TEST_CASE( name_double )
{
  BOOST_CHECK_EQUAL( Utility::TypeNameTraits<double>::name(), "double" );
  BOOST_CHECK_EQUAL( Utility::typeName<double>(), "double" );
}

//---------------------------------------------------------------------------//
// Check that the type name for std::complex<float> can be returned
BOOST_AUTO_TEST_CASE( name_complex_float )
{
  BOOST_CHECK_EQUAL( Utility::TypeNameTraits<std::complex<float> >::name(), "std::complex<float>" );
  BOOST_CHECK_EQUAL( Utility::typeName<std::complex<float> >(), "std::complex<float>" );
}

//---------------------------------------------------------------------------//
// Check that the type name for std::complex<double> can be returned
BOOST_AUTO_TEST_CASE( name_complex_double )
{
  BOOST_CHECK_EQUAL( Utility::TypeNameTraits<std::complex<double> >::name(), "std::complex<double>" );
  BOOST_CHECK_EQUAL( Utility::typeName<std::complex<double> >(), "std::complex<double>" );
}

//---------------------------------------------------------------------------//
// Check that the type name for std::string can be returned
BOOST_AUTO_TEST_CASE( name_string )
{
  BOOST_CHECK_EQUAL( Utility::TypeNameTraits<std::string>::name(), "std::string" );
  BOOST_CHECK_EQUAL( Utility::typeName<std::string>(), "std::string" );
}

//---------------------------------------------------------------------------//
// Check that the type name for integral constants can be returned
BOOST_AUTO_TEST_CASE( name_integral_constants )
{
  BOOST_CHECK_EQUAL( Utility::TypeNameTraits<std::true_type>::name(), "true" );
  BOOST_CHECK_EQUAL( Utility::typeName<std::true_type>(), "true" );

  BOOST_CHECK_EQUAL( Utility::TypeNameTraits<std::false_type>::name(), "false" );
  BOOST_CHECK_EQUAL( Utility::typeName<std::false_type>(), "false" );

  BOOST_CHECK_EQUAL( (Utility::TypeNameTraits<std::integral_constant<size_t,0> >::name()), "0" );
  BOOST_CHECK_EQUAL( (Utility::TypeNameTraits<std::integral_constant<size_t,1> >::name()), "1" );
  BOOST_CHECK_EQUAL( (Utility::TypeNameTraits<std::integral_constant<size_t,2> >::name()), "2" );

  BOOST_CHECK_EQUAL( (Utility::typeName<std::integral_constant<size_t,0> >()), "0" );
  BOOST_CHECK_EQUAL( (Utility::typeName<std::integral_constant<size_t,1> >()), "1" );
  BOOST_CHECK_EQUAL( (Utility::typeName<std::integral_constant<size_t,2> >()), "2" );

  BOOST_CHECK_EQUAL( (Utility::TypeNameTraits<std::integral_constant<int,-1> >::name()), "-1" );
  BOOST_CHECK_EQUAL( (Utility::TypeNameTraits<std::integral_constant<int,0> >::name()), "0" );
  BOOST_CHECK_EQUAL( (Utility::TypeNameTraits<std::integral_constant<int,1> >::name()), "1" );

  BOOST_CHECK_EQUAL( (Utility::typeName<std::integral_constant<int,-1> >()), "-1" );
  BOOST_CHECK_EQUAL( (Utility::typeName<std::integral_constant<int,0> >()), "0" );
  BOOST_CHECK_EQUAL( (Utility::typeName<std::integral_constant<int,1> >()), "1" );
}

//---------------------------------------------------------------------------//
// Check that the type name for boost::units::quantity types can be returned
BOOST_AUTO_TEST_CASE_TEMPLATE( name_quantity, UnitRawTypePair, QuantityTypes )
{
  typedef typename std::tuple_element<0,UnitRawTypePair>::type Unit;
  typedef typename std::tuple_element<1,UnitRawTypePair>::type T;
  
  std::string name = "boost::units::quantity<" +
    Utility::UnitTraits<Unit>::symbol() + "," +
    Utility::TypeNameTraits<T>::name() + ">";
  
  BOOST_CHECK_EQUAL( (Utility::TypeNameTraits<boost::units::quantity<Unit,T> >::name()), name );
  BOOST_CHECK_EQUAL( (Utility::typeName<boost::units::quantity<Unit,T> >()), name );
}

//---------------------------------------------------------------------------//
// Check that the type name for special cases can be returned
BOOST_AUTO_TEST_CASE_TEMPLATE( name_special_cases, T, TestTypes )
{
  // Const case
  BOOST_CHECK( Utility::TypeNameTraits<const T>::IsSpecialized::value );
  BOOST_CHECK_EQUAL( Utility::TypeNameTraits<const T>::name(),
                     std::string("const ")+Utility::TypeNameTraits<T>::name() );
  BOOST_CHECK_EQUAL( Utility::typeName<const T>(),
                     std::string("const ")+Utility::TypeNameTraits<T>::name() );

  // Volatile case
  BOOST_CHECK( Utility::TypeNameTraits<volatile T>::IsSpecialized::value );
  BOOST_CHECK_EQUAL( Utility::TypeNameTraits<volatile T>::name(),
                     std::string("volatile ")+Utility::TypeNameTraits<T>::name() );
  BOOST_CHECK_EQUAL( Utility::typeName<volatile T>(),
                     std::string("volatile ")+Utility::TypeNameTraits<T>::name() );

  // Const volatile case
  BOOST_CHECK( Utility::TypeNameTraits<const volatile T>::IsSpecialized::value );
  BOOST_CHECK_EQUAL( Utility::TypeNameTraits<const volatile T>::name(),
                     std::string("const volatile ")+Utility::TypeNameTraits<T>::name() );
  BOOST_CHECK_EQUAL( Utility::typeName<const volatile T>(),
                     std::string("const volatile ")+Utility::TypeNameTraits<T>::name() );

  // Pointer case
  BOOST_CHECK( Utility::TypeNameTraits<T*>::IsSpecialized::value );
  BOOST_CHECK_EQUAL( Utility::TypeNameTraits<T*>::name(),
                     Utility::TypeNameTraits<T>::name()+"*" );
  BOOST_CHECK_EQUAL( Utility::typeName<T*>(),
                     Utility::TypeNameTraits<T>::name()+"*" );

  // Const pointer case
  BOOST_CHECK( Utility::TypeNameTraits<T* const>::IsSpecialized::value );
  BOOST_CHECK_EQUAL( Utility::TypeNameTraits<T* const>::name(),
                     Utility::TypeNameTraits<T>::name()+"* const" );
  BOOST_CHECK_EQUAL( Utility::typeName<T* const>(),
                     Utility::TypeNameTraits<T>::name()+"* const" );

  // Pointer-to-const case
  BOOST_CHECK( Utility::TypeNameTraits<const T*>::IsSpecialized::value );
  BOOST_CHECK_EQUAL( Utility::TypeNameTraits<const T*>::name(),
                     std::string("const ")+Utility::TypeNameTraits<T>::name()+"*" );
  BOOST_CHECK_EQUAL( Utility::typeName<const T*>(),
                     std::string("const ")+Utility::TypeNameTraits<T>::name()+"*" );

  // Const pointer-to-const case
  BOOST_CHECK( Utility::TypeNameTraits<const T* const>::IsSpecialized::value );
  BOOST_CHECK_EQUAL( Utility::TypeNameTraits<const T* const>::name(),
                     std::string("const ")+Utility::TypeNameTraits<T>::name()+"* const" );
  BOOST_CHECK_EQUAL( Utility::typeName<const T* const>(),
                     std::string("const ")+Utility::TypeNameTraits<T>::name()+"* const" );

  // Reference case
  BOOST_CHECK( Utility::TypeNameTraits<T&>::IsSpecialized::value );
  BOOST_CHECK_EQUAL( Utility::TypeNameTraits<T&>::name(),
                     Utility::TypeNameTraits<T>::name()+"&" );
  BOOST_CHECK_EQUAL( Utility::typeName<T&>(),
                     Utility::TypeNameTraits<T>::name()+"&" );

  // Const reference case
  BOOST_CHECK( Utility::TypeNameTraits<const T&>::IsSpecialized::value );
  BOOST_CHECK_EQUAL( Utility::TypeNameTraits<const T&>::name(),
                     std::string("const ")+Utility::TypeNameTraits<T>::name()+"&" );
  BOOST_CHECK_EQUAL( Utility::typeName<const T&>(),
                     std::string("const ")+Utility::TypeNameTraits<T>::name()+"&" );
}

//---------------------------------------------------------------------------//
// end tstTypeNameTraits.cpp
//---------------------------------------------------------------------------//
