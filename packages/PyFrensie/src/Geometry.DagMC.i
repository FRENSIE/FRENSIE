//---------------------------------------------------------------------------//
//!
//! \file    Geometry.DagMC.i
//! \author  Luke Kersting
//! \brief   The Geometry.DagMC sub-module swig interface file
//!
//---------------------------------------------------------------------------//

%define %geometry_dagmc_docstring
"
PyFrensie.Geometry.DagMC is the python interface to the FRENSIE geometry/dagmc
subpackage.

The purpose of DagMC is to allow a user to query CAD geometry data and to
ray trace on a CAD geometry using python. This can be useful for debugging
geometries.
"
%enddef

%module(package   = "PyFrensie.Geometry",
        autodoc   = "1",
        docstring = %geometry_dagmc_docstring) DagMC

%{

// Std Lib Includes
#include <memory>
// #include <sstream>

// FRENSIE Includes
#include "PyFrensie_PythonTypeTraits.hpp"
// #include "Geometry_PointLocation.hpp"
// #include "Geometry_EstimatorType.hpp"
// #include "Geometry_ParticleType.hpp"
// #include "Geometry_Model.hpp"
// #include "Geometry_AdvancedModel.hpp"
// #include "Geometry_Ray.hpp"
// #include "Geometry_Navigator.hpp"
#include "Geometry_Exceptions.hpp"
// #include "Utility_SerializationHelpers.hpp"
// #include "Utility_ContractException.hpp"

// FRENSIE Includes
#include "Geometry_DagMCModelProperties.hpp"
#include "Geometry_DagMCModel.hpp"
#include "Geometry_DagMCRay.hpp"
#include "Geometry_DagMCNavigator.hpp"
#include "Geometry_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_SerializationHelpers.hpp"
%}

// // C++ STL support
%include <stl.i>
// %include <std_string.i>
// %include <std_set.i>
// %include <std_map.i>
// %include <std_vector.i>
%include <std_except.i>
%include <std_shared_ptr.i>

// Include typemaps support
%include <typemaps.i>

// Import the Geometry.__init__.i file
%import "Geometry.__init__.i"

// // Include the vector support
// %include "PyFrensie_Array.i"

// // Standard exception handling
// %include "exception.i"

// // Global swig features
// %feature("autodoc", "1");

// // General exception handling
// %exception
// {
//   try{
//     $action;
//     if( PyErr_Occurred() )
//       SWIG_fail;
//   }
//   catch( Utility::ContractException& e )
//   {
//     SWIG_exception( SWIG_ValueError, e.what() );
//   }
//   catch( Geometry::InvalidGeometryRepresentation& e )
//   {
//     SWIG_exception( SWIG_RuntimeError, e.what() );
//   }
//   catch( std::runtime_error& e )
//   {
//     SWIG_exception( SWIG_RuntimeError, e.what() );
//   }
//   catch( ... )
//   {
//     SWIG_exception( SWIG_UnknownError, "Unknown C++ exception" );
//   }
// }

// // General ignore directives
// %ignore *::LengthUnit;
// %ignore *::Length;
// %ignore *::Ray;
// %ignore *::AdvanceCompleteCallback;

// Add a few general templates
%template(StringVector) std::vector<std::string>;

// Add a few general typemaps
%apply std::vector<std::string>& OUTPUT { std::vector<std::string>& properties };
// typedef unsigned long long InternalMaterialHandle;
// typedef unsigned long long InternalEstimatorHandle;
// typedef std::set<InternalCellHandle> CellIdSet;
// typedef Geometry::UnitAwareRay<void>::Length Length;

//---------------------------------------------------------------------------//
// Add support for the DagMCModelProperties class
//---------------------------------------------------------------------------//
// Include the DagMCModelProperties class
%include "Geometry_DagMCModelProperties.hpp"

//---------------------------------------------------------------------------//
// Add support for the DagMCNavigator class
//---------------------------------------------------------------------------//

%feature("docstring")
Geometry::DagMCNavigator
"
The DagMCNavigator class is primarily used to traverse a Model. Some geometric data,
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

%feature("autodoc",
"getPointLocation(DagMCNavigator self, Sequence position, Sequence direction, Long cell_id ) -> PointLocation
getPointLocation(DagMCNavigator self, Ray ray, Long cell_id) -> PointLocation

The position and direction sequences must have a size of three. The point
location returned can be one of three values:
   1. PyFrensie.Geometry.POINT_INSIDE_CELL
   2. PyFrensie.Geometry.POINT_ON_CELL
   3. PyFrensie.Geometry.POINT_OUTSIDE_CELL
" )
Geometry::DagMCNavigator::getPointLocation;

%feature("autodoc",
"getSurfaceNormal(DagMCNavigator self, Long surface_id, Sequence position, Sequence direction) -> Numpy Array
getSurfaceNormal(DagMCNavigator self, Long surface_id, Ray ray) -> Numpy Array

The position and direction sequences must have a size of three. The returned
value is a Numpy Array of size three.
" )
Geometry::DagMCNavigator::getSurfaceNormal;

%feature("autodoc",
"findCellContainingRay(DagMCNavigator self, Sequence position, Sequence direction) -> cell_id(Long)
findCellContainingRay(DagMCNavigator self, Ray ray) -> cell_id(Long)

The position and direction sequences must have a size of three.
" )
Geometry::DagMCNavigator::findCellContainingRay;

%feature("autodoc",
"setRay(DagMCNavigator self, Float x_position, Float y_position, Float z_position, Float x_direction, Float y_direction, Float z_direction)
setRay(DagMCNavigator self, Sequence position, Sequence direction)
setRay(DagMCNavigator self, Ray ray)

setRay(DagMCNavigator self, Float x_position, Float y_position, Float z_position, Float x_direction, Float y_direction, Float z_direction, Long cell_id)
setRay(DagMCNavigator self, Sequence position, Sequence direction, Long cell_id)
setRay(DagMCNavigator self, Ray ray, Long cell_id)

The position and direction sequences must have a size of three.
" )
Geometry::DagMCNavigator::setState;

%feature("autodoc", "getPosition(DagMCNavigator self) -> Numpy Array")
Geometry::DagMCNavigator::getPosition;

%feature("autodoc", "getDirection(DagMCNavigator self) -> Numpy Array")
Geometry::DagMCNavigator::getDirection;

%feature("docstring")
Geometry::DagMCNavigator::fireRay
"
The distance to the surface that was hit will be returned.
"

%feature("autdoc",
"fireRayAndGetSurfaceHit(DagMCNavigator self) -> [distance_to_surface(Float), surface_hit(Long)]
" )
Geometry::DagMCNavigator::fireRayAndGetSurfaceHit;

%feature("docstring")
Geometry::DagMCNavigator::advanceToCellBoundary
"
If a reflecting surface was encountered at the cell boundary True will be
returned. False will be returned if a normal surface was encountered.
"

%feature("autodoc",
"advanceToCellBoundaryAndGetSurfaceNormal(DagMCNavigator self) -> [reflecting_surface(Bool),surface_normal(Numpy Array)]
" )
Geometry::DagMCNavigator::advanceToCellBoundaryAndGetSurfaceNormal;

%feature("autodoc",
"changeInternalRayDirection(DagMCNavigator self, Float x_direction, Float y_direction, Float z_direction)
changeInternalRayDirection(DagMCNavigator self, Sequence direction)

The direction sequence must have a size of three.
" )
Geometry::DagMCNavigator::changeDirection;

// Allow shared pointers of DagMCNavigator objects
%shared_ptr(Geometry::DagMCNavigator);

// Ignore the findCellContainingRay methods that take a cache
%ignore Geometry::DagMCNavigator::findCellContainingRay( const double[3], const double[3], Geometry::Navigator::CellIdSet& );
%ignore Geometry::DagMCNavigator::findCellContainingRay( const Ray&, Geometry::Navigator::CellIdSet& );
%ignore Geometry::DagMCNavigator::findCellContainingRay( const Ray&, Geometry::Navigator::CellIdSet& ) const;

// Rename a few overloaded methods
%rename(fireRayAndGetSurfaceHit) Geometry::DagMCNavigator::fireRay( InternalSurfaceHandle* );
%rename(fireRayAndGetSurfaceHit2) Geometry::DagMCNavigator::fireRay( InternalSurfaceHandle& );
%rename(advanceToCellBoundaryAndGetSurfaceNormal) Geometry::DagMCNavigator::advanceToCellBoundary( double* );

// Add a few general type maps
%typemap(in,numinputs=0) Geometry::DagMCNavigator::InternalSurfaceHandle* (Geometry::Navigator::InternalSurfaceHandle temp) "$1 = &temp;"

%typemap(argout) Geometry::Navigator::InternalSurfaceHandle* {
  %append_output(PyFrensie::convertToPython( *$1 ));
}

%typemap(in,numinputs=0) double normal[3] (std::vector<double> temp)
{
  temp.resize( 3 );
  $1 = temp.data();
}

%typemap(argout) double normal[3] {
  Utility::ArrayView<const double> output_view( $1, 3 );

  npy_intp dims[1] = { output_view.size() };

  $result = PyArray_SimpleNewFromData( 1, dims, NPY_DOUBLE, (void*)output_view.data() );

  if( !$result )
    SWIG_fail;

  // %append_output(PyFrensie::convertToPython( output_view ));
}

%typemap(in,numinputs=0) double* surface_normal (std::vector<double> temp)
{
  temp.resize( 3 );
  $1 = temp.data();
}

%typemap(argout) double* surface_normal {
  Utility::ArrayView<const double> output_view( $1, 3 );

  npy_intp dims[1] = { output_view.size() };

  $result = PyArray_SimpleNewFromData( 1, dims, NPY_DOUBLE, (void*)output_view.data() );

  if( !$result )
    SWIG_fail;

  // %append_output(PyFrensie::convertToPython( output_view ));
}

%typemap(in) Geometry::Navigator::CellIdSet& (std::set<unsigned long long> temp)
{
  std::cout << std::setprecision(16) << std::scientific << "Typemap called" << std::endl;

  $1 = &temp;
}

%typemap(argout) Geometry::Navigator::InternalSurfaceHandle* {
  %append_output(PyFrensie::convertToPython( *$1 ));
}

%typemap(in,numinputs=0) double normal[3] (std::vector<double> temp)
{
  temp.resize( 3 );
  $1 = temp.data();
}

// Include the DagMCNavigator class
%include "Geometry_DagMCNavigator.hpp"

//---------------------------------------------------------------------------//
// Add support for the DagMCModel class
//---------------------------------------------------------------------------//

// Add more detailed docstrings for the DagMCModel class
%feature("docstring")
Geometry::DagMCModel
"
The DagMCModel class stores a geometric model, which can be from a CAD (.sat) file
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


%feature("autodoc", "getInstance() -> shared_ptr<DagMCModel>" )
Geometry::DagMCModel::getInstance;

%feature("autodoc", "isInitialized() -> bool" )
Geometry::DagMCModel::isInitialized;

%feature("autodoc", "getMaterialIds(DagMCModel self) -> set[material_id]" )
Geometry::DagMCModel::getMaterialIds;

%feature("autodoc", "getCells(DagMCModel self, bool include_void_cells, bool include_termination_cells) -> set[cell_id]")
Geometry::DagMCModel::getCells;

%feature("autodoc","getCellMaterialIds(DagMCModel self) -> dictionary[cell_id,material_id]" )
Geometry::DagMCModel::getCellMaterialIds;

%feature("autodoc", "getCellDensities(DagMCModel self) -> dictionary[cell_id,density(float)]" )
Geometry::DagMCModel::getCellDensities;

%feature("autodoc",
"getCellEstimatorData(DagMCModel self) -> dictionary[estimator_id,estimator_data]

The mapped value (estimator_data) is a tuple of size three with the following
elements:
   1. Estimator type (e.g. Geometry.CELL_TRACK_LENGTH_FLUX_ESTIMATOR)
   2. Particle type (e.g. Geometry.NEUTRON)
   3. Numpy array of cells assigned to this estimator
" )
Geometry::DagMCModel::getCellEstimatorData;

%feature("autodoc", "createNavigator(DagMCModel self) -> Navigator" )
Geometry::DagMCModel::createNavigator;

// Allow shared pointers of DagMCNavigator objects
%shared_ptr(Geometry::DagMCModel);

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

// %typemap(in,numinputs=0) Geometry::Model::CellEstimatorIdDataMap& (Geometry::Model::CellEstimatorIdDataMap temp) "$1 = &temp;"

// %typemap(argout) Geometry::Model::CellEstimatorIdDataMap& {
//   std::map<Geometry::Model::InternalEstimatorHandle,Geometry::Model::CellEstimatorData> temp;

//   // %append_output(PyFrensie::convertToPython( temp ));
//   PyObject* py_array;
//   return py_array;
// }

// Add some useful methods to the DagMCModel class
%extend Geometry::DagMCModel
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

  // DagMCModel comparison method
  bool __eq__( const Geometry::DagMCModel& that ) const
  {
    return $self == &that;
  }

  // DagMCModel comparison method
  bool __ne__( const Geometry::DagMCModel& that ) const
  {
    return $self != &that;
  }
};

// Include the DagMCModel class
%include "Geometry_DagMCModel.hpp"

// //---------------------------------------------------------------------------//
// // Add support for the DagMCRay class
// //---------------------------------------------------------------------------//

// // Add more detailed docstrings for the DagMCRay class
// %feature("docstring")
// Geometry::DagMCRay
// "
// The Ray stores the state of a ray object (position and direction). A brief
// usage tutorial for this class is shown below:

//    import PyFrensie.Geometry, numpy

//    ray1 = PyFrensie.Geometry.Ray( 0, 0, 0, 0, 0, 1 )
//    ray2 = PyFrensie.Geometry.Ray( (0.,0.,0.), (0.,0.,1.) )
//    ray3 = PyFrensie.Geometry.Ray( [0.,0.,0.], [0.,0.,1.] )
//    ray4 = PyFrensie.Geometry.Ray( numpy.array( [0,0,0], dtype=numpy.dtype('d') ), numpy.array( [0,0,1], dtype=numpy.dtype('d') ) )

//    ray1.getPosition()
//    ray1.getDirection()

//    ray1.advanceHead( 1 )
//    ray1.changeDirection( 0, 1, 0 )
//    ray1.advanceHead( 1 )
// "

// %feature("docstring")
// Geometry::DagMCRay::DagMCRay
// "
// The Ray object can be constructed with 6 doubles or two sequences (list,
// tuple, numpy.array or a combination). Make sure that the direction is valid
// (If Design-by-Contract is turned on in FRENSIE it will do the check for you.)
// "

// %feature("docstring")
// Geometry::DagMCRay::getPosition
// "
// A NumPy array will be returned.
// "

// %feature("docstring")
// Geometry::DagMCRay::getDirection
// "
// A NumPy array will be returned.
// "

// // Ignore the extra contructors
// %ignore Geometry::DagMCRay::DagMCRay( double[3], double[3], const bool );
// %ignore Geometry::DagMCRay::DagMCRay( double[3], double[3] );

// // Add a general typemap that will convert the input position from a Python
// // Array object to a double*.
// %typemap(in) const double position[3] (std::vector<double> temp_position){
//   temp_position =
//     PyFrensie::convertFromPython<std::vector<double> >( $input );

//   // Make sure the sequence has 3 elements
//   if( temp_position.size() != 3 )
//   {
//     PyErr_SetString( PyExc_TypeError,
//                      "The input position must have 3 elements." );
//   }

//   $1 = temp_position.data();
// }

// // Add a general typemap that will convert the input direction from a Python
// // array object to a double*
// %typemap(in) const double direction[3] (std::vector<double> temp_direction){
//   temp_direction =
//     PyFrensie::convertFromPython<std::vector<double> >( $input );

//   // Make sure the sequence has 3 elements
//   if( temp_direction.size() != 3 )
//   {
//     PyErr_SetString( PyExc_TypeError,
//                      "The input direction must have 3 elements." );
//   }

//   $1 = temp_direction.data();
// }

// // The typecheck precedence, which is used by SWIG to determine which
// // overloaded method should be called, should be set to
// // SWIG_TYPECHECK_DOUBLE_ARRAY (1050) for the C double arrays. You will get a
// // Python error when calling the overloaded method in Python without this
// // typecheck
// %typemap(typecheck, precedence=1050) (const double[3]) {
//   $1 = (PyArray_Check($input) || PySequence_Check($input)) ? 1 : 0;
// }

// // Add a general typemap that will convert the output position or direction
// // from a double* to a Python array object
// %typemap(out) const double* {
//   Utility::ArrayView<const double> output_view( $1, 3 );

//   npy_intp dims[1] = { output_view.size() };

//   $result = PyArray_SimpleNewFromData( 1, dims, NPY_DOUBLE, (void*)output_view.data() );

//   if( !$result )
//     SWIG_fail;

//   // $result = PyFrensie::convertToPython( output_view );
// }

// // Include the DagMCRay class
// %include "Geometry_DagMCRay.hpp"

//---------------------------------------------------------------------------//
// end Geometry.DagMC.i
//---------------------------------------------------------------------------//e
