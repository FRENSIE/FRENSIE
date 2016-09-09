//---------------------------------------------------------------------------//
//!
//! \file   tstNormalDistribution.cpp
//! \author Alex Robinson
//! \brief  Normal distribution unit tests.
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
#include "Utility_NormalDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_RandomNumberGenerator.hpp"
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

Teuchos::RCP<Utility::OneDDistribution> distribution(
				 new Utility::NormalDistribution( 0.0, 1.0 ) );

Teuchos::RCP<Utility::UnitAwareOneDDistribution<cgs::length,si::amount> > unit_aware_distribution( new Utility::UnitAwareNormalDistribution<cgs::length,si::amount>( 0.0*si::meter, 0.01*si::meter, 0.5*si::mole, -Utility::QuantityTraits<quantity<si::length> >::inf(), Utility::QuantityTraits<quantity<si::length> >::inf() ) );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( NormalDistribution, evaluate )
{
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), 1.0 );
  TEST_EQUALITY( distribution->evaluate( 2.0 ), exp( -4.0/2.0 ) );
  TEST_EQUALITY( distribution->evaluate( -2.0 ), exp( -4.0/2.0 ) );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareNormalDistribution, evaluate )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*cgs::centimeter ),
		       0.5*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 2.0*cgs::centimeter ),
		       0.5*exp( -4.0/2.0 )*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( -2.0*cgs::centimeter ),
		       0.5*exp( -4.0/2.0 )*si::mole );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( NormalDistribution, evaluatePDF )
{
  double center_value = 1.0/sqrt( 2.0*Utility::PhysicalConstants::pi );
  double off_center_value = center_value*exp( -4.0/2.0 );

  TEST_EQUALITY_CONST( distribution->evaluatePDF( 0.0 ), center_value);
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 2.0 ), off_center_value );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -2.0 ), off_center_value );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware PDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareNormalDistribution, evaluatePDF )
{
  double center_value = 1.0/sqrt( 2.0*Utility::PhysicalConstants::pi );

  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 0.0*cgs::centimeter ),
		       center_value/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 2.0*cgs::centimeter ),
		       center_value*exp( -4.0/2.0 )/cgs::centimeter );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( -2.0*cgs::centimeter ),
		       center_value*exp( -4.0/2.0 )/cgs::centimeter );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( NormalDistribution, sample_static )
{
  std::vector<double> fake_stream( 11 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.9;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.2;
  fake_stream[6] = 0.049787;
  fake_stream[7] = 0.449329;
  fake_stream[8] = 0.5;
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.4;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = Utility::NormalDistribution::sample( 0.0, 1.0 );
  TEST_FLOATING_EQUALITY( sample, 0.69314718055995, 1e-14 );

  sample = Utility::NormalDistribution::sample( 0.0, 1.0 );
  TEST_FLOATING_EQUALITY( sample, -0.69314718055995, 1e-14 );

  sample = Utility::NormalDistribution::sample( 0.0, 1.0 );
  TEST_FLOATING_EQUALITY( sample, -0.69314718055995, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareNormalDistribution, sample_static )
{
  std::vector<double> fake_stream( 11 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.9;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.2;
  fake_stream[6] = 0.049787;
  fake_stream[7] = 0.449329;
  fake_stream[8] = 0.5;
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.4;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<cgs::length> sample =
    Utility::UnitAwareNormalDistribution<cgs::length>::sample(
				    0.0*cgs::centimeter, 1.0*cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( sample,
				  0.69314718055995*cgs::centimeter,
				  1e-14 );

  sample = Utility::UnitAwareNormalDistribution<cgs::length>::sample(
				    0.0*cgs::centimeter, 1.0*cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( sample,
				  -0.69314718055995*cgs::centimeter,
				  1e-14 );

  sample = Utility::UnitAwareNormalDistribution<cgs::length>::sample(
				    0.0*cgs::centimeter, 1.0*cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( sample,
				  -0.69314718055995*cgs::centimeter,
				  1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( NormalDistribution, sampleAndRecordTrials_static )
{
  std::vector<double> fake_stream( 11 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.9;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.2;
  fake_stream[6] = 0.049787;
  fake_stream[7] = 0.449329;
  fake_stream[8] = 0.5;
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.4;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned trials = 0;

  double sample = Utility::NormalDistribution::sampleAndRecordTrials(
							    trials, 0.0, 1.0 );
  TEST_FLOATING_EQUALITY( sample, 0.69314718055995, 1e-14 );
  TEST_EQUALITY_CONST( 1.0/trials, 1.0 );

  sample = Utility::NormalDistribution::sampleAndRecordTrials(
							    trials, 0.0, 1.0 );
  TEST_FLOATING_EQUALITY( sample, -0.69314718055995, 1e-14 );
  TEST_EQUALITY_CONST( 2.0/trials, 1.0 );

  sample = Utility::NormalDistribution::sampleAndRecordTrials(
							    trials, 0.0, 1.0 );
  TEST_FLOATING_EQUALITY( sample, -0.69314718055995, 1e-14 );
  TEST_EQUALITY_CONST( 3.0/trials, 0.75 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareNormalDistribution, sampleAndRecordTrials_static )
{
  std::vector<double> fake_stream( 11 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.9;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.2;
  fake_stream[6] = 0.049787;
  fake_stream[7] = 0.449329;
  fake_stream[8] = 0.5;
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.4;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned trials = 0;

  quantity<cgs::length> sample =
    Utility::UnitAwareNormalDistribution<cgs::length>::sampleAndRecordTrials(
			    trials, 0.0*cgs::centimeter, 1.0*cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( sample,
				  0.69314718055995*cgs::centimeter,
				  1e-14 );
  TEST_EQUALITY_CONST( 1.0/trials, 1.0 );

  sample = Utility::UnitAwareNormalDistribution<cgs::length>::sampleAndRecordTrials(
			    trials, 0.0*cgs::centimeter, 1.0*cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( sample,
				  -0.69314718055995*cgs::centimeter,
				  1e-14 );
  TEST_EQUALITY_CONST( 2.0/trials, 1.0 );

  sample = Utility::UnitAwareNormalDistribution<cgs::length>::sampleAndRecordTrials(
			    trials, 0.0*cgs::centimeter, 1.0*cgs::centimeter );
  UTILITY_TEST_FLOATING_EQUALITY( sample,
				  -0.69314718055995*cgs::centimeter,
				  1e-14 );
  TEST_EQUALITY_CONST( 3.0/trials, 0.75 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( NormalDistribution, sample )
{
  std::vector<double> fake_stream( 11 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.9;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.2;
  fake_stream[6] = 0.049787;
  fake_stream[7] = 0.449329;
  fake_stream[8] = 0.5;
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.4;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 0.69314718055995, 1e-14 );

  sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, -0.69314718055995, 1e-14 );

  sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, -0.69314718055995, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareNormalDistribution, sample )
{
  std::vector<double> fake_stream( 11 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.9;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.2;
  fake_stream[6] = 0.049787;
  fake_stream[7] = 0.449329;
  fake_stream[8] = 0.5;
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.4;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<cgs::length> sample = unit_aware_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample,
				  0.69314718055995*cgs::centimeter,
				  1e-14 );

  sample = unit_aware_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample,
				  -0.69314718055995*cgs::centimeter,
				  1e-14 );

  sample = unit_aware_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample,
				  -0.69314718055995*cgs::centimeter,
				  1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( NormalDistribution, sampleAndRecordTrials )
{
  std::vector<double> fake_stream( 11 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.9;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.2;
  fake_stream[6] = 0.049787;
  fake_stream[7] = 0.449329;
  fake_stream[8] = 0.5;
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.4;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned trials = 0;

  double sample = distribution->sampleAndRecordTrials( trials );
  TEST_FLOATING_EQUALITY( sample, 0.69314718055995, 1e-14 );
  TEST_EQUALITY_CONST( 1.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_FLOATING_EQUALITY( sample, -0.69314718055995, 1e-14 );
  TEST_EQUALITY_CONST( 2.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_FLOATING_EQUALITY( sample, -0.69314718055995, 1e-14 );
  TEST_EQUALITY_CONST( 3.0/trials, 0.75 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareNormalDistribution, sampleAndRecordTrials )
{
  std::vector<double> fake_stream( 11 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.9;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.2;
  fake_stream[6] = 0.049787;
  fake_stream[7] = 0.449329;
  fake_stream[8] = 0.5;
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.4;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned trials = 0;

  quantity<cgs::length> sample =
    unit_aware_distribution->sampleAndRecordTrials( trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample,
				  0.69314718055995*cgs::centimeter,
				  1e-14 );
  TEST_EQUALITY_CONST( 1.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample,
				  -0.69314718055995*cgs::centimeter,
				  1e-14 );
  TEST_EQUALITY_CONST( 2.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample,
				  -0.69314718055995*cgs::centimeter,
				  1e-14 );
  TEST_EQUALITY_CONST( 3.0/trials, 0.75 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( NormalDistribution, getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfIndepVar(),
		       std::numeric_limits<double>::infinity() );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware distribution independent
// variable can be returned
TEUCHOS_UNIT_TEST( UnitAwareNormalDistribution, getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfIndepVar(),
		       Utility::QuantityTraits<quantity<cgs::length> >::inf());
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( NormalDistribution, getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfIndepVar(),
		       -std::numeric_limits<double>::infinity() );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware distribution independent
// variable can be returned
TEUCHOS_UNIT_TEST( UnitAwareNormalDistribution, getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfIndepVar(),
		       -Utility::QuantityTraits<quantity<cgs::length> >::inf());
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
TEUCHOS_UNIT_TEST( NormalDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( distribution->getDistributionType(),
		       Utility::NORMAL_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type can be returned
TEUCHOS_UNIT_TEST( UnitAwareNormalDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getDistributionType(),
		       Utility::NORMAL_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
TEUCHOS_UNIT_TEST( NormalDistribution, isTabular )
{
  TEST_ASSERT( !distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is tabular
TEUCHOS_UNIT_TEST( UnitAwareNormalDistribution, isTabular )
{
  TEST_ASSERT( !unit_aware_distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
TEUCHOS_UNIT_TEST( NormalDistribution, isContinuous )
{
  TEST_ASSERT( distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is continuous
TEUCHOS_UNIT_TEST( UnitAwareNormalDistribution, isContinuous )
{
  TEST_ASSERT( unit_aware_distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is compatible with the interpolation type
TEUCHOS_UNIT_TEST( NormalDistribution, isCompatibleWithInterpType )
{
  TEST_ASSERT( distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  TEST_ASSERT( distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LogLog>() );

  // Create another distribution that is compatible with all interpolation
  // types
  Utility::NormalDistribution test_dist( 10.0, 1.0, 1.0, 19.0 );

  TEST_ASSERT( test_dist.isCompatibleWithInterpType<Utility::LinLin>() );
  TEST_ASSERT( test_dist.isCompatibleWithInterpType<Utility::LinLog>() );
  TEST_ASSERT( test_dist.isCompatibleWithInterpType<Utility::LogLin>() );
  TEST_ASSERT( test_dist.isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is compatible with the interp type
TEUCHOS_UNIT_TEST( UnitAwareNormalDistribution, isCompatibleWithInterpType )
{
  TEST_ASSERT( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  TEST_ASSERT( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  TEST_ASSERT( unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  TEST_ASSERT( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );

  // Create another distribution that is compatible with all interpolation
  // types
  Utility::UnitAwareNormalDistribution<cgs::length,si::amount>
    test_dist( 10.0*si::meter,
               1.0*si::meter,
               1.0*si::mole,
               1.0*si::meter,
               19.0*si::meter );

  TEST_ASSERT( test_dist.isCompatibleWithInterpType<Utility::LinLin>() );
  TEST_ASSERT( test_dist.isCompatibleWithInterpType<Utility::LinLog>() );
  TEST_ASSERT( test_dist.isCompatibleWithInterpType<Utility::LogLin>() );
  TEST_ASSERT( test_dist.isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be written to an xml file
TEUCHOS_UNIT_TEST( NormalDistribution, toParameterList )
{
  Teuchos::RCP<Utility::NormalDistribution> true_distribution =
    Teuchos::rcp_dynamic_cast<Utility::NormalDistribution>( distribution );

  Teuchos::ParameterList parameter_list;

  parameter_list.set<Utility::NormalDistribution>( "test distribution",
						     *true_distribution );

  Teuchos::writeParameterListToXmlFile( parameter_list,
					"normal_dist_test_list.xml" );

  Teuchos::RCP<Teuchos::ParameterList> read_parameter_list =
    Teuchos::getParametersFromXmlFile( "normal_dist_test_list.xml" );

  TEST_EQUALITY( parameter_list, *read_parameter_list );

  Teuchos::RCP<Utility::NormalDistribution>
    copy_distribution( new Utility::NormalDistribution );

  *copy_distribution = read_parameter_list->get<Utility::NormalDistribution>(
							  "test distribution");

  TEST_EQUALITY( *copy_distribution, *true_distribution );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be written to an xml file
TEUCHOS_UNIT_TEST( UnitAwareNormalDistribution, toParameterList )
{
  typedef Utility::UnitAwareNormalDistribution<cgs::length,si::amount>
    UnitAwareNormalDistribution;

  Teuchos::RCP<UnitAwareNormalDistribution> true_distribution =
    Teuchos::rcp_dynamic_cast<UnitAwareNormalDistribution>( unit_aware_distribution );

  Teuchos::ParameterList parameter_list;

  parameter_list.set<UnitAwareNormalDistribution>( "test distribution",
						   *true_distribution );

  Teuchos::writeParameterListToXmlFile( parameter_list,
				       "unit_aware_normal_dist_test_list.xml" );

  Teuchos::RCP<Teuchos::ParameterList> read_parameter_list =
    Teuchos::getParametersFromXmlFile( "unit_aware_normal_dist_test_list.xml" );

  TEST_EQUALITY( parameter_list, *read_parameter_list );

  Teuchos::RCP<UnitAwareNormalDistribution>
    copy_distribution( new UnitAwareNormalDistribution );

  *copy_distribution = read_parameter_list->get<UnitAwareNormalDistribution>(
							  "test distribution");

  TEST_EQUALITY( *copy_distribution, *true_distribution );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be read from an xml file
TEUCHOS_UNIT_TEST( NormalDistribution, fromParameterList )
{
  Utility::NormalDistribution read_distribution =
    test_dists_list->get<Utility::NormalDistribution>( "Normal Distribution A" );

  TEST_EQUALITY_CONST( read_distribution.getLowerBoundOfIndepVar(),
		       -std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( read_distribution.getUpperBoundOfIndepVar(),
		       std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( read_distribution.evaluate( 0.0 ), 1.0 );

  read_distribution =
    test_dists_list->get<Utility::NormalDistribution>( "Normal Distribution B" );

  TEST_EQUALITY_CONST( read_distribution.getLowerBoundOfIndepVar(),
		       -Utility::PhysicalConstants::pi );
  TEST_EQUALITY_CONST( read_distribution.getUpperBoundOfIndepVar(),
		       Utility::PhysicalConstants::pi );
  TEST_EQUALITY_CONST( read_distribution.evaluate( 0.0 ), 1.0 );

  read_distribution =
    test_dists_list->get<Utility::NormalDistribution>( "Normal Distribution C" );

  TEST_EQUALITY_CONST( read_distribution.getLowerBoundOfIndepVar(), 0.0 );
  TEST_EQUALITY_CONST( read_distribution.getUpperBoundOfIndepVar(), 2.0 );
  TEST_EQUALITY_CONST( read_distribution.evaluate( 1.0 ), 0.5 );

  read_distribution =
    test_dists_list->get<Utility::NormalDistribution>( "Normal Distribution D" );

  TEST_EQUALITY_CONST( read_distribution.getLowerBoundOfIndepVar(),
		       -std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( read_distribution.getUpperBoundOfIndepVar(),
		       std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( read_distribution.evaluate( 1.0 ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be read from an xml file
TEUCHOS_UNIT_TEST( UnitAwareNormalDistribution, fromParameterList )
{
  typedef Utility::UnitAwareNormalDistribution<cgs::length,si::amount>
    UnitAwareNormalDistribution;

  UnitAwareNormalDistribution read_distribution =
    test_dists_list->get<UnitAwareNormalDistribution>( "Unit-Aware Normal Distribution A" );

  TEST_EQUALITY_CONST( read_distribution.getLowerBoundOfIndepVar(),
		       -Utility::QuantityTraits<quantity<cgs::length> >::inf());
  TEST_EQUALITY_CONST( read_distribution.getUpperBoundOfIndepVar(),
		       Utility::QuantityTraits<quantity<cgs::length> >::inf() );
  TEST_EQUALITY_CONST( read_distribution.evaluate( 0.0*cgs::centimeter ),
		       1.0*si::mole );

  read_distribution =
    test_dists_list->get<UnitAwareNormalDistribution>( "Unit-Aware Normal Distribution B" );

  TEST_EQUALITY_CONST( read_distribution.getLowerBoundOfIndepVar(),
  		       -Utility::PhysicalConstants::pi*cgs::centimeter );
  TEST_EQUALITY_CONST( read_distribution.getUpperBoundOfIndepVar(),
  		       Utility::PhysicalConstants::pi*cgs::centimeter );
  TEST_EQUALITY_CONST( read_distribution.evaluate( 0.0*cgs::centimeter ),
		       1.0*si::mole );

  read_distribution =
    test_dists_list->get<UnitAwareNormalDistribution>( "Unit-Aware Normal Distribution C" );

  TEST_EQUALITY_CONST( read_distribution.getLowerBoundOfIndepVar(),
		       0.0*cgs::centimeter );
  TEST_EQUALITY_CONST( read_distribution.getUpperBoundOfIndepVar(),
		       2.0*cgs::centimeter );
  TEST_EQUALITY_CONST( read_distribution.evaluate( 1.0*cgs::centimeter ),
		       0.5*si::mole );

  read_distribution =
    test_dists_list->get<UnitAwareNormalDistribution>( "Unit-Aware Normal Distribution D" );

  TEST_EQUALITY_CONST( read_distribution.getLowerBoundOfIndepVar(),
  		       -Utility::QuantityTraits<quantity<cgs::length> >::inf());
  TEST_EQUALITY_CONST( read_distribution.getUpperBoundOfIndepVar(),
  		       Utility::QuantityTraits<quantity<cgs::length> >::inf());
  TEST_EQUALITY_CONST( read_distribution.evaluate( 1.0*cgs::centimeter ),
		       1.0*si::mole );
}

//---------------------------------------------------------------------------//
// Check that distributions can be scaled
TEUCHOS_UNIT_TEST_TEMPLATE_4_DECL( UnitAwareNormalDistribution,
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

  // Copy from unitless distribution to distribution type A (static method)
  Utility::UnitAwareNormalDistribution<IndepUnitA,DepUnitA>
    unit_aware_dist_a_copy = Utility::UnitAwareNormalDistribution<IndepUnitA,DepUnitA>::fromUnitlessDistribution( *Teuchos::rcp_dynamic_cast<Utility::NormalDistribution>( distribution ) );

  // Copy from distribution type A to distribution type B (explicit cast)
  Utility::UnitAwareNormalDistribution<IndepUnitB,DepUnitB>
    unit_aware_dist_b_copy( unit_aware_dist_a_copy );

  IndepQuantityA indep_quantity_a =
    Utility::QuantityTraits<IndepQuantityA>::initializeQuantity( 0.0 );
  InverseIndepQuantityA inv_indep_quantity_a =
    Utility::QuantityTraits<InverseIndepQuantityA>::initializeQuantity( 1.0/sqrt( 2.0*Utility::PhysicalConstants::pi ) );
  DepQuantityA dep_quantity_a =
    Utility::QuantityTraits<DepQuantityA>::initializeQuantity( 1.0 );

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

  Utility::setQuantity( indep_quantity_a, 2.0 );
  Utility::setQuantity( inv_indep_quantity_a, exp( -4.0/2.0 )/sqrt( 2.0*Utility::PhysicalConstants::pi ) );
  Utility::setQuantity( dep_quantity_a, exp( -4.0/2.0 ) );

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
typedef si::amount si_amount;
typedef si::length si_length;
typedef cgs::length cgs_length;
typedef si::mass si_mass;
typedef cgs::mass cgs_mass;
typedef si::dimensionless si_dimensionless;
typedef cgs::dimensionless cgs_dimensionless;

TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareNormalDistribution,
				      explicit_conversion,
				      si_energy,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareNormalDistribution,
				      explicit_conversion,
				      cgs_energy,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareNormalDistribution,
				      explicit_conversion,
				      si_energy,
				      si_length,
				      cgs_energy,
				      cgs_length );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareNormalDistribution,
				      explicit_conversion,
				      cgs_energy,
				      cgs_length,
				      si_energy,
				      si_length );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareNormalDistribution,
				      explicit_conversion,
				      si_energy,
				      si_mass,
				      cgs_energy,
				      cgs_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareNormalDistribution,
				      explicit_conversion,
				      cgs_energy,
				      cgs_mass,
				      si_energy,
				      si_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareNormalDistribution,
				      explicit_conversion,
				      si_energy,
				      si_dimensionless,
				      cgs_energy,
				      cgs_dimensionless );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareNormalDistribution,
				      explicit_conversion,
				      cgs_energy,
				      cgs_dimensionless,
				      si_energy,
				      si_dimensionless );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareNormalDistribution,
				      explicit_conversion,
				      si_energy,
				      void,
				      cgs_energy,
				      void );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareNormalDistribution,
				      explicit_conversion,
				      cgs_energy,
				      void,
				      si_energy,
				      void );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareNormalDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareNormalDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareNormalDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      KiloElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareNormalDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      MegaElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareNormalDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareNormalDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareNormalDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      ElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareNormalDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      MegaElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareNormalDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareNormalDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareNormalDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      ElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareNormalDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      KiloElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareNormalDistribution,
				      explicit_conversion,
				      void,
				      MegaElectronVolt,
				      void,
				      KiloElectronVolt );

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
  TEUCHOS_ADD_TYPE_CONVERTER( Utility::NormalDistribution );
  typedef Utility::UnitAwareNormalDistribution<cgs::length,si::amount> UnitAwareNormalDistribution;
  TEUCHOS_ADD_TYPE_CONVERTER( UnitAwareNormalDistribution );
  test_dists_list = Teuchos::getParametersFromXmlFile( test_dists_xml_file );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstNormalDistribution.cpp
//---------------------------------------------------------------------------//

