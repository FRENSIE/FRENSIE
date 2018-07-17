//---------------------------------------------------------------------------//
//!
//! \file   tstTabularDistribution.cpp
//! \author Alex Robinson
//! \brief  Tabular distribution unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/cgs.hpp>
#include <boost/units/io.hpp>

// FRENSIE Includes
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTraits.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_ElectronVoltUnit.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

using boost::units::quantity;
using namespace Utility::Units;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

typedef std::tuple<Utility::LinLin,
                   Utility::LogLin,
                   Utility::LinLog,
                   Utility::LogLog
                  > TestInterpPolicies;

template<typename ArchivePair>
struct InterpPolicyArchiveList
{
  typedef std::tuple<
    std::tuple<Utility::LinLin,typename Utility::TupleElement<0,ArchivePair>::type,typename Utility::TupleElement<1,ArchivePair>::type>,
    std::tuple<Utility::LogLin,typename Utility::TupleElement<0,ArchivePair>::type,typename Utility::TupleElement<1,ArchivePair>::type>,
    std::tuple<Utility::LinLog,typename Utility::TupleElement<0,ArchivePair>::type,typename Utility::TupleElement<1,ArchivePair>::type>,
    std::tuple<Utility::LogLog,typename Utility::TupleElement<0,ArchivePair>::type,typename Utility::TupleElement<1,ArchivePair>::type>
   > type;
};

template<typename... Types>
struct CreateInterpPolicyArchiveList;

template<typename T, typename... Types>
struct CreateInterpPolicyArchiveList<T,Types...>
{
  typedef decltype(std::tuple_cat(typename InterpPolicyArchiveList<T>::type(), typename CreateInterpPolicyArchiveList<Types...>::type())) type;
};

template<typename T>
struct CreateInterpPolicyArchiveList<T>
{
  typedef typename InterpPolicyArchiveList<T>::type type;
};

template<typename... Types>
struct CreateInterpPolicyArchiveList<std::true_type,std::tuple<Types...> > : public CreateInterpPolicyArchiveList<Types...>
{ /* ... */ };

template<typename... Types>
struct CreateInterpPolicyArchiveList<std::false_type,std::tuple<Types...> > : public CreateInterpPolicyArchiveList<std::tuple<Types...> >
{ /* ... */ };

typedef typename CreateInterpPolicyArchiveList<std::true_type,TestArchiveHelper::TestArchives>::type InterpPoliciesAndArchives;

typedef std::tuple<
  std::tuple<si::energy,si::amount,cgs::energy,si::amount>,
  std::tuple<cgs::energy,si::amount,si::energy,si::amount>,
  std::tuple<si::energy,si::length,cgs::energy,cgs::length>,
  std::tuple<cgs::energy,cgs::length,si::energy,si::length>,
  std::tuple<si::energy,si::mass,cgs::energy,cgs::mass>,
  std::tuple<cgs::energy,cgs::mass,si::energy,si::mass>,
  std::tuple<si::energy,si::dimensionless,cgs::energy,cgs::dimensionless>,
  std::tuple<cgs::energy,cgs::dimensionless,si::energy,si::dimensionless>,
  std::tuple<si::energy,void*,cgs::energy,void*>,
  std::tuple<cgs::energy,void*,si::energy,void*>,
  std::tuple<ElectronVolt,si::amount,si::energy,si::amount>,
  std::tuple<ElectronVolt,si::amount,cgs::energy,si::amount>,
  std::tuple<ElectronVolt,si::amount,KiloElectronVolt,si::amount>,
  std::tuple<ElectronVolt,si::amount,MegaElectronVolt,si::amount>,
  std::tuple<KiloElectronVolt,si::amount,si::energy,si::amount>,
  std::tuple<KiloElectronVolt,si::amount,cgs::energy,si::amount>,
  std::tuple<KiloElectronVolt,si::amount,ElectronVolt,si::amount>,
  std::tuple<KiloElectronVolt,si::amount,MegaElectronVolt,si::amount>,
  std::tuple<MegaElectronVolt,si::amount,si::energy,si::amount>,
  std::tuple<MegaElectronVolt,si::amount,cgs::energy,si::amount>,
  std::tuple<MegaElectronVolt,si::amount,ElectronVolt,si::amount>,
  std::tuple<MegaElectronVolt,si::amount,KiloElectronVolt,si::amount>,
  std::tuple<void*,MegaElectronVolt,void*,KiloElectronVolt>
 > TestUnitTypeQuads;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<Utility::UnivariateDistribution> distribution;
std::shared_ptr<Utility::TabularUnivariateDistribution> tab_distribution;

std::shared_ptr<Utility::UnitAwareUnivariateDistribution<MegaElectronVolt,si::amount> >
  unit_aware_distribution;
std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<MegaElectronVolt,si::amount> >
unit_aware_tab_distribution;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Initialize the distribution
template<typename InterpolationPolicy, typename BaseDistribution>
void initialize( std::shared_ptr<BaseDistribution>& dist )
{
  // Use the basic constructor
  std::vector<typename BaseDistribution::IndepQuantity>
    independent_values( 4 );
  Utility::setQuantity( independent_values[0], 1e-3 );
  Utility::setQuantity( independent_values[1], 1e-2 );
  Utility::setQuantity( independent_values[2], 1e-1 );
  Utility::setQuantity( independent_values[3], 1.0 );

  std::vector<typename BaseDistribution::DepQuantity> dependent_values( 4 );
  Utility::setQuantity( dependent_values[0], 1e2 );
  Utility::setQuantity( dependent_values[1], 1e1 );
  Utility::setQuantity( dependent_values[2], 1.0 );
  Utility::setQuantity( dependent_values[3], 1e-1 );

  dist.reset(new Utility::UnitAwareTabularDistribution<InterpolationPolicy,typename BaseDistribution::IndepUnit, typename BaseDistribution::DepUnit>(
							  independent_values,
							  dependent_values ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST_TEMPLATE( TabularDistribution,
                            evaluate,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( distribution );

  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1e-3 ), 1e2 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1e-2 ), 1e1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1e-1 ), 1.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1.0 ), 1e-1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 2.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularDistribution,
                            evaluate,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*MeV ),
		       0.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1e-3*MeV ),
		       1e2*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1e-2*MeV ),
		       1e1*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1e-1*MeV ),
		       1.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.0*MeV ),
		       1e-1*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 2.0*MeV ),
		       0.0*si::mole );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
FRENSIE_UNIT_TEST_TEMPLATE( TabularDistribution,
                            evaluatePDF,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( distribution );

  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 0.0 ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluatePDF( 1e-3 ),
			  67.340006734,
			  1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluatePDF( 1e-2 ),
			  6.7340006734,
			  1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluatePDF( 1e-1 ),
			  0.67340006734,
			  1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluatePDF( 1.0 ),
			  0.067340006734,
			  1e-6 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 2.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware PDF can be evaluated
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularDistribution,
                            evaluatePDF,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 0.0*MeV ),
		       0.0/MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			     unit_aware_distribution->evaluatePDF( 1e-3*MeV ),
			     67.340006734/MeV,
			     1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			     unit_aware_distribution->evaluatePDF( 1e-2*MeV ),
			     6.7340006734/MeV,
			     1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			     unit_aware_distribution->evaluatePDF( 1e-1*MeV ),
			     0.67340006734/MeV,
			     1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			      unit_aware_distribution->evaluatePDF( 1.0*MeV ),
			      0.067340006734/MeV,
			      1e-6 );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 2.0*MeV ),
		       0.0/MeV );
}

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated
FRENSIE_UNIT_TEST_TEMPLATE( TabularDistribution,
                            evaluateCDF,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( tab_distribution );

  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( 0.0 ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateCDF( 1e-3 ),
			  0.0000000000,
			  1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateCDF( 1e-2 ),
			  0.33333333333,
			  1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateCDF( 1e-1 ),
			  0.66666666667,
			  1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateCDF( 1.0 ),
			  1.0000000000,
			  1e-10 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( 2.0 ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware CDF can be evaluated
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularDistribution,
                            evaluateCDF,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( unit_aware_tab_distribution );

  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateCDF( 0.0*MeV ),
		       0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateCDF( 1e-3*MeV ),
			  0.0000000000,
			  1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateCDF( 1e-2*MeV ),
			  0.33333333333,
			  1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateCDF( 1e-1*MeV ),
			  0.66666666667,
			  1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateCDF( 1.0*MeV ),
			  1.0000000000,
			  1e-10 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateCDF( 2.0*MeV ),
		       1.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( TabularDistribution,
                            sample,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 1e-3 );

  sample = distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = distribution->sample();
  FRENSIE_CHECK_GREATER_OR_EQUAL( sample, 1e-3 );
  FRENSIE_CHECK_LESS_OR_EQUAL( sample, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularDistribution,
                            sample,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( unit_aware_distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<MegaElectronVolt> sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 1e-3*MeV );

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_GREATER_OR_EQUAL( sample, 1e-3*MeV );
  FRENSIE_CHECK_LESS_OR_EQUAL( sample, 1.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( TabularDistribution,
                            sampleAndRecordTrials,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0;

  double sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 1e-3 );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_GREATER_OR_EQUAL( sample, 1e-3 );
  FRENSIE_CHECK_LESS_OR_EQUAL( sample, 1.0 );
  FRENSIE_CHECK_EQUAL( 3.0/trials, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularDistribution,
                            sampleAndRecordTrials,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( unit_aware_distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0;

  quantity<MegaElectronVolt> sample =
    unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 1e-3*MeV );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-12 );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_GREATER_OR_EQUAL( sample, 1e-3*MeV );
  FRENSIE_CHECK_LESS_OR_EQUAL( sample, 1.0*MeV );
  FRENSIE_CHECK_EQUAL( 3.0/trials, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( TabularDistribution,
                            sampleAndRecordBinIndex,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( tab_distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  size_t bin_index;

  double sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 1e-3 );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_GREATER_OR_EQUAL( sample, 1e-3 );
  FRENSIE_CHECK_LESS_OR_EQUAL( sample, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularDistribution,
                            sampleAndRecordBinIndex,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( unit_aware_tab_distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  size_t bin_index;

  quantity<MegaElectronVolt> sample =
    unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 1e-3*MeV );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-12 );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_GREATER_OR_EQUAL( sample, 1e-3*MeV );
  FRENSIE_CHECK_LESS_OR_EQUAL( sample, 1.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( TabularDistribution,
                            sampleWithRandomNumber,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( tab_distribution );

  double sample = tab_distribution->sampleWithRandomNumber( 0.0 );
  FRENSIE_CHECK_EQUAL( sample, 1e-3 );

  sample = tab_distribution->sampleWithRandomNumber( 1.0 - 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularDistribution,
                            sampleWithRandomNumber,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( unit_aware_tab_distribution );

  quantity<MegaElectronVolt> sample =
    unit_aware_tab_distribution->sampleWithRandomNumber( 0.0 );
  FRENSIE_CHECK_EQUAL( sample, 1e-3*MeV );

  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 1.0 - 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from a subrange
FRENSIE_UNIT_TEST_TEMPLATE( TabularDistribution,
                            sampleInSubrange,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( tab_distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = tab_distribution->sampleInSubrange( 1e-1  );
  FRENSIE_CHECK_EQUAL( sample, 1e-3 );

  sample = tab_distribution->sampleInSubrange( 1e-1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1e-1, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = tab_distribution->sampleInSubrange( 1e-1 );
  FRENSIE_CHECK_GREATER_OR_EQUAL( sample, 1e-3 );
  FRENSIE_CHECK_LESS_OR_EQUAL( sample, 1e-1 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled from a subrange
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularDistribution,
                            sampleInSubrange,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( unit_aware_tab_distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<MegaElectronVolt> sample =
    unit_aware_tab_distribution->sampleInSubrange( 1e-1*MeV  );
  FRENSIE_CHECK_EQUAL( sample, 1e-3*MeV );

  sample = unit_aware_tab_distribution->sampleInSubrange( 1e-1*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1e-1*MeV, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = unit_aware_tab_distribution->sampleInSubrange( 1e-1*MeV );
  FRENSIE_CHECK_GREATER_OR_EQUAL( sample, 1e-3*MeV );
  FRENSIE_CHECK_LESS_OR_EQUAL( sample, 1e-1*MeV );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from a subrange
FRENSIE_UNIT_TEST_TEMPLATE( TabularDistribution,
                            sampleWithRandomNumberInSubrange,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( tab_distribution );

  double sample =
    tab_distribution->sampleWithRandomNumberInSubrange( 0.0, 1e-1  );
  FRENSIE_CHECK_EQUAL( sample, 1e-3 );

  sample = tab_distribution->sampleWithRandomNumberInSubrange( 1.0, 1e-1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1e-1, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled from a subrange
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularDistribution,
                            sampleWithRandomNumberInSubrange,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( unit_aware_tab_distribution );

  quantity<MegaElectronVolt> sample =
    unit_aware_tab_distribution->sampleWithRandomNumberInSubrange(
							       0.0, 1e-1*MeV );
  FRENSIE_CHECK_EQUAL( sample, 1e-3*MeV );

  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange(
							       1.0, 1e-1*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1e-1*MeV, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
FRENSIE_UNIT_TEST_TEMPLATE( TabularDistribution,
                            getUpperBoundOfIndepVar,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( distribution );

  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfIndepVar(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware distribution independent
// variable can be returned
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularDistribution,
                            getUpperBoundOfIndepVar,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfIndepVar(),
		       1.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
FRENSIE_UNIT_TEST_TEMPLATE( TabularDistribution,
                            getLowerBoundOfIndepVar,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( distribution );

  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfIndepVar(), 1e-3 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware distribution independent
// variable can be returned
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularDistribution,
                            getLowerBoundOfIndepVar,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfIndepVar(),
		       1e-3*MeV );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
FRENSIE_UNIT_TEST_TEMPLATE( TabularDistribution,
                            getDistributionType,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( distribution );

  FRENSIE_CHECK_EQUAL( distribution->getDistributionType(),
		       Utility::TABULAR_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type can be returned
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularDistribution,
                            getDistributionType,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getDistributionType(),
		       Utility::TABULAR_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
FRENSIE_UNIT_TEST_TEMPLATE( TabularDistribution,
                            isTabular,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( distribution );

  FRENSIE_CHECK( distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is tabular
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularDistribution,
                            isTabular,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( unit_aware_distribution );

  FRENSIE_CHECK( unit_aware_distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check that the distribution is continuous
FRENSIE_UNIT_TEST_TEMPLATE( TabularDistribution,
                            isContinuous,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( distribution );

  FRENSIE_CHECK( distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution is continuous
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularDistribution,
                            isContinuous,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( unit_aware_distribution );

  FRENSIE_CHECK( unit_aware_distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is compatible with the interpolation type
FRENSIE_UNIT_TEST_TEMPLATE( TabularDistribution,
                            isCompatibleWithInterpType,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( distribution );

  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LogLog>() );

  // if( boost::is_same<InterpolationPolicy,Utility::LinLin>::value )
  // {
  //   FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  // }
  // else
  // {
  //   FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  // }

  // if( boost::is_same<InterpolationPolicy,Utility::LinLog>::value )
  // {
  //   FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  // }
  // else
  // {
  //   FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  // }

  // if( boost::is_same<InterpolationPolicy,Utility::LogLin>::value )
  // {
  //   FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  // }
  // else
  // {
  //   FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  // }

  // if( boost::is_same<InterpolationPolicy,Utility::LogLog>::value )
  // {
  //   FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LogLog>() );
  // }
  // else
  // {
  //   FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogLog>() );
  // }
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is compatible with the interp type
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularDistribution,
                            isCompatibleWithInterpType,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( unit_aware_distribution );
  
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );

  // if( boost::is_same<InterpolationPolicy,Utility::LinLin>::value )
  // {
  //   FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  // }
  // else
  // {
  //   FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  // }

  // if( boost::is_same<InterpolationPolicy,Utility::LinLog>::value )
  // {
  //   FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  // }
  // else
  // {
  //   FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  // }

  // if( boost::is_same<InterpolationPolicy,Utility::LogLin>::value )
  // {
  //   FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  // }
  // else
  // {
  //   FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  // }

  // if( boost::is_same<InterpolationPolicy,Utility::LogLog>::value )
  // {
  //   FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );
  // }
  // else
  // {
  //   FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );
  // }
}

//---------------------------------------------------------------------------//
// Check that the distribution can be placed in a stream
FRENSIE_UNIT_TEST_TEMPLATE( TabularDistribution,
                            ostream_operator,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  std::ostringstream oss;

  oss << Utility::TabularDistribution<InterpolationPolicy>();

  Utility::VariantMap dist_data =
    Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Tabular Distribution",
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["interp"].toString(),
                       InterpolationPolicy::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["independent values"].toType<std::vector<double> >(),
                       std::vector<double>({(std::is_same<typename InterpolationPolicy::IndepVarProcessingTag,Utility::LinIndepVarProcessingTag>::value ? 0.0 : 0.1), 1.0}),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent values"].toType<std::vector<double> >(),
                       std::vector<double>({1.0, 1.0}) );
  
  oss.str( "" );
  oss.clear();
  
  oss << Utility::TabularDistribution<InterpolationPolicy>( {1, 2, 3}, {3, 2, 1} );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Tabular Distribution",
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["interp"].toString(),
                       InterpolationPolicy::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["independent values"].toType<std::vector<double> >(),
                       std::vector<double>({1.0, 2.0, 3.0}),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent values"].toType<std::vector<double> >(),
                       std::vector<double>({3.0, 2.0, 1.0}),
                       SHOW_LHS );

  oss.str( "" );
  oss.clear();

  std::unique_ptr<Utility::UnivariateDistribution> local_dist( new Utility::TabularDistribution<InterpolationPolicy>( {1, 2, 3}, {3, 2, 1} ) );

  oss << *local_dist;

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Tabular Distribution",
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["interp"].toString(),
                       InterpolationPolicy::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["independent values"].toType<std::vector<double> >(),
                       std::vector<double>({1.0, 2.0, 3.0}),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent values"].toType<std::vector<double> >(),
                       std::vector<double>({3.0, 2.0, 1.0}),
                       SHOW_LHS );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be placed in a stream
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularDistribution,
                            ostream_operator,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  std::ostringstream oss;

  oss << Utility::UnitAwareTabularDistribution<InterpolationPolicy,MegaElectronVolt,si::amount>();

  Utility::VariantMap dist_data =
    Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Tabular Distribution",
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<MegaElectronVolt>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::amount>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["interp"].toString(),
                       InterpolationPolicy::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["independent values"].toType<std::vector<quantity<MegaElectronVolt> > >(),
                       std::vector<quantity<MegaElectronVolt> >({(std::is_same<typename InterpolationPolicy::IndepVarProcessingTag,Utility::LinIndepVarProcessingTag>::value ? 0.0*MeV : 0.1*MeV), 1.0*MeV}),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent values"].toType<std::vector<quantity<si::amount> > >(),
                       std::vector<quantity<si::amount> >({1.0*si::mole, 1.0*si::mole}),
                       SHOW_LHS );

  oss.str( "" );
  oss.clear();
  
  oss << Utility::UnitAwareTabularDistribution<InterpolationPolicy,MegaElectronVolt,si::amount>( {1, 2, 3}, {3, 2, 1} );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Tabular Distribution",
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<MegaElectronVolt>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::amount>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["interp"].toString(),
                       InterpolationPolicy::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["independent values"].toType<std::vector<quantity<MegaElectronVolt> > >(),
                       std::vector<quantity<MegaElectronVolt> >({1.0*MeV, 2.0*MeV, 3.0*MeV}),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent values"].toType<std::vector<quantity<si::amount> > >(),
                       std::vector<quantity<si::amount> >({3.0*si::mole, 2.0*si::mole, 1.0*si::mole}),
                       SHOW_LHS );

  oss.str( "" );
  oss.clear();

  std::unique_ptr<Utility::UnitAwareUnivariateDistribution<MegaElectronVolt,si::amount> > local_dist( new Utility::UnitAwareTabularDistribution<InterpolationPolicy,MegaElectronVolt,si::amount>( {1, 2, 3}, {3, 2, 1} ) );

  oss << *local_dist;

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Tabular Distribution",
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<MegaElectronVolt>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::amount>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["interp"].toString(),
                       InterpolationPolicy::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["independent values"].toType<std::vector<quantity<MegaElectronVolt> > >(),
                       std::vector<quantity<MegaElectronVolt> >({1.0*MeV, 2.0*MeV, 3.0*MeV}),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent values"].toType<std::vector<quantity<si::amount> > >(),
                       std::vector<quantity<si::amount> >({3.0*si::mole, 2.0*si::mole, 1.0*si::mole}),
                       SHOW_LHS );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( TabularDistribution,
                                   archive,
                                   InterpPoliciesAndArchives )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  FETCH_TEMPLATE_PARAM( 1, RawOArchive );
  FETCH_TEMPLATE_PARAM( 2, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;
  
  std::string archive_base_name( "test_tabular_" );
  archive_base_name += InterpolationPolicy::name();
  archive_base_name += "_dist";

  std::ostringstream archive_ostream;

  // Create and archive some tabular distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );
    
    Utility::TabularDistribution<InterpolationPolicy> dist_a( {1.0, 2.0, 3.0, 4.0}, {4.0, 3.0, 2.0, 1.0} );

    initialize<InterpolationPolicy>( distribution );

    FRENSIE_REQUIRE_NO_THROW(
                            (*oarchive) << BOOST_SERIALIZATION_NVP( dist_a ) );
    FRENSIE_REQUIRE_NO_THROW(
                      (*oarchive) << BOOST_SERIALIZATION_NVP( distribution ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  Utility::TabularDistribution<InterpolationPolicy> dist_a;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_a ) );
  FRENSIE_CHECK_EQUAL( dist_a, Utility::TabularDistribution<InterpolationPolicy>( {1.0, 2.0, 3.0, 4.0}, {4.0, 3.0, 2.0, 1.0} ) );

  std::shared_ptr<Utility::UnivariateDistribution> shared_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> boost::serialization::make_nvp( "distribution", shared_dist ) );
  FRENSIE_CHECK_EQUAL( *dynamic_cast<Utility::TabularDistribution<InterpolationPolicy>*>( shared_dist.get() ),
                       *dynamic_cast<Utility::TabularDistribution<InterpolationPolicy>*>( distribution.get() ) );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitAwareTabularDistribution,
                                   archive,
                                   InterpPoliciesAndArchives )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  FETCH_TEMPLATE_PARAM( 1, RawOArchive );
  FETCH_TEMPLATE_PARAM( 2, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;
  
  std::string archive_base_name( "test_tabular_" );
  archive_base_name += InterpolationPolicy::name();
  archive_base_name += "_dist";

  std::ostringstream archive_ostream;

  // Create and archive some tabular distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );
    
    Utility::UnitAwareTabularDistribution<InterpolationPolicy,MegaElectronVolt,si::amount> dist_a( {1.0, 2.0, 3.0, 4.0}, {4.0, 3.0, 2.0, 1.0} );

    initialize<InterpolationPolicy>( unit_aware_distribution );

    FRENSIE_REQUIRE_NO_THROW(
                            (*oarchive) << BOOST_SERIALIZATION_NVP( dist_a ) );
    FRENSIE_REQUIRE_NO_THROW(
           (*oarchive) << BOOST_SERIALIZATION_NVP( unit_aware_distribution ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  Utility::UnitAwareTabularDistribution<InterpolationPolicy,MegaElectronVolt,si::amount> dist_a;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_a ) );
  FRENSIE_CHECK_EQUAL( dist_a, (Utility::UnitAwareTabularDistribution<InterpolationPolicy,MegaElectronVolt,si::amount>( {1.0, 2.0, 3.0, 4.0}, {4.0, 3.0, 2.0, 1.0} )) );

  std::shared_ptr<Utility::UnitAwareUnivariateDistribution<MegaElectronVolt,si::amount> > shared_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> boost::serialization::make_nvp( "unit_aware_distribution", shared_dist ) );
  FRENSIE_CHECK_EQUAL( (*dynamic_cast<Utility::UnitAwareTabularDistribution<InterpolationPolicy,MegaElectronVolt,si::amount>*>( shared_dist.get() )),
                       (*dynamic_cast<Utility::UnitAwareTabularDistribution<InterpolationPolicy,MegaElectronVolt,si::amount>*>( unit_aware_distribution.get() ) ));
}

//---------------------------------------------------------------------------//
// Check that distributions can be scaled
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitAwareTabularDistribution,
				   explicit_conversion,
				   TestUnitTypeQuads )
{
  FETCH_TEMPLATE_PARAM( 0, RawIndepUnitA );
  FETCH_TEMPLATE_PARAM( 1, RawDepUnitA );
  FETCH_TEMPLATE_PARAM( 2, RawIndepUnitB );
  FETCH_TEMPLATE_PARAM( 3, RawDepUnitB );

  typedef typename std::remove_pointer<RawIndepUnitA>::type IndepUnitA;
  typedef typename std::remove_pointer<RawDepUnitA>::type DepUnitA;
  typedef typename std::remove_pointer<RawIndepUnitB>::type IndepUnitB;
  typedef typename std::remove_pointer<RawDepUnitB>::type DepUnitB;
  
  typedef typename Utility::UnitTraits<IndepUnitA>::template GetQuantityType<double>::type IndepQuantityA;
  typedef typename Utility::UnitTraits<typename Utility::UnitTraits<IndepUnitA>::InverseUnit>::template GetQuantityType<double>::type InverseIndepQuantityA;

  typedef typename Utility::UnitTraits<IndepUnitB>::template GetQuantityType<double>::type IndepQuantityB;
  typedef typename Utility::UnitTraits<typename Utility::UnitTraits<IndepUnitB>::InverseUnit>::template GetQuantityType<double>::type InverseIndepQuantityB;

  typedef typename Utility::UnitTraits<DepUnitA>::template GetQuantityType<double>::type DepQuantityA;
  typedef typename Utility::UnitTraits<DepUnitB>::template GetQuantityType<double>::type DepQuantityB;

  initialize<Utility::LinLin>( distribution );

  // Copy from unitless distribution to distribution type A
  Utility::UnitAwareTabularDistribution<Utility::LinLin,IndepUnitA,DepUnitA>
    unit_aware_dist_a_copy = Utility::UnitAwareTabularDistribution<Utility::LinLin,IndepUnitA,DepUnitA>::fromUnitlessDistribution( *dynamic_cast<Utility::TabularDistribution<Utility::LinLin>*>( distribution.get() ) );

  // Copy from distribution type A to distribution type B
  Utility::UnitAwareTabularDistribution<Utility::LinLin,IndepUnitB,DepUnitB>
    unit_aware_dist_b_copy( unit_aware_dist_a_copy );

  IndepQuantityA indep_quantity_a =
    Utility::QuantityTraits<IndepQuantityA>::initializeQuantity( 0.0 );
  InverseIndepQuantityA inv_indep_quantity_a =
    Utility::QuantityTraits<InverseIndepQuantityA>::initializeQuantity( 0.0 );
  DepQuantityA dep_quantity_a =
    Utility::QuantityTraits<DepQuantityA>::initializeQuantity( 0.0 );

  IndepQuantityB indep_quantity_b( indep_quantity_a );
  InverseIndepQuantityB inv_indep_quantity_b( inv_indep_quantity_a );
  DepQuantityB dep_quantity_b( dep_quantity_a );

  FRENSIE_CHECK_FLOATING_EQUALITY(
			   unit_aware_dist_a_copy.evaluate( indep_quantity_a ),
			   dep_quantity_a,
			   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			unit_aware_dist_a_copy.evaluatePDF( indep_quantity_a ),
			inv_indep_quantity_a,
			1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			   unit_aware_dist_b_copy.evaluate( indep_quantity_b ),
			   dep_quantity_b,
			   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			unit_aware_dist_b_copy.evaluatePDF( indep_quantity_b ),
			inv_indep_quantity_b,
			1e-15 );

  Utility::setQuantity( indep_quantity_a, 0.1 );
  Utility::setQuantity( inv_indep_quantity_a, 0.67340006734 );
  Utility::setQuantity( dep_quantity_a, 1.0 );

  indep_quantity_b = IndepQuantityB( indep_quantity_a );
  inv_indep_quantity_b = InverseIndepQuantityB( inv_indep_quantity_a );
  dep_quantity_b = DepQuantityB( dep_quantity_a );

  FRENSIE_CHECK_FLOATING_EQUALITY(
			   unit_aware_dist_a_copy.evaluate( indep_quantity_a ),
			   dep_quantity_a,
			   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			unit_aware_dist_a_copy.evaluatePDF( indep_quantity_a ),
			inv_indep_quantity_a,
			1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			   unit_aware_dist_b_copy.evaluate( indep_quantity_b ),
			   dep_quantity_b,
			   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			unit_aware_dist_b_copy.evaluatePDF( indep_quantity_b ),
			inv_indep_quantity_b,
			1e-6 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstTabularDistribution.cpp
//---------------------------------------------------------------------------//
