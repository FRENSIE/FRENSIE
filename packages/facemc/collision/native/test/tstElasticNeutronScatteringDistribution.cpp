//---------------------------------------------------------------------------//
//!
//! \file   tstElasticNeutronScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  Elastic neutron scattering distribution unit tests
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Facemc_UnitTestHarnessExtensions.hpp"
#include "Facemc_ElasticNeutronScatteringDistribution.hpp"
#include "Facemc_NeutronScatteringAngularDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
void initializeScatteringDistribution( 
  const double atomic_weight_ratio,
  Teuchos::RCP<Facemc::NeutronScatteringDistribution>& scattering_dist )
{
  Teuchos::RCP<Utility::OneDDistribution> uniform_dist( 
			  new Utility::UniformDistribution( -1.0, 1.0, 0.5 ) );
  
  Teuchos::Array<Utility::Pair<double,
			       Teuchos::RCP<Utility::OneDDistribution> > >
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

  Teuchos::RCP<Facemc::NeutronScatteringAngularDistribution> angular_dist(
                             new Facemc::NeutronScatteringAngularDistribution(
					       raw_scattering_distribution ) );
  
  scattering_dist.reset( new Facemc::ElasticNeutronScatteringDistribution( 
					                   atomic_weight_ratio,
							   angular_dist ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an incoming neutron can be scattered
TEUCHOS_UNIT_TEST( ElasticNeutronScatteringDistribution, 
		   scatterNeutron_hydrogen )
{
  Teuchos::RCP<Facemc::NeutronScatteringDistribution> scattering_dist;
  
  initializeScatteringDistribution( 0.999167, scattering_dist );
  
  Facemc::NeutronState neutron( 0ull );
  neutron.setDirection( 0.0, 0.0, 1.0 );
  double start_energy = 1e-9;
  neutron.setEnergy( start_energy );
  
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.90; // go to second branch (alpha)
  fake_stream[1] = 0.1; // \
  fake_stream[2] = 0.5; // = sample y_2
  fake_stream[3] = 0.5; // /
  fake_stream[4] = 0.0; // sample mu_t
  fake_stream[5] = 0.7; // accept target speed and mu_t 
  fake_stream[6] = 0.0; // sample the azimuthal angle
  fake_stream[7] = 0.5; // sample from the lower cm angle distribution
  fake_stream[8] = 0.0; // sample a cm scattering angle of -1
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  std::cout << neutron << std::endl;

  scattering_dist->scatterNeutron( neutron, 2.53010e-8 );

  std::cout << neutron << std::endl;

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_COMPARE( neutron.getEnergy(), >, start_energy );
}

//---------------------------------------------------------------------------//
// tstElasticNeutronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
