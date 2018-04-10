//---------------------------------------------------------------------------//
//!
//! \file   Utility.SpatialCoordinate.i
//! \author Luke Kersting
//! \brief  The SpatialCoordinateConversionPolicy class interface file
//!
//---------------------------------------------------------------------------//

%{
// FRENSIE Includes
#include "Utility_CartesianSpatialCoordinateConversionPolicy.hpp"
#include "Utility_CartesianDirectionalCoordinateConversionPolicy.hpp"
#include "Utility_BasicCartesianCoordinateConversionPolicy.hpp"
#include "Utility_GeneralCartesianSpatialCoordinateConversionPolicy.hpp"

// Add the Utility namespace to the global lookup scope
using namespace Utility;
%}

// Include typemaps support
%include <typemaps.i>

// Include vector support
%include <std_vector.i>

// Add a few general templates
%template(DoubleVector) std::vector<double>;

// Add a few general typemaps
%apply double& OUTPUT { double& x_spatial_coord };
%apply double& OUTPUT { double& y_spatial_coord };
%apply double& OUTPUT { double& z_spatial_coord };
%apply double& OUTPUT { double& primary_spatial_coord };
%apply double& OUTPUT { double& secondary_spatial_coord };
%apply double& OUTPUT { double& tertiary_spatial_coord };
%apply double& OUTPUT { double& x_directional_coord };
%apply double& OUTPUT { double& y_directional_coord };
%apply double& OUTPUT { double& z_directional_coord };
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
// Add support for the GeneralCartesianSpatialCoordinateSystemPolicy
//---------------------------------------------------------------------------//
// Import the GeneralCartesianSpatialCoordinateSystemPolicy
%include "Utility_GeneralCartesianSpatialCoordinateConversionPolicy.hpp"

%extend Utility::GeneralCartesianSpatialCoordinateConversionPolicy
{
   GeneralCartesianSpatialCoordinateConversionPolicy(
    const std::vector<double> origin,
    const std::vector<double> axis )
  {
    return new Utility::GeneralCartesianSpatialCoordinateConversionPolicy(
      origin.data(), axis.data() );
  }
}

%basic_spatial_coordinate_interface_setup( GeneralCartesianSpatialCoordinateConversionPolicy )

// ---------------------------------------------------------------------------//
// Add support for the BasicCartesianSpatialCoordinateSystemPolicy
// ---------------------------------------------------------------------------//
// Import the BasicCartesianSpatialCoordinateSystemPolicy
%include "Utility_BasicCartesianCoordinateConversionPolicy.hpp"

%basic_coordinate_interface_setup( BasicCartesianCoordinateConversionPolicy )

//---------------------------------------------------------------------------//
// end Utility.CartesianCoordinate.i
//---------------------------------------------------------------------------//e
