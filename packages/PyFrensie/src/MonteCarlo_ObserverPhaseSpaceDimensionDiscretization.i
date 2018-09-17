//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ObserverPhaseSpaceDimensionDiscretization.i
//! \author Luke Kersting
//! \brief  The ObserverPhaseSpaceDimensionDiscretization classes interface file
//!
//---------------------------------------------------------------------------//

%{
// Boost includes
#include <boost/any.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleType.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_MasslessParticleState.hpp"
#include "MonteCarlo_MassiveParticleState.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_PositronState.hpp"
#include "MonteCarlo_AdjointPhotonState.hpp"
#include "MonteCarlo_AdjointElectronState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_ObserverParticleStateWrapper.hpp"
#include "MonteCarlo_ObserverPhaseSpaceDimension.hpp"
#include "MonteCarlo_ObserverPhaseSpaceDimensionDiscretization.hpp"
#include "MonteCarlo_TypedObserverPhaseSpaceDimensionDiscretization.hpp"
#include "MonteCarlo_OrderedTypedObserverPhaseSpaceDimensionDiscretization.hpp"
#include "MonteCarlo_FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization.hpp"
#include "MonteCarlo_HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization.hpp"
#include "MonteCarlo_IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization.hpp"
#include "MonteCarlo_UnorderedTypedObserverPhaseSpaceDimensionDiscretization.hpp"
#include "MonteCarlo_DefaultTypedObserverPhaseSpaceDimensionDiscretization.hpp"

using namespace MonteCarlo;
%}

// C++ STL support
%include <std_string.i>
%include <std_shared_ptr.i>
%include <std_pair.i>
%include <std_set.i>
%include <std_vector.i>

// Include the MonteCarlo event helpers
%include "MonteCarlo_EventHelpers.i"

// Particle state handling
%import(module="PyFrensie.MonteCarlo") MonteCarlo_ParticleState.i

// Add some general templates
%template(DoubleVector) std::vector<double>;
%template(UnsignedVector) std::vector<unsigned>;
%template(UnsignedDoublePair) std::pair<long unsigned int,double>;
%template(UnsignedDoublePairVector) std::vector<std::pair<long unsigned int,double> >;
%template(UnsignedSet) std::set<unsigned>;
%template(UnsignedVectorSet) std::vector<std::set<unsigned> >;

// ---------------------------------------------------------------------------//
// Add ObserverPhaseSpaceDimension support
// ---------------------------------------------------------------------------//

%include "MonteCarlo_ObserverParticleStateWrapper.hpp"

// ---------------------------------------------------------------------------//
// Add ObserverPhaseSpaceDimension support
// ---------------------------------------------------------------------------//

%include "MonteCarlo_ObserverPhaseSpaceDimension.hpp"

// ---------------------------------------------------------------------------//
// Add ObserverPhaseSpaceDimensionDiscretization support
// ---------------------------------------------------------------------------//

%ignore *::print;

// Add typemaps for converting file_path to and from Python string
%typemap(in) const boost::any& any_value ( boost::any temp ){
  double value = PyFrensie::convertFromPython<double>( $input );
  temp = boost::any(value);
  $1 = &temp;
}

%typemap(typecheck, precedence=SWIG_TYPECHECK_FLOAT) (const boost::any& any_value) {
  $1 = (PyFloat_Check($input)) ? 1 : 0;
}

// Add a typemap for BinIndexArray& bin_indices
%typemap(in,numinputs=0) MonteCarlo::ObserverPhaseSpaceDimensionDiscretization::BinIndexArray& bin_indices (MonteCarlo::ObserverPhaseSpaceDimensionDiscretization::BinIndexArray temp) "$1 = &temp;"

%typemap(argout) MonteCarlo::ObserverPhaseSpaceDimensionDiscretization::BinIndexArray& bin_indices {
  %append_output(PyFrensie::convertToPython( *$1 ));
}

// Add a typemap for BinIndexWeightPairArray& bin_indices_and_weights
%typemap(in,numinputs=0) MonteCarlo::ObserverPhaseSpaceDimensionDiscretization::BinIndexWeightPairArray& bin_indices_and_weights (MonteCarlo::ObserverPhaseSpaceDimensionDiscretization::BinIndexWeightPairArray temp) "$1 = &temp;"

%typemap(argout) MonteCarlo::ObserverPhaseSpaceDimensionDiscretization::BinIndexWeightPairArray& bin_indices_and_weights {
  %append_output(swig::from( *$1 ));
}

// Rename the overloaded calculateBinIndicesOfValue function
%rename(calculateBinIndicesAndWeightsOfValue) MonteCarlo::ObserverPhaseSpaceDimensionDiscretization::calculateBinIndicesOfValue(
  const ObserverParticleStateWrapper& particle_state_wrapper,
  BinIndexWeightPairArray& bin_indices_and_weights ) const;

%shared_ptr( MonteCarlo::ObserverPhaseSpaceDimensionDiscretization )
%include "MonteCarlo_ObserverPhaseSpaceDimensionDiscretization.hpp"

// ---------------------------------------------------------------------------//
// Add TypedObserverPhaseSpaceDimensionDiscretization support
// ---------------------------------------------------------------------------//

%pre_all_dimesion_discretization_setup( TypedObserver )

// Extend functions using boost::any for the Source Id template type
%extend_boost_any_functions( SOURCE_ID, int )

// Extend functions using boost::any for the Source Id template type
%extend_boost_any_functions( COLLISION_NUMBER, int )

%include "MonteCarlo_TypedObserverPhaseSpaceDimensionDiscretization.hpp"

%post_all_dimesion_discretization_setup( TypedObserver)

// ---------------------------------------------------------------------------//
// Add OrderedTypedObserverPhaseSpaceDimensionDiscretization support
// ---------------------------------------------------------------------------//

%pre_all_dimesion_discretization_setup( OrderedTypedObserver)

%include "MonteCarlo_OrderedTypedObserverPhaseSpaceDimensionDiscretization.hpp"

%post_all_dimesion_discretization_setup( OrderedTypedObserver)

// ---------------------------------------------------------------------------//
// Add FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization support
// ---------------------------------------------------------------------------//

%pre_floating_point_setup( FloatingPointOrderedTypedObserver )

%include "MonteCarlo_FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization.hpp"

%post_floating_point_setup( FloatingPointOrderedTypedObserver )

// ---------------------------------------------------------------------------//
// Add HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization support
// ---------------------------------------------------------------------------//

%pre_hashed_floating_point_setup( HashedFloatingPointOrderedTypedObserver)

%include "MonteCarlo_HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization.hpp"

%post_hashed_floating_point_setup( HashedFloatingPointOrderedTypedObserver)

// ---------------------------------------------------------------------------//
// Add IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization support
// ---------------------------------------------------------------------------//

%pre_integral_setup( IntegralOrderedTypedObserver )

%include "MonteCarlo_IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization.hpp"

%post_integral_setup( IntegralOrderedTypedObserver )

// ---------------------------------------------------------------------------//
// Add UnorderedTypedObserverPhaseSpaceDimensionDiscretization support
// ---------------------------------------------------------------------------//

%pre_unordered_setup(UnorderedTypedObserver )

%include "MonteCarlo_UnorderedTypedObserverPhaseSpaceDimensionDiscretization.hpp"

%post_unordered_setup( UnorderedTypedObserver )

// ---------------------------------------------------------------------------//
// Add DefaultTypedObserverPhaseSpaceDimensionDiscretization support
// ---------------------------------------------------------------------------//

%pre_default_typed_setup( DefaultTypedObserver )

%include "MonteCarlo_DefaultTypedObserverPhaseSpaceDimensionDiscretization.hpp"

%post_default_typed_setup( DefaultTypedObserver )

//---------------------------------------------------------------------------//
// end MonteCarlo_ObserverPhaseSpaceDimensionDiscretization.i
//---------------------------------------------------------------------------//
