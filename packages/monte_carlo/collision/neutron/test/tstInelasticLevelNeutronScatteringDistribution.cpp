//---------------------------------------------------------------------------//
//!
//! \file   tstInelasticLevelNeutronScatteringDistribution.cpp
//! \author Alex Bennett
//! \brief  Inelastic level neutron scattering distribution unit tests
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_IndependentEnergyAngleNuclearScatteringDistribution.hpp"
#include "MonteCarlo_AceLaw3NuclearScatteringEnergyDistribution.hpp"
#include "MonteCarlo_LabSystemConversionPolicy.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
void initializeScatteringDistribution(
  const double atomic_weight_ratio,
  std::shared_ptr<MonteCarlo::NuclearScatteringDistribution<MonteCarlo::NeutronState,MonteCarlo::NeutronState> >& scattering_dist )
{
  std::shared_ptr<Utility::TabularUnivariateDistribution> delta_dist(
			  new Utility::DeltaDistribution( 0.0 ) );

  std::vector<std::pair<double,std::shared_ptr<const Utility::TabularUnivariateDistribution> > >
    raw_scattering_distribution( 2 );

  raw_scattering_distribution[0].first = 1e-11;
  raw_scattering_distribution[0].second = delta_dist;
  raw_scattering_distribution[1].first = 2e1;
  raw_scattering_distribution[1].second = delta_dist;

  std::shared_ptr<MonteCarlo::NuclearScatteringAngularDistribution> angular_dist(
                         new MonteCarlo::NuclearScatteringAngularDistribution(
					       raw_scattering_distribution ) );

  // Q value is 1 and A is 1
  // param_a = (A + 1)/A * |Q| = 2.0
  // param_b = (A/(A + 1)^2 = 0.25
  std::shared_ptr<MonteCarlo::NuclearScatteringEnergyDistribution> energy_dist(
       new MonteCarlo::AceLaw3NuclearScatteringEnergyDistribution( 6.516454, 0.8848775 ) );

  scattering_dist.reset(
    new MonteCarlo::IndependentEnergyAngleNuclearScatteringDistribution<MonteCarlo::NeutronState,MonteCarlo::NeutronState,MonteCarlo::CMSystemConversionPolicy>(
					                   atomic_weight_ratio,
							   energy_dist,
							   angular_dist ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an incoming neutron can be scattered
FRENSIE_UNIT_TEST( InelasticLevelNeutronScatteringDistribution,
		   scatterParticle_hydrogen )
{
  std::shared_ptr<MonteCarlo::NuclearScatteringDistribution<MonteCarlo::NeutronState,MonteCarlo::NeutronState> > scattering_dist;

  initializeScatteringDistribution( 15.857510, scattering_dist );

  MonteCarlo::NeutronState neutron( 0ull );
  double initial_angle[3];
  initial_angle[0] = 0.0;
  initial_angle[1] = 0.0;
  initial_angle[2] = 1.0;
  neutron.setDirection( initial_angle );
  double start_energy = 7.0;
  neutron.setEnergy( start_energy );

  scattering_dist->scatterParticle( neutron, 2.53010e-8 );

  FRENSIE_CHECK_FLOATING_EQUALITY( neutron.getEnergy(), 0.452512, 1e-6);

  double angle = Utility::calculateCosineOfAngleBetweenVectors(
					      initial_angle,
					      neutron.getDirection() );
  FRENSIE_CHECK_FLOATING_EQUALITY( angle, 0.233314, 1e-6);

//  start_energy = 5.0;
//  neutron.setEnergy( start_energy );
//
//  scattering_dist->scatterParticle( neutron, 2.53010e-8 );
//
//  FRENSIE_CHECK_FLOATING_EQUALITY( neutron.getEnergy(), 2.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// tstInelasticLevelNeutronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
