//---------------------------------------------------------------------------//
//!
//! \file   tstHistogramFullyTabularTwoDDistribution.cpp
//! \author Alex Robinson
//! \brief  The histogram fully tabular two-dimensional dist. unit tests
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
#include "Utility_HistogramFullyTabularTwoDDistribution.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
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

std::shared_ptr<Utility::UnitAwareFullyTabularTwoDDistribution<MegaElectronVolt,cgs::length,Barn> >
  unit_aware_tab_distribution;

std::shared_ptr<Utility::TwoDDistribution> distribution;

std::shared_ptr<Utility::FullyTabularTwoDDistribution> tab_distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( HistogramFullyTabularTwoDDistribution, evaluate )
{
  // Before the first bin
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0, 0.0 ), 1.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0, 1.0 ), 0.0 );

  // On the second bin (first bin boundary = second bin boundary)
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0, 0.0 ), 2.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0, 1.0 ), 2.0 );

  // In the second bin
  TEST_EQUALITY_CONST( distribution->evaluate( 0.5, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.5, 0.0 ), 2.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.5, 1.0 ), 2.0 );

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
TEUCHOS_UNIT_TEST( UnitAwareHistogramFullyTabularTwoDDistribution, evaluate )
{
  // Before the first bin
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( -1.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( -1.0*MeV, 0.0*cgs::centimeter ), 1.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( -1.0*MeV, 1.0*cgs::centimeter ), 0.0*barn );

  // On the second bin (first bin boundary = second bin boundary)
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*MeV, 0.0*cgs::centimeter ), 2.0*barns );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*MeV, 1.0*cgs::centimeter ), 2.0*barns );

  // In the second bin
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.5*MeV, -1.0*cgs::centimeter ), 0.0*barn );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.5*MeV, 0.0*cgs::centimeter ), 2.0*barns );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.5*MeV, 1.0*cgs::centimeter ), 2.0*barns );

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
    Utility::HistogramFullyTabularTwoDDistribution::DistributionType
      distribution_data( 4 );

    // Create the secondary distribution in the first bin
    distribution_data[0].first = 0.0;
    distribution_data[0].second.reset( new Utility::DeltaDistribution( 0.0 ) );
    

    // Create the secondary distribution in the second bin
    distribution_data[1].first = 0.0;
    distribution_data[1].second.reset( new Utility::UniformDistribution( 0.0, 10.0, 2.0 ) );

    // Create the secondary distribution in the third bin
    distribution_data[2].first = 1.0;
    distribution_data[2].second.reset( new Utility::UniformDistribution( 0.0, 10.0, 1.0 ) );

    // Create the secondary distribution beyond the third bin
    distribution_data[3].first = 2.0;
    distribution_data[3].second = distribution_data[0].second;

    tab_distribution.reset( new Utility::HistogramFullyTabularTwoDDistribution(
                                                         distribution_data ) );

    distribution = tab_distribution;
  }

  // Create the unit-aware two-dimensional distribution
  {
    std::vector<quantity<MegaElectronVolt> > primary_bins( 4 );

    Teuchos::Array<std::shared_ptr<const Utility::UnitAwareTabularOneDDistribution<cgs::length,Barn> > > secondary_dists( 4 );

    // Create the secondary distribution in the first bin
    primary_bins[0] = 0.0*MeV;
    secondary_dists[0].reset( new Utility::UnitAwareDeltaDistribution<cgs::length,Barn>( 0.0*cgs::centimeter ) );

    // Create the secondary distribution in the second bin
    primary_bins[1] = 0.0*MeV;
    secondary_dists[1].reset( new Utility::UnitAwareUniformDistribution<cgs::length,Barn>( 0.0*cgs::centimeter, 10.0*cgs::centimeter, 2.0*barn ) );

    // Create the secondary distribution in the third bin
    primary_bins[2] = 1.0*MeV;
    secondary_dists[2].reset( new Utility::UnitAwareUniformDistribution<cgs::length,Barn>( 0.0*cgs::centimeter, 10.0*cgs::centimeter, 1.0*barn ) );

    // Create the secondary distribution beyond the third bin
    primary_bins[3] = 2.0*MeV;
    secondary_dists[3] = secondary_dists[0];

    unit_aware_tab_distribution.reset( new Utility::UnitAwareHistogramFullyTabularTwoDDistribution<MegaElectronVolt,cgs::length,Barn>( primary_bins, secondary_dists ) );

    unit_aware_distribution = unit_aware_tab_distribution;
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
// end tstHistogramFullyTabularTwoDDistribution.hpp
//---------------------------------------------------------------------------//
