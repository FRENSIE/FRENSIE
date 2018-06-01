//---------------------------------------------------------------------------//
//!
//! \file   Utility_SphericalCoordinate.i
//! \author Luke Kersting
//! \brief  The Spherical Coordinate Conversion Policy classes interface file
//!
//---------------------------------------------------------------------------//

%{
// FRENSIE Includes
#include "Utility_SphericalSpatialCoordinateConversionPolicy.hpp"
#include "Utility_SphericalDirectionalCoordinateConversionPolicy.hpp"
#include "Utility_TranslationSphericalSpatialCoordinateConversionPolicy.hpp"
#include "Utility_GeneralSphericalSpatialCoordinateConversionPolicy.hpp"
#include "Utility_RotationSphericalCoordinateConversionPolicy.hpp"
#include "Utility_BasicSphericalCoordinateConversionPolicy.hpp"

// Add the Utility namespace to the global lookup scope
using namespace Utility;
%}

// Include typemaps support
%include <typemaps.i>

// Add a few general typemaps
%apply double& OUTPUT { double& r_spatial_coord };
%apply double& OUTPUT { double& theta_spatial_coord };
%apply double& OUTPUT { double& mu_spatial_coord };
%apply double& OUTPUT { double& r_directional_coord };
%apply double& OUTPUT { double& theta_directional_coord };
%apply double& OUTPUT { double& mu_directional_coord };

//---------------------------------------------------------------------------//
// Add support for the SphericalSpatialCoordinateConversionPolicy
//---------------------------------------------------------------------------//

%basic_spatial_coordinate_interface_setup( SphericalSpatialCoordinateConversionPolicy )

// Allow shared pointers of SphericalSpatialCoordinateConversionPolicy objects
%shared_ptr( Utility::SphericalSpatialCoordinateConversionPolicy );

// Import the SphericalSpatialCoordinateConversionPolicy
%include "Utility_SphericalSpatialCoordinateConversionPolicy.hpp"

//---------------------------------------------------------------------------//
// Add support for the SphericalDirectionalCoordinateConversionPolicy
//---------------------------------------------------------------------------//

%basic_directional_coordinate_interface_setup( SphericalDirectionalCoordinateConversionPolicy )

// Allow shared pointers of SphericalDirectionalCoordinateConversionPolicy objects
%shared_ptr( Utility::SphericalDirectionalCoordinateConversionPolicy );

// Import the SphericalDirectionalCoordinateConversionPolicy
%include "Utility_SphericalDirectionalCoordinateConversionPolicy.hpp"

//---------------------------------------------------------------------------//
// Add support for the TranslationSphericalSpatialCoordinateConversionPolicy
//---------------------------------------------------------------------------//

%translation_spatial_coordinate_interface_setup( TranslationSphericalSpatialCoordinateConversionPolicy )

// Allow shared pointers of TranslationSphericalSpatialCoordinateConversionPolicy objects
%shared_ptr( Utility::TranslationSphericalSpatialCoordinateConversionPolicy );

// Import the TranslationSphericalSpatialCoordinateConversionPolicy
%include "Utility_TranslationSphericalSpatialCoordinateConversionPolicy.hpp"

//---------------------------------------------------------------------------//
// Add support for the GeneralSphericalSpatialCoordinateConversionPolicy
//---------------------------------------------------------------------------//

%general_spatial_coordinate_interface_setup( GeneralSphericalSpatialCoordinateConversionPolicy )

// Allow shared pointers of GeneralSphericalSpatialCoordinateConversionPolicy objects
%shared_ptr( Utility::GeneralSphericalSpatialCoordinateConversionPolicy );

// Import the GeneralSphericalSpatialCoordinateConversionPolicy
%include "Utility_GeneralSphericalSpatialCoordinateConversionPolicy.hpp"

// ---------------------------------------------------------------------------//
// Add support for the RotationSphericalCoordinateConversionPolicy
// ---------------------------------------------------------------------------//

%rotation_coordinate_interface_setup( RotationSphericalCoordinateConversionPolicy )

// Allow shared pointers of RotationSphericalCoordinateConversionPolicy objects
%shared_ptr( Utility::RotationSphericalCoordinateConversionPolicy );

// Import the RotationSphericalCoordinateConversionPolicy
%include "Utility_RotationSphericalCoordinateConversionPolicy.hpp"

// ---------------------------------------------------------------------------//
// Add support for the BasicSphericalCoordinateConversionPolicy
// ---------------------------------------------------------------------------//

%basic_coordinate_interface_setup( BasicSphericalCoordinateConversionPolicy )

// Allow shared pointers of BasicSphericalCoordinateConversionPolicy objects
%shared_ptr( Utility::BasicSphericalCoordinateConversionPolicy );

// Import the BasicSphericalCoordinateConversionPolicy
%include "Utility_BasicSphericalCoordinateConversionPolicy.hpp"

//---------------------------------------------------------------------------//
// end Utility_SphericalCoordinate.i
//---------------------------------------------------------------------------//e
