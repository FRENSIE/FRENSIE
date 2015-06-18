//---------------------------------------------------------------------------//
//!
//! \file   tstHydrogenFormFactorDistribution.cpp
//! \author Alex Robinson
//! \brief  Hydrogen form factor distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_OneDDistribution.hpp"
#include "Utility_HydrogenFormFactorDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<Utility::OneDDistribution> distribution(
                               new Utility::HydrogenFormFactorDistribution() );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( HydrogenFormFactorDistribution, evaluate )
{
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( distribution->evaluate( 1.0 ), 
			  3.75610653691183e-12,
			  1e-15 );
  TEST_FLOATING_EQUALITY( distribution->evaluate( 100.0 ), 
			  3.75577292599516e-08,
			  1e-15 );
  TEST_FLOATING_EQUALITY( distribution->evaluate( 1e6 ),
			  0.929247855858261418,
			  1e-15 );
  TEST_FLOATING_EQUALITY( distribution->evaluate( 1e17 ),
			  1.0,
			  1e-15 );
}

//---------------------------------------------------------------------------//
// end tstHydrogenFormFactorDistribution.cpp
//---------------------------------------------------------------------------//
