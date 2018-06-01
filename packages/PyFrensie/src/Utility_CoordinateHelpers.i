//---------------------------------------------------------------------------//
//!
//! \file   Utility_CoordinateHelpers.i
//! \author Luke Kersting
//! \brief  The coordinate helper macros
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

// Add typemaps for converting double[3] to and from Python array
%typemap(in) const double[3] (std::vector<double> temp){
  temp = PyFrensie::convertFromPython<std::vector<double> >( $input );

  // Make sure the sequence has 3 elements
  if( temp.size() != 3 )
  {
    PyErr_SetString( PyExc_TypeError, "The input must have 3 elements." );
    SWIG_fail;
  }

  $1 = temp.data();
}

// Add typecheck out for the Ray class
%typemap(typecheck, precedence=1050) (const double[3]) {
  $1 = (PyArray_Check($input) || PySequence_Check($input)) ? 1 : 0;
}

// Add typemaps for converting double[3] to and from Python array
%typemap(in) const double coordinates[3] (std::vector<double> temp){
  temp = PyFrensie::convertFromPython<std::vector<double> >( $input );

  // Make sure the sequence has 3 elements
  if( temp.size() != 3 )
  {
    PyErr_SetString( PyExc_TypeError, "The input must have 3 elements." );
    SWIG_fail;
  }

  $1 = temp.data();
}

// Add typemaps for converting double cartesian_coordinates[3 to a Python array
%typemap(in,numinputs=0) double cartesian_coordinates[3] (std::vector<double> temp)
{
  temp.resize( 3 );
  $1 = temp.data();
}

%typemap(argout) double cartesian_coordinates[3] {
  std::vector<double> temp(3);

  temp[0] = $1[0];
  temp[1] = $1[1];
  temp[2] = $1[2];

  $result = PyFrensie::convertToPython( temp );
}

// Add typemaps for converting double cartesian_coordinates[3 to a Python array
%typemap(in,numinputs=0) double coordinates[3] (std::vector<double> temp)
{
  temp.resize( 3 );
  $1 = temp.data();
}

%typemap(argout) double coordinates[3] {
  std::vector<double> temp(3);

  temp[0] = $1[0];
  temp[1] = $1[1];
  temp[2] = $1[2];

  $result = PyFrensie::convertToPython( temp );
}

//---------------------------------------------------------------------------//
// Helper macro for setting up a basic SpatialCoordinateConversionPolicy class python interface
//---------------------------------------------------------------------------//
%define %basic_spatial_coordinate_interface_setup_helper( SYSTEM )

%feature("docstring") Utility::SYSTEM::SYSTEM
"The SYSTEM proxy class. This class can convert spatial coordinates."

%feature("autodoc",
"getLocalSpatialCoordinateSystemType(SYSTEM self) -> SpatialCoordinateSystemType" )
Utility::SYSTEM::getLocalSpatialCoordinateSystemType;

%feature("autodoc",
"isPrimarySpatialCoordinateValid(SYSTEM self, double coordinate ) -> bool" )
Utility::SYSTEM::isPrimarySpatialCoordinateValid;

%feature("autodoc",
"isSecondarySpatialCoordinateValid(SYSTEM self, double coordinate ) -> bool" )
Utility::SYSTEM::isSecondarySpatialCoordinateValid;

%feature("autodoc",
"isTertiarySpatialCoordinateValid(SYSTEM self, double coordinate ) -> bool" )
Utility::SYSTEM::isTertiarySpatialCoordinateValid;

%feature("autodoc",
"convertToCartesianSpatialCoordinates(SYSTEM self, double primary_spatial_coord, double secondary_spatial_coord, double tertiary_spatial_coord ) -> double, double, double

Convert the spatial coordinates to cartesian coordinates. The first element of
the returned tuple is the x_spatial_coord. The first element of
the returned tuple is the y_spatial_coord. The first element of
the returned tuple is the z_spatial_coord. ")
Utility::SYSTEM::convertToCartesianSpatialCoordinates;

%feature("autodoc",
"convertFromCartesianSpatialCoordinates(SYSTEM self, double x_spatial_coord, double y_spatial_coord, double z_spatial_coord ) -> double, double, double

Convert the spatial coordinates to cartesian coordinates. The first element of
the returned tuple is the primary_spatial_coord. The first element of
the returned tuple is the secondary_spatial_coord. The first element of
the returned tuple is the tertiary_spatial_coord. ")
Utility::SYSTEM::convertFromCartesianSpatialCoordinates;

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up a basic DirectionalCoordinateConversionPolicy class python interface
//---------------------------------------------------------------------------//
%define %basic_directional_coordinate_interface_setup_helper( SYSTEM )

%feature("docstring") Utility::SYSTEM
"The SYSTEM proxy class. This class can convert directional coordinates."

%feature("autodoc",
"getLocalDirectionalCoordinateSystemType(SYSTEM self) -> DirectionalCoordinateSystemType" )
Utility::SYSTEM::getLocalDirectionalCoordinateSystemType;

%feature("autodoc",
"isPrimaryDirectionalCoordinateValid(SYSTEM self, double coordinate ) -> bool" )
Utility::SYSTEM::isPrimaryDirectionalCoordinateValid;

%feature("autodoc",
"isSecondaryDirectionalCoordinateValid(SYSTEM self, double coordinate ) -> bool" )
Utility::SYSTEM::isSecondaryDirectionalCoordinateValid;

%feature("autodoc",
"isTertiaryDirectionalCoordinateValid(SYSTEM self, double coordinate ) -> bool" )
Utility::SYSTEM::isTertiaryDirectionalCoordinateValid;

%feature("autodoc",
"normalizeLocalDirectionalCoordinates(SYSTEM self, double primary_directional_coord, double secondary_directional_coord, double tertiary_directional_coord ) -> double, double, double" )
Utility::SYSTEM::normalizeLocalDirectionalCoordinates;

%ignore Utility::SYSTEM::normalizeLocalDirectionalCoordinate( double [3] ) const;

%extend Utility::SYSTEM
{
  // Normalize the local directional coordinates
  void Utility::SYSTEM::normalizeLocalDirectionalCoordinates(
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
"normalizeCartesianDirectionalCoordinates(SYSTEM self, double x_directional_coord, double y_directional_coord, double z_directional_coord ) -> double, double, double" )
Utility::SYSTEM::normalizeCartesianDirectionalCoordinates;

%ignore Utility::SYSTEM::normalizeCartesianDirectionalCoordinates( double [3] ) const;

%extend Utility::SYSTEM
{
  // Normalize the Cartesian directional coordinates
  void Utility::SYSTEM::normalizeCartesianDirectionalCoordinates(
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
"convertToCartesianDirectionalCoordinates(SYSTEM self, double primary_directional_coord, double secondary_directional_coord, double tertiary_directional_coord ) -> double, double, double

Convert the directional coordinates to cartesian coordinates. The first element of
the returned tuple is the x_directional_coord. The first element of
the returned tuple is the y_directional_coord. The first element of
the returned tuple is the z_directional_coord. ")
SYSTEM::convertToCartesianDirectionalCoordinates;

%feature("autodoc",
"convertFromCartesianDirectionalCoordinates(SYSTEM self, double x_directional_coord, double y_directional_coord, double z_directional_coord ) -> double, double, double

Convert the directional coordinates to cartesian coordinates. The first element of
the returned tuple is the primary_directional_coord. The first element of
the returned tuple is the secondary_directional_coord. The first element of
the returned tuple is the tertiary_directional_coord. ")
Utility::SYSTEM::convertFromCartesianDirectionalCoordinates;

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up a basic SpatialCoordinateConversionPolicy class python interface
//---------------------------------------------------------------------------//
%define %basic_spatial_coordinate_interface_setup( SYSTEM )

// Set up basic spatial interface
%basic_spatial_coordinate_interface_setup_helper( SYSTEM )

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up a translation SpatialCoordinateConversionPolicy class python interface
//---------------------------------------------------------------------------//
%define %translation_spatial_coordinate_interface_setup( SYSTEM )

// Set up basic spatial interface
%basic_spatial_coordinate_interface_setup_helper( SYSTEM )

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up a general SpatialCoordinateConversionPolicy class python interface
//---------------------------------------------------------------------------//
%define %general_spatial_coordinate_interface_setup( SYSTEM )

// Set up basic spatial interface
%basic_spatial_coordinate_interface_setup_helper( SYSTEM )

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up a rotation SpatialCoordinateConversionPolicy class python interface
//---------------------------------------------------------------------------//
%define %rotation_spatial_coordinate_interface_setup( SYSTEM )

// Set up basic spatial interface
%basic_spatial_coordinate_interface_setup_helper( SYSTEM )

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up a basic DirectionalCoordinateConversionPolicy class python interface
//---------------------------------------------------------------------------//
%define %basic_directional_coordinate_interface_setup( SYSTEM )

// Set up basic directional interface
%basic_directional_coordinate_interface_setup_helper( SYSTEM )

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up a basic CoordinateConversionPolicy class python interface
//---------------------------------------------------------------------------//
%define %basic_coordinate_interface_setup( SYSTEM )

// Set up basic spatial interface
%basic_spatial_coordinate_interface_setup_helper( SYSTEM )

// Set up basic directional interface
%basic_directional_coordinate_interface_setup_helper( SYSTEM )

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up a rotation DirectionalCoordinateConversionPolicy class python interface
//---------------------------------------------------------------------------//
%define %rotation_coordinate_interface_setup( SYSTEM )

// Set up basic spatial interface
%basic_spatial_coordinate_interface_setup_helper( SYSTEM )

// Set up basic directional interface
%basic_directional_coordinate_interface_setup_helper( SYSTEM )

%enddef

//---------------------------------------------------------------------------//
// end Utility_CoordinateHelpers.i
//---------------------------------------------------------------------------//