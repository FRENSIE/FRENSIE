//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo.Collision.i
//! \author Alex Robinson
//! \brief  The MonteCarlo.Collision sub-module swig interface file
//!
//---------------------------------------------------------------------------//

%define %monte_carlo_collision_docstring
"
PyFrensie.MonteCarlo.Collision is the python interface to the FRENSIE
monte_carlo/collision subpackage.
"
%enddef

%module(package   = "PyFrensie.MonteCarlo",
        autodoc   = "1",
        docstring = %monte_carlo_collision_docstring) Collision

%{
// FRENSIE Includes
#include "MonteCarlo_PhotonKinematicsHelpers.hpp"
#include "Utility_ContractException.hpp"
%}

// C++ STL support
%include <stl.i>
%include <std_string.i>
%include <std_except.i>

// Include typemaps support
%include <typemaps.i>

// Standard exception handling
%include <exception.i>

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

//---------------------------------------------------------------------------//
// Add support for the photon kinematic helpers
//---------------------------------------------------------------------------//
// Add more detailed docstrings for the helper methods
%feature("docstring")
MonteCarlo::calculateComptonLineEnergy
"
The initial energy must have units of MeV. The output Compton-line energy
will also have units of MeV.
"

%feature("docstring")
MonteCarlo::calculateElectronMomentumProjection
"
The initial and final energies must have units of MeV. The calculated
electron momentum projection will be in me*c units.
"

%feature("docstring")
MonteCarlo::calculateMaxElectronMomentumProjection
"
The initial and binding energies must have units of MeV. The calculated 
electron momentum projection will be in me*c units.
"

%feature("autodoc",
"calculateMaxElectronMomentumProjection(double const initial_energy, double const binding_energy, double const scattering_angle_cosine) -> double,bool


The initial and binding energies must have units of MeV. The calculated 
electron momentum projection will be in me*c units. If there is an
energetically possible outgoing energy a value of true will also be returned.
If false is returned the returned energy should be ignored.")
MonteCarlo::calculateDopplerBroadenedEnergy;

// Add a general typemap
%apply bool& OUTPUT { bool& energetically_possible };

// Include the PhotonKinematicHelpers
%include "MonteCarlo_PhotonKinematicsHelpers.hpp"

//---------------------------------------------------------------------------//
// Turn off the exception handling
//---------------------------------------------------------------------------//
%exception;

//---------------------------------------------------------------------------//
// end MonteCarlo.Collision.i
//---------------------------------------------------------------------------//
