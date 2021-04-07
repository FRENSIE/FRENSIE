//---------------------------------------------------------------------------//
//!
//! \file   tstElasticNeutronScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  Elastic neutron scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_UnitTestHarnessExtensions.hpp"
#include "MonteCarlo_ElasticNeutronScatteringDistribution.hpp"
#include "MonteCarlo_NeutronScatteringAngularDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_DirectionHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
void initializeScatteringDistribution(
  const double atomic_weight_ratio,
  Teuchos::RCP<MonteCarlo::NeutronScatteringDistribution>& scattering_dist )
{
  Teuchos::RCP<Utility::OneDDistribution> uniform_dist(
			  new Utility::UniformDistribution( -1.0, 1.0, 0.5 ) );

  Teuchos::Array<Utility::Pair<double,
			       Teuchos::RCP<const Utility::OneDDistribution> > >
    raw_scattering_distribution( 5 );

  raw_scattering_distribution[0].first = 1e-11;
  raw_scattering_distribution[0].second = uniform_dist;
  raw_scattering_distribution[1].first = 1e-8;
  raw_scattering_distribution[1].second = uniform_dist;
  raw_scattering_distribution[2].first = 1e-5;
  raw_scattering_distribution[2].second = uniform_dist;
  raw_scattering_distribution[3].first = 1e-3;
  raw_scattering_distribution[3].second = uniform_dist;
  raw_scattering_distribution[4].first = 1.0;
  raw_scattering_distribution[4].second = uniform_dist;

  Teuchos::RCP<MonteCarlo::NeutronScatteringAngularDistribution> angular_dist(
                             new MonteCarlo::NeutronScatteringAngularDistribution(
					       raw_scattering_distribution ) );

  scattering_dist.reset( new MonteCarlo::ElasticNeutronScatteringDistribution(
					                   atomic_weight_ratio,
							   angular_dist ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an incoming neutron can be scattered
TEUCHOS_UNIT_TEST( ElasticNeutronScatteringDistribution,
		   scatterNeutron )
{
  Teuchos::RCP<MonteCarlo::NeutronScatteringDistribution> scattering_dist;

  initializeScatteringDistribution( 2.0, scattering_dist );

  MonteCarlo::NeutronState neutron( 0ull );
  double initial_angle[3];
  initial_angle[0] = 0.0;
  initial_angle[1] = 1.0;
  initial_angle[2] = 0.0;
  neutron.setDirection( initial_angle );
  double start_energy = 1.0;
  neutron.setEnergy( start_energy );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0; // go to second branch (alpha)
  fake_stream[1] = 0.0; // \

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  scattering_dist->scatterNeutron( neutron, 2.53010e-8 );

  double angle = Utility::calculateCosineOfAngleBetweenVectors(
					      initial_angle,
					      neutron.getDirection() );

  TEST_FLOATING_EQUALITY( neutron.getEnergy(),0.1111111, 1e-6);
  TEST_FLOATING_EQUALITY( angle, -1.0, 1e-6);

  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  neutron.setDirection( initial_angle );
  neutron.setEnergy( start_energy );

  scattering_dist->scatterNeutron( neutron, 2.53010e-8 );

  angle = Utility::calculateCosineOfAngleBetweenVectors(
					      initial_angle,
					      neutron.getDirection() );

  TEST_FLOATING_EQUALITY( neutron.getEnergy(),0.555556, 1e-6);
  TEST_FLOATING_EQUALITY( angle, 0.447214, 1e-6);

  fake_stream[0] = 0.99999999999;
  fake_stream[1] = 0.99999999999;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  neutron.setDirection( initial_angle );
  neutron.setEnergy( start_energy );

  scattering_dist->scatterNeutron( neutron, 2.53010e-8 );

  angle = Utility::calculateCosineOfAngleBetweenVectors(
					      initial_angle,
					      neutron.getDirection() );

  TEST_FLOATING_EQUALITY( neutron.getEnergy(),1.0, 1e-11);
  TEST_FLOATING_EQUALITY( angle, 1.0, 1e-11);
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();

  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );
}

//---------------------------------------------------------------------------//
// tstElasticNeutronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
