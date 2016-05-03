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

// Ignore the methods that receive or return pointers - new ones will be
// created that receive or return Python objects
%ignore Geometry::Root::getPointLocation( const double[3], const Geometry::ModuleTraits::InternalCellHandle );
%ignore Geometry::Root::setInternalRay( const double[3], const double[3] );
%ignore Geometry::Root::changeInternalRayDirection( const double[3] );

// Add some useful methods to the Root class
%extend Geometry::Root
{
  // Get the point location
  static PointLocation getPointLocation(
                               PyObject* py_array_position,
                               const ModuleTraits::InternalCellHandle cell_id )
  {
    Teuchos::Array<double> position;

    %convert_python_position_to_teuchos( py_array_position, position );

    return Geometry::Root::getPointLocation( position.getRawPtr(), cell_id );
  }

  // Set the internal ray
  static void setInternalRay( PyObject* py_array_position,
                              PyObject* py_array_direction )
  {
    Teuchos::Array<double> position;

    %convert_python_position_to_teuchos( py_array_position, position );

    Teuchos::Array<double> direction;

    %convert_python_direction_to_teuchos( py_array_direction, direction );

    Geometry::Root::setInternalRay( position.getRawPtr(),
                                    direction.getRawPtr() );
  }

  // Get the internal Root ray position
  static PyObject* getInternalRayPosition()
  {
    Teuchos::ArrayView<const double> position(
                                Geometry::Root::getInternalRayPosition(), 3 );

    return PyFrensie::copyTeuchosToNumPy( position );
  }

  // Get the internal DagMC ray direction
  static PyObject* getInternalRayDirection()
  {
    Teuchos::ArrayView<const double> direction(
                               Geometry::Root::getInternalRayDirection(), 3 );

    return PyFrensie::copyTeuchosToNumPy( direction );
  }
};

// Include the Root class
%include "Geometry_Root.hpp"

// Include the geometry helpers
%include "Geometry_Helpers.i"

%standard_geom_template_extends( Root );

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
