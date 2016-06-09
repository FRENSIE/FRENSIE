//---------------------------------------------------------------------------//
//!
//! \file   tstMeasurement.cpp
//! \author Alex Robinson
//! \brief  Measurement unit test
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/units/io.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/systems/si.hpp>
#include <boost/units/cmath.hpp>
#include <boost/units/static_rational.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_Measurement.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a measurement can be constructed
TEUCHOS_UNIT_TEST( Measurement, constructor )
{
  // The default constructor
  Utility::Measurement<double> measurement;

  TEST_EQUALITY_CONST( measurement.getValue(), 0.0 );
  TEST_EQUALITY_CONST( measurement.getUncertainty(), 0.0 );

  // Default uncertainty constructor
  measurement = Utility::Measurement<double>( 1.0 );

  TEST_EQUALITY_CONST( measurement.getValue(), 1.0 );
  TEST_EQUALITY_CONST( measurement.getUncertainty(), 0.0 );

  // Full constructor
  measurement = Utility::Measurement<double>( 1.0, 0.1 );

  TEST_EQUALITY_CONST( measurement.getValue(), 1.0 );
  TEST_EQUALITY_CONST( measurement.getUncertainty(), 0.1 );

  // Copy constructor
  Utility::Measurement<double> measurement_2( measurement );

  TEST_EQUALITY_CONST( measurement_2.getValue(), 1.0 );
  TEST_EQUALITY_CONST( measurement_2.getUncertainty(), 0.1 );
}

//---------------------------------------------------------------------------//
// Check that the relative uncertainty can be calculated
TEUCHOS_UNIT_TEST( Measurement, getRelativeUncertainty )
{
  Utility::Measurement<double> measurement;

  TEST_EQUALITY_CONST( measurement.getRelativeUncertainty(), 0.0 );

  measurement = Utility::Measurement<double>( 1.0 );

  TEST_EQUALITY_CONST( measurement.getRelativeUncertainty(), 0.0 );

  measurement = Utility::Measurement<double>( 0.1, 0.01 );

  TEST_FLOATING_EQUALITY( measurement.getRelativeUncertainty(), 0.1, 1e-15 );

  measurement = Utility::Measurement<double>( 0.0, 0.01 );

  TEST_EQUALITY_CONST( measurement.getRelativeUncertainty(), 0.0 );

  measurement = Utility::Measurement<double>( -1.0, 0.01 );

  TEST_FLOATING_EQUALITY( measurement.getRelativeUncertainty(), 0.01, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the measurement can be calculated
TEUCHOS_UNIT_TEST( Measurement, getLowerBound )
{
  Utility::Measurement<double> measurement( 1.0, 0.1 );

  TEST_EQUALITY_CONST( measurement.getLowerBound(), 0.9 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the measurement can be calculated
TEUCHOS_UNIT_TEST( Measurement, getUpperBound )
{
  Utility::Measurement<double> measurement( 1.0, 0.1 );

  TEST_EQUALITY_CONST( measurement.getUpperBound(), 1.1 );
}

//---------------------------------------------------------------------------//
// Check that a measurement can be converted to double
TEUCHOS_UNIT_TEST( Measurement, implicit_conversion )
{
  double value = Utility::Measurement<double>( 2.0, 0.1 );

  TEST_EQUALITY_CONST( value, 2.0 );

  float reduced_precision_value = Utility::Measurement<float>( 2.0f, 0.1f );

  TEST_EQUALITY_CONST( reduced_precision_value, 2.0f );
}

//---------------------------------------------------------------------------//
// Check measurement addition
TEUCHOS_UNIT_TEST( Measurement, addition )
{
  Utility::Measurement<double> measurement( 1.0, 0.1 );

  // Addition of measurement and scalar
  Utility::Measurement<double> new_measurement = measurement + 1.0;

  TEST_EQUALITY_CONST( new_measurement.getValue(), 2.0 );
  TEST_EQUALITY_CONST( new_measurement.getUncertainty(), 0.1 );

  new_measurement = measurement + -1.0;

  TEST_EQUALITY_CONST( new_measurement.getValue(), 0.0 );
  TEST_EQUALITY_CONST( new_measurement.getUncertainty(), 0.1 );

  // Addition of scalar and measurement
  new_measurement = 2.0 + measurement;

  TEST_EQUALITY_CONST( new_measurement.getValue(), 3.0 );
  TEST_EQUALITY_CONST( new_measurement.getUncertainty(), 0.1 );

  new_measurement = -2.0 + measurement;

  TEST_EQUALITY_CONST( new_measurement.getValue(), -1.0 );
  TEST_EQUALITY_CONST( new_measurement.getUncertainty(), 0.1 );

  // Addition of two measurements
  new_measurement = measurement + Utility::Measurement<double>( 1.0, 0.0 );

  TEST_EQUALITY_CONST( new_measurement.getValue(), 2.0 );
  TEST_EQUALITY_CONST( new_measurement.getUncertainty(), 0.1 );

  new_measurement = measurement + Utility::Measurement<double>( -1.0, 0.0 );

  TEST_EQUALITY_CONST( new_measurement.getValue(), 0.0 );
  TEST_EQUALITY_CONST( new_measurement.getUncertainty(), 0.1 );

  // In-place addition of measurement and scalar
  measurement += 1.0;

  TEST_EQUALITY_CONST( measurement.getValue(), 2.0 );
  TEST_EQUALITY_CONST( measurement.getUncertainty(), 0.1 );

  measurement = Utility::Measurement<double>( 1.0, 0.1 );
  measurement += -1.0;

  TEST_EQUALITY_CONST( measurement.getValue(), 0.0 );
  TEST_EQUALITY_CONST( measurement.getUncertainty(), 0.1 );

  // In-place addition of measurement and another measurement
  measurement = Utility::Measurement<double>( 1.0, 0.1 );
  measurement += Utility::Measurement<double>( 2.0, 0.3 );

  TEST_EQUALITY_CONST( measurement.getValue(), 3.0 );
  TEST_FLOATING_EQUALITY( measurement.getUncertainty(),
			  sqrt( 0.1*0.1+0.3*0.3 ),
			  1e-15 );

  measurement = Utility::Measurement<double>( 1.0, 0.1 );
  measurement += Utility::Measurement<double>( -2.0, 0.3 );

  TEST_EQUALITY_CONST( measurement.getValue(), -1.0 );
  TEST_FLOATING_EQUALITY( measurement.getUncertainty(),
			  sqrt( 0.1*0.1+0.3*0.3 ),
			  1e-15 );
}

//---------------------------------------------------------------------------//
// Check measurement subtraction
TEUCHOS_UNIT_TEST( Measurement, subtraction )
{
  Utility::Measurement<double> measurement( 1.0, 0.1 );

  // Subtraction of measurement to scaler
  Utility::Measurement<double> new_measurement = measurement - 1.0;

  TEST_EQUALITY_CONST( new_measurement.getValue(), 0.0 );
  TEST_EQUALITY_CONST( new_measurement.getUncertainty(), 0.1 );

  new_measurement = measurement - -1.0;

  TEST_EQUALITY_CONST( new_measurement.getValue(), 2.0 );
  TEST_EQUALITY_CONST( new_measurement.getUncertainty(), 0.1 );

  // Subtraction of scalar and measurement
  new_measurement = 1.0 - measurement;

  TEST_EQUALITY_CONST( new_measurement.getValue(), 0.0 );
  TEST_EQUALITY_CONST( new_measurement.getUncertainty(), 0.1 );

  new_measurement = -1.0 - measurement;

  TEST_EQUALITY_CONST( new_measurement.getValue(), -2.0 );
  TEST_EQUALITY_CONST( new_measurement.getUncertainty(), 0.1 );

  // Subtraction of two measurements
  new_measurement = measurement - Utility::Measurement<double>( 1.0, 0.0 );

  TEST_EQUALITY_CONST( new_measurement.getValue(), 0.0 );
  TEST_EQUALITY_CONST( new_measurement.getUncertainty(), 0.1 );

  new_measurement = measurement - Utility::Measurement<double>( -1.0, 0.0 );

  TEST_EQUALITY_CONST( new_measurement.getValue(), 2.0 );
  TEST_EQUALITY_CONST( new_measurement.getUncertainty(), 0.1 );

  // In-place subtraction of measurement and scalar
  measurement -= 1.0;

  TEST_EQUALITY_CONST( measurement.getValue(), 0.0 );
  TEST_EQUALITY_CONST( measurement.getUncertainty(), 0.1 );

  measurement = Utility::Measurement<double>( 1.0, 0.1 );
  measurement -= -1.0;

  TEST_EQUALITY_CONST( measurement.getValue(), 2.0 );
  TEST_EQUALITY_CONST( measurement.getUncertainty(), 0.1 );

  // In-place subtraction of measurement and another measurement
  measurement = Utility::Measurement<double>( 1.0, 0.1 );
  measurement -= Utility::Measurement<double>( 2.0, 0.3 );

  TEST_EQUALITY_CONST( measurement.getValue(), -1.0 );
  TEST_FLOATING_EQUALITY( measurement.getUncertainty(),
			  sqrt( 0.1*0.1 + 0.3*0.3 ),
			  1e-15 );

  measurement = Utility::Measurement<double>( 1.0, 0.1 );
  measurement -= Utility::Measurement<double>( -2.0, 0.3 );

  TEST_EQUALITY_CONST( measurement.getValue(), 3.0 );
  TEST_FLOATING_EQUALITY( measurement.getUncertainty(),
			  sqrt( 0.1*0.1 + 0.3*0.3 ),
			  1e-15 );
}

//---------------------------------------------------------------------------//
// Check measurement multiplication
TEUCHOS_UNIT_TEST( Measurement, multiplication )
{
  Utility::Measurement<double> measurement( 1.0, 0.1 );

  // Multiplication of measurement and scalar
  Utility::Measurement<double> new_measurement = measurement*2.0;

  TEST_EQUALITY_CONST( new_measurement.getValue(), 2.0 );
  TEST_EQUALITY_CONST( new_measurement.getUncertainty(), 0.2 );

  new_measurement = measurement*-2.0;

  TEST_EQUALITY_CONST( new_measurement.getValue(), -2.0 );
  TEST_EQUALITY_CONST( new_measurement.getUncertainty(), 0.2 );

  // Multiplication of scalar and measurement
  new_measurement = 2.0*measurement;

  TEST_EQUALITY_CONST( new_measurement.getValue(), 2.0 );
  TEST_EQUALITY_CONST( new_measurement.getUncertainty(), 0.2 );

  new_measurement = -2.0*measurement;

  TEST_EQUALITY_CONST( new_measurement.getValue(), -2.0 );
  TEST_EQUALITY_CONST( new_measurement.getUncertainty(), 0.2 );

  // Multiplication of two measurements
  new_measurement = measurement*Utility::Measurement<double>( 2.0, 0.0 );

  TEST_EQUALITY_CONST( new_measurement.getValue(), 2.0 );
  TEST_EQUALITY_CONST( new_measurement.getUncertainty(), 0.2 );

  new_measurement = measurement*Utility::Measurement<double>( -2.0, 0.0 );

  TEST_EQUALITY_CONST( new_measurement.getValue(), -2.0 );
  TEST_EQUALITY_CONST( new_measurement.getUncertainty(), 0.2 );

  new_measurement = measurement*Utility::Measurement<double>( 2.0, 0.2 );

  TEST_EQUALITY_CONST( new_measurement.getValue(), 2.0 );
  TEST_FLOATING_EQUALITY( new_measurement.getUncertainty(),
			  sqrt( 0.1*0.1*2.0*2.0 + 0.2*0.2 ),
			  1e-15 );

  new_measurement = measurement*Utility::Measurement<double>( -2.0, 0.2 );

  TEST_EQUALITY_CONST( new_measurement.getValue(), -2.0 );
  TEST_FLOATING_EQUALITY( new_measurement.getUncertainty(),
			  sqrt( 0.1*0.1*2.0*2.0 + 0.2*0.2 ),
			  1e-15 );

  // In-place multiplication of measurement and scalar
  measurement *= 2.0;

  TEST_EQUALITY_CONST( measurement.getValue(), 2.0 );
  TEST_EQUALITY_CONST( measurement.getUncertainty(), 0.2 );

  measurement = Utility::Measurement<double>( 1.0, 0.1 );
  measurement *= -2.0;

  TEST_EQUALITY_CONST( measurement.getValue(), -2.0 );
  TEST_EQUALITY_CONST( measurement.getUncertainty(), 0.2 );

  // In-place multiplication of measurement and another measurement
  measurement = Utility::Measurement<double>( 1.0, 0.1 );
  measurement *= Utility::Measurement<double>( 2.0, 0.0 );

  TEST_EQUALITY_CONST( measurement.getValue(), 2.0 );
  TEST_EQUALITY_CONST( measurement.getUncertainty(), 0.2 );

  measurement = Utility::Measurement<double>( 1.0, 0.1 );
  measurement *= Utility::Measurement<double>( -2.0, 0.0 );

  TEST_EQUALITY_CONST( measurement.getValue(), -2.0 );
  TEST_EQUALITY_CONST( measurement.getUncertainty(), 0.2 );

  measurement = Utility::Measurement<double>( 1.0, 0.1 );
  measurement *= Utility::Measurement<double>( 2.0, 0.2 );

  TEST_EQUALITY_CONST( measurement.getValue(), 2.0 );
  TEST_FLOATING_EQUALITY( measurement.getUncertainty(),
			  sqrt( 0.1*0.1*2.0*2.0 + 0.2*0.2 ),
			  1e-15 );

  measurement = Utility::Measurement<double>( 1.0, 0.1 );
  measurement *= Utility::Measurement<double>( -2.0, 0.2 );

  TEST_EQUALITY_CONST( measurement.getValue(), -2.0 );
  TEST_FLOATING_EQUALITY( measurement.getUncertainty(),
			  sqrt( 0.1*0.1*2.0*2.0 + 0.2*0.2 ),
			  1e-15 );
}

//---------------------------------------------------------------------------//
// Check measurement division
TEUCHOS_UNIT_TEST( Measurement, division )
{
  Utility::Measurement<double> measurement( 1.0, 0.1 );

  // Division of measurement and scalar
  Utility::Measurement<double> new_measurement = measurement/2.0;

  TEST_EQUALITY_CONST( new_measurement.getValue(), 0.5 );
  TEST_EQUALITY_CONST( new_measurement.getUncertainty(), 0.05 );

  new_measurement = measurement/-2.0;

  TEST_EQUALITY_CONST( new_measurement.getValue(), -0.5 );
  TEST_EQUALITY_CONST( new_measurement.getUncertainty(), 0.05 );

  // Division of scalar and measurement
  new_measurement = 2.0/measurement;

  TEST_EQUALITY_CONST( new_measurement.getValue(), 2.0 );
  TEST_EQUALITY_CONST( new_measurement.getUncertainty(), 0.2 );

  new_measurement = -2.0/measurement;

  TEST_EQUALITY_CONST( new_measurement.getValue(), -2.0 );
  TEST_EQUALITY_CONST( new_measurement.getUncertainty(), 0.2 );

  // Division of two measurements
  new_measurement = measurement/Utility::Measurement<double>( 2.0, 0.0 );

  TEST_EQUALITY_CONST( new_measurement.getValue(), 0.5 );
  TEST_EQUALITY_CONST( new_measurement.getUncertainty(), 0.05 );

  new_measurement = measurement/Utility::Measurement<double>( -2.0, 0.0 );

  TEST_EQUALITY_CONST( new_measurement.getValue(), -0.5 );
  TEST_EQUALITY_CONST( new_measurement.getUncertainty(), 0.05 );

  new_measurement = measurement/Utility::Measurement<double>( 2.0, 0.2 );

  TEST_EQUALITY_CONST( new_measurement.getValue(), 0.5 );
  TEST_FLOATING_EQUALITY( new_measurement.getUncertainty(),
			  sqrt( 0.1*0.1/4.0 + 0.2*0.2/16.0 ),
			  1e-15 );

  new_measurement = measurement/Utility::Measurement<double>( -2.0, 0.2 );

  TEST_EQUALITY_CONST( new_measurement.getValue(), -0.5 );
  TEST_FLOATING_EQUALITY( new_measurement.getUncertainty(),
			  sqrt( 0.1*0.1/4.0 + 0.2*0.2/16.0 ),
			  1e-15 );

  // In-place division of measurement and scalar
  measurement /= 2.0;

  TEST_EQUALITY_CONST( measurement.getValue(), 0.5 );
  TEST_EQUALITY_CONST( measurement.getUncertainty(), 0.05 );

  measurement = Utility::Measurement<double>( 1.0, 0.1 );
  measurement /= -2.0;

  TEST_EQUALITY_CONST( measurement.getValue(), -0.5 );
  TEST_EQUALITY_CONST( measurement.getUncertainty(), 0.05 );

  // In-place division of measurement and another measurement
  measurement = Utility::Measurement<double>( 1.0, 0.1 );
  measurement /= Utility::Measurement<double>( 2.0, 0.0 );

  TEST_EQUALITY_CONST( measurement.getValue(), 0.5 );
  TEST_EQUALITY_CONST( measurement.getUncertainty(), 0.05 );

  measurement = Utility::Measurement<double>( 1.0, 0.1 );
  measurement /= Utility::Measurement<double>( -2.0, 0.0 );

  TEST_EQUALITY_CONST( measurement.getValue(), -0.5 );
  TEST_EQUALITY_CONST( measurement.getUncertainty(), 0.05 );

  measurement = Utility::Measurement<double>( 1.0, 0.1 );
  measurement /= Utility::Measurement<double>( 2.0, 0.2 );

  TEST_EQUALITY_CONST( measurement.getValue(), 0.5 );
  TEST_FLOATING_EQUALITY( measurement.getUncertainty(),
			  sqrt( 0.1*0.1/4.0 + 0.2*0.2/16.0 ),
			  1e-15 );

  measurement = Utility::Measurement<double>( 1.0, 0.1 );
  measurement /= Utility::Measurement<double>( -2.0, 0.2 );

  TEST_EQUALITY_CONST( measurement.getValue(), -0.5 );
  TEST_FLOATING_EQUALITY( measurement.getUncertainty(),
			  sqrt( 0.1*0.1/4.0 + 0.2*0.2/16.0 ),
			  1e-15 );
}

//---------------------------------------------------------------------------//
// Check measurement sqrt
TEUCHOS_UNIT_TEST( Measurement, sqrt )
{
  Utility::Measurement<double> measurement( 2.0, 0.1 );

  Utility::Measurement<double> new_measurement = sqrt( measurement );

  TEST_FLOATING_EQUALITY( new_measurement.getValue(),
			  sqrt( 2.0 ),
			  1e-15 );
  TEST_FLOATING_EQUALITY( new_measurement.getUncertainty(),
			  0.1/(2*sqrt(2.0)),
			  1e-15 );
}

//---------------------------------------------------------------------------//
// Check measurement pow
TEUCHOS_UNIT_TEST( Measurement, pow )
{
  Utility::Measurement<double> measurement( 2.0, 0.1 );

  Utility::Measurement<double> new_measurement = pow( measurement, 1.5 );

  TEST_FLOATING_EQUALITY( new_measurement.getValue(),
			  pow( 2.0, 1.5 ),
			  1e-15 );
  TEST_FLOATING_EQUALITY( new_measurement.getUncertainty(),
			  1.5*0.1*pow( 2.0, 0.5 ),
			  1e-15 );

  new_measurement = pow( measurement, 0.5 );

  TEST_FLOATING_EQUALITY( new_measurement.getValue(),
			  sqrt( 2.0 ),
			  1e-15 );
  TEST_FLOATING_EQUALITY( new_measurement.getUncertainty(),
			  0.1/(2*sqrt(2.0)),
			  1e-15 );

  new_measurement = pow( measurement, -0.5 );

  TEST_FLOATING_EQUALITY( new_measurement.getValue(),
			  pow( 2.0, -0.5 ),
			  1e-15 );
  TEST_FLOATING_EQUALITY( new_measurement.getUncertainty(),
			  0.5*0.1*pow( 2.0, -1.5 ),
			  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the root of a quantity can be calculated
TEUCHOS_UNIT_TEST( Measurement, quantity_sqrt )
{
  namespace si = boost::units::si;
  using boost::units::quantity;

  quantity<si::area,Utility::Measurement<double> > area_measurement(
			  Utility::Measurement<double>( 2.0, 0.1 )*si::square_meter );

  quantity<si::length,Utility::Measurement<double> > length_measurement =
    sqrt( area_measurement );

  TEST_FLOATING_EQUALITY( length_measurement.value().getValue(),
			  sqrt( 2.0 ),
			  1e-15 );
  TEST_FLOATING_EQUALITY( length_measurement.value().getUncertainty(),
			  0.1/(2*sqrt(2.0)),
			  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a quantity raised to a rational power can be calculated
TEUCHOS_UNIT_TEST( Measurement, quantity_pow )
{
  namespace si = boost::units::si;
  using boost::units::quantity;
  using boost::units::static_rational;
  using boost::units::pow;

  typedef boost::units::power_typeof_helper<quantity<si::length,Utility::Measurement<double> >,static_rational<3,2> >::type QuantityTypeA;

  typedef boost::units::power_typeof_helper<quantity<si::length,Utility::Measurement<double> >,static_rational<1,2> >::type QuantityTypeB;

  typedef boost::units::power_typeof_helper<quantity<si::length,Utility::Measurement<double> >,static_rational<-1,2> >::type QuantityTypeC;

  quantity<si::length,Utility::Measurement<double> > measurement(
			  Utility::Measurement<double>( 2.0, 0.1 )*si::meter );

  QuantityTypeA new_measurement_a =
    pow<static_rational<3,2> >( measurement );

  TEST_FLOATING_EQUALITY( new_measurement_a.value().getValue(),
			  std::pow( 2.0, 1.5 ),
			  1e-15 );
  TEST_FLOATING_EQUALITY( new_measurement_a.value().getUncertainty(),
			  1.5*0.1*std::pow( 2.0, 0.5 ),
			  1e-15 );

  QuantityTypeB new_measurement_b =
    pow<static_rational<1,2> >( measurement );

  TEST_FLOATING_EQUALITY( new_measurement_b.value().getValue(),
  			  sqrt( 2.0 ),
  			  1e-15 );
  TEST_FLOATING_EQUALITY( new_measurement_b.value().getUncertainty(),
  			  0.1/(2*sqrt(2.0)),
  			  1e-15 );

  QuantityTypeC new_measurement_c =
    pow<static_rational<-1,2> >( measurement );

  TEST_FLOATING_EQUALITY( new_measurement_c.value().getValue(),
  			  std::pow( 2.0, -0.5 ),
  			  1e-15 );
  TEST_FLOATING_EQUALITY( new_measurement_c.value().getUncertainty(),
  			  0.5*0.1*std::pow( 2.0, -1.5 ),
  			  1e-15 );
}

//---------------------------------------------------------------------------//
// end tstMeasurement.cpp
//---------------------------------------------------------------------------//
