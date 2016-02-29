//---------------------------------------------------------------------------//
//!
//! \file   tstSphericalDirectionalDistribution.cpp
//! \author Alex Robinson
//! \brief  Spherical directional distribution unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Tuple.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_OneDDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_SphericalDirectionalDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_RandomNumberGenerator.hpp"

std::shared_ptr<Utility::DirectionalDistribution> directional_distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( SphericalDirectionalDistribution, evaluate )
{
  double cartesian_point[3] = {0.0, 0.0, 1.0};
  TEST_EQUALITY_CONST( directional_distribution->evaluate( cartesian_point ),
		       1.0 );

  cartesian_point[1] = 1.0;
  cartesian_point[2] = 0.0;
  TEST_EQUALITY_CONST( directional_distribution->evaluate( cartesian_point ),
		       1.0 );

  cartesian_point[0] = 1.0;
  cartesian_point[1] = 0.0;
  TEST_EQUALITY_CONST( directional_distribution->evaluate( cartesian_point ),
		       1.0 );

  cartesian_point[0] = 1.0/sqrt(3.0);
  cartesian_point[1] = 1.0/sqrt(3.0);
  cartesian_point[2] = 1.0/sqrt(3.0);
  TEST_EQUALITY_CONST( directional_distribution->evaluate( cartesian_point ),
		       1.0 );

  cartesian_point[0] = -1.0/sqrt(3.0);
  cartesian_point[1] = -1.0/sqrt(3.0);
  cartesian_point[2] = -1.0/sqrt(3.0);
  TEST_EQUALITY_CONST( directional_distribution->evaluate( cartesian_point ),
		       1.0 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( SphericalDirectionalDistribution, evaluatePDF )
{
  double pdf_value = 1.0/(Utility::PhysicalConstants::pi*4);

  double cartesian_point[3] = {0.0, 0.0, 1.0};
  TEST_EQUALITY_CONST( directional_distribution->evaluatePDF(cartesian_point),
		       pdf_value );

  cartesian_point[1] = 1.0;
  cartesian_point[2] = 0.0;
  TEST_EQUALITY_CONST( directional_distribution->evaluatePDF(cartesian_point),
		       pdf_value );

  cartesian_point[0] = 1.0;
  cartesian_point[1] = 0.0;
  TEST_EQUALITY_CONST( directional_distribution->evaluatePDF(cartesian_point),
		       pdf_value );

  cartesian_point[0] = 1.0/sqrt(3.0);
  cartesian_point[1] = 1.0/sqrt(3.0);
  cartesian_point[2] = 1.0/sqrt(3.0);
  TEST_EQUALITY_CONST( directional_distribution->evaluatePDF(cartesian_point),
		       pdf_value );

  cartesian_point[0] = -1.0/sqrt(3.0);
  cartesian_point[1] = -1.0/sqrt(3.0);
  cartesian_point[2] = -1.0/sqrt(3.0);
  TEST_EQUALITY_CONST( directional_distribution->evaluatePDF(cartesian_point),
		       pdf_value );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from
TEUCHOS_UNIT_TEST( SphericalDirectionalDistribution, sample )
{
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5;
  fake_stream[3] = 0.5;
  fake_stream[4] = 1.0 - 1e-15;
  fake_stream[5] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sampled_direction[3];

  directional_distribution->sample( sampled_direction );
  TEST_EQUALITY_CONST( sampled_direction[0], 0.0 );
  TEST_EQUALITY_CONST( sampled_direction[1], 0.0 );
  TEST_EQUALITY_CONST( sampled_direction[2], -1.0 );

  directional_distribution->sample( sampled_direction );
  TEST_EQUALITY_CONST( sampled_direction[0], -1.0 );
  UTILITY_TEST_FLOATING_EQUALITY( sampled_direction[1], 0.0, 1e-15 );
  TEST_EQUALITY_CONST( sampled_direction[2], 0.0 );

  directional_distribution->sample( sampled_direction );
  UTILITY_TEST_FLOATING_EQUALITY( sampled_direction[0], 0.0, 1e-7 );
  UTILITY_TEST_FLOATING_EQUALITY( sampled_direction[1], 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( sampled_direction[2], 1.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
TEUCHOS_UNIT_TEST( SphericalDirectionalDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( directional_distribution->getDistributionType(),
		       Utility::SPHERICAL_DIRECTIONAL_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the bounds of two distributions can be tested
TEUCHOS_UNIT_TEST( SphericalDirectionalDistribution, hasSameBounds )
{
  std::shared_ptr<Utility::OneDDistribution> theta_distribution( 
	    new Utility::UniformDistribution( 0.0,
					      2*Utility::PhysicalConstants::pi,
					      1.0 ) );

  std::shared_ptr<Utility::OneDDistribution> uniform_distribution( 
			  new Utility::UniformDistribution( -1.0, 1.0, 1.0 ) );
  
  std::shared_ptr<Utility::OneDDistribution> histogram_distribution(
	  new Utility::HistogramDistribution( Teuchos::tuple( -1.0, 0.0, 1.0 ),
					      Teuchos::tuple( 1.0, 1.0 ) ) );

  std::shared_ptr<Utility::OneDDistribution> discrete_distribution(
	     new Utility::DiscreteDistribution( Teuchos::tuple( 0.0, 1.0 ),
						Teuchos::tuple( 1.0, 1.0 ) ) );

  
  std::shared_ptr<Utility::DirectionalDistribution> directional_dist_a(
	   new Utility::SphericalDirectionalDistribution( theta_distribution,
							  uniform_distribution,
							  Utility::Y_AXIS ) );

  std::shared_ptr<Utility::DirectionalDistribution> directional_dist_b(
	   new Utility::SphericalDirectionalDistribution( theta_distribution,
							  uniform_distribution,
							  Utility::X_AXIS ) );

  std::shared_ptr<Utility::DirectionalDistribution> directional_dist_c(
	 new Utility::SphericalDirectionalDistribution( theta_distribution,
							histogram_distribution,
							Utility::Z_AXIS ) );

  std::shared_ptr<Utility::DirectionalDistribution> directional_dist_d(
	 new Utility::SphericalDirectionalDistribution( theta_distribution,
							discrete_distribution,
							Utility::Z_AXIS ) );

  TEST_ASSERT(!directional_distribution->hasSameBounds( *directional_dist_a ));
  TEST_ASSERT(!directional_distribution->hasSameBounds( *directional_dist_b ));
  TEST_ASSERT(directional_distribution->hasSameBounds( *directional_dist_c ));
  TEST_ASSERT(!directional_distribution->hasSameBounds( *directional_dist_d ));
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
  
  // Uniform distribution in theta dimension
  std::shared_ptr<Utility::OneDDistribution>
    theta_distribution( new Utility::UniformDistribution( 
					      0.0,
					      2*Utility::PhysicalConstants::pi,
					      1.0 ) );

  // Uniform distribution in mu dimension
  std::shared_ptr<Utility::OneDDistribution>
    mu_distribution( new Utility::UniformDistribution( -1.0, 1.0, 1.0 ) );

  directional_distribution.reset( new Utility::SphericalDirectionalDistribution(
							   theta_distribution,
							   mu_distribution ) );

  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );
}

//---------------------------------------------------------------------------//
// end tstDirectionalDistribution.cpp
//---------------------------------------------------------------------------//
