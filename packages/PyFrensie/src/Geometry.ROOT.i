//---------------------------------------------------------------------------//
//!
//! \file    Geometry.ROOT.i
//! \author  Luke Kersting
//! \brief   The Geometry.ROOT sub-module swig interface file
//!
//---------------------------------------------------------------------------//

%define %geometry_root_docstring
"
PyFrensie.Geometry.ROOT is the python interface to the FRENSIE geometry/root
subpackage.

The purpose of ROOT is to allow a user to query root geometry data and to
ray trace on a combinatorial geometry using python. This can be useful for
debugging geometries.
"
%enddef

%module(package   = "PyFrensie.Geometry",
        autodoc   = "1",
        docstring = %geometry_root_docstring) ROOT

%{

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "PyFrensie_PythonTypeTraits.hpp"
#include "Geometry_InfiniteMediumNavigator.hpp"
#include "Geometry_InfiniteMediumModel.hpp"
#include "Geometry_RootModelProperties.hpp"
#include "Geometry_RootModel.hpp"
#include "Geometry_AdvancedModel.hpp"
#include "Geometry_RootNavigator.hpp"
#include "Geometry_Exceptions.hpp"
#include "Utility_SerializationHelpers.hpp"
#include "Utility_DesignByContract.hpp"

using namespace Geometry;
%}

// // C++ STL support
%include <stl.i>
%include <std_except.i>

// Include typemaps support
%include <typemaps.i>

// Import the Geometry.Geometry__init__.i file
%import "Geometry.Geometry__init__.i"

// Standard exception handling
%include "exception.i"

// Global swig features
%feature("autodoc", "1");

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

// General ignore directives
%ignore *::Volume;
%ignore *::Area;

// Add a few general templates
%template(StringVector) std::vector<std::string>;

// Add a few general typemaps
%apply std::vector<std::string>& OUTPUT { std::vector<std::string>& properties };

// Add typemaps for converting file_path to and from Python string
%typemap(in) const boost::filesystem::path& ( boost::filesystem::path temp ){
  temp = PyFrensie::convertFromPython<std::string>( $input );
  $1 = &temp;
}

%typemap(typecheck, precedence=1140) (const boost::filesystem::path&) {
  $1 = (PyString_Check($input)) ? 1 : 0;
}

//---------------------------------------------------------------------------//
// Add support for the RootModelProperties class
//---------------------------------------------------------------------------//
// Include the RootModelProperties class
%include "Geometry_RootModelProperties.hpp"

//---------------------------------------------------------------------------//
// Add support for the RootNavigator class
//---------------------------------------------------------------------------//

%feature("docstring")
Geometry::RootNavigator
"
The RootNavigator class is primarily used to traverse a Model.
Some geometric data, such as the surface normal at a point on a surface or the
relationship between a point and a cell, can also be queried.
A brief useage tutorial for this class is shown below:

   import PyFrensie.Geometry, numpy
   model = PyFrensie.Geometry.ROOT.RootModel.getInstance()
   properties = PyFrensie.Geometry.ROOT.RootModelProperties( 'my_geom.root' )
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

%navigator_interface_setup( RootNavigator )

// Include the RootNavigator class
%include "Geometry_RootNavigator.hpp"

//---------------------------------------------------------------------------//
// Add support for the RootModel class
//---------------------------------------------------------------------------//

// Add more detailed docstrings for the RootModel class
%feature("docstring")
Geometry::RootModel
"
The RootModel class stores a geometric model, from a combinatorial (.root).
It can be used for querying properties of the geometry
and for creating navigators, which can be used to traverse the geometry.
A brief usage tutorial for this class is shown below:

   import PyFrensie.Geometry, numpy

   model = PyFrensie.Geometry.ROOT.RootModel.getInstance()
   properties = PyFrensie.Geometry.ROOT.RootModelProperties( 'my_geom.root' )
   model.initialize( properties )

   cells = model.getCells( True, True )
   materials = model.getMaterialIds()
   cell_materials = model.getCellMaterialIds()
   cell_densities = model.getCellDensities()
   cell_estimator_data = model.getCellEstimatorData()
   navigator = model.createNavigator()
"

%model_interface_setup( RootModel )

%template(MatNameMap) std::map<Geometry::Model::EntityId,std::string>;

// Add some useful methods to the RootModel class
%extend Geometry::RootModel
{
  // Return the cell material names
  std::map<Geometry::Model::EntityId,std::string> Geometry::RootModel::getCellMaterialNames() const
  {
    std::map<Geometry::Model::EntityId,std::string> cell_id_mat_name_map;
    $self->getCellMaterialNames( cell_id_mat_name_map );

    return cell_id_mat_name_map;
  }
};

// Include the RootModel class
%include "Geometry_RootModel.hpp"

// Turn off the exception handling
%exception;

//---------------------------------------------------------------------------//
// end Geometry.ROOT.i
//---------------------------------------------------------------------------//e
