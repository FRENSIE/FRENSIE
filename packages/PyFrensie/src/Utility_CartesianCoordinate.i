//---------------------------------------------------------------------------//
//!
//! \file   Utility.CartesianCoordinate.i
//! \author Luke Kersting
//! \brief  The Cartesian Coordinate Conversion Policy classes interface file
//!
//---------------------------------------------------------------------------//

%{
// FRENSIE Includes
#include "Utility_CartesianSpatialCoordinateConversionPolicy.hpp"
#include "Utility_CartesianDirectionalCoordinateConversionPolicy.hpp"
#include "Utility_TranslationCartesianSpatialCoordinateConversionPolicy.hpp"
#include "Utility_GeneralCartesianSpatialCoordinateConversionPolicy.hpp"
#include "Utility_RotationCartesianCoordinateConversionPolicy.hpp"
#include "Utility_BasicCartesianCoordinateConversionPolicy.hpp"

// Add the Utility namespace to the global lookup scope
using namespace Utility;
%}

// Include typemaps support
%include <typemaps.i>

// Add a few general typemaps
%apply double& OUTPUT { double& primary_spatial_coord };
%apply double& OUTPUT { double& secondary_spatial_coord };
%apply double& OUTPUT { double& tertiary_spatial_coord };
%apply double& OUTPUT { double& primary_directional_coord };
%apply double& OUTPUT { double& secondary_directional_coord };
%apply double& OUTPUT { double& tertiary_directional_coord };

//---------------------------------------------------------------------------//
// Add support for the CartesianSpatialCoordinateSystemPolicy
//---------------------------------------------------------------------------//
// Import the CartesianSpatialCoordinateSystemPolicy
%include "Utility_CartesianSpatialCoordinateConversionPolicy.hpp"

%basic_spatial_coordinate_interface_setup( CartesianSpatialCoordinateConversionPolicy )

//---------------------------------------------------------------------------//
// Add support for the CartesianDirectionalCoordinateSystemPolicy
//---------------------------------------------------------------------------//
// Import the CartesianDirectionalCoordinateSystemPolicy
%include "Utility_CartesianDirectionalCoordinateConversionPolicy.hpp"

%basic_directional_coordinate_interface_setup( CartesianDirectionalCoordinateConversionPolicy )

//---------------------------------------------------------------------------//
// Add support for the TranslationCartesianSpatialCoordinateConversionPolicy
//---------------------------------------------------------------------------//
// Import the TranslationCartesianSpatialCoordinateConversionPolicy
%include "Utility_TranslationCartesianSpatialCoordinateConversionPolicy.hpp"

%translation_spatial_coordinate_interface_setup( TranslationCartesianSpatialCoordinateConversionPolicy )

//---------------------------------------------------------------------------//
// Add support for the GeneralCartesianSpatialCoordinateSystemPolicy
//---------------------------------------------------------------------------//
// Import the GeneralCartesianSpatialCoordinateSystemPolicy
%include "Utility_GeneralCartesianSpatialCoordinateConversionPolicy.hpp"

%general_spatial_coordinate_interface_setup( GeneralCartesianSpatialCoordinateConversionPolicy )

// ---------------------------------------------------------------------------//
// Add support for the RotationCartesianSpatialCoordinateConversionPolicy
// ---------------------------------------------------------------------------//
// Import the RotationCartesianSpatialCoordinateConversionPolicy
%include "Utility_RotationCartesianCoordinateConversionPolicy.hpp"

%rotation_coordinate_interface_setup( RotationCartesianCoordinateConversionPolicy )

// ---------------------------------------------------------------------------//
// Add support for the BasicCartesianSpatialCoordinateSystemPolicy
// ---------------------------------------------------------------------------//
// Import the BasicCartesianSpatialCoordinateSystemPolicy
%include "Utility_BasicCartesianCoordinateConversionPolicy.hpp"

%basic_coordinate_interface_setup( BasicCartesianCoordinateConversionPolicy )

//---------------------------------------------------------------------------//
// end Utility.CartesianCoordinate.i
//---------------------------------------------------------------------------//e
