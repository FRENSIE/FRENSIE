//---------------------------------------------------------------------------//
//! 
//! \file   NativeGeometryInputValidator.cpp
//! \author Alex Robinson
//! \brief  Native geometry input file validator definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <set>

// Trilinos Includes
#include <Teuchos_XMLParameterListCoreHelpers.hpp>

// FACEMC Includes
#include "NativeGeometryInputValidator.hpp"
#include "ContractException.hpp"

namespace FACEMC{

// Constructor
NativeGeometryInputValidator::NativeGeometryInputValidator( 
				       const std::string& xml_input_file_name )
  : d_xml_input_file_name( xml_input_file_name ),
    d_error_message(),
    d_parameter_list()
{ 
  // Make sure the input file name is valid
  testPrecondition( xml_input_file_name.size() > 0 );
}

// Validate the input file
/*! \details If errors are detected in the input file the error will be added
 * to the error message string. If the error message string is not empty at
 * the end of this function, a std::runtime_exception will be thrown whose 
 * message will contain the contents of the error message. If the input file
 * is valid the contents will be stored in a Teuchos::Parameter list.
 */
void NativeGeometryInputValidator::validateInputs( 
			    const Teuchos::ParameterList& geometry_parameters )
{
  // Append the contents of the xml file to the parameter list
  Teuchos::updateParametersFromXmlFile(geometry_parameters,
				       Teuchos::inoutArg(geometry_parameters));

  // Create the set which contains all surface names
  std::set<std::string> surface_names;

  // Check that the surfaces sublist is present 
  if( geometry_parameters.isSublist( "surfaces" ) )
  {
    Teuchos::ParameterList& surfaces = geometry_parameters.sublist("surfaces");

    // Check that each surface is defined properly
    validateSurfaces( surfaces, surface_names );
  }
  else
    appendErrorMessage( "Error: no sublist named surfaces present.\n" );
  

  // Check that the cells sublist is present
  if( geometry_parameters.isSublist( "cells" ) )
  {
    Teuchos::ParameterList& cells = geometry_parameters.sublist( "cells" );
    
    // Check that each cell is defined properly (if all surfaces are defined 
    // properly)
    if( d_error_message.size() == 0 )
      validateCells( cells, surface_names );
  }

  // If any errors occured, throw a runtime exception
  if( d_error_message.size() > 0 )
    throw std::runtime_exception( d_error_message );
}

// Append the error message
void NativeGeometryInputValidator::appendErrorMessage( const char* message )
{
  d_error_message += message;
}

// Validate the surfaces
void NativeGeometryInputValidator::validateSurfaces( 
					const Teuchos::ParameterList& surfaces,
					std::set<std::string>& surface_names )
{
  // Iterate over all surfaces defined in the surfaces parameter list
  Teuchos::ParameterList::ConstIterator surfaces_sublist_parameter = 
    surfaces.begin();
  Teuchos::ParameterList::ConstIterator surfaces_sublist_end = 
    surfaces.end();
  
  while( surfaces_sublist_parameter != surfaces_sublist_end )
  {
    const Teuchos::ParameterEnetry& surfaces_sublist_parameter_entry =
      surfaces.entry( surfaces_sublist_parameter );
    
    const std::string& surface_name = 
      surfaces.name( surfaces_sublist_parameter );
    
    // Every parameter must be a sublist
    if( !surfaces_sublist_parameter_entry.isList() )
    {
      appendErrorMessage( "Error: Surface " + surface_name.c_str() + 
			  " is not a sublist.\n" );
    }
    else
    {
      const Teuchos::ParameterList& surface = 
	Teuchos::getValue<Teuchos::ParameterList>( 
					    surfaces_sublist_parameter_entry );

      // Validate the surface name
      validateSurfaceName( surface_name );

      // Add the surface name to the surface name set
      surface_names.insert( surface_name );
      
      // Validate the surface
      validateSurface( surface, surface_name );
    }
    
    ++surfaces_sublist_parameter;
  }
}

// Validate the surface name
void NativeGeometryInputValidator::validateSurfaceName( 
					      const std::string& surface_name )
{
  
}

// Validate an individual surface
void NativeGeometryInputValidator::validateSurface( 
					 const Teuchos::ParameterList& surface,
					 const std::string& surface_name )
{
  // Check that the surface type is defined and valid
  bool valid_surface_type;
  
  if( surface.isParameter( "type" ) )
  {
    validateSurfaceType( surface.get<std::string>( "type" ),
			 surface_name,
			 valid_surface_type );	
  }
  else
  {
    appendErrorMessage( "Error in surface " + surface_name.c_str() +
			": the surface type must be specified.\n" );
  }

  // If the surface type is valid, check that the surface definition is 
  // defined and valid
  if( valid_surface_type )
  {
    if( surface.isParameter( "definition" ) )
    {
      validateSurfaceDefinition( 
			     surface.get<std::vector<double> >( "definition" ),
			     surface.get<std::string>( "type" ),
			     surface_name );
    }
    else
    {
      appendErrorMessage( "Error in surface " + surface_name.c_str() +
			  ": the surface definition must be specified.\n" );
    }
  }
    
  // Check if any special attributes have been specified (optional)
  if( surface.isParameter( "special attribute" ) )
  {
    validateSurfaceSpecialAttributes( 
	                     surface.get<std::string>( "special attribute" ) );
  }
}

// Validate the surface type
void NativeGeometryInputValidator::validateSurfaceType( 
					       const std::string& surface_type,
					       const std::string& surface_name,
					       bool& valid_surface_type )
{
  valid_surface_type = false;
    
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
  
  if( !valid_surface_type )
  {
    appendErrorMessage( "Error in surface " + surface_name.c_str() +
			": invalid surface type.\n" );
  }
}

// Validate the surface definition
// Note: this does not check if the surface is physically reasonable
void NativeGeometryInputValidator::validateSurfaceDefinition( 
			         const std::vector<double>& surface_definition,
				 const std::string& surface_type,
				 const std::string& surface_name )
{
  // axis aligned planes only require a single input value
  if( surface_type.compare( "x plane" ) == 0 || 
      surface_type.compare( "y plane" ) == 0 ||
      surface_type.compare( "z plane" ) == 0 )
  {
    if( surface_definition.size() != 1 )
    {
      appendErrorMessage( "Error in surface " + surface_name.c_str() +
			  ": 1 parameter should be given for surfaces " +
			  "of type " + surface_type.c_str() + ".\n" );
    }
  }
  else if( surface_type.compare( "x cylinder" ) == 0 ||
	   surface_type.compare( "y cylinder" ) == 0 ||
	   surface_type.compare( "z cylinder" ) == 0 )
  {
    if( surface_definition.size() != 3 )
    {
      appendErrorMessage( "Error in surface " + surface_name.c_str() +
			  ": 3 parameters should be given for surfaces " +
			  "of type " + surface_type.c_str() + ".\n" );
    }
  }
  else if( surface_type.compare( "general plane" ) == 0 ||
	   surface_type.compare( "sphere" ) == 0 )
  {
    if( surface_definition.size() != 4 )
    {
      appendErrorMessage( "Error in surface " + surface_name.c_str() +
			  ": 4 parameters should be given for surfaces " +
			  "of type " + surface_type.c_str() + ".\n" );
    }
  }
  else if( surface_type.compare( "general surface" ) == 0 )
  {
    if( surface_definition.size() != 10 )
    {
      appendErrorMessage( "Error in surface " + surface_name.c_str() +
			  ": 10 parameters should be given for surfaces " +
			  " of type " + surface_type.c_str() + ".\n" );
    }
  }
}

// Validate the surface special attributes
void NativeGeometryInputValidator::validateSurfaceSpecialAttributes(
					  const std::string& surface_attribute,
					  const std::string& surface_name )
{
  if( surface_attribute.compare( "reflecting" ) != 0)
  {
    appendErrorMessage( "Error in surface " + surface_name.c_str() +
			": invalid special attribute.\n" );
  }
}

// Validate the surfaces
void NativeGeometryInputValidator::validateCells( 
				   const Teuchos::ParameterList& cells,
				   const std::set<std::string>& surface_names )
{
  // Iterate over all cells defined in the cells parameter list
  Teuchos::ParameterList::ConstIterator cells_sublist_parameter = 
    cells.begin();
  Teuchos::ParameterList::ConstIterator cells_sublist_end = 
    cells.end();
  
  while( cells_sublist_parameter != cells_sublist_end )
  {
    const Teuchos::ParameterEnetry& cells_sublist_parameter_entry =
      cells.entry( cells_sublist_parameter );
    
    const std::string& cell_name = 
      cells.name( cells_sublist_parameter );
    
    // Every parameter must be a sublist
    if( !cells_sublist_parameter_entry.isList() )
    {
      appendErrorMessage( "Error: Cell " + cell_name.c_str() + 
			  " is not a sublist.\n" );
    }
    else
    {
      const Teuchos::ParameterList& cell = 
	Teuchos::getValue<Teuchos::ParameterList>( 
					    cells_sublist_parameter_entry );
      
      // Validate the cell
      validateCell( cell, cell_name, surface_names );
    }
    
    ++cells_sublist_parameter;
  }
}

// Validate an individual cell
void NativeGeometryInputValidator::validateCell( 
				   const Teuchos::ParameterList& cell,
				   const std::string& cell_name,
				   const std::set<std::string>& surface_names )
{
  // Check that the cell definition is valid
  if( cell.isParameter( "definition" ) )
  {
    validateCellDefinition( cell.get<std::string>( "definition" ),
			    cell_name,
			    surface_names );
  }
  else
  {
    appendErrorMessage( "Error in cell " + cell_name.c_str() +
			": the cell definition must be specified.\n" );
  }

  // Check if the cell material is valid (optional)
  if( cell.isParameter( "material" ) )
  {
    validateCellMaterial( cell.get<std::string>( "material" ), cell_name );
    
    // If the material is defined, a density must also be defined
    if( cell.isParameter( "density" ) )
      validateCellDensity( cell.get<double>( "density" ), cell_name );
    else
    {
      appendErrorMessage( "Error in cell " + cell_name.c_str() +
			  ": the cell density must be specified when a " +
			  "material is specified.\n" );
    }
  }
    
  // Check if the cell special attributes are valid (optional)
  if( cell.isParameter( "special attribute" ) )
  {
    validateCellSpecialAttributes(
			       surface.get<std::string>( "special attribute" );
  }
}

// Validate the cell definition
void NativeGeometryInputValidator::validateCellMaterial(
				   const std::string& cell_definition,
				   const std::string& cell_name,
				   const std::set<std::string>& surface_names )
{
  
}


} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end NativeGeomtryInputValidator.cpp
//---------------------------------------------------------------------------//
