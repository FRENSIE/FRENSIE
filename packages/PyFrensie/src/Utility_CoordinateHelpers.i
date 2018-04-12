//---------------------------------------------------------------------------//
//!
//! \file   Utility_CoordinateHelpers.i
//! \author Luke Kersting
//! \brief  The distribution helper macros
//!
//---------------------------------------------------------------------------//

// Include vector support
%include <std_vector.i>

// Add a few general templates
%template(DoubleVector) std::vector<double>;

// Add a few general typemaps
%apply double& OUTPUT { double& x_spatial_coord };
%apply double& OUTPUT { double& y_spatial_coord };
%apply double& OUTPUT { double& z_spatial_coord };
%apply double& OUTPUT { double& x_directional_coord };
%apply double& OUTPUT { double& y_directional_coord };
%apply double& OUTPUT { double& z_directional_coord };

//---------------------------------------------------------------------------//
// Helper macro for setting up a basic SpatialCoordinateConversionPolicy class python interface
//---------------------------------------------------------------------------//
%define %basic_spatial_coordinate_interface_setup_helper( DISTRIBUTION )

%feature("docstring") Utility::DISTRIBUTION
"The DISTRIBUTION proxy class. This class can convert spatial coordinates."

%feature("autodoc",
"getLocalSpatialCoordinateSystemType(DISTRIBUTION self) -> SpatialCoordinateSystemType" )
Utility::DISTRIBUTION::getLocalSpatialCoordinateSystemType;

%feature("autodoc",
"isPrimarySpatialCoordinateValid(DISTRIBUTION self, double coordinate ) -> bool" )
Utility::DISTRIBUTION::isPrimarySpatialCoordinateValid;

%feature("autodoc",
"isSecondarySpatialCoordinateValid(DISTRIBUTION self, double coordinate ) -> bool" )
Utility::DISTRIBUTION::isSecondarySpatialCoordinateValid;

%feature("autodoc",
"isTertiarySpatialCoordinateValid(DISTRIBUTION self, double coordinate ) -> bool" )
Utility::DISTRIBUTION::isTertiarySpatialCoordinateValid;

%feature("autodoc",
"convertToCartesianSpatialCoordinates(DISTRIBUTION self, double primary_spatial_coord, double secondary_spatial_coord, double tertiary_spatial_coord ) -> double, double, double

Convert the spatial coordinates to cartesian coordinates. The first element of
the returned tuple is the x_spatial_coord. The first element of
the returned tuple is the y_spatial_coord. The first element of
the returned tuple is the z_spatial_coord. ")
Utility::DISTRIBUTION::convertToCartesianSpatialCoordinates;

%ignore Utility::DISTRIBUTION::convertToCartesianSpatialCoordinates( double[3], double[3] );

%feature("autodoc",
"convertFromCartesianSpatialCoordinates(DISTRIBUTION self, double x_spatial_coord, double y_spatial_coord, double z_spatial_coord ) -> double, double, double

Convert the spatial coordinates to cartesian coordinates. The first element of
the returned tuple is the primary_spatial_coord. The first element of
the returned tuple is the secondary_spatial_coord. The first element of
the returned tuple is the tertiary_spatial_coord. ")
Utility::DISTRIBUTION::convertFromCartesianSpatialCoordinates;

%ignore Utility::DISTRIBUTION::convertFromCartesianSpatialCoordinates( double[3], double[3] );

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up a basic DirectionalCoordinateConversionPolicy class python interface
//---------------------------------------------------------------------------//
%define %basic_directional_coordinate_interface_setup_helper( DISTRIBUTION )

%feature("docstring") Utility::DISTRIBUTION
"The DISTRIBUTION proxy class. This class can convert directional coordinates."

%feature("autodoc",
"getLocalDirectionalCoordinateSystemType(DISTRIBUTION self) -> DirectionalCoordinateSystemType" )
Utility::DISTRIBUTION::getLocalDirectionalCoordinateSystemType;

%feature("autodoc",
"isPrimaryDirectionalCoordinateValid(DISTRIBUTION self, double coordinate ) -> bool" )
Utility::DISTRIBUTION::isPrimaryDirectionalCoordinateValid;

%feature("autodoc",
"isSecondaryDirectionalCoordinateValid(DISTRIBUTION self, double coordinate ) -> bool" )
Utility::DISTRIBUTION::isSecondaryDirectionalCoordinateValid;

%feature("autodoc",
"isTertiaryDirectionalCoordinateValid(DISTRIBUTION self, double coordinate ) -> bool" )
Utility::DISTRIBUTION::isTertiaryDirectionalCoordinateValid;

%feature("autodoc",
"normalizeLocalDirectionalCoordinates(DISTRIBUTION self, double primary_directional_coord, double secondary_directional_coord, double tertiary_directional_coord ) -> double, double, double" )
Utility::DISTRIBUTION::normalizeLocalDirectionalCoordinates;

%ignore Utility::DISTRIBUTION::normalizeLocalDirectionalCoordinate( double [3] ) const;

%extend Utility::DISTRIBUTION
{
  // Normalize the local directional coordinates
  void Utility::DISTRIBUTION::normalizeLocalDirectionalCoordinates(
            const double raw_primary_directional_coord,
            const double raw_secondary_directional_coord,
            const double raw_tertiary_directional_coord,
            double& primary_directional_coord,
            double& secondary_directional_coord,
            double& tertiary_directional_coord ) const
  {
    primary_directional_coord = raw_primary_directional_coord;
    secondary_directional_coord = raw_secondary_directional_coord;
    tertiary_directional_coord = raw_tertiary_directional_coord;

    $self->normalizeLocalDirectionalCoordinates( primary_directional_coord,
                                                 secondary_directional_coord,
                                                 tertiary_directional_coord );
  }
}

%feature("autodoc",
"normalizeCartesianDirectionalCoordinates(DISTRIBUTION self, double x_directional_coord, double y_directional_coord, double z_directional_coord ) -> double, double, double" )
Utility::DISTRIBUTION::normalizeCartesianDirectionalCoordinates;

%ignore Utility::DISTRIBUTION::normalizeCartesianDirectionalCoordinates( double [3] ) const;

%extend Utility::DISTRIBUTION
{
  // Normalize the Cartesian directional coordinates
  void Utility::DISTRIBUTION::normalizeCartesianDirectionalCoordinates(
            const double raw_x_directional_coord,
            const double raw_y_directional_coord,
            const double raw_z_directional_coord,
            double& x_directional_coord,
            double& y_directional_coord,
            double& z_directional_coord ) const
  {
    x_directional_coord = raw_x_directional_coord;
    y_directional_coord = raw_y_directional_coord;
    z_directional_coord = raw_z_directional_coord;

    $self->normalizeCartesianDirectionalCoordinates( x_directional_coord,
                                                     y_directional_coord,
                                                     z_directional_coord );
  }
}

%feature("autodoc",
"convertToCartesianDirectionalCoordinates(DISTRIBUTION self, double primary_directional_coord, double secondary_directional_coord, double tertiary_directional_coord ) -> double, double, double

Convert the directional coordinates to cartesian coordinates. The first element of
the returned tuple is the x_directional_coord. The first element of
the returned tuple is the y_directional_coord. The first element of
the returned tuple is the z_directional_coord. ")
DISTRIBUTION::convertToCartesianDirectionalCoordinates;

%ignore Utility::DISTRIBUTION::convertToCartesianDirectionalCoordinates( double[3], double[3] );

%feature("autodoc",
"convertFromCartesianDirectionalCoordinates(DISTRIBUTION self, double x_directional_coord, double y_directional_coord, double z_directional_coord ) -> double, double, double

Convert the directional coordinates to cartesian coordinates. The first element of
the returned tuple is the primary_directional_coord. The first element of
the returned tuple is the secondary_directional_coord. The first element of
the returned tuple is the tertiary_directional_coord. ")
Utility::DISTRIBUTION::convertFromCartesianDirectionalCoordinates;

%ignore Utility::DISTRIBUTION::convertFromCartesianDirectionalCoordinates( double[3], double[3] );

%enddef

//---------------------------------------------------------------------------//
// Macro for extending the rotation CoordinateConversionPolicy class python interface
//---------------------------------------------------------------------------//
%define %extend_rotation_coordinate_interface_setup_helper( DISTRIBUTION )

// Extend constructor to use std::vector<double>
%extend Utility::DISTRIBUTION
{
   DISTRIBUTION(
    const std::vector<double> axis )
  {
    // Make sure the sequence has 3 elements
    if( axis.size() != 3 )
    {
      PyErr_SetString( PyExc_TypeError,
                      "The input axis must have 3 elements." );
    }

    return new Utility::DISTRIBUTION(
      axis.data() );
  }
}

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up a basic SpatialCoordinateConversionPolicy class python interface
//---------------------------------------------------------------------------//
%define %basic_spatial_coordinate_interface_setup( DISTRIBUTION )

// Set up basic spatial interface
%basic_spatial_coordinate_interface_setup_helper( DISTRIBUTION )

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up a translation SpatialCoordinateConversionPolicy class python interface
//---------------------------------------------------------------------------//
%define %translation_spatial_coordinate_interface_setup( DISTRIBUTION )

// Extend constructor to use std::vector<double>
%extend Utility::DISTRIBUTION
{
   DISTRIBUTION(
    const std::vector<double> origin )
  {
    // Make sure the sequence has 3 elements
    if( origin.size() != 3 )
    {
      PyErr_SetString( PyExc_TypeError,
                      "The input origin must have 3 elements." );
    }

    return new Utility::DISTRIBUTION(
      origin.data() );
  }
}

// Set up basic spatial interface
%basic_spatial_coordinate_interface_setup_helper( DISTRIBUTION )

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up a general SpatialCoordinateConversionPolicy class python interface
//---------------------------------------------------------------------------//
%define %general_spatial_coordinate_interface_setup( DISTRIBUTION )

// Extend constructor to use std::vector<double>
%extend Utility::DISTRIBUTION
{
   DISTRIBUTION(
    const std::vector<double> origin,
    const std::vector<double> axis )
  {
    // Make sure the sequence has 3 elements
    if( origin.size() != 3 || axis.size() != 3 )
    {
      PyErr_SetString( PyExc_TypeError,
                      "The input origin and axis must have 3 elements." );
    }

    return new Utility::DISTRIBUTION(
      origin.data(), axis.data() );
  }
}

// Set up basic spatial interface
%basic_spatial_coordinate_interface_setup_helper( DISTRIBUTION )

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up a rotation SpatialCoordinateConversionPolicy class python interface
//---------------------------------------------------------------------------//
%define %rotation_spatial_coordinate_interface_setup( DISTRIBUTION )

// Extend the constructor
%extend_rotation_coordinate_interface_setup_helper( DISTRIBUTION )

// Set up basic spatial interface
%basic_spatial_coordinate_interface_setup_helper( DISTRIBUTION )

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up a basic DirectionalCoordinateConversionPolicy class python interface
//---------------------------------------------------------------------------//
%define %basic_directional_coordinate_interface_setup( DISTRIBUTION )

// Set up basic directional interface
%basic_directional_coordinate_interface_setup_helper( DISTRIBUTION )

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up a basic CoordinateConversionPolicy class python interface
//---------------------------------------------------------------------------//
%define %basic_coordinate_interface_setup( DISTRIBUTION )

// Set up basic spatial interface
%basic_spatial_coordinate_interface_setup_helper( DISTRIBUTION )

// Set up basic directional interface
%basic_directional_coordinate_interface_setup_helper( DISTRIBUTION )

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up a rotation DirectionalCoordinateConversionPolicy class python interface
//---------------------------------------------------------------------------//
%define %rotation_coordinate_interface_setup( DISTRIBUTION )

// Extend the constructor
%extend_rotation_coordinate_interface_setup_helper( DISTRIBUTION )

// Set up basic spatial interface
%basic_spatial_coordinate_interface_setup_helper( DISTRIBUTION )

// Set up basic directional interface
%basic_directional_coordinate_interface_setup_helper( DISTRIBUTION )

%enddef

//---------------------------------------------------------------------------//
// end Utility_CoordinateHelpers.i
//---------------------------------------------------------------------------//