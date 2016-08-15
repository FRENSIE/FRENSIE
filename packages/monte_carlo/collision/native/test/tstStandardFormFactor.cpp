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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_UnitTestHarnessExtensions.hpp"
#include "MonteCarlo_ComptonProfile.hpp"
#include "MonteCarlo_StandardFormFactor.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_InverseAngstromUnit.hpp"
#include "Utility_InverseCentimeterUnit.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::FormFactor> form_factor;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the form factor squared can be evaluated
TEUCHOS_UNIT_TEST( StandardFormFactor, evaluate )
{
  MonteCarlo::FormFactor::ArgumentQuantity
    arg( 0.0*Utility::Units::inverse_centimeter );

  double value = form_factor->evaluate( arg );

  TEST_EQUALITY_CONST( value, 1.0 );

  arg = 1e17*Utility::Units::inverse_centimeter;
  value = form_factor->evaluate( arg );

  UTILITY_TEST_FLOATING_EQUALITY( value, 0.0, 1e-15 );

  arg = 1e18*Utility::Units::inverse_centimeter;
  value = form_factor->evaluate( arg );

  UTILITY_TEST_FLOATING_EQUALITY( value, 0.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the max form factor squared value can be returned
TEUCHOS_UNIT_TEST( StandardFormFactor, getMaxValue )
{
  TEST_EQUALITY_CONST( form_factor->getMaxValue(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the min form factor squared value can be returned
TEUCHOS_UNIT_TEST( StandardFormFactor, getMinValue )
{
  TEST_EQUALITY_CONST( form_factor->getMinValue(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the squared argument can be returned
TEUCHOS_UNIT_TEST( StandardFormFactor, getLowerBoundOfArgument )
{
  UTILITY_TEST_FLOATING_EQUALITY(
			 form_factor->getLowerBoundOfArgument(),
			 0.0*Utility::Units::inverse_centimeter,
			 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the squared argument can be returned
TEUCHOS_UNIT_TEST( StandardFormFactor, getUpperBoundOfArgument )
{
  UTILITY_TEST_FLOATING_EQUALITY(
			 form_factor->getUpperBoundOfArgument(),
			 1e17*Utility::Units::inverse_centimeter,
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

  // Create the form factor
  {
    Teuchos::Array<double> args( 3 ), form_factor_vals( 3 );
    args[0] = 0.0;
    args[1] = 10.0;
    args[2] = 1e9;

    form_factor_vals[0] = 1.0;
    form_factor_vals[1] = 0.001;
    form_factor_vals[2] = 0.0;

    std::shared_ptr<Utility::UnitAwareTabularOneDDistribution<Utility::Units::InverseAngstrom,void> >
      raw_form_factor( new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::InverseAngstrom,void>( args, form_factor_vals ) );

    form_factor.reset( new MonteCarlo::StandardFormFactor<Utility::Units::InverseAngstrom>( raw_form_factor ) );
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
// end tstStandardFormFactor.cpp
//---------------------------------------------------------------------------//
