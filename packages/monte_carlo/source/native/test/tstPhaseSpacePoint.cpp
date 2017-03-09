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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Tuple.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhaseSpacePoint.hpp"
#include "Utility_BasicCartesianCoordinateConversionPolicy.hpp"
#include "Utility_GeneralCartesianSpatialCoordinateConversionPolicy.hpp"
#include "Utility_GeneralCylindricalSpatialCoordinateConversionPolicy.hpp"
#include "Utility_GeneralSphericalSpatialCoordinateConversionPolicy.hpp"
#include "Utility_RotationSphericalCoordinateConversionPolicy.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

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
TEUCHOS_UNIT_TEST( PhaseSpacePoint, setPrimarySpatialCoordinate )
{
  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  point.setPrimarySpatialCoordinate( 1.0 );

  TEST_EQUALITY_CONST( point.getPrimarySpatialCoordinate(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the secondary spatial coordinate can be set
TEUCHOS_UNIT_TEST( PhaseSpacePoint, setSecondarySpatialCoordinate )
{
  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  point.setSecondarySpatialCoordinate( 2.0 );

  TEST_EQUALITY_CONST( point.getSecondarySpatialCoordinate(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the tertiary spatial coordinate can be set
TEUCHOS_UNIT_TEST( PhaseSpacePoint, setTertiarySpatialCoordinate )
{
  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  point.setTertiarySpatialCoordinate( 2.0 );

  TEST_EQUALITY_CONST( point.getTertiarySpatialCoordinate(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the primary directional coordinate can be set
TEUCHOS_UNIT_TEST( PhaseSpacePoint, setPrimaryDirectionalCoordinate )
{
  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  point.setPrimaryDirectionalCoordinate( 1.0 );

  TEST_EQUALITY_CONST( point.getPrimaryDirectionalCoordinate(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the secondary directional coordinate can be set
TEUCHOS_UNIT_TEST( PhaseSpacePoint, setSecondaryDirectionalCoordinate )
{
  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  point.setSecondaryDirectionalCoordinate( 1.0 );

  TEST_EQUALITY_CONST( point.getSecondaryDirectionalCoordinate(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the tertiary directional coordinate can be set
TEUCHOS_UNIT_TEST( PhaseSpacePoint, setTertiaryDirectionalCoordinate )
{
  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  point.setTertiaryDirectionalCoordinate( 1.0 );

  TEST_EQUALITY_CONST( point.getTertiaryDirectionalCoordinate(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the energy coordinate can be set
TEUCHOS_UNIT_TEST( PhaseSpacePoint, setEnergyCoordinate )
{
  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  point.setEnergyCoordinate( 10.0 );

  TEST_EQUALITY_CONST( point.getEnergyCoordinate(), 10.0 );
}

//---------------------------------------------------------------------------//
// Check that the time coordinate can be set
TEUCHOS_UNIT_TEST( PhaseSpacePoint, setTimeCoordinate )
{
  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  point.setTimeCoordinate( 10.0 );

  TEST_EQUALITY_CONST( point.getTimeCoordinate(), 10.0 );
}

//---------------------------------------------------------------------------//
// Check that the weight coordinate can be set
TEUCHOS_UNIT_TEST( PhaseSpacePoint, setWeightCoordinate )
{
  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  point.setWeightCoordinate( 0.5 );

  TEST_EQUALITY_CONST( point.getWeightCoordinate(), 0.5 );
}

//---------------------------------------------------------------------------//
// Check that the spatial coordinates can be converted to Cartesian coordinates
TEUCHOS_UNIT_TEST( PhaseSpacePoint,
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

  TEST_EQUALITY_CONST( cartesian_point[0], 1.0 );
  TEST_EQUALITY_CONST( cartesian_point[1], 2.0 );
  TEST_EQUALITY_CONST( cartesian_point[2], 3.0 );

  // Cartesian spatial coordinate system
  {
    std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
      spatial_policy(
               new Utility::GeneralCartesianSpatialCoordinateConversionPolicy(
                                 Teuchos::tuple( 2.0, -1.0, 0.1 ).getRawPtr(),
                                 Teuchos::tuple(1.0, 1.0, 1.0).getRawPtr() ) );

    point.reset( new MonteCarlo::PhaseSpacePoint(
                       spatial_policy, directional_coord_conversion_policy ) );
  }

  point->setPrimarySpatialCoordinate( 0.0 );
  point->setSecondarySpatialCoordinate( 0.0 );
  point->setTertiarySpatialCoordinate( 2.0 );

  point->convertSpatialCoordinatesToCartesianCoordinates( cartesian_point );

  TEST_FLOATING_EQUALITY( cartesian_point[0], 2.0/sqrt(3.0)+2.0, 1e-12 );
  TEST_FLOATING_EQUALITY( cartesian_point[1], 2.0/sqrt(3.0)-1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( cartesian_point[2], 2.0/sqrt(3.0)+0.1, 1e-12 );

  // Cylindrical spatial coordinate system
  {
    std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
      spatial_policy(
             new Utility::GeneralCylindricalSpatialCoordinateConversionPolicy(
                               Teuchos::tuple( 2.0, -1.0, 0.1 ).getRawPtr(),
                               Teuchos::tuple( 1.0, 1.0, 1.0 ).getRawPtr() ) );

    point.reset( new MonteCarlo::PhaseSpacePoint(
                       spatial_policy, directional_coord_conversion_policy ) );
  }

  point->setPrimarySpatialCoordinate( 2.0 );
  point->setSecondarySpatialCoordinate( 3*Utility::PhysicalConstants::pi/2 );
  point->setTertiarySpatialCoordinate( 0.0 );

  point->convertSpatialCoordinatesToCartesianCoordinates( cartesian_point );

  TEST_FLOATING_EQUALITY( cartesian_point[0], sqrt(2.0)+2.0, 1e-12 );
  TEST_FLOATING_EQUALITY( cartesian_point[1], -sqrt(2.0)-1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( cartesian_point[2], 0.1, 1e-12 );

  // Spherical spatial coordinate system
  {
    std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
      spatial_policy(
               new Utility::GeneralSphericalSpatialCoordinateConversionPolicy(
                                 Teuchos::tuple(2.0, -1.0, 0.1).getRawPtr(),
                                 Teuchos::tuple(1.0, 1.0, 1.0).getRawPtr() ) );

    point.reset( new MonteCarlo::PhaseSpacePoint(
                       spatial_policy, directional_coord_conversion_policy ) );
  }

  point->setPrimarySpatialCoordinate( 2.0 );
  point->setSecondarySpatialCoordinate( Utility::PhysicalConstants::pi );
  point->setTertiarySpatialCoordinate( 0.0 );

  point->convertSpatialCoordinatesToCartesianCoordinates( cartesian_point );

  TEST_FLOATING_EQUALITY( cartesian_point[0], -2.0/sqrt(6.0)+2.0, 1e-12 );
  TEST_FLOATING_EQUALITY( cartesian_point[1], -2.0/sqrt(6.0)-1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( cartesian_point[2], sqrt(8.0/3.0)+0.1, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the directional coordinates can be converted to Cartesian
// coordinates
TEUCHOS_UNIT_TEST( PhaseSpacePoint,
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

  TEST_FLOATING_EQUALITY( cartesian_direction[0], 1.0/sqrt(3.0), 1e-12 );
  TEST_FLOATING_EQUALITY( cartesian_direction[1], 1.0/sqrt(3.0), 1e-12 );
  TEST_FLOATING_EQUALITY( cartesian_direction[2], 1.0/sqrt(3.0), 1e-12 );

  // Spherical directional coordinate system
  {
    std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
      directional_policy(
                     new Utility::RotationSphericalCoordinateConversionPolicy(
                                 Teuchos::tuple(1.0, 1.0, 1.0).getRawPtr() ) );

    point.reset(
              new MonteCarlo::PhaseSpacePoint( spatial_coord_conversion_policy,
                                               directional_policy ) );
  }

  point->setPrimaryDirectionalCoordinate( 1.0 );
  point->setSecondaryDirectionalCoordinate( Utility::PhysicalConstants::pi/2 );
  point->setTertiaryDirectionalCoordinate( 0.0 );

  point->convertDirectionalCoordinatesToCartesianCoordinates( cartesian_direction );

  TEST_FLOATING_EQUALITY( cartesian_direction[0], -sqrt(2.0)/2, 1e-12 );
  TEST_FLOATING_EQUALITY( cartesian_direction[1], sqrt(2.0)/2, 1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( cartesian_direction[2], 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the primary spaial coordinate weight can be set
TEUCHOS_UNIT_TEST( PhaseSpacePoint, setPrimarySpatialCoordinateWeight )
{

}

//---------------------------------------------------------------------------//
// Check that the secondary spatial coordinate weight can be set
TEUCHOS_UNIT_TEST( PhaseSpacePoint, setSecondarySpatialCoordinateWeight )
{

}

//---------------------------------------------------------------------------//
// Check that the tertiary spatial coordinate weight can be set
TEUCHOS_UNIT_TEST( PhaseSpacePoint, setTertiarySpatialCoordinateWeight )
{

}

//---------------------------------------------------------------------------//
// Check that the primary directional coordinate weight can be set
TEUCHOS_UNIT_TEST( PhaseSpacePoint, setPrimaryDirectionalCoordinateWeight )
{

}

//---------------------------------------------------------------------------//
// Check that the secondary directional coordinate weight can be set
TEUCHOS_UNIT_TEST( PhaseSpacePoint, setSecondaryDirectionalCoordinateWeight )
{

}

//---------------------------------------------------------------------------//
// Check that the tertiary directional coordinate weight can be set
TEUCHOS_UNIT_TEST( PhaseSpacePoint, setTertiaryDirectionalCoordinateWeight )
{

}

//---------------------------------------------------------------------------//
// Check that the energy coordinate weight can be set
TEUCHOS_UNIT_TEST( PhaseSpacePoint, setEnergyCoordinateWeight )
{

}

//---------------------------------------------------------------------------//
// Check that the time coordinate weight can be set
TEUCHOS_UNIT_TEST( PhaseSpacePoint, setTimeCoordinateWeight )
{

}

//---------------------------------------------------------------------------//
// Check that the weight of all spatial coordinates can be returned
TEUCHOS_UNIT_TEST( PhaseSpacePoint, getWeightOfSpatialCoordinates )
{

}

//---------------------------------------------------------------------------//
// Check that the weight of all directional coordinates can be returned
TEUCHOS_UNIT_TEST( PhaseSpacePoint, getWeightOfDirectionalCoordinates )
{

}

//---------------------------------------------------------------------------//
// Check that the weight of all coordinates can be returned
TEUCHOS_UNIT_TEST( PhaseSpacePoint, getWeightOfCoordinates )
{

}

//---------------------------------------------------------------------------//
// Check that a particle state can be set
TEUCHOS_UNIT_TEST( PhaseSpacePoint, setParticleState )
{

}

//---------------------------------------------------------------------------//
// Check that a phase space point can be initialized from a particle state
TEUCHOS_UNIT_TEST( PhaseSpacePoint, state_constructor )
{

}

//---------------------------------------------------------------------------//
// end tstPhaseSpacePoint.cpp
//---------------------------------------------------------------------------//
