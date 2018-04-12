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
// Import the SphericalSpatialCoordinateConversionPolicy
%include "Utility_SphericalSpatialCoordinateConversionPolicy.hpp"

%basic_spatial_coordinate_interface_setup( SphericalSpatialCoordinateConversionPolicy )

//---------------------------------------------------------------------------//
// Add support for the SphericalDirectionalCoordinateConversionPolicy
//---------------------------------------------------------------------------//
// Import the SphericalDirectionalCoordinateConversionPolicy
%include "Utility_SphericalDirectionalCoordinateConversionPolicy.hpp"

%basic_directional_coordinate_interface_setup( SphericalDirectionalCoordinateConversionPolicy )

//---------------------------------------------------------------------------//
// Add support for the TranslationSphericalSpatialCoordinateConversionPolicy
//---------------------------------------------------------------------------//
// Import the TranslationSphericalSpatialCoordinateConversionPolicy
%include "Utility_TranslationSphericalSpatialCoordinateConversionPolicy.hpp"

%translation_spatial_coordinate_interface_setup( TranslationSphericalSpatialCoordinateConversionPolicy )

//---------------------------------------------------------------------------//
// Add support for the GeneralSphericalSpatialCoordinateConversionPolicy
//---------------------------------------------------------------------------//
// Import the GeneralSphericalSpatialCoordinateConversionPolicy
%include "Utility_GeneralSphericalSpatialCoordinateConversionPolicy.hpp"

%general_spatial_coordinate_interface_setup( GeneralSphericalSpatialCoordinateConversionPolicy )

// ---------------------------------------------------------------------------//
// Add support for the RotationSphericalSpatialCoordinateConversionPolicy
// ---------------------------------------------------------------------------//
// Import the RotationSphericalSpatialCoordinateConversionPolicy
%include "Utility_RotationSphericalCoordinateConversionPolicy.hpp"

%rotation_coordinate_interface_setup( RotationSphericalCoordinateConversionPolicy )

// ---------------------------------------------------------------------------//
// Add support for the BasicSphericalSpatialCoordinateConversionPolicy
// ---------------------------------------------------------------------------//
// Import the BasicSphericalSpatialCoordinateConversionPolicy
%include "Utility_BasicSphericalCoordinateConversionPolicy.hpp"

%basic_coordinate_interface_setup( BasicSphericalCoordinateConversionPolicy )

//---------------------------------------------------------------------------//
// end Utility_SphericalCoordinate.i
//---------------------------------------------------------------------------//e
