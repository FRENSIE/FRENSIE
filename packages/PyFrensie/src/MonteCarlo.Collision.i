//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo.Collision.i
//! \author Alex Robinson, Luke Kersting
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
/*// FRENSIE Includes*/
#include "MonteCarlo_PhotonKinematicsHelpers.hpp"
#include "MonteCarlo_AdjointPhotonKinematicsHelpers.hpp"
#include "Utility_ContractException.hpp"
%}

// C++ STL support
%include <stl.i>
%include <std_string.i>
%include <std_except.i>
%include <std_shared_ptr.i>

// Include typemaps support
%include <typemaps.i>

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
MonteCarlo::calculateAdjointComptonLineEnergy
"
The initial energy must have units of MeV. The output adjoint Compton-line
energy will also have units of MeV.
"

%feature("docstring")
MonteCarlo::calculateScatteringAngleCosineAdjoint
"
The initial and final energies must have units of MeV. If the final energy
is not energetically possible and Design-by-Contract is turned on an 
exception will be thrown. It it best to verify that the final energy is
energetically possible before using this function.
"

%feature("docstring")
MonteCarlo::calculateMinScatteringAngleCosine
"
The initial energy and maximum energy must have units of MeV. The minimum
scattering angle cosine calculated only applies to the kinematics of
adjoint photons.
"

%feature("docstring")
MonteCarlo::calculateAbsoluteMinScatteringAngleCosine
"
The initial energy must have units of MeV. The absolute minimum scattering
angle cosine is the limit of the minimum scattering angle cosine as the
maximum energy goes to infinity.
"

%feature("docstring")
MonteCarlo::calculateMinInverseEnergyGainRatio
"
The initial energy and maximum energy must have units of MeV. The minimum 
inverse energy gain ratio is commonly used to sample from the adjoint
Klein-Nishina cross section.
"

%feature("docstring")
MonteCarlo::calculateAbsoluteMinInverseEnergyGainRatio
"
The initial energy must have units of MeV. The absolute minimum inverse
energy gain ratio is the limit of the minimum inverse energy gain ratio as
the maximum energy goes to infinity.
"

%feature("docstring")
MonteCarlo::calculateElectronMomentumProjection
"
The initial and final energies must have units of MeV. The calculated
electron momentum projection will be in me*c units.
"

%feature("docstring")
MonteCarlo::calculateElectronMomentumProjectionAdjoint
"
The initial and final energies must have units of MeV. The calculated
adjoint electron momentum projection will be in me*c units.
"

%feature("docstring")
MonteCarlo::calculateMaxElectronMomentumProjection
"
The initial and binding energies must have units of MeV. The calculated 
electron momentum projection will be in me*c units. 
"

%feature("docstring")
MonteCarlo::calculateMaxElectronMomentumProjectionAdjoint
"
The initial and binding energies must have units of MeV. The calculated
electron momentum projection will be in me*c units.
"

%feature("docstring")
MonteCarlo::calculateMinElectronMomentumProjectionAdjoint
"
The initial and maximum energies must have units of MeV. The calculated
electron momentum projection will be in me*c units.
"

%feature("docstring")
MonteCarlo::calculateAbsoluteMinElectronMomentumProjectionAdjoint
"
The initial energy must have units of MeV. The absolute minimum adjoint
electron momentum projection is the limit of the minimum adjoint electron
momentum projection as the maximum energy goes to infinity.
"

%feature("autodoc",
"calculateDopplerBroadenedEnergyAdjoint(const double electron_momentum_projection, const double initial_energy, const double scattering_angle_cosine) -> double,bool

The electron momentum projection must have units of me*c. The initial energy 
must have units of MeV. The calculated energy will have units of MeV. If 
there is an energetically possible outgoing energy a value of true will also be
returned. If false is returned the returned energy should be ignored.")
MonteCarlo::calculateDopplerBroadenedEnergyAdjont;

%feature("autodoc",
"calculateDopplerBroadenedEnergy(const double electron_momentum_projection, const double initial_energy, const double scattering_angle_cosine) -> double,bool

The electron momentum projection must have units of me*c. The initial energy 
must have units of MeV. The calculated energy will have units of MeV. If 
there is an energetically possible outgoing energy a value of true will also be
returned. If false is returned the returned energy should be ignored.")
MonteCarlo::calculateDopplerBroadenedEnergy;

// Add a general typemap
%apply bool& OUTPUT { bool& energetically_possible };

// Include the PhotonKinematicHelpers and AdjointPhotonKinematicsHelpers
%include "MonteCarlo_PhotonKinematicsHelpers.hpp"
%include "MonteCarlo_AdjointPhotonKinematicsHelpers.hpp"

//---------------------------------------------------------------------------//
// Add Atomic Excitation Distribution support
//---------------------------------------------------------------------------//
%include "MonteCarlo_ElectronScatteringDistribution.i"

//---------------------------------------------------------------------------//
// Turn off the exception handling
//---------------------------------------------------------------------------//
%exception;

//---------------------------------------------------------------------------//
// end MonteCarlo.Collision.i
//---------------------------------------------------------------------------//
