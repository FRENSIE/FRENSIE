//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CollisionForcer.i
//! \author Alex Robinson
//! \brief  The collision forcer class's interface file
//!
//---------------------------------------------------------------------------//

%{
// FRENSIE Includes
#include "PyFrensie_PythonTypeTraits.hpp"

#include "MonteCarlo_FilledGeometryModel.hpp"
#include "MonteCarlo_CollisionForcer.hpp"
#include "MonteCarlo_StandardCollisionForcer.hpp"

using namespace MonteCarlo;
%}

// C++ STL support
%include <stl.i>
%include <std_string.i>
%include <std_shared_ptr.i>
%include <std_set.i>
%include <std_vector.i>

// Include typemaps support
%include <typemaps.i>

// Include the ArrayView support
%include "PyFrensie_Array.i"

// Add some general templates
%template(LongUnsignedVector) std::vector<long unsigned int>;

// Add typemaps for converting Python int to ParticleType
%typemap(in) const MonteCarlo::ParticleType particle_type {
  $1 = MonteCarlo::convertIntToParticleType( PyInt_AsLong($input) );
}

%typemap(typecheck, precedence=70) (const MonteCarlo::ParticleType) {
  $1 = (PyInt_Check($input)) ? 1 : 0;
}

// Filled geometry model handling
%import (module="Collision") MonteCarlo.GeometryModel.i

//---------------------------------------------------------------------------//
// Add Collision Forcer support
//---------------------------------------------------------------------------//

// Extend the collision forcer class
%extend MonteCarlo::CollisionForcer
{
  // Get the particle types that can contribute to the estimator
  PyObject* getParticleTypes()
  {
    const std::set<ParticleTypes>& particle_types = $self->getParticleTypes();

    std::set<int> raw_particle_types( particle_types.begin(),
                                      particle_types.end() );

    return PyFrensie::convertToPython( raw_particle_types );
  }
};

%ignore *::getParticleTypes;
%ignore *::forceCollision;

// Add a typemap for std::set<MonteCarlo::CollisionForcer::CellIdType>& cells_set
%typemap(in,numinputs=0) std::set<MonteCarlo::CollisionForcer::CellIdType>& cells_set (std::set<MonteCarlo::CollisionForcer::CellIdType> temp) "$1 = &temp;"

%typemap(argout) std::set<MonteCarlo::CollisionForcer::CellIdType>& cells_set {
  %append_output(PyFrensie::convertToPython( *$1 ));
}

// Apply vector input typemaps
%apply std::vector<long unsigned int>& INPUT { const std::vector<MonteCarlo::CollisionForcer::CellIdType>& cells }

// Apply set input typemaps
%apply std::set<long unsigned int>& INPUT { const std::set<MonteCarlo::CollisionForcer::CellIdType>& cells }

%shared_ptr( MonteCarlo::CollisionForcer )
%include "MonteCarlo_CollisionForcer.hpp"

//---------------------------------------------------------------------------//
// Add Standard Collision Forcer support
//---------------------------------------------------------------------------//

%shared_ptr( MonteCarlo::StandardCollisionForcer )
%include "MonteCarlo_StandardCollisionForcer.hpp"

//---------------------------------------------------------------------------//
// end MonteCarlo_CollisionForcer.i
//---------------------------------------------------------------------------//
