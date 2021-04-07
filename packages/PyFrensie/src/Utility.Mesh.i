//---------------------------------------------------------------------------//
//!
//! \file   Utility.Mesh.i
//! \author Luke Kersting
//! \brief  The Utility.Mesh sub-module swig interface file
//!
//---------------------------------------------------------------------------//

%define %utility_mesh_docstring
"
PyFrensie.Utility.Mesh is the python interface to the FRENSIE utility/mesh
subpackage.

The purpose of the Mesh package is to provide a variety of spatial mesh
conversion policies that can be used in FRENSIE and PyFrensie.
"
%enddef

%module(package   = "PyFrensie.Utility",
        autodoc   = "1",
        docstring = %utility_mesh_docstring) Mesh

%{
// FRENSIE Includes
#include "PyFrensie_PythonTypeTraits.hpp"
#include "Utility_SerializationHelpers.hpp"

#include "Utility_Mesh.hpp"
#include "Utility_StructuredHexMesh.hpp"
#include "Utility_TetMesh.hpp"

// Add the Utility namespace to the global lookup scope
using namespace Utility;
%}

// Standard exception handling
%include "exception.i"

// Global swig features
%feature("autodoc", "1");

// C++ STL support
%include <stl.i>
%include <std_vector.i>
%include <std_map.i>
%include <std_unordered_map.i>
%include <std_string.i>
%include <std_shared_ptr.i>
%include <std_except.i>

// Include typemaps support
%include <typemaps.i>

// Include the serialization helpers for handling macros
%include "Utility_SerializationHelpers.hpp"

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

// Add a few general typedefs
typedef unsigned long int uint64_t;

// Add typemaps for converting double[3] to and from Python array
%typemap(in) const double[3] (std::array<double,3ul> temp){
  temp = PyFrensie::convertFromPython<std::array<double,3ul> >( $input );

  $1 = temp.data();
}

// Add typecheck out for the Ray class
%typemap(typecheck, precedence=1050) (const double[3]) {
  $1 = (PyArray_Check($input) || PySequence_Check($input)) ? 1 : 0;
}

// ---------------------------------------------------------------------------//
// Add Mesh support
// ---------------------------------------------------------------------------//

// Ignore functions that return iterators
%ignore *::getStartElementHandleIterator();
%ignore *::getEndElementHandleIterator();
%ignore *::exportData();



// Add a typemap for ElementHandleVolumeMap& element_volumes
%typemap(in,numinputs=0) Utility::Mesh::ElementHandleVolumeMap& element_volumes (Utility::Mesh::ElementHandleVolumeMap temp) "$1 = &temp;"

%typemap(argout) Utility::Mesh::ElementHandleVolumeMap& element_volumes {
  %append_output(PyFrensie::convertToPython( *$1 ));
}

// Add a typemap for ElementHandleTrackLengthArray&
%typemap(in,numinputs=0) Utility::Mesh::ElementHandleTrackLengthArray& (Utility::Mesh::ElementHandleTrackLengthArray temp) "$1 = &temp;"

%typemap(argout) Utility::Mesh::ElementHandleTrackLengthArray& {
  %append_output(PyFrensie::convertToPython( *$1 ));
}

// Add a typemap for ElementHandleVolumeMap& element_volumes
%typemap(in,numinputs=0) std::vector<Utility::Mesh::ElementHandle>& element_handles (std::vector<Utility::Mesh::ElementHandle> temp) "$1 = &temp;"

%typemap(argout) std::vector<Utility::Mesh::ElementHandle>& element_handles {
  %append_output(PyFrensie::convertToPython( *$1 ));
}

// Extend Mesh classes to return the mesh element list as a vector
%extend Utility::Mesh
{
  // Return the mesh element list
  void getElementHandles( std::vector<Utility::Mesh::ElementHandle>& element_handles ) const
  {
    std::vector<Utility::Mesh::ElementHandle>::const_iterator begin = $self->getStartElementHandleIterator();
    std::vector<Utility::Mesh::ElementHandle>::const_iterator end = $self->getEndElementHandleIterator();

    element_handles.insert( element_handles.begin(), begin, end );
  }
};

%shared_ptr(Utility::Mesh)
%include "Utility_Mesh.hpp"

// Add a few general templates
%template(DoubleVector) std::vector<double>;
%template(ElementHandleVector) std::vector<Utility::Mesh::ElementHandle>;
// %template(ElementHandleVolumeMapORDERED) std::map<Utility::Mesh::ElementHandle,double>;
// %template(ElementHandleVolumeMap) std::unordered_map<Utility::Mesh::ElementHandle,double>;

// ---------------------------------------------------------------------------//
// Add StructuredHexMesh support
// ---------------------------------------------------------------------------//

// Extend Mesh classes to return the mesh element list as a vector
%extend Utility::StructuredHexMesh
{
  // Return the mesh element list
  void getElementHandles( std::vector<Utility::Mesh::ElementHandle>& element_handles ) const
  {
    std::vector<Utility::Mesh::ElementHandle>::const_iterator begin = $self->getStartElementHandleIterator();
    std::vector<Utility::Mesh::ElementHandle>::const_iterator end = $self->getEndElementHandleIterator();

    element_handles.insert( element_handles.begin(), begin, end );
  }
};

%shared_ptr(Utility::StructuredHexMesh)
%include "Utility_StructuredHexMesh.hpp"

// ---------------------------------------------------------------------------//
// Add TetMesh support
// ---------------------------------------------------------------------------//

// Extend Mesh classes to return the mesh element list as a vector
%extend Utility::TetMesh
{
  // Return the mesh element list
  void getElementHandles( std::vector<Utility::Mesh::ElementHandle>& element_handles ) const
  {
    std::vector<Utility::Mesh::ElementHandle>::const_iterator begin = $self->getStartElementHandleIterator();
    std::vector<Utility::Mesh::ElementHandle>::const_iterator end = $self->getEndElementHandleIterator();

    element_handles.insert( element_handles.begin(), begin, end );
  }
};

%shared_ptr(Utility::TetMesh)
%include "Utility_TetMesh.hpp"

//---------------------------------------------------------------------------//
// Turn off the exception handling
//---------------------------------------------------------------------------//
%exception;

//---------------------------------------------------------------------------//
// end Utility.Mesh.i
//---------------------------------------------------------------------------//e
