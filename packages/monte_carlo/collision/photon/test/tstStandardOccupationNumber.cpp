//---------------------------------------------------------------------------//
//!
//! \file   tstStandardOccupationNumber.cpp
//! \author Alex Robinson
//! \brief  The standard occupation number scattering function unit tests
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
#include "MonteCarlo_StandardOccupationNumber.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_AtomicMomentumUnit.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::OccupationNumber> occupation_number;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the occupation number can be evaluated
TEUCHOS_UNIT_TEST( StandardOccupationNumber, evaluate )
{
  MonteCarlo::OccupationNumber::MomentumQuantity
    momentum( -1.0*Utility::Units::mec_momentum );

  TEST_EQUALITY_CONST( occupation_number->evaluate( momentum ), 0.0 );

  momentum = 0.0*Utility::Units::mec_momentum;

  TEST_EQUALITY_CONST( occupation_number->evaluate( momentum ), 0.5 );

  momentum = 1.0*Utility::Units::mec_momentum;

  TEST_EQUALITY_CONST( occupation_number->evaluate( momentum ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the max occupation number value can be returned
TEUCHOS_UNIT_TEST( StandardOccupationNumber, getMaxValue )
{
  TEST_EQUALITY_CONST( occupation_number->getMaxValue(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the min scattering function value can be returned
TEUCHOS_UNIT_TEST( StandardOccupationNumber, getMinValue )
{
  TEST_EQUALITY_CONST( occupation_number->getMinValue(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the occupation number indep variable
// can be returned
TEUCHOS_UNIT_TEST( StandardOccupationNumber, getLowerBoundOfIndepVar )
{
  MonteCarlo::OccupationNumber::MomentumQuantity
    momentum = occupation_number->getLowerBoundOfMomentum();

  TEST_EQUALITY_CONST( momentum, -1.0*Utility::Units::mec_momentum );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the occupation number indep variable
// can be returned
TEUCHOS_UNIT_TEST( StandardOccupationNumber, getUpperBoundOfIndepVar )
{
  MonteCarlo::OccupationNumber::MomentumQuantity
    momentum = occupation_number->getUpperBoundOfMomentum();

  TEST_EQUALITY_CONST( momentum, 1.0*Utility::Units::mec_momentum );
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

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) 
  {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Create the occupation number
  {
    Teuchos::Array<double> momentums( 2 ), occupation_number_vals( 2 );
    momentums[0] = -Utility::PhysicalConstants::inverse_fine_structure_constant;
    momentums[1] = Utility::PhysicalConstants::inverse_fine_structure_constant;

    occupation_number_vals[0] = 0.0;
    occupation_number_vals[1] = 1.0;
    
    // Create the occupation number distribution
    std::shared_ptr<Utility::UnitAwareTabularOneDDistribution<Utility::Units::AtomicMomentum,void> > raw_occupation_number(
              new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::AtomicMomentum,void>(
                                                    momentums,
                                                    occupation_number_vals ) );

    occupation_number.reset( new MonteCarlo::StandardOccupationNumber<Utility::Units::AtomicMomentum>( raw_occupation_number ) );
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
// end tstStandardOccupationNumber.cpp
//---------------------------------------------------------------------------//
