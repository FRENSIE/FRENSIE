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
#include "MonteCarlo_ParticleScatteringAngularDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_DirectionHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Structs
//---------------------------------------------------------------------------//
class TestElasticNeutronScatteringDistribution : public MonteCarlo::ElasticNeutronScatteringDistribution
{
public:
  TestElasticNeutronScatteringDistribution( 
	 const double atomic_weight_ratio,
	 const Teuchos::RCP<MonteCarlo::ParticleScatteringAngularDistribution>&
	 angular_scattering_distribution )
    : MonteCarlo::ElasticNeutronScatteringDistribution( 
					      atomic_weight_ratio,
					      angular_scattering_distribution )
  { /* ... */ }

  ~TestElasticNeutronScatteringDistribution()
  { /* ... */ }

  void scatterNeutron( MonteCarlo::NeutronState& particle,
		       const double temperature ) const
  { /* ... */ }

  // Allow public access to the protected member functions
  using MonteCarlo::ElasticNeutronScatteringDistribution::calculateCenterOfMassVelocity;
  using MonteCarlo::ElasticNeutronScatteringDistribution::transformVelocityToCenterOfMassFrame;
  using MonteCarlo::ElasticNeutronScatteringDistribution::transformVelocityToLabFrame;
  using MonteCarlo::ElasticNeutronScatteringDistribution::sampleTargetVelocity;
};

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
template<typename DistType>
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

  Teuchos::RCP<MonteCarlo::ParticleScatteringAngularDistribution> angular_dist(
                         new MonteCarlo::ParticleScatteringAngularDistribution(
					       raw_scattering_distribution ) );
  
  scattering_dist.reset( new DistType( atomic_weight_ratio, angular_dist ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the center of mass velocity can be calculated
TEUCHOS_UNIT_TEST( ElasticNeutronScatteringDistribution, 
		   calculateCenterOfMassVelocity )
{
  Teuchos::RCP<MonteCarlo::NeutronScatteringDistribution>
    base_distribution;

  initializeScatteringDistribution<TestElasticNeutronScatteringDistribution>( 
						      2.0, base_distribution );

  Teuchos::RCP<TestElasticNeutronScatteringDistribution> 
    scattering_distribution = Teuchos::rcp_dynamic_cast<TestElasticNeutronScatteringDistribution>( base_distribution );
  
  Teuchos::Array<double> neutron_velocity( 3 );
  neutron_velocity[0] = 1.0;
  neutron_velocity[1] = 1.0;
  neutron_velocity[2] = 1.0;
  
  Teuchos::Array<double> target_velocity( 3 );
  target_velocity[0] = 1.0;
  target_velocity[1] = 1.0;
  target_velocity[2] = -1.0;
  
  Teuchos::Array<double> center_of_mass_velocity( 3 );

  scattering_distribution->calculateCenterOfMassVelocity( 
					 neutron_velocity.getRawPtr(),
					 target_velocity.getRawPtr(),
					 center_of_mass_velocity.getRawPtr() );

  Teuchos::Array<double> ref_center_of_mass_velocity( 3 );
  ref_center_of_mass_velocity[0] = 1.0;
  ref_center_of_mass_velocity[1] = 1.0;
  ref_center_of_mass_velocity[2] = -1.0/3.0;
  
  TEST_COMPARE_FLOATING_ARRAYS( center_of_mass_velocity,
				ref_center_of_mass_velocity,
				1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a lab velocity can be converted to a center-of-mass velocity
TEUCHOS_UNIT_TEST( ElasticNeutronScatteringDistribution, 
		   transformVelocityToCenterOfMassFrame )
{
  Teuchos::RCP<MonteCarlo::NeutronScatteringDistribution>
    base_distribution;

  initializeScatteringDistribution<TestElasticNeutronScatteringDistribution>( 
						      2.0, base_distribution );

  Teuchos::RCP<TestElasticNeutronScatteringDistribution> 
    scattering_distribution = Teuchos::rcp_dynamic_cast<TestElasticNeutronScatteringDistribution>( base_distribution );

  Teuchos::Array<double> neutron_velocity( 3 );
  neutron_velocity[0] = 1.0;
  neutron_velocity[1] = 1.0;
  neutron_velocity[2] = 1.0;
  
  Teuchos::Array<double> center_of_mass_velocity( 3 );
  center_of_mass_velocity[0] = 1.0;
  center_of_mass_velocity[1] = 1.0;
  center_of_mass_velocity[2] = -1.0/3.0;

  scattering_distribution->transformVelocityToCenterOfMassFrame( 
					   center_of_mass_velocity.getRawPtr(),
					   neutron_velocity.getRawPtr() );
  
  Teuchos::Array<double> cm_neutron_velocity( 3 );
  cm_neutron_velocity[0] = 0.0;
  cm_neutron_velocity[1] = 0.0;
  cm_neutron_velocity[2] = 4.0/3.0;

  TEST_COMPARE_FLOATING_ARRAYS( cm_neutron_velocity,
				neutron_velocity,
				1e-15 );				
}

//---------------------------------------------------------------------------//
// Check that a center-of-mass velocity can be converted to a lab velocity
TEUCHOS_UNIT_TEST( ElasticNeutronScatteringDistribution, 
		   transformVelocityToLabFrame )
{
  Teuchos::RCP<MonteCarlo::NeutronScatteringDistribution>
    base_distribution;

  initializeScatteringDistribution<TestElasticNeutronScatteringDistribution>( 
						      2.0, base_distribution );

  Teuchos::RCP<TestElasticNeutronScatteringDistribution> 
    scattering_distribution = Teuchos::rcp_dynamic_cast<TestElasticNeutronScatteringDistribution>( base_distribution );

  Teuchos::Array<double> neutron_velocity( 3 );
  neutron_velocity[0] = 0.0;
  neutron_velocity[1] = 0.0;
  neutron_velocity[2] = 4.0/3.0;

  Teuchos::Array<double> center_of_mass_velocity( 3 );
  center_of_mass_velocity[0] = 1.0;
  center_of_mass_velocity[1] = 1.0;
  center_of_mass_velocity[2] = -1.0/3.0;

  scattering_distribution->transformVelocityToLabFrame(
					   center_of_mass_velocity.getRawPtr(),
					   neutron_velocity.getRawPtr() );

  Teuchos::Array<double> lab_neutron_velocity( 3 );
  lab_neutron_velocity[0] = 1.0;
  lab_neutron_velocity[1] = 1.0;
  lab_neutron_velocity[2] = 1.0;

  TEST_COMPARE_FLOATING_ARRAYS( lab_neutron_velocity,
				neutron_velocity,
				1e-15 );
}

//---------------------------------------------------------------------------//
// Check that an incoming neutron can be scattered
TEUCHOS_UNIT_TEST( ElasticNeutronScatteringDistribution, 
		   scatterNeutron )
{
  Teuchos::RCP<MonteCarlo::NeutronScatteringDistribution> scattering_dist;
  
  initializeScatteringDistribution<MonteCarlo::ElasticNeutronScatteringDistribution>( 2.0, scattering_dist );
  
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
