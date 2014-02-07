//---------------------------------------------------------------------------//
//!
//! \file   tstExponentialDistribution.cpp
//! \author Alex Robinson
//! \brief  Histogram distribution unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>

// FACEMC Includes
#include "OneDDistribution.hpp"
#include "ExponentialDistribution.hpp"
#include "RandomNumberGenerator.hpp"

Teuchos::RCP<FACEMC::OneDDistribution> distribution( 
				     new ExponentialDistribution( 2.0, 3.0 ) );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//

// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( ExponentialDistribution, evaluate )
{
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), 2.0 );
}

//---------------------------------------------------------------------------//
// end tstExponentialDistribution.cpp
//---------------------------------------------------------------------------//
