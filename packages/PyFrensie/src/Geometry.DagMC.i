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
%include <std_set.i>
%include <std_map.i>

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
Geometry::DagMC::getCellEstimatorData
"
This method will return an EstimatorIdDataMap that contains the estimators ids
and their assigned data.
"

%feature("docstring")
Geometry::DagMC::getSurfaceEstimatorData
"
This method will return an EstimatorIdDataMap that contains the estimators ids
and their assigned data.
"

%feature("docstring")
Geometry::DagMC::getMaterialIds
"
This method will return an IdSet that contains the material ids.
"

%feature("docstring")
Geometry::DagMC::getCells
"
This method will return an IdSet that contains the cells.
"

%feature("docstring")
Geometry::DagMC::getSurfaces
"
This method will return an IdSet that contains the surfaces.
"

%feature("docstring")
Geometry::DagMC::getFoundCellCache
"
This method will return an IdSet that contains the cached cells.
"

%feature("docstring")
Geometry::DagMC::getCellMaterialIds
"
This method will return a CellIdMatIdMap that contains the cells and their
assigned material ids.
"

%feature("docstring")
Geometry::DagMC::getCellDensities
"
This method will return a CellIdDensityMap that contains the cells and their
assigned densities.
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

%feature("autodoc",
"advanceInternalRayToCellBoundary()
advanceInternalRayToCellBoundary() -> bool, numpy.array

The first return value indicates if a reflecting surface was encountered. The
second return value is the surface normal at the surface intersection point.
")
Geometry::DagMC::advanceInternalRayToCellBoundary;

// Typemaps for id sets that convert the inout set to an output set
%typemap(in,numinputs=0) std::set<unsigned long long>& cell_set (std::set<unsigned long long> temp) "$1 = &temp;"

%typemap(argout) std::set<unsigned long long>& cell_set {
  %append_output(SWIG_NewPointerObj(new std::set<unsigned long long>( *$1 ), SWIGTYPE_p_std__setT_unsigned_long_long_std__lessT_unsigned_long_long_t_std__allocatorT_unsigned_long_long_t_t, SWIG_POINTER_OWN |  0 ));
}

%typemap(in,numinputs=0) std::set<unsigned long long>& cached_cells (std::set<unsigned long long> temp) "$1 = &temp;"

%typemap(argout) std::set<unsigned long long>& cached_cells {
  %append_output(SWIG_NewPointerObj(new std::set<unsigned long long>( *$1 ), SWIGTYPE_p_std__setT_unsigned_long_long_std__lessT_unsigned_long_long_t_std__allocatorT_unsigned_long_long_t_t, SWIG_POINTER_OWN |  0 ));
}

%typemap(in,numinputs=0) std::set<unsigned long long>& surface_set (std::set<unsigned long long> temp) "$1 = &temp;"

%typemap(argout) std::set<unsigned long long>& surface_set {
  %append_output(SWIG_NewPointerObj(new std::set<unsigned long long>( *$1 ), SWIGTYPE_p_std__setT_unsigned_long_long_std__lessT_unsigned_long_long_t_std__allocatorT_unsigned_long_long_t_t, SWIG_POINTER_OWN |  0 ));
}

%typemap(in,numinputs=0) std::set<unsigned long long>& material_ids (std::set<unsigned long long> temp) "$1 = &temp;"

%typemap(argout) std::set<unsigned long long>& material_ids {
  %append_output(SWIG_NewPointerObj(new std::set<unsigned long long>( *$1 ), SWIGTYPE_p_std__setT_unsigned_long_long_std__lessT_unsigned_long_long_t_std__allocatorT_unsigned_long_long_t_t, SWIG_POINTER_OWN |  0 ));
}

// Typemaps for cell id mat id maps that convert the inout map to an output map
%typemap(in,numinputs=0) std::map<unsigned long long, unsigned long long>& cell_id_mat_id_map (std::map<unsigned long long, unsigned long long> temp) "$1 = &temp;"

%typemap(argout) std::map<unsigned long long, unsigned long long>& cell_id_mat_id_map {
  %append_output(SWIG_NewPointerObj((new std::map< unsigned long long,unsigned long long,std::less< unsigned long long >,std::allocator< std::pair< unsigned long long const,unsigned long long > > >(static_cast< const std::map< unsigned long long,unsigned long long,std::less< unsigned long long >,std::allocator< std::pair< unsigned long long const,unsigned long long > > >& >( *$1 ))), SWIGTYPE_p_std__mapT_unsigned_long_long_unsigned_long_long_std__lessT_unsigned_long_long_t_std__allocatorT_std__pairT_unsigned_long_long_const_unsigned_long_long_t_t_t, SWIG_POINTER_OWN |  0 ));
}

// Typemaps for cell id density maps that convert the inout map to an output
// map
%typemap(in,numinputs=0) std::map<unsigned long long, double>& cell_id_density_map (std::map<unsigned long long, double> temp) "$1 = &temp;"

%typemap(argout) std::map<unsigned long long, double>& cell_id_density_map {
  %append_output(SWIG_NewPointerObj((new std::map< unsigned long long,double,std::less< unsigned long long >,std::allocator< std::pair< unsigned long long const,double > > >(static_cast< const std::map< unsigned long long,double,std::less< unsigned long long >,std::allocator< std::pair< unsigned long long const,double > > >& >( *$1 ))), SWIGTYPE_p_std__mapT_unsigned_long_long_double_std__lessT_unsigned_long_long_t_std__allocatorT_std__pairT_unsigned_long_long_const_double_t_t_t, SWIG_POINTER_OWN |  0 ));
}

// Typemaps for a estimator data map that converst the inout map to an
// output map
%typemap(in,numinputs=0) std::map<unsigned int, Utility::Trip<std::string,std::string,std::vector<unsigned long long> > >& estimator_id_data_map (std::map<unsigned int, Utility::Trip<std::string,std::string,std::vector<unsigned long long> > > temp) "$1 = &temp;"

%typemap(argout) std::map<unsigned int, Utility::Trip<std::string,std::string,std::vector<unsigned long long> > >& estimator_id_data_map {
  %append_output(SWIG_NewPointerObj((new std::map< unsigned int,Utility::Trip< std::string,std::string,std::vector< unsigned long long,std::allocator< unsigned long long > > >,std::less< unsigned int >,std::allocator< std::pair< unsigned int const,Utility::Trip< std::string,std::string,std::vector< unsigned long long,std::allocator< unsigned long long > > > > > >(static_cast< const std::map< unsigned int,Utility::Trip< std::string,std::string,std::vector< unsigned long long,std::allocator< unsigned long long > > >,std::less< unsigned int >,std::allocator< std::pair< unsigned int const,Utility::Trip< std::string,std::string,std::vector< unsigned long long,std::allocator< unsigned long long > > > > > >& >( *$1 ))), SWIGTYPE_p_std__mapT_unsigned_int_Utility__TripT_std__string_std__string_std__vectorT_unsigned_long_long_std__allocatorT_unsigned_long_long_t_t_t_std__lessT_unsigned_int_t_std__allocatorT_std__pairT_unsigned_int_const_Utility__TripT_std__string_std__string_std__vectorT_unsigned_long_long_std__allocatorT_unsigned_long_long_t_t_t_t_t_t, SWIG_POINTER_OWN |  0 ));
}

// Add a general typemap that will convert the inout surface_hit parameter to
// a return from the python wrapper method
%apply Geometry::ModuleTraits::InternalSurfaceHandle& OUTPUT { Geometry::ModuleTraits::InternalSurfaceHandle& surface_hit }

// Add typemaps for the advanceInternalRayToCellBoundary method
%typemap(in,numinputs=0) double* surface_normal (double temp[3]) "$1 = &temp[0];"

%typemap(argout) double* surface_normal {
  Teuchos::ArrayView<const double> normal_view( $1, 3 );
  %append_output(PyFrensie::copyTeuchosToNumPy( normal_view ));
}

// Add typemaps for the getSurfaceNormal method
%typemap(in,numinputs=0) double normal[3] (double temp[3]) "$1 = &temp[0];"

%typemap(argout) double normal[3] {
  Teuchos::ArrayView<const double> normal_view( $1, 3 );
  %append_output(PyFrensie::copyTeuchosToNumPy( normal_view ));
}

// Include the DagMC class
%include "Geometry_DagMC.hpp"

// Instantiate an IdSet
%template(IdSet) std::set<unsigned long long>;

// Instantiate the template getMaterialIds method
%template(getMaterialIds) Geometry::DagMC::getMaterialIds<std::set<unsigned long long> >;

// Instantiate the template getCells method
%template(getCells) Geometry::DagMC::getCells<std::set<unsigned long long> >;

// Instantiate the template getSurfaces method
%template(getSurfaces) Geometry::DagMC::getSurfaces<std::set<unsigned long long> >;

// Instantiate the template getFoundCellCache method
%template(getFoundCellCache) Geometry::DagMC::getFoundCellCache<std::set<unsigned long long> >;

// Instantiate a cell id to mat id map
%template(CellIdMatIdMap) std::map<unsigned long long, unsigned long long>;

// Instantiate the template getCellMaterialIds method
%template(getCellMaterialIds) Geometry::DagMC::getCellMaterialIds<std::map<unsigned long long, unsigned long long> >;

// Instantiate a cell id to density map
%template(CellIdDensityMap) std::map<unsigned long long, double>;

// Instantiate the template getCellDensities method
%template(getCellDensities) Geometry::DagMC::getCellDensities<std::map<unsigned long long, double> >;

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
