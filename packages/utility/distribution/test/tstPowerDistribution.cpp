//---------------------------------------------------------------------------//
//!
//! \file   tstPowerDistribution.cpp
//! \author Alex Robinson
//! \brief  Power distribution unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/cgs.hpp>
#include <boost/units/io.hpp>

// FRENSIE Includes
#include "Utility_PowerDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTraits.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

using boost::units::quantity;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

typedef std::tuple<
  std::integral_constant<size_t,1>,
  std::integral_constant<size_t,2>,
  std::integral_constant<size_t,3>,
  std::integral_constant<size_t,4>,
  std::integral_constant<size_t,5>,
  std::integral_constant<size_t,6>,
  std::integral_constant<size_t,7>,
  std::integral_constant<size_t,8>,
  std::integral_constant<size_t,9>,
  std::integral_constant<size_t,10>
 > TestInts;

template<typename ArchivePair>
struct IntArchiveList
{
  typedef std::tuple<
    std::tuple<std::integral_constant<size_t,1>,typename Utility::TupleElement<0,ArchivePair>::type,typename Utility::TupleElement<1,ArchivePair>::type>,
    std::tuple<std::integral_constant<size_t,2>,typename Utility::TupleElement<0,ArchivePair>::type,typename Utility::TupleElement<1,ArchivePair>::type>,
    std::tuple<std::integral_constant<size_t,3>,typename Utility::TupleElement<0,ArchivePair>::type,typename Utility::TupleElement<1,ArchivePair>::type>,
    std::tuple<std::integral_constant<size_t,4>,typename Utility::TupleElement<0,ArchivePair>::type,typename Utility::TupleElement<1,ArchivePair>::type>,
    std::tuple<std::integral_constant<size_t,5>,typename Utility::TupleElement<0,ArchivePair>::type,typename Utility::TupleElement<1,ArchivePair>::type>,
    std::tuple<std::integral_constant<size_t,6>,typename Utility::TupleElement<0,ArchivePair>::type,typename Utility::TupleElement<1,ArchivePair>::type>,
    std::tuple<std::integral_constant<size_t,7>,typename Utility::TupleElement<0,ArchivePair>::type,typename Utility::TupleElement<1,ArchivePair>::type>,
    std::tuple<std::integral_constant<size_t,8>,typename Utility::TupleElement<0,ArchivePair>::type,typename Utility::TupleElement<1,ArchivePair>::type>,
    std::tuple<std::integral_constant<size_t,9>,typename Utility::TupleElement<0,ArchivePair>::type,typename Utility::TupleElement<1,ArchivePair>::type>,
    std::tuple<std::integral_constant<size_t,10>,typename Utility::TupleElement<0,ArchivePair>::type,typename Utility::TupleElement<1,ArchivePair>::type>
   > type;
};

template<typename... Types>
struct CreateIntArchiveList;

template<typename T, typename... Types>
struct CreateIntArchiveList<T,Types...>
{
  typedef decltype(std::tuple_cat(typename IntArchiveList<T>::type(), typename CreateIntArchiveList<Types...>::type())) type;
};

template<typename T>
struct CreateIntArchiveList<T>
{
  typedef typename IntArchiveList<T>::type type;
};

template<typename... Types>
struct CreateIntArchiveList<std::true_type,std::tuple<Types...> > : public CreateIntArchiveList<Types...>
{ /* ... */ };

template<typename... Types>
struct CreateIntArchiveList<std::false_type,std::tuple<Types...> > : public CreateIntArchiveList<std::tuple<Types...> >
{ /* ... */ };

typedef typename CreateIntArchiveList<std::true_type,TestArchiveHelper::TestArchives>::type TestIntsAndArchives;

typedef std::tuple<
  std::tuple<si::length,si::amount,cgs::length,si::amount>,
  std::tuple<cgs::length,si::amount,si::length,si::amount>,
  std::tuple<cgs::length,cgs::mass,si::length,si::mass>,
  std::tuple<si::length,si::mass,cgs::length,cgs::mass>,
  std::tuple<cgs::length,cgs::dimensionless,si::length,si::dimensionless>,
  std::tuple<si::length,si::dimensionless,cgs::length,cgs::dimensionless>,
  std::tuple<cgs::length,void*,si::length,void*>,
  std::tuple<si::length,void*,cgs::length,void*>,
  std::tuple<void*,cgs::dimensionless,void*,si::dimensionless>,
  std::tuple<void*,si::dimensionless,void*,cgs::dimensionless>,
  std::tuple<si::length,si::amount,cgs::length,si::amount>,
  std::tuple<cgs::length,si::amount,si::length,si::amount>,
  std::tuple<cgs::length,cgs::mass,si::length,si::mass>,
  std::tuple<si::length,si::mass,cgs::length,cgs::mass>,
  std::tuple<cgs::length,cgs::dimensionless,si::length,si::dimensionless>
 > TestUnitTypeQuads;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<Utility::UnivariateDistribution> distribution;

std::shared_ptr<Utility::UnitAwareUnivariateDistribution<cgs::length,si::amount> >
  unit_aware_distribution;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Initialize the distribution
template<unsigned N, typename IndepUnit, typename DepUnit>
void initializeDistribution(
       std::shared_ptr<Utility::UnitAwareUnivariateDistribution<IndepUnit,DepUnit> >&
       distribution )
{
  typedef typename Utility::UnitAwareUnivariateDistribution<IndepUnit,DepUnit>::IndepQuantity IndepQuantity;
  distribution.reset(
     new Utility::UnitAwarePowerDistribution<N,IndepUnit,DepUnit>(
	   (N+1.0),
	   Utility::QuantityTraits<IndepQuantity>::initializeQuantity( 0.0 ),
	   Utility::QuantityTraits<IndepQuantity>::initializeQuantity( 1.0 )));
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST_TEMPLATE( PowerDistribution, evaluate, TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  initializeDistribution<WrappedN::value,void,void>( distribution );

  FRENSIE_CHECK_EQUAL( distribution->evaluate( -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1.0 ), WrappedN::value + 1.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 2.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwarePowerDistribution, evaluate, TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  initializeDistribution<WrappedN::value,cgs::length,si::amount>( unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate(-1.0*cgs::centimeter),
		       0.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*cgs::centimeter),
		       0.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.0*cgs::centimeter),
		       (WrappedN::value + 1.0)*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 2.0*cgs::centimeter),
		       0.0*si::mole );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
FRENSIE_UNIT_TEST_TEMPLATE( PowerDistribution, evaluatePDF, TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  initializeDistribution<WrappedN::value,void,void>( distribution );

  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 1.0 ), WrappedN::value+1.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 2.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware PDF can be evaluated
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwarePowerDistribution, evaluatePDF, TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  initializeDistribution<WrappedN::value,cgs::length,si::amount>( unit_aware_distribution );

  FRENSIE_CHECK_EQUAL(
	          unit_aware_distribution->evaluatePDF( -1.0*cgs::centimeter ),
		  0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL(
		   unit_aware_distribution->evaluatePDF( 0.0*cgs::centimeter ),
		   0.0/cgs::centimeter );
  FRENSIE_CHECK_EQUAL(
		   unit_aware_distribution->evaluatePDF( 1.0*cgs::centimeter ),
		   (WrappedN::value+1.0)/cgs::centimeter );
  FRENSIE_CHECK_EQUAL(
		   unit_aware_distribution->evaluatePDF( 2.0*cgs::centimeter ),
		   0.0/cgs::centimeter );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( PowerDistribution, sample, TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  initializeDistribution<WrappedN::value,void,void>( distribution );

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, pow(0.5, 1.0/(WrappedN::value+1u)) );

  sample = distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0, 1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwarePowerDistribution, sample, TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  initializeDistribution<WrappedN::value,cgs::length,si::amount>( unit_aware_distribution );

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<cgs::length> sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, pow(0.5, 1.0/(WrappedN::value+1u))*cgs::centimeter );

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0*cgs::centimeter, 1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( PowerDistribution, sample_static, TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = Utility::PowerDistribution<WrappedN::value>::sample( 0.0, 1.0 );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = Utility::PowerDistribution<WrappedN::value>::sample( 0.0, 1.0 );
  FRENSIE_CHECK_EQUAL( sample, pow(0.5, 1.0/(WrappedN::value+1u)) );

  sample = Utility::PowerDistribution<WrappedN::value>::sample( 0.0, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0, 1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwarePowerDistribution,
                            sample_static,
                            TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<cgs::length> sample =
    Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length>::sample(
							 0.0*cgs::centimeter,
						         1.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample =
    Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length>::sample(
							 0.0*cgs::centimeter,
						         1.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( sample, pow(0.5, 1.0/(WrappedN::value+1u))*cgs::centimeter );

  sample =
    Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length>::sample(
							 0.0*cgs::centimeter,
						         1.0*cgs::centimeter );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0*cgs::centimeter, 1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( PowerDistribution,
                            sampleAndRecordTrials,
                            TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  initializeDistribution<WrappedN::value,void,void>( distribution );

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0;

  double sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, pow(0.5, 1.0/(WrappedN::value+1u)) );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0, 1e-15 );
  FRENSIE_CHECK_EQUAL( 3.0/trials, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwarePowerDistribution,
                            sampleAndRecordTrials,
                            TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  initializeDistribution<WrappedN::value,cgs::length,si::amount>( unit_aware_distribution );

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0;

  quantity<cgs::length> sample =
    unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, pow(0.5, 1.0/(WrappedN::value+1u))*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0*cgs::centimeter, 1e-15 );
  FRENSIE_CHECK_EQUAL( 3.0/trials, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
FRENSIE_UNIT_TEST_TEMPLATE( PowerDistribution,
                            getUpperBoundOfIndepVar,
                            TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  initializeDistribution<WrappedN::value,void,void>( distribution );

  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfIndepVar(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware distribution independent
// variable can be returned
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwarePowerDistribution,
                            getUpperBoundOfIndepVar,
                            TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  initializeDistribution<WrappedN::value,cgs::length,si::amount>( unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfIndepVar(),
		       1.0*cgs::centimeter );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
FRENSIE_UNIT_TEST_TEMPLATE( PowerDistribution,
                            getLowerBoundOfIndepVar,
                            TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  initializeDistribution<WrappedN::value,void,void>( distribution );

  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfIndepVar(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware distribution independent
// variable can be returned
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwarePowerDistribution,
                            getLowerBoundOfIndepVar,
                            TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  initializeDistribution<WrappedN::value,cgs::length,si::amount>( unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfIndepVar(),
		       0.0*cgs::centimeter );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
FRENSIE_UNIT_TEST_TEMPLATE( PowerDistribution,
                            getDistributionType,
                            TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  initializeDistribution<WrappedN::value,void,void>( distribution );

  FRENSIE_CHECK_EQUAL( distribution->getDistributionType(),
                       Utility::POWER_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type can be returned
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwarePowerDistribution,
                            getDistributionType,
                            TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  initializeDistribution<WrappedN::value,cgs::length,si::amount>( unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getDistributionType(),
                       Utility::POWER_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
FRENSIE_UNIT_TEST_TEMPLATE( PowerDistribution, isTabular, TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  initializeDistribution<WrappedN::value,void,void>( distribution );

  FRENSIE_CHECK( !distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is tabular
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwarePowerDistribution, isTabular, TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  initializeDistribution<WrappedN::value,cgs::length,si::amount>( unit_aware_distribution );

  FRENSIE_CHECK( !unit_aware_distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
FRENSIE_UNIT_TEST_TEMPLATE( PowerDistribution, isContinuous, TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  initializeDistribution<WrappedN::value,void,void>( distribution );

  FRENSIE_CHECK( distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is continuous
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwarePowerDistribution,
                            isContinuous,
                            TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  initializeDistribution<WrappedN::value,cgs::length,si::amount>( unit_aware_distribution );

  FRENSIE_CHECK( unit_aware_distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is compatible with an interpolation type
FRENSIE_UNIT_TEST_TEMPLATE( PowerDistribution,
                            isCompatibleWithInterpType,
                            TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  initializeDistribution<WrappedN::value,void,void>( distribution );

  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogLog>() );
  // Create another distribution that is compatible with all interpolation
  // types
  Utility::PowerDistribution<WrappedN::value> test_dist( 1.0, 1.0, 2.0 );

  FRENSIE_CHECK( test_dist.template isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( test_dist.template isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( test_dist.template isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( test_dist.template isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is compatible with the interp type
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwarePowerDistribution,
                            isCompatibleWithInterpType,
                            TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  
  initializeDistribution<WrappedN::value,cgs::length,si::amount>( unit_aware_distribution );

  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );

  // Create another distribution that is compatible with all interpolation
  // types
  Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>
    test_dist( 1.0, 1.0*si::meter, 2.0*si::meter );

  FRENSIE_CHECK( test_dist.template isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( test_dist.template isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( test_dist.template isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( test_dist.template isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be placed in a stream
FRENSIE_UNIT_TEST_TEMPLATE( PowerDistribution, ostream_operator, TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );

  std::ostringstream oss;
  
  oss << Utility::PowerDistribution<WrappedN::value>();

  Utility::VariantMap dist_data =
    Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Power Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["power"].toInt(), WrappedN::value, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toDouble(), 1.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toDouble(), 0.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toDouble(), 1.0, SHOW_LHS );
  
  oss.str( "" );
  oss.clear();

  oss << Utility::PowerDistribution<WrappedN::value>( 2.0 );
  
  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Power Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["power"].toInt(), WrappedN::value, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toDouble(), 2.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toDouble(), 0.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toDouble(), 1.0, SHOW_LHS );
  
  oss.str( "" );
  oss.clear();

  oss << Utility::PowerDistribution<WrappedN::value>( 2.0, 1.0, 2.0 );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Power Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["power"].toInt(), WrappedN::value, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toDouble(), 2.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toDouble(), 1.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toDouble(), 2.0, SHOW_LHS );
  
  oss.str( "" );
  oss.clear();

  initializeDistribution<WrappedN::value,void,void>( distribution );

  oss << *distribution;

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Power Distribution" );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["power"].toInt(), WrappedN::value, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toDouble(), WrappedN::value+1, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toDouble(), 0.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toDouble(), 1.0, SHOW_LHS );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be placed in a stream
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwarePowerDistribution,
                            ostream_operator,
                            TestInts )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );

  std::ostringstream oss;
  
  oss << Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>();

  Utility::VariantMap dist_data =
    Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Power Distribution",
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<cgs::length>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::amount>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["power"].toInt(), WrappedN::value, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toDouble(), 1.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toType<quantity<cgs::length> >(),
                       0.0*cgs::centimeter,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toType<quantity<cgs::length> >(),
                       1.0*cgs::centimeter,
                       SHOW_LHS );

  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>( 2.0 );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Power Distribution",
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<cgs::length>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::amount>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["power"].toInt(), WrappedN::value, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toDouble(), 2.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toType<quantity<cgs::length> >(),
                       0.0*cgs::centimeter,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toType<quantity<cgs::length> >(),
                       1.0*cgs::centimeter,
                       SHOW_LHS );

  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>( 2.0, 1.0*cgs::centimeter, 2.0*cgs::centimeter );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Power Distribution",
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<cgs::length>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::amount>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["power"].toInt(), WrappedN::value, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toDouble(), 2.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toType<quantity<cgs::length> >(),
                       1.0*cgs::centimeter,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toType<quantity<cgs::length> >(),
                       2.0*cgs::centimeter,
                       SHOW_LHS );

  oss.str( "" );
  oss.clear();

  initializeDistribution<WrappedN::value,cgs::length,si::amount>( unit_aware_distribution );

  oss << *unit_aware_distribution;

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Power Distribution",
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<cgs::length>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::amount>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["power"].toInt(), WrappedN::value, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toDouble(), WrappedN::value+1, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["lower bound"].toType<quantity<cgs::length> >(),
                       0.0*cgs::centimeter,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["upper bound"].toType<quantity<cgs::length> >(),
                       1.0*cgs::centimeter,
                       SHOW_LHS );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( PowerDistribution,
                                   archive,
                                   TestIntsAndArchives )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  FETCH_TEMPLATE_PARAM( 1, RawOArchive );
  FETCH_TEMPLATE_PARAM( 2, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;
  
  std::string archive_base_name( "test_power_dist_" );
  archive_base_name += Utility::toString( WrappedN::value );
  
  std::ostringstream archive_ostream;
  
  // Create and archive some power distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );
    
    Utility::PowerDistribution<WrappedN::value> dist_a;
    Utility::PowerDistribution<WrappedN::value> dist_b( 2.0 );
    Utility::PowerDistribution<WrappedN::value> dist_c( 3.0, 1.0, 2.0 );
    initializeDistribution<WrappedN::value,void,void>( distribution );

    FRENSIE_REQUIRE_NO_THROW(
                            (*oarchive) << BOOST_SERIALIZATION_NVP( dist_a ) );
    FRENSIE_REQUIRE_NO_THROW(
                            (*oarchive) << BOOST_SERIALIZATION_NVP( dist_b ) );
    FRENSIE_REQUIRE_NO_THROW(
                            (*oarchive) << BOOST_SERIALIZATION_NVP( dist_c ) );
    FRENSIE_REQUIRE_NO_THROW(
                      (*oarchive) << BOOST_SERIALIZATION_NVP( distribution ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  Utility::PowerDistribution<WrappedN::value> dist_a;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_a ) );
  FRENSIE_CHECK_EQUAL( dist_a, Utility::PowerDistribution<WrappedN::value>() );

  Utility::PowerDistribution<WrappedN::value> dist_b;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_b ) );
  FRENSIE_CHECK_EQUAL( dist_b, Utility::PowerDistribution<WrappedN::value>( 2.0 ) );

  Utility::PowerDistribution<WrappedN::value> dist_c;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_c ) );
  FRENSIE_CHECK_EQUAL( dist_c, Utility::PowerDistribution<WrappedN::value>( 3.0, 1.0, 2.0 ) );

  std::shared_ptr<Utility::UnivariateDistribution> shared_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> boost::serialization::make_nvp( "distribution", shared_dist ) );
  FRENSIE_CHECK_EQUAL( *dynamic_cast<Utility::PowerDistribution<WrappedN::value>*>( shared_dist.get() ),
                       *dynamic_cast<Utility::PowerDistribution<WrappedN::value>*>( distribution.get() ) );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitAwarePowerDistribution,
                                   archive,
                                   TestIntsAndArchives )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedN );
  FETCH_TEMPLATE_PARAM( 1, RawOArchive );
  FETCH_TEMPLATE_PARAM( 2, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;
  
  std::string archive_base_name( "test_unit_aware_power_dist_" );
  archive_base_name += Utility::toString( WrappedN::value );

  std::ostringstream archive_ostream;

  // Create and archive some power distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );
    
    Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount> dist_a;
    Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount> dist_b( 2.0 );
    Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount> dist_c( 3.0, 1.0*cgs::centimeter, 2.0*cgs::centimeter );
    initializeDistribution<WrappedN::value,cgs::length,si::amount>( unit_aware_distribution );

    FRENSIE_REQUIRE_NO_THROW(
                            (*oarchive) << BOOST_SERIALIZATION_NVP( dist_a ) );
    FRENSIE_REQUIRE_NO_THROW(
                            (*oarchive) << BOOST_SERIALIZATION_NVP( dist_b ) );
    FRENSIE_REQUIRE_NO_THROW(
                            (*oarchive) << BOOST_SERIALIZATION_NVP( dist_c ) );
    FRENSIE_REQUIRE_NO_THROW(
           (*oarchive) << BOOST_SERIALIZATION_NVP( unit_aware_distribution ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );
  
  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount> dist_a;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_a ) );
  FRENSIE_CHECK_EQUAL( dist_a, (Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>()) );

  Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount> dist_b;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_b ) );
  FRENSIE_CHECK_EQUAL( dist_b, (Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>( 2.0 )) );

  Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount> dist_c;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_c ) );
  FRENSIE_CHECK_EQUAL( dist_c, (Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>( 3.0, 1.0*cgs::centimeter, 2.0*cgs::centimeter )) );

  std::shared_ptr<Utility::UnitAwareUnivariateDistribution<cgs::length,si::amount> > shared_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> boost::serialization::make_nvp( "unit_aware_distribution", shared_dist ) );
  FRENSIE_CHECK_EQUAL( (*dynamic_cast<Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>*>( shared_dist.get() )),
                       (*dynamic_cast<Utility::UnitAwarePowerDistribution<WrappedN::value,cgs::length,si::amount>*>( unit_aware_distribution.get() )) );
}

//---------------------------------------------------------------------------//
// Check that distributions can be scaled
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitAwarePowerDistribution,
				   explicit_conversion_1,
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

  initializeDistribution<1,void,void>( distribution );

  // Copy from unitless distribution to distribution type A
  Utility::UnitAwarePowerDistribution<1,IndepUnitA,DepUnitA>
    unit_aware_dist_a_copy = Utility::UnitAwarePowerDistribution<1,IndepUnitA,DepUnitA>::fromUnitlessDistribution( *dynamic_cast<Utility::PowerDistribution<1>*>( distribution.get() ) );

  // Copy from distribution type A to distribution type B
  Utility::UnitAwarePowerDistribution<1,IndepUnitB,DepUnitB>
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

  Utility::setQuantity( indep_quantity_a, 1.0 );
  Utility::setQuantity( inv_indep_quantity_a, 2.0 );
  Utility::setQuantity( dep_quantity_a, 2.0 );

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
			1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			   unit_aware_dist_b_copy.evaluate( indep_quantity_b ),
			   dep_quantity_b,
			   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			unit_aware_dist_b_copy.evaluatePDF( indep_quantity_b ),
			inv_indep_quantity_b,
			1e-15 );
}

//---------------------------------------------------------------------------//
// Check that distributions can be scaled
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitAwarePowerDistribution,
				   explicit_conversion_2,
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

  initializeDistribution<2,void,void>( distribution );

  // Copy from unitless distribution to distribution type A
  Utility::UnitAwarePowerDistribution<2,IndepUnitA,DepUnitA>
    unit_aware_dist_a_copy = Utility::UnitAwarePowerDistribution<2,IndepUnitA,DepUnitA>::fromUnitlessDistribution( *dynamic_cast<Utility::PowerDistribution<2>*>( distribution.get() ) );

  // Copy from distribution type A to distribution type B
  Utility::UnitAwarePowerDistribution<2,IndepUnitB,DepUnitB>
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

  Utility::setQuantity( indep_quantity_a, 1.0 );
  Utility::setQuantity( inv_indep_quantity_a, 3.0 );
  Utility::setQuantity( dep_quantity_a, 3.0 );

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
			1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			   unit_aware_dist_b_copy.evaluate( indep_quantity_b ),
			   dep_quantity_b,
			   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			unit_aware_dist_b_copy.evaluatePDF( indep_quantity_b ),
			inv_indep_quantity_b,
			1e-15 );
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
// end tstPowerDistribution.cpp
//---------------------------------------------------------------------------//
