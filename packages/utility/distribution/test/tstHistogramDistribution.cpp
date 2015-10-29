//---------------------------------------------------------------------------//
//!
//! \file   tstHistogramDistribution.cpp
//! \author Alex Robinson
//! \brief  Histogram distribution unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

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
#include "Utility_HistogramDistribution.hpp"
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

Teuchos::RCP<Utility::OneDDistribution> pdf_distribution;
Teuchos::RCP<Utility::TabularOneDDistribution> tab_pdf_distribution;

Teuchos::RCP<Utility::UnitAwareOneDDistribution<MegaElectronVolt,si::amount> >
  unit_aware_pdf_distribution;
Teuchos::RCP<Utility::UnitAwareTabularOneDDistribution<MegaElectronVolt,si::amount> >
  unit_aware_tab_pdf_distribution;


Teuchos::RCP<Utility::OneDDistribution> cdf_distribution;
Teuchos::RCP<Utility::TabularOneDDistribution> tab_cdf_distribution;

Teuchos::RCP<Utility::UnitAwareOneDDistribution<MegaElectronVolt,si::amount> >
  unit_aware_cdf_distribution;
Teuchos::RCP<Utility::UnitAwareTabularOneDDistribution<MegaElectronVolt,si::amount> >
  unit_aware_tab_cdf_distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( HistogramDistribution, evalute )
{
  TEST_EQUALITY_CONST( pdf_distribution->evaluate( -3.0 ), 0.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluate( -2.0 ), 2.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluate( -1.5 ), 2.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluate( -1.0 ), 1.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluate( 0.0 ), 1.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluate( 1.0 ), 2.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluate( 1.5 ), 2.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluate( 2.0 ), 2.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluate( 3.0 ), 0.0 );

  TEST_EQUALITY_CONST( cdf_distribution->evaluate( -3.0 ), 0.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluate( -2.0 ), 2.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluate( -1.5 ), 2.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluate( -1.0 ), 1.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluate( 0.0 ), 1.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluate( 1.0 ), 2.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluate( 1.5 ), 2.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluate( 2.0 ), 2.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluate( 3.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareHistogramDistribution, evalute )
{
  TEST_EQUALITY_CONST( unit_aware_pdf_distribution->evaluate( -3.0*MeV ), 
		       0.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_pdf_distribution->evaluate( -2.0*MeV ), 
		       2.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_pdf_distribution->evaluate( -1.5*MeV ), 
		       2.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_pdf_distribution->evaluate( -1.0*MeV ), 
		       1.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_pdf_distribution->evaluate( 0.0*MeV ), 
		       1.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_pdf_distribution->evaluate( 1.0*MeV ), 
		       2.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_pdf_distribution->evaluate( 1.5*MeV ), 
		       2.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_pdf_distribution->evaluate( 2.0*MeV ), 
		       2.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_pdf_distribution->evaluate( 3.0*MeV ), 
		       0.0*si::mole );

  TEST_EQUALITY_CONST( unit_aware_cdf_distribution->evaluate( -3.0*MeV ), 
		       0.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_cdf_distribution->evaluate( -2.0*MeV ), 
		       2.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_cdf_distribution->evaluate( -1.5*MeV ), 
		       2.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_cdf_distribution->evaluate( -1.0*MeV ), 
		       1.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_cdf_distribution->evaluate( 0.0*MeV ), 
		       1.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_cdf_distribution->evaluate( 1.0*MeV ), 
		       2.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_cdf_distribution->evaluate( 1.5*MeV ), 
		       2.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_cdf_distribution->evaluate( 2.0*MeV ), 
		       2.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_cdf_distribution->evaluate( 3.0*MeV ), 
		       0.0*si::mole);
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( HistogramDistribution, evaluatePDF )
{
  TEST_EQUALITY_CONST( pdf_distribution->evaluatePDF( -3.0 ), 0.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluatePDF( -2.0 ), 1.0/3.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluatePDF( -1.5 ), 1.0/3.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluatePDF( -1.0 ), 1.0/6.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluatePDF( 0.0 ), 1.0/6.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluatePDF( 1.0 ), 1.0/3.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluatePDF( 1.5 ), 1.0/3.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluatePDF( 2.0 ), 1.0/3.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluatePDF( 3.0 ), 0.0 );

  TEST_EQUALITY_CONST( cdf_distribution->evaluatePDF( -3.0 ), 0.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluatePDF( -2.0 ), 1.0/3.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluatePDF( -1.5 ), 1.0/3.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluatePDF( -1.0 ), 1.0/6.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluatePDF( 0.0 ), 1.0/6.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluatePDF( 1.0 ), 1.0/3.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluatePDF( 1.5 ), 1.0/3.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluatePDF( 2.0 ), 1.0/3.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluatePDF( 3.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareHistogramDistribution, evaluatePDF )
{
  TEST_EQUALITY_CONST( unit_aware_pdf_distribution->evaluatePDF( -3.0*MeV ), 
		       0.0/MeV );
  TEST_EQUALITY_CONST( unit_aware_pdf_distribution->evaluatePDF( -2.0*MeV ), 
		       (1.0/3.0)/MeV );
  TEST_EQUALITY_CONST( unit_aware_pdf_distribution->evaluatePDF( -1.5*MeV ), 
		       (1.0/3.0)/MeV );
  TEST_EQUALITY_CONST( unit_aware_pdf_distribution->evaluatePDF( -1.0*MeV ), 
		       (1.0/6.0)/MeV );
  TEST_EQUALITY_CONST( unit_aware_pdf_distribution->evaluatePDF( 0.0*MeV ), 
		       (1.0/6.0)/MeV );
  TEST_EQUALITY_CONST( unit_aware_pdf_distribution->evaluatePDF( 1.0*MeV ), 
		       (1.0/3.0)/MeV );
  TEST_EQUALITY_CONST( unit_aware_pdf_distribution->evaluatePDF( 1.5*MeV ), 
		       (1.0/3.0)/MeV );
  TEST_EQUALITY_CONST( unit_aware_pdf_distribution->evaluatePDF( 2.0*MeV ), 
		       (1.0/3.0)/MeV );
  TEST_EQUALITY_CONST( unit_aware_pdf_distribution->evaluatePDF( 3.0*MeV ), 
		       0.0/MeV );

  TEST_EQUALITY_CONST( unit_aware_cdf_distribution->evaluatePDF( -3.0*MeV ), 
		       0.0/MeV );
  TEST_EQUALITY_CONST( unit_aware_cdf_distribution->evaluatePDF( -2.0*MeV ), 
		       (1.0/3.0)/MeV );
  TEST_EQUALITY_CONST( unit_aware_cdf_distribution->evaluatePDF( -1.5*MeV ), 
		       (1.0/3.0)/MeV );
  TEST_EQUALITY_CONST( unit_aware_cdf_distribution->evaluatePDF( -1.0*MeV ), 
		       (1.0/6.0)/MeV );
  TEST_EQUALITY_CONST( unit_aware_cdf_distribution->evaluatePDF( 0.0*MeV ), 
		       (1.0/6.0)/MeV );
  TEST_EQUALITY_CONST( unit_aware_cdf_distribution->evaluatePDF( 1.0*MeV ), 
		       (1.0/3.0)/MeV );
  TEST_EQUALITY_CONST( unit_aware_cdf_distribution->evaluatePDF( 1.5*MeV ), 
		       (1.0/3.0)/MeV );
  TEST_EQUALITY_CONST( unit_aware_cdf_distribution->evaluatePDF( 2.0*MeV ), 
		       (1.0/3.0)/MeV );
  TEST_EQUALITY_CONST( unit_aware_cdf_distribution->evaluatePDF( 3.0*MeV ), 
		       0.0/MeV );
}

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated
TEUCHOS_UNIT_TEST( HistogramDistribution, evaluateCDF )
{
  TEST_EQUALITY_CONST( tab_pdf_distribution->evaluateCDF(-3.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_pdf_distribution->evaluateCDF(-2.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_pdf_distribution->evaluateCDF(-1.5 ), 1.0/6.0, 1e-14 );
  TEST_EQUALITY_CONST( tab_pdf_distribution->evaluateCDF(-1.0 ), 1.0/3.0 );
  TEST_FLOATING_EQUALITY( tab_pdf_distribution->evaluateCDF( 0.0 ), 0.5, 1e-14 );
  TEST_EQUALITY_CONST( tab_pdf_distribution->evaluateCDF( 1.0 ), 2.0/3.0 );
  TEST_FLOATING_EQUALITY( tab_pdf_distribution->evaluateCDF( 1.5 ), 5.0/6.0, 1e-14 );
  TEST_EQUALITY_CONST( tab_pdf_distribution->evaluateCDF( 2.0 ), 1.0 );
  TEST_EQUALITY_CONST( tab_pdf_distribution->evaluateCDF( 3.0 ), 1.0 );

  TEST_EQUALITY_CONST( tab_cdf_distribution->evaluateCDF(-3.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_cdf_distribution->evaluateCDF(-2.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_cdf_distribution->evaluateCDF(-1.5 ), 1.0/6.0, 1e-14 );
  TEST_EQUALITY_CONST( tab_cdf_distribution->evaluateCDF(-1.0 ), 1.0/3.0 );
  TEST_FLOATING_EQUALITY( tab_cdf_distribution->evaluateCDF( 0.0 ), 0.5, 1e-14 );
  TEST_EQUALITY_CONST( tab_cdf_distribution->evaluateCDF( 1.0 ), 2.0/3.0 );
  TEST_FLOATING_EQUALITY( tab_cdf_distribution->evaluateCDF( 1.5 ), 5.0/6.0, 1e-14 );
  TEST_EQUALITY_CONST( tab_cdf_distribution->evaluateCDF( 2.0 ), 1.0 );
  TEST_EQUALITY_CONST( tab_cdf_distribution->evaluateCDF( 3.0 ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware CDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareHistogramDistribution, evaluateCDF )
{
  TEST_EQUALITY_CONST(unit_aware_tab_pdf_distribution->evaluateCDF( -3.0*MeV ),
		      0.0 );
  TEST_EQUALITY_CONST(unit_aware_tab_pdf_distribution->evaluateCDF( -2.0*MeV ),
		      0.0 );
  TEST_FLOATING_EQUALITY(
		      unit_aware_tab_pdf_distribution->evaluateCDF( -1.5*MeV ),
		      1.0/6.0, 
		      1e-14 );
  TEST_EQUALITY_CONST(unit_aware_tab_pdf_distribution->evaluateCDF( -1.0*MeV ),
		      1.0/3.0 );
  TEST_FLOATING_EQUALITY(
		       unit_aware_tab_pdf_distribution->evaluateCDF( 0.0*MeV ),
		       0.5, 
		       1e-14 );
  TEST_EQUALITY_CONST( unit_aware_tab_pdf_distribution->evaluateCDF( 1.0*MeV ),
		       2.0/3.0 );
  TEST_FLOATING_EQUALITY( 
		       unit_aware_tab_pdf_distribution->evaluateCDF( 1.5*MeV ),
		       5.0/6.0, 
		       1e-14 );
  TEST_EQUALITY_CONST( unit_aware_tab_pdf_distribution->evaluateCDF( 2.0*MeV ),
		       1.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_pdf_distribution->evaluateCDF( 3.0*MeV ),
		       1.0 );

  TEST_EQUALITY_CONST(unit_aware_tab_cdf_distribution->evaluateCDF( -3.0*MeV ),
		      0.0 );
  TEST_EQUALITY_CONST(unit_aware_tab_cdf_distribution->evaluateCDF( -2.0*MeV ),
		      0.0 );
  TEST_FLOATING_EQUALITY(
		      unit_aware_tab_cdf_distribution->evaluateCDF( -1.5*MeV ),
		      1.0/6.0, 
		      1e-14 );
  TEST_EQUALITY_CONST(unit_aware_tab_cdf_distribution->evaluateCDF( -1.0*MeV ),
		      1.0/3.0 );
  TEST_FLOATING_EQUALITY( 
		       unit_aware_tab_cdf_distribution->evaluateCDF( 0.0*MeV ),
		       0.5, 
		       1e-14 );
  TEST_EQUALITY_CONST( unit_aware_tab_cdf_distribution->evaluateCDF( 1.0*MeV ),
		       2.0/3.0 );
  TEST_FLOATING_EQUALITY( 
		       unit_aware_tab_cdf_distribution->evaluateCDF( 1.5*MeV ),
		       5.0/6.0, 
		       1e-14 );
  TEST_EQUALITY_CONST( unit_aware_tab_cdf_distribution->evaluateCDF( 2.0*MeV ),
		      1.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_cdf_distribution->evaluateCDF( 3.0*MeV ),
		      1.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( HistogramDistribution, sample )
{
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0/6.0;
  fake_stream[2] = 1.0/3.0 - 1e-15;
  fake_stream[3] = 1.0/3.0;
  fake_stream[4] = 0.5;
  fake_stream[5] = 2.0/3.0 - 1e-15;
  fake_stream[6] = 2.0/3.0;
  fake_stream[7] = 5.0/6.0;
  fake_stream[8] = 1.0 - 1e-15;
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  // Test the first bin
  double sample = pdf_distribution->sample();
  TEST_EQUALITY_CONST( sample, -2.0 );
  
  sample = pdf_distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.5 );
  
  sample = pdf_distribution->sample();
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );
    
  // Test the second bin
  sample = pdf_distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  sample = pdf_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0, 1e-14 );
  
  sample = pdf_distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
    
  // Test the third bin
  sample = pdf_distribution->sample();
  TEST_EQUALITY_CONST( sample, 1.0 );
    
  sample = pdf_distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 1.5, 1e-14 );
  
  sample = pdf_distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 2.0, 1e-14 );
  
  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  sample = cdf_distribution->sample();
  TEST_EQUALITY_CONST( sample, -2.0 );
  
  sample = cdf_distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.5 );
  
  sample = cdf_distribution->sample();
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );
    
  // Test the second bin
  sample = cdf_distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  sample = cdf_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0, 1e-14 );
  
  sample = cdf_distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
    
  // Test the third bin
  sample = cdf_distribution->sample();
  TEST_EQUALITY_CONST( sample, 1.0 );
    
  sample = cdf_distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 1.5, 1e-14 );
  
  sample = cdf_distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 2.0, 1e-14 );
  
  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareHistogramDistribution, sample )
{
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0/6.0;
  fake_stream[2] = 1.0/3.0 - 1e-15;
  fake_stream[3] = 1.0/3.0;
  fake_stream[4] = 0.5;
  fake_stream[5] = 2.0/3.0 - 1e-15;
  fake_stream[6] = 2.0/3.0;
  fake_stream[7] = 5.0/6.0;
  fake_stream[8] = 1.0 - 1e-15;
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  // Test the first bin
  quantity<MegaElectronVolt> sample = unit_aware_pdf_distribution->sample();
  TEST_EQUALITY_CONST( sample, -2.0*MeV );
  
  sample = unit_aware_pdf_distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.5*MeV );
  
  sample = unit_aware_pdf_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample, -1.0*MeV, 1e-14 );
    
  // Test the second bin
  sample = unit_aware_pdf_distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.0*MeV );
  
  sample = unit_aware_pdf_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0*MeV, 1e-14 );
  
  sample = unit_aware_pdf_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-14 );
    
  // Test the third bin
  sample = unit_aware_pdf_distribution->sample();
  TEST_EQUALITY_CONST( sample, 1.0*MeV );
    
  sample = unit_aware_pdf_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.5*MeV, 1e-14 );
  
  sample = unit_aware_pdf_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample, 2.0*MeV, 1e-14 );
  
  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  sample = unit_aware_cdf_distribution->sample();
  TEST_EQUALITY_CONST( sample, -2.0*MeV );
  
  sample = unit_aware_cdf_distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.5*MeV );
  
  sample = unit_aware_cdf_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample, -1.0*MeV, 1e-14 );
    
  // Test the second bin
  sample = unit_aware_cdf_distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.0*MeV );
  
  sample = unit_aware_cdf_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0*MeV, 1e-14 );
  
  sample = unit_aware_cdf_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-14 );
    
  // Test the third bin
  sample = unit_aware_cdf_distribution->sample();
  TEST_EQUALITY_CONST( sample, 1.0*MeV );
    
  sample = unit_aware_cdf_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.5*MeV, 1e-14 );
  
  sample = unit_aware_cdf_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample, 2.0*MeV, 1e-14 );
  
  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( HistogramDistribution, sampleAndRecordTrials )
{
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0/6.0;
  fake_stream[2] = 1.0/3.0 - 1e-15;
  fake_stream[3] = 1.0/3.0;
  fake_stream[4] = 0.5;
  fake_stream[5] = 2.0/3.0 - 1e-15;
  fake_stream[6] = 2.0/3.0;
  fake_stream[7] = 5.0/6.0;
  fake_stream[8] = 1.0 - 1e-15;
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned trials = 0;
  
  // Test the first bin
  double sample = pdf_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -2.0 );
  TEST_EQUALITY_CONST( trials, 1 );
  
  sample = pdf_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.5 );
  TEST_EQUALITY_CONST( trials, 2 );
  
  sample = pdf_distribution->sampleAndRecordTrials( trials );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );
  TEST_EQUALITY_CONST( trials, 3 );
    
  // Test the second bin
  sample = pdf_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( trials, 4 );
  
  sample = pdf_distribution->sampleAndRecordTrials( trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0, 1e-14 );
  TEST_EQUALITY_CONST( trials, 5 );
  
  sample = pdf_distribution->sampleAndRecordTrials( trials );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  TEST_EQUALITY_CONST( trials, 6 );
    
  // Test the third bin
  sample = pdf_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( trials, 7 );
    
  sample = pdf_distribution->sampleAndRecordTrials( trials );
  TEST_FLOATING_EQUALITY( sample, 1.5, 1e-14 );
  TEST_EQUALITY_CONST( trials, 8 );
  
  sample = pdf_distribution->sampleAndRecordTrials( trials );
  TEST_FLOATING_EQUALITY( sample, 2.0, 1e-14 );
  TEST_EQUALITY_CONST( trials, 9 );
  
  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0;

  // Test the first bin
  sample = cdf_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -2.0 );
  TEST_EQUALITY_CONST( trials, 1 );
  
  sample = cdf_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.5 );
  TEST_EQUALITY_CONST( trials, 2 );
  
  sample = cdf_distribution->sampleAndRecordTrials( trials );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );
  TEST_EQUALITY_CONST( trials, 3 );
    
  // Test the second bin
  sample = cdf_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( trials, 4 );
  
  sample = cdf_distribution->sampleAndRecordTrials( trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0, 1e-14 );
  TEST_EQUALITY_CONST( trials, 5 );
  
  sample = cdf_distribution->sampleAndRecordTrials( trials );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  TEST_EQUALITY_CONST( trials, 6 );
    
  // Test the third bin
  sample = cdf_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( trials, 7 );
    
  sample = cdf_distribution->sampleAndRecordTrials( trials );
  TEST_FLOATING_EQUALITY( sample, 1.5, 1e-14 );
  TEST_EQUALITY_CONST( trials, 8 );
  
  sample = cdf_distribution->sampleAndRecordTrials( trials );
  TEST_FLOATING_EQUALITY( sample, 2.0, 1e-14 );
  TEST_EQUALITY_CONST( trials, 9 );
  
  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareHistogramDistribution, sampleAndRecordTrials )
{
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0/6.0;
  fake_stream[2] = 1.0/3.0 - 1e-15;
  fake_stream[3] = 1.0/3.0;
  fake_stream[4] = 0.5;
  fake_stream[5] = 2.0/3.0 - 1e-15;
  fake_stream[6] = 2.0/3.0;
  fake_stream[7] = 5.0/6.0;
  fake_stream[8] = 1.0 - 1e-15;
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned trials = 0;
  
  // Test the first bin
  quantity<MegaElectronVolt> sample = 
    unit_aware_pdf_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -2.0*MeV );
  TEST_EQUALITY_CONST( trials, 1 );
  
  sample = unit_aware_pdf_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.5*MeV );
  TEST_EQUALITY_CONST( trials, 2 );
  
  sample = unit_aware_pdf_distribution->sampleAndRecordTrials( trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -1.0*MeV, 1e-14 );
  TEST_EQUALITY_CONST( trials, 3 );
    
  // Test the second bin
  sample = unit_aware_pdf_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.0*MeV );
  TEST_EQUALITY_CONST( trials, 4 );
  
  sample = unit_aware_pdf_distribution->sampleAndRecordTrials( trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0*MeV, 1e-14 );
  TEST_EQUALITY_CONST( trials, 5 );
  
  sample = unit_aware_pdf_distribution->sampleAndRecordTrials( trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-14 );
  TEST_EQUALITY_CONST( trials, 6 );
    
  // Test the third bin
  sample = unit_aware_pdf_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1.0*MeV );
  TEST_EQUALITY_CONST( trials, 7 );
    
  sample = unit_aware_pdf_distribution->sampleAndRecordTrials( trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.5*MeV, 1e-14 );
  TEST_EQUALITY_CONST( trials, 8 );
  
  sample = unit_aware_pdf_distribution->sampleAndRecordTrials( trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 2.0*MeV, 1e-14 );
  TEST_EQUALITY_CONST( trials, 9 );
  
  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0;

  // Test the first bin
  sample = unit_aware_cdf_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -2.0*MeV );
  TEST_EQUALITY_CONST( trials, 1 );
  
  sample = unit_aware_cdf_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.5*MeV );
  TEST_EQUALITY_CONST( trials, 2 );
  
  sample = unit_aware_cdf_distribution->sampleAndRecordTrials( trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -1.0*MeV, 1e-14 );
  TEST_EQUALITY_CONST( trials, 3 );
    
  // Test the second bin
  sample = unit_aware_cdf_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.0*MeV );
  TEST_EQUALITY_CONST( trials, 4 );
  
  sample = unit_aware_cdf_distribution->sampleAndRecordTrials( trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0*MeV, 1e-14 );
  TEST_EQUALITY_CONST( trials, 5 );
  
  sample = unit_aware_cdf_distribution->sampleAndRecordTrials( trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-14 );
  TEST_EQUALITY_CONST( trials, 6 );
    
  // Test the third bin
  sample = unit_aware_cdf_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1.0*MeV );
  TEST_EQUALITY_CONST( trials, 7 );
    
  sample = unit_aware_cdf_distribution->sampleAndRecordTrials( trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.5*MeV, 1e-14 );
  TEST_EQUALITY_CONST( trials, 8 );
  
  sample = unit_aware_cdf_distribution->sampleAndRecordTrials( trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 2.0*MeV, 1e-14 );
  TEST_EQUALITY_CONST( trials, 9 );
  
  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( HistogramDistribution, sampleAndRecordBinIndex )
{
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0/6.0;
  fake_stream[2] = 1.0/3.0 - 1e-15;
  fake_stream[3] = 1.0/3.0;
  fake_stream[4] = 0.5;
  fake_stream[5] = 2.0/3.0 - 1e-15;
  fake_stream[6] = 2.0/3.0;
  fake_stream[7] = 5.0/6.0;
  fake_stream[8] = 1.0 - 1e-15;
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned bin_index;

  // Test the first bin
  double sample = tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -2.0 );
  TEST_EQUALITY_CONST( bin_index, 0u );

  sample = tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.5 );
  TEST_EQUALITY_CONST( bin_index, 0u );  

  sample = tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 0u );
  
  // Test the second bin
  sample = tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( bin_index, 1u );

  sample = tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 1u );

  sample = tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 1u );
  
  // Test the third bin
  sample = tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( bin_index, 2u );
  
  sample = tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_FLOATING_EQUALITY( sample, 1.5, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  sample = tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_FLOATING_EQUALITY( sample, 2.0, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  sample = tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -2.0 );
  TEST_EQUALITY_CONST( bin_index, 0u );

  sample = tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.5 );
  TEST_EQUALITY_CONST( bin_index, 0u );  

  sample = tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 0u );
  
  // Test the second bin
  sample = tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( bin_index, 1u );

  sample = tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 1u );

  sample = tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 1u );
  
  // Test the third bin
  sample = tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( bin_index, 2u );
  
  sample = tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_FLOATING_EQUALITY( sample, 1.5, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  sample = tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_FLOATING_EQUALITY( sample, 2.0, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareHistogramDistribution, sampleAndRecordBinIndex )
{
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0/6.0;
  fake_stream[2] = 1.0/3.0 - 1e-15;
  fake_stream[3] = 1.0/3.0;
  fake_stream[4] = 0.5;
  fake_stream[5] = 2.0/3.0 - 1e-15;
  fake_stream[6] = 2.0/3.0;
  fake_stream[7] = 5.0/6.0;
  fake_stream[8] = 1.0 - 1e-15;
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned bin_index;

  // Test the first bin
  quantity<MegaElectronVolt> sample = 
    unit_aware_tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -2.0*MeV );
  TEST_EQUALITY_CONST( bin_index, 0u );

  sample = 
    unit_aware_tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.5*MeV );
  TEST_EQUALITY_CONST( bin_index, 0u );  

  sample = 
    unit_aware_tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -1.0*MeV, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 0u );
  
  // Test the second bin
  sample = 
    unit_aware_tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0*MeV );
  TEST_EQUALITY_CONST( bin_index, 1u );

  sample = 
    unit_aware_tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0*MeV, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 1u );

  sample = 
    unit_aware_tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 1u );
  
  // Test the third bin
  sample = 
    unit_aware_tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1.0*MeV );
  TEST_EQUALITY_CONST( bin_index, 2u );
  
  sample = 
    unit_aware_tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.5*MeV, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  sample = 
    unit_aware_tab_pdf_distribution->sampleAndRecordBinIndex( bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 2.0*MeV, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  sample = 
    unit_aware_tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -2.0*MeV );
  TEST_EQUALITY_CONST( bin_index, 0u );

  sample = 
    unit_aware_tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.5*MeV );
  TEST_EQUALITY_CONST( bin_index, 0u );  

  sample = 
    unit_aware_tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -1.0*MeV, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 0u );
  
  // Test the second bin
  sample = 
    unit_aware_tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0*MeV );
  TEST_EQUALITY_CONST( bin_index, 1u );

  sample = 
    unit_aware_tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0*MeV, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 1u );

  sample = 
    unit_aware_tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 1u );
  
  // Test the third bin
  sample = 
    unit_aware_tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1.0*MeV );
  TEST_EQUALITY_CONST( bin_index, 2u );
  
  sample = 
    unit_aware_tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.5*MeV, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  sample = 
    unit_aware_tab_cdf_distribution->sampleAndRecordBinIndex( bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 2.0*MeV, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( HistogramDistribution, sampleWithRandomNumber )
{
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0/6.0;
  fake_stream[2] = 1.0/3.0 - 1e-15;
  fake_stream[3] = 1.0/3.0;
  fake_stream[4] = 0.5;
  fake_stream[5] = 2.0/3.0 - 1e-15;
  fake_stream[6] = 2.0/3.0;
  fake_stream[7] = 5.0/6.0;
  fake_stream[8] = 1.0 - 1e-15;
  
  // Test the first bin
  double sample = tab_pdf_distribution->sampleWithRandomNumber( 0.0 );
  TEST_EQUALITY_CONST( sample, -2.0 );
  
  sample = tab_pdf_distribution->sampleWithRandomNumber( 1.0/6.0 );
  TEST_EQUALITY_CONST( sample, -1.5 );
  
  sample = tab_pdf_distribution->sampleWithRandomNumber( 1.0/3.0 - 1e-15 );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );
    
  // Test the second bin
  sample = tab_pdf_distribution->sampleWithRandomNumber( 1.0/3.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  sample = tab_pdf_distribution->sampleWithRandomNumber( 0.5 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0, 1e-14 );
  
  sample = tab_pdf_distribution->sampleWithRandomNumber( 2.0/3.0 - 1e-15 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
    
  // Test the third bin
  sample = tab_pdf_distribution->sampleWithRandomNumber( 2.0/3.0 );
  TEST_EQUALITY_CONST( sample, 1.0 );
    
  sample = tab_pdf_distribution->sampleWithRandomNumber( 5.0/6.0 );
  TEST_FLOATING_EQUALITY( sample, 1.5, 1e-14 );
  
  sample = tab_pdf_distribution->sampleWithRandomNumber( 1.0 - 1e-15 );
  TEST_FLOATING_EQUALITY( sample, 2.0, 1e-14 );
  
  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  sample = tab_cdf_distribution->sampleWithRandomNumber( 0.0 );
  TEST_EQUALITY_CONST( sample, -2.0 );
  
  sample = tab_cdf_distribution->sampleWithRandomNumber( 1.0/6.0 );
  TEST_EQUALITY_CONST( sample, -1.5 );
  
  sample = tab_cdf_distribution->sampleWithRandomNumber( 1.0/3.0 - 1e-15 );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );
    
  // Test the second bin
  sample = tab_cdf_distribution->sampleWithRandomNumber( 1.0/3.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );
  
  sample = tab_cdf_distribution->sampleWithRandomNumber( 0.5 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0, 1e-14 );
  
  sample = tab_cdf_distribution->sampleWithRandomNumber( 2.0/3.0 - 1e-15 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
    
  // Test the third bin
  sample = tab_cdf_distribution->sampleWithRandomNumber( 2.0/3.0 );
  TEST_EQUALITY_CONST( sample, 1.0 );
    
  sample = tab_cdf_distribution->sampleWithRandomNumber( 5.0/6.0 );
  TEST_FLOATING_EQUALITY( sample, 1.5, 1e-14 );
  
  sample = tab_cdf_distribution->sampleWithRandomNumber( 1.0 - 1e-15 );
  TEST_FLOATING_EQUALITY( sample, 2.0, 1e-14 );
  
  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareHistogramDistribution, sampleWithRandomNumber )
{
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0/6.0;
  fake_stream[2] = 1.0/3.0 - 1e-15;
  fake_stream[3] = 1.0/3.0;
  fake_stream[4] = 0.5;
  fake_stream[5] = 2.0/3.0 - 1e-15;
  fake_stream[6] = 2.0/3.0;
  fake_stream[7] = 5.0/6.0;
  fake_stream[8] = 1.0 - 1e-15;
  
  // Test the first bin
  quantity<MegaElectronVolt> sample = 
    unit_aware_tab_pdf_distribution->sampleWithRandomNumber( 0.0 );
  TEST_EQUALITY_CONST( sample, -2.0*MeV );
  
  sample = unit_aware_tab_pdf_distribution->sampleWithRandomNumber( 1.0/6.0 );
  TEST_EQUALITY_CONST( sample, -1.5*MeV );
  
  sample = 
    unit_aware_tab_pdf_distribution->sampleWithRandomNumber( 1.0/3.0 - 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -1.0*MeV, 1e-14 );
    
  // Test the second bin
  sample = unit_aware_tab_pdf_distribution->sampleWithRandomNumber( 1.0/3.0 );
  TEST_EQUALITY_CONST( sample, -1.0*MeV );
  
  sample = unit_aware_tab_pdf_distribution->sampleWithRandomNumber( 0.5 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0*MeV, 1e-14 );
  
  sample = 
    unit_aware_tab_pdf_distribution->sampleWithRandomNumber( 2.0/3.0 - 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-14 );
    
  // Test the third bin
  sample = unit_aware_tab_pdf_distribution->sampleWithRandomNumber( 2.0/3.0 );
  TEST_EQUALITY_CONST( sample, 1.0*MeV );
    
  sample = unit_aware_tab_pdf_distribution->sampleWithRandomNumber( 5.0/6.0 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.5*MeV, 1e-14 );
  
  sample = 
    unit_aware_tab_pdf_distribution->sampleWithRandomNumber( 1.0 - 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 2.0*MeV, 1e-14 );
  
  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  sample = unit_aware_tab_cdf_distribution->sampleWithRandomNumber( 0.0 );
  TEST_EQUALITY_CONST( sample, -2.0*MeV );
  
  sample = unit_aware_tab_cdf_distribution->sampleWithRandomNumber( 1.0/6.0 );
  TEST_EQUALITY_CONST( sample, -1.5*MeV );
  
  sample = 
    unit_aware_tab_cdf_distribution->sampleWithRandomNumber( 1.0/3.0 - 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, -1.0*MeV, 1e-14 );
    
  // Test the second bin
  sample = unit_aware_tab_cdf_distribution->sampleWithRandomNumber( 1.0/3.0 );
  TEST_EQUALITY_CONST( sample, -1.0*MeV );
  
  sample = unit_aware_tab_cdf_distribution->sampleWithRandomNumber( 0.5 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0*MeV, 1e-14 );
  
  sample = 
    unit_aware_tab_cdf_distribution->sampleWithRandomNumber( 2.0/3.0 - 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-14 );
    
  // Test the third bin
  sample = 
    unit_aware_tab_cdf_distribution->sampleWithRandomNumber( 2.0/3.0 );
  TEST_EQUALITY_CONST( sample, 1.0*MeV );
    
  sample = 
    unit_aware_tab_cdf_distribution->sampleWithRandomNumber( 5.0/6.0 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.5*MeV, 1e-14 );
  
  sample = 
    unit_aware_tab_cdf_distribution->sampleWithRandomNumber( 1.0 - 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 2.0*MeV, 1e-14 );
  
  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
//Check that the distribution can be sampled from a subrange
TEUCHOS_UNIT_TEST( HistogramDistribution, sampleInSubrange )
{
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15 ;
  fake_stream[3] = 0.0;
  fake_stream[4] = 0.5;
  fake_stream[5] = 1.0 - 1e-15;
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // PDF Histogram: test max independent value 2nd bin
  double sample = tab_pdf_distribution->sampleInSubrange( -1.0 );
  TEST_FLOATING_EQUALITY( sample, -2.0, 1e-14 );

  sample = tab_pdf_distribution->sampleInSubrange( -1.0 );
  TEST_FLOATING_EQUALITY( sample, -1.5, 1e-14 ); 

  sample = tab_pdf_distribution->sampleInSubrange( -1.0 );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );
  
  // PDF Histogram: test max independent value 3rd bin
  sample = tab_pdf_distribution->sampleInSubrange( 1.0 );
  TEST_FLOATING_EQUALITY( sample, -2.0, 1e-14 );

  sample = tab_pdf_distribution->sampleInSubrange( 1.0 );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 ); 

  sample = tab_pdf_distribution->sampleInSubrange( 1.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // CDF Histogram: test max independent value 2nd bin
  sample = tab_cdf_distribution->sampleInSubrange( -1.0 );
  TEST_FLOATING_EQUALITY( sample, -2.0, 1e-14 );

  sample = tab_cdf_distribution->sampleInSubrange( -1.0 );
  TEST_FLOATING_EQUALITY( sample, -1.5, 1e-14 );

  sample = tab_cdf_distribution->sampleInSubrange( -1.0 );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );
  
  // CDF Histogram: test max independent value 3rd bin
  sample = tab_cdf_distribution->sampleInSubrange( 1.0 );
  TEST_FLOATING_EQUALITY( sample, -2.0, 1e-14 );

  sample = tab_cdf_distribution->sampleInSubrange( 1.0 );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );

  sample = tab_cdf_distribution->sampleInSubrange( 1.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled from a subrange
TEUCHOS_UNIT_TEST( UnitAwareHistogramDistribution, sampleInSubrange )
{
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15 ;
  fake_stream[3] = 0.0;
  fake_stream[4] = 0.5;
  fake_stream[5] = 1.0 - 1e-15;
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // PDF Histogram: test max independent value 2nd bin
  quantity<MegaElectronVolt> sample = 
    unit_aware_tab_pdf_distribution->sampleInSubrange( -1.0*MeV );
  TEST_FLOATING_EQUALITY( sample, -2.0, 1e-14 );

  sample = tab_pdf_distribution->sampleInSubrange( -1.0 );
  TEST_FLOATING_EQUALITY( sample, -1.5, 1e-14 ); 

  sample = tab_pdf_distribution->sampleInSubrange( -1.0 );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );
  
  // PDF Histogram: test max independent value 3rd bin
  sample = tab_pdf_distribution->sampleInSubrange( 1.0 );
  TEST_FLOATING_EQUALITY( sample, -2.0, 1e-14 );

  sample = tab_pdf_distribution->sampleInSubrange( 1.0 );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 ); 

  sample = tab_pdf_distribution->sampleInSubrange( 1.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // CDF Histogram: test max independent value 2nd bin
  sample = tab_cdf_distribution->sampleInSubrange( -1.0 );
  TEST_FLOATING_EQUALITY( sample, -2.0, 1e-14 );

  sample = tab_cdf_distribution->sampleInSubrange( -1.0 );
  TEST_FLOATING_EQUALITY( sample, -1.5, 1e-14 );

  sample = tab_cdf_distribution->sampleInSubrange( -1.0 );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );
  
  // CDF Histogram: test max independent value 3rd bin
  sample = tab_cdf_distribution->sampleInSubrange( 1.0 );
  TEST_FLOATING_EQUALITY( sample, -2.0, 1e-14 );

  sample = tab_cdf_distribution->sampleInSubrange( 1.0 );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );

  sample = tab_cdf_distribution->sampleInSubrange( 1.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from a subrange
TEUCHOS_UNIT_TEST( HistogramDistribution, sampleWithRandomNumberInSubrange )
{
  // PDF Histogram: test max independent value 2nd bin
  double sample = tab_pdf_distribution->sampleWithRandomNumberInSubrange( 0.0, -1.0 );
  TEST_FLOATING_EQUALITY( sample, -2.0, 1e-14 );

  sample = tab_pdf_distribution->sampleWithRandomNumberInSubrange( 0.5, -1.0 );
  TEST_FLOATING_EQUALITY( sample, -1.5, 1e-14 ); 

  sample = tab_pdf_distribution->sampleWithRandomNumberInSubrange( 1.0 - 1e-15, -1.0 );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );
  
  // PDF Histogram: test max independent value 3rd bin
  sample = tab_pdf_distribution->sampleWithRandomNumberInSubrange( 0.0, 1.0 );
  TEST_FLOATING_EQUALITY( sample, -2.0, 1e-14 );

  sample = tab_pdf_distribution->sampleWithRandomNumberInSubrange( 0.5, 1.0 );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 ); 

  sample = tab_pdf_distribution->sampleWithRandomNumberInSubrange( 1.0 - 1e-15, 1.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // CDF Histogram: test max independent value 2nd bin
  sample = tab_cdf_distribution->sampleWithRandomNumberInSubrange( 0.0, -1.0 );
  TEST_FLOATING_EQUALITY( sample, -2.0, 1e-14 );

  sample = tab_cdf_distribution->sampleWithRandomNumberInSubrange( 0.5, -1.0 );
  TEST_FLOATING_EQUALITY( sample, -1.5, 1e-14 );

  sample = tab_cdf_distribution->sampleWithRandomNumberInSubrange( 1.0 - 1e-15, -1.0 );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );
  
  // Test max independent value 3rd bin
  sample = tab_cdf_distribution->sampleWithRandomNumberInSubrange( 0.0, 1.0 );
  TEST_FLOATING_EQUALITY( sample, -2.0, 1e-14 );

  sample = tab_cdf_distribution->sampleWithRandomNumberInSubrange( 0.5, 1.0 );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );

  sample = tab_cdf_distribution->sampleWithRandomNumberInSubrange( 1.0 - 1e-15, 1.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( HistogramDistribution, getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( pdf_distribution->getUpperBoundOfIndepVar(), 2.0 );
  TEST_EQUALITY_CONST( cdf_distribution->getUpperBoundOfIndepVar(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution dependent variable can be
// returned
TEUCHOS_UNIT_TEST( HistogramDistribution, getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( pdf_distribution->getLowerBoundOfIndepVar(), -2.0 );
  TEST_EQUALITY_CONST( cdf_distribution->getLowerBoundOfIndepVar(), -2.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
TEUCHOS_UNIT_TEST( HistogramDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( pdf_distribution->getDistributionType(),
		       Utility::HISTOGRAM_DISTRIBUTION );

  TEST_EQUALITY_CONST( cdf_distribution->getDistributionType(),
		       Utility::HISTOGRAM_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
TEUCHOS_UNIT_TEST( HistogramDistribution, isTabular )
{
  TEST_ASSERT( pdf_distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
TEUCHOS_UNIT_TEST( HistogramDistribution, isContinuous )
{
  TEST_ASSERT( pdf_distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be written to an xml file
TEUCHOS_UNIT_TEST( HistogramDistribution, toParameterList )
{
  Teuchos::RCP<Utility::HistogramDistribution> true_distribution =
  Teuchos::rcp_dynamic_cast<Utility::HistogramDistribution>( pdf_distribution );
  
  Teuchos::ParameterList parameter_list;
  
  parameter_list.set<Utility::HistogramDistribution>( "test distribution", 
						     *true_distribution );

  Teuchos::writeParameterListToXmlFile( parameter_list,
					"histogram_dist_test_list.xml" );
  
  Teuchos::RCP<Teuchos::ParameterList> read_parameter_list = 
    Teuchos::getParametersFromXmlFile( "histogram_dist_test_list.xml" );
  
  TEST_EQUALITY( parameter_list, *read_parameter_list );

  Teuchos::RCP<Utility::HistogramDistribution> 
    copy_distribution( new Utility::HistogramDistribution );

  *copy_distribution = 
    read_parameter_list->get<Utility::HistogramDistribution>(
							  "test distribution");

  TEST_EQUALITY( *copy_distribution, *true_distribution );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be read from an xml file
TEUCHOS_UNIT_TEST( HistogramDistribution, fromParameterList )
{
  Utility::HistogramDistribution distribution = 
    test_dists_list->get<Utility::HistogramDistribution>( "Histogram Distribution A" );

  TEST_EQUALITY_CONST( distribution.getLowerBoundOfIndepVar(), -2.0 );
  TEST_EQUALITY_CONST( distribution.getUpperBoundOfIndepVar(), 
		       Utility::PhysicalConstants::pi );

  distribution = 
    test_dists_list->get<Utility::HistogramDistribution>( "Histogram Distribution B" );

  TEST_EQUALITY_CONST( distribution.getLowerBoundOfIndepVar(), 0.0 );
  TEST_EQUALITY_CONST( distribution.getUpperBoundOfIndepVar(), 1.0 );
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

  TEUCHOS_ADD_TYPE_CONVERTER( Utility::HistogramDistribution );

  test_dists_list = Teuchos::getParametersFromXmlFile( test_dists_xml_file );

  // Create a distribution using the standard constructor
  {
    Teuchos::Array<double> bin_boundaries( 4 );
    bin_boundaries[0] = -2.0;
    bin_boundaries[1] = -1.0;
    bin_boundaries[2] = 1.0;
    bin_boundaries[3] = 2.0;
  
    Teuchos::Array<double> bin_values( 3 );
    bin_values[0] = 2.0;
    bin_values[1] = 1.0;
    bin_values[2] = 2.0;
    
    tab_pdf_distribution.reset( 
			   new Utility::HistogramDistribution( bin_boundaries,
							       bin_values) );

    pdf_distribution = tab_pdf_distribution;
  }

  // Create a distribution using the cdf constructor
  {
    Teuchos::Array<double> bin_boundaries( 4 );
    bin_boundaries[0] = -2.0;
    bin_boundaries[1] = -1.0;
    bin_boundaries[2] = 1.0;
    bin_boundaries[3] = 2.0;
    
    Teuchos::Array<double> cdf_values( 3 );
    cdf_values[0] = 2.0;
    cdf_values[1] = 4.0;
    cdf_values[2] = 6.0;
    
    tab_cdf_distribution.reset( 
			  new Utility::HistogramDistribution( bin_boundaries,
							      cdf_values,
                                                              true ) );
  
    cdf_distribution = tab_cdf_distribution;
  }

  // Create a unit-aware distribution using the standard constructor
  {
    Teuchos::Array<quantity<MegaElectronVolt> > bin_boundaries( 4 );
    bin_boundaries[0] = -2.0*MeV;
    bin_boundaries[1] = -1.0*MeV;
    bin_boundaries[2] = 1.0*MeV;
    bin_boundaries[3] = 2.0*MeV;
  
    Teuchos::Array<quantity<si::amount> > bin_values( 3 );
    bin_values[0] = 2.0*si::mole;
    bin_values[1] = 1.0*si::mole;
    bin_values[2] = 2.0*si::mole;
    
    unit_aware_tab_pdf_distribution.reset( 
      new Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount>(
								bin_boundaries,
								bin_values) );

    unit_aware_pdf_distribution = unit_aware_tab_pdf_distribution;
  }

  // Create a unit-aware distribution using the cdf constructor
  {
    Teuchos::Array<quantity<MegaElectronVolt> > bin_boundaries( 4 );
    bin_boundaries[0] = -2.0*MeV;
    bin_boundaries[1] = -1.0*MeV;
    bin_boundaries[2] = 1.0*MeV;
    bin_boundaries[3] = 2.0*MeV;
    
    Teuchos::Array<double> cdf_values( 3 );
    cdf_values[0] = 2.0;
    cdf_values[1] = 4.0;
    cdf_values[2] = 6.0;
    
    unit_aware_tab_cdf_distribution.reset( 
      new Utility::UnitAwareHistogramDistribution<MegaElectronVolt,si::amount>(
								bin_boundaries,
								cdf_values ) );
  
    unit_aware_cdf_distribution = unit_aware_tab_cdf_distribution;
  }

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
// end tstHistogramDistribution.cpp
//---------------------------------------------------------------------------//
