//---------------------------------------------------------------------------//
//!
//! \file   NativeGeometryInputValidator.hpp
//! \author Alex Robinson
//! \brief  Native geometry input file validator declaration.
//!
//---------------------------------------------------------------------------//

#ifndef NATIVE_GEOMETRY_INPUT_VALIDATOR_HPP
#define NATIVE_GEOMETRY_INPUT_VALIDATOR_HPP

// Std Lib Includes
#include <string>
#include <iostream>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_StandardParameterEntryValidators.hpp>
#include <Teuchos_ParameterList.hpp>

namespace FACEMC{

//! Native geometry input validator
class NativeGeometryInputValidator
{

public:

  //! Constructor 
  NativeGeometryInputValidator( const std::string& xml_input_file_name );

  //! Destructor
  ~NativeGeometryInputValidator()
  { /* ... */ }

  //! Validate the input file
  void validateInputs( const Teuchos::ParameterList& geometry_parameters );

private:

  // Append error message
  void appendErrorMessage( const char* message );

  // Validate the surfaces
  void validateSurfaces( const Teuchos::ParameterList& surfaces,
			 std::set<std::string>& surface_names );

  // Validate the surface name
  void validateSurfaceName( const std::string& surface_name )

  // Validate an individual surface
  void validateSurface( const Teuchos::ParameterList& surface,
			const std::string& surface_name );

  // Validate the surface type
  void validateSurfaceType( const std::string& surface_type,
			    const std::string& surface_name,
			    bool& valid_surface_type );

  // Validate the surface definition
  void validateSurfaceDefinition( 
			         const std::vector<double>& surface_definition,
				 const std::string& surface_type,
				 const std::string& surface_name );

  // Validate the surface special attribute
  void validateSurfaceSpecialAttribute( const std::string& surface_attribute,
					const std::string& surface_name )

  // Validate the cells
  void validateCells( const Teuchos::ParameterList& cells,
		      const std::set<std::string>& surface_names );
  
  // Validate an individual cell
  void validateCell( const Teuchos::ParameterList& cell,
		     const std::string& cell_name,
		     const std::set<std::string>& surface_names );

  // Validate the cell definition
  void validateCellDefinition( const std::string& cell_definition,
			       const std::string& cell_name,
			       const std::set<std::string>& surface_names );

  // Validate the cell material
  void validateCellMaterial( const std::string& cell_material,
			     const std::string& cell_name );

  // Validate the cell density
  void validateCellDensity( const double cell_density,
			    const std::string& cell_name );

  // Validate the cell special attribute
  void validateCellSpecialAttribute( const std::string& cell_attribute,
				     const std::string& cell_name );

  // The xml geometry input file name
  std::string d_xml_input_file_name;

  // The error message string
  std::string d_error_message;
};

} // end FACEMC namespace

#endif // end NATIVE_GEOMETRY_INPUT_VALIDATOR_HPP

//---------------------------------------------------------------------------//
// end NativeGeometryInputValidator.hpp
//---------------------------------------------------------------------------//
