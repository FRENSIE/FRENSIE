//---------------------------------------------------------------------------//
//!
//! \file   tstStandardScatteringFunction.cpp
//! \author Alex Robinson
//! \brief  The standard scattering function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_ComptonProfile.hpp"
#include "MonteCarlo_StandardScatteringFunction.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_InverseAngstromUnit.hpp"
#include "Utility_InverseCentimeterUnit.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<const MonteCarlo::ScatteringFunction> scattering_function;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the scattering function can be evaluated
FRENSIE_UNIT_TEST( StandardScatteringFunction, evaluate )
{
  MonteCarlo::ScatteringFunction::ArgumentQuantity
    arg( -1.0*Utility::Units::inverse_centimeter );

  double value = scattering_function->evaluate( arg );

  FRENSIE_CHECK_EQUAL( value, 0.0 );

  arg = 0.0*Utility::Units::inverse_centimeter;

  value = scattering_function->evaluate( arg );

  FRENSIE_CHECK_EQUAL( value, 0.0 );

  arg = 1e9*Utility::Units::inverse_centimeter;

  value = scattering_function->evaluate( arg );

  FRENSIE_CHECK_EQUAL( value, 1e-3 );

  arg = 1e17*Utility::Units::inverse_centimeter;

  value = scattering_function->evaluate( arg );

  FRENSIE_CHECK_EQUAL( value, 1.0 );

  arg = 1e18*Utility::Units::inverse_centimeter;

  value = scattering_function->evaluate( arg );

  FRENSIE_CHECK_EQUAL( value, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the max scattering function value can be returned
FRENSIE_UNIT_TEST( StandardScatteringFunction, getMaxValue )
{
  FRENSIE_CHECK_EQUAL( scattering_function->getMaxValue(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the min scattering function value can be returned
FRENSIE_UNIT_TEST( StandardScatteringFunction, getMinValue )
{
  FRENSIE_CHECK_EQUAL( scattering_function->getMinValue(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the min scattering function value can be returned
FRENSIE_UNIT_TEST( StandardScatteringFunction, getLowerBoundOfArgument )
{
  FRENSIE_CHECK_EQUAL( scattering_function->getLowerBoundOfArgument(),
		       0.0*Utility::Units::inverse_centimeter );
}

//---------------------------------------------------------------------------//
// Check that the max scattering function value can be returned
FRENSIE_UNIT_TEST( StandardScatteringFunction, getUpperBoundOfArgument )
{
  FRENSIE_CHECK_EQUAL( scattering_function->getUpperBoundOfArgument(),
		       1e17*Utility::Units::inverse_centimeter );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create the scattering function
  {
    std::vector<double> args( 3 ), scattering_func_vals( 3 );
    args[0] = 0.0;
    args[1] = 10.0;
    args[2] = 1e9;

    scattering_func_vals[0] = 0.0;
    scattering_func_vals[1] = 1e-3;
    scattering_func_vals[2] = 1.0;

    std::shared_ptr<Utility::UnitAwareUnivariateDistribution<Utility::Units::InverseAngstrom,void> >
      raw_scattering_function( new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::InverseAngstrom,void>( args, scattering_func_vals ) );

    scattering_function.reset( new MonteCarlo::StandardScatteringFunction<Utility::Units::InverseAngstrom>( raw_scattering_function ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstStandardScatteringFunction.cpp
//---------------------------------------------------------------------------//
