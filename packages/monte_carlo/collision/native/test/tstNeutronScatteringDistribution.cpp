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
#include "MonteCarlo_UnitTestHarnessExtensions.hpp"
#include "MonteCarlo_NeutronScatteringDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"

//---------------------------------------------------------------------------//
// Testing Structs
//---------------------------------------------------------------------------//
class TestScatteringDistribution : public MonteCarlo::NeutronScatteringDistribution
{
public:
  TestScatteringDistribution( const double atomic_weight_ratio )
  : MonteCarlo::NeutronScatteringDistribution( atomic_weight_ratio )
  { /* ... */ }

  ~TestScatteringDistribution()
  { /* ... */ }

  void scatterNeutron( MonteCarlo::NeutronState& particle,
		       const double temperature ) const
  { /* ... */ }

  // Allow public access to the protected member functions
  using MonteCarlo::NeutronScatteringDistribution::getAtomicWeightRatio;
  using MonteCarlo::NeutronScatteringDistribution::sampleAzimuthalAngle;
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
