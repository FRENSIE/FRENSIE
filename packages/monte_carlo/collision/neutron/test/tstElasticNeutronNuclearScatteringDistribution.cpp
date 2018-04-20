//---------------------------------------------------------------------------//
//!
//! \file   tstElasticNeutronNuclearScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  Elastic neutron scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_ElasticNeutronNuclearScatteringDistribution.hpp"
#include "MonteCarlo_NuclearScatteringAngularDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Structs
//---------------------------------------------------------------------------//
class TestElasticNeutronScatteringDistribution : public MonteCarlo::ElasticNeutronNuclearScatteringDistribution
{
public:
  TestElasticNeutronScatteringDistribution(
	 const double atomic_weight_ratio,
         const double free_gas_threshold,
	 const std::shared_ptr<const MonteCarlo::NuclearScatteringAngularDistribution>&
	 angular_scattering_distribution )
    : MonteCarlo::ElasticNeutronNuclearScatteringDistribution(
					      atomic_weight_ratio,
                                              free_gas_threshold,
					      angular_scattering_distribution )
  { /* ... */ }

  ~TestElasticNeutronScatteringDistribution()
  { /* ... */ }

  // Allow public access to the protected member functions
  using MonteCarlo::ElasticNeutronNuclearScatteringDistribution::calculateCenterOfMassVelocity;
  using MonteCarlo::ElasticNeutronNuclearScatteringDistribution::transformVelocityToCenterOfMassFrame;
  using MonteCarlo::ElasticNeutronNuclearScatteringDistribution::transformVelocityToLabFrame;
  using MonteCarlo::ElasticNeutronNuclearScatteringDistribution::sampleTargetVelocity;
};

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
template<typename DistType>
void initializeScatteringDistribution(
  const double atomic_weight_ratio,
  std::shared_ptr<MonteCarlo::NuclearScatteringDistribution<MonteCarlo::NeutronState,MonteCarlo::NeutronState> >& scattering_dist )
{
  std::shared_ptr<Utility::TabularUnivariateDistribution> uniform_dist(
			  new Utility::UniformDistribution( -1.0, 1.0, 0.5 ) );

  std::vector<std::pair<double,std::shared_ptr<const Utility::TabularUnivariateDistribution> > >
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

  std::shared_ptr<MonteCarlo::NuclearScatteringAngularDistribution> angular_dist(
                         new MonteCarlo::NuclearScatteringAngularDistribution(
					       raw_scattering_distribution ) );

  scattering_dist.reset( new DistType( atomic_weight_ratio, 400, angular_dist ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the center of mass velocity can be calculated
FRENSIE_UNIT_TEST( ElasticNeutronNuclearScatteringDistribution,
		   calculateCenterOfMassVelocity )
{
  std::shared_ptr<MonteCarlo::NuclearScatteringDistribution<MonteCarlo::NeutronState,MonteCarlo::NeutronState> >
    base_distribution;

  initializeScatteringDistribution<TestElasticNeutronScatteringDistribution>(
						      2.0, base_distribution );

  std::shared_ptr<TestElasticNeutronScatteringDistribution>
    scattering_distribution = std::dynamic_pointer_cast<TestElasticNeutronScatteringDistribution>( base_distribution );

  std::vector<double> neutron_velocity( 3 );
  neutron_velocity[0] = 1.0;
  neutron_velocity[1] = 1.0;
  neutron_velocity[2] = 1.0;

  std::vector<double> target_velocity( 3 );
  target_velocity[0] = 1.0;
  target_velocity[1] = 1.0;
  target_velocity[2] = -1.0;

  std::vector<double> center_of_mass_velocity( 3 );

  scattering_distribution->calculateCenterOfMassVelocity(
					 neutron_velocity.data(),
					 target_velocity.data(),
					 center_of_mass_velocity.data() );

  std::vector<double> ref_center_of_mass_velocity( 3 );
  ref_center_of_mass_velocity[0] = 1.0;
  ref_center_of_mass_velocity[1] = 1.0;
  ref_center_of_mass_velocity[2] = -1.0/3.0;

  FRENSIE_CHECK_FLOATING_EQUALITY( center_of_mass_velocity,
				ref_center_of_mass_velocity,
				1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a lab velocity can be converted to a center-of-mass velocity
FRENSIE_UNIT_TEST( ElasticNeutronNuclearScatteringDistribution,
		   transformVelocityToCenterOfMassFrame )
{
  std::shared_ptr<MonteCarlo::NuclearScatteringDistribution<MonteCarlo::NeutronState,MonteCarlo::NeutronState> >
    base_distribution;

  initializeScatteringDistribution<TestElasticNeutronScatteringDistribution>(
						      2.0, base_distribution );

  std::shared_ptr<TestElasticNeutronScatteringDistribution>
    scattering_distribution = std::dynamic_pointer_cast<TestElasticNeutronScatteringDistribution>( base_distribution );

  std::vector<double> neutron_velocity( 3 );
  neutron_velocity[0] = 1.0;
  neutron_velocity[1] = 1.0;
  neutron_velocity[2] = 1.0;

  std::vector<double> center_of_mass_velocity( 3 );
  center_of_mass_velocity[0] = 1.0;
  center_of_mass_velocity[1] = 1.0;
  center_of_mass_velocity[2] = -1.0/3.0;

  scattering_distribution->transformVelocityToCenterOfMassFrame(
					   center_of_mass_velocity.data(),
					   neutron_velocity.data() );

  std::vector<double> cm_neutron_velocity( 3 );
  cm_neutron_velocity[0] = 0.0;
  cm_neutron_velocity[1] = 0.0;
  cm_neutron_velocity[2] = 4.0/3.0;

  FRENSIE_CHECK_FLOATING_EQUALITY( cm_neutron_velocity,
				neutron_velocity,
				1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a center-of-mass velocity can be converted to a lab velocity
FRENSIE_UNIT_TEST( ElasticNeutronNuclearScatteringDistribution,
		   transformVelocityToLabFrame )
{
  std::shared_ptr<MonteCarlo::NuclearScatteringDistribution<MonteCarlo::NeutronState,MonteCarlo::NeutronState> >
    base_distribution;

  initializeScatteringDistribution<TestElasticNeutronScatteringDistribution>(
						      2.0, base_distribution );

  std::shared_ptr<TestElasticNeutronScatteringDistribution>
    scattering_distribution = std::dynamic_pointer_cast<TestElasticNeutronScatteringDistribution>( base_distribution );

  std::vector<double> neutron_velocity( 3 );
  neutron_velocity[0] = 0.0;
  neutron_velocity[1] = 0.0;
  neutron_velocity[2] = 4.0/3.0;

  std::vector<double> center_of_mass_velocity( 3 );
  center_of_mass_velocity[0] = 1.0;
  center_of_mass_velocity[1] = 1.0;
  center_of_mass_velocity[2] = -1.0/3.0;

  scattering_distribution->transformVelocityToLabFrame(
					   center_of_mass_velocity.data(),
					   neutron_velocity.data() );

  std::vector<double> lab_neutron_velocity( 3 );
  lab_neutron_velocity[0] = 1.0;
  lab_neutron_velocity[1] = 1.0;
  lab_neutron_velocity[2] = 1.0;

  FRENSIE_CHECK_FLOATING_EQUALITY( lab_neutron_velocity,
                                   neutron_velocity,
                                   1e-15 );
}

//---------------------------------------------------------------------------//
// Check that an incoming neutron can be scattered
FRENSIE_UNIT_TEST( ElasticNeutronNuclearScatteringDistribution,
		   scatterNeutron )
{
  std::shared_ptr<MonteCarlo::NuclearScatteringDistribution<MonteCarlo::NeutronState,MonteCarlo::NeutronState> > scattering_dist;

  initializeScatteringDistribution<MonteCarlo::ElasticNeutronNuclearScatteringDistribution>( 2.0, scattering_dist );

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

  scattering_dist->scatterParticle( neutron, 2.53010e-8 );

  double angle = Utility::calculateCosineOfAngleBetweenVectors(
					      initial_angle,
					      neutron.getDirection() );

  FRENSIE_CHECK_FLOATING_EQUALITY( neutron.getEnergy(),0.1111111, 1e-6);
  FRENSIE_CHECK_FLOATING_EQUALITY( angle, -1.0, 1e-6);

  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  neutron.setDirection( initial_angle );
  neutron.setEnergy( start_energy );

  scattering_dist->scatterParticle( neutron, 2.53010e-8 );

  angle = Utility::calculateCosineOfAngleBetweenVectors(
					      initial_angle,
					      neutron.getDirection() );

  FRENSIE_CHECK_FLOATING_EQUALITY( neutron.getEnergy(),0.555556, 1e-6);
  FRENSIE_CHECK_FLOATING_EQUALITY( angle, 0.447214, 1e-6);

  fake_stream[0] = 0.99999999999;
  fake_stream[1] = 0.99999999999;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  neutron.setDirection( initial_angle );
  neutron.setEnergy( start_energy );

  scattering_dist->scatterParticle( neutron, 2.53010e-8 );

  angle = Utility::calculateCosineOfAngleBetweenVectors(
					      initial_angle,
					      neutron.getDirection() );

  FRENSIE_CHECK_FLOATING_EQUALITY( neutron.getEnergy(),1.0, 1e-11);
  FRENSIE_CHECK_FLOATING_EQUALITY( angle, 1.0, 1e-11);
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
// tstElasticNeutronNuclearScatteringDistribution.cpp
//---------------------------------------------------------------------------//
