//---------------------------------------------------------------------------//
//!
//! \file   tstDagMCParticleState.cpp
//! \author Alex Robinson
//! \brief  DagMC particle state unit tests using DagMC navigators
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_ParticleState.hpp"
#include "Geometry_DagMCNavigator.hpp"
#include "Geometry_DagMCModel.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "TestParticleState.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

namespace cgs = boost::units::cgs;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<const Geometry::DagMCModel> model;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a particle state can be embedded in a DagMC model
FRENSIE_UNIT_TEST( ParticleState, embedInModel )
{
  TestParticleState particle( 1ull );
  particle.setPosition( -40.0, -40.0, 108.0 );
  particle.setDirection( 0.0, 0.0, 1.0 );

  particle.embedInModel( model );

  // If embedding fails the particle state will be set to lost or gone
  FRENSIE_REQUIRE( (bool)particle );

  // Verify that the particle position and direction are unchanged
  FRENSIE_CHECK_EQUAL( particle.getXPosition(), -40.0 );
  FRENSIE_CHECK_EQUAL( particle.getYPosition(), -40.0 );
  FRENSIE_CHECK_EQUAL( particle.getZPosition(), 108.0 );
  FRENSIE_CHECK_EQUAL( particle.getXDirection(), 0.0 );
  FRENSIE_CHECK_EQUAL( particle.getYDirection(), 0.0 );
  FRENSIE_CHECK_EQUAL( particle.getZDirection(), 1.0 );

  // Check that the particle can move through the geometry
  FRENSIE_CHECK_EQUAL( particle.getCell(), 82 );

  Geometry::Navigator::EntityId surface_hit;

  Geometry::Navigator::Length distance_to_surface_hit =
    particle.navigator().fireRay( surface_hit );

  FRENSIE_CHECK_FLOATING_EQUALITY( distance_to_surface_hit,
                                   1.474*cgs::centimeter,
                                   1e-6 );
  FRENSIE_CHECK_EQUAL( surface_hit, 394 );

  // Advance the ray to the boundary surface
  bool reflection = particle.navigator().advanceToCellBoundary();

  FRENSIE_CHECK( !reflection );

  FRENSIE_CHECK_EQUAL( particle.getCell(), 83 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getTime(), 1.474, 1e-6 );

  distance_to_surface_hit = particle.navigator().fireRay( surface_hit );

  FRENSIE_CHECK_FLOATING_EQUALITY( distance_to_surface_hit,
                                   17.526*cgs::centimeter,
                                   1e-6 );
  FRENSIE_CHECK_EQUAL( surface_hit, 408 );

  // Advance the ray to the boundary surface (reflecting)
  double surface_normal[3];

  reflection = particle.navigator().advanceToCellBoundary( surface_normal );

  FRENSIE_CHECK( reflection );
  FRENSIE_CHECK_EQUAL( surface_normal[0], 0.0 );
  FRENSIE_CHECK_EQUAL( surface_normal[1], 0.0 );
  FRENSIE_CHECK_EQUAL( surface_normal[2], 1.0 );

  FRENSIE_CHECK_EQUAL( particle.getXDirection(), 0.0 );
  FRENSIE_CHECK_EQUAL( particle.getYDirection(), 0.0 );
  FRENSIE_CHECK_EQUAL( particle.getZDirection(), -1.0 );
  FRENSIE_CHECK_EQUAL( particle.getCell(), 83 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getTime(), 19.0, 1e-6 );
  
  distance_to_surface_hit = particle.navigator().fireRay( surface_hit );

  FRENSIE_CHECK_FLOATING_EQUALITY( distance_to_surface_hit,
                                   17.526*cgs::centimeter,
                                   1e-6 );
  FRENSIE_CHECK_EQUAL( surface_hit, 394 );
}

//---------------------------------------------------------------------------//
// Check that a particle state can be advanced after it's been embedded in
// a DagMC model
FRENSIE_UNIT_TEST( ParticleState, advance )
{
  TestParticleState particle( 1ull );
  particle.setPosition( -40.0, -40.0, 108.0 );
  particle.setDirection( 0.0, 0.0, 1.0 );

  particle.embedInModel( model );

  // If embedding fails the particle state will be set to lost or gone
  FRENSIE_REQUIRE( (bool)particle );

  // Advance past a reflecting surface
  particle.advance( 19.1 );

  FRENSIE_REQUIRE( (bool)particle );
  FRENSIE_CHECK_EQUAL( particle.getXPosition(), -40.0 );
  FRENSIE_CHECK_EQUAL( particle.getYPosition(), -40.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getZPosition(), 126.9, 1e-6 );
  FRENSIE_CHECK_EQUAL( particle.getXDirection(), 0.0 );
  FRENSIE_CHECK_EQUAL( particle.getYDirection(), 0.0 );
  FRENSIE_CHECK_EQUAL( particle.getZDirection(), -1.0 );
  FRENSIE_CHECK_EQUAL( particle.getCell(), 83 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getTime(), 19.1, 1e-6 );

  // Advance through a normal surface
  particle.setPosition( -40.0, -40.0, 59.0 );
  particle.setDirection( 0.0, 0.0, 1.0 );
  particle.setTime( 0.0 );

  FRENSIE_CHECK_EQUAL( particle.getCell(), 53 );
  
  particle.advance( 4.51 );

  FRENSIE_REQUIRE( (bool)particle );
  FRENSIE_CHECK_EQUAL( particle.getXPosition(), -40.0 );
  FRENSIE_CHECK_EQUAL( particle.getYPosition(), -40.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getZPosition(), 63.51, 1e-6 );
  FRENSIE_CHECK_EQUAL( particle.getXDirection(), 0.0 );
  FRENSIE_CHECK_EQUAL( particle.getYDirection(), 0.0 );
  FRENSIE_CHECK_EQUAL( particle.getZDirection(), 1.0 );
  FRENSIE_CHECK_EQUAL( particle.getCell(), 55 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getTime(), 4.51, 1e-6 );

  // Advance through the boundary of the model
  particle.setPosition( -40.0, -40.0, 59.0 );
  particle.setDirection( 0.0, 0.0, -1.0 );
  particle.setTime( 0.0 );
  particle.advance( 1e6 );

  FRENSIE_CHECK( particle.isGone() );
  FRENSIE_CHECK( !particle.isLost() );
  FRENSIE_CHECK_EQUAL( particle.getCell(), 188 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getTime(), 66.54, 1e-6 );
}

//---------------------------------------------------------------------------//
// Check that a particle state created using the copy constructor is
// embedded in the same geometry model
FRENSIE_UNIT_TEST( ParticleState, copy_constructor )
{
  TestParticleState particle( 1ull );
  particle.setPosition( -40.0, -40.0, 59.0 );
  particle.setDirection( 0.0, 0.0, 1.0 );

  particle.embedInModel( model );
  particle.advance( 4.51 );

  TestParticleState particle_copy( particle, true );

  FRENSIE_REQUIRE( (bool)particle_copy );
  FRENSIE_CHECK_EQUAL( particle_copy.getXPosition(), -40.0 );
  FRENSIE_CHECK_EQUAL( particle_copy.getYPosition(), -40.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle_copy.getZPosition(), 63.51, 1e-6 );
  FRENSIE_CHECK_EQUAL( particle_copy.getXDirection(), 0.0 );
  FRENSIE_CHECK_EQUAL( particle_copy.getYDirection(), 0.0 );
  FRENSIE_CHECK_EQUAL( particle_copy.getZDirection(), 1.0 );
  FRENSIE_CHECK_EQUAL( particle_copy.getCell(), 55 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle_copy.getTime(), 4.51, 1e-6 );

  particle_copy.advance( 1e6 );

  FRENSIE_CHECK( particle_copy.isGone() );
  FRENSIE_CHECK( !particle_copy.isLost() );
  FRENSIE_CHECK_EQUAL( particle_copy.getCell(), 188 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle_copy.getTime(), 202.54, 1e-6 );

  // The state of the original particle should be unchanged
  FRENSIE_REQUIRE( (bool)particle );
  FRENSIE_CHECK_EQUAL( particle.getXPosition(), -40.0 );
  FRENSIE_CHECK_EQUAL( particle.getYPosition(), -40.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getZPosition(), 63.51, 1e-6 );
  FRENSIE_CHECK_EQUAL( particle.getXDirection(), 0.0 );
  FRENSIE_CHECK_EQUAL( particle.getYDirection(), 0.0 );
  FRENSIE_CHECK_EQUAL( particle.getZDirection(), 1.0 );
  FRENSIE_CHECK_EQUAL( particle.getCell(), 55 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getTime(), 4.51, 1e-6 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_dagmc_geom_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_cad_file",
                                        test_dagmc_geom_file_name, "",
                                        "Test CAD file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  Geometry::DagMCModelProperties local_properties( test_dagmc_geom_file_name );
  
  local_properties.setTerminationCellPropertyName( "graveyard" );
  local_properties.setMaterialPropertyName( "mat" );
  local_properties.setDensityPropertyName( "rho" );
  local_properties.setEstimatorPropertyName( "tally" );
  
  model.reset( new Geometry::DagMCModel( local_properties ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstDagMCParticleState.cpp
//---------------------------------------------------------------------------//

