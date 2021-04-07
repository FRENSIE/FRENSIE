//---------------------------------------------------------------------------//
//!
//! \file   tstPhaseSpaceDimensionTraits.cpp
//! \author Alex Robinson
//! \brief  Phase space dimension traits unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_PhaseSpacePoint.hpp"
#include "MonteCarlo_PhaseSpaceDimensionTraits.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Utility_BasicCartesianCoordinateConversionPolicy.hpp"
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
// Check that the dimension class can be returned
FRENSIE_UNIT_TEST( PhaseSpaceDimensionTraits, getClass )
{
  FRENSIE_CHECK_EQUAL( MonteCarlo::PhaseSpaceDimensionTraits<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>::getClass(),
                       MonteCarlo::SPATIAL_DIMENSION_CLASS );
  FRENSIE_CHECK_EQUAL( MonteCarlo::PhaseSpaceDimensionTraits<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>::getClass(),
                       MonteCarlo::SPATIAL_DIMENSION_CLASS );
  FRENSIE_CHECK_EQUAL( MonteCarlo::PhaseSpaceDimensionTraits<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>::getClass(),
                       MonteCarlo::SPATIAL_DIMENSION_CLASS );

  FRENSIE_CHECK_EQUAL( MonteCarlo::PhaseSpaceDimensionTraits<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION>::getClass(),
                       MonteCarlo::DIRECTIONAL_DIMENSION_CLASS );
  FRENSIE_CHECK_EQUAL( MonteCarlo::PhaseSpaceDimensionTraits<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION>::getClass(),
                       MonteCarlo::DIRECTIONAL_DIMENSION_CLASS );
  FRENSIE_CHECK_EQUAL( MonteCarlo::PhaseSpaceDimensionTraits<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION>::getClass(),
                       MonteCarlo::DIRECTIONAL_DIMENSION_CLASS );
  FRENSIE_CHECK_EQUAL( MonteCarlo::PhaseSpaceDimensionTraits<MonteCarlo::ENERGY_DIMENSION>::getClass(),
                       MonteCarlo::ENERGY_DIMENSION_CLASS );
  FRENSIE_CHECK_EQUAL( MonteCarlo::PhaseSpaceDimensionTraits<MonteCarlo::TIME_DIMENSION>::getClass(),
                       MonteCarlo::TIME_DIMENSION_CLASS );
  FRENSIE_CHECK_EQUAL( MonteCarlo::PhaseSpaceDimensionTraits<MonteCarlo::WEIGHT_DIMENSION>::getClass(),
                       MonteCarlo::WEIGHT_DIMENSION_CLASS );
  FRENSIE_CHECK_EQUAL( MonteCarlo::PhaseSpaceDimensionTraits<MonteCarlo::SOURCE_ENERGY_DIMENSION>::getClass(),
                       MonteCarlo::ENERGY_DIMENSION_CLASS );
  FRENSIE_CHECK_EQUAL( MonteCarlo::PhaseSpaceDimensionTraits<MonteCarlo::SOURCE_TIME_DIMENSION>::getClass(),
                       MonteCarlo::TIME_DIMENSION_CLASS );
  FRENSIE_CHECK_EQUAL( MonteCarlo::PhaseSpaceDimensionTraits<MonteCarlo::SOURCE_WEIGHT_DIMENSION>::getClass(),
                       MonteCarlo::WEIGHT_DIMENSION_CLASS );
}

//---------------------------------------------------------------------------//
// Check that the phase space point coordinates can be returned
FRENSIE_UNIT_TEST( PhaseSpaceDimensionTraits, getCoordinate_point )
{
  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  point.setPrimarySpatialCoordinate( 1.0 );

  FRENSIE_CHECK_EQUAL( MonteCarlo::getCoordinate<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( point ), 1.0 );

  point.setSecondarySpatialCoordinate( 2.0 );

  FRENSIE_CHECK_EQUAL( MonteCarlo::getCoordinate<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( point ), 2.0 );

  point.setTertiarySpatialCoordinate( 3.0 );

  FRENSIE_CHECK_EQUAL( MonteCarlo::getCoordinate<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( point ), 3.0 );

  point.setPrimaryDirectionalCoordinate( 1.0 );

  FRENSIE_CHECK_EQUAL( MonteCarlo::getCoordinate<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION>( point ), 1.0 );

  point.setSecondaryDirectionalCoordinate( 1.0 );

  FRENSIE_CHECK_EQUAL( MonteCarlo::getCoordinate<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION>( point ), 1.0 );

  point.setTertiaryDirectionalCoordinate( 1.0 );

  FRENSIE_CHECK_EQUAL( MonteCarlo::getCoordinate<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION>( point ), 1.0 );

  point.setEnergyCoordinate( 0.5 );
  
  FRENSIE_CHECK_EQUAL( MonteCarlo::getCoordinate<MonteCarlo::ENERGY_DIMENSION>( point ), 0.5 );

  point.setTimeCoordinate( 0.1 );

  FRENSIE_CHECK_EQUAL( MonteCarlo::getCoordinate<MonteCarlo::TIME_DIMENSION>( point ), 0.1 );

  point.setWeightCoordinate( 0.9 );

  FRENSIE_CHECK_EQUAL( MonteCarlo::getCoordinate<MonteCarlo::WEIGHT_DIMENSION>( point ), 0.9 );

  point.setEnergyCoordinate( 0.5 );

  FRENSIE_CHECK_EQUAL( MonteCarlo::getCoordinate<MonteCarlo::SOURCE_ENERGY_DIMENSION>( point ), 0.5 );

  point.setTimeCoordinate( 0.1 );

  FRENSIE_CHECK_EQUAL( MonteCarlo::getCoordinate<MonteCarlo::SOURCE_TIME_DIMENSION>( point ), 0.1 );

  point.setWeightCoordinate( 0.9 );

  FRENSIE_CHECK_EQUAL( MonteCarlo::getCoordinate<MonteCarlo::SOURCE_WEIGHT_DIMENSION>( point ), 0.9 );
}

//---------------------------------------------------------------------------//
// Check that the phase space point coordinates can be returned
FRENSIE_UNIT_TEST( PhaseSpaceDimensionTraits, getCoordinate_particle )
{
  MonteCarlo::PhotonState point( 1ull );

  point.setPosition( 1.0, 2.0, 3.0 );

  FRENSIE_CHECK_EQUAL( MonteCarlo::getCoordinate<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( point ), 1.0 );
  FRENSIE_CHECK_EQUAL( MonteCarlo::getCoordinate<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( point ), 2.0 );
  FRENSIE_CHECK_EQUAL( MonteCarlo::getCoordinate<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( point ), 3.0 );

  point.setDirection( -1.0/std::sqrt(2.0), 1.0/sqrt(2.0), 0.0 );

  FRENSIE_CHECK_EQUAL( MonteCarlo::getCoordinate<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION>( point ), -1.0/std::sqrt(2.0) );
  FRENSIE_CHECK_EQUAL( MonteCarlo::getCoordinate<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION>( point ), 1.0/sqrt(2.0) );
  FRENSIE_CHECK_EQUAL( MonteCarlo::getCoordinate<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION>( point ), 0.0 );

  point.setEnergy( 0.5 );
  
  FRENSIE_CHECK_EQUAL( MonteCarlo::getCoordinate<MonteCarlo::ENERGY_DIMENSION>( point ), 0.5 );

  point.setTime( 0.1 );

  FRENSIE_CHECK_EQUAL( MonteCarlo::getCoordinate<MonteCarlo::TIME_DIMENSION>( point ), 0.1 );

  point.setWeight( 0.9 );

  FRENSIE_CHECK_EQUAL( MonteCarlo::getCoordinate<MonteCarlo::WEIGHT_DIMENSION>( point ), 0.9 );

  point.setSourceEnergy( 1.0 );
  
  FRENSIE_CHECK_EQUAL( MonteCarlo::getCoordinate<MonteCarlo::SOURCE_ENERGY_DIMENSION>( point ), 1.0 );

  point.setSourceTime( 0.2 );

  FRENSIE_CHECK_EQUAL( MonteCarlo::getCoordinate<MonteCarlo::SOURCE_TIME_DIMENSION>( point ), 0.2 );

  point.setSourceWeight( 1.0 );

  FRENSIE_CHECK_EQUAL( MonteCarlo::getCoordinate<MonteCarlo::SOURCE_WEIGHT_DIMENSION>( point ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the phase space point coordinates can be set
FRENSIE_UNIT_TEST( PhaseSpaceDimensionTraits, setCoordinate )
{
  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  MonteCarlo::setCoordinate<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( point, 1.0 );

  FRENSIE_CHECK_EQUAL( point.getPrimarySpatialCoordinate(), 1.0 );

  MonteCarlo::setCoordinate<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( point, 2.0 );

  FRENSIE_CHECK_EQUAL( point.getSecondarySpatialCoordinate(), 2.0 );

  MonteCarlo::setCoordinate<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( point, 3.0 );

  FRENSIE_CHECK_EQUAL( point.getTertiarySpatialCoordinate(), 3.0 );

  MonteCarlo::setCoordinate<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION>( point, 1.0 );

  FRENSIE_CHECK_EQUAL( point.getPrimaryDirectionalCoordinate(), 1.0 );

  MonteCarlo::setCoordinate<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION>( point, 1.0 );

  FRENSIE_CHECK_EQUAL( point.getSecondaryDirectionalCoordinate(), 1.0 );

  MonteCarlo::setCoordinate<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION>( point, 1.0 );

  FRENSIE_CHECK_EQUAL( point.getTertiaryDirectionalCoordinate(), 1.0 );

  MonteCarlo::setCoordinate<MonteCarlo::ENERGY_DIMENSION>( point, 0.5 );

  FRENSIE_CHECK_EQUAL( point.getEnergyCoordinate(), 0.5 );

  MonteCarlo::setCoordinate<MonteCarlo::TIME_DIMENSION>( point, 0.1 );

  FRENSIE_CHECK_EQUAL( point.getTimeCoordinate(), 0.1 );

  MonteCarlo::setCoordinate<MonteCarlo::WEIGHT_DIMENSION>( point, 0.9 );

  FRENSIE_CHECK_EQUAL( point.getWeightCoordinate(), 0.9 );

  MonteCarlo::setCoordinate<MonteCarlo::SOURCE_ENERGY_DIMENSION>( point, 0.5 );

  FRENSIE_CHECK_EQUAL( point.getEnergyCoordinate(), 0.5 );

  MonteCarlo::setCoordinate<MonteCarlo::SOURCE_TIME_DIMENSION>( point, 0.1 );

  FRENSIE_CHECK_EQUAL( point.getTimeCoordinate(), 0.1 );

  MonteCarlo::setCoordinate<MonteCarlo::SOURCE_WEIGHT_DIMENSION>( point, 0.9 );

  FRENSIE_CHECK_EQUAL( point.getWeightCoordinate(), 0.9 );
}

//---------------------------------------------------------------------------//
// Check that the coordinate weight can be returned
FRENSIE_UNIT_TEST( PhaseSpaceDimensionTraits, getCoordinateWeight )
{
  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );
  
  point.setPrimarySpatialCoordinateWeight( 0.1 );

  FRENSIE_CHECK_EQUAL( MonteCarlo::getCoordinateWeight<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( point ), 0.1 );

  point.setSecondarySpatialCoordinateWeight( 0.2 );

  FRENSIE_CHECK_EQUAL( MonteCarlo::getCoordinateWeight<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( point ), 0.2 );

  point.setTertiarySpatialCoordinateWeight( 0.3 );

  FRENSIE_CHECK_EQUAL( MonteCarlo::getCoordinateWeight<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( point ), 0.3 );

  point.setPrimaryDirectionalCoordinateWeight( 0.4 );

  FRENSIE_CHECK_EQUAL( MonteCarlo::getCoordinateWeight<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION>( point ), 0.4 );

  point.setSecondaryDirectionalCoordinateWeight( 0.5 );

  FRENSIE_CHECK_EQUAL( MonteCarlo::getCoordinateWeight<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION>( point ), 0.5 );

  point.setTertiaryDirectionalCoordinateWeight( 0.6 );

  FRENSIE_CHECK_EQUAL( MonteCarlo::getCoordinateWeight<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION>( point ), 0.6 );

  point.setEnergyCoordinateWeight( 0.7 );
  
  FRENSIE_CHECK_EQUAL( MonteCarlo::getCoordinateWeight<MonteCarlo::ENERGY_DIMENSION>( point ), 0.7 );

  point.setTimeCoordinateWeight( 0.8 );

  FRENSIE_CHECK_EQUAL( MonteCarlo::getCoordinateWeight<MonteCarlo::TIME_DIMENSION>( point ), 0.8 );

  point.setWeightCoordinate( 0.9 );

  FRENSIE_CHECK_EQUAL( MonteCarlo::getCoordinateWeight<MonteCarlo::WEIGHT_DIMENSION>( point ), 0.9 );

  point.setEnergyCoordinateWeight( 0.7 );
  
  FRENSIE_CHECK_EQUAL( MonteCarlo::getCoordinateWeight<MonteCarlo::SOURCE_ENERGY_DIMENSION>( point ), 0.7 );

  point.setTimeCoordinateWeight( 0.8 );

  FRENSIE_CHECK_EQUAL( MonteCarlo::getCoordinateWeight<MonteCarlo::SOURCE_TIME_DIMENSION>( point ), 0.8 );

  point.setWeightCoordinate( 0.9 );

  FRENSIE_CHECK_EQUAL( MonteCarlo::getCoordinateWeight<MonteCarlo::SOURCE_WEIGHT_DIMENSION>( point ), 0.9 );
}

//---------------------------------------------------------------------------//
// Check that the coordinate weight can be set
FRENSIE_UNIT_TEST( PhaseSpaceDimensionTraits, setCoordinateWeight )
{
  MonteCarlo::PhaseSpacePoint point( spatial_coord_conversion_policy,
                                     directional_coord_conversion_policy );

  MonteCarlo::setCoordinateWeight<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( point, 0.1 );

  FRENSIE_CHECK_EQUAL( point.getPrimarySpatialCoordinateWeight(), 0.1 );

  MonteCarlo::setCoordinateWeight<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( point, 0.2 );

  FRENSIE_CHECK_EQUAL( point.getSecondarySpatialCoordinateWeight(), 0.2 );

  MonteCarlo::setCoordinateWeight<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( point, 0.3 );

  FRENSIE_CHECK_EQUAL( point.getTertiarySpatialCoordinateWeight(), 0.3 );

  MonteCarlo::setCoordinateWeight<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION>( point, 0.4 );

  FRENSIE_CHECK_EQUAL( point.getPrimaryDirectionalCoordinateWeight(), 0.4 );

  MonteCarlo::setCoordinateWeight<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION>( point, 0.5 );

  FRENSIE_CHECK_EQUAL( point.getSecondaryDirectionalCoordinateWeight(), 0.5 );

  MonteCarlo::setCoordinateWeight<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION>( point, 0.6 );

  FRENSIE_CHECK_EQUAL( point.getTertiaryDirectionalCoordinateWeight(), 0.6 );

  MonteCarlo::setCoordinateWeight<MonteCarlo::ENERGY_DIMENSION>( point, 0.7 );

  FRENSIE_CHECK_EQUAL( point.getEnergyCoordinateWeight(), 0.7 );

  MonteCarlo::setCoordinateWeight<MonteCarlo::TIME_DIMENSION>( point, 0.8 );

  FRENSIE_CHECK_EQUAL( point.getTimeCoordinateWeight(), 0.8 );

  // The weight should be ignored with the weight dimension
  MonteCarlo::setCoordinateWeight<MonteCarlo::WEIGHT_DIMENSION>( point, 0.9 );

  FRENSIE_CHECK_EQUAL( point.getWeightCoordinate(), 1.0 );

  MonteCarlo::setCoordinateWeight<MonteCarlo::SOURCE_ENERGY_DIMENSION>( point, 0.7 );

  FRENSIE_CHECK_EQUAL( point.getEnergyCoordinateWeight(), 0.7 );

  MonteCarlo::setCoordinateWeight<MonteCarlo::SOURCE_TIME_DIMENSION>( point, 0.8 );

  FRENSIE_CHECK_EQUAL( point.getTimeCoordinateWeight(), 0.8 );

  // The weight should be ignored with the weight dimension
  MonteCarlo::setCoordinateWeight<MonteCarlo::SOURCE_WEIGHT_DIMENSION>( point, 0.9 );

  FRENSIE_CHECK_EQUAL( point.getWeightCoordinate(), 1.0 );
}

//---------------------------------------------------------------------------//
// end tstPhaseSpaceDimensionTraits.cpp
//---------------------------------------------------------------------------//
