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

%pythonbegin
%{
  # With python 2.7.14 and swig version 3.0.10 the default generated import
  # code cannot find the ___init__.so file. Unfortunately the 'moduleimport'
  # option of the %module macro does not seem to work with this version
  # of swig either. To get the import code working we have to manually add
  # the current directory to the system path temporarily.

  import os.path
  import sys
  current_dir,file_name = os.path.split(__file__)
  sys.path.insert(0, current_dir)
%}

%include "Geometry_Config.i"

// // Set the special python variables
// %pythoncode
// %{
// # Remove the local current directory from the sys path (added to help
// # import code - see comment above)
// sys.path.pop(0)

// __all__ = ['DagMC'
//            ]
// %}

%{
// Std Lib Includes
#include <sstream>
#include <memory>

// FRENSIE Includes
#include "PyFrensie_PythonTypeTraits.hpp"
#include "Geometry_PointLocation.hpp"
#include "Geometry_EstimatorType.hpp"
#include "Geometry_ParticleType.hpp"
#include "Geometry_Model.hpp"
#include "Geometry_AdvancedModel.hpp"
#include "Geometry_Ray.hpp"
#include "Geometry_Navigator.hpp"
#include "Geometry_Exceptions.hpp"
#include "Utility_SerializationHelpers.hpp"
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

// Include the vector support
%include "PyFrensie_Array.i"

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
%ignore *::LengthUnit;
%ignore *::Length;
%ignore *::Ray;
%ignore *::AdvanceCompleteCallback;

// // Add a few general typedefs
// typedef unsigned long long InternalCellHandle;
// typedef unsigned long long InternalMaterialHandle;
// typedef unsigned long long InternalEstimatorHandle;
// typedef std::set<InternalCellHandle> CellIdSet;
// typedef Geometry::UnitAwareRay<Geometry::Navigator::LengthUnit>::Length Length;
// typedef Geometry::Navigator::Length Length2;

// Add a few general templates
%template(DoubleVector) std::vector<double>;

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
// Add support for the Ray class
//---------------------------------------------------------------------------//
// Include the Ray class
%include "Geometry_Ray.hpp"

// Add more detailed docstrings for the Ray class
%feature("docstring")
Geometry::UnitAwareRay<Geometry::Navigator::LengthUnit>
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
Geometry::UnitAwareRay<Geometry::Navigator::LengthUnit>::UnitAwareRay
"
The Ray object can be constructed with 6 doubles or two sequences (list,
tuple, numpy.array or a combination). Make sure that the direction is valid
(If Design-by-Contract is turned on in FRENSIE it will do the check for you.)
"

%feature("docstring")
Geometry::UnitAwareRay<Geometry::Navigator::LengthUnit>::getPosition
"
A NumPy array will be returned.
"

%feature("docstring")
Geometry::UnitAwareRay<Geometry::Navigator::LengthUnit>::getDirection
"
A NumPy array will be returned.
"

// Ignore the extra contructors
// %ignore Geometry::UnitAwareRay<void>::UnitAwareRay( double[3], double[3], const bool );
// %ignore Geometry::UnitAwareRay<void>::UnitAwareRay( double[3], double[3] );

// Ignore the toStream method
%ignore Geometry::UnitAwareRay<Geometry::Navigator::LengthUnit>::toStream;



// Add typemaps for converting Length to and from Python float
%typemap(in) const Geometry::UnitAwareRay<Geometry::Navigator::LengthUnit>::Length {
  $1 = Geometry::Navigator::Length::from_value( PyFrensie::convertFromPython<double>( $input ) );
}

%typemap(out) Geometry::UnitAwareRay<Geometry::Navigator::LengthUnit>::Length {
  %append_output(PyFrensie::convertToPython( Utility::getRawQuantity( $1 ) ) );
}

%typemap(typecheck, precedence=90) (const Geometry::UnitAwareRay<Geometry::Navigator::LengthUnit>::Length) {
  $1 = (PyFloat_Check($input)) ? 1 : 0;
}

// Add typemaps for converting Length* to and from Python array
%typemap(in) const Geometry::UnitAwareRay<Geometry::Navigator::LengthUnit>::Length[3] (std::vector<Geometry::UnitAwareRay<Geometry::Navigator::LengthUnit>::Length> temp_position){
  std::vector<double> raw_position = PyFrensie::convertFromPython<std::vector<double> >( $input );

  // Make sure the sequence has 3 elements
  if( raw_position.size() != 3 )
  {
    PyErr_SetString( PyExc_TypeError,
                     "The input position must have 3 elements." );
  }
  else
  {
    temp_position.resize(3);
    temp_position[0] = Geometry::Navigator::Length::from_value( raw_position[0] );
    temp_position[1] = Geometry::Navigator::Length::from_value( raw_position[1] );
    temp_position[2] = Geometry::Navigator::Length::from_value( raw_position[2] );

    $1 = temp_position.data();
  }
}

%typemap(out) const Geometry::UnitAwareRay<Geometry::Navigator::LengthUnit>::Length* {
  std::vector<double> raw_length(3);

  raw_length[0] = Utility::getRawQuantity($1[0]);
  raw_length[1] = Utility::getRawQuantity($1[1]);
  raw_length[2] = Utility::getRawQuantity($1[2]);

  %append_output(PyFrensie::convertToPython( raw_length ));

  // Utility::ArrayView<const double> output_view( raw_length.data(), 3 );
  // npy_intp dims[1] = { output_view.size() };

  // $result = PyArray_SimpleNewFromData( 1, dims, NPY_DOUBLE, (void*)output_view.data() );

  // if( !$result )
  //   SWIG_fail;
}

%typemap(typecheck, precedence=1050) (const Geometry::UnitAwareRay<Geometry::Navigator::LengthUnit>::Length[3]) {
  $1 = (PyArray_Check($input) || PySequence_Check($input)) ? 1 : 0;
}


// Add typemaps for converting direction (double*) to and from Python array
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

%typemap(out) const double* {
  Utility::ArrayView<const double> output_view( $1, 3 );

  npy_intp dims[1] = { output_view.size() };

  $result = PyArray_SimpleNewFromData( 1, dims, NPY_DOUBLE, (void*)output_view.data() );

  if( !$result )
    SWIG_fail;
}

// Add typecheck out for the Ray class
%typemap(typecheck, precedence=1050) (const double[3]) {
  $1 = (PyArray_Check($input) || PySequence_Check($input)) ? 1 : 0;
}


// Add some useful methods to the Ray class
%extend Geometry::UnitAwareRay<Geometry::Navigator::LengthUnit>
{
  // String conversion method
  PyObject* __str__() const
  {
    std::ostringstream oss;

    $self->toStream( oss );

    return PyFrensie::convertToPython( oss.str() );
  }

  // String representation method
  PyObject* __repr__() const
  {
    std::ostringstream oss;

    $self->toStream( oss );

    return PyFrensie::convertToPython( oss.str() );
  }
};

%template(Ray) Geometry::UnitAwareRay<Geometry::Navigator::LengthUnit>;

//---------------------------------------------------------------------------//
// Add support for the Navigator class
//---------------------------------------------------------------------------//

// Include the Navigator helpers
%include "Geometry_NavigatorHelpers.i"

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

   navigator.setState( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 )
   distance_to_surface_hit = navigator.fireRay()
   navigator.advanceToCellBoundary()

   ray_position = navigator.getPosition()
   ray_cell = navigator.getCellContainingPoint( ray_position )

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

// Ignore the findCellContainingRay methods that take a cache
%ignore Geometry::Navigator::findCellContainingRay( const double[3], const double[3], Geometry::Navigator::CellIdSet& );
%ignore Geometry::Navigator::findCellContainingRay( const Ray&, Geometry::Navigator::CellIdSet& );
%ignore Geometry::Navigator::findCellContainingRay( const Ray&, Geometry::Navigator::CellIdSet& ) const;

// Rename a few overloaded methods
%rename(fireRayAndGetSurfaceHit) Geometry::Navigator::fireRay( InternalSurfaceHandle* );
%rename(fireRayAndGetSurfaceHit2) Geometry::Navigator::fireRay( InternalSurfaceHandle& );
%rename(advanceToCellBoundaryAndGetSurfaceNormal) Geometry::Navigator::advanceToCellBoundary( double* );

// Add typemaps for the InternalSurfaceHandle
%typemap(in,numinputs=0) Geometry::Navigator::InternalSurfaceHandle* (Geometry::Navigator::InternalSurfaceHandle temp) "$1 = &temp;"

%typemap(argout) Geometry::Navigator::InternalSurfaceHandle* {
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

  // Utility::ArrayView<const double> output_view( $1, 3 );
  // npy_intp dims[1] = { output_view.size() };

  // $result = PyArray_SimpleNewFromData( 1, dims, NPY_DOUBLE, (void*)output_view.data() );

  // if( !$result )
  //   SWIG_fail;

  // // %append_output(PyFrensie::convertToPython( output_view ));
}

// Add typemaps for the CellIdSet
%typemap(in) Geometry::Navigator::CellIdSet& (std::set<unsigned long long> temp)
{
  $1 = &temp;
}

%typemap(argout) Geometry::Navigator::InternalSurfaceHandle* {
  %append_output(PyFrensie::convertToPython( *$1 ));
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

  // Utility::ArrayView<const double> output_view( $1, 3 );

  // npy_intp dims[1] = { output_view.size() };

  // $result = PyArray_SimpleNewFromData( 1, dims, NPY_DOUBLE, (void*)output_view.data() );

  // if( !$result )
  //   SWIG_fail;
}

// Add typemaps for converting the Length to and from a Python float/array
%apply const Geometry::UnitAwareRay<Geometry::Navigator::LengthUnit>::Length[3] { const Geometry::Navigator::Length[3] };
%apply const Geometry::UnitAwareRay<Geometry::Navigator::LengthUnit>::Length* { const Geometry::Navigator::Length* };
%apply const Geometry::UnitAwareRay<Geometry::Navigator::LengthUnit>::Length { const Geometry::Navigator::Length };
%apply Geometry::UnitAwareRay<Geometry::Navigator::LengthUnit>::Length { Geometry::Navigator::Length };

// Include the Navigator class
%include "Geometry_Navigator.hpp"

//---------------------------------------------------------------------------//
// Add support for the Model class
//---------------------------------------------------------------------------//

// Include the model helpers
%include "Geometry_ModelHelpers.i"

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

%model_interface_setup( Model )

// Add a few Geometry::Model typemaps
%typemap(out) Geometry::Model::Volume {
    $result = PyFloat_FromDouble( Utility::getRawQuantity($1) ); }

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
  std::map<Geometry::Model::InternalCellHandle,double> density_map;

  Geometry::Model::CellIdDensityMap::const_iterator it = ($1)->begin();

  while( it != ($1)->end() )
  {
    // insert raw elements in density_map
    density_map.insert(std::pair<Geometry::Model::InternalCellHandle,double> (it->first, it->second.value()));

    ++it;
  }

  %append_output(PyFrensie::convertToPython( density_map ));
}

%typemap(in,numinputs=0) Geometry::Model::CellEstimatorIdDataMap& (Geometry::Model::CellEstimatorIdDataMap temp) "$1 = &temp;"

%typemap(argout) Geometry::Model::CellEstimatorIdDataMap& {
  %append_output(PyFrensie::convertToPython( *$1 ) );
}

// // Add some useful methods to the Model class
// %extend Geometry::Model
// {
//   // String conversion method
//   PyObject* __str__() const
//   {
//     return PyFrensie::convertToPython( $self->getName() );
//   }

//   // String representation method
//   PyObject* __repr__() const
//   {
//     std::string string_rep( "Model(" );
//     string_rep += $self->getName();
//     string_rep += ")";

//     return PyFrensie::convertToPython( string_rep );
//   }

//   // Model comparison method
//   bool __eq__( const Geometry::Model& that ) const
//   {
//     return $self == &that;
//   }

//   // Model comparison method
//   bool __ne__( const Geometry::Model& that ) const
//   {
//     return $self != &that;
//   }
// };

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

%advanced_model_interface_setup( AdvancedModel )

// %feature("autodoc", "getSurfaces(Model self) -> set[surface_id]" )
// Geometry::AdvancedModel::getSurfaces;

// %feature("autodoc",
// "getSurfaceEstimatorData(Model self) -> dictionary[estimator_id,estimator_data]
// The mapped value (estimator_data) is a tuple of size three with the following
// elements:
//    1. Estimator type (e.g. Geometry.SURFACE_FLUX_ESTIMATOR)
//    2. Particle type (e.g. Geometry.NEUTRON)
//    3. Numpy array of surfaces assigned to this estimator
// " )
// Geometry::AdvancedModel::getSurfaceEstimatorData;

// // Allow shared pointers of AdvancedModel objects
// %shared_ptr(Geometry::AdvancedModel);

%typemap(in,numinputs=0) Geometry::AdvancedModel::SurfaceIdSet& (Geometry::AdvancedModel::SurfaceIdSet temp) "$1 = &temp;"

%typemap(argout) Geometry::AdvancedModel::SurfaceIdSet& {
  %append_output(PyFrensie::convertToPython( *$1 ));
}

// Add a few AdvancedModel typemaps
%typemap(out) Geometry::AdvancedModel::Area {
    $result = PyFloat_FromDouble( Utility::getRawQuantity($1) ); }

%typemap(in,numinputs=0) Geometry::AdvancedModel::SurfaceEstimatorIdDataMap& (Geometry::AdvancedModel::SurfaceEstimatorIdDataMap temp) "$1 = &temp;"

%typemap(argout) Geometry::AdvancedModel::SurfaceEstimatorIdDataMap& {
  %append_output(PyFrensie::convertToPython( *$1 ) );
}

// // Add some useful methods to the Model class
// %extend Geometry::AdvancedModel
// {
//   // String conversion method
//   PyObject* __str__() const
//   {
//     return PyFrensie::convertToPython( $self->getName() );
//   }

//   // String representation method
//   PyObject* __repr__() const
//   {
//     std::string string_rep( "Advanced Model(" );
//     string_rep += $self->getName();
//     string_rep += ")";

//     return PyFrensie::convertToPython( string_rep );
//   }
// }

// Include the AdvancedModel class
%include "Geometry_AdvancedModel.hpp"

// // //---------------------------------------------------------------------------//
// // // Add support for the ModelFactory class
// // //---------------------------------------------------------------------------//
// // // Import the ModelFactory class
// // %import "Geometry_ModelFactory.hpp"

// // %feature("autodoc",
// // "
// // createModel(String geometry_xml_file) -> Model

// // The string must be the file name (with path) of the xml file that describes
// // the geometry. Refer to the FRENSIE documentation regarding the proper way
// // to constuct this xml file
// // " )
// // createModel;

// // %feature("autodoc",
// // "
// // createAdvancedModel(String geometry_xml_file) -> AdvancedModel

// // The string must be the file name (with path) of the xml file that describes
// // the geometry. Refer to the FRENSIE documentation regarding the proper way
// // to constuct this xml file. If the geometry does not support the AdvancedModel
// // interface an exception will be thrown.
// // " )
// // createAdvancedModel;

// // %feature("autodoc",
// // "
// // makeModelAdvanced(Model model) -> AdvancedModel

// // If the geometry does not support the AdvancedModel
// // interface an exception will be thrown.
// // " )
// // makeModelAdvanced;

// // %feature("autodoc", "makeModelBasic(AdvancedModel model) -> Model" )
// // makeModelBasic;

// // %inline %{
// // std::shared_ptr<const Geometry::Model> createModel(
// //                                         const std::string& geom_rep_file_name )
// // {
// //   Utility::RCP<const Utility::ParameterList> geom_rep =
// //     Utility::getParametersFromXmlFile( geom_rep_file_name );

// //   return Geometry::ModelFactory::createModel( *geom_rep );
// // }

// // // This method will only work if the geometry supports advanced models
// // std::shared_ptr<const Geometry::AdvancedModel> createAdvancedModel(
// //                                         const std::string& geom_rep_file_name )
// // {
// //   return std::dynamic_pointer_cast<const Geometry::AdvancedModel>(
// //                                            createModel( geom_rep_file_name ) );
// // }

// // // Convert an existing model to an advanced model. This method will only
// // // work if the geometry supports advanced models
// // std::shared_ptr<const Geometry::AdvancedModel> makeModelAdvanced(
// //                           const std::shared_ptr<const Geometry::Model>& model )
// // {
// //   return std::dynamic_pointer_cast<const Geometry::AdvancedModel>( model );
// // }

// // // Convert an existing advanced model to a basic model.
// // std::shared_ptr<const Geometry::Model> makeModelBasic(
// //                   const std::shared_ptr<const Geometry::AdvancedModel>& model )
// // {
// //   return model;
// // }
// // %}

// Specific geometry type support
// %include "Geometry_DagMC.i"
// %include "Geometry_Root.i"

// Turn off the exception handling
%exception;

//---------------------------------------------------------------------------//
// end Geometry.__init__.i
//---------------------------------------------------------------------------//
