//---------------------------------------------------------------------------//
//!
//! \file   tstUnitBaseTwoDGridPolicy.cpp
//! \author Luke Kersting
//! \brief  The UnitBase two-dimensional sampling policy unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <memory>

// Boost Includes
#include <boost/units/systems/cgs.hpp>
#include <boost/units/io.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Utility_TwoDGridPolicy.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_DynamicOutputFormatter.hpp"
#include "Utility_InterpolatedFullyTabularTwoDDistribution.hpp"
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
// Testing Typenames
//---------------------------------------------------------------------------//

using DistributionType = Utility::FullyTabularTwoDDistribution::DistributionType;
using UnitAwareDistributionType = Utility::UnitAwareFullyTabularTwoDDistribution<MegaElectronVolt,cgs::length,Barn>::DistributionType;
using XIndepType = Utility::UnitTraits<MegaElectronVolt>::template GetQuantityType<double>::type;
using YIndepType = Utility::UnitTraits<cgs::length>::template GetQuantityType<double>::type;
using ZDepType = Utility::UnitTraits<Barn>::template GetQuantityType<double>::type;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<Utility::FullyTabularTwoDDistribution::DistributionType> distribution;
std::shared_ptr<Utility::UnitAwareFullyTabularTwoDDistribution<MegaElectronVolt,cgs::length,Barn>::DistributionType> unit_aware_distribution;

std::function<double(const Utility::TabularOneDDistribution&)> functor;
std::function<YIndepType(const Utility::UnitAwareTabularOneDDistribution<cgs::length,Barn>&)> ua_functor;

std::function<double (double)> min_func, max_func;
std::function<YIndepType(const XIndepType)> ua_min_func, ua_max_func;

Utility::FullyTabularTwoDDistribution::DistributionType::const_iterator
  lower_bin, upper_bin, sampled_bin, start_bin;

Utility::UnitAwareFullyTabularTwoDDistribution<MegaElectronVolt,cgs::length,Barn>::DistributionType::const_iterator
  ua_lower_bin, ua_upper_bin, ua_sampled_bin, ua_start_bin;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution is tabular in the primary dimension
TEUCHOS_UNIT_TEST( UnitBase, name )
{
  std::string name = Utility::UnitBase<Utility::LinLinLin>::name();

  TEST_ASSERT( name == "LinLinLin Unit-Base" );
}

//---------------------------------------------------------------------------//
// Check that the Y lower bound can be calculated
TEUCHOS_UNIT_TEST( UnitBase, calculateLowerBound )
{
  lower_bin = distribution->begin();
  upper_bin = lower_bin;
  ++upper_bin;

  // On the first bin boundary
  double x_value = 0.0;
  double bound = Utility::UnitBase<Utility::LinLinLin>::calculateLowerBound<double>(
                    x_value, lower_bin, upper_bin );
  TEST_EQUALITY_CONST( bound, 0.0 );

  // In the first bin
  x_value = 0.5;
  bound = Utility::UnitBase<Utility::LinLinLin>::calculateLowerBound<double>(
                    x_value, lower_bin, upper_bin );
  TEST_EQUALITY_CONST( bound, 1.25 );

  // On the second bin boundary
  ++lower_bin; ++upper_bin;
  x_value = 1.0;
  bound = Utility::UnitBase<Utility::LinLinLin>::calculateLowerBound<double>(
                    x_value, lower_bin, upper_bin );
  TEST_EQUALITY_CONST( bound, 2.5 );

  // In the second bin
  x_value = 1.5;
  bound = Utility::UnitBase<Utility::LinLinLin>::calculateLowerBound<double>(
                    x_value, lower_bin, upper_bin );
  TEST_EQUALITY_CONST( bound, 1.25 );

  // On the upper bin boundary
  x_value = 2.0;
  bound = Utility::UnitBase<Utility::LinLinLin>::calculateLowerBound<double>(
                    x_value, lower_bin, upper_bin );
  TEST_EQUALITY_CONST( bound, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the Y lower bound can be calculated
TEUCHOS_UNIT_TEST( UnitBase, calculateUpperBound )
{
  lower_bin = distribution->begin();
  upper_bin = lower_bin;
  ++upper_bin;

  // On the first bin boundary
  double x_value = 0.0;
  double bound = Utility::UnitBase<Utility::LinLinLin>::calculateUpperBound<double>(
                    x_value, lower_bin, upper_bin );
  TEST_EQUALITY_CONST( bound, 10.0 );

  // In the first bin
  x_value = 0.5;
  bound = Utility::UnitBase<Utility::LinLinLin>::calculateUpperBound<double>(
                    x_value, lower_bin, upper_bin );
  TEST_EQUALITY_CONST( bound, 8.75 );

  // On the second bin boundary
  ++lower_bin; ++upper_bin;
  x_value = 1.0;
  bound = Utility::UnitBase<Utility::LinLinLin>::calculateUpperBound<double>(
                    x_value, lower_bin, upper_bin );
  TEST_EQUALITY_CONST( bound, 7.5 );

  // In the second bin
  x_value = 1.5;
  bound = Utility::UnitBase<Utility::LinLinLin>::calculateUpperBound<double>(
                    x_value, lower_bin, upper_bin );
  TEST_EQUALITY_CONST( bound, 8.75 );

  // On the upper bin boundary
  x_value = 2.0;
  bound = Utility::UnitBase<Utility::LinLinLin>::calculateUpperBound<double>(
                    x_value, lower_bin, upper_bin );
  TEST_EQUALITY_CONST( bound, 10.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( UnitBase, evaluatePDF )
{
  std::function<double(double,double)> evaluate =
  [&min_func, &max_func, &lower_bin, &upper_bin](double x_value, double y_value)
  {
    return Utility::UnitBase<Utility::LinLinLin>::evaluatePDF<Utility::TabularOneDDistribution,double,double,double>(
      x_value, y_value, min_func, max_func, &Utility::TabularOneDDistribution::evaluate, lower_bin, upper_bin );
  };

  lower_bin = distribution->begin();
  upper_bin = lower_bin;
  ++upper_bin;

  double x_value = 0.0;
  min_func = [](double x){return 0.0;}; max_func = [](double x){return 10.0;};;

  // On the first bin boundary
  TEST_EQUALITY_CONST( evaluate( 0.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( evaluate( 0.0, 0.0 ), 1.0 );
  TEST_EQUALITY_CONST( evaluate( 0.0, 5.0 ), 1.0 );
  TEST_EQUALITY_CONST( evaluate( 0.0, 10.0 ), 1.0 );
  TEST_EQUALITY_CONST( evaluate( 0.0, 11.0 ), 0.0 );

  // In the first bin
  min_func = [](double x){return 1.25;}; max_func = [](double x){return 8.75;};

  TEST_EQUALITY_CONST( evaluate( 0.5, 1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( evaluate( 0.5, 1.25 ), 0.7, 1e-15 );
  TEST_FLOATING_EQUALITY( evaluate( 0.5, 5.0 ), 1.0, 1e-6 );
  TEST_FLOATING_EQUALITY( evaluate( 0.5, 8.75 ), 5.0/6.0, 1e-15 );
  TEST_EQUALITY_CONST( evaluate( 0.5, 9.0 ), 0.0 );

  // On the second bin boundary
  ++lower_bin; ++upper_bin;
  min_func = [](double x){return 2.5;}; max_func = [](double x){return 7.5;};

  TEST_EQUALITY_CONST( evaluate( 1.0, 2.0 ), 0.0 );
  TEST_EQUALITY_CONST( evaluate( 1.0, 2.5 ), 0.1 );
  TEST_EQUALITY_CONST( evaluate( 1.0, 5.0 ), 1.0 );
  TEST_EQUALITY_CONST( evaluate( 1.0, 7.5 ), 0.5 );
  TEST_EQUALITY_CONST( evaluate( 1.0, 8.0 ), 0.0 );

  // In the second bin
  min_func = [](double x){return 1.25;}; max_func = [](double x){return 8.75;};

  TEST_EQUALITY_CONST( evaluate( 1.5, 1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( evaluate( 1.5, 1.25 ), 0.1, 1e-15 );
  TEST_FLOATING_EQUALITY( evaluate( 1.5, 5.0 ), 0.4, 1e-6 );
  TEST_FLOATING_EQUALITY( evaluate( 1.5, 8.75 ), 7.0/30.0, 1e-15 );
  TEST_EQUALITY_CONST( evaluate( 1.5, 9.0 ), 0.0 );

  // On the upper bin boundary
  min_func = [](double x){return 0.0;}; max_func = [](double x){return 10.0;};

  TEST_EQUALITY_CONST( evaluate( 2.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( evaluate( 2.0, 0.0 ), 0.1 );
  TEST_EQUALITY_CONST( evaluate( 2.0, 5.0 ), 0.1 );
  TEST_EQUALITY_CONST( evaluate( 2.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( evaluate( 2.0, 11.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareUnitBase, evaluatePDF )
{
  std::function<ZDepType(XIndepType,YIndepType)> evaluate =
  [&ua_min_func, &ua_max_func, &ua_lower_bin, &ua_upper_bin](XIndepType x_value, YIndepType y_value)
  {
    return Utility::UnitBase<Utility::LinLinLin>::evaluatePDF<Utility::UnitAwareTabularOneDDistribution<cgs::length,Barn>,XIndepType,YIndepType,ZDepType>(
      x_value, y_value, ua_min_func, ua_max_func, &Utility::UnitAwareTabularOneDDistribution<cgs::length,Barn>::evaluate, ua_lower_bin, ua_upper_bin );
  };

  ua_lower_bin = unit_aware_distribution->begin();
  ua_upper_bin = ua_lower_bin;
  ++ua_upper_bin;

  ua_min_func = [](XIndepType x){return 0.0*cgs::centimeter;};
  ua_max_func = [](XIndepType x){return 10.0*cgs::centimeter;};

  // On the first bin boundary
  TEST_EQUALITY_CONST( evaluate( 0.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( evaluate( 0.0*MeV, 0.0*cgs::centimeter ), 1.0*barn );
  TEST_EQUALITY_CONST( evaluate( 0.0*MeV, 5.0*cgs::centimeter ), 1.0*barn );
  TEST_EQUALITY_CONST( evaluate( 0.0*MeV, 10.0*cgs::centimeter ), 1.0*barn );
  TEST_EQUALITY_CONST( evaluate( 0.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  // In the first bin
  ua_min_func = [](XIndepType x){return 1.25*cgs::centimeter;};
  ua_max_func = [](XIndepType x){return 8.75*cgs::centimeter;};

  TEST_EQUALITY_CONST( evaluate( 0.5*MeV, 1.0*cgs::centimeter ), 0.0*barn );
  UTILITY_TEST_FLOATING_EQUALITY( evaluate( 0.5*MeV, 1.25*cgs::centimeter ),
                                  0.7*barn,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( evaluate( 0.5*MeV, 5.0*cgs::centimeter ),
                                  1.0*barn,
                                  1e-6 );
  UTILITY_TEST_FLOATING_EQUALITY( evaluate( 0.5*MeV, 8.75*cgs::centimeter ),
                                  5.0/6.0*barn,
                                  1e-15 );
  TEST_EQUALITY_CONST( evaluate( 0.5*MeV, 9.0*cgs::centimeter ), 0.0*barn );

  // On the second bin boundary
  ++ua_lower_bin; ++ua_upper_bin;
  ua_min_func = [](XIndepType x){return 2.5*cgs::centimeter;};
  ua_max_func = [](XIndepType x){return 7.5*cgs::centimeter;};

  TEST_EQUALITY_CONST( evaluate( 1.0*MeV, 2.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( evaluate( 1.0*MeV, 2.5*cgs::centimeter ), 0.1*barn );
  TEST_EQUALITY_CONST( evaluate( 1.0*MeV, 5.0*cgs::centimeter ), 1.0*barn );
  TEST_EQUALITY_CONST( evaluate( 1.0*MeV, 7.5*cgs::centimeter ), 0.5*barn );
  TEST_EQUALITY_CONST( evaluate( 1.0*MeV, 8.0*cgs::centimeter ), 0.0*barn );

  // In the second bin
  ua_min_func = [](XIndepType x){return 1.25*cgs::centimeter;};
  ua_max_func = [](XIndepType x){return 8.75*cgs::centimeter;};

  TEST_EQUALITY_CONST( evaluate( 1.5*MeV, 1.0*cgs::centimeter ), 0.0*barn );
  UTILITY_TEST_FLOATING_EQUALITY( evaluate( 1.5*MeV, 1.25*cgs::centimeter ),
                                  0.1*barn,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( evaluate( 1.5*MeV, 5.0*cgs::centimeter ),
                                  0.4*barn,
                                  1e-6 );
  UTILITY_TEST_FLOATING_EQUALITY( evaluate( 1.5*MeV, 8.75*cgs::centimeter ),
                                  7.0/30.0*barn,
                                  1e-15 );
  TEST_EQUALITY_CONST( evaluate( 1.5*MeV, 9.0*cgs::centimeter ), 0.0*barn );

  // On the upper bin boundary
  ua_min_func = [](XIndepType x){return 0.0*cgs::centimeter;};
  ua_max_func = [](XIndepType x){return 10.0*cgs::centimeter;};

  TEST_EQUALITY_CONST( evaluate( 2.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( evaluate( 2.0*MeV, 0.0*cgs::centimeter ), 0.1*barn );
  TEST_EQUALITY_CONST( evaluate( 2.0*MeV, 5.0*cgs::centimeter ), 0.1*barn );
  TEST_EQUALITY_CONST( evaluate( 2.0*MeV, 10.0*cgs::centimeter ), 0.1*barn );
  TEST_EQUALITY_CONST( evaluate( 2.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( UnitBase, evaluateCDF )
{
  std::function<double(double,double)> evaluate =
  [&min_func, &max_func, &lower_bin, &upper_bin](double x_value, double y_value)
  {
    return Utility::UnitBase<Utility::LinLinLin>::evaluateCDF<Utility::TabularOneDDistribution,double,double>(
      x_value, y_value, min_func, max_func, &Utility::TabularOneDDistribution::evaluateCDF, lower_bin, upper_bin );
  };

  lower_bin = distribution->begin();
  upper_bin = lower_bin;
  ++upper_bin;

  double x_value = 0.0;
  min_func = [](double x){return 0.0;}; max_func = [](double x){return 10.0;};;

  // On the first bin boundary
  TEST_EQUALITY_CONST( evaluate( 0.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( evaluate( 0.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( evaluate( 0.0, 5.0 ), 0.5 );
  TEST_EQUALITY_CONST( evaluate( 0.0, 10.0 ), 1.0 );
  TEST_EQUALITY_CONST( evaluate( 0.0, 11.0 ), 1.0 );

  // In the first bin
  min_func = [](double x){return 1.25;}; max_func = [](double x){return 8.75;};

  TEST_EQUALITY_CONST( evaluate( 0.5, 1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( evaluate( 0.5, 1.25 ), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( evaluate( 0.5, 5.0 ), 4.6153846153846156e-01, 1e-6 );
  TEST_FLOATING_EQUALITY( evaluate( 0.5, 8.75 ), 1.0, 1e-15 );
  TEST_EQUALITY_CONST( evaluate( 0.5, 9.0 ), 1.0 );

  // On the second bin boundary
  ++lower_bin; ++upper_bin;
  min_func = [](double x){return 2.5;}; max_func = [](double x){return 7.5;};

  TEST_EQUALITY_CONST( evaluate( 1.0, 2.0 ), 0.0 );
  TEST_EQUALITY_CONST( evaluate( 1.0, 2.5 ), 0.0 );
  TEST_EQUALITY_CONST( evaluate( 1.0, 5.0 ), 4.23076923076923128e-01 );
  TEST_EQUALITY_CONST( evaluate( 1.0, 7.5 ), 1.0 );
  TEST_EQUALITY_CONST( evaluate( 1.0, 8.0 ), 1.0 );

  // In the second bin
  min_func = [](double x){return 1.25;}; max_func = [](double x){return 8.75;};

  TEST_EQUALITY_CONST( evaluate( 1.5, 1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( evaluate( 1.5, 1.25 ), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( evaluate( 1.5, 5.0 ), 4.6153846153846156e-01, 1e-6 );
  TEST_FLOATING_EQUALITY( evaluate( 1.5, 8.75 ), 1.0, 1e-15 );
  TEST_EQUALITY_CONST( evaluate( 1.5, 9.0 ), 1.0 );

  // On the upper bin boundary
  min_func = [](double x){return 0.0;}; max_func = [](double x){return 10.0;};

  TEST_EQUALITY_CONST( evaluate( 2.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( evaluate( 2.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( evaluate( 2.0, 5.0 ), 0.5 );
  TEST_EQUALITY_CONST( evaluate( 2.0, 10.0 ), 1.0 );
  TEST_EQUALITY_CONST( evaluate( 2.0, 11.0 ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareUnitBase, evaluateCDF )
{
  std::function<double(XIndepType,YIndepType)> evaluate =
  [&ua_min_func, &ua_max_func, &ua_lower_bin, &ua_upper_bin](XIndepType x_value, YIndepType y_value)
  {
    return Utility::UnitBase<Utility::LinLinLin>::evaluateCDF<Utility::UnitAwareTabularOneDDistribution<cgs::length,Barn>,XIndepType,YIndepType>(
      x_value, y_value, ua_min_func, ua_max_func, &Utility::UnitAwareTabularOneDDistribution<cgs::length,Barn>::evaluateCDF, ua_lower_bin, ua_upper_bin );
  };

  ua_lower_bin = unit_aware_distribution->begin();
  ua_upper_bin = ua_lower_bin;
  ++ua_upper_bin;

  ua_min_func = [](XIndepType x){return 0.0*cgs::centimeter;};
  ua_max_func = [](XIndepType x){return 10.0*cgs::centimeter;};

  // On the first bin boundary
  TEST_EQUALITY_CONST( evaluate( 0.0*MeV, -1.0*cgs::centimeter ), 0.0);
  TEST_EQUALITY_CONST( evaluate( 0.0*MeV, 0.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( evaluate( 0.0*MeV, 5.0*cgs::centimeter ), 0.5 );
  TEST_EQUALITY_CONST( evaluate( 0.0*MeV, 10.0*cgs::centimeter ), 1.0 );
  TEST_EQUALITY_CONST( evaluate( 0.0*MeV, 11.0*cgs::centimeter ), 1.0 );

  // In the first bin
  ua_min_func = [](XIndepType x){return 1.25*cgs::centimeter;};
  ua_max_func = [](XIndepType x){return 8.75*cgs::centimeter;};

  TEST_EQUALITY_CONST( evaluate( 0.5*MeV, 1.0*cgs::centimeter ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( evaluate( 0.5*MeV, 1.25*cgs::centimeter ),
                                  0.0,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( evaluate( 0.5*MeV, 5.0*cgs::centimeter ),
                                  4.6153846153846156e-01,
                                  1e-6 );
  UTILITY_TEST_FLOATING_EQUALITY( evaluate( 0.5*MeV, 8.75*cgs::centimeter ),
                                  1.0,
                                  1e-15 );
  TEST_EQUALITY_CONST( evaluate( 0.5*MeV, 9.0*cgs::centimeter ), 1.0 );

  // On the second bin boundary
  ++ua_lower_bin; ++ua_upper_bin;
  ua_min_func = [](XIndepType x){return 2.5*cgs::centimeter;};
  ua_max_func = [](XIndepType x){return 7.5*cgs::centimeter;};

  TEST_EQUALITY_CONST( evaluate( 1.0*MeV, 2.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( evaluate( 1.0*MeV, 2.5*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( evaluate( 1.0*MeV, 5.0*cgs::centimeter ), 4.23076923076923128e-01 );
  TEST_EQUALITY_CONST( evaluate( 1.0*MeV, 7.5*cgs::centimeter ), 1.0 );
  TEST_EQUALITY_CONST( evaluate( 1.0*MeV, 8.0*cgs::centimeter ), 1.0 );

  // In the second bin
  ua_min_func = [](XIndepType x){return 1.25*cgs::centimeter;};
  ua_max_func = [](XIndepType x){return 8.75*cgs::centimeter;};

  TEST_EQUALITY_CONST( evaluate( 1.5*MeV, 1.0*cgs::centimeter ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( evaluate( 1.5*MeV, 1.25*cgs::centimeter ),
                                  0.0,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( evaluate( 1.5*MeV, 5.0*cgs::centimeter ),
                                  4.6153846153846156e-01,
                                  1e-6 );
  UTILITY_TEST_FLOATING_EQUALITY( evaluate( 1.5*MeV, 8.75*cgs::centimeter ),
                                  1.0,
                                  1e-15 );
  TEST_EQUALITY_CONST( evaluate( 1.5*MeV, 9.0*cgs::centimeter ), 1.0 );

  // On the upper bin boundary
  ua_min_func = [](XIndepType x){return 0.0*cgs::centimeter;};
  ua_max_func = [](XIndepType x){return 10.0*cgs::centimeter;};

  TEST_EQUALITY_CONST( evaluate( 2.0*MeV, -1.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( evaluate( 2.0*MeV, 0.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( evaluate( 2.0*MeV, 5.0*cgs::centimeter ), 0.5 );
  TEST_EQUALITY_CONST( evaluate( 2.0*MeV, 10.0*cgs::centimeter ), 1.0 );
  TEST_EQUALITY_CONST( evaluate( 2.0*MeV, 11.0*cgs::centimeter ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitBase, sample )
{
  // On the first bin
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  lower_bin = distribution->begin();
  upper_bin = lower_bin;
  ++upper_bin;

  double x_value = 0.0;
  min_func = [](double x){return 0.0;}; max_func = [](double x){return 10.0;};

  double sample = Utility::UnitBase<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = Utility::UnitBase<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = Utility::UnitBase<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-14 );

  // In the first bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5; // use lower bin boundary
  fake_stream[5] = 1.0-1e-15;
  fake_stream[6] = 0.49; // use upper bin boundary
  fake_stream[7] = 0.0;
  fake_stream[8] = 0.49; // use upper bin boundary
  fake_stream[9] = 4.23076923076923128e-01;
  fake_stream[10] = 0.49; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  x_value = 0.5;
  min_func = [](double x){return 1.25;}; max_func = [](double x){return 8.75;};

  // Samples from lower boundary of first bin
  sample = Utility::UnitBase<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  TEST_EQUALITY_CONST( sample, 1.25 );

  sample = Utility::UnitBase<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = Utility::UnitBase<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-14 );

  // Samples from the upper boundary of the first bin
  sample = Utility::UnitBase<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  TEST_EQUALITY_CONST( sample, 1.25 );

  sample = Utility::UnitBase<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  TEST_FLOATING_EQUALITY( sample, 5.0, 1e-15 );

  sample = Utility::UnitBase<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-14 );

  // On the second bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 4.23076923076923128e-01;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  x_value = 1.0;
  min_func = [](double x){return 2.5;}; max_func = [](double x){return 7.5;};

  sample = Utility::UnitBase<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  TEST_EQUALITY_CONST( sample, 2.5 );

  sample = Utility::UnitBase<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  TEST_FLOATING_EQUALITY( sample, 5.0, 1e-15 );

  sample = Utility::UnitBase<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-15 );

  // In the second bin
  ++lower_bin; ++upper_bin;
  fake_stream.resize( 12 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 4.23076923076923128e-01;
  fake_stream[4] = 0.5; // use lower bin boundary
  fake_stream[5] = 1.0-1e-15;
  fake_stream[6] = 0.49; // use upper bin boundary
  fake_stream[7] = 0.0;
  fake_stream[8] = 0.49; // use upper bin boundary
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.49; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  x_value = 1.5;
  min_func = [](double x){return 1.25;}; max_func = [](double x){return 8.75;};

  // Samples from lower boundary of second bin
  sample = Utility::UnitBase<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  TEST_EQUALITY_CONST( sample, 1.25 );

  sample = Utility::UnitBase<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  TEST_FLOATING_EQUALITY( sample, 5.0, 1e-15 );

  sample = Utility::UnitBase<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-14 );

  // Samples from upper boundary of second bin
  sample = Utility::UnitBase<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  TEST_EQUALITY_CONST( sample, 1.25 );

  sample = Utility::UnitBase<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = Utility::UnitBase<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-14 );

  // On the upper bin boundary
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  x_value = 2.0;
  min_func = [](double x){return 0.0;}; max_func = [](double x){return 10.0;};

  sample = Utility::UnitBase<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = Utility::UnitBase<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = Utility::UnitBase<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareUnitBase, sample )
{
  // On the first bin
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  ua_lower_bin = unit_aware_distribution->begin();
  ua_upper_bin = ua_lower_bin;
  ++ua_upper_bin;
  quantity<MegaElectronVolt> x_value = 0.0*MeV;
  ua_min_func = [](quantity<MegaElectronVolt> x){return 0.0*cgs::centimeter;};
  ua_max_func = [](quantity<MegaElectronVolt> x){return 10.0*cgs::centimeter;};

  quantity<cgs::length> sample =
    Utility::UnitBase<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
      ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = Utility::UnitBase<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  sample = Utility::UnitBase<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );

  // In the first bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5; // use lower bin boundary
  fake_stream[5] = 1.0-1e-15;
  fake_stream[6] = 0.49; // use upper bin boundary
  fake_stream[7] = 0.0;
  fake_stream[8] = 0.49; // use upper bin boundary
  fake_stream[9] = 4.23076923076923128e-01;
  fake_stream[10] = 0.49; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  x_value = 0.5*MeV;
  ua_min_func = [](quantity<MegaElectronVolt> x){return 1.25*cgs::centimeter;};
  ua_max_func = [](quantity<MegaElectronVolt> x){return 8.75*cgs::centimeter;};

  // Samples from lower boundary of first bin
  sample = Utility::UnitBase<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  sample = Utility::UnitBase<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  sample = Utility::UnitBase<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-14 );

  // Samples from the upper boundary of the first bin
  sample = Utility::UnitBase<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  sample = Utility::UnitBase<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );

  sample = Utility::UnitBase<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-14 );

  // On the second bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 4.23076923076923128e-01;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  x_value = 1.0*MeV;
  ua_min_func = [](quantity<MegaElectronVolt> x){return 2.5*cgs::centimeter;};
  ua_max_func = [](quantity<MegaElectronVolt> x){return 7.5*cgs::centimeter;};

  sample = Utility::UnitBase<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  TEST_EQUALITY_CONST( sample, 2.5*cgs::centimeter );

  sample = Utility::UnitBase<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );

  sample = Utility::UnitBase<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-15 );

  // In the second bin
  ++ua_lower_bin; ++ua_upper_bin;
  fake_stream.resize( 12 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 4.23076923076923128e-01;
  fake_stream[4] = 0.5; // use lower bin boundary
  fake_stream[5] = 1.0-1e-15;
  fake_stream[6] = 0.49; // use upper bin boundary
  fake_stream[7] = 0.0;
  fake_stream[8] = 0.49; // use upper bin boundary
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.49; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  x_value = 1.5*MeV;
  ua_min_func = [](quantity<MegaElectronVolt> x){return 1.25*cgs::centimeter;};
  ua_max_func = [](quantity<MegaElectronVolt> x){return 8.75*cgs::centimeter;};

  // Samples from lower boundary of second bin
  sample = Utility::UnitBase<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  sample = Utility::UnitBase<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );

  sample = Utility::UnitBase<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-14 );

  // Samples from upper boundary of second bin
  sample = Utility::UnitBase<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  sample = Utility::UnitBase<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  sample = Utility::UnitBase<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-14 );

  // On the upper bin boundary
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;\
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  x_value = 2.0*MeV;
  ua_min_func = [](quantity<MegaElectronVolt> x){return 0.0*cgs::centimeter;};
  ua_max_func = [](quantity<MegaElectronVolt> x){return 10.0*cgs::centimeter;};

  sample = Utility::UnitBase<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  sample = Utility::UnitBase<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  sample = Utility::UnitBase<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitBase, sampleDetailed )
{
  // On the first bin
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double raw_sample;
  unsigned bin_index;

  start_bin = distribution->begin();
  lower_bin = start_bin;
  upper_bin = lower_bin;
  ++upper_bin;
  min_func = [](double x){return 0.0;}; max_func = [](double x){return 10.0;};

  double sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<double,double>(
      functor, min_func, max_func, 0.0, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 0u );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( raw_sample, 0.0 );

  sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<double,double>(
    functor, min_func, max_func, 0.0, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 0u );
  TEST_EQUALITY_CONST( sample, 5.0 );
  TEST_EQUALITY_CONST( raw_sample, 5.0 );

  sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<double,double>(
    functor, min_func, max_func, 0.0, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 0u );
  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-14 );
  TEST_FLOATING_EQUALITY( raw_sample, 10.0, 1e-14 );

  // In the first bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5; // use lower bin boundary
  fake_stream[5] = 1.0-1e-15;
  fake_stream[6] = 0.49; // use upper bin boundary
  fake_stream[7] = 0.0;
  fake_stream[8] = 0.49; // use upper bin boundary
  fake_stream[9] = 4.23076923076923128e-01;
  fake_stream[10] = 0.49; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  min_func = [](double x){return 1.25;}; max_func = [](double x){return 8.75;};

  // Samples from lower boundary of first bin
  sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<double,double>(
    functor, min_func, max_func, 0.5, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 0u );
  TEST_EQUALITY_CONST( sample, 1.25 );
  TEST_EQUALITY_CONST( raw_sample, 0.0 );

  sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<double,double>(
    functor, min_func, max_func, 0.5, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 0u );
  TEST_EQUALITY_CONST( sample, 5.0 );
  TEST_EQUALITY_CONST( raw_sample, 5.0 );

  sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<double,double>(
    functor, min_func, max_func, 0.5, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 0u );
  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-14 );
  TEST_FLOATING_EQUALITY( raw_sample, 10.0, 1e-14 );

  // Samples from the upper boundary of the first bin
  sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<double,double>(
    functor, min_func, max_func, 0.5, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  TEST_EQUALITY_CONST( sample, 1.25 );
  TEST_EQUALITY_CONST( raw_sample, 2.5 );

  sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<double,double>(
    functor, min_func, max_func, 0.5, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  TEST_FLOATING_EQUALITY( sample, 5.0, 1e-15 );
  TEST_FLOATING_EQUALITY( raw_sample, 5.0, 1e-15 );

  sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<double,double>(
    functor, min_func, max_func, 0.5, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-14 );
  TEST_FLOATING_EQUALITY( raw_sample, 7.5, 1e-14 );

  // On the second bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 4.23076923076923128e-01;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  min_func = [](double x){return 2.5;}; max_func = [](double x){return 7.5;};

  sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<double,double>(
    functor, min_func, max_func, 1.0, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  TEST_EQUALITY_CONST( sample, 2.5 );
  TEST_EQUALITY_CONST( raw_sample, 2.5 );

  sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<double,double>(
    functor, min_func, max_func, 1.0, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  TEST_FLOATING_EQUALITY( sample, 5.0, 1e-15 );
  TEST_FLOATING_EQUALITY( raw_sample, 5.0, 1e-15 );

  sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<double,double>(
    functor, min_func, max_func, 1.0, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-15 );
  TEST_FLOATING_EQUALITY( raw_sample, 7.5, 1e-15 );

  // In the second bin
  ++lower_bin; ++upper_bin;
  fake_stream.resize( 12 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 4.23076923076923128e-01;
  fake_stream[4] = 0.5; // use lower bin boundary
  fake_stream[5] = 1.0-1e-15;
  fake_stream[6] = 0.49; // use upper bin boundary
  fake_stream[7] = 0.0;
  fake_stream[8] = 0.49; // use upper bin boundary
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.49; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  min_func = [](double x){return 1.25;}; max_func = [](double x){return 8.75;};

  // Samples from lower boundary of second bin
  sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<double,double>(
    functor, min_func, max_func, 1.5, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  TEST_EQUALITY_CONST( sample, 1.25 );
  TEST_EQUALITY_CONST( raw_sample, 2.5 );

  sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<double,double>(
    functor, min_func, max_func, 1.5, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  TEST_FLOATING_EQUALITY( sample, 5.0, 1e-15 );
  TEST_FLOATING_EQUALITY( raw_sample, 5.0, 1e-15 );

  sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<double,double>(
    functor, min_func, max_func, 1.5, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-14 );
  TEST_FLOATING_EQUALITY( raw_sample, 7.5, 1e-14 );

  // Samples from upper boundary of second bin
  sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<double,double>(
    functor, min_func, max_func, 1.5, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 2u );
  TEST_EQUALITY_CONST( sample, 1.25 );
  TEST_EQUALITY_CONST( raw_sample, 0.0 );

  sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<double,double>(
    functor, min_func, max_func, 1.5, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 2u );
  TEST_EQUALITY_CONST( sample, 5.0 );
  TEST_EQUALITY_CONST( raw_sample, 5.0 );

  sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<double,double>(
    functor, min_func, max_func, 1.5, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 2u );
  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-14 );
  TEST_FLOATING_EQUALITY( raw_sample, 10.0, 1e-14 );

  // On the upper bin boundary
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  min_func = [](double x){return 0.0;}; max_func = [](double x){return 10.0;};

  sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<double,double>(
    functor, min_func, max_func, 2.0, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 2u );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( raw_sample, 0.0 );

  sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<double,double>(
    functor, min_func, max_func, 2.0, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 2u );
  TEST_EQUALITY_CONST( sample, 5.0 );
  TEST_EQUALITY_CONST( raw_sample, 5.0 );

  sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<double,double>(
    functor, min_func, max_func, 2.0, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 2u );
  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-14 );
  TEST_FLOATING_EQUALITY( raw_sample, 10.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareUnitBase, sampleDetailed )
{
  // On the first bin
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned bin_index;
  quantity<cgs::length> raw_sample;
  ua_start_bin = unit_aware_distribution->begin();
  ua_lower_bin = ua_start_bin;
  ua_upper_bin = ua_lower_bin;
  ++ua_upper_bin;
  ua_min_func = [](quantity<MegaElectronVolt> x){return 0.0*cgs::centimeter;};
  ua_max_func = [](quantity<MegaElectronVolt> x){return 10.0*cgs::centimeter;};

  quantity<cgs::length> sample =
    Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
      ua_functor, ua_min_func, ua_max_func, 0.0*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 0u );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 0.0*cgs::centimeter );

  sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, 0.0*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 0u );
  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 5.0*cgs::centimeter );

  sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, 0.0*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 0u );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 10.0*cgs::centimeter, 1e-14 );

  // In the first bin
  fake_stream.resize( 12 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5; // use lower bin boundary
  fake_stream[5] = 1.0-1e-15;
  fake_stream[6] = 0.49; // use upper bin boundary
  fake_stream[7] = 0.0;
  fake_stream[8] = 0.49; // use upper bin boundary
  fake_stream[9] = 4.23076923076923128e-01;
  fake_stream[10] = 0.49; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  ua_min_func = [](quantity<MegaElectronVolt> x){return 1.25*cgs::centimeter;};
  ua_max_func = [](quantity<MegaElectronVolt> x){return 8.75*cgs::centimeter;};

  // Samples from lower boundary of first bin
  sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, 0.5*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 0u );
  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 0.0*cgs::centimeter );

  sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, 0.5*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 0u );
  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 5.0*cgs::centimeter );

  sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, 0.5*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 0u );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 10.0*cgs::centimeter, 1e-14 );

  // Samples from the upper boundary of the first bin
  sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, 0.5*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 2.5*cgs::centimeter );

  sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, 0.5*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 5.0*cgs::centimeter, 1e-15 );

  sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, 0.5*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 7.5*cgs::centimeter, 1e-14 );

  // On the second bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 4.23076923076923128e-01;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  ua_min_func = [](quantity<MegaElectronVolt> x){return 2.5*cgs::centimeter;};
  ua_max_func = [](quantity<MegaElectronVolt> x){return 7.5*cgs::centimeter;};

  sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, 1.0*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  TEST_EQUALITY_CONST( sample, 2.5*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 2.5*cgs::centimeter );

  sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, 1.0*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 5.0*cgs::centimeter, 1e-15 );

  sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, 1.0*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 7.5*cgs::centimeter, 1e-15 );

  // In the second bin
  ++ua_lower_bin; ++ua_upper_bin;
  fake_stream.resize( 12 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 4.23076923076923128e-01;
  fake_stream[4] = 0.5; // use lower bin boundary
  fake_stream[5] = 1.0-1e-15;
  fake_stream[6] = 0.49; // use upper bin boundary
  fake_stream[7] = 0.0;
  fake_stream[8] = 0.49; // use upper bin boundary
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.49; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  ua_min_func = [](quantity<MegaElectronVolt> x){return 1.25*cgs::centimeter;};
  ua_max_func = [](quantity<MegaElectronVolt> x){return 8.75*cgs::centimeter;};

  // Samples from lower boundary of second bin
  sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, 1.5*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 2.5*cgs::centimeter );

  sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, 1.5*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 5.0*cgs::centimeter, 1e-15 );

  sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, 1.5*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 7.5*cgs::centimeter, 1e-14 );

  // Samples from upper boundary of second bin
  sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, 1.5*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 2u );
  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 0.0*cgs::centimeter );

  sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, 1.5*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 2u );
  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 5.0*cgs::centimeter );

  sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, 1.5*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 2u );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 10.0*cgs::centimeter, 1e-14 );

  // On the upper bin boundary
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  ua_min_func = [](quantity<MegaElectronVolt> x){return 0.0*cgs::centimeter;};
  ua_max_func = [](quantity<MegaElectronVolt> x){return 10.0*cgs::centimeter;};

  sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, 2.0*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 2u );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 0.0*cgs::centimeter );

  sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, 2.0*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 2u );
  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 5.0*cgs::centimeter );

  sample = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, 2.0*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 2u );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 10.0*cgs::centimeter, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Create the two-dimensional distribution
  {
    Utility::FullyTabularTwoDDistribution::DistributionType
      distribution_data( 3 );

    // Create the secondary distribution in the first bin
    distribution_data[0].first = 0.0;
    distribution_data[0].second.reset( new Utility::UniformDistribution( 0.0, 10.0, 1.0 ) );

    // Create the secondary distribution in the second bin
    std::vector<double> bin_boundaries( 3 ), values( 3 );
    bin_boundaries[0] = 2.5; values[0] = 0.1;
    bin_boundaries[1] = 5.0; values[1] = 1.0;
    bin_boundaries[2] = 7.5; values[2] = 0.5;

    distribution_data[1].first = 1.0;
    distribution_data[1].second.reset( new Utility::TabularDistribution<Utility::LinLin>( bin_boundaries, values ) );

    // Create the secondary distribution beyond the second bin
    distribution_data[2].first = 2.0;
    distribution_data[2].second.reset( new Utility::UniformDistribution( 0.0, 10.0, 0.1 ) );

    distribution.reset( new Utility::FullyTabularTwoDDistribution::DistributionType(
                                                        distribution_data ) );

    // Create the sampling functor
    functor = std::bind<double>( &Utility::TabularOneDDistribution::sample,
                                 std::placeholders::_1 );
  }

  // Create the unit-aware two-dimensional distribution
  {
    Utility::UnitAwareFullyTabularTwoDDistribution<MegaElectronVolt,cgs::length,Barn>::DistributionType
    distribution_data( 3 );

    // Create the secondary distribution in the first bin
    distribution_data[0].first = 0.0*MeV;
    distribution_data[0].second.reset( new Utility::UnitAwareUniformDistribution<cgs::length,Barn>( 0.0*cgs::centimeter, 10.0*cgs::centimeter, 1.0*barn ) );

    // Create the secondary distribution in the second bin
    Teuchos::Array<quantity<cgs::length> > bin_boundaries( 3 );
    Teuchos::Array<quantity<Barn> > values( 3 );
    bin_boundaries[0] = 2.5*cgs::centimeter; values[0] = 0.1*barn;
    bin_boundaries[1] = 5.0*cgs::centimeter; values[1] = 1.0*barn;
    bin_boundaries[2] = 7.5*cgs::centimeter; values[2] = 0.5*barn;

    distribution_data[1].first = 1.0*MeV;
    distribution_data[1].second.reset( new Utility::UnitAwareTabularDistribution<Utility::LinLin,cgs::length,Barn>( bin_boundaries, values ) );

    // Create the secondary distribution beyond the second bin
    distribution_data[2].first = 2.0*MeV;
    distribution_data[2].second.reset( new Utility::UnitAwareUniformDistribution<cgs::length,Barn>( 0.0*cgs::centimeter, 10.0*cgs::centimeter, 0.1*barn ) );

    unit_aware_distribution.reset(
        new Utility::UnitAwareFullyTabularTwoDDistribution<MegaElectronVolt,cgs::length,Barn>::DistributionType(
                                                        distribution_data ) );

    // Create the sampling functor
    ua_functor = std::bind<YIndepType>(
      &Utility::UnitAwareTabularOneDDistribution<cgs::length,Barn>::sample,
      std::placeholders::_1 );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstUnitBaseTwoDGridPolicy.cpp
//---------------------------------------------------------------------------//
