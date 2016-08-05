//---------------------------------------------------------------------------//
//!
//! \file   tstSurfaceInputValidatorHelpers.cpp
//! \author Alex Robinson
//! \brief  Surface input validator helper function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Geometry_SurfaceInputValidatorHelpers.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the surface name can be validated
TEUCHOS_UNIT_TEST( SurfaceInputValidatorHelpers, validateSurfaceName )
{
  std::string good_surface_name = "surface_A";
  std::string bad_surface_name_1 = "surface A";
  std::string bad_surface_name_2 = "surface(A";
  std::string bad_surface_name_3 = "surface)A";
  std::string bad_surface_name_4 = "surface-A";
  std::string bad_surface_name_5 = "n";
  std::string bad_surface_name_6 = "u";

  TEST_NOTHROW( Geometry::validateSurfaceName( good_surface_name ) );

  TEST_THROW( Geometry::validateSurfaceName( bad_surface_name_1 ),
	      std::invalid_argument );
  TEST_THROW( Geometry::validateSurfaceName( bad_surface_name_2 ),
	      std::invalid_argument );
  TEST_THROW( Geometry::validateSurfaceName( bad_surface_name_3 ),
	      std::invalid_argument );
  TEST_THROW( Geometry::validateSurfaceName( bad_surface_name_4 ),
	      std::invalid_argument );
  TEST_THROW( Geometry::validateSurfaceName( bad_surface_name_5 ),
	      std::invalid_argument );
  TEST_THROW( Geometry::validateSurfaceName( bad_surface_name_6 ),
	      std::invalid_argument );
}

//---------------------------------------------------------------------------//
// Check that the surface type can be validated
TEUCHOS_UNIT_TEST( SurfaceInputValidatorHelpers, validateSurfaceType )
{
  std::string valid_surface_type_1 = "x plane";
  std::string valid_surface_type_2 = "y plane";
  std::string valid_surface_type_3 = "z plane";
  std::string valid_surface_type_4 = "general plane";
  std::string valid_surface_type_5 = "x cylinder";
  std::string valid_surface_type_6 = "y cylinder";
  std::string valid_surface_type_7 = "z cylinder";
  std::string valid_surface_type_8 = "sphere";
  std::string valid_surface_type_9 = "general surface";
  std::string invalid_surface_type = "torus";

  std::string surface_name = "test.surface";

  TEST_NOTHROW( Geometry::validateSurfaceType( valid_surface_type_1,
					     surface_name ) );
  TEST_NOTHROW( Geometry::validateSurfaceType( valid_surface_type_2,
					     surface_name ) );
  TEST_NOTHROW( Geometry::validateSurfaceType( valid_surface_type_3,
					     surface_name ) );
  TEST_NOTHROW( Geometry::validateSurfaceType( valid_surface_type_4,
					     surface_name ) );
  TEST_NOTHROW( Geometry::validateSurfaceType( valid_surface_type_5,
					     surface_name ) );
  TEST_NOTHROW( Geometry::validateSurfaceType( valid_surface_type_6,
					     surface_name ) );
  TEST_NOTHROW( Geometry::validateSurfaceType( valid_surface_type_7,
					     surface_name ) );
  TEST_NOTHROW( Geometry::validateSurfaceType( valid_surface_type_8,
					     surface_name ) );
  TEST_NOTHROW( Geometry::validateSurfaceType( valid_surface_type_9,
					     surface_name ) );

  TEST_THROW( Geometry::validateSurfaceType( invalid_surface_type,
					   surface_name ),
	      std::invalid_argument );
}

//---------------------------------------------------------------------------//
// Check that the surface definition can be validated
TEUCHOS_UNIT_TEST( SurfaceInputValidatorHelpers, validateSurfaceDefinition )
{
  std::string name = "test_surface";

  std::string x_plane = "x plane";
  Teuchos::Array<double> x_plane_valid_parameters( 1 );
  Teuchos::Array<double> x_plane_invalid_parameters( 2 );

  TEST_NOTHROW( Geometry::validateSurfaceDefinition( x_plane_valid_parameters,
						   x_plane,
						   name ) );
  TEST_THROW( Geometry::validateSurfaceDefinition( x_plane_invalid_parameters,
						 x_plane,
						 name ),
	      std::invalid_argument );

  std::string y_plane = "y plane";
  Teuchos::Array<double> y_plane_valid_parameters( 1 );
  Teuchos::Array<double> y_plane_invalid_parameters( 2 );

  TEST_NOTHROW( Geometry::validateSurfaceDefinition( y_plane_valid_parameters,
						   y_plane,
						   name ) );
  TEST_THROW( Geometry::validateSurfaceDefinition( y_plane_invalid_parameters,
						 y_plane,
						 name ),
	      std::invalid_argument );

  std::string z_plane = "z plane";
  Teuchos::Array<double> z_plane_valid_parameters( 1 );
  Teuchos::Array<double> z_plane_invalid_parameters( 2 );

  TEST_NOTHROW( Geometry::validateSurfaceDefinition( z_plane_valid_parameters,
						   z_plane,
						   name ) );
  TEST_THROW( Geometry::validateSurfaceDefinition( z_plane_invalid_parameters,
						 z_plane,
						 name ),
	      std::invalid_argument );

  std::string general_plane = "general plane";
  Teuchos::Array<double> general_plane_valid_parameters( 4 );
  Teuchos::Array<double> general_plane_invalid_parameters( 3 );

  TEST_NOTHROW( Geometry::validateSurfaceDefinition(
						general_plane_valid_parameters,
						general_plane,
						name ) );
  TEST_THROW( Geometry::validateSurfaceDefinition(
					      general_plane_invalid_parameters,
					      general_plane,
					      name ),
	      std::invalid_argument );

  std::string x_cylinder = "x cylinder";
  Teuchos::Array<double> x_cylinder_valid_parameters( 3 );
  Teuchos::Array<double> x_cylinder_invalid_parameters( 4 );

  TEST_NOTHROW( Geometry::validateSurfaceDefinition( x_cylinder_valid_parameters,
						   x_cylinder,
						   name ) );
  TEST_THROW( Geometry::validateSurfaceDefinition( x_cylinder_invalid_parameters,
						 x_cylinder,
						 name ),
	      std::invalid_argument );

  std::string y_cylinder = "y cylinder";
  Teuchos::Array<double> y_cylinder_valid_parameters( 3 );
  Teuchos::Array<double> y_cylinder_invalid_parameters( 4 );

  TEST_NOTHROW( Geometry::validateSurfaceDefinition( y_cylinder_valid_parameters,
						   y_cylinder,
						   name ) );
  TEST_THROW( Geometry::validateSurfaceDefinition( y_cylinder_invalid_parameters,
						 y_cylinder,
						 name ),
	      std::invalid_argument );

  std::string z_cylinder = "z cylinder";
  Teuchos::Array<double> z_cylinder_valid_parameters( 3 );
  Teuchos::Array<double> z_cylinder_invalid_parameters( 4 );

  TEST_NOTHROW( Geometry::validateSurfaceDefinition( z_cylinder_valid_parameters,
						   z_cylinder,
						   name ) );
  TEST_THROW( Geometry::validateSurfaceDefinition( z_cylinder_invalid_parameters,
						 z_cylinder,
						 name ),
	      std::invalid_argument );

  std::string sphere = "sphere";
  Teuchos::Array<double> sphere_valid_parameters( 4 );
  Teuchos::Array<double> sphere_invalid_parameters( 3 );

  TEST_NOTHROW( Geometry::validateSurfaceDefinition( sphere_valid_parameters,
						   sphere,
						   name ) );
  TEST_THROW( Geometry::validateSurfaceDefinition( sphere_invalid_parameters,
						 sphere,
						 name ),
	      std::invalid_argument );

  std::string general_surface = "general surface";
  Teuchos::Array<double> general_surface_valid_parameters( 10 );
  Teuchos::Array<double> general_surface_invalid_parameters( 9 );

  TEST_NOTHROW( Geometry::validateSurfaceDefinition(
					      general_surface_valid_parameters,
					      general_surface,
					      name ) );
  TEST_THROW( Geometry::validateSurfaceDefinition(
					    general_surface_invalid_parameters,
					    general_surface,
					    name ),
	      std::invalid_argument );
}

//---------------------------------------------------------------------------//
// Check that the surface special attribute can be validated
TEUCHOS_UNIT_TEST( SurfaceInputValidatorHelpers,
		   validateSurfaceSpecialAttribute )
{
  std::string valid_surface_attribute = "reflecting";
  std::string invalid_surface_attribute = "white";

  TEST_NOTHROW( Geometry::validateSurfaceSpecialAttribute(
						       valid_surface_attribute,
						       "test:surface" ) );
  TEST_THROW( Geometry::validateSurfaceSpecialAttribute(
						     invalid_surface_attribute,
						     "test|surface" ),
	      std::invalid_argument );
}

//---------------------------------------------------------------------------//
// end tstSurfaceInputValidatorHelpers.cpp
//---------------------------------------------------------------------------//

