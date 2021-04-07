//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleState.i
//! \author Luke Kersting
//! \brief  The ParticleState classes interface file
//!
//---------------------------------------------------------------------------//


%{
// FRENSIE Includes
#include "PyFrensie_PythonTypeTraits.hpp"
#include "Utility_SerializationHelpers.hpp"
#include "Utility_ToStringTraitsDecl.hpp"
#include "Geometry_Model.hpp"
#include "Geometry_InfiniteMediumModel.hpp"
#include "Geometry_AdvancedModel.hpp"

#include "MonteCarlo_ParticleType.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_MasslessParticleState.hpp"
#include "MonteCarlo_MassiveParticleState.hpp"
#include "MonteCarlo_ChargedParticleState.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_PositronState.hpp"
#include "MonteCarlo_AdjointPhotonState.hpp"
#include "MonteCarlo_AdjointElectronState.hpp"
#include "MonteCarlo_ParticleBank.hpp"

using namespace MonteCarlo;
%}

// C++ STL support
%include <stl.i>
%include <std_except.i>
%include <std_string.i>
%include <std_shared_ptr.i>
%include <typemaps.i>

// Import the ToStringTraitsDecl
%import "Utility_ToStringTraitsDecl.hpp"

// Include the serialization helpers for handling macros
%include "Utility_SerializationHelpers.hpp"

// ParticleType handling
%import(module="PyFrensie.Geometry") Geometry_ParticleType.i
%import(module="PyFrensie.Geometry") Geometry_Model.i

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

// Ignore tag structs
%ignore *::NeutronTag;
%ignore *::PhotonTag;
%ignore *::ElectronTag;
%ignore *::PositronTag;
%ignore *::AdjointPhotonTag;
%ignore *::AdjointElectronTag;

// Add a few general typedefs
typedef unsigned long int uint64_t;

// ---------------------------------------------------------------------------//
// Add ParticleType support
// ---------------------------------------------------------------------------//

%include "MonteCarlo_ParticleType.hpp"

// ---------------------------------------------------------------------------//
// Add ParticleState support
// ---------------------------------------------------------------------------//

// Add typemaps for converting ParticleState::sourceIdType to and from Python
%typemap(in) const MonteCarlo::ParticleState::sourceIdType id ( MonteCarlo::ParticleState::sourceIdType temp ){
  temp = PyFrensie::convertFromPython<ParticleState::sourceIdType>( $input );
  $1 = temp;
}

%typemap(out) MonteCarlo::ParticleState::sourceIdType {
  %append_output(PyFrensie::convertToPython( $1 ));
}

%typemap(typecheck, precedence=70) (const MonteCarlo::ParticleState::sourceIdType) {
  $1 = (PyInt_Check($input)) ? 1 : 0;
}

// Add typemaps for converting EntityId to and from Python int
%typemap(in) const Geometry::Model::EntityId cell ( Geometry::Model::EntityId temp ){
  temp = PyInt_AsUnsignedLongMask( $input );
  $1 = temp;
}

%typemap(out) Geometry::Model::EntityId {
  %append_output(PyFrensie::convertToPython( $1 ) );
}

%typemap(typecheck, precedence=70) (const Geometry::Model::EntityId) {
  $1 = (PyInt_Check($input)) ? 1 : 0;
}


// Add typemaps for converting position (double*) to a Python array
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

// Add typemaps for converting direction (double*) to a Python array
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

// Add typemap for converting a Python array to double*
%typemap(out) const double* {
  Utility::ArrayView<const double> output_view( $1, 3 );

  $result = PyFrensie::Details::convertArrayToPython( output_view );

  if( !$result )
    SWIG_fail;
}

// Add typecheck for double[3]
%typemap(typecheck, precedence=1050) (const double[3]) {
  $1 = (PyArray_Check($input) || PySequence_Check($input)) ? 1 : 0;
}

%shared_ptr(MonteCarlo::ParticleState)
%include "MonteCarlo_ParticleState.hpp"

// ---------------------------------------------------------------------------//
// Add MasslessParticleState support
// ---------------------------------------------------------------------------//

%shared_ptr(MonteCarlo::MasslessParticleState)
%include "MonteCarlo_MasslessParticleState.hpp"

// ---------------------------------------------------------------------------//
// Add MassiveParticleState support
// ---------------------------------------------------------------------------//

%shared_ptr(MonteCarlo::MassiveParticleState)
%include "MonteCarlo_MassiveParticleState.hpp"

// ---------------------------------------------------------------------------//
// Add ChargedParticleState support
// ---------------------------------------------------------------------------//

%shared_ptr(MonteCarlo::ChargedParticleState)
%include "MonteCarlo_ChargedParticleState.hpp"

// ---------------------------------------------------------------------------//
// Add NeutronState support
// ---------------------------------------------------------------------------//

%shared_ptr(MonteCarlo::NeutronState)
%include "MonteCarlo_NeutronState.hpp"

// ---------------------------------------------------------------------------//
// Add PhotonState support
// ---------------------------------------------------------------------------//

%shared_ptr(MonteCarlo::PhotonState)
%include "MonteCarlo_PhotonState.hpp"

// ---------------------------------------------------------------------------//
// Add ElectronState support
// ---------------------------------------------------------------------------//

%shared_ptr(MonteCarlo::ElectronState)
%include "MonteCarlo_ElectronState.hpp"

// ---------------------------------------------------------------------------//
// Add PositronState support
// ---------------------------------------------------------------------------//

%shared_ptr(MonteCarlo::PositronState)
%include "MonteCarlo_PositronState.hpp"

// ---------------------------------------------------------------------------//
// Add AdjointPhotonState support
// ---------------------------------------------------------------------------//

%shared_ptr(MonteCarlo::AdjointPhotonState)
%include "MonteCarlo_AdjointPhotonState.hpp"

// ---------------------------------------------------------------------------//
// Add AdjointElectronState support
// ---------------------------------------------------------------------------//

%shared_ptr(MonteCarlo::AdjointElectronState)
%include "MonteCarlo_AdjointElectronState.hpp"

// ---------------------------------------------------------------------------//
// Add ParticleBank support
// ---------------------------------------------------------------------------//

// Ignore ParticleBank function that require a std::function as an input
%ignore MonteCarlo::ParticleBank::isSorted;
%ignore MonteCarlo::ParticleBank::sort;
%ignore MonteCarlo::ParticleBank::merge;

// Extend Particle Bank class to allow pop to return a smart pointer
%extend MonteCarlo::ParticleBank
{
  std::shared_ptr<MonteCarlo::ParticleState> pop()
  {
    std::shared_ptr<MonteCarlo::ParticleState> particle;

    // Pop the top particle from the bank and store it in the smart pointer
    $self->pop(particle);

    return particle;
  }
};

// Ignore pop() function and instead use the one defined with %extend
%ignore MonteCarlo::ParticleBank::pop;

%include "MonteCarlo_ParticleBank.hpp"

//---------------------------------------------------------------------------//
// Turn off the exception handling
//---------------------------------------------------------------------------//
%exception;

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleState.i
//---------------------------------------------------------------------------//
