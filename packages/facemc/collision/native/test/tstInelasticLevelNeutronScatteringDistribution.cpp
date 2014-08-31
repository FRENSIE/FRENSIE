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
#include "Facemc_IndependentEnergyAngleNeutronScatteringDistribution.hpp"
#include "Facemc_AceLaw3NeutronScatteringEnergyDistribution.hpp"
#include "Facemc_LabSystemConversionPolicy.hpp"
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
  Teuchos::RCP<Facemc::NeutronScatteringEnergyDistribution> energy_dist( 
       new Facemc::AceLaw3NeutronScatteringEnergyDistribution( 6.516454, 0.8848775 ) );
  
  scattering_dist.reset( 
   new Facemc::IndependentEnergyAngleNeutronScatteringDistribution<Facemc::CMSystemConversionPolicy>( 
					                   atomic_weight_ratio,
							   energy_dist, 
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
  
  initializeScatteringDistribution( 15.857510, scattering_dist );
  
  Facemc::NeutronState neutron( 0ull );
  double initial_angle[3];
  initial_angle[0] = 0.0;
  initial_angle[1] = 0.0;
  initial_angle[2] = 1.0;
  neutron.setDirection( initial_angle );
  double start_energy = 7.0;
  neutron.setEnergy( start_energy );

  scattering_dist->scatterNeutron( neutron, 2.53010e-8 );

  TEST_FLOATING_EQUALITY( neutron.getEnergy(), 0.452512, 1e-6);

  double angle = Utility::calculateCosineOfAngleBetweenVectors( 
					      initial_angle, 
					      neutron.getDirection() );
  TEST_FLOATING_EQUALITY( angle, 0.233314, 1e-6);

//  start_energy = 5.0;
//  neutron.setEnergy( start_energy );
//
//  scattering_dist->scatterNeutron( neutron, 2.53010e-8 );
//
//  TEST_FLOATING_EQUALITY( neutron.getEnergy(), 2.0, 1e-15 );
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
// tstInelasticLevelNeutronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
