//---------------------------------------------------------------------------//
//!
//! \file   NativeSurfaceInputValidators.hpp
//! \author Alex Robinson
//! \brief  Native surface input validator function declarations.
//!
//---------------------------------------------------------------------------//

#ifndef NATIVE_SURFACE_INPUT_VALIDATORS_HPP
#define NATIVE_SURFACE_INPUT_VALIDATORS_HPP

// Std Lib Includes
#include <string>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_ParameterList.hpp>

namespace FACEMC{

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

//! Validate an individual surface
void validateSurface( const Teuchos::ParameterList& surface,
		      const std::string& surface_name );

//! Validate all surfaces
void validateAllSurfaces( const Teuchos::ParameterList& all_surfaces );

} // end FACEMC namespace

#endif // end NATIVE_SURFACE_INPUT_VALIDATORS_HPP

//---------------------------------------------------------------------------//
// end NativeSurfaceInputValidators.hpp
//---------------------------------------------------------------------------//
