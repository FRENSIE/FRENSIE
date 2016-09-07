//---------------------------------------------------------------------------//
//!
//! \file   tstInterpolatedPartiallyTabularTwoDDistribution.cpp
//! \author Alex Robinson
//! \brief  The interpolated partially tabular two-dimensional dist. unit tests
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
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_DynamicOutputFormatter.hpp"
#include "Utility_InterpolatedPartiallyTabularTwoDDistribution.hpp"
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
std::shared_ptr<Utility::UnitAwarePartiallyTabularTwoDDistribution<MegaElectronVolt,cgs::length,Barn> >
  unit_aware_distribution;

std::shared_ptr<Utility::PartiallyTabularTwoDDistribution> distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( InterpolatedPartiallyTabularTwoDDistribution, evaluate )
{
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0, 5.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0, 11.0 ), 0.0 );

  // Before the first bin - with extension
  distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0, 0.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0, 5.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0, 11.0 ), 0.0 );

  distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0, 0.0 ), 1.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0, 10.0 ), exp( -10.0 ) );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0, 11.0 ), 0.0 );

  // In the second bin
  TEST_EQUALITY_CONST( distribution->evaluate( 0.5, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( distribution->evaluate( 0.5, 0.0 ),
                          1.0,
                          1e-15 );
  TEST_FLOATING_EQUALITY( distribution->evaluate( 0.5, 5.0 ),
                          0.5033689734995427,
                          1e-15 );
  TEST_FLOATING_EQUALITY( distribution->evaluate( 0.5, 10.0 ),
                          0.5000226999648812,
                          1e-15 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.5, 11.0 ), 0.0 );

  // On the third bin boundary
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0, 0.0 ), 1.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0, 5.0 ), 1.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0, 10.0 ), 1.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0, 11.0 ), 0.0 );

  // In the third bin
  TEST_EQUALITY_CONST( distribution->evaluate( 1.5, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.5, 0.0 ), 0.55 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.5, 5.0 ), 0.55 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.5, 10.0 ), 0.55 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.5, 11.0 ), 0.0 );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( distribution->evaluate( 2.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 2.0, 0.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluate( 2.0, 5.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluate( 2.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluate( 2.0, 11.0 ), 0.0 );

  // After the third bin - no extension
  TEST_EQUALITY_CONST( distribution->evaluate( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 3.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 3.0, 5.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 3.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 3.0, 11.0 ), 0.0 );

  // After the third bin - with extension
  distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( distribution->evaluate( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 3.0, 0.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluate( 3.0, 5.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluate( 3.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluate( 3.0, 11.0 ), 0.0 );

  distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that the secondary conditional PDF can be evaluated
TEUCHOS_UNIT_TEST( InterpolatedPartiallyTabularTwoDDistribution,
                   evaluateSecondaryConditionalPDF )
{
  // Before the first bin - no extension
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( -1.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( -1.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( -1.0, 5.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( -1.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( -1.0, 11.0 ), 0.0 );

  // Before the first bin - with extension
  distribution->extendBeyondPrimaryIndepLimits();
  
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( -1.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( -1.0, 0.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( -1.0, 5.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( -1.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( -1.0, 11.0 ), 0.0 );

  distribution->limitToPrimaryIndepLimits();

  // On the second bin boundary
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 0.0, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( distribution->evaluateSecondaryConditionalPDF( 0.0, 0.0 ),
                          1.0000454019910097,
                          1e-15 );
  TEST_FLOATING_EQUALITY( distribution->evaluateSecondaryConditionalPDF( 0.0, 10.0 ),
                          4.540199100968777e-05,
                          1e-15 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 0.0, 11.0 ), 0.0 );

  // In the second bin
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 0.5, -1.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( distribution->evaluateSecondaryConditionalPDF( 0.5, 0.0 ),
                          0.5500227009955049,
                          1e-15 );
  TEST_FLOATING_EQUALITY( distribution->evaluateSecondaryConditionalPDF( 0.5, 5.0 ),
                          0.05336912645764728,
                          1e-15 );
  TEST_FLOATING_EQUALITY( distribution->evaluateSecondaryConditionalPDF( 0.5, 10.0 ),
                          0.05002270099550485,
                          1e-15 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 0.5, 11.0 ), 0.0 );

  // On the third bin boundary
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 1.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 1.0, 0.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 1.0, 5.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 1.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 1.0, 11.0 ), 0.0 );

  // In the third bin
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 1.5, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 1.5, 0.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 1.5, 5.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 1.5, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 1.5, 11.0 ), 0.0 );

  // On the upper bin boundary
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 2.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 2.0, 0.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 2.0, 5.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 2.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 2.0, 11.0 ), 0.0 );

  // After the third bin - no extension
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 3.0, 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 3.0, 5.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 3.0, 10.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 3.0, 11.0 ), 0.0 );

  // After the third bin - with extension
  distribution->extendBeyondPrimaryIndepLimits();

  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 3.0, -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 3.0, 0.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 3.0, 5.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 3.0, 10.0 ), 0.1 );
  TEST_EQUALITY_CONST( distribution->evaluateSecondaryConditionalPDF( 3.0, 11.0 ), 0.0 );

  distribution->limitToPrimaryIndepLimits();
}

//---------------------------------------------------------------------------//
// Check that a secondary conditional PDF can be sampled
TEUCHOS_UNIT_TEST( InterpolatedPartiallyTabularTwoDDistribution,
                   sampleSecondaryConditional )
{
  // Before the first bin
  double sample = distribution->sampleSecondaryConditional( -1.0 );

  TEST_EQUALITY_CONST( sample, 0.0 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  std::ostringstream oss;
  
  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::fancyOStream(Teuchos::rcpFromRef(oss));

  int return_value = clp.parse(argc,argv);

  if( return_value != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL )
  {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
  }
  else
  {
    // Create the two-dimensional distribution
    {
      Utility::PartiallyTabularTwoDDistribution::DistributionType
        distribution_data( 4 );

      // Create the secondary distribution in the first bin
      distribution_data[0].first = 0.0;
      distribution_data[0].second.reset( new Utility::UniformDistribution( 0.0, 10.0, 0.1 ) );
    
      // Create the secondary distribution in the second bin
      distribution_data[1].first = 0.0;
      distribution_data[1].second.reset( new Utility::ExponentialDistribution( 1.0, 1.0, 0.0, 10.0 ) );

      // Create the secondary distribution in the third bin
      distribution_data[2].first = 1.0;
      distribution_data[2].second.reset( new Utility::UniformDistribution( 0.0, 10.0, 1.0 ) );
      
      // Create the secondary distribution beyond the third bin
      distribution_data[3].first = 2.0;
      distribution_data[3].second = distribution_data[0].second;
      
      distribution.reset( new Utility::InterpolatedPartiallyTabularTwoDDistribution<Utility::LinLinLin>(
                                                         distribution_data ) );
    }

    // Create the unit-aware two-dimensional distribution
    {
      std::vector<quantity<MegaElectronVolt> > primary_bins( 4 );
      
      Teuchos::Array<std::shared_ptr<const Utility::UnitAwareOneDDistribution<cgs::length,Barn> > > secondary_dists( 4 );
      
      // Create the secondary distribution in the first bin
      primary_bins[0] = 0.0*MeV;
      secondary_dists[0].reset( new Utility::UnitAwareUniformDistribution<cgs::length,Barn>( 0.0*cgs::centimeter, 10.0*cgs::centimeter, 0.1*barn ) );
      
      // Create the secondary distribution in the second bin
      primary_bins[1] = 0.0*MeV;
      secondary_dists[1].reset( new Utility::UnitAwareExponentialDistribution<cgs::length,Barn>( 1.0*barn, 1.0/cgs::centimeter, 0.0*cgs::centimeter, 10.0*cgs::centimeter ) );
      
      // Create the secondary distribution in the third bin
      primary_bins[2] = 1.0*MeV;
      secondary_dists[2].reset( new Utility::UnitAwareUniformDistribution<cgs::length,Barn>( 0.0*cgs::centimeter, 10.0*cgs::centimeter, 1.0*barn ) );
      
      // Create the secondary distribution beyond the third bin
      primary_bins[3] = 2.0*MeV;
      secondary_dists[3] = secondary_dists[0];
      
      unit_aware_distribution.reset( new Utility::UnitAwareInterpolatedPartiallyTabularTwoDDistribution<Utility::LinLinLin,MegaElectronVolt,cgs::length,Barn>( primary_bins, secondary_dists ) );
    }

    // Initialize the random number generator
    Utility::RandomNumberGenerator::createStreams();
  
    // Run the unit tests
    Teuchos::GlobalMPISession mpiSession( &argc, &argv );
    
    const bool success = Teuchos::UnitTestRepository::runUnitTests(*out);

    if( success )
      *out << "\nEnd Result: TEST PASSED" << std::endl;
    else
      *out << "\nEnd Result: TEST FAILED" << std::endl;

    clp.printFinalTimerSummary(out.ptr());

    return_value = (success ? 0 : 1);
  }

  // Format the output
  Utility::DynamicOutputFormatter formatter( oss.str() );
  formatter.formatTeuchosUnitTestKeywords();  

  std::cout << formatter << std::endl;
  
  return return_value;
}

//---------------------------------------------------------------------------//
// end tstInterpolatedPartiallyTabularTwoDDistribution.cpp
//---------------------------------------------------------------------------//
