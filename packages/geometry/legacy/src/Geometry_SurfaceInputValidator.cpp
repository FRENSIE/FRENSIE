//---------------------------------------------------------------------------//
//!
//! \file   Geometry_SurfaceInputValidator.hpp
//! \author Alex Robinson
//! \brief  Surface input validator definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <stdexcept>

// Trilinos Includes
#include <Teuchos_ParameterListExceptions.hpp>

// FRENSIE Includes
#include "Geometry_SurfaceInputValidator.hpp"

namespace Geometry{

// Initialize the static members
const std::string SurfaceInputValidator::type_parameter = "type";
const std::string SurfaceInputValidator::definition_parameter = "definition";
const std::string SurfaceInputValidator::special_attribute_parameter =
  "special attribute";
std::set<std::string> SurfaceInputValidator::surface_names;

// Validate individual surface
/*! \details All parameters in the surface parameter list will be tested. If
 * any errors are detected, they will be recorded and a std::invalid_argument
 * exception will be thrown.
 */
void SurfaceInputValidator::validateSurface(
					 const Teuchos::ParameterList& surface,
					 const std::string name )
{
  std::string error_message;

  // Validate the surface name
  try{
    validateSurfaceName( name );
  }
  catch( std::invalid_argument& surface_exception )
  {
    // record the error message
    error_message += surface_exception.what();
  }

  // See if the name already exists (record it if new)
  if( SurfaceInputValidator::surface_names.count( name ) == 0 )
  {
    SurfaceInputValidator::surface_names.insert( name );
  }
  else
  {
    error_message += "Error: surface name \"";
    error_message += name;
    error_message += "\" appears multiple times.\n";
  }

  // Validate the surface type
  bool valid_surface_type = true;

  try{
    validateSurfaceType(
	     surface.get<std::string>( SurfaceInputValidator::type_parameter ),
	     name );
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
      validateSurfaceDefinition( surface.get<Teuchos::Array<double> >(
				 SurfaceInputValidator::definition_parameter ),
				 surface.get<std::string>( "type" ),
				 name );
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
                          surface.get<std::string>(
			  SurfaceInputValidator::special_attribute_parameter ),
			  name );
  }
  // No special attribute has been specified (okay - optional argument)
  catch( Teuchos::Exceptions::InvalidParameter& parameterlist_exception ){}
  // The special attribute is invalid
  catch( std::invalid_argument& surface_exception )
  {
    // record the error message
    error_message += surface_exception.what();
  }

  // If any errors have occurred, throw
  if( error_message.size() > 0 )
  {
    throw std::invalid_argument( error_message );
  }
}

// Validate all surfaces
/*! \details All surface names will be stored
 */
void SurfaceInputValidator::validateAllSurfaces(
				       const Teuchos::ParameterList& surfaces )
{
  std::string error_message;

  // Iterate over all surfaces defined in the surfaces parameter list
  Teuchos::ParameterList::ConstIterator parameter =
    surfaces.begin();
  Teuchos::ParameterList::ConstIterator end_parameter =
    surfaces.end();

  while( parameter != end_parameter )
  {
    const Teuchos::ParameterEntry& parameter_entry =
      surfaces.entry( parameter );

    // Every parameter must be a sublist
    if( !parameter_entry.isList() )
    {
      error_message += "Error: surface \"";
      error_message += surfaces.name( parameter );
      error_message +=  "\" must be a parameter list.\n";
    }
    else
    {
      const Teuchos::ParameterList& surface =
	Teuchos::getValue<Teuchos::ParameterList>( parameter_entry );

      // Validate the surface
      try{
	SurfaceInputValidator::validateSurface( surface,
						surfaces.name( parameter ) );
      }
      catch( std::invalid_argument& surface_exception )
      {
	// record the error message
	error_message += surface_exception.what();
      }
    }

    ++parameter;
  }

  // If any error occurred throw
  if( error_message.size() > 0 )
  {
    throw std::invalid_argument( error_message );
  }
}

// Clear the surface names
void SurfaceInputValidator::clearSurfaceNames()
{
  SurfaceInputValidator::surface_names.clear();
}

// Get the surface names
const std::set<std::string>& SurfaceInputValidator::getSurfaceNames()
{
  return SurfaceInputValidator::surface_names;
}

} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_SurfaceInputValidator.cpp
//---------------------------------------------------------------------------//
