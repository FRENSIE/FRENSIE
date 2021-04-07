//---------------------------------------------------------------------------//
//!
//! \file   tstFromStringTraits.cpp
//! \author Alex Robinson
//! \brief  FromStringTraits unit tests
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
#include <boost/units/systems/cgs/energy.hpp>
#include <boost/units/systems/si/energy.hpp>

// FRENSIE Includes
#include "Utility_FromStringTraits.hpp"
#include "Utility_ElectronVoltUnit.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_UnitTraits.hpp"

using namespace Utility::Units;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

//---------------------------------------------------------------------------//
// Template Test Types
//---------------------------------------------------------------------------//
typedef boost::mpl::list<char, signed char, unsigned char> SingleByteTypes;

typedef boost::mpl::list<short, int, long, long long> MultipleByteTypes;

typedef boost::mpl::list<int, unsigned int, long, unsigned long, long long, unsigned long long, float, double> ComplexTestTypes;

template<typename Unit, typename RawTypeWrapper = void>
struct QuantityTypeList
{
  typedef boost::mpl::list<boost::units::quantity<Unit,float>, boost::units::quantity<Unit,double> > BasicFloatingPointQuantityTypes;
  
  typedef boost::mpl::list<boost::units::quantity<Unit,int>, boost::units::quantity<Unit,float>, boost::units::quantity<Unit,double> > BasicQuantityTypes;

  typedef boost::mpl::list<boost::units::quantity<Unit,std::complex<int> >, boost::units::quantity<Unit,std::complex<float> >, boost::units::quantity<Unit,std::complex<double> > > ComplexQuantityTypes;

  typedef typename boost::mpl::insert_range<BasicQuantityTypes, typename boost::mpl::end<BasicQuantityTypes>::type,ComplexQuantityTypes>::type type;
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

typedef typename MergeTypeLists<typename QuantityTypeList<cgs::energy>::BasicFloatingPointQuantityTypes, typename QuantityTypeList<si::energy>::BasicFloatingPointQuantityTypes, typename QuantityTypeList<ElectronVolt>::BasicFloatingPointQuantityTypes, typename QuantityTypeList<KiloElectronVolt>::BasicFloatingPointQuantityTypes>::type TestBasicFloatingPointQuantityTypes;

typedef typename MergeTypeLists<typename QuantityTypeList<cgs::energy>::BasicQuantityTypes, typename QuantityTypeList<si::energy>::BasicQuantityTypes, typename QuantityTypeList<ElectronVolt>::BasicQuantityTypes, typename QuantityTypeList<KiloElectronVolt>::BasicQuantityTypes>::type TestBasicQuantityTypes;

typedef typename MergeTypeLists<typename QuantityTypeList<cgs::energy>::ComplexQuantityTypes, typename QuantityTypeList<si::energy>::ComplexQuantityTypes, typename QuantityTypeList<ElectronVolt>::ComplexQuantityTypes, typename QuantityTypeList<KiloElectronVolt>::ComplexQuantityTypes>::type TestComplexQuantityTypes;

typedef typename MergeTypeLists<typename QuantityTypeList<cgs::energy>::type, typename QuantityTypeList<si::energy>::type, typename QuantityTypeList<ElectronVolt>::type, typename QuantityTypeList<KiloElectronVolt>::type>::type TestQuantityTypes;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a string can be created from a string
BOOST_AUTO_TEST_CASE( string_fromString )
{
  BOOST_CHECK_EQUAL( Utility::fromString<std::string>( " " ), " " );
  BOOST_CHECK_EQUAL( Utility::fromString<std::string>( "testing" ), "testing" );
  BOOST_CHECK_EQUAL( Utility::fromString<std::string>( "{{1,0},{-1,2}}" ), "{{1,0},{-1,2}}" );
  BOOST_CHECK_EQUAL( Utility::fromString<std::string>( "{ {1,0}, {-1,2} }" ), "{ {1,0}, {-1,2} }" );
}

//---------------------------------------------------------------------------//
// Check that a string can be extracted from a stream
BOOST_AUTO_TEST_CASE( string_fromStream )
{
  std::istringstream iss;
  iss.str( " " );

  std::string string;
  
  Utility::fromStream( iss, string );

  BOOST_CHECK_EQUAL( string, " " );

  iss.str( "testing" );
  iss.clear();

  Utility::fromStream( iss, string );

  BOOST_CHECK_EQUAL( string, "testing" );

  string.clear();

  // Multiple booleans in the same stream with default deliminators
  iss.str( "testing-1\ntesting-2\ntesting-3\ntesting-4" );
  iss.clear();

  Utility::fromStream( iss, string );

  BOOST_CHECK_EQUAL( string, "testing-1" );

  Utility::fromStream( iss, string );

  BOOST_CHECK_EQUAL( string, "testing-2" );

  Utility::fromStream( iss, string );

  BOOST_CHECK_EQUAL( string, "testing-3" );

  Utility::fromStream( iss, string );

  BOOST_CHECK_EQUAL( string, "testing-4" );

  string.clear();
  
  // Multiple booleans in the same stream with white space deliminators
  iss.str( "testing-1 testing-2\ttesting-3\ntesting-4" );
  iss.clear();

  Utility::fromStream( iss, string, Utility::Details::white_space_delims );

  BOOST_CHECK_EQUAL( string, "testing-1" );

  Utility::fromStream( iss, string, Utility::Details::white_space_delims );

  BOOST_CHECK_EQUAL( string, "testing-2" );

  Utility::fromStream( iss, string, Utility::Details::white_space_delims );

  BOOST_CHECK_EQUAL( string, "testing-3" );

  Utility::fromStream( iss, string, Utility::Details::white_space_delims );

  BOOST_CHECK_EQUAL( string, "testing-4" );

  string.clear();
  
  // Multiple booleans in the same stream with custom deliminators
  iss.str( "testing-1,testing-2" );
  iss.clear();

  Utility::fromStream( iss, string, "," );

  BOOST_CHECK_EQUAL( string, "testing-1" );

  string.clear();

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, string );

  BOOST_CHECK_EQUAL( string, "testing-2" );

  // Multiple string elements in the same stream with container deliminators
  iss.str( "{1,0},{-1,2}, {a,b} , {key, {a,b}} }" );
  iss.clear();

  Utility::fromStream( iss, string, ",}" );

  BOOST_CHECK_EQUAL( string, "{1,0}" );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, string, ",}" );

  BOOST_CHECK_EQUAL( string, "{-1,2}" );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, string, ",}" );

  BOOST_CHECK_EQUAL( string, " {a,b}" );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, string, ",}" );

  BOOST_CHECK_EQUAL( string, " {key, {a,b}}" );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );
}

//---------------------------------------------------------------------------//
// Check that a LogRecordType can be created from a string
BOOST_AUTO_TEST_CASE( LogRecordType_fromString )
{
  Utility::LogRecordType record_type;
  
  BOOST_CHECK_EQUAL( Utility::fromString<Utility::LogRecordType>( "Error" ),
                     Utility::ERROR_RECORD );
  BOOST_CHECK_EQUAL( Utility::fromString<Utility::LogRecordType>( " Error " ),
                     Utility::ERROR_RECORD );
  BOOST_CHECK_THROW( Utility::fromString<Utility::LogRecordType>( "error" ),
                     Utility::StringConversionException );

  BOOST_CHECK_EQUAL( Utility::fromString<Utility::LogRecordType>( "Warning" ),
                     Utility::WARNING_RECORD );
  BOOST_CHECK_EQUAL( Utility::fromString<Utility::LogRecordType>( " Warning " ),
                     Utility::WARNING_RECORD );
  BOOST_CHECK_THROW( Utility::fromString<Utility::LogRecordType>( "warning" ),
                     Utility::StringConversionException );

  BOOST_CHECK_EQUAL( Utility::fromString<Utility::LogRecordType>( "Notification" ),
                     Utility::NOTIFICATION_RECORD );
  BOOST_CHECK_EQUAL( Utility::fromString<Utility::LogRecordType>( " Notification " ),
                     Utility::NOTIFICATION_RECORD );
  BOOST_CHECK_THROW( Utility::fromString<Utility::LogRecordType>( "notification" ),
                     Utility::StringConversionException );

  BOOST_CHECK_EQUAL( Utility::fromString<Utility::LogRecordType>( "Details" ),
                     Utility::DETAILS_RECORD );
  BOOST_CHECK_EQUAL( Utility::fromString<Utility::LogRecordType>( " Details " ),
                     Utility::DETAILS_RECORD );
  BOOST_CHECK_THROW( Utility::fromString<Utility::LogRecordType>( "details" ),
                     Utility::StringConversionException );

  BOOST_CHECK_EQUAL( Utility::fromString<Utility::LogRecordType>( "Pedantic Details" ),
                     Utility::PEDANTIC_DETAILS_RECORD );

  BOOST_CHECK_EQUAL( Utility::fromString<Utility::LogRecordType>( " Pedantic Details " ),
                     Utility::PEDANTIC_DETAILS_RECORD );

  BOOST_CHECK_THROW( Utility::fromString<Utility::LogRecordType>( "pedantic Details" ),
                     Utility::StringConversionException );
  BOOST_CHECK_THROW( Utility::fromString<Utility::LogRecordType>( "Pedantic details" ),
                     Utility::StringConversionException );
  BOOST_CHECK_THROW( Utility::fromString<Utility::LogRecordType>( "pedantic details" ),
                     Utility::StringConversionException );
}

//---------------------------------------------------------------------------//
// Check that a LogRecordType can be extracted from a stream
BOOST_AUTO_TEST_CASE( LogRecordType_fromStream )
{
  Utility::LogRecordType record_type;
  std::istringstream iss( "Error" );
  
  Utility::fromStream( iss, record_type );

  BOOST_CHECK_EQUAL( record_type, Utility::ERROR_RECORD );

  iss.str( " Error " );
  iss.clear();

  Utility::fromStream( iss, record_type );

  BOOST_CHECK_EQUAL( record_type, Utility::ERROR_RECORD );

  iss.str( "error" );
  iss.clear();

  BOOST_CHECK_THROW( Utility::fromStream( iss, record_type ), std::runtime_error );

  iss.str( "Warning" );
  iss.clear();

  Utility::fromStream( iss, record_type );

  BOOST_CHECK_EQUAL( record_type, Utility::WARNING_RECORD );

  iss.str( " Warning " );
  iss.clear();

  Utility::fromStream( iss, record_type );

  BOOST_CHECK_EQUAL( record_type, Utility::WARNING_RECORD );

  iss.str( "warning" );
  iss.clear();

  BOOST_CHECK_THROW( Utility::fromStream( iss, record_type ), std::runtime_error );

  iss.str( "Notification" );
  iss.clear();

  Utility::fromStream( iss, record_type );

  BOOST_CHECK_EQUAL( record_type, Utility::NOTIFICATION_RECORD );

  iss.str( " Notification " );
  iss.clear();

  Utility::fromStream( iss, record_type );

  BOOST_CHECK_EQUAL( record_type, Utility::NOTIFICATION_RECORD );

  iss.str( "notification" );
  iss.clear();

  BOOST_CHECK_THROW( Utility::fromStream( iss, record_type ), std::runtime_error );

  iss.str( "Details" );
  iss.clear();

  Utility::fromStream( iss, record_type );

  BOOST_CHECK_EQUAL( record_type, Utility::DETAILS_RECORD );

  iss.str( " Details " );
  iss.clear();

  Utility::fromStream( iss, record_type );

  BOOST_CHECK_EQUAL( record_type, Utility::DETAILS_RECORD );

  iss.str( "details" );
  iss.clear();

  BOOST_CHECK_THROW( Utility::fromStream( iss, record_type ), std::runtime_error );

  iss.str( "Pedantic Details" );
  iss.clear();

  Utility::fromStream( iss, record_type );

  BOOST_CHECK_EQUAL( record_type, Utility::PEDANTIC_DETAILS_RECORD );

  iss.str( " Pedantic  Details " );
  iss.clear();

  Utility::fromStream( iss, record_type );

  BOOST_CHECK_EQUAL( record_type, Utility::PEDANTIC_DETAILS_RECORD );

  iss.str( "pedantic Details" );
  iss.clear();

  BOOST_CHECK_THROW( Utility::fromStream( iss, record_type ), std::runtime_error );

  iss.str( "Pedantic details" );
  iss.clear();

  BOOST_CHECK_THROW( Utility::fromStream( iss, record_type ), std::runtime_error );

  iss.str( "pedantic details" );
  iss.clear();

  BOOST_CHECK_THROW( Utility::fromStream( iss, record_type ), std::runtime_error );
}

//---------------------------------------------------------------------------//
// Check that a boolean can be created from a string
BOOST_AUTO_TEST_CASE( bool_fromString )
{
  BOOST_CHECK_EQUAL( Utility::fromString<bool>( "0" ), false );
  BOOST_CHECK_EQUAL( Utility::fromString<bool>( "false" ), false );
  BOOST_CHECK_EQUAL( Utility::fromString<bool>( "False" ), false );
  BOOST_CHECK_EQUAL( Utility::fromString<bool>( "FaLsE" ), false );
  BOOST_CHECK_EQUAL( Utility::fromString<bool>( "FALSE" ), false );

  BOOST_CHECK_EQUAL( Utility::fromString<bool>( "1" ), true );
  BOOST_CHECK_EQUAL( Utility::fromString<bool>( "true" ), true );
  BOOST_CHECK_EQUAL( Utility::fromString<bool>( "True" ), true );
  BOOST_CHECK_EQUAL( Utility::fromString<bool>( "TrUe" ), true );
  BOOST_CHECK_EQUAL( Utility::fromString<bool>( "TRUE" ), true );

  BOOST_CHECK_THROW( Utility::fromString<bool>( "0 1" ),
                     Utility::StringConversionException );
  BOOST_CHECK_THROW( Utility::fromString<bool>( "1 false" ),
                     Utility::StringConversionException );
  BOOST_CHECK_THROW( Utility::fromString<bool>( "2" ),
                     Utility::StringConversionException );
  BOOST_CHECK_THROW( Utility::fromString<bool>( "abc" ),
                     Utility::StringConversionException );
}

//---------------------------------------------------------------------------//
// Check that a boolean can be extracted from a stream
BOOST_AUTO_TEST_CASE( bool_fromStream )
{
  std::istringstream iss( "0" );

  bool boolean;

  Utility::fromStream( iss, boolean );

  BOOST_CHECK_EQUAL( boolean, false );

  iss.str( "false" );
  iss.clear();

  Utility::fromStream( iss, boolean );

  BOOST_CHECK_EQUAL( boolean, false );

  iss.str( "1" );
  iss.clear();

  Utility::fromStream( iss, boolean );

  BOOST_CHECK_EQUAL( boolean, true );

  iss.str( "true" );
  iss.clear();

  Utility::fromStream( iss, boolean );

  BOOST_CHECK_EQUAL( boolean, true );

  // Multiple booleans in the same stream with default deliminators
  iss.str( "0 1  true   false  " );
  iss.clear();

  Utility::fromStream( iss, boolean );

  BOOST_CHECK_EQUAL( boolean, false );

  Utility::fromStream( iss, boolean );

  BOOST_CHECK_EQUAL( boolean, true );

  Utility::fromStream( iss, boolean );

  BOOST_CHECK_EQUAL( boolean, true );

  Utility::fromStream( iss, boolean );

  BOOST_CHECK_EQUAL( boolean, false );
  
  // Multiple booleans in the same stream with custom deliminators
  iss.str( "0, true" );
  iss.clear();

  Utility::fromStream( iss, boolean, "," );

  BOOST_CHECK_EQUAL( boolean, false );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, boolean );

  BOOST_CHECK_EQUAL( boolean, true );
}

//---------------------------------------------------------------------------//
// Check that single byte integer types can be created from a string
BOOST_AUTO_TEST_CASE_TEMPLATE( byte_fromString, T, SingleByteTypes )
{
  BOOST_CHECK_EQUAL( Utility::fromString<T>( " " ), (T)32 );
  
  std::string test_string;
  test_string.push_back( '\t' );
  
  BOOST_CHECK_EQUAL( Utility::fromString<T>( test_string ), (T)9 );

  test_string.clear();
  test_string.push_back( '\n' );
  
  BOOST_CHECK_EQUAL( Utility::fromString<T>( test_string ), (T)10 );

  test_string = "-128";

  if( std::is_signed<T>::value )
  {
    BOOST_CHECK_EQUAL( Utility::fromString<T>( test_string ), (T)-128 );
  }
  else
  {
    BOOST_CHECK_THROW( Utility::fromString<T>( test_string ),
                       Utility::StringConversionException );
  }

  test_string = "127";

  BOOST_CHECK_EQUAL( Utility::fromString<T>( test_string ), (T)127 );

  test_string = "255";

  if( std::is_signed<T>::value )
  {
    BOOST_CHECK_THROW( Utility::fromString<T>( test_string ),
                       Utility::StringConversionException );
  }
  else
  {
    BOOST_CHECK_EQUAL( Utility::fromString<T>( test_string ), (T)255 );
  }

  test_string.clear();
  
  BOOST_CHECK_THROW( Utility::fromString<T>( "256" ),
                     Utility::StringConversionException );
  BOOST_CHECK_THROW( Utility::fromString<T>( "0.0" ),
                     Utility::StringConversionException );
  BOOST_CHECK_THROW( Utility::fromString<T>( "0.000000000e+00" ),
                     Utility::StringConversionException );
  BOOST_CHECK_THROW( Utility::fromString<T>( "0 0" ),
                     Utility::StringConversionException );
  BOOST_CHECK_THROW( Utility::fromString<T>( "ab" ),
                     Utility::StringConversionException );
  BOOST_CHECK_THROW( Utility::fromString<T>( "a b" ),
                     Utility::StringConversionException );
}

//---------------------------------------------------------------------------//
// Check that single byte integer types can be created from a stream
BOOST_AUTO_TEST_CASE_TEMPLATE( byte_fromStream, T, SingleByteTypes )
{
  std::istringstream iss( " " );

  T test_byte;

  Utility::fromStream( iss, test_byte );
  
  BOOST_CHECK_EQUAL( test_byte, (T)32 );

  {
    std::string test_string;
    test_string.push_back( '\t' );

    iss.str( test_string );
    iss.clear();
  }

  Utility::fromStream( iss, test_byte );
  
  BOOST_CHECK_EQUAL( test_byte, (T)9 );

  {
    std::string test_string;
    test_string.push_back( '\n' );

    iss.str( test_string );
    iss.clear();
  }

  Utility::fromStream( iss, test_byte );
  
  BOOST_CHECK_EQUAL( test_byte, (T)10 );

  // Multiple bytes in the same stream with no deliminators
  iss.str( "-128" );
  iss.clear();

  Utility::fromStream( iss, test_byte );

  BOOST_CHECK_EQUAL( test_byte, (T)'-' );

  Utility::fromStream( iss, test_byte );

  BOOST_CHECK_EQUAL( test_byte, (T)'1' );

  Utility::fromStream( iss, test_byte );

  BOOST_CHECK_EQUAL( test_byte, (T)'2' );

  Utility::fromStream( iss, test_byte );

  BOOST_CHECK_EQUAL( test_byte, (T)'8' );

  // Multiple bytes in the same stream with white space deliminators
  iss.str( "127" );
  iss.clear();

  Utility::fromStream( iss, test_byte, Utility::Details::white_space_delims );

  BOOST_CHECK_EQUAL( test_byte, (T)127 );

  iss.str( "a 0\n127\t-" );
  iss.clear();

  Utility::fromStream( iss, test_byte, Utility::Details::white_space_delims );

  BOOST_CHECK_EQUAL( test_byte, (T)'a' );

  Utility::fromStream( iss, test_byte, Utility::Details::white_space_delims );

  BOOST_CHECK_EQUAL( test_byte, (T)'0' );

  Utility::fromStream( iss, test_byte, Utility::Details::white_space_delims );

  BOOST_CHECK_EQUAL( test_byte, (T)127 );

  Utility::fromStream( iss, test_byte, Utility::Details::white_space_delims );

  BOOST_CHECK_EQUAL( test_byte, (T)'-' );

  // Multiple bytes in the same stream with custom deliminators
  iss.str( "a, b, c, d, 127, , -}" );
  iss.clear();

  Utility::fromStream( iss, test_byte, "," );

  BOOST_CHECK_EQUAL( test_byte, (T)'a' );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, test_byte, "," );

  BOOST_CHECK_EQUAL( test_byte, (T)'b' );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, test_byte, "," );

  BOOST_CHECK_EQUAL( test_byte, (T)'c' );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, test_byte, "," );

  BOOST_CHECK_EQUAL( test_byte, (T)'d' );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, test_byte, "," );

  BOOST_CHECK_EQUAL( test_byte, (T)127 );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, test_byte, "," );

  BOOST_CHECK_EQUAL( test_byte, (T)' ' );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, test_byte, "}" );

  BOOST_CHECK_EQUAL( test_byte, (T)'-' );
}

//---------------------------------------------------------------------------//
// Check that signed integer types can be created from a string
BOOST_AUTO_TEST_CASE_TEMPLATE( fromString, T, MultipleByteTypes )
{
  BOOST_CHECK_EQUAL( Utility::fromString<T>( "-10" ), -10 );
  BOOST_CHECK_EQUAL( Utility::fromString<T>( "0" ), 0 );
  BOOST_CHECK_EQUAL( Utility::fromString<T>( " 10 " ), 10 );

  BOOST_CHECK_THROW( Utility::fromString<T>( "0.0" ),
                     Utility::StringConversionException );
  BOOST_CHECK_THROW( Utility::fromString<T>( "0.000000000e+00" ),
                     Utility::StringConversionException );
  BOOST_CHECK_THROW( Utility::fromString<T>( "0 0" ),
                     Utility::StringConversionException );
  BOOST_CHECK_THROW( Utility::fromString<T>( "abc" ),
                     Utility::StringConversionException );
  // Overflow should result in an error: #(2^63) > 2^63 - 1
  BOOST_CHECK_THROW( Utility::fromString<T>( "9223372036854775808" ),
                     Utility::StringConversionException );
}

//---------------------------------------------------------------------------//
// Check that signed integer types can be extracted from a stream
BOOST_AUTO_TEST_CASE_TEMPLATE( fromStream, T, MultipleByteTypes )
{
  std::istringstream iss( "-10" );

  T test_int;

  Utility::fromStream( iss, test_int );

  BOOST_CHECK_EQUAL( test_int, -10 );

  iss.str( "0" );
  iss.clear();

  Utility::fromStream( iss, test_int );

  BOOST_CHECK_EQUAL( test_int, 0 );

  iss.str( " 10 " );
  iss.clear();

  Utility::fromStream( iss, test_int );

  BOOST_CHECK_EQUAL( test_int, 10 );

  // Multiple integers in the same stream with default deliminators
  iss.str( "-10 0   10 " );
  iss.clear();

  Utility::fromStream( iss, test_int );

  BOOST_CHECK_EQUAL( test_int, -10 );

  Utility::fromStream( iss, test_int );

  BOOST_CHECK_EQUAL( test_int, 0 );

  Utility::fromStream( iss, test_int );

  BOOST_CHECK_EQUAL( test_int, 10 );
  
  // Multiple integers in the same stream with custom deliminators
  iss.str( "-10, 1" );
  iss.clear();
  
  Utility::fromStream( iss, test_int, "," );

  BOOST_CHECK_EQUAL( test_int, -10 );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, test_int );

  BOOST_CHECK_EQUAL( test_int, 1 );
}

//---------------------------------------------------------------------------//
// Check that unsigned integer types can be created from a string
BOOST_AUTO_TEST_CASE_TEMPLATE( unsigned_fromString, T, MultipleByteTypes )
{
  typedef typename std::make_unsigned<T>::type UnsignedT;
  
  BOOST_CHECK_EQUAL( Utility::fromString<UnsignedT>( "0" ), 0 );
  BOOST_CHECK_EQUAL( Utility::fromString<UnsignedT>( "10" ), 10 );
  BOOST_CHECK_EQUAL( Utility::fromString<UnsignedT>( "255" ), 255 );

  BOOST_CHECK_THROW( Utility::fromString<UnsignedT>( "-10" ),
                     Utility::StringConversionException );
  BOOST_CHECK_THROW( Utility::fromString<UnsignedT>( "0.0" ),
                     Utility::StringConversionException );
  BOOST_CHECK_THROW( Utility::fromString<UnsignedT>( "0.000000000e+00" ),
                     Utility::StringConversionException );
  BOOST_CHECK_THROW( Utility::fromString<UnsignedT>( "-1." ),
                     Utility::StringConversionException );
  BOOST_CHECK_THROW( Utility::fromString<UnsignedT>( "1 1" ),
                     Utility::StringConversionException );
  // Overflow should result in an error: #(2^64) > 2^64 - 1
  BOOST_CHECK_THROW( Utility::fromString<UnsignedT>( "18446744073709551616" ),
                     Utility::StringConversionException );
}

//---------------------------------------------------------------------------//
// Check that unsigned integer types can be extracted from a stream
BOOST_AUTO_TEST_CASE_TEMPLATE( unsigned_fromStream, T, MultipleByteTypes )
{
  std::istringstream iss( "0" );

  T test_int;

  Utility::fromStream( iss, test_int );

  BOOST_CHECK_EQUAL( test_int, 0 );

  iss.str( "10" );
  iss.clear();

  Utility::fromStream( iss, test_int );

  BOOST_CHECK_EQUAL( test_int, 10 );

  iss.str( "255" );
  iss.clear();

  Utility::fromStream( iss, test_int );

  BOOST_CHECK_EQUAL( test_int, 255 );

  // Multiple integers in the same stream with default deliminators
  iss.str( "0 10   255 " );
  iss.clear();

  Utility::fromStream( iss, test_int );

  BOOST_CHECK_EQUAL( test_int, 0 );

  Utility::fromStream( iss, test_int );

  BOOST_CHECK_EQUAL( test_int, 10 );

  Utility::fromStream( iss, test_int );

  BOOST_CHECK_EQUAL( test_int, 255 );
  
  // Multiple integers in the same stream with custom deliminators
  iss.str( "255, 1" );
  iss.clear();
  
  Utility::fromStream( iss, test_int, "," );

  BOOST_CHECK_EQUAL( test_int, 255 );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, test_int );

  BOOST_CHECK_EQUAL( test_int, 1 );
}

//---------------------------------------------------------------------------//
// Check that a float can be created from a string
BOOST_AUTO_TEST_CASE( float_fromString )
{
  BOOST_CHECK_EQUAL( Utility::fromString<float>( "1" ), 1.0f );
  BOOST_CHECK_EQUAL( Utility::fromString<float>( "-1.0" ), -1.0f );
  BOOST_CHECK_EQUAL( Utility::fromString<float>( "0.000000000e+00" ), 0.0f );
  BOOST_CHECK_EQUAL( Utility::fromString<float>( "inf" ),
                       std::numeric_limits<float>::infinity() );
  BOOST_CHECK_EQUAL( Utility::fromString<float>( "infinity" ),
                       std::numeric_limits<float>::infinity() );
  BOOST_CHECK_EQUAL( Utility::fromString<float>( "Inf" ),
                       std::numeric_limits<float>::infinity() );
  BOOST_CHECK_EQUAL( Utility::fromString<float>( "Infinity" ),
                       std::numeric_limits<float>::infinity() );
  BOOST_CHECK_EQUAL( Utility::fromString<float>( "InFiNiTy" ),
                       std::numeric_limits<float>::infinity() );
  BOOST_CHECK_EQUAL( Utility::fromString<float>( "INF" ),
                       std::numeric_limits<float>::infinity() );
  BOOST_CHECK_EQUAL( Utility::fromString<float>( "INFINITY" ),
                       std::numeric_limits<float>::infinity() );
  BOOST_CHECK_EQUAL( Utility::fromString<float>( "-inf" ),
                       -std::numeric_limits<float>::infinity() );
  BOOST_CHECK_EQUAL( Utility::fromString<float>( "-infinity" ),
                       -std::numeric_limits<float>::infinity() );
  BOOST_CHECK_EQUAL( Utility::fromString<float>( "-Inf" ),
                       -std::numeric_limits<float>::infinity() );
  BOOST_CHECK_EQUAL( Utility::fromString<float>( "-Infinity" ),
                       -std::numeric_limits<float>::infinity() );
  BOOST_CHECK_EQUAL( Utility::fromString<float>( "-InFiNiTy" ),
                       -std::numeric_limits<float>::infinity() );
  BOOST_CHECK_EQUAL( Utility::fromString<float>( "-INF" ),
                       -std::numeric_limits<float>::infinity() );
  BOOST_CHECK_EQUAL( Utility::fromString<float>( "-INFINITY" ),
                       -std::numeric_limits<float>::infinity() );
  BOOST_CHECK_EQUAL( Utility::fromString<float>( "pi" ),
                       (float)Utility::PhysicalConstants::pi );
  BOOST_CHECK_EQUAL( Utility::fromString<float>( " Pi" ),
                       (float)Utility::PhysicalConstants::pi );
  BOOST_CHECK_EQUAL( Utility::fromString<float>( " PI " ),
                       (float)Utility::PhysicalConstants::pi );
  BOOST_CHECK_EQUAL( Utility::fromString<float>( "1*pi" ),
                       (float)Utility::PhysicalConstants::pi );
  BOOST_CHECK_EQUAL( Utility::fromString<float>( "2Pi" ),
                       2*(float)Utility::PhysicalConstants::pi );
  BOOST_CHECK_EQUAL( Utility::fromString<float>( "-pI" ),
                       -(float)Utility::PhysicalConstants::pi );
  BOOST_CHECK_CLOSE_FRACTION( Utility::fromString<float>( "-5*pi" ),
                              -5*(float)Utility::PhysicalConstants::pi,
                              1e-7 );
  BOOST_CHECK_EQUAL( Utility::fromString<float>( "pi/2" ),
                       (float)Utility::PhysicalConstants::pi/2 );
  BOOST_CHECK_EQUAL( Utility::fromString<float>( "-pi/2" ),
                       -(float)Utility::PhysicalConstants::pi/2 );
  BOOST_CHECK_EQUAL( Utility::fromString<float>( "pi/3" ),
                       (float)Utility::PhysicalConstants::pi/3 );
  BOOST_CHECK_EQUAL( Utility::fromString<float>( "2pi/3" ),
                       2*(float)Utility::PhysicalConstants::pi/3 );
  BOOST_CHECK_EQUAL( Utility::fromString<float>( "-3pi/7" ),
                       -3*(float)Utility::PhysicalConstants::pi/7 );
  BOOST_CHECK_CLOSE_FRACTION( Utility::fromString<float>( "5*pi/3" ),
                              5*(float)Utility::PhysicalConstants::pi/3,
                              1e-7 );
  BOOST_CHECK_CLOSE_FRACTION( Utility::fromString<float>( "-5*PI/3" ),
                              -5*(float)Utility::PhysicalConstants::pi/3,
                              1e-7 );
  
  BOOST_CHECK_THROW( Utility::fromString<float>( "1.0 1.0" ),
                     Utility::StringConversionException );
  BOOST_CHECK_THROW( Utility::fromString<float>( "1 1" ),
                     Utility::StringConversionException );
  BOOST_CHECK_THROW( Utility::fromString<float>( "-pi / 2 5*pi/3" ),
                     Utility::StringConversionException );
  BOOST_CHECK_THROW( Utility::fromString<float>( "1.01.0" ),
                     Utility::StringConversionException );
}

//---------------------------------------------------------------------------//
// Check that a float can be extracted from a stream
BOOST_AUTO_TEST_CASE( float_fromStream )
{
  std::istringstream iss( "1" );

  float test_float;

  Utility::fromStream( iss, test_float );

  BOOST_CHECK_EQUAL( test_float, 1.0f );

  iss.str( "-1.0" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  BOOST_CHECK_EQUAL( test_float, -1.0f );

  iss.str( "0.000000000e+00" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  BOOST_CHECK_EQUAL( test_float, 0.0f );

  iss.str( "inf" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  BOOST_CHECK_EQUAL( test_float, std::numeric_limits<float>::infinity() );

  iss.str( "infinity" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  BOOST_CHECK_EQUAL( test_float, std::numeric_limits<float>::infinity() );

  iss.str( "Inf" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  BOOST_CHECK_EQUAL( test_float, std::numeric_limits<float>::infinity() );

  iss.str( "Infinity" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  BOOST_CHECK_EQUAL( test_float, std::numeric_limits<float>::infinity() );

  iss.str( "InFiNiTy" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  BOOST_CHECK_EQUAL( test_float, std::numeric_limits<float>::infinity() );

  iss.str( "INF" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  BOOST_CHECK_EQUAL( test_float, std::numeric_limits<float>::infinity() );

  iss.str( "INFINITY" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  BOOST_CHECK_EQUAL( test_float, std::numeric_limits<float>::infinity() );

  iss.str( "-inf" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  BOOST_CHECK_EQUAL( test_float, -std::numeric_limits<float>::infinity() );

  iss.str( "-infinity" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  BOOST_CHECK_EQUAL( test_float, -std::numeric_limits<float>::infinity() );

  iss.str( "-Inf" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  BOOST_CHECK_EQUAL( test_float, -std::numeric_limits<float>::infinity() );

  iss.str( "-Infinity" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  BOOST_CHECK_EQUAL( test_float, -std::numeric_limits<float>::infinity() );

  iss.str( "-InFiNiTy" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  BOOST_CHECK_EQUAL( test_float, -std::numeric_limits<float>::infinity() );

  iss.str( "-INF" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  BOOST_CHECK_EQUAL( test_float, -std::numeric_limits<float>::infinity() );

  iss.str( "-INFINITY" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  BOOST_CHECK_EQUAL( test_float, -std::numeric_limits<float>::infinity() );
  
  iss.str( "pi" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  BOOST_CHECK_EQUAL( test_float, (float)Utility::PhysicalConstants::pi );

  iss.str( " Pi" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  BOOST_CHECK_EQUAL( test_float, (float)Utility::PhysicalConstants::pi );

  iss.str( " PI " );
  iss.clear();

  Utility::fromStream( iss, test_float );

  BOOST_CHECK_EQUAL( test_float, (float)Utility::PhysicalConstants::pi );
                       
  iss.str( "1*pi" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  BOOST_CHECK_EQUAL( test_float, (float)Utility::PhysicalConstants::pi );

  iss.str( "2Pi" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  BOOST_CHECK_EQUAL( test_float, 2*(float)Utility::PhysicalConstants::pi );
  
  iss.str( "-pI" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  BOOST_CHECK_EQUAL( test_float, -(float)Utility::PhysicalConstants::pi );

  iss.str( "-5*pi" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  BOOST_CHECK_CLOSE_FRACTION( test_float,
                              -5*(float)Utility::PhysicalConstants::pi,
                              1e-7 );

  iss.str( "pi/2" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  
  BOOST_CHECK_EQUAL( test_float, (float)Utility::PhysicalConstants::pi/2 );

  iss.str( "-pi/2" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  BOOST_CHECK_EQUAL( test_float, -(float)Utility::PhysicalConstants::pi/2 );

  iss.str( "pi/3" );
  iss.clear();

  Utility::fromStream( iss, test_float );
  
  BOOST_CHECK_EQUAL( test_float, (float)Utility::PhysicalConstants::pi/3 );

  iss.str( "2pi/3" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  BOOST_CHECK_EQUAL( test_float, 2*(float)Utility::PhysicalConstants::pi/3 );

  iss.str( "-3pi/7" );
  iss.clear();
  
  Utility::fromStream( iss, test_float );
  
  BOOST_CHECK_EQUAL( test_float,
                       -3*(float)Utility::PhysicalConstants::pi/7 );

  iss.str( "5*pi/3" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  BOOST_CHECK_CLOSE_FRACTION( test_float,
                              5*(float)Utility::PhysicalConstants::pi/3,
                              1e-7 );

  iss.str( "-5*PI/3" );
  iss.clear();

  Utility::fromStream( iss, test_float );
  
  BOOST_CHECK_CLOSE_FRACTION( test_float,
                              -5*(float)Utility::PhysicalConstants::pi/3,
                              1e-7 );

  // Multiple floats in the same stream with default deliminators
  iss.str( "-Pi/2 5*pi/3  -inf INFTY  1.0e+00 -1.00000e+00 0" );
  iss.clear();

  Utility::fromStream( iss, test_float );
  
  BOOST_CHECK_CLOSE_FRACTION( test_float,
                              -(float)Utility::PhysicalConstants::pi/2,
                              1e-7 );

  Utility::fromStream( iss, test_float );

  BOOST_CHECK_CLOSE_FRACTION( test_float,
                              5*(float)Utility::PhysicalConstants::pi/3,
                              1e-7 );

  Utility::fromStream( iss, test_float );

  BOOST_CHECK_EQUAL( test_float, -std::numeric_limits<float>::infinity() );

  Utility::fromStream( iss, test_float );

  BOOST_CHECK_EQUAL( test_float, std::numeric_limits<float>::infinity() );

  Utility::fromStream( iss, test_float );

  BOOST_CHECK_CLOSE_FRACTION( test_float, 1.0f, 1e-7 );

  Utility::fromStream( iss, test_float );

  BOOST_CHECK_CLOSE_FRACTION( test_float, -1.0f, 1e-7 );

  Utility::fromStream( iss, test_float );

  BOOST_CHECK_SMALL( test_float, 1e-7f );

  // Multiple floats in the same stream with custom deliminators
  iss.str( "-1, 1.000000000000000000e+00" );
  iss.clear();

  Utility::fromStream( iss, test_float, "," );

  BOOST_CHECK_EQUAL( test_float, -1.0f );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, test_float );

  BOOST_CHECK_EQUAL( test_float, 1.0f );

  iss.str( "-1, 2*pi/3" );
  iss.clear();

  Utility::fromStream( iss, test_float, "," );

  BOOST_CHECK_EQUAL( test_float, -1.0f );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, test_float );

  BOOST_CHECK_EQUAL( test_float, 2*(float)Utility::PhysicalConstants::pi/3 );

  iss.str( "-PI, Pi/2" );
  iss.clear();

  Utility::fromStream( iss, test_float, "," );

  BOOST_CHECK_EQUAL( test_float, -(float)Utility::PhysicalConstants::pi );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, test_float );

  BOOST_CHECK_EQUAL( test_float, (float)Utility::PhysicalConstants::pi/2 );
}

//---------------------------------------------------------------------------//
// Check that a double can be created from a string
BOOST_AUTO_TEST_CASE( double_fromString )
{
  BOOST_CHECK_EQUAL( Utility::fromString<double>( "1" ), 1.0 );
  BOOST_CHECK_EQUAL( Utility::fromString<double>( "-1.0" ), -1.0 );
  BOOST_CHECK_EQUAL( Utility::fromString<double>( "0.000000000000000000e+00" ), 0.0 );
  BOOST_CHECK_EQUAL( Utility::fromString<double>( "inf" ),
                       std::numeric_limits<double>::infinity() );
  BOOST_CHECK_EQUAL( Utility::fromString<double>( "infinity" ),
                       std::numeric_limits<double>::infinity() );
  BOOST_CHECK_EQUAL( Utility::fromString<double>( "Inf" ),
                       std::numeric_limits<double>::infinity() );
  BOOST_CHECK_EQUAL( Utility::fromString<double>( "Infinity" ),
                       std::numeric_limits<double>::infinity() );
  BOOST_CHECK_EQUAL( Utility::fromString<double>( "InFiNiTy" ),
                       std::numeric_limits<double>::infinity() );
  BOOST_CHECK_EQUAL( Utility::fromString<double>( "INF" ),
                       std::numeric_limits<double>::infinity() );
  BOOST_CHECK_EQUAL( Utility::fromString<double>( "INFINITY" ),
                       std::numeric_limits<double>::infinity() );
  BOOST_CHECK_EQUAL( Utility::fromString<double>( "-inf" ),
                       -std::numeric_limits<double>::infinity() );
  BOOST_CHECK_EQUAL( Utility::fromString<double>( "-infinity" ),
                       -std::numeric_limits<double>::infinity() );
  BOOST_CHECK_EQUAL( Utility::fromString<double>( "-Inf" ),
                       -std::numeric_limits<double>::infinity() );
  BOOST_CHECK_EQUAL( Utility::fromString<double>( "-Infinity" ),
                       -std::numeric_limits<double>::infinity() );
  BOOST_CHECK_EQUAL( Utility::fromString<double>( "-InFiNiTy" ),
                       -std::numeric_limits<double>::infinity() );
  BOOST_CHECK_EQUAL( Utility::fromString<double>( "-INF" ),
                       -std::numeric_limits<double>::infinity() );
  BOOST_CHECK_EQUAL( Utility::fromString<double>( "-INFINITY" ),
                       -std::numeric_limits<double>::infinity() );
  BOOST_CHECK_EQUAL( Utility::fromString<double>( "pi" ),
                       Utility::PhysicalConstants::pi );
  BOOST_CHECK_EQUAL( Utility::fromString<double>( " Pi" ),
                       Utility::PhysicalConstants::pi );
  BOOST_CHECK_EQUAL( Utility::fromString<double>( " PI " ),
                       Utility::PhysicalConstants::pi );
  BOOST_CHECK_EQUAL( Utility::fromString<double>( "1*pi" ),
                       Utility::PhysicalConstants::pi );
  BOOST_CHECK_EQUAL( Utility::fromString<double>( "2Pi" ),
                       2*Utility::PhysicalConstants::pi );
  BOOST_CHECK_EQUAL( Utility::fromString<double>( "-pI" ),
                       -Utility::PhysicalConstants::pi );
  BOOST_CHECK_CLOSE_FRACTION( Utility::fromString<double>( "-5*pi" ),
                              -5*Utility::PhysicalConstants::pi,
                              1e-7 );
  BOOST_CHECK_EQUAL( Utility::fromString<double>( "pi/2" ),
                       Utility::PhysicalConstants::pi/2 );
  BOOST_CHECK_EQUAL( Utility::fromString<double>( "-pi/2" ),
                       -Utility::PhysicalConstants::pi/2 );
  BOOST_CHECK_EQUAL( Utility::fromString<double>( "pi/3" ),
                       Utility::PhysicalConstants::pi/3 );
  BOOST_CHECK_EQUAL( Utility::fromString<double>( "2pi/3" ),
                       2*Utility::PhysicalConstants::pi/3 );
  BOOST_CHECK_EQUAL( Utility::fromString<double>( "-3pi/7" ),
                       -3*Utility::PhysicalConstants::pi/7 );
  BOOST_CHECK_CLOSE_FRACTION( Utility::fromString<double>( "5*pi/3" ),
                              5*Utility::PhysicalConstants::pi/3,
                              1e-7 );
  BOOST_CHECK_CLOSE_FRACTION( Utility::fromString<double>( "-5*PI/3" ),
                              -5*Utility::PhysicalConstants::pi/3,
                              1e-7 );

  BOOST_CHECK_THROW( Utility::fromString<double>( "1.0 1.0" ),
                     Utility::StringConversionException );
  BOOST_CHECK_THROW( Utility::fromString<double>( "1 1" ),
                     Utility::StringConversionException );
  BOOST_CHECK_THROW( Utility::fromString<double>( "-pi / 2 5*pi/3" ),
                     Utility::StringConversionException );
  BOOST_CHECK_THROW( Utility::fromString<double>( "1.01.0" ),
                     Utility::StringConversionException );
}

//---------------------------------------------------------------------------//
// Check that a double can be extracted from a stream
BOOST_AUTO_TEST_CASE( double_fromStream )
{
  std::istringstream iss( "1" );

  double test_double;

  Utility::fromStream( iss, test_double );

  BOOST_CHECK_EQUAL( test_double, 1.0 );

  iss.str( "-1.0" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  BOOST_CHECK_EQUAL( test_double, -1.0 );

  iss.str( "0.000000000000000000e+00" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  BOOST_CHECK_EQUAL( test_double, 0.0 );

  iss.str( "inf" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  BOOST_CHECK_EQUAL( test_double, std::numeric_limits<double>::infinity() );

  iss.str( "infinity" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  BOOST_CHECK_EQUAL( test_double, std::numeric_limits<double>::infinity() );

  iss.str( "Inf" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  BOOST_CHECK_EQUAL( test_double, std::numeric_limits<double>::infinity() );

  iss.str( "Infinity" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  BOOST_CHECK_EQUAL( test_double, std::numeric_limits<double>::infinity() );

  iss.str( "InFiNiTy" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  BOOST_CHECK_EQUAL( test_double, std::numeric_limits<double>::infinity() );

  iss.str( "INF" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  BOOST_CHECK_EQUAL( test_double, std::numeric_limits<double>::infinity() );

  iss.str( "INFINITY" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  BOOST_CHECK_EQUAL( test_double, std::numeric_limits<double>::infinity() );

  iss.str( "-inf" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  BOOST_CHECK_EQUAL( test_double, -std::numeric_limits<double>::infinity() );

  iss.str( "-infinity" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  BOOST_CHECK_EQUAL( test_double, -std::numeric_limits<double>::infinity() );

  iss.str( "-Inf" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  BOOST_CHECK_EQUAL( test_double, -std::numeric_limits<double>::infinity() );

  iss.str( "-Infinity" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  BOOST_CHECK_EQUAL( test_double, -std::numeric_limits<double>::infinity() );

  iss.str( "-InFiNiTy" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  BOOST_CHECK_EQUAL( test_double, -std::numeric_limits<double>::infinity() );

  iss.str( "-INF" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  BOOST_CHECK_EQUAL( test_double, -std::numeric_limits<double>::infinity() );

  iss.str( "-INFINITY" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  BOOST_CHECK_EQUAL( test_double, -std::numeric_limits<double>::infinity() );
  
  iss.str( "pi" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  BOOST_CHECK_EQUAL( test_double, Utility::PhysicalConstants::pi );

  iss.str( " Pi" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  BOOST_CHECK_EQUAL( test_double, Utility::PhysicalConstants::pi );

  iss.str( " PI " );
  iss.clear();

  Utility::fromStream( iss, test_double );

  BOOST_CHECK_EQUAL( test_double, Utility::PhysicalConstants::pi );
                       
  iss.str( "1*pi" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  BOOST_CHECK_EQUAL( test_double, Utility::PhysicalConstants::pi );

  iss.str( "2Pi" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  BOOST_CHECK_EQUAL( test_double, 2*Utility::PhysicalConstants::pi );
  
  iss.str( "-pI" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  BOOST_CHECK_EQUAL( test_double, -Utility::PhysicalConstants::pi );

  iss.str( "-5*pi" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  BOOST_CHECK_CLOSE_FRACTION( test_double,
                              -5*Utility::PhysicalConstants::pi,
                              1e-14 );

  iss.str( "pi/2" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  
  BOOST_CHECK_EQUAL( test_double, Utility::PhysicalConstants::pi/2 );

  iss.str( "-pi/2" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  BOOST_CHECK_EQUAL( test_double, -Utility::PhysicalConstants::pi/2 );

  iss.str( "pi/3" );
  iss.clear();

  Utility::fromStream( iss, test_double );
  
  BOOST_CHECK_EQUAL( test_double, Utility::PhysicalConstants::pi/3 );

  iss.str( "2pi/3" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  BOOST_CHECK_EQUAL( test_double, 2*Utility::PhysicalConstants::pi/3 );

  iss.str( "-3pi/7" );
  iss.clear();
  
  Utility::fromStream( iss, test_double );
  
  BOOST_CHECK_EQUAL( test_double,
                       -3*Utility::PhysicalConstants::pi/7 );

  iss.str( "5*pi/3" );
  iss.clear();

  Utility::fromStream( iss, test_double );

  BOOST_CHECK_CLOSE_FRACTION( test_double,
                              5*Utility::PhysicalConstants::pi/3,
                              1e-14 );

  iss.str( "-5*PI/3" );
  iss.clear();

  Utility::fromStream( iss, test_double );
  
  BOOST_CHECK_CLOSE_FRACTION( test_double,
                              -5*Utility::PhysicalConstants::pi/3,
                              1e-14 );

  // Multiple doubles in the same stream with default deliminators
  iss.str( "-Pi/2 5*pi/3  -inf INFTY  1.0e+00 -1.00000e+00 0" );
  iss.clear();

  Utility::fromStream( iss, test_double );
  
  BOOST_CHECK_CLOSE_FRACTION( test_double,
                              -Utility::PhysicalConstants::pi/2,
                              1e-14 );

  Utility::fromStream( iss, test_double );

  BOOST_CHECK_CLOSE_FRACTION( test_double,
                              5*Utility::PhysicalConstants::pi/3,
                              1e-14 );

  Utility::fromStream( iss, test_double );

  BOOST_CHECK_EQUAL( test_double, -std::numeric_limits<double>::infinity() );

  Utility::fromStream( iss, test_double );

  BOOST_CHECK_EQUAL( test_double, std::numeric_limits<double>::infinity() );

  Utility::fromStream( iss, test_double );

  BOOST_CHECK_CLOSE_FRACTION( test_double, 1.0, 1e-14 );

  Utility::fromStream( iss, test_double );

  BOOST_CHECK_CLOSE_FRACTION( test_double, -1.0, 1e-14 );

  Utility::fromStream( iss, test_double );

  BOOST_CHECK_SMALL( test_double, 1e-14 );

  // Multiple floats in the same stream with custom deliminators
  iss.str( "-1, 1.000000000e+00" );
  iss.clear();

  Utility::fromStream( iss, test_double, "," );

  BOOST_CHECK_EQUAL( test_double, -1.0 );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, test_double );

  BOOST_CHECK_EQUAL( test_double, 1.0 );

  iss.str( "-1, 2*pi/3" );
  iss.clear();

  Utility::fromStream( iss, test_double, "," );

  BOOST_CHECK_EQUAL( test_double, -1.0 );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, test_double );

  BOOST_CHECK_EQUAL( test_double, 2*Utility::PhysicalConstants::pi/3 );

  iss.str( "-PI, Pi/2" );
  iss.clear();

  Utility::fromStream( iss, test_double, "," );

  BOOST_CHECK_EQUAL( test_double, -Utility::PhysicalConstants::pi );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, test_double );

  BOOST_CHECK_EQUAL( test_double, Utility::PhysicalConstants::pi/2 );
}

//---------------------------------------------------------------------------//
// Check that a std::complex can be created from a string
BOOST_AUTO_TEST_CASE_TEMPLATE( complex_fromString, T, ComplexTestTypes )
{
  std::string complex_string = Utility::toString( std::complex<T>(0, 0) );

  std::complex<T> complex_value =
    Utility::fromString<std::complex<T> >( complex_string );

  BOOST_CHECK_EQUAL( complex_value, std::complex<T>(0, 0) );

  complex_string = Utility::toString( std::complex<T>(1, 0) );
  complex_value = Utility::fromString<std::complex<T> >( complex_string );

  BOOST_CHECK_EQUAL( complex_value, std::complex<T>(1, 0) );

  complex_string = Utility::toString( std::complex<T>(0, 1) );
  complex_value = Utility::fromString<std::complex<T> >( complex_string );

  BOOST_CHECK_EQUAL( complex_value, std::complex<T>(0, 1) );

  complex_string = Utility::toString( std::complex<T>(1, 1) );
  complex_value = Utility::fromString<std::complex<T> >( complex_string );

  BOOST_CHECK_EQUAL( complex_value, std::complex<T>(1, 1) );

  complex_string = Utility::toString( std::complex<T>(2, 2) );
  complex_value = Utility::fromString<std::complex<T> >( complex_string );

  BOOST_CHECK_EQUAL( complex_value, std::complex<T>(2, 2) );

  if( std::is_signed<T>::value )
  {
    complex_string = Utility::toString( std::complex<T>(-1, 0) );
    complex_value = Utility::fromString<std::complex<T> >( complex_string );

    BOOST_CHECK_EQUAL( complex_value, std::complex<T>(-1, 0) );
    
    complex_string = Utility::toString( std::complex<T>(0, -1) );
    complex_value = Utility::fromString<std::complex<T> >( complex_string );
    
    BOOST_CHECK_EQUAL( complex_value, std::complex<T>(0, -1) );
    
    complex_string = Utility::toString( std::complex<T>(-1, -1) );
    complex_value = Utility::fromString<std::complex<T> >( complex_string );
    
    BOOST_CHECK_EQUAL( complex_value, std::complex<T>(-1, -1) );
    
    complex_string = Utility::toString( std::complex<T>(-2, -2) );
    complex_value = Utility::fromString<std::complex<T> >( complex_string );
    
    BOOST_CHECK_EQUAL( complex_value, std::complex<T>(-2, -2) );
  }

  complex_string = std::string("{") + Utility::toString(0) + "," +
    Utility::toString(0) + "," + Utility::toString(0) + "}";

  BOOST_CHECK_THROW( Utility::fromString<std::complex<T> >( complex_string ),
                     Utility::StringConversionException );

  complex_string = std::string("{") + Utility::toString(0) + "}";

  BOOST_CHECK_THROW( Utility::fromString<std::complex<T> >( complex_string ),
                     Utility::StringConversionException );
}

//---------------------------------------------------------------------------//
// Check that a std::complex can be extracted from a stream
BOOST_AUTO_TEST_CASE_TEMPLATE( complex_fromStream, T, ComplexTestTypes )
{
  std::istringstream iss;

  iss.str( Utility::toString( std::complex<T>(0, 0) ) );

  std::complex<T> complex_value;

  Utility::fromStream( iss, complex_value );

  BOOST_CHECK_EQUAL( complex_value, std::complex<T>(0, 0) );

  iss.str( Utility::toString( std::complex<T>(1, 0) ) );
  iss.clear();

  Utility::fromStream( iss, complex_value );

  BOOST_CHECK_EQUAL( complex_value, std::complex<T>(1, 0) );

  iss.str( Utility::toString( std::complex<T>(0, 1) ) );
  iss.clear();

  Utility::fromStream( iss, complex_value );

  BOOST_CHECK_EQUAL( complex_value, std::complex<T>(0, 1) );

  iss.str( Utility::toString( std::complex<T>(1, 1) ) );
  iss.clear();
  
  Utility::fromStream( iss, complex_value );

  BOOST_CHECK_EQUAL( complex_value, std::complex<T>(1, 1) );

  iss.str( Utility::toString( std::complex<T>(2, 2) ) );
  iss.clear();

  Utility::fromStream( iss, complex_value );

  BOOST_CHECK_EQUAL( complex_value, std::complex<T>(2, 2) );

  // Multiple complex values in the same stream with default deliminators
  iss.str( Utility::toString( std::complex<T>(0, 0) ) + " " +
           Utility::toString( std::complex<T>(1, 0) ) + " " +
           Utility::toString( std::complex<T>(0, 1) ) + "  " +
           Utility::toString( std::complex<T>(1, 1) ) + "\t" +
           Utility::toString( std::complex<T>(2, 2) ) + "\n" +
           Utility::toString( std::complex<T>(3, 3) ) );
  iss.clear();

  Utility::fromStream( iss, complex_value );

  BOOST_CHECK_EQUAL( complex_value, std::complex<T>(0, 0) );

  Utility::fromStream( iss, complex_value );

  BOOST_CHECK_EQUAL( complex_value, std::complex<T>(1, 0) );

  Utility::fromStream( iss, complex_value );

  BOOST_CHECK_EQUAL( complex_value, std::complex<T>(0, 1) );

  Utility::fromStream( iss, complex_value );

  BOOST_CHECK_EQUAL( complex_value, std::complex<T>(1, 1) );

  Utility::fromStream( iss, complex_value );

  BOOST_CHECK_EQUAL( complex_value, std::complex<T>(2, 2) );

  Utility::fromStream( iss, complex_value );

  BOOST_CHECK_EQUAL( complex_value, std::complex<T>(3, 3) );

  // Multiple complex values in the same stream with custom deliminators
  iss.str( Utility::toString( std::complex<T>(0, 0) ) + ", " +
           Utility::toString( std::complex<T>(1, 0) ) + " , " +
           Utility::toString( std::complex<T>(0, 1) ) + ",  " +
           Utility::toString( std::complex<T>(1, 1) ) + ",\t" +
           Utility::toString( std::complex<T>(2, 2) ) + "," +
           Utility::toString( std::complex<T>(3, 3) ) );
  iss.clear();

  Utility::fromStream( iss, complex_value, "," );

  BOOST_CHECK_EQUAL( complex_value, std::complex<T>(0, 0) );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, complex_value, "," );

  BOOST_CHECK_EQUAL( complex_value, std::complex<T>(1, 0) );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, complex_value, "," );

  BOOST_CHECK_EQUAL( complex_value, std::complex<T>(0, 1) );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, complex_value, "," );

  BOOST_CHECK_EQUAL( complex_value, std::complex<T>(1, 1) );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, complex_value, "," );

  BOOST_CHECK_EQUAL( complex_value, std::complex<T>(2, 2) );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, complex_value );

  BOOST_CHECK_EQUAL( complex_value, std::complex<T>(3, 3) );

  if( std::is_signed<T>::value )
  {
    iss.str( Utility::toString( std::complex<T>(-1, 0) ) );
    iss.clear();
    
    Utility::fromStream( iss, complex_value );

    BOOST_CHECK_EQUAL( complex_value, std::complex<T>(-1, 0) );

    iss.str( Utility::toString( std::complex<T>(0, -1) ) );
    iss.clear();
    
    Utility::fromStream( iss, complex_value );
    
    BOOST_CHECK_EQUAL( complex_value, std::complex<T>(0, -1) );

    iss.str( Utility::toString( std::complex<T>(-1, -1) ) );
    iss.clear();
    
    Utility::fromStream( iss, complex_value );
    
    BOOST_CHECK_EQUAL( complex_value, std::complex<T>(-1, -1) );

    iss.str( Utility::toString( std::complex<T>(-2, -2) ) );
    iss.clear();

    Utility::fromStream( iss, complex_value );
    
    BOOST_CHECK_EQUAL( complex_value, std::complex<T>(-2, -2) );
  }

  iss.str( std::string("{") + Utility::toString(0) + "," +
           Utility::toString(0) + "," + Utility::toString(0) + "}" );
  iss.clear();

  BOOST_CHECK_THROW( Utility::fromStream( iss, complex_value ),
                     Utility::StringConversionException );

  iss.str( std::string("{") + Utility::toString(0) + "}" );
  iss.clear();

  BOOST_CHECK_THROW( Utility::fromStream( iss, complex_value ),
                     Utility::StringConversionException );
}

//---------------------------------------------------------------------------//
// Check that a boost::units::quantity can be created from a string
BOOST_AUTO_TEST_CASE_TEMPLATE( quantity_fromString,
                               QuantityType,
                               TestBasicQuantityTypes )
{
  typedef typename Utility::QuantityTraits<QuantityType>::UnitType UnitType;
  typedef typename Utility::QuantityTraits<QuantityType>::RawType RawType;

  // Basic quantity types
  std::string quantity_string =
    Utility::toString( QuantityType::from_value(RawType(0)) );

  QuantityType quantity =
    Utility::fromString<QuantityType>( quantity_string );

  BOOST_CHECK_EQUAL( quantity, QuantityType::from_value(RawType(0)) );

  quantity_string = Utility::toString( QuantityType::from_value(RawType(1)) );

  quantity = Utility::fromString<QuantityType>( quantity_string );

  BOOST_CHECK_EQUAL( quantity, QuantityType::from_value(RawType(1)) );

  quantity_string = Utility::toString( QuantityType::from_value(RawType(2)) );

  quantity = Utility::fromString<QuantityType>( quantity_string );

  BOOST_CHECK_EQUAL( quantity, QuantityType::from_value(RawType(2)) );

  // Complex quantity types
  typedef std::complex<RawType> ComplexRawType;
  typedef boost::units::quantity<UnitType,ComplexRawType> ComplexQuantityType;

  quantity_string =
    Utility::toString( ComplexQuantityType::from_value(ComplexRawType(0, 0)) );

  ComplexQuantityType complex_quantity =
    Utility::fromString<ComplexQuantityType>( quantity_string );
  
  BOOST_CHECK_EQUAL( complex_quantity, ComplexQuantityType::from_value(ComplexRawType(0, 0)) );

  quantity_string =
    Utility::toString( ComplexQuantityType::from_value(ComplexRawType(1, 0)) );

  complex_quantity =
    Utility::fromString<ComplexQuantityType>( quantity_string );
  
  BOOST_CHECK_EQUAL( complex_quantity, ComplexQuantityType::from_value(ComplexRawType(1, 0)) );

  quantity_string =
    Utility::toString( ComplexQuantityType::from_value(ComplexRawType(0, 1)) );

  complex_quantity =
    Utility::fromString<ComplexQuantityType>( quantity_string );
  
  BOOST_CHECK_EQUAL( complex_quantity, ComplexQuantityType::from_value(ComplexRawType(0, 1)) );

  quantity_string =
    Utility::toString( ComplexQuantityType::from_value(ComplexRawType(1, 1)) );

  complex_quantity =
    Utility::fromString<ComplexQuantityType>( quantity_string );
  
  BOOST_CHECK_EQUAL( complex_quantity, ComplexQuantityType::from_value(ComplexRawType(1, 1)) );

  quantity_string =
    Utility::toString( ComplexQuantityType::from_value(ComplexRawType(2, 2)) );

  complex_quantity =
    Utility::fromString<ComplexQuantityType>( quantity_string );
  
  BOOST_CHECK_EQUAL( complex_quantity, ComplexQuantityType::from_value(ComplexRawType(2, 2)) );

  if( Utility::QuantityTraits<QuantityType>::is_signed::value )
  {
    // Basic quantity types
    quantity_string =
      Utility::toString( QuantityType::from_value(RawType(-1)) );

    quantity = Utility::fromString<QuantityType>( quantity_string );
    
    BOOST_CHECK_EQUAL( quantity, QuantityType::from_value(RawType(-1)) );
    
    quantity_string =
      Utility::toString( QuantityType::from_value(RawType(-2)) );
    
    quantity = Utility::fromString<QuantityType>( quantity_string );
    
    BOOST_CHECK_EQUAL( quantity, QuantityType::from_value(RawType(-2)) );
    
    // Complex quantity types
    quantity_string =
      Utility::toString( ComplexQuantityType::from_value(ComplexRawType(-1, 0)) );
    
    complex_quantity =
      Utility::fromString<ComplexQuantityType>( quantity_string );
  
    BOOST_CHECK_EQUAL( complex_quantity, ComplexQuantityType::from_value(ComplexRawType(-1, 0)) );
    
    quantity_string =
      Utility::toString( ComplexQuantityType::from_value(ComplexRawType(0, -1)) );
    
    complex_quantity =
      Utility::fromString<ComplexQuantityType>( quantity_string );
    
    BOOST_CHECK_EQUAL( complex_quantity, ComplexQuantityType::from_value(ComplexRawType(0, -1)) );
    
    quantity_string =
      Utility::toString( ComplexQuantityType::from_value(ComplexRawType(-1, -1)) );
    
    complex_quantity =
      Utility::fromString<ComplexQuantityType>( quantity_string );
    
    BOOST_CHECK_EQUAL( complex_quantity, ComplexQuantityType::from_value(ComplexRawType(-1, -1)) );
    
    quantity_string =
      Utility::toString( ComplexQuantityType::from_value(ComplexRawType(-2, -2)) );
    
    complex_quantity =
      Utility::fromString<ComplexQuantityType>( quantity_string );
    
    BOOST_CHECK_EQUAL( complex_quantity, ComplexQuantityType::from_value(ComplexRawType(-2, -2)) );
  }
}

//---------------------------------------------------------------------------//
// Check that a boost::units::quantity can be extracted from a stream
BOOST_AUTO_TEST_CASE_TEMPLATE( quantity_fromStream,
                               QuantityType,
                               TestBasicQuantityTypes )
{
  typedef typename Utility::QuantityTraits<QuantityType>::UnitType UnitType;
  typedef typename Utility::QuantityTraits<QuantityType>::RawType RawType;

  std::istringstream iss;

  // Basic quantity types
  iss.str( Utility::toString( QuantityType::from_value(RawType(0)) ) );

  QuantityType quantity;

  Utility::fromStream( iss, quantity );

  BOOST_CHECK_EQUAL( quantity, QuantityType::from_value(RawType(0)) );

  iss.str( Utility::toString( QuantityType::from_value(RawType(1)) ) );
  iss.clear();

  Utility::fromStream( iss, quantity );

  BOOST_CHECK_EQUAL( quantity, QuantityType::from_value(RawType(1)) );

  iss.str( Utility::toString( QuantityType::from_value(RawType(2)) ) );
  iss.clear();

  Utility::fromStream( iss, quantity );

  BOOST_CHECK_EQUAL( quantity, QuantityType::from_value(RawType(2)) );

  // Complex quantity types
  typedef std::complex<RawType> ComplexRawType;
  typedef boost::units::quantity<UnitType,ComplexRawType> ComplexQuantityType;

  iss.str( Utility::toString( ComplexQuantityType::from_value(ComplexRawType(0, 0)) ) );
  iss.clear();

  ComplexQuantityType complex_quantity;

  Utility::fromStream( iss, complex_quantity );
  
  BOOST_CHECK_EQUAL( complex_quantity, ComplexQuantityType::from_value(ComplexRawType(0, 0)) );

  iss.str( Utility::toString( ComplexQuantityType::from_value(ComplexRawType(1, 0)) ) );
  iss.clear();

  Utility::fromStream( iss, complex_quantity );
  
  BOOST_CHECK_EQUAL( complex_quantity, ComplexQuantityType::from_value(ComplexRawType(1, 0)) );

  iss.str( Utility::toString( ComplexQuantityType::from_value(ComplexRawType(0, 1)) ) );
  iss.clear();

  Utility::fromStream( iss, complex_quantity );
  
  BOOST_CHECK_EQUAL( complex_quantity, ComplexQuantityType::from_value(ComplexRawType(0, 1)) );

  iss.str( Utility::toString( ComplexQuantityType::from_value(ComplexRawType(1, 1)) ) );
  iss.clear();

  Utility::fromStream( iss, complex_quantity );
  
  BOOST_CHECK_EQUAL( complex_quantity, ComplexQuantityType::from_value(ComplexRawType(1, 1)) );

  iss.str( Utility::toString( ComplexQuantityType::from_value(ComplexRawType(2, 2)) ) );
  iss.clear();

  Utility::fromStream( iss, complex_quantity );
  
  BOOST_CHECK_EQUAL( complex_quantity, ComplexQuantityType::from_value(ComplexRawType(2, 2)) );

  // Multiple quantities in the same stream with default deliminators
  iss.str( Utility::toString( QuantityType::from_value(RawType(0)) ) + " " +
           Utility::toString( QuantityType::from_value(RawType(1)) ) + "  " +
           Utility::toString( ComplexQuantityType::from_value(ComplexRawType(0, 0)) ) + "\t" +
           Utility::toString( ComplexQuantityType::from_value(ComplexRawType(1, 1)) ) + "\n" +
           Utility::toString( ComplexQuantityType::from_value(ComplexRawType(2, 2)) ) );
  iss.clear();

  Utility::fromStream( iss, quantity );

  BOOST_CHECK_EQUAL( quantity, QuantityType::from_value(RawType(0)) );

  Utility::fromStream( iss, quantity );

  BOOST_CHECK_EQUAL( quantity, QuantityType::from_value(RawType(1)) );

  Utility::fromStream( iss, complex_quantity );

  BOOST_CHECK_EQUAL( complex_quantity, ComplexQuantityType::from_value(ComplexRawType(0, 0)) );

  Utility::fromStream( iss, complex_quantity );

  BOOST_CHECK_EQUAL( complex_quantity, ComplexQuantityType::from_value(ComplexRawType(1, 1)) );

  Utility::fromStream( iss, complex_quantity );

  BOOST_CHECK_EQUAL( complex_quantity, ComplexQuantityType::from_value(ComplexRawType(2, 2)) );

  // Multiple quantities in the same stream with custom deliminators
  iss.str( Utility::toString( QuantityType::from_value(RawType(0)) ) + ", " +
           Utility::toString( QuantityType::from_value(RawType(1)) ) + ",  " +
           Utility::toString( ComplexQuantityType::from_value(ComplexRawType(0, 0)) ) + ",\t" +
           Utility::toString( ComplexQuantityType::from_value(ComplexRawType(1, 1)) ) + " ,\n" +
           Utility::toString( ComplexQuantityType::from_value(ComplexRawType(2, 2)) ) );
  iss.clear();

  Utility::fromStream( iss, quantity, "," );

  BOOST_CHECK_EQUAL( quantity, QuantityType::from_value(RawType(0)) );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, quantity, "," );

  BOOST_CHECK_EQUAL( quantity, QuantityType::from_value(RawType(1)) );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, complex_quantity, "," );

  BOOST_CHECK_EQUAL( complex_quantity, ComplexQuantityType::from_value(ComplexRawType(0, 0)) );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );
  
  Utility::fromStream( iss, complex_quantity, "," );

  BOOST_CHECK_EQUAL( complex_quantity, ComplexQuantityType::from_value(ComplexRawType(1, 1)) );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );
  
  Utility::fromStream( iss, complex_quantity );

  BOOST_CHECK_EQUAL( complex_quantity, ComplexQuantityType::from_value(ComplexRawType(2, 2)) );

  if( Utility::QuantityTraits<QuantityType>::is_signed::value )
  {
    // Basic quantity types
    iss.str( Utility::toString( QuantityType::from_value(RawType(-1)) ) );
    iss.clear();

    Utility::fromStream( iss, quantity );
    
    BOOST_CHECK_EQUAL( quantity, QuantityType::from_value(RawType(-1)) );

    iss.str( Utility::toString( QuantityType::from_value(RawType(-2)) ) );
    iss.clear();

    Utility::fromStream( iss, quantity );
    
    BOOST_CHECK_EQUAL( quantity, QuantityType::from_value(RawType(-2)) );
    
    // Complex quantity types
    iss.str( Utility::toString( ComplexQuantityType::from_value(ComplexRawType(-1, 0)) ) );
    iss.clear();
    
    Utility::fromStream( iss, complex_quantity );
  
    BOOST_CHECK_EQUAL( complex_quantity, ComplexQuantityType::from_value(ComplexRawType(-1, 0)) );
    
    iss.str( Utility::toString( ComplexQuantityType::from_value(ComplexRawType(0, -1)) ) );
    iss.clear();
    
    Utility::fromStream( iss, complex_quantity );
    
    BOOST_CHECK_EQUAL( complex_quantity, ComplexQuantityType::from_value(ComplexRawType(0, -1)) );
    
    iss.str( Utility::toString( ComplexQuantityType::from_value(ComplexRawType(-1, -1)) ) );
    iss.clear();
    
    Utility::fromStream( iss, complex_quantity );
    
    BOOST_CHECK_EQUAL( complex_quantity, ComplexQuantityType::from_value(ComplexRawType(-1, -1)) );
    
    iss.str( Utility::toString( ComplexQuantityType::from_value(ComplexRawType(-2, -2)) ) );
    iss.clear();
    
    Utility::fromStream( iss, complex_quantity );
    
    BOOST_CHECK_EQUAL( complex_quantity, ComplexQuantityType::from_value(ComplexRawType(-2, -2)) );
  }
}

//---------------------------------------------------------------------------//
// end tstFromStringTraits.cpp
//---------------------------------------------------------------------------//
