//---------------------------------------------------------------------------//
//!
//! \file   Geometry_Model.i
//! \author Luke Kersting
//! \brief  The SModel classes interface file
//!
//---------------------------------------------------------------------------//


%{
// FRENSIE Includes
#include "Geometry_Model.hpp"
#include "Geometry_InfiniteMediumModel.hpp"
#include "Geometry_AdvancedModel.hpp"

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
// Add support for the Model class
//---------------------------------------------------------------------------//

// Add more detailed docstrings for the Model class
%feature("docstring")
Geometry::Model
"
The Model class stores a geometric model, which can be from a CAD (.h5m) file
or a Root (.root) file. It can be used for querying properties of the geometry
and for creating navigators, which can be used to traverse the geometry.
A brief usage tutorial for this class is shown below:

   import PyFrensie.Geometry, numpy

   model = PyFrensie.Geometry.DagMC.DagMCModel.getInstance()
   properties = PyFrensie.Geometry.DagMC.DagMCModelProperties( 'my_geom.h5m' )
   model.initialize( properties )

   cells = model.getCells( True, True )
   materials = model.getMaterialIds()
   cell_materials = model.getCellMaterialIds()
   cell_densities = model.getCellDensities()
   cell_estimator_data = model.getCellEstimatorData()
   navigator = model.createNavigator()
"

%model_interface_setup( Model )

// Add a few Geometry::Model typemaps
%typemap(out) Geometry::Model::Volume {
    $result = PyFloat_FromDouble( Utility::getRawQuantity($1) ); }

%typemap(in,numinputs=0) Geometry::Model::MaterialIdSet& (Geometry::Model::MaterialIdSet temp) "$1 = &temp;"

%typemap(argout) Geometry::Model::MaterialIdSet& {
  %append_output(PyFrensie::convertToPython( *$1 ));
}

%typemap(in,numinputs=0) Geometry::Model::CellIdSet &cell_set(Geometry::Model::CellIdSet temp) "$1 = &temp;"

%typemap(argout) Geometry::Model::CellIdSet &cell_set {
  %append_output(PyFrensie::convertToPython( *$1 ));
}

%typemap(in,numinputs=0) Geometry::Model::CellIdMatIdMap& (Geometry::Model::CellIdMatIdMap temp) "$1 = &temp;"

%typemap(argout) Geometry::Model::CellIdMatIdMap& {
  %append_output(PyFrensie::convertToPython( *$1 ));
}

%typemap(in,numinputs=0) Geometry::Model::CellIdDensityMap& (Geometry::Model::CellIdDensityMap temp) "$1 = &temp;"

%typemap(argout) Geometry::Model::CellIdDensityMap& {
  std::map<Geometry::Model::EntityId,double> density_map;

  Geometry::Model::CellIdDensityMap::const_iterator it = ($1)->begin();

  while( it != ($1)->end() )
  {
    // insert raw elements in density_map
    density_map.insert(std::pair<Geometry::Model::EntityId,double> (it->first, it->second.value()));

    ++it;
  }

  %append_output(PyFrensie::convertToPython( density_map ));
}

%typemap(in,numinputs=0) Geometry::Model::CellEstimatorIdDataMap& (Geometry::Model::CellEstimatorIdDataMap temp) "$1 = &temp;"

%typemap(argout) Geometry::Model::CellEstimatorIdDataMap& {
  %append_output(PyFrensie::convertToPython( *$1 ) );
}

// Include the Model class
%include "Geometry_Model.hpp"

//---------------------------------------------------------------------------//
// Add support for the Model class
//---------------------------------------------------------------------------//

// Add more detailed docstrings for the Model class
%feature("docstring")
Geometry::InfiniteMediumModel
"
The InfiniteMediumModel class stores an infinite geometric model. A cell id,
material id and density can optionally be assigned to the single infinite cell
stored in the model. A brief usage tutorial for this class is shown below:

   import PyFrensie.Geometry, numpy

   model = PyFrensie.Geometry.InfiniteMediumModel()

   cells = model.getCells( True, True )
   materials = model.getMaterialIds()
   cell_materials = model.getCellMaterialIds()
   cell_densities = model.getCellDensities()
   cell_estimator_data = model.getCellEstimatorData()
   navigator = model.createNavigator()
"

%model_interface_setup( InfiniteMediumModel )

%typemap(in) const Geometry::Model::EntityId ( Geometry::Model::EntityId temp ){
  temp = PyInt_AsUnsignedLongMask( $input );
  $1 = temp;
}

%typemap(typecheck, precedence=70) (const Geometry::Model::EntityId) {
  $1 = (PyInt_Check($input)) ? 1 : 0;
}

%typemap(in) const Geometry::Model::MaterialId ( Geometry::Model::MaterialId temp ){
  temp = PyInt_AsUnsignedLongMask( $input );
  $1 = temp;
}

%typemap(typecheck, precedence=70) (const Geometry::Model::MaterialId) {
  $1 = (PyInt_Check($input)) ? 1 : 0;
}

%typemap(in) const Geometry::Model::Density {
  if(PyFloat_Check($input))
  {
    $1 = Geometry::Model::Density::from_value( PyFrensie::convertFromPython<double>( $input ) );
  }
  else
  {
    $1 = Geometry::Model::Density::from_value( (double)(PyFrensie::convertFromPython<int>( $input )) );
  }
}

%typemap(out) Geometry::Model::Density {
  %append_output(PyFrensie::convertToPython( Utility::getRawQuantity( $1 ) ) );
}

%typemap(typecheck, precedence=90) (const Geometry::Model::Density) {
  $1 = (PyFloat_Check($input) || PyInt_Check($input)) ? 1 : 0;
}

// Include the InfiniteMediumModel class
%include "Geometry_InfiniteMediumModel.hpp"

//---------------------------------------------------------------------------//
// Add support for the AdvancedModel class
//---------------------------------------------------------------------------//

// Add more detailed docstrings for the AdvancedModel class
%feature("docstring")
Geometry::AdvancedModel
"
The AdvancedModel class extends the Model class with surface querying methods.
Currently, only CAD geometries can be stored as AdvancedModels since they are
the only types of geometries that keep track of surfaces independently of
cells. There are two ways to create an advanced model. A brief useage tutorial
for this class is shown below:

   import PyFrensie.Geometry, numpy
   model = PyFrensie.Geometry.DagMC.DagMCModel.getInstance()
   properties = PyFrensie.Geometry.DagMC.DagMCModelProperties( 'my_geom.h5m' )
   model.initialize( properties )

   cells = model.getCells( True, True )
   materials = model.getMaterialIds()
   cell_materials = model.getCellMaterialIds()
   cell_densities = model.getCellDensities()
   cell_estimator_data = model.getCellEstimatorData()

   surfaces = model.getSurfaces()
   surface_estimator_data = model.getSurfaceEstimatorData()

   navigator = model.createNavigator()
"

%advanced_model_interface_setup( AdvancedModel )

// Add a few AdvancedModel typemaps
%typemap(in,numinputs=0) Geometry::AdvancedModel::SurfaceIdSet& (Geometry::AdvancedModel::SurfaceIdSet temp) "$1 = &temp;"

%typemap(argout) Geometry::AdvancedModel::SurfaceIdSet& {
  %append_output(PyFrensie::convertToPython( *$1 ));
}

%typemap(out) Geometry::AdvancedModel::Area {
    $result = PyFloat_FromDouble( Utility::getRawQuantity($1) ); }

%typemap(in,numinputs=0) Geometry::AdvancedModel::SurfaceEstimatorIdDataMap& (Geometry::AdvancedModel::SurfaceEstimatorIdDataMap temp) "$1 = &temp;"

%typemap(argout) Geometry::AdvancedModel::SurfaceEstimatorIdDataMap& {
  %append_output(PyFrensie::convertToPython( *$1 ) );
}

// Include the AdvancedModel class
%include "Geometry_AdvancedModel.hpp"

//---------------------------------------------------------------------------//
// Turn off the exception handling
//---------------------------------------------------------------------------//
%exception;

//---------------------------------------------------------------------------//
// end Geometry_Model.i
//---------------------------------------------------------------------------//
