//---------------------------------------------------------------------------//
//!
//! \file   tstPhaseSpacePoint.cpp
//! \author Alex Robinson
//! \brief  Phase space point unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <string>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_PhaseSpacePoint.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "Utility_BasicCartesianCoordinateConversionPolicy.hpp"
#include "Utility_GeneralCartesianSpatialCoordinateConversionPolicy.hpp"
#include "Utility_GeneralCylindricalSpatialCoordinateConversionPolicy.hpp"
#include "Utility_GeneralSphericalSpatialCoordinateConversionPolicy.hpp"
#include "Utility_RotationSphericalCoordinateConversionPolicy.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//
std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
spatial_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );

std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
directional_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the primary spaial coordinate can be set
FRENSIE_UNIT_TEST( PhaseSpacePoint, setPrimarySpatialCoordinate )
{
  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  point.setPrimarySpatialCoordinate( 1.0 );

  FRENSIE_CHECK_EQUAL( point.getPrimarySpatialCoordinate(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the secondary spatial coordinate can be set
FRENSIE_UNIT_TEST( PhaseSpacePoint, setSecondarySpatialCoordinate )
{
  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  point.setSecondarySpatialCoordinate( 2.0 );

  FRENSIE_CHECK_EQUAL( point.getSecondarySpatialCoordinate(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the tertiary spatial coordinate can be set
FRENSIE_UNIT_TEST( PhaseSpacePoint, setTertiarySpatialCoordinate )
{
  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  point.setTertiarySpatialCoordinate( 2.0 );

  FRENSIE_CHECK_EQUAL( point.getTertiarySpatialCoordinate(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the primary directional coordinate can be set
FRENSIE_UNIT_TEST( PhaseSpacePoint, setPrimaryDirectionalCoordinate )
{
  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  point.setPrimaryDirectionalCoordinate( 1.0 );

  FRENSIE_CHECK_EQUAL( point.getPrimaryDirectionalCoordinate(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the secondary directional coordinate can be set
FRENSIE_UNIT_TEST( PhaseSpacePoint, setSecondaryDirectionalCoordinate )
{
  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  point.setSecondaryDirectionalCoordinate( 1.0 );

  FRENSIE_CHECK_EQUAL( point.getSecondaryDirectionalCoordinate(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the tertiary directional coordinate can be set
FRENSIE_UNIT_TEST( PhaseSpacePoint, setTertiaryDirectionalCoordinate )
{
  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  point.setTertiaryDirectionalCoordinate( 1.0 );

  FRENSIE_CHECK_EQUAL( point.getTertiaryDirectionalCoordinate(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the energy coordinate can be set
FRENSIE_UNIT_TEST( PhaseSpacePoint, setEnergyCoordinate )
{
  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  point.setEnergyCoordinate( 10.0 );

  FRENSIE_CHECK_EQUAL( point.getEnergyCoordinate(), 10.0 );
}

//---------------------------------------------------------------------------//
// Check that the time coordinate can be set
FRENSIE_UNIT_TEST( PhaseSpacePoint, setTimeCoordinate )
{
  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  point.setTimeCoordinate( 10.0 );

  FRENSIE_CHECK_EQUAL( point.getTimeCoordinate(), 10.0 );
}

//---------------------------------------------------------------------------//
// Check that the weight coordinate can be set
FRENSIE_UNIT_TEST( PhaseSpacePoint, setWeightCoordinate )
{
  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  point.setWeightCoordinate( 0.5 );

  FRENSIE_CHECK_EQUAL( point.getWeightCoordinate(), 0.5 );
}

//---------------------------------------------------------------------------//
// Check that the spatial coordinates can be converted to Cartesian coordinates
FRENSIE_UNIT_TEST( PhaseSpacePoint,
                   convertSpatialCoordinatesToCartesianCoordinates )
{
  // Cartesian spatial coordinate system located at the origin
  std::unique_ptr<MonteCarlo::PhaseSpacePoint> point(
      new MonteCarlo::PhaseSpacePoint( spatial_coord_conversion_policy,
                                       directional_coord_conversion_policy ) );

  point->setPrimarySpatialCoordinate( 1.0 );
  point->setSecondarySpatialCoordinate( 2.0 );
  point->setTertiarySpatialCoordinate( 3.0 );

  double cartesian_point[3];

  point->convertSpatialCoordinatesToCartesianCoordinates( cartesian_point );

  FRENSIE_CHECK_EQUAL( cartesian_point[0], 1.0 );
  FRENSIE_CHECK_EQUAL( cartesian_point[1], 2.0 );
  FRENSIE_CHECK_EQUAL( cartesian_point[2], 3.0 );

  // Cartesian spatial coordinate system
  {
    std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
      spatial_policy(
               new Utility::GeneralCartesianSpatialCoordinateConversionPolicy(
                             std::vector<double>( {2.0, -1.0, 0.1} ).data(),
                             std::vector<double>( {1.0, 1.0, 1.0} ).data() ) );

    point.reset( new MonteCarlo::PhaseSpacePoint(
                       spatial_policy, directional_coord_conversion_policy ) );
  }

  point->setPrimarySpatialCoordinate( 0.0 );
  point->setSecondarySpatialCoordinate( 0.0 );
  point->setTertiarySpatialCoordinate( 2.0 );

  point->convertSpatialCoordinatesToCartesianCoordinates( cartesian_point );

  FRENSIE_CHECK_FLOATING_EQUALITY( cartesian_point[0], 2.0/sqrt(3.0)+2.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cartesian_point[1], 2.0/sqrt(3.0)-1.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cartesian_point[2], 2.0/sqrt(3.0)+0.1, 1e-12 );

  // Cylindrical spatial coordinate system
  {
    std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
      spatial_policy(
             new Utility::GeneralCylindricalSpatialCoordinateConversionPolicy(
                             std::vector<double>( {2.0, -1.0, 0.1} ).data(),
                             std::vector<double>( {1.0, 1.0, 1.0} ).data() ) );

    point.reset( new MonteCarlo::PhaseSpacePoint(
                       spatial_policy, directional_coord_conversion_policy ) );
  }

  point->setPrimarySpatialCoordinate( 2.0 );
  point->setSecondarySpatialCoordinate( 3*Utility::PhysicalConstants::pi/2 );
  point->setTertiarySpatialCoordinate( 0.0 );

  point->convertSpatialCoordinatesToCartesianCoordinates( cartesian_point );

  FRENSIE_CHECK_FLOATING_EQUALITY( cartesian_point[0], sqrt(2.0)+2.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cartesian_point[1], -sqrt(2.0)-1.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cartesian_point[2], 0.1, 1e-12 );

  // Spherical spatial coordinate system
  {
    std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
      spatial_policy(
               new Utility::GeneralSphericalSpatialCoordinateConversionPolicy(
                             std::vector<double>( {2.0, -1.0, 0.1} ).data(),
                             std::vector<double>( {1.0, 1.0, 1.0} ).data() ) );

    point.reset( new MonteCarlo::PhaseSpacePoint(
                       spatial_policy, directional_coord_conversion_policy ) );
  }

  point->setPrimarySpatialCoordinate( 2.0 );
  point->setSecondarySpatialCoordinate( Utility::PhysicalConstants::pi );
  point->setTertiarySpatialCoordinate( 0.0 );

  point->convertSpatialCoordinatesToCartesianCoordinates( cartesian_point );

  FRENSIE_CHECK_FLOATING_EQUALITY( cartesian_point[0], -2.0/sqrt(6.0)+2.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cartesian_point[1], -2.0/sqrt(6.0)-1.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cartesian_point[2], sqrt(8.0/3.0)+0.1, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the directional coordinates can be converted to Cartesian
// coordinates
FRENSIE_UNIT_TEST( PhaseSpacePoint,
                   convertDirectionalCoordinatesToCartesianCoordinates )
{
  // Cartesian directional coordinate system
  std::unique_ptr<MonteCarlo::PhaseSpacePoint> point(
      new MonteCarlo::PhaseSpacePoint( spatial_coord_conversion_policy,
                                       directional_coord_conversion_policy ) );

  point->setPrimaryDirectionalCoordinate( 1.0 );
  point->setSecondaryDirectionalCoordinate( 1.0 );
  point->setTertiaryDirectionalCoordinate( 1.0 );

  double cartesian_direction[3];

  point->convertDirectionalCoordinatesToCartesianCoordinates( cartesian_direction );

  FRENSIE_CHECK_FLOATING_EQUALITY( cartesian_direction[0], 1.0/sqrt(3.0), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cartesian_direction[1], 1.0/sqrt(3.0), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cartesian_direction[2], 1.0/sqrt(3.0), 1e-12 );

  // Spherical directional coordinate system
  {
    std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
      directional_policy(
                     new Utility::RotationSphericalCoordinateConversionPolicy(
                             std::vector<double>( {1.0, 1.0, 1.0} ).data() ) );

    point.reset(
              new MonteCarlo::PhaseSpacePoint( spatial_coord_conversion_policy,
                                               directional_policy ) );
  }

  point->setPrimaryDirectionalCoordinate( 1.0 );
  point->setSecondaryDirectionalCoordinate( Utility::PhysicalConstants::pi/2 );
  point->setTertiaryDirectionalCoordinate( 0.0 );

  point->convertDirectionalCoordinatesToCartesianCoordinates( cartesian_direction );

  FRENSIE_CHECK_FLOATING_EQUALITY( cartesian_direction[0], -sqrt(2.0)/2, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cartesian_direction[1], sqrt(2.0)/2, 1e-12 );
  FRENSIE_CHECK_SMALL( cartesian_direction[2], 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the primary spaial coordinate weight can be set
FRENSIE_UNIT_TEST( PhaseSpacePoint, setPrimarySpatialCoordinateWeight )
{
  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  point.setPrimarySpatialCoordinateWeight( 0.5 );

  FRENSIE_CHECK_EQUAL( point.getPrimarySpatialCoordinateWeight(), 0.5 );
}

//---------------------------------------------------------------------------//
// Check that the secondary spatial coordinate weight can be set
FRENSIE_UNIT_TEST( PhaseSpacePoint, setSecondarySpatialCoordinateWeight )
{
  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  point.setSecondarySpatialCoordinateWeight( 0.5 );

  FRENSIE_CHECK_EQUAL( point.getSecondarySpatialCoordinateWeight(), 0.5 );
}

//---------------------------------------------------------------------------//
// Check that the tertiary spatial coordinate weight can be set
FRENSIE_UNIT_TEST( PhaseSpacePoint, setTertiarySpatialCoordinateWeight )
{
  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  point.setTertiarySpatialCoordinateWeight( 0.5 );

  FRENSIE_CHECK_EQUAL( point.getTertiarySpatialCoordinateWeight(), 0.5 );
}

//---------------------------------------------------------------------------//
// Check that the primary directional coordinate weight can be set
FRENSIE_UNIT_TEST( PhaseSpacePoint, setPrimaryDirectionalCoordinateWeight )
{
  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  point.setPrimaryDirectionalCoordinateWeight( 0.5 );

  FRENSIE_CHECK_EQUAL( point.getPrimaryDirectionalCoordinateWeight(), 0.5 );
}

//---------------------------------------------------------------------------//
// Check that the secondary directional coordinate weight can be set
FRENSIE_UNIT_TEST( PhaseSpacePoint, setSecondaryDirectionalCoordinateWeight )
{
  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );
  
  point.setSecondaryDirectionalCoordinateWeight( 0.5 );

  FRENSIE_CHECK_EQUAL( point.getSecondaryDirectionalCoordinateWeight(), 0.5 );
}

//---------------------------------------------------------------------------//
// Check that the tertiary directional coordinate weight can be set
FRENSIE_UNIT_TEST( PhaseSpacePoint, setTertiaryDirectionalCoordinateWeight )
{
  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );
  
  point.setTertiaryDirectionalCoordinateWeight( 0.5 );

  FRENSIE_CHECK_EQUAL( point.getTertiaryDirectionalCoordinateWeight(), 0.5 );
}

//---------------------------------------------------------------------------//
// Check that the energy coordinate weight can be set
FRENSIE_UNIT_TEST( PhaseSpacePoint, setEnergyCoordinateWeight )
{
  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );
  
  point.setEnergyCoordinateWeight( 0.1 );

  FRENSIE_CHECK_EQUAL( point.getEnergyCoordinateWeight(), 0.1 );
}

//---------------------------------------------------------------------------//
// Check that the time coordinate weight can be set
FRENSIE_UNIT_TEST( PhaseSpacePoint, setTimeCoordinateWeight )
{
  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );
  
  point.setTimeCoordinateWeight( 0.1 );

  FRENSIE_CHECK_EQUAL( point.getTimeCoordinateWeight(), 0.1 );
}

//---------------------------------------------------------------------------//
// Check that the weight of all spatial coordinates can be returned
FRENSIE_UNIT_TEST( PhaseSpacePoint, getWeightOfSpatialCoordinates )
{
  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  point.setPrimarySpatialCoordinateWeight( 0.1 );
  point.setSecondarySpatialCoordinateWeight( 0.2 );
  point.setTertiarySpatialCoordinateWeight( 0.3 );

  FRENSIE_CHECK_EQUAL( point.getWeightOfSpatialCoordinates(), 0.1*0.2*0.3 );
}

//---------------------------------------------------------------------------//
// Check that the weight of all directional coordinates can be returned
FRENSIE_UNIT_TEST( PhaseSpacePoint, getWeightOfDirectionalCoordinates )
{
  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  point.setPrimaryDirectionalCoordinateWeight( 0.4 );
  point.setSecondaryDirectionalCoordinateWeight( 0.5 );
  point.setTertiaryDirectionalCoordinateWeight( 0.6 );

  FRENSIE_CHECK_EQUAL( point.getWeightOfDirectionalCoordinates(), 0.4*0.5*0.6 );
}

//---------------------------------------------------------------------------//
// Check that the weight of all coordinates can be returned
FRENSIE_UNIT_TEST( PhaseSpacePoint, getWeightOfCoordinates )
{
  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  point.setPrimarySpatialCoordinateWeight( 0.1 );
  point.setSecondarySpatialCoordinateWeight( 0.2 );
  point.setTertiarySpatialCoordinateWeight( 0.3 );
  point.setPrimaryDirectionalCoordinateWeight( 0.4 );
  point.setSecondaryDirectionalCoordinateWeight( 0.5 );
  point.setTertiaryDirectionalCoordinateWeight( 0.6 );
  point.setEnergyCoordinateWeight( 0.99 );
  point.setTimeCoordinateWeight( 0.95 );
  point.setWeightCoordinate( 0.78 );

  FRENSIE_CHECK_FLOATING_EQUALITY( point.getWeightOfCoordinates(),
                          0.0005281848,
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a particle state can be set
FRENSIE_UNIT_TEST( PhaseSpacePoint, setParticleState_cartesian )
{
  // Cartesian spatial and directional coordinate system located at the origin
  std::unique_ptr<MonteCarlo::PhaseSpacePoint> point(
      new MonteCarlo::PhaseSpacePoint( spatial_coord_conversion_policy,
                                       directional_coord_conversion_policy ) );

  point->setPrimarySpatialCoordinate( 1.0 );
  point->setPrimarySpatialCoordinateWeight( 0.1 );
  
  point->setSecondarySpatialCoordinate( 2.0 );
  point->setSecondarySpatialCoordinateWeight( 0.2 );
  
  point->setTertiarySpatialCoordinate( 3.0 );
  point->setTertiarySpatialCoordinateWeight( 0.3 );
  
  point->setPrimaryDirectionalCoordinate( 1.0 );
  point->setPrimaryDirectionalCoordinateWeight( 0.4 );
  
  point->setSecondaryDirectionalCoordinate( 1.0 );
  point->setSecondaryDirectionalCoordinateWeight( 0.5 );
  
  point->setTertiaryDirectionalCoordinate( 1.0 );
  point->setTertiaryDirectionalCoordinateWeight( 0.6 );
  
  point->setEnergyCoordinate( 0.5 );
  point->setEnergyCoordinateWeight( 0.99 );
  
  point->setTimeCoordinate( 1.0 );
  point->setTimeCoordinateWeight( 0.95 );
  
  point->setWeightCoordinate( 0.78 );

  MonteCarlo::PhotonState photon( 1 );
  
  point->setParticleState( photon );

  FRENSIE_CHECK_EQUAL( photon.getXPosition(), 1.0 );
  FRENSIE_CHECK_EQUAL( photon.getYPosition(), 2.0 );
  FRENSIE_CHECK_EQUAL( photon.getZPosition(), 3.0 );
  FRENSIE_CHECK_EQUAL( photon.getXDirection(), 1.0/sqrt(3.0) );
  FRENSIE_CHECK_EQUAL( photon.getYDirection(), 1.0/sqrt(3.0) );
  FRENSIE_CHECK_EQUAL( photon.getZDirection(), 1.0/sqrt(3.0) );
  FRENSIE_CHECK_EQUAL( photon.getSourceEnergy(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getSourceTime(), 1.0 );
  FRENSIE_CHECK_EQUAL( photon.getTime(), 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getSourceWeight(), 0.0005281848, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getWeight(), 0.0005281848, 1e-12 );

  // Off-axis Cartesian spatial coordinate system,
  // Cartesian directional coordinate system
  {
    std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
      spatial_policy(
               new Utility::GeneralCartesianSpatialCoordinateConversionPolicy(
                             std::vector<double>( {2.0, -1.0, 0.1} ).data(),
                             std::vector<double>( {1.0, 1.0, 1.0} ).data() ) );

    point.reset( new MonteCarlo::PhaseSpacePoint(
                       spatial_policy, directional_coord_conversion_policy ) );
  }

  point->setPrimarySpatialCoordinate( 0.0 );
  point->setPrimarySpatialCoordinateWeight( 0.1 );
  
  point->setSecondarySpatialCoordinate( 0.0 );
  point->setSecondarySpatialCoordinateWeight( 0.2 );
  
  point->setTertiarySpatialCoordinate( 2.0 );
  point->setTertiarySpatialCoordinateWeight( 0.3 );

  point->setPrimaryDirectionalCoordinate( 1.0 );
  point->setPrimaryDirectionalCoordinateWeight( 0.4 );
  
  point->setSecondaryDirectionalCoordinate( 1.0 );
  point->setSecondaryDirectionalCoordinateWeight( 0.5 );
  
  point->setTertiaryDirectionalCoordinate( 1.0 );
  point->setTertiaryDirectionalCoordinateWeight( 0.6 );
  
  point->setEnergyCoordinate( 0.5 );
  point->setEnergyCoordinateWeight( 0.99 );
  
  point->setTimeCoordinate( 1.0 );
  point->setTimeCoordinateWeight( 0.95 );
  
  point->setWeightCoordinate( 0.78 );

  point->setParticleState( photon );

  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getXPosition(), 2.0/sqrt(3.0)+2.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getYPosition(), 2.0/sqrt(3.0)-1.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZPosition(), 2.0/sqrt(3.0)+0.1, 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getXDirection(), 1.0/sqrt(3.0) );
  FRENSIE_CHECK_EQUAL( photon.getYDirection(), 1.0/sqrt(3.0) );
  FRENSIE_CHECK_EQUAL( photon.getZDirection(), 1.0/sqrt(3.0) );
  FRENSIE_CHECK_EQUAL( photon.getSourceEnergy(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getSourceTime(), 1.0 );
  FRENSIE_CHECK_EQUAL( photon.getTime(), 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getSourceWeight(), 0.0005281848, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getWeight(), 0.0005281848, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a particle state can be set
FRENSIE_UNIT_TEST( PhaseSpacePoint, setParticleState_cylindrical )
{
  // Cylindrical spatial coordinate system located at the origin
  // Cartesian directional coordinate system
  std::unique_ptr<MonteCarlo::PhaseSpacePoint> point;

  {
    std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
      spatial_policy(
             new Utility::GeneralCylindricalSpatialCoordinateConversionPolicy(
                             std::vector<double>( {2.0, -1.0, 0.1} ).data(),
                             std::vector<double>( {1.0, 1.0, 1.0} ).data() ) );

    point.reset( new MonteCarlo::PhaseSpacePoint(
                       spatial_policy, directional_coord_conversion_policy ) );
  }

  point->setPrimarySpatialCoordinate( 2.0 );
  point->setPrimarySpatialCoordinateWeight( 0.1 );
  
  point->setSecondarySpatialCoordinate( 3*Utility::PhysicalConstants::pi/2 );
  point->setSecondarySpatialCoordinateWeight( 0.2 );
  
  point->setTertiarySpatialCoordinate( 0.0 );
  point->setTertiarySpatialCoordinateWeight( 0.3 );
  
  point->setPrimaryDirectionalCoordinate( 1.0 );
  point->setPrimaryDirectionalCoordinateWeight( 0.4 );
  
  point->setSecondaryDirectionalCoordinate( 1.0 );
  point->setSecondaryDirectionalCoordinateWeight( 0.5 );
  
  point->setTertiaryDirectionalCoordinate( 1.0 );
  point->setTertiaryDirectionalCoordinateWeight( 0.6 );
  
  point->setEnergyCoordinate( 0.5 );
  point->setEnergyCoordinateWeight( 0.99 );
  
  point->setTimeCoordinate( 1.0 );
  point->setTimeCoordinateWeight( 0.95 );
  
  point->setWeightCoordinate( 0.78 );

  MonteCarlo::NeutronState neutron( 1 );

  point->setParticleState( neutron );

  FRENSIE_CHECK_FLOATING_EQUALITY( neutron.getXPosition(), sqrt(2.0)+2.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( neutron.getYPosition(), -sqrt(2.0)-1.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( neutron.getZPosition(), 0.1, 1e-12 );
  FRENSIE_CHECK_EQUAL( neutron.getXDirection(), 1.0/sqrt(3.0) );
  FRENSIE_CHECK_EQUAL( neutron.getYDirection(), 1.0/sqrt(3.0) );
  FRENSIE_CHECK_EQUAL( neutron.getZDirection(), 1.0/sqrt(3.0) );
  FRENSIE_CHECK_EQUAL( neutron.getSourceEnergy(), 0.5 );
  FRENSIE_CHECK_EQUAL( neutron.getEnergy(), 0.5 );
  FRENSIE_CHECK_EQUAL( neutron.getSourceTime(), 1.0 );
  FRENSIE_CHECK_EQUAL( neutron.getTime(), 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( neutron.getSourceWeight(), 0.0005281848, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( neutron.getWeight(), 0.0005281848, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a particle state can be set
FRENSIE_UNIT_TEST( PhaseSpacePoint, setParticleState_spherical )
{
  // Spherical spatial coordinate system located at the origin
  // Cartesian directional coordinate system
  std::unique_ptr<MonteCarlo::PhaseSpacePoint> point;

  {
    std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
      spatial_policy(
               new Utility::GeneralSphericalSpatialCoordinateConversionPolicy(
                             std::vector<double>( {2.0, -1.0, 0.1} ).data(),
                             std::vector<double>( {1.0, 1.0, 1.0} ).data() ) );

    point.reset( new MonteCarlo::PhaseSpacePoint(
                       spatial_policy, directional_coord_conversion_policy ) );
  }

  point->setPrimarySpatialCoordinate( 2.0 );
  point->setPrimarySpatialCoordinateWeight( 0.1 );
  
  point->setSecondarySpatialCoordinate( Utility::PhysicalConstants::pi );
  point->setSecondarySpatialCoordinateWeight( 0.2 );
  
  point->setTertiarySpatialCoordinate( 0.0 );
  point->setTertiarySpatialCoordinateWeight( 0.3 );

  point->setPrimaryDirectionalCoordinate( 1.0 );
  point->setPrimaryDirectionalCoordinateWeight( 0.4 );
  
  point->setSecondaryDirectionalCoordinate( 1.0 );
  point->setSecondaryDirectionalCoordinateWeight( 0.5 );
  
  point->setTertiaryDirectionalCoordinate( 1.0 );
  point->setTertiaryDirectionalCoordinateWeight( 0.6 );
  
  point->setEnergyCoordinate( 0.5 );
  point->setEnergyCoordinateWeight( 0.99 );
  
  point->setTimeCoordinate( 1.0 );
  point->setTimeCoordinateWeight( 0.95 );
  
  point->setWeightCoordinate( 0.78 );

  MonteCarlo::ElectronState electron( 1 );

  point->setParticleState( electron );

  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getXPosition(), -2.0/sqrt(6.0)+2.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getYPosition(), -2.0/sqrt(6.0)-1.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getZPosition(), sqrt(8.0/3.0)+0.1, 1e-12 );
  FRENSIE_CHECK_EQUAL( electron.getXDirection(), 1.0/sqrt(3.0) );
  FRENSIE_CHECK_EQUAL( electron.getYDirection(), 1.0/sqrt(3.0) );
  FRENSIE_CHECK_EQUAL( electron.getZDirection(), 1.0/sqrt(3.0) );
  FRENSIE_CHECK_EQUAL( electron.getSourceEnergy(), 0.5 );
  FRENSIE_CHECK_EQUAL( electron.getEnergy(), 0.5 );
  FRENSIE_CHECK_EQUAL( electron.getSourceTime(), 1.0 );
  FRENSIE_CHECK_EQUAL( electron.getTime(), 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getSourceWeight(), 0.0005281848, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getWeight(), 0.0005281848, 1e-12 );

  // Spherical spatial coordinate system located at the origin
  // Spherical directional coordinate system
  {
    std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
      spatial_policy(
               new Utility::GeneralSphericalSpatialCoordinateConversionPolicy(
                             std::vector<double>( {2.0, -1.0, 0.1} ).data(),
                             std::vector<double>( {1.0, 1.0, 1.0} ).data() ) );

    std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
      directional_policy(
                     new Utility::RotationSphericalCoordinateConversionPolicy(
                             std::vector<double>( {1.0, 1.0, 1.0} ).data() ) );

    point.reset( new MonteCarlo::PhaseSpacePoint(
                                        spatial_policy, directional_policy ) );
  }

  point->setPrimarySpatialCoordinate( 2.0 );
  point->setPrimarySpatialCoordinateWeight( 0.1 );
  
  point->setSecondarySpatialCoordinate( Utility::PhysicalConstants::pi );
  point->setSecondarySpatialCoordinateWeight( 0.2 );
  
  point->setTertiarySpatialCoordinate( 0.0 );
  point->setTertiarySpatialCoordinateWeight( 0.3 );

  point->setPrimaryDirectionalCoordinate( 1.0 );
  point->setPrimaryDirectionalCoordinateWeight( 0.4 );
  
  point->setSecondaryDirectionalCoordinate( Utility::PhysicalConstants::pi/2 );
  point->setSecondaryDirectionalCoordinateWeight( 0.5 );
  
  point->setTertiaryDirectionalCoordinate( 0.0 );
  point->setTertiaryDirectionalCoordinateWeight( 0.6 );

  point->setEnergyCoordinate( 0.5 );
  point->setEnergyCoordinateWeight( 0.99 );
  
  point->setTimeCoordinate( 1.0 );
  point->setTimeCoordinateWeight( 0.95 );
  
  point->setWeightCoordinate( 0.78 );

  point->setParticleState( electron );

  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getXPosition(), -2.0/sqrt(6.0)+2.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getYPosition(), -2.0/sqrt(6.0)-1.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getZPosition(), sqrt(8.0/3.0)+0.1, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getXDirection(), -sqrt(2.0)/2, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getYDirection(), sqrt(2.0)/2, 1e-12 );
  FRENSIE_CHECK_SMALL( electron.getZDirection(), 1e-12 );
  FRENSIE_CHECK_EQUAL( electron.getSourceEnergy(), 0.5 );
  FRENSIE_CHECK_EQUAL( electron.getEnergy(), 0.5 );
  FRENSIE_CHECK_EQUAL( electron.getSourceTime(), 1.0 );
  FRENSIE_CHECK_EQUAL( electron.getTime(), 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getSourceWeight(), 0.0005281848, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getWeight(), 0.0005281848, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a phase space point can be initialized from a particle state
FRENSIE_UNIT_TEST( PhaseSpacePoint, state_constructor_cartesian )
{
  // Cartesian spatial and directional coordinate system located at the origin
  MonteCarlo::PhotonState photon( 1 );
  photon.setPosition( 1.0, 2.0, 3.0 );
  photon.setDirection( 1.0/sqrt(3.0), 1.0/sqrt(3.0), 1.0/sqrt(3.0) );
  photon.setEnergy( 0.5 );
  photon.setTime( 1.0 );
  photon.setWeight( 0.0005281848 );
  
  std::unique_ptr<MonteCarlo::PhaseSpacePoint> point(
      new MonteCarlo::PhaseSpacePoint( photon,
                                       spatial_coord_conversion_policy,
                                       directional_coord_conversion_policy ) );

  FRENSIE_CHECK_EQUAL( point->getPrimarySpatialCoordinate(), 1.0 );
  FRENSIE_CHECK_EQUAL( point->getPrimarySpatialCoordinateWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( point->getSecondarySpatialCoordinate(), 2.0 );
  FRENSIE_CHECK_EQUAL( point->getSecondarySpatialCoordinateWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( point->getTertiarySpatialCoordinate(), 3.0 );
  FRENSIE_CHECK_EQUAL( point->getTertiarySpatialCoordinateWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( point->getPrimaryDirectionalCoordinate(), 1.0/sqrt(3.0) );
  FRENSIE_CHECK_EQUAL( point->getPrimaryDirectionalCoordinateWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( point->getSecondaryDirectionalCoordinate(), 1.0/sqrt(3.0) );
  FRENSIE_CHECK_EQUAL( point->getSecondaryDirectionalCoordinateWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( point->getTertiaryDirectionalCoordinate(), 1.0/sqrt(3.0) );
  FRENSIE_CHECK_EQUAL( point->getTertiaryDirectionalCoordinateWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( point->getEnergyCoordinate(), 0.5 );
  FRENSIE_CHECK_EQUAL( point->getEnergyCoordinateWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( point->getTimeCoordinate(), 1.0 );
  FRENSIE_CHECK_EQUAL( point->getTimeCoordinateWeight(), 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( point->getWeightCoordinate(), 0.0005281848, 1e-12 );

  // Off-axis Cartesian spatial coordinate system,
  // Cartesian directional coordinate system
  photon.setPosition( 2.0/sqrt(3.0)+2.0, 2.0/sqrt(3.0)-1.0, 2.0/sqrt(3.0)+0.1 );
  photon.setDirection( 1.0/sqrt(3.0), 1.0/sqrt(3.0), 1.0/sqrt(3.0) );
  photon.setEnergy( 0.5 );
  photon.setTime( 1.0 );
  photon.setWeight( 0.0005281848 );

  {
    std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
      spatial_policy(
               new Utility::GeneralCartesianSpatialCoordinateConversionPolicy(
                             std::vector<double>( {2.0, -1.0, 0.1} ).data(),
                             std::vector<double>( {1.0, 1.0, 1.0} ).data() ) );

    point.reset( new MonteCarlo::PhaseSpacePoint(
                                       photon,
                                       spatial_policy,
                                       directional_coord_conversion_policy ) );
  }

  FRENSIE_CHECK_SMALL( point->getPrimarySpatialCoordinate(), 1e-15 );
  FRENSIE_CHECK_EQUAL( point->getPrimarySpatialCoordinateWeight(), 1.0 );
  FRENSIE_CHECK_SMALL( point->getSecondarySpatialCoordinate(), 1e-15 );
  FRENSIE_CHECK_EQUAL( point->getSecondarySpatialCoordinateWeight(), 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( point->getTertiarySpatialCoordinate(), 2.0, 1e-15 );
  FRENSIE_CHECK_EQUAL( point->getTertiarySpatialCoordinateWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( point->getPrimaryDirectionalCoordinate(), 1.0/sqrt(3.0) );
  FRENSIE_CHECK_EQUAL( point->getPrimaryDirectionalCoordinateWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( point->getSecondaryDirectionalCoordinate(), 1.0/sqrt(3.0) );
  FRENSIE_CHECK_EQUAL( point->getSecondaryDirectionalCoordinateWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( point->getTertiaryDirectionalCoordinate(), 1.0/sqrt(3.0) );
  FRENSIE_CHECK_EQUAL( point->getTertiaryDirectionalCoordinateWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( point->getEnergyCoordinate(), 0.5 );
  FRENSIE_CHECK_EQUAL( point->getEnergyCoordinateWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( point->getTimeCoordinate(), 1.0 );
  FRENSIE_CHECK_EQUAL( point->getTimeCoordinateWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( point->getWeightCoordinate(), 0.0005281848 );
}

//---------------------------------------------------------------------------//
// Check that a phase space point can be initialized from a particle state
FRENSIE_UNIT_TEST( PhaseSpacePoint, state_constructor_cylindrical )
{
  // Cylindrical spatial coordinate system located at the origin
  // Cartesian directional coordinate system
  MonteCarlo::NeutronState neutron( 1 );
  neutron.setPosition( sqrt(2.0)+2.0, -sqrt(2.0)-1.0, 0.1 );
  neutron.setDirection( 1.0/sqrt(3.0), 1.0/sqrt(3.0), 1.0/sqrt(3.0) );
  neutron.setEnergy( 0.5 );
  neutron.setTime( 1.0 );
  neutron.setWeight( 0.0005281848 );

  std::unique_ptr<MonteCarlo::PhaseSpacePoint> point;

  {
    std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
      spatial_policy(
             new Utility::GeneralCylindricalSpatialCoordinateConversionPolicy(
                             std::vector<double>( {2.0, -1.0, 0.1} ).data(),
                             std::vector<double>( {1.0, 1.0, 1.0} ).data() ) );

    point.reset( new MonteCarlo::PhaseSpacePoint(
                                       neutron,
                                       spatial_policy,
                                       directional_coord_conversion_policy ) );
  }

  FRENSIE_CHECK_FLOATING_EQUALITY( point->getPrimarySpatialCoordinate(), 2.0, 1e-15 );
  FRENSIE_CHECK_EQUAL( point->getPrimarySpatialCoordinateWeight(), 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( point->getSecondarySpatialCoordinate(),
                          3*Utility::PhysicalConstants::pi/2,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( point->getSecondarySpatialCoordinateWeight(), 1.0 );
  FRENSIE_CHECK_SMALL( point->getTertiarySpatialCoordinate(), 1e-15 );
  FRENSIE_CHECK_EQUAL( point->getTertiarySpatialCoordinateWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( point->getPrimaryDirectionalCoordinate(), 1.0/sqrt(3.0) );
  FRENSIE_CHECK_EQUAL( point->getPrimaryDirectionalCoordinateWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( point->getSecondaryDirectionalCoordinate(), 1.0/sqrt(3.0) );
  FRENSIE_CHECK_EQUAL( point->getSecondaryDirectionalCoordinateWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( point->getTertiaryDirectionalCoordinate(), 1.0/sqrt(3.0) );
  FRENSIE_CHECK_EQUAL( point->getTertiaryDirectionalCoordinateWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( point->getEnergyCoordinate(), 0.5 );
  FRENSIE_CHECK_EQUAL( point->getEnergyCoordinateWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( point->getTimeCoordinate(), 1.0 );
  FRENSIE_CHECK_EQUAL( point->getTimeCoordinateWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( point->getWeightCoordinate(), 0.0005281848 );
}

//---------------------------------------------------------------------------//
// Check that a phase space point can be initialized from a particle state
FRENSIE_UNIT_TEST( PhaseSpacePoint, state_constructor_spherical )
{
  // Spherical spatial coordinate system located at the origin
  // Cartesian directional coordinate system
  MonteCarlo::ElectronState electron( 1 );
  electron.setPosition( -2.0/sqrt(6.0)+2.0, -2.0/sqrt(6.0)-1.0, sqrt(8.0/3.0)+0.1 );
  electron.setDirection( 1.0/sqrt(3.0), 1.0/sqrt(3.0), 1.0/sqrt(3.0) );
  electron.setEnergy( 0.5 );
  electron.setTime( 1.0 );
  electron.setWeight( 0.0005281848 );

  std::unique_ptr<MonteCarlo::PhaseSpacePoint> point;

  {
    std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
      spatial_policy(
               new Utility::GeneralSphericalSpatialCoordinateConversionPolicy(
                             std::vector<double>( {2.0, -1.0, 0.1} ).data(),
                             std::vector<double>( {1.0, 1.0, 1.0} ).data() ) );

    point.reset( new MonteCarlo::PhaseSpacePoint(
                                       electron,
                                       spatial_policy,
                                       directional_coord_conversion_policy ) );
  }

  FRENSIE_CHECK_FLOATING_EQUALITY( point->getPrimarySpatialCoordinate(), 2.0, 1e-15 );
  FRENSIE_CHECK_EQUAL( point->getPrimarySpatialCoordinateWeight(), 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( point->getSecondarySpatialCoordinate(),
                          Utility::PhysicalConstants::pi,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( point->getSecondarySpatialCoordinateWeight(), 1.0 );
  FRENSIE_CHECK_SMALL( point->getTertiarySpatialCoordinate(), 1e-15 );
  FRENSIE_CHECK_EQUAL( point->getTertiarySpatialCoordinateWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( point->getPrimaryDirectionalCoordinate(), 1.0/sqrt(3.0) );
  FRENSIE_CHECK_EQUAL( point->getPrimaryDirectionalCoordinateWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( point->getSecondaryDirectionalCoordinate(), 1.0/sqrt(3.0) );
  FRENSIE_CHECK_EQUAL( point->getSecondaryDirectionalCoordinateWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( point->getTertiaryDirectionalCoordinate(), 1.0/sqrt(3.0) );
  FRENSIE_CHECK_EQUAL( point->getTertiaryDirectionalCoordinateWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( point->getEnergyCoordinate(), 0.5 );
  FRENSIE_CHECK_EQUAL( point->getEnergyCoordinateWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( point->getTimeCoordinate(), 1.0 );
  FRENSIE_CHECK_EQUAL( point->getTimeCoordinateWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( point->getWeightCoordinate(), 0.0005281848 );

  // Spherical spatial coordinate system located at the origin
  // Spherical directional coordinate system
  electron.setPosition( -2.0/sqrt(6.0)+2.0, -2.0/sqrt(6.0)-1.0, sqrt(8.0/3.0)+0.1 );
  electron.setDirection( -sqrt(2.0)/2, sqrt(2.0)/2, 0.0 );
  electron.setEnergy( 0.5 );
  electron.setTime( 1.0 );
  electron.setWeight( 0.0005281848 );

  {
    std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
      spatial_policy(
               new Utility::GeneralSphericalSpatialCoordinateConversionPolicy(
                             std::vector<double>( {2.0, -1.0, 0.1} ).data(),
                             std::vector<double>( {1.0, 1.0, 1.0} ).data() ) );

    std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
      directional_policy(
                     new Utility::RotationSphericalCoordinateConversionPolicy(
                             std::vector<double>( {1.0, 1.0, 1.0} ).data() ) );

    point.reset( new MonteCarlo::PhaseSpacePoint( electron,
                                                  spatial_policy,
                                                  directional_policy ) );
  }

  FRENSIE_CHECK_FLOATING_EQUALITY( point->getPrimarySpatialCoordinate(), 2.0, 1e-15 );
  FRENSIE_CHECK_EQUAL( point->getPrimarySpatialCoordinateWeight(), 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( point->getSecondarySpatialCoordinate(),
                          Utility::PhysicalConstants::pi,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( point->getSecondarySpatialCoordinateWeight(), 1.0 );
  FRENSIE_CHECK_SMALL( point->getTertiarySpatialCoordinate(), 1e-15 );
  FRENSIE_CHECK_EQUAL( point->getTertiarySpatialCoordinateWeight(), 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( point->getPrimaryDirectionalCoordinate(), 1.0, 1e-15 )
  FRENSIE_CHECK_EQUAL( point->getPrimaryDirectionalCoordinateWeight(), 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( point->getSecondaryDirectionalCoordinate(),
                          Utility::PhysicalConstants::pi/2,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( point->getSecondaryDirectionalCoordinateWeight(), 1.0 );
  FRENSIE_CHECK_SMALL( point->getTertiaryDirectionalCoordinate(), 1e-15 );
                       
  FRENSIE_CHECK_EQUAL( point->getTertiaryDirectionalCoordinateWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( point->getEnergyCoordinate(), 0.5 );
  FRENSIE_CHECK_EQUAL( point->getEnergyCoordinateWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( point->getTimeCoordinate(), 1.0 );
  FRENSIE_CHECK_EQUAL( point->getTimeCoordinateWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( point->getWeightCoordinate(), 0.0005281848 );
}

//---------------------------------------------------------------------------//
// end tstPhaseSpacePoint.cpp
//---------------------------------------------------------------------------//
