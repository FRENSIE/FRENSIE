//---------------------------------------------------------------------------//
//!
//! \file   tstParticleSourceDimensionTraits.cpp
//! \author Alex Robinson
//! \brief  Particle source dimension traits unit tests
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
#include "MonteCarlo_ParticleSourceDimensionTraits.hpp"
#include "MonteCarlo_SourceUnitTestHarnessExtensions.hpp"
#include "Utility_BasicCartesianCoordinateConversionPolicy.hpp"

using namespace MonteCarlo;

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
// Check that the class associated with the primary spatial dimension can be
// returned
TEUCHOS_UNIT_TEST( ParticleSourceDimensionTraits_PrimarySpatial, getClass )
{
  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<PRIMARY_SPATIAL_PS_DIMENSION>::getClass(),
                       SPATIAL_PS_DIMENSION_CLASS );
}

//---------------------------------------------------------------------------//
// Check that the primary spatial phase space coordinate of a phase space point
// can be retrieved and set
TEUCHOS_UNIT_TEST( ParticleSourceDimensionTraits_PrimarySpatial,
                   get_setCoordinate )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  ParticleSourceDimensionTraits<PRIMARY_SPATIAL_PS_DIMENSION>::setCoordinate( phase_space_point, 10.0 );

  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<PRIMARY_SPATIAL_PS_DIMENSION>::getCoordinate( phase_space_point ), 10.0 );
  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<PRIMARY_SPATIAL_PS_DIMENSION>::getCoordinate( phase_space_point ),
                       phase_space_point.getPrimarySpatialCoordinate() );
}

//---------------------------------------------------------------------------//
// Check that the primary spatial phase space coordinate weight can be
// retrieved and set
TEUCHOS_UNIT_TEST( ParticleSourceDimensionTraits_PrimarySpatial,
                   get_setCoordinateWeight )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  ParticleSourceDimensionTraits<PRIMARY_SPATIAL_PS_DIMENSION>::setCoordinateWeight( phase_space_point, 0.5 );

  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<PRIMARY_SPATIAL_PS_DIMENSION>::getCoordinateWeight( phase_space_point ), 0.5 );
  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<PRIMARY_SPATIAL_PS_DIMENSION>::getCoordinateWeight( phase_space_point ),
                       phase_space_point.getPrimarySpatialCoordinateWeight() );
}

//---------------------------------------------------------------------------//
// Check that the class associated with the secondary spatial dimension can be
// returned
TEUCHOS_UNIT_TEST( ParticleSourceDimensionTraits_SecondarySpatial, getClass )
{
  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<SECONDARY_SPATIAL_PS_DIMENSION>::getClass(),
                       SPATIAL_PS_DIMENSION_CLASS );
}

//---------------------------------------------------------------------------//
// Check that the secondary spatial phase space coordinate of a phase space point
// can be retrieved and set
TEUCHOS_UNIT_TEST( ParticleSourceDimensionTraits_SecondarySpatial,
                   get_setCoordinate )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  ParticleSourceDimensionTraits<SECONDARY_SPATIAL_PS_DIMENSION>::setCoordinate( phase_space_point, 10.0 );

  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<SECONDARY_SPATIAL_PS_DIMENSION>::getCoordinate( phase_space_point ), 10.0 );
  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<SECONDARY_SPATIAL_PS_DIMENSION>::getCoordinate( phase_space_point ),
                       phase_space_point.getSecondarySpatialCoordinate() );
}

//---------------------------------------------------------------------------//
// Check that the secondary spatial phase space coordinate weight can be
// retrieved and set
TEUCHOS_UNIT_TEST( ParticleSourceDimensionTraits_SecondarySpatial,
                   get_setCoordinateWeight )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  ParticleSourceDimensionTraits<SECONDARY_SPATIAL_PS_DIMENSION>::setCoordinateWeight( phase_space_point, 0.5 );

  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<SECONDARY_SPATIAL_PS_DIMENSION>::getCoordinateWeight( phase_space_point ), 0.5 );
  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<SECONDARY_SPATIAL_PS_DIMENSION>::getCoordinateWeight( phase_space_point ),
                       phase_space_point.getSecondarySpatialCoordinateWeight() );
}

//---------------------------------------------------------------------------//
// Check that the class associated with the tertiary spatial dimension can be
// returned
TEUCHOS_UNIT_TEST( ParticleSourceDimensionTraits_TertiarySpatial, getClass )
{
  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<TERTIARY_SPATIAL_PS_DIMENSION>::getClass(),
                       SPATIAL_PS_DIMENSION_CLASS );
}

//---------------------------------------------------------------------------//
// Check that the tertiary spatial phase space coordinate of a phase space point
// can be retrieved and set
TEUCHOS_UNIT_TEST( ParticleSourceDimensionTraits_TertiarySpatial,
                   get_setCoordinate )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  ParticleSourceDimensionTraits<TERTIARY_SPATIAL_PS_DIMENSION>::setCoordinate( phase_space_point, 10.0 );

  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<TERTIARY_SPATIAL_PS_DIMENSION>::getCoordinate( phase_space_point ), 10.0 );
  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<TERTIARY_SPATIAL_PS_DIMENSION>::getCoordinate( phase_space_point ),
                       phase_space_point.getTertiarySpatialCoordinate() );
}

//---------------------------------------------------------------------------//
// Check that the tertiary spatial phase space coordinate weight can be
// retrieved and set
TEUCHOS_UNIT_TEST( ParticleSourceDimensionTraits_TertiarySpatial,
                   get_setCoordinateWeight )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  ParticleSourceDimensionTraits<TERTIARY_SPATIAL_PS_DIMENSION>::setCoordinateWeight( phase_space_point, 0.5 );

  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<TERTIARY_SPATIAL_PS_DIMENSION>::getCoordinateWeight( phase_space_point ), 0.5 );
  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<TERTIARY_SPATIAL_PS_DIMENSION>::getCoordinateWeight( phase_space_point ),
                       phase_space_point.getTertiarySpatialCoordinateWeight() );
}

//---------------------------------------------------------------------------//
// Check that the class associated with the primary directional dimension can be
// returned
TEUCHOS_UNIT_TEST( ParticleSourceDimensionTraits_PrimaryDirectional, getClass )
{
  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<PRIMARY_DIRECTIONAL_PS_DIMENSION>::getClass(),
                       DIRECTIONAL_PS_DIMENSION_CLASS );
}

//---------------------------------------------------------------------------//
// Check that the primary directional phase space coordinate of a phase space point
// can be retrieved and set
TEUCHOS_UNIT_TEST( ParticleSourceDimensionTraits_PrimaryDirectional,
                   get_setCoordinate )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  ParticleSourceDimensionTraits<PRIMARY_DIRECTIONAL_PS_DIMENSION>::setCoordinate( phase_space_point, -1.0 );

  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<PRIMARY_DIRECTIONAL_PS_DIMENSION>::getCoordinate( phase_space_point ), -1.0 );
  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<PRIMARY_DIRECTIONAL_PS_DIMENSION>::getCoordinate( phase_space_point ),
                       phase_space_point.getPrimaryDirectionalCoordinate() );
}

//---------------------------------------------------------------------------//
// Check that the primary directional phase space coordinate weight can be
// retrieved and set
TEUCHOS_UNIT_TEST( ParticleSourceDimensionTraits_PrimaryDirectional,
                   get_setCoordinateWeight )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  ParticleSourceDimensionTraits<PRIMARY_DIRECTIONAL_PS_DIMENSION>::setCoordinateWeight( phase_space_point, 0.5 );

  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<PRIMARY_DIRECTIONAL_PS_DIMENSION>::getCoordinateWeight( phase_space_point ), 0.5 );
  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<PRIMARY_DIRECTIONAL_PS_DIMENSION>::getCoordinateWeight( phase_space_point ),
                       phase_space_point.getPrimaryDirectionalCoordinateWeight() );
}

//---------------------------------------------------------------------------//
// Check that the class associated with the secondary directional dimension can be
// returned
TEUCHOS_UNIT_TEST( ParticleSourceDimensionTraits_SecondaryDirectional, getClass )
{
  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<SECONDARY_DIRECTIONAL_PS_DIMENSION>::getClass(),
                       DIRECTIONAL_PS_DIMENSION_CLASS );
}

//---------------------------------------------------------------------------//
// Check that the secondary directional phase space coordinate of a phase space point
// can be retrieved and set
TEUCHOS_UNIT_TEST( ParticleSourceDimensionTraits_SecondaryDirectional,
                   get_setCoordinate )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  ParticleSourceDimensionTraits<SECONDARY_DIRECTIONAL_PS_DIMENSION>::setCoordinate( phase_space_point, -1.0 );

  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<SECONDARY_DIRECTIONAL_PS_DIMENSION>::getCoordinate( phase_space_point ), -1.0 );
  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<SECONDARY_DIRECTIONAL_PS_DIMENSION>::getCoordinate( phase_space_point ),
                       phase_space_point.getSecondaryDirectionalCoordinate() );
}

//---------------------------------------------------------------------------//
// Check that the secondary directional phase space coordinate weight can be
// retrieved and set
TEUCHOS_UNIT_TEST( ParticleSourceDimensionTraits_SecondaryDirectional,
                   get_setCoordinateWeight )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  ParticleSourceDimensionTraits<SECONDARY_DIRECTIONAL_PS_DIMENSION>::setCoordinateWeight( phase_space_point, 0.5 );

  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<SECONDARY_DIRECTIONAL_PS_DIMENSION>::getCoordinateWeight( phase_space_point ), 0.5 );
  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<SECONDARY_DIRECTIONAL_PS_DIMENSION>::getCoordinateWeight( phase_space_point ),
                       phase_space_point.getSecondaryDirectionalCoordinateWeight() );
}

//---------------------------------------------------------------------------//
// Check that the class associated with the tertiary directional dimension can be
// returned
TEUCHOS_UNIT_TEST( ParticleSourceDimensionTraits_TertiaryDirectional, getClass )
{
  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<TERTIARY_DIRECTIONAL_PS_DIMENSION>::getClass(),
                       DIRECTIONAL_PS_DIMENSION_CLASS );
}

//---------------------------------------------------------------------------//
// Check that the tertiary directional phase space coordinate of a phase space point
// can be retrieved and set
TEUCHOS_UNIT_TEST( ParticleSourceDimensionTraits_TertiaryDirectional,
                   get_setCoordinate )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  ParticleSourceDimensionTraits<TERTIARY_DIRECTIONAL_PS_DIMENSION>::setCoordinate( phase_space_point, -1.0 );

  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<TERTIARY_DIRECTIONAL_PS_DIMENSION>::getCoordinate( phase_space_point ), -1.0 );
  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<TERTIARY_DIRECTIONAL_PS_DIMENSION>::getCoordinate( phase_space_point ),
                       phase_space_point.getTertiaryDirectionalCoordinate() );
}

//---------------------------------------------------------------------------//
// Check that the tertiary directional phase space coordinate weight can be
// retrieved and set
TEUCHOS_UNIT_TEST( ParticleSourceDimensionTraits_TertiaryDirectional,
                   get_setCoordinateWeight )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  ParticleSourceDimensionTraits<TERTIARY_DIRECTIONAL_PS_DIMENSION>::setCoordinateWeight( phase_space_point, 0.5 );

  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<TERTIARY_DIRECTIONAL_PS_DIMENSION>::getCoordinateWeight( phase_space_point ), 0.5 );
  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<TERTIARY_DIRECTIONAL_PS_DIMENSION>::getCoordinateWeight( phase_space_point ),
                       phase_space_point.getTertiaryDirectionalCoordinateWeight() );
}

//---------------------------------------------------------------------------//
// Check that the class associated with the energy dimension can be
// returned
TEUCHOS_UNIT_TEST( ParticleSourceDimensionTraits_Energy, getClass )
{
  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<ENERGY_PS_DIMENSION>::getClass(),
                       ENERGY_PS_DIMENSION_CLASS );
}

//---------------------------------------------------------------------------//
// Check that the energy phase space coordinate of a phase space point
// can be retrieved and set
TEUCHOS_UNIT_TEST( ParticleSourceDimensionTraits_Energy,
                   get_setCoordinate )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  ParticleSourceDimensionTraits<ENERGY_PS_DIMENSION>::setCoordinate( phase_space_point, 1e-5 );

  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<ENERGY_PS_DIMENSION>::getCoordinate( phase_space_point ), 1e-5 );
  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<ENERGY_PS_DIMENSION>::getCoordinate( phase_space_point ),
                       phase_space_point.getEnergyCoordinate() );
}

//---------------------------------------------------------------------------//
// Check that the energy phase space coordinate weight can be
// retrieved and set
TEUCHOS_UNIT_TEST( ParticleSourceDimensionTraits_Energy,
                   get_setCoordinateWeight )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  ParticleSourceDimensionTraits<ENERGY_PS_DIMENSION>::setCoordinateWeight( phase_space_point, 0.5 );

  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<ENERGY_PS_DIMENSION>::getCoordinateWeight( phase_space_point ), 0.5 );
  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<ENERGY_PS_DIMENSION>::getCoordinateWeight( phase_space_point ),
                       phase_space_point.getEnergyCoordinateWeight() );
}

//---------------------------------------------------------------------------//
// Check that the class associated with the time dimension can be
// returned
TEUCHOS_UNIT_TEST( ParticleSourceDimensionTraits_Time, getClass )
{
  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<TIME_PS_DIMENSION>::getClass(),
                       TIME_PS_DIMENSION_CLASS );
}

//---------------------------------------------------------------------------//
// Check that the time phase space coordinate of a phase space point
// can be retrieved and set
TEUCHOS_UNIT_TEST( ParticleSourceDimensionTraits_Time,
                   get_setCoordinate )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  ParticleSourceDimensionTraits<TIME_PS_DIMENSION>::setCoordinate( phase_space_point, 1e-5 );

  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<TIME_PS_DIMENSION>::getCoordinate( phase_space_point ), 1e-5 );
  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<TIME_PS_DIMENSION>::getCoordinate( phase_space_point ),
                       phase_space_point.getTimeCoordinate() );
}

//---------------------------------------------------------------------------//
// Check that the time phase space coordinate weight can be
// retrieved and set
TEUCHOS_UNIT_TEST( ParticleSourceDimensionTraits_Time,
                   get_setCoordinateWeight )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  ParticleSourceDimensionTraits<TIME_PS_DIMENSION>::setCoordinateWeight( phase_space_point, 0.5 );

  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<TIME_PS_DIMENSION>::getCoordinateWeight( phase_space_point ), 0.5 );
  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<TIME_PS_DIMENSION>::getCoordinateWeight( phase_space_point ),
                       phase_space_point.getTimeCoordinateWeight() );
}

//---------------------------------------------------------------------------//
// Check that the class associated with the weight dimension can be
// returned
TEUCHOS_UNIT_TEST( ParticleSourceDimensionTraits_Weight, getClass )
{
  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<WEIGHT_PS_DIMENSION>::getClass(),
                       WEIGHT_PS_DIMENSION_CLASS );
}

//---------------------------------------------------------------------------//
// Check that the weight phase space coordinate of a phase space point
// can be retrieved and set
TEUCHOS_UNIT_TEST( ParticleSourceDimensionTraits_Weight,
                   get_setCoordinate )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  ParticleSourceDimensionTraits<WEIGHT_PS_DIMENSION>::setCoordinate( phase_space_point, 0.5 );

  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<WEIGHT_PS_DIMENSION>::getCoordinate( phase_space_point ), 0.5 );
  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<WEIGHT_PS_DIMENSION>::getCoordinate( phase_space_point ),
                       phase_space_point.getWeightCoordinate() );
}

//---------------------------------------------------------------------------//
// Check that the weight phase space coordinate weight can be
// retrieved and set
TEUCHOS_UNIT_TEST( ParticleSourceDimensionTraits_Weight,
                   get_setCoordinateWeight )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );

  ParticleSourceDimensionTraits<WEIGHT_PS_DIMENSION>::setCoordinateWeight( phase_space_point, 0.1 );

  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<WEIGHT_PS_DIMENSION>::getCoordinateWeight( phase_space_point ), 0.1 );
  TEST_EQUALITY_CONST( ParticleSourceDimensionTraits<WEIGHT_PS_DIMENSION>::getCoordinateWeight( phase_space_point ),
                       phase_space_point.getWeightCoordinate() );
}

//---------------------------------------------------------------------------//
// Check that the high-level getters/setters behave as expected
TEUCHOS_UNIT_TEST( ParticleSourceDimensionTraits, get_setCoordinate )
{
  MonteCarlo::ParticleSourcePhaseSpacePoint
    phase_space_point( basic_spatial_policy, basic_directional_policy );
  
  setCoordinate<PRIMARY_SPATIAL_PS_DIMENSION>( phase_space_point, 10.0 );
  setCoordinate<SECONDARY_SPATIAL_PS_DIMENSION>( phase_space_point, 5.0 );
  setCoordinate<TERTIARY_SPATIAL_PS_DIMENSION>( phase_space_point, -2.0 );

  setCoordinate<PRIMARY_DIRECTIONAL_PS_DIMENSION>( phase_space_point, 1.0/sqrt(3.0) );
  setCoordinate<SECONDARY_DIRECTIONAL_PS_DIMENSION>( phase_space_point, -1.0/sqrt(3.0) );
  setCoordinate<TERTIARY_DIRECTIONAL_PS_DIMENSION>( phase_space_point, 1.0/sqrt(3.) );

  setCoordinate<ENERGY_PS_DIMENSION>( phase_space_point, 1e-5 );
  setCoordinate<TIME_PS_DIMENSION>( phase_space_point, 2.0 );
  setCoordinate<WEIGHT_PS_DIMENSION>( phase_space_point, 0.5 );

  TEST_EQUALITY_CONST( phase_space_point.getPrimarySpatialCoordinate(), 10.0 );
  TEST_EQUALITY_CONST( getCoordinate<PRIMARY_SPATIAL_PS_DIMENSION>( phase_space_point ), 10.0 );

  TEST_EQUALITY_CONST( phase_space_point.getSecondarySpatialCoordinate(), 5.0 );
  TEST_EQUALITY_CONST( getCoordinate<SECONDARY_SPATIAL_PS_DIMENSION>( phase_space_point ), 5.0 );

  TEST_EQUALITY_CONST( phase_space_point.getTertiarySpatialCoordinate(), -2.0 );
  TEST_EQUALITY_CONST( getCoordinate<TERTIARY_SPATIAL_PS_DIMENSION>( phase_space_point ), -2.0 );

  TEST_EQUALITY_CONST( phase_space_point.getPrimaryDirectionalCoordinate(), 1.0/sqrt(3.0) );
  TEST_EQUALITY_CONST( getCoordinate<PRIMARY_DIRECTIONAL_PS_DIMENSION>( phase_space_point ), 1.0/sqrt(3.0) );

  TEST_EQUALITY_CONST( phase_space_point.getSecondaryDirectionalCoordinate(), -1.0/sqrt(3.0) );
  TEST_EQUALITY_CONST( getCoordinate<SECONDARY_DIRECTIONAL_PS_DIMENSION>( phase_space_point ), -1.0/sqrt(3.0) );

  TEST_EQUALITY_CONST( phase_space_point.getTertiaryDirectionalCoordinate(), 1.0/sqrt(3.0) );
  TEST_EQUALITY_CONST( getCoordinate<TERTIARY_DIRECTIONAL_PS_DIMENSION>( phase_space_point ), 1.0/sqrt(3.0) );

  TEST_EQUALITY_CONST( phase_space_point.getEnergyCoordinate(), 1e-5 );
  TEST_EQUALITY_CONST( getCoordinate<ENERGY_PS_DIMENSION>( phase_space_point ), 1e-5 );

  TEST_EQUALITY_CONST( phase_space_point.getTimeCoordinate(), 2.0 );
  TEST_EQUALITY_CONST( getCoordinate<TIME_PS_DIMENSION>( phase_space_point ), 2.0 );

  TEST_EQUALITY_CONST( phase_space_point.getWeightCoordinate(), 0.5 );
  TEST_EQUALITY_CONST( getCoordinate<WEIGHT_PS_DIMENSION>( phase_space_point ), 0.5 );
}

//---------------------------------------------------------------------------//
// end tstParticleSourceDimensionTraits.cpp
//---------------------------------------------------------------------------//
