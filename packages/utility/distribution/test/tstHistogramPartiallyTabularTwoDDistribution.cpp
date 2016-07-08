//---------------------------------------------------------------------------//
//!
//! \file   tstHistogramPartiallyTabularTwoDDistribution.cpp
//! \author Alex Robinson
//! \brief  The histogram partially tabular two-dimensional dist. unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Boost Includes
#include <boost/units/systems/cgs.hpp>
#include <boost/units/io.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_HistogramPartiallyTabularTwoDDistribution.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_ExponentialDistribution.hpp"
#include "Utility_ElectronVoltUnit.hpp"
#include "Utility_BarnUnit.hpp"

using boost::units::quantity;
using Utility::Units::MegaElectronVolt;
using Utility::Units::MeV;
using Utility::Units::Barn;
using Utility::Units::barn;
using Utility::Units::barns;
namespace cgs = boost::units::cgs;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<Utility::UnitAwareTwoDDistribution<MegaElectronVolt,cgs::length,Barn> > 
  unit_aware_distribution;

std::shared_ptr<Utility::TwoDDistribution> distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( HistogramPartiallyTabularTwoDDistribution, evaluate )
{
  // Before the first bin
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0, 0.0 ), 1.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0, 1.0 ), 0.0 );

  // On the second bin (first bin boundary = second bin boundary)
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0, 0.0 ), 1.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0, 1.0 ), exp( -1.0 ) );

  // In the second bin
  TEST_EQUALITY_CONST( distribution->evaluate( 0.5, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.5, 0.0 ), 1.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.5, 1.0 ), exp( -1.0 ) );

  // On the third bin
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0, 0.0 ), 1.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0, 1.0 ), 1.0 );

  // In the third bin
  TEST_EQUALITY_CONST( distribution->evaluate( 1.5, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.5, 0.0 ), 1.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.5, 1.0 ), 1.0 );

  // After the third bin
  TEST_EQUALITY_CONST( distribution->evaluate( 2.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 2.0, 0.0 ), 1.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 2.0, 1.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareHistogramPartiallyTabularTwoDDistribution,
                   evaluate )
{
  // Before the first bin
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( -1.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( -1.0*MeV, 0.0*cgs::centimeter ), 1.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( -1.0*MeV, 1.0*cgs::centimeter ), 0.0*barn );

  // On the second bin (first bin boundary = second bin boundary)
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*MeV, 0.0*cgs::centimeter ), 1.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*MeV, 1.0*cgs::centimeter ), exp( -1.0 )*barns );

  // In the second bin
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.5*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.5*MeV, 0.0*cgs::centimeter ), 1.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.5*MeV, 1.0*cgs::centimeter ), exp( -1.0 )*barns );

  // On the third bin
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1.0*MeV, 0.0*cgs::centimeter ), 1.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1.0*MeV, 1.0*cgs::centimeter ), 1.0*barn );

  // In the third bin
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1.5*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1.5*MeV, 0.0*cgs::centimeter ), 1.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1.5*MeV, 1.0*cgs::centimeter ), 1.0*barn );

  // After the third bin
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 2.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 2.0*MeV, 0.0*cgs::centimeter ), 1.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 2.0*MeV, 1.0*cgs::centimeter ), 0.0*barn );
}

//---------------------------------------------------------------------------//
// Check that the secondary conditional PDF can be evaluated
TEUCHOS_UNIT_TEST( HistogramPartiallyTabularTwoDDistribution,
                   evaluateSecondaryConditionalPDF )
{
  // Before the first bin
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( -1.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( -1.0, 0.0 ), 1.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( -1.0, 1.0 ), 0.0 );

  // On the second bin (first bin boundary = second bin boundary)
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 0.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 0.0, 0.0 ), 1.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 0.0, 1.0 ), exp( -1.0 ) );

  // In the second bin
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 0.5, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 0.5, 0.0 ), 1.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 0.5, 1.0 ), exp( -1.0 ) );

  // On the third bin
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 1.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 1.0, 0.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 1.0, 1.0 ), 0.1 );

  // In the third bin
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 1.5, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 1.5, 0.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 1.5, 1.0 ), 0.1 );

  // After the third bin
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 2.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 2.0, 0.0 ), 1.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 2.0, 1.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware secondary conditional PDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareHistogramPartiallyTabularTwoDDistribution,
                   evaluateSecondaryConditionalPDF )
{
  // Before the first bin
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, 0.0*cgs::centimeter ), 1.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( -1.0*MeV, 1.0*cgs::centimeter ), 0.0/cgs::centimeter );

  // On the second bin (first bin boundary = second bin boundary)
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 0.0*cgs::centimeter ), 1.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.0*MeV, 1.0*cgs::centimeter ), exp( -1.0 )/cgs::centimeter );

  // In the second bin
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.5*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.5*MeV, 0.0*cgs::centimeter ), 1.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 0.5*MeV, 1.0*cgs::centimeter ), exp( -1.0 )/cgs::centimeter );

  // On the third bin
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, 0.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.0*MeV, 1.0*cgs::centimeter ), 0.1/cgs::centimeter );

  // In the third bin
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, 0.0*cgs::centimeter ), 0.1/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 1.5*MeV, 1.0*cgs::centimeter ), 0.1/cgs::centimeter );

  // After the third bin
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, -1.0*cgs::centimeter ), 0.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, 0.0*cgs::centimeter ), 1.0/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluateSecondaryConditionalPDF( 2.0*MeV, 1.0*cgs::centimeter ), 0.0/cgs::centimeter );
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( HistogramPartiallyTabularTwoDDistribution,
                   sampleSecondaryConditional )
{
  // Before the first bin
  double sample = distribution->sampleSecondaryConditional( -1.0 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  // On the second bin (first bin boundary = second bin boundary)
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditional( 0.0 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 0.0 );

  TEST_FLOATING_EQUALITY( sample, 0.6931471805599453, 1e-9 );

  // In the second bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditional( 0.5 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 0.5 );

  TEST_FLOATING_EQUALITY( sample, 0.6931471805599453, 1e-9 );

  // On the third bin
  fake_stream.push_back( 1.0 - 1e-15 );
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditional( 1.0 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 1.0 );
  
  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = distribution->sampleSecondaryConditional( 1.0 );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-9 );
  
  // In the third bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditional( 1.5 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sampleSecondaryConditional( 1.5 );
  
  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = distribution->sampleSecondaryConditional( 1.5 );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-9 );

  // After the third bin
  Utility::RandomNumberGenerator::unsetFakeStream();

  sample = distribution->sampleSecondaryConditional( 2.0 );

  TEST_EQUALITY_CONST( sample, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareHistogramPartiallyTabularTwoDDistribution,
                   sampleSecondaryConditional )
{
  // Before the first bin
  quantity<cgs::length> sample = unit_aware_distribution->sampleSecondaryConditional( -1.0*MeV );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  // On the second bin (first bin boundary = second bin boundary)
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.0*MeV );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.6931471805599453*cgs::centimeter, 1e-9 );

  // In the second bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.5*MeV );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 0.5*MeV );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.6931471805599453*cgs::centimeter, 1e-9 );

  // On the third bin
  fake_stream.push_back( 1.0 - 1e-15 );
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.0*MeV );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.0*MeV );
  
  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.0*MeV );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-9 );
  
  // In the third bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );
  
  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  sample = unit_aware_distribution->sampleSecondaryConditional( 1.5*MeV );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-9 );

  // After the third bin
  Utility::RandomNumberGenerator::unsetFakeStream();

  sample = unit_aware_distribution->sampleSecondaryConditional( 2.0*MeV );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( HistogramPartiallyTabularTwoDDistribution,
                   sampleSecondaryConditionalAndRecordTrials )
{
  unsigned trials = 0u;
  
  // Before the first bin
  double sample = distribution->sampleSecondaryConditionalAndRecordTrials( -1.0 , trials );

  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( trials, 1u );

  // On the second bin (first bin boundary = second bin boundary)
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.0, trials );

  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.0, trials );

  TEST_FLOATING_EQUALITY( sample, 0.6931471805599453, 1e-9 );
  TEST_EQUALITY_CONST( trials, 3u );

  // In the second bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.5, trials );

  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( trials, 4u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 0.5, trials );

  TEST_FLOATING_EQUALITY( sample, 0.6931471805599453, 1e-9 );
  TEST_EQUALITY_CONST( trials, 5u );

  // On the third bin
  fake_stream.push_back( 1.0 - 1e-15 );
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.0, trials );

  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( trials, 6u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.0, trials );
  
  TEST_EQUALITY_CONST( sample, 5.0 );
  TEST_EQUALITY_CONST( trials, 7u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.0, trials );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-9 );
  TEST_EQUALITY_CONST( trials, 8u );
  
  // In the third bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );

  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( trials, 9u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );
  
  TEST_EQUALITY_CONST( sample, 5.0 );
  TEST_EQUALITY_CONST( trials, 10u );

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 1.5, trials );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-9 );
  TEST_EQUALITY_CONST( trials, 11u );

  // After the third bin
  Utility::RandomNumberGenerator::unsetFakeStream();

  sample = distribution->sampleSecondaryConditionalAndRecordTrials( 2.0, trials );

  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( trials, 12u );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareHistogramPartiallyTabularTwoDDistribution,
                   sampleSecondaryConditionalAndRecordTrials )
{
  unsigned trials = 0u;
  
  // Before the first bin
  quantity<cgs::length> sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( -1.0*MeV, trials );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );
  TEST_EQUALITY_CONST( trials, 1u );

  // On the second bin (first bin boundary = second bin boundary)
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.0*MeV, trials );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );
  TEST_EQUALITY_CONST( trials, 2u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.0*MeV, trials );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.6931471805599453*cgs::centimeter, 1e-9 );
  TEST_EQUALITY_CONST( trials, 3u );

  // In the second bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.5*MeV, trials );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );
  TEST_EQUALITY_CONST( trials, 4u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 0.5*MeV, trials );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.6931471805599453*cgs::centimeter, 1e-9 );
  TEST_EQUALITY_CONST( trials, 5u );

  // On the third bin
  fake_stream.push_back( 1.0 - 1e-15 );
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.0*MeV, trials );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );
  TEST_EQUALITY_CONST( trials, 6u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.0*MeV, trials );
  
  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );
  TEST_EQUALITY_CONST( trials, 7u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.0*MeV, trials );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-9 );
  TEST_EQUALITY_CONST( trials, 8u );
  
  // In the third bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );
  TEST_EQUALITY_CONST( trials, 9u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );
  
  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );
  TEST_EQUALITY_CONST( trials, 10u );

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 1.5*MeV, trials );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-9 );
  TEST_EQUALITY_CONST( trials, 11u );

  // After the third bin
  Utility::RandomNumberGenerator::unsetFakeStream();

  sample = unit_aware_distribution->sampleSecondaryConditionalAndRecordTrials( 2.0*MeV, trials );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );
  TEST_EQUALITY_CONST( trials, 12u );
}

//---------------------------------------------------------------------------//
// Chech that the upper bound of the distribution primary independent variable
// can be returned
TEUCHOS_UNIT_TEST( HistogramPartiallyTabularTwoDDistribution,
                   getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfPrimaryIndepVar(), 2.0 );
}

//---------------------------------------------------------------------------//
// Chech that the upper bound of the unit-aware distribution primary
// independent variable can be returned
TEUCHOS_UNIT_TEST( UnitAwareHistogramPartiallyTabularTwoDDistribution,
                   getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfPrimaryIndepVar(), 2.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution primary independent variable
// can be returned
TEUCHOS_UNIT_TEST( HistogramPartiallyTabularTwoDDistribution,
                   getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfPrimaryIndepVar(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware distribution primary
// independent variable can be returned
TEUCHOS_UNIT_TEST( UnitAwareHistogramPartiallyTabularTwoDDistribution,
                   getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfPrimaryIndepVar(), 0.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the conditional distribution independent
// variable can be returned
TEUCHOS_UNIT_TEST( HistogramPartiallyTabularTwoDDistribution,
                   getUpperBoundOfConditionalIndepVar )
{
  // Before the first bin
  TEST_EQUALITY_CONST(
                 distribution->getUpperBoundOfConditionalIndepVar(-1.0), 0.0 );

  // On the second bin (first bin boundary = second bin boundary)
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfConditionalIndepVar(0.0),
                       std::numeric_limits<double>::infinity() );

  // In the second bin
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfConditionalIndepVar(0.5),
                       std::numeric_limits<double>::infinity() );

  // On the third bin
  TEST_EQUALITY_CONST(
                 distribution->getUpperBoundOfConditionalIndepVar(1.0), 10.0 );

  // In the third bin
  TEST_EQUALITY_CONST(
                 distribution->getUpperBoundOfConditionalIndepVar(1.5), 10.0 );

  // After the third bin
  TEST_EQUALITY_CONST(
                  distribution->getUpperBoundOfConditionalIndepVar(2.0), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware conditional distribution
// independent variable can be returned
TEUCHOS_UNIT_TEST( UnitAwareHistogramPartiallyTabularTwoDDistribution,
                   getUpperBoundOfConditionalIndepVar )
{
  // Before the first bin
  TEST_EQUALITY_CONST(
         unit_aware_distribution->getUpperBoundOfConditionalIndepVar(-1.0*MeV),
         0.0*cgs::centimeter );

  // On the second bin (first bin boundary = second bin boundary)
  TEST_EQUALITY_CONST(
         unit_aware_distribution->getUpperBoundOfConditionalIndepVar(0.0*MeV),
         std::numeric_limits<double>::infinity()*cgs::centimeter );

  // In the second bin
  TEST_EQUALITY_CONST(
         unit_aware_distribution->getUpperBoundOfConditionalIndepVar(0.5*MeV),
         std::numeric_limits<double>::infinity()*cgs::centimeter );

  // On the third bin
  TEST_EQUALITY_CONST(
         unit_aware_distribution->getUpperBoundOfConditionalIndepVar(1.0*MeV),
         10.0*cgs::centimeter );

  // In the third bin
  TEST_EQUALITY_CONST(
         unit_aware_distribution->getUpperBoundOfConditionalIndepVar(1.5*MeV),
         10.0*cgs::centimeter );

  // After the third bin
  TEST_EQUALITY_CONST(
         unit_aware_distribution->getUpperBoundOfConditionalIndepVar(2.0*MeV),
         0.0*cgs::centimeter );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the conditional distribution independent
// variable can be returned
TEUCHOS_UNIT_TEST( HistogramPartiallyTabularTwoDDistribution,
                   getLowerBoundOfConditionalIndepVar )
{
  // Before the first bin
  TEST_EQUALITY_CONST(
                 distribution->getLowerBoundOfConditionalIndepVar(-1.0), 0.0 );

  // On the second bin (first bin boundary = second bin boundary)
  TEST_EQUALITY_CONST(
                  distribution->getLowerBoundOfConditionalIndepVar(0.0), 0.0 );
                       

  // In the second bin
  TEST_EQUALITY_CONST(
                  distribution->getLowerBoundOfConditionalIndepVar(0.5), 0.0 );

  // On the third bin
  TEST_EQUALITY_CONST(
                  distribution->getLowerBoundOfConditionalIndepVar(1.0), 0.0 );

  // In the third bin
  TEST_EQUALITY_CONST(
                  distribution->getLowerBoundOfConditionalIndepVar(1.5), 0.0 );

  // After the third bin
  TEST_EQUALITY_CONST(
                  distribution->getLowerBoundOfConditionalIndepVar(2.0), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware conditional distribution
// independent variable can be returned
TEUCHOS_UNIT_TEST( UnitAwareHistogramPartiallyTabularTwoDDistribution,
                   getLowerBoundOfConditionalIndepVar )
{
  // Before the first bin
  TEST_EQUALITY_CONST(
         unit_aware_distribution->getLowerBoundOfConditionalIndepVar(-1.0*MeV),
         0.0*cgs::centimeter );

  // On the second bin (first bin boundary = second bin boundary)
  TEST_EQUALITY_CONST(
         unit_aware_distribution->getLowerBoundOfConditionalIndepVar(0.0*MeV),
         0.0*cgs::centimeter );
                       

  // In the second bin
  TEST_EQUALITY_CONST(
         unit_aware_distribution->getLowerBoundOfConditionalIndepVar(0.5*MeV),
         0.0*cgs::centimeter );

  // On the third bin
  TEST_EQUALITY_CONST(
         unit_aware_distribution->getLowerBoundOfConditionalIndepVar(1.0*MeV),
         0.0*cgs::centimeter );

  // In the third bin
  TEST_EQUALITY_CONST(
         unit_aware_distribution->getLowerBoundOfConditionalIndepVar(1.5*MeV),
         0.0*cgs::centimeter );

  // After the third bin
  TEST_EQUALITY_CONST(
         unit_aware_distribution->getLowerBoundOfConditionalIndepVar(2.0*MeV),
         0.0*cgs::centimeter );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular in the primary dimension
TEUCHOS_UNIT_TEST( HistogramPartiallyTabularTwoDDistribution,
                   isPrimaryDimensionTabular )
{
  TEST_ASSERT( distribution->isPrimaryDimensionTabular() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is tabular in the primary dimension
TEUCHOS_UNIT_TEST( UnitAwareHistogramPartiallyTabularTwoDDistribution,
                   isPrimaryDimensionTabular )
{
  TEST_ASSERT( unit_aware_distribution->isPrimaryDimensionTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous in the primary dimension
TEUCHOS_UNIT_TEST( HistogramPartiallyTabularTwoDDistribution,
                   isPrimaryDimensionContinuous )
{
  TEST_ASSERT( distribution->isPrimaryDimensionContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is continuous in the primary dimension
TEUCHOS_UNIT_TEST( UnitAwareHistogramPartiallyTabularTwoDDistribution,
                   isPrimaryDimensionContinuous )
{
  TEST_ASSERT( unit_aware_distribution->isPrimaryDimensionContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the distribution has the same bounds as another distribution
TEUCHOS_UNIT_TEST( HistogramPartiallyTabularTwoDDistribution,
                   hasSamePrimaryBounds )
{
  std::shared_ptr<Utility::TwoDDistribution> other_distribution;
  
  {
    Utility::HistogramPartiallyTabularTwoDDistribution::DistributionType
      distribution_data( 2 );
    
    distribution_data[0].first = 0.0;
    distribution_data[0].second.reset( new Utility::DeltaDistribution( 0.0 ) );

    distribution_data[1].first = 2.0;
    distribution_data[1].second.reset( new Utility::DeltaDistribution( 1.0 ) );

    other_distribution.reset(
                       new Utility::HistogramPartiallyTabularTwoDDistribution(
                                                         distribution_data ) );
  }

  TEST_ASSERT( distribution->hasSamePrimaryBounds( *other_distribution ) );

  {
    Utility::HistogramPartiallyTabularTwoDDistribution::DistributionType
      distribution_data( 2 );
    
    distribution_data[0].first = -1.0;
    distribution_data[0].second.reset( new Utility::DeltaDistribution( 0.0 ) );

    distribution_data[1].first = 2.0;
    distribution_data[1].second.reset( new Utility::DeltaDistribution( 1.0 ) );

    other_distribution.reset(
                       new Utility::HistogramPartiallyTabularTwoDDistribution(
                                                         distribution_data ) );
  }

  TEST_ASSERT( !distribution->hasSamePrimaryBounds( *other_distribution ) );

  {
    Utility::HistogramPartiallyTabularTwoDDistribution::DistributionType
      distribution_data( 2 );
    
    distribution_data[0].first = 0.0;
    distribution_data[0].second.reset( new Utility::DeltaDistribution( 0.0 ) );

    distribution_data[1].first = 3.0;
    distribution_data[1].second.reset( new Utility::DeltaDistribution( 1.0 ) );

    other_distribution.reset(
                       new Utility::HistogramPartiallyTabularTwoDDistribution(
                                                         distribution_data ) );
  }

  TEST_ASSERT( !distribution->hasSamePrimaryBounds( *other_distribution ) );

  {
    Utility::HistogramPartiallyTabularTwoDDistribution::DistributionType
      distribution_data( 2 );
    
    distribution_data[0].first = -1.0;
    distribution_data[0].second.reset( new Utility::DeltaDistribution( 0.0 ) );

    distribution_data[1].first = 3.0;
    distribution_data[1].second.reset( new Utility::DeltaDistribution( 1.0 ) );

    other_distribution.reset(
                       new Utility::HistogramPartiallyTabularTwoDDistribution(
                                                         distribution_data ) );
  }

  TEST_ASSERT( !distribution->hasSamePrimaryBounds( *other_distribution ) );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution has the same bounds as another
// distribution
TEUCHOS_UNIT_TEST( UnitAwareHistogramPartiallyTabularTwoDDistribution,
                   hasSamePrimaryBounds )
{
  std::shared_ptr<Utility::UnitAwareTwoDDistribution<MegaElectronVolt,cgs::length,Barn> > other_distribution;
  
  {
    Utility::UnitAwareHistogramPartiallyTabularTwoDDistribution<MegaElectronVolt,cgs::length,Barn>::DistributionType
      distribution_data( 2 );
    
    distribution_data[0].first = 0.0*MeV;
    distribution_data[0].second.reset( new Utility::UnitAwareDeltaDistribution<cgs::length,Barn>( 0.0*cgs::centimeter ) );

    distribution_data[1].first = 2.0*MeV;
    distribution_data[1].second.reset( new Utility::UnitAwareDeltaDistribution<cgs::length,Barn>( 1.0*cgs::centimeter ) );

    other_distribution.reset(
                       new Utility::UnitAwareHistogramPartiallyTabularTwoDDistribution<MegaElectronVolt,cgs::length,Barn>(
                                                         distribution_data ) );
  }

  TEST_ASSERT( unit_aware_distribution->hasSamePrimaryBounds( *other_distribution ) );

  {
    Utility::UnitAwareHistogramPartiallyTabularTwoDDistribution<MegaElectronVolt,cgs::length,Barn>::DistributionType
      distribution_data( 2 );
    
    distribution_data[0].first = -1.0*MeV;
    distribution_data[0].second.reset( new Utility::UnitAwareDeltaDistribution<cgs::length,Barn>( 0.0*cgs::centimeter ) );

    distribution_data[1].first = 2.0*MeV;
    distribution_data[1].second.reset( new Utility::UnitAwareDeltaDistribution<cgs::length,Barn>( 1.0*cgs::centimeter ) );

    other_distribution.reset(
                       new Utility::UnitAwareHistogramPartiallyTabularTwoDDistribution<MegaElectronVolt,cgs::length,Barn>(
                                                         distribution_data ) );
  }

  TEST_ASSERT( !unit_aware_distribution->hasSamePrimaryBounds( *other_distribution ) );

  {
    Utility::UnitAwareHistogramPartiallyTabularTwoDDistribution<MegaElectronVolt,cgs::length,Barn>::DistributionType
      distribution_data( 2 );
    
    distribution_data[0].first = 0.0*MeV;
    distribution_data[0].second.reset( new Utility::UnitAwareDeltaDistribution<cgs::length,Barn>( 0.0*cgs::centimeter ) );

    distribution_data[1].first = 3.0*MeV;
    distribution_data[1].second.reset( new Utility::UnitAwareDeltaDistribution<cgs::length,Barn>( 1.0*cgs::centimeter ) );

    other_distribution.reset(
                       new Utility::UnitAwareHistogramPartiallyTabularTwoDDistribution<MegaElectronVolt,cgs::length,Barn>(
                                                         distribution_data ) );
  }

  TEST_ASSERT( !unit_aware_distribution->hasSamePrimaryBounds( *other_distribution ) );

  {
    Utility::UnitAwareHistogramPartiallyTabularTwoDDistribution<MegaElectronVolt,cgs::length,Barn>::DistributionType
      distribution_data( 2 );
    
    distribution_data[0].first = -1.0*MeV;
    distribution_data[0].second.reset( new Utility::UnitAwareDeltaDistribution<cgs::length,Barn>( 0.0*cgs::centimeter ) );

    distribution_data[1].first = 3.0*MeV;
    distribution_data[1].second.reset( new Utility::UnitAwareDeltaDistribution<cgs::length,Barn>( 1.0*cgs::centimeter ) );

    other_distribution.reset(
                       new Utility::UnitAwareHistogramPartiallyTabularTwoDDistribution<MegaElectronVolt,cgs::length,Barn>(
                                                         distribution_data ) );
  }

  TEST_ASSERT( !unit_aware_distribution->hasSamePrimaryBounds( *other_distribution ) );
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

  // Create the two-dimensional distribution
  {
    Utility::HistogramPartiallyTabularTwoDDistribution::DistributionType
      distribution_data( 4 );

    // Create the secondary distribution in the first bin
    distribution_data[0].first = 0.0;
    distribution_data[0].second.reset( new Utility::DeltaDistribution( 0.0 ) );
    

    // Create the secondary distribution in the second bin
    distribution_data[1].first = 0.0;
    distribution_data[1].second.reset( new Utility::ExponentialDistribution( 1.0, 1.0 ) );

    // Create the secondary distribution in the third bin
    distribution_data[2].first = 1.0;
    distribution_data[2].second.reset( new Utility::UniformDistribution( 0.0, 10.0, 1.0 ) );

    // Create the secondary distribution beyond the third bin
    distribution_data[3].first = 2.0;
    distribution_data[3].second = distribution_data[0].second;

    distribution.reset( new Utility::HistogramPartiallyTabularTwoDDistribution(
                                                         distribution_data ) );
  }

  // Create the unit-aware two-dimensional distribution
  {
    std::vector<quantity<MegaElectronVolt> > primary_bins( 4 );

    Teuchos::Array<std::shared_ptr<const Utility::UnitAwareOneDDistribution<cgs::length,Barn> > > secondary_dists( 4 );

    // Create the secondary distribution in the first bin
    primary_bins[0] = 0.0*MeV;
    secondary_dists[0].reset( new Utility::UnitAwareDeltaDistribution<cgs::length,Barn>( 0.0*cgs::centimeter ) );

    // Create the secondary distribution in the second bin
    primary_bins[1] = 0.0*MeV;
    secondary_dists[1].reset( new Utility::UnitAwareExponentialDistribution<cgs::length,Barn>( 1.0*barn, 1.0/cgs::centimeter ) );

    // Create the secondary distribution in the third bin
    primary_bins[2] = 1.0*MeV;
    secondary_dists[2].reset( new Utility::UnitAwareUniformDistribution<cgs::length,Barn>( 0.0*cgs::centimeter, 10.0*cgs::centimeter, 1.0*barn ) );

    // Create the secondary distribution beyond the third bin
    primary_bins[3] = 2.0*MeV;
    secondary_dists[3] = secondary_dists[0];

    unit_aware_distribution.reset( new Utility::UnitAwareHistogramPartiallyTabularTwoDDistribution<MegaElectronVolt,cgs::length,Barn>( primary_bins, secondary_dists ) );
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
// end tstHistogramPartiallyTabularTwoDDistribution.cpp
//---------------------------------------------------------------------------//
