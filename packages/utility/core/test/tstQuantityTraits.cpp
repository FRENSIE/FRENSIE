//---------------------------------------------------------------------------//
//!
//! \file   tstQuantityTraits.cpp
//! \author Alex Robinson
//! \brief  Quantity traits unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <string>
#include <type_traits>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>
#include <boost/units/systems/cgs/energy.hpp>
#include <boost/units/systems/si/energy.hpp>

// FRENSIE Includes
#include "Utility_QuantityTraits.hpp"
#include "Utility_ElectronVoltUnit.hpp"

using namespace Utility::Units;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//
typedef boost::mpl::list<int, unsigned long, float, double> TestTypes;

//---------------------------------------------------------------------------//
// Check that UnitType is defined
BOOST_AUTO_TEST_CASE_TEMPLATE( UnitType, T, TestTypes )
{
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<T>::UnitType,void>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<std::complex<T> >::UnitType,void>::value) );
  
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::UnitType,cgs::energy>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::UnitType,si::energy>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::UnitType,ElectronVolt>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,T> >::UnitType,KiloElectronVolt>::value) );

  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::UnitType,cgs::energy>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::UnitType,si::energy>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::UnitType,ElectronVolt>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,std::complex<T> > >::UnitType,KiloElectronVolt>::value) );
}

//---------------------------------------------------------------------------//
// Check that RawType is defined
BOOST_AUTO_TEST_CASE_TEMPLATE( RawType, T, TestTypes )
{
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<T>::RawType,T>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<std::complex<T> >::RawType,std::complex<T> >::value) );
  
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::RawType,T>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::RawType,T>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::RawType,T>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,T> >::RawType,T>::value) );

  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::RawType,std::complex<T> >::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::RawType,std::complex<T> >::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::RawType,std::complex<T> >::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,std::complex<T> > >::RawType,std::complex<T> >::value) );
}

//---------------------------------------------------------------------------//
// Check that QuantityType is defined
BOOST_AUTO_TEST_CASE_TEMPLATE( QuantityType, T, TestTypes )
{
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<T>::QuantityType,T>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<std::complex<T> >::QuantityType,std::complex<T> >::value) );

  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::QuantityType,boost::units::quantity<cgs::energy,T> >::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::QuantityType,boost::units::quantity<si::energy,T> >::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::QuantityType,boost::units::quantity<ElectronVolt,T> >::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,T> >::QuantityType,boost::units::quantity<KiloElectronVolt,T> >::value) );

  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::QuantityType,boost::units::quantity<cgs::energy,std::complex<T> > >::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::QuantityType,boost::units::quantity<si::energy,std::complex<T> > >::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::QuantityType,boost::units::quantity<ElectronVolt,std::complex<T> > >::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,std::complex<T> > >::QuantityType,boost::units::quantity<KiloElectronVolt,std::complex<T> > >::value) );
}

//---------------------------------------------------------------------------//
// Check that the QuantityTraits struct has been specialized for the type
BOOST_AUTO_TEST_CASE_TEMPLATE( is_specialized, T, TestTypes )
{
  BOOST_CHECK( Utility::QuantityTraits<T>::is_specialized::value );
  BOOST_CHECK( Utility::QuantityTraits<std::complex<T> >::is_specialized::value );
  
  BOOST_CHECK( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::is_specialized::value) );
  BOOST_CHECK( (Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::is_specialized::value) );
  BOOST_CHECK( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::is_specialized::value) );
  BOOST_CHECK( (Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,T> >::is_specialized::value) );

  BOOST_CHECK( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::is_specialized::value) );
  BOOST_CHECK( (Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::is_specialized::value) );
  BOOST_CHECK( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::is_specialized::value) );
  BOOST_CHECK( (Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,std::complex<T> > >::is_specialized::value) );
}

//---------------------------------------------------------------------------//
// Check if the type is signed
BOOST_AUTO_TEST_CASE_TEMPLATE( is_signed, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::is_signed::value,
                     std::is_signed<T>::value );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::is_signed::value,
                     std::is_signed<T>::value );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::is_signed::value),
                     std::is_signed<T>::value );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::is_signed::value),
                     std::is_signed<T>::value );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::is_signed::value),
                     std::is_signed<T>::value );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,T> >::is_signed::value),
                     std::is_signed<T>::value );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::is_signed::value),
                     std::is_signed<T>::value );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::is_signed::value),
                     std::is_signed<T>::value );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::is_signed::value),
                     std::is_signed<T>::value );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,std::complex<T> > >::is_signed::value),
                     std::is_signed<T>::value );
}

//---------------------------------------------------------------------------//
// Check if the type is an integer
BOOST_AUTO_TEST_CASE_TEMPLATE( is_integer, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::is_integer::value,
                     std::is_integral<T>::value );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::is_integer::value,
                     std::is_integral<T>::value );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::is_integer::value),
                     std::is_integral<T>::value );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::is_integer::value),
                     std::is_integral<T>::value );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::is_integer::value),
                     std::is_integral<T>::value );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,T> >::is_integer::value),
                     std::is_integral<T>::value );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::is_integer::value),
                     std::is_integral<T>::value );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::is_integer::value),
                     std::is_integral<T>::value );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::is_integer::value),
                     std::is_integral<T>::value );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,std::complex<T> > >::is_integer::value),
                     std::is_integral<T>::value );
}

//---------------------------------------------------------------------------//
// Check if the type is complex
BOOST_AUTO_TEST_CASE_TEMPLATE( is_complex, T, TestTypes )
{
  BOOST_CHECK( !Utility::QuantityTraits<T>::is_complex::value );
  BOOST_CHECK( Utility::QuantityTraits<std::complex<T> >::is_complex::value );

  BOOST_CHECK( !(Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::is_complex::value) );
  BOOST_CHECK( !(Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::is_complex::value) );
  BOOST_CHECK( !(Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::is_complex::value) );
  BOOST_CHECK( !(Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,T> >::is_complex::value) );

  BOOST_CHECK( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::is_complex::value) );
  BOOST_CHECK( (Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::is_complex::value) );
  BOOST_CHECK( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::is_complex::value) );
  BOOST_CHECK( (Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,std::complex<T> > >::is_complex::value) );
}

//---------------------------------------------------------------------------//
// Check if the type uses exact representations
BOOST_AUTO_TEST_CASE_TEMPLATE( is_exact, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::is_exact::value,
                     std::numeric_limits<T>::is_exact );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::is_exact::value,
                     std::numeric_limits<T>::is_exact );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::is_exact::value),
                     std::numeric_limits<T>::is_exact );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::is_exact::value),
                     std::numeric_limits<T>::is_exact );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::is_exact::value),
                     std::numeric_limits<T>::is_exact );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,T> >::is_exact::value),
                     std::numeric_limits<T>::is_exact );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::is_exact::value),
                     std::numeric_limits<T>::is_exact );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::is_exact::value),
                     std::numeric_limits<T>::is_exact );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::is_exact::value),
                     std::numeric_limits<T>::is_exact );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,std::complex<T> > >::is_exact::value),
                     std::numeric_limits<T>::is_exact );
}

//---------------------------------------------------------------------------//
// Check if the type has a representation for positive infinity
BOOST_AUTO_TEST_CASE_TEMPLATE( has_infinity, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::has_infinity::value,
                     std::numeric_limits<T>::has_infinity );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::has_infinity::value,
                     std::numeric_limits<T>::has_infinity );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::has_infinity::value),
                     std::numeric_limits<T>::has_infinity );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::has_infinity::value),
                     std::numeric_limits<T>::has_infinity );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::has_infinity::value),
                     std::numeric_limits<T>::has_infinity );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,T> >::has_infinity::value),
                     std::numeric_limits<T>::has_infinity );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::has_infinity::value),
                     std::numeric_limits<T>::has_infinity );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::has_infinity::value),
                     std::numeric_limits<T>::has_infinity );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::has_infinity::value),
                     std::numeric_limits<T>::has_infinity );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,std::complex<T> > >::has_infinity::value),
                     std::numeric_limits<T>::has_infinity );
}

//---------------------------------------------------------------------------//
// Check if the type has a representation for quiet nan
BOOST_AUTO_TEST_CASE_TEMPLATE( has_quiet_nan, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::has_quiet_nan::value,
                     std::numeric_limits<T>::has_quiet_NaN );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::has_quiet_nan::value,
                     std::numeric_limits<T>::has_quiet_NaN );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::has_quiet_nan::value),
                     std::numeric_limits<T>::has_quiet_NaN );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::has_quiet_nan::value),
                     std::numeric_limits<T>::has_quiet_NaN );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::has_quiet_nan::value),
                     std::numeric_limits<T>::has_quiet_NaN );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,T> >::has_quiet_nan::value),
                     std::numeric_limits<T>::has_quiet_NaN );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::has_quiet_nan::value),
                     std::numeric_limits<T>::has_quiet_NaN );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::has_quiet_nan::value),
                     std::numeric_limits<T>::has_quiet_NaN );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::has_quiet_nan::value),
                     std::numeric_limits<T>::has_quiet_NaN );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,std::complex<T> > >::has_quiet_nan::value),
                     std::numeric_limits<T>::has_quiet_NaN );  
}

//---------------------------------------------------------------------------//
// Check if the type has a representation for signaling nan
BOOST_AUTO_TEST_CASE_TEMPLATE( has_signaling_nan, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::has_signaling_nan::value,
                     std::numeric_limits<T>::has_signaling_NaN );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::has_signaling_nan::value,
                     std::numeric_limits<T>::has_signaling_NaN );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::has_signaling_nan::value),
                     std::numeric_limits<T>::has_signaling_NaN );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::has_signaling_nan::value),
                     std::numeric_limits<T>::has_signaling_NaN );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::has_signaling_nan::value),
                     std::numeric_limits<T>::has_signaling_NaN );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,T> >::has_signaling_nan::value),
                     std::numeric_limits<T>::has_signaling_NaN );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::has_signaling_nan::value),
                     std::numeric_limits<T>::has_signaling_NaN );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::has_signaling_nan::value),
                     std::numeric_limits<T>::has_signaling_NaN );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::has_signaling_nan::value),
                     std::numeric_limits<T>::has_signaling_NaN );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,std::complex<T> > >::has_signaling_nan::value),
                     std::numeric_limits<T>::has_signaling_NaN );
}

//---------------------------------------------------------------------------//
// Check if the type allows denormalizing values
BOOST_AUTO_TEST_CASE_TEMPLATE( has_denorm, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::has_denorm::value,
                     std::numeric_limits<T>::has_denorm );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::has_denorm::value,
                     std::numeric_limits<T>::has_denorm );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::has_denorm::value),
                     std::numeric_limits<T>::has_denorm );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::has_denorm::value),
                     std::numeric_limits<T>::has_denorm );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::has_denorm::value),
                     std::numeric_limits<T>::has_denorm );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,T> >::has_denorm::value),
                     std::numeric_limits<T>::has_denorm );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::has_denorm::value),
                     std::numeric_limits<T>::has_denorm );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::has_denorm::value),
                     std::numeric_limits<T>::has_denorm );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::has_denorm::value),
                     std::numeric_limits<T>::has_denorm );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,std::complex<T> > >::has_denorm::value),
                     std::numeric_limits<T>::has_denorm );
}

//---------------------------------------------------------------------------//
// Check if the type detects a loss of accuracy as a denormalization loss
// instead of an inexact result
BOOST_AUTO_TEST_CASE_TEMPLATE( has_denorm_loss, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::has_denorm_loss::value,
                     std::numeric_limits<T>::has_denorm_loss );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::has_denorm_loss::value,
                     std::numeric_limits<T>::has_denorm_loss );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::has_denorm_loss::value),
                     std::numeric_limits<T>::has_denorm_loss );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::has_denorm_loss::value),
                     std::numeric_limits<T>::has_denorm_loss );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::has_denorm_loss::value),
                     std::numeric_limits<T>::has_denorm_loss );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,T> >::has_denorm_loss::value),
                     std::numeric_limits<T>::has_denorm_loss );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::has_denorm_loss::value),
                     std::numeric_limits<T>::has_denorm_loss );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::has_denorm_loss::value),
                     std::numeric_limits<T>::has_denorm_loss );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::has_denorm_loss::value),
                     std::numeric_limits<T>::has_denorm_loss );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,std::complex<T> > >::has_denorm_loss::value),
                     std::numeric_limits<T>::has_denorm_loss );
}

//---------------------------------------------------------------------------//
// Check if the type adheres to the IEC-559/IEEE-754 standard
BOOST_AUTO_TEST_CASE_TEMPLATE( is_iec559, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::is_iec559::value,
                     std::numeric_limits<T>::is_iec559 );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::is_iec559::value,
                     std::numeric_limits<T>::is_iec559 );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::is_iec559::value),
                     std::numeric_limits<T>::is_iec559 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::is_iec559::value),
                     std::numeric_limits<T>::is_iec559 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::is_iec559::value),
                     std::numeric_limits<T>::is_iec559 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,T> >::is_iec559::value),
                     std::numeric_limits<T>::is_iec559 );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::is_iec559::value),
                     std::numeric_limits<T>::is_iec559 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::is_iec559::value),
                     std::numeric_limits<T>::is_iec559 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::is_iec559::value),
                     std::numeric_limits<T>::is_iec559 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,std::complex<T> > >::is_iec559::value),
                     std::numeric_limits<T>::is_iec559 );
}

//---------------------------------------------------------------------------//
// Check if the set of values that the type can represent is bounded
BOOST_AUTO_TEST_CASE_TEMPLATE( is_bounded, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::is_bounded::value,
                     std::numeric_limits<T>::is_bounded );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::is_bounded::value,
                     std::numeric_limits<T>::is_bounded );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::is_bounded::value),
                     std::numeric_limits<T>::is_bounded );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::is_bounded::value),
                     std::numeric_limits<T>::is_bounded );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::is_bounded::value),
                     std::numeric_limits<T>::is_bounded );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,T> >::is_bounded::value),
                     std::numeric_limits<T>::is_bounded );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::is_bounded::value),
                     std::numeric_limits<T>::is_bounded );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::is_bounded::value),
                     std::numeric_limits<T>::is_bounded );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::is_bounded::value),
                     std::numeric_limits<T>::is_bounded );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,std::complex<T> > >::is_bounded::value),
                     std::numeric_limits<T>::is_bounded );
}

//---------------------------------------------------------------------------//
// Check if the type is modulo
BOOST_AUTO_TEST_CASE_TEMPLATE( is_modulo, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::is_modulo::value,
                     std::numeric_limits<T>::is_modulo );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::is_modulo::value,
                     std::numeric_limits<T>::is_modulo );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::is_modulo::value),
                     std::numeric_limits<T>::is_modulo );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::is_modulo::value),
                     std::numeric_limits<T>::is_modulo );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::is_modulo::value),
                     std::numeric_limits<T>::is_modulo );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,T> >::is_modulo::value),
                     std::numeric_limits<T>::is_modulo );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::is_modulo::value),
                     std::numeric_limits<T>::is_modulo );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::is_modulo::value),
                     std::numeric_limits<T>::is_modulo );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::is_modulo::value),
                     std::numeric_limits<T>::is_modulo );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,std::complex<T> > >::is_modulo::value),
                     std::numeric_limits<T>::is_modulo );
}

//---------------------------------------------------------------------------//
// Check if trapping is implemented for the type
BOOST_AUTO_TEST_CASE_TEMPLATE( traps, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::traps::value,
                     std::numeric_limits<T>::traps );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::traps::value,
                     std::numeric_limits<T>::traps );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::traps::value),
                     std::numeric_limits<T>::traps );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::traps::value),
                     std::numeric_limits<T>::traps );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::traps::value),
                     std::numeric_limits<T>::traps );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,T> >::traps::value),
                     std::numeric_limits<T>::traps );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::traps::value),
                     std::numeric_limits<T>::traps );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::traps::value),
                     std::numeric_limits<T>::traps );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::traps::value),
                     std::numeric_limits<T>::traps );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,std::complex<T> > >::traps::value),
                     std::numeric_limits<T>::traps );
}

//---------------------------------------------------------------------------//
// Check if the type check the tinyness before rounding
BOOST_AUTO_TEST_CASE_TEMPLATE( tinyness_before, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::tinyness_before::value,
                     std::numeric_limits<T>::tinyness_before );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::tinyness_before::value,
                     std::numeric_limits<T>::tinyness_before );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::tinyness_before::value),
                     std::numeric_limits<T>::tinyness_before );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::tinyness_before::value),
                     std::numeric_limits<T>::tinyness_before );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::tinyness_before::value),
                     std::numeric_limits<T>::tinyness_before );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,T> >::tinyness_before::value),
                     std::numeric_limits<T>::tinyness_before );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::tinyness_before::value),
                     std::numeric_limits<T>::tinyness_before );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::tinyness_before::value),
                     std::numeric_limits<T>::tinyness_before );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::tinyness_before::value),
                     std::numeric_limits<T>::tinyness_before );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,std::complex<T> > >::tinyness_before::value),
                     std::numeric_limits<T>::tinyness_before );
}

//---------------------------------------------------------------------------//
// end tstQuantityTraits.cpp
//---------------------------------------------------------------------------//
