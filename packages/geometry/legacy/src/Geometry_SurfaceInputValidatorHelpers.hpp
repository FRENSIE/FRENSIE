//---------------------------------------------------------------------------//
//!
//! \file   Geometry_SurfaceInputValidatorHelpers.hpp
//! \author Alex Robinson
//! \brief  Surface input validator helper function declarations.
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_SURFACE_INPUT_VALIDATOR_HELPERS_HPP
#define GEOMETRY_SURFACE_INPUT_VALIDATOR_HELPERS_HPP

// Std Lib Includes
#include <string>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_ParameterList.hpp>

namespace Geometry{

//! Validate the surface name
void validateSurfaceName( const std::string& surface_name );

//! Validate the surface type
void validateSurfaceType( const std::string& surface_type,
			  const std::string& surface_name );

//! Validate the surface definition
void validateSurfaceDefinition(
			      const Teuchos::Array<double>& surface_definition,
			      const std::string& surface_type,
			      const std::string& surface_name );

//! Validate the surface special attribute
void validateSurfaceSpecialAttribute( const std::string& surface_attribute,
				      const std::string& surface_name );

} // end Geometry namespace

#endif // end GEOMETRY_SURFACE_INPUT_VALIDATOR_HELPERS_HPP

//---------------------------------------------------------------------------//
// end Geometry_SurfaceInputValidatorHelpers.hpp
//---------------------------------------------------------------------------//
