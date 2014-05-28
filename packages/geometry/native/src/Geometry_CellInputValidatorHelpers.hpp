//---------------------------------------------------------------------------//
//!
//! \file   Geometry_CellInputValidatorHelpers.hpp
//! \author Alex Robinson
//! \brief  Cell input validator helper function declarations.
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_CELL_INPUT_VALIDATOR_HELPERS_HPP
#define GEOMETRY_CELL_INPUT_VALIDATOR_HELPERS_HPP

// Std Lib Includes
#include <string>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_ParameterList.hpp>

namespace Geometry{

//! Validate the cell name
void validateCellName( const std::string& cell_name );

//! Validate the cell definition
void validateCellDefinition( const std::string& cell_definition,
			     const std::string& cell_name,
			     const std::set<std::string>& surface_names );

//! Validate the cell material
void validateCellMaterial( const std::string& cell_material,
			   const std::string& cell_name );

//! Validate the cell density
void validateCellDensity( const double cell_density,
			  const std::string& cell_name );

//! Validate the cell special attribute
void validateCellSpecialAttribute( const std::string& cell_attribute,
				   const std::string& cell_name );

} // end Geometry namespace

#endif // end GEOMETRY_CELL_INPUT_VALIDATOR_HELPERS_HPP

//---------------------------------------------------------------------------//
// end Geometry_CellInputValidatorHelpers.hpp
//---------------------------------------------------------------------------//
