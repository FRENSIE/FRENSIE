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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_UnitTestHarnessExtensions.hpp"
#include "MonteCarlo_ComptonProfile.hpp"
#include "MonteCarlo_StandardFormFactorSquared.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_InverseSquareAngstromUnit.hpp"
#include "Utility_InverseSquareCentimeterUnit.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::FormFactorSquared> form_factor_squared;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the form factor squared can be evaluated
TEUCHOS_UNIT_TEST( StandardFormFactorSquared, evaluate )
{
  MonteCarlo::FormFactorSquared::SquaredArgumentQuantity
    sqr_arg( 0.0*Utility::Units::inverse_square_centimeter );

  double value = form_factor_squared->evaluate( sqr_arg );

  TEST_EQUALITY_CONST( value, 1.0 );

  sqr_arg = 1e34*Utility::Units::inverse_square_centimeter;
  value = form_factor_squared->evaluate( sqr_arg );

  UTILITY_TEST_FLOATING_EQUALITY( value, 0.0, 1e-15 );
  
  sqr_arg = 1e35*Utility::Units::inverse_square_centimeter;
  value = form_factor_squared->evaluate( sqr_arg );

  UTILITY_TEST_FLOATING_EQUALITY( value, 0.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the form factor squared can be sampled from
TEUCHOS_UNIT_TEST( StandardFormFactorSquared, sample )
{
  MonteCarlo::FormFactorSquared::SquaredArgumentQuantity 
    sqr_arg = form_factor_squared->sample();

  TEST_ASSERT( sqr_arg >= 0.0*Utility::Units::inverse_square_centimeter );
  TEST_ASSERT( sqr_arg <= 1e34*Utility::Units::inverse_square_centimeter );
}

//---------------------------------------------------------------------------//
// Check that the form factor squared can be sampled from
TEUCHOS_UNIT_TEST( StandardFormFactorSquared, sampleInSubrange )
{
  MonteCarlo::FormFactorSquared::SquaredArgumentQuantity
    sqr_arg = form_factor_squared->sampleInSubrange( 1e10*Utility::Units::inverse_square_centimeter );

  TEST_ASSERT( sqr_arg >= 0.0*Utility::Units::inverse_square_centimeter );
  TEST_ASSERT( sqr_arg <= 1e10*Utility::Units::inverse_square_centimeter );
}

//---------------------------------------------------------------------------//
// Check that the max form factor squared value can be returned
TEUCHOS_UNIT_TEST( StandardFormFactorSquared, getMaxValue )
{
  TEST_EQUALITY_CONST( form_factor_squared->getMaxValue(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the min form factor squared value can be returned
TEUCHOS_UNIT_TEST( StandardFormFactorSquared, getMinValue )
{
  TEST_EQUALITY_CONST( form_factor_squared->getMinValue(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the squared argument can be returned
TEUCHOS_UNIT_TEST( StandardFormFactorSquared, getLowerBoundOfSquaredArgument )
{
  UTILITY_TEST_FLOATING_EQUALITY(
			 form_factor_squared->getLowerBoundOfSquaredArgument(),
			 0.0*Utility::Units::inverse_square_centimeter,
			 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the squared argument can be returned
TEUCHOS_UNIT_TEST( StandardFormFactorSquared, getUpperBoundOfSquaredArgument )
{
  UTILITY_TEST_FLOATING_EQUALITY( 
			 form_factor_squared->getUpperBoundOfSquaredArgument(),
			 1e34*Utility::Units::inverse_square_centimeter,
			 1e-15 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }
  
  // Create the form factor squared
  {
    Teuchos::Array<double> sqr_args( 3 ), sqr_form_factor_vals( 3 );
    sqr_args[0] = 0.0;
    sqr_args[1] = 10.0;
    sqr_args[2] = 1e18;
    
    sqr_form_factor_vals[0] = 1.0;
    sqr_form_factor_vals[1] = 1e-6;
    sqr_form_factor_vals[2] = 0.0;

    std::shared_ptr<Utility::UnitAwareTabularOneDDistribution<Utility::Units::InverseSquareAngstrom,void> >
      raw_form_factor_squared( new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::InverseSquareAngstrom,void>( sqr_args, sqr_form_factor_vals ) );

    form_factor_squared.reset( new MonteCarlo::StandardFormFactorSquared<Utility::Units::InverseSquareAngstrom>( raw_form_factor_squared ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
  
  // Run the unit tests
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  const bool success = Teuchos::UnitTestRepository::runUnitTests( *out );

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstStandardFormFactorSquared.cpp
//---------------------------------------------------------------------------//
