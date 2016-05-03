//---------------------------------------------------------------------------//
//!
//! \file   tstDiscreteDistribution.cpp
//! \author Alex Robinson
//! \brief  Discrete distribution unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>

// Boost Includes
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/cgs.hpp>
#include <boost/units/io.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTraits.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_ElectronVoltUnit.hpp"

using boost::units::quantity;
using namespace Utility::Units;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<Teuchos::ParameterList> test_dists_list;

Teuchos::RCP<Utility::OneDDistribution> distribution;
Teuchos::RCP<Utility::TabularOneDDistribution> tab_distribution;
Teuchos::RCP<Utility::OneDDistribution> cdf_cons_distribution;
Teuchos::RCP<Utility::TabularOneDDistribution> tab_cdf_cons_distribution;
Teuchos::RCP<Utility::OneDDistribution> repeat_vals_distribution;
Teuchos::RCP<Utility::TabularOneDDistribution> tab_repeat_vals_distribution;

Teuchos::RCP<Utility::UnitAwareOneDDistribution<ElectronVolt,si::amount> >
  unit_aware_distribution;
Teuchos::RCP<Utility::UnitAwareTabularOneDDistribution<ElectronVolt,si::amount> >
  unit_aware_tab_distribution;

Teuchos::RCP<Utility::UnitAwareOneDDistribution<ElectronVolt,si::amount> >
  unit_aware_cdf_cons_distribution;
Teuchos::RCP<Utility::UnitAwareTabularOneDDistribution<ElectronVolt,si::amount> >
  unit_aware_tab_cdf_cons_distribution;


//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( DiscreteDistribution, evaluate )
{  
  TEST_EQUALITY_CONST( distribution->evaluate( -2.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0 ), 1.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( -0.5 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), 2.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.5 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0 ), 1.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 2.0 ), 0.0 );

  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluate( -2.0 ), 0.0 );
  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluate( -1.0 ), 0.25 );
  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluate( -0.5 ), 0.0 );
  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluate( 0.0 ), 0.5 );
  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluate( 0.5 ), 0.0 );
  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluate( 1.0 ), 0.25 );
  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluate( 2.0 ), 0.0 );

  TEST_EQUALITY_CONST( repeat_vals_distribution->evaluate( -2.0 ), 0.0 );
  TEST_EQUALITY_CONST( repeat_vals_distribution->evaluate( -1.0 ), 1.0 );
  TEST_EQUALITY_CONST( repeat_vals_distribution->evaluate( -0.5 ), 0.0 );
  TEST_EQUALITY_CONST( repeat_vals_distribution->evaluate( 0.0 ), 2.0 );
  TEST_EQUALITY_CONST( repeat_vals_distribution->evaluate( 0.5 ), 0.0 );
  TEST_EQUALITY_CONST( repeat_vals_distribution->evaluate( 1.0 ), 1.0 );
  TEST_EQUALITY_CONST( repeat_vals_distribution->evaluate( 2.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution, evaluate )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*eV ), 
		       0.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.1*eV ), 
		       0.25*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.5*eV ), 
		       0.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1.0*eV ), 
		       1.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 2.5*eV ), 
		       0.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 5.0*eV ), 
		       2.7*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 100.0*eV ), 
		       0.0*si::mole );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluate( 1e3*eV ), 
				  0.05*si::mole,
				  1e-14 );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 2e3*eV ), 
		       0.0*si::mole );

  TEST_EQUALITY_CONST( unit_aware_cdf_cons_distribution->evaluate( 0.0*eV ), 
		       0.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_cdf_cons_distribution->evaluate( 0.1*eV ), 
		       0.0625*si::mole );
  TEST_EQUALITY_CONST( unit_aware_cdf_cons_distribution->evaluate( 0.5*eV ), 
		       0.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_cdf_cons_distribution->evaluate( 1.0*eV ), 
		       0.25*si::mole );
  TEST_EQUALITY_CONST( unit_aware_cdf_cons_distribution->evaluate( 2.5*eV ), 
		       0.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_cdf_cons_distribution->evaluate( 5.0*eV ), 
		       0.675*si::mole );
  TEST_EQUALITY_CONST( unit_aware_cdf_cons_distribution->evaluate( 100.0*eV ), 
		       0.0*si::mole );
  UTILITY_TEST_FLOATING_EQUALITY( 
			  unit_aware_cdf_cons_distribution->evaluate( 1e3*eV ),
			  0.0125*si::mole,
			  1e-14 );
  TEST_EQUALITY_CONST( unit_aware_cdf_cons_distribution->evaluate( 2e3*eV ), 
		       0.0*si::mole );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( DiscreteDistribution, evaluatePDF )
{
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -2.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -1.0 ), 0.25 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -0.5 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 0.0 ), 0.50 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 0.5 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 1.0 ), 0.25 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 2.0 ), 0.0 );

  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluatePDF( -2.0 ), 0.0 );
  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluatePDF( -1.0 ), 0.25 );
  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluatePDF( -0.5 ), 0.0 );
  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluatePDF( 0.0 ), 0.50 );
  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluatePDF( 0.5 ), 0.0 );
  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluatePDF( 1.0 ), 0.25 );
  TEST_EQUALITY_CONST( cdf_cons_distribution->evaluatePDF( 2.0 ), 0.0 );

  TEST_EQUALITY_CONST( repeat_vals_distribution->evaluatePDF( -2.0 ), 0.0 );
  TEST_EQUALITY_CONST( repeat_vals_distribution->evaluatePDF( -1.0 ), 0.25 );
  TEST_EQUALITY_CONST( repeat_vals_distribution->evaluatePDF( -0.5 ), 0.0 );
  TEST_EQUALITY_CONST( repeat_vals_distribution->evaluatePDF( 0.0 ), 0.5 );
  TEST_EQUALITY_CONST( repeat_vals_distribution->evaluatePDF( 0.5 ), 0.0 );
  TEST_EQUALITY_CONST( repeat_vals_distribution->evaluatePDF( 1.0 ), 0.25 );
  TEST_EQUALITY_CONST( repeat_vals_distribution->evaluatePDF( 2.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware PDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution, evaluatePDF )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 0.0*eV ), 
		       0.0/eV );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 0.1*eV ), 
		       0.0625/eV );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 0.5*eV ), 
		       0.0/eV );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 1.0*eV ), 
		       0.25/eV );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 2.5*eV ), 
		       0.0/eV );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 5.0*eV ), 
		       0.675/eV );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 100.0*eV ), 
		       0.0/eV );
  UTILITY_TEST_FLOATING_EQUALITY(
			        unit_aware_distribution->evaluatePDF( 1e3*eV ),
				0.0125/eV,
				1e-14 );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 2e3*eV ), 
		       0.0/eV );

  TEST_EQUALITY_CONST( unit_aware_cdf_cons_distribution->evaluatePDF( 0.0*eV ),
		       0.0/eV );
  TEST_EQUALITY_CONST( unit_aware_cdf_cons_distribution->evaluatePDF( 0.1*eV ),
		       0.0625/eV );
  TEST_EQUALITY_CONST( unit_aware_cdf_cons_distribution->evaluatePDF( 0.5*eV ),
		       0.0/eV );
  TEST_EQUALITY_CONST( unit_aware_cdf_cons_distribution->evaluatePDF( 1.0*eV ),
		       0.25/eV );
  TEST_EQUALITY_CONST( unit_aware_cdf_cons_distribution->evaluatePDF( 2.5*eV ),
		       0.0/eV );
  TEST_EQUALITY_CONST( unit_aware_cdf_cons_distribution->evaluatePDF( 5.0*eV ),
		       0.675/eV );
  TEST_EQUALITY_CONST( unit_aware_cdf_cons_distribution->evaluatePDF(100.0*eV),
		       0.0/eV );
  UTILITY_TEST_FLOATING_EQUALITY(
		       unit_aware_cdf_cons_distribution->evaluatePDF( 1e3*eV ),
		       0.0125/eV,
		       1e-14 );
  TEST_EQUALITY_CONST( unit_aware_cdf_cons_distribution->evaluatePDF( 2e3*eV ),
		       0.0/eV );
}

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated
TEUCHOS_UNIT_TEST( DiscreteDistribution, evaluateCDF )
{
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( -2.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( -1.0 ), 0.25 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( -0.5 ), 0.25 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 0.0 ), 0.75 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 0.5 ), 0.75 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 1.0 ), 1.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 2.0 ), 1.0 );

  TEST_EQUALITY_CONST( tab_cdf_cons_distribution->evaluateCDF( -2.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_cdf_cons_distribution->evaluateCDF( -1.0 ), 0.25 );
  TEST_EQUALITY_CONST( tab_cdf_cons_distribution->evaluateCDF( -0.5 ), 0.25 );
  TEST_EQUALITY_CONST( tab_cdf_cons_distribution->evaluateCDF( 0.0 ), 0.75 );
  TEST_EQUALITY_CONST( tab_cdf_cons_distribution->evaluateCDF( 0.5 ), 0.75 );
  TEST_EQUALITY_CONST( tab_cdf_cons_distribution->evaluateCDF( 1.0 ), 1.0 );
  TEST_EQUALITY_CONST( tab_cdf_cons_distribution->evaluateCDF( 2.0 ), 1.0 );

  TEST_EQUALITY_CONST( tab_repeat_vals_distribution->evaluateCDF( -2.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_repeat_vals_distribution->evaluateCDF( -1.0 ), 0.25 );
  TEST_EQUALITY_CONST( tab_repeat_vals_distribution->evaluateCDF( -0.5 ), 0.25 );
  TEST_EQUALITY_CONST( tab_repeat_vals_distribution->evaluateCDF( 0.0 ), 0.75 );
  TEST_EQUALITY_CONST( tab_repeat_vals_distribution->evaluateCDF( 0.5 ), 0.75 );
  TEST_EQUALITY_CONST( tab_repeat_vals_distribution->evaluateCDF( 1.0 ), 1.0 );
  TEST_EQUALITY_CONST( tab_repeat_vals_distribution->evaluateCDF( 2.0 ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware CDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution, evaluateCDF )
{
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateCDF( 0.0*eV ), 
		       0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateCDF( 0.1*eV ), 
		       0.0625 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateCDF( 0.5*eV ), 
		       0.0625 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateCDF( 1.0*eV ),
		       0.3125 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateCDF( 2.5*eV ),
		       0.3125 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateCDF( 5.0*eV ),
		       0.9875 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateCDF(100.0*eV),
		       0.9875 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateCDF( 1e3*eV ),
		       1.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateCDF( 2e3*eV ),
		       1.0 );

  TEST_EQUALITY_CONST( 
		   unit_aware_tab_cdf_cons_distribution->evaluateCDF( 0.0*eV ),
		   0.0 );
  TEST_EQUALITY_CONST(
		   unit_aware_tab_cdf_cons_distribution->evaluateCDF( 0.1*eV ),
		   0.0625 );
  TEST_EQUALITY_CONST( 
		   unit_aware_tab_cdf_cons_distribution->evaluateCDF( 0.5*eV ),
		   0.0625 );
  TEST_EQUALITY_CONST( 
		   unit_aware_tab_cdf_cons_distribution->evaluateCDF( 1.0*eV ),
		   0.3125 );
  TEST_EQUALITY_CONST( 
		   unit_aware_tab_cdf_cons_distribution->evaluateCDF( 2.5*eV ),
		   0.3125 );
  TEST_EQUALITY_CONST( 
		   unit_aware_tab_cdf_cons_distribution->evaluateCDF( 5.0*eV ),
		   0.9875 );
  TEST_EQUALITY_CONST( 
		   unit_aware_tab_cdf_cons_distribution->evaluateCDF(100.0*eV),
		   0.9875 );
  TEST_EQUALITY_CONST( 
		   unit_aware_tab_cdf_cons_distribution->evaluateCDF( 1e3*eV ),
		   1.0 );
  TEST_EQUALITY_CONST( 
		   unit_aware_tab_cdf_cons_distribution->evaluateCDF( 2e3*eV ),
		   1.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( DiscreteDistribution, sample )
{
  std::vector<double> fake_stream( 7 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.2;
  fake_stream[2] = 1.0/4.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 3.0/4.0;
  fake_stream[5] = 0.85;
  fake_stream[6] = 1.0 - 1.0e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  // Test the first bin
  double sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  // Test the second bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.0 );
  
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.0 );
  
  // Test the third bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 1.0 );
  
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 1.0 );
  
  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  // Test the first bin
  sample = cdf_cons_distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  sample = cdf_cons_distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  sample = cdf_cons_distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  // Test the second bin
  sample = cdf_cons_distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.0 );
  
  sample = cdf_cons_distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.0 );
  
  // Test the third bin
  sample = cdf_cons_distribution->sample();
  TEST_EQUALITY_CONST( sample, 1.0 );
  
  sample = cdf_cons_distribution->sample();
  TEST_EQUALITY_CONST( sample, 1.0 );
  
  Utility::RandomNumberGenerator::unsetFakeStream();

  fake_stream.resize( 10 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0625;
  fake_stream[2] = 0.2;
  fake_stream[3] = 0.25;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.75;
  fake_stream[6] = 0.85;
  fake_stream[7] = 0.9375;
  fake_stream[8] = 0.95;
  fake_stream[9] = 1.0 - 1.0e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  sample = repeat_vals_distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  sample = repeat_vals_distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  // Test the second bin
  sample = repeat_vals_distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  sample = repeat_vals_distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  // Test the third bin
  sample = repeat_vals_distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.0 );
  
  sample = repeat_vals_distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.0 );
  
  // Test the fourth bin
  sample = repeat_vals_distribution->sample();
  TEST_EQUALITY_CONST( sample, 1.0 );
  
  sample = repeat_vals_distribution->sample();
  TEST_EQUALITY_CONST( sample, 1.0 );
  
  // Test the fifth bin
  sample = repeat_vals_distribution->sample();
  TEST_EQUALITY_CONST( sample, 1.0 );
  
  sample = repeat_vals_distribution->sample();
  TEST_EQUALITY_CONST( sample, 1.0 );
  
  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution, sample )
{
  std::vector<double> fake_stream( 7 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0625;
  fake_stream[2] = 0.3;
  fake_stream[3] = 0.3125;
  fake_stream[4] = 0.9;
  fake_stream[5] = 0.9875;
  fake_stream[6] = 1.0 - 1.0e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  // Test the first bin
  quantity<ElectronVolt> sample = unit_aware_distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.1*eV );
  
  sample = unit_aware_distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.1*eV );
  
  // Test the second bin
  sample = unit_aware_distribution->sample();
  TEST_EQUALITY_CONST( sample, 1.0*eV );
  
  sample = unit_aware_distribution->sample();
  TEST_EQUALITY_CONST( sample, 1.0*eV );
  
  // Test the third bin
  sample = unit_aware_distribution->sample();
  TEST_EQUALITY_CONST( sample, 5.0*eV );
  
  sample = unit_aware_distribution->sample();
  TEST_EQUALITY_CONST( sample, 5.0*eV );
  
  // Test the fourth bin
  sample = unit_aware_distribution->sample();
  TEST_EQUALITY_CONST( sample, 1e3*eV );
  
  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  // Test the first bin
  sample = unit_aware_cdf_cons_distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.1*eV );
  
  sample = unit_aware_cdf_cons_distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.1*eV );
  
  // Test the second bin
  sample = unit_aware_cdf_cons_distribution->sample();
  TEST_EQUALITY_CONST( sample, 1.0*eV );
  
  sample = unit_aware_cdf_cons_distribution->sample();
  TEST_EQUALITY_CONST( sample, 1.0*eV );
  
  // Test the third bin
  sample = unit_aware_cdf_cons_distribution->sample();
  TEST_EQUALITY_CONST( sample, 5.0*eV );
    
  sample = unit_aware_cdf_cons_distribution->sample();
  TEST_EQUALITY_CONST( sample, 5.0*eV );
  
  // Test the fourth bin
  sample = unit_aware_cdf_cons_distribution->sample();
  TEST_EQUALITY_CONST( sample, 1e3*eV );
  
  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( DiscreteDistribution, sampleAndRecordTrials )
{
  std::vector<double> fake_stream( 7 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.2;
  fake_stream[2] = 1.0/4.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 3.0/4.0;
  fake_stream[5] = 0.85;
  fake_stream[6] = 1.0 - 1.0e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  unsigned trials = 0;

  // Test the first bin
  double sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( trials, 1 );
  
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( trials, 2 );
  
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( trials, 3 );
  
  // Test the second bin
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( trials, 4 );
  
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( trials, 5 );
  
  // Test the third bin
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( trials, 6 );
  
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( trials, 7 );
  
  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0;
  
  // Test the first bin
  sample = cdf_cons_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( trials, 1 );
  
  sample = cdf_cons_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( trials, 2 );
  
  sample = cdf_cons_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( trials, 3 );
  
  // Test the second bin
  sample = cdf_cons_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( trials, 4 );
  
  sample = cdf_cons_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( trials, 5 );
  
  // Test the third bin
  sample = cdf_cons_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( trials, 6 );
  
  sample = cdf_cons_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( trials, 7 );
  
  Utility::RandomNumberGenerator::unsetFakeStream();

  fake_stream.resize( 10 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0625;
  fake_stream[2] = 0.2;
  fake_stream[3] = 0.25;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.75;
  fake_stream[6] = 0.85;
  fake_stream[7] = 0.9375;
  fake_stream[8] = 0.95;
  fake_stream[9] = 1.0 - 1.0e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0;

  // Test the first bin
  sample = repeat_vals_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( trials, 1 );
  
  sample = repeat_vals_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( trials, 2 );
  
  // Test the second bin
  sample = repeat_vals_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( trials, 3 );
  
  sample = repeat_vals_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( trials, 4 );
  
  // Test the third bin
  sample = repeat_vals_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( trials, 5 );
  
  sample = repeat_vals_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( trials, 6 );
  
  // Test the fourth bin
  sample = repeat_vals_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( trials, 7 );
  
  sample = repeat_vals_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( trials, 8 );
  
  // Test the fifth bin
  sample = repeat_vals_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( trials, 9 );
  
  sample = repeat_vals_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( trials, 10 );
  
  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution, sampleAndRecordTrials )
{
  std::vector<double> fake_stream( 7 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0625;
  fake_stream[2] = 0.3;
  fake_stream[3] = 0.3125;
  fake_stream[4] = 0.9;
  fake_stream[5] = 0.9875;
  fake_stream[6] = 1.0 - 1.0e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  unsigned trials = 0;

  // Test the first bin
  quantity<ElectronVolt> sample = 
    unit_aware_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.1*eV );
  TEST_EQUALITY_CONST( trials, 1u );
  
  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.1*eV );
  TEST_EQUALITY_CONST( trials, 2u );
  
  // Test the second bin
  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1.0*eV );
  TEST_EQUALITY_CONST( trials, 3u );
  
  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1.0*eV );
  TEST_EQUALITY_CONST( trials, 4u );
  
  // Test the third bin
  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 5.0*eV );
  TEST_EQUALITY_CONST( trials, 5u );
  
  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 5.0*eV );
  TEST_EQUALITY_CONST( trials, 6u );
  
  // Test the fourth bin
  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1e3*eV );
  TEST_EQUALITY_CONST( trials, 7u );
  
  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0u;
  
  // Test the first bin
  sample = unit_aware_cdf_cons_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.1*eV );
  TEST_EQUALITY_CONST( trials, 1u );
  
  sample = unit_aware_cdf_cons_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.1*eV );
  TEST_EQUALITY_CONST( trials, 2u );
  
  // Test the second bin
  sample = unit_aware_cdf_cons_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1.0*eV );
  TEST_EQUALITY_CONST( trials, 3u );
  
  sample = unit_aware_cdf_cons_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1.0*eV );
  TEST_EQUALITY_CONST( trials, 4u );
  
  // Test the third bin
  sample = unit_aware_cdf_cons_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 5.0*eV );
  TEST_EQUALITY_CONST( trials, 5u );
    
  sample = unit_aware_cdf_cons_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 5.0*eV );
  TEST_EQUALITY_CONST( trials, 6u );
  
  // Test the fourth bin
  sample = unit_aware_cdf_cons_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1e3*eV );
  TEST_EQUALITY_CONST( trials, 7u );
  
  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( DiscreteDistribution, sampleAndRecordBinIndex )
{
  std::vector<double> fake_stream( 7 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.2;
  fake_stream[2] = 1.0/4.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 3.0/4.0;
  fake_stream[5] = 0.85;
  fake_stream[6] = 1.0 - 1.0e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  unsigned bin_index;

  // Test the first bin
  double sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( bin_index, 0u );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( bin_index, 0u );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( bin_index, 0u );

  // Test the second bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( bin_index, 1u );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( bin_index, 1u );

  // Test the third bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  // Test the first bin
  sample = tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( bin_index, 0u );

  sample = tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( bin_index, 0u );

  sample = tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( bin_index, 0u );

  // Test the second bin
  sample = tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( bin_index, 1u );

  sample = tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( bin_index, 1u );

  // Test the third bin
  sample = tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  sample = tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  Utility::RandomNumberGenerator::unsetFakeStream();

  fake_stream.resize( 10 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0625;
  fake_stream[2] = 0.2;
  fake_stream[3] = 0.25;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.75;
  fake_stream[6] = 0.85;
  fake_stream[7] = 0.9375;
  fake_stream[8] = 0.95;
  fake_stream[9] = 1.0 - 1.0e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  sample = tab_repeat_vals_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( bin_index, 0u );

  sample = tab_repeat_vals_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( bin_index, 0u );

  // Test the second bin
  sample = tab_repeat_vals_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( bin_index, 1u );

  sample = tab_repeat_vals_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( bin_index, 1u );

  // Test the third bin
  sample = tab_repeat_vals_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  sample = tab_repeat_vals_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  // Test the fourth bin
  sample = tab_repeat_vals_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( bin_index, 3u );

  sample = tab_repeat_vals_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( bin_index, 3u );

  // Test the fifth bin
  sample = tab_repeat_vals_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( bin_index, 4u );

  sample = tab_repeat_vals_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( bin_index, 4u );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution, sampleAndRecordBinIndex )
{
  std::vector<double> fake_stream( 7 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0625;
  fake_stream[2] = 0.3;
  fake_stream[3] = 0.3125;
  fake_stream[4] = 0.9;
  fake_stream[5] = 0.9875;
  fake_stream[6] = 1.0 - 1.0e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  unsigned bin_index = 0;

  // Test the first bin
  quantity<ElectronVolt> sample = 
    unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 0.1*eV );
  TEST_EQUALITY_CONST( bin_index, 0u );
  
  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 0.1*eV );
  TEST_EQUALITY_CONST( bin_index, 0u );
  
  // Test the second bin
  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1.0*eV );
  TEST_EQUALITY_CONST( bin_index, 1u );
  
  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1.0*eV );
  TEST_EQUALITY_CONST( bin_index, 1u );
  
  // Test the third bin
  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 5.0*eV );
  TEST_EQUALITY_CONST( bin_index, 2u );
  
  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 5.0*eV );
  TEST_EQUALITY_CONST( bin_index, 2u );
  
  // Test the fourth bin
  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1e3*eV );
  TEST_EQUALITY_CONST( bin_index, 3u );
  
  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  sample = unit_aware_tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 0.1*eV );
  TEST_EQUALITY_CONST( bin_index, 0u );
  
  sample = unit_aware_tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 0.1*eV );
  TEST_EQUALITY_CONST( bin_index, 0u );
  
  // Test the second bin
  sample = unit_aware_tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1.0*eV );
  TEST_EQUALITY_CONST( bin_index, 1u );
  
  sample = unit_aware_tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1.0*eV );
  TEST_EQUALITY_CONST( bin_index, 1u );
  
  // Test the third bin
  sample = unit_aware_tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 5.0*eV );
  TEST_EQUALITY_CONST( bin_index, 2u );
    
  sample = unit_aware_tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 5.0*eV );
  TEST_EQUALITY_CONST( bin_index, 2u );
  
  // Test the fourth bin
  sample = unit_aware_tab_cdf_cons_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1e3*eV );
  TEST_EQUALITY_CONST( bin_index, 3u );
  
  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( DiscreteDistribution, sampleWithRandomNumber )
{
  // Test the first bin
  double sample = tab_distribution->sampleWithRandomNumber( 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  sample = tab_distribution->sampleWithRandomNumber( 0.2 );
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  sample = tab_distribution->sampleWithRandomNumber( 0.25 );
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  // Test the second bin
  sample = tab_distribution->sampleWithRandomNumber( 0.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );
  
  sample = tab_distribution->sampleWithRandomNumber( 0.75 );
  TEST_EQUALITY_CONST( sample, 0.0 );
  
  // Test the third bin
  sample = tab_distribution->sampleWithRandomNumber( 0.85 );
  TEST_EQUALITY_CONST( sample, 1.0 );
  
  sample = tab_distribution->sampleWithRandomNumber( 1.0 );
  TEST_EQUALITY_CONST( sample, 1.0 );
  
  // Test the first bin
  sample = tab_cdf_cons_distribution->sampleWithRandomNumber( 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  sample = tab_cdf_cons_distribution->sampleWithRandomNumber( 0.2 );
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  sample = tab_cdf_cons_distribution->sampleWithRandomNumber( 0.25 );
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  // Test the second bin
  sample = tab_cdf_cons_distribution->sampleWithRandomNumber( 0.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );
  
  sample = tab_cdf_cons_distribution->sampleWithRandomNumber( 0.75 );
  TEST_EQUALITY_CONST( sample, 0.0 );
  
  // Test the third bin
  sample = tab_cdf_cons_distribution->sampleWithRandomNumber( 0.85 );
  TEST_EQUALITY_CONST( sample, 1.0 );
  
  sample = tab_cdf_cons_distribution->sampleWithRandomNumber( 1.0 );
  TEST_EQUALITY_CONST( sample, 1.0 );

  // Test the first bin
  sample = tab_repeat_vals_distribution->sampleWithRandomNumber( 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  sample = tab_repeat_vals_distribution->sampleWithRandomNumber( 0.0625 );
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  // Test the second bin
  sample = tab_repeat_vals_distribution->sampleWithRandomNumber( 0.2 );
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  sample = tab_repeat_vals_distribution->sampleWithRandomNumber( 0.25 );
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  // Test the third bin
  sample = tab_repeat_vals_distribution->sampleWithRandomNumber( 0.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );
  
  sample = tab_repeat_vals_distribution->sampleWithRandomNumber( 0.75 );
  TEST_EQUALITY_CONST( sample, 0.0 );
  
  // Test the fourth bin
  sample = tab_repeat_vals_distribution->sampleWithRandomNumber( 0.85 );
  TEST_EQUALITY_CONST( sample, 1.0 );
  
  sample = tab_repeat_vals_distribution->sampleWithRandomNumber( 0.9375 );
  TEST_EQUALITY_CONST( sample, 1.0 );
  
  // Test the fifth bin
  sample = tab_repeat_vals_distribution->sampleWithRandomNumber( 0.95 );
  TEST_EQUALITY_CONST( sample, 1.0 );
  
  sample = tab_repeat_vals_distribution->sampleWithRandomNumber( 1.0 );
  TEST_EQUALITY_CONST( sample, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution, sampleWithRandomNumber )
{
  // Test the first bin
  quantity<ElectronVolt> sample = 
    unit_aware_tab_distribution->sampleWithRandomNumber( 0.0 );
  TEST_EQUALITY_CONST( sample, 0.1*eV );
    
  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 0.0625 );
  TEST_EQUALITY_CONST( sample, 0.1*eV );
    
  // Test the second bin
  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 0.3 );
  TEST_EQUALITY_CONST( sample, 1.0*eV );
    
  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 0.3125 );
  TEST_EQUALITY_CONST( sample, 1.0*eV );
    
  // Test the third bin
  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 0.9 );
  TEST_EQUALITY_CONST( sample, 5.0*eV );
    
  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 0.9875 );
  TEST_EQUALITY_CONST( sample, 5.0*eV );
    
  // Test the fourth bin
  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 1.0-1e-15 );
  TEST_EQUALITY_CONST( sample, 1e3*eV );
    
  // Test the first bin
  sample = unit_aware_tab_cdf_cons_distribution->sampleWithRandomNumber( 0.0 );
  TEST_EQUALITY_CONST( sample, 0.1*eV );
    
  sample = unit_aware_tab_cdf_cons_distribution->sampleWithRandomNumber( 0.0625 );
  TEST_EQUALITY_CONST( sample, 0.1*eV );
    
  // Test the second bin
  sample = unit_aware_tab_cdf_cons_distribution->sampleWithRandomNumber( 0.3 );
  TEST_EQUALITY_CONST( sample, 1.0*eV );
    
  sample = unit_aware_tab_cdf_cons_distribution->sampleWithRandomNumber( 0.3125 );
  TEST_EQUALITY_CONST( sample, 1.0*eV );
    
  // Test the third bin
  sample = unit_aware_tab_cdf_cons_distribution->sampleWithRandomNumber( 0.9 );
  TEST_EQUALITY_CONST( sample, 5.0*eV );
      
  sample = unit_aware_tab_cdf_cons_distribution->sampleWithRandomNumber( 0.9875 );
  TEST_EQUALITY_CONST( sample, 5.0*eV );
    
  // Test the fourth bin
  sample = unit_aware_tab_cdf_cons_distribution->sampleWithRandomNumber( 1.0-1e-15 );
  TEST_EQUALITY_CONST( sample, 1e3*eV );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( DiscreteDistribution, sampleInSubrange )
{
  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.2;
  fake_stream[2] = 1.0/3.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 1.0 - 1.0e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  double sample = tab_distribution->sampleInSubrange( 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  sample = tab_distribution->sampleInSubrange( 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  sample = tab_distribution->sampleInSubrange( 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  // Test the second bin
  sample = tab_distribution->sampleInSubrange( 0.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );
  
  sample = tab_distribution->sampleInSubrange( 0.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );
  
  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
    
  // Test the first bin
  sample = tab_cdf_cons_distribution->sampleInSubrange( 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  sample = tab_cdf_cons_distribution->sampleInSubrange( 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  sample = tab_cdf_cons_distribution->sampleInSubrange( 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  // Test the second bin
  sample = tab_cdf_cons_distribution->sampleInSubrange( 0.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );
  
  sample = tab_cdf_cons_distribution->sampleInSubrange( 0.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.25/3.0;
  fake_stream[2] = 0.2;
  fake_stream[3] = 1.0/3.0;
  fake_stream[4] = 0.5;
  fake_stream[5] = 1.0 - 1.0e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  sample = tab_repeat_vals_distribution->sampleInSubrange( 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  sample = tab_repeat_vals_distribution->sampleInSubrange( 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  // Test the second bin
  sample = tab_repeat_vals_distribution->sampleInSubrange( 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  sample = tab_repeat_vals_distribution->sampleInSubrange( 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  // Test the third bin
  sample = tab_repeat_vals_distribution->sampleInSubrange( 0.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );
  
  sample = tab_repeat_vals_distribution->sampleInSubrange( 0.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution, sampleInSubrange )
{
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.2;
  fake_stream[2] = 0.6;
  fake_stream[3] = 1.0 - 1.0e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  // Test the first bin
  quantity<ElectronVolt> sample = 
    unit_aware_tab_distribution->sampleInSubrange( 3.0*eV );
  TEST_EQUALITY_CONST( sample, 0.1*eV );
    
  sample = unit_aware_tab_distribution->sampleInSubrange( 3.0*eV );
  TEST_EQUALITY_CONST( sample, 0.1*eV );
    
  // Test the second bin
  sample = unit_aware_tab_distribution->sampleInSubrange( 3.0*eV );
  TEST_EQUALITY_CONST( sample, 1.0*eV );
    
  sample = unit_aware_tab_distribution->sampleInSubrange( 3.0*eV );
  TEST_EQUALITY_CONST( sample, 1.0*eV );
    
  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  sample = unit_aware_tab_cdf_cons_distribution->sampleInSubrange( 3.0*eV );
  TEST_EQUALITY_CONST( sample, 0.1*eV );
  
  sample = unit_aware_tab_cdf_cons_distribution->sampleInSubrange( 3.0*eV );
  TEST_EQUALITY_CONST( sample, 0.1*eV );
    
  // Test the second bin
  sample = unit_aware_tab_cdf_cons_distribution->sampleInSubrange( 3.0*eV );
  TEST_EQUALITY_CONST( sample, 1.0*eV );
    
  sample = unit_aware_tab_cdf_cons_distribution->sampleInSubrange( 3.0*eV );
  TEST_EQUALITY_CONST( sample, 1.0*eV );
    
  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( DiscreteDistribution, sampleWithRandomNumberInSubrange )
{
  // Test the first bin
  double sample = tab_distribution->sampleWithRandomNumberInSubrange( 0.0, 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  sample = tab_distribution->sampleWithRandomNumberInSubrange( 0.2, 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  sample = tab_distribution->sampleWithRandomNumberInSubrange( 1.0/3.0, 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  // Test the second bin
  sample = tab_distribution->sampleWithRandomNumberInSubrange( 0.5, 0.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );
  
  sample = tab_distribution->sampleWithRandomNumberInSubrange( 1.0, 0.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );
  
  // Test the first bin
  sample = tab_cdf_cons_distribution->sampleWithRandomNumberInSubrange( 0.0, 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  sample = tab_cdf_cons_distribution->sampleWithRandomNumberInSubrange( 0.2, 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  sample = tab_cdf_cons_distribution->sampleWithRandomNumberInSubrange( 1.0/3.0, 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  // Test the second bin
  sample = tab_cdf_cons_distribution->sampleWithRandomNumberInSubrange( 0.5, 0.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );
  
  sample = tab_cdf_cons_distribution->sampleWithRandomNumberInSubrange( 1.0, 0.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  // Test the first bin
  sample = tab_repeat_vals_distribution->sampleWithRandomNumberInSubrange( 0.0, 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  sample = tab_repeat_vals_distribution->sampleWithRandomNumberInSubrange( 1.0/12, 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  // Test the second bin
  sample = tab_repeat_vals_distribution->sampleWithRandomNumberInSubrange( 0.2, 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  sample = tab_repeat_vals_distribution->sampleWithRandomNumberInSubrange( 1.0/3, 0.5 );
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  // Test the third bin
  sample = tab_repeat_vals_distribution->sampleWithRandomNumberInSubrange( 0.5, 0.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );
  
  sample = tab_repeat_vals_distribution->sampleWithRandomNumberInSubrange( 1.0, 0.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution, 
		   sampleWithRandomNumberInSubrange )
{
  // Test the first bin
  quantity<ElectronVolt> sample = 
    unit_aware_tab_distribution->sampleWithRandomNumberInSubrange( 0.0, 3.0*eV );
  TEST_EQUALITY_CONST( sample, 0.1*eV );
    
  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange( 0.2, 3.0*eV );
  TEST_EQUALITY_CONST( sample, 0.1*eV );
    
  // Test the second bin
  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange( 0.6, 3.0*eV );
  TEST_EQUALITY_CONST( sample, 1.0*eV );
    
  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange( 0.99, 3.0*eV );
  TEST_EQUALITY_CONST( sample, 1.0*eV );
    
  // Test the first bin
  sample = unit_aware_tab_cdf_cons_distribution->sampleWithRandomNumberInSubrange( 0.0, 3.0*eV );
  TEST_EQUALITY_CONST( sample, 0.1*eV );
    
  sample = unit_aware_tab_cdf_cons_distribution->sampleWithRandomNumberInSubrange( 0.2, 3.0*eV );
  TEST_EQUALITY_CONST( sample, 0.1*eV );
    
  // Test the second bin
  sample = unit_aware_tab_cdf_cons_distribution->sampleWithRandomNumberInSubrange( 0.6, 3.0*eV );
  TEST_EQUALITY_CONST( sample, 1.0*eV );
    
  sample = unit_aware_tab_cdf_cons_distribution->sampleWithRandomNumberInSubrange( 0.99, 3.0*eV );
  TEST_EQUALITY_CONST( sample, 1.0*eV );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( DiscreteDistribution, getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfIndepVar(), 1.0 );
  TEST_EQUALITY_CONST( cdf_cons_distribution->getUpperBoundOfIndepVar(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware distribution independent 
// variable can be returned
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution, getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfIndepVar(), 1e3*eV );
  TEST_EQUALITY_CONST( unit_aware_cdf_cons_distribution->getUpperBoundOfIndepVar(), 1e3*eV );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution dependent variable can be
// returned
TEUCHOS_UNIT_TEST( DiscreteDistribution, getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfIndepVar(), -1.0 );
  TEST_EQUALITY_CONST( cdf_cons_distribution->getLowerBoundOfIndepVar(),-1.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware distribution dependent variable
// can be returned
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution, getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfIndepVar(), 0.1*eV );
  TEST_EQUALITY_CONST( unit_aware_cdf_cons_distribution->getLowerBoundOfIndepVar(), 0.1*eV );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
TEUCHOS_UNIT_TEST( DiscreteDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( distribution->getDistributionType(),
		       Utility::DISCRETE_DISTRIBUTION );
  TEST_EQUALITY_CONST( cdf_cons_distribution->getDistributionType(),
		       Utility::DISCRETE_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type can be returned
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getDistributionType(),
		       Utility::DISCRETE_DISTRIBUTION );
  TEST_EQUALITY_CONST( unit_aware_cdf_cons_distribution->getDistributionType(),
		       Utility::DISCRETE_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
TEUCHOS_UNIT_TEST( DiscreteDistribution, isTabular )
{
  TEST_ASSERT( distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution, isTabular )
{
  TEST_ASSERT( unit_aware_distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
TEUCHOS_UNIT_TEST( DiscreteDistribution, isContinuous )
{
  TEST_ASSERT( !distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution, isContinuous )
{
  TEST_ASSERT( !unit_aware_distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be written to an xml file
TEUCHOS_UNIT_TEST( DiscreteDistribution, toParameterList )
{
  Teuchos::RCP<Utility::DiscreteDistribution> true_distribution =
    Teuchos::rcp_dynamic_cast<Utility::DiscreteDistribution>( distribution );
  
  Teuchos::ParameterList parameter_list;
  
  parameter_list.set<Utility::DiscreteDistribution>( "test distribution", 
						     *true_distribution );

  Teuchos::writeParameterListToXmlFile( parameter_list,
					"discrete_dist_test_list.xml" );
  
  Teuchos::RCP<Teuchos::ParameterList> read_parameter_list = 
    Teuchos::getParametersFromXmlFile( "discrete_dist_test_list.xml" );

  // Rounding errors prevent us from being able to do this test reliably
  // TEST_EQUALITY( parameter_list, *read_parameter_list );

  Teuchos::RCP<Utility::DiscreteDistribution> 
    copy_distribution( new Utility::DiscreteDistribution );

  *copy_distribution = read_parameter_list->get<Utility::DiscreteDistribution>(
							  "test distribution");

  // Rounding errors prevent us from being able to do a full equality test
  // reliably
  //TEST_EQUALITY( *copy_distribution, *true_distribution );
  TEST_FLOATING_EQUALITY( copy_distribution->getLowerBoundOfIndepVar(),
                          true_distribution->getLowerBoundOfIndepVar(),
                          1e-15 );
  TEST_FLOATING_EQUALITY( copy_distribution->getUpperBoundOfIndepVar(),
                          true_distribution->getUpperBoundOfIndepVar(),
                          1e-15 );                       
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be written to an xml file
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution, toParameterList )
{
  typedef Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount> UnitAwareDiscreteDistribution;
  
  Teuchos::RCP<UnitAwareDiscreteDistribution> true_distribution =
    Teuchos::rcp_dynamic_cast<UnitAwareDiscreteDistribution>( unit_aware_distribution );
  
  Teuchos::ParameterList parameter_list;
  
  parameter_list.set<UnitAwareDiscreteDistribution>( "test distribution", 
						     *true_distribution );

  Teuchos::writeParameterListToXmlFile( parameter_list,
					"unit_aware_discrete_dist_test_list.xml" );
  
  Teuchos::RCP<Teuchos::ParameterList> read_parameter_list = 
    Teuchos::getParametersFromXmlFile( "unit_aware_discrete_dist_test_list.xml" );
  
  TEST_EQUALITY( parameter_list, *read_parameter_list );

  Teuchos::RCP<UnitAwareDiscreteDistribution> 
    copy_distribution( new UnitAwareDiscreteDistribution );

  *copy_distribution = read_parameter_list->get<UnitAwareDiscreteDistribution>(
							  "test distribution");

  TEST_EQUALITY( *copy_distribution, *true_distribution );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be read from an xml file
TEUCHOS_UNIT_TEST( DiscreteDistribution, fromParameterList )
{
  Utility::DiscreteDistribution xml_distribution = 
    test_dists_list->get<Utility::DiscreteDistribution>( "Discrete Distribution A" );
  
  TEST_EQUALITY_CONST( xml_distribution.getLowerBoundOfIndepVar(), -1.0 );
  TEST_EQUALITY_CONST( xml_distribution.getUpperBoundOfIndepVar(), 1.0 );
  TEST_EQUALITY_CONST( xml_distribution.evaluatePDF( -1.0 ), 0.25 );
  TEST_EQUALITY_CONST( xml_distribution.evaluatePDF( 0.0 ), 0.5 );
  TEST_EQUALITY_CONST( xml_distribution.evaluatePDF( 1.0 ), 0.25 );

  xml_distribution = 
    test_dists_list->get<Utility::DiscreteDistribution>( "Discrete Distribution B" );

  TEST_EQUALITY_CONST( xml_distribution.getLowerBoundOfIndepVar(), 
		       -Utility::PhysicalConstants::pi/2 );
  TEST_EQUALITY_CONST( xml_distribution.getUpperBoundOfIndepVar(),
		       Utility::PhysicalConstants::pi );
  TEST_FLOATING_EQUALITY( xml_distribution.evaluatePDF(-Utility::PhysicalConstants::pi/2),
			  0.2,
			  1e-15 );
  TEST_FLOATING_EQUALITY( xml_distribution.evaluatePDF(Utility::PhysicalConstants::pi),
			  0.2,
			  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that distributions can be scaled
TEUCHOS_UNIT_TEST_TEMPLATE_4_DECL( UnitAwareDiscreteDistribution,
				   explicit_conversion,
				   IndepUnitA,
				   DepUnitA,
				   IndepUnitB,
				   DepUnitB )
{
  typedef typename Utility::UnitTraits<IndepUnitA>::template GetQuantityType<double>::type IndepQuantityA;
  typedef typename Utility::UnitTraits<typename Utility::UnitTraits<IndepUnitA>::InverseUnit>::template GetQuantityType<double>::type InverseIndepQuantityA;
  
  typedef typename Utility::UnitTraits<IndepUnitB>::template GetQuantityType<double>::type IndepQuantityB;
  typedef typename Utility::UnitTraits<typename Utility::UnitTraits<IndepUnitB>::InverseUnit>::template GetQuantityType<double>::type InverseIndepQuantityB;
  
  typedef typename Utility::UnitTraits<DepUnitA>::template GetQuantityType<double>::type DepQuantityA;
  typedef typename Utility::UnitTraits<DepUnitB>::template GetQuantityType<double>::type DepQuantityB;

  // Copy from unitless distribution to distribution type A
  Utility::UnitAwareDiscreteDistribution<IndepUnitA,DepUnitA>
    unit_aware_dist_a_copy = Utility::UnitAwareDiscreteDistribution<IndepUnitA,DepUnitA>::fromUnitlessDistribution( *Teuchos::rcp_dynamic_cast<Utility::DiscreteDistribution>( distribution ) );

  // Copy from distribution type A to distribution type B
  Utility::UnitAwareDiscreteDistribution<IndepUnitB,DepUnitB>
    unit_aware_dist_b_copy( unit_aware_dist_a_copy );

  IndepQuantityA indep_quantity_a = 
    Utility::QuantityTraits<IndepQuantityA>::initializeQuantity( 0.0 );
  InverseIndepQuantityA inv_indep_quantity_a = 
    Utility::QuantityTraits<InverseIndepQuantityA>::initializeQuantity( 0.5 );
  DepQuantityA dep_quantity_a = 
    Utility::QuantityTraits<DepQuantityA>::initializeQuantity( 2.0 );

  IndepQuantityB indep_quantity_b( indep_quantity_a );
  InverseIndepQuantityB inv_indep_quantity_b = 
    Utility::QuantityTraits<InverseIndepQuantityB>::initializeQuantity( 0.5 );
  DepQuantityB dep_quantity_b( dep_quantity_a );

  UTILITY_TEST_FLOATING_EQUALITY( 
			   unit_aware_dist_a_copy.evaluate( indep_quantity_a ),
			   dep_quantity_a,
			   1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( 
			unit_aware_dist_a_copy.evaluatePDF( indep_quantity_a ),
			inv_indep_quantity_a,
			1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( 
			   unit_aware_dist_b_copy.evaluate( indep_quantity_b ),
			   dep_quantity_b,
			   1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( 
			unit_aware_dist_b_copy.evaluatePDF( indep_quantity_b ),
			inv_indep_quantity_b,
			1e-15 );

  Utility::setQuantity( indep_quantity_a, 0.5 );
  Utility::setQuantity( inv_indep_quantity_a, 0.0 );
  Utility::setQuantity( dep_quantity_a, 0.0 );			

  indep_quantity_b = IndepQuantityB( indep_quantity_a );
  Utility::setQuantity( inv_indep_quantity_b, 0.0 );
  dep_quantity_b = DepQuantityB( dep_quantity_a );

  UTILITY_TEST_FLOATING_EQUALITY( 
			   unit_aware_dist_a_copy.evaluate( indep_quantity_a ),
			   dep_quantity_a,
			   1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( 
			unit_aware_dist_a_copy.evaluatePDF( indep_quantity_a ),
			inv_indep_quantity_a,
			1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( 
			   unit_aware_dist_b_copy.evaluate( indep_quantity_b ),
			   dep_quantity_b,
			   1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( 
			unit_aware_dist_b_copy.evaluatePDF( indep_quantity_b ),
			inv_indep_quantity_b,
			1e-15 );
}

typedef si::energy si_energy;
typedef cgs::energy cgs_energy;
typedef si::amount si_amount;
typedef si::length si_length;
typedef cgs::length cgs_length;
typedef si::mass si_mass;
typedef cgs::mass cgs_mass;
typedef si::dimensionless si_dimensionless;
typedef cgs::dimensionless cgs_dimensionless;

TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      si_energy,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      cgs_energy,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      si_energy,
				      si_length,
				      cgs_energy,
				      cgs_length );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      cgs_energy,
				      cgs_length,
				      si_energy,
				      si_length );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      si_energy,
				      si_mass,
				      cgs_energy,
				      cgs_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      cgs_energy,
				      cgs_mass,
				      si_energy,
				      si_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      si_energy,
				      si_dimensionless,
				      cgs_energy,
				      cgs_dimensionless );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      cgs_energy,
				      cgs_dimensionless,
				      si_energy,
				      si_dimensionless );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      si_energy,
				      void,
				      cgs_energy,
				      void );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      cgs_energy,
				      void,
				      si_energy,
				      void );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      KiloElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      MegaElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      ElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      MegaElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      ElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      KiloElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDiscreteDistribution,
				      explicit_conversion,
				      void,
				      MegaElectronVolt,
				      void,
				      KiloElectronVolt );

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be read from an xml file
TEUCHOS_UNIT_TEST( UnitAwareDiscreteDistribution, fromParameterList )
{
  typedef Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount> UnitAwareDiscreteDistribution;
  
  UnitAwareDiscreteDistribution xml_distribution = 
    test_dists_list->get<UnitAwareDiscreteDistribution>( "Unit-Aware Discrete Distribution A" );
  
  TEST_EQUALITY_CONST( xml_distribution.getLowerBoundOfIndepVar(), 0.1*eV );
  TEST_EQUALITY_CONST( xml_distribution.getUpperBoundOfIndepVar(), 10.0*eV );
  UTILITY_TEST_FLOATING_EQUALITY( xml_distribution.evaluatePDF( 0.1*eV ), 
				  0.2/eV,
				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( xml_distribution.evaluatePDF( 1.0*eV ), 
				  0.6/eV,
				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( xml_distribution.evaluatePDF( 10.0*eV ), 
				  0.2/eV,
				  1e-15 );

  xml_distribution = 
    test_dists_list->get<UnitAwareDiscreteDistribution>( "Unit-Aware Discrete Distribution B" );

  TEST_EQUALITY_CONST( xml_distribution.getLowerBoundOfIndepVar(), 
		       Utility::PhysicalConstants::pi/2*eV );
  TEST_EQUALITY_CONST( xml_distribution.getUpperBoundOfIndepVar(),
		       Utility::PhysicalConstants::pi*eV );
  UTILITY_TEST_FLOATING_EQUALITY( xml_distribution.evaluatePDF( Utility::PhysicalConstants::pi/2*eV ),
			  0.2/eV,
			  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( xml_distribution.evaluatePDF( Utility::PhysicalConstants::pi*eV ),
			  0.2/eV,
			  1e-15 );
}



//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_dists_xml_file;
  
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();
  
  clp.setOption( "test_dists_xml_file",
		 &test_dists_xml_file,
		 "Test distributions xml file name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  TEUCHOS_ADD_TYPE_CONVERTER( Utility::DiscreteDistribution );
  typedef Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount> UnitAwareDiscreteDistribution;
  TEUCHOS_ADD_TYPE_CONVERTER( UnitAwareDiscreteDistribution );
  
  test_dists_list = Teuchos::getParametersFromXmlFile( test_dists_xml_file );

  // Create a distribution using the standard constructor
  Teuchos::Array<double> independent_values( 3 );
  independent_values[0] = -1.0;
  independent_values[1] = 0.0;
  independent_values[2] = 1.0;
  
  Teuchos::Array<double> dependent_values( 3 );
  dependent_values[0] = 1.0;
  dependent_values[1] = 2.0;
  dependent_values[2] = 1.0;
  
  tab_distribution.reset( 
		      new Utility::DiscreteDistribution( independent_values,
							 dependent_values ) );

  distribution = tab_distribution;
  
  // Create a distribution using the cdf constructor
  Teuchos::Array<double> cdf_values( 3 );
  cdf_values[0] = 0.25;
  cdf_values[1] = 0.75;
  cdf_values[2] = 1.0;

  tab_cdf_cons_distribution.reset( new Utility::DiscreteDistribution(
							  independent_values,
							  cdf_values,
							  true ) );

  cdf_cons_distribution = tab_cdf_cons_distribution;

  // Create a distribution with repeated values
  independent_values.resize( 5 );
  independent_values[0] = -1.0;
  independent_values[1] = -1.0;
  independent_values[2] = 0.0;
  independent_values[3] = 1.0;
  independent_values[4] = 1.0;

  dependent_values.resize( 5 );
  dependent_values[0] = 0.25;
  dependent_values[1] = 0.75;
  dependent_values[2] = 2.0;
  dependent_values[3] = 0.75;
  dependent_values[4] = 0.25;

  tab_repeat_vals_distribution.reset( new Utility::DiscreteDistribution(
							  independent_values,
							  dependent_values ) );

  repeat_vals_distribution = tab_repeat_vals_distribution;

  // Create a unit aware distribution using quantities
  Teuchos::Array<quantity<ElectronVolt> > independent_quantities( 4 );
  independent_quantities[0] = 0.1*eV;
  independent_quantities[1] = 1.0*eV;
  independent_quantities[2] = 5.0*eV;
  independent_quantities[3] = quantity<ElectronVolt>( 1.0*keV );

  Teuchos::Array<quantity<si::amount> > dependent_quantities( 4 );
  dependent_quantities[0] = 0.25*si::mole;
  dependent_quantities[1] = 1.0*si::mole;
  dependent_quantities[2] = 2.7*si::mole;
  dependent_quantities[3] = 0.05*si::mole;
  
  unit_aware_tab_distribution.reset( 
	   new Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount>(
  						      independent_quantities,
  						      dependent_quantities ) );

  unit_aware_distribution = unit_aware_tab_distribution;

  // Create a unit aware distribution using quantities and the cdf constructor
  dependent_values.resize( 4 );
  dependent_values[0] = 0.0625;
  dependent_values[1] = 0.3125;
  dependent_values[2] = 0.9875;
  dependent_values[3] = 1.0;

  unit_aware_tab_cdf_cons_distribution.reset(
	   new Utility::UnitAwareDiscreteDistribution<ElectronVolt,si::amount>(
  							independent_quantities,
  							dependent_values ) );

  unit_aware_cdf_cons_distribution = unit_aware_tab_cdf_cons_distribution;
  
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
  
  // Run the unit tests
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  const bool success = Teuchos::UnitTestRepository::runUnitTests(*out);

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstDiscreteDistribution.cpp
//---------------------------------------------------------------------------//
