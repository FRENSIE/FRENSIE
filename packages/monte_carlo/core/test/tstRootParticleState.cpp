//---------------------------------------------------------------------------//
//!
//! \file   tstRootParticleState.cpp
//! \author Alex Robinson
//! \brief  Particle state unit tests using Root navigators
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_ParticleState.hpp"
#include "Geometry_RootNavigator.hpp"
#include "Geometry_RootModel.hpp"
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
std::shared_ptr<const Geometry::RootModel> model;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a particle state can be embedded in a Root model
FRENSIE_UNIT_TEST( ParticleState, embedInModel )
{
  TestParticleState particle( 1ull );
  particle.setPosition( 0.0, 0.0, 0.0 );
  particle.setDirection( 0.0, 0.0, 1.0 );
  
  particle.embedInModel( model );

  // If embedding fails the particle state will be set to lost or gone
  FRENSIE_REQUIRE( (bool)particle );

  // Verify that the particle position and direction are unchanged
  FRENSIE_CHECK_EQUAL( particle.getXPosition(), 0.0 );
  FRENSIE_CHECK_EQUAL( particle.getYPosition(), 0.0 );
  FRENSIE_CHECK_EQUAL( particle.getZPosition(), 0.0 );
  FRENSIE_CHECK_EQUAL( particle.getXDirection(), 0.0 );
  FRENSIE_CHECK_EQUAL( particle.getYDirection(), 0.0 );
  FRENSIE_CHECK_EQUAL( particle.getZDirection(), 1.0 );

  // Check that that particle can move through the geometry
  FRENSIE_CHECK_EQUAL( particle.getCell(), 2 );
  
  Geometry::Navigator::Length distance_to_boundary =
    particle.navigator().fireRay();

  FRENSIE_CHECK_FLOATING_EQUALITY( distance_to_boundary,
                                   2.5*cgs::centimeter,
                                   1e-9 );

  double surface_normal[3];

  particle.navigator().advanceToCellBoundary( surface_normal );

  FRENSIE_CHECK_EQUAL( surface_normal[0], 0.0 );
  FRENSIE_CHECK_EQUAL( surface_normal[1], 0.0 );
  FRENSIE_CHECK_EQUAL( surface_normal[2], 1.0 );
  FRENSIE_CHECK_EQUAL( particle.getCell(), 1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getTime(), 2.5, 1e-6 );

  distance_to_boundary = particle.navigator().fireRay();

  FRENSIE_CHECK_FLOATING_EQUALITY( distance_to_boundary,
                                   2.5*cgs::centimeter,
                                   1e-6 );

  particle.navigator().advanceBySubstep( 0.5*distance_to_boundary );

  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getTime(), 3.75, 1e-6 );
  
  particle.navigator().changeDirection( 0.0, 1.0, 0.0 );

  distance_to_boundary = particle.navigator().fireRay();

  FRENSIE_CHECK_FLOATING_EQUALITY( distance_to_boundary,
                                   5.0*cgs::centimeter,
                                   1e-9 );

  particle.navigator().advanceToCellBoundary();

  FRENSIE_CHECK_EQUAL( particle.getCell(), 3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getTime(), 8.75, 1e-6 );
}

//---------------------------------------------------------------------------//
// Check that a particle state can be advanced after it's been embedded in
// a Root model
FRENSIE_UNIT_TEST( ParticleState, advance )
{
  TestParticleState particle( 1ull );
  particle.setPosition( 0.0, 0.0, 0.0 );
  particle.setDirection( 0.0, 0.0, 1.0 );
  
  particle.embedInModel( model );

  FRENSIE_REQUIRE( (bool)particle );

  particle.advance( 3.75 );

  FRENSIE_REQUIRE( (bool)particle )
  FRENSIE_CHECK_EQUAL( particle.getXPosition(), 0.0 );
  FRENSIE_CHECK_EQUAL( particle.getYPosition(), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getZPosition(), 3.75, 1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getTime(), 3.75, 1e-6 );
  FRENSIE_CHECK_EQUAL( particle.getCell(), 1 );

  particle.setDirection( 0.0, 1.0, 0.0 );

  // Advance through the boundary of the model
  particle.advance( 5.1 );

  FRENSIE_CHECK( particle.isGone() );
  FRENSIE_CHECK( !particle.isLost() );
  FRENSIE_CHECK_EQUAL( particle.getXPosition(), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getYPosition(), 5.0, 1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getZPosition(), 3.75, 1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getTime(), 8.75, 1e-6 );
  FRENSIE_CHECK_EQUAL( particle.getCell(), 3 );
}

//---------------------------------------------------------------------------//
// Check that a particle state created using the copy constructor is
// embedded in the same geometry model
FRENSIE_UNIT_TEST( ParticleState, copy_constructor )
{
  TestParticleState particle( 1ull );
  particle.setPosition( 0.0, 0.0, 0.0 );
  particle.setDirection( 0.0, 0.0, 1.0 );
  
  particle.embedInModel( model );
  particle.advance( 3.75 );

  TestParticleState particle_copy( particle, true );

  FRENSIE_REQUIRE( (bool)particle_copy )
  FRENSIE_CHECK_EQUAL( particle_copy.getXPosition(), 0.0 );
  FRENSIE_CHECK_EQUAL( particle_copy.getYPosition(), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle_copy.getZPosition(), 3.75, 1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle_copy.getTime(), 3.75, 1e-6 );
  FRENSIE_CHECK_EQUAL( particle_copy.getCell(), 1 );

  particle_copy.setDirection( 0.0, 1.0, 0.0 );

  particle_copy.advance( 5.1 );

  FRENSIE_CHECK( particle_copy.isGone() );
  FRENSIE_CHECK( !particle_copy.isLost() );
  FRENSIE_CHECK_EQUAL( particle_copy.getXPosition(), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle_copy.getYPosition(), 5.0, 1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle_copy.getZPosition(), 3.75, 1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle_copy.getTime(), 8.75, 1e-6 );
  FRENSIE_CHECK_EQUAL( particle_copy.getCell(), 3 );

  // The state of the original particle should be unchanged
  FRENSIE_REQUIRE( (bool)particle );
  FRENSIE_CHECK_EQUAL( particle.getXPosition(), 0.0 );
  FRENSIE_CHECK_EQUAL( particle.getYPosition(), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getZPosition(), 3.75, 1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( particle.getTime(), 3.75, 1e-6 );
  FRENSIE_CHECK_EQUAL( particle.getCell(), 1 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_root_geom_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_root_file",
                                        test_root_geom_file_name, "",
                                        "Test ROOT file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  Geometry::RootModelProperties local_properties( test_root_geom_file_name );
  
  std::shared_ptr<Geometry::RootModel> tmp_model =
    Geometry::RootModel::getInstance();

  tmp_model->initialize( local_properties );

  model = tmp_model;
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstRootParticleState.cpp
//---------------------------------------------------------------------------//
