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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_UnitTestHarnessExtensions.hpp"
#include "MonteCarlo_ComptonProfile.hpp"
#include "MonteCarlo_StandardComptonProfile.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_AtomicMomentumUnit.hpp"
#include "Utility_MeCMomentumUnit.hpp"
#include "Utility_InverseAtomicMomentumUnit.hpp"
#include "Utility_InverseMeCMomentumUnit.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::ComptonProfile> compton_profile;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the Compton profile can be evaluated
TEUCHOS_UNIT_TEST( StandardComptonProfile, evaluate )
{
  MonteCarlo::ComptonProfile::MomentumQuantity 
    momentum( -1.0*Utility::Units::mec_momentum );

  MonteCarlo::ComptonProfile::ProfileQuantity
    profile_value = compton_profile->evaluate( momentum );

  TEST_EQUALITY_CONST( profile_value, 
		       0.0*Utility::Units::inverse_mec_momentum );

  momentum = 0.0*Utility::Units::mec_momentum;
  
  profile_value = compton_profile->evaluate( momentum );

  TEST_EQUALITY_CONST( 
		   profile_value,
		   Utility::PhysicalConstants::inverse_fine_structure_constant*
		   Utility::Units::inverse_mec_momentum );

  momentum = 1.0*Utility::Units::mec_momentum;

  profile_value = compton_profile->evaluate( momentum );

  TEST_EQUALITY_CONST( 
		   profile_value,
		   Utility::PhysicalConstants::inverse_fine_structure_constant*
		   Utility::Units::inverse_mec_momentum );

  momentum = 1.5*Utility::Units::mec_momentum;

  profile_value = compton_profile->evaluate( momentum );

  TEST_EQUALITY_CONST( profile_value,
		       0.0*Utility::Units::inverse_mec_momentum );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be sampled from
TEUCHOS_UNIT_TEST( StandardComptonProfile, sample )
{
  MonteCarlo::ComptonProfile::MomentumQuantity 
    momentum = compton_profile->sample();

  TEST_ASSERT( momentum >= 0.0*Utility::Units::mec_momentum );
  TEST_ASSERT( momentum <= 1.0*Utility::Units::mec_momentum );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be sampled from
TEUCHOS_UNIT_TEST( StandardComptonProfile, sampleInSubrange )
{
  MonteCarlo::ComptonProfile::MomentumQuantity
    momentum = compton_profile->sampleInSubrange( 0.5*Utility::Units::mec_momentum );

  TEST_ASSERT( momentum >= 0.0*Utility::Units::mec_momentum );
  TEST_ASSERT( momentum <= 0.5*Utility::Units::mec_momentum );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the momentum can be returned
TEUCHOS_UNIT_TEST( StandardComptonProfile, getLowerBoundOfMomentum )
{
  MonteCarlo::ComptonProfile::MomentumQuantity
    momentum = compton_profile->getLowerBoundOfMomentum();

  TEST_EQUALITY_CONST( momentum, 0.0*Utility::Units::mec_momentum );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the momentum can be returned
TEUCHOS_UNIT_TEST( StandardComptonProfile, getUpperBoundOfMomentum )
{
  MonteCarlo::ComptonProfile::MomentumQuantity
    momentum = compton_profile->getUpperBoundOfMomentum();

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

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Create the raw Compton profile
  {
    Teuchos::Array<double> momentums( 2 ), profile_vals( 2 );
    momentums[0] = 0.0;
    momentums[1] = Utility::PhysicalConstants::inverse_fine_structure_constant;
    
    profile_vals[0] = 1.0;
    profile_vals[1] = 1.0;
    
    std::shared_ptr<Utility::UnitAwareTabularOneDDistribution<Utility::Units::AtomicMomentum,Utility::Units::InverseAtomicMomentum> > 
      raw_compton_profile( new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::AtomicMomentum,Utility::Units::InverseAtomicMomentum>( momentums, profile_vals ) );
    
    compton_profile.reset( new MonteCarlo::StandardComptonProfile<Utility::Units::AtomicMomentum,Utility::Units::InverseAtomicMomentum>( raw_compton_profile ) );
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
// end tstStandardComptonProfile.cpp
//---------------------------------------------------------------------------//
