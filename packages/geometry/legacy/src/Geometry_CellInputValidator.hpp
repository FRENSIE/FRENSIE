//---------------------------------------------------------------------------//
//!
//! \file   Geometry_CellInputValidator.hpp
//! \author Alex Robinson
//! \brief  Cell input validator declaration.
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_CELL_INPUT_VALIDATOR_HPP
#define GEOMETRY_CELL_INPUT_VALIDATOR_HPP

// Std Lib Includes
#include <string>
#include <set>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>

// FRENSIE Includes
#include "Geometry_CellInputValidatorHelpers.hpp"

namespace Geometry{

//! Cell input validator
class CellInputValidator
{

public:

  //! Validate individual cell
  static void validateCell( const Teuchos::ParameterList& cell,
			    const std::string& name,
			    const std::set<std::string>& surface_names );

  //! Validate all cells
  static void validateAllCells( const Teuchos::ParameterList& cells,
				const std::set<std::string>& surface_names );

  //! Clear the material names
  static void clearMaterialNames();

  //! Clear the cell names
  static void clearCellNames();

  //! Get the material names
  static const std::set<std::string>& getMaterialNames();

  //! Get the cell names
  static const std::set<std::string>& getCellNames();

private:

  // Constructor
  CellInputValidator()
  { /* ... */ }

  // Destructor
  ~CellInputValidator()
  { /* ... */ }

  // The cell definition parameter name
  static const std::string definition_parameter;

  // The cell material parameter name
  static const std::string material_parameter;

  // The cell density parameter name
  static const std::string density_parameter;

  // The cell special attribute parameter name
  static const std::string special_attribute_parameter;

  // The material names encountered while validating cells (all at once)
  static std::set<std::string> material_names;

  // The cell names encountered while validating cells (all at once)
  static std::set<std::string> cell_names;
};

} // end Geometry namespace

#endif // end GEOMETRY_CELL_INPUT_VALIDATOR_HPP

//---------------------------------------------------------------------------//
// end Geometry_CellInputValidator.hpp
//---------------------------------------------------------------------------//
