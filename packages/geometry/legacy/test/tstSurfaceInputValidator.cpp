//---------------------------------------------------------------------------//
//!
//! \file   tstSurfaceInputValidator.cpp
//! \author Alex Robinson
//! \brief  Surface input validator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_UnitTestRepository.hpp>
#include <Teuchos_GlobalMPISession.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>

// FRENSIE Includes
#include "Geometry_SurfaceInputValidator.hpp"

//---------------------------------------------------------------------------//
// Test XML File Name
//---------------------------------------------------------------------------//
std::string test_xml_file_name;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an individual surface can be validated
TEUCHOS_UNIT_TEST( SurfaceInputValidator, validateSurface )
{
  Teuchos::ParameterList valid_surface( "test/surface" );
  valid_surface.set( "type", "x cylinder" );
  valid_surface.set<Teuchos::Array<double> >( "definition",
					      Teuchos::tuple( 1.0, 1.0, 1.0 ));
  valid_surface.set( "special attribute", "reflecting" );

  TEST_NOTHROW( Geometry::SurfaceInputValidator::validateSurface(
						      valid_surface,
						      valid_surface.name() ) );

  Teuchos::ParameterList invalid_surface_1( "test_surface" );

  TEST_THROW( Geometry::SurfaceInputValidator::validateSurface(
						    invalid_surface_1,
						    invalid_surface_1.name() ),
	      std::invalid_argument );

  Teuchos::ParameterList invalid_surface_2( "test__surface" );
  invalid_surface_2.set( "type", "y cylinder" );

  TEST_THROW( Geometry::SurfaceInputValidator::validateSurface(
						    invalid_surface_2,
						    invalid_surface_2.name() ),
	      std::invalid_argument );

  Teuchos::ParameterList invalid_surface_3;
  invalid_surface_3.set( "type", "z cylinder" );
  invalid_surface_3.set<Teuchos::Array<double> >( "definition",
						  Teuchos::tuple( 1.0 ) );

  TEST_THROW( Geometry::SurfaceInputValidator::validateSurface(
						    invalid_surface_3,
						    invalid_surface_3.name() ),
	      std::invalid_argument );

  Geometry::SurfaceInputValidator::clearSurfaceNames();
}

//---------------------------------------------------------------------------//
// Check that a list of surfaces can be validated
TEUCHOS_UNIT_TEST( SurfaceInputValidator, validateAllSurfaces )
{
  // Read in the parameter list from the xml file
  Teuchos::ParameterList surfaces( "surfaces" );

  Teuchos::updateParametersFromXmlFile( test_xml_file_name,
					Teuchos::inoutArg( surfaces ) );

  // Validate the surfaces
  TEST_NOTHROW( Geometry::SurfaceInputValidator::validateAllSurfaces(surfaces) );

  // Print the parameter list
  surfaces.print();
}

//---------------------------------------------------------------------------//
// Check that the surface names can be recovered
TEUCHOS_UNIT_TEST( SurfaceInputValidator, getSurfaceNames )
{
  std::set<std::string> surface_names =
    Geometry::SurfaceInputValidator::getSurfaceNames();


  TEST_EQUALITY_CONST( surface_names.size(), 6 );
  TEST_ASSERT( surface_names.count( "plane_1" ) );
  TEST_ASSERT( surface_names.count( "plane_2" ) );
  TEST_ASSERT( surface_names.count( "cylinder_1" ) );
  TEST_ASSERT( surface_names.count( "general_plane_1" ) );
  TEST_ASSERT( surface_names.count( "sphere_1" ) );
  TEST_ASSERT( surface_names.count( "general_surface_1" ) );
  TEST_ASSERT( !surface_names.count( "no_such_surface" ) );
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
// end tstSurfaceInputValidator.cpp
//---------------------------------------------------------------------------//
