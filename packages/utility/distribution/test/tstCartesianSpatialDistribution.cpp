//---------------------------------------------------------------------------//
//!
//! \file   tstCartesianSpatialDistribution.cpp
//! \author Alex Robinson
//! \brief  Cartesian spatial distribution unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_OneDDistribution.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_SpatialDistribution.hpp"
#include "Utility_CartesianSpatialDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"

std::shared_ptr<Utility::SpatialDistribution> spatial_distribution;

//---------------------------------------------------------------------------//
// Testing Functions
//---------------------------------------------------------------------------//
// Initialize the distribution
void initializeDistribution(
		      std::shared_ptr<Utility::SpatialDistribution>& distribution )
{
  // Delta distribution in x dimension
  std::shared_ptr<Utility::OneDDistribution> 
    x_distribution( new Utility::DeltaDistribution( 1.0 ) );

  // Uniform distribution in y dimension
  std::shared_ptr<Utility::OneDDistribution>
    y_distribution( new Utility::UniformDistribution( 0.0, 2.0, 0.5 ) );

  // Uniform distribution in z dimension
  std::shared_ptr<Utility::OneDDistribution>
    z_distribution( new Utility::UniformDistribution( 0.0, 2.0, 0.5 ) );

  distribution.reset( new Utility::CartesianSpatialDistribution( 
							    x_distribution,
							    y_distribution,
							    z_distribution ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( CartesianSpatialDistribution, evaluate )
{
  initializeDistribution( spatial_distribution );

  double point[3] = {0.0, 0.0, 0.0};
  TEST_EQUALITY_CONST( spatial_distribution->evaluate( point ), 0.0 );

  point[0] = 1.0;
  point[1] = 1.0;
  point[2] = 1.0;
  TEST_EQUALITY_CONST( spatial_distribution->evaluate( point ), 0.25 );

  point[0] = 1.0;
  point[1] = 3.0;
  point[2] = 3.0;
  TEST_EQUALITY_CONST( spatial_distribution->evaluate( point ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( CartesianSpatialDistribution, evaluatePDF )
{
  double point[3] = {0.0, 0.0, 0.0};
  TEST_EQUALITY_CONST( spatial_distribution->evaluatePDF( point ), 0.0 );

  point[0] = 1.0;
  point[1] = 1.0;
  point[2] = 1.0;
  TEST_EQUALITY_CONST( spatial_distribution->evaluatePDF( point ), 0.25 );

  point[0] = 1.0;
  point[1] = 3.0;
  point[2] = 3.0;
  TEST_EQUALITY_CONST( spatial_distribution->evaluatePDF( point ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribuiton can be sampled from
TEUCHOS_UNIT_TEST( CartesianSpatialDistribution, sample )
{
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5;
  fake_stream[3] = 0.5;
  fake_stream[4] = 1.0 - 1e-15;
  fake_stream[5] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sampled_point[3] = {0.0, 0.0, 0.0};

  spatial_distribution->sample( sampled_point );
  TEST_EQUALITY_CONST( sampled_point[0], 1.0 );
  TEST_EQUALITY_CONST( sampled_point[1], 0.0 );
  TEST_EQUALITY_CONST( sampled_point[2], 0.0 );

  spatial_distribution->sample( sampled_point );
  TEST_EQUALITY_CONST( sampled_point[0], 1.0 );
  TEST_EQUALITY_CONST( sampled_point[1], 1.0 );
  TEST_EQUALITY_CONST( sampled_point[2], 1.0 );
  
  spatial_distribution->sample( sampled_point );
  TEST_EQUALITY_CONST( sampled_point[0], 1.0 );
  TEST_FLOATING_EQUALITY( sampled_point[1], 2.0, 1e-15 );
  TEST_FLOATING_EQUALITY( sampled_point[2], 2.0, 1e-15 );
  
  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the correct distribution type is returned
TEUCHOS_UNIT_TEST( CartesianSpatialDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( spatial_distribution->getDistributionType(),
		       Utility::CARTESIAN_SPATIAL_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that distribution can be tested for uniformity
TEUCHOS_UNIT_TEST( CartesianSpatialDistribution, isUniform )
{
  TEST_ASSERT( !spatial_distribution->isUniform() );
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
// end tstCartesianSpatialDistribution.cpp
//---------------------------------------------------------------------------//
