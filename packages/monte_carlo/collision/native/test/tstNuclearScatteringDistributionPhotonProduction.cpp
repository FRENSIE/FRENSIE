//---------------------------------------------------------------------------//
//!
//! \file   tstNuclearScatteringDistributionPhotonProduction.cpp
//! \author Eli Moll
//! \brief  Nuclear scattering distribution unit tests
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
#include "MonteCarlo_NuclearScatteringDistribution.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Utility_RandomNumberGenerator.hpp"

//---------------------------------------------------------------------------//
// Testing Structs
//---------------------------------------------------------------------------//
class TestScatteringDistributionPhotonProduction : public MonteCarlo::NuclearScatteringDistribution<MonteCarlo::NeutronState,MonteCarlo::PhotonState>
{
public:
  TestScatteringDistributionPhotonProduction( const double atomic_weight_ratio )
  : MonteCarlo::NuclearScatteringDistribution<MonteCarlo::NeutronState,MonteCarlo::PhotonState>( atomic_weight_ratio )
  { /* ... */ }

  ~TestScatteringDistributionPhotonProduction()
  { /* ... */ }

  void scatterParticle( const MonteCarlo::NeutronState& incoming_neutron,
			MonteCarlo::PhotonState& outgoing_photon,
			const double temperature ) const
  { /* ... */ }

  // Allow public access to the protected member functions
  using MonteCarlo::NuclearScatteringDistribution<MonteCarlo::NeutronState,MonteCarlo::PhotonState>::getAtomicWeightRatio;
  using MonteCarlo::NuclearScatteringDistribution<MonteCarlo::NeutronState,MonteCarlo::PhotonState>::sampleAzimuthalAngle;
};

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the atomic weight ratio can be returned
TEUCHOS_UNIT_TEST( NuclearScatteringDistributionPhotonProduction, getAtomicWeightRatio )
{
  TestScatteringDistributionPhotonProduction scattering_distribution( 2.0 );
  
  TEST_EQUALITY_CONST( scattering_distribution.getAtomicWeightRatio(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the azimuthal angle can be sampled
TEUCHOS_UNIT_TEST( NuclearScatteringDistributionPhotonProduction, sampleAzimuthalAngle )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  TestScatteringDistributionPhotonProduction scattering_distribution( 2.0 );

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
// tstNuclearScatteringDistribution.cpp
//---------------------------------------------------------------------------//
