//---------------------------------------------------------------------------//
//!
//! \file   tstCorrelatedTwoDSamplingPolicy.cpp
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
#include "Utility_TwoDSamplingPolicy.hpp"
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

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<Utility::FullyTabularTwoDDistribution::DistributionType> distribution;
std::shared_ptr<Utility::UnitAwareFullyTabularTwoDDistribution<MegaElectronVolt,cgs::length,Barn>::DistributionType> unit_aware_distribution;

std::function<double(const Utility::TabularOneDDistribution&)> functor;
std::function<YIndepType(const Utility::UnitAwareTabularOneDDistribution<cgs::length,Barn>&)> ua_functor;

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
  // Use this random number to do create the correlated sampling functor
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
  // Use this random number to do create the correlated sampling functor
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
  std::string name = Utility::Correlated::name();

  TEST_ASSERT( name == "Correlated" );
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

  lower_bin = distribution->begin();
  upper_bin = lower_bin;
  ++upper_bin;

  functor = getFunctor();
  double sample = Utility::Correlated::sample<Utility::LinLinLin,double,double>(
                              functor, lower_bin, upper_bin, 0.0 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  functor = getFunctor();
  sample = Utility::Correlated::sample<Utility::LinLinLin,double,double>(
                              functor, lower_bin, upper_bin, 0.0 );

  TEST_EQUALITY_CONST( sample, 5.0 );

  functor = getFunctor();
  sample = Utility::Correlated::sample<Utility::LinLinLin,double,double>(
                              functor, lower_bin, upper_bin, 0.0 );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-14 );

  // In the first bin
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.4230769230769231;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  functor = getFunctor();
  sample = Utility::Correlated::sample<Utility::LinLinLin,double,double>(
                              functor, lower_bin, upper_bin, 0.5 );

  TEST_EQUALITY_CONST( sample, 1.25 );

  functor = getFunctor();
  sample = Utility::Correlated::sample<Utility::LinLinLin,double,double>(
                              functor, lower_bin, upper_bin, 0.5 );

  TEST_EQUALITY_CONST( sample, 4.7115384615384617 );

  functor = getFunctor();
  sample = Utility::Correlated::sample<Utility::LinLinLin,double,double>(
                              functor, lower_bin, upper_bin, 0.5 );

  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-14 );

  // On the second bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  functor = getFunctor();
  sample = Utility::Correlated::sample<Utility::LinLinLin,double,double>(
                              functor, lower_bin, upper_bin, 1.0 );

  TEST_EQUALITY_CONST( sample, 2.5 );

  functor = getFunctor();
  sample = Utility::Correlated::sample<Utility::LinLinLin,double,double>(
                              functor, lower_bin, upper_bin, 1.0 );

  TEST_FLOATING_EQUALITY( sample, 5.0, 1e-15 );

  functor = getFunctor();
  sample = Utility::Correlated::sample<Utility::LinLinLin,double,double>(
                              functor, lower_bin, upper_bin, 1.0 );

  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-15 );

  // In the second bin
  ++lower_bin; ++upper_bin;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  functor = getFunctor();
  sample = Utility::Correlated::sample<Utility::LinLinLin,double,double>(
                              functor, lower_bin, upper_bin, 1.5 );

  TEST_EQUALITY_CONST( sample, 1.25 );

  functor = getFunctor();
  sample = Utility::Correlated::sample<Utility::LinLinLin,double,double>(
                              functor, lower_bin, upper_bin, 1.5 );

  TEST_FLOATING_EQUALITY( sample, 4.7115384615384617, 1e-15 );

  functor = getFunctor();
  sample = Utility::Correlated::sample<Utility::LinLinLin,double,double>(
                              functor, lower_bin, upper_bin, 1.5 );

  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-14 );

  // On the upper bin boundary
  fake_stream.resize( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  functor = getFunctor();
  sample = Utility::Correlated::sample<Utility::LinLinLin,double,double>(
                              functor, lower_bin, upper_bin, 2.0 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  functor = getFunctor();
  sample = Utility::Correlated::sample<Utility::LinLinLin,double,double>(
                              functor, lower_bin, upper_bin, 2.0 );

  TEST_EQUALITY_CONST( sample, 5.0 );

  functor = getFunctor();
  sample = Utility::Correlated::sample<Utility::LinLinLin,double,double>(
                              functor, lower_bin, upper_bin, 2.0 );

  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a unit-aware secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( UnitAwareCorrelated, sample )
{
  // On the first bin
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  ua_lower_bin = unit_aware_distribution->begin();
  ua_upper_bin = ua_lower_bin;
  ++ua_upper_bin;

  ua_functor = getUnitAwareFunctor();
  quantity<cgs::length> sample =
    Utility::Correlated::sample<Utility::LinLinLin,XIndepType,YIndepType>(
      ua_functor, ua_lower_bin, ua_upper_bin, 0.0*MeV );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  ua_functor = getUnitAwareFunctor();
  sample = Utility::Correlated::sample<Utility::LinLinLin,XIndepType,YIndepType>(
    ua_functor, ua_lower_bin, ua_upper_bin, 0.0*MeV );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  ua_functor = getUnitAwareFunctor();
  sample = Utility::Correlated::sample<Utility::LinLinLin,XIndepType,YIndepType>(
    ua_functor, ua_lower_bin, ua_upper_bin, 0.0*MeV );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );

  // In the first bin
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.4230769230769231;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  ua_functor = getUnitAwareFunctor();
  sample = Utility::Correlated::sample<Utility::LinLinLin,XIndepType,YIndepType>(
    ua_functor, ua_lower_bin, ua_upper_bin, 0.5*MeV );

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  ua_functor = getUnitAwareFunctor();
  sample = Utility::Correlated::sample<Utility::LinLinLin,XIndepType,YIndepType>(
    ua_functor, ua_lower_bin, ua_upper_bin, 0.5*MeV );

  TEST_EQUALITY_CONST( sample, 4.7115384615384617*cgs::centimeter );

  ua_functor = getUnitAwareFunctor();
  sample = Utility::Correlated::sample<Utility::LinLinLin,XIndepType,YIndepType>(
    ua_functor, ua_lower_bin, ua_upper_bin, 0.5*MeV );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-14 );

  // On the second bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  ua_functor = getUnitAwareFunctor();
  sample = Utility::Correlated::sample<Utility::LinLinLin,XIndepType,YIndepType>(
    ua_functor, ua_lower_bin, ua_upper_bin, 1.0*MeV );

  TEST_EQUALITY_CONST( sample, 2.5*cgs::centimeter );

  ua_functor = getUnitAwareFunctor();
  sample = Utility::Correlated::sample<Utility::LinLinLin,XIndepType,YIndepType>(
    ua_functor, ua_lower_bin, ua_upper_bin, 1.0*MeV );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );

  ua_functor = getUnitAwareFunctor();
  sample = Utility::Correlated::sample<Utility::LinLinLin,XIndepType,YIndepType>(
    ua_functor, ua_lower_bin, ua_upper_bin, 1.0*MeV );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-15 );

  // In the second bin
  ++ua_lower_bin; ++ua_upper_bin;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  ua_functor = getUnitAwareFunctor();
  sample = Utility::Correlated::sample<Utility::LinLinLin,XIndepType,YIndepType>(
    ua_functor, ua_lower_bin, ua_upper_bin, 1.5*MeV );

  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );

  ua_functor = getUnitAwareFunctor();
  sample = Utility::Correlated::sample<Utility::LinLinLin,XIndepType,YIndepType>(
    ua_functor, ua_lower_bin, ua_upper_bin, 1.5*MeV );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 4.7115384615384617*cgs::centimeter, 1e-15 );

  ua_functor = getUnitAwareFunctor();
  sample = Utility::Correlated::sample<Utility::LinLinLin,XIndepType,YIndepType>(
    ua_functor, ua_lower_bin, ua_upper_bin, 1.5*MeV );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-14 );

  // On the upper bin boundary
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  ua_functor = getUnitAwareFunctor();
  sample = Utility::Correlated::sample<Utility::LinLinLin,XIndepType,YIndepType>(
    ua_functor, ua_lower_bin, ua_upper_bin, 2.0*MeV );

  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );

  ua_functor = getUnitAwareFunctor();
  sample = Utility::Correlated::sample<Utility::LinLinLin,XIndepType,YIndepType>(
    ua_functor, ua_lower_bin, ua_upper_bin, 2.0*MeV );

  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );

  ua_functor = getUnitAwareFunctor();
  sample = Utility::Correlated::sample<Utility::LinLinLin,XIndepType,YIndepType>(
    ua_functor, ua_lower_bin, ua_upper_bin, 2.0*MeV );

  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( Correlated, sampleDetailed )
{
  // On the first bin
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double raw_sample;
  unsigned bin_index;

  start_bin = distribution->begin();
  lower_bin = start_bin;
  upper_bin = lower_bin;
  ++upper_bin;

  functor = getFunctor();
  double sample = Utility::Correlated::sampleDetailed<Utility::LinLinLin,double,double>(
      functor, raw_sample, sampled_bin, lower_bin, upper_bin, 0.0, 0.0, 10.0 );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 0u );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( raw_sample, 0.0 );

  functor = getFunctor();
  sample = Utility::Correlated::sampleDetailed<Utility::LinLinLin,double,double>(
      functor, raw_sample, sampled_bin, lower_bin, upper_bin, 0.0, 0.0, 10.0 );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 0u );
  TEST_EQUALITY_CONST( sample, 5.0 );
  TEST_EQUALITY_CONST( raw_sample, 5.0 );

  functor = getFunctor();
  sample = Utility::Correlated::sampleDetailed<Utility::LinLinLin,double,double>(
      functor, raw_sample, sampled_bin, lower_bin, upper_bin, 0.0, 0.0, 10.0 );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 0u );
  TEST_FLOATING_EQUALITY( sample, 10.0, 1e-14 );
  TEST_FLOATING_EQUALITY( raw_sample, 10.0, 1e-14 );

  // In the first bin
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.4230769230769231;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  functor = getFunctor();
  sample = Utility::Correlated::sampleDetailed<Utility::LinLinLin,double,double>(
    functor, raw_sample, sampled_bin, lower_bin, upper_bin, 0.5, 1.25, 8.75 );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 0u );
  TEST_EQUALITY_CONST( sample, 1.25 );
  TEST_EQUALITY_CONST( raw_sample, 1.25 );

  functor = getFunctor();
  sample = Utility::Correlated::sampleDetailed<Utility::LinLinLin,double,double>(
    functor, raw_sample, sampled_bin, lower_bin, upper_bin, 0.5, 1.25, 8.75 );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 0u );
  TEST_FLOATING_EQUALITY( sample, 4.7115384615384617, 1e-14 );
  TEST_FLOATING_EQUALITY( raw_sample, 4.7115384615384617, 1e-14 );

  functor = getFunctor();
  sample = Utility::Correlated::sampleDetailed<Utility::LinLinLin,double,double>(
    functor, raw_sample, sampled_bin, lower_bin, upper_bin, 0.5, 1.25, 8.75 );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 0u );
  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-14 );
  TEST_FLOATING_EQUALITY( raw_sample, 8.75, 1e-14 );

  // On the second bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  functor = getFunctor();
  sample = Utility::Correlated::sampleDetailed<Utility::LinLinLin,double,double>(
    functor, raw_sample, sampled_bin, lower_bin, upper_bin, 1.0, 2.5, 7.5 );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  TEST_EQUALITY_CONST( sample, 2.5 );
  TEST_EQUALITY_CONST( raw_sample, 2.5 );

  functor = getFunctor();
  sample = Utility::Correlated::sampleDetailed<Utility::LinLinLin,double,double>(
    functor, raw_sample, sampled_bin, lower_bin, upper_bin, 1.0, 2.5, 7.5 );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  TEST_FLOATING_EQUALITY( sample, 5.0, 1e-15 );
  TEST_FLOATING_EQUALITY( raw_sample, 5.0, 1e-15 );

  functor = getFunctor();
  sample = Utility::Correlated::sampleDetailed<Utility::LinLinLin,double,double>(
    functor, raw_sample, sampled_bin, lower_bin, upper_bin, 1.0, 2.5, 7.5 );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  TEST_FLOATING_EQUALITY( sample, 7.5, 1e-15 );
  TEST_FLOATING_EQUALITY( raw_sample, 7.5, 1e-15 );

  // In the second bin
  ++lower_bin; ++upper_bin;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  functor = getFunctor();
  sample = Utility::Correlated::sampleDetailed<Utility::LinLinLin,double,double>(
    functor, raw_sample, sampled_bin, lower_bin, upper_bin, 1.5, 1.25, 8.75 );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  TEST_EQUALITY_CONST( sample, 1.25 );
  TEST_EQUALITY_CONST( raw_sample, 1.25 );

  functor = getFunctor();
  sample = Utility::Correlated::sampleDetailed<Utility::LinLinLin,double,double>(
    functor, raw_sample, sampled_bin, lower_bin, upper_bin, 1.5, 1.25, 8.75 );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  TEST_FLOATING_EQUALITY( sample, 4.7115384615384617, 1e-15 );
  TEST_FLOATING_EQUALITY( raw_sample, 4.7115384615384617, 1e-15 );

  functor = getFunctor();
  sample = Utility::Correlated::sampleDetailed<Utility::LinLinLin,double,double>(
    functor, raw_sample, sampled_bin, lower_bin, upper_bin, 1.5, 1.25, 8.75 );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  TEST_FLOATING_EQUALITY( sample, 8.75, 1e-14 );
  TEST_FLOATING_EQUALITY( raw_sample, 8.75, 1e-14 );

  // On the upper bin boundary
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  functor = getFunctor();
  sample = Utility::Correlated::sampleDetailed<Utility::LinLinLin,double,double>(
    functor, raw_sample, sampled_bin, lower_bin, upper_bin, 2.0, 0.0, 10.0 );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 2u );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( raw_sample, 0.0 );

  functor = getFunctor();
  sample = Utility::Correlated::sampleDetailed<Utility::LinLinLin,double,double>(
    functor, raw_sample, sampled_bin, lower_bin, upper_bin, 2.0, 0.0, 10.0 );

  bin_index = std::distance( start_bin, sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 2u );
  TEST_EQUALITY_CONST( sample, 5.0 );
  TEST_EQUALITY_CONST( raw_sample, 5.0 );

  functor = getFunctor();
  sample = Utility::Correlated::sampleDetailed<Utility::LinLinLin,double,double>(
    functor, raw_sample, sampled_bin, lower_bin, upper_bin, 2.0, 0.0, 10.0 );

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
  // On the first bin
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned bin_index;
  quantity<cgs::length> raw_sample;
  ua_start_bin = unit_aware_distribution->begin();
  ua_lower_bin = ua_start_bin;
  ua_upper_bin = ua_lower_bin;
  ++ua_upper_bin;

  ua_functor = getUnitAwareFunctor();
  quantity<cgs::length> sample =
    Utility::Correlated::sampleDetailed<Utility::LinLinLin,XIndepType,YIndepType>(
      ua_functor, raw_sample, ua_sampled_bin, ua_lower_bin, ua_upper_bin, 0.0*MeV, 0.0*cgs::centimeter, 10.0*cgs::centimeter );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 0u );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 0.0*cgs::centimeter );

  ua_functor = getUnitAwareFunctor();
  sample = Utility::Correlated::sampleDetailed<Utility::LinLinLin,XIndepType,YIndepType>(
    ua_functor, raw_sample, ua_sampled_bin, ua_lower_bin, ua_upper_bin, 0.0*MeV, 0.0*cgs::centimeter, 10.0*cgs::centimeter );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 0u );
  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 5.0*cgs::centimeter );

  ua_functor = getUnitAwareFunctor();
  sample = Utility::Correlated::sampleDetailed<Utility::LinLinLin,XIndepType,YIndepType>(
    ua_functor, raw_sample, ua_sampled_bin, ua_lower_bin, ua_upper_bin, 0.0*MeV, 0.0*cgs::centimeter, 10.0*cgs::centimeter );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 0u );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*cgs::centimeter, 1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 10.0*cgs::centimeter, 1e-14 );

  // In the first bin
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.4230769230769231;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  ua_functor = getUnitAwareFunctor();
  sample = Utility::Correlated::sampleDetailed<Utility::LinLinLin,XIndepType,YIndepType>(
    ua_functor, raw_sample, ua_sampled_bin, ua_lower_bin, ua_upper_bin, 0.5*MeV, 1.25*cgs::centimeter, 8.75*cgs::centimeter );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 0u );
  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 1.25*cgs::centimeter );

  ua_functor = getUnitAwareFunctor();
  sample = Utility::Correlated::sampleDetailed<Utility::LinLinLin,XIndepType,YIndepType>(
    ua_functor, raw_sample, ua_sampled_bin, ua_lower_bin, ua_upper_bin, 0.5*MeV, 1.25*cgs::centimeter, 8.75*cgs::centimeter );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 0u );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 4.7115384615384617*cgs::centimeter, 1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 4.7115384615384617*cgs::centimeter, 1e-14 );

  ua_functor = getUnitAwareFunctor();
  sample = Utility::Correlated::sampleDetailed<Utility::LinLinLin,XIndepType,YIndepType>(
    ua_functor, raw_sample, ua_sampled_bin, ua_lower_bin, ua_upper_bin, 0.5*MeV, 1.25*cgs::centimeter, 8.75*cgs::centimeter );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 0u );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 8.75*cgs::centimeter, 1e-14 );

  // On the second bin
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  ua_functor = getUnitAwareFunctor();
  sample = Utility::Correlated::sampleDetailed<Utility::LinLinLin,XIndepType,YIndepType>(
    ua_functor, raw_sample, ua_sampled_bin, ua_lower_bin, ua_upper_bin, 1.0*MeV, 2.5*cgs::centimeter, 7.5*cgs::centimeter );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  TEST_EQUALITY_CONST( sample, 2.5*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 2.5*cgs::centimeter );

  ua_functor = getUnitAwareFunctor();
  sample = Utility::Correlated::sampleDetailed<Utility::LinLinLin,XIndepType,YIndepType>(
    ua_functor, raw_sample, ua_sampled_bin, ua_lower_bin, ua_upper_bin, 1.0*MeV, 2.5*cgs::centimeter, 7.5*cgs::centimeter );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*cgs::centimeter, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 5.0*cgs::centimeter, 1e-15 );

  ua_functor = getUnitAwareFunctor();
  sample = Utility::Correlated::sampleDetailed<Utility::LinLinLin,XIndepType,YIndepType>(
    ua_functor, raw_sample, ua_sampled_bin, ua_lower_bin, ua_upper_bin, 1.0*MeV, 2.5*cgs::centimeter, 7.5*cgs::centimeter );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 7.5*cgs::centimeter, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 7.5*cgs::centimeter, 1e-15 );

  // In the second bin
  ++ua_lower_bin; ++ua_upper_bin;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  ua_functor = getUnitAwareFunctor();
  sample = Utility::Correlated::sampleDetailed<Utility::LinLinLin,XIndepType,YIndepType>(
    ua_functor, raw_sample, ua_sampled_bin, ua_lower_bin, ua_upper_bin, 1.5*MeV, 1.25*cgs::centimeter, 8.75*cgs::centimeter );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  TEST_EQUALITY_CONST( sample, 1.25*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 1.25*cgs::centimeter );

  ua_functor = getUnitAwareFunctor();
  sample = Utility::Correlated::sampleDetailed<Utility::LinLinLin,XIndepType,YIndepType>(
    ua_functor, raw_sample, ua_sampled_bin, ua_lower_bin, ua_upper_bin, 1.5*MeV, 1.25*cgs::centimeter, 8.75*cgs::centimeter );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 4.7115384615384617*cgs::centimeter, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 4.7115384615384617*cgs::centimeter, 1e-15 );

  ua_functor = getUnitAwareFunctor();
  sample = Utility::Correlated::sampleDetailed<Utility::LinLinLin,XIndepType,YIndepType>(
    ua_functor, raw_sample, ua_sampled_bin, ua_lower_bin, ua_upper_bin, 1.5*MeV, 1.25*cgs::centimeter, 8.75*cgs::centimeter );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 1u );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 8.75*cgs::centimeter, 1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_sample, 8.75*cgs::centimeter, 1e-14 );

  // On the upper bin boundary
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0-1e-15;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  ua_functor = getUnitAwareFunctor();
  sample = Utility::Correlated::sampleDetailed<Utility::LinLinLin,XIndepType,YIndepType>(
    ua_functor, raw_sample, ua_sampled_bin, ua_lower_bin, ua_upper_bin, 2.0*MeV, 0.0*cgs::centimeter, 10.0*cgs::centimeter );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 2u );
  TEST_EQUALITY_CONST( sample, 0.0*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 0.0*cgs::centimeter );

  ua_functor = getUnitAwareFunctor();
  sample = Utility::Correlated::sampleDetailed<Utility::LinLinLin,XIndepType,YIndepType>(
    ua_functor, raw_sample, ua_sampled_bin, ua_lower_bin, ua_upper_bin, 2.0*MeV, 0.0*cgs::centimeter, 10.0*cgs::centimeter );

  bin_index = std::distance( ua_start_bin, ua_sampled_bin );
  TEST_EQUALITY_CONST( bin_index, 2u );
  TEST_EQUALITY_CONST( sample, 5.0*cgs::centimeter );
  TEST_EQUALITY_CONST( raw_sample, 5.0*cgs::centimeter );

  ua_functor = getUnitAwareFunctor();
  sample = Utility::Correlated::sampleDetailed<Utility::LinLinLin,XIndepType,YIndepType>(
    ua_functor, raw_sample, ua_sampled_bin, ua_lower_bin, ua_upper_bin, 2.0*MeV, 0.0*cgs::centimeter, 10.0*cgs::centimeter );

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
    distribution_data[2].second = distribution_data[0].second;

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
    distribution_data[2].second = distribution_data[0].second;

    unit_aware_distribution.reset(
        new Utility::UnitAwareFullyTabularTwoDDistribution<MegaElectronVolt,cgs::length,Barn>::DistributionType(
                                                        distribution_data ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstLinLinLinInterpolatedFullyTabularTwoDDistribution.cpp
//---------------------------------------------------------------------------//
