//---------------------------------------------------------------------------//
//!
//! \file   Geometry_CellInputValidatorHelpers.hpp
//! \author Alex Robinson
//! \brief  Cell input validator helper function definitions
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Geometry_CellInputValidatorHelpers.hpp"

namespace Geometry{

// Validate the cell name
/*! \details No empty spaces are allowed in cell names. If one is found, a
 * std::invalid_argument exception is thrown.
 */
void validateCellName( const std::string& cell_name )
{
  std::string::size_type empty_space_pos = cell_name.find( " " );

  // No empty spaces are allowed in cell names
  if( empty_space_pos < cell_name.size() )
  {
    std::string error_message = "Error in cell \"";
    error_message += cell_name.c_str();
    error_message += "\": spaces are not allowed in cell names.\n";

    throw std::invalid_argument( error_message );
  }
}

// Validate the cell definition
/*! \details All surface names appearing in the cell definition must
 * correspond to defined surfaces (names must be in name set ). If a name is
 * found that does not correspond to a defined surface, a
 * std::invalid_argument exception is thrown.
 */
void validateCellDefinition( const std::string& cell_definition,
			     const std::string& cell_name,
			     const std::set<std::string>& surface_names )
{
  std::string error_message;

  // copy and remove (, ) and - characters from the cell definition
  std::string simplified_cell_definition( cell_definition );
  std::string special_characters( "()-" );

  unsigned operation_pos =
    simplified_cell_definition.find_first_of( special_characters );

  // Remove the special characters
  while( operation_pos < simplified_cell_definition.size() )
  {
    simplified_cell_definition[operation_pos] = ' ';

    operation_pos = cell_definition.find_first_of( special_characters,
						   operation_pos+1 );
  }

  // Remove leading and trailing white space
  unsigned start_pos = simplified_cell_definition.find_first_not_of( " " );
  unsigned end_pos = simplified_cell_definition.find_last_not_of( " " );

  if( start_pos > 0 )
    simplified_cell_definition.erase( 0, start_pos );

  if( end_pos+1 < simplified_cell_definition.size() )
  {
    simplified_cell_definition.erase(
				 end_pos+1,
				 simplified_cell_definition.size() -end_pos-1);
  }

  // Check that all surface names exists
  unsigned surface_name_start_pos = 0;
  unsigned surface_name_end_pos =
    simplified_cell_definition.find_first_of( " " );

  if( surface_name_end_pos > simplified_cell_definition.size() )
    surface_name_end_pos = simplified_cell_definition.size();

  while( surface_name_end_pos <= simplified_cell_definition.size() )
  {
    unsigned surface_name_size = surface_name_end_pos - surface_name_start_pos;

    std::string surface_name =
      simplified_cell_definition.substr( surface_name_start_pos,
					 surface_name_size );
    //std::cout << "\"" << surface_name << "\"" << std::endl;
    // Exclude the set operation characters and blank spaces
    if( surface_name.compare( "n" ) != 0 &&
	surface_name.compare( "u" ) != 0 &&
	surface_name.compare( " " ) != 0 &&
	surface_name.size() > 0 )
    {
      if( surface_names.count( surface_name ) == 0 )
      {
	error_message = "Error in cell \"";
	error_message += cell_name;
	error_message += "\" definition: surface \"";
	error_message += surface_name;
	error_message += "\" does not exists.\n";
      }
    }

    // Get the next surface name
    surface_name_start_pos = surface_name_end_pos+1;
    surface_name_end_pos =
      simplified_cell_definition.find( " ", surface_name_start_pos );

    if( surface_name_start_pos < simplified_cell_definition.size() &&
	surface_name_end_pos > simplified_cell_definition.size() )
    {
      surface_name_end_pos = simplified_cell_definition.size();
    }
  }

  // If any errors occurred, throw
  if( error_message.size() > 0 )
  {
    throw std::invalid_argument( error_message );
  }
}

// Validate the cell material
/*! \details No empty spaces are allowed in material names. If one is found, a
 * std::invalid_argument exception is thrown.
 */
void validateCellMaterial( const std::string& cell_material,
			   const std::string& cell_name )
{
  std::string::size_type empty_space_pos = cell_material.find( " " );

  // No empty spaces are allowed in material names
  if( empty_space_pos < cell_material.size() )
  {
    std::string error_message = "Error in cell \"";
    error_message += cell_name;
    error_message += "\": material name \"";
    error_message += cell_material;
    error_message += "\" contains spaces.\n";

    throw std::invalid_argument( error_message );
  }
}

// Validate the cell density
/*! \details The cell density must be positive and finite. If it is not, a
 * std::invalid_argument exception is thrown.
 */
void validateCellDensity( const double cell_density,
			  const std::string& cell_name )
{
  if( cell_density < 0 )
  {
    std::string error_message = "Error in cell \"";
    error_message += cell_name;
    error_message += "\": the cell density must be positive.\n";

    throw std::invalid_argument( error_message );
  }
  else if( Teuchos::ScalarTraits<double>::isnaninf( cell_density ) )
  {
    std::string error_message = "Error in cell \"";
    error_message += cell_name;
    error_message += "\": the cell density must be finite.\n";

    throw std::invalid_argument( error_message );
  }
}

// Validate the cell special attribute
/*! \details The following special attributes are valid:
 * <ul>
 *  <li> forced collision
 *  <li> graveyard
 * </ul>
 */
void validateCellSpecialAttribute( const std::string& cell_attribute,
				   const std::string& cell_name )
{
  bool valid_attribute = false;

  if( cell_attribute.compare( "forced collision" ) == 0 )
    valid_attribute = true;
  else if( cell_attribute.compare( "graveyard" ) == 0 )
    valid_attribute = true;

  // The special attribute is invalid
  if( !valid_attribute )
  {
    std::string error_message = "Error in cell \"";
    error_message += cell_name;
    error_message += "\": \"";
    error_message += cell_attribute;
    error_message += "\" is not a valid special attribute.\n";

    throw std::invalid_argument( error_message );
  }
}

} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_CellInputValidatorHelpers.cpp
//---------------------------------------------------------------------------//
