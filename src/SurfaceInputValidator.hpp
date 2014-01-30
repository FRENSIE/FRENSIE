//---------------------------------------------------------------------------//
//!
//! \file   SurfaceInputValidator.hpp
//! \author Alex Robinson
//! \brief  Surface input validator declaration.
//!
//---------------------------------------------------------------------------//

#ifndef SURFACE_INPUT_VALIDATOR_HPP
#define SURFACE_INPUT_VALIDATOR_HPP

// Std Lib Includes
#include <string>
#include <set>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>

// FACEMC Includes
#include "SurfaceInputValidatorHelpers.hpp"

namespace FACEMC{

//! Surface input validator
class SurfaceInputValidator
{

public:

  //! Validate individual surface
  static void validateSurface( const Teuchos::ParameterList& surface,
			       const std::string name );

  //! Validate all surfaces
  static void validateAllSurfaces( const Teuchos::ParameterList& surfaces );

  //! Clear the surface names
  static void clearSurfaceNames();

  //! Get the surface names
  static const std::set<std::string>& getSurfaceNames();

private:

  // Constructor
  SurfaceInputValidator()
  { /* ... */ }

  // Destructor
  ~SurfaceInputValidator()
  { /* ... */ }

  // The surface definition parameter name
  static const std::string type_parameter;
  
  // The surface definition parameter name
  static const std::string definition_parameter;

  // The special attribute parameter name
  static const std::string special_attribute_parameter;

  // The surface names encountered while validating surfaces (all at once)
  static std::set<std::string> surface_names;
};

} // end FACEMC namespace

#endif // end SURFACE_INPUT_VALIDATOR_HPP

//---------------------------------------------------------------------------//
// end SurfaceInputValidator.hpp
//---------------------------------------------------------------------------//
