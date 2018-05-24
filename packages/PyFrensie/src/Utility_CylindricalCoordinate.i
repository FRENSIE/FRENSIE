//---------------------------------------------------------------------------//
//!
//! \file   Utility_CylindricalCoordinate.i
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

%basic_spatial_coordinate_interface_setup( CylindricalSpatialCoordinateConversionPolicy )

// Allow shared pointers of CylindricalSpatialCoordinateConversionPolicy objects
%shared_ptr( Utility::CylindricalSpatialCoordinateConversionPolicy );

// Import the CylindricalSpatialCoordinateConversionPolicy
%include "Utility_CylindricalSpatialCoordinateConversionPolicy.hpp"

//---------------------------------------------------------------------------//
// Add support for the TranslationCylindricalSpatialCoordinateConversionPolicy
//---------------------------------------------------------------------------//

%translation_spatial_coordinate_interface_setup( TranslationCylindricalSpatialCoordinateConversionPolicy )

// Allow shared pointers of TranslationCylindricalSpatialCoordinateConversionPolicy objects
%shared_ptr( Utility::TranslationCylindricalSpatialCoordinateConversionPolicy );

// Import the TranslationCylindricalSpatialCoordinateConversionPolicy
%include "Utility_TranslationCylindricalSpatialCoordinateConversionPolicy.hpp"

//---------------------------------------------------------------------------//
// Add support for the GeneralCylindricalSpatialCoordinateConversionPolicy
//---------------------------------------------------------------------------//

%general_spatial_coordinate_interface_setup( GeneralCylindricalSpatialCoordinateConversionPolicy )

// Allow shared pointers of GeneralCylindricalSpatialCoordinateConversionPolicyobjects
%shared_ptr( Utility::GeneralCylindricalSpatialCoordinateConversionPolicy);

// Import the GeneralCylindricalSpatialCoordinateConversionPolicy
%include "Utility_GeneralCylindricalSpatialCoordinateConversionPolicy.hpp"

// ---------------------------------------------------------------------------//
// Add support for the RotationCylindricalSpatialCoordinateConversionPolicy
// ---------------------------------------------------------------------------//

%rotation_spatial_coordinate_interface_setup( RotationCylindricalSpatialCoordinateConversionPolicy )

// Allow shared pointers of RotationCylindricalSpatialCoordinateConversionPolicy objects
%shared_ptr( Utility::RotationCylindricalSpatialCoordinateConversionPolicy );

// Import the RotationCylindricalSpatialCoordinateConversionPolicy
%include "Utility_RotationCylindricalSpatialCoordinateConversionPolicy.hpp"

// ---------------------------------------------------------------------------//
// Add support for the BasicCylindricalSpatialCoordinateConversionPolicy
// ---------------------------------------------------------------------------//

%basic_spatial_coordinate_interface_setup( BasicCylindricalSpatialCoordinateConversionPolicy )

// Allow shared pointers of BasicCylindricalSpatialCoordinateConversionPolicy objects
%shared_ptr( Utility::BasicCylindricalSpatialCoordinateConversionPolicy );

// Import the BasicCylindricalSpatialCoordinateConversionPolicy
%include "Utility_BasicCylindricalSpatialCoordinateConversionPolicy.hpp"

//---------------------------------------------------------------------------//
// end Utility_CylindricalCoordinate.i
//---------------------------------------------------------------------------//e
