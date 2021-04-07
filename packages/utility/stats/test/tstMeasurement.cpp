//---------------------------------------------------------------------------//
//!
//! \file   tstMeasurement.cpp
//! \author Alex Robinson
//! \brief  Measurement unit test
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// Boost Includes
#include <boost/units/io.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/systems/si.hpp>
#include <boost/units/cmath.hpp>
#include <boost/units/static_rational.hpp>

// FRENSIE Includes
#include "Utility_Measurement.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//
typedef std::tuple<float,double> TestTypes;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a measurement can be constructed
FRENSIE_UNIT_TEST_TEMPLATE( Measurement, constructor, TestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  // The default constructor
  Utility::Measurement<T> measurement;

  FRENSIE_CHECK_EQUAL( measurement.getValue(), T(0) );
  FRENSIE_CHECK_EQUAL( measurement.getUncertainty(), T(0) );

  // Default uncertainty constructor
  measurement = Utility::Measurement<T>( T(1) );

  FRENSIE_CHECK_EQUAL( measurement.getValue(), T(1) );
  FRENSIE_CHECK_EQUAL( measurement.getUncertainty(), T(0) );

  // Full constructor
  measurement = Utility::Measurement<T>( T(1), T(1)/T(10) );

  FRENSIE_CHECK_EQUAL( measurement.getValue(), T(1) );
  FRENSIE_CHECK_EQUAL( measurement.getUncertainty(), T(1)/T(10) );

  // Copy constructor
  Utility::Measurement<T> measurement_2( measurement );

  FRENSIE_CHECK_EQUAL( measurement_2.getValue(), T(1) );
  FRENSIE_CHECK_EQUAL( measurement_2.getUncertainty(), T(1)/T(10) );
}

//---------------------------------------------------------------------------//
// Check that the relative uncertainty can be calculated
FRENSIE_UNIT_TEST_TEMPLATE( Measurement, getRelativeUncertainty, TestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  T tol;

  if( std::is_same<T,float>::value )
    tol = T(1e-6);
  else
    tol = T(1e-15);
  
  Utility::Measurement<T> measurement;

  FRENSIE_CHECK_EQUAL( measurement.getRelativeUncertainty(), T(0) );

  measurement = Utility::Measurement<T>( T(1) );

  FRENSIE_CHECK_EQUAL( measurement.getRelativeUncertainty(), T(0) );

  measurement = Utility::Measurement<T>( T(0.1), T(0.01) );

  FRENSIE_CHECK_FLOATING_EQUALITY( measurement.getRelativeUncertainty(), T(0.1), tol );

  measurement = Utility::Measurement<T>( T(0), T(0.01) );

  FRENSIE_CHECK_EQUAL( measurement.getRelativeUncertainty(), T(0) );

  measurement = Utility::Measurement<T>( -T(1), T(0.01) );

  FRENSIE_CHECK_FLOATING_EQUALITY( measurement.getRelativeUncertainty(), T(0.01), tol );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the measurement can be calculated
FRENSIE_UNIT_TEST_TEMPLATE( Measurement, getLowerBound, TestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  Utility::Measurement<T> measurement( T(1), T(0.1) );

  FRENSIE_CHECK_EQUAL( measurement.getLowerBound(), T(0.9) );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the measurement can be calculated
FRENSIE_UNIT_TEST_TEMPLATE( Measurement, getUpperBound, TestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  Utility::Measurement<T> measurement( T(1), T(0.1) );

  FRENSIE_CHECK_EQUAL( measurement.getUpperBound(), T(1.1) );
}

//---------------------------------------------------------------------------//
// Check measurement addition
FRENSIE_UNIT_TEST_TEMPLATE( Measurement, addition, TestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  Utility::Measurement<T> measurement( T(1), T(0.1) );

  T tol;

  if( std::is_same<T,float>::value )
    tol = T(1e-6);
  else
    tol = T(1e-15);

  // Addition of measurement and scalar
  Utility::Measurement<T> new_measurement = measurement + T(1);

  FRENSIE_CHECK_EQUAL( new_measurement.getValue(), T(2.0) );
  FRENSIE_CHECK_EQUAL( new_measurement.getUncertainty(), T(0.1) );

  new_measurement = measurement + -T(1);

  FRENSIE_CHECK_EQUAL( new_measurement.getValue(), T(0) );
  FRENSIE_CHECK_EQUAL( new_measurement.getUncertainty(), T(0.1) );

  // Addition of scalar and measurement
  new_measurement = T(2.0) + measurement;

  FRENSIE_CHECK_EQUAL( new_measurement.getValue(), T(3.0) );
  FRENSIE_CHECK_EQUAL( new_measurement.getUncertainty(), T(0.1) );

  new_measurement = -T(2.0) + measurement;

  FRENSIE_CHECK_EQUAL( new_measurement.getValue(), -T(1) );
  FRENSIE_CHECK_EQUAL( new_measurement.getUncertainty(), T(0.1) );

  // Addition of two measurements
  new_measurement = measurement + Utility::Measurement<T>( T(1), T(0) );

  FRENSIE_CHECK_EQUAL( new_measurement.getValue(), T(2.0) );
  FRENSIE_CHECK_EQUAL( new_measurement.getUncertainty(), T(0.1) );

  new_measurement = measurement + Utility::Measurement<T>( -T(1), T(0) );

  FRENSIE_CHECK_EQUAL( new_measurement.getValue(), T(0) );
  FRENSIE_CHECK_EQUAL( new_measurement.getUncertainty(), T(0.1) );

  // In-place addition of measurement and scalar
  measurement += T(1);

  FRENSIE_CHECK_EQUAL( measurement.getValue(), T(2.0) );
  FRENSIE_CHECK_EQUAL( measurement.getUncertainty(), T(0.1) );

  measurement = Utility::Measurement<T>( T(1), T(0.1) );
  measurement += -T(1);

  FRENSIE_CHECK_EQUAL( measurement.getValue(), T(0) );
  FRENSIE_CHECK_EQUAL( measurement.getUncertainty(), T(0.1) );

  // In-place addition of measurement and another measurement
  measurement = Utility::Measurement<T>( T(1), T(0.1) );
  measurement += Utility::Measurement<T>( T(2.0), T(0.3) );

  FRENSIE_CHECK_EQUAL( measurement.getValue(), T(3.0) );
  FRENSIE_CHECK_FLOATING_EQUALITY( measurement.getUncertainty(),
                                   sqrt( T(0.1*0.1)+T(0.3*0.3) ),
                                   tol );

  measurement = Utility::Measurement<T>( T(1), T(0.1) );
  measurement += Utility::Measurement<T>( T(-2.0), T(0.3) );

  FRENSIE_CHECK_EQUAL( measurement.getValue(), -T(1) );
  FRENSIE_CHECK_FLOATING_EQUALITY( measurement.getUncertainty(),
                                   sqrt( T(0.1*0.1)+T(0.3*0.3) ),
                                   tol );
}

//---------------------------------------------------------------------------//
// Check measurement subtraction
FRENSIE_UNIT_TEST_TEMPLATE( Measurement, subtraction, TestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  Utility::Measurement<T> measurement( T(1), T(0.1) );

  T tol;

  if( std::is_same<T,float>::value )
    tol = T(1e-6);
  else
    tol = T(1e-15);

  // Subtraction of measurement to scaler
  Utility::Measurement<T> new_measurement = measurement - T(1);

  FRENSIE_CHECK_EQUAL( new_measurement.getValue(), T(0) );
  FRENSIE_CHECK_EQUAL( new_measurement.getUncertainty(), T(0.1) );

  new_measurement = measurement - -T(1);

  FRENSIE_CHECK_EQUAL( new_measurement.getValue(), T(2.0) );
  FRENSIE_CHECK_EQUAL( new_measurement.getUncertainty(), T(0.1) );

  // Subtraction of scalar and measurement
  new_measurement = T(1) - measurement;

  FRENSIE_CHECK_EQUAL( new_measurement.getValue(), T(0) );
  FRENSIE_CHECK_EQUAL( new_measurement.getUncertainty(), T(0.1) );

  new_measurement = -T(1) - measurement;

  FRENSIE_CHECK_EQUAL( new_measurement.getValue(), -T(2.0) );
  FRENSIE_CHECK_EQUAL( new_measurement.getUncertainty(), T(0.1) );

  // Subtraction of two measurements
  new_measurement = measurement - Utility::Measurement<T>( T(1), T(0) );

  FRENSIE_CHECK_EQUAL( new_measurement.getValue(), T(0) );
  FRENSIE_CHECK_EQUAL( new_measurement.getUncertainty(), T(0.1) );

  new_measurement = measurement - Utility::Measurement<T>( -T(1), T(0) );

  FRENSIE_CHECK_EQUAL( new_measurement.getValue(), 2.0 );
  FRENSIE_CHECK_EQUAL( new_measurement.getUncertainty(), T(0.1) );

  // In-place subtraction of measurement and scalar
  measurement -= T(1);

  FRENSIE_CHECK_EQUAL( measurement.getValue(), T(0) );
  FRENSIE_CHECK_EQUAL( measurement.getUncertainty(), T(0.1) );

  measurement = Utility::Measurement<T>( T(1), T(0.1) );
  measurement -= -T(1);

  FRENSIE_CHECK_EQUAL( measurement.getValue(), 2.0 );
  FRENSIE_CHECK_EQUAL( measurement.getUncertainty(), T(0.1) );

  // In-place subtraction of measurement and another measurement
  measurement = Utility::Measurement<T>( T(1), 0.1 );
  measurement -= Utility::Measurement<T>( 2.0, 0.3 );

  FRENSIE_CHECK_EQUAL( measurement.getValue(), -T(1) );
  FRENSIE_CHECK_FLOATING_EQUALITY( measurement.getUncertainty(),
                                   sqrt( T(0.1*0.1) + T(0.3*0.3) ),
                                   tol );

  measurement = Utility::Measurement<T>( T(1), T(0.1) );
  measurement -= Utility::Measurement<T>( -T(2.0), T(0.3) );

  FRENSIE_CHECK_EQUAL( measurement.getValue(), T(3.0) );
  FRENSIE_CHECK_FLOATING_EQUALITY( measurement.getUncertainty(),
                                   sqrt( T(0.1*0.1) + T(0.3*0.3) ),
                                   tol );
}

//---------------------------------------------------------------------------//
// Check measurement multiplication
FRENSIE_UNIT_TEST_TEMPLATE( Measurement, multiplication, TestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  Utility::Measurement<T> measurement( T(1), T(0.1) );

  T tol;

  if( std::is_same<T,float>::value )
    tol = T(1e-6);
  else
    tol = T(1e-15);

  // Multiplication of measurement and scalar
  Utility::Measurement<T> new_measurement = measurement*T(2.0);

  FRENSIE_CHECK_EQUAL( new_measurement.getValue(), T(2.0) );
  FRENSIE_CHECK_EQUAL( new_measurement.getUncertainty(), T(0.2) );

  new_measurement = measurement*T(-2.0);

  FRENSIE_CHECK_EQUAL( new_measurement.getValue(), T(-2.0) );
  FRENSIE_CHECK_EQUAL( new_measurement.getUncertainty(), T(0.2) );

  // Multiplication of scalar and measurement
  new_measurement = T(2.0)*measurement;

  FRENSIE_CHECK_EQUAL( new_measurement.getValue(), T(2.0) );
  FRENSIE_CHECK_EQUAL( new_measurement.getUncertainty(), T(0.2) );

  new_measurement = T(-2.0)*measurement;

  FRENSIE_CHECK_EQUAL( new_measurement.getValue(), T(-2.0) );
  FRENSIE_CHECK_EQUAL( new_measurement.getUncertainty(), T(0.2) );

  // Multiplication of two measurements
  new_measurement = measurement*Utility::Measurement<T>( T(2.0), T(0) );

  FRENSIE_CHECK_EQUAL( new_measurement.getValue(), T(2.0) );
  FRENSIE_CHECK_EQUAL( new_measurement.getUncertainty(), T(0.2) );

  new_measurement = measurement*Utility::Measurement<T>( T(-2.0), T(0) );

  FRENSIE_CHECK_EQUAL( new_measurement.getValue(), T(-2.0) );
  FRENSIE_CHECK_EQUAL( new_measurement.getUncertainty(), T(0.2) );

  new_measurement = measurement*Utility::Measurement<T>( T(2.0), T(0.2) );

  FRENSIE_CHECK_EQUAL( new_measurement.getValue(), T(2.0) );
  FRENSIE_CHECK_FLOATING_EQUALITY( new_measurement.getUncertainty(),
                                   sqrt( T(0.1*0.1*2.0*2.0) + T(0.2*0.2) ),
                                   tol );
  
  new_measurement = measurement*Utility::Measurement<T>( T(-2.0), T(0.2) );

  FRENSIE_CHECK_EQUAL( new_measurement.getValue(), T(-2.0) );
  FRENSIE_CHECK_FLOATING_EQUALITY( new_measurement.getUncertainty(),
                                   sqrt( T(0.1*0.1*2.0*2.0) + T(0.2*0.2) ),
                                   tol );

  // In-place multiplication of measurement and scalar
  measurement *= T(2.0);

  FRENSIE_CHECK_EQUAL( measurement.getValue(), T(2.0) );
  FRENSIE_CHECK_EQUAL( measurement.getUncertainty(), T(0.2) );

  measurement = Utility::Measurement<T>( T(1), T(0.1) );
  measurement *= T(-2.0);

  FRENSIE_CHECK_EQUAL( measurement.getValue(), T(-2.0) );
  FRENSIE_CHECK_EQUAL( measurement.getUncertainty(), T(0.2) );

  // In-place multiplication of measurement and another measurement
  measurement = Utility::Measurement<T>( T(1), T(0.1) );
  measurement *= Utility::Measurement<T>( T(2.0), T(0) );

  FRENSIE_CHECK_EQUAL( measurement.getValue(), T(2.0) );
  FRENSIE_CHECK_EQUAL( measurement.getUncertainty(), T(0.2) );

  measurement = Utility::Measurement<T>( T(1), T(0.1) );
  measurement *= Utility::Measurement<T>( T(-2.0), T(0) );

  FRENSIE_CHECK_EQUAL( measurement.getValue(), T(-2.0) );
  FRENSIE_CHECK_EQUAL( measurement.getUncertainty(), T(0.2) );

  measurement = Utility::Measurement<T>( T(1), T(0.1) );
  measurement *= Utility::Measurement<T>( T(2.0), T(0.2) );

  FRENSIE_CHECK_EQUAL( measurement.getValue(), T(2.0) );
  FRENSIE_CHECK_FLOATING_EQUALITY( measurement.getUncertainty(),
                                   sqrt( T(0.1*0.1*2.0*2.0) + T(0.2*0.2) ),
                                   tol );

  measurement = Utility::Measurement<T>( T(1), T(0.1) );
  measurement *= Utility::Measurement<T>( T(-2.0), T(0.2) );

  FRENSIE_CHECK_EQUAL( measurement.getValue(), T(-2.0) );
  FRENSIE_CHECK_FLOATING_EQUALITY( measurement.getUncertainty(),
                                   sqrt( T(0.1*0.1*2.0*2.0) + T(0.2*0.2) ),
                                   tol );
}

//---------------------------------------------------------------------------//
// Check measurement division
FRENSIE_UNIT_TEST_TEMPLATE( Measurement, division, TestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  Utility::Measurement<T> measurement( T(1), T(0.1) );

  T tol;

  if( std::is_same<T,float>::value )
    tol = T(1e-6);
  else
    tol = T(1e-15);

  // Division of measurement and scalar
  Utility::Measurement<T> new_measurement = measurement/T(2.0);

  FRENSIE_CHECK_EQUAL( new_measurement.getValue(), T(0.5) );
  FRENSIE_CHECK_EQUAL( new_measurement.getUncertainty(), T(0.05) );

  new_measurement = measurement/T(-2.0);

  FRENSIE_CHECK_EQUAL( new_measurement.getValue(), T(-0.5) );
  FRENSIE_CHECK_EQUAL( new_measurement.getUncertainty(), T(0.05) );

  // Division of scalar and measurement
  new_measurement = T(2.0)/measurement;

  FRENSIE_CHECK_EQUAL( new_measurement.getValue(), T(2.0) );
  FRENSIE_CHECK_EQUAL( new_measurement.getUncertainty(), T(0.2) );

  new_measurement = -T(2.0)/measurement;

  FRENSIE_CHECK_EQUAL( new_measurement.getValue(), T(-2.0) );
  FRENSIE_CHECK_EQUAL( new_measurement.getUncertainty(), T(0.2) );

  // Division of two measurements
  new_measurement = measurement/Utility::Measurement<T>( T(2), T(0) );

  FRENSIE_CHECK_EQUAL( new_measurement.getValue(), T(0.5) );
  FRENSIE_CHECK_EQUAL( new_measurement.getUncertainty(), T(0.05) );

  new_measurement = measurement/Utility::Measurement<T>( -T(2), T(0) );

  FRENSIE_CHECK_EQUAL( new_measurement.getValue(), T(-0.5) );
  FRENSIE_CHECK_EQUAL( new_measurement.getUncertainty(), T(0.05) );

  new_measurement = measurement/Utility::Measurement<T>( T(2), T(0.2) );

  FRENSIE_CHECK_EQUAL( new_measurement.getValue(), T(0.5) );
  FRENSIE_CHECK_FLOATING_EQUALITY( new_measurement.getUncertainty(),
                                   sqrt( T(0.1*0.1/4.0) + T(0.2*0.2/16.0) ),
                                   tol );

  new_measurement = measurement/Utility::Measurement<T>( -T(2), T(0.2) );

  FRENSIE_CHECK_EQUAL( new_measurement.getValue(), T(-0.5) );
  FRENSIE_CHECK_FLOATING_EQUALITY( new_measurement.getUncertainty(),
                                   sqrt( T(0.1*0.1/4.0) + T(0.2*0.2/16.0) ),
                                   tol );

  // In-place division of measurement and scalar
  measurement /= T(2);

  FRENSIE_CHECK_EQUAL( measurement.getValue(), T(0.5) );
  FRENSIE_CHECK_EQUAL( measurement.getUncertainty(), T(0.05) );

  measurement = Utility::Measurement<T>( T(1), T(0.1) );
  measurement /= -T(2);

  FRENSIE_CHECK_EQUAL( measurement.getValue(), T(-0.5) );
  FRENSIE_CHECK_EQUAL( measurement.getUncertainty(), T(0.05) );

  // In-place division of measurement and another measurement
  measurement = Utility::Measurement<T>( T(1), T(0.1) );
  measurement /= Utility::Measurement<T>( T(2), T(0) );

  FRENSIE_CHECK_EQUAL( measurement.getValue(), T(0.5) );
  FRENSIE_CHECK_EQUAL( measurement.getUncertainty(), T(0.05) );

  measurement = Utility::Measurement<T>( T(1), T(0.1) );
  measurement /= Utility::Measurement<T>( -T(2), T(0) );

  FRENSIE_CHECK_EQUAL( measurement.getValue(), T(-0.5) );
  FRENSIE_CHECK_EQUAL( measurement.getUncertainty(), T(0.05) );

  measurement = Utility::Measurement<T>( T(1), T(0.1) );
  measurement /= Utility::Measurement<T>( T(2), T(0.2) );

  FRENSIE_CHECK_EQUAL( measurement.getValue(), T(0.5) );
  FRENSIE_CHECK_FLOATING_EQUALITY( measurement.getUncertainty(),
                                   sqrt( T(0.1*0.1/4.0) + T(0.2*0.2/16.0) ),
                                   tol );

  measurement = Utility::Measurement<T>( T(1), T(0.1) );
  measurement /= Utility::Measurement<T>( -T(2), T(0.2) );

  FRENSIE_CHECK_EQUAL( measurement.getValue(), T(-0.5) );
  FRENSIE_CHECK_FLOATING_EQUALITY( measurement.getUncertainty(),
                                   sqrt( T(0.1*0.1/4.0) + T(0.2*0.2/16.0) ),
                                   tol );
}

//---------------------------------------------------------------------------//
// Check that a measurement can be converted to a string
FRENSIE_UNIT_TEST_TEMPLATE( Measurement, toString, TestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  Utility::Measurement<T> measurement( T(2), T(0.1) );

  std::string measurement_string = Utility::toString( measurement );

  FRENSIE_CHECK_EQUAL( measurement_string,
                       Utility::toString( measurement.getValue() ) + " +/- " +
                       Utility::toString( measurement.getUncertainty() ) );
}

//---------------------------------------------------------------------------//
// Check that a measurement can be placed in a stream
FRENSIE_UNIT_TEST_TEMPLATE( Measurement, toStream, TestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  Utility::Measurement<T> measurement( T(2), T(0.1) );

  std::ostringstream oss;

  Utility::toStream( oss, measurement );

  FRENSIE_CHECK_EQUAL( oss.str(),
                       Utility::toString( measurement.getValue() ) + " +/- " +
                       Utility::toString( measurement.getUncertainty() ) );
}

//---------------------------------------------------------------------------//
// Check that a measurement can be placed in a stream
FRENSIE_UNIT_TEST_TEMPLATE( Measurement, ostream_operator, TestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  Utility::Measurement<T> measurement( T(2), T(0.1) );

  std::ostringstream oss;

  oss << measurement;

  FRENSIE_CHECK_EQUAL( oss.str(),
                       Utility::toString( measurement.getValue() ) + " +/- " +
                       Utility::toString( measurement.getUncertainty() ) );
}

//---------------------------------------------------------------------------//
// Check measurement sqrt
FRENSIE_UNIT_TEST_TEMPLATE( Measurement, sqrt_std, TestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  Utility::Measurement<T> measurement( T(2), T(0.1) );

  T tol;

  if( std::is_same<T,float>::value )
    tol = T(1e-6);
  else
    tol = T(1e-15);

  // Std namespace sqrt
  Utility::Measurement<T> new_measurement = std::sqrt( measurement );

  FRENSIE_CHECK_FLOATING_EQUALITY( new_measurement.getValue(),
                                   sqrt( T(2) ),
                                   tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( new_measurement.getUncertainty(),
                                   T(0.1)/(2*sqrt(T(2))),
                                   tol );

  // Default sqrt (should be the same as the std namespace sqrt)
  new_measurement = sqrt( measurement );

  FRENSIE_CHECK_FLOATING_EQUALITY( new_measurement.getValue(),
                                   sqrt( T(2) ),
                                   tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( new_measurement.getUncertainty(),
                                   T(0.1)/(2*sqrt(T(2))),
                                   tol );
}

//---------------------------------------------------------------------------//
// Check measurement sqrt
FRENSIE_UNIT_TEST_TEMPLATE( Measurement, sqrt, TestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  Utility::Measurement<T> measurement( T(2), T(0.1) );

  T tol;

  if( std::is_same<T,float>::value )
    tol = T(1e-6);
  else
    tol = T(1e-15);

  Utility::Measurement<T> new_measurement = Utility::sqrt( measurement );

  FRENSIE_CHECK_FLOATING_EQUALITY( new_measurement.getValue(),
                                   sqrt( T(2) ),
                                   tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( new_measurement.getUncertainty(),
                                   T(0.1)/(2*sqrt(T(2))),
                                   tol );
}

//---------------------------------------------------------------------------//
// Check quantity measurement sqrt
FRENSIE_UNIT_TEST_TEMPLATE( Measurement, sqrt_quantity, TestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  namespace si = boost::units::si;
  using boost::units::quantity;

  quantity<si::area,Utility::Measurement<T> > area_measurement(
		   Utility::Measurement<T>( T(2), 0.1 )*si::square_meter );

  T tol;

  if( std::is_same<T,float>::value )
    tol = T(1e-6);
  else
    tol = T(1e-15);

  quantity<si::length,Utility::Measurement<T> > length_measurement =
    Utility::sqrt( area_measurement );

  FRENSIE_CHECK_FLOATING_EQUALITY( length_measurement.value().getValue(),
                                   sqrt( T(2) ),
                                   tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( length_measurement.value().getUncertainty(),
                                   T(0.1)/(2*sqrt(T(2))),
                                   tol );
}

//---------------------------------------------------------------------------//
// Check measurement cbrt
FRENSIE_UNIT_TEST_TEMPLATE( Measurement, cbrt_std, TestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  Utility::Measurement<T> measurement( T(2), 0.1 );

  T tol;

  if( std::is_same<T,float>::value )
    tol = T(1e-6);
  else
    tol = T(1e-15);

  // Std namespace cbrt
  Utility::Measurement<T> new_measurement = std::cbrt( measurement );

  FRENSIE_CHECK_FLOATING_EQUALITY( new_measurement.getValue(),
                                   cbrt( T(2) ),
                                   tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( new_measurement.getUncertainty(),
                                   T(0.1)/(3*pow(T(2), T(2.0/3))),
                                   tol );

  // Default sqrt (should be the same as the std namespace sqrt)
  new_measurement = cbrt( measurement );

  FRENSIE_CHECK_FLOATING_EQUALITY( new_measurement.getValue(),
                                   cbrt( T(2) ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( new_measurement.getUncertainty(),
                                   0.1/(3*pow(T(2), 2.0/3)),
                                   tol );
}

//---------------------------------------------------------------------------//
// Check measurement cbrt
FRENSIE_UNIT_TEST_TEMPLATE( Measurement, cbrt, TestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  Utility::Measurement<T> measurement( T(2), 0.1 );

  T tol;

  if( std::is_same<T,float>::value )
    tol = T(1e-6);
  else
    tol = T(1e-15);

  Utility::Measurement<T> new_measurement = Utility::cbrt( measurement );

  FRENSIE_CHECK_FLOATING_EQUALITY( new_measurement.getValue(),
                                   cbrt( T(2) ),
                                   tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( new_measurement.getUncertainty(),
                                   T(0.1)/(3*pow(T(2), T(2.0/3))),
                                   tol );
}

//---------------------------------------------------------------------------//
// Check quantity measurement cbrt
FRENSIE_UNIT_TEST_TEMPLATE( Measurement, cbrt_quantity, TestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  namespace si = boost::units::si;
  using boost::units::quantity;

  quantity<si::volume,Utility::Measurement<T> > volume_measurement(
		   Utility::Measurement<T>( T(2), 0.1 )*si::cubic_meter );

  T tol;

  if( std::is_same<T,float>::value )
    tol = T(1e-6);
  else
    tol = T(1e-15);

  quantity<si::length,Utility::Measurement<T> > length_measurement =
    Utility::cbrt( volume_measurement );

  FRENSIE_CHECK_FLOATING_EQUALITY( length_measurement.value().getValue(),
                                   cbrt( T(2) ),
                                   tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( length_measurement.value().getUncertainty(),
                                   T(0.1)/(3*pow(T(2), T(2.0/3))),
                                   tol );
}

//---------------------------------------------------------------------------//
// Check measurement pow
FRENSIE_UNIT_TEST_TEMPLATE( Measurement, pow_std, TestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  Utility::Measurement<T> measurement( T(2), 0.1 );

  T tol;

  if( std::is_same<T,float>::value )
    tol = T(1e-6);
  else
    tol = T(1e-15);

  // Std namespace pow
  Utility::Measurement<T> new_measurement = std::pow( measurement, 1.5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( new_measurement.getValue(),
                                   pow( T(2), T(1.5) ),
                                   tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( new_measurement.getUncertainty(),
                                   T(1.5*0.1)*pow( T(2), T(0.5) ),
                                   tol );

  // Default pow (should be the same as the std namespace pow)
  new_measurement = pow( measurement, T(0.5) );

  FRENSIE_CHECK_FLOATING_EQUALITY( new_measurement.getValue(),
                                   sqrt( T(2) ),
                                   tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( new_measurement.getUncertainty(),
                                   T(0.1)/(2*sqrt(T(2))),
                                   tol );

  new_measurement = pow( measurement, T(-0.5) );

  FRENSIE_CHECK_FLOATING_EQUALITY( new_measurement.getValue(),
                                   pow( T(2), T(-0.5) ),
                                   tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( new_measurement.getUncertainty(),
                                   T(0.5*0.1)*pow( T(2), T(-1.5) ),
                                   tol );
}

//---------------------------------------------------------------------------//
// Check measurement rpow
FRENSIE_UNIT_TEST_TEMPLATE( Measurement, rpow, TestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  Utility::Measurement<T> measurement( T(2), 0.1 );

  T tol;

  if( std::is_same<T,float>::value )
    tol = T(1e-6);
  else
    tol = T(1e-15);

  Utility::Measurement<T> new_measurement =
    Utility::rpow<3,2>( measurement );

  FRENSIE_CHECK_FLOATING_EQUALITY( new_measurement.getValue(),
                                   pow( T(2), T(1.5) ),
                                   tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( new_measurement.getUncertainty(),
                                   T(1.5*0.1)*pow( T(2), T(0.5) ),
                                   tol );

  new_measurement = Utility::rpow<1,2>( measurement );

  FRENSIE_CHECK_FLOATING_EQUALITY( new_measurement.getValue(),
                                   sqrt( T(2) ),
                                   tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( new_measurement.getUncertainty(),
                                   T(0.1)/(2*sqrt(T(2))),
                                   tol );

  new_measurement = Utility::rpow<-1,2>( measurement );

  FRENSIE_CHECK_FLOATING_EQUALITY( new_measurement.getValue(),
                                   pow( T(2), T(-0.5) ),
                                   tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( new_measurement.getUncertainty(),
                                   T(0.5*0.1)*pow( T(2), T(-1.5) ),
                                   tol );

  new_measurement = Utility::rpow<1,-2>( measurement );

  FRENSIE_CHECK_FLOATING_EQUALITY( new_measurement.getValue(),
                                   pow( T(2), T(-0.5) ),
                                   tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( new_measurement.getUncertainty(),
                                   T(0.5*0.1)*pow( T(2), T(-1.5) ),
                                   tol );
}

//---------------------------------------------------------------------------//
// Check quantity measurement rpow
FRENSIE_UNIT_TEST_TEMPLATE( Measurement, rpow_quantity, TestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  namespace si = boost::units::si;
  using boost::units::quantity;

  quantity<si::volume,Utility::Measurement<T> > volume_measurement(
		   Utility::Measurement<T>( T(2), 0.1 )*si::cubic_meter );

  T tol;

  if( std::is_same<T,float>::value )
    tol = T(1e-6);
  else
    tol = T(1e-15);

  quantity<si::length,Utility::Measurement<T> > length_measurement =
    Utility::rpow<1,3>( volume_measurement );

  FRENSIE_CHECK_FLOATING_EQUALITY( length_measurement.value().getValue(),
                                   cbrt( T(2) ),
                                   tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( length_measurement.value().getUncertainty(),
                                   T(0.1)/(3*pow(T(2), T(2.0/3))),
                                   tol );

  // Reverse the operation
  volume_measurement = Utility::rpow<3,1>( length_measurement );

  FRENSIE_CHECK_FLOATING_EQUALITY( volume_measurement.value().getValue(),
                                   T(2),
                                   tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( volume_measurement.value().getUncertainty(),
                                   0.1,
                                   tol );
}

//---------------------------------------------------------------------------//
// end tstMeasurement.cpp
//---------------------------------------------------------------------------//
