//---------------------------------------------------------------------------//
//!
//! \file   Geometry.Root.i
//! \author Alex Robinson
//! \brief  The Geometry.Root.i sub-module
//!
//---------------------------------------------------------------------------//

%define %geometry_root_docstring
"
PyFrensie.Geometry.Root is the python interface to the FRENSIE geometry/root
subpackage.

The purpose of Root is to allow a user to query ROOT geometry data and to
ray trace on a ROOT geometry using python. This can be useful for debugging
geometries.
"
%enddef

%module(package   = "PyFrensie.Geometry",
        autodoc   = "1",
        docstring = %geometry_root_docstring) ROOT

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
#include "Geometry_Root.hpp"
#include "Geometry_RootInstanceFactory.hpp"
#include "Utility_ContractException.hpp"
%}

// C++ STL support
%include <stl.i>
%include <std_string.i>
%include <std_set.i>
%include <std_map.i>
%include <std_except.i>

// Include typemaps support
%include <typemaps.i>

// Import the PyFrensie Teuchos Array conversion helpers
%import "PyFrensie_ArrayConversionHelpers.hpp"

// Import the ModuleTraits classes
%import "MonteCarlo_ModuleTraits.hpp"
%import "Geometry_ModuleTraits.hpp"

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
  catch( Geometry::InvalidRootGeometry& e )
  {
    SWIG_exception( SWIG_RuntimeError, e.what() );
  }
  catch( ... )
  {
    SWIG_exception( SWIG_UnknownError, "Unknown C++ exception" );
  }
}

//---------------------------------------------------------------------------//
// Add support for the Root class
//---------------------------------------------------------------------------//
// Add more detailed docstrings for the Root class
%feature("docstring")
Geometry::Root
"
The Root class can be used to interact with a ROOT file that has been
set up for use with FRENSIE. The query methods have been grouped into
several groups based on the level of information that is sought. Some of
these query methods can be called before the geometry has been loaded:

ROOT File Properties:
  *getMaterialPropertyName
  *setMaterialPropertyName
  *getVoidMaterialName
  *setVoidMaterialName
  *getTerminalMaterialName
  *setTerminalMaterialName
  *isInitialized

Others must only be called after the geometry has been loaded:

Geometry Properties:
  *doesCellExist
  *isTerminationCell
  *isVoidCell
  *getCells

Geometric Entity Properties:
  *getCellVolume
  *getCellMaterialNames
  *getCellMaterialIds
  *getCellDensities

The initialize method is used to load the ROOT file and parse its properties
and geometric information. It is recommended that one use
PyFrensie.Geometry.ROOT.initializeRoot to load the geometry instead of
calling the initialize method directly. Once the geometry has been loaded one
may ray trace on the geometry. This can be useful for debugging ray trace
errors encountered while running Monte Carlo particle simulations. A brief
usage tutorial for this class is shown below:

  import PyFrensie.Geometry.ROOT as ROOT

  geom = ROOT.Root

  geom.initialize( 'my_root_file.root', 1e-3 )

  ray = PyFrensie.Geometry.Ray( 0, 0, 0, 0, 0, 1 )

  cell = geom.findCellContainingExternalRay( ray )
  distance_to_surface = geom.fireExternalRay( ray )

  ray.advanceHead( distance_to_surface )

  geom.setInternalRay( ray )

  cell = geom.findCellContainingInternalRay()

  distance_to_surface = geom.fireInternalRay()

  geom.advanceInternalRayToCellBoundary()

  cell = geom.findCellContainingInternalRay()
"

%feature("docstring")
Geometry::Root::getMaterialIds
"
This method will return an IdSet that contains the material ids.
"

%feature("docstring")
Geometry::Root::getCells
"
This method will return an IdSet that contains the cells of interest.
"

%feature("docstring")
Geometry::Root::getCellMaterialNames
"
This method will return a CellIdMatNameMap that contains the cells and their
assigned material names.
"

%feature("docstring")
Geometry::Root::getCellMaterialIds
"
This method will return a CellIdMatIdMap that contains the cells and their
assigned material ids.
"

%feature("docstring")
Geometry::Root::getCellDensities
"
This method will return a CellIdDensityMap that contains the cells and their
assigned densities.
"

// Typemaps for id sets that convert the inout set to an output set
%typemap(in,numinputs=0) std::set<unsigned long long>& cell_set (std::set<unsigned long long> temp) "$1 = &temp;"

%typemap(argout) std::set<unsigned long long>& cell_set {
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

// Typemaps for cell id material name maps that convert the inout map to an
// output map
%typemap(in,numinputs=0) std::map<unsigned long long, std::string>& cell_id_mat_name_map (std::map<unsigned long long, std::string> temp) "$1 = &temp;"

%typemap(argout) std::map<unsigned long long, std::string>& cell_id_mat_name_map {
  %append_output(SWIG_NewPointerObj((new std::map< unsigned long long,std::string,std::less< unsigned long long >,std::allocator< std::pair< unsigned long long const,std::string > > >(static_cast< const std::map< unsigned long long,std::string,std::less< unsigned long long >,std::allocator< std::pair< unsigned long long const,std::string > > >& >( *$1 ))), SWIGTYPE_p_std__mapT_unsigned_long_long_std__string_std__lessT_unsigned_long_long_t_std__allocatorT_std__pairT_unsigned_long_long_const_std__string_t_t_t, SWIG_POINTER_OWN |  0 ));
}

// Include the Root class
%include "Geometry_Root.hpp"

// Instantiate an IdSet
%template(IdSet) std::set<unsigned long long>;

// Instantiate the template getMaterialIds method
%template(getMaterialIds) Geometry::Root::getMaterialIds<std::set<unsigned long long> >;

// Instantiate the template getCells method
%template(getCells) Geometry::Root::getCells<std::set<unsigned long long> >;

// Instantiate a cell id to mat name map
%template(CellIdMatNameMap) std::map<unsigned long long, std::string>;

// Instantiate the template getCellMaterialNames method
%template(getCellMaterialNames) Geometry::Root::getCellMaterialNames<std::map<unsigned long long, std::string> >;

// Instantiate a cell id to mat id map
%template(CellIdMatIdMap) std::map<unsigned long long, unsigned long long>;

// Instantiate the template getCellMaterialIds method
%template(getCellMaterialIds) Geometry::Root::getCellMaterialIds<std::map<unsigned long long, unsigned long long> >;

// Instantiate a cell id to density map
%template(CellIdDensityMap) std::map<unsigned long long, double>;

// Instantiate the template getCellDensities method
%template(getCellDensities) Geometry::Root::getCellDensities<std::map<unsigned long long, double> >;

//---------------------------------------------------------------------------//
// Add support for the RootInstanceFactory class
//---------------------------------------------------------------------------//
// Add more detailed docstrings for the RootInstanceFactory class
%feature("docstring")
initializeRoot
"
This is the recommended way to initialize a ROOT geometry. The
PyTrilinos.Teuchos.ParameterList object should store all of the ROOT file
properties and the ROOT initialization options. A brief usage tutorial for
this class is shown below:

  import PyFrensie.Geometry.Root, PyTrilinos.Teuchos, numpy

  source = PyTrilinos.Teuchos.FileInputSource( 'my_geom_file.xml' )
  xml_obj = source.getObject()
  geom_init_list = PyTrilinos.Teuchos.XMLParameterListReader().toParameterList( xml_obj )

  PyFrensie.Geometry.ROOT.initializeRoot( geom_init_list )

  geom = PyFrensie.Geometry.ROOT.Root
  geom.isInitialize()
"

// Import the Teuchos_ParameterList interface
%import <Teuchos.i>

// Import the DagMCInstanceFactory class
%import "Geometry_RootInstanceFactory.hpp"

%inline %{
void initializeRoot( const Teuchos::ParameterList& geom_rep )
{
  Geometry::RootInstanceFactory::initializeRoot( geom_rep );
}
%}

// Turn off the exception handling
%exception;

//---------------------------------------------------------------------------//
// end Geometry.Root.i
//---------------------------------------------------------------------------//
