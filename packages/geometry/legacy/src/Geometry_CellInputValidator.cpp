//---------------------------------------------------------------------------//
//!
//! \file   Geometry_CellInputValidator.cpp
//! \author Alex Robinson
//! \brief  Cell input validator definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <stdexcept>

// Trilinos Includes
#include <Teuchos_ParameterListExceptions.hpp>

// FRENSIE Includes
#include "Geometry_CellInputValidator.hpp"

namespace Geometry{

// Initialize the static members
std::set<std::string> CellInputValidator::material_names;
std::set<std::string> CellInputValidator::cell_names;
const std::string CellInputValidator::definition_parameter = "definition";
const std::string CellInputValidator::material_parameter = "material";
const std::string CellInputValidator::density_parameter = "density";
const std::string CellInputValidator::special_attribute_parameter =
  "special attribute";

// Validate individual cell
/*! \details All parameters in the cell parameter list will be tested. If any
 * errors are detected, they will be recorded and a std::invalid_argument
 * exception will be thrown.
 */
void CellInputValidator::validateCell(
				   const Teuchos::ParameterList& cell,
				   const std::string& name,
				   const std::set<std::string>& surface_names )
{
  std::string error_message;

  // Validate the cell name
  try{
    validateCellName( name );
  }
  catch( std::invalid_argument& cell_exception )
  {
    // record the error message
    error_message += cell_exception.what();
  }

  // See if the name already exists (record it if new)
  if( CellInputValidator::cell_names.count( name ) == 0 )
  {
    CellInputValidator::cell_names.insert( name  );
  }
  else
  {
    error_message += "Error: cell name \"";
    error_message += name;
    error_message += "\" appears multiple times.\n";
  }

  // Validate the cell definition
  try{
    validateCellDefinition(
	     cell.get<std::string>( CellInputValidator::definition_parameter ),
	     name,
	     surface_names );
  }
  // The definition hasn't been specified
  catch( Teuchos::Exceptions::InvalidParameter& parameterlist_exception )
  {
    // record the error message
    error_message += parameterlist_exception.what();
  }
  // The definition is invalid
  catch( std::invalid_argument& cell_exception )
  {
    // record the error message
    error_message += cell_exception.what();
  }

  // Validate the cell material
  bool material_defined = true;

  try{
    validateCellMaterial(
	     cell.get<std::string>( CellInputValidator::material_parameter ),
	     name );
  }
  // The material hasn't been specified (okay - optional argument)
  catch( Teuchos::Exceptions::InvalidParameter& parameterlist_exception )
  {
    material_defined = false;
  }
  // The material name is invalid
  catch( std::invalid_argument& cell_exception )
  {
    // record the error message
    error_message += cell_exception.what();
  }

  // Record the material
  if( material_defined )
  {
    CellInputValidator::material_names.insert(
	     cell.get<std::string>( CellInputValidator::material_parameter ) );
  }

  // Validate the cell density (if the material is defined)
  if( material_defined )
  {
    try{
      validateCellDensity(
		     cell.get<double>( CellInputValidator::density_parameter ),
		     name );
    }
    // The density hasn't been specified (okay if material not defined)
    catch( Teuchos::Exceptions::InvalidParameter& parameterlist_exception )
    {
      error_message += "Error in cell \"";
      error_message += name;
      error_message += "\": no density has been specified for material \"";
      error_message +=
	cell.get<std::string>( CellInputValidator::material_parameter );
      error_message += "\".\n";
    }
    // The density is invalid
    catch( std::invalid_argument& cell_exception )
    {
      // record the error message
      error_message +=  cell_exception.what();
    }
  }

  // Validate the cell special attribute
  try{
    validateCellSpecialAttribute(
      cell.get<std::string>( CellInputValidator::special_attribute_parameter ),
      name );
  }
  // The special attribute hasn't been specified (okay - optional argument)
  catch( Teuchos::Exceptions::InvalidParameter& parameterlist_exception ){}
  // The special attribute is invalid
  catch( std::invalid_argument& cell_exception )
  {
    // record the error message
    error_message +=  cell_exception.what();
  }

  // If any errors have occurred, throw
  if( error_message.size() > 0 )
  {
    throw std::invalid_argument( error_message );
  }
}

// Validate all cells
void CellInputValidator::validateAllCells(
				   const Teuchos::ParameterList& cells,
				   const std::set<std::string>& surface_names )
{
  std::string error_message;

  // Iterate over all cells in the cells parameter list
  Teuchos::ParameterList::ConstIterator parameter =
    cells.begin();
  Teuchos::ParameterList::ConstIterator end_parameter =
    cells.end();

  while( parameter != end_parameter )
  {
    const Teuchos::ParameterEntry& parameter_entry =
      cells.entry( parameter );

    // Every parameter must be a sublist
    if( !parameter_entry.isList() )
    {
      error_message += "Error: cell \"";
      error_message += cells.name( parameter );
      error_message += "\" must be a parameter list.\n";
    }
    else
    {
      const Teuchos::ParameterList& cell =
	Teuchos::getValue<Teuchos::ParameterList>( parameter_entry );

      // Validate the surface
      try{
	CellInputValidator::validateCell( cell,
					  cells.name( parameter ),
					  surface_names );
      }
      catch( std::invalid_argument& cell_exception )
      {
	// record the error message
	error_message += cell_exception.what();
      }
    }

    ++parameter;
  }

  // If any error occurred, throw
  if( error_message.size() > 0 )
  {
    throw std::invalid_argument( error_message );
  }
}

// Clear the material names
void CellInputValidator::clearMaterialNames()
{
  material_names.clear();
}

// Clear the cell names
void CellInputValidator::clearCellNames()
{
  cell_names.clear();
}

// Get the material names
const std::set<std::string>& CellInputValidator::getMaterialNames()
{
  return CellInputValidator::material_names;
}

// Get the cell names
const std::set<std::string>& CellInputValidator::getCellNames()
{
  return CellInputValidator::cell_names;
}

} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_CellInputValidator.cpp
//---------------------------------------------------------------------------//
