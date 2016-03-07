//---------------------------------------------------------------------------//
//!
//! \file   tstSphericalSpatialDistribution.cpp
//! \author Alex Robinson
//! \brief  Spherical spatial distribution unit tests.
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
#include "Utility_PowerDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_SpatialDistribution.hpp"
#include "Utility_SphericalSpatialDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_RandomNumberGenerator.hpp"

std::shared_ptr<Utility::SpatialDistribution> spatial_distribution;

//---------------------------------------------------------------------------//
// Testing Functions
//---------------------------------------------------------------------------//
// Initialize the distribution
void initializeDistribution( 
		  std::shared_ptr<Utility::SpatialDistribution>& distribution )
{
  // Power distribution in r dimension
  std::shared_ptr<Utility::OneDDistribution>
    r_distribution( new Utility::PowerDistribution<2u>( 3.0, 0.0, 1.0 ) );

  // Uniform distribution in theta dimension
  std::shared_ptr<Utility::OneDDistribution>
    theta_distribution( new Utility::UniformDistribution( 
					       0.0, 
					       2*Utility::PhysicalConstants::pi,
					       1.0 ) );

  // Uniform distribution in mu dimension
  std::shared_ptr<Utility::OneDDistribution>
    mu_distribution( new Utility::UniformDistribution( -1.0, 1.0, 1.0 ) );

  distribution.reset( new Utility::SphericalSpatialDistribution( 
							   r_distribution,
							   theta_distribution,
							   mu_distribution,
							   1.0,
							   1.0,
							   1.0 ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( SphericalSpatialDistribution, evaluate )
{
  initializeDistribution( spatial_distribution );

  double cartesian_point[3] = {1.0, 1.0, 1.0};
  TEST_EQUALITY_CONST( spatial_distribution->evaluate( cartesian_point ), 3.0);
  
  cartesian_point[2] = 2.0;
  TEST_EQUALITY_CONST( spatial_distribution->evaluate( cartesian_point ), 3.0);

  cartesian_point[1] = 2.0;
  cartesian_point[2] = 1.0;
  TEST_EQUALITY_CONST( spatial_distribution->evaluate( cartesian_point ), 3.0);

  cartesian_point[0] = 2.0;
  cartesian_point[1] = 1.0;
  TEST_EQUALITY_CONST( spatial_distribution->evaluate( cartesian_point ), 3.0);

  cartesian_point[0] = 1.0/sqrt(3.0)+1;
  cartesian_point[1] = 1.0/sqrt(3.0)+1;
  cartesian_point[2] = 1.0/sqrt(3.0)+1;
  TEST_EQUALITY_CONST( spatial_distribution->evaluate( cartesian_point ), 3.0);

  cartesian_point[0] = -1.0/sqrt(3.0)+1;
  cartesian_point[1] = -1.0/sqrt(3.0)+1;
  cartesian_point[2] = -1.0/sqrt(3.0)+1;
  TEST_EQUALITY_CONST( spatial_distribution->evaluate( cartesian_point ), 3.0);

  cartesian_point[0] = 1.0;
  cartesian_point[2] = 3.0;
  TEST_EQUALITY_CONST( spatial_distribution->evaluate( cartesian_point ), 0.0);
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( SphericalSpatialDistribution, evaluatePDF )
{
  double pdf_value = 3.0/(Utility::PhysicalConstants::pi*4);

  double cartesian_point[3] = {1.0, 1.0, 1.0};
  TEST_EQUALITY_CONST( spatial_distribution->evaluatePDF( cartesian_point ), 
		       0.0);
  
  cartesian_point[2] = 2.0;
  TEST_EQUALITY_CONST( spatial_distribution->evaluatePDF( cartesian_point ), 
		       pdf_value );

  cartesian_point[1] = 2.0;
  cartesian_point[2] = 1.0;
  TEST_EQUALITY_CONST( spatial_distribution->evaluatePDF( cartesian_point ),
		       pdf_value );

  cartesian_point[0] = 2.0;
  cartesian_point[1] = 1.0;
  TEST_EQUALITY_CONST( spatial_distribution->evaluatePDF( cartesian_point ), 
		       pdf_value );

  cartesian_point[0] = 1.0/sqrt(3.0)+1;
  cartesian_point[1] = 1.0/sqrt(3.0)+1;
  cartesian_point[2] = 1.0/sqrt(3.0)+1;
  TEST_EQUALITY_CONST( spatial_distribution->evaluatePDF( cartesian_point ), 
		       pdf_value );

  cartesian_point[0] = -1.0/sqrt(3.0)+1;
  cartesian_point[1] = -1.0/sqrt(3.0)+1;
  cartesian_point[2] = -1.0/sqrt(3.0)+1;
  TEST_EQUALITY_CONST( spatial_distribution->evaluatePDF( cartesian_point ), 
		       pdf_value );

  cartesian_point[0] = 1.0;
  cartesian_point[2] = 3.0;
  TEST_EQUALITY_CONST( spatial_distribution->evaluatePDF( cartesian_point ), 
		       0.0);
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from
TEUCHOS_UNIT_TEST( SphericalSpatialDistribution, sample )
{
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.5;
  fake_stream[6] = 1.0 - 1e-15;
  fake_stream[7] = 1.0 - 1e-15;
  fake_stream[8] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sampled_point[3];

  spatial_distribution->sample( sampled_point );
  TEST_EQUALITY_CONST( sampled_point[0], 1.0 );
  TEST_EQUALITY_CONST( sampled_point[1], 1.0 );
  TEST_EQUALITY_CONST( sampled_point[2], 1.0 );

  spatial_distribution->sample( sampled_point );
  TEST_FLOATING_EQUALITY( sampled_point[0], 0.2062994740159, 1e-14 );
  TEST_EQUALITY_CONST( sampled_point[1], 1.0 );
  TEST_EQUALITY_CONST( sampled_point[2], 1.0 );

  spatial_distribution->sample( sampled_point );
  TEST_FLOATING_EQUALITY( sampled_point[0], 1.0, 1e-7 );
  TEST_FLOATING_EQUALITY( sampled_point[1], 1.0, 1e-15 );
  TEST_FLOATING_EQUALITY( sampled_point[2], 2.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the correct distribution type is returned
TEUCHOS_UNIT_TEST( SphericalSpatialDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( spatial_distribution->getDistributionType(),
		       Utility::SPHERICAL_SPATIAL_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that distribution can be tested for uniformity
TEUCHOS_UNIT_TEST( SphericalSpatialDistribution, isUniform )
{
  TEST_ASSERT( spatial_distribution->isUniform() );
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
// end tstSphericalSpatialDistribution.cpp
//---------------------------------------------------------------------------//

