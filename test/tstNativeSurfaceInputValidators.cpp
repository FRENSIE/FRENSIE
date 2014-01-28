//---------------------------------------------------------------------------//
//!
//! \file   tstNativeSurfaceInputValidators.cpp
//! \author Alex Robinson
//! \brief  Native surface input validator function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_UnitTestRepository.hpp>
#include <Teuchos_GlobalMPISession.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>

// FACEMC Includes
#include "NativeSurfaceInputValidators.hpp"

//---------------------------------------------------------------------------//
// Test XML File Name
//---------------------------------------------------------------------------//
std::string test_xml_file_name;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the surface name can be validated
TEUCHOS_UNIT_TEST( NativeSurfaceInputValidator, validateSurfaceName )
{
  std::string good_surface_name = "surface_A";
  std::string bad_surface_name = "surface A";

  TEST_NOTHROW( FACEMC::validateSurfaceName( good_surface_name ) );

  TEST_THROW( FACEMC::validateSurfaceName( bad_surface_name ),
	      std::invalid_argument );
}

//---------------------------------------------------------------------------//
// Check that the surface type can be validated
TEUCHOS_UNIT_TEST( NativeSurfaceInputValidator, validateSurfaceType )
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

  TEST_NOTHROW( FACEMC::validateSurfaceType( valid_surface_type_1,
					     surface_name ) );
  TEST_NOTHROW( FACEMC::validateSurfaceType( valid_surface_type_2,
					     surface_name ) );
  TEST_NOTHROW( FACEMC::validateSurfaceType( valid_surface_type_3,
					     surface_name ) );
  TEST_NOTHROW( FACEMC::validateSurfaceType( valid_surface_type_4,
					     surface_name ) );
  TEST_NOTHROW( FACEMC::validateSurfaceType( valid_surface_type_5,
					     surface_name ) );
  TEST_NOTHROW( FACEMC::validateSurfaceType( valid_surface_type_6,
					     surface_name ) );
  TEST_NOTHROW( FACEMC::validateSurfaceType( valid_surface_type_7,
					     surface_name ) );
  TEST_NOTHROW( FACEMC::validateSurfaceType( valid_surface_type_8,
					     surface_name ) );
  TEST_NOTHROW( FACEMC::validateSurfaceType( valid_surface_type_9,
					     surface_name ) );

  TEST_THROW( FACEMC::validateSurfaceType( invalid_surface_type,
					   surface_name ),
	      std::invalid_argument );
}

//---------------------------------------------------------------------------//
// Check that the surface definition can be validated
TEUCHOS_UNIT_TEST( NativeSurfaceInputValidator, validateSurfaceDefinition )
{
  std::string name = "test-surface";
  
  std::string x_plane = "x plane";
  Teuchos::Array<double> x_plane_valid_parameters( 1 );
  Teuchos::Array<double> x_plane_invalid_parameters( 2 );

  TEST_NOTHROW( FACEMC::validateSurfaceDefinition( x_plane_valid_parameters,
						   x_plane,
						   name ) );
  TEST_THROW( FACEMC::validateSurfaceDefinition( x_plane_invalid_parameters,
						 x_plane,
						 name ),
	      std::invalid_argument );

  std::string y_plane = "y plane";
  Teuchos::Array<double> y_plane_valid_parameters( 1 );
  Teuchos::Array<double> y_plane_invalid_parameters( 2 );

  TEST_NOTHROW( FACEMC::validateSurfaceDefinition( y_plane_valid_parameters,
						   y_plane,
						   name ) );
  TEST_THROW( FACEMC::validateSurfaceDefinition( y_plane_invalid_parameters,
						 y_plane,
						 name ),
	      std::invalid_argument );

  std::string z_plane = "z plane";
  Teuchos::Array<double> z_plane_valid_parameters( 1 );
  Teuchos::Array<double> z_plane_invalid_parameters( 2 );

  TEST_NOTHROW( FACEMC::validateSurfaceDefinition( z_plane_valid_parameters,
						   z_plane,
						   name ) );
  TEST_THROW( FACEMC::validateSurfaceDefinition( z_plane_invalid_parameters,
						 z_plane,
						 name ),
	      std::invalid_argument );
  
  std::string general_plane = "general plane";
  Teuchos::Array<double> general_plane_valid_parameters( 4 );
  Teuchos::Array<double> general_plane_invalid_parameters( 3 );

  TEST_NOTHROW( FACEMC::validateSurfaceDefinition( 
						general_plane_valid_parameters,
						general_plane,
						name ) );
  TEST_THROW( FACEMC::validateSurfaceDefinition( 
					      general_plane_invalid_parameters,
					      general_plane,
					      name ),
	      std::invalid_argument );
  
  std::string x_cylinder = "x cylinder";
  Teuchos::Array<double> x_cylinder_valid_parameters( 3 );
  Teuchos::Array<double> x_cylinder_invalid_parameters( 4 );

  TEST_NOTHROW( FACEMC::validateSurfaceDefinition( x_cylinder_valid_parameters,
						   x_cylinder,
						   name ) );
  TEST_THROW( FACEMC::validateSurfaceDefinition( x_cylinder_invalid_parameters,
						 x_cylinder,
						 name ),
	      std::invalid_argument );

  std::string y_cylinder = "y cylinder";
  Teuchos::Array<double> y_cylinder_valid_parameters( 3 );
  Teuchos::Array<double> y_cylinder_invalid_parameters( 4 );

  TEST_NOTHROW( FACEMC::validateSurfaceDefinition( y_cylinder_valid_parameters,
						   y_cylinder,
						   name ) );
  TEST_THROW( FACEMC::validateSurfaceDefinition( y_cylinder_invalid_parameters,
						 y_cylinder,
						 name ),
	      std::invalid_argument );
  
  std::string z_cylinder = "z cylinder";
  Teuchos::Array<double> z_cylinder_valid_parameters( 3 );
  Teuchos::Array<double> z_cylinder_invalid_parameters( 4 );

  TEST_NOTHROW( FACEMC::validateSurfaceDefinition( z_cylinder_valid_parameters,
						   z_cylinder,
						   name ) );
  TEST_THROW( FACEMC::validateSurfaceDefinition( z_cylinder_invalid_parameters,
						 z_cylinder,
						 name ),
	      std::invalid_argument );
  
  std::string sphere = "sphere";
  Teuchos::Array<double> sphere_valid_parameters( 4 );
  Teuchos::Array<double> sphere_invalid_parameters( 3 );

  TEST_NOTHROW( FACEMC::validateSurfaceDefinition( sphere_valid_parameters,
						   sphere,
						   name ) );
  TEST_THROW( FACEMC::validateSurfaceDefinition( sphere_invalid_parameters,
						 sphere,
						 name ),
	      std::invalid_argument );
  
  std::string general_surface = "general surface";
  Teuchos::Array<double> general_surface_valid_parameters( 10 );
  Teuchos::Array<double> general_surface_invalid_parameters( 9 );

  TEST_NOTHROW( FACEMC::validateSurfaceDefinition( 
					      general_surface_valid_parameters,
					      general_surface,
					      name ) );
  TEST_THROW( FACEMC::validateSurfaceDefinition( 
					    general_surface_invalid_parameters,
					    general_surface,
					    name ),
	      std::invalid_argument );
}

//---------------------------------------------------------------------------//
// Check that the surface special attribute can be validated
TEUCHOS_UNIT_TEST( NativeSurfaceInputValidator, 
		   validateSurfaceSpecialAttribute )
{
  std::string valid_surface_attribute = "reflecting";
  std::string invalid_surface_attribute = "white";

  TEST_NOTHROW( FACEMC::validateSurfaceSpecialAttribute( 
						       valid_surface_attribute,
						       "test:surface" ) );
  TEST_THROW( FACEMC::validateSurfaceSpecialAttribute( 
						     invalid_surface_attribute,
						     "test|surface" ),
	      std::invalid_argument );
}

//---------------------------------------------------------------------------//
// Check that an individual surface can be validated
TEUCHOS_UNIT_TEST( NativeSurfaceInputValidator, validateSurface )
{
  Teuchos::ParameterList valid_surface;

  valid_surface.set( "type", "x cylinder" );
  valid_surface.set<Teuchos::Array<double> >( "definition", 
					      Teuchos::tuple( 1.0, 1.0, 1.0 ));
  valid_surface.set( "special attribute", "reflecting" );
  
  TEST_NOTHROW( FACEMC::validateSurface( valid_surface, "test/surface" ) );

  Teuchos::ParameterList invalid_surface_1;

  TEST_THROW( FACEMC::validateSurface( invalid_surface_1, "test-surface" ),
	      std::invalid_argument );
  
  Teuchos::ParameterList invalid_surface_2;
  invalid_surface_2.set( "type", "y cylinder" );
  
  TEST_THROW( FACEMC::validateSurface( invalid_surface_2, "test-surface" ),
	      std::invalid_argument );

  Teuchos::ParameterList invalid_surface_3;
  invalid_surface_3.set( "type", "z cylinder" );
  invalid_surface_3.set<Teuchos::Array<double> >( "definition", 
						  Teuchos::tuple( 1.0 ) );

  TEST_THROW( FACEMC::validateSurface( invalid_surface_3, "test-surface" ),
	      std::invalid_argument );

  Teuchos::writeParameterListToXmlFile( valid_surface, "test.xml" );
}

//---------------------------------------------------------------------------//
// Check that a list of surfaces can be validated
TEUCHOS_UNIT_TEST( NativeSurfaceInputValidator, validateAllSurfaces )
{
  // Read in the parameter list from the xml file
  Teuchos::ParameterList surfaces;
  
  Teuchos::updateParametersFromXmlFile( test_xml_file_name, 
					Teuchos::inoutArg( surfaces ) );
  
  // Validate the surfaces
  TEST_NOTHROW( FACEMC::validateAllSurfaces( surfaces ) );
  
  // Print the parameter list
  surfaces.print();
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char* argv[] )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_xml_file",
		 &test_xml_file_name,
		 "Test xml file name with surfaces defined" );

  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );
}

//---------------------------------------------------------------------------//
// end tstNativeSurfaceInputValidators.cpp
//---------------------------------------------------------------------------//

