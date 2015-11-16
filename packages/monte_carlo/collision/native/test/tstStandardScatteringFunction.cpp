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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_UnitTestHarnessExtensions.hpp"
#include "MonteCarlo_ComptonProfile.hpp"
#include "MonteCarlo_StandardScatteringFunction.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_InverseAngstromUnit.hpp"
#include "Utility_InverseCentimeterUnit.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::ScatteringFunction> scattering_function;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the scattering function can be evaluated
TEUCHOS_UNIT_TEST( StandardScatteringFunction, evaluate )
{
  MonteCarlo::ScatteringFunction::ArgumentQuantity
    arg( -1.0*Utility::Units::inverse_centimeter );

  double value = scattering_function->evaluate( arg );

  TEST_EQUALITY_CONST( value, 0.0 );

  arg = 0.0*Utility::Units::inverse_centimeter;

  value = scattering_function->evaluate( arg );

  TEST_EQUALITY_CONST( value, 0.0 );

  arg = 1e9*Utility::Units::inverse_centimeter;

  value = scattering_function->evaluate( arg );

  TEST_EQUALITY_CONST( value, 1e-3 );

  arg = 1e17*Utility::Units::inverse_centimeter;

  value = scattering_function->evaluate( arg );

  TEST_EQUALITY_CONST( value, 1.0 );

  arg = 1e18*Utility::Units::inverse_centimeter;

  value = scattering_function->evaluate( arg );

  TEST_EQUALITY_CONST( value, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the max scattering function value can be returned
TEUCHOS_UNIT_TEST( StandardScatteringFunction, getMaxValue )
{
  TEST_EQUALITY_CONST( scattering_function->getMaxValue(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the min scattering function value can be returned
TEUCHOS_UNIT_TEST( StandardScatteringFunction, getMinValue )
{
  TEST_EQUALITY_CONST( scattering_function->getMinValue(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the min scattering function value can be returned
TEUCHOS_UNIT_TEST( StandardScatteringFunction, getLowerBoundOfArgument )
{
  TEST_EQUALITY_CONST( scattering_function->getLowerBoundOfArgument(),
		       0.0*Utility::Units::inverse_centimeter );
}

//---------------------------------------------------------------------------//
// Check that the max scattering function value can be returned
TEUCHOS_UNIT_TEST( StandardScatteringFunction, getUpperBoundOfArgument )
{
  TEST_EQUALITY_CONST( scattering_function->getUpperBoundOfArgument(),
		       1e17*Utility::Units::inverse_centimeter );
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

  // Create the scattering function
  {
    Teuchos::Array<double> args( 3 ), scattering_func_vals( 3 );
    args[0] = 0.0;
    args[1] = 10.0;
    args[2] = 1e9;
    
    scattering_func_vals[0] = 0.0;
    scattering_func_vals[1] = 1e-3;
    scattering_func_vals[2] = 1.0;

    std::shared_ptr<Utility::UnitAwareOneDDistribution<Utility::Units::InverseAngstrom,void> >
      raw_scattering_function( new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::InverseAngstrom,void>( args, scattering_func_vals ) );

    scattering_function.reset( new MonteCarlo::StandardScatteringFunction<Utility::Units::InverseAngstrom>( raw_scattering_function ) );
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
// end tstStandardScatteringFunction.cpp
//---------------------------------------------------------------------------//
