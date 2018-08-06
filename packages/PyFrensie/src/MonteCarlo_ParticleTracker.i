//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleTracker.i
//! \author Luke Kersting
//! \brief  The ParticleTracker class interface file
//!
//---------------------------------------------------------------------------//

%{
// FRENSIE Includes
#include "MonteCarlo_ParticleTracker.hpp"


using namespace MonteCarlo;
%}

// C++ STL support
%include <stl.i>
// %include <std_string.i>
// %include <std_shared_ptr.i>
// %include <std_set.i>
// %include <std_map.i>
// %include <std_vector.i>
%include <std_except.i>

// Include typemaps support
%include <typemaps.i>

// // Import the Geometry.Geometry__init__.i file
// %import "Geometry.Geometry__init__.i"

// // Mesh handling
// %import "Utility.Mesh.i"

// // Include the ArrayView support
// %include "PyFrensie_Array.i"

// // Import the PyFrensie_ArraySharedPtr.i
// %include "PyFrensie_ArraySharedPtr.i"

// // Add a few general typedefs
// typedef unsigned int uint32_t;

// // Add some general templates
// %template(LongUnsignedVector) std::vector<long unsigned int>;
// %template(IntVector) std::vector<int>;
// %template(StringVectorMap) std::map<std::string,std::vector<double> >;

// // Add some general typemaps
// %apply long unsigned int { const Geometry::Model::EntityId };


// ---------------------------------------------------------------------------//
// Add ParticleTracker support
// ---------------------------------------------------------------------------//

%include "MonteCarlo_ParticleTracker.hpp"

// // ---------------------------------------------------------------------------//
// // Add ParticleHistoryObserver support
// // ---------------------------------------------------------------------------//

// // Add typemaps for converting unsigned long long to and from Python string
// %typemap(in) const unsigned long long num_histories ( unsigned long long temp ){
//   temp = PyInt_AsUnsignedLongLongMask( $input );
//   $1 = temp;
// }

// %typemap(typecheck, precedence=70) (const unsigned long long) {
//   $1 = (PyInt_Check($input)) ? 1 : 0;
// }

// %shared_ptr( MonteCarlo::ParticleHistoryObserver )
// %include "MonteCarlo_ParticleHistoryObserver.hpp"

// // ---------------------------------------------------------------------------//
// // Add ParticleTracker support
// // ---------------------------------------------------------------------------//

// // Extend the ParticleTracker class to handle ParticleType enum as int
// %extend MonteCarlo::ParticleTracker
// {
//   // Set the particle types that can contribute to the ParticleTracker
//   void setParticleTypes( const std::vector<int>& particle_types_int )
//   {
//     std::vector<MonteCarlo::ParticleType> particle_types;

//     particle_types.resize(particle_types_int.size());
//     for( unsigned i = 0; i < particle_types_int.size(); ++i )
//     {
//       particle_types[i] = (MonteCarlo::ParticleType)particle_types_int[i];
//     }

//     $self->setParticleTypes( particle_types );
//   }

//   // Set response functions
//   void setResponseFunctions( PyObject* raw_response_functions )
//   {
//     std::vector< std::shared_ptr< MonteCarlo::ParticleResponse const > > response_functions;

//     bool conversion_success;

//     CONVERT_PYOBJECT_TO_VECTOR_OF_BASE_SHARED_PTR( raw_response_functions, response_functions, SWIGTYPE_p_std__shared_ptrT_ParticleResponse_const_t, conversion_success );

//     if( conversion_success )
//     {
//       $self->setResponseFunctions( response_functions );
//     }
//     // SWIG will throw a runtime error
//     else
//       PyErr_SetString( PyExc_RuntimeError,
//                        "Could not convert Pyobject to a vector of ParticleResponse shared_ptrs." );
//   }

// };

// %template(ParticleResponseVector) std::vector< std::shared_ptr< ParticleResponse const >,std::allocator< std::shared_ptr< ParticleResponse const > > >;

// // Add a typemap for std::set<uint64_t>& entity_ids
// %typemap(in,numinputs=0) std::map<std::string,std::vector<double> >& processed_data (std::map<std::string,std::vector<double> > temp) "$1 = &temp;"

// %typemap(argout) std::map<std::string,std::vector<double> >& processed_data {
//   %append_output(swig::from( *$1 ));
// }

// // Add a typemap for std::set<uint64_t>& entity_ids
// %typemap(in,numinputs=0) std::set<uint64_t>& entity_ids (std::set<uint64_t> temp) "$1 = &temp;"

// %typemap(argout) std::set<uint64_t>& entity_ids {
//   %append_output(swig::from( *$1 ));
// }

// %shared_ptr( MonteCarlo::ParticleTracker )
// %include "MonteCarlo_ParticleTracker.hpp"

// // Add setDiscretization function templates
// %template(setEnergyDiscretization) MonteCarlo::ParticleTracker::setDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION, std::vector<double> >;
// %template(setTimeDiscretization) MonteCarlo::ParticleTracker::setDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION, std::vector<double> >;
// %template(setSourceEnergyDiscretization) MonteCarlo::ParticleTracker::setDiscretization<MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION, std::vector<double> >;
// %template(setSourceTimeDiscretization) MonteCarlo::ParticleTracker::setDiscretization<MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION, std::vector<double> >;
// %template(setCollisionNumberDiscretization) MonteCarlo::ParticleTracker::setDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION, std::vector<unsigned> >;
// %template(setCosineDiscretization) MonteCarlo::ParticleTracker::setDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION, std::vector<double> >;

// // ---------------------------------------------------------------------------//
// // Add SurfaceCurrentParticleTracker support
// // ---------------------------------------------------------------------------//

// // The weight multiplied surface current ParticleTracker
// %pre_template_setup_helper( SurfaceCurrentParticleTracker<MonteCarlo::WeightMultiplier>, WeightMultipliedSurfaceCurrentParticleTracker )

// // The weight and energy multiplied surface current ParticleTracker
// %pre_template_setup_helper( SurfaceCurrentParticleTracker<MonteCarlo::WeightAndEnergyMultiplier>, WeightAndEnergyMultipliedSurfaceCurrentParticleTracker )

// %shared_ptr( MonteCarlo::SurfaceCurrentParticleTracker )
// %include "MonteCarlo_SurfaceCurrentParticleTracker.hpp"

// // The weight multiplied surface current ParticleTracker
// %post_template_setup_helper( SurfaceCurrentParticleTracker<MonteCarlo::WeightMultiplier>, WeightMultipliedSurfaceCurrentParticleTracker )

// // The weight and energy multiplied surface current ParticleTracker
// %post_template_setup_helper( SurfaceCurrentParticleTracker<MonteCarlo::WeightAndEnergyMultiplier>, WeightAndEnergyMultipliedSurfaceCurrentParticleTracker )

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleTracker.i
//---------------------------------------------------------------------------//
