//---------------------------------------------------------------------------//
//!
//! \file   Geometry_Navigator.i
//! \author Luke Kersting
//! \brief  The SNavigator classes interface file
//!
//---------------------------------------------------------------------------//


%{
// FRENSIE Includes
#include "Geometry_Navigator.hpp"
#include "Geometry_InfiniteMediumNavigator.hpp"

using namespace Geometry;
%}

// Include the geometry helpers
%include "Geometry_Helpers.i"

// Standard exception handling
%include "exception.i"

// General exception handling
%exception
{
  try{
    $action;
    if( PyErr_Occurred() )
      SWIG_fail;
  }
  catch( Utility::ContractException& e )
  {
    SWIG_exception( SWIG_ValueError, e.what() );
  }
  catch( Geometry::InvalidGeometryRepresentation& e )
  {
    SWIG_exception( SWIG_RuntimeError, e.what() );
  }
  catch( std::runtime_error& e )
  {
    SWIG_exception( SWIG_RuntimeError, e.what() );
  }
  catch( ... )
  {
    SWIG_exception( SWIG_UnknownError, "Unknown C++ exception" );
  }
}

// Global swig features
%feature("autodoc", "1");

//---------------------------------------------------------------------------//
// Add support for the Navigator class
//---------------------------------------------------------------------------//

%feature("docstring")
Geometry::Navigator
"
The Navigator class is primarily used to traverse a Model. Some geometric data,
such as the surface normal at a point on a surface or the relationship between
a point and a cell, can also be queried. A brief useage tutorial for this
class is shown below:

   import PyFrensie.Geometry, numpy
   model = PyFrensie.Geometry.DagMC.DagMCModel.getInstance()
   properties = PyFrensie.Geometry.DagMC.DagMCModelProperties( 'my_geom.h5m' )
   model.initialize( properties )
   navigator = model.createNavigator()

   navigator.setState( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 )
   distance_to_surface_hit = navigator.fireRay()
   navigator.advanceToCellBoundary()

   ray_position = navigator.getPosition()
   ray_cell = navigator.getCurrentCell()

   distance_to_surface_hit, surface_hit = navigator.fireRayAndGetSurfaceHit()
   reflected = navigator.advanceToCellBoundary()
   if( reflected ):
      print 'Surface ', surface_hit, ' reflected ray.'

   distance_to_surface_hit = navigator.fireRay()
   navigator.advanceBySubstep( 0.5*distance_to_surface_hit )
   navigator.changeDirection( 0.0, 0.0, -1.0 )

   navigator.fireRay()
   reflected, normal = navigator.advanceToCellBoundaryAndGetSurfaceNormal()
"

%navigator_interface_setup( Navigator )

// Rename a few overloaded methods
%rename(fireRayAndGetSurfaceHit) Geometry::Navigator::fireRay( EntityId* );
%rename(fireRayAndGetSurfaceHit2) Geometry::Navigator::fireRay( EntityId& );
%rename(advanceToCellBoundaryAndGetSurfaceNormal) Geometry::Navigator::advanceToCellBoundary( double* );

// Add typemaps for the EntityId
%typemap(in,numinputs=0) Geometry::Navigator::EntityId* (Geometry::Navigator::EntityId temp) "$1 = &temp;"

%typemap(argout) Geometry::Navigator::EntityId* {
  %append_output(PyFrensie::convertToPython( *$1 ));
}

// Add typemaps for the surface_normal
%typemap(in,numinputs=0) double* surface_normal (std::vector<double> temp)
{
  temp.resize( 3 );
  $1 = temp.data();
}

%typemap(argout) double* surface_normal {
  std::vector<double> normal(3);

  normal[0] = $1[0];
  normal[1] = $1[1];
  normal[2] = $1[2];

  %append_output(PyFrensie::convertToPython( normal ));
}

// Add typemaps for the CellIdSet
%typemap(in) Geometry::Navigator::CellIdSet& (Geometry::Navigator::CellIdSet temp)
{
  temp = PyFrensie::convertFromPython<Geometry::Navigator::CellIdSet>( $input );
  $1 = &temp;
}

%typemap(typecheck, precedence=SWIG_TYPECHECK_SET) (Geometry::Navigator::CellIdSet&) {
  $1 = (PySet_Check($input)) ? 1 : 0;
}

// Add typemaps for normal[3]
%typemap(in,numinputs=0) double normal[3] (std::vector<double> temp)
{
  temp.resize( 3 );
  $1 = temp.data();
}

%typemap(argout) double normal[3] {
  std::vector<double> temp_normal(3);

  temp_normal[0] = $1[0];
  temp_normal[1] = $1[1];
  temp_normal[2] = $1[2];

  %append_output(PyFrensie::convertToPython( temp_normal ));
}

// Add typemaps for converting the Length to and from a Python float/array
%apply const Geometry::UnitAwareRay<Geometry::Navigator::LengthUnit>::Length[3] { const Geometry::Navigator::Length[3] };
%apply const Geometry::UnitAwareRay<Geometry::Navigator::LengthUnit>::Length* { const Geometry::Navigator::Length* };
%apply const Geometry::UnitAwareRay<Geometry::Navigator::LengthUnit>::Length { const Geometry::Navigator::Length };
%apply Geometry::UnitAwareRay<Geometry::Navigator::LengthUnit>::Length { Geometry::Navigator::Length };

// Include the Navigator class
%include "Geometry_Navigator.hpp"

//---------------------------------------------------------------------------//
// Add support for the InfiniteMediumNavigator class
//---------------------------------------------------------------------------//

%feature("docstring")
Geometry::InfiniteMediumNavigator
"
The InfiniteMediumNavigator class is primarily used to traverse a Model. Some geometric data,
such as the surface normal at a point on a surface or the relationship between
a point and a cell, can also be queried. A brief useage tutorial for this
class is shown below:

   import PyFrensie.Geometry, numpy
   model = PyFrensie.Geometry.DagMC.DagMCModel.getInstance()
   properties = PyFrensie.Geometry.DagMC.DagMCModelProperties( 'my_geom.h5m' )
   model.initialize( properties )
   navigator = model.createNavigator()

   navigator.setState( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 )
   distance_to_surface_hit = navigator.fireRay()
   navigator.advanceToCellBoundary()

   ray_position = navigator.getPosition()
   ray_cell = navigator.getCurrentCell()

   distance_to_surface_hit, surface_hit = navigator.fireRayAndGetSurfaceHit()
   reflected = navigator.advanceToCellBoundary()
   if( reflected ):
      print 'Surface ', surface_hit, ' reflected ray.'

   distance_to_surface_hit = navigator.fireRay()
   navigator.advanceBySubstep( 0.5*distance_to_surface_hit )
   navigator.changeDirection( 0.0, 0.0, -1.0 )

   navigator.fireRay()
   reflected, normal = navigator.advanceToCellBoundaryAndGetSurfaceNormal()
"

// Add typemaps for converting AtomicWeight to and from Python float
%typemap(in) const Geometry::Model::Density {
  $1 = Geometry::Model::Density::from_value( PyFrensie::convertFromPython<double>( $input ) );
}

%typemap(out) Geometry::Model::Density {
  %append_output(PyFrensie::convertToPython( Utility::getRawQuantity( $1 ) ) );
}

%typemap(typecheck, precedence=90) (const Geometry::Model::Density) {
  $1 = (PyFloat_Check($input)) ? 1 : 0;
}

%navigator_interface_setup( InfiniteMediumNavigator )

// Include the InfiniteMediumNavigator class
%include "Geometry_InfiniteMediumNavigator.hpp"

//---------------------------------------------------------------------------//
// Turn off the exception handling
//---------------------------------------------------------------------------//
%exception;

//---------------------------------------------------------------------------//
// end Geometry_Navigator.i
//---------------------------------------------------------------------------//
