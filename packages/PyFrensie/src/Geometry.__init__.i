//---------------------------------------------------------------------------//
//!
//! \file   Geometry.__init__.i
//! \author Alex Robinson
//! \brief  The geometry module swig interface file
//!
//---------------------------------------------------------------------------//

%define %geometry_docstring
"
PyFrensie.Geometry is the python interface to the FRENSIE geometry package
"
%enddef

%module(package   = "PyFrensie.Geometry",
        autodoc   = "1",
        docstring = %geometry_docstring) __init__

%include "Geometry_Config.i"

%{
// Std Lib Includes
#include <sstream>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "PyFrensie_PythonTypeTraits.hpp"
#include "Geometry_ModuleTraits.hpp"
#include "Geometry_PointLocation.hpp"
#include "Geometry_EstimatorType.hpp"
#include "Geometry_ParticleType.hpp"
#include "Geometry_Model.hpp"
#include "Geometry_AdvancedModel.hpp"
#include "Geometry_ModelFactory.hpp"
#include "Geometry_Ray.hpp"
#include "Geometry_Navigator.hpp"
#include "Utility_ContractException.hpp"
%}

// C++ STL support
%include <stl.i>
%include <std_string.i>
%include <std_set.i>
%include <std_map.i>
%include <std_vector.i>
%include <std_except.i>
%include <std_shared_ptr.i>

// Include typemaps support
%include <typemaps.i>

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
  catch( std::runtime_error& e )
  {
    SWIG_exception( SWIG_RuntimeError, e.what() );
  }
  catch( ... )
  {
    SWIG_exception( SWIG_UnknownError, "Unknown C++ exception" );
  }
}

//---------------------------------------------------------------------------//
// Add support for the ModuleTraits
//---------------------------------------------------------------------------//
// Include ModuleTraits
%include "Geometry_ModuleTraits.hpp"

//---------------------------------------------------------------------------//
// Add support for the PointLocation enum
//---------------------------------------------------------------------------//
// Include the PointLocation enum
%include "Geometry_PointLocation.hpp"

//---------------------------------------------------------------------------//
// Add support for the EstimatorType enum
//---------------------------------------------------------------------------//
// Include the EstimatorType enum
%include "Geometry_EstimatorType.hpp"

//---------------------------------------------------------------------------//
// Add support for the ParticleType enum
//---------------------------------------------------------------------------//
// Include the ParticleType enum
%include "Geometry_ParticleType.hpp"

//---------------------------------------------------------------------------//
// Add support for the Model class
//---------------------------------------------------------------------------//
// Add more detailed docstrings for the Model class
%feature("docstring")
Geometry::Model
"
The Model class stores a geometric model, which can be from a CAD (.sat) file
or a Root (.root) file. It can be used for querying properties of the geometry
and for creating navigators, which can be used to traverse the geometry.
A brief usage tutorial for this class is shown below:

   import PyFrensie.Geometry, numpy

   model = PyFrensie.Geometry.createModel( 'my_geom.xml' )
   
   cells = model.getCells( True, True )
   materials = model.getMaterialIds()
   cell_materials = model.getCellMaterialIds()
   cell_densities = model.getCellDensities()
   cell_estimator_data = model.getCellEstimatorData()
   navigator = model.createNavigator()
"

%feature("autodoc", "getMaterialIds(Model self) -> set[material_id]" )
Geometry::Model::getMaterialIds;

%feature("autodoc", "getCells(Model self, bool include_void_cells, bool include_termination_cells) -> set[cell_id]")
Geometry::Model::getCells;

%feature("autodoc","getCellMaterialIds(Model self) -> dictionary[cell_id,material_id]" )
Geometry::Model::getCellMaterialIds;
   
%feature("autodoc", "getCellDensities(Model self) -> dictionary[cell_id,density(float)]" )
Geometry::Model::getCellDensities;

%feature("autodoc",
"getCellEstimatorData(Model self) -> dictionary[estimator_id,estimator_data]

The mapped value (estimator_data) is a tuple of size three with the following 
elements:
   1. Estimator type (e.g. Geometry.CELL_TRACK_LENGTH_FLUX_ESTIMATOR)
   2. Particle type (e.g. Geometry.NEUTRON)
   3. Numpy array of cells assigned to this estimator
" )
Geometry::Model::getCellEstimatorData;

%feature("autodoc", "createNavigator(Model self) -> Navigator" )
Geometry::Model::createNavigator;

// Allow shared pointers of Model objects
%shared_ptr(Geometry::Model);

// Add a few general typemaps
%typemap(in,numinputs=0) Geometry::Model::MaterialIdSet& (Geometry::Model::MaterialIdSet temp) "$1 = &temp;"

%typemap(argout) Geometry::Model::MaterialIdSet& {
  %append_output(PyFrensie::convertToPython( *$1 ));
}

%typemap(in,numinputs=0) Geometry::Model::CellIdSet& (Geometry::Model::CellIdSet temp) "$1 = &temp;"

%typemap(argout) Geometry::Model::CellIdSet& {
  %append_output(PyFrensie::convertToPython( *$1 ));
}

%typemap(in,numinputs=0) Geometry::Model::CellIdMatIdMap& (Geometry::Model::CellIdMatIdMap temp) "$1 = &temp;"

%typemap(argout) Geometry::Model::CellIdMatIdMap& {
  %append_output(PyFrensie::convertToPython( *$1 ));
}

%typemap(in,numinputs=0) Geometry::Model::CellIdDensityMap& (Geometry::Model::CellIdDensityMap temp) "$1 = &temp;"

%typemap(argout) Geometry::Model::CellIdDensityMap& {
  %append_output(PyFrensie::convertToPython( *$1 ));
}

%typemap(in,numinputs=0) Geometry::Model::CellEstimatorIdDataMap& (Geometry::Model::CellEstimatorIdDataMap temp) "$1 = &temp;"

%typemap(argout) Geometry::Model::CellEstimatorIdDataMap& {
  %append_output(PyFrensie::convertToPython( *$1 ));
}

// Add some useful methods to the Model class
%extend Geometry::Model
{
  // String conversion method
  PyObject* __str__() const
  {
    return PyFrensie::convertToPython( $self->getName() );
  }

  // String representation method
  PyObject* __repr__() const
  {
    std::string string_rep( "Model(" );
    string_rep += $self->getName();
    string_rep += ")";

    return PyFrensie::convertToPython( string_rep );
  }

  // Model comparison method
  bool __eq__( const Geometry::Model& that ) const
  {
    return $self == &that;
  }

  // Model comparison method
  bool __ne__( const Geometry::Model& that ) const
  {
    return $self != &that;
  }
};

// Include the Model class
%include "Geometry_Model.hpp"

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
cells. There are two ways to create an advanced model. The first is by
simply loading your geometry as an advanced model, as shown below:

   import PyFrensie.Geometry, numpy
   model = PyFrensie.Geometry.createAdvancedModel( 'my_cad_geom.xml' )

The second is by converting your model to an advanced model, as shown below:

   import PyFrensie.Geometry, numpy
   model = PyFrensie.Geometry.createModel( 'my_cad_geom.xml' )
   model = PyFrensie.Geometry.makeModelAdvanced( model )

Note that if your geometry does not support the AdvancedModel interface 
attempting to load it as an advanced model or attempting to convert it to
an advanced model will result in an exception.

An brief usage tutorial for this class is shown below:

   import PyFrensie.Geometry, numpy
   model = PyFrensie.Geometry.createAdvancedModel( 'my_cad_geom.xml' )

   cells = model.getCells( True, True )
   materials = model.getMaterialIds()
   cell_materials = model.getCellMaterialIds()
   cell_densities = model.getCellDensities()
   cell_estimator_data = model.getCellEstimatorData()

   surfaces = model.getSurfaces()
   surface_estimator_data = model.getSurfaceEstimatorData()

   navigator = model.createNavigator()
"

%feature("autodoc", "getSurfaces(Model self) -> set[surface_id]" )
Geometry::AdvancedModel::getSurfaces;

%feature("autodoc",
"getSurfaceEstimatorData(Model self) -> dictionary[estimator_id,estimator_data]
The mapped value (estimator_data) is a tuple of size three with the following
elements:
   1. Estimator type (e.g. Geometry.SURFACE_FLUX_ESTIMATOR)
   2. Particle type (e.g. Geometry.NEUTRON)
   3. Numpy array of surfaces assigned to this estimator
" )
Geometry::AdvancedModel::getSurfaceEstimatorData;

// Allow shared pointers of AdvancedModel objects
%shared_ptr(Geometry::AdvancedModel);

// Add a few general typemaps
%typemap(in,numinputs=0) Geometry::AdvancedModel::SurfaceIdSet& (Geometry::AdvancedModel::SurfaceIdSet temp) "$1 = &temp;"

%typemap(argout) Geometry::AdvancedModel::SurfaceIdSet& {
  %append_output(PyFrensie::convertToPython( *$1 ));
}

%typemap(in,numinputs=0) Geometry::AdvancedModel::SurfaceEstimatorIdDataMap& (Geometry::AdvancedModel::SurfaceEstimatorIdDataMap temp) "$1 = &temp;"

%typemap(argout) Geometry::AdvancedModel::SurfaceEstimatorIdDataMap& {
  %append_output(PyFrensie::convertToPython( *$1 ));
}

// Add some useful methods to the Model class
%extend Geometry::AdvancedModel
{
  // String conversion method
  PyObject* __str__() const
  {
    return PyFrensie::convertToPython( $self->getName() );
  }

  // String representation method
  PyObject* __repr__() const
  {
    std::string string_rep( "Advanced Model(" );
    string_rep += $self->getName();
    string_rep += ")";

    return PyFrensie::convertToPython( string_rep );
  }
}

// Include the AdvancedModel class
%include "Geometry_AdvancedModel.hpp"

//---------------------------------------------------------------------------//
// Add support for the ModelFactory class
//---------------------------------------------------------------------------//
// Import the ModelFactory class
%import "Geometry_ModelFactory.hpp"

%feature("autodoc",
"
createModel(String geometry_xml_file) -> Model

The string must be the file name (with path) of the xml file that describes
the geometry. Refer to the FRENSIE documentation regarding the proper way
to constuct this xml file
" )
createModel;

%feature("autodoc",
"
createAdvancedModel(String geometry_xml_file) -> AdvancedModel

The string must be the file name (with path) of the xml file that describes
the geometry. Refer to the FRENSIE documentation regarding the proper way
to constuct this xml file. If the geometry does not support the AdvancedModel
interface an exception will be thrown.
" )
createAdvancedModel;

%feature("autodoc",
"
makeModelAdvanced(Model model) -> AdvancedModel

If the geometry does not support the AdvancedModel
interface an exception will be thrown.
" )
makeModelAdvanced;

%feature("autodoc", "makeModelBasic(AdvancedModel model) -> Model" )
makeModelBasic;

%inline %{
std::shared_ptr<const Geometry::Model> createModel(
                                        const std::string& geom_rep_file_name )
{
  Teuchos::RCP<const Teuchos::ParameterList> geom_rep =
    Teuchos::getParametersFromXmlFile( geom_rep_file_name );
  
  return Geometry::ModelFactory::createModel( *geom_rep );
}

// This method will only work if the geometry supports advanced models
std::shared_ptr<const Geometry::AdvancedModel> createAdvancedModel(
                                        const std::string& geom_rep_file_name )
{
  return std::dynamic_pointer_cast<const Geometry::AdvancedModel>(
                                           createModel( geom_rep_file_name ) );
}

// Convert an existing model to an advanced model. This method will only
// work if the geometry supports advanced models
std::shared_ptr<const Geometry::AdvancedModel> makeModelAdvanced(
                          const std::shared_ptr<const Geometry::Model>& model )
{
  return std::dynamic_pointer_cast<const Geometry::AdvancedModel>( model );
}

// Convert an existing advanced model to a basic model.
std::shared_ptr<const Geometry::Model> makeModelBasic(
                  const std::shared_ptr<const Geometry::AdvancedModel>& model )
{
  return model;
}
%}

//---------------------------------------------------------------------------//
// Add support for the Ray class
//---------------------------------------------------------------------------//
// Add more detailed docstrings for the Ray class
%feature("docstring")
Geometry::Ray
"
The Ray stores the state of a ray object (position and direction). A brief 
usage tutorial for this class is shown below:

   import PyFrensie.Geometry, numpy

   ray1 = PyFrensie.Geometry.Ray( 0, 0, 0, 0, 0, 1 )
   ray2 = PyFrensie.Geometry.Ray( (0.,0.,0.), (0.,0.,1.) )
   ray3 = PyFrensie.Geometry.Ray( [0.,0.,0.], [0.,0.,1.] )
   ray4 = PyFrensie.Geometry.Ray( numpy.array( [0,0,0], dtype=numpy.dtype('d') ), numpy.array( [0,0,1], dtype=numpy.dtype('d') ) )

   ray1.getPosition()
   ray1.getDirection()

   ray1.advanceHead( 1 )
   ray1.changeDirection( 0, 1, 0 )
   ray1.advanceHead( 1 )
"

%feature("docstring")
Geometry::Ray::Ray
"
The Ray object can be constructed with 6 doubles or two sequences (list,
tuple, numpy.array or a combination). Make sure that the direction is valid
(If Design-by-Contract is turned on in FRENSIE it will do the check for you.)
"

%feature("docstring")
Geometry::Ray::getPosition
"
A NumPy array will be returned.
"

%feature("docstring")
Geometry::Ray::getDirection
"
A NumPy array will be returned.
"

// Ignore the extra contructors
%ignore Geometry::Ray::Ray( double[3], double[3], const bool );
%ignore Geometry::Ray::Ray( double[3], double[3] );

// Ignore the print method
%ignore Geometry::Ray::print;

// Add a general typemap that will convert the input position from a Python
// Array object to a double*.
%typemap(in) const double position[3] (std::vector<double> temp_position){
  temp_position =
    PyFrensie::convertFromPython<std::vector<double> >( $input );

  // Make sure the sequence has 3 elements
  if( temp_position.size() != 3 )
  {
    PyErr_SetString( PyExc_TypeError,
                     "The input position must have 3 elements." );
  }

  $1 = temp_position.data();
}

// Add a general typemap that will convert the input direction from a Python
// array object to a double*
%typemap(in) const double direction[3] (std::vector<double> temp_direction){
  temp_direction =
    PyFrensie::convertFromPython<std::vector<double> >( $input );

  // Make sure the sequence has 3 elements
  if( temp_direction.size() != 3 )
  {
    PyErr_SetString( PyExc_TypeError,
                     "The input direction must have 3 elements." );
  }

  $1 = temp_direction.data();
}

// The typecheck precedence, which is used by SWIG to determine which
// overloaded method should be called, should be set to
// SWIG_TYPECHECK_DOUBLE_ARRAY (1050) for the C double arrays. You will get a
// Python error when calling the overloaded method in Python without this
// typecheck
%typemap(typecheck, precedence=1050) (const double[3]) {
  $1 = (PyArray_Check($input) || PySequence_Check($input)) ? 1 : 0;
}

// Add a general typemap that will convert the output position or direction
// from a double* to a Python array object
%typemap(out) const double* {
  Teuchos::ArrayView<const double> output_view( $1, 3 );

  $result = PyFrensie::convertToPython( output_view );
}

// Add some useful methods to the Ray class
%extend Geometry::Ray
{
  // String conversion methd
  PyObject* __str__() const
  {
    std::ostringstream oss;

    $self->print( oss );

    return PyFrensie::convertToPython( oss.str() );
  }

  // String representation method
  PyObject* __repr__() const
  {
    std::ostringstream oss;

    $self->print( oss );

    return PyFrensie::convertToPython( oss.str() );
  }
};

// Include the Ray class
%include "Geometry_Ray.hpp"

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
   model = PyFrensie.Geometry.createModel( 'my_geom.xml' )
   navigator = model.createNavigator()

   navigator.setInternalRay( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 )
   distance_to_surface_hit = navigator.fireInternalRay()
   navigator.advanceInternalRayToCellBoundary()

   ray_position = navigator.getInternalRayPosition()
   ray_cell = navigator.getCellContainingInternalRay()
 
   distance_to_surface_hit, surface_hit = navigator.fireInternalRayAndGetSurfaceHit()
   reflected = navigator.advanceInternalRayToCellBoundary()
   if( reflected ):
      print 'Surface ', surface_hit, ' reflected ray.'

   distance_to_surface_hit = navigator.fireInternalRay()
   navigator.advanceInternalRayBySubstep( 0.5*distance_to_surface_hit )
   navigator.changeInternalRayDirection( 0.0, 0.0, -1.0 )

   navigator.fireInternalRay()
   reflected, normal = navigator.advanceInternalRayToCellBoundaryAndGetSurfaceNormal()
"

%feature("autodoc",
"getPointLocation(Navigator self, Sequence position, Sequence direction, Long cell_id ) -> PointLocation
getPointLocation(Navigator self, Ray ray, Long cell_id) -> PointLocation

The position and direction sequences must have a size of three. The point
location returned can be one of three values:
   1. PyFrensie.Geometry.POINT_INSIDE_CELL
   2. PyFrensie.Geometry.POINT_ON_CELL
   3. PyFrensie.Geometry.POINT_OUTSIDE_CELL
" )
Geometry::Navigator::getPointLocation;

%feature("autodoc",
"getSurfaceNormal(Navigator self, Long surface_id, Sequence position, Sequence direction) -> Numpy Array
getSurfaceNormal(Navigator self, Long surface_id, Ray ray) -> Numpy Array

The position and direction sequences must have a size of three. The returned
value is a Numpy Array of size three.
" )
Geometry::Navigator::getSurfaceNormal;

%feature("autodoc",
"findCellContainingRay(Navigator self, Sequence position, Sequence direction) -> cell_id(Long)
findCellContainingRay(Navigator self, Ray ray) -> cell_id(Long)

The position and direction sequences must have a size of three.
" )
Geometry::Navigator::findCellContainingRay;

%feature("autodoc",
"setInternalRay(Navigator self, Float x_position, Float y_position, Float z_position, Float x_direction, Float y_direction, Float z_direction)
setInternalRay(Navigator self, Sequence position, Sequence direction)
setInternalRay(Navigator self, Ray ray)

setInternalRay(Navigator self, Float x_position, Float y_position, Float z_position, Float x_direction, Float y_direction, Float z_direction, Long cell_id)
setInternalRay(Navigator self, Sequence position, Sequence direction, Long cell_id)
setInternalRay(Navigator self, Ray ray, Long cell_id)

The position and direction sequences must have a size of three.
" )
Geometry::Navigator::setInternalRay;

%feature("autodoc", "getInternalRayPosition(Navigator self) -> Numpy Array")
Geometry::Navigator::getInternalRayPosition;

%feature("autodoc", "getInternalRayDirection(Navigator self) -> Numpy Array")
Geometry::Navigator::getInternalRayDirection;

%feature("docstring")
Geometry::Navigator::fireInternalRay
"
The distance to the surface that was hit will be returned.
"

%feature("autdoc",
"fireInternalRayAndGetSurfaceHit(Navigator self) -> [distance_to_surface(Float), surface_hit(Long)]
" )
Geometry::Navigator::fireInternalRayAndGetSurfaceHit;

%feature("docstring")
Geometry::Navigator::advanceInternalRayToCellBoundary
"
If a reflecting surface was encountered at the cell boundary True will be
returned. False will be returned if a normal surface was encountered.
"

%feature("autodoc",
"advanceInternalRayToCellBoundaryAndGetSurfaceNormal(Navigator self) -> [reflecting_surface(Bool),surface_normal(Numpy Array)]
" )
Geometry::Navigator::advanceInternalRayToCellBoundaryAndGetSurfaceNormal;

%feature("autodoc",
"changeInternalRayDirection(Navigator self, Float x_direction, Float y_direction, Float z_direction)
changeInternalRayDirection(Navigator self, Sequence direction)

The direction sequence must have a size of three.
" )
Geometry::Navigator::changeInternalRayDirection;

// Allow shared pointers of Navigator objects
%shared_ptr(Geometry::Navigator);

// Ignore the findCellContainingRay methods that take a cache
%ignore Geometry::Navigator::findCellContainingRay( const double[3], const double[3], Geometry::Navigator::CellIdSet& );
%ignore Geometry::Navigator::findCellContainingRay( const Ray&, Geometry::Navigator::CellIdSet& );

// Rename a few overloaded methods
%rename(fireInternalRayAndGetSurfaceHit) Geometry::Navigator::fireInternalRay( ModuleTraits::InternalSurfaceHandle* );
%rename(advanceInternalRayToCellBoundaryAndGetSurfaceNormal) Geometry::Navigator::advanceInternalRayToCellBoundary( double* );

// Add a few general type maps
%typemap(in,numinputs=0) Geometry::ModuleTraits::InternalSurfaceHandle* (Geometry::ModuleTraits::InternalSurfaceHandle temp) "$1 = &temp;"

%typemap(argout) Geometry::ModuleTraits::InternalSurfaceHandle* {
  %append_output(PyFrensie::convertToPython( *$1 ));
}

%typemap(in,numinputs=0) double normal[3] (std::vector<double> temp)
{
  temp.resize( 3 );
  $1 = temp.data();
}

%typemap(argout) double normal[3] {
  Teuchos::ArrayView<const double> output_view( $1, 3 );

  %append_output(PyFrensie::convertToPython( output_view ));
}

%typemap(in,numinputs=0) double* surface_normal (std::vector<double> temp)
{
  temp.resize( 3 );
  $1 = temp.data();
}

%typemap(argout) double* surface_normal {
  Teuchos::ArrayView<const double> output_view( $1, 3 );

  %append_output(PyFrensie::convertToPython( output_view ));
}

// Include the Navigator class
%include "Geometry_Navigator.hpp"

// Turn off the exception handling
%exception;

//---------------------------------------------------------------------------//
// end Geometry.__init__.i
//---------------------------------------------------------------------------//
