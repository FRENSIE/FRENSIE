//---------------------------------------------------------------------------//
//!
//! \file   tstStandardComptonProfile.cpp
//! \author Alex Robinson
//! \brief  The standard Compton profile unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_ComptonProfile.hpp"
#include "MonteCarlo_StandardComptonProfile.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_AtomicMomentumUnit.hpp"
#include "Utility_MeCMomentumUnit.hpp"
#include "Utility_InverseAtomicMomentumUnit.hpp"
#include "Utility_InverseMeCMomentumUnit.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<const MonteCarlo::ComptonProfile> compton_profile;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the Compton profile can be evaluated
FRENSIE_UNIT_TEST( StandardComptonProfile, evaluate )
{
  MonteCarlo::ComptonProfile::MomentumQuantity
    momentum( -1.0*Utility::Units::mec_momentum );

  MonteCarlo::ComptonProfile::ProfileQuantity
    profile_value = compton_profile->evaluate( momentum );

  FRENSIE_CHECK_EQUAL( profile_value,
		       0.0*Utility::Units::inverse_mec_momentum );

  momentum = 0.0*Utility::Units::mec_momentum;

  profile_value = compton_profile->evaluate( momentum );

  FRENSIE_CHECK_EQUAL(
		   profile_value,
		   Utility::PhysicalConstants::inverse_fine_structure_constant*
		   Utility::Units::inverse_mec_momentum );

  momentum = 1.0*Utility::Units::mec_momentum;

  profile_value = compton_profile->evaluate( momentum );

  FRENSIE_CHECK_EQUAL(
		   profile_value,
		   Utility::PhysicalConstants::inverse_fine_structure_constant*
		   Utility::Units::inverse_mec_momentum );

  momentum = 1.5*Utility::Units::mec_momentum;

  profile_value = compton_profile->evaluate( momentum );

  FRENSIE_CHECK_EQUAL( profile_value,
		       0.0*Utility::Units::inverse_mec_momentum );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be sampled from
FRENSIE_UNIT_TEST( StandardComptonProfile, sample )
{
  MonteCarlo::ComptonProfile::MomentumQuantity
    momentum = compton_profile->sample();

  FRENSIE_CHECK( momentum >= 0.0*Utility::Units::mec_momentum );
  FRENSIE_CHECK( momentum <= 1.0*Utility::Units::mec_momentum );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be sampled from
FRENSIE_UNIT_TEST( StandardComptonProfile, sampleInSubrange )
{
  MonteCarlo::ComptonProfile::MomentumQuantity
    momentum = compton_profile->sampleInSubrange( 0.5*Utility::Units::mec_momentum );

  FRENSIE_CHECK( momentum >= 0.0*Utility::Units::mec_momentum );
  FRENSIE_CHECK( momentum <= 0.5*Utility::Units::mec_momentum );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be sampled from
FRENSIE_UNIT_TEST( StandardComptonProfile, sampleInSubrange_with_lower )
{
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ComptonProfile::MomentumQuantity
    momentum = compton_profile->sampleInSubrange(
                                           0.75*Utility::Units::mec_momentum,
                                           0.25*Utility::Units::mec_momentum );

  FRENSIE_CHECK_EQUAL( momentum, 0.25*Utility::Units::mec_momentum );

  momentum = compton_profile->sampleInSubrange(
                                           0.75*Utility::Units::mec_momentum,
                                           0.25*Utility::Units::mec_momentum );

  FRENSIE_CHECK_FLOATING_EQUALITY(
                          momentum, 0.75*Utility::Units::mec_momentum, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the momentum can be returned
FRENSIE_UNIT_TEST( StandardComptonProfile, getLowerBoundOfMomentum )
{
  MonteCarlo::ComptonProfile::MomentumQuantity
    momentum = compton_profile->getLowerBoundOfMomentum();

  FRENSIE_CHECK_EQUAL( momentum, 0.0*Utility::Units::mec_momentum );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the momentum can be returned
FRENSIE_UNIT_TEST( StandardComptonProfile, getUpperBoundOfMomentum )
{
  MonteCarlo::ComptonProfile::MomentumQuantity
    momentum = compton_profile->getUpperBoundOfMomentum();

  FRENSIE_CHECK_EQUAL( momentum, 1.0*Utility::Units::mec_momentum );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create the raw Compton profile
  {
    std::vector<double> momentums( 2 ), profile_vals( 2 );
    momentums[0] = 0.0;
    momentums[1] = Utility::PhysicalConstants::inverse_fine_structure_constant;

    profile_vals[0] = 1.0;
    profile_vals[1] = 1.0;

    std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<Utility::Units::AtomicMomentum,Utility::Units::InverseAtomicMomentum> >
      raw_compton_profile( new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::AtomicMomentum,Utility::Units::InverseAtomicMomentum>( momentums, profile_vals ) );

    compton_profile.reset( new MonteCarlo::StandardComptonProfile<Utility::Units::AtomicMomentum,Utility::Units::InverseAtomicMomentum>( raw_compton_profile ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstStandardComptonProfile.cpp
//---------------------------------------------------------------------------//
