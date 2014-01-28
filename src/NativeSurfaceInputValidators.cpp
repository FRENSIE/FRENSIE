//---------------------------------------------------------------------------//
//!
//! \file   NativeSurfaceInputValidators.cpp
//! \author Alex Robinson
//! \brief  Native surface input validator function definitions.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <stdexcept>

// Trilinos Includes
#include <Teuchos_ParameterListExceptions.hpp>

// FACEMC Includes
#include "NativeSurfaceInputValidators.hpp"

namespace FACEMC{

// Validate the surface name
/*! \details No empty spaces are allows in surface names. If one is found, a
 * std::invalid_argument exception is thrown.
 */ 
void validateSurfaceName( const std::string& surface_name )
{
  std::string::size_type empty_space_pos = surface_name.find( " " );
  
  // No empty spaces are allowed in surface names
  if( empty_space_pos < surface_name.size() )
  {
    std::string error_message = "Error in surface \"";
    error_message += surface_name.c_str();
    error_message += "\": spaces are not allows in surface names.\n";
    
    throw std::invalid_argument( error_message );
  }
}

// Validate the surface type
/*! \details Only the follow surface types are valid:
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
 * If any other type is specified, a std::invalid_argument excpetion is thrown.
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

// Validate an individual surface
/*! \details All parameters in the surface parameter list will be tested. If
 * any errors are detected, they will be recorded and a std::invalid_argument
 * exception will be thrown.
 */
void validateSurface( const Teuchos::ParameterList& surface,
		      const std::string& surface_name )
{
  std::string error_message;

  // Validate the surface type
  bool valid_surface_type = true;
  
  try{
    validateSurfaceType( surface.get<std::string>( "type" ), surface_name );
  }
  // The type hasn't been specified
  catch( Teuchos::Exceptions::InvalidParameter& parameterlist_exception )
  {
    // record the error message
    error_message += parameterlist_exception.what();
    
    valid_surface_type = false;
  }
  // The type is invalid
  catch( std::invalid_argument& surface_exception )
  {
    // record the error message
    error_message += surface_exception.what();
    
    valid_surface_type = false;
  }

  // Validate the surface definition
  if( valid_surface_type )
  {
    try{
      validateSurfaceDefinition( 
			  surface.get<Teuchos::Array<double> >( "definition" ),
			  surface.get<std::string>( "type" ),
			  surface_name );
    }
    // The definition hasn't been specified
    catch( Teuchos::Exceptions::InvalidParameter& parameterlist_exception )
    {
      // record the error message
      error_message += parameterlist_exception.what();
    }
    // The definition is invalid
    catch( std::invalid_argument& surface_exception )
    {
      // record the error message
      error_message += surface_exception.what();
    }
  }

  // Validate the surface special attribute
  try{
    validateSurfaceSpecialAttribute( 
			       surface.get<std::string>( "special attribute" ),
			       surface_name );
  }
  // No special attribute has been specified (okay - optional argument)
  catch( Teuchos::Exceptions::InvalidParameter& parameterlist_exception ){}
  // The special attribute is invalid
  catch( std::invalid_argument& surface_exception )
  {
    // record the error message
    error_message += surface_exception.what();
  }

  // If any errors have occured throw
  if( error_message.size() > 0 )
  {
    throw std::invalid_argument( error_message );
  }
}

// Validate all surfaces
void validateAllSurfaces( const Teuchos::ParameterList& all_surfaces )
{
  std::string error_message;

  // Iterate over all surfaces defined in the surfaces parameter list
  Teuchos::ParameterList::ConstIterator parameter =
    all_surfaces.begin();
  Teuchos::ParameterList::ConstIterator end_parameter = 
    all_surfaces.end();
  
  while( parameter != end_parameter )
  {
    const Teuchos::ParameterEntry& parameter_entry = 
      all_surfaces.entry( parameter );

    const std::string& parameter_name = 
      all_surfaces.name( parameter );

    // Every parameter must be a sublist
    if( !parameter_entry.isList() )
    {
      error_message += "Error: surface \"";
      error_message += parameter_name.c_str();
      error_message +=  "\" must be a parameter list.\n";
    }
    else
    {
      const Teuchos::ParameterList& surface = 
	Teuchos::getValue<Teuchos::ParameterList>( parameter_entry );

      // Validate the surface name
      try{
	validateSurfaceName( parameter_name );
      }
      catch( std::invalid_argument& surface_exception )
      {
	// record the error message
	error_message += surface_exception.what();
      }

      // Validate the surface
      try{
	validateSurface( surface, parameter_name );
      }
      catch( std::invalid_argument& surface_exception )
      {
	// record the error message
	error_message += surface_exception.what();
      }
      
      // If any error occurred throw
      if( error_message.size() > 0 )
      {
	throw std::invalid_argument( error_message );
      }				  
    }
    
    ++parameter;
  }
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end NativeSurfaceInputValidators.cpp
//---------------------------------------------------------------------------//
