//---------------------------------------------------------------------------//
//!
//! \file   tstStandardFormFactor.cpp
//! \author Alex Robinson
//! \brief  The standard form factor unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Include
#include <iostream>
#include <limits>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_ComptonProfile.hpp"
#include "MonteCarlo_StandardFormFactor.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_InverseAngstromUnit.hpp"
#include "Utility_InverseCentimeterUnit.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<const MonteCarlo::FormFactor> form_factor;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the form factor squared can be evaluated
FRENSIE_UNIT_TEST( StandardFormFactor, evaluate )
{
  MonteCarlo::FormFactor::ArgumentQuantity
    arg( 0.0*Utility::Units::inverse_centimeter );

  double value = form_factor->evaluate( arg );

  FRENSIE_CHECK_EQUAL( value, 1.0 );

  arg = 1e17*Utility::Units::inverse_centimeter;
  value = form_factor->evaluate( arg );

  FRENSIE_CHECK_FLOATING_EQUALITY( value, 0.0, 1e-15 );

  arg = 1e18*Utility::Units::inverse_centimeter;
  value = form_factor->evaluate( arg );

  FRENSIE_CHECK_FLOATING_EQUALITY( value, 0.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the max form factor squared value can be returned
FRENSIE_UNIT_TEST( StandardFormFactor, getMaxValue )
{
  FRENSIE_CHECK_EQUAL( form_factor->getMaxValue(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the min form factor squared value can be returned
FRENSIE_UNIT_TEST( StandardFormFactor, getMinValue )
{
  FRENSIE_CHECK_EQUAL( form_factor->getMinValue(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the squared argument can be returned
FRENSIE_UNIT_TEST( StandardFormFactor, getLowerBoundOfArgument )
{
  FRENSIE_CHECK_FLOATING_EQUALITY(
			 form_factor->getLowerBoundOfArgument(),
			 0.0*Utility::Units::inverse_centimeter,
			 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the squared argument can be returned
FRENSIE_UNIT_TEST( StandardFormFactor, getUpperBoundOfArgument )
{
  FRENSIE_CHECK_FLOATING_EQUALITY(
			 form_factor->getUpperBoundOfArgument(),
			 1e17*Utility::Units::inverse_centimeter,
			 1e-15 );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create the form factor
  {
    std::vector<double> args( 3 ), form_factor_vals( 3 );
    args[0] = 0.0;
    args[1] = 10.0;
    args[2] = 1e9;

    form_factor_vals[0] = 1.0;
    form_factor_vals[1] = 0.001;
    form_factor_vals[2] = 0.0;

    std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<Utility::Units::InverseAngstrom,void> >
      raw_form_factor( new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::InverseAngstrom,void>( args, form_factor_vals ) );

    form_factor.reset( new MonteCarlo::StandardFormFactor<Utility::Units::InverseAngstrom>( raw_form_factor ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstStandardFormFactor.cpp
//---------------------------------------------------------------------------//
