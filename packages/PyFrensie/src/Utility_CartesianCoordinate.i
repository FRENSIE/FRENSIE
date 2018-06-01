//---------------------------------------------------------------------------//
//!
//! \file   Utility_CartesianCoordinate.i
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

%basic_spatial_coordinate_interface_setup( CartesianSpatialCoordinateConversionPolicy )

// Allow shared pointers of CartesianSpatialCoordinateConversionPolicy objects
%shared_ptr( Utility::CartesianSpatialCoordinateConversionPolicy );

// Import the CartesianSpatialCoordinateSystemPolicy
%include "Utility_CartesianSpatialCoordinateConversionPolicy.hpp"

//---------------------------------------------------------------------------//
// Add support for the CartesianDirectionalCoordinateSystemPolicy
//---------------------------------------------------------------------------//

%basic_directional_coordinate_interface_setup( CartesianDirectionalCoordinateConversionPolicy )

// Allow shared pointers of CartesianDirectionalCoordinateConversionPolicy objects
%shared_ptr( Utility::CartesianDirectionalCoordinateConversionPolicy );

// Import the CartesianDirectionalCoordinateSystemPolicy
%include "Utility_CartesianDirectionalCoordinateConversionPolicy.hpp"

//---------------------------------------------------------------------------//
// Add support for the TranslationCartesianSpatialCoordinateConversionPolicy
//---------------------------------------------------------------------------//

%basic_spatial_coordinate_interface_setup( TranslationCartesianSpatialCoordinateConversionPolicy )

// Allow shared pointers of TranslationCartesianSpatialCoordinateConversionPolicy objects
%shared_ptr( Utility::TranslationCartesianSpatialCoordinateConversionPolicy );

// Import the TranslationCartesianSpatialCoordinateConversionPolicy
%include "Utility_TranslationCartesianSpatialCoordinateConversionPolicy.hpp"

//---------------------------------------------------------------------------//
// Add support for the GeneralCartesianSpatialCoordinateSystemPolicy
//---------------------------------------------------------------------------//

%basic_spatial_coordinate_interface_setup( GeneralCartesianSpatialCoordinateConversionPolicy )

// Allow shared pointers of GeneralCartesianSpatialCoordinateConversionPolicy objects
%shared_ptr( Utility::GeneralCartesianSpatialCoordinateConversionPolicy );

// Import the GeneralCartesianSpatialCoordinateSystemPolicy
%include "Utility_GeneralCartesianSpatialCoordinateConversionPolicy.hpp"

// ---------------------------------------------------------------------------//
// Add support for the RotationCartesianSpatialCoordinateConversionPolicy
// ---------------------------------------------------------------------------//

%rotation_coordinate_interface_setup( RotationCartesianCoordinateConversionPolicy )

// Allow shared pointers of RotationCartesianCoordinateConversionPolicy objects
%shared_ptr( Utility::RotationCartesianCoordinateConversionPolicy );

// Import the RotationCartesianSpatialCoordinateConversionPolicy
%include "Utility_RotationCartesianCoordinateConversionPolicy.hpp"

// ---------------------------------------------------------------------------//
// Add support for the BasicCartesianSpatialCoordinateSystemPolicy
// ---------------------------------------------------------------------------//

%basic_coordinate_interface_setup( BasicCartesianCoordinateConversionPolicy )

// Allow shared pointers of BasicCartesianCoordinateConversionPolicy objects
%shared_ptr( Utility::BasicCartesianCoordinateConversionPolicy );

// Import the BasicCartesianSpatialCoordinateSystemPolicy
%include "Utility_BasicCartesianCoordinateConversionPolicy.hpp"

//---------------------------------------------------------------------------//
// end Utility_CartesianCoordinate.i
//---------------------------------------------------------------------------//e
