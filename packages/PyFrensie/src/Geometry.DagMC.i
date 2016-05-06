//---------------------------------------------------------------------------//
//!
//! \file    Geometry.DagMC.i
//! \author  Alex Robinson
//! \brief   The Geometry.DagMC sub-module
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
// Trilinos Includes
#include "PyTrilinos_config.h"
#include "Teuchos_Comm.hpp"
#include "Teuchos_DefaultSerialComm.hpp"
#ifdef HAVE_MPI
#include "Teuchos_DefaultMpiComm.hpp"
#endif // end HAVE_MPI
  
// FRENSIE Includes
#include "PyFrensie_ArrayConversionHelpers.hpp"
#include "MonteCarlo_ModuleTraits.hpp"
#include "Geometry_ModuleTraits.hpp"
#include "Geometry_DagMC.hpp"
#include "Geometry_DagMCInstanceFactory.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_ContractException.hpp"
%}

// C++ STL support
// Note: stl.i provides typemaps for std::string which allows one to
// use python strings seamlessly with any wrapped c++ method that would
// normally take a std::string
%include <stl.i>
%include <std_vector.i>
%include <std_except.i>

// Include typemaps support
%include <typemaps.i>

// Import the PyFrensie Teuchos Array conversion helpers
%import "PyFrensie_ArrayConversionHelpers.hpp"

// Import the ModuleTraits classes
%import "MonteCarlo_ModuleTraits.hpp"
%import "Geometry_ModuleTraits.hpp"

// Import the Tuple classes
%import "Utility_Tuple.hpp"

// Import the Geometry.__init__.i file
%import "Geometry.__init__.i"

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
  catch( Geometry::InvalidDagMCGeometry& e )
  {
    SWIG_exception( SWIG_RuntimeError, e.what() );
  }
  catch( Geometry::DagMCGeometryError& e )
  {
    SWIG_exception( SWIG_RuntimeError, e.what() );
  }
  catch( ... )
  {
    SWIG_exception( SWIG_UnknownError, "Unknown C++ exception" );
  }
}

//---------------------------------------------------------------------------//
// Add support for the DagMC class
//---------------------------------------------------------------------------//
// Add more detailed docstrings for the DagMC class
%feature("docstring")
Geometry::DagMC
"
The DagMC class can be used to interact with a CAD file that has been 
set up for use with FRENSIE. The query methods have been grouped into several
groups based on the level of the information that is sought. Some of these
query methods can be called before the geometry has been loaded:

CAD File Properties:
  *setTerminationCellPropertyName
  *getTerminationCellPropertyName
  *setReflectingSurfacePropertyName
  *getReflectingSurfacePropertyName
  *setMaterialPropertyName
  *getMaterialPropertyName
  *setDensityPropertyName
  *getDensityPropertyName
  *setEstimatorPropertyName
  *getEstimatorPropertyName
  *setSurfaceCurrentName
  *getSurfaceCurrentName
  *setSurfaceFluxName
  *getSurfaceFluxName
  *setCellPulseHeightName
  *getCellPulseHeightName
  *setCellTrackLengthFluxName
  *getCellTrackLengthFluxName
  *setCellCollisionFluxName
  *getCellCollisionFluxName
  *isInitialized

Others must only be called after the geometry has been loaded:

Geometry Properties:
  *doesCellExist
  *doesSurfaceExist
  *isTerminationCell
  *isVoidCell
  *isReflectingSurface. 
  *getCells
  *getSurfaces

Geometric Entity Properties:
  *getCellVolume
  *getCellMaterialIds
  *getCellDensities
  *getSurfaceArea

Estimator Properties:
  *getCellEstimatorData
  *getSurfaceEstimatorData
  

The initialize method is used to load the CAD file and parse its properties and
geometric information. It is recommended that one use
PyFrensie.Geometry.DagMC.initializeDagMC to load the geometry instead
of calling the initialize method directly. Once the geometry has been one may
ray trace on the geometry. This can be useful for debugging ray trace errors
encountered while running Monte Carlo particle simulations. A brief usage
tutorial for this class is shown below:

  import PyFrensie.Geometry.DagMC as DagMC

  geom = DagMC.DagMC
  
  geom.initialize( 'my_cad_file.sat', 1e-3 )

  ray = PyFrensie.Geometry.Ray( 0, 0, 0, 0, 0, 1 )

  cell = geom.findCellContainingExternalRay( ray )
  distance_to_surface,surface_id = geom.fireExternalRay( ray, cell )

  ray.advanceHead( distance_to_surface )

  cell = geom.getBoundaryCell( cell, surface_id )

  distance_to_surface,surface_id = geom.fireExternalRay( ray, cell )

  geom.setInternalRay( ray )

  cell = geom.findCellContainingInternalRay()

  distance_to_surface,surface_id = geom.fireInternalRay()

  geom.advanceInternalRayToCellBoundary()

  cell = geom.findCellContainingInternalRay()
"

%feature("docstring")
Geometry::DagMC::fireExternalRay
"The first value returned is the distance to the nearest surface in the
direction of the ray. The second value returned is the surface id of the 
surface that will be hit by the ray.
"

%feature("autodoc",
"fireInternalRay() -> double,unsigned long long

The first value returned is the distance to the nearest surface in the 
direction of the ray. The second value returned is the surface id of the
surface that will be hit by the ray.
")
Geometry::DagMC::fireInternalRay;

// Add a few general typemaps
%apply Geometry::ModuleTraits::InternalCellHandle& OUTPUT { Geometry::ModuleTraits::InternalSurfaceHandle& surface_hit }

// Ignore the methods that receive or return pointers - new ones will be
// created that receive or return Python objects
%ignore Geometry::DagMC::getSurfaceNormal( const ModuleTraits::InternalSurfaceHandle, const double[3], double[3] );
%ignore Geometry::DagMC::setInternalRay( const double[3], const double[3], const bool );
%ignore Geometry::DagMC::setInternalRay( const double[3], const double[3], const ModuleTraits::InternalCellHandle, const bool );
%ignore Geometry::DagMC::changeInternalRayDirection( const double[3] );

// Add some useful methods to the DagMC class
%extend Geometry::DagMC
{
  // Set the internal ray
  static void setInternalRay( PyObject* py_array_position,
                              PyObject* py_array_direction,
                              const bool cache_start_cell )
  {
    Teuchos::Array<double> position;

    %convert_python_position_to_teuchos( py_array_position, position );

    Teuchos::Array<double> direction;

    %convert_python_direction_to_teuchos( py_array_direction, direction );

    Geometry::DagMC::setInternalRay( position.getRawPtr(),
                                     direction.getRawPtr(),
                                     cache_start_cell );
  }

  // Set the internal ray
  static void setInternalRay(
                           PyObject* py_array_position,
                           PyObject* py_array_direction,
                           const ModuleTraits::InternalCellHandle current_cell,
                           const bool cache_start_cell )
  {
    Teuchos::Array<double> position;

    %convert_python_position_to_teuchos( py_array_position, position );

    Teuchos::Array<double> direction;

    %convert_python_direction_to_teuchos( py_array_direction, direction );

    Geometry::DagMC::setInternalRay( position.getRawPtr(),
                                     direction.getRawPtr(),
                                     current_cell,
                                     cache_start_cell );
  }
  
  // Set the internal ray
  static void setInternalRay( PyObject* py_array_position,
                              PyObject* py_array_direction )
  {
    Teuchos::Array<double> position;

    %convert_python_position_to_teuchos( py_array_position, position );

    Teuchos::Array<double> direction;

    %convert_python_direction_to_teuchos( py_array_direction, direction );

    Geometry::DagMC::setInternalRay( position.getRawPtr(),
                                     direction.getRawPtr(),
                                     false );
  }

  // Set the internal ray
  static void setInternalRay(
                          PyObject* py_array_position,
                          PyObject* py_array_direction,
                          const ModuleTraits::InternalCellHandle current_cell )
  {
    Teuchos::Array<double> position;

    %convert_python_position_to_teuchos( py_array_position, position );

    Teuchos::Array<double> direction;

    %convert_python_direction_to_teuchos( py_array_direction, direction );

    Geometry::DagMC::setInternalRay( position.getRawPtr(),
                                     direction.getRawPtr(),
                                     current_cell,
                                     false );
  }

  // Get the surface normal at a point on the surface
  static PyObject* getSurfaceNormal(
                          const ModuleTraits::InternalSurfaceHandle surface_id,
                          PyObject* py_array_position )
  {
    Teuchos::Array<double> position;

    %convert_python_position_to_teuchos( py_array_position, position );

    Teuchos::Array<double> normal( 3 );

    Geometry::DagMC::getSurfaceNormal( surface_id,
                                       position.getRawPtr(),
                                       normal.getRawPtr() );

    return PyFrensie::copyTeuchosToNumPy( normal );
  }
                              
  // Get the internal DagMC ray position
  static PyObject* getInternalRayPosition()
  {
    Teuchos::ArrayView<const double> position(
                                Geometry::DagMC::getInternalRayPosition(), 3 );

    return PyFrensie::copyTeuchosToNumPy( position );
  }

  // Get the internal DagMC ray direction
  static PyObject* getInternalRayDirection()
  {
    Teuchos::ArrayView<const double> direction(
                               Geometry::DagMC::getInternalRayDirection(), 3 );

    return PyFrensie::copyTeuchosToNumPy( direction );
  }
};

// Include the DagMC class
%include "Geometry_DagMC.hpp"

// Include the geometry helpers
%include "Geometry_Helpers.i"

%standard_geom_template_extends( DagMC );

// Instantiate the template getSurfaces method
%template(getSurfaces) Geometry::DagMC::getSurfaces<std::set<unsigned long long> >;

// Instantiate the template getFoundCellCache method
%template(getFoundCellCache) Geometry::DagMC::getFoundCellCache<std::set<unsigned long long> >;

// Add methods that return a std::set (since the OUTPUT typemaps don't seem
// to work in this case)
%extend Geometry::DagMC
{
  // Output the surface ids set
  static std::set<unsigned long long> getSurfaces()
  {
    std::set<unsigned long long> surface_ids;
    Geometry::DagMC::getSurfaces( surface_ids );

    return surface_ids;
  }

  // Get the found cell cache
  static std::set<unsigned long long> getFoundCellCache()
  {
    std::set<unsigned long long> cache;
    Geometry::DagMC::getFoundCellCache( cache );

    return cache;
  }
};

// Instantiate a vector of unsigned lon long
%template(CellIdArray) std::vector<unsigned long long>;

// Istantiate a triplet of string,string,CellIdArray
%template(EstimatorData) Utility::Trip<std::string,std::string,std::vector<unsigned long long> >;

// Instantiate an estimator id to estimator data map
%template(EstimatorIdDataMap) std::map<unsigned int, Utility::Trip<std::string,std::string,std::vector<unsigned long long> > >;

// Instantiate the template getCellEstimatorData method
%template(getCellEstimatorData) Geometry::DagMC::getCellEstimatorData<std::map<unsigned int, Utility::Trip<std::string,std::string,std::vector<unsigned long long> > > >;

// Instantiate the template getSurfaceEstimatorData method
%template(getSurfaceEstimatorData) Geometry::DagMC::getSurfaceEstimatorData<std::map<unsigned int, Utility::Trip<std::string,std::string,std::vector<unsigned long long> > > >;

// Add method that returns a std::map (since the OUTPUT typemaps don't seem
// to work in this case)
%extend Geometry::DagMC
{
  // Output the cell estimator id to data map
  static std::map<unsigned int, Utility::Trip<std::string,std::string,std::vector<unsigned long long> > > getCellEstimatorData()
  {
    std::map<unsigned int, Utility::Trip<std::string,std::string,std::vector<unsigned long long> > > cell_estimator_data_map;
    Geometry::DagMC::getCellEstimatorData( cell_estimator_data_map );

    return cell_estimator_data_map;
  }

  // Output the surface estimator id to data map
  static std::map<unsigned int, Utility::Trip<std::string,std::string,std::vector<unsigned long long> > > getSurfaceEstimatorData()
  {
    std::map<unsigned int, Utility::Trip<std::string,std::string,std::vector<unsigned long long> > > surface_estimator_data_map;
    Geometry::DagMC::getSurfaceEstimatorData( surface_estimator_data_map );

    return surface_estimator_data_map;
  }
};

//---------------------------------------------------------------------------//
// Add support for the DagMCInstanceFactory class
//---------------------------------------------------------------------------//
// Add more detailed docstrings for the DagMCInstanceFactory class
%feature("docstring")
initializeDagMC
"
This is the recommended way to initialize a DagMC geometry. The 
PyTrilinos.Teuchos.ParameterList object should store all of the
CAD file properties and the DagMC initialization options. A brief usage
tutorial for this class is shown below:

  import PyFrensie.Geometry.DagMC, PyTrilinos.Teuchos, numpy
 
  source = PyTrilinos.Teuchos.FileInputSource( 'my_geom_file.xml' )
  xml_obj = source.getObject()
  geom_init_list = PyTrilinos.Teuchos.XMLParameterListReader().toParameterList( xml_obj )

  PyFrensie.Geometry.DagMC.initializeDagMC( geom_init_list )

  geom = PyFrensie.Geometry.DagMC.DagMC
  geom.isInitialized()
"
 
// Import the Teuchos_ParameterList interface
%import <Teuchos.i>

// Import the DagMCInstanceFactory class
%import "Geometry_DagMCInstanceFactory.hpp"

%inline %{
void initializeDagMC( const Teuchos::ParameterList& geom_rep )
{
  Geometry::DagMCInstanceFactory::initializeDagMC( geom_rep );
}
%}

// Turn off the exception handling
%exception;

//---------------------------------------------------------------------------//
// Geometry.DagMC.i
//---------------------------------------------------------------------------//
