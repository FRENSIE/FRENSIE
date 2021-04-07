//---------------------------------------------------------------------------//
//!
//! \file   tstDirectTwoDGridPolicy.cpp
//! \author Luke Kersting
//! \brief  The Direct two-dimensional sampling policy unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <memory>

// Boost Includes
#include <boost/units/systems/cgs.hpp>
#include <boost/units/io.hpp>

// FRENSIE Includes
#include "Utility_TwoDGridPolicy.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "Utility_DynamicOutputFormatter.hpp"
#include "Utility_InterpolatedFullyTabularBasicBivariateDistribution.hpp"
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

using DistributionType = std::vector<std::pair<double,std::shared_ptr<const Utility::TabularUnivariateDistribution > > >;

using XIndepType = Utility::UnitTraits<MegaElectronVolt>::template GetQuantityType<double>::type;
using YIndepType = Utility::UnitTraits<cgs::length>::template GetQuantityType<double>::type;
using ZDepType = Utility::UnitTraits<Barn>::template GetQuantityType<double>::type;

using UnitAwareDistributionType = std::vector<std::pair<Utility::UnitTraits<MegaElectronVolt>::template GetQuantityType<double>::type,std::shared_ptr<const Utility::UnitAwareTabularUnivariateDistribution<cgs::length,Barn> > > >;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<DistributionType> distribution;
std::shared_ptr<UnitAwareDistributionType> unit_aware_distribution;

std::function<double(const Utility::TabularUnivariateDistribution&)> functor;
std::function<YIndepType(const Utility::UnitAwareTabularUnivariateDistribution<cgs::length,Barn>&)> ua_functor;

std::function<double (double)> min_func, max_func;
std::function<YIndepType(const XIndepType)> ua_min_func, ua_max_func;

DistributionType::const_iterator
  lower_bin, upper_bin, sampled_bin, start_bin;

UnitAwareDistributionType::const_iterator
  ua_lower_bin, ua_upper_bin, ua_sampled_bin, ua_start_bin;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution is tabular in the primary dimension
FRENSIE_UNIT_TEST( Direct,
                   name )
{
  std::string name = Utility::Direct<Utility::LinLinLin>::name();
  FRENSIE_CHECK( name == "Direct" );

  name = Utility::Direct<Utility::LinLinLin>::TwoDInterpPolicy::name();
  FRENSIE_CHECK( name == "LinLinLin" );
}

//---------------------------------------------------------------------------//
// Check that the Y lower bound can be calculated
FRENSIE_UNIT_TEST( Direct, calculateLowerBound )
{
  lower_bin = distribution->begin();
  upper_bin = lower_bin;
  ++upper_bin;

  // On the first bin boundary
  double x_value = 0.0;
  double bound = Utility::Direct<Utility::LinLinLin>::calculateLowerBound<double>(
                    x_value, lower_bin, upper_bin );
  FRENSIE_CHECK_EQUAL( bound, 0.0 );

  // In the first bin
  x_value = 0.5;
  bound = Utility::Direct<Utility::LinLinLin>::calculateLowerBound<double>(
                    x_value, lower_bin, upper_bin );
  FRENSIE_CHECK_EQUAL( bound, 0.0 );

  // On the second bin boundary
  ++lower_bin; ++upper_bin;
  x_value = 1.0;
  bound = Utility::Direct<Utility::LinLinLin>::calculateLowerBound<double>(
                    x_value, lower_bin, upper_bin );
  FRENSIE_CHECK_EQUAL( bound, 2.5 );

  // In the second bin
  x_value = 1.5;
  bound = Utility::Direct<Utility::LinLinLin>::calculateLowerBound<double>(
                    x_value, lower_bin, upper_bin );
  FRENSIE_CHECK_EQUAL( bound, 0.0 );

  // On the upper bin boundary
  x_value = 2.0;
  bound = Utility::Direct<Utility::LinLinLin>::calculateLowerBound<double>(
                    x_value, lower_bin, upper_bin );
  FRENSIE_CHECK_EQUAL( bound, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the Y lower bound can be calculated
FRENSIE_UNIT_TEST( Direct, calculateUpperBound )
{
  lower_bin = distribution->begin();
  upper_bin = lower_bin;
  ++upper_bin;

  // On the first bin boundary
  double x_value = 0.0;
  double bound = Utility::Direct<Utility::LinLinLin>::calculateUpperBound<double>(
                    x_value, lower_bin, upper_bin );
  FRENSIE_CHECK_EQUAL( bound, 10.0 );

  // In the first bin
  x_value = 0.5;
  bound = Utility::Direct<Utility::LinLinLin>::calculateUpperBound<double>(
                    x_value, lower_bin, upper_bin );
  FRENSIE_CHECK_EQUAL( bound, 10.0 );

  // On the second bin boundary
  ++lower_bin; ++upper_bin;
  x_value = 1.0;
  bound = Utility::Direct<Utility::LinLinLin>::calculateUpperBound<double>(
                    x_value, lower_bin, upper_bin );
  FRENSIE_CHECK_EQUAL( bound, 7.5 );

  // In the second bin
  x_value = 1.5;
  bound = Utility::Direct<Utility::LinLinLin>::calculateUpperBound<double>(
                    x_value, lower_bin, upper_bin );
  FRENSIE_CHECK_EQUAL( bound, 10.0 );

  // On the upper bin boundary
  x_value = 2.0;
  bound = Utility::Direct<Utility::LinLinLin>::calculateUpperBound<double>(
                    x_value, lower_bin, upper_bin );
  FRENSIE_CHECK_EQUAL( bound, 10.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( Direct, evaluatePDF )
{
  std::function<double(double,double)> evaluate =
  [&min_func, &max_func, &lower_bin, &upper_bin](double x_value, double y_value)
  {
    return Utility::Direct<Utility::LinLinLin>::evaluatePDF<Utility::TabularUnivariateDistribution,double,double,double>(
      x_value, y_value, min_func, max_func, &Utility::TabularUnivariateDistribution::evaluate, lower_bin, upper_bin );
  };

  lower_bin = distribution->begin();
  upper_bin = lower_bin;
  ++upper_bin;

  double x_value = 0.0;
  min_func = [](double x){return 0.0;}; max_func = [](double x){return 10.0;};

  // On the first bin boundary
  FRENSIE_CHECK_EQUAL( evaluate( 0.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( evaluate( 0.0, 0.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( evaluate( 0.0, 5.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( evaluate( 0.0, 10.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( evaluate( 0.0, 11.0 ), 0.0 );

  // In the first bin
  min_func = [](double x){return 1.25;}; max_func = [](double x){return 8.75;};

  FRENSIE_CHECK_EQUAL( evaluate( 0.5, 1.0 ), 0.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( evaluate( 0.5, 1.25 ), 0.5, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( evaluate( 0.5, 5.0 ), 1.0, 1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( evaluate( 0.5, 8.75 ), 0.5, 1e-15 );
  FRENSIE_CHECK_EQUAL( evaluate( 0.5, 9.0 ), 0.5 );

  // On the second bin boundary
  ++lower_bin; ++upper_bin;
  min_func = [](double x){return 2.5;}; max_func = [](double x){return 7.5;};

  FRENSIE_CHECK_EQUAL( evaluate( 1.0, 2.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( evaluate( 1.0, 2.5 ), 0.1 );
  FRENSIE_CHECK_EQUAL( evaluate( 1.0, 5.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( evaluate( 1.0, 7.5 ), 0.5 );
  FRENSIE_CHECK_EQUAL( evaluate( 1.0, 8.0 ), 0.0 );

  // In the second bin
  min_func = [](double x){return 1.25;}; max_func = [](double x){return 8.75;};

  FRENSIE_CHECK_EQUAL( evaluate( 1.5, 1.0 ), 0.05 );
  FRENSIE_CHECK_FLOATING_EQUALITY( evaluate( 1.5, 1.25 ), 0.05, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( evaluate( 1.5, 5.0 ), 0.55, 1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( evaluate( 1.5, 8.75 ), 0.05, 1e-15 );
  FRENSIE_CHECK_EQUAL( evaluate( 1.5, 9.0 ), 0.05 );

  // On the upper bin boundary
  min_func = [](double x){return 0.0;}; max_func = [](double x){return 10.0;};

  FRENSIE_CHECK_EQUAL( evaluate( 2.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( evaluate( 2.0, 0.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( evaluate( 2.0, 5.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( evaluate( 2.0, 10.0 ), 0.1 );
  FRENSIE_CHECK_EQUAL( evaluate( 2.0, 11.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
FRENSIE_UNIT_TEST( UnitAwareDirect, evaluatePDF )
{
  std::function<ZDepType(XIndepType,YIndepType)> evaluate =
  [&ua_min_func, &ua_max_func, &ua_lower_bin, &ua_upper_bin](XIndepType x_value, YIndepType y_value)
  {
    return Utility::Direct<Utility::LinLinLin>::evaluatePDF<Utility::UnitAwareTabularUnivariateDistribution<cgs::length,Barn>,XIndepType,YIndepType,ZDepType>(
      x_value, y_value, ua_min_func, ua_max_func, &Utility::UnitAwareTabularUnivariateDistribution<cgs::length,Barn>::evaluate, ua_lower_bin, ua_upper_bin );
  };

  ua_lower_bin = unit_aware_distribution->begin();
  ua_upper_bin = ua_lower_bin;
  ++ua_upper_bin;

  ua_min_func = [](XIndepType x){return 0.0*cgs::centimeter;};
  ua_max_func = [](XIndepType x){return 10.0*cgs::centimeter;};

  // On the first bin boundary
  FRENSIE_CHECK_EQUAL( evaluate( 0.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( evaluate( 0.0*MeV, 0.0*cgs::centimeter ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( evaluate( 0.0*MeV, 5.0*cgs::centimeter ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( evaluate( 0.0*MeV, 10.0*cgs::centimeter ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( evaluate( 0.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  // In the first bin
  ua_min_func = [](XIndepType x){return 1.25*cgs::centimeter;};
  ua_max_func = [](XIndepType x){return 8.75*cgs::centimeter;};

  FRENSIE_CHECK_EQUAL( evaluate( 0.5*MeV, 1.0*cgs::centimeter ), 0.5*barn );
  FRENSIE_CHECK_FLOATING_EQUALITY( evaluate( 0.5*MeV, 1.25*cgs::centimeter ),
                                  0.5*barn,
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( evaluate( 0.5*MeV, 5.0*cgs::centimeter ),
                                  1.0*barn,
                                  1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( evaluate( 0.5*MeV, 8.75*cgs::centimeter ),
                                  0.5*barn,
                                  1e-15 );
  FRENSIE_CHECK_EQUAL( evaluate( 0.5*MeV, 9.0*cgs::centimeter ), 0.5*barn );

  // On the second bin boundary
  ++ua_lower_bin; ++ua_upper_bin;
  ua_min_func = [](XIndepType x){return 2.5*cgs::centimeter;};
  ua_max_func = [](XIndepType x){return 7.5*cgs::centimeter;};

  FRENSIE_CHECK_EQUAL( evaluate( 1.0*MeV, 2.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( evaluate( 1.0*MeV, 2.5*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( evaluate( 1.0*MeV, 5.0*cgs::centimeter ), 1.0*barn );
  FRENSIE_CHECK_EQUAL( evaluate( 1.0*MeV, 7.5*cgs::centimeter ), 0.5*barn );
  FRENSIE_CHECK_EQUAL( evaluate( 1.0*MeV, 8.0*cgs::centimeter ), 0.0*barn );

  // In the second bin
  ua_min_func = [](XIndepType x){return 1.25*cgs::centimeter;};
  ua_max_func = [](XIndepType x){return 8.75*cgs::centimeter;};

  FRENSIE_CHECK_EQUAL( evaluate( 1.5*MeV, 1.0*cgs::centimeter ), 0.05*barn );
  FRENSIE_CHECK_FLOATING_EQUALITY( evaluate( 1.5*MeV, 1.25*cgs::centimeter ),
                                  0.05*barn,
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( evaluate( 1.5*MeV, 5.0*cgs::centimeter ),
                                  0.55*barn,
                                  1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( evaluate( 1.5*MeV, 8.75*cgs::centimeter ),
                                  0.05*barn,
                                  1e-15 );
  FRENSIE_CHECK_EQUAL( evaluate( 1.5*MeV, 9.0*cgs::centimeter ), 0.05*barn );

  // On the upper bin boundary
  ua_min_func = [](XIndepType x){return 0.0*cgs::centimeter;};
  ua_max_func = [](XIndepType x){return 10.0*cgs::centimeter;};

  FRENSIE_CHECK_EQUAL( evaluate( 2.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  FRENSIE_CHECK_EQUAL( evaluate( 2.0*MeV, 0.0*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( evaluate( 2.0*MeV, 5.0*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( evaluate( 2.0*MeV, 10.0*cgs::centimeter ), 0.1*barn );
  FRENSIE_CHECK_EQUAL( evaluate( 2.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( Direct, evaluateCDF )
{
  std::function<double(double,double)> evaluate =
  [&min_func, &max_func, &lower_bin, &upper_bin](double x_value, double y_value)
  {
    return Utility::Direct<Utility::LinLinLin>::evaluateCDF<Utility::TabularUnivariateDistribution,double,double>(
      x_value, y_value, min_func, max_func, &Utility::TabularUnivariateDistribution::evaluateCDF, lower_bin, upper_bin );
  };

  lower_bin = distribution->begin();
  upper_bin = lower_bin;
  ++upper_bin;

  double x_value = 0.0;
  min_func = [](double x){return 0.0;}; max_func = [](double x){return 10.0;};

  // On the first bin boundary
  FRENSIE_CHECK_EQUAL( evaluate( 0.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( evaluate( 0.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( evaluate( 0.0, 5.0 ), 0.5 );
  FRENSIE_CHECK_EQUAL( evaluate( 0.0, 10.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( evaluate( 0.0, 11.0 ), 1.0 );

  // In the first bin
  min_func = [](double x){return 1.25;}; max_func = [](double x){return 8.75;};

  FRENSIE_CHECK_EQUAL( evaluate( 0.5, 1.0 ), 0.05 );
  FRENSIE_CHECK_FLOATING_EQUALITY( evaluate( 0.5, 1.25 ), 1.0/16.0, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( evaluate( 0.5, 5.0 ), 4.6153846153846156e-01, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( evaluate( 0.5, 8.75 ), 15.0/16.0, 1e-15 );
  FRENSIE_CHECK_EQUAL( evaluate( 0.5, 9.0 ), 19.0/20.0 );

  // On the second bin boundary
  ++lower_bin; ++upper_bin;
  min_func = [](double x){return 2.5;}; max_func = [](double x){return 7.5;};

  FRENSIE_CHECK_EQUAL( evaluate( 1.0, 2.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( evaluate( 1.0, 2.5 ), 0.0 );
  FRENSIE_CHECK_EQUAL( evaluate( 1.0, 5.0 ), 4.23076923076923128e-01 );
  FRENSIE_CHECK_EQUAL( evaluate( 1.0, 7.5 ), 1.0 );
  FRENSIE_CHECK_EQUAL( evaluate( 1.0, 8.0 ), 1.0 );

  // In the second bin
  min_func = [](double x){return 1.25;}; max_func = [](double x){return 8.75;};

  FRENSIE_CHECK_EQUAL( evaluate( 1.5, 1.0 ), 0.05 );
  FRENSIE_CHECK_FLOATING_EQUALITY( evaluate( 1.5, 1.25 ), 1.0/16.0, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( evaluate( 1.5, 5.0 ), 4.6153846153846156e-01, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( evaluate( 1.5, 8.75 ), 15.0/16.0, 1e-15 );
  FRENSIE_CHECK_EQUAL( evaluate( 1.5, 9.0 ), 19.0/20.0 );

  // On the upper bin boundary
  min_func = [](double x){return 0.0;}; max_func = [](double x){return 10.0;};

  FRENSIE_CHECK_EQUAL( evaluate( 2.0, -1.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( evaluate( 2.0, 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( evaluate( 2.0, 5.0 ), 0.5 );
  FRENSIE_CHECK_EQUAL( evaluate( 2.0, 10.0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( evaluate( 2.0, 11.0 ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
FRENSIE_UNIT_TEST( UnitAwareDirect, evaluateCDF )
{
  std::function<double(XIndepType,YIndepType)> evaluate =
  [&ua_min_func, &ua_max_func, &ua_lower_bin, &ua_upper_bin](XIndepType x_value, YIndepType y_value)
  {
    return Utility::Direct<Utility::LinLinLin>::evaluateCDF<Utility::UnitAwareTabularUnivariateDistribution<cgs::length,Barn>,XIndepType,YIndepType>(
      x_value, y_value, ua_min_func, ua_max_func, &Utility::UnitAwareTabularUnivariateDistribution<cgs::length,Barn>::evaluateCDF, ua_lower_bin, ua_upper_bin );
  };

  ua_lower_bin = unit_aware_distribution->begin();
  ua_upper_bin = ua_lower_bin;
  ++ua_upper_bin;

  ua_min_func = [](XIndepType x){return 0.0*cgs::centimeter;};
  ua_max_func = [](XIndepType x){return 10.0*cgs::centimeter;};

  // On the first bin boundary
  FRENSIE_CHECK_EQUAL( evaluate( 0.0*MeV, -1.0*cgs::centimeter ), 0.0 );
  FRENSIE_CHECK_EQUAL( evaluate( 0.0*MeV, 0.0*cgs::centimeter ), 0.0 );
  FRENSIE_CHECK_EQUAL( evaluate( 0.0*MeV, 5.0*cgs::centimeter ), 0.5 );
  FRENSIE_CHECK_EQUAL( evaluate( 0.0*MeV, 10.0*cgs::centimeter ), 1.0 );
  FRENSIE_CHECK_EQUAL( evaluate( 0.0*MeV, 11.0*cgs::centimeter ), 1.0 );

  // In the first bin
  ua_min_func = [](XIndepType x){return 1.25*cgs::centimeter;};
  ua_max_func = [](XIndepType x){return 8.75*cgs::centimeter;};

  FRENSIE_CHECK_EQUAL( evaluate( 0.5*MeV, 1.0*cgs::centimeter ), 0.05 );
  FRENSIE_CHECK_FLOATING_EQUALITY( evaluate( 0.5*MeV, 1.25*cgs::centimeter ),
                                  1.0/16.0,
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( evaluate( 0.5*MeV, 5.0*cgs::centimeter ),
                                  4.6153846153846156e-01,
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( evaluate( 0.5*MeV, 8.75*cgs::centimeter ),
                                  15.0/16.0,
                                  1e-15 );
  FRENSIE_CHECK_EQUAL( evaluate( 0.5*MeV, 9.0*cgs::centimeter ), 19.0/20.0 );

  // On the second bin boundary
  ++ua_lower_bin; ++ua_upper_bin;
  ua_min_func = [](XIndepType x){return 2.5*cgs::centimeter;};
  ua_max_func = [](XIndepType x){return 7.5*cgs::centimeter;};

  FRENSIE_CHECK_EQUAL( evaluate( 1.0*MeV, 2.0*cgs::centimeter ), 0.0 );
  FRENSIE_CHECK_EQUAL( evaluate( 1.0*MeV, 2.5*cgs::centimeter ), 0.0 );
  FRENSIE_CHECK_EQUAL( evaluate( 1.0*MeV, 5.0*cgs::centimeter ), 4.23076923076923128e-01 );
  FRENSIE_CHECK_EQUAL( evaluate( 1.0*MeV, 7.5*cgs::centimeter ), 1.0 );
  FRENSIE_CHECK_EQUAL( evaluate( 1.0*MeV, 8.0*cgs::centimeter ), 1.0 );

  // In the second bin
  ua_min_func = [](XIndepType x){return 1.25*cgs::centimeter;};
  ua_max_func = [](XIndepType x){return 8.75*cgs::centimeter;};

  FRENSIE_CHECK_EQUAL( evaluate( 1.5*MeV, 1.0*cgs::centimeter ), 0.05 );
  FRENSIE_CHECK_FLOATING_EQUALITY( evaluate( 1.5*MeV, 1.25*cgs::centimeter ),
                                  1.0/16.0,
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( evaluate( 1.5*MeV, 5.0*cgs::centimeter ),
                                  4.6153846153846156e-01,
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( evaluate( 1.5*MeV, 8.75*cgs::centimeter ),
                                  15.0/16.0,
                                  1e-15 );
  FRENSIE_CHECK_EQUAL( evaluate( 1.5*MeV, 9.0*cgs::centimeter ), 19.0/20.0 );

  // On the upper bin boundary
  ua_min_func = [](XIndepType x){return 0.0*cgs::centimeter;};
  ua_max_func = [](XIndepType x){return 10.0*cgs::centimeter;};

  FRENSIE_CHECK_EQUAL( evaluate( 2.0*MeV, -1.0*cgs::centimeter ), 0.0 );
  FRENSIE_CHECK_EQUAL( evaluate( 2.0*MeV, 0.0*cgs::centimeter ), 0.0 );
  FRENSIE_CHECK_EQUAL( evaluate( 2.0*MeV, 5.0*cgs::centimeter ), 0.5 );
  FRENSIE_CHECK_EQUAL( evaluate( 2.0*MeV, 10.0*cgs::centimeter ), 1.0 );
  FRENSIE_CHECK_EQUAL( evaluate( 2.0*MeV, 11.0*cgs::centimeter ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( Direct, sample )
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

  double sample = Utility::Direct<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = Utility::Direct<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );

  sample = Utility::Direct<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-14 );

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
  fake_stream[9] = 0.4230769230769231;
  fake_stream[10] = 0.49; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  x_value = 0.5;
  min_func = [](double x){return 1.25;}; max_func = [](double x){return 8.75;};

  // Samples from lower boundary of first bin
  sample = Utility::Direct<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = Utility::Direct<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );

  sample = Utility::Direct<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-14 );

  // Samples from the upper boundary of the first bin
  sample = Utility::Direct<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  FRENSIE_CHECK_EQUAL( sample, 2.5 );

  sample = Utility::Direct<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0, 1e-15 );

  sample = Utility::Direct<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  // On the second bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.4230769230769231;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  x_value = 1.0;
  min_func = [](double x){return 2.5;}; max_func = [](double x){return 7.5;};

  sample = Utility::Direct<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  FRENSIE_CHECK_EQUAL( sample, 2.5 );

  sample = Utility::Direct<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0, 1e-15 );

  sample = Utility::Direct<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-15 );

  // In the second bin
  ++lower_bin; ++upper_bin;
  fake_stream.resize( 12 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 0.4230769230769231;
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
  sample = Utility::Direct<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  FRENSIE_CHECK_EQUAL( sample, 2.5 );

  sample = Utility::Direct<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0, 1e-15 );

  sample = Utility::Direct<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-14 );

  // Samples from upper boundary of second bin
  sample = Utility::Direct<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = Utility::Direct<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );

  sample = Utility::Direct<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-14 );

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

  sample = Utility::Direct<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  FRENSIE_CHECK_EQUAL( sample, 0.0 );

  sample = Utility::Direct<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  FRENSIE_CHECK_EQUAL( sample, 5.0 );

  sample = Utility::Direct<Utility::LinLinLin>::sample<double,double>(
                  functor, min_func, max_func, x_value, lower_bin, upper_bin );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( UnitAwareDirect, sample )
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
    Utility::Direct<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
      ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = Utility::Direct<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );

  sample = Utility::Direct<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );

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
  fake_stream[9] = 0.4230769230769231;
  fake_stream[10] = 0.49; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  x_value = 0.5*MeV;
  ua_min_func = [](quantity<MegaElectronVolt> x){return 1.25*cgs::centimeter;};
  ua_max_func = [](quantity<MegaElectronVolt> x){return 8.75*cgs::centimeter;};

  // Samples from lower boundary of first bin
  sample = Utility::Direct<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = Utility::Direct<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );

  sample = Utility::Direct<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );

  // Samples from the upper boundary of the first bin
  sample = Utility::Direct<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );

  sample = Utility::Direct<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );

  sample = Utility::Direct<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  // On the second bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.4230769230769231;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  x_value = 1.0*MeV;
  ua_min_func = [](quantity<MegaElectronVolt> x){return 2.5*cgs::centimeter;};
  ua_max_func = [](quantity<MegaElectronVolt> x){return 7.5*cgs::centimeter;};

  sample = Utility::Direct<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );

  sample = Utility::Direct<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );

  sample = Utility::Direct<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-15 );

  // In the second bin
  ++ua_lower_bin; ++ua_upper_bin;
  fake_stream.resize( 12 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 0.4230769230769231;
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
  sample = Utility::Direct<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );

  sample = Utility::Direct<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );

  sample = Utility::Direct<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );

  // Samples from upper boundary of second bin
  sample = Utility::Direct<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = Utility::Direct<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );

  sample = Utility::Direct<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );

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

  sample = Utility::Direct<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );

  sample = Utility::Direct<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );

  sample = Utility::Direct<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, x_value, ua_lower_bin, ua_upper_bin );

  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( Direct, sampleDetailed )
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

  double sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<double,double>(
      functor, min_func, max_func, 0.0, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0 );

  sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<double,double>(
    functor, min_func, max_func, 0.0, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );
  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, 5.0 );

  sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<double,double>(
    functor, min_func, max_func, 0.0, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 10.0, 1e-14 );

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
  fake_stream[9] = 0.4230769230769231;
  fake_stream[10] = 0.49; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  min_func = [](double x){return 1.25;}; max_func = [](double x){return 8.75;};

  // Samples from lower boundary of first bin
  sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<double,double>(
    functor, min_func, max_func, 0.5, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0 );

  sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<double,double>(
    functor, min_func, max_func, 0.5, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );
  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, 5.0 );

  sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<double,double>(
    functor, min_func, max_func, 0.5, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 10.0, 1e-14 );

  // Samples from the upper boundary of the first bin
  sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<double,double>(
    functor, min_func, max_func, 0.5, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );
  FRENSIE_CHECK_EQUAL( sample, 2.5 );
  FRENSIE_CHECK_EQUAL( raw_sample, 2.5 );

  sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<double,double>(
    functor, min_func, max_func, 0.5, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 5.0, 1e-15 );

  sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<double,double>(
    functor, min_func, max_func, 0.5, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 7.5, 1e-14 );

  // On the second bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.4230769230769231;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  min_func = [](double x){return 2.5;}; max_func = [](double x){return 7.5;};

  sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<double,double>(
    functor, min_func, max_func, 1.0, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );
  FRENSIE_CHECK_EQUAL( sample, 2.5 );
  FRENSIE_CHECK_EQUAL( raw_sample, 2.5 );

  sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<double,double>(
    functor, min_func, max_func, 1.0, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 5.0, 1e-15 );

  sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<double,double>(
    functor, min_func, max_func, 1.0, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 7.5, 1e-15 );

  // In the second bin
  ++lower_bin; ++upper_bin;
  fake_stream.resize( 12 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 0.4230769230769231;
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
  sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<double,double>(
    functor, min_func, max_func, 1.5, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );
  FRENSIE_CHECK_EQUAL( sample, 2.5 );
  FRENSIE_CHECK_EQUAL( raw_sample, 2.5 );

  sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<double,double>(
    functor, min_func, max_func, 1.5, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 5.0, 1e-15 );

  sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<double,double>(
    functor, min_func, max_func, 1.5, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5, 1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 7.5, 1e-14 );

  // Samples from upper boundary of second bin
  sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<double,double>(
    functor, min_func, max_func, 1.5, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0 );

  sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<double,double>(
    functor, min_func, max_func, 1.5, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );
  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, 5.0 );

  sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<double,double>(
    functor, min_func, max_func, 1.5, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 10.0, 1e-14 );

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

  sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<double,double>(
    functor, min_func, max_func, 2.0, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );
  FRENSIE_CHECK_EQUAL( sample, 0.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0 );

  sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<double,double>(
    functor, min_func, max_func, 2.0, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );
  FRENSIE_CHECK_EQUAL( sample, 5.0 );
  FRENSIE_CHECK_EQUAL( raw_sample, 5.0 );

  sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<double,double>(
    functor, min_func, max_func, 2.0, lower_bin, upper_bin, sampled_bin, raw_sample );

  bin_index = std::distance( start_bin, sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0, 1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 10.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
FRENSIE_UNIT_TEST( UnitAwareDirect, sampleDetailed )
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
    Utility::Direct<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
      ua_functor, ua_min_func, ua_max_func, 0.0*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0*cgs::centimeter );

  sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, 0.0*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );
  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( raw_sample, 5.0*cgs::centimeter );

  sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, 0.0*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 10.0*cgs::centimeter, 1e-14 );

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
  fake_stream[9] = 0.4230769230769231;
  fake_stream[10] = 0.49; // use upper bin boundary
  fake_stream[11] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  ua_min_func = [](quantity<MegaElectronVolt> x){return 1.25*cgs::centimeter;};
  ua_max_func = [](quantity<MegaElectronVolt> x){return 8.75*cgs::centimeter;};

  // Samples from lower boundary of first bin
  sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, 0.5*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0*cgs::centimeter );

  sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, 0.5*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );
  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( raw_sample, 5.0*cgs::centimeter );

  sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, 0.5*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 10.0*cgs::centimeter, 1e-14 );

  // Samples from the upper boundary of the first bin
  sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, 0.5*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );
  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( raw_sample, 2.5*cgs::centimeter );

  sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, 0.5*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 5.0*cgs::centimeter, 1e-15 );

  sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, 0.5*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 7.5*cgs::centimeter, 1e-14 );

  // On the second bin
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.4230769230769231;
  fake_stream[4] = 0.0;
  fake_stream[5] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  ua_min_func = [](quantity<MegaElectronVolt> x){return 2.5*cgs::centimeter;};
  ua_max_func = [](quantity<MegaElectronVolt> x){return 7.5*cgs::centimeter;};

  sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, 1.0*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );
  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( raw_sample, 2.5*cgs::centimeter );

  sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, 1.0*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 5.0*cgs::centimeter, 1e-15 );

  sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, 1.0*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 7.5*cgs::centimeter, 1e-15 );

  // In the second bin
  ++ua_lower_bin; ++ua_upper_bin;
  fake_stream.resize( 12 );
  fake_stream[0] = 0.5; // use lower bin boundary
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5; // use lower bin boundary
  fake_stream[3] = 0.4230769230769231;
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
  sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, 1.5*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );
  FRENSIE_CHECK_EQUAL( sample, 2.5*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( raw_sample, 2.5*cgs::centimeter );

  sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, 1.5*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 5.0*cgs::centimeter, 1e-15 );

  sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, 1.5*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 1u );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 7.5*cgs::centimeter, 1e-14 );

  // Samples from upper boundary of second bin
  sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, 1.5*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0*cgs::centimeter );

  sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, 1.5*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );
  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( raw_sample, 5.0*cgs::centimeter );

  sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, 1.5*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 10.0*cgs::centimeter, 1e-14 );

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

  sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, 2.0*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );
  FRENSIE_CHECK_EQUAL( sample, 0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( raw_sample, 0.0*cgs::centimeter );

  sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, 2.0*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );
  FRENSIE_CHECK_EQUAL( sample, 5.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( raw_sample, 5.0*cgs::centimeter );

  sample = Utility::Direct<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
    ua_functor, ua_min_func, ua_max_func, 2.0*MeV, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( raw_sample, 10.0*cgs::centimeter, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create the two-dimensional distribution
  {
    DistributionType distribution_data( 3 );

    // Create the secondary distribution in the first bin
    Utility::get<0>( distribution_data[0] ) = 0.0;
    Utility::get<1>( distribution_data[0] ) = std::make_shared<Utility::UniformDistribution>( 0.0, 10.0, 1.0 );

    // Create the secondary distribution in the second bin
    std::vector<double> bin_boundaries( 3 ), values( 3 );
    bin_boundaries[0] = 2.5; values[0] = 0.1;
    bin_boundaries[1] = 5.0; values[1] = 1.0;
    bin_boundaries[2] = 7.5; values[2] = 0.5;

    Utility::get<0>( distribution_data[1] ) = 1.0;
    Utility::get<1>( distribution_data[1] ) = std::make_shared<Utility::TabularDistribution<Utility::LinLin> >( bin_boundaries, values );

    // Create the secondary distribution beyond the second bin
    Utility::get<0>( distribution_data[2] ) = 2.0;
    Utility::get<1>( distribution_data[2] ) = std::make_shared<Utility::UniformDistribution>( 0.0, 10.0, 0.1 );

    distribution.reset( new DistributionType( distribution_data ) );

    // Create the sampling functor
    functor = std::bind<double>( &Utility::TabularUnivariateDistribution::sample,
                                 std::placeholders::_1 );
  }

  // Create the unit-aware two-dimensional distribution
  {
    UnitAwareDistributionType distribution_data( 3 );

    // Create the secondary distribution in the first bin
    Utility::get<0>( distribution_data[0] ) = 0.0*MeV;
    Utility::get<1>( distribution_data[0] ) = std::make_shared<Utility::UnitAwareUniformDistribution<cgs::length,Barn> >( 0.0*cgs::centimeter, 10.0*cgs::centimeter, 1.0*barn );

    // Create the secondary distribution in the second bin
    std::vector<quantity<cgs::length> > bin_boundaries( 3 );
    std::vector<quantity<Barn> > values( 3 );
    bin_boundaries[0] = 2.5*cgs::centimeter; values[0] = 0.1*barn;
    bin_boundaries[1] = 5.0*cgs::centimeter; values[1] = 1.0*barn;
    bin_boundaries[2] = 7.5*cgs::centimeter; values[2] = 0.5*barn;

    Utility::get<0>( distribution_data[1] ) = 1.0*MeV;
    Utility::get<1>( distribution_data[1] ) = std::make_shared<Utility::UnitAwareTabularDistribution<Utility::LinLin,cgs::length,Barn> >( bin_boundaries, values );

    // Create the secondary distribution beyond the second bin
    Utility::get<0>( distribution_data[2] ) = 2.0*MeV;
    Utility::get<1>( distribution_data[2] ) = std::make_shared<Utility::UnitAwareUniformDistribution<cgs::length,Barn> >( 0.0*cgs::centimeter, 10.0*cgs::centimeter, 0.1*barn );

    unit_aware_distribution.reset(
        new UnitAwareDistributionType( distribution_data ) );

    // Create the sampling functor
    ua_functor = std::bind<YIndepType>(
      &Utility::UnitAwareTabularUnivariateDistribution<cgs::length,Barn>::sample,
      std::placeholders::_1 );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstDirectTwoDGridPolicy.cpp
//---------------------------------------------------------------------------//
