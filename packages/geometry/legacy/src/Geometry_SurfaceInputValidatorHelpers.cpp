//---------------------------------------------------------------------------//
//!
//! \file   Geometry_SurfaceInputValidatorHelpers.cpp
//! \author Alex Robinson
//! \brief  Surface input validator helper function definitions.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <stdexcept>

// Trilinos Includes
#include <Teuchos_ParameterListExceptions.hpp>

// FRENSIE Includes
#include "Geometry_SurfaceInputValidatorHelpers.hpp"

namespace Geometry{

// Validate the surface name
/*! \details No empty spaces, (, ) or - characters are allowed in surface
 * names. If one is found, a std::invalid_argument exception is thrown. In
 * addition, the surface cannot be named "n" or "u". A
 * std::invalid_argument exception will be thrown if so.
 */
void validateSurfaceName( const std::string& surface_name )
{
  std::string error_message;

  // No empty spaces are allowed in surface names
  std::string::size_type empty_space_pos = surface_name.find( " " );

  if( empty_space_pos < surface_name.size() )
  {
    error_message += "Error in surface \"";
    error_message += surface_name;
    error_message += "\": spaces are not allowed in surface names.\n";
  }

  // No ( or ) characters are allowed in surface names
  std::string::size_type left_paren_pos = surface_name.find( "(" );
  std::string::size_type right_paren_pos = surface_name.find( ")" );

  if( left_paren_pos < surface_name.size() )
  {
    error_message += "Error in surface \"";
    error_message += surface_name;
    error_message += "\": ( characters are not allowed in surface names.\n";
  }

  if( right_paren_pos < surface_name.size() )
  {
    error_message += "Error in surface \"";
    error_message += surface_name;
    error_message += "\": ) characters are not allowed in surface names.\n";
  }

  // No - characters are allowed in surface names
  std::string::size_type minus_pos = surface_name.find( "-" );
  if( minus_pos < surface_name.size() )
  {
    error_message += "Error in surface \"";
    error_message += surface_name;
    error_message += "\": - characters are not allowed in surface names.\n";
  }

  // The name cannot be "n" or "u"
  if( surface_name.compare( "n" ) == 0 ||
      surface_name.compare( "u" ) == 0 )
  {
    error_message += "Error in surface \"";
    error_message += surface_name;
    error_message += "\": the name is reserved.\n";
  }

  // If any errors have occurred, throw
  if( error_message.size() > 0 )
  {
    throw std::invalid_argument( error_message );
  }
}

// Validate the surface type
/*! \details Only the following surface types are valid:
 * <ul>
 *  <li> x plane
 *  <li> y plane
 *  <li> z plane
 *  <li> general plane
 *  <li> x cylinder
 *  <li> y cylinder
 *  <li> z cylinder
 *  <li> sphere
 *  <li> general surface
 * </ul>
 * If any other type is specified, a std::invalid_argument exception is thrown.
 */
void validateSurfaceType( const std::string& surface_type,
			  const std::string& surface_name )
{
  bool valid_surface_type = false;

  if( surface_type.compare( "x plane" ) == 0 )
    valid_surface_type = true;
  else if( surface_type.compare( "y plane" ) == 0 )
    valid_surface_type = true;
  else if( surface_type.compare( "z plane" ) == 0 )
    valid_surface_type = true;
  else if( surface_type.compare( "general plane" ) == 0 )
    valid_surface_type = true;
  else if( surface_type.compare( "x cylinder" ) == 0 )
    valid_surface_type = true;
  else if( surface_type.compare( "y cylinder" ) == 0 )
    valid_surface_type = true;
  else if( surface_type.compare( "z cylinder" ) == 0 )
    valid_surface_type = true;
  else if( surface_type.compare( "sphere" ) == 0 )
    valid_surface_type = true;
  else if( surface_type.compare( "general surface" ) == 0 )
    valid_surface_type = true;

  // The surface type specified is invalid
  if( !valid_surface_type )
  {
    std::string error_message = "Error in surface \"";
    error_message += surface_name.c_str();
    error_message += "\": \"";
    error_message += surface_type.c_str();
    error_message += "\" does not name a surface type.\n";

    throw std::invalid_argument( error_message );
  }
}

// Validate the surface definition
/*! \details This function does not check if the surface is physically
 * reasonable - only that the correct number of arguments are specified for
 * the particular surface type. The required number of arguments are as
 * follows:
 * <ul>
 *  <li> x plane: 1
 *  <li> y plane: 1
 *  <li> z plane: 1
 *  <li> general plane: 4
 *  <li> x cylinder: 3
 *  <li> y cylinder: 3
 *  <li> z cylinder: 3
 *  <li> sphere: 4
 *  <li> general surface: 10
 * </ul>
 * If the number of parameters is not correct, a std::invalid_argument
 * exception is thrown.
 */
void validateSurfaceDefinition(
			      const Teuchos::Array<double>& surface_definition,
			      const std::string& surface_type,
			      const std::string& surface_name )
{
  // Create the potential error message template
  std::string error_message = "Error in surface \"";
  error_message += surface_name.c_str();
  error_message += "\": \"";
  error_message += surface_type.c_str();
  error_message += "\" ";

  // axis aligned planes only require a single input value
  if( surface_type.compare( "x plane" ) == 0 ||
      surface_type.compare( "y plane" ) == 0 ||
      surface_type.compare( "z plane" ) == 0 )
  {
    if( surface_definition.size() != 1 )
    {
      error_message += "requires 1 argument.\n";

      throw std::invalid_argument( error_message );
    }
  }
  else if( surface_type.compare( "x cylinder" ) == 0 ||
	   surface_type.compare( "y cylinder" ) == 0 ||
	   surface_type.compare( "z cylinder" ) == 0 )
  {
    if( surface_definition.size() != 3 )
    {
      error_message += "requires 3 arguments.\n";

      throw std::invalid_argument( error_message );
    }
  }
  else if( surface_type.compare( "general plane" ) == 0 ||
	   surface_type.compare( "sphere" ) == 0 )
  {
    if( surface_definition.size() != 4 )
    {
      error_message += "requires 4 arguments.\n";

      throw std::invalid_argument( error_message );
    }
  }
  else if( surface_type.compare( "general surface" ) == 0 )
  {
    if( surface_definition.size() != 10 )
    {
      error_message += "requires 10 arguments.\n";

      throw std::invalid_argument( error_message );
    }
  }
}

// Validate the surface special attribute
/*! \details Only one special attribute is currently accepted: reflecting.
 * Anything else will cause a std::invalid_argument exception to be thrown.
 */
void validateSurfaceSpecialAttribute( const std::string& surface_attribute,
				      const std::string& surface_name )
{
  if( surface_attribute.compare( "reflecting" ) != 0)
  {
    std::string error_message = "Error in surface \"";
    error_message += surface_name.c_str();
    error_message += "\": \"";
    error_message += surface_attribute.c_str();
    error_message += "\" is not a valid special attribute.\n";

    throw std::invalid_argument( error_message );
  }
}

} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_SurfaceInputValidatorHelpers.cpp
//---------------------------------------------------------------------------//
