//---------------------------------------------------------------------------//
//!
//! \file   tstUniformDistribution.cpp
//! \author Alex Robinson
//! \brief  Uniform distribution unit tests.
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
#include "Utility_OneDDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
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

Teuchos::RCP<Utility::TabularOneDDistribution> tab_distribution(
			  new Utility::UniformDistribution( -1.0, 1.0, 2.0 ) );

Teuchos::RCP<Utility::OneDDistribution> distribution = tab_distribution;

Teuchos::RCP<Utility::UnitAwareTabularOneDDistribution<si::energy,si::amount> >
  unit_aware_tab_distribution;

Teuchos::RCP<Utility::UnitAwareOneDDistribution<si::energy,si::amount> >
  unit_aware_distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( UniformDistribution, evaluate )
{
  TEST_EQUALITY_CONST( distribution->evaluate( -2.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0 ), 2.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), 2.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0 ), 2.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( -2.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit aware distribution can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareUniformDistribution, evaluate )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( -1.0*si::joule ),
		       0.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*si::joule ),
  		       1.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.5*si::joule ),
  		       1.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1.0*si::joule ),
  		       1.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 2.0*si::joule ),
  		       0.0*si::mole );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( UniformDistribution, evaluatePDF )
{
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -2.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -1.0 ), 0.5 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 0.0 ), 0.5 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 1.0 ), 0.5 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 2.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit aware PDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareUniformDistribution, evaluatePDF )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( -1.0*si::joule ),
  		       0.0/si::joule );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 0.0*si::joule ),
  		       1.0/si::joule );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 0.5*si::joule ),
  		       1.0/si::joule );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 1.0*si::joule ),
  		       1.0/si::joule );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 2.0*si::joule ),
  		       0.0/si::joule );
}

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated
TEUCHOS_UNIT_TEST( UniformDistribution, evaluateCDF )
{
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( -2.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 0.0 ), 0.5 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 1.0 ), 1.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 2.0 ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit aware CDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareUniformDistribution, evaluateCDF )
{
  TEST_EQUALITY_CONST(unit_aware_tab_distribution->evaluateCDF(-1.0*si::joule),
		      0.0 );
  TEST_EQUALITY_CONST(unit_aware_tab_distribution->evaluateCDF(0.0*si::joule),
		      0.0 );
  TEST_EQUALITY_CONST(unit_aware_tab_distribution->evaluateCDF(0.5*si::joule),
		      0.5 );
  TEST_EQUALITY_CONST(unit_aware_tab_distribution->evaluateCDF(1.0*si::joule),
		      1.0 );
  TEST_EQUALITY_CONST(unit_aware_tab_distribution->evaluateCDF(2.0*si::joule),
		      1.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( UniformDistribution, sample )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareUniformDistribution, sample )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<si::energy> sample = unit_aware_distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.0*si::joule );

  sample = unit_aware_distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.5*si::joule );

  sample = unit_aware_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*si::joule, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled w/o an instance
TEUCHOS_UNIT_TEST( UniformDistribution, sample_static )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = Utility::UniformDistribution::sample( -1.0, 1.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = Utility::UniformDistribution::sample( -1.0, 1.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = Utility::UniformDistribution::sample( -1.0, 1.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled w/o an instance
TEUCHOS_UNIT_TEST( UnitAwareUniformDistribution, sample_static )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<si::energy> sample =
    Utility::UnitAwareUniformDistribution<si::energy>::sample(
					        0.0*si::joule, 1.0*si::joule );
  TEST_EQUALITY_CONST( sample, 0.0*si::joule );

  sample =
    Utility::UnitAwareUniformDistribution<si::energy>::sample(
					        0.0*si::joule, 1.0*si::joule );
  TEST_EQUALITY_CONST( sample, 0.5*si::joule );

  sample =
    Utility::UnitAwareUniformDistribution<si::energy>::sample(
					        0.0*si::joule, 1.0*si::joule );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*si::joule, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( UniformDistribution, sampleAndRecordTrials )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned trials = 0;

  double sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( 1.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( 2.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  TEST_EQUALITY_CONST( 3.0/trials, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareUniformDistribution, sampleAndRecordTrials )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned trials = 0;

  quantity<si::energy> sample =
    unit_aware_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.0*si::joule );
  TEST_EQUALITY_CONST( 1.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.5*si::joule );
  TEST_EQUALITY_CONST( 2.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*si::joule, 1e-14 );
  TEST_EQUALITY_CONST( 3.0/trials, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled w/o an instance
TEUCHOS_UNIT_TEST( UniformDistribution, sampleAndRecordTrials_static )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned trials = 0;

  double sample = Utility::UniformDistribution::sampleAndRecordTrials(
							   -1.0, 1.0, trials );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( 1.0/trials, 1.0 );

  sample = Utility::UniformDistribution::sampleAndRecordTrials(
							   -1.0, 1.0, trials );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( 2.0/trials, 1.0 );

  sample = Utility::UniformDistribution::sampleAndRecordTrials(
							   -1.0, 1.0, trials );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  TEST_EQUALITY_CONST( 3.0/trials, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled w/o an instance
TEUCHOS_UNIT_TEST( UnitAwareUniformDistribution, sampleAndRecordTrials_static )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned trials = 0;

  quantity<si::energy> sample = Utility::UnitAwareUniformDistribution<si::energy,si::amount>::sampleAndRecordTrials(
				        0.0*si::joule, 1.0*si::joule, trials );
  TEST_EQUALITY_CONST( sample, 0.0*si::joule );
  TEST_EQUALITY_CONST( 1.0/trials, 1.0 );

  sample =
    Utility::UnitAwareUniformDistribution<si::energy,si::amount>::sampleAndRecordTrials(
				        0.0*si::joule, 1.0*si::joule, trials );
  TEST_EQUALITY_CONST( sample, 0.5*si::joule );
  TEST_EQUALITY_CONST( 2.0/trials, 1.0 );

  sample =
    Utility::UnitAwareUniformDistribution<si::energy,si::amount>::sampleAndRecordTrials(
				        0.0*si::joule, 1.0*si::joule, trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*si::joule, 1e-14 );
  TEST_EQUALITY_CONST( 3.0/trials, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( UniformDistribution, sampleAndRecordBinIndex )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned bin_index;

  double sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( bin_index, 0.0 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( bin_index, 0.0 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 0.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareUniformDistribution, sampleAndRecordBinIndex )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned bin_index;

  quantity<si::energy> sample =
    unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 0.0*si::joule );
  TEST_EQUALITY_CONST( bin_index, 0.0 );

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 0.5*si::joule );
  TEST_EQUALITY_CONST( bin_index, 0.0 );

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*si::joule, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 0.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( UniformDistribution, sampleWithRandomNumber )
{
  double sample = tab_distribution->sampleWithRandomNumber( 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleWithRandomNumber( 0.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleWithRandomNumber( 1.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the unit aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareUniformDistribution, sampleWithRandomNumber )
{
  quantity<si::energy> sample =
    unit_aware_tab_distribution->sampleWithRandomNumber( 0.0 );
  TEST_EQUALITY_CONST( sample, 0.0*si::joule );

  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 0.5 );
  TEST_EQUALITY_CONST( sample, 0.5*si::joule );

  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 1.0 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*si::joule, 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled w/o an instance
TEUCHOS_UNIT_TEST( UniformDistribution, sampleWithRandomNumber_static )
{
  double sample = Utility::UniformDistribution::sampleWithRandomNumber(
							      -1.0, 1.0, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = Utility::UniformDistribution::sampleWithRandomNumber(
							      -1.0, 1.0, 0.5 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = Utility::UniformDistribution::sampleWithRandomNumber(
							      -1.0, 1.0, 1.0 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the unit aware distribution can be sampled w/o an instance
TEUCHOS_UNIT_TEST( UnitAwareUniformDistribution,
		   sampleWithRandomNumber_static )
{
  quantity<si::energy> sample = Utility::UnitAwareUniformDistribution<si::energy,si::amount>::sampleWithRandomNumber(
					   0.0*si::joule, 1.0*si::joule, 0.0 );
  TEST_EQUALITY_CONST( sample, 0.0*si::joule );

  sample = Utility::UnitAwareUniformDistribution<si::energy,si::amount>::sampleWithRandomNumber(
					   0.0*si::joule, 1.0*si::joule, 0.5 );
  TEST_EQUALITY_CONST( sample, 0.5*si::joule );

  sample = Utility::UnitAwareUniformDistribution<si::energy,si::amount>::sampleWithRandomNumber(
					   0.0*si::joule, 1.0*si::joule, 1.0 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*si::joule, 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( UniformDistribution, sampleInSubrange )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = tab_distribution->sampleInSubrange( 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleInSubrange( 0.0 );
  TEST_EQUALITY_CONST( sample, -0.5 );

  sample = tab_distribution->sampleInSubrange( 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareUniformDistribution, sampleInSubrange )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<si::energy> sample =
    unit_aware_tab_distribution->sampleInSubrange( 0.5*si::joule );
  TEST_EQUALITY_CONST( sample, 0.0*si::joule );

  sample = unit_aware_tab_distribution->sampleInSubrange( 0.5*si::joule );
  TEST_EQUALITY_CONST( sample, 0.25*si::joule );

  sample = unit_aware_tab_distribution->sampleInSubrange( 0.5*si::joule );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.5*si::joule, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( UniformDistribution, sampleWithRandomNumberInSubrange )
{
  double sample = tab_distribution->sampleWithRandomNumberInSubrange( 0.0, 0.0 );
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = tab_distribution->sampleWithRandomNumberInSubrange( 0.5, 0.0 );
  TEST_EQUALITY_CONST( sample, -0.5 );

  sample = tab_distribution->sampleWithRandomNumberInSubrange( 1.0, 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0, 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the unit aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareUniformDistribution,
		   sampleWithRandomNumberInSubrange )
{
  quantity<si::energy> sample =
    unit_aware_tab_distribution->sampleWithRandomNumberInSubrange(
							  0.0, 0.5*si::joule );
  TEST_EQUALITY_CONST( sample, 0.0*si::joule );

  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange(
							  0.5, 0.5*si::joule );
  TEST_EQUALITY_CONST( sample, 0.25*si::joule );

  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange(
							  1.0, 0.5*si::joule );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.5*si::joule, 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( UniformDistribution, getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfIndepVar(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware distribution independent
// variable can be returned
TEUCHOS_UNIT_TEST( UnitAwareUniformDistribution, getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfIndepVar(),
		       1.0*si::joule );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( UniformDistribution, getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfIndepVar(), -1.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware distribution independent
// variable can be returned
TEUCHOS_UNIT_TEST( UnitAwareUniformDistribution, getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfIndepVar(),
		       0.0*si::joule );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
TEUCHOS_UNIT_TEST( UniformDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( distribution->getDistributionType(),
		       Utility::UNIFORM_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type can be returned
TEUCHOS_UNIT_TEST( UnitAwareUniformDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getDistributionType(),
		       Utility::UNIFORM_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
TEUCHOS_UNIT_TEST( UniformDistribution, isTabular )
{
  TEST_ASSERT( distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is tabular
TEUCHOS_UNIT_TEST( UnitAwareUniformDistribution, isTabular )
{
  TEST_ASSERT( unit_aware_distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
TEUCHOS_UNIT_TEST( UniformDistribution, isContinuous )
{
  TEST_ASSERT( distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is continuous
TEUCHOS_UNIT_TEST( UnitAwareUniformDistribution, isContinuous )
{
  TEST_ASSERT( unit_aware_distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is compatible with the interpolation type
TEUCHOS_UNIT_TEST( UniformDistribution, isCompatibleWithInterpType )
{
  TEST_ASSERT( distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  TEST_ASSERT( distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LogLog>() );

  // Create another distribution that is compatible with all interpolation
  // types
  Utility::UniformDistribution test_dist( 1.0, 2.0, 1.0 );

  TEST_ASSERT( test_dist.isCompatibleWithInterpType<Utility::LinLin>() );
  TEST_ASSERT( test_dist.isCompatibleWithInterpType<Utility::LinLog>() );
  TEST_ASSERT( test_dist.isCompatibleWithInterpType<Utility::LogLin>() );
  TEST_ASSERT( test_dist.isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is compatible with the interp type
TEUCHOS_UNIT_TEST( UnitAwareUniformDistribution, isCompatibleWithInterpType )
{
  TEST_ASSERT( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  TEST_ASSERT( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  TEST_ASSERT( unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  TEST_ASSERT( unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );

  // Create another distribution that is compatible with all interpolation
  // types
  Utility::UnitAwareUniformDistribution<si::energy,si::amount>
    test_dist( 1.0*si::joule, 2.0*si::joule, 1.0*si::mole );

  TEST_ASSERT( test_dist.isCompatibleWithInterpType<Utility::LinLin>() );
  TEST_ASSERT( test_dist.isCompatibleWithInterpType<Utility::LinLog>() );
  TEST_ASSERT( test_dist.isCompatibleWithInterpType<Utility::LogLin>() );
  TEST_ASSERT( test_dist.isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be written to an xml file
TEUCHOS_UNIT_TEST( UniformDistribution, toParameterList )
{
  Teuchos::RCP<Utility::UniformDistribution> true_distribution =
   Teuchos::rcp_dynamic_cast<Utility::UniformDistribution>( distribution );

  Teuchos::ParameterList parameter_list;

  parameter_list.set<Utility::UniformDistribution>( "test distribution",
						     *true_distribution );

  Teuchos::writeParameterListToXmlFile( parameter_list,
					"uniform_dist_test_list.xml" );

  Teuchos::RCP<Teuchos::ParameterList> read_parameter_list =
    Teuchos::getParametersFromXmlFile( "uniform_dist_test_list.xml" );

  TEST_EQUALITY( parameter_list, *read_parameter_list );

  Teuchos::RCP<Utility::UniformDistribution>
    copy_distribution( new Utility::UniformDistribution );

  *copy_distribution =
    read_parameter_list->get<Utility::UniformDistribution>(
							  "test distribution");

  TEST_EQUALITY( *copy_distribution, *true_distribution );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be written to an xml file
TEUCHOS_UNIT_TEST( UnitAwareUniformDistribution, toParameterList )
{
  typedef Utility::UnitAwareUniformDistribution<si::energy,si::amount> UnitAwareUniformDistribution;

  Teuchos::RCP<UnitAwareUniformDistribution> true_distribution =
    Teuchos::rcp_dynamic_cast<UnitAwareUniformDistribution>( unit_aware_distribution );

  Teuchos::ParameterList parameter_list;

  parameter_list.set<UnitAwareUniformDistribution>( "test distribution",
						    *true_distribution );

  Teuchos::writeParameterListToXmlFile( parameter_list,
					"unit_aware_uniform_dist_test_list.xml" );

  Teuchos::RCP<Teuchos::ParameterList> read_parameter_list =
    Teuchos::getParametersFromXmlFile( "unit_aware_uniform_dist_test_list.xml" );

  TEST_EQUALITY( parameter_list, *read_parameter_list );

  Teuchos::RCP<UnitAwareUniformDistribution>
    copy_distribution( new UnitAwareUniformDistribution );

  *copy_distribution =
    read_parameter_list->get<UnitAwareUniformDistribution>(
							  "test distribution");

  TEST_EQUALITY( *copy_distribution, *true_distribution );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be read from an xml file
TEUCHOS_UNIT_TEST( UniformDistribution, fromParameterList )
{
  Utility::UniformDistribution xml_distribution =
    test_dists_list->get<Utility::UniformDistribution>( "Uniform Distribution A" );

  TEST_EQUALITY_CONST( xml_distribution.getLowerBoundOfIndepVar(), -1.0 );
  TEST_EQUALITY_CONST( xml_distribution.getUpperBoundOfIndepVar(), 1.0 );
  TEST_EQUALITY_CONST( xml_distribution.evaluate( 0.0 ), 2.0 );

  xml_distribution =
    test_dists_list->get<Utility::UniformDistribution>( "Uniform Distribution B" );

  TEST_EQUALITY_CONST( xml_distribution.getLowerBoundOfIndepVar(), 0.0 );
  TEST_EQUALITY_CONST( xml_distribution.getUpperBoundOfIndepVar(),
		       2*Utility::PhysicalConstants::pi );
  TEST_EQUALITY_CONST( xml_distribution.evaluate( 1.0 ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be read from an xml file
TEUCHOS_UNIT_TEST( UnitAwareUniformDistribution, fromParameterList )
{
  typedef Utility::UnitAwareUniformDistribution<si::energy,si::amount> UnitAwareUniformDistribution;

  UnitAwareUniformDistribution xml_distribution =
    test_dists_list->get<UnitAwareUniformDistribution>( "Unit-Aware Uniform Distribution A" );

  TEST_EQUALITY_CONST( xml_distribution.getLowerBoundOfIndepVar(), 0.0*si::joule );
  TEST_EQUALITY_CONST( xml_distribution.getUpperBoundOfIndepVar(), 10.0*si::joule);
  TEST_EQUALITY_CONST( xml_distribution.evaluate( 5.0*si::joule ), 3.0*si::mole );

  xml_distribution =
    test_dists_list->get<UnitAwareUniformDistribution>( "Unit-Aware Uniform Distribution B" );

  TEST_EQUALITY_CONST( xml_distribution.getLowerBoundOfIndepVar(), 0.0*si::joule );
  TEST_EQUALITY_CONST( xml_distribution.getUpperBoundOfIndepVar(),
		       Utility::PhysicalConstants::pi*si::joule );
  TEST_EQUALITY_CONST( xml_distribution.evaluate( 1.0*si::joule ), 1.0*si::mole );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be scaled
TEUCHOS_UNIT_TEST_TEMPLATE_4_DECL( UnitAwareUniformDistribution,
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

  // Copy from a unitless distribution to distribution type A (static method)
  Utility::UnitAwareUniformDistribution<IndepUnitA,DepUnitA>
    unit_aware_dist_a_copy = Utility::UnitAwareUniformDistribution<IndepUnitA,DepUnitA>::fromUnitlessDistribution( *Teuchos::rcp_dynamic_cast<Utility::UniformDistribution>( distribution ) );

  // Copy from distribution type A to distribution type B (explicit cast)
  Utility::UnitAwareUniformDistribution<IndepUnitB,DepUnitB>
    unit_aware_dist_b_copy( unit_aware_dist_a_copy );

  IndepQuantityA indep_quantity_a =
    Utility::QuantityTraits<IndepQuantityA>::initializeQuantity( -1.0 );
  InverseIndepQuantityA inv_indep_quantity_a =
    Utility::QuantityTraits<InverseIndepQuantityA>::initializeQuantity( 0.5 );
  DepQuantityA dep_quantity_a =
    Utility::QuantityTraits<DepQuantityA>::initializeQuantity( 2.0 );

  IndepQuantityB indep_quantity_b( indep_quantity_a );
  InverseIndepQuantityB inv_indep_quantity_b( inv_indep_quantity_a );
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

  Utility::setQuantity( indep_quantity_a, 1.0 );
  Utility::setQuantity( inv_indep_quantity_a, 0.5 );
  Utility::setQuantity( dep_quantity_a, 2.0 );

  indep_quantity_b = IndepQuantityB( indep_quantity_a );
  inv_indep_quantity_b = InverseIndepQuantityB( inv_indep_quantity_a );
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
typedef si::length si_length;
typedef cgs::length cgs_length;
typedef si::mass si_mass;
typedef cgs::mass cgs_mass;
typedef si::amount si_amount;
typedef si::dimensionless si_dimensionless;
typedef cgs::dimensionless cgs_dimensionless;

TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareUniformDistribution,
				      explicit_conversion,
				      si_energy,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareUniformDistribution,
				      explicit_conversion,
				      cgs_energy,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareUniformDistribution,
				      explicit_conversion,
				      si_length,
				      si_energy,
				      cgs_length,
				      cgs_energy );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareUniformDistribution,
				      explicit_conversion,
				      cgs_length,
				      cgs_energy,
				      si_length,
				      si_energy );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareUniformDistribution,
				      explicit_conversion,
				      si_length,
				      si_mass,
				      cgs_length,
				      cgs_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareUniformDistribution,
				      explicit_conversion,
				      cgs_length,
				      cgs_mass,
				      si_length,
				      si_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareUniformDistribution,
				      explicit_conversion,
				      si_length,
				      void,
				      cgs_length,
				      void );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareUniformDistribution,
				      explicit_conversion,
				      cgs_length,
				      void,
				      si_length,
				      void );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareUniformDistribution,
				      explicit_conversion,
				      void,
				      si_mass,
				      void,
				      cgs_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareUniformDistribution,
				      explicit_conversion,
				      void,
				      cgs_mass,
				      void,
				      si_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareUniformDistribution,
				      explicit_conversion,
				      si_length,
				      si_dimensionless,
				      cgs_length,
				      cgs_dimensionless );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareUniformDistribution,
				      explicit_conversion,
				      cgs_length,
				      cgs_dimensionless,
				      si_length,
				      si_dimensionless );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareUniformDistribution,
				      explicit_conversion,
				      si_dimensionless,
				      si_length,
				      cgs_dimensionless,
				      cgs_length );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareUniformDistribution,
				      explicit_conversion,
				      cgs_dimensionless,
				      cgs_length,
				      si_dimensionless,
				      si_length );

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_dists_xml_file;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_dists_xml_file",
                   &test_dists_xml_file,
                   "Test distributions xml file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  TEUCHOS_ADD_TYPE_CONVERTER( Utility::UniformDistribution );
  typedef Utility::UnitAwareUniformDistribution<si::energy,si::amount> UnitAwareUniformDistribution;
  TEUCHOS_ADD_TYPE_CONVERTER( UnitAwareUniformDistribution );

  test_dists_list = Teuchos::getParametersFromXmlFile( test_dists_xml_file );

  // Initialize the unit-aware distributions
  unit_aware_tab_distribution.reset(
	     new Utility::UnitAwareUniformDistribution<si::energy,si::amount>(
				      quantity<si::energy>( 0.0*si::joule ),
				      quantity<si::energy>( 1.0*si::joule ),
				      quantity<si::amount>( 1.0*si::mole ) ) );

  unit_aware_distribution = unit_aware_tab_distribution;

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstUniformDistribution.cpp
//---------------------------------------------------------------------------//

