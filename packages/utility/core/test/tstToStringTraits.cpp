//---------------------------------------------------------------------------//
//!
//! \file   tstToStringTraits.cpp
//! \author Alex Robinson
//! \brief  ToStringTraits unit tests
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
#include "Utility_ToStringTraits.hpp"
#include "Utility_ElectronVoltUnit.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_UnitTraits.hpp"

using namespace Utility::Units;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

//---------------------------------------------------------------------------//
// Template Test Types
//---------------------------------------------------------------------------//
typedef boost::mpl::list<char, signed char, short, int, long, long long> TestTypes;

typedef boost::mpl::list<int, long, long long> LongTestTypes;

typedef boost::mpl::list<int, unsigned int, long, unsigned long, long long, unsigned long long, float, double> ComplexTestTypes;

template<typename Unit, typename RawTypeWrapper = void>
struct QuantityTypeList
{
  typedef boost::mpl::list<boost::units::quantity<Unit,float>, boost::units::quantity<Unit,double> > BasicFloatingPointQuantityTypes;
  
  typedef boost::mpl::list<boost::units::quantity<Unit,int>, boost::units::quantity<Unit,unsigned long>, boost::units::quantity<Unit,float>, boost::units::quantity<Unit,double> > BasicQuantityTypes;

  typedef boost::mpl::list<boost::units::quantity<Unit,std::complex<int> >, boost::units::quantity<Unit,std::complex<unsigned long> >, boost::units::quantity<Unit,std::complex<float> >, boost::units::quantity<Unit,std::complex<double> > > ComplexQuantityTypes;

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
// Check that a string can be converted to a string
BOOST_AUTO_TEST_CASE( string_toString )
{
  BOOST_CHECK_EQUAL( Utility::toString( std::string( " " ) ), " " );
  BOOST_CHECK_EQUAL( Utility::toString( std::string( "testing" ) ), "testing" );
  BOOST_CHECK_EQUAL( Utility::toString( "test c-string" ), "test c-string" );
}

//---------------------------------------------------------------------------//
// Check that a string can be placed in a stream
BOOST_AUTO_TEST_CASE( string_toStream )
{
  std::ostringstream oss;
  Utility::toStream( oss, std::string( " " ) );
  
  BOOST_CHECK_EQUAL( oss.str(), " " );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::string( "testing" ) );

  BOOST_CHECK_EQUAL( oss.str(), "testing" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, "test c-string" );

  BOOST_CHECK_EQUAL( oss.str(), "test c-string" );
}

//---------------------------------------------------------------------------//
// Check that a LogRecordType can be converted to a string
BOOST_AUTO_TEST_CASE( LogRecordType_toString )
{
  BOOST_CHECK_EQUAL( Utility::toString( Utility::ERROR_RECORD ), "Error" );
  BOOST_CHECK_EQUAL( Utility::toString( Utility::WARNING_RECORD ), "Warning" );
  BOOST_CHECK_EQUAL( Utility::toString( Utility::NOTIFICATION_RECORD ),
                     "Notification" );
  BOOST_CHECK_EQUAL( Utility::toString( Utility::DETAILS_RECORD ), "Details" );
  BOOST_CHECK_EQUAL( Utility::toString( Utility::PEDANTIC_DETAILS_RECORD ),
                     "Pedantic Details" );
}

//---------------------------------------------------------------------------//
// Check that a LogRecordType can be placed in a stream
BOOST_AUTO_TEST_CASE( LogRecordType_toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, Utility::ERROR_RECORD );

  BOOST_CHECK_EQUAL( oss.str(), "Error" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::WARNING_RECORD );

  BOOST_CHECK_EQUAL( oss.str(), "Warning" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::NOTIFICATION_RECORD );

  BOOST_CHECK_EQUAL( oss.str(), "Notification" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::DETAILS_RECORD );

  BOOST_CHECK_EQUAL( oss.str(), "Details" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::PEDANTIC_DETAILS_RECORD );

  BOOST_CHECK_EQUAL( oss.str(), "Pedantic Details" );
}

//---------------------------------------------------------------------------//
// Check that a bool can be converted to a string
BOOST_AUTO_TEST_CASE( bool_toString )
{
  BOOST_CHECK_EQUAL( Utility::toString( true ), "true" );
  BOOST_CHECK_EQUAL( Utility::toString( false ), "false" );
}

//---------------------------------------------------------------------------//
// Check that a bool can be placed in a stream
BOOST_AUTO_TEST_CASE( bool_toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, true );
  
  BOOST_CHECK_EQUAL( oss.str(), "true" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, false );

  BOOST_CHECK_EQUAL( oss.str(), "false" );
}

//---------------------------------------------------------------------------//
// Check that a float can be converted to a string
BOOST_AUTO_TEST_CASE( float_toString )
{
  BOOST_CHECK_EQUAL( Utility::toString( -1.0f ), "-1.000000000e+00" );
  BOOST_CHECK_EQUAL( Utility::toString( 0.0f ), "0.000000000e+00" );
  BOOST_CHECK_EQUAL( Utility::toString( 1.0f ), "1.000000000e+00" );
}

//---------------------------------------------------------------------------//
// Check that a float can be placed in a stream
BOOST_AUTO_TEST_CASE( float_toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, -1.0f );

  BOOST_CHECK_EQUAL( oss.str(), "-1.000000000e+00" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, 0.0f );

  BOOST_CHECK_EQUAL( oss.str(), "0.000000000e+00" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, 1.0f );

  BOOST_CHECK_EQUAL( oss.str(), "1.000000000e+00" );
}

//---------------------------------------------------------------------------//
// Check that a double can be converted to a string
BOOST_AUTO_TEST_CASE( double_toString )
{
  BOOST_CHECK_EQUAL( Utility::toString( -1.0 ), "-1.000000000000000000e+00" );
  BOOST_CHECK_EQUAL( Utility::toString( 0.0 ), "0.000000000000000000e+00" );
  BOOST_CHECK_EQUAL( Utility::toString( 1.0 ), "1.000000000000000000e+00" );
}

//---------------------------------------------------------------------------//
// Check that a double can be placed in a stream
BOOST_AUTO_TEST_CASE( double_toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, -1.0 );

  BOOST_CHECK_EQUAL( oss.str(), "-1.000000000000000000e+00" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, 0.0 );

  BOOST_CHECK_EQUAL( oss.str(), "0.000000000000000000e+00" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, 1.0 );

  BOOST_CHECK_EQUAL( oss.str(), "1.000000000000000000e+00" );
}

//---------------------------------------------------------------------------//
// Check that signed integer types can be converted to a string
BOOST_AUTO_TEST_CASE_TEMPLATE( toString, T, TestTypes )
{
  if( sizeof(T) > 1 )
  {
    BOOST_CHECK_EQUAL( Utility::toString( static_cast<T>( -10 ) ), "-10" );
    BOOST_CHECK_EQUAL( Utility::toString( static_cast<T>( 0 ) ), "0" );
    BOOST_CHECK_EQUAL( Utility::toString( static_cast<T>( 10 ) ), "10" );
  }
  else
  {
    BOOST_CHECK_EQUAL( Utility::toString( static_cast<T>( -10 ) ),
                       std::string( 1, -10 ) );
    BOOST_CHECK_EQUAL( Utility::toString( static_cast<T>( 0 ) ),
                       std::string( 1, 0 ) );
    BOOST_CHECK_EQUAL( Utility::toString( static_cast<T>( 10 ) ),
                       std::string( 1, 10 ) );
  }
}

//---------------------------------------------------------------------------//
// Check that signed integer types can be placed in a stream
BOOST_AUTO_TEST_CASE_TEMPLATE( toStream, T, TestTypes )
{
  std::ostringstream oss;

  Utility::toStream( oss, static_cast<T>( -10 ) );

  if( sizeof(T) > 1 )
    BOOST_CHECK_EQUAL( oss.str(), "-10" );
  else
    BOOST_CHECK_EQUAL( oss.str(), std::string( 1, -10 ) );      

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, static_cast<T>( 0 ) );

  if( sizeof(T) > 1 )
    BOOST_CHECK_EQUAL( oss.str(), "0" );
  else
    BOOST_CHECK_EQUAL( oss.str(), std::string( 1, 0 ) );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, static_cast<T>( 10 ) );

  if( sizeof(T) > 1 )
    BOOST_CHECK_EQUAL( oss.str(), "10" );
  else
    BOOST_CHECK_EQUAL( oss.str(), std::string( 1, 10 ) );
}

//---------------------------------------------------------------------------//
// Check that pointer types can be converted to a string
BOOST_AUTO_TEST_CASE_TEMPLATE( toString_pointer, T, LongTestTypes )
{
  std::string pointer_string = Utility::toString( (T*)NULL );
    
  BOOST_CHECK_EQUAL( pointer_string, "NULL" );
  
  T value = T();
  pointer_string = Utility::toString( &value );
  
  BOOST_CHECK( pointer_string.find( "x" ) < pointer_string.size() );

  pointer_string = Utility::toString( std::shared_ptr<T>() );

  BOOST_CHECK_EQUAL( pointer_string, "NULL" );

  pointer_string = Utility::toString( std::shared_ptr<const T>() );

  BOOST_CHECK_EQUAL( pointer_string, "NULL" );
}

//---------------------------------------------------------------------------//
// Check that pointer types can be placed in a stream
BOOST_AUTO_TEST_CASE_TEMPLATE( toStream_pointer, T, LongTestTypes )
{
  std::ostringstream oss;
  Utility::toStream( oss, (T*)NULL );
    
  BOOST_CHECK_EQUAL( oss.str(), "NULL" );

  oss.str( "" );
  oss.clear();
  
  T value = T();

  Utility::toStream( oss, &value );
  
  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::shared_ptr<T>() );

  BOOST_CHECK_EQUAL( oss.str(), "NULL" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::shared_ptr<const T>() );

  BOOST_CHECK_EQUAL( oss.str(), "NULL" );

  oss.str( "" );
  oss.clear();

  std::shared_ptr<T> shared_value( new T );

  Utility::toStream( oss, shared_value );

  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  oss.str( "" );
  oss.clear();

  std::shared_ptr<const T> shared_const_value( new T );

  Utility::toStream( oss, shared_const_value );

  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );
}

//---------------------------------------------------------------------------//
// Check that unsigned integer types can be converted to a string
BOOST_AUTO_TEST_CASE_TEMPLATE( unsigned_toString, T, TestTypes )
{
  typedef typename std::make_unsigned<T>::type UnsignedT;

  if( sizeof(T) > 1 )
  {
    BOOST_CHECK_EQUAL( Utility::toString( static_cast<UnsignedT>( 0 ) ), "0" );
    BOOST_CHECK_EQUAL( Utility::toString( static_cast<UnsignedT>( 10 ) ), "10" );
    BOOST_CHECK_EQUAL( Utility::toString( static_cast<UnsignedT>( 255 ) ), "255" );
  }
  else
  {
    BOOST_CHECK_EQUAL( Utility::toString( static_cast<UnsignedT>( 0 ) ),
                       std::string( 1, (char)0 ) );
    BOOST_CHECK_EQUAL( Utility::toString( static_cast<UnsignedT>( 10 ) ),
                       std::string( 1, (char)10 ) );
    BOOST_CHECK_EQUAL( Utility::toString( static_cast<UnsignedT>( 255 ) ),
                       std::string( 1, (char)255 ) );
  }
}

//---------------------------------------------------------------------------//
// Check that unsigned integer types can be placed in a stream
BOOST_AUTO_TEST_CASE_TEMPLATE( unsigned_toStream, T, TestTypes )
{
  typedef typename std::make_unsigned<T>::type UnsignedT;
  
  std::ostringstream oss;

  Utility::toStream( oss, static_cast<UnsignedT>( 0 ) );

  if( sizeof(T) > 1 )
    BOOST_CHECK_EQUAL( oss.str(), "0" );
  else
    BOOST_CHECK_EQUAL( oss.str(), std::string( 1, (char)0 ) );
  
  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, static_cast<UnsignedT>( 10 ) );

  if( sizeof(T) > 1 )
    BOOST_CHECK_EQUAL( oss.str(), "10" );
  else
    BOOST_CHECK_EQUAL( oss.str(), std::string( 1, (char)10 ) );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, static_cast<UnsignedT>( 255 ) );

  if( sizeof(T) > 1 )
    BOOST_CHECK_EQUAL( oss.str(), "255" );
  else
    BOOST_CHECK_EQUAL( oss.str(), std::string( 1, (char)255 ) );
}

//---------------------------------------------------------------------------//
// Check that std::complex types can be converted to a string
BOOST_AUTO_TEST_CASE_TEMPLATE( complex_toString, T, ComplexTestTypes )
{
  BOOST_CHECK_EQUAL( Utility::toString( std::complex<T>(0, 0) ),
                     std::string("{") + Utility::toString(T(0)) + ", " +
                     Utility::toString(T(0)) + "}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::complex<T>(1, 0) ),
                     std::string("{") + Utility::toString(T(1)) + ", " +
                     Utility::toString(T(0)) + "}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::complex<T>(0, 1) ),
                     std::string("{") + Utility::toString(T(0)) + ", " +
                     Utility::toString(T(1)) + "}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::complex<T>(1, 1) ),
                     std::string("{") + Utility::toString(T(1)) + ", " +
                     Utility::toString(T(1)) + "}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::complex<T>(2, 2) ),
                     std::string("{") + Utility::toString(T(2)) + ", " +
                     Utility::toString(T(2)) + "}" );

  if( std::is_signed<T>::value )
  {
    BOOST_CHECK_EQUAL( Utility::toString( std::complex<T>(-1, 0) ),
                       std::string("{") + Utility::toString(T(-1)) + ", " +
                       Utility::toString(T(0)) + "}" );
    BOOST_CHECK_EQUAL( Utility::toString( std::complex<T>(0, -1) ),
                       std::string("{") + Utility::toString(T(0)) + ", " +
                       Utility::toString(T(-1)) + "}" );
    BOOST_CHECK_EQUAL( Utility::toString( std::complex<T>(-1, -1) ),
                       std::string("{") + Utility::toString(T(-1)) + ", " +
                       Utility::toString(T(-1)) + "}" );
    BOOST_CHECK_EQUAL( Utility::toString( std::complex<T>(-2, -2) ),
                       std::string("{") + Utility::toString(T(-2)) + ", " +
                       Utility::toString(T(-2)) + "}" );
  }
}

//---------------------------------------------------------------------------//
// Check that std::complex types can be placed in a stream
BOOST_AUTO_TEST_CASE_TEMPLATE( complex_toStream, T, ComplexTestTypes )
{
  std::ostringstream oss;

  Utility::toStream( oss, std::complex<T>(0, 0) );

  BOOST_CHECK_EQUAL( oss.str(),
                     std::string("{") + Utility::toString(T(0)) + ", " +
                     Utility::toString(T(0)) + "}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::complex<T>(1, 0) );

  BOOST_CHECK_EQUAL( oss.str(),
                     std::string("{") + Utility::toString(T(1)) + ", " +
                     Utility::toString(T(0)) + "}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::complex<T>(0, 1) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                     std::string("{") + Utility::toString(T(0)) + ", " +
                     Utility::toString(T(1)) + "}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::complex<T>(1, 1) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                     std::string("{") + Utility::toString(T(1)) + ", " +
                     Utility::toString(T(1)) + "}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::complex<T>(2, 2) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                     std::string("{") + Utility::toString(T(2)) + ", " +
                     Utility::toString(T(2)) + "}" );

  if( std::is_signed<T>::value )
  {
    oss.str( "" );
    oss.clear();

    Utility::toStream( oss, std::complex<T>(-1, 0) );
    
    BOOST_CHECK_EQUAL( oss.str(),
                       std::string("{") + Utility::toString(T(-1)) + ", " +
                       Utility::toString(T(0)) + "}" );

    oss.str( "" );
    oss.clear();

    Utility::toStream( oss, std::complex<T>(0, -1) );
    
    BOOST_CHECK_EQUAL( oss.str(),
                       std::string("{") + Utility::toString(T(0)) + ", " +
                       Utility::toString(T(-1)) + "}" );

    oss.str( "" );
    oss.clear();

    Utility::toStream( oss, std::complex<T>(-1, -1) );
    
    BOOST_CHECK_EQUAL( oss.str(),
                       std::string("{") + Utility::toString(T(-1)) + ", " +
                       Utility::toString(T(-1)) + "}" );

    oss.str( "" );
    oss.clear();

    Utility::toStream( oss, std::complex<T>(-2, -2) );
    
    BOOST_CHECK_EQUAL( oss.str(),
                       std::string("{") + Utility::toString(T(-2)) + ", " +
                       Utility::toString(T(-2)) + "}" );
  }  
}

//---------------------------------------------------------------------------//
// Check that boost::units::quantity types can be placed in a stream
BOOST_AUTO_TEST_CASE_TEMPLATE( quantity_toString,
                               QuantityType,
                               TestBasicQuantityTypes )
{
  typedef typename Utility::QuantityTraits<QuantityType>::UnitType UnitType;
  typedef typename Utility::QuantityTraits<QuantityType>::RawType RawType;

  // Basic quantity types
  BOOST_CHECK_EQUAL( Utility::toString(QuantityType::from_value( RawType(0) )),
                     Utility::toString(RawType(0)) + " " +
                     Utility::UnitTraits<UnitType>::symbol() );
  BOOST_CHECK_EQUAL( Utility::toString(QuantityType::from_value( RawType(1) )),
                     Utility::toString(RawType(1)) + " " +
                     Utility::UnitTraits<UnitType>::symbol() );
  BOOST_CHECK_EQUAL( Utility::toString(QuantityType::from_value( RawType(2) )),
                     Utility::toString(RawType(2)) + " " +
                     Utility::UnitTraits<UnitType>::symbol() );

  // Complex quantity types
  typedef std::complex<RawType> ComplexRawType;
  typedef boost::units::quantity<UnitType,ComplexRawType> ComplexQuantityType;

  BOOST_CHECK_EQUAL( Utility::toString(ComplexQuantityType::from_value( ComplexRawType(0, 0) )),
                     Utility::toString(ComplexRawType(0, 0)) + " " +
                     Utility::UnitTraits<UnitType>::symbol() );
  BOOST_CHECK_EQUAL( Utility::toString(ComplexQuantityType::from_value( ComplexRawType(1, 0) )),
                     Utility::toString(ComplexRawType(1, 0)) + " " +
                     Utility::UnitTraits<UnitType>::symbol() );
  BOOST_CHECK_EQUAL( Utility::toString(ComplexQuantityType::from_value( ComplexRawType(0, 1) )),
                     Utility::toString(ComplexRawType(0, 1)) + " " +
                     Utility::UnitTraits<UnitType>::symbol() );
  BOOST_CHECK_EQUAL( Utility::toString(ComplexQuantityType::from_value( ComplexRawType(1, 1) )),
                     Utility::toString(ComplexRawType(1, 1)) + " " +
                     Utility::UnitTraits<UnitType>::symbol() );
  BOOST_CHECK_EQUAL( Utility::toString(ComplexQuantityType::from_value( ComplexRawType(2, 2) )),
                     Utility::toString(ComplexRawType(2, 2)) + " " +
                     Utility::UnitTraits<UnitType>::symbol() );

  if( Utility::QuantityTraits<QuantityType>::is_signed::value )
  {
    // Basic quantity types
    BOOST_CHECK_EQUAL( Utility::toString(QuantityType::from_value( RawType(-1) )),
                       Utility::toString(RawType(-1)) + " " +
                       Utility::UnitTraits<UnitType>::symbol() );
    BOOST_CHECK_EQUAL( Utility::toString(QuantityType::from_value( RawType(-2) )),
                       Utility::toString(RawType(-2)) + " " +
                       Utility::UnitTraits<UnitType>::symbol() );
    
    // Complex quantity types
    BOOST_CHECK_EQUAL( Utility::toString(ComplexQuantityType::from_value( ComplexRawType(-1, 0) )),
                       Utility::toString(ComplexRawType(-1, 0)) + " " +
                       Utility::UnitTraits<UnitType>::symbol() );
    BOOST_CHECK_EQUAL( Utility::toString(ComplexQuantityType::from_value( ComplexRawType(0, -1) )),
                       Utility::toString(ComplexRawType(0, -1)) + " " +
                       Utility::UnitTraits<UnitType>::symbol() );
    BOOST_CHECK_EQUAL( Utility::toString(ComplexQuantityType::from_value( ComplexRawType(-1, -1) )),
                       Utility::toString(ComplexRawType(-1, -1)) + " " +
                       Utility::UnitTraits<UnitType>::symbol() );
    BOOST_CHECK_EQUAL( Utility::toString(ComplexQuantityType::from_value( ComplexRawType(-2, -2) )),
                       Utility::toString(ComplexRawType(-2, -2)) + " " +
                       Utility::UnitTraits<UnitType>::symbol() );
  }
}

//---------------------------------------------------------------------------//
// Check that boost::units::quantity types can be placed in a stream
BOOST_AUTO_TEST_CASE_TEMPLATE( quantity_toStream,
                               QuantityType,
                               TestBasicQuantityTypes )
{
  typedef typename Utility::QuantityTraits<QuantityType>::UnitType UnitType;
  typedef typename Utility::QuantityTraits<QuantityType>::RawType RawType;
  
  std::ostringstream oss;

  // Basic quantity types
  Utility::toStream( oss, QuantityType::from_value( RawType(0) ) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                     Utility::toString(RawType(0)) + " " +
                     Utility::UnitTraits<UnitType>::symbol() );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, QuantityType::from_value( RawType(1) ) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                     Utility::toString(RawType(1)) + " " +
                     Utility::UnitTraits<UnitType>::symbol() );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, QuantityType::from_value( RawType(2) ) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                     Utility::toString(RawType(2)) + " " +
                     Utility::UnitTraits<UnitType>::symbol() );

  oss.str( "" );
  oss.clear();

  // Complex quantity types
  typedef std::complex<RawType> ComplexRawType;
  typedef boost::units::quantity<UnitType,ComplexRawType> ComplexQuantityType;

  Utility::toStream( oss, ComplexQuantityType::from_value( ComplexRawType(0, 0) ) );

  BOOST_CHECK_EQUAL( oss.str(),
                     Utility::toString(ComplexRawType(0, 0)) + " " +
                     Utility::UnitTraits<UnitType>::symbol() );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, ComplexQuantityType::from_value( ComplexRawType(1, 0) ) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                     Utility::toString(ComplexRawType(1, 0)) + " " +
                     Utility::UnitTraits<UnitType>::symbol() );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, ComplexQuantityType::from_value( ComplexRawType(0, 1) ) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                     Utility::toString(ComplexRawType(0, 1)) + " " +
                     Utility::UnitTraits<UnitType>::symbol() );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, ComplexQuantityType::from_value( ComplexRawType(1, 1) ) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                     Utility::toString(ComplexRawType(1, 1)) + " " +
                     Utility::UnitTraits<UnitType>::symbol() );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, ComplexQuantityType::from_value( ComplexRawType(2, 2) ) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                     Utility::toString(ComplexRawType(2, 2)) + " " +
                     Utility::UnitTraits<UnitType>::symbol() );

  if( Utility::QuantityTraits<QuantityType>::is_signed::value )
  {
    oss.str( "" );
    oss.clear();

    // Basic quantity types
    Utility::toStream( oss, QuantityType::from_value( RawType(-1) ) );
    
    BOOST_CHECK_EQUAL( oss.str(),
                       Utility::toString(RawType(-1)) + " " +
                       Utility::UnitTraits<UnitType>::symbol() );

    oss.str( "" );
    oss.clear();

    Utility::toStream( oss, QuantityType::from_value( RawType(-2) ) );
    
    BOOST_CHECK_EQUAL( oss.str(),
                       Utility::toString(RawType(-2)) + " " +
                       Utility::UnitTraits<UnitType>::symbol() );

    oss.str( "" );
    oss.clear();
    
    // Complex quantity types
    Utility::toStream( oss, ComplexQuantityType::from_value( ComplexRawType(-1, 0) ) );
    
    BOOST_CHECK_EQUAL( oss.str(),
                       Utility::toString(ComplexRawType(-1, 0)) + " " +
                       Utility::UnitTraits<UnitType>::symbol() );

    oss.str( "" );
    oss.clear();

    Utility::toStream( oss, ComplexQuantityType::from_value( ComplexRawType(0, -1) ) );
    
    BOOST_CHECK_EQUAL( oss.str(),
                       Utility::toString(ComplexRawType(0, -1)) + " " +
                       Utility::UnitTraits<UnitType>::symbol() );

    oss.str( "" );
    oss.clear();

    Utility::toStream( oss, ComplexQuantityType::from_value( ComplexRawType(-1, -1) ) );
    
    BOOST_CHECK_EQUAL( oss.str(),
                       Utility::toString(ComplexRawType(-1, -1)) + " " +
                       Utility::UnitTraits<UnitType>::symbol() );

    oss.str( "" );
    oss.clear();

    Utility::toStream( oss, ComplexQuantityType::from_value( ComplexRawType(-2, -2) ) );
    
    BOOST_CHECK_EQUAL( oss.str(),
                       Utility::toString(ComplexRawType(-2, -2)) + " " +
                       Utility::UnitTraits<UnitType>::symbol() );
  }
}

//---------------------------------------------------------------------------//
// Check that an initializer list can be converted to a string
BOOST_AUTO_TEST_CASE_TEMPLATE( initializer_list_toString,
                               T,
                               ComplexTestTypes )
{
  BOOST_CHECK_EQUAL( Utility::toString( {} ), std::string("{}") );

  BOOST_CHECK_EQUAL( Utility::toString( {T(0)} ),
                     std::string("{") + Utility::toString(T(0)) +
                     std::string("}") );

  BOOST_CHECK_EQUAL( Utility::toString( {T(0),T(1)} ),
                     std::string("{") + Utility::toString(T(0)) + ", " +
                     Utility::toString(T(1)) + "}" );
  
  BOOST_CHECK_EQUAL( Utility::toString( {T(0),T(1),T(2)} ),
                     std::string("{") + Utility::toString(T(0)) + ", " +
                     Utility::toString(T(1)) + ", " +
                     Utility::toString(T(2)) + "}" );
}

//---------------------------------------------------------------------------//
// Check that an initializer list can be placed in a stream
BOOST_AUTO_TEST_CASE_TEMPLATE( initializer_list_toStream,
                               T,
                               ComplexTestTypes )
{
  std::ostringstream oss;

  Utility::toStream( oss, {} );
  
  BOOST_CHECK_EQUAL( oss.str(), std::string("{}") );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, {T(0)} );

  BOOST_CHECK_EQUAL( oss.str(),
                     std::string("{") + Utility::toString(T(0)) +
                     std::string("}") );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, {T(0),T(1)} );

  BOOST_CHECK_EQUAL( oss.str(),
                     std::string("{") + Utility::toString(T(0)) + ", " +
                     Utility::toString(T(1)) + "}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, {T(0),T(1),T(2)} );
  
  BOOST_CHECK_EQUAL( oss.str(),
                     std::string("{") + Utility::toString(T(0)) + ", " +
                     Utility::toString(T(1)) + ", " +
                     Utility::toString(T(2)) + "}" );
}

//---------------------------------------------------------------------------//
// end tstToStringTraits.cpp
//---------------------------------------------------------------------------//
