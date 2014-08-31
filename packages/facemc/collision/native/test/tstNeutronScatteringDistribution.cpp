//---------------------------------------------------------------------------//
//!
//! \file   tstNeutronScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  Neutron-neutron scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Facemc_UnitTestHarnessExtensions.hpp"
#include "Facemc_NeutronScatteringDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"

//---------------------------------------------------------------------------//
// Testing Structs
//---------------------------------------------------------------------------//
class TestScatteringDistribution : public Facemc::NeutronScatteringDistribution
{
public:
  TestScatteringDistribution( const double atomic_weight_ratio )
  : Facemc::NeutronScatteringDistribution( atomic_weight_ratio )
  { /* ... */ }

  ~TestScatteringDistribution()
  { /* ... */ }

  void scatterNeutron( Facemc::NeutronState& particle,
		       const double temperature ) const
  { /* ... */ }

  // Allow public access to the protected member functions
  using Facemc::NeutronScatteringDistribution::getAtomicWeightRatio;
  using Facemc::NeutronScatteringDistribution::sampleAzimuthalAngle;
  using Facemc::NeutronScatteringDistribution::calculateCenterOfMassVelocity;
  using Facemc::NeutronScatteringDistribution::transformVelocityToCenterOfMassFrame;
  using Facemc::NeutronScatteringDistribution::transformVelocityToLabFrame;
  using Facemc::NeutronScatteringDistribution::sampleTargetVelocity;
};

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the atomic weight ratio can be returned
TEUCHOS_UNIT_TEST( NeutronScatteringDistribution, getAtomicWeightRatio )
{
  TestScatteringDistribution scattering_distribution( 2.0 );
  
  TEST_EQUALITY_CONST( scattering_distribution.getAtomicWeightRatio(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the azimuthal angle can be sampled
TEUCHOS_UNIT_TEST( NeutronScatteringDistribution, sampleAzimuthalAngle )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  TestScatteringDistribution scattering_distribution( 2.0 );

  double azimuthal_angle = scattering_distribution.sampleAzimuthalAngle();

  TEST_EQUALITY_CONST( azimuthal_angle, 0.0 );

  azimuthal_angle = scattering_distribution.sampleAzimuthalAngle();

  TEST_EQUALITY_CONST( azimuthal_angle, Utility::PhysicalConstants::pi );

  azimuthal_angle = scattering_distribution.sampleAzimuthalAngle();

  TEST_FLOATING_EQUALITY( azimuthal_angle, 
			  2*Utility::PhysicalConstants::pi,
			  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the center of mass velocity can be calculated
TEUCHOS_UNIT_TEST( NeutronScatteringDistribution, 
		   calculateCenterOfMassVelocity )
{
  TestScatteringDistribution scattering_distribution( 2.0 );

  Teuchos::Array<double> neutron_velocity( 3 );
  neutron_velocity[0] = 1.0;
  neutron_velocity[1] = 1.0;
  neutron_velocity[2] = 1.0;
  
  Teuchos::Array<double> target_velocity( 3 );
  target_velocity[0] = 1.0;
  target_velocity[1] = 1.0;
  target_velocity[2] = -1.0;
  
  Teuchos::Array<double> center_of_mass_velocity( 3 );

  scattering_distribution.calculateCenterOfMassVelocity( 
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
TEUCHOS_UNIT_TEST( NeutronScatteringDistribution, 
		   transformVelocityToCenterOfMassFrame )
{
  TestScatteringDistribution scattering_distribution( 2.0 );

  Teuchos::Array<double> neutron_velocity( 3 );
  neutron_velocity[0] = 1.0;
  neutron_velocity[1] = 1.0;
  neutron_velocity[2] = 1.0;
  
  Teuchos::Array<double> center_of_mass_velocity( 3 );
  center_of_mass_velocity[0] = 1.0;
  center_of_mass_velocity[1] = 1.0;
  center_of_mass_velocity[2] = -1.0/3.0;

  scattering_distribution.transformVelocityToCenterOfMassFrame( 
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
TEUCHOS_UNIT_TEST( NeutronScatteringDistribution, 
		   transformVelocityToLabFrame )
{
  TestScatteringDistribution scattering_distribution( 2.0 );

  Teuchos::Array<double> neutron_velocity( 3 );
  neutron_velocity[0] = 0.0;
  neutron_velocity[1] = 0.0;
  neutron_velocity[2] = 4.0/3.0;

  Teuchos::Array<double> center_of_mass_velocity( 3 );
  center_of_mass_velocity[0] = 1.0;
  center_of_mass_velocity[1] = 1.0;
  center_of_mass_velocity[2] = -1.0/3.0;

  scattering_distribution.transformVelocityToLabFrame(
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
// tstNeutronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
