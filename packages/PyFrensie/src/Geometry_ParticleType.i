//---------------------------------------------------------------------------//
//!
//! \file   Geometry_ParticleType.i
//! \author Luke Kersting
//! \brief  The ParticleType classes interface file
//!
//---------------------------------------------------------------------------//

%{
// FRENSIE Includes
#include "Geometry_ParticleType.hpp"
#include "Utility_ToStringTraitsDecl.hpp"

// Add the Geometry namespace to the global lookup scope
using namespace Geometry;
%}

// C++ STL support
%include <stl.i>

// Include typemaps support
%include <typemaps.i>

// Import the ToStringTraitsDecl
%import "Utility_ToStringTraitsDecl.hpp"

//---------------------------------------------------------------------------//
// Add support for the ParticleType
//---------------------------------------------------------------------------//

// Import the ParticleType
%include "Geometry_ParticleType.hpp"

//---------------------------------------------------------------------------//
// end Geometry_ParticleType.i
//---------------------------------------------------------------------------//e
