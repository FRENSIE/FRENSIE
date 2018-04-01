//---------------------------------------------------------------------------//
//!
//! \file   tstNuclearScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  Nuclear scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringDistribution.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Structs
//---------------------------------------------------------------------------//
class TestScatteringDistribution : public MonteCarlo::NuclearScatteringDistribution<MonteCarlo::NeutronState,MonteCarlo::NeutronState>
{
public:
  TestScatteringDistribution( const double atomic_weight_ratio )
  : MonteCarlo::NuclearScatteringDistribution<MonteCarlo::NeutronState,MonteCarlo::NeutronState>( atomic_weight_ratio )
  { /* ... */ }

  ~TestScatteringDistribution()
  { /* ... */ }

  void scatterParticle( const MonteCarlo::NeutronState& incoming_neutron,
			MonteCarlo::NeutronState& outgoing_neutron,
			const double temperature ) const
  { /* ... */ }

  // Allow public access to the protected member functions
  using MonteCarlo::NuclearScatteringDistribution<MonteCarlo::NeutronState,MonteCarlo::NeutronState>::getAtomicWeightRatio;
  using MonteCarlo::NuclearScatteringDistribution<MonteCarlo::NeutronState,MonteCarlo::NeutronState>::sampleAzimuthalAngle;
};

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the atomic weight ratio can be returned
FRENSIE_UNIT_TEST( NuclearScatteringDistribution, getAtomicWeightRatio )
{
  TestScatteringDistribution scattering_distribution( 2.0 );

  FRENSIE_CHECK_EQUAL( scattering_distribution.getAtomicWeightRatio(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the azimuthal angle can be sampled
FRENSIE_UNIT_TEST( NuclearScatteringDistribution, sampleAzimuthalAngle )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  TestScatteringDistribution scattering_distribution( 2.0 );

  double azimuthal_angle = scattering_distribution.sampleAzimuthalAngle();

  FRENSIE_CHECK_EQUAL( azimuthal_angle, 0.0 );

  azimuthal_angle = scattering_distribution.sampleAzimuthalAngle();

  FRENSIE_CHECK_EQUAL( azimuthal_angle, Utility::PhysicalConstants::pi );

  azimuthal_angle = scattering_distribution.sampleAzimuthalAngle();

  FRENSIE_CHECK_FLOATING_EQUALITY( azimuthal_angle,
                                   2*Utility::PhysicalConstants::pi,
                                   1e-15 );
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
// tstNuclearScatteringDistribution.cpp
//---------------------------------------------------------------------------//
