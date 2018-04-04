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

// FRENSIE Includes
#include "MonteCarlo_StandardOccupationNumber.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_AtomicMomentumUnit.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<const MonteCarlo::OccupationNumber> occupation_number;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the occupation number can be evaluated
FRENSIE_UNIT_TEST( StandardOccupationNumber, evaluate )
{
  MonteCarlo::OccupationNumber::MomentumQuantity
    momentum( -1.0*Utility::Units::mec_momentum );

  FRENSIE_CHECK_EQUAL( occupation_number->evaluate( momentum ), 0.0 );

  momentum = 0.0*Utility::Units::mec_momentum;

  FRENSIE_CHECK_EQUAL( occupation_number->evaluate( momentum ), 0.5 );

  momentum = 1.0*Utility::Units::mec_momentum;

  FRENSIE_CHECK_EQUAL( occupation_number->evaluate( momentum ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the max occupation number value can be returned
FRENSIE_UNIT_TEST( StandardOccupationNumber, getMaxValue )
{
  FRENSIE_CHECK_EQUAL( occupation_number->getMaxValue(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the min scattering function value can be returned
FRENSIE_UNIT_TEST( StandardOccupationNumber, getMinValue )
{
  FRENSIE_CHECK_EQUAL( occupation_number->getMinValue(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the occupation number indep variable
// can be returned
FRENSIE_UNIT_TEST( StandardOccupationNumber, getLowerBoundOfIndepVar )
{
  MonteCarlo::OccupationNumber::MomentumQuantity
    momentum = occupation_number->getLowerBoundOfMomentum();

  FRENSIE_CHECK_EQUAL( momentum, -1.0*Utility::Units::mec_momentum );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the occupation number indep variable
// can be returned
FRENSIE_UNIT_TEST( StandardOccupationNumber, getUpperBoundOfIndepVar )
{
  MonteCarlo::OccupationNumber::MomentumQuantity
    momentum = occupation_number->getUpperBoundOfMomentum();

  FRENSIE_CHECK_EQUAL( momentum, 1.0*Utility::Units::mec_momentum );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create the occupation number
  std::vector<double> momentums( 2 ), occupation_number_vals( 2 );
  momentums[0] = -Utility::PhysicalConstants::inverse_fine_structure_constant;
  momentums[1] = Utility::PhysicalConstants::inverse_fine_structure_constant;
  
  occupation_number_vals[0] = 0.0;
  occupation_number_vals[1] = 1.0;
  
  // Create the occupation number distribution
  std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<Utility::Units::AtomicMomentum,void> > raw_occupation_number(
              new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::AtomicMomentum,void>(
                                                    momentums,
                                                    occupation_number_vals ) );

  occupation_number.reset( new MonteCarlo::StandardOccupationNumber<Utility::Units::AtomicMomentum>( raw_occupation_number ) );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstStandardOccupationNumber.cpp
//---------------------------------------------------------------------------//
