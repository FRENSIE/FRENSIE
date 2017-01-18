//---------------------------------------------------------------------------//
//!
//! \file   tstParticleSourcePhaseSpacePoint.cpp
//! \author Alex Robinson
//! \brief  Particle source phase space point unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Tuple.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleSourcePhaseSpacePoint.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "Utility_BasicCartesianCoordinateConversionPolicy.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//
std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
    basic_spatial_policy( new Utility::BasicCartesianCoordinateConversionPolicy );

  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
    basic_directional_policy( new Utility::BasicCartesianCoordinateConversionPolicy );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the primary spatial coordinate can be set
TEUCHOS_UNIT_TEST( ParticleSourcePhaseSpacePoint,
                   get_setPrimarySpatialCoordinate )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  phase_space_point.setPrimarySpatialCoordinate( 1.0 );

  TEST_EQUALITY_CONST( phase_space_point.getPrimarySpatialCoordinate(), 1.0 );

  phase_space_point.setPrimarySpatialCoordinate( -1.0 );

  TEST_EQUALITY_CONST( phase_space_point.getPrimarySpatialCoordinate(), -1.0 );
}

//---------------------------------------------------------------------------//
// Check that the primary spatial coordinate weight can be set
TEUCHOS_UNIT_TEST( ParticleSourcePhaseSpacePoint,
                   get_setPrimarySpatialCoordinateWeight )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  phase_space_point.setPrimarySpatialCoordinateWeight( 0.5 );

  TEST_EQUALITY_CONST( phase_space_point.getPrimarySpatialCoordinateWeight(), 0.5 );

  phase_space_point.setPrimarySpatialCoordinateWeight( 1.5 );

  TEST_EQUALITY_CONST( phase_space_point.getPrimarySpatialCoordinateWeight(), 1.5 );
}

//---------------------------------------------------------------------------//
// Check that the secondary spatial coordinate can be set
TEUCHOS_UNIT_TEST( ParticleSourcePhaseSpacePoint,
                   get_setSecondarySpatialCoordinate )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  phase_space_point.setSecondarySpatialCoordinate( 1.0 );

  TEST_EQUALITY_CONST( phase_space_point.getSecondarySpatialCoordinate(), 1.0 );

  phase_space_point.setSecondarySpatialCoordinate( -1.0 );

  TEST_EQUALITY_CONST( phase_space_point.getSecondarySpatialCoordinate(), -1.0 );
}

//---------------------------------------------------------------------------//
// Check that the secondary spatial coordinate weight can be set
TEUCHOS_UNIT_TEST( ParticleSourcePhaseSpacePoint,
                   get_setSecondarySpatialCoordinateWeight )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  phase_space_point.setSecondarySpatialCoordinateWeight( 0.5 );

  TEST_EQUALITY_CONST( phase_space_point.getSecondarySpatialCoordinateWeight(), 0.5 );

  phase_space_point.setSecondarySpatialCoordinateWeight( 1.5 );

  TEST_EQUALITY_CONST( phase_space_point.getSecondarySpatialCoordinateWeight(), 1.5 );
}

//---------------------------------------------------------------------------//
// Check that the tertiary spatial coordinate can be set
TEUCHOS_UNIT_TEST( ParticleSourcePhaseSpacePoint,
                   get_setTertiarySpatialCoordinate )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  phase_space_point.setTertiarySpatialCoordinate( 1.0 );

  TEST_EQUALITY_CONST( phase_space_point.getTertiarySpatialCoordinate(), 1.0 );

  phase_space_point.setTertiarySpatialCoordinate( -1.0 );

  TEST_EQUALITY_CONST( phase_space_point.getTertiarySpatialCoordinate(), -1.0 );
}

//---------------------------------------------------------------------------//
// Check that the tertiary spatial coordinate weight can be set
TEUCHOS_UNIT_TEST( ParticleSourcePhaseSpacePoint,
                   get_setTertiarySpatialCoordinateWeight )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  phase_space_point.setTertiarySpatialCoordinateWeight( 0.5 );

  TEST_EQUALITY_CONST( phase_space_point.getTertiarySpatialCoordinateWeight(), 0.5 );

  phase_space_point.setTertiarySpatialCoordinateWeight( 1.5 );

  TEST_EQUALITY_CONST( phase_space_point.getTertiarySpatialCoordinateWeight(), 1.5 );
}

//---------------------------------------------------------------------------//
// Check that the spatial coordinates can be converted to Cartesian coordinates
TEUCHOS_UNIT_TEST( ParticleSourcePhaseSpacePoint,
                   convertSpatialCoordinatesToCartesianCoordinates )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  phase_space_point.setPrimarySpatialCoordinate( 1.0 );
  phase_space_point.setSecondarySpatialCoordinate( -1.0 );
  phase_space_point.setTertiarySpatialCoordinate( 0.1 );

  Teuchos::Tuple<double,3> cartesian_spatial_point;

  phase_space_point.convertSpatialCoordinatesToCartesianCoordinates(
                                                  cartesian_spatial_point[0],
                                                  cartesian_spatial_point[1],
                                                  cartesian_spatial_point[2] );

  TEST_EQUALITY_CONST( cartesian_spatial_point[0], 1.0 );
  TEST_EQUALITY_CONST( cartesian_spatial_point[1], -1.0 );
  TEST_EQUALITY_CONST( cartesian_spatial_point[2], 0.1 );
}

//---------------------------------------------------------------------------//
// Check that the weight of all spatial coordinates can be returned
TEUCHOS_UNIT_TEST( ParticleSourcePhaseSpacePoint,
                   getWeightOfSpatialCoordinates )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  phase_space_point.setPrimarySpatialCoordinateWeight( 0.5 );
  phase_space_point.setSecondarySpatialCoordinateWeight( 0.1 );
  phase_space_point.setTertiarySpatialCoordinateWeight( 0.75 );

  TEST_EQUALITY_CONST( phase_space_point.getWeightOfSpatialCoordinates(),
                       0.5*0.1*0.75 );
}

//---------------------------------------------------------------------------//
// Check that the primary directional coordinate can be set
TEUCHOS_UNIT_TEST( ParticleSourcePhaseSpacePoint,
                   get_setPrimaryDirectionalCoordinate )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  phase_space_point.setPrimaryDirectionalCoordinate( 1.0 );

  TEST_EQUALITY_CONST( phase_space_point.getPrimaryDirectionalCoordinate(), 1.0 );

  phase_space_point.setPrimaryDirectionalCoordinate( -1.0 );

  TEST_EQUALITY_CONST( phase_space_point.getPrimaryDirectionalCoordinate(), -1.0 );
}

//---------------------------------------------------------------------------//
// Check that the primary directional coordinate weight can be set
TEUCHOS_UNIT_TEST( ParticleSourcePhaseSpacePoint,
                   get_setPrimaryDirectionalCoordinateWeight )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  phase_space_point.setPrimaryDirectionalCoordinateWeight( 0.5 );

  TEST_EQUALITY_CONST( phase_space_point.getPrimaryDirectionalCoordinateWeight(), 0.5 );

  phase_space_point.setPrimaryDirectionalCoordinateWeight( 1.5 );

  TEST_EQUALITY_CONST( phase_space_point.getPrimaryDirectionalCoordinateWeight(), 1.5 );
}

//---------------------------------------------------------------------------//
// Check that the secondary directional coordinate can be set
TEUCHOS_UNIT_TEST( ParticleSourcePhaseSpacePoint,
                   get_setSecondaryDirectionalCoordinate )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  phase_space_point.setSecondaryDirectionalCoordinate( 1.0 );

  TEST_EQUALITY_CONST( phase_space_point.getSecondaryDirectionalCoordinate(), 1.0 );

  phase_space_point.setSecondaryDirectionalCoordinate( -1.0 );

  TEST_EQUALITY_CONST( phase_space_point.getSecondaryDirectionalCoordinate(), -1.0 );
}

//---------------------------------------------------------------------------//
// Check that the secondary directional coordinate weight can be set
TEUCHOS_UNIT_TEST( ParticleSourcePhaseSpacePoint,
                   get_setSecondaryDirectionalCoordinateWeight )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  phase_space_point.setSecondaryDirectionalCoordinateWeight( 0.5 );

  TEST_EQUALITY_CONST( phase_space_point.getSecondaryDirectionalCoordinateWeight(), 0.5 );

  phase_space_point.setSecondaryDirectionalCoordinateWeight( 1.5 );

  TEST_EQUALITY_CONST( phase_space_point.getSecondaryDirectionalCoordinateWeight(), 1.5 );
}

//---------------------------------------------------------------------------//
// Check that the tertiary directional coordinate can be set
TEUCHOS_UNIT_TEST( ParticleSourcePhaseSpacePoint,
                   get_setTertiaryDirectionalCoordinate )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  phase_space_point.setTertiaryDirectionalCoordinate( 1.0 );

  TEST_EQUALITY_CONST( phase_space_point.getTertiaryDirectionalCoordinate(), 1.0 );

  phase_space_point.setTertiaryDirectionalCoordinate( -1.0 );

  TEST_EQUALITY_CONST( phase_space_point.getTertiaryDirectionalCoordinate(), -1.0 );
}

//---------------------------------------------------------------------------//
// Check that the tertiary directional coordinate weight can be set
TEUCHOS_UNIT_TEST( ParticleSourcePhaseSpacePoint,
                   get_setTertiaryDirectionalCoordinateWeight )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  phase_space_point.setTertiaryDirectionalCoordinateWeight( 0.5 );

  TEST_EQUALITY_CONST( phase_space_point.getTertiaryDirectionalCoordinateWeight(), 0.5 );

  phase_space_point.setTertiaryDirectionalCoordinateWeight( 1.5 );

  TEST_EQUALITY_CONST( phase_space_point.getTertiaryDirectionalCoordinateWeight(), 1.5 );
}

//---------------------------------------------------------------------------//
// Check that the directional coordinates can be converted to Cartesian coordinates
TEUCHOS_UNIT_TEST( ParticleSourcePhaseSpacePoint,
                   convertDirectionalCoordinatesToCartesianCoordinates )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  phase_space_point.setPrimaryDirectionalCoordinate( 1.0 );
  phase_space_point.setSecondaryDirectionalCoordinate( -1.0 );
  phase_space_point.setTertiaryDirectionalCoordinate( -1.0 );

  Teuchos::Tuple<double,3> cartesian_directional_point;

  phase_space_point.convertDirectionalCoordinatesToCartesianCoordinates(
                                              cartesian_directional_point[0],
                                              cartesian_directional_point[1],
                                              cartesian_directional_point[2] );

  TEST_EQUALITY_CONST( cartesian_directional_point[0], 1.0/sqrt(3.0) );
  TEST_EQUALITY_CONST( cartesian_directional_point[1], -1.0/sqrt(3.0) );
  TEST_EQUALITY_CONST( cartesian_directional_point[2], -1.0/sqrt(3.0) );
}

//---------------------------------------------------------------------------//
// Check that the weight of all directional coordinates can be returned
TEUCHOS_UNIT_TEST( ParticleSourcePhaseSpacePoint,
                   getWeightOfDirectionalCoordinates )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  phase_space_point.setPrimaryDirectionalCoordinateWeight( 0.5 );
  phase_space_point.setSecondaryDirectionalCoordinateWeight( 0.1 );
  phase_space_point.setTertiaryDirectionalCoordinateWeight( 0.75 );

  TEST_EQUALITY_CONST( phase_space_point.getWeightOfDirectionalCoordinates(),
                       0.5*0.1*0.75 );
}

//---------------------------------------------------------------------------//
// Check that the energy coordinate of the phase space point can be set
TEUCHOS_UNIT_TEST( ParticleSourcePhaseSpacepoint,
                   get_setEnergyCoordinate )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  phase_space_point.setEnergyCoordinate( 10.0 );

  TEST_EQUALITY_CONST( phase_space_point.getEnergyCoordinate(), 10.0 );
}

//---------------------------------------------------------------------------//
// Check that the weight of the energy coordinate can be set
TEUCHOS_UNIT_TEST( ParticleSourcePhaseSpacePoint,
                   get_setEnergyCoordinateWeight )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  phase_space_point.setEnergyCoordinateWeight( 0.5 );

  TEST_EQUALITY_CONST( phase_space_point.getEnergyCoordinateWeight(), 0.5 );
}

//---------------------------------------------------------------------------//
// Check that the time coordinate of the phase space point can be set
TEUCHOS_UNIT_TEST( ParticleSourcePhaseSpacePoint,
                   get_setTimeCoordinate )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  phase_space_point.setTimeCoordinate( 0.1 );

  TEST_EQUALITY_CONST( phase_space_point.getTimeCoordinate(), 0.1 );
}

//---------------------------------------------------------------------------//
// Check that the weight of the time coordinate can be set
TEUCHOS_UNIT_TEST( ParticleSourcePhaseSpacePoint,
                   get_setTimeCoordinateWeight )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  phase_space_point.setTimeCoordinateWeight( 0.9 );

  TEST_EQUALITY_CONST( phase_space_point.getTimeCoordinateWeight(), 0.9 );
}

//---------------------------------------------------------------------------//
// Check that the weight coordinate of the phase space point can be set
TEUCHOS_UNIT_TEST( ParticleSourcePhaseSpacePoint,
                   get_setWeightCoordinate )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  phase_space_point.setWeightCoordinate( 0.75 );

  TEST_EQUALITY_CONST( phase_space_point.getWeightCoordinate(), 0.75 );
}

//---------------------------------------------------------------------------//
// Check that the weight of the coordinates can be returned
TEUCHOS_UNIT_TEST( ParticleSourcePhaseSpacePoint, getWeightOfCoordinates )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  phase_space_point.setPrimarySpatialCoordinateWeight( 0.5 );
  phase_space_point.setSecondarySpatialCoordinateWeight( 0.1 );
  phase_space_point.setTertiarySpatialCoordinateWeight( 0.75 );

  phase_space_point.setPrimaryDirectionalCoordinateWeight( 0.5 );
  phase_space_point.setSecondaryDirectionalCoordinateWeight( 0.1 );
  phase_space_point.setTertiaryDirectionalCoordinateWeight( 0.75 );

  phase_space_point.setEnergyCoordinateWeight( 0.9 );
  phase_space_point.setTimeCoordinateWeight( 0.1 );
  phase_space_point.setWeightCoordinate( 0.5 );

  TEST_FLOATING_EQUALITY( phase_space_point.getWeightOfCoordinates(),
                          6.328125e-05,
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a particle state can be set
TEUCHOS_UNIT_TEST( ParticleSourcePhaseSpacePoint, setParticleState )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  phase_space_point.setPrimarySpatialCoordinate( 2.0 );
  phase_space_point.setPrimarySpatialCoordinateWeight( 0.5 );

  phase_space_point.setSecondarySpatialCoordinate( 0.5 );
  phase_space_point.setSecondarySpatialCoordinateWeight( 0.1 );

  phase_space_point.setTertiarySpatialCoordinate( -1.0 );
  phase_space_point.setTertiarySpatialCoordinateWeight( 0.75 );

  phase_space_point.setPrimaryDirectionalCoordinate( 1.0 );
  phase_space_point.setPrimaryDirectionalCoordinateWeight( 0.5 );

  phase_space_point.setSecondaryDirectionalCoordinate( -1.0 );
  phase_space_point.setSecondaryDirectionalCoordinateWeight( 0.1 );

  phase_space_point.setTertiaryDirectionalCoordinate( -1.0 );
  phase_space_point.setTertiaryDirectionalCoordinateWeight( 0.75 );

  phase_space_point.setEnergyCoordinate( 10.0 );
  phase_space_point.setEnergyCoordinateWeight( 0.9 );

  phase_space_point.setTimeCoordinate( 3.0 );
  phase_space_point.setTimeCoordinateWeight( 0.1 );
  
  phase_space_point.setWeightCoordinate( 0.5 );

  MonteCarlo::NeutronState neutron( 0ull );
  
  phase_space_point.setParticleState( neutron );

  TEST_EQUALITY_CONST( neutron.getXPosition(), 2.0 );
  TEST_EQUALITY_CONST( neutron.getYPosition(), 0.5 );
  TEST_EQUALITY_CONST( neutron.getZPosition(), -1.0 );
  TEST_EQUALITY_CONST( neutron.getXDirection(), 1.0/sqrt(3.0) );
  TEST_EQUALITY_CONST( neutron.getYDirection(), -1.0/sqrt(3.0) );
  TEST_EQUALITY_CONST( neutron.getZDirection(), -1.0/sqrt(3.0) );
  TEST_EQUALITY_CONST( neutron.getSourceEnergy(), 10.0 );
  TEST_EQUALITY_CONST( neutron.getEnergy(), 10.0 );
  TEST_EQUALITY_CONST( neutron.getSourceTime(), 3.0 );
  TEST_EQUALITY_CONST( neutron.getTime(), 3.0 );
  TEST_FLOATING_EQUALITY( neutron.getSourceWeight(),
                          6.328125e-05,
                          1e-15 );
  TEST_FLOATING_EQUALITY( neutron.getWeight(),
                          6.328125e-05,
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the phase space point defaults are correct
TEUCHOS_UNIT_TEST( ParticleSourcePhaseSpacePoint, defaults )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  TEST_EQUALITY_CONST( phase_space_point.getPrimarySpatialCoordinate(), 0.0 );
  TEST_EQUALITY_CONST( phase_space_point.getPrimarySpatialCoordinateWeight(), 1.0 );
  
  TEST_EQUALITY_CONST( phase_space_point.getSecondarySpatialCoordinate(), 0.0 );
  TEST_EQUALITY_CONST( phase_space_point.getSecondarySpatialCoordinateWeight(), 1.0 );
  
  TEST_EQUALITY_CONST( phase_space_point.getTertiarySpatialCoordinate(), 0.0 );
  TEST_EQUALITY_CONST( phase_space_point.getTertiarySpatialCoordinateWeight(), 1.0 );
  
  TEST_EQUALITY_CONST( phase_space_point.getPrimaryDirectionalCoordinate(), 1.0 );
  TEST_EQUALITY_CONST( phase_space_point.getPrimaryDirectionalCoordinateWeight(), 1.0 );
  
  TEST_EQUALITY_CONST( phase_space_point.getSecondaryDirectionalCoordinate(), 0.0 );
  TEST_EQUALITY_CONST( phase_space_point.getSecondaryDirectionalCoordinateWeight(), 1.0 );
  
  TEST_EQUALITY_CONST( phase_space_point.getTertiaryDirectionalCoordinate(), 0.0 );
  TEST_EQUALITY_CONST( phase_space_point.getTertiaryDirectionalCoordinateWeight(), 1.0 );
  
  TEST_EQUALITY_CONST( phase_space_point.getEnergyCoordinate(), 1.0 );
  TEST_EQUALITY_CONST( phase_space_point.getEnergyCoordinateWeight(), 1.0 );
  
  TEST_EQUALITY_CONST( phase_space_point.getTimeCoordinate(), 0.0 );
  TEST_EQUALITY_CONST( phase_space_point.getTimeCoordinateWeight(), 1.0 );
  
  TEST_EQUALITY_CONST( phase_space_point.getWeightCoordinate(), 1.0 );
}

//---------------------------------------------------------------------------//
// end tstParticleSourcePhaseSpacePoint.cpp
//---------------------------------------------------------------------------//
