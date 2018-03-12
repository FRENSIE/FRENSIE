//---------------------------------------------------------------------------//
//!
//! \file   tstCorrelatedTwoDGridPolicy.cpp
//! \author Luke Kersting
//! \brief  The Correlated two-dimensional sampling policy unit tests
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

std::function<double (double)> func;
std::function<YIndepType(const XIndepType)> ua_func;

Utility::FullyTabularTwoDDistribution::DistributionType::const_iterator
  lower_bin, upper_bin, sampled_bin, start_bin;

Utility::UnitAwareFullyTabularTwoDDistribution<MegaElectronVolt,cgs::length,Barn>::DistributionType::const_iterator
  ua_lower_bin, ua_upper_bin, ua_sampled_bin, ua_start_bin;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Return the sampling functor
std::function<double(const Utility::TabularOneDDistribution&)> getFunctor()
{
  // Use this random number to do create the Correlated sampling functor
  const double random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  // Create the sampling functor
  return std::bind<double>(
                    &Utility::TabularOneDDistribution::sampleWithRandomNumber,
                    std::placeholders::_1,
                    random_number );
}
// Return the sampling functor
std::function<YIndepType(const Utility::UnitAwareTabularOneDDistribution<cgs::length,Barn>&)> getUnitAwareFunctor()
{
  // Use this random number to do create the Correlated sampling functor
  const double random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  // Create the sampling functor
  return std::bind<YIndepType>(
    &Utility::UnitAwareTabularOneDDistribution<cgs::length,Barn>::sampleWithRandomNumber,
    std::placeholders::_1,
    random_number );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution is tabular in the primary dimension
TEUCHOS_UNIT_TEST( Correlated,
                   name )
{
  std::string name = Utility::Correlated<Utility::LinLinLin>::name();

  TEST_ASSERT( name == "LinLinLin Correlated" );
}

//---------------------------------------------------------------------------//
// Check that the Y lower bound can be calculated
TEUCHOS_UNIT_TEST( Correlated, calculateLowerBound )
{
  lower_bin = distribution->begin();
  upper_bin = lower_bin;
  ++upper_bin;

  // On the first bin boundary
  double x_value = 0.0;
  double bound = Utility::Correlated<Utility::LinLinLin>::calculateLowerBound<double>(
                    x_value, lower_bin, upper_bin );
  TEST_EQUALITY_CONST( bound, 0.0 );

  // In the first bin
  x_value = 0.5;
  bound = Utility::Correlated<Utility::LinLinLin>::calculateLowerBound<double>(
                    x_value, lower_bin, upper_bin );
  TEST_EQUALITY_CONST( bound, 1.25 );

  // On the second bin boundary
  ++lower_bin; ++upper_bin;
  x_value = 1.0;
  bound = Utility::Correlated<Utility::LinLinLin>::calculateLowerBound<double>(
                    x_value, lower_bin, upper_bin );
  TEST_EQUALITY_CONST( bound, 2.5 );

  // In the second bin
  x_value = 1.5;
  bound = Utility::Correlated<Utility::LinLinLin>::calculateLowerBound<double>(
                    x_value, lower_bin, upper_bin );
  TEST_EQUALITY_CONST( bound, 1.25 );

  // On the upper bin boundary
  x_value = 2.0;
  bound = Utility::Correlated<Utility::LinLinLin>::calculateLowerBound<double>(
                    x_value, lower_bin, upper_bin );
  TEST_EQUALITY_CONST( bound, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the Y lower bound can be calculated
TEUCHOS_UNIT_TEST( Correlated, calculateUpperBound )
{
  lower_bin = distribution->begin();
  upper_bin = lower_bin;
  ++upper_bin;

  // On the first bin boundary
  double x_value = 0.0;
  double bound = Utility::Correlated<Utility::LinLinLin>::calculateUpperBound<double>(
                    x_value, lower_bin, upper_bin );
  TEST_EQUALITY_CONST( bound, 10.0 );

  // In the first bin
  x_value = 0.5;
  bound = Utility::Correlated<Utility::LinLinLin>::calculateUpperBound<double>(
                    x_value, lower_bin, upper_bin );
  TEST_EQUALITY_CONST( bound, 8.75 );

  // On the second bin boundary
  ++lower_bin; ++upper_bin;
  x_value = 1.0;
  bound = Utility::Correlated<Utility::LinLinLin>::calculateUpperBound<double>(
                    x_value, lower_bin, upper_bin );
  TEST_EQUALITY_CONST( bound, 7.5 );

  // In the second bin
  x_value = 1.5;
  bound = Utility::Correlated<Utility::LinLinLin>::calculateUpperBound<double>(
                    x_value, lower_bin, upper_bin );
  TEST_EQUALITY_CONST( bound, 8.75 );

  // On the upper bin boundary
  x_value = 2.0;
  bound = Utility::Correlated<Utility::LinLinLin>::calculateUpperBound<double>(
                    x_value, lower_bin, upper_bin );
  TEST_EQUALITY_CONST( bound, 10.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( Correlated, evaluatePDF )
{
  std::function<double(double,double)> evaluate =
  [&func, &lower_bin, &upper_bin](double x_value, double y_value)
  {
    return Utility::Correlated<Utility::LinLinLin>::evaluatePDF<Utility::TabularOneDDistribution,double,double,double>(
      x_value, y_value, func, func, &Utility::TabularOneDDistribution::evaluate, lower_bin, upper_bin, 1e-3, 1e-15 );
  };

  lower_bin = distribution->begin();
  upper_bin = lower_bin;
  ++upper_bin;

  double x_value = 0.0;
  func = [](double x){return 0.0;}; func = [](double x){return 10.0;};;

  // On the first bin boundary
  TEST_EQUALITY_CONST( evaluate( 0.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( evaluate( 0.0, 0.0 ), 1.0 );
  TEST_EQUALITY_CONST( evaluate( 0.0, 5.0 ), 1.0 );
  TEST_EQUALITY_CONST( evaluate( 0.0, 10.0 ), 1.0 );
  TEST_EQUALITY_CONST( evaluate( 0.0, 11.0 ), 0.0 );

  // In the first bin
  func = [](double x){return 1.25;}; func = [](double x){return 8.75;};

  TEST_EQUALITY_CONST( evaluate( 0.5, 1.0 ), 0.0 );
  TEST_EQUALITY_CONST( evaluate( 0.5, 1.25 ), 2.0/11.0 );
  TEST_FLOATING_EQUALITY( evaluate( 0.5, 5.0 ), 9.8048179459037177e-01, 1e-12 );
  TEST_EQUALITY_CONST( evaluate( 0.5, 8.75 ), 2.0/3.0 );
  TEST_EQUALITY_CONST( evaluate( 0.5, 9.0 ), 0. );

  // On the second bin boundary
  ++lower_bin; ++upper_bin;
  func = [](double x){return 2.5;}; func = [](double x){return 7.5;};

  TEST_EQUALITY_CONST( evaluate( 1.0, 2.0 ), 0.0 );
  TEST_EQUALITY_CONST( evaluate( 1.0, 2.5 ), 0.1 );
  TEST_EQUALITY_CONST( evaluate( 1.0, 5.0 ), 1.0 );
  TEST_EQUALITY_CONST( evaluate( 1.0, 7.5 ), 0.5 );
  TEST_EQUALITY_CONST( evaluate( 1.0, 8.0 ), 0.0 );

  // In the second bin
  func = [](double x){return 1.25;}; func = [](double x){return 8.75;};

  TEST_EQUALITY_CONST( evaluate( 1.5, 1.0 ), 0.0 );
  TEST_EQUALITY_CONST( evaluate( 1.5, 1.25 ), 0.1 );
  TEST_FLOATING_EQUALITY( evaluate( 1.5, 5.0 ), 1.8116248070721774e-01, 1e-12 );
  TEST_EQUALITY_CONST( evaluate( 1.5, 8.75 ), 1.0/6.0 );
  TEST_EQUALITY_CONST( evaluate( 1.5, 9.0 ), 0.0 );

  // On the upper bin boundary
  func = [](double x){return 0.0;}; func = [](double x){return 10.0;};

  TEST_EQUALITY_CONST( evaluate( 2.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( evaluate( 2.0, 0.0 ), 0.1 );
  TEST_EQUALITY_CONST( evaluate( 2.0, 5.0 ), 0.1 );
  TEST_EQUALITY_CONST( evaluate( 2.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( evaluate( 2.0, 11.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareCorrelated, evaluatePDF )
{
  std::function<ZDepType(XIndepType,YIndepType)> evaluate =
  [&ua_func, &ua_lower_bin, &ua_upper_bin](XIndepType x_value, YIndepType y_value)
  {
    return Utility::Correlated<Utility::LinLinLin>::evaluatePDF<Utility::UnitAwareTabularOneDDistribution<cgs::length,Barn>,XIndepType,YIndepType,ZDepType>(
      x_value, y_value, ua_func, ua_func, &Utility::UnitAwareTabularOneDDistribution<cgs::length,Barn>::evaluate, ua_lower_bin, ua_upper_bin, 1e-3, 1e-15 );
  };

  ua_lower_bin = unit_aware_distribution->begin();
  ua_upper_bin = ua_lower_bin;
  ++ua_upper_bin;

  ua_func = [](XIndepType x){return 0.0*cgs::centimeter;};
  ua_func = [](XIndepType x){return 10.0*cgs::centimeter;};

  // On the first bin boundary
  TEST_EQUALITY_CONST( evaluate( 0.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( evaluate( 0.0*MeV, 0.0*cgs::centimeter ), 1.0*barn );
  TEST_EQUALITY_CONST( evaluate( 0.0*MeV, 5.0*cgs::centimeter ), 1.0*barn );
  TEST_EQUALITY_CONST( evaluate( 0.0*MeV, 10.0*cgs::centimeter ), 1.0*barn );
  TEST_EQUALITY_CONST( evaluate( 0.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );

  // In the first bin
  ua_func = [](XIndepType x){return 1.25*cgs::centimeter;};
  ua_func = [](XIndepType x){return 8.75*cgs::centimeter;};

  TEST_EQUALITY_CONST( evaluate( 0.5*MeV, 1.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( evaluate( 0.5*MeV, 1.25*cgs::centimeter ), 2.0/11.0*barn );
  UTILITY_TEST_FLOATING_EQUALITY( evaluate( 0.5*MeV, 5.0*cgs::centimeter ),
                                  9.8048179459037177e-01*barn,
                                  1e-12 );
  TEST_EQUALITY_CONST( evaluate( 0.5*MeV, 8.75*cgs::centimeter ), 2.0/3.0*barn );
  TEST_EQUALITY_CONST( evaluate( 0.5*MeV, 9.0*cgs::centimeter ), 0.0*barn );

  // On the second bin boundary
  ++ua_lower_bin; ++ua_upper_bin;
  ua_func = [](XIndepType x){return 2.5*cgs::centimeter;};
  ua_func = [](XIndepType x){return 7.5*cgs::centimeter;};

  TEST_EQUALITY_CONST( evaluate( 1.0*MeV, 2.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( evaluate( 1.0*MeV, 2.5*cgs::centimeter ), 0.1*barn );
  TEST_EQUALITY_CONST( evaluate( 1.0*MeV, 5.0*cgs::centimeter ), 1.0*barn );
  TEST_EQUALITY_CONST( evaluate( 1.0*MeV, 7.5*cgs::centimeter ), 0.5*barn );
  TEST_EQUALITY_CONST( evaluate( 1.0*MeV, 8.0*cgs::centimeter ), 0.0*barn );

  // In the second bin
  ua_func = [](XIndepType x){return 1.25*cgs::centimeter;};
  ua_func = [](XIndepType x){return 8.75*cgs::centimeter;};

  TEST_EQUALITY_CONST( evaluate( 1.5*MeV, 1.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( evaluate( 1.5*MeV, 1.25*cgs::centimeter ), 0.1*barn );
  UTILITY_TEST_FLOATING_EQUALITY( evaluate( 1.5*MeV, 5.0*cgs::centimeter ),
                                  1.8116248070721774e-01*barn,
                                  1e-12 );
  TEST_EQUALITY_CONST( evaluate( 1.5*MeV, 8.75*cgs::centimeter ), 1.0/6.0*barn );
  TEST_EQUALITY_CONST( evaluate( 1.5*MeV, 9.0*cgs::centimeter ), 0.0*barn );

  // On the upper bin boundary
  ua_func = [](XIndepType x){return 0.0*cgs::centimeter;};
  ua_func = [](XIndepType x){return 10.0*cgs::centimeter;};

  TEST_EQUALITY_CONST( evaluate( 2.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( evaluate( 2.0*MeV, 0.0*cgs::centimeter ), 0.1*barn );
  TEST_EQUALITY_CONST( evaluate( 2.0*MeV, 5.0*cgs::centimeter ), 0.1*barn );
  TEST_EQUALITY_CONST( evaluate( 2.0*MeV, 10.0*cgs::centimeter ), 0.1*barn );
  TEST_EQUALITY_CONST( evaluate( 2.0*MeV, 11.0*cgs::centimeter ), 0.0*barn );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( Correlated, evaluateCDF )
{
  std::function<double(double,double)> evaluate =
  [&func, &lower_bin, &upper_bin](double x_value, double y_value)
  {
    return Utility::Correlated<Utility::LinLinLin>::evaluateCDF<Utility::TabularOneDDistribution,double,double>(
      x_value, y_value, func, func, &Utility::TabularOneDDistribution::evaluateCDF, lower_bin, upper_bin, 1e-3, 1e-15 );
  };

  lower_bin = distribution->begin();
  upper_bin = lower_bin;
  ++upper_bin;

  double x_value = 0.0;
  func = [](double x){return 0.0;}; func = [](double x){return 10.0;};;

  // On the first bin boundary
  TEST_EQUALITY_CONST( evaluate( 0.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( evaluate( 0.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( evaluate( 0.0, 5.0 ), 0.5 );
  TEST_EQUALITY_CONST( evaluate( 0.0, 10.0 ), 1.0 );
  TEST_EQUALITY_CONST( evaluate( 0.0, 11.0 ), 1.0 );

  // In the first bin
  func = [](double x){return 1.25;}; func = [](double x){return 8.75;};

  TEST_EQUALITY_CONST( evaluate( 0.5, 1.0 ), 0.0 );
  TEST_EQUALITY_CONST( evaluate( 0.5, 1.25 ), 0.0 );
  TEST_FLOATING_EQUALITY( evaluate( 0.5, 4.615384615384615 ), 0.4230769230769231, 1e-12 );
  TEST_EQUALITY_CONST( evaluate( 0.5, 8.75 ), 1.0 );
  TEST_EQUALITY_CONST( evaluate( 0.5, 9.0 ), 1.0 );

  // On the second bin boundary
  ++lower_bin; ++upper_bin;
  func = [](double x){return 2.5;}; func = [](double x){return 7.5;};

  TEST_EQUALITY_CONST( evaluate( 1.0, 2.0 ), 0.0 );
  TEST_EQUALITY_CONST( evaluate( 1.0, 2.5 ), 0.0 );
  TEST_FLOATING_EQUALITY( evaluate( 1.0, 5.0 ), 0.4230769230769231, 1e-15 );
  TEST_EQUALITY_CONST( evaluate( 1.0, 7.5 ), 1.0 );
  TEST_EQUALITY_CONST( evaluate( 1.0, 8.0 ), 1.0 );

  // In the second bin
  func = [](double x){return 1.25;}; func = [](double x){return 8.75;};

  TEST_EQUALITY_CONST( evaluate( 1.5, 1.0 ), 0.0 );
  TEST_EQUALITY_CONST( evaluate( 1.5, 1.25 ), 0.0 );
  TEST_FLOATING_EQUALITY( evaluate( 1.5, 4.615384615384615 ), 0.4230769230769231, 1e-12 );
  TEST_EQUALITY_CONST( evaluate( 1.5, 8.75 ), 1.0 );
  TEST_EQUALITY_CONST( evaluate( 1.5, 9.0 ), 1.0 );

  // On the upper bin boundary
  func = [](double x){return 0.0;}; func = [](double x){return 10.0;};

  TEST_EQUALITY_CONST( evaluate( 2.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( evaluate( 2.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( evaluate( 2.0, 5.0 ), 0.5 );
  TEST_EQUALITY_CONST( evaluate( 2.0, 10.0 ), 1.0 );
  TEST_EQUALITY_CONST( evaluate( 2.0, 11.0 ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareCorrelated, evaluateCDF )
{
  std::function<double(XIndepType,YIndepType)> evaluate =
  [&ua_func, &ua_lower_bin, &ua_upper_bin](XIndepType x_value, YIndepType y_value)
  {
    return Utility::Correlated<Utility::LinLinLin>::evaluateCDF<Utility::UnitAwareTabularOneDDistribution<cgs::length,Barn>,XIndepType,YIndepType>(
      x_value, y_value, ua_func, ua_func, &Utility::UnitAwareTabularOneDDistribution<cgs::length,Barn>::evaluateCDF, ua_lower_bin, ua_upper_bin, 1e-3, 1e-15 );
  };

  ua_lower_bin = unit_aware_distribution->begin();
  ua_upper_bin = ua_lower_bin;
  ++ua_upper_bin;

  ua_func = [](XIndepType x){return 0.0*cgs::centimeter;};
  ua_func = [](XIndepType x){return 10.0*cgs::centimeter;};

  // On the first bin boundary
  TEST_EQUALITY_CONST( evaluate( 0.0*MeV, -1.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( evaluate( 0.0*MeV, 0.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( evaluate( 0.0*MeV, 5.0*cgs::centimeter ), 0.5 );
  TEST_EQUALITY_CONST( evaluate( 0.0*MeV, 10.0*cgs::centimeter ), 1.0 );
  TEST_EQUALITY_CONST( evaluate( 0.0*MeV, 11.0*cgs::centimeter ), 1.0 );

  // In the first bin
  ua_func = [](XIndepType x){return 1.25*cgs::centimeter;};
  ua_func = [](XIndepType x){return 8.75*cgs::centimeter;};

  TEST_EQUALITY_CONST( evaluate( 0.5*MeV, 1.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( evaluate( 0.5*MeV, 1.25*cgs::centimeter ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( evaluate( 0.5*MeV, 4.615384615384615*cgs::centimeter ),
                                  0.4230769230769231,
                                  1e-12 );

  TEST_EQUALITY_CONST( evaluate( 0.5*MeV, 8.75*cgs::centimeter ), 1.0 );
  TEST_EQUALITY_CONST( evaluate( 0.5*MeV, 9.0*cgs::centimeter ), 1.0 );

  // On the second bin boundary
  ++ua_lower_bin; ++ua_upper_bin;
  ua_func = [](XIndepType x){return 2.5*cgs::centimeter;};
  ua_func = [](XIndepType x){return 7.5*cgs::centimeter;};

  TEST_EQUALITY_CONST( evaluate( 1.0*MeV, 2.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( evaluate( 1.0*MeV, 2.5*cgs::centimeter ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( evaluate( 1.0*MeV, 5.0*cgs::centimeter ), 0.4230769230769231, 1e-15 );
  TEST_EQUALITY_CONST( evaluate( 1.0*MeV, 7.5*cgs::centimeter ), 1.0 );
  TEST_EQUALITY_CONST( evaluate( 1.0*MeV, 8.0*cgs::centimeter ), 1.0 );

  // In the second bin
  ua_func = [](XIndepType x){return 1.25*cgs::centimeter;};
  ua_func = [](XIndepType x){return 8.75*cgs::centimeter;};

  TEST_EQUALITY_CONST( evaluate( 1.5*MeV, 1.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( evaluate( 1.5*MeV, 1.25*cgs::centimeter ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( evaluate( 1.5*MeV, 4.615384615384615*cgs::centimeter ),
                                  0.4230769230769231,
                                  1e-12 );

  TEST_EQUALITY_CONST( evaluate( 1.5*MeV, 8.75*cgs::centimeter ), 1.0 );
  TEST_EQUALITY_CONST( evaluate( 1.5*MeV, 9.0*cgs::centimeter ), 1.0 );

  // On the upper bin boundary
  ua_func = [](XIndepType x){return 0.0*cgs::centimeter;};
  ua_func = [](XIndepType x){return 10.0*cgs::centimeter;};

  TEST_EQUALITY_CONST( evaluate( 2.0*MeV, -1.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( evaluate( 2.0*MeV, 0.0*cgs::centimeter ), 0.0 );
  TEST_EQUALITY_CONST( evaluate( 2.0*MeV, 5.0*cgs::centimeter ), 0.5 );
  TEST_EQUALITY_CONST( evaluate( 2.0*MeV, 10.0*cgs::centimeter ), 1.0 );
  TEST_EQUALITY_CONST( evaluate( 2.0*MeV, 11.0*cgs::centimeter ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( Correlated, sample )
{
  // On the first bin
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  std::function<double(double)> sample_function =
  [&functor, &func, &lower_bin, &upper_bin](double x_value)
  {
    return Utility::Correlated<Utility::LinLinLin>::sample<double,double>(
      functor, func, func, x_value, lower_bin, upper_bin );
  };

  lower_bin = distribution->begin();
  upper_bin = lower_bin;
  ++upper_bin;

  double x_value = 0.0;
  func = [](double x){return 0.0;}; func = [](double x){return 10.0;};
  functor = getFunctor();

  double sample = sample_function( x_value );
  TEST_EQUALITY_CONST( sample, 0.0 );

  functor = getFunctor();
  sample = sample_function( x_value );
  TEST_EQUALITY_CONST( sample, 5.0 );

  functor = getFunctor();
  sample = sample_function( x_value );
  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-14 );

  // In the first bin
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.4230769230769231;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  x_value = 0.5;
  func = [](double x){return 1.25;}; func = [](double x){return 8.75;};

  functor = getFunctor();
  sample = sample_function( x_value );
  TEST_EQUALITY_CONST( sample, 1.25 );

  functor = getFunctor();
  sample = sample_function( x_value );
  TEST_EQUALITY_CONST( sample, 4.615384615384615 );

  functor = getFunctor();
  sample = sample_function( x_value );
  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-14 );

  // On the second bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  x_value = 1.0;
  func = [](double x){return 2.5;}; func = [](double x){return 7.5;};

  functor = getFunctor();
  sample = sample_function( x_value );
  TEST_EQUALITY_CONST( sample, 2.5 );

  functor = getFunctor();
  sample = sample_function( x_value );
  TEST_FLOATING_EQUALITY( sample, 5.0, 1e-15 );

  functor = getFunctor();
  sample = sample_function( x_value );
  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-15 );

  // In the second bin
  ++lower_bin; ++upper_bin;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  x_value = 1.5;
  func = [](double x){return 1.25;}; func = [](double x){return 8.75;};

  functor = getFunctor();
  sample = sample_function( x_value );
  TEST_EQUALITY_CONST( sample, 1.25 );

  functor = getFunctor();
  sample = sample_function( x_value );
  TEST_FLOATING_EQUALITY( sample, 4.615384615384615, 1e-15 );

  functor = getFunctor();
  sample = sample_function( x_value );
  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-14 );


  // On the upper bin boundary
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  x_value = 2.0;
  func = [](double x){return 0.0;}; func = [](double x){return 10.0;};

  functor = getFunctor();
  sample = sample_function( x_value );
  TEST_EQUALITY_CONST( sample, 0.0 );

  functor = getFunctor();
  sample = sample_function( x_value );
  TEST_EQUALITY_CONST( sample, 5.0 );

  functor = getFunctor();
  sample = sample_function( x_value );
  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareCorrelated, sample )
{
  std::function<YIndepType(XIndepType)> sample_function =
  [&ua_functor, &ua_func, &ua_lower_bin, &ua_upper_bin](XIndepType x_value)
  {
    return Utility::Correlated<Utility::LinLinLin>::sample<XIndepType,YIndepType>(
      ua_functor, ua_func, ua_func, x_value, ua_lower_bin, ua_upper_bin );
  };

  // On the first bin
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  ua_lower_bin = unit_aware_distribution->begin();
  ua_upper_bin = ua_lower_bin;
  ++ua_upper_bin;
  XIndepType x_value = 0.0*MeV;
  ua_func = [](XIndepType x){return 0.0*cgs::centimeter;};
  ua_func = [](XIndepType x){return 10.0*cgs::centimeter;};

  ua_functor = getUnitAwareFunctor();
  quantity<cgs::length> sample = sample_function( x_value );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  ua_functor = getUnitAwareFunctor();
  sample = sample_function( x_value);
  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  ua_functor = getUnitAwareFunctor();
  sample = sample_function( x_value);
  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );

  // In the first bin
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.4230769230769231;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  x_value = 0.5*MeV;
  ua_func = [](XIndepType x){return 1.25*cgs::centimeter;};
  ua_func = [](XIndepType x){return 8.75*cgs::centimeter;};

  ua_functor = getUnitAwareFunctor();
  sample = sample_function( x_value);
  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  ua_functor = getUnitAwareFunctor();
  sample = sample_function( x_value);
  TEST_EQUALITY_CONST( sample, 4.615384615384615*cgs::centimeter );

  ua_functor = getUnitAwareFunctor();
  sample = sample_function( x_value);
  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-14 );

  // On the second bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  x_value = 1.0*MeV;
  ua_func = [](XIndepType x){return 2.5*cgs::centimeter;};
  ua_func = [](XIndepType x){return 7.5*cgs::centimeter;};

  ua_functor = getUnitAwareFunctor();
  sample = sample_function( x_value);
  TEST_EQUALITY_CONST( sample, 2.5*cgs::centimeter );

  ua_functor = getUnitAwareFunctor();
  sample = sample_function( x_value);
  UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );

  ua_functor = getUnitAwareFunctor();
  sample = sample_function( x_value);
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-15 );

  // In the second bin
  ++ua_lower_bin; ++ua_upper_bin;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  x_value = 1.5*MeV;
  ua_func = [](XIndepType x){return 1.25*cgs::centimeter;};
  ua_func = [](XIndepType x){return 8.75*cgs::centimeter;};

  ua_functor = getUnitAwareFunctor();
  sample = sample_function( x_value);
  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  ua_functor = getUnitAwareFunctor();
  sample = sample_function( x_value);
  UTILITY_TEST_FLOATING_EQUALITY( sample, 4.615384615384615*cgs::centimeter, 1e-15 );

  ua_functor = getUnitAwareFunctor();
  sample = sample_function( x_value);
  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-14 );

  // On the upper bin boundary
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  x_value = 2.0*MeV;
  ua_func = [](XIndepType x){return 0.0*cgs::centimeter;};
  ua_func = [](XIndepType x){return 10.0*cgs::centimeter;};

  ua_functor = getUnitAwareFunctor();
  sample = sample_function( x_value);
  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  ua_functor = getUnitAwareFunctor();
  sample = sample_function( x_value);
  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  ua_functor = getUnitAwareFunctor();
  sample = sample_function( x_value);
  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( Correlated, sampleDetailed )
{
  double raw_sample;
  std::function<double(double)> sample_function =
  [&functor, &func, &lower_bin, &upper_bin, &sampled_bin, &raw_sample](double x_value)
  {
    return Utility::Correlated<Utility::LinLinLin>::sampleDetailed<double,double>(
      functor, func, func, x_value, lower_bin, upper_bin, sampled_bin, raw_sample );
  };

  // On the first bin
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned bin_index;

  start_bin = distribution->begin();
  lower_bin = start_bin;
  upper_bin = lower_bin;
  ++upper_bin;
  func = [](double x){return 0.0;}; func = [](double x){return 10.0;};;

  functor = getFunctor();
  double sample = sample_function( 0.0 );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 0u );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( raw_sample, 0.0 );

  functor = getFunctor();
  sample = sample_function( 0.0 );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 0u );
  TEST_EQUALITY_CONST( sample, 5.0 );
  TEST_EQUALITY_CONST( raw_sample, 5.0 );

  functor = getFunctor();
  sample = sample_function( 0.0 );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 0u );
  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-14 );
  TEST_FLOATING_EQUALITY( raw_sample, 10.0, 1e-14 );

  // In the first bin
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.4230769230769231;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  func = [](double x){return 1.25;}; func = [](double x){return 8.75;};;

  functor = getFunctor();
  sample = sample_function( 0.5 );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 0u );
  TEST_EQUALITY_CONST( sample, 1.25 );
  TEST_EQUALITY_CONST( raw_sample, 1.25 );

  functor = getFunctor();
  sample = sample_function( 0.5 );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 0u );
  TEST_EQUALITY_CONST( sample, 4.615384615384615 );
  TEST_EQUALITY_CONST( raw_sample, 4.615384615384615 );

  functor = getFunctor();
  sample = sample_function( 0.5 );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 0u );
  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-14 );
  TEST_FLOATING_EQUALITY( raw_sample, 8.75, 1e-14 );

  // On the second bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  func = [](double x){return 2.5;}; func = [](double x){return 7.5;};;

  functor = getFunctor();
  sample = sample_function( 1.0 );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  TEST_EQUALITY_CONST( sample, 2.5 );
  TEST_EQUALITY_CONST( raw_sample, 2.5 );

  functor = getFunctor();
  sample = sample_function( 1.0 );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  TEST_FLOATING_EQUALITY( sample, 5.0, 1e-15 );
  TEST_FLOATING_EQUALITY( raw_sample, 5.0, 1e-15 );

  functor = getFunctor();
  sample = sample_function( 1.0 );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-15 );
  TEST_FLOATING_EQUALITY( raw_sample, 7.5, 1e-15 );

  // In the second bin
  ++lower_bin; ++upper_bin;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  func = [](double x){return 1.25;}; func = [](double x){return 8.75;};;

  functor = getFunctor();
  sample = sample_function( 1.5 );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  TEST_EQUALITY_CONST( sample, 1.25 );
  TEST_EQUALITY_CONST( raw_sample, 1.25 );

  functor = getFunctor();
  sample = sample_function( 1.5 );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  TEST_FLOATING_EQUALITY( sample, 4.615384615384615, 1e-15 );
  TEST_FLOATING_EQUALITY( raw_sample, 4.615384615384615, 1e-15 );

  functor = getFunctor();
  sample = sample_function( 1.5 );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-14 );
  TEST_FLOATING_EQUALITY( raw_sample, 8.75, 1e-14 );

  // On the upper bin boundary
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  func = [](double x){return 0.0;}; func = [](double x){return 10.0;};;

  functor = getFunctor();
  sample = sample_function( 2.0 );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 2u );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( raw_sample, 0.0 );

  functor = getFunctor();
  sample = sample_function( 2.0 );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 2u );
  TEST_EQUALITY_CONST( sample, 5.0 );
  TEST_EQUALITY_CONST( raw_sample, 5.0 );

  functor = getFunctor();
  sample = sample_function( 2.0 );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 2u );
  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-14 );
  TEST_FLOATING_EQUALITY( raw_sample, 10.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareCorrelated, sampleDetailed )
{
  quantity<cgs::length> raw_sample;
  std::function<YIndepType(XIndepType)> sample_function =
  [&ua_functor, &ua_func, &ua_lower_bin, &ua_upper_bin, &ua_sampled_bin, &raw_sample](XIndepType x_value)
  {
    return Utility::Correlated<Utility::LinLinLin>::sampleDetailed<XIndepType,YIndepType>(
      ua_functor, ua_func, ua_func, x_value, ua_lower_bin, ua_upper_bin, ua_sampled_bin, raw_sample );
  };

  // On the first bin
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned bin_index;
  ua_start_bin = unit_aware_distribution->begin();
  ua_lower_bin = ua_start_bin;
  ua_upper_bin = ua_lower_bin;
  ++ua_upper_bin;
  ua_func = [](XIndepType x){return 0.0*cgs::centimeter;};
  ua_func = [](XIndepType x){return 10.0*cgs::centimeter;};

  ua_functor = getUnitAwareFunctor();
  quantity<cgs::length> sample = sample_function( 0.0*MeV );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 0u );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 0.0*cgs::centimeter );

  ua_functor = getUnitAwareFunctor();
  sample =  sample_function( 0.0*MeV );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 0u );
  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 5.0*cgs::centimeter );

  ua_functor = getUnitAwareFunctor();
  sample =  sample_function( 0.0*MeV );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 0u );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 10.0*cgs::centimeter, 1e-14 );

  // In the first bin
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.4230769230769231;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  ua_func = [](XIndepType x){return 1.25*cgs::centimeter;};
  ua_func = [](XIndepType x){return 8.75*cgs::centimeter;};

  ua_functor = getUnitAwareFunctor();
  sample =  sample_function( 0.5*MeV );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 0u );
  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 1.25*cgs::centimeter );

  ua_functor = getUnitAwareFunctor();
  sample =  sample_function( 0.5*MeV );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 0u );
  TEST_EQUALITY_CONST( sample, 4.615384615384615*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 4.615384615384615*cgs::centimeter );

  ua_functor = getUnitAwareFunctor();
  sample =  sample_function( 0.5*MeV );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 0u );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 8.75*cgs::centimeter, 1e-14 );

  // On the second bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  ua_func = [](XIndepType x){return 2.5*cgs::centimeter;};
  ua_func = [](XIndepType x){return 7.5*cgs::centimeter;};

  ua_functor = getUnitAwareFunctor();
  sample =  sample_function( 1.0*MeV );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  TEST_EQUALITY_CONST( sample, 2.5*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 2.5*cgs::centimeter );

  ua_functor = getUnitAwareFunctor();
  sample =  sample_function( 1.0*MeV );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 5.0*cgs::centimeter, 1e-15 );

  ua_functor = getUnitAwareFunctor();
  sample =  sample_function( 1.0*MeV );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 7.5*cgs::centimeter, 1e-15 );

  // In the second bin
  ++ua_lower_bin; ++ua_upper_bin;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  ua_func = [](XIndepType x){return 1.25*cgs::centimeter;};
  ua_func = [](XIndepType x){return 8.75*cgs::centimeter;};

  ua_functor = getUnitAwareFunctor();
  sample =  sample_function( 1.5*MeV );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 1.25*cgs::centimeter );

  ua_functor = getUnitAwareFunctor();
  sample =  sample_function( 1.5*MeV );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 4.615384615384615*cgs::centimeter, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 4.615384615384615*cgs::centimeter, 1e-15 );

  ua_functor = getUnitAwareFunctor();
  sample =  sample_function( 1.5*MeV );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 8.75*cgs::centimeter, 1e-14 );

  // On the upper bin boundary
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  ua_func = [](XIndepType x){return 0.0*cgs::centimeter;};
  ua_func = [](XIndepType x){return 10.0*cgs::centimeter;};

  ua_functor = getUnitAwareFunctor();
  sample =  sample_function( 2.0*MeV );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 2u );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 0.0*cgs::centimeter );

  ua_functor = getUnitAwareFunctor();
  sample =  sample_function( 2.0*MeV );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 2u );
  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 5.0*cgs::centimeter );

  ua_functor = getUnitAwareFunctor();
  sample =  sample_function( 2.0*MeV );

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
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstCorrelatedTwoDGridPolicy.cpp
//---------------------------------------------------------------------------//