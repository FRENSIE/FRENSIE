//---------------------------------------------------------------------------//
//!
//! \file   tstStandardFormFactorSquared.cpp
//! \author Alex Robinson
//! \brief  The standard form factor squared unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Include
#include <iostream>
#include <limits>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_ComptonProfile.hpp"
#include "MonteCarlo_StandardFormFactorSquared.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_InverseSquareAngstromUnit.hpp"
#include "Utility_InverseSquareCentimeterUnit.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<const MonteCarlo::FormFactorSquared> form_factor_squared;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the form factor squared can be evaluated
FRENSIE_UNIT_TEST( StandardFormFactorSquared, evaluate )
{
  MonteCarlo::FormFactorSquared::SquaredArgumentQuantity
    sqr_arg( 0.0*Utility::Units::inverse_square_centimeter );

  double value = form_factor_squared->evaluate( sqr_arg );

  FRENSIE_CHECK_EQUAL( value, 1.0 );

  sqr_arg = 1e34*Utility::Units::inverse_square_centimeter;
  value = form_factor_squared->evaluate( sqr_arg );

  FRENSIE_CHECK_SMALL( value, 1e-15 );

  sqr_arg = 1e35*Utility::Units::inverse_square_centimeter;
  value = form_factor_squared->evaluate( sqr_arg );

  FRENSIE_CHECK_FLOATING_EQUALITY( value, 0.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the form factor squared can be sampled from
FRENSIE_UNIT_TEST( StandardFormFactorSquared, sample )
{
  MonteCarlo::FormFactorSquared::SquaredArgumentQuantity
    sqr_arg = form_factor_squared->sample();

  FRENSIE_CHECK( sqr_arg >= 0.0*Utility::Units::inverse_square_centimeter );
  FRENSIE_CHECK( sqr_arg <= 1e34*Utility::Units::inverse_square_centimeter );
}

//---------------------------------------------------------------------------//
// Check that the form factor squared can be sampled from
FRENSIE_UNIT_TEST( StandardFormFactorSquared, sampleInSubrange )
{
  MonteCarlo::FormFactorSquared::SquaredArgumentQuantity
    sqr_arg = form_factor_squared->sampleInSubrange( 1e10*Utility::Units::inverse_square_centimeter );

  FRENSIE_CHECK( sqr_arg >= 0.0*Utility::Units::inverse_square_centimeter );
  FRENSIE_CHECK( sqr_arg <= 1e10*Utility::Units::inverse_square_centimeter );
}

//---------------------------------------------------------------------------//
// Check that the max form factor squared value can be returned
FRENSIE_UNIT_TEST( StandardFormFactorSquared, getMaxValue )
{
  FRENSIE_CHECK_EQUAL( form_factor_squared->getMaxValue(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the min form factor squared value can be returned
FRENSIE_UNIT_TEST( StandardFormFactorSquared, getMinValue )
{
  FRENSIE_CHECK_EQUAL( form_factor_squared->getMinValue(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the squared argument can be returned
FRENSIE_UNIT_TEST( StandardFormFactorSquared, getLowerBoundOfSquaredArgument )
{
  FRENSIE_CHECK_FLOATING_EQUALITY(
			 form_factor_squared->getLowerBoundOfSquaredArgument(),
			 0.0*Utility::Units::inverse_square_centimeter,
			 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the squared argument can be returned
FRENSIE_UNIT_TEST( StandardFormFactorSquared, getUpperBoundOfSquaredArgument )
{
  FRENSIE_CHECK_FLOATING_EQUALITY(
			 form_factor_squared->getUpperBoundOfSquaredArgument(),
			 1e34*Utility::Units::inverse_square_centimeter,
			 1e-15 );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create the form factor squared
  {
    std::vector<double> sqr_args( 3 ), sqr_form_factor_vals( 3 );
    sqr_args[0] = 0.0;
    sqr_args[1] = 10.0;
    sqr_args[2] = 1e18;

    sqr_form_factor_vals[0] = 1.0;
    sqr_form_factor_vals[1] = 1e-6;
    sqr_form_factor_vals[2] = 0.0;

    std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<Utility::Units::InverseSquareAngstrom,void> >
      raw_form_factor_squared( new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::InverseSquareAngstrom,void>( sqr_args, sqr_form_factor_vals ) );

    form_factor_squared.reset( new MonteCarlo::StandardFormFactorSquared<Utility::Units::InverseSquareAngstrom>( raw_form_factor_squared ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstStandardFormFactorSquared.cpp
//---------------------------------------------------------------------------//
