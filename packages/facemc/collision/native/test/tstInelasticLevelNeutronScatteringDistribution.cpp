//---------------------------------------------------------------------------//
//!
//! \file   tstInelasticLevelNeutronScatteringDistribution.cpp
//! \author Alex Bennett
//! \brief  Inelastic level neutron scattering distribution unit tests
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Facemc_UnitTestHarnessExtensions.hpp"
#include "Facemc_InelasticLevelNeutronScatteringDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
void initializeScatteringDistribution( 
  const double atomic_weight_ratio,
  Teuchos::RCP<Facemc::NeutronScatteringDistribution>& scattering_dist )
{
  Teuchos::RCP<Utility::OneDDistribution> delta_dist( 
			  new Utility::DeltaDistribution( 0.0 ) );
  
  Teuchos::Array<Utility::Pair<double,
			       Teuchos::RCP<Utility::OneDDistribution> > >
    raw_scattering_distribution( 2 );

  raw_scattering_distribution[0].first = 1e-11;
  raw_scattering_distribution[0].second = delta_dist;
  raw_scattering_distribution[1].first = 2e1;
  raw_scattering_distribution[1].second = delta_dist;

  Teuchos::RCP<Facemc::NeutronScatteringAngularDistribution> angular_dist(
                             new Facemc::NeutronScatteringAngularDistribution(
					       raw_scattering_distribution ) );
  // Q value is 1 and A is 1
  // param_a = (A + 1)/A * |Q| = 2.0
  // param_b = (A/(A + 1)^2 = 0.25
  scattering_dist.reset( new Facemc::InelasticLevelNeutronScatteringDistribution( 
					                   atomic_weight_ratio,
							   2.0,
							   0.25,
							   angular_dist ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an incoming neutron can be scattered
TEUCHOS_UNIT_TEST( InelasticLevelNeutronScatteringDistribution, 
		   scatterNeutron_hydrogen )
{
  Teuchos::RCP<Facemc::NeutronScatteringDistribution> scattering_dist;
  
  initializeScatteringDistribution( 1.0, scattering_dist );
  
  Facemc::NeutronState neutron( 0ull );
  neutron.setDirection( 0.0, 0.0, 1.0 );
  double start_energy = 3.0;
  neutron.setEnergy( start_energy );

  scattering_dist->scatterNeutron( neutron, 2.53010e-8 );

  TEST_FLOATING_EQUALITY( neutron.getEnergy(), 1.0, 1e-15);

  start_energy = 5.0;
  neutron.setEnergy( start_energy );

  scattering_dist->scatterNeutron( neutron, 2.53010e-8 );

  TEST_FLOATING_EQUALITY( neutron.getEnergy(), 2.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// tstInelasticLevelNeutronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
