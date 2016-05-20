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

%module(package   = "MonteCarlo.Collision",
        autodoc   = "1",
        docstring = %monte_carlo_collision_docstring) Collision

%{

%}

//---------------------------------------------------------------------------//
// end MonteCarlo.Collision.i
//---------------------------------------------------------------------------//
