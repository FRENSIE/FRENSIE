//---------------------------------------------------------------------------//
//!
//! \file   Utility.CylindricalCoordinate.i
//! \author Luke Kersting
//! \brief  The Cylindrical Coordinate Conversion Policy classes interface file
//!
//---------------------------------------------------------------------------//

%{
// FRENSIE Includes
#include "Utility_CylindricalSpatialCoordinateConversionPolicy.hpp"
#include "Utility_TranslationCylindricalSpatialCoordinateConversionPolicy.hpp"
#include "Utility_GeneralCylindricalSpatialCoordinateConversionPolicy.hpp"
#include "Utility_RotationCylindricalSpatialCoordinateConversionPolicy.hpp"
#include "Utility_BasicCylindricalSpatialCoordinateConversionPolicy.hpp"

// Add the Utility namespace to the global lookup scope
using namespace Utility;
%}

// Include typemaps support
%include <typemaps.i>

// Add a few general typemaps
%apply double& OUTPUT { double& r_spatial_coord };
%apply double& OUTPUT { double& theta_spatial_coord };
%apply double& OUTPUT { double& z_spatial_coord };

//---------------------------------------------------------------------------//
// Add support for the CylindricalSpatialCoordinateConversionPolicy
//---------------------------------------------------------------------------//
// Import the CylindricalSpatialCoordinateConversionPolicy
%include "Utility_CylindricalSpatialCoordinateConversionPolicy.hpp"

%basic_spatial_coordinate_interface_setup( CylindricalSpatialCoordinateConversionPolicy )

//---------------------------------------------------------------------------//
// Add support for the TranslationCylindricalSpatialCoordinateConversionPolicy
//---------------------------------------------------------------------------//
// Import the TranslationCylindricalSpatialCoordinateConversionPolicy
%include "Utility_TranslationCylindricalSpatialCoordinateConversionPolicy.hpp"

%translation_spatial_coordinate_interface_setup( TranslationCylindricalSpatialCoordinateConversionPolicy )

//---------------------------------------------------------------------------//
// Add support for the GeneralCylindricalSpatialCoordinateConversionPolicy
//---------------------------------------------------------------------------//
// Import the GeneralCylindricalSpatialCoordinateConversionPolicy
%include "Utility_GeneralCylindricalSpatialCoordinateConversionPolicy.hpp"

%general_spatial_coordinate_interface_setup( GeneralCylindricalSpatialCoordinateConversionPolicy )

// ---------------------------------------------------------------------------//
// Add support for the RotationCylindricalSpatialCoordinateConversionPolicy
// ---------------------------------------------------------------------------//
// Import the RotationCylindricalSpatialCoordinateConversionPolicy
%include "Utility_RotationCylindricalSpatialCoordinateConversionPolicy.hpp"

%rotation_spatial_coordinate_interface_setup( RotationCylindricalSpatialCoordinateConversionPolicy )

// ---------------------------------------------------------------------------//
// Add support for the BasicCylindricalSpatialCoordinateConversionPolicy
// ---------------------------------------------------------------------------//
// Import the BasicCylindricalSpatialCoordinateConversionPolicy
%include "Utility_BasicCylindricalSpatialCoordinateConversionPolicy.hpp"

%basic_spatial_coordinate_interface_setup( BasicCylindricalSpatialCoordinateConversionPolicy )

//---------------------------------------------------------------------------//
// end Utility.CylindricalCoordinate.i
//---------------------------------------------------------------------------//e
